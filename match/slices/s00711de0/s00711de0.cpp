// Slice s00711de0: SP::cMaterialManager map accessors (mutex + hash_map operator[] wrappers),
// the hash_map operator[] itself, serialization/list helpers and a fixed-vector copy ctor.
// /O2 /MD /Gy /EHsc /TP /GS-
#include <new>
#include <intrin.h>
#include "types.h"

void __cdecl EastlFree(void* p);                     // 0xF47380
void* __cdecl EastlNew(uint32_t n, const char* name, int flags, int dbg, const char* file, int line); // 0xF473A0
void __cdecl DoFreeNodesStr(void* pBegin, uint32_t n); // 0x6A85B0
struct VecBase24 {
    void DestroyRange(void** first, void** last);       // 0x70F520 (thiscall, pops 8)
};

// Thread mutex (EA::Thread::Mutex): lock/unlock are out-of-line in the image.
struct Mutex {
    char mData[0x40];
    void Lock(const void* pTimeout);       // 0x9221B0
    void Unlock();                          // 0x922270
};
extern char g_mutexParams;                  // DAT_0140C860 (relocated constant passed to Lock)

// RAII lock: the source keeps the mutex pointer in a local and unlocks in its destructor,
// which is what produces the shared EH frame (LAB_0120cf58) in the original.
struct MutexLock {
    Mutex* mpMutex;
    MutexLock(Mutex& m, const void* pTimeout) : mpMutex(&m) { m.Lock(pTimeout); }
    ~MutexLock() { mpMutex->Unlock(); }
};

// ---------------------------------------------------------------------------------------------
// hash_map<uint32_t, cMaterialInternal> accessors
// ---------------------------------------------------------------------------------------------
struct MatMap {
    char mData[0x40];                       // +0x174 in the manager
    uint8_t& operator[](const uint32_t& key);   // 0x7129E0
};

struct MaterialManager3 {
    char pad0[0x174];
    MatMap mMap;                            // +0x174
    void* mpInvalidState;                   // +0x1b4
    char pad1[0x258 - 0x1b8];
    Mutex mMutex;                           // +0x258

    bool HasMaterial(uint32_t key);
    uint8_t* GetMaterial(uint32_t key);
    void GetMaterials(int32_t n, const uint32_t* keys, void** out);
    uint8_t* GetMaterialInstance(uint32_t key, void* param3);
};

// @ 0x00712BA0
bool MaterialManager3::HasMaterial(uint32_t key)
{
    MutexLock lock(mMutex, &g_mutexParams);
    return mMap[key] != 0;
}

// @ 0x00712C20
uint8_t* MaterialManager3::GetMaterial(uint32_t key)
{
    MutexLock lock(mMutex, &g_mutexParams);
    uint8_t* p = &mMap[key];
    if (*p == 0) {
        *(uint32_t*)(p + 0x18) = key;
        void* invalid = mpInvalidState;
        if (*(void**)(p + 4) != invalid)
            *(void**)(p + 4) = invalid;
    }
    return p;
}

// @ 0x00712CB0
void MaterialManager3::GetMaterials(int32_t n, const uint32_t* keys, void** out)
{
    MutexLock lock(mMutex, &g_mutexParams);
    if (n > 0) {
        intptr_t delta = (intptr_t)((char*)out - (char*)keys);
        do {
            uint8_t* p = &mMap[*keys];
            if (*p == 0) {
                *(uint32_t*)(p + 0x18) = *keys;
                void* invalid = mpInvalidState;
                if (*(void**)(p + 4) != invalid)
                    *(void**)(p + 4) = invalid;
            }
            *(void**)((char*)keys + delta) = p;
            ++keys;
            --n;
        } while (n != 0);
    }
}

