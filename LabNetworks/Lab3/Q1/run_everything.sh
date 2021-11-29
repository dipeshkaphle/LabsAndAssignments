#!/bin/bash


python3 throughput.py all.tr 4 0.0 4.0 1 > throughput_out.txt
python3 delay.py all.tr > delay_out.txt
python3 loss.py all.tr 3 0.0 4.0 1 > loss_out.txt
