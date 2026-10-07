// w1g1 slice s004e7990 -- /Od EASTL container glue and colour-variation helpers
// around the editor verb-icon data.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" {
uint32_t __cdecl FNV1_String8(const char* s, uint32_t basis, int flag);   // 0x00932e80
}
void* __cdecl operator new(unsigned int size, const char* tag, int a, int b, int c, int d) throw();  // 0x00f473a0 (EASTL_allocator_allocate)

// Intrusive refcounted interface: vtable +0 AddRef, +4 Release.
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    // Releases any held object and returns the out-param slot (0x0041d870).
    T** GetAddress()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

// Same holder, but GetAddress is the out-of-line instance at 0x0041d870 (cl declined to inline it
// at the first two sites of a large function).
template <class T> struct AutoRefCountOut {
    T* mpObject;
    AutoRefCountOut(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCountOut() { if (mpObject) mpObject->Release(); }
    T** GetAddress();                                     // 0x0041d870
};

// SP::cSPEditorVerbIconData (0xc4 bytes) and its creature subclass cSPCreatureVerbIconData (0xd0).
struct cSPEditorVerbIconData {
    virtual int AddRef();
    virtual int Release();
    virtual void v02();
    virtual void v03();
    virtual void SetIcon(IRefObj* icon);     // vtable +0x10
    char pad04[0x18 - 4];
    float mValue;                            // +0x18
    char pad1c[0xc4 - 0x1c];
    cSPEditorVerbIconData();                 // 0x005e5a70
};
struct cSpeciesProfile;
struct VerbAbility {
    char pad[0x130];
    int mVerbType;                           // +0x130
    int GetVerbType() { return mVerbType; }
};
struct cSPCreatureVerbIconData : cSPEditorVerbIconData {
    char pad0c4[0xd0 - 0xc4];
    cSPCreatureVerbIconData();               // 0x005e5b60
    void Init(cSpeciesProfile* profile, VerbAbility* ability, int index);   // 0x005e5950
};

// A 12-byte EASTL vector of refcounted elements; the destructor at 0x004b5440
// releases each element and frees the buffer.
struct RefVec {
    AutoRefCount<cSPEditorVerbIconData>* mBegin; // +0
    AutoRefCount<cSPEditorVerbIconData>* mEnd;   // +4
    AutoRefCount<cSPEditorVerbIconData>* mCap;   // +8
    uint32_t mAlloc[2];                          // uninitialised allocator dwords (vector is 0x14 bytes)
    RefVec() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~RefVec();                                            // 0x004b5440
    void push_back(const AutoRefCount<cSPEditorVerbIconData>& r);   // 0x004b54b0
    void resize(int n);                                   // 0x00421bf0 (IPtrVec::resize)
    AutoRefCount<cSPEditorVerbIconData>& operator[](int i) { return mBegin[i]; }
};

struct IPropertyManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void GetProperty(uint32_t propId, uint32_t typeId, IRefObj** out);   // vtable +0x2c
};
IPropertyManager* __cdecl PropertyManager();                                    // 0x0067de30

void FillRefVec18(RefVec* out, uint32_t key); // 0x004e7990
void FillRefVec3(void* a, RefVec* out, void* b, float c); // 0x004e7eb0

struct VerbSink {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void Deliver(RefVec* v); // vtable +0x14
};

struct TreeNode;

// rbtree anchor/owner laid out as: [+0 pad][+4 next][+8 prev][+0xc root]
// [+0x10 flag][+0x14 count].
struct TreeHead {
    uint32_t        pad0;
    void*           mNext;   // +0x4
    void*           mPrev;   // +0x8
    TreeNode*       mRoot;   // +0xc
    unsigned char   mFlag;   // +0x10
    char            pad1[3];
    int             mCount;  // +0x14

    void FreeNode(TreeNode* node); // 0x004e8a30
    void Reset();                  // @ 0x004e8850
};

// @ 0x004e8850
// Reinitialises the tree: frees the node chain, points the anchor at itself,
// then clears root/flag/count.
void TreeHead::Reset()
{
    FreeNode(mRoot);
    mNext = &mNext;
    mPrev = &mNext;
    mRoot = 0;
    mFlag = 0;
    mCount = 0;
}

#define HASH_NAME(s) FNV1_String8(s, 0x811c9dc5, 1)

