// src/game/SPEngine/_at_00710000.cpp -- migrated from slice(s) s0071e390, s0071d550, s0071c900, s0071ac50, s00719e10, s00719620, s00718640, s007173e0, s00716110, s00714f20, s00713e40 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00710000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_vecdtor4E1BF0;   // 0x4E1BF0 element destructor
#include <new>
#include <string.h>
#include <math.h>
#include <intrin.h>
#include <stddef.h>
#include <xmmintrin.h>

// ---- items of slice s00713e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EastlNew(uint32_t n, const char* name, int flags, int dbg, const char* file, int line); // 0xF473A0
void __cdecl EastlFree(void* p);                        // 0xF47380
void __cdecl VectorDtorRange(void* first, uint32_t elemSize, uint32_t count, void (__cdecl* dtor)(void*)); // 0x11E0B22
void* __cdecl GetMaterialManager();                     // 0x67DD70
void __cdecl SPKeyFromName(void* out, const void* name, int a, int b); // 0x68D840
void __fastcall FUN_711170(void* self);                 // 0x711170
typedef bool (__cdecl* TextureFilter)(void*);
struct MaterialManager;
struct MaterialManager {
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
    virtual void* at28(uint32_t id);                                     // +0x28
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual void at3c(void* element, uint32_t a, uint32_t b);            // +0x3c
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
};
struct SmartPtr {
    void* mp;
    SmartPtr(void* q) : mp(q) {
        if (mp)
            ((void(__thiscall*)(void*))(*(void***)mp)[0])(mp);
    }
    ~SmartPtr() {
        if (mp)
            ((void(__thiscall*)(void*))(*(void***)mp)[1])(mp);
    }
};
struct AdapterVec {
    void* mpBegin;                      // +0x00
    void* mpEnd;                        // +0x04
    void* mpCap;                        // +0x08
    void push_back(const void* item);   // 0x7A6AC0
};
struct AdapterList {
    void* mVt0; void* mVt1;             // +0x00
    uint32_t m8;                        // +0x08
    AdapterVec mVec;                    // +0x0c
    void Remove(void* item);
};
struct DispatchTarget {
    char pad[0xb8];
    void** mB8;     // +0xb8
    void** mBC;     // +0xbc
    char pad2[0xf4 - 0xc0];
    void** mF4;     // +0xf4
    void** mF8;     // +0xf8
};
extern void* g_vecdtor4E1BF0;   // 0x4E1BF0 element destructor
static void EastlFreeGuarded(void* p)
{
    if (p && *(int*)((char*)p - 4) != 0)
        EastlFree(p);
}
struct AdapterTeardown {
    char pad0[8];
    void* m8;          // +0x08
    char pad0C[0x10];
    void* m1c;         // +0x1c
    char pad20[0x10];
    char m30[0x50];    // +0x30  vector: begin/end/cap + 4 * 0x14 elements
    char m80[0x28];    // +0x80  vector: begin/end/cap + 2 * 0x14 elements
    void* ma8;         // +0xa8
    char padAC[0x10];
    void* mbc;         // +0xbc
    void Destroy();
};
struct RecordCmp {
    const uint32_t** mpBase;                // +0x00  pointer to the record-array base pointer
    bool less(uint32_t a, uint32_t b) const;
};
struct PairTable {
    char pad0[0xf8];
    uint32_t* mpBegin;                      // +0xf8
    uint32_t* mpEnd;                        // +0xfc
    void Set(uint32_t key, uint32_t value);
};
struct MatrixTable {
    char pad0[0x10c];
    void* mpData;                           // +0x10c
    uint32_t* Set(uint32_t index, const uint32_t* mat);
};
struct Vec4 {
    uint32_t* mpBegin;                      // +0x00
    uint32_t* mpEnd;                        // +0x04
    uint32_t* mpCap;                        // +0x08
    void Reserve(uint32_t n);
};
struct ResourceAdapter {
    char pad0[0x14c];
    uint32_t mKey;      // +0x14c
    void SetName(const void* name);
    void SetNameAndCall(const void* a, const void* name);
    void SetFlag(int value);
    void Dispatch(uint8_t flags, uint32_t a, uint32_t b, uint32_t c);
};
struct Float12 { float v[12]; };
struct TElem {
    void* m0; void* m4; void* m8;
    uint32_t mC; uint32_t m10;
    TElem() : m0(0), m4(0), m8(0) {}
    ~TElem();
};
struct AdapterCtor {
    uint32_t m0;            // +0x00
    uint32_t m4;            // +0x04
    TElem t1;               // +0x08
    TElem t2;               // +0x1c
    TElem arr4[4];          // +0x30
    TElem arr2[2];          // +0x80
    TElem t3;               // +0xa8
    TElem t4;               // +0xbc
    AdapterCtor();
};
// ---- items of slice s00713e40 end

// ---- items of slice s00714f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
void* __cdecl ea_alloc(const char* tag, unsigned size, int a, int b, const char* file, int line);
void  __cdecl ea_free(void* p);
void* __cdecl move_ret(void* dst, const void* src, unsigned n);
void* __cdecl mem_copy(void* dst, const void* src, unsigned n);
void* __cdecl mem_move(void* dst, const void* src, unsigned n);
struct Cmp4 { bool operator()(int a, int b) const; };
void __cdecl adjust_heap(int* first, int hole, int length, int top, int value, Cmp4 cmp);
int* __cdecl median3(int* a, int* b, int* c, Cmp4 cmp);
static inline void ea_del(void* p)
{
    if (p != 0 && ((int*)p)[-1] != 0)
        ea_free(p);
}
static inline void* ea_new(unsigned size)
{
    return ea_alloc("Graphics", size, 0, 0, "EASTL/allocator.h", 0xd1);
}
struct Elem40 { void* p0; void* pad0[4]; void* p14; void* pad1[4]; };
void* __cdecl alloc20(int count, const void* first, const void* last);
void* __cdecl copy20(const void* first, const void* last, void* dst);
void  __cdecl uninit20(void* out, const void* first, const void* last, void* end, void* tmp);
struct Vec20 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    Vec20& assign(const Vec20& x);
};
void* __cdecl alloc4(int count, const void* first, const void* last);
void* __cdecl copy4(const void* first, const void* last, void* dst);
void* __cdecl uninit4(void* dst, const void* first, const void* last);
struct Vec4_s0071_4f20 {
    int* mpBegin; int* mpEnd; int* mpCapacity;
    Vec4_s0071_4f20& assign(const Vec4_s0071_4f20& x);
    void  insert(int* position, const int* value);
    void  insert_range(int* position, const int* first, const int* last, int unused);
};
void* __cdecl uninit_copy48(const void* first, const void* last, void* dst);
void  __cdecl fill48(void* dst, unsigned n, const void* value, void* arg);
void  __cdecl move48(const void* first, const void* last, void* dst);
void  __cdecl copy48_assign(void* dst, const void* value);   // Matrix34::operator=
void  __cdecl fill48b(void* dst, unsigned n, const void* value, void* arg);
void  __cdecl shift48(void* dst, const void* first, const void* last, void* arg);
void  __cdecl copy48_range(const void* first, const void* last, void* dst);
struct Vec48 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void insert(char* position, unsigned n, const void* value);
};
void  __cdecl helper73fe50(void* a, void* b, void* c);
void  __cdecl helperac4440(void* a, void* b, void* c);
void  __cdecl helper714bc0(void* a, const void* b, const void* c, void* d, const void* e);
void* __cdecl helper4763a0(void* a, const void* b, void* c);
struct Vec8 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void insert_range(char* position, char* first, char* last, int unused);
};
struct cMeshBuilder {
    void*    mVtbl;        // +0x000
    void*    mp04;         // +0x004
    void*    mp08;         // +0x008
    void*    mp0c;         // +0x00c
    void*    mp10;         // +0x010
    void*    mp14;         // +0x014
    void*    mp18;         // +0x018
    void*    mp1c;         // +0x01c
    void*    mp20;         // +0x020
    void*    mp24;         // +0x024
    u8       pad28[0x08];  // +0x028
    u8       arr30[0x14 * 4];  // +0x030  five-array? (4 elements, 0x14 each)
    u8       arr80[0x14 * 2];  // +0x080  (2 elements, 0x14 each)
    void*    mpa8;         // +0x0a8
    void*    mpac;         // +0x0ac
    void*    mpb0;         // +0x0b0
    void*    mpbc;         // +0x0bc
    void*    mpc0;         // +0x0c0
    void*    mpc4;         // +0x0c4
    void*    mpd0;         // +0x0d0
    void*    mpd4;         // +0x0d4
    void*    mpd8;         // +0x0d8
    void*    mpe4;         // +0x0e4
    void*    mpe8;         // +0x0e8
    void*    mpec;         // +0x0ec
    void*    mpf8;         // +0x0f8
    void*    mpfc;         // +0x0fc
    void*    mp100;        // +0x100
    void*    mp10c;        // +0x10c
    void*    mp110;        // +0x110
    void*    mp114;        // +0x114
    void*    mp120;        // +0x120
    void*    mp124;        // +0x124
    void*    mp128;        // +0x128
    void*    mp134;        // +0x134
    void*    mp138;        // +0x138
    void*    mp13c;        // +0x13c
    void*    mp148;        // +0x148  refcounted object pointer
    u32      m14c;         // +0x14c  magic 0x9f84a565
    u8       m150;         // +0x150
    u8       pad151[3];    // +0x151
    void*    mp154;        // +0x154
    int      m158;         // +0x158  -1
    void*    mp15c;        // +0x15c
    int      m160;         // +0x160  -1
    void*    mp164;        // +0x164
    void*    mp168;        // +0x168
    void*    mp16c;        // +0x16c
    void*    mp170[0x18 / 4]; // +0x170  (through +0x187)
    void*    mp188[0x10 / 4]; // +0x188  (through +0x197)
    void*    mp19c;        // +0x19c
    void*    mp1a0;        // +0x1a0
    void*    mp1a4;        // +0x1a4
    void*    mp1a8;        // +0x1a8
    u8       arr1b0[0x14 * 4]; // +0x1b0
    u8       arr200[0x2 * 0x14]; // +0x200

    cMeshBuilder();
    ~cMeshBuilder();
};
void __stdcall eh_vector_ctor(void* base, unsigned elemSize, unsigned count,
                              void* ctor, void* dtor);
void __stdcall eh_vector_dtor(void* base, unsigned elemSize, unsigned count, void* dtor);
void __cdecl elem_ctor_6e5790(void* self);   // shared element constructor
void __cdecl elem_dtor_4cddd0(void* self);
void __cdecl elem_dtor_7a41a0(void* self);
void __cdecl elem_dtor_4e1bf0(void* self);
void __cdecl release_range_714b40(void* first, void* last);
void __cdecl clear_range_714f20(void* first, void* last);
void __cdecl release_vec_714d70(void* self);
struct RefObj { void** vtbl; int* refcount; };
// ---- items of slice s00714f20 end

// ---- items of slice s00716110 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec2 { float x, y;     Vec2& operator=(const Vec2& o) { x = o.x; y = o.y; return *this; } };
struct Vec3 { float x, y, z;  Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; } };
struct Vec4_s0071_6110 { float x, y, z, w; };
struct Vec8_s0071_6110 { int a, b; };
template<class T> struct EAVec {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    void reserve(int n);                       // masked (eastl::vector::reserve)
    void DoInsertValue(T* pos, const T& v);   // masked (eastl::vector::DoInsertValue)
    void push_back(const T& v) {
        T* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p)
                *p = v;
        } else {
            DoInsertValue(p, v);
        }
    }
};
template<class T> struct VecSlot { EAVec<T> v; char pad[8]; };  // 0x14 bytes
struct Elem120 { EAVec<u32> u; char p0[8]; EAVec<float> f; char p1[8]; };
struct Elem134 {
    EAVec<u32> u0;  char p0[8];
    EAVec<Vec3> v14; char p1[8];
    EAVec<u32> u28;  char p2[8];
    EAVec<Vec3> v3c; char p3[8];
};
struct MeshBuilder {
    char pad0[8];                    // +0x00
    VecSlot<Vec3> v8;                // +0x08
    VecSlot<Vec3> v1c;               // +0x1c
    VecSlot<Vec2> v30[4];            // +0x30
    VecSlot<u32>  v80[2];            // +0x80
    VecSlot<u32>  vA8;               // +0xa8
    VecSlot<u32>  vBC;               // +0xbc
    char padD0[0xf8 - 0xd0];         // +0xd0
    EAVec<Vec8_s0071_6110>   vF8;               // +0xf8
    char pad104[0x120 - 0x104];      // +0x104
    Elem120*      p120;              // +0x120
    char pad124[0x134 - 0x124];      // +0x124
    Elem134*      p134;              // +0x134
    char pad138[0x148 - 0x138];      // +0x138
    void*         p148;              // +0x148
    int           n14c;              // +0x14c
    u8            b150;              // +0x150
    char pad151[0x158 - 0x151];      // +0x151
    int           n158;              // +0x158
    char pad15c[0x168 - 0x15c];      // +0x15c
    int           n168;              // +0x168
    int           n16c;              // +0x16c
    char pad170[0x188 - 0x170];      // +0x170
    VecSlot<u32>  v188[8];           // +0x188 .. +0x228

    // accessors / helpers in this slice
    void pushV8(const Vec3& v);                 // 0x716700
    void pushV1c(const Vec3& v);                // 0x716740
    void pushV30(const Vec2& v, int index);     // 0x716780
    void resizeV8(int n, const Vec3& v);        // 0x7168c0
    void resizeV1c(int n, const Vec3& v);       // 0x716930
    void addPair120(int elemIdx, float value, int delta);        // 0x716e40
    void addBulk120(int elemIdx, int n, const int* idx, const float* vals); // 0x716ed0
    void pushV188_2(u32 v, int index);   // 0x716bf0
    void pushV188_6(u32 v, int index);   // 0x716c30
    void addMasked(u8 mask, u32 value);         // 0x716c70
    void uniqueAdd(int key);                    // 0x716ad0
    void pushColor(const Vec4_s0071_6110& c, int index);   // 0x7167c0
    void addColors(int index, int n, const Vec4_s0071_6110* c); // 0x7169a0
    void addDiff120(int elemIdx);               // (unused)
    void addDiff134_lo(int slot, int n, const Vec3* pts); // 0x716fc0
    void addDiff134_hi(int slot, int n, const Vec3* pts); // 0x7170e0
    void addDiff134_lo1(int slot, int index, const Vec3* pt); // 0x717200
    void addDiff134_hi1(int slot, int index, const Vec3* pt); // 0x7172f0
};
struct BGRA { u8 b, g, r, a; };
static __forceinline u8 PackComp(float f)
{
    // The retail tail keeps everything in xmm0 (xorps/maxss/mulss/minss/cvtss2si) and
    // never writes another vector register.  Evaluate the clamp in x87 (double compares)
    // so no extra xmm register is materialised, then materialise only xmm0 for the final
    // round-to-nearest conversion the original uses (cvtss2si, not truncation).
    double d = (double)f * 255.0;
    if (d > 255.0 || !(d <= 255.0))
        d = 255.0;                            // NaN and +inf clamp high, like minss
    else if (d < 0.0)
        d = 0.0;
    float t = (float)d;
    return (u8)_mm_cvtss_si32(_mm_load_ss(&t));
}
static __forceinline u32 PackColor(const Vec4_s0071_6110& c)
{
    BGRA col;
    col.b = PackComp(c.z);
    col.g = PackComp(c.y);
    col.r = PackComp(c.x);
    col.a = PackComp(c.w);
    return *(u32*)&col;
}
// ---- items of slice s00716110 end

// ---- items of slice s007173e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char g_eastlAllocator;                              // 0x13ebb38
struct VecN {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    VecN& operator=(const VecN& o);   // masked (eastl::vector<T>::operator=)
    void insert(void* pos, void* first, void* last, int tag); // masked range insert
};
struct VecSlotN { VecN v; char pad[8]; };   // 0x14 bytes
struct Elem28 { VecN v0; char p0[8]; VecN v14; char p1[8]; };
struct Elem50 { VecN v0; char p0[8]; VecN v14; char p1[8];
                VecN v28; char p2[8]; VecN v3c; char p3[8]; };
