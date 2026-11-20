// Slice s00c74d30 - SporeApp 0x00c74d30..0x00c75e30
// SP::cSPPlanetaryArtifact / cSPToolObject / player-war bookkeeping helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: only the small helpers below were reconstructed within this pass; the
// remaining slice VAs are recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int i32;

// ---- receiver types ----------------------------------------------------------

// Game-noun manager interface slice used by FUN_00c754e0.
struct cGameNounManager {
    i32   GetKind();                               // 0x00bb9ae0
    void* GetAvatar();                             // 0x00b1fdb0
};

struct cStarManager {                              // returned by SP::StarManager(avatar)
    void* GetEmpireByID();                         // 0x00ba9370
};

struct cEmpire {
    void  SetValue(i32 v);                         // 0x00c322f0
};

void* __cdecl FUN_00b3d2a0(void* avatar);          // 0x00b3d2a0 (SP::StarManager)

// ---- counter / stack helper ---------------------------------------------------
// Two adjacent counters live at 0x124c (current depth, clamped to [0,4]) and
// 0x1250 (accumulated count, only touched when the caller asks for it).
struct cDepthCounter {
    u8   mPad0000[0x124c];
    i32  mDepth;                                   // 0x124c
    i32  mTotal;                                   // 0x1250

    void Increment(bool countIt);                  // 0x00c755c0
    void Decrement(bool countIt);                  // 0x00c755f0
};

// @ 0x00c754e0
// If the noun is a level-5 object, hand its owning empire a zero value.
void __stdcall FUN_00c754e0(cGameNounManager* self)
{
    if (self->GetKind() == 5) {
        void* avatar = self->GetAvatar();
        cStarManager* stars = (cStarManager*)FUN_00b3d2a0(avatar);
        void* empire = stars->GetEmpireByID();
        if (empire)
            ((cEmpire*)empire)->SetValue(0);
    }
}

// @ 0x00c755c0
// Raises the depth counter, saturating at 5; also raises the total when asked.
void cDepthCounter::Increment(bool countIt)
{
    if (mDepth < 5) {
        mDepth = mDepth + 1;
        if (countIt)
            mTotal = mTotal + 1;
    }
}

// @ 0x00c755f0
// Lowers the depth counter, saturating at 0; also lowers the total when asked.
void cDepthCounter::Decrement(bool countIt)
{
    if (0 < mDepth) {
        mDepth = mDepth - 1;
        if (countIt)
            mTotal = mTotal - 1;
    }
}

// ---- SP::cSPPlanetaryArtifact::Set (0x00c74d30) ------------------------------
//
// The generated SP/cSPPlanetaryArtifact.h re-laid the artifact's tail 0x108
// bytes too low: retail keeps this block at 0x638..0x660 (mItemType is
// compared at 0x658 and mItemID is copied to 0x64c).  The stand-ins below
// carry the retail offsets and only the interface slots this function calls.

struct ArtifactKey {                       // EA::ResourceMan::Key, 12 bytes
    u32 mType;                             // 0x00
    u32 mGroup;                            // 0x04
    u32 mInstance;                         // 0x08
};

struct ArtifactVariant {                   // EA::Variant tail; type id at +0x12
    u8  mPad0000[0x12];
    unsigned short mTypeId;                // 0x12 (0xd == EA::Variant::kTypeFloat)

    float* GetFloat() const;               // 0x0041ea70 (typed accessor, this in ecx)
};

struct ArtifactPropertyList {              // SP::cPropertyList (slots used here)
    virtual int AddRef();                                          // slot 0
    virtual int Release();                                         // slot 1
    virtual ~ArtifactPropertyList();                               // slot 2
    virtual void* AsInterface(void*);                              // slot 3
    virtual int GetRefCount();                                     // slot 4
    virtual void SetProperty(u32, ArtifactVariant const&);         // slot 5
    virtual void RemoveProperty(u32);                              // slot 6
    virtual bool HasProperty(u32) const;                           // slot 7
    virtual bool GetPropertyWritable(u32, ArtifactVariant**);      // slot 8
    virtual bool GetProperty(u32, ArtifactVariant const**) const;  // slot 9 (retail 0x24)
};

