// Slice s00a670b0 - EA::Audio::Eapd SymbolManager / System helpers (the "pd" port).
#include "types.h"
#include <string.h>

// ===========================================================================
// Pure Data (pd) types - shared with eapdclass.cpp
// ===========================================================================
namespace EA { namespace Audio { namespace Eapd {

struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }

struct t_atom {
    int a_type;
    union { float w_float; t_symbol w_symbol; } a_w;
};

struct t_class;
typedef t_class* t_pd;

struct t_class {
    char pad00[0x1c];
    void*  c_methods;                                   // +0x1c
    int    c_nmethod;                                   // +0x20
    char   pad24[4];
    void (*c_bangmethod)(t_pd* x);                      // +0x28
    void (*c_floatmethod)(t_pd* x, float f);            // +0x2c
    void (*c_symbolmethod)(t_pd* x, t_symbol s);        // +0x30
    void (*c_listmethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);  // +0x34
    void (*c_anymethod)(t_pd* x, t_symbol s, int argc, t_atom* argv);   // +0x38
};

}}}  // namespace EA::Audio::Eapd

using namespace EA::Audio::Eapd;

// ===========================================================================
// globals (address in the comment)
// ===========================================================================
extern "C" {
    extern t_symbol gEmptySymbol;       // 0x167589c
    extern t_symbol gFloatSymbol;       // 0x16758c4
    extern t_symbol gSymbolSymbol;      // 0x1675894
    extern t_symbol gBangSymbol;        // 0x16758b4
    extern t_symbol gListSymbol;        // 0x16758ac
    extern t_symbol gAnythingSymbol;    // 0x16758cc
    extern t_symbol gHashXSymbol;       // 0x16758bc
    extern t_symbol gHashNSymbol;       // 0x16758a4
    extern void*    spEapdSystem;       // 0x16758d4
}

// unnamed retail callees (address in the comment)
extern "C" {
    void  pd_list(t_pd* x, t_symbol s, int argc, t_atom* argv);         // 0xa495b0
    void  pd_typedmess(t_pd* x, t_symbol s, int argc, t_atom* argv);    // 0xa48100
    float clock_getlogicaltimeafter(float t);                           // 0xa49240
    void  EapdSetLogicalTime(double t);                                 // 0xa492c0
    void  EapdSetLookAhead(float f);                                    // 0xa492e0
    bool  clearallclasses();                                            // 0xa47e30
    bool  g_editor_free();                                              // 0xa4d070
    bool  EapdResetGlobals();                                           // 0xa480b0
    void  EapdStubCall(void* p);                                        // 0xa5ecb0
    uint32_t EapdSymbolHash(const char* s);                             // 0xa66970
    uint32_t EapdRoundUpSize(uint32_t n);                               // 0x9213c0
    uint32_t EapdPrimeBelow(uint32_t n);                                // 0x921340
}

class SymbolManager;

// ===========================================================================
// allocator blocks / pools
// ===========================================================================
struct NamedAllocator {
    void*       mpVtbl;   // +0x00
    int         mA;       // +0x04
    const char* mpName;   // +0x08
};

inline void* AllocatorAlloc(void* a, unsigned n)
{
    void** v = *(void***)a;
    return ((void* (__thiscall*)(void*, unsigned))v[2])(a, n);
}
inline void AllocatorFree(void* a, void* p)
{
    void** v = *(void***)a;
    ((void (__thiscall*)(void*, void*))v[3])(a, p);
}

struct HashNode { uint32_t mKey; void* mValue; HashNode* mpNext; };
struct KeyValue { uint32_t mKey; void* mValue; };
struct Iterator { HashNode* mpNode; HashNode** mpBucket; };

class FixedPool {
public:
    NamedAllocator mInitAllocator;       // +0x00
    NamedAllocator mOverflowAllocator;   // +0x0c
    uint32_t  mnNodeSize;                // +0x18
    void*     mpPoolBegin;               // +0x1c
    void*     mpPoolEnd;                 // +0x20
    void*     mpHead;                    // +0x24
    uint32_t  mnCurrentSize;             // +0x28
    uint32_t  mnPeakSize;                // +0x2c
    void Destroy();                      // 0xa531b0  (~FixedPool)
};

