// Slice s00449ed0: /Od /Ob1 cSPEditorBlock helpers.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
// NOTE: only skeletons; see partial.txt.
#include "types.h"

struct Blk {
    char pad0[0x154];
    int mArr[3];        // +0x154
    char pad1[0x33c - 0x160];
    Blk* mParent;       // +0x33c

    void A49ed0();
    void A4a070();
    void A4a0e0();
    int A4a8c0();
    bool A4a9a0(Blk* other);
    int A4aa10(int i);
    void A4aaa0();
    void A4ad00();
};

// @ 0x00449ed0
void Blk::A49ed0()
{
}

// @ 0x0044a070
void Blk::A4a070()
{
}

// @ 0x0044a0e0
void Blk::A4a0e0()
{
}

// @ 0x0044a8c0
int Blk::A4a8c0()
{
    return 0;
}

// @ 0x0044a9a0
bool Blk::A4a9a0(Blk* other)
{
    int count = 0;
    while (other != 0 && other != this && count < 100) {
        other = other->mParent;
        count = count + 1;
    }
    if (count > 100)
        return false;
    return other == this;
}

// @ 0x0044aa10
int Blk::A4aa10(int i)
{
    if (i < 0 || i >= 3)
        return 0;
    int x = mArr[i];
    if (x == 0)
        return 0;
    return mArr[i];
}

// @ 0x0044aaa0
void Blk::A4aaa0()
{
}

// @ 0x0044ad00
void Blk::A4ad00()
{
}
