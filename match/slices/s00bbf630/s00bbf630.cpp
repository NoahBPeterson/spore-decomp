// Slice s00bbf630: Simulator community/commodity cache bookkeeping plus the EASTL
// heap/sort internals it pulls in (0x00bbf630..0x00bc0740):
//   - a hashtable key-intern helper (0x00bbf630) and its sorted-insert sibling (0x00bbf730),
//   - the reset/nuke pass over the Simulator community caches (0x00bbf860),
//   - the five EASTL sort/heap internals (insertion sort, unguarded insertion sort, median,
//     get_partition, sift-down) which all take a by-value "key intern" object in the middle of
//     their argument list and a pool-page cleanup list as the last argument,
//   - the universe-reset wrapper (0x00bbfe80) and the three commodity-node rebuild passes
//     (0x00bbfeb0 / 0x00bbff40 / 0x00bc0000) plus the community-cache rebuild (0x00bc0180)
//     invoked when the active planet's game-data vector changes.
// Flags region: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"
#include <math.h>

typedef unsigned int  uint;
typedef unsigned char uint8;

#pragma pack(push, 4)

// -------------------------------------------------------------------------------------------
// Runtime externs.
extern "C" void* EAAllocate(uint size, const char* name, int a, int b, void* site, int line); // 0x00f473a0
extern "C" void  operator_delete__(void* p);                                                   // 0x00f47380
extern "C" void* FUN_006782c0(void* first, void* last, void* result);                          // 0x006782c0
extern "C" void  FUN_00829110(void* dest, void* first, void* last, void* a, void* b);          // 0x00829110
extern "C" int   FUN_00fc2080(float lo, float hi);                                             // 0x00fc2080
extern "C" void* FUN_00b93c60(void* self, int n, void* alloc);                                 // 0x00b93c60
extern "C" void* FUN_00bbc700(void* a, void* b, float x, float y, float z);                    // 0x00bbc700
extern "C" void  FUN_00aea5d0(void* at, void* src);                                            // 0x00aea5d0
extern "C" void* FUN_00c6fe00(void* p);                                                        // 0x00c6fe00
extern "C" void* FUN_0102f810(void* p);                                                        // 0x0102f810
extern "C" float FUN_0102f8c0(void* p);                                                        // 0x0102f8c0
extern "C" void* FUN_00472b80(void* out, void* m, float a);                                    // 0x00472b80
extern "C" void* FUN_01021260();                                                               // 0x01021260 GetActivePlanet
extern "C" void* FUN_010212a0();                                                               // 0x010212a0 GetActivePlanetRecord
extern "C" void* FUN_01021370();                                                               // 0x01021370 GetPlayerHomePlanet
extern "C" int   FUN_01021080();                                                               // 0x01021080 GetUniverseContext
extern "C" void* FUN_0067de30();                                                               // 0x0067de30 PropertyManager
extern "C" void* FUN_00f473a0();                                                               // 0x00f473a0 (EAAllocate thunk)
extern "C" uint  g_0168a478;   // 0x0168a478
extern "C" uint  g_0168a488;   // 0x0168a488
extern "C" uint  g_0168a48c;   // 0x0168a48c
extern "C" uint  g_0168a490;   // 0x0168a490
extern "C" float g_kEpsilon;   // 0x014666c0

// -------------------------------------------------------------------------------------------
// Small shared types.
struct AutoRef {
    virtual void AddRef();     // vtable +0x00
    virtual void Release();    // vtable +0x04
};

// Object returned by the planet-record accessor; only AddRef is used here.
struct cSPGameDataUFO {
    int AddRef();      // 0x00801920
};

struct Property {
    void*    mpData;      // +0x00
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10
    uint16_t mnType;      // +0x12
};

struct cPropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, void** out);          // vtable +0x24
};

// Pointer vector (eastl::vector<T*>, begin/end/cap at +0/+4/+8).
struct PtrVector {
    void** mpBegin;    // +0x00
    void** mpEnd;      // +0x04
    void** mpCap;      // +0x08

    void   erase(void* first, void* last);   // 0x00e25bd0
    void   push_back(void* src);             // 0x00aea5d0
};