struct ArtifactPropertyManager {           // SP::cIPropertyManager (slots used here)
    virtual int AddRef();                                          // slot 0
    virtual int Release();                                         // slot 1
    virtual bool Init();                                           // slot 2
    virtual bool Shutdown();                                       // slot 3
    virtual bool GetIDFromName(char const*, u32*);                 // slot 4
    virtual char const* GetNameFromID(u32);                        // slot 5
    virtual bool GetGroupIDFromName(char const*, u32*);            // slot 6
    virtual char const* GetGroupNameFromID(u32);                   // slot 7
    virtual bool HasPropertyList(u32, u32);                        // slot 8
    virtual int GetPropertyGroupCount();                           // slot 9
    virtual int GetPropertyListCount();                            // slot 10
    virtual bool GetPropertyList(u32, u32, ArtifactPropertyList**);// slot 11 (retail 0x2c)
};

// Embedded model object at +0x34: retail dispatches through its slot 0x94
// with the model key.  Only that one slot is identified here.
struct ArtifactModel {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36();
    virtual void SetModelKey(ArtifactKey const&);                  // slot 37, retail 0x94
};

extern u32 gItemPropertyListIDByType[];                        // 0x01578c1c

ArtifactPropertyManager* __cdecl PropertyManager();            // 0x0067de30
bool __cdecl GetPropertyAsKey(ArtifactPropertyList*, u32, ArtifactKey*); // 0x006a1250
u32 __cdecl GetCurrentGameMode();                              // 0x00b5b800

struct cArtifact {
    u8  mPad0000[0x34];
    ArtifactModel mModel;                  // 0x034 (embedded, virtual)
    u8  mPad0038[0x638 - 0x38];
    u32 mChargeCount;                      // 0x638
    ArtifactPropertyList* mPropertyList;   // 0x63c
    u32 mLootDropTimeS;                    // 0x640
    float mPlumpScale;                     // 0x644
    float mNormalScale;                    // 0x648
    ArtifactKey mItemID;                   // 0x64c
    int mItemType;                         // 0x658 (SP::eInventoryItemType)
    bool mHasMoved;                        // 0x65c
    bool mAbductable;                      // 0x65d
    float mCollectionScale;                // 0x660

    void Set(int itemType, ArtifactKey const& itemID, int chargeCount, bool moved);
};

// @ 0x00c74d30
// Store the artifact's item type, key, charge count and moved flag; when the
// type changes, rebuild its property list and pull the plump/normal scale and
// the model key for the new type, then re-evaluate whether it is abductable.
void cArtifact::Set(int itemType, ArtifactKey const &itemID, int chargeCount, bool moved)
{
    mItemID = itemID;
    mChargeCount = chargeCount;
    mHasMoved = moved;
    if (itemType == mItemType)
        return;
    mItemType = itemType;

    u32 listID = gItemPropertyListIDByType[itemType];
    ArtifactPropertyManager *pm = PropertyManager();

    ArtifactPropertyList *oldList = mPropertyList;
    if (oldList != 0) {
        mPropertyList = 0;
        oldList->Release();
    }
    pm->GetPropertyList(mItemID.mType, listID, &mPropertyList);

    ArtifactVariant const *value;
    if (mPropertyList != 0 && mPropertyList->GetProperty(0xe5663079u, &value) && value->mTypeId == 0xd)
        mNormalScale = *value->GetFloat();
    if (mPropertyList != 0 && mPropertyList->GetProperty(0x49593334u, &value) && value->mTypeId == 0xd)
        mPlumpScale = *value->GetFloat();

    mAbductable = (GetCurrentGameMode() == 0x1654c05u);

    ArtifactKey modelKey;
    modelKey.mType = 0;
    modelKey.mGroup = 0;
    modelKey.mInstance = 0;
    GetPropertyAsKey(mPropertyList, 0xfadf5aadu, &modelKey);
    mModel.SetModelKey(modelKey);
}
