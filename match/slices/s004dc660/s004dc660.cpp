// w1g1 slice s004dc660 -- cSpeciesCheat::GetFullPath and the cPlantSummarizer /
// cSpeciesSummarizer functional-match glue around 0x4dc660-0x4dd05f.
//
// Region is unoptimized: /Od /Ob1 /MD /Gy /TP /arch:SSE (frame pointer, this spilled
// to [ebp-4], SSE scalar float copies; no C++ EH frame).

typedef unsigned int uint32_t;

extern wchar_t gEmptyString16[];       // 0x1667bac
extern const wchar_t gEmptyName[];     // 0x13ec468
extern const wchar_t gFormatString[];  // 0x13eb9cc  L"%ls%ls"

namespace eastl {

class allocator {};
class sp_vector_allocator {};

template <class CharT, class Alloc>
class basic_string {
public:
    CharT* mpBegin;
    CharT* mpEnd;
    CharT* mpCapacity;
    basic_string()
    {
        mpBegin = 0;
        mpEnd = 0;
        mpCapacity = 0;
        mpBegin = gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    void FreeBuffer();  // 0x4237d0
};

template <class T, class Alloc>
class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    void push_back(const T& value);  // 0x4e19a0
};

} // namespace eastl

namespace EA { namespace ResourceMan {

class Key {
public:
    uint32_t mInstance;  // 0x00
    uint32_t mType;      // 0x04
    uint32_t mGroup;     // 0x08
};

class IObject {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual const wchar_t* GetDisplayName();  // +0x28
};

class IResourceManager {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual IObject* GetObject(const Key& key);  // +0x58
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual bool GetFileName(const Key& key, eastl::basic_string<wchar_t, eastl::allocator>& path);  // +0x7c
};

IResourceManager* GetManager();  // 0x67dcd0

}} // namespace EA::ResourceMan

void Format(eastl::basic_string<wchar_t, eastl::allocator>* pOut, const wchar_t* pFormat, ...);  // 0x41e050

namespace SP {

struct cSpeciesCheat {
    char pad[0x10];
    void GetFullPath(const EA::ResourceMan::Key& key,
                     eastl::basic_string<wchar_t, eastl::allocator>& path);  // 0x004dc660
};

namespace FunctionalMatch {

struct DeclareParam {
    uint32_t mParameter;  // 0x00
    int mType;            // 0x04
    int mValue;           // 0x08
    DeclareParam(uint32_t parameter, int value);  // 0x558bc0
};

} // namespace FunctionalMatch

// Fully loaded species record; only the "loaded" flag is consumed here.  The full
// retail object is 0xa18 bytes and its ctor/dtor write the whole thing, so the local
// must be laid out at full size or it overruns the caller's frame.
struct cSpeciesProfile {
    char pad0[0x578];
    bool mbLoaded;                      // 0x578
    char pad579[0xa18 - 0x579];
    cSpeciesProfile(const EA::ResourceMan::Key& key, bool bPlant);  // 0x4d3dd0
    ~cSpeciesProfile();                                            // 0x4d44e0
    bool Load(const EA::ResourceMan::Key& key);                    // 0x4d4f10
};

class cPlantSummarizer { public:
    char pad[0x10];
    int GetStaticType();  // 0x004dc730
    int GetResType(int);  // 0x004dc740
    virtual bool ExtractParameters(const EA::ResourceMan::Key& desc,
        eastl::vector<FunctionalMatch::DeclareParam, eastl::sp_vector_allocator>& out) const;  // 0x004dc760
};

class cSpeciesSummarizer { public:
    char pad[0x10];
    int GetStaticType();  // 0x004dc920
    int GetResType(int);  // 0x004dc930
    virtual bool ExtractParameters(const EA::ResourceMan::Key& desc,
        eastl::vector<FunctionalMatch::DeclareParam, eastl::sp_vector_allocator>& out) const;  // 0x004dc950
};

} // namespace SP

extern int g_plantStaticType;    // 0x15d9670
extern int g_speciesStaticType;  // 0x15d9674

// Four species variant ids handed to the model-validity helper by value.
struct SpeciesVariantIDs {
    int mCreature;  // 0x00
    int mPlant;     // 0x04
    int mSkin;      // 0x08
    int mPattern;   // 0x0c
};
extern SpeciesVariantIDs g_speciesVariantIDs;    // 0x15da9c8
bool FUN_004f3c50(int key, SpeciesVariantIDs ids);  // 0x4f3c50
void BuildParameters(SP::cSpeciesProfile* pProfile,
    eastl::vector<SP::FunctionalMatch::DeclareParam, eastl::sp_vector_allocator>& out,
    bool bArchetypes);  // 0x4d15c0

// @ 0x004dc730
int SP::cPlantSummarizer::GetStaticType()
{
    return g_plantStaticType;
}

// @ 0x004dc740
int SP::cPlantSummarizer::GetResType(int p)
{
    if (p == 0)
        return 0x438f6347;
    return -1;
}

// @ 0x004dc920
int SP::cSpeciesSummarizer::GetStaticType()
{
    return g_speciesStaticType;
}