class FixedHashtableAllocator : public FixedPool {
public:
    uint32_t mnBucketCount;              // +0x30
    void*    mpBucketBuffer;             // +0x34
    bool Initialize(unsigned n, int a2, int a3);           // 0xa67d90
    bool InitTables(uint32_t a, uint32_t b, uint32_t c);   // 0xa669d0
    void DestroyAllocator();                               // 0xa67d30
};

class Hashtable {
public:
    uint32_t   mFunctors;                 // +0x00
    HashNode** mpBucketArray;             // +0x04
    uint32_t   mnBucketCount;             // +0x08
    uint32_t   mnElementCount;            // +0x0c
    float      mfMaxLoadFactor;           // +0x10
    uint32_t   mnGrowthFactor;            // +0x14
    uint32_t   mnNextResize;              // +0x18
    FixedHashtableAllocator mAlloc;       // +0x1c

    Hashtable(const char* name);                                    // 0xa67770
    void  Destroy();                                               // 0xa672e0
    void  ClearBuckets(HashNode** arr, uint32_t n);                // 0xa66bf0
    void  Rehash(uint32_t n);                                      // 0xa66b40
    HashNode** AllocateBuckets(uint32_t n);                        // 0xa67ee0
    void  RehashTo(uint32_t n);                                    // 0xa67f60
    bool  Init(uint32_t a, uint32_t b, uint32_t c);                // 0xa67440
    Iterator find(const uint32_t& key);                            // 0x645ed0
    Iterator equal_range(const uint32_t& key);                     // 0x9a6dd0
    Iterator* DoInsertValue(Iterator* sret, const KeyValue* value, const uint32_t* key); // 0xa67370
};

// ===========================================================================
// SymbolManager (size 0xd8)
// ===========================================================================
class SymbolManager {
public:
    void*         mpVtbl;                    // +0x00
    NamedAllocator mAllocA;                  // +0x04
    NamedAllocator mAllocB;                  // +0x10
    char          pad1c[0x10];               // +0x1c
    Hashtable     mSymbols;                  // +0x2c
    Hashtable     mBindings;                 // +0x80
    uint32_t (*mHashFunction)(const char*);  // +0xd4

    SymbolManager();

    // callees
    void  VguiBind(uint32_t a, uint32_t b, uint32_t c);                  // 0xa66e30
    void  BindX(uint32_t a, uint32_t b);                                 // 0xa66ec0
    t_pd* FindByClass(uint32_t a, uint32_t b, uint32_t c);               // 0xa66f10
    void  SendBang(uint32_t a, uint32_t b);                              // 0xa66f70
    void  SendFloat(uint32_t a, uint32_t b, float f);                    // 0xa66fd0
    void  SendSymbol(uint32_t a, uint32_t b, uint32_t c, uint32_t d);    // 0xa67040
    bool  InitBuffer(uint32_t a, uint32_t b, uint32_t c);                // 0xa66890
    bool  FindSym(uint32_t a, t_symbol* out);                            // 0xa66de0
    bool  ClearClasses();                                                // 0xa66d60

    // defined here
    void  BindingsListDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);      // 0xa670b0
    void  BindingsTypedmessDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f); // 0xa67130
    bool  GetSymbolFromName(const char* name, t_symbol* out);            // 0xa67570
    bool  InsertSymbol(uint32_t hash, const char* name, t_symbol* out);  // 0xa674e0
    bool  Init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t (*hashFn)(const char*)); // 0xa67670
};

SymbolManager* GetSymbolManager();   // 0xa67cc0

