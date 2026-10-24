// src/game/SPGonzago/SPTribeDisplayStrategy.cpp -- migrated from slice(s) s00ccd050, s00ccaff0, s00cc9e20, s00cc8ed0, s00cc7fa0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeDisplayStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cReservationGrid.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "cSPUILayout.h"
#include <math.h>
#include "SP/cTribe.h"

// ---- items of slice s00cc7fa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
struct ModelInstanceSet {
    u8 mData[0x60];
    void AddToRenderer(void* p); // 0x006f3df0
    void ReleaseIf();            // 0x006f33d0
};
struct CameraCtl {
    u8 mPad00[0x14]; // +0x00
    u8 m14;          // +0x14
    u8 m15;          // +0x15
    u8 m16;          // +0x16
    u8 m17;          // +0x17

    bool FUN_00cc87f0();
    bool FUN_00cc8810();
};
struct Citizen8a30 {
    void* GetTribe(int zero); // 0x00c22f50
};
struct GlobalUI8aa0 {
    void* FindWindowByID(u32 id); // 0x00e012b0
};
struct Vec3u {
    u32 x;
    u32 y;
    u32 z;
};
struct TribeStrategy {
    u8 mPad00[0x08];        // +0x000
    void* mChild[6];        // +0x008
    u8 mPad20[0x4c - 0x20]; // +0x020
    GlobalUI8aa0* m4C;      // +0x04c
    u8 mPad50[0x88 - 0x50]; // +0x050
    Vec3u mVec;             // +0x088
    u8 mPad94[0xb8 - 0x94]; // +0x094
    ModelInstanceSet mInst[2]; // +0x0b8
    u32 mArray178[0x28];    // +0x178
    u32 mArray218[0x28];    // +0x218

    u32 FUN_00cc88e0(u32 key);                // 0x00cc88e0
    void FUN_00cc8940(bool add);              // 0x00cc8940
    u32 FUN_00cc89f0(bool first);             // 0x00cc89f0
    void FUN_00cc8a30(void* pose, Citizen8a30* citizen); // 0x00cc8a30
    void FUN_00cc8aa0(bool show);             // 0x00cc8aa0
    void FUN_00cc8ba0();                      // 0x00cc8ba0
};
// ---- items of slice s00cc7fa0 end

// ---- items of slice s00cc8ed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace SP {
namespace cTribeModeStrategy {
    void* Instance();                                  // 0x00cd40b0
}
}
struct IntVec {                                 // 8-byte range stored inside a posse
    int32_t mBegin;                             // +0x00
    int32_t mEnd;                               // +0x04
    uint32_t Size() const { return (uint32_t)((mEnd - mBegin) >> 3); }
};
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Vector4 {
    float x, y, z, w;
};
struct PosseItem;                               // SP::cSPUIPosseItem (what FindItem returns)
struct Posse {                                  // SP::cSPUIPosse (UI item container)
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38)
    virtual Vector4* pv39(Vector4* out);        // +0x9c  bounds of the posse contents
    PV(40)
    virtual void pv41(PosseItem* item);         // +0xa4  append the item to the posse
    virtual void* pv42(void* item, int flag);   // +0xa8  add the item to the posse
    PV(43) PV(44) PV(45) PV(46) PV(47)
    virtual void pv48(int value);               // +0xc0  broadcast the value to the items

    uint8_t  mPad04[0xa4 - 0x04];
    IntVec   mVec;                              // +0xa4  item range

    void* FindItem(void* key);                  // 0x00e24c90
    uint32_t GetSystem();                       // 0x00e23250 (EA::Audio::GetSystem in the PDB map)
    void FUN_00e21960();                        // 0x00e21960
    void FUN_00e21980();                        // 0x00e21980
};
struct PosseItem {                              // SP::cSPUIPosseItem
    virtual void pv0();                         // +0x00
    virtual void pv1();                         // +0x04
    PV(2)
    virtual PosseItem* pv3(int tag);            // +0x0c  state object for a tag
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31)
    virtual void pv32(uint32_t id, float value, int first, int second);  // +0x80
    virtual void pv33(int visible, int mode);                           // +0x84
    virtual void pv34(void* arg);                                       // +0x88
    PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
    virtual void pv46(int value);               // +0xb8  set the item state
    virtual int  pv47();                        // +0xbc  query the item state

    void FUN_00e235e0(int value);               // 0x00e235e0  apply the item's tribe state
};
struct EntityRef {                              // entity/tribe handle passed to the strategy
    PV(0) PV(1) PV(2)
    virtual void* pv3(uint32_t tag);            // +0x0c

    char FUN_00c0b770();                        // 0x00c0b770
    int  FUN_00c22dc0();                        // 0x00c22dc0
};
struct UiIface {                                // generic UI interface (vtable-only view)
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30)
    virtual void pv31(int mode, int value);     // +0x7c
};
struct IWinTextSub {                            // sub-object embedded at IWinText+0x34
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10)
    virtual Vector3* pv11();                    // +0x2c  current world position
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42)
    virtual void* pv43();                       // +0xac  icon target drawn for this window
};
struct IWinText {                               // EA::UTFWinControls::IWinText (icon handle)
    PV(0)
    virtual void pv1();                         // vtable +0x04
    uint8_t    mPad04[0x34 - 0x04];
    IWinTextSub mSub34;                         // +0x34
};
struct AutoRef {                                // EA::AutoRefCount<IWinText>
    IWinText* mPtr;                             // +0x00

    AutoRef& operator=(IWinText* p) {           // 0x00b5f950 (inlined at the icon sites)
        if (p != mPtr) {
            IWinText* old = mPtr;
            p->pv0();
            mPtr = p;
            if (old != 0) {
                old->pv1();
            }
        }
        return *this;
    }
};
struct IconDef {                                // 0x24-byte icon description handed to AddIcon
    uint32_t mColor;                            // +0x00
    Vector3  mPos;                              // +0x04
    int32_t  mKind;                             // +0x10  icon kind flags
    AutoRef  mOwner;                            // +0x14  reference held on the icon handle
    float    mRadius;                           // +0x18
    int32_t  mExtra1C;                          // +0x1c
    int32_t  mExtra20;                          // +0x20
};
struct Gfx70 {                                  // object stored at strategy+0x70
    uint8_t  mPad00[0x04];
    UiIface  mSub04;                            // +0x04  embedded sub-object

    void RemoveIcon(void* entity, int a, int b);                // 0x00e0f9c0
    void AddIcon(void* entity, IconDef* def, int a, int b);     // 0x00e10580
    int8_t FUN_00e0df70(IWinText* entity, Vector3* pos, int zero);  // 0x00e0df70
};
uint32_t FUN_0067ac80(int a, int b, int c, int d);              // 0x0067ac80 EA::Color::PackARGB
struct GlobalUI {                               // SP::cSPUIGlobalUI
    void SetVisibility(int visible);            // 0x00e01350
    void* GetBuffer();                          // 0x0093b6c0  the UI layout object
};
struct Iface2B8 {                               // object stored at strategy+0x2b8
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual void pv8(int value);                // +0x20
    PV(9)
    PV(10)
    virtual void pv11(int visible);             // +0x2c
    PV(12) PV(13) PV(14)
    virtual void* pv15();                       // +0x3c  animation target handle
};
struct Ornament {                               // SP::cInteractiveOrnament
    uint8_t mPad00[0x34];
    IWinTextSub mSub34;                         // +0x34  embedded sub-object (slot +0xac)
    uint8_t mPad38[0x240 - 0x38];
    int32_t mField240;                          // +0x240  countdown/value used to pick an ornament

    void Update(int value);                     // 0x00c408f0
};
struct Sub120 {                                 // embedded sub-object at TribeObj+0x120
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10)
    virtual Vector3* pv11();                    // +0x2c  position of the embedded window
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21)
    virtual int8_t pv22();                      // +0x58  ornament set selector
};
struct TribeObj {                               // object passed to FUN_00cc98e0
    uint8_t mPad00[0x120];
    Sub120  m120;                               // +0x120
    uint8_t mPad124[0x234 - 0x124];
    int32_t m234;                               // +0x234  passed to FUN_00b6f0c0

    uint8_t FUN_00c905a0();                     // 0x00c905a0
};
struct IconTarget {                             // object returned by the ornament's slot +0xac
    uint8_t mPad00[0x04];
    int32_t mFlags;                             // +0x04
    uint8_t mPad08[0x4c - 0x08];
    Vector3 mPos;                               // +0x4c
};
Vector3* FUN_00b6f0c0(int arg);                 // 0x00b6f0c0
Ornament* __stdcall FUN_00cc98e0(TribeObj* obj);
struct TribeStrategy_s00cc_8ed0 {                          // the UI strategy object of this slice
    uint32_t mVt;                               // +0x000
    uint8_t  mPad04[0x08 - 0x04];
    Posse*   mChild[6];                         // +0x008 .. +0x01c  six posse slots
    uint8_t  mPad20[0x4c - 0x20];
    GlobalUI* m4C;                              // +0x04c  global UI
    uint8_t  mPad50[0x70 - 0x50];
    Gfx70*   m70;                               // +0x070
    uint8_t  mPad74[0x78 - 0x74];
    TribeStrategy_s00cc_8ed0* m78;                         // +0x078  nested strategy/list
    uint8_t  mPad7C[0x85 - 0x7c];
    uint8_t  m85;                               // +0x085  icon window state seen last update
    uint8_t  mPad86[0x178 - 0x86];
    int32_t  mArray178[0x28];                   // +0x178  forty dwords
    int32_t  mArray218[0x28];                   // +0x218  forty more
    Iface2B8* m2B8;                             // +0x2b8

    void  FUN_00cc8ed0(EntityRef* ref);
    void  FUN_00cc9040(EntityRef* ref);
    void* FUN_00cc90a0(EntityRef* ref);
    void  FUN_00cc90f0(EntityRef* ref, int index);
    void  FUN_00cc9270(Vector4* out);
    void  FUN_00cc91b0(int value);
    void  FUN_00cc91e0(int unused);
    bool  FUN_00cc9360();
    void  FUN_00cc93b0(int visible);
    void  FUN_00cc9430();
    void  FUN_00cc9460(TribeObj* obj);
    void  FUN_00cc9740(IWinText* entity, Vector3 pos, int32_t kind, int8_t show);
    void  FUN_00cc9640(IWinText* entity, int8_t show);
    void  FUN_00cc9cd0(int value);
    void  FUN_00cc9d50(EntityRef* ref);
    void  FUN_00cc99b0(uint32_t param_2);

    int   FUN_00cc88e0(int arg);                // 0x00cc88e0
    void  FUN_00cc8be0();                       // 0x00cc8be0
};
struct BufferedWriter {                         // rw::movie::BufferedWriter
    void* GetBuffer();                          // 0x0093b6c0
};
struct ModeView {                               // object returned by the mode strategy's slot 0x6c
    uint8_t mPad00[0x4c];
    BufferedWriter* m4C;                        // +0x04c
};
struct ModeStrategy {                           // SP::cTribeModeStrategy singleton
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual ModeView* pv27();                   // +0x6c

