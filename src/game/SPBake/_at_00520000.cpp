// src/game/SPBake/_at_00520000.cpp -- migrated from slice(s) s0052c230, s0052b340, s0052a400, s005296b0, s00527a70, s005266f0, s00525360 by tools/migrate/rewrite.py
// Object file: SPBake/_at_00520000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPSkinner/cRTTBuffer.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cICommand.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380

// ---- items of slice s00525360 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}
extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380
struct sp_vector_allocator {
    uint32_t mFlags[2];
    void* allocate(uint32_t n, uint32_t align, uint32_t ofs);
};
void* EASTL_Allocate(sp_vector_allocator* a, uint32_t n, uint32_t align, uint32_t ofs);  // 0x0042dee0
struct IRefObj {
    virtual void AddRef();
    virtual void Release();
};
template <typename T> struct intrusive_ptr {
    T* mp;
    intrusive_ptr() : mp(0) {}
    ~intrusive_ptr() { if (mp) mp->Release(); }
};
struct PoolNode {
    PoolNode* mpNext;
};
struct PooledObj {
    PoolNode* mpNext;
    uint32_t pad04[0x12];
    int mRefCount;                  // +0x4c
    static PoolNode* sFreeList;     // 0x015de2b0
    static void Free(void* p)
    {
        PoolNode* const node = (PoolNode*)p;
        node->mpNext = sFreeList;
        sFreeList = node;
    }
    void AddRef() { mRefCount++; }
    void Release()
    {
        if (--mRefCount > 0)
            return;
        Free(this);
    }
};
struct PoolPtr {
    PooledObj* mp;
    PoolPtr() : mp(0) {}
    ~PoolPtr();
    PoolPtr& operator=(PooledObj* p);
};
struct Elem38 {
    uint32_t data[11];
    intrusive_ptr<IRefObj> mpObj;   // +0x2c
    uint32_t m30;
    PoolPtr mpPooled;               // +0x34
    Elem38() {}
    ~Elem38();
};
template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    ~VectorBase();      // declined inline in the original
};
struct Elem40 {
    uint32_t data[0x10];
    Elem40() {}
};
struct VectorElem40 : VectorBase<Elem40> {
    typedef Elem40 value_type;
    typedef uint32_t size_type;
    VectorElem40(const VectorElem40& x);                                         // 0x00527150
    ~VectorElem40();                                                              // 0x0045d750
    void swap(VectorElem40& x);                                                   // 0x005271f0
    void resize(size_type n);
    void set_capacity(size_type n);
    void DoInsertValues(Elem40* position, size_type n, const value_type& value);  // 0x00527f30
    Elem40* erase(Elem40* first, Elem40* last);                                   // 0x00476a40
    void insert(Elem40* position, size_type n, const value_type& value)
    {
        DoInsertValues(position, n, value);
    }
    Elem40* DoAllocate(size_type n)
    {
        return n ? (Elem40*)EASTL_Allocate(&mAllocator, n * sizeof(Elem40), 4, 0) : 0;
    }
    void DoFree(Elem40* p, size_type n)
    {
        if (p && ((uint32_t*)p)[-1]) {
            void* q = p;
            EASTL_allocator_deallocate(q);
        }
    }
};
Elem40* uninitialized_copy_ptr(Elem40* first, Elem40* last, Elem40* result);   // 0x005273a0
// ---- items of slice s00525360 end

// ---- items of slice s005266f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, uint32_t);
#pragma intrinsic(memcpy)
template <int N> inline void ScratchSlots_s0052_66f0() { uint32_t slots[N]; }
template <> inline void ScratchSlots_s0052_66f0<0>() {}
inline void* operator new(unsigned int, void* p) { return p; }
struct sp_vector_allocator_s0052_66f0 {
    const char* mpName;
    uint32_t mFlags;
};
void* EA_Allocate(void* allocator, uint32_t n, uint32_t align, uint32_t offset);  // 0x0042dee0
void  EA_Free(void* p);                                                            // 0x00f47380
struct PooledObj_s0052_66f0 {
    uint32_t pad00[0x13];
    int mRefCount;              // +0x4c
    void AddRef() { mRefCount++; }
};
struct Vec2f {
    float x, y;
    Vec2f() {}
    Vec2f(const Vec2f& o) { x = o.x; y = o.y; }
};
struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(const Vec3f& o) { x = o.x; y = o.y; z = o.z; }
};
struct ObjPtr {
    IRefObj* mp;
    ObjPtr() : mp(0) {}
    ObjPtr(const ObjPtr& o) : mp(o.mp) { if (mp) mp->AddRef(); }
};
struct PoolPtr2 {
    PooledObj_s0052_66f0* mp;
    PoolPtr2() : mp(0) {}
    PoolPtr2(const PoolPtr2& o) : mp(o.mp) { if (mp) mp->AddRef(); }
};
struct Elem38_s0052_66f0 {                 // 0x38 bytes
    uint32_t m00;               // +0x00
    Vec2f v04;                  // +0x04
    Vec3f v0c;                  // +0x0c
    float v18;                  // +0x18
    uint32_t m1c, m20, m24, m28;
    ObjPtr mpObj;               // +0x2c
    uint32_t m30;               // +0x30
    PoolPtr2 mpPooled;          // +0x34
    Elem38_s0052_66f0() {}
    Elem38_s0052_66f0(const Elem38_s0052_66f0& x);            // 0x00527440
    Elem38_s0052_66f0& operator=(const Elem38_s0052_66f0&);   // 0x005218e0
    ~Elem38_s0052_66f0();                          // 0x00526660
};
Elem38_s0052_66f0* UninitCopy38(Elem38_s0052_66f0* first, Elem38_s0052_66f0* last, Elem38_s0052_66f0* dest);      // 0x005279c0
template <typename T> struct VectorBase_s0052_66f0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0052_66f0 mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    uint32_t capacity() const { return (uint32_t)(mpCapacity - mpBegin); }
    T* DoAllocate(uint32_t n) { return n ? (T*)EA_Allocate(&mAllocator, n * sizeof(T), 0, 0) : 0; }
    void DoFree(T* p, uint32_t) { if (p && ((uint32_t*)p)[-1]) { void* q = p; EA_Free(q); } }
};
template <typename T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}
template <class In, class Out> __forceinline Out copy_impl(In first, In last, Out result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}
template <class In, class Out> __forceinline Out copy(In first, In last, Out result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_impl(first, last, result);
}
template <class Bi1, class Bi2> __forceinline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 result)
{
    while (last != first)
        *--result = *--last;
    return result;
}
template <class Bi1, class Bi2> __forceinline Bi2 copy_backward(Bi1 first, Bi1 last, Bi2 result)
{
    const bool bIsMove = false;
    const bool bCanMemmove = false;
    const bool bIsPod = false;
    return copy_backward_impl(first, last, result);
}
struct VectorElem38 : VectorBase_s0052_66f0<Elem38_s0052_66f0> {
    typedef Elem38_s0052_66f0 value_type;
    typedef uint32_t size_type;
    Elem38_s0052_66f0* erase(Elem38_s0052_66f0* first, Elem38_s0052_66f0* last);                                  // 0x005266f0
    void DoInsertValue(Elem38_s0052_66f0* position, const Elem38_s0052_66f0& value);                   // 0x005267c0
    void DoInsertValues(Elem38_s0052_66f0* position, size_type n, const Elem38_s0052_66f0& value);     // 0x00527570
    void insert(Elem38_s0052_66f0* position, size_type n, const Elem38_s0052_66f0& value) { DoInsertValues(position, n, value); }
    VectorElem38& operator=(const VectorElem38& x);
};
struct Elem18 {
    uint32_t data[6];
};
Elem18* UninitCopy18(Elem18* first, Elem18* last, Elem18* dest);      // 0x00527b70
Elem18* AllocAndCopy18(uint32_t n, Elem18* first, Elem18* last);      // 0x00527c10
struct VectorElem18 : VectorBase_s0052_66f0<Elem18> {
    typedef Elem18 value_type;
    typedef uint32_t size_type;
    VectorElem18& operator=(const VectorElem18& x);
};
struct Elem1c {
    uint32_t data[7];
};
Elem1c* UninitCopy1c(Elem1c* first, Elem1c* last, Elem1c* dest);      // 0x00527a70
Elem1c* AllocAndCopy1c(uint32_t n, Elem1c* first, Elem1c* last);      // 0x00527b10
struct VectorElem1c : VectorBase_s0052_66f0<Elem1c> {
    typedef Elem1c value_type;
    typedef uint32_t size_type;
    VectorElem1c& operator=(const VectorElem1c& x);
};
Elem40* UninitCopy40(Elem40* first, Elem40* last, Elem40* dest);      // 0x00528330
struct VectorElem40_s0052_66f0 : VectorBase_s0052_66f0<Elem40> {
    typedef Elem40 value_type;
    typedef uint32_t size_type;
    VectorElem40_s0052_66f0(const VectorElem40_s0052_66f0& x);                              // 0x00527150
};
struct DequeElem48 {
    Elem40** mpPtrArray;
    uint32_t mnPtrArraySize;
    struct Iterator {
        void* mpCurrent;
        void* mpBegin;
        void* mpEnd;
        void** mpCurrentArrayPtr;
        void DoFreeMap(void* p);   // 0x00515170 (this = &mItBegin)
    };
    Iterator mItBegin;       // +0x08
    Iterator mItEnd;         // +0x18
    void FreeNode(void* p);  // 0x00569260
    void DoPopFront();       // 0x00527110
};
struct Alloc4 {
    uint32_t mFlags;
};
struct FixedVec8 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    Alloc4 mAllocator;
    void* mpInlineBuffer;    // +0x10
    void Free();             // 0x00526a40
};
// ---- items of slice s005266f0 end

