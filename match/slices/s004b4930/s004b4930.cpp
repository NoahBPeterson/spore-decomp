// Slice s004b4930: eastl container primitives (rbtree reset/nuke, vector erase/insert/push) plus
// the (huge) ExtractRegionPaintData. Unoptimized editor module: /Od /Ob1 /arch:SSE, no /EHsc.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

extern void* g_static1;   // 0x01667bac

extern "C" {
    void  FUN_00425990(void* vec);
    void  FUN_0042dee0();
    void  FUN_004b6340();
    void  FUN_004b69d0();
    void  FUN_004b64b0();
    void  FUN_004b66b0();
    void  FUN_004b6bf0();
    void  FUN_004b5a60(void* node);
    void  operator_delete_(void* p);
}
void __fastcall FUN_00455290(void* self);   // thiscall: ecx = outer element
void __fastcall FUN_004b6450(void* self);   // thiscall: ecx = outer vector

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

struct Rec11c {
    char pad[0x118]; char f118;
    void FUN_004b62a0(Rec11c* src);   // 0x004b62a0
};
struct RecVec11c {
    Rec11c* mpBegin; Rec11c* mpEnd; Rec11c* mpCap;
    void FUN_004b4fa0(Rec11c* a);
    void FUN_004b5690(Rec11c* pos, Rec11c* a);   // 0x004b5690
};

// @ 0x4b4fa0
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

// @ 0x4b5610
void __fastcall FUN_004b5610(int* p)
{
    int* end = (int*)p[1];
    for (int* it = (int*)*p; it < end; it += 0x47) {
        for (uint32_t i = (uint32_t)*it; i < (uint32_t)it[1]; i += 0x20) {
        }
        FUN_00455290(it);
    }
    FUN_004b6450(p);
}

struct Float3Cmp {
    float x, y, z;
    bool FUN_004b52b0(float* b);
};

// @ 0x4b52b0
bool Float3Cmp::FUN_004b52b0(float* b)
{
    float* a = &x;
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
    void DoInsertValue(PropListRef** end, const PropListRef& r);   // 0x4b6000
};

// @ 0x4b54b0
void PropListVec::push_back(const PropListRef& r)
{
    if (mpEnd < mpCap) {
        PropListRef* slot = (PropListRef*)mpEnd;
        mpEnd = (PropListRef**)((char*)mpEnd + 4);
        if (slot != 0) {
            slot->mp = r.mp;
            if (slot->mp != 0)
                slot->mp->AddRef();
        }
    } else {
        DoInsertValue(mpEnd, r);
    }
}

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

// ---- 0x4b5080..0x4b5370 eastl rbtree wrappers ----------------------------------------------------
struct RbNode;
struct RbNodeBase {
    RbNodeBase* mpLeft;                 // +0x00
    RbNodeBase* mpRight;                // +0x04
    RbNodeBase* mpParent;               // +0x08
    char        mColor;                 // +0x0c
    char        pad0d[3];
};
struct RbIter {
    RbNodeBase* mpNode;                 // +0x00 (null == end)
    RbIter() {}
    RbIter(const RbIter& src);          // 0x5673e0  out-of-line copy ctor (retail keeps it non-trivial)
    RbIter*  assign(RbNodeBase* node);  // 0x566c50  *this = node; returns this
    uint32_t* value();                  // 0x564f50  &node->mValue (the stored key pair)
};
// rbtree base: anchor/sentinel node at +0x04 (mpParent at +0x0c is the root)
struct RbTree {
    char        pad0[4];
    RbNodeBase  mAnchor;                // +0x04
    RbIter* lower_bound(RbIter* out, const uint32_t* key);          // 0x4b5e90
    RbIter* insert_v4(RbIter* out, RbIter pos, const void* value);  // 0x4b59e0 (4-byte value)
    RbIter* insert_v28(RbIter* out, RbIter pos, const void* value); // 0x4b5e50 (0x1c-byte value)
    RbIter* insert_float(RbIter* out, RbIter pos, const void* value); // 0x4b5f00 (float key)
    RbIter* lower_bound_key16(RbIter* out, const void* key);        // 0x4b5f40

