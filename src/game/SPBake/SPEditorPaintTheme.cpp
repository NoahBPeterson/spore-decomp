// src/game/SPBake/SPEditorPaintTheme.cpp -- migrated from slice(s) s004b5690, s004b3e10, s004bafc0, s004ba150, s004b4930, s004b33e0, s004b2320 by tools/migrate/rewrite.py
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
#include "EA/Variant.h"
#include "EA/ResourceMan/Resource.h"
#include "EA/ResourceMan/Manager.h"
#include "SP/cEditorResource.h"
#include "SP/cPropertyList.h"

// ---- items of slice s004b2320 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_PropertyManager();                 // 0x0067de30
extern "C" void  FUN_006a0760(void* obj, uint32_t id, void* a, void* b);
extern "C" void  FUN_004b8750(int a, int b, void* out, int c);
extern "C" char  FUN_004b3a50(void* out, int a, uint32_t b);
extern "C" void  FUN_00440f60(void* out);
extern "C" void  FUN_00440ff0(void* obj);
extern "C" void  FUN_00440c40(void* obj, int a);
extern "C" void  FUN_004b8180();
extern "C" void  FUN_00425990(void* vec);
extern "C" void  FUN_00455290(void* vec);
extern "C" void  FUN_004b3c20(int a);
extern void* g_vtbl_EditorResource;
extern void* g_vtbl_BakeSprites;
extern void* g_vtbl_ContentValidator;
extern void* g_vtbl_PaintTheme0;
extern void* g_vtbl_PaintTheme1;
extern uint32_t DAT_015d6e2c, DAT_015d6e30, DAT_015d6e34;
extern uint32_t DAT_015d6b98, DAT_015d6b9c, DAT_015d6ba0;
extern uint32_t DAT_015d6cc8, DAT_015d6f64;
extern "C" void* FUN_004bb860(void* a);
extern "C" char  FUN_0041dd30(void* a, void* b);
extern "C" void  FUN_004553b0(void* out, void* key);
inline void* operator new(unsigned int, void* p) { return p; }
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
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual char Has(uint32_t id);                    // 7 (+0x1c)
virtual void v8();
virtual void v9();
    virtual void* Get(uint32_t id);                   // 10 (+0x28)
};
struct PropMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void v10();
    virtual char GetPropertyList(int id, uint32_t type, void** out);   // 11 (+0x2c)
};
struct PropEntry { uint32_t v; float x, y, z; };
struct Vec3_s004b_2320 {  // 0x004098a0
    float x, y, z;
    Vec3_s004b_2320(const Vec3_s004b_2320& v);
};
struct Trans { uint32_t f0; float a[3]; float b[3]; };
struct PaintPropRef {
    PropObj* mpRef;                                             // +0
    PaintPropRef() : mpRef(0) { if (mpRef) mpRef->v0(); }
    ~PaintPropRef() { if (mpRef) mpRef->Release(); }
    void* AsPPVoidParam();                                      // 0x0041d870
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
    void  Reset();  // 0x004b2710 (SP::cSPEditorPaintTheme::Reset)
    void  Reset2();  // 0x004b27c0 (SP::cSPEditorPaintTheme::Reset2)
    uint32_t ReadFromAsset(Asset* asset);  // 0x004b2800 (SP::cSPEditorPaintTheme::ReadFromAsset)
    bool ReadFromProp2(int prop, char useColors);  // 0x004b29b0 (SP::cSPEditorPaintTheme::ReadFromProp2)
    bool ReadFromProp(uint32_t prop);  // 0x004b2bb0 (SP::cSPEditorPaintTheme::ReadFromProp)
    void  WriteToProp(Asset* asset, int resourceType);  // 0x004b2f80 (SP::cSPEditorPaintTheme::WriteToProp)
    void  ApplyToAsset(int asset, int view);  // 0x004b3190 (SP::cSPEditorPaintTheme::ApplyToAsset)
    void  Apply(int a, int b, int c, int d);  // 0x004b31d0 (SP::cSPEditorPaintTheme::Apply)
    void  InitClosestRegions(void* a, void* b);  // 0x004b3730 (SP::cSPEditorPaintTheme::InitClosestRegions)
};
}
extern "C" void  FUN_004add30(Asset* a, int i, cSPColorRGB_s004b_2320* c);
extern "C" void  FUN_004adcf0(Asset* a, int i, uint32_t v);
extern "C" void  FUN_004add10(Asset* a, int i, uint32_t v);
extern "C" void  FUN_004ae250(Asset* a);
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
extern "C" void  FUN_004f3de0(void* a, void* b, int c, int d, int e, int f, char g);
extern int DAT_015da860, DAT_015da864, DAT_015da868, DAT_015da86c;
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
    void* FUN_004b5080(void* a);
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

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
bool FUN_004bbe90(uint32_t type);   // defined at 0x004bbe90, called earlier in the TU