// ===========================================================================
// instance / asset / callback managers (opaque)
// ===========================================================================
class SubObj {
public:
    virtual void v0();                                       // +0x00
    virtual void v1();                                       // +0x04
    virtual void v2();                                       // +0x08
    virtual bool VfnC(uint32_t a, uint32_t b);               // +0x0c
    virtual bool Vfn10(uint32_t a, float f);                 // +0x10
    virtual bool Vfn14(uint32_t a);                          // +0x14
};
class InstanceObj {
public:
    char pad00[0x34];
    char mSub;                          // +0x34 (returned by 0xff5b80)
    char pad35[0x74 - 0x35];
    bool mFlag;                         // +0x74
    bool GetFlag();                     // 0xa64a00
    void SetX(void* p);                 // 0xa64aa0
    void* GetSub();                     // 0xff5b80
};
class InstanceManager {
public:
    char pad[0xec];
    void* Find(uint32_t key);                       // 0xa65d60
    bool  Shutdown();                               // 0xa65fe0
    bool  Op(uint32_t a, uint32_t b, uint32_t c);   // 0xa657a0
    bool  Op2(uint32_t a, uint32_t b);              // 0xa663e0
    bool  Op3(uint32_t a, uint32_t b);              // 0xa66410
};
class AssetManager {
public:
    char pad[0x60];
    bool FindA(uint32_t a, void** out);                  // 0xa63860
    bool FindB(uint32_t a, uint32_t b, void** out);      // 0xa63dd0
    bool OpC(uint32_t a, uint32_t b);                    // 0xa636b0
};
class CallbackManager {
public:
    char pad[0x54];
    bool Shutdown();       // 0xa64560
    void Update();         // 0xa645c0
};

struct TaskNode { TaskNode* mpNext; TaskNode* mpPrev; void* mpValue; };
class TaskList {
public:
    TaskNode* mpHead;      // +0x00
    TaskNode* mpTail;      // +0x04
    char      mAlloc;      // +0x08 (IInternalAllocator)
    char      pad0c[0x14 - 9];
    void Destroy();        // 0xa67e80
};

// ===========================================================================
// System (size 0x330)
// ===========================================================================
class System {
public:
    void*          mpVtbl;                 // +0x00
    NamedAllocator mAllocator;             // +0x04
    NamedAllocator mOverflowAllocator;     // +0x10
    char           pad1c[0x60];            // +0x1c  asset manager
    SymbolManager  mSymbolManager;         // +0x7c
    char           pad154[0xec];           // +0x154 instance manager
    char           pad240[0x54];           // +0x240 callback manager
    char           pad294[0x64];           // +0x294 global input manager
    void*          mpVoiceManager;         // +0x2f8
    char           pad2fc[4];              // +0x2fc
    double         mdSystemSyncTime;       // +0x300
    double         mdVoiceSyncTime;        // +0x308
    float          mfLatency;              // +0x310
    float          mfLookAhead;            // +0x314
    float          mfMaximumDrift;         // +0x318
    TaskList       mTasks;                 // +0x31c

    bool  Shutdown();                                     // 0xa678d0
    void  SetMaximumDrift(float f);                       // 0xa67960
    static float GetVoiceStartTime(float t);              // 0xa67c70
    bool  FindInstanceSym(uint32_t a, uint32_t b);        // 0xa67990
    bool  GetInstanceFlag(uint32_t a);                    // 0xa679f0
    bool  SetInstanceX(uint32_t a, uint32_t b);           // 0xa67a20
    bool  InstanceVfn10(uint32_t a, uint32_t b, float c); // 0xa67a50
    bool  InstanceVfnC(uint32_t a, uint32_t b, uint32_t c); // 0xa67a90
    bool  InstanceVfn14(uint32_t a, uint32_t b);          // 0xa67ad0
    void  InputVfn10(uint32_t a, float f);                        // 0xa67b10
    bool  AssetInstanceOpA(uint32_t a, uint32_t b, uint32_t* out); // 0xa67b60
    bool  AssetInstanceOpB(uint32_t a);                            // 0xa67bb0
    bool  AssetOpC(uint32_t a);                                    // 0xa67c00
    void  Update(double t);                                        // 0xa68010
    void  UpdateNoTime();                                          // 0xa680c0
};

void* GetVoiceManager();                       // 0xa67d00
void __stdcall SysGfxStubFree(void* p);        // 0xa67c50 (__stdcall)

// ===========================================================================
// functions
// ===========================================================================

// @ 0x00a670b0
void SymbolManager::BindingsListDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    t_symbol s;
    s.mHash = c;
    s.mpName = (const char*)d;
    Hashtable* h = &mBindings;
    Iterator it = h->equal_range(a);
    HashNode** end = h->mpBucketArray + h->mnBucketCount;
    if (it.mpNode != *end) {
        do {
            pd_list((t_pd*)it.mpNode->mValue, s, (int)e, (t_atom*)f);
            it.mpNode = it.mpNode->mpNext;
            while (!it.mpNode)
                it.mpNode = *++it.mpBucket;
        } while (it.mpNode != *end);
    }
}