// -------------------------------------------------------------------------------------------
// The Simulator-side hash map used to intern 12-byte keys.
struct SimHash {
    uint32_t pad00;
    uint32_t mpBuckets;    // +0x04
    uint32_t mnBucket;     // +0x08
    uint32_t mUnknown0c;   // +0x0c

    void           find(void* out, const void* key);                    // 0x00a3b2c0
    void           insert(void* iterOut, const void* value, void* key); // 0x00bbf070
    void           deallocate(uint32_t buckets, uint32_t count);        // 0x01068400
    int*           FUN_00bbf630(const int* key);
};

// -------------------------------------------------------------------------------------------
// Inline red-black tree (eastl::rbtree): compare +0x00, anchor +0x04, size +0x14.
struct RBNodeBase {
    RBNodeBase* mpNodeRight;    // +0x00
    RBNodeBase* mpNodeLeft;     // +0x04
    RBNodeBase* mpNodeParent;   // +0x08
    uint8_t     mColor;         // +0x0c
};

struct RBTree {
    int         mCompare;     // +0x00
    RBNodeBase  mAnchor;      // +0x04
    uint32_t    mnSize;       // +0x14

    void nuke(void* node);    // 0x009a9600
};

// -------------------------------------------------------------------------------------------
// The by-value "key intern" object the sort internals take in the middle of their argument
// list.  0x0103de50 looks a 12-byte key up in a tree (ecx = &intern) and returns a pointer to
// the canonical 32-bit key; 0x009a9600 frees a subtree (ecx = &intern).
struct KeyIntern {
    uint32_t m0, m4, m8;

    int* intern(const void* elem);   // 0x0103de50
    void nuke(void* node);           // 0x009a9600
};

struct Elem12  { int v0, v1, v2; };
struct AllocNode { void* mpRoot; AllocNode* mpNext; };

// -------------------------------------------------------------------------------------------
// Vtables.
struct EntrySub {
    virtual void  s00(); virtual void  s04(); virtual void  s08(); virtual void  s0c();
    virtual void  s10(); virtual void  s14(); virtual void  s18(); virtual void  s1c();
    virtual void  s20(); virtual void  s24(); virtual void  s28(); virtual void* s2c();
    virtual void  s30(); virtual void  s34(); virtual void  s38(void* p); virtual void  s3c(void* p);
    virtual void  s40(float f);
};

// Community / commodity entry.
struct Entry {
    virtual void  v00();                     // +0x00 AddRef
    virtual void  v04();                     // +0x04 Release
    virtual void  v08();                     // +0x08
    virtual void* v0c(void* a);              // +0x0c
    virtual void  v10(); virtual void  v14(); virtual void  v18(); virtual void  v1c();
    virtual void  v20(); virtual void  v24(); virtual void  v28(); virtual void  v2c();
    virtual void  v30(); virtual void  v34(); virtual void  v38(); virtual void  v3c();
    virtual void  v40(); virtual void  v44();
    virtual void  v48(void* a);              // +0x48
    virtual void* v4c();                     // +0x4c
    uint8_t   pad04[0x34 - 0x04];            // data between the vptr and the sub-object
    EntrySub  mSub;                          // +0x34 (own vptr; slots 0x2c/0x38/0x3c/0x40)
    uint8_t   pad38[0x68 - 0x38];
    void**    mpVec;                         // +0x68
    void*     pad6c[2];
    uint8_t   pad74[0x90 - 0x74];
    cPropertyList* mpPropList;               // +0x90
    uint8_t   pad94[0x1ec - 0x94];
    int32_t   m1ec;                          // +0x1ec

    void* FillPair(void* p);                 // 0x00bfe260
    void  FUN_00bfe220(void* p);             // 0x00bfe220
    void  FUN_00bff6e0(void* p);             // 0x00bff6e0
    void  SetState(int s);                   // 0x00bfdfb0
    void  FUN_00bfeaf0(void* p);             // 0x00bfeaf0
};

// Records stored in the planet's community list (couched as <noun, state>).
struct OtherRec {
    void*   mpNoun;     // +0x00
    int32_t mState;     // +0x04
};
struct OtherVec {
    OtherRec** mpBegin;   // +0x00
    OtherRec** mpEnd;     // +0x04
    OtherRec** mpCap;     // +0x08
};

