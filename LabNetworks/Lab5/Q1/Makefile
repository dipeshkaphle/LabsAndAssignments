tcp:
	cd bus && make tcp
	cd grid && make tcp

udp:
	cd bus && make udp
	cd grid && make udp

tcp-plots: tcp
	python3 plotter.py TCP bus/throughput_out.txt grid/throughput_out.txt tcp_throughput.png
	python3 plotter.py TCP bus/bandwithutil_out.txt grid/bandwithutil_out.txt tcp_bandwith_util.png
	python3 plotter.py TCP bus/e2e_delay.txt grid/e2e_delay.txt tcp_e2e_delay.png
	python3 plotter.py TCP bus/packet_drop_ratio_out.txt grid/packet_drop_ratio_out.txt tcp_pdr.png


udp-plots: udp
	python3 plotter.py UDP bus/throughput_out.txt grid/throughput_out.txt udp_throughput.png
	python3 plotter.py UDP bus/bandwithutil_out.txt grid/bandwithutil_out.txt udp_bandwith_util.png
	python3 plotter.py UDP bus/e2e_delay.txt grid/e2e_delay.txt udp_e2e_delay.png
	python3 plotter.py UDP bus/packet_drop_ratio_out.txt grid/packet_drop_ratio_out.txt udp_pdr.png



.PHONY: tcp udp tcp-plots udp-plots
