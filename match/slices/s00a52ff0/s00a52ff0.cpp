// Slice s00a52ff0 - EA::Audio::Eapd (Pure Data) fracplay: fixed pool, voice list, parameter map.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00a52ff0.h"
#include <new>
#include <string.h>

#define NOINLINE __declspec(noinline)

namespace EA { namespace Audio { namespace Eapd {

// Address of the (fixed-pool) allocator vftable, materialized as a constant so
// allocator-owning structs can be initialized without a real symbol reference.
extern void* g_allocVftable[];       // 0x01454fac
extern void* g_paramIterVftable[]; // 0x01454fdc

// @ 0xa52ff0
NOINLINE bool Group::Init(void* param_2, void* param_3, int nAtoms, void* argv)
{
    if (nAtoms > 0) {
        Symbol loc;
        getSymbol(&loc);
        mLocation = loc;
        vectorSymbolResize(&mSamples, nAtoms);
        for (int i = 0; i < nAtoms; ++i) {
            mSamples.mpBegin[i] = *atom_gensym(&loc, argv);
            argv = (char*)argv + 0xc;
        }
        return true;
    }

    int count;
    getSymbol((Symbol*)&count);
    EapdSystem* sys = (EapdSystem*)getEapdSystemData();
    if (!sys->Load((Symbol*)&count, param_3, param_2, param_3, &count, 0))
        return false;

    if (count <= 4) {
        sys->Destroy(&count);
        return false;
    }

    Symbol loc;
    getSymbol(&loc);
    mLocation = loc;
    unsigned n = *(unsigned*)argv;
    vectorSymbolResize(&mSamples, n);

    char* p = (char*)argv + 4;
    char* end = (char*)argv + count;
    unsigned i = 0;
    while (i < n) {
        if (p >= end)
            break;
        mSamples.mpBegin[i] = *gensym(&loc, p);
        while (*p)
            ++p;
        ++p;
        ++i;
    }
    bool ok = (i == n);
    sys->Destroy(&count);
    return ok;
}

// @ 0xa531b0
NOINLINE FixedPool::~FixedPool()
{
    if (mpPoolBegin != 0)
        mInitAllocator.v0c(mpPoolBegin);
}

// @ 0xa53210
NOINLINE bool FixedPool::Init(uint32_t nodeSize, int count, InitAllocator* a1, InitAllocator* a2)
{
    if (mpPoolBegin != 0) {
        mInitAllocator.v0c(mpPoolBegin);
        mpPoolBegin = 0;
    }
    if (nodeSize >= 4) {
        mnNodeSize = nodeSize;
        uint32_t total = mnNodeSize * (unsigned)count;
        mInitAllocator.mpCoreAllocator = a1->field4;
        mOverflowAllocator.mpCoreAllocator = a2->field4;
        char* begin = (char*)mInitAllocator.v08(total);
        char* end = begin + total;
        mpPoolBegin = begin;
        mpPoolEnd = end;
        mnCurrentSize = 0;
        mnPeakSize = 0;
        mpHead = 0;
        if (begin != 0 && (unsigned)count > 0) {
            mpHead = begin;
            char* p = begin;
            while (p < end - nodeSize) {
                *(char**)p = p + nodeSize;
                p = p + nodeSize;
            }
            *(char**)p = 0;
        }
    }
    return mpPoolBegin != 0;
}

// @ 0xa532b0
NOINLINE void* FixedPool::Alloc()
{
    void* p = mpHead;
    if (p != 0) {
        mpHead = *(void**)p;
    } else {
        p = mOverflowAllocator.v08(mnNodeSize);
    }
    if (p != 0) {
        ++mnCurrentSize;
        if (mnCurrentSize > mnPeakSize)
            mnPeakSize = mnCurrentSize;
    }
    return p;
}

// @ 0xa53310
NOINLINE void artists_play_setname(t_play* x, unsigned hash, const char* name)
{
    if (x->bIsDynamic) {
        if (x->play.mName.mHash != hash)
            x->play.mnLastGroupID = 0xffffffff;
        x->play.mName.mHash = hash;
        x->play.mName.mpName = name;
    }
}

// @ 0xa53360
NOINLINE bool FixedHashtableAllocator::InitBuckets(unsigned count, InitAllocator* p1, InitAllocator* p2)
{
    if (mpBucketBuffer != 0) {
        mInitAllocator.v0c(mpBucketBuffer);
        mpBucketBuffer = 0;
    }
    unsigned nb = (unsigned)(long long)((float)count * 1.3333334f);
    mnBucketCount = nb;
    if (nb < 3)
        mnBucketCount = 3;
    else
        mnBucketCount = roundLog2(nb) + 1;
    if (mnBucketCount * 4 == 0x18)
        return Init(0x18, count + 1, p1, p2);
    if (Init(0x18, count, p1, p2)) {
        mpBucketBuffer = mInitAllocator.v08(mnBucketCount * 4);
        return mpBucketBuffer != 0;
    }
    return false;
}

// @ 0xa53450
NOINLINE void VoiceList::Clear()
{
    VoiceNode* node = (VoiceNode*)mNode.mpNext;
    while (node != (VoiceNode*)&mNode) {
        VoiceNode* cur = node;
        node = (VoiceNode*)node->mpNext;
        --mPool.mnCurrentSize;
        if ((void*)cur >= mPool.mpPoolBegin && (void*)cur < mPool.mpPoolEnd) {
            *(void**)cur = mPool.mpHead;
            mPool.mpHead = cur;
        } else {
            mPool.mOverflowAllocator.v0c(cur);
        }
    }
}

// @ 0xa53490
NOINLINE void ParamTable::FreeBuckets(ParamNode** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        ParamNode* node = buckets[i];
        while (node != 0) {
            ParamNode* cur = node;
            node = cur->mpNext;
            if (cur != (ParamNode*)mAllocator.mpBucketBuffer) {
                --mAllocator.mnCurrentSize;
                if ((void*)cur >= mAllocator.mpPoolBegin && (void*)cur < mAllocator.mpPoolEnd) {
                    *(void**)cur = mAllocator.mpHead;
                    mAllocator.mpHead = cur;
                } else {
                    mAllocator.mOverflowAllocator.v0c(cur);
                }
            }
        }
        buckets[i] = 0;
    }
}

// @ 0xa53500
typedef void* VoiceManager;

void Play::SetPaused(bool b)
{
    if (mbPaused != b) {
        mbPaused = b;
        VoiceNode* n = (VoiceNode*)mVoices.mNode.mpNext;
        while (n != (VoiceNode*)&mVoices.mNode) {
            unsigned v = n->mValue;
            if (((bool (__thiscall*)(VoiceManager, unsigned))(*(void***)mVoiceManager)[8])((VoiceManager)mVoiceManager, v))
                ((void (__thiscall*)(VoiceManager, unsigned, bool))(*(void***)mVoiceManager)[4])((VoiceManager)mVoiceManager, v, b);
            n = (VoiceNode*)n->mpNext;
        }
    }
}

// @ 0xa53560
NOINLINE void artists_play_setpausedf(t_play* x, float f)
{
    x->play.SetPaused(f != 0.0f);
}

// @ 0xa535a0
NOINLINE void VoiceList::PopFront()
{
    VoiceNode* cur = (VoiceNode*)mNode.mpNext;
    cur->mpPrev->mpNext = cur->mpNext;
    cur->mpNext->mpPrev = cur->mpPrev;
    --mPool.mnCurrentSize;
    if ((void*)cur >= mPool.mpPoolBegin && (void*)cur < mPool.mpPoolEnd) {
        *(void**)cur = mPool.mpHead;
        mPool.mpHead = cur;
    } else {
        mPool.mOverflowAllocator.v0c(cur);
    }
}

// @ 0xa535e0
NOINLINE ParamNode* ParamTable::AllocNode(const ParamPair* v)
{
    ParamNode* node = (ParamNode*)mAllocator.mpHead;
    if (node != 0) {
        mAllocator.mpHead = *(ParamNode**)node;
    } else {
        node = (ParamNode*)mAllocator.mOverflowAllocator.v08(mAllocator.mnNodeSize);
    }
    if (node != 0) {
        ++mAllocator.mnCurrentSize;
        if (mAllocator.mnCurrentSize > mAllocator.mnPeakSize)
            mAllocator.mnPeakSize = mAllocator.mnCurrentSize;
        node->mValue = *v;
    }
    node->mpNext = 0;
    return node;
}

// @ 0xa53640
NOINLINE ParamIter::ParamIter(ParamTable* t)
{    mpVftable = g_paramIterVftable;
    ParamNode** p = t->mpBucketArray;
    mpNode = *p;
    mpBucket = p;
    if (mpNode == 0) {
        mpBucket = p + 1;
        while (*mpBucket == 0) {
            mpBucket += 1;
        }
        mpNode = *mpBucket;
    }
    ParamNode** end = t->mpBucketArray + t->mnBucketCount;
    mpLast = *end;
    mpBucketEnd = end;
    mpTable = t;}

// @ 0xa536a0
NOINLINE bool ParamIter::Next(Symbol* out, AtomValue* value)
{
    bool r = false;
    if (mpNode != mpLast) {
        *out = mpNode->mValue.first;
        const AtomValue* src = (const AtomValue*)&mpNode->mValue.a_type;
        switch (src->a_type) {
        case 1:
            value->a_type = 0;
            value->a_float = src->a_float;
            r = true;
            break;
        case 2:
            value->a_type = 1;
            value->a_sym = src->a_sym;
            value->a_sym2 = src->a_sym2;
            r = true;
            break;
        default:
            r = false;
            break;
        }
        mpNode = mpNode->mpNext;
        while (mpNode == 0) {
            mpBucket = mpBucket + 1;
            mpNode = *mpBucket;
        }
    }
    return r;
}

// @ 0xa53730
NOINLINE void ParamTable::Bucket(void** out, const Symbol* key, BucketTag t, void* a4)
{
    (void)t; (void)a4;
    ParamNode** base = mpBucketArray;
    unsigned idx = key->mHash % mnBucketCount;
    ParamNode** slot = base + idx;
    ParamNode* node = *slot;
    while (node != 0) {
        if (node->mValue.first.mHash == key->mHash) {
            out[0] = node;
            out[1] = slot;
            return;
        }
        node = node->mpNext;
    }
    slot = base + mnBucketCount;
    out[0] = *slot;
    out[1] = slot;
}

// @ 0xa53790
NOINLINE VoiceList::~VoiceList()
{
    Clear();
}
// @ 0xa537e0
NOINLINE void Play::UpdatePlaying()
{
    VoiceNode* node = (VoiceNode*)mVoices.mNode.mpNext;
    while (node != (VoiceNode*)&mVoices.mNode) {
        unsigned v = node->mValue;
        if (((bool (__thiscall*)(VoiceManager, unsigned))(*(void***)mVoiceManager)[8])((VoiceManager)mVoiceManager, v))
            ((void (__thiscall*)(VoiceManager, unsigned))(*(void***)mVoiceManager)[3])((VoiceManager)mVoiceManager, v);
        node = (VoiceNode*)node->mpNext;
        VoiceNode* cur = (VoiceNode*)node->mpPrev;
        cur->mpPrev->mpNext = cur->mpNext;
        cur->mpNext->mpPrev = cur->mpPrev;
        --mVoices.mPool.mnCurrentSize;
        if ((void*)cur >= mVoices.mPool.mpPoolBegin && (void*)cur < mVoices.mPool.mpPoolEnd) {
            *(void**)cur = mVoices.mPool.mpHead;
            mVoices.mPool.mpHead = cur;
        } else {
            mVoices.mPool.mOverflowAllocator.v0c(cur);
        }
    }
    mnBusyVoices = 0;
}
// @ 0xa53860
NOINLINE void Play::SetPlaying()
{
    VoiceNode* node = (VoiceNode*)mVoices.mNode.mpNext;
    while (node != (VoiceNode*)&mVoices.mNode) {
        bool playing = ((bool (__thiscall*)(VoiceManager, unsigned))(*(void***)mVoiceManager)[8])
                           ((VoiceManager)mVoiceManager, node->mValue);
        node = (VoiceNode*)node->mpNext;
        if (!playing) {
            VoiceNode* cur = (VoiceNode*)node->mpPrev;
            cur->mpPrev->mpNext = cur->mpNext;
            cur->mpNext->mpPrev = cur->mpPrev;
            --mVoices.mPool.mnCurrentSize;
            if ((void*)cur >= mVoices.mPool.mpPoolBegin && (void*)cur < mVoices.mPool.mpPoolEnd) {
                *(void**)cur = mVoices.mPool.mpHead;
                mVoices.mPool.mpHead = cur;
            } else {
                mVoices.mPool.mOverflowAllocator.v0c(cur);
            }
            --mnBusyVoices;
        }
    }
}

// @ 0xa538d0
NOINLINE void artists_play_updateplaying(t_play* x)
{
    x->play.UpdatePlaying();
}

// @ 0xa538e0
NOINLINE ParamTable::~ParamTable()
{
    FreeBuckets(mpBucketArray, mnBucketCount);
    unsigned n = mnBucketCount;
    ParamNode** arr = mpBucketArray;
    mnElementCount = 0;
    if (n > 1 && arr != (ParamNode**)mAllocator.mpBucketBuffer) {
        --mAllocator.mnCurrentSize;
        if ((void*)arr >= mAllocator.mpPoolBegin && (void*)arr < mAllocator.mpPoolEnd) {
            *(void**)arr = mAllocator.mpHead;
            mAllocator.mpHead = arr;
        } else {
            mAllocator.mOverflowAllocator.v0c(arr);
        }
    }
}

struct VoiceListCtor {
    VoiceListCtor(FixedPool* src);
};

// Same construction routine, declared only at this call site: the unwinder must
// be kept for a callee whose body is not visible (the original TU did not see it).
struct VoiceListCtorExternal {
    void Construct(FixedPool* src);
};

// @ 0xa539d0
NOINLINE int artists_play_step(void* self)
{    int r = 0;
    if (self != 0) {
        t_play* x = *(t_play**)((char*)self + 0xc);
        if (x != 0) {
            Play* p = &x->play;
            p->SetPlaying();
            if (p->mnBusyVoices <= 0) {
                x->pUpdateCallback = 0;
                outlet_bang(x->pDoneOutlet);
                r = 0;
            } else {
                r = 1;
            }
        }
    }
    return r;}

// @ 0xa53a20
NOINLINE void VoiceList::PushBack(ListLink* anchor, const unsigned* value2)
{
    VoiceNode* node = (VoiceNode*)mPool.mpHead;
    if (node != 0) {
        mPool.mpHead = node->mpNext;
    } else {
        node = (VoiceNode*)mPool.mOverflowAllocator.v08(mPool.mnNodeSize);
    }
    if (node != 0) {
        ++mPool.mnCurrentSize;
        if (mPool.mnCurrentSize > mPool.mnPeakSize)
            mPool.mnPeakSize = mPool.mnCurrentSize;
    }
    if (&node->mValue != 0)
        node->mValue = *value2;
    node->mpNext = anchor;
    node->mpPrev = anchor->mpPrev;
    anchor->mpPrev->mpNext = node;
    anchor->mpPrev = node;
}

// @ 0xa53a80
NOINLINE bool Play::GetParam(unsigned key, ParamPair* out)
{
    ParamTable* table = *(ParamTable**)((char*)this + 0x14);
    struct HashIter { ParamNode* mpNode; ParamNode** mpBucket; };
    HashIter it;
    unsigned keyCopy = key;
    table->Bucket((void**)&it, (const Symbol*)&keyCopy, BucketTag(), out);
    ParamNode* node = it.mpNode;
    bool r = false;
    if (node != (ParamNode*)table->mpBucketArray[table->mnBucketCount]) {
        const AtomValue* v = (const AtomValue*)&node->mValue.a_type;
        switch (v->a_type) {
        case 1:
            out->a_type = 0;
            out->a_float = v->a_float;
            r = true;
            break;
        case 2:
            out->a_type = 1;
            out->a_sym = v->a_sym;
            out->a_sym2 = v->a_sym2;
            r = true;
            break;
        default:
            r = false;
            break;
        }
    }
    return r;
}

// @ 0xa53b20
NOINLINE Play::~Play()
{
    UpdatePlaying();
}

// @ 0xa53b90
NOINLINE bool Play::Init(unsigned maxVoices, unsigned maxParams, void* a3, void* a4)
{
    InitAllocator rec;
    rec.vftable = (void*)0x1454fac;
    rec.field4 = 0;
    rec.name = g_eapdAlloc;
    bool r = mVoices.mPool.Init(0xc, maxParams, &rec, &rec);
    if (r) {
        r = FUN_00a65e40(a4, (void*)maxVoices, &rec) != 0;
    }
    mnMaxParameters = maxVoices;
    mnMaxVoices = maxParams;
    return r;
}

// @ 0xa53c20
NOINLINE ParamPair* ParamTable::LocateOrInsert(const Symbol* key)
{
    struct HashIter { ParamNode* mpNode; ParamNode** mpBucket; };
    struct HashPair { HashIter first; bool second; };
    HashPair it;
    HashFind(&it, key);
    if (it.first.mpNode == (ParamNode*)mpBucketArray[mnBucketCount]) {
        ParamPair tmp;
        tmp.a_type = 0;
        tmp.a_sym = 0;
        tmp.a_sym2 = 0;
        tmp.first = *key;
        HashInsert(&it, &tmp, ParamTable::DoInsertTrueType());
    }
    return (ParamPair*)((char*)it.first.mpNode + 8);
}

// @ 0xa53c90
struct VoiceListInitHelper {
    void* InitFromName(void* name);
};

NOINLINE void* VoiceListInitHelper::InitFromName(void* name)
{
    FixedPool local;
    local.mInitAllocator.mpNamePtr = name;
    local.mOverflowAllocator.mpNamePtr = name;
    *(void**)&local.mInitAllocator = g_allocVftable;
    *(void**)&local.mOverflowAllocator = g_allocVftable;
    local.mInitAllocator.mpCoreAllocator = 0;
    local.mOverflowAllocator.mpCoreAllocator = 0;
    local.mnNodeSize = 0;
    local.mpPoolBegin = 0;
    local.mpPoolEnd = 0;
    local.mpHead = 0;
    local.mnCurrentSize = 0;
    local.mnPeakSize = 0;
    ((VoiceListCtorExternal*)this)->Construct(&local);
    return this;
}

// @ 0xa53970
NOINLINE VoiceListCtor::VoiceListCtor(FixedPool* src)
{
    VoiceList* dst = (VoiceList*)this;
    memset(&dst->mNode, 0, sizeof(dst->mNode));
    *(void**)&dst->mPool.mInitAllocator = g_allocVftable;
    dst->mPool.mInitAllocator.mpCoreAllocator = src->mInitAllocator.mpCoreAllocator;
    dst->mPool.mInitAllocator.mpNamePtr = src->mInitAllocator.mpNamePtr;
    *(void**)&dst->mPool.mOverflowAllocator = g_allocVftable;
    dst->mPool.mOverflowAllocator.mpCoreAllocator = src->mOverflowAllocator.mpCoreAllocator;
    dst->mPool.mOverflowAllocator.mpNamePtr = src->mOverflowAllocator.mpNamePtr;
    dst->mPool.mnNodeSize = src->mnNodeSize;
    dst->mPool.mpPoolBegin = src->mpPoolBegin;
    dst->mPool.mpPoolEnd = src->mpPoolEnd;
    dst->mPool.mpHead = src->mpHead;
    dst->mPool.mnCurrentSize = src->mnCurrentSize;
    dst->mPool.mnPeakSize = src->mnPeakSize;
    dst->mNode.mpNext = &dst->mNode;
    dst->mNode.mpPrev = &dst->mNode;
}

// @ 0xa53d20
NOINLINE struct InstanceDesc {
    void* p0;   // +0x00
    void* p1;   // +0x04
    void* p2;   // +0x08
};

void Play::StartVoice(void* a1, void* a2, float time)
{
    SetPlaying();
    if (mnBusyVoices >= mnMaxVoices && !mbSteal)
        return;

    double start = GetVoiceStartTime(time);
    unsigned voiceId = 0;
    ParamIter it(&mParameters);
    InstanceDesc desc;
    desc.p1 = 0;
    desc.p2 = 0;
    FUN_00a649b0(&desc.p1);
    desc.p0 = FUN_00a649a0();

    VoiceManager vm = (VoiceManager)mVoiceManager;
    if (!((bool (__thiscall*)(VoiceManager, void*, void*, void*, double, ParamIter*, InstanceDesc, unsigned*))
          (*(void***)vm)[2])(vm, a1, a2, 0, start, &it, desc, &voiceId))
        return;

    if (mnBusyVoices == mnMaxVoices) {
        VoiceNode* first = (VoiceNode*)mVoices.mNode.mpNext;
        ((void (__thiscall*)(VoiceManager, unsigned))(*(void***)vm)[3])(vm, first->mValue);
        mVoices.PopFront();
        --mnBusyVoices;
    }
    mVoices.PushBack(&mVoices.mNode, &voiceId);
    ++mnBusyVoices;
    if (mbPaused) {
        unsigned last = ((VoiceNode*)mVoices.mNode.mpPrev)->mValue;
        ((void (__thiscall*)(VoiceManager, unsigned, int))(*(void***)vm)[4])(vm, last, 1);
    }
}

// @ 0xa53e60
NOINLINE void Play::ParamEvent(Symbol key, ParamPair* atom)
{
    SetPlaying();
    if (mbUpdatePlaying && mnBusyVoices != 0) {
        VoiceManager vm = (VoiceManager)mVoiceManager;
        unsigned last = ((VoiceNode*)mVoices.mNode.mpPrev)->mValue;
        bool ok;
        if (atom->a_type == 1) {
            ok = ((bool (__thiscall*)(VoiceManager, unsigned, unsigned, const char*, float))
                  (*(void***)vm)[7])(vm, last, key.mHash, key.mpName, atom->a_float);
        } else if (atom->a_type == 2) {
            ok = ((bool (__thiscall*)(VoiceManager, unsigned, unsigned, const char*, float, const char*))
                  (*(void***)vm)[6])(vm, last, key.mHash, key.mpName, atom->a_float, atom->a_sym2);
        } else {
            char buf[1000];
            atom_string(atom, buf, 1000);
            return;
        }
        if (!ok || mParameters.mnElementCount >= mnMaxParameters) {
            char buf[1000];
            atom_string(atom, buf, 1000);
            return;
        }
    }
    ParamPair* slot = mParameters.LocateOrInsert(&key);
    slot->a_type = atom->a_type;
    slot->a_float = atom->a_float;
    slot->a_sym2 = atom->a_sym2;
}

// Force emission of out-of-line destructors that are otherwise inlined away.
void DestroyVoiceListOutOfLine(VoiceList* p) { p->~VoiceList(); }

}}}  // namespace
