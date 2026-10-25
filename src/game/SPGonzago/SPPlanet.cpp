// src/game/SPGonzago/SPPlanet.cpp -- migrated from slice(s) s0134f690, s01315a50, s00c73cb0, s00c72c60, s00b0c190, s00b09570, s00b047b0, s00b02830, s00b01690, s00b00520, s00afef10, s00ac0180 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlanet.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cFruit.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cSPEditorAnimatedCreatureData.h"
#include "SP/cTreeData.h"
#include "SP/cVarListSerializer.h"
#include <intrin.h>
#include "SP/cPlanet.h"
#include "SP/cVisiblePlanet.h"
#include "SP/cCivData.h"
#include "SP/cCombatant.h"
#include <new>

// ---- items of slice s00afef10 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
class cVector2 {
public:
    float x;    // +0x00
    float y;    // +0x04
    cVector2() {}
    cVector2(float fValue) : x(fValue), y(fValue) {}
};
class cVector3 {
public:
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
    cVector3() {}
    cVector3(float fValue) : x(fValue), y(fValue), z(fValue) {}
};
class cZeroVector3 {
public:
    uint32_t x;     // +0x00
    uint32_t y;     // +0x04
    uint32_t z;     // +0x08
    cZeroVector3() : x(0), y(0), z(0) {}
};
class IStream {
public:
    uint8_t mnPad00[0x04];  // +0x00
};
class IAVIStream {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual IStream* GetStream();   // +0x18
};
class cOutStream {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual IAVIStream* GetIO();    // +0x20
};
typedef void* (__cdecl* tGetValueFn)(void* pSelf);
class cValueHost {
public:
    uint8_t mnPad00[0x20];      // +0x00
    tGetValueFn mpfnGet;        // +0x20
};
class cTransform {
public:
    uint8_t mnPad00[0x0c];              // +0x00
    uint16_t mnFlags;                   // +0x0c
    uint16_t mnVersion;                 // +0x0e
    cVector3 mPosition;                 // +0x10
    void SetPosition(const cVector3* pPosition); // 0x00affde0
};
class cPtrItem {
public:
    uint8_t mnPad00[0x48];              // +0x00
    uint32_t mnField48;                 // +0x48
};
class cPtrVector {
public:
    cPtrItem** mpBegin;                 // +0x00
    cPtrItem** mpEnd;                   // +0x04
};
namespace SP {
class cTreeData_s00af_ef10 {
public:
    uint8_t mnPad00[0x74];      // +0x00
    float mFruitHeight;         // +0x74
    float GetFruitHeight() const; // 0x00aff240
};  // namespace SP
}
class RotSerial {
public:
    uint8_t mnPad00[0x38];      // +0x00
    void Load(IStream* pStream);  // 0x006b9230
    void Save(IStream* pStream);  // 0x006b9190
};
class cSerializeMgr;
class cSerializeItem {
public:
    VSLOT(0) VSLOT(1)
    virtual void Destroy(int32_t nFlags);              // +0x08
    VSLOT(3)
    virtual void WriteItem(cSerializeMgr* pMgr);       // +0x10
    VSLOT(5) VSLOT(6)
    virtual void ReadItem(cSerializeMgr* pMgr);        // +0x1c
    uint8_t mnPad04[0x7c];                             // +0x004
};
class cSerializeMgr {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual void End();                 // +0x1c
    virtual IAVIStream* GetIO();        // +0x20
};
class cSerializeItemList {
public:
    cSerializeItem* mpBegin;            // +0x00
    cSerializeItem* mpEnd;              // +0x04
};
class cKeyedValue {
public:
    uint8_t mnPad00[0x14];              // +0x00
    uint32_t mField14;                  // +0x14
    uint32_t mField18;                  // +0x18
    uint32_t mField1c;                  // +0x1c
    uint32_t GetValue(uint32_t nKey);   // 0x00aff250
};
class cObstacle {
public:
    uint8_t mnPad00[0x44];              // +0x00
    float mField44;                     // +0x44
};
class cObstacleMgr {
public:
    uint64_t MakeKey(uint32_t nA, uint32_t nB, uint32_t nC); // 0x00b72410
    cObstacle* FindById(uint64_t nKey);                      // 0x00b74e90
};
namespace Simulator {
class cDecalSubObject {
public:
    void* mpVtbl;                       // +0x00
    uint8_t mnPad04[0x1c];              // +0x04
    void* Cast(uint32_t nType);         // 0x00ac0320
    void Init();                        // 0x00ac0520
};
}
namespace Simulator {
class cCastSubObject {
public:
    void* mpVtbl;                       // +0x00
    void* Cast(uint32_t nType);         // 0x00ac0320
};
}
namespace Simulator {
extern void* gVtblFruit[];              // 0x0145c5c8
}
namespace Simulator {
extern void* gVtblFruit04[];            // 0x0145c5b4
}
namespace Simulator {
extern void* gVtblFruit34[];            // 0x0145c4f0
}
namespace Simulator {
extern void* gVtblFruit130[];           // 0x0145c4d0
}
namespace Simulator {
class cFruit {
public:
    void* mpVtbl00;                     // +0x000
    void* mpVtbl04;                     // +0x004
    uint8_t mnPad08[0x2c];              // +0x008
    cCastSubObject mSub34;              // +0x034
    uint8_t mnPad38[0x14];              // +0x038
    uint32_t mField4c;                  // +0x04c
    uint32_t mField50;                  // +0x050
    uint32_t mField54;                  // +0x054
    uint8_t mnPad58[0xd8];              // +0x058
    cDecalSubObject mDecal;             // +0x130
    uint32_t mField150;                 // +0x150
    uint32_t mField154;                 // +0x154
    uint32_t mnKey158;                  // +0x158
    uint32_t mField15c;                 // +0x15c
    uint32_t mField160;                 // +0x160
    uint32_t mField164;                 // +0x164
    uint32_t mField168;                 // +0x168
    uint8_t mnPad16c[0x1ba18c - 0x16c]; // +0x16c
    int32_t mnTimer;                    // +0x1ba18c

    void Initialize();                                  // 0x00aff280
    void Release();                                     // 0x00c3f850
    bool BaseWrite(cOutStream* pStream);                // 0x00c3fb00
    void* Cast(uint32_t nType);                         // 0x00aff330
    void Reset();                                       // 0x00aff370
    bool Write(cOutStream* pStream);                    // 0x00aff400
    void* CastOther(uint32_t nType);                    // 0x00aff520
    float GetObstacleValue();                           // 0x00aff550
    void AddTime(int32_t nUnused, int32_t nDelta);      // 0x00aff700
    void Finish();                                      // 0x00c3fa70
    void ResetState();                                  // 0x00c3f880
    void* CastBase(uint32_t nType);                     // 0x00c3f850
    void* CastVariant(uint32_t nType);                  // 0x00b18460
    cObstacleMgr* GetObstacleMgr();                     // 0x00b3d3c0
};
}
using Simulator::cFruit;
namespace SP {
class cSpatialObjectData {
public:
    uint8_t mnPad00[0x75];              // +0x000
    uint8_t mbActive;                   // +0x075
    bool IsActive();                    // 0x00c888c0
};
}
namespace SP {
class cSpatialObjectView {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10)
    virtual void* GetObject();          // +0x2c
    uint8_t mnPad04[0x08];              // +0x04
    cSpatialObjectData* mpData;         // +0x0c
    void HandleSimulationUpdate(uint32_t nA, uint32_t nB); // 0x00e92ca0
    void Update(uint32_t nA, uint32_t nB);                 // 0x00afffa0
};
}
static cVector2 const gDefaultVector2(0.0f); // 0x0167bab8
static uint8_t gDefaultByte = 0;             // 0x0167bae8
// ---- items of slice s00afef10 end

// ---- items of slice s00b00520 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IEntryRef {
public:
    virtual void v00();
    virtual void Release();      // 0x04
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
    virtual void Reset();        // 0x38
};
struct cSpatialEntry {
    int mpVtbl;                  // 0x00
    int mPad04;                  // 0x04
    int mField08;                // 0x08
    int mField0c;                // 0x0c
    IEntryRef* mpRef0;           // 0x10
    IEntryRef* mpRef1;           // 0x14
    int mField18;                // 0x18
    int mPad1c;                  // 0x1c
};
struct cPositionedObject {
    uint8_t mPad00[0x5c];        // 0x00
    float mX;                    // 0x5c
    float mY;                    // 0x60
    float mZ;                    // 0x64
};
struct cNode {
    uint8_t mPad00[0x10];        // 0x00
    float mX;                    // 0x10
    float mY;                    // 0x14
    float mZ;                    // 0x18
};
struct cTreeClumpData {
    uint8_t mPad00[0x08];        // 0x00
    uint8_t mBody[0x19a0];       // 0x08
};
class cTreeClump {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08(int bFlag);
    uint8_t mPad04[0x2c];
};
struct cTreeClumpVector {
    cTreeClump** mpBegin;        // 0x00
    cTreeClump** mpEnd;          // 0x04
    int* mpCapacity;             // 0x08
};
void DestroyTreeClumpData(cTreeClumpData* pClump, const void* pType, const wchar_t* pName);
void operator_delete__(void* pMemory);
// ---- items of slice s00b00520 end

// ---- items of slice s00b01690 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef signed int         i32;
typedef float              f32;
void* op_new(u32 size, const char* a, int b, int c, const char* d, int e); // 0x00f473a0
void  op_delete_array(void* p);                                          // 0x00f47380
struct CMatrix3Ops { void Assign(const void* src); };                    // 0x0041cb40
#define M3(p) ((CMatrix3Ops*)(p))
void  FUN_00c3f9b0(void);                                                // 0x00c3f9b0
void  FUN_00c3f9a0(u32);                                                 // 0x00c3f9a0
void  __stdcall FUN_00c3ff10(void*);                                    // 0x00c3ff10
void  __stdcall FUN_00c3fad0(void*);                                    // 0x00c3fad0
void  FUN_00ac0520(void);                                                // 0x00ac0520
void  FUN_00b184c0(void);                                                // 0x00b184c0
void* SP_cSpatialObjectView_ctor(void* p);                               // 0x00e92af0
void* SP_cInteractionTarget_ctor(void* p);                               // 0x00ac03d0
void* SP_GetCurrentGameMode(void);                                       // 0x00b5b800
void* SP_NounManager(void*);                                             // 0x00b3d300
void  FUN_00b3d320(void);                                                // 0x00b3d320
void* FUN_00b1daf0(void);                                                // 0x00b1daf0
void* SP_cGameNounManager_CreateNoun(void* key);                         // 0x00b20c60
void* SP_GetActiveTerrainSphere(void);                                   // 0x00f48aa0
void  SP_cHierGrid_Shutdown(void);                                       // 0x00704060
void  SP_cHierGrid_Init(void* self, const void* v, float f, int a, int b); // 0x00704260
struct CRBTreeFind { void find(const u32* key, u32* out); };             // 0x00e5c780
#define RBF(p) ((CRBTreeFind*)(p))
void  FUN_00a887b0(u32 a, u32 b);                                        // 0x00a887b0
void  FUN_00a057f0(void* a, const void* b);                              // 0x00a057f0
void* cProperty_GetBool(void* p);                                        // 0x0041e920
void* cProperty_GetInt(void* p);                                         // 0x0041e990
void* cProperty_GetFloat(void* p);                                       // 0x0041ea70
static f32 g_167af5c = 0.0f;             // 0x0167af5c
static f32 g_167af60 = 0.0f;             // 0x0167af60
static f32 g_167af64 = 0.0f;             // 0x0167af64
static u32 g_167b550 = 0;                // 0x0167b550
static f32 g_1567398 = 0.0f;             // 0x01567398
static f32 g_156739c = 0.0f;             // 0x0156739c
static f32 g_15673a0 = 0.0f;             // 0x015673a0
static u32 g_15673a4 = 0;                // 0x015673a4
static inline void** vtbl(const void* p) { return *(void***)p; }
static inline u8*    at(void* p, int o)  { return (u8*)p + o; }
static inline void  vcall0(void* obj, int off) { (*(void(__thiscall**)(void*))((char*)vtbl(obj) + off))(obj); }
struct Simulator_cTreeData {
    void* vtbl;                      // +0x00
    void* vtbl8;                     // +0x04
    u32   f08;                       // +0x08
    u16   f0c;                       // +0x0c
    u16   f0e;                       // +0x0e
    f32   f10;                       // +0x10
    f32   f14;                       // +0x14
    f32   f18;                       // +0x18
    f32   f1c;                       // +0x1c
    u32   m20[10];                   // +0x20..0x48 (matrix33 + pad)
    u32   f48;                       // +0x48
    u32   f4c;                       // +0x4c
    u32   f50;                       // +0x50
    u32   f54;                       // +0x54
    u32   f58;                       // +0x58
    u32   f5c;                       // +0x5c
    u32   f60;                       // +0x60
    u32   f64;                       // +0x64
    u32   f68;                       // +0x68
    f32   f6c;                       // +0x6c
    f32   f70;                       // +0x70
    f32   f74;                       // +0x74
    u32   f78;                       // +0x78
    u8    f7c;                       // +0x7c
    Simulator_cTreeData();
};
struct cFruitViewFactory {
    void* Create(void* owner);
};
struct Simulator_cFruit {
    void* vtbl;      // +0x00
    void* vtbl4;     // +0x04
    u32   m08[0xb];  // +0x08
    void* vtbl34;    // +0x34
    u32   m38[0x10]; // +0x38
    u32   f84;       // +0x84
    u32   f88;       // +0x88
    u8    f8c[0x19]; // +0x8c
    u8    fa5;       // +0xa5
    u32   m108;      // +0x108
    u8    pad10c[0x44];
    u32   f148;      // +0x148
    u32   f150;      // +0x150
    u32   f154;      // +0x154
    u32   f158;      // +0x158
    u32   f15c;      // +0x15c
    u32   f160;      // +0x160
    u32   f164;      // +0x164
    u32   f168;      // +0x168
    u32   f16c;      // +0x16c
    u8    m130[0x18];
    Simulator_cFruit();
};
struct cFruitOps1 {
    void Enable(void* arg);
};
struct cFruitOps2 {
    void Disable(void* arg);
};
struct Simulator_cFruitGroup {
    void* vtbl;       // +0x00
    void* vtbl4;      // +0x04
    u32   m08[0xb];   // +0x08
    void* vtbl34;     // +0x34
    u32   m38[5];     // +0x38
    u32   f4c;        // +0x4c
    u32   f50;        // +0x50
    u32   f54;        // +0x54
    u8    pad58[0x48];
    u32   fa0;        // +0xa0
    u32   fa4;        // +0xa4
    u8    padA8[0xf4];
    u32   f19c;       // +0x19c
    u8    pad1a0[0x24];
    u32   f1c4;       // +0x1c4
    u8    pad1c8[8];
    u32   f1d0;       // +0x1d0
    ~Simulator_cFruitGroup();
};
struct RefRecordOps {
    void* Assign(const void* src);
};
struct RefRecordOps2 {
    void* Assign2(const void* src);
};
struct cAppModeEditorBase {
    void HandleGameCommandMessage(void* arg);
};
struct NounCreator {
    void* GetOrCreate();
};
struct GridOwner {
    void Rebuild();
};
struct TreeApplyOps {
    void Apply(void* key, u32 id, u32 arg);
};
struct PairTreeOps {
    void Find(void* out, const u32* key);
};
struct RefRecordCtorStruct {
    void* Construct2(void* src);  // 0x00b01cb0
};
struct WrapperOps {
    void* Wrap(u32* src, void* inner);
};
// ---- items of slice s00b01690 end

// ---- items of slice s00b02830 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void*, int, unsigned);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern char gVtblFruitView[];         // 0x0145c6d0
extern char gVtblRegNodeSdtor[];                 // 0x0145c6c0
extern float g_HK_REAL_ONE;       // 0x01485720
extern char  g_matrixIdentity[];  // 0x0167b554
extern float g_zero3a[];          // 0x0167af5c, 0x0167af60, 0x0167af64
#pragma intrinsic(memset, memcpy)
typedef unsigned char  uint8;
typedef unsigned int   uint32;
void __cdecl FUN_00b014f0(void* first, void* last, int holeIndex, void* top, float* pos);
void __cdecl FUN_00b015c0(void* first, void* last, int holeIndex, void* top,
                          float px, float py, float pz);
void __cdecl FUN_00b01690(void* first, void* last, int holeIndex, void* top,
                          float px, float py, float pz);
