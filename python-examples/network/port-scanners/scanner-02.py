#!/usr/bin/python3
import socket


def portscanner(s, h, p):
    if s.connect_ex((h, p)):
        print('Port %d is closed' % p)
    else:
        print('Port %d is open' % p)


if __name__ == '__main__':
    host = input('[+] Enter the host to scan: ')
    port = int(input('[+] Enter the port to scan: '))

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    portscanner(sock, host, port)
