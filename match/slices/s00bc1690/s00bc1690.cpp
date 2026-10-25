// Slice s00bc1690: tribe/city community update helpers, the sound-slot table and the eastl
// record-vector sort/merge helpers (0xc-byte records).
// Targets: 00BC1690 FUN_00bc1690   00BC1700 FUN_00bc1700   00BC17A0 FUN_00bc17a0
//          00BC1830 FUN_00bc1830   00BC1A50 FUN_00bc1a50   00BC1B10 FUN_00bc1b10
//          00BC2070 FUN_00bc2070   00BC20E0 FUN_00bc20e0   00BC2180 FUN_00bc2180
//          00BC21C0 FUN_00bc21c0   00BC2240 FUN_00bc2240   00BC22B0 FUN_00bc22b0
//          00BC23D0 FUN_00bc23d0   00BC24C0 FUN_00bc24c0   00BC2520 FUN_00bc2520
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "s00bc1690.h"
#include <stddef.h>
#include <math.h>

// FLT_MAX as stored by the original (0x7f7fffff, loaded with movss).
#define FLT_MAX_ 3.402823466e+38f
// 2^32 as float: added to a negative int before scaling (the unsigned-int conversion).
#define FLT_2P32 4.2949673e+09f

// Reference-returning min; the retail build materialised the result as an address
// select (lea &a / lea &b; movss xmm0,[edx]) rather than a branch.
static inline float& RefMin(float& a, float& b) { return (a <= b) ? a : b; }

// Min as the retail build emitted it: a mutable accumulator kept in xmm0 compared
// against a memory element (comiss xmm0,[elem]; ja), with the result stored back.
#define ACC_MIN(acc, elem) ((acc) > (elem) ? (elem) : (acc))

// A 0xc-byte ResourceKey (three words) as stored in the species vectors.
struct ResourceKey {
    uint32_t mType;                                             // +0x00
    uint32_t mGroup;                                            // +0x04
    uint32_t mInstance;                                         // +0x08
};

// The object owning the community-pointer vector at +0x68.
struct CommunityUpdater {
    uint32_t pad00[0x68/4];                                     // 0x00..0x68
    void**   mpBegin;                                           // 0x68
    void**   mpEnd;                                             // 0x6c

    void AdvanceCommunities(int param_2, int param_3);          // 0x00BC1690
};

// The object owning the city/tribe display state used at 0x00bc2070/0x00bc20e0.
struct CityDisplayOwner {
    uint32_t pad00[0x3c/4];                                     // 0x00..0x3c
    unsigned char mFlag3c;                                      // 0x3c
    uint32_t mSubject40;                                        // 0x40
    unsigned char mActive44;                                    // 0x44
    uint32_t pad48[0x1c/4];                                     // 0x48..0x64
    uint32_t mValue64;                                          // 0x64

    void Activate(void* param_2, void* param_3);                // 0x00BC2070
    void SetSubject(void* param_2);                             // 0x00BC20E0
};

// ===========================================================================
// 0x00bc1690  FUN_00bc1690: advance every community's phase by a millisecond step
// ===========================================================================
// @ 0x00bc1690
void __fastcall AdvanceCommunities(CommunityUpdater* self, int, int param_2, int param_3)
{
    float dt = (float)param_3;                                  // fild int->float
    if (param_3 < 0)
        dt += FLT_2P32;
    dt *= 0.001f;
    void** end   = self->mpEnd;
    void** begin = self->mpBegin;
    while (begin != end) {
        ((RcCommunity*)*begin)->AdvancePhase(dt);
        ++begin;
    }
    if (*(char*)((char*)self + 0x3c) != 0) {
        if (cSPLivingUniverse_GetUniverseContext() == 0) {
            *(char*)((char*)self + 0x3c) = 0;
            ((RcDisplay*)self)->FUN_00bc08d0(0);
        }
    }
}

