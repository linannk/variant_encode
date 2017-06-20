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
    for (int32_t i = INT32_MIN; i != INT32_MAX; ++i) {
        i32_encode(i, buffer);
        if (i32_decode(buffer, NULL) != i) {
            std::cerr << "i32 " << i << " != " << i32_decode(buffer, NULL) << std::endl;
            break;
        }
    }
    return 0;
}
