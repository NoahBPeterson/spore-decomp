// src/game/SPGonzago/_at_00fe0000.cpp -- migrated from slice(s) s00feff80, s00fef140, s00fea240, s00fe8630, s00fe76d0, s00fe68a0, s00fe3b10 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00fe0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cISerializableObject.h"
#include "SP/cIObjectDatabaseOStream.h"
#include "SP/cPropertyList.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"
#include "EA/Variant.h"
#include <math.h>
#include "SP/cGameNounManager.h"
#include "SP/cEmpire.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cCommandBase.h"
#include "SP/cGonzagoSimulator.h"
#include "SP/cStarManager.h"
#include "SP/cViewer.h"
#include <stddef.h>
#include <string.h>
#include <new>
#include "SP/cSPMission.h"
#include "cSPVector3.h"
#include "SP/cBuildingData.h"
#include "SP/cCityData.h"
#include "SP/cCivData.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSpatialObject.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTribe.h"
#include "SP/cTribeData.h"
#include "SP/cVehicleData.h"

// ---- items of slice s00fe3b10 begin (TODO(rewrite): local stubs, replace by canonical classes)
int32_t     __cdecl GetUniverseContext();                  // 0x01021080
void*       __cdecl GetActivePlanet();                     // 0x01021260
void*       __cdecl SpaceGameGet();                        // 0x01002bd0
void        __cdecl FUN_00aea5d0(void** ppEnd, const void* pValue);  // 0x00aea5d0 eastl vector grow
struct tRBNode;
tRBNode*    __cdecl RBTreeIncrement(tRBNode* pNode);       // 0x00921580
struct tRBNode {                        // eastl::rbtree_node_base
    tRBNode* mpNodeRight;               // +0x00
    tRBNode* mpNodeLeft;                // +0x04
    tRBNode* mpNodeParent;              // +0x08
    uint32_t mColor;                    // +0x0c
};
struct tPairNode {                      // rbtree node holding pair<const unsigned, unsigned>
    tRBNode  mBase;                     // +0x00
    uint32_t mKey;                      // +0x10
    uint32_t mValue;                    // +0x14
};
class tU32Tree {
public:
    uint32_t    mBase00;                // +0x00
    tRBNode     mAnchor;                // +0x04
    uint32_t    mnSize;                 // +0x14
    uint32_t    mAllocator18;           // +0x18
    tPairNode** find(tPairNode** ppOut, const uint32_t* pKey) const; // 0x00e5c780
    void        DoNukeSubtree(tRBNode* pNode);                       // 0x009a9600
    tPairNode*  begin() const { return (tPairNode*)mAnchor.mpNodeLeft; }
    tPairNode*  end() const { return (tPairNode*)&mAnchor; }
    ~tU32Tree()                                                      // inline in the original
    {
        DoNukeSubtree(mAnchor.mpNodeParent);
    }
    void clear()                                                     // inline in the original
    {
        DoNukeSubtree(mAnchor.mpNodeParent);
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
        mAnchor.mpNodeRight = &mAnchor;
    }
};
class cStarContext;
cStarContext* __cdecl FUN_01021230();                                 // 0x01021230
class cGalaxyPlanet {
public:
    uint32_t       mPad00[0x13c / 4];   // +0x000
    cGalaxyPlanet* mpOwner13c;          // +0x13c
    int32_t        GetSystemId();                                    // 0x00b8de30
};
class cStarContext {
public:
    uint32_t mPad00[0x48 / 4];          // +0x00
    int32_t  mnSystemId;                // +0x48
};
class cBadgeEntry {
public:
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
};
cBadgeEntry* __fastcall FUN_00c30c60(uint32_t nId);                   // 0x00c30c60
class tStarManager;
tStarManager* __cdecl StarManager();                                  // 0x00b3d2a0
class tStarManager {
public:
    tU32Tree* GetBadgeTree();                                        // 0x00ba6430
};
class tBadgeVec {
public:
    cBadgeEntry** mpBegin;              // +0x00
    cBadgeEntry** mpEnd;                // +0x04
    cBadgeEntry** mpCapacity;           // +0x08
    uint32_t      mPad0c;               // +0x0c
    uint32_t      mPad10;               // +0x10
    void push_back(const class tBadgeRef& r);                        // inline in the original
};
class tBadgeRef {
public:
    cBadgeEntry* mpObject;              // +0x00
    explicit tBadgeRef(cBadgeEntry* pObject) : mpObject(pObject)
    {
        if (mpObject != 0)
            mpObject->AddRef();
    }
    tBadgeRef(const tBadgeRef& r) : mpObject(r.mpObject)
    {
        if (mpObject != 0)
            mpObject->AddRef();
    }
    ~tBadgeRef()
    {
        if (mpObject != 0)
            mpObject->Release();
    }
};
void tBadgeVec::push_back(const tBadgeRef& r)
{
    if (mpEnd < mpCapacity) {
        cBadgeEntry* pObject = r.mpObject;
        *mpEnd++ = pObject;
        if (pObject != 0)
            pObject->AddRef();
    } else {
        FUN_00aea5d0((void**)mpEnd, &r);
    }
}
// ---- items of slice s00fe3b10 end

// ---- items of slice s00fe68a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uintptr_t;
void*  __cdecl FUN_01021300(void);                               // 0x01021300
void*  __cdecl FUN_010666a0(void);                               // 0x010666a0
void*  __cdecl FUN_0067dcc0(void);                               // 0x0067dcc0
void*  __cdecl FUN_00b3d380(void);                               // 0x00b3d380
void*  __cdecl FUN_00fd9c60(void);                               // 0x00fd9c60
void*  __stdcall FUN_00401090(void* key);                        // 0x00401090
float  __cdecl FUN_004d12a0(void* a);                            // 0x004d12a0
void*  __cdecl FUN_00c028b0(void* a, int b);                     // 0x00c028b0
void   __cdecl FUN_00881ea0(double v, void* buf, int a, int b);  // 0x00881ea0
void*  __cdecl operator_new_sp(unsigned size, const char* name,
                               int a, int b, int c, int d);       // 0x00f473a0
void   __cdecl operator_delete(void* p);                         // 0x00f47380
struct MC {
    void* f_00c30f90();                  // 0x00c30f90
    void* f_004df550();                  // 0x004df550
    void* f_00fdf5f0();                  // 0x00fdf5f0
    void* f_0108db30();                  // 0x0108db30
    void* f_00ba6430();                  // 0x00ba6430
    void* f_00ba93b0();                  // 0x00ba93b0
    void* f_00b1fdb0();                  // 0x00b1fdb0
    bool  f_00bb9c00();                  // 0x00bb9c00
    bool  f_00bb9bd0();                  // 0x00bb9bd0
    void  f_00b962d0(void* src);         // 0x00b962d0
    void  f_00bb1080();                  // 0x00bb1080
    void  f_00c344f0(void* a, int b);    // 0x00c344f0
    void  f_00ae6970();                  // 0x00ae6970  vector dtor
    void  f_009a9600(void* root);        // 0x009a9600  rbtree nuke
    void  f_00e25bd0(void* first, void* last);   // 0x00e25bd0  vector::erase
    void  f_00a17a70(void* a, void* b, void* c);// 0x00a17a70  rbtree insert
    void* f_00d01790(int n);             // 0x00d01790
    void* f_00e012b0(unsigned id);       // 0x00e012b0
    void  f_00f13890();                  // 0x00f13890
    void  f_00f138c0();                  // 0x00f138c0
    void* f_00f13810();                  // 0x00f13810
    void  f_0093a560(int a, int b);      // 0x0093a560  Stopwatch ctor
    void  f_0093a1a0(int units);         // 0x0093a1a0  Stopwatch::SetUnits
    void  f_00b32250(unsigned id);       // 0x00b32250  DecPauseGate
    void* f_008105b0(unsigned id, int b);// 0x008105b0  FindWindowByID
    void* f_00c8b360(void* a, void* b);  // 0x00c8b360  StarManager::Query
};
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
struct Key { uint32_t a, b, c; };
struct Vec {                    // eastl vector header
    void*    mBegin;            // +0x00
    void*    mEnd;              // +0x04
    void*    mCapacity;         // +0x08
    uint32_t mPad0c;            // +0x0c
    uint32_t mPad10;            // +0x10
};
struct Rbtree {                 // eastl set header
    uint32_t mField00;          // +0x00
    void*    mNode;             // +0x04  (self-referential anchor)
    void*    mNode2;            // +0x08
    void*    mRoot;             // +0x0c
    union {
        uint32_t mSize;         // +0x10
        uint8_t  mSizeByte;     // +0x10
    };
    uint32_t mField14;          // +0x14
    uint32_t mField18;          // +0x18
};
struct cCachedEventData {
    void*    mpVtbl;            // +0x00
    void*    mHandler;          // +0x04  (EA::Messaging::AutoHandler)
    void*    mArg08;            // +0x08
    uint32_t mArg0c;            // +0x0c
    uint32_t mArg10;            // +0x10
    uint32_t mArg14;            // +0x14
    Vec      mPlayerAllyColonyPlanets;   // +0x18
    Vec      mColonizedPlanetList;       // +0x2c
    Vec      mGrobPlanetList;            // +0x40
    Vec      mHomeworldStarsList;        // +0x54
    Vec      mNearbyEmpireStars;         // +0x68
    Vec      mNearbyKnownEmpireStars;    // +0x7c
    Rbtree   mNearbyEmpires;             // +0x90
    Rbtree   mLocalEmpires;              // +0xac
    Rbtree   mActiveEmpires;             // +0xc8
    Rbtree   mInactivePlayers;           // +0xe4
    int      mBioProtectedPlanetCount;   // +0x100
    int      mLoyaltyBoostedPlanetCount; // +0x104

