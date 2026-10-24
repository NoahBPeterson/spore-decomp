// Slice s00cd6680 - SporeApp 0x00cd6680..0x00cd7530
// SP::cTribeModeStrategy posse-vector helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: the remaining slice VAs were not reconstructed in this pass and are
// recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
void __cdecl operator_delete_array(void* p);   // 0x00f47380

// eastl::basic_string<wchar_t>
struct cWString {
    void* mpBegin;                 // 0x00
    void* mpEnd;                   // 0x04
    void* mpCap;                   // 0x08
    u8    mPad00c[0x10 - 0x0c];

    void  assign(const void* first, const void* last);  // 0x00423650
};

// SP::cTribeModeStrategy::cPosseInfo
struct cPosseInfo {
    cWString mName;                // 0x00
    float    mField10;             // 0x10
    int      mField14;             // 0x14
    int      mField18;             // 0x18
};

// ---------------------------------------------------------------------------------------------
// Vector helpers
// ---------------------------------------------------------------------------------------------
// @ 0x00cd6fd0
// Destroys every element in [first, last).
void __stdcall DoDestroyValues(cPosseInfo* first, cPosseInfo* last)
{
    for (; first < last; ++first) {
        u8* p = (u8*)first->mName.mpBegin;
        int cap = (int)first->mName.mpCap;
        if (((cap - (int)p) & -2) > 2 && p != 0)
            operator_delete_array(p);
    }
}

// @ 0x00cd6710
// Moves [first, last) into dst, destroying the source elements as it goes.
cPosseInfo* DestroyRange(cPosseInfo* first, cPosseInfo* last, cPosseInfo* dst)
{
    while (first != last) {
        u8* p = (u8*)first->mName.mpBegin;
        int cap = (int)first->mName.mpCap;
        if (((cap - (int)p) & -2) > 2 && p != 0)
            operator_delete_array(p);
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00cd6760
// Copies [first, last) forward into dst; dst elements are reused.
cPosseInfo* CopyRange(cPosseInfo* first, cPosseInfo* last, cPosseInfo* dst)
{
    while (first != last) {
        if (first != dst)
            dst->mName.assign(first->mName.mpBegin, first->mName.mpEnd);
        dst->mField10 = first->mField10;
        dst->mField14 = first->mField14;
        dst->mField18 = first->mField18;
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00cd67b0
// Copies [first, last) backward into dst; dst elements are reused.
cPosseInfo* CopyRangeBackward(cPosseInfo* first, cPosseInfo* last, cPosseInfo* dst)
{
    while (last != first) {
        --last;
        --dst;
        if (last != dst)
            dst->mName.assign(last->mName.mpBegin, last->mName.mpEnd);
        dst->mField10 = last->mField10;
        dst->mField14 = last->mField14;
        dst->mField18 = last->mField18;
    }
    return dst;
}
