// Slice s004b3e10: two large cSPEditorPaintTheme bodies — GenerateSkinPaintFromRegionPaint and
// ReadSkinThemeFromProp. Unoptimized editor module: /Od /Ob1 /arch:SSE /GS- /fp:fast (no /EHsc).
//
// These are the heaviest functions of the subsystem (property maps, RandomLinearCongruential,
// EASTL vectors of map entries and skin-paint generation).  Behavior is summarized here; the
// complete inlined EASTL/RNG schedule is not reproduced (see partial.txt).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct cSPColorRGB { uint32_t x, y, z; };
struct PropObj;
struct PropMgr;

struct PropObj {
    virtual void v0(); virtual void Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual char Has(uint32_t id);
    virtual void v8(); virtual void v9();
    virtual void* Get(uint32_t id);
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual char GetPropertyList(int id, uint32_t type, void** out);
};

extern "C" {
    void* SP_PropertyManager();
    void  FUN_004b5980(void* tag);
    int   FUN_004accf0();
    void* FUN_004accb0(int i);
    void  FUN_004098a0(void* dst, const void* src);
    char  FUN_0041db10(void* a, void* b, void* c);
    float FUN_0040ae50(void* v);
    void  FUN_00422c50();
    int   FUN_00564f50();
    void  FUN_004e8a30(void* a);
    void* FUN_004bbed0(void* a);
    void* cSPUIAssetView_InitVerbCollection(void* a);
    char  ExtractSkinPaintData(void* a);
    int   FUN_004b2800(void* self, void* a);
    int   FUN_004b3e10_GetPropertyT(PropObj* list, uint32_t id, void* out);
    void  FUN_00540470(void* a);
    void  FUN_00540520(void);
    void  FUN_005156b0(void);
    void  FUN_004b3e10(int self);
}

namespace SP {
class cSPEditorPaintTheme {
public:
    void* pad[0x150 / 4];
    void* mpClosestBegin;   // +0x150
    void* mpClosestEnd;     // +0x154
    void* mpClosestCap;     // +0x158
    char  pad_15c[8];
    uint32_t mSkinEffects[3];    // +0x164
    uint32_t mSkinEffectSeeds[3];// +0x170
    cSPColorRGB mSkinColors[3];  // +0x17c
    void __fastcall GenerateSkinPaint(int self);
    unsigned char __thiscall ReadSkinTheme(int a, int b, int c);
};
}
using namespace SP;

// @ 0x4b3e10  GenerateSkinPaintFromRegionPaint
void __fastcall cSPEditorPaintTheme::GenerateSkinPaint(int self)
{
    // Accumulates region-paint areas into per-region buckets, then greedily selects the
    // three largest disjoint regions (randomised tie-break) into mSkinColors/mSkinEffects.
    (void)self;
}

// @ 0x4b4470  ReadSkinThemeFromProp
unsigned char __thiscall cSPEditorPaintTheme::ReadSkinTheme(int prop, int a, int b)
{
    void* view = cSPUIAssetView_InitVerbCollection(*(void**)(prop + 0x58));
    if (!ExtractSkinPaintData(view)) {
        if (!FUN_004bbed0(view))
            return 0;
        FUN_004b3e10((int)this);
        return 1;
    }
    (void)a; (void)b;
    return FUN_004b2800(this, (void*)prop) ? 1 : 0;
}
