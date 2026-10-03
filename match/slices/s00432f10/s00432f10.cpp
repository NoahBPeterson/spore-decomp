// Slice s00432f10: a settings-keyed id remapper, a small weighted-slot table helper
// (init / find / normalize) and two routines that walk an owner's entry list, create
// resources through the global factory and accumulate slot weights.
//
// Built without optimization and without C++ EH: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
// Notes on /Od quirks used below:
//   - Pad<N>() reserves unused frame slots that the original's inlined helpers left behind.
//   - Local variable *names* affect the /Od stack slot order (hash order), so names such as
//     `j`, `num`, `used`, `pRes` are kept as found by brute force.

typedef unsigned int uint32_t;

template<int N> inline void Pad() { unsigned int s[N]; }

// ---------------------------------------------------------------------------
// Weighted slot table
// ---------------------------------------------------------------------------
struct WeightEntry { uint32_t id; float weight; };
struct WeightVector {
    WeightEntry* begin; WeightEntry* end; WeightEntry* cap;
    void Reserve(int n);   // 0x004338e0
    WeightEntry& At(int i) { return begin[i]; }
};

extern uint32_t g_slotIds[3];          // 0x013ebd5c
bool IsSpecialId(uint32_t id);         // 0x00433660
uint32_t __cdecl RemapId(uint32_t v);  // 0x00458eb0

// @ 0x00433660
bool IsSpecialId(uint32_t id)
{
    switch (id) {
    case 0x6329468: case 0x6329469: case 0x632946A: case 0x11B78A72:
        return true;
    }
    return false;
}

// @ 0x004336a0
int FindSlotIndex(uint32_t id)
{
    int count = 3;
    for (int i = 0; i < count; ++i) {
        if (id == g_slotIds[i])
            return i;
        else if (IsSpecialId(id) && IsSpecialId(g_slotIds[i]))
            return i;
    }
    return -1;
}

// @ 0x004335c0
void __cdecl InitSlotWeights(WeightVector* v, uint32_t seed)
{
    int count = 3;
    v->Reserve(count);
    for (int i = 0; i < count; ++i) {
        int a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;   // stack temps of inlined v->At(i)
        if (IsSpecialId(g_slotIds[i]))
            v->At(i).id = RemapId(seed);
        else
            v->begin[i].id = g_slotIds[i];
        v->begin[i].weight = 0.0f;
    }
}

// @ 0x00433720
void __cdecl NormalizeSlotWeights(WeightVector* v, float unused, float total)
{
    float sum = 0.0f;
    int n = v->end - v->begin;
    for (int i = 0; i < n; ++i)
        sum += v->begin[i].weight;
    if (sum > 0.0f) {
        if (sum < total / 3.0f)
            total = sum * 3.0f;
        for (int i = 0; i < n; ++i) {
            WeightEntry* e = &v->begin[i];
            v->begin[i].weight = e->weight * total / sum;
        }
    }
}

// ---------------------------------------------------------------------------
// Settings-keyed id remap (big switch; many ids map to themselves)
// ---------------------------------------------------------------------------
struct Settings { uint32_t pad[15]; int* flags; bool Has(int i) { return flags[i] != 0; } };
extern Settings* g_settings;           // 0x015fd918

// @ 0x00432f10
int RemapTypeId(int id)
{
    switch (id) {
    case 0xdfad9f51: return 0x1d2ec0a4;
    case 0x9ea3031a: {
        Settings* s = g_settings;
        if (s->Has(0x46)) return 0x5bf8f774;
        else return 0x465c50ba;
    }
    case 0x372e2c04: return 0x156276d1;
    case 0xccc35c46: return 0x9adf00a9;
    case 0x65672ade: return 0x37e82da1;
    case 0x4178b8e8: return 0xa56567f7;
    case 0x99e92f05: return 0x99e92f05;
    case 0x4e3f7777: return 0x4e3f7777;
    case 0xbdd15f3d: return 0xbdd15f3d;
    case 0x47c10953: return 0x8707be7d;
    case 0x72c49181: return 0x72c49181;
    case 0x7d433fad: return 0x7d433fad;
    case 0x8f963dcb: return 0x8f963dcb;
    case 0x441cd3e6: return 0x441cd3e6;
    case 0xf670aa43: return 0xf670aa43;
    case 0x2a5147a9: return 0x2a5147a9;
    case 0x1a4e0708: return 0x1a4e0708;
    case 0x9ad7d4aa: return 0x9ad7d4aa;
    case 0x1f2a25b6: return 0x1f2a25b6;
    case 0x449c040f: return 0x449c040f;
    case 0xbc1041e6: return 0xbc1041e6;
    case 0xc15695da: return 0xc15695da;
    case 0x2090a11b: return 0x2090a11b;
    case 0xc0b74287: return 0xc0b74287;
    case 0x98e03c0d: return 0x96b24187;
    case 0xbcd73e89: return 0x1c7eca95;
    case 0xb8669ec9: return 0x1c7eca95;
    case 0x37148141: return 0x1c7eca95;
    }
    return -1;
}