    uint8_t mPad04[0x258 - 0x04];
    Ornament* mOrnament258[0x14];               // +0x258  twenty ornament slots
    Ornament* mOrnament2A8[0x14];               // +0x2a8  twenty more

    uint8_t mPad2F8[0x390 - 0x2f8];
    int32_t m390;                               // +0x390
};
struct cSPUILayout_s00cc_8ed0 {
    void* FindWindowByID(int id, int flag);     // 0x008105b0
};
struct WinIface {                               // window handle returned by cSPUILayout
    PV(0) PV(1) PV(2)
    virtual WinIface* pv3(uint32_t tag);        // +0x0c
    PV(4) PV(5) PV(6) PV(7)
    virtual uint32_t pv8();                     // +0x20  window visibility state
    PV(9)
    virtual void pv10(int mode, int value);     // +0x28
};
#define G_WIN_ID_A         ((int)0x04c61b50)
#define G_WIN_ID_B         ((int)0x04c61dd9)
namespace Simulator {
 struct cGameData; 
}
namespace SP {
    struct cGameNounManager_s00cc_8ed0 {                       // SP::cGameNounManager
        Simulator::cGameData* GetPlayerTribe();     // 0x00bfc5f0
    };
}
namespace SP {
    cGameNounManager_s00cc_8ed0* NounManager();                // 0x00b3d300
}
struct Entity;
struct EntityRange {                                // range handed out by the tribe's slot 0x90
    Entity** mBegin;                                // +0x00
    Entity** mEnd;                                  // +0x04
};
namespace Simulator {
 struct cGameData {            // the player's tribe
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    virtual EntityRange* pv36();                    // +0x90  tribe members

    uint8_t mPad04[0x234 - 0x04];
    int32_t m234;                                   // +0x234  passed to FUN_00b6f0c0

    char FUN_00c8e870();                            // 0x00c8e870
    char FUN_00c8e850();                            // 0x00c8e850
}; 
}
struct CameraCtl_s00cc_8ed0 {                              // camera controller returned by 0x00b3d280
    uint8_t mPad00[0x14];
    uint8_t m14;                                // +0x14  first icon window's state
    uint8_t m15;                                // +0x15
    uint8_t m16;                                // +0x16
    uint8_t m17;                                // +0x17

    char FUN_00cc8810();                        // 0x00cc8810
    char FUN_00cc87f0();                        // 0x00cc87f0
};
struct TribeMode {                              // SP::cTribeModeStrategy singleton view
    char TerrainHasKey(uint32_t key);           // 0x00cd4460
    void SignalTribeEvent(uint32_t key);        // 0x00cd6980
};
struct TerrainSphere {
    char FUN_00c772c0(uint32_t key);            // 0x00c772c0
};
struct TerrainEditor {                          // object returned by SP::NounManager()
    TerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
struct EntitySub {                              // sub-object embedded at entity+0xc0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual char pv20();                        // +0x50
};
struct IconPos {                                // 16-byte icon position block: xyz + w
    Vector3 mPos;                               // +0x00
    float   mW;                                 // +0x0c
};
struct EntityB54 {                              // block entity+0xb54 points at
    uint8_t mPad00[0x74];
    IconPos mIcon;                              // +0x74  icon position
};
struct Entity {                                 // cSPCreatureBase
    uint8_t mPad00[0xc0];
    EntitySub mSubC0;                           // +0x0c0
    uint8_t mPadC4[0xb54 - 0xc4];
    EntityB54* mB54;                            // +0xb54  block the icon position lives in

    void* e040();                               // 0x00c0e040  current animation GUID
};
struct AnimTarget {                             // handle returned by the strategy's slot 0x3c
    PV(0)
    virtual void pv1(void* id, int flag);       // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21)
    virtual void pv22(void* out, int a, int b, int c);   // +0x58

    uint8_t mPad04[0x3c - 0x04];
    float   m3C;                                // +0x3c
    uint8_t mPad40[0x74 - 0x40];
    IconPos mIcon;                              // +0x74  icon position
    uint8_t m84;                                // +0x84
};
void* FUN_00b3d280();                           // 0x00b3d280  camera controller getter
void* GetRecorderState();                       // 0x00435e90
void  KillSetiEffects(uint32_t id, void* recorder);   // 0x00435ed0
// ---- items of slice s00cc8ed0 end

// ---- items of slice s00cc9e20 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100)
void* __cdecl FUN_009512c0();                                        // 0x009512c0
void* __cdecl FUN_009512d0(u32 size, u32 align, const char* what);   // 0x009512d0
void* __cdecl op_new(u32 size, const char* file, int a, int b, const char* what, int line); // 0xf473a0
struct CCitizenOps {
    char  FUN_00c0b770();                             // 0x00c0b770
    u32   FUN_00c22dc0();                             // 0x00c22dc0
    void* FUN_00c22f50();                             // 0x00c22f50 GetTribe
    char  FUN_00c232d0();                             // 0x00c232d0 IsLeader
};
#define CIT(p) ((CCitizenOps*)(p))
void* __cdecl FUN_00cc8830(void* citizen);                           // 0x00cc8830
struct CPosseSetOps {
    char  FUN_00cc9360();                             // 0x00cc9360
    void  FUN_00e26a90(int a);                        // 0x00e26a90
    void  FUN_00e21960();                             // 0x00e21960
    void  FUN_00e28230();                             // 0x00e28230
    void  FUN_00cc8be0();                             // 0x00cc8be0
    void* FUN_00e24c90(void* citizen);                // 0x00e24c90
    void* FUN_00cc88e0(u32 key);                      // 0x00cc88e0
    void* FUN_00cc90a0(u32 key);                      // 0x00cc90a0
    void  FUN_00cc90f0(void* a, void* b);             // 0x00cc90f0
};
#define POSSE(p) ((CPosseSetOps*)(p))
struct CStrategyOps {
    void  FUN_00cc8ed0(void* b);                      // 0x00cc8ed0
    void  FUN_00cc8a30(void* pose, void* citizen);    // 0x00cc8a30
};
#define STRAT(p) ((CStrategyOps*)(p))
void  __cdecl FUN_00e0f9c0(void* minimap, void* a, int b, int c);    // 0x00e0f9c0 RemoveIcon
void  __cdecl FUN_00e10580(void* minimap, void* a, void* b, int c, int d); // 0x00e10580 AddIcon
void* __cdecl FUN_00e25710(void* mem);                               // 0x00e25710 cSPUIPosse ctor
void  __cdecl FUN_00e5c780(void* map, void* out, void* key);         // 0x00e5c780 rbtree::find
void* __cdecl FUN_00921580(void* node);                              // 0x00921580 RBTreeIncrement
void* __cdecl FUN_00bca2c0();                                        // 0x00bca2c0 FirstPending
void* __cdecl FUN_00cca0c0(void* p);                                 // 0x00cca0c0
void* __cdecl FUN_00c9cec0(u32 id);                                  // 0x00c9cec0
void* __cdecl FUN_008061c0(void* layout, u32 id);                    // 0x008061c0 GetImageFromLayout
void* __cdecl FUN_00b3d300();                                        // 0x00b3d300 NounManager
void* __cdecl FUN_00bfc5f0(void* nounManager);                       // 0x00bfc5f0 GetPlayerTribe
char  __cdecl FUN_00c8e870(void* tribe);                             // 0x00c8e870
char  __cdecl FUN_00c8e850(void* tribe);                             // 0x00c8e850
void* __cdecl FUN_00cd40b0();                                        // 0x00cd40b0 cTribeModeStrategy::Instance
void  __cdecl FUN_006b5770(void* self, u32 a, u32 b, const wchar_t* s); // cString ctor 0x6b5770
const wchar_t* __cdecl FUN_006b55c0(void* self);                     // cString::GetText 0x6b55c0
void  __cdecl FUN_006b5240(void* self);                              // cString dtor 0x6b5240
struct CTransformOps { void* Assign(const void* src); };              // 0x537dc0
struct CModelInstSet { void  Update(); };                             // 0x6f3b70
struct CPool {
    void* FUN_00ccad10(u8* payload);                  // 0x00ccad10
    void* FUN_00cca170(void* payload);                // 0x00cca170
};
struct cPosseSet {
    u8    pad_00[0x1c];
    void* mpFreeList;                                 // +0x1c
    u8    pad_20[0x2c - 0x20];
    u32   mAllocIndex;                                // +0x2c

    void Init();                                      // 0x00cca230
};
struct cTribeDisplayStrategy {
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0c();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1c();
virtual void vf20();
virtual void vf24();
virtual void vf28();
virtual void vf2c();
virtual void vf30();
virtual void vf34();
virtual void vf38();
virtual void vf3c();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4c();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5c();
virtual void vf60();
virtual void vf64();
virtual void vf68();
    virtual void* GetDisplayStrategy();               // +0x6c

    u8    pad_1c_pre[0x1c - 0x04];
    void* mpFreeList;                                 // +0x1c
    u8    pad_20[0x2c - 0x20];
    u32   mAllocIndex;                                // +0x2c
    u8    pad_30[0x70 - 0x30];
    void* mpMinimap;                                  // +0x70
    void* mpLayout;                                   // +0x74
    void* mpPosseSet;                                 // +0x78
    u8    pad_7c[0x94 - 0x7c];
    u32   mMapCount;                                  // +0x94 (eastl map header)
    void* mMapAnchor;                                 // +0x98
    void* mMapEnd;                                    // +0x9c

