#!/usr/bin/python3
from scapy.all import IP, ICMP, sr1

# create a packet
pkt = IP(dst="8.8.8.8")/ICMP()

# check the contents of the packet
print("=== sent packet ===")
pkt.show()

# send it and wait for a reply
ans = sr1(pkt, timeout=2)

# check the reply packet
if ans:
  print("\n=== reply packet ===")
  ans.show()
else:
  print("=== no reply  ===")