// ===========================================================================
// 0x00bc1700  FUN_00bc1700: heapify every record (0xc-byte) down to the root
// ===========================================================================
// @ 0x00bc1700
void FUN_00bc1700(void* param_1, void* param_2)
{
    int n = (int)((char*)param_2 - (char*)param_1) / 0xc;
    if (n > 1) {
        int i = ((n - 2) >> 1) + 1;
        char* p = (char*)param_1 + i * 0xc;
        do {
            uint32_t v0 = *(uint32_t*)(p - 4);
            uint32_t v1 = *(uint32_t*)(p - 0xc);
            uint32_t v2 = *(uint32_t*)(p - 8);
            p -= 0xc;
            --i;
            FUN_00af0d40(&i);
            FUN_00bc0740(param_1, 0, n, i, v1, v2, v0);
        } while (i != 0);
    }
    void* node = 0;                                             // in_stack_00000018
    while (node != 0) {
        DoNukeSubtree(*(void**)node);
        void* next = *(void**)((char*)node + 4);
        operator_delete__(node);
        node = next;
    }
}

// ===========================================================================
// 0x00bc17a0  FUN_00bc17a0: repeatedly sift the largest record to the end, then
// destroy the associated rbtree nodes
// ===========================================================================
// @ 0x00bc17a0
// NOTE: the retail code reads the caller's eastl node temporary at [esp+0x18];
// reproduced here as a trailing parameter so the offsets line up.
void FUN_00bc17a0(void* param_1, void* param_2, int, int, int, void* root)
{
    void* end = param_2;
    int n = (int)((char*)param_2 - (char*)param_1);
    if (n / 0xc > 1) {
        do {
            uint32_t node[7];                                   // 0x1c-byte node temporary
            ResourceKey key;                                    // the record being erased
            ((RcMapNode*)node)->FUN_00af0d40(&key);
            FUN_00bc0840(param_1, end);
            n -= 0xc;
            end = (char*)end - 0xc;
        } while (n / 0xc > 1);
    }
    while (root != 0) {
        DoNukeSubtree(*(void**)root);
        void* next = *(void**)((char*)root + 4);
        operator_delete__(root);
        root = next;
    }
}

// ===========================================================================
// 0x00bc1830  FUN_00bc1830: heap-sort a record range: heapify, then bubble the
// root record into each successive position
// ===========================================================================
// @ 0x00bc1830
void FUN_00bc1830(void* param_1, void* param_2, void* param_3, HeapCompare)
{
    // Construct the eastl node temporary the sort helpers expect on the stack.
    uint32_t node[7];
    ResourceKey key;
    ((RcMapNode*)node)->FUN_00af0d40(&key);

    FUN_00bc1700(param_1, param_2);

    // Selection pass: walk the tail and, whenever its key exceeds the first
    // record's key, swap it to the front and re-heapify.
    char* p = (char*)param_2;
    while (p < (char*)param_3) {
        uint32_t* ka = ((RcKeyAccessor*)&key)->GetKey(p);
        uint32_t* kb = ((RcKeyAccessor*)&key)->GetKey(param_1);
        if (*kb < *ka) {
            uint32_t v0 = *(uint32_t*)(p + 8);
            uint32_t v1 = *(uint32_t*)(p + 0);
            uint32_t v2 = *(uint32_t*)(p + 4);
            *(uint32_t*)(p + 0) = *(uint32_t*)param_1;
            *(uint32_t*)(p + 4) = *(uint32_t*)((char*)param_1 + 4);
            *(uint32_t*)(p + 8) = *(uint32_t*)((char*)param_1 + 8);
            uint32_t node2[7];
            ((RcMapNode*)node2)->FUN_00af0d40(&key);
            int cnt = (int)((char*)param_2 - (char*)param_1) / 0xc;
            FUN_00bc0740(param_1, 0, cnt, 0, v1, v2, v0);
        }
        p += 0xc;
    }

    uint32_t node3[7];
    ((RcMapNode*)node3)->FUN_00af0d40(&key);
    void* root = *(void**)((char*)node3 + 0x18);
    FUN_00bc17a0(param_1, param_2, 0, 0, 0, root);
}

