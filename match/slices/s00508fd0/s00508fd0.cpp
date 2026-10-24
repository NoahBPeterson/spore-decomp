// w1g1 slice s00508fd0 -- skin/animation table helpers for the big container.
//
// Flags: /Od /Ob1 /MD /Gy /TP (integer; /arch:SSE where floats appear).

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

void ea_delete(void* p);                       // operator_delete__
void rangeErase(void* begin, void* end);       // 0x004769b0
void rangeC0(uint32_t n, void* p);             // 0x004746c0
void Func5daf0();                              // 0x0045daf0
void Func5402c0(void* p);                      // 0x005402c0
void Func5470(void* p);                        // 0x00540470
void Func73f30(void* p);                       // 0x00473f30
void CleanupElement(void* p);                  // 0x00507b30

// __thiscall element cleanup (the retail CleanupElement: pointer in ecx).
typedef void (__thiscall* CleanupElementFn)(void* self);

extern const signed char gTriOffset[3];        // @ 0x013f18d0 (triangle step table)

// ---------------------------------------------------------------------------
// @ 0x00509850  (two-integer key equality)
// ---------------------------------------------------------------------------
struct Key {
    int a, b;
    uint8_t Equals(int x, int y);
};
uint8_t Key::Equals(int x, int y)
{
    int result = (a == x) && (b == y);
    return (uint8_t)result;
}