// Game-data vector returned by cGameNounManager::GetGameDataVector (begin/end at +4/+8).
struct GameDataVector {
    uint32_t m00;
    void**   mpBegin;   // +0x04
    void**   mpEnd;     // +0x08
};

extern "C" void* FUN_00b3d300();   // 0x00b3d300 SP::NounManager

struct cGameNounManager {
    void* GetGameDataVector(void* a, void* b, void* c, void* d, uint32_t type);  // 0x00b21340
    void  RemoveNoun(void* noun);                                                // 0x00b225d0
    void* CreateNoun(uint32_t type);                                             // 0x00b20c60
};
inline cGameNounManager* SP_NounManager() { return (cGameNounManager*)FUN_00b3d300(); }

// Node returned by PlanetRecord::FUN_00c71030.
struct WNode {
    uint8_t  pad00[0x3c];
    void**   mpBegin;   // +0x3c
    void**   mpEnd;     // +0x40

    void* FUN_00ff0420();   // 0x00ff0420
};

// Element of a WNode's vector: yields the float triple.
struct UintArray {
    float* FUN_00572590();   // 0x00572590
};

// Planet record (retail layout; only the members touched here).
struct PlanetRecord {
    uint32_t   flags4;      // +0x04
    uint8_t    pad08[0x0c - 0x08];
    float      f0c[4];      // +0x0c
    uint8_t    p1c;         // +0x1c
    uint8_t    pad1d[0x6c - 0x1d];
    float      f_6c;        // +0x6c
    uint8_t    pad70[0x90 - 0x70];
    cPropertyList* mpPropList;  // +0x90
    uint8_t    pad94[0xb0 - 0x94];
    uint32_t   p_b0;        // +0xb0
    uint32_t   p_b4;        // +0xb4
    uint8_t    padb8[0x13c - 0xb8];
    void*      p_13c;       // +0x13c

    OtherVec* FUN_00c71020();    // 0x00c71020
    int    FUN_00c70e00();       // 0x00c70e00
    int    FUN_00c710c0();       // 0x00c710c0
    WNode* FUN_00c71030(int i);  // 0x00c71030
    void   FUN_00c72dd0(void* node);  // 0x00c72dd0
    void*  FUN_00b8de30();       // 0x00b8de30
};

extern "C" void* FUN_00b3d350();   // 0x00b3d350 SP::PlanetModel

// Property-manager view exposed by the planet model object (virtual at vtable +0xb0).
struct PropMgr {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    virtual int  GetPropertyVector(void* out);   // vtable +0xb0
};

struct PlanetModelObj {
    virtual void d00();
    uint8_t pad04[0x24 - 4];
    PropMgr* mpPropMgr;    // +0x24

    float* FUN_00b81630(void* out, void* p);   // 0x00b81630
};
inline PlanetModelObj* SP_PlanetModel() { return (PlanetModelObj*)FUN_00b3d350(); }

// -------------------------------------------------------------------------------------------
// The Simulator object this slice's thiscall entry points hang off.
struct SimSelf {
    uint8_t  pad00[0x1c];
    SimHash  mHash;          // +0x1c
    uint8_t  pad2c[0x3c - 0x2c];
    uint8_t  mb3c;           // +0x3c
    uint8_t  pad3d[3];
    int32_t  m40;            // +0x40
    uint8_t  mb44;           // +0x44
    uint8_t  pad45[3];
    RBTree   mTree;          // +0x48
    uint8_t  pad60[0x68 - 0x60];
    PtrVector mVec;          // +0x68
    uint8_t  pad74[0x7c - 0x74];
    uint32_t m7c, m80, m84;  // +0x7c
    uint32_t m88, m8c, m90;  // +0x88

    int   FUN_00bbf730(const int* src, float f);
    void  FUN_00bbf860();
    void  FUN_00bbcb90(int tier, void* planet);   // 0x00bbcb90
    void  FUN_00bbfe80();
    void  FUN_00bc0180(uint8_t flag);
};

// -------------------------------------------------------------------------------------------
// Forward declarations of the helpers used by the rebuild passes.
void FUN_00bbfeb0(void* planet);
void FUN_00bbff40(void* planet);
void FUN_00bc0000(void* planet);