struct Vec30 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void  insert(char* pos, unsigned n, const void* value);   // masked (0x715470)
    void  erase(char* first, char* last);                     // masked (0x9c69f0)
    void  resize(unsigned n, const void* value);
};
struct Vec18 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void  insert(char* pos, unsigned n, const void* value);   // masked (0x722580)
    static void move(char* first, char* last, char* dest);    // masked (0x720250), cdecl: the original sets no ecx
    void  resize(unsigned n);
};
struct Vec14x4 { char pad[0x30]; VecSlotN v; };   // v at +0x30
struct AppEditor {
    char pad0[8];                    // +0x00
    VecSlotN v8;                     // +0x08
    VecSlotN v1c;                    // +0x1c
    VecSlotN v30[4];                 // +0x30
    VecSlotN v80[2];                 // +0x80
    VecSlotN vA8;                    // +0xa8
    VecSlotN vBC;                    // +0xbc
    AppEditor& operator=(const AppEditor& x);
    void  insertRange(int count, char* first, int index);
};
struct SelRec28 {                   // 0x28-byte group
    int*   idxBegin;    // +0x00
    int*   idxEnd;      // +0x04
    char   pad08[0x0c]; // +0x08
    float* weights;     // +0x14 weight/visibility flags per index
};
struct SelRec50 {                   // 0x50-byte group, two 0x28 sub-records
    int*   idxBegin;    // +0x00
    int*   idxEnd;      // +0x04
    char   pad08[0x0c]; // +0x08
    float* pos;         // +0x14 xyz triples
    char   pad18[0x10]; // +0x18
    int*   idx2Begin;   // +0x28
    int*   idx2End;     // +0x2c
    char   pad30[0x0c]; // +0x30
    float* pos2;        // +0x3c xyz triples
};
struct SelRecD0 {                   // 0xd0-byte usage record
    unsigned flags;     // +0x00 accumulated use bits
    int      count;     // +0x04
    int*     idxBegin;  // +0x08 vertex indices
    int*     idxEnd;    // +0x0c
    int*     idxCap;    // +0x10
    char     pad14[0x08];// +0x14
    int*     view1Begin;// +0x1c second index array
    int*     view1End;  // +0x20
    int*     view1Cap;  // +0x24
    char     pad28[0x80];// +0x28
    int*     view2Begin;// +0xa8 third index array
    int*     view2End;  // +0xac
    int*     view2Cap;  // +0xb0
    char     padB4[0x08];// +0xb4
    int*     remapBegin;// +0xbc index remap
    int*     remapEnd;  // +0xc0
    int*     remapCap;  // +0xc4
};
struct AttrEnt {                      // 0x14-byte attribute/range entry
    int tag;     // +0x00 attribute channel (0..9)
    int rec;     // +0x04 owner record index
    int begin;   // +0x08 first index into the record remap
    int end;     // +0x0c last index into the record remap
    int inner;   // +0x10 inner index
};
struct SelEditor {
    char       pad00[0x08];  // +0x00
    float*     sizeBegin;    // +0x08 vertex-size triples
    float*     sizeEnd;      // +0x0c
    char       pad10[0x0c];  // +0x10
    float*     size2Begin;   // +0x1c
    float*     size2End;     // +0x20
    char       pad24[0xac];  // +0x24
    SelRecD0*  recBegin;     // +0xd0
    SelRecD0*  recEnd;       // +0xd4
    char       padD8[0x0c];  // +0xd8
    AttrEnt*   entBegin;     // +0xe4 attribute/range entries
    AttrEnt*   entEnd;       // +0xe8
    char       padEC[0x0c];  // +0xec
    char*      keyBegin;     // +0xf8 8-byte inner keys
    char*      keyEnd;       // +0xfc
    char       pad100[0x20]; // +0x100
    SelRec28*  r28Begin;     // +0x120
    SelRec28*  r28End;       // +0x124
    char       pad128[0x0c]; // +0x128
    SelRec50*  r50Begin;     // +0x134
    SelRec50*  r50End;       // +0x138
};
void* __cdecl EA_Allocate(unsigned size, const char* area, int a, int b, void* allocator, int line); // 0x00f473a0
void  __cdecl EA_Free(void* p);                                     // 0x00f47380
static unsigned* gfxCountArray(int count)
{
    unsigned* a = 0;
    if (count != 0) {
        a = (unsigned*)EA_Allocate((unsigned)(count * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
        for (int k = 0; k < count; ++k)
            a[k] = 0;
    }
    return a;
}
struct IntVec { int* begin; int* end; int* cap; };
void __fastcall FUN_0052c730(IntVec* self, int unused, IntVec* other); // 0x0052c730 eastl vector swap (this in ecx)
int  __cdecl FUN_00921240(int* vec);                               // 0x00921240 sort key for a group vector
void __cdecl FUN_00715e50(int* first, int* last, int key);         // 0x00715e50 stable sort by that key
static void PushU32(IntVec* v, int value)
{
    if (v->end < v->cap) {
        *v->end = value;
        v->end = v->end + 1;
        return;
    }
    int cur = (int)(v->end - v->begin);
    int cap = (int)(v->cap - v->begin);
    int ncap = cap * 2;
    if (ncap < cur + 1)
        ncap = cur + 1;
    int* p = (int*)EA_Allocate((unsigned)(ncap * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
    for (int k = 0; k < cur; ++k)
        p[k] = v->begin[k];
    p[cur] = value;
    if (v->begin != 0 && ((int*)v->begin)[-1] != 0)
        EA_Free(v->begin);
    v->begin = p;
    v->end = p + cur + 1;
    v->cap = p + ncap;
}
struct Span5 {                        // 0x14-byte description span
    int tag;     // +0x00
    int rec;     // +0x04
    int begin;   // +0x08
    int end;     // +0x0c
    int inner;   // +0x10
};
struct IntVecF { float* begin; float* end; float* cap; };
void __cdecl FUN_0042b9e0(float* dst, const int* first, const int* last, int count);  // 0x0042b9e0
void __cdecl FUN_00428900(Span5* pos, const Span5* value);       // eastl vector<cAnimationCurve>::DoInsertValue
void __cdecl FloatVec_Release(IntVecF* v);                        // eastl::vector<float>::~vector
void __fastcall FUN_00715120(void* self, int unused, IntVec* other); // 0x00715120 vector<0x14-record> copy-assign (this in ecx)
void __fastcall FUN_004aa350(void* self, int unused, unsigned count, void** allocator); // 0x004aa350 eastl reserve (this in ecx)
// ---- items of slice s007173e0 end

// ---- items of slice s00718640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_0042cd50(void);                 // FixedIdVector6::DoAssign
extern "C" void* FUN_00717a90(void*, void*, void*);       // relocate 0xd0 elements
extern "C" void* FUN_00717ad0(void*, void*, void*);       // copy 0x50 elements
extern "C" void  FUN_00714b40(void);                      // tail teardown (thiscall, 2 args)
extern "C" void  FUN_007146c0(void);                      // AdapterTeardown::Destroy
extern "C" void  FUN_00716110(void);                      // 0xd0-element copy ctor
extern "C" void  FUN_007191d0(void*, void*, void*);        // construct a range
extern "C" void  FUN_007163c0(void*, void*, void*, void*, void*); // range relocation
extern "C" void* FUN_007165c0(void*, void*, void*);       // copy-construct a range
extern "C" void  FUN_00714960(void*, void*, void*);       // destroy a range
extern "C" void  FUN_00717b30(void*, void*, void*);       // move an element range
struct VecN_s0071_8640 {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    VecN_s0071_8640& operator=(const VecN_s0071_8640& o);                                // masked
    void  insert(void* pos, const void* first, const void* last, int tag); // masked range insert
};
struct VecSlotN_s0071_8640 { VecN_s0071_8640 v; char pad[8]; };   // 0x14 bytes
struct Elem28_s0071_8640 { VecN_s0071_8640 v0; char p0[8]; VecN_s0071_8640 v14; char p1[8]; };
struct MeshBuilder8 {
    char   pad0[0xd0];               // +0x00
    void*  pD0;                      // +0xd0
    char   padD4[0xe8 - 0xd4];
    void*  pE8;                      // +0xe8
    char   padEC[0x150 - 0xec];
    u8     b150;                     // +0x150
    char   pad151[0x160 - 0x151];
    int    n160;                     // +0x160
    char   pad164[0x188 - 0x164];
    VecSlotN_s0071_8640 v188[8];                // +0x188 .. +0x228

    void addIndices0(int count, const int* values, int delta);
    void addIndices1(int count, const int* values, int delta);
    void addIndicesSlot(int count, const int* values, int index, int delta);
    void addIndicesSlot6(int count, const int* values, int index, int delta);
    void finish();
    // callees (other slices / TUs), masked
    void sub18820();
    void sub17ce0();
    void sub173e0();
    void sub18050();
};
struct FixedIdVector6
{
    u32* mpBegin;      // +0x00
    u32* mpEnd;        // +0x04
    u32* mpCapacity;   // +0x08

    FixedIdVector6* Assign(const FixedIdVector6& x);               // @ 0x00719170
    void DoAssign(u32* first, u32* last, const FixedIdVector6& x); // 0x0042cd50
};
typedef void (__thiscall* FixedIdDoAssignFn)(void*, const u32*, const u32*, const void*);
struct MeshVecD0
{
    u8* mpBegin;      // +0x00
    u8* mpEnd;        // +0x04
    u8* mpCapacity;   // +0x08

    u8*  relocateRange(u8* first, u8* last);              // @ 0x00719330
    void insert(u8* position, u32 n, const void* value);  // @ 0x007193e0
};
struct MeshVec50
{
    u8* mpBegin;      // +0x00
    u8* mpEnd;        // +0x04
    u8* mpCapacity;   // +0x08

    u8* copyEraseRange(u8* first, u8* last);              // @ 0x00719390
};
extern "C" void  FUN_00716440(void*, u32, void*, void*);   // construct n copies
typedef void (__thiscall* DestroyFn)(void*);
typedef void (__thiscall* CopyCtorFn)(void*, const void*);
typedef void (__thiscall* TailFn)(void*, u8*, u8*);
#define ELEM_D0 0xd0
#define ELEM_50 0x50
void* __cdecl xmemcpy(void* d, const void* s, size_t n);          // 0x011e0744
void* __cdecl EAAlloc(size_t n, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
void  __cdecl EAFree(void* p);                                    // 0x00f47380
#define ALLOC_H "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct Vec2_s0071_8640 { float x, y; Vec2_s0071_8640() {} Vec2_s0071_8640(const Vec2_s0071_8640& o) : x(o.x), y(o.y) {}
  Vec2_s0071_8640& operator=(const Vec2_s0071_8640& o) { x = o.x; y = o.y; return *this; } };
struct Byte4 { u8 b[4]; Byte4() { b[0] = 0; b[1] = 0; b[2] = 0; b[3] = 0; } };
struct Vertex6 { int a[4]; int b[2]; };
extern Vec2_s0071_8640 gDefaultTexCoord;      // 0x0162a4e8
extern u32  gUVMask;               // 0x015366b8 (bitset<11> mask)
template <class T, class D> struct SVecBase {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    SVecBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    explicit SVecBase(u32 n) {
        mpBegin = n ? (T*)EAAlloc(n * sizeof(T), "Graphics", 0, 0, ALLOC_H, 0xd1) : 0;
        mpEnd = mpBegin + n;
        mpCapacity = mpEnd;
        for (T* p = mpBegin; n; --n) { *p = T(); ++p; }
    }
    ~SVecBase() { if (mpBegin && ((u32*)mpBegin)[-1] != 0) EAFree(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
    void erase(T* first, T* last) {
        xmemcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd = mpEnd - (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
    void resize(u32 n, const T& v) {
        u32 cur = (u32)(mpEnd - mpBegin);
        if (cur < n) static_cast<D*>(this)->insert(mpEnd, n - cur, v);
        else erase(mpBegin + n, mpEnd);
    }
    void push_back(const T& v) {
        if (mpEnd < mpCapacity) { if (mpEnd) *mpEnd = v; ++mpEnd; }
        else static_cast<D*>(this)->DoInsertValue(mpEnd, v);
    }
};
struct UIntVec : SVecBase<u32, UIntVec> {
    UIntVec() {}
    explicit UIntVec(u32 n) : SVecBase<u32, UIntVec>(n) {}
    void DoInsertValue(u32* pos, const u32& v);                    // 0x004558a0
};
struct IntVec_s0071_8640 : SVecBase<int, IntVec_s0071_8640> {
    IntVec_s0071_8640() {}
    explicit IntVec_s0071_8640(u32 n) : SVecBase<int, IntVec_s0071_8640>(n) {}
    void insert(int* pos, u32 n, const int& v);                    // 0x004cea40
};
struct Vec2Vec : SVecBase<Vec2_s0071_8640, Vec2Vec> {
    void reserve(u32 n);                                           // 0x00473e40
    void DoInsertValue(Vec2_s0071_8640* pos, const Vec2_s0071_8640& v);                  // 0x00476000
    void assign(const Vec2Vec& o);                                 // 0x00473b00
};
struct Byte4Vec : SVecBase<Byte4, Byte4Vec> {
    void reserve(u32 n);                                           // 0x00714cd0
    void DoInsertValue(Byte4* pos, const Byte4& v);                // 0x00715350
    void assign(const Byte4Vec& o);                                // 0x00715250
};
template <class V> struct Slot { V v; u32 pad[2]; };
struct VertexVec {
    Vertex6* mpBegin; Vertex6* mpEnd; Vertex6* mpCapacity;
    void resize(u32 n);                                            // 0x00717890 masked
};
void __cdecl SortVertexOrder(int* first, int* last, VertexVec* verts);   // 0x00717960
struct Section {
    u32 flags; int count; char pad8[0x28];
    Slot<IntVec_s0071_8640> tex[4];    // +0x30
    Slot<IntVec_s0071_8640> col[2];    // +0x80
    IntVec_s0071_8640 indices;         // +0xa8
    char padB4[0xd0 - 0xb4];
};
struct MeshBuilderUV {
    char pad0[0x30];
    Slot<Vec2Vec> tex[4];  // +0x30
    Slot<Byte4Vec> col[2]; // +0x80
    char padA8[0xd0 - 0xa8];
    Section* mpSectionsBegin;   // +0xd0
    Section* mpSectionsEnd;     // +0xd4

    void CompactAttributeVertices();
};
static inline bool SameVertex(const Vertex6* p, const Vertex6* q)
{
    for (int k = 0; k < 4; ++k)
        if (p->a[k] != q->a[k]) return false;
    for (int k = 0; k < 2; ++k)
        if (p->b[k] != q->b[k]) return false;
    return true;
}
static inline void Bump(u32& c, int& id)
{
    if (c != 0xffffffff) {
        ++c;
        id = (id < (int)c) ? (int)c : id;
    }
}
struct ElemD0
{
    u8    pad00[0xc];    // +0x00
    void* mpAux;         // +0x0c  auxiliary pointer forwarded to the range helpers
    u8    pad10[0xd0 - 0x10];
};
// ---- items of slice s00718640 end

// ---- items of slice s00719620 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <typename T>
struct spv {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAlloc[1];
    spv() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~spv() throw();
};
struct T28 {
    spv<int> m0;      // +0x00
    uint32_t m1;      // +0x10
    spv<int> m2;      // +0x14
    uint32_t m3;      // +0x24
    T28() {}
    ~T28() throw();
    T28(const T28&);
    T28& operator=(const T28&);
};
struct T50 {
    spv<int> m0;      // +0x00
    uint32_t m1;      // +0x10
    spv<int> m2;      // +0x14
    uint32_t m3;      // +0x24
    spv<int> m4;      // +0x28
    uint32_t m5;      // +0x38
    spv<int> m6;      // +0x3c
    uint32_t m7;      // +0x4c
    T50() {}
    ~T50() throw();
    T50(const T50&);
    T50& operator=(const T50&);
};
struct T140 {
    uint32_t mData[0x34];
    T140();
    T140(const T140&);
    ~T140();
    T140& operator=(const T140&);
};
struct Ref;
struct FixedIdVector6_s0071_9620 {
    uint32_t mData[6];
    void DoAssign(const FixedIdVector6_s0071_9620&);
};
struct FixedEntryVector3 { uint32_t mData[3]; void DoAssign(const FixedEntryVector3&); };
struct Obj8C {
    uint32_t mId;             // +0x00
    uint32_t mFlags;          // +0x04
    uint16_t mA;              // +0x08
    uint16_t mB;              // +0x0a
    Ref* mRef;                // +0x0c
    uint32_t mX;              // +0x10
    FixedIdVector6_s0071_9620 mV6;       // +0x14
    FixedEntryVector3 mV3;    // +0x2c
    uint32_t mPad[0x14];      // rest up to 0x8c
};
void SpFree(void* p);                                       // 0x00f47380
void* SpAlloc(uint32_t size, const char* area, int a, int b, const char* file, int line); // 0x00f473a0
T28*  UninitMove28(T28* first, T28* last, T28* dest);        // 0x00718570
void  Destroy28(T28* first, T28* last, T28* dest);           // 0x00714c70
T28*  FillN28(T28* dest, uint32_t n, const T28* value, T28* extra); // 0x007184a0
T28*  MoveUninit28(T28* dest, T28* first, T28* last, T28* extra);   // 0x00718420
void  FillRange28(T28* first, T28* last, const T28* value);  // 0x00719200
void  CopyBackward28(T28* first, T28* last, T28* dest);      // 0x00718640
T50*  UninitMove50(T50* first, T50* last, T50* dest);        // 0x00716650
void  Destroy50(T50* first, T50* last, T50* dest);           // 0x00714a20
T50*  FillN50(T50* dest, uint32_t n, const T50* value, T50* extra); // 0x00716540
T50*  MoveUninit50(T50* dest, T50* first, T50* last, T50* extra);   // 0x007164c0
void  FillRange50(T50* first, T50* last, const T50* value);  // 0x00718520
void  CopyBackward50(T50* first, T50* last, T50* dest);      // 0x00717b70
void  Obj8C_Assign(Obj8C* dst, const Obj8C* src);
struct Vec28 {
    T28* mpBegin; T28* mpEnd; T28* mpCapacity; uint32_t mAlloc[1];
    void insert(T28* position, uint32_t n, const T28& value);
    void resize(uint32_t n);
};
struct Vec50 {
    T50* mpBegin; T50* mpEnd; T50* mpCapacity; uint32_t mAlloc[1];
    void insert(T50* position, uint32_t n, const T50& value);
    void resize(uint32_t n);
    void erase(T50* first, T50* last);       // 0x00719390, out of line
};
struct Vec140 {
    T140* mpBegin; T140* mpEnd; T140* mpCapacity; uint32_t mAlloc[1];
    void resize(uint32_t n);
    void DoInsertValues(T140* position, uint32_t n, const T140& value); // 0x007193e0
    void erase(T140* first, T140* last);                                 // 0x00719330
};
// ---- items of slice s00719620 end

// ---- items of slice s00719e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector2_s0071_9e10 { float x, y; };
struct cSPVector3_s0071_9e10 { float x, y, z; };
struct tMDUByte4 { unsigned char a, b, c, d; };
template <typename T>
struct spvec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAlloc[1];
    spvec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~spvec() { if (mpBegin && ((uint32_t*)mpBegin)[-1]) SpFree(mpBegin); }
    void clear();
    void erase(T* first, T* last);
    void resize(uint32_t n);
    void DoInsertValue(T* position, const T& value);
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            if (mpEnd)
                *mpEnd = value;
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};
template <typename T>
struct spvec1 { spvec<T> v; uint32_t mAfter; };
struct T28_s0071_9e10 {
    int* mB0; int* mE0; int* mC0; uint32_t mA0;   // +0x00
    uint32_t mX;                                  // +0x10
    int* mB1; int* mE1; int* mC1; uint32_t mA1;   // +0x14
    uint32_t mY;                                  // +0x24
    T28_s0071_9e10() { mB0 = 0; mE0 = 0; mC0 = 0; mB1 = 0; mE1 = 0; mC1 = 0; }
    ~T28_s0071_9e10() throw() { if (mB1 && ((uint32_t*)mB1)[-1]) SpFree(mB1);
                     if (mB0 && ((uint32_t*)mB0)[-1]) SpFree(mB0); }
};
struct Vec28_s0071_9e10 {
    T28_s0071_9e10* mpBegin; T28_s0071_9e10* mpEnd; T28_s0071_9e10* mpCapacity; uint32_t mAlloc[1];
    void insert(T28_s0071_9e10* position, uint32_t n, const T28_s0071_9e10& value);   // 0x00719a00
    void erase(T28_s0071_9e10* first, T28_s0071_9e10* last);                          // 0x007199b0
    void resize(uint32_t n);                                    // 0x0071a930
};
struct Mat34 { float m[12]; };
struct Mat34Vec {
    Mat34*   mpBegin;      // +0x00
    Mat34*   mpEnd;        // +0x04
    Mat34*   mpCapacity;   // +0x08
    uint32_t mAlloc[1];    // +0x0c
    uint32_t mAfter;       // +0x10
    void erase(void* first, void* last);                     // 0x009c69f0
    void resize(uint32_t n, const Mat34& value);             // 0x00717820
};
struct Vec3Erase {
    cSPVector3_s0071_9e10* mpBegin;   // +0x00
    cSPVector3_s0071_9e10* mpEnd;     // +0x04
    cSPVector3_s0071_9e10* mpCapacity; // +0x08
    uint32_t    mAlloc[1]; // +0x0c
    void erase(void* first, void* last);                     // 0x0050f740
};
struct UVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t mAlloc; uint32_t mAfter;
    void DoInsertValue(uint32_t* position, const uint32_t& value);   // 0x004558a0 (ret 8)
    void push_back(const uint32_t& value)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p)
                *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    void clear()
    {
        uint32_t* first = mpBegin;
        uint32_t* last = mpEnd;
        xmemcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd = mpEnd - (last - first);
    }
};
struct T140_s0071_9e10 {
    uint32_t mMask;          // +0x00  which attribute streams are present (bit0 position .. bit7 colour 1)
    int      mCount;         // +0x04  number of vertices emitted so far
    UVec     mAttr[8];       // +0x08  position, normal, 4x texcoord, 2x colour index streams
    UVec     mUnk;           // +0xa8
    UVec     mIndices;       // +0xbc  triangle/line index list
T140_s0071_9e10();
~T140_s0071_9e10();
T140_s0071_9e10(const T140_s0071_9e10&);
    void Destroy();          // 0x007146c0
};
struct Batch {
    int      mType;          // +0x00  primitive type (4 = triangle list)
    uint32_t mSection;       // +0x04
    int      mStart;         // +0x08  first index in the section's index list
    int      mEnd;           // +0x0c  -1 while open
    int      mExtra;         // +0x10
};
struct RefCounted {
    void** mpVtbl;      // +0x0
    long   mnRefCount;  // +0x4
    int Release()
    {
        long n = _InterlockedDecrement(&mnRefCount);
        if (n == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            ((void (__thiscall*)(RefCounted*, int))mpVtbl[0])(this, 1);
            return 0;
        }
        return n;
    }
};
struct cMeshBuilder_s0071_9e10 {
    char pad_00[0x8];
    spvec1<cSPVector3_s0071_9e10> mPositions;                   // +0x08
    spvec1<cSPVector3_s0071_9e10> mNormals;                     // +0x1c
    spvec1<cSPVector2_s0071_9e10> mTexCoords[4];                // +0x30
    spvec1<tMDUByte4>  mColors[2];                   // +0x80
    spvec1<int>        mV0;                          // +0xa8
    spvec1<int>        mV1;                          // +0xbc
    spvec1<T140_s0071_9e10>       mSections;                    // +0xd0
    spvec1<Batch>      mV2;                          // +0xe4   draw batches (0x14-byte element)
    spvec1<uint64_t>   mV3;                          // +0xf8   (8-byte element)
    Mat34Vec           mV4;                          // +0x10c  0x30-byte transform records
    spvec1<T28_s0071_9e10>        mV5;                          // +0x120
    spvec1<int>        mV6;                          // +0x134
    RefCounted*        mMeshData;                    // +0x148
    uint32_t           mKey;                         // +0x14c
    bool               mInMesh;                      // +0x150
    char pad_151[3];
    int                mPrimType;                    // +0x154  current primitive type (4 list, 9 polygon)
    int                m158;                         // +0x158
    int                m15c;                         // +0x15c
    int                m160;                         // +0x160
    int                m164;                         // +0x164
    int                m168;                         // +0x168
    int                m16c;                         // +0x16c
    int                m170;                         // +0x170
    int                m174;                         // +0x174
    int                m178;                         // +0x178
    int                m17c;                         // +0x17c
    int                m180;                         // +0x180
    int                m184;                         // +0x184
    UVec               mPrim[8];                     // +0x188  per-vertex attribute indices of the current primitive
                                                     //         (position, normal, 4x texcoord, 2x colour)

    void BeginMesh();
    void EndPrimitive();
    void ClearMeshInfo();
    void TransformStreams(uint32_t n);
};
void __stdcall mV5_DestroyRange(void* first, void* last);    // 0x00714f20
void __stdcall mV6_DestroyRange(void* first, void* last);    // 0x00714b40
template <typename T, int ES>
static __forceinline void DropTailDiv(T* begin, T*& end)
{
    int n = (int)((const char*)end - (const char*)begin);
    end = (T*)((char*)end - (n / ES) * ES);
}
template <typename T, int SH>
static __forceinline void DropTailShift(T* begin, T*& end)
{
    int n = (int)((const char*)end - (const char*)begin);
    end = (T*)((char*)end - ((n >> SH) << SH));
}
static __forceinline bool TestBit11(unsigned mask, unsigned pos)
{
    return pos < 11 && (mask & (1u << pos)) != 0;
}
static __forceinline void SetBit(unsigned& mask, unsigned bit, bool on)
{
    if (on)
        mask |= bit;
    else
        mask &= ~bit;
}
static __forceinline bool IsSingle(const UVec& v)
{
    return (((char*)v.mpEnd - (char*)v.mpBegin) & ~3) == 4;
}
// ---- items of slice s00719e10 end

// ---- items of slice s0071ac50 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);             // 0x00f473a0
void operator delete[](void* p);                           // 0x00f47380
namespace EA {
namespace COM {
class IRefCount_s0071_ac50 { public:
    virtual int AddRef() = 0;   // slot 0
    virtual int Release() = 0;  // slot 1
};
}
}
struct RefCountTemplate_s0071_ac50 {
    virtual ~RefCountTemplate_s0071_ac50();   // slot 0: scalar deleting dtor
    long mnRefCount;               // +0x4
    RefCountTemplate_s0071_ac50() { _InterlockedExchange(&mnRefCount, 0); }
    int AddRef() { return _InterlockedExchangeAdd(&mnRefCount, 1) + 1; }
    int Release()
    {
        int n = _InterlockedExchangeAdd(&mnRefCount, -1) - 1;
        if (n == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            delete this;
        }
        return n;
    }
};
template <typename T>
struct sp_vector {
    T* mpBegin;          // +0x0
    T* mpEnd;            // +0x4
    T* mpCapacity;       // +0x8
    uint32_t mAlloc[2];  // +0xc  sp_vector_allocator
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);  // out of line
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            ::new (p) T(value);
        } else
            DoInsertValue(mpEnd, value);
    }
};
template <typename T, int N>
struct fixed_vector_base {
    T* mpBegin;            // +0x00
    T* mpEnd;              // +0x04
    T* mpCapacity;         // +0x08
    uint32_t mOverflow;    // +0x0c
    void* mpPoolBegin;     // +0x10
    uint32_t mUnused;      // +0x14
    uint32_t mBuffer[(sizeof(T) * N) / 4];  // +0x18
    fixed_vector_base()
    {
        mpBegin = mpEnd = (T*)mBuffer;
        mpPoolBegin = mBuffer;
        mpCapacity = (T*)mBuffer + N;
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    void DoInsertValue(T* position, const T& value);  // out of line
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            ::new (p) T(value);
        } else
            DoInsertValue(mpEnd, value);
    }
};
struct bitset11 {
    uint32_t mWord;
    bool test(uint32_t i) const
    {
        if (i < 11)
            return (mWord & (1u << (i & 31))) != 0;
        return false;
    }
};
struct cSPVector2_s0071_ac50 { float x, y; };
struct cSPVector3_s0071_ac50 { float x, y, z; };
struct tMDUByte4_s0071_ac50 { unsigned char c[4]; };
struct cMDBoneTransform { float m[12]; };            // 0x30
struct cEltArrayRef {
    int mNumElts;                     // +0x0
    unsigned char* mData;             // +0x4
    unsigned short mEltSize;          // +0x8
    unsigned short mEltStride;        // +0xa
    EA::COM::IRefCount_s0071_ac50* mDataRC;      // +0xc  AutoRefCount<IRefCount>

    cEltArrayRef() : mNumElts(0), mData(0), mEltSize(0), mEltStride(0), mDataRC(0) {}
    cEltArrayRef(int n, const void* data, unsigned short size, unsigned short stride)
        : mNumElts(n), mData((unsigned char*)data), mEltSize(size), mEltStride(stride), mDataRC(0) {}
    template <typename T>
    explicit cEltArrayRef(const sp_vector<T>& v)
        : mNumElts(v.size()), mData((unsigned char*)v.mpBegin),
          mEltSize(sizeof(T)), mEltStride(sizeof(T)), mDataRC(0) {}
    __forceinline cEltArrayRef(const cEltArrayRef& o)
        : mNumElts(o.mNumElts), mData(o.mData), mEltSize(o.mEltSize),
          mEltStride(o.mEltStride), mDataRC(o.mDataRC)
    {
        if (mDataRC)
            mDataRC->AddRef();
    }
    ~cEltArrayRef()
    {
        if (mDataRC)
            mDataRC->Release();
    }
    cEltArrayRef& operator=(const cEltArrayRef& o)
    {
        mNumElts = o.mNumElts;
        mData = o.mData;
        mEltSize = o.mEltSize;
        mEltStride = o.mEltStride;
        EA::COM::IRefCount_s0071_ac50* old = mDataRC;
        if (o.mDataRC != old) {
            if (o.mDataRC)
                o.mDataRC->AddRef();
            mDataRC = o.mDataRC;
            if (old)
                old->Release();
        }
        return *this;
    }
};
typedef cEltArrayRef cIndexArrayRef;
enum tMDSemantic {
    kSemPosition = 1, kSemNormal = 2, kSemTangent = 3, kSemBinormal = 4,
    kSemColor = 5, kSemTexCoord = 8, kSemBoneIndices = 9, kSemBoneWeights = 10,
    kSemMorphPosition = 0xc, kSemMorphNormal = 0xd, kSemBonePose = 0x12,
    kSemSubsetID = 0x14, kSemSubsetMaterial = 0x15
};
struct cMDElementArray {
    int mSemantic;       // +0x0  tMDSemantic
    int mNumber;         // +0x4
    int mType;           // +0x8  tMDDataType
    int mClass;          // +0xc  tMDElementClass
    cEltArrayRef mArray; // +0x10
    cMDElementArray(int sem, int number, int type, int cls, const cEltArrayRef& a)
        : mSemantic(sem), mNumber(number), mType(type), mClass(cls), mArray(a) {}
    __forceinline cMDElementArray(const cMDElementArray& o)
        : mSemantic(o.mSemantic), mNumber(o.mNumber), mType(o.mType), mClass(o.mClass),
          mArray(o.mArray) {}
};
struct cMDFormatEntry {
    short mElts;
    short mIndices;
    cMDFormatEntry(short elts, short indices) : mElts(elts), mIndices(indices) {}
};
struct IndexArrayFixedVector : fixed_vector_base<cIndexArrayRef, 3> {
    ~IndexArrayFixedVector();   // 0x0041f9b0 (equiv t3)
};
struct FormatFixedVector : fixed_vector_base<cMDFormatEntry, 6> {
    ~FormatFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
};
struct cMDSection {
    cIndexArrayRef mVertIndices;          // +0x00
    int mNumVertices;                     // +0x10
    FormatFixedVector mFormat;            // +0x14
    IndexArrayFixedVector mEltIndices;    // +0x44
    cMDSection() : mNumVertices(0) {}
    cMDSection(const cMDSection& o);      // out of line (0x0042cba0)
};
struct cMDPrimitive { int mPrimType, mSection, mStart, mEnd, mSubset; };
struct cMeshData : RefCountTemplate_s0071_ac50 {
    sp_vector<cMDElementArray> mEltArrays;   // +0x08
    sp_vector<cMDSection> mSections;         // +0x1c
    sp_vector<cMDPrimitive> mPrimitives;     // +0x30
    sp_vector<void*> mAttachments;           // +0x44
    cMeshData() {}
    virtual ~cMeshData();
};
struct MeshDataPtr {
    cMeshData* mp;
    __forceinline MeshDataPtr& operator=(cMeshData* p)
    {
        if (p != mp) {
            cMeshData* old = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    cMeshData* operator->() const { return mp; }
};
void MeshData_ResolveArrays(cMeshData* md);   // 0x007320f0 (walks every elt/index array ref)
struct cSubset { unsigned int mID; unsigned int mMaterialID; };
struct cBuilderSection {
    bitset11 mVertexFormat;               // +0x00
    int mNumVertices;                     // +0x04
    sp_vector<int> mPositionIndices;      // +0x08
    sp_vector<int> mNormalIndices;        // +0x1c
    uint32_t pad_30[0x78 / 4];            // +0x30
    sp_vector<int> mAttribIndices;        // +0xa8  (tex coord / colour index stream)
    sp_vector<int> mVertIndices;          // +0xbc
};
struct cBoneWeights {
    sp_vector<int> mIndices;              // +0x00
    sp_vector<float> mWeights;            // +0x14
};
struct cMorphTarget {
    sp_vector<int> mPositionIndices;          // +0x00
    sp_vector<cSPVector3_s0071_ac50> mPositionDeltas;    // +0x14
    sp_vector<int> mNormalIndices;            // +0x28
    sp_vector<cSPVector3_s0071_ac50> mNormalDeltas;      // +0x3c
};
class cMeshBuilder_s0071_ac50 {
public:
    void CreateMeshData();
    void ClearMeshInfo();                              // 0x0071a650

    void* mpVtbl;                                      // +0x000
    int mRefCount;                                     // +0x004
    sp_vector<cSPVector3_s0071_ac50> mPositions;                  // +0x008
    sp_vector<cSPVector3_s0071_ac50> mNormals;                    // +0x01c
    sp_vector<cSPVector2_s0071_ac50> mTexCoords[4];               // +0x030
    sp_vector<tMDUByte4_s0071_ac50> mColors[2];                   // +0x080
    sp_vector<cSPVector3_s0071_ac50> mTangents;                   // +0x0a8
    sp_vector<cSPVector3_s0071_ac50> mBinormals;                  // +0x0bc
    sp_vector<cBuilderSection> mSections;              // +0x0d0
    sp_vector<cMDPrimitive> mPrimitives;               // +0x0e4
    sp_vector<cSubset> mSubsets;                       // +0x0f8
    sp_vector<cMDBoneTransform> mBonePoses;            // +0x10c
    sp_vector<cBoneWeights> mBoneWeightsArray;         // +0x120
    sp_vector<cMorphTarget> mMorphTargetArray;         // +0x134
    MeshDataPtr mMeshData;                             // +0x148
};
enum { kDataFloat2 = 2, kDataFloat3 = 3, kDataUByte4 = 5, kDataInt = 6,
       kDataMatrix = 0xe, kDataFloat1x = 0x81, kDataFloat3x = 0x83 };
// ---- items of slice s0071ac50 end

// ---- items of slice s0071c900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern const float   g_angle2Pi;   // 0x0162a8e0  (2*pi)
#pragma intrinsic(sin, cos)
struct IVt {
    void** mpVtbl;      // +0x0
};
typedef void (__thiscall* Fn0)(IVt*);
typedef void (__thiscall* Fn1)(IVt*, int);
typedef void (__thiscall* Fn2)(IVt*, int, int);
struct Vec3_s0071_c900 {
    float x, y, z;
    Vec3_s0071_c900(float a, float b, float c) : x(a), y(b), z(c) {}
};
typedef void (__thiscall* FnP)(IVt*, const Vec3_s0071_c900&);
typedef void (__thiscall* FnPi)(IVt*, const Vec3_s0071_c900&, int);
typedef void (__thiscall* FnPv)(IVt*, const void*);
struct Vector3 {
    float x, y, z;
};
extern const Vector3 g_axisX;      // 0x01536700
extern const Vector3 g_axisY;      // 0x0153670c
extern const Vector3 g_axisZ;      // 0x01536718
typedef void (__thiscall* FnPvi)(IVt*, const void*, int);
typedef void (__thiscall* FnVii)(IVt*, int, const int*, int);
static const int s_boxQuads[6][4] = {
    { 1, 3, 7, 5 },
    { 2, 0, 4, 6 },
    { 3, 2, 6, 7 },
    { 0, 1, 5, 4 },
    { 4, 5, 7, 6 },
    { 2, 3, 1, 0 },
};
// ---- items of slice s0071c900 end

// ---- items of slice s0071d550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
extern const float g_angleStep;    // 0x0162a8e0  sphere row angle step scale
extern const float g_subdivK;      // 0x01471064  segment falloff scale
extern const float g_discStep;     // 0x015366f0  disc row angle step scale
#pragma intrinsic(sin, cos, fabs)
struct Rend {
    virtual void v0() = 0;                          // +0x00
    virtual void v1() = 0;                          // +0x04
    virtual void v2() = 0;                          // +0x08
    virtual void v3() = 0;                          // +0x0C
    virtual void v4() = 0;                          // +0x10
    virtual void v5() = 0;                          // +0x14
    virtual void v6(Vector3* p) = 0;                // +0x18
    virtual void v7(Vector3* p) = 0;                // +0x1C
    virtual void v8(Vector3* p, int n) = 0;         // +0x20
    virtual void v9() = 0;                          // +0x24
    virtual void v10() = 0;                         // +0x28
    virtual void v11() = 0;                         // +0x2C
    virtual void v12() = 0;                         // +0x30
    virtual void v13() = 0;                         // +0x34
    virtual void v14(const void* p, int n) = 0;     // +0x38
    virtual void v15() = 0;                         // +0x3C
    virtual void v16() = 0;                         // +0x40
    virtual void v17() = 0;                         // +0x44
    virtual void v18() = 0;                         // +0x48
    virtual void v19(int n) = 0;                    // +0x4C
    virtual void v20(int n) = 0;                    // +0x50
    virtual void v21(int n) = 0;                    // +0x54
    virtual void v22(int n) = 0;                    // +0x58
    virtual void v23() = 0;                         // +0x5C
    virtual void v24() = 0;                         // +0x60
    virtual void v25(int a, int b) = 0;             // +0x64
    virtual void v26() = 0;                         // +0x68
    virtual void v27() = 0;                         // +0x6C
    virtual void v28() = 0;                         // +0x70
    virtual void v29() = 0;                         // +0x74
    virtual void v30() = 0;                         // +0x78
    virtual void v31() = 0;                         // +0x7C
    virtual void v32(int n) = 0;                    // +0x80
    virtual void v33() = 0;                         // +0x84
    virtual void v34() = 0;                         // +0x88
    virtual void v35(int a, int b, float f) = 0;    // +0x8C
};
extern Vector3 g_axis;             // 0x01536718  fixed normal for the sphere cap
// ---- items of slice s0071d550 end

// ---- items of slice s0071e390 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
struct VecInt {
    int* mpBegin; int* mpEnd; int* mpCapacity; int mAllocPad; int* mpFixed;
    void DoInsertValues(int* position, unsigned n, const int* value);   // 0x0071e870
    void DoInsertValue(int* position, const int& value);               // 0x004558a0
    void reserve(unsigned n);                                          // 0x004e0880
    void resize(unsigned n);                                           // 0x0071ef50
    int* erase(int* first, int* last);                                 // 0x004ce270
    void push_back(const int& v)
    {
        if (mpEnd < mpCapacity) {
            int* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
// ---- items of slice s0071e390 end

// @ 0x00714050
void AdapterList::Remove(void* item)
{
    int n = (int)((char*)mVec.mpEnd - (char*)mVec.mpBegin) >> 2;
    int i = 0;
    if (n > 0) {
        char* p = (char*)mVec.mpBegin;
        do {
            if (*(void**)p == item)
                return;
            ++i;
            p += 4;
        } while (i < n);
    }
    SmartPtr local(item);
    mVec.push_back(&local);
}

// @ 0x007140e0
__declspec(noinline) void __cdecl CollectTextures(void* obj, void* outVec, TextureFilter filter)
{
    int n = (*(int*)((char*)obj + 0xc) - *(int*)((char*)obj + 8)) >> 2;
    int i = 0;
    if (n > 0) {
        do {
            int element = *(int*)(*(int*)((char*)obj + 8) + i * 4);
            if (*(short*)(element + 4) == 0x20d) {
                int j = 0;
                if (0 < *(int*)(element + 0xc)) {
                    int* p = (int*)(element + 0x14);
                    do {
                        int v = *p;
                        if (v != 0 && (filter == 0 || filter((void*)v))) {
                            FUN_711170(outVec);
                            int* slot = (int*)((char*)outVec + 4);
                            int* cur  = (int*)(*slot - 4);
                            int old   = *cur;
                            if (v != old) {
                                _InterlockedExchangeAdd((volatile long*)(v + 8), 1);
                                *cur = v;
                                if (old != 0) {
                                    int* rc = (int*)(old + 8);
                                    if (_InterlockedExchangeAdd((volatile long*)rc, -1) < 1)
                                        _InterlockedExchangeAdd((volatile long*)rc, 1);
                                    else
                                        _InterlockedExchangeAdd((volatile long*)rc, 0);
                                }
                            }
                        }
                        ++p;
                        ++j;
                    } while (j < *(int*)(element + 0xc));
                }
            }
            ++i;
        } while (i < n);
    }
}

// @ 0x007141e0
void __cdecl DispatchAll(DispatchTarget* obj, void* a, void* filter)
{
    for (void** it = obj->mB8; it != obj->mBC; ++it) {
        void* element = *it;
        if (element)
            ((MaterialManager*)GetMaterialManager())->at3c(element, (uint32_t)a, (uint32_t)filter);
    }
    for (void** it2 = obj->mF4; it2 != obj->mF8; ++it2) {
        void* element = *it2;
        if (element)
            CollectTextures(element, a, (TextureFilter)filter);
    }
}

// @ 0x00714260
void __cdecl CollectMaterials(uint32_t* ids, int n, void** out)
{
    int i = 0;
    if (n > 0) {
        do {
            uint32_t id = ids[i];
            void* item = *(void**)((char*)((MaterialManager*)GetMaterialManager())->at28(id) + 0x1c);
            if (item != 0 && *out == 0) {
                void* obj = EastlNew(0x20, (const char*)0x13eb8a4, 0, 0, 0, 0);
                if (obj) {
                    // two stores to +4: the base vtable then the final one; keep the first alive.
                    *(void* volatile*)((char*)obj + 4) = (void*)0x13ef094;
                    *(uint32_t*)((char*)obj + 8) = 0;
                    *(void**)obj = (void*)0x140cca4;
                    *(void**)((char*)obj + 4) = (void*)0x140cca0;
                    *(uint32_t*)((char*)obj + 0xc) = 0;
                    *(uint32_t*)((char*)obj + 0x10) = 0;
                    *(uint32_t*)((char*)obj + 0x14) = 0;
                } else {
                    obj = 0;
                }
                *out = obj;
                (*(void(__thiscall**)(void*))obj)(obj);
                ((AdapterList*)*out)->Remove(item);
            }
            ++i;
        } while (i < n);
    }
}

// @ 0x00714310
void ResourceAdapter::SetName(const void* name)
{
    uint32_t key[3] = { 0, 0, 0 };
    SPKeyFromName(key, name, 0, 0);
    mKey = key[0];
}

// @ 0x00714350
void ResourceAdapter::SetNameAndCall(const void* a, const void* name)
{
    uint32_t key[3] = { 0, 0, 0 };
    SPKeyFromName(key, name, 0, 0);
    void* fn = (*(void***)this)[0x48 / 4];
    ((void(__thiscall*)(void*, const void*, uint32_t))fn)(this, a, key[0]);
}

// @ 0x007143a0
void ResourceAdapter::SetFlag(int value)
{
    int* p = (int*)((char*)this + 0x158);
    if (*p < 0) {
        void* fn = (*(void***)this)[0x4c / 4];
        ((void(__thiscall*)(void*, int))fn)(this, 0);
    }
    *(int*)((char*)this + 0x154) = value;
}

// @ 0x007143e0
void ResourceAdapter::Dispatch(uint8_t flags, uint32_t a, uint32_t b, uint32_t c)
{
    void** vt = *(void***)this;
    if (flags & 1) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))vt[0x68 / 4])(this, a, b, c);
    if (flags & 2) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))vt[0x6c / 4])(this, a, b, c);
    if (flags & 4) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x70 / 4])(this, a, b, 0, c);
    if (flags & 0xf8) {
        if (flags & 8)  ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x70 / 4])(this, a, b, 1, c);
        if (flags & 0x10) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x70 / 4])(this, a, b, 2, c);
        if (flags & 0x20) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x70 / 4])(this, a, b, 3, c);
        if (flags & 0x40) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x74 / 4])(this, a, b, 0, c);
        if (flags & 0x80) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x74 / 4])(this, a, b, 1, c);
    }
}

