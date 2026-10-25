// Slice s00a30460 -- EA::Audio::System property/preload entry points,
// a fixed_hash_map constructor, a hashtable erase helper and two
// small fixed_vector-initialising constructors.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch=SSE /fp:fast
#include "types.h"
#include <string.h>

typedef unsigned char u8;
typedef unsigned int  u32;

void* operator new(unsigned int);
void  operator_delete__(void*);

// --- float / vtable constants the original loads from .rdata -----------------
extern const float g_1485378;   // 0.0f
extern const float g_1485720;   // 1.0f
extern const float g_1470f1c;   // 2.0f
extern const float g_13f0620;   // initial hashtable load factor
extern void* g_vtbl_1452a08;    // functor vtable used by the Submix enumeration
extern void* g_vtbl_1452a10;    // provider-list vtable

// --- resolved-by-address externals -------------------------------------------
void* __cdecl FUN_00f473a0(unsigned int size, const char* name,
                           int a, int b, int c, int d);   // named operator new
void  __cdecl FUN_00f47380(void* p);                       // operator delete
void  __cdecl FUN_011e0744(void* dst, void* src, int n);   // vector<bool>::DoInsertValue
void  __cdecl FUN_00a26ce0(void* dst, void* pair, int flag);  // fixed_map insert
void  __cdecl FUN_00a2b120(void* dst, void* pair, int flag);  // fixed_map insert (preload)
void  __cdecl FUN_00a26b00(void* dst, void* pair, int flag);  // fixed_map insert (preload 2)
void  __cdecl FUN_00a17820(void* p);
void  __cdecl FUN_00a236d0(u32, void*, void*, void*, u32, void*, void*);  // hashtable ctor
void  __cdecl FUN_00a21eb0(u32);                           // rehash
void* __cdecl FUN_008de1a0();                              // Eapd::Debug::ObjectError
unsigned int __cdecl FUN_00921340(unsigned int);           // hash seed
unsigned int __stdcall FUN_009213c0(unsigned int);         // bucket count for n elements
void* __cdecl FUN_00921260(void* pool, void* base, u32 size, u32 nodeSize,
                           u32 align, u32 flags);          // fixed_pool_base::init
void* __cdecl RBTreeIncrement(void* node);                 // eastl::RBTreeIncrement

