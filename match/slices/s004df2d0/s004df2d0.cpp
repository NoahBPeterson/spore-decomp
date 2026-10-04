// Slice s004df2d0: SP::cSPEditorSpeciesManager (species profile cache) members. Retail layout differs from the
// 2008 PDB: an extra Key->profile hash_map (mReplacementCache) sits at 0x84, pushing mAvatarSpeciesKey to 0xA4.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

// Reproduces dead /Od stack slots left by inlined helpers whose locals the original never used.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00F473A0
void operator delete(void* p);                                                                                      // 0x00F47380

namespace EA { namespace ResourceMan {
struct Key {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
inline bool operator==(const Key& a, const Key& b) { return a.mInstance == b.mInstance && a.mType == b.mType && a.mGroup == b.mGroup; }
inline bool operator!=(const Key& a, const Key& b) { return a.mInstance != b.mInstance || a.mType != b.mType || a.mGroup != b.mGroup; }
} }
using EA::ResourceMan::Key;

class RandomLinearCongruential;
extern RandomLinearCongruential sMathRandom;                                   // 0x01601760
double RandomRange(RandomLinearCongruential* r, double lo, double hi);         // 0x004B8900

struct Vector2 { float mData[2]; const float& operator[](int i) const { return mData[i]; } };

namespace SP {

class cSpeciesProfile {
public:
    cSpeciesProfile(const Key& key, bool bPlant);   // 0x004D3DD0
    ~cSpeciesProfile();                              // 0x004D44E0
    bool Load(const Key& key);                       // 0x004D4F10
    char pad0[0x504];
    Key mSpeciesKey;          // 0x504
    char pad510[0x53C - 0x510];
    int mbLoaded;             // 0x53C
    char pad540[0xA18 - 0x540];
};

class cSpeciesArchetype;

namespace { void InitStatics(); }   // 0x004D34F0
bool ResourceExists(const Key* key); // 0x004DA3A0

struct IObjectTemplateDB {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void FindTemplates(struct KeyVector& out, int count, struct ConstraintVector& constraints);   // 0x24
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50(); virtual void v54();
    virtual void Prefetch(const Key& key, bool b);                         // 0x58
    virtual void v5C(); virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C(); virtual void v70();
    virtual void Remove(const Key& key, int flags);                           // 0x74
};
IObjectTemplateDB* ObjectTemplateDB();   // 0x0067CB40

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void MessageSend(uint32_t id, void* msg, int flags);   // 0x14
};
IMessageServer* MessageServer();   // 0x0067DCC0

union MessageValue { uint32_t mUint32; float mFloat; uint32_t pad[2]; };

class MessageBasicRC5 {
public:
    MessageBasicRC5(uint32_t id);   // 0x00421C80
    ~MessageBasicRC5();             // 0x00421CF0
    const void* vptr;               // 0x00
    volatile long mRefCount;        // 0x04
    MessageValue mData[5];          // 0x08
    void SetUint32(int i, uint32_t v) { mData[i].mUint32 = v; }
    uint32_t mId;                   // 0x30
    uint32_t pad34;
    uint32_t mRCFlags;              // 0x38
    uint32_t pad3C;
};

} // namespace SP