struct Op {
    void* M18660();                    // 0x00b18660 SP::cGameData::cGameData
    void  M03d0();                     // 0x00ac03d0 SP::cInteractionTarget::cInteractionTarget
    void  M8550(int v);               // 0x00b18550 cGameData SetGameDataOwner2
    void* M2a690(uint32 a, uint32 b, uint32 c);  // 0x00b2a690
    void* M90410();                    // 0x00b90410
    void* M2830();                     // 0x00ad2830
    void* M1cb40(const void* src);     // 0x0041cb40 Matrix3::Assign
    void  M0ccb0(void* o);            // 0x0040ccb0 ComposeTransforms
    void  M44040();                    // 0x00434040 XformMsg::XformMsg
    void* M01090();                    // 0x00401090 GetSetting9 (ignores args)
    void* Mdf440(const void* key);     // 0x004df440 GetPlantProfile
    int   Md9070();                    // 0x004d9070
    void* Md9010(void* a);            // 0x004d9010
    void* Mc3e790();                   // 0x00c3e790
    void  M5c780(void* out, void* key); // 0x00e5c780 eastl::rbtree find (out, key)
    void  Me92660();                   // 0x00e92660 ~cSpatialObjectView
    void  M92850();                    // 0x00692850
    void* M537dc0(const void* src);    // 0x00537dc0 cSPTransformOps::Assign
};
void* __cdecl FUN_0067ddd0();
void __cdecl FUN_00f47380(void* p);
void __cdecl FUN_011e07ef(void (*fn)());
extern uint32 g_regNodeGuard;   // 0x0167bbdc
typedef void (__cdecl* VtFn)(void*, uint8);
inline void VtCall(void* obj, int slot, uint8 arg)
{
    uint8* a = *(uint8**)obj;            // obj->vtbl
    uint8* b = *(uint8**)a;              // vtbl->[0]
    VtFn fn = *(VtFn*)(b + slot);
    fn(obj, arg);
}
struct HeapNodeBig {
    uint32 pad00[0x5c / 4];
    float  x;           // +0x5c
    float  y;           // +0x60
    float  z;           // +0x64
};
struct HeapNodeSmall {
    uint32 pad00[0x10 / 4];
    float  x;           // +0x10
    float  y;           // +0x14
    float  z;           // +0x18
};
struct HeapNodePlain {
    float  x;           // +0x00
    float  y;           // +0x04
    float  z;           // +0x08
};
struct ScopedDtorEffect {
    uint32 pad00;         // +0x00
    uint32 flags;         // +0x04 (bit 31 = "detach without release")
    uint32 pad08[0x38 / 4];  // +0x08 .. +0x3f
    int    refcount;      // +0x40
};
struct cFruitView {
    void*  vtbl;         // +0x00
    uint32 pad[0x30 / 4];
    ScopedDtorEffect* mpEffect;  // +0x34
    cFruitView* ScopedDtor(uint8 del);
};
struct cFruitGroup {
    void*  vtbl00;           // +0x00  gVtblFruitGroup2
    void*  vtbl04;           // +0x04  gVtblFruitGroup3
    uint32 pad08[0x2c / 4];  // +0x08 .. +0x33
    void*  targetVtbl;       // +0x34  embedded cInteractionTarget vtable
    uint32 pad38[0x10 / 4];  // +0x38 .. +0x47
    uint32 m48;              // +0x48  low half of the 64-bit used-slot mask
    int    m4c;              // +0x4c  high half / -1 sentinel
    uint32 m50;              // +0x50  species key (init 0x3a8be428)
    int    m54;              // +0x54
    uint32 m58;              // +0x58  (low half m58, high half m5a)
    float  f5c;              // +0x5c  position x
    float  f60;              // +0x60  position y
    float  f64;              // +0x64  position z
    float  f68;              // +0x68  scale
    float  mRot[9];          // +0x6c  orientation matrix
    uint32 m90;              // +0x90  state flags
    uint32 m94;              // +0x94
    uint32 m98;              // +0x98
    uint32 m9c;              // +0x9c
    uint32 ma0;              // +0xa0
    void*  ma4;              // +0xa4  element cursor array base
    void*  ma8;              // +0xa8
    void*  mac;              // +0xac
    uint32 padb0[8 / 4];     // +0xb0 .. +0xb7
    uint32 mb8;              // +0xb8
    void*  mbc;              // +0xbc
    uint32 padc0[0xdc / 4];  // +0xc0 .. +0x19b
    void*  m19c;             // +0x19c  per-slot key array
    void*  m1a0;             // +0x1a0
    void*  m1a4;             // +0x1a4
    uint32 pad1a8[8 / 4];    // +0x1a8 .. +0x1af
    uint32 m1b0;             // +0x1b0
    void*  m1b4;             // +0x1b4
    uint32 pad1b8[0xc / 4];  // +0x1b8 .. +0x1c3
    uint32 m1c4;             // +0x1c4
    void*  m1c8;             // +0x1c8  tree pointer
    int    m1cc;             // +0x1cc  mode (1/2)
    void*  m1d0;             // +0x1d0  attached object handle
    void FillSlots(cFruitGroup* group);   // 0x00b033b0 (thiscall: ecx=this)
};
extern uint32 g_kResA0;    // 0x015673c0
extern uint32 g_kResA1;    // 0x015673c4
extern uint32 g_kResB0;    // 0x015673c8
extern uint32 g_kResB1;    // 0x015673cc
void __cdecl FUN_013c1e60();
struct RegNode {
    void* vtbl;              // +0x00
    void* M92f60(void* a);   // 0x00692f60 Construct
    char  Ma30c0();          // 0x00ab30c0
    void  M92850();          // 0x00692850
};
extern RegNode g_regNode;    // 0x0167bbc8
struct RegNodeThunk {
    void  M001b0();          // 0x00b001b0 (thiscall)
    void  M3550();           // 0x00b03550 (thiscall; ecx = &subobject at +4)
};
extern char gVtblFruitGroup2[];       // 0x0145c748
extern char gVtblFruitGroup3[];       // 0x0145c738
// ---- items of slice s00b02830 end

// ---- items of slice s00b047b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint;
void* make_heap_a(void* a, void* b, void* c, void* d);                     // 0x00b00cd0
void* sort_partition_a(void* a, void* b, void* c, int d);                  // 0x00b038e0
void  sort_by_distance(void* a, void* b, void* c, int d);                  // 0x00b04590
void* make_heap_b(void* a, void* b, void* c, float x, float y, float z,
                  float x2, float y2, float z2);                           // 0x00b00f50
void* sort_partition_b(void* a, void* b, void* c);                         // 0x00b03a20
void  sort_and_visit(void* a, void* b, void* c, float x, float y, float z); // 0x00b04670
void* make_heap_c(void* a, void* b, void* c, float x, float y, float z,
                  float x2, float y2, float z2);                           // 0x00b011f0
void* sort_partition_c(void* a, void* b, void* c);                         // 0x00b03b50
void* FUN_00b3d440_arg(void* p);                                           // 0x00b3d440 (1 stack arg)
void  remove_1st(void* vec);                                               // 0x00acca00
struct SimEnt {
    uint32_t pad00[2];        // +0x00
    void*    mpSub_08;        // +0x08
    uint32_t pad0c[5];        // +0x0c
    uint32_t mId_20;          // +0x20
    uint32_t pad24[3];        // +0x24
    uint32_t mFlags_30;       // +0x30
};
struct SimObj;
struct SelfOps {                       // 0x00c3fe70  (thiscall, ecx = SimObj)
    void Finish();
};
struct Sub130 {                        // 0x00ac0450  (thiscall, ecx = SimObj+0x130)
    void Init();
};
struct SimObj : SelfOps {
    uint32_t pad000[0x4c / 4];                 // +0x000 .. +0x048
    uint32_t mKeyId_4c;                        // +0x04c
    uint32_t mKeyPitch_50;                     // +0x050
    uint32_t mKeyIdx_54;                       // +0x054
    uint32_t pad058[(0x108 - 0x58) / 4];       // +0x058 .. +0x104
    void*    mpSub_108;                        // +0x108
    uint32_t pad10c[(0x130 - 0x10c) / 4];      // +0x10c .. +0x12c
    Sub130   mSub_130;                         // +0x130 (1-byte object -> padded to 4)
    uint32_t pad134[(0x148 - 0x134) / 4];      // +0x134 .. +0x144
    uint32_t mFlags_148;                       // +0x148
    uint32_t pad14c;                           // +0x14c
    uint32_t mA_150;                           // +0x150
    uint32_t mB_154;                           // +0x154
    uint32_t mId_158;                          // +0x158
    uint32_t mSel_15c;                         // +0x15c
    uint32_t mIdx_160;                         // +0x160
    uint32_t mE_164;                           // +0x164
    uint32_t mF_168;                           // +0x168
    uint32_t mG_16c;                           // +0x16c
    uint32_t pad170[(0x1b8e08 - 0x170) / 4];   // +0x170 .. +0x1b8e04
    // +0x1b8e08 .. +0x1e5ef is a large opaque region (the same offset as
    // +0x1e5f0 only when the object has no intervening members); modelled as
    // an unchecked byte span so the following members land exactly.
    uint8_t  mbFlag_1b8e08;                    // +0x1b8e08
    uint8_t  padBig[0x57E7];                   // +0x1b8e09 .. +0x1e5ef
    void*    mpTreeRoot_1e5f0;                 // +0x1e5f0
    void*    mpTreeHead_1e5f4;                 // +0x1e5f4

    void  fillSlot(SimEnt* ent);               // 0x00b04aa0
    void* findSlot(uint id, int species);      // 0x00b04ba0
    void* slotAt(uint id, int species, uint idx); // 0x00b04c20
    void  reset();                             // 0x00b05800
    void* curEntry();                          // 0x00b058a0
    uint  curEntryBits();                      // 0x00b058f0
};
// ---- items of slice s00b047b0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void* FUN_00b047b0(void** param_1, void** param_2, void** param_3, float px, float py, float pz);  // 0x00b047b0 (stays in the slice: not this object's)

// ---- items of slice s00b09570 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void *FUN_00b091d0(void *pThis);
extern "C" void *FUN_00b06cd0(void *pThis);
struct Fv16 {
    u32 *mpBegin;   // +0x00
    u32 *mpEnd;     // +0x04
    u32 *mpCap;     // +0x08
    u32  mPad0c;    // +0x0c
    u32  mPad10;    // +0x10
    u32  mCount;    // +0x14
    u32  mBuf[16];  // +0x18
    Fv16() { mpBegin = mBuf; mpEnd = mBuf; mpCap = mBuf + 16; mCount = 0; }
    Fv16(const Fv16 &src);             // 0x01011cc0 (out-of-line)
    Fv16 &operator=(const Fv16 &src);  // 0x01011cc0 (out-of-line)
};
struct Fv512 {
    u32 *mpBegin;   // +0x00
    u32 *mpEnd;     // +0x04
    u32 *mpCap;     // +0x08
    u32  mPad0c;    // +0x0c
    u32  mPad10;    // +0x10
    u32  mCount;    // +0x14
    u32  mBuf[512]; // +0x18
    Fv512() { mpBegin = mBuf; mpEnd = mBuf; mpCap = mBuf + 512; mCount = 0; }
    Fv512(const Fv512 &src);             // 0x00b07050 (out-of-line)
    Fv512 &operator=(const Fv512 &src);  // 0x00b07050 (out-of-line)
};
struct Scatter {
    float mX;         // +0x0000
    float mY;         // +0x0004
    float mZ;         // +0x0008
    float mSpread;    // +0x000c
    u32   mPad10;     // +0x0010
    u32   mPad14;     // +0x0014
    u32   mPad18;     // +0x0018
    u32   mPad1c;     // +0x001c
    u32   mPad20;     // +0x0020
    u32   mPad24;     // +0x0024
    u32   mPad28;     // +0x0028
    u32   mPad2c;     // +0x002c
    u32   mPad30;     // +0x0030
    u32   mPad34;     // +0x0034
    u32   mPad38;     // +0x0038
    u32   mPad3c;     // +0x003c
    u32   mFlag40;    // +0x0040
    Fv16  mSmall0;    // +0x0044
    Fv16  mSmall1;    // +0x009c
    Fv16  mSmall2;    // +0x00f4
    float mTimerA;    // +0x014c
    float mTimerB;    // +0x0150
    u32   mPad154;    // +0x0154
    Fv512 mBig0;      // +0x0158
    Fv512 mBig1;      // +0x0970
    Fv512 mBig2;      // +0x1188
    Scatter(const Scatter &src);            // ctor
    Scatter &AssignFrom(const Scatter &src); // assign
    char F09740(u32 param_2);               // 0x00b09740
};
struct Mgr {
    u32   mPad00[13];     // +0x0000
    float mSpawnX;        // +0x0034
    float mSpawnY;        // +0x0038
    float mSpawnZ;        // +0x003c
    u32   mPad40;         // +0x0040
    u32   mPad44[2];      // +0x0044
    u32   mSelA;          // +0x004c
    u32   mSelB;          // +0x0050
    u32   mSelC;          // +0x0054
    float mSoundX;        // +0x005c
    float mSoundY;        // +0x0060
    float mSoundZ;        // +0x0064
    u32   mPad68[15];     // +0x0068
    u32  *mpSpots;        // +0x00a4  array of 0x38-byte spots
    u32   mPadA8[61];     // +0x00a8
    u32  *mpIndexA;       // +0x019c
    u32   mPadA0[10];     // +0x01a0
    u32  *mpIndexB;       // +0x01c8
    u32   mPad1cc[22733]; // +0x01cc .. +0x164ff
    u32  *mpGrid;         // +0x16500  sphere-query grid
    u32   mPad16504[38];  // +0x16504 .. +0x1659b
    u32   mCount1659c;    // +0x1659c
    u32   mPad165a0[428573]; // +0x165a0 .. +0x1b8e13
    u32  *mpTreesBegin;   // +0x1b8e14
    u32  *mpTreesEnd;     // +0x1b8e18
    u32   mPad1b8e1c[1243]; // +0x1b8e1c .. +0x1ba187
    u32   mFlagsA;        // +0x1ba188
    u32   mFlagsB;        // +0x1ba18c
    Scatter *Place(u32 index, int *pOut);                          // 0x00b09830
    void  RemoveAllNouns();                                        // 0x00b09b00
    Scatter *PlaceIndexed(Scatter *pTree, u32 index, u32 param_3);  // 0x00b09b80
    void  UpdateFruit(int period);                                 // 0x00b09bf0
    char  SerializeMgr(u32 param_2);                               // 0x00b0a040
    void  QueryTrees(float *pPos, void **ppVec, u32 mask, float radius,
                     int sort, float *pSortPos, int needFruit);    // 0x00b0a0c0
};
extern "C" void *SP__cVarListSerializer__ctor(void *pThis, void *a, const char *s, u32 n);
extern "C" char  SP__cVarListSerializer__Serialize(void *pThis, u32 a);
// ---- items of slice s00b09570 end

// ---- items of slice s00b0c190 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cPlanetRecord;
class cPlanetRecordTable;
class cPlanetObjectData;
class cSlotObject;
class cObjectKey;
class cPlanetManager;
class cNoun;
class cHierGrid;
class cWorld;
extern void __stdcall SetSelectedKey(const cObjectKey* pKey);                   // 0x00b01db0
extern void RemoveHandler(int nHandler, uint nKey0, uint nKey1, uint nKey2, uint nKey3);
extern const cObjectKey sNullKey;                                              // 0x01654c08
class cSlotObject
{
 public:
    virtual int AddRef();                      // +0x00
    virtual int Release();                     // +0x04
    virtual uint SaveToTag(uint nTag);         // +0x08
    virtual int ReleaseRef(bool bForce);       // +0x0c
    virtual void v10();                        // +0x10
    virtual void v14();                        // +0x14
    virtual void v18();                        // +0x18
    virtual void v1c();                        // +0x1c
    virtual void v20();                        // +0x20
    virtual void v24();                        // +0x24
    virtual void v28();                        // +0x28
    virtual void v2c();                        // +0x2c
    virtual void v30();                        // +0x30
    virtual void v34();                        // +0x34
    virtual void v38();                        // +0x38
    virtual void v3c();                        // +0x3c
    virtual void v40();                        // +0x40
    virtual void v44();                        // +0x44
    virtual void v48();                        // +0x48
    virtual void v4c();                        // +0x4c
    virtual void v50();                        // +0x50
    virtual void v54();                        // +0x54
    virtual void v58();                        // +0x58
    virtual void v5c();                        // +0x5c
    virtual void AddRefShared();               // +0x60
};
class cSlotObjectList
{
 public:
    cSlotObject** mBegin;   // +0x00
    cSlotObject** mEnd;     // +0x04
};
struct cRecordSubObject
{
    char mBody[0x58];
};
class cPlanetObjectData
{
 public:
    float mPosition[3];              // +0x00
    float mHeight;                   // +0x0c
    uint mObjectKey;                 // +0x10
    uint mValue14;                   // +0x14
    uint mValue18;                   // +0x18
    uint mValue1c;                   // +0x1c
    char mPad20[0x24];               // +0x20
    cRecordSubObject mSubA;          // +0x44
    cRecordSubObject mSubB;          // +0x9c
    cRecordSubObject mSubC;          // +0xf4
    float mScaledHeight;             // +0x14c
    float mScale;                    // +0x150
    char mBody[0x19a0 - 0x154];      // +0x154
};
struct cPlanetRecord
{
    uint mKey;                       // +0x00
    uint mPad;                       // +0x04
    cPlanetObjectData mData;         // +0x08
};
class cPlanetRecordTable
{
 public:
    cPlanetRecord* Insert(cPlanetRecord* pPos, const uint* pKey);
    cPlanetRecord* InsertRecord(cPlanetRecord* pPos, const uint* pKey);   // 0x00b0c110
    cPlanetObjectData* FindOrCreate(const uint* pKey);
    void ReleaseAll();