    cCachedEventData();                                  // 0x00fe68a0
    ~cCachedEventData();                                 // 0x00fe6a00
    void InsertRange(void* first, void* last);           // 0x00fe6ad0
    void RebuildInactivePlayersCache();                  // 0x00fe6b20
    void RebuildNearbyEmpireStarsCache();                // 0x00fe6bc0
    void RebuildAllyColonyPlanetCache();                 // 0x00fe6dc0
    void RebuildPlayerColonyPlanetCache();               // 0x00fe6e40
    bool HandleMessage(unsigned int msg, void* arg);     // 0x00fe6fb0
    void Flush();                                        // 0x00fe7020
    void Prime();                                        // 0x00fe7100
    void Init();                                         // 0x00fe7160
    void Shutdown();                                     // 0x00fe71c0
};
struct cHelper7210 {
    uint8_t mPad00[0xb8];
    uint8_t mbFieldB8;          // +0xb8

    bool HandleEvent(uint32_t msg, int* arg);   // 0x00fe7210
};
struct cSimOwner {
    void*   mpVtbl;             // +0x00
    void*   mpVtbl2;            // +0x04
    void*   mField08;           // +0x08
    uint8_t pad0c[0x04];        // +0x0c
    uint8_t mStopwatch[0x18];   // +0x10  (EA::Stopwatch)
    uint8_t mbField28;          // +0x28
    uint8_t pad29[0x03];
    cSimOwner* mpField2c;       // +0x2c
    void*   mField30;           // +0x30
    uint8_t pad34[0x88];
    uint8_t mbFieldBC;          // +0xbc

    cSimOwner();                            // 0x00fe75d0
    void* Destroy(int flags);               // 0x00fe7680
};
// ---- items of slice s00fe68a0 end

// ---- items of slice s00fe76d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float        DAT_01485720;   // 0x1485720   1.0f
extern "C" float        DAT_015b44f8;   // 0x15b44f8   1.5707964f (pi/2)
extern "C" float        DAT_013eb8a0;   // 0x13eb8a0   0.25f
extern "C" float        DAT_01471064;   // 0x1471064   0.5f
extern "C" float        DAT_013f9428;   // 0x13f9428   0.001f
extern "C" float        DAT_013ef56c;   // 0x13ef56c  -0.001f
extern "C" float        DAT_013f89bc;   // 0x13f89bc   1e-05f
extern "C" float        DAT_01477fbc;   // 0x1477fbc   200.0f
extern "C" unsigned int DAT_015b444c;   // 0x15b444c
extern "C" unsigned int DAT_015da7c4;   // 0x15da7c4
extern "C" unsigned int DAT_015da7c8;   // 0x15da7c8
extern "C" unsigned int DAT_015da7cc;   // 0x15da7cc
extern "C" unsigned int DAT_015da7d0;   // 0x15da7d0
extern "C" unsigned int DAT_01488848;   // 0x1488848
extern "C" char         DAT_013ebc58[]; // 0x13ebc58  "App"
extern "C" unsigned int DAT_016c7aa4;   // 0x16c7aa4  Simulator singleton
void* FUN_00b3d490(void);                                              // 0xb3d490
void* FUN_010212a0(void);                                              // 0x10212a0
void* FUN_00aed4d0(void);                                              // 0xaed4d0
void* FUN_00b3d320();                                                 // 0xb3d320 (0-arg getter)
void* FUN_00b3d300(void);                                              // 0xb3d300 SP_NounManager
void* SP_MessageServer(void);                                          // 0x67dcc0
void* SP_App(void);                                                    // 0x67dd10
void* FUN_00f473a0(unsigned sz, const char* f, int l, int a, int b, int c); // 0xf473a0 EAAllocate
void  FUN_00fe7590(int a, int b);                                      // 0xfe7590
void  FUN_00fe72b0();                                                  // 0xfe72b0
void  FUN_00fe73c0();                                                  // 0xfe73c0
void  FUN_00fe74a0();                                                  // 0xfe74a0
void* FUN_00eec580(int a);                                             // 0xeec580
int   FUN_005bf0e0(void* owner, void** out);                           // 0x5bf0e0 GetEditorPropertyList
int   FUN_00410370(void* list, unsigned key, unsigned* out);           // 0x410370 TryGetUIntProperty
void  FUN_00eb96a0(void* out, const void* src, const wchar_t* in);     // 0xeb96a0
void  FUN_00881ae0(int value, int sign, wchar_t* buf, unsigned n);     // 0x881ae0 Locale::SetNumberString
void  FUN_00807c70(void* a, void* b, int c, int d);                    // 0x807c70
void  FUN_00806de0(void* w, void* text, int a, int b);                  // 0x806de0 SetTooltipText
void* EA_COM_interface_cast(void* p);                                  // 0xfe7290 interface_cast
struct Fns {
    void  f1067f60(int x);                       // 0x1067f60
    void  ae8ea0();                              // 0xae8ea0 CommHost::ResetSlots
    void  b32220(unsigned tag);                  // 0xb32220 GameTimeManager::IncPauseGate
    void  b32250(unsigned tag);                  // 0xb32250 GameTimeManager::DecPauseGate
    void  f16fd0();                              // 0xf16fd0
    void* c30f90();                              // 0xc30f90 GetPlayerEmpire
    void* f67d90();                              // 0xf67d90 cTerrainEditor::GetCurrentTerrainSphere
    void  f12680(unsigned a);                    // 0xf12680
    void  f16260();                              // 0xf16260
    void  f14980();                              // 0xf14980
    void  f120c0(void* w);                       // 0xf120c0
    void  f150d0(void* v);                       // 0xf150d0 Owner::Load
    void  f17b00(void* v);                       // 0xf17b00
    void* g5a9080();                             // 0x5a9080 ctor (returns this)
    void  g6b5770(unsigned a, unsigned b, const wchar_t* c); // 0x6b5770 cString ctor
    void  g6b5240();                             // 0x6b5240 cString dtor
    const wchar_t* g6b55c0();                    // 0x6b55c0 cString::GetText
    void  g6ec1c0(void* src);                    // 0x6ec1c0
    void  g57cb80();                             // 0x57cb80 eastl::fixed_string dtor
    void  gb1dee0(void* obj);                    // 0xb1dee0
    void* b8d9b0();                              // 0xb8d9b0
    char  ec5a60(void* ctx, int a, int b);       // 0xec5a60
    void  ae7e10(unsigned a, unsigned b, int c, int d);  // 0xae7e10
    void  g93a2e0();                             // 0x93a2e0 SetBoolProperty
    long long g93a3a0();                         // 0x93a3a0 GetElapsedTimeTicks
};
struct Layout  { void* FindWindowByID(unsigned int id, int flag); };   // 0x8105b0
struct GlobUI  { void* FindWindowByID(unsigned int id); };             // 0xe012b0
struct IWinL {
virtual void  a00();
virtual void a04();
virtual void a08();
    virtual void* a0c(unsigned int id);
virtual void  a10();
virtual void a14();
virtual void a18();
virtual void  a1c();
virtual void a20();
virtual void a24();
    virtual char  a28();
virtual void  a2c();
virtual void a30();
virtual void a34();
    virtual float* a38();
virtual void  a3c();
virtual void a40();
virtual void a44();
virtual void  a48();
virtual void a4c();
virtual void a50();
virtual void  a54();
virtual void a58();
virtual void a5c();
virtual void  a60();
virtual void a64();
virtual void a68();
    virtual void  a6c(void* p);
virtual void  a70();
virtual void a74();
virtual void a78();
    virtual void  a7c(int a, int b);
    virtual char  a80(const void* s);
};
struct IWinG {
virtual void  a00();
virtual void a04();
virtual void a08();
    virtual void* a0c(unsigned int id);
virtual void  a10();
virtual void a14();
virtual void a18();
virtual void  a1c();
virtual void a20();
virtual void a24();
    virtual void  a28(int a, int b);
};
struct Brush {
    unsigned char b00;
    char  pad01[3];
    float f04, f08, f0c, f10, f14, f18, f1c, f20;
    float f24, f28, f2c, f30, f34, f38, f3c;
    float f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64;

