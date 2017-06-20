#include <string.h>
#include <iostream>
#include "variant_encode.h"

using namespace std;

int main(int argc, char *argv[])
{
    unsigned char buffer[BIT64_MAX_BYTES] = { 0 };
//    for (int16_t i = INT16_MIN; i != INT16_MAX; ++i)
//    {
//        i16_encode(i, buffer);
//        if (i16_decode(buffer, NULL) != i)
//        {
//            std::cerr << "i16" << i << " != " << i16_decode(buffer, NULL) << std::endl;
//        }
//    }
//    i16_encode(INT16_MAX, buffer);
//    if (INT16_MAX != i16_decode(buffer, NULL)) {
//        std::cerr << INT16_MAX << " != " << i16_decode(buffer, NULL) << std::endl;
//    }
//    for (uint16_t i = 0; i != UINT16_MAX; ++i)
//    {
//        u16_encode(i, buffer);
//        if (u16_decode(buffer, NULL) != i) {
//            std::cerr << "u16" << i << " != " << u16_decode(buffer, NULL) << std::endl;
//        }
//    }
//    for (uint32_t i = 65536; i != UINT32_MAX; ++i) {
//        u32_encode(i, buffer);
//        if (u32_decode(buffer, NULL) != i) {
//            std::cerr << "u32 " << i << " != " << u32_decode(buffer, NULL) << std::endl;
//            break;
//        }
//    }
    //for (int32_t i = INT32_MIN; i != INT32_MAX; ++i) {
    //    i32_encode(i, buffer);
    //    if (i32_decode(buffer, NULL) != i) {
    //        std::cerr << "i32 " << i << " != " << i32_decode(buffer, NULL) << std::endl;
    //        break;
    //    }
    //}

    //i32_encode(INT32_MAX, buffer);
    //if (INT32_MAX != i32_decode(buffer, NULL)) {
    //    std::cerr << "INT32_MAX: " << i32_decode(buffer, NULL) << std::endl;
    //}

    //int32_t i = 4096;

    //i32_encode(4096, buffer);
    //std::cout << i32_decode(buffer, NULL) << std::endl;

    uint64_t u64_test[] = {
        UBIT7_MAX - 1,
        UBIT7_MAX,
        UBIT7_MAX + 1,
        UBIT14_MAX - 1,
        UBIT14_MAX,
        UBIT14_MAX + 1,
        UBIT21_MAX - 1,
        UBIT21_MAX,
        UBIT21_MAX + 1,
        UBIT28_MAX - 1,
        UBIT28_MAX,
        UBIT28_MAX + 1,
        UBIT35_MAX - 1,
        UBIT35_MAX,
        UBIT35_MAX + 1,
        UBIT42_MAX - 1,
        UBIT42_MAX,
        UBIT42_MAX + 1,
        UBIT49_MAX - 1,
        UBIT49_MAX,
        UBIT49_MAX + 1,
        UBIT56_MAX - 1,
        UBIT56_MAX,
        UBIT56_MAX + 1,
        UBIT64_MAX - 1,
        UBIT64_MAX
    };

    for (int j = 0; j < sizeof(u64_test) / sizeof(uint64_t); ++j) {
        uint64_t i = u64_test[j];
        u64_encode(i, buffer);
        if (i != u64_decode(buffer, NULL)) {
            std::cerr << "u64 " << i << " != " << u64_decode(buffer, NULL) << std::endl;
        }
    }

    int64_t i64_test[] = {
        BIT7_MIN,
        BIT7_MAX,
        BIT14_MIN,
        BIT14_MAX,
        BIT21_MIN,
        BIT21_MAX,
        BIT28_MIN,
        BIT28_MAX,
        BIT35_MIN,
        BIT35_MAX,
        BIT42_MIN,
        BIT42_MAX,
        BIT49_MIN,
        BIT49_MAX,
        BIT56_MIN,
        BIT56_MAX,
        BIT64_MIN,
        BIT64_MAX
    };
    for (int j = 0; j < sizeof(i64_test) / sizeof(int64_t); ++j) {
        int64_t i = i64_test[j];
        i64_encode(i, buffer);
        if (i != i64_decode(buffer, NULL)) {
            std::cerr << "i64 " << i << " != " << i64_decode(buffer, NULL) << std::endl;
        }
    }

    union f_to_uc4 {
        float         f;
        unsigned char c[4];
    };
    f_to_uc4 ftu;
    ftu.f = 1.0f;

    union i32 {
        int32_t i;
        unsigned char cc[4];
    };
    i32 k;
    for (int j = 0; j < 100; ++j) {
        ftu.f = j;
        for (int i = 0; i < 4; ++i) {
            k.cc[3 - i] = ftu.c[i];
        }
        std::cout << i32_encode(k.i, buffer) << std::endl;
    }

    return 0;
}
