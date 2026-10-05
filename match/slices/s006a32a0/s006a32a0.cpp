// Slice s006a32a0 (part 1): EA::ArgScript command/property helpers.
// Module appears to be /O2, no frame pointer, /MD, /arch:SSE (float copies via
// x87 fld/fstp in a few places, SSE movss in others).
#include "s006a32a0.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
int cPropertyManager::Count()
{
    if (mVecBegin != mVecEnd)
        return (int)((mVecEnd - mVecBegin) >> 2);
    return 0;
}

// ---------------------------------------------------------------------------
// 006a39d0  bool cPropertyManager::GetAt(int idx, uint32_t* out)
// ---------------------------------------------------------------------------
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
void CopyVec12(void* dst, unsigned n, const void* src)
{
    while (n--) {
        if (dst) {
            *(float*)dst = *(const float*)src;
            *((float*)dst + 1) = *((const float*)src + 1);
            *((float*)dst + 2) = *((const float*)src + 2);
        }
        dst = (char*)dst + 0xc;
    }
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
    String& assign(const char* pBegin, const char* pEnd);
};

String& String::assign(const char* p)
{
    const char* q = p;
    while (*q)
        ++q;
    return assign(p, q);
}

// ---------------------------------------------------------------------------
// 006a3ac0  `anonymous_namespace'::cPropertyListCommand::Execute  (partial)
// 006a3c30  `anonymous_namespace'::cPropertyListCommand::OnEndParse (partial)
// 006a3dd0  property apply helper (partial)
// ---------------------------------------------------------------------------
void FUN_006a3ac0(void* args)
{
    (void)args;
}

void FUN_006a3c30(int b)
{
    (void)b;
}