// @ 0x00a67130
void SymbolManager::BindingsTypedmessDispatch(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    t_symbol s;
    s.mHash = c;
    s.mpName = (const char*)d;
    Hashtable* h = &mBindings;
    Iterator it = h->equal_range(a);
    HashNode** end = h->mpBucketArray + h->mnBucketCount;
    if (it.mpNode != *end) {
        do {
            pd_typedmess((t_pd*)it.mpNode->mValue, s, (int)e, (t_atom*)f);
            it.mpNode = it.mpNode->mpNext;
            while (!it.mpNode)
                it.mpNode = *++it.mpBucket;
        } while (it.mpNode != *end);
    }
}

// @ 0x00a671b0
void sys_vgui(uint32_t a, uint32_t b, uint32_t c)
{
    GetSymbolManager()->VguiBind(a, b, c);
}

// @ 0x00a671d0
void EapdBindRemove(uint32_t a, uint32_t b)
{
    GetSymbolManager()->BindX(a, b);
}

// @ 0x00a671f0
t_pd* pd_findbyclass(uint32_t a, uint32_t b, uint32_t c)
{
    return GetSymbolManager()->FindByClass(a, b, c);
}

// @ 0x00a67210
void pd_send_bang(uint32_t a, uint32_t b)
{
    GetSymbolManager()->SendBang(a, b);
}

// @ 0x00a67230
void pd_send_float(uint32_t a, uint32_t b, float f)
{
    GetSymbolManager()->SendFloat(a, b, f);
}

// @ 0x00a67250
void pd_send_symbol(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    GetSymbolManager()->SendSymbol(a, b, c, d);
}

// @ 0x00a67280
void pd_list_bindings(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    GetSymbolManager()->BindingsListDispatch(a, b, c, d, e, f);
}

// @ 0x00a672b0
void pd_typedmess_bindings(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    GetSymbolManager()->BindingsTypedmessDispatch(a, b, c, d, e, f);
}

// @ 0x00a672e0
void Hashtable::Destroy()
{
    ClearBuckets(mpBucketArray, mnBucketCount);
    HashNode** b = mpBucketArray;
    mnElementCount = 0;
    if (mnBucketCount > 1 && b != (HashNode**)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if (b < (HashNode**)mAlloc.mpPoolBegin || b >= (HashNode**)mAlloc.mpPoolEnd) {
            AllocatorFree(&mAlloc.mOverflowAllocator, b);
        } else {
            *(void**)b = mAlloc.mpHead;
            mAlloc.mpHead = b;
        }
    }
    mAlloc.DestroyAllocator();
}

// @ 0x00a67370
Iterator* Hashtable::DoInsertValue(Iterator* sret, const KeyValue* value, const uint32_t* key)
{
    // eastl::prime_rehash_policy::need_rehash (0x921440)
    struct RehashResult { bool mNeed; uint32_t mNewCount; };
    RehashResult rr;
    ((RehashResult* (__thiscall*)(void*, RehashResult*, uint32_t, uint32_t, uint32_t))
        (*(void***)((char*)this + 0x10))[0])((char*)this + 0x10, &rr, mnBucketCount, mnElementCount, 1);
    if (rr.mNeed)
        Rehash(rr.mNewCount);

    uint32_t h = *key;
    uint32_t bc = mnBucketCount;
    HashNode* node = (HashNode*)mAlloc.mpHead;
    if (node)
        mAlloc.mpHead = *(void**)node;
    else
        node = (HashNode*)AllocatorAlloc(&mAlloc.mOverflowAllocator, mAlloc.mnNodeSize);
    if (node) {
        ++mAlloc.mnCurrentSize;
        if (mAlloc.mnCurrentSize > mAlloc.mnPeakSize)
            mAlloc.mnPeakSize = mAlloc.mnCurrentSize;
        node->mKey = value->mKey;
        node->mValue = value->mValue;
    }
    node->mpNext = 0;
    uint32_t idx = h % bc;
    HashNode* head = mpBucketArray[idx];
    if (head) {
        HashNode* p = head;
        do {
            if (value->mKey == p->mKey) {
                node->mpNext = p->mpNext;
                p->mpNext = node;
                goto inserted;
            }
            p = p->mpNext;
        } while (p);
    }
    node->mpNext = head;
    mpBucketArray[idx] = node;
inserted:
    ++mnElementCount;
    sret->mpNode = node;
    sret->mpBucket = &mpBucketArray[idx];
    return sret;
}