    void FUN_00cc9e20(void* citizen);                 // 0x00cc9e20
    void FUN_00cca060();                              // 0x00cca060
    char FUN_00cca090();                              // 0x00cca090
    void FUN_00cca0a0();                              // 0x00cca0a0
    u32  FUN_00cca3d0(void* citizen);                 // 0x00cca3d0
    void SetPosseActivity(void* key, int activity);   // 0x00cca5b0
    void FUN_00cca880(void* citizen, int a);          // 0x00cca880
    char SetGroundSpearTransform(char slot, u32 index, const void* xform, char ref); // 0x00cca9e0
    void FUN_00ccaa80(void* arg);                     // 0x00ccaa80
    void FUN_00ccab80();                              // 0x00ccab80
};
static inline int   ld32(const void* p, int o)  { return *(const int*)((const char*)p + o); }
static inline u32   ldu32(const void* p, int o) { return *(const u32*)((const char*)p + o); }
static inline u8    ldu8(const void* p, int o)  { return *(const u8*)((const char*)p + o); }
static inline void  st32(void* p, int o, int v){ *(int*)((char*)p + o) = v; }
static inline void** vtbl(const void* p)       { return *(void***)p; }
// ---- items of slice s00cc9e20 end

// ---- items of slice s00ccaff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g1582ff0;
extern float g1582ff4;
extern float g1471064;
extern float g13ef53c;
extern float g13ebc5c;
extern float g1485720;
extern uint8_t g169b160[0x24];   // a Matrix3
struct Vertex3D { float f[6]; };
struct IObj { virtual void AddRef(); virtual void Release(); };
inline void AddRefOf(void* o) { if (o) ((IObj*)o)->AddRef(); }
inline void ReleaseOf(void* o) { if (o) ((IObj*)o)->Release(); }
#define VF(o, n) (*(void**)((uint8_t*)(*(void**)(o)) + (n)))
void* __cdecl FUN_0067dcc0();                                     // MessageServer
void* __cdecl FUN_0067ddd0();                                     // EffectsManager
void* __cdecl FUN_00b30d70();                                     // GetGameTerrainCursor
void* __cdecl FUN_009512d0(int a, int b, const char* n, void* p);
void* __cdecl FUN_00f473a0(uint32_t size, uint32_t alloc, int a, int b, int c, int d); // operator_new
void  __cdecl FUN_00f47380(void* p);                              // operator_delete_array
void* __cdecl FUN_00ac8730(void* p);
void  __cdecl FUN_0075d4b0(const char* name, void* a, int b);
void* __cdecl FUN_00421c80(void* p, int a);                       // SlotMessage::Construct
void  __cdecl FUN_0061df40(void* p);
void  __cdecl FUN_00c99c30(void* tribe);                          // cTribe::ChooseNewHutModel
struct S00e0ad00 { void __thiscall FUN_00e0ad00(int a); };
struct S00e25b50 { void* __thiscall FUN_00e25b50(); };                 // cSPUIPosseItemTribeGhostShell ctor
struct S00bfc5d0 { bool __thiscall FUN_00bfc5d0(); };
struct S00cc8be0 { void __thiscall FUN_00cc8be0(); };
struct S00e24c90 { void* __thiscall FUN_00e24c90(int a); };            // cSPUIPosse::FindItem
struct S00c8eae0 { uint32_t __thiscall FUN_00c8eae0(); };              // cTribe::GetMaxPopulation
struct S00bfc5f0 { void* __thiscall FUN_00bfc5f0(); };                 // cGameNounManager::GetPlayerTribe
struct S00cc9040 { void __thiscall FUN_00cc9040(void* key); };        // on this->[0x78]
struct S00e0f9c0 { void __thiscall FUN_00e0f9c0(void* key, int a, int b); }; // MinimapWin::RemoveIcon
struct S00cc9460 { void __thiscall FUN_00cc9460(void* obj); };        // MakeTribeIcon
struct S00cc91e0 { void __thiscall FUN_00cc91e0(void* obj); };
struct S00437f70 { void __thiscall FUN_00437f70(bool b); };           // Model::SetFlag
struct S00cd4460 { bool __thiscall FUN_00cd4460(uint32_t k); };       // TerrainHasKey
struct S00cd6980 { void __thiscall FUN_00cd6980(uint32_t e); };       // SignalTribeEvent
struct S00bfc5e0 { void __thiscall FUN_00bfc5e0(bool b); };           // on key+0x5a8
void* __cdecl FUN_006985b0(Vector3* out, const Vector3* in);     // OrthogonalVector
void* __cdecl FUN_0069b440(void* out, const Vector3* f, const Vector3* u); // Matrix3FromFacingAndUp
void* __cdecl FUN_0041cb40(void* dst, void* src);                 // Matrix3::Assign
void* __cdecl FUN_00b3d350();                                     // PlanetModel
void  __cdecl FUN_00b7e3b0(void* pm, Vector3* out, const Vector3* p); // GetNormalAt
float __cdecl FUN_00d99a60(void* a);                              // DistanceBetweenBodies
void __cdecl FUN_00720250(Vertex3D* first, Vertex3D* last, Vertex3D* dst); // CopyVertex3D
void __cdecl FUN_00cc8b50(Vertex3D* d, Vertex3D* f, Vertex3D* l); // CopyBackwardVertex3D
Vertex3D* __cdecl FUN_00cca1d0(Vertex3D* f, Vertex3D* l, Vertex3D* d); // UninitCopyVertex3D
void __cdecl FUN_00cca110(void** out, Vertex3D* first, Vertex3D* lastEq, Vertex3D* dst, Vertex3D* last); // FillVertex3D
struct RBNode {
    RBNode*  mpLeft;    // +0x00
    RBNode*  mpRight;   // +0x04
    RBNode*  mpParent;  // +0x08
    uint32_t mColor;    // +0x0c
};
struct CitizenUIData {
    void*    mpPosseObject;   // +0x14
    uint32_t mUiState;        // +0x18
};
struct CitizenNode : RBNode {
    void*         mpKey;      // +0x10  AutoRefCount<cSPCreatureCitizen>
    CitizenUIData mValue;     // +0x14
};
struct MemberNode : RBNode {
    void* mpStrategy;   // +0x10
    void* mpCreature;   // +0x14
};
struct Vec3D {
    Vertex3D* mpBegin;      // +0x00
    Vertex3D* mpEnd;        // +0x04
    Vertex3D* mpCapacity;   // +0x08

    Vertex3D* Grow(uint32_t n, Vertex3D* first, Vertex3D* last);   // 0x00ccb260
    Vec3D*    Assign(Vec3D* other);                                // 0x00ccb810
    void      InsertAt(Vertex3D* pos, Vertex3D* val);              // 0x00ccba20
    Vertex3D* Insert(Vertex3D* pos, Vertex3D* val);                // 0x00ccbc90
};
struct TreeIter { CitizenNode* mpNode; };
struct EffectTree {
    void* mpNode00;      // +0x00
    void* mpEnd04;       // +0x04
    void* mpNode08;      // +0x08
    void* mpRoot0c;      // +0x0c
    void* mpNode10;      // +0x10
    uint8_t mFlag14;     // +0x14
    TreeIter Find(uint32_t* keyRef) const;                          // 0x00e5c780
    void     Erase(uint32_t* keyRef);                               // 0x005f05e0
    uint8_t* FindOrInsert(uint32_t* key);                           // 0x00ccc070
    uint8_t* InsertHint2(RBNode* hint, uint32_t* val);              // 0x00ccc120
    void*    FUN_00ccb930(void* out1, void* hint, void* out2, void* flag); // 0x00ccb930
};
struct HashNode { void* mpValue; };
struct HashIter { void* mpNode; void* mpBucket; };
struct Hashtable {
    void*    mp_00;         // +0x00
    void**   mpBuckets;     // +0x04
    uint32_t mBucketCount;  // +0x08
    void     Find(HashIter* out, const uint32_t* keyRef) const;     // 0x00db4780
    void     InsertNode(HashIter* out, const uint32_t* key, uint32_t flag); // 0x00ccb1a0
    HashNode* FUN_00ccbc00(uint32_t* key);                          // 0x00ccbc00
};
struct PosseItem_s00cc_aff0 { uint32_t mWords[2]; };
struct ItemList {
    PosseItem_s00cc_aff0* mpBegin;     // +0x00
    PosseItem_s00cc_aff0* mpEnd;       // +0x04
    PosseItem_s00cc_aff0* mpCapacity;  // +0x08
    int Count() const { return (int)(mpEnd - mpBegin); }
};
struct PosseObject {              // cSPUIPosse (only the item vector is used here)
    uint8_t pad_00[0xa4];
    ItemList mItems;              // +0xa4
};
struct cTDS {
    uint8_t  pad_00[0x08];
    void*    mpPosseVec0;              // +0x08
    void*    mpPosseVec1;              // +0x0c
    void*    mpPosseVec2;              // +0x10
    void*    mpPosseVec3;              // +0x14
    void*    mpPosseVec4;              // +0x18
    void*    mpPosse;                  // +0x1c  cSPUIPosse*
    uint8_t  pad_20[0x38 - 0x20];
    void*    mpMiniMapWin_38;          // +0x38
    void*    mp_3c;                    // +0x3c
    void*    mpObj_40;                 // +0x40
    uint8_t  pad_44[0x60 - 0x44];
    MemberNode* mpMemberEnd;           // +0x60  (sentinel; == this+0x60)
    MemberNode* mpMemberRoot;          // +0x64
    uint8_t  pad_68[0x70 - 0x68];
    void*    mpMiniMapWin;             // +0x70
    uint8_t  pad_74[4];
    void*    mpObj_78;                 // +0x78
    uint8_t  pad_7c[0x94 - 0x7c];
    EffectTree mEffectTree;            // +0x94
    uint8_t  pad_ac[0xc0 - 0xac];
    uint8_t  mEffectSlot[0x200];       // +0xc0  inlined effect object (vtable at +0xc0)
    Hashtable mEffectCache;            // +0x2c0