// ---- items of slice s00527a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots_s0052_7a70() { uint32_t slots[N]; }
template <> inline void ScratchSlots_s0052_7a70<0>() {}
struct sp_vector_allocator_s0052_7a70 { const char* mpName; uint32_t mFlags; };
struct Matrix33 {                                  // 0x24 bytes
    float m[9];
    Matrix33() {}
    Matrix33(const Matrix33& o) { Assign(o); }
    void Assign(const Matrix33& o);                // 0x0041cb40
};
struct B4 {
    uint8_t a, b, c, d;
    B4() {}
    B4(const B4& o) { a = o.a; b = o.b; c = o.c; d = o.d; }
};
struct Elem40_s0052_7a70 {
    B4 m00;                     // +0x00
    Vec3f v04;                  // +0x04
    Matrix33 mat;               // +0x10
    float v34, v38, v3c;        // +0x34
    Elem40_s0052_7a70() {}
    Elem40_s0052_7a70(const Elem40_s0052_7a70& x);    // 0x00528610
};
template <typename T> struct gi {
    T* it;
    explicit gi(T* x) : it(x) {}
    gi& operator++() { ++it; return *this; }
    T& operator*() const { return *it; }
    T* base() const { return it; }
};
template <typename T> inline bool operator!=(const gi<T>& a, const gi<T>& b) { return a.it != b.it; }
struct Elem1c_s0052_7a70 { uint32_t d[7]; };   // 0x1c
struct Elem18_s0052_7a70 { uint32_t d[6]; };   // 0x18
template <typename T> struct VectorBase_s0052_7a70 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0052_7a70 mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    uint32_t capacity() const { return (uint32_t)(mpCapacity - mpBegin); }
    void DoFree(T* p, uint32_t) { if (p && ((uint32_t*)p)[-1]) { void* q = p; EA_Free(q); } }
};
Elem40_s0052_7a70* UninitCopy40_s0052_7a70(Elem40_s0052_7a70* first, Elem40_s0052_7a70* last, Elem40_s0052_7a70* dest);   // 0x00528330
Elem40_s0052_7a70* AllocAndCopy40(uint32_t n, Elem40_s0052_7a70* first, Elem40_s0052_7a70* last);   // 0x005286c0
struct VectorElem40_s0052_7a70 : VectorBase_s0052_7a70<Elem40_s0052_7a70> {
    typedef Elem40_s0052_7a70 value_type;
    typedef uint32_t size_type;
    VectorElem40_s0052_7a70() {}
    VectorElem40_s0052_7a70(const VectorElem40_s0052_7a70& x);
    VectorElem40_s0052_7a70& operator=(const VectorElem40_s0052_7a70& x);                       // 0x00527c70
    void DoInsertValues(Elem40_s0052_7a70* position, size_type n, const Elem40_s0052_7a70& value);  // 0x00527f30
    void insert(Elem40_s0052_7a70* position, size_type n, const Elem40_s0052_7a70& value) { DoInsertValues(position, n, value); }
};
void* __fastcall FixedAlloc8(void* self, int, uint32_t n, void* first, void* last);  // 0x0056a0e0 (thiscall, ret 0xc)
void* FixedUninit8(void* first, void* last, void* dest);     // 0x004d0960
struct FixedVec8_s0052_7a70 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    Alloc4 mAllocator;
    void* mpInlineBuffer;    // +0x10
    // retail pops three dwords (ret 0xc) but only ever reads [ebp+8] and [ebp+0xc]
    void assign(void* first, void* last, void* unused);   // 0x005283d0
};
// ---- items of slice s00527a70 end

// ---- items of slice s005296b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
float* Vector3Scale(float* out, float* a, float* b);                   // 0x0041de40
// ---- items of slice s005296b0 end

// ---- items of slice s0052a400 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t DAT_013f18d0[3];
extern uint8_t DAT_013f18d8[3];
extern float   _DAT_0150cb00;
extern "C" const float g_zero0;     // 0x01485378
extern uint8_t DAT_013f1f10[64];
void  ClustersAndEdges(void* mesh, int flags);                     // 0x00735470 / CreateClustersAndEdges
int   MeshOp1(void* mesh);                                         // 0x00733ed0
int   MeshOp2(void* mesh, int, int, int, int);                     // 0x0071ddc0
int   MeshOp3(void* mesh, int, int*, int*, int, int*, int);           // 0x0071ded0
void  MeshOp4(void* mesh);                                         // 0x00736b00
int   MeshOp5(void* mesh);                                         // 0x0071e230
void* CreateRaster(int w, int h, int a, int b, int c);             // SP::CreateRaster
int   RasterFill(void* r, int);                                    // rw::graphics::Raster::Fill
void  RasterMip(void* r, void* data, int);                         // D3D9GetStreamedMipLevelSize
void* TextureManager();                                            // 0x0067dd60
void  ReleaseRaster(void*);                                        // 0x00402420
void  FUN_00473810(int);
void  FUN_00473dc0(int);
void  FUN_0050d3c0(int);
void* FUN_0044e460(void* out, void* a, void* b);
void* V3NormalizeSafe(void* out, void* in);                        // SP::normalized_safe
int   FUN_00467980(int);
void  FUN_004cd3c0(int);
void  FUN_00533680(void*, void*, char);
struct BoneWeightEntry {
    unsigned char   bone;       // +0x00
    unsigned char   pad[3];
    float           weight;     // +0x04
};
struct BoneWeightList {
    BoneWeightEntry* mpBegin;       // +0x00
    int              mUnused04;     // +0x04
    int              mUnused08;     // +0x08
    int              mUnused0c;     // +0x0c
    int              mUnused10;     // +0x10
    int              mCount;        // +0x14
    void Accum(int param_2, float param_3);     // 0x0052b060
    void Normalize(float param_2);              // 0x0052b170
    void CopyTop(int param_2);                  // 0x0052b220
};
void  FUN_0052ae30(uint32_t, const void*);
struct VectorU32 {
    bool empty() const;                        // 0x00526430
};
struct TexMgr {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
    virtual void* v19(int, int, void*, int);      // +0x4c
};
struct PairVec;
struct VectorIF {
    void  FUN_004cef00(void* end, uint32_t n, const void* value);  // vector::_Insert_n
    void* FUN_00530c80(void* first, void* last);                   // vector::erase
};
struct PairVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mFlags[2];
    void resize(uint32_t n, const void* value);   // 0x0052ae30
};
// ---- items of slice s0052a400 end

