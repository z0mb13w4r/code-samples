#!/usr/bin/python3
import paramiko


def ssh_connect(hostname, username, password):
    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy)
        ssh.connect(hostname=hostname, port=22, username=username, password=password)
        print(f'[+] {hostname}: SSH login')
        return ssh
    except paramiko.AuthenticationException:
        print(f'[-]  {hostname}: SSH failed to login')
        return None


def ssh_command(child, command):
    stdin, stdout, stderr = child.exec_command(command)
    print(stdout.read().decode())


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