// ---------------------------------------------------------------------------
// Entry walkers (not byte-exact: stack slot layout of locals differs)
// ---------------------------------------------------------------------------
struct AllocTag { AllocTag() {} };
struct Alloc { int x, y; Alloc* Init(const AllocTag& tag); };   // 0x00429360
struct IntVec {
    int* mBegin; int* mEnd; int* mCap; Alloc mAlloc;
    void push_back(const int& v);   // 0x00454860
    void Free();                    // 0x00425990
    int* begin() { return mBegin; }
    int* end() { return mEnd; }
};
inline void DestroyRange(int* first, int* last) { for (; first < last; ++first) {} }
inline int* Find(int* first, int* last, const int& v)
{
    while (first != last && *first != v) ++first;
    return first;
}

struct RefObj { virtual void AddRef(); virtual void Release(); };
struct RefPtr {
    RefObj* mp;
    RefPtr(RefObj* x) : mp(x) {}
    void AddRef() { if (mp) mp->AddRef(); }
    RefObj** operator&() { if (mp) { RefObj* t = mp; mp = 0; t->Release(); } return &mp; }
    void Release() { if (mp) mp->Release(); }
};

struct Factory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void CreateInto(uint32_t a, uint32_t b, RefObj** out);   // slot 0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual RefObj* Create(uint32_t a, uint32_t b);                                      // slot 0x58
};
Factory* __cdecl GetFactory();                           // 0x00401010 / 0x0067de30
void __cdecl ApplyEntry(RefObj* o, WeightVector* w);     // 0x00433800

// Owner with an inline vector of 0x1d8-byte entries at +0x98.
struct Entry { uint32_t id0; uint32_t id1; uint32_t pad8; int other; char pad2[0x1d8 - 0x10]; };
struct EntryVec {
    Entry* mBegin; Entry* mEnd; Entry* mCap;
    int size() { return mEnd - mBegin; }
};
struct Owner {
    char pad0[0x18]; uint32_t key;
    char pad1[0x98 - 0x1c]; EntryVec entries;
    uint32_t GetKey() { return key; }
};

// @ 0x00433210
void ApplyOwnerEntries(Owner* o, WeightVector* w)
{
    if (o) {
        Entry* e;
        int j;
        int num;
        IntVec used;
        InitSlotWeights(w, o->GetKey());
        used.mBegin = 0; used.mEnd = 0; used.mCap = 0;
        used.mAlloc.Init(AllocTag());
        j = 0;
        num = o->entries.size();
        for (; j < num; ++j) {
            if (Find(used.begin(), used.end(), j) != used.end())
                continue;
            {
                e = &o->entries.mBegin[j];
                RefPtr pRes(GetFactory()->Create(e->id1, e->id0));
                pRes.AddRef();
                Pad<4>();
                ApplyEntry(pRes.mp, w);
                used.push_back(j);
                if (e->other != -1) {
                    int temp = e->other;
                    used.push_back(temp);
                }
                pRes.Release();
            }
        }
        NormalizeSlotWeights(w, 0.0f, 20.0f);
        DestroyRange(used.mBegin, used.mEnd);
        used.Free();
        Pad<3>();
    }
}

// Second owner type: entries fetched through accessors, resources created into an out-ref.
struct Entry2 {
    char pad[0x1c]; uint32_t a; uint32_t b; char pad2[0x3e0 - 0x24]; int c; int d;
    uint32_t GetA() { return a; }
    uint32_t GetB() { return b; }
    int GetC() { return c; }
    int GetD() { return d; }
};
struct Owner2 {
    char pad0[0x58]; uint32_t key;
    uint32_t GetKey() { return key; }
    int GetCount();                  // 0x004accf0
    Entry2* GetEntry(int i);         // 0x004accb0
};

// @ 0x004333c0
void ApplyOwnerEntries2(Owner2* o, WeightVector* w)
{
    InitSlotWeights(w, o->GetKey());
    IntVec ids; ids.mBegin = 0; ids.mEnd = 0; ids.mCap = 0;
    ids.mAlloc.Init(AllocTag());
    int iEntry = 0;
    int entryCount = o->GetCount();
    for (; iEntry < entryCount; ++iEntry) {
        Entry2* pe = o->GetEntry(iEntry);
        if (Find(ids.begin(), ids.end(), (int&)pe) != ids.end())
            continue;
        {
            RefPtr pModel(0);
            GetFactory()->CreateInto(pe->GetA(), pe->GetB(), &pModel);
            ApplyEntry(pModel.mp, w);
            ids.push_back((int&)pe);
            Pad<2>();
            if (pe->GetC() != 0) {
                int linked = pe->GetC();
                ids.push_back(linked);
            } else if (Pad<2>(), pe->GetD() != 0) {
                int tt2 = pe->GetD();
                ids.push_back(tt2);
            }
            pModel.Release();
        }
    }
    NormalizeSlotWeights(w, 0.0f, 20.0f);
    Pad<2>();
    DestroyRange(ids.mBegin, ids.mEnd);
    ids.Free();
    Pad<3>();
}
