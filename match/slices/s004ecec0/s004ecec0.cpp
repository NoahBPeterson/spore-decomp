// w1g1 slice s004ecec0 -- editor validity entry compaction/reorder helpers.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
//
// Three /Od functions (1111 / 1218 / 575 bytes) that walk the 0x1d8-byte
// resource entry vector and compact/reorder it.

typedef unsigned int uint32_t;

struct Flags128 {
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline void set(uint32_t i, bool value) {
        if (i < 128) {
            if (value) DoGetWord(i) |= 1u << (i % 32);
            else DoGetWord(i) &= ~(1u << (i % 32));
        }
    }
};

struct FlagWord {
    unsigned int a : 8;
    unsigned int b : 8;
    unsigned int c : 8;
    unsigned int d : 6;
    unsigned int e : 2;
};

struct Block {
    uint32_t group;                 // +0x00
    uint32_t instance;              // +0x04
    int      parent;                // +0x08
    uint32_t symmetric;             // +0x0c
    char     pad0[0xd4 - 0x10];
    int      mNumPaintRegions;      // +0xd4
    char     pad1[0xf8 - 0xd8];
    uint32_t mPaintIDs[8];          // +0xf8
    char     pad2[0x1d8 - 0x118];
};

struct EntryVec {
    char* mpBegin;
    char* mpEnd;
    Block& operator[](int idx) { return *(Block*)(mpBegin + idx * 0x1d8); }
    int size() const { return (int)(mpEnd - mpBegin) / 0x1d8; }
};

struct PropertyList {
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};

template <class T>
struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    ~AutoRefCount() { if (mp) mp->Release(); }
    void AddRef() { if (mp) mp->AddRef(); }
    void** AsPPVoidParam();            // 0x0041d870
    T** AsPPTypeParam() { return (T**)AsPPVoidParam(); }
};

struct PropertyManager_ {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** out);  // +0x2c
};

struct Manager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21();
    virtual void* Find(int a, int b);   // +0x58
};

PropertyManager_* PropertyManager();                        // 0x0067de30
uint32_t RemapTypeId(uint32_t id);                          // 0x00432f10
extern uint32_t g_15daa00;                                  // 0x015daa00
void* GetMgr401010();                                       // 0x00401010
bool GetBoolProperty(PropertyList* p, uint32_t id, bool* out);   // 0x00407190

static inline uint32_t MakePaintKey(unsigned c, unsigned b)
{
    int base, prev, cur;            // (unused: reserve the helper's remaining frame slots)
    FlagWord f = {0};
    f.e = 1;
    f.c = c;
    f.b = b;
    (void)base; (void)prev; (void)cur;
    return *(uint32_t*)&f;
}

// @ 0x004ecec0
bool FUN_004ecec0(void* res, Flags128* flags)
{
    bool p13 = false;                                            // skip
    uint32_t p18 = *(uint32_t*)((char*)res + 0x18);              // config
    AutoRefCount<PropertyList> p;                                // propList
    p.AddRef();
    PropertyManager()->GetPropertyList(RemapTypeId(p18), g_15daa00, p.AsPPTypeParam());
    if (!p.mp) {
        if (flags) flags->set(3, true);
        return false;
    }
    if (p.mp) GetBoolProperty(p.mp, 0x300de90b, &p13);
    if (p13) goto valid;
    {
        int n34;                                                 // i
        int p9;                                                  // size
        EntryVec* t18;                                           // pv
        uint32_t n10;                                            // key
        t18 = (EntryVec*)((char*)res + 0x98);
        n10 = MakePaintKey(0x6a, 2);
        n34 = 0;
        p9 = t18->size();
        for (; n34 < p9; n34++) {
            int v36 = (*t18)[n34].mNumPaintRegions;               // numIds
            for (int v14 = 0; v14 < v36; v14++) {                 // j
                if ((*t18)[n34].mPaintIDs[v14] == 0) {
                    if (flags) flags->set(3, true);
                    return false;
                } else {
                    if (!((Manager*)GetMgr401010())->Find((*t18)[n34].mPaintIDs[v14], n10)) {
                        if (flags) flags->set(3, true);
                        return false;
                    }
                }
            }
        }
    }
valid:
    if (flags) flags->set(3, false);
    return true;
}

// @ 0x004ed320
bool FUN_004ed320(char* res, Flags128* flags)
{
    EntryVec* p15 = (EntryVec*)(res + 0x98);
    int iEntry = 0;
    int size = (int)(p15->mpEnd - p15->mpBegin) / 0x1d8;
    for (; iEntry < size; iEntry++) {
        Manager* n35 = (Manager*)GetMgr401010();
        char* p12 = p15->mpBegin + iEntry * 0x1d8;
        char* v18 = p15->mpBegin + iEntry * 0x1d8;
        PropertyList* prop = (PropertyList*)n35->Find(*(int*)(v18 + 4), *(int*)p12);
        if (!prop) {
            if (flags) flags->set(6, true);
            return false;
        }
        bool canBeParentless = true;
        GetBoolProperty(prop, 0x8e31d974, &canBeParentless);
        bool other = true;
        GetBoolProperty(prop, 0x6a96f17, &other);
        bool bNoParent = (canBeParentless == 0 && other != 0);
        bool bUnused = false;
        int parent = *(int*)(p15->mpBegin + iEntry * 0x1d8 + 8);
        if (parent < 0 || parent >= size) {
            if (bNoParent) goto invalidParents;
        }
        bool reserved = (*(unsigned char*)(p15->mpBegin + iEntry * 0x1d8 + 0x81)) ? true : false;
        int sym = *(int*)(p15->mpBegin + iEntry * 0x1d8 + 0xc);
        if (sym >= 0 && sym < size) {
            if (*(int*)(p15->mpBegin + sym * 0x1d8 + 0xc) != iEntry) {
                if (flags) flags->set(6, true);
                return false;
            }
            int symParent = *(int*)(p15->mpBegin + sym * 0x1d8 + 8);
            if (symParent >= 0 && symParent < size) {
                if (!reserved) {
                    if (symParent != *(int*)(p15->mpBegin + iEntry * 0x1d8 + 8)) {
                        char* pSymParent = p15->mpBegin + symParent * 0x1d8;
                        if (*(int*)(pSymParent + 0xc) !=
                            *(int*)(p15->mpBegin + iEntry * 0x1d8 + 8)) {
                            if (flags) flags->set(6, true);
                            return false;
                        }
                    }
                }
            }
        }
        continue;
    invalidParents:
        if (flags) flags->set(6, true);
        return false;
    }
    if (flags) flags->set(6, false);
    return true;
}

// @ 0x004ed7f0
bool FUN_004ed7f0(void* res, Flags128* flags)
{
    EntryVec* p = (EntryVec*)((char*)res + 0x98);
    int i = 0;
    int n;
    n = p->size();
    for (; i < n; i++) {
        uint32_t sym = (*p)[i].symmetric;
        if (sym < (uint32_t)p->size()) {
            if ((*p)[sym].symmetric != (uint32_t)i) {
                if (flags) flags->set(15, true);
                return false;
            }
        } else if (sym != 0xffffffff) {
            if (flags) flags->set(15, true);
            return false;
        }
    }
    if (flags) flags->set(15, false);
    return true;
}
