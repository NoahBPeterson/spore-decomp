// src/game/SPGonzago/SPDramaManager.cpp -- migrated from slice(s) s01364b20, s00f21850, s00d50380, s00d4e4a0, s00d4d5c0, s00d4bc60, s00d4a930 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPDramaManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureAnimal.h"
#include "EA/Variant.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyList.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cStarManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cVarListSerializer.h"
#include "SP/cViewer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete_array(void *p);                                     // 0xf47380
extern "C" void  *SP_GetCurrentGameMode();          // 0x00b5b800
extern "C" void  *SP_NounManager();                 // 0x00b3d300
extern "C" void  *FUN_00b1fdb0(void *o);            // 0x00b1fdb0 cGameNounManager::GetAvatar
extern "C" void  *FUN_00bfc5f0(void *o);            // 0x00bfc5f0 cGameData::SetGameDataOwner2
extern "C" void  *FUN_00c0bbd0(void *o);            // 0x00c0bbd0 cSPCreatureBase::GetSpeciesProfile
extern "C" void  *PropertyManager();                // 0x0067de30
extern "C" void *RBTreeIncrement(void *node);                            // 0x921580
extern const float kCheckForMate;    // 0x1582f88 (mCheckForMateTimer)
extern float gVec0169e440[3];        // 0x0169e440

// ---- items of slice s00d4a930 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef int            i32;
#define FORCEINLINE __forceinline
extern "C" void  operator_delete_array(void *p);                                     // 0xf47380
extern "C" void  *SP_GetCurrentGameMode();          // 0x00b5b800
extern "C" void  *SP_NounManager();                 // 0x00b3d300
extern "C" u8     FUN_00c0b770(void *o);            // 0x00c0b770
extern "C" i32    FUN_00bca0c0(int a, int b, int c, int d); // 0x00bca0c0
extern "C" void  *FUN_00b1fdb0(void *o);            // 0x00b1fdb0 cGameNounManager::GetAvatar
extern "C" void  *FUN_00bfc5f0(void *o);            // 0x00bfc5f0 cGameData::SetGameDataOwner2
extern "C" void  *FUN_00c0bbd0(void *o);            // 0x00c0bbd0 cSPCreatureBase::GetSpeciesProfile
extern "C" void  *PropertyManager();                // 0x0067de30
extern "C" u8     FUN_006a10c0(void *plist, u32 hash, void *out); // 0x006a10c0 GetPropertyAsVector2
extern "C" void *RBTreeIncrement(void *node);                            // 0x921580
extern const float kCheckForMate;    // 0x1582f88 (mCheckForMateTimer)
extern float gVec0169e440[3];        // 0x0169e440
extern u8    gModeA;                 // 0x01654c01
extern u8    gModeB;                 // 0x01654c02
extern u32   kVtblA;                 // 0x0147b108
extern u32   kVtblB;                 // 0x013ec458
extern u32   kVtblC;                 // 0x0147b278
typedef void (__fastcall *ReleaseThunk)(void *self);
struct RefObj {
    void **m_vtbl;              // +0x00
};
FORCEINLINE void AutoRefRelease(void **ppField)
{
    void *pOld = *ppField;
    if (pOld != 0) {
        *ppField = 0;
        ((ReleaseThunk)((RefObj *)pOld)->m_vtbl[1])((RefObj *)pOld);
    }
}
struct ModeSetter {
    u8  m_pad00[0x44];
    u32 m_value44;     // +0x44
    void SetValue(u32 v);
};
struct Thresholded {
    u8    m_pad00[0x2c];
    float m_value2c;   // +0x2c
    bool IsBelowZero();
};
struct RBNode {
    RBNode *mpNodeLeft;    // +0x00
    RBNode *mpNodeRight;   // +0x04
    RBNode *mpNodeParent;  // +0x08
    u32     mColor;        // +0x0c
    u32     mKey;          // +0x10
    void   *mValue;        // +0x14
};
struct RBTreeHead {
    RBNode  mAnchor;       // +0x00 (anchor.mpNodeRight = root)
    u32     mCount;        // +0x14
};
struct RBTree {
    u32     m_gap0;        // +0x00
    RBNode  mAnchor;       // +0x04  anchor node (left=+0x04, right=+0x08, parent=+0x0c)
    u32     mCount;        // +0x18

    void equal_range(RBNode **out, u32 *key);   // 0x00d4b450
};
typedef void (__thiscall *VisitFn)(void *self, void *param);
struct TreeValue {
    void **m_vtbl;         // +0x00
};
struct cSPCreatureAnimal {
    void **m_vtbl;              // +0x00
    u8    m_pad04[0x131];
    u8    m_b135;               // +0x135
    u8    m_pad136[0xa12];
    u32   m_idB48;              // +0xb48
    void *m_pB4C;               // +0xb4c
    u8    m_padB50[8];
    u32   m_flagsB58;           // +0xb58
    u8    m_padB5C[2];
    u8    m_b5e;                // +0xb5e
};
struct cSPSubObject {
    u8  m_pad00[0x5fc];
    u32 m_flags5fc;             // +0x5fc
};
struct cSPDramaManager {
    void         **m_vtbl;              // +0x00
    u8             m_pad04[0x10];
    void          *m_mateTeacher14;     // +0x14  AutoRefCount<creature>
    u8             m_pad18[0x18];
    void          *m_stream30;          // +0x30
    void          *m_tuning34;          // +0x34
    void          *m_mate38;            // +0x38  AutoRefCount<creature>
    float          m_checkMate3c;       // +0x3c
    void          *m_tuning40;          // +0x40
    float          m_progress48;        // +0x48
    u8             m_pad4c[8];
    u8             m_tree54[0x20];      // +0x54  eastl::multimap<u32,AutoRefCount<...>>

    void  MatedWith(cSPCreatureAnimal *mate);   // 0x00d4b180
    void  ClearMate(cSPCreatureAnimal *mate);   // 0x00d4b1d0
    void  PostLoad(void *p);                    // 0x00d4b410
    int   IsValidBabyTeacher(cSPCreatureAnimal *c); // 0x00d4b2f0
};
struct RefEntry {
    u32   m_pad00;
    void *m_obj;           // +0x04
};
struct cDramaEventInstanceData {
    RefEntry *m_pBegin;    // +0x00
    RefEntry *m_pEnd;      // +0x04
    u8        m_pad08[8];
    u32       m_bits10;    // +0x10
    u8        m_pad14[4];
    u32       m_field18;   // +0x18
    u32       m_field1c;   // +0x1c
    float     m_vec20[2];  // +0x20 (cSPVector2)
    float     m_field28;   // +0x28
    float     m_field2c;   // +0x2c
    u8        m_flag30;    // +0x30
    u8        m_pad31[0x0f];
    void     *m_propList40; // +0x40  cPropertyList
    u8        m_pad44[0x30];

    void DestroyMembers();          // 0x00d4b4b0
    void Construct();               // 0x00d4ba40
    void InitFromTuning(int unused); // 0x00d4af80
};
typedef u32   *(__thiscall *GetUIntP)(void *self);    // 0x41ea00
typedef float *(__thiscall *GetFloatP)(void *self);   // 0x41ea70
typedef u8    *(__thiscall *GetBoolP)(void *self);    // 0x41e920
struct RefRange {
    RefEntry *m_begin;     // +0x00
    RefEntry *m_end;       // +0x04
};
typedef void (__thiscall *NotifyFn)(void *self);
typedef void (__thiscall *NotifyFnP)(void *self, void *param);
struct TuningOwner {
    void        **m_vtbl;       // +0x00
    u8            m_pad04[0x30];
    void         *m_tuning34;   // +0x34
    void         *m_field38;    // +0x38
    void         *m_tuning3c;   // +0x3c
    void         *m_tuning40;   // +0x40

    void ReloadTuning(int unused);    // 0x00d4b3c0
};
struct Vec3 { float x, y, z; };
// ---- items of slice s00d4a930 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" u8     FUN_00c0b770(void *o);            // 0x00c0b770
extern "C" i32    FUN_00bca0c0(int a, int b, int c, int d); // 0x00bca0c0
extern "C" u8     FUN_006a10c0(void *plist, u32 hash, void *out); // 0x006a10c0 GetPropertyAsVector2
extern u8    gModeA;                 // 0x01654c01
extern u8    gModeB;                 // 0x01654c02
extern u32   kVtblA;                 // 0x0147b108
extern u32   kVtblB;                 // 0x013ec458
extern u32   kVtblC;                 // 0x0147b278

// ---- items of slice s00d4bc60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern const float kF_13ec4d0;                    // 0x013ec4d0
extern const float kF_147b4bc;                    // 0x0147b4bc
extern const float kF_13ebc5c;                    // 0x013ebc5c
struct cSPVector2_s00d4_bc60 { float x, y; };
struct IInterface {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void* AsInterface(u32 ifaceId);            // +0x0c
};
struct Property {
    void*  mpValue;   // +0x00
    u8     pad04[0x0c];
    u8     m_flags10; // +0x10
    u8     pad11;
    u16    m_type12;  // +0x12
    float* GetFloat();                                 // 0x0041ea70
    u32*   GetUInt();                                  // 0x0041ea00
};
struct cPropertyList_s00d4_bc60 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool FindProperty(u32 id, Property** ppOut);  // +0x24
};
struct PairUR { u32 mKey; void* mValue; };                  // 8-byte vector_map entry
struct VecMapU32 { u32* mpBegin; u32* mpEnd; u32* mpCap; }; // eastl::vector_map<u32,u32>
PairUR* __cdecl LowerBound(PairUR* first, PairUR* last, const u32* key, bool flag); // 0x00d01260
struct RefMap {
    PairUR* mpBegin;                 // +0x00
    PairUR* mpEnd;                   // +0x04
    u8      pad08[0xc];              // +0x08
    bool    mbFlag;                  // +0x14  (eastl::less<u32> comparator)
    u8      pad15[3];

    __forceinline PairUR* find(u32 keyIn)
    {
        const u32 key = keyIn;
        PairUR* const e = mpEnd;
        PairUR* it = LowerBound(mpBegin, e, &key, mbFlag);
        if (it == e || keyIn < it->mKey) it = e;
        else if (it == it + 1) it = e;
        return it;
    }
    void DestroyMembers();           // 0x00d4b4b0
};
struct IEventVtbl {
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
    virtual void v28(int flag);                       // +0x28
    virtual void v2c();
    virtual void v30();                               // +0x30
};
namespace SP {
struct cDramaEventInstanceData_s00d4_bc60 {
    void** m_vtbl00;              // +0x00
    void** m_vtbl04;              // +0x04
    u8     pad08[4];              // +0x08
    u8     mFlag0c;               // +0x0c
    u8     pad0d[3];              // +0x0d
    u32    mEventMask10;          // +0x10
    i32    mEventType14;          // +0x14  index into sDramaEventToBitArray
    u32    mCountdown18;          // +0x18
    i32    mField1c;              // +0x1c
    cSPVector2_s00d4_bc60 mVec20;            // +0x20
    float  mFreq28;               // +0x28
    float  mActivationType2c;     // +0x2c
    u8     mFlag30;               // +0x30
    u8     pad31[3];
    void*  mStream34;             // +0x34
    void*  mField38;              // +0x38
    void*  mTuning3c;             // +0x3c
    cPropertyList_s00d4_bc60* mpPropList40;  // +0x40
    VecMapU32 mData44;            // +0x44
    u8     pad50[0xc];            // +0x50 .. +0x5c
    RefMap mGameDataMap5c;        // +0x5c
    Vec3   mPos74;                // +0x74

    __forceinline void* GetGameData(u32 key, u32 ifaceId)
    {
        PairUR* const e = mGameDataMap5c.mpEnd;
        PairUR* it = mGameDataMap5c.find(key);
        if (it == e) return 0;
        void* v = it->mValue;
        if (v == 0) return 0;
        return ((IInterface*)v)->AsInterface(ifaceId);
    }

    cDramaEventInstanceData_s00d4_bc60* FUN_00d4ca70(u8 flags);      // 0x00d4ca70  destructor
    Vec3* FUN_00d4bbd0(Vec3* out);                         // 0x00d4bbd0  GetNestPosition
    u8    FUN_00d4bd10();                                  // 0x00d4bd10
    void  FUN_00d4cf70();                                  // 0x00d4cf70
    __declspec(noinline) void* FUN_00d4cf10(u32 a, u32 b);      // 0x00d4cf10
    u8    GetGameDataIsUsable();                           // 0x00d4d030
    u8    PlayIdleIfFlagged();                             // 0x00d4d220
    void  PostLoadEvent(void* arg);                        // 0x00d4d180
    void  ReleaseGameDataObject(int arg);                  // 0x00d4d2b0
    u8    AnyGameDataFlagged();                            // 0x00d4d340
};
}
namespace SP {
struct cRainStormEvent : cDramaEventInstanceData_s00d4_bc60 {
    void TriggerEvent();                                   // 0x00d4bc60
};
}
namespace SP {
struct cSeaMonsterEvent : cDramaEventInstanceData_s00d4_bc60 {
    bool ShouldActivate();                                 // 0x00d4c650
};
}
namespace SP {
struct cNightPredatorEvent : cDramaEventInstanceData_s00d4_bc60 {
    bool ShouldActivate();                                 // 0x00d4d0b0
};
}
namespace SP {
struct cGameDataInfo {
    u8     pad00[0x40];
    void** mpArray40;             // +0x40  begin of a noun array
    void** mpArray44;             // +0x44  end
    u8     pad48[0x2c];           // +0x48 .. +0x74
    u8     mFlag74;               // +0x74
    u8     pad75[0x1b];
    u8     mFlag190;              // +0x190
    u8     pad191[0x4b7];
    void*  mCreature6c8;          // +0x6c8
};
}
namespace SP {
struct MMRange { void* mFirst; void* mSecond; };
}
namespace SP {
struct RBTreeMM {
    u8 pad00[4];
    void equal_range(MMRange* out, const u32* key);        // 0x00f21cd0
};
}
namespace SP {
void* __cdecl RBTreeIncrement(void* node);                  // 0x00921580
}
namespace SP {
struct cSPDramaManager_s00d4_bc60 {
    u8       pad00[0x50];
    RBTreeMM mDramaEvents;             // +0x50
    u32      mActiveDramaEventMask;    // +0x6c

