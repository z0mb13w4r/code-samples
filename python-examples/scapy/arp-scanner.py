#!/usr/bin/python3
from scapy.all import ARP, Ether, srp

target = "192.168.1.0/24"

pkt = Ether(dst="ff:ff:ff:ff:ff:ff")/ARP(pdst=target)
ans, _ = srp(pkt, timeout=2, verbose=0)
for _, r in ans:
  print(f"IP: {r.psrc}, MAC: {r.hwsrc}")