// ===========================================================================
// 0x00bc1940  FUN_00bc1940: introspective recursion for the record sort: while
// the range is longer than 0x1c records, partition it around the median and
// recurse into the right half; finish with a heap sort once the depth runs out.
// ===========================================================================
// @ 0x00bc1940
void FUN_00bc1940(void* param_1, void* param_2, int depth, HeapCompare compare)
{
    while ((int)((char*)param_2 - (char*)param_1) / 0xc > 0x1c && depth > 0) {
        ResourceKey* pivot = (ResourceKey*)FUN_00bbfbf0(param_1,
            (char*)param_1 + ((int)((char*)param_2 - (char*)param_1) / 0xc / 2) * 0xc,
            (char*)param_2 - 0xc, compare);
        void* part = FUN_00bbfce0(param_1, param_2, *(Record12*)pivot, compare);
        --depth;
        FUN_00bc1940(part, param_2, depth, compare);
        param_2 = part;
    }
    if (depth == 0)
        FUN_00bc1830(param_1, param_2, param_2, compare);
}

// ===========================================================================
// 0x00bc1a50  FUN_00bc1a50: introspective record sort entry point
// ===========================================================================
// @ 0x00bc1a50
void FUN_00bc1a50(void* param_1, void* param_2)
{
    if (param_1 != param_2) {
        HeapCompare compare;
        uint32_t scratch[6];
        FUN_00af0d40(scratch);
        int n = 0;
        int cnt = (int)((char*)param_2 - (char*)param_1) / 0xc;
        for (int t = cnt; t != 0; t >>= 1)
            ++n;
        FUN_00bc1940(param_1, param_2, n * 2 - 2, compare);
        FUN_00af0d40(scratch);
        if (cnt > 0x1c) {
            FUN_00bbfa30(param_1, (char*)param_1 + 0x150);
            FUN_00af0d40(scratch);
            FUN_00bbfb10((char*)param_1 + 0x150, param_2);
            void* node = 0;                                     // in_stack_00000018
            while (node != 0) {
                DoNukeSubtree(*(void**)node);
                void* next = *(void**)((char*)node + 4);
                operator_delete__(node);
                node = next;
            }
            return;
        }
        FUN_00bbfa30(param_1, param_2);
    }
    void* node = 0;                                             // in_stack_00000018
    while (node != 0) {
        DoNukeSubtree(*(void**)node);
        void* next = *(void**)((char*)node + 4);
        operator_delete__(node);
        node = next;
    }
}

// ===========================================================================
// 0x00bc1b10  FUN_00bc1b10: reconcile the community's plant/editor species lists
// with the world species managers; drop the missing ones, then refresh the
// cargo slots and the zoo markers.
// ===========================================================================
// A growable vector of ResourceKey/pointer records: { begin, end, cap }.
struct KeyVector {
    void*    mpBegin;                                           // +0x00
    void*    mpEnd;                                             // +0x04
    void*    mpCap;                                             // +0x08
};

// Does the key vector already hold this 0xc-byte key?
static bool VecHasKey(KeyVector* v, ResourceKey* k)
{
    for (ResourceKey* it = (ResourceKey*)v->mpBegin; it != (ResourceKey*)v->mpEnd; ++it)
        if (it->mType == k->mType && it->mGroup == k->mGroup && it->mInstance == k->mInstance)
            return true;
    return false;
}

// Append a 0xc-byte key to the vector, growing it through the retail helper.
static void VecAppendKey(KeyVector* v, ResourceKey* k)
{
    char* slot = (char*)v->mpEnd;
    if (slot >= (char*)v->mpCap) {
        ((RcKeyVec*)v)->DoInsertKey(v->mpEnd, k);
    } else {
        v->mpEnd = slot + 0xc;
        if (slot != 0) {
            ((ResourceKey*)slot)->mType = k->mType;
            ((ResourceKey*)slot)->mGroup = k->mGroup;
            ((ResourceKey*)slot)->mInstance = k->mInstance;
        }
    }
}