// -------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------

// @ 0x00bbf630
// Intern a 12-byte key in the hash map; returns a pointer four bytes into the stored node.
int* SimHash::FUN_00bbf630(const int* key)
{
    int found[4];
    find(found, key);
    if (found[0] == *(int*)(mpBuckets + mnBucket * 4)) {
        int value[5];
        value[0] = key[0];
        value[1] = found[0];
        value[2] = found[1];
        value[3] = found[2];
        value[4] = found[3];
        insert(found, value, (void*)((uint)key & 0xffffff00u));
    }
    return (int*)(found[0] + 4);
}

// @ 0x00bbf730
int SimSelf::FUN_00bbf730(const int* src, float f)
{
    ++g_0168a478;
    int* p = mHash.FUN_00bbf630((const int*)&g_0168a478);
    p[0] = src[0];
    p[1] = src[1];
    p[2] = src[2];
    *(float*)(p + 3) = f;
    mb3c = 1;
    return (int)g_0168a478;
}

// @ 0x00bbf860
void SimSelf::FUN_00bbf860()
{
    if (mb44 == 0)
        return;

    mHash.deallocate(mHash.mpBuckets, mHash.mnBucket);
    mHash.mUnknown0c = 0;

    mTree.nuke(mTree.mAnchor.mpNodeParent);
    mTree.mAnchor.mpNodeRight  = (RBNodeBase*)&mTree.mAnchor;
    mTree.mAnchor.mpNodeLeft   = (RBNodeBase*)&mTree.mAnchor;
    mTree.mAnchor.mpNodeParent = 0;
    mTree.mAnchor.mColor       = 0;
    mTree.mnSize               = 0;
    mb44                       = 0;

    void* planet = FUN_01021260();
    if (planet != 0) {
        void* rec = *(void**)((char*)planet + 0x13c);
        if (rec == 0)
            rec = FUN_010212a0();
        int lim = FUN_00fc2080(*(float*)((char*)rec + 0xb0), *(float*)((char*)rec + 0xb4));
        for (int tier = 3; tier > lim; --tier)
            FUN_00bbcb90(tier, planet);
    }

    void** it  = mVec.mpBegin;
    void** end = mVec.mpEnd;
    for (; it != end; ++it)
        SP_NounManager()->RemoveNoun(*it);

    void* begin = mVec.mpBegin;
    void* last  = mVec.mpEnd;
    void** p    = (void**)FUN_006782c0(last, last, begin);
    for (void** e = (void**)last; p < e; ++p) {
        AutoRef* o = (AutoRef*)*p;
        if (o != 0)
            o->Release();
    }
    mVec.mpEnd = (void**)begin;

    m7c = g_0168a488;
    m80 = g_0168a48c;
    m84 = g_0168a490;
    m88 = g_0168a488;
    m8c = g_0168a48c;
    m90 = g_0168a490;
}

// -------------------------------------------------------------------------------------------
// EASTL sort / heap internals.  Each takes a by-value "key intern" object in the middle of its
// argument list (the compiler materialises it in the caller's argument area and passes its
// address in ecx to the 0x0103de50 key accessor) and a pool-page cleanup list as its last
// argument, which is walked and freed on the way out.

// @ 0x00bbfa30  eastl::Internal::insertion_sort
void insertion_sort(Elem12* first, Elem12* last, KeyIntern intern, AllocNode* cleanup)
{
    if (first != last) {
        for (Elem12* i = first + 1; i != last; ++i) {
            Elem12 value = *i;
            Elem12* j = i;
            if (j != first) {
                do {
                    Elem12* prev = j - 1;
                    int* kp = intern.intern(prev);
                    int* kv = intern.intern(&value);
                    if (*kv <= *kp)
                        break;
                    *j = *prev;
                    --j;
                } while (j != first);
            }
            *j = value;
        }
    }

    while (cleanup) {
        intern.nuke(cleanup->mpRoot);
        AllocNode* next = cleanup->mpNext;
        operator_delete__(cleanup);
        cleanup = next;
    }
}

