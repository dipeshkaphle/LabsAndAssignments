q1-DV-fail:
	ns q1.tcl 4 DV fail
	nam out.nam
	./con out.tr 7 8 rip4f 
	xgraph rip4f_pdr
	xgraph rip4f_plr
	xgraph rip4f_co
	ns q1.tcl 5 DV fail
	nam out.nam
	./con out.tr 12 13 rip5f
	xgraph rip5f_pdr
	xgraph rip5f_plr
	xgraph rip5f_co
	ns q1.tcl 6 DV fail
	nam out.nam
	./con out.tr 17 18 rip6f
	xgraph rip6f_pdr
	xgraph rip6f_plr
	xgraph rip6f_co
q1-DV-nofail:
	ns q1.tcl 4 DV nofail
	nam out.nam
	./con out.tr 7 8 rip4
	xgraph rip4_pdr
	xgraph rip4_plr
	xgraph rip4_co
	ns q1.tcl 5 DV nofail
	nam out.nam
	./con out.tr 12 13 rip5
	xgraph rip5_pdr
	xgraph rip5_plr
	xgraph rip5_co
	ns q1.tcl 6 DV nofail
	nam out.nam
	./con out.tr 17 18 rip6
	xgraph rip6_pdr
	xgraph rip6_plr
	xgraph rip6_co
q1-LS-fail:
	ns q1.tcl 4 LS fail
	nam out.nam
	./con out.tr 7 8 ospf4f 
	xgraph ospf4f_pdr
	xgraph ospf4f_plr
	xgraph ospf4f_co
	ns q1.tcl 5 LS fail
	nam out.nam
	./con out.tr 12 13 ospf5f 
	xgraph ospf5f_pdr
	xgraph ospf5f_plr
	xgraph ospf5f_co
	ns q1.tcl 6 LS fail
	nam out.nam
	./con out.tr 17 18 ospf6f 
	xgraph ospf6f_pdr
	xgraph ospf6f_plr
	xgraph ospf6f_co
q1-LS-nofail:
	ns q1.tcl 4 LS nofail
	nam out.nam
	./con out.tr 7 8 ospf4 
	xgraph ospf4_pdr
	xgraph ospf4_plr
	xgraph ospf4_co
	ns q1.tcl 5 LS nofail
	nam out.nam
	./con out.tr 12 13 ospf5 
	xgraph ospf5_pdr
	xgraph ospf5_plr
	xgraph ospf5_co
	ns q1.tcl 6 LS nofail
	nam out.nam
	./con out.tr 17 18 ospf6 
	xgraph ospf6_pdr
	xgraph ospf6_plr
	xgraph ospf6_co

all: q1-DV-fail q1-DV-nofail q1-LS-fail q1-LS-nofail