namespace eastl {
struct HashNode {
    Key mKey;
    SP::cSpeciesProfile* mpProfile;
    HashNode* mpNext;
};
struct hashtable_iterator_base {
    HashNode* mpNode;
    HashNode** mpBucket;
    hashtable_iterator_base(HashNode* pNode, HashNode** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
struct hashtable_iterator : public hashtable_iterator_base {
    hashtable_iterator(HashNode* pNode = 0, HashNode** pBucket = 0) : hashtable_iterator_base(pNode, pBucket) {}
    hashtable_iterator(HashNode** pBucket) : hashtable_iterator_base(*pBucket, pBucket) {}
    hashtable_iterator(const hashtable_iterator& x) : hashtable_iterator_base(x.mpNode, x.mpBucket) {}
};
struct hashtable_const_iterator : public hashtable_iterator_base {
    hashtable_const_iterator(const hashtable_iterator& x) : hashtable_iterator_base(x.mpNode, x.mpBucket) {}
};
inline bool operator!=(const hashtable_iterator_base& a, const hashtable_iterator_base& b) { return a.mpNode != b.mpNode; }
class SpeciesMap {   // hash_map<Key, cSpeciesProfile*, KeyHash>
public:
    typedef hashtable_iterator iterator;
    typedef hashtable_const_iterator const_iterator;
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    iterator find(const Key& k);                       // 0x004E0F80
    SP::cSpeciesProfile*& operator[](const Key& k);    // 0x004E0560
    uint32_t erase(const Key& k);                      // 0x004E10A0
    iterator erase(iterator it);                       // 0x004E11E0
    uint32_t mFunctors;
    HashNode** mpBucketArray;   // 0x04
    uint32_t mnBucketCount;     // 0x08
    uint32_t mnElementCount;    // 0x0C
    uint32_t mRehashPolicy[3];  // 0x10
    uint32_t mAllocator;        // 0x1C
};

struct ArchetypeNode;
struct archetype_iterator_base {
    ArchetypeNode* mpNode;
    ArchetypeNode** mpBucket;
    archetype_iterator_base(ArchetypeNode* pNode, ArchetypeNode** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
struct archetype_iterator : public archetype_iterator_base {
    archetype_iterator(ArchetypeNode* pNode = 0, ArchetypeNode** pBucket = 0) : archetype_iterator_base(pNode, pBucket) {}
    archetype_iterator(ArchetypeNode** pBucket) : archetype_iterator_base(*pBucket, pBucket) {}
};
inline bool operator!=(const archetype_iterator_base& a, const archetype_iterator_base& b) { return a.mpNode != b.mpNode; }
class ArchetypeMap {   // hash_map<uint32_t, cSpeciesArchetype>
public:
    typedef archetype_iterator iterator;
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    iterator find(const uint32_t& k);                  // 0x004E14E0
    uint32_t mFunctors;
    ArchetypeNode** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    uint32_t mRehashPolicy[3];
    uint32_t mAllocator;
};
} // namespace eastl

namespace SP {

struct ArchetypeIdVector { uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); } };

class cSpeciesArchetype {
public:
    char pad0[0x3C4];
    ArchetypeIdVector mParentIds;   // 0x3C4
};
}
namespace eastl {
struct ArchetypeNode { uint32_t mKey; SP::cSpeciesArchetype mValue; };
}

namespace SP {

namespace FunctionalMatch { class Constraint; }
struct DefaultAllocTag { DefaultAllocTag() {} };
struct ConstraintAllocator {
    ConstraintAllocator() {}
    ConstraintAllocator(const DefaultAllocTag&);   // 0x00429360
    uint32_t mFlags;
};
struct ConstraintVectorBase {
    FunctionalMatch::Constraint* mpBegin;
    FunctionalMatch::Constraint* mpEnd;
    FunctionalMatch::Constraint* mpCapacity;
    ConstraintAllocator mAllocator;
    ConstraintVectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ConstraintVectorBase(const DefaultAllocTag& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ConstraintVectorBase(uint32_t n, const DefaultAllocTag& a);   // 0x004E3CF0
    ~ConstraintVectorBase();   // 0x004AB0D0
};
struct ConstraintVector : public ConstraintVectorBase {   // eastl::vector<FunctionalMatch::Constraint>
    ConstraintVector() {}
    ConstraintVector(const DefaultAllocTag& a) : ConstraintVectorBase(a) {}
    inline ConstraintVector(uint32_t n, const FunctionalMatch::Constraint& value, const DefaultAllocTag& a = DefaultAllocTag());
    ~ConstraintVector();   // 0x004E1780
    void DoDestroyValues(FunctionalMatch::Constraint* first, FunctionalMatch::Constraint* last);   // 0x004E39A0
    void reserve(uint32_t n);                                   // 0x004E17E0
    void push_back(const FunctionalMatch::Constraint& value);   // 0x004E18E0
};
namespace FunctionalMatch {
class Constraint {
public:
    Constraint(uint32_t property, uint32_t op, uint32_t value);   // 0x00558960
    uint32_t mData[4];
    ConstraintVector mSubConstraints;   // 0x10
    uint32_t mFlags;                    // 0x20
};
}
void uninitialized_fill_n(FunctionalMatch::Constraint* p, uint32_t n, const FunctionalMatch::Constraint& value);   // 0x004E3D60
inline ConstraintVector::ConstraintVector(uint32_t n, const FunctionalMatch::Constraint& value, const DefaultAllocTag& a)
    : ConstraintVectorBase(n, a)
{
    uninitialized_fill_n(mpBegin, n, value);
    mpEnd = mpBegin + n;
}

template <class T> inline void destruct(T* first, T* last) { for (; first < last; ++first) first->~T(); }

struct KeyVectorBase {
    Key* mpBegin;
    Key* mpEnd;
    Key* mpCapacity;
    uint32_t mAllocator;
    KeyVectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~KeyVectorBase();   // 0x005156B0
};
struct KeyVector : public KeyVectorBase {   // eastl::vector<ResourceKey>
    ~KeyVector() { destruct(mpBegin, mpEnd); }
};

struct ProfileAllocator { uint32_t mData[3]; };
struct ProfileVectorBase {
    cSpeciesProfile** mpBegin;
    cSpeciesProfile** mpEnd;
    cSpeciesProfile** mpCapacity;
    ProfileVectorBase(const DefaultAllocTag& a);   // 0x00540470
};
struct ProfileVector : public ProfileVectorBase {   // eastl::fixed_vector<cSpeciesProfile*, 5>
    ProfileVector() : ProfileVectorBase(DefaultAllocTag()) { InitBuffer(); SetOverflowCapacity(1); }
    ~ProfileVector();                    // 0x004E1BF0
    void InitBuffer();                   // 0x004E0810
    void SetOverflowCapacity(uint32_t);  // 0x004CD3C0
    cSpeciesProfile*& operator[](uint32_t i) { return mpBegin[i]; }
    ProfileAllocator mAllocator;
    cSpeciesProfile* mBuffer[5];
};
int FindMatchingCreatures(ProfileVector& out, cSpeciesArchetype* pArchetype, int count, int a, bool b, ConstraintVector& constraints); // 0x004D2200

class cSPEditorSpeciesManager {
public:
    void SetAvatarSpecies(const Key& key);
    void SetAvatarProfile(cSpeciesProfile* pProfile);
    cSpeciesProfile* GetAvatarProfile();
    cSpeciesProfile* GetPlantProfile(const Key& key);
    cSpeciesProfile* GetProfile(const Key& key);
    cSpeciesProfile* FindProfile(eastl::SpeciesMap& map, const Key& key);
    bool GetDefaultReplacementKey(const Key& key, Key& outKey);
    bool GetReplacementKey(const Key& key, uint32_t archetypeId, Key& outKey);
    bool GetReplacementKeyForArchetype(const Key& key, cSpeciesArchetype* pArchetype, Key& outKey);
    bool UpdateProfile(cSpeciesProfile* pProfile, const Key& key);
    int GetMatchingPlantProfiles(ProfileVector& results, int maxCount, int plantType);
    int GetMatchingCreatureKeys(ProfileVector& out, uint32_t archetypeId, int count, int a, bool b);
    int GetMatchingCreatureKeys(ProfileVector& out, cSpeciesArchetype* pArchetype, int count, int a, bool b);
    cSpeciesArchetype* GetSpeciesArchetype(uint32_t id, uint32_t level);
    cSpeciesArchetype* GetDefaultArchetype();