// @ 0x00bbfb10  eastl::Internal::insertion_sort_simple
void insertion_sort_simple(Elem12* first, Elem12* last, KeyIntern intern, AllocNode* cleanup)
{
    for (; first != last; ++first) {
        Elem12 value = *first;
        Elem12* prev = first - 1;
        Elem12* at   = first;
        int* kp = intern.intern(prev);
        int* kv = intern.intern(&value);
        if (*kv > *kp) {
            do {
                *at = *prev;
                --prev;
                --at;
                kp = intern.intern(prev);
                kv = intern.intern(&value);
            } while (*kv > *kp);
        }
        *at = value;
    }

    while (cleanup) {
        intern.nuke(cleanup->mpRoot);
        AllocNode* next = cleanup->mpNext;
        operator_delete__(cleanup);
        cleanup = next;
    }
}

// @ 0x00bbfbf0  eastl::Internal::median
Elem12* median(Elem12* a, Elem12* b, Elem12* c, KeyIntern intern, AllocNode* cleanup)
{
    if (*intern.intern(a) > *intern.intern(b)) {
        if (*intern.intern(b) > *intern.intern(c)) {
            intern.nuke(cleanup);
            return b;
        }
        if (*intern.intern(a) > *intern.intern(c)) {
            intern.nuke(cleanup);
            return c;
        }
        intern.nuke(cleanup);
        return a;
    } else {
        if (*intern.intern(a) > *intern.intern(c)) {
            intern.nuke(cleanup);
            return a;
        }
        if (*intern.intern(b) > *intern.intern(c)) {
            intern.nuke(cleanup);
            return c;
        }
        intern.nuke(cleanup);
        return b;
    }
}

// @ 0x00bbfce0  eastl::Internal::get_partition
Elem12* get_partition(Elem12* first, Elem12* last, Elem12 pivot, KeyIntern intern, AllocNode* cleanup)
{
    for (;;) {
        while (*intern.intern(first) > *intern.intern(&pivot))
            ++first;
        --last;
        while (*intern.intern(&pivot) > *intern.intern(last))
            --last;
        if (first >= last)
            break;
        Elem12 t = *first;
        *first = *last;
        *last = t;
        ++first;
    }

    while (cleanup) {
        intern.nuke(cleanup->mpRoot);
        AllocNode* next = cleanup->mpNext;
        operator_delete__(cleanup);
        cleanup = next;
    }
    return first;
}

// @ 0x00bbfdc0  eastl::Internal::sift_down
void sift_down(Elem12* heap, int lo, int hi, Elem12 value, KeyIntern intern, AllocNode* cleanup)
{
    int i = hi;
    int parent = (i - 1) >> 1;
    while (i > lo) {
        Elem12* p = heap + parent;
        if (*intern.intern(p) <= *intern.intern(&value))
            break;
        heap[i] = *p;
        i = parent;
        parent = (i - 1) >> 1;
    }
    heap[i] = value;

    while (cleanup) {
        intern.nuke(cleanup->mpRoot);
        AllocNode* next = cleanup->mpNext;
        operator_delete__(cleanup);
        cleanup = next;
    }
}

// @ 0x00bbfe80
void SimSelf::FUN_00bbfe80()
{
    if (FUN_01021080() == 0 || FUN_01021080() == -1)
        FUN_00bbf860();
    m40 = -1;
}

// @ 0x00bbfeb0
void FUN_00bbfeb0(void* planet)
{
    cGameNounManager* nm = SP_NounManager();
    GameDataVector* dv = (GameDataVector*)nm->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);
    int n = (int)(dv->mpEnd - dv->mpBegin);

    for (int i = 0; i < n; ++i) {
        Entry* node = (Entry*)EAAllocate(8, "Simulator/cCommodityNodeData", 0, 0, 0, 0);
        if (node != 0)
            node = (Entry*)node->FillPair(dv->mpBegin[i]);
        ((Entry*)dv->mpBegin[i])->FUN_00bfe220(node);
        ((PlanetRecord*)planet)->FUN_00c72dd0(node);
    }
}

