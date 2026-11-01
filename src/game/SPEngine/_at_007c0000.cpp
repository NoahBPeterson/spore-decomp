// src/game/SPEngine/_at_007c0000.cpp -- migrated from slice(s) s007cf310, s007ce500, s007cd6d0, s007c77e0, s007c5a90, s007c4be0, s007c3ba0, s007c2ab0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_007c0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <xmmintrin.h>
#include <string.h>
#include <math.h>
#include "SP/cViewer.h"
#include "SP/cShaderDataRenderType.h"
#include "rw/core/arena/Arena.h"
#include "SP/cCameraManager.h"
#include "EA/ArgScript/cIFileParser.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cConfigManager.h"
#include "SP/cConfigScriptState.h"
#include "SP/cOption.h"
#include <math.h>       // fabsf -> x87 fabs
#include <stdlib.h>     // abs  -> cdq/xor/sub
#include "EA/Random/RandomLinearCongruential.h"

// ---- items of slice s007c2ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Mat4 {
    __m128 a, b, c, d;                 // 4 x 16 bytes
    void CopyMat4(const Mat4* src);
};
struct HNode { unsigned key; int value; HNode* next; };
struct HIter { HNode* node; HNode** bucket; };
struct HMap {
    HNode** mpBucketArray; unsigned mnBucketCount; unsigned mnElementCount;
    void DoFreeNodes(HNode** b, unsigned n);
    HIter find(const unsigned& k) const;
    int& operator[](const unsigned& k);
};
struct HMapHolder { int pad; HMap m; };
extern HMapHolder gTable;
void FUN_00761130(int);
// ---- items of slice s007c2ab0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern HMapHolder gTable;

// ---- items of slice s007c3ba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_16f6dac;
extern int g_16f8a38;
extern int g_16f9110;
struct Vec4 { float x, y, z, w; };
struct Matrix44 {
    Vec4 xAxis, yAxis, zAxis, wAxis;    // +0x00,+0x10,+0x20,+0x30
    void FUN_007c3da0(float* dst);
};
struct Camera {
    char pad0[0x54];
    float f54, f58;                 // +0x54,+0x58
    float f5c, f60;                 // +0x5c,+0x60 (width,height)
    float f64, f68;                 // +0x64,+0x68 (inverse)
    int   n6c;                      // +0x6c (projection type)
    float f70, f74;                 // +0x70,+0x74
    int   vpX, vpY, vpW, vpH;       // +0x78,+0x7c,+0x80,+0x84 (viewport)
    int   f88, f8c;                 // +0x88,+0x8c
    void SetClear(void* color, int flags);
};
struct cViewer {
    Matrix44 mCameraToWorldTransform;      // +0x00
    Matrix44 mWorldToCameraTransform;      // +0x40
    Matrix44 mCameraToClipTransform;       // +0x80
    Matrix44 mWorldToClipTransform;        // +0xc0
    Matrix44 mClipToWorldTransform;        // +0x100
    float    mClearColor[4];               // +0x140
    int      mRenderType;                  // +0x150
    int      mRenderTypeVariation;         // +0x154
    int      mShaderDataRT;                // +0x158
    float    mMaterialLODs[4];             // +0x15c
    unsigned char mTileRender;             // +0x16c
    char pad1[3];
    Camera*  mCamera;                      // +0x170

    bool   FUN_007c3ba0();
    void   FUN_007c3c50(unsigned char);
    float  FUN_007c3c90();
    float  FUN_007c3ca0();
    void   GetCameraLocationInfo(float*, float*, float*, float*);
    cViewer* FUN_007c3f70();
    void   FUN_007c4000();
    void   FUN_007c4010(unsigned*);
    float  FUN_007c4050();
    float  FUN_007c40a0();
    void   FUN_007c40c0(float*, float*);
    float  FUN_007c40e0();
    void   FUN_007c40f0(unsigned short*);
    void   FUN_007c4180(float*, const float*);            // clip-space perspective divide
    void   FUN_007c42a0(float*);                          // build projection matrix
    bool   FUN_007c43e0();                                // rebuild the device matrices
    bool   FUN_007c4510(float, float, float*, float*);    // screen -> world (projected)
    bool   FUN_007c4730(float, float, float*, float*);    // screen -> world ray
    void   FUN_007c46f0(void*, void*);
    void   FUN_007c4900(void*, void*);
    void   FUN_007c4a60(unsigned short*);
    void   FUN_007c4ad0(float, float);
    void   FUN_007c4b00(float, float);
    void   FUN_007c4b50(float);
    void   FUN_007c4ba0(float);
    void   FUN_007c4bc0(float);
    void   FUN_007c4940();                  // recompute derived transforms
};
void __cdecl EASTL_deallocate(void*);      // 0x00f47380
void __cdecl FUN_00f47410(void*);
// ---- items of slice s007c3ba0 end

// ---- items of slice s007c4be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* ArenaTypeRegGetType(int type);   // 0x11e22c0
extern "C" void* OpNewArray(void* p, int a, int b); // 0x11e073e
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct rwArena {
    char pad[0x40];
    int ObjectToId(int id);   // 0x11e3c30
    int IdToObject(int id);   // 0x11e2300
};
struct ArenaInner { rwArena* m_arena; };            // first dword is arena
struct ResMgr1 { char pad[0x80]; ArenaInner* m_inner; };
struct ResourceHolder { char pad[0x1c]; ResMgr1* m_mgr; };
struct rwArray { char pad[0x14]; int m_count; float* Get(int i); };
struct SerializedArray {
    char pad[8];
    void* mData;   // +8
    int   mCount;  // +0xc
    void* Alloc();
};
struct SomeDesc {
    u8 b0, b1, b2, b3;   // +0
    u16 w4;              // +4
    u16 w6;              // +6
    u8  b8;              // +8
    u8  b9;              // +9
    u16 wa;              // +a
    u16 wc;              // +c
    u16 we;              // +e
    u16 w10;             // +10
    u8  b12;             // +12
    u8  b13;             // +13
    u32 d14;             // +14
    u32 d18;             // +18
    u32 d1c;             // +1c
};
// ---- items of slice s007c4be0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int ResolveFF0002(void* obj, int unused, ResMgr1* mgr);  // 0x007c5760 (stays in the slice: not this object's)

// ---- items of slice s007c5a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   FUN_007c5820(void);
extern "C" int   FUN_007c5920(void);
struct FILE;
extern "C" FILE* fopen(const char*, const char*);
extern "C" int   fclose(FILE*);
extern "C" unsigned int fwrite(const void*, unsigned int, unsigned int, FILE*);
// ---- items of slice s007c5a90 end