// @ 0x00bc1b10
void __fastcall FUN_00bc1b10(void* thisptr, int, void* param_2)
{
    void* ctx = FUN_008414c0(param_2);
    void* mgr = FUN_00b3d420();
    void* owner = *(void**)((char*)param_2 + 0x13c);

    // --- pass 1: collect plant species keys that no longer resolve ---
    ResourceKey* p   = (ResourceKey*)((char*)owner + 0xbc);
    ResourceKey* end = (ResourceKey*)((char*)owner + 0xc0);
    KeyVector missing;
    missing.mpBegin = 0;
    missing.mpEnd = 0;
    missing.mpCap = 0;
    while (p != end) {
        if (((RcPlantMgr*)mgr)->GetSpeciesFromID(p) == 0) {
            char* slot = (char*)missing.mpEnd;
            if (slot >= (char*)missing.mpCap) {
                ((RcKeyVec*)&missing)->DoInsertKey(missing.mpEnd, p);
            } else {
                missing.mpEnd = slot + 0xc;
                if (slot != 0) {
                    ((ResourceKey*)slot)->mType = p->mType;
                    ((ResourceKey*)slot)->mGroup = p->mGroup;
                    ((ResourceKey*)slot)->mInstance = p->mInstance;
                }
            }
        }
        ++p;
    }
    // apply the removals to the cargo slots
    for (ResourceKey* it = (ResourceKey*)missing.mpBegin; it != (ResourceKey*)missing.mpEnd; ++it)
        ((RcCargo*)thisptr)->CargoSlotsUpdate(it, param_2);

    // --- pass 2: refresh the species profiles / editor species list ---
    void* setting = GetSetting9();
    void* owner2  = *(void**)((char*)param_2 + 0x13c);
    ResourceKey* e = (ResourceKey*)((char*)owner2 + 0xd0);
    ResourceKey* eend = (ResourceKey*)((char*)owner2 + 0xd4);
    KeyVector refreshed;
    refreshed.mpBegin = 0;
    refreshed.mpEnd = 0;
    refreshed.mpCap = 0;
    int presentCount = 0;
    int emptyCount = 0;
    while (e != eend) {
        void* prof = ((RcSpeciesMgr*)setting)->GetProfile(e);
        if (prof != 0) {
            if (*(uint32_t*)((char*)prof + 0x608) > 0)
                ++presentCount;
            else
                ++emptyCount;
        } else {
            char* slot = (char*)refreshed.mpEnd;
            if (slot >= (char*)refreshed.mpCap) {
                ((RcKeyVec*)&refreshed)->DoInsertKey(refreshed.mpEnd, e);
            } else {
                refreshed.mpEnd = slot + 0xc;
                if (slot != 0) {
                    ((ResourceKey*)slot)->mType = e->mType;
                    ((ResourceKey*)slot)->mGroup = e->mGroup;
                    ((ResourceKey*)slot)->mInstance = e->mInstance;
                }
            }
        }
        ++e;
    }
    (void)presentCount;
    (void)emptyCount;

    // --- reclassify every surviving key against the two world classes ---
    for (ResourceKey* it = (ResourceKey*)refreshed.mpBegin; it != (ResourceKey*)refreshed.mpEnd; ++it) {
        void* found = ((RcAc10a0*)FUN_00b3d450(0x5029da65))->FUN_00ac10a0();
        while (found != 0) {
            ResourceKey* k = (ResourceKey*)((char*)found + 0x504);
            if (VecHasKey(&refreshed, k))
                break;
            found = ((RcAc10a0*)FUN_00b3d450(0x5029da65))->FUN_00ac10a0();
        }
        if (found == 0)
            break;
        VecAppendKey(&refreshed, (ResourceKey*)((char*)found + 0x504));
    }

    FUN_00bbf2b0(param_2);
    if (refreshed.mpBegin != 0 && *(uint32_t*)((char*)refreshed.mpBegin - 4) != 0)
        operator_delete__((char*)refreshed.mpBegin - 4);
    if (refreshed.mpEnd != 0 && *(uint32_t*)((char*)refreshed.mpEnd - 4) != 0)
        operator_delete__((char*)refreshed.mpEnd - 4);
    if (missing.mpBegin != 0 && *(uint32_t*)((char*)missing.mpBegin - 4) != 0)
        operator_delete__((char*)missing.mpBegin - 4);
}

