#!/usr/bin/python3
import hashlib


def check(passwords, hashed):
    try:
        with open(passwords, 'r') as f:
            for password in f.readlines():
                md5 = hashlib.md5(password.strip('\n').encode()).hexdigest()
                if hashed == md5:
                    print('[+] MD5:', hashed, password)
                    f.close()
                    return True

            f.close()

        print('[-] MD5:', hashed, password)
        return False

    except FileNotFoundError:
        print(f'[-] {passwords} file does not exist!')
        return False


def main():
    hashed = '21232f297a57a5a743894a0e4a801fc3'
    check('10-million-password-list-top-1000000.txt', hashed)


if __name__ == '__main__':
    main()
