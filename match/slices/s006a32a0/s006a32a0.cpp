// Slice s006a32a0 (part 1): EA::ArgScript command/property helpers.
// Module appears to be /O2, no frame pointer, /MD, /arch:SSE (float copies via
// x87 fld/fstp in a few places, SSE movss in others).
#include "s006a32a0.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <intrin.h>

// ---------------------------------------------------------------------------
// cPropertyManager / command stubs with fields at the observed retail offsets
// ---------------------------------------------------------------------------
struct cPropertyManager {
    uint8_t  pad0[0x114];
    char*    mVecBegin;         // +0x114
    char*    mVecEnd;           // +0x118
    uint16_t mPad2[2];
    uint8_t  mInAppProperties;  // +0x1d0  (retail appears shifted; used as +0x1e8 below)

    int  GetSupportedTypes(uint32_t* p, unsigned n);  // 0x006a3400
    bool Empty() const { return mVecBegin == mVecEnd; }
    int  Size() const { return (int)((mVecEnd - mVecBegin) >> 2); }
    int  Count();                                      // 0x006a39a0
    bool GetAt(int idx, uint32_t* out);                // 0x006a39d0
};

struct cCommandStub {
    void Forward(int a, int b);     // 0x006a3310
};

struct cAppPropsCommand {
    uint8_t pad0[4];
    void*   mOwner;                 // +0x4
    uint8_t pad1[0x28];
    void*   mManager;               // +0x30
    void Execute(void* args);       // 0x006a3ce0
    void OnEndParse(int b);         // 0x006a3d10
};

extern void* g_sAppProperties;      // 0x015fd918

// ---------------------------------------------------------------------------
// 006a32a0  bool EA::ArgScript::cExprFunction::EvalBool(int,int)
// ---------------------------------------------------------------------------
bool EA::ArgScript::cExprFunction::EvalBool(int a, int b)
{
    return ((int (__thiscall*)(cExprFunction*, int, int))vftable[1])(this, a, b) != 0;
}

// ---------------------------------------------------------------------------
// 006a32c0  unsigned int FUN_006a32c0(const char* s)
// ---------------------------------------------------------------------------
unsigned int FUN_006a32c0(const char* s)
{
    if (isdigit((unsigned char)*s)) {
        return (unsigned int)strtoul(s, 0, 0);
    }
    return FNVHash(s, 0x811c9dc5u, 1);
}

// ---------------------------------------------------------------------------
// 006a3310  void cCommandStub::Forward(int a, int b)
// ---------------------------------------------------------------------------
void cCommandStub::Forward(int a, int b)
{
    ((void (__thiscall*)(cCommandStub*, int, int, int))(*(void***)this)[0xb])(this, a, 0, b);
}

