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
    int result;
    if (a == x && b == y)
        result = 1;
    else
        result = 0;
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
struct Table {
    char pad[0x200];
    int Insert(int idx, uint32_t* key, int slot);
};
int Table::Insert(int idx, uint32_t* key, int slot)
{
    int* base = (int*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + idx * 4) * 8);
    uint32_t k = *key;
    if (slot == -1) {
        uint8_t tmp[8];
        uint32_t* r = MakePair((uint32_t*)tmp, *(int*)(*(int*)((char*)this + 0x58) + idx * 4) * 0xc + *(int*)((char*)this + 8), key[1]);
        Func73f30(r);
        Func5402c0(&k);
        slot = ((*(int*)((char*)this + 0x34) - *(int*)((char*)this + 0x30)) >> 3) - 1;
        *(int*)(*(int*)((char*)this + 0x80) + idx * 4) = slot;
    } else {
        int t = *(int*)((char*)this + 0x124);
        *(uint32_t*)(t + slot * 8) = k;
        *(int*)(t + 4 + slot * 8) = idx;
    }
    base[0] = *key;
    base[1] = slot;
    return slot;
}

// ---------------------------------------------------------------------------
// @ 0x00509b20  (table teardown)
// ---------------------------------------------------------------------------
void __fastcall TableTeardown(int self)
{
    uint32_t n = (uint32_t)(*(int*)(self + 0x5c) - *(int*)(self + 0x58)) >> 2;
    uint32_t third = n / 3;
    uint32_t a = 0xffffffffu;
    rangeC0(n, &a);

    uint32_t end = (uint32_t)(*(int*)(self + 0xe8) - *(int*)(self + 0xe4)) >> 2;
    for (uint32_t i = 0; i < end; ++i) {
        int p = *(int*)(*(int*)(self + 0xe4) + i * 4);
        if (p != 0) {
            CleanupElement((void*)p);
            ea_delete((void*)p);
        }
    }
    rangeErase((void*)(self + 0xe4), (void*)(self + 0xe8));
    rangeErase((void*)(self + 0x110), (void*)(self + 0x114));
    uint32_t b = 0;
    rangeC0(third, &b);
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