    int* find_or_insert4(const uint32_t* key);      // 0x4b5080
    int* find_or_insert28(const uint32_t* key);     // 0x4b5160
    RbIter* find_iter(RbIter* out, const float* key);// 0x4b5210
    int* find_or_insert_float(const float* key);    // 0x4b5370
};
// small eastl vector with a fixed inline 8-byte node buffer, built around the insert call
struct NodeVec8 {
    void* mpBegin;                      // +0x00
    void* mpEnd;                        // +0x04
    void* mpCapacity;                   // +0x08
    char  mAlloc[8];                    // +0x0c
    void* mpOverflow;                   // +0x14
    NodeVec8* Construct();                       // 0x4727a0
    NodeVec8* ConstructFrom(const NodeVec8& s);  // 0x455cf0
    void      Destroy();                         // 0x45daf0
};
// value type of the 0x1c-byte tree: pair<uint32, Trans>
struct TransBody { char m[0xc]; };      // SP::Trans (12 bytes here)
struct Val16 { uint32_t mKey; TransBody mVal; };
void Value_DefaultCtor16(void* v);      // 0x4b63b0
void Trans_CopyCtor(void* self, const void* src);   // 0x440ff0 (SP::Trans::Trans(const Trans&))
struct Val04 { uint32_t mKey; uint32_t mVal; };
void Fun_004b5610(void* v);             // 0x4b5610 (NodeVec8 destructor helper)

// forward decls of types/functions defined earlier in this file
struct Float3Cmp;

// @ 0x4b5080  map<uint32,pair>::find_or_insert -> pointer to the 4-byte value (+4)
int* RbTree::find_or_insert4(const uint32_t* key)
{
    RbIter found;
    lower_bound(&found, key);
    RbIter end;
    end.assign(&mAnchor);
    if (found.mpNode == end.mpNode || *key < *found.value()) {
        NodeVec8 scratchA;
        scratchA.Construct();
        Val04 value;
        value.mKey = *key;
        value.mVal = 0;
        NodeVec8 scratchB;
        scratchB.ConstructFrom(scratchA);
        RbIter out;
        insert_v4(&out, found, &value);
        found = out;
        for (char* p = (char*)scratchB.mpBegin; p < (char*)scratchB.mpEnd; p += 8) {}
        scratchB.Destroy();
        for (char* p = (char*)scratchA.mpBegin; p < (char*)scratchA.mpEnd; p += 8) {}
        scratchA.Destroy();
    }
    return (int*)(found.value() + 1);
}

// @ 0x4b5160  map<uint32,pair>::find_or_insert -> pointer to the 0x1c-byte value (+0x1c)
int* RbTree::find_or_insert28(const uint32_t* key)
{
    RbIter found;
    lower_bound(&found, key);
    RbIter end;
    end.assign(&mAnchor);
    if (found.mpNode == end.mpNode || *key < *found.value()) {
        Val16 value;
        value.mKey = 0;
        Trans_CopyCtor(&value.mVal, (const void*)key);  // 0x440ff0 (SP::Trans copy ctor into the value)
        RbIter out;
        insert_v28(&out, found, &value);
        found = out;
    }
    return (int*)((char*)found.value() + 0x1c);
}

// @ 0x4b5210  rbtree lower_bound/find -> iterator out (returns the out pointer)
RbIter* RbTree::find_iter(RbIter* out, const float* key)
{
    int slot;                              // retail reserves one extra 4-byte slot here
    RbNodeBase* node = mAnchor.mpParent;   // root
    RbNodeBase* prev = &mAnchor;
    while (node != 0) {
        if (!((Float3Cmp*)((char*)node + 0x10))->FUN_004b52b0((float*)key)) {
            prev = node;
            node = node->mpRight;
        } else {
            node = node->mpLeft;
        }
    }
    if (prev == &mAnchor || !((Float3Cmp*)key)->FUN_004b52b0((float*)((char*)prev + 0x10))) {
        out->assign(prev);
    } else {
        out->assign(&mAnchor);
    }
    return out;
}

// @ 0x4b5370  map<Key16,pair>::find_or_insert -> pointer to value (+0xc)
int* RbTree::find_or_insert_float(const float* key)
{
    RbIter found;
    lower_bound_key16(&found, key);
    RbIter end;
    end.assign(&mAnchor);
    if (found.mpNode == end.mpNode || ((Float3Cmp*)key)->FUN_004b52b0((float*)found.value())) {
        struct Key16Val {
            float    mKey;               // +0x00 = 0
            float    v[3];               // +0x04 = key[0..2]
            float    mTail;              // +0x10 = 0
        };
        float zero = 0.0f;
        Key16Val value;
        value.mKey = zero;
        value.v[0] = key[0];
        value.v[1] = key[1];
        value.v[2] = key[2];
        value.mTail = zero;
        RbIter out;
        insert_float(&out, found, &value);
        found = out;
    }
    return (int*)((char*)found.value() + 0xc);
}

// --- out-of-line iterator helpers (retail has these at 0x5673e0 / 0x566c50 / 0x564f50; defined here so the
//     slice links standalone for the difftest harness) ---------------------------------------------------
RbIter::RbIter(const RbIter& src) { mpNode = src.mpNode; }
RbIter* RbIter::assign(RbNodeBase* node) { mpNode = node; return this; }
uint32_t* RbIter::value() { return (uint32_t*)((char*)mpNode + 0x10); }
