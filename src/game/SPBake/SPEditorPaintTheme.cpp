// src/game/SPBake/SPEditorPaintTheme.cpp -- migrated from slice(s) s004b3e10, s004bafc0, s004ba150, s004b4930, s004b33e0, s004b2320 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorPaintTheme.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorPaintTheme.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include "cSPBoundingBox.h"
#include "cSPTransform.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"

// ---- items of slice s004b2320 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_PropertyManager();                 // 0x0067de30
extern "C" void  FUN_006a0760(void* obj, uint32_t id, void* a, void* b);
extern "C" void  FUN_004b8750(int a, int b, void* out, int c);
extern "C" char  FUN_004b3a50(void* out, int a, uint32_t b);
extern "C" void  FUN_00440f60(void* out);
extern "C" void  FUN_00440ff0(void* obj);
extern "C" void  FUN_00440c40(void* obj, int a);
extern "C" void  FUN_004b8180();
extern "C" void  FUN_004098a0(void* dst, const void* src);
extern "C" void  FUN_00425990(void* vec);
extern uint32_t DAT_015d6e2c, DAT_015d6e30, DAT_015d6e34;
extern uint32_t DAT_015d6b98, DAT_015d6b9c, DAT_015d6ba0;
extern uint32_t DAT_015d6cc8, DAT_015d6f64;
extern "C" void  FUN_004553b0(void* out, void* key);
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct cSPColorRGB_s004b_2320 { uint32_t x, y, z; };
struct PropObj;
struct PropMgr;
extern "C" void  FUN_006a0ae0(PropObj* list, uint32_t name, void* a, void* b);
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
struct PropObj {
    virtual void v0();                                // 0 (+0)
    virtual void Release();                           // 1 (+4)
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual char Has(uint32_t id);                    // 7 (+0x1c)
    virtual void v8(); virtual void v9();
    virtual void* Get(uint32_t id);                   // 10 (+0x28)
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual char GetPropertyList(int id, uint32_t type, void** out);   // 11 (+0x2c)
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
    void  SetSource(int source);  // 0x004b26e0 (SP::cSPEditorPaintTheme::SetSource)
    void  Reset();
    void  Reset2();  // 0x004b27c0 (SP::cSPEditorPaintTheme::Reset2)
    uint32_t ReadFromAsset(Asset* asset);
    uint32_t ReadFromProp2(int prop, char useColors);
    uint32_t ReadFromProp(int prop);
    void  WriteToProp(Asset* asset, int resourceType);
    void  ApplyToAsset(int asset, int view);  // 0x004b3190 (SP::cSPEditorPaintTheme::ApplyToAsset)
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

// ---- items of slice s004b33e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00454420(void* value);
extern "C" void  FUN_00566c50(void* tree);
extern "C" int   FUN_004b5210(void* out, void* key);
extern "C" void  FUN_004769b0(void* a, void* b);
extern "C" void  FUN_00441d10(void* a);
extern "C" void  FUN_004b5xxx_push(void* value);
struct cSPColorRGB_s004b_33e0 { uint32_t x, y, z; };
extern "C" void  GetPropertyAsIntArray(PropObj* list, uint32_t id, void* a, void* b);
namespace SP {
struct PaintVector_s004b_33e0 {
    void* mpBegin; void* mpEnd; void* mpCap;
    char  mInline[0x110];
    void* Insert(void* value);
    void FUN_004b4fa0(void* a);   // 0x004b4fa0
};
}
namespace SP {
struct ModelTree_s004b_33e0 {  // 0x004b5080
    char _[0x1c];
    void* FUN_004b5080(void* a, void* b = 0);
};
}
namespace SP {
class cSPEditorPaintTheme_s004b_33e0 {
public:
    void* mpVtbl0; void* mpVtbl1; int mRefCount;
    PaintVector_s004b_33e0 mPropTheme;          // +0xc
    ModelTree_s004b_33e0   mModelTheme;         // +0x128
    uint32_t mPropThemeID;           // +0x144
    uint32_t mSourceRef;             // +0x148
    uint32_t mResourceType;          // +0x14c
    void* mpClosestBegin;            // +0x150
    void* mpClosestEnd;              // +0x154
    void* mpClosestCap;              // +0x158
    char  pad_15c[8];
    uint32_t mSkinEffects[3];
    uint32_t mSkinEffectSeeds[3];
    cSPColorRGB_s004b_33e0 mSkinColors[3];
    void InitClosestRegions(int a, int b);  // 0x004b3730 (SP::cSPEditorPaintTheme::InitClosestRegions)
    void SetRegionColor(int a, int b, int c, int d);  // 0x004b3c70 (SP::cSPEditorPaintTheme::SetRegionColor)
    char FUN_004b3910(int* out, int key, int arg3);
    char FUN_004b3a50(int out, int key, int arg3);
    char FUN_004b3b20(int key, int* outCount, int* outPtr);
    void FUN_004b3c20(int model);
};
}
// ---- items of slice s004b33e0 end

// ---- items of slice s004b3e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gPropListType;                               // 0x15d6cc8
extern "C" void* FUN_004bbed0(void* a);
extern "C" void* cSPUIAssetView_InitVerbCollection(void* a);
extern "C" int   FUN_004b2800(void* self, void* a);
extern "C" void  FUN_004b3e10(int self);
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vec3R : Vec3 {};
Vec3R operator-(const Vec3& a, const Vec3& b);               // 0x0041db10
float VectorLength(const Vec3& v);                           // 0x0040ae50 (cdecl, by address)
struct rwVec3 {
    float x, y, z;
    rwVec3() {}
    rwVec3(const rwVec3& v);                                 // 0x004098a0
};
struct BBox { rwVec3 mn, mx; };
struct rwVec3R : rwVec3 { };
rwVec3R operator-(const rwVec3& a, const rwVec3& b);         // 0x0041db10
struct EntryRec { uint32_t id; Vec3 a; Vec3 b; };
struct Entry { uint32_t inst; EntryRec rec; };
struct EntryVec { Entry* mpBegin; Entry* mpEnd; };
struct cSPEditorBlock_s004b_3e10 {
    char pad[0x4c8];
    EntryVec mEntries;                                       // +0x4c8
    void GetBBox(BBox* out, int a, int b, int c);            // 0x44ae00
};
struct cSPEditorModel_s004b_3e10 {
    cSPEditorBlock_s004b_3e10* GetBlock(int i);                         // 0x4accb0
    uint32_t GetBlockCount();                                // 0x4accf0
};
struct PropObj2 { virtual void v0(); virtual void Release(); };
struct PropRef {
    PropObj2* mp;
    PropRef() : mp(0) {}
    ~PropRef() { if (mp) mp->Release(); }
    PropObj2** operator&() { if (mp) { PropObj2* t = mp; mp = 0; t->Release(); } return &mp; }
};
struct PropMgr2 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t id, uint32_t type, PropObj2** out);
};
PropMgr2* SP_PropertyManager2();                             // 0x67de30
void GetFloatProperty(PropObj2* list, uint32_t id, float* out);   // 0x40cf10
struct TreeNode { char hdr[0x10]; };
struct TreePair { Vec3 first; float second; };
struct TreeIter {
    TreeNode* mpNode;
    TreeIter(TreeNode* n);                                   // 0x566c50
    TreePair* operator->();                                  // 0x564f50 (returns &value)
    TreeIter& operator++();                                  // 0x422c50
};
inline bool operator!=(const TreeIter& a, const TreeIter& b) { return a.mpNode != b.mpNode; }
struct AllocTag { AllocTag() {} };
struct ColorAreaMap {
    typedef TreeIter iterator;
    uint32_t cmp;
    TreeNode* mpRight;
    TreeNode* mpLeft;
    TreeNode* mpParent;
    uint32_t mColor;
    uint32_t mnSize;
    uint32_t mPad;
    ColorAreaMap(const AllocTag& a = AllocTag());            // 0x4b5980
    ~ColorAreaMap() { DoNuke(mpParent); }
    void DoNuke(TreeNode* n);                                // 0x4e8a30
    iterator begin() { return iterator(mpLeft); }
    iterator end() { return iterator((TreeNode*)&mpRight); }
    iterator find(const Vec3& k);                            // 0x4b5210
    float& operator[](const Vec3& k);                        // 0x4b5370
};
namespace SP {
class cSPEditorPaintTheme_s004b_3e10 {
public:
    void* pad[0x150 / 4];
    void* mpClosestBegin;   // +0x150
    void* mpClosestEnd;     // +0x154
    void* mpClosestCap;     // +0x158
    char  pad_15c[8];
    uint32_t mSkinEffects[3];    // +0x164
    uint32_t mSkinEffectSeeds[3];// +0x170
    Vec3 mSkinColors[3];         // +0x17c
    void __thiscall GenerateSkinPaint(cSPEditorModel_s004b_3e10* model);
    unsigned char __thiscall ReadSkinTheme(int a, int b, int c);
};
}
// ---- items of slice s004b3e10 end

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



