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


set cols 10
set rows 5
set total [expr $cols * $rows]

for {set i 0} {$i < $total} {incr i} {
    set n($i) [$ns node]
}

for {set i 0} {$i < $rows} {incr i} {
    for {set j 0} {$j < [expr {$cols-1}]} {incr j} {
        set k1 [expr {$cols*$i + $j}]
        set k2 [expr {$k1 + 1}]
        $ns duplex-link $n($k1) $n($k2) 1Mb 10ms DropTail
        $ns duplex-link-op $n($k1) $n($k2) orient right
        $ns queue-limit $n($k1) $n($k2) 10
        $ns queue-limit $n($k2) $n($k1) 10
        $ns duplex-link-op $n($k1) $n($k2) queuePos 0.5
    }
}

for {set i 0} {$i < $cols} {incr i} {
    for {set j 0} {$j < [expr {$rows - 1}]} {incr j} {
        set k1 [expr {$i + $cols*$j}]
        set k2 [expr {$k1 + $cols}]
        $ns duplex-link $n($k1) $n($k2) 1Mb 10ms DropTail
        $ns duplex-link-op $n($k1) $n($k2) orient down
        $ns queue-limit $n($k1) $n($k2) 10
        $ns queue-limit $n($k2) $n($k1) 10
        $ns duplex-link-op $n($k1) $n($k2) queuePos 0.5
    }
}

set type [lindex $argv 0]
set traffic [lindex $argv 1]

set no_of_source [expr {int($traffic*$total/100.0)}]



for {set i 0} {$i < $no_of_source} {incr i} {

    if {$type == "tahoe"} {
        set tcp($i) [new Agent/TCP]
    } elseif {$type == "reno"} {
        set tcp($i) [new Agent/TCP/Reno]
    }

    set test ""

    set s [expr {int(rand()*50)}]
    set test "$test $s"

    set d [expr {int(rand()*50)}]
    set test "$test $d"

    puts "$test"

    $tcp($i) set class_ 2
    $ns attach-agent $n($s) $tcp($i)
    $tcp($i) tracevar cwnd_


    set sink($i) [new Agent/TCPSink]
    $ns attach-agent $n($d) $sink($i)
    $ns connect $tcp($i) $sink($i)
    $tcp($i) set fid_ 1

    #Setup a FTP over TCP connection
    set ftp($i) [new Application/FTP]
    $ftp($i) attach-agent $tcp($i)
    $ftp($i) set type_ FTP

    $ns at 0.5 "$ftp($i) start"
    $ns at 49.5 "$ftp($i) stop"
}

# call finish after 5s
$ns at 50.0 "finish"

# run ns
$ns run