// ---- items of slice s007c77e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t g_BitLengthTable[];   // 0x01410e24
struct cRandom {
    char pad0[4];
    const uint8_t* mData;   // +0x04
    uint32_t mSize;         // +0x08
    uint32_t mPos;          // +0x0c
    uint32_t mPoly;         // +0x10
    uint32_t mState;        // +0x14
    uint32_t mMask;         // +0x18

    void Init(const uint8_t* data, uint32_t size);  // 0x007c7770
    bool Seed(const char* name);                    // 0x007c77e0
    int  Mode();                                    // 0x007c78c0
    int  Query(int which);                          // 0x007c78e0
    int  Read(void* dst, int n);                    // 0x007c7910
    bool Reset();                                   // 0x007c7980
};
// ---- items of slice s007c77e0 end

// ---- items of slice s007cd6d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _ReadWriteBarrier();
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#ifndef SPORE_S007CA950_H
#endif  // SPORE_S007CA950_H
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(_InterlockedIncrement)
typedef unsigned __int64 uint64;
inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
namespace eastl {
template <typename T1, typename T2> struct pair_s007c_d6d0 {
    T1 first;
    T2 second;
    pair_s007c_d6d0() {}
    pair_s007c_d6d0(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
template <typename T> T* uninitialized_copy_ptr(const T* first, const T* last, T* result) {
    T* d = result;
    for (; first != last; ++first, ++d)
        ::new ((void*)d) T(*first);
    return d;
}
}
namespace EA {
template <typename T> class AutoRefCount_s007c_d6d0 { public:
    T* mpObject;   // +0
    AutoRefCount_s007c_d6d0(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s007c_d6d0(const AutoRefCount_s007c_d6d0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s007c_d6d0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s007c_d6d0& operator=(const AutoRefCount_s007c_d6d0& x) {
        if (x.mpObject != mpObject) {
            T* pOld = mpObject;
            if (x.mpObject) x.mpObject->AddRef();
            mpObject = x.mpObject;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    AutoRefCount_s007c_d6d0& operator=(T* p) {
        if (p != mpObject) {
            T* pOld = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};
}
namespace EA {
struct Variant_s007c_d6d0 {
    unsigned int mData[4];   // +0
    unsigned short mFlags;   // +0x10
    unsigned short mTypeId;  // +0x12
    Variant_s007c_d6d0() : mFlags(0), mTypeId(0) {}
    ~Variant_s007c_d6d0() { if (mFlags & 4) Destruct(false); }
    Variant_s007c_d6d0& operator=(const Variant_s007c_d6d0& x);
    template <typename T> Variant_s007c_d6d0& operator=(const T& x);
    void Destruct(bool bReconstruct);  // 0x0093db80 (EA::Variant::Destruct)
};
}
namespace SP {
class cPropertyList_s007c_d6d0 {
public:
    virtual void AddRef();                                       // +0x00
    virtual void Release();                                      // +0x04
virtual void v02();
virtual void v03();
virtual void v04();
    virtual void SetProperty(int id, const EA::Variant_s007c_d6d0& value);  // +0x14 0x006a2e20
virtual void v18();
virtual void v1C();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2C();
    virtual void v30(cPropertyList_s007c_d6d0* p);                          // +0x30
    char pad[0x38 - 4];
};
}
typedef eastl::pair_s007c_d6d0<uint64, EA::AutoRefCount_s007c_d6d0<SP::cPropertyList_s007c_d6d0> > PropPair;
namespace EA {
namespace Messaging {
 void* __cdecl GetServer();   // 0x00883860
}
}
struct cConfigManagerS {
    void Initialize();
    bool SetupParser(void* cmd, bool p3);
    void TryConfigure();
    bool Configure();
    void Unnamed960();
    void Unnamed990();
    bool Unnamed9C0();
    void UnnamedA70(float* v);
};
#define VTOBJ(p)      (*(void***)(p))
// ---- items of slice s007cd6d0 end

// ---- items of slice s007ce500 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" void* __cdecl EAlloc(uint32_t size, const char* name, int flags, int debugFlags,
                                const char* file, int line);   // 0x00f473a0
extern "C" void  __cdecl EFree(void* p);                       // 0x00f47380
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" void* __cdecl FUN_0099efa0(void* src, void* end, void* dst); // uninitialized_copy
extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned int n); // 0x011e0744 memcpy
extern "C" void  __cdecl FUN_0076ffd0(void* a, void* b, void* c, void* d, void* e);
extern "C" void  __cdecl FUN_0073fe50(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_00a52da0(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_006ac440(void* a, int n, void* v);
#pragma intrinsic(_InterlockedExchangeAdd)
struct IMessagingServer {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void Unregister(void* obj, int id, int code);   // 0x2c
};
extern "C" IMessagingServer* GetServer_s007c_e500();  // 0x00883860
struct PaintSystemBase {
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5();
virtual void b6();
virtual void b7();
    virtual ~PaintSystemBase() {}
};
struct DerivedPaint : PaintSystemBase {
    virtual ~DerivedPaint();
    bool mb4;           // +4
    char pad5[3];
    void* m8;           // +8
    char padC[0x1c - 0xc];
    int m1c;            // +0x1c
};
struct PropList {
    virtual void v0();          // +0
    int m4;                     // +4
    volatile long mRefCount;    // +8
    int Release()
    {
        _InterlockedExchangeAdd(&mRefCount, -1);
        if (_InterlockedExchangeAdd(&mRefCount, 0) < 1) {
            _InterlockedExchangeAdd(&mRefCount, 1);
            return 1;
        }
        return _InterlockedExchangeAdd(&mRefCount, 0);
    }
    void AddRef() { _InterlockedExchangeAdd(&mRefCount, 1); }
};
struct PropPair_s007c_e500 {
    uint64_t first;
    PropList* pObj;
};
inline void ReleaseProp(PropList* p)
{
    p->Release();
}
inline void AddRefProp(PropList* p)
{
    p->AddRef();
}
struct HasVt {
    virtual void d0();
};
struct VecHolder : HasVt {
    bool mb4;
    char pad5[3];
    void* mBegin;   // +8
    void* mEnd;     // +0xc
    void* mCap;     // +0x10
    VecHolder();
};
struct P8 { uint32_t a, b; };
struct Vec8 {
    P8* mpBegin;
    P8* mpEnd;
    P8* mpEndCap;
    void insert(P8* pos, uint32_t n, const P8& value);
    void insert(P8* pos, const P8& value);
};
// ---- items of slice s007ce500 end

// ---- items of slice s007cf310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl FUN_004b54b0(void*);
extern "C" const char s_vec16[];   // 0x13ebb38 allocator.h site string
extern "C" const char n_vec16[];   // 0x13ebc58 "App"
extern "C" void* __cdecl FUN_007cde30(void*, void*, void*);   // uninitialized copy (ret dst)
extern "C" void  __cdecl FUN_007cede0(void*, void*, void*);   // uninitialized copy (no ret)
extern "C" void  __cdecl FUN_007ceec0(void*, void*, void*);   // shift range back
extern "C" void* __cdecl FUN_00ec4ac0(void*, void*, void*, int);   // lower_bound (map A)
extern "C" void  __cdecl FUN_007cf630(unsigned);                   // Vec8::resize
extern "C" void  __cdecl FUN_00d018d0(void*, void*);               // vector erase
extern "C" void  __cdecl FUN_006130e0(void*, void*);               // vector<bool> clear
extern "C" void* __cdecl VecBoolDoInsertValue(void*, void*, int);  // 0x11e0744
extern "C" void* __cdecl FUN_007cee40(void*, void*, void*);
extern "C" void  __cdecl FUN_00533500(void*, void*);
struct AutoRef {
    void* p;
    AutoRef() {}
    AutoRef(const AutoRef& o) {
        p = o.p;
        if (p)
            _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1);
    }
};
struct RefField {
    void* p;
    void ctor(const RefField& src);
};
struct VecCommon {
    void* mpBegin;   // +0
    void* mpEnd;     // +4
    void* mpCap;     // +8
    void destructRange(void* first, void* last);   // 0x007cefd0  (thiscall, ret 8)
    void destroy();                                // 0x007cef60  (~vector)
};
struct Pair8   { uint32_t key, sub; };                 // 8-byte key view of a map element
struct MapElem { unsigned ka, kb; AutoRef ref; unsigned d; };   // 16-byte map element
struct Slot8   { uint32_t a, b; };
struct E16 { unsigned a, b, c, d; };
extern "C" void* __cdecl UninitCopy16(E16** out, E16* first, E16* last, E16* dst, E16* pos);
extern "C" E16*  __cdecl eastl_copy_backward(E16* first, E16* last, E16* dst);
extern "C" void  __cdecl eastl_fill_n(E16* dst, unsigned n, const E16* value, E16* pos);
extern "C" void  __cdecl eastl_fill(E16* first, E16* last, const E16* value);
extern "C" E16*  __cdecl eastl_move(E16* first, E16* last, E16* dst);
struct Vec16 {
    E16*  mpBegin;   // +0x0
    E16*  mpEnd;     // +0x4
    E16*  mpCap;     // +0x8
    char  pad0c[4];  // +0xc
    E16*  mpInline;  // +0x10
    void insert(E16* pos, unsigned n, const E16* pv);
};
struct V16 {
    void* mBegin;    // +0
    void* mEnd;      // +4
    void* mCap;      // +8
    void* mMid;      // +0xc  (object whose dtor is FUN_007cef60)
    void* mInline;   // +0x10
    void clear();
};
struct Big {
    int f0, f4, f8, fc;
    char p10[0xc];
    int f1c, f20, f24;
    char p28[0xc];
    int f34, f38, f3c;
    char p40[0xc];
    int f4c, f50, f54;
    char p58[0xc];
    int f64, f68, f6c;
    char p70[8];
};
struct Vec8_s007c_f310 {
    Slot8* mpBegin;
    Slot8* mpEnd;
    Slot8* mpCap;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void insert(Slot8* pos, uint32_t n, const Slot8& value);   // 0x007cf030 external
    void erase(Slot8* first, Slot8* last);                     // 0x00d018d0 external
    void resize(uint32_t n);
};
struct MapX {
    void*  mpTree;    // +0
    void*  mpBegin;   // +4  (end of the node vector)
    char   pad8[0x14 - 8];
    bool   mb14;      // +0x14
    char   pad15[0x18 - 0x15];
    void*  mpRoot;    // +0x18
    Pair8* insertAt(void* pos, Pair8* kv);
    Pair8* findOrInsert(char* out, Pair8* kv);
};
struct MapY {
    void* mpTree;    // +0
    void* mpEnd;     // +4
    void* mpRoot;    // +8
    void insertPair(void* pos, void* value);
};
struct MapZ {
    char    pad0[8];
    Slot8*  mpBegin;   // +8
    Slot8*  mpEnd;     // +0xc
    char    pad10[0x1c - 0x10];
    int     m1c;       // +0x1c
    int     m20;       // +0x20
    bool setSlot(int handle, uint32_t* rec);
};
struct IObj {
    virtual bool probe();                 // +0x10
    virtual void fillTmp(void* t);        // +0x14
};
struct RefPtr {
    void* p;          // +0
    int   refs;       // +4
    void release() {
        if (p)
            ((void(__thiscall*)(void*))*(void**)(*(char**)p + 4))(p);
    }
};
struct ObjX2 {
    int   m0;             // +0
    char  pad04[0x1c - 4];
    void* m1c;            // +0x1c  begin
    void* m20;            // +0x20  end
    char  pad24[0x34 - 0x24];
    void* m34;            // +0x34  begin
    void* m38;            // +0x38  end
    void  clear();
};
struct ObjX { void destroy(); };   // 0x007cf4e0 external thiscall
struct PtrX {
    ObjX* p;
    void reset();
};
struct MapW {
    void* mpTree;    // +0
    void* mpEnd;     // +4
    void* mpRoot;    // +8
    char  pad0c[0x10 - 0xc];
    void* mpCap;     // +0x10
    void* tryInsert(void* pos, void* value);
};
struct InnerC {
    char  pad00[0x34];
    void* m34;           // +0x34
    void* m38;           // +0x38
    char  pad3c[0x4c - 0x3c];
    void* m4c;           // +0x4c
    void* m50;           // +0x50
    void  clear();
};
struct W {
    InnerC* m;
    void clear();
};
// ---- items of slice s007cf310 end

// @ 0x007c3910
void FUN_007c3910()
{
    HNode* n = *gTable.m.mpBucketArray;
    HNode** p = gTable.m.mpBucketArray;
    if (!n) {
        ++p;
        while (!*p) ++p;
        n = *p;
    }
    HNode* end = gTable.m.mpBucketArray[gTable.m.mnBucketCount];
    while (n != end) {
        FUN_00761130(n->value);
        n = n->next;
        if (!n) { do { n = *++p; } while (!n); }
    }
    gTable.m.DoFreeNodes(gTable.m.mpBucketArray, gTable.m.mnBucketCount);
    gTable.m.mnElementCount = 0;
}

// @ 0x007c3b70
void Mat4::CopyMat4(const Mat4* src)
{
    a = src->a;
    b = src->b;
    c = src->c;
    d = src->d;
}

// @ 0x007c3ba0
bool cViewer::FUN_007c3ba0()
{
    if (mShaderDataRT != 0) {
        if (g_16f6dac == mShaderDataRT) {
            g_16f8a38 = g_16f8a38 | 2;
            g_16f9110 = g_16f9110 | 8;
            g_16f6dac = 0;
        }
        EASTL_deallocate((void*)mShaderDataRT);
        mShaderDataRT = 0;
    }
    if (mCamera != 0) {
        FUN_00f47410(mCamera);
        mCamera = 0;
        return true;
    }
    return false;
}

// @ 0x007c3c50
void cViewer::FUN_007c3c50(unsigned char param)
{
    int flags = 0;
    if ((param & 1) != 0)
        flags = 1;
    if ((param & 2) != 0)
        flags = flags | 2;
    if ((param & 4) != 0)
        flags = flags | 4;
    mCamera->SetClear(mClearColor, flags);
}

// @ 0x007c3c90
float cViewer::FUN_007c3c90()
{ return mCamera->f70; }

// @ 0x007c3ca0
float cViewer::FUN_007c3ca0()
{ return mCamera->f74; }

// @ 0x007c5490
void* SerializedArray::Alloc()
{
    return OpNewArray(mData, 0, mCount * 4);
}

// @ 0x007c54b0
void* ResolveOne(void* obj, ResourceHolder* holder)
{
    int* p = (int*)((char*)obj + 0x3c);
    if (*p == 0) {
        *p = -1;
        return holder;
    }
    *p = holder->m_mgr->m_inner->m_arena->ObjectToId(*p);
    return holder;
}

// @ 0x007c54f0
void ResolveOneToObject(void* obj, int unused, ResMgr1* mgr)
{
    int* p = (int*)((char*)obj + 0x3c);
    if (*p == -1) {
        *p = 0;
        return;
    }
    *p = mgr->m_inner->m_arena->IdToObject(*p);
}

// @ 0x007c5520
int ResolveAllOne(void* obj, ResMgr1* mgr)
{
    int* p = (int*)((char*)obj + 0x3c);
    if (*p == -1) {
        *p = 0;
        return 1;
    }
    *p = mgr->m_inner->m_arena->IdToObject(*p);
    return 1;
}

// @ 0x007c5560
void* ResolveMany(void* a, ResourceHolder* holder)
{
    int n = *(int*)((char*)a + 4);
    for (int i = 0; i < n; i++) {
        int* e = (int*)(*(void**)a);
        int id = e[i * 2 + 1];
        int r = (id == 0) ? -1 : holder->m_mgr->m_inner->m_arena->ObjectToId(id);
        ((int*)*(void**)a)[i * 2 + 1] = r;
    }
    if (*(void**)a == 0) {
        *(int*)a = -1;
        return holder;
    }
    *(int*)a = holder->m_mgr->m_inner->m_arena->ObjectToId(*(int*)a);
    return holder;
}

// @ 0x007c55d0
void ResolveManyToObject(void* a, int unused, ResMgr1* mgr)
{
    int x = (*(int*)a == -1) ? 0 : mgr->m_inner->m_arena->IdToObject(*(int*)a);
    *(int*)a = x;
    int n = *(int*)((char*)a + 4);
    for (int i = 0; i < n; i++) {
        int* e = (int*)(*(void**)a);
        int id = e[i * 2 + 1];
        int r = (id == -1) ? 0 : mgr->m_inner->m_arena->IdToObject(id);
        ((int*)*(void**)a)[i * 2 + 1] = r;
    }
}

// @ 0x007c5630
int ResolveManyToObject2(void* a, ResMgr1* mgr)
{
    int x = (*(int*)a == -1) ? 0 : mgr->m_inner->m_arena->IdToObject(*(int*)a);
    *(int*)a = x;
    int n = *(int*)((char*)a + 4);
    for (int i = 0; i < n; i++) {
        int* e = (int*)(*(void**)a);
        int id = e[i * 2 + 1];
        int r = (id == -1) ? 0 : mgr->m_inner->m_arena->IdToObject(id);
        ((int*)*(void**)a)[i * 2 + 1] = r;
    }
    return 1;
}

// @ 0x007c56a0
int SerializeArray(int out, int* src)
{
    if (out == 0) out = src[2];
    rwArray* arr = (rwArray*)src[0];
    u32 n = (u32)arr->m_count;
    for (u32 i = 0; i < n; i++)
        ((float*)out)[i] = *arr->Get((int)i);
    return 1;
}

// @ 0x007c56e0
void RegFF0000C()
{
    void* t = ArenaTypeRegGetType(0xff0000);
    if (t) *(void**)((char*)t + 0xc) = (void*)&ResolveAllOne;
}

// @ 0x007c5700
void RegFF0000()
{
    void* t = ArenaTypeRegGetType(0xff0000);
    if (t) {
        *(void**)((char*)t + 4) = (void*)&ResolveOne;
        *(void**)((char*)t + 8) = (void*)&ResolveOneToObject;
    }
}

// @ 0x007c5720
void RegFF0001C()
{
    void* t = ArenaTypeRegGetType(0xff0001);
    if (t) *(void**)((char*)t + 0xc) = (void*)&ResolveManyToObject2;
}

// @ 0x007c5740
void RegFF0001()
{
    void* t = ArenaTypeRegGetType(0xff0001);
    if (t) {
        *(void**)((char*)t + 4) = (void*)&ResolveMany;
        *(void**)((char*)t + 8) = (void*)&ResolveManyToObject;
    }
}

// @ 0x007c57c0
void RegFF0002C()
{
    void* t = ArenaTypeRegGetType(0xff0002);
    if (t) *(void**)((char*)t + 0xc) = (void*)&ResolveFF0002;
}

// @ 0x007c57e0
int IsType1Or9(int p)
{
    char c = *(char*)(p + 2);
    if (c == 1 || c == 9) return 1;
    return 0;
}

// @ 0x007c5800
int IsType9to11(int p)
{
    char c = *(char*)(p + 2);
    if (c == 9 || c == 10 || c == 11) return 1;
    return 0;
}

// @ 0x007c5820
static int AdjacentRowsMatch(int base, u32 cnt, u32 st, u32 row)
{
    if (row == cnt - 1) return 0;
    const char* a = (const char*)(base + row * st);
    const char* b = (const char*)(base + (row + 1) * st);
    for (u32 j = 0; j < st; j++)
        if (a[j] != b[j]) return 0;
    if (st > 1) return 1;
    if ((int)row >= (int)cnt - 2) return 0;
    const char* c = (const char*)(base + (row + 2) * st);
    for (u32 j = 0; j < st; j++)
        if (b[j] != c[j]) return 0;
    return 1;
}

// @ 0x007c5920
u32 FindMatch(int base, int p2, int p3, int stride, int mode)
{
    // The original loads the row stride only after the early exits, so keep that load (and the
    // scratch register it needs) out of the fast path.
    u32 n = (u32)p3 & 0xffff;
    u32 idx = (u32)p2 & 0xffff;
    u32 eax = n - 1;                       // lea eax,[esi-1]
    u8 k = 2;
    if (idx == n - 1) return (eax & ~0xffu) | 1;
    if (idx == n - 2) return (eax & ~0xffu) | 2;
    if (mode == 1) {
        // Mode 1 compares row idx against row idx+k in line (the original inlines it) and
        // returns as soon as a byte differs; the other mode calls 0x7c5820 instead.
        if ((int)(idx + 2) >= (int)n) return (eax & ~0xffu) | k;
        u32 st = (u32)stride & 0xffff;     // movzx edi,word[esp+0x24]
        const char* row = (const char*)(base + idx * st);
        for (;;) {
            const char* other = (const char*)(base + (idx + k) * st);
            int differs = 0;
            for (u32 j = 0; j < st; j++) {
                if (row[j] != other[j]) { differs = 1; break; }
            }
            if (differs) return ((u32)other & ~0xffu) | k;   // eax = that row pointer
            k++;
            if (k == 0x80) return ((u32)other & ~0xffu) | 0x80;
            if ((int)(idx + k) >= (int)n)
                return ((u32)(base + (idx + k) * st) & ~0xffu) | k;
        }
    } else {
        if ((int)(idx + 2) >= (int)n) return (eax & ~0xffu) | k;
        u32 st = (u32)stride & 0xffff;
        for (;;) {
            if (AdjacentRowsMatch(base, n, st, idx + k)) return k;   // eax = the helper's 1
            k++;
            if (k == 0x80) return 0x80;
            if ((int)(idx + k) >= (int)n)
                return ((idx + k) & ~0xffu) | k;            // eax = bl+idx, then al = bl
        }
    }
}

// @ 0x007c5a40
void InitDesc(SomeDesc* d, u32 p2, u16 p3, u16 p4, u8 p5)
{
    d->w4 = 0;
    d->w6 = 0;
    d->wa = 0;
    d->wc = 0;
    d->we = p3;
    d->b0 = 0;
    d->b1 = 0;
    d->b2 = 0;
    d->b8 = 0;
    d->w10 = p4;
    d->d14 = 0;
    d->d18 = 0;
    d->b12 = p5;
    d->b13 = 0x20;
    d->d1c = p2;
}

// @ 0x007c5a90
int WriteScan(FILE* f, const u8* d, u8* base)
{
    u32 px = (u32)(d[0x12] >> 3);
    u16 row = 0;
    if (*(const u16*)(d + 0xe) == 0) return 0;
    do {
        int cmp = FUN_007c5820();
        u8 n = (u8)FUN_007c5920();
        u8 tag = (u8)(n - 1);
        if (cmp == 1) tag |= 0x80;
        if (fwrite(&tag, 1, 1, f) != 1) return 3;
        u32 sz = px;
        if (cmp != 1) sz = (u32)n * px;
        if (fwrite(base + (u32)row * px, sz, 1, f) != 1) return 3;
        row = (u16)(row + n);
    } while (row < *(const u16*)(d + 0xe));
    return 0;
}

// @ 0x007c5b90
u32 WriteImage(FILE* f, const u8* d)
{
    u32 local;
    if (fwrite(d, 1, 1, f) != 1) return 3;
    if (d[1] != 0 && d[1] != 1) return 4;
    if (fwrite(d + 1, 1, 1, f) != 1) return 3;
    u8 fmt = d[2];
    if (fmt == 0) return 6;
    if (fmt != 1 && fmt != 2 && fmt != 3 && fmt != 9 && fmt != 10 && fmt != 11)
        return 5;
    if (fwrite(d + 2, 1, 1, f) != 1) return 3;

    int t = IsType1Or9((int)d);
    if (t != 0 && d[1] == 0) return 7;
    if (t == 0) {
        if (d[1] == 1) return 8;
    } else if (d[1] == 1) {
        if (*(const u16*)(d + 6) == 0) return 9;
        u8 bd = d[8];
        if (bd != 0x10 && bd != 0x18 && bd != 0x20) return 10;
    }

    local = *(const u16*)(d + 4);
    if (fwrite(&local, 2, 1, f) != 1) return 3;
    local = *(const u16*)(d + 6);
    if (fwrite(&local, 2, 1, f) != 1) return 3;
    if (fwrite(d + 8, 1, 1, f) != 1) return 3;
    local = *(const u16*)(d + 10);
    if (fwrite(&local, 2, 1, f) != 1) return 3;
    local = *(const u16*)(d + 0xc);
    if (fwrite(&local, 2, 1, f) != 1) return 3;

    if (*(const u16*)(d + 0xe) == 0 || *(const u16*)(d + 0x10) == 0) return 0xb;
    local = *(const u16*)(d + 0xe);
    if (fwrite(&local, 2, 1, f) != 1) return 3;
    local = *(const u16*)(d + 0x10);
    if (fwrite(&local, 2, 1, f) != 1) return 3;

    u8 bpp = d[0x12];
    if (bpp != 8) {
        if (bpp != 0x10 && bpp != 0x18 && bpp != 0x20) return 0xc;
        if (IsType1Or9((int)d) != 0) return 0xc;
    }
    if (fwrite(d + 0x12, 1, 1, f) != 1) return 3;
    if (fwrite(d + 0x13, 1, 1, f) != 1) return 3;

    if (d[0] != 0 && fwrite(d + 0x14, d[0], 1, f) != 1) return 3;
    if (d[1] == 1) {
        void* p = (void*)(((int)((u32)*(const u16*)(d + 4) * d[8]) >> 3) + *(const int*)(d + 0x18));
        u32 n = (u32)((int)((u32)*(const u16*)(d + 6) * d[8]) >> 3);
        if (fwrite(p, n, 1, f) != 1) return 3;
    }

    if (IsType9to11((int)d) == 0) {
        int n = (int)((u32)*(const u16*)(d + 0x10) * *(const u16*)(d + 0xe) * d[0x12]);
        if (fwrite(*(void**)(d + 0x1c), (u32)((n + (n >> 0x1f & 7)) >> 3), 1, f) != 1)
            return 3;
    } else {
        u32 i = 0;
        if (*(const u16*)(d + 0x10) != 0) {
            do {
                u32 r = WriteScan(f, d, 0);
                if (r != 0) return r;
                i++;
            } while ((u16)i < *(const u16*)(d + 0x10));
        }
    }
    static const char trailer[0x1a] = {0};
    if (fwrite(trailer, 0x1a, 1, f) != 1) return 3;
    return 0;
}

// @ 0x007c5f00
int WriteImageFile(char* path, void* desc)
{
    FILE* f = fopen(path, "wb");
    if (f == 0) return 1;
    int r = (int)WriteImage(f, (const u8*)desc);
    fclose(f);
    return r;
}

// @ 0x007c78c0
int cRandom::Mode()
{
    return mData ? 0 : -2;
}

// @ 0x007c78e0
int cRandom::Query(int which)
{
    switch (which) {
    case 0: return (int)mPos;
    case 1: return 0;
    case 2: return (int)(mSize - mPos);
    }
    return -1;
}

// @ 0x007c7910
int cRandom::Read(void* dst, int n)
{
    if (mData != 0 && dst != 0 && (mPos + 1) < mSize) {
        uint8_t* out = (uint8_t*)dst;
        while (n--) {
            uint32_t v = mState;
            do {
                if (v & 1)
                    v = (v >> 1) ^ mPoly;
                else
                    v >>= 1;
            } while (v >= mSize);
            mState = v;
            *out = mData[v];
            mPos++;
            out++;
        }
        return (int)(out - (uint8_t*)dst);
    }
    return -1;
}

// @ 0x007c7980
bool cRandom::Reset()
{
    if (mData != 0) {
        uint32_t v = mSize;
        int n = 0;
        if (v & 0xffff0000u) { n = 0x10; v >>= 0x10; }
        if (v & 0xff00u)     { n += 8;   v >>= 8; }
        if (v & 0xf0u)       { n += 4;   v >>= 4; }
        if (v & 0xcu)        { n += 2;   v >>= 2; }
        if (v & 2u)          { n += 1; }
        uint32_t p = g_BitLengthTable[n];
        int m = ++n;
        mPoly  = p;
        mState = p;
        mMask  = (1u << m) - 1;
    }
    return true;
}

// @ 0x007cd960
void cConfigManagerS::Unnamed960()
{
    char* self = (char*)this;
    if (self[4] == 0) {
        void* s = EA::Messaging::GetServer();
        ((void(__thiscall*)(void*, char*, int))VTOBJ(s)[0x24 / 4])(s, self, *(int*)(self + 0x1c));
        self[4] = 1;
    }
}

// @ 0x007cd990
void cConfigManagerS::Unnamed990()
{
    char* self = (char*)this;
    if (self[4] != 0) {
        void* s = EA::Messaging::GetServer();
        ((void(__thiscall*)(void*, char*, int, int))VTOBJ(s)[0x2c / 4])(s, self, *(int*)(self + 0x1c), 0xffffd8f1);
        *(int*)(self + 0x1c) = 0;
        self[4] = 0;
    }
}

// @ 0x007cd9c0
bool cConfigManagerS::Unnamed9C0()
{
    int* p = *(int**)this;
    return *p == 0;
}

// @ 0x007cd9d0
namespace eastl {
template <> PropPair* uninitialized_copy_ptr<PropPair>(const PropPair* first, const PropPair* last, PropPair* result)
{
    PropPair* d = result;
    for (; first != last; ++first, ++d)
        ::new ((void*)d) PropPair(*first);
    return d;
}
}  // namespace eastl

// @ 0x007ced20
DerivedPaint::~DerivedPaint()
{
    if (mb4) {
        GetServer_s007c_e500()->Unregister(this, m1c, 0xffffd8f1);
        m1c = 0;
        mb4 = false;
    }
    void* p = m8;
    if (p && *(int*)((char*)p - 4) != 0)
        EFree(p);
}

// @ 0x007cede0
void* DestructRange_7cede0(PropPair_s007c_e500* begin, PropPair_s007c_e500* end, char* out)
{
    for (; begin != end; begin = (PropPair_s007c_e500*)((char*)begin + 0x10)) {
        if (begin->pObj)
            ReleaseProp(begin->pObj);
        out += 0x10;
    }
    return out;
}

// @ 0x007cee40
PropPair_s007c_e500* CopyRange_7cee40(PropPair_s007c_e500* begin, PropPair_s007c_e500* end, PropPair_s007c_e500* dst)
{
    for (; begin != end; begin = (PropPair_s007c_e500*)((char*)begin + 0x10), dst = (PropPair_s007c_e500*)((char*)dst + 0x10)) {
        dst->first = begin->first;
        PropList* nv = begin->pObj;
        PropList* ov = dst->pObj;
        if (nv != ov) {
            if (nv) AddRefProp(nv);
            dst->pObj = nv;
            if (ov) ReleaseProp(ov);
        }
    }
    return dst;
}

// @ 0x007ceec0
PropPair_s007c_e500* CopyBackward_7ceec0(PropPair_s007c_e500* first, PropPair_s007c_e500* last, PropPair_s007c_e500* dst)
{
    while (last != first) {
        last = (PropPair_s007c_e500*)((char*)last - 0x10);
        dst = (PropPair_s007c_e500*)((char*)dst - 0x10);
        dst->first = last->first;
        PropList* nv = last->pObj;
        PropList* ov = dst->pObj;
        if (nv != ov) {
            if (nv) AddRefProp(nv);
            dst->pObj = nv;
            if (ov) ReleaseProp(ov);
        }
    }
    return dst;
}

// @ 0x007cef40
VecHolder::VecHolder()
: mb4(false), mBegin(0), mEnd(0), mCap(0) {}

// @ 0x007cefd0
void __stdcall DestructRange2_7cefd0(PropPair_s007c_e500* begin, PropPair_s007c_e500* end)
{
    while (begin < end) {
        if (begin->pObj)
            ReleaseProp(begin->pObj);
        begin = (PropPair_s007c_e500*)((char*)begin + 0x10);
    }
}

// @ 0x007cf030
void Vec8::insert(P8* pos, uint32_t n, const P8& value)
{
    if (n <= (uint32_t)(mpEndCap - mpEnd)) {
        if (n > 0) {
            P8 local = value;
            P8* const end = mpEnd;
            const uint32_t tail = (uint32_t)(end - pos);
            if (n < tail) {
                const uint32_t nn = n * 8;
                P8* const src = (P8*)((char*)end - nn);
                FUN_0076ffd0(&pos, src, end, end, src);
                mpEnd = (P8*)((char*)mpEnd + nn);
                FUN_0073fe50(pos, src, end);
                FUN_00a52da0(pos, (char*)pos + nn, &local);
            } else {
                const uint32_t extra = n - tail;
                FUN_006ac440(end, extra, &local);
                mpEnd = (P8*)((char*)mpEnd + extra * 8);
                FUN_0076ffd0(&pos, pos, end, mpEnd, (void*)tail);
                mpEnd = (P8*)((char*)mpEnd + tail * 8);
                FUN_00a52da0(pos, end, &local);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        const uint32_t nNewSize  = (nGrowSize > (nPrevSize + n)) ? nGrowSize : (nPrevSize + n);
        P8* const nb = nNewSize ? (P8*)EAlloc(nNewSize * 8, "App", 0, 0,
             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        P8* mid = (P8*)FUN_0099efa0(mpBegin, pos, nb);
        for (uint32_t i = n; i != 0; --i) {
            if (mid) { mid->a = value.a; mid->b = value.b; }
            mid++;
        }
        P8* ne = (P8*)FUN_0099efa0(pos, mpEnd, mid);
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            EFree(mpBegin);
        mpBegin = nb;
        mpEnd = ne;
        mpEndCap = (P8*)((char*)nb + nNewSize * 8);
    }
}

// @ 0x007cf1f0
void Vec8::insert(P8* pos, const P8& value)
{
    if (mpEnd != mpEndCap) {
        const P8* pValue = &value;
        if (pValue >= pos && pValue < mpEnd)
            ++pValue;
        if (mpEnd)
            mpEnd[0] = mpEnd[-1];
        char* src = (char*)pos;
        int n = (int)((char*)(mpEnd - 1) - src);
        memmove((char*)mpEnd - (n >> 3) * 8, src, n);
        *pos = *pValue;
        mpEnd = (P8*)((char*)mpEnd + 8);
        return;
    }
    const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
    const uint32_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
    P8* const nb = nNewSize ? (P8*)EAlloc(nNewSize * 8, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    const uint32_t off1 = (uint32_t)((char*)pos - (char*)mpBegin);
    P8* mid = (P8*)((char*)FUN_011e0744(nb, mpBegin, off1) + off1);
    if (mid) { mid->a = value.a; mid->b = value.b; }
    const uint32_t off2 = (uint32_t)((char*)mpEnd - (char*)pos);
    P8* ne = (P8*)((char*)FUN_011e0744((char*)mid + 8, pos, off2) + off2);
    if (mpBegin) EFree(mpBegin);
    mpBegin = nb;
    mpEnd = ne;
    mpEndCap = (P8*)((char*)nb + nNewSize * 8);
}

// @ 0x007cf310
void Vec16::insert(E16* pos, unsigned n, const E16* pv)
{
    if (n <= (unsigned)(mpCap - mpEnd)) {
        if (n > 0) {
            E16 t = *pv;
            unsigned nx = (unsigned)(mpEnd - pos);
            E16* oe = mpEnd;
            if (n < nx) {
                UninitCopy16((E16**)&pv, oe - n, oe, oe, pos);
                mpEnd += n;
                eastl_copy_backward(pos, oe - n, oe);
                eastl_fill(pos, pos + n, &t);
            } else {
                eastl_fill_n(oe, n - nx, &t, pos);
                mpEnd += n - nx;
                E16* p0 = pos;
                UninitCopy16((E16**)&pos, p0, oe, mpEnd, p0);
                mpEnd += nx;
                eastl_fill(p0, oe, &t);
            }
        }
    } else {
        unsigned old = (unsigned)(mpEnd - mpBegin);
        unsigned nc = old > 0 ? 2 * old : 1;
        unsigned want = old + n;
        if ((int)nc <= (int)want) { nc = want; } else { want = nc; }
        E16* nb = want ? (E16*)EAlloc(want * sizeof(E16), n_vec16, 0, 0, s_vec16, 0xd1) : 0;
        E16* np = eastl_move(mpBegin, pos, nb);
        eastl_fill_n(np, n, pv, pos);
        np = eastl_move(pos, mpEnd, np + n);
        if (mpBegin && mpBegin != mpInline)
            EFree(mpBegin);
        mpBegin = nb; mpEnd = np; mpCap = nb + want;
    }
}

// @ 0x007cf4b0
void V16::clear()
{
    ((VecCommon*)this)->destructRange(mBegin, mEnd);
    if (mBegin)
        EFree(mBegin);
}

// @ 0x007cf5d0
Big** __fastcall createBig(Big** out)
{
    Big* p = (Big*)EAlloc(0x78, "App", 0, 0, 0, 0);
    if (p) {
        p->f0 = 0; p->f4 = 0; p->f8 = 0; p->fc = 0;
        p->f1c = 0; p->f20 = 0; p->f24 = 0;
        p->f34 = 0; p->f38 = 0; p->f3c = 0;
        p->f4c = 0; p->f50 = 0; p->f54 = 0;
        p->f64 = 0; p->f68 = 0; p->f6c = 0;
        *out = p;
        return out;
    }
    *out = 0;
    return out;
}

// @ 0x007cf630
void Vec8_s007c_f310::resize(uint32_t n)
{
    if (n > size()) {
        Slot8 z;
        z.a = 0;
        z.b = 0;
        insert(mpEnd, n - size(), z);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x007cf690
Pair8* MapX::findOrInsert(char* out, Pair8* kv)
{
    void* end = mpBegin;
    Pair8* r = (Pair8*)FUN_00ec4ac0(mpTree, end, kv, mb14);
    if ((void*)r != end) {
        Pair8* k = kv;
        if (r->sub < k->sub)
            goto doInsert;
        if (r->sub == k->sub) {
            if (r->key < k->key)
                goto doInsert;
        }
        *(Pair8**)out = r;
        out[4] = 0;
        return (Pair8*)out;
    }
doInsert:
    {
        Pair8* ins = this->insertAt(r, kv);
        *(Pair8**)out = ins;
        out[4] = 1;
        return (Pair8*)out;
    }
}

// @ 0x007cf760
void MapY::insertPair(void* pos, void* value)
{
    void* p = mpEnd;
    if (p != mpRoot) {
        if (pos <= value && value < p)
            value = (char*)value + 0x10;
        if (p) {
            MapElem* d = (MapElem*)p;
            MapElem* s = (MapElem*)((char*)p - 0x10);
            d->ka = s->ka;
            d->kb = s->kb;
            new (&d->ref) AutoRef(s->ref);
        }
        FUN_007ceec0(pos, (char*)p - 0x10, p);
        {
            MapElem* d = (MapElem*)pos;
            MapElem* s = (MapElem*)value;
            d->ka = s->ka;
            d->kb = s->kb;
        }
        ((RefField*)((char*)pos + 8))->ctor(*(RefField*)((char*)value + 8));
        mpEnd = (char*)p + 0x10;
        return;
    }
    {
        unsigned old = (unsigned)((char*)p - (char*)mpTree) >> 4;
        unsigned want = old == 0 ? 1 : old * 2;
        void* nb = want ? EAlloc(want * 0x10, n_vec16, 0, 0, s_vec16, 0xd1) : 0;
        void* a = FUN_007cde30(mpTree, pos, nb);
        FUN_007cede0(mpTree, pos, nb);
        if (a) {
            MapElem* d = (MapElem*)a;
            MapElem* s = (MapElem*)value;
            d->ka = s->ka;
            d->kb = s->kb;
            new (&d->ref) AutoRef(s->ref);
        }
        void* b = FUN_007cde30(pos, mpEnd, (char*)a + 0x10);
        FUN_007cede0(pos, mpEnd, (char*)a + 0x10);
        if (mpTree)
            EFree(mpTree);
        mpTree = nb;
        mpEnd = b;
        mpRoot = (char*)nb + want * 0x10;
    }
}

// @ 0x007cf8d0
bool MapZ::setSlot(int handle, uint32_t* rec)
{
    if (handle != m1c)
        return false;
    uint32_t u = rec[0];
    int i = rec[10], a = rec[2], idx = rec[8];
    if (a != 0 && i != 0) {
        if (mpBegin == mpEnd)
            FUN_007cf630((unsigned)i);
        if (i != (int)(mpEnd - mpBegin))
            return false;
        if (mpBegin[idx].a == 0)
            m20 = m20 + 1;
        mpBegin[idx].a = a;
        mpBegin[idx].b = u;
        return true;
    }
    if (mpBegin != mpEnd) {
        if (i != (int)(mpEnd - mpBegin))
            return false;
        if (mpBegin[idx].a != 0)
            m20 = m20 - 1;
        mpBegin[idx].a = 0;
        mpBegin[idx].b = 0;
        if (m20 == 0)
            FUN_00d018d0(mpBegin, mpEnd);
    }
    return true;
}

// @ 0x007cf9b0
void ObjX2::clear()
{
    m0 = 0;
    for (char* e = (char*)m1c; e != (char*)m20; e += 0x10) {
        IObj* o = *(IObj**)(e + 8);
        if (!o)
            continue;
        if (!o->probe()) {
            m0 = m0 + 1;
            continue;
        }
        RefPtr tmp;
        tmp.p = 0;
        tmp.refs = 0;
        o->fillTmp(&tmp);
        FUN_004b54b0(&tmp);
        IObj* q = *(IObj**)(e + 8);
        if (q) {
            *(void**)(e + 8) = 0;
            ((void(__thiscall*)(void*))*(void**)(*(char**)q + 4))(q);
        }
        tmp.refs = -1;
        tmp.release();
    }
    for (char* e = (char*)m34; e != (char*)m38; e += 0x10) {
        RefPtr* r = *(RefPtr**)(e + 8);
        if (r && !(r->refs & 1))
            m0 = m0 + 1;
    }
}

// @ 0x007cfa90
void PtrX::reset()
{
    ObjX* q = p;
    if (q) {
        q->destroy();
        EFree(q);
    }
    p = 0;
}

// @ 0x007cfac0
bool __fastcall checkPtr(ObjX2** pp)
{
    if ((*pp)->m0 != 0)
        (*pp)->clear();
    return (*pp)->m0 == 0;
}

// @ 0x007cfb40
void* MapW::tryInsert(void* pos, void* value)
{
    void* p = mpEnd;
    int idx = (int)((char*)pos - (char*)mpTree) >> 4;
    if (pos != p || p == mpRoot) {
        ((MapY*)(void*)this)->insertPair(pos, value);
        return (char*)mpTree + idx * 0x10;
    }
    mpEnd = (char*)p + 0x10;
    if (p) {
        unsigned* d = (unsigned*)p;
        const unsigned* s = (const unsigned*)value;
        d[0] = s[0];
        d[1] = s[1];
        unsigned ref = s[2];
        d[2] = ref;
        if (ref)
            _InterlockedExchangeAdd((volatile long*)(ref + 8), 1);
    }
    return (char*)mpTree + idx * 0x10;
}

// @ 0x007cfbb0
void InnerC::clear()
{
    // +0x00 : vector<bool>  (begin/end/cap at +0/+4/+8)
    char* v0 = (char*)this;
    char* b0 = *(char**)(v0 + 4);
    char* e0 = *(char**)(v0 + 8);
    VecBoolDoInsertValue(b0, e0, 0);
    *(char**)(v0 + 8) = e0 + ((e0 - b0) >> 3) * -8;

    // +0x34 : vector<Entry16>
    char* v1 = (char*)this + 0x34;
    char* b1 = *(char**)(v1 + 4);
    char* e1 = *(char**)(v1 + 8);
    void* r = FUN_007cee40(e1, e1, b1);
    ((VecCommon*)((char*)this + 0x34))->destructRange(r, e1);
    *(char**)(v1 + 4) = e1 + ((e1 - b1) >> 4) * -0x10;

    // +0x1c : vector<bool-ish>
    char* v2 = (char*)this + 0x1c;
    FUN_006130e0(*(void**)v2, *(void**)(v2 + 4));

    // +0x4c : vector<bool>
    char* v3 = (char*)this + 0x4c;
    char* b3 = *(char**)(v3);
    char* e3 = *(char**)(v3 + 4);
    VecBoolDoInsertValue(b3, e3, 0);
    *(char**)(v3 + 4) = e3 + ((e3 - b3) >> 3) * -8;

    FUN_00533500(*(void**)((char*)this + 0x64), *(void**)((char*)this + 0x68));
}

// @ 0x007cfc60
void W::clear()
{
    m->clear();
}