// @ 0x004dc930
int SP::cSpeciesSummarizer::GetResType(int p)
{
    if (p == 0)
        return 0x2b978c46;
    return -1;
}

// @ 0x004dc660
// Resolves the resource path (manager vcall +0x7c) and display name (vcall +0x58 /
// +0x28) and formats L"%ls%ls" into the caller's string.
void SP::cSpeciesCheat::GetFullPath(const EA::ResourceMan::Key& key,
    eastl::basic_string<wchar_t, eastl::allocator>& path)
{
    eastl::basic_string<wchar_t, eastl::allocator> fileName;
    EA::ResourceMan::GetManager()->GetFileName(key, fileName);
    EA::ResourceMan::IObject* pObject = EA::ResourceMan::GetManager()->GetObject(key);
    const wchar_t* pName = gEmptyName;
    if (pObject)
        pName = pObject->GetDisplayName();
    Format(&path, gFormatString, pName, fileName.mpBegin);
    fileName.FreeBuffer();
}

// @ 0x004dc760
// Rejects non-plant keys, loads the species record and declares its four capture
// parameters when the record is marked as loaded.
bool SP::cPlantSummarizer::ExtractParameters(const EA::ResourceMan::Key& desc,
    eastl::vector<SP::FunctionalMatch::DeclareParam, eastl::sp_vector_allocator>& out) const
{
    if (desc.mGroup == 0)
        return false;
    if (((desc.mGroup >> 16) & 0xff) == 0x6b)
        return false;
    if (((desc.mGroup >> 24) & 0x1f) == 1)
        return false;

    EA::ResourceMan::Key null = { 0, 0, 0 };
    cSpeciesProfile profile(null, false);
    if (!profile.Load(desc))
        return false;
    if (desc.mInstance == 0xde727fa9)
        return false;
    if (profile.mbLoaded) {
        out.push_back(SP::FunctionalMatch::DeclareParam(0x54a32960, 1));
        out.push_back(SP::FunctionalMatch::DeclareParam(0x54a32961, 0));
        out.push_back(SP::FunctionalMatch::DeclareParam(0x665f917, 1));
        out.push_back(SP::FunctionalMatch::DeclareParam(0x67b82d8, 0));
        return true;
    }
    return false;
}

