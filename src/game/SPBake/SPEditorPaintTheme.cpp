// src/game/SPBake/SPEditorPaintTheme.cpp -- migrated from slice(s) s004bafc0, s004ba150, s004b4930, s004b33e0, s004b2320 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorPaintTheme.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorPaintTheme.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include "cSPBoundingBox.h"
#include "cSPTransform.h"

// ---- items of slice s004b2320 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct cSPColorRGB_s004b_2320 { uint32_t x, y, z; };
struct Asset {
    char b[0x800];
    void     GetColor(int i, cSPColorRGB_s004b_2320* out);      // 0x004adca0
    uint32_t GetEffect(int i);                        // 0x004adc60
    uint32_t GetSeed(int i);                          // 0x004adc80
    void     SetColor(int i, cSPColorRGB_s004b_2320* c);         // 0x004add30
    void     SetEffect(int i, uint32_t v);            // 0x004adcf0
    void     SetSeed(int i, uint32_t v);              // 0x004add10
    void     BeginWrite();                            // 0x004ae250
    int      ModelCount();                            // 0x004accf0
    void*    ModelAt(int i);                          // 0x004accb0
};
namespace SP {
struct PaintVector {
    void* mpBegin;          // +0
    void* mpEnd;            // +4
    void* mpCap;            // +8
    char  mInline[0x110];   // +0xc .. +0x11c
    void  Ctor();                             // 0x0041d050
    void* Erase(void* first, void* last);     // 0x004b5570
    void* Insert(void* value);                // 0x00454420
    void  Clear() { Erase(mpBegin, mpEnd); }
};
}
namespace SP {
struct ModelTree {
    char _[0x1c];
    void Ctor(void* tag);       // 0x004b5980
    void Reset();               // 0x004b5030
    void ResetFast();           // 0x004b5a20
    void Nuke(void* node);      // 0x004b5a60
};
}
namespace SP {
class cSPEditorPaintTheme_s004b_2320 {
public:
    void* mpVtbl0;              // +0x00
    void* mpVtbl1;              // +0x04
    int   mRefCount;            // +0x08
    PaintVector mPropTheme;     // +0x0c
    ModelTree   mModelTheme;    // +0x128
    uint32_t mPropThemeID;      // +0x144
    uint32_t mSourceRef;        // +0x148
    uint32_t mResourceType;     // +0x14c
    void* mpClosestBegin;       // +0x150
    void* mpClosestEnd;         // +0x154
    void* mpClosestCap;         // +0x158
    char  pad_15c[8];           // +0x15c
    uint32_t mSkinEffects[3];   // +0x164
    uint32_t mSkinEffectSeeds[3]; // +0x170
    cSPColorRGB_s004b_2320 mSkinColors[3]; // +0x17c

    cSPEditorPaintTheme_s004b_2320();
    ~cSPEditorPaintTheme_s004b_2320();
    void* AsInterface(int type);  // 0x004b26a0 (SP::cSPEditorPaintTheme::AsInterface)
    void  SetSource(int source);
    void  Reset();
    void  Reset2();
    uint32_t ReadFromAsset(Asset* asset);
    uint32_t ReadFromProp2(int prop, char useColors);
    uint32_t ReadFromProp(int prop);
    void  WriteToProp(Asset* asset, int resourceType);
    void  ApplyToAsset(int asset, int view);
    void  Apply(int a, int b, int c, int d);  // 0x004b31d0 (SP::cSPEditorPaintTheme::Apply)
    void  InitClosestRegions(void* a, void* b);  // 0x004b3730 (SP::cSPEditorPaintTheme::InitClosestRegions)
};
}
// ---- items of slice s004b2320 end

