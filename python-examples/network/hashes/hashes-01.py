#!/usr/bin/python3
import hashlib


def hash_md5(password):
    hashobj = hashlib.md5()
    hashobj.update(password.encode())
    print('MD5:', hashobj.hexdigest())


def hash_sha1(password):
    hashobj = hashlib.sha1()
    hashobj.update(password.encode())
    print('SHA1:', hashobj.hexdigest())


def hash_sha224(password):
    hashobj = hashlib.sha224()
    hashobj.update(password.encode())
    print('SHA224:', hashobj.hexdigest())


def hash_sha256(password):
    hashobj = hashlib.sha256()
    hashobj.update(password.encode())
    print('SHA256:', hashobj.hexdigest())


def hash_sha384(password):
    hashobj = hashlib.sha384()
    hashobj.update(password.encode())
    print('SHA384:', hashobj.hexdigest())


def hash_sha3_224(password):
    hashobj = hashlib.sha3_224()
    hashobj.update(password.encode())
    print('SHA3_224:', hashobj.hexdigest())


def hash_sha3_256(password):
    hashobj = hashlib.sha3_256()
    hashobj.update(password.encode())
    print('SHA3_256:', hashobj.hexdigest())


def hash_sha3_384(password):
    hashobj = hashlib.sha3_384()
    hashobj.update(password.encode())
    print('SHA3_384:', hashobj.hexdigest())


def hash_sha3_512(password):
    hashobj = hashlib.sha3_512()
    hashobj.update(password.encode())
    print('SHA3_512:', hashobj.hexdigest())


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
