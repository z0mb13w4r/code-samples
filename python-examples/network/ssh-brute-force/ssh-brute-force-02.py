#!/usr/bin/python3
from pexpect import pxssh


def ssh_connect(hostname, username, password):
    try:
        ssh = pxssh.pxssh()
        ssh.login(hostname, username, password)
        print(f'[+] {hostname}: {username}@{password}')
        return ssh
    except pxssh.ExceptionPxssh as e:
        print(f'[-] {hostname}: {username}@{password}')
        return None


def ssh_command(child, command):
    child.sendline(command)
    child.prompt()
    print(child.before.decode())


def main():
    host = '192.168.100.97'
    user = 'msfadmin'
    password = 'msfadmin'
    child = ssh_connect(host, user, password)
    if child:
        ssh_command(child, 'ls -al; ps')
        child.close()


if __name__ == '__main__':
    main()