// @ 0x004b2710
void SP::cSPEditorPaintTheme_s004b_2320::Reset()
{
    ScratchSlots<6>();
    mModelTheme.Reset();
    mPropTheme.Clear();
    mPropThemeID = 0;
    for (int i = 0; i < 3; i++) {
        mSkinColors[i].x = DAT_015d6e2c;
        mSkinColors[i].y = DAT_015d6e30;
        mSkinColors[i].z = DAT_015d6e34;
        mSkinEffects[i] = 0;
        mSkinEffectSeeds[i] = 0x4d2;
    }
}



// @ 0x004b27c0
void SP::cSPEditorPaintTheme_s004b_2320::Reset2()
{
    ScratchSlots<6>();
    mModelTheme.Reset();
    mPropTheme.Clear();
}



// @ 0x004b29b0
uint32_t SP::cSPEditorPaintTheme_s004b_2320::ReadFromProp2(int prop, char useColors)
{
    PropObj* list = 0;
    char ok = ((PropMgr*)SP_PropertyManager())->GetPropertyList(prop, DAT_015d6cc8, (void**)&list);
    if (!ok) {
        if (list)
            list->Release();
        return 0;
    }
    int count = 0;
    void* data = 0;
    int unused = 0;
    FUN_006a0ae0(list, 0xb0e066a7, &unused, &count);
    void* colors = 0;
    if (list->Has(0xb0e066a8)) {
        void* p = list->Get(0xb0e066a8);
        if ((*(uint16_t*)((char*)p + 0x10) & 0x30) == 0) {
            if (*(int16_t*)((char*)p + 0x12) != 0)
                colors = p;
        } else {
            colors = *(void**)p;
        }
    }
    for (int i = 0; i < count; i++) {
        int v = *(int*)((char*)data + i * 0xc);
        if (v != 0) {
            mSkinEffects[i] = v;
            mSkinEffectSeeds[i] = 0x4d2;
            if (useColors == 0) {
                mSkinColors[i].x = DAT_015d6b98;
                mSkinColors[i].y = DAT_015d6b9c;
                mSkinColors[i].z = DAT_015d6ba0;
            } else {
                uint32_t* c = (uint32_t*)colors + i * 3;
                mSkinColors[i].x = c[0];
                mSkinColors[i].y = c[1];
                mSkinColors[i].z = c[2];
            }
        }
    }
    if (list)
        list->Release();
    return 1;
}