// @ 0x00a67440
bool Hashtable::Init(uint32_t a, uint32_t b, uint32_t c)
{
    bool r = mAlloc.InitTables(a, b, c);
    if (r) {
        Rehash(mAlloc.mnBucketCount - 1);
        mfMaxLoadFactor = 10000.0f;
        mnGrowthFactor = 2;
        mnNextResize = 0;
        uint32_t n = EapdRoundUpSize(mnElementCount);
        if (n > mnBucketCount)
            Rehash(n);
    }
    return r;
}

// @ 0x00a674e0
bool SymbolManager::InsertSymbol(uint32_t hash, const char* name, t_symbol* out)
{
    int n = (int)strlen(name) + 1;
    char* copy = (char*)AllocatorAlloc(this, n);
    if (!copy)
        return false;
    char* dst = copy;
    const char* src = name;
    char ch;
    do {
        ch = *src;
        *dst = ch;
        ++dst;
        ++src;
    } while (ch);
    out->mHash = hash;
    out->mpName = copy;
    KeyValue kv;
    kv.mKey = hash;
    kv.mValue = copy;
    Iterator it;
    uint32_t key = hash & 0xffffff00u;
    mSymbols.DoInsertValue(&it, &kv, &key);
    return true;
}

// @ 0x00a67570
bool SymbolManager::GetSymbolFromName(const char* name, t_symbol* out)
{
    uint32_t h = mHashFunction(name);
    Iterator it = mSymbols.find(h);
    if (mSymbols.mpBucketArray[mSymbols.mnBucketCount] != it.mpNode) {
        out->mHash = h;
        out->mpName = (const char*)it.mpNode->mValue;
        if (_stricmp(out->mpName, name) == 0)
            return true;
        return false;
    }
    return InsertSymbol(h, name, out);
}

// @ 0x00a675f0
t_symbol* gensym(t_symbol* out, const char* name)
{
    if (!GetSymbolManager()->GetSymbolFromName(name, out))
        *out = gEmptySymbol;
    return out;
}

// @ 0x00a67620
bool pd_bind(void* x, t_symbol s)
{
    GetSymbolManager();
    KeyValue kv;
    kv.mKey = s.mHash;
    kv.mValue = x;
    Iterator it;
    uint32_t key = (uint32_t)x & 0xffffff00u;
    GetSymbolManager()->mBindings.DoInsertValue(&it, &kv, &key);
    return true;
}

// @ 0x00a67670
bool SymbolManager::Init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t (*hashFn)(const char*))
{
    if (hashFn)
        mHashFunction = hashFn;
    bool r = InitBuffer(c, d, e) & 1;
    r &= mSymbols.Init(b, d, e);
    r &= mBindings.Init(a, d, e);
    r &= GetSymbolFromName("float", &gFloatSymbol);
    r &= GetSymbolFromName("symbol", &gSymbolSymbol);
    r &= GetSymbolFromName("bang", &gBangSymbol);
    r &= GetSymbolFromName("list", &gListSymbol);
    r &= GetSymbolFromName("anything", &gAnythingSymbol);
    r &= GetSymbolFromName("#N", &gHashNSymbol);
    r &= GetSymbolFromName("#X", &gHashXSymbol);
    r &= GetSymbolFromName("", &gEmptySymbol);
    return r;
}

// @ 0x00a67810
SymbolManager::SymbolManager()
    : mSymbols("EAPd/Symbols"), mBindings("EAPd/Bindings")
{
    mpVtbl = (void*)0x1455710;
    mAllocA.mpVtbl = (void*)0x1454fac;
    mAllocA.mA = 0;
    mAllocA.mpName = "EAPd/SymbolBuffer";
    mAllocB.mpVtbl = (void*)0x1454fac;
    mAllocB.mA = 0;
    mAllocB.mpName = "EAPd/SymbolBuffer";
    for (int i = 0; i < 0x10; ++i)
        pad1c[i] = 0;
    mHashFunction = EapdSymbolHash;
}

