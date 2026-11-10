// Slice s00897f90: interpolate a float pair from a keyframe array.
// A 32-byte keyframe (bit flags + a float pair and a divisor at +0xc) and a
// parallel 8-byte tag array are indexed through a run table; the caller's vector
// receives the keyframe position, adjusted by the record's divisor.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int u32;

struct Key32 {
    u32   mBits;            // +0x00
    float mf04;             // +0x04
    float mf08;             // +0x08
    float mf0c;             // +0x0c
    unsigned char mPad10[0x10];
};

struct Rec8 {
    u32 mBits;              // +0x00
    u32 mPad04;             // +0x04
};

struct Layout {
    unsigned char mPad00[0x2c];
    short* mp2c;            // +0x2c
    short* mp30;            // +0x30
    unsigned char mPad34[0x40 - 0x34];
    Rec8*  mp40;            // +0x40
    unsigned char mPad44[0x54 - 0x44];
    Key32* mp54;            // +0x54
    Key32* mp58;            // +0x58
    unsigned char mPad5c[0x68 - 0x5c];
    int*   mp68;            // +0x68
    int*   mp6c;            // +0x6c

    void GetPair(int index, int firstOnly, float* out);
};

// @ 0x00897f90
void Layout::GetPair(int index, int firstOnly, float* out)
{
    out[0] = 0.0f;
    out[1] = 0.0f;

    int count = (int)(mp58 - mp54);
    if (count == 0)
        return;

    int idx;
    if (index < (int)(mp6c - mp68))
        idx = mp68[index];
    else
        idx = (int)(mp30 - mp2c);

    int flag = firstOnly;
    if (idx >= count) {
        idx = count - 1;
        flag = 1;
    }

    Key32* key = &mp54[idx];
    Rec8*  rec = &mp40[idx];
    Key32* p = key;
    if (flag == 1) {
        Key32* end = &mp54[count];
        Rec8*  r = rec + 1;
        p = key + 1;
        while (p < end && (r->mBits & 0xe0) != 0) {
            ++p;
            ++r;
        }
        --p;
    }

    out[0] = p->mf04;
    out[1] = p->mf08;

    if (flag == 1) {
        u32 bits = rec->mBits;
        u32 n = (bits >> 8) & 7;
        float scale = key->mf0c;
        if (n != 0 && (bits & 0x800) != 0)
            scale /= (float)n;
        out[0] += scale;
    }
}
