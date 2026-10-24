// Slice s00a1f2b0 -- EA::Audio::Sound group unsubscription, the eastl
// fixed-container copy/ctor helpers and Sound's own constructor/destructor.
// Object file: SPAudio/AudioSound.obj.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <ctype.h>
#include <new>
#include <intrin.h>
#include <xmmintrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// --- external callees (address-labelled) -----------------------------------
void* GetSystemAT();                                                    // 0x00a206f0
void  __stdcall VectorGrow(void* end, const void* value);               // 0x00899480
void* AllocObject(u32 size);                                            // 0x00a17090
void* CtorHelper(void* obj, void* owner);                               // 0x00a17100
void  SetCurveGain(void* self, float v);                                // 0x00a16fd0
void  Sub_e4_ctor(void* self);                                          // 0x00a107a0
void* Sub_f8_ctor(void* self, void* a, void* b);                        // 0x00a1e320
void  Sub_518_ctor(void* self, void* a, void* b);                       // 0x00a1e420
void  ResponseCurve_ctor(void* self);                                   // 0x00a1aa50
void* VecBool_DoInsertValue(void* a, void* b, u32 n);                   // 0x011e0744
void  VecBool_assign_(void* self, u32 n, void* p);                      // 0x00a69430
void  Vec4_assign_(void* self, const void* src);                        // 0x00a1e520
void  OperatorDelete(void* p);                                          // 0x00f47380
void  Hashtable_DoFreeNodes(void* a, void* b);                          // 0x00a1b6c0
void  HTable28_FreeBuckets(void* a, void* b);                           // 0x00a24480
void  HTable28_Rehash(void* self, u32 n);                               // 0x00a22220
void  Pool_init(void* self, void* p, u32 a, u32 b, u32 c, u32 d);       // 0x00921260
u32   Pool_alloc(u32 n);                                                // 0x00921340
u32   Pool_next(u32 n);                                                 // 0x009213c0
void  HashMap_ctor(void* self, void* a, void* b, void* c, void* d, void* e, void* f); // 0x00a1cdb0

#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])

// eastl fixed_vector header (begin/end/capacity pointers).
struct VecU32 {
    u32* mpBegin; u32* mpEnd; u32* mpCapacity;
    void push_back(u32 value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) u32(value);
        else
            VectorGrow(mpEnd, &value);
    }
};
struct VecPtr { void* mpBegin; void* mpEnd; void* mpCapacity; };

// eastl copy-on-write vector<bool> (refcount lives at buffer[-1]).
struct COWVec { void* mpBegin; void* mpEnd; void* mpCapacity; };

// Embedded configuration object at Sound+0xe4 (0xa107a0 / 0xa10800):
// thiscall, no arguments.
struct SubE4 {
    void ctor();   // 0x00a107a0
    void dtor();   // 0x00a10800
};

// EA::Audio::ResponseCurve at 0xa1aa50: thiscall, no arguments.
struct ResponseCurve {
    void ctor();   // 0x00a1aa50
};

// eastl fixed_vector/fixed_hash_map constructors: thiscall with two dummy
// void* stack arguments, callee pops 8.  The 0xf8 member uses the small
// fixed_vector ctor, the 0x518/0x888 hash tables use the 0x1e0-node variant
// and the 0x338 primitive map uses the fixed_hash_map ctor.
struct FixedVecCtor {
    void* ctor(void* a, void* b);   // 0x00a1e320
};
struct FixedVecCtor2 {
    void* ctor(void* a, void* b);   // 0x00a1e420
};
struct FixedHashMapCtor {
    void* ctor(void* a, void* b);   // 0x00a1fab0
};

