#include "../include/base64c.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  unsigned char in[13] = "Hello Worlds";
  size_t in_len = 12;
  unsigned char enc[32];
  size_t enc_len = 32;
  unsigned char out[13];
  size_t out_len = 13;

  printf("Encoding %lu - %s\n", in_len, in);

  size_t enc_result = base64c_encode(in, in_len, enc, enc_len);

  printf("Encoded %lu - %s\n", enc_result, enc);

  size_t dec_result = base64c_decode(enc, enc_result, out, out_len);

	if ((long)dec_result < 0) {
    printf("Decode failed with code %ld\n", (long)dec_result);
    return 1;
  }

  printf("Decoded %lu - %s\n", dec_result, out);

  if (dec_result != in_len) {
    printf("in length %ld not equal to out length %ld", in_len, dec_result);
    return 3;
  }
	if (strncmp((char*)in, (char*)out, in_len)) {
		printf("roundtrip encoding failed\n");
		return 2;
	}
}