// @ 0x00bbff40
void FUN_00bbff40(void* planet)
{
    cGameNounManager* nm = SP_NounManager();
    GameDataVector* dv = (GameDataVector*)nm->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);

    OtherVec* other = ((PlanetRecord*)planet)->FUN_00c71020();
    int n = (int)(other->mpEnd - other->mpBegin);
    int m = (int)(dv->mpEnd - dv->mpBegin);
    if (n != m)
        return;

    for (int i = 0; i < n; ++i) {
        Entry*    c = (Entry*)dv->mpBegin[i];
        OtherRec* o = other->mpBegin[i];
        c->FUN_00bfe220(o);
        c->v48(o->mpNoun);
        if (o->mState > 0) {
            if (c->m1ec < 4)
                c->FUN_00bff6e0(c->v4c());
        } else {
            c->SetState(o->mState);
        }
    }
}

// @ 0x00bc0000
void FUN_00bc0000(void* planet)
{
    cGameNounManager* nm = SP_NounManager();
    GameDataVector* dv = (GameDataVector*)nm->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);

    int count = (int)(dv->mpEnd - dv->mpBegin);

    void** buf = 0;
    FUN_00b93c60(&buf, count, (char*)dv + 0x10);

    void* dest;
    FUN_00829110(&dest, dv->mpBegin, dv->mpEnd, buf, 0);
    void** end = (void**)dest;

    int n = ((PlanetRecord*)planet)->FUN_00c710c0();
    for (int i = 0; i < n; ++i) {
        WNode* node = ((PlanetRecord*)planet)->FUN_00c71030(i);
        void** vbase = node->mpBegin;
        int k = (int)(node->mpEnd - vbase);
        for (int j = 0; j < k; ++j) {
            float* p = ((UintArray*)vbase[j])->FUN_00572590();
            void** found = (void**)FUN_00bbc700(buf, end, p[0], p[1], p[2]);
            if (found != end) {
                void* access = node->FUN_00ff0420();
                ((Entry*)*found)->FUN_00bff6e0(access);
                if (found + 1 < end)
                    FUN_006782c0(found + 1, end, found);
                end -= 1;
                if (*end != 0)
                    ((Entry*)*end)->v04();
            }
        }
    }

    for (void** p = buf; p < end; ++p) {
        if (*p != 0)
            ((Entry*)*p)->v04();
    }
    if (buf != 0 && buf[-1] != 0)
        operator_delete__(buf);
}

