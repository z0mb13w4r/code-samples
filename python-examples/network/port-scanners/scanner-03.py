#!/usr/bin/python3
import socket


def portscanner(s, h, p):
    if s.connect_ex((h, p)):
        print('[-] %s: Port %d is closed' % (h, p))
    else:
        print('[+] %s: Port %d is open' % (h, p))
        s.close()


if __name__ == '__main__':
    host = input('[+] Enter the host to scan: ')

    for port in range(1, 1000):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(5)

        portscanner(sock, host, port)