    cDramaEventInstanceData_s00d4_bc60* GetActiveEvent(u32 type, bool onlyActive); // 0x00d4cad0
    bool  IsDramaEventActive(u32 type);                                // 0x00d4cb30
    void* GetActiveEventTuning(u32 type);                              // 0x00d4cb50
    void  HandleMeteorImpact(void* impact);                            // 0x00d4cb70
    void  TriggerEvent(cDramaEventInstanceData_s00d4_bc60* e, int a2);            // 0x00d4d530
};
}
void* __cdecl SP_PlanetModel();               // 0x00b3d350
void* __cdecl SP_StarManager();               // 0x00b3d2a0
void* __cdecl SP_PropertyManager();           // 0x0067de30
void* __cdecl SP_EventLog();                  // 0x00b3d3e0
void* __cdecl FUN_00b3d480();                 // 0x00b3d480
void  __cdecl SetGlobalProperty(u32 id, float v);           // 0x005ca880
void* __cdecl CreateUFO(u32 type, void* a, void* b);        // 0x0102acb0
void  __cdecl ApplyFilterConstraints(void* a, char b);      // 0x0102c7f0
void  __fastcall FUN_00fc6f00(void* self, Vec3 pos, float a);// 0x00fc6f00
void  __cdecl FUN_00aca360(void* self, void* o);            // 0x00aca360
struct RandomLCG {
    double RandomDoubleUniform();                 // 0x009360d0
};
RandomLCG gRand;                                  // 0x01601760
extern const float gVec0169e440_s00d4_bc60[3];               // 0x0169e440
extern u8     gGameModeA;                         // 0x01654c01
extern u8     gVec147aed8;                        // 0x0147aed8
extern u32    sDramaEventToBitArray[];            // 0x0147aef4
struct IStormAnchor {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void v10();
    virtual void* GetStormTarget();                  // +0x14
};
struct cPlanetModel_s00d4_bc60 {
    u8     pad00[0x24];
    IStormAnchor* mpAnchor24;            // +0x24
    u8     pad28[0x3c];
    void*  mpVisited64;                  // +0x64
    u8     pad68[0x28];
    void BuildSurfaceOrientation(Vec3* orient, Vec3* pos);              // 0x00b7f190
    void FUN_00b81630(Vec3* out, const Vec3* in);                      // 0x00b81630
    i32  GetContinent(const Vec3* pos);                                // 0x00b88590
    bool RayCast(const Vec3* dir, float radius, Vec3* out, float a,
                 u32 b, u32 c);                                        // 0x00b88770
    i32  FUN_00b7ea00(i32 continent);                                  // 0x00b7ea00
};
struct cUFO {
    u8    pad00[0x6c8];
    void* mCreature6c8;                                          // +0x6c8
    void FUN_00c3daa0(float a);                                  // 0x00c3daa0
    void FUN_00c3aa40(Vec3* n, Vec3* m);                         // 0x00c3aa40
};
struct cGameNounManager_s00d4_bc60 {
    void* GetAvatar();                                          // 0x00b1fdb0
};
struct cAvatarAnchor {                 // the sub-object embedded at avatar+0xc0
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
    virtual Vec3* GetPos();                                     // +0x2c
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
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
    virtual void vec();                                         // +0xec
};
struct cStarManager_s00d4_bc60 {
    void* FUN_00ba93b0();                                       // 0x00ba93b0
    float FUN_00885c90();                                       // 0x00885c90
};
struct cEmpire_s00d4_bc60 {
    u32 GetUFOKey();                                            // 0x00c326b0
};
struct cCreatureModeStrategy {
    static cCreatureModeStrategy* Instance();                   // 0x00d38840
    void FUN_00d39360(u32 a, void* ctx);                        // 0x00d39360
    void SignalCreatureEvent(u32 a);                            // 0x00d3cdc0
};
struct cTimeOfDay {
    static cTimeOfDay* Instance();                              // 0x00bc30b0
    float FUN_00bc2b30(const Vec3* pos);                        // 0x00bc2b30
    i32   FUN_00bc24c0(float t);                                // 0x00bc24c0
};
struct cSPUIEventLog {
    void RemoveEvent(u32 id, u32 b);                            // 0x00dd6d10
};
struct cSPCreatureBase_s00d4_bc60 {              // sub-object embedded at creature+8
    u8   Play(u32 a, u32 b);                                    // 0x00bc96a0
    void PlayWith(u32 a, u32 b, float c, void* d);              // 0x00bc97f0
    void ClearAll(u32 a, u32 b);                                // 0x00bc98f0
};
struct cCreatureCore {                // a creature / noun
    void* mpBehaviorsB4C;             // +0xb4c
    u8    FUN_00c0b770();                                       // 0x00c0b770
    void* FUN_00c04590();                                       // 0x00c04590
};
struct cNearNoun {
    void* GetPosition(float a, float b);                        // 0x00c6acc0
};
struct cNounContainer {
    void FUN_00aca360(void* o);                                 // 0x00aca360
    void FUN_00acc700(void* o);                                 // 0x00acc700
};
struct StrategyCtx { void* mObject; u32 mField04; u32 mField08; u32 mPad0c; u32 mPad10; u32 mPad14; };
// ---- items of slice s00d4bc60 end

// ---- items of slice s00d4d5c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00f47380(void* p);                                   // 0xf47380 operator_delete_array
extern "C" void* __cdecl FUN_00921580(void* node);                                // 0x921580 eastl::RBTreeIncrement
extern "C" void  __cdecl FUN_009216a0(void* node, void* hint, void* anchor, int side); // 0x9216a0 eastl::RBTreeInsert
extern "C" void  __cdecl FUN_0093a780(void* istream, void* out, int count, int flags);        // 0x93a780 EA::IO::ReadInt32
extern "C" void* __cdecl FUN_00a35070(void* dst, void* end, void* src);           // 0xa35070 vector erase shift
extern "C" void* __cdecl FUN_0067de30();                                          // 0x67de30 SP::PropertyManager
extern "C" void* __cdecl FUN_00b5b800();                                          // 0xb5b800 SP::GetCurrentGameMode
extern "C" void* __cdecl FUN_00920090();                                          // 0x920090 property-event factory owner
extern "C" void* __cdecl FUN_00b3d300();                                          // 0xb3d300 SP::NounManager
extern char gVtbl_cSPDramaManager0[];  // 0x0147b5ec
extern char gVtbl_cSPDramaManager8[];  // 0x0147b5c8
extern char gVtbl_ContentValidationSummarizer0[]; // 0x013ec458
extern char gVtbl_ContentValidationSummarizer8[]; // 0x013eb938
extern char RenameAllocator_013ebb38[];// 0x013ebb38 ("...EASTL/allocator.h")
extern char RenameSimulator_013f09b4[];// 0x013f09b4 ("Simulator")
typedef signed int     i32_s00d4_d5c0;
extern "C" void* __cdecl FUN_00f473a0(u32 n, const char* a, int b, int c, const char* d, int e); // 0xf473a0 operator_new
extern "C" bool  __cdecl FUN_0093aa70(void* istream, const void* data, u32 count, int flags); // 0x93aa70 EA::IO::WriteUint32
extern u32  gDramaEventToBitArray[];   // 0x0147aef4 (indexed by drama-event type)
extern u32  gspDramaManagerInstance;   // 0x0169e43c
extern u8   gDefaultVariant_015d1164[];// 0x015d1164 default property variant
typedef void* (__thiscall *StreamGetFn)(void* self);
typedef bool  (__thiscall *StreamTickFn)(void* self);
typedef bool  (__thiscall *StreamGetDataFn)(void* self, u32 hash, void** out, int flags);
FORCEINLINE void** Vtbl(void* obj) { return *(void***)obj; }
FORCEINLINE void* StreamReader(void* stream) {
    return ((StreamGetFn)Vtbl(stream)[0x20 / 4])(stream);
}
FORCEINLINE void* StreamIStream(void* reader) {
    return ((StreamGetFn)Vtbl(reader)[0x18 / 4])(reader);
}
FORCEINLINE bool StreamTick(void* stream) {
    return ((StreamTickFn)Vtbl(stream)[0x1c / 4])(stream);
}
FORCEINLINE bool StreamGetData(void* stream, u32 hash, void** out, int flags) {
    return ((StreamGetDataFn)Vtbl(stream)[0x28 / 4])(stream, hash, out, flags);
}
struct OReader;
struct OStream {
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
virtual void _v6();
virtual void _v7();
    virtual OReader* v8();                 // vtbl[0x20] -> reader
};
struct OReader {
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
    virtual void* v6();                    // vtbl[0x18] -> istream
};
struct RBNode_s00d4_d5c0 {
    RBNode_s00d4_d5c0* mpNodeLeft;    // +0x00
    RBNode_s00d4_d5c0* mpNodeRight;   // +0x04
    RBNode_s00d4_d5c0* mpNodeParent;  // +0x08
    u32     mColor;        // +0x0c
    u32     mKey;          // +0x10
    void*   mValue;        // +0x14
};
struct RBTree_s00d4_d5c0 {
    u32     m_gap0;        // +0x00
    RBNode_s00d4_d5c0  mAnchor;       // +0x04
    u32     mCount;        // +0x18 (overlays mAnchor.mValue)

    void  equalRange_00d4b450(RBNode_s00d4_d5c0** out, u32* key);             // 0x00d4b450
    void  insertUnique_00d4b4f0(RBNode_s00d4_d5c0** out, RBNode_s00d4_d5c0* hint, void* value, int isInsert); // 0x00d4b4f0
    void  destroyNodes_00d0c930(RBNode_s00d4_d5c0* root);                     // 0x00d0c930
};
typedef void (__thiscall *RefFn)(void* self);
typedef void (__thiscall *SetFn)(void* self, int v);
struct AutoRefObj {
    virtual void _ref_add();      // +0x00
    virtual void _ref_release();  // +0x04
};
struct GameDataObj {              // game-data entry object (predicate at +0x2c)
    virtual void _g0();
    virtual void _g1();
virtual void _g2();
virtual void _g3();
virtual void _g4();
virtual void _g5();
virtual void _g6();
virtual void _g7();
virtual void _g8();
virtual void _g9();
virtual void _g10();
    virtual bool _gpred();        // +0x2c
};
FORCEINLINE void RefAddRef(void* obj) {
    ((AutoRefObj*)obj)->_ref_add();
}
FORCEINLINE void RefRelease(void* obj) {
    ((AutoRefObj*)obj)->_ref_release();
}
struct RefPair { u32 key; void* obj; };   // 8-byte element of the game-data vector
struct RefVec {
    u8* mBegin;            // +0x00
    u8* mEnd;              // +0x04
    u8* mCap;              // +0x08
    void eraseIF_00530c80(u8* first, u8* last);       // 0x530c80 (pair<int,float> erase)
    void eraseGD_00621f50(u8* first, u8* last);       // 0x621f50 (pair<u32,AutoRef> erase)
    void* insertAt_00d4cda0(void* pos, const void* value); // 0x00d4cda0
    void* insert_00d4d9b0(RefPair* pos, const RefPair* value); // 0x00d4d9b0
};
struct cDramaEventInstanceData_s00d4_d5c0 {
    void** m_vtbl;             // +0x00
    u32    m_pad04[2];         // +0x04
    u8     mbActive;           // +0x0c
    u8     m_pad0d[3];         // +0x0d
    u32    mEventMask;         // +0x10
    u32    mType;              // +0x14
    u32    m_pad18[7];         // +0x18
    u32    mPropListKey[3];    // +0x34 (EA::ResourceMan::Key)
    void*  mpPropList;         // +0x40
    RefVec mData;              // +0x44
    u32    m_pad50[3];         // +0x50
    RefVec mGameDataMap;       // +0x5c

    bool Write(void* stream);                 // 0x00d4db50
    bool WriteData(void* stream);             // 0x00d4da10
    void ClearData();                         // 0x00d4dae0
};
struct cNightPredatorEvent_s00d4_d5c0   { bool Write(void* stream); };  // 0x00d4dbe0
struct cUFOAbductionEvent    { bool Write(void* stream); };  // 0x00d4dc70
struct cBabyGameEvent        { bool Write(void* stream); };  // 0x00d4dd00
struct cRainStormEvent_s00d4_d5c0       { bool Write(void* stream); };  // 0x00d4dd90
struct cSeaMonsterEvent_s00d4_d5c0      { bool Write(void* stream); };  // 0x00d4de20
struct cTribeFoodRaidEvent   { bool Write(void* stream); };  // 0x00d4deb0
struct cMeteorStrikeEvent    { bool Write(void* stream); };  // 0x00d4df40
struct cVarListSerializer {
    u8 m_data[0xa14];
    void ctor_00692f90(void* obj, const char* name, u32 sig);  // 0x692f90
    bool serialize_00692900(void* stream);                     // 0x692900
};
struct cGonzagoTimer {
    u8 m_data[0x20];
    void dtor_00b638b0();     // 0xb638b0
};
struct cGameNounManager {
    void removeNoun_00b225d0(void* noun);   // 0xb225d0
};
struct cSPDramaManager_s00d4_d5c0 {
    void** m_vtbl;                // +0x00
    u8     m_pad04[0x0c];         // +0x04
    bool   mbShouldHaveStalker;   // +0x10
    void*  mpBabyTeacher;         // +0x14 (AutoRefCount)
    cGonzagoTimer mGameTimer;     // +0x18
    void*  mpMate;                // +0x38 (AutoRefCount)
    float  mCheckForMateTimer;    // +0x3c
    u32    mCurrentMateCallIndex; // +0x40
    i32_s00d4_d5c0    mNestUpgradeLevel;     // +0x44
    float  mNestItemProgress;     // +0x48
    void*  mpStalkerNPC;          // +0x4c (AutoRefCount)
    RBTree_s00d4_d5c0 mDramaEvents;          // +0x50
    u32    mActiveDramaEventMask; // +0x6c