// ---- items of slice s004b5690 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memmove_nd(void* dst, const void* src, uint32_t n);                     // 0x11e0744 (static CRT memmove)
void __cdecl EASTL_allocator_deallocate(void* p);                                                // 0xf47380
inline void operator delete(void* p) { EASTL_allocator_deallocate(p); }
namespace eastl {
template <typename T, T v> struct integral_constant { static const T value = v; };
}
namespace eastl {
typedef integral_constant<bool, true>  true_type;
}
namespace eastl {
typedef integral_constant<bool, false> false_type;
}
namespace eastl {
struct input_iterator_tag { input_iterator_tag() {} };
}
namespace eastl {
struct forward_iterator_tag : public input_iterator_tag { forward_iterator_tag() {} };
}
namespace eastl {
struct bidirectional_iterator_tag : public forward_iterator_tag { bidirectional_iterator_tag() {} };
}
namespace eastl {
struct random_access_iterator_tag : public bidirectional_iterator_tag { random_access_iterator_tag() {} };
}
namespace eastl {
template <typename T> struct has_trivial_relocate : public false_type {};
}
namespace eastl {
template <typename It> struct Iterator_traits_ref;
}
namespace eastl {
template <typename T> struct Iterator_traits_ref<T*> { typedef T& type; typedef T value_type; };
}
namespace eastl {
template <typename T> struct Iterator_traits_ref<const T*> { typedef const T& type; typedef T value_type; };
}
namespace eastl {
struct sp_vector_allocator_s004b_5690 {
    uint32_t mFlags;
    void deallocate(void* p, uint32_t n)
    {
        if (((uint32_t*)p)[-1]) {
            void* pBlock = p;
            EASTL_allocator_deallocate(pBlock);
        }
    }
};
}
namespace eastl {
void* __cdecl allocate_memory(sp_vector_allocator_s004b_5690& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);   // 0x42dee0
}
namespace eastl {
template <typename T> struct has_trivial_assign : public false_type {};
}
namespace eastl {
template <typename T> struct is_integral : public false_type {};
}
namespace eastl {
class fixed_vector_allocator { public:
    uint32_t mOverflowAllocator;
    void* mpPoolBegin;
    void deallocate(void* p, uint32_t n)
    {
        if (p != mpPoolBegin) {
            void* pBlock = p;
            EASTL_allocator_deallocate(pBlock);
        }
    }
};
}
namespace eastl {
void* __cdecl allocate_memory(fixed_vector_allocator& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);
}
namespace eastl {
template <typename Iterator>
class generic_iterator { public:
    Iterator mIterator;
    explicit generic_iterator(const Iterator& x) : mIterator(x) {}
    typename Iterator_traits_ref<Iterator>::type operator*() const { return *mIterator; }
    generic_iterator& operator++() { ++mIterator; return *this; }
    const Iterator& base() const { return mIterator; }
};
}
namespace eastl {
template <typename IteratorL, typename IteratorR>
inline bool operator!=(const generic_iterator<IteratorL>& lhs, const generic_iterator<IteratorR>& rhs)
{
    return lhs.base() != rhs.base();
}
}
namespace eastl {
template <bool bHasTrivialCopy>
struct copy_impl
{
    template <typename T>
    static T* do_copy(const T* first, const T* last, T* result)
    {
        for (; first != last; ++result, ++first)
            *result = *first;
        return result;
    }
};
}
namespace eastl {
template <typename T>
inline T* copy(const T* first, const T* last, T* result)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_impl<bHasTrivialCopy>::do_copy(first, last, result);
}
}
namespace eastl {
namespace Internal {
template <typename T, typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy_impl(InputIterator first, InputIterator last, ForwardIterator dest, false_type)
{
    ForwardIterator currentDest(dest);
    for (; first != last; ++first, ++currentDest)
        ::new(&*currentDest) T(*first);
    ScratchSlots<4>();
    return currentDest;
}
}
}
namespace eastl {
template <typename First, typename Last, typename Result>
Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    typedef typename Iterator_traits_ref<Result>::value_type value_type;
    const generic_iterator<Result> i(Internal::uninitialized_copy_impl<value_type>(generic_iterator<First>(first),
                                                                                   generic_iterator<Last>(last),
                                                                                   generic_iterator<Result>(result),
                                                                                   has_trivial_assign<value_type>()));
    return i.base();
}
}
namespace eastl {
template <bool bHasTrivialCopy>
struct copy_backward_impl
{
    template <typename T>
    static T* do_copy(T* first, T* last, T* resultEnd)
    {
        while (last != first)
            *--resultEnd = *--last;
        return resultEnd;
    }
};
}
namespace eastl {
template <typename T>
inline T* copy_backward(T* first, T* last, T* resultEnd)
{
    const bool bOutputIsPointer = false;
    const bool bInputIsPointer = false;
    const bool bHasTrivialCopy = false;
    return copy_backward_impl<bHasTrivialCopy>::do_copy(first, last, resultEnd);
}
}
namespace eastl {
template <bool hasTrivialRelocate>
struct uninitialized_relocate_impl
{
    template <typename T>
    static T* do_move_start(T* first, T* last, T* dest)
    {
        for (; first != last; ++first, ++dest)
            ::new(dest) T(*first);
        return dest;
    }
    template <typename T>
    static T* do_move_commit(T* first, T* last, T* dest)
    {
        for (; first != last; ++first, ++dest)
            (*first).~T();
        return dest;
    }
};
}
namespace eastl {
template <>
struct uninitialized_relocate_impl<true>
{
    template <typename T>
    static T* do_move_start(T* first, T* last, T* dest)
    {
        return (T*)((last - first) * sizeof(T) + (char*)memmove_nd(dest, first, (uint32_t)((char*)last - (char*)first)));
    }
    template <typename T>
    static T* do_move_commit(T* first, T* last, T* dest)
    {
        return dest;
    }
};
}
namespace eastl {
template <typename T>
inline T* uninitialized_relocate_start(T* first, T* last, T* dest)
{
    const bool bHasTrivialRelocate = has_trivial_relocate<T>::value;
    return uninitialized_relocate_impl<bHasTrivialRelocate>::do_move_start(first, last, dest);
}
}
namespace eastl {
template <typename T>
inline T* uninitialized_relocate_commit(T* first, T* last, T* dest)
{
    const bool bHasTrivialRelocate = has_trivial_relocate<T>::value;
    return uninitialized_relocate_impl<bHasTrivialRelocate>::do_move_commit(first, last, dest);
}
}
namespace eastl {
template <typename T>
inline T* uninitialized_relocate(T* first, T* last, T* dest)
{
    T* result = uninitialized_relocate_start(first, last, dest);
    uninitialized_relocate_commit(first, last, dest);
    return result;
}
}
namespace eastl {
template <typename T, typename Allocator>
struct VectorBase_s004b_5690 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    ~VectorBase_s004b_5690();                                                   // 0x455290 (for Entry32)
    T* DoAllocate(uint32_t n)
    {
        return n ? (T*)allocate_memory(mAllocator, n * sizeof(T), 4, 0) : 0;
    }
    void DoFree(T* p, uint32_t n)
    {
        if (p)
            mAllocator.deallocate(p, n * sizeof(T));
    }
    uint32_t GetNewCapacity(uint32_t currentCapacity)
    {
        return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
    }
};
}
namespace eastl {
template <typename T, typename Allocator>
class vector_s004b_5690 : public VectorBase_s004b_5690<T, Allocator> { public:
    typedef VectorBase_s004b_5690<T, Allocator> base_type;
    using base_type::mpBegin;
    using base_type::mpEnd;
    using base_type::mpCapacity;
    using base_type::mAllocator;

