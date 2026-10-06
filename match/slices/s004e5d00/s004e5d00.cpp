// w1g1 slice s004e5d00 -- editor capability/property id helpers.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
void* operator new(unsigned int size, const char* pName, int flags = 0, unsigned debugFlags = 0, const char* pFile = 0, int line = 0); // 0xf473a0

// ---- shared types for the verb-icon builders ----
struct PropertyList {
    virtual void AddRef();   // +0
    virtual void Release();  // +4
};

// EA::AutoRefCount: ctor AddRefs a non-null pointer; AsPPVoidParam releases then exposes the slot.
template <class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    AutoRefCount(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount() { if (mp) mp->Release(); }
    T** AsPPVoidParam() { if (mp) { T* t = mp; mp = 0; t->Release(); } return &mp; }
};
// The PropertyList flavour has its AsPPVoidParam out of line (0x0041d870).
struct PropListRef {
    PropertyList* mp;
    PropListRef(PropertyList* p) : mp(p) { if (mp) mp->AddRef(); }
    ~PropListRef() { if (mp) mp->Release(); }
    PropertyList** AsPPVoidParam();   // 0x0041d870
};

struct PropertyManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual bool GetPropertyList(uint32_t propID, uint32_t groupID, void* out); // +0x2c
};
PropertyManager* GetPropertyManager();   // 0x0067de30 (SP::PropertyManager)

struct CapabilityManager {
    static uint32_t __cdecl GetPropIDForAbility(uint32_t id, int flag);  // 0x00459370
};

// Retail cSPEditorVerbIconData (0xC4 bytes; ctor at 0x005e5a70).
struct cSPEditorVerbIconData {
    cSPEditorVerbIconData();        // 0x005e5a70
    virtual void AddRef();          // +0
    virtual void Release();         // +4
    virtual void v2();
    virtual void v3();
    virtual void SetPropertyList(PropertyList* pl); // +0x10
    char pad[0x14];
    float mLevel;                   // +0x18
    float mMaxLevel;                // +0x1c
    char pad2[0xc4 - 0x20];
};
typedef AutoRefCount<cSPEditorVerbIconData> VerbIconRef;
struct IconVec {                    // eastl::vector<AutoRefCount<cSPEditorVerbIconData>>
    void* mpBegin; void* mpEnd; void* mpCap; uint32_t mAlloc;
    void push_back(const VerbIconRef& r);   // 0x004b54b0
};

// bitset<3>: constant-index test() inlines to the n<3 range check + shift/mask.
struct VerbFlags {
    uint32_t mBits;
    VerbFlags() { mBits = 0; mBits = 0; }
    bool test(uint32_t n) const {
        if (n < 3) {
            uint32_t w = mBits;
            return (w & (1u << (n % 32))) != 0;
        }
        return false;
    }
};

// eastl::vector<uint32_t, sp_vector_allocator>
struct AllocTag { AllocTag() {} };
struct sp_vector_allocator {
    uint32_t m;
    sp_vector_allocator(const AllocTag&);   // 0x00429360
};
struct IdVec {
    typedef int T;
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    sp_vector_allocator mAlloc;
    IdVec() : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(AllocTag()) {}
    int* begin() { return mpBegin; }
    int* end() { return mpEnd; }
    ~IdVec() { DoDestroy(mpBegin, mpEnd); DoFree(); }
    static void DoDestroy(int* first, int* last) { for (; first < last; ++first) first->~T(); }
    void DoFree();                          // 0x00425990
    void push_back(const int& v);      // 0x00454860
};
template <class It, class T> inline It find(It first, It last, const T& v) {
    while (first != last && *first != v) ++first;
    return first;
}

struct VerbData {                   // per-verb record handed out by the owner
    char pad0[0x1c];
    uint32_t mPropID;               // +0x1c
    uint32_t mGroupID;              // +0x20
    char pad1[0x3e0 - 0x24];
    uint32_t mAbilityA;             // +0x3e0
    uint32_t mAbilityB;             // +0x3e4
    uint32_t GetPropID() const { return mPropID; }
    uint32_t GetGroupID() const { return mGroupID; }
    uint32_t GetAbilityA() const { return mAbilityA; }
    uint32_t GetAbilityB() const { return mAbilityB; }
};
struct VerbOwner {
    int GetCount();                 // 0x004accf0
    int Get(int i);                 // 0x004accb0 (VerbData* as an integer handle)
};
bool __cdecl IsVerbUsable(VerbData* v);                                       // 0x004e57f0
void __cdecl AddVerbIcons(PropertyList* pl, IconVec* out, VerbFlags* flags);  // 0x004e5960

struct VerbEntry {                  // 0x1d8-byte records at owner+0x98
    uint32_t mGroupID;              // +0
    uint32_t mPropID;               // +4
    uint32_t pad8;
    int mAltIndex;                  // +0xc
    char pad[0x1d8 - 0x10];
};
struct EntryVec {
    VerbEntry* mpBegin;
    VerbEntry* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
    VerbEntry& operator[](int i) { return mpBegin[i]; }
};
struct EntryOwner {
    char pad[0x98];
    EntryVec mEntries;              // +0x98
};


// 12-byte vector of refcounted elements; dtor at 0x004b5440.
struct RefVec {
    void* mBegin;
    void* mEnd;
    void* mCap;
    RefVec() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~RefVec();
};

struct VerbSink {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void Deliver(RefVec* v); // vtable +0x14
};

void FillRefVec6720(void* owner, RefVec* out); // 0x004e6720
void FillRefVec6a10(void* owner, RefVec* out); // 0x004e6a10