    cPlanetRecord* mBegin;           // +0x0000
    cPlanetRecord* mEnd;             // +0x0004
    char mBody[0x19a810];            // +0x0008 (rest of the planet data block)
    bool mbSorted;                   // +0x19a818
};
struct cTrackedTreeNode
{
    char mBody[0x28];                // +0x00
    cSlotObject* mpObject;           // +0x28
    cTrackedTreeNode* Next() const;  // 0x00921580
};
class cTrackedTree
{
 public:
    cTrackedTreeNode* First() const;   // 0x00b09510
    cTrackedTreeNode* End() const { return (cTrackedTreeNode*)&mpAnchorBegin; }
    void Reset()
    {
        mpAnchorBegin = &mpAnchorBegin;
        mpAnchorEnd = &mpAnchorBegin;
        mpRoot = 0;
        mbFlag = false;
        mCount = 0;
    }

    char mPad00[4];                  // +0x00
    void* mpAnchorBegin;             // +0x04
    void* mpAnchorEnd;               // +0x08
    cTrackedTreeNode* mpRoot;        // +0x0c
    bool mbFlag;                     // +0x10
    uint mCount;                     // +0x14
};
struct cEffect
{
    char mBody[0x10];                // +0x00
    cSlotObject* mpObject;           // +0x10
    char mTail[0x0c];                // +0x14
};
class cEffectList
{
 public:
    void Clear();

    cEffect* mBegin;                 // +0x00
    cEffect* mEnd;                   // +0x04
};
class cNoun
{
 public:
    virtual void v00();              // +0x00
    virtual int Release();           // +0x04
};
class cNounList
{
 public:
    void EraseFirst()
    {
        cNoun** pp = mBegin + 1;
        for (; pp < mEnd; ++pp)
            pp[-1] = pp[0];
        --mEnd;
        cNoun* pNoun = *mEnd;
        if (pNoun != 0)
            pNoun->Release();
    }

    cNoun** mBegin;                  // +0x00
    cNoun** mEnd;                    // +0x04
};
class cHierGrid
{
 public:
    bool Shutdown();                 // 0x00704060
};
class cWorld
{
 public:
    void Shutdown();                 // 0x007cd990
};
class cSlotContainer
{
 public:
    void* mBegin;                    // +0x00
    void* mEnd;                      // +0x04
};
class cPlanetManager
{
 public:
    void Unload(bool bUnloadRecords);
    void SetCurrentKey(const cObjectKey* pKey);
    void ClearContainer(cSlotContainer* pContainer, void* pArg2, void* pArg3); // 0x00b068c0
    cSlotObject** UnloadTrackedObject(cSlotObject** ppObject);                // 0x00b06a40
    void RefreshFromSelection();                                              // 0x00b0b150

    char mPad00[0x20];               // +0x0000
    int mHandlerId;                  // +0x0020
    uint mHandlerKey[4];             // +0x0024
    cSlotContainer mContainerA;      // +0x0034
    char mGap3c[0x8080 - 0x003c];    // +0x003c
    cTrackedTree mTracked;           // +0x8080
    char mGap8098[0x160e8 - 0x8098]; // +0x8098
    cEffectList mEffects;            // +0x160e8
    char mGap160f0[0x16500 - 0x160f0];  // +0x160f0
    cHierGrid* mpHierGrid;           // +0x16500
    char mGap16504[0x165a0 - 0x16504];  // +0x16504
    cSlotContainer mContainerB;      // +0x165a0
    char mGap165a8[0x1e5f0 - 0x165a8];  // +0x165a8
    cPlanetRecordTable mRecords;     // +0x1e5f0
    char mGap1b8e0c[0x1b8f2c - 0x1b8e0c];   // +0x1b8e0c
    const cObjectKey* mpCurrentKey;  // +0x1b8f2c
    cWorld* mpWorld;                 // +0x1b8f30
    char mGap1b8f34[0x1b8f44 - 0x1b8f34];   // +0x1b8f34
    cNounList mNouns;                // +0x1b8f44
    char mGap1b8f4c[0x1b905c - 0x1b8f4c];   // +0x1b8f4c
    cSlotObjectList mTrackedObjects; // +0x1b905c
    char mGap1b9064[0x1b9174 - 0x1b9064];   // +0x1b9064
    cNounList mExtraNouns;           // +0x1b9174
    char mGap1b917c[0x1ba18c - 0x1b917c];   // +0x1b917c
    uint mFlags;                     // +0x1ba18c
};
struct cPlanetObjectSpawn
{
    uint mUnknown00;                 // +0x00
    float mDirection[3];             // +0x04
    float mHeight;                   // +0x10
    char mRest[0x4c - 0x14];         // +0x14
};
class cPlanetObjectMessage
{
 public:
    cPlanetObjectSpawn* mpSpawns;    // +0x00
    char mPad04[4];                  // +0x04
    uint mnSpawns;                   // +0x08
    char mPad0c[0x14];               // +0x0c
    uint mBaseIndex;                 // +0x20
};
class cMessageHandler
{
 public:
    virtual bool DoMessage(uint nMessageId, cPlanetObjectMessage* pMessage); // 0x007cf8d0
};
class cKeyChangeNotifier : public cMessageHandler
{
 public:
    void Shutdown();
    bool DoMessage(uint nMessageId, cPlanetObjectMessage* pMessage);

    cPlanetManager* Owner() const
    {
        return reinterpret_cast<cPlanetManager*>(reinterpret_cast<char*>(
            const_cast<cKeyChangeNotifier*>(this)) - 4);
    }

    char mGap04[0x18];               // +0x04
    int mHandlerId;                  // +0x1c
    uint mHandlerKey[4];             // +0x20
};
// ---- items of slice s00b0c190 end

// ---- items of slice s00c72c60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_01693efc, g_01693f00, g_01693f04;
extern void* vtbl_CPlanet_014725d8;
extern void* vtbl_CPlanet_gd_01472580;
extern void* vtbl_CPlanet_d8_01472570;
void  StrAppendSprintf(void* s, const char* fmt, ...);               // 0x005f9450
void* FUN_00ecdba0(void* p);                                        // 0x00ecdba0
int   FUN_00b8dab0(void* p);                                        // 0x00b8dab0
void* SP_StarManager_00b3d2a0(void* p);                             // 0x00b3d2a0
void* cStarManager_GetEmpireByID_00ba9370(void* sm);                // 0x00ba9370
void* cEmpire_DebugArchetype_00c30eb0(void* e);                     // 0x00c30eb0
void* FUN_00f473a0(int size, const char* file, int a, int b, int c, int d); // 0x00f473a0
void* FUN_00c72540(void* a, void* b, void* c, int d);               // 0x00c72540
void* FUN_00bef6c0(void);                                           // 0x00bef6c0
void* FUN_00ff0db0(int v);                                          // 0x00ff0db0
void* FUN_00ff23b0(int v);                                          // 0x00ff23b0
void* FUN_00ff3220(void* a, void* b, void* c);                      // 0x00ff3220
void  FUN_00bd81e0(void* p);                                        // 0x00bd81e0
void* FUN_00bd81f0(void* p);                                        // 0x00bd81f0
void  FUN_00a110b0(void* p, void* q);                               // 0x00a110b0
void  FUN_00c9eae0(void* p);                                        // 0x00c9eae0
void  FUN_00b8eec0(void* p);                                        // 0x00b8eec0
void* SP_NounManager_00b3d300();                                    // 0x00b3d300 (no args)
void  cGameNounManager_RemoveNoun_00b225d0(void* mgr, void* noun);  // 0x00b225d0
struct CommRef_00ce6950 { void* GetCommContext(); };                // 0x00ce6950 (ecx=self)
struct TerrainSphere_00f67d90 { void* GetCurrentTerrainSphere(); }; // 0x00f67d90 (ecx=nounmgr)
struct CivData_005c65e0 { void* GetCities(); };                     // 0x005c65e0 (ecx=civ)
struct PtrPair { int* begin; int* end; };
void  DoInsertValue_00ac9200(void* a);                              // 0x00ac9200
void  FUN_00acb810(void* cur, void* v);                             // 0x00acb810
struct VecH_00b96600 { void Push(void* cur, const void* v); };            // 0x00b96600
struct VecH_004e3e10 { void GrowAndAppend(void* pos, const void* v); };   // 0x004e3e10
struct EaVec3 { void* begin; void* end; void* cap; void erase(void* first, void* last); };
void  FUN_00533500(void* a, void* b);                               // 0x00533500
void  cGonzagoTimer_dtor_00b638b0(void* p);                         // 0x00b638b0
void  cGameData_dtor_00b184c0(void* p);                             // 0x00b184c0
void  FUN_00c8a420(void);                                           // 0x00c8a420
void  FUN_00c72d00(void* a, void* b);                               // 0x00c72d00
void  FUN_00ba70d0(void* p);                                        // 0x00ba70d0
void  WStr_Assign(void* vec3, const uint16_t* src);                 // helper (not a slice VA)
void* SP_cGameNounManager_GetGameDataVector(void* mgr, void* f1, void* f2, void* f3, void* f4, void* id); // 0x00b21340
void  FUN_00b8de60(void* p);                                        // 0x00b8de60
void  FUN_00b8df20(void* p);                                        // 0x00b8df20
void  FUN_00c8ea30(void* p, void* d);                               // 0x00c8ea30
void  FUN_00b8ef00(void* p, void* d);                               // 0x00b8ef00
void* cTribeData_ctor_00ff0610(int v);                              // 0x00ff0610
struct PlanetMap_00c729b0 { void find_00c729b0(void* out, void* key); };  // 0x00c729b0 (ecx=this)
void  FUN_00705250(void* dst, void* end, void* src);                // 0x00705250
void  FUN_00c723d0_local(void* self);                               // 0x00c723d0
void  FUN_00c8b2e0_00(void);                                        // 0x00c8b2e0
void* FUN_00d01260(void* a, void* b, void* c, int d);               // 0x00d01260
void  FUN_004b5440(void* p);                                        // 0x004b5440
struct PlanetCls {
    void AddDebugInfo_00c72c60(void* str);
    void AddDebugInfo_00c72ce0(void* str);
    bool FUN_00c72d70(int key);
    void FUN_00c72dd0(int v);
    void FUN_00c72e10(char* pd);
    bool FUN_00c73250();
    void FUN_00c73270(int* key);
    void FUN_00c732c0(int* key);
    void FUN_00c73310();
    void FUN_00c73330();
    int FUN_00c73350(int* key);
    void FUN_00c733b0();
    void** FUN_00c73520(void** out);
    int* FUN_00c735e0(int* key);
    void FUN_00c73680();
    void FUN_00c73b60();
};
// ---- items of slice s00c72c60 end

// ---- items of slice s00c73cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* NounManager();                                                       // 0x00b3d300
void* eastl_lower_bound(void* b, void* e, void* k, unsigned char c);       // 0x00ba2e50
void* FUN_00ba57f0(void* key, int n);                                      // 0x00ba57f0
void* FUN_00ba5650(void* key, int n);                                      // 0x00ba5650
void* __stdcall FUN_00b3d4f0(void* x);                                     // 0x00b3d4f0
void  NotifyScannedCreatureSpecies(void* key, int flag);                   // 0x01058460
struct Notifier { void Notify(); };
struct EaMap {
    void*         begin;          // +0x00
    void*         end;            // +0x04
    char          mPad08[0x0c];   // +0x08
    unsigned char mCmp14;         // +0x14
    char          mPad15[3];      // +0x15
    void* find(void* key);              // 0x00ba4e60  thiscall, ret 4
    void  find(void* out, void* key);   // 0x00c729b0  thiscall, ret 8
    void* insert(void* key);            // 0x00ba4520  thiscall, ret 4
};
struct EaVec { void* begin; void* end; };  // two-pointer eastl vector
struct Key12 { unsigned k0, k1, k2; };
inline bool KeyLess(const void* a, const void* b)
{
    const unsigned* x = (const unsigned*)a;
    const unsigned* y = (const unsigned*)b;
    if (x[0] != y[0]) return x[0] < y[0];
    if (x[2] != y[2]) return x[2] < y[2];
    return x[1] < y[1];
}
struct ComCtxRef {                 // the planet data reached through cPlanet::+0x13c
    char  mPad00[0xbc];            // +0x000
    EaVec mVecBC;                  // +0x0bc  scanned-key vector A (12-byte records)
    char  mPadC4[0xd0 - 0xc4];     // +0x0c4
    EaVec mVecD0;                  // +0x0d0  scanned-key vector B
    char  mPadD8[0x15c - 0xd8];    // +0x0d8
    EaVec mCivVec;                 // +0x15c  vector<cCivData*>
    char  mPad164[0x184 - 0x164];  // +0x164
    void* mCommCtx;                // +0x184
    void* GetCommContext();        // 0x00ce6950  returns mCommCtx
};
struct NounMgr {                   // SP::NounManager() result
    void* GetCurrentTerrainSphere();   // 0x00f67d90  returns this->+0x74
    void* FUN_00b25f40(int id);        // 0x00b25f40
    void  RemoveNoun(void* noun);      // 0x00b225d0
};
struct ScanNode {                  // rbtree node of ComCtxRef's +0x11c0 map
    char mPad00[8];                // +0x000
    EaMap mMaps[5];                // +0x008 species / +0x20 / +0x38 / +0x50 / +0x68
    char mPad80[0xa2 - 0x80];      // +0x080
    unsigned char mFlagA2;         // +0x0a2
};
struct PlanetCls_s00c7_3cb0 {                 // SP::cPlanet / current terrain sphere
    char       mPad00[0x13c];      // +0x000
    ComCtxRef* mPData;             // +0x13c
    char       mPad140[0x11c0 - 0x140]; // +0x140
    EaMap      mScanned;           // +0x11c0

    void* FUN_00c73cb0(void* key);                 // +0x20 entry of a scanned map
    void* FUN_00c73cd0(void* key);                 // +0x68 entry of a scanned map
    void  FUN_00c73cf0(int flag);                 // scan the two key vectors into maps[0]
    char  SetSpeciesAsScanned(void* key);
    char  IsSpeciesScanned(void* key);
    void  FUN_00c73f80(void* key);
    void  FUN_00c73ff0();
    char  FUN_00c741a0(void* key);
    void  FUN_00c74210(void* key);
    void  FUN_00c74280();
    char  FUN_00c74400(void* key);
    void  FUN_00c74470(void* key);
    char  FUN_00c744e0(unsigned* key);
    char FUN_00c74550(unsigned* key);
    void  FUN_00c745d0(char flag, void* key);
    void  FUN_00c74650();
    void  FUN_00c74690(void* key, char b2, char b3);
    void  FUN_00c74730(void* k1, void* k2);
    int   FUN_00c73350(int* key);                  // defined in slice s00c72c60 0x00c73350
    void* FUN_00c735e0(void* key);                 // defined in slice s00c72c60 0x00c735e0
};
// ---- items of slice s00c73cb0 end

// ---- items of slice s01315a50 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0131_5a50; 
}
typedef eastl::string8_s0131_5a50 string8_s0131_5a50;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0131_5a50&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)
}
namespace Simulator {
struct Attribute
{
    // Member attribute: offset is relative to the current object.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    // Static attribute: the offset field holds the static's address; no ToXml callback.
    Attribute(const char* pName, uint32_t nID, void* pStatic,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = StaticOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = 0;
        offset = (uint32_t)pStatic;
    }

