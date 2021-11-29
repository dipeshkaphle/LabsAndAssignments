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

# make a linear topology of the nodes given
proc makeLinear { nodes options } {
    global ns
    set linkBandwith [lindex $options 0]
    set linkDelay [lindex $options 1]
    set queueType [lindex $options 2]

    for {set i 0} {$i < [llength $nodes] - 1} {incr i} {
        $ns duplex-link [lindex $nodes $i] [lindex $nodes [expr $i+1]] $linkBandwith $linkDelay $queueType
    }
}

# make a ring topology of the nodes given
proc makeRing { nodes options } {
    global ns
    set linkBandwith [lindex $options 0]
    set linkDelay [lindex $options 1]
    set queueType [lindex $options 2]
    for {set i 0} {$i < [llength $nodes] - 1} {incr i} {
        $ns duplex-link [lindex $nodes $i] [lindex $nodes [expr $i+1]] $linkBandwith $linkDelay $queueType
    }
    $ns duplex-link [lindex $nodes [expr [llength $nodes] - 1]] [lindex $nodes 0] $linkBandwith $linkDelay $queueType
}

# make a star topology of the nodes given (connects the first node to all others)
proc makeStar { nodes options } {
    global ns
    set linkBandwith [lindex $options 0]
    set linkDelay [lindex $options 1]
    set queueType [lindex $options 2]
    for {set i 1} {$i < [llength $nodes]} {incr i} {
        $ns duplex-link [lindex $nodes $i] [lindex $nodes 0] $linkBandwith $linkDelay $queueType
    }
}

# make a grid topology of the nodes given and length and width
proc makeGrid { nodes options length width } {
    global ns
    set linkBandwith [lindex $options 0]
    set linkDelay [lindex $options 1]
    set queueType [lindex $options 2]
    for {set i 0} {$i < $length} {incr i} {
        for {set j 0} {$j < $width} {incr j} {
            if {$i > 0} {
                $ns duplex-link [lindex $nodes [expr $i*$width + $j]] [lindex $nodes [expr ($i-1)*$width + $j]] $linkBandwith $linkDelay $queueType
            }
            if {$j > 0} {
                $ns duplex-link [lindex $nodes [expr $i*$width + $j]] [lindex $nodes [expr $i*$width + [expr $j-1]]] $linkBandwith $linkDelay $queueType
            }
        }
    }
}

# make a bus topology of the nodes
proc makeBus { nodes } {
    set s ""
    for {set i 0} {$i < [llength $nodes]} {incr i} {
        set s [concat $s [lindex $nodes $i] " "]
    }
    set lan [$ns newLan "$s" 1Mb 50ms LL Queue/DropTail MAC/Csma Channel]
}

# make a list of nodes of the given length 
proc makeNodes { num } {
    global ns
    
    set nodes [list]
    for {set i 0} {$i < $num} {incr i} {
        set node [$ns node]
        lappend nodes $node
    }
    return $nodes
}

set n 25
# make n nodes
set nodes [makeNodes $n]
set options [list 1Mb 10ms DropTail]
makeGrid $nodes $options 5 5

set ftp [makeTcp [lindex $nodes 0] [lindex $nodes [expr 24]]]
set cbr [makeUdp [lindex $nodes 5] [lindex $nodes [expr 19]]]

$ns at 0.1 "$cbr start"
$ns at 1.0 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 4.5 "$cbr stop"

# call finish after 5s
$ns at 5.0 "finish"

# run ns
$ns run