    void ConsumeDramaEvents(u32 eventType);    // 0x00d4d5c0
    void ConsumeAllDramaEvents();              // 0x00d4d6c0
    void TriggerDramaEvent(u32 eventType, u32 unused); // 0x00d4d790
    void TriggerEvent(cDramaEventInstanceData_s00d4_d5c0* ev, int flags); // 0x00d4d530
    ~cSPDramaManager_s00d4_d5c0();                        // 0x00d4dfd0 (destructor body)
    void Init();                               // 0x00d4e070
    void Shutdown();                           // 0x00d4e350
};
typedef u8*  (__thiscall *VariantGetFn)(void* self, u32 hash);                    // vtbl[0x28]
typedef void* (__thiscall *MakeEventFn)(void* self, const char* name, u32 sig, u32 a, u32 b); // vtbl[0x20]
typedef void  (__thiscall *PropQueryFn)(void* propMgr, u32 sig, RefVec* out);          // vtbl[0x48]
typedef bool  (__thiscall *PropFindFn)(void* propMgr, void* element, u32 sig, void** out); // vtbl[0x2c]
// ---- items of slice s00d4d5c0 end

// ---- items of slice s00d4e4a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
class cDramaRefObj {
public:
    virtual void AddRef();                               // +0x00
    virtual void Release();                              // +0x04
};
}
namespace SP {
class cDramaSlotHolder {
public:
    cDramaRefObj** FUN_00d4eb30(cDramaRefObj*** ppOutSlot); // 0x00d4eb30
    void           FUN_00d4e8e0(cDramaRefObj*** ppOutSlot); // 0x00d4e8e0
};
}
namespace SP {
class cDramaEventHandle {
public:
    void Assign(cDramaRefObj** ppOut, cDramaRefObj* p);

    uint8_t           pad000[0x5c];                      // +0x000 .. +0x05b
    cDramaSlotHolder  mSlotHolder;                       // +0x05c
};
}
namespace SP {
class cMeteorStrikeEvent_s00d4_e4a0 {
public:
    void Clear();  // 0x00d4e950 (SP::cMeteorStrikeEvent::Clear)
};
}
namespace SP {
class cTribeFoodRaidEvent_s00d4_e4a0 {
public:
    void TriggerEvent();  // 0x00d4ee20 (SP::cTribeFoodRaidEvent::TriggerEvent)
    void ShouldActivate();  // 0x00d4f0a0 (SP::cTribeFoodRaidEvent::ShouldActivate)
    void TickInactiveEvent();  // 0x00d4f260 (SP::cTribeFoodRaidEvent::TickInactiveEvent)
};
}
// ---- items of slice s00d4e4a0 end

// ---- items of slice s00d50380 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kEps;        // 0x013ec4b8 (1.0e-8)
extern const float kTiny;       // 0x0147af24 (1.5258789e-05 = 2^-16)
extern const float kSeventy;    // 0x01443c8c (70.0f)
extern const float kTen;        // 0x01473c70 (10.0f)
extern const float kF_13ebc4c;  // 0x013ebc4c (default spawn-distance scalar)
extern const float kF_15d9c6c;  // 0x015d9c6c (default property scalar)
extern const float kF_14853bc;  // 0x014853bc (stimulus radius)
extern "C" void* __cdecl GetSystemAT();                 // 0x00a206f0
extern "C" void* __cdecl SP_App();                      // 0x0067dd10
extern "C" void* __cdecl SP_PlanetModel(void* a, void* b, ...);   // 0x00b3d350
extern "C" void* __cdecl FUN_00d539d0();                // 0x00d539d0  cPosseSimulator::Instance
extern "C" void* __cdecl FUN_00401010();                // 0x00401010
extern "C" void* __cdecl FUN_01021260(void** p);        // 0x01021260
extern "C" void  __cdecl FUN_00acd2d0(void* o);         // 0x00acd2d0
extern "C" void  __cdecl FUN_00d4e8e0(void* p);         // 0x00d4e8e0
extern "C" void  __cdecl FUN_00b7f190(void* self, void* a, void* b);  // 0x00b7f190
extern "C" void  __cdecl FUN_00b81780(void* self, void* a, void* b, float c, float d); // 0x00b81780
extern "C" void  __cdecl FUN_00d54330(void* self, void* o);         // 0x00d54330
extern "C" bool  __cdecl FUN_00d9a360(void* out12, float* dir);     // 0x00d9a360
extern "C" void* __cdecl FUN_00a0a360(void*** vecBegin, void** end, void** valuePtr);  // 0x00a0a360
extern "C" void  FUN_00d502f0(void* self);                                  // 0x00d502f0
struct cSPVector2_s00d5_0380 { float x, y; };      // SP::cSPVector2 (struct, 8 bytes)
struct Vector3    { float x, y, z; };
struct VecMapU32_s00d5_0380 {
    u32* mpBegin;   // +0x00
    u32* mpEnd;     // +0x04
    u32* mpCap;     // +0x08
    u32* Index(const u32& key);          // 0x00564a10
};
struct Property_s00d5_0380 {
    float* mpData;      // +0x00   the typed value
    u8     m_pad04[0xc];
    u8     m_flags10;   // +0x10
    u8     m_pad11;
    u16    m_type12;    // +0x12   EA property type tag
    float* GetFloat();  // 0x0041ea70
};
class cPropertyList_s00d5_0380 {
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
    virtual bool FindProperty(u32 id, Property_s00d5_0380** ppOut);      // +0x24
};
struct AudioSystem {
virtual void a00();
virtual void a04();
virtual void a08();
virtual void a0c();
virtual void a10();
virtual void a14();
virtual void a18();
virtual void a1c();
virtual void a20();
virtual void a24();
virtual void a28();
virtual void a2c();
virtual void a30();
virtual void a34();
    virtual void v38(u32 id);                    // +0x38
    virtual void v3c(u32 id, float value);       // +0x3c
    virtual void v40(u32 id, u32 flags);         // +0x40
virtual void a44();
virtual void a48();
virtual void a4c();
virtual void a50();
    virtual void a54();
    virtual void v58();                          // +0x58
};
struct GDEntry { u32 mKey; void* mValue; };
struct AnchorIface {
virtual void a00();
virtual void a04();
virtual void a08();
virtual void a0c();
virtual void a10();
virtual void a14();
virtual void a18();
virtual void a1c();
virtual void a20();
virtual void a24();
virtual void a28();
    virtual float* GetPos();                     // +0x2c
};
struct SpawnedObj {
    u8     m_pad00[0x98];
    u8     m_v98[0xc];        // +0x98  (12-byte sub-object passed to FUN_01021260)
    u8     m_padA4[4];        // +0xa4
    void*  m_CreatureA4;      // +0xa4  (owner, ecx.add 0x504)
    u8     m_padA8[0x7c];     // +0xa8 .. +0x124
    i32    m_i124;            // +0x124
    u8     m_b128;            // +0x128
    u8     m_pad129[0x69];    // +0x129 .. +0x192
    u8     m_b192;            // +0x192
    u8     m_pad193[0x1c];    // +0x193 .. +0x1af
    u32    m_dword1af_pad;    // padding to make m_nFields reach +0xf4 range below
};
struct RandomLCG_s00d5_0380 {
    u32    RandomUint32Uniform(u32 range);   // 0x00a68fb0
    double RandomDoubleUniform();            // 0x009360d0
};
extern RandomLCG_s00d5_0380 gRand_s00d5_0380;         // 0x01601760
struct cGameNounManager_s00d5_0380 {
    void* GetAvatar();          // 0x00b1fdb0
    void  RemoveNoun(void* n);  // 0x00b225d0
};
struct cViewer_s00d5_0380 {
    void GetCameraLocationInfo(Vector3* a, Vector3* b, int c, int d);  // 0x007c3d30
};
struct MegaManager {              // result of FUN_00b3d480()
    void Method_aca360(void* o);  // 0x00aca360
};
extern "C" bool GetPropertyAsFloatArray(cPropertyList_s00d5_0380* list, u32 id, int* pCount, float** ppOut);   // 0x006a08b0
extern "C" bool GetPropertyAsIntArray  (cPropertyList_s00d5_0380* list, u32 id, int* pCount, int**   ppOut);   // 0x006a07d0
extern "C" bool GetPropertyAsVector2Array(cPropertyList_s00d5_0380* list, u32 id, int* pCount, void** ppOut);  // 0x006a0920
extern "C" bool GetPropertyAsUint32Array (cPropertyList_s00d5_0380* list, u32 id, int* pCount, u32**  ppOut);   // 0x006a0840
extern "C" void* GetPropertyAsKeyInstance(cPropertyList_s00d5_0380* list, u32 id, void* pOut);                 // 0x006a12a0
extern "C" void* __cdecl FUN_00b23650(u32 a, float b, u32 c, void* d, void* e);   // 0x00b23650
extern "C" void* __cdecl FUN_00c099e0(float* pos, float a, u32 b, void* c, u32 d, u32 e); // 0x00c099e0
extern "C" void  __cdecl FUN_00d4edd0(u32 a, void* b);  // 0x00d4edd0
extern "C" void* __cdecl FUN_00d4cf10(u32 a, u32 b);    // 0x00d4cf10
extern "C" void* __cdecl FUN_00d998d0(void* a, u32 b);  // 0x00d998d0
extern "C" void* __cdecl FUN_00c74690(void** a, u32 b, u32 c);  // 0x00c74690
extern "C" void* __cdecl FUN_00b82970(void* a, void* b, u32 c);  // 0x00b82970
extern "C" void  __cdecl FUN_00c13a30(void* self, u32 a);           // 0x00c13a30
extern "C" void  __cdecl FUN_00bc98f0(void* self, u32 a, u32 b);    // 0x00bc98f0
extern "C" void* __cdecl FUN_00bc97f0(u32 a, u32 b, float c, u32 d); // 0x00bc97f0
extern "C" void* __cdecl FUN_00bc96a0(void* self, u32 a, u32 b);    // 0x00bc96a0
extern "C" int   __cdecl GetTutorialToolPrice(void* plist, u32 id, int nDefault);  // 0x004e1c30
extern "C" void* __cdecl MapLowerBound(void* first, void* last, const u32* key, u32 flag); // 0x00d01260
extern "C" void* FUN_00d50040(u32 effectKey, float* pos, float a, float b); // 0x00d50040
typedef void (__thiscall *VoidThunk)(void*);
static inline void AddRefObj(void* o) { ((VoidThunk)(*(void***)o)[0])(o); }
static inline void ReleaseObj(void* o) { ((VoidThunk)(*(void***)o)[1])(o); }
typedef void* (__thiscall *PtrThunk1)(void*);
typedef void* (__thiscall *PtrThunk2)(void*, u32);
static inline void* CallV0c(void* o, u32 a)
{
    return ((PtrThunk2)(*(void***)o)[0x0c / 4])(o, a);
}
static inline u32 CallV4c(void* o)
{
    return ((u32(__thiscall*)(void*))(*(void***)o)[0x4c / 4])(o);
}
namespace SP {
struct Meteors {                        // sp_fixed_vector<AutoRefCount<cIVisualEffect>,128>
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCap;                       // +0x08
    u8     m_pad0c[0x20c];              // +0x0c .. +0x218
};
}
namespace SP {
union F2U { float f[2]; u32 u[2]; };
}
namespace SP {
union R2U { cSPVector2_s00d5_0380 v[2]; u32 u[4]; };
}
namespace SP {
struct cMeteorStrikeEvent_s00d5_0380 {
    // ---- base cDramaEventInstanceData (retail offsets observed here) ----
    u8             m_pad00[0x20];
    cSPVector2_s00d5_0380     m_thresh20;          // +0x20
    float          m_f28;               // +0x28
    float          m_f2c;               // +0x2c
    u8             m_pad30[0x10];       // +0x30 .. +0x40
    cPropertyList_s00d5_0380* m_pPropList40;       // +0x40
    VecMapU32_s00d5_0380      m_data44;            // +0x44
    u8             m_pad50[0xc];        // +0x50 .. +0x5c
    u8*            m_gdBegin5c;         // +0x5c  mGameDataMap begin
    u8*            m_gdEnd60;           // +0x60  mGameDataMap end
    u8             m_pad64[0xc];        // +0x64 .. +0x70
    u8             m_gdSorted70;        // +0x70
    u8             m_pad71[3];          // +0x71 .. +0x74
    // ---- meteor fields ----
    u8             m_b74;               // +0x74
    u8             m_pad75[3];
    i32            m_meteorCount[2][2]; // +0x78  {current,target} per stream
    F2U            m_f88;               // +0x88  strike centre from avatar
    F2U            m_f90;               // +0x90  strike range
    u32            m_u98[2];            // +0x98  effect key
    R2U            m_rangeA0;           // +0xa0  spawn-delay range
    F2U            m_timerB0;           // +0xb0  current spawn delay
    float          m_fB8;               // +0xb8
    float          m_fBC;               // +0xbc
    float          m_fC0;               // +0xc0
    float          m_fC4;               // +0xc4
    Meteors        m_meteors[2];        // +0xc8, +0x2e0

    void Clear();                                                // 0x00d4e950
    void InitFromTuning(int flag);                               // 0x00d4af80
    void LoadAndInitMeteorStrikeData(cPropertyList_s00d5_0380* pList);      // 0x00d50380
    u8   FUN_00d505a0(void* pAvatar, float dt);                  // 0x00d505a0
    void ShutdownEvent();                                        // 0x00d50960
    void TickEvent(float dt);                                    // 0x00d509c0
    void FUN_00d509f0(int flag);                                 // 0x00d509f0
    void FUN_00d50a40();                                         // 0x00d50a40
    u8   FUN_00d50b80();                                         // 0x00d50b80
    u8   FUN_00d50c30();                                         // 0x00d50c30
    void FUN_00d50e40(float dt);                                 // 0x00d50e40
    void FUN_00d50ef0();                                         // 0x00d50ef0
};
}
// ---- items of slice s00d50380 end

// ---- items of slice s00f21850 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct DramaEventMultiMap
{
    void equal_range(void** out, const unsigned int* key);
};
}
// ---- items of slice s00f21850 end