    // Record with a default value: the store of the default (static or GetDefaultValue<T>()) is part
    // of the record's construction and sits just before the offset store.
    template<typename Store>
    __forceinline Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault, const Store& storeDefault)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        storeDefault();
        offset = nOffset;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
struct UInt_mSource;
}
namespace Simulator {
struct UInt_mTarget;
}
namespace Simulator {
struct UInt_mPlanetKey;
}
namespace Simulator {
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0131_5a50& text, void* pData);
}
namespace Simulator {
template<typename T> bool AlwaysValid();
}
namespace Simulator {
template<typename T> void WriteTextUInt(char* pBuffer, void* pData);
}
namespace Simulator {
template<typename T> bool ToXmlUInt(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00aeba50(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae9e60(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0131_5a50& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00ae9ed0();
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00aeacc0(void* pData, const char* pName, int depth);   // SerializeList
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
}
namespace Simulator {
#define LIST_ATTR  Read_00aeba50, Write_00ae9e60, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae9ed0, ToXml_00aeacc0
}
namespace Simulator {
struct Vector3 { float x, y, z; Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {} };
}
namespace Simulator {
struct Matrix3 {
    float m[3][3];
    Matrix3& Assign(const Matrix3& other);        // 0x0041cb40
};
}
namespace Simulator {
extern const Vector3 kDefaultOffset;              // 0x0167af5c (this module's zero vector)
}
namespace Simulator {
extern const Matrix3 kDefaultRotation;            // 0x0167b554 (this module's identity)
}
namespace Simulator {
struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3  mOffset;
    float    mScale;
    Matrix3  mRotation;
    cSPTransform() : mFlags(0), mModificationCount(0), mOffset(kDefaultOffset), mScale(1.0f)
    {
        mRotation.Assign(kDefaultRotation);
    }
    cSPTransform& operator=(const cSPTransform& other);   // 0x00537dc0
};
}
namespace Simulator {
cSPTransform& GetDefaultTransform();              // 0x00b024a0 (SP::GetDefaultValue<cSPTransform;90607414>)
}
namespace Simulator {
struct ResourceKeyValue {
    uint32_t instance, type, group;
    ResourceKeyValue() : instance(0), type(0), group(0) {}
};
}
namespace Simulator {
struct IRefObject {
    virtual void AddRef();
    virtual void Release();
};
}
namespace Simulator {
template<typename T> struct SmartPtr {
    T* mp;
    SmartPtr() : mp(0) {}
    ~SmartPtr() { if (mp) mp->Release(); }
    SmartPtr& operator=(T* p)
    {
        if (p != mp) {
            T* pOld = mp;
            mp = p;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
};
}
namespace Simulator {
__forceinline ResourceKeyValue& GetDefaultKey() { static ResourceKeyValue key; return key; }
}
namespace Simulator {
__forceinline SmartPtr<IRefObject>& GetDefaultObject() { static SmartPtr<IRefObject> object; return object; }
}
namespace Simulator {
struct StoreTransform { const cSPTransform& v; StoreTransform(const cSPTransform& x) : v(x) {} void operator()() const { GetDefaultTransform() = v; } };
}
namespace Simulator {
struct StoreU64 { uint64_t* p; uint64_t v; StoreU64(uint64_t* a, uint64_t b) : p(a), v(b) {} void operator()() const { *p = v; } };
}
namespace Simulator {
struct StoreU32 { uint32_t* p; uint32_t v; StoreU32(uint32_t* a, uint32_t b) : p(a), v(b) {} void operator()() const { *p = v; } };
}
namespace Simulator {
struct StoreFloat { float* p; float v; StoreFloat(float* a, float b) : p(a), v(b) {} void operator()() const { *p = v; } };
}
namespace Simulator {
struct StoreByte { uint8_t* p; uint8_t v; StoreByte(uint8_t* a, uint8_t b) : p(a), v(b) {} void operator()() const { *p = v; } };
}
namespace Simulator {
struct StoreNullObject { StoreNullObject(int) {} void operator()() const { GetDefaultObject() = 0; } };
}
namespace Simulator {
struct StoreNullKey { StoreNullKey(int) {} void operator()() const { GetDefaultKey() = ResourceKeyValue(); } };
}
namespace Simulator {
extern uint64_t sFruitDefault;        // 0x0167bab8
}
namespace Simulator {
extern uint32_t sSeqIdDefault;        // 0x0167bac0
}
namespace Simulator {
extern uint32_t sSeqIndexDefault;     // 0x0167bac4
}
namespace Simulator {
extern uint32_t sSizeBracketDefault;  // 0x0167bac8
}
namespace Simulator {
extern float sBaseRadiusDefault;      // 0x0167badc
}
namespace Simulator {
extern float sCanopyRadiusDefault;    // 0x0167bae0
}
namespace Simulator {
extern float sHeightDefault;          // 0x0167bae4
}
namespace Simulator {
extern uint8_t sRemovedDefault;       // 0x0167bae8
}
namespace Simulator {
void SetDefault_00b02520(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00aff8b0(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00aff8d0(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00aff8f0(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00aff910(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00b002e0(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00aff930(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00aff980(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00aff9a0(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00aff9c0(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00aff9e0(Attribute* pAttr);
}
namespace Simulator {
bool Read_00aff7e0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b02540(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00aff810(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692fd0(const string8_s0131_5a50& text, void* pData);
}
namespace Simulator {
void ReadText_00693150(const string8_s0131_5a50& text, void* pData);
}
namespace Simulator {
void ReadText_006930b0(const string8_s0131_5a50& text, void* pData);
}
namespace Simulator {
void WriteText_00694ec0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_00595a70(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
}
namespace Simulator {
struct Tag_mTransform;
}
namespace Simulator {
struct Tag_mFruit;
}
namespace Simulator {
struct Tag_mSeq;
}
namespace Simulator {
struct Tag_mKey;
}
namespace Simulator {
extern AttrSlot cPlant_sAttributes[12];   // 0x0167b578
}
namespace Simulator {
#define FLOAT_ATTR Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
}
namespace Simulator {
#define SHORT_ATTR(T) Read4<T>, Write4<T>, ReadTextInt<T>, WriteTextUInt<T>, AlwaysValid<Tag_mSeq>, ToXmlUInt<Tag_mSeq>
}
namespace Simulator {
#define ADD2(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cPlant_sAttributes[IDX] = a; }
}
// ---- items of slice s01315a50 end

// ---- items of slice s0134f690 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gSimAttributeDefaultOffset;      // 0x00692ca0  Simulator::Attribute::DefaultOffset
extern char FUN_00c724d0;                    // 0x00c724d0
extern char cAgentOrderManager_ActivateOne;  // 0x00bca960
extern char UTFWin_ILayoutElement_SetSerializer;  // 0x00c2e4e0
extern char ClearBuffer;                     // 0x00692fb0
extern char FUN_00b6f550;                    // 0x00b6f550
extern char FUN_00ac8050;                    // 0x00ac8050
extern char FUN_00c72500;                    // 0x00c72500
extern char FUN_00bdd350;                    // 0x00bdd350
extern char operator__SP_cPlanet;            // 0x00c3b930  operator>>(SP::cPlanet)
extern char FUN_00b6e3a0;                    // 0x00b6e3a0
extern char FUN_00ac88c0;                    // 0x00ac88c0
extern char ParseVector3;                    // 0x006930f0
extern char FUN_00695010;                    // 0x00695010
extern char UTFWin_Window_Initialize;        // 0x00b1fbf0
extern char FUN_00acbba0;                    // 0x00acbba0
extern char FUN_00ae3470;                    // 0x00ae3470
extern char FUN_00ae3490;                    // 0x00ae3490
extern char FUN_00ae3310;                    // 0x00ae3310
extern char FUN_00b72e30;                    // 0x00b72e30
extern char FUN_00b74a40;                    // 0x00b74a40
extern char FUN_00572810;                    // 0x00572810
extern char WriteUint32Value;                // 0x00572840
extern char ParseULong;                      // 0x00693090
extern char FUN_00694f00;                    // 0x00694f00
extern char ParseLong;                       // 0x00692ff0
extern char FUN_00694ee0;                    // 0x00694ee0
extern char FUN_0057cde0;                    // 0x0057cde0
extern char FUN_00ac87c0;                    // 0x00ac87c0
extern char FUN_00ac87f0;                    // 0x00ac87f0
extern char FUN_00ac88f0;                    // 0x00ac88f0
extern char FUN_00694c80;                    // 0x00694c80
extern char FUN_00694c10;                    // 0x00694c10
extern char FUN_00acbbc0;                    // 0x00acbbc0
extern char ParseFloat;                      // 0x006930b0
extern char FUN_00694fc0;                    // 0x00694fc0
extern char FUN_00acbb80;                    // 0x00acbb80
extern char Simulator_ToXml;                 // 0x00675ca0
struct SimAttribute {
    const char* mName;          // +0x00
    u32         mHash;          // +0x04
    u32         mOffset;        // +0x08  offsetof(cPlanet, member)
    u32         mBaseA;         // +0x0c  left to the runtime base initialiser
    u32         mBaseB;         // +0x10
    u32         mBaseC;         // +0x14
    u32         mDefaultLow;    // +0x18
    u32         mDefaultHigh;   // +0x1c
    void*       mFnDefault;     // +0x20  Simulator::Attribute::DefaultOffset
    void*       mFnSave;        // +0x24
    void*       mFnLoad;        // +0x28
    void*       mFnParse;       // +0x2c
    void*       mFnEdit;        // +0x30
    void*       mFnUI;          // +0x34
    void*       mFnExtra;       // +0x38
};
extern SimAttribute gPlanetAttributes[12];   // 0x01578890
// ---- items of slice s0134f690 end

// @ 0x00ac0d80
int* __cdecl FUN_00ac0d80(int* first, int* last, int* key)
{
    if (first != last) {
        do {
            if (first[0] == key[0] && first[1] == key[1] && first[2] == key[2])
                break;
            first += 3;
        } while (first != last);
    }
    return first;
}

// @ 0x00aff240
float SP::cTreeData_s00af_ef10::GetFruitHeight() const
{
    return mFruitHeight * 0.25f;
}

// @ 0x00aff250
uint32_t cKeyedValue::GetValue(uint32_t nKey)
{
    switch (nKey) {
    case 0x29c388a:
        return mField18;
    case 0x3a8be428:
        return mField14;
    case 0x6d60a1cc:
        return mField1c;
    }
    return 0;
}

// @ 0x00aff280
void Simulator::cFruit::Initialize()
{
    mpVtbl00 = gVtblFruit;
    mpVtbl04 = gVtblFruit04;
    mSub34.mpVtbl = gVtblFruit34;
    mDecal.mpVtbl = gVtblFruit130;
    mnKey158 = 0x6d60a1cc;
    mField15c = 0xffffffff;
    mField160 = 0xffffffff;
    mField150 = 0;
    mField154 = 0;
    mField164 = 0xffffffff;
    mField168 = 0;
    mDecal.Init();
    Finish();
}

// @ 0x00aff330
void* Simulator::cFruit::Cast(uint32_t nType)
{
    switch (nType) {
    case 0x2c9cc8e:
        return this;
    }
    void* pObject = mDecal.Cast(nType);
    if (pObject != 0)
        return pObject;
    return CastBase(nType);
}

// @ 0x00aff370
void Simulator::cFruit::Reset()
{
    ResetState();
    mField150 = 0xffffffff;
    mField154 = 0;
    mField164 = 0xffffffff;
    mnKey158 = 0x6d60a1cc;
    mField15c = 0xffffffff;
    mField160 = 0xffffffff;
    mField168 = 0;
}

// @ 0x00aff520
void* Simulator::cFruit::CastOther(uint32_t nType)
{
    switch (nType) {
    case 0x2e9688e:
        return this;
    }
    void* pObject = CastVariant(nType);
    if (pObject != 0)
        return pObject;
    return mSub34.Cast(nType);
}

// @ 0x00aff550
float Simulator::cFruit::GetObstacleValue()
{
    cObstacleMgr* pManager = GetObstacleMgr();
    uint64_t nKey = pManager->MakeKey(mField50, mField4c, mField54);
    cObstacle* pObstacle = pManager->FindById(nKey);
    if (pObstacle != 0)
        return pObstacle->mField44;
    return 0.0f;
}

// @ 0x00aff700
void Simulator::cFruit::AddTime(int32_t nUnused, int32_t nDelta)
{
    if ((int32_t)mnTimer > 0)
        mnTimer -= nDelta;
}

// @ 0x00aff7e0
bool LoadRotation(cOutStream* pStream, RotSerial* pRotation)
{
    pRotation->Load(pStream->GetIO()->GetStream());
    return true;
}

// @ 0x00aff810
bool SaveRotation(cOutStream* pStream, RotSerial* pRotation)
{
    pRotation->Save(pStream->GetIO()->GetStream());
    return true;
}

// @ 0x00aff8b0
void WriteVector2Value(cValueHost* pHost)
{
    cVector2* pValue = (cVector2*)pHost->mpfnGet(pHost);
    *pValue = gDefaultVector2;
}

// @ 0x00aff930
void WriteVector3Value(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cZeroVector3 sDefault;
    *pValue = reinterpret_cast<cVector3&>(sDefault);
}

// @ 0x00aff9e0
void WriteByteValue(cValueHost* pHost)
{
    uint8_t* pValue = (uint8_t*)pHost->mpfnGet(pHost);
    *pValue = gDefaultByte;
}

// @ 0x00affae0
void WriteVector3Value2(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cZeroVector3 sDefault;
    *pValue = reinterpret_cast<cVector3&>(sDefault);
}

// @ 0x00affb30
void WriteVector3Value3(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cZeroVector3 sDefault;
    *pValue = reinterpret_cast<cVector3&>(sDefault);
}

// @ 0x00affb80
void WriteVector3Value4(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cZeroVector3 sDefault;
    *pValue = reinterpret_cast<cVector3&>(sDefault);
}

// @ 0x00affc90
void __stdcall DestroyItemRange(cSerializeItem* pBegin, cSerializeItem* pEnd)
{
    while (pBegin < pEnd) {
        pBegin->Destroy(0);
        ++pBegin;
    }
}

// @ 0x00affcc0
cSerializeItem* DestroyItemRangeInto(cSerializeItem* pBegin, cSerializeItem* pEnd, cSerializeItem* pOut)
{
    while (pBegin != pEnd) {
        pBegin->Destroy(0);
        ++pBegin;
        ++pOut;
    }
    return pOut;
}

// @ 0x00affde0
void cTransform::SetPosition(const cVector3* pPosition)
{
    mPosition = *pPosition;
    mnFlags |= 4;
    ++mnVersion;
}

// @ 0x00afff30
void* VectorAt(const cPtrVector* pVector, uint32_t nIndex)
{
    if (pVector == 0)
        return 0;
    if (nIndex < (uint32_t)(pVector->mpEnd - pVector->mpBegin))
        return pVector->mpBegin[nIndex];
    return 0;
}

// @ 0x00afffa0
void SP::cSpatialObjectView::Update(uint32_t nA, uint32_t nB)
{
    if (mpData->mbActive == 0)
        return;
    if (GetObject() == 0) {
        if (!mpData->IsActive())
            return;
    }
    HandleSimulationUpdate(nA, nB);
}

// @ 0x00b00350
void WriteVector3Value5(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cVector3 const sDefault;
    *pValue = sDefault;
}

// @ 0x00b00400
bool ReadItemList(cSerializeMgr* pMgr, const cSerializeItemList* pList)
{
    cSerializeItem* pItem = pList->mpBegin;
    cSerializeItem* pEnd = pList->mpEnd;
    for (; pItem != pEnd; ++pItem) {
        cSerializeItem* pReadItem = pItem;
        if (pReadItem != 0)
            pReadItem->ReadItem(pMgr);
    }
    return true;
}

// @ 0x00b00520
int TreeClumpArrayDestroyAll(int bUnused, cTreeClumpVector* pVector)
{
    (void)bUnused;
    cTreeClumpData* pEnd = (cTreeClumpData*)pVector->mpEnd;
    for (cTreeClumpData* pCur = (cTreeClumpData*)pVector->mpBegin; pCur != pEnd;
         pCur = (cTreeClumpData*)((uint8_t*)pCur + sizeof(cTreeClumpData))) {
        DestroyTreeClumpData(pCur, &pVector->mpCapacity, L"cTreeClumpData");
    }
    return 1;
}

// @ 0x00b00560
void TreeClumpArrayFree(cTreeClumpVector* pVector)
{
    cTreeClump** pEnd = pVector->mpEnd;
    for (cTreeClump** pCur = pVector->mpBegin; pCur < pEnd; ++pCur)
        (*pCur)->v08(0);

    int* pBase = (int*)pVector->mpBegin;
    if (pBase != nullptr && pBase[-1] != 0)
        operator_delete__(pBase);
}

// @ 0x00b006f0
void SpatialEntryResetRange(cSpatialEntry* pFirst, cSpatialEntry* pLast)
{
    for (; pFirst < pLast; ++pFirst) {
        pFirst->mpVtbl = 0;
        pFirst->mField08 = 0;
        pFirst->mField0c = 0;

        IEntryRef* pRef0 = pFirst->mpRef0;
        if (pRef0 != nullptr) {
            pFirst->mpRef0 = nullptr;
            pRef0->Release();
        }
        IEntryRef* pRef1 = pFirst->mpRef1;
        if (pRef1 != nullptr) {
            pFirst->mpRef1 = nullptr;
            pRef1->Reset();
        }
        pFirst->mField18 = 0;
        if (pFirst->mpRef1 != nullptr)
            pFirst->mpRef1->Reset();
        if (pFirst->mpRef0 != nullptr)
            pFirst->mpRef0->Release();
    }
}

// @ 0x00b00820
void InsertionSortByDistance_Positioned(cPositionedObject** pFirst, cPositionedObject** pLast, const Vec3* pReference)
{
    if (pFirst == pLast)
        return;

    for (cPositionedObject** pCur = pFirst + 1; pCur != pLast; ++pCur) {
        cPositionedObject* pValue = *pCur;
        cPositionedObject** pSlot = pCur;
        if (pCur != pFirst) {
            float dx1 = pReference->mX - pValue->mX;
            float dy1 = pReference->mY - pValue->mY;
            float dz1 = pReference->mZ - pValue->mZ;
            do {
                cPositionedObject* pPrev = pSlot[-1];
                float dx2 = pReference->mX - pPrev->mX;
                float dy2 = pReference->mY - pPrev->mY;
                float dz2 = pReference->mZ - pPrev->mZ;
                if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                    break;
                *pSlot = pPrev;
                --pSlot;
            } while (pSlot != pFirst);
        }
        *pSlot = pValue;
    }
}

// @ 0x00b008f0
void InsertionSortByDistance_Positioned_FromRange(cPositionedObject** pFirst, cPositionedObject** pLast, const Vec3* pReference)
{
    if (pFirst == pLast)
        return;

    float refX = pReference->mX;
    float refY = pReference->mY;
    float refZ = pReference->mZ;
    do {
        cPositionedObject* pValue = *pFirst;
        float dx1 = refX - pValue->mX;
        float dy1 = refY - pValue->mY;
        float dz1 = refZ - pValue->mZ;
        cPositionedObject** pSlot = pFirst;
        cPositionedObject** pWrite = pFirst;
        for (;;) {
            --pSlot;
            cPositionedObject* pPrev = *pSlot;
            float dx2 = refX - pPrev->mX;
            float dy2 = refY - pPrev->mY;
            float dz2 = refZ - pPrev->mZ;
            if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                break;
            *pWrite = pPrev;
            --pWrite;
        }
        ++pFirst;
        *pWrite = pValue;
    } while (pFirst != pLast);
}

// @ 0x00b009b0
void InsertionSortByDistance_Node(cNode** pFirst, cNode** pLast, float refX, float refY, float refZ)
{
    if (pFirst == pLast)
        return;

    for (cNode** pCur = pFirst + 1; pCur != pLast; ++pCur) {
        cNode* pValue = *pCur;
        cNode** pSlot = pCur;
        if (pCur != pFirst) {
            float dx1 = refX - pValue->mX;
            float dy1 = refY - pValue->mY;
            float dz1 = refZ - pValue->mZ;
            do {
                cNode* pPrev = pSlot[-1];
                float dx2 = refX - pPrev->mX;
                float dy2 = refY - pPrev->mY;
                float dz2 = refZ - pPrev->mZ;
                if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                    break;
                *pSlot = pPrev;
                --pSlot;
            } while (pSlot != pFirst);
        }
        *pSlot = pValue;
    }
}

// @ 0x00b00a80
void InsertionSortByDistance_Node_FromRange(cNode** pFirst, cNode** pLast, float refX, float refY, float refZ)
{
    for (; pFirst != pLast; ++pFirst) {
        cNode* pValue = *pFirst;
        float dx1 = refX - pValue->mX;
        float dy1 = refY - pValue->mY;
        float dz1 = refZ - pValue->mZ;
        cNode** pSlot = pFirst;
        cNode** pWrite = pFirst;
        for (;;) {
            --pSlot;
            cNode* pPrev = *pSlot;
            float dx2 = refX - pPrev->mX;
            float dy2 = refY - pPrev->mY;
            float dz2 = refZ - pPrev->mZ;
            if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                break;
            *pWrite = pPrev;
            --pWrite;
        }
        *pWrite = pValue;
    }
}

// @ 0x00b00b40
void InsertionSortVec3Pointers(Vec3** pFirst, Vec3** pLast, float refX, float refY, float refZ)
{
    if (pFirst == pLast)
        return;

    for (Vec3** pCur = pFirst + 1; pCur != pLast; ++pCur) {
        Vec3* pValue = *pCur;
        Vec3** pSlot = pCur;
        if (pCur != pFirst) {
            float dx1 = refX - pValue->mX;
            float dy1 = refY - pValue->mY;
            float dz1 = refZ - pValue->mZ;
            do {
                Vec3* pPrev = pSlot[-1];
                float dx2 = refX - pPrev->mX;
                float dy2 = refY - pPrev->mY;
                float dz2 = refZ - pPrev->mZ;
                if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                    break;
                *pSlot = pPrev;
                --pSlot;
            } while (pSlot != pFirst);
        }
        *pSlot = pValue;
    }
}

// @ 0x00b00c10
void InsertionSortVec3Pointers_FromRange(Vec3** pFirst, Vec3** pLast, float refX, float refY, float refZ)
{
    for (; pFirst != pLast; ++pFirst) {
        Vec3* pValue = *pFirst;
        float dx1 = refX - pValue->mX;
        float dy1 = refY - pValue->mY;
        float dz1 = refZ - pValue->mZ;
        Vec3** pSlot = pFirst;
        Vec3** pWrite = pFirst;
        for (;;) {
            --pSlot;
            Vec3* pPrev = *pSlot;
            float dx2 = refX - pPrev->mX;
            float dy2 = refY - pPrev->mY;
            float dz2 = refZ - pPrev->mZ;
            if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 <= dx1 * dx1 + dy1 * dy1 + dz1 * dz1)
                break;
            *pWrite = pPrev;
            --pWrite;
        }
        *pWrite = pValue;
    }
}

// @ 0x00b00cd0
cPositionedObject** NearestOfThree_Positioned(cPositionedObject** ppA, cPositionedObject** ppB, cPositionedObject** ppC, const Vec3* pReference)
{
    cPositionedObject* pA = *ppA;
    cPositionedObject* pB = *ppB;
    cPositionedObject* pC = *ppC;

    float refX = pReference->mX;
    float refY = pReference->mY;
    float refZ = pReference->mZ;

    float ax = refX - pA->mX;
    float ay = refY - pA->mY;
    float az = refZ - pA->mZ;
    float bx = refX - pB->mX;
    float by = refY - pB->mY;
    float bz = refZ - pB->mZ;
    float cx = refX - pC->mX;
    float cy = refY - pC->mY;
    float cz = refZ - pC->mZ;

    float distA = ax * ax + ay * ay + az * az;
    float distB = bx * bx + by * by + bz * bz;
    float distC = cx * cx + cy * cy + cz * cz;

    if (distB <= distA) {
        if (distA < distC)
            return ppA;
        if (distB < distC)
            return ppC;
    } else {
        if (distC <= distB) {
            if (distC <= distA)
                return ppA;
            return ppC;
        }
    }
    return ppB;
}

// @ 0x00b00f50
cNode** NearestOfThree_Node(cNode** ppA, cNode** ppB, cNode** ppC, float refX, float refY, float refZ)
{
    cNode* pA = *ppA;
    cNode* pB = *ppB;
    cNode* pC = *ppC;

    float ax = refX - pA->mX;
    float ay = refY - pA->mY;
    float az = refZ - pA->mZ;
    float bx = refX - pB->mX;
    float by = refY - pB->mY;
    float bz = refZ - pB->mZ;
    float cx = refX - pC->mX;
    float cy = refY - pC->mY;
    float cz = refZ - pC->mZ;

    float distA = ax * ax + ay * ay + az * az;
    float distB = bx * bx + by * by + bz * bz;
    float distC = cx * cx + cy * cy + cz * cz;

    if (distB <= distA) {
        if (distA < distC)
            return ppA;
        if (distB < distC)
            return ppC;
    } else {
        if (distC <= distB) {
            if (distC <= distA)
                return ppA;
            return ppC;
        }
    }
    return ppB;
}

// @ 0x00b011f0
Vec3** NearestOfThreeVec3(Vec3** ppA, Vec3** ppB, Vec3** ppC, float refX, float refY, float refZ)
{
    Vec3* pA = *ppA;
    Vec3* pB = *ppB;
    Vec3* pC = *ppC;

    float ax = refX - pA->mX;
    float ay = refY - pA->mY;
    float az = refZ - pA->mZ;
    float bx = refX - pB->mX;
    float by = refY - pB->mY;
    float bz = refZ - pB->mZ;
    float cx = refX - pC->mX;
    float cy = refY - pC->mY;
    float cz = refZ - pC->mZ;

    float distA = ax * ax + ay * ay + az * az;
    float distB = bx * bx + by * by + bz * bz;
    float distC = cx * cx + cy * cy + cz * cz;

    if (distB <= distA) {
        if (distA < distC)
            return ppA;
        if (distC <= distB)
            return ppB;
    } else {
        if (distB < distC)
            return ppB;
        if (distC <= distA)
            return ppA;
    }
    return ppC;
}

// @ 0x00b01470
cSpatialEntry* SpatialEntryResetRangeWithOutput(cSpatialEntry* pFirst, cSpatialEntry* pLast, cSpatialEntry* pOut)
{
    if (pFirst == pLast)
        return pOut;

    do {
        pFirst->mpVtbl = 0;
        pFirst->mField08 = 0;
        pFirst->mField0c = 0;

        IEntryRef* pRef0 = pFirst->mpRef0;
        if (pRef0 != nullptr) {
            pFirst->mpRef0 = nullptr;
            pRef0->Release();
        }
        IEntryRef* pRef1 = pFirst->mpRef1;
        if (pRef1 != nullptr) {
            pFirst->mpRef1 = nullptr;
            pRef1->Reset();
        }
        pFirst->mField18 = 0;
        if (pFirst->mpRef1 != nullptr)
            pFirst->mpRef1->Reset();
        if (pFirst->mpRef0 != nullptr)
            pFirst->mpRef0->Release();

        ++pFirst;
        ++pOut;
    } while (pFirst != pLast);
    return pOut;
}

// @ 0x00b014f0
void HeapInsertPositioned(cPositionedObject** ppHeap, int nRoot, int nIndex, cPositionedObject* pValue, const Vec3* pReference)
{
    if (nIndex <= nRoot) {
        ppHeap[nIndex] = pValue;
        return;
    }

    float refX = pReference->mX;
    float refY = pReference->mY;
    float refZ = pReference->mZ;
    float vx = refX - pValue->mX;
    float vy = refY - pValue->mY;
    float vz = refZ - pValue->mZ;
    float distValue = vx * vx + vy * vy + vz * vz;

    for (;;) {
        int nParent = (nIndex - 1) >> 1;
        cPositionedObject* pParent = ppHeap[nParent];
        float px = refX - pParent->mX;
        float py = refY - pParent->mY;
        float pz = refZ - pParent->mZ;
        if (distValue <= px * px + py * py + pz * pz)
            break;
        ppHeap[nIndex] = pParent;
        nIndex = nParent;
        if (nParent <= nRoot)
            break;
    }
    ppHeap[nIndex] = pValue;
}

// @ 0x00b015c0
void HeapInsertNode(cNode** ppHeap, int nRoot, int nIndex, cNode* pValue, float refX, float refY, float refZ)
{
    if (nIndex <= nRoot) {
        ppHeap[nIndex] = pValue;
        return;
    }

    float vx = refX - pValue->mX;
    float vy = refY - pValue->mY;
    float vz = refZ - pValue->mZ;
    float distValue = vx * vx + vy * vy + vz * vz;

    for (;;) {
        int nParent = (nIndex - 1) >> 1;
        cNode* pParent = ppHeap[nParent];
        float px = refX - pParent->mX;
        float py = refY - pParent->mY;
        float pz = refZ - pParent->mZ;
        if (distValue <= px * px + py * py + pz * pz)
            break;
        ppHeap[nIndex] = pParent;
        nIndex = nParent;
        if (nParent <= nRoot)
            break;
    }
    ppHeap[nIndex] = pValue;
}

// @ 0x00b01690
void FUN_00b01690(void** arr, int root, int hole, const f32* key, f32 kx, f32 ky, f32 kz)
{
    if (hole <= root) {
        arr[hole] = (void*)key;
        return;
    }
    f32 x0 = key[0], y0 = key[1], z0 = key[2];
    int parent;
    do {
        parent = (hole - 1) >> 1;
        const f32* p = (const f32*)arr[parent];
        f32 dx0 = kx - x0, dy0 = ky - y0, dz0 = kz - z0;
        f32 d0 = dz0 * dz0 + dy0 * dy0 + dx0 * dx0;
        f32 dx1 = kx - p[0], dy1 = ky - p[1], dz1 = kz - p[2];
        f32 d1 = dx1 * dx1 + dz1 * dz1 + dy1 * dy1;
        if (d0 <= d1) break;
        arr[hole] = (void*)p;
        hole = parent;
    } while (parent > root);
    arr[hole] = (void*)key;
}

// @ 0x00b01770
Simulator_cTreeData::Simulator_cTreeData()
{
    this->vtbl8 = (void*)0x013ec458;
    this->f08 = 0;
    this->vtbl = (void*)0x0145c678;
    this->vtbl8 = (void*)0x0145c668;
    this->f0e = 0;
    this->f0c = 0;
    this->f10 = g_167af5c;
    this->f14 = g_167af60;
    this->f18 = g_167af64;
    this->f1c = 1.0f;
    M3(&this->m20[0])->Assign((const void*)0x0167b554);
    this->f48 = 0;
    this->f4c = 0;
    this->f50 = 0;
    this->f54 = 0;
    this->f58 = 0x6d60a1cc;
    this->f5c = 0;
    this->f60 = 0;
    this->f64 = 0;
    this->f68 = 0;
    this->f7c = 0;
    this->f6c = 0.0f;
    this->f70 = 0.0f;
    this->f74 = 0.0f;
    this->f78 = 0xffffffff;
}

// @ 0x00b01890
void* cFruitViewFactory::Create(void* owner)
{
    void* v;
    if (owner == 0) {
        v = 0;
    } else {
        v = (*(void*(__thiscall**)(void*, u32))((char*)vtbl(owner) + 0xc))(owner, 0x02c9cc8e);
    }
    void* sub = at(v, 0x34);
    if ((*(void*(__thiscall**)(void*))((char*)vtbl(sub) + 0xac))(sub) == 0) {
        return 0;
    }
    u8* o = (u8*)op_new(0x38, "Simulator/cFruitView", 0, 0, 0, 0);
    if (o != 0) {
        SP_cSpatialObjectView_ctor(o);
        *(void**)o = (void*)0x0145c6d0;
        *(u32*)(o + 0x34) = 0;
        (*(void(__thiscall**)(void*, void*))((char*)vtbl(o) + 0x24))(o, owner);
        return o;
    }
    (*(void(__thiscall**)(void*))((char*)vtbl((void*)0) + 0x24))((void*)0);
    return 0;
}

// @ 0x00b01910
Simulator_cFruit::Simulator_cFruit()
{
    FUN_00c3f9b0();
    SP_cInteractionTarget_ctor((u8*)this + 0x130);
    *(void**)this = (void*)0x0145c5c8;
    this->vtbl4 = (void*)0x0145c5b4;
    this->vtbl34 = (void*)0x0145c4f0;
    *(void**)((u8*)this + 0x130) = (void*)0x0145c4d0;
    this->f148 = 0;
    FUN_00c3f9a0(4);
    this->f88 = 6;
    this->f84 |= 0x200;
    this->fa5 = 0;
    this->f158 = 0x6d60a1cc;
    this->f15c = 0xffffffff;
    this->f160 = 0xffffffff;
    this->f164 = 0xffffffff;
    this->f150 = 0xffffffff;
    this->f154 = 0;
    this->f168 = 0;
    if (this->f16c != 6) {
        void* p = (void*)this->m108;
        if (p != 0) {
            this->m108 = 0;
            vcall0(p, 4);
        }
        this->f16c = 6;
    }
}

// @ 0x00b019d0
void cFruitOps1::Enable(void* arg)
{
    FUN_00c3ff10(arg);
    *(u32*)((u8*)this + 0x148) |= 2;
    *(u8*)((u8*)this + 0xa5) = 1;
    *(u32*)((u8*)this + 0x16c) = 3;
}

// @ 0x00b01a00
void cFruitOps2::Disable(void* arg)
{
    FUN_00c3fad0(arg);
    *(u32*)((u8*)this + 0x148) &= 0xfffffffd;
    if (*(u32*)((u8*)this + 0x16c) != 2) {
        *(u32*)((u8*)this + 0x168) = 0;
        *(u32*)((u8*)this + 0x16c) = 2;
    }
}

// @ 0x00b01a40
Simulator_cFruitGroup::~Simulator_cFruitGroup()
{
    Simulator_cFruitGroup* self = this;
    *(void**)self = (void*)0x0145c748;
    self->vtbl4 = (void*)0x0145c738;
    self->vtbl34 = (void*)0x0145c71c;
    self->f4c = 0;
    self->f54 = 0;
    void* p1 = (void*)self->f1d0;
    if (p1 != 0) {
        vcall0(p1, 4);
    }
    void* p2 = (void*)self->f1c4;
    if (p2 != 0) {
        vcall0(p2, 4);
    }
    u32 a = self->f19c;
    if (a != 0 && *(u32*)(a - 4) != 0) {
        op_delete_array((void*)a);
    }
    u32 b = self->fa4;
    if (b != 0 && *(u32*)(b - 4) != 0) {
        op_delete_array((void*)b);
    }
    void* p3 = (void*)self->fa0;
    if (p3 != 0) {
        vcall0(p3, 4);
    }
    FUN_00ac0520();
    FUN_00b184c0();
}

// @ 0x00b01cb0
void* RefRecordOps::Assign(const void* src)
{
    u8* self = (u8*)this;
    const u8* s = (const u8*)src;
    *(u32*)(self + 0x10) = 0;
    *(u32*)(self + 0x14) = 0;
    *(u32*)(self + 0) = *(u32*)(s + 0);
    *(u32*)(self + 8) = *(u32*)(s + 8);
    *(u32*)(self + 0xc) = *(u32*)(s + 0xc);
    void* p1 = *(void**)(s + 0x10);
    void* old1 = *(void**)(self + 0x10);
    if (p1 != old1) {
        if (p1 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p1) + 0))(p1);
        }
        *(void**)(self + 0x10) = p1;
        if (old1 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(old1) + 4))(old1);
        }
    }
    void* p2 = *(void**)(s + 0x14);
    void* old2 = *(void**)(self + 0x14);
    if (p2 != old2) {
        if (p2 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p2) + 0x34))(p2);
        }
        *(void**)(self + 0x14) = p2;
        if (old2 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(old2) + 0x38))(old2);
        }
    }
    *(u32*)(self + 0x18) = *(u32*)(s + 0x18);
    return self;
}

// @ 0x00b01d30
void* RefRecordOps2::Assign2(const void* src)
{
    u8* self = (u8*)this;
    const u8* s = (const u8*)src;
    *(u32*)(self + 0) = *(u32*)(s + 0);
    *(u32*)(self + 8) = *(u32*)(s + 8);
    *(u32*)(self + 0xc) = *(u32*)(s + 0xc);
    void* p1 = *(void**)(s + 0x10);
    void* old1 = *(void**)(self + 0x10);
    if (p1 != old1) {
        if (p1 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p1) + 0))(p1);
        }
        *(void**)(self + 0x10) = p1;
        if (old1 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(old1) + 4))(old1);
        }
    }
    void* p2 = *(void**)(s + 0x14);
    void* old2 = *(void**)(self + 0x14);
    if (p2 != old2) {
        if (p2 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p2) + 0x34))(p2);
        }
        *(void**)(self + 0x14) = p2;
        if (old2 != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(old2) + 0x38))(old2);
        }
    }
    *(u32*)(self + 0x18) = *(u32*)(s + 0x18);
    return self;
}