// @ 0x00a678d0
bool System::Shutdown()
{
    bool b = ((InstanceManager*)((char*)this + 0x154))->Shutdown() & 1;
    b &= ((bool (__thiscall*)(void*))(*(void***)((char*)this + 0x1c))[2])((char*)this + 0x1c);
    b &= ((CallbackManager*)((char*)this + 0x240))->Shutdown();
    b &= g_editor_free();
    b &= EapdResetGlobals();
    b &= clearallclasses();
    b &= mSymbolManager.ClearClasses();
    return b;
}

// @ 0x00a67960
void System::SetMaximumDrift(float f)
{
    mfMaximumDrift = f * f;
}

// @ 0x00a67990
bool System::FindInstanceSym(uint32_t a, uint32_t b)
{
    bool r = false;
    t_symbol sym;
    if (mSymbolManager.FindSym(a, &sym))
        r = ((InstanceManager*)((char*)this + 0x154))->Op(sym.mHash, (uint32_t)sym.mpName, b);
    return r;
}

// @ 0x00a679f0
bool System::GetInstanceFlag(uint32_t a)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o)
        r = o->GetFlag();
    return r;
}

// @ 0x00a67a20
bool System::SetInstanceX(uint32_t a, uint32_t b)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o) {
        o->SetX((void*)b);
        r = true;
    }
    return r;
}

// @ 0x00a67a50
bool System::InstanceVfn10(uint32_t a, uint32_t b, float c)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o)
        r = ((SubObj*)o->GetSub())->Vfn10(b, c);
    return r;
}

// @ 0x00a67a90
bool System::InstanceVfnC(uint32_t a, uint32_t b, uint32_t c)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o)
        r = ((SubObj*)o->GetSub())->VfnC(b, c);
    return r;
}

// @ 0x00a67ad0
bool System::InstanceVfn14(uint32_t a, uint32_t b)
{
    bool r = false;
    InstanceObj* o = (InstanceObj*)((InstanceManager*)((char*)this + 0x154))->Find(a);
    if (o)
        r = ((SubObj*)o->GetSub())->Vfn14(b);
    return r;
}

// @ 0x00a67b10
void System::InputVfn10(uint32_t a, float f)
{
    void* self = (char*)this + 0x294;
    void** vt = *(void***)self;
    ((void (__thiscall*)(void*, uint32_t, float))vt[4])(self, a, f);
}

// @ 0x00a67b60
bool System::AssetInstanceOpA(uint32_t a, uint32_t b, uint32_t* out)
{
    void* pair[2];
    bool ok = ((AssetManager*)((char*)this + 0x1c))->FindB(a, b, pair);
    if (ok) {
        ((InstanceManager*)((char*)this + 0x154))->Op3((uint32_t)pair[0], (uint32_t)pair[1]);
        *out = (uint32_t)pair[0];
    }
    return ok;
}

// @ 0x00a67bb0
bool System::AssetInstanceOpB(uint32_t a)
{
    void* pair[2];
    bool ok = ((AssetManager*)((char*)this + 0x1c))->FindA(a, pair);
    if (ok)
        ((InstanceManager*)((char*)this + 0x154))->Op2((uint32_t)pair[0], (uint32_t)pair[1]);
    return ok;
}

// @ 0x00a67c00
bool System::AssetOpC(uint32_t a)
{
    bool r = false;
    t_symbol sym;
    if (mSymbolManager.FindSym(a, &sym))
        r = ((AssetManager*)((char*)this + 0x1c))->OpC(sym.mHash, (uint32_t)sym.mpName);
    return r;
}

// @ 0x00a67c50
void __stdcall SysGfxStubFree(void* p)
{
    EapdStubCall(p);
}

// @ 0x00a67c70
float System::GetVoiceStartTime(float t)
{
    System* sys = (System*)spEapdSystem;
    float v = clock_getlogicaltimeafter(t) - sys->mdSystemSyncTime
              + sys->mfLatency + sys->mdVoiceSyncTime;
    if (v < 0.0f)
        return 0.0f;
    return v;
}

// @ 0x00a67d00
void* GetVoiceManager()
{
    if (spEapdSystem)
        return *(void**)((char*)spEapdSystem + 0x2f8);
    return 0;
}