// eastl fixed_hashtable header tail: the node/bucket array at +0x04, its
// element count at +0x08, the free-list head at +0x1c and the inline-buffer
// bounds at +0x24/+0x28/+0x30.  DoFreeNodes (0xa1b6c0) and FreeBuckets
// (0xa24480) are thiscall with (begin, count) and callee-pop 8.
struct FixedHash {
    u32   mPad00;        // +0x00
    void* mpBegin;       // +0x04
    u32   mnCount;       // +0x08
    u32   mnFlag;        // +0x0c
    u32   mPad10[3];     // +0x10..+0x1b
    void* mpFreeList;    // +0x1c
    u32   mPad20;        // +0x20
    void* mpInlineLo;    // +0x24
    void* mpInlineHi;    // +0x28
    u32   mPad2c;        // +0x2c
    void* mpInline;      // +0x30
    void DoFreeNodes(void* p, u32 n);   // 0x00a1b6c0
    void FreeBuckets(void* p, u32 n);   // 0x00a24480
};

// MSVC otherwise folds a plain float copy through x87 (fld/fstp); the original
// performs each copy with an SSE movss load/store pair, so force that shape.
static __forceinline void CopyFloat(float* dst, const float* src)
{
    _mm_store_ss(dst, _mm_load_ss(src));
}

static void TeardownFixedHash(FixedHash* h, bool buckets)
{
    if (buckets)
        h->FreeBuckets(h->mpBegin, h->mnCount);
    else
        h->DoFreeNodes(h->mpBegin, h->mnCount);

    h->mnFlag = 0;
    void* p = h->mpBegin;
    u32 n = h->mnCount;
    if (n > 1 && p != h->mpInline) {
        if ((char*)p < (char*)h->mpInlineLo || (char*)p >= (char*)h->mpInlineHi)
            OperatorDelete(p);
        else {
            *(void**)p = h->mpFreeList;
            h->mpFreeList = p;
        }
    }
}

// ===========================================================================
// 0x00a1f3e0  copy-on-write vector<bool> assignment (this = vec @ Sound+0xc7c).
// If either side still owns its buffer, a fresh buffer is built through the
// eastl resize/DoInsertValue pair and handed to Vec4::assign_; otherwise the
// two headers are simply swapped.
// ===========================================================================
// @ 0x00a1f3e0
void Sound_AssignC7C(COWVec* self, COWVec* other)
{
    void* a = self->mpBegin;
    void* b = other->mpBegin;
    bool aShared = (a == 0) || (*(int*)((char*)a - 4) != 0);
    bool bShared = (b == 0) || (*(int*)((char*)b - 4) != 0);
    if (aShared && bShared) {
        self->mpBegin = b;
        other->mpBegin = a;
        void* t = self->mpEnd;      self->mpEnd      = other->mpEnd;      other->mpEnd      = t;
        t       = self->mpCapacity; self->mpCapacity = other->mpCapacity; other->mpCapacity = t;
        return;
    }

    COWVec tmp;
    int n = (int)((char*)self->mpEnd - (char*)self->mpBegin);
    VecBool_assign_(&tmp, (u32)n >> 2, (char*)self + 0xc);
    void* r = VecBool_DoInsertValue(&tmp, self->mpBegin, (u32)n);
    (void)r;
    Vec4_assign_(self, other);
    Vec4_assign_(other, &tmp);
    if (tmp.mpBegin != 0 && *(int*)((char*)tmp.mpBegin - 4) != 0)
        OperatorDelete(tmp.mpBegin);
}

struct Sound {
    u8     pad0[0x2e0];
    VecU32 mGroups;                       // 0x2e0  eastl fixed_vector<u32,10>
    u8     pad1[0x2000 - 0x2e0 - 12];

    void  UnsubscribeFromGroupsFromSymbol(const char* str);   // 0x00a1f2b0
    void  CreatePrimitive(u32 id);                            // 0x00a1f840
    void  CopyStateFrom(Sound* src);                          // 0x00a1f960
    Sound();                                                  // 0x00a1fbb0
    ~Sound();                                                 // 0x00a1f4d0
};