// @ 0x00b01db0
void cAppModeEditorBase::HandleGameCommandMessage(void* arg)
{
    u8* self = (u8*)this;
    u32 key = (u32)arg;
    if (key == 0x01654c06) {
        key = (u32)SP_GetCurrentGameMode();
    }
    FUN_00b3d320();
    void* mgr = FUN_00b1daf0();
    void* src = SP_NounManager((void*)key);
    (void)src;
    void* inst = mgr;
    if (inst != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(inst) + 0))(inst);
    }
    bool flagEnter = false;
    if (inst != 0) {
        u32 out;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out, 0x3337809)
            && *(u16*)(out + 0x12) == 1) {
            flagEnter = *(bool*)cProperty_GetBool((void*)out);
        }
        u32 out2;
        bool b2 = false;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out2, 0x33385cd)
            && *(u16*)(out2 + 0x12) == 1) {
            b2 = *(bool*)cProperty_GetBool((void*)out2);
        }
        if (b2) {
            *(u32*)(self + 0x1ba18c) |= 8;
        } else {
            *(u32*)(self + 0x1ba18c) &= 0xfffffff7;
        }
        u32 out3;
        bool b3 = false;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out3, 0x62978be)
            && *(u16*)(out3 + 0x12) == 1) {
            b3 = *(bool*)cProperty_GetBool((void*)out3);
        }
        if (b3) {
            *(u32*)(self + 0x1ba18c) |= 0x20;
        } else {
            *(u32*)(self + 0x1ba18c) &= 0xffffffdf;
        }
        i32 oldv = *(i32*)(self + 0x1b8e10);
        i32 newv = 0;
        u32 out4;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out4, 0x339ddf2)
            && *(u16*)(out4 + 0x12) == 9) {
            newv = *(i32*)cProperty_GetInt((void*)out4);
            if (newv < 0 || newv > 1) {
                newv = 0;
            }
        }
        *(i32*)(self + 0x1b8e10) = newv;
        if (oldv != newv) {
            *(u32*)(self + 0x1ba18c) |= 4;
        }
        u32 out5;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out5, 0x302aa89)
            && *(u16*)(out5 + 0x12) == 0xd) {
            g_1567398 = *(f32*)cProperty_GetFloat((void*)out5);
        }
        u32 out6;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out6, 0x302aa8f)
            && *(u16*)(out6 + 0x12) == 0xd) {
            g_156739c = *(f32*)cProperty_GetFloat((void*)out6);
        }
        u32 out7;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out7, 0x302aa93)
            && *(u16*)(out7 + 0x12) == 0xd) {
            f32 v = *(f32*)cProperty_GetFloat((void*)out7) * 1000.0f;
            g_15673a4 = (u32)(i32)v;
        }
        u32 out8;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out8, 0x302aa9b)
            && *(u16*)(out8 + 0x12) == 0xd) {
            f32 v = *(f32*)cProperty_GetFloat((void*)out8) * 1000.0f;
            g_167b550 += (u32)(i32)v + g_15673a4;
        }
        u32 out9;
        if ((*(bool(__thiscall**)(void*, u32*, u32))((char*)vtbl(inst) + 0x24))(inst, &out9, 0x302aa97)
            && *(u16*)(out9 + 0x12) == 0xd) {
            g_15673a0 = *(f32*)cProperty_GetFloat((void*)out9);
        }
    }
    if (flagEnter) {
        *(u32*)(self + 0x1ba18c) |= 1;
    } else {
        *(u32*)(self + 0x1ba18c) &= 0xfffffffe;
    }
    if (inst != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(inst) + 4))(inst);
    }
}

