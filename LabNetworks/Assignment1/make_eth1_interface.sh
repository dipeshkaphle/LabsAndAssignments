# https://unix.stackexchange.com/questions/152331/how-can-i-create-a-virtual-ethernet-interface-on-a-machine-without-a-physical-ad/152334#152334?newreg=fae89b45bb1c4960ae05e6eea9554922
sudo modprobe dummy
sudo lsmod | grep dummy
sudo ip link add eth1 type dummy
sudo ip address change dev eth1 10.0.0.1

# Up the eth1 interface
sudo ip link set up eth1