// @ 0x007144b0
void __cdecl Copy24(uint32_t* dst, uint32_t* end, const uint32_t* src)
{
    for (; dst != end; dst += 6) {
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
        dst[3] = src[3]; dst[4] = src[4]; dst[5] = src[5];
    }
}

// @ 0x007144f0
__declspec(noinline) bool RecordCmp::less(uint32_t a, uint32_t b) const
{
    const uint32_t* base = *mpBase;
    const uint32_t* pa = base + a * 6;
    const uint32_t* pb = base + b * 6;
    for (int i = 0; i < 4; ++i) {
        if (pa[i] < pb[i]) return true;
        if (pa[i] != pb[i]) return false;
    }
    for (int i = 4; i < 6; ++i) {
        if (pa[i] < pb[i]) return true;
        if (pa[i] != pb[i]) return false;
    }
    return false;
}

// @ 0x00714560
void PairTable::Set(uint32_t key, uint32_t value)
{
    int n = (int)((char*)mpEnd - (char*)mpBegin) >> 3;
    if (n > 0) {
        uint32_t* p = mpBegin;
        for (int i = 0; i < n; ++i, p += 2) {
            if (*p == key) {
                mpBegin[i * 2 + 1] = value;
                return;
            }
        }
    }
}

// @ 0x007145b0
uint32_t* MatrixTable::Set(uint32_t index, const uint32_t* mat)
{
    uint32_t* dst = (uint32_t*)((char*)mpData + index * 0x30);
    dst[0] = mat[0]; dst[1] = mat[4]; dst[2] = mat[8];  dst[3] = mat[12];
    dst[4] = mat[1]; dst[5] = mat[5]; dst[6] = mat[9];  dst[7] = mat[13];
    dst[8] = mat[2]; dst[9] = mat[6]; dst[10] = mat[10]; dst[11] = mat[14];
    return dst + 8;
}

