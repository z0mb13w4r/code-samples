#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

int simpleSHA1(void* input, size_t length, unsigned char* md) {
  SHA_CTX context;
  if(!SHA1_Init(&context))
    return -1;

  if (!SHA1_Update(&context, input, length))
    return -1;

  if(!SHA1_Final(md, &context))
    return -1;

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 2) {
    FILE *f = fopen(argv[1], "rb");
    if (f) {
      fseek(f, 0, SEEK_END);
      size_t siz = ftell(f);
      fseek(f, 0, SEEK_SET);

      void *p = malloc(siz);
      if (p) {
        fread(p, siz, 1, f);
        unsigned char md[SHA_DIGEST_LENGTH]; // 20 bytes
        if (!simpleSHA1(p, siz, md)) {
          for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
            printf("%02x", md[i]);
          }
          printf("\n");
        }
        free(p);
      }
      fclose(f);
    }
  }

  return 0;
}