// @ 0x00b02060
void* NounCreator::GetOrCreate()
{
    u8* self = (u8*)this;
    i32 count = (i32)((*(u32*)(self + 0x1b9178) - *(u32*)(self + 0x1b9174)) >> 2);
    void* result = 0;
    if (count > 0) {
        u8* end = (u8*)*(u32*)(self + 0x1b9178);
        void* p = *(void**)(end - 4);
        if (p != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(p) + 0))(p);
            result = p;
        }
        *(u32*)(self + 0x1b9178) = *(u32*)(self + 0x1b9178) - 4;
        void* q = *(void**)*(u32*)(self + 0x1b9178);
        if (q != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(q) + 4))(q);
        }
    } else {
        void* n = SP_cGameNounManager_CreateNoun((void*)0x2e96892);
        if (n != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(n) + 0))(n);
            result = n;
        }
    }
    if (result != 0) {
        (*(void(__thiscall**)(void*))((char*)vtbl(result) + 4))(result);
    }
    return result;
}

// @ 0x00b02120
void GridOwner::Rebuild()
{
    u8* self = (u8*)this;
    if (SP_GetActiveTerrainSphere() == 0) {
        return;
    }
    void* ts = SP_GetActiveTerrainSphere();
    if ((*(void*(__thiscall**)(void*))((char*)vtbl(ts) + 0xc))(ts) == 0) {
        return;
    }
    void* ts2 = SP_GetActiveTerrainSphere();
    void* s = (*(void*(__thiscall**)(void*))((char*)vtbl(ts2) + 0xc))(ts2);
    f32 r = (*(f32*)((u8*)s + 0x38) * *(f32*)((u8*)s + 0x54) + *(f32*)((u8*)s + 0x34)) + 50.0f;
    f32 x0 = g_167af5c - r, x1 = g_167af5c + r;
    f32 y0 = g_167af60 - r, y1 = g_167af60 + r;
    f32 z0 = g_167af64 - r, z1 = g_167af64 + r;
    f32 v[5];
    v[0] = x0;  v[1] = y0;  v[2] = z0;  v[3] = y1;  v[4] = z1;
    v[0] = x1;
    f32 dx = v[0] - x0;
    f32 dy = y1 - y0;
    f32 dz = z1 - z0;
    f32* p = &v[2];
    if (dy <= dx) {
        p = &v[1];
    }
    if (*p <= dz && dz != *p) {
        p = &v[3];
    }
    if (*(u32*)(*(u32*)(self + 0x16500) + 0x24) != *(u32*)(*(u32*)(self + 0x16500) + 0x28)) {
        SP_cHierGrid_Shutdown();
    }
    if (x0 <= x1) {
        f32 a = *p * 2.0f;
        f32 b = a * 9.999999f;
        f32 c = a * 0.01f;
        i32 ic = (i32)c;
        if ((f32)ic < c) {
            ic = ic + 1;
        }
        u32 uc = (u32)ic;
        i32 n1 = 0;
        while (uc != 0) {
            uc = uc >> 1;
            n1 = n1 + 1;
        }
        i32 ib = (i32)b;
        if ((f32)ib < b) {
            ib = ib + 1;
        }
        u32 ub = (u32)ib;
        i32 n2 = 0;
        while (ub != 0) {
            ub = ub >> 1;
            n2 = n2 + 1;
        }
        i32 a1 = n1 > 0 ? n1 : 0;
        i32 a2 = n2 < 7 ? n2 : 7;
        if (a2 < a1) {
            a2 = a1;
        }
        SP_cHierGrid_Init(*(void**)(self + 0x16500), &v[0], *p, a1, a2);
    }
}

// @ 0x00b023d0
void TreeApplyOps::Apply(void* key, u32 id, u32 arg)
{
    if (key == 0 || id == 0xffffffff) {
        return;
    }
    u8* self = (u8*)this;
    u32 out;
    RBF(self + 0x8080)->find(&id, &out);
    if ((void*)out == (void*)(self + 0x8084)) {
        return;
    }
    u8* node = (u8*)out;
    if (*(u32*)(node + 0x30) == 0) {
        return;
    }
    if (*(u32*)(node + 0x18) <= id) {
        return;
    }
    FUN_00a887b0(*(u32*)(node + 0x2c), arg);
}

// @ 0x00b02430
void PairTreeOps::Find(void* out, const u32* key)
{
    u8* self = (u8*)this;
    u8* first = (u8*)(self + 4);
    u8* node = *(u8**)(self + 0xc);
    if (node != 0) {
        u32 k0 = key[0], k1 = key[1];
        do {
            u32 nk1 = *(u32*)(node + 0x14);
            u32 nk0 = *(u32*)(node + 0x10);
            if (nk1 > k1 || (nk1 == k1 && nk0 >= k0)) {
                first = node;
                node = *(u8**)(node + 4);
            } else {
                node = *(u8**)node;
            }
        } while (node != 0);
    }
    u32 outv;
    FUN_00a057f0(&outv, key);
    *(u32*)out = outv;
    *(u8**)((u8*)out + 4) = first;
}

// @ 0x00b02480
void* WrapperOps::Wrap(u32* src, void* inner)
{
    u8* self = (u8*)this;
    *(u32*)self = *src;
    ((RefRecordCtorStruct*)(self + 8))->Construct2(inner);
    return self;
}

// @ 0x00b024a0
void* GetDefaultValue_A(void)
{
    if ((*(volatile u32*)0x0167bb88 & 1) == 0) {
        *(volatile u32*)0x0167bb88 |= 1;
        *(f32*)0x0167bb54 = g_167af5c;
        *(f32*)0x0167bb58 = g_167af60;
        *(u16*)0x0167bb52 = 0;
        *(f32*)0x0167bb5c = g_167af64;
        *(u16*)0x0167bb50 = 0;
        *(f32*)0x0167bb60 = 1.0f;
        M3((void*)0x0167bb64)->Assign((const void*)0x0167b554);
    }
    return (void*)0x0167bb50;
}

// @ 0x00b02830
void __cdecl FUN_00b02830(void** first, void* last, int n, int holeIndex, void* top, float* pos)
{
    int child = holeIndex * 2 + 2;
    if (child >= n)
        goto done;
    {
        float py = pos[1];
        float pz = pos[2];
        float px = pos[0];
        for (;;) {
            HeapNodeBig* left  = (HeapNodeBig*)first[child];
            HeapNodeBig* right = (HeapNodeBig*)first[child - 1];
            float dly = py - left->y;
            float dlx = px - left->x;
            float dlz = pz - left->z;
            float drx = px - right->x;
            float dry = py - right->y;
            float drz = pz - right->z;
            float dl = dlz * dlz + dlx * dlx + dly * dly;
            float dr = drz * drz + dry * dry + drx * drx;
            if (dl < dr)
                --child;
            first[holeIndex] = first[child];
            holeIndex = child;
            child = child * 2 + 2;
            if (child >= n)
                break;
        }
    }
done:
    if (child == n) {
        first[holeIndex] = first[child - 1];
        holeIndex = child - 1;
    }
    FUN_00b014f0(first, last, holeIndex, top, pos);
}

// @ 0x00b02930
void __cdecl FUN_00b02930(void** first, void* last, int n, int holeIndex, void* top, float px, float py, float pz)
{
    int child = holeIndex * 2 + 2;
    if (child >= n)
        goto done;
    for (;;) {
        HeapNodeSmall* left  = (HeapNodeSmall*)first[child];
        HeapNodeSmall* right = (HeapNodeSmall*)first[child - 1];
        float dly = py - left->y;
        float dlx = px - left->x;
        float dlz = pz - left->z;
        float drx = px - right->x;
        float dry = py - right->y;
        float drz = pz - right->z;
        float dl = dlz * dlz + dlx * dlx + dly * dly;
        float dr = drz * drz + dry * dry + drx * drx;
        if (dl < dr)
            --child;
        first[holeIndex] = first[child];
        holeIndex = child;
        child = child * 2 + 2;
        if (child >= n)
            break;
    }
done:
    if (child == n) {
        first[holeIndex] = first[child - 1];
        holeIndex = child - 1;
    }
    FUN_00b015c0(first, last, holeIndex, top, px, py, pz);
}

// @ 0x00b02a40
void __cdecl FUN_00b02a40(void** first, void* last, int n, int holeIndex, void* top, float px, float py, float pz)
{
    int child = holeIndex * 2 + 2;
    if (child >= n)
        goto done;
    for (;;) {
        HeapNodePlain* left  = (HeapNodePlain*)first[child];
        HeapNodePlain* right = (HeapNodePlain*)first[child - 1];
        float dlz = pz - left->z;
        float dlx = px - left->x;
        float drx = px - right->x;
        float dly = py - left->y;
        float dry = py - right->y;
        float drz = pz - right->z;
        float dl = dlz * dlz;
        dl += dlx * dlx;
        dl += dly * dly;
        float dr = drz * drz;
        dr += dry * dry;
        dr += drx * drx;
        if (dl < dr)
            --child;
        first[holeIndex] = first[child];
        holeIndex = child;
        child = child * 2 + 2;
        if (child >= n)
            break;
    }
done:
    if (child == n) {
        first[holeIndex] = first[child - 1];
        holeIndex = child - 1;
    }
    FUN_00b01690(first, last, holeIndex, top, px, py, pz);
}

