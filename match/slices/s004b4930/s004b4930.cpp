// Slice s004b4930: eastl container primitives (rbtree reset/nuke, vector erase/insert/push) plus
// the (huge) ExtractRegionPaintData. Unoptimized editor module: /Od /Ob1 /arch:SSE, no /EHsc.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

extern void* g_static1;   // 0x01667bac

extern "C" {
    void  FUN_00425990(void* vec);
    void  FUN_00455290(void* vec);
    void  FUN_0042dee0();
    void  FUN_004b62a0();
    void  FUN_004b6340();
    void  FUN_004b69d0();
    void  FUN_004b6450();
    void  FUN_004b64b0();
    void  FUN_004b66b0();
    void  FUN_004b6bf0();
    void  FUN_004b5690();
    void  FUN_004b5a60(void* node);
    void  operator_delete_(void* p);
}

// --- intrusive ref object / linked node -------------------------------------
struct RefObj { virtual void v0(); virtual void v1(); virtual void v2(); };

// --- generic rbtree-ish container (head at +4) ------------------------------
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

// @ 0x4b5030
void Tree::Reset()
{
    Nuke(mpRoot);
    mpHead1 = (char*)this + 4;
    mpHead2 = (char*)this + 4;
    mpRoot = 0;
    f10 = 0;
    x14 = 0;
}

// --- a 3-word vector with a static 1-element buffer -------------------------
struct C540 {
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void  Init();          // 0x4b5540
};
// @ 0x4b5540
void C540::Init()
{
    mpBegin = &g_static1;
    mpEnd = mpBegin;
    mpCap = (char*)mpBegin + 1;
}

// --- holder that releases a single intrusive object -------------------------
struct C70 {
    RefObj* mp;
    void Release();        // 0x4b4f70
};
// @ 0x4b4f70
void C70::Release()
{
    if (mp != 0)
        mp->v2();
}

// --- vector of intrusive pointers (Destroy = dtor loop) ---------------------
struct Vec544 {
    RefObj** mpBegin;
    RefObj** mpEnd;
    RefObj** mpCap;
    void Destroy();        // 0x4b5440
};
// @ 0x4b5440
void Vec544::Destroy()
{
    for (RefObj** p = mpBegin; p < mpEnd; p++) {
        if (*p != 0)
            (*p)->v1();
    }
    FUN_00425990(this);
}

// --- vector<T> with 0x20-byte elements --------------------------------------
struct Blk20 { uint32_t w[8]; };
struct Vec20 {
    Blk20* mpBegin;
    Blk20* mpEnd;
    Blk20* mpCap;
    Blk20* Erase(Blk20* first, Blk20* last);   // 0x4b5570
    void   PushBack(const Blk20& v);           // 0x4b54b0
};
// @ 0x4b5570
Blk20* Vec20::Erase(Blk20* first, Blk20* last)
{
    Blk20* dest = first;
    for (Blk20* src = last; src != mpEnd; ++src, ++dest)
        *dest = *src;
    mpEnd = (Blk20*)((char*)mpEnd + (((char*)last - (char*)first) >> 5) * -0x20);
    return first;
}

// @ 0x4b54b0
void Vec20::PushBack(const Blk20& v)
{
    if (mpEnd < mpCap) {
        *mpEnd = v;
        ++mpEnd;
    } else {
        extern void vec20_DoInsertValue(Vec20*, const Blk20&);
        vec20_DoInsertValue(this, v);
    }
}

// @ 0x4b4fa0
void FUN_004b4fa0(int* p, int a)
{
    if ((uint32_t)p[1] < (uint32_t)p[2]) {
        int old = p[1];
        p[1] = p[1] + 0x11c;
        if (old != 0) {
            FUN_004b62a0();
            *(char*)(old + 0x118) = *(char*)(a + 0x118);
        }
    } else {
        FUN_004b5690();
    }
}

// @ 0x4b5610
void __fastcall FUN_004b5610(int* p)
{
    int* end = (int*)p[1];
    for (int* it = (int*)*p; it < end; it += 0x47) {
        for (uint32_t i = (uint32_t)*it; i < (uint32_t)it[1]; i += 0x20) {
        }
        FUN_00455290(it);
    }
    FUN_004b6450();
}

// @ 0x4b52b0
int FUN_004b52b0(float* a, float* b)
{
    bool c;
    if (*a == *b) {
        if (a[1] == b[1]) {
            if (a[2] == b[2]) c = false;
            else c = (a[2] <= b[2]) && (b[2] != a[2]);
        } else {
            c = (a[1] <= b[1]) && (b[1] != a[1]);
        }
    } else {
        c = (*a <= *b) && (*b != *a);
    }
    return c;
}

// ---------------------------------------------------------------- 0x4b4930 ExtractRegionPaintData
// Reads the region paint data for a model from its UI asset view: picks the skin-effect property ids by theme id, loads the
// property list of each (AutoRefCount<PropertyList> into vB), then for every outline vertex of the asset picks a random
// palette colour id (vC, filled from the palette cursor's entries of type 0xbd110a25) and stores
// {colour, next vertex, vertex} into the theme's region map (this+0xc) for every flag set in the "regionPaint" bool array.
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
extern "C" void* __cdecl InitVerbCollection(void* a);    // 0x4bb860
extern "C" bool __cdecl IsRegionless(void* verbs);       // 0x4bbed0
extern "C" bool __cdecl ExtractSkinPaintData(void* verbs);   // 0x4bbe90
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

// @ 0x4b4930
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

// @ 0x4b5080  hashtable find/insert (4-byte value)
int __fastcall FUN_004b5080(void* self, uint32_t* key)
{
    (void)self; (void)key;
    return 0;
}

// @ 0x4b5160  hashtable find/insert (0x1c-byte value)
int __fastcall FUN_004b5160(void* self, uint32_t* key)
{
    (void)self; (void)key;
    return 0;
}

// @ 0x4b5210  rbtree lower_bound-ish search
void* __fastcall FUN_004b5210(void* self, void* out, void* key)
{
    (void)self; (void)out; (void)key;
    return out;
}

// @ 0x4b5370  rbtree insert with float key
int __fastcall FUN_004b5370(void* self, void* out, void* key)
{
    (void)self; (void)out; (void)key;
    return 0;
}