// @ 0x004e7990
// Builds the verb-icon list for a vehicle/building type id: maps the id to the hash of its
// property name, fetches that property and wraps it in a cSPEditorVerbIconData appended to `out`.
void FillRefVec18(RefVec* out, uint32_t key)
{
    uint32_t hash = 0;
    switch ((int)key) {
    case 0x7d433fad: hash = HASH_NAME("Vehicle_MilitaryLand"); break;
    case 0x8f963dcb: hash = HASH_NAME("Vehicle_MilitarySea"); break;
    case 0x441cd3e6: hash = HASH_NAME("Vehicle_MilitaryAir"); break;
    case 0xf670aa43: hash = HASH_NAME("Vehicle_EconomicLand"); break;
    case 0x2a5147a9: hash = HASH_NAME("Vehicle_EconomicSea"); break;
    case 0x1a4e0708: hash = HASH_NAME("Vehicle_EconomicAir"); break;
    case 0x9ad7d4aa: hash = HASH_NAME("Vehicle_ReligiousLand"); break;
    case 0x1f2a25b6: hash = HASH_NAME("Vehicle_ReligiousSea"); break;
    case 0x449c040f: hash = HASH_NAME("Vehicle_ReligiousAir"); break;
    case 0xbc1041e6: hash = HASH_NAME("Vehicle_ColonyLand"); break;
    case 0xc15695da: hash = HASH_NAME("Vehicle_ColonySea"); break;
    case 0x2090a11b: hash = HASH_NAME("Vehicle_ColonyAir"); break;
    case 0x98e03c0d: hash = HASH_NAME("Vehicle_UFO"); break;
    case 0x99e92f05: hash = HASH_NAME("Building_CityHall"); break;
    case 0x4e3f7777: hash = HASH_NAME("Building_House"); break;
    case 0x47c10953: hash = HASH_NAME("Building_Factory"); break;
    case 0x72c49181: hash = HASH_NAME("Building_Entertainment"); break;
    }
    if (hash != 0) {
        AutoRefCount<IRefObj> k(0);
        PropertyManager()->GetProperty(hash, 0x1b68db4, k.GetAddress());
        cSPEditorVerbIconData* info = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData();
        info->SetIcon(k.mpObject);
        ScratchSlots<2>();
        out->push_back(AutoRefCount<cSPEditorVerbIconData>(info));
    }
}

// ---------------------------------------------------------------------------
// Collects the owner's entry list (8-byte entries), builds a verb-icon vector from it and
// hands it to the sink; the trailing empty loop is a /Od leftover of an unused iteration.
struct Entry8 { uint32_t a, b; };
struct EntryVec {
    Entry8* mBegin;
    Entry8* mEnd;
    Entry8* mCap;
    uint32_t mAlloc[2];
    EntryVec() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~EntryVec();                                          // 0x0045daf0
};
struct EntryOwner {
    char pad[0x18];
    uint32_t mKey;                                        // +0x18
    uint32_t GetKey() { return mKey; }
};
void __cdecl ApplyOwnerEntries(EntryOwner* owner, EntryVec* out);                  // 0x00433210
void __cdecl BuildVerbIcons(EntryVec* entries, RefVec* out, uint32_t key);         // 0x004e7610

// @ 0x004e7da0
void ConvertOwnerEntries(EntryOwner* owner, VerbSink* sink)
{
    if (owner) {
        EntryVec entries;
        ApplyOwnerEntries(owner, &entries);
        {
            RefVec vec;
            BuildVerbIcons(&entries, &vec, owner->GetKey());
            sink->Deliver(&vec);
        }
        for (Entry8* p = entries.mBegin; p < entries.mEnd; p++) {
        }
    }
}

// @ 0x004e7e50
// Builds a refcounted vector from owner+0x18 and dispatches it through a sink.
void BuildAndDispatch18(void* owner, VerbSink* sink)
{
    uint32_t scratch[1];
    RefVec vec;
    FillRefVec18(&vec, ((EntryOwner*)owner)->GetKey());
    ScratchSlots<5>();
    sink->Deliver(&vec);
}