// ---------------------------------------------------------------------------
// @ 0x00509ec0  (build a 2-dword pair; index bit flips the sign bit)
// ---------------------------------------------------------------------------
uint32_t* __cdecl MakePair(uint32_t* out, int base, uint32_t idx)
{
    uint32_t a = *(uint32_t*)(base + (((idx >> 1) + 1) % 3) * 4);
    uint32_t b = *(uint32_t*)(base + (((idx >> 1) + 2) % 3) * 4);
    if ((idx & 1) != 0)
        a = a ^ 0x80000000u;
    out[0] = a;
    out[1] = b;
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00509da0  (expand a 2x2 float range)
// ---------------------------------------------------------------------------
struct Range {
    char pad[0x58];
    float lo0, hi0, lo1, hi1;   // 0x58,0x5c,0x60,0x64
    void Expand(float* p);
};
void Range::Expand(float* p)
{
    float* lo = &lo0;
    if (*p <= *lo && *lo != *p) lo = p;
    lo0 = *lo;

    float* hi = &hi0;
    if (*hi <= *p && *p != *hi) hi = p;
    hi0 = *hi;

    float* lo2 = &lo1;
    if (p[1] <= *lo2 && *lo2 != p[1]) lo2 = p + 1;
    lo1 = *lo2;

    float* hi2 = &hi1;
    float v = p[1];
    if (*hi2 <= v && v != *hi2) hi2 = p + 1;
    hi1 = *hi2;
}

// ---------------------------------------------------------------------------
// @ 0x00509c80  (insert an entry into a slot table, returns slot index)
// ---------------------------------------------------------------------------

// The two intrusive vectors the body touches: +0x58 is the id list (u32 per
// entry), +0x30 and +0x124 are 8-byte {a,b} pair lists.
struct IdVecU32 {
    uint32_t* mBegin;   // +0x00
    uint32_t* mEnd;     // +0x04
    uint32_t* mCap;     // +0x08
};
struct PairVec8 {
    uint32_t* mBegin;   // +0x00
    uint32_t* mEnd;     // +0x04
    uint32_t* mCap;     // +0x08
};

// __thiscall helpers: the pair-list append (this = the list itself) and the
// key-range widen (this = the id list at +0x30, argument is the freshly built
// pair).
typedef void (__thiscall* Func73f30Fn)(void* self, void* pair);      // va 00473f30
typedef void (__thiscall* Func5402c0Fn)(void* self, const void* v);  // va 005402c0

struct Table {
    char      pad00[0x08];   // +0x00
    int       mIdBase;       // +0x08  (MakePair base for the id block)
    char      pad0c[0x24];   // +0x0c
    PairVec8  mPairs30;      // +0x30  (widen target for Expand)
    char      pad3c[0x1c];   // +0x3c
    IdVecU32  mIds;          // +0x58  (per-index runtime id)
    char      pad64[0x1c];   // +0x64
    uint32_t* mSlotOfIdx;    // +0x80  (idx -> slot map)
    char      pad84[0xa0];   // +0x84
    PairVec8  mPairs124;     // +0x124 (slot -> {key, idx} entries)
    char      pad130[0x88];  // +0x130
    int*      mBaseTab;      // +0x1b8 (id -> base pair)

    int Insert(int idx, uint32_t* key, int slot);
};

int Table::Insert(int idx, uint32_t* key, int slot)
{
    int* base = (int*)((char*)mBaseTab + (int)mIds.mBegin[idx] * 8);
    uint32_t k = key[0];
    if (slot == -1) {
        uint32_t tmp[2];
        uint32_t* r = MakePair(tmp, (int)mIds.mBegin[idx] * 0xc + mIdBase, key[1]);
        ((Func73f30Fn)Func73f30)(&mPairs30, r);
        ((Func5402c0Fn)Func5402c0)(&mPairs124, &k);
        slot = (int)(((char*)mPairs30.mEnd - (char*)mPairs30.mBegin) >> 3) - 1;
        mSlotOfIdx[idx] = (uint32_t)slot;
    } else {
        mPairs124.mBegin[slot * 2] = k;
        mPairs124.mBegin[slot * 2 + 1] = (uint32_t)idx;
    }
    base[0] = (int)key[0];
    base[1] = slot;
    ((Range*)key)->Expand((float*)((char*)mPairs30.mBegin + slot * 8));
    return slot;
}

// ---------------------------------------------------------------------------
// @ 0x00509b20  (table teardown)
// ---------------------------------------------------------------------------

// Intrusive u32 vector (SP::SimpleVector<unsigned>): fill-to-n and erase are
// __thiscall, so they are modelled as members and reached through a pointer to
// the member at its real offset.
struct TVecU32 {
    uint32_t* mBegin;   // +0x00
    uint32_t* mEnd;     // +0x04
    uint32_t* mCap;     // +0x08
    void Assign(uint32_t n, const uint32_t* value);   // va 004746c0
    uint32_t* Erase(uint32_t* first, uint32_t* last); // va 004769b0
};

// Intrusive pointer vector (the +0xe4 element list).
struct TVecPtr {
    int* mBegin;        // +0x00
    int* mEnd;          // +0x04
    int* mCap;          // +0x08
    int* Erase(int* first, int* last);   // va 004769b0
};

// The teardown target; only the touched members are named.
struct TableCtx {
    char    pad00[0x58];    // +0x00
    TVecU32 mIds;           // +0x58  (count drives the fill)
    char    pad64[0x1c];    // +0x64
    TVecU32 mSlots;         // +0x80  (filled to n with 0xffffffff)
    char    pad8c[0x58];    // +0x8c
    TVecPtr mElems;         // +0xe4  (elements deleted in the loop)
    char    padf0[0x20];    // +0xf0
    TVecU32 mThirds;        // +0x110 (filled to n/3 with 0)
};

void __fastcall TableTeardown(TableCtx* self)
{
    uint32_t n = (uint32_t)(self->mIds.mEnd - self->mIds.mBegin);
    uint32_t third = n / 3;
    uint32_t a = 0xffffffffu;
    self->mSlots.Assign(n, &a);

    uint32_t end = (uint32_t)(self->mElems.mEnd - self->mElems.mBegin);
    for (uint32_t i = 0; i < end; ++i) {
        int p = self->mElems.mBegin[i];
        if (p != 0) {
            ((CleanupElementFn)CleanupElement)((void*)p);
            ea_delete((void*)p);
        }
    }
    self->mElems.Erase(self->mElems.mBegin, self->mElems.mEnd);
    self->mThirds.Erase(self->mThirds.mBegin, self->mThirds.mEnd);
    uint32_t b = 0;
    self->mThirds.Assign(third, &b);
}

// ---------------------------------------------------------------------------
// @ 0x005098a0  (rebuild the lookup vectors)
//
// Walks the +0xbc id vector; for each id it collects the closed chain
// reachable through +0x94 into a scratch set of {node, light-tag} pairs
// (tag = whether the node's +0x58 weight is below its triangle-step
// neighbour), then repeatedly pairs the head with the first differently
// tagged member, relinking +0x94 and erasing both, and finally self-links
// whatever remains.  The id vector and the scratch set are emptied last.
// ---------------------------------------------------------------------------

// Scratch-set element: a node id plus a one-byte tag.
struct PairIF {
    int  mNode;      // +0x00
    char mTag;       // +0x04
    char pad05[3];   // +0x05
};

// Allocator blob handed to the scratch vector's constructor (never written
// by the retail body, so it is left uninitialised here too).
struct Alloc {
    char mState;
};

// Intrusive vector of PairIF (the original SP::VectorIF).
struct VSet {
    PairIF* mBegin;      // +0x00
    PairIF* mEnd;        // +0x04
    PairIF* mCap;        // +0x08
    void Ctor(const Alloc& alloc);                  // va 00540470
    void Erase(PairIF* first, PairIF* last);        // va 00530c80
    void PushBack(const PairIF& value);             // va 005402c0
    void EraseAt(PairIF* where);                    // va 0050e200
    bool Empty();                                   // va 00526430
    void Dtor();                                    // va 0045daf0
};

// Intrusive vector of unsigned (the original SP::SimpleVector<unsigned>).
struct SimpleVecU32 {
    uint32_t* mBegin;   // +0x00
    uint32_t* mEnd;     // +0x04
    uint32_t* mCap;     // +0x08
    uint32_t* Erase(uint32_t* first, uint32_t* last);   // va 004769b0
};

// The entity this helper rebuilds; only the touched members are named.
struct LookupTable {
    char         pad00[0x58];   // +0x00
    uint32_t*    mWeights;      // +0x58
    char         pad5c[0x38];   // +0x5c
    int*         mLink;         // +0x94
    char         pad98[0x24];   // +0x98
    SimpleVecU32 mIds;          // +0xbc

    void Rebuild();
};

// @ 0x005098a0
void LookupTable::Rebuild()
{
    Alloc alloc;
    VSet set;
    set.Ctor(alloc);

    for (uint32_t i = 0; ; ++i) {
        if ((uint32_t)(mIds.mEnd - mIds.mBegin) <= i)
            break;

        uint32_t node = mIds.mBegin[i];
        uint32_t start = node;

        set.Erase(set.mBegin, set.mEnd);
        do {
            PairIF pair;
            pair.mNode = (int)node;
            pair.mTag = (char)(mWeights[node] <
                               mWeights[node + (int)gTriOffset[node % 3]]);
            set.PushBack(pair);
            node = (uint32_t)mLink[node];
        } while (node != start);

        while ((uint32_t)((set.mEnd - set.mBegin) >> 3) >= 2) {
            int a = set.mBegin[0].mNode;
            int b = -1;
            char tag = set.mBegin[0].mTag;

            uint32_t count = (uint32_t)(set.mEnd - set.mBegin) >> 3;
            uint32_t j = 1;
            for (; j < count; ++j) {
                if (tag != set.mBegin[j].mTag) {
                    b = set.mBegin[j].mNode;
                    break;
                }
            }
            if (j == count)
                break;

            mLink[a] = b;
            mLink[b] = a;
            set.EraseAt(&set.mBegin[j]);
            set.EraseAt(set.mBegin);
        }

        while (!set.Empty()) {
            int last = set.mEnd[-1].mNode;
            set.mEnd -= 1;
            mLink[last] = last;
        }
    }

    mIds.Erase(mIds.mBegin, mIds.mEnd);
    for (PairIF* it = set.mBegin; it < set.mEnd; ++it) {
    }
    set.Dtor();
}

// ---------------------------------------------------------------------------
// 0x00508fd0 / 0x00509450 -- the two table builders remain PARTIAL; see
// partial.txt and work/match/scratch_s00508fd0_fixlog.txt.
// ---------------------------------------------------------------------------