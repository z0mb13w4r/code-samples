#!/usr/bin/python3
from scapy.all import *

# craft a DNS query packet
pkt = IP(dst="8.8.8.8")/UDP(dport=53)/DNS(rd=1, qd=DNSQR(qname="www.example.com"))

# send and receive the packet
rsp = sr1(pkt)

# print the answer section of the DNS response
rsp[DNS].summary()
rsp[DNS].show()