// ---- items of slice s01364b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00572810();
extern "C" void FUN_00572840();
extern "C" void FUN_0057cde0();
extern "C" void FUN_0057ce00();
extern "C" void FUN_00675ca0();
extern "C" void FUN_00692ca0();
extern "C" void FUN_00692fb0();
extern "C" void FUN_00692ff0();
extern "C" void FUN_00693090();
extern "C" void FUN_006930b0();
extern "C" void FUN_00693150();
extern "C" void FUN_00694ee0();
extern "C" void FUN_00694f00();
extern "C" void FUN_00694fa0();
extern "C" void FUN_00694fc0();
extern "C" void FUN_00695080();
extern "C" void FUN_00ac8050();
extern "C" void FUN_00ac8750();
extern "C" void FUN_00ac8780();
extern "C" void FUN_00ac88f0();
extern "C" void FUN_00acbb80();
extern "C" void FUN_00ae3310();
extern "C" void FUN_00ae3430();
extern "C" void FUN_00ae3450();
extern "C" void FUN_00ae3470();
extern "C" void FUN_00ae3490();
extern "C" void FUN_00ae5720();
extern "C" void FUN_00b1fbf0();
extern "C" void FUN_00b20510();
extern "C" void FUN_00b6f550();
extern "C" void FUN_00ba7450();
extern "C" void FUN_00ba94e0();
extern "C" void FUN_00baa2b0();
extern "C" void FUN_00bca960();
extern "C" void FUN_00c2e4e0();
extern "C" void FUN_00c78ff0();
extern "C" void FUN_00cd5980();
extern "C" void FUN_00cd92f0();
extern "C" void FUN_00cdb4c0();
extern "C" void FUN_00d4b390();
extern "C" void FUN_00d4cce0();
extern "C" void FUN_00d4d7f0();
extern "C" void FUN_00d4ebe0();
#pragma warning(disable: 4100)
namespace Simulator {
struct Attribute {
    const char* mpName;                                    // +0x00  attribute name
    uint32_t    mHash;                                     // +0x04  FNV hash of the name
    uint32_t    mLocation;                                 // +0x08  member offset, or a static address
    uint32_t    mUnused0c;                                 // +0x0c  never written
    uint32_t    mUnused10;                                 // +0x10  never written
    uint32_t    mUnused14;                                 // +0x14  never written
    uint32_t    mZero18;                                   // +0x18
    uint32_t    mZero1c;                                   // +0x1c
    void*       mpFn20;                                    // +0x20
    void*       mpFn24;                                    // +0x24
    void*       mpFn28;                                    // +0x28
    void*       mpFn2c;                                    // +0x2c
    void*       mpFn30;                                    // +0x30
    void*       mpFn34;                                    // +0x34
    void*       mpFn38;                                    // +0x38
};  // namespace Simulator
}
using Simulator::Attribute;
extern Attribute g_commandUIAttributes[8];                 // 0x015836c8
extern Attribute g_mateBehaviourAttributes[8];             // 0x01583b00
// ---- items of slice s01364b20 end

// @ 0x00d4af70
void ModeSetter::SetValue(u32 v)
{
    if (v <= 3) {
        m_value44 = v;
    }
}

// @ 0x00d4af80
void cDramaEventInstanceData::InitFromTuning(int unused)
{
    typedef bool (__thiscall *FindFn)(void *self, u32 hash, void **ppOut);
    void *found;
    u32 bits;

    if (m_propList40 != 0) {
        found = 0;
        if (((FindFn)(*(void ***)m_propList40)[0x24 / 4])(m_propList40, 0xc55c98bb, &found)
            && *(u16 *)((u8 *)found + 0x12) == 10) {
            u32 *p = ((GetUIntP)(*(void ***)found)[0])(found);
            bits = (*p != 0) ? (1u << *p) : 0u;
        } else {
            bits = 0;
        }
        m_bits10 = bits;

        if (m_propList40 != 0) {
            found = 0;
            if (((FindFn)(*(void ***)m_propList40)[0x24 / 4])(m_propList40, 0x06bfe2ed, &found)
                && *(u16 *)((u8 *)found + 0x12) == 10) {
                u32 *p = ((GetUIntP)(*(void ***)found)[0])(found);
                *(u32 *)((u8 *)this + 0x1c) = *p;
            }
        }
    }

    FUN_006a10c0(m_propList40, 0xd2e804ee, (u8 *)this + 0x20);

    if (m_propList40 != 0) {
        found = 0;
        if (((FindFn)(*(void ***)m_propList40)[0x24 / 4])(m_propList40, 0x346dbe16, &found)
            && *(u16 *)((u8 *)found + 0x12) == 1) {
            u8 *p = ((GetBoolP)(*(void ***)found)[0])(found);
            *(u8 *)((u8 *)this + 0x30) = *p;
        }
    }

    if (unused != 0) return;

    if (m_propList40 != 0) {
        found = 0;
        if (((FindFn)(*(void ***)m_propList40)[0x24 / 4])(m_propList40, 0x332c289d, &found)
            && *(u16 *)((u8 *)found + 0x12) == 10) {
            u32 *p = ((GetUIntP)(*(void ***)found)[0])(found);
            *(u32 *)((u8 *)this + 0x18) = *p;
        }
    }

    if (m_propList40 != 0) {
        found = 0;
        if (((FindFn)(*(void ***)m_propList40)[0x24 / 4])(m_propList40, 0x920a2318, &found)
            && *(u16 *)((u8 *)found + 0x12) == 13) {
            float *p = ((GetFloatP)(*(void ***)found)[0])(found);
            *(float *)((u8 *)this + 0x28) = *p;
        }
    }

    if (m_propList40 != 0) {
        found = 0;
        if (((FindFn)(*(void ***)m_propList40)[0x24 / 4])(m_propList40, 0xb1f42539, &found)
            && *(u16 *)((u8 *)found + 0x12) == 13) {
            float *p = ((GetFloatP)(*(void ***)found)[0])(found);
            *(float *)((u8 *)this + 0x2c) = *p;
        }
    }
}

// @ 0x00d4b180
void cSPDramaManager::MatedWith(cSPCreatureAnimal *mate)
{
    if (m_mate38 != 0) {
        ((cSPCreatureAnimal *)m_mate38)->m_flagsB58 &= ~0x10u;
        ((cSPSubObject *)((cSPCreatureAnimal *)m_mate38)->m_pB4C)->m_flags5fc &= ~0x4000u;
        AutoRefRelease(&m_mate38);
        m_checkMate3c = kCheckForMate;
    }
}

// @ 0x00d4b1d0
void cSPDramaManager::ClearMate(cSPCreatureAnimal *mate)
{
    mate->m_flagsB58 &= ~0x10u;
    ((cSPSubObject *)mate->m_pB4C)->m_flags5fc &= ~0x4000u;
    if (mate == (cSPCreatureAnimal *)m_mate38) {
        AutoRefRelease(&m_mate38);
        m_checkMate3c = kCheckForMate;
    }
}

// @ 0x00d4b2f0
int cSPDramaManager::IsValidBabyTeacher(cSPCreatureAnimal *c)
{
    if (c != 0
        && !((u8 (__thiscall *)(void *))(*(void ***)c)[0x2c / 4])(c)
        && c->m_b135 != 0
        && c->m_b5e == 0
        && ((u8 (__thiscall *)(void *))FUN_00c0b770)(c)
        && ((void *(__thiscall *)(void *))FUN_00c0bbd0)(c) == ((void *(__thiscall *)(void *))FUN_00c0bbd0)(((void *(__thiscall *)(void *))FUN_00b1fdb0)(SP_NounManager()))
        && !((u8 (__thiscall *)(void *))(*(void ***)((u8 *)c + 0xc0))[0x58 / 4])((u8 *)c + 0xc0)
        && c != (cSPCreatureAnimal *)m_mateTeacher14
        && ((int (__thiscall *)(void *, int, int, int, int))FUN_00bca0c0)((void *)c->m_idB48, 3, 1, 0, 0) == -1)
    {
        return 1;
    }
    return 0;
}

// @ 0x00d4b390
u8 FUN_00d4b390(void *param, RefRange *range)
{
    RefEntry *end = range->m_end;
    for (RefEntry *it = range->m_begin; it != end; it++) {
        void *obj = it->m_obj;
        if (obj != 0) {
            void **vtbl = *(void ***)obj;
            ((NotifyFnP)vtbl[0x1c / 4])(obj, param);
        }
    }
    return 1;
}

// @ 0x00d4b3c0
void TuningOwner::ReloadTuning(int unused)
{
    void *pm = PropertyManager();
    if (m_tuning40 != 0) {
        void *old = m_tuning40;
        m_tuning40 = 0;
        void **vtbl = *(void ***)old;
        ((void (__thiscall *)(void *))vtbl[4 / 4])(old);
    }
    void **pvtbl = *(void ***)pm;
    ((void (__thiscall *)(void *, void *, void *, void **))pvtbl[0x2c / 4])(pm, m_tuning34, m_tuning3c, &m_tuning40);
    void **vtbl = *(void ***)this;
    ((void (__thiscall *)(void *, int))vtbl[0x28 / 4])(this, 1);
}

// @ 0x00d4b410
void cSPDramaManager::PostLoad(void *p)
{
    RBTreeHead *tree = (RBTreeHead *)((u8 *)this + 0x54);
    RBNode *end = &tree->mAnchor;
    for (RBNode *n = tree->mAnchor.mpNodeRight; n != end; n = (RBNode *)RBTreeIncrement(n)) {
        TreeValue *v = (TreeValue *)n->mValue;
        ((VisitFn)v->m_vtbl[0x24 / 4])(v, p);
    }
}

// @ 0x00d4b450
void RBTree::equal_range(RBNode **out, u32 *key)
{
    RBNode *const root = mAnchor.mpNodeParent;
    RBNode *lo = &mAnchor;
    for (RBNode *n = root; n != 0; ) {
        if (*key < n->mKey) {
            lo = n;
            n = n->mpNodeRight;
        } else {
            n = n->mpNodeLeft;
        }
    }
    RBNode *hi = &mAnchor;
    for (RBNode *n = root; n != 0; ) {
        if (*key > n->mKey) {
            n = n->mpNodeRight;
        } else {
            hi = n;
            n = n->mpNodeLeft;
        }
    }
    out[0] = lo;
    out[1] = hi;
}

// @ 0x00d4b4b0
void cDramaEventInstanceData::DestroyMembers()
{
    RefEntry *end = m_pEnd;
    for (RefEntry *it = m_pBegin; it < end; it++) {
        void *obj = it->m_obj;
        if (obj != 0) {
            void **vtbl = *(void ***)obj;
            ((NotifyFn)vtbl[4 / 4])(obj);
        }
    }
    if (m_pBegin != 0) {
        operator_delete_array(m_pBegin);
    }
}

// @ 0x00d4ba40
void cDramaEventInstanceData::Construct()
{
    cDramaEventInstanceData *p = this;
    *(void **)((u8 *)p + 0x04) = (void *)&kVtblB;
    *(u32 *)((u8 *)p + 0x08) = 0;
    *(u8  *)((u8 *)p + 0x0c) = 0;
    *(u32 *)((u8 *)p + 0x14) = 0;
    *(u32 *)((u8 *)p + 0x18) = 0;
    *(u32 *)((u8 *)p + 0x1c) = 0;
    *(float *)((u8 *)p + 0x28) = 0.0f;
    *(float *)((u8 *)p + 0x2c) = 0.0f;
    *(u8  *)((u8 *)p + 0x30) = 1;
    *(u32 *)((u8 *)p + 0x34) = 0;
    *(u32 *)((u8 *)p + 0x38) = 0;
    *(u32 *)((u8 *)p + 0x3c) = 0;
    *(u32 *)((u8 *)p + 0x40) = 0;
    *(u32 *)((u8 *)p + 0x44) = 0;
    *(u32 *)((u8 *)p + 0x48) = 0;
    *(u32 *)((u8 *)p + 0x4c) = 0;
    *(u32 *)((u8 *)p + 0x5c) = 0;
    *(u32 *)((u8 *)p + 0x60) = 0;
    *(u32 *)((u8 *)p + 0x64) = 0;
    *(void **)((u8 *)p + 0x00) = (void *)&kVtblA;
    *(void **)((u8 *)p + 0x04) = (void *)&kVtblC;
    *(float *)((u8 *)p + 0x74) = gVec0169e440[0];
    *(float *)((u8 *)p + 0x78) = gVec0169e440[1];
    *(float *)((u8 *)p + 0x7c) = gVec0169e440[2];
}

// @ 0x00d4bbb0
bool Thresholded::IsBelowZero()
{
    return 0.0f > m_value2c;
}

// @ 0x00d4bbd0
void *FUN_00d4bbd0(Vec3 *out)
{
    u8 *mode = (u8 *)SP_GetCurrentGameMode();
    if (mode == &gModeA || mode == &gModeB) {
        void *src = (mode == &gModeA)
            ? (u8 *)FUN_00b1fdb0(SP_NounManager()) + 0xc0
            : (u8 *)FUN_00bfc5f0(SP_NounManager()) + 0x120;
        void **vtbl = *(void ***)src;
        Vec3 *v = (Vec3 *)((void *(__thiscall *)(void *))vtbl[0x2c / 4])(src);
        out->x = v->x;
        out->y = v->y;
        out->z = v->z;
        return out;
    }
    out->x = gVec0169e440[0];
    out->y = gVec0169e440[1];
    out->z = gVec0169e440[2];
    return out;
}

// @ 0x00d4bc60
void SP::cRainStormEvent::TriggerEvent()
{
    cPlanetModel_s00d4_bc60* pm = (cPlanetModel_s00d4_bc60*)SP_PlanetModel();
    void* target = pm->mpAnchor24->GetStormTarget();
    if (mpPropList40 != 0) {
        Property* p = 0;
        mpPropList40->FindProperty(0x8de8a7c2, &p);
    }
    Vec3 nest;
    mPos74 = *FUN_00d4bbd0(&nest);
    if (mPos74.x != gVec0169e440_s00d4_bc60[0] || mPos74.y != gVec0169e440_s00d4_bc60[1]
        || mPos74.z != gVec0169e440_s00d4_bc60[2]) {
        FUN_00fc6f00(target, mPos74, mActivationType2c);
    }
}

// @ 0x00d4bd10
u8 SP::cDramaEventInstanceData_s00d4_bc60::FUN_00d4bd10()
{
    Vec3 nest;
    FUN_00d4bbd0(&nest);
    if (nest.x != gVec0169e440_s00d4_bc60[0] || nest.y != gVec0169e440_s00d4_bc60[1]
        || nest.z != gVec0169e440_s00d4_bc60[2]) {
        float t = cTimeOfDay::Instance()->FUN_00bc2b30(&nest);
        if (cTimeOfDay::Instance()->FUN_00bc24c0(t) == 2) return 1;
    }
    return 0;
}