    void  SendSelectMessage(void* key, uint32_t kind);                          // 0x00ccaff0
    void  MaintainSelectionState(void* key);                                    // 0x00ccb0f0
    void  FUN_00ccb2c0();                                                       // 0x00ccb2c0
    bool  HandleMessage(uint32_t id, void* msg);                                // 0x00ccb420
    void  FUN_00ccbb60(void* key);                                              // 0x00ccbb60
    void  FUN_00ccbd10(void* a, Vector3* p, float f, int kind, bool b);         // 0x00ccbd10
};
// ---- items of slice s00ccaff0 end


// @ 0x00cc8810
bool CameraCtl::FUN_00cc8810()
{
    return m17 || m16;
}

// @ 0x00cc88e0
u32 TribeStrategy::FUN_00cc88e0(u32 key)
{
    switch (key) {
    case 11: return 0;
    case 1:
    case 2:
    case 3:
    case 9: return 2;
    case 4:
    case 5:
    case 6: return 1;
    case 7:
    case 8: return 3;
    default: return 4;
    }
}

// @ 0x00cc9430
void TribeStrategy_s00cc_8ed0::FUN_00cc9430()
{
    Posse** p = mChild + 6;
    for (int i = 5; i >= 0; i--) {
        Posse* c = *--p;
        if (c != 0) {
            c->pv1();
        }
    }
    mVt = 0x013ef094;
}

// @ 0x00cc9460
void TribeStrategy_s00cc_8ed0::FUN_00cc9460(TribeObj* obj)
{
    if (m70 == 0) {
        return;
    }

    IconDef icon;
    icon.mKind = (obj->FUN_00c905a0() != 0 ? 0x100000 : 0) | 2;
    icon.mColor = 0;
    icon.mPos.x = 0.0f;
    icon.mPos.y = 0.0f;
    icon.mPos.z = -1.0f;
    icon.mOwner.mPtr = 0;
    icon.mRadius = 0.0f;
    icon.mExtra1C = 0;
    icon.mExtra20 = 0;

    Vector3 pos = *obj->m120.pv11();
    icon.mPos = pos;

    float* tint = (float*)FUN_00b6f0c0(obj->m234);
    float c0 = tint[0];
    float c1 = tint[1];
    float c2 = tint[2];
    icon.mColor = 0xff000000u
                  | ((uint32_t)(int)(c0 * 255.0f) & 0xffu) << 16
                  | ((uint32_t)(int)(c1 * 255.0f) & 0xffu) << 8
                  | ((uint32_t)(int)(c2 * 255.0f) & 0xffu);

    icon.mOwner = (IWinText*)obj;

    m70->RemoveIcon(obj, 1, 0);
    m70->AddIcon(obj, &icon, 0, 0);
    if (icon.mOwner.mPtr != 0) {
        icon.mOwner.mPtr->pv1();
    }
}

// @ 0x00cc9640
void TribeStrategy_s00cc_8ed0::FUN_00cc9640(IWinText* entity, int8_t show)
{
    Gfx70* gfx = m70;
    if (gfx == 0) {
        return;
    }
    if (show == 0) {
        gfx->RemoveIcon(entity, 1, 0);
        return;
    }
    if (entity == 0) {
        return;
    }
    if (gfx->FUN_00e0df70(entity, entity->mSub34.pv11(), 0) != 0) {
        return;
    }

    IconDef icon;
    icon.mColor = 0;
    icon.mPos.x = 0.0f;
    icon.mPos.y = 0.0f;
    icon.mPos.z = -1.0f;
    icon.mKind = 1;
    icon.mOwner.mPtr = 0;
    icon.mRadius = 0.0f;
    icon.mExtra1C = 0;
    icon.mExtra20 = 0;

    icon.mPos = *entity->mSub34.pv11();
    icon.mOwner = entity;
    icon.mKind = 0x20;
    m70->AddIcon(entity, &icon, 0, 0);
    if (icon.mOwner.mPtr != 0) {
        icon.mOwner.mPtr->pv1();
    }
}

// @ 0x00cc9740
void TribeStrategy_s00cc_8ed0::FUN_00cc9740(IWinText* entity, Vector3 pos, int32_t kind, int8_t show)
{
    if (entity == 0) {
        return;
    }
    if (m70 == 0) {
        return;
    }
    if (show == 0) {
        m70->RemoveIcon(entity, 1, 0);
        return;
    }
    if (m70->FUN_00e0df70(entity, &pos, 0) != 0) {
        return;
    }

    IconDef icon;
    icon.mColor = 0;
    icon.mOwner.mPtr = 0;
    icon.mRadius = 0.0f;
    icon.mExtra1C = 0;
    icon.mExtra20 = 0;
    if (kind == 0) {
        icon.mKind = 0x10000;
    } else if (kind == 1) {
        icon.mKind = 0x8000;
    } else {
        icon.mKind = 0x4000;
        icon.mColor = FUN_0067ac80(0xff, 0xff, 0xff, 0);
    }
    icon.mPos = pos;
    m70->AddIcon(entity, &icon, 0, 0);
    if (icon.mOwner.mPtr != 0) {
        icon.mOwner.mPtr->pv1();
    }
}

// @ 0x00cc9830
void FUN_00cc9830(int id, int value)
{
    ModeStrategy* inst = (ModeStrategy*)SP::cTribeModeStrategy::Instance();
    ModeView* view = inst->pv27();
    cSPUILayout_s00cc_8ed0* layout = (cSPUILayout_s00cc_8ed0*)view->m4C->GetBuffer();
    WinIface* window = (WinIface*)layout->FindWindowByID(id, 1);
    WinIface* child;
    if (window != 0) {
        child = (WinIface*)window->pv3(0x8ed27e7a);
        child->pv10(4, value);
    } else {
        child = 0;
        child->pv10(4, value);
    }
}

// @ 0x00cc9890
void FUN_00cc9890()
{
    ModeStrategy* inst = (ModeStrategy*)SP::cTribeModeStrategy::Instance();
    if (inst->m390 == 1) {
        FUN_00cc9830(G_WIN_ID_A, 0);
        FUN_00cc9830(G_WIN_ID_B, 1);
    } else {
        FUN_00cc9830(G_WIN_ID_A, 1);
        FUN_00cc9830(G_WIN_ID_B, 0);
    }
}

// @ 0x00cc98e0
Ornament* __stdcall FUN_00cc98e0(TribeObj* obj)
{
    if (obj == 0) {
        return 0;
    }

    int8_t mode = obj->m120.pv22();
    Ornament* found = 0;
    int bestValue = 0x7fffffff;
    int bestIndex = -1;

    ModeStrategy* inst = (ModeStrategy*)SP::cTribeModeStrategy::Instance();
    Ornament** arr;
    if (mode != 0) {
        arr = inst->mOrnament258;
    } else {
        arr = inst->mOrnament2A8;
    }

    for (uint32_t i = 0; i < 0x14; i++) {
        Ornament* ornament = arr[i];
        if (ornament != 0) {
            int value = ornament->mField240;
            if (value <= 0) {
                found = arr[i];
                if (found != 0) {
                    goto use_found;
                }
                break;
            } else if (value < bestValue) {
                bestValue = value;
                bestIndex = i;
            }
        }
    }
    if (bestIndex < 0) {
        return found;
    }
    found = arr[bestIndex];
    if (found == 0) {
        return found;
    }
use_found:
    if (found->mSub34.pv43() != 0) {
        IconTarget* target = (IconTarget*)found->mSub34.pv43();
        if (target != 0) {
            target->mFlags |= 4;
            Vector3* pos = FUN_00b6f0c0(obj->m234);
            target->mPos = *pos;
        }
    }
    return found;
}

// @ 0x00cc99b0
void TribeStrategy_s00cc_8ed0::FUN_00cc99b0(uint32_t param_2)
{
    CameraCtl_s00cc_8ed0* camera = (CameraCtl_s00cc_8ed0*)FUN_00b3d280();
    if (m4C == 0 || camera == 0) {
        return;
    }

    cSPUILayout_s00cc_8ed0* layout = (cSPUILayout_s00cc_8ed0*)m4C->GetBuffer();
    if (layout != 0) {
        WinIface* el = (WinIface*)layout->FindWindowByID(0x4cab570, 1);
        WinIface* window = el != 0 ? el->pv3(0x8ed27e7a) : 0;
        uint8_t flags = 0;
        if (window != 0) {
            flags = (uint8_t)((window->pv8() >> 1) & 1);
            camera->m14 = flags;
        }

        el = (WinIface*)layout->FindWindowByID(0x4cab571, 1);
        if (el != 0 && (el = el->pv3(0x8ed27e7a)) != 0) {
            uint8_t on = (uint8_t)((el->pv8() >> 1) & 1);
            flags |= on;
            camera->m15 = on;
        }

        el = (WinIface*)layout->FindWindowByID(0x4cab56f, 1);
        if (el != 0 && (el = el->pv3(0x8ed27e7a)) != 0) {
            uint8_t on = (uint8_t)((el->pv8() >> 1) & 1);
            flags |= on;
            camera->m17 = on;
        }

        el = (WinIface*)layout->FindWindowByID(0x4cab56e, 1);
        if (el != 0 && (el = el->pv3(0x8ed27e7a)) != 0) {
            uint8_t on = (uint8_t)((el->pv8() >> 1) & 1);
            flags |= on;
            camera->m16 = on;
        }

        if (flags != 0 && m85 == 0) {
            KillSetiEffects(0x9203d717, GetRecorderState());
        }
        m85 = flags;
    }

    if (m85 != 0) {
        TribeMode* mode = (TribeMode*)SP::cTribeModeStrategy::Instance();
        TerrainEditor* editor = (TerrainEditor*)SP::NounManager();
        TerrainSphere* sphere = editor->GetCurrentTerrainSphere();
        if (!sphere->FUN_00c772c0(0x56d1871)) {
            if (mode->TerrainHasKey(0x64be5ff)) {
                if (!mode->TerrainHasKey(0x53203528) && camera->FUN_00cc8810()) {
                    mode->SignalTribeEvent(0x53203528);
                }
                if (!mode->TerrainHasKey(0x64c010f) && camera->FUN_00cc87f0()) {
                    mode->SignalTribeEvent(0x64c010f);
                }
            }
        }
    }

    if (m2B8 != 0) {
        m2B8->pv8((int)param_2);
        AnimTarget* target = (AnimTarget*)m2B8->pv15();
        if (target == 0) {
            return;
        }
        Simulator::cGameData* tribe = SP::NounManager()->GetPlayerTribe();
        target->m84 = 1;
        Vector3* pos = FUN_00b6f0c0(tribe->m234);
        target->mIcon.mPos = *pos;
        target->mIcon.mW = 1.0f;
        target->m3C = 1.0f;
        EntityRange* range = tribe->pv36();
        Entity** it = range->mBegin;
        Entity** end = range->mEnd;
        for (; it != end; ++it) {
            Entity* entity = *it;
            if (entity->mSubC0.pv20() != 0) {
                target->mIcon = entity->mB54->mIcon;
                param_2 = 0;
                target->pv22(&param_2, 0, 0, 0);
                if (param_2 != (uint32_t)entity->e040()) {
                    target->pv1(entity->e040(), 0);
                }
                return;
            }
        }
        param_2 = 0;
        target->pv22(&param_2, 0, 0, 0);
        if (param_2 != 0x2481de5) {
            target->pv1((void*)0x2481de5, 0);
        }
    }
}

// @ 0x00cc9cd0
void TribeStrategy_s00cc_8ed0::FUN_00cc9cd0(int elapsed)
{
    ModeStrategy* mode = (ModeStrategy*)SP::cTribeModeStrategy::Instance();
    for (int i = 0; i < 0x14; i++) {
        Ornament* ornament = mode->mOrnament258[i];
        if (ornament != 0) {
            ornament->Update(elapsed);
        }
    }
    for (int i = 0; i < 0x14; i++) {
        Ornament* ornament = mode->mOrnament2A8[i];
        if (ornament != 0) {
            ornament->Update(elapsed);
        }
    }
    for (int i = 0; i < 0x28; i++) {
        mArray178[i] -= elapsed;
        mArray218[i] -= elapsed;
    }
}

// @ 0x00cc9d50
void TribeStrategy_s00cc_8ed0::FUN_00cc9d50(EntityRef* ref)
{
    Gfx70* gfx = m70;
    if (gfx != 0) {
        gfx->RemoveIcon(ref, 1, 0);
    }

    TribeStrategy_s00cc_8ed0* obj = m78;
    int slot;
    if (ref->FUN_00c0b770() != 0) {
        slot = obj->FUN_00cc88e0(ref->FUN_00c22dc0());
    } else {
        slot = 5;
    }

    PosseItem* item = (PosseItem*)obj->mChild[slot]->FindItem(ref);
    if (ref != 0 && item != 0) {
        item->pv32(0x3dea7f0, 0.0f, 1, 1);
        item->pv32(0x3d99184, 0.0f, 1, 0);
        item->pv32(0x3d99162, 0.0f, 1, 0);
        item->pv33(0, 0);
        item->pv33(1, 0);
    }
}

// @ 0x00cc9e20
void cTribeDisplayStrategy::FUN_00cc9e20(void* citizen)
{
    u8* p = (u8*)this;
    u8* c = (u8*)citizen;
    if (ld32(p, 0x70) != 0 && CIT(citizen)->FUN_00c22f50() != 0) {
        FUN_00e0f9c0(*(void**)((char*)p + 0x70), citizen, 1, 0);

        u8 rec[0x20];
        *(u32*)(rec + 0x00) = 0;
        *(u32*)(rec + 0x04) = 0;
        *(u32*)(rec + 0x08) = 0;
        *(u32*)(rec + 0x0c) = 0xbf800000;
        *(u32*)(rec + 0x10) = 0x2008;
        *(u32*)(rec + 0x14) = 0;
        *(u32*)(rec + 0x18) = 0;
        *(u32*)(rec + 0x1c) = 0;

        float* col = (float*)(*(void*(__thiscall**)(void*))((char*)vtbl(c) + 0xe0))((void*)c);
        u32 r = (u32)(long long)(col[0] * 255.0f);
        u32 g = (u32)(long long)(col[1] * 255.0f);
        u32 b = (u32)(long long)(col[2] * 255.0f);
        *(u32*)(rec + 0x00) = ((((r | 0xffffff00) << 8) | (g & 0xff)) << 8) | (b & 0xff);

        u8* pos = (u8*)(*(void*(__thiscall**)(void*))((char*)vtbl(c) + 0xc0))((void*)c);
        *(u32*)(rec + 0x04) = *(u32*)(pos + 0x00);
        *(u32*)(rec + 0x08) = *(u32*)(pos + 0x04);
        *(u32*)(rec + 0x0c) = *(u32*)(pos + 0x08);

        FUN_00e10580(*(void**)((char*)p + 0x70), citizen, rec, 0, 0);
    }

    void* ps = *(void**)((char*)p + 0x78);
    u32 kind;
    if (CIT(citizen)->FUN_00c0b770() != 0) {
        kind = (u32)POSSE(ps)->FUN_00cc88e0(CIT(citizen)->FUN_00c22dc0());
    } else {
        kind = 5;
    }
    void* pose = *(void**)((char*)ps + 8 + kind * 4);
    void* item = POSSE(pose)->FUN_00e24c90(citizen);
    if (citizen != 0 && item != 0) {
        (*(void(__thiscall**)(void*, u32, float, int, int))((char*)vtbl(item) + 0x80))(item, 0x3dea7f0, 0.0f, 1, 1);
    }
}

// @ 0x00cca060
void cTribeDisplayStrategy::FUN_00cca060()
{
    u8* p = (u8*)this;
    void* ps = *(void**)((char*)p + 0x78);
    if (ps != 0) {
        u8* slot = (u8*)ps + 8;
        for (int i = 6; i != 0; i--) {
            void* q = *(void**)slot;
            if (q != 0) {
                POSSE(q)->FUN_00e21960();
            }
            slot += 4;
        }
    }
}

// @ 0x00cca090
char cTribeDisplayStrategy::FUN_00cca090()
{
    u8* p = (u8*)this;
    void* ps = *(void**)((char*)p + 0x78);
    if (ps != 0) {
        return POSSE(ps)->FUN_00cc9360();
    }
    return 0;
}

// @ 0x00cca0a0
void cTribeDisplayStrategy::FUN_00cca0a0()
{
    u8* p = (u8*)this;
    void* ps = *(void**)((char*)p + 0x78);
    if (ps != 0) {
        void* q = *(void**)((char*)ps + 8);
        if (q != 0) {
            POSSE(q)->FUN_00e26a90(0);
        }
    }
}

// @ 0x00cca0e0
void FUN_00cca0e0_impl(void* dst, unsigned count, const void* src)
{
    struct P3 { u32 a, b, c; };
    P3* d = (P3*)dst;
    const P3* s = (const P3*)src;
    for (unsigned i = count; i > 0; i--) {
        *d = *s;
        d++;
        s++;
    }
}

// @ 0x00cca110
void FUN_00cca110_impl(void** out, u8* first, u8* last, u8* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0) {
                *(u32*)(dst + 0x00) = *(u32*)(first + 0x00);
                *(u32*)(dst + 0x04) = *(u32*)(first + 0x04);
                *(float*)(dst + 0x08) = *(float*)(first + 0x08);
                *(float*)(dst + 0x0c) = *(float*)(first + 0x0c);
                *(float*)(dst + 0x10) = *(float*)(first + 0x10);
            }
            first += 0x18;
            dst   += 0x18;
        } while (first != last);
        *out = dst;
    }
}