// ===========================================================================
// 0x00a1f2b0  Sound::UnsubscribeFromGroupsFromSymbol
// Tokenise the symbol on non-alnum boundaries, FNV-hash each lowercased token,
// record it in mGroups and tell the audio system to drop the subscription.
// ===========================================================================
// @ 0x00a1f2b0
void Sound::UnsubscribeFromGroupsFromSymbol(const char* str)
{
    if (str == 0 || *str == 0)
        return;

    const char* p = str;
    while (!isalnum(*p))
        ++p;
    while (*p != 0) {
        const char* q = p;
        while (isalnum(*q))
            ++q;
        u32 hash = 0x811c9dc5;
        for (; p < q; ++p)
            hash = hash * 0x1000193 ^ (u32)tolower((unsigned char)*p);
        mGroups.push_back(hash);
        void* mix = this ? (char*)this + 4 : 0;
        void* sys = GetSystemAT();
        ((void(__thiscall*)(void*, u32, void*))VTSLOT(sys, 0x110))(sys, hash, mix);
        while (*p != 0 && !isalnum(*p))
            ++p;
    }
}

// ===========================================================================
// 0x00a1f4d0  Sound::~Sound
// Reset the three vtables, then run the member teardown in reverse declaration
// order (eastl fixed containers, refcounted handles, the response curves and
// the configuration block).  SEH funclets guard the middle of the body.
// ===========================================================================
// @ 0x00a1f4d0
Sound::~Sound()
{
    // three vtable slots of the second vtable family.
    *(void**)((char*)this + 0) = (void*)0x1452878;
    *(void**)((char*)this + 4) = (void*)0x1453cac;
    *(void**)((char*)this + 8) = (void*)0x1452870;

    // file-name string at 0x1dfc: free when capacity-begin > 1.
    void* p = *(void**)((char*)this + 0x1dfc);
    if ((char*)this + 0x1e04 - (char*)p > 1 && p != 0)
        OperatorDelete(p);

    // the five ResponseCurve members, each a fixed_vector at offset +0x00
    // with its inline buffer at +0x10.
    void* q;
    q = *(void**)((char*)this + 0x1a7c);
    if (q != 0 && q != *(void**)((char*)this + 0x1a8c)) OperatorDelete(q);
    q = *(void**)((char*)this + 0x1718);
    if (q != 0 && q != *(void**)((char*)this + 0x1728)) OperatorDelete(q);
    q = *(void**)((char*)this + 0x13b4);
    if (q != 0 && q != *(void**)((char*)this + 0x13c4)) OperatorDelete(q);
    q = *(void**)((char*)this + 0x1050);
    if (q != 0 && q != *(void**)((char*)this + 0x1060)) OperatorDelete(q);
    q = *(void**)((char*)this + 0xcec);
    if (q != 0 && q != *(void**)((char*)this + 0xcfc)) OperatorDelete(q);

    // mpConfiguration (0xc90): release the refcounted config object.
    void* cfg = *(void**)((char*)this + 0xc90);
    if (cfg != 0)
        ((void(__thiscall*)(void*))VTSLOT(cfg, 4))(cfg);

    // mRoutedInstanceIds (0xc7c): copy-on-write vector<bool>.
    void* cv = *(void**)((char*)this + 0xc7c);
    if (cv != 0 && *(int*)((char*)cv - 4) != 0)
        OperatorDelete(cv);

    // mAtmosphericResponse curve buffer (0xc3c), inline buffer at 0xc4c.
    q = *(void**)((char*)this + 0xc3c);
    if (q != 0 && q != *(void**)((char*)this + 0xc4c)) OperatorDelete(q);

    // mpAtmosphericResponse (0xc38): release.
    void* p38 = *(void**)((char*)this + 0xc38);
    if (p38 != 0)
        ((void(__thiscall*)(void*))VTSLOT(p38, 4))(p38);

    // mPrimitives (0xbf8): fixed_vector<IPrimitive*>, inline buffer 0xc08.
    q = *(void**)((char*)this + 0xbf8);
    if (q != 0 && q != *(void**)((char*)this + 0xc08)) OperatorDelete(q);

    // the inline fixed hashtables: mGroupMap (0x888), mSampleMap (0x518)
    // and mPropertySet (0x338, whose teardown uses PHTable::FreeBuckets).
    TeardownFixedHash((FixedHash*)((char*)this + 0x888), false);
    TeardownFixedHash((FixedHash*)((char*)this + 0x518), false);
    TeardownFixedHash((FixedHash*)((char*)this + 0x338), true);

    // mGroups (0x2e0): fixed_vector<u32,10>, inline buffer at 0x2f0.
    q = *(void**)((char*)this + 0x2e0);
    if (q != 0 && q != *(void**)((char*)this + 0x2f0)) OperatorDelete(q);

    // mpGroupSubscriptions (0x2dc): release.
    void* p2dc = *(void**)((char*)this + 0x2dc);
    if (p2dc != 0)
        ((void(__thiscall*)(void*))VTSLOT(p2dc, 4))(p2dc);

    // mpMixable (0x2d8): intrusive refcount.  On the last reference the
    // object is told Release(1) through vtable slot 0, then kept alive.
    void* p2d8 = *(void**)((char*)this + 0x2d8);
    if (p2d8 != 0) {
        int nRef = *(int*)((char*)p2d8 + 4) - 1;
        *(int*)((char*)p2d8 + 4) = nRef;
        if (nRef == 0) {
            *(int*)((char*)p2d8 + 4) = 1;
            ((void(__thiscall*)(void*, int))VTSLOT(p2d8, 0))(p2d8, 1);
        }
    }

    // mNodeMap (0xf8): inline fixed hashtable.
    TeardownFixedHash((FixedHash*)((char*)this + 0xf8), false);

    // the embedded configuration object at 0xe4.
    ((SubE4*)((char*)this + 0xe4))->dtor();

    // mpEmitter (0x44): release.
    void* p44 = *(void**)((char*)this + 0x44);
    if (p44 != 0)
        ((void(__thiscall*)(void*))VTSLOT(p44, 4))(p44);

    // mSampleName (0x28): free the heap buffer when capacity-begin > 1.
    void* p28 = *(void**)((char*)this + 0x28);
    if ((char*)*(void**)((char*)this + 0x30) - (char*)p28 > 1 && p28 != 0)
        OperatorDelete(p28);

    // mName (0x18).
    void* p18 = *(void**)((char*)this + 0x18);
    if ((char*)*(void**)((char*)this + 0x20) - (char*)p18 > 1 && p18 != 0)
        OperatorDelete(p18);

    // the IEventModifier vtable slot is reset last.
    *(void**)((char*)this + 8) = (void*)0x13ef094;
}

