// Slice s005628d0: SP::cSPObjectTemplateDB matching/priority-constraint driver methods.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s0055ce80/s0055ce80.h"

namespace SP {

void FUN_004769b0(void* a, void* b);
void FUN_00562280(void* self, void* c);
void FUN_005625a0(void* self, int flag);
bool FUN_00562510(void* self, void* out);
void FUN_00565380(void* out, void* a, void* b, void* c, void* d, void* e, void* f);
void FUN_00565410(void* out, void* a, void* b, void* c, void* d, void* e, void* f);
void FUN_00565df0(void* self);
void FUN_00565500(void* self, void* first, int count);
void FUN_00565560(void* self);
void FUN_00554020(void* out, void* val);
void FUN_0055c2e0(void* a, void* b);

struct CandidateDBStub {
    void AssignCandidates(void* out, void* pRange);
    bool TryFilterCandidates(void* a, void* b, void* pRange);
};

// ---------------------------------------------------------------------------
// Reconstructed types for the driver methods.
// ---------------------------------------------------------------------------

struct Constraint {
    uint32_t mParameter;
    uint32_t mType;
    int mMin;
    int mMax;
    char mConstraints[0x14];
};

struct ConstraintCursor {
    void* mpNext;
    void* mpCur;
    ConstraintCursor(const Constraint& c) : mpNext((void*)(&c + 1)), mpCur((void*)&c) {}
};

struct PriorityConstraint {
    uint32_t mnTag;
    Constraint mConstraint;
};

typedef eastl::vector<Constraint, eastl::sp_vector_allocator> ConstraintVec;

struct InsertIter {
    void* container;
    uint32_t* it;
    InsertIter(void* c, uint32_t* i) : container(c), it(i) {}
    InsertIter(const InsertIter& x) : container(x.container), it(x.it) {}
};
InsertIter set_intersection(uint32_t* f1, uint32_t* l1, uint32_t* f2, uint32_t* l2, InsertIter r); // 0x565380
InsertIter set_difference(uint32_t* f1, uint32_t* l1, uint32_t* f2, uint32_t* l2, InsertIter r);  // 0x565410

// eastl::vector<uint32_t> and vector_set<uint32_t> as used here (0x14 / 0x18 bytes).
struct U32Vec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAlloc[2];
    bool empty() const;                                   // 0x526430
    void erase(uint32_t* first, uint32_t* last);          // 0x4769b0
    void swap(U32Vec& x);                                 // 0x565df0
    void insertOut(void* out, uint32_t value);            // 0x554020
};
struct U32Set : public U32Vec {
    uint32_t mCompare;
};

struct DqIter {
    uint32_t f[4];
    void* Deref();                                        // 0x5658b0
    void Inc();                                           // 0x5677f0
};

struct PodDeque {
    void Ctor(void* tag);                                 // 0x567680
    void Init2();                                         // 0x567780
    ~PodDeque();                                          // 0x5656f0
    size_t Size();                                        // 0x565780
    void* Front();                                        // 0x5657e0
    void PopFront();                                      // 0x565810
    void PushBack(void* outIter, const void* value);      // 0x565850
    void Begin(DqIter* out);                              // 0x565740
    void End(DqIter* out);                                // 0x565760
};

struct SpVecV3 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAlloc[2];
    void Erase(void* first, void* last);                  // 0x50f740
    void Reserve(size_t n);                               // 0x41e4d0
    void PushBack(const void* value);                     // 0x4e19a0
    bool Empty() const;                                   // 0x526430
};

struct TraitQuery {
    float Compute(void* a, void* feature);                // 0x5709b0
};

struct Pod8 { float mValue; uint32_t mIndex; };

extern uint32_t DAT_015e4460;
extern uint32_t DAT_015e4444;
extern uint32_t DAT_015e3ffc;
extern uint32_t DAT_015e4344;
extern uint32_t DAT_015e3f38;
extern uint32_t DAT_015e3ff8;
extern uint32_t DAT_015e3f04;
extern const uint32_t DAT_013f4b10;

