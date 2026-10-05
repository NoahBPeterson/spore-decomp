// Slice s00711de0: SP::cMaterialManager map accessors (mutex + hash_map operator[] wrappers),
// the hash_map operator[] itself, serialization/list helpers and a fixed-vector copy ctor.
// /O2 /MD /Gy /EHsc /TP /GS-
#include <new>
#include "types.h"

void __cdecl EastlFree(void* p);                     // 0xF47380
void* __cdecl EastlNew(uint32_t n, const char* name, int flags, int dbg, const char* file, int line); // 0xF473A0
void __cdecl DoFreeNodesStr(void* pBegin, uint32_t n); // 0x6A85B0
void __cdecl AssignRange(void* first, void* last, const void* tag); // 0x7106D0
void __cdecl DestroyRange(void* first, void* last);     // 0x70F520

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
    char mBuffer[16];      // +0x14 inline elements (4 x 4 bytes)
    TailVec(const TailVec& src);
};

// @ 0x00712760
TailVec::TailVec(const TailVec& src)
{
    void* buf = mBuffer;
    mpBegin = buf;
    mpEnd = buf;
    mpCapacity = (char*)buf + 16;
    mpPoolBegin = buf;
    AssignRange(*(void**)&src.mpBegin, *(void**)&src.mpEnd, 0);
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
    ::new (&mVec) TailVec(b.mVec);
    return this;
}

// ---------------------------------------------------------------------------------------------
// remaining cMaterialManager machinery (partial reconstructions)
// ---------------------------------------------------------------------------------------------
struct MaterialManagerBig2 {
    char pad0[0x174];
    MatMap mMap;             // +0x174
    char pad1[0x40];
    void* mpInvalidState;    // +0x1b4
    char pad2[0x258 - 0x1b8];
    Mutex mMutex;            // +0x258
    char pad3[0x200];
    int32_t mCount;          // +0x200 (approx)

    void ReadMaterials1184(void* stream, int32_t n, uint32_t* ids, void* a, void* b);
    void Shutdown();
    void Update2670();
    void RemoveAllRegistered();
    void UnregisterArenaContents(void* arena);
};

// @ 0x00711DE0
void MaterialManagerBig2::ReadMaterials1184(void* stream, int32_t n, uint32_t* ids, void* a, void* b)
{
    // Large serialization entry; guarded by mMutex.
    mMutex.Lock(&g_mutexParams);
    (void)stream; (void)n; (void)ids; (void)a; (void)b;
    mMutex.Unlock();
}

// @ 0x007123A0
void MaterialManagerBig2::Shutdown()
{
    RemoveAllRegistered();
    // FUN_00711380 on this+0x1b8
    // release file parser and invalid texture, then clear package tables
}

// @ 0x00712670
void MaterialManagerBig2::Update2670()
{
    // reads two int properties, clamps mCount, optionally unregisters, loads a package
}

// @ 0x00712450
void MaterialManagerBig2::RemoveAllRegistered()
{
    // bucket walk + UnregisterArenaContents (see slice s00711220)
}

// @ 0x00711B80
void MaterialManagerBig2::UnregisterArenaContents(void* arena)
{
    (void)arena;
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
    for (uint32_t i = 0; i < n; ++i) {
        FreeNode24* node = pArray[i];
        while (node) {
            FreeNode24* next = node->mpNext;
            DestroyRange(node->mpBegin, node->mpEnd);
            if (node->mpBegin != 0 && node->mpBegin != node->mpCapacity)
                EastlFree(node->mpBegin);
            EastlFree(node);
            node = next;
        }
        pArray[i] = 0;
    }
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
