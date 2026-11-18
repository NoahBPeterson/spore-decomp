// Slice s00ff1290 - SporeApp 0x00ff1290
// Range copy of 0x38-byte ornament records (same record as cOrnamentDataA in the
// s00ff11c0 slice): the destination is tested per element, so a null destination
// only skips the stores and the loop still walks the whole range.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

typedef unsigned char u8;

// 0x38-byte record with two flag bytes (see cOrnamentDataA::operator= at 0x00ff11c0).
// The three leading floats are copied through the record pointer itself; the rest of
// the record is a nested aggregate based at 0x0c.  That is what makes the inlined
// copy address the tail through a second base pair (record + 0x14) exactly as the
// retail loop does; a flat member list makes the compiler use one base pair.
struct cOrnamentTail {
    float mF0c;                    // 0x0c
    float mF10;                    // 0x10
    float mF14;                    // 0x14
    float mF18;                    // 0x18
    float mF1c;                    // 0x1c
    int   mField20;                // 0x20
    bool  mFlag24;                 // 0x24
    bool  mFlag25;                 // 0x25
    int   mField28;                // 0x28
    int   mField2c;                // 0x2c
    int   mField30;                // 0x30
    int   mField34;                // 0x34

    // Plain member-wise copy assignment (out of line at 0x00ff11c0); inlined here.
    cOrnamentTail& operator=(const cOrnamentTail& o)
    {
        mF0c = o.mF0c;
        mF10 = o.mF10;
        mF14 = o.mF14;
        mF18 = o.mF18;
        mF1c = o.mF1c;
        mField20 = o.mField20;
        mFlag24 = o.mFlag24;
        mFlag25 = o.mFlag25;
        mField28 = o.mField28;
        mField2c = o.mField2c;
        mField30 = o.mField30;
        mField34 = o.mField34;
        return *this;
    }
};

struct cOrnamentDataA {
    float mF00;                    // 0x00
    float mF04;                    // 0x04
    float mF08;                    // 0x08
    cOrnamentTail mTail;           // 0x0c

    // Member-wise copy assignment, same order as cOrnamentDataA::operator= at 0x00ff11c0.
    cOrnamentDataA& operator=(const cOrnamentDataA& o)
    {
        mF00 = o.mF00;
        mF04 = o.mF04;
        mF08 = o.mF08;
        mTail = o.mTail;
        return *this;
    }
};

// @ 0x00ff1290
cOrnamentDataA* CopyOrnamentRange(cOrnamentDataA* first, cOrnamentDataA* last, cOrnamentDataA* dest)
{
    while (first != last) {
        if (dest)
            *dest = *first;
        ++first;
        ++dest;
    }
    return dest;
}