    void f8450();
};
struct NewObj {                      // freshly constructed editor-launch object
virtual void  n00();
virtual void n04();
virtual void* n08();
};
struct SimpleVec {
    unsigned* begin; unsigned* end; unsigned* cap;
    void  DoInsertValue(void* pos, const void* val);    // 0x4558a0 eastl::vector::DoInsertValue
};
static void vecPush(SimpleVec* v, unsigned val)
{
    unsigned* p = v->end;
    if (p < v->cap) {
        v->end = p + 1;
        if (p != 0)
            *p = val;
    } else {
        v->DoInsertValue(p, &val);
    }
}
struct MsgObj { virtual void m00(); virtual void m04(); virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
                virtual void m18(); virtual unsigned m1c(); };
struct MsgSrv { virtual void m00(); virtual void m04(); virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
                virtual void v20(void* a, unsigned b);
virtual void m24();
virtual void m28();
                virtual void v2c(void* a, unsigned b, int c); };
struct AppV { virtual void a00(); virtual void a04(); virtual void a08();
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
virtual void a38();
virtual void a3c();
virtual void a40();
virtual void a44();
virtual void a48();
virtual void a4c();
              virtual void* a50(); };
struct AppCam { virtual void c00(); virtual void c04(); virtual void c08();
virtual void c0c();
virtual void c10();
virtual void c14();
virtual void c18();
virtual void c1c();
virtual void c20();
virtual void c24();
virtual void c28();
virtual void c2c();
virtual void c30();
virtual void c34();
virtual void* c38();
virtual void c3c();
virtual void c40();
virtual void c44();
virtual void c48();
virtual void c4c();
virtual void c50();
virtual void c54();
virtual void c58();
virtual void c5c();
                virtual void c60();
                virtual void c64(int a); };
struct AedV { virtual void a00(); virtual void a04(); virtual void a08();
virtual void a0c();
virtual void a10();
virtual void a14();
virtual void a18();
virtual void a1c();
virtual void a20();
              virtual void a24(); virtual void a28(unsigned, unsigned, void*, void*); };
struct CBr {
    char   pad00[4];
    void*  f04;
    unsigned f08;
    char   pad0c[4];
    char   f10[8];
    char   pad18[0xc];
    float  f24;
    unsigned char f28;
    char   pad29[3];
    void*  f2c;
    char   f30[0x8c];
    unsigned char fbc;
    char   padbd[0x43];

    void  f76d0(int p);
    void  f7d70();
    void* f7b80();
    void  f7e10();
    char  f7e60(unsigned p2, void** msg);
};
// ---- items of slice s00fe76d0 end

// ---- items of slice s00fe8630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float RaySphereIntersect(const float* a, const float* b, const float* c);  // 0x006994a0
extern "C" void* GetTriggerMgr();                    // 0x00b3d4d0
extern "C" void* SP_SpaceGameGet();                  // 0x01002bd0
#define NOINLINE __declspec(noinline)
typedef unsigned int   u32;
struct Brush_s00fe_8630;                       // fwd (the rule-set is shared with the brush code)
struct Brush_s00fe_8630 {
    unsigned char b00;                  // +0x00
    char  pad01[3];
    float f04, f08, f0c, f10, f14, f18, f1c, f20;
    float f24, f28, f2c, f30, f34, f38, f3c;
    float f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64;

    bool __thiscall ShouldGrow();        // 0x00fe8990
    char __thiscall ReadBrush(void* stream);   // 0x00fe8880
    void __thiscall DeriveFields();            // 0x00fe8450
};
int f8380(float* value, const Brush_s00fe_8630* p, float p1, float p2);   // 0x00fe8380
struct VarListSerializer {               // 0x00a14 bytes
    char mData[0xa14];
    void __thiscall ctor(void* owner, int id, int tag);   // 0x00692f90
    char __thiscall Read(void* stream);                   // 0x00693e10
};
struct SpVectorV3 {
    void __thiscall resize(int n);       // 0x00473810
    char* mpBegin;                       // +0x00
    char* mpEnd;                         // +0x04
    char* mpCap;                         // +0x08
};
struct TriggerMgr { char pad00[0x2c]; int mode; };   // mode at +0x2c
struct GameNounMgr {
    void* __thiscall GetPlayerTribe();               // 0x00bfc5f0
};
struct TribeState {
    unsigned int __thiscall GetStage();              // 0x00fe42a0
};
struct GrowthState {
    char pad00[0x48];
    unsigned char b48;                               // +0x48
    unsigned char b49;                               // +0x49

    bool __thiscall ShouldGrow();
};
// ---- items of slice s00fe8630 end

// ---- items of slice s00fea240 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VtableHolder {
    void* mpVtable;   // +0x00
    void* mpField4;   // +0x04
};
// ---- items of slice s00fea240 end

// ---- items of slice s00fef140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b8de30();
extern "C" void* __cdecl FUN_00401090(void*, void*);
#pragma warning(disable : 4100)
typedef unsigned char u8;
struct cReqElem;
void* __cdecl FUN_00fef810(cReqElem*, cReqElem*, cReqElem*);
extern "C" void* __cdecl FUN_00c8b450(u32);                         // IsGasStarType
extern "C" void* __cdecl FUN_00c8b520(u32);
extern "C" u8    __cdecl FUN_00fefcd0(u32, void**, u8*, u8*);
extern "C" u32   __cdecl FUN_00bb9ae0();
struct spVecF {
    float* mpBegin;                                      // +0x00
    float* mpEnd;                                        // +0x04
    u32    mCap;                                         // +0x08
    u32    mAlloc;                                       // +0x0c
    u32    mExtra;                                       // +0x10

    void* FUN_004aa350(int count, u32* alloc);           // 0x004aa350 (ret 8)  allocate
    void  FUN_0050d4e0(spVecF* src);                     // 0x0050d4e0 (ret 4)  operator=
    void  FUN_00fecc40(void* a, void* b);                // 0x00fecc40 (ret 8)
    void* FUN_00fef570(void* a, void* b);                // 0x00fef570 (ret 8)  our target
};
struct cReqElem {
    u32    mField_00;                                    // +0x00
    u32    mField_04;                                    // +0x04
    spVecF mVec_08;                                      // +0x08
    spVecF mVec_1c;                                      // +0x1c
    u32    mField_30;                                    // +0x30
    u32    mField_34;                                    // +0x34

    cReqElem* FUN_00fef730(cReqElem* src);               // 0x00fef730 (ret 4)  copy-construct
};
struct cBioFunctor {                                     // FUN_00fefe90 argument
    void* FUN_00b8de30();                                // 0x00b8de30
};
struct cSpeciesMgr {
    void* FUN_004e0050();                                // 0x004e0050 (GetSpeciesArchetype)
};
struct IVt0 { virtual void slot0(); virtual void slot1(); };  // refcounted object vtable
// ---- items of slice s00fef140 end