// ===========================================================================
// 0x00a1f840  Sound::CreatePrimitive
// Ask the configuration object (this+0xe4) to resolve the primitive id, create
// it through the allocator, register it in the 0xbf8 vector and notify the
// mixable (this+4) either of the new primitive or of a failed lookup.
// ===========================================================================
// @ 0x00a1f840
void Sound::CreatePrimitive(u32 id)
{
    float gain = 0.0f;
    char ok = ((char(__thiscall*)(void*, u32, float*))VTSLOT((char*)this + 0xe4, 0x30))((char*)this + 0xe4, id, &gain);
    if (!ok)
        return;

    void* sys = GetSystemAT();
    if (!((char(__thiscall*)(void*, u32))VTSLOT(sys, 0xf8))(sys, id)) {
        ((void(__thiscall*)(void*, u32, float*, int))VTSLOT((char*)this + 4, 0xc))((char*)this + 4, id, &gain, 1);
        return;
    }

    void* prim = AllocObject(0x1c);
    if (prim)
        prim = CtorHelper(prim, this);
    SetCurveGain(prim, gain);
    ((void(__thiscall*)(void*))VTSLOT(prim, 0))(prim);

    VecPtr* v = (VecPtr*)((char*)this + 0xbf8);
    if (v->mpEnd < v->mpCapacity)
        *(void**)v->mpEnd = prim, v->mpEnd = (char*)v->mpEnd + 4;
    else
        VectorGrow(v->mpEnd, &prim);

    ((void(__thiscall*)(void*, u32, void*))VTSLOT((char*)this + 4, 0x18))((char*)this + 4, id, prim);
}