// Raw vtable helpers.  Slot numbers are byte offsets into the vtable, which
// keeps the object models free of reinterpret_casts.
template<class R> static inline R vc0(void* o, int off)
{
    return ((R (__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
template<class R, class A1> static inline R vc1(void* o, int off, A1 a1)
{
    return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1);
}

// ===========================================================================
// 0x00a30460  EA::Audio::System::SetProperty(uint prop, float value)
// ===========================================================================
struct SysBucket { u32 key; float value; SysBucket* next; };
struct SysMap {
    void*        mpOwner;     // +0
    SysBucket**  mpBuckets;   // +4
    u32          mnBuckets;   // +8
};

// eastl::vector<bool> view: three pointers plus the out-of-line resize.
struct VecBool {
    void** mpBegin;          // +0
    void** mpEnd;            // +4
    void** mpCap;            // +8
    void resize(int n);      // 0x0089cb60
};

// The voice-manager object exposing slot +0x48 (performance profile lookup).
struct VoiceMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
    virtual void v18(u32 id, int* outCount, void** outPtr);      // +0x48
};

// The per-voice object walked by the +0x119ba4 array.
struct VoiceObj {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(u32 level, void** begin, int count);         // +0x20
};

// Array of AutoRefCount<IPrimitive> at +0x119ba4.
struct VoicePtrs {
    void** mpBegin;          // +0
    void** mpEnd;            // +4
    void** mpCap;            // +8
    void PushBack(void** out);   // 0x00a2aac0
};

// One element of the mExternalIds intrusive list: the notifiable subobject
// starts at +4, the list links live at +0x10.
struct ExtNotify {
    virtual void n0(); virtual void n1(); virtual void n2();
    virtual void n3(u32 id, float v, int flag);                 // +0xc
};
struct ExtNode {
    u32        mPad0;        // +0
    ExtNotify  mNotify;      // +4  (vptr only)
    u32        mPad8;        // +8
    u32        mPadC;        // +0xc
    ExtNode*   mpNextLink;   // +0x10  (points at next+0x10)
};

struct AudioSystem {
    unsigned char pad0[0x97];
    bool mbMutedForFocus;                 // +0x97
    bool mbMutedByProperty;               // +0x98
    bool mbMuted;                         // +0x99
    unsigned char pad1[0xa8 - 0x9a];
    float mDacOutputMode;                 // +0xa8
    float mDacOutputSampleRate;           // +0xac
    int   mNumOutputChannels;             // +0xb0
    unsigned char pad2[0x1f8 - 0xb4];
    VoiceMgr* mpVoiceMgr;                 // +0x1f8
    unsigned char pad3[0x200 - 0x1fc];
    int   mPerformanceLevel;              // +0x200
    unsigned char pad4[0x119ba4 - 0x204];
    VoicePtrs mVoices;                    // +0x119ba4
    unsigned char pad5[0x13777c - 0x119bb0];
    SysMap mPropertyMap;                  // +0x13777c
    unsigned char pad6[0x157438 - 0x13778c];
    ExtNode* mpExtHead;                   // +0x157438
    unsigned char pad7[0x15bb7c - 0x15743c];
    VecBool mBits;                        // +0x15bb7c

    void SetProperty(u32 key, float value);        // 0x00a30460
    int  FUN_00a30790();                          // 0x00a30790
    void PreloadConfigurations();                 // 0x00a30940
};

// @ 0x00a30460
void AudioSystem::SetProperty(u32 key, float value)
{
    if (key < 0x194f967d) {
        if (key == 0x194f967c) {
            mbMutedForFocus = (value == 0.0f);
        } else if (key == 0x435b383) {
            mDacOutputMode = value;
            switch ((int)value) {
            case 0: mNumOutputChannels = 1; break;
            case 2: mNumOutputChannels = 4; break;
            case 3: mNumOutputChannels = 6; break;
            case 1: mNumOutputChannels = 2; break;
            default:
                mDacOutputMode = 1.0f;
                mNumOutputChannels = 2;
                break;
            }
        } else if (key == 0x6a371e0) {
            mDacOutputSampleRate = value;
        } else if (key == 0x9cd802a) {
            mbMutedByProperty = (value == 0.0f);
        }
    } else if (key == 0x6df5822d) {
        mPerformanceLevel = (int)value;

        // Drop every currently queued "performance changed" bit, then rebuild
        // the bit-vector from the voice manager for the new level.
        void** begin = mBits.mpBegin;
        void** end = mBits.mpEnd;
        FUN_011e0744(begin, end, 0);
        mBits.mpEnd = (void**)((char*)mBits.mpEnd - ((char*)end - (char*)begin));

        int count = 0;
        void* ptr = 0;
        if (mPerformanceLevel == 1)
            mpVoiceMgr->v18(0xdf59188d, &count, &ptr);
        else if (mPerformanceLevel == 2)
            mpVoiceMgr->v18(0xb5760a90, &count, &ptr);

        mBits.resize(count);
        FUN_011e0744(mBits.mpBegin, ptr, count * 4);

        for (VoiceObj** p = (VoiceObj**)mVoices.mpBegin;
             p != (VoiceObj**)mVoices.mpEnd; ++p) {
            (*p)->p8((u32)mPerformanceLevel, mBits.mpBegin,
                     (int)((char*)mBits.mpEnd - (char*)mBits.mpBegin) >> 2);
        }

        // Notify every live voice of the new performance level.
        ExtNode* node = mpExtHead ? (ExtNode*)((char*)mpExtHead - 0x10) : 0;
        ExtNode* stop = (ExtNode*)((char*)&mpExtHead - 0x10);
        while (node != stop) {
            node->mNotify.n3(0x6df5822d, (float)mPerformanceLevel, 1);
            node = node->mpNextLink
                 ? (ExtNode*)((char*)node->mpNextLink - 0x10) : 0;
        }
    } else if (key == 0x899eb157) {
        mbMuted = (value != 0.0f);
    }

    // Publish the property into the flat hash map (open chaining, one past the
    // last bucket used as the "end" sentinel).
    SysBucket** buckets = mPropertyMap.mpBuckets;
    u32 n = mPropertyMap.mnBuckets;
    SysBucket* node = buckets[key % n];
    while (node != 0 && node->key != key)
        node = node->next;
    if (node == 0)
        node = buckets[n];
    if (node == buckets[n]) {
        struct Pair { u32 key; float value; } pair;
        pair.key = key;
        pair.value = value;
        int flag = 0;
        FUN_00a26ce0(&mPropertyMap, &pair, flag);
    } else {
        node->value = value;
    }
}

// ===========================================================================
// 0x00a30790  EA::Audio::System submix enumeration / registration
// ===========================================================================
struct Rec12 { u32 a, b, c; };
struct RecVec { Rec12* mpBegin; Rec12* mpEnd; Rec12* mpCap; };
struct Functor { void* mpVt; };

struct DebugObj {
    virtual void d0(); virtual void d1(); virtual void d2();
    virtual bool d3(Rec12* key, void** out, int, int, int, int);   // +0xc
    virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10();
    virtual void d11(); virtual void d12(); virtual void d13();
    virtual void d14(RecVec* out, Functor* fn, int zero);           // +0x38
};

struct RefCounted {
    virtual void r0(); virtual void r1();
};

struct SubmixObj {
    virtual void s0(); virtual void s1();
    bool Init(void* out);                                          // 0x00a2b7d0
    SubmixObj* InitCtor();                                         // 0x00a2f960
};

// @ 0x00a30790
int AudioSystem::FUN_00a30790()
{
    DebugObj* d = (DebugObj*)FUN_008de1a0();
    if (d == 0)
        return 0;

    RecVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCap = 0;
    Functor fn;
    fn.mpVt = (void*)&g_vtbl_1452a08;

    d->d14(&vec, &fn, 0);

    for (Rec12* it = vec.mpBegin; it != vec.mpEnd; ++it) {
        Rec12 rec = *it;
        void* out = 0;
        if (d->d3(&rec, &out, 0, 0, 0, 0)) {
            SubmixObj* s = (SubmixObj*)FUN_00f473a0(0x197c, "Audio", 0, 0, 0, 0);
            if (s != 0)
                s = s->InitCtor();
            if (s != 0)
                s->s0();
            if (s->Init(out)) {
                mVoices.PushBack(&out);
                vc1<void, SubmixObj*>(this, 0x16c, s);
            }
            if (s != 0)
                s->s1();
        }
        if (out != 0)
            ((RefCounted*)out)->r1();
    }

    if (vec.mpBegin != 0 && ((void**)vec.mpBegin)[-1] != 0)
        FUN_00f47380(vec.mpBegin);
    return 1;
}

// ===========================================================================
// 0x00a30940  EA::Audio::System::PreloadConfigurations
// ===========================================================================
struct RKey { u32 mInstance; u32 mType; u32 mGroup; };

// A red-black tree node as eastl lays it out: three links + colour, then the
// key/value pair; the referenced value lives at +0x1c.
struct RbNode {
    RbNode* mpLeft;      // +0
    RbNode* mpRight;     // +4
    RbNode* mpParent;    // +8
    u32     mColor;      // +0xc
    RKey    mKey;        // +0x10
    void*   mpValue;     // +0x1c
};

// The inline-node fixed_map that lives on the frame (20 000 nodes).
struct PreloadMap {
    RbNode* mpRoot;      // +0
    u32     mnSize;      // +4
    unsigned char mPool[0x9c4b0];

    void ctor();                     // eastl::rbtree+fixed_node_pool ctor
    RbNode* find(RKey* key);
    void DoNukeSubtree();            // eastl::rbtree::DoNukeSubtree
};

RbNode* PreloadMap::find(RKey* key)
{
    RbNode* n = mpRoot;
    while (n != 0) {
        int c = 0;
        if (key->mInstance != n->mKey.mInstance)
            c = (key->mInstance < n->mKey.mInstance) ? -1 : 1;
        else if (key->mType != n->mKey.mType)
            c = (key->mType < n->mKey.mType) ? -1 : 1;
        else if (key->mGroup != n->mKey.mGroup)
            c = (key->mGroup < n->mKey.mGroup) ? -1 : 1;
        if (c == 0)
            return n;
        n = (c < 0) ? n->mpLeft : n->mpRight;
    }
    return 0;
}

struct Provider {
    virtual void p0(); virtual void p1(); virtual void p2();
    virtual u32  p3();                                                  // +0xc
    virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
    virtual void p12(Rec12** out, u32* unused);                         // +0x30
    virtual bool p13(RKey* key, RefCounted** out, int, int, int, int);   // +0x34
};

struct RecordObj {
    virtual void q0(); virtual void q1(); virtual void q2();
    virtual void q3(); virtual void q4(); virtual void q5();
    virtual void* q6();                                                 // +0x18
};

// The resource-manager view object a ResourceConfiguration keeps at +0x14.
struct PropSource {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11();
    virtual void e12();
    virtual bool e13(u32 id, RKey* key);                                // +0x34
};

struct ResConfig {
    virtual void c0(); virtual void c1();
    unsigned char mPad8[0x14 - 8];
    PropSource* mpPropSource;   // +0x14
    RKey mKey;                  // +0x18
    ResConfig* ctor();          // 0x00a2ec30-ish ResourceConfiguration ctor
    bool Read(void* reader);
    void UpdateAggregatedProperties();   // 0x00a1c4?? 
};

struct ProviderNode {
    u32 mPad0;
    void* mpVt;
    u32 mPad8;
    u32 mPadC;
    ProviderNode* mpNextLink;    // +0x10
    ProviderNode** mpPrevLink;   // +0x14
};
struct ProviderList {
    void** mpVt;                 // +0
    u32 mPad4, mPad8, mPadC;
    ProviderNode* mpNextLink;    // +0x10
    ProviderNode** mpPrevLink;   // +0x14
};

// @ 0x00a30940
void AudioSystem::PreloadConfigurations()
{
    PreloadMap map;
    map.ctor();

    DebugObj* mgr = (DebugObj*)FUN_008de1a0();

    ProviderList list;
    list.mpVt = (void**)&g_vtbl_1452a10;
    list.mpNextLink = (ProviderNode*)&list;
    list.mpPrevLink = &list.mpNextLink;

    vc1<void, int>(&list, 0x5c, 0);     // enumerate the resource providers

    ProviderNode* pn = (ProviderNode*)list.mpNextLink;
    while (pn != (ProviderNode*)&list) {
        Provider* prov = (Provider*)pn->mpVt;
        if (prov->p3() != 0x34728492) {
            Rec12* recs = 0;
            u32 unused = 0;
            prov->p12(&recs, &unused);
            int count = (int)unused / 0xc;
            for (int i = 0; i < count; ++i) {
                RKey key;
                key.mInstance = recs[i].a;
                key.mType = recs[i].b;
                key.mGroup = recs[i].c;

                if (map.find(&key) == 0) {
                    RefCounted* stream = 0;
                    if (prov->p13(&key, &stream, 1, 3, 1, 0)) {
                        ResConfig* cfg = (ResConfig*)FUN_00f473a0(
                            0x84, "Audio/ResourceConfiguration/Preload", 0, 0, 0, 0);
                        if (cfg != 0)
                            cfg = cfg->ctor();
                        if (cfg != 0)
                            cfg->c0();
                        cfg->mKey.mInstance = key.mInstance;
                        cfg->mKey.mType = key.mType;
                        cfg->mKey.mGroup = key.mGroup;
                        void* reader = ((RecordObj*)stream)->q6();
                        if (cfg->Read(reader)) {
                            struct Pair { RKey key; ResConfig* value; } p1, p2;
                            p1.key = key;
                            p1.value = cfg;
                            cfg->c0();
                            FUN_00a2b120(&map, &p1, 0);
                            p2.key = key;
                            p2.value = cfg;
                            cfg->c0();
                            FUN_00a26b00(&map, &p2, 0);
                        }
                        cfg->c1();
                    }
                    if (stream != 0)
                        stream->r1();
                }
            }
            if (recs != 0 && ((void**)recs)[-1] != 0)
                FUN_00f47380(recs);
        }
        pn = pn->mpNextLink;
    }

    // Second pass: let each resource configuration read a resource-manager
    // property, then hand it to the audio side.
    for (RbNode* it = map.mpRoot; it != 0; it = (RbNode*)RBTreeIncrement(it)) {
        RKey key;
        key.mInstance = 0;
        key.mType = 0;
        key.mGroup = 0;
        ResConfig* cfg = (ResConfig*)it->mpValue;
        if (cfg->mpPropSource->e13(0x5f6317d5, &key)) {
            if (key.mGroup == 0 || key.mGroup == 0xffffffff)
                key.mGroup = 0x21407ee;
            if (key.mType == 0 || key.mType == 0xffffffff)
                key.mType = 0x2b9f662;
            RbNode* found = map.find(&key);
            if (found != 0) {
                RefCounted* p = (RefCounted*)found->mpValue;
                if (p != 0)
                    p->r0();
                FUN_00a17820(p);
            }
        }
    }

    // Third pass: aggregate the properties once every entry is in place.
    for (RbNode* it = map.mpRoot; it != 0; it = (RbNode*)RBTreeIncrement(it))
        ((ResConfig*)it->mpValue)->UpdateAggregatedProperties();

    // Tear the provider list down through its own destructor slot.
    while ((ProviderNode*)list.mpNextLink != (ProviderNode*)&list) {
        ProviderNode* n = (ProviderNode*)list.mpNextLink;
        vc1<void, int>(&list, 0xc, 0xc);
        list.mpNextLink = n->mpNextLink;
    }

    map.DoNukeSubtree();
}

// ===========================================================================
// 0x00a30e10  eastl::fixed_hash_map<...> constructor (node size 0x14)
// ===========================================================================
struct FixedPoolBase {
    void* mpHead;
    void* pad[7];
    void init(void* base, u32 size, u32 nodeSize, u32 align, u32 flags);
};
struct HashBaseCD {
    void ctor(u32, void*, void*, void*, u32, void*, void*);   // 0x00a236d0
    void rehash(u32);                                          // 0x00a21eb0
};

// A base with an out-of-line destructor: MSVC only emits the /EHsc frame for
// this constructor because a base destructor has to run if a later step throws.
struct MapEhGuard { ~MapEhGuard(); };

struct FixedMap30e10 : MapEhGuard {
    FixedMap30e10(void* a2, void* a3);
    ~FixedMap30e10();
};

// @ 0x00a30e10
FixedMap30e10::FixedMap30e10(void* a2, void* a3)
{
    FixedPoolBase fb;
    fb.mpHead = 0;
    fb.init((char*)this + 0x2f1c, 600000, 0x14, 4, 0);

    struct PoolDesc {
        void* mpBase;        // +0  start of the inline node pool
        void* mpUnused;      // +4
        void* mpEnd;         // +8  one past the last node
        u32   mnNodeSize;    // +0xc
        void* mpOwner;       // +0x10
    } loc;
    loc.mpBase = (char*)this + 0x2f1c;
    loc.mpEnd = (char*)this + 0x2f1c + 600000;
    loc.mnNodeSize = 0x14;
    loc.mpOwner = (char*)this + 0x34;

    u32 v = (u32)FUN_00921340(0xbb9);
    ((HashBaseCD*)this)->ctor(v, a2, &loc, &loc, (u32)(size_t)a3, &loc, &fb);
    *(u32*)((char*)this + 0x10) = *(u32*)&g_13f0620;
    *(u32*)((char*)this + 0x14) = *(u32*)&g_1470f1c;
    *(u32*)((char*)this + 0x18) = 0;
    u32 u = FUN_009213c0(*(u32*)((char*)this + 0xc));
    if (*(u32*)((char*)this + 8) < u)
        ((HashBaseCD*)this)->rehash(u);
}

FixedMap30e10::~FixedMap30e10()
{
}

// ===========================================================================
// 0x00a30f10  eastl::hashtable<...>::erase(key) -> number removed
// ===========================================================================
struct NodeMap {
    void* f0;
    int*  mpBuckets;       // +4
    u32   mnBucketCount;   // +8
    int   mnElementCount;  // +0xc
    void FreeNode(void* node);   // 0x00a2f660
    int  eraseKey(u32* key);
};

// @ 0x00a30f10
int NodeMap::eraseKey(u32* key)
{
    int iVar1 = mnElementCount;
    u32 uVar3 = *key % mnBucketCount;
    u32* puVar4 = (u32*)((char*)mpBuckets + uVar3 * 4);
    if (*(int*)((char*)mpBuckets + uVar3 * 4) != 0) {
        u32* puVar2;
        do {
            puVar2 = (u32*)*puVar4;
            if (*key == *puVar2)
                break;
            puVar4 = puVar2 + 0x79;
        } while (puVar2[0x79] != 0);
        while (*puVar4 != 0 && *key == *(u32*)*puVar4) {
            u32* puVar2 = (u32*)*puVar4;
            *puVar4 = puVar2[0x79];
            FreeNode(puVar2);
            mnElementCount -= 1;
        }
    }
    return iVar1 - mnElementCount;
}

// ===========================================================================
// 0x00a31040  constructor of a fixed_vector<uint32,1000>-backed object
// ===========================================================================
struct Vec11EhGuard { ~Vec11EhGuard(); };

struct FixedVec11 : Vec11EhGuard {
    u32* mpBegin;    // +0
    u32* mpEnd;      // +4
    u32* mpCap;      // +8
    u32* f0c;        // +0xc
    u32* f10;        // +0x10
    u32* f14;        // +0x14
    u32  storage[1001];  // +0x18 .. 0xfbc (capacity one past 1000?)
    u32  fStart;     // +0xfbc
    u32  fEnd;       // +0xfc0
    u32  fCount;     // +0xfc4
    void resize(int n);   // 0x0089cb60
    FixedVec11(int param_2);
    ~FixedVec11();
};

// @ 0x00a31040
FixedVec11::FixedVec11(int param_2)
{
    u32* p = storage;
    f10 = p;
    mpEnd = p;
    mpBegin = p;
    mpCap = p + 1001;
    resize(param_2 + 1);
    fStart = (u32)mpBegin;
    fEnd = (u32)mpBegin;
    fCount = 0;
}

FixedVec11::~FixedVec11()
{
}

// ===========================================================================
// 0x00a310b0  constructor of a fixed_vector<uint32,250>-backed object
// ===========================================================================
struct FixedVec11b {
    u32* mpBegin;    // +0
    u32* mpEnd;      // +4
    u32* mpCap;      // +8
    u32* f0c;        // +0xc
    u32* f10;        // +0x10
    u32* f14;        // +0x14
    u32  storage[250];   // +0x18
    void InitRange(u32 a, u32 b, void* c);   // 0x00a2b2e0
    FixedVec11b* ctor(u32* param_2);
};

// @ 0x00a310b0
FixedVec11b* FixedVec11b::ctor(u32* param_2)
{
    u32* p = storage;
    f10 = p;
    mpEnd = p;
    mpBegin = p;
    mpCap = p + 250;
    InitRange(param_2[0], param_2[1], param_2);
    return this;
}
