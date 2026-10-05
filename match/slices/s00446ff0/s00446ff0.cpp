// Slice s00446ff0: two /Od /Ob1 helpers in the SP::cSPEditorBlock region.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy /GS-
#include "types.h"

// @ 0x00446ff0  (byte-exact)
int* __fastcall Sub_446ff0(int* p)
{
    if ((*(unsigned short*)((char*)p + 0x10) & 0x30) != 0) {
        return (int*)*p;
    } else {
        if (*(unsigned short*)((char*)p + 0x12) != 0)
            return p;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00447030: build 0x20 scratch transform blocks, ask a model-world-like
// object to fill them, then apply each to the matching bound object.
// ---------------------------------------------------------------------------
struct cSPTransform {
    unsigned short mFlags;
    unsigned short mModificationCount;
    float mTranslation[3];
    float mScale;
    float mRotation[9];
    void Init();
};

struct Elem {                          // stride 0x5c
    unsigned int mPad0;
    cSPTransform mTransform;
    char mPad1[0x5c - 4 - 0x38];
};

struct Target {
    void Apply(void* block, unsigned char param2);
};

struct Binder {
    char pad0[0x10];
    int mArg;                          // +0x10
    char pad1[4];
    void* mWorld;                      // +0x18
    char pad2[0x6cc - 0x1c];
    Target** mTargets;                 // +0x6cc
    void Method(unsigned char param2);
};

// @ 0x00447030
void Binder::Method(unsigned char param2)
{
    Elem scratch[0x20];
    int n = 0x20;
    Elem* p = scratch;
    while (n = n - 1, -1 < n) {
        p->mTransform.Init();
        p = (Elem*)((char*)p + 0x5c);
    }
    void* obj = mWorld;
    int count = ((int(__thiscall*)(void*, int, void*, int))(
        *(void**)(*(char**)obj + 0xe8)))(obj, mArg, scratch, 0x20);
    for (int i = 0; i < count; i++)
        mTargets[i]->Apply(&scratch[i], param2);
}
