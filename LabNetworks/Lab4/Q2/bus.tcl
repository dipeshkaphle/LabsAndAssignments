#Create a simulator object
set ns [new Simulator]

#Define different colors for data flows (for NAM)
$ns color 1 Blue
$ns color 2 Red

# Set all queue limit to 5
Queue set limit_ 5

#Open the NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf

set all_trace [open all.tr w]
$ns trace-all $all_trace


#Define a 'finish' procedure
proc finish {} {
        global ns nf all_trace
        $ns flush-trace
        #Close the NAM trace file
        close $nf
		close $all_trace
        #Execute NAM on the trace file
        exec nam out.nam &
        exit 0
}

for {set i 0} {$i < 10} {incr i} {
    set n($i) [$ns node]
}

# make a string
set s ""
for {set i 0} {$i < 10} {incr i} {
    set s "$s $n($i)"
}

set lan [$ns newLan "$s" 10Mb 50ms LL Queue/DropTail MAC/Csma Channel]

set s1 [lindex $argv 0]
set d1 [lindex $argv 1]
set s2 [lindex $argv 2]
set d2 [lindex $argv 3]

#Setup a TCP connection
set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n($s1) $tcp

set sink [new Agent/TCPSink]
$ns attach-agent $n($d1) $sink
$ns connect $tcp $sink
$tcp set fid_ 1

#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP


#Setup a UDP connection
set udp [new Agent/UDP]
$ns attach-agent $n($s2) $udp
set null [new Agent/Null]
$ns attach-agent $n($d2) $null
$ns connect $udp $null
$udp set fid_ 2

#Setup a CBR over UDP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packetSize_ 1000
$cbr set rate_ 10Mb
$cbr set random_ false

#Schedule events for the CBR and FTP agents
$ns at 1.0 "$cbr start"
$ns at 1.0 "$ftp start"
$ns at 49.0 "$ftp stop"
$ns at 49.0 "$cbr stop"

$ns at 50.0 "finish"

$ns run
