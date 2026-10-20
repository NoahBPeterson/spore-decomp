// Slice s00a1f2b0 -- EA::Audio::Sound group unsubscription, the eastl
// fixed-container copy/ctor helpers and Sound's own constructor/destructor.
// Object file: SPAudio/AudioSound.obj.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <ctype.h>
#include <new>

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
    *(void**)((char*)this + 0) = (void*)0x1452878;
    *(void**)((char*)this + 4) = (void*)0x1453cac;
    *(void**)((char*)this + 8) = (void*)0x1452870;

    // fixed_vector<u32,10> name buffer at 0x1dfc..0x1e04
    void* p = *(void**)((char*)this + 0x1dfc);
    if ((char*)this + 0x1e04 - (char*)p > 1 && p != 0)
        OperatorDelete(p);

    // the five ResponseCurve members (0x364 bytes each).
    for (u32 off = 0x1a7c; off >= 0xcec; off -= 0x364) {
        void* q = *(void**)((char*)this + off);
        if (q != 0 && q != *(void**)((char*)this + off + 0x10))
            OperatorDelete(q);
    }

    // refcounted configuration object at 0xc90.
    void* cfg = *(void**)((char*)this + 0xc90);
    if (cfg != 0)
        ((void(__thiscall*)(void*))VTSLOT(cfg, 4))(cfg);

    // COW vector<bool> at 0xc7c.
    void* cv = *(void**)((char*)this + 0xc7c);
    if (cv != 0 && *(int*)((char*)cv - 4) != 0)
        OperatorDelete(cv);

    // ... 852-byte EH teardown of the remaining eastl hashtables, the
    // refcounted handles at 0x2d8/0x2dc/0x44/0xc38 and the 0x18/0x28 vectors
    // is omitted here; see partial.txt.
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
    *(void**)((char*)this + 0) = (void*)0x144934c;
    *(void**)((char*)this + 4) = (void*)0x1449430;
    *(void**)((char*)this + 8) = (void*)0x13ef094;
    *(u32*)((char*)this + 0xc)  = 0;   // atomic refcount
    *(u32*)((char*)this + 0x10) = 0;
    *(u32*)((char*)this + 0x14) = 0;
    *(void**)((char*)this + 0) = (void*)0x1452878;
    *(void**)((char*)this + 4) = (void*)0x1453cac;
    *(void**)((char*)this + 8) = (void*)0x1452870;

    // two inline eastl strings share the static empty string (0x1667bac).
    *(void**)((char*)this + 0x18) = (void*)0x1667bac;
    *(void**)((char*)this + 0x1c) = (void*)0x1667bac;
    *(void**)((char*)this + 0x20) = (void*)0x1667bad;
    *(void**)((char*)this + 0x28) = (void*)0x1667bac;
    *(void**)((char*)this + 0x2c) = (void*)0x1667bac;
    *(void**)((char*)this + 0x30) = (void*)0x1667bad;

    *(u32*)((char*)this + 0x38) = 0;
    *(u32*)((char*)this + 0x3c) = 0;
    *(u32*)((char*)this + 0x40) = 0;
    *(u32*)((char*)this + 0x44) = 0;   // mpEmitter
    *(float*)((char*)this + 0x68) = -1.0f;
    *(float*)((char*)this + 0x6c) = 1.0e-6f;
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
    *(float*)((char*)this + 0x78) = 96000.0f;
    *(float*)((char*)this + 0x7c) = 0.0f;
    *(float*)((char*)this + 0x80) = 1.0f;
    *(float*)((char*)this + 0x84) = 1.0f;
    *(float*)((char*)this + 0x88) = 1.0f;
    *(float*)((char*)this + 0x8c) = 0.0f;
    *(float*)((char*)this + 0x90) = 0.0f;
    *(float*)((char*)this + 0x94) = 0.0f;
    *(float*)((char*)this + 0x98) = 1.0f;
    *(u8*)((char*)this + 0x9c) = 0;
    *(u8*)((char*)this + 0x9d) = 0;
    *(u8*)((char*)this + 0x9e) = 0;
    *(u8*)((char*)this + 0x9f) = 1;
    *(u8*)((char*)this + 0xa0) = 0;
    *(u32*)((char*)this + 0xa4) = 0;
    *(float*)((char*)this + 0xa8) = 0.0f;
    *(float*)((char*)this + 0xac) = 0.0f;
    *(float*)((char*)this + 0xb0) = 0.0f;
    *(float*)((char*)this + 0xb4) = 0.0f;
    *(float*)((char*)this + 0xb8) = 0.0f;
    *(float*)((char*)this + 0xbc) = 0.0f;
    *(u8*)((char*)this + 0xc0) = 0;
    *(float*)((char*)this + 0xc4) = 0.0f;
    *(float*)((char*)this + 0xc8) = 0.0f;
    *(float*)((char*)this + 0xcc) = 0.0f;
    *(float*)((char*)this + 0xd0) = 1.0f;
    *(float*)((char*)this + 0xd4) = 1.0f;
    *(float*)((char*)this + 0xd8) = 0.0f;
    *(u32*)((char*)this + 0xdc) = 0;
    *(u32*)((char*)this + 0xe0) = 0;
    Sub_e4_ctor((char*)this + 0xe4);

    // ... the remaining 1164-byte body (nested eastl fixed_hash_map/fixed_vector
    // construction, the five ResponseCurve members, the mGroups/mPrimitives
    // inline buffers and the final vtable refresh) is omitted here; see
    // partial.txt.
}