// ---- items of slice s0052b340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_150cb04;                                                             // 0150cb04
struct Vec3 { float x, y, z; };
Vec3 __cdecl Vec3Sub(const Vec3& a, const Vec3& b);                 // 0041db10
float __cdecl VectorLength(const Vec3* v);                          // 0040ae50
void __cdecl MakeBoneTip(Vec3* out, const Vec3* p, const Vec3* q, float r);   // 004a5c70
float __cdecl GetExactSkinRadiusFromVertebra(float v);              // 004a5b70 (SP::EditorUtils)
struct Row {                       // one output row: four bone bytes and four weights (0x14 bytes)
    unsigned char bone[4];
    float         weight[4];
};
struct PairIF { int index; float weight; };
struct Joint {                     // 0x34 bytes
    Vec3      pos;                 // +0x00
    unsigned* childBegin;          // +0x0c
    unsigned* childEnd;            // +0x10
    unsigned* childCap;            // +0x14
    char      pad[0x34 - 0x18];
};
struct Bone {                      // 0x8c bytes
    char  pad0[0xb];
    unsigned char kind;            // +0x0b
    char  pad1[0x2c - 0xc];
    float radius;                  // +0x2c
    char  pad2[0x48 - 0x30];
    Vec3  a;                       // +0x48
    Vec3  b;                       // +0x54
    char  pad3[0x8c - 0x60];
};
struct Segment { int a, b; };
struct SkeletonObj { char pad[0x98]; Bone* boneBegin; Bone* boneEnd; };            // +0x98 / +0x9c
struct PointSet    { char pad[8]; Vec3* ptBegin; Vec3* ptEnd; };                    // +8 / +0xc
struct SegVec      { Segment* begin; Segment* end; };
struct JointVec    { Joint* begin; };
struct RemapTable  { unsigned* table; };
struct SpAllocator { char c; SpAllocator(const char* name); };                      // 00429360
struct RowVec {                                                                     // vector<Row>
    Row* mpBegin; Row* mpEnd; Row* mpCap; SpAllocator mAlloc;
    RowVec(const char* n) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(n) {}
    void resize(unsigned n);                                                        // 004cd690
    void Free();                                                                    // 0050ea50
    ~RowVec() { for (Row* p = mpBegin; p < mpEnd; ++p) {} Free(); }
};
struct FloatVec {                                                                   // fixed_vector<float, 65> (0x11c bytes)
    float* mpBegin; float* mpEnd; float* mpCap; char mAlloc[4];
    int    mPoolPad;                                                                // +0x10
    int    mOverflowFlag;                                                           // +0x14 (read by Free as begin[-1])
    float  mBuffer[65];                                                             // +0x18
    void Construct(const char* n);                                                  // 00540470
    void Init();                                                                    // 0052c1f0
    void resize(unsigned n, const float* v);                                        // 0052c380
    void Free();                                                                    // 00425990
    ~FloatVec() { for (float* p = mpBegin; p < mpEnd; ++p) {} Free(); }
};
struct PairVec_s0052_b340 {                                                                    // fixed_vector<PairIF, 32> (0x118 bytes)
    PairIF* mpBegin; PairIF* mpEnd; PairIF* mpCap; char mAlloc[4];
    int     mPoolPad;                                                               // +0x10
    int     mOverflowFlag;                                                          // +0x14 (read by Free as begin[-1])
    PairIF  mBuffer[32];                                                            // +0x18
    void Construct(const char* n);                                                  // 00540470
    void Init();                                                                    // 004c5e70
    void erase(PairIF* first, PairIF* last);                                        // 00530c80
    void resize(unsigned n, const PairIF* v);                                       // 0052c570 0x0052ae30
    void insert(PairIF* pos, const PairIF* v);                                      // 0052c2e0
    void Free();                                                                    // 0045daf0
    ~PairVec_s0052_b340() { for (PairIF* p = mpBegin; p < mpEnd; ++p) {} Free(); }
};
struct ScratchVec {                                                                 // vector of 8-byte items
    char* mpBegin; char* mpEnd; char* mpCap; char mAlloc[4];
    void Construct(unsigned n, const char* a);                                      // 0052c230
    void Free();                                                                    // 0045daf0
    ~ScratchVec() { for (char* p = mpBegin; p < mpEnd; p += 8) {} Free(); }
};
struct WeightSource { void Query(const Vec3* pt, PairVec_s0052_b340* out); };                  // 004f9570
void __cdecl SkinBoneWeights(Row* src, Row* dst, ScratchVec* tmp, PointSet* pts, float f);   // 0052aeb0
// ---- items of slice s0052b340 end