// @ 0x00cca170
void* CPool::FUN_00cca170(void* payload)
{
    u8* mem = (u8*)op_new(0x20, "Simulator", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                          0xd1);
    u8* node = mem + 0x10;
    if (node != 0) {
        void* p = *(void**)payload;
        *(void**)node = p;
        if (p != 0) {
            (*(void(__thiscall**)(void*))vtbl(p))(p);
        }
        struct Tail { u32 a, b, c; };
        *(Tail*)(node + 4) = *(Tail*)((u8*)payload + 4);
    }
    return mem;
}

// @ 0x00cca1d0
void FUN_00cca1d0_impl(u8* first, u8* last, u8* dst)
{
    if (first != last) {
        do {
            if (dst != 0) {
                *(u32*)(dst + 0x00) = *(u32*)(first + 0x00);
                *(u32*)(dst + 0x04) = *(u32*)(first + 0x04);
                *(float*)(dst + 0x08) = *(float*)(first + 0x08);
                *(float*)(dst + 0x0c) = *(float*)(first + 0x0c);
                *(float*)(dst + 0x10) = *(float*)(first + 0x10);
            }
            first += 0x18;
            dst   += 0x18;
        } while (first != last);
    }
}

// @ 0x00cca230
void cPosseSet::Init()
{
    u8* self = (u8*)this;
    // the six AutoRefCount<cSPUIPosse> slots start at +8 and are walked
    // downwards: slot index i -> +8 + i*4.
    int stop = 5;
    u8* slot = (u8*)self + 0x8 + 5 * 4;    // &mPosse[5]
    for (;;) {
        u8* mem = (u8*)FUN_009512c0();
        (void)mem;
        u8* raw = (u8*)FUN_009512d0(0x20c, 4, "UI/Posse");
        u8* novo;
        if (raw != 0) {
            novo = (u8*)FUN_00e25710(raw);
        } else {
            novo = 0;
        }
        void* old = *(void**)slot;
        if (novo != old) {
            if (novo != 0) {
                (*(void(__thiscall**)(void*))vtbl(novo))(novo);
            }
            *(void**)slot = novo;
            if (old != 0) {
                (*(void(__thiscall**)(void*))((char*)vtbl(old) + 4))(old);
            }
        }
        void* cur = *(void**)slot;
        (*(void(__thiscall**)(void*, float, const wchar_t*))((char*)vtbl(cur) + 0x80))(cur, 0x40464100, L"PosseBar");
        stop--;
        slot -= 4;
        if (stop < 0) {
            break;
        }
    }

    wchar_t name[0x10];
    FUN_006b5770(name, 0xf71fa311, 0xf37c273b, L"~Tribe");
    u8* posseAdults = (u8*)self + 0x8;
    void* first = *(void**)posseAdults;
    u8* cur = (u8*)first;
    (*(void(__thiscall**)(void*, const wchar_t*))((char*)vtbl(cur) + 0xb8))(cur, FUN_006b55c0(name));
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x1c)) + 0xb8))(*(void**)((char*)self + 0x1c), (u32*)0x13ec468);
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x10)) + 0xb8))(*(void**)((char*)self + 0x10), (u32*)0x13ec468);
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x0c)) + 0xb8))(*(void**)((char*)self + 0x0c), (u32*)0x13ec468);
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x14)) + 0xb8))(*(void**)((char*)self + 0x14), (u32*)0x13ec468);
    (*(void(__thiscall**)(void*, u32*))((char*)vtbl(*(void**)((char*)self + 0x18)) + 0xb8))(*(void**)((char*)self + 0x18), (u32*)0x13ec468);

    u8* ptr = (u8*)posseAdults;
    for (int i = 0; i < 6; i++) {
        void* pose = *(void**)ptr;
        float f = *(float*)0x1476a90;
        (*(void(__thiscall**)(void*, float))((char*)vtbl(pose) + 0xc4))(pose, f);
        if (i != 0) {
            void* wnd = (void*)FUN_008061c0((void*)(*(u8**)((char*)pose + 0x0) + 0x1bc), 0x3dae412);
            (*(void(__thiscall**)(void*, int, int))((char*)vtbl(wnd) + 0x7c))(wnd, 1, 0x10);
            (*(void(__thiscall**)(void*, int, int))((char*)vtbl(wnd) + 0x7c))(wnd, 2, 0);
            (*(void(__thiscall**)(void*, int, int))((char*)vtbl(wnd) + 0x7c))(wnd, 1, 0);
        }
        ptr += 4;
    }
    POSSE(self)->FUN_00cc8be0();
    FUN_006b5240(name);
}

// @ 0x00cca3d0
u32 cTribeDisplayStrategy::FUN_00cca3d0(void* citizen)
{
    u8* p = (u8*)this;
    u8* c = (u8*)citizen;
    if (ldu8(p, 0xb5e) != 0) {
        return 0;
    }
    u32 v = ldu32(*(void**)((char*)p + 0xb4c), 0x1d8);
    if (v < 0x4639cd2) {
        if (v == 0x4639cd1) return 7;
        if (v < 0x4625f65) {
            if (v == 0x4625f64) return 9;
            if (v == 0x4611ff4) return 8;
            if (v == 0x461300f) return 3;
            if (v == 0x4623e0c) {
                void* o = FUN_00bca2c0();
                if (o != 0) {
                    int k = *(int*)o;
                    if (k == 8) return 4;
                    if (k == 9) return 0xe;
                }
            }
        } else if (v == 0x462854d) {
            void* o = FUN_00bca2c0();
            if (o != 0 && *(int*)o == 3) {
                void* a = FUN_00cca0c0((char*)o + 0x28);
                if (a != 0) {
                    u32 s = (u32)(*(int(__thiscall**)(void*))((char*)vtbl(a) + 0x58))(a);
                    s -= 1;
                    if (s <= 8) {
                        static const u8 tbl[9] = { 10, 10, 10, 13, 13, 13, 12, 11, 10 };
                        return tbl[s];
                    }
                }
            }
        } else if (v == 0x462854e) {
            return 1;
        } else if (v == 0x462855e) {
            return 0xe;
        }
    } else {
        if (v < 0x569236f) {
            if (v == 0x569236e) return 7;
            if (v == 0x5218bb3) return 1;
            if (v == 0x562aa6f) return 8;
            if (v == 0x562c0fb) return 8;
        } else if (v == 0x5b9b7f5) {
            return 7;
        } else if (v == 0xb46e8803) {
            return 5;
        } else if (v == 0xf56baff5) {
            return 0xe;
        }
    }
    void* q = (void*)(*(int(__thiscall**)(void*))((char*)vtbl(p) + 0x20))(p);
    if (q != 0) {
        u32 id = (u32)(*(int(__thiscall**)(void*))((char*)vtbl(q) + 0x1c))(q);
        if (id == 0x3c19bc97) return 6;
        if (id == 0xf09b40e0) return 2;
    }
    (void)c;
    return 0;
}