void FUN_006a3dd0(int* p)
{
    (void)p;
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
// 006a3330  bool cPropertyManager::CreateResource(int* info,int a,int b,int out)
// ---------------------------------------------------------------------------
struct cPropertyList {
    void* vftable;           // +0
    void* mRef;              // +4
    uint32_t mKey0, mKey1, mKey2;  // +8,0xc,0x10
    uint8_t pad[0x20];       // +0x14
    void* vfn0_idx;          // placeholder
    cPropertyList* Ctor(const char* name);
    void Release(int);
    void AddRef();
};

struct cPropertyManager2 {
    void* vftable;              // +0
    void* mBase;                // +4
    uint8_t pad[0x20];          // +8
    void* mFactoryVt;           // +0x24 area
    bool CreateResource(int* info, int a, int b, int* out);
};

bool cPropertyManager2::CreateResource(int* info, int a, int b, int* out)
{
    cPropertyList* pl = (cPropertyList*)EA_Alloc(0x38, "App/PropertyList/Create", 0, 0, 0, 0);
    if (pl)
        pl = pl->Ctor("CreateResource");

    uint32_t* k = (uint32_t*)((int* (*)(int*))((void**)info)[0x10 / 4])(info);
    pl->mKey0 = k[0];
    pl->mKey1 = k[1];
    pl->mKey2 = k[2];

    bool ok = ((bool (__thiscall*)(void*, int*, void*, int, int))(((void**)this)[0x24 / 4]))(this, info, pl, a, b);
    if (ok) {
        *out = (int)pl;
        pl->AddRef();
        return true;
    }
    pl->Release(1);
    return false;
}

// ---------------------------------------------------------------------------
// 006a3ce0 already defined above (cAppPropsCommand::Execute)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 006a3d50  feedback-event lookup
// ---------------------------------------------------------------------------
struct FeedbackCmd {
    uint8_t pad0[0x1c];
    uint8_t mActive;        // +0x1c
    uint8_t pad1[3];
    uint8_t mMap[0x20];     // +0x20  (rbtree)
    void*   mEnd;           // +0x40 ... approx
};

void* FUN_006a3d50(FeedbackCmd* self)
{
    if (!self->mActive)
        return ((void* (__thiscall*)(void*))((void**)*(void**)((char*)self + 0x3c))[0x28 / 4])((char*)self + 0x3c);
    // rbtree find + atexit fallback
    extern void* g_feedbackFallback;
    return g_feedbackFallback;
}

// ---------------------------------------------------------------------------
// 006a3f00  bool FUN_006a3f00(FeedbackCmd*)
// ---------------------------------------------------------------------------
bool FUN_006a3f00(FeedbackCmd* self)
{
    if (self->mActive)
        return true;    // replaced by real rbtree test in matching version
    return ((bool (__thiscall*)(void*))((void**)*(void**)((char*)self + 0x3c))[0x1c / 4])((char*)self + 0x3c);
}

// ---------------------------------------------------------------------------
// 006a3f40  String-range constructor
// ---------------------------------------------------------------------------
void FUN_006a3f40(String* self, const char** range, const void* tag)
{
    self->mpBegin = 0;
    self->mpEnd = 0;
    self->mpCapacity = 0;
    const char* b = range[0];
    const char* e = range[1];
    unsigned n = (unsigned)(e - b);
    ((void (__thiscall*)(String*, unsigned))0x00475ab0)(self, n + 1);  // RangeInitialize
    char* dst = (char*)self->mpBegin;
    memcpy(dst, b, n);
    self->mpEnd = dst + n;
    dst[n] = 0;
    *(const void**)((char*)self + 0x10) = tag;
}

// ---------------------------------------------------------------------------
// 006a4190  unsigned int FUN_006a4190(...)
// ---------------------------------------------------------------------------
uint32_t FUN_006a4190(void* parser)
{
    static char buf[0x10];
    char* s = buf;
    // EvalString(parser, string) then hash
    StringEvalString(parser, s);
    return FNVHash(s, 0x811c9dc5u, 1);
}

// ---------------------------------------------------------------------------
// 006a4240 / 006a42d0  hashtable lookups
// ---------------------------------------------------------------------------
bool FUN_006a4240(cPropertyManager* self, int a, int b)
{
    (void)self; (void)a; (void)b;
    return false;
}

bool FUN_006a42d0(cPropertyManager* self, int n, const void* values)
{
    (void)self; (void)n; (void)values;
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
    VecC* InitValue(unsigned n, const float* value, const void* alloc);
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

// 006a44d0  element 0x208, filled with {-1,0,...}
struct E208 { uint32_t a; uint32_t b; uint32_t rest[0x80]; };
Vec208* Vec208::Init(unsigned n, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0x208, "App", 0, 0, kAllocPath, 0xd1) : 0;
    unsigned bytes = n * 0x208;
    cap = p + bytes;
    E208 v;
    v.a = 0xffffffff;
    v.b = 0;
    begin = p;
    end = p;
    unsigned cnt = n;
    if (cnt > 0) {
        do {
            if (p)
                *(E208*)p = v;
            p += 0x208;
        } while (--cnt);
    }
    end = (char*)begin + bytes;
    return this;
}

// 006a4580  element 0xc, zero-filled
struct E12 { uint32_t x, y, z; };
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
VecC* VecC::InitValue(unsigned n, const float* value, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0xc, "App", 0, 0, kAllocPath, 0xd1) : 0;
    begin = p;
    cap = p + n * 0xc;
    for (int i = 0; i < n; i++) {
        *(float*)(p + i * 0xc) = value[0];
        *(float*)(p + i * 0xc + 4) = value[1];
        *(float*)(p + i * 0xc + 8) = value[2];
    }
    end = p + n * 0xc;
    return this;
}

// 006a4600  element 8, filled with a 2-float value
Vec8* Vec8::Init(unsigned n, const float* value)
{
    Alloc(n, value);
    char* p = (char*)begin;
    float a = value[0];
    float b = value[1];
    unsigned cnt = n;
    while (cnt--) {
        if (p) {
            *(float*)p = b;
            *(float*)(p + 4) = a;
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

Vec10* Vec10::Init(int n, const void* value)
{
    Alloc(n, value);
    uint32_t tmp[4];
    Fill16a(begin, n, tmp, value);
    end = (char*)begin + n * 0x10;
    return this;
}

Vec10b* Vec10b::Init(int n, const void* value)
{
    Alloc(n, value);
    uint32_t tmp[4];
    Fill16b(begin, n, tmp, value);
    end = (char*)begin + n * 0x10;
    return this;
}
