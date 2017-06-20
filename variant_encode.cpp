#include "variant_encode.h"

#define IS_FINAL_UCHAR(c) (!(c >> 7))

union b16_to_uc2 {
    uint16_t      u16;
    int16_t       i16;
    unsigned char c[2];
};

union b32_to_uc4 {
    uint32_t      u32;
    int32_t       i32;
    unsigned char c[4];
};

union b64_to_uc8 {
    uint64_t      u64;
    int64_t       i64;
    unsigned char c[8];
};

size_t u16_encode(uint16_t var, unsigned char buffer[])
{
    b16_to_uc2 btu;
    btu.u16 = var;
    if (var <= UBIT7_MAX) {
        buffer[0] = btu.c[0];
        return 1;
    }
    else if (var <= UBIT14_MAX) {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[0] >> 7) | (btu.c[1] << 1);
        return 2;
    }
    else {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[0] >> 7) | (btu.c[1] << 1) | (1 << 7);
        buffer[2] = (btu.c[1] >> 6);
        return 3;
    }
}

uint16_t u16_decode(const unsigned char* buffer, size_t* nCh)
{
    b16_to_uc2 ret;
    ret.u16 = 0;

    if (IS_FINAL_UCHAR(buffer[0])) {
        ret.c[0] = buffer[0];
        if (nCh) {
            *nCh = 1;
        }
        return ret.u16;
    }
    else {
        ret.c[0] = ((buffer[0] & ~(1 << 7))) | (buffer[1] << 7);
    }
    if (IS_FINAL_UCHAR(buffer[1])) {
        ret.c[1] = buffer[1] >> 1;
        if (nCh) {
            *nCh = 2;
        }
        return ret.u16;
    }
    else {
        ret.c[1] = ((buffer[1] & ~(1 << 7)) >> 1) | (buffer[2] << 6);
    }
    if (nCh) {
        *nCh = 3;
    }
    return ret.u16;
}

size_t i16_encode(int16_t var, unsigned char buffer[])
{
    b16_to_uc2 itu;
    itu.i16 = var;

    if (var >= -64 && var <= 63) //! [-2^6, 2^6 - 1]
    {
        buffer[0] = *((unsigned char*)&var) & ~(1 << 7);
        return 1;
    }
    else if (var >= -8192 && var <= 8191) //! [-2^13, 2^13 - 1]
    {
        buffer[0] = itu.c[0] | (1 << 7);
        buffer[1] = ((itu.c[0] >> 7) | (itu.c[1] << 1)) & ~(1 << 7);
        return 2;
    }
    else //! [-2^15, 2^15 - 1]
    {
        buffer[0] = itu.c[0] | (1 << 7);
        buffer[1] = (itu.c[0] >> 7) | (itu.c[1] << 1) | (1 << 7);
        buffer[2] = (itu.c[1] >> 6);
        return 3;
    }
}

int16_t i16_decode(const unsigned char* buffer, size_t* nCh)
{
    b16_to_uc2 ret;
    ret.i16 = 0;
    if (IS_FINAL_UCHAR(buffer[0])) {
        if (buffer[0] & (1 << 6)) {
            ret.c[0] = buffer[0] | (1 << 7);
            ret.c[1] = ~0;
        }
        else {
            ret.c[0] = buffer[0];
        }
        if (nCh) {
            *nCh = 1;
        }
        return ret.i16;
    }
    else {
        ret.c[0] = (buffer[0] & ~(1 << 7)) | (buffer[1] << 7);
    }
    if (IS_FINAL_UCHAR(buffer[1])) {
        ret.c[1] = (buffer[1] & ~(1 << 7)) >> 1;
        if (ret.c[1] & (1 << 5)) {
            ret.c[1] |= (3 << 6);
        }
        if (nCh) {
            *nCh = 2;
        }
    }
    else {
        ret.c[1] = ((buffer[1] & ~(1 << 7)) >> 1) | (buffer[2] << 6);
        if (nCh) {
            *nCh = 3;
        }
    }
    return ret.i16;
}

