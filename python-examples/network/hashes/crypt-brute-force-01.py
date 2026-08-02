#!/usr/bin/python3
import crypt


def encrypt(password, salt):
    return crypt.crypt(password, salt)


def check(passwords, encrypted):
    try:
        with open(passwords, 'r') as f:
            for password in f.readlines():
                crypted = encrypt(password.strip('\n'), encrypted[:2])
                if encrypted == crypted:
                    print('[+] CRYPT:', encrypted, password)
                    f.close()
                    return True

            f.close()

        print('[-] CRYPT:', encrypted, password)
        return False

    except FileNotFoundError:
        print(f'[-] {passwords} file does not exist!')
        return False


def main():
    encrypted = 'GHbEfIMmMF95o'
    check('10-million-password-list-top-1000000.txt', encrypted)


if __name__ == '__main__':
    main()