// @ 0x00cca5b0
void cTribeDisplayStrategy::SetPosseActivity(void* key, int activity)
{
    u8* p = (u8*)this;
    if (ld32(p, 0x78) == 0) {
        return;
    }
    u8* k = (u8*)key;
    if (k != 0) {
        (*(void(__thiscall**)(void*))vtbl(k))(k);
    }
    u8 nodeOut[4];
    FUN_00e5c780((char*)p + 0x94, nodeOut, &k);
    if (k != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(k) + 4))(k);
    }
    u8* node = *(u8**)nodeOut;
    if (node == p + 0x98) {
        return;
    }
    if (ld32(node, 0x1c) == activity) {
        return;
    }
    void* pose = (void*)POSSE(*(void**)((char*)p + 0x78))->FUN_00cc90a0(ldu32(node, 0x14));
    if (pose == 0) {
        return;
    }
    st32(node, 0x1c, activity);
    switch (activity) {
    case 1:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x74e57247, ldu32(p, 0x74), 0);
        return;
    case 2:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0xe7032112, ldu32(p, 0x74), 0);
        return;
    case 3: {
        void* tribe = FUN_00bfc5f0(FUN_00b3d300());
        if (FUN_00c8e870(tribe) == 0) {
            (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0xaf899239, ldu32(p, 0x74), 0);
            return;
        }
        if (FUN_00c8e850(tribe) != 0) {
            (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x1088670e, ldu32(p, 0x74), 0);
        } else {
            (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x9f9c8136, ldu32(p, 0x74), 0);
        }
        return;
    }
    case 4:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0xbfffc8aa, ldu32(p, 0x74), 0);
        return;
    case 5:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x3ee93e5d, ldu32(p, 0x74), 0);
        return;
    case 6:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x2f96d59d, ldu32(p, 0x74), 0);
        return;
    case 7:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0xfb0e7c68, ldu32(p, 0x74), 0);
        return;
    case 8:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x76de3589, ldu32(p, 0x74), 0);
        return;
    case 9:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x5b47d20e, ldu32(p, 0x74), 0);
        return;
    case 10:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x2b5af9b8, ldu32(p, 0x74), 0);
        return;
    case 0xb:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x6c7ef657, ldu32(p, 0x74), 0);
        return;
    case 0xc:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x7e91c364, ldu32(p, 0x74), 0);
        return;
    case 0xd:
        (*(void(__thiscall**)(void*, u32, u32, int))((char*)vtbl(pose) + 0x9c))(pose, 0x6f50def7, ldu32(p, 0x74), 0);
        return;
    default:
        (*(void(__thiscall**)(void*, int))((char*)vtbl(pose) + 0xa4))(pose, 0);
        return;
    }
}

// @ 0x00cca880
void cTribeDisplayStrategy::FUN_00cca880(void* citizen, int a)
{
    u8* p = (u8*)this;
    u8* c = (u8*)citizen;
    if (c != 0) {
        (*(void(__thiscall**)(void*))vtbl(c))(c);
    }
    u8 nodeOut[4];
    FUN_00e5c780((char*)p + 0x94, nodeOut, &c);
    if (c != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(c) + 4))(c);
    }
    u8* node = *(u8**)nodeOut;
    if (node == p + 0x98) {
        return;
    }
    if (ld32(p, 0x78) == 0) {
        return;
    }
    u32 kind = (u32)CIT(c)->FUN_00c22dc0();
    if (a != (int)kind) {
        POSSE(*(void**)((char*)p + 0x78))->FUN_00cc90f0(c, (void*)a);
    }
    void* pose = (void*)POSSE(*(void**)((char*)p + 0x78))->FUN_00cc90a0(ldu32(node, 0x14));
    if (pose == 0) {
        return;
    }
    if (CIT(c)->FUN_00c232d0() != 0 && kind == 0) {
        void* img = FUN_008061c0(*(void**)((char*)p + 0x74), 0xc37a78d7);
        (*(void(__thiscall**)(void*, void*, int))((char*)vtbl(pose) + 0x94))(pose, img, 0);
    } else if ((int)kind >= 1) {
        void* o = FUN_00c9cec0(kind);
        void* img = *(void**)((char*)o + 0x20);
        if (img != 0) {
            void* im = FUN_008061c0(*(void**)((char*)p + 0x74), (u32)img);
            (*(void(__thiscall**)(void*, void*, int))((char*)vtbl(pose) + 0x94))(pose, im, 0);
        } else {
            STRAT(p)->FUN_00cc8a30(pose, c);
        }
    } else {
        STRAT(p)->FUN_00cc8a30(pose, c);
    }
    void* v = FUN_00cc8830(c);
    (*(void(__thiscall**)(void*, void*))((char*)vtbl(pose) + 0x88))(pose, v);
    if (CIT(c)->FUN_00c0b770() != 0) {
        void* ps = *(void**)((char*)p + 0x78);
        u32 k = (u32)POSSE(ps)->FUN_00cc88e0(CIT(c)->FUN_00c22dc0());
        POSSE(*(void**)((char*)ps + k * 4 + 8))->FUN_00e28230();
    } else {
        POSSE(*(void**)((char*)p + 0x78) ? *(void**)((char*)*(void**)((char*)p + 0x78) + 0x8 + 5 * 4) : 0)->FUN_00e28230();
    }
}

// @ 0x00cca9e0
char cTribeDisplayStrategy::SetGroundSpearTransform(char slot, u32 index, const void* xform, char ref)
{
    u8* p = (u8*)this;
    int b = (slot == 0);
    u8* arrBase = b ? ((u8*)p + 0x178) : ((u8*)p + 0x218);
    u8* arr = (u8*)p + b * 0x60;
    u32 count = (ldu32(arr, 0xc8) - ldu32(arr, 0xc4)) / 0x38;
    if (index < count) {
        u8* item = (u8*)(ldu32(arr, 0xc4) + (index * 0x38));
        ((CTransformOps*)item)->Assign(xform);
        *(u32*)(arrBase + index * 4) = (u32)ref;
        ((CModelInstSet*)(arr + 0xb8))->Update();
        return 1;
    }
    return 0;
}

// @ 0x00ccaa80
void cTribeDisplayStrategy::FUN_00ccaa80(void* arg)
{
    u8* p = (u8*)this;
    u8* node = *(u8**)((char*)p + 0x9c);
    u8* end = p + 0x98;
    if (node == end) {
        return;
    }
    do {
        void* cit = *(void**)((char*)node + 0x14);
        void* ps = *(void**)((char*)p + 0x78);
        void* key = *(void**)((char*)node + 0x10);
        u32 idx;
        if (CIT(cit)->FUN_00c0b770() == 0) {
            idx = 5;
        } else {
            switch (CIT(cit)->FUN_00c22dc0()) {
            case 0xb:
                idx = 0;
                break;
            case 1:
            case 2:
            case 3:
            case 9:
                idx = 2;
                break;
            case 4:
            case 5:
            case 6:
                idx = 1;
                break;
            case 7:
            case 8:
                idx = 3;
                break;
            default:
                idx = 4;
                break;
            }
        }
        void* pose = *(void**)((char*)ps + idx * 4 + 8);
        void* item = POSSE(pose)->FUN_00e24c90(cit);
        if (key != 0 && item != 0) {
            u32 a = (u32)CIT(key)->FUN_00c22dc0();
            u32 bb = (u32)CIT(arg)->FUN_00c22dc0();
            if (a == bb) {
                (*(void(__thiscall**)(void*, int))((char*)vtbl(item) + 0xb8))(item, 2);
            }
        }
        node = (u8*)FUN_00921580(node);
    } while (node != end);
}

// @ 0x00ccab80
void cTribeDisplayStrategy::FUN_00ccab80()
{
    u8* p = (u8*)this;
    u8* node = *(u8**)((char*)p + 0x9c);
    if (node == p + 0x98) {
        return;
    }
    do {
        void* cit = *(void**)((char*)node + 0x14);
        void* ps = *(void**)((char*)p + 0x78);
        void* key = *(void**)((char*)node + 0x10);
        u32 idx;
        if (CIT(cit)->FUN_00c0b770() == 0) {
            idx = 5;
        } else {
            switch (CIT(cit)->FUN_00c22dc0()) {
            case 0xb:
                idx = 0;
                break;
            case 1:
            case 2:
            case 3:
            case 9:
                idx = 2;
                break;
            case 4:
            case 5:
            case 6:
                idx = 1;
                break;
            case 7:
            case 8:
                idx = 3;
                break;
            default:
                idx = 4;
                break;
            }
        }
        void* pose = *(void**)((char*)ps + idx * 4 + 8);
        void* item = POSSE(pose)->FUN_00e24c90(cit);
        if (key != 0 && item != 0) {
            (*(void(__thiscall**)(void*, int))((char*)vtbl(item) + 0xb8))(item, 2);
        }
        node = (u8*)FUN_00921580(node);
    } while (node != p + 0x98);
}