// ---- items of slice s00feff80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
class cGameNounManager_s00fe_ff80;
}
namespace SP {
cGameNounManager_s00fe_ff80* NounManager();                              // 0x00b3d300
}
namespace SP {
class cTerrainSphere_s00fe_ff80 {
public:
    char mPad00[0x1108];
    int32_t mSphereType;      // +0x1108
};
}
namespace SP {
class cGameNounManager_s00fe_ff80 {
public:
    cTerrainSphere_s00fe_ff80* GetCurrentTerrainSphere();    // 0x00f67d90
};
}
namespace SP {
class cRefTarget {
public:
    virtual void AddRef();                 // +0x00
    virtual void Release();                // +0x04
};
}
namespace SP {
class cRefVector {
public:
    void PushBack(cRefTarget* pTarget);    // 0x00aea5d0

    cRefTarget** mpBegin;                  // +0x00
    cRefTarget** mpEnd;                    // +0x04
    cRefTarget** mpCapacity;               // +0x08
};
}
namespace SP {
class cBehavior;
}
namespace SP {
class cCitizenMind;
}
namespace SP {
class cNearNoun {
public:
    const Vec3* GetPosition();             // 0x00c6acc0
};
}
namespace SP {
class cBehaviorManager {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void va();
virtual void vb();
virtual void vc();
virtual void vd();
    virtual void RegisterBehavior(cBehavior* pBehavior);    // +0x38
};
}
namespace SP {
class cCitizen {
public:
virtual void v0();
virtual void v1();
virtual void v2();
    virtual cBehavior* GetBehavior(uint32_t nBehaviorId);   // +0x0c
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void va();
virtual void vb();
virtual void vc();
virtual void vd();
virtual void ve();
virtual void vf();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual void Activate();                                // +0x54

    char mPad58[0xb62 - 0x58];             // +0x058
    uint8_t mFieldB62;                     // +0x0b62
};
}
namespace SP {
class cCitizenMind {
public:
    char mPad00[0x71];
    uint8_t mField71;                      // +0x71
    char mPad72[3];
    uint8_t mField75;                      // +0x75
};
}
namespace SP {
extern Vec3 gCityCentrePosition;                              // 0x016daccc
}
namespace SP {
void* PlanetModel();                                          // 0x00b3d350
}
namespace SP {
void* GetSpawnTuning();                                       // 0x00b3d480
}
namespace SP {
uint32_t RandomUint32Uniform(uint32_t nRange);                // 0x00a68fb0
}
namespace SP {
void GatherSpawnCandidates(cRefVector* pOut, cGameNounManager_s00fe_ff80* pNouns, void* pTuning);
}
namespace SP {
void ShuffleSpawnCandidates(cRefVector* pCandidates);         // 0x00fefec0
}
namespace SP {
cCitizen* CreateCitizen(const Vec3* pPosition, uint32_t nOwner, bool bAdult, void* pParent,
                        int32_t nA, int32_t nB);              // 0x00c099e0
}
namespace SP {
void InitCitizenTool(cCitizen* pCitizen, uint32_t nToolId);    // 0x00c03170
}
namespace SP {
void RegisterCitizen(cCitizen* pCitizen);                      // 0x00acd2d0
}
namespace SP {
void BindCitizenHome(cCitizen* pCitizen, uint32_t nBehaviorId);  // 0x00c1d430
}
namespace SP {
cBehaviorManager* BehaviorManager();                           // 0x00b3d260
}
namespace SP {
void operator delete[](void* pBlock);                          // 0x00f47380
}
namespace SP {
static inline bool IsParkedAtCityCentre(cNearNoun* pNoun)
{
    const Vec3* pPosition = pNoun->GetPosition();
    return pPosition->x == gCityCentrePosition.x && pPosition->y == gCityCentrePosition.y
        && pPosition->z == gCityCentrePosition.z;
}
}
// ---- items of slice s00feff80 end

// @ 0x00fe3b10
bool FUN_00fe3b10(cGalaxyPlanet* pPlanet)
{
    if (GetUniverseContext() == 0) {
        void* pActive = GetActivePlanet();
        if (pPlanet != 0 && pActive == pPlanet)
            return true;
    }
    return false;
}

// @ 0x00fe3b30
bool FUN_00fe3b30(cGalaxyPlanet* pPlanet)
{
    if (SpaceGameGet() == 0)
        return false;
    if (pPlanet == 0)
        return false;
    switch (GetUniverseContext()) {
    case 2:
        return true;
    case 0:
        if (((cGalaxyPlanet*)GetActivePlanet())->mpOwner13c == pPlanet)
            return true;
        return false;
    case 1: {
        int32_t nSystem = ((cStarContext*)FUN_01021230())->mnSystemId;
        if (nSystem == pPlanet->GetSystemId())
            return true;
        return false;
    }
    }
    return false;
}

// @ 0x00fe3b90
bool FUN_00fe3b90(tBadgeVec* pBadges)
{
    tU32Tree* pTree = StarManager()->GetBadgeTree();
    for (tPairNode* p = pTree->begin(); p != pTree->end(); p = (tPairNode*)RBTreeIncrement(&p->mBase)) {
        cBadgeEntry* pEntry = FUN_00c30c60(p->mValue);
        if (pEntry != 0) {
            tBadgeRef ref(pEntry);
            pBadges->push_back(ref);
        }
    }
    return true;
}

// @ 0x00fe68a0
cCachedEventData::cCachedEventData()
{
    mpVtbl  = (void*)0x1494390;
    mHandler = 0;
    mArg08 = 0;
    mArg0c = 0;
    mArg10 = 0;
    mArg14 = 0;

    mPlayerAllyColonyPlanets.mBegin = 0;
    mPlayerAllyColonyPlanets.mEnd = 0;
    mPlayerAllyColonyPlanets.mCapacity = 0;

    mColonizedPlanetList.mBegin = 0;
    mColonizedPlanetList.mEnd = 0;
    mColonizedPlanetList.mCapacity = 0;

    mGrobPlanetList.mBegin = 0;
    mGrobPlanetList.mEnd = 0;
    mGrobPlanetList.mCapacity = 0;

    mHomeworldStarsList.mBegin = 0;
    mHomeworldStarsList.mEnd = 0;
    mHomeworldStarsList.mCapacity = 0;

    mNearbyEmpireStars.mBegin = 0;
    mNearbyEmpireStars.mEnd = 0;
    mNearbyEmpireStars.mCapacity = 0;

    mNearbyKnownEmpireStars.mBegin = 0;
    mNearbyKnownEmpireStars.mEnd = 0;
    mNearbyKnownEmpireStars.mCapacity = 0;

    mNearbyEmpires.mNode2 = 0;
    mNearbyEmpires.mRoot = 0;
    mNearbyEmpires.mSize = 0;
    mNearbyEmpires.mRoot = 0;
    mNearbyEmpires.mSizeByte = 0;
    mNearbyEmpires.mField14 = 0;
    mNearbyEmpires.mNode = &mNearbyEmpires.mNode;
    mNearbyEmpires.mNode2 = &mNearbyEmpires.mNode;

    mLocalEmpires.mNode2 = 0;
    mLocalEmpires.mRoot = 0;
    mLocalEmpires.mSize = 0;
    mLocalEmpires.mRoot = 0;
    mLocalEmpires.mSizeByte = 0;
    mLocalEmpires.mField14 = 0;
    mLocalEmpires.mNode = &mLocalEmpires.mNode;
    mLocalEmpires.mNode2 = &mLocalEmpires.mNode;

    mActiveEmpires.mRoot = 0;
    mActiveEmpires.mSize = 0;
    mActiveEmpires.mNode = &mActiveEmpires.mNode;
    mActiveEmpires.mNode2 = &mActiveEmpires.mNode;
    mActiveEmpires.mRoot = 0;
    mActiveEmpires.mSizeByte = 0;
    mActiveEmpires.mField14 = 0;

    mInactivePlayers.mNode2 = 0;
    mInactivePlayers.mSize = 0;
    mInactivePlayers.mField14 = 0;
    mInactivePlayers.mNode = &mInactivePlayers.mNode;
    mInactivePlayers.mNode2 = &mInactivePlayers.mNode;
    mInactivePlayers.mSize = 0;
    mInactivePlayers.mSizeByte = 0;
    mInactivePlayers.mField18 = 0;

    ((MC*)this)->f_00d01790(0xa);
    ((MC*)&mPlayerAllyColonyPlanets)->f_00d01790(0x14);
    ((MC*)&mHomeworldStarsList)->f_00d01790(0x352);
}