size_t u32_encode(uint32_t var, unsigned char buffer[])
{
    b32_to_uc4 btu;
    btu.u32 = var;
    if (var <= UBIT7_MAX)
    {
        buffer[0] = btu.c[0];
        return 1;
    }
    else if (var <= UBIT14_MAX) {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[1] << 1) | (btu.c[0] >> 7);
        return 2;
    }
    else if (var <= UBIT21_MAX) {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[1] << 1) | (btu.c[0] >> 7) | (1 << 7);
        buffer[2] = (btu.c[2] << 2) | (btu.c[1] >> 6);
        return 3;
    }
    else if (var <= UBIT28_MAX) {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[1] << 1) | (btu.c[0] >> 7) | (1 << 7);
        buffer[2] = (btu.c[2] << 2) | (btu.c[1] >> 6) | (1 << 7);
        buffer[3] = (btu.c[3] << 3) | (btu.c[2] >> 5);
        return 4;
    }
    else {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[1] << 1) | (btu.c[0] >> 7) | (1 << 7);
        buffer[2] = (btu.c[2] << 2) | (btu.c[1] >> 6) | (1 << 7);
        buffer[3] = (btu.c[3] << 3) | (btu.c[2] >> 5) | (1 << 7);
        buffer[4] = (btu.c[4] << 4) | (btu.c[3] >> 4);
        return 5;
    }
}

uint32_t u32_decode(const unsigned char *buffer, size_t *nCh)
{
    b32_to_uc4 btu;
    btu.u32 = 0;
    if (IS_FINAL_UCHAR(buffer[0])) {
        btu.c[0] = buffer[0];
        if (nCh) {
            *nCh = 1;
        }
        return btu.u32;
    }
    if (IS_FINAL_UCHAR(buffer[1])) {
        btu.c[0] = (buffer[0] & ~(1 << 7)) | (buffer[1] << 7);
        btu.c[1] = buffer[1] >> 1;
        if (nCh) {
            *nCh = 2;
        }
        return btu.u32;
    }
    if (IS_FINAL_UCHAR(buffer[2])) {
        btu.c[0] = (buffer[0] & ~(1 << 7)) | (buffer[1] << 7);
        btu.c[1] = ((buffer[1] >> 1) & ~(3 << 6)) | (buffer[2] << 6);
        btu.c[2] = buffer[2] >> 2;
        if (nCh) {
            *nCh = 3;
        }
        return btu.u32;
    }
    if (IS_FINAL_UCHAR(buffer[3])) {
        btu.c[0] = (buffer[0] & ~(1 << 7)) | (buffer[1] << 7);
        btu.c[1] = ((buffer[1] >> 1) & ~(3 << 6)) | (buffer[2] << 6);
        btu.c[2] = ((buffer[2] >> 2) & ~(7 << 5)) | (buffer[3] << 5);
        btu.c[3] = buffer[3] >> 3;
        if (nCh) {
            *nCh = 4;
        }
        return btu.u32;
    }
    else {
        btu.c[0] = (buffer[0] & ~(1 << 7)) | (buffer[1] << 7);
        btu.c[1] = ((buffer[1] >> 1) & ~(3 << 6)) | (buffer[2] << 6);
        btu.c[2] = ((buffer[2] >> 2) & ~(7 << 5)) | (buffer[3] << 5);
        btu.c[3] = ((buffer[3] >> 3) & ~(15 << 4)) | (buffer[4] << 4);
        btu.c[4] = buffer[4] >> 4;
        if (nCh) {
            *nCh = 5;
        }
        return btu.u32;
    }
}