// @ 0x00ccad10
void* CPool::FUN_00ccad10(u8* payload)
{
    u8* self = (u8*)this;
    u8* node = *(u8**)(self + 0x1c);
    if (node != 0) {
        *(u8**)(self + 0x1c) = *(u8**)node;
    } else {
        node = (u8*)op_new(*(u32*)(self + 0x2c), "Simulator", 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    }
    if (node != 0) {
        struct Payload { u32 a, b; void* p; u8 c; };
        Payload* np = (Payload*)node;
        Payload* pp = (Payload*)payload;
        np->a = pp->a;
        np->b = pp->b;
        void* p2 = pp->p;
        np->p = p2;
        if (p2 != 0) {
            (*(void(__thiscall**)(void*))vtbl(p2))(p2);
        }
        np->c = pp->c;
    }
    *(u32*)(node + 0x10) = 0;
    return node;
}

// @ 0x00ccad80
u8* FUN_00ccad80_impl(u8* first, u8* last, const void* key)
{
    int n = (int)(last - first) / 0x18;
    const u32* k = (const u32*)key;
    if (n > 0) {
        u32 k0 = k[0];
        u32 k1 = k[1];
        do {
            int half = n >> 1;
            u8* mid = first + half * 0x18;
            if (ldu32(mid, 4) <= k1 && (ldu32(mid, 4) < k1 || ldu32(mid, 0) < k0)) {
                first = mid + 0x18;
                half = n - (half + 1);
            }
            n = half;
        } while (n > 0);
    }
    return first;
}

// @ 0x00ccaf60
char __cdecl FUN_00ccaf60(void* self)
{
    u8* p = (u8*)self;
    u8* c = (u8*)self;
    void* a = (void*)(*(void*(__thiscall**)(void*))((char*)vtbl(c) + 0xc4))(c);
    if (a == 0) {
        return 1;
    }
    void* b = (void*)(*(void*(__thiscall**)(void*, u32))((char*)vtbl(a) + 0xc))(a, 0x4f176642);
    if (b != 0) {
        if (CIT(b)->FUN_00c0b770() != 0) {
            void* h = *(void**)((char*)p + 0x1c);
            (*(void(__thiscall**)(void*, void*, int))((char*)vtbl(h) + 0xa8))(h, c, 1);
            ((CStrategyOps*)p)->FUN_00cc8ed0(b);
            void* inst = FUN_00cd40b0();
            u32 k = (u32)CIT(b)->FUN_00c22dc0();
            void* r = (void*)(*(void*(__thiscall**)(void*, void*, u32))((char*)vtbl(inst) + 0x6c))(inst, b, k);
            ((cTribeDisplayStrategy*)r)->FUN_00cca880(b, (int)k);
            return 1;
        }
    }
    return 1;
}

// @ 0x00ccaff0
void cTDS::SendSelectMessage(void* key, uint32_t kind)
{
    AddRefOf(key);
    uint32_t k = (uint32_t)(uintptr_t)key;
    TreeIter it = mEffectTree.Find(&k);
    ReleaseOf(key);
    if (it.mpNode == (RBNode*)((uint8_t*)this + 0x98))
        return;
    void* m = FUN_00f473a0(0x40, 0x13f6b3c, 0, 0, 0, 0);
    if (m) {
        *(uint32_t*)((uint8_t*)m + 0x30) = 0x3e41916;
        *(void**)m = (void*)0x13eb90c;
        *(uint32_t*)((uint8_t*)m + 4) = 0;
        *(void**)m = (void*)0x13eb844;
        *(uint32_t*)((uint8_t*)m + 0x38) = 0;
        (*(void (__thiscall*)(void*))VF(m, 4))(m);
    } else {
        m = 0;
    }
    void* owner = it.mpNode->mValue.mpPosseObject;
    if ((*(uint8_t*)((uint8_t*)m + 0x38) & 1) && *(void**)((uint8_t*)m + 8))
        (*(void (__thiscall*)(void*))VF(*(void**)((uint8_t*)m + 8), 4))(*(void**)((uint8_t*)m + 8));
    *(void**)((uint8_t*)m + 8) = owner;
    AddRefOf(owner);
    *(uint32_t*)((uint8_t*)m + 0x38) |= 1;
    *(uint32_t*)((uint8_t*)m + 0x10) = kind;
    void* ms = FUN_0067dcc0();
    (*(void (__thiscall*)(void*, uint32_t, void*, int, int))VF(ms, 0x18))(
        ms, *(uint32_t*)((uint8_t*)m + 0x30), m, 0, 0);
    (*(void (__thiscall*)(void*))VF(m, 8))(m);
}

// @ 0x00ccb0f0
void cTDS::MaintainSelectionState(void* key)
{
    uint32_t k = (uint32_t)(uintptr_t)key;
    AddRefOf(key);
    TreeIter it = mEffectTree.Find(&k);
    ReleaseOf(key);
    if (it.mpNode == (RBNode*)((uint8_t*)this + 0x98))
        return;
    uint8_t* sub = (uint8_t*)key + 0xc0;
    uint32_t flags = 0;
    if ((*(uint8_t (__thiscall*)(void*))VF(sub, 0x50))(sub))
        flags = 1;
    if (((S00bfc5d0*)((uint8_t*)key + 0x5a8))->FUN_00bfc5d0() ||
        (*(uint8_t (__thiscall*)(void*))VF(sub, 0x24))(sub))
        flags |= 2;
    if (flags != it.mpNode->mValue.mUiState) {
        SendSelectMessage(key, flags);
        it.mpNode->mValue.mUiState = flags;
    }
}

// @ 0x00ccb2c0
void cTDS::FUN_00ccb2c0()
{
    void* posse = mpPosse;
    (*(void (__thiscall*)(void*, void*, void*))VF(posse, 0xa0))(posse, (void*)0x00ccaf60, this);
    void* mgr = FUN_00b3d300();
    void* tribe = ((S00bfc5f0*)mgr)->FUN_00bfc5f0();
    uint32_t maxPop = ((S00c8eae0*)tribe)->FUN_00c8eae0();
    uint32_t have = 0;
    void* v;
    if ((v = mpPosseVec0) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosseVec1) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosseVec2) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosseVec3) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosseVec4) != 0) have += ((PosseObject*)v)->mItems.Count();
    if ((v = mpPosse) != 0) have += ((PosseObject*)v)->mItems.Count();
    if (have < maxPop) {
        uint32_t n = maxPop - have;
        do {
            void* a = FUN_009512c0();
            void* p = FUN_009512d0(0x14c, 4, "UI/PosseItemTribeGhostShell", a);
            void* item = p ? ((S00e25b50*)p)->FUN_00e25b50() : 0;
            (*(void (__thiscall*)(void*, int))VF(item, 0x88))(item, 0xb);
            void* againPosse = mpPosse;
            (*(void (__thiscall*)(void*, void*))VF(againPosse, 0xa4))(againPosse, item);
            if (--n == 0) break;
        } while (true);
        ((S00cc8be0*)this)->FUN_00cc8be0();
        return;
    }
    if (maxPop < have) {
        uint32_t n = have - maxPop;
        do {
            void* item = ((S00e24c90*)mpPosse)->FUN_00e24c90(0);
            if (item) {
                void* p2 = mpPosse;
                (*(void (__thiscall*)(void*, void*, int))VF(p2, 0xa8))(p2, item, 1);
            }
            if (--n == 0) break;
        } while (true);
        ((S00cc8be0*)this)->FUN_00cc8be0();
    }
}

// @ 0x00ccb420
bool cTDS::HandleMessage(uint32_t id, void* msg)
{
    switch (id) {
    case 3: {
        void* p = *(void**)((uint8_t*)msg + 0x10);
        if (!p) break;
        void* o = FUN_00ac8730(p);
        if (!o) break;
        ((S00cc9460*)((uint8_t*)this - 0x38))->FUN_00cc9460(o);
        return true;
    }
    case 0x1ee100d: {
        void* v = mpMiniMapWin_38;
        if (!v) break;
        uint8_t* s = (uint8_t*)v + 4;
        (*(void (__thiscall*)(void*))VF(s, 0x90))(s);
        ((S00e0ad00*)v)->FUN_00e0ad00(4);
        return true;
    }
    case 0x1e8c9e0:
    case 0x58baddd: {
        ((S00cc9460*)((uint8_t*)this - 0x38))->FUN_00cc9460(*(void**)((uint8_t*)msg + 8));
        return true;
    }
    case 0x3deb129: {
        void* k = *(void**)((uint8_t*)msg + 8);
        if (!k) break;
        MemberNode* end = mpMemberEnd;
        MemberNode* it = mpMemberRoot;
        if (it == end) break;
        do {
            if (it->mpCreature == k) {
                uint8_t* s = (uint8_t*)it->mpStrategy;
                if (s[0xb5e] == 0) {
                    uint32_t flags = *(uint32_t*)((uint8_t*)msg + 0x10);
                    uint8_t* e = s + 0xc0;
                    if (flags & 1) {
                        (*(void (__thiscall*)(void*, int))VF(e, 0x54))(e, 1);
                        void* inst = FUN_00cd40b0();
                        if (!((S00cd4460*)inst)->FUN_00cd4460(0x56d1871)) {
                            if (((S00cd4460*)inst)->FUN_00cd4460(0x64be5ff))
                                ((S00cd6980*)inst)->FUN_00cd6980(0x64e70b3);
                        }
                    } else {
                        (*(void (__thiscall*)(void*, int))VF(e, 0x54))(e, 0);
                    }
                    ((S00bfc5e0*)(s + 0x5a8))->FUN_00bfc5e0((flags & 2) != 0);
                    ((cTDS*)((uint8_t*)this - 0x38))->MaintainSelectionState(it->mpStrategy);
                    void* cur = FUN_00b30d70();
                    (*(void (__thiscall*)(void*))VF(cur, 0x74))(cur);
                    cur = FUN_00b30d70();
                    (*(void (__thiscall*)(void*))VF(cur, 0xc8))(cur);
                }
            }
            it = (MemberNode*)FUN_00921580(it);
        } while (it != mpMemberEnd);
        return true;
    }
    case 0x3deb12a: {
        void* k = *(void**)((uint8_t*)msg + 8);
        if (!k) break;
        MemberNode* end = mpMemberEnd;
        MemberNode* it = mpMemberRoot;
        if (it == end) break;
        do {
            if (it->mpCreature == k) {
                void* inst = (void*)FUN_00cd40b0();
                (*(void (__thiscall*)(void*, int))VF((uint8_t*)inst, 0))((uint8_t*)inst, 0);
            }
            it = (MemberNode*)FUN_00921580(it);
        } while (it != mpMemberEnd);
        return true;
    }
    case 0x685ce6c: {
        uint8_t* base = *(uint8_t**)msg;
        bool f8 = (*(void**)((uint8_t*)msg + 8) == 0);
        void* v = *(void**)(base + 0x64);
        void* r = v ? (*(void* (__thiscall*)(void*, uint32_t))VF(v, 0xc))(v, 0x4f396a66) : 0;
        void* mgr = FUN_00b3d300();
        void* tribe = ((S00bfc5f0*)mgr)->FUN_00bfc5f0();
        if (!tribe || tribe != r) break;
        if (!f8) {
            void* m = FUN_00f473a0(0x40, 0x13ebc58, 0, 0, 0, 0);
            m = m ? FUN_00421c80(m, 0) : 0;
            FUN_0061df40(m);
            *(uint32_t*)((uint8_t*)m + 0x30) = 0x68b2082;
            *(void**)((uint8_t*)m + 8) = base;
            void* ms = FUN_0067dcc0();
            (*(void (__thiscall*)(void*, uint32_t, void*, int, int))VF(ms, 0x18))(ms, 0x68b2082, m, 0, 0);
            (*(void (__thiscall*)(void*))VF(m, 8))(m);
            return true;
        }
        void* e = (*(void* (__thiscall*)(void*))VF(tribe, 0xac))(tribe);
        if (!e) break;
        void* e2 = (*(void* (__thiscall*)(void*))VF((uint8_t*)e + 0x34, 0xac))((uint8_t*)e + 0x34);
        if (!e2) break;
        ((S00437f70*)e2)->FUN_00437f70(true);
        return true;
    }
    case 0x61ed580: {
        void* o = *(void**)((uint8_t*)msg + 8);
        if (!o) break;
        if (!mpObj_40) break;
        ((S00cc91e0*)mpObj_40)->FUN_00cc91e0(o);
        return true;
    }
    case 0x3e41917: {
        void* p = *(void**)((uint8_t*)this + 0x10);
        FUN_0075d4b0("c:\\dumpthumb.png", p, 1);
        return true;
    }
    case 0x68b2082: {
        uint8_t* base = *(uint8_t**)((uint8_t*)msg + 8);
        void* v = *(void**)(base + 0x64);
        void* r = v ? (*(void* (__thiscall*)(void*, uint32_t))VF(v, 0xc))(v, 0x4f396a66) : 0;
        void* mgr = FUN_00b3d300();
        void* tribe = ((S00bfc5f0*)mgr)->FUN_00bfc5f0();
        if (!tribe || tribe != r) break;
        FUN_00c99c30(tribe);
        void* e = (*(void* (__thiscall*)(void*))VF(tribe, 0xac))(tribe);
        if (!e) break;
        void* e2 = (*(void* (__thiscall*)(void*))VF((uint8_t*)e + 0x34, 0xac))((uint8_t*)e + 0x34);
        if (!e2) break;
        *(uint32_t*)((uint8_t*)e2 + 4) &= ~1u;
        break;
    }
    }
    return true;
}

