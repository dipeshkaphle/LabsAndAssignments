set ns [new Simulator]


$ns color 1 Blue
$ns color 2 Red


#Open the nam trace file
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

# make a tcp connection between src and sink
proc makeTcp { src sink } {
    global ns
    set tcp [new Agent/TCP]
    $ns attach-agent $src $tcp
    set sinkAgent [new Agent/TCPSink]
    $ns attach-agent $sink $sinkAgent
    $ns connect $tcp $sinkAgent
    $tcp set fid_ 1

    set ftp [new Application/FTP]
    $ftp attach-agent $tcp
    $ftp set type_ FTP
    return $ftp
}

# make a udp connection between src and sink
proc makeUdp { src sink } {
    global ns
    set udp [new Agent/UDP]
    $ns attach-agent $src $udp
    set null [new Agent/Null]
    $ns attach-agent $sink $null
    $ns connect $udp $null
    $udp set fid_ 2

    set cbr [new Application/Traffic/CBR]
    $cbr attach-agent $udp
    $cbr set type_ CBR
    $cbr set packet_size_ 1000
    $cbr set rate_ 1mb
    $cbr set random_ false
    return $cbr
}

proc makeNodes { num } {
    global ns
    
    set nodes [list]
    for {set i 0} {$i < $num} {incr i} {
        set node [$ns node]
        lappend nodes $node
    }
    return $nodes
}


# Get the routing protocol to be used as command line arg
set proto [ lindex $argv 0 ]
# set protocol
$ns rtproto $proto

set N 10
# make n nodes
for {set i 1} {$i <= $N} {incr i} {
    set n($i) [$ns node]
}



# Make Mesh
# connect each node with all other nodes
for {set i 1} {$i <= $N} {incr i} {
    for {set j [expr {$i + 1}]} {$j <= $N} {incr j} {
            $ns duplex-link $n($i) $n($j) 1Mb 10ms DropTail
    }
}

set ftp [makeTcp $n(1) $n(10)]
set cbr [makeUdp $n(1) $n(8)]


$ns rtmodel-at 45 down $n(2) $n(8)
$ns rtmodel-at 45 down $n(1) $n(10)
$ns rtmodel-at 45 down $n(4) $n(5)
$ns rtmodel-at 45 down $n(3) $n(7)
$ns rtmodel-at 45 down $n(6) $n(9)
$ns rtmodel-at 45 down $n(7) $n(9)
$ns rtmodel-at 45 down $n(1) $n(8)

$ns rtmodel-at 60 up $n(3) $n(7)
$ns rtmodel-at 60 up $n(1) $n(10)


$ns at 1.0 "$cbr start"
$ns at 30.0 "$ftp start"
$ns at 99.0 "$ftp stop"
$ns at 99.0 "$cbr stop"

# call finish after 200s
$ns at 100.0 "finish"

# run simulation
$ns run
