// Slice s00a52ff0 - EA::Audio::Eapd (Pure Data) fracplay: fixed pool, voice list, parameter map.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00a52ff0.h"

#define NOINLINE __declspec(noinline)

namespace EA { namespace Audio { namespace Eapd {

// Address of the (fixed-pool) allocator vftable, materialized as a constant so
// allocator-owning structs can be initialized without a real symbol reference.
extern void* const g_allocVftable;

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
        mAllocator.mpHead = node->mpNext;
    } else {
        node = (ParamNode*)mAllocator.mOverflowAllocator.v08(mAllocator.mnNodeSize);
    }
    if (node != 0) {
        ++mAllocator.mnCurrentSize;
        if (mAllocator.mnCurrentSize > mAllocator.mnPeakSize)
            mAllocator.mnPeakSize = mAllocator.mnCurrentSize;
        node->mValue = *v;
        node->mpNext = 0;
    }
    return node;
}

// @ 0xa53640
NOINLINE ParamIter::ParamIter(ParamTable* t)
{
    mpTable = t;
    mpVftable = (void*)0x1454fdc;
    ParamNode** p = t->mpBucketArray;
    ParamNode* n = *p;
    mpNode = n;
    mpBucket = p;
    if (n == 0) {
        mpBucket = p + 1;
        ParamNode* m = p[1];
        while (m == 0) {
            mpBucket += 1;
            m = *mpBucket;
        }
        mpNode = *mpBucket;
    }
    ParamNode** end = t->mpBucketArray + t->mnBucketCount;
    mpLast = *end;
    mpBucketEnd = end;
}

// @ 0xa536a0
NOINLINE unsigned ParamIter::Next(Symbol* out, ParamPair* value)
{
    ParamNode* node = mpNode;
    if (node == mpLast)
        return 0;
    *out = node->mValue.first;
    unsigned r;
    switch (node->mValue.a_type) {
    case 1:
        value->a_type = 0;
        value->a_float = node->mValue.a_float;
        r = 1;
        break;
    case 2:
        value->a_type = 1;
        value->a_float = node->mValue.a_float;
        value->a_sym2 = node->mValue.a_sym2;
        r = 1;
        break;
    default:
        r = 0;
        break;
    }
    ParamNode* next = node->mpNext;
    mpNode = next;
    while (next == 0) {
        mpBucket = mpBucket + 1;
        next = *mpBucket;
        mpNode = next;
    }
    return r;
}

// @ 0xa53730
NOINLINE void ParamTable::Bucket(void** out, const Symbol* key, void* a3, void* a4)
{
    (void)a3; (void)a4;
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

// @ 0xa53970
NOINLINE void VoiceList_CopyCtor(VoiceList* dst, FixedPool* src)
{
    dst->mNode.mpNext = 0;
    dst->mNode.mpPrev = 0;
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

// @ 0xa539d0
NOINLINE int artists_play_step(void* self)
{
    int r = 0;
    if (self != 0) {
        t_play* x = *(t_play**)((char*)self + 0xc);
        if (x != 0) {
            ((Play*)((char*)x + 0x28))->SetPlaying();
            if (x->play.mnBusyVoices == 0) {
                x->pUpdateCallback = 0;
                outlet_bang(x->pDoneOutlet);
            } else {
                r = 1;
            }
        }
    }
    return r;
}

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
NOINLINE unsigned Play::GetParam(void* outAtom, Symbol key)
{
    ParamNode* node = 0;
    mParameters.Bucket((void**)&node, &key, 0, 0);
    ParamPair* out = (ParamPair*)outAtom;
    if (node == (ParamNode*)mParameters.mpBucketArray[mParameters.mnBucketCount])
        return 0;
    if (node->mValue.a_type == 1) {
        out->a_type = 0;
        out->a_float = node->mValue.a_float;
        return 1;
    }
    if (node->mValue.a_type == 2) {
        out->a_type = 1;
        out->a_float = node->mValue.a_float;
        out->a_sym2 = node->mValue.a_sym2;
        return 1;
    }
    return 0;
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
    unsigned it[2];
    FUN_00a3b2c0(it, key);
    ParamNode* found = (ParamNode*)it[0];
    if (found == (ParamNode*)mpBucketArray[mnBucketCount]) {
        ParamPair tmp;
        tmp.first = *key;
        tmp.a_type = 0;
        tmp.a_float = 0.0f;
        tmp.a_sym2 = 0;
        FUN_00a65bb0(this, &tmp, 0);
    }
    return (ParamPair*)((char*)found + 8);
}

// @ 0xa53c90
NOINLINE struct PoolForCtor {
    void*  vftable0;   // +0x00
    void*  field4;     // +0x04
    void*  name0;      // +0x08
    void*  vftable1;   // +0x0c
    void*  field4b;    // +0x10
    void*  name1;      // +0x14
    uint32_t nodeSize; // +0x18
    void*  poolBegin;  // +0x1c
    void*  poolEnd;    // +0x20
    void*  head;       // +0x24
    uint32_t curSize;  // +0x28
    uint32_t peakSize; // +0x2c
};

void* VoiceList_InitFromName(void* dst, void* name)
{
    PoolForCtor local;
    local.vftable0 = 0;
    local.field4 = 0;
    local.name0 = name;
    local.vftable1 = (void*)0;
    local.field4b = 0;
    local.name1 = name;
    local.nodeSize = 0;
    local.poolBegin = 0;
    local.poolEnd = 0;
    local.head = 0;
    local.curSize = 0;
    local.peakSize = 0;
    VoiceList_CopyCtor((VoiceList*)dst, (FixedPool*)&local);
    ((FixedPool*)&local)->~FixedPool();
    return dst;
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

void* const EA::Audio::Eapd::g_allocVftable = (void*)0x1454fac;