// @ 0x00fe7210
bool cHelper7210::HandleEvent(uint32_t msg, int* arg)
{
    if (msg == 0xcc0bf723u && mbFieldB8 != 0) {
        if (*arg == 2) {
            void* a = FUN_00fd9c60();
            ((MC*)a)->f_00fdf5f0();
        }
        ((MC*)FUN_00b3d380())->f_00b32250(0x7e9e4b7u);

        uint32_t self = (uint32_t)(uintptr_t)this;
        uint32_t handler = (self != 4) ? self : 0;
        mbFieldB8 = 0;

        void* server = FUN_0067dcc0();
        typedef void (__thiscall* Fn)(void*, uint32_t, uint32_t, uint32_t);
        ((Fn)VF(server, 0x2c))(server, handler, 0xcc0bf723u, 0xffffd8f1u);
    }
    return false;
}

// @ 0x00fe72b0
void __cdecl RefreshNumbers_72b0()
{
    void* p = FUN_01021300();
    void* q = ((MC*)p)->f_00c30f90();

    Key key;
    key.a = ((uint32_t*)q)[0];
    key.b = ((uint32_t*)q)[1];
    key.c = ((uint32_t*)q)[2];

    void* prof = ((MC*)FUN_00401090(&key))->f_004df550();
    void* layout = *(void**)((char*)FUN_010666a0() + 0x258);

    float sum = FUN_004d12a0(FUN_00c028b0(prof, 1)) + *(float*)((char*)prof + 0x56c);
    int n = (int)sum;
    if ((float)n < sum)
        n += 1;

    {
        void* w = ((MC*)layout)->f_008105b0(0x797ec68u, 1);
        char buf[0x40];
        FUN_00881ea0((double)n, buf, 0x40, 0);
        ((void(__thiscall*)(void*, void*))VF(w, 0x80))(w, buf);
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x7fdbb88u, 1);
        char buf[0x40];
        FUN_00881ea0((double)*(float*)((char*)prof + 0x66c), buf, 0x40, 0);
        ((void(__thiscall*)(void*, void*))VF(w, 0x80))(w, buf);
    }
}

// @ 0x00fe73c0
void __cdecl RefreshNumbers_73c0()
{
    char buf[0x80];

    void* p = FUN_01021300();
    void* q = ((MC*)p)->f_00c30f90();

    Key key;
    key.a = ((uint32_t*)q)[0];
    key.b = ((uint32_t*)q)[1];
    key.c = ((uint32_t*)q)[2];

    void* prof = ((MC*)FUN_00401090(&key))->f_004df550();
    void* colLayout = FUN_010666a0();

    float f1 = *(float*)((char*)prof + 0x644);
    void* layout = *(void**)((char*)colLayout + 0x258);

    {
        void* w = ((MC*)layout)->f_008105b0(0x7edc860u, 1);
        FUN_00881ea0((double)f1, buf, 0x40, 0);
        ((void(__thiscall*)(void*, void*))VF(w, 0x80))(w, buf);
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x7d0ede8u, 1);
        FUN_00881ea0((double)*(float*)((char*)prof + 0x640), buf, 0x40, 0);
        ((void(__thiscall*)(void*, void*))VF(w, 0x80))(w, buf);
    }
}

// @ 0x00fe74a0
void __cdecl RefreshPips_74a0()
{
    void* p = FUN_01021300();
    void* q = ((MC*)p)->f_00c30f90();

    Key key;
    key.a = ((uint32_t*)q)[0];
    key.b = ((uint32_t*)q)[1];
    key.c = ((uint32_t*)q)[2];

    void* prof = ((MC*)FUN_00401090(&key))->f_004df550();

    int n = *(int*)((char*)prof + 0x668) + *(int*)((char*)prof + 0x664)
          + *(int*)((char*)prof + 0x660) + *(int*)((char*)prof + 0x648);

    void* layout = *(void**)((char*)FUN_010666a0() + 0x258);

    typedef void (__thiscall* Fn)(void*, int, unsigned char);
    {
        void* w = ((MC*)layout)->f_008105b0(0x797f4f3u, 1);
        ((Fn)VF(w, 0x7c))(w, 1, (unsigned char)(n > 0));
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x797f4f2u, 1);
        ((Fn)VF(w, 0x7c))(w, 1, (unsigned char)(n > 1));
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x797f4f1u, 1);
        ((Fn)VF(w, 0x7c))(w, 1, (unsigned char)(n > 2));
    }
    {
        void* w = ((MC*)layout)->f_008105b0(0x797f4f0u, 1);
        ((Fn)VF(w, 0x7c))(w, 1, (unsigned char)(n > 3));
    }
}

// @ 0x00fe7590
void __cdecl ForwardWindowMessage_7590(uint32_t a1, uint32_t a2)
{
    void* w = ((MC*)*(void**)((char*)FUN_010666a0() + 0x224))->f_00e012b0(0x7bb7790u);
    if (w != 0) {
        void* o = ((void*(__thiscall*)(void*, uint32_t))VF(w, 0xc))(w, 0x8ed27e7au);
        if (o != 0)
            ((void(__thiscall*)(void*, uint32_t, uint32_t))VF(o, 0x28))(o, a1, a2);
    }
}

// @ 0x00fe75d0
cSimOwner::cSimOwner()
{
    mpVtbl2  = (void*)0x13eb384;
    mpVtbl   = (void*)0x14943d0;
    mpVtbl2  = (void*)0x14943c0;
    mField08 = 0;
    ((MC*)((char*)this + 0x10))->f_0093a560(0, 0);
    mbField28 = 0;
    mpField2c = 0;
    ((MC*)((char*)this + 0x30))->f_00f13890();
    mbFieldBC = 0;
    ((MC*)((char*)this + 0x10))->f_0093a1a0(4);

    cSimOwner* p = (cSimOwner*)operator_new_sp(0x5c, "Simulator", 0, 0, 0, 0);
    if (p == 0)
        p = 0;
    else
        p = (cSimOwner*)((MC*)p)->f_00f13810();

    cSimOwner* old = mpField2c;
    if (p != old) {
        if (p != 0) {
            cSimOwner* o = (cSimOwner*)((char*)p + 4);
            ((void(__thiscall*)(void*))VF(o, 4))(o);
        }
        mpField2c = p;
        if (old != 0) {
            cSimOwner* o = (cSimOwner*)((char*)old + 4);
            ((void(__thiscall*)(void*))VF(o, 8))(o);
        }
    }
}