// @ 0x004b2bb0
uint32_t SP::cSPEditorPaintTheme_s004b_2320::ReadFromProp(int prop)
{
    mModelTheme.Nuke(*(void**)((char*)&mModelTheme + 0xc));
    mModelTheme.ResetFast();
    mPropTheme.Erase(mPropTheme.mpBegin, mPropTheme.mpEnd);

    PropMgr* mgr = (PropMgr*)SP_PropertyManager();
    PropObj* list = 0;
    void* key = 0;
    mgr->GetPropertyList(prop, DAT_015d6cc8, (void**)&key);
    list = (PropObj*)key;
    if (list == 0)
        return 0;

    void* colors = 0;
    int count = 0;
    if (list->Has(0xb0e066a7)) {
        void* p = list->Get(0xb0e066a7);
        if ((*(uint16_t*)((char*)p + 0x10) & 0x30) == 0) {
            count = (*(int16_t*)((char*)p + 0x12) != 0) ? 1 : 0;
        } else {
            count = *(int*)((char*)p + 8);
        }
        colors = p;
    }
    void* colorA = 0;
    void* colorB = 0;
    if (list->Has(0xb0e066a8)) {
        void* p = list->Get(0xb0e066a8);
        colorA = p;
        if ((*(uint16_t*)((char*)p + 0x10) & 0x30) == 0) {
            if (*(int16_t*)((char*)p + 0x12) == 0)
                colorA = 0;
        } else {
            colorA = *(void**)p;
        }
    }
    if (list->Has(0xb0e066a9)) {
        void* p = list->Get(0xb0e066a9);
        colorB = p;
        if ((*(uint16_t*)((char*)p + 0x10) & 0x30) == 0) {
            if (*(int16_t*)((char*)p + 0x12) == 0)
                colorB = 0;
        } else {
            colorB = *(void**)p;
        }
    }
    (void)colors;
    for (int i = 0; i < count; i++) {
        int v = *(int*)((char*)colorA + i * 0xc);
        if (v != 0 && v != (int)0xe960add1) {
            uint32_t out[7];
            out[0] = v;
            uint32_t* cb = (uint32_t*)colorB + i * 3;
            out[1] = cb[0];
            out[2] = cb[1];
            out[3] = cb[2];
            cSPColorRGB_s004b_2320 col;
            FUN_004098a0(&col, (char*)colorA + i * 0xc + 4);
            (void)col;
            uint32_t* dst = (uint32_t*)mPropTheme.Insert(out);
            for (int k = 0; k < 7; k++)
                dst[k] = out[k];
        }
    }
    mPropThemeID = (uint32_t)prop;
    InitClosestRegions((void*)mSourceRef, (void*)mSourceRef);
    if (list)
        list->Release();
    return 1;
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



// @ 0x004b31d0
void SP::cSPEditorPaintTheme_s004b_2320::Apply(int a, int b, int c, int d)
{
    int local8 = 0;
    int localc = 0;
    if (c != 0)
        FUN_006a0760((void*)c, 0xf21a7bdc, &localc, &local8);
    if (a == 0 || b == 0)
        return;
    int vec[3] = {0, 0, 0};
    FUN_004b8750(a, b, vec, -1);
    int* begin = *(int**)&vec[0];
    int* end = *(int**)&vec[1];
    int n = (int)(end - begin) >> 2;
    for (int i = 0; i < n; i++) {
        int region = begin[i];
        if (!(localc != 0 && !(region < local8 && *(char*)(localc + region) != 0)))
            continue;
        int out[8];
        FUN_00440f60(out);
        int extra = 0;
        if (d != 0)
            extra = *(int*)(d + 0x1c);
        char ok = FUN_004b3a50(out, region, extra);
        if (!ok)
            continue;
        if (d == 0) {
            FUN_00440ff0(out);
            FUN_004b8180();
        } else {
            if (out[0] == 0) {
                int base = d + 0x4c8;
                int tmpA = 0, tmpB = 0;
                FUN_004553b0(&tmpA, &region);
                int node = (tmpA == tmpB) ? *(int*)(base + 4) : tmpA;
                if (node != *(int*)(base + 4))
                    out[0] = *(int*)(node + 4);
            }
            FUN_00440c40(out, region);
        }
    }
    FUN_00425990(vec);
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


// @ 0x004b3730
void SP::cSPEditorPaintTheme_s004b_33e0::InitClosestRegions(int a, int b)
{
    FUN_004769b0((void*)mResourceType, (void*)mSourceRef);
    int id = 0;
    bool match = false;
    if ((a == 0x24682294) || (a == 0x476a98c7)) {
        if ((b == 0x24682294) || (b == 0x476a98c7))
            id = 0x1625a584;
        else if (b == 0x2399be55)
            id = (int)0xb5306a4c;
    } else if (a == 0x2399be55) {
        if ((b == 0x24682294) || (b == 0x476a98c7))
            id = (int)0x844c912e;
        else if (b == 0x2399be55)
            id = (int)0xb3ef1246;
    }
    (void)match;
    if (id != 0) {
        PropObj* list = 0;
        PropMgr* mgr = (PropMgr*)SP_PropertyManager();
        if (list)
            list->Release();
        char ok = mgr->GetPropertyList(id, 0x4060e200, (void**)&list);
        if (ok) {
            int count = 0;
            int data = 0;
            GetPropertyAsIntArray(list, 0x52c57aa, &count, &data);
            FUN_00441d10(&mpClosestBegin);
            for (int i = 0; i < count; i++)
                FUN_004b5xxx_push((void*)(data + i * 4));
        }
        if (list)
            list->Release();
    }
}


// @ 0x004b3910
char SP::cSPEditorPaintTheme_s004b_33e0::FUN_004b3910(int* out, int key, int arg3)
{
    if (out == 0)
        return 0;
    FUN_00566c50((void*)((int)this + 300));
    int local_c = 0;
    void* found = (void*)FUN_004b5210(&local_c, &arg3);
    if (found != 0) {
        void* r = mModelTheme.FUN_004b5080((void*)&arg3);
        int iVar2 = FUN_004b33e0(out, (int*)r, key);
        if (iVar2 != 0)
            return 1;
    }
    char cVar1 = (char)FUN_004b3660((int)this, out, key);
    if (cVar1 != '\0')
        return 1;
    int a = 0, b = 0;
    FUN_004553b0(&a, &key);
    int node = (a == b) ? *(int*)((int)this + 0x10) : a;
    if (node != *(int*)((int)this + 0x10)) {
        int* src = (int*)FUN_00454420(&key);
        for (int k = 0; k < 7; k++)
            out[k] = src[k];
        return 1;
    }
    return 0;
}


// @ 0x004b3a50
char SP::cSPEditorPaintTheme_s004b_33e0::FUN_004b3a50(int out, int key, int arg3)
{
    int local_8 = 0;
    int local_10 = 0;
    char c = FUN_004b3b20(key, &local_8, &local_10);
    if (c == '\0') {
        if (FUN_004b3910((int*)out, key, arg3) != 0)
            return 1;
    } else {
        for (int i = 0; i < local_8; i++) {
            if (FUN_004b3910((int*)out, *(int*)(local_10 + i * 4), arg3) != 0)
                return 1;
        }
    }
    int limit = 0x22;
    int i = 0;
    while (i < limit) {
        if (FUN_004b3910((int*)out, i, arg3) != 0)
            return 1;
        i++;
    }
    return 0;
}


// @ 0x004b3b20
char SP::cSPEditorPaintTheme_s004b_33e0::FUN_004b3b20(int key, int* outCount, int* outPtr)
{
    int self = (int)this;
    if (outCount == 0 || outPtr == 0 || key < 0)
        return 0;
    *outCount = 0;
    int found = 0;
    int start = *(int*)(self + 0x150);
    int n = (*(int*)(self + 0x154) - start) >> 2;
    int i = 0;
    while (i < n && found != key) {
        if (*(int*)(start + i * 4) == -1)
            found++;
        i++;
    }
    if (i == n)
        return 0;
    *outPtr = start + i * 4;
    do {
        int off = i * 4;
        i++;
        if (*(int*)(start + off) == -1)
            break;
        *outCount = *outCount + 1;
    } while (i != n);
    return 1;
}


// @ 0x004b3c20
void SP::cSPEditorPaintTheme_s004b_33e0::FUN_004b3c20(int model)
{
    if (model != 0) {
        int local = *(int*)(model + 0x1c);
        int local2 = local;
        int addr = model + 0x4c8;
        (void)addr;
        void* r = mModelTheme.FUN_004b5080(&local2, &addr);
        ((SP::PaintVector_s004b_33e0*)r)->FUN_004b4fa0(&local2);
    }
}


// @ 0x004b3c70
void SP::cSPEditorPaintTheme_s004b_33e0::SetRegionColor(int a, int b, int c, int d)
{
    PropObj* list = 0;
    PropMgr* mgr = (PropMgr*)SP_PropertyManager();
    if (list)
        list->Release();
    mgr->GetPropertyList(d, 0x406a6f00, (void**)&list);
    if (list != 0) {
        int n = 0;
        int data = 0;
        FUN_006a0760(list, 0xf21a7bdc, &data, &n);
        for (int i = 0; i < n; i++) {
            if (*(char*)(data + i) == 1) {
                int a1 = 0, b1 = 0;
                FUN_004553b0(&a1, &i);
                int node = (a1 == b1) ? *(int*)((char*)&mPropTheme + 0xc)
                                      : a1;
                if (node != *(int*)((char*)&mPropTheme + 0xc)) {
                    int e = (int)FUN_00454420(&i);                    *(int*)(e + 0x10) = a;
                    *(int*)(e + 0x14) = b;
                    *(int*)(e + 0x18) = c;
                }
            }
        }
    }
    if (list)
        list->Release();
}


// @ 0x004b3e10
void SP::cSPEditorPaintTheme_s004b_3e10::GenerateSkinPaint(cSPEditorModel_s004b_3e10* model)
{
    const uint32_t n1 = 0x25e49bb;
    const uint32_t m = 0x265fb07;
    ColorAreaMap t25;
    uint32_t v14 = model->GetBlockCount();
    for (uint32_t i = 0; i < v14; i++) {
        cSPEditorBlock_s004b_3e10* n35 = model->GetBlock(i);
        const EntryVec& p15 = n35->mEntries;
        const Entry* v18 = p15.mpBegin;
        const Entry* p12 = p15.mpEnd;
        while (v18 != p12) {
            const EntryRec* t38 = &v18->rec;
            uint32_t n12 = v18->inst;
            PropRef n21;
            if (SP_PropertyManager2()->GetPropertyList(t38->id, gPropListType, &n21)) {
                float v4 = 0.0f;
                float size = 0.0f;
                GetFloatProperty(n21.mp, n1, &v4);
                GetFloatProperty(n21.mp, m, &size);
                BBox data;
                n35->GetBBox(&data, 1, 0, 0);
                ScratchSlots<6>();
                rwVec3 left = data.mx - data.mn;
                float t34 = (left.x * left.y + left.y * left.z + left.x * left.z) * 2.0f;
                float t20 = t34;
                if (v4 > 0.0f) {
                    Vec3 k(t38->a);
                    if (t25.find(k) != t25.end())
                        t25[k] += t20;
                    else
                        t25[k] = t20;
                }
                if (size > 0.0f) {
                    ScratchSlots<20>();
                    Vec3 k(t38->b);
                    if (t25.find(k) != t25.end())
                        t25[k] += t20;
                    else
                        t25[k] = t20;
                }
            }
            v18++;
        }
    }
    float t14 = 0.3f;
    for (int i = 0; i < 3; i++) {
        float p5 = 0.0f;
        bool v1 = false;
        ColorAreaMap::iterator p27 = t25.begin();
        ColorAreaMap::iterator pNode = t25.end();
        while (p27 != pNode) {
            float count = p27->second;
            if (count > p5) {
                ScratchSlots<20>();
                Vec3 cap(p27->first);
                bool p24 = false;
                for (int j = i - 1; j >= 0; j--) {
                    Vec3 elem(mSkinColors[j]);
                    Vec3 h = elem - cap;
                    float p33 = VectorLength(h);
                    if (t14 > p33) {
                        p24 = true;
                        break;
                    }
                }
                if (!p24) {
                    p5 = count;
                    mSkinColors[i] = cap;
                    v1 = true;
                }
            }
            ++p27;
        }
        if (!v1) {
            t14 -= 0.1f;
            i--;
        }
    }
}

// @ 0x004b4470
unsigned char __thiscall SP::cSPEditorPaintTheme_s004b_3e10::ReadSkinTheme(int prop, int a, int b)
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
