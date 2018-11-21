# base64c
This is primarily just a fork of a base64 decoder from the FreeBSD codebase. It has received a few modifications:
  * removed all allocations, you are expected to pass in a buffer that has sufficient space and you will get an error (-1) if you run out of space
  * replaced a dynamically generated lookup table with a hardcoded lookup table
  * wrote my own unit tests, i'm sure there are tests for freebsd somewhere but i didn't find them

# Embedding
This code is primarily intended to be dropped into an existing code base ( or perhaps using submodules). To do that:
  
  * grab include/base64c.h
  * grab src/base64c.h

# Usage

Call base64c_encoding_length() to calculate how big a buffer you need to encode a string. It's somewhere around 4 times the size of the input string. This length includes a null terminator.

```c
char input_string[256];

size_t new_len = base64c_encoding_length( strlen(input_string));

unsigned char *buffer = (unsigned char*)malloc(new_len);
```

Call base64c_encode() to actually encode your input string as base64. It will write to the buffer and return how many characters were written. If there was an error it will return -1.

```c
size_t output_length = base64c_encode(input_string, strlen(input_string), buffer, new_len);

if (output_length == -1) {
  int x = 1/0; // ERROR!
}
```

Call base64c_decoding_length() to calculate how big a buffer you need to decode. It comes out to about half the size. This number isn't always exact, but it is close to within a byte or two.

```c
size_t decode_len = base64c_decoding_length( strlen(buffer) );

unsigned char *decoded = (unsigned char*)malloc( decode_len );
```

Call base64c_decode() to decode an encoded base64 string. It will write to the buffer and return how many characters were written. IF there was an error it will return -1. If the string contains invalid number of characters, or has any characters that are not part of the base64 character set an error will be returned.

# Building

You need to bootstrap all the autoconf tools by running ./autogen.sh

You need to have autoconf installed to do this.

Once bootstrapped run ./configure

# Tests

There are tests in the test/ subfolder. They will be built automatically. There is no special test runner. You can run each of the test cases manually to check whether the code is working properly.
