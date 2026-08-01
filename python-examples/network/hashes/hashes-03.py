#!/usr/bin/python3
import hashlib


def hash_this(password, name, func):
    hashobj = func()
    hashobj.update(password.encode())
    print(name, hashobj.hexdigest())


def main():
    password = 'admin'
    hash_this(password, 'MD5:', hashlib.md5)
    hash_this(password, 'SHA1:', hashlib.sha1)
    hash_this(password, 'SHA224:', hashlib.sha224)
    hash_this(password, 'SHA256:', hashlib.sha256)
    hash_this(password, 'SHA384:', hashlib.sha384)
    hash_this(password, 'SHA3_224:', hashlib.sha3_224)
    hash_this(password, 'SHA3_256:', hashlib.sha3_256)
    hash_this(password, 'SHA3_384:', hashlib.sha3_384)
    hash_this(password, 'SHA3_512:', hashlib.sha3_512)


if __name__ == '__main__':
    main()