// @ 0x00b02c40
cFruitView* cFruitView::ScopedDtor(uint8 del)
{
    cFruitView* s = this;
    s->vtbl = gVtblFruitView;
    _ReadWriteBarrier();
    ScopedDtorEffect* eff = s->mpEffect;
    if (eff != 0) {
        if (eff->refcount > 1) {
            eff->refcount = eff->refcount - 1;
        } else {
            uint8 flag = (uint8)((eff->flags >> 31) & 1);
            VtCall(eff, 0x170, flag);
        }
    }
    ((Op*)this)->Me92660();
    if (del & 1)
        FUN_00f47380(this);
    return this;
}

// @ 0x00b02dd0
void __fastcall cFruitGroup_SetGameDataOwner(cFruitGroup* self)
{
    ((Op*)self)->M8550(0);
    self->m4c = -1;
    self->m54 = 0;
    memcpy(self->mRot, g_matrixIdentity, 0x24);
    self->f68 = g_HK_REAL_ONE;
    self->f5c = g_zero3a[0];
    self->f60 = g_zero3a[1];
    self->f64 = g_zero3a[2];
    self->m58 = 0;
    self->m90 = 0;
    self->m50 = 0x3a8be428;
    if (self->m1cc != 0) {
        void* p = self->m1d0;
        self->m1cc = 0;
        if (p != 0) {
            ((void(__thiscall*)(void*, int))*(void**)(*(int*)p + 0xc))(p, 1);
            p = self->m1d0;
            if (p != 0) {
                self->m1d0 = 0;
                ((void(__thiscall*)(void*))*(void**)(*(int*)p + 4))(p);
            }
        }
        int mode = self->m1cc;
        if (mode == 1) {
            void* em = FUN_0067ddd0();
            void* q = self->m1d0;
            if (q != 0) {
                self->m1d0 = 0;
                ((void(__thiscall*)(void*))*(void**)(*(int*)q + 4))(q);
            }
            ((void(__thiscall*)(void*, uint32, uint32, void*))*(void**)(*(int*)em + 0x2c))
                (em, g_kResA0, g_kResA1, &self->m1d0);
        } else if (mode == 2) {
            void* em = FUN_0067ddd0();
            void* q = self->m1d0;
            if (q != 0) {
                self->m1d0 = 0;
                ((void(__thiscall*)(void*))*(void**)(*(int*)q + 4))(q);
            }
            ((void(__thiscall*)(void*, uint32, uint32, void*))*(void**)(*(int*)em + 0x2c))
                (em, g_kResB0, g_kResB1, &self->m1d0);
        }
    }
    if (self->m1d0 != 0) {
        void* p = self->m1d0;
        self->m1d0 = 0;
        ((void(__thiscall*)(void*))*(void**)(*(int*)p + 4))(p);
    }
}

// @ 0x00b03550
void RegNodeThunk::M3550()
{
    ((RegNodeThunk*)((char*)this - 4))->M001b0();
    if ((g_regNodeGuard & 1) == 0) {
        g_regNodeGuard |= 1;
        g_regNode.M92f60(0);
        g_regNode.vtbl = gVtblRegNodeSdtor;
        FUN_011e07ef(FUN_013c1e60);
    }
    if (g_regNode.Ma30c0() == 0)
        g_regNode.M92850();
}

// @ 0x00b05410
void FUN_00b05410(int param_1, int param_2, int param_3, int param_4)
{
    uint span = (uint)(param_2 - param_1);
    while ((int)(span & 0xfffffffc) > 0x70 && param_3 > 0) {
        int* mid = (int*)make_heap_a((void*)param_1,
                                     (void*)(param_1 + (((param_2 - param_1) >> 2)
                                                        - ((param_2 - param_1) >> 31) >> 1) * 4),
                                     (void*)(param_2 - 4), (void*)param_4);
        int i = (int)sort_partition_a((void*)param_1, (void*)param_2, (void*)*mid, param_4);
        --param_3;
        FUN_00b05410(i, param_2, param_3, param_4);
        span = (uint)(i - param_1);
        param_2 = i;
    }
    if (param_3 == 0)
        sort_by_distance((void*)param_1, (void*)param_2, (void*)param_2, param_4);
}

// @ 0x00b054a0
void FUN_00b054a0(int param_1, int param_2, int param_3, int param_4, float px, float py, float pz)
{
    int pa = param_4;
    uint span = (uint)(param_2 - param_1);
    while ((int)(span & 0xfffffffc) > 0x70 && param_3 > 0) {
        int* mid = (int*)make_heap_b((void*)param_1,
                                     (void*)(param_1 + (((param_2 - param_1) >> 2)
                                                        - ((param_2 - param_1) >> 31) >> 1) * 4),
                                     (void*)(param_2 - 4), px, py, pz, px, py, pz);
        int i = (int)sort_partition_b((void*)param_1, (void*)param_2, (void*)*mid);
        --param_3;
        FUN_00b054a0(i, param_2, param_3, pa, px, py, pz);
        span = (uint)(i - param_1);
        param_2 = i;
    }
    if (param_3 == 0)
        sort_and_visit((void*)param_1, (void*)param_2, (void*)param_2, px, py, pz);
}

// @ 0x00b055c0
void FUN_00b055c0(int param_1, int param_2, int param_3, int param_4, float px, float py, float pz)
{
    int pa = param_4;
    uint span = (uint)(param_2 - param_1);
    while ((int)(span & 0xfffffffc) > 0x70 && param_3 > 0) {
        int* mid = (int*)make_heap_c((void*)param_1,
                                     (void*)(param_1 + (((param_2 - param_1) >> 2)
                                                        - ((param_2 - param_1) >> 31) >> 1) * 4),
                                     (void*)(param_2 - 4), px, py, pz, px, py, pz);
        int i = (int)sort_partition_c((void*)param_1, (void*)param_2, (void*)*mid);
        --param_3;
        FUN_00b055c0(i, param_2, param_3, pa, px, py, pz);
        span = (uint)(i - param_1);
        param_2 = i;
    }
    if (param_3 == 0)
        FUN_00b047b0((void**)param_1, (void**)param_2, (void**)param_2, px, py, pz);
}

// @ 0x00b05800
void SimObj::reset()
{
    if (this->mFlags_148 & 1) {
        void* tmp = (void*)this;
        void* mgr = FUN_00b3d440_arg(&tmp);
        remove_1st((char*)mgr + 0x1b905c);
    }
    this->mA_150 = 0xffffffff;
    this->mB_154 = 0;
    this->mE_164 = 0xffffffff;
    this->mId_158 = 0x6d60a1cc;
    this->mSel_15c = 0xffffffff;
    this->mIdx_160 = 0xffffffff;
    this->mF_168 = 0;
    {
        int* sub = (int*)this->mpSub_108;
        if (sub) {
            this->mpSub_108 = 0;
            (*(void(__thiscall**)(int*))(sub[0] + 4))(sub);
        }
    }
    this->mG_16c = 6;
    this->mSub_130.Init();
    this->Finish();
}

// @ 0x00b0a040
char Mgr::SerializeMgr(u32 param_2)
{
    char buf[0xa14];
    void *pOuter = (char *)this - 4;
    SP__cVarListSerializer__ctor(buf, pOuter, (const char *)0x01567a80, 0x1a80d26);
    char ok = SP__cVarListSerializer__Serialize(buf, param_2);
    mFlagsA &= 0xfffffffd;
    mFlagsB = 0x1388;
    if ((mFlagsA & 0x10) != 0) {
        FUN_00b091d0(pOuter);
        return ok;
    }
    FUN_00b06cd0(pOuter);
    return ok;
}

// @ 0x00b0c520
void cPlanetManager::SetCurrentKey(const cObjectKey* pKey)
{
    if (mpCurrentKey != pKey) {
        if (pKey != &sNullKey) {
            SetSelectedKey(pKey);
            if (mFlags & 1) {
                RefreshFromSelection();
                mpCurrentKey = pKey;
                return;
            }
            Unload(false);
        }
        mpCurrentKey = pKey;
    }
}

// @ 0x00b0c5d0
void cKeyChangeNotifier::Shutdown()
{
    cPlanetManager* pOwner = Owner();
    pOwner->Unload(true);
    if (pOwner->mHandlerId != 0) {
        int nHandler = pOwner->mHandlerId;
        pOwner->mHandlerId = 0;
        RemoveHandler(nHandler, pOwner->mHandlerKey[0], pOwner->mHandlerKey[1],
                      pOwner->mHandlerKey[2], pOwner->mHandlerKey[3]);
    }
    pOwner->mpWorld->Shutdown();
}

// @ 0x00c72c60
void SP::cPlanet::AddDebugInfo(eastl::basic_string<char, eastl::allocator> * str)
{
    char* s = (char*)this;
    void* pd = *(void**)(s + 0x13c);
    StrAppendSprintf(str, "\nPlanet Name: %S", ((void**)FUN_00ecdba0(pd))[0]);

    pd = *(void**)(s + 0x13c);
    if (pd != 0 && FUN_00b8dab0(pd) == 5) {
        void* gd = *(void**)(s + 0xd4);
        void* slot = ((void*(__thiscall*)(void*))(*(void***)gd)[0x4c / 4])(gd);
        void* sm = SP_StarManager_00b3d2a0(slot);
        void* emp = cStarManager_GetEmpireByID_00ba9370(sm);
        if (emp != 0)
            StrAppendSprintf(str, "\nArchetype: %s\n", cEmpire_DebugArchetype_00c30eb0(emp));
    }
}

// @ 0x00c72d70
bool PlanetCls::FUN_00c72d70(int key)
{
    char* s = (char*)this;
    int* end = *(int**)(s + 0x11c4);
    int* r = (int*)FUN_00c72540(*(void**)(s + 0x11c0), end, &key,
                                *(unsigned char*)(s + 0x11d4));
    if (r == end || key < *r || r == (int*)((char*)r + 0xb0))
        r = end;
    if (r != end)
        return *(char*)((char*)r + 0xaa) != 0;
    return false;
}

// @ 0x00c72dd0
void PlanetCls::FUN_00c72dd0(int v)
{
    char* p = *(char**)((char*)this + 0x13c);
    int* vec = (int*)(p + 0xe4);
    int* cur = (int*)vec[1];
    if (cur < (int*)vec[2]) {
        vec[1] = (int)(cur + 1);
        if (cur != 0) {
            *cur = v;
            return;
        }
    } else {
        ((VecH_00b96600*)vec)->Push(cur, &v);
    }
}