struct LookupAsset {
    ResourceKey mKey;
    char pad0c[0x50 - 0x0c];
};

struct LookupDB {
    char pad00[0x14];
    eastl::vector<LookupAsset, eastl::sp_vector_allocator> mAssetList;   // +0x14
    eastl::vector_set<uint32_t> mFreeList;                               // +0x28
    char pad40[0x64 - 0x40];
    U32Set mCandidates;                                                  // +0x64
    U32Set mSomeSet;                                                     // +0x7c
    char pad94[0x12c - 0x94];
    U32Set mIndices;                                                     // +0x12c
    U32Set mResultSet;                                                   // +0x144
    U32Set mScratchSet;                                                  // +0x15c
    char pad174[0x258 - 0x174];
    eastl::vector<PriorityConstraint, eastl::sp_vector_allocator> mPriority;  // +0x258

    void Add(U32Vec* pResults, const Constraint* c);                 // 0x562280
    void Set(U32Vec* list, const Constraint* p, unsigned n);         // 0x5655f0
    void AddFirst(U32Vec* list, ConstraintCursor c, unsigned n);     // 0x565560
    void SetCursor(U32Vec* list, ConstraintCursor c, unsigned n);    // 0x565660
    void ExcludeCandidates(U32Vec* cand, int force);                 // 0x5625a0
    bool GetAssetKeys(U32Vec* indices, void* keys);                  // 0x562510
    bool RandomizeFirstN(void* a, int b);                            // 0x55c2e0
    int FindAssetIndex(const ResourceKey& key);

    void FUN_005628d0(U32Vec* pList);
    void FUN_00562d50(void* out, void* pRange);
    bool FUN_00562e90(void* a, void* b, void* pRange);
    bool FUN_00562f50(void* a, void* b, const ResourceKey* pKey, void* pRange);
    void FUN_00563090(void* a, U32Vec* range, unsigned n, PodDeque* out);
    bool FUN_005632d0(PodDeque* dq, SpVecV3* out);
    int FUN_00563370(uint32_t modelType);
};

// @ 0x005628d0  (large reassignment driver)
void LookupDB::FUN_005628d0(U32Vec* pList) {
    if (pList->empty())
        return;
    {
        U32Vec* scratch = &mScratchSet;
        scratch->erase(scratch->mpBegin, scratch->mpEnd);
    }
    PriorityConstraint* it = mPriority.mpEnd;
    PriorityConstraint* begin = mPriority.mpBegin;
    for (; mScratchSet.empty() && it != begin; it -= 1) {
        {
            U32Vec* results = &mResultSet;
            results->erase(results->mpBegin, results->mpEnd);
        }
        Add(&mResultSet, &(it - 1)->mConstraint);
        set_intersection(pList->mpBegin, pList->mpEnd, mResultSet.mpBegin, mResultSet.mpEnd,
                         InsertIter(&mScratchSet, mScratchSet.mpBegin));
        ExcludeCandidates(&mScratchSet, 1);
    }
    if (mScratchSet.empty()) {
        {
            U32Vec* results = &mResultSet;
            results->erase(results->mpBegin, results->mpEnd);
        }
        set_difference(mCandidates.mpBegin, mCandidates.mpEnd, pList->mpBegin, pList->mpEnd,
                       InsertIter(&mResultSet, mResultSet.mpBegin));
        for (uint32_t* p = pList->mpBegin; p != pList->mpEnd; ++p) {
            char outIter[8];
            mSomeSet.insertOut(outIter, *p);
        }
    } else {
        pList->swap(mScratchSet);
    }
}

// @ 0x00562b80
void CandidateDBStub::AssignCandidates(void* out, void* pRange) {
    void* this_ = this;
    FUN_004769b0(*(void**)((char*)this_ + 0x12c), *(void**)((char*)this_ + 0x130));
    int* r = (int*)pRange;
    FUN_00565500((char*)this_ + 0x12c, (void*)*r, (r[1] - *r) / 0x24);
    FUN_00562510((char*)this_ + 0x12c, out);
}