// ===========================================================================
// 0x00bc2070  FUN_00bc2070: activate this container and add its resource nodes
// ===========================================================================
// @ 0x00bc2070
void CityDisplayOwner::Activate(void* param_2, void* param_3)
{
    if (mActive44 == 0) {
        mActive44 = 1;
        mValue64 = 0;
        FUN_00bc0180(param_3);
        ((RcDisplay*)this)->FUN_00bc08d0(0);
        ((RcDisplay*)this)->FUN_00bc1b10(param_2);
        float f2 = ((RcDisplay*)param_2)->FUN_00c70a20(0);
        float f3 = ((RcDisplay*)param_2)->FUN_00c709d0(f2);
        ((RcDisplay*)this)->FUN_00bbcf00(param_2, f3);
        ((RcCityDisplay*)PlanetModel())->AddResourceNodes();
    }
}

// ===========================================================================
// 0x00bc20e0  FUN_00bc20e0: switch the container's active subject
// ===========================================================================
// @ 0x00bc20e0
void CityDisplayOwner::SetSubject(void* param_2)
{
    uint32_t cur = mSubject40;
    unsigned p2 = (unsigned)(size_t)param_2;
    if (p2 == cur)
        return;
    unsigned which;
    if (cur == 0xffffffffu || cur == 0x02ccd1d2u || cur == 0x01654c00u) {
        switch (p2 - 0x01654c01u) {
        case 0x0:
        case 0x1:
        case 0x3:
        case 0x5:
            which = 1;
            break;
        default:
            goto store;
        }
    } else {
        if (cur != 0x01654c08u)
            goto store;
        if ((int)p2 < 0x01654c01)
            goto store;
        if ((int)p2 > 0x01654c02 && p2 != 0x01654c04)
            goto store;
        which = 0;
    }
    Activate(cSPLivingUniverse_GetActivePlanet(), (void*)which);
    mFlag3c = 1;
store:
    mSubject40 = p2;
}

// ===========================================================================
// 0x00bc2180  FUN_00bc2180: release one sound slot
// ===========================================================================
// @ 0x00bc2180
void __fastcall FUN_00bc2180(SoundSlots* self, int, int i)
{
    if (i != 0) {
        void* h = self->mSlots[i].mpHandle;
        if (h != 0) {
            FUN_00572020(h, 0);
            self->mSlots[i].mpHandle = 0;
        }
        self->mSlots[i].mDistance = FLT_MAX_;
    }
}

// ===========================================================================
// 0x00bc21c0  FUN_00bc21c0: release every in-use sound slot
// ===========================================================================
// @ 0x00bc21c0
void __fastcall FUN_00bc21c0(SoundSlots* self, int)
{
    int i = 1;
    SoundSlots::Slot* p = &self->mSlots[i];
    do {
        if (i != 0) {
            void* h = p->mpHandle;
            if (h != 0) {
                void* at = EA_Audio_GetSystemAT();
                if (at != 0) {
                    ((void (__thiscall*)(void*, int))(*(void***)at)[0x38/4])(at, 0x347536b);
                    ((void (__thiscall*)(void*, int, void*))(*(void***)at)[0x40/4])(at, 0x3475385, h);
                    ((void (__thiscall*)(void*, int, int))(*(void***)at)[0x40/4])(at, 0x34753a0, 0);
                    ((void (__thiscall*)(void*))(*(void***)at)[0x58/4])(at);
                }
                p->mpHandle = 0;
            }
            p->mDistance = FLT_MAX_;
        }
        ++i;
        ++p;
    } while (i < 0x18);
}

