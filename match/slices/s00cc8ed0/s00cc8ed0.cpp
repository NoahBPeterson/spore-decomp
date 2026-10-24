// Slice s00cc8ed0 -- the tribe UI display strategy (SP::cTribeDisplayStrategy and the small UI
// strategy object it drives): posse-item construction, the six-slot child lookup helpers, the
// visibility switch, the icon/UI refresh helpers and a handful of small window lookups.
//
// Subject objects:
//   * the strategy object used by most functions of this slice: a vtable at +0, six child
//     cSPUIPosse pointers at +0x08..+0x1c, further UI pointers at +0x4c/+0x70/+0x78 and +0x2b8;
//   * the entity/ref handle passed in by the callers (vtable + slot 0x0c accessor, the
//     0x00c0b770 / 0x00c22dc0 state helpers);
//   * the cSPUIPosse child objects (their own vector range at +0xa4/+0xa8, FindItem at 0x00e24c90);
//   * the SP::cTribeModeStrategy singleton and the cSPUILayout window lookup used by the icon
//     helpers at the end of the slice.
//
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define PV(n) virtual void pv##n();

// --------------------------------------------------------------------------- opaque services
namespace SP { namespace cTribeModeStrategy {
    void* Instance();                                  // 0x00cd40b0
} }

// --------------------------------------------------------------------------- interfaces
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

inline float MinF(float a, float b) { return b > a ? a : b; }
inline float MaxF(float a, float b) { return a > b ? a : b; }

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

struct cSPUIEventLog {                          // SP::cSPUIEventLog
    void SetVisibility(int visible);            // 0x00dd8da0
};
namespace SP { cSPUIEventLog* EventLog(); }     // 0x00b3d3e0

struct CurMgr {                                 // CurMgr
    char FindLocal(unsigned id);                // 0x00801bb0
};
void* FUN_0067cab0();                           // 0x0067cab0

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

struct TribeStrategy {                          // the UI strategy object of this slice
    uint32_t mVt;                               // +0x000
    uint8_t  mPad04[0x08 - 0x04];
    Posse*   mChild[6];                         // +0x008 .. +0x01c  six posse slots
    uint8_t  mPad20[0x4c - 0x20];
    GlobalUI* m4C;                              // +0x04c  global UI
    uint8_t  mPad50[0x70 - 0x50];
    Gfx70*   m70;                               // +0x070
    uint8_t  mPad74[0x78 - 0x74];
    TribeStrategy* m78;                         // +0x078  nested strategy/list
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

// --------------------------------------------------------------------------- mode strategy / UI layout
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

struct cSPUILayout {
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

// --------------------------------------------------------------------------- retail globals
#define G_STR_UI_POSSEITEM ((const char*)0x01476a7c)   // "UI/PosseItem"
#define G_WIN_ID_A         ((int)0x04c61b50)
#define G_WIN_ID_B         ((int)0x04c61dd9)

#define G_TAG_ITEM_OWNER   ((uint32_t)0xee3f516e)      // owner tag queried before building an item
#define G_TAG_ITEM_STATE   ((int)0x03deb129)           // state tag queried before updating an item

namespace Simulator { struct cGameData; }
namespace SP {
    struct cGameNounManager {                       // SP::cGameNounManager
        Simulator::cGameData* GetPlayerTribe();     // 0x00bfc5f0
    };
    cGameNounManager* NounManager();                // 0x00b3d300
}
struct Entity;
struct EntityRange {                                // range handed out by the tribe's slot 0x90
    Entity** mBegin;                                // +0x00
    Entity** mEnd;                                  // +0x04
};

namespace Simulator { struct cGameData {            // the player's tribe
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35)
    virtual EntityRange* pv36();                    // +0x90  tribe members

    uint8_t mPad04[0x234 - 0x04];
    int32_t m234;                                   // +0x234  passed to FUN_00b6f0c0

