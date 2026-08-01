#!/usr/bin/python3
import socket
import optparse
import threading


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

    return ip, hostname[0]


def portscanner(host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(5)
    if sock.connect_ex((host, port)):
        print(f'[-] {host}: tcp/{port} closed')
    else:
        print(f'[+] {host}: tcp/{port} open')
        sock.close()


def portscanners(host, ports):
    for port in ports:
        t = threading.Thread(target=portscanner, args=(host, int(port)))
        t.start()


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

    host, hostname = resolvename(host)
    print('[+]', host, hostname)

    portscanners(host, ports)


if __name__ == '__main__':
    main()