// @ 0x007146c0
void AdapterTeardown::Destroy()
{
    EastlFreeGuarded(mbc);
    EastlFreeGuarded(ma8);
    VectorDtorRange(m80, 0x14, 2, (void (__cdecl*)(void*))&g_vecdtor4E1BF0);
    VectorDtorRange(m30, 0x14, 4, (void (__cdecl*)(void*))&g_vecdtor4E1BF0);
    EastlFreeGuarded(m1c);
    EastlFreeGuarded(m8);
}

// @ 0x00714780
void __cdecl InsertionSortA(uint32_t* first, uint32_t* last, RecordCmp compare)
{
    if (first == last)
        return;
    uint32_t* cur = first + 1;
    if (cur == last)
        return;
    do {
        const uint32_t value = *cur;
        uint32_t* pos = cur;
        while (pos != first && compare.less(value, *(pos - 1))) {
            *pos = *(pos - 1);
            --pos;
        }
        *pos = value;
        ++cur;
    } while (cur != last);
}

// @ 0x007147e0
void __cdecl InsertionSortB(uint32_t* first, uint32_t* last, RecordCmp compare)
{
    for (uint32_t* cur = first; cur != last; ++cur) {
        uint32_t value = *cur;
        uint32_t* hole = cur;
        uint32_t* prev = cur - 1;
        while (compare.less(value, *prev)) {
            *hole = *prev;
            hole = prev;
            prev = hole - 1;
        }
        *hole = value;
    }
}

// @ 0x00714880
uint32_t* __cdecl MinOfThree(uint32_t* a, uint32_t* b, uint32_t* c, RecordCmp compare)
{
    if (compare.less(*a, *b)) {
        if (compare.less(*b, *c))
            return b;
        if (compare.less(*a, *c))
            return c;
        return a;
    }
    if (compare.less(*a, *c))
        return a;
    if (compare.less(*b, *c))
        return c;
    return b;
}

// @ 0x00714910
void* __cdecl Fill24(uint32_t* dst, uint32_t n, const uint32_t* src)
{
    for (; n != 0; --n) {
        if (dst != 0) {
            dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
            dst[3] = src[3]; dst[4] = src[4]; dst[5] = src[5];
        }
        dst += 6;
    }
    return dst;
}

// @ 0x007149a0
void __cdecl CopyFloats48(Float12* first, Float12* last, Float12* dst)
{
    for (; first != last; first += 1, dst += 1) {
        if (dst != 0) {
            float* d = dst->v;
            const float* s = first->v;
            d[0] = s[0];
            float* d2 = d + 6;
            const float* s2 = s + 6;
            d2[-5] = s2[-5];
            d2[-4] = s2[-4];
            d2[-3] = s2[-3];
            d2[-2] = s2[-2];
            d2[-1] = s2[-1];
            d2[0] = s2[0];
            d2[1] = s2[1];
            d2[2] = s2[2];
            d2[3] = s2[3];
            d2[4] = s2[4];
            d2[5] = s2[5];
        }
    }
}

// @ 0x00714a20
void* __cdecl DestroyRes50(void* first, void* last, char* out)
{
    while (first != last) {
        EastlFreeGuarded(*(void**)((char*)first + 0x3c));
        EastlFreeGuarded(*(void**)((char*)first + 0x28));
        EastlFreeGuarded(*(void**)((char*)first + 0x14));
        EastlFreeGuarded(*(void**)first);
        first = (char*)first + 0x50;
        out += 0x50;
    }
    return out;
}

// @ 0x00714ab0
void __cdecl HeapSiftUp(uint32_t* base, int root, int hole, uint32_t value, RecordCmp compare)
{
    int parent = (hole - 1) >> 1;
    if (hole > root) {
        do {
            const uint32_t parentValue = base[parent];
            if (!compare.less(parentValue, value))
                break;
            base[hole] = parentValue;
            hole = parent;
            parent = (hole - 1) >> 1;
        } while (hole > root);
    }
    base[hole] = value;
}

// @ 0x00714b40
void __stdcall DestroyRes50Range(void* first, void* last)
{
    while ((uintptr_t)first < (uintptr_t)last) {
        EastlFreeGuarded(*(void**)((char*)first + 0x3c));
        EastlFreeGuarded(*(void**)((char*)first + 0x28));
        EastlFreeGuarded(*(void**)((char*)first + 0x14));
        EastlFreeGuarded(*(void**)first);
        first = (char*)first + 0x50;
    }
}

// @ 0x00714bc0
void* __cdecl CopyPairs(uint32_t* out, uint32_t* first, uint32_t* last, uint32_t* dst)
{
    *out = (uint32_t)dst;
    if (first != last) {
        do {
            if (dst != 0) { dst[0] = first[0]; dst[1] = first[1]; }
            first += 2;
            dst += 2;
        } while (first != last);
        *out = (uint32_t)dst;
    }
    return out;
}

// @ 0x00714c00
void __cdecl HeapSiftDown(uint32_t* base, int root, int n, int hole, uint32_t value, RecordCmp compare)
{
    int child = hole * 2 + 2;
    if (child < n) {
        do {
            if (compare.less(base[child], base[child - 1]))
                --child;
            base[hole] = base[child];
            hole = child;
            child = child * 2 + 2;
        } while (child < n);
    }
    if (child == n) {
        base[hole] = base[child - 1];
        hole = child - 1;
    }
    HeapSiftUp(base, root, hole, value, compare);
}

// @ 0x00714c70
void* __cdecl DestroyRes28(void* first, void* last, char* out)
{
    while (first != last) {
        EastlFreeGuarded(*(void**)((char*)first + 0x14));
        EastlFreeGuarded(*(void**)first);
        first = (char*)first + 0x28;
        out += 0x28;
    }
    return out;
}

