#!/usr/bin/env python3
from scapy.all import IP, TCP, sr

ip = "192.168.1.254"
ports = [22, 53, 80, 443, 3306] # ports to test

# send SYN packets and wait for replies
ans, unans = sr(IP(dst=ip)/TCP(dport=ports, flags="S"), timeout=2, verbose=0)

# analyse responses
for s,r in ans:
  if r.haslayer(TCP):
    if r[TCP].flags == "SA":
      print(f"port {s[TCP].dport} is OPEN")
    elif r[TCP].flags == "RA":
      print(f"port {s[TCP].dport} is CLOSED")

