#!/usr/bin/python3
import subprocess


def ifconfig(iface):
    return subprocess.check_output(['ifconfig', iface]).decode()


def macchanger(iface, macaddress):
    subprocess.call(['ifconfig', iface, 'down'])
    subprocess.call(['ifconfig', iface, 'hw', 'ether', macaddress])
    subprocess.call(['ifconfig', iface, 'up'])


def main():
    iface = 'enp0s3'
    #macaddress = 'AA:BB:CC:DD:EE:FF'
    macaddress = '08:00:27:af:cc:46'
    change1 = ifconfig(iface)
    macchanger(iface, macaddress)
    change2 = ifconfig(iface)
    if change1 == change2:
        print(f'[-] {iface}@{macaddress}')
    else:
        print(f'[+] {iface}@{macaddress}')


if __name__ == '__main__':
    main()