// @ 0x00fe7680
void* cSimOwner::Destroy(int flags)
{
    mpVtbl  = (void*)0x14943d0;
    mpVtbl2 = (void*)0x14943c0;
    ((MC*)((char*)this + 0x30))->f_00f138c0();
    if (mpField2c != 0) {
        cSimOwner* o = (cSimOwner*)((char*)mpField2c + 4);
        ((void(__thiscall*)(void*))VF(o, 8))(o);
    }
    mpVtbl2 = (void*)0x13eb394;
    mpVtbl  = (void*)0x13eb938;
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00fe76d0
void CBr::f76d0(int p)
{
    void* o = FUN_010666a0();
    Layout* lay = (Layout*)*(void**)((char*)o + 0x258);
    IWinL* w0 = (IWinL*)lay->FindWindowByID(0x7550880, 1);
    if (w0 == 0)
        return;
    IWinL* w1 = (IWinL*)lay->FindWindowByID(0x7550881, 1);
    if (w1 == 0)
        return;

    FUN_00fe7590(4, 1);

    if (p == 1) {
        w0->a7c(1, 1);
        w1->a7c(1, 0);
        IWinL* w2 = (IWinL*)lay->FindWindowByID(0x7551618, 1);
        if (w2 != 0)
            w2->a7c(1, 0);
        ((Fns*)f2c)->f16fd0();
        return;
    }

    w0->a7c(1, 0);
    w1->a7c(1, 1);
    IWinL* w2 = (IWinL*)lay->FindWindowByID(0x7551618, 1);
    if (w2 != 0)
        w2->a7c(1, 1);

    unsigned* empire = (unsigned*)((Fns*)FUN_01021300())->c30f90();

    IWinL* wA = (IWinL*)lay->FindWindowByID(0x7cf6498, 1);
    if (wA != 0) {
        unsigned char* ed = (unsigned char*)*(void**)((char*)DAT_016c7aa4 + 0x7c);
        *(unsigned*)(ed + 0x14) = empire[0];
        *(unsigned*)(ed + 0x18) = empire[1];
        *(unsigned*)(ed + 0x1c) = empire[2];
        *(unsigned*)(ed + 0x20) = 0xffffffffu;
        char s1[0x1c];
        char s2[0x1c];
        ((Fns*)s1)->g6b5770(0x623d2fc0, 0x7ceb16a, 0);
        ((Fns*)s2)->g6b5770(0x623d2fc0, 0x7ceb16b, 0);
        wA->a80(((Fns*)s1)->g6b55c0());
        ((Fns*)s2)->g6b5240();
        ((Fns*)s1)->g6b5240();
    }

    IWinL* wTool = (IWinL*)lay->FindWindowByID(0x755e358, 1);

    void* prop = 0;
    FUN_005bf0e0(empire, &prop);
    unsigned out1 = 0;
    FUN_00410370(prop, 0x5888ef41, &out1);
    unsigned out2 = 0;
    FUN_00410370(prop, 0xcf837237, &out2);
    int count = (int)FUN_00eec580((int)(out1 + 1));

    wchar_t buf[0x20];
    IWinL* wB = (IWinL*)lay->FindWindowByID(0x7cd1550, 1);
    if (wB != 0) {
        FUN_00881ae0((int)out1, (int)out1 >> 31, buf, 0x20);
        wB->a80(buf);
    }
    FUN_00881ae0((int)out2, (int)out2 >> 31, buf, 0x20);
    char cstr[0x1c];
    FUN_00eb96a0(cstr, &DAT_01488848, buf);
    FUN_00881ae0(count, count >> 31, buf, 0x20);
    ((Fns*)cstr)->g6ec1c0(buf);
    FUN_00806de0(wTool, *(void**)cstr, -1, 1);
    FUN_00807c70(wTool, lay, 0x7d10de0 + (int)out1, 0xffffffff);

    IWinL* wC = (IWinL*)lay->FindWindowByID(0x7cf8048, 1);
    if (wC != 0) {
        float hi = (float)count - DAT_01485720;
        float lo = (float)(int)FUN_00eec580((int)out1);
        float base = (lo < hi) ? lo : hi;
        float frac = ((float)(int)out2 - base) / ((float)count - base);
        float t = (frac > DAT_01485720) ? DAT_01485720 : frac;
        float* pv = wC->a38();
        float vals[4];
        vals[0] = pv[0];
        vals[1] = pv[1];
        vals[2] = pv[2];
        vals[3] = pv[3];
        void* o2 = FUN_010666a0();
        vals[3] = (*(float*)((char*)o2 + 0x690) - vals[1]) * (DAT_01485720 - t) + vals[1];
        wC->a6c(vals);
    }

    IWinL* wD = (IWinL*)lay->FindWindowByID(0x7cc9018, 1);
    if (wD != 0) {
        unsigned* emp = (unsigned*)((Fns*)FUN_01021300())->c30f90();
        unsigned v[3];
        v[0] = emp[0];
        v[1] = emp[1];
        v[2] = emp[2];
        ((Fns*)f2c)->f17b00(v);
    }
    ((Fns*)this)->f16fd0();
    FUN_00fe72b0();
    FUN_00fe73c0();
    FUN_00fe74a0();

    IWinL* wE = (IWinL*)lay->FindWindowByID(0x7cded28, 1);
    if (wE != 0) {
        IWinL* wF = (IWinL*)lay->FindWindowByID(0x7cded29, 1);
        if (wF != 0) {
            if (p == 0) {
                wF->a7c(1, 1);
                wE->a7c(1, 0);
            } else {
                wF->a7c(1, 0);
                wE->a7c(1, 1);
            }
        }
    }
}

// @ 0x00fe7b80
void* CBr::f7b80()
{
    void* mem = FUN_00f473a0(0x9c, DAT_013ebc58, 0, 0, 0, 0);
    void* obj = 0;
    if (mem != 0) {
        obj = ((Fns*)mem)->g5a9080();
        if (obj != 0)
            ((NewObj*)obj)->n04();
    }

    unsigned* e = (unsigned*)((Fns*)FUN_01021300())->c30f90();
    unsigned* od = (unsigned*)obj;
    od[4] = e[0];
    od[5] = e[1];
    od[6] = e[2];
    od[3] = 0xa56567f7u;

    void* r = *(void**)((char*)obj + 0x94);
    if (r != 0) {
        *(void**)((char*)obj + 0x94) = 0;
        void** vt = *(void***)r;
        ((void(*)(void))vt[1])();
    }
    od[9]  = DAT_015da7c4;
    od[10] = DAT_015da7c8;
    od[0xb] = DAT_015da7cc;
    od[0xc] = DAT_015da7d0;
    *(unsigned char*)((char*)obj + 0x35) = 0;
    *(unsigned char*)((char*)obj + 0x34) = 0;
    *(unsigned char*)((char*)obj + 0x36) = 0;
    *(unsigned char*)((char*)obj + 0x38) = 0;
    *(unsigned char*)((char*)obj + 0x37) = 0;
    *(unsigned char*)((char*)obj + 0x39) = 0;
    *(unsigned char*)((char*)obj + 0x3c) = 1;
    *(unsigned char*)((char*)obj + 0x6d) = 1;

    void* ts = ((Fns*)FUN_00b3d300())->f67d90();
    if (ts != 0) {
        SimpleVec* v = (SimpleVec*)((char*)obj + 0x70);
        vecPush(v, *(unsigned*)((char*)ts + 0x10fc));
        vecPush(v, *(unsigned*)((char*)ts + 0x1100));
        vecPush(v, *(unsigned*)((char*)ts + 0x1104));
        vecPush(v, *(unsigned*)((char*)ts + 0x1108));
        vecPush(v, *(unsigned*)((char*)ts + 0x110c));
    }
    *(unsigned*)((char*)obj + 0x90) = f08;
    *(unsigned char*)((char*)obj + 0x3d) = 1;
    *(unsigned char*)((char*)obj + 0x64) = 1;

    ((Fns*)FUN_00b3d320())->gb1dee0(obj);
    return ((NewObj*)obj)->n08();
}

// @ 0x00fe7d70
void CBr::f7d70()
{
    void* o = FUN_010666a0();
    Layout* lay = (Layout*)*(void**)((char*)o + 0x258);
    IWinL* w = (IWinL*)lay->FindWindowByID(0x755f180, 1);
    if (w != 0)
        w->a7c(1, 0);

    ((Fns*)FUN_010666a0())->f1067f60(0);
    ((Fns*)FUN_00b3d490())->ae8ea0();
    f76d0(1);

    IWinG* w2 = (IWinG*)((GlobUI*)*(void**)((char*)FUN_010666a0() + 0x224))->FindWindowByID(0x7bb7790);
    if (w2 != 0) {
        IWinG* x = (IWinG*)w2->a0c(0x8ed27e7a);
        if (x != 0)
            x->a28(4, 0);
    }
    ((Fns*)FUN_00b3d380())->b32250(0x7e9e4b7);
}

// @ 0x00fe7e10
void CBr::f7e10()
{
    f7d70();

    IWinG* w = (IWinG*)((GlobUI*)*(void**)((char*)FUN_010666a0() + 0x224))->FindWindowByID(0x7bb7790);
    if (w != 0) {
        IWinG* x = (IWinG*)w->a0c(0x8ed27e7a);
        if (x != 0)
            x->a28(4, 0);
    }
    f28 = 0;
}

// @ 0x00fe7e60
char CBr::f7e60(unsigned p2, void** msg)
{
    (void)p2;
    void* o = FUN_010666a0();
    Layout* lay = (Layout*)*(void**)((char*)o + 0x258);
    unsigned m2 = (unsigned)msg[2];

    if (m2 == 0x287259f6u) {
        unsigned id = ((MsgObj*)*msg)->m1c();
        f08 = id;

        switch (id) {
        case 0x755e358: {
            IWinL* w1 = (IWinL*)lay->FindWindowByID(0x7cccbd0, 1);
            if (w1 == 0)
                break;
            IWinL* w2 = (IWinL*)lay->FindWindowByID(0x7cc9000, 1);
            if (w2 == 0)
                break;
            char b1 = (char)(w1->a28() & 1);
            char b2 = (char)(w2->a28() & 1);
            if ((b1 ^ b2) == 0)
                break;
            if (b1 != 0) {
                w1->a7c(1, 0);
                w2->a7c(1, 1);
                break;
            }
            w1->a7c(1, 1);
            w2->a7c(1, 0);
            void* self30 = (char*)this + 0x30;
            ((Fns*)self30)->f16260();
            ((Fns*)self30)->f14980();
            IWinL* w3 = (IWinL*)lay->FindWindowByID(0x7da1928, 1);
            if (w3 != 0)
                ((Fns*)self30)->f120c0(w3);
            unsigned* emp = (unsigned*)((Fns*)FUN_01021300())->c30f90();
            unsigned v[3];
            v[0] = emp[0];
            v[1] = emp[1];
            v[2] = emp[2];
            ((Fns*)self30)->f150d0(v);
            break;
        }
        case 0x5e4f788: {
            f7d70();
            void* planet = FUN_010212a0();
            if (planet == 0)
                break;
            void* x = ((Fns*)planet)->b8d9b0();
            if (x == 0)
                break;
            ((Fns*)FUN_00b3d380())->b32220(0x7e9e4b7);
            unsigned ctx[3];
            ctx[0] = (unsigned)x;
            ctx[1] = 0x366a930du;
            ctx[2] = DAT_015b444c;
            fbc = 1;
            ((MsgSrv*)SP_MessageServer())->v20((char*)this + 4, 0xcc0bf723);
            void* ec = *(void**)((char*)DAT_016c7aa4 + 0x1c);
            char r = ((Fns*)ec)->ec5a60(ctx, 0, 0);
            if (r != 0)
                break;
            fbc = 0;
            ((MsgSrv*)SP_MessageServer())->v2c((char*)this + 4, 0xcc0bf723, 0xffffd8f1);
            ((Fns*)FUN_00b3d380())->b32250(0x7e9e4b7);
            break;
        }
        case 0x5e4f770:
        case 0x75dd100: {
            f7d70();
            AppV* app = (AppV*)SP_App();
            void* c = app->a50();
            void* ic = EA_COM_interface_cast(((AppCam*)c)->c38());
            ((AppCam*)ic)->c64(1);
            break;
        }
        case 0x7ce1750:
        case 0x7ce3cb0:
            f7d70();
            f7b80();
            break;
        case 0x770996a:
            f76d0(1);
            break;
        case 0x7bb9fc8:
            f7d70();
            FUN_00fe7590(4, 0);
            f28 = 0;
            break;
        case 0x75dd108: {
            f76d0(2);
            void* s = FUN_01021300();
            AedV* g = (AedV*)FUN_00aed4d0();
            unsigned l1, l2;
            g->a28(0x55125425u, *(unsigned*)((char*)s + 0x58), &l1, &l2);
            ((Fns*)FUN_00b3d490())->ae7e10(l1, l2, 0, 1);
            break;
        }
        default:
            break;
        }
        return 0;
    }

    if (m2 == 0x0cu) {
        void* self2c = *(void**)((char*)this + 0x2c);
        ((Fns*)self2c)->f12680(0x14);
        if (*(unsigned*)((char*)this + 0x10) == 0 && *(unsigned*)((char*)this + 0x14) == 0)
            return 0;
        long long ticks = ((Fns*)((char*)this + 0x10))->g93a3a0();
        double elapsed = (double)ticks * (double)f24;
        if (elapsed <= (double)DAT_01477fbc)
            return 0;
        ((Fns*)((char*)this + 0x10))->g93a2e0();
        IWinL* w = (IWinL*)lay->FindWindowByID(0x7551618, 1);
        if (w != 0)
            w->a7c(1, 1);
    }
    return 0;
}

// @ 0x00fe8260
float f8260(const Brush* p, float p1, float p2, float p3)
{
    float sa = sinf(p1);
    float ca = cosf(p1);
    float sb = sinf(p2);
    float cb = cosf(p2);

    float t1 = sqrtf((DAT_01485720 - p->f3c) /
                     (DAT_01485720 - (p->f3c * cb) * cb)) * p->f24;
    float x1 = t1 * sb;
    float t2 = sqrtf((DAT_01485720 - p->f3c) /
                     (DAT_01485720 - (p->f3c * ca) * ca)) * p->f24;
    float x2 = t2 * sa;

    float d = (t2 * ca) * x1 - (t1 * cb) * x2;

    float a = ((p->f28 - p->f30) * (ca * sa - cb * sb) +
               (p->f28 + p->f30) * (p1 - p2)) * DAT_013eb8a0;
    float b = ((x2 - x1) * p->f34 + d) * DAT_01471064;

    return (fabsf(a) - fabsf(d) * DAT_01471064) + fabsf(b) -
           (p->f40 / p->f20) * fabsf(p3);
}

// @ 0x00fe8380
int f8380(float* value, const Brush* p, float p1, float p2)
{
    for (int i = 0; i < 10; i++) {
        float delta = (p2 < 0.0f) ? DAT_013ef56c : DAT_013f9428;
        float v = *value;
        float f1 = f8260(p, v, p1, p2);
        float f2 = f8260(p, v + delta, p1, p2);
        float step = f1 / ((f2 - f1) / delta);
        *value = v - step;
        if (fabsf(step) < DAT_013f89bc)
            return 1;
    }
    return 0;
}

// @ 0x00fe8450
void Brush::f8450()
{
    if (b00 != 0)
        return;

    float v10 = f10;
    f3c = v10 * v10;

    float mag = sqrtf(f14 * f14 + f18 * f18 + f1c * f1c);
    float r   = mag / (DAT_01485720 - v10);
    f24 = r;

    float r2 = r * r;
    float rv = r * v10;
    f34 = rv;
    f38 = rv * rv;
    f28 = r2;

    float side = sqrtf(r2 - rv * rv);
    f2c = side;
    f30 = side * side;
    f40 = (side * side + r2) * DAT_015b44f8;

    float inv = DAT_01485720 / mag;
    float nx = f14 * inv;
    float ny = f18 * inv;
    float nz = f1c * inv;
    f44 = nx;
    f48 = ny;
    f4c = nz;

    f50 = f4c * f08 - f48 * f0c;
    f54 = f44 * f0c - f04 * f4c;
    f58 = f04 * f48 - f44 * f08;

    float q = f34;
    f5c = q * (f14 * inv);
    f60 = q * (f18 * inv);
    f64 = q * (f1c * inv);
}

// @ 0x00fe8630
static NOINLINE float Brush_f8630(Brush_s00fe_8630* self, const float* addend)
{
    float d[3];
    d[0] = self->f5c + addend[0];
    d[1] = self->f60 + addend[1];
    d[2] = self->f64 + addend[2];
    float inv = 1.0f / sqrtf(d[0] * d[0] + (d[1] * d[1] + d[2] * d[2]));
    d[0] = d[0] * inv;
    d[1] = d[1] * inv;
    d[2] = d[2] * inv;
    return RaySphereIntersect(&self->f44, d, &self->f04);
}

// @ 0x00fe86d0
static NOINLINE float* Brush_f86d0(Brush_s00fe_8630* self, float angle, float* out)
{
    float ca = cosf(angle);
    float t = sqrtf((1.0f - self->f3c) /
                    (1.0f - (self->f3c * ca) * ca)) * self->f24;
    float sa = sinf(angle);
    float a = t * ca;
    float b = t * sa;
    out[0] = (self->f50 * b + self->f44 * a) - self->f5c;
    out[1] = (self->f54 * b + self->f48 * a) - self->f60;
    out[2] = (self->f58 * b + self->f4c * a) - self->f64;
    return out;
}

// @ 0x00fe8780
float* Brush_f8780(float* out, const float* src, const float* add, Brush_s00fe_8630* self, float angle)
{
    if (self->b00 != 0) {
        out[0] = src[0];
        out[1] = src[1];
        out[2] = src[2];
        return out;
    }
    float diff[3];
    diff[0] = src[0] - add[0];
    diff[1] = src[1] - add[1];
    diff[2] = src[2] - add[2];
    float t = Brush_f8630(self, diff);
    if (f8380(&t, self, angle, 0)) {
        float tmp[3];
        Brush_f86d0(self, t, tmp);
        out[0] = tmp[0] + add[0];
        out[1] = tmp[1] + add[1];
        out[2] = tmp[2] + add[2];
        return out;
    }
    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    return out;
}

// @ 0x00fe8880
char Brush_s00fe_8630::ReadBrush(void* stream)
{
    VarListSerializer ser;
    ser.ctor(this, 0x015b4568, 0x01a80d26);
    char ok = ser.Read(stream);
    if (ok != 0)
        DeriveFields();
    return ok;
}

// @ 0x00fe88d0
void Brush_f88d0(Brush_s00fe_8630* self, SpVectorV3* out, int count)
{
    out->resize(count);
    float step = self->f20 / (float)count;
    u32 v[3];
    v[0] = *(u32*)&self->f14;
    v[1] = *(u32*)&self->f18;
    v[2] = *(u32*)&self->f1c;
    if (count > 0) {
        int off = 0;
        int remaining = count;
        do {
            u32* dst = (u32*)(out->mpBegin + off);
            dst[0] = v[0];
            dst[1] = v[1];
            dst[2] = v[2];
            u32 scratch[3];
            u32* r = (u32*)Brush_f8780((float*)scratch, (const float*)v,
                                       (const float*)0x016dab58, self, step);
            v[0] = r[0];
            v[1] = r[1];
            v[2] = r[2];
            off += 0xc;
            remaining--;
        } while (remaining != 0);
    }
}

// @ 0x00fe8990
bool GrowthState::ShouldGrow()
{
    TriggerMgr* mgr = (TriggerMgr*)GetTriggerMgr();
    int mode = mgr->mode;
    if (mode == 1)
        return true;
    if (mode == 2)
        return true;
    bool result;
    if (b48 != 0 || b49 != 0) {
        result = true;
        void* game = SP_SpaceGameGet();
        if (game != 0) {
            void* tribe = ((GameNounMgr*)game)->GetPlayerTribe();
            result = ((TribeState*)tribe)->GetStage() < 2u;
            if (!result) {
                b48 = 0;
                b49 = 0;
            }
        }
    } else {
        result = false;
    }
    return result;
}

// @ 0x00feb050
void* __fastcall FUN_00feb050(VtableHolder* self)
{
    self->mpVtable = (void*)0x014948a4;
    self->mpField4 = 0;
    return self;
}

// @ 0x00fef810
void* FUN_00fef810(cReqElem* a, cReqElem* b, cReqElem* d)
{
    while (b != a) {
        b = (cReqElem*)((u8*)b - 0x38);
        d = (cReqElem*)((u8*)d - 0x38);
        d->mField_00 = b->mField_00;
        d->mField_04 = b->mField_04;
        d->mVec_08.FUN_0050d4e0(&b->mVec_08);
        d->mVec_1c.FUN_0050d4e0(&b->mVec_1c);
        d->mField_30 = b->mField_30;
        d->mField_34 = b->mField_34;
    }
    return d;
}

// @ 0x00fefcd0
__declspec(noinline) u8 FUN_00fefcd0(u32 param1, void** param2, u8* param3, u8* param4)
{
    if (param3 != 0)
        *param3 = 0;
    if (param4 != 0)
        *param4 = 0;

    void* u = FUN_00b8de30();
    (void)u;
    char g = (char)(u32)FUN_00c8b450(param1);
    if (g == 0)
        return 0;
    char s = (char)(u32)FUN_00c8b520(param1);
    if (s == 0)
        return 0;
    int i = (int)(u32)FUN_00bb9ae0();
    if (i >= 2)
        return 0;
    return 0;
}

// @ 0x00fefe70
void FUN_00fefe70(u32 param1)
{
    FUN_00fefcd0(param1, 0, 0, 0);
}

// @ 0x00fefe90
void FUN_00fefe90(u32 param1, u32 param2, u32 param3)
{
    u32 buf[1];
    void* r = ((cBioFunctor*)param1)->FUN_00b8de30();
    buf[0] = param1;
    FUN_00fefcd0((u32)r, (void**)buf, (u8*)param2, (u8*)param3);
}

// @ 0x00fefec0
void FUN_00fefec0(void** vec)
{
    u32 i = 0;
    while (i < (u32)((int)((u8*)vec[1] - (u8*)vec[0]) >> 2)) {
        u32 off = i * 4;
        u8* el = *(u8**)((u8*)vec[0] + off);
        void* s = FUN_00401090(*(void**)(el + 0x88), *(void**)(el + 0xf0));
        void* sp = ((cSpeciesMgr*)s)->FUN_004e0050();
        if (sp == 0 || *(u8*)((u8*)sp + 0x388) == 0) {
            ++i;
        } else {
            u8* base = (u8*)vec[0];
            IVt0* cur = *(IVt0**)(base + off);
            IVt0* last = *(IVt0**)((u8*)vec[1] - 4);
            if (last != cur) {
                if (last != 0)
                    last->slot0();
                *(IVt0**)(base + off) = last;
                if (cur != 0)
                    cur->slot1();
            }
            vec[1] = (void*)((u8*)vec[1] - 4);
            IVt0* e2 = *(IVt0**)vec[1];
            if (e2 != 0)
                e2->slot1();
        }
    }
}

// @ 0x00feff80
namespace SP {
void sSpawnTribesmen(uint32_t nOwner, int nCount, int nMinSlot, int nMaxSlot, uint32_t nToolId, uint32_t nBehaviorId, cRefVector* pTargets)
{
    PlanetModel();
    cGameNounManager_s00fe_ff80* pNouns = NounManager();
    void* pTuning = GetSpawnTuning();
    int32_t nSpawned = 0;

    cRefVector candidates;
    GatherSpawnCandidates(&candidates, pNouns, pTuning);
    ShuffleSpawnCandidates(&candidates);

    while (candidates.mpBegin != candidates.mpEnd && nSpawned < nCount) {
        int32_t nWant = (int32_t)RandomUint32Uniform((uint32_t)((nMaxSlot - nMinSlot) + 1)) + nMinSlot;
        int32_t nLeft = nCount - nSpawned;
        int32_t nPicks = nWant < nLeft ? nWant : nLeft;
        cRefTarget* pPick = 0;

        // drop candidates off the back of the list until the drawn one may stay
        while (candidates.mpBegin != candidates.mpEnd) {
            if (pPick != 0 && !IsParkedAtCityCentre((cNearNoun*)pPick))
                break;
            cRefTarget* pTail = *--candidates.mpEnd;
            int32_t nSlots = (int32_t)(candidates.mpEnd - candidates.mpBegin);
            int32_t nSlot = (int32_t)RandomUint32Uniform((uint32_t)nSlots);
            cRefTarget* pOld = candidates.mpBegin[nSlot];
            pPick = pTail;
            if (pTail != pOld) {
                if (pTail != 0)
                    pTail->AddRef();
                candidates.mpBegin[nSlot] = pTail;
                if (pOld != 0)
                    pOld->Release();
            }
            cRefTarget* pDropped = *candidates.mpEnd;
            if (pDropped != 0)
                pDropped->Release();
        }
        if (pPick == 0) {
            GatherSpawnCandidates(&candidates, pNouns, pTuning);
            ShuffleSpawnCandidates(&candidates);
            continue;
        }

        // hand the pick over to the target list
        pPick->AddRef();
        pTargets->PushBack(pPick);
        pPick->Release();

        for (int32_t i = 0; i < nPicks; ++i) {
            Vec3 position = *((cNearNoun*)pPick)->GetPosition();
            bool bAdult = RandomUint32Uniform(10) >= 2;
            cCitizen* pCitizen = CreateCitizen(&position, nOwner, bAdult, pPick, 0, 1);
            if (pCitizen != 0) {
                InitCitizenTool(pCitizen, nToolId);
                RegisterCitizen(pCitizen);
                pCitizen->mFieldB62 = 1;
                BindCitizenHome(pCitizen, nBehaviorId);
                ++nSpawned;
                BehaviorManager()->RegisterBehavior(pCitizen->GetBehavior(0x11c0ba3));
                cCitizenMind* pMind = (cCitizenMind*)pCitizen->GetBehavior(0x116dd1b);
                if (pMind != 0) {
                    pMind->mField71 = 0;
                    pMind->mField75 = 1;
                }
                pCitizen->Activate();
            }
        }
    }

    for (cRefTarget** ppRef = candidates.mpBegin; ppRef != candidates.mpEnd; ++ppRef) {
        if (*ppRef != 0)
            (*ppRef)->Release();
    }
    if (candidates.mpBegin != 0)
        operator delete[](candidates.mpBegin);
}
}  // namespace SP
