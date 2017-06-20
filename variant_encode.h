#ifndef VARIANT_ENCODE_H
#define VARIANT_ENCODE_H
#include <stdint.h>
#include <stddef.h>

//! [-2^6, 2^6 - 1]
#define BIT7_MAX  ((1 << 6) - 1)
#define BIT7_MIN -(1 << 6)

#define BIT14_MAX ((1 << 13) - 1)
#define BIT14_MIN -(1 << 13)

#define BIT21_MAX ((1 << 20) - 1)
#define BIT21_MIN -(1 << 20)

#define BIT28_MAX ((1 << 27) - 1)
#define BIT28_MIN -(1 << 27)

#define BIT35_MAX ((1L << 34L) - 1L)
#define BIT35_MIN -(1L << 34L)

#define BIT42_MAX (1L << 41L - 1L)
#define BIT42_MIN -(1L << 41L)

#define BIT49_MAX (1L << 48L - 1L)
#define BIT49_MIN -(1L << 48L)

#define BIT56_MAX (1L << 55L - 1L)
#define BIT56_MIN -(1L << 55L)

#define BIT64_MAX (1L << 63L - 1L)
#define BIT64_MIN -(1L << 63L)

#define UBIT7_MAX ((1 << 7) - 1)
#define UBIT14_MAX ((1 << 14) - 1)
#define UBIT21_MAX ((1 << 21) - 1)
#define UBIT28_MAX ((1 << 28) - 1)
#define UBIT35_MAX ((1L << 35L) - 1L)
#define UBIT42_MAX ((1L << 42L) - 1L)
#define UBIT56_MAX ((1L << 56L) - 1L)
#define UBIT64_MAX ((1L << 64L) - 1L)

#define BIT16_MAX_BYTES 3
#define BIT32_MAX_BYTES 5
#define BIT64_MAX_BYTES 9

size_t u16_encode(uint16_t var, unsigned char buffer[BIT16_MAX_BYTES]);
uint16_t u16_decode(const unsigned char* buffer, size_t* nCh);

size_t i16_encode(int16_t var, unsigned char buffer[BIT16_MAX_BYTES]);
int16_t i16_decode(const unsigned char* buffer, size_t *nCh);

size_t u32_encode(uint32_t var, unsigned char buffer[BIT32_MAX_BYTES]);
uint32_t u32_decode(const unsigned char* buffer, size_t* nCh);

size_t i32_encode(int32_t var, unsigned char buffer[]);
int32_t i32_decode(unsigned char* buffer, size_t* nCh);

size_t u64_encode(uint64_t var, unsigned char buffer[BIT64_MAX_BYTES]);
uint64_t u64_decode(unsigned char* buffer, size_t* nCh);

size_t i64_encode(uint64_t var, unsigned char buffer[BIT64_MAX_BYTES]);
int64_t i64_decode(unsigned char* buffer, size_t* nCh);

#endif // VARIANT_ENCODE_H
