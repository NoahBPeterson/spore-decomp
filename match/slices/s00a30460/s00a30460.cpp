// Slice s00a30460 -- EA::Audio::System property/preload entry points,
// a fixed_hash_map constructor, a hashtable erase helper and two
// small fixed_vector-initialising constructors.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

typedef unsigned char u8;
typedef unsigned int  u32;

void* operator new(unsigned int);
void  operator_delete__(void*);

// --- resolved-by-address externals -------------------------------------------
void __cdecl FUN_011e0744(void*, void*, int);              // eastl::vector<bool>::DoInsertValue
void __cdecl FUN_00a26ce0(void*, void*, void*);            // map insert
void __cdecl FUN_00a2b120(void*, void*, void*);            // fixed_map insert
void __cdecl FUN_00a26b00(void*, void*, void*);            // fixed_map insert (2)
void __cdecl FUN_00a17820(void*);
void __cdecl FUN_00a2aac0(void*);
void __cdecl FUN_00a2b2e0(void*, void*, void*);
void __cdecl FUN_00a236d0(u32, void*, void*, void*, u32, void*, void*);
void __cdecl FUN_00a21eb0(u32);                            // rehash
void __cdecl FUN_00a2f960(void);                           // Submix ctor
unsigned int __cdecl FUN_00921340(unsigned int);
unsigned int __stdcall FUN_009213c0(unsigned int);
void __cdecl fixed_pool_base_init_impl(void*, void*, u32, u32, u32, u32);

template<class R> static inline R vc0(void* o, int off)
{ return ((R (__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
template<class R, class A1> static inline R vc(void* o, int off, A1 a1)
{ return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1); }

// ===========================================================================
// 0x00a30460  EA::Audio::System::SetProperty(uint prop, float value)
// ===========================================================================
struct MapNode { u32 key; float val; u32 next; };
struct SysMap {
    void* f0;
    MapNode** buckets;   // +4
    u32       count;     // +8
    void insert(u32 key, float val);
};

struct SystemStub {
    void SetProperty(u32 key, float value);
    void PreloadConfigurations();
};

// @ 0x00a30460
void SystemStub::SetProperty(u32 key, float value)
{
    char* s = (char*)this;
    if (key < 0x194f967d) {
        if (key == 0x194f967c) {
            s[0x97] = (value == 0.0f);
        } else if (key == 0x435b383) {
            *(float*)(s + 0xa8) = value;
            switch ((int)value) {
            case 0: *(int*)(s + 0xb0) = 1; break;
            case 2: *(int*)(s + 0xb0) = 4; break;
            case 3: *(int*)(s + 0xb0) = 6; break;
            default:
                *(float*)(s + 0xa8) = 1.0f;
            case 1: *(int*)(s + 0xb0) = 2; break;
            }
        } else if (key == 0x6a371e0) {
            *(float*)(s + 0xac) = value;
        } else if (key == 0x9cd802a) {
            s[0x98] = (value == 0.0f);
        }
    } else if (key == 0x6df5822d) {
        *(int*)(s + 0x200) = (int)value;
        void* dst = *(void**)(s + 0x15bb80);
        void* src = *(void**)(s + 0x15bb7c);
        FUN_011e0744(dst, src, 0);
        *(int*)(s + 0x15bb80) += ((int)src - (int)dst >> 2) * -4;
        int local_18 = 0;
        void* local_14 = 0;
        if (*(int*)(s + 0x200) == 1)
            vc<void>(*(void**)(s + 0x1f8), 0x48, 0xdf59188d);
        else if (*(int*)(s + 0x200) == 2)
            vc<void>(*(void**)(s + 0x1f8), 0x48, 0xb5760a90);
        (void)local_18; (void)local_14;
        // default 2-ch allocation path: FUN_0089cb60(local_18) then vector<bool>
        // DoInsertValue(local_14, local_18*4).
        void** subs = *(void***)(s + 0x119ba4);
        void** sube = *(void***)(s + 0x119ba8);
        int begin = *(int*)(s + 0x15bb7c);
        int count = (*(int*)(s + 0x15bb80) - begin) >> 2;
        for (; subs != sube; ++subs) {
            void* p = *subs;
            vc<void>(p, 0x20, *(int*)(s + 0x200));
            (void)begin; (void)count;
        }
    } else if (key == 0x899eb157) {
        s[0x99] = (value != 0.0f);
    }

    SysMap* m = (SysMap*)(s + 0x13777c);
    MapNode** buckets = m->buckets;
    u32 n = m->count;
    MapNode* node = buckets[key % n];
    while (node != 0 && node->key != key)
        node = (MapNode*)node->next;
    if (node == 0)
        m->insert(key, value);
    else
        node->val = value;
}

// ===========================================================================
// 0x00a30790  audio-object enumeration callback (Eapd::Debug::ObjectError)
// ===========================================================================
void __cdecl FUN_00a30790_cb(void);   // forward stub

// @ 0x00a30790
int __cdecl FUN_00a30790(void)
{
    void* obj = vc0<void*>(0, 0x0);   // EA::Audio::Eapd::Debug::ObjectError()
    (void)obj;
    return 0;
}

// ===========================================================================
// 0x00a30940  EA::Audio::System::PreloadConfigurations
// ===========================================================================
struct RBNode { u32 pad[7]; void* value; };  // 0x1c -> value

// @ 0x00a30940
void SystemStub::PreloadConfigurations()
{
    // fixed_map<Key,AutoRefCount<ResourceConfiguration>,20000,1,...> local at
    // the base of the frame; enumerates every ResourceMan record that exposes
    // the audio resource-configuration interface, reads it and publishes it.
    // The original allocates a ~640 KiB frame (see _chkstk).  This body keeps
    // the observable sequence of calls.
    char localmap[0x1c];
    memset(localmap, 0, sizeof(localmap));
    void* obj = 0;  // Eapd::Debug::ObjectError()
    (void)obj;
    // enumerator walk + per-record construction/Read/insert omitted (alloca frame)
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
struct FixedMap30e10 {
    int ctor(void* a2, void* a3);
};

// @ 0x00a30e10
int FixedMap30e10::ctor(void* a2, void* a3)
{
    FixedPoolBase fb;
    fb.mpHead = 0;
    fb.init((char*)this + 0x2f1c, 600000, 0x14, 4, 0);
    u32 v = FUN_00921340(0xbb9);
    ((HashBaseCD*)this)->ctor(v, a2, (void*)&a3, (void*)&a3, (u32)(size_t)a3,
                              (void*)&a3, &fb);
    *(u32*)((char*)this + 0x10) = 0x461c4000;
    *(u32*)((char*)this + 0x14) = 0x40000000;
    *(u32*)((char*)this + 0x18) = 0;
    u32 u = FUN_009213c0(*(u32*)((char*)this + 0xc));
    if (*(u32*)((char*)this + 8) < u)
        ((HashBaseCD*)this)->rehash(u);
    return (int)this;
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
struct FixedVec11 {
    u32* mpBegin;    // +0
    u32* mpEnd;      // +4
    u32* mpCap;      // +8
    u32* f0c;        // +0xc
    u32* f10;        // +0x10
    u32* f14;        // +0x14
    u32  storage[1000];  // +0x18
    u32  fStart;     // +0xfbc
    u32  fEnd;       // +0xfc0
    u32  fCount;     // +0xfc4
    void resize(int n);   // 0x0089cb60
    FixedVec11* ctor(int param_2);
};

// @ 0x00a31040
FixedVec11* FixedVec11::ctor(int param_2)
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
    return this;
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
