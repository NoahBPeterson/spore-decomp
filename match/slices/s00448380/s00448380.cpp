// Slice s00448380: cSPEditorBlock / cSPBoundingBox-ish /Od /Ob1 helpers.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy /GS-
#include "types.h"

struct Item;
struct Key3 { int a, b, c; };

struct Blk {
    char pad0[0x10];
    int m10;                 // +0x10
    int m14;                 // +0x14
    int m18;                 // +0x18
    int m1c;                 // +0x1c
    int m20;                 // +0x20
    char pad1[0x6cc - 0x24];
    Item** mItems;           // +0x6cc
    Item** mItemsEnd;        // +0x6d0
    char pad2[0xdc8 - 0x6d4];
    unsigned mBits;          // +0xdc8

    float A8380();
    bool A8480(int index, char flag);
    bool A84f0();
    void A85d0();
    void A8690(int a, int b, int c, int d);
    void A88c0();
    void A8a80();
    void A8b10();
    void A8b80(char flag);
    bool A8c10();
    void A8d60();
    void A8dd0();
    void A8e90(void* v, char flag);
};

struct Item {
    bool Apply(char flag);
    void Method();
    bool Other(char flag);
    void Release();
};

void sub_458f60(int a, int b, Key3 key, int c);

// @ 0x00448380
float Blk::A8380()
{
    float a = (mBits /*placeholder*/ ? 1.0f : 0.6f);
    return a;
}

// @ 0x00448480
bool Blk::A8480(int index, char flag)
{
    bool result = false;
    if (-1 < index) {
        if (index < (int)(mItemsEnd - mItems)) {
            result = mItems[index]->Apply(flag);
        }
    }
    return result;
}

// @ 0x004484f0
bool Blk::A84f0()
{
    bool result = true;
    if ((mBits & 0x800) == 0) {
        for (int i = 0; i < (int)(mItemsEnd - mItems); i++) {
            bool r = A8480(i, 1);
            result = (result && r);
        }
    }
    return result;
}

// @ 0x004485d0
void Blk::A85d0()
{
    if ((mBits & 0x800) == 0) {
        for (int i = 0; i < (int)(mItemsEnd - mItems); i++)
            mItems[i]->Method();
    }
}

// @ 0x00448690
void Blk::A8690(int, int, int, int)
{
}

// @ 0x004488c0
void Blk::A88c0()
{
}

// @ 0x00448a80
void Blk::A8a80()
{
}

// @ 0x00448b10
void Blk::A8b10()
{
    Key3 key;
    key.a = m1c;
    key.b = 0;
    key.c = m20;
    sub_458f60(m10, m18, key, 1);
}

// @ 0x00448b80
void Blk::A8b80(char flag)
{
    int a = m10;
    if (flag != '\0')
        a = m14;
    Key3 key;
    key.a = m1c;
    key.b = 0;
    key.c = m20;
    sub_458f60(a, m18, key, 0);
}

// @ 0x00448c10
bool Blk::A8c10()
{
    return false;
}

// @ 0x00448d60
void Blk::A8d60()
{
}

// @ 0x00448dd0
void Blk::A8dd0()
{
}

// @ 0x00448e90
void Blk::A8e90(void*, char)
{
}