// @ 0x00d4c1b0
void* __stdcall FUN_00d4c1b0(Vec3* pos, float scale, char flag)
{
    cUFO* ufo;
    if (flag == 0) {
        Vec3 c; c.x = 0.0f; c.y = 0.0f; c.z = 0.0f;
        ApplyFilterConstraints(&c, 0);
        ufo = (cUFO*)CreateUFO(7, &gVec147aed8, &c);
    } else {
        void* empire = ((cStarManager_s00d4_bc60*)SP_StarManager())->FUN_00ba93b0();
        u32 key = ((cEmpire_s00d4_bc60*)empire)->GetUFOKey();
        float dist = ((cStarManager_s00d4_bc60*)SP_StarManager())->FUN_00885c90();
        ufo = (cUFO*)CreateUFO(7, &dist, (void*)key);
    }

    Vec3 orient;
    cPlanetModel_s00d4_bc60* pm = (cPlanetModel_s00d4_bc60*)SP_PlanetModel();
    pm->BuildSurfaceOrientation(&orient, pos);

    float x = pos->x, y = pos->y, z = pos->z;
    float len = (float)sqrt((double)(x * x + (y * y + z * z)));
    float inv = 1.0f / len;
    len = len + scale;
    x *= inv; y *= inv; z *= inv;
    ufo->FUN_00c3daa0(len);
    x *= len; y *= len; z *= len;
    Vec3 n; n.x = x; n.y = y; n.z = z;
    ufo->FUN_00c3aa40(&n, &orient);

    if (SP_GetCurrentGameMode() == &gGameModeA) {
        *(u32*)((u8*)ufo->mCreature6c8 + 0x5fc) |= 1u;
    }
    return ufo;
}

// @ 0x00d4c470
void FUN_00d4c470()
{
    cGameNounManager_s00d4_bc60* nm = (cGameNounManager_s00d4_bc60*)SP_NounManager();
    cCreatureCore* avatar = (cCreatureCore*)nm->GetAvatar();
    avatar->FUN_00c0b770();
}

// @ 0x00d4c5e0
void FUN_00d4c5e0()
{
    cGameNounManager_s00d4_bc60* nm = (cGameNounManager_s00d4_bc60*)SP_NounManager();
    void* avatar = nm->GetAvatar();
    ((cAvatarAnchor*)((u8*)avatar + 0xc0))->vec();
    StrategyCtx ctx;
    ctx.mObject = avatar;
    ctx.mField04 = 0;
    ctx.mField08 = 9;
    cCreatureModeStrategy::Instance()->FUN_00d39360(0xd3353639, &ctx);
    cCreatureModeStrategy::Instance()->SignalCreatureEvent(0xd3353639);
}

// @ 0x00d4c650
bool SP::cSeaMonsterEvent::ShouldActivate()
{
    cGameNounManager_s00d4_bc60* nm = (cGameNounManager_s00d4_bc60*)SP_NounManager();
    void* avatar = nm->GetAvatar();
    cPlanetModel_s00d4_bc60* pm = (cPlanetModel_s00d4_bc60*)SP_PlanetModel();

    Vec3 avatarPos = *((cAvatarAnchor*)((u8*)avatar + 0xc0))->GetPos();
    void* holder = ((cCreatureCore*)avatar)->FUN_00c04590();
    Vec3* otherPos = (Vec3*)((cNearNoun*)holder)->GetPosition(0.0f, 0.0f);

    i32 contA = pm->GetContinent(&avatarPos);
    i32 contB = pm->GetContinent(otherPos);
    if (contA == contB) return false;

    if (*((u8*)pm->mpVisited64 + contA) != 0) {
        i32 count = pm->FUN_00b7ea00(contA);
        u32 threshold = 100;
        if (mpPropList40 != 0) {
            Property* p = 0;
            if (mpPropList40->FindProperty(0x58d4cf9a, &p) && p->m_type12 == 10)
                threshold = *p->GetUInt();
        }
        return (u32)count > threshold;
    }

    Vec3 dir;
    pm->FUN_00b81630(&dir, &avatarPos);
    float radius = kF_13ec4d0;
    if (mpPropList40 != 0) {
        Property* p = 0;
        if (mpPropList40->FindProperty(0x9388b444, &p) && p->m_type12 == 13)
            radius = *p->GetFloat();
    }
    Vec3 hit;
    return !pm->RayCast(&avatarPos, radius, &hit, 1.0f, 0, 0);
}

// @ 0x00d4ca70
SP::cDramaEventInstanceData_s00d4_bc60* SP::cDramaEventInstanceData_s00d4_bc60::FUN_00d4ca70(u8 flags)
{
    m_vtbl00 = (void**)0x147b090;
    m_vtbl04 = (void**)0x147b278;
    mGameDataMap5c.DestroyMembers();
    if (mData44.mpBegin != 0) operator_delete_array(mData44.mpBegin);
    if (mpPropList40 != 0) {
        void* old = mpPropList40;
        ((IInterface*)old)->v04();
    }
    m_vtbl04 = (void**)0x13ec458;
    m_vtbl00 = (void**)0x13eb938;
    if ((flags & 1) != 0) operator_delete_array(this);
    return this;
}

// @ 0x00d4cad0
SP::cDramaEventInstanceData_s00d4_bc60* SP::cSPDramaManager_s00d4_bc60::GetActiveEvent(u32 type, bool onlyActive)
{
    u32 key = type;
    MMRange out;
    mDramaEvents.equal_range(&out, &key);
    void* it = out.mFirst;
    void* end = out.mSecond;
    while (it != end) {
        void* v = *(void**)((u8*)it + 0x14);
        if (!onlyActive || *(u8*)((u8*)v + 0xc) != 0) return (cDramaEventInstanceData_s00d4_bc60*)v;
        it = RBTreeIncrement(it);
    }
    return 0;
}

// @ 0x00d4cb30
bool SP::cSPDramaManager_s00d4_bc60::IsDramaEventActive(u32 type)
{
    return GetActiveEvent(type, true) != 0;
}

// @ 0x00d4cb50
void* SP::cSPDramaManager_s00d4_bc60::GetActiveEventTuning(u32 type)
{
    cDramaEventInstanceData_s00d4_bc60* e = GetActiveEvent(type, true);
    if (e != 0) return e->mpPropList40;
    return 0;
}

// @ 0x00d4cf10
void* SP::cDramaEventInstanceData_s00d4_bc60::FUN_00d4cf10(u32 a, u32 b)
{
    PairUR* const e = mGameDataMap5c.mpEnd;
    PairUR* it = LowerBound(mGameDataMap5c.mpBegin, e, &a, mGameDataMap5c.mbFlag);
    if (it == e || a < it->mKey) it = e;
    else if (it == it + 1) it = e;
    if (it == e) return 0;
    void* v = it->mValue;
    if (v == 0) return 0;
    return ((IInterface*)v)->AsInterface(b);
}

// @ 0x00d4cf70
void SP::cDramaEventInstanceData_s00d4_bc60::FUN_00d4cf70()
{
    void* gd = GetGameData(0, 0x52aa6117);
    if (gd != 0) {
        cNounContainer* mgr = (cNounContainer*)FUN_00b3d480();
        void** it = *(void***)((u8*)gd + 0x40);
        void** end = *(void***)((u8*)gd + 0x44);
        for (; it != end; ++it) {
            void* creature = *it;
            void* bt = *(void**)((u8*)creature + 0xb4c);
            if (bt != 0) ((cSPCreatureBase_s00d4_bc60*)((u8*)bt + 8))->ClearAll(0, 0x100);
            mgr->FUN_00aca360(creature);
        }
    }
    ((cSPUIEventLog*)SP_EventLog())->RemoveEvent(0xe2def8b4, 1);
}

// @ 0x00d4d030
u8 SP::cDramaEventInstanceData_s00d4_bc60::GetGameDataIsUsable()
{
    void* gd = GetGameData(0, 0x52aa6117);
    if (mActivationType2c < 0.0f) return 1;
    if (gd == 0) return 1;
    if (((cGameDataInfo*)gd)->mpArray40 == ((cGameDataInfo*)gd)->mpArray44) return 1;
    return 0;
}

// @ 0x00d4d0b0
bool SP::cNightPredatorEvent::ShouldActivate()
{
    void* gd = GetGameData(0, 0x52aa6117);
    if (gd != 0 && *((u8*)gd + 0x190) != 0) return false;

    float chance = 0.0f;
    if (mpPropList40 != 0) {
        Property* p = 0;
        if (mpPropList40->FindProperty(0x360b94a0, &p) && p->m_type12 == 13)
            chance = *p->GetFloat();
    }
    if (gRand.RandomDoubleUniform() < chance) return true;
    return false;
}

// @ 0x00d4d180
void SP::cDramaEventInstanceData_s00d4_bc60::PostLoadEvent(void* arg)
{
    void* pm = SP_PropertyManager();
    if (mpPropList40 != 0) {
        void* old = mpPropList40;
        mpPropList40 = 0;
        ((IInterface*)old)->v04();
    }
    ((void (__thiscall*)(void*, void*, void*, cPropertyList_s00d4_bc60**))
        (*(void***)pm)[0x2c / 4])(pm, mStream34, mTuning3c, &mpPropList40);
    ((IEventVtbl*)this)->v28(1);

    if (mFlag0c != 0) {
        void* gd = FUN_00d4cf10(0, 0xb033b403);
        if (gd != 0) {
            if (SP_GetCurrentGameMode() == &gGameModeA) SetGlobalProperty(0xdca3b514, 1.0f);
            void* obj = *(void**)((u8*)gd + 0x6c8);
            ((cSPCreatureBase_s00d4_bc60*)((u8*)obj + 8))->PlayWith(2, 0, mActivationType2c, 0);
        }
    }
    (void)arg;
}

// @ 0x00d4d220
u8 SP::cDramaEventInstanceData_s00d4_bc60::PlayIdleIfFlagged()
{
    void* gd = GetGameData(0, 0xb033b403);
    if (gd != 0 && mActivationType2c >= 0.0f) {
        void* obj = *(void**)((u8*)gd + 0x6c8);
        if ((*(u8*)((u8*)obj + 0x5fc) & 2) == 0) return 0;
        if (((cSPCreatureBase_s00d4_bc60*)((u8*)obj + 8))->Play(2, 0) == 0) return 1;
        return 0;
    }
    return 1;
}

// @ 0x00d4d2b0
void SP::cDramaEventInstanceData_s00d4_bc60::ReleaseGameDataObject(int arg)
{
    void* gd = GetGameData(0x5f115ab, 0x52aa6117);
    if (gd != 0) {
        void* p = ((cNearNoun*)gd)->GetPosition(kF_13ebc5c, kF_147b4bc);
        ((cNounContainer*)FUN_00b3d480())->FUN_00acc700(p);
    }
    (void)arg;
}

// @ 0x00d4d340
u8 SP::cDramaEventInstanceData_s00d4_bc60::AnyGameDataFlagged()
{
    void* gd = GetGameData(0x609f2f8, 0x52aa6117);
    if (gd == 0) return 1;
    void** it = ((cGameDataInfo*)gd)->mpArray40;
    void** end = ((cGameDataInfo*)gd)->mpArray44;
    u8 r = 1;
    while (it != end) {
        if (*(u8*)((u8*)(*it) + 0x135) != 0) { r = 0; break; }
        ++it;
    }
    return r;
}

// @ 0x00d4d530
void SP::cSPDramaManager_s00d4_bc60::TriggerEvent(cDramaEventInstanceData_s00d4_bc60* e, int a2)
{
    e->mFlag0c = 1;
    if (e->mCountdown18 != 0xffffffffu && e->mCountdown18 != 0)
        e->mCountdown18 = e->mCountdown18 - 1;

    if (e->mpPropList40 != 0) {
        Property* p = 0;
        if (e->mpPropList40->FindProperty(0xb1f42539, &p) && p->m_type12 == 13)
            e->mActivationType2c = *p->GetFloat();
    }
    ((IEventVtbl*)e)->v30();

    i32 type = e->mEventType14;
    u32 bit = sDramaEventToBitArray[type];
    if (GetActiveEvent((u32)type, true) != 0)
        mActiveDramaEventMask |= bit;
    else
        mActiveDramaEventMask &= ~bit;
    (void)a2;
}

// @ 0x00d4d5c0
void cSPDramaManager_s00d4_d5c0::ConsumeDramaEvents(u32 eventType)
{
    RBNode_s00d4_d5c0* range[2];
    mDramaEvents.equalRange_00d4b450(range, &eventType);

    RBNode_s00d4_d5c0* n = range[0];
    if (range[0] != range[1]) {
        do {
            cDramaEventInstanceData_s00d4_d5c0* ev = (cDramaEventInstanceData_s00d4_d5c0*)n->mValue;
            if (ev->mbActive) {
                void** vt = (void**)ev->m_vtbl;
                ((RefFn)vt[0x34 / 4])(ev);
                ev->mbActive = 0;

                u32 type = ev->mType;
                RBNode_s00d4_d5c0* lo = &mDramaEvents.mAnchor;
                for (RBNode_s00d4_d5c0* a = mDramaEvents.mAnchor.mpNodeParent; a != 0; ) {
                    if (type < a->mKey) { lo = a; a = a->mpNodeRight; }
                    else a = a->mpNodeLeft;
                }
                RBNode_s00d4_d5c0* hi = &mDramaEvents.mAnchor;
                for (RBNode_s00d4_d5c0* b = mDramaEvents.mAnchor.mpNodeParent; b != 0; ) {
                    if (b->mKey < type) b = b->mpNodeLeft;
                    else { hi = b; b = b->mpNodeRight; }
                }
                cDramaEventInstanceData_s00d4_d5c0* found = 0;
                for (RBNode_s00d4_d5c0* p = hi; p != lo; p = (RBNode_s00d4_d5c0*)FUN_00921580(p)) {
                    cDramaEventInstanceData_s00d4_d5c0* v = (cDramaEventInstanceData_s00d4_d5c0*)p->mValue;
                    if (v->mbActive) { found = v; break; }
                }

                u32 bit = gDramaEventToBitArray[type];
                if (found) mActiveDramaEventMask |= bit;
                else       mActiveDramaEventMask &= ~bit;
            }
            n = (RBNode_s00d4_d5c0*)FUN_00921580(n);
        } while (n != range[1]);
    }
}

