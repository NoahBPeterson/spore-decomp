// Slice s004d2200: creature-key matching for the species editor.
// Real symbol: free function ?GetMatchingCreatureKeys@@YAHPAIIHID0@Z (the PDB candidate name
// SP::cSPEditorSpeciesManager::GetMatchingCreatureKeys comes from caller scoring; the mangled
// name spells the two object parameters as "unsigned int", the code dereferences both).
// The function builds a FunctionalMatch::Constraint, asks the ObjectTemplateDB for the
// matching creature keys, drops the avatar's own profile and returns the count written.
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#pragma pack(push, 4)

struct cSpeciesProfile;

namespace EA { namespace ResourceMan {
struct Key {                            // 0xc bytes
    uint32_t instance;                  // +0x0
    uint32_t type;                      // +0x4
    uint32_t group;                     // +0x8
};
}}

// OTDB key: the same three dwords under the database's own name (the vector<ResourceKey>
// instantiations of the original live under this symbol). The key members are inherited
// unchanged, so a `ResourceKey&` is a `EA::ResourceMan::Key&` at the same address.
struct ResourceKey : EA::ResourceMan::Key { };

// ---------------------------------------------------------------------------
// eastl vector plumbing, spelled so the destructions resolve to the original's symbols:
// eastl sp vector allocator and VectorBase.
// ---------------------------------------------------------------------------
namespace eastl {

struct sp_vector_allocator {
    const char* mpName;                 // +0x0
    uint32_t mFlags;                    // +0x4
};

template<typename T, typename A>
struct VectorBase {
    T* mpBegin;                         // +0x0
    T* mpEnd;                           // +0x4
    T* mpCapacity;                      // +0x8
    A mAllocator;                       // +0xc
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) { }
    ~VectorBase();                      // <ResourceKey> 0x005156b0, <Constraint> 0x004ab0d0
};

template<typename T, typename A = sp_vector_allocator>
class vector : public VectorBase<T, A> {
public:
    typedef T* iterator;
    ~vector() {
        T* end = this->mpEnd;
        for (T* p = this->mpBegin; p < end; ++p)
            p->~T();
    }
    void reserve(uint32_t n);           // 0x0041e4d0 (12-byte elements, allocator at +0xc)
    void push_back(const T& value);     // 0x004e18e0 (vector<Constraint>, 0x24-byte elements)
};

}

namespace SP { namespace FunctionalMatch {

enum eType { kInteger = 0x2e1a75d };
enum EqualConstraint { kEqual = 0 };

// SP::FunctionalMatch::Constraint: one 12-byte-table parameter plus a nested key list.
struct Constraint {
    unsigned int mParameter;            // +0x00  selected 12-byte-table entry
    eType mType;                        // +0x04  kInteger
    union {
        struct { int mMin; int mMax; } mIntVal;               // +0x08 / +0x0c
        struct { float mMin; float mMax; } mFloatVal;         // +0x08 / +0x0c
    };
    eastl::vector<Constraint, eastl::sp_vector_allocator> mConstraints;   // +0x10 (0x14 bytes)
    Constraint(unsigned int param, EqualConstraint, int value);           // 0x00558960
};

}}

typedef eastl::vector<SP::FunctionalMatch::Constraint, eastl::sp_vector_allocator> ConstraintVector;
typedef eastl::vector<ResourceKey, eastl::sp_vector_allocator> ResourceKeyVector;

// SP::cSpeciesRecord: one row of the species manager's hash map.
struct cSpeciesRecord {
    uint32_t pad00[0x14 / 4];           // +0x00 .. +0x13
    uint32_t mSpeciesKey;               // +0x14  species id
    uint32_t pad18[(0x2d0 - 0x18) / 4]; // +0x18 .. +0x2cf
    int mStatus;                        // +0x2d0  2/3 = profile-only record
};

