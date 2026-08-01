#!/usr/bin/python3
import pexpect

PROMPT = [pexpect.TIMEOUT, pexpect.EOF, '#', '~$', '>', '>>>']
PASSWORD = '[Pp]assword: '


def ssh_connect(user, host, password):
    ssh_newkey = 'Are you sure you want to continue connecting'
    ssh_command = '/usr/bin/ssh ' + user + '@' + host

    child = pexpect.spawn(ssh_command)
    r = child.expect([pexpect.TIMEOUT, ssh_newkey, PASSWORD], timeout=5)
    if r == 0:
        print('[-] Error connecting')
        return None

    elif r == 1:
        child.sendline('yes')
        r = child.expect([pexpect.TIMEOUT, PASSWORD], timeout=5)
        if r == 0:
            print('[-] Error connecting')
            return None

    child.sendline(password)
    r = child.expect(PROMPT, timeout=5)

    if r == 0 or r == 1:
        print('[-] Error connecting')
        return None

    r = child.expect([pexpect.TIMEOUT, pexpect.EOF], timeout=5)
    print(f'[+] {host}: {user}@{password}')
    return child


def send_command(child, command):
    print('-' * 10, command, '-' * 10)
    try:
        #r = child.expect([pexpect.TIMEOUT, pexpect.EOF], timeout=5)

        child.sendline(command)
        #print('xxx', child.before.decode())
        r = child.expect(PROMPT, timeout=5)
        #r = child.expect([pexpect.TIMEOUT, pexpect.EOF, '$'], timeout=5)
        #r = child.expect([pexpect.TIMEOUT, 'msfadmin.*:'], timeout=5)
        #r = child.expect([pexpect.TIMEOUT, pexpect.EOF], timeout=5)
        print('xxx', r, 'xxx', child.before.decode())
    except:
        pass


def main():
    host = '192.168.100.97'
    user = 'msfadmin'
    password = 'msfadmin'
    child = ssh_connect(user, host, password)
    if child:
        send_command(child, ' whoami ')
        send_command(child, 'hostname')
        send_command(child, 'uname -a')


if __name__ == '__main__':
    main()
