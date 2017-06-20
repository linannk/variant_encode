#ifndef VARIANT_ENCODE_H
#define VARIANT_ENCODE_H
#include <stdint.h>
#include <stddef.h>

//! [-2^6, 2^6 - 1]
#define BIT7_MAX  ((1 << 6) - 1)
#define BIT7_MIN  (-(1 << 6))

#define BIT14_MAX ((1 << 13) - 1)
#define BIT14_MIN (-(1 << 13))

#define BIT21_MAX ((1 << 20) - 1)
#define BIT21_MIN (-(1 << 20))

#define BIT28_MAX ((1 << 27) - 1)
#define BIT28_MIN (-(1 << 27))

#define BIT35_MAX ((1LL << 34LL) - 1LL)
#define BIT35_MIN (-(1LL << 34LL))

#define BIT42_MAX ((1LL << 41LL) - 1LL)
#define BIT42_MIN (-(1LL << 41LL))

#define BIT49_MAX ((1LL << 48LL) - 1LL)
#define BIT49_MIN (-(1LL << 48LL))

#define BIT56_MAX ((1LL << 55LL) - 1LL)
#define BIT56_MIN (-(1LL << 55LL))

#define BIT64_MAX ((1LL << 63LL) - 1LL)
#define BIT64_MIN (-(1LL << 63LL))

#define UBIT7_MAX ((1 << 7) - 1)
#define UBIT14_MAX ((1 << 14) - 1)
#define UBIT21_MAX ((1 << 21) - 1)
#define UBIT28_MAX ((1 << 28) - 1)
#define UBIT35_MAX ((1LL << 35LL) - 1LL)
#define UBIT42_MAX ((1LL << 42LL) - 1LL)
#define UBIT49_MAX ((1LL << 49LL) - 1LL)
#define UBIT56_MAX ((1LL << 56LL) - 1LL)
#define UBIT64_MAX (0xffffffffffffffff)

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

size_t encode_float(float var, unsigned char buffer[5]);
float decode_float(const unsigned char* buffer, size_t* nCh);

size_t encode_double(double var, unsigned char buffer[9]);
double decode_double(const unsigned char* buffer, size_t* nCh);


#endif // VARIANT_ENCODE_H