// @ 0x00714cd0
void Vec4::Reserve(uint32_t n)
{
    if (n <= (uint32_t)((int)((char*)mpCap - (char*)mpBegin) >> 2))
        return;
    uint32_t* dst = n ? (uint32_t*)EastlNew(n * 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    uint32_t* end = mpEnd;
    uint32_t* src = mpBegin;
    uint32_t* cur = dst;
    while (src != end) {
        if (cur != 0)
            *cur = *src;
        ++src;
        ++cur;
    }
    EastlFreeGuarded(mpBegin);
    int count = (int)((char*)mpEnd - (char*)mpBegin) >> 2;
    mpBegin = dst;
    mpEnd = dst + count;
    mpCap = dst + n;
}

// @ 0x00714e10
AdapterCtor::AdapterCtor()
: m0(0)
{
}

// @ 0x00714ec0
void __stdcall AllocAndCopy(uint32_t n, uint32_t* first, uint32_t* last)
{
    uint32_t* dst = n ? (uint32_t*)EastlNew(n * 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    if (first != last) {
        intptr_t delta = (intptr_t)((char*)first - (char*)dst);
        do {
            if (dst != 0)
                *dst = *(uint32_t*)((char*)dst + delta);
            ++dst;
        } while ((char*)dst + delta != (char*)last);
    }
}

// @ 0x00714f20
void __stdcall f714f20(Elem40* first, Elem40* last)
{
    for (Elem40* it = first; it < last; ++it) {
        void* a = it->p14;
        if (a != 0 && ((int*)a)[-1] != 0)
            ea_free(a);
        void* b = it->p0;
        if (b != 0 && ((int*)b)[-1] != 0)
            ea_free(b);
    }
}

// @ 0x00714fa0
int* __cdecl f714fa0(int* first, int* last, int pivot, Cmp4 cmp)
{
    for (;; ++first) {
        int cur;
        while ((cur = *first), cmp(cur, pivot))
            ++first;
        --last;
        while (cmp(pivot, *last))
            --last;
        if (first >= last)
            return first;
        *first = *last;
        *last = cur;
    }
}

// @ 0x00715010
int* __cdecl f715010(int* first0, int* last0, int* first1, int* last1, int* out, int** keys)
{
    while (first0 != last0 && first1 != last1) {
        if ((*keys)[*first1] < (*keys)[*first0]) {
            *out = *first1;
            ++first1;
        } else {
            *out = *first0;
            ++first0;
        }
        ++out;
    }
    out = (int*)((char*)move_ret(out, first0, (unsigned)((char*)last0 - (char*)first0)) + (last0 - first0) * 4);
    out = (int*)((char*)move_ret(out, first1, (unsigned)((char*)last1 - (char*)first1)) + (last1 - first1) * 4);
    return out;
}

// @ 0x00715090
void __cdecl f715090(int* first, int* last, Cmp4 cmp)
{
    int n = (int)(last - first);
    if (n < 2)
        return;
    for (int parent = (n - 2) / 2; parent >= 0; --parent) {
        int value = first[parent];
        adjust_heap(first, parent, n, parent, value, cmp);
    }
}

// @ 0x007150d0
void __cdecl f7150d0(int* first, int* last, Cmp4 cmp)
{
    if (last - first <= 1)
        return;
    for (int* it = last - 1; it > first; --it) {
        int value = *it;
        *it = *first;
        adjust_heap(first, 0, (int)(it - first), 0, value, cmp);
    }
}

// @ 0x00715120
Vec20& Vec20::assign(const Vec20& x)
{
    if (&x == this)
        return *this;

    char* srcBegin = x.mpBegin;
    int count = (int)(x.mpEnd - x.mpBegin) / 0x14;
    int have = (int)(mpCapacity - mpBegin) / 0x14;
    if (have < count) {
        // Not enough room: allocate a fresh block and re-seat all three pointers.
        char* buf = (char*)alloc20(count, x.mpBegin, x.mpEnd);
        ea_del(mpBegin);
        mpCapacity = buf + count * 0x14;
        mpBegin = buf;
        mpEnd = buf + count * 0x14;
        return *this;
    }

    int cur = (int)(mpEnd - mpBegin) / 0x14;
    if (cur < count) {
        // Copy the overlap, then fill the new tail with copies of the source elements.
        copy20(x.mpBegin, x.mpBegin + cur * 0x14, mpBegin);
        uninit20(mpEnd, x.mpBegin + cur * 0x14, x.mpEnd, mpEnd, 0);
        mpEnd = mpBegin + count * 0x14;
        return *this;
    }

    copy20(x.mpBegin, x.mpEnd, mpBegin);
    mpEnd = mpBegin + count * 0x14;
    return *this;
}

// @ 0x00715250
Vec4_s0071_4f20& Vec4_s0071_4f20::assign(const Vec4_s0071_4f20& x)
{
    if (&x == this)
        return *this;

    int* src = x.mpBegin;
    int count = (int)(x.mpEnd - x.mpBegin) / 4;
    int have = (int)(mpCapacity - mpBegin) / 4;
    if (have < count) {
        int* buf = (int*)alloc4(count, x.mpBegin, x.mpEnd);
        ea_del(mpBegin);
        mpBegin = buf;
        mpCapacity = buf + count;
        mpEnd = buf + count;
        return *this;
    }

    int cur = (int)(mpEnd - mpBegin) / 4;
    if (cur < count) {
        copy4(x.mpBegin, x.mpBegin + cur, mpBegin);
        uninit4(mpEnd, x.mpBegin + cur, x.mpEnd);
        mpEnd = mpBegin + count;
        return *this;
    }

    copy4(src, x.mpEnd, mpBegin);
    mpEnd = mpBegin + count;
    return *this;
}

// @ 0x00715350
void Vec4_s0071_4f20::insert(int* position, const int* value)
{
    if (mpEnd != mpCapacity) {
        // Room available: shift [position, mpEnd) right by one slot in place.
        int* v = (int*)value;
        if (v >= position && v < mpEnd)
            v = v + 1;
        if (mpEnd)
            *mpEnd = mpEnd[-1];
        int* w = mpEnd;
        while (w - 1 != position) {
            --w;
            *w = w[-1];
        }
        *position = *v;
        ++mpEnd;
        return;
    }

    // Full: allocate a buffer of twice the element count (or 1) and rebuild.
    int n = (int)(mpEnd - mpBegin);
    int need = n ? n * 2 : 1;
    int* buf = need ? (int*)ea_new(need * 4) : 0;
    int* w = buf;
    for (int* p = mpBegin; p != position; ++p) {
        if (w)
            *w = *p;
        ++w;
    }
    if (w)
        *w = *value;
    ++w;
    for (int* p = position; p != mpEnd; ++p) {
        if (w)
            *w = *p;
        ++w;
    }
    ea_del(mpBegin);
    mpBegin = buf;
    mpEnd = w;
    mpCapacity = buf + need;
}

// @ 0x00715470
void Vec48::insert(char* position, unsigned n, const void* value)
{
    if ((unsigned)((mpCapacity - mpEnd) / 0x30) < n) {
        // Grow to max(2 * count, count + n) elements and rebuild the array.
        int old = (int)(mpEnd - mpBegin) / 0x30;
        unsigned cap = old ? (unsigned)old * 2 : 1;
        unsigned need = (unsigned)old + n;
        if (need < cap)
            need = cap;
        char* buf = need ? (char*)ea_new(need * 0x30) : 0;
        char* p = (char*)uninit_copy48(mpBegin, position, buf);
        fill48(p, n, value, position);
        char* q = (char*)uninit_copy48(position, mpEnd, p + n * 0x30);
        ea_del(mpBegin);
        mpBegin = buf;
        mpEnd = q;
        mpCapacity = buf + need * 0x30;
        return;
    }

    if (n == 0)
        return;

    // Materialise `value` into a local Matrix34 first (retail copies it up front).
    char local[0x30];
    copy48_assign(local, value);

    int tail = (int)(mpEnd - position) / 0x30;
    if ((int)n < tail) {
        // Shift the last n elements out of the way, rotate, then stamp value in.
        char* moved = mpEnd - n * 0x30;
        shift48(moved, mpEnd, mpEnd, position);
        mpEnd += n * 0x30;
        move48(position, moved, mpEnd - n * 0x30);
        copy48_range(position, position + n * 0x30, local);
        return;
    }

    // Tail shorter than n: fill the new slots beyond mpEnd, then fill the rest.
    unsigned grow = n - (unsigned)tail;
    fill48b(mpEnd, grow, local, position);
    mpEnd += grow * 0x30;
    shift48(position, mpEnd, mpEnd, position);
    mpEnd += (unsigned)tail * 0x30;
    copy48_range(position, position + (unsigned)tail * 0x30, local);
}

// @ 0x00715630
void Vec8::insert_range(char* position, char* first, char* last, int)
{
    if (first == last)
        return;

    unsigned count = (unsigned)(last - first) / 8;
    unsigned spare = (unsigned)(mpCapacity - mpEnd) / 8;
    if (count <= spare) {
        unsigned tail = (unsigned)(mpEnd - position) / 8;
        if (count < tail) {
            // Room in the tail: relocate the last `count` elements to the very
            // end, slide the remaining tail right, then drop the range in.
            char* moved = mpEnd - count * 8;
            helper73fe50(mpEnd, moved, (void*)(count * 8));
            mpEnd += count * 8;
            helper73fe50(moved, position, (void*)(moved - position));
            helperac4440(first, last, position);
            return;
        }
        // Tail shorter than the range: copy the tail beyond mpEnd, copy the new
        // elements in, then shift the original tail into place.
        char* dst = position + count * 8;
        helper73fe50(mpEnd, position, (void*)(mpEnd - position));
        mpEnd += count * 8;
        helper73fe50(dst, first, (void*)(tail * 8));
        helperac4440(first, last, dst);
        return;
    }

    // Grow: allocate a new buffer and copy the three segments across.
    int old = (int)(mpEnd - mpBegin) / 8;
    unsigned cap = old ? (unsigned)old * 2 : 1;
    unsigned need = (unsigned)old + count;
    if (need < cap)
        need = cap;
    char* buf = need ? (char*)ea_new(need * 8) : 0;
    char* mid = (char*)helper4763a0(buf, mpBegin, position);
    helper714bc0(mid, first, last, mid, first);
    char* tailEnd = (char*)helper4763a0(mid + count * 8, position, mpEnd);
    ea_del(mpBegin);
    mpBegin = buf;
    mpEnd = tailEnd;
    mpCapacity = buf + need * 8;
}

// @ 0x00715900
void __cdecl f715900(int* first, int* middle, int* last, Cmp4 cmp)
{
    f715090(first, middle, cmp);
    for (int* i = middle; i < last; ++i) {
        if (cmp(*i, *first)) {
            int temp = *i;
            *i = *first;
            adjust_heap(first, 0, (int)(middle - first), 0, temp, cmp);
        }
    }
    f7150d0(first, middle, cmp);
}

// @ 0x00715980
cMeshBuilder::cMeshBuilder()
{
    mVtbl = (void*)0x140cd40;
    mp04 = 0; mp08 = 0; mp0c = 0; mp10 = 0;
    mp1c = 0; mp20 = 0; mp24 = 0;

    // Two EH-constructed arrays of 0x14-byte elements.
    eh_vector_ctor(arr30, 0x14, 4, (void*)elem_ctor_6e5790, (void*)elem_dtor_4cddd0);
    eh_vector_ctor(arr80, 0x14, 2, (void*)elem_ctor_6e5790, (void*)elem_dtor_7a41a0);

    mpa8 = 0; mpac = 0; mpb0 = 0;
    mpbc = 0; mpc0 = 0; mpc4 = 0;
    mpd0 = 0; mpd4 = 0; mpd8 = 0;
    mpe4 = 0; mpe8 = 0; mpec = 0;
    mpf8 = 0; mpfc = 0; mp100 = 0;
    mp10c = 0; mp110 = 0; mp114 = 0;
    mp120 = 0; mp124 = 0; mp128 = 0;
    mp134 = 0; mp138 = 0; mp13c = 0;
    mp148 = 0;

    m14c = 0x9f84a565u;
    m150 = 0;
    mp154 = 0;
    m158 = -1;
    mp15c = 0;
    m160 = -1;
    mp164 = 0; mp168 = 0; mp16c = 0;

    for (int i = 0; i < 0x18 / 4; ++i)
        mp170[i] = 0;
    mp188[0] = 0; mp188[1] = 0; mp188[2] = 0; mp188[3] = 0;
    mp19c = 0; mp1a0 = 0; mp1a4 = 0;

    // Second pair of EH-constructed arrays.
    eh_vector_ctor(arr1b0, 0x14, 4, (void*)elem_ctor_6e5790, (void*)elem_dtor_4e1bf0);
    eh_vector_ctor(arr200, 0x14, 2, (void*)elem_ctor_6e5790, (void*)elem_dtor_4e1bf0);

    // Zero the two trailing run arrays at +0x170..+0x180 and +0x180..+0x188.
    for (void** p = mp170; p != (void**)((char*)this + 0x180); ++p)
        *p = 0;
    for (void** p = (void**)((char*)this + 0x180); p != (void**)((char*)this + 0x188); ++p)
        *p = 0;
}

// @ 0x00715bb0
cMeshBuilder::~cMeshBuilder()
{
    mVtbl = (void*)0x140cd40;

    // Tear down the trailing EH arrays (in reverse declaration order).
    eh_vector_dtor(arr200, 0x14, 2, (void*)elem_dtor_4e1bf0);
    eh_vector_dtor(arr1b0, 0x14, 4, (void*)elem_dtor_4e1bf0);

    ea_del(mp19c);
    ea_del(mp188[0]);

    // Release the refcounted object at +0x148.
    if (mp148 != 0) {
        RefObj* obj = (RefObj*)mp148;
        int* rc = obj->refcount;
        if (--*rc == 0) {
            *rc = 1;
            ((void (__thiscall*)(RefObj*, int))obj->vtbl[0])(obj, 1);
        }
    }

    release_range_714b40(mp134, mp138);
    ea_del(mp134);

    clear_range_714f20(mp120, mp124);
    ea_del(mp120);

    ea_del(mp10c);
    ea_del(mpf8);
    ea_del(mpe4);

    release_vec_714d70((char*)this + 0xd0);
    ea_del(mpbc);
    ea_del(mpa8);

    eh_vector_dtor(arr80, 0x14, 2, (void*)elem_dtor_7a41a0);
    eh_vector_dtor(arr30, 0x14, 4, (void*)elem_dtor_4cddd0);

    ea_del(mp1c);
    ea_del(mp08);

    mVtbl = (void*)0x13eb938;   // EA::Trace::ITracerBase vtable
}

// @ 0x00715ec0
void Vec4_s0071_4f20::insert_range(int* position, const int* first, const int* last, int)
{
    if (first == last)
        return;

    int count = (int)(last - first);
    int spare = (int)(mpCapacity - mpEnd);
    if (count <= spare) {
        int tail = (int)(mpEnd - position);
        if (count < tail) {
            // Move the last `count` elements to the very end, then slide the
            // remaining tail right and drop [first,last) into the hole.
            int* moved = mpEnd - count;
            mem_copy(mpEnd, moved, (unsigned)(count * 4));
            mpEnd += count;
            int* dst = mpEnd - count - (int)((char*)moved - (char*)position);
            mem_move(dst, position, (unsigned)((char*)moved - (char*)position));
            mem_copy(position, first, (unsigned)((char*)last - (char*)first));
            return;
        }
        // Tail is shorter than the inserted range: duplicate the tail, copy the
        // new elements in, then memmove the original tail into place.
        int* out = mpEnd + count;
        int* dst = out - count;
        mem_copy(dst, position, (unsigned)((char*)mpEnd - (char*)position));
        mpEnd += count;
        mem_copy(dst + count, first, (unsigned)((char*)last - (char*)first));
        mem_move(mpEnd - count - count, first + count, (unsigned)(count * 4));
        return;
    }

    // Grow: allocate a buffer large enough and copy the three segments.
    int old = (int)(mpEnd - mpBegin);
    unsigned cap = old ? (unsigned)old * 2 : 1;
    unsigned need = (unsigned)old + (unsigned)count;
    if (need < cap)
        need = cap;
    int* buf = need ? (int*)ea_new(need * 4) : 0;
    int* p = (int*)mem_copy(buf, mpBegin, (unsigned)((char*)position - (char*)mpBegin));
    int* q = (int*)mem_copy(p, first, (unsigned)((char*)last - (char*)first));
    q = (int*)mem_copy(q, position, (unsigned)((char*)mpEnd - (char*)position));
    ea_del(mpBegin);
    mpEnd = q;
    mpBegin = buf;
    mpCapacity = buf + need;
}

// @ 0x00716080
void __cdecl f716080(int* first, int* last, int depth, Cmp4 cmp)
{
    while (((char*)last - (char*)first) > 0x70 && depth > 0) {
        int* mid = first + ((last - first) / 2);
        int pivot = *median3(first, mid, last - 1, cmp);
        int* p = f714fa0(first, last, pivot, cmp);
        --depth;
        f716080(p, last, depth, cmp);
        last = p;
    }
    if (depth == 0)
        f715900(first, last, last, cmp);
}

// @ 0x00716700
void MeshBuilder::pushV8(const Vec3& v)
{ v8.v.push_back(v); }

// @ 0x00716740
void MeshBuilder::pushV1c(const Vec3& v)
{ v1c.v.push_back(v); }

// @ 0x00716780
void MeshBuilder::pushV30(const Vec2& v, int index)
{ v30[index].v.push_back(v); }

// @ 0x007167c0
void MeshBuilder::pushColor(const Vec4_s0071_6110& c, int index)
{
    u32 packed = PackColor(c);
    v80[index].v.push_back(packed);
}

// @ 0x007168c0
void MeshBuilder::resizeV8(int n, const Vec3& v)
{
    v8.v.reserve((int)(v8.v.mpEnd - v8.v.mpBegin) + n);
    for (int i = n; i > 0; --i)
        v8.v.push_back(v);
}

// @ 0x00716930
void MeshBuilder::resizeV1c(int n, const Vec3& v)
{
    v1c.v.reserve((int)(v1c.v.mpEnd - v1c.v.mpBegin) + n);
    for (int i = n; i > 0; --i)
        v1c.v.push_back(v);
}

// @ 0x007169a0
void MeshBuilder::addColors(int index, int n, const Vec4_s0071_6110* c)
{
    EAVec<u32>& v = v80[index].v;
    v.reserve((int)(v.mpEnd - v.mpBegin) + n);
    for (int i = 0; i < n; ++i) {
        u32 packed = PackColor(c[i]);
        v.push_back(packed);
    }
}

// @ 0x00716ad0
void MeshBuilder::uniqueAdd(int key)
{
    n158 = -1;
    int n = (int)(vF8.mpEnd - vF8.mpBegin);
    int idx = 0;
    if (n > 0) {
        int* p = (int*)vF8.mpBegin;
        do {
            if (*p == key) {
                n158 = idx;
                break;
            }
            ++idx;
            p += 2;
        } while (idx < n);
    }
    if (n158 < 0) {
        n158 = (int)(vF8.mpEnd - vF8.mpBegin);
        Vec8_s0071_6110 e;
        e.a = key;
        e.b = n14c;
        vF8.push_back(e);
    }
}

// @ 0x00716bf0
void MeshBuilder::pushV188_2(u32 v, int index)
{ v188[2 + index].v.push_back(v); }

// @ 0x00716c30
void MeshBuilder::pushV188_6(u32 v, int index)
{ v188[6 + index].v.push_back(v); }

// @ 0x00716c70
void MeshBuilder::addMasked(u8 mask, u32 value)
{
    if (mask & 1)
        v188[0].v.push_back(value);
    if (mask & 2)
        v188[1].v.push_back(value);
    if (mask & 4)
        v188[2].v.push_back(value);
    if (mask & 0xf8) {
        if (mask & 8)
            v188[3].v.push_back(value);
        if (mask & 0x10)
            v188[4].v.push_back(value);
        if (mask & 0x20)
            v188[5].v.push_back(value);
        if (mask & 0x40)
            v188[6].v.push_back(value);
        if (mask & 0x80)
            v188[7].v.push_back(value);
    }
}

// @ 0x00716e40
void MeshBuilder::addPair120(int elemIdx, float value, int delta)
{
    Elem120& e = p120[elemIdx];
    u32 index = (u32)(n168 + delta);
    e.u.push_back(index);
    e.f.push_back(value);
}

// @ 0x00716ed0
void MeshBuilder::addBulk120(int elemIdx, int n, const int* idx, const float* vals)
{
    Elem120& e = p120[elemIdx];
    e.u.reserve((int)(e.u.mpEnd - e.u.mpBegin) + n);
    e.f.reserve((int)(e.f.mpEnd - e.f.mpBegin) + n);
    for (int i = 0; i < n; ++i) {
        u32 index = (u32)(n168 + idx[i]);
        e.u.push_back(index);
        e.f.push_back(vals[i]);
    }
}

// @ 0x00716fc0
void MeshBuilder::addDiff134_lo(int slot, int n, const Vec3* pts)
{
    for (int i = 0; i < n; ++i) {
        int index = n168 + i;
        const Vec3& base = *(const Vec3*)((char*)v8.v.mpBegin + index * 0xc);
        float dx = pts[i].x - base.x;
        float dy = pts[i].y - base.y;
        float dz = pts[i].z - base.z;
        Elem134& e = p134[slot];
        e.u0.push_back((u32)index);
        Vec3 d; d.x = dx; d.y = dy; d.z = dz;
        e.v14.push_back(d);
    }
}

// @ 0x007170e0
void MeshBuilder::addDiff134_hi(int slot, int n, const Vec3* pts)
{
    for (int i = 0; i < n; ++i) {
        int index = n16c + i;
        const Vec3& base = *(const Vec3*)((char*)v1c.v.mpBegin + index * 0xc);
        float dx = pts[i].x - base.x;
        float dy = pts[i].y - base.y;
        float dz = pts[i].z - base.z;
        Elem134& e = p134[slot];
        e.u28.push_back((u32)index);
        Vec3 d; d.x = dx; d.y = dy; d.z = dz;
        e.v3c.push_back(d);
    }
}

// @ 0x00717200
void MeshBuilder::addDiff134_lo1(int slot, int index, const Vec3* pt)
{
    int idx = n168 + index;
    const Vec3& base = *(const Vec3*)((char*)v8.v.mpBegin + idx * 0xc);
    Vec3 d;
    d.x = pt->x - base.x;
    d.y = pt->y - base.y;
    d.z = pt->z - base.z;
    Elem134& e = p134[slot];
    e.u0.push_back((u32)idx);
    e.v14.push_back(d);
}

// @ 0x007172f0
void MeshBuilder::addDiff134_hi1(int slot, int index, const Vec3* pt)
{
    int idx = n16c + index;
    const Vec3& base = *(const Vec3*)((char*)v1c.v.mpBegin + idx * 0xc);
    Vec3 d;
    d.x = pt->x - base.x;
    d.y = pt->y - base.y;
    d.z = pt->z - base.z;
    Elem134& e = p134[slot];
    e.u28.push_back((u32)idx);
    e.v3c.push_back(d);
}

// @ 0x007173e0
void __fastcall FUN_007173e0(SelEditor* self)
{
    int n1 = (int)(self->sizeEnd - self->sizeBegin) / 3;
    unsigned* c1 = gfxCountArray(n1);
    int n2 = (int)(self->sizeEnd - self->sizeBegin) / 3;
    unsigned* c2 = gfxCountArray(n2);
    int n3 = (int)(self->size2End - self->size2Begin) / 3;
    unsigned* c3 = gfxCountArray(n3);
    int groups = (int)(self->r28End - self->r28Begin);
    if (groups > 0) {
        for (int i = 0; i < groups; ++i) {
            SelRec28* r = self->r28Begin + i;
            int cnt = (int)(r->idxEnd - r->idxBegin);
            for (int j = 0; j < cnt; ++j) {
                if (r->weights[j] > 0.0001f)
                    ++c1[r->idxBegin[j]];
            }
        }
    }
    int groups50 = (int)(self->r50End - self->r50Begin);
    if (groups50 > 0) {
        for (int i = 0; i < groups50; ++i) {
            SelRec50* r = self->r50Begin + i;
            int cnt = (int)(r->idxEnd - r->idxBegin);
            for (int j = 0; j < cnt; ++j) {
                const float* p = r->pos + j * 3;
                if (p[0] * p[0] + p[1] * p[1] + p[2] * p[2] > 9.999999e-09f)
                    ++c2[r->idxBegin[j]];
            }
            int cnt2 = (int)(r->idx2End - r->idx2Begin);
            for (int j = 0; j < cnt2; ++j) {
                const float* p = r->pos2 + j * 3;
                if (p[0] * p[0] + p[1] * p[1] + p[2] * p[2] > 9.999999e-09f)
                    ++c3[r->idx2Begin[j]];
            }
        }
    }
    int recs = (int)(self->recEnd - self->recBegin);
    if (recs > 0) {
        for (int i = 0; i < recs; ++i) {
            SelRecD0* r = self->recBegin + i;
            if (r->idxBegin != r->idxEnd) {
                for (int j = 0; j < r->count; ++j) {
                    int idx = r->idxBegin[j];
                    if ((int)c1[idx] > 0)
                        r->flags |= 0x100;
                    if ((int)c2[idx] > 0)
                        r->flags |= 0x200;
                    if ((r->flags & 0x100) != 0 && (r->flags & 0x200) != 0)
                        break;
                }
            }
            if (r->view1Begin != r->view1End) {
                for (int j = 0; j < r->count; ++j) {
                    if ((int)c3[r->view1Begin[j]] > 0) {
                        r->flags |= 0x400;
                        break;
                    }
                }
            }
        }
    }
    if (c3 != 0 && ((int*)c3)[-1] != 0)
        EA_Free(c3);
    if (c2 != 0 && ((int*)c2)[-1] != 0)
        EA_Free(c2);
    if (c1 != 0 && ((int*)c1)[-1] != 0)
        EA_Free(c1);
}

// @ 0x00717820
void Vec30::resize(unsigned n, const void* value)
{
    unsigned cur = (unsigned)((mpEnd - mpBegin) / 0x30);
    if (cur < n)
        insert(mpEnd, n - cur, value);
    else
        erase(mpBegin + n * 0x30, mpEnd);
}

// @ 0x00717890
void Vec18::resize(unsigned n)
{
    unsigned cur = (unsigned)((mpEnd - mpBegin) / 0x18);
    if (cur < n) {
        int fill[6] = { -1, -1, -1, -1, -1, -1 };
        insert(mpEnd, n - cur, fill);
    } else {
        char* p = mpBegin + n * 0x18;
        char* end = mpEnd;
        move(end, end, p);
        mpEnd += (int)((p - end) / 0x18) * 0x18;
    }
}

// @ 0x007179e0
AppEditor& AppEditor::operator=(const AppEditor& x)
{
    *(int*)&pad0[0] = *(int*)&x.pad0[0];
    *(int*)&pad0[4] = *(int*)&x.pad0[4];
    v8.v = x.v8.v;
    v1c.v = x.v1c.v;
    for (int i = 0; i < 4; ++i)
        v30[i].v = x.v30[i].v;
    for (int i = 0; i < 2; ++i)
        v80[i].v = x.v80[i].v;
    vA8.v = x.vA8.v;
    vBC.v = x.vBC.v;
    return *this;
}

// @ 0x00717ad0
Elem50* copyFwd50(Elem50* first, Elem50* last, Elem50* dst)
{
    while (first != last) {
        dst->v0 = first->v0;
        dst->v14 = first->v14;
        dst->v28 = first->v28;
        dst->v3c = first->v3c;
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00717b70
Elem50* copyBack50(Elem50* first, Elem50* last, Elem50* dst)
{
    while (last != first) {
        --last;
        --dst;
        dst->v0 = last->v0;
        dst->v14 = last->v14;
        dst->v28 = last->v28;
        dst->v3c = last->v3c;
    }
    return dst;
}

// @ 0x00717bd0
void __cdecl FUN_00717bd0(int* map, int* dstRaw)
{
    IntVec* dst = (IntVec*)dstRaw;
    IntVec out;
    int n = (int)(map[1] - map[0]) >> 2;
    out.begin = 0;
    if (n != 0)
        out.begin = (int*)EA_Allocate((unsigned)(n * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
    out.end = out.begin + n;
    for (int k = 0; k < n; ++k)
        out.begin[k] = 0;
    const int* mapBegin = (const int*)map[0];
    int* src = dst->begin;
    for (unsigned i = 0; i < (unsigned)n; ++i)
        out.begin[i] = src[mapBegin[i]];
    out.cap = out.end;
    FUN_0052c730(dst, 0, &out);
    if (out.begin != 0 && ((int*)out.begin)[-1] != 0)
        EA_Free(out.begin);
}

// @ 0x00717cb0
void AppEditor::insertRange(int count, char* first, int index)
{
    Vec14x4* e = (Vec14x4*)((char*)this + index * 0x14);
    e->v.v.insert(e->v.v.mpEnd, first, first + count * 8, index);
}

// @ 0x00717ce0
void __fastcall FUN_00717ce0(SelEditor* self)
{
    int recs = (int)(self->recEnd - self->recBegin);
    for (int i = 0; i < recs; ++i) {
        SelRecD0* r = self->recBegin + i;
        int count = r->count;
        int* order = (int*)gfxCountArray(count);
        for (int k = 0; k < count; ++k)
            order[k] = k;
        IntVec ov = { order, order + count, order + count };
        if (r->view2Begin != r->view2End)
            FUN_00715e50(order, order + count, FUN_00921240((int*)&r->view2Begin));
        if (r->view1Begin != r->view1End)
            FUN_00715e50(order, order + count, FUN_00921240((int*)&r->view1Begin));
        if (r->idxBegin != r->idxEnd)
            FUN_00715e50(order, order + count, FUN_00921240((int*)&r->idxBegin));
        int* gids = 0;
        if (count != 0) {
            gids = (int*)EA_Allocate((unsigned)(count * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
            for (int k = 0; k < count; ++k)
                gids[k] = -1;
        }
        IntVec groups = { 0, 0, 0 };
        int cur = *ov.begin;
        PushU32(&groups, cur);
        gids[cur] = 0;
        int remaining = count - 1;
        if (remaining > 0) {
            int* it = ov.begin;
            do {
                ++it;
                int idx = *it;
                if (r->idxBegin[cur] != r->idxBegin[idx] ||
                    (r->view1Begin != r->view1End && r->view1Begin[cur] != r->view1Begin[idx]) ||
                    (r->view2Begin != r->view2End && r->view2Begin[cur] != r->view2Begin[idx])) {
                    PushU32(&groups, idx);
                    idx = *it;
                    cur = idx;
                }
                --remaining;
                gids[idx] = (int)(groups.end - groups.begin) - 1;
            } while (remaining != 0);
        }
        int nremap = (int)(r->remapEnd - r->remapBegin);
        for (int k = 0; k < nremap; ++k)
            r->remapBegin[k] = gids[r->remapBegin[k]];
        if (r->idxBegin != r->idxEnd)
            FUN_00717bd0((int*)&groups, (int*)&r->idxBegin);
        if (r->view1Begin != r->view1End)
            FUN_00717bd0((int*)&groups, (int*)&r->view1Begin);
        if (r->view2Begin != r->view2End)
            FUN_00717bd0((int*)&groups, (int*)&r->view2Begin);
        r->count = (int)(groups.end - groups.begin);
        if (gids != 0 && ((int*)gids)[-1] != 0)
            EA_Free(gids);
        if (groups.begin != 0 && ((int*)groups.begin)[-1] != 0)
            EA_Free(groups.begin);
        if (order != 0 && ((int*)order)[-1] != 0)
            EA_Free(order);
    }
}

// @ 0x00718050
void __fastcall FUN_00718050(SelEditor* self)
{
    IntVecF accum = { 0, 0, 0 };
    Span5* spans = 0;
    Span5* spansEnd = 0;
    Span5* spansCap = 0;
    int recs = (int)(self->recEnd - self->recBegin);
    for (int i = 0; i < recs; ++i) {
        SelRecD0* r = self->recBegin + i;
        accum.begin = 0;
        accum.end = 0;
        accum.cap = 0;
        for (int tag = 0; tag < 10; ++tag) {
            for (int j = 0; j < (int)((self->keyEnd - self->keyBegin) >> 3); ++j) {
                int start = (int)(accum.end - accum.begin);
                int nEnt = (int)((self->entEnd - self->entBegin) / 0x14);
                for (int e = 0; e < nEnt; ++e) {
                    AttrEnt* en = self->entBegin + e;
                    if (en->rec != i || en->tag != tag || en->inner != j)
                        continue;
                    FUN_0042b9e0(accum.end, r->remapBegin + en->begin * 4,
                                 r->remapBegin + en->end * 4, recs);
                    int end = (int)(accum.end - accum.begin);
                    if (tag != 4 && start < end) {
                        Span5 s = { tag, i, start, end, j };
                        if (spansEnd < spansCap) {
                            *spansEnd = s;
                            ++spansEnd;
                        } else {
                            FUN_00428900(spansEnd, &s);
                        }
                    }
                }
                int end = (int)(accum.end - accum.begin);
                if (tag == 4 && start < end) {
                    Span5 s = { 4, i, start, end, j };
                    if (spansEnd < spansCap) {
                        *spansEnd = s;
                        ++spansEnd;
                    } else {
                        FUN_00428900(spansEnd, &s);
                    }
                }
            }
        }
        FloatVec_Release(&accum);
        if (accum.begin != 0 && ((int*)accum.begin)[-1] != 0)
            EA_Free(accum.begin);
    }
    Span5* first = spans;
    IntVec spansVec = { (int*)spans, (int*)spansEnd, (int*)spansCap };
    FUN_00715120((void*)&self->entBegin, 0, &spansVec);
    if (first != 0 && ((int*)first)[-1] != 0)
        EA_Free(first);
}

// @ 0x00718370
void* __fastcall FUN_00718370(int* self, int unused, int* src)
{
    int n0 = src[1] - src[0];
    FUN_004aa350((void*)self, 0, (unsigned)(n0 >> 2), (void**)(src + 3));
    int* end0 = (int*)memcpy((void*)self[0], (const void*)src[0], (unsigned)n0);
    self[1] = (int)end0 + (n0 >> 2) * 4;
    int n1 = src[6] - src[5];
    FUN_004aa350((void*)(self + 5), 0, (unsigned)(n1 >> 2), (void**)(src + 8));
    int* end1 = (int*)memcpy((void*)self[5], (const void*)src[5], (unsigned)n1);
    self[6] = (int)end1 + (n1 >> 2) * 4;
    return self;
}

// @ 0x00718520
void assignFwd50(Elem50* first, Elem50* last, Elem50* src)
{
    while (first != last) {
        first->v0 = src->v0;
        first->v14 = src->v14;
        first->v28 = src->v28;
        first->v3c = src->v3c;
        ++first;
        ++src;
    }
}

// @ 0x00718600
Elem28* copyFwd28(Elem28* first, Elem28* last, Elem28* dst)
{
    while (first != last) {
        dst->v0 = first->v0;
        dst->v14 = first->v14;
        ++first;
        ++dst;
    }
    return dst;
}

// @ 0x00718640
Elem28_s0071_8640* copyBack28(Elem28_s0071_8640* first, Elem28_s0071_8640* last, Elem28_s0071_8640* dst)
{
    while (last != first) {
        --last;
        --dst;
        dst->v0 = last->v0;
        dst->v14 = last->v14;
    }
    return dst;
}

// @ 0x00718680
void MeshBuilder8::addIndices0(int count, const int* values, int delta)
{
    v188[0].v.insert(v188[0].v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v188[0].v.mpEnd - count;
        while (p != (int*)v188[0].v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x007186e0
void MeshBuilder8::addIndices1(int count, const int* values, int delta)
{
    v188[1].v.insert(v188[1].v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v188[1].v.mpEnd - count;
        while (p != (int*)v188[1].v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x00718740
void MeshBuilder8::addIndicesSlot(int count, const int* values, int index, int delta)
{
    VecN_s0071_8640& v = v188[2 + index].v;
    v.insert(v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v.mpEnd - count;
        while (p != (int*)v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x007187b0
void MeshBuilder8::addIndicesSlot6(int count, const int* values, int index, int delta)
{
    VecN_s0071_8640& v = v188[6 + index].v;
    v.insert(v.mpEnd, values, values + count, count);
    if (delta != 0) {
        int* p = (int*)v.mpEnd - count;
        while (p != (int*)v.mpEnd) {
            *p += delta;
            ++p;
        }
    }
}

// @ 0x00718820
void MeshBuilderUV::CompactAttributeVertices()
{
    u32 c4[4];
    u32 c2[2];
    VertexVec verts = { 0, 0, 0 };
    UIntVec starts;

    for (Section* sec = mpSectionsBegin; sec != mpSectionsEnd; ++sec) {
        u32 base = (u32)(verts.mpEnd - verts.mpBegin);
        starts.push_back(base);
        u32 m = sec->flags & gUVMask;
        if (m) {
            verts.resize(base + sec->count);
            Vertex6* dst = verts.mpBegin + ((verts.mpEnd - verts.mpBegin) - sec->count);
            for (int i = 0; i < 4; ++i) {
                IntVec_s0071_8640& v = sec->tex[i].v;
                if (v.mpBegin != v.mpEnd) {
                    for (int j = 0; j < sec->count; ++j) dst[j].a[i] = v.mpBegin[j];
                    v.clear();
                }
            }
            for (int i = 0; i < 2; ++i) {
                IntVec_s0071_8640& v = sec->col[i].v;
                if (v.mpBegin != v.mpEnd) {
                    for (int j = 0; j < sec->count; ++j) dst[j].b[i] = v.mpBegin[j];
                    v.clear();
                }
            }
        }
    }

    if (verts.mpBegin != verts.mpEnd) {
        u32 nv = (u32)(verts.mpEnd - verts.mpBegin);
        IntVec_s0071_8640 order(nv);
        for (int i = 0; i < order.size(); ++i) order.mpBegin[i] = i;
        SortVertexOrder(order.mpBegin, order.mpEnd, (VertexVec*)&verts);

        u32 nv2 = (u32)(verts.mpEnd - verts.mpBegin);
        UIntVec remap(nv2);
        UIntVec unique;
        u32 first = order.mpBegin[0];
        unique.DoInsertValue(unique.mpEnd, first);
        remap.mpBegin[first] = 0;

        c4[0] = c4[1] = c4[2] = c4[3] = 0;
        c2[0] = c2[1] = 0;
        const Vertex6* cur = verts.mpBegin + first;
        int n = remap.size();
        int id = 0;
        for (int i = 1; i < n; ++i) {
            u32 oi = order.mpBegin[i];
            const Vertex6* v = verts.mpBegin + oi;
            if (!SameVertex(cur, v)) {
                cur = v;
                unique.push_back(oi);
                id = -1;
                for (int k = 0; k < 4; ++k) Bump(c4[k], id);
                for (int k = 0; k < 2; ++k) Bump(c2[k], id);
            }
            remap.mpBegin[oi] = id;
        }
        order.clear();

        u32* st = starts.mpBegin;
        for (Section* sec = mpSectionsBegin; sec != mpSectionsEnd; ++sec, ++st) {
            if (sec->flags & gUVMask) {
                int zero = 0;
                sec->indices.resize(sec->count, zero);
                for (int j = 0; j < sec->count; ++j)
                    sec->indices.mpBegin[j] = remap.mpBegin[*st + j];
            }
        }
        starts.clear();
        remap.clear();

        for (int i = 0; i < 4; ++i) {
            Vec2Vec& v = tex[i].v;
            if (v.mpBegin != v.mpEnd) {
                Vec2Vec tmp;
                tmp.reserve(unique.size());
                for (u32* it = unique.mpBegin; it != unique.mpEnd; ++it) {
                    int idx = verts.mpBegin[*it].a[i];
                    if (idx == -1) tmp.push_back(gDefaultTexCoord);
                    else tmp.push_back(v.mpBegin[idx]);
                }
                v.assign(tmp);
            }
        }
        Byte4 defColor;
        for (int i = 0; i < 2; ++i) {
            Byte4Vec& v = col[i].v;
            if (v.mpBegin != v.mpEnd) {
                Byte4Vec tmp;
                tmp.reserve(unique.size());
                for (u32* it = unique.mpBegin; it != unique.mpEnd; ++it) {
                    int idx = verts.mpBegin[*it].b[i];
                    if (idx == -1) tmp.push_back(defColor);
                    else tmp.push_back(v.mpBegin[idx]);
                }
                v.assign(tmp);
            }
        }
    }
    if (verts.mpBegin && ((u32*)verts.mpBegin)[-1]) EAFree(verts.mpBegin);
}

// @ 0x00719170
FixedIdVector6* FixedIdVector6::Assign(const FixedIdVector6& x)
{
    if (this != &x) {
        u32* first = mpBegin;
        u32* last  = mpEnd;
        u32* dst   = first;
        for (const u32* src = last; src != last; ++src)   // empty tail copy
            *dst++ = *src;
        mpEnd = mpEnd - (last - first);
        ((FixedIdDoAssignFn)(void*)FUN_0042cd50)(this, x.mpBegin, x.mpEnd, &x);
    }
    return this;
}

// @ 0x00719200
void fill28(Elem28_s0071_8640* first, Elem28_s0071_8640* last, const Elem28_s0071_8640* value)
{
    while (first != last) {
        first->v0 = value->v0;
        first->v14 = value->v14;
        ++first;
    }
}

// @ 0x00719240
void MeshBuilder8::finish()
{
    if (n160 >= 0) {
        char* base = (char*)pD0 + n160 * 0xd0;
        *(int*)((char*)pE8 - 8) = (*(int*)(base + 0xc0) - *(int*)(base + 0xbc)) >> 2;
    }
    sub18820();
    sub17ce0();
    sub173e0();
    sub18050();
    b150 = 0;
}

// @ 0x00719330
u8* MeshVecD0::relocateRange(u8* first, u8* last)
{
    u8* r      = (u8*)FUN_00717a90(last, mpEnd, first);
    u8* oldEnd = mpEnd;
    for (; r < oldEnd; r += ELEM_D0)
        ((DestroyFn)(void*)FUN_007146c0)(r);
    mpEnd -= ((ptrdiff_t)(last - first) / ELEM_D0) * ELEM_D0;
    return first;
}

// @ 0x00719390
u8* MeshVec50::copyEraseRange(u8* first, u8* last)
{
    u8* r = (u8*)FUN_00717ad0(last, mpEnd, first);
    ((TailFn)(void*)FUN_00714b40)(this, r, mpEnd);
    mpEnd -= ((ptrdiff_t)(last - first) / ELEM_50) * ELEM_50;
    return first;
}

// @ 0x007193e0
void MeshVecD0::insert(u8* position, u32 n, const void* value)
{
    if ((u32)((ptrdiff_t)(mpCapacity - mpEnd) / ELEM_D0) < n) {
        // not enough spare capacity: reallocate, copy the head, fill, move the tail
        u32 size = (u32)((ptrdiff_t)(mpEnd - mpBegin) / ELEM_D0);
        u32 grown = size * 2;
        if (size == 0) grown = 1;
        u32 cap = size + n;
        if (cap < grown) cap = grown;
        u8* buf = cap ? (u8*)EAAlloc(cap * ELEM_D0, "Graphics", 0, 0, ALLOC_H, 0xd1) : 0;
        u8* oldBegin = mpBegin;
        u8* mid = (u8*)FUN_007165c0(oldBegin, position, buf);
        FUN_00714960(oldBegin, position, buf);
        FUN_00716440(mid, n, (void*)value, oldBegin);
        u8* tailDst = mid + n * ELEM_D0;
        u8* oldEnd  = mpEnd;
        u8* newEnd  = (u8*)FUN_007165c0(position, oldEnd, tailDst);
        FUN_00714960(position, oldEnd, tailDst);
        if (mpBegin && ((u32*)mpBegin)[-1] != 0)
            EAFree(mpBegin);
        mpEnd      = newEnd;
        mpBegin    = buf;
        mpCapacity = buf + cap * ELEM_D0;
    }
    else if (n != 0) {
        ElemD0 temp;
        ((CopyCtorFn)(void*)FUN_00716110)(&temp, value);
        u32 tail = (u32)((ptrdiff_t)(mpEnd - position) / ELEM_D0);
        if (n < tail) {
            // the tail is longer than n: shift the last n elements on by n, then fill
            u8* split = mpEnd - n * ELEM_D0;
            FUN_007163c0(&temp.mpAux, split, mpEnd, mpEnd, temp.mpAux);
            mpEnd = mpEnd + n * ELEM_D0;
            FUN_00717b30(position, split, mpEnd);
            FUN_007191d0(position, position + n * ELEM_D0, &temp);
        }
        else {
            // construct the overflow past the end, then shift the whole tail
            FUN_00716440(mpEnd, n - tail, &temp, temp.mpAux);
            u8* oldEnd = mpEnd;
            mpEnd = mpEnd + (n - tail) * ELEM_D0;
            FUN_007163c0(&temp.mpAux, position, oldEnd, mpEnd, temp.mpAux);
            mpEnd = mpEnd + tail * ELEM_D0;
            FUN_007191d0(position, oldEnd, &temp);
        }
        ((DestroyFn)(void*)FUN_007146c0)(&temp);
    }
}

// @ 0x00719620
void Vec50::insert(T50* position, uint32_t n, const T50& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n != 0) {
            const T50 temp = value;
            T50* const oldEnd = mpEnd;
            const uint32_t nExtra = (uint32_t)(oldEnd - position);
            if (n < nExtra) {
                T50* r;
                MoveUninit50(r, oldEnd - n, oldEnd, oldEnd);
                mpEnd += n;
                CopyBackward50(position, oldEnd - n, oldEnd);
                FillRange50(position, position + n, &temp);
            } else {
                FillN50(oldEnd, n - nExtra, &temp, position);
                mpEnd += n - nExtra;
                T50* r;
                MoveUninit50(r, position, oldEnd, mpEnd);
                mpEnd += nExtra;
                FillRange50(position, oldEnd, &temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (nPrevSize * 2) : 1;
        const uint32_t nNewSize = (nGrowSize > (nPrevSize + n)) ? nGrowSize : (nPrevSize + n);
        T50* const pNewData = nNewSize ? (T50*)SpAlloc(nNewSize * sizeof(T50),
            "Graphics", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        T50* pNewEnd = UninitMove50(mpBegin, position, pNewData);
        Destroy50(mpBegin, position, pNewData);
        FillN50(pNewEnd, n, &value, pNewEnd);
        pNewEnd += n;
        pNewEnd = UninitMove50(position, mpEnd, pNewEnd);
        Destroy50(position, mpEnd, pNewEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            SpFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00719890
void CopyBackward8C(Obj8C* first, Obj8C* last, Obj8C* dest)
{
    while (last != first)
        Obj8C_Assign(--dest, --last);
}

// @ 0x00719a00
void Vec28::insert(T28* position, uint32_t n, const T28& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n != 0) {
            const T28 temp = value;
            T28* const oldEnd = mpEnd;
            const uint32_t nExtra = (uint32_t)(oldEnd - position);
            if (n < nExtra) {
                T28* r;
                MoveUninit28(r, oldEnd - n, oldEnd, oldEnd);
                mpEnd += n;
                CopyBackward28(position, oldEnd - n, oldEnd);
                FillRange28(position, position + n, &temp);
            } else {
                FillN28(oldEnd, n - nExtra, &temp, position);
                mpEnd += n - nExtra;
                T28* r;
                MoveUninit28(r, position, oldEnd, mpEnd);
                mpEnd += nExtra;
                FillRange28(position, oldEnd, &temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (nPrevSize * 2) : 1;
        const uint32_t nNewSize = (nGrowSize > (nPrevSize + n)) ? nGrowSize : (nPrevSize + n);
        T28* const pNewData = nNewSize ? (T28*)SpAlloc(nNewSize * sizeof(T28),
            "Graphics", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        T28* pNewEnd = UninitMove28(mpBegin, position, pNewData);
        Destroy28(mpBegin, position, pNewData);
        FillN28(pNewEnd, n, &value, pNewEnd);
        T28* const pInsertEnd = pNewEnd + n;
        T28* const oldEnd = mpEnd;
        T28* pNewEnd2 = UninitMove28(position, oldEnd, pInsertEnd);
        Destroy28(position, oldEnd, pInsertEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            SpFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd2;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00719c60
void Vec140::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), T140());
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00719d30
void Vec50::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), T50());
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00719e10
void cMeshBuilder_s0071_9e10::EndPrimitive()
{
    unsigned mask = (mPrim[0].mpBegin != mPrim[0].mpEnd);
    SetBit(mask, 2, mPrim[1].mpBegin != mPrim[1].mpEnd);
    SetBit(mask, 4, mPrim[2].mpBegin != mPrim[2].mpEnd);
    SetBit(mask, 8, mPrim[3].mpBegin != mPrim[3].mpEnd);
    SetBit(mask, 0x10, mPrim[4].mpBegin != mPrim[4].mpEnd);
    SetBit(mask, 0x20, mPrim[5].mpBegin != mPrim[5].mpEnd);
    SetBit(mask, 0x40, mPrim[6].mpBegin != mPrim[6].mpEnd);
    SetBit(mask, 0x80, mPrim[7].mpBegin != mPrim[7].mpEnd);

    // find (or create) the section for this attribute mask, searching from the mesh's first section
    uint32_t secIdx = (uint32_t)m164;
    if (secIdx < (uint32_t)(mSections.v.mpEnd - mSections.v.mpBegin)) {
        T140_s0071_9e10* s = mSections.v.mpBegin + secIdx;
        do {
            if (s->mMask == mask)
                break;
            ++secIdx;
            ++s;
        } while (secIdx < (uint32_t)(mSections.v.mpEnd - mSections.v.mpBegin));
    }
    int zero = 0;
    if (secIdx == (uint32_t)(mSections.v.mpEnd - mSections.v.mpBegin)) {
        mSections.v.resize(secIdx + 1);
        mSections.v.mpBegin[secIdx].mMask = mask;
        mSections.v.mpBegin[secIdx].mCount = zero;
    }
    uint32_t secOffset = secIdx * 0xd0;
    T140_s0071_9e10* sec = mSections.v.mpBegin + secIdx;

    // append the indices of every vertex of the primitive to the section's attribute streams
    uint32_t vi = zero;
    if ((uint32_t)(mPrim[0].mpEnd - mPrim[0].mpBegin) != 0) {
        do {
            if (IsSingle(mPrim[0])) {
                uint32_t v = m168 + mPrim[0].mpBegin[0];
                sec->mAttr[0].push_back(v);
            } else if (mask & 1) {
                uint32_t v = mPrim[0].mpBegin[vi] + m168;
                sec->mAttr[0].push_back(v);
            }
            if (IsSingle(mPrim[1])) {
                uint32_t v = m16c + mPrim[1].mpBegin[0];
                sec->mAttr[1].push_back(v);
            } else if ((mask >> 1) & 1) {
                uint32_t v = mPrim[1].mpBegin[vi] + m16c;
                sec->mAttr[1].push_back(v);
            }
            int* texBase = &m170;
            for (int k = 0; k < 4; ++k) {
                const UVec& src = mPrim[2 + k];
                uint32_t v;
                if (IsSingle(src))
                    v = texBase[k] + src.mpBegin[0];
                else if (TestBit11(mask, k + 2))
                    v = src.mpBegin[vi] + texBase[k];
                else
                    continue;
                sec->mAttr[2 + k].push_back(v);
            }
            int* colBase = &m180;
            for (int k = 0; k < 2; ++k) {
                const UVec& src = mPrim[6 + k];
                uint32_t v;
                if (IsSingle(src))
                    v = colBase[k] + src.mpBegin[0];
                else if (TestBit11(mask, k + 6))
                    v = src.mpBegin[vi] + colBase[k];
                else
                    continue;
                sec->mAttr[6 + k].push_back(v);
            }
            ++vi;
        } while (vi < (uint32_t)(mPrim[0].mpEnd - mPrim[0].mpBegin));
    }

    // vertices of the primitive are numbered from the section's previous vertex count
    uint32_t first = (uint32_t)sec->mCount;
    sec->mCount = (int)(sec->mAttr[0].mpEnd - sec->mAttr[0].mpBegin);

    if (mPrimType == 9) {
        // polygon: triangulate as a fan
        uint32_t cur = (uint32_t)m160;
        if (secIdx != cur || m158 != m15c || mV2.v.mpEnd[-1].mType != 4) {
            if ((int)cur >= 0)
                mV2.v.mpEnd[-1].mEnd = (int)(mSections.v.mpBegin[cur].mIndices.mpEnd - mSections.v.mpBegin[cur].mIndices.mpBegin);
            Batch nb;
            nb.mType = 4;
            nb.mSection = secIdx;
            nb.mStart = (int)(mSections.v.mpBegin[secIdx].mIndices.mpEnd - mSections.v.mpBegin[secIdx].mIndices.mpBegin);
            nb.mEnd = -1;
            nb.mExtra = m158;
            mV2.v.push_back(nb);
        }
        uint32_t prev = first + 1;
        uint32_t next = first + 2;
        uint32_t k = 2;
        uint32_t n = (uint32_t)(mPrim[0].mpEnd - mPrim[0].mpBegin);
        if (n > 2) {
            do {
                uint32_t a = first;
                uint32_t b = prev;
                uint32_t c = next;
                sec->mIndices.push_back(a);
                sec->mIndices.push_back(b);
                sec->mIndices.push_back(c);
                ++k;
                ++next;
                prev = c;
            } while (k < (uint32_t)(mPrim[0].mpEnd - mPrim[0].mpBegin));
        }
    } else {
        if (mV2.v.mpBegin == mV2.v.mpEnd || mV2.v.mpEnd[-1].mType != 4 || mPrimType != 4
            || secIdx != (uint32_t)m160 || m158 != m15c) {
            if (m160 >= 0)
                mV2.v.mpEnd[-1].mEnd = (int)(mSections.v.mpBegin[m160].mIndices.mpEnd - mSections.v.mpBegin[m160].mIndices.mpBegin);
            Batch nb;
            nb.mType = mPrimType;
            nb.mSection = secIdx;
            nb.mStart = (int)(mSections.v.mpBegin[secIdx].mIndices.mpEnd - mSections.v.mpBegin[secIdx].mIndices.mpBegin);
            nb.mEnd = -1;
            nb.mExtra = m158;
            mV2.v.push_back(nb);
        }
        int n = (int)(mPrim[0].mpEnd - mPrim[0].mpBegin);
        uint32_t idx = first;
        if (n > 0) {
            do {
                uint32_t v = idx;
                sec->mIndices.push_back(v);
                ++idx;
                --n;
            } while (n != 0);
        }
    }

    mPrim[0].clear();
    mPrim[1].clear();
    for (int k = 0; k < 4; ++k)
        mPrim[2 + k].clear();
    for (int k = 0; k < 2; ++k)
        mPrim[6 + k].clear();
    m15c = m158;
    m160 = (int)secIdx;
    mPrimType = 0;
}

// @ 0x0071a650
void cMeshBuilder_s0071_9e10::ClearMeshInfo()
{
    // The four vertex-attribute streams whose erase stays out of line (0x50f740).
    ((Vec3Erase*)&mPositions.v)->erase(mPositions.v.mpBegin, mPositions.v.mpEnd);
    ((Vec3Erase*)&mNormals.v)->erase(mNormals.v.mpBegin, mNormals.v.mpEnd);
    ((Vec3Erase*)&mV0.v)->erase(mV0.v.mpBegin, mV0.v.mpEnd);
    ((Vec3Erase*)&mV1.v)->erase(mV1.v.mpBegin, mV1.v.mpEnd);

    for (int i = 0; i < 4; ++i)
        DropTailShift<cSPVector2_s0071_9e10, 3>(mTexCoords[i].v.mpBegin, mTexCoords[i].v.mpEnd);
    for (int i = 0; i < 2; ++i)
        DropTailShift<tMDUByte4, 2>(mColors[i].v.mpBegin, mColors[i].v.mpEnd);

    mV4.erase(mV4.mpBegin, mV4.mpEnd);                       // 0x009c69f0

    // The 0x28-byte records at +0x120 own two sub-vectors: free them, then drop the elements.
    mV5_DestroyRange(mV5.v.mpBegin, mV5.v.mpEnd);            // 0x00714f20
    DropTailDiv<T28_s0071_9e10, 40>(mV5.v.mpBegin, mV5.v.mpEnd);

    // The 0x50-byte records at +0x134 own four sub-buffers each.
    mV6_DestroyRange(mV6.v.mpBegin, mV6.v.mpEnd);            // 0x00714b40
    DropTailDiv<int, 80>(mV6.v.mpBegin, mV6.v.mpEnd);

    // Sections own their attribute index streams.
    for (T140_s0071_9e10* s = mSections.v.mpBegin; s < mSections.v.mpEnd; ++s)
        s->Destroy();                                        // 0x007146c0
    DropTailDiv<T140_s0071_9e10, 208>(mSections.v.mpBegin, mSections.v.mpEnd);

    DropTailDiv<Batch, 20>(mV2.v.mpBegin, mV2.v.mpEnd);
    DropTailShift<uint64_t, 3>(mV3.v.mpBegin, mV3.v.mpEnd);
}

// @ 0x0071a930
void Vec28_s0071_9e10::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        T28_s0071_9e10 v;
        insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), v);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x0071aa20
void cMeshBuilder_s0071_9e10::BeginMesh()
{
    mInMesh = true;
    if (mMeshData == 0)
        ClearMeshInfo();
    if (mMeshData != 0) {
        RefCounted* p = mMeshData;
        mMeshData = 0;
        p->Release();
    }
    mKey = 0x9f84a565;
    m164 = (int)(mSections.v.mpEnd - mSections.v.mpBegin);
    m168 = (int)(mPositions.v.mpEnd - mPositions.v.mpBegin);
    m16c = (int)(mNormals.v.mpEnd - mNormals.v.mpBegin);
    m170 = (int)(mTexCoords[0].v.mpEnd - mTexCoords[0].v.mpBegin);
    m174 = (int)(mTexCoords[1].v.mpEnd - mTexCoords[1].v.mpBegin);
    m178 = (int)(mTexCoords[2].v.mpEnd - mTexCoords[2].v.mpBegin);
    m17c = (int)(mTexCoords[3].v.mpEnd - mTexCoords[3].v.mpBegin);
    m180 = (int)(mColors[0].v.mpEnd - mColors[0].v.mpBegin);
    m184 = (int)(mColors[1].v.mpEnd - mColors[1].v.mpBegin);
    m158 = -1;
    m15c = -1;
    m160 = -1;
}

// @ 0x0071ab60
void cMeshBuilder_s0071_9e10::TransformStreams(uint32_t param)
{
    ((Vec28_s0071_9e10*)&mV5.v)->resize(param);                        // 0x0071a930
    Mat34 mtx;
    mtx.m[0]  = 1.0f;  mtx.m[1]  = 0.0f;  mtx.m[2]  = 0.0f;  mtx.m[3]  = 0.0f;
    mtx.m[4]  = 0.0f;  mtx.m[5]  = 1.0f;  mtx.m[6]  = 0.0f;  mtx.m[7]  = 0.0f;
    mtx.m[8]  = 0.0f;  mtx.m[9]  = 0.0f;  mtx.m[10] = 1.0f;  mtx.m[11] = 0.0f;
    mV4.resize(param, mtx);                                 // 0x00717820
}

// @ 0x0071ac50
void cMeshBuilder_s0071_ac50::CreateMeshData()
{
    mMeshData = new ("Graphics", 0, 0, 0, 0) cMeshData;

    // Vertex attribute streams.
    mMeshData->mEltArrays.push_back(
        cMDElementArray(kSemPosition, 0, kDataFloat3, 0, cEltArrayRef(mPositions)));
    mMeshData->mEltArrays.push_back(
        cMDElementArray(kSemNormal, 0, kDataFloat3, 1, cEltArrayRef(mNormals)));

    int tangentElt = mMeshData->mEltArrays.size();
    if (!mTangents.empty())
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemTangent, 0, kDataFloat3, 1, cEltArrayRef(mTangents)));

    int binormalElt = mMeshData->mEltArrays.size();
    if (!mBinormals.empty())
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemBinormal, 0, kDataFloat3, 1, cEltArrayRef(mBinormals)));

    int texCoordElt = mMeshData->mEltArrays.size();
    for (int i = 0; i < 4; ++i) {
        if (!mTexCoords[i].empty())
            mMeshData->mEltArrays.push_back(
                cMDElementArray(kSemTexCoord, i, kDataFloat2, 2, cEltArrayRef(mTexCoords[i])));
    }

    int colorElt = mMeshData->mEltArrays.size();
    for (int i = 0; i < 2; ++i) {
        if (!mColors[i].empty())
            mMeshData->mEltArrays.push_back(
                cMDElementArray(kSemColor, i, kDataUByte4, 2, cEltArrayRef(mColors[i])));
    }

    // Bone weights: two streams (weights, indices) per bone.
    int boneElt = mMeshData->mEltArrays.size();
    int numBones = mBoneWeightsArray.size();
    for (int i = 0; i < numBones; ++i) {
        cBoneWeights& bw = mBoneWeightsArray[i];
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemBoneWeights, i, kDataFloat1x, 0, cEltArrayRef(bw.mWeights)));
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemBoneIndices, i, kDataInt, 0, cEltArrayRef(bw.mIndices)));
    }

    // Morph targets: position deltas + indices for every target...
    int morphPosElt = mMeshData->mEltArrays.size();
    int numMorphs = mMorphTargetArray.size();
    for (int i = 0; i < numMorphs; ++i) {
        cMorphTarget& mt = mMorphTargetArray[i];
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemMorphPosition, i, kDataFloat3x, 0, cEltArrayRef(mt.mPositionDeltas)));
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemMorphPosition, i, kDataInt, 0, cEltArrayRef(mt.mPositionIndices)));
    }

    // ...then normal deltas + indices for targets that have them.
    int morphNrmElt = mMeshData->mEltArrays.size();
    numMorphs = mMorphTargetArray.size();
    for (int i = 0; i < numMorphs; ++i) {
        cMorphTarget& mt = mMorphTargetArray[i];
        if (!mt.mNormalDeltas.empty()) {
            mMeshData->mEltArrays.push_back(
                cMDElementArray(kSemMorphNormal, i, kDataFloat3x, 0, cEltArrayRef(mt.mNormalDeltas)));
            mMeshData->mEltArrays.push_back(
                cMDElementArray(kSemMorphNormal, i, kDataInt, 0, cEltArrayRef(mt.mNormalIndices)));
        }
    }

    if (!mBonePoses.empty())
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemBonePose, 0, kDataMatrix, 5, cEltArrayRef(mBonePoses)));

    if (!mSubsets.empty()) {
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemSubsetID, 0, kDataInt, 8,
                            cEltArrayRef(mSubsets.size(), &mSubsets.mpBegin->mID, 4, 8)));
        mMeshData->mEltArrays.push_back(
            cMDElementArray(kSemSubsetMaterial, 0, kDataInt, 8,
                            cEltArrayRef(mSubsets.size(), &mSubsets.mpBegin->mMaterialID, 4, 8)));
    }

    // Sections.
    int numSections = mSections.size();
    for (int s = 0; s < numSections; ++s) {
        cBuilderSection& src = mSections[s];
        cMDSection section;
        section.mVertIndices = cIndexArrayRef(src.mVertIndices);
        section.mNumVertices = src.mNumVertices;

        int positionIndex = -1;
        int normalIndex = -1;
        int attribIndex = -1;
        if (!src.mPositionIndices.empty()) {
            positionIndex = section.mEltIndices.size();
            section.mEltIndices.push_back(cIndexArrayRef(src.mPositionIndices));
        }
        if (!src.mNormalIndices.empty()) {
            normalIndex = section.mEltIndices.size();
            section.mEltIndices.push_back(cIndexArrayRef(src.mNormalIndices));
        }
        if (!src.mAttribIndices.empty()) {
            attribIndex = section.mEltIndices.size();
            section.mEltIndices.push_back(cIndexArrayRef(src.mAttribIndices));
        }

        bitset11 format = src.mVertexFormat;
        if (format.test(0) && positionIndex >= 0)
            section.mFormat.push_back(cMDFormatEntry(0, (short)positionIndex));
        if (format.test(1) && normalIndex >= 0) {
            section.mFormat.push_back(cMDFormatEntry(1, (short)normalIndex));
            if (!mTangents.empty())
                section.mFormat.push_back(cMDFormatEntry((short)tangentElt, (short)normalIndex));
            if (!mBinormals.empty())
                section.mFormat.push_back(cMDFormatEntry((short)binormalElt, (short)normalIndex));
        }
        if (attribIndex >= 0) {
            for (int i = 0; i < 4; ++i) {
                if (format.test(i + 2))
                    section.mFormat.push_back(cMDFormatEntry((short)(texCoordElt + i), (short)attribIndex));
            }
            for (int i = 0; i < 2; ++i) {
                if (format.test(i + 6))
                    section.mFormat.push_back(cMDFormatEntry((short)(colorElt + i), (short)attribIndex));
            }
        }
        if (format.test(8)) {
            int n = mBoneWeightsArray.size();
            for (int i = 0; i < n; ++i)
                section.mFormat.push_back(cMDFormatEntry((short)(boneElt + i * 2), -1));
        }
        if (positionIndex >= 0) {
            if (format.test(9)) {
                int n = mMorphTargetArray.size();
                for (int i = 0; i < n; ++i)
                    section.mFormat.push_back(cMDFormatEntry((short)(morphPosElt + i * 2), (short)positionIndex));
            }
            if (format.test(10)) {
                int n = mMorphTargetArray.size();
                for (int i = 0; i < n; ++i)
                    section.mFormat.push_back(cMDFormatEntry((short)(morphNrmElt + i * 2), (short)positionIndex));
            }
        }

        mMeshData->mSections.push_back(section);
    }

    // Primitives.
    int numPrims = mPrimitives.size();
    for (int i = 0; i < numPrims; ++i)
        mMeshData->mPrimitives.push_back(mPrimitives[i]);

    MeshData_ResolveArrays(mMeshData.mp);
    ClearMeshInfo();
}

// @ 0x0071c900
void SimCmd_exec_c900(IVt* self)
{
    ((Fn0)self->mpVtbl[3])(self);                          // +0xc
    ((Fn1)self->mpVtbl[0x13])(self, 0);                    // +0x4c(0)
    ((FnP)self->mpVtbl[6])(self, Vec3_s0071_c900(0.0f, 0.0f, 0.0f));  // +0x18
    ((FnP)self->mpVtbl[7])(self, Vec3_s0071_c900(0.0f, 0.0f, 1.0f));  // +0x1c
    ((FnPi)self->mpVtbl[8])(self, Vec3_s0071_c900(0.0f, 0.0f, 0.0f), 0); // +0x20
    ((Fn1)self->mpVtbl[0x14])(self, 4);                    // +0x50(4)
    ((Fn2)self->mpVtbl[0x19])(self, 7, 0);                 // +0x64(7,0)
    ((Fn2)self->mpVtbl[0x19])(self, 7, 0);
    ((Fn2)self->mpVtbl[0x19])(self, 7, 0);
    ((Fn0)self->mpVtbl[0x1f])(self);                       // +0x7c
    ((Fn0)self->mpVtbl[4])(self);                          // tail +0x10
}

// @ 0x0071c9e0
void __cdecl CreateDiscMesh(IVt* self, float radius, int segments)
{
    ((Fn0)self->mpVtbl[3])(self);       // +0xc  begin mesh
    ((Fn1)self->mpVtbl[0x13])(self, 0); // +0x4c  texture stage 0

    int half = segments / 2;
    if (half >= 0) {
        float fSeg = (float)segments;
        for (int ring = 0; ring <= half; ++ring) {
            float v = (float)(ring * 2) / fSeg;
            float polar = ((float)ring / fSeg) * g_angle2Pi;
            float cosP = (float)cos(polar);
            float sinP = (float)sin(polar);
            for (int i = 0; i <= segments; ++i) {
                float u = (float)i / fSeg;
                float az = u * g_angle2Pi;
                float cosA = (float)cos(az);
                float sinA = (float)sin(az);

                Vector3 p;
                p.x = cosA * sinP * radius;
                p.y = sinA * sinP * radius;
                p.z = cosP * radius;
                ((FnPv)self->mpVtbl[6])(self, &p);      // +0x18 position

                Vector3 n;
                n.x = cosA * sinP;
                n.y = sinA * sinP;
                n.z = cosP;
                ((FnPv)self->mpVtbl[7])(self, &n);      // +0x1c normal

                Vector3 uv;
                uv.x = u;
                uv.y = v;
                uv.z = 0.0f;
                ((FnPvi)self->mpVtbl[8])(self, &uv, 0);  // +0x20 texcoord
            }
        }
    }

    for (int row = 0; row < half; ++row) {
        int rowStart = row * (segments + 1);
        int nextRow = rowStart + segments + 1;
        for (int i = 0; i < segments; ++i) {
            ((Fn1)self->mpVtbl[0x14])(self, 9);         // +0x50 primitive type
            ((Fn2)self->mpVtbl[0x19])(self, 7, rowStart + i);
            ((Fn2)self->mpVtbl[0x19])(self, 7, nextRow + i);
            if (row < half - 1)
                ((Fn2)self->mpVtbl[0x19])(self, 7, nextRow + i + 1);
            if (row > 0)
                ((Fn2)self->mpVtbl[0x19])(self, 7, rowStart + i + 1);
            ((Fn0)self->mpVtbl[0x1f])(self);           // +0x7c end primitive
        }
    }

    ((Fn0)self->mpVtbl[4])(self);       // +0x10 end mesh
}

// @ 0x0071cc20
void __cdecl CreateQuadMesh(IVt* self, const Vector3& vmin, const Vector3& vmax)
{
    ((Fn0)self->mpVtbl[3])(self);

    Vector3 p;
    p = vmin;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmin.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p = vmax;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmin.x; p.y = vmax.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);

    // Normal points along the axis of the thinner dimension.
    float dz = vmax.z - vmin.z;
    float dy = vmax.y - vmin.y;
    if (dz < 0.0f) dz = -dz;
    if (dy < 0.0f) dy = -dy;
    const Vector3* n = (dz <= dy) ? &g_axisZ : &g_axisY;
    ((FnPv)self->mpVtbl[7])(self, n);

    Vector3 uv;
    uv.z = 0.0f;
    uv.x = 0.0f; uv.y = 1.0f; ((FnPvi)self->mpVtbl[8])(self, &uv, 0);
    uv.x = 1.0f; uv.y = 1.0f; ((FnPvi)self->mpVtbl[8])(self, &uv, 0);
    uv.x = 1.0f; uv.y = 0.0f; ((FnPvi)self->mpVtbl[8])(self, &uv, 0);
    uv.x = 0.0f; uv.y = 0.0f; ((FnPvi)self->mpVtbl[8])(self, &uv, 0);

    ((Fn1)self->mpVtbl[0x13])(self, 0);         // +0x4c
    ((Fn1)self->mpVtbl[0x14])(self, 9);         // +0x50
    ((Fn1)self->mpVtbl[0x16])(self, 0);         // +0x58
    ((Fn2)self->mpVtbl[0x19])(self, 5, 0);      // +0x64
    ((Fn2)self->mpVtbl[0x19])(self, 5, 1);
    ((Fn2)self->mpVtbl[0x19])(self, 5, 2);
    ((Fn2)self->mpVtbl[0x19])(self, 5, 3);
    ((Fn0)self->mpVtbl[0x1f])(self);            // +0x7c
    ((Fn0)self->mpVtbl[4])(self);               // +0x10
}

// @ 0x0071cde0
void __cdecl CreateBoxMesh(IVt* self, const Vector3& vmin, const Vector3& vmax)
{
    ((Fn0)self->mpVtbl[3])(self);

    Vector3 p;
    p.x = vmin.x; p.y = vmin.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmin.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmin.x; p.y = vmax.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmax.y; p.z = vmin.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmin.x; p.y = vmin.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmin.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmin.x; p.y = vmax.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);
    p.x = vmax.x; p.y = vmax.y; p.z = vmax.z;
    ((FnPv)self->mpVtbl[6])(self, &p);

    Vector3 n;
    n.x = g_axisX.x; n.y = g_axisX.y; n.z = g_axisX.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = -g_axisX.x; n.y = -g_axisX.y; n.z = -g_axisX.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = g_axisY.x; n.y = g_axisY.y; n.z = g_axisY.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = -g_axisY.x; n.y = -g_axisY.y; n.z = -g_axisY.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = g_axisZ.x; n.y = g_axisZ.y; n.z = g_axisZ.z;
    ((FnPv)self->mpVtbl[7])(self, &n);
    n.x = -g_axisZ.x; n.y = -g_axisZ.y; n.z = -g_axisZ.z;
    ((FnPv)self->mpVtbl[7])(self, &n);

    ((Fn1)self->mpVtbl[0x13])(self, 0);         // +0x4c

    for (int k = 0; k < 6; ++k) {
        ((Fn1)self->mpVtbl[0x14])(self, 9);     // +0x50
        ((Fn1)self->mpVtbl[0x16])(self, k);     // +0x58
        ((FnVii)self->mpVtbl[0x1a])(self, 4, s_boxQuads[k], 0); // +0x68
        ((Fn0)self->mpVtbl[0x1f])(self);        // +0x7c
    }

    ((Fn0)self->mpVtbl[4])(self);               // +0x10
}

// @ 0x0071d2f0
void __cdecl CreateMesh_d2f0(IVt* self, float size)
{
    ((Fn0)self->mpVtbl[3])(self);

    // Twelve vertices of a three-part gizmo (one part per 4 vertices).
    static const float s_verts[36] = {
        0.0f, 0.0f, 0.1f,   1.0f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.0f,   0.0f, -0.1f, 0.0f,
        0.0f, 0.0f, 0.1f,   0.0f, 1.0f, 0.0f,
        0.1f, 0.0f, 0.0f,   -0.1f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.1f, 0.0f, 0.0f,   -0.1f, 0.0f, 0.0f,
    };

    for (int k = 0; k < 12; ++k) {
        Vector3 p;
        p.x = s_verts[k * 3 + 0] * size;
        p.y = s_verts[k * 3 + 1] * size;
        p.z = s_verts[k * 3 + 2] * size;
        ((FnPv)self->mpVtbl[6])(self, &p);      // +0x18
    }

    static const int s_idx[9] = { 1, 0, 3, 1, 2, 0, 1, 3, 2 };

    for (int part = 0; part < 3; ++part) {
        ((Fn1)self->mpVtbl[0x13])(self, part);  // +0x4c
        int base = part * 4;
        for (int k = 0; k < 3; ++k) {
            ((Fn1)self->mpVtbl[0x14])(self, 9); // +0x50
            ((Fn1)self->mpVtbl[0x15])(self, s_idx[k * 3 + 0] + base); // +0x54
            ((Fn1)self->mpVtbl[0x15])(self, s_idx[k * 3 + 1] + base);
            ((Fn1)self->mpVtbl[0x15])(self, s_idx[k * 3 + 2] + base);
            ((Fn0)self->mpVtbl[0x1f])(self);    // +0x7c
        }
    }

    ((Fn0)self->mpVtbl[4])(self);               // +0x10
}

// @ 0x0071d550
void __cdecl EmitSphere(Rend* w, float r, float zscale, int count, int seg, int subdiv, char flag)
{
    w->v3();
    if (flag == 0)
        w->v19(0);
    if (seg != 0)
        w->v32(seg + 1);

    Vector3 p;
    Vector3 n;
    Vector3 uv;
    float angle = 0.0f;
    float invCount = 1.0f / (float)count;
    int vert = 0;
    int rowIdx = 0;
    if (count > 0) {
        float invLast = (float)(count - 1);
        do {
            float cosA = (float)cos(angle);
            float sinA = (float)sin(angle);
            float rowN = (float)rowIdx * invCount;
            int col = 0;
            do {
                float colN = (float)col / invLast;
                p.x = cosA * r;
                p.y = sinA * r;
                p.z = ((colN * 2.0f - 1.0f) * zscale) * r;
                w->v6(&p);
                n.x = cosA;
                n.y = sinA;
                n.z = 0.0f;
                w->v7(&n);
                uv.x = rowN;
                uv.y = colN;
                w->v8(&uv, 0);

                float base = (float)(seg - 1) * colN;
                float denom = (float)subdiv * g_subdivK;
                for (int k = 0; k < seg; ++k) {
                    double f = 1.0 - fabs((double)base - (double)k) / (double)denom;
                    if (f > 0.0)
                        w->v35(k + 1, vert, (float)f);
                }
                ++vert;
                ++col;
            } while (col < count);
            angle = g_angleStep * invCount + angle;
            ++rowIdx;
        } while (rowIdx < count);
    }

    Vector3 neg;
    w->v7(&g_axis);
    neg.x = -g_axis.x;
    neg.y = -g_axis.y;
    neg.z = -g_axis.z;
    w->v7(&neg);
    if (flag)
        w->v19(0);
    w->v20(9);
    w->v22(vert);

    if (count > 0) {
        int e = count - 1;
        int m = count;
        do {
            w->v25(5, e);
            e += count;
        } while (--m);
    }
    w->v31();

    if (flag)
        w->v19(1);
    w->v20(9);
    w->v22(vert + 1);
    if (count > 0) {
        int e = (count - 1) * count;
        int m = count;
        do {
            w->v25(5, e);
            e -= count;
        } while (--m);
    }
    w->v31();

    if (count > 0) {
        int rowBase = 0;
        int fourI = 0;
        int i = 0;
        do {
            if (flag)
                w->v19(fourI / count + 2);
            int a = (i == count - 1) ? 0 : (rowBase + count);
            for (int j = 0; j < count - 1; ++j) {
                int idx = a + 1 + j;
                w->v20(9);
                w->v25(7, idx - 1);
                w->v25(7, idx);
                w->v25(7, (rowBase - a) + idx);
                w->v25(7, rowBase + j);
                w->v31();
            }
            ++i;
            rowBase += count;
            fourI += 4;
        } while (i < count);
    }

    w->v4();
}

// @ 0x0071d960
void __cdecl EmitDisc(Rend* w, float a, float b, char flag, int count)
{
    w->v3();
    w->v19(0);

    float nb = -b;
    float nz = -(a / nb);
    float angle = 0.0f;
    int vert = 0;
    if (count > 0) {
        float invLast = (float)(count - 1);
        float fcount = (float)count;
        vert = count * count;
        int rows = count;
        do {
            float cosA = (float)cos(angle);
            float sinA = (float)sin(angle);
            int col = 0;
            do {
                Vector3 p;
                Vector3 n;
                float colN = (float)col / invLast;
                float X = colN * a;
                p.x = cosA * X;
                p.y = sinA * X;
                p.z = colN * nb;
                w->v6(&p);
                n.x = cosA;
                n.y = sinA;
                n.z = nz;
                w->v7(&n);
                ++col;
            } while (col < count);
            angle = (g_discStep * 2.0f) / fcount + angle;
        } while (--rows);
    }

    if (flag) {
        Vector3 n;
        n.x = 0.0f;
        n.y = 0.0f;
        n.z = -1.0f;
        w->v7(&n);
        w->v20(9);
        w->v22(vert);
        if (count > 0) {
            int e = vert - 1;
            int m = count;
            do {
                w->v21(e);
                e -= count;
            } while (--m);
        }
        w->v31();
    }

    if (count > 0) {
        int rowStart = 1;
        int i = 0;
        do {
            int last = count - 1;
            int aa = (i == last) ? 0 : (rowStart + last);
            if (last > 0) {
                int rb = aa;
                int idx = rowStart;
                int j = last;
                do {
                    w->v20(9);
                    w->v25(3, idx - 1);
                    w->v25(3, idx);
                    w->v25(3, (aa - rowStart + 1) + idx);
                    w->v25(3, rb);
                    w->v31();
                    ++idx;
                    ++rb;
                } while (--j);
            }
            ++i;
            rowStart += count;
        } while (i < count);
    }

    w->v4();
}

// @ 0x0071ef50
void VecInt::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        struct { short lo, hi; } v;   // element default value: two zeroed 16-bit halves
        v.lo = 0;
        v.hi = 0;
        DoInsertValues(mpEnd, n - (unsigned)(mpEnd - mpBegin), (const int*)&v);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}
