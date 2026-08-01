#!/usr/bin/env python3
from scapy.all import *

IFACE = 'mon0'
SSIDS = ['testing', 'the', 'beacons']

packets = []

for ssid in SSIDS:
    src = RandMAC()
    packets.append(RadioTap()
                   / Dot11(type=0, subtype=8, # Management beacon frame
                           addr1='ff:ff:ff:ff:ff:ff', # Broadcast address
                           addr2=src,
                           addr3=src)
                   / Dot11Beacon(cap='ESS+privacy')
                   / Dot11Elt(ID='SSID', info=ssid, len=len(ssid))
                   / Dot11Elt(ID='RSNinfo', info=(
                    '\x01\x00'
                    '\x00\x0f\xac\x02'
                    '\x02\x00'
                    '\x00\x0f\xac\x04'
                    '\x00\x0f\xac\x02'
                    '\x01\x00'
                    '\x00\x0f\xac\x02'
                    '\x00\x00')))

# RSN info from https://www.4armed.com/blog/forging-wifi-beacon-frames-using-scapy/
while True:
    sendp(packets, iface=IFACE, inter=0.01)