// @ 0x00bc0180
void SimSelf::FUN_00bc0180(uint8_t flag)
{
    Entry** it  = (Entry**)mVec.mpBegin;
    Entry** end = (Entry**)mVec.mpEnd;
    for (; it != end; ++it)
        SP_NounManager()->RemoveNoun(*it);
    mVec.erase(mVec.mpBegin, mVec.mpEnd);

    if (flag == 0) {
        cGameNounManager* nm = SP_NounManager();
        GameDataVector* dv = (GameDataVector*)nm->GetGameDataVector(
            (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500, 0x403df5c);
        void** begin = dv->mpBegin;
        void** dend  = dv->mpEnd;
        int cnt = (int)(dend - begin);

        Entry** buf = 0;
        if (cnt != 0)
            buf = (Entry**)EAAllocate(cnt * 4, "Simulator", 0, 0, (void*)0x13ebb38, 0xd1);

        void* out;
        FUN_00829110(&out, begin, dend, buf, 0);
        Entry** dstEnd = (Entry**)out;

        for (Entry** p = buf; p != dstEnd; ++p) {
            Entry* o = *p;
            mVec.push_back(&o);
        }
        for (Entry** p = buf; p != dstEnd; ++p) {
            if (*p != 0)
                (*p)->v04();
        }
        if (buf != 0 && buf[-1] != 0)
            operator_delete__(buf);
    }

    FUN_0067de30();

    uint32_t arrLocal = 0;
    int32_t  count2   = SP_PlanetModel()->mpPropMgr->GetPropertyVector(&arrLocal);
    uint32_t accepted = 0;
    for (int i = 0; i < count2; ++i) {
        PlanetRecord* planet = ((PlanetRecord**)arrLocal)[i];
        if (planet == 0)
            continue;
        cPropertyList* pl = planet->mpPropList;
        if (pl == 0)
            continue;
        Property* prop = 0;
        if (pl->GetProperty(0x3f6d22a, (void**)&prop) && prop->mnType == 1) {
            char* value = (char*)prop;
            if (prop->mnFlags & 0x30)
                value = (char*)prop->mpData;
            if (*value != 0)
                ++accepted;
        }
    }

    uint32_t budget = accepted;
    void* rec = FUN_010212a0();
    if (rec != FUN_01021370()) {
        void* p1 = ((PlanetRecord*)rec)->FUN_00b8de30();
        int   p2 = ((cSPGameDataUFO*)p1)->AddRef();
        void* p3 = FUN_00c6fe00((void*)(uint32_t)p2);
        void* p4 = FUN_0102f810(p3);
        float f1 = FUN_0102f8c0(p4);
        void* p5 = FUN_0102f810((void*)2);
        float f2 = FUN_0102f8c0(p5);
        budget = (uint32_t)(int32_t)((f1 / f2) * (float)(int)accepted);
    } else {
        budget = 1000;
    }

    for (int k = 0; k < count2; ++k) {
        PlanetRecord* planet = ((PlanetRecord**)arrLocal)[k];
        if (planet == 0)
            continue;
        cPropertyList* pl = planet->mpPropList;
        if (pl == 0)
            continue;
        Property* prop = 0;
        if (!pl->GetProperty(0x3f6d22a, (void**)&prop) || prop->mnType != 1)
            continue;
        char* value = (char*)prop;
        if (prop->mnFlags & 0x30)
            value = (char*)prop->mpData;
        if (*value == 0)
            continue;

        if (flag == 0) {
            Entry** vit = (Entry**)mVec.mpBegin;
            Entry** vend = (Entry**)mVec.mpEnd;
            bool placed = false;
            while (vit != vend) {
                if (placed)
                    break;
                Entry* c = *vit;
                float v1[3];
                float v2[3];
                float* f0 = SP_PlanetModel()->FUN_00b81630(v1, c->mSub.s2c());
                float* f1 = SP_PlanetModel()->FUN_00b81630(v2, planet->f0c);
                if (fabsf(f1[0] - f0[0]) > g_kEpsilon) { ++vit; continue; }
                if (fabsf(f1[1] - f0[1]) > g_kEpsilon) { ++vit; continue; }
                if (fabsf(f1[2] - f0[2]) > g_kEpsilon) { ++vit; continue; }
                c->mSub.s38(planet->f0c);
                float q[4];
                FUN_00472b80(q, &planet->p1c, 0.0f);
                c->mSub.s3c(q);
                c->FUN_00bfeaf0(planet);
                placed = true;
                ++vit;
            }
        } else {
            if ((uint)(mVec.mpEnd - mVec.mpBegin) < (uint)budget) {
                float dist = planet->f_6c;
                cPropertyList* pl2 = planet->mpPropList;
                if (((planet->flags4 >> 0x11) & 1) == 0 && pl2 != 0) {
                    Property* prop2 = 0;
                    if (pl2->GetProperty(0x254cf89, (void**)&prop2) && prop2->mnType == 0xd) {
                        char* v2 = (char*)prop2;
                        if (prop2->mnFlags & 0x30)
                            v2 = (char*)prop2->mpData;
                        dist = *(float*)v2;
                    }
                }
                Entry* node = (Entry*)SP_NounManager()->CreateNoun(0x403df5c);
                if (node != 0)
                    node = (Entry*)node->v0c((void*)0x403df5f);
                Entry* saved = node;
                if (node != 0)
                    node->v00();
                node->mSub.s40(dist);
                node->mSub.s38(planet->f0c);
                float q[4];
                FUN_00472b80(q, &planet->p1c, 0.0f);
                node->mSub.s3c(q);
                node->FUN_00bfeaf0(planet);
                mVec.push_back(&saved);
                if (saved != 0)
                    saved->v04();
            }
        }
    }

    if (flag != 0) {
        void* active = FUN_01021260();
        if (active != 0) {
            OtherVec* v = ((PlanetRecord*)active)->FUN_00c71020();
            if (v->mpBegin == v->mpEnd) {
                FUN_00bbfeb0(active);
                if (((PlanetRecord*)active)->FUN_00c70e00() == 4) {
                    FUN_00bc0000(active);
                    return;
                }
            } else {
                FUN_00bbff40(active);
            }
        }
    }
}

#pragma pack(pop)