// ===========================================================================
// 0x00a1f960  Sound::CopyStateFrom
// Snapshot the mixer state of `src` onto this: detach the emitter, move the
// intrusive handles at 0x2d8, copy the bit vector at 0x1de4 and the COW vector
// at 0xc7c, propagate the "direct" flag and reset the pause gain.
// ===========================================================================
// @ 0x00a1f960
void Sound::CopyStateFrom(Sound* src)
{
    ((void(__thiscall*)(void*, int))VTSLOT(this, 0xd4))(this, 0);

    void* se = *(void**)((char*)this + 0x44);
    void* oe = *(void**)((char*)src  + 0x44);
    if (se != oe) {
        if (oe)
            ((void(__thiscall*)(void*))VTSLOT(oe, 0))(oe);
        *(void**)((char*)this + 0x44) = oe;
        if (se)
            ((void(__thiscall*)(void*))VTSLOT(se, 4))(se);
    }
    void* se2 = *(void**)((char*)src + 0x44);
    if (se2) {
        *(void**)((char*)src + 0x44) = 0;
        ((void(__thiscall*)(void*))VTSLOT(se2, 4))(se2);
    }

    void* so = *(void**)((char*)src  + 0x2d8);
    void* mo = *(void**)((char*)this + 0x2d8);
    if (so != mo) {
        if (so)
            ++*(int*)((char*)so + 4);
        *(void**)((char*)this + 0x2d8) = so;
        if (mo && --*(int*)((char*)mo + 4) == 0) {
            *(int*)((char*)mo + 4) = 1;
            ((void(__thiscall*)(void*, int))VTSLOT(mo, 0))(mo, 1);
        }
    }
    void* so2 = *(void**)((char*)src + 0x2d8);
    if (so2) {
        *(void**)((char*)src + 0x2d8) = 0;
        if (--*(int*)((char*)so2 + 4) == 0) {
            *(int*)((char*)so2 + 4) = 1;
            ((void(__thiscall*)(void*, int))VTSLOT(so2, 0))(so2, 1);
        }
    }

    *(u32*)((char*)this + 0x1de0) = *(u32*)((char*)src + 0x1de0);
    VecBool_DoInsertValue((char*)this + 0x1de4, (char*)src + 0x1de4,
                          *(u32*)((char*)this + 0x1dec) * 4);
    Sound_AssignC7C((COWVec*)((char*)this + 0xc7c), (COWVec*)((char*)src + 0xc7c));

    void* e = *(void**)((char*)this + 0x44);
    if (e)
        ((void(__thiscall*)(void*, void*))VTSLOT(e, 0x38))(e, (char*)this + 0xe4);

    if (*(u32*)((char*)src + 0xce4) & 0x20)
        *(u32*)((char*)this + 0xce4) |= 0x20;
    else
        *(u32*)((char*)this + 0xce4) &= ~0x20u;

    void* sys = GetSystemAT();
    ((void(__thiscall*)(void*, void*))VTSLOT(sys, 0x70))(sys, this);
    *(u32*)((char*)this + 0xce4) |= 8;
    *(float*)((char*)this + 0x68) = -1.0f;
}