    void* vptr;                              // 0x00
    eastl::SpeciesMap mSpecies;              // 0x04
    eastl::SpeciesMap mOldSpeciesMapping;    // 0x24
    eastl::SpeciesMap mPlantSpecies;         // 0x44
    eastl::SpeciesMap mReplacementSpecies;   // 0x64
    eastl::SpeciesMap mReplacementCache;     // 0x84
    Key mAvatarSpeciesKey;                   // 0xA4
    eastl::ArchetypeMap mArchetypes;         // 0xB0
};


// @ 0x004DF2D0 ?RandomInRange@SP@@
float RandomInRange(const Vector2& range)
{
    return (float)RandomRange(&sMathRandom, range[0], range[1]);
}

// @ 0x004DF310 ?SetAvatarSpecies@cSPEditorSpeciesManager@SP@@
void cSPEditorSpeciesManager::SetAvatarSpecies(const Key& key)
{
    mAvatarSpeciesKey = key;
    if (key.mInstance)
        ObjectTemplateDB()->Prefetch(key, true);
    MessageBasicRC5 msg(0x3795725);
    ScratchSlots<2>();
    msg.SetUint32(0, key.mType);
    msg.SetUint32(1, key.mInstance);
    msg.SetUint32(2, key.mGroup);
    ScratchSlots<1>();
    MessageServer()->MessageSend(msg.mId, &msg, 0);
}

// @ 0x004DF3E0 ?SetAvatarProfile@cSPEditorSpeciesManager@SP@@
void cSPEditorSpeciesManager::SetAvatarProfile(cSpeciesProfile* pProfile)
{
    SetAvatarSpecies(pProfile->mSpeciesKey);
}

// @ 0x004DF420 ?GetAvatarProfile@cSPEditorSpeciesManager@SP@@
cSpeciesProfile* cSPEditorSpeciesManager::GetAvatarProfile()
{
    return GetProfile(mAvatarSpeciesKey);
}

// @ 0x004DF440 ?GetPlantProfile@cSPEditorSpeciesManager@SP@@
cSpeciesProfile* cSPEditorSpeciesManager::GetPlantProfile(const Key& key)
{
    ScratchSlots<27>();
    cSpeciesProfile* pProfile = FindProfile(mPlantSpecies, key);
    if (!pProfile) {
        Key k = key;
        if (ResourceExists(&k)) {
            pProfile = FindProfile(mPlantSpecies, k);
            if (!pProfile) {
                cSpeciesProfile* pNew = new ("Simulator/cSpeciesProfile", 0, 0, 0, 0) cSpeciesProfile(k, true);
                mPlantSpecies[k] = pNew;
                pProfile = FindProfile(mPlantSpecies, k);
            }
        }
    }
    return pProfile;
}

// @ 0x004DF550 ?GetProfile@cSPEditorSpeciesManager@SP@@
cSpeciesProfile* cSPEditorSpeciesManager::GetProfile(const Key& key)
{
    if (!key.mInstance && !mAvatarSpeciesKey.mInstance)
        return 0;
    ScratchSlots<27>();
    cSpeciesProfile* pProfile = FindProfile(mSpecies, key);
    if (!pProfile) {
        Key k = key;
        if (!k.mInstance) {
            k = mAvatarSpeciesKey;
            pProfile = FindProfile(mSpecies, k);
            if (pProfile)
                return pProfile;
        }
        if (ResourceExists(&k)) {
            pProfile = FindProfile(mSpecies, k);
            if (!pProfile) {
                cSpeciesProfile* pNew = new ("Simulator/cSpeciesProfile", 0, 0, 0, 0) cSpeciesProfile(k, false);
                mSpecies[k] = pNew;
                pProfile = FindProfile(mSpecies, k);
            }
        }
    }
    return pProfile;
}

// @ 0x004DF6D0 ?FindProfile@cSPEditorSpeciesManager@SP@@
cSpeciesProfile* cSPEditorSpeciesManager::FindProfile(eastl::SpeciesMap& map, const Key& key)
{
    ScratchSlots<14>();
    eastl::SpeciesMap::const_iterator it = map.find(key);
    if (it != map.end() && it.mpNode->mpProfile) {
        cSpeciesProfile* pProfile = it.mpNode->mpProfile;
        if (!pProfile->mbLoaded) {
            InitStatics();
            if (!pProfile->Load(pProfile->mSpeciesKey))
                return 0;
        }
        return pProfile;
    }
    return 0;
}

// @ 0x004DF790 ?GetDefaultReplacementKey@cSPEditorSpeciesManager@SP@@
bool cSPEditorSpeciesManager::GetDefaultReplacementKey(const Key& key, Key& outKey)
{
    cSpeciesArchetype* pArchetype = GetSpeciesArchetype(0xdada0591, 0);
    if (pArchetype)
        return GetReplacementKeyForArchetype(key, pArchetype, outKey);
    return false;
}

// @ 0x004DF7D0 ?GetReplacementKey@cSPEditorSpeciesManager@SP@@
bool cSPEditorSpeciesManager::GetReplacementKey(const Key& key, uint32_t archetypeId, Key& outKey)
{
    cSpeciesArchetype* pArchetype = GetSpeciesArchetype(archetypeId, 0);
    if (!pArchetype)
        pArchetype = GetSpeciesArchetype(0xdada0591, 0);
    if (pArchetype)
        return GetReplacementKeyForArchetype(key, pArchetype, outKey);
    return false;
}

// @ 0x004DF830 ?GetReplacementKeyForArchetype@cSPEditorSpeciesManager@SP@@
bool cSPEditorSpeciesManager::GetReplacementKeyForArchetype(const Key& key, cSpeciesArchetype* pArchetype, Key& outKey)
{
    eastl::SpeciesMap::iterator it = mReplacementSpecies.find(key);
    if (it != mReplacementSpecies.end()) {
        cSpeciesProfile* pProfile = it.mpNode->mpProfile;
        outKey = pProfile->mSpeciesKey;
        return true;
    }
    it = mReplacementCache.find(key);
    if (it != mReplacementCache.end()) {
        delete it.mpNode->mpProfile;
        mReplacementCache.erase(it);
    }
    ConstraintVector constraints = ConstraintVector(DefaultAllocTag());
    constraints.reserve(2);
    constraints.push_back(FunctionalMatch::Constraint(0x3cc89b1, 0, 0x913b23be));
    ProfileVector profiles;
    int n = FindMatchingCreatures(profiles, pArchetype, 1, 0, false, constraints);
    if (!n)
        n = FindMatchingCreatures(profiles, pArchetype, 1, 0, true, constraints);
    if (n) {
        cSpeciesProfile* pProfile = profiles[0];
        outKey = pProfile->mSpeciesKey;
        mReplacementSpecies[key] = pProfile;
        return true;
    }
    return false;
}

// @ 0x004DFB50 ?UpdateProfile@cSPEditorSpeciesManager@SP@@
bool cSPEditorSpeciesManager::UpdateProfile(cSpeciesProfile* pNewProfile, const Key& key)
{
    Key oldKey = pNewProfile->mSpeciesKey;
    cSpeciesProfile* pProfile = pNewProfile;
    if (pProfile) {
        bool bResult = pProfile->Load(key);
        if (bResult) {
            if (oldKey != key) {
                ScratchSlots<12>();
                eastl::SpeciesMap::iterator it = mSpecies.find(key);
                if (it != mSpecies.end()) {
                    cSpeciesProfile* pOld = it.mpNode->mpProfile;
                    delete pOld;
                }
                mSpecies[key] = pProfile;
                mSpecies.erase(oldKey);
                mOldSpeciesMapping[oldKey] = pProfile;
            }
            ScratchSlots<52>();
            if (oldKey == mAvatarSpeciesKey)
                SetAvatarSpecies(key);
        }
        return bResult;
    }
    return false;
}

// @ 0x004DFD50 ?GetMatchingPlantProfiles@cSPEditorSpeciesManager@SP@@
int cSPEditorSpeciesManager::GetMatchingPlantProfiles(ProfileVector& results, int maxCount, int plantType)
{
    IObjectTemplateDB* pDB = ObjectTemplateDB();
    if (pDB) {
        ConstraintVector constraints(1, FunctionalMatch::Constraint(0x2dd90af, 0, 0x438f6347));
        if (plantType != -1)
            constraints.push_back(FunctionalMatch::Constraint(0x2dc9d1e, 0, plantType));
        KeyVector keys;
        pDB->FindTemplates(keys, maxCount, constraints);
        int n = 0;
        for (Key *it = keys.mpBegin, *itEnd = keys.mpEnd; n < maxCount && it != itEnd; ++it) {
            const Key* pKey = it;
            if (pKey->mGroup) {
                cSpeciesProfile* pProfile = GetPlantProfile(*pKey);
                if (pProfile)
                    results[n++] = pProfile;
                else
                    pDB->Remove(*pKey, 0);
            }
        }
        return n;
    }
    return 0;
}

// @ 0x004DFF50 ?GetMatchingCreatureKeys@cSPEditorSpeciesManager@SP@@QAEHAAUProfileVector@2@IHH_N@Z
int cSPEditorSpeciesManager::GetMatchingCreatureKeys(ProfileVector& out, uint32_t archetypeId, int count, int a, bool b)
{
    eastl::ArchetypeMap::iterator it = mArchetypes.find(archetypeId);
    ScratchSlots<14>();
    if (it != mArchetypes.end()) {
        cSpeciesArchetype* pArchetype = &it.mpNode->mValue;
        return GetMatchingCreatureKeys(out, pArchetype, count, a, b);
    }
    return 0;
}

// @ 0x004DFFF0 ?GetMatchingCreatureKeys@cSPEditorSpeciesManager@SP@@QAEHAAUProfileVector@2@PAVcSpeciesArchetype@2@HH_N@Z
int cSPEditorSpeciesManager::GetMatchingCreatureKeys(ProfileVector& out, cSpeciesArchetype* pArchetype, int count, int a, bool b)
{
    ConstraintVector constraints;
    int n;        // unused locals: they reproduce the original frame
    int result;
    ScratchSlots<5>();
    return FindMatchingCreatures(out, pArchetype, count, a, b, constraints);
}

// @ 0x004E0050 ?GetSpeciesArchetype@cSPEditorSpeciesManager@SP@@
cSpeciesArchetype* cSPEditorSpeciesManager::GetSpeciesArchetype(uint32_t id, uint32_t level)
{
    ScratchSlots<12>();
    cSpeciesArchetype* pResult = 0;
    eastl::ArchetypeMap::iterator it = mArchetypes.find(id);
    if (it != mArchetypes.end()) {
        pResult = &it.mpNode->mValue;
        if (level > 0) {
            uint32_t idx = level - 1;
            if (idx < pResult->mParentIds.size()) {
                ScratchSlots<14>();
                uint32_t parentId = pResult->mParentIds.mpBegin[idx];
                it = mArchetypes.find(parentId);
                if (it != mArchetypes.end())
                    pResult = &it.mpNode->mValue;
            }
        }
    }
    return pResult;
}

// @ 0x004E01B0 ?GetDefaultArchetype@cSPEditorSpeciesManager@SP@@
cSpeciesArchetype* cSPEditorSpeciesManager::GetDefaultArchetype()
{
    return GetSpeciesArchetype(0xaed08dd4, 0);
}

} // namespace SP
#pragma pack(pop)