// @ 0x00ccb810
Vec3D* Vec3D::Assign(Vec3D* other)
{
    if (other == this)
        return this;
    Vertex3D* ob = other->mpBegin;
    uint32_t n = (uint32_t)((char*)other->mpEnd - (char*)ob) / 0x18u;
    Vertex3D* tb = mpBegin;
    if (n > (uint32_t)((char*)mpCapacity - (char*)tb) / 0x18u) {
        Vertex3D* nb = Grow(n, ob, other->mpEnd);
        if (mpBegin)
            FUN_00f47380(mpBegin);
        mpCapacity = (Vertex3D*)((char*)nb + (n + n * 2) * 8);
        mpBegin = nb;
        mpEnd = (Vertex3D*)((char*)nb + (n + n * 2) * 8);
        return this;
    }
    int have = (int)((char*)mpEnd - (char*)tb) / 0x18;
    if ((uint32_t)have < (uint32_t)n) {
        Vertex3D* mid = (Vertex3D*)((char*)ob + (have + have * 2) * 8);
        FUN_00720250(ob, mid, tb);
        Vertex3D* e = other->mpEnd;
        void* scratch;
        FUN_00cca110(&scratch, mid, e, mpEnd, e);
        mpEnd = (Vertex3D*)((char*)mpBegin + (n + n * 2) * 8);
        return this;
    }
    FUN_00720250(ob, other->mpEnd, tb);
    mpEnd = (Vertex3D*)((char*)mpBegin + (n + n * 2) * 8);
    return this;
}

// @ 0x00ccba20
void Vec3D::InsertAt(Vertex3D* pos, Vertex3D* val)
{
    Vertex3D* end = mpEnd;
    if (end != mpCapacity) {
        if (val >= pos && val < end)
            val = (Vertex3D*)((char*)val + 0x18);
        if (end) {
            ((uint32_t*)end)[0] = ((uint32_t*)end)[-6];
            ((uint32_t*)end)[1] = ((uint32_t*)end)[-5];
            end->f[2] = ((Vertex3D*)((char*)end - 0x18))->f[2];
            end->f[3] = ((Vertex3D*)((char*)end - 0x18))->f[3];
            end->f[4] = ((Vertex3D*)((char*)end - 0x18))->f[4];
        }
        FUN_00cc8b50(pos, (Vertex3D*)((char*)end - 0x18), end);
        ((uint32_t*)pos)[0] = ((uint32_t*)val)[0];
        ((uint32_t*)pos)[1] = ((uint32_t*)val)[1];
        ((uint32_t*)pos)[2] = ((uint32_t*)val)[2];
        ((uint32_t*)pos)[3] = ((uint32_t*)val)[3];
        ((uint32_t*)pos)[4] = ((uint32_t*)val)[4];
        ((uint32_t*)pos)[5] = ((uint32_t*)val)[5];
        mpEnd = (Vertex3D*)((char*)mpEnd + 0x18);
        return;
    }
    Vertex3D* b = mpBegin;
    int n = (int)((char*)end - (char*)b) / 0x18;
    int cap2;
    if (n == 0) {
        cap2 = 1;
    } else {
        cap2 = n + n;
        if (cap2 == 0) {
            b = 0;
            goto alloc_done;
        }
    }
    b = (Vertex3D*)FUN_00f473a0((cap2 + cap2 * 2) * 8, 0x13f09b4, 0, 0, 0x13ebb38, 0xd1);
alloc_done:
    b = FUN_00cca1d0(mpBegin, pos, b);
    if (b) {
        ((uint32_t*)b)[0] = ((uint32_t*)val)[0];
        ((uint32_t*)b)[1] = ((uint32_t*)val)[1];
        ((uint32_t*)b)[2] = ((uint32_t*)val)[2];
        ((uint32_t*)b)[3] = ((uint32_t*)val)[3];
        ((uint32_t*)b)[4] = ((uint32_t*)val)[4];
    }
    Vertex3D* ne = FUN_00cca1d0(pos, mpEnd, b + 1);
    if (mpBegin)
        FUN_00f47380(mpBegin);
    mpBegin = b;
    mpEnd = ne;
    mpCapacity = (Vertex3D*)((char*)b + (cap2 + cap2 * 2) * 8);
}

// @ 0x00ccbb60
void cTDS::FUN_00ccbb60(void* key)
{
    if (mpMiniMapWin)
        ((S00e0f9c0*)mpMiniMapWin)->FUN_00e0f9c0(key, 1, 0);
    uint32_t k = (uint32_t)(uintptr_t)key;
    AddRefOf(key);
    TreeIter it = mEffectTree.Find(&k);
    ReleaseOf(key);
    if (it.mpNode != (RBNode*)((uint8_t*)this + 0x98)) {
        if (mpObj_78)
            ((S00cc9040*)mpObj_78)->FUN_00cc9040(key);
        uint32_t k2 = (uint32_t)(uintptr_t)key;
        AddRefOf(key);
        mEffectTree.Erase(&k2);
        ReleaseOf(key);
    }
}

// @ 0x00ccbc00
HashNode* Hashtable::FUN_00ccbc00(uint32_t* key)
{
    HashIter out;
    out.mpNode = 0; out.mpBucket = 0;
    Find(&out, key);
    if (out.mpNode == mpBuckets[mBucketCount]) {
        uint32_t keyval = *key;
        uint32_t flag = (uint32_t)(uintptr_t)key & 0xffffff00u;
        InsertNode(&out, &keyval, flag);
    }
    return (HashNode*)((uint8_t*)out.mpNode + 4);
}

// @ 0x00ccbc90
Vertex3D* Vec3D::Insert(Vertex3D* pos, Vertex3D* val)
{
    int idx = (int)((char*)pos - (char*)mpBegin) / 0x18;
    Vertex3D* end = mpEnd;
    if (pos == end && end != mpCapacity) {
        mpEnd = (Vertex3D*)((char*)end + 0x18);
        if (end) {
            ((uint32_t*)end)[0] = ((uint32_t*)val)[0];
            ((uint32_t*)end)[1] = ((uint32_t*)val)[1];
            end->f[2] = val->f[2];
            end->f[3] = val->f[3];
            end->f[4] = val->f[4];
        }
    } else {
        InsertAt(pos, val);
    }
    return (Vertex3D*)((char*)mpBegin + (idx + idx * 2) * 8);
}

// @ 0x00ccbd10
void cTDS::FUN_00ccbd10(void* a, Vector3* p, float f, int kind, bool b)
{
    (void)a;
    bool bVar4;
    uint8_t bVar5;
    if (g1582ff0 < f) {
        bVar4 = false;
        if (g1582ff4 < f) goto after_range;
        bVar5 = 1;
    } else {
        bVar4 = true;
after_range:
        bVar5 = 0;
    }
    uint32_t hash;
    switch (kind) {
    case 0:
        if (b) goto case3;
        hash = bVar4 ? 0x4ccc8e63u : ((uint32_t)(-(int)bVar5) & 0x60e181dc) + 0x8fbc1ed7;
        break;
    case 1:
        if (!b)
            hash = bVar4 ? 0xb69dc16au : ((uint32_t)(-(int)bVar5) & 0x879b0692) + 0xae79fece;
        else
            hash = bVar4 ? 0xa231da2fu : ((uint32_t)(-(int)bVar5) & 0xd8ed2874) + 0x7d2bf7a3;
        break;
    case 2:
        hash = bVar4 ? 0x3751cceau : ((uint32_t)(-(int)bVar5) & 0x22551592) + 0x2f2e0a4e;
        break;
    case 3:
case3:
        hash = bVar4 ? 0xb490e2ecu : ((uint32_t)(-(int)bVar5) & 0x2917cb66) + 0x59861ae4;
        break;
    default:
        return;
    }
    uint8_t* sub = mEffectSlot;
    Vector3 tmp;
    (*(Vector3* (__thiscall*)(void*, Vector3*, float, int))VF(sub, 0x74))(sub, &tmp, f, 1);
    void* body = (*(void* (__thiscall*)(void*))VF(sub, 0x2c))(sub);
    float dist = FUN_00d99a60(body);
    float weight = (g13ebc5c - dist) * g13ef53c;
    if (weight <= 0.5f) weight = 0.5f;
    if (weight >= g1485720) weight = g1485720;
    HashNode* e = mEffectCache.FUN_00ccbc00((uint32_t*)&tmp);
    void* h = e->mpValue;
    *(uint8_t*)((uint8_t*)e + 8) = 1;
    if (h == 0) {
newh:
        void* em = FUN_0067ddd0();
        if (e->mpValue) {
            void* old = e->mpValue;
            e->mpValue = 0;
            (*(void (__thiscall*)(void*))VF(old, 4))(old);
        }
        void* created = 0;
        uint8_t ok = (*(uint8_t (__thiscall*)(void*, uint32_t, int, void**))VF(em, 0x2c))(em, hash, 0, &created);
        if (ok) {
            h = created;
            *(uint32_t*)e = hash;
        } else {
            h = e->mpValue;
        }
        if (h == 0)
            return;
    } else if (h != (void*)*(uint32_t*)e) {
        (*(void (__thiscall*)(void*, int))VF(h, 0xc))(h, 1);
        h = 0;
        goto newh;
    }
    uint32_t n8 = 0, n4 = 0;
    Vector3 pos;
    pos = *p;
    n4 = n4 & ~4u;
    (void)n8;
    FUN_0041cb40(g169b160, g169b160);
    Vector3 src = *p;
    Vector3 normal;
    void* pm = FUN_00b3d350();
    FUN_00b7e3b0(pm, &normal, &src);
    Vector3 ortho;
    FUN_006985b0(&ortho, &normal);
    uint8_t m[0x24];
    FUN_0069b440(m, &normal, &ortho);
    n4 |= 2;
    g1471064 = f;
    (*(void (__thiscall*)(void*, void*))VF(h, 0x18))(h, &n4);
    uint8_t alive = (*(uint8_t (__thiscall*)(void*))VF(h, 0x10))(h);
    if (!alive)
        (*(void (__thiscall*)(void*, int))VF(h, 8))(h, 0);
    (void)normal; (void)m;
}

// @ 0x00ccc070
uint8_t* EffectTree::FindOrInsert(uint32_t* key)
{
    RBNode* end = (RBNode*)&mpEnd04;
    RBNode* root = (RBNode*)mpRoot0c;
    RBNode* pos = end;
    if (root) {
        uint32_t k = *key;
        do {
            if (*((uint32_t*)root + 4) < k)
                root = root->mpLeft;
            else {
                pos = root;
                root = root->mpRight;
            }
        } while (root);
    }
    if (pos != end && *((uint32_t*)pos + 4) <= *key)
        return (uint8_t*)pos + 0x14;
    uint32_t owned = *key;
    AddRefOf((void*)(uintptr_t)owned);
    uint32_t value[4];
    value[0] = owned; value[1] = 0; value[2] = 0; value[3] = 0;
    uint32_t flag = (uint32_t)(uintptr_t)key & 0xffffff00u;
    FUN_00ccb930((void*)&key, pos, value, (void*)(uintptr_t)flag);
    ReleaseOf((void*)(uintptr_t)owned);
    return (uint8_t*)(uintptr_t)key + 0x14;
}

