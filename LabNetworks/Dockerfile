FROM ubuntu:18.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y

RUN apt-get install -y build-essential autoconf automake libxmu-dev libgtk2.0-0 curl wget gcc-4.8 g++-4.8 

RUN apt install -y ns2 nam

RUN wget https://www.xgraph.org/linux/xgraph_4.38_linux64.tar.gz

RUN mkdir -p /opt/xgraph

RUN tar -xvf xgraph_4.38_linux64.tar.gz -C /opt/xgraph

RUN ln -s /opt/xgraph/XGraph4.38_linux64/bin/xgraph /usr/bin/

RUN apt install -y python3 vim tclsh

RUN apt install -y python3-pip

RUN pip3 install matplotlib