// ---- items of slice s004b4930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl InitVerbCollection(void* a);    // 0x4bb860
extern "C" bool __cdecl IsRegionless(void* verbs);       // 0x4bbed0
extern "C" bool __cdecl ExtractSkinPaintData(void* verbs);   // 0x4bbe90
struct RefObj { virtual void v0(); virtual void v1(); virtual void v2(); };
struct Tree {
    int   pad0;       // +0
    char* mpHead1;    // +4
    char* mpHead2;    // +8
    int   mpRoot;     // +c
    char  f10;        // +10
    int   x14;        // +14
    void  Nuke(int node);
    void  Reset();          // 0x4b5030
    void  ResetFast();      // 0x4b5a20
};
struct C70 {
    RefObj* mp;
    void Release();        // 0x4b4f70
};
struct Rec11c {
    char pad[0x118]; char f118;
    void FUN_004b62a0(Rec11c* src);   // 0x004b62a0
};
struct RecVec11c {
    Rec11c* mpBegin; Rec11c* mpEnd; Rec11c* mpCap;
    void FUN_004b4fa0(Rec11c* a);
    void FUN_004b5690(Rec11c* pos, Rec11c* a);   // 0x004b5690
};
struct PaintVec3 { float x, y, z; };
struct PaintEntry           // tSPEditorPaint (0x1c bytes)
{
    uint32_t mPaint;        // +0
    PaintVec3 mColor1;      // +4
    PaintVec3 mColor2;      // +0x10
    PaintEntry();           // 0x440f60
};
struct PaintEntryMap { PaintEntry& operator[](const int& k); };   // 0x454420 (eastl::map<int,tSPEditorPaint>::operator[])
struct VAlloc { };
struct VSet               // SP::SimpleVector<unsigned> / vector of pointers
{
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    VSet(const VAlloc&);                 // 0x540470
    ~VSet() { for (uint32_t* p = mpBegin; p < mpEnd; ++p) {} Free(); }
    void Free();                         // 0x425990
    void push_back(const uint32_t& v);   // 0x454860
};
struct PropList { virtual void AddRef(); virtual void Release(); };
struct PropListRef
{
    PropList* mp;
    PropListRef() : mp(0) {}
    PropListRef(PropList* p) : mp(p) { if (mp) mp->AddRef(); }
    ~PropListRef() { if (mp) mp->Release(); }   // 0x4a9b10 out-of-line copy
    void** AsPPVoidParam();              // 0x41d870
};
struct PropListVec
{
    PropListRef** mpBegin;
    PropListRef** mpEnd;
    PropListRef** mpCap;
    PropListVec(const VAlloc&);             // 0x540470
    ~PropListVec() { DestroyRange(mpBegin, mpEnd); Free(); }
    void DestroyRange(PropListRef** f, PropListRef** l);   // 0x4b5fb0
    void Free();                            // 0x425990
    void push_back(const PropListRef& r);   // 0x4b54b0
};
struct PropReqBits
{
    uint32_t a : 8;
    uint32_t b : 8;
    uint32_t c : 8;
    uint32_t d : 6;
    uint32_t e : 2;
    PropReqBits(uint32_t cc, uint32_t bb) { *(uint32_t*)this = 0; e = 1; c = cc; b = bb; }
};
struct PropManager { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                     virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
                     virtual void v10(); virtual void GetPropertyList(uint32_t id, PropReqBits req, void** out); };
extern PropManager* __cdecl GetPropManager();    // 0x67de30 (SP::PropertyManager)
struct PalItem { char pad[0xc]; PaintVec3 key; uint32_t pad2[3]; uint32_t type; };   // type at +0x24
struct PalCursor                                  // cSPPaletteCursor (0x20 bytes, refcounted)
{
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[7];
    PalCursor();                                   // 0x5c7b80
    void SetPalette(void* pal);                    // 0x5c7bc0
    PalItem* First(int, int, int, int);            // 0x5c7e80
    PalItem* Next(int, int, int, int);             // 0x5c7e20
    void Finish();                                 // 0xc2e4e0
};
struct PalCursorRef
{
    PalCursor* mp;
    PalCursorRef(PalCursor* p) : mp(p) { if (mp) mp->AddRef(); }
    ~PalCursorRef() { if (mp) mp->Release(); }
    PalCursor* operator->() const { return mp; }
};
struct AssetView
{
    char pad[0x58];
    void* verbs;
    void* GetVerbs() { return verbs; }
    PaintVec3 GetVertex(uint32_t i);   // 0x4adca0 (outline vertices at +0xa4)
};
struct Rng
{
    char st[8];
    Rng() { SetSeed(0xffffffff); }
    void SetSeed(uint32_t seed);                   // 0x936090
    uint32_t RandomUint32Uniform(uint32_t n);      // 0xa68fb0
};
extern "C" char __cdecl GetPropertyAsBoolArray(PropList* l, uint32_t id, int* count, uint8_t** arr);   // 0x6a0760
void* operator new(size_t, const char*, int, int, int, int);   // 0xf473a0
struct PaintTheme
{
    char pad0[0xc];
    PaintEntryMap mRegions;          // +0xc
    char pad1[0x148 - 0xc - 1];
    uint32_t mThemeId;               // +0x148
    bool ReadFromAsset(AssetView* a);                         // 0x4b2800
    bool ExtractRegionPaintData(AssetView* asset, void* palette, uint32_t seed);   // 0x4b4930
};
// ---- items of slice s004b4930 end

// ---- items of slice s004ba150 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    float& operator[](int i) { return (&x)[i]; }
};
}
namespace SP {
struct Matrix3 {
    Vector3 m[3];
    Vector3& operator[](int i) { return m[i]; }
};
}
namespace SP {
Matrix3 operator*(const Matrix3& a, const Matrix3& b);                               // 0x0041de20
}
// ---- items of slice s004ba150 end

// @ 0x004b26a0
void* SP::cSPEditorPaintTheme_s004b_2320::AsInterface(int type)
{
    switch (type) {
    case 0x31ec923: return this;
    case (int)0xee3f516e: return this;
    default: return 0;
    }
}





// @ 0x004b26e0
void SP::cSPEditorPaintTheme_s004b_2320::SetSource(int source)
{
    mSourceRef = source;
    Reset();
}





// @ 0x004b27c0
void SP::cSPEditorPaintTheme_s004b_2320::Reset2()
{
    ScratchSlots<6>();
    mModelTheme.Reset();
    mPropTheme.Clear();
}





