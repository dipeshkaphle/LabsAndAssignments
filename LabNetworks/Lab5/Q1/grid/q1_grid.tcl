#Create a simulator object
set ns [new Simulator]

#Define different colors for data flows (for NAM)
$ns color 1 Blue
$ns color 2 Red

#Open the NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf

set all_trace [open all.tr w]
$ns trace-all $all_trace

#Define a 'finish' procedure
proc finish {} {
        global ns nf all_trace
        $ns flush-trace
	#Close the trace file
        close $nf
	close $all_trace
	#Execute nam on the trace file
        exec nam out.nam &
        exit 0
}

for {set i 0} {$i < 25} {incr i} {
    set n($i) [$ns node]
}

for {set i 0} {$i < 5} {incr i} {
    for {set j 0} {$j < 4} {incr j} {
        set k1 [expr {5*$i + $j}]
        set k2 [expr {$k1 + 1}]
        $ns duplex-link $n($k1) $n($k2) 2Mb 10ms DropTail
        $ns duplex-link-op $n($k1) $n($k2) orient right
        $ns queue-limit $n($k1) $n($k2) 2
        $ns queue-limit $n($k2) $n($k1) 2
        $ns duplex-link-op $n($k1) $n($k2) queuePos 0.5
    }
}

for {set i 0} {$i < 5} {incr i} {
    for {set j 0} {$j < 4} {incr j} {
        set k1 [expr {$i + 5*$j}]
        set k2 [expr {$k1 + 5}]
        $ns duplex-link $n($k1) $n($k2) 2Mb 10ms DropTail
        $ns duplex-link-op $n($k1) $n($k2) orient down
        $ns queue-limit $n($k1) $n($k2) 2
        $ns queue-limit $n($k2) $n($k1) 2
        $ns duplex-link-op $n($k1) $n($k2) queuePos 0.5
    }
}

set s [lindex $argv 0]
set d [lindex $argv 1]
set type [lindex $argv 2]

if {$type == "tcp"} {

    #Setup a TCP connection
    set tcp [new Agent/TCP]
    $tcp set class_ 2
    $ns attach-agent $n($s) $tcp

    set sink [new Agent/TCPSink]
    $ns attach-agent $n($d) $sink
    $ns connect $tcp $sink
    $tcp set fid_ 1

    #Setup a FTP over TCP connection
    set ftp [new Application/FTP]
    $ftp attach-agent $tcp
    $ftp set type_ FTP

    $ns at 0.5 "$ftp start"
    $ns at 4.5 "$ftp stop"

} elseif {$type == "udp"} {

    #Setup a UDP connection
    set udp [new Agent/UDP]
    $ns attach-agent $n($s) $udp
    set null [new Agent/Null]
    $ns attach-agent $n($d) $null
    $ns connect $udp $null
    $udp set fid_ 2

    #Setup a CBR over UDP connection
    set cbr [new Application/Traffic/CBR]
    $cbr attach-agent $udp
    $cbr set type_ CBR
    $cbr set packet_size_ 1000
    $cbr set rate_ 3mb
    $cbr set random_ false

    $ns at 0.5 "$cbr start"
    $ns at 4.5 "$cbr stop"
}
# call finish after 5s
$ns at 5.0 "finish"

# run ns
$ns run