// @ 0x004e6920
// Maps a capability/ability hash to its property-id hash (0 if unknown).
uint32_t GetPropIDForAbilityHash(uint32_t id)
{
    switch (id) {
    case 0xab97cd36: return 0x66783b4;
    case 0x91c3bf70: return 0x11b79302;
    case 0x9052db45: return 0x4d18efd;
    case 0x8a30ddc4: return 0x11b79a71;
    case 0xefd1720c: return 0x11b79a72;
    case 0x2d94dcd7: return 0x32f92e6;
    case 0xb40fb63b: return 0x11b79a75;
    case 0x6701d2bb: return 0x11b79a76;
    case 0x2b2d090b: return 0x11b79a77;
    case 0x2bfee57a: return 0xb3e30313;
    }
    return 0;
}


void BuildVerbCapabilities(IconVec* out, VerbFlags* flags); // 0x004e5d00

// @ 0x004e5d00
// Builds the two always-present verb icons (plus the one selected by the modifier flags).
void BuildVerbCapabilities(IconVec* out, VerbFlags* flags)
{
    uint32_t id1 = CapabilityManager::GetPropIDForAbility(0x4d18efd, 0);
    PropListRef plist((PropertyList*)0);
    if (id1 != 0) {
        GetPropertyManager()->GetPropertyList(id1, 0x1b68db4, plist.AsPPVoidParam());
    }
    cSPEditorVerbIconData* icon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData();
    icon->SetPropertyList(plist.mp);
    icon->mLevel = 3.0f;
    icon->mMaxLevel = 3.0f;
    {
        VerbIconRef r(icon);
        out->push_back(r);
    }

    cSPEditorVerbIconData* icon2 = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData();
    AutoRefCount<PropertyList> plist2;
    uint32_t id2;
    if (!flags->test(2) && !flags->test(0) && !flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x4d192a14, 0);
    } else if (!flags->test(2) && !flags->test(0) && flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x4d192a2, 0);
    } else if (!flags->test(2) && flags->test(0) && !flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x4d192a1, 0);
    } else if (!flags->test(2) && flags->test(0) && flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x177209ee, 0);
    } else if (flags->test(2) && !flags->test(0) && !flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x4d192a3, 0);
    } else if (flags->test(2) && !flags->test(0) && flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x64e7222b, 0);
    } else if (flags->test(2) && flags->test(0) && !flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0xf613df04, 0);
    } else if (flags->test(2) && flags->test(0) && flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x50c34699, 0);
    }
    GetPropertyManager()->GetPropertyList(id2, 0x1b68db4, plist2.AsPPVoidParam());
    icon2->SetPropertyList(plist2.mp);
    icon2->mLevel = 0.0f;
    {
        VerbIconRef r(icon2);
        out->push_back(r);
    }
}

// @ 0x004e6720
// Collects every usable verb (and its ability ids) of the owner, then appends the verb icons.
void Collect6720(VerbOwner* owner, IconVec* out)
{
    VerbFlags flags;
    IdVec seen;
    int i = 0;
    int n = owner->GetCount();
    for (; i < n; ++i) {
        int verb = owner->Get(i);
        if (find(seen.begin(), seen.end(), verb) == seen.end()) {
            if (IsVerbUsable((VerbData*)verb)) {
                seen.push_back(verb);
                if (((VerbData*)verb)->GetAbilityA() != 0) {
                    int a = ((VerbData*)verb)->GetAbilityA();
                    seen.push_back(a);
                } else if (((VerbData*)verb)->GetAbilityB() != 0) {
                    int b = ((VerbData*)verb)->GetAbilityB();
                    seen.push_back(b);
                }
                AutoRefCount<PropertyList> pl;
                GetPropertyManager()->GetPropertyList(((VerbData*)verb)->GetPropID(), ((VerbData*)verb)->GetGroupID(), pl.AsPPVoidParam());
                AddVerbIcons(pl.mp, out, &flags);
            }
        }
    }
    BuildVerbCapabilities(out, &flags);
}

// @ 0x004e6a10
// Same, but over the 0x1d8-byte entry records of an owner.
void UpdateEntry6a10(EntryOwner* owner, IconVec* out)
{
    if (owner != 0) {
        VerbFlags flags;
        IdVec seen;
        int i = 0;
        int n = owner->mEntries.size();
        for (; i < n; ++i) {
            if (find(seen.begin(), seen.end(), i) == seen.end()) {
                VerbEntry* e = &owner->mEntries[i];
                AutoRefCount<PropertyList> pl;
                GetPropertyManager()->GetPropertyList(e->mPropID, e->mGroupID, pl.AsPPVoidParam());
                AddVerbIcons(pl.mp, out, &flags);
                seen.push_back(i);
                if (e->mAltIndex != -1) {
                    int alt = e->mAltIndex;
                    seen.push_back(alt);
                }
            }
        }
        BuildVerbCapabilities(out, &flags);
    }
}

// @ 0x004e6bc0
// Builds a refcounted vector from the owner and dispatches it through a sink.
void BuildDispatch6bc0(void* owner, VerbSink* sink)
{
    RefVec vec;
    FillRefVec6720(owner, &vec);
    sink->Deliver(&vec);
}

// @ 0x004e6c10
// Guarded variant of the above.
void BuildDispatch6c10(void* owner, VerbSink* sink)
{
    if (owner != 0) {
        RefVec vec;
        FillRefVec6a10(owner, &vec);
        sink->Deliver(&vec);
    }
}