size_t i32_encode(int32_t var, unsigned char buffer[])
{
    b32_to_uc4 btu;
    btu.i32 = var;
    if (var >= BIT7_MIN && var <= BIT7_MAX) {
        buffer[0] = btu.c[0] & ~(1 << 7);
        return 1;
    }
    else if (var >= BIT14_MIN && var <= BIT14_MAX) {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[1] << 1) | (btu.c[0] >> 7) & ~(1 << 7);
        return 2;
    }
    else if (var >= BIT21_MIN && var <= BIT21_MAX) {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[1] << 1) | (btu.c[0] >> 7) | (1 << 7);
        buffer[2] = (btu.c[2] << 2) | (btu.c[1] >> 6) & ~(1 << 7);
        return 3;
    }
    else if (var >= BIT28_MIN && var <= BIT28_MAX) {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[1] << 1) | (btu.c[0] >> 7) | (1 << 7);
        buffer[2] = (btu.c[2] << 2) | (btu.c[1] >> 6) | (1 << 7);
        buffer[3] = (btu.c[3] << 3) | (btu.c[2] >> 5) & ~(1 << 7);
        return 4;
    }
    else
    {
        buffer[0] = btu.c[0] | (1 << 7);
        buffer[1] = (btu.c[1] << 1) | (btu.c[0] >> 7) | (1 << 7);
        buffer[2] = (btu.c[2] << 2) | (btu.c[1] >> 6) | (1 << 7);
        buffer[3] = (btu.c[3] << 3) | (btu.c[2] >> 5) | (1 << 7);
        buffer[4] = (btu.c[3] >> 4) & ~(1 << 7);
        return 5;
    }
}

int32_t i32_decode(unsigned char *buffer, size_t *nCh)
{
    b32_to_uc4 ret;
    ret.i32 = 0;
    if (IS_FINAL_UCHAR(buffer[0])) {
        if (buffer[0] & (1 << 6)) {
            ret.c[0] = buffer[0] | (1 << 7);
            ret.c[1] = ~0;
            ret.c[2] = ~0;
            ret.c[3] = ~0;
        }
        else {
            ret.c[0] = buffer[0];
        }
        if (nCh) {
            *nCh = 1;
        }
        return ret.i32;
    }
    else if (IS_FINAL_UCHAR(buffer[1])) {
        ret.c[0] = buffer[0] & ~(1 << 7) | (buffer[1] << 7);
        if (buffer[1] & (1 << 5)) {
            ret.c[1] = buffer[1] | (3 << 6);
            ret.c[2] = ~0;
            ret.c[3] = ~0;
        }
        else {
            ret.c[1] = buffer[1];
        }
        if (nCh) {
            *nCh = 2;
        }
        return ret.i32;
    }
    else if (IS_FINAL_UCHAR(buffer[2])) {
        ret.c[0] = buffer[0] & ~(1 << 7) | (buffer[1] << 7);
        ret.c[1] = buffer[1] & ~(3 << 6) | (buffer[2] << 6);
        if (buffer[2] & (1 << 4)) {
            ret.c[2] = buffer[2] | (7 << 5);
            ret.c[3] = ~0;
        }
        else {
            ret.c[2] = buffer[2];
        }
        if (nCh) {
            *nCh = 3;
        }
        return ret.i32;
    }
    else if (IS_FINAL_UCHAR(buffer[3])) {
        ret.c[0] = buffer[0] & ~(1 << 7) | (buffer[1] << 7);
        ret.c[1] = buffer[1] & ~(3 << 6) | (buffer[2] << 6);
        ret.c[2] = buffer[2] & ~(7 << 5) | (buffer[3] << 5);
        if (buffer[3] & (1 << 3)) {
            ret.c[3] = buffer[3] | (15 << 4);
        }
        else {
            ret.c[3] = buffer[3];
        }
        if (nCh) {
            *nCh = 4;
        }
        return ret.i32;
    }
    else {
        ret.c[0] = buffer[0] & ~(1 << 7) | (buffer[1] << 7);
        ret.c[1] = buffer[1] & ~(3 << 6) | (buffer[2] << 6);
        ret.c[2] = buffer[2] & ~(7 << 5) | (buffer[3] << 5);
        ret.c[3] = buffer[3] & ~(15 << 4) | (buffer[4] << 4);
        if (nCh) {
            *nCh = 5;
        }
        return ret.i32;
    }
}