// @ 0x00d4d6c0
void cSPDramaManager_s00d4_d5c0::ConsumeAllDramaEvents()
{
    RBNode_s00d4_d5c0* end = &mDramaEvents.mAnchor;
    RBNode_s00d4_d5c0* n = mDramaEvents.mAnchor.mpNodeRight;
    if (n != end) {
        do {
            cDramaEventInstanceData_s00d4_d5c0* ev = (cDramaEventInstanceData_s00d4_d5c0*)n->mValue;
            if (ev->mbActive) {
                void** vt = (void**)ev->m_vtbl;
                ((RefFn)vt[0x34 / 4])(ev);
                ev->mbActive = 0;

                u32 type = ev->mType;
                RBNode_s00d4_d5c0* lo = &mDramaEvents.mAnchor;
                for (RBNode_s00d4_d5c0* a = mDramaEvents.mAnchor.mpNodeParent; a != 0; ) {
                    if (type < a->mKey) { lo = a; a = a->mpNodeRight; }
                    else a = a->mpNodeLeft;
                }
                RBNode_s00d4_d5c0* hi = &mDramaEvents.mAnchor;
                for (RBNode_s00d4_d5c0* b = mDramaEvents.mAnchor.mpNodeParent; b != 0; ) {
                    if (b->mKey < type) b = b->mpNodeLeft;
                    else { hi = b; b = b->mpNodeRight; }
                }
                cDramaEventInstanceData_s00d4_d5c0* found = 0;
                for (RBNode_s00d4_d5c0* p = hi; p != lo; p = (RBNode_s00d4_d5c0*)FUN_00921580(p)) {
                    cDramaEventInstanceData_s00d4_d5c0* v = (cDramaEventInstanceData_s00d4_d5c0*)p->mValue;
                    if (v->mbActive) { found = v; break; }
                }

                u32 bit = gDramaEventToBitArray[type];
                if (found) mActiveDramaEventMask |= bit;
                else       mActiveDramaEventMask &= ~bit;
            }
            n = (RBNode_s00d4_d5c0*)FUN_00921580(n);
        } while (n != end);
    }
}

// @ 0x00d4d790
void cSPDramaManager_s00d4_d5c0::TriggerDramaEvent(u32 eventType, u32 unused)
{
    u32 key = eventType;
    RBNode_s00d4_d5c0* range[2];
    mDramaEvents.equalRange_00d4b450(range, &key);
    RBNode_s00d4_d5c0* n = range[0];
    RBNode_s00d4_d5c0* const hi = range[1];
    while (n != hi) {
        cDramaEventInstanceData_s00d4_d5c0* ev = (cDramaEventInstanceData_s00d4_d5c0*)n->mValue;
        if (!ev->mbActive) {
            TriggerEvent(ev, 0);
        }
        n = (RBNode_s00d4_d5c0*)FUN_00921580(n);
    }
}

// @ 0x00d4d7f0
void FUN_00d4d7f0(void* stream, RBTree_s00d4_d5c0* tree)
{
    tree->destroyNodes_00d0c930(tree->mAnchor.mpNodeParent);
    tree->mAnchor.mpNodeLeft = &tree->mAnchor;
    tree->mAnchor.mpNodeRight = &tree->mAnchor;
    tree->mAnchor.mpNodeParent = 0;
    tree->mAnchor.mColor = 0;
    tree->mAnchor.mKey = 0;

    u32 count = 0;
    FUN_0093a780(StreamIStream(StreamReader(stream)), &count, 1, 0);

    u32 i = 0;
    if (count != 0) {
        do {
            u32 key;
            FUN_0093a780(StreamIStream(StreamReader(stream)), &key, 1, 0);
            StreamTick(stream);

            void* value = 0;
            if (value) { void* old = value; value = 0; RefRelease(old); }
            StreamGetData(stream, 0x558fe09, &value, 0);
            StreamTick(stream);

            // pair{key, value} with an extra addref for the node copy
            u32 pairKey = key;
            void* pairVal = value;
            if (pairVal) RefAddRef(pairVal);

            RBNode_s00d4_d5c0* hint = &tree->mAnchor;
            for (RBNode_s00d4_d5c0* a = tree->mAnchor.mpNodeParent; a != 0; ) {
                hint = a;
                if (key < a->mKey) a = a->mpNodeRight;
                else               a = a->mpNodeLeft;
            }
            int isInsert = 0;
            if (hint != &tree->mAnchor && !(key < hint->mKey)) isInsert = 1;

            RBNode_s00d4_d5c0* node = (RBNode_s00d4_d5c0*)FUN_00f473a0(0x18, RenameSimulator_013f09b4, 0, 0,
                                                 RenameAllocator_013ebb38, 0xd1);
            if (node) {
                node->mKey = pairKey;
                node->mValue = pairVal;
                if (pairVal) RefAddRef(pairVal);
            }
            FUN_009216a0(node, hint, &tree->mAnchor, isInsert);
            tree->mAnchor.mKey++;
            RefRelease(pairKey ? pairVal : pairVal);
            if (value) RefRelease(value);
            i++;
        } while (i < count);
    }
    StreamTick(stream);
}

// @ 0x00d4d9b0
void* RefVec::insert_00d4d9b0(RefPair* pos, const RefPair* value)
{
    RefPair* end = (RefPair*)mEnd;
    u32 idx = (u32)(((u8*)pos - mBegin) >> 3);
    if (pos == end && (u8*)end != mCap) {
        mEnd = (u8*)(end + 1);
        if (end) {
            end->key = value->key;
            void* obj = value->obj;
            end->obj = obj;
            if (obj) RefAddRef(obj);
        }
    } else {
        insertAt_00d4cda0(pos, value);
    }
    return mBegin + idx * 8;
}

// @ 0x00d4da10
bool cDramaEventInstanceData_s00d4_d5c0::WriteData(void* stream)
{
    u32 key;
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    key = 0x558fe09;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);

    u8* begin = mGameDataMap.mBegin;
    u8* end = mGameDataMap.mEnd;
    if (begin != end) {
        u8* next = begin + 8;
        do {
            void* obj = *(void**)(begin + 4);
            if (obj == 0 || ((GameDataObj*)obj)->_gpred()) {
                if (next < mGameDataMap.mEnd) {
                    FUN_00a35070(next, mGameDataMap.mEnd, begin);
                }
                mGameDataMap.mEnd -= 8;
                void* tail = *(void**)(mGameDataMap.mEnd + 4);
                if (tail) RefRelease(tail);
            }
            begin += 8;
            next += 8;
        } while (begin != end);
    }

    local.ctor_00692f90(this, (const char*)0x15836c8, 0x1a80d26);
    return local.serialize_00692900(stream);
}

// @ 0x00d4dae0
void cDramaEventInstanceData_s00d4_d5c0::ClearData()
{
    if (mpPropList) {
        void* p = mpPropList;
        mpPropList = 0;
        RefRelease(p);
    }
    mData.eraseIF_00530c80(mData.mBegin, mData.mEnd);

    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    RefVec* map = &mGameDataMap;
    for (u8* p = map->mBegin, *e = map->mEnd; p != e; p += 8) {
        nm->removeNoun_00b225d0(*(void**)(p + 4));
    }
    map->eraseGD_00621f50(map->mBegin, map->mEnd);
}

// @ 0x00d4db50
bool cDramaEventInstanceData_s00d4_d5c0::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x558fe09;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x15838e4, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4dbe0
bool cNightPredatorEvent_s00d4_d5c0::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599e34;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData_s00d4_d5c0*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583920, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4dc70
bool cUFOAbductionEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599eb8;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData_s00d4_d5c0*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x158395c, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4dd00
bool cBabyGameEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599f2c;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData_s00d4_d5c0*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x15839d4, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4dd90
bool cRainStormEvent_s00d4_d5c0::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599f52;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData_s00d4_d5c0*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583a10, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4de20
bool cSeaMonsterEvent_s00d4_d5c0::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5599f7c;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData_s00d4_d5c0*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583a4c, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4deb0
bool cTribeFoodRaidEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x5ed29d3;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData_s00d4_d5c0*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583a88, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4df40
bool cMeteorStrikeEvent::Write(void* stream)
{
    cVarListSerializer local;
    OReader* reader = ((OStream*)stream)->v8();
    u32 key = 0x609eedc;
    void* istream = reader->v6();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((cDramaEventInstanceData_s00d4_d5c0*)this)->WriteData(stream);
    local.ctor_00692f90(this, (const char*)0x1583ac4, 0x1a80d26);
    if (ok && local.serialize_00692900(stream)) return true;
    return false;
}

// @ 0x00d4dfd0
cSPDramaManager_s00d4_d5c0::~cSPDramaManager_s00d4_d5c0() // modelled as the ctor-named destroying body
{
    *(void**)this = (void*)gVtbl_cSPDramaManager0;
    *(void**)((u8*)this + 8) = (void*)gVtbl_cSPDramaManager8;
    gspDramaManagerInstance = 0;
    RBTree_s00d4_d5c0* t = &mDramaEvents;
    t->destroyNodes_00d0c930(t->mAnchor.mpNodeParent);
    if (mpStalkerNPC) RefRelease(mpStalkerNPC);
    if (mpMate) RefRelease(mpMate);
    mGameTimer.dtor_00b638b0();
    if (mpBabyTeacher) RefRelease(mpBabyTeacher);
    *(void**)((u8*)this + 8) = (void*)gVtbl_ContentValidationSummarizer8;
    *(void**)this = (void*)gVtbl_ContentValidationSummarizer0;
}

// @ 0x00d4e070
void cSPDramaManager_s00d4_d5c0::Init()
{
    u8* mode = (u8*)FUN_00b5b800();
    u32 sig;
    if (mode == &gModeA)      sig = 0xebcfbc7;
    else if (mode == &gModeB) sig = 0xe7ca1f54;
    else return;

    void* propMgr = FUN_0067de30();
    RefVec propList;
    propList.mBegin = 0;
    propList.mEnd = 0;
    propList.mCap = 0;
    ((PropQueryFn)Vtbl(propMgr)[0x48 / 4])(propMgr, sig, &propList);

    mDramaEvents.destroyNodes_00d0c930(mDramaEvents.mAnchor.mpNodeParent);
    mDramaEvents.mAnchor.mpNodeLeft = &mDramaEvents.mAnchor;
    mDramaEvents.mAnchor.mpNodeRight = &mDramaEvents.mAnchor;
    mDramaEvents.mAnchor.mpNodeParent = 0;
    mDramaEvents.mAnchor.mColor = 0;
    mDramaEvents.mAnchor.mKey = 0;

    void* factory = FUN_00920090();
    void* handle = 0;
    for (u8** it = (u8**)propList.mBegin; it != (u8**)propList.mEnd; ++it) {
        void* element = *it;
        if (handle) { void* old = handle; handle = 0; RefRelease(old); }
        if (!((PropFindFn)Vtbl(propMgr)[0x2c / 4])(propMgr, element, sig, &handle))
            continue;

        u8* prop = ((VariantGetFn)Vtbl(handle)[0x28 / 4])(handle, 0xb10f785d);
        u16 tag = *(u16*)(prop + 0x12);
        u8* vp;
        if (tag == 0x0a || tag == 0x10)
            vp = (*(u8*)(prop + 0x10) & 0x30) ? *(u8**)prop : prop;
        else
            vp = gDefaultVariant_015d1164;
        u32 type = *(u32*)vp;
        if (type > 8) continue;

        u32 evsig;
        switch (type) {
        case 0: evsig = 0x558fe09; break;
        case 1: evsig = 0x5599e34; break;
        case 2: evsig = 0x5599eb8; break;
        case 3: evsig = 0x5599ef6; break;
        case 4: evsig = 0x5599f2c; break;
        case 5: evsig = 0x5599f52; break;
        case 6: evsig = 0x5599f7c; break;
        case 7: evsig = 0x5ed29d3; break;
        default: evsig = 0x609eedc; break;
        }
        // the (name, sig) constants live in the jump table, kept as raw data addresses
        const char* name = (const char*)(evsig == 0x558fe09 ? 0x5599d0c :
                                         evsig == 0x5599e34 ? 0x5599e3b :
                                         evsig == 0x5599eb8 ? 0x5599ec7 :
                                         evsig == 0x5599ef6 ? 0x5599f00 :
                                         evsig == 0x5599f2c ? 0x5599f34 :
                                         evsig == 0x5599f52 ? 0x5599f5a :
                                         evsig == 0x5599f7c ? 0x5599f83 :
                                         evsig == 0x5ed29d3 ? 0x5ed29d9 : 0x609eedf);

        cDramaEventInstanceData_s00d4_d5c0* ev =
            (cDramaEventInstanceData_s00d4_d5c0*)((MakeEventFn)Vtbl(factory)[0x20 / 4])(factory, name, evsig, 0, 0);
        if (!ev) continue;

        ev->mType = type;
        void* oldProp = ev->mpPropList;
        if (handle != oldProp) {
            if (handle) RefAddRef(handle);
            ev->mpPropList = handle;
            if (oldProp) RefRelease(oldProp);
        }
        ev->mPropListKey[0] = *(u32*)((u8*)handle + 8);
        ev->mPropListKey[1] = *(u32*)((u8*)handle + 12);
        ev->mPropListKey[2] = *(u32*)((u8*)handle + 16);

        ((SetFn)Vtbl(ev)[0x28 / 4])(ev, 0);   // vtbl[0x28](0)
        RefAddRef(ev);
        u32 pairKey = type;
        void* pairVal = ev;
        RefAddRef(ev);

        RBNode_s00d4_d5c0* hint = &mDramaEvents.mAnchor;
        for (RBNode_s00d4_d5c0* a = mDramaEvents.mAnchor.mpNodeParent; a != 0; ) {
            hint = a;
            if (type < a->mKey) a = a->mpNodeRight;
            else                a = a->mpNodeLeft;
        }
        RBNode_s00d4_d5c0* inserted = 0;
        mDramaEvents.insertUnique_00d4b4f0(&inserted, hint, &pairKey, 0);
        RefRelease(ev);
        RefRelease(ev);
    }

    if (handle) RefRelease(handle);
    if (propList.mBegin && *(u32*)(propList.mBegin - 4) != 0)
        FUN_00f47380(propList.mBegin);
}