// @ 0x00712D60
uint8_t* MaterialManager3::GetMaterialInstance(uint32_t key, void* param3)
{
    if (param3 == 0) {
        MutexLock lock(mMutex, &g_mutexParams);
        uint8_t* p = &mMap[key];
        if (*p == 0) {
            *(uint32_t*)(p + 0x18) = key;
            void* invalid = mpInvalidState;
            if (*(void**)(p + 4) != invalid)
                *(void**)(p + 4) = invalid;
        }
        return p;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// fixed-vector copy ctors for cMaterialScriptState-like objects
// ---------------------------------------------------------------------------------------------
struct TailVec {
    void* mpBegin;         // +0x00
    void* mpEnd;           // +0x04
    void* mpCapacity;      // +0x08
    char pad0[4];          // +0x0c
    void* mpPoolBegin;     // +0x10
    char pad1[4];          // +0x14
    char mBuffer[16];      // +0x18 inline elements (4 x 4 bytes)
    __declspec(noinline) TailVec(const TailVec& src);
    void assign(void* first, void* last, const TailVec* src);  // 0x7106D0 (thiscall, ret 0xc)
};

// @ 0x00712760
TailVec::TailVec(const TailVec& src)
{
    void* buf = mBuffer;
    mpBegin = buf;
    mpEnd = buf;
    mpCapacity = (char*)buf + 16;
    mpPoolBegin = buf;
    assign(src.mpBegin, src.mpEnd, &src);
}

// @ 0x007127D0
struct State27D0 {
    uint32_t m0[9];        // +0x00
    TailVec mVec;          // +0x24
    State27D0* CopyFrom(const State27D0& src);
};

State27D0* State27D0::CopyFrom(const State27D0& src)
{
    for (int i = 0; i < 9; ++i)
        m0[i] = src.m0[i];
    ::new (&mVec) TailVec(src.mVec);
    return this;
}

// @ 0x00712850
struct State2850 {
    uint32_t m0[9];        // +0x00
    TailVec mVec;          // +0x24
    State2850* CopyFrom2(const State2850& a, const State2850& b);
};

State2850* State2850::CopyFrom2(const State2850& a, const State2850& b)
{
    m0[0] = a.m0[0];
    for (int i = 1; i < 9; ++i)
        m0[i] = b.m0[i - 1];
    // the original hands the ctor the address of b.m0[8] (one word before b.mVec)
    const TailVec* srcVec = (const TailVec*)&b.m0[8];
    ::new (&mVec) TailVec(*srcVec);
    return this;
}

// ---------------------------------------------------------------------------------------------
// remaining cMaterialManager machinery (partial reconstructions)
// ---------------------------------------------------------------------------------------------
static inline long AtomicAdd(volatile long* p, long v) { return _InterlockedExchangeAdd(p, v); }

struct IFileParserW {                 // object at manager+0xc (vtable slots 1 and 3)
    virtual void f0();
    virtual void Release();           // +0x04
    virtual void f2();
    virtual void Flush();             // +0x0c
};
struct FixedClear { void clear(); };  // 0x00711380 (thiscall)

void FUN_006fd7a0();                  // 0x006fd7a0 (cdecl)
void __cdecl FUN_006ff680(int i);     // 0x006ff680
void __cdecl ClearPSFragment(int i);  // 0x006fc6a0

struct MaterialManagerBig2 {
    char pad00[0x0c];
    IFileParserW* mpFileParser;   // +0x0c
    char pad10[4];
    char* mpInvalidTexture;       // +0x14 (cTextureInstance; refcount at +8)
    char pad18[0x174 - 0x18];
    MatMap mMap;             // +0x174 (bucket/anchor storage; +0x180 == mMap+0xc)
    char* mpInvalidState;    // +0x1b4
    FixedClear mFixed;       // +0x1b8
    char pad1b9[0x200 - 0x1b9];
    int32_t mCount;          // +0x200
    char pad204[0x258 - 0x204];
    Mutex mMutex;            // +0x258

    uint8_t ReadMaterials1184(void* stream);
    bool Shutdown();
    bool Update2670();
    void Update();
    void RemoveAllRegistered();
    void RemoveAllRegisteredMaterials();   // 0x00711d10 (thiscall)
    void UnregisterArenaContents(void* arena);
};

// ---- out-of-slice callees used by Update2670 ----
namespace SP { struct cDirectPropertyList { int GetIntProperty(uint32_t key) const; }; } // 0x6a2660
extern "C" SP::cDirectPropertyList* g_sAppProps;                 // 0x15fd918 (_sAppProperties)
extern "C" uint32_t g_1535f60;                                 // 0x1535f60
extern "C" void*    GetManager67dcd0();                        // 0x67dcd0
extern "C" void     FUN_006fd7b0();                            // 0x6fd7b0
extern "C" int      FUN_006bb1c0(const char* msg, int a, int b, int c); // 0x6bb1c0

// ---- out-of-slice callees used by ReadMaterials1184 (addresses from the image) ----
extern "C" bool   FUN_006e54c0(void* p);                                  // 0x6E54C0 add-ref/release
extern "C" bool   FUN_006e57a0(void* p);                                  // 0x6E57A0 ShaderState_Release
extern "C" void   FUN_006e5bd0(void* p);                                  // 0x6E5BD0 ShaderState::Reset
extern "C" void*  FUN_006e57d0();                                         // 0x6E57D0 ShaderState ctor
extern "C" bool   FUN_006e5d50(void* obj, uint32_t a, uint32_t b);        // 0x6E5D50
extern "C" void*  FUN_006fd280();                                         // 0x6FD280 shader-array ctor
extern "C" bool   FUN_006fd300(void* p);                                  // 0x6FD300 refcount release
extern "C" bool   FUN_006fd5d0(void* obj, uint32_t a, uint32_t b);        // 0x6FD5D0
extern "C" void   FUN_006ff3f0(void* stream);                             // 0x6FF3F0
extern "C" void   FUN_006fc1f0(void* stream);                             // 0x6FC1F0 ReadShaderCache
extern "C" void   FUN_00711070(void* self);                               // 0x711070 VecResizeA::resize
extern "C" void   FUN_007110f0(void* self);                               // 0x7110F0 VecResizeB::resize
extern "C" void   FUN_0070fa60(void* begin, void* end);                   // 0x70FA60 VecA::Shrink
extern "C" void   FUN_0093a6c0(void* a, const void* b, uint32_t n);       // 0x93A6C0 write blob
extern "C" void   FUN_0093a780(void* a, void* b, uint32_t n, int flags);  // 0x93A780 read blob
void* __cdecl    FUN_00f473a0(uint32_t n, const char* name, int a, int b, const char* file, int c);
extern "C" void   FUN_0047bf30(void* str, uint32_t n, char c);            // string::resize
extern "C" void*  memmove(void*, const void*, unsigned int);
extern "C" uint32_t g_1535f6c;                                            // 0x1535F6C

typedef void (__thiscall *IOReadFn)(void* obj, void* out, int n, int flags);
typedef void* (__thiscall *HashFindFn)(void* ht, void* out, const uint32_t* key);
typedef void* (__thiscall *MapIndexFn)(void* map, const uint32_t* key);

// @ 0x00711DE0
uint8_t MaterialManagerBig2::ReadMaterials1184(void* stream)
{
    char* const self = (char*)this;
    MutexLock lock(mMutex, &g_mutexParams);

    uint8_t ok = 1;

    // Ask the stream to resolve { mCount, serTag, 0x1535F6C } and hand back the reader object.
    uint32_t key[3];
    key[0] = *(uint32_t*)(self + 0x200);
    key[1] = 0x0469a3f7u;
    key[2] = g_1535f6c;
    void* reader = 0;
    uint32_t tag = 0;
    if (!((bool (__thiscall*)(void*, uint32_t*, void**, int))
              *(void**)(*(char**)stream + 0x34))(stream, key, &reader, 1))
        return 0;

    // vtable+0x18 opens the IO channel; all reads go through 0x93A780(obj, &dst, 1, 0)
    char* io = (char*)((void* (__thiscall*)(void*))*(void**)(*(char**)stream + 0x18))(stream);
    uint32_t version = 0;
    FUN_0093a780(io, &version, 1, 0);
    if (version - 6 > 1u) {
        if (stream) ((void (__thiscall*)(void*))*(void**)(*(char**)stream + 8))(stream);
        return 0;
    }

    // ---- type table ----
    char* typeVec = self + 0x98;
    char* typeMap = self + 0xcc;
    FUN_0070fa60(*(void**)(self + 0x98), *(void**)(self + 0x9c));
    uint32_t nTypes = 0;
    FUN_0093a780(io, &nTypes, 1, 0);
    FUN_00711070(typeVec);
    int typeCount = (int)((*(uint32_t*)(self + 0x9c) - *(uint32_t*)(self + 0x98)) >> 2);
    for (int i = 0; i < typeCount; ++i) {
        uint32_t id = 0;
        FUN_0093a780(io, &id, 1, 0);
        void* it[2];
        ((HashFindFn)0x00645ed0)(typeMap, it, &id);
        char* obj;
        if (it[0] == *(void**)(*(char**)(typeMap + 4) + *(int*)(typeMap + 8) * 4)) {
            obj = (char*)FUN_00f473a0(0x348, "Graphics", 0, 0, 0, 0);
            obj = obj ? (char*)FUN_006e57d0() : 0;
            if (id < 0x70000000u || (int)id < 0) {
                void** slot = (void**)((MapIndexFn)0x007101f0)(typeMap, &id);
                char* prev = (char*)*slot;
                if (obj != prev) {
                    if (obj) FUN_006e54c0(obj);
                    *slot = obj;
                    if (prev) FUN_006e57a0(prev);
                }
            }
        } else {
            obj = *(char**)((char*)it[0] + 4);
            FUN_006e5bd0(obj);
        }
        if (!FUN_006e5d50(obj, key[1], version))
            ok = 0;
        char** arr = *(char***)typeVec;
        char* old = arr[i];
        if (obj != old) {
            if (obj) FUN_006e54c0(obj);
            arr[i] = obj;
            if (old) FUN_006e57a0(old);
        }
        FUN_006e57a0(obj);
    }

    // ---- instance table ----
    char* instVec = self + 0xec;
    char* instMap = self + 0x100;
    uint32_t nInst = 0;
    FUN_0093a780(io, &nInst, 1, 0);
    FUN_007110f0(instVec);
    int instCount = (int)((*(uint32_t*)(self + 0xf0) - *(uint32_t*)(self + 0xec)) >> 2);
    for (int i = 0; i < instCount; ++i) {
        uint32_t id = 0;
        FUN_0093a780(io, &id, 1, 0);
        void* it[2];
        ((HashFindFn)0x00645ed0)(instMap, it, &id);
        char* obj;
        if (it[0] == *(void**)(*(char**)(instMap + 4) + *(int*)(instMap + 8) * 4)) {
            obj = (char*)FUN_00f473a0(0x2c8, "Graphics", 0, 0, 0, 0);
            obj = obj ? (char*)FUN_006fd280() : 0;
            if (id < 0x70000000u || (int)id < 0) {
                void** slot = (void**)((MapIndexFn)0x007102b0)(instMap, &id);
                char* prev = (char*)*slot;
                if (obj != prev) {
                    if (obj) FUN_006e54c0(obj);
                    *slot = obj;
                    if (prev) FUN_006fd300(prev);
                }
            }
        } else {
            obj = *(char**)((char*)it[0] + 4);
        }
        if (!FUN_006fd5d0(obj, key[1], version))
            ok = 0;
        char** arr = *(char***)instVec;
        char* old = arr[i];
        if (obj != old) {
            if (obj) FUN_006e54c0(obj);
            arr[i] = obj;
            if (old) FUN_006fd300(old);
        }
        FUN_006fd300(obj);
    }

    FUN_006ff3f0(stream);
    FUN_006fc1f0(stream);

    // ---- trailing shader-cache blob (version > 3) ----
    if (version > 3) {
        uint32_t len = 0;
        FUN_0093a780(io, &len, 1, 0);
        char** str = (char**)(self + 0x120);
        char* end = str[1];
        uint32_t cur = (uint32_t)(end - str[0]);
        if (len < cur) {
            char* dst = str[0] + len;
            if (dst != end) {
                memmove(dst, end, (size_t)((end - end) + 1));
                str[1] += dst - end;
            }
        } else if (len > cur) {
            FUN_0047bf30(str, len - cur, 0);
        }
        FUN_0093a6c0(io, str[0], (uint32_t)(str[1] - str[0]));
    }

    if (stream)
        ((void (__thiscall*)(void*))*(void**)(*(char**)stream + 0x24))(stream);
    return ok;
}

// @ 0x007123A0
bool MaterialManagerBig2::Shutdown()
{
    RemoveAllRegisteredMaterials();
    mFixed.clear();
    if (mpFileParser) {
        mpFileParser->Flush();
        if (mpFileParser) {
            IFileParserW* p = mpFileParser;
            mpFileParser = 0;
            p->Release();
        }
    }
    if (mpInvalidTexture) {
        volatile long* rc = (volatile long*)(mpInvalidTexture + 8);
        mpInvalidTexture = 0;
        AtomicAdd(rc, -1);
        long cur = AtomicAdd(rc, 0);
        if (cur < 1)
            AtomicAdd(rc, 1);
        else
            AtomicAdd(rc, 0);
    }
    FUN_006fd7a0();
    for (int i = 1; i < 0x100; ++i)
        FUN_006ff680(i);
    for (int i = 1; i < 0x100; ++i)
        ClearPSFragment(i);
    return true;
}

// @ 0x00712670
bool MaterialManagerBig2::Update2670()
{
    SP::cDirectPropertyList* props = g_sAppProps;
    int a = props->GetIntProperty(0x1a34e253u);
    int b = props->GetIntProperty(0xe1408308u);
    mCount = (b < 0 || a <= b) ? a : b;

    bool ok = false;

    if (*(void**)((char*)this + 0x180) != 0) {
        RemoveAllRegisteredMaterials();
        FUN_006fd7b0();
    }

    struct PkgKey { uint32_t a; uint32_t b; uint32_t c; };
    PkgKey key;
    key.a = (uint32_t)mCount;
    key.b = 0x469a3f7u;
    key.c = g_1535f60;

    void* mgr = GetManager67dcd0();
    void* res = ((void* (__thiscall*)(void*, void*))*(void**)(*(char**)mgr + 0x58))(mgr, &key);
    if (res != 0) {
        bool v80 = ((bool (__thiscall*)(void*, void*))*(void**)(*(char**)this + 0x80))(this, res);
        bool v78 = ((bool (__thiscall*)(void*, void*))*(void**)(*(char**)this + 0x78))(this, res);
        ok = (v78 && v80) ? true : false;
        bool v7c = ((bool (__thiscall*)(void*, void*))*(void**)(*(char**)this + 0x7c))(this, res);
        if (v7c && ok)
            return true;
    }

    ok = false;
    FUN_006bb1c0("Could not find a needed package.\n\nThe data directory is missing or corrupt.",
                 0x3ec, 1, 0);
    return ok;
}

// ---- out-of-slice callees used by Update (addresses taken from the image) ----
typedef long long (__thiscall *StopwatchElapsedFn)(void* self);          // 0x0093A3A0
typedef void      (__cdecl    *ShaderSetFn)(int id, const void* value, int flags); // 0x00777AE0
typedef void*     (__cdecl    *GetManagerFn)(void);                      // 0x0067DD50
typedef void      (__thiscall *SetRasterFn)(void* state, int index, void* raster); // 0x011EE6B0
typedef void      (__thiscall *VecResizeFn)(void* self, uint32_t n);     // 0x00712280
typedef bool      (__thiscall *IsBusyFn)(void* self);                    // vtable slot 0x28

// @ 0x00712450
void MaterialManagerBig2::Update()
{
    char* const self = (char*)this;

    // frame timing / shader constants
    long long ticks = ((StopwatchElapsedFn)0x0093A3A0)(self + 0x208);
    uint32_t frame = *(uint32_t*)(self + 0x220);
    *(uint32_t*)(self + 0x228) = frame;
    *(uint32_t*)(self + 0x220) = frame + 1;
    *(float*)(self + 0x224) = (float)ticks * *(float*)(self + 0x21c);
    ((ShaderSetFn)0x00777AE0)(0x203, self + 0x224, 0);
    ((ShaderSetFn)0x00777AE0)(0x256, (const void*)1, 0);

    void* mgr = ((GetManagerFn)0x0067DD50)();
    int* dims = (int*)((void* (__thiscall*)(void*))*(void**)(*(char**)mgr + 0x1c))(mgr);
    *(float*)(self + 0x22c) = (float)dims[0];
    *(float*)(self + 0x230) = (float)dims[1];
    float fx = *(float*)(self + 0x22c);
    float fy = *(float*)(self + 0x230);
    *(float*)(self + 0x234) = (fx <= 0.0f) ? 0.0f : 1.0f / fx;
    *(float*)(self + 0x238) = (fy <= 0.0f) ? 0.0f : 1.0f / fy;
    ((ShaderSetFn)0x00777AE0)(0x204, self + 0x22c, 0);

    // walk the registered materials, refresh the rasters of the live ones and compact the vector
    int n = (*(int32_t*)(self + 0x248) - *(int32_t*)(self + 0x244)) >> 2;
    int keep = 0;
    for (int i = 0; i < n; ++i) {
        char* mat = (char*)(*(void***)(self + 0x244))[i];
        int nTex = (*(int32_t*)(mat + 0x24) - *(int32_t*)(mat + 0x20)) >> 2;
        bool stale = false;
        for (int j = 0; j < nTex; ++j) {
            char* tex = (char*)(*(void***)(mat + 0x20))[j];
            if (tex != 0) {
                if ((*(uint8_t*)(tex + 4) & 1) == 0)
                    stale = true;
                else
                    ((SetRasterFn)0x011EE6B0)(*(void**)(mat + 4), j, *(void**)tex);
            }
        }
        if (stale) {
            if (keep < i) {
                void** v = *(void***)(self + 0x244);
                char* src = (char*)v[i];
                char* dst = (char*)v[keep];
                if (src != dst) {
                    if (src != 0)
                        ++*(int*)(src + 0x14);
                    v[keep] = src;
                    if (dst != 0 && *(int*)(dst + 0x14) > 1)
                        --*(int*)(dst + 0x14);
                }
            }
            ++keep;
        }
    }
    ((VecResizeFn)0x00712280)(self + 0x244, (uint32_t)keep);

    // only re-create the material state when the configured budget changed
    SP::cDirectPropertyList* props = g_sAppProps;
    int a = props->GetIntProperty(0x1a34e253u);
    int b = props->GetIntProperty(0xe1408308u);
    if (b >= 0 && a > b)
        a = b;

    if (*(int*)(self + 0x200) == a) {
        void* parser = *(void**)(self + 0xc);
        if (parser == 0 || !((IsBusyFn)*(void**)(*(char**)parser + 0x28))(parser))
            return;
    }
    ((void (__thiscall*)(void*))*(void**)(*(char**)this + 0x1c))(this);
}

// @ 0x00711B80
void MaterialManagerBig2::UnregisterArenaContents(void* arena)
{
    (void)arena;
}

// ---------------------------------------------------------------------------------------------
// eastl::vector<AutoRefCount<cMaterialInternal>>::resize(n)  (0x00712280)
// ---------------------------------------------------------------------------------------------
struct ARefMat {                       // EA::AutoRefCount<cMaterialInternal>
    void* mpObject;
    ARefMat() : mpObject(0) {}
    ~ARefMat() { if (mpObject) ((IFileParserW*)mpObject)->Release(); }
};
void** __cdecl AssignWeak14(void** first, void** last, void** dest);   // 0x0070ebf0 (copy of the tail down over the erased range)

struct MatRefVec {
    void** mpBegin;                    // +0
    void** mpEnd;                      // +4
    void** mpCapacity;                 // +8
    void DoInsertValues(void** pos, uint32_t n, const ARefMat& value);   // 0x00710510 (thiscall, ret 0xc)
    void RangeWeakRelease(void** first, void** last);   // 0x0070e890 (thiscall, ret 8; releases the vacated range)
    void resize(uint32_t n);
};

// @ 0x00712280
void MatRefVec::resize(uint32_t n)
{
    void** pEnd = mpEnd;
    uint32_t nSize = (uint32_t)(pEnd - mpBegin);
    if (n > nSize) {
        const ARefMat zero;
        DoInsertValues(pEnd, n - nSize, zero);
    } else {
        void** first = mpBegin + n;
        void** pos = AssignWeak14(pEnd, pEnd, first);
        RangeWeakRelease(pos, mpEnd);
        mpEnd -= (pEnd - first);
    }
}

// ---------------------------------------------------------------------------------------------
// hashtable node free helpers for two more hashtable instantiations
// ---------------------------------------------------------------------------------------------
struct FreeNode24 {
    int32_t m00;           // +0x00
    char pad0[0x24 - 0x04];
    void* mpBegin;         // +0x24
    void* mpEnd;           // +0x28
    char pad1[0x34 - 0x2c];
    void* mpCapacity;      // +0x34
    char pad2[0x4c - 0x38];
    FreeNode24* mpNext;    // +0x4c
};

// @ 0x00712320
void __stdcall DoFreeNodes24(FreeNode24** pArray, uint32_t n)
{
    uint32_t result;
    __asm { mov result, eax }          // the empty-range path returns the caller's eax unchanged
    if (n != 0) {
        for (uint32_t i = 0; i < n; ++i) {
            FreeNode24* node = pArray[i];
            while (node) {
                FreeNode24* next = node->mpNext;
                VecBase24* vec = (VecBase24*)((char*)node + 0x24);
                vec->DestroyRange((void**)node->mpBegin, (void**)node->mpEnd);
                if (node->mpBegin != 0 && node->mpBegin != node->mpCapacity)
                    EastlFree(node->mpBegin);
                EastlFree(node);
                node = next;
            }
            pArray[i] = 0;
        }
        result = (uint32_t)pArray;     // the original's final store leaves pArray in eax
    }
    __asm { mov eax, result }
}

// A hashtable<string,...> object embedded in a node; its node/bucket free helper is out-of-line.
struct HashStr {
    char pad0[4];
    uint32_t* mpBucketArray;   // +0x04 (relative to the embedded object)
    uint32_t mnBucketCount;    // +0x08
    uint32_t mnElementCount;   // +0x0c
    void DoFreeNodes(uint32_t* pNodes, uint32_t n);   // 0x6A85B0
};

struct FreeNodeStr {
    int32_t m00;           // +0x00
    char pad0[0x24 - 0x04];
    FreeNodeStr* mpNext;   // +0x24
    // The embedded string hashtable lives at +0x04:
    //   +0x08 bucket array, +0x0c bucket count, +0x10 element count
};

// @ 0x00712B20
void __stdcall DoFreeNodesStr2(FreeNodeStr** pArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        FreeNodeStr* node = pArray[i];
        while (node) {
            FreeNodeStr* next = node->mpNext;
            HashStr* h = (HashStr*)((char*)node + 4);
            h->DoFreeNodes(h->mpBucketArray, h->mnBucketCount);
            h->mnElementCount = 0;
            if (h->mnBucketCount > 1)
                EastlFree(h->mpBucketArray);
            EastlFree(node);
            node = next;
        }
        pArray[i] = 0;
    }
}

// NOTE: hash_map<uint32_t, cMaterialInternal>::operator[] (0x007129E0) is implemented in
// s00711de0_map.cpp.  It must stay out of this TU: cl's nothrow analysis would otherwise
// remove the exception frames from the accessors above (which are byte-exact).