// @ 0x00a67d30
void FixedHashtableAllocator::DestroyAllocator()
{
    if (mpBucketBuffer) {
        AllocatorFree(this, mpBucketBuffer);
    }
    Destroy();
}

// @ 0x00a67d90
bool FixedHashtableAllocator::Initialize(unsigned n, int a2, int a3)
{
    if (mpBucketBuffer) {
        AllocatorFree(this, mpBucketBuffer);
        mpBucketBuffer = 0;
    }
    uint32_t buckets = (uint32_t)((float)n * 1.3333334f);
    mnBucketCount = buckets;
    if (buckets < 3) {
        mnBucketCount = 3;
    } else {
        mnBucketCount = EapdPrimeBelow(buckets) + 1;
    }
    uint32_t bytes = mnBucketCount * 4;
    if (bytes == 0x10) {
        if (!((bool (__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))
                (*(void***)this)[2])(this, 0x10, n + 1, a2, a3))
            return false;
    } else {
        if (!((bool (__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))
                (*(void***)this)[2])(this, 0x10, n, a2, a3))
            return false;
        void* buf = AllocatorAlloc(this, mnBucketCount * 4);
        mpBucketBuffer = buf;
        return buf != 0;
    }
    return false;
}

// @ 0x00a67e80
void TaskList::Destroy()
{
    if (mpHead != (TaskNode*)this) {
        TaskNode* n = mpHead;
        do {
            TaskNode* next = n->mpNext;
            AllocatorFree(&mAlloc, n);
            n = next;
        } while (n != (TaskNode*)this);
    }
    *(void**)(&mAlloc) = (void*)0x1403934;
}

// @ 0x00a67f60
void Hashtable::RehashTo(uint32_t n)
{
    HashNode** nb = AllocateBuckets(n);
    for (uint32_t i = 0; i < mnBucketCount; ++i) {
        HashNode* node = mpBucketArray[i];
        while (node) {
            uint32_t idx = node->mKey % n;
            HashNode* next = node->mpNext;
            mpBucketArray[i] = next;
            node->mpNext = nb[idx];
            nb[idx] = node;
            node = mpBucketArray[i];
        }
    }
    HashNode** old = mpBucketArray;
    if (mnBucketCount > 1 && old != (HashNode**)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if (old < (HashNode**)mAlloc.mpPoolBegin || old >= (HashNode**)mAlloc.mpPoolEnd) {
            AllocatorFree(&mAlloc.mOverflowAllocator, old);
        } else {
            *(void**)old = mAlloc.mpHead;
            mAlloc.mpHead = old;
        }
    }
    mpBucketArray = nb;
    mnBucketCount = n;
}

// @ 0x00a68010
void System::Update(double t)
{
    EapdSetLogicalTime(t);
    double voice = ((double (__thiscall*)(void*))((*(void***)mpVoiceManager)[1]))(mpVoiceManager);
    double diff = (t - mdSystemSyncTime) - (voice - mdVoiceSyncTime);
    if (diff * diff > (double)mfMaximumDrift) {
        mdSystemSyncTime = t;
        mdVoiceSyncTime = voice;
    }
    for (TaskNode* n = mTasks.mpHead; n != (TaskNode*)&mTasks.mpHead; n = n->mpNext) {
        void* obj = n->mpValue;
        ((void (__thiscall*)(void*, double))((*(void***)obj)[1]))(obj, t);
    }
    ((CallbackManager*)((char*)this + 0x240))->Update();
    EapdSetLookAhead(mfLookAhead);
}

// @ 0x00a680c0
void System::UpdateNoTime()
{
    double voice = ((double (__thiscall*)(void*))((*(void***)mpVoiceManager)[1]))(mpVoiceManager);
    EapdSetLogicalTime(voice);
    for (TaskNode* n = mTasks.mpHead; n != (TaskNode*)&mTasks.mpHead; n = n->mpNext) {
        void* obj = n->mpValue;
        ((void (__thiscall*)(void*, double))((*(void***)obj)[1]))(obj, voice);
    }
    ((CallbackManager*)((char*)this + 0x240))->Update();
    EapdSetLookAhead(mfLookAhead);
}