// @ 0x00d4e350
void cSPDramaManager_s00d4_d5c0::Shutdown()
{
    ConsumeAllDramaEvents();

    RBNode_s00d4_d5c0* end = &mDramaEvents.mAnchor;
    RBNode_s00d4_d5c0* n = mDramaEvents.mAnchor.mpNodeRight;
    if (n != end) {
        do {
            cDramaEventInstanceData_s00d4_d5c0* ev = (cDramaEventInstanceData_s00d4_d5c0*)n->mValue;
            if (ev->mbActive) {
                ((RefFn)((void**)ev->m_vtbl)[0x34 / 4])(ev);
                ev->mbActive = 0;

                u32 type = ev->mType;
                RBNode_s00d4_d5c0* lo = &mDramaEvents.mAnchor;
                for (RBNode_s00d4_d5c0* a = mDramaEvents.mAnchor.mpNodeParent; a != 0; ) {
                    if (type < a->mKey) { lo = a; a = a->mpNodeRight; }
                    else a = a->mpNodeLeft;
                }
                RBNode_s00d4_d5c0* hi = &mDramaEvents.mAnchor;
                for (RBNode_s00d4_d5c0* b = mDramaEvents.mAnchor.mpNodeParent; b != 0; ) {
                    if (b->mKey < type) b = b->mpNodeLeft;
                    else { hi = b; b = b->mpNodeRight; }
                }
                cDramaEventInstanceData_s00d4_d5c0* found = 0;
                for (RBNode_s00d4_d5c0* p = hi; p != lo; p = (RBNode_s00d4_d5c0*)FUN_00921580(p)) {
                    cDramaEventInstanceData_s00d4_d5c0* v = (cDramaEventInstanceData_s00d4_d5c0*)p->mValue;
                    if (v->mbActive) { found = v; break; }
                }

                u32 bit = gDramaEventToBitArray[type];
                if (found) mActiveDramaEventMask |= bit;
                else       mActiveDramaEventMask &= ~bit;
            }
            ((RefFn)((void**)ev->m_vtbl)[0x2c / 4])(ev);
            n = (RBNode_s00d4_d5c0*)FUN_00921580(n);
        } while (n != end);
    }

    mDramaEvents.destroyNodes_00d0c930(mDramaEvents.mAnchor.mpNodeParent);
    mDramaEvents.mAnchor.mpNodeLeft = &mDramaEvents.mAnchor;
    mDramaEvents.mAnchor.mpNodeRight = &mDramaEvents.mAnchor;
    mDramaEvents.mAnchor.mpNodeParent = 0;
    mDramaEvents.mAnchor.mColor = 0;
    mDramaEvents.mAnchor.mKey = 0;

    if (mpMate) { void* p = mpMate; mpMate = 0; RefRelease(p); }
    mCheckForMateTimer = 0.0f;
    mCurrentMateCallIndex = 0;
    mNestUpgradeLevel = 0;
    mNestItemProgress = 0.0f;
    if (mpStalkerNPC) { void* p = mpStalkerNPC; mpStalkerNPC = 0; RefRelease(p); }
    if (mpBabyTeacher) { void* p = mpBabyTeacher; mpBabyTeacher = 0; RefRelease(p); }
}

// @ 0x00d4e4a0
void __cdecl FUN_00d4e4a0()
{
}

// @ 0x00d4e8e0
__declspec(noinline) void __thiscall SP::cDramaSlotHolder::FUN_00d4e8e0(SP::cDramaRefObj*** ppOutSlot)
{
    *ppOutSlot = 0;
}

// @ 0x00d4e950
void __thiscall SP::cMeteorStrikeEvent_s00d4_e4a0::Clear()
{
}

// @ 0x00d4ea90
void __fastcall cDramaManagerCtor(void* this_, int unused)
{
    (void)this_;
}

// @ 0x00d4eb30
__declspec(noinline) SP::cDramaRefObj** __thiscall SP::cDramaSlotHolder::FUN_00d4eb30(SP::cDramaRefObj*** ppOutSlot)
{
    return (SP::cDramaRefObj**)ppOutSlot;
}

// @ 0x00d4ebe0
void __cdecl allocator_template_helper()
{
}

// @ 0x00d4edd0
void __thiscall SP::cDramaEventHandle::Assign(SP::cDramaRefObj** ppOut, SP::cDramaRefObj* p)
{
    SP::cDramaSlotHolder& holder = mSlotHolder;
    if (p) {
        SP::cDramaRefObj** ppSlot = holder.FUN_00d4eb30(&ppOut);
        SP::cDramaRefObj* pOld = *ppSlot;
        if (p != pOld) {
            p->AddRef();
            *ppSlot = p;
            if (pOld)
                pOld->Release();
        }
    } else {
        holder.FUN_00d4e8e0(&ppOut);
    }
}

// @ 0x00d4ee20
void __thiscall SP::cTribeFoodRaidEvent_s00d4_e4a0::TriggerEvent()
{
}

// @ 0x00d4f0a0
void __thiscall SP::cTribeFoodRaidEvent_s00d4_e4a0::ShouldActivate()
{
}

// @ 0x00d4f260
void __thiscall SP::cTribeFoodRaidEvent_s00d4_e4a0::TickInactiveEvent()
{
}

// @ 0x00d50380
void SP::cMeteorStrikeEvent_s00d5_0380::LoadAndInitMeteorStrikeData(cPropertyList_s00d5_0380* pList)
{
    Clear();
    m_b74 = 1;

    int     nCount = 0;
    float*  pFloat = 0;
    int*    pInt   = 0;
    void*   pVec2  = 0;
    u32*    pU32   = 0;

    if (GetPropertyAsFloatArray(pList, 0x8a788159, &nCount, &pFloat)) {
        m_f88.u[0] = ((u32*)pFloat)[0];
        m_f88.u[1] = ((u32*)pFloat)[1];
    }
    if (GetPropertyAsFloatArray(pList, 0x15585c0a, &nCount, &pFloat)) {
        m_f90.u[0] = ((u32*)pFloat)[0];
        m_f90.u[1] = ((u32*)pFloat)[1];
    }
    if (GetPropertyAsIntArray(pList, 0x5616c7e8, &nCount, &pInt)) {
        m_meteorCount[0][1] = pInt[0];
        m_meteorCount[1][1] = pInt[1];
    }
    if (GetPropertyAsFloatArray(pList, 0x9dc91e04, &nCount, &pFloat)) {
        m_timerB0.u[0] = ((u32*)pFloat)[0];
        m_timerB0.u[1] = ((u32*)pFloat)[1];
    }
    if (GetPropertyAsVector2Array(pList, 0x9920c7ca, &nCount, &pVec2)) {
        u32* src = (u32*)pVec2;
        m_rangeA0.u[0] = src[0];
        m_rangeA0.u[1] = src[1];
        m_rangeA0.u[2] = src[2];
        m_rangeA0.u[3] = src[3];
    }
    if (GetPropertyAsUint32Array(pList, 0xa45eb62d, &nCount, &pU32)) {
        m_u98[0] = pU32[0];
        m_u98[1] = pU32[1];
    }

    if (pList != 0) {
        Property_s00d5_0380* p = 0;
        if (pList->FindProperty(0x9ba81197, &p) && p->m_type12 == 13) {
            m_fB8 = *p->GetFloat();
        }
        if (pList->FindProperty(0x697c13ca, &p) && p->m_type12 == 13) {
            m_fBC = *p->GetFloat();
        }
        if (pList->FindProperty(0x4d4b5974, &p) && p->m_type12 == 13) {
            m_fC0 = *p->GetFloat();
        }
        if (pList->FindProperty(0x8a24d51c, &p) && p->m_type12 == 13) {
            m_fC4 = *p->GetFloat();
        }
    }
}

// @ 0x00d505a0
u8 SP::cMeteorStrikeEvent_s00d5_0380::FUN_00d505a0(void* pAvatar, float dt)
{
    if (m_meteorCount[0][0] == m_meteorCount[0][1] &&
        m_meteorCount[1][0] == m_meteorCount[1][1] &&
        m_meteors[1].mpBegin == m_meteors[1].mpEnd &&
        m_meteors[0].mpBegin == m_meteors[0].mpEnd)
    {
        return 0;
    }

    AnchorIface* pAnchor = (AnchorIface*)((u8*)pAvatar + 0xc0);
    float* pAnchorPos = pAnchor->GetPos();

    void* app = SP_App();
    void* p50 = ((PtrThunk1)(*(void***)app)[0x50 / 4])(app);
    cViewer_s00d5_0380* viewer = (cViewer_s00d5_0380*)((PtrThunk1)(*(void***)p50)[0x1c / 4])(p50);

    Vector3 v1, v2;
    v1.x = gVec0169e440[0]; v1.y = gVec0169e440[1]; v1.z = gVec0169e440[2];
    v2.x = gVec0169e440[0]; v2.y = gVec0169e440[1]; v2.z = gVec0169e440[2];

    if (viewer != 0) {
        viewer->GetCameraLocationInfo(&v1, &v2, 0, 0);
        float inv = 1.0f / (float)(sqrt((double)(v1.x * v1.x + (v1.z * v1.z + v1.y * v1.y)) + kEps));
        v1.x = inv * v1.x;
        v1.y = v1.y * inv;
        v1.z = v1.z * inv;
    }

    float dot = v2.y * v1.y + v2.z * v1.z + v2.x * v1.x;
    v2.y = v2.y - v1.y * dot;
    v2.z = v2.z - v1.z * dot;
    v2.x = v2.x - dot * v1.x;

    float inv2 = 1.0f / (float)(sqrt((double)(v2.x * v2.x + (v2.z * v2.z + v2.y * v2.y)) + kEps));
    v2.x = v2.x * inv2;
    v2.y = v2.y * inv2;
    float z2 = v2.z * inv2;
    v2.z = z2;

    for (int i = 0; i < 2; i++) {
        if (m_meteorCount[i][0] < m_meteorCount[i][1]) {
            float t = m_timerB0.f[i] - dt;
            m_timerB0.f[i] = t;
            if (t <= 0.0f) {
                double lo = (double)m_rangeA0.v[i].x;
                double hi = (double)m_rangeA0.v[i].y;
                double rv = gRand_s00d5_0380.RandomDoubleUniform() * (hi - lo) + lo;
                if (rv >= hi) rv = hi; else if (rv < lo) rv = lo;
                m_timerB0.f[i] = (float)rv;

                float dist = m_f88.f[i];
                float px = pAnchorPos[0] + dist * v2.x;
                float py = pAnchorPos[1] + dist * v2.y;
                float pz = pAnchorPos[2] + dist * v2.z;
                Vector3 pos; pos.x = px; pos.y = py; pos.z = pz;

                void* obj = FUN_00d50040(m_u98[i], (float*)&pos, m_fB8, m_f90.f[i]);
                if (obj != 0) AddRefObj(obj);

                Meteors* vec = &m_meteors[i];
                void** endp = vec->mpEnd;
                if (endp < vec->mpCap) {
                    vec->mpEnd = endp + 1;
                    if (endp != 0) {
                        *endp = obj;
                        if (obj != 0) AddRefObj(obj);
                    }
                } else {
                    FUN_00a0a360(&vec->mpBegin, endp, &obj);
                }
                m_meteorCount[i][0] = m_meteorCount[i][0] + 1;
                if (obj != 0) ReleaseObj(obj);
            }
        }
    }

    FUN_00d502f0(this);
    return 1;
}

// @ 0x00d50960
void SP::cMeteorStrikeEvent_s00d5_0380::ShutdownEvent()
{
    AudioSystem* sys = (AudioSystem*)GetSystemAT();
    if (sys != 0) {
        sys->v38(0x3cdd1a9);
        sys->v40(0x34753a7, 0x413df353);
        sys->v3c(0x34753aa, 0.0f);
        sys->v58();
    }
    Clear();
}

// @ 0x00d509c0
void SP::cMeteorStrikeEvent_s00d5_0380::TickEvent(float dt)
{
    cGameNounManager_s00d5_0380* mgr = (cGameNounManager_s00d5_0380*)SP_NounManager();
    void* avatar = mgr->GetAvatar();
    FUN_00d505a0(avatar, dt);
}

// @ 0x00d509f0
void SP::cMeteorStrikeEvent_s00d5_0380::FUN_00d509f0(int flag)
{
    InitFromTuning(flag);
    if (m_pPropList40 != 0 && (u8)flag == 0) {
        int n = (int)m_thresh20.x;
        u32 r = gRand_s00d5_0380.RandomUint32Uniform(0);
        u32 key = 0x5f10ce1;
        *m_data44.Index(key) = r + (u32)n;
    }
}

// @ 0x00d50a40
void SP::cMeteorStrikeEvent_s00d5_0380::FUN_00d50a40()
{
    GDEntry* begin = (GDEntry*)m_gdBegin5c;
    GDEntry* end   = (GDEntry*)m_gdEnd60;
    u32 key = 0x5f115ab;
    GDEntry* it = (GDEntry*)MapLowerBound(begin, end, &key, m_gdSorted70);
    if (it == end || it->mKey > key) it = end;

    if (it == end || it->mValue == 0) return;

    void* r = CallV0c(it->mValue, 0x52aa6117);
    if (r == 0) return;

    MegaManager* mgr = (MegaManager*)FUN_00b3d480();
    void** arr   = *(void***)((u8*)r + 0x40);
    void** arrEnd = *(void***)((u8*)r + 0x44);
    for (; arr != arrEnd; arr++) {
        void* creature = *arr;
        void* bt = *(void**)((u8*)creature + 0xb4c);
        if (bt != 0) {
            FUN_00bc98f0((u8*)bt + 8, 0, 0x4000);
            void* stim = FUN_00bc97f0(0x20000, 0, kF_14853bc, 0);
            if (stim != 0) {
                *(u32*)((u8*)stim + 0xc) = 1;
            }
        }
        mgr->Method_aca360(creature);
    }

    if (*m_data44.Index(0x613614c) != 0) {
        cGameNounManager_s00d5_0380* nm = (cGameNounManager_s00d5_0380*)SP_NounManager();
        nm->RemoveNoun(r);
    }
    FUN_00d4e8e0(&key);
}

