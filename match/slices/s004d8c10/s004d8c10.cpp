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

    void Update(void* p, bool flag);   // 0x004d8c10

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
// Shared 0x4d8c10 updater: remaps each profile list's entries through a table
// built from the source vector, guarded by a one-shot flag byte.
// ---------------------------------------------------------------------------
// @ 0x004D8C10
void SpeciesProfile::Update(void* p, bool flag)
{
    // /Od lays locals out by a hash of their NAMES (declaration order only breaks
    // ties within a hash bucket), so these cryptic names are chosen to reproduce
    // the original 0x4d8c10 frame exactly. Each is documented by its role.
    bool* p30 = flag ? (bool*)((char*)this + 0x80d) : (bool*)((char*)this + 0x80c);  // pFlag
    if (!*p30) {
        int p18[255] = { 0 };     // map
        int** p4;                 // lists
        unsigned n31 = 0;         // i
        int p34;                  // count
        int* p37;                 // pRoot (outer)
        int* p21;                 // pData (outer)
        int* p25;                 // pRange
        int* p40;                 // pRoot (loop)
        int* p33;                 // pData (loop)
        int  p20;                 // entry
        int* p7[3];               // listsB
        int* n40[4];              // listsA
        unsigned p39;             // j
        int* p32;                 // list
        int  p38;                 // n
        unsigned p14;             // k
        int  p35;                 // t

        p37 = *(int**)((char*)p + 0x17c);
        p21 = (int*)*p37;
        p25 = (int*)((char*)p21 + 0x384);
        p34 = (p25[1] - p25[0]) / 0x468;
        for (; n31 < p34; ++n31) {
            p40 = *(int**)((char*)p + 0x17c);
            p33 = (int*)*p40;
            p20 = *(int*)((char*)p33 + 0x384) + n31 * 0x468;
            if (*(unsigned*)(p20 + 0x21c) < 0xff)
                p18[*(int*)(p20 + 0x21c)] = n31;
        }

        n40[0] = (int*)((char*)this + 0x810);
        n40[1] = (int*)((char*)this + 0x878);
        n40[2] = (int*)((char*)this + 0x8e0);
        n40[3] = 0;
        p7[0] = (int*)((char*)this + 0x948);
        p7[1] = (int*)((char*)this + 0x9b0);
        p7[2] = 0;
        p4 = flag ? p7 : n40;

        p39 = 0;
        for (; p4[p39] != 0; ++p39) {
            p32 = p4[p39];
            p14 = 0;
            p38 = (p32[1] - p32[0]) >> 2;
            for (; p14 < p38; ++p14) {
                p35 = ((int*)p32[0])[p14];
                ((int*)p32[0])[p14] = p18[p35];
            }
        }
        *p30 = 1;
    }
}

// ---------------------------------------------------------------------------
// SP::cSpeciesProfile::FillInProfileValues (0x4d90a0)
// ---------------------------------------------------------------------------
// EA::Variant / SP::cPropertyList view (slot 9 = GetProperty(uint32_t, Variant const**)).
struct IPropValue {
    char pad0[0x10];
    unsigned short mFlags;             // +0x10
    unsigned short mType;              // +0x12
    float* GetFloatValue();            // 0x004E4230
};
struct IProfileSource {
    virtual int v00(); virtual int v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual bool HasProperty(uint32_t id);
    virtual void v08();
    virtual bool GetProp(uint32_t id, IPropValue*& out);   // vtable +0x24
};

// Untyped read with a default (the module's shared inline helper).
inline float GetFloatValue(IProfileSource* pList, uint32_t id, float defaultValue)
{
    float bValue;
    (void)bValue;
    IPropValue* prop;
    if (pList && pList->GetProp(id, prop))
        return *prop->GetFloatValue();
    return defaultValue;
}

namespace SP {
struct cSpeciesProfile {
    char pad0[0x548];
    float mJumping;             // +0x548
    float mGliding;             // +0x54c
    float mFlapping;            // +0x550
    char pad554[0x5c8 - 0x554];
    int   mStealthRecharge;     // +0x5c8
    float mSprintRecharge;      // +0x5cc
    int   m5d0;                 // +0x5d0
    char pad5d4[0x63c - 0x5d4];
    float m63c;                 // +0x63c
    char pad640[0x6b0 - 0x640];
    float m6b0;                 // +0x6b0

    bool FillInProfileValues(void* p, IProfileSource* src);   // 0x004d90a0
};
}

// @ 0x004D90A0
bool SP::cSpeciesProfile::FillInProfileValues(void* p, IProfileSource* src)
{
    float v33, n40, len;
    v33 = GetFloatValue(src, 0x2cc9739, 0.0f);
    this->mJumping = this->mJumping + v33;
    n40 = GetFloatValue(src, 0x2cc974a, 0.0f);
    this->mGliding = this->mGliding + n40;
    len = GetFloatValue(src, 0x2cccf5c, 0.0f);
    this->mFlapping = this->mFlapping + len;

    switch (*(int*)((char*)p + 8)) {
    case 0x27:
    case 0x50:
        this->mStealthRecharge = (uint32_t)(*(float*)((char*)p + 0xa0) * 1000.0f);
        this->mSprintRecharge = (*(float*)((char*)p + 0xa4) > 0.0f)
                                    ? (*(float*)((char*)p + 0xa0) / *(float*)((char*)p + 0xa4)) : 1.0f;
        this->m6b0 = *(float*)((char*)p + 0x104);
        this->m5d0 = *(int*)((char*)p + 0x108);
        break;
    case 0x2c:
        this->m63c = *(float*)((char*)p + 0x3c);
        break;
    }
    return 1;
}
