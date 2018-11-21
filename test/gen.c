#include <stdio.h>
#include <string.h>

static const unsigned char base64_table[65] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main() {
  unsigned char out[256];

  memset(out, 0x80, 255);
  for (int i = 0; i < 64; i++) {
    out[base64_table[i]] = i;
  }
  out['='] = 0;

  printf("static const unsigned char base64c_dtable[256] = {");
  for (int i = 0; i < 256; i++) {
    if (i% 20==0) { printf("\n"); }
    printf("/*%03d*/0x%02x,", i, out[i]);
  }
  printf("\n};");
}
