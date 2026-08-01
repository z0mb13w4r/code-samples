#!/usr/bin/python3
import hashlib


def hash_this(password, name, func):
    hashobj = func()
    hashobj.update(password.encode())
    print(name, hashobj.hexdigest())


def hash_md5(password):
    hash_this(password, 'MD5:', hashlib.md5)


def hash_sha1(password):
    hash_this(password, 'SHA1:', hashlib.sha1)


def hash_sha224(password):
    hash_this(password, 'SHA224:', hashlib.sha224)


def hash_sha256(password):
    hash_this(password, 'SHA256:', hashlib.sha256)


def hash_sha384(password):
    hash_this(password, 'SHA384:', hashlib.sha384)


def hash_sha3_224(password):
    hash_this(password, 'SHA3_224:', hashlib.sha3_224)


def hash_sha3_256(password):
    hash_this(password, 'SHA3_256:', hashlib.sha3_256)


def hash_sha3_384(password):
    hash_this(password, 'SHA3_384:', hashlib.sha3_384)


def hash_sha3_512(password):
    hash_this(password, 'SHA3_512:', hashlib.sha3_512)


def main():
    password = 'admin'
    hash_md5(password)
    hash_sha1(password)
    hash_sha224(password)
    hash_sha256(password)
    hash_sha384(password)
    hash_sha3_224(password)
    hash_sha3_256(password)
    hash_sha3_384(password)
    hash_sha3_512(password)


if __name__ == '__main__':
    main()