// @ 0x00d50b80
u8 SP::cMeteorStrikeEvent_s00d5_0380::FUN_00d50b80()
{
    float v;
    Property_s00d5_0380* p = 0;
    if (m_pPropList40 == 0 || !m_pPropList40->FindProperty(0x81a3ccd6, &p)) {
        v = kF_13ebc4c;
    } else {
        u16 t = p->m_type12;
        if (t == 13 || t == 16) {
            if ((p->m_flags10 & 0x30) == 0) {
                v = *(float*)p;
            } else {
                v = *p->mpData;
            }
        } else {
            v = kF_15d9c6c;
        }
    }

    u32 key = 0x5f11011;
    u32 raw = *m_data44.Index(key);
    float mapv = *(float*)&raw;
    return (u8)(mapv > v);
}

// @ 0x00d50c30
u8 SP::cMeteorStrikeEvent_s00d5_0380::FUN_00d50c30()
{
    GDEntry* begin = (GDEntry*)m_gdBegin5c;
    GDEntry* end   = (GDEntry*)m_gdEnd60;
    u32 key = 0x5f115ab;
    GDEntry* it = (GDEntry*)MapLowerBound(begin, end, &key, m_gdSorted70);
    if (it == end || it->mKey > key) it = end;

    void* ctx = 0;
    if (it != end && it->mValue != 0) {
        ctx = CallV0c(it->mValue, 0x52aa6117);
    }

    if (!(m_f2c <= 0.0f)) return 1;
    if (ctx == 0) return 1;
    if (*(void**)((u8*)ctx + 0x40) == *(void**)((u8*)ctx + 0x44)) return 1;

    int price = GetTutorialToolPrice(m_pPropList40, 0xf51fc002, 3);

    u32 key2 = 0x5f0f28d;
    int target = (int)*m_data44.Index(key2);

    int n = (int)((*(u8**)((u8*)ctx + 0x44) - *(u8**)((u8*)ctx + 0x40)) >> 2);
    for (int i = 0; i < n; i++) {
        void* creature = *(void**)(*(u8**)((u8*)ctx + 0x40) + i * 4);
        void* bt = *(void**)((u8*)creature + 0xb4c);
        if (FUN_00bc96a0((u8*)bt + 8, 0, 0x4000) == 0) return 1;
        void* h = FUN_00bc96a0((u8*)bt + 8, 0x2000, 0);
        if (h != 0) {
            void* a = FUN_00d998d0(h, 0x17f243b);
            if (a != 0) {
                int skip = 0;
                void* b = FUN_00d4cf10(0x5f11333, 0x4f396a66);
                if (b != 0) {
                    if (CallV4c(b) != CallV4c(a)) skip = 1;
                }
                if (!skip) {
                    u32 idv = *(u32*)((u8*)a + 0x24);
                    u32 k3 = idv;
                    if (*m_data44.Index(k3) == 0) {
                        target = target + 1;
                        u32 k4 = 0x5f0f28d;
                        *m_data44.Index(k4) = (u32)target;
                        u32 k5 = *(u32*)((u8*)a + 0x24);
                        *m_data44.Index(k5) = 1;
                    }
                }
            }
        }
    }

    u32 key6 = 0x5f0f28d;
    return (u8)(price <= (int)*m_data44.Index(key6));
}

// @ 0x00d50e40
void SP::cMeteorStrikeEvent_s00d5_0380::FUN_00d50e40(float dt)
{
    GDEntry* begin = (GDEntry*)m_gdBegin5c;
    GDEntry* end   = (GDEntry*)m_gdEnd60;
    u32 key = 0x5f11333;
    GDEntry* it = (GDEntry*)MapLowerBound(begin, end, &key, m_gdSorted70);
    if (it == end || it->mKey > key) it = end;
    if (it == end || it->mValue == 0) return;

    if (CallV0c(it->mValue, 0x4f396a66) == 0) return;

    u32 k = 0x5f11011;
    float cur = *(float*)m_data44.Index(k);
    float sum = cur + dt;
    *m_data44.Index(k) = *(u32*)&sum;
}

// @ 0x00d50ef0
void SP::cMeteorStrikeEvent_s00d5_0380::FUN_00d50ef0()
{
    Vector3 pos;
    pos.x = gVec0169e440[0]; pos.y = gVec0169e440[1]; pos.z = gVec0169e440[2];

    cGameNounManager_s00d5_0380* mgr = (cGameNounManager_s00d5_0380*)SP_NounManager();
    void* avatar = mgr->GetAvatar();

    if (avatar != 0) {
        u8 head[12];
        Vector3 dir;
        if (FUN_00d9a360(head, (float*)&dir)) {
            float len = (float)sqrt((double)(dir.x * dir.x + (dir.y * dir.y + dir.z * dir.z)));
            if (len > kTiny) {
                float inv = 1.0f / len;
                dir.x = dir.x * inv;
                dir.y = dir.y * inv;
                dir.z = dir.z * inv;
            }
            float sx = dir.x * kSeventy;
            float sy = dir.y * kSeventy;
            float sz = dir.z * kSeventy;

            AnchorIface* pAnchor = (AnchorIface*)((u8*)avatar + 0xc0);
            float* ap = pAnchor->GetPos();
            Vector3 target;
            target.x = ap[0] + sx;
            target.y = ap[1] + sy;
            target.z = ap[2] + sz;

            u8 surf[16];
            void* pm = SP_PlanetModel(surf, &target, 0);
            float* snapped = (float*)FUN_00b82970(pm, &target, 0);
            pos.x = snapped[0];
            pos.y = snapped[1];
            pos.z = snapped[2];
        }
    }

    if (pos.x == gVec0169e440[0] && pos.y == gVec0169e440[1] && pos.z == gVec0169e440[2]) {
        return;
    }

    float keyInst = 0.0f;
    GetPropertyAsKeyInstance(m_pPropList40, 0x1b806155, &keyInst);

    u8 orient[16];
    void* pm2 = SP_PlanetModel(orient, &pos);
    FUN_00b7f190(pm2, orient, &pos);

    u8 out2[16];
    void* owner = FUN_00b23650(0x1be418e, keyInst, 0, &pos, orient);
    if (owner == 0) return;

    if (((u32(__thiscall*)(void*))(*(u32**)owner)[0x20 / 4])(owner) != 0x1be418e) return;

    SpawnedObj* sp = (SpawnedObj*)owner;
    *m_data44.Index(0x614a7ea) = 0;
    FUN_00d4edd0(0x609f2f8, owner);
    sp->m_i124 = -1;
    sp->m_b128 = 0;
    sp->m_b192 = 1;

    void* sub = FUN_00401010();
    u8 tmp[8];
    *(u32*)(tmp + 0) = 0x0609b763;
    *(u16*)(tmp + 4) = 4;
    *(u16*)(tmp + 6) = 0;
    (*(void(__thiscall*)(void*, void*, void*))(*(u32**)sub)[0x4c / 4])(sub,
        (void*)((u8*)sp->m_CreatureA4 + 0x504), tmp);

    FUN_01021260((void**)&sp->m_v98);
    FUN_00c74690((void**)&sp->m_v98, 1, 0);
    void* b3 = FUN_00b3d480();
    void* posse = FUN_00d539d0();

    u32 count = *(u32*)((u8*)sp + 0xf4);
    for (u32 i = 0; i < count; i++) {
        Vector3 rnd;
        Vector3 dirv;
        void* pm3 = SP_PlanetModel(&dirv, &rnd, kTen, kSeventy);
        FUN_00b81780(pm3, &dirv, &rnd, kTen, kSeventy);

        float inv = 1.0f / (float)(sqrt((double)(rnd.x * rnd.x + (rnd.y * rnd.y + rnd.z * rnd.z)) + kEps));
        rnd.x = (rnd.x * inv) * kTen + rnd.x;
        rnd.y = (rnd.y * inv) * kTen + rnd.y;
        rnd.z = (rnd.z * inv) * kTen + rnd.z;

        void* creature = FUN_00c099e0((float*)&rnd, *(float*)&sp->m_CreatureA4, 1, owner, 0, 1);
        FUN_00acd2d0(creature);

        AnchorIface* cAnchor = (AnchorIface*)((u8*)creature + 0xc0);
        void* v30 = ((PtrThunk1)(*(void***)cAnchor)[0x30 / 4])(cAnchor);
        (*(void(__thiscall*)(void*, void*, void*))(*(u32**)cAnchor)[0x44 / 4])(cAnchor, &rnd, v30);
        FUN_00c13a30(creature, 1);
        if (posse != 0) {
            FUN_00d54330(posse, creature);
        }
    }
}

// @ 0x00f21cd0
void eastl::DramaEventMultiMap::equal_range(void** out, const unsigned int* key)
{
    void** root = *(void***)((char*)this + 0xc);
    void** lower = (void**)((char*)this + 4);
    void** upper = lower;
    void** node = root;
    if (node != 0)
    {
        do
        {
            void** next;
            if (*key < (unsigned int)node[4]) { next = (void**)node[1]; upper = node; }
            else next = (void**)*node;
            node = next;
        } while (node != 0);
    }
    node = root;
    if (node != 0)
    {
        do
        {
            void** next;
            if ((unsigned int)node[4] < *key) next = (void**)*node;
            else { next = (void**)node[1]; lower = node; }
            node = next;
        } while (node != 0);
    }
    out[1] = upper;
    out[0] = lower;
}

// @ 0x01364f50
void init_15836c8()
{
    Attribute a;

    a.mpName   = "mbActive";
    a.mHash    = 0x0559039b;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00ac8750;
    a.mpFn28   = (void*)&FUN_00ac8780;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694fa0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_0057ce00;
    a.mLocation = 0xc;
    g_commandUIAttributes[0] = a;

    a.mpName   = "mType";
    a.mHash    = 0x055903a0;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x14;
    g_commandUIAttributes[1] = a;

    a.mpName   = "mFrequency";
    a.mHash    = 0x0695c2d7;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x18;
    g_commandUIAttributes[2] = a;

    a.mpName   = "mCheckTime";
    a.mHash    = 0x069d8c20;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00ac88f0;
    a.mpFn2c   = (void*)&FUN_006930b0;
    a.mpFn30   = (void*)&FUN_00694fc0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00acbb80;
    a.mLocation = 0x28;
    g_commandUIAttributes[3] = a;

    a.mpName   = "mDuration";
    a.mHash    = 0x055946f7;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00ac88f0;
    a.mpFn2c   = (void*)&FUN_006930b0;
    a.mpFn30   = (void*)&FUN_00694fc0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00acbb80;
    a.mLocation = 0x2c;
    g_commandUIAttributes[4] = a;

    a.mpName   = "mPropListKey";
    a.mHash    = 0x055903a4;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00ae3430;
    a.mpFn28   = (void*)&FUN_00ae3450;
    a.mpFn2c   = (void*)&FUN_00693150;
    a.mpFn30   = (void*)&FUN_00695080;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00ae5720;
    a.mLocation = 0x34;
    g_commandUIAttributes[5] = a;

    a.mpName   = "mData";
    a.mHash    = 0x055903a7;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00cdb4c0;
    a.mpFn28   = (void*)&FUN_00cd5980;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00cd92f0;
    a.mLocation = 0x44;
    g_commandUIAttributes[6] = a;

    a.mpName   = "mGameDataMap";
    a.mHash    = 0x055903ab;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00d4ebe0;
    a.mpFn28   = (void*)&FUN_00d4cce0;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)(void(*)())FUN_00d4b390;
    a.mpFn38   = (void*)&FUN_00c78ff0;
    a.mLocation = 0x5c;
    g_commandUIAttributes[7] = a;
}

// @ 0x01365320
void init_1583b00()
{
    Attribute a;

    a.mpName   = "mGameTimer";
    a.mHash    = 0x057a5299;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00ae3470;
    a.mpFn28   = (void*)&FUN_00ae3490;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00ae3310;
    a.mpFn38   = (void*)&FUN_00ac8050;
    a.mLocation = 0x18;
    g_mateBehaviourAttributes[0] = a;

    a.mpName   = "mpMate";
    a.mHash    = 0x32709745;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00b20510;
    a.mpFn28   = (void*)&FUN_00bca960;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00b6f550;
    a.mpFn38   = (void*)&FUN_00ac8050;
    a.mLocation = 0x38;
    g_mateBehaviourAttributes[1] = a;

    a.mpName   = "mpBabyTeacher";
    a.mHash    = 0x94d9ce6c;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00b20510;
    a.mpFn28   = (void*)&FUN_00bca960;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00b6f550;
    a.mpFn38   = (void*)&FUN_00ac8050;
    a.mLocation = 0x14;
    g_mateBehaviourAttributes[2] = a;

    a.mpName   = "mCheckForMateTimer";
    a.mHash    = 0x04a0ad62;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00ac88f0;
    a.mpFn2c   = (void*)&FUN_006930b0;
    a.mpFn30   = (void*)&FUN_00694fc0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00acbb80;
    a.mLocation = 0x3c;
    g_mateBehaviourAttributes[3] = a;

    a.mpName   = "mCurrentMateCallIndex";
    a.mHash    = 0x04a0ad63;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x40;
    g_mateBehaviourAttributes[4] = a;

    a.mpName   = "mNestUpgradeLevel";
    a.mHash    = 0x93f4227d;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00692ff0;
    a.mpFn30   = (void*)&FUN_00694ee0;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_0057cde0;
    a.mLocation = 0x44;
    g_mateBehaviourAttributes[5] = a;

    a.mpName   = "mDramaEvents";
    a.mHash    = 0x055912ad;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)(void(*)())FUN_00d4d7f0;
    a.mpFn28   = (void*)&FUN_00ba94e0;
    a.mpFn2c   = (void*)&FUN_00c2e4e0;
    a.mpFn30   = (void*)&FUN_00692fb0;
    a.mpFn34   = (void*)&FUN_00ba7450;
    a.mpFn38   = (void*)&FUN_00baa2b0;
    a.mLocation = 0x50;
    g_mateBehaviourAttributes[6] = a;

    a.mpName   = "mActiveDramaEventMask";
    a.mHash    = 0x746556ec;
    a.mZero18  = 0;
    a.mZero1c  = 0;
    a.mpFn20   = (void*)&FUN_00692ca0;
    a.mpFn24   = (void*)&FUN_00572810;
    a.mpFn28   = (void*)&FUN_00572840;
    a.mpFn2c   = (void*)&FUN_00693090;
    a.mpFn30   = (void*)&FUN_00694f00;
    a.mpFn34   = (void*)&FUN_00b1fbf0;
    a.mpFn38   = (void*)&FUN_00675ca0;
    a.mLocation = 0x6c;
    g_mateBehaviourAttributes[7] = a;
}
