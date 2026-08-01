#!/usr/bin/python3
import socket
import optparse
import threading


def portscanner(h, p):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(5)
    if sock.connect_ex((h, p)):
        print('[-] %s: Port %d is closed' % (h, p))
    else:
        print('[+] %s: Port %d is open' % (h, p))
        sock.close()


def main():
    p = optparse.OptionParser('Usage: -H <target> -p <port>')
    p.add_option('-H', dest='tgtHost', type='string', help='specify target host')
    p.add_option('-p', dest='tgtPorts', type='string', help='specify target ports separated by ports')
    options, args = p.parse_args()

    if options.tgtHost is None or options.tgtPorts is None:
        print(p.usage)
        exit(0)

    host = options.tgtHost
    ports = options.tgtPorts.split(',')

    for port in ports:
        portscanner(host, int(port))


if __name__ == '__main__':
    main()