// ---- items of slice s0052c230 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots_s0052_c230() { uint32_t slots[N]; }
template <> inline void ScratchSlots_s0052_c230<0>() {}
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                            // 0x00f473a0
struct sp_vector_allocator_s0052_c230 {
    uint32_t mFlags[2];
    sp_vector_allocator_s0052_c230() {}
};
void* EASTL_Allocate(sp_vector_allocator_s0052_c230* a, uint32_t n, uint32_t align, uint32_t ofs);  // 0x0042dee0
namespace eastl {
template <typename T1, typename T2> struct pair_s0052_c230 {
    T1 first;
    T2 second;
};
}
namespace eastl {
template <typename T, bool v> struct integral_constant {
    static const bool value = v;
};
}
namespace eastl {
typedef integral_constant<bool, false> false_type;
}
namespace eastl {
typedef integral_constant<bool, true> true_type;
}
namespace eastl {
template <typename T> struct has_trivial_constructor : public false_type {};
}
namespace eastl {
template <> struct has_trivial_constructor<float> : public true_type {};
}
namespace eastl {
template <typename T> class generic_iterator { public:     // eastl::generic_iterator<T*>
    T* mIterator;
    generic_iterator(T* const& x) : mIterator(x) {}
    T& operator*() const { return *mIterator; }
    generic_iterator& operator++()
    {
        ++mIterator;
        return *this;
    }
};
}
namespace eastl {
template <typename ForwardIterator, typename T>
void uninitialized_fill_n_impl(ForwardIterator first, uint32_t n, const T& value, false_type);   // 0x0052c8f0
}
namespace eastl {
template <typename OutputIterator, typename T> OutputIterator fill_n(OutputIterator first, uint32_t n, const T& value);
}
namespace eastl {
template <typename ForwardIterator, typename T>
inline void uninitialized_fill_n_impl(ForwardIterator first, uint32_t n, const T& value, true_type)
{
    fill_n(first, n, value);
}
}
namespace eastl {
template <typename T> inline void uninitialized_fill_n_ptr(T* first, uint32_t n, const T& value)
{
    uninitialized_fill_n_impl(generic_iterator<T>(first), n, value, has_trivial_constructor<T>());
}
}
namespace eastl {
template <typename T> inline T* fill_n_impl(T* first, uint32_t n, const T& value)
{
    for (; n-- > 0; ++first)
        *first = value;
    return first;
}
}
namespace eastl {
template <typename T> struct is_scalar : public false_type {};
}
namespace eastl {
template <> struct is_scalar<float> : public true_type {};
}
namespace eastl {
template <bool bIsScalar> struct fill_imp {
    template <typename ForwardIterator, typename T>
    static void do_fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
        for (; first != last; ++first)
            *first = value;
    }
};
}
namespace eastl {
template <> struct fill_imp<true> {
    template <typename ForwardIterator, typename T>
    static void do_fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
        const T temp(value);
        for (; first != last; ++first)
            *first = temp;
    }
};
}
namespace eastl {
template <typename ForwardIterator, typename T>
inline void fill(ForwardIterator first, ForwardIterator last, const T& value)
{
    fill_imp<is_scalar<T>::value>::do_fill(first, last, value);
}
}
namespace eastl {
template <typename T> struct VectorBase_s0052_c230 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0052_c230 mAllocator;
    VectorBase_s0052_c230(uint32_t n, const sp_vector_allocator_s0052_c230& allocator)
    {
        mpBegin = DoAllocate(n);
        mpEnd = mpBegin;
        mpCapacity = mpBegin + n;
    }
    ~VectorBase_s0052_c230();
    T* DoAllocate(uint32_t n)
    {
        return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), 4, 0) : 0;
    }
};
}
namespace eastl {
template <typename T> class vector_s0052_c230 : public VectorBase_s0052_c230<T> { public:
    typedef T value_type;
    typedef uint32_t size_type;
    vector_s0052_c230(size_type n, const sp_vector_allocator_s0052_c230& allocator);
    vector_s0052_c230(size_type n, const value_type& value, const sp_vector_allocator_s0052_c230& allocator)
        : VectorBase_s0052_c230<T>(n, allocator)
    {
        uninitialized_fill_n_ptr(mpBegin, n, value);
        mpEnd = mpBegin + n;
    }
    ~vector_s0052_c230();
    void swap(vector_s0052_c230& x);
    T* insert(T* position, const value_type& value);
    T* erase(T* first, T* last);  // 0x00621f50 (eastl::vector::erase)
    void DoInsertValue(T* position, const value_type& value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    void DoAssignValues(size_type n, const value_type& value);
};
}
namespace eastl {
template <typename T> struct erase_frame { enum { value = 6 }; };   // erase() frames of the declined
}
namespace eastl {
template <> struct erase_frame<float> { enum { value = 4 }; };       // inline expansions
}
namespace eastl {
template <typename T> void vector_s0052_c230<T>::DoAssignValues(size_type n, const value_type& value)
{
    if (n > (size_type)(mpCapacity - mpBegin)) {
        vector_s0052_c230 temp(n, value, mAllocator);
        swap(temp);
        ScratchSlots_s0052_c230<21>();
    } else if (n > (size_type)(mpEnd - mpBegin)) {
        fill(mpBegin, mpEnd, value);
        uninitialized_fill_n_ptr(mpEnd, n - (size_type)(mpEnd - mpBegin), value);
        mpEnd += n - (size_type)(mpEnd - mpBegin);
    } else {
        fill_n(mpBegin, n, value);
        ScratchSlots_s0052_c230<erase_frame<T>::value>();
        erase(mpBegin + n, mpEnd);
    }
}
}
namespace eastl {
template void vector_s0052_c230<float>::DoAssignValues(size_type n, const value_type& value);
}
namespace eastl {
struct SecondGreater {
    bool operator()(const pair_s0052_c230<int, float>& a, const pair_s0052_c230<int, float>& b) const { return a.second > b.second; }
};
}
namespace eastl {
typedef pair_s0052_c230<int, float> PairIF_s0052_c230;
}
namespace eastl {
const PairIF_s0052_c230& median(const PairIF_s0052_c230& a, const PairIF_s0052_c230& b, const PairIF_s0052_c230& c, SecondGreater compare);  // 0x00533ba0
}
namespace eastl {
PairIF_s0052_c230* get_partition(PairIF_s0052_c230* first, PairIF_s0052_c230* last, PairIF_s0052_c230 pivotValue, SecondGreater compare);
}
namespace eastl {
void adjust_heap(PairIF_s0052_c230* first, int topPosition, int heapSize, int position, PairIF_s0052_c230 value, SecondGreater compare);
}
namespace eastl {
void make_heap(PairIF_s0052_c230* first, PairIF_s0052_c230* last, SecondGreater compare);
}
namespace eastl {
void partial_sort(PairIF_s0052_c230* first, PairIF_s0052_c230* middle, PairIF_s0052_c230* last, SecondGreater compare);
}
namespace eastl {
void quick_sort_impl_helper(PairIF_s0052_c230* first, PairIF_s0052_c230* last, int kRecursionCount, SecondGreater compare);
}
namespace eastl {
template <typename T> inline void promote_heap(T* first, int topPosition, int position, T value, SecondGreater compare)
{
    for (int parentPosition = (position - 1) >> 1; (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}
}
namespace eastl {
inline void sort_heap(PairIF_s0052_c230* first, PairIF_s0052_c230* last, SecondGreater compare)
{
    for (; (last - first) > 1; --last) {
        const PairIF_s0052_c230 temp(*(last - 1));
        *(last - 1) = *first;
        adjust_heap(first, 0, (int)(last - first) - 1, 0, temp, compare);
    }
}
}
// ---- items of slice s0052c230 end

// @ 0x00526450
void VectorElem40::resize(size_type n)
{
    if (n > (size_type)(mpEnd - mpBegin))
        insert(mpEnd, n - (size_type)(mpEnd - mpBegin), value_type());
    else {
        ScratchSlots<6>();
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x005264d0
void VectorElem40::set_capacity(size_type n)
{
    if ((n == (size_type)-1) || (n <= (size_type)(mpEnd - mpBegin))) {
        if (n < (size_type)(mpEnd - mpBegin))
            resize(n);
        ScratchSlots<17>();
        VectorElem40 temp(*this);
        ScratchSlots<35>();
        swap(temp);
    } else {
        Elem40* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        const int nPrevSize = (int)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}

// @ 0x00526660
Elem38::~Elem38()
{
    ScratchSlots<2>();
}

// @ 0x005266a0
PoolPtr::~PoolPtr()
{
    if (mp)
        mp->Release();
}

// @ 0x005266f0
Elem38_s0052_66f0* VectorElem38::erase(Elem38_s0052_66f0* first, Elem38_s0052_66f0* last)
{
    ScratchSlots_s0052_66f0<8>();
    Elem38_s0052_66f0* const position = copy(last, mpEnd, first);
    destruct(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x005267c0
void VectorElem38::DoInsertValue(Elem38_s0052_66f0* position, const Elem38_s0052_66f0& value)
{
    if (mpEnd != mpCapacity) {
        const Elem38_s0052_66f0* pValue = &value;
        if (pValue >= position && pValue < mpEnd)
            ++pValue;
        ::new (mpEnd) Elem38_s0052_66f0(*(mpEnd - 1));
        copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Elem38_s0052_66f0* const pNewData = DoAllocate(nNewSize);
        Elem38_s0052_66f0* pNewEnd = UninitCopy38(mpBegin, position, pNewData);
        if (pNewEnd)
            ::new (pNewEnd) Elem38_s0052_66f0(value);
        ++pNewEnd;
        pNewEnd = UninitCopy38(position, mpEnd, pNewEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1]) {
            void* q = mpBegin;
            EA_Free(q);
        }
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00526a40
void FixedVec8::Free()
{
    void* q;
    if (mpBegin) {
        int nBytes = (int)(((char*)mpCapacity - (char*)mpBegin) >> 3) << 3;
        void* p = mpBegin;
        (void)nBytes;
        if (p != mpInlineBuffer) {
            q = p;
            EA_Free(q);
        }
    }
}

// @ 0x00526b30
VectorElem1c& VectorElem1c::operator=(const VectorElem1c& x)
{
    if (this != &x) {
        uint32_t n = x.size();
        if (n > capacity()) {
            Elem1c* pNewData = AllocAndCopy1c(n, x.mpBegin, x.mpEnd);
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = pNewData + n;
        } else if (n > size()) {
            memcpy(mpBegin, x.mpBegin, size() * sizeof(Elem1c));
            UninitCopy1c(x.mpBegin + size(), x.mpEnd, mpEnd);
        } else {
            Elem1c* pNewEnd = (Elem1c*)memcpy(mpBegin, x.mpBegin, (x.mpEnd - x.mpBegin) * sizeof(Elem1c));
            destruct(pNewEnd, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x00526e70
VectorElem18& VectorElem18::operator=(const VectorElem18& x)
{
    if (this != &x) {
        uint32_t n = x.size();
        if (n > capacity()) {
            Elem18* pNewData = AllocAndCopy18(n, x.mpBegin, x.mpEnd);
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = pNewData + n;
        } else if (n > size()) {
            memcpy(mpBegin, x.mpBegin, size() * sizeof(Elem18));
            UninitCopy18(x.mpBegin + size(), x.mpEnd, mpEnd);
        } else {
            Elem18* pNewEnd = (Elem18*)memcpy(mpBegin, x.mpBegin, (x.mpEnd - x.mpBegin) * sizeof(Elem18));
            destruct(pNewEnd, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x00527110
void DequeElem48::DoPopFront()
{
    FreeNode(mItBegin.mpBegin);
    mItBegin.DoFreeMap((char*)mItBegin.mpCurrentArrayPtr + 4);
    mItBegin.mpCurrent = mItBegin.mpBegin;
}

// @ 0x00527150
VectorElem40_s0052_66f0::VectorElem40_s0052_66f0(const VectorElem40_s0052_66f0& x)
{
    ScratchSlots_s0052_66f0<15>();
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    mpBegin = n ? (Elem40*)EA_Allocate(&mAllocator, n << 6, 4, 0) : 0;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + n;
    mpEnd = UninitCopy40(x.mpBegin, x.mpEnd, mpBegin);
}

// @ 0x00527440
Elem38_s0052_66f0::Elem38_s0052_66f0(const Elem38_s0052_66f0& x)
: m00(x.m00), v04(x.v04), v0c(x.v0c), v18(x.v18),
      m1c(x.m1c), m20(x.m20), m24(x.m24), m28(x.m28),
      mpObj(x.mpObj), m30(x.m30), mpPooled(x.mpPooled)
{
}

// @ 0x00527570
void VectorElem38::DoInsertValues(Elem38_s0052_66f0* position, size_type n, const Elem38_s0052_66f0& value)
{
    if (n == 0)
        return;
    Elem38_s0052_66f0 valueSaved(value);
    size_type nAfter = (size_type)(mpEnd - position);
    if ((size_type)(mpCapacity - mpEnd) >= n) {
        if (nAfter > n) {
            for (size_type i = 0; i < n; ++i)
                ::new (mpEnd + i) Elem38_s0052_66f0(mpEnd[nAfter - n + i]);
            for (Elem38_s0052_66f0* p = mpEnd - n - 1; p >= position; --p)
                p[n] = *p;
            for (size_type i = 0; i < n; ++i)
                position[i] = valueSaved;
            mpEnd += n;
        } else {
            for (size_type i = 0; i < n - nAfter; ++i)
                ::new (mpEnd + i) Elem38_s0052_66f0(valueSaved);
            for (Elem38_s0052_66f0* p = mpEnd - 1; p >= position; --p)
                p[n] = *p;
            for (size_type i = 0; i < nAfter; ++i)
                position[i] = valueSaved;
            mpEnd += n;
        }
    } else {
        size_type nOldSize = (size_type)(mpEnd - mpBegin);
        size_type nNewSize = nOldSize + n;
        if (nOldSize > 0 && nNewSize < 2 * nOldSize)
            nNewSize = 2 * nOldSize;
        Elem38_s0052_66f0* pNewData = DoAllocate(nNewSize);
        Elem38_s0052_66f0* pNewEnd = UninitCopy38(mpBegin, position, pNewData);
        for (size_type i = 0; i < n; ++i)
            ::new (pNewEnd + i) Elem38_s0052_66f0(valueSaved);
        pNewEnd += n;
        pNewEnd = UninitCopy38(position, mpEnd, pNewEnd);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00527a70
void* UninitCopy1c(void* first, void* last, void* dest)
{
    const gi<Elem1c_s0052_7a70> i((Elem1c_s0052_7a70*)((char*)dest + (((char*)last - (char*)first) / 0x1c) * 0x1c));
    memcpy(dest, first, (uint32_t)((char*)last - (char*)first));
    (void)i;
    return (void*)((char*)dest + (((char*)last - (char*)first) / 0x1c) * 0x1c);
}

// @ 0x00527b70
void* UninitCopy18(void* first, void* last, void* dest)
{
    const gi<Elem18_s0052_7a70> i((Elem18_s0052_7a70*)((char*)dest + (((char*)last - (char*)first) / 0x18) * 0x18));
    memcpy(dest, first, (uint32_t)((char*)last - (char*)first));
    (void)i;
    return (void*)((char*)dest + (((char*)last - (char*)first) / 0x18) * 0x18);
}

// @ 0x00527c70
VectorElem40_s0052_7a70& VectorElem40_s0052_7a70::operator=(const VectorElem40_s0052_7a70& x)
{
    if (this != &x) {
        uint32_t n = x.size();
        if (n > capacity()) {
            Elem40_s0052_7a70* pNewData = AllocAndCopy40(n, x.mpBegin, x.mpEnd);
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = pNewData + n;
        } else if (n > size()) {
            Elem40_s0052_7a70* p = mpBegin;
            for (Elem40_s0052_7a70* s = x.mpBegin; s != x.mpBegin + size(); ++s, ++p)
                *p = *s;
            UninitCopy40_s0052_7a70(x.mpBegin + size(), x.mpEnd, mpEnd);
        } else {
            Elem40_s0052_7a70* p = mpBegin;
            for (Elem40_s0052_7a70* s = x.mpBegin; s != x.mpEnd; ++s, ++p)
                *p = *s;
            destruct(p, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x00527f30
void VectorElem40_s0052_7a70::DoInsertValues(Elem40_s0052_7a70* position, size_type n, const Elem40_s0052_7a70& value)
{
    if (n == 0)
        return;
    Elem40_s0052_7a70 valueSaved(value);
    size_type nAfter = (size_type)(mpEnd - position);
    if ((size_type)(mpCapacity - mpEnd) >= n) {
        if (nAfter > n) {
            for (size_type i = 0; i < n; ++i)
                ::new (mpEnd + i) Elem40_s0052_7a70(mpEnd[nAfter - n + i]);
            for (Elem40_s0052_7a70* p = mpEnd - n - 1; p >= position; --p)
                p[n] = *p;
            for (size_type i = 0; i < n; ++i)
                position[i] = valueSaved;
            mpEnd += n;
        } else {
            for (size_type i = 0; i < n - nAfter; ++i)
                ::new (mpEnd + i) Elem40_s0052_7a70(valueSaved);
            for (Elem40_s0052_7a70* p = mpEnd - 1; p >= position; --p)
                p[n] = *p;
            for (size_type i = 0; i < nAfter; ++i)
                position[i] = valueSaved;
            mpEnd += n;
        }
    } else {
        size_type nOldSize = (size_type)(mpEnd - mpBegin);
        size_type nNewSize = nOldSize + n;
        if (nOldSize > 0 && nNewSize < 2 * nOldSize)
            nNewSize = 2 * nOldSize;
        Elem40_s0052_7a70* pNewData = nNewSize ? (Elem40_s0052_7a70*)EA_Allocate(&mAllocator, nNewSize << 6, 4, 0) : 0;
        Elem40_s0052_7a70* pNewEnd = UninitCopy40_s0052_7a70(mpBegin, position, pNewData);
        for (size_type i = 0; i < n; ++i)
            ::new (pNewEnd + i) Elem40_s0052_7a70(valueSaved);
        pNewEnd += n;
        pNewEnd = UninitCopy40_s0052_7a70(position, mpEnd, pNewEnd);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x005283d0
void FixedVec8_s0052_7a70::assign(void* first, void* last, void* unused)
{
    (void)unused;
    uint32_t n = (uint32_t)(((char*)last - (char*)first) >> 3);
    if ((uint32_t)(((char*)mpCapacity - (char*)mpBegin) >> 3) < n) {
        void* pNew = FixedAlloc8(this, 0, n, first, last);
        for (void* p = mpBegin; p < mpEnd; p = (char*)p + 8) { }
        void* old = mpBegin;
        if (old && old != mpInlineBuffer) {
            void* q = old;
            EA_Free(q);
        }
        mpBegin = pNew;
        mpEnd = (char*)mpBegin + n * 8;
        mpCapacity = mpEnd;
    } else if ((uint32_t)(((char*)mpEnd - (char*)mpBegin) >> 3) < n) {
        void* dst = mpBegin;
        uint32_t cur = (uint32_t)(((char*)mpEnd - (char*)mpBegin) >> 3);
        void* s = first;
        while (s != (char*)first + cur * 8) {
            *(uint32_t*)dst = *(uint32_t*)s;
            *((uint32_t*)dst + 1) = *((uint32_t*)s + 1);
            dst = (char*)dst + 8;
            s = (char*)s + 8;
        }
        void* newEnd = FixedUninit8((char*)first + cur * 8, last, mpEnd);
        mpEnd = newEnd;
    } else {
        void* dst = mpBegin;
        for (void* s = first; s != last; s = (char*)s + 8) {
            *(uint32_t*)dst = *(uint32_t*)s;
            *((uint32_t*)dst + 1) = *((uint32_t*)s + 1);
            dst = (char*)dst + 8;
        }
        for (void* p = dst; p < mpEnd; p = (char*)p + 8) { }
        mpEnd = dst;
    }
}

// @ 0x00528610
Elem40_s0052_7a70::Elem40_s0052_7a70(const Elem40_s0052_7a70& x)
: m00(x.m00), v04(x.v04), mat(x.mat), v34(x.v34), v38(x.v38), v3c(x.v3c)
{
    ScratchSlots_s0052_7a70<11>();
}

// @ 0x00529d30
float* RGBtoHSV(float* out, float r, float g, float b)
{
    int which;
    float mx;
    float d;
    if (r <= g) {
        if (g <= b) {
            which = 2; mx = b; d = b - r;
        } else {
            which = 1; mx = g;
            float t = g - b;
            if (r < b) t = g - r;
            d = t;
        }
    } else if (b <= r) {
        which = 0; mx = r;
        float t = r - g;
        if (b < g) t = r - b;
        d = t;
    } else {
        which = 2; mx = b; d = b - g;
    }
    if (d <= 1.5258789e-05f) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = mx;
    } else {
        float s = 60.0f / d;
        if (which == 2)
            s = s * (r - g) + 240.0f;
        else if (which == 1)
            s = s * (b - r) + 120.0f;
        else {
            s = s * (g - b);
            if (g < b) s = s + 360.0f;
        }
        out[0] = s;
        out[1] = d / mx;
        out[2] = mx;
    }
    return out;
}

// @ 0x0052a030
float* HSVtoRGB(float* out, float param_2, float param_3)
{
    float local_10 = param_2 * 0.016666668f;
    int local_c = (int)local_10;
    float local_98 = 1.0f - param_3;
    float local_80 = 1.0f - (local_10 - (float)local_c) * param_3;
    float local_9c = (local_10 - (float)local_c) * param_3 + local_98;
    float local_18 = local_9c;
    float local_14 = local_80;
    float local_8 = local_98;
    float result[3];
    switch (local_c) {
    case 0: {
        float v[3] = { 1.0f, local_9c, local_98 };
        float* p = Vector3Scale(result, &param_3 + 1, v);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    case 1: {
        float v[3] = { local_80, 1.0f, local_98 };
        float* p = Vector3Scale(result, &param_3 + 1, v);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    case 2: {
        float v[3] = { local_98, 1.0f, local_9c };
        float* p = Vector3Scale(result, &param_3 + 1, v);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    case 3: {
        float v[3] = { local_98, 1.0f, 0.0f };
        float* p = Vector3Scale(result, &param_3 + 1, v);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    case 4: {
        float v[3] = { local_80, local_98, 0.0f };
        float* p = Vector3Scale(result, &param_3 + 1, v);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
        break;
    }
    default: {
        float v[3] = { 1.0f, local_98, local_80 };
        float* p = Vector3Scale(result, &param_3 + 1, v);
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2];
    }
    }
    return out;
}

// @ 0x0052a400
int CreatePlaceholderTextures(int a, int b, int c, int* out1, int* out2, float* color)
{
    float f = color[0];
    if (f < 0.0f) f = 0.0f;
    f = f * 255.0f;
    if (f > 255.0f) f = 255.0f;
    uint8_t local_36 = (uint8_t)(int)(f + 0.5f);
    f = color[1];
    if (f < 0.0f) f = 0.0f;
    f = f * 255.0f;
    if (f > 255.0f) f = 255.0f;
    uint8_t local_37 = (uint8_t)(int)(f + 0.5f);
    f = color[2];
    if (f < 0.0f) f = 0.0f;
    f = f * 255.0f;
    if (f > 255.0f) f = 255.0f;
    uint8_t local_38 = (uint8_t)(int)(f + 0.5f);
    uint8_t local_35 = 0xff, local_31 = 0xff, local_2d = 0xff, local_29 = 0xff;
    int local_3c = 0, local_40 = 0;
    uint8_t local_34 = local_38, local_33 = local_37, local_32 = local_36;
    uint8_t local_30 = local_38, local_2f = local_37, local_2e = local_36;
    uint8_t local_2c = local_38, local_2b = local_37, local_2a = local_36;
    uint8_t local_25 = local_38, local_1d = local_37, local_15 = local_36;
    uint8_t buf[16];
    buf[0] = local_38; buf[1] = local_37; buf[2] = local_36; buf[3] = 0xff;
    buf[4] = local_34; buf[5] = local_33; buf[6] = local_32; buf[7] = local_35;
    buf[8] = local_30; buf[9] = local_2f; buf[10] = local_2e; buf[11] = local_31;
    buf[12] = local_2c; buf[13] = local_2b; buf[14] = local_2a; buf[15] = local_29;
    (void)local_25; (void)local_1d; (void)local_15;

    int iVar2;
    void* pR = CreateRaster(2, 2, 0, 8, 0x15);
    if (pR && (iVar2 = RasterFill(pR, 0)) == 0x10) {
        RasterMip(pR, buf, 0);
        TexMgr* tm = (TexMgr*)TextureManager();
        iVar2 = (int)tm->v19(a, b, pR, 0);
        if (iVar2 != 0) {
            local_3c = iVar2;
            *(int*)(iVar2 + 8) = *(int*)(iVar2 + 8) + 1;
        }
    }
    int iVar1 = local_3c;
    pR = CreateRaster(2, 2, 0, 8, 0x15);
    if (pR && (iVar2 = RasterFill(pR, 0)) == 0x10) {
        RasterMip(pR, DAT_013f1f10, 0);
        TexMgr* tm = (TexMgr*)TextureManager();
        iVar2 = (int)tm->v19(a, c, pR, 0);
        if (iVar2 != 0) {
            local_40 = iVar2;
            *(int*)(iVar2 + 8) = *(int*)(iVar2 + 8) + 1;
        }
    }
    int iVar4 = local_40;
    if (out1) *out1 = iVar1;
    if (out2) *out2 = iVar4;
    if (local_40) ReleaseRaster((void*)local_40);
    if (local_3c) ReleaseRaster((void*)local_3c);
    return 1;
}

// @ 0x0052a700
int LoadSkinnerMesh(int mesh, int md)
{
    MeshOp1((void*)mesh);
    ClustersAndEdges((void*)mesh, 1);
    uint32_t i = 0;
    uint32_t nBlocks = (uint32_t)((*(int*)(mesh + 0x20) - *(int*)(mesh + 0x1c)) / 0x8c);
    while (i < nBlocks) {
        // each block carries a list at +0x44; bail out if it is already populated
        VectorU32* pList = (VectorU32*)(i * 0x8c + *(int*)(mesh + 0x1c) + 0x44);
        if (!pList->empty())
            return 0;
        i++;
    }

    int r = MeshOp2((void*)mesh, 3, -1, 3, 0xe);
    if (r < 0)
        MeshOp4((void*)mesh);
    int local_48[4] = { 1, 2, 3, 8 };
    int local_38[4] = { 3, 3, 3, 2 };
    int local_24[4] = { -1, -1, -1, -1 };
    uint32_t uVar4 = (uint32_t)MeshOp3((void*)mesh, 4, local_24, local_48, 0, local_38, 0);
    if ((uVar4 & 0xff) == 0)
        return uVar4 & 0xffffff00u;

    uint32_t* local_10 = (uint32_t*)(*(int*)(mesh + 8) + 0x10 + local_24[0] * 0x20);
    uint32_t* local_54 = (uint32_t*)(*(int*)(mesh + 8) + 0x10 + local_24[1] * 0x20);
    int local_8 = *(int*)(mesh + 8) + 0x10 + local_24[2] * 0x20;
    uint32_t* local_28 = (uint32_t*)(*(int*)(mesh + 8) + 0x10 + local_24[3] * 0x20);
    int local_c = (*(int*)(md + 0xc) - *(int*)(md + 8)) / 0xc;
    int local_4c = (*(int*)(md + 0x20) - *(int*)(md + 0x1c)) / 0xc;
    int local_14 = (*(int*)(md + 0x48) - *(int*)(md + 0x44)) / 0x18;
    int local_50 = (*(int*)(md + 0x34) - *(int*)(md + 0x30)) >> 3;
    FUN_00473810(local_c + *local_10);
    for (uint32_t k = 0; k < *local_10; k++) {
        uint32_t* src = (uint32_t*)(*(uint16_t*)((char*)local_10 + 10) * k + local_10[1]);
        uint32_t* dst = (uint32_t*)(*(int*)(md + 8) + (local_c + k) * 0xc);
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
    }
    FUN_00473810(local_4c + *local_54);
    for (uint32_t k = 0; k < *local_54; k++) {
        uint32_t* dst = (uint32_t*)((local_4c + k) * 0xc + *(int*)(md + 0x1c));
        char tmp[12];
        uint32_t* src = (uint32_t*)V3NormalizeSafe(tmp, (void*)(*(uint16_t*)((char*)local_54 + 10) * k + local_54[1]));
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
    }
    FUN_00473dc0(local_50 + *local_28);
    FUN_0050d3c0(*(int*)(md + 0x34) - *(int*)(md + 0x30) >> 3);
    for (uint32_t k = 0; k < *local_28; k++) {
        uint32_t* src = (uint32_t*)(*(uint16_t*)(local_8 + 10) * k + *(int*)(local_8 + 4));
        uint32_t* dst = (uint32_t*)(*(int*)(md + 0x44) + (local_14 + k) * 0x18);
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
        int row = (local_14 + k) * 0x18 + *(int*)(md + 0x44);
        char tmp[12];
        uint32_t* t = (uint32_t*)FUN_0044e460(tmp, (void*)(*(uint16_t*)((char*)local_54 + 10) * k + local_54[1]),
                                              (void*)(*(uint16_t*)(local_8 + 10) * k + *(int*)(local_8 + 4)));
        *(uint32_t*)(row + 0xc) = t[0];
        *(uint32_t*)(row + 0x10) = t[1];
        *(uint32_t*)(row + 0x14) = t[2];
        uint32_t* s2 = (uint32_t*)(*(uint16_t*)((char*)local_28 + 10) * k + local_28[1]);
        int base = *(int*)(md + 0x30);
        *(uint32_t*)(base + (local_50 + k) * 8) = s2[0];
        *(uint32_t*)(base + 4 + (local_50 + k) * 8) = s2[1];
    }
    int pairv[2] = { 0, -1 };
    FUN_0052ae30((uint32_t)(*(int*)(md + 0x34) - *(int*)(md + 0x30)) >> 3, pairv);
    (void)pairv;
    for (uint32_t b = 0; b < (uint32_t)((*(int*)(mesh + 0x20) - *(int*)(mesh + 0x1c)) / 0x8c); b++) {
        uint32_t* blk = (uint32_t*)(b * 0x8c + *(int*)(mesh + 0x1c));
        char ok = (char)MeshOp5(blk + 5);
        if (ok) {
            uint32_t cnt = *blk;
            int local_8c = (*(int*)(md + 0x5c) - *(int*)(md + 0x58)) >> 2;
            FUN_004cd3c0(local_8c + cnt);
            FUN_004cd3c0(local_8c + cnt);
            FUN_004cd3c0(local_8c + cnt);
            for (uint32_t m = 0; m < cnt; m++) {
                int idx = FUN_00467980(m);
                *(int*)(*(int*)(md + 0x58) + (local_8c + m) * 4) = local_c + idx;
                *(int*)(*(int*)(md + 0x6c) + (local_8c + m) * 4) = local_4c + idx;
                *(int*)(*(int*)(md + 0x80) + (local_8c + m) * 4) = local_50 + idx;
                if (*(int*)(*(int*)(md + 0x124) + 4 + (local_50 + idx) * 8) == -1)
                    *(int*)(*(int*)(md + 0x124) + 4 + (local_50 + idx) * 8) = local_8c + m;
            }
        }
    }
    return 1;
}

// @ 0x0052ae30
void PairVec::resize(uint32_t n, const void* value)
{
    int cur = (int)((char*)mpEnd - (char*)mpBegin) >> 3;
    if (n > cur)
        ((VectorIF*)this)->FUN_004cef00(mpEnd, n - cur, value);
    else
        ((VectorIF*)this)->FUN_00530c80((char*)mpBegin + n * 8, mpEnd);
}

// @ 0x0052aeb0
void SkinBoneWeights(int out1, int out2, int param_3, int param_4, float param_5)
{
    int iVar1 = *(int*)(param_4 + 0xc);
    int iVar2 = *(int*)(param_4 + 8);
    for (int b = 0; b < (iVar1 - iVar2) / 0xc; b++) {
        *(uint32_t*)(param_3 + 0x14) = 0;
        uint32_t uVar3 = *(uint32_t*)(*(int*)(param_4 + 0xa8) + b * 4);
        uint32_t local_10 = uVar3;
        uint32_t uVar5;
        do {
            uVar5 = (int)(char)(&DAT_013f18d8)[local_10 % 3] + local_10;
            int iVar4 = *(int*)(*(int*)(param_4 + 0x58) + ((int)(char)(&DAT_013f18d0)[local_10 % 3] + local_10) * 4);
            float* pfVar7 = (float*)(b * 0xc + *(int*)(param_4 + 0x1c));
            float* pfVar6 = (float*)(iVar4 * 0xc + *(int*)(param_4 + 0x1c));
            float dp = pfVar6[0] * pfVar7[0] + pfVar6[1] * pfVar7[1] + pfVar6[2] * pfVar7[2];
            if (_DAT_0150cb00 < dp)
                ((BoneWeightList*)(iVar4 * 0x14 + out1))->Accum(iVar4, dp * dp);
            local_10 = *(uint32_t*)(*(int*)(param_4 + 0x94) + uVar5 * 4);
        } while (local_10 != uVar5 && local_10 != uVar3);
        ((BoneWeightList*)(b * 0x14 + out1))->Normalize(param_5);
        ((BoneWeightList*)(b * 0x14 + out1))->Accum(b, 1.0f - param_5);
        ((BoneWeightList*)(b * 0x14 + out2))->CopyTop(b);
    }
}

// @ 0x0052b060
void BoneWeightList::Accum(int param_2, float param_3)
{
    int maxBones = 4;
    (void)maxBones;
    for (int i = 0; i < 4; i++) {
        if (g_zero0 >= *(float*)(param_2 + 4 + i * 4))
            break;
        int j = 0;
        while (j < mCount &&
               *(unsigned char*)((char*)mpBegin + j * 8) != *(unsigned char*)(param_2 + i))
            j++;
        if (j < mCount) {
            float* pf = (float*)((char*)mpBegin + 4 + j * 8);
            *pf = *(float*)(param_2 + 4 + i * 4) * param_3 + *pf;
        } else {
            *(unsigned char*)((char*)mpBegin + mCount * 8) = *(unsigned char*)(param_2 + i);
            *(float*)((char*)mpBegin + 4 + mCount * 8) = *(float*)(param_2 + 4 + i * 4) * param_3;
            mCount = mCount + 1;
        }
    }
}

// @ 0x0052b170
void BoneWeightList::Normalize(float param_2)
{
    float total = 0.0f;
    for (int i = 0; i < mCount; i++)
        total = total + *(float*)((char*)mpBegin + 4 + i * 8);
    if (0.0f < total) {
        for (int i = 0; i < mCount; i++) {
            float* pf = (float*)((char*)mpBegin + 4 + i * 8);
            *pf = (param_2 / total) * *pf;
        }
    }
}

// @ 0x0052b220
void BoneWeightList::CopyTop(int param_2)
{
    int* this_ = (int*)this;
    char tmp;
    FUN_00533680((void*)*this_, (void*)this_[1], tmp);
    float total = 0.0f;
    for (int i = 0; i < 4; i++) {
        if (i < this_[5]) {
            *(uint8_t*)(param_2 + i) = *(uint8_t*)(*this_ + i * 8);
            float f = *(float*)(*this_ + 4 + i * 8);
            *(float*)(param_2 + 4 + i * 4) = f;
            total = total + f;
        } else {
            *(uint32_t*)(param_2 + 4 + i * 4) = 0;
        }
    }
    if (0.0f < total) {
        for (int i = 0; i < 4; i++) {
            float* pf = (float*)(param_2 + 4 + i * 4);
            *pf = *pf / total;
        }
    }
}

// @ 0x0052b340
void SkinPaintBuild(Row** ppOut, JointVec* joints, SegVec* segs, int unused4, RemapTable* remap, WeightSource* src, PointSet* pts, SkeletonObj* skel, int passes, float biasDist)
{
    (void)unused4;
    // leading run of bones with kind == 5
    Bone* bones = skel->boneBegin;
    int   nBones = (int)(skel->boneEnd - skel->boneBegin);
    int   nLead;
    for (nLead = 0; nLead < nBones && bones[nLead].kind == 5; ++nLead) {
    }
    unsigned nSegs   = (unsigned)(segs->end - segs->begin);
    unsigned nPoints = (unsigned)(pts->ptEnd - pts->ptBegin);

    char dummyAlloc;
    RowVec scratch(&dummyAlloc);
    Row* bufA;     // result rows being produced
    Row* bufB;     // other ping-pong buffer
    if (passes < 1) {
        bufA = *ppOut;
    } else {
        scratch.resize(nPoints);
        bufA = (passes % 2 == 0) ? *ppOut : scratch.mpBegin;
    }

    char dummyA, dummyB;
    FloatVec segWeight;
    segWeight.Construct(&dummyA);
    segWeight.Init();
    PairVec_s0052_b340 cand;
    cand.Construct(&dummyB);
    cand.Init();

    for (unsigned p = 0; p < nPoints; ++p) {
        cand.erase(cand.mpBegin, cand.mpEnd);
        Vec3* pt = &pts->ptBegin[p];
        src->Query(pt, &cand);
        float zero = 0.0f;
        segWeight.resize(nSegs, &zero);

        unsigned nCand = (unsigned)(cand.mpEnd - cand.mpBegin);
        for (unsigned j = 0; j < nCand; ++j) {
            unsigned idx = (unsigned)cand.mpBegin[j].index;
            float    wgt = cand.mpBegin[j].weight;
            if ((idx & 0x80000000) == 0) {
                Segment* seg = &segs->begin[idx];
                Vec3 a = joints->begin[seg->a].pos;
                Vec3 b = joints->begin[seg->b].pos;
                unsigned origIdx = idx;
                Vec3 ab = Vec3Sub(b, a);
                Vec3 pa = Vec3Sub(*pt, a);
                float num = (pa.x * ab.x + pa.y * ab.y) + pa.z * ab.z;
                float den = (ab.x * ab.x + ab.y * ab.y) + ab.z * ab.z;
                float one = 1.0f;
                float t = 0.0f;
                if (0.0f <= num / den)
                    t = num / den;
                if (one <= t)
                    t = one;
                int   endJoint;
                float near;
                if (t > 0.5f) {
                    endJoint = seg->b;
                    near = 1.0f - t;
                } else {
                    endJoint = seg->a;
                    near = t;
                }
                near = near * 2.0f;
                if (0.0f < wgt * near) {
                    if (remap != 0)
                        origIdx = remap->table[origIdx];
                    float* slot = &segWeight.mpBegin[origIdx];
                    *slot = wgt * near + *slot;
                }
                Joint* ej = &joints->begin[endJoint];
                unsigned nChild = (unsigned)(ej->childEnd - ej->childBegin);
                float share = ((1.0f - near) * wgt) / (float)nChild;
                if (0.0f < share) {
                    for (unsigned c = 0; c < nChild; ++c) {
                        Joint* j2 = &joints->begin[endJoint];
                        unsigned bi = j2->childBegin[c];
                        if (remap != 0)
                            bi = remap->table[bi];
                        unsigned limit = 0x40;
                        if (bi < limit) {
                            float* s2 = &segWeight.mpBegin[bi];
                            *s2 = *s2 + share;
                        }
                    }
                }
            } else {
                unsigned ji = idx & 0x7fffffff;
                Joint* jt = &joints->begin[ji];
                unsigned nChild = (unsigned)(jt->childEnd - jt->childBegin);
                float share = wgt / (float)nChild;
                for (unsigned c = 0; c < nChild; ++c) {
                    unsigned bi = jt->childBegin[c];
                    if (remap != 0)
                        bi = remap->table[bi];
                    unsigned limit = 0x40;
                    if (bi < limit) {
                        float* s2 = &segWeight.mpBegin[bi];
                        *s2 = *s2 + share;
                    }
                }
            }
        }

        if (0.0f < biasDist) {
            unsigned best = 0;
            for (unsigned s = 0; s < nSegs; ++s) {
                float* cur = &segWeight.mpBegin[s];
                float* top = &segWeight.mpBegin[best];
                if (*top < *cur)
                    best = s;
            }
            if ((int)best < nLead && 1 < nLead) {
                float zero2 = 0.0f;
                segWeight.resize(nSegs, &zero2);
                int first = ((int)best < 3) ? 0 : (int)best - 2;
                for (int b = first; b <= (int)(best + 2) && b < nLead; ++b) {
                    Bone* bone = &bones[b];
                    Vec3 tip;
                    MakeBoneTip(&tip, &bone->b, &bone->a, bone->radius);
                    float skinRadius = GetExactSkinRadiusFromVertebra(bone->radius);
                    Vec3 rel = Vec3Sub(*pt, tip);
                    Vec3 relCopy = rel;
                    float dist = VectorLength(&relCopy) - skinRadius;
                    if (0.0f <= dist)
                        segWeight.mpBegin[b] = biasDist / (biasDist + dist);
                    else
                        segWeight.mpBegin[b] = 1.0f;
                }
            }
        }

        // keep the four strongest segments, sorted by weight (insertion into a 4-entry list)
        PairIF init = { 0, 0.0f };
        cand.resize(4, &init);
        for (unsigned s = 0; s < nSegs; ++s) {
            PairIF* it = cand.mpBegin;
            while (it != cand.mpEnd) {
                float cur = segWeight.mpBegin[s];
                if (it->weight < cur) {
                    PairIF entry;
                    entry.index = (int)s;
                    entry.weight = segWeight.mpBegin[s];
                    cand.insert(it, &entry);
                    cand.mpEnd = cand.mpEnd - 1;
                    break;
                }
                ++it;
            }
        }

        PairIF* e0 = &cand.mpBegin[0];
        PairIF* e1 = &cand.mpBegin[1];
        PairIF* e2 = &cand.mpBegin[2];
        float total = ((e0->weight + e1->weight) + e2->weight) + cand.mpBegin[3].weight;
        Row* row = &bufA[p];
        for (unsigned k = 0; k < 4; ++k) {
            row->bone[k] = (unsigned char)cand.mpBegin[k].index;
            PairIF* pk = &cand.mpBegin[k];
            row->weight[k] = pk->weight / total;
        }
    }

    if (passes > 0) {
        char dummyC;
        ScratchVec tmp;
        tmp.Construct(0x40, &dummyC);
        bufB = (passes % 2 == 0) ? scratch.mpBegin : *ppOut;
        for (int k = 0; k < passes; ++k) {
            SkinBoneWeights(bufA, bufB, &tmp, pts, g_150cb04);
            Row* sw = bufA;
            bufA = bufB;
            bufB = sw;
        }
    }
}

// @ 0x0052c230
namespace eastl {
template <> vector_s0052_c230<pair_s0052_c230<int, float> >::vector_s0052_c230(size_type n, const sp_vector_allocator_s0052_c230& allocator)
: VectorBase_s0052_c230<pair_s0052_c230<int, float> >(n, allocator)
{
    uninitialized_fill_n_ptr(mpBegin, n, value_type());
    mpEnd = mpBegin + n;
}
}  // namespace eastl

// @ 0x0052c2e0
namespace eastl {
template <> pair_s0052_c230<int, float>* vector_s0052_c230<pair_s0052_c230<int, float> >::insert(pair_s0052_c230<int, float>* position, const value_type& value)
{
    const int n = (int)(position - mpBegin);
    if ((position != mpEnd) || (mpEnd == mpCapacity))
        DoInsertValue(position, value);
    else
        ::new (mpEnd++) value_type(value);
    return mpBegin + n;
}
}  // namespace eastl

// @ 0x0052c380
namespace eastl {
template <typename T> inline void iter_swap(T* a, T* b)
{
    const T temp = *a;
    *a = *b;
    *b = temp;
}
}  // namespace eastl

// @ 0x0052c570
namespace eastl {
template void vector_s0052_c230<pair_s0052_c230<int, float> >::DoAssignValues(size_type n, const value_type& value)
;
}  // namespace eastl

// @ 0x0052c8f0
namespace eastl {
template <> void uninitialized_fill_n_impl(generic_iterator<pair_s0052_c230<int, float> > first, uint32_t n, const pair_s0052_c230<int, float>& value, false_type)
{
    generic_iterator<pair_s0052_c230<int, float> > currentDest(first);
    for (; n > 0; --n, ++currentDest)
        ::new (&*currentDest) pair_s0052_c230<int, float>(value);
}
}  // namespace eastl

// @ 0x0052c950
namespace eastl {
void quick_sort_impl_helper(PairIF_s0052_c230* first, PairIF_s0052_c230* last, int kRecursionCount, SecondGreater compare)
{
    while (((last - first) > 28) && (kRecursionCount > 0)) {
        PairIF_s0052_c230* const position = get_partition(first, last,
            median(*first, *(first + (last - first) / 2), *(last - 1), compare), compare);
        quick_sort_impl_helper(position, last, --kRecursionCount, compare);
        last = position;
        ScratchSlots_s0052_c230<9>();   // frames of the declined median() / get_partition() expansions
    }
    if (kRecursionCount == 0)
        partial_sort(first, last, last, compare);
}
}  // namespace eastl

// @ 0x0052cbc0
namespace eastl {
template <> pair_s0052_c230<int, float>* fill_n(pair_s0052_c230<int, float>* first, uint32_t n, const pair_s0052_c230<int, float>& value)
{
    return fill_n_impl(first, n, value);
}
}  // namespace eastl

// @ 0x0052cc10
namespace eastl {
PairIF_s0052_c230* get_partition(PairIF_s0052_c230* first, PairIF_s0052_c230* last, PairIF_s0052_c230 pivotValue, SecondGreater compare)
{
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        iter_swap(first, last);
    }
}
}  // namespace eastl

// @ 0x0052ccd0
namespace eastl {
void partial_sort(PairIF_s0052_c230* first, PairIF_s0052_c230* middle, PairIF_s0052_c230* last, SecondGreater compare)
{
    make_heap(first, middle, compare);
    for (PairIF_s0052_c230* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const PairIF_s0052_c230 temp(*i);
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }
    sort_heap(first, middle, compare);
}
}  // namespace eastl

// @ 0x0052cf00
namespace eastl {
void make_heap(PairIF_s0052_c230* first, PairIF_s0052_c230* last, SecondGreater compare)
{
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            const PairIF_s0052_c230 temp(*(first + parentPosition));
            adjust_heap(first, parentPosition, heapSize, parentPosition, temp, compare);
        } while (parentPosition != 0);
    }
}
}  // namespace eastl

// @ 0x0052cf80
namespace eastl {
void adjust_heap(PairIF_s0052_c230* first, int topPosition, int heapSize, int position, PairIF_s0052_c230 value, SecondGreater compare)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value, compare);
}
}  // namespace eastl
