#include "game/types.h"

struct HkAlloc_0107e140 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Free(void* p, int size, int tag);
};

extern HkAlloc_0107e140* gHkAlloc_016e4178;

struct HkPtrMap_0107e140 {
    void* mpData;     // +0x00
    uint32_t mSize;   // +0x04
    int32_t mHashMod; // +0x08

    // @ 0x0107e140
    void FreeTable();
};

// @ 0x0107e140
void HkPtrMap_0107e140::FreeTable()
{
    gHkAlloc_016e4178->Free(mpData, (mHashMod + 1) * 16, 0x14);
}
