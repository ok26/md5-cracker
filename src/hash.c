#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const unsigned int s[64] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

static const unsigned int k[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static unsigned int leftRotate(unsigned int value, unsigned int n) {
    return (value << n) | (value >> ((sizeof(value) * 8) - n));
}

void md5(char* password, char* hash) {
    unsigned int a0 = 0x67452301;
    unsigned int b0 = 0xefcdab89;
    unsigned int c0 = 0x98badcfe;
    unsigned int d0 = 0x10325476;

    unsigned int original_length = strlen(password);
    char* padded = malloc(sizeof(char) * (original_length + 64 - original_length % 64));
    strcpy(padded, password);
    padded[original_length] = 0x80;
    unsigned int new_length = original_length + 1;
    while (new_length % 64 != 56) {
        padded[new_length] = 0x00;
        new_length++;
    }
    long long* l = (long long*)&padded[new_length];
    *l = (long long)(original_length * 8);
    new_length += 8;

    unsigned int chunk = 0;
    unsigned int* m = malloc(sizeof(unsigned int) * 16);
    while (chunk < new_length / 64) {
        
        m = (unsigned int*)&padded[chunk * 64];

        unsigned int a = a0;
        unsigned int b = b0;
        unsigned int c = c0;
        unsigned int d = d0;

        for (int i = 0; i < 64; i++) {
            unsigned int f, g;
            if (i < 16) {
                f = (b & c) | (~b & d);
                g = i;
            }
            else if (i < 32) {
                f = (d & b) | (~d & c);
                g = (5 * i + 1) % 16;
            }
            else if (i < 48) {
                f = b ^ c ^ d;
                g = (3 * i + 5) % 16;
            }
            else {
                f = c ^ (b | ~d);
                g = (7 * i) % 16;
            }

            f = f + a + k[i] + m[g];
            a = d;
            d = c;
            c = b;
            b = b + leftRotate(f, s[i]);
        }

        a0 = a0 + a;
        b0 = b0 + b;
        c0 = c0 + c;
        d0 = d0 + d;
        chunk++;
    }

    free(padded);

    unsigned int* p = (unsigned int*)hash;
    *p = a0;
    *(p + 1) = b0;
    *(p + 2) = c0;
    *(p + 3) = d0;
};

void hexdigest(char* digest, int length, char* output) {
    const char *hex_chars = "0123456789abcdef";

    for (int i = 0; i < length; i++) {
        output[i * 2] = hex_chars[(digest[i] >> 4) & 0xF];
        output[i * 2 + 1] = hex_chars[digest[i] & 0xF];
    }

    output[length * 2] = '\0';
}