// @ 0x004b3190
void SP::cSPEditorPaintTheme_s004b_2320::ApplyToAsset(int p, int x)
{
    if (p != 0) {
        int b18 = *(int*)(p + 0x18);
        int a10 = *(int*)(p + 0x10);
        Apply(a10, b18, x, p);
    }
}




// @ 0x004b33e0
int FUN_004b33e0(int* out, int* range, int key)
{
    (void)out; (void)range; (void)key;
    return 0;
}




// @ 0x004b3660
int FUN_004b3660(int self, int* out, int key)
{
    (void)self; (void)out; (void)key;
    return 0;
}



// @ 0x004b4930
bool PaintTheme::ExtractRegionPaintData(AssetView* asset, void* palette, uint32_t seed)
{
    void* verbs = InitVerbCollection(asset->GetVerbs());
    if (IsRegionless(verbs))
        return ReadFromAsset(asset);
    if (!ExtractSkinPaintData(verbs))
        return false;

    VAlloc a1;
    VSet effects(a1);
    if (mThemeId == 0x2399be55) {
        uint32_t k0 = 0xc862f28f; effects.push_back(k0);
        uint32_t k1 = 0x3a53cb54; effects.push_back(k1);
        uint32_t k2 = 0xb833bbda; effects.push_back(k2);
    } else if (mThemeId == 0x24682294 || mThemeId == 0x476a98c7) {
        uint32_t k0 = 0xa294caf0; effects.push_back(k0);
        uint32_t k1 = 0xb12297cf; effects.push_back(k1);
        uint32_t k2 = 0x4b7b4536; effects.push_back(k2);
    }

    VAlloc a2;
    PropListVec props(a2);
    for (uint32_t i = 0; i < (uint32_t)(effects.mpEnd - effects.mpBegin); ++i) {
        PropListRef list;
        PropManager* mgr = GetPropManager();
        void** pp = list.AsPPVoidParam();
        PropReqBits req(0x6a, 0x6f);
        mgr->GetPropertyList(effects.mpBegin[i], req, pp);
        if (list.mp)
            props.push_back(list);
    }

    Rng rng;
    rng.SetSeed(seed);

    VAlloc a3;
    VSet colors(a3);
    PalCursorRef cursor(new("Editor", 0, 0, 0, 0) PalCursor());
    if (!cursor.mp)
        return false;

    cursor.mp->SetPalette(palette);
    for (PalItem* item = cursor->First(0, 0, 0, 0); item; item = cursor->Next(0, 0, 0, 0)) {
        if (item->type == 0xbd110a25) {
            PaintVec3 key = item->key;
            colors.push_back(*(uint32_t*)&key);
        }
    }
    cursor.mp->Finish();

    int nColors = (int)(colors.mpEnd - colors.mpBegin);
    for (uint32_t j = 0; j < (uint32_t)(props.mpEnd - props.mpBegin); ++j) {
        const PaintVec3& pa = asset->GetVertex(j);
        uint32_t next = (j + 1) % (uint32_t)(props.mpEnd - props.mpBegin);
        const PaintVec3& pb = asset->GetVertex(next);
        uint32_t pick = 0;
        if (nColors != 0)
            pick = colors.mpBegin[rng.RandomUint32Uniform(nColors)];
        PropListRef pl(props.mpBegin[j]->mp);
        uint8_t* flags = 0;
        int cnt = 0;
        GetPropertyAsBoolArray(pl.mp, 0xf21a7bdc, &cnt, &flags);
        for (int k = 0; k < cnt; ++k) {
            if (flags[k] == 1) {
                PaintEntry e;
                e.mPaint = pick;
                e.mColor1 = pb;
                e.mColor2 = pa;
                mRegions[k] = e;
            }
        }
    }
    return true;
}



// @ 0x004b4f70
void C70::Release()
{
    if (mp != 0)
        mp->v2();
}



// @ 0x004b4fa0
void RecVec11c::FUN_004b4fa0(Rec11c* a)
{
    if (mpEnd < mpCap) {
        Rec11c* old = mpEnd;
        mpEnd = (Rec11c*)((char*)mpEnd + 0x11c);
        if (old != 0) {
            old->FUN_004b62a0(a);
            old->f118 = a->f118;
        }
    } else {
        FUN_004b5690(mpEnd, a);
    }
}



// @ 0x004b5030
void Tree::Reset()
{
    Nuke(mpRoot);
    mpHead1 = (char*)this + 4;
    mpHead2 = (char*)this + 4;
    mpRoot = 0;
    f10 = 0;
    x14 = 0;
}



// @ 0x004b5080
int __fastcall FUN_004b5080(void* self, uint32_t* key)
{
    (void)self; (void)key;
    return 0;
}


// @ 0x004badd0
int FUN_004badd0(void* self, int* a, void* b)
{
    (void)self; (void)a; (void)b;
    return 0;
}

// @ 0x004bbe90
bool FUN_004bbe90(uint32_t type)
{
    switch (type) {
    case 0x2b978c46:
    case 0x3d97a8e4:
    case 0x438f6347:
        return true;
    default:
        return false;
    }
}