    char FUN_00c8e870();                            // 0x00c8e870
    char FUN_00c8e850();                            // 0x00c8e850
}; }

void* FUN_009512c0();                                  // 0x009512c0
void* FUN_009512d0(int size, int align, const char* name, void* arg);   // 0x009512d0

struct cSPUIPosseItemTribe {                        // SP::cSPUIPosseItemTribe
    PosseItem* ctor(void* owner);                   // 0x00e25840  declared only; returns the live item
};
struct cSPUIPosseItemTribeBaby {                    // SP::cSPUIPosseItemTribeBaby
    PosseItem* ctor(void* owner);                   // 0x00e258d0
};

void* FUN_00cc8830(EntityRef* ref);                    // 0x00cc8830

// --------------------------------------------------------------------------- 0x00cc99b0 support
struct CameraCtl {                              // camera controller returned by 0x00b3d280
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

// --------------------------------------------------------------------------- 0x00cc8ed0
// Build the posse item for one tribe member: allocate it (tribe or baby flavour), register it with
// the display strategy, then push the item's tribe state back onto it.
// @ 0x00cc8ed0
void TribeStrategy::FUN_00cc8ed0(EntityRef* ref)
{
    PosseItem* item = 0;
    PosseItem* created;
    if (ref->FUN_00c0b770() != 0) {
        created = (PosseItem*)FUN_009512d0(0x150, 4, G_STR_UI_POSSEITEM, FUN_009512c0());
        if (created != 0) {
            created = (ref != 0)
                ? ((cSPUIPosseItemTribe*)created)->ctor(ref->pv3(G_TAG_ITEM_OWNER))
                : ((cSPUIPosseItemTribe*)created)->ctor(0);
        }
    } else {
        created = (PosseItem*)FUN_009512d0(0x150, 4, G_STR_UI_POSSEITEM, FUN_009512c0());
        if (created != 0) {
            created = ((cSPUIPosseItemTribeBaby*)created)->ctor(
                ref != 0 ? ref->pv3(G_TAG_ITEM_OWNER) : 0);
        }
    }
    if (created != 0) {
        created->pv0();
        item = created;
    }

    item->pv34(FUN_00cc8830(ref));

    int slot;
    if (ref->FUN_00c0b770() != 0) {
        slot = FUN_00cc88e0(ref->FUN_00c22dc0());
    } else {
        slot = 5;
    }
    mChild[slot]->pv41(item);

    PosseItem* state = item->pv3(G_TAG_ITEM_STATE);
    if (state != 0) {
        int value;
        Simulator::cGameData* tribe = SP::NounManager()->GetPlayerTribe();
        if (tribe->FUN_00c8e870() != 0) {
            value = (tribe->FUN_00c8e850() == 0) ? 1 : 0;
        } else {
            value = tribe->FUN_00c8e850() ? 2 : -1;
        }
        state->FUN_00e235e0(value);
    }

    FUN_00cc8be0();
    item->pv1();
}

// --------------------------------------------------------------------------- 0x00cc9cd0
// Age the spear/ornament timers: update the twenty interactive ornaments of both ornament slots
// of the mode strategy and subtract the elapsed time from both forty-entry timer tables.
// @ 0x00cc9cd0
void TribeStrategy::FUN_00cc9cd0(int elapsed)
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

// --------------------------------------------------------------------------- 0x00cc9040
// Look the entity's posse slot up (the 0x00c0b770 gate decides between the derived slot index and
// slot 5), find the item for the entity in that posse and add it back to the posse.
// @ 0x00cc9040
void TribeStrategy::FUN_00cc9040(EntityRef* ref)
{
    int slot;
    if (ref->FUN_00c0b770() != 0) {
        slot = FUN_00cc88e0(ref->FUN_00c22dc0());
    } else {
        slot = 5;
    }
    void* item = mChild[slot]->FindItem(ref);
    mChild[slot]->pv42(item, 1);
    FUN_00cc8be0();
}

// --------------------------------------------------------------------------- 0x00cc90a0
// Same slot lookup as FUN_00cc9040 but returns the item found in the posse.
// @ 0x00cc90a0
void* TribeStrategy::FUN_00cc90a0(EntityRef* ref)
{
    int slot;
    if (ref->FUN_00c0b770() != 0) {
        slot = FUN_00cc88e0(ref->FUN_00c22dc0());
    } else {
        slot = 5;
    }
    return mChild[slot]->FindItem(ref);
}

// --------------------------------------------------------------------------- 0x00cc90f0
// Re-home the item of the entity's current posse slot: look the slot for the entity and the slot for
// the given index up, and when they differ move the item over and re-run the posse-item pass.
// @ 0x00cc90f0
void TribeStrategy::FUN_00cc90f0(EntityRef* ref, int index)
{
    int currentSlot;
    if (ref->FUN_00c0b770() != 0) {
        currentSlot = FUN_00cc88e0(index);
    } else {
        currentSlot = 5;
    }

    int wantedSlot;
    if (ref->FUN_00c0b770() != 0) {
        wantedSlot = FUN_00cc88e0(ref->FUN_00c22dc0());
    } else {
        wantedSlot = 5;
    }

    if (currentSlot == wantedSlot) {
        return;
    }

    PosseItem* item = (PosseItem*)mChild[currentSlot]->FindItem(ref);
    bool wasTwo = (item->pv47() == 2);
    mChild[currentSlot]->pv42(item, 1);
    FUN_00cc8ed0(ref);
    if (wasTwo) {
        PosseItem* moved = (PosseItem*)mChild[wantedSlot]->FindItem(ref);
        moved->pv46(2);
    }
}

// --------------------------------------------------------------------------- 0x00cc91b0
// Broadcast the value to the six child slots that are present.
// @ 0x00cc91b0
void TribeStrategy::FUN_00cc91b0(int value)
{
    for (int i = 0; i < 6; i++) {
        Posse* child = mChild[i];
        if (child != 0) {
            child->pv48(value);
        }
    }
}

// --------------------------------------------------------------------------- 0x00cc91e0
// Compare the summed audio-item system value of the first five posse slots with the summed item
// range size and broadcast the matching tick to every present slot.
// @ 0x00cc91e0
void TribeStrategy::FUN_00cc91e0(int unused)
{
    int systemTotal = 0;
    int rangeTotal = 0;
    for (int i = 0; i < 6; i++) {
        if (i != 5 && mChild[i] != 0) {
            systemTotal += mChild[i]->GetSystem();
            rangeTotal += mChild[i]->mVec.Size();
        }
    }
    if (systemTotal == rangeTotal) {
        for (int i = 0; i < 6; i++) {
            Posse* child = mChild[i];
            if (child != 0) {
                child->FUN_00e21960();
            }
        }
    } else {
        for (int i = 0; i < 6; i++) {
            Posse* child = mChild[i];
            if (child != 0) {
                child->FUN_00e21980();
            }
        }
    }
}

// --------------------------------------------------------------------------- 0x00cc9270
// Union the bounds of every non-empty posse slot into *out: the x/y components are minimised and the
// z/w components maximised; the first non-empty slot seeds the result.
// @ 0x00cc9270
void TribeStrategy::FUN_00cc9270(Vector4* out)
{
    bool seeded = false;
    for (int i = 0; i < 6; i++) {
        Posse* child = mChild[i];
        if (child != 0 && child->mVec.Size() > 0) {
            if (seeded) {
                Vector4 bounds;
                Vector4* other = child->pv39(&bounds);
                out->x = MinF(out->x, other->x);
                out->y = MinF(out->y, other->y);
                out->z = MaxF(out->z, other->z);
                out->w = MaxF(out->w, other->w);
            } else {
                Vector4 bounds;
                Vector4* other = child->pv39(&bounds);
                out->x = other->x;
                seeded = true;
                out->y = other->y;
                out->z = other->z;
                out->w = other->w;
            }
        }
    }
}

// --------------------------------------------------------------------------- 0x00cc9360
// True when every present child slot (slot 5 excluded) has at least as many spare audio items as
// its vector range holds.
// @ 0x00cc9360
bool TribeStrategy::FUN_00cc9360()
{
    for (int i = 0; i < 6; i++) {
        if (i != 5 && mChild[i] != 0) {
            int count = (mChild[i]->mVec.mEnd - mChild[i]->mVec.mBegin) >> 3;
            if (mChild[i]->GetSystem() < (uint32_t)count) {
                return false;
            }
        }
    }
    return true;
}

// --------------------------------------------------------------------------- 0x00cc93b0
// Show/hide the strategy's UI: the global UI, the nested strategy's items, the embedded icon
// sub-object, the extra interface, the local player's HUD entry and finally the event log.
// @ 0x00cc93b0
void TribeStrategy::FUN_00cc93b0(int visible)
{
    if (m4C != 0) {
        m4C->SetVisibility(visible);
    }
    if (m78 != 0) {
        m78->FUN_00cc91b0(visible);
    }
    Gfx70* gfx = m70;
    if (gfx != 0) {
        gfx->mSub04.pv31(1, visible);
    }
    Iface2B8* extra = m2B8;
    if (extra != 0) {
        extra->pv11(visible);
    }
    if ((char)visible == 0) {
        CurMgr* mgr = (CurMgr*)FUN_0067cab0();
        if (mgr != 0) {
            mgr->FindLocal(0x1002);
        }
    }
    SP::EventLog()->SetVisibility(visible);
}

// --------------------------------------------------------------------------- 0x00cc9430
// Tear the six child slots down in reverse order and install the IEventModifier base vtable.
// @ 0x00cc9430
void TribeStrategy::FUN_00cc9430()
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

// --------------------------------------------------------------------------- 0x00cc9460
// Build the minimap icon of one tribe object: the kind comes from the object's own query, the position
// from its embedded window and the colour from the object's tint.
// @ 0x00cc9460
void TribeStrategy::FUN_00cc9460(TribeObj* obj)
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

// --------------------------------------------------------------------------- 0x00cc9740
// Add (or remove) the minimap icon for an entity: the icon kind picks the flag word, and the three
// resource parameters are copied into the 0x24-byte icon description handed to the minimap window.
// @ 0x00cc9740
void TribeStrategy::FUN_00cc9740(IWinText* entity, Vector3 pos, int32_t kind, int8_t show)
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

// --------------------------------------------------------------------------- 0x00cc9640
// Same icon description as above but the position comes from the entity's own sub-object, and the
// handle is retained by the icon so the window can keep drawing the nest marker.
// @ 0x00cc9640
void TribeStrategy::FUN_00cc9640(IWinText* entity, int8_t show)
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

// --------------------------------------------------------------------------- 0x00cc98e0
// Pick the ornament the given tribe object should draw its marker on: the first ornament whose
// 0x240 field has already run out, otherwise the one with the smallest positive 0x240 value, and
// finally move that ornament's icon target to the object's current position.
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

// --------------------------------------------------------------------------- 0x00cc9d50
// Drop the given entity's posse item out of the tribe display: remove its icon and push the item
// itself out of sight, then tag it so the next update re-adds it in the new slot.
// @ 0x00cc9d50
void TribeStrategy::FUN_00cc9d50(EntityRef* ref)
{
    Gfx70* gfx = m70;
    if (gfx != 0) {
        gfx->RemoveIcon(ref, 1, 0);
    }

    TribeStrategy* obj = m78;
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

// --------------------------------------------------------------------------- 0x00cc9830
// Set the mode of the window with the given id inside the current tribe UI layout; when the window
// is missing the call is made through the null pointer (retail really does dereference 0).
// @ 0x00cc9830
void FUN_00cc9830(int id, int value)
{
    ModeStrategy* inst = (ModeStrategy*)SP::cTribeModeStrategy::Instance();
    ModeView* view = inst->pv27();
    cSPUILayout* layout = (cSPUILayout*)view->m4C->GetBuffer();
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

// --------------------------------------------------------------------------- 0x00cc9890
// Show the "idle" window of the two tribe icon windows and hide the other, depending on whether the
// mode strategy is in state 1.
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

// --------------------------------------------------------------------------- 0x00cc99b0
// Per-frame UI update: mirror the four icon windows' visibility into the camera controller, poke the
// tribe events when the terrain keys appear, and hand the selected creature's animation and position
// to the strategy's animation target.
// @ 0x00cc99b0
void TribeStrategy::FUN_00cc99b0(uint32_t param_2)
{
    CameraCtl* camera = (CameraCtl*)FUN_00b3d280();
    if (m4C == 0 || camera == 0) {
        return;
    }

    cSPUILayout* layout = (cSPUILayout*)m4C->GetBuffer();
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
