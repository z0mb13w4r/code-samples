/* zmemory.c: example of proper use of zlib's inflate() and deflate() */

#include <zlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define CHUNK 16384

void* get(const char* name, size_t *size) {
  if (name && size) {
    FILE* f = fopen(name, "rb");
    if (f) {
      fseek(f, 0, SEEK_END);
      *size = ftell(f);
      fseek(f, 0, SEEK_SET);
      if (0 < *size) {
        void *p = malloc(*size);
        if (*size == fread(p, 1, *size, f)) {
          fclose(f);
          return p;
        }
      }
      fclose(f);
    }
  }
  return NULL;
}

int put(const char* name, const void* data, size_t size) {
  if (name && data && size) {
    FILE* f = fopen(name, "wb");
    if (f) {
      int b = fwrite(data, 1, size, f);
      fclose(f);
      return b;
    }
  }

  return 0;
}

int def(void *src, size_t srcsize, void *dst, size_t *dstsize, int level) {
  int ret;

  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = (uInt)srcsize;
  strm.next_in = (Bytef *)src;
  strm.avail_out = (uInt)*dstsize;
  strm.next_out = (Bytef *)dst;

  ret = deflateInit(&strm, level);
  if (ret != Z_OK)
    return ret;

  ret = deflate(&strm, Z_FINISH); /* no bad return value */
  assert(ret != Z_STREAM_ERROR);  /* state not clobbered */

  /* clean up and return */
  (void)deflateEnd(&strm);

// This is one way of getting the size of the output
printf("Deflated size is: %lu\n", (char*)strm.next_out - (char*)dst);
  *dstsize = (char*)strm.next_out - (char*)dst;

  return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int inf(void *src, size_t srcsize, void *dst, size_t *dstsize) {
  int ret;
  z_stream strm;

  /* allocate inflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = (uInt)srcsize;
  strm.next_in = (Bytef *)src;
  strm.avail_out = (uInt)*dstsize;
  strm.next_out = (Bytef *)dst;

  ret = inflateInit(&strm);
  if (ret != Z_OK)
    return ret;

  ret = inflate(&strm, Z_NO_FLUSH);
  assert(ret != Z_STREAM_ERROR);  /* state not clobbered */

  /* clean up and return */
  (void)inflateEnd(&strm);

// This is one way of getting the size of the output
printf("Inflated size is: %lu\n", (char*)strm.next_out - (char*)dst);
  *dstsize = (char*)strm.next_out - (char*)dst;

  return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

/* report a zlib or i/o error */
int zerr(int ret) {
  if (Z_OK != ret) {
    fputs("zmemory: ", stderr);
    switch (ret) {
    case Z_ERRNO:
      if (ferror(stdin))
        fputs("error reading stdin\n", stderr);
      if (ferror(stdout))
        fputs("error writing stdout\n", stderr);
      break;
    case Z_STREAM_ERROR:
      fputs("invalid compression level\n", stderr);
      break;
    case Z_DATA_ERROR:
      fputs("invalid or incomplete deflate data\n", stderr);
      break;
    case Z_MEM_ERROR:
      fputs("out of memory\n", stderr);
      break;
    case Z_VERSION_ERROR:
      fputs("zlib version mismatch!\n", stderr);
    }
  }
  return ret;
}

/* compress or decompress from memory */
int main(int argc, char* argv[]) {
  /* do compression if two arguments */
  if (argc == 3) {
    size_t srcsize = 0;
    void*  src = get(argv[1], &srcsize);
    size_t dstsize = 2 * srcsize;
    void*  dst = malloc(dstsize);
    int ret = zerr(def(src, srcsize, dst, &dstsize, Z_DEFAULT_COMPRESSION));
    put(argv[2], dst, dstsize);
    return ret;
  }
  /* do decompression if -d specified */
  else if (argc == 4 && strcmp(argv[1], "-d") == 0) {
    size_t srcsize = 0;
    void*  src = get(argv[2], &srcsize);
    size_t dstsize = 10 * srcsize;
    void*  dst = malloc(dstsize);
    int ret = zerr(inf(src, srcsize, dst, &dstsize));
    put(argv[3], dst, dstsize);
    return ret;
  }

  /* otherwise, report usage */
  fputs("zmemory usage: zmemory [-d] src dst\n", stderr);
  return 1;
}

