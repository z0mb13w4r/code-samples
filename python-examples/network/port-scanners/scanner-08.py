#!/usr/bin/python3
import socket
import optparse
import os


def resolvename(host):
    try:
        ip = socket.gethostbyname(host)
    except:
        print(f'[!] unknown host: {host}')
    try:
        hostname = socket.gethostbyaddr(ip)
    except:
        print(f'[!] unknown IP address: {ip}')
        return ip, 'unknown'

    print('[+]', host, hostname[0])
    return ip, hostname[0]


def getbanner(sock):
    try:
        return sock.recv(1024).decode().strip('\n')
    except:
        return None


def checkbanner(banner, vuln):
    if vuln:
        f = open(vuln, 'r')
        for i in f.readlines():
            if i.strip('\n') in banner:
                print('[+] SERVER IS VULNERABLE {banner}')


def portscanner(host, port, vuln):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(5)
    if sock.connect_ex((host, port)):
        print(f'[-] {host}: tcp/{port} closed')
    else:
        print(f'[+] {host}: tcp/{port} open')
        b = getbanner(sock)
        if b:
            print(f'[+] {host}:\t{b}')
            checkbanner(b, vuln)
        sock.close()


def portscanners(host, ports, vuln):
    for port in ports:
        if port:
            portscanner(host, int(port), vuln)


def main():
    p = optparse.OptionParser('Usage: -H <target> -p <port> [-v <banners file>]')
    p.add_option('-H', dest='tgtHost', type='string', help='specify target host')
    p.add_option('-p', dest='tgtPorts', type='string', help='specify target ports separated by ports')
    p.add_option('-v', dest='vulnBanner', type='string', help='specify vulnerability banners')
    options, args = p.parse_args()

    if options.tgtHost is None or options.tgtPorts is None:
        print(p.usage)
        exit(0)

    if options.vulnBanner:
        if not os.path.isfile(options.vulnBanner):
            print(f'[-] {options.vulnBanner} does not exist')
            exit(0)
        elif not os.access(options.vulnBanner, os.R_OK):
            print(f'[-] {options.vulnBanner} access denied')
            exit(0)

    vuln = options.vulnBanner
    host = options.tgtHost
    ports = options.tgtPorts.split(',')
    ports.sort()

    host, hostname = resolvename(host)

    portscanners(host, ports, vuln)


if __name__ == '__main__':
    main()