// ---------------------------------------------------------------------------
// 006a3400  int cPropertyManager::GetSupportedTypes(uint32_t* p, int n)
// ---------------------------------------------------------------------------
int cPropertyManager::GetSupportedTypes(uint32_t* p, unsigned n)
{
    if (p) {
        if (n < 1)
            return 0;
        *p = 0xb1b104;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// Variant setters (12-byte payload)
// ---------------------------------------------------------------------------
Variant& Variant::SetVec21(const void* p)
{
    if (mFlags & 4) Destruct(1);
    if ((mFlags & 2) != 0 && mTypeId != 0x21) {
        SetType(0x21, 0, p, 0xc, 1);
        return *this;
    }
    d0 = ((const uint32_t*)p)[0];
    d1 = ((const uint32_t*)p)[1];
    d2 = ((const uint32_t*)p)[2];
    mTypeId = 0x21;
    mFlags = mFlags & 2;
    return *this;
}

Variant& Variant::SetVec30(const void* p)
{
    if (mFlags & 4) Destruct(1);
    if ((mFlags & 2) != 0 && mTypeId != 0x30) {
        SetType(0x30, 0, p, 8, 1);
        return *this;
    }
    d0 = ((const uint32_t*)p)[0];
    d1 = ((const uint32_t*)p)[1];
    mTypeId = 0x30;
    mFlags = mFlags & 2;
    return *this;
}

Variant& Variant::SetVec31(const void* p)
{
    if (mFlags & 4) Destruct(1);
    if ((mFlags & 2) != 0 && mTypeId != 0x31) {
        SetType(0x31, 0, p, 0xc, 1);
        return *this;
    }
    d0 = ((const uint32_t*)p)[0];
    d1 = ((const uint32_t*)p)[1];
    d2 = ((const uint32_t*)p)[2];
    mTypeId = 0x31;
    mFlags = mFlags & 2;
    return *this;
}

Variant& Variant::SetVec32(const void* p)
{
    if (mFlags & 4) Destruct(1);
    if ((mFlags & 2) != 0 && mTypeId != 0x32) {
        SetType(0x32, 0, p, 0xc, 1);
        return *this;
    }
    d0 = ((const uint32_t*)p)[0];
    d1 = ((const uint32_t*)p)[1];
    d2 = ((const uint32_t*)p)[2];
    mTypeId = 0x32;
    mFlags = mFlags & 2;
    return *this;
}

// ---------------------------------------------------------------------------
// 006a39a0  int cPropertyManager::Count()
// ---------------------------------------------------------------------------
// @ 0x006a39a0
int cPropertyManager::Count()
{
    // Retail reloads mVecEnd for the subtraction instead of keeping it in a
    // register across the branch; the volatile-qualified lvalue forces that
    // load and keeps the begin pointer out of edx.
    if (mVecBegin != mVecEnd)
        return (int)((*(char* volatile*)&mVecEnd - mVecBegin) >> 2);
    return 0;
}

// ---------------------------------------------------------------------------
// 006a39d0  bool cPropertyManager::GetAt(int idx, uint32_t* out)
// ---------------------------------------------------------------------------
// @ 0x006a39d0
bool cPropertyManager::GetAt(int idx, uint32_t* out)
{
    if (mVecBegin != mVecEnd && idx < (int)((mVecEnd - mVecBegin) >> 2)) {
        *out = ((uint32_t*)mVecBegin)[idx];
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 006a3ce0  void cAppPropsCommand::Execute(void* args)
// ---------------------------------------------------------------------------
void cAppPropsCommand::Execute(void* args)
{
    ((EA::ArgScript::cArguments*)args)->MainArguments(0);
    *(uint8_t*)(*(int*)((char*)this + 0x30) + 0x1e8) = 1;
    ((void (__thiscall*)(void*, void*))(*(void***)mOwner)[0x8c / 4])(mOwner, this);
}

// ---------------------------------------------------------------------------
// 006a3d10  void cAppPropsCommand::OnEndParse(int b)
// ---------------------------------------------------------------------------
void cAppPropsCommand::OnEndParse(int b)
{
    (void)b;
    *(uint8_t*)(*(int*)((char*)this + 0x30) + 0x1e8) = 0;
    ++*(uint32_t*)((char*)g_sAppProperties + 0x34);
}

// ---------------------------------------------------------------------------
// 006a3980  const char* FUN_006a3980(int index)
// ---------------------------------------------------------------------------
const char* __stdcall FUN_006a3980(int index)
{
    if (index == 0)
        return "Displays or modifies properties";
    return index == 1 ? "[<propName:string>]                Displays value of given app property" : 0;
}

// ---------------------------------------------------------------------------
// 006a4100  void CopyVec12(void* dst, int n, const void* src)
// ---------------------------------------------------------------------------
// @ 0x006a4100
void* CopyVec12(void* dst, unsigned n, const void* src)
{
    if (n > 0) {
        do {
            if (dst) {
                *(float*)dst = *(const float*)src;
                *((float*)dst + 1) = *((const float*)src + 1);
                *((float*)dst + 2) = *((const float*)src + 2);
            }
            --n;
            dst = (char*)dst + 0xc;
        } while (n > 0);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 006a4360  void FUN_006a4360()
// ---------------------------------------------------------------------------
extern "C" void EA_Dealloc(void* p);    // 0x00f47380

struct cDealloc {
    uint8_t pad0[4];
    void Release();     // 0x006a4360
};

void cDealloc::Release()
{
    char* b = *(char**)((char*)this + 4);
    if (1 < (*(char**)((char*)this + 0xc) - b) && b != 0) {
        EA_Dealloc(b);
    }
}

// ---------------------------------------------------------------------------
// 006a4380  String& String::assign(const char* p)
// ---------------------------------------------------------------------------
struct String {
    void* mpBegin;      // +0
    void* mpEnd;        // +4
    void* mpCapacity;   // +8
    void* mAlloc;       // +0xc
    String& assign(const char* p);
    String& assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
    String* Init(const char** range, const void** tag);  // 0x006a3f40
    void RangeInitialize(unsigned n);                    // 0x00475ab0
};

// @ 0x006a4380
String& String::assign(const char* p)
{
    return assign(p, p + strlen(p));
}

// ---------------------------------------------------------------------------
// 006a3ac0  `anonymous_namespace'::cPropertyListCommand::Execute
// 006a3c30  `anonymous_namespace'::cPropertyListCommand::OnEndParse
// 006a3dd0  property apply helper
// ---------------------------------------------------------------------------
extern "C" void* EA_Alloc2(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void* FUN_006a1b90(void* mem, const char* name);   // 0x006a1b90 (ret 4)
void  FUN_0068d5a0(void* out, unsigned key, unsigned magic); // 0x0068d5a0
void  FUN_006ad010(void* p);                       // 0x006ad010
void  FUN_006ad050(void* p);                       // 0x006ad050
void* FUN_0067dcd0(void);                          // 0x0067dcd0
void  FUN_006a1710(void* txn, void* prop);         // 0x006a1710
void* FUN_006bb640(void);                          // 0x006bb640
void* FUN_00e5c780(void* outA, void* outB, void* map); // 0x00e5c780 (rbtree find)

struct IVtRef {
    virtual void  Slot0();          // +0
    virtual void  Release();        // +4
};
typedef IVtRef* (*GetInfoFn)(void* self);  // vfn at info vtbl +0x10

struct Resource {
    virtual void AddRef();          // +0 (slot 0)
    virtual void Release(int);      // +4 (slot 1)
    void*    mRef;                  // +4
    uint32_t mKey0;                 // +8
    uint32_t mKey1;                 // +0xc
    uint32_t mKey2;                 // +0x10
    Resource* Ctor(const char* name);   // 0x006a1b90
};

template<class T>
struct Ref {
    T* mp;
    void* mk;
    Ref(T* p) : mp(p), mk(0) {}
    ~Ref() { if (mp) mp->Release(1); }
    T* operator->() const { return mp; }
    T* release() { T* t = mp; mp = 0; return t; }
};

// cPropertyListCommand (anonymous namespace)
struct cPropertyListCommand {
    void* vftable;      // +0
    void* mOwner;       // +4
    void* mField8;      // +8
    void* mTxn;         // +0xc
    void* mPropList;    // +0x10
    void Execute(void* args);   // 0x006a3ac0
    void OnEndParse(int b);     // 0x006a3c30
};

// @ 0x006a3ac0
void cPropertyListCommand::Execute(void* args)
{
    char* edi = (char*)((EA::ArgScript::cArguments*)args)->MainArguments(1);
    Ref<Resource> pl((Resource*)EA_Alloc2(0x38, (const char*)0x13ebc58, 0, 0, 0, 0));
    if (pl.mp)
        pl.mp = (Resource*)FUN_006a1b90(pl.mp, *(const char**)edi);
    Resource* old = (Resource*)mPropList;
    if (pl.mp != old) {
        if (pl.mp)
            pl.mp->AddRef();
        mPropList = pl.mp;
        if (old)
            old->Release(1);
    }
    unsigned char buf[0xc];
    *(void**)&buf[0] = 0;
    *(void**)&buf[4] = 0;
    *(unsigned int*)&buf[8] = 0;
    FUN_0068d5a0(buf, *(unsigned int*)mTxn, 0xb1b104);
    unsigned int* dst = (unsigned int*)((char*)mPropList + 8);
    dst[0] = *(unsigned int*)&buf[0];
    dst[1] = *(unsigned int*)&buf[4];
    dst[2] = *(unsigned int*)&buf[8];
    unsigned int* ve = (unsigned int*)((char*)mTxn + 0x1d8);
    if (ve[0] != ve[1]) {
        *(unsigned char*)ve[0] = 0;
        ve[1] = ve[0];
    }
    void* owner = mOwner;
    ((void (__thiscall*)(void*, void*, const void*))(*(void***)owner)[0x90 / 4])(owner, this, (const void*)0x1408db4);
    pl.release();
}

// @ 0x006a3c30
void cPropertyListCommand::OnEndParse(int b)
{
    if (b == 0) {
        ++*(unsigned int*)((char*)mPropList + 0x34);
        void* p = FUN_0067dcd0();
        void* prop = 0;
        if (((bool (__thiscall*)(void*, void*, void**))(*(void***)p)[0x14 / 4])(p, (char*)mPropList + 8, &prop))
            FUN_006ad050(prop);
        FUN_006ad010(mPropList);
        if (mPropList)
            (*(IVtRef**)mPropList)->Release();
    }
    void* pl = mPropList;
    if (pl) {
        mPropList = 0;
        (*(IVtRef**)pl)->Release();
    }
}

// property apply helper (thiscall)
struct cPropsSelf {
    void* vftable;  // +0
    void Apply(void* prop);     // 0x006a3dd0
};

// @ 0x006a3dd0
void cPropsSelf::Apply(void* prop)
{
    unsigned int c;
    if (prop == 0)
        goto cleanup;
    if (!((bool (__thiscall*)(void*, unsigned))(*(void***)prop)[0x1c / 4])(prop, 0xb2cccb)) {
        if (*(void**)((char*)prop + 0x30))
            FUN_006a1710(prop, 0);
        goto cleanup;
    }
    {
        void* var = ((void* (__thiscall*)(void*, unsigned))(*(void***)prop)[0x28 / 4])(prop, 0xb2cccb);
        unsigned short tid = *(unsigned short*)((char*)var + 0x12);
        void* data;
        if (tid == 0x20 || tid == 0x10) {
            if (*(unsigned char*)((char*)var + 0x10) & 0x30)
                data = *(void**)var;
            else
                data = (tid != 0) ? var : 0;
        } else {
            data = FUN_006bb640();
        }
        unsigned int lo = *(unsigned int*)((char*)data + 4);
        unsigned int a = *(unsigned int*)data;
        unsigned int hi = *(unsigned int*)((char*)data + 8);
        if (hi == 0)
            hi = *(unsigned int*)((char*)prop + 0x10);
        unsigned int tmp = lo;
        void* cur = *(void**)((char*)prop + 0x30);
        if (cur && *(unsigned int*)((char*)cur + 8) == a
            && *(unsigned int*)((char*)cur + 0xc) == 0xb1b104
            && *(unsigned int*)((char*)cur + 0x10) == hi)
            goto cleanup;
        {
            void* out = 0;
            void* vt = *(void**)this;
            if (((bool (__thiscall*)(void*, unsigned, unsigned, void**))(*(void***)vt)[0x2c / 4])(this, a, hi, &out)) {
                FUN_006a1710(prop, out);
            }
            if (tmp)
                ((IVtRef*)tmp)->Release();
        }
    }
cleanup:
    c = *(unsigned int*)((char*)prop + 0x30);
    if (c)
        ((IVtRef*)c)->Release();
}


// ===========================================================================
//  External helpers
// ===========================================================================
namespace EA { namespace ArgScript {
class cIMetaCommand {
public:
    void* vftable;      // +0
    void* mParser;      // +4
    int   mRefCount;    // +8
    int   mState;       // +0xc
    void OnRegister(void* parser, int b);   // 0x0083c7f0 (ret 8, only parser used)
};
}}

void* FUN_006bb640(void);
extern "C" void* EA_Alloc(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  EA_Dealloc(void* p);

// external hash-table / rbtree helpers (other slices)
void HashFind(void* out, const void* key, void* table);   // 0x0041fb20
void StringEvalString(void* out, void* arg);              // 0x0083dc00

// ---------------------------------------------------------------------------
// 006a38c0  cCommandStateT<...>::OnRegister
// ---------------------------------------------------------------------------
struct cCommandStateA {
    void* vftable;      // +0
    void* mParser;      // +4
    int   mRefCount;    // +8
    int   mCmd;         // +0xc
    void OnRegister(void* parser, int b);
};

// @ 0x006a38c0
void cCommandStateA::OnRegister(void* parser, int b)
{
    if (b) {
        mCmd = b - 0x10;
        ((EA::ArgScript::cIMetaCommand*)this)->OnRegister(parser, b);
    } else {
        mCmd = 0;
        ((EA::ArgScript::cIMetaCommand*)this)->OnRegister(parser, b);
    }
}

// ---------------------------------------------------------------------------
// 006a38f0  cCommandStateT<...>::OnRegister (variant, field +0x30)
// ---------------------------------------------------------------------------
struct cCommandStateB {
    void* vftable;      // +0
    void* mParser;      // +4
    int   mRefCount;    // +8
    int   mState;       // +0xc
    uint8_t pad[0x20];  // +0x10
    void* mCmd;         // +0x30
    void OnRegister(void* parser, int b);
    void OnRegister2(void* parser, int b);  // 0x0083c780 (external)
};

// @ 0x006a38f0
void cCommandStateB::OnRegister(void* parser, int b)
{
    if (b) {
        mCmd = (void*)(b - 0x10);
        OnRegister2(parser, b);
    } else {
        mCmd = 0;
        OnRegister2(parser, b);
    }
}

// ---------------------------------------------------------------------------
// 006a3430  void EulerFromMatrix(float* out, const float* m)
// ---------------------------------------------------------------------------
extern "C" float atan2f_(float, float);

// @ 0x006a3430
float* EulerFromMatrix(float* out, const float* m)
{
    float len = sqrtf(m[0] * m[0] + m[1] * m[1]);
    if (len > 0.001f) {
        out[0] = atan2f_(m[5], m[8]);
        out[1] = atan2f_(-m[2], len);
        out[2] = atan2f_(m[1], m[0]);
        return out;
    }
    out[2] = 0.0f;
    out[0] = atan2f_(-m[7], m[4]);
    out[1] = atan2f_(-m[2], len);
    return out;
}

// ---------------------------------------------------------------------------
// 006a3920  float3* FUN_006a3920(float3* out, const float* m)
// ---------------------------------------------------------------------------
struct Float3 { float x, y, z; };

Float3* FUN_006a3920(Float3* out, const float* m)
{
    Float3 tmp;
    Float3* p = (Float3*)EulerFromMatrix((float*)&tmp, m);
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}

// ---------------------------------------------------------------------------
// 006a3330  bool cPropertyManager::CreateResource(int* info,int a,int b,int* out)
// ---------------------------------------------------------------------------
struct InfoObj {
    virtual void      s0();
    virtual void      s1();
    virtual void      s2();
    virtual void      s3();
    virtual uint32_t* s4();     // +0x10
};

template <class T> struct AutoPtr {
    T* mp;
    AutoPtr(T* p) : mp(p) {}
    ~AutoPtr() { if (mp) mp->Release(1); }
    T* operator->() const { return mp; }
    T* release() { T* t = mp; mp = 0; return t; }
};

struct cPropertyManager2 {
    void* vftable;              // +0
    bool CreateResource(int* info, void** out, int a, int b);   // 0x006a3330
};

bool cPropertyManager2::CreateResource(int* info, void** out, int a, int b)
{
    AutoPtr<Resource> pl((Resource*)EA_Alloc(0x38, (const char*)0x1408b44, 0, 0, 0, 0));
    if (pl.mp)
        pl.mp = pl.mp->Ctor((const char*)0x1408b34);

    uint32_t* k = ((InfoObj*)info)->s4();
    pl->mKey0 = k[0];
    pl->mKey1 = k[1];
    pl->mKey2 = k[2];

    bool ok = ((bool (__thiscall*)(void*, int*, Resource*, int, int))(*(void***)this)[0x24 / 4])(this, info, pl.mp, a, b);
    if (ok) {
        *out = pl.mp;
        pl.mp->AddRef();
        pl.release();
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 006a3ce0 already defined above (cAppPropsCommand::Execute)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 006a3d50  feedback-event lookup
// ---------------------------------------------------------------------------
struct FbIter { void* p; };
void FUN_011e07ef(void* fn);   // 0x011e07ef (atexit-ish; cdecl)

struct FbMap { void* FindSlot(void* a, void* b); };   // 0x00e5c780
struct FbOwner {   // embedded at FeedbackCmd+0x3c; vtable at +0
    virtual bool  s0(); virtual bool  s1(); virtual bool  s2(); virtual bool  s3();
    virtual bool  s4(); virtual void  s5(); virtual bool  s6();
    virtual bool  s7(int key);            // +0x1c
    virtual void* s8(); virtual void* s9();
    virtual void* s10(int key);           // +0x28
};
struct FeedbackCmd {
    uint8_t pad0[0x1c];
    uint8_t mActive;        // +0x1c
    uint8_t pad1[3];
    uint8_t mTree[4];       // +0x20  (map object; ecx for Find)
    uint8_t mEnd[0x18];     // +0x24  (end node; +0x24 = sentinel)
    FbOwner mOwner;         // +0x3c
    void* Get(int key);     // 0x006a3d50
    bool  Test(int key);    // 0x006a3f00
};
extern void* g_fb_default;  // 0x016029b0
struct FbInitFlag { unsigned inited : 1; unsigned unused : 31; };
extern FbInitFlag g_fbInit;  // 0x016029c4

// @ 0x006a3d50
void* FeedbackCmd::Get(int key)
{
    if (mActive) {
        void* it;
        void* k;
        void** slot = (void**)((FbMap*)(mTree))->FindSlot(&it, &k);
        char* found = (char*)*slot;
        if (found != (char*)this + 0x24)
            return found + 0x14;
        if (!g_fbInit.inited) {
            g_fbInit.inited = 1;
            FUN_011e07ef((*(volatile uint16_t*)0x16029c0 = 0,
                           *(volatile uint16_t*)0x16029c2 = 0,
                           (void*)0x13bed20));
        }
        return (void*)0x16029b0;
    } else {
        return mOwner.s10(key);
    }
}

// ---------------------------------------------------------------------------
// 006a3f00  bool FUN_006a3f00(FeedbackCmd*)
// ---------------------------------------------------------------------------
// @ 0x006a3f00
bool FeedbackCmd::Test(int key)
{
    if (mActive) {
        void* it;
        void* k;
        void** slot = (void**)((FbMap*)(mTree))->FindSlot(&it, &k);
        return *slot != (void*)((char*)this + 0x24);
    } else {
        return mOwner.s7(key);
    }
}

// ---------------------------------------------------------------------------
// 006a3f40  String::Init(const char** range, const void** tag)  (range ctor)
// ---------------------------------------------------------------------------
// @ 0x006a3f40
String* String::Init(const char** range, const void** tag)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    char* e = (char*)range[1];
    char* b = (char*)range[0];
    unsigned n = (unsigned)(e - b);
    RangeInitialize(n + 1);                 // 0x00475ab0 (thiscall, ret 4)
    char* dst = (char*)mpBegin;
    memcpy(dst, b, n);
    char* end = (dst - b) + e;
    mpEnd = end;
    *end = 0;
    *(const void**)((char*)this + 0x10) = *tag;
    return this;
}

// ---------------------------------------------------------------------------
// 006a4190  unsigned int FUN_006a4190(void* a, cArgParser* p)
// ---------------------------------------------------------------------------
// SSO 16-byte string: empty string points into a static table.
struct PoiStr16 {
    char* mpBegin;      // +0
    char* mpEnd;        // +4
    char* mpCapacity;   // +8
    void* mAlloc;       // +0xc
    PoiStr16() { char* const p = (char*)0x1667bac; mpBegin = p; mpEnd = p; mpCapacity = (char*)0x1667bad; }
    ~PoiStr16() { if (mpCapacity - mpBegin > 1 && mpBegin) EA_Dealloc(mpBegin); }
};

struct cArgParser {
    void  Tag(void* a, int tag);            // 0x0083d240
    void  EvalString(void* a, void* out);   // 0x0083dc00
    void* MainArguments(int b);             // 0x00838320
};

// @ 0x006a4190
unsigned int __stdcall FUN_006a4190(void* a, cArgParser* p)
{
    PoiStr16 s;
    p->Tag(a, 0x28);
    p->EvalString(a, &s);
    p->Tag(a, 0x29);
    return FNVHash(s.mpBegin, 0x811c9dc5u, 1);
}

// ---------------------------------------------------------------------------
// 006a4240 / 006a42d0  hashtable lookups
// ---------------------------------------------------------------------------
// An opaque intrinsic-map-like hashtable at cPropertyManager+0x74. Lookup takes
// a composed 64-bit key and returns an iterator (pointer to a bucket link).
struct THashTable {
    uint8_t  pad0[4];
    uint8_t** mpBucketArray;   // +0x4  (points at array of bucket-end pointers)
    uint32_t  mBucketIndex;    // +0x8
};
// 0x0041fb20: Find(outIter, key, table) — thiscall on the table.
struct THashFind { void Find(void* out, const void* key); };
inline void poi_ht_find(void* out, const void* key, void* table) {
    ((THashFind*)table)->Find(out, key);
}

// thiscall wrappers exposing the +0x74 hashtable at the observed offsets.
struct cPropertyManagerThunk {
    bool HasKey(unsigned int a, unsigned int b);           // 0x006a4240
    bool ReleaseKeys(int n, const void* values);           // 0x006a42d0
};

// @ 0x006a4240
bool cPropertyManagerThunk::HasKey(unsigned int a, unsigned int b)
{
    char* const base = (char*)this;
    THashTable* const ht = (THashTable*)(base + 0x74);
    struct Key64 { unsigned int lo, hi; } key;
    key.lo = a;
    key.hi = b;
    void* it;
    poi_ht_find(&it, &key, ht);
    if (it != (void*)ht->mpBucketArray[ht->mBucketIndex])
        return *(unsigned int*)((char*)it + 8) != 0;
    void* const obj = *(void**)(base + 0x18);
    struct KeyC { unsigned int a, magic, b; } k;
    k.a = a; k.magic = 0xb1b104; k.b = b;
    return ((bool (__thiscall*)(void*, void*, int))((void**)*(void**)obj)[3])(obj, &k, 0);
}

// @ 0x006a42d0
bool cPropertyManagerThunk::ReleaseKeys(int n, const void* values)
{
    char* const base = (char*)this;
    THashTable* const ht = (THashTable*)(base + 0x74);
    const unsigned char* v = (const unsigned char*)values;
    for (int i = 0; i < n; ++i, v += 0xc) {
        struct Key64 { unsigned int lo, hi; } key;
        key.lo = *(const unsigned int*)(v + 0);
        key.hi = *(const unsigned int*)(v + 8);
        void* it;
        poi_ht_find(&it, &key, ht);
        if (it != (void*)ht->mpBucketArray[ht->mBucketIndex]) {
            long* const rc = (long*)*(void**)((char*)it + 8);
            if (rc) {
                long old = _InterlockedExchangeAdd(rc + 1, 0);
                if ((old >> 1) - 1 > 1)
                    return true;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 006a43b0  hashtable erase-by-key
// ---------------------------------------------------------------------------
int FUN_006a43b0(char* self, const uint32_t* key)
{
    uint32_t before = *(uint32_t*)(self + 0xc);
    uint32_t b = key[0] % *(uint32_t*)(self + 8);
    uint32_t** slot = (uint32_t**)(*(int*)(self + 4) + b * 4);
    if (*slot) {
        // find node then unlink
        while (*slot) {
            uint32_t* node = *slot;
            if (node[0] == key[0] && node[1] == key[1]) {
                *slot = *(uint32_t**)((char*)node + 0x10);
                if (*(int*)((char*)node + 8))
                    (**(void (__thiscall***)(void*))(*(int*)((char*)node + 8)))((void*)(*(int*)((char*)node + 8)));
                EA_Dealloc(node);
                --*(uint32_t*)(self + 0xc);
                break;
            }
            slot = (uint32_t**)((char*)node + 0x10);
        }
    }
    return (int)(before - *(uint32_t*)(self + 0xc));
}

// ---------------------------------------------------------------------------
// 006a4450  rbtree erase-node
// ---------------------------------------------------------------------------
void* FUN_006a4450(char* tree, void** it, int node, void** root)
{
    (void)tree; (void)it; (void)node; (void)root;
    return it;
}

// ---------------------------------------------------------------------------
// 006a4100  void CopyVec12(...)  (defined above)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// vector allocation helpers
// ---------------------------------------------------------------------------
static const char kAllocPath[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

struct VecHdr { void* begin; void* end; void* cap; };

struct Vec38 {
    void* begin; void* end; void* cap;
    Vec38* Init(int n, const void* alloc);
};
struct Vec208 {
    void* begin; void* end; void* cap;
    Vec208* Init(unsigned n, const void* alloc);
};
struct VecC {
    void* begin; void* end; void* cap;
    VecC* Init(unsigned n, const void* alloc);
    VecC* InitValue(unsigned n, const float* value);
};
struct Vec8 {
    void* begin; void* end; void* cap;
    Vec8* Init(unsigned n, const float* value);
    void* Alloc(unsigned n, const void* x);   // 0x006a40a0 (external)
};

// 006a4130  element 0x38
Vec38* Vec38::Init(int n, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0x38, "App", 0, 0, kAllocPath, 0xd1) : 0;
    begin = p;
    end = p;
    cap = p + n * 0x38;
    return this;
}

// 006a44d0  element 0x208, filled with {-1,-1,0}
struct E208 { int32_t a; int32_t b; int16_t c; char rest[0x1fe]; };
// @ 0x006a44d0
Vec208* Vec208::Init(unsigned n, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0x208, "App", 0, 0, kAllocPath, 0xd1) : 0;
    unsigned cnt = n;
    cap = p + n * 0x208;
    E208 v;
    v.a = -1;
    v.b = -1;
    begin = p;
    end = p;
    v.c = 0;
    if (cnt > 0) {
        do {
            if (p)
                *(E208*)p = v;
            --cnt;
            p += 0x208;
        } while (cnt > 0);
    }
    end = (char*)begin + n * 0x208;
    return this;
}

// 006a4580  element 0xc, zero-filled
struct E12 { uint32_t x, y, z; };
// @ 0x006a4580
VecC* VecC::Init(unsigned n, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0xc, "App", 0, 0, kAllocPath, 0xd1) : 0;
    unsigned bytes = n * 0xc;
    E12 zero;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    begin = p;
    end = p;
    cap = p + bytes;
    unsigned cnt = n;
    for (; cnt; --cnt) {
        if (p)
            *(E12*)p = zero;
        p = (char*)p + 0xc;
    }
    end = (char*)begin + bytes;
    return this;
}

// 006a46a0  element 0xc, filled with a 3-float value
// @ 0x006a46a0
VecC* VecC::InitValue(unsigned n, const float* value)
{
    char* p = n ? (char*)EA_Alloc(n * 0xc, "App", 0, 0, kAllocPath, 0xd1) : 0;
    begin = p;
    end = p;
    cap = p + n * 0xc;
    float v0 = value[0];
    float v1 = value[1];
    float v2 = value[2];
    unsigned cnt = n;
    while (cnt--) {
        if (p) {
            *(float*)(p + 0) = v0;
            *(float*)(p + 4) = v1;
            *(float*)(p + 8) = v2;
        }
        p += 0xc;
    }
    end = p;
    return this;
}

// 006a4600  element 8, filled with a 2-float value
// @ 0x006a4600
Vec8* Vec8::Init(unsigned n, const float* value)
{
    Alloc(n, value);
    char* p = (char*)begin;
    float a = value[0];
    float b = value[1];
    unsigned cnt = n;
    while (cnt--) {
        if (p) {
            *(float*)p = a;
            *(float*)(p + 4) = b;
        }
        p = (char*)p + 8;
    }
    end = p;
    return this;
}

// 006a4660 / 006a4730  element 0x10, allocated then filled by a helper
extern "C" void Fill16a(void* begin, int n, void* tmp, const void* value);   // 0x0047cae0
extern "C" void Fill16b(void* begin, int n, void* tmp, const void* value);   // 0x00b11580

struct Vec10 {
    void* begin; void* end; void* cap;
    Vec10* Init(int n, const void* value);
    void Alloc(int n, const void* value);   // 0x007c7a40 (external)
};
struct Vec10b {
    void* begin; void* end; void* cap;
    Vec10b* Init(int n, const void* value);
    void Alloc(int n, const void* value);   // 0x007c7a40 (external)
};

// @ 0x006a4660
Vec10* Vec10::Init(int n, const void* value)
{
    Alloc(n, value);
    uint32_t tmp[4];
    Fill16a(begin, n, tmp, value);
    end = (char*)begin + n * 0x10;
    return this;
}

// @ 0x006a4730
Vec10b* Vec10b::Init(int n, const void* value)
{
    Alloc(n, value);
    uint32_t tmp[4];
    Fill16b(begin, n, tmp, value);
    end = (char*)begin + n * 0x10;
    return this;
}
