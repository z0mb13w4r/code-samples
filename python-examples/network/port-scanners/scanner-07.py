#!/usr/bin/python3
import socket
import optparse


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
        return '\t' + sock.recv(1024).decode().strip('\n')
    except:
        return None


def portscanner(host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(5)
    if sock.connect_ex((host, port)):
        print(f'[-] {host}: tcp/{port} closed')
    else:
        print(f'[+] {host}: tcp/{port} open')
        b = getbanner(sock)
        if b:
            print(f'[+] {host}:', b)
        sock.close()


def portscanners(host, ports):
    for port in ports:
        if port:
            portscanner(host, int(port))


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
    ports.sort()

    host, hostname = resolvename(host)

    portscanners(host, ports)


if __name__ == '__main__':
    main()