// @ 0x004dc950
// Rejects non-creature keys, runs the combined variant check (true = "nothing to
// declare") and otherwise declares the full creature parameter set.
bool SP::cSpeciesSummarizer::ExtractParameters(const EA::ResourceMan::Key& desc,
    eastl::vector<SP::FunctionalMatch::DeclareParam, eastl::sp_vector_allocator>& out) const
{
    if (desc.mGroup == 0)
        return false;
    if (((desc.mGroup >> 16) & 0xff) == 0x6b)
        return false;
    if (((desc.mGroup >> 24) & 0x1f) == 1)
        return false;

    if (!FUN_004f3c50((int)&desc, g_speciesVariantIDs))
        return true;

    EA::ResourceMan::Key null = { 0, 0, 0 };
    cSpeciesProfile profile(null, false);
    if (profile.Load(desc)) {
        BuildParameters(&profile, out, true);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// Species manager map teardown / message handling.
// ---------------------------------------------------------------------------

namespace SP {

struct SpeciesNode;

// eastl::hashtable, 0x20 bytes: functor, bucket array, bucket count, element count,
// three rehash words and the allocator.
template <class Node>
struct hashtable {
    uint32_t mFunctor;      // 0x00
    Node** mpBucketArray;   // 0x04
    uint32_t mnBucketCount; // 0x08
    uint32_t mnElementCount;// 0x0c
    uint32_t mRehash[3];    // 0x10
    uint32_t mAllocator;    // 0x1c

    struct iterator {
        Node* mpNode;    // 0x00
        Node** mpBucket; // 0x04
        iterator() : mpNode(0), mpBucket(0) {}
        Node* node() const { return mpNode; }
        bool operator!=(const iterator& other) const { return mpNode != other.mpNode; }
        iterator& operator++()
        {
            mpNode = mpNode->mpNext;
            while (mpNode == 0)
                mpNode = *++mpBucket;
            return *this;
        }
    };

    iterator begin();  // 0x564140
    iterator end()
    {
        iterator i;
        i.mpBucket = mpBucketArray + mnBucketCount;
        i.mpNode = *i.mpBucket;
        return i;
    }
    iterator find(const EA::ResourceMan::Key& key);                 // 0x4e0f80
    cSpeciesProfile*& operator[](const EA::ResourceMan::Key& key);  // 0x4e0560
    void DoFreeNodes(Node** buckets, uint32_t count);               // 0x4e3590
    void DoFreeArchetypeNodes(Node** buckets, uint32_t count);      // 0x4e3760
};

struct SpeciesNode {
    EA::ResourceMan::Key mKey;  // 0x00
    cSpeciesProfile* mValue;    // 0x0c
    SpeciesNode* mpNext;        // 0x10
};

struct PendingBatch {
    void Flush();  // 0x4039f0
};

class cSPEditorSpeciesManager_s004d_c660 {
public:
    char pad00[4];                                // 0x00 (handler vptr)
    hashtable<SpeciesNode> mSpecies;              // 0x04
    hashtable<SpeciesNode> mOldSpeciesMapping;    // 0x24
    hashtable<SpeciesNode> mPlantSpecies;         // 0x44
    hashtable<SpeciesNode> mReplacementSpecies;   // 0x64
    hashtable<SpeciesNode> mReplacementCache;     // 0x84
    EA::ResourceMan::Key mAvatarSpeciesKey;       // 0xa4
    hashtable<SpeciesNode> mArchetypes;           // 0xb0
    PendingBatch mPendingBatch;                   // 0xd0

    void Teardown();                              // 0x004dcaa0
    bool HandleMessage(int msgId, void* payload); // 0x004dcee0
    void ReloadTuning();                          // 0x4dd060
};

struct cSpeciesProfileVector {
    cSpeciesProfile** mpBegin;  // 0x00
    cSpeciesProfile** mpEnd;    // 0x04
    void erase(cSpeciesProfile** first, cSpeciesProfile** last);  // 0x4247f0
};

} // namespace SP

extern SP::cSpeciesProfileVector g_speciesProfileVector;  // 0x15d9780
void FreeRawBlock(void* p);                               // 0xf47380
extern const char* g_speciesQuery;                        // 0x150c908

class ICheatManager {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual bool RemoveCheat(const char* name);  // +0x1c
};
ICheatManager* CheatManager();  // 0x67de20

// @ 0x004dcaa0
// Flushes the pending batch, destroys every owned profile in the species maps,
// frees the bucket arrays and finally drops the species-query cheat.
void SP::cSPEditorSpeciesManager_s004d_c660::Teardown()
{
    mPendingBatch.Flush();

    for (hashtable<SpeciesNode>::iterator it = mSpecies.begin(); it != mSpecies.end(); ++it) {
        cSpeciesProfile* pProfile = it.mpNode->mValue;
        if (pProfile) {
            pProfile->~cSpeciesProfile();
            FreeRawBlock(pProfile);
        }
    }
    mSpecies.DoFreeNodes(mSpecies.mpBucketArray, mSpecies.mnBucketCount);
    mSpecies.mnElementCount = 0;

    for (hashtable<SpeciesNode>::iterator it = mPlantSpecies.begin(); it != mPlantSpecies.end(); ++it) {
        cSpeciesProfile* pProfile = it.mpNode->mValue;
        if (pProfile) {
            pProfile->~cSpeciesProfile();
            FreeRawBlock(pProfile);
        }
    }
    mPlantSpecies.DoFreeNodes(mPlantSpecies.mpBucketArray, mPlantSpecies.mnBucketCount);
    mPlantSpecies.mnElementCount = 0;

    for (hashtable<SpeciesNode>::iterator it = mReplacementCache.begin(); it != mReplacementCache.end(); ++it) {
        cSpeciesProfile* pProfile = it.mpNode->mValue;
        if (pProfile) {
            pProfile->~cSpeciesProfile();
            FreeRawBlock(pProfile);
        }
    }
    mReplacementCache.DoFreeNodes(mReplacementCache.mpBucketArray, mReplacementCache.mnBucketCount);
    mReplacementCache.mnElementCount = 0;

    mOldSpeciesMapping.DoFreeNodes(mOldSpeciesMapping.mpBucketArray, mOldSpeciesMapping.mnBucketCount);
    mOldSpeciesMapping.mnElementCount = 0;

    mReplacementSpecies.DoFreeNodes(mReplacementSpecies.mpBucketArray, mReplacementSpecies.mnBucketCount);
    mReplacementSpecies.mnElementCount = 0;

    mArchetypes.DoFreeArchetypeNodes(mArchetypes.mpBucketArray, mArchetypes.mnBucketCount);
    mArchetypes.mnElementCount = 0;

    g_speciesProfileVector.erase(g_speciesProfileVector.mpBegin, g_speciesProfileVector.mpEnd);

    ICheatManager* pCheats = CheatManager();
    if (pCheats)
        pCheats->RemoveCheat(g_speciesQuery);
}

// @ 0x004dcee0
// Tuning-changed message triggers a reload; the "species replaced" message moves the
// profile pointer from mSpecies into the replacement cache and nulls the original.
bool SP::cSPEditorSpeciesManager_s004d_c660::HandleMessage(int msgId, void* payload)
{
    if (msgId == 0xf62def) {
        int instance = *(int*)((char*)payload + 0x10);
        int group = *(int*)((char*)payload + 0x18);
        if ((instance == 0 && group == 0x236f18f2) || instance == 0x2f98b67)
            ReloadTuning();
        return true;
    }
    if (msgId == 0x4249453) {
        EA::ResourceMan::Key key = {
            *(uint32_t*)((char*)payload + 0x18),
            *(uint32_t*)((char*)payload + 0x08),
            *(uint32_t*)((char*)payload + 0x10)
        };
        hashtable<SpeciesNode>::iterator it = mSpecies.find(key);
        if (it != mSpecies.end()) {
            mReplacementCache[key] = it.mpNode->mValue;
            mSpecies[key] = 0;
        }
        return true;
    }
    return false;
}