// ===========================================================================
// 0x00a1fab0  eastl fixed_hash_map<u32, AutoRefCount<PrimitiveRegister>,20,...>
// constructor: carve the node pool out of the inline 0xf0-byte buffer, build
// the hashtable, seed the two float parameters and rehash to the initial
// bucket count.
// ===========================================================================
// @ 0x00a1fab0
void PrimHashTable_ctor(void* self, void* a, void* b)
{
    Pool_init((char*)self + 0x8c, (char*)self + 0x8c, 0xf0, 0xc, 4, 0);
    u32 n = Pool_alloc(0x15);
    HashMap_ctor(self, a, b, b, b, b, (char*)self + 0x8c);
    (void)n;
    *(float*)((char*)self + 0x10) = 1.0e4f;
    *(float*)((char*)self + 0x14) = 2.0f;
    *(u32*)((char*)self + 0x18) = 0;
    u32 want = Pool_next(*(u32*)((char*)self + 0xc));
    if (want > *(u32*)((char*)self + 8))
        HTable28_Rehash(self, want);
}

// ===========================================================================
// 0x00a1fbb0  Sound::Sound
// Set the three vtables, clear the atomic refcount, point the two inline
// eastl strings at the shared empty string, initialise every float field and
// construct the nested containers.
// ===========================================================================
// @ 0x00a1fbb0
Sound::Sound()
{
    // first vtable family (ITickable / IMixable / IEventModifier).
    *(void**)((char*)this + 0) = (void*)0x144934c;
    *(void**)((char*)this + 4) = (void*)0x1449430;
    *(void**)((char*)this + 8) = (void*)0x13ef094;

    // atomic refcount at 0xc, then the intrusive-list links (0x14 before 0x10).
    _InterlockedExchange((long*)((char*)this + 0xc), 0);
    *(u32*)((char*)this + 0x14) = 0;
    *(u32*)((char*)this + 0x10) = 0;

    // second vtable family.
    *(void**)((char*)this + 0) = (void*)0x1452878;
    *(void**)((char*)this + 4) = (void*)0x1453cac;
    *(void**)((char*)this + 8) = (void*)0x1452870;

    // mName (+0x18) and mSampleName (+0x28) point at the shared empty string.
    *(void**)((char*)this + 0x18) = (void*)0x1667bac;
    *(void**)((char*)this + 0x1c) = (void*)0x1667bac;
    *(void**)((char*)this + 0x20) = (void*)0x1667bad;
    *(void**)((char*)this + 0x28) = (void*)0x1667bac;
    *(void**)((char*)this + 0x2c) = (void*)0x1667bac;
    *(void**)((char*)this + 0x30) = (void*)0x1667bad;

    // ids and the emitter handle.
    *(u32*)((char*)this + 0x38) = 0;
    *(u32*)((char*)this + 0x3c) = 0;
    *(u32*)((char*)this + 0x40) = 0;
    *(u32*)((char*)this + 0x44) = 0;

    // gain / distance / pitch tuning block (the original reads the shared
    // constants at 0x13eb1bc, 0x13f11c8 and 0x145284c).
    CopyFloat((float*)((char*)this + 0x68), (const float*)0x13eb1bc);
    CopyFloat((float*)((char*)this + 0x6c), (const float*)0x13f11c8);
    *(float*)((char*)this + 0x48) = 0.0f;
    *(float*)((char*)this + 0x4c) = 0.0f;
    *(float*)((char*)this + 0x50) = 1.0f;
    *(float*)((char*)this + 0x54) = 0.0f;
    *(float*)((char*)this + 0x58) = 0.0f;
    *(float*)((char*)this + 0x5c) = 1.0f;
    *(float*)((char*)this + 0x60) = 0.0f;
    *(float*)((char*)this + 0x64) = 0.0f;
    *(float*)((char*)this + 0x70) = 1.0f;
    *(float*)((char*)this + 0x74) = 0.0f;
    CopyFloat((float*)((char*)this + 0x78), (const float*)0x145284c);
    *(float*)((char*)this + 0x7c) = 0.0f;
    *(float*)((char*)this + 0x80) = 1.0f;
    *(float*)((char*)this + 0x84) = 1.0f;
    *(float*)((char*)this + 0x88) = 1.0f;
    *(float*)((char*)this + 0x8c) = 0.0f;
    *(float*)((char*)this + 0x90) = 0.0f;
    *(float*)((char*)this + 0x94) = 0.0f;
    *(float*)((char*)this + 0x98) = 1.0f;

    // flags.
    *(u8*)((char*)this + 0x9c) = 0;
    *(u8*)((char*)this + 0x9d) = 0;
    *(u8*)((char*)this + 0x9e) = 0;
    *(u8*)((char*)this + 0x9f) = 1;
    *(u8*)((char*)this + 0xa0) = 0;
    *(u32*)((char*)this + 0xa4) = 0;

    // position / doppler vectors and the stop-reason block; the original
    // reloads the three shared runtime floats at 0x166d9e0/4/8 for each slot.
    CopyFloat((float*)((char*)this + 0xa8), (const float*)0x166d9e0);
    CopyFloat((float*)((char*)this + 0xac), (const float*)0x166d9e4);
    CopyFloat((float*)((char*)this + 0xb0), (const float*)0x166d9e8);
    CopyFloat((float*)((char*)this + 0xb4), (const float*)0x166d9e0);
    CopyFloat((float*)((char*)this + 0xb8), (const float*)0x166d9e4);
    CopyFloat((float*)((char*)this + 0xbc), (const float*)0x166d9e8);
    *(u8*)((char*)this + 0xc0) = 0;
    CopyFloat((float*)((char*)this + 0xc4), (const float*)0x166d9e0);
    CopyFloat((float*)((char*)this + 0xc8), (const float*)0x166d9e4);
    CopyFloat((float*)((char*)this + 0xcc), (const float*)0x166d9e8);
    *(float*)((char*)this + 0xd0) = 1.0f;
    *(float*)((char*)this + 0xd4) = 1.0f;
    *(float*)((char*)this + 0xd8) = 0.0f;
    *(u32*)((char*)this + 0xdc) = 0;
    *(u32*)((char*)this + 0xe0) = 0;

    // the embedded configuration object.
    ((SubE4*)((char*)this + 0xe4))->ctor();

    // mGroups (0xf8): inline fixed_vector<u32,10> (buffer at +0x184),
    // followed by the intrusive handles at 0x2d8/0x2dc and the mPrimitives
    // vector header pointing at its inline buffer at 0x2f8.
    char dummy = 0;
    ((FixedVecCtor*)((char*)this + 0xf8))->ctor(&dummy, &dummy);

    *(void**)((char*)this + 0x2d8) = 0;
    *(void**)((char*)this + 0x2dc) = 0;
    void* vec = (char*)this + 0x2f8;
    *(void**)((char*)this + 0x2f0) = vec;
    *(void**)((char*)this + 0x2e4) = vec;
    *(void**)((char*)this + 0x2e0) = vec;
    *(void**)((char*)this + 0x2e8) = (char*)vec + 0x28;

    // mPropertySet (0x338): inline fixed_hash_map with its policy fields.
    *(u32*)((char*)this + 0x320) = 0;
    *(float*)((char*)this + 0x324) = 0.0f;
    *(float*)((char*)this + 0x328) = 0.0f;
    *(float*)((char*)this + 0x32c) = 0.0f;
    *(u32*)((char*)this + 0x330) = 2;
    *(u32*)((char*)this + 0x334) = 0xee8347b0;
    ((FixedHashMapCtor*)((char*)this + 0x338))->ctor(&dummy, &dummy);

    // mGroupMap (0x518) and mSampleMap (0x888).
    ((FixedVecCtor2*)((char*)this + 0x518))->ctor(&dummy, &dummy);
    ((FixedVecCtor2*)((char*)this + 0x888))->ctor(&dummy, &dummy);

    // mPrimitives (0xbf8): fixed_vector<IPrimitive*>, inline buffer 0xc10.
    void* p = (char*)this + 0xc10;
    *(void**)((char*)this + 0xc08) = p;
    *(void**)((char*)this + 0xbfc) = p;
    *(void**)((char*)this + 0xbf8) = p;
    *(void**)((char*)this + 0xc00) = (char*)p + 0x28;
    *(void**)((char*)this + 0xc38) = 0;

    // mRoutedInstanceIds buffer chain (0xc3c): inline buffer 0xc54.
    p = (char*)this + 0xc54;
    *(void**)((char*)this + 0xc4c) = p;
    *(void**)((char*)this + 0xc40) = p;
    *(void**)((char*)this + 0xc3c) = p;
    *(void**)((char*)this + 0xc44) = (char*)p + 0x28;

    *(void**)((char*)this + 0xc7c) = 0;
    *(void**)((char*)this + 0xc80) = 0;
    *(void**)((char*)this + 0xc84) = 0;
    *(void**)((char*)this + 0xc90) = 0;

    // the atmospheric / filter / pitch block starting at 0xcb0.
    *(u8*)((char*)this + 0xcb0) = 0;
    *(float*)((char*)this + 0xcc0) = 0.0f;
    *(float*)((char*)this + 0xcc4) = 0.0f;
    *(u32*)((char*)this + 0xc94) = 0;
    *(u32*)((char*)this + 0xc98) = 0;
    *(u32*)((char*)this + 0xc9c) = 0;
    *(u32*)((char*)this + 0xca0) = 0;
    *(u32*)((char*)this + 0xca4) = 0;
    *(u32*)((char*)this + 0xca8) = 0;
    *(float*)((char*)this + 0xcb8) = 1.0f;
    *(float*)((char*)this + 0xcbc) = 0.0f;
    *(u32*)((char*)this + 0xcac) = 0;
    *(double*)((char*)this + 0xcc8) = 0.0;
    *(float*)((char*)this + 0xcd0) = 0.0f;
    *(u8*)((char*)this + 0xcd4) = 0;
    *(u8*)((char*)this + 0xcd5) = 0;
    *(u32*)((char*)this + 0xcd8) = 0xffffffff;
    *(u32*)((char*)this + 0xcdc) = 0;
    *(u32*)((char*)this + 0xce0) = 1;
    *(u32*)((char*)this + 0xce4) = 0;
    *(u32*)((char*)this + 0xce8) = 0x25df0108;

    // the five ResponseCurve members (0x364 bytes apart).
    ((ResponseCurve*)((char*)this + 0xcec))->ctor();
    ((ResponseCurve*)((char*)this + 0x1050))->ctor();
    ((ResponseCurve*)((char*)this + 0x13b4))->ctor();
    ((ResponseCurve*)((char*)this + 0x1718))->ctor();
    ((ResponseCurve*)((char*)this + 0x1a7c))->ctor();

    *(u32*)((char*)this + 0x1dec) = 5;
    *(void**)((char*)this + 0x1dfc) = (void*)0x1667bac;
    *(void**)((char*)this + 0x1e00) = (void*)0x1667bac;
    *(void**)((char*)this + 0x1e04) = (void*)0x1667bad;
    *(u32*)((char*)this + 0x1e0c) = 3;
    *(u32*)((char*)this + 0xce4) = 0;

    // let the configuration object refresh its listeners, then clear the
    // intrusive-list links once more (the stores happen before the call).
    void* pE4 = (char*)this + 0xe4;
    void* vtbl = *(void**)pE4;
    *(u32*)((char*)this + 0x14) = 0;
    *(u32*)((char*)this + 0x10) = 0;
    ((void(__thiscall*)(void*))((void**)vtbl)[0])(pE4);
}
