#include <stdio.h>
#include <stdlib.h>
#include <openssl/ripemd.h>

int simpleRIPEND160(void* input, size_t length, unsigned char* md) {
  RIPEMD160_CTX context;
  if(!RIPEMD160_Init(&context))
    return -1;

  if (!RIPEMD160_Update(&context, input, length))
    return -1;

  if(!RIPEMD160_Final(md, &context))
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
        unsigned char md[RIPEMD160_DIGEST_LENGTH]; // 20 bytes
        if (!simpleRIPEND160(p, siz, md)) {
          for (int i = 0; i < RIPEMD160_DIGEST_LENGTH; ++i) {
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

