low-tahoe:
	python3 runner.py q2.tcl tahoe 5 0.01
	python3 plotter.py 'low_tahoe_pdr' pdr_out.txt 'low_tahoe_pdr_out.png'
	python3 plotter.py 'low_tahoe_control_over_head' control_overhead.txt 'low_tahoe_control_over_head.png'
	python3 plotter.py 'low_tahoe_congestion_control' congestion_control.txt 'low_tahoe_congestion_control.png'

medium-tahoe:
	python3 runner.py q2.tcl tahoe 15 0.01
	python3 plotter.py 'medium_tahoe_pdr' pdr_out.txt 'medium_tahoe_pdr_out.png'
	python3 plotter.py 'medium_tahoe_control_over_head' control_overhead.txt 'medium_tahoe_control_over_head.png'
	python3 plotter.py 'medium_tahoe_congestion_control' congestion_control.txt 'medium_tahoe_congestion_control.png'

high-tahoe:
	python3 runner.py q2.tcl tahoe 25 0.01
	python3 plotter.py 'high_tahoe_pdr' pdr_out.txt 'high_tahoe_pdr_out.png'
	python3 plotter.py 'high_tahoe_control_over_head' control_overhead.txt 'high_tahoe_control_over_head.png'
	python3 plotter.py 'high_tahoe_congestion_control' congestion_control.txt 'high_tahoe_congestion_control.png'

low-reno:
	python3 runner.py q2.tcl reno 5 0.01
	python3 plotter.py 'low_reno_pdr' pdr_out.txt 'low_reno_pdr_out.png'
	python3 plotter.py 'low_reno_control_over_head' control_overhead.txt 'low_reno_control_over_head.png'
	python3 plotter.py 'low_reno_congestion_control' congestion_control.txt 'low_reno_congestion_control.png'

medium-reno:
	python3 runner.py q2.tcl reno 15 0.01
	python3 plotter.py 'medium_reno_pdr' pdr_out.txt 'medium_reno_pdr_out.png'
	python3 plotter.py 'medium_reno_control_over_head' control_overhead.txt 'medium_reno_control_over_head.png'
	python3 plotter.py 'medium_reno_congestion_control' congestion_control.txt 'medium_reno_congestion_control.png'

high-reno:
	python3 runner.py q2.tcl reno 25 0.01
	python3 plotter.py 'high_reno_pdr' pdr_out.txt 'high_reno_pdr_out.png'
	python3 plotter.py 'high_reno_control_over_head' control_overhead.txt 'high_reno_control_over_head.png'
	python3 plotter.py 'high_reno_congestion_control' congestion_control.txt 'high_reno_congestion_control.png'

reno: low-reno medium-reno high-reno

tahoe: low-tahoe medium-tahoe high-tahoe

all: tahoe reno


.PHONY: low-tahoe high-tahoe medium-tahoe low-reno medium-reno high-reno all