// Creature summary the match is derived from.
struct cCreatureSummary {
    uint32_t pad000[(0x504) / 4];       // +0x000 .. +0x503
    EA::ResourceMan::Key mKey;          // +0x504
};

// SP::cSPEditorSpeciesManager (singleton behind 0x00401090).
struct cSPEditorSpeciesManager {
    cSpeciesProfile* GetAvatarProfile();                            // 0x004df420
    cSpeciesProfile* GetProfile(const EA::ResourceMan::Key& key);   // 0x004df550
};

cSPEditorSpeciesManager* GetSpeciesManagerInstance();   // 0x00401090 (global at 0x015d0c24)

// Object template database holding the template -> creature-key map.
struct ObjectTemplateDB {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual void GetMatchingKeys(ResourceKeyVector* pKeys, int maxCount,
                                 ConstraintVector* pParams);                         // +0x24
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14();
    // Same DB query, narrowed to one template key (a second overload in the original).
    virtual void GetMatchingKeysByTemplate(ResourceKeyVector* pKeys, int maxCount,
                                           const EA::ResourceMan::Key* pKey,
                                           ConstraintVector* pParams);               // +0x3c
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28();
    virtual void OnMissingProfile(const EA::ResourceMan::Key* pKey, int flags);       // +0x74
};

namespace SP { ObjectTemplateDB* ObjectTemplateDB(); }   // 0x0067cb40 (singleton getter)

// Constraint key selected by the "use all species" flag (two 12-byte-table entries 0xc apart).
enum { kConstraintKeyMatch = 0x052def3f, kConstraintKeyAll = 0x052def4b };

// Output slot: the caller passes the address of the profile-pointer array to fill.
struct MatchResult {
    cSpeciesProfile** mpProfiles;       // +0x0
};

// @ 0x004D2200  SP::cSPEditorSpeciesManager::GetMatchingCreatureKeys
int GetMatchingCreatureKeys(MatchResult* pOut, cSpeciesRecord* pRecord, int maxCount,
                            cCreatureSummary* pSummary, unsigned char useAll, ConstraintVector* pParams)
{
    cSPEditorSpeciesManager* pManager = GetSpeciesManagerInstance();
    if (pRecord->mStatus == 3 || pRecord->mStatus == 2) {
        pOut->mpProfiles[0] = pManager->GetAvatarProfile();
        return 1;
    }
    int bAll = useAll != 0;   // kept: the original computes it once and re-tests the flag inline below
    ObjectTemplateDB* pDB = SP::ObjectTemplateDB();
    if (pDB == 0)
        return 0;
    ConstraintVector defaultParams;                     // zero-initialised: empty constraint list
    if (pParams == 0)
        pParams = &defaultParams;
    {
        SP::FunctionalMatch::Constraint query(useAll ? kConstraintKeyAll : kConstraintKeyMatch,
                                              SP::FunctionalMatch::kEqual, (int)pRecord->mSpeciesKey);
        pParams->push_back(query);
    }
    ResourceKeyVector keys;
    keys.reserve((uint32_t)(maxCount + 1));
    if (pSummary != 0 && pSummary->mKey.instance != 0)
        pDB->GetMatchingKeysByTemplate(&keys, maxCount + 1, &pSummary->mKey, pParams);
    else
        pDB->GetMatchingKeys(&keys, maxCount + 1, pParams);
    cSpeciesProfile* pAvatarProfile = pManager->GetAvatarProfile();
    int count = 0;
    ResourceKey* it = keys.mpBegin;
    ResourceKey* itEnd = keys.mpEnd;
    for (; count < maxCount && it != itEnd; ++it) {
        ResourceKey* pKey = it;
        cSpeciesProfile* pProfile = pManager->GetProfile(*pKey);
        if (pProfile == 0)
            pDB->OnMissingProfile(pKey, 0);
        else if (pProfile != pAvatarProfile) {
            pOut->mpProfiles[count] = pProfile;
            ++count;
        }
    }
    (void)bAll;
    return count;
}

#pragma pack(pop)