// @ 0x00c72e10
void PlanetCls::FUN_00c72e10(char* pd)
{
    void* self = this;
    (void)self;
    int nVeh = *(int**)(pd + 0xb4) - *(int**)(pd + 0xb0);

    char* vehMap[3] = {0, 0, 0};
    if (nVeh > 0) {
        for (int i = 0; i < nVeh; ++i) {
            int v = (*(int**)(pd + 0xb0))[i];
            void* raw = FUN_00f473a0(0x14, "Simulator/cVehicleData", 0, 0, 0, 0);
            void* node = raw ? FUN_00ff0db0(v) : 0;
            FUN_00a110b0((void*)v, node);
            if (vehMap[1] < vehMap[2]) {
                int* p = (int*)vehMap[1];
                vehMap[1] = (char*)(p + 1);
                if (p) *p = (int)node;
            } else {
                ((VecH_00b96600*)vehMap)->Push(vehMap[1], &node);
            }
        }
    }

    void* civVec = FUN_00bef6c0();
    int nCity = (((int*)civVec)[1] - ((int*)civVec)[0]) >> 2;

    char* cityMap[3] = {0, 0, 0};
    if (nCity > 0) {
        for (int i = 0; i < nCity; ++i) {
            int v = *(int*)(((int*)civVec)[0] + i * 4);
            void* raw = FUN_00f473a0(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
            void* city = raw ? FUN_00ff23b0(v) : 0;
            void* name = ((void*(__thiscall*)(void*))(*(void***)(v + 0x34))[1])((void*)(v + 0x34));
            WStr_Assign(&cityMap[0], (const uint16_t*)name);
            FUN_00bd81e0(city);
            void* got = FUN_00bd81f0(city);
            if (cityMap[1] < cityMap[2]) {
                int* p = (int*)cityMap[1];
                cityMap[1] = (char*)(p + 1);
                if (p) *p = (int)got;
            } else {
                ((VecH_00b96600*)cityMap)->Push(cityMap[1], &got);
            }
        }
    }

    void* raw = FUN_00f473a0(0x50, "Simulator/cCivData", 0, 0, 0, 0);
    void* civ = raw ? FUN_00ff3220(pd, &vehMap[0], &cityMap[0]) : 0;
    FUN_00b8eec0(civ);
    int n = *(int**)(pd + 0xb4) - *(int**)(pd + 0xb0);
    for (int i = 0; i < n; ++i)
        FUN_00c9eae0(civ);

    if (cityMap[0] && *(int*)(cityMap[0] - 4) != 0)
        FUN_00f47380(cityMap[0]);
    if (vehMap[0] && *(int*)(vehMap[0] - 4) != 0)
        FUN_00f47380(vehMap[0]);
}

// @ 0x00c731a0
void FUN_00c731a0(void* self, char b2, void* p3, uint16_t w4, char b5, int d6, int d7, int d8, char b9)
{
    char* s = (char*)self;
    char local[0x2c];
    local[0x00] = *(int*)p3;
    local[0x04] = d6;
    local[0x08] = d7;
    local[0x0c] = d8;
    local[0x10] = w4;
    local[0x12] = b2;
    local[0x14] = 0;
    local[0x18] = 0;
    local[0x1c] = 0;
    local[0x20] = 0;
    local[0x24] = 0;
    local[0x28] = (char)((1 << ((b9 != 0) + 3)) | (-(b5 != 0) & 2) | 0x20);

    int* vec = (int*)(s + 0x134);
    if (vec[1] < vec[2]) {
        vec[1] += 0x2c;
        if (vec[1] != 0) {
            DoInsertValue_00ac9200(local);
            return;
        }
    } else {
        char* cur = (char*)vec[1];
        FUN_00acb810(cur, local);
    }
}

// @ 0x00c73250
bool PlanetCls::FUN_00c73250()
{
    return ((PlanetCls*)((TerrainSphere_00f67d90*)SP_NounManager_00b3d300())
                ->GetCurrentTerrainSphere())
        ->FUN_00c72d70((int)((CommRef_00ce6950*)*(void**)((char*)this + 0x13c))->GetCommContext());
}

// @ 0x00c73270
void PlanetCls::FUN_00c73270(int* key)
{
    char* p = *(char**)((char*)this + 0x13c);
    int* vec = (int*)(p + 0xbc);
    int* cur = (int*)vec[1];
    if (cur < (int*)vec[2]) {
        vec[1] = (int)(cur + 3);
        if (cur != 0) {
            cur[0] = key[0];
            cur[1] = key[1];
            cur[2] = key[2];
            return;
        }
    } else {
        ((VecH_004e3e10*)vec)->GrowAndAppend(cur, key);
    }
}

// @ 0x00c732c0
void PlanetCls::FUN_00c732c0(int* key)
{
    char* p = *(char**)((char*)this + 0x13c);
    int* vec = (int*)(p + 0xd0);
    int* cur = (int*)vec[1];
    if (cur < (int*)vec[2]) {
        vec[1] = (int)(cur + 3);
        if (cur != 0) {
            cur[0] = key[0];
            cur[1] = key[1];
            cur[2] = key[2];
            return;
        }
    } else {
        ((VecH_004e3e10*)vec)->GrowAndAppend(cur, key);
    }
}

// @ 0x00c73310
void PlanetCls::FUN_00c73310()
{
    char* p = *(char**)((char*)this + 0x13c);
    void* e = *(void**)(p + 0xc0);
    void* b = *(void**)(p + 0xbc);
    ((EaVec3*)(p + 0xbc))->erase(b, e);
}

// @ 0x00c73330
void PlanetCls::FUN_00c73330()
{
    char* p = *(char**)((char*)this + 0x13c);
    void* e = *(void**)(p + 0xd4);
    void* b = *(void**)(p + 0xd0);
    ((EaVec3*)(p + 0xd0))->erase(b, e);
}

// @ 0x00c73350
int PlanetCls::FUN_00c73350(int* key)
{
    char* s = (char*)this;
    int local[2];
    ((PlanetMap_00c729b0*)this)->find_00c729b0(&local[0], key);
    unsigned cur = (unsigned)local[0];
    if (cur == (unsigned)local[1])
        cur = *(unsigned*)(s + 4);
    unsigned end = *(unsigned*)(s + 4);
    if (cur != end) {
        if ((char*)cur + 0x10 < (char*)end)
            FUN_00705250((void*)((char*)cur + 0x10), (void*)end, (void*)cur);
        *(int*)(s + 4) -= 0x10;
        return 1;
    }
    return 0;
}

// @ 0x00c733b0
void PlanetCls::FUN_00c733b0()
{
    char* s = (char*)this;
    void* p = *(void**)(s + 0x188);
    if (p != 0) {
        void* nm = SP_NounManager_00b3d300();
        cGameNounManager_RemoveNoun_00b225d0(nm, p);
        p = *(void**)(s + 0x188);
        if (p != 0) {
            *(void**)(s + 0x188) = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        }
    }
    p = *(void**)(s + 0x154);
    if (p != 0) {
        void* nm = SP_NounManager_00b3d300();
        cGameNounManager_RemoveNoun_00b225d0(nm, p);
        p = *(void**)(s + 0x154);
        if (p != 0) {
            *(void**)(s + 0x154) = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        }
    }
    p = *(void**)(s + 0x18c);
    if (p != 0) {
        void* nm = SP_NounManager_00b3d300();
        cGameNounManager_RemoveNoun_00b225d0(nm, (char*)p + 0xd4);
        p = *(void**)(s + 0x18c);
        if (p != 0) {
            *(void**)(s + 0x18c) = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
        }
    }
    p = *(void**)(s + 0x1c0);
    if (p != 0) {
        *(void**)(s + 0x1c0) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
    }
    p = *(void**)(s + 0x13c);
    if (p != 0) {
        *(void**)(s + 0x13c) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    *(uint32_t*)(s + 0x148) = g_01693efc;
    *(uint32_t*)(s + 0x14c) = g_01693f00;
    *(uint32_t*)(s + 0x150) = g_01693f04;
    p = *(void**)(s + 0x13c);
    if (p != 0) {
        *(void**)(s + 0x13c) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    char* v = s + 0x170;
    for (int* it = *(int**)v; it != *(int**)(s + 0x174); ++it) {
        void* o = (void*)*it;
        ((void(__thiscall*)(void*, int))(*(void***)o)[0xc / 4])(o, 1);
    }
    FUN_00533500(*(void**)v, *(void**)(s + 0x174));
    FUN_00c723d0_local(this);
    p = *(void**)(s + 0x100);
    if (p != 0) {
        *(void**)(s + 0x100) = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
    FUN_00c8b2e0_00();
}

// @ 0x00c73520
void** PlanetCls::FUN_00c73520(void** out)
{
    out[0] = 0; out[1] = 0; out[2] = 0;
    char* p = *(char**)((char*)this + 0x13c);
    int n = *(int**)(p + 0x160) - *(int**)(p + 0x15c);
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            void* civ = ((void**)*(void**)(p + 0x15c))[i];
            PtrPair* cities = (PtrPair*)((CivData_005c65e0*)civ)->GetCities();
            int m = cities->end - cities->begin;
            for (int j = 0; j < m; ++j) {
                int* src = cities->begin + j;
                if (out[1] < out[2]) {
                    int* d = (int*)out[1];
                    out[1] = d + 1;
                    if (d) *d = *src;
                } else {
                    ((VecH_00b96600*)out)->Push(out[1], src);
                }
            }
        }
    }
    return out;
}

// @ 0x00c735e0
int* PlanetCls::FUN_00c735e0(int* key)
{
    char* s = (char*)this;
    int* beg = *(int**)s;
    int* end = *(int**)(s + 4);
    int* r = (int*)FUN_00d01260(beg, end, key, *(unsigned char*)(s + 0x14));
    if (r == end || *key < *r) {
        int k = *key;
        if (r == end || *r <= k) {
            r = (int*)FUN_00d01260(r, end, &k, *(unsigned char*)(s + 0x14));
        } else {
            r = (int*)FUN_00d01260(beg, r, &k, *(unsigned char*)(s + 0x14));
        }
        if (r == end || k < *r)
            FUN_00c72d00(r, &k);
    }
    return r + 1;
}

// @ 0x00c73680
void PlanetCls::FUN_00c73680()
{
    char* s = (char*)this;
    *(void**)s = &vtbl_CPlanet_014725d8;
    *(void**)(s + 0xd4) = &vtbl_CPlanet_gd_01472580;
    *(void**)(s + 0xd8) = &vtbl_CPlanet_d8_01472570;
    void* sm = SP_StarManager_00b3d2a0(s);
    FUN_00ba70d0(sm);
    FUN_00c733b0();

    void* p = *(void**)(s + 0x1c0);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
    cGonzagoTimer_dtor_00b638b0(s + 0x198);
    p = *(void**)(s + 0x18c);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
    p = *(void**)(s + 0x188);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    FUN_004b5440(s + 0x170);
    {
        int* a = *(int**)(s + 0x15c);
        int* b = *(int**)(s + 0x164);
        int d = ((char*)b - (char*)a) & 0xfffffffe;
        if (d > 2 && a != 0)
            FUN_00f47380(a);
    }
    p = *(void**)(s + 0x154);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = *(void**)(s + 0x13c);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    int* m = *(int**)(s + 0x138);
    if (m != 0) {
        if (m[0x40 / 4] > 1) {
            m[0x40 / 4] -= 1;
            cGameData_dtor_00b184c0(s + 0xd4);
            FUN_00c8a420();
            return;
        }
        unsigned f = (unsigned)m[1] >> 31;
        ((void(__thiscall*)(void*, unsigned))(*(void***)m)[0x170 / 4])(m, f);
    }
    cGameData_dtor_00b184c0(s + 0xd4);
    FUN_00c8a420();
}

// @ 0x00c73b60
void PlanetCls::FUN_00c73b60()
{
    char* s = (char*)this;
    FUN_00b8de60(*(void**)(s + 0x13c));
    FUN_00b8df20(*(void**)(s + 0x13c));

    void* nm = SP_NounManager_00b3d300();
    void* vec = SP_cGameNounManager_GetGameDataVector(nm, (void*)0x00b21080, (void*)0x00d3d420,
                                                      (void*)0x00b236c0, (void*)0x00b1e500,
                                                      (void*)0x018c816a);
    int n = *(int**)((char*)vec + 8) - *(int**)((char*)vec + 4);
    for (int i = 0; i < n; ++i) {
        char* t = *(char**)(*(int**)((char*)vec + 4) + i * 4);
        void* civ = FUN_00bef6c0();
        if (*(int*)civ != *(int*)((char*)civ + 4) ||
            *(int*)(t + 0xb0) != *(int*)(t + 0xb4))
            FUN_00c72e10(t);
    }

    void* vec2 = SP_cGameNounManager_GetGameDataVector(nm, (void*)0x00cd7d10, (void*)0x00d3d420,
                                                       (void*)0x00accbb0, (void*)0x00b1e500,
                                                       (void*)0x018c6d19);
    int n2 = *(int**)((char*)vec2 + 8) - *(int**)((char*)vec2 + 4);
    for (int i = 0; i < n2; ++i) {
        int v = *(int*)(*(int**)((char*)vec2 + 4) + i * 4);
        void* raw = FUN_00f473a0(0x18, "Simulator/cTribeData", 0, 0, 0, 0);
        void* td = raw ? cTribeData_ctor_00ff0610(v) : 0;
        FUN_00c8ea30((void*)v, td);
        FUN_00b8ef00(*(void**)(s + 0x13c), td);
    }
}

// @ 0x00c73cb0
void* PlanetCls_s00c7_3cb0::FUN_00c73cb0(void* key)
{
    return (char*)mScanned.find(&key) + 0x20;
}

// @ 0x00c73cd0
void* PlanetCls_s00c7_3cb0::FUN_00c73cd0(void* key)
{
    return (char*)mScanned.find(&key) + 0x68;
}

// @ 0x00c73cf0
void PlanetCls_s00c7_3cb0::FUN_00c73cf0(int flag)
{
    if (mPData == 0) return;
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[0];
    for (Key12* it = (Key12*)mPData->mVecBC.begin; it != (Key12*)mPData->mVecBC.end;
         it = (Key12*)((char*)it + 0xc)) {
        char* end = (char*)m->end;
        char* r = (char*)eastl_lower_bound(m->begin, end, it, m->mCmp14);
        if (r == end || KeyLess(it, r) || r == r + 0x10)
            r = end;
        if (r == end || *(char*)(r + 0xc) == 0) {
            *(char*)m->insert(it) = 1;
            void* e = FUN_00ba57f0(it, 2);
            if ((char)flag) ((Notifier*)FUN_00b3d4f0(e))->Notify();
        }
    }
    for (Key12* it = (Key12*)mPData->mVecD0.begin; it != (Key12*)mPData->mVecD0.end;
         it = (Key12*)((char*)it + 0xc)) {
        char* end = (char*)m->end;
        char* r = (char*)eastl_lower_bound(m->begin, end, it, m->mCmp14);
        if (r == end || KeyLess(it, r) || r == r + 0x10)
            r = end;
        if (r == end || *(char*)(r + 0xc) == 0) {
            NotifyScannedCreatureSpecies(it, flag);
            *(char*)m->insert(it) = 1;
            void* e = FUN_00ba5650(it, 2);
            if ((char)flag) ((Notifier*)FUN_00b3d4f0(e))->Notify();
        }
    }
}

// @ 0x00c73ea0
char PlanetCls_s00c7_3cb0::SetSpeciesAsScanned(void* key)
{
    void* local[2];
    local[0] = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&local[0]);
    EaMap* m = &node->mMaps[0];
    m->find(&local[0], key);
    char* cur = (char*)local[0];
    if (cur == (char*)local[1]) cur = (char*)m->end;
    char* end = (char*)m->end;
    if (cur != end) return *(char*)(cur + 0xc);
    return 0;
}

// @ 0x00c73f10
char PlanetCls_s00c7_3cb0::IsSpeciesScanned(void* key)
{
    void* local[2];
    local[0] = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&local[0]);
    EaMap* m = &node->mMaps[1];
    m->find(&local[0], key);
    char* cur = (char*)local[0];
    if (cur == (char*)local[1]) cur = (char*)m->end;
    char* end = (char*)m->end;
    if (cur != end) return *(char*)(cur + 0xc);
    return 0;
}

// @ 0x01317720
namespace Simulator {
void InitPlantAttributes()
{
    cSPTransform defaultTransform;
    ADD2(0,  "mTransform", 0x05668f36, 0xc, Read_00aff7e0, Write_00aff810, ReadText_00c2e4e0, WriteText_00692fb0,
              AlwaysValid<Tag_mTransform>, ToXml_00ac8050, SetDefault_00b02520, StoreTransform(defaultTransform))
    ADD2(1,  "mFruit", 0x05668f38, 0x48, Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0,
              AlwaysValid<Tag_mFruit>, ToXml_00595a70, SetDefault_00aff8b0, StoreU64(&sFruitDefault, 0))
    ADD2(2,  "mSeqId", 0x05810db9, 0x50, SHORT_ATTR(UInt_mSource), SetDefault_00aff8d0, StoreU32(&sSeqIdDefault, 0))
    ADD2(3,  "mSeqIndex", 0x05810dba, 0x54, SHORT_ATTR(UInt_mTarget), SetDefault_00aff8f0, StoreU32(&sSeqIndexDefault, 0))
    ADD2(4,  "mSizeBracket", 0x05810dbb, 0x58, SHORT_ATTR(UInt_mPlanetKey), SetDefault_00aff910,
              StoreU32(&sSizeBracketDefault, 0x6d60a1cc))
    ADD2(5,  "mpWhoIsInteractingWithMe", 0x05810dbc, 0x68, Read_00b02540, Write_00bca960, ReadText_00c2e4e0,
              WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, SetDefault_00b002e0, StoreNullObject(0))
    ADD2(6,  "mSpeciesKey", 0x05810dbe, 0x5c, Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
              AlwaysValid<Tag_mKey>, ToXml_00ae5720, SetDefault_00aff930, StoreNullKey(0))
    ADD2(7,  "mBaseRadius", 0x05810dbf, 0x6c, FLOAT_ATTR, SetDefault_00aff980, StoreFloat(&sBaseRadiusDefault, 0.0f))
    ADD2(8,  "mCanopyRadius", 0x0595fd21, 0x70, FLOAT_ATTR, SetDefault_00aff9a0, StoreFloat(&sCanopyRadiusDefault, 0.0f))
    ADD2(9,  "mHeight", 0x0595fdff, 0x74, FLOAT_ATTR, SetDefault_00aff9c0, StoreFloat(&sHeightDefault, 0.0f))
    ADD2(10, "mbRemoved", 0x06abf15d, 0x7c, BOOL_ATTR, SetDefault_00aff9e0, StoreByte(&sRemovedDefault, 0))
    // "field_name" sentinel: a static record (id -1, no callbacks) built in place at table slot 11.
    new (&cPlant_sAttributes[11]) Attribute("field_name", 0xffffffff, (void*)0, 0, 0, 0, 0, 0);
}
}  // namespace Simulator

// @ 0x0134f690
void RegisterPlanetAttributes()
{
    SimAttribute t;

    t.mName = "mpPlanetSim";
    t.mHash = 0x35d9760;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00c724d0;
    t.mFnLoad = &cAgentOrderManager_ActivateOne;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &FUN_00b6f550;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x154;
    gPlanetAttributes[0] = t;

    t.mName = "mpVisiblePlanet";
    t.mHash = 0x4457f99;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00c72500;
    t.mFnLoad = &FUN_00bdd350;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &FUN_00b6f550;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x18c;
    gPlanetAttributes[1] = t;

    t.mName = "mParent";
    t.mHash = 0x30d5fd2;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &operator__SP_cPlanet;
    t.mFnLoad = &FUN_00bdd350;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &FUN_00b6f550;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x1c0;
    gPlanetAttributes[2] = t;

    t.mName = "mOrbitedPlanetLastKnownPosition";
    t.mHash = 0x37d2e7b;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00b6e3a0;
    t.mFnLoad = &FUN_00ac88c0;
    t.mFnParse = &ParseVector3;
    t.mFnEdit = &FUN_00695010;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_00acbba0;
    t.mOffset = 0x148;
    gPlanetAttributes[3] = t;

    t.mName = "mTimeSinceLastColonyPlaced";
    t.mHash = 0x57a58cf;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00ae3470;
    t.mFnLoad = &FUN_00ae3490;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &FUN_00ae3310;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x198;
    gPlanetAttributes[4] = t;

    t.mName = "mPlanetFlags";
    t.mHash = 0x35d5a50;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00b72e30;
    t.mFnLoad = &FUN_00b74a40;
    t.mFnParse = &UTFWin_ILayoutElement_SetSerializer;
    t.mFnEdit = &ClearBuffer;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_00ac8050;
    t.mOffset = 0x1bc;
    gPlanetAttributes[5] = t;

    t.mName = "mPlanetKey";
    t.mHash = 0x355f943;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &WriteUint32Value;
    t.mFnParse = &ParseULong;
    t.mFnEdit = &FUN_00694f00;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &Simulator_ToXml;
    t.mOffset = 0x140;
    gPlanetAttributes[6] = t;

    t.mName = "mNumSpecializedBehaviorUFOs";
    t.mHash = 0x519a04c;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &WriteUint32Value;
    t.mFnParse = &ParseLong;
    t.mFnEdit = &FUN_00694ee0;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_0057cde0;
    t.mOffset = 0x108;
    gPlanetAttributes[7] = t;

    t.mName = "mImpostorModel";
    t.mHash = 0x3742a6e;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00ac87c0;
    t.mFnLoad = &FUN_00ac87f0;
    t.mFnParse = &FUN_00694c80;
    t.mFnEdit = &FUN_00694c10;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_00acbbc0;
    t.mOffset = 0x15c;
    gPlanetAttributes[8] = t;

    t.mName = "mEffectScript";
    t.mHash = 0x3742a83;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &WriteUint32Value;
    t.mFnParse = &ParseULong;
    t.mFnEdit = &FUN_00694f00;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &Simulator_ToXml;
    t.mOffset = 0x16c;
    gPlanetAttributes[9] = t;

    t.mName = "mPlanetScale";
    t.mHash = 0x3741dd7;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &FUN_00ac88f0;
    t.mFnParse = &ParseFloat;
    t.mFnEdit = &FUN_00694fc0;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &FUN_00acbb80;
    t.mOffset = 0x184;
    gPlanetAttributes[10] = t;

    t.mName = "mStarterWorldID";
    t.mHash = 0x3742ea6;
    t.mDefaultLow = 0;
    t.mDefaultHigh = 0;
    t.mFnDefault = &gSimAttributeDefaultOffset;
    t.mFnSave = &FUN_00572810;
    t.mFnLoad = &WriteUint32Value;
    t.mFnParse = &ParseULong;
    t.mFnEdit = &FUN_00694f00;
    t.mFnUI = &UTFWin_Window_Initialize;
    t.mFnExtra = &Simulator_ToXml;
    t.mOffset = 0x144;
    gPlanetAttributes[11] = t;
}