    ~vector_s004b_5690() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* erase(T* first, T* last);                                      // 0x4b5570 (Entry32)
    T* DoRealloc(uint32_t n, const T* first, const T* last);          // 0x4b74d0 (Entry32)
    const T* begin() const { return mpBegin; }
    const T* end() const { return mpEnd; }
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last) { DoAssign(first, last, is_integral<InputIterator>()); }
    template <typename InputIterator>
    void DoAssign(InputIterator first, InputIterator last, const false_type&) { DoAssignFromIterator(first, last, random_access_iterator_tag()); }
    void DoAssignFromIterator(const T* first, const T* last, input_iterator_tag);   // 0x4b7290 (Entry32)
    static void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    void DoInsertValue(T* position, const T& value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
};
}
namespace eastl {
template <typename T, typename Allocator>
void vector_s004b_5690<T, Allocator>::DoAssignFromIterator(const T* first, const T* last, input_iterator_tag)
{
    const uint32_t n = (uint32_t)(last - first);
    ScratchSlots<10>();     // unused slots of inlined helpers in the original
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        T* const pNewData = DoRealloc(n, first, last);
        DoDestroyValues(mpBegin, mpEnd);
        this->DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
    } else if (n <= (uint32_t)(mpEnd - mpBegin)) {
        T* const pNewEnd = eastl::copy(first, last, mpBegin);
        DoDestroyValues(pNewEnd, mpEnd);
        mpEnd = pNewEnd;
    } else {
        const T* position = first + (mpEnd - mpBegin);
        eastl::copy(first, position, mpBegin);
        mpEnd = eastl::uninitialized_copy_ptr(position, last, mpEnd);
    }
    ScratchSlots<16>();
}
}
namespace eastl {
template <typename T, typename Allocator>
void vector_s004b_5690<T, Allocator>::DoInsertValue(T* position, const T& value)
{
    if (mpEnd != mpCapacity) {
        const T* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new(mpEnd) T(*(mpEnd - 1));
        eastl::copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = this->GetNewCapacity(nPrevSize);
        T* const pNewData = this->DoAllocate(nNewSize);
        T* pNewEnd = eastl::uninitialized_relocate(mpBegin, position, pNewData);
        ::new(pNewEnd) T(value);
        pNewEnd = eastl::uninitialized_relocate(position, mpEnd, ++pNewEnd);
        this->DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
}
struct Element28 {
    uint32_t d[7];
    Element28(const Element28& x);                                   // 0x440ff0
};
struct Entry32 {
    uint32_t mKey;
    Element28 mValue;
};
struct EntryFixedVector : public eastl::vector_s004b_5690<Entry32, eastl::fixed_vector_allocator> {
    uint32_t mBuffer[(0x118 - 0x14) / 4];
    EntryFixedVector(const EntryFixedVector& x);                     // 0x4b62a0
    EntryFixedVector& operator=(const EntryFixedVector& x)
    {
        ScratchSlots<6>();
        if (this != &x) {
            erase(mpBegin, mpEnd);
            assign(x.begin(), x.end());
        }
        return *this;
    }
};
struct Flag { bool mbValue; };
struct Record11c {
    EntryFixedVector mEntries;
    Flag mFlag;
    Record11c(const Record11c& x) : mEntries(x.mEntries), mFlag(x.mFlag) { ScratchSlots<5>(); }
    Record11c& operator=(const Record11c& x);
};
namespace SP {
class cPropertyList_s004b_5690 { public:
    virtual int AddRef();
    virtual int Release();
};
}
namespace EA {
template<class T> class AutoRefCount_s004b_5690 { public:
    T* mpObject;
    AutoRefCount_s004b_5690(const AutoRefCount_s004b_5690& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s004b_5690& operator=(const AutoRefCount_s004b_5690& x) { return operator=(x.mpObject); }
    AutoRefCount_s004b_5690& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
}
namespace eastl {
 template<> struct has_trivial_relocate<EA::AutoRefCount_s004b_5690<SP::cPropertyList_s004b_5690> > : public true_type {}; 
}
namespace eastl {
template <typename T> struct less_s004b_5690 { bool operator()(const T& a, const T& b) const { return a < b; } };
}
namespace eastl {
template <typename T> struct use_self_s004b_5690 { const T& operator()(const T& x) const { return x; } };
}
namespace eastl {
template <typename Pair> struct use_first_s004b_5690 { const typename Pair::first_type& operator()(const Pair& x) const { return x.first; } };
}
namespace eastl {
template <typename T1, typename T2> struct pair_s004b_5690 {
    typedef T1 first_type;
    T1 first;
    T2 second;
    pair_s004b_5690(const T1& x, const T2& y) : first(x), second(y) {}
};
}
namespace eastl {
struct rbtree_node_base_s004b_5690 {
    rbtree_node_base_s004b_5690* mpNodeRight;
    rbtree_node_base_s004b_5690* mpNodeLeft;
    rbtree_node_base_s004b_5690* mpNodeParent;
    char mColor;
};
}
namespace eastl {
template <typename Value> struct rbtree_node_s004b_5690 : public rbtree_node_base_s004b_5690 {
    Value mValue;
};
}
namespace eastl {
template <typename Value>
struct rbtree_iterator_s004b_5690 {
    typedef rbtree_node_s004b_5690<Value> node_type;
    node_type* mpNode;
    explicit rbtree_iterator_s004b_5690(const node_type* pNode);                // 0x566c50
    rbtree_iterator_s004b_5690(const rbtree_iterator_s004b_5690& x);                       // 0x5673e0
    rbtree_iterator_s004b_5690& operator++();                                   // 0x422c50
    Value& operator*() const { return mpNode->mValue; }
};
}
namespace eastl {
rbtree_node_base_s004b_5690* __cdecl RBTreeDecrement(const rbtree_node_base_s004b_5690* pNode);                                     // 0x9215c0
}
namespace eastl {
void __cdecl RBTreeInsert(rbtree_node_base_s004b_5690* pNode, rbtree_node_base_s004b_5690* pNodeParent, rbtree_node_base_s004b_5690* pNodeAnchor, int insertionSide);  // 0x9216a0
}
namespace eastl {
enum RBTreeSide { kRBTreeSideLeft, kRBTreeSideRight };
}
namespace eastl {
class allocator_s004b_5690 { public:
    void deallocate(void* p, uint32_t n) { void* pBlock = p; EASTL_allocator_deallocate(pBlock); }
};
}
namespace eastl {
void* __cdecl allocate_memory(allocator_s004b_5690& a, uint32_t n, uint32_t alignment, uint32_t alignmentOffset);   // 0x42dee0
}
namespace eastl {
template <typename Key, typename Value, typename Compare, typename ExtractKey>
class rbtree_s004b_5690 {
public:
    typedef rbtree_node_s004b_5690<Value> node_type;
    typedef rbtree_iterator_s004b_5690<Value> iterator;
    typedef Value value_type;
    typedef Key key_type;
    typedef ExtractKey extract_key;
    typedef allocator_s004b_5690 allocator_type;
    typedef eastl::pair_s004b_5690<iterator, bool> insert_return_type;

    Compare mCompare;
    rbtree_node_base_s004b_5690 mAnchor;
    uint32_t mnSize;
    allocator_type mAllocator;

    rbtree_s004b_5690(const allocator_type& allocator_s004b_5690);
    void reset()
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = kRBTreeColorRed;
        mnSize = 0;
    }
    enum { kRBTreeColorRed = 0 };

    iterator lower_bound(const key_type& key);
    iterator DoInsertValue(iterator position, const value_type& value, true_type);
    insert_return_type DoInsertValue(const value_type& value, true_type);
    insert_return_type insert(const value_type& value) { return DoInsertValue(value, true_type()); }
    iterator DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft);
    node_type* DoCreateNode(const value_type& value);
    node_type* DoAllocateNode() { return (node_type*)allocate_memory(mAllocator, sizeof(node_type), 4, 0); }
    void DoFreeNode(node_type* pNode)
    {
        pNode->~node_type();
        ScratchSlots<9>();
        mAllocator.deallocate(pNode, sizeof(node_type));
    }
    void DoNuke(node_type* pNode);
};
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::insert_return_type rbtree_s004b_5690<K, V, C, E>::DoInsertValue(const value_type& value, true_type)
{
    extract_key extractKey;
    node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
    node_type* pLowerBound = (node_type*)&mAnchor;
    node_type* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = mCompare(extractKey(value), extractKey(pCurrent->mValue));
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (node_type*)pCurrent->mpNodeLeft;
        else
            pCurrent = (node_type*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (node_type*)mAnchor.mpNodeLeft)
            pLowerBound = (node_type*)RBTreeDecrement(pLowerBound);
        else {
            const iterator itResult(DoInsertValueImpl(pLowerBound, value, false));
            return insert_return_type(itResult, true);
        }
    }

    if (mCompare(extractKey(pLowerBound->mValue), extractKey(value))) {
        const iterator itResult(DoInsertValueImpl(pParent, value, false));
        return insert_return_type(itResult, true);
    }

    return insert_return_type(iterator(pLowerBound), false);
}
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::iterator rbtree_s004b_5690<K, V, C, E>::DoInsertValueImpl(node_type* pNodeParent, const value_type& value, bool bForceToLeft)
{
    RBTreeSide side;
    extract_key extractKey;

    if (bForceToLeft || (pNodeParent == &mAnchor) || mCompare(extractKey(value), extractKey(pNodeParent->mValue)))
        side = kRBTreeSideLeft;
    else
        side = kRBTreeSideRight;

    node_type* const pNodeNew = DoCreateNode(value);
    RBTreeInsert(pNodeNew, pNodeParent, &mAnchor, side);
    mnSize++;

    return iterator(pNodeNew);
}
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::node_type* rbtree_s004b_5690<K, V, C, E>::DoCreateNode(const value_type& value)
{
    node_type* const pNode = DoAllocateNode();
    ::new(&pNode->mValue) value_type(value);
    return pNode;
}
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
rbtree_s004b_5690<K, V, C, E>::rbtree_s004b_5690(const allocator_type& allocator_s004b_5690)
    : mAnchor(), mnSize(0)
{
    reset();
}
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::iterator rbtree_s004b_5690<K, V, C, E>::lower_bound(const key_type& key)
{
    extract_key extractKey;
    node_type* pCurrent = (node_type*)mAnchor.mpNodeParent;
    node_type* pRangeEnd = (node_type*)&mAnchor;
    while (pCurrent) {
        if (!mCompare(extractKey(pCurrent->mValue), key)) {
            pRangeEnd = pCurrent;
            pCurrent = (node_type*)pCurrent->mpNodeLeft;
        } else
            pCurrent = (node_type*)pCurrent->mpNodeRight;
    }
    return iterator(pRangeEnd);
}
}
namespace eastl {
template <typename K, typename V, typename C, typename E>
typename rbtree_s004b_5690<K, V, C, E>::iterator rbtree_s004b_5690<K, V, C, E>::DoInsertValue(iterator position, const value_type& value, true_type)
{
    extract_key extractKey;
    if ((position.mpNode != mAnchor.mpNodeRight) && (position.mpNode != &mAnchor)) {
        iterator itNext(position);
        ++itNext;
        if (mCompare(extractKey(*position), extractKey(value))) {
            if (mCompare(extractKey(value), extractKey(*itNext))) {
                if (position.mpNode->mpNodeRight)
                    return DoInsertValueImpl(itNext.mpNode, value, true);
                return DoInsertValueImpl(position.mpNode, value, false);
            }
        }
        return insert(value).first;
    }
    if (mnSize && mCompare(extractKey(((node_type*)mAnchor.mpNodeRight)->mValue), extractKey(value)))
        return DoInsertValueImpl((node_type*)mAnchor.mpNodeRight, value, false);
    return insert(value).first;
}
}
struct NukeMapped { ~NukeMapped(); uint32_t d[3]; };
typedef eastl::pair_s004b_5690<const uint32_t, NukeMapped> NukePair;
typedef eastl::rbtree_s004b_5690<uint32_t, NukePair, eastl::less_s004b_5690<uint32_t>, eastl::use_first_s004b_5690<NukePair> > NukeTree;
struct Key16 {
    float x, y, z, w;
    Key16(const Key16& k) : x(k.x), y(k.y), z(k.z), w(k.w) {}
    bool operator<(const Key16& k) const;                            // 0x4b52b0
};
typedef eastl::rbtree_s004b_5690<Key16, Key16, eastl::less_s004b_5690<Key16>, eastl::use_self_s004b_5690<Key16> > Key16Tree;
struct Mapped0 { uint32_t d[4]; };
typedef eastl::pair_s004b_5690<const uint32_t, Mapped0> Pair0;
typedef eastl::rbtree_s004b_5690<uint32_t, Pair0, eastl::less_s004b_5690<uint32_t>, eastl::use_first_s004b_5690<Pair0> > UIntTree0;
template void NukeTree::DoNuke(NukeTree::node_type*);
struct Deletable {
    virtual void _v0();
    virtual void Destroy();
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
struct DeletablePtr {
    Deletable* p;
    ~DeletablePtr() { if (p) p->Destroy(); }
    static void operator delete(void* q) { EASTL_allocator_deallocate(q); }
};
struct DeletablePtrRange {
    void DestroyRange(DeletablePtr* first, DeletablePtr* last);
};
// ---- items of slice s004b5690 end

// @ 0x004b24c0
SP::cSPEditorPaintTheme_s004b_2320::cSPEditorPaintTheme_s004b_2320()
{
    mpVtbl0 = &g_vtbl_EditorResource;
    mpVtbl0 = &g_vtbl_BakeSprites;
    mpVtbl1 = &g_vtbl_ContentValidator;
    mRefCount = 0;
    mpVtbl0 = &g_vtbl_PaintTheme0;
    mpVtbl1 = &g_vtbl_PaintTheme1;
    mPropTheme.Ctor();
    mModelTheme.Ctor(&mSourceRef);
    mPropThemeID = 0;
    mResourceType = 0;
    mpClosestBegin = 0;
    mpClosestEnd = 0;
    mpClosestCap = 0;
    for (int i = 0; i < 3; i++) {
    }
}

// @ 0x004b25e0
SP::cSPEditorPaintTheme_s004b_2320::~cSPEditorPaintTheme_s004b_2320()
{
    mpVtbl0 = &g_vtbl_PaintTheme0;
    mpVtbl1 = &g_vtbl_PaintTheme1;
    for (void** p = (void**)mpClosestBegin; p < (void**)mpClosestEnd; p++) {
    }
    FUN_00425990(&mpClosestBegin);
    mModelTheme.Nuke(*(void**)((char*)&mModelTheme + 0xc));
    for (char* p = (char*)mPropTheme.mpBegin; p < (char*)mPropTheme.mpEnd; p += 0x20) {
    }
    FUN_00455290(&mPropTheme);
    mpVtbl1 = &g_vtbl_ContentValidator;
    mpVtbl0 = &g_vtbl_EditorResource;
}

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

// @ 0x004b2800
uint32_t SP::cSPEditorPaintTheme_s004b_2320::ReadFromAsset(Asset* asset)
{
    Reset();
    if (asset != 0) {
        void* view = FUN_004bb860(*(void**)((char*)asset + 0x58));
        if (FUN_004bbe90((uint32_t)view)) {
            if (!FUN_004bbe90((uint32_t)mSourceRef))
                return 0;
            mResourceType = (uint32_t)asset;
            for (int i = 0; i < 3; i++) {
                cSPColorRGB_s004b_2320 col;
                asset->GetColor(i, &col);
                mSkinColors[i] = col;
                mSkinEffects[i] = asset->GetEffect(i);
                mSkinEffectSeeds[i] = asset->GetSeed(i);
            }
            return 1;
        }
        if (FUN_004bbed0(view)) {
            if (!FUN_004bbed0((void*)mSourceRef))
                return 0;
            mResourceType = (uint32_t)asset;
            int n = asset->ModelCount();
            for (int i = 0; i < n; i++)
                FUN_004b3c20((int)asset->ModelAt(i));
            InitClosestRegions((void*)mSourceRef, (void*)mResourceType);
            return 1;
        }
    }
    return 0;
}

// @ 0x004b29b0
bool SP::cSPEditorPaintTheme_s004b_2320::ReadFromProp2(int prop, char useColors)
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
bool SP::cSPEditorPaintTheme_s004b_2320::ReadFromProp(uint32_t prop)
{
    PaintPropRef ref;

    void* colors = 0;
    void* colorA = 0;
    void* colorB = 0;
    int count = 0;

    mModelTheme.Nuke(*(void**)((char*)&mModelTheme + 0xc));
    mModelTheme.ResetFast();
    mPropTheme.Erase(mPropTheme.mpBegin, mPropTheme.mpEnd);

    PropMgr* mgr = (PropMgr*)SP_PropertyManager();
    mgr->GetPropertyList(prop, DAT_015d6cc8, (void**)ref.AsPPVoidParam());
    if (ref.mpRef == 0)
        return false;

    if (ref.mpRef->Has(0xb0e066a7)) {
        void* p = ref.mpRef->Get(0xb0e066a7);
        count = (*(uint16_t*)((char*)p + 0x10) & 0x30)
                    ? *(int*)((char*)p + 8)
                    : ((*(int16_t*)((char*)p + 0x12) != 0) ? 1 : 0);
        colors = (*(uint16_t*)((char*)p + 0x10) & 0x30)
                     ? *(void**)p
                     : ((*(int16_t*)((char*)p + 0x12) != 0) ? p : 0);
    }
    if (ref.mpRef->Has(0xb0e066a8)) {
        void* p = ref.mpRef->Get(0xb0e066a8);
        colorA = (*(uint16_t*)((char*)p + 0x10) & 0x30)
                     ? *(void**)p
                     : ((*(int16_t*)((char*)p + 0x12) != 0) ? p : 0);
    }
    if (ref.mpRef->Has(0xb0e066a9)) {
        void* p = ref.mpRef->Get(0xb0e066a9);
        colorB = (*(uint16_t*)((char*)p + 0x10) & 0x30)
                     ? *(void**)p
                     : ((*(int16_t*)((char*)p + 0x12) != 0) ? p : 0);
    }

    int i = 0;
    while (i < count) {
        uint32_t v = *(uint32_t*)((char*)colors + i * 0xc);
        if (v == 0 || v == 0xe960add1) {
            i++;
            continue;
        }
        // colorB is evaluated first and the payload's second vector is constructed in place:
        // that is the original's evaluation order (see the 0x004b2bb0 disassembly).
        PropEntry* eb = (PropEntry*)((char*)colorB + i * 0xc);
        PropEntry* ea = (PropEntry*)((char*)colorA + i * 0xc);
        Trans t;
        t.f0 = v;
        t.a[0] = ea->x;
        t.a[1] = ea->y;
        t.a[2] = ea->z;
        new ((void*)&t.b) Vec3_s004b_2320(*(Vec3_s004b_2320*)&eb->x);
        uint32_t* dst = (uint32_t*)mPropTheme.Insert(&i);
        *(Trans*)dst = t;
        i++;
    }

    mPropThemeID = (uint32_t)prop;
    InitClosestRegions((void*)mSourceRef, (void*)mSourceRef);
    return true;
}

// @ 0x004b2f80
void SP::cSPEditorPaintTheme_s004b_2320::WriteToProp(Asset* asset, int resourceType)
{
    if (asset == 0)
        return;
    void* view = FUN_004bb860(*(void**)((char*)asset + 0x58));
    if (FUN_004bbe90((uint32_t)view)) {
        for (int i = 0; i < 3; i++) {
            if (mSkinEffects[i] == 0)
                continue;
            if (FUN_0041dd30(&DAT_015d6b98, &mSkinColors[i]))
                FUN_004add30(asset, i, &mSkinColors[i]);
            FUN_004adcf0(asset, i, mSkinEffects[i]);
            FUN_004add10(asset, i, mSkinEffectSeeds[i]);
        }
    } else if (FUN_004bbed0(view)) {
        PropObj* list = 0;
        if (resourceType != -1) {
            PropMgr* mgr = (PropMgr*)SP_PropertyManager();
            if (list)
                list->Release();
            mgr->GetPropertyList(resourceType, DAT_015d6f64, (void**)&list);
        }
        FUN_004ae250(asset);
        int n = asset->ModelCount();
        for (int i = 0; i < n; i++) {
            void* model = asset->ModelAt(i);
            ApplyToAsset((int)model, (int)list);
        }
        FUN_004ae250(asset);
        if (list)
            list->Release();
    }
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
    return (char)(i - limit);   // always 0 here; keeps the tail in a full-width eax like the /Od original
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
        void* r = mModelTheme.FUN_004b5080(&local2);
        ((SP::PaintVector_s004b_33e0*)r)->FUN_004b4fa0((void*)(model + 0x4c8));
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

// @ 0x004b5690
template void eastl::vector_s004b_5690<Record11c, eastl::sp_vector_allocator_s004b_5690>::DoInsertValue(Record11c*, const Record11c&)
;

// @ 0x004b5980
template eastl::rbtree_s004b_5690<Key16, Key16, eastl::less_s004b_5690<Key16>, eastl::use_self_s004b_5690<Key16> >::rbtree_s004b_5690(const eastl::allocator_s004b_5690&)
;

// @ 0x004b5a20
template void Key16Tree::reset()
;

// @ 0x004b5a60
namespace eastl {
template <typename K, typename V, typename C, typename E> void rbtree_s004b_5690<K, V, C, E>::DoNuke(node_type* pNode)
{
    while (pNode) {
        DoNuke((node_type*)pNode->mpNodeRight);
        node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}
}  // namespace eastl

// @ 0x004b5e90
template UIntTree0::iterator UIntTree0::lower_bound(const uint32_t&)
;

// @ 0x004b5fb0
void DeletablePtrRange::DestroyRange(DeletablePtr* first, DeletablePtr* last)
{
    for (; first < last; ++first)
        first->~DeletablePtr();
}

// @ 0x004babe0
void* __fastcall FUN_004babe0(void* self, void* unused, void* a, char c)
{
    FUN_004f3de0(a, self, DAT_015da860, DAT_015da864, DAT_015da868, DAT_015da86c, c);
    return a;
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

// @ 0x004bbed0
bool FUN_004bbed0(uint32_t type)
{
    switch (type) {
    case 0x2399be55:
    case 0x24682294:
    case 0x476a98c7:
        return true;
    default:
        return false;
    }
}