// ===========================================================================
// 0x00bc2240  FUN_00bc2240: start a 3D sound in the first free slot
// ===========================================================================
// @ 0x00bc2240
int __fastcall FUN_00bc2240(SoundSlots* self, int, void* name, float f1, float f2, float f3)
{
    int i = 1;
    SoundSlots::Slot* p = &self->mSlots[i];
    do {
        if (p->mpHandle == 0) {
            void* at = EA_Audio_GetSystemAT();
            void* h;
            if (at != 0)
                h = ((void* (__thiscall*)(void*))(*(void***)at)[0x20/4])(at);
            else
                h = 0;
            self->mSlots[i].mpHandle = h;
            Start3dSoundByName(name, h, f1, f2, f3);
            return i;
        }
        ++i;
        ++p;
    } while (i < 0x18);
    return 0;
}

// ===========================================================================
// 0x00bc22b0  FUN_00bc22b0: minimum over the two distance blocks
// ===========================================================================
// @ 0x00bc22b0
float __fastcall FUN_00bc22b0(void* thisptr, int)
{
    float acc = FLT_MAX_;
    float* base = (float*)((char*)thisptr + 0x1c);
    int outer = 2;
    do {
        float* p = base;
        for (int k = 0; k < 8; ++k) {
            float v = p[k * 2];
            if (v < acc)
                acc = v;
        }
        base += 0x10;
        --outer;
    } while (outer != 0);
    float* r = (float*)((char*)thisptr + 0x94);
    int inner = 9;
    do {
        float v = *r;
        if (v < acc)
            acc = v;
        r += 2;
        --inner;
    } while (inner != 0);
    return (float)sqrt((double)acc);
}

// ===========================================================================
// 0x00bc23d0  FUN_00bc23d0: position one sound slot's listener
// ===========================================================================
// @ 0x00bc23d0
void __fastcall FUN_00bc23d0(SoundSlots* self, int, int i, float px, float py, float pz)
{
    if (i == 0)
        return;
    AudioSetListener3(self->mSlots[i].mpHandle, px, py, pz);
    if (GetCameraCtl() != 0) {
        float orient[3];
        float* q = (float*)((RcCamera*)GetCameraCtl())->GetTargetOrientation(orient);
        float dx = q[0] - px;
        float dy = q[1] - py;
        float dz = q[2] - pz;
        self->mSlots[i].mDistance = dx * dx + dy * dy + dz * dz;
    } else {
        self->mSlots[i].mDistance = FLT_MAX_;
    }
}

// ===========================================================================
// 0x00bc24c0  FUN_00bc24c0: classify a value against three thresholds
// ===========================================================================
// @ 0x00bc24c0
unsigned __stdcall FUN_00bc24c0(float value)
{
    if (kFlt156cfb8 > value)
        return 0;
    if (kFlt156cfbc > value)
        return 1;
    if (kFlt156cfc0 > value)
        return 2;
    if (kFlt156cfc4 > value)
        return 3;
    return 0;
}

// ===========================================================================
// 0x00bc2520  FUN_00bc2520: is the planet's rotation axis near-perpendicular?
// ===========================================================================
// @ 0x00bc2520
unsigned char __cdecl FUN_00bc2520(void* planet)
{
    if (((RcSimPlanet*)planet)->IsRotationNull() != 0)
        return 0;
    float* axis = (float*)((RcSimPlanet*)planet)->GetRotationAxis();
    float* up = (float*)((void* (__thiscall*)(void*))(*(void***)planet)[0x2c/4])(planet);
    float dot = up[0] * axis[0] + up[1] * axis[1] + up[2] * axis[2];
    float a = (float)fabs(dot);
    if (kFlt14666f0 > a)
        return 1;
    return 0;
}
