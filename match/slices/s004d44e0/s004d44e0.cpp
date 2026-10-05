// Slice s004d44e0: species database helpers (scale getter, id->index searches) and
// larger surrounding operations.  Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#pragma pack(push, 4)

struct SpeciesDB {
    char  pad0[0x5ac];
    float mScale;      // +0x5ac
    char  pad2[0x6d4 - 0x5b0];
    int   mVecBegin;   // +0x6d4
    int   mVecEnd;     // +0x6d8

    float GetScale();
    uint32_t FindField8(int id);
    uint32_t FindField10(int id);
};

// @ 0x004D46B0
float SpeciesDB::GetScale()
{
    return mScale * 0.025f * 100.0f;
}

// @ 0x004D46D0
uint32_t SpeciesDB::FindField8(int id)
{
    uint32_t i = 0;
    int* vec = (int*)((char*)this + 0x6d4);
    int n = (vec[1] - vec[0]) >> 2;
    for (; i < (uint32_t)n; i = i + 1) {
        int* slot = (int*)(mVecBegin + i * 4);
        int elem = *slot;
        if (*(int*)(elem + 8) == id)
            return i;
    }
    return 0xffffffff;
}

// @ 0x004D4750
uint32_t SpeciesDB::FindField10(int id)
{
    uint32_t i = 0;
    int* vec = (int*)((char*)this + 0x6d4);
    int n = (vec[1] - vec[0]) >> 2;
    for (; i < (uint32_t)n; i = i + 1) {
        int* slot = (int*)(mVecBegin + i * 4);
        int elem = *slot;
        if (*(int*)(elem + 0x10) == id)
            return i;
    }
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// Larger neighbours -> partial.txt
// ---------------------------------------------------------------------------
// @ 0x004D44E0
void SpeciesDB_Op1(void* self) { (void)self; }
// @ 0x004D47D0
void SpeciesDB_Op2(void* self) { (void)self; }
// @ 0x004D4AD0
void SpeciesDB_Op3(void* self) { (void)self; }
// @ 0x004D4F10
void SpeciesDB_Op4(void* self) { (void)self; }
