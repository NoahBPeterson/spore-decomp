// src/game/SPGonzago/SPPlanetaryArtifact.cpp -- migrated from slice(s) s00c74d30, s00c73cb0, s00c68280 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlanetaryArtifact.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_14727c8[];
extern "C" char g_1472830[];
extern "C" char g_1472898[];
extern "C" char g_14728a0[];
extern "C" char g_147299c[];
extern "C" char g_14729b0[];
extern "C" char g_1472bf0[];
extern "C" char g_1472bdc[];
extern "C" char g_1472ae0[];
extern "C" char g_1472ad8[];
extern "C" char g_1472a70[];
extern "C" char g_1472a08[];
extern "C" char g_1694514[];
extern "C" char g_1694518[];
extern "C" char g_169451c[];
#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)

#include "game/types.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cMovableDestructibleOrnament.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern int g_guard1693e00;       // 0x1693e00
extern int g_data1693dec[3];     // 0x1693dec
extern "C" void __cdecl FUN_013c4150();
#include <stdlib.h>
#include <math.h>
#include "SP/cSPPlanetaryArtifact.h"
#include "SP/cCivData.h"
#include "SP/cPropertyManager.h"
#include "SP/cEmpire.h"
#include "SP/cStarManager.h"

// ---- items of slice s00c68280 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_guard1693e00;       // 0x1693e00
extern int g_data1693dec[3];     // 0x1693dec
extern "C" void __cdecl FUN_013c4150();
// ---- items of slice s00c68280 end

// ---- items of slice s00c73cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_13eb1bc;   // 0x013eb1bc
void* NounManager();                                                       // 0x00b3d300
void* FUN_00f47380(void* p);                                               // 0x00f47380 operator delete[]
void* FUN_01021260();                                                      // 0x01021260
void  GetPropertyAsKey(void* obj, int key, void* out);                     // 0x006a1250
void  RemoveArtifact(void* a, void* b, void* c);                           // 0x00c71160
void* GetSpaceCombatTuning();                                              // 0x01029940
struct SpaceCombatTuning { float GetColonyObjectHealth(); };               // 0x0102a7f0
struct cCombatant { void TakeHit(float d, int a, int b, int c, int e); };  // 0x00bfcdd0
struct NounMgr {                   // SP::NounManager() result
    void* GetCurrentTerrainSphere();   // 0x00f67d90  returns this->+0x74
    void* FUN_00b25f40(int id);        // 0x00b25f40
    void  RemoveNoun(void* noun);      // 0x00b225d0
};
struct MovableOrn { void cMovOrnCtor(); void cMovOrnDtor(); void FUN_00c69030(); };
struct Pod12 { void* a; void* b; void* c; };
struct cToolObject {
    void* mVtbl0;                  // +0x000
    void* mVtbl4;                  // +0x004
    char  mPad08[0x34 - 0x08];     // +0x008
    void* mVtbl34;                 // +0x034
    char  mPad38[0x108 - 0x38];    // +0x038
    void* mVtbl108;                // +0x108
    char  mPad10c[0x508 - 0x10c];  // +0x10c
    void* mVtbl508;                // +0x508
    char  mPad50c[0x534 - 0x50c];  // +0x50c
    float m534;                    // +0x534
    char  mPad538[0x540 - 0x538];  // +0x538
    float m540;                    // +0x540
    char  mPad544[0x5d0 - 0x544];  // +0x544
    void* mVtbl5d0;                // +0x5d0
    char  mPad5d4[0x638 - 0x5d4];  // +0x5d4
    void* m638;                    // +0x638
    void* m63c;                    // +0x63c
    Pod12 m640;                    // +0x640
    void* m64c;                    // +0x64c
    void* m650;                    // +0x650
    void* m654;                    // +0x654

    void* FUN_00c74950();          // ctor
    void* FUN_00c749e0(unsigned char flag);  // deleting dtor
    void  FUN_00c74a30(void* v);
};
struct cPlanetaryArtifact {
    void* mVtbl0;                  // +0x000
    void* mVtbl4;                  // +0x004
    char  mPad08[0x34 - 0x08];     // +0x008
    union { void* p34; int i34; }; // +0x034  secondary vptr / state int
    char  mPad38[0x108 - 0x38];    // +0x038
    void* mVtbl108;                // +0x108
    char  mPad10c[0x130 - 0x10c];  // +0x10c
    void* m130;                    // +0x130
    char  mPad134[0x144 - 0x134];  // +0x134
    void* m144;                    // +0x144 (8-byte sub-record)
    char  mPad148[0x150 - 0x148];  // +0x148
    int   m150;                    // +0x150
    char  mPad154[0x508 - 0x154];  // +0x154
    void* mVtbl508;                // +0x508
    char  mPad50c[0x5d0 - 0x50c];  // +0x50c
    void* mVtbl5d0;                // +0x5d0
    char  mPad5d4[0x638 - 0x5d4];  // +0x5d4
    void* m638;                    // +0x638
    void* m63c;                    // +0x63c
    void* m640;                    // +0x640
    void* m644;                    // +0x644
    void* m648;                    // +0x648
    void* m64c;                    // +0x64c
    void* m650;                    // +0x650
    void* m654;                    // +0x654
    int   m658;                    // +0x658
    char  m65c;                    // +0x65c
    char  m65d;                    // +0x65d
    char  m65e;                    // +0x65e
    char  mPad65f[1];              // +0x65f
    float m660;                    // +0x660

