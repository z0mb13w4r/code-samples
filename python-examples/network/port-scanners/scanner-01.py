#!/usr/bin/python3
import socket

host = '192.168.1.254'
port = 443


def portscanner(s, h, p):
    if s.connect_ex((h, p)):
        print('Port %d is closed' % p)
    else:
        print('Port %d is open' % p)


if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    portscanner(sock, host, port)
