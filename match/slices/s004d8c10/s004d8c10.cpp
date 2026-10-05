// Slice s004d8c10: SP::cSpeciesProfile variant getters + the shared 0x4d8c10 updater.
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#pragma pack(push, 4)

struct SpeciesProfile {
    char pad0[0x17c];
    int* m17c;            // +0x17c (pointer whose target holds +0x31c)
    char pad2[0x518 - 0x180];
    int  mSelector;       // +0x518
    char pad3[0x9b4 - 0x51c];

    void Update(void* p, int flag);   // 0x004d8c10

    int GetVariantA(void* p);
    int GetVariantB(void* p);
    int GetVariantC(void* p);
};

// @ 0x004D8EE0
int SpeciesProfile::GetVariantA(void* p)
{
    Update(p, 0);
    return (int)((char*)this + 0x810);
}

// @ 0x004D8F10
int SpeciesProfile::GetVariantB(void* p)
{
    int* pOwner = *(int**)((char*)p + 0x17c);
    int* pData = (int*)*pOwner;
    bool b = *(int*)((char*)pData + 0x31c) == mSelector;
    Update(p, b);
    int result;
    if (b)
        result = (int)((char*)this + 0x948);
    else
        result = (int)((char*)this + 0x878);
    return result;
}

// @ 0x004D8F90
int SpeciesProfile::GetVariantC(void* p)
{
    int* pOwner = *(int**)((char*)p + 0x17c);
    int* pData = (int*)*pOwner;
    bool b = *(int*)((char*)pData + 0x31c) == mSelector;
    Update(p, b);
    int result;
    if (b)
        result = (int)((char*)this + 0x9b0);
    else
        result = (int)((char*)this + 0x8e0);
    return result;
}

// ---------------------------------------------------------------------------
// Larger neighbours -> partial.txt
// ---------------------------------------------------------------------------
// @ 0x004D8C10
void SpeciesProfile_Update(void* a, int b) { (void)a; (void)b; }
// @ 0x004D90A0
void cSpeciesProfile_FillInProfileValues(void* self) { (void)self; }
