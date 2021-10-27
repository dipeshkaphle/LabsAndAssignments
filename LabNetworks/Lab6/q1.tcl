# new simulator object
set ns [new Simulator]

$ns color 1 Blue

set s [ lindex $argv 0 ]
set ss [expr $s * $s]
set proto [ lindex $argv 1 ]

# set protocol
$ns rtproto $proto

# set failure true or not
set failbool [lindex $argv 2]
# setting files for trace and nam data
set namtracefile [open out.nam w]
set tracefile [open out.tr w]
$ns namtrace-all $namtracefile
$ns trace-all $tracefile


# defining finish procedure to close files
proc finish {} {
    global ns namtracefile tracefile
    $ns flush-trace
    close $namtracefile
    close $tracefile
    #exec nam out.nam &
    exit 0
}

# grid


# create nodes
for {set i 0} {$i < $ss} {incr i} {
    set n($i) [$ns node]   
}

# create links between them
for {set i 0} {$i < $ss} {incr i} {
    if {[expr $i % $s] != 0} {
        $ns duplex-link $n($i) $n([expr $i - 1]) 1Mb 10ms DropTail
        $ns queue-limit $n($i) $n([expr $i - 1]) 20
        $ns queue-limit $n([expr $i - 1]) $n($i) 20
        
        if { $failbool == "fail" } {
            if {$i < [expr 0.15 * $ss]} {
                $ns rtmodel-at 30.0 down $n($i) $n([expr $i - 1])
                if {$i < [expr 0.05 * $ss]} {
                    $ns rtmodel-at 60.0 up $n($i) $n([expr $i - 1])
                } else {
                    $ns rtmodel-at 90.0 up $n($i) $n([expr $i - 1])
                }
            }
        }
    }
    if {$i >= $s} {
        $ns duplex-link $n($i) $n([expr $i - $s]) 1Mb 10ms DropTail
        $ns queue-limit $n($i) $n([expr $i - $s]) 20
        $ns queue-limit $n([expr $i - $s]) $n($i) 20
    }
}
set temp [expr $ss - 1 ]

for {set i 0} { $i < [ expr $ss / 2] } {incr i} {
    # setup tcp part
    set tcp($i) [new Agent/TCP]
    set sink($i) [new Agent/TCPSink]
    $ns attach-agent $n($i) $tcp($i)
    $ns attach-agent $n([expr $temp - $i]) $sink($i)
    $ns connect $tcp($i) $sink($i)


    # set packet information
    set ftp($i) [new Application/FTP]
    $ftp($i) attach-agent $tcp($i)
    $ftp($i) set type_ FTP
    
    # color
    $tcp($i) set fid_ 1

    # # schedule events
    $ns at 1.0 "$ftp($i) start"
    $ns at 99.0 "$ftp($i) stop"
}

$ns at 100.0 "finish"

# run
$ns run