// @ 0x00562c00
bool FUN_00562c00(void* self_, void* out, Constraint constraint) {
    LookupDB* self = (LookupDB*)self_;
    ConstraintCursor cur(constraint);
    {
        U32Vec* list = &self->mIndices;
        list->erase(list->mpBegin, list->mpEnd);
    }
    self->AddFirst(&self->mIndices, cur, 0x14);
    return self->GetAssetKeys(&self->mIndices, out);
}

// @ 0x00562ca0
bool CandidateDBStub::TryFilterCandidates(void* a, void* b, void* pRange) {
    void* this_ = this;
    FUN_004769b0(*(void**)((char*)this_ + 0x12c), *(void**)((char*)this_ + 0x130));
    int* r = (int*)pRange;
    FUN_00565500((char*)this_ + 0x12c, (void*)*r, (r[1] - *r) / 0x24);
    if (!FUN_00562510((char*)this_ + 0x12c, a))
        return false;
    FUN_0055c2e0(a, b);
    return true;
}

// @ 0x00562d50
void LookupDB::FUN_00562d50(void* out, void* pRange) {
    int p30;
    int n10;
    int begin;
    int t32;
    U32Vec* t25 = &mIndices;
    t25->erase(t25->mpBegin, t25->mpEnd);
    int p32 = (int)(((ConstraintVec*)pRange)->mpEnd - ((ConstraintVec*)pRange)->mpBegin);
    Constraint* n30 = ((ConstraintVec*)pRange)->mpBegin;
    Set(&mIndices, n30, (unsigned)p32);
    FUN_005628d0(&mIndices);
    GetAssetKeys(&mIndices, out);
}

// @ 0x00562de0
bool FUN_00562de0(void* self_, void* out, Constraint constraint) {
    LookupDB* self = (LookupDB*)self_;
    ConstraintCursor cur(constraint);
    {
        U32Vec* list = &self->mIndices;
        list->erase(list->mpBegin, list->mpEnd);
    }
    self->SetCursor(&self->mIndices, cur, 0x14);
    self->FUN_005628d0(&self->mIndices);
    return self->GetAssetKeys(&self->mIndices, out);
}

// @ 0x00562e90
bool LookupDB::FUN_00562e90(void* a, void* b, void* pRange) {
    int p30;
    int n10;
    int begin;
    int t32;
    U32Vec* t25 = &mIndices;
    t25->erase(t25->mpBegin, t25->mpEnd);
    int p32 = (int)(((ConstraintVec*)pRange)->mpEnd - ((ConstraintVec*)pRange)->mpBegin);
    Constraint* n30 = ((ConstraintVec*)pRange)->mpBegin;
    Set(&mIndices, n30, (unsigned)p32);
    FUN_005628d0(&mIndices);
    return GetAssetKeys(&mIndices, a) && RandomizeFirstN(a, (int)b);
}

// @ 0x00562f50
bool LookupDB::FUN_00562f50(void* a, void* b, const ResourceKey* pKey, void* pRange) {
    U32Vec* list = &mIndices;
    list->erase(list->mpBegin, list->mpEnd);
    int count = (int)(((ConstraintVec*)pRange)->mpEnd - ((ConstraintVec*)pRange)->mpBegin);
    Constraint* first = ((ConstraintVec*)pRange)->mpBegin;
    Set(&mIndices, first, (unsigned)count);
    ExcludeCandidates(&mIndices, 0);
    int idx = FindAssetIndex(*pKey);
    if (idx == -1)
        return GetAssetKeys(&mIndices, a) && RandomizeFirstN(a, (int)b);
    char tag;
    char dqBuf[0x28];
    PodDeque* dq = (PodDeque*)dqBuf;
    dq->Ctor(&tag);
    dq->Init2();
    FUN_00563090((void*)((char*)mAssetList.mpBegin + 0x10 + idx * 0x50), &mIndices,
                 (unsigned)b, dq);
    bool result = FUN_005632d0(dq, (SpVecV3*)a);
    dq->~PodDeque();
    return result;
}