// ---------------------------------------------------------------------------
// Builds the creature verb-icon list for an editor rig: profiles the creature, then fills `out`
// with [carnivore icon][value icon][jump/herbivore icon][one icon per ability / passive ability].
struct EditorRig;
struct AbilityVec {                                       // eastl::vector<ability*>
    VerbAbility** mBegin;
    VerbAbility** mEnd;
    VerbAbility** mCap;
    int size() const { return (int)(mEnd - mBegin); }
    VerbAbility*& operator[](int i) { return mBegin[i]; }
};
struct SpeciesVecInit {
    void* a; void* b; void* c;
    SpeciesVecInit() { a = 0; b = 0; c = 0; }
};
struct cSpeciesProfile {
    char pad0[0x56c];
    float mBoundsZ;                                       // +0x56c (aabb_origin.z)
    char pad570[0x604 - 0x570];
    uint32_t carnivore_level;                             // +0x604
    uint32_t herbivore_level;                             // +0x608
    uint32_t jump_level;                                  // +0x60c
    char pad610[0x6d4 - 0x610];
    AbilityVec abilities;                                 // +0x6d4
    char pad6e0[0x73c - 0x6e0];
    AbilityVec passiveAbilities;                          // +0x73c
    char pad748[0xa18 - 0x748];
    cSpeciesProfile(SpeciesVecInit* v, int a);            // 0x004d3dd0
    ~cSpeciesProfile();                                   // 0x004d44e0
    bool Update(EditorRig* rig);                          // 0x004d5020
};
uint32_t __cdecl GetPropIDForAbility(uint32_t ability, int flags);                 // 0x00459370
float __cdecl FUN_4d12a0(void* arg);                                               // 0x004d12a0
int __cdecl GetVerbCategory(int verbType);                                         // 0x004e58c0
bool __cdecl IsDietCategory(int category);                                         // 0x004e5910

// @ 0x004e7eb0
void BigBuilder2368(EditorRig* rig, RefVec* out, void* arg3, float minValue)
{
    if (rig) {
        SpeciesVecInit vecInit;
        cSpeciesProfile profile(&vecInit, 0);
        profile.Update(rig);
        int total = profile.abilities.size() + profile.passiveAbilities.size();
        uint32_t propId = GetPropIDForAbility(0x31c3e5b2, 0);
        AutoRefCountOut<IRefObj> carnProp(0);
        if (propId != 0) {
            IPropertyManager* pm = PropertyManager();
            pm->GetProperty(propId, 0xdd91ac58, carnProp.GetAddress());
        }
        float scale = FUN_4d12a0(arg3);
        out->resize(total + 3);
        cSPEditorVerbIconData* carnIcon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData();
        carnIcon->SetIcon(carnProp.mpObject);
        carnIcon->mValue = (float)profile.carnivore_level;
        cSPEditorVerbIconData* sizeIcon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData();
        AutoRefCountOut<IRefObj> sizeProp(0);
        IPropertyManager* pm2 = PropertyManager();
        pm2->GetProperty(0x5ce214c5, 0xdd91ac58, sizeProp.GetAddress());
        sizeIcon->SetIcon(sizeProp.mpObject);
        sizeIcon->mValue = scale + profile.mBoundsZ;
        if (minValue > 0.0f)
            sizeIcon->mValue = minValue;
        int idx = 0;
        (*out)[idx++] = carnIcon;
        (*out)[idx++] = sizeIcon;
        int nPassive = profile.passiveAbilities.size();
        int nAbilities = profile.abilities.size();
        bool hasJump = profile.jump_level != 0;
        bool hasHerb = profile.herbivore_level != 0;
        bool both = hasJump && hasHerb;
        AutoRefCount<IRefObj> dietProp(0);
        float levelSum = (float)(profile.jump_level + profile.herbivore_level);
        uint32_t dietId;
        if (both)
            dietId = GetPropIDForAbility(0x4d18972, 0);
        else if (hasJump)
            dietId = GetPropIDForAbility(0x22e785c, 0);
        else if (hasHerb)
            dietId = GetPropIDForAbility(0x22e7847, 0);
        else
            dietId = GetPropIDForAbility(0x4d18c4c, 0);
        IPropertyManager* pm3 = PropertyManager();
        pm3->GetProperty(dietId, 0xdd91ac58, dietProp.GetAddress());
        cSPEditorVerbIconData* dietIcon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData();
        dietIcon->SetIcon(dietProp.mpObject);
        dietIcon->mValue = levelSum;
        (*out)[idx++] = dietIcon;
        for (int i = idx; i < total + idx; i++) {
            int j = i - idx;
            VerbAbility* ability;
            if (j < profile.abilities.size())
                ability = profile.abilities[j];
            else
                ability = profile.passiveAbilities[j - profile.abilities.size()];
            bool isDiet = IsDietCategory(GetVerbCategory(ability->GetVerbType()));
            if (!isDiet) {
                cSPCreatureVerbIconData* cv = new("Editor", 0, 0, 0, 0) cSPCreatureVerbIconData();
                cv->Init(&profile, ability, i);
                (*out)[i] = cv;
            } else {
                (*out)[i] = 0;
            }
        }
    }
}

// @ 0x004e87f0
// Builds a refcounted vector from three args and dispatches it through a sink.
void BuildAndDispatch3(void* a, VerbSink* sink, void* b, float c)
{
    uint32_t scratch[6];
    RefVec vec;
    FillRefVec3(a, &vec, b, c);
    sink->Deliver(&vec);
}