    void* FUN_00c74a50();          // ctor
    void  FUN_00c74ba0();
    void  FUN_00c74bd0();
    void  FUN_00c74c20(float dmg, int a, int b, int c, int d);
    bool  FUN_00c74ca0();
};
struct RefObj { virtual void v0(); virtual void v1(); };
// ---- items of slice s00c73cb0 end

// ---- items of slice s00c74d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned int u32;
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
struct ArtifactModel {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
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
// ---- items of slice s00c74d30 end

// @ 0x00c69110
void* FUN_00c69110()
{
    if ((g_guard1693e00 & 1) == 0) {
        g_guard1693e00 |= 1;
        g_data1693dec[0] = 0;
        g_data1693dec[1] = 0;
        g_data1693dec[2] = 0;
        atexit(FUN_013c4150);
    }
    return g_data1693dec;
}

// @ 0x00c74950
void* cToolObject::FUN_00c74950()
{
    ((MovableOrn*)this)->cMovOrnCtor();
    mVtbl0 = (void*)g_14729b0;
    mVtbl4 = (void*)g_147299c;
    mVtbl34 = (void*)g_14728a0;
    mVtbl108 = (void*)g_1472898;
    mVtbl508 = (void*)g_1472830;
    mVtbl5d0 = (void*)g_14727c8;
    m638 = 0;
    m63c = 0;
    m640.a = 0;
    m640.b = 0;
    m640.c = 0;
    m64c = 0;
    m650 = 0;
    m654 = 0;
    float h = ((struct SpaceCombatTuning*)GetSpaceCombatTuning())->GetColonyObjectHealth();
    m540 = h;
    m534 = h;
    return this;
}

// @ 0x00c749e0
void* cToolObject::FUN_00c749e0(unsigned char flag)
{
    mVtbl0 = (void*)g_14729b0;
    mVtbl4 = (void*)g_147299c;
    mVtbl34 = (void*)g_14728a0;
    mVtbl108 = (void*)g_1472898;
    mVtbl508 = (void*)g_1472830;
    mVtbl5d0 = (void*)g_14727c8;
    ((MovableOrn*)this)->cMovOrnDtor();
    if (flag & 1)
        FUN_00f47380(this);
    return this;
}

// @ 0x00c74a30
void cToolObject::FUN_00c74a30(void* v)
{
    Pod12 t;
    t.a = v;
    t.b = 0;
    t.c = 0;
    m640 = t;
}

// @ 0x00c74a50
void* cPlanetaryArtifact::FUN_00c74a50()
{
    ((MovableOrn*)this)->cMovOrnCtor();
    float f = g_13eb1bc;
    m638 = 0;
    mVtbl0 = (void*)g_1472bf0;
    mVtbl4 = (void*)g_1472bdc;
    p34 = (void*)g_1472ae0;
    mVtbl108 = (void*)g_1472ad8;
    mVtbl508 = (void*)g_1472a70;
    mVtbl5d0 = (void*)g_1472a08;
    _ReadWriteBarrier();
    m63c = 0;
    m640 = 0;
    m64c = *(void**)g_1694514;
    m650 = *(void**)g_1694518;
    _ReadWriteBarrier();
    void* t = *(void**)g_169451c;
    m65c = 0;
    m65d = 0;
    m654 = t;
    m658 = -1;
    m65e = 1;
    m660 = f;
    return this;
}

// @ 0x00c74ba0
void cPlanetaryArtifact::FUN_00c74ba0()
{
    if (m63c != 0) {
        void* p = m63c;
        m63c = 0;
        ((RefObj*)p)->v1();
    }
    ((MovableOrn*)this)->FUN_00c69030();
}

// @ 0x00c74bd0
void cPlanetaryArtifact::FUN_00c74bd0()
{
    mVtbl0 = (void*)0x1472bf0;
    mVtbl4 = (void*)0x1472bdc;
    p34 = (void*)0x1472ae0;
    mVtbl108 = (void*)0x1472ad8;
    mVtbl508 = (void*)0x1472a70;
    mVtbl5d0 = (void*)0x1472a08;
    if (m63c != 0)
        ((RefObj*)m63c)->v1();
    ((MovableOrn*)this)->cMovOrnDtor();
}

// @ 0x00c74c20
void cPlanetaryArtifact::FUN_00c74c20(float dmg, int a, int b, int c, int d)
{
    ((cCombatant*)this)->TakeHit(dmg, a, b, c, d);
    if (i34 == 2) {
        i34 = 0;
        if (m150 == 4) {
            void* p = FUN_01021260();
            if (p != 0)
                RemoveArtifact(*(void**)((char*)p + 0x13c), (void*)&m144, m130);
            ((NounMgr*)NounManager())->RemoveNoun((char*)this - 0x508);
        }
    }
}

// @ 0x00c74ca0
bool cPlanetaryArtifact::FUN_00c74ca0()
{
    unsigned local[3];
    local[0] = 0;
    local[1] = 0;
    local[2] = 0;
    GetPropertyAsKey(m63c, 0x34f1a4f, local);
    return local[0] == 0x7ecbe6f5u;
}

// @ 0x00c74d30
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
