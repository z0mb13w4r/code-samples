#!/usr/bin/python3
from urllib.request import urlopen
import hashlib


def get(url):
    url = 'https://raw.githubusercontent.com/' + url
    return urlopen(url).read().decode().split('\n')


def check(passwords, hashed):
    for password in passwords:
        sha1 = hashlib.sha1(password.encode()).hexdigest()
        if hashed == sha1:
            print('[+] SHA1:', hashed, password)
            return True

    print('[-] SHA1:', hash)
    return False


def main():
    hashed = 'd033e22ae348aeb5660fc2140aec35850c4da997'
    p = get('danielmiessler/SecLists/master/Passwords/Common-Credentials/10-million-password-list-top-1000000.txt')
    if p:
        check(p, hashed)


if __name__ == '__main__':
    main()