// @ 0x00563090
void LookupDB::FUN_00563090(void* a, U32Vec* range, unsigned n, PodDeque* out) {
    uint32_t* it = range->mpBegin;
    uint32_t* end = range->mpEnd;
    for (; it != end; ++it) {
        uint32_t idx = *it;
        void* feature = (void*)((char*)mAssetList.mpBegin + 0x10 + idx * 0x50);
        float v = ((TraitQuery*)((char*)this + 0x174))->Compute(a, feature);
        if (0x7f800000u < (*(uint32_t*)&v & 0x7fffFFFFu))
            v = 3.4028234663852886e+38f;
        if ((unsigned)out->Size() < n) {
            Pod8 e;
            e.mValue = v;
            e.mIndex = idx;
            char outIter[0x10];
            out->PushBack(outIter, &e);
        } else {
            float front = *(float*)out->Front();
            if (front > v) {
                out->PopFront();
                Pod8 e;
                e.mValue = v;
                e.mIndex = idx;
                char outIter[0x10];
                out->PushBack(outIter, &e);
            }
        }
    }
}

struct LookupDB;
static inline bool KeyNotEqual(const LookupAsset* a, const ResourceKey* k) {
    return !(a->mKey.mInstanceID == k->mInstanceID && a->mKey.mTypeID == k->mTypeID &&
             a->mKey.mGroupID == k->mGroupID);
}

// @ 0x005631e0  (asset lookup by resource key)
int LookupDB::FindAssetIndex(const ResourceKey& key) {
    LookupAsset* pAsset = mAssetList.begin();
    LookupAsset* end = mAssetList.end();
    for (; pAsset != end && KeyNotEqual(pAsset, &key); ++pAsset) {
    }
    uint32_t index = pAsset - mAssetList.begin();
    if (pAsset == end || mFreeList.find(index) != mFreeList.end())
        return -1;
    return index;
}

// @ 0x005632d0
bool LookupDB::FUN_005632d0(PodDeque* dq, SpVecV3* out) {
    DqIter p30;
    DqIter n10;
    int begin;
    int t32;
    int t25;
    int p32;
    int n30;
    int n37;
    uint32_t buf;
    int owner;
    int n6;
    out->Erase(out->mpBegin, out->mpEnd);
    out->Reserve(dq->Size());
    dq->Begin(&n10);
    dq->End(&p30);
    for (; n10.f[0] != p30.f[0]; n10.Inc()) {
        buf = *(uint32_t*)((char*)n10.Deref() + 4);
        out->PushBack((const void*)&mAssetList[buf]);
    }
    return !out->Empty();
}

// @ 0x00563370
int LookupDB::FUN_00563370(uint32_t modelType) {
    if (!(DAT_015e4460 & 1)) {
        DAT_015e4460 |= 1;
        (&DAT_015e4444)[0] = DAT_015e3ffc;
        (&DAT_015e4444)[1] = DAT_015e4344;
        (&DAT_015e4444)[2] = DAT_015e3f38;
        (&DAT_015e4444)[3] = DAT_015e3ff8;
        {
            uint32_t v = 0;
            v = (v & 0x3fffffff) | 0x40000000;
            v = (v & 0xff00ffff) | ((0x8a & 0xff) << 16);
            v = (v & 0xffff00ff) | ((0x00 & 0xff) << 8);
            (&DAT_015e4444)[4] = v;
        }
        (&DAT_015e4444)[5] = DAT_015e3f04;
        {
            uint32_t v = 0;
            v = (v & 0x3fffffff) | 0x40000000;
            v = (v & 0xff00ffff) | ((0xc0 & 0xff) << 16);
            v = (v & 0xffff00ff) | ((0xc2 & 0xff) << 8);
            (&DAT_015e4444)[6] = v;
        }
    }
    uint32_t i = 0;
    int result = 0;
    while (i < 7 && result == 0) {
        int mapped;
        if (modelType == (&DAT_015e4444)[i])
            mapped = (int)(&DAT_013f4b10)[i];
        else
            mapped = 0;
        ++i;
        result = mapped;
    }
    return result;
}

}
