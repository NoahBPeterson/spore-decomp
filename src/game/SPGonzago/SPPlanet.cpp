// src/game/SPGonzago/SPPlanet.cpp -- migrated from slice(s) s00c6f6e0, s00b0b3d0, s00b0a590, s00b08670, s00b07980, s00b06e10, s00b05980, s00b03820, s0134f690, s01315a50, s00c73cb0, s00c72c60, s00b0c190, s00b09570, s00b047b0, s00b02830, s00b01690, s00b00520, s00afef10, s00ac0180 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlanet.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_145c660[];
extern "C" char g_145c71c[];
extern "C" char g_145c738[];
extern "C" char g_145c748[];

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
#include "SP/cInteractableObject.h"
#include <math.h>
#include <string.h>
#include "SP/cDefaultBeamProjectile.h"
#include "SP/cSPSpaceToolData.h"
#include "SP/cViewer.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cHierGrid.h"
#include "SP/cCityData.h"

// ---- items of slice s00afef10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t gVarListDataFruit[];     // 0x01567860
extern uint8_t gVarListDataGame[];      // 0x0167b858
extern uint8_t gStateData[];            // 0x01567410
extern uint32_t gFruitMessageIds[];     // 0x0145c6b0
extern uint32_t gNextFruitId;           // 0x0167af58
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
class IStream_s00af_ef10 {
public:
    uint8_t mnPad00[0x04];  // +0x00
};
class IAVIStream {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual IStream_s00af_ef10* GetStream();   // +0x18
};
class cOutStream {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual IAVIStream* GetIO();    // +0x20
};
namespace EA {
namespace IO {
bool WriteUint32(IStream_s00af_ef10* pStream, const uint32_t* pValue, int32_t nCount,
                 int32_t nFlags); // 0x0093aa70
}
}
namespace EA {
namespace IO {
bool WriteUint64(IStream_s00af_ef10* pStream, const uint64_t* pValue, int32_t nCount,
                 int32_t nFlags); // 0x0093ab10
}
}
class cRefObject {
public:
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
};
template <class T>
class AutoRefCount {
public:
    T* mpObject;                // +0x00
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount()
    {
        if (mpObject != 0)
            mpObject->Release();
    }
    AutoRefCount& operator=(T* pObject)
    {
        if (mpObject != pObject) {
            if (pObject != 0)
                pObject->AddRef();
            T* pOld = mpObject;
            mpObject = pObject;
            if (pOld != 0)
                pOld->Release();
        }
        return *this;
    }
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
uint32_t CountBits(uint32_t nValue)
{
    nValue = nValue - ((nValue >> 1) & 0x55555555);
    nValue = (nValue & 0x33333333) + ((nValue >> 2) & 0x33333333);
    nValue = ((nValue >> 4) + nValue) & 0x0f0f0f0f;
    return (nValue * 0x01010101) >> 24;
}
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
    void Load(IStream_s00af_ef10* pStream);  // 0x006b9230
    void Save(IStream_s00af_ef10* pStream);  // 0x006b9190
};
class cRotList {
public:
    RotSerial* mpBegin;                 // +0x00
    RotSerial* mpEnd;                   // +0x04
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
class cRBNode {
public:
    uint8_t mnPad00[0x18];              // +0x00
    cSerializeItem* mpItem;             // +0x18
};
cRBNode* RBTreeIncrement(cRBNode* pNode); // 0x00921580
class cRBTreeAnchor {
public:
    uint32_t mnColor;                   // +0x00
    cRBNode* mpParent;                  // +0x04
    cRBNode* mpLeft;                    // +0x08
    cRBNode* mpRight;                   // +0x0c
};
class cRBTree {
public:
    uint32_t mnPad00;                   // +0x00
    cRBTreeAnchor mAnchor;              // +0x04
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
class cVarListSerializer_s00af_ef10 {
public:
    uint8_t mnData[0xa14];              // +0x000
    cVarListSerializer_s00af_ef10(void* pOwner, void* pVarList, uint32_t nKey); // 0x00692f90
    bool Serialize(cOutStream* pStream);                             // 0x00692900
};
class cGameData_s00af_ef10 {
public:
    bool Write(cOutStream* pStream);    // 0x00b18590
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
class cFruitGameData : public cGameData_s00af_ef10 {
public:
    bool WriteData(cOutStream* pStream);   // 0x00aff5e0
};
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
class cSubState {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14)
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21)
    VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30) VSLOT(31) VSLOT(32) VSLOT(33) VSLOT(34) VSLOT(35)
    VSLOT(36)
    virtual void SetData(void* pData);  // +0x94
};
class cStateObject {
public:
    uint8_t mnPad00[0x34];              // +0x000
    cSubState mSub;                     // +0x034
    uint8_t mnPad38[0xa3 - 0x38];       // +0x038
    uint8_t mbFlagA3;                   // +0x0a3
    uint8_t mbFlagA4;                   // +0x0a4
    uint8_t mbFlagA5;                   // +0x0a5
    uint8_t mnPadA6[0x108 - 0xa6];      // +0x0a6
    cRefObject* mpObject108;            // +0x108
    uint8_t mnPad10c[0x168 - 0x10c];    // +0x10c
    uint32_t mField168;                 // +0x168
    uint32_t mnState;                   // +0x16c
    void SetState(int32_t nState, bool bForce); // 0x00b00080
};
class cSubObject {
public:
    VSLOT(0)
    virtual void Release();             // +0x04
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13)
    virtual void Close();               // +0x38
};
class cSplitSerializer {
public:
    uint32_t mField00;                  // +0x00
    uint32_t mnPad04;                   // +0x04
    uint32_t mField08;                  // +0x08
    uint32_t mField0c;                  // +0x0c
    cSubObject* mpReader;               // +0x10
    cSubObject* mpWriter;               // +0x14
    uint32_t mField18;                  // +0x18
    void Reset();                       // 0x00b00150
};
namespace EA {
namespace Messaging {
class Server_s00af_ef10;
}
}
namespace EA {
namespace Messaging {
class IHandler_s00af_ef10 {
public:
    uint8_t mnPad00[0x04];              // +0x00
};
}
}
namespace EA {
namespace Messaging {
Server_s00af_ef10* GetServer(); // 0x00883860
}
}
namespace EA {
namespace Messaging {
class Server_s00af_ef10 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8)
    virtual void AddHandler(IHandler_s00af_ef10* pHandler, uint32_t nMessageId); // +0x24
};
}
}
class cSPEditorAnimatedCreatureData_s00af_ef10 {
public:
    uint8_t mnPad00[0x04];              // +0x00
    void SetLastAnimationPlayed(uint32_t nAnimation); // 0x007cd950
    void ResetAnimation();                            // 0x007cd960
};
class cFruitEditorData : public EA::Messaging::IHandler_s00af_ef10 {
public:
    uint8_t mnPad00[0x1c];              // +0x00004
    EA::Messaging::Server_s00af_ef10* mpServer;    // +0x00020
    EA::Messaging::IHandler_s00af_ef10* mpHandler; // +0x00024
    uint32_t* mpIdArray;                // +0x00028
    uint32_t mnIdCount;                 // +0x0002c
    int32_t mnPriority;                 // +0x00030
    uint8_t mnPad34[0x1b8f30 - 0x34];   // +0x00034
    cSPEditorAnimatedCreatureData_s00af_ef10* mpCreatureData; // +0x1b8f30
    uint8_t mnPad1b8f34[0x1ba18c - 0x1b8f34]; // +0x1b8f34
    uint32_t mnFlags;                   // +0x1ba18c
    void OnCreated();                   // 0x00b001b0
};
class cGameNounManager_s00af_ef10 {
public:
    cFruit* CreateNoun(uint32_t nType); // 0x00b20c60
};
cGameNounManager_s00af_ef10* NounManager(uint32_t nType); // 0x00b3d300
cFruit* CreateFruit();                  // 0x00b00220
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
struct TreeClumpArchive { bool AddChild(void* data, const void* type, const wchar_t* name); };
extern const char gTreeClumpType; // 0x01567428
extern const wchar_t gTreeClumpName[]; // 0x0145c4b0
void operator_delete__(void* pMemory);
typedef unsigned int       u32;
struct CRBTreeFind { void find(u32* out, const u32* key); };             // 0x00e5c780
#define RBF(p) ((CRBTreeFind*)(p))
// ---- items of slice s00b00520 end

// ---- items of slice s00b01690 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned short     u16;
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
void* SP_EffectsManager(void);                                           // 0x0067ddd0
void* SP_GetCurrentGameMode(void);                                       // 0x00b5b800
void* SP_NounManager(void*);                                             // 0x00b3d300
void  FUN_00b3d320(void);                                                // 0x00b3d320
void* FUN_00b1daf0(void);                                                // 0x00b1daf0
void* SP_cGameNounManager_CreateNoun(void* key);                         // 0x00b20c60
void* SP_GetActiveTerrainSphere(void);                                   // 0x00f48aa0
void  SP_cHierGrid_Shutdown(void);                                       // 0x00704060
void  SP_cHierGrid_Init(void* self, const void* v, float f, int a, int b); // 0x00704260
u32   SP_cHierGrid_CreateEntry(void* self, const void* v, float f);      // 0x00703d50
void  SP_HierGridStub_Remove(void* self, u32 i);                         // 0x00702da0
struct TreeApplyTarget { void SetKey(u32 id, float key); };              // 0x00a887b0
void  FUN_00a057f0(void* a, const void* b);                              // 0x00a057f0
void  XformMsg_ctor(void* p);                                            // 0x00434040
void* cProperty_GetBool(void* p);                                        // 0x0041e920
void* cProperty_GetInt(void* p);                                         // 0x0041e990
void* cProperty_GetFloat(void* p);                                       // 0x0041ea70
void  GridRebuildProxy(void* self);                                      // 0x00b02120
struct CTransformAssignOps {
    void* Assign(const void* src);                    // 0x00537dc0
};
static f32 g_167af5c_s00b0_1690 = 0.0f;             // 0x0167af5c
static f32 g_167af60_s00b0_1690 = 0.0f;             // 0x0167af60
static f32 g_167af64_s00b0_1690 = 0.0f;             // 0x0167af64
static u32 g_167b550_s00b0_1690 = 0;                // 0x0167b550
static f32 g_167af5c = 0.0f;             // 0x0167af5c
static f32 g_167af60 = 0.0f;             // 0x0167af60
static f32 g_167af64 = 0.0f;             // 0x0167af64
static u32 g_167b550 = 0;                // 0x0167b550
static f32 g_1567398 = 0.0f;             // 0x01567398
static f32 g_156739c = 0.0f;             // 0x0156739c
static f32 g_15673a0 = 0.0f;             // 0x015673a0
static u32 g_15673a4_s00b0_1690 = 0;                // 0x015673a4
static u32 g_15673c0 = 0, g_15673c4 = 0; // 0x015673c0 / 0x015673c4
static u32 g_15673c8 = 0, g_15673cc = 0; // 0x015673c8 / 0x015673cc
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
struct cFruitGroupOps_s00b0_1690 {
    void SetEffect(u32 mode, u8 force);
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
struct GridEntryOps {
    void SetEntry(void* obj, u8 add);
};
struct PairTreeOps {
    void Find(void* out, const u32* key);
    void FindNode(u32* out, const u32* key);   // 0x00a057f0
};
struct TreeApplyOps {
    void Apply(void* key, u32 id, u32 arg);
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
extern char gVtblFruitGroup[];        // 0x0145c71c
extern char gVtblRegNodeSdtor[];                 // 0x0145c6c0
extern float g_HK_REAL_ONE;       // 0x01485720
extern char  g_matrixIdentity[];  // 0x0167b554
extern float g_zero3a[];          // 0x0167af5c, 0x0167af60, 0x0167af64
#pragma intrinsic(memset, memcpy)
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned __int64 uint64;
void __cdecl FUN_00b014f0(void* first, void* last, int holeIndex, void* top, float* pos);
void __cdecl FUN_00b015c0(void* first, void* last, int holeIndex, void* top,
                          float px, float py, float pz);
void __cdecl FUN_00b01690(void* first, void* last, int holeIndex, void* top,
                          float px, float py, float pz);
void* __cdecl FUN_006271a0(void* out, void* a, void* b);
void* __cdecl FUN_0059c190(void* out, void* q);
struct Op_s00b0_2830 {
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
void* __cdecl FUN_00b3d420(void* self);
void* __cdecl FUN_00b3d440(void);
void* __cdecl FUN_00b3d3b0();          // returns the global singleton at 0x0167eb10
void* __cdecl FUN_00401090();
struct RbtLookup { void* Find(void* out, void* key); };
void __cdecl FUN_00a887b0(uint32 a, float f);
struct Op {
    void* M18660();                    // 0x00b18660 SP::cGameData::cGameData
    void  M03d0();                     // 0x00ac03d0 SP::cInteractionTarget::cInteractionTarget
    void  M3f9b0();                    // 0x00c3f9b0
    void  M3f9a0(u32);                 // 0x00c3f9a0
    void  M0520();                     // 0x00ac0520
    void  M184c0();                    // 0x00b184c0
    void* Mecdba0();                   // 0x00ecdba0
    int   Mb8dab0();                   // 0x00b8dab0
    void* Mba9370(void* arg);          // 0x00ba9370
    void* Mc30eb0();                   // 0x00c30eb0
    void* Mc92af0();                   // 0x00e92af0 cSpatialObjectView ctor
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
void* __cdecl FUN_00921580(void* node);
void __cdecl FUN_00f47380(void* p);
void __cdecl FUN_011e07ef(void (*fn)());
uint32 __cdecl FUN_011e08d0(uint32 hi, uint32 lo, int sh);
void  __cdecl FUN_011e06e0(uint32* out, int sh);   // returns edx:eax
char __cdecl FUN_0093aa70(void* stream, const void* p, int n, int e);
char __cdecl FUN_0093ab10(void* stream, const void* p, int n, int e);
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
struct TmpXform {
    uint16 a;             // +0x00
    uint16 b;             // +0x02
    float  x;             // +0x04
    float  y;             // +0x08
    float  z;             // +0x0c
    uint32 pad10;         // +0x10
    float  w;             // +0x14
    float  m00, m01, m02; // +0x18 transform matrix (9 floats, 0x24 bytes)
    float  m10, m11, m12;
    float  m20, m21, m22;
};
struct cFruitGroupSlots {
    uint32 pad00[0xc / 4];
    uint16 mW0;         // +0x0c
    uint16 mW1;         // +0x0e
    float  f10;         // +0x10
    float  f14;         // +0x14
    float  f18;         // +0x18
    float  f1c;         // +0x1c
    uint8  mTransform[0x38];  // +0x20
    uint32 pad58;
    uint32 p5c;
    void GetFruitPos(float* out, int idx);
};
struct cModelWorld {
    uint32 pad00[0x6b8 / 4];   // +0x0000
    void*  mpPieces;           // +0x6b8  array, stride 0x38
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
struct cSPTransform_s00b0_2830 {
    uint16 flags;         // +0x00
    uint16 modCount;      // +0x02
    float  tx, ty, tz;    // +0x04
    float  scale;         // +0x10
    float  rot[9];        // +0x14
};
struct cModelHolder {
    uint32 pad00[0x10 / 4];
    void*  mpChild;       // +0x10
};
struct cSpeciesProfile {
    uint32 pad00[0x6b8 / 4];       // +0x0000
    cSPTransform_s00b0_2830* mpTransforms;    // +0x6b8  array, stride 0x38
};
struct cPieceElem {
    uint32 pad00[0x10 / 4];    // +0x00
    float  x, y, z;            // +0x10
    float  quat[4];            // +0x1c
    uint8  rest[0x2bc - 0x2c]; // +0x2c ... element stride is 0x2bc
};
struct cCreatureModel {
    uint32 pad00[0x70 / 4];    // +0x00
    float  scale;              // +0x70
    uint32 pad74[0x270 / 4];   // +0x74 .. +0x2e3
    cPieceElem* mpElemBegin;   // +0x2e4
    cPieceElem* mpElemEnd;     // +0x2e8
};
struct cCreature {
    uint32 pad00[0x17c / 4];   // +0x00
    cCreatureModel* mpModel;   // +0x17c
};
struct cTreeSlot {
    cSPTransform_s00b0_2830 xform;        // +0x00
    uint32 extra[5];           // +0x38
};
struct cFruitTreeNode {
    uint32 pad00[0x18 / 4];    // +0x00
    uint32 key;                // +0x18
    uint32 pad1c[0x14 / 4];    // +0x1c .. +0x2f
    cTreeSlot* mpSlots;        // +0x30
};
struct cFruitTreeRoot {
    uint32 pad00[0x8080 / 4];  // +0x0000
    uint32 mHeader;            // +0x8080  find entry (this)
    uint32 mEndNode;           // +0x8084  end sentinel
};
struct cFruitGroupOps {
    uint32 pad00[0x34 / 4];
    RbtLookup mLookup;          // +0x34
    uint32 FindNth(uint32 a, uint32 b, uint32 c);
};
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
struct cSaveNode {
    uint32 pad00[4];     // +0x00
    uint32 key0;         // +0x10
    uint32 key1;         // +0x14
    void*  mpObj;        // +0x18
};
struct cSaveTreeHdr {
    uint32 pad00;        // +0x00
    void*  mpEnd;        // +0x04  (sentinel node address = hdr + 4)
    void*  mpFirst;      // +0x08
    uint32 pad0c[2];     // +0x0c
    uint32 firstKey;     // +0x14
};
struct cTreeData {
    void*  vtbl0;              // +0x00
    void*  vtbl1;              // +0x04
    uint32 m08;                // +0x08
    uint16 m0c;                // +0x0c
    uint16 m0e;                // +0x0e
    float  tx;                 // +0x10
    float  ty;                 // +0x14
    float  tz;                 // +0x18
    float  scale;              // +0x1c
    float  rot[9];             // +0x20 (matrix; 0x24 bytes)
    uint32 m44_unused;         // +0x44 (not copied by the ctor / operator=)
    uint32 m48;                // +0x48
    uint32 m4c;                // +0x4c
    uint32 m50;                // +0x50
    uint32 m54;                // +0x54
    uint32 m58;                // +0x58
    uint32 m5c;                // +0x5c
    uint32 m60;                // +0x60
    uint32 m64;                // +0x64
    void*  mp68;               // +0x68  refcounted
    float  f6c;                // +0x6c
    float  f70;                // +0x70
    float  f74;                // +0x74
    uint32 m78;                // +0x78
    uint8  m7c;                // +0x7c
    cTreeData(void* src);
    cTreeData& operator=(cTreeData const& rhs);
};
extern char gVtblFruitGroup2[];       // 0x0145c748
extern char gVtblFruitGroup3[];       // 0x0145c738
extern char gVtblTreeData[];          // 0x0145c678
extern char gVtblTreeData2[];         // 0x0145c668
extern char gVtblContentValidationSummarizer[];  // 0x013ec458
// ---- items of slice s00b02830 end

// ---- items of slice s00b047b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_allocName_13ebb38[];                                         // 0x013ebb38
extern char g_allocFile_13f09b4[];                                         // 0x013f09b4
typedef unsigned int   uint;
struct HeapPos {
    float x, y, z;
    HeapPos(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    HeapPos(const HeapPos& o) : x(o.x), y(o.y), z(o.z) {}
};
void  make_heap_range2(void* a, void* b, HeapPos pos);       // 0x00b03e40
void  sort_heap_range2(void* a, void* b, float x, float y, float z);       // 0x00b03ea0
void  heap_adjust(void* a, int n, int i, int j, void* v, float x, float y, float z); // 0x00b02a40
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
void  operator_delete(void* p);                                            // 0x00f47380
void* EAAllocate(uint size, const char* cat, int a, int b, const char* file, int line); // 0x00f473a0
void  vect_copy(void* dst, void* first, void* last);                       // 0x005f4d00
void  memcpy_(void* dst, void* src, uint n);                               // 0x011e0744
void  DoInsertValueI(void* v, uint* at, const uint* v2);                   // 0x004558a0
void  ReadInt32(void* stream, void* out, int n, int flags);                // 0x0093a780
void* RBTreeIncrement(void* n);                                            // 0x00921580
void  RBTreeErase(void* n, void* head);                                    // 0x00921880
void  RBTreeInsert(void* n, void* parent, void* head, int side);           // 0x009216a0
void* rbtree_find(void* root, void* head, void* key, unsigned char flag);  // 0x00b02750
void* FUN_00b3d3b0(void* a);                                               // 0x00b3d3b0
void* FUN_00b2b1e0(void* a);                                               // 0x00b2b1e0
void  release_node_chain(void* p);                                         // 0x00b04350
void* GetSpeciesFromID(void* mgr, int id);                                 // 0x00b90410
uint  FUN_00b8f860(void* species);                                         // 0x00b8f860
void  reserve_tex(void* vec, uint n);                                      // 0x004e0880
struct VVec {
    int* mpBegin_00;
    int* mpEnd_04;
    int* mpCap_08;
    void* erase(void* first, void* last);
    void  reserve(uint n);       // 0x00b04c50
};
struct PoolOwner_s00b0_47b0 {
    void  rbcontainer_copy(void* src);       // 0x00b04520 (thiscall, 1 stack arg)
    void* AllocNode(const uint* k);          // 0x00b03820
    void* AllocNodeTiny(const uint* k);      // 0x00b03880
    void  release_node_chain(void* p);       // 0x00b04350
};
struct PoolElem;
struct NodeBase {
    NodeBase* mpLeft_00;      // +0x00
    NodeBase* mpRight_04;     // +0x04
    NodeBase* mpParent_08;    // +0x08
    uint8_t   mColor_0c;      // +0x0c
    uint8_t   pad0d[3];       // +0x0d
};
struct Payload {
    void*    mpTarget_00;            // +0x00
    uint32_t mRest_04[0x50 / 4 - 1]; // +0x04 .. +0x67
    void CopyFrom(const Payload* src); // 0x00b01cb0 (thiscall copy-ctor)
};
struct PoolElem {
    PoolElem* mpLink0_00;     // +0x00  child / free-list link
    PoolElem* mpLink1_04;     // +0x04  child / chain link
    PoolElem* mpParent_08;    // +0x08
    uint8_t   mColor_0c;      // +0x0c
    uint8_t   pad0d[3];       // +0x0d
    uint32_t  mKeyA_10;       // +0x10
    uint32_t  mKeyB_14;       // +0x14
    Payload   mPayload_18;    // +0x18
};
struct SlottedObj {
    uint32_t pad00[0x68 / 4]; // +0x00 .. +0x64
    void*    mpSub_68;        // +0x68  polymorphic object (vtable[1] released)
    uint32_t pad6c[4];        // +0x6c .. +0x7b
    uint8_t  mFlag_7c;        // +0x7c
    uint8_t  pad7d[3];        // +0x7d
};
struct RBTree : PoolOwner_s00b0_47b0 {
    void*    mpvptr_00;       // +0x00  vptr
    NodeBase mAnchor_04;      // +0x04  sentinel node
    int      mnSize_14;       // +0x14  element count
    int*     mpFree_18;       // +0x18  free-list head
    uint32_t mPad_1c;         // +0x1c  (unused gap)
    int*     mpPoolBegin_20;  // +0x20  pooled-node range begin
    int*     mpPoolEnd_24;    // +0x24  pooled-node range end
    uint32_t mnStride_28;     // +0x28  node allocation size

    void  eraseRange(int* out, void* first, void* last);   // 0x00b04ed0
    void  insert(int* out, uint* key, uint hint);          // 0x00b04f70
    void* copyNode(PoolElem* src, PoolElem* parent);       // 0x00b05000
};
struct LeafVec {
    void** mpBegin_00;        // +0x00
    void** mpEnd_04;          // +0x04
};
struct AllocHdr {
    uint32_t mSize_00;        // +0x00  owned size (0 => not owned)
};
struct Leaf {
    uint32_t mPad_000[0x4c / 4];             // +0x000 .. +0x048
    LeafVec  mVec_04c;                       // +0x04c
    uint32_t mPad_054[(0xa4 - 0x54) / 4];    // +0x054 .. +0x0a0
    LeafVec  mVec_0a4;                       // +0x0a4
    uint32_t mPad_0ac[(0xfc - 0xac) / 4];    // +0x0ac .. +0x0f8
    LeafVec  mVec_0fc;                       // +0x0fc
    uint32_t mPad_104[(0x160 - 0x104) / 4];  // +0x104 .. +0x15c
    LeafVec  mVec_160;                       // +0x160
    uint32_t mPad_168[(0x978 - 0x168) / 4];  // +0x168 .. +0x974
    LeafVec  mVec_978;                       // +0x978
    uint32_t mPad_980[(0x1190 - 0x980) / 4]; // +0x980 .. +0x118c
    LeafVec  mVec_1190;                      // +0x1190
    uint32_t mPad_1198[(0x19a8 - 0x1198) / 4];// +0x1198 .. +0x19a4
};
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
struct SlotVec {
    void** mpBegin_00;      // +0x00
    void** mpEnd_04;        // +0x04
};
struct SubObj48 {
    uint mPad_00[0x48 / 4];        // +0x00 .. +0x44
    unsigned long long mBits_48;   // +0x48
};
static uint popcount32(uint v)
{
    v = v - ((v >> 1) & 0x55555555);
    v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
    v = (v + (v >> 4)) & 0x0f0f0f0f;
    return (v * 0x01010101) >> 24;
}
// ---- items of slice s00b047b0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void* FUN_00b047b0(void** param_1, void** param_2, void** param_3, float px, float py, float pz);  // 0x00b047b0 (stays in the slice: not this object's)

// ---- items of slice s00b09570 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00b07140(void *pVec, void *pBegin, void *pEnd);
extern "C" void *FUN_00b091d0(void *pThis);
extern "C" void *FUN_00b06cd0(void *pThis);
extern "C" float FUN_00b00000f();
extern "C" void  FUN_00b06340(void *a, void *b, float x, float y, float z);
extern "C" double RandomDoubleUniform(void);
extern "C" void *SP__App();
extern "C" void *SP__PlanetModel(void *pOut, const float *pIn);
extern "C" void *SP__cPlanetModel__DirectionToSurfacePosition(void *pThis, void *a, void *b);
extern "C" void  SP__cViewer__GetCameraLocationInfo(void *pThis, void *a, void *b, int c, int d);
extern "C" void  eastl__copy_backward(void *pFirst, void *pLast, void *pOut);
extern "C" void operator_delete_array(void *p);
typedef unsigned __int64 u64;
typedef void  (__thiscall *F0v_s00b0_9570)(void *);
typedef void *(__thiscall *F0p_s00b0_9570)(void *);
typedef void  (__thiscall *F1p_s00b0_9570)(void *, void *);
static inline void *VS_s00b0_9570(void *o, int off) { return *(void **)((char *)(*(void **)o) + off); }
static inline void *vc_p_s00b0_9570(void *o, int off) { return ((F0p_s00b0_9570)VS_s00b0_9570(o, off))(o); }
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
struct ScatterE {
    u32     mKey;    // +0x0000
    u32     mPad04;  // +0x0004
    Scatter mBody;   // +0x0008
};
struct TreeData {
    u32   mPad00;     // +0x00  (vtable in the original; never dereferenced here)
    u32   mPad04[3];  // +0x04
    float mPosX;      // +0x10
    float mPosY;      // +0x14
    float mPosZ;      // +0x18
    u32   mPad1c[11]; // +0x1c
    u32   mFruitLo;   // +0x48
    u32   mFruitHi;   // +0x4c
    u32   mSeedX;     // +0x50
    u32   mSeedY;     // +0x54
    u32   mSeedZ;     // +0x58
    u32   mPad5c[4];  // +0x5c
    float mCanopyR;   // +0x6c
    u32   mPad70[3];  // +0x70
    char  mSkip;      // +0x7c
    u32   mScore;     // +0x1c8
    TreeData();                      // ctor
    void  ReadFromIArchive(void *p); // vtable slot 5
};
struct TreeBits {
    u32 mPad00[0x12]; // +0x00
    u32 mMaskLo;      // +0x48
    u32 mMaskHi;      // +0x4c
    u32 mSeedX;       // +0x50
    u32 mSeedY;       // +0x54
    u32 mSeedZ;       // +0x58
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
struct Pairs {
    int *mpBegin; // +0x00
    int *mpEnd;   // +0x04
    int *mpCap;   // +0x08
};
struct Stream {
    void *mpVtbl;          // +0x00
    Stream *GetOuter();    // vtable slot 8  (0x20)
    void   *GetIO();       // vtable slot 6  (0x18)
    void    EndRead();     // vtable slot 7  (0x1c)
    void    ReadTreeRefVector(void *pThis, void *pVec);  // 0x00b0a310
};
extern "C" Mgr  *FUN_00b3d440_s00b0_9570();
extern "C" void  FUN_00b023d0(void *pThis, void *a, u32 b, u32 c);
extern "C" void  FUN_00b060f0(void *pVec, u32 n);
extern "C" void  FUN_00b03680(TreeData *pDst, const TreeData *pSrc);
extern "C" void  FUN_00b07190(void *pVec, u32 where, const TreeData *pSrc);
extern "C" void  FUN_00b97280(void *pDst, u32 n, u32 *pOut);
extern "C" void  FUN_00b98ea0(void *p, u32 n);
extern "C" void  FUN_00b96600(void *pVec, u32 *pWhere);
extern "C" void  FUN_00d01790(void *pThis, u32 n);
extern "C" void  FUN_00b09340(Mgr *pThis, float f, int **ppEnd, u32 a, u32 b);
extern "C" void  SetSeed(u32 seed);
extern "C" u32    RandomUint32Uniform(u32 n);
extern "C" int    ReadInt32_s00b0_9570(void *pIO, u32 *pOut, u32 n, u32 z);
extern "C" int    FUN_00702760(void *pThis, float r, float *pPos, u32 n, void *pList);
extern "C" void *SP__NounManager(u32 h);
extern "C" void  SP__cGameNounManager__RemoveNoun(void *pThis, u32 h);
extern "C" void *SP__cVarListSerializer__ctor(void *pThis, void *a, const char *s, u32 n);
extern "C" char  SP__cVarListSerializer__Serialize(void *pThis, u32 a);
typedef void (__thiscall *FAssign16)(Fv16 *, const Fv16 *);
typedef void (__thiscall *FAssign512)(Fv512 *, const Fv512 *);
static inline void CopyFv16Contents(Fv16 *pDst, const Fv16 *pSrc) {
    ((FAssign16)0x01011cc0)(pDst, pSrc);
}
static inline void CopyFv512Contents(Fv512 *pDst, const Fv512 *pSrc) {
    ((FAssign512)0x00b07050)(pDst, pSrc);
}
extern "C" void *__fastcall FUN_00b03320(Mgr *p, int dummy, u32 a, u32 b, u32 c);
extern "C" u32   __fastcall FUN_00b058f0(Mgr *p, int dummy);
static inline void *FUN_00b03320_tc(Mgr *p, u32 a, u32 b, u32 c) {
    return FUN_00b03320(p, 0, a, b, c);
}
static inline u32 FUN_00b058f0_tc(Mgr *p) { return FUN_00b058f0(p, 0); }
// ---- items of slice s00b09570 end

// ---- items of slice s00b0c190 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cPlanetRecord;
class cPlanetRecordTable;
class cPlanetObjectData;
class cSlotObject;
class cObjectKey;
class cPlanetManager;
class cNoun;
class cNounManager;
class cHierGrid;
class cWorld;
extern cPlanetRecord* LowerBoundRecords(cPlanetRecord* pBegin, cPlanetRecord* pEnd,
                                        const uint* pKey, bool bSorted);
extern void DestroyRecordRange(cPlanetRecord* pBegin, cPlanetRecord* pEnd);
extern void CollapseRecordRange(cPlanetRecord* pBegin, cPlanetRecord* pEnd);
extern void __stdcall SetSelectedKey(const cObjectKey* pKey);                   // 0x00b01db0
extern void ShutdownSelection(cPlanetManager* pOwner);                         // 0x00b09b00
extern void RemoveHandler(int nHandler, uint nKey0, uint nKey1, uint nKey2, uint nKey3);
extern cNounManager* GetNounManager_s00b0_c190();                                         // 0x00b3d300
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
class cNounManager
{
 public:
    void RemoveNoun(cNoun* pNoun);   // 0x00b225d0
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
void* SP_StarManager_00b3d2a0();                                    // 0x00b3d2a0
struct VecSlot_00ac9200 { void Insert(void* v); };                        // 0x00ac9200 ecx=slot
struct VecBase_00acb810 { void GrowInsert(void* pos, void* v); };         // 0x00acb810 ecx=vector base
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
void* FUN_00b8de30(void* p);                                        // 0x00b8de30
void  FUN_00a16a90(void* p);                                        // 0x00a16a90
struct PlanetMap_00c729b0 { void find_00c729b0(void* out, void* key); };  // 0x00c729b0 (ecx=this)
void  FUN_00705250(void* dst, void* end, void* src);                // 0x00705250
void  FUN_00c723d0_local(void* self);                               // 0x00c723d0
void  FUN_00c8b2e0_00(void);                                        // 0x00c8b2e0
void* FUN_00d01260(void* a, void* b, void* c, int d);               // 0x00d01260
void  FUN_004b5440(void* p);                                        // 0x004b5440
struct PlanetCls_s00c7_2c60 {
    void AddDebugInfo_00c72c60(void* str);
    void AddDebugInfo_00c72ce0(void* str);
    bool FUN_00c72d70(int key);  // 0x00c72d70 (PlanetCls::FUN_00c72d70)
    void FUN_00c72dd0(int v);  // 0x00c72dd0 (PlanetCls::FUN_00c72dd0)
    void FUN_00c72e10(char* pd);  // 0x00c72e10 (PlanetCls::FUN_00c72e10)
    bool FUN_00c73250();  // 0x00c73250 (PlanetCls::FUN_00c73250)
    void FUN_00c73270(int* key);  // 0x00c73270 (PlanetCls::FUN_00c73270)
    void FUN_00c732c0(int* key);  // 0x00c732c0 (PlanetCls::FUN_00c732c0)
    void FUN_00c73310();  // 0x00c73310 (PlanetCls::FUN_00c73310)
    void FUN_00c73330();  // 0x00c73330 (PlanetCls::FUN_00c73330)
    int FUN_00c73350(int* key);  // 0x00c73350 (PlanetCls::FUN_00c73350)
    void FUN_00c733b0();  // 0x00c733b0 (PlanetCls::FUN_00c733b0)
    void** FUN_00c73520(void** out);  // 0x00c73520 (PlanetCls::FUN_00c73520)
    int* FUN_00c735e0(int* key);  // 0x00c735e0 (PlanetCls::FUN_00c735e0)
    void FUN_00c73680();  // 0x00c73680 (PlanetCls::FUN_00c73680)
    void FUN_00c73b60();  // 0x00c73b60 (PlanetCls::FUN_00c73b60)
};
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
    void FUN_00c72d00(void* r, void* k);   // 0x00c72d00 thiscall
    void FUN_00c73680();
    void FUN_00c73b60();
};
// ---- items of slice s00c72c60 end

// ---- items of slice s00c73cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* NounManager();                                                       // 0x00b3d300
void* eastl_lower_bound(void* b, void* e, void* k, unsigned char c);       // 0x00ba2e50
void* FUN_00ac0d80(void* b, void* e, void* k);                             // 0x00ac0d80
void* FUN_00ba57f0(void* key, int n);                                      // 0x00ba57f0
void* FUN_00ba5650(void* key, int n);                                      // 0x00ba5650
void* FUN_00ba5a60(void* x, int n);                                        // 0x00ba5a60
void* __stdcall FUN_00b3d4f0(void* x);                                     // 0x00b3d4f0
void  NotifyScannedCreatureSpecies(void* key, int flag);                   // 0x01058460
struct VecEraser { void eraseElem(void* p); };                            // 0x00eeee40
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

    void* FUN_00c73cb0(void* key);                 // +0x20 entry of a scanned map 0x00c73cb0
    void* FUN_00c73cd0(void* key);                 // +0x68 entry of a scanned map 0x00c73cd0
    void  FUN_00c73cf0(int flag);                 // scan the two key vectors into maps[0] 0x00c73cf0
    char  SetSpeciesAsScanned(void* key);  // 0x00c73ea0 (PlanetCls::SetSpeciesAsScanned)
    char  IsSpeciesScanned(void* key);  // 0x00c73f10 (PlanetCls::IsSpeciesScanned)
    void  FUN_00c73f80(void* key);
    void  FUN_00c73ff0();  // 0x00c73ff0 (PlanetCls::FUN_00c73ff0)
    char  FUN_00c741a0(void* key);
    void  FUN_00c74210(void* key);  // 0x00c74210 (PlanetCls::FUN_00c74210)
    void  FUN_00c74280();  // 0x00c74280 (PlanetCls::FUN_00c74280)
    char  FUN_00c74400(void* key);
    void  FUN_00c74470(void* key);  // 0x00c74470 (PlanetCls::FUN_00c74470)
    char  FUN_00c744e0(unsigned* key);  // 0x00c744e0 (PlanetCls::FUN_00c744e0)
    char FUN_00c74550(unsigned* key);
    void  FUN_00c745d0(char flag, void* key);
    void  FUN_00c74650();  // 0x00c74650 (PlanetCls::FUN_00c74650)
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

// ---- items of slice s00b03820 begin (TODO(rewrite): local stubs, replace by canonical classes)

struct TinyCopyT { void Copy(const void* src); };                  // 0x00b01cb0 (thiscall, 1 arg)
struct BigElem   { void Ctor(void* src); };                        // 0x00b03680 (thiscall, 1 arg)
struct BigElemD  { void Dtor(); void Dtor2(void* src); };          // 0x00b03740 (thiscall)
// The 0x80-byte element the range helpers at 0x00b03ca0 / 0x00b03f10 copy (same shape as
// SPCity's CElement helpers 0x00bdd5c0 / 0x00bdd600).
struct BigElem80 {
    char pad00[0x80];
    void CopyConstructFrom(const BigElem80& src);  // 0x00b03680
    void CopyAssignFrom(const BigElem80& src);     // 0x00b03740
};
void* __cdecl FUN_00f473a0(uint32 size, const char* name, int, int, const char* file, int line);
void  __cdecl FUN_00b02930(void*, int, int, int, void*, float, float, float);
void  __cdecl FUN_00b02930(void*, int, int, int, void*, HeapPos);
void  __cdecl FUN_00b02a40(void*, int, int, int, void*, float, float, float);
void  __cdecl FUN_00b02a40(void*, int, int, int, void*, HeapPos);
void  __cdecl FUN_00ac8050_ish(void* a, const char* b, int c);      // per-node visitor
void  __cdecl FUN_00921880(void* node, void* head);                 // eastl::RBTreeErase
void  __cdecl FUN_00ac20d0(int n, void* src);                       // vector range assign
void  __cdecl FUN_0076ffd0(void* a, void* b, void* c, void* d);     // eastl::copy
typedef void (__thiscall* RefVtSlot0)(void*);
inline void RefObjCall0(void* obj)
{
    RefVtSlot0* vt = *(RefVtSlot0**)obj;
    vt[0](obj);
}
inline void RefObjCall1(void* obj)
{
    RefVtSlot0* vt = *(RefVtSlot0**)obj;
    vt[1](obj);
}
struct PoolNode {                       // carved in 0x20-byte units
    PoolNode* next;                     // +0x00
    uint32    pad04[3];                 // +0x04
    float     f10;                      // +0x10
    float     f14;                      // +0x14
    float     f18;                      // +0x18
    uint32    pad1c;                    // +0x1c
};
struct PoolOwner {
    uint32    pad00[6];
    PoolNode* freeList;                 // +0x18
    uint32    pad1c[3];
    uint32    chunkSize;                // +0x28

    PoolNode* AllocNode(const uint32* src);     // 0x00b03820
    PoolNode* AllocNodeTiny(const uint32* src); // 0x00b03880

    void release_node_chain(void* node);        // 0x00b04350
    void erase_tree_node(void** out, void* node);// 0x00b043b0
    void* rbcontainer_copy(void* src);          // 0x00b04520
};
struct RedBlackTree {
    void* begin;                        // +0x00
    void* end;                          // +0x04
    uint8 flags[0x19a810];              // +0x08..
    uint8 flag19a818;                   // +0x19a818

    void* Find(uint32* key);            // 0x00b03f90
};
void* __cdecl FUN_00b02750(void* begin, void* last, uint32* key, uint8 f);
void __cdecl make_heap_range(void* first, void* last, HeapPos pos);
void __cdecl FUN_00b03d20(void** first, void** last, const float* pos);
void __cdecl FUN_00b03ce0(void** first, void** last, const float* pos);
void __cdecl FUN_00b02830(void** first, int, int, int, void* v, const float* pos);
// ---- items of slice s00b03820 end

// ---- items of slice s00b05980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*  FUN_00b3d300(void* obj);                               // SP::NounManager(obj)
extern "C" void   FUN_0093a780(void* dst, void* count, int n, int c);    // ReadInt32
extern "C" void   FUN_0093a800(void* dst, void* val, int n, int c);      // ReadXXX
extern "C" void   FUN_00537dc0(void* self, void* other);                 // cSPTransform::operator=
extern "C" void*  FUN_00b027f0(void* first, void* last, void* dst);      // move-back 0x20 elems
extern "C" void*  FUN_00b027b0(void* first, void* last, void* dst);      // construct-copy range
extern "C" void   FUN_00b01470(void* first, void* last, void* dst);      // destroy range
extern "C" void   FUN_00b02b50(void* a, void* b, void* c);               // move one 0x20 elem
extern "C" void   FUN_00b02710(void* a, void* b, void* c, void* d, void* e);  // tail copy w/ allocator
extern "C" void   FUN_005f4e10(void* first, void* last, void* dst);      // 4-byte copy-back
extern "C" void   FUN_006782c0(void* first, void* last, void* dst);      // 4-byte copy-back
extern "C" void   FUN_011e0744(void* self, void* value, int n);          // vector<bool>::DoInsertValue
extern float g_167af5c, g_167af60, g_167af64;   // default placement (Vec3)
extern float g_156741c;                          // default orientation
extern uint32_t g_15673b8;                       // list capacity limit
template<class T> static inline T& At(void* p, unsigned o) { return *(T*)((char*)p + o); }
struct Vec3_s00b0_5980 { float x, y, z; };
typedef void  (__thiscall *F0v)(void*);
typedef int   (__thiscall *F0i)(void*);
typedef void* (__thiscall *F0p)(void*);
typedef void  (__thiscall *F1i)(void*, int);
typedef void  (__thiscall *F1p)(void*, void*);
typedef void  (__thiscall *F2)(void*, void*, int);
static inline void* VS(void* o, int off) { return *(void**)((char*)(*(void**)o) + off); }
static inline int   vc_i(void* o, int off)          { return ((F0i)VS(o, off))(o); }
static inline void* vc_p(void* o, int off)          { return ((F0p)VS(o, off))(o); }
static inline void  vc_v(void* o, int off)          { ((F0v)VS(o, off))(o); }
static inline void  vc_vi(void* o, int off, int a)  { ((F1i)VS(o, off))(o, a); }
static inline void  vc_vp(void* o, int off, void* a){ ((F1p)VS(o, off))(o, a); }
struct Bucket { void** begin; void** end; };
struct Mgr_s00b0_5980 {
    Bucket* GetBucket(uint32_t key, uint32_t kind);   // 0xb04ba0
};
struct EffectRec {
    uint32_t f00;   // +0x00
    uint32_t f04;   // +0x04
    uint32_t f08;   // +0x08
    uint32_t f0c;   // +0x0c
    void*    f10;   // +0x10  (Release at vtable+4)
    void*    f14;   // +0x14  (Release at vtable+0x38)
    uint32_t f18;   // +0x18
    uint32_t f1c;   // +0x1c
    void Reset();                          // 0xb00150
    void copyFrom(const EffectRec&);       // 0xb01cb0
    void construct(const EffectRec&);      // 0xb01d30
};
struct RefVec {
    void* begin;   // +0
    void* end;     // +4
    void* cap;     // +8
    void* erase(void* first, void* last);                  // 0xe25bd0
    void  insertSlow(void* pos, void* value);              // 0xaea5d0
    void  growAt(void* where, unsigned n, void* value);    // 0xbabb70
    void** F05b40(void** pos, void** value);               // 0x00b05b40
    void*  F05d80(void* pos);                              // 0x00b05d80
    void   F06d90(uint32_t n);                             // 0x00b06d90
};
struct EffectVec {
    EffectRec* begin;   // +0
    EffectRec* end;     // +4
    EffectRec* cap;     // +8
    EffectRec* allocateCopy(unsigned n, EffectRec* first, EffectRec* last);  // 0xb044c0
    void       destroyRange(EffectRec* first, EffectRec* last);              // 0xb006f0
    EffectVec* F05c60(EffectVec* other);                                     // 0x00b05c60
    EffectRec* F05d50(EffectRec* pos);                                       // 0x00b05d50
    void       F06190(EffectRec* pos, EffectRec* value);                     // 0x00b06190
};
struct XformObj {
    Vec3_s00b0_5980*    F05a00(Vec3_s00b0_5980* out, uint32_t index);   // 0x00b05a00
    uint32_t Count();                             // 0xb058f0
};
struct Tree {
    void  reset(void* a);                  // 0xb04350
    void  add(void* a, void* b, uint32_t c);   // 0xb04f70
    void  addRange(void* a, void* b, void* c); // 0xb04ed0
    int*  lowerBound(void* out, const void* key);    // 0xb02430
};
struct Interactable {
    bool InitFromDefinition(void* a, void* b, void* c);   // 0xc3fc80
    bool F06740(void* a, void* b, void* c);                // 0x00b06740
};
struct NounMgr_s00b0_5980 {
    void RemoveNoun(void* obj);   // 0xb225d0
};
struct CTreeData {
    void* ctor();   // 0xb01770
};
struct Pair { void* a; void* b; };
struct Rec3 { void* a; void* b; void* c; };
struct EffectOwner {
    bool F06810(uint32_t key);
};
struct RangeScan {
    void F068c0(void* range, uint32_t a, uint32_t b);
};
struct TearDown {
    void** F06a40(void** slot, int flag);
};
struct Proximity {
    void F06bd0(Vec3_s00b0_5980* point, float radius, RefVec* out);
};
struct ModelList {
    void F06cd0();
};
// ---- items of slice s00b05980 end

// ---- items of slice s00b06e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cGlyphVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
    void operator=(const cGlyphVector& other);               // 0x00ac44a0
};
struct cGlyphRun {
    uint32_t     mKey;                                       // +0x00
    uint8_t      mFlag;                                      // +0x04
    uint8_t      mPad05[3];                                  // +0x05 .. +0x07
    cGlyphVector mGlyphs;                                    // +0x08
    uint32_t     mPad14[2];                                  // +0x14 .. +0x1b
    uint32_t     mValue1c;                                   // +0x1c
    uint32_t     mValue20;                                   // +0x20
};
struct cBigElement {
    void*    mpVtable;                                       // +0x00
    uint8_t  mPad04[0x7c];                                   // +0x04 .. +0x7f
};
struct cBigVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void Erase(void* first, void* last);
};
// ---- items of slice s00b06e10 end

// ---- items of slice s00b07980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_15673a8;     // 0x015673a8
extern uint32_t g_15673ac;     // 0x015673ac
struct Vector3_s00b0_7980 { float x, y, z; };
template<class T> inline T& At_s00b0_7980(void* p, int off) { return *(T*)((char*)p + off); }
struct Req            // param_2 (spawn request)
{
    uint32_t count;       // +0x00
    uint32_t pad4;
    uint8_t* elems;       // +0x08  array of count 0x4c-byte transforms
    uint32_t pad0c;       // +0x0c
    void*    target10;    // +0x10  object that receives the range key at +0xd4
    uint32_t pad14[3];    // +0x14
    void*    key;         // +0x20
    uint32_t pad24[3];    // +0x24
    uint32_t field30;     // +0x30
};
struct Xform
{
    uint16_t flags;
    uint16_t counter;
    Vector3_s00b0_7980  pos;
    uint32_t pad[0x4c / 4 - 5];
    Xform& operator=(const Xform&);                  // 0x537dc0 (thiscall, ret 4)
};
struct XformMsg                                      // ctor 0x434040
{
    uint16_t flags;
    uint16_t counter;
    Vector3_s00b0_7980  pos;
    uint32_t pad[10];
    XformMsg();
};
struct IVisualEffect
{
    virtual int AddRef();
    virtual int Release();
    virtual void Slot2(int);                         // +0x08
};
struct VfxRef                                        // EA::AutoRefCount<cIVisualEffect>
{
    IVisualEffect* p;
    IVisualEffect** AsPPTypeParam();                 // 0xa16f40
    VfxRef& assign(VfxRef*);                         // 0xac9480 (this = dst, arg = &src, ret 4)
};
struct EffectsManager
{
virtual void pv0();
virtual void pv1();
virtual void pv2();
virtual void pv3();
virtual void pv4();
virtual void pv5();
virtual void pv6();
virtual void pv7();
virtual void pv8();
virtual void pv9();
virtual void pv10();
    virtual bool CreateEffect(uint32_t a, uint32_t b, IVisualEffect** out);   // +0x2c
};
struct Model                                         // species->+0xa0
{
    uint32_t GetCount();                             // 0x4d9070 (end-begin of the vector at +0x810)
};
struct Species
{
virtual void pv0();
virtual void pv1();
virtual void pv2();
virtual void pv3();
virtual void pv4();
virtual void pv5();
    virtual const Vector3_s00b0_7980* GetPosition();            // +0x18
    uint32_t GetKind();                              // 0xb8f860
    Model* GetModelWorld();                          // 0xad2830 (returns [this+0xa0])
};
struct SpeciesMgr { Species* GetSpeciesFromID(uint32_t id); };   // 0xb90410 (ret 4)
struct IdLookup   { uint32_t Lookup(Req* req); };                // 0xb2b1e0 (ret 4)
struct XformListener
{
virtual void pv0();
virtual void pv1();
virtual void pv2();
virtual void pv3();
virtual void pv4();
virtual void pv5();
    virtual void Slot6(XformMsg*);                   // +0x18
    virtual void pv7();
    virtual void Slot8(XformMsg*);                   // +0x20
};
struct Plant                                         // object created by Mgr::NewPlant (0xb02060)
{
    virtual int AddRef();
    virtual int Release();
};
struct Item                                          // result of FUN_00afff30
{
    // +0x0c Xform, +0x10 Vector3, +0x48/+0x4c ints, +0x6c float, +0x78 int
    uint32_t pad[0xc / 4];
};
struct PlanetModel
{
    Vector3_s00b0_7980* DirectionToSurfacePosition(Vector3_s00b0_7980* out, const Vector3_s00b0_7980* in);   // 0xb815a0 (ret 8)
    void     FUN_00b88420();                                                 // 0xb88420
    uint32_t GetAverageRadius(const Vector3_s00b0_7980* v);                             // 0xb7e840 (ret 4)
};
struct NounManager_s00b0_7980 { void RemoveNoun(Plant* p); };   // 0xb225d0 (ret 4)
struct RBNode { uint32_t pad[6]; Plant* value; };    // value at +0x18
struct Range  { RBNode* begin; RBNode* end; };
struct Triple { void* key; uint32_t kind; Plant* plant; };
struct Group
{
    void Add(uint32_t* out, Triple* t, bool b);                // 0xb04f70 (ret 0xc)
    void AddRange(uint32_t* out, RBNode* first, RBNode* last); // 0xb04ed0 (ret 0xc)
};
struct EffectRec_s00b0_7980                                     // 0x20-byte record queued at manager +0x160e8
{
    uint32_t total;
    uint32_t pad04;
    void*    key;
    uint32_t kind;
    VfxRef   vfx;
    uint32_t z14, z18, pad1c;
    void Reset();                                    // 0xb00150
};
struct EffectVec_s00b0_7980
{
    void push_back(EffectRec_s00b0_7980* r);                    // 0xb06de0 (ret 4)
};
struct EffectBook                                    // *(mgr+0x16500)
{
    uint32_t pad[0x24 / 4];
    uint32_t f24, f28;
    uint32_t FUN_00703d50(float f, void* a, void* b);   // 0x703d50 (ret 0xc)
    void     Remove(uint32_t id);                       // 0x702da0 (ret 4)
};
struct Bucket_s00b0_7980 { uint32_t first, second; };
struct SlotBits {                                    // per-slot mask of a placed object (0xb04c20 result)
    char     pad00[0x48];
    uint32_t mMaskLo;                                // +0x48
    uint32_t mMaskHi;                                // +0x4c
};
struct FeatureLookup {                               // one 0x5c-byte feature entry of an effect
    uint32_t mSlotId38;                              // +0x38
    char     pad3c[0x5c - 0x3c];
};
struct FeatureVec {                                  // the feature vector at effect+0x144
    FeatureLookup* mBegin;                           // +0x00
    uint32_t Size();                                 // 0x00a70310
};
struct VfxOwner {                                    // the visual effect behind EffectRec::vfx.p
    virtual int  AddRef();                           // +0x00
    virtual int  Release();                          // +0x04
    virtual void Slot2(int);                         // +0x08
    virtual void Slot3(int);                         // +0x0c
};
struct PlantObject {                                 // a placed plant (RBNode::value)
    virtual int  AddRef();                           // +0x00
    virtual int  Release();                          // +0x04
    char     pad04[0x4c - 4];
    void*    mpKey;                                  // +0x4c
    uint32_t mField50;                               // +0x50
    uint32_t mIndex54;                               // +0x54
    Xform    mXform58;                               // +0x58
    char     padA0[0xa4 - 0x58 - sizeof(Xform)];
    void*    mpMatrixA4;                             // +0xa4  array of 0x38-byte world matrices
    char     padA8[0x19c - 0xa8];
    uint32_t* mpSlotIds;                             // +0x19c
    uint32_t* mpSlotIdsEnd;                          // +0x1a0
    char     pad1a4[0x1c4 - 0x1a4];
    VfxOwner* mpVfx;                                 // +0x1c4
    uint32_t mField1c8;                              // +0x1c8
    uint32_t CurEntryBits();                         // 0x00b058f0
};
struct PlantRange {                                  // the container at Mgr+0x34 (count at +0x14)
    char     pad00[0x14];
    uint32_t mCount;                                 // +0x14
    void     FindRange(Range* out, void** key);      // 0x00b02430 (ret 8)
    void     AddRange(uint32_t* out, RBNode* first, RBNode* last);   // 0x00b04ed0 (ret 0xc)
};
struct MapNode {                                     // a node of the map at Mgr+0x8080
    char     pad00[0x18];
    void*    mpKey;                                  // +0x18
    char     pad1c[0xc];
    VfxOwner* mpValue;                               // +0x28
    char     pad2c[4];
    void*    mpField30;                              // +0x30
};
struct KeyMap {                                      // eastl::rbtree<key, AutoRefCount<...>>
    uint32_t pad00;                                  // +0x00
    void     find(MapNode** out, void** key);        // 0x00e5c780 (ret 8)
    void     F05c30(void* out, void* value);         // 0x00b05c30 (ret 8)
    MapNode* end() { return (MapNode*)((char*)this + 4); }
};
struct HolderObject {                                // a sim object holding the slot shadow at +0x64
    virtual int  AddRef();                           // +0x00
    virtual int  Release();                          // +0x04
    char     pad04[0x64 - 4];
    VfxOwner* mpField64;                             // +0x64
};
struct PtrVec { void** mBegin; void** mEnd; };       // the pointer vector at Mgr+0x16504
struct BucketObject {                                // an entry scanned in GetBucket's bucket
    char pad00[0x78];
    int  mSlot78;                                    // +0x78
};
void __cdecl FUN_00b057b0(Bucket_s00b0_7980* b);                // 0xb057b0
struct PlantEffectVec {                              // the effect-record vector at Mgr+0x160e8
    EffectRec_s00b0_7980* mBegin;                               // +0x00
    EffectRec_s00b0_7980* mEnd;                                 // +0x04
    void F05d50(EffectRec_s00b0_7980* rec);                     // 0x00b05d50 (ret 4)
};
struct SimEvent {                                    // the record handed to the handlers
    uint32_t mKey;                                   // +0x00  key / slot limit
    uint32_t mField04;                               // +0x04
    void*    mpTransforms;                           // +0x08  array of 0x4c-byte cSPTransform records
    uint32_t mField0c;                               // +0x0c
    void*    mpTarget;                               // +0x10  object receiving the range key
};
struct SimTarget {                                   // *SimEvent::mpTarget
    char     pad00[0xd4];
    uint32_t mRangeKey;                              // +0xd4
};
struct RecordBuilder {                               // the 0x20-byte temporary map record
    uint32_t mField00;                               // +0x00  key
    char     pad04[0x1c];
    void*    Build(void* key, void* arg);            // 0x00b02480 (ret 8)
    void     Reset();                                // 0x00b00150
};
struct RefCollector {                                // the 0x18-byte temporary that keeps references
    void* mpData[6];
    void Add(void* p);                               // 0x00b01d30 (ret 4)
};
struct SlotOwner {                                   // the object behind the slot shadow
    void SetShadow(uint32_t id, float z);            // 0x00a887b0 (ret 8)
};
struct RecordTail {                                  // EffectRec+0x14
    void  F07d4590(void* key);                       // 0x007d4590 (ret 4)
};
struct XformOps { Xform* Assign(const void* src); };  // 0x537dc0
void* __cdecl translateTransform(void* out, void* src, void* xform);   // 0x6271a0
void  __cdecl FUN_00b043b0(void* out, MapNode* node);                  // 0x00b043b0
uint64_t __cdecl __allshl(uint64_t value, uint32_t count);             // 0x11e06e0
struct Mgr_s00b0_7980
{
    bool     FindExisting(Range* out, void* key, uint32_t kind, uint32_t count, Group* g);          // 0xb034f0 (ret 0x14)
    Bucket_s00b0_7980*  GetBucket(void* key, uint32_t kind);                                                    // 0xb04ba0 (ret 8)
    Plant*   NewPlant();                                                                             // 0xb02060
    void     InitBook();                                                                             // 0xb02120
    bool     SetupPlant(Plant* p, Species* s, Xform* elem, int isEmpty, int notFlag, int* idx, VfxRef* vfx); // 0xb07560 (ret 0x1c)
    bool     FUN_00b07980(Req* req, bool flag, Group* g4, Group* p5, Group* p6);
    bool     FUN_00b07fa0(SimEvent* ev, bool flag, PlantRange* range, Group* group);
    bool     FUN_00b08260(uint32_t eventId, SimEvent* ev);
    void     F06810(void* vfx);                                                      // 0x00b06810 (ret 4)
    void     F068c0(Group* group, void* key, uint32_t kind);                         // 0x00b068c0 (ret 0xc)
    void     fillSlot(SimEvent* ev);                                                 // 0x00b04aa0 (ret 4)
    SlotBits* slotAt(void* key, uint32_t a, uint32_t b);                             // 0x00b04c20 (ret 0xc)

    char           pad00[0x34];
    PlantRange     mRange34;                                                         // +0x34
    char           pad4c[0x8080 - 0x4c];
    KeyMap         mMap8080;                                                         // +0x8080
    char           pad8088[0x160e8 - 0x8084];
    PlantEffectVec mEffects;                                                         // +0x160e8
    char           pad160f0[0x16500 - 0x160f0];
    EffectBook*    mpBook;                                                           // +0x16500
    PtrVec         mVec16504;                                                        // +0x16504
    char           pad1650c[0x165a0 - 0x1650c];
    Group          mGroup165a0;                                                      // +0x165a0
    char           pad165a4[0x1ba18c - 0x165a4];
    uint32_t       mMode;                                                            // +0x1ba18c
    int            mField1ba190;                                                     // +0x1ba190
};
extern "C" IdLookup*       GetIdLookup(void);        // 0xb3d3b0
extern "C" SpeciesMgr*     GetSpeciesMgr(void);      // 0xb3d420
extern "C" EffectsManager* GetEffectsManager(void);  // 0x67ddd0
extern "C" PlanetModel*    GetPlanetModel(void);     // 0xb3d350
extern "C" NounManager_s00b0_7980*    GetNounManager(void);     // 0xb3d300
Item* __cdecl FUN_00afff30(Bucket_s00b0_7980* b, uint32_t i);      // 0xafff30
RBNode* __cdecl RBTreeIncrement(RBNode* n);             // 0x921580
// ---- items of slice s00b07980 end

// ---- items of slice s00b08670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_15673a4;                 // 0x015673a4 (state-2 timeout)
extern uint32_t g_167b550;                 // 0x0167b550 (state-4 timeout)
extern uint32_t g_167afa8;                 // 0x0167afa8
extern const float g_1485720;              // 0x01485720 (_HK_REAL_ONE)
struct Vector3_s00b0_8670
{
    float x, y, z;
    Vector3_s00b0_8670() {}
    Vector3_s00b0_8670(const Vector3_s00b0_8670& o) : x(o.x), y(o.y), z(o.z) {}
};
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
extern const Vector3_s00b0_8670 g_167af5c_s00b0_8670;            // 0x0167af5c
extern const ResourceKey g_1567410;        // 0x01567410
struct cSpatialObject
{
    PV8 PV2 PV                                         // slots 0..10
    virtual const Vector3_s00b0_8670* GetPosition();              // +0x2c
    PV2
    virtual void SetPosition(const Vector3_s00b0_8670* v);        // +0x38
    PV                                                 // slot 15 (+0x3c)
    virtual void SetF40(float v);                      // +0x40
    PV8 PV2                                            // slots 17..26
    virtual const float* GetExtents(void* tmp);        // +0x6c (min xyz, max xyz)
    virtual float GetBoundingRadius();                 // +0x70
    PV8                                                // slots 29..36
    virtual void SetModelKey(const ResourceKey* key);  // +0x94
};
struct IRefCounted { virtual int AddRef(); virtual int Release(); };
struct Target                                          // the item returned by Item::FUN_00b058a0
{
    char pad000[0x10];
    Vector3_s00b0_8670 mPos;                                      // +0x10
    char pad01c[0x6c - 0x1c];
    float mRadius;                                     // +0x6c
};
struct Item_s00b0_8670 : public IRefCounted
{
    char pad004[0x34 - 4];
    cSpatialObject mSpatial;                           // +0x34 (own vtable)
    char pad038[0x84 - 0x38];
    uint8_t mFlags84;                                  // +0x84 (0x10 = dead)
    char pad085[0xa3 - 0x85];
    bool mFlagA3;                                      // +0xa3
    bool mFlagA4;                                      // +0xa4
    bool mFlagA5;                                      // +0xa5
    char pad0a6[0x108 - 0xa6];
    IRefCounted* mpEffect;                             // +0x108
    char pad10c[0x148 - 0x10c];
    uint32_t mFlags148;                                // +0x148
    char pad14c[0x168 - 0x14c];
    uint32_t mTimer;                                   // +0x168
    int mState;                                        // +0x16c
    Target* FUN_00b058a0();                            // 0x00b058a0
};
struct AutoRef
{
    Item_s00b0_8670* mp;
    AutoRef(Item_s00b0_8670* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRef() { if (mp) mp->Release(); }
};
struct ItemVector
{
    Item_s00b0_8670** mpBegin;
    Item_s00b0_8670** mpEnd;
    Item_s00b0_8670** mpCapacity;
    uint32_t mAlloc[2];
    int mHeader;
    Item_s00b0_8670* mBuf[64];
    ItemVector() { mHeader = 0; mpBegin = mBuf; mpEnd = mBuf; mpCapacity = mBuf + 64; }
    ~ItemVector();                                     // 0x00ae6970
    Item_s00b0_8670** insert(Item_s00b0_8670** pos, const AutoRef& v);       // 0x00b05b40 (ret 8)
};
struct Model_s00b0_8670 {  // 0x00b452f0 (ret 0xc), 0x00b453a0 (ret 4)
    char pad[0x20];
    int mMode;
    void FUN_00b452f0(cSpatialObject* s, const Vector3_s00b0_8670* v, int flag);
    void FUN_00b453a0(cSpatialObject* s);
};
Model_s00b0_8670* __cdecl FUN_00b3d310();                         // 0x00b3d310 (mode at +0x20)
struct IReferencePoint
{
    PV8 PV4 PV2
    virtual void GetPos(Vector3_s00b0_8670* out, int flag, Vector3_s00b0_8670 v);   // +0x38
};
IReferencePoint* __cdecl FUN_00b3d240();               // 0x00b3d240
struct PlanetModelT
{
    void FUN_00b81630(Vector3_s00b0_8670* out, const Vector3_s00b0_8670* in);                        // 0x00b81630 (ret 8)
    Vector3_s00b0_8670* FUN_00b82b40(Vector3_s00b0_8670* out, const Vector3_s00b0_8670* in, bool flag);         // 0x00b82b40 (ret 0xc)
};
PlanetModelT* __cdecl PlanetModel();                   // 0x00b3d350
struct VelHolder { char pad[0xd0]; float vx, vy, vz; };   // +0xd0
struct VelOwner { char pad[0x58]; VelHolder* mp58; };      // +0x58
VelOwner* __cdecl FUN_00b53940(cSpatialObject* s);     // 0x00b53940
bool __cdecl FUN_00b54200(cSpatialObject* s);          // 0x00b54200
Vector3_s00b0_8670 __cdecl normalized_safe(const Vector3_s00b0_8670& v);     // 0x00449c20
Vector3_s00b0_8670 __cdecl Normalize(const Vector3_s00b0_8670& v);           // 0x00436ce0
struct ItemManager
{
    char pad000[0x1b8f44];
    Item_s00b0_8670** mpPendingBegin;                             // +0x1b8f44
    Item_s00b0_8670** mpPendingEnd;                               // +0x1b8f48
    char pad18f4c[0x1b905c - 0x1b8f4c];
    Item_s00b0_8670** mpBegin;                                    // +0x1b905c
    Item_s00b0_8670** mpEnd;                                      // +0x1b9060
    Item_s00b0_8670** FUN_00b06a40(Item_s00b0_8670** it, bool erase);        // 0x00b06a40 (ret 8)
    Item_s00b0_8670*  FUN_00b08e90();                             // 0x00b08e90
    void Update(uint32_t dt);
};
void ItemManager::Update(uint32_t dt)   // @ 0x00B08670
{
    ItemVector sorted;
    Vector3_s00b0_8670 refPos;
    FUN_00b3d240()->GetPos(&refPos, 1, g_167af5c_s00b0_8670);

    Item_s00b0_8670** it = mpBegin;
    if (it != mpEnd)
    {
        do
        {
            Item_s00b0_8670* item = *it;
            if (item == 0 || (item->mFlags84 & 0x10))
            {
                ++it;
                continue;
            }
            const int state = item->mState;
            switch (state)
            {
            case 1:
            {
                if (FUN_00b3d310()->mMode == 0)
                {
                    VelOwner* owner = FUN_00b53940(&item->mSpatial);
                    if (item->mFlagA5 ||
                        (owner && (owner->mp58->vx * owner->mp58->vx + owner->mp58->vy * owner->mp58->vy +
                                   owner->mp58->vz * owner->mp58->vz) < 1.1f))
                    {
                        item->mFlagA5 = false;
                        FUN_00b54200(&item->mSpatial);
                        Vector3_s00b0_8670 dir = *item->mSpatial.GetPosition();
                        dir = normalized_safe(dir);
                        const float f = (float)dt * -0.0098f;
                        dir.x = dir.x * f;
                        dir.y = dir.y * f;
                        dir.z = dir.z * f;
                        FUN_00b3d310()->FUN_00b452f0(&item->mSpatial, &dir, 1);
                    }
                }
                else if (item->mFlagA5)
                {
                    item->mFlagA5 = false;
                }

                char extentsTmp[24];
                const float* b = item->mSpatial.GetExtents(extentsTmp);
                Vector3_s00b0_8670 center;
                center.x = (b[3] + b[0]) * 0.5f;
                center.y = (b[4] + b[1]) * 0.5f;
                center.z = (b[5] + b[2]) * 0.5f;
                Vector3_s00b0_8670 ground;
                PlanetModel()->FUN_00b81630(&ground, &center);
                Vector3_s00b0_8670 d;
                d.x = center.x - ground.x;
                d.y = center.y - ground.y;
                d.z = center.z - ground.z;
                const float dist2 = d.z * d.z + d.y * d.y + d.x * d.x;
                if (!((item->mSpatial.GetBoundingRadius() + 0.03f) < dist2))
                {
                    if (item->mState != 2)
                    {
                        item->mTimer = 0;
                        item->mState = 2;
                    }
                    Target* t = item->FUN_00b058a0();
                    if (t)
                    {
                        const float tradius = t->mRadius;
                        const float r = item->mSpatial.GetBoundingRadius() + 0.05f;
                        Vector3_s00b0_8670 v;
                        v.x = center.x - t->mPos.x;
                        v.z = center.z - t->mPos.z;
                        v.y = center.y - t->mPos.y;
                        const float len = sqrtf(v.x * v.x + v.z * v.z + v.y * v.y);
                        const float sum = r + tradius;
                        if (sum > len && len > 1.52587890625e-05f)
                        {
                            const float inv = 1.0f / len;
                            Vector3_s00b0_8670 p;
                            p.x = inv * v.x * sum + t->mPos.x;
                            p.y = v.y * inv * sum + t->mPos.y;
                            p.z = v.z * inv * sum + t->mPos.z;
                            Vector3_s00b0_8670 out;
                            const Vector3_s00b0_8670* snapped = PlanetModel()->FUN_00b82b40(&out, &p, false);
                            p = *snapped;
                            item->mSpatial.SetPosition(&p);
                        }
                    }
                }
                if (FUN_00b3d310()->mMode == 2)
                {
                    const Vector3_s00b0_8670* pos = item->mSpatial.GetPosition();
                    Vector3_s00b0_8670 surf;
                    PlanetModel()->FUN_00b81630(&surf, pos);
                    Vector3_s00b0_8670 w;
                    w.x = surf.x - pos->x;
                    w.y = surf.y - pos->y;
                    w.z = surf.z - pos->z;
                    const float wlen2 = w.x * w.x + w.z * w.z + w.y * w.y;
                    if (wlen2 > 0.1f)
                    {
                        Vector3_s00b0_8670 target = surf;
                        const float step = (float)dt * 0.0098f;
                        if (step * step < wlen2)
                        {
                            Vector3_s00b0_8670 n = Normalize(w);
                            target.x = step * n.x + pos->x;
                            target.y = n.y * step + pos->y;
                            target.z = n.z * step + pos->z;
                        }
                        item->mSpatial.SetPosition(&target);
                    }
                    else
                    {
                        item->mSpatial.SetPosition(&surf);
                    }
                }
                ++it;
                break;
            }
            case 2:
            {
                const Vector3_s00b0_8670* p = item->mSpatial.GetPosition();
                const float dist2 = (p->x - refPos.x) * (p->x - refPos.x) + (p->z - refPos.z) * (p->z - refPos.z) +
                                    (p->y - refPos.y) * (p->y - refPos.y);
                Item_s00b0_8670** pos = sorted.mpBegin;
                while (pos != sorted.mpEnd)
                {
                    const Vector3_s00b0_8670* q = (*pos)->mSpatial.GetPosition();
                    const float od2 = (q->x - refPos.x) * (q->x - refPos.x) + (q->z - refPos.z) * (q->z - refPos.z) +
                                      (q->y - refPos.y) * (q->y - refPos.y);
                    if (dist2 <= od2)
                        break;
                    ++pos;
                }
                {
                    AutoRef ref(item);
                    sorted.insert(pos, ref);
                }
                if (item->mTimer == 0 && item->mFlagA5)
                {
                    item->mFlagA5 = false;
                    FUN_00b54200(&item->mSpatial);
                }
                item->mTimer += dt;
                if (!(item->mFlags148 & 1) && item->mTimer > g_15673a4 && item->mpEffect == 0 && item->mState != 4)
                {
                    item->mFlagA4 = false;
                    item->mFlagA3 = false;
                    item->mSpatial.SetModelKey(&g_1567410);
                    ++it;
                    item->mState = 4;
                    break;
                }
                ++it;
                break;
            }
            case 4:
            {
                item->mTimer += dt;
                if (item->mTimer > g_167b550 && state != 5)
                {
                    IRefCounted* effect = item->mpEffect;
                    if (effect)
                    {
                        item->mpEffect = 0;
                        effect->Release();
                    }
                    ++it;
                    item->mState = 5;
                    break;
                }
                ++it;
                break;
            }
            case 5:
                it = FUN_00b06a40(it, true);
                break;
            default:
                ++it;
                break;
            }
        } while (it != mpEnd);
    }
}
struct Data9 { uint32_t d[9]; };
extern const Data9 g_167b554;              // 0x0167b554
void __cdecl ea_delete(void* p);           // 0x00f47380
struct Viewer { PV4 PV2 PV virtual void* v1c(); };                    // +0x1c
struct AppObj { PV8 PV8 PV4 virtual void* v50(); };                   // +0x50
AppObj* __cdecl App();                                                // 0x0067dd10
struct Camera
{
    void GetCameraLocationInfo(Vector3_s00b0_8670* a, Vector3_s00b0_8670* b, Vector3_s00b0_8670* c, Vector3_s00b0_8670* d) const;   // 0x007c3d30 (ret 0x10)
};
struct ResObj
{
    virtual void AddRef();                                        // +0x00
    virtual void Release();                                       // +0x04
    PV                                                            // +0x08
    virtual ResObj* v0c(uint32_t a, uint32_t b, uint32_t c);      // +0x0c
    void FUN_00b79c30();                                          // 0x00b79c30
};
struct SPVec
{
    uint32_t* mpBegin;                                    // +0x00
    uint32_t* mpEnd;                                      // +0x04
    uint32_t* mpCapacity;                                 // +0x08
    uint32_t mPad0c;                                      // +0x0c
    uint32_t mPad10;                                      // +0x10
    uint32_t mAlloc;                                      // +0x14
    void FUN_00d01790(uint32_t n);                        // 0x00d01790 (ret 4)
    void DoInsertKey(uint32_t* pos, const uint32_t& key); // 0x00b96600 (ret 8)
    void erase(uint32_t* first, uint32_t* last)           // eastl::vector::erase, inlined
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
    }
};
template <class T> const T& Min(const T& a, const T& b) { return (a < b) ? a : b; }
ResObj* __stdcall FUN_00b3d3c0(uint32_t a1, SPVec* v, uint32_t n, float f, uint32_t one, uint32_t zero);   // 0x00b3d3c0
void __cdecl FUN_00b062c0(uint32_t* begin, uint32_t* end, int a3);                                          // 0x00b062c0
struct cQueryMgr
{
    uint32_t FindNth(uint32_t key, uint32_t a, uint32_t b);           // 0x00b03320 (ret 0xc)
    void FUN_00b09070(uint32_t a1, float a2, SPVec* out, int a4);
};
struct ModelInst
{
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV2 PV      // slots 0..90
    virtual void v16c(int a);                              // +0x16c
    virtual void v170(int a);                              // +0x170
    uint32_t mField04;                                     // +0x04
    uint16_t mWord08;                                      // +0x08
    uint16_t mWord0a;                                      // +0x0a
    Vector3_s00b0_8670  mPos;                                         // +0x0c
    float    mF18;                                         // +0x18
    Data9    mData1c;                                       // +0x1c
    int32_t  mRefCount;                                    // +0x40
};
struct ModelList_s00b0_8670
{
    ModelInst** mpBegin;                                   // +0x00
    ModelInst** mpEnd;                                     // +0x04
    ModelInst** mpCapacity;                                // +0x08
    void FUN_00473270(uint32_t n);                         // 0x00473270 (ret 4)
};
struct ModelMgr { PV4 PV2 PV virtual void* v1c(uint32_t id); };   // +0x1c
ModelMgr* __cdecl ModelManager();                                 // 0x0067dd80
struct cCreatureHitBoxes
{
    char pad000[0x16504];
    ModelList_s00b0_8670 mList;                                       // +0x16504
    void FUN_00b06cd0();                                   // 0x00b06cd0
    void FUN_00b091d0();
};
struct BigElem_s00b0_8670
{
    char pad000[0x08];
    Vector3_s00b0_8670 mPos;                                          // +0x08
    float   mRadius;                                       // +0x14
    char pad018[0x28 - 0x18];
    Vector3_s00b0_8670 mCmp0;                                         // +0x28
    Vector3_s00b0_8670 mCmp1;                                         // +0x34
    Vector3_s00b0_8670 mCmp2;                                         // +0x40
    char pad04c[0x19a8 - 0x4c];
};
struct cBigList
{
    char pad000[0x1e5f0];
    BigElem_s00b0_8670* mpBegin;                                      // +0x1e5f0
    BigElem_s00b0_8670* mpEnd;                                        // +0x1e5f4
    void FUN_00b09340(Vector3_s00b0_8670* p, float radius, SPVec* out, bool full, Vector3_s00b0_8670* filter);
};
void __cdecl FUN_00b06420(uint32_t* begin, uint32_t* end, Vector3_s00b0_8670 v);   // 0x00b06420
struct FixedPool
{
    void* mpHead;                                          // +0x00
    void* mpNext;                                          // +0x04
    void* mpStart;                                         // +0x08
    void* mpEnd;                                           // +0x0c
    uint32_t mSize;                                        // +0x10
    void init(void* p, uint32_t size, uint32_t itemSize, uint32_t align, uint32_t flags);   // 0x00921260 (ret 0x14)
};
struct cEffectPool
{
    char pad000[0x2c];
    char mBuffer[0xe000];                                  // +0x2c .. +0xe02c
    cEffectPool* FUN_00b09510(int a1);
    void FUN_00b00610(int a1, FixedPool* pool);            // 0x00b00610 (ret 8)
    void FUN_00b05ba0(int a1);                             // 0x00b05ba0 (ret 4)
};
// ---- items of slice s00b08670 end

// ---- items of slice s00b0a590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_15673b0;   // 0x015673b0
extern uint32_t g_15673b4;   // 0x015673b4
extern "C" void*     EAAlloc(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
struct Vec3_s00b0_a590 {
    float x, y, z;
    Vec3_s00b0_a590() {}
    Vec3_s00b0_a590(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
struct FVec3 : Vec3_s00b0_a590 {
    FVec3() {}
    FVec3(const FVec3& o) { x = o.x; y = o.y; z = o.z; }
    FVec3& operator=(const FVec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Mat3 { float m[9]; };
struct Quat { float x, y, z, w; };
extern FVec3 g_zeroVec;     // 0x0167af5c
extern FVec3 g_axisVec;     // 0x0167b84c
extern Mat3 g_identity;    // 0x0167b554
struct Light;
struct SrcObj;
#define VPAD10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); \
    virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7(); \
virtual void p##8();
struct LightOwner {
    VPAD10(a) VPAD10(b) VPAD10(c) VPAD10(d) VPAD10(e) VPAD10(f) VPAD10(g) VPAD10(h) VPAD10(i)
    virtual void pad90();
    virtual void Update(Light* l, int flag);   // slot 91 (+0x16c)
};
struct SrcObj {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[3];
    Vec3_s00b0_a590 pos;          // +0x10
    float pad1c;
    Mat3 mat;          // +0x20
    uint32_t pad44[(0x70 - 0x44) / 4];
    float sizeA;       // +0x70
    float sizeB;       // +0x74
};
struct Light {
    LightOwner* owner;   // +0x00
    uint32_t flags;      // +0x04
    uint16_t dirty;      // +0x08
    uint16_t dirtyCount; // +0x0a
    Vec3_s00b0_a590 pos;            // +0x0c
    float scale;         // +0x18
    Mat3 mat;            // +0x1c
    uint32_t pad40[9];
    SrcObj* ref;         // +0x64
    uint32_t pad68;
    float radius;        // +0x6c
    Vec3_s00b0_a590 bmin;           // +0x70
    Vec3_s00b0_a590 bmax;           // +0x7c
    void Mark(uint16_t f) { dirty |= f; dirtyCount++; }
};
struct Located {
virtual void l0();
virtual void l1();
virtual void l2();
virtual void l3();
virtual void l4();
virtual void l5();
virtual void l6();
virtual void l7();
virtual void l8();
virtual void l9();
    virtual void l10();
    virtual const Vec3_s00b0_a590* GetPosition();     // +0x2c
    virtual const Quat* GetOrientation();  // +0x30
};
struct Avatar { uint32_t pad[0xc0 / 4]; Located loc; };
struct NounObj;
struct NounManager_s00b0_a590 {
    Avatar* GetAvatar();            // 0x00b1fdb0
    NounObj* CreateNoun(uint32_t key);   // 0x00b20c60
};
struct Viewer_s00b0_a590 {
    void GetCameraLocationInfo(Vec3_s00b0_a590* a, Vec3_s00b0_a590* b, Vec3_s00b0_a590* c, Vec3_s00b0_a590* d);   // 0x007c3d30
};
struct ViewerHolder {
virtual void h0();
virtual void h1();
virtual void h2();
virtual void h3();
virtual void h4();
virtual void h5();
virtual void h6();
    virtual Viewer_s00b0_a590* GetViewer();           // +0x1c
};
struct AppSub {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
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
    virtual ViewerHolder* GetHolder();     // +0x50
};
struct AimSource {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
    virtual Vec3_s00b0_a590* GetPoint(Vec3_s00b0_a590* out, int flag, FVec3 hint);   // +0x38
};
struct BeamArea {
    void GetEndPoints(Vec3_s00b0_a590* start, Vec3_s00b0_a590* end);   // 0x00cb8ba0
};
struct SpaceToolData {
    uint32_t pad[0x124 / 4];
    BeamArea* area;          // +0x124
    uint32_t pad2[(0x174 - 0x128) / 4];
    uint32_t flags174;
    bool HasFlag();                                       // 0x0104cd50
    void* GetStrategy();                                  // 0x0104f930
};
struct Inventory {
    SpaceToolData* GetTool();     // 0x00ff3f00
};
struct SpaceGame {
    Inventory* GetPlayerInventory();   // 0x00a1ad60
};
struct PtrVec_s00b0_a590 {
    SrcObj** begin;
    SrcObj** end;
    SrcObj** cap;
    int zero;
    SrcObj* buf[256];
};
AppSub* __cdecl App_s00b0_a590();                       // 0x0067dd10
unsigned __cdecl GetCurrentGameMode();       // 0x00b5b800
NounManager_s00b0_a590* __cdecl GetNounManager_s00b0_a590();       // 0x00b3d300
SpaceGame* __cdecl SpaceGameGet();           // 0x01002bd0
AimSource* __cdecl GetAimSource();           // 0x00b3d240
Vec3_s00b0_a590* __cdecl RotateByQuat(Vec3_s00b0_a590* out, const Vec3_s00b0_a590* v, const Quat* q);   // 0x0059aed0
struct Key3 { uint32_t a, b, c; };
extern uint32_t g_1567410_s00b0_a590;   // 0x01567410
extern uint32_t g_156741c_s00b0_a590;   // 0x0156741c
struct RefTarget {
    virtual void AddRef();    // +0x00
    virtual void Release();   // +0x04
};
struct RefElem {
    RefTarget* mpObject;      // +0x00
    RefElem() : mpObject(0) {}
    RefElem(RefTarget* p) : mpObject(p) { if (p) p->AddRef(); }
    ~RefElem() { if (mpObject) mpObject->Release(); }
    RefElem& operator=(RefTarget* p) {
        if (p != mpObject) {
            if (p) p->AddRef();
            RefTarget* old = mpObject;
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct RefVec_s00b0_a590 {
    RefElem* mpBegin;   // +0x00
    RefElem* mpEnd;     // +0x04
    RefElem* mpCap;     // +0x08
    void   F06d90(uint32_t n);                              // 0x00b06d90
    void   insertSlow(RefElem* pos, const RefElem* value);  // 0x00aea5d0
    void   push_back(const RefElem& value) {
        if (mpEnd < mpCap) {
            new ((void*)mpEnd) RefElem(value);
            ++mpEnd;
        } else {
            insertSlow(mpEnd, &value);
        }
    }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    RefElem& operator[](uint32_t i) { return mpBegin[i]; }
};
struct U32Vec {
    uint32_t* mpBegin;   // +0x00
    uint32_t* mpEnd;     // +0x04
    uint32_t* mpCap;     // +0x08
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct SpatialC {
    VPAD10(a) VPAD10(b) VPAD10(c)
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
    virtual void SetKey(const Key3* key);   // +0x94
    char pad_04[0x4c];                      // +0x04 .. +0x4f
    uint32_t flags;                         // +0x50
};
struct ItemObj : RefTarget {
    char pad_04[0x30];    // +0x04 .. +0x33
    SpatialC spatial;     // +0x34
};
struct NounObj : RefTarget {
virtual void n02();
virtual void n03();
virtual void n04();
virtual void n05();
virtual void n06();
virtual void n07();
virtual void n08();
virtual void n09();
virtual void n10();
virtual void n11();
virtual void n12();
virtual void n13();
virtual void n14();
virtual void n15();
virtual void n16();
virtual void n17();
virtual void n18();
virtual void n19();
virtual void n20();
    virtual void Init();      // +0x54
};
struct PlanetObj {
virtual void p00();
virtual void p01();
    virtual uint32_t GetId();   // +0x08
};
struct GlyphInfoVec { void* mpBegin; void* mpEnd; void* mpCap; };
struct PoolOwner_s00b0_a590 {
    virtual ~PoolOwner_s00b0_a590();              // slot 0 (overridden by PoolElem)
    uint8_t  mFlag_04;                 // +0x04
    uint8_t  mPad_05[3];               // +0x05
    GlyphInfoVec mGlyphs_08;           // +0x08
    uint32_t mAlloc_14;                // +0x14
    uint32_t mData_18;                 // +0x18
    uint32_t mData_1c;                 // +0x1c
    uint32_t mData_20;                 // +0x20
    PoolOwner_s00b0_a590(const PoolOwner_s00b0_a590&);       // 0x00b04520
};
struct PoolElem_s00b0_a590 : PoolOwner_s00b0_a590 {
    PoolElem_s00b0_a590(const PoolElem_s00b0_a590& o) : PoolOwner_s00b0_a590(o) {}
    virtual ~PoolElem_s00b0_a590();               // 0x007ced20
};
struct PoolVec {
    PoolElem_s00b0_a590* mpBegin;   // +0x00
    PoolElem_s00b0_a590* mpEnd;     // +0x04
    PoolElem_s00b0_a590* mpCap;     // +0x08
    PoolElem_s00b0_a590* erase(PoolElem_s00b0_a590* first, PoolElem_s00b0_a590* last);                     // 0x00b0aee0
    void insert(PoolElem_s00b0_a590* position, uint32_t n, const PoolElem_s00b0_a590* value);   // 0x00b0af40
};
extern "C" PoolElem_s00b0_a590* copy_forward(PoolElem_s00b0_a590* first, PoolElem_s00b0_a590* last, PoolElem_s00b0_a590* dst);     // 0x00b06500
extern "C" PoolElem_s00b0_a590* copy_backward(PoolElem_s00b0_a590* first, PoolElem_s00b0_a590* last, PoolElem_s00b0_a590* dst);    // 0x00b06550
extern "C" PoolElem_s00b0_a590* construct_range(PoolElem_s00b0_a590* first, PoolElem_s00b0_a590* last, PoolElem_s00b0_a590* dst);  // 0x00b05770
extern "C" void**    construct_cursor(void** out, PoolElem_s00b0_a590* first, PoolElem_s00b0_a590* last,
PoolElem_s00b0_a590* result, PoolElem_s00b0_a590* extra);              // 0x00b056e0
extern "C" void      fill_n_copy(PoolElem_s00b0_a590* dst, uint32_t n, const PoolElem_s00b0_a590* value,
PoolElem_s00b0_a590* extra);                                     // 0x00b05730
extern "C" void      assign_range(PoolElem_s00b0_a590* first, PoolElem_s00b0_a590* last, const PoolElem_s00b0_a590* src); // 0x00b072d0
extern "C" PoolElem_s00b0_a590* destroy_range(PoolElem_s00b0_a590* first, PoolElem_s00b0_a590* last, PoolElem_s00b0_a590* out);    // 0x00affd00
void* __cdecl PlanetModel_s00b0_a590();                                       // 0x00b3d350
void  __cdecl GetPropertyAsKey(uint32_t id, uint32_t key, uint32_t* out);          // 0x006a1250
void  __cdecl GetPropertyAsKeyInstance(uint32_t id, uint32_t key, uint32_t* out);  // 0x006a12a0
struct BeamMgr2 {
    uint32_t pad0[0x16504 / 4];
    Light** lightBegin;       // +0x16504
    Light** lightEnd;         // +0x16508
    uint32_t pad1[(0x1659c - 0x1650c) / 4];
    uint32_t objMask;         // +0x1659c
    uint32_t pad2[(0x1b8e10 - 0x165a0) / 4];
    int state;                // +0x1b8e10
    RefVec_s00b0_a590 items;             // +0x1b8e14
    uint32_t pad3[(0x1b8f44 - 0x1b8e20) / 4];
    RefVec_s00b0_a590 items2;            // +0x1b8f44
    uint32_t pad4[(0x1b905c - 0x1b8f50) / 4];
    U32Vec bitvec;            // +0x1b905c
    uint32_t pad5[(0x1b9174 - 0x1b9068) / 4];
    RefVec_s00b0_a590 nouns;             // +0x1b9174
    uint32_t pad6[(0x1ba18c - 0x1b9180) / 4];
    uint32_t mode;            // +0x1ba18c
    void Gather(const Vec3_s00b0_a590* pos, PtrVec_s00b0_a590* out, uint32_t mask, float radius, char flag, Vec3_s00b0_a590* extra, char flag2); // 0x00b0a0c0
    void UpdateBeams();       // 0x00b0a6f0
    void UpdateState();       // 0x00b0a590
    void Init();              // 0x00b0b150
    void RemoveAllNouns();    // 0x00b09b00
    void FUN_00b02120();      // 0x00b02120
    void FUN_00b06cd0();      // 0x00b06cd0
    void FUN_00b091d0();      // 0x00b091d0
    ItemObj* CreateItem();    // 0x00b00220
};
void BeamMgr2::UpdateBeams()
{
    Viewer_s00b0_a590* viewer = App_s00b0_a590()->GetHolder()->GetViewer();
    Vec3_s00b0_a590 camPos(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    Vec3_s00b0_a590 camDir(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    if (viewer)
        viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);

    Vec3_s00b0_a590 target(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    Vec3_s00b0_a590 second(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    Vec3_s00b0_a590* pSecond = 0;
    float radius = 20.0f;
    Vec3_s00b0_a590 scratch;
    unsigned mode = GetCurrentGameMode();
    if (mode == 0x1654c05) {
        radius = 25.0f;
        Avatar* av = GetNounManager_s00b0_a590()->GetAvatar();
        if (av) {
            Located* loc = &av->loc;
            const Vec3_s00b0_a590* a = RotateByQuat(&scratch, &g_axisVec, loc->GetOrientation());
            float d = camDir.x * a->x + a->y * camDir.y + a->z * camDir.z;
            float px = camDir.x - d * a->x;
            float pz = camDir.z - a->z * d;
            float py = camDir.y - a->y * d;
            float inv = 1.0f / sqrtf(py * py + (pz * pz + px * px));
            Vec3_s00b0_a590 n(inv * px * 16.0f, py * inv * 16.0f, pz * inv * 16.0f);
            const Vec3_s00b0_a590* lp = loc->GetPosition();
            target.x = n.x + lp->x;
            target.z = lp->z + n.z;
            target.y = lp->y + n.y;
            second = *loc->GetPosition();
            pSecond = &second;
            goto done;
        } else {
            SpaceToolData* tool = SpaceGameGet()->GetPlayerInventory()->GetTool();
            if (tool && tool->HasFlag() && tool->GetStrategy() && tool->area) {
                Vec3_s00b0_a590 end;
                tool->area->GetEndPoints(&scratch, &end);
                target = end;
                goto done;
            }
        }
        goto dflt;
    } else if (mode == 0x1654c01) {
    dflt:
        target.x = camDir.x * 20.0f + camPos.x;
        target.y = camDir.y * 20.0f + camPos.y;
        target.z = camDir.z * 20.0f + camPos.z;
    } else {
        const Vec3_s00b0_a590* r = GetAimSource()->GetPoint(&scratch, 1, g_zeroVec);
        target = *r;
    }
done:

    PtrVec_s00b0_a590 v;
    v.zero = 0;
    v.begin = v.buf;
    v.end = v.buf;
    v.cap = v.buf + 256;
    Gather(&target, &v, objMask, radius, 1, pSecond, 1);

    Light** d = lightBegin;
    Light** e = lightEnd;
    SrcObj** s = v.begin;
    if (d != e) {
        do {
            if (s == v.end)
                break;
            SrcObj* src = *s;
            if (src) {
                Light* l1 = *d;
                Light** n = d + 1;
                d = n;
                if (n != e) {
                    Light* l2 = *n;
                    d = n + 1;
                    float a55 = src->sizeA * 0.55f;
                    float t = src->sizeB * 0.35f;
                    float u = src->sizeB - t;
                    float h = a55 * 0.5f;

                    l1->pos = src->pos;
                    l1->Mark(4);
                    l1->mat = src->mat;
                    l1->Mark(2);
                    {
                        Vec3_s00b0_a590 hi(h, h, t);
                        Vec3_s00b0_a590 lo(-h, -h, 0.0f);
                        l1->bmax = hi;
                        l1->bmin = lo;
                        Vec3_s00b0_a590 ext(hi.x - lo.x, hi.y - lo.y, hi.z - lo.z);
                        l1->radius = sqrtf(ext.x * ext.x + ext.y * ext.y + ext.z * ext.z);
                    }
                    if (l1->ref) {
                        SrcObj* old = l1->ref;
                        l1->ref = 0;
                        old->Release();
                    }
                    {
                        SrcObj* old = l1->ref;
                        if (src != old) {
                            src->AddRef();
                            l1->ref = src;
                            if (old) old->Release();
                        }
                    }
                    l1->flags |= 1;
                    l1->owner->Update(l1, 1);

                    float x = src->pos.x, y = src->pos.y, z = src->pos.z;
                    float inv = 1.0f / sqrtf(x * x + y * y + z * z);
                    l2->Mark(4);
                    l2->pos.x = x * inv * t + src->pos.x;
                    l2->pos.y = src->pos.y + y * inv * t;
                    l2->pos.z = src->pos.z + z * inv * t;
                    l2->mat = src->mat;
                    l2->Mark(2);
                    {
                        Vec3_s00b0_a590 hi(a55, a55, u);
                        Vec3_s00b0_a590 lo(-a55, -a55, 0.0f);
                        l2->bmax = hi;
                        l2->bmin = lo;
                        Vec3_s00b0_a590 ext(hi.x - lo.x, hi.y - lo.y, hi.z - lo.z);
                        l2->radius = sqrtf(ext.x * ext.x + ext.y * ext.y + ext.z * ext.z);
                    }
                    if (l2->ref) {
                        SrcObj* old = l2->ref;
                        l2->ref = 0;
                        old->Release();
                    }
                    {
                        SrcObj* old = l2->ref;
                        if (src != old) {
                            src->AddRef();
                            l2->ref = src;
                            if (old) old->Release();
                        }
                    }
                    l2->flags |= 1;
                    l2->owner->Update(l2, 1);
                    d = n + 1;
                    s++;
                    continue;
                }
            } else {
                s++;
                continue;
            }
            e = lightEnd;
        } while (d != e);
    }
    while (d != lightEnd) {
        Light* l = *d;
        l->flags &= ~1u;
        l->mat = g_identity;
        l->scale = 1.0f;
        l->pos = g_zeroVec;
        l->dirty = 0;
        l->dirtyCount = 0;
        SrcObj* r = l->ref;
        if (r) {
            l->ref = 0;
            r->Release();
        }
        l->owner->Update(l, 0);
        d++;
    }
    if (v.begin && v.begin[-1])
        operator_delete_array(v.begin);
}
static void destroy_values(PoolElem_s00b0_a590* first, PoolElem_s00b0_a590* last)
{
    while (first < last) {
        first->~PoolElem_s00b0_a590();
        ++first;
    }
}
// ---- items of slice s00b0a590 end

// ---- items of slice s00b0b3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gVtablePaintBase[];                                            // 0x013eb384
extern void* gVtablePaintDtor[];                                            // 0x013eb394
extern void* gVtablePaintSub[];                                             // 0x0145c828
extern void* gVtablePaint[];                                                // 0x0145c878
extern void* gVtablePaint3[];                                               // 0x0145c824
void operator delete(void* p);                                           // 0x00f47380
void* __cdecl EaAllocate(unsigned int size, const char* name, int a, int b, int c, int line); // 0x00f473a0
void __cdecl RemoveMessageHandler(void* handler, uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00571db0
struct GonzagoSub {                                      // secondary base at +4
    void Construct();                                    // 0x00b5b960
    ~GonzagoSub();                                       // 0x00b5b9a0
};
struct HierGrid {
    HierGrid();                                          // 0x00703ce0
    ~HierGrid();                                         // 0x00750310
};
struct PaintPool {
    char   mData[0xc];                                   // +0x00
    void*  mpChain;                                      // +0x0c
    void Construct();                                    // 0x00b05a80
    void ConstructAlt();                                 // 0x00b05ae0
    void ReleaseChain(void* chain);                      // 0x00b04350 (ret 4)
    void WalkChain(void* chain);                         // 0x00b04420 (ret 4)
};
struct __declspec(align(8)) Scatter_s00b0_b3d0 {
    char mData[0x19a0];                                  // +0x0000
    Scatter_s00b0_b3d0();
    Scatter_s00b0_b3d0(const Scatter_s00b0_b3d0&);
    ~Scatter_s00b0_b3d0();
    void AssignFrom(const Scatter_s00b0_b3d0&);                     // 0x00b0a3f0 (ret 4)
};
struct ScatterE_s00b0_b3d0 {
    uint32_t mKey;                                       // +0x0000
    Scatter_s00b0_b3d0  mPayload;                                   // +0x0008 (8-byte aligned)
};
void* __cdecl ScatterCopyRange(void* first, void* last, void* dest);        // 0x00b096e0
void* __cdecl ScatterFillRange(void* first, void* last, void* dest);        // 0x00b048f0
void* __cdecl ScatterCopyBackward(ScatterE_s00b0_b3d0* first, ScatterE_s00b0_b3d0* last, ScatterE_s00b0_b3d0* dest); // 0x00b0a530
struct ScatterVec {                                      // sp_vector<ScatterE, 256>
    ScatterE_s00b0_b3d0* mpBegin;                                   // +0x0000
    ScatterE_s00b0_b3d0* mpEnd;                                     // +0x0004
    ScatterE_s00b0_b3d0* mpCap;                                     // +0x0008
    void*     mPad0c;                                    // +0x000c
    ScatterE_s00b0_b3d0* mpInline;                                  // +0x0010
    void*     mPad14;                                    // +0x0014
    char      mBuf[0x19a800];                            // +0x0018
    ScatterE_s00b0_b3d0* Insert(ScatterE_s00b0_b3d0* pos, const ScatterE_s00b0_b3d0& v);  // 0x00b0c110 (ret 8)
    void InsertGrow(ScatterE_s00b0_b3d0* pos, const ScatterE_s00b0_b3d0& v);   // 0x00b0bfa0 (ret 8)
    void DestroyElements(ScatterE_s00b0_b3d0* first, ScatterE_s00b0_b3d0* last);  // 0x00b051f0 (ret 8)
};
struct ScatterBase {
    ScatterBase();                                       // 0x007cef40
    virtual ~ScatterBase();                              // 0x007ced20
};
struct Elem24 : ScatterBase {
    char mRest[0x20];                                    // +0x0004
};
struct Elem24Vec {
    Elem24* mpBegin;                                     // +0x0000
    Elem24* mpEnd;                                       // +0x0004
    Elem24* mpCap;                                       // +0x0008
    void InsertN(Elem24* pos, unsigned int count, const Elem24& v); // 0x00b0af40 (ret 0xc)
    void DestroyRange(Elem24* first, Elem24* last);      // 0x00b0aee0 (ret 8)
    void DestroyStorage();                               // 0x00b002a0
    void Resize(unsigned int n);                         // 0x00b0bd10 (ret 4)
};
struct RefVec_s00b0_b3d0 {
    void* mpBegin; void* mpEnd; void* mpCap; void* mPad0c; void* mpInline; void* mpAlloc;
    char  mBuf[0x100];                                   // inline buffer
    void Destroy();                                      // 0x00ae6970
};
struct RefVecBig {
    void* mpBegin; void* mpEnd; void* mpCap; void* mPad0c; void* mpInline; void* mpAlloc;
    char  mBuf[0x1000];                                  // inline buffer
    void Destroy();                                      // 0x00ae6970
};
struct SpatialVec {
    void*    mpBegin;                                    // +0x00
    void*    mpEnd;                                      // +0x04
    void*    mpCap;                                      // +0x08
    char     mPad0c[8];                                  // +0x0c
    uint32_t mFlag;                                      // +0x14
    char     mBuf[0x400];                                // +0x18 inline buffer
    void ResetRange(void* first, void* last);            // 0x00b006f0 (ret 8)
};
struct EntVec {
    void*    mpBegin;                                    // +0x00
    void*    mpEnd;                                      // +0x04
    void*    mpCap;                                      // +0x08
    char     mPad0c[8];                                  // +0x0c
    void*    mpAlloc;                                    // +0x14
    char     mBuf[0x80];                                 // +0x18 inline buffer
    void DestroyValues(void* first, void* last);         // 0x005f3680 (ret 8)
};
struct PaintMgr {
    void*    mVtable;                                    // +0x0000
    void*    mVtableSub;                                 // +0x0004
    void*    mVtable3;                                   // +0x0008
    char     mGonzagoRest[0x14];                         // +0x000c
    uint32_t mHandler;                                   // +0x0020
    uint32_t mHandlerArg0;                               // +0x0024
    uint32_t mHandlerArg1;                               // +0x0028
    uint32_t mHandlerArg2;                               // +0x002c
    uint32_t mHandlerArg3;                               // +0x0030
    char     mPoolA[0x0c];                               // +0x0034
    void*    mpPoolAChain;                               // +0x0040
    char     mPad044[0x8080 - 0x0044];                   // +0x0044
    char     mPoolB[0x0c];                               // +0x8080
    void*    mpPoolBChain;                               // +0x808c
    char     mPad090[0x160e8 - 0x8090];                  // +0x8090
    SpatialVec mSpatial;                                 // +0x160e8
    void*    mpGrid;                                     // +0x16500
    EntVec   mEnt;                                       // +0x16504
    uint32_t mObjMask;                                   // +0x1659c
    char     mPoolC[0x0c];                               // +0x165a0
    void*    mpPoolCChain;                               // +0x165ac
    char     mPad165b0[0x1e5f0 - 0x165b0];               // +0x165b0
    ScatterVec mScatter;                                 // +0x1e5f0
    char     mPad1b8e08[8];                              // +0x1b8e08
    uint32_t mUnk1b8e10;                                 // +0x1b8e10
    RefVec_s00b0_b3d0   mVec1;                                      // +0x1b8e14
    int32_t  mUnk1b8f2c;                                 // +0x1b8f2c
    Elem24Vec mItems;                                    // +0x1b8f30
    char     mPad1b8f3c[8];                              // +0x1b8f3c
    RefVec_s00b0_b3d0   mVec3;                                      // +0x1b8f44
    RefVec_s00b0_b3d0   mVec4;                                      // +0x1b905c
    RefVecBig mVec5;                                     // +0x1b9174
    uint32_t mFlags1;                                    // +0x1ba18c
    uint32_t mUnk1ba190;                                 // +0x1ba190

    PaintMgr();                                          // 0x00b0bdb0
    ~PaintMgr();                                         // 0x00b0bb50
};
// ---- items of slice s00b0b3d0 end

// ---- items of slice s00c6f6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int    DAT_01578890;
extern int    DAT_01578ba0;
extern void*  DAT_015b4500;                            // default cEllipticalOrbit
extern void*  DAT_015787f0;                            // default rotation axis
typedef unsigned char  uchar;
void* __cdecl FUN_00c884f0(void* id);                 // 0xc884f0  Simulator::cSpatialObject::Cast
void* __cdecl FUN_00b18460(void* id);                 // 0xb18460  (class-id dispatch)
void* __cdecl FUN_00b18590(void* a, void* b);         // 0xb18590  SP::cGameData::Write
void* __cdecl FUN_00c88a90(void* a, void* b);         // 0xc88a90  Simulator::cSpatialObject::Write
void* __cdecl FUN_00b18600(void* a, void* b);         // 0xb18600  SP::cGameData::Read
void* __cdecl FUN_00c88b00(void* a, void* b);         // 0xc88b00  Simulator::cSpatialObject::Read
void* __cdecl FUN_00692f90(void* a, void* b, void* c, void* d); // 0x692f90 cVarListSerializer::cVarListSerializer
void* __cdecl FUN_00692900(void* a, void* b);         // 0x692900 cVarListSerializer::Serialize
void* __cdecl FUN_00693e10(void* a, void* b);         // 0x693e10 cVarListSerializer::Read
void* __cdecl FUN_00c884f0(void* self, unsigned type); // 0xc884f0  Simulator::cSpatialObject::Cast
void* __cdecl FUN_00b18460(void* self, unsigned type); // 0xb18460  cGameData::Cast
struct Vec3_s00c6_f6e0 { float x, y, z; };
struct Orbit { uint w[0x1a]; void Recalc(); };   // cEllipticalOrbit, 0x68 bytes
struct WorldObj { void Func70860(); };           // the b8de30 result
struct NameRow { void* col0; void* col1; void* col2; };
extern NameRow g_NameRows[];                     // 0x01578750 (0xc-byte rows)
struct PlanetRecord {
    uchar   pad_000[0x18];
    void*   mName_18;          // 0x18  (eastl::wstring begin)
    uchar   pad_01c[0x0c];
    int     mType_28;          // 0x28  ePlanetType
    int     mFlags_2c;         // 0x2c
    Orbit   mOrbit_30;         // 0x30  cEllipticalOrbit
    bool    mRotationIsNull_98; // 0x98
    uchar   pad_099[0x3];
    Vec3_s00c6_f6e0    mRotationAxis_9c;  // 0x9c
    float   mRotationPeriod_a8; // 0xa8
    char    mRingType_ac;      // 0xac

    WorldObj* GetWorld();      // 0x00b8de30 (thiscall; retail returns the owning WorldObj)
};
struct SimPlanet {
    uchar        pad_000[0x13c];
    PlanetRecord* mRecord_13c;   // 0x13c
    uchar        pad_140[0x54];
    int          mTechLevel_194; // 0x194

    int   GetPlanetType() const;                 // 0x00c70880
    void* GetOrbit() const;                      // 0x00c708a0
    void  SetOrbit(void* pOrbit);                // 0x00c708c0
    bool  IsRotationNull() const;                // 0x00c708f0
    void  SetRotationNull(bool val);             // 0x00c70910
    void* GetRotationAxis() const;               // 0x00c70930
    void  SetRotationAxis(Vec3_s00c6_f6e0* axis);           // 0x00c70950
    float GetRotationPeriod() const;             // 0x00c70980
    void  SetRotationPeriod(float v);            // 0x00c709b0

    void* GetNameRow(bool wantCol0) const;       // 0x00c707f0
    void  Func70860();                           // 0x00c70860
};
struct VarListSerializer {
    uchar mData_000[0xa14];
    VarListSerializer(const void* obj, void* desc, unsigned count); // 0x692f90
    bool Serialize(void* pArchive);                               // 0x692900
    bool Read(void* pArchive);                                    // 0x693e10
};
struct GameDataPart { bool Write(void* pArchive); bool Read(void* pArchive); };     // 0xb18590 / 0xb18600
struct SpatialObjPart { bool Write(void* pArchive); bool Read(void* pArchive); };   // 0xc88a90 / 0xc88b00
struct VisiblePlanet {
    uchar mSpatial_000[0xd4];   // 0x00..0xd4 cSpatialObject
    uchar mGameData_d4[0x44];   // 0xd4..    cGameData

    void* Cast(unsigned type);                       // 0x00c6fec0
    bool  Write(void* pArchive);                     // 0x00c6ff00
    void* Cast2(unsigned type);                      // 0x00c6ffd0
    bool  Write2(void* pArchive);                    // 0x00c70010
    bool  Read(void* pArchive);                      // 0x00c70090
};
// ---- items of slice s00c6f6e0 end

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

// @ 0x00aff400
bool Simulator::cFruit::Write(cOutStream* pStream)
{
    uint32_t nType = 0x2c9cc8e;
    IAVIStream* pIO = pStream->GetIO();
    IStream_s00af_ef10* pOut = pIO->GetStream();
    EA::IO::WriteUint32(pOut, &nType, 1, 0);
    bool bResult = BaseWrite(pStream);
    cVarListSerializer_s00af_ef10 serializer(this, gVarListDataFruit, 0x1a80d26);
    if (bResult && serializer.Serialize(pStream))
        return true;
    return false;
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

// @ 0x00aff5e0
bool cFruitGameData::WriteData(cOutStream* pStream)
{
    uint32_t nType = 0x2e9688e;
    IAVIStream* pIO = pStream->GetIO();
    IStream_s00af_ef10* pOut = pIO->GetStream();
    EA::IO::WriteUint32(pOut, &nType, 1, 0);
    bool bResult = Write(pStream);
    cVarListSerializer_s00af_ef10 serializer(this, gVarListDataGame, 0x1a80d26);
    if (bResult && serializer.Serialize(pStream))
        return true;
    return false;
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

// @ 0x00aff870
bool WriteUint64Value(cOutStream* pStream, const uint64_t* pValue)
{
    IAVIStream* pIO = pStream->GetIO();
    uint64_t nValue = *pValue;
    IStream_s00af_ef10* pStream2 = pIO->GetStream();
    EA::IO::WriteUint64(pStream2, &nValue, 1, 0);
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

// @ 0x00affe10
uint32_t CountItemBits(const cPtrVector* pVector)
{
    if (pVector == 0)
        return 0;
    uint32_t nCount = (uint32_t)(pVector->mpEnd - pVector->mpBegin);
    uint32_t nSum = 0;
    for (uint32_t i = 0; i < nCount; ++i)
        nSum += CountBits(pVector->mpBegin[i]->mnField48);
    return nSum;
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

// @ 0x00b00000
float RandomRange()
{
    extern double RandomUniform();      // 0x009360d0
    extern float gRangeMin;             // 0x01567398
    extern float gRangeMax;             // 0x0156739c
    if (gRangeMin == -1.0f || gRangeMax == -1.0f)
        return -1.0f;
    return RandomUniform() * (gRangeMax - gRangeMin) + gRangeMin;
}

// @ 0x00b00080
void cStateObject::SetState(int32_t nState, bool bForce)
{
    if (!bForce && nState == (int32_t)mnState)
        return;
    switch (nState) {
    case 0:
        mnState = nState;
        mbFlagA4 = 1;
        mbFlagA3 = 1;
        break;
    case 2:
        mnState = nState;
        mField168 = 0;
        break;
    case 3:
        mnState = nState;
        mbFlagA5 = 1;
        break;
    case 4:
        mbFlagA4 = 0;
        mbFlagA3 = 0;
        mSub.SetData(gStateData);
        mnState = nState;
        break;
    case 5:
    case 6:
        if (mpObject108 != 0) {
            cRefObject* pObject = mpObject108;
            mpObject108 = 0;
            pObject->Release();
        }
        // fall through
    case 1:
        mnState = nState;
        break;
    }
}

// @ 0x00b00150
void cSplitSerializer::Reset()
{
    mField00 = 0;
    mField08 = 0;
    mField0c = 0;
    if (mpReader != 0) {
        cSubObject* pReader = mpReader;
        mpReader = 0;
        pReader->Release();
    }
    if (mpWriter != 0) {
        cSubObject* pWriter = mpWriter;
        mpWriter = 0;
        pWriter->Close();
    }
    mField18 = 0;
    if (mpWriter != 0)
        mpWriter->Close();
    if (mpReader != 0)
        mpReader->Release();
}

// @ 0x00b001b0
void cFruitEditorData::OnCreated()
{
    EA::Messaging::Server_s00af_ef10* pServer = EA::Messaging::GetServer();
    mpServer = pServer;
    mpHandler = this;
    mpIdArray = gFruitMessageIds;
    mnIdCount = 4;
    mnPriority = 0;
    EA::Messaging::IHandler_s00af_ef10* pHandler = this;
    if (pServer != 0 && pHandler != 0) {
        for (uint32_t i = 0; i < 4; ++i)
            pServer->AddHandler(pHandler, gFruitMessageIds[i]);
    }
    mpCreatureData->SetLastAnimationPlayed(0x30fc4ec);
    mpCreatureData->ResetAnimation();
    mnFlags |= 0x28;
}

// @ 0x00b00220
cFruit* CreateFruit()
{
    cFruit* pFruit = NounManager(0x2c9cc91)->CreateNoun(0x2c9cc91);
    if (pFruit == 0)
        return 0;
    pFruit->Initialize();
    ++gNextFruitId;
    pFruit->Release();
    return pFruit;
}

// @ 0x00b002e0
void SetObjectValue(cValueHost* pHost)
{
    AutoRefCount<cRefObject>* pValue =
        (AutoRefCount<cRefObject>*)pHost->mpfnGet(pHost);
    static AutoRefCount<cRefObject> sDefault;
    *pValue = sDefault.mpObject;
}

// @ 0x00b00350
void WriteVector3Value5(cValueHost* pHost)
{
    cVector3* pValue = (cVector3*)pHost->mpfnGet(pHost);
    static cVector3 const sDefault;
    *pValue = sDefault;
}

// @ 0x00b00390
void WriteItemList(cSerializeMgr* pMgr, const cSerializeItemList* pList)
{
    IAVIStream* pIO = pMgr->GetIO();
    uint32_t nCount = (uint32_t)(pList->mpEnd - pList->mpBegin);
    IStream_s00af_ef10* pStream = pIO->GetStream();
    EA::IO::WriteUint32(pStream, &nCount, 1, 0);
    cSerializeItem* pItem = pList->mpBegin;
    cSerializeItem* pEnd = pList->mpEnd;
    for (; pItem != pEnd; ++pItem)
        pItem->WriteItem(pMgr);
    pMgr->End();
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

// @ 0x00b00450
void WriteRotationList(cSerializeMgr* pMgr, const cRotList* pList)
{
    uint32_t nCount = (uint32_t)((pList->mpEnd - pList->mpBegin));
    IAVIStream* pIO = pMgr->GetIO();
    IStream_s00af_ef10* pStream = pIO->GetStream();
    EA::IO::WriteUint32(pStream, &nCount, 1, 0);
    RotSerial* pItem = pList->mpBegin;
    RotSerial* pEnd = pList->mpEnd;
    for (; pItem != pEnd; ++pItem)
        pItem->Save(pMgr->GetIO()->GetStream());
    pMgr->End();
}

// @ 0x00b004e0
bool ReadTreeItems(cSerializeMgr* pMgr, const cRBTree* pTree)
{
    for (cRBNode* pNode = pTree->mAnchor.mpParent;
         pNode != (cRBNode*)&pTree->mAnchor; pNode = RBTreeIncrement(pNode)) {
        cSerializeItem* pReadItem = pNode->mpItem;
        if (pReadItem != 0)
            pReadItem->ReadItem(pMgr);
    }
    return true;
}

// @ 0x00b00520
bool WriteTreeClumps(TreeClumpArchive* archive, cTreeClumpVector* pVector)
{
    cTreeClumpData* end = (cTreeClumpData*)pVector->mpEnd;
    for (cTreeClumpData* cur = (cTreeClumpData*)pVector->mpBegin; cur != end; ++cur) {
        if (cur->mBody != 0)
            archive->AddChild(cur->mBody, &gTreeClumpType, gTreeClumpName);
    }
    return true;
}

// 0x00b00560 (byte-exact lifted version: match/slices/s00b00560/s00b00560.cpp)
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
void __stdcall SpatialEntryResetRange(cSpatialEntry* pFirst, cSpatialEntry* pLast)
{
    for (; pFirst < pLast; ++pFirst) {
        pFirst->mpVtbl = 0;
        pFirst->mField08 = 0;
        pFirst->mField0c = 0;
        _ReadWriteBarrier();

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
        _ReadWriteBarrier();
        if (pFirst->mpRef1 != nullptr)
            pFirst->mpRef1->Reset();
        if (pFirst->mpRef0 != nullptr)
            pFirst->mpRef0->Release();
    }
}

// @ 0x00b00820
void InsertionSortByDistance_Positioned(cPositionedObject** pFirst, cPositionedObject** pLast, const Vec3* pReference)
{    if (pFirst == pLast)
        return;

    for (cPositionedObject** pCur = pFirst + 1; pCur != pLast; ++pCur) {
        cPositionedObject* pValue = *pCur;
        cPositionedObject** pSlot = pCur;
        if (pCur != pFirst) {
            float dx1 = pReference->mX - pValue->mX;
            float dy1 = pReference->mY - pValue->mY;
            float dz1 = pReference->mZ - pValue->mZ;
            float dist1 = dx1 * dx1;
            dist1 += dy1 * dy1;
            dist1 += dz1 * dz1;
            do {
                cPositionedObject* pPrev = pSlot[-1];
                float dx2 = pReference->mX - pPrev->mX;
                float dy2 = pReference->mY - pPrev->mY;
                float dz2 = pReference->mZ - pPrev->mZ;
                if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 > dist1) {
                    *pSlot = pPrev;
                    --pSlot;
                } else {
                    break;
                }
            } while (pSlot != pFirst);
        }
        *pSlot = pValue;
    }}

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
{    if (pFirst == pLast)
        return;

    for (cNode** pCur = pFirst + 1; pCur != pLast; ++pCur) {
        cNode* pValue = *pCur;
        cNode** pSlot = pCur;
        if (pCur != pFirst) {
            float dx1 = refX - pValue->mX;
            float dy1 = refY - pValue->mY;
            float dz1 = refZ - pValue->mZ;
            float dist1 = dy1 * dy1;
            dist1 += dx1 * dx1;
            dist1 += dz1 * dz1;
            do {
                cNode* pPrev = pSlot[-1];
                float dx2 = refX - pPrev->mX;
                float dy2 = refY - pPrev->mY;
                float dz2 = refZ - pPrev->mZ;
                if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 > dist1) {
                    *pSlot = pPrev;
                    --pSlot;
                } else {
                    break;
                }
            } while (pSlot != pFirst);
        }
        *pSlot = pValue;
    }}

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
{    if (pFirst == pLast)
        return;

    for (Vec3** pCur = pFirst + 1; pCur != pLast; ++pCur) {
        Vec3* pValue = *pCur;
        Vec3** pSlot = pCur;
        if (pCur != pFirst) {
            float dx1 = refX - pValue->mX;
            float dy1 = refY - pValue->mY;
            float dz1 = refZ - pValue->mZ;
            float dist1 = dx1 * dx1;
            dist1 += dz1 * dz1;
            dist1 += dy1 * dy1;
            do {
                Vec3* pPrev = pSlot[-1];
                float dx2 = refX - pPrev->mX;
                float dy2 = refY - pPrev->mY;
                float dz2 = refZ - pPrev->mZ;
                if (dx2 * dx2 + dy2 * dy2 + dz2 * dz2 > dist1) {
                    *pSlot = pPrev;
                    --pSlot;
                } else {
                    break;
                }
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

extern "C" char g_145c6d0[];   // 0x0145c6d0 Simulator::cFruitView vtable
struct FruitOwnerSub {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42();
    virtual void* IsVisible();                   // +0xac
};
struct FruitOwner {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual FruitOwner* Cast(u32 type);          // +0x0c
    char pad04[0x30];
    FruitOwnerSub mSub;                          // +0x34
};
struct FruitViewBase {
    void ConstructSpatialObjectView();           // 0x00e92af0 cSpatialObjectView::cSpatialObjectView
};
struct FruitView {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual void SetOwner(void* owner);          // +0x24
};

// @ 0x00b01890
void* cFruitViewFactory::Create(void* owner)
{
    FruitOwner* obj = owner ? ((FruitOwner*)owner)->Cast(0x02c9cc8e) : 0;
    FruitView* view = 0;
    if (obj->mSub.IsVisible()) {
        u8* o = (u8*)op_new(0x38, "Simulator/cFruitView", 0, 0, 0, 0);
        if (o != 0) {
            ((FruitViewBase*)o)->ConstructSpatialObjectView();
            *(void**)o = g_145c6d0;
            *(u32*)(o + 0x34) = 0;
            view = (FruitView*)o;
        } else {
            view = 0;
        }
        view->SetOwner(owner);
    }
    return view;
}

// @ 0x00b01910
Simulator_cFruit::Simulator_cFruit()
{
    ((Op*)this)->M3f9b0();
    ((Op*)((u8*)this + 0x130))->M03d0();
    *(void**)this = (void*)0x0145c5c8;
    this->vtbl4 = (void*)0x0145c5b4;
    this->vtbl34 = (void*)0x0145c4f0;
    *(void**)((u8*)this + 0x130) = (void*)0x0145c4d0;
    this->f148 = 0;
    ((Op*)this)->M3f9a0(4);
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
    *(void**)self = (void*)g_145c748;
    self->vtbl4 = (void*)g_145c738;
    self->vtbl34 = (void*)g_145c71c;
    self->f4c = 0;
    self->f54 = 0;
    _ReadWriteBarrier();
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
    ((Op*)at(self, 0x34))->M0520();
    ((Op*)self)->M184c0();
}

// @ 0x00b01b50
void cFruitGroupOps_s00b0_1690::SetEffect(u32 mode, u8 force)
{
    u8* self = (u8*)this;
    if (*((u32*)self + 0x1cc / 4) == mode && force == 0) {
        return;
    }
    if (mode > 2) {
        return;
    }
    u32* slot = (u32*)(self + 0x1d0);
    *(u32*)(self + 0x1cc) = mode;
    if (*slot != 0) {
        void* cur = (void*)*slot;
        (*(void(__thiscall**)(void*, int))((char*)vtbl(cur) + 0xc))(cur, 1);
        void* c2 = (void*)*slot;
        if (c2 != 0) {
            *slot = 0;
            (*(void(__thiscall**)(void*))((char*)vtbl(c2) + 4))(c2);
        }
    }
    if (*(u32*)(self + 0x1cc) == 1) {
        void* em = SP_EffectsManager();
        void* cur = (void*)*slot;
        if (cur != 0) {
            *slot = 0;
            (*(void(__thiscall**)(void*))((char*)vtbl(cur) + 4))(cur);
        }
        (*(void(__thiscall**)(void*, u32, u32, u32*))((char*)vtbl(em) + 0x2c))(em, g_15673c0, g_15673c4, slot);
    } else if (*(u32*)(self + 0x1cc) == 2) {
        void* em = SP_EffectsManager();
        void* cur = (void*)*slot;
        if (cur != 0) {
            *slot = 0;
            (*(void(__thiscall**)(void*))((char*)vtbl(cur) + 4))(cur);
        }
        (*(void(__thiscall**)(void*, u32, u32, u32*))((char*)vtbl(em) + 0x2c))(em, g_15673c8, g_15673cc, slot);
    }
    if (*slot != 0) {
        u8 msg[0x38];
        XformMsg_ctor(msg);
        *(u32*)(msg + 4) = *(u32*)(self + 0x5c);
        *(u32*)(msg + 8) = *(u32*)(self + 0x60);
        *(u32*)(msg + 0xc) = *(u32*)(self + 0x64);
        *(u16*)(msg + 2) = *(u16*)(msg + 2) + 1;
        *(u16*)(msg + 0) |= 4;
        f32 scale = *(f32*)(self + 0x68) * 1.5f;
        for (int i = 0; i < 9; i++) {
            *(u32*)(msg + 0x14 + i * 4) = *(u32*)(self + 0x6c + i * 4);
        }
        u16 w = *(u16*)(msg + 2);
        *(u16*)(msg + 0) |= 2;
        w = (u16)(w + 1);
        w = (u16)(w + 1);
        *(u16*)(msg + 2) = w;
        *(f32*)(msg + 0x10) = scale;
        void* target = (void*)*slot;
        (*(void(__thiscall**)(void*, u8*))((char*)vtbl(target) + 0x18))(target, msg);
        void* t2 = (void*)*slot;
        (*(void(__thiscall**)(void*, int))((char*)vtbl(t2) + 8))(t2, 0);
    }
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
    _ReadWriteBarrier();
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

// 0x00b01d30 (byte-exact lifted version: match/slices/s00b01d30/s00b01d30.cpp)
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

// 0x00b02350 (byte-exact lifted version: match/slices/s00b02350/s00b02350.cpp)
void GridEntryOps::SetEntry(void* obj, u8 add)
{
    u8* self = (u8*)this;
    u8* o = (u8*)obj;
    if (o == 0) {
        return;
    }
    u32 grid = *(u32*)(self + 0x16500);
    if (grid == 0) {
        return;
    }
    if (*(u32*)(grid + 0x24) == *(u32*)(grid + 0x28)) {
        GridRebuildProxy(self);
    }
    if (add == 0) {
        i32 idx = *(i32*)(o + 0x78);
        if (idx < 0) {
            return;
        }
        u32 g = *(u32*)(self + 0x16500);
        if (*(u32*)(g + 0x24) != *(u32*)(g + 0x28)) {
            SP_HierGridStub_Remove((void*)g, (u32)idx);
        }
        *(u32*)(o + 0x78) = 0xffffffff;
    } else {
        if (*(i32*)(o + 0x78) != -1) {
            return;
        }
        u32 g = *(u32*)(self + 0x16500);
        if (*(u32*)(g + 0x24) == *(u32*)(g + 0x28)) {
            return;
        }
        u32 r = SP_cHierGrid_CreateEntry((void*)g, o + 0x10, *(f32*)(o + 0x6c));
        *(u32*)(o + 0x78) = r;
    }
}

// @ 0x00b023d0
void TreeApplyOps::Apply(void* key, u32 id, u32 arg)
{
    if (key == 0 || id == 0xffffffff) {
        return;
    }
    u8* self = (u8*)this;
    u32 idv = id;
    RBF(self + 0x8080)->find(&id, (const u32*)&key);
    if ((void*)id == (void*)(self + 0x8084)) {
        return;
    }
    u8* node = (u8*)id;
    if (*(u32*)(node + 0x30) == 0) {
        return;
    }
    if (*(u32*)(node + 0x18) <= idv) {
        return;
    }
    ((TreeApplyTarget*)*(u32*)(node + 0x2c))->SetKey(idv, *(float*)&arg);
}

// @ 0x00b02430
void PairTreeOps::Find(void* out, const u32* key)
{
    u8* self = (u8*)this;
    u8* first = (u8*)(self + 4);
    u8* node = *(u8**)(self + 0xc);
    if (node != 0) {
        u32 k1 = key[1], k0 = key[0];
        do {
            u32 nk1 = *(u32*)(node + 0x14);
            u32 nk0 = *(u32*)(node + 0x10);
            if (k1 > nk1 || (k1 == nk1 && k0 >= nk0)) {
                node = *(u8**)node;
            } else {
                first = node;
                node = *(u8**)(node + 4);
            }
        } while (node != 0);
    }
    u32* tmp = (u32*)&key;
    FindNode(tmp, key);
    *(u32*)out = *tmp;
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

// The function-local static of SP::GetDefaultValue<cSPTransform>: its init guard and the value itself.
struct DefaultTransform_s00b0_24a0 {
    u16 mFlags;                  // +0x00 (0x0167bb50)
    u16 mFlags2;                 // +0x02
    f32 mPosition[3];            // +0x04
    f32 mScale;                  // +0x10
    char mRotation[0x24];        // +0x14 (Matrix3)
};
extern "C" u32 g_167bb88;                               // 0x0167bb88
extern "C" DefaultTransform_s00b0_24a0 g_167bb50;       // 0x0167bb50
// @ 0x00b024a0
void* GetDefaultValue_A(void)
{
    if ((g_167bb88 & 1) == 0) {
        g_167bb88 |= 1;
        g_167bb50.mPosition[0] = g_167af5c_s00b0_1690;
        g_167bb50.mFlags = 0;
        g_167bb50.mFlags2 = 0;
        g_167bb50.mPosition[1] = g_167af60_s00b0_1690;
        g_167bb50.mPosition[2] = g_167af64_s00b0_1690;
        g_167bb50.mScale = 1.0f;
        M3(g_167bb50.mRotation)->Assign(&g_167b554);
    }
    return &g_167bb50;
}

// @ 0x00b02520
void FUN_00b02520(void* obj)
{
    void* t = (*(void*(*)(void*))(*(void**)((char*)obj + 0x20)))(obj);
    void* d = GetDefaultValue_A();
    ((CTransformAssignOps*)t)->Assign(d);
}

// @ 0x00b02750
u8* FUN_00b02750(u8* first, u8* last, const u32* key)
{
    i32 n = (i32)(last - first) / 0x19a8;
    i32 half = 0;
    if (n > 0) {
        do {
            half = n >> 1;
            u8* mid = first + half * 0x19a8;
            if (*(u32*)mid < *key) {
                first = mid + 0x19a8;
                half = n + (-1 - half);
            }
            n = half;
        } while (half > 0);
    }
    return first;
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

// @ 0x00b02b90
void cFruitGroupSlots::GetFruitPos(float* out, int idx)
{
    void* r1 = FUN_00b3d420(&this->p5c);
    void* r2 = ((Op_s00b0_2830*)r1)->M90410();        // GetSpeciesFromID
    cModelWorld* mw = (cModelWorld*)((Op_s00b0_2830*)r2)->M2830();  // GetModelWorld
    TmpXform tmp;                          // local transform snapshot
    float x = f10;
    float y = f14;
    float z = f18;
    tmp.a = mW0;
    tmp.b = mW1;
    tmp.x = x;
    tmp.y = y;
    tmp.z = z;
    tmp.w = f1c;
    ((Op_s00b0_2830*)&tmp.m00)->M1cb40(this->mTransform);
    void* dst = (void*)((char*)mw->mpPieces + idx * 0x38);
    ((Op_s00b0_2830*)&tmp)->M0ccb0(dst);
    out[0] = tmp.x; out[1] = tmp.y; out[2] = tmp.z;
}

// @ 0x00b02c40
cFruitView* cFruitView::ScopedDtor(uint8 del)
{
    cFruitView* s = this;
    s->vtbl = (void*)0x0145c6d0;
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

// @ 0x00b02ca0
void* __fastcall cFruitGroup_Ctor(cFruitGroup* self)
{
    ((Op_s00b0_2830*)self)->M18660();
    ((Op_s00b0_2830*)&self->targetVtbl)->M03d0();
    self->targetVtbl = gVtblFruitGroup;
    self->vtbl00 = gVtblFruitGroup2;
    self->vtbl04 = gVtblFruitGroup3;
    self->m4c = -1;
    self->m50 = 0x3a8be428;
    self->m54 = 0;
    self->m58 = 0;
    self->f5c = g_zero3a[0];
    self->f60 = g_zero3a[1];
    self->f64 = g_zero3a[2];
    self->f68 = g_HK_REAL_ONE;
    ((Op_s00b0_2830*)self->mRot)->M1cb40(g_matrixIdentity);
    self->m90 = 0;
    self->m94 = 0;
    self->m98 = 0;
    self->m9c = 0;
    self->ma0 = 0;
    char* p = (char*)&self->mbc;
    self->ma4 = p;
    self->ma8 = p;
    self->mb8 = 0;
    p += 0xe0;
    self->mac = p;
    p = (char*)&self->m1b4;
    self->m19c = p;
    self->m1a0 = p;
    self->m1b0 = 0;
    p += 0x10;
    self->m1a4 = p;
    self->m1c4 = 0;
    self->m1c8 = 0;
    self->m1cc = 0;
    self->m1d0 = 0;
    return self;
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

// @ 0x00b02fa0
void __fastcall FUN_00b02fa0(cFruitGroup* self)
{
    void* mgr = (void*)FUN_00b3d3b0();       // 0x0167eb10 singleton
    cModelHolder* ch = (cModelHolder*)((Op_s00b0_2830*)mgr)->M2a690(self->m50, self->m4c, self->m54);
    int owner = (ch != 0) ? (int)ch->mpChild : 0;
    if (owner == 0) {
        if ((self->m90 & 1) == 0)
            return;
        self->m90 &= 0xfffffffe;
    } else {
        self->m90 |= 1;
    }
    cSpeciesProfile* prof = (cSpeciesProfile*)((Op_s00b0_2830*)FUN_00401090())->Mdf440(&self->m94);
    if (prof == 0)
        return;
    if ((int)((Op_s00b0_2830*)prof)->Md9070() == 0)
        return;
    uint32 n = (uint32)((Op_s00b0_2830*)prof)->Md9070();
    if (n == 0)
        return;
    uint32 idx = 0;
    uint32 off = 0;
    do {
        cSPTransform_s00b0_2830* dst = (cSPTransform_s00b0_2830*)((char*)self->ma4 + off);
        if (self->m1c8 != 0) {
            cSPTransform_s00b0_2830 tf;
            tf.flags = 0;
            tf.modCount = 0;
            tf.tx = g_zero3a[0];
            tf.ty = g_zero3a[1];
            tf.tz = g_zero3a[2];
            tf.scale = g_HK_REAL_ONE;
            ((Op_s00b0_2830*)tf.rot)->M1cb40(g_matrixIdentity);
            if (owner == 0) {
                ((Op_s00b0_2830*)&tf)->M537dc0((char*)prof->mpTransforms + off);
                tf.flags |= 4;
                ++tf.modCount;
            } else {
                cCreature* crea = (cCreature*)((Op_s00b0_2830*)(uintptr_t)owner)->Mc3e790();
                if (crea != 0 && crea->mpModel != 0) {
                    cCreatureModel* model = crea->mpModel;
                    int* pp = (int*)((Op_s00b0_2830*)prof)->Md9010(crea);
                    uint32 ei = *(uint32*)(*pp + idx * 4);
                    if ((uint32)(((char*)model->mpElemEnd - (char*)model->mpElemBegin) / 700) <= ei)
                        ei = 0;
                    cPieceElem* elem = &model->mpElemBegin[ei];
                    float mat[9];
                    FUN_0059c190(mat, elem->quat);
                    float inv = g_HK_REAL_ONE / model->scale;
                    tf.tx = elem->x * inv;
                    tf.ty = elem->y * inv;
                    tf.tz = elem->z * inv;
                    for (int k = 0; k < 9; ++k)
                        tf.rot[k] = mat[k];
                    tf.flags |= 6;
                    tf.modCount += 2;
                }
            }
            if (tf.tx != g_zero3a[0] || tf.ty != g_zero3a[1] || tf.tz != g_zero3a[2]) {
                cFruitTreeRoot* tree = (cFruitTreeRoot*)FUN_00b3d440();
                uint32 found[2];
                ((Op_s00b0_2830*)&tree->mHeader)->M5c780(found, &self->m1c8);
                cFruitTreeNode* node = (cFruitTreeNode*)found[0];
                if ((char*)node != (char*)&tree->mEndNode && node->mpSlots != 0) {
                    uint32 k2 = *(uint32*)((char*)self->m19c + idx * 4);
                    if (k2 < node->key) {
                        char tmp[0x38];
                        FUN_006271a0(tmp, &tf, &self->m58);
                        ((Op_s00b0_2830*)&node->mpSlots[k2])->M537dc0(tmp);
                    }
                }
                ((Op_s00b0_2830*)dst)->M537dc0(&tf);
            }
        }
        ++idx;
        off += 0x38;
    } while (idx < n);
}

// @ 0x00b03320
uint32 cFruitGroupOps::FindNth(uint32 a, uint32 b, uint32 c) // a=m58, b=m50, c=m54
{
    uint32 key[2];
    key[0] = b;          // +0: m50 (species key)
    key[1] = a;          // +4: m58
    uint32 out[2];
    mLookup.Find(out, key);
    uint32 it = out[0];
    uint32 end = out[1];
    uint32 n = 0;
    while (it != end) {
        it = (uint32)FUN_00921580((void*)it);
        ++n;
    }
    if (c < n) {
        for (uint32 k = 0; k < c; ++k)
            out[0] = (uint32)FUN_00921580((void*)out[0]);
        return ((cFruitTreeNode*)(uintptr_t)out[0])->key;
    }
    return 0;
}

// @ 0x00b033b0
void cFruitGroup::FillSlots(cFruitGroup* group)
{
    cFruitGroup* node = (cFruitGroup*)(uintptr_t)((cFruitGroupOps*)this)->FindNth(
        group->m58, group->m50, group->m54);
    if (node == 0)
        return;
    // popcount of the high dword of the 64-bit "used slot" mask at +0x48/+0x4c
    uint32 hi = FUN_011e08d0(group->m4c, group->m48, 0x20);
    uint32 v = hi - (hi >> 1 & 0x55555555);
    v = (v >> 2 & 0x33333333) + (v & 0x33333333);
    uint32 count = ((v >> 4) + v & 0x0f0f0f0f) * 0x01010101 >> 24;
    for (uint32 i = 0; i < count; ++i) {
        uint64 mask;
        FUN_011e06e0((uint32*)&mask, (int)i);  // mask = 1 << i
        uint32 ml = (uint32)mask;
        uint32 mh = (uint32)(mask >> 32);
        if ((ml & group->m48) != 0 || (mh & group->m4c) != 0)
            continue;
        group->m48 |= ml;
        group->m4c |= mh;
        uint32 key = (uint32)(uintptr_t)node->m1c8;                       // find key
        uint32 v6  = *(uint32*)((char*)node->m19c + i * 4);               // slot key
        cFruitTreeRoot* r = (cFruitTreeRoot*)FUN_00b3d440();
        if (key != 0 && v6 != 0xffffffff) {
            uint32 found[2];
            ((Op_s00b0_2830*)&r->mHeader)->M5c780(found, &key);
            cFruitTreeNode* fn = (cFruitTreeNode*)found[0];
            if ((char*)fn != (char*)&r->mEndNode && fn->mpSlots != 0 && v6 < fn->key)
                FUN_00a887b0(v6, g_HK_REAL_ONE);
        }
    }
}

// @ 0x00b034f0
uint8 __stdcall FUN_00b034f0(uint32* out, uint32 key0, uint32 key1, uint32 count, void* owner)
{
    uint32 pair[2];
    ((RbtLookup*)owner)->Find(pair, &key0);
    uint32 it = pair[0];
    uint32 end = pair[1];
    out[0] = it;
    out[1] = end;
    uint32 n = 0;
    if (it != end) {
        do {
            it = (uint32)FUN_00921580((void*)it);
            ++n;
        } while (it != end);
        if (n != 0 && n == count)
            return 1;
    }
    return 0;
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

// @ 0x00b035b0
void __cdecl FUN_00b035b0(void* ar, cSaveTreeHdr* hdr)
{
    uint32 key = hdr->firstKey;
    void* r = ((void*(__thiscall*)(void*))*(void**)(*(int*)ar + 0x20))(ar);
    void* st = ((void*(__thiscall*)(void*))*(void**)(*(int*)r + 0x18))(r);
    FUN_0093aa70(st, &key, 1, 0);
    cSaveNode* it  = (cSaveNode*)hdr->mpFirst;
    cSaveNode* end = (cSaveNode*)((char*)hdr + 4);
    for (; it != end; it = (cSaveNode*)FUN_00921580(it)) {
        r = ((void*(__thiscall*)(void*))*(void**)(*(int*)ar + 0x20))(ar);
        uint32 v0 = it->key0;
        uint32 v1 = it->key1;
        st = ((void*(__thiscall*)(void*))*(void**)(*(int*)r + 0x18))(r);
        FUN_0093ab10(st, &v0, 1, 0);
        ((void(__thiscall*)(void*))*(void**)(*(int*)ar + 0x1c))(ar);
        void* p = it->mpObj;
        uint32 res = 0;
        if (p != 0)
            res = (uint32)((void*(__thiscall*)(void*, uint32))*(void**)(*(int*)p + 0xc))(p, 0x179c807);
        ((void(__thiscall*)(void*, uint32))*(void**)(*(int*)ar + 0x2c))(ar, res);
        ((void(__thiscall*)(void*))*(void**)(*(int*)ar + 0x1c))(ar);
    }
    ((void(__thiscall*)(void*))*(void**)(*(int*)ar + 0x1c))(ar);
}

// @ 0x00b03680
cTreeData::cTreeData(void* src)
{
    cTreeData* p = (cTreeData*)src;
    *(void* volatile*)&this->vtbl1 = gVtblContentValidationSummarizer;  // base-subobject vtable store kept by retail
    this->m08 = 0;
    this->vtbl0 = gVtblTreeData;
    this->vtbl1 = gVtblTreeData2;
    this->m0c = p->m0c;
    this->m0e = p->m0e;
    this->tx = p->tx;
    this->ty = p->ty;
    this->tz = p->tz;
    this->scale = p->scale;
    ((Op_s00b0_2830*)this->rot)->M1cb40(p->rot);
    this->m48 = p->m48;
    this->m4c = p->m4c;
    this->m50 = p->m50;
    this->m54 = p->m54;
    this->m58 = p->m58;
    this->m5c = p->m5c;
    this->m60 = p->m60;
    this->m64 = p->m64;
    this->mp68 = p->mp68;
    if (this->mp68 != 0)
        ((void(__thiscall*)(void*))(*(void***)this->mp68)[0])(this->mp68);
    this->f6c = p->f6c;
    this->f70 = p->f70;
    this->f74 = p->f74;
    this->m78 = p->m78;
    this->m7c = p->m7c;
}

// @ 0x00b03740
cTreeData& cTreeData::operator=(cTreeData const& rhs)
{
    ((Op_s00b0_2830*)(void*)&this->m0c)->M537dc0(&((cTreeData&)rhs).m0c);
    this->m48 = rhs.m48;
    this->m4c = rhs.m4c;
    this->m50 = rhs.m50;
    this->m54 = rhs.m54;
    this->m58 = rhs.m58;
    this->m5c = rhs.m5c;
    this->m60 = rhs.m60;
    this->m64 = rhs.m64;
    void* np = rhs.mp68;
    if (np != this->mp68) {
        void* op68 = this->mp68;
        if (np != 0)
            ((void(__thiscall*)(void*))(*(void***)np)[0])(np);
        this->mp68 = np;
        if (op68 != 0)
            ((void(__thiscall*)(void*))((*(void***)op68)[1]))(op68);
    }
    this->f6c = rhs.f6c;
    this->f70 = rhs.f70;
    this->f74 = rhs.f74;
    this->m78 = rhs.m78;
    this->m7c = rhs.m7c;
    return *this;
}

struct S_00b037e0 { char d[0x80]; };
struct R_00b037e0 { S_00b037e0* p; };
struct I_00b037e0 {
    S_00b037e0* p;
    S_00b037e0& operator*() const { return *p; }
    I_00b037e0& operator++() { ++p; return *this; }
    bool operator!=(const I_00b037e0& o) const { return p != o.p; }
};

// @ 0x00b037e0
R_00b037e0* __cdecl FUN_00b037e0(R_00b037e0* out, I_00b037e0 begin, I_00b037e0 end, S_00b037e0* value)
{    out->p = value;
    for (; begin != end; ++begin, ++out->p) {
        if (out->p != 0)
            ((cTreeData*)out->p)->cTreeData::cTreeData((void*)&*begin);
    }
    return out;
}

// @ 0x00b03820
PoolNode* PoolOwner::AllocNode(const uint32* src)
{
    PoolNode* node = freeList;
    if (node != 0) {
        freeList = node->next;
    } else {
        node = (PoolNode*)FUN_00f473a0(chunkSize, g_allocName_13ebb38, 0, 0,
                                       g_allocFile_13f09b4, 0xd1);
    }
    float* dst = &node->f10;
    if (dst != 0) {
        uint32* d = (uint32*)dst;
        const uint32* s = src;
        d[0] = s[0];
        d[1] = s[1];
        void* r = (void*)s[2];
        d[2] = (uint32)r;
        if (r != 0)
            RefObjCall0(r);
    }
    return node;
}

// @ 0x00b03880
PoolNode* PoolOwner::AllocNodeTiny(const uint32* src)
{
    PoolNode* node = freeList;
    if (node != 0) {
        freeList = node->next;
    } else {
        node = (PoolNode*)FUN_00f473a0(chunkSize, g_allocName_13ebb38, 0, 0,
                                       g_allocFile_13f09b4, 0xd1);
    }
    uint32* d = (uint32*)&node->f10;
    if (d != 0) {
        d[0] = src[0];
        ((TinyCopyT*)((char*)d + 8))->Copy(&src[2]);
    }
    return node;
}

// @ 0x00b038e0
void __cdecl sort_partition_a(void** lo, void** hi, void* pivot, const float* pos)
{
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2];
    void** left = lo;
    void*  pivotNode = pivot;
    for (;;) {
        void* n;
        do {
            n = *left;
            float dx = px - *(float*)((char*)pivotNode + 0x5c);
            float dy = py - *(float*)((char*)pivotNode + 0x60);
            float dz = pz - *(float*)((char*)pivotNode + 0x64);
            float dp = dz * dz + dy * dy + dx * dx;
            float ex = px - *(float*)((char*)n + 0x5c);
            float ey = py - *(float*)((char*)n + 0x60);
            float ez = pz - *(float*)((char*)n + 0x64);
            float dn = ez * ez + ey * ey + ex * ex;
            if (dn <= dp)
                break;
            ++left;
        } while (true);

        void** right = hi;
        for (;;) {
            float ex = px - *(float*)((char*)pivotNode + 0x5c);
            float ey = py - *(float*)((char*)pivotNode + 0x60);
            float ez = pz - *(float*)((char*)pivotNode + 0x64);
            float dp = ez * ez + ey * ey + ex * ex;
            (void)dp;
            --right;
            void* m = *right;
            float gx = px - *(float*)((char*)m + 0x5c);
            float gy = py - *(float*)((char*)m + 0x60);
            float gz = pz - *(float*)((char*)m + 0x64);
            float dm = gz * gz + gy * gy + gx * gx;
            if (dm > dp)
                break;
        }
        if (left >= right)
            return;
        void* t = *left;
        *left = *right;
        *right = t;
        ++left;
    }
}

// @ 0x00b03a20
void __cdecl sort_partition_b(void** lo, void** hi, void* pivot, float px, float py, float pz)
{
    void** left = lo;
    void*  pivotNode = pivot;
    for (;;) {
        void* n;
        do {
            n = *left;
            float dz = pz - *(float*)((char*)pivotNode + 0x18);
            float dy = py - *(float*)((char*)pivotNode + 0x14);
            float dx = px - *(float*)((char*)pivotNode + 0x10);
            float dp = dz * dz + dy * dy + dx * dx;
            float ex = px - *(float*)((char*)n + 0x10);
            float ey = py - *(float*)((char*)n + 0x14);
            float ez = pz - *(float*)((char*)n + 0x18);
            float dn = ez * ez + ey * ey + ex * ex;
            if (dn <= dp)
                break;
            ++left;
        } while (true);

        void** right = hi;
        for (;;) {
            float ex = px - *(float*)((char*)pivotNode + 0x10);
            float ey = py - *(float*)((char*)pivotNode + 0x14);
            float ez = pz - *(float*)((char*)pivotNode + 0x18);
            float dp = ez * ez + ey * ey + ex * ex;
            (void)dp;
            --right;
            void* m = *right;
            float gx = px - *(float*)((char*)m + 0x10);
            float gy = py - *(float*)((char*)m + 0x14);
            float gz = pz - *(float*)((char*)m + 0x18);
            float dm = gz * gz + gy * gy + gx * gx;
            if (dm > dp)
                break;
        }
        if (left >= right)
            return;
        void* t = *left;
        *left = *right;
        *right = t;
        ++left;
    }
}

// @ 0x00b03b50
void __cdecl sort_partition_c(void** lo, void** hi, const float* pivot, float px, float py, float pz)
{
    float dx0 = px - pivot[0];
    float dy0 = py - pivot[1];
    float dz0 = pz - pivot[2];
    void** left = lo;
    for (;;) {
        void* n;
        do {
            n = *left;
            float ex = px - *(float*)((char*)n + 0);
            float ey = py - *(float*)((char*)n + 4);
            float ez = pz - *(float*)((char*)n + 8);
            float dn = ez * ez + ey * ey + ex * ex;
            float dp = dz0 * dz0 + dy0 * dy0 + dx0 * dx0;
            if (dn <= dp)
                break;
            ++left;
        } while (true);

        void** right = hi;
        for (;;) {
            --right;
            void* m = *right;
            float gx = px - *(float*)((char*)m + 0);
            float gy = py - *(float*)((char*)m + 4);
            float gz = pz - *(float*)((char*)m + 8);
            float dm = gz * gz + gy * gy + gx * gx;
            float dp = dz0 * dz0 + dy0 * dy0 + dx0 * dx0;
            if (dm > dp)
                break;
        }
        if (left >= right)
            return;
        void* t = *left;
        *left = *right;
        *right = t;
        ++left;
    }
}

// @ 0x00b03ca0
BigElem80* __cdecl construct_range_big(BigElem80* first, BigElem80* last, BigElem80* dest)
{
    while (first != last) {
        if (dest != 0)
            dest->CopyConstructFrom(*first);
        ++first;
        ++dest;
    }
    return dest;
}

// @ 0x00b03d70
void __cdecl make_heap_range(void* first, void* last, HeapPos pos)
{
    int n = (int)(((char*)last - (char*)first) >> 2);
    if (n < 2)
        return;
    int i = ((n - 2) >> 1) + 1;
    do {
        --i;
        FUN_00b02930(first, i, n, i, *(void**)((char*)first + i * 4), pos);
    } while (i != 0);
}

// @ 0x00b03dd0
void __cdecl sort_heap_range(void* first, void* last, float px, float py, float pz)
{
    int n = (int)(((char*)last - (char*)first) >> 2);
    while (n > 1) {
        void** e = (void**)((char*)last - 4);
        void*  v = *e;
        *e = *(void**)first;
        FUN_00b02930(first, 0, n - 1, 0, v, px, py, pz);
        --e;
        last = e;
        n = (int)(((char*)last - (char*)first) >> 2);
    }
}

// @ 0x00b03e40
void __cdecl make_heap_range2(void* first, void* last, HeapPos pos)
{
    int n = (int)(((char*)last - (char*)first) >> 2);
    if (n < 2)
        return;
    int i = ((n - 2) >> 1) + 1;
    do {
        --i;
        FUN_00b02a40(first, i, n, i, *(void**)((char*)first + i * 4), pos);
    } while (i != 0);
}

// @ 0x00b03ea0
void __cdecl sort_heap_range2(void* first, void* last, float px, float py, float pz)
{
    int n = (int)(((char*)last - (char*)first) >> 2);
    while (n > 1) {
        void** e = (void**)((char*)last - 4);
        void*  v = *e;
        *e = *(void**)first;
        FUN_00b02a40(first, 0, n - 1, 0, v, px, py, pz);
        --e;
        last = e;
        n = (int)(((char*)last - (char*)first) >> 2);
    }
}

// @ 0x00b03f10
BigElem80* __cdecl copy_range_big(BigElem80* first, BigElem80* last, BigElem80* dest)
{
    while (first != last) {
        dest->CopyAssignFrom(*first);
        ++first;
        ++dest;
    }
    return dest;
}

// @ 0x00b03f50
void* __cdecl destroy_range_big2(void* first, void* last, void* cursor)
{
    if (last != first) {
        do {
            last = (char*)last - 0x80;
            cursor = (char*)cursor - 0x80;
            ((BigElemD*)cursor)->Dtor2(last);
        } while (last != first);
    } else {
        cursor = cursor;
    }
    return cursor;
}

// @ 0x00b03f90
void* RedBlackTree::Find(uint32* key)
{
    void* last = end;
    void* r = FUN_00b02750(begin, last, key, flag19a818);
    if (r == last || *key < *(uint32*)r || r == (char*)r + 0x19a8)
        r = last;
    return r;
}

// @ 0x00b03fd0
void __cdecl walk_tree_dump(void* tree, const char* label)
{
    void* first = *(void**)tree;
    int   ok    = 1;
    void* guard = 0;
    (void)guard;
    if (first != *(void**)((char*)tree + 4)) {
        FUN_00ac8050_ish(tree, label, 0);
    }
    (void)ok;
}

// @ 0x00b04120
void __cdecl walk_tree_dump2(void* tree, const char* label)
{
    void* first = *(void**)tree;
    int   ok    = 1;
    if (first != *(void**)((char*)tree + 4)) {
        FUN_00ac8050_ish(tree, label, 0);
    }
    (void)ok;
}

// @ 0x00b04270
void __cdecl pool_owner_ctor(void* self)
{
    uint32* p = (uint32*)self;
    p[0x20 / 4] = 0;
    p[0x24 / 4] = 0;
    p[0x28 / 4] = 0;
    p[0x2c / 4] = 0;
    p[0x30 / 4] = 0;
    p[0x34 / 4] = 0;
    p[0x38 / 4] = 0;
    p[0x3c / 4] = 0;
    p[0x40 / 4] = 0;
    p[0x58 / 4] = 0;
    *(void**)((char*)self + 0x44) = (char*)self + 0x5c;
    *(void**)((char*)self + 0x48) = (char*)self + 0x5c;
    *(void**)((char*)self + 0x4c) = (char*)self + 0x5c + 0x40;
    p[0xb0 / 4] = 0;
    *(void**)((char*)self + 0x9c) = (char*)self + 0xb4;
    *(void**)((char*)self + 0xa0) = (char*)self + 0xb4;
    *(void**)((char*)self + 0xa4) = (char*)self + 0xb4 + 0x40;
    p[0x108 / 4] = 0;
    *(void**)((char*)self + 0xf4) = (char*)self + 0x10c;
    *(void**)((char*)self + 0xf8) = (char*)self + 0x10c;
    *(void**)((char*)self + 0xfc) = (char*)self + 0x10c + 0x40;
    p[0x16c / 4] = 0;
    *(void**)((char*)self + 0x158) = (char*)self + 0x170;
    *(void**)((char*)self + 0x15c) = (char*)self + 0x170;
    *(void**)((char*)self + 0x160) = (char*)self + 0x170 + 0x800;
    *(void**)((char*)self + 0x970) = (char*)self + 0x988;
    *(void**)((char*)self + 0x974) = (char*)self + 0x988;
    p[0x984 / 4] = 0;
    *(void**)((char*)self + 0x978) = (char*)self + 0x988 + 0x800;
    p[0x119c / 4] = 0;
    *(void**)((char*)self + 0x1188) = (char*)self + 0x11a0;
    *(void**)((char*)self + 0x118c) = (char*)self + 0x11a0;
    *(void**)((char*)self + 0x1190) = (char*)self + 0x11a0 + 0x800;
}

// @ 0x00b04350
void PoolOwner::release_node_chain(void* node)
{
    while (node != 0) {
        release_node_chain(*(void**)node);
        void* next = *(void**)((char*)node + 4);
        void* ref  = *(void**)((char*)node + 0x18);
        if (ref != 0)
            RefObjCall1(ref);
        if (node >= *(void**)((char*)this + 0x20) && node < *(void**)((char*)this + 0x24)) {
            *(void**)node = *(void**)((char*)this + 0x18);
            *(void**)((char*)this + 0x18) = node;
        } else {
            FUN_00f47380(node);
        }
        node = next;
    }
}

// @ 0x00b043b0
void PoolOwner::erase_tree_node(void** out, void* node)
{
    --*(int*)((char*)this + 0x14);
    void* next = FUN_00921580(node);
    FUN_00921880(node, (char*)this + 4);
    if (node >= *(void**)((char*)this + 0x20) && node < *(void**)((char*)this + 0x24)) {
        *(void**)node = *(void**)((char*)this + 0x18);
        *(void**)((char*)this + 0x18) = node;
        *out = next;
        return;
    }
    FUN_00f47380(node);
    *out = next;
}

// 0x00b04420 (byte-exact lifted version: match/slices/s00b04420/s00b04420.cpp)
void __cdecl node_free_walk(void* self, void* node)
{
    while (node != 0) {
        node_free_walk(self, *(void**)node);
        void* next = *(void**)((char*)node + 4);
        *(uint32*)((char*)node + 0x18) = 0;
        *(uint32*)((char*)node + 0x20) = 0;
        *(uint32*)((char*)node + 0x24) = 0;
        void* a = *(void**)((char*)node + 0x28);
        if (a != 0) {
            *(uint32*)((char*)node + 0x28) = 0;
            void* vt = *(void**)a;
            (*(void(__thiscall**)(void*))(*(uint32*)vt + 4))(a);
        }
        void* b = *(void**)((char*)node + 0x2c);
        if (b != 0) {
            *(uint32*)((char*)node + 0x2c) = 0;
            void* vt = *(void**)b;
            (*(void(__thiscall**)(void*))(*(uint32*)vt + 0x38))(b);
        }
        *(uint32*)((char*)node + 0x30) = 0;
        void* c = *(void**)((char*)node + 0x2c);
        if (c != 0) {
            void* vt = *(void**)c;
            (*(void(__thiscall**)(void*))(*(uint32*)vt + 0x38))(c);
        }
        void* d = *(void**)((char*)node + 0x28);
        if (d != 0) {
            void* vt = *(void**)d;
            (*(void(__thiscall**)(void*))(*(uint32*)vt + 4))(d);
        }
        if (node >= *(void**)((char*)self + 0x20) && node < *(void**)((char*)self + 0x24)) {
            *(void**)node = *(void**)((char*)self + 0x18);
            *(void**)((char*)self + 0x18) = node;
        } else {
            FUN_00f47380(node);
        }
        node = next;
    }
}

// @ 0x00b04520
void* PoolOwner::rbcontainer_copy(void* src)
{
    *(void**)this = (void*)0x01411b88;
    *(uint8*)((char*)this + 4) = *(uint8*)((char*)src + 4);
    FUN_00ac20d0((int)((*(char**)((char*)src + 0xc) - *(char**)((char*)src + 8)) >> 3),
                 (char*)src + 0x14);
    FUN_0076ffd0(*(void**)((char*)src + 8), *(void**)((char*)src + 0xc),
                 *(void**)((char*)this + 8), src);
    *(void**)((char*)this + 0x0c) = src;
    *(uint32*)((char*)this + 0x1c) = *(uint32*)((char*)src + 0x1c);
    *(uint32*)((char*)this + 0x20) = *(uint32*)((char*)src + 0x20);
    return this;
}

// @ 0x00b04590
void __cdecl sort_by_distance(void** first, void** last, const float* pos)
{
    FUN_00b03ce0(first, last, pos);
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2];
    for (void** it = last; it < first; ++it) {
        void*  n = *it;
        void*  m = *first;
        float az = pz - *(float*)((char*)n + 0x64);
        float bz = pz - *(float*)((char*)m + 0x64);
        float ax = px - *(float*)((char*)n + 0x5c);
        float bx = px - *(float*)((char*)m + 0x5c);
        float ay = py - *(float*)((char*)n + 0x60);
        float by = py - *(float*)((char*)m + 0x60);
        if (az * az + ax * ax + ay * ay < bz * bz + by * by + bx * bx) {
            *it = m;
            FUN_00b02830(first, 0, (int)((char*)last - (char*)first) >> 2, 0, n, pos);
        }
    }
    FUN_00b03d20(first, last, pos);
}

// @ 0x00b04670
void __cdecl sort_and_visit(void** first, void** last, const float* pos)
{
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2];
    make_heap_range(first, last, HeapPos(px, py, pz));
    void** it = first;
    void** hi = last;
    while (it < hi) {
        void* n = *it;
        (void)n;
        ++it;
    }
    FUN_00b03d20(first, last, pos);
}

// @ 0x00b047b0
void* FUN_00b047b0(void** param_1, void** param_2, void** param_3, float px, float py, float pz)
{
    make_heap_range2(param_1, param_2, HeapPos(px, py, pz));
    void** it = param_2;
    while (it < param_3) {
        float* cur = (float*)*it;
        float* top = (float*)*param_1;
        float dcur = (pz - cur[2]) * (pz - cur[2])
                   + (px - cur[0]) * (px - cur[0])
                   + (py - cur[1]) * (py - cur[1]);
        float dtop = (pz - top[2]) * (pz - top[2])
                   + (py - top[1]) * (py - top[1])
                   + (px - top[0]) * (px - top[0]);
        if (dtop < dcur) {
            *it = top;
            heap_adjust(param_1, 0, (int)((char*)param_2 - (char*)param_1) >> 2,
                        0, cur, px, py, pz);
        }
        ++it;
    }
    sort_heap_range2(param_1, param_2, px, py, pz);
    return param_1;
}

// @ 0x00b048f0
int FUN_00b048f0(int param_1, int param_2, int param_3)
{
    if (param_1 != param_2) {
        Leaf* leaf = (Leaf*)param_1;
        do {
            void** end;
            void** it;

            end = leaf->mVec_1190.mpEnd_04;
            for (it = leaf->mVec_1190.mpBegin_00; it < end; it += 0x20)
                (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
            {
                void* a = leaf->mVec_1190.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_978.mpEnd_04;
            for (it = leaf->mVec_978.mpBegin_00; it < end; it += 0x20)
                (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
            {
                void* a = leaf->mVec_978.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_160.mpEnd_04;
            for (it = leaf->mVec_160.mpBegin_00; it < end; it += 0x20)
                (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
            {
                void* a = leaf->mVec_160.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_0fc.mpEnd_04;
            for (it = leaf->mVec_0fc.mpBegin_00; it < end; ++it) {
                void* e = *it;
                if (e)
                    (*(void(__thiscall**)(void*))e)(e);
            }
            {
                void* a = leaf->mVec_0fc.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_0a4.mpEnd_04;
            for (it = leaf->mVec_0a4.mpBegin_00; it < end; ++it) {
                void* e = *it;
                if (e)
                    (*(void(__thiscall**)(void*))e)(e);
            }
            {
                void* a = leaf->mVec_0a4.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            end = leaf->mVec_04c.mpEnd_04;
            for (it = leaf->mVec_04c.mpBegin_00; it < end; ++it) {
                void* e = *it;
                if (e)
                    (*(void(__thiscall**)(void*))e)(e);
            }
            {
                void* a = leaf->mVec_04c.mpBegin_00;
                if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                    operator_delete(a);
            }

            param_3 += 0x19a8;
            param_1 += 0x19a8;
            ++leaf;
        } while (param_1 != param_2);
    }
    return param_3;
}

// @ 0x00b04aa0
void SimObj::fillSlot(SimEnt* ent)
{
    unsigned char flag = (unsigned char)(ent->mFlags_30 & 1);
    uint   key  = ent->mId_20;
    if (ent->mpSub_08 == 0 && flag == 0)
        return;

    uint* tail = (uint*)this->mpTreeHead_1e5f4;
    uint  local = key;
    uint* found = (uint*)rbtree_find(this->mpTreeRoot_1e5f0, tail, &local,
                                     this->mbFlag_1b8e08);
    uint* sel = tail;
    if (found != tail && key >= *found && found != found + 0x66a)
        sel = found;
    if (sel == tail)
        return;

    FUN_00b3d3b0(ent);
    void* p = FUN_00b2b1e0(ent);
    if (!p)
        return;
    FUN_00b3d420(p);
    void* sp = GetSpeciesFromID(p, 0);
    if (!sp)
        return;
    uint id = FUN_00b8f860(sp);
    uint* slot;
    if (id == 0x29c388a)
        slot = &sel[0xd];
    else if (id == 0x3a8be428)
        slot = &sel[0xa];
    else if (id == 0x6d60a1cc)
        slot = &sel[0x10];
    else
        return;
    if (!slot)
        return;
    if (flag) {
        slot[0] = 0;
        slot[1] = 0;
        slot[2] = 0;
        return;
    }
    void* src = (*(void*(**)(void*))(*(int*)sp + 0x18))((void*)sp);
    slot[0] = ((uint*)src)[0];
    slot[1] = ((uint*)src)[1];
    slot[2] = ((uint*)src)[2];
}

// @ 0x00b04ba0
void* SimObj::findSlot(uint id, int species)
{
    uint8_t flag = this->mbFlag_1b8e08;
    void*   root = this->mpTreeRoot_1e5f0;
    void*   head = this->mpTreeHead_1e5f4;
    uint* n = (uint*)rbtree_find(root, head, &id, flag);
    if (n == (uint*)head || id < *n || n == n + 0x66a)
        n = (uint*)head;
    if (n == (uint*)head)
        return 0;
    if (species == 0x29c388a)
        return n + 0x29;
    if (species == 0x3a8be428)
        return n + 0x13;
    if (species == 0x6d60a1cc)
        return n + 0x3f;
    return 0;
}

// @ 0x00b04c20
void* SimObj::slotAt(uint id, int species, uint idx)
{
    int* v = (int*)this->findSlot(id, species);
    if (v != 0 && idx < (uint)((v[1] - v[0]) >> 2))
        return *(void**)(v[0] + idx * 4);
    return 0;
}

// @ 0x00b04c50
void VVec::reserve(uint n)
{
    if (n > (uint)(((char*)this->mpCap_08 - (char*)this->mpBegin_00) / 0x38)) {
        void* mem;
        if (n != 0)
            mem = EAAllocate(n * 0x38, g_allocName_13ebb38, 0, 0,
                             g_allocFile_13f09b4, 0xd1);
        else
            mem = 0;
        vect_copy(this->mpBegin_00, this->mpEnd_04, mem);
        if (this->mpBegin_00) {
            int* blk = (int*)((char*)this->mpBegin_00 - 4);
            if (*blk != 0)
                operator_delete(this->mpBegin_00);
        }
        int oldn = (int)(((char*)this->mpEnd_04 - (char*)this->mpBegin_00) / 0x38);
        this->mpBegin_00 = (int*)mem;
        this->mpEnd_04   = (int*)((char*)mem + oldn * 0x38);
        this->mpCap_08   = (int*)((char*)mem + n * 0x38);
    }
}

// @ 0x00b04e00
void __stdcall FUN_00b04e00(void* unused, int* vec, void* param_2)
{
    void* first = (void*)vec[0];
    void* last  = (void*)vec[1];
    memcpy_(first, last, (uint)((char*)last - (char*)last));
    vec[1] += -((int)((char*)last - (char*)first) >> 2) * 4;

    uint count = 0;
    void* s = (*(void*(**)(void*))(*(int*)param_2 + 0x20))(param_2);
    void* s2 = (*(void*(**)(void*))(*(int*)s + 0x18))(s);
    ReadInt32(s2, &count, 1, 0);
    reserve_tex(vec, count);

    uint i = 0;
    while (i < count) {
        void* t = (*(void*(**)(void*))(*(int*)param_2 + 0x20))(param_2);
        void* t2 = (*(void*(**)(void*))(*(int*)t + 0x18))(t);
        uint v;
        ReadInt32(t2, &v, 1, 0);
        int* slot = (int*)vec[1];
        if (slot < (int*)vec[2]) {
            vec[1] = (int)(slot + 1);
            if (slot)
                *slot = (int)v;
        } else {
            DoInsertValueI(slot, (uint*)&slot, &v);
        }
        ++i;
    }
    (*(void(__thiscall**)(void*))(*(int*)param_2 + 0x1c))(param_2);
}

// @ 0x00b04ed0
void RBTree::eraseRange(int* param_2, void* param_3, void* param_4)
{
    PoolElem* head = (PoolElem*)&this->mAnchor_04;
    if ((void*)param_3 == *(void**)&this->mAnchor_04.mpRight_04 && param_4 == head) {
        release_node_chain(this->mAnchor_04.mpParent_08);
        this->mAnchor_04.mpParent_08 = 0;
        this->mAnchor_04.mColor_0c = 0;
        this->mnSize_14 = 0;
        this->mAnchor_04.mpRight_04 = (NodeBase*)head;
        this->mAnchor_04.mpLeft_00 = (NodeBase*)head;
        *param_2 = (int)head;
        return;
    }
    PoolElem* cur = (PoolElem*)param_3;
    if (cur != (PoolElem*)param_4) {
        do {
            --this->mnSize_14;
            PoolElem* next = (PoolElem*)RBTreeIncrement(cur);
            RBTreeErase(cur, head);
            void* target = cur->mPayload_18.mpTarget_00;
            if (target) {
                (*(void(__thiscall**)(void*))(*(int*)target + 4))(target);
            }
            if (cur < (PoolElem*)this->mpPoolBegin_20 || (PoolElem*)this->mpPoolEnd_24 <= cur) {
                operator_delete(cur);
            } else {
                cur->mpLink0_00 = (PoolElem*)this->mpFree_18;
                this->mpFree_18 = (int*)cur;
            }
            cur = next;
        } while (cur != (PoolElem*)param_4);
    }
    *param_2 = (int)cur;
}

// @ 0x00b04f70
void RBTree::insert(int* param_2, uint* param_3, uint)
{
    PoolElem* head = (PoolElem*)&this->mAnchor_04;
    PoolElem* pos  = head;
    int   side;
    PoolElem* root = (PoolElem*)this->mAnchor_04.mpParent_08;
    if (root) {
        PoolElem* n = root;
        uint k1 = param_3[1];
        uint k0 = param_3[0];
        do {
            pos = n;
            if (n->mKeyB_14 < k1 || (n->mKeyB_14 <= k1 && n->mKeyA_10 <= k0))
                n = n->mpLink0_00;
            else
                n = n->mpLink1_04;
        } while (n);
    }
    if (pos != head) {
        if (pos->mKeyB_14 <= param_3[1] &&
            (param_3[1] != pos->mKeyB_14 || pos->mKeyA_10 <= param_3[0])) {
            side = 1;
            goto insert;
        }
    }
    side = 0;
insert:
    {
        PoolElem* nd = (PoolElem*)AllocNode(param_3);
        RBTreeInsert(nd, pos, head, side);
        ++this->mnSize_14;
        *param_2 = (int)nd;
    }
}

// @ 0x00b05000
void* RBTree::copyNode(PoolElem* src, PoolElem* parent)
{
    PoolElem* node = (PoolElem*)AllocNodeTiny(&src->mKeyA_10);
    node->mpLink0_00 = 0;
    node->mpLink1_04 = 0;
    node->mpParent_08 = parent;
    node->mColor_0c   = src->mColor_0c;

    if (src->mpLink0_00)
        node->mpLink0_00 = (PoolElem*)copyNode(src->mpLink0_00, node);

    PoolElem* s    = src->mpLink1_04;
    PoolElem* prev = node;
    while (s) {
        PoolElem* dst = (PoolElem*)this->mpFree_18;
        if (dst) {
            this->mpFree_18 = (int*)dst->mpLink0_00;
        } else {
            dst = (PoolElem*)EAAllocate(this->mnStride_28, g_allocName_13ebb38, 0, 0,
                                        g_allocFile_13f09b4, 0xd1);
        }
        if (&dst->mKeyA_10) {
            dst->mKeyA_10 = s->mKeyA_10;
            dst->mPayload_18.CopyFrom(&s->mPayload_18);
        }
        dst->mpLink0_00  = 0;
        dst->mpLink1_04  = 0;
        dst->mpParent_08 = prev;
        dst->mColor_0c   = s->mColor_0c;
        prev->mpLink1_04 = dst;
        if (s->mpLink0_00)
            dst->mpLink0_00 = (PoolElem*)copyNode(s->mpLink0_00, dst);
        s    = s->mpLink1_04;
        prev = dst;
    }
    return node;
}

// 0x00b051f0 (byte-exact lifted version: match/slices/s00b051f0/s00b051f0.cpp)
void FUN_00b051f0(uint param_1, uint param_2)
{
    if (param_1 >= param_2)
        return;
    uint n = ((param_2 - param_1) - 1) / 0x19a8 + 1;
    Leaf* leaf = (Leaf*)param_1;
    do {
        void** end;
        void** it;

        end = leaf->mVec_1190.mpEnd_04;
        for (it = leaf->mVec_1190.mpBegin_00; it < end; it += 0x20)
            (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
        {
            void* a = leaf->mVec_1190.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_978.mpEnd_04;
        for (it = leaf->mVec_978.mpBegin_00; it < end; it += 0x20)
            (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
        {
            void* a = leaf->mVec_978.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_160.mpEnd_04;
        for (it = leaf->mVec_160.mpBegin_00; it < end; it += 0x20)
            (*(void(__thiscall**)(void*, int))(*it))(*it, 0);
        {
            void* a = leaf->mVec_160.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_0fc.mpEnd_04;
        for (it = leaf->mVec_0fc.mpBegin_00; it < end; ++it) {
            void* e = *it;
            if (e)
                (*(void(__thiscall**)(void*))e)(e);
        }
        {
            void* a = leaf->mVec_0fc.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_0a4.mpEnd_04;
        for (it = leaf->mVec_0a4.mpBegin_00; it < end; ++it) {
            void* e = *it;
            if (e)
                (*(void(__thiscall**)(void*))e)(e);
        }
        {
            void* a = leaf->mVec_0a4.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        end = leaf->mVec_04c.mpEnd_04;
        for (it = leaf->mVec_04c.mpBegin_00; it < end; ++it) {
            void* e = *it;
            if (e)
                (*(void(__thiscall**)(void*))e)(e);
        }
        {
            void* a = leaf->mVec_04c.mpBegin_00;
            if (a && ((AllocHdr*)a)[-1].mSize_00 != 0)
                operator_delete(a);
        }

        ++leaf;
        --n;
    } while (n != 0);
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

struct S_00b056e0 { char d[0x24]; };
struct R_00b056e0 { S_00b056e0* p; };
struct I_00b056e0 {
    S_00b056e0* p;
    S_00b056e0& operator*() const { return *p; }
    I_00b056e0& operator++() { ++p; return *this; }
    bool operator!=(const I_00b056e0& o) const { return p != o.p; }
};

// @ 0x00b056e0
R_00b056e0* FUN_00b056e0(R_00b056e0* out, I_00b056e0 first, I_00b056e0 last, S_00b056e0* obj)
{    out->p = obj;
    for (; first != last; ++first, ++out->p) {
        int* p = (int*)out->p;
        if (p) {
            ((PoolOwner_s00b0_47b0*)p)->rbcontainer_copy(&*first);
            *p = (int)g_145c660;
        }
    }
    return out;
}

// @ 0x00b05730
void FUN_00b05730(int* p, uint n, int src, void*)
{
    int* d = p;
    while (n > 0) {
        if (d) {
            ((PoolOwner_s00b0_47b0*)d)->rbcontainer_copy((void*)src);
            *d = (int)g_145c660;
        }
        --n;
        d = (int*)((char*)d + 0x24);
    }
}

// @ 0x00b05770
int* FUN_00b05770(int* srcBegin, int* srcEnd, int* dest, int)
{
    while (srcBegin != srcEnd) {
        if (dest) {
            ((PoolOwner_s00b0_47b0*)dest)->rbcontainer_copy(srcBegin);
            *dest = (int)g_145c660;
        }
        srcBegin = (int*)((char*)srcBegin + 0x24);
        dest     = (int*)((char*)dest + 0x24);
    }
    return dest;
}

// @ 0x00b057b0
void FUN_00b057b0(int* param_1)
{
    unsigned int sn = (unsigned int)((param_1[1] - param_1[0]) >> 2);
    unsigned int i = 0;
    if (sn <= 0) {
        ;
    } else {
        do {
            SlottedObj* obj = ((SlottedObj**)param_1[0])[i];
            void* sub = obj->mpSub_68;
            if (sub) {
                obj->mpSub_68 = 0;
                (*(void(__thiscall**)(void*))(*(int*)sub + 4))(sub);
            }
            ++i;
            obj->mFlag_7c = 1;
        } while (i < sn);
    }
    ((VVec*)param_1)->erase((void*)param_1[0], (void*)param_1[1]);
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
    _ReadWriteBarrier();
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

// @ 0x00b058a0
void* SimObj::curEntry()
{
    uint pitch = this->mId_158;
    uint key   = this->mSel_15c;
    uint idx   = this->mIdx_160;
    SimObj* mgr = (SimObj*)FUN_00b3d440();
    return mgr->slotAt(key, pitch, idx);
}

// @ 0x00b058f0
uint SimObj::curEntryBits()
{
    uint idx   = this->mKeyIdx_54;
    uint id50  = this->mKeyPitch_50;
    uint sel4c = this->mKeyId_4c;
    uint r = 0;
    SimObj* mgr = (SimObj*)FUN_00b3d440();
    SlotVec* a = (SlotVec*)mgr->findSlot(sel4c, id50);
    if (a && idx < (uint)(a->mpEnd_04 - a->mpBegin_00)) {
        SubObj48* e = (SubObj48*)a->mpBegin_00[idx];
        if (e)
            r = popcount32((uint)(e->mBits_48 >> 32));
    }
    return r;
}

// @ 0x00b05a00
Vec3_s00b0_5980* XformObj::F05a00(Vec3_s00b0_5980* out, uint32_t index)
{
    out->x = g_167af5c;
    out->y = g_167af60;
    out->z = g_167af64;
    uint32_t n = Count();
    if (index < n) {
        Vec3_s00b0_5980 tmp;
        void* list = At<void*>(this, 0xa4);
        FUN_006271a0(&tmp, (char*)list + index * 0x38, (char*)this + 0x58);
        out->x = tmp.x;
        out->y = tmp.y;
        out->z = tmp.z;
    }
    return out;
}

// @ 0x00b05c60
EffectVec* EffectVec::F05c60(EffectVec* other)
{
    if (other == this) return this;
    EffectRec* ob = other->begin;
    EffectRec* oe = other->end;
    unsigned otherN = (unsigned)((char*)oe - (char*)ob) >> 5;
    if ((unsigned)((char*)cap - (char*)begin) >> 5 < otherN) {
        EffectRec* nb = allocateCopy(otherN, ob, oe);
        destroyRange(begin, end);
        EffectRec* old = begin;
        if (old != 0 && *(int*)((char*)old - 4) != 0) FUN_00f47380(old);
        end   = (EffectRec*)((char*)nb + otherN * 0x20);
        cap   = (EffectRec*)((char*)nb + otherN * 0x20);
        begin = nb;
        return this;
    }
    unsigned myN = (unsigned)((char*)end - (char*)begin) >> 5;
    if (myN < otherN) {
        FUN_00b027f0((char*)ob + myN * 0x20, oe, begin);
        void* mid = (char*)other->begin + ((unsigned)((char*)end - (char*)begin) >> 5) * 0x20;
        FUN_00b02710(&other, mid, other->end, end, other);
        end = (EffectRec*)((char*)begin + otherN * 0x20);
        return this;
    }
    void* stop = FUN_00b027f0(ob, oe, begin);
    destroyRange((EffectRec*)stop, end);
    end = (EffectRec*)((char*)begin + otherN * 0x20);
    return this;
}

// @ 0x00b05d80
void* RefVec::F05d80(void* pos)
{
    if ((char*)pos + 4 < (char*)end) {
        FUN_005f4e10((char*)pos + 4, end, pos);
    }
    end = (char*)end - 4;
    void* v = *(void**)end;
    if (v != 0) {
        int cnt = At<int>(v, 0x40);
        if (cnt > 1) {
            At<int>(v, 0x40) = cnt - 1;
        } else {
            bool flag = (At<uint32_t>(v, 4) >> 31) & 1;
            void* inner = *(void**)v;
            ((F2)VS(inner, 0x170))(inner, v, (int)flag);
        }
    }
    return pos;
}

// @ 0x00b05fa0
void FUN_00b05fa0(int* src, int* tree)
{
    Tree* t = (Tree*)tree;
    t->reset((void*)tree[3]);
    int* self1 = tree + 1;
    tree[1] = (int)self1;
    tree[2] = (int)self1;
    tree[3] = 0;
    *((uint8_t*)tree + 0x10) = 0;
    tree[5] = 0;

    uint32_t count = 0;
    void* q = vc_p(vc_p(src, 0x20), 0x18);
    FUN_0093a780(q, &count, 1, 0);

    uint32_t i = 0;
    while (i < count) {
        void* obj = 0;
        void* s = vc_p(vc_p(src, 0x20), 0x18);
        Pair val;
        FUN_0093a800(s, &val, 1, 0);
        vc_v(src, 0x1c);
        if (obj != 0) { void* h = obj; obj = 0; vc_v(h, 4); }
        vc_vp(src, 0x28, (void*)0x02e9688e);
        vc_v(src, 0x1c);
        if (obj != 0) vc_v(obj, 0);
        Rec3 out;
        out.a = val.a;
        out.b = val.b;
        out.c = obj;
        uint32_t flags = 0;
        t->add(&out, &val, flags);
        if (obj != 0) vc_v(obj, 4);
        i++;
    }
    vc_v(src, 0x1c);
}

// @ 0x00b06190
void EffectVec::F06190(EffectRec* pos, EffectRec* value)
{
    EffectRec* e = end;
    if (e != cap) {
        if (value >= pos && value < e) {
            value = (EffectRec*)((char*)value + 0x20);
        }
        if (e != 0) e->copyFrom(*(EffectRec*)((char*)e - 0x20));
        FUN_00b02b50(pos, (char*)end - 0x20, end);
        pos->construct(*value);
        end = (EffectRec*)((char*)end + 0x20);
        return;
    }
    int n = (int)((char*)end - (char*)begin) >> 5;
    EffectRec* nb;
    if (n != 0) {
        n = n * 2;
        if (n == 0) { nb = 0; goto have_nb; }
    } else {
        n = 1;
    }
    nb = (EffectRec*)FUN_00f473a0(n << 5, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
have_nb:
    EffectRec* old = begin;
    EffectRec* mid = (EffectRec*)FUN_00b027b0(old, pos, nb);
    FUN_00b01470(old, pos, nb);
    if (mid != 0) {
        mid->copyFrom(*value);
    }
    EffectRec* e2 = end;
    void* ret = FUN_00b027b0(pos, e2, (char*)mid + 0x20);
    FUN_00b01470(pos, e2, (char*)mid + 0x20);
    if (old != 0 && *(int*)((char*)old - 4) != 0) FUN_00f47380(old);
    begin = nb;
    end   = (EffectRec*)ret;
    cap   = (EffectRec*)((char*)nb + n * 0x20);
}

// @ 0x00b065c0
void FUN_00b065c0(RefVec* out, RefVec* src)
{
    unsigned want = (unsigned)((char*)out->end - (char*)out->begin) >> 7;
    unsigned have = (unsigned)((char*)src->end - (char*)src->begin) >> 2;
    if (have < want) {
        uint32_t zero = 0;
        src->growAt(src->end, want - have, &zero);
    } else {
        src->erase((char*)src->begin + want * 4, src->end);
    }

    unsigned n = (unsigned)((char*)out->end - (char*)out->begin) >> 7;
    uint32_t zero = 0;
    unsigned i = 0;
    if (n == 0) return;
    unsigned off = 0;
    do {
        char* e  = (char*)out->begin + off;
        void* td = FUN_00f473a0(0x80, "Simulator/cTreeData_BackwardsCompatibility", 0, 0, 0, 0);
        if (td != 0) td = ((CTreeData*)td)->ctor();
        void** slot = (void**)((char*)src->begin + i * 4);
        void* old = *slot;
        if (td != old) {
            if (td != 0) vc_v(td, 0);
            *slot = td;
            if (old != 0) vc_v(old, 4);
        }
        FUN_00537dc0((char*)td + 0x0c, e + 0x0c);
        At<uint32_t>(td, 0x48) = At<uint32_t>(e, 0x48);
        At<uint32_t>(td, 0x4c) = At<uint32_t>(e, 0x4c);
        At<uint32_t>(td, 0x50) = At<uint32_t>(e, 0x50);
        At<uint32_t>(td, 0x54) = At<uint32_t>(e, 0x54);
        At<uint32_t>(td, 0x58) = At<uint32_t>(e, 0x58);
        void* p1 = At<void*>(e, 0x68);
        void* p2 = At<void*>(td, 0x68);
        if (p1 != p2) {
            if (p1 != 0) vc_v(p1, 0);
            At<void*>(td, 0x68) = p1;
            if (p2 != 0) vc_v(p2, 4);
        }
        off += 0x80;
        At<uint32_t>(td, 0x5c) = At<uint32_t>(e, 0x5c);
        At<uint32_t>(td, 0x60) = At<uint32_t>(e, 0x60);
        At<uint32_t>(td, 0x64) = At<uint32_t>(e, 0x64);
        At<uint32_t>(td, 0x6c) = At<uint32_t>(e, 0x6c);
        At<uint32_t>(td, 0x70) = At<uint32_t>(e, 0x70);
        At<uint32_t>(td, 0x74) = At<uint32_t>(e, 0x74);
        At<uint8_t>(td, 0x7c)  = At<uint8_t>(e, 0x7c);
        i++;
    } while (i < n);
    (void)zero;
}

// @ 0x00b06740
bool Interactable::F06740(void* a, void* b, void* c)
{
    if (InitFromDefinition(a, b, c)) {
        vc_v(this, 0x5c);
        vc_vp((char*)this + 0x34, 0x94, (void*)&g_156741c);
        uint32_t v = 2;
        if (At<uint32_t>(this, 0x16c) != v) {
            At<uint32_t>(this, 0x168) = 0;
            At<uint32_t>(this, 0x16c) = v;
        }
        At<uint32_t>(this, 0x148) |= 1;
        void* self = this;
        vc_v(this, 0);
        Mgr_s00b0_5980* mgr = (Mgr_s00b0_5980*)FUN_00b3d440();
        RefVec* vec = (RefVec*)((char*)mgr + 0x1b905c);
        if ((char*)vec->end < (char*)vec->cap) {
            void** e = (void**)vec->end;
            vec->end = (char*)e + 4;
            if (e != 0) {
                *e = this;
                vc_v(this, 0);
            }
        } else {
            vec->insertSlow(vec->end, &self);
        }
        if (self != 0) vc_v(self, 4);
        return true;
    }
    return false;
}

// @ 0x00b06810
bool EffectOwner::F06810(uint32_t key)
{
    EffectRec* it  = *(EffectRec**)((char*)this + 0x160e8);
    EffectRec* end = *(EffectRec**)((char*)this + 0x160ec);
    if (it == end) return false;
    do {
        uint32_t f = At<uint32_t>(it, 0x10);
        if (f != 0 && f == key) {
            if (it + 1 < end) {
                FUN_00b027f0(it + 1, end, it);
            }
            *(EffectRec**)((char*)this + 0x160ec) = (EffectRec*)((char*)end - 0x20);
            EffectRec* e = *(EffectRec**)((char*)this + 0x160ec);
            e->f00 = 0;
            e->f08 = 0;
            e->f0c = 0;
            void* p = e->f10;
            if (p != 0) { e->f10 = 0; vc_v(p, 4); }
            p = e->f14;
            if (p != 0) { e->f14 = 0; vc_v(p, 0x38); }
            e->f18 = 0;
            if (e->f14 != 0) vc_v(e->f14, 0x38);
            if (e->f10 != 0) vc_v(e->f10, 4);
            return true;
        }
        it = (EffectRec*)((char*)it + 0x20);
    } while (it != end);
    return false;
}

// @ 0x00b068c0
void RangeScan::F068c0(void* range, uint32_t a, uint32_t b)
{
    if (At<uint32_t>(range, 0x14) == 0) return;
    int* node = (int*)At<void*>(range, 8);
    int* stop = (int*)((char*)range + 4);
    if (a != 0 || b != 0) {
        int pair[2];
        ((Tree*)range)->lowerBound(pair, &a);
        stop = (int*)pair[1];
        node = (int*)pair[0];
    }
    int* cur = node;
    if (cur != stop) {
        char* base = (char*)this + 0x1b9174;
        do {
            int* obj = (int*)At<void*>(cur, 0x18);
            int* held = obj;
            if (obj != 0) {
                vc_v(obj, 0);
                int* sub = *(int**)((char*)obj + 0x1c4);
                if (sub != 0) {
                    vc_vi(sub, 0x0c, 1);
                    sub = *(int**)((char*)obj + 0x1c4);
                    if (sub != 0) {
                        *(int**)((char*)obj + 0x1c4) = 0;
                        vc_v(sub, 4);
                    }
                }
                void* vd = *(void**)((char*)obj + 0x1a0);
                void* vs = *(void**)((char*)obj + 0x19c);
                FUN_011e0744(vs, vd, 0);
                *(int*)((char*)obj + 0x1a0) =
                    *(int*)((char*)obj + 0x1a0) + ((int)vd - (int)vs >> 2) * -4;
            }
            RefVec* vec = (RefVec*)base;
            if ((unsigned)((char*)vec->end - (char*)vec->begin) >> 2 < g_15673b8) {
                vc_v(obj, 0x44);
                void** e = (void**)vec->end;
                if (e < (void**)vec->cap) {
                    vec->end = (char*)e + 4;
                    if (e != 0) { *e = obj; vc_v(obj, 0); }
                } else {
                    vec->insertSlow(vec->end, &held);
                    obj = held;
                }
            } else {
                void* nm = FUN_00b3d300(obj);
                ((NounMgr_s00b0_5980*)nm)->RemoveNoun(obj);
            }
            if (obj != 0) vc_v(obj, 4);
            cur = (int*)FUN_00921580(cur);
        } while (cur != stop);
    }
    ((Tree*)range)->addRange((void*)&a, (void*)node, (void*)stop);
}

// @ 0x00b06a40
void** TearDown::F06a40(void** slot, int flag)
{
    void* obj = *slot;
    if (obj != 0) {
        vc_v(obj, 0);
        At<uint32_t>(obj, 0x154) = 0;
        At<uint32_t>(obj, 0x158) = 0x6d60a1cc;
        At<uint32_t>(obj, 0x15c) = 0xffffffff;
        At<uint32_t>(obj, 0x160) = 0xffffffff;
        At<uint32_t>(obj, 0x164) = 0xffffffff;
        void* p = At<void*>(obj, 0x108);
        if (p != 0) { At<void*>(obj, 0x108) = 0; vc_v(p, 4); }
        At<uint32_t>(obj, 0x16c) = 6;
        At<uint32_t>(obj, 0x148) &= ~2u;
        p = At<void*>(obj, 0x108);
        if (p != 0) { At<void*>(obj, 0x108) = 0; vc_v(p, 4); }
        vc_vp((char*)obj + 0x34, 0x38, (void*)&g_167af5c);
        At<uint8_t>(obj, 0xa5) = 1;
        At<uint8_t>(obj, 0xa9) = 0;
        vc_vi((char*)obj + 0x34, 0x40, 0x3f800000);
        if (vc_i((char*)obj + 0x34, 0xac) != 0) {
            void* q = vc_p((char*)obj + 0x34, 0xac);
            At<uint32_t>(q, 4) &= ~1u;
            q = vc_p((char*)obj + 0x34, 0xac);
            void* inner = *(void**)q;
            ((F2)VS(inner, 0x16c))(inner, q, 0);
        }
        if (flag != 0) {
            vc_vi((char*)obj + 0x34, 0x40, 0x3f800000);
            RefVec* vec = (RefVec*)((char*)this + 0x1b8f44);
            if ((char*)vec->end < (char*)vec->cap) {
                void** e = (void**)vec->end;
                vec->end = (char*)e + 4;
                if (e != 0) { *e = obj; vc_v(obj, 0); }
            } else {
                vec->insertSlow(vec->end, &obj);
                obj = *(void**)vec->end;
            }
        }
    }
    RefVec* vec = (RefVec*)((char*)this + 0x1b905c);
    if ((char*)slot + 4 < (char*)vec->end) {
        FUN_006782c0((char*)slot + 4, vec->end, slot);
    }
    vec->end = (char*)vec->end - 4;
    void* last = *(void**)vec->end;
    if (last != 0) vc_v(last, 4);
    if (obj != 0) vc_v(obj, 4);
    return slot;
}

// @ 0x00b06bd0
void Proximity::F06bd0(Vec3_s00b0_5980* point, float radius, RefVec* out)
{
    out->erase(out->begin, out->end);
    float rr = radius * radius;
    void** it  = (void**)*(void**)((char*)this + 0x1b905c);
    void** end = (void**)*(void**)((char*)this + 0x1b9060);
    while (it != end) {
        void* obj = *it;
        Vec3_s00b0_5980* p = (Vec3_s00b0_5980*)vc_p((char*)obj + 0x34, 0x2c);
        float dx = p->x - point->x;
        float dy = p->y - point->y;
        float dz = p->z - point->z;
        if (dx * dx + dy * dy + dz * dz < rr) {
            vc_v(obj, 0);
            if ((char*)out->end < (char*)out->cap) {
                void** e = (void**)out->end;
                out->end = (char*)e + 4;
                if (e != 0) { *e = obj; vc_v(obj, 0); }
            } else {
                out->insertSlow(out->end, &obj);
                obj = *(void**)out->end;
            }
            if (obj != 0) vc_v(obj, 4);
        }
        it = it + 1;
    }
    volatile int selfbits = (int)this;
    if (selfbits == *(volatile int*)((char*)this + 0x1b905c)) return;
}

// @ 0x00b06cd0
void ModelList::F06cd0()
{
    void* it  = *(void**)((char*)this + 0x16504);
    void* end = *(void**)((char*)this + 0x16508);
    while (it != end) {
        void* o = *(void**)it;
        if (o != 0) {
            void* p = At<void*>(o, 0x64);
            if (p != 0) { At<void*>(o, 0x64) = 0; vc_v(p, 4); }
            At<uint32_t>(o, 4) &= ~1u;
            void* inner = *(void**)o;
            ((F2)VS(inner, 0x16c))(inner, o, 0);
        }
        void* e2 = *(void**)((char*)this + 0x16508);
        if ((char*)it + 4 < (char*)e2) {
            FUN_005f4e10((char*)it + 4, e2, it);
        }
        *(char**)((char*)this + 0x16508) -= 4;
        void* v = *(void**)*(void**)((char*)this + 0x16508);
        if (v != 0) {
            int cnt = At<int>(v, 0x40);
            if (cnt > 1) {
                At<int>(v, 0x40) = cnt - 1;
            } else {
                int flag = (int)(At<uint32_t>(v, 4) >> 31) & 1;
                void* inner = *(void**)v;
                ((F2)VS(inner, 0x170))(inner, v, flag);
            }
        }
        end = *(void**)((char*)this + 0x16508);
    }
}

void* __cdecl destroy_range_big_s06(void* src, void* end, void* dst); // 0x00b03f10 (slice view: declared only)
// 0x00b07140 (byte-exact lifted version: match/slices/s00b07140/s00b07140.cpp)
void cBigVector::Erase(void* first, void* last)
{
    cBigElement* p = (cBigElement*)destroy_range_big_s06(last, mpEnd, first);
    cBigElement* end = (cBigElement*)mpEnd;
    while (p < end) {
        ((void (__thiscall*)(cBigElement*, int))((void**)p->mpVtable)[2])(p, 0);
        p = (cBigElement*)((char*)p + 0x80);
    }
    mpEnd = (void*)((char*)mpEnd + (((char*)last - (char*)first) >> 7) * -0x80);
}

// @ 0x00b072d0
void __cdecl CopyGlyphRuns(cGlyphRun* dst, cGlyphRun* end, const cGlyphRun* src)
{
    if (dst != end) {
        do {
            dst->mFlag = src->mFlag;
            dst->mGlyphs = src->mGlyphs;
            dst->mValue1c = src->mValue1c;
            dst->mValue20 = src->mValue20;
            ++dst;
        } while (dst != end);
    }
}

// @ 0x00b07980
bool Mgr_s00b0_7980::FUN_00b07980(Req* req, bool flag, Group* g4, Group* p5, Group* p6)
{
    bool result = false;
    uint32_t mode = At_s00b0_7980<uint32_t>(this, 0x1ba18c);
    if ((mode & 1) == 0) return false;
    if (((mode >> 1) & 1) == 0) return false;

    uint8_t* elems = req->elems;
    void*    key   = req->key;
    uint32_t count = req->count;

    uint32_t id = GetIdLookup()->Lookup(req);
    if (!id) return false;
    Species* species = GetSpeciesMgr()->GetSpeciesFromID(id);
    if (!species) return false;
    if (species->GetKind() == 0x3a8be428) return false;
    result = true;

    uint32_t kind = species->GetKind();
    Triple pair = { key, kind, 0 };
    Model* model = species->GetModelWorld();

    VfxRef vfx;
    vfx.p = 0;
    if (flag && model && model->GetCount() != 0 && count != 0) {
        EffectsManager* em = GetEffectsManager();
        if (em->CreateEffect(g_15673a8, g_15673ac, vfx.AsPPTypeParam())) {
            EffectRec_s00b0_7980 rec;
            rec.z14 = 0; rec.z18 = 0;
            rec.vfx.p = 0;
            rec.total = model->GetCount() * count;
            rec.key = key;
            rec.kind = kind;
            rec.vfx.assign(&vfx);
            vfx.p->Slot2(0);
            ((EffectVec_s00b0_7980*)((char*)this + 0x160e8))->push_back(&rec);
            rec.Reset();
        }
    }

    Range range = { 0, 0 };
    Group* last = p5;
    bool found = FindExisting(&range, key, kind, count, p5);
    if (!found) {
        if (p6) {
            found = FindExisting(&range, key, kind, count, p6);
            last = p6;
        }
    }
    uint32_t outTmp[2];

    if (found) {
        Bucket_s00b0_7980* bucket = GetBucket(key, species->GetKind());
        int idx = -1;
        uint32_t i = 0;
        RBNode* it = range.begin;
        uint8_t* cursor = elems + 0xc;
        if (it != range.end) {
            do {
                if (i >= count) break;
                Item* item = FUN_00afff30(bucket, i);
                Plant* o = it->value;
                At_s00b0_7980<uint32_t>(o, 0x54) = i;
                Xform* xf = &At_s00b0_7980<Xform>(o, 0x58);
                *xf = *(Xform*)(cursor - 0xc);
                Vector3_s00b0_7980 v;
                v.x = *(float*)(cursor - 8);
                v.y = *(float*)(cursor - 4);
                v.z = *(float*)cursor;
                Vector3_s00b0_7980 tmp;
                Vector3_s00b0_7980* r = GetPlanetModel()->DirectionToSurfacePosition(&tmp, &v);
                v = *r;
                xf->pos = *r;
                xf->flags |= 4;
                xf->counter++;
                XformListener* lst = At_s00b0_7980<XformListener*>(o, 0x1d0);
                if (lst) {
                    XformMsg m;
                    lst->Slot8(&m);
                    m.flags |= 4;
                    m.counter++;
                    m.pos = v;
                    lst->Slot6(&m);
                }
                GetPlanetModel()->FUN_00b88420();
                uint32_t rad = GetPlanetModel()->GetAverageRadius(&v);
                if ((rad & 0x18000000) && item) {
                    At_s00b0_7980<uint32_t>(item, 0x48) = 0;
                    At_s00b0_7980<uint32_t>(item, 0x4c) = 0;
                }
                if (item && flag)
                    At_s00b0_7980<Xform>(item, 0xc) = *xf;
                At_s00b0_7980<VfxRef>(o, 0x1c4).assign(&vfx);
                uint32_t n = model->GetCount();
                for (uint32_t j = 0; j < n; ++j) {
                    ++idx;
                    At_s00b0_7980<int*>(o, 0x19c)[j] = idx;
                }
                if (item) {
                    EffectBook* book = At_s00b0_7980<EffectBook*>(this, 0x16500);
                    if (book) {
                        if (book->f24 == book->f28) InitBook();
                        if (At_s00b0_7980<int>(item, 0x78) == -1) {
                            EffectBook* b2 = At_s00b0_7980<EffectBook*>(this, 0x16500);
                            if (b2->f24 != b2->f28)
                                At_s00b0_7980<int>(item, 0x78) = b2->FUN_00703d50(At_s00b0_7980<float>(item, 0x6c), &At_s00b0_7980<uint32_t>(item, 0x10), item);
                        }
                    }
                }
                if (last != p6) {
                    o->AddRef();
                    Triple t = { pair.key, pair.kind, o };
                    o->AddRef();
                    g4->Add(outTmp, &t, false);
                    o->Release();
                    o->Release();
                }
                it = RBTreeIncrement(it);
                ++i;
                cursor += 0x4c;
            } while (it != range.end);
        }
        if (last != p6)
            last->AddRange(outTmp, range.begin, range.end);
    } else {
        int idx = -1;
        Bucket_s00b0_7980* bucket = GetBucket(key, species->GetKind());
        bool isEmpty = (bucket == 0) || (bucket->first == bucket->second);
        if (count > 0) {
            bool notFlag = !flag;
            Xform* cursor = (Xform*)elems;
            uint32_t i = 0;
            do {
                Plant* o = NewPlant();
                if (o) o->AddRef();
                At_s00b0_7980<void*>(o, 0x4c) = key;
                At_s00b0_7980<uint32_t>(o, 0x54) = i;
                const Vector3_s00b0_7980* sp = species->GetPosition();
                At_s00b0_7980<float>(o, 0x94) = sp->x;
                At_s00b0_7980<float>(o, 0x98) = sp->y;
                At_s00b0_7980<float>(o, 0x9c) = sp->z;
                if (SetupPlant(o, species, cursor, isEmpty, notFlag, &idx, &vfx)) {
                    o->AddRef();
                    Triple t = { pair.key, pair.kind, o };
                    g4->Add(outTmp, &t, false);
                    o->Release();
                } else {
                    GetNounManager()->RemoveNoun(o);
                }
                o->Release();
                cursor = (Xform*)((char*)cursor + 0x4c);
                ++i;
            } while (i < count);
        }
    }
    if (vfx.p) vfx.p->Release();
    return result;
}

// @ 0x00b07fa0
bool Mgr_s00b0_7980::FUN_00b07fa0(SimEvent* ev, bool flag, PlantRange* range, Group* group)
{
    bool result = false;
    if (range->mCount == 0)
        return false;

    Req* req = (Req*)ev;
    void* key = req->key;
    uint32_t count = req->field30;

    uint32_t id = GetIdLookup()->Lookup(req);
    if (!id)
        return result;
    Species* species = GetSpeciesMgr()->GetSpeciesFromID(id);
    if (!species)
        return result;

    uint32_t kind = species->GetKind();
    Range found = { 0, 0 };
    int idx = -1;
    uint32_t out[2];
    range->FindRange(&found, &key);

    uint32_t n = 0;
    for (RBNode* it = found.begin; it != found.end; it = RBTreeIncrement(it))
        ++n;
    if (n == 0)
        return result;

    uint32_t skip = count & 1;
    result = true;
    for (RBNode* it = found.begin; it != found.end; it = RBTreeIncrement(it)) {
        PlantObject* o = (PlantObject*)it->value;
        if (o)
            o->AddRef();
        if (flag)
            F06810(o->mpVfx);
        if (o->mpVfx) {
            o->mpVfx->Slot3(1);
            if (o->mpVfx) {
                VfxOwner* old = o->mpVfx;
                o->mpVfx = 0;
                old->Release();
            }
        }
        o->mIndex54 = ++idx;
        o->mField1c8 = 0;
        int slots = (int)(o->mpSlotIdsEnd - o->mpSlotIds);
        for (int j = 0; j < slots; ++j)
            o->mpSlotIds[j] = 0xffffffff;
        if (skip == 0) {
            Triple t = { key, kind, (Plant*)o };
            o->AddRef();
            group->Add(out, &t, false);
            o->Release();
        }
        o->Release();
    }
    if (skip == 0) {
        range->AddRange(out, found.begin, found.end);
        return result;
    }

    // the request carries pit objects: drop the slot shadows and the queued effects
    F068c0(group, key, kind);
    for (void** p = mVec16504.mBegin; p != mVec16504.mEnd; ++p) {
        HolderObject* h = (HolderObject*)*p;
        VfxOwner* ref = h->mpField64;
        if (ref) {
            h->mpField64 = 0;
            ref->Release();
        }
    }
    Bucket_s00b0_7980* bucket = GetBucket(key, species->GetKind());
    if (bucket) {
        for (BucketObject** p = (BucketObject**)bucket->first; p != (BucketObject**)bucket->second; ++p) {
            BucketObject* item = *p;
            if (!item)
                continue;
            EffectBook* book = mpBook;
            if (!book)
                continue;
            if (book->f24 == book->f28)
                InitBook();
            if (item->mSlot78 < 0)
                continue;
            book = mpBook;
            if (book->f24 != book->f28)
                book->Remove(item->mSlot78);
            item->mSlot78 = -1;
        }
        FUN_00b057b0(bucket);
    }
    return result;
}

// @ 0x00b08260
bool Mgr_s00b0_7980::FUN_00b08260(uint32_t eventId, SimEvent* ev)
{
    bool result = false;
    MapNode* node;
    RecordBuilder built;
    RefCollector collector;

    switch (eventId) {
    case 0x2f3fc35: {
        uint32_t key0 = ev->mKey;
        void*    transforms = ev->mpTransforms;
        void*    target = ev->mpTarget;
        uint32_t targetId = (uint32_t)target;
        if (transforms == 0) {
            // the object went away: drop its map entry
            void* key = target;
            mMap8080.find(&node, &key);
            if (node != mMap8080.end()) {
                if (node->mpValue)
                    node->mpValue->Slot3(1);
                FUN_00b043b0(&node, node);
            }
            return true;
        }
        if ((mMode & 1) == 0)
            return true;
        if ((mMode >> 1 & 1) == 0)
            return true;

        bool matched = false;
        for (int i = 0; i < 6; ++i)
            collector.mpData[i] = 0;
        built.mField00 = 0;
        void* mapKey = target;
        mMap8080.find(&node, &mapKey);
        if (node != mMap8080.end()) {
            matched = true;
            if (node->mpKey == (void*)key0)
                node->mpField30 = transforms;
            collector.Add(&node->mpKey);
        }
        for (EffectRec_s00b0_7980* rec = mEffects.mBegin; rec != mEffects.mEnd; ++rec) {
            if (matched)
                break;
            VfxOwner* fx = (VfxOwner*)rec->vfx.p;
            if (!fx)
                continue;
            FeatureVec* vec = (FeatureVec*)((char*)fx + 0x144);
            uint32_t count = vec->Size();
            FeatureLookup* f = vec->mBegin;
            for (uint32_t i = 0; i < count; ++i, f = (FeatureLookup*)((char*)f + 0x5c)) {
                if (f->mSlotId38 != targetId)
                    continue;
                matched = true;
                ((RecordTail*)&rec->z14)->F07d4590(target);
                if (key0 == rec->total)
                    rec->z18 = (uint32_t)transforms;
                collector.Add(rec);
                void* bkey = target;
                void* value = built.Build(&bkey, &collector);
                mMap8080.F05c30(&collector, value);
                built.Reset();
                mEffects.F05d50(rec);
                break;
            }
        }
        if (matched) {
            if (key0 == built.mField00) {
                // re-seat the objects of the range on the transforms of the event
                Range found = { 0, 0 };
                void* rkey = target;
                mRange34.FindRange(&found, &rkey);
                for (RBNode* it = found.begin; it != found.end; it = RBTreeIncrement(it)) {
                    PlantObject* o = (PlantObject*)it->value;
                    if (!o)
                        continue;
                    o->mField1c8 = targetId;
                    SlotBits* bits = slotAt(o->mpKey, o->mField50, o->mIndex54);
                    uint32_t slots = o->CurEntryBits();
                    for (uint32_t i = 0; i < slots; ++i) {
                        uint32_t slot = o->mpSlotIds[i];
                        if (slot >= key0)
                            continue;
                        Xform tmp;
                        translateTransform(&tmp, (char*)o->mpMatrixA4 + i * 0x38, &o->mXform58);
                        ((XformOps*)((char*)transforms + slot * 0x4c))->Assign(&tmp);
                        if (bits) {
                            uint64_t mask = __allshl(1, i);
                            if ((bits->mMaskLo & (uint32_t)mask) == 0 &&
                                (bits->mMaskHi & (uint32_t)(mask >> 32)) == 0)
                                ((SlotOwner*)this)->SetShadow(slot, 0.0f);
                        }
                    }
                }
            }
            else {
                ((SimTarget*)target)->mRangeKey = built.mField00;
            }
        }
        built.Reset();
        return true;
    }
    case 0x25630b7:
        result = true;
        break;
    case 0x2e9977e:
        break;
    case 0x477c00d:
        result = true;
        break;
    default:
        return false;
    }

    // place / update the objects of the request
    void* id08 = ev->mpTransforms;
    Req* req = (Req*)ev;
    fillSlot(ev);
    if (id08 != 0) {
        Group* p5 = (mField1ba190 > 0) ? (Group*)&mRange34 : 0;
        FUN_00b07980(req, result, (Group*)&mRange34, &mGroup165a0, p5);
    }
    else {
        FUN_00b07fa0(ev, result, &mRange34, &mGroup165a0);
    }
    return true;
}

// @ 0x00b08e90
Item_s00b0_8670* ItemManager::FUN_00b08e90()
{
    Item_s00b0_8670* result = 0;
    if ((uint32_t)(mpPendingEnd - mpPendingBegin) > 0)
    {
        Item_s00b0_8670* item = mpPendingEnd[-1];
        if (item)
        {
            item->AddRef();
            result = item;
        }
        --mpPendingEnd;
        Item_s00b0_8670* popped = *mpPendingEnd;
        if (popped)
            popped->Release();
    }
    else
    {
        Camera* cam = (Camera*)((Viewer*)App()->v50())->v1c();
        Vector3_s00b0_8670 camPos = g_167af5c_s00b0_8670;
        Vector3_s00b0_8670 camUp = g_167af5c_s00b0_8670;
        if (cam)
            cam->GetCameraLocationInfo(&camPos, &camUp, 0, 0);
        Item_s00b0_8670** end = mpEnd;
        Item_s00b0_8670** best = end;
        float bestDist = 0.0f;
        for (Item_s00b0_8670** it = mpBegin; it != end; ++it)
        {
            Item_s00b0_8670* item = *it;
            if (!item)
                continue;
            if (item->mState == 3)
                continue;
            if (item->mFlags148 & 1)
                continue;
            if (item->mpEffect)
                continue;
            const Vector3_s00b0_8670* p = item->mSpatial.GetPosition();
            const float dy = p->y - camPos.y;
            const float dx = p->x - camPos.x;
            const float dz = p->z - camPos.z;
            const float d = dz * dz + dy * dy + dx * dx;
            if (d > bestDist)
            {
                best = it;
                bestDist = d;
            }
        }
        if (best == end)
            return 0;
        Item_s00b0_8670* item = *best;
        if (item)
        {
            item->AddRef();
            result = item;
        }
        FUN_00b06a40(best, false);
    }
    if (result)
    {
        result->mSpatial.SetF40(1.0f);
        if (FUN_00b3d310())
            FUN_00b3d310()->FUN_00b453a0(&result->mSpatial);
        result->Release();
    }
    return result;
}

// @ 0x00b09070
void cQueryMgr::FUN_00b09070(uint32_t a1, float a2, SPVec* out, int a4)
{
    uint32_t buf[256];
    SPVec local;
    local.mpBegin = buf;
    local.mpEnd = buf;
    local.mpCapacity = buf + 256;
    local.mAlloc = 0;

    out->erase(out->mpBegin, out->mpEnd);

    ResObj* q = FUN_00b3d3c0(a1, &local, 6, a2, 1, 0);
    q->FUN_00b79c30();

    out->FUN_00d01790((uint32_t)(local.mpEnd - local.mpBegin));

    for (uint32_t* it = local.mpBegin; it != local.mpEnd; ++it)
    {
        uint32_t* e = (uint32_t*)*it;
        uint32_t key;
        switch (e[0x88 / 4])
        {
        case 0: key = 0x3a8be428; break;
        case 1: key = 0x29c388a;  break;
        case 2: key = 0x6d60a1cc; break;
        default: continue;
        }
        uint32_t r = FindNth(key, e[0x50 / 4], e[0x5c / 4]);
        if (r)
        {
            if (out->mpEnd < out->mpCapacity)
                *out->mpEnd++ = r;
            else
                out->DoInsertKey(out->mpEnd, r);
        }
    }

    if (a4)
        FUN_00b062c0(out->mpBegin, out->mpEnd, a4);

    struct AllocHeader { uint32_t mFlag; };
    if (local.mpBegin && ((AllocHeader*)local.mpBegin)[-1].mFlag != 0)
        ea_delete(local.mpBegin);
}

// @ 0x00b091d0
void cCreatureHitBoxes::FUN_00b091d0()
{
    if ((uint32_t)(mList.mpEnd - mList.mpBegin) > 0)
        FUN_00b06cd0();

    ModelMgr* mm = ModelManager();
    ResObj* model = (ResObj*)mm->v1c(0xeb9968);
    if (model)
        model->AddRef();

    mList.FUN_00473270(0x14);

    const uint32_t n = (uint32_t)(mList.mpEnd - mList.mpBegin);
    for (uint32_t i = 0; i < n; ++i)
    {
        if (mList.mpBegin[i] == 0)
        {
            ResObj* made = model->v0c(0x2e81370, g_167afa8, 0x10);
            ModelInst* old = mList.mpBegin[i];
            if (made != (ResObj*)old)
            {
                if (made)
                    ++((ModelInst*)made)->mRefCount;
                mList.mpBegin[i] = (ModelInst*)made;
                if (old)
                {
                    if (old->mRefCount > 1)
                        --old->mRefCount;
                    else
                        old->v170((old->mField04 >> 31) & 1);
                }
            }
            ModelInst* inst = mList.mpBegin[i];
            inst->mData1c = g_167b554;
            inst->mF18 = g_1485720;
            inst->mPos = g_167af5c_s00b0_8670;
            inst->mWord08 = 0;
            inst->mWord0a = 0;
            inst->mField04 &= ~1u;
            inst->v16c(0);
        }
    }

    if (model)
        model->Release();
}

// @ 0x00b09340
void cBigList::FUN_00b09340(Vector3_s00b0_8670* p, float radius, SPVec* out, bool full, Vector3_s00b0_8670* filter)
{
    const int n = (int)(mpEnd - mpBegin);
    if (n == 0)
    {
        out->erase(out->mpBegin, out->mpEnd);
        return;
    }

    out->FUN_00d01790(Min(n, 0x20));

    for (BigElem_s00b0_8670* e = mpBegin; e != mpEnd; ++e)
    {
        if (filter != 0 &&
            memcmp(filter, &e->mCmp0, sizeof(Vector3_s00b0_8670)) != 0 &&
            memcmp(filter, &e->mCmp1, sizeof(Vector3_s00b0_8670)) != 0 &&
            memcmp(filter, &e->mCmp2, sizeof(Vector3_s00b0_8670)) != 0)
            continue;

        const float dy = e->mPos.y - p->y;
        const float dz = e->mPos.z - p->z;
        const float dx = e->mPos.x - p->x;
        const float rr = e->mRadius + radius;
        const float d = dy * dy + dz * dz + dx * dx;
        if (rr * rr > d)
        {
            if (out->mpEnd < out->mpCapacity)
                *out->mpEnd++ = (uint32_t)&e->mPos;
            else
                out->DoInsertKey(out->mpEnd, (const uint32_t&)e->mPos);
        }
    }

    if (full)
        FUN_00b06420(out->mpBegin, out->mpEnd, *p);
}

// @ 0x00b09510
cEffectPool* cEffectPool::FUN_00b09510(int a1)
{
    FixedPool pool;
    pool.mpHead = 0;
    pool.init(mBuffer, 0xe000, 0x38, 8, 0);
    pool.mpStart = mBuffer;
    pool.mpEnd = (char*)pool.mpStart + 0xe000;
    pool.mSize = 0x38;
    FUN_00b00610(a1, &pool);
    FUN_00b05ba0(a1);
    return this;
}

// 0x00b09570 (byte-exact lifted version: match/slices/s00b09570/s00b09570_lifted.cpp)
Scatter::Scatter(const Scatter &src)
{
    mX = src.mX;
    mY = src.mY;
    mZ = src.mZ;
    mSpread = src.mSpread;
    mPad10 = src.mPad10;
    mPad14 = src.mPad14;
    mPad18 = src.mPad18;
    mPad1c = src.mPad1c;
    mPad20 = src.mPad20;
    mPad24 = src.mPad24;
    mPad28 = src.mPad28;
    mPad2c = src.mPad2c;
    mPad30 = src.mPad30;
    mPad34 = src.mPad34;
    mPad38 = src.mPad38;
    mPad3c = src.mPad3c;
    mFlag40 = src.mFlag40;
    Fv16 *p0 = &mSmall0;
    p0->mpBegin = p0->mBuf;
    p0->mpEnd = p0->mBuf;
    p0->mpCap = p0->mBuf + 16;
    p0->mCount = 0;
    CopyFv16Contents(p0, &src.mSmall0);
    Fv16 *p1 = &mSmall1;
    p1->mpBegin = p1->mBuf;
    p1->mpEnd = p1->mBuf;
    p1->mpCap = p1->mBuf + 16;
    p1->mCount = 0;
    CopyFv16Contents(p1, &src.mSmall1);
    Fv16 *p2 = &mSmall2;
    p2->mpBegin = p2->mBuf;
    p2->mpEnd = p2->mBuf;
    p2->mpCap = p2->mBuf + 16;
    p2->mCount = 0;
    CopyFv16Contents(p2, &src.mSmall2);
    mTimerA = src.mTimerA;
    mTimerB = src.mTimerB;
    Fv512 *b0 = &mBig0;
    b0->mpBegin = b0->mBuf;
    b0->mpEnd = b0->mBuf;
    b0->mpCap = b0->mBuf + 512;
    b0->mCount = 0;
    CopyFv512Contents(b0, &src.mBig0);
    Fv512 *b1 = &mBig1;
    b1->mpBegin = b1->mBuf;
    b1->mpEnd = b1->mBuf;
    b1->mpCap = b1->mBuf + 512;
    b1->mCount = 0;
    CopyFv512Contents(b1, &src.mBig1);
    Fv512 *b2 = &mBig2;
    b2->mpBegin = b2->mBuf;
    b2->mpEnd = b2->mBuf;
    b2->mpCap = b2->mBuf + 512;
    b2->mCount = 0;
    CopyFv512Contents(b2, &src.mBig2);
}

// ---- F09740 / Place from slice s00b09570 (landed by hand: the module spells the callees differently)
extern "C" void  FUN_00b07140_p9(void *pVec, void *pBegin, void *pEnd);
extern "C" Mgr  *FUN_00b3d440_p9();
extern "C" void *FUN_00b08e90_p9(void *pThis);
extern "C" void *FUN_00b04ba0_p9(void *pThis, u32 a, u32 b);
extern "C" int   FUN_00b3d310_p9();
extern "C" void  FUN_00b023d0_p9(void *pThis, void *a, u32 b, u32 c);
extern "C" void  FUN_00b065c0_p9(void *pDst, void *pSrc);
extern "C" void *EA__Audio__GetSystemAT_p9();
extern "C" void  Start3dSoundByName_p9(u32 id, void *pSys, float x, float y, float z);
extern "C" void *SP__cVarListSerializer__ctor_p9(void *pThis, void *a, const char *s, u32 n);
extern "C" char  SP__cVarListSerializer__Serialize_p9(void *pThis, u32 a);
extern "C" void *rw__math__fpu__QuaternionFromMatrix33_p9(void *pOut, void *pIn, int n);
extern "C" void *cSPTransformOps__Assign_p9(void *pThis, const void *pSrc);
extern "C" void *translateTransform_p9(void *pOut, const char *pIn, const float *pVec);
extern "C" void  FUN_00aea5d0_p9(void *pPos, void **ppSrc);
extern "C" void  FUN_00c3f8b0_p9(int a, int b);
extern "C" void  FUN_00b53940_p9(void *pThis);
extern "C" void  FUN_00b5a260_p9(void *pThis, int a);
extern "C" void  FUN_00b54200_p9(void *pThis);
extern "C" void  FUN_00b54230_p9(void *pThis, int a);
typedef void  (__thiscall *F1i_p9)(void *, int);
typedef void  (__thiscall *F1u_p9)(void *, u32);
static inline void *vc_p_p9(void *o, int off) { return ((F0p_s00b0_9570)VS_s00b0_9570(o, off))(o); }
static inline void  vc_v_p9(void *o, int off) { ((F0v_s00b0_9570)VS_s00b0_9570(o, off))(o); }
static inline void  vc_vu_p9(void *o, int off, u32 a) { ((F1u_p9)VS_s00b0_9570(o, off))(o, a); }

// @ 0x00b09740
char Scatter::F09740(u32 param_2)
{
    char buf[0xa14];
    SP__cVarListSerializer__ctor_p9(buf, this, (const char *)0x01567428, 0x1a80d26);
    char ok = SP__cVarListSerializer__Serialize_p9(buf, param_2);
    if (ok != 0) {
        if (mBig0.mpBegin != mBig0.mpEnd) {
            FUN_00b065c0_p9(&mBig0, &mSmall0);
            FUN_00b07140_p9(&mBig0, mBig0.mpBegin, mBig0.mpEnd);
        }
        if (mBig1.mpBegin != mBig1.mpEnd) {
            FUN_00b065c0_p9(&mBig1, &mSmall1);
            FUN_00b07140_p9(&mBig1, mBig1.mpBegin, mBig1.mpEnd);
        }
        if (mBig2.mpBegin != mBig2.mpEnd) {
            FUN_00b065c0_p9(&mBig2, &mSmall2);
            FUN_00b07140_p9(&mBig2, mBig2.mpBegin, mBig2.mpEnd);
        }
        return ok;
    }
    return 0;
}

// @ 0x00b09830
Scatter *Mgr::Place(u32 index, int *pOut)
{
    Scatter *pEntry = 0;
    Mgr *pMan = this;
    if (*(char *)&pOut != 0) {
        pMan = FUN_00b3d440_p9();
        Scatter *pNew = (Scatter *)FUN_00b08e90_p9(pMan);
        if (pNew == 0)
            goto done;
        vc_v_p9(pNew, 0);
        pOut = (int *)pNew;
        pMan = FUN_00b3d440_p9();
        u32 *pEnd = pMan->mpTreesBegin;
        if (pEnd < pMan->mpTreesEnd) {
            pMan->mpTreesBegin = pEnd + 1;
            pEntry = pNew;
            if (pEnd != 0) {
                *pEnd = (u32)pNew;
                vc_v_p9(pNew, 0);
            }
        } else {
            FUN_00aea5d0_p9(pEnd, (void **)&pOut);
            pEntry = (Scatter *)pOut;
        }
        vc_v_p9(pEntry, 0x5c);
        if (*(int *)((char *)pEntry + 0x16c) != 1)
            *(int *)((char *)pEntry + 0x16c) = 1;
        {
            float mat[3];
            translateTransform_p9(mat, (const char *)(pMan->mpSpots + index * 0xe),
                               &this->mSpawnX);
            char *pTr = (char *)pEntry + 0x34;
            ((F1p_s00b0_9570)VS_s00b0_9570(pTr, 0x38))(pTr, &mat[1]);
            float q[4];
            rw__math__fpu__QuaternionFromMatrix33_p9(q, mat, 0);
            ((F1p_s00b0_9570)VS_s00b0_9570(pTr, 0x3c))(pTr, q);
            ((char *)pEntry)[0xa9] = 1;
            ((char *)pEntry)[0xab] = 0;
            ((char *)pEntry)[0xa4] = 1;
            ((char *)pEntry)[0xa3] = 1;
            FUN_00b53940_p9(pTr);
            FUN_00b3d310_p9();
            FUN_00b5a260_p9(pTr, 0);
            FUN_00b54200_p9(pTr);
            FUN_00b54230_p9(pTr, 0);
            int *pQ = (int *)vc_p_p9(pTr, 0x98);
            if (pQ[0] != (int)0x4f15bfb5 || pQ[1] != (int)0x00b1b104 || pQ[2] != 0)
                vc_vu_p9(pTr, 0x94, 0x0156741c);
            u32 *pF = (u32 *)vc_p_p9(pTr, 0xac);
            if (pF != 0) {
                pF[1] |= 1;
                ((F1i_p9)VS_s00b0_9570(pF, 0x16c))(pF, 1);
                cSPTransformOps__Assign_p9(pF + 2, mat);
                FUN_00c3f8b0_p9(1, 0);
                *(int *)((char *)pEntry + 0x158) = (int)this->mSelB;
                *(int *)((char *)pEntry + 0x15c) = (int)this->mSelA;
                *(int *)((char *)pEntry + 0x160) = (int)this->mSelC;
                *(int *)((char *)pEntry + 0x150) = -1;
            }
        }
    }
done:
    {
        u32 selA = this->mSelA;
        u32 selC = this->mSelC;
        u32 selB = this->mSelB;
        pMan = FUN_00b3d440_p9();
        int *pVec = (int *)FUN_00b04ba0_p9(pMan, selA, selB);
        if (pVec != 0 && selC < (u32)((pVec[1] - *pVec) >> 2)) {
            int pObj = *(int *)(*pVec + selC * 4);
            if (pObj != 0) {
                u64 mask = 1ULL << index;
                *(u32 *)(pObj + 0x48) &= ~(u32)mask;
                *(u32 *)(pObj + 0x4c) &= ~(u32)(mask >> 32);
            }
        }
    }
    {
        u32 spot = this->mpIndexA[index];
        u32 arg = this->mpIndexB ? this->mpIndexB[0] : 0;
        pMan = FUN_00b3d440_p9();
        FUN_00b023d0_p9(pMan, (void *)spot, arg, 0);
    }
    {
        void *pSys = EA__Audio__GetSystemAT_p9();
        void *pSnd;
        if (pSys == 0)
            pSnd = 0;
        else
            pSnd = vc_p_p9(pSys, 0x20);
        Start3dSoundByName_p9(0xbd19551a, pSnd, this->mSoundX, this->mSoundY, this->mSoundZ);
    }
    if (pEntry != 0)
        vc_v_p9(pEntry, 4);
    return pEntry;
}

// @ 0x00b09b00
void Mgr::RemoveAllNouns()
{
    u32 *pIt = mpTreesBegin;
    if (pIt != mpTreesEnd) {
        do {
            u32 h = *pIt;
            void *pNM = SP__NounManager(h);
            SP__cGameNounManager__RemoveNoun(pNM, h);
            if (pIt + 1 < mpTreesEnd)
                eastl__copy_backward(pIt + 1, mpTreesEnd, pIt);
            mpTreesEnd--;
            u32 last = *mpTreesEnd;
            if (last != 0)
                ((F0v_s00b0_9570)VS_s00b0_9570((void *)last, 4))((void *)last);
        } while (pIt != mpTreesEnd);
    }
    mFlagsB &= 0xffffffef;
    mCount1659c = 0;
    FUN_00b06cd0(this);
}

// @ 0x00b09b80
Scatter *Mgr::PlaceIndexed(Scatter *pTreeRaw, u32 index, u32 param_3)
{
    u64 mask = 1ULL << index;
    const TreeBits *pBits = (const TreeBits *)pTreeRaw;
    if ((((u32)mask & pBits->mMaskLo) | ((u32)(mask >> 32) & pBits->mMaskHi)) == 0)
        return 0;
    Mgr *pSub = (Mgr *)FUN_00b03320_tc(this, pBits->mSeedZ,
                                       pBits->mSeedX,
                                       pBits->mSeedY);
    Scatter *pFound = (Scatter *)0;
    if (pSub != 0) {
        u32 cnt = FUN_00b058f0_tc(pSub);
        if (index < cnt)
            pFound = pSub->Place(index, (int *)param_3);
    }
    return pFound;
}

// @ 0x00b09bf0
void Mgr::UpdateFruit(int period)
{
    float dt = (float)period * 0.001f;
    if ((*(u32 *)0x0167bbe4 & 1) == 0) {
        *(u32 *)0x0167bbe4 |= 1;
        SetSeed(0xffffffff);
    }
    char buf[0x100];
    int *pAnchors[3] = { (int *)buf, (int *)buf, (int *)buf + 0x40 };
    int *pBegin = (int *)buf;
    int *pEnd = pBegin;
    (void)pAnchors;
    if ((mFlagsB >> 3 & 1) != 0 || (mFlagsB >> 5 & 1) != 0) {
        int *pApp = (int *)SP__App();
        int *pV = (int *)vc_p_s00b0_9570(pApp, 0x50);
        void *pViewer = vc_p_s00b0_9570(pV, 0x1c);
        float loc[3] = { *(float *)0x0167af5c, *(float *)0x0167af60, *(float *)0x0167af64 };
        float dir[3] = { *(float *)0x0167af5c, *(float *)0x0167af60, *(float *)0x0167af64 };
        if (pViewer != 0) {
            SP__cViewer__GetCameraLocationInfo(pViewer, loc, dir, 0, 0);
            void *pPM = SP__PlanetModel(dir, loc);
            SP__cPlanetModel__DirectionToSurfacePosition(pPM, dir, loc);
            FUN_00b09340(this, 200.0f, &pBegin, 0, 0);
            pEnd = pAnchors[1];
        }
    }
    int n = (int)((char *)pEnd - (char *)pBegin) >> 2;
    if ((mFlagsB >> 5 & 1) != 0 && n > 0) {
        for (int i = 0; i < n; i++) {
            int e = pBegin[i];
            float v = *(float *)(e + 0x150) - dt;
            *(float *)(e + 0x150) = v;
            if (v < 0.0f) {
                SetSeed(0xffffffff);
                float f = (float)(RandomDoubleUniform() * 2.0 - 1.0);
                if (f > 1.0f) f = 1.0f;
                if (f < -1.0f) f = -1.0f;
                *(float *)(e + 0x150) = f + *(float *)0x015673a0;
                int *pVec = (RandomDoubleUniform() >= 0.5) ? (int *)(e + 0xf4)
                                                           : (int *)(e + 0x9c);
                if (*pVec != pVec[1]) {
                    int cnt = (pVec[1] - *pVec) >> 2;
                    int left = cnt;
                    int t;
                    u32 lo = 0;
                    u32 hi = 0;
                    for (;;) {
                        if (left == 0)
                            goto nextA;
                        left--;
                        u32 r = RandomUint32Uniform((u32)cnt);
                        t = *(int *)(*pVec + r * 4);
                        lo = *(u32 *)(t + 0x48);
                        hi = *(u32 *)(t + 0x4c);
                        if (hi > lo)
                            break;
                    }
                    u32 x = (lo + 1) & ~lo;
                    int b;
                    if (x == 0) {
                        b = 0x20;
                    } else {
                        b = 1;
                        u32 u = x;
                        if ((u & 0xffff) == 0) { b = 0x11; u >>= 16; }
                        if ((unsigned char)u == 0) { b += 8; u >>= 8; }
                        if ((u & 0xf) == 0) { b += 4; u >>= 4; }
                        if ((u & 3) == 0) { b += 2; u >>= 2; }
                        b -= (int)(u & 1);
                    }
                    u64 m = 1ULL << b;
                    *(u32 *)(t + 0x48) = (u32)m | lo;
                    *(u32 *)(t + 0x4c) = (u32)(m >> 32) | hi;
                    Mgr *pSub;
                    do {
                        pSub = (Mgr *)FUN_00b03320_tc(this, *(u32 *)(t + 0x58),
                                                      *(u32 *)(t + 0x50),
                                                      *(u32 *)(t + 0x54));
                    } while (pSub == 0);
                    {
                        u32 spot = pSub->mpIndexA[b];
                        u32 arg = pSub->mpIndexB[0];
                        Mgr *pM2 = FUN_00b3d440_s00b0_9570();
                        FUN_00b023d0(pM2, (void *)spot, arg, 0x3f800000);
                    }
                }
            }
        nextA:;
        }
    }
    if ((mFlagsB >> 3 & 1) != 0 && n > 0) {
        for (int i = 0; i < n; i++) {
            int e = pBegin[i];
            float v = *(float *)(e + 0x14c) - dt;
            *(float *)(e + 0x14c) = v;
            if (v < 0.0f) {
                SetSeed(0xffffffff);
                *(float *)(e + 0x14c) = FUN_00b00000f();
                int *pVec = (RandomDoubleUniform() >= 0.5) ? (int *)(e + 0xf4)
                                                           : (int *)(e + 0x9c);
                int cnt = (pVec[1] - *pVec) >> 2;
                int left = cnt;
                int t;
                for (;;) {
                    if (left == 0)
                        goto nextB;
                    left--;
                    u32 r = RandomUint32Uniform((u32)cnt);
                    t = *(int *)(*pVec + r * 4);
                    if (*(u32 *)(t + 0x48) != 0)
                        break;
                }
                {
                    u32 lo = *(u32 *)(t + 0x48);
                    int b;
                    if (lo == 0) {
                        b = 0x20;
                    } else {
                        b = 1;
                        u32 u = lo;
                        if ((u & 0xffff) == 0) { b = 0x11; u >>= 16; }
                        if ((unsigned char)u == 0) { b += 8; u >>= 8; }
                        if ((u & 0xf) == 0) { b += 4; u >>= 4; }
                        if ((u & 3) == 0) { b += 2; u >>= 2; }
                        b -= (int)(u & 1);
                    }
                    PlaceIndexed((Scatter *)t, (u32)b, 1);
                }
            }
        nextB:;
        }
    }
    if (pBegin != 0 && pBegin[-1] != 0)
        operator_delete_array(pBegin);
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

// @ 0x00b0a0c0
void Mgr::QueryTrees(float *pPos, void **ppVec, u32 mask, float radius, int sort, float *pSortPos, int needFruit)
{
    if (*(u32 *)((char *)mpGrid + 0x24) == *(u32 *)((char *)mpGrid + 0x28))
        return;
    {
        float org[3];
        void *pPM = SP__PlanetModel(org, pPos);
        SP__cPlanetModel__DirectionToSurfacePosition(pPM, org, pPos);
        int *pList = 0;
        int found = 0;
        FUN_00b97280(&pList, 0x100, (u32 *)&found);
        int n = FUN_00702760(mpGrid, radius, org, 0x100, (void *)pList);
        FUN_00b98ea0((void *)n, 0);
        Pairs *pVec = (Pairs *)ppVec;
        memcpy(pVec->mpBegin, pVec->mpEnd, 0);
        pVec->mpEnd += (int)(((char *)pVec->mpEnd - (char *)pVec->mpBegin) >> 2) * -4;
        FUN_00d01790(ppVec, (u32)n);
        for (int i = 0; i < n; i++) {
            int e = pList[i];
            if (*(char *)(e + 0x7c) != 0)
                continue;
            u32 kind;
            u32 key = *(u32 *)(e + 0x58);
            if (key == 0x29c388a) kind = 2;
            else if (key == 0x3a8be428) kind = 1;
            else kind = (-(u32)(key != 0x6d60a1cc) & 0xfffffffd) + 4;
            if ((mask & kind) == 0)
                continue;
            if (needFruit != 0 && *(int *)(e + 0x48) == 0)
                continue;
            float dz = pPos[2] - *(float *)(e + 0x18);
            float dy = pPos[1] - *(float *)(e + 0x14);
            float dx = pPos[0] - *(float *)(e + 0x10);
            float r = *(float *)(e + 0x6c) + radius;
            if (dx * dx + dy * dy + dz * dz >= r * r)
                continue;
            if (pVec->mpEnd < pVec->mpCap) {
                int *pSlot = pVec->mpEnd;
                pVec->mpEnd = pSlot + 1;
                if (pSlot != 0)
                    *pSlot = e;
            } else {
                FUN_00b96600(ppVec, (u32 *)&e);
            }
        }
        if (sort != 0 && ((char *)pVec->mpEnd - (char *)pVec->mpBegin) >> 2 > 1) {
            float *p = (pSortPos != 0) ? pSortPos : org;
            FUN_00b06340(pVec->mpBegin, pVec->mpEnd, p[0], p[1], p[2]);
        }
        if (pList != 0 && pList[-1] != 0)
            operator_delete_array(pList);
    }
}

// @ 0x00b0a310
void Stream::ReadTreeRefVector(void *pThis, void *pVecRaw)
{
    char *pVec = (char *)pVecRaw;
    FUN_00b07140(pVec, *(void **)(pVec + 0), *(void **)(pVec + 4));
    u32 count = 0;
    Stream *pS = (Stream *)pThis;
    Stream *pO = pS->GetOuter();
    void *pIO = pO->GetIO();
    ReadInt32_s00b0_9570(pIO, &count, 1, 0);
    FUN_00b060f0(pVec, count);
    for (u32 i = 0; i < count; i++) {
        TreeData tmp;
        ((F1p_s00b0_9570)VS_s00b0_9570(&tmp, 0x14))(&tmp, pThis);
        TreeData *pEnd = *(TreeData **)(pVec + 4);
        if (pEnd < *(TreeData **)(pVec + 8)) {
            *(TreeData **)(pVec + 4) = pEnd + 1;
            if (pEnd != 0)
                FUN_00b03680(pEnd, &tmp);
        } else {
            FUN_00b07190(pVec, (u32)pEnd, &tmp);
        }
        *(int *)&tmp = 0x145c678;
        *(int *)((char *)&tmp + 4) = 0x145c668;
        int *pX = *(int **)((char *)&tmp + 0x6c);
        if (pX != 0)
            ((F0v_s00b0_9570)VS_s00b0_9570(pX, 4))((void *)pX);
    }
    pS->EndRead();
}

// 0x00b0a3f0 (byte-exact lifted version: match/slices/s00b0a3f0/s00b0a3f0.cpp)
Scatter &Scatter::AssignFrom(const Scatter &src)
{
    mX = src.mX;
    mY = src.mY;
    mZ = src.mZ;
    mSpread = src.mSpread;
    mFlag40 = src.mFlag40;
    mSmall0 = src.mSmall0;
    mSmall1 = src.mSmall1;
    mSmall2 = src.mSmall2;
    mTimerA = src.mTimerA;
    mTimerB = src.mTimerB;
    mBig0 = src.mBig0;
    mBig1 = src.mBig1;
    mBig2 = src.mBig2;
    return *this;
}

// @ 0x00b0a530
ScatterE *CopyBackwardScatterE(const ScatterE *pFirst, ScatterE *pLast, ScatterE *pOut)
{
    if (pLast != pFirst) {
        do {
            pLast--;
            pOut--;
            pOut->mKey = pLast->mKey;
            pOut->mBody.AssignFrom(pLast->mBody);
        } while (pLast != pFirst);
    }
    return pOut;
}

// @ 0x00b0a590
void BeamMgr2::UpdateState()
{
    uint32_t i = 0;
    if (state != 0 && state != 1)
        state = 0;
    RemoveAllNouns();
    if (state == 0) {
        items.F06d90(g_15673b0);
        uint32_t n = items.size();
        for (; i < n; ++i) {
            if (items[i].mpObject == 0) {
                RefElem& slot = items[i];
                slot = CreateItem();
                Key3 key;
                key.a = 0xb5bc5ab6;
                key.b = 0x00e6bce5;
                key.c = 0;
                ((ItemObj*)items[i].mpObject)->spatial.SetKey(&key);
                ((ItemObj*)items[i].mpObject)->spatial.flags |= 0x80;
            }
        }
    }
    if (state == 1) {
        if (mode & 0x10) {
            mode &= ~0x10u;
            objMask = 0;
            FUN_00b06cd0();
        }
        if (mode & 1)
            mode |= 0x10;
        else
            mode &= ~0x10u;
        if (mode & 0x10) {
            objMask = 6;
            return FUN_00b091d0();
        }
    }
}

// @ 0x00b0aee0
PoolElem_s00b0_a590* PoolVec::erase(PoolElem_s00b0_a590* first, PoolElem_s00b0_a590* last)
{    PoolElem_s00b0_a590* const pEnd = mpEnd;
    PoolElem_s00b0_a590* const position = copy_forward(last, pEnd, first);
    destroy_values(position, mpEnd);
    mpEnd -= last - first;
    return first;
}

// @ 0x00b0af40
void PoolVec::insert(PoolElem_s00b0_a590* position, uint32_t n, const PoolElem_s00b0_a590* value)
{
    if (n <= (uint32_t)(mpCap - mpEnd)) {
        if (n != 0) {
            const PoolElem_s00b0_a590 temp = *value;
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            PoolElem_s00b0_a590* const pEnd = mpEnd;
            if (n < nExtra) {
                construct_cursor((void**)&value, mpEnd - n, mpEnd, mpEnd, position);
                mpEnd += n;
                copy_backward(position, pEnd - n, pEnd);
                assign_range(position, position + n, &temp);
            } else {
                fill_n_copy(mpEnd, n - nExtra, &temp, position);
                mpEnd += n - nExtra;
                construct_cursor((void**)&position, position, pEnd, mpEnd, position);
                mpEnd += nExtra;
                assign_range(position, pEnd, &temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        PoolElem_s00b0_a590* const pNewData = nNewSize
            ? (PoolElem_s00b0_a590*)EAAlloc(nNewSize * 0x24, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
            : 0;
        PoolElem_s00b0_a590* pNewEnd = construct_range(mpBegin, position, pNewData);
        destroy_range(mpBegin, position, pNewData);
        fill_n_copy(pNewEnd, n, value, pNewEnd);
        PoolElem_s00b0_a590* const tail = pNewEnd + n;
        pNewEnd = construct_range(position, mpEnd, tail);
        destroy_range(position, mpEnd, tail);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete_array(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCap = pNewData + nNewSize;
    }
}

// @ 0x00b0b150
void BeamMgr2::Init()
{
    if (!(mode & 1))
        return;
    if (!(mode & 2)) {
        FUN_00b02120();
        void* pm = PlanetModel_s00b0_a590();
        PlanetObj* p = pm ? *(PlanetObj**)((char*)pm + 0x24) : 0;
        if (p && p->GetId()) {
            uint32_t id = p->GetId();
            GetPropertyAsKey(id, 0x463cda3, &g_156741c_s00b0_a590);
            GetPropertyAsKey(id, 0x463d9ba, &g_1567410_s00b0_a590);
            uint32_t tmp = 0;
            GetPropertyAsKeyInstance(id, 0x463cdb4, &tmp);
            g_15673a8 = tmp;
            g_15673ac = 0;
        }
        uint32_t n = items2.size();
        while (n < g_15673b4) {
            ItemObj* it = CreateItem();
            RefElem ref(it);
            items2.push_back(ref);
            ++n;
        }
        uint32_t m = nouns.size();
        while (m < g_15673b8) {
            NounObj* nw = GetNounManager_s00b0_a590()->CreateNoun(0x2e96892);
            RefElem ref(nw);
            nw->Init();
            nouns.push_back(ref);
            ++m;
        }
        if (bitvec.size() < 0x40) {
            uint32_t* nb = (uint32_t*)EAAlloc(0x100, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            memcpy(nb, bitvec.mpBegin, (char*)bitvec.mpEnd - (char*)bitvec.mpBegin);
            if (bitvec.mpBegin && ((int*)bitvec.mpBegin)[-1] != 0)
                operator_delete_array(bitvec.mpBegin);
            uint32_t cnt = bitvec.size();
            bitvec.mpBegin = nb;
            bitvec.mpEnd = nb + cnt;
            bitvec.mpCap = nb + 0x40;
        }
    }
    if ((mode & 4) || !(mode & 2))
        UpdateState();
    mode |= 2;
    mode &= ~4u;
}

// @ 0x00b0bb50
PaintMgr::~PaintMgr()
{
    void* grid = mpGrid;
    mVtable = gVtablePaint;
    mVtableSub = gVtablePaintSub;
    mVtable3 = gVtablePaint3;

    if (grid) {
        ((HierGrid*)grid)->~HierGrid();                  // 0x00750310
        operator delete(grid);
    }

    mItems.DestroyRange(mItems.mpBegin, mItems.mpEnd);   // 0x00b0aee0
    mVec5.Destroy();                                     // 0x00ae6970
    mVec4.Destroy();
    mVec3.Destroy();
    mItems.DestroyStorage();                             // 0x00b002a0
    mVec1.Destroy();

    mScatter.DestroyElements(mScatter.mpBegin, mScatter.mpEnd);   // 0x00b051f0
    void* scatterBuf = mScatter.mpBegin;
    if (scatterBuf && scatterBuf != mScatter.mpInline)
        operator delete(scatterBuf);

    ((PaintPool*)mPoolC)->ReleaseChain(mpPoolCChain);    // 0x00b04350

    mEnt.DestroyValues(mEnt.mpBegin, mEnt.mpEnd);        // 0x005f3680
    if (mEnt.mpBegin && ((uint32_t*)mEnt.mpBegin)[-1])
        operator delete(mEnt.mpBegin);

    mSpatial.ResetRange(mSpatial.mpBegin, mSpatial.mpEnd);     // 0x00b006f0
    if (mSpatial.mpBegin && ((uint32_t*)mSpatial.mpBegin)[-1])
        operator delete(mSpatial.mpBegin);

    ((PaintPool*)mPoolB)->WalkChain(mpPoolBChain);       // 0x00b04420
    ((PaintPool*)mPoolA)->ReleaseChain(mpPoolAChain);    // 0x00b04350

    if (mHandler) {
        RemoveMessageHandler((void*)mHandler, mHandlerArg0, mHandlerArg1, mHandlerArg2, mHandlerArg3);
        mHandler = 0;
    }

    ((GonzagoSub*)&mVtableSub)->~GonzagoSub();           // 0x00b5b9a0
    mVtable = gVtablePaintDtor;
}

// @ 0x00b0bd10
void Elem24Vec::Resize(unsigned int n)
{
    if (n > (unsigned int)(mpEnd - mpBegin)) {
        Elem24 tmp;
        InsertN(mpEnd, n - (unsigned int)(mpEnd - mpBegin), tmp);
    } else {
        DestroyRange(mpBegin + n, mpEnd);
    }
}

// @ 0x00b0bdb0
PaintMgr::PaintMgr()
{
    mVtable = gVtablePaintBase;
    ((GonzagoSub*)&mVtableSub)->Construct();
    mVtableSub = gVtablePaintSub;
    mVtable = gVtablePaint;
    mVtable3 = gVtablePaint3;

    mHandler = 0;
    mHandlerArg0 = 0;
    mHandlerArg1 = 0;
    mHandlerArg2 = 0;
    mHandlerArg3 = 0;

    ((PaintPool*)mPoolA)->Construct();                   // 0x00b05a80
    ((PaintPool*)mPoolB)->ConstructAlt();                // 0x00b05ae0

    void* p = mSpatial.mBuf;
    mSpatial.mpBegin = p;
    mSpatial.mpEnd = p;
    p = (char*)p + 0x400;
    mSpatial.mpCap = p;
    mSpatial.mFlag = 0;

    p = mEnt.mBuf;
    mEnt.mpBegin = p;
    mEnt.mpEnd = p;
    p = (char*)p + 0x80;
    mEnt.mpAlloc = 0;
    mEnt.mpCap = p;

    mObjMask = 0;
    ((PaintPool*)mPoolC)->Construct();                   // 0x00b05a80

    p = mScatter.mBuf;
    mScatter.mpInline = (ScatterE_s00b0_b3d0*)p;
    mScatter.mpEnd = (ScatterE_s00b0_b3d0*)p;
    mScatter.mpBegin = (ScatterE_s00b0_b3d0*)p;
    p = (char*)p + 0x19a800;
    mScatter.mpCap = (ScatterE_s00b0_b3d0*)p;

    mUnk1b8e10 = 0;
    mVec1.mpAlloc = 0;
    p = mVec1.mBuf;
    mVec1.mpBegin = p;
    mVec1.mpEnd = p;
    p = (char*)p + 0x100;
    mVec1.mpCap = p;

    mUnk1b8f2c = -1;
    mItems.mpBegin = 0;
    mItems.mpEnd = 0;
    mItems.mpCap = 0;

    mVec3.mpAlloc = 0;
    p = mVec3.mBuf;
    mVec3.mpBegin = p;
    mVec3.mpEnd = p;
    p = (char*)p + 0x100;
    mVec3.mpCap = p;

    p = mVec4.mBuf;
    mVec4.mpBegin = p;
    mVec4.mpEnd = p;
    p = (char*)p + 0x100;
    mVec4.mpCap = p;
    mVec4.mpAlloc = 0;

    p = mVec5.mBuf;
    mVec5.mpBegin = p;
    mVec5.mpEnd = p;
    p = (char*)p + 0x1000;
    mVec5.mpCap = p;
    mVec5.mpAlloc = 0;

    mFlags1 = 0;
    mUnk1ba190 = 0;
    mFlags1 &= ~3u;

    void* mem = EaAllocate(0x84, "Simulator/HierGrid", 0, 0, 0, 0);
    mpGrid = mem ? new (mem) HierGrid() : 0;

    mItems.Resize(1);
}

// @ 0x00b0bfa0
void ScatterVec::InsertGrow(ScatterE_s00b0_b3d0* pos, const ScatterE_s00b0_b3d0& v)
{
    if (mpEnd != mpCap) {
        ScatterE_s00b0_b3d0* src = (ScatterE_s00b0_b3d0*)&v;
        if (src >= pos && src < mpEnd)
            src = (ScatterE_s00b0_b3d0*)((char*)src + sizeof(ScatterE_s00b0_b3d0));
        new ((void*)mpEnd) ScatterE_s00b0_b3d0(*(mpEnd - 1));
        ScatterCopyBackward(pos, mpEnd - 1, mpEnd);
        pos->mKey = src->mKey;
        pos->mPayload.AssignFrom(src->mPayload);
        ++mpEnd;
    } else {
        unsigned int count = (unsigned int)(mpEnd - mpBegin);
        unsigned int cap = count ? count * 2 : 1;
        ScatterE_s00b0_b3d0* buf = (ScatterE_s00b0_b3d0*)EaAllocate(cap * sizeof(ScatterE_s00b0_b3d0), "Simulator", 0, 0, 0, 0xd1);
        if (buf) {
            ScatterCopyRange(mpBegin, pos, buf);
            ScatterE_s00b0_b3d0* newpos = (ScatterE_s00b0_b3d0*)ScatterFillRange(mpBegin, pos, buf);
            if (newpos) {
                newpos->mKey = v.mKey;
                new (newpos) ScatterE_s00b0_b3d0(*(ScatterE_s00b0_b3d0*)&v);
            }
            ScatterCopyRange(pos, mpEnd, newpos + 1);
            ScatterE_s00b0_b3d0* newend = (ScatterE_s00b0_b3d0*)ScatterFillRange(pos, mpEnd, newpos + 1);
            if (mpBegin && mpBegin != mpInline)
                operator delete(mpBegin);
            mpBegin = buf;
            mpEnd = newend;
            mpCap = buf + cap;
        }
    }
}

// @ 0x00b0c110
ScatterE_s00b0_b3d0* ScatterVec::Insert(ScatterE_s00b0_b3d0* pos, const ScatterE_s00b0_b3d0& v)
{
    unsigned int index = (unsigned int)(pos - mpBegin);
    if (pos == mpEnd && mpEnd != mpCap) {
        ScatterE_s00b0_b3d0* p = mpEnd;
        mpEnd = p + 1;
        new (p) ScatterE_s00b0_b3d0(v);
    } else {
        InsertGrow(pos, v);
    }
    return mpBegin + index;
}

// @ 0x00b0c190
void cPlanetManager::Unload(bool bUnloadRecords)
{
    mpCurrentKey = (const cObjectKey*)-1;
    if ((mFlags >> 1) & 1) {
        mpHierGrid->Shutdown();
        ClearContainer(&mContainerA, 0, 0);
        ClearContainer(&mContainerB, 0, 0);
        if (mTracked.mCount != 0) {
            cTrackedTreeNode* pEnd = mTracked.End();
            for (cTrackedTreeNode* pNode = mTracked.First(); pNode != pEnd;
                 pNode = pNode->Next()) {
                if (pNode->mpObject != 0)
                    pNode->mpObject->ReleaseRef(true);
            }
            mTracked.Reset();
        }
        if (mEffects.mBegin != mEffects.mEnd)
            mEffects.Clear();
        for (cSlotObject** pp = mTrackedObjects.mBegin; pp != mTrackedObjects.mEnd;
             pp = UnloadTrackedObject(pp)) {
        }
        for (; mNouns.mBegin != mNouns.mEnd; mNouns.EraseFirst())
            GetNounManager_s00b0_c190()->RemoveNoun(*mNouns.mBegin);
        for (; mExtraNouns.mBegin != mExtraNouns.mEnd; mExtraNouns.EraseFirst())
            GetNounManager_s00b0_c190()->RemoveNoun(*mExtraNouns.mBegin);
        ShutdownSelection(this);
        mFlags &= ~2u;
    }
    if (bUnloadRecords) {
        DestroyRecordRange(mRecords.mBegin, mRecords.mEnd);
        CollapseRecordRange(mRecords.mBegin, mRecords.mEnd);
    }
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

// @ 0x00b0c570
cPlanetRecord* cPlanetRecordTable::Insert(cPlanetRecord* pPos, const uint* pKey)
{
    cPlanetRecord* pEnd = mEnd;
    cPlanetRecord* pFound;
    if (pPos == pEnd || *pKey >= pPos->mKey)
        pFound = LowerBoundRecords(pPos, pEnd, pKey, mbSorted);
    else
        pFound = LowerBoundRecords(mBegin, pPos, pKey, mbSorted);
    if (pFound == pEnd || *pKey < pFound->mKey)
        pFound = InsertRecord(pFound, pKey);
    return pFound;
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

// @ 0x00c6fec0
void* VisiblePlanet::Cast(unsigned type)
{
    if (type != 0x3275872) {
        void* r = ((void* (__thiscall*)(void*, unsigned))FUN_00b18460)((uchar*)this + 0xd4, type);
        if (r == 0) return ((void* (__thiscall*)(void*, unsigned))FUN_00c884f0)(this, type);
        return r;
    }
    return this;
}

// @ 0x00c6ff00
bool VisiblePlanet::Write(void* pArchive)
{
    bool b = ((GameDataPart*)mGameData_d4)->Write(pArchive) && ((SpatialObjPart*)this)->Write(pArchive);
    VarListSerializer ser(this, &DAT_01578890, 0x1a80d26);
    return b && ser.Serialize(pArchive);
}

// @ 0x00c6ffd0
void* VisiblePlanet::Cast2(unsigned type)
{
    if (type != 0x44462a6) {
        void* r = ((void* (__thiscall*)(void*, unsigned))FUN_00b18460)((uchar*)this + 0xd4, type);
        if (r == 0) return ((void* (__thiscall*)(void*, unsigned))FUN_00c884f0)(this, type);
        return r;
    }
    return this;
}

// @ 0x00c70010
bool VisiblePlanet::Write2(void* pArchive)
{
    bool b = ((GameDataPart*)mGameData_d4)->Write(pArchive) && ((SpatialObjPart*)this)->Write(pArchive);
    VarListSerializer ser(this, &DAT_01578ba0, 0x1a80d26);
    if (b && ser.Serialize(pArchive)) return true;
    return false;
}

// @ 0x00c70090
bool VisiblePlanet::Read(void* pArchive)
{
    bool b = ((GameDataPart*)mGameData_d4)->Read(pArchive) && ((SpatialObjPart*)this)->Read(pArchive);
    VarListSerializer ser(this, &DAT_01578ba0, 0x1a80d26);
    if (b && ser.Read(pArchive)) return true;
    return false;
}

// @ 0x00c707f0
void* SimPlanet::GetNameRow(bool wantCol0) const
{
    PlanetRecord* r = mRecord_13c;
    if (!r) return wantCol0 ? g_NameRows[0].col0 : g_NameRows[0].col1;
    char t = r->mRingType_ac;
    if (t < 0) return 0;
    int i = (int)t;
    if (r->mType_28 == 1) return g_NameRows[i].col2;
    return wantCol0 ? g_NameRows[i].col0 : g_NameRows[i].col1;
}

// @ 0x00c70860
void SimPlanet::Func70860()
{
    mRecord_13c->GetWorld()->Func70860();
}

// @ 0x00c70880
int SimPlanet::GetPlanetType() const
{
    return mRecord_13c ? mRecord_13c->mType_28 : 2;
}

// @ 0x00c708a0
void* SimPlanet::GetOrbit() const
{
    if (mRecord_13c) return (uchar*)mRecord_13c + 0x30;
    return &DAT_015b4500;
}

// @ 0x00c708c0
void SimPlanet::SetOrbit(void* pOrbit)
{
    if (!mRecord_13c) return;
    mRecord_13c->mOrbit_30 = *(Orbit*)pOrbit;
    mRecord_13c->mOrbit_30.Recalc();
}

// @ 0x00c708f0
bool SimPlanet::IsRotationNull() const
{
    return mRecord_13c ? mRecord_13c->mRotationIsNull_98 : true;
}

// @ 0x00c70910
void SimPlanet::SetRotationNull(bool val)
{
    if (mRecord_13c) mRecord_13c->mRotationIsNull_98 = val;
}

// @ 0x00c70930
void* SimPlanet::GetRotationAxis() const
{
    if (mRecord_13c) return (uchar*)mRecord_13c + 0x9c;
    return &DAT_015787f0;
}

// @ 0x00c70950
void SimPlanet::SetRotationAxis(Vec3_s00c6_f6e0* axis)
{
    if (!mRecord_13c) return;
    mRecord_13c->mRotationAxis_9c = *axis;
}

// @ 0x00c70980
float SimPlanet::GetRotationPeriod() const
{
    return mRecord_13c ? mRecord_13c->mRotationPeriod_a8 : 1.0f;
}

// @ 0x00c709b0
void SimPlanet::SetRotationPeriod(float v)
{
    if (mRecord_13c) mRecord_13c->mRotationPeriod_a8 = v;
}

// @ 0x00c72c60
void SP::cPlanet::AddDebugInfo(eastl::basic_string<char, eastl::allocator> * str)
{
    char* s = (char*)this;
    void* pd = *(void**)(s + 0x13c);
    StrAppendSprintf(str, "\nPlanet Name: %S", ((void**)((Op*)pd)->Mecdba0())[0]);

    pd = *(void**)(s + 0x13c);
    if (pd != 0 && ((Op*)pd)->Mb8dab0() == 5) {
        void* gd = (void*)(s + 0xd4);
        void* slot = (*(void*(__thiscall**)(void*))((char*)vtbl(gd) + 0x4c))(gd);
        void* sm = SP_StarManager_00b3d2a0();
        void* emp = ((Op*)sm)->Mba9370(slot);
        if (emp != 0)
            StrAppendSprintf(str, "\nArchetype: %s\n", ((Op*)emp)->Mc30eb0());
    }
}

// @ 0x00c72ce0
void SP::cVisiblePlanet::AddDebugInfo(eastl::basic_string<char, eastl::allocator> * str)
{
    StrAppendSprintf(str, "\nVisiblePlanet");
}

// @ 0x00c72d70
bool PlanetCls::FUN_00c72d70(int key)
{
    char* s = (char*)this;
    int* end = *(int**)(s + 0x11c4);
    int* r = (int*)FUN_00c72540(*(void**)(s + 0x11c0), end, &key,
                                *(unsigned char*)(s + 0x11d4));
    if (r == end || (unsigned)key < (unsigned)*r || r == (int*)((char*)r + 0xb0))
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
    struct Entry {
        int      f00;   // +0x00
        int      f04;   // +0x04
        int      f08;   // +0x08
        int      f0c;   // +0x0c
        uint16_t f10;   // +0x10
        char     f12;   // +0x12
        char     pad13; // +0x13
        float    f14;   // +0x14
        int      f18;   // +0x18
        int      f1c;   // +0x1c
        int      f20;   // +0x20
        int      f24;   // +0x24
        char     f28;   // +0x28
        char     pad29[3];
    };
    Entry local;
    local.f00 = *(int*)p3;
    local.f04 = d6;
    local.f08 = d7;
    local.f0c = d8;
    local.f10 = w4;
    local.f12 = b2;
    local.f14 = 0.0f;
    local.f18 = 0;
    local.f1c = 0;
    local.f20 = 0;
    local.f24 = 0;
    local.f28 = (char)((1 << ((b9 != 0) + 3)) | (-(b5 != 0) & 2) | 0x20);

    int* vec = (int*)(s + 0x134);
    if ((unsigned)vec[1] < (unsigned)vec[2]) {
        int* slot = (int*)vec[1];
        vec[1] = (int)((char*)slot + 0x2c);
        if (slot != 0) {
            ((VecSlot_00ac9200*)slot)->Insert(&local);
        }
    } else {
        ((VecBase_00acb810*)vec)->GrowInsert((void*)vec[1], &local);
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
    EaVec3* v = (EaVec3*)(*(char**)((char*)this + 0x13c) + 0xbc);
    v->erase(v->begin, v->end);
}

// @ 0x00c73330
void PlanetCls::FUN_00c73330()
{
    EaVec3* v = (EaVec3*)(*(char**)((char*)this + 0x13c) + 0xd0);
    v->erase(v->begin, v->end);
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
    struct Key8 { int k; char c; };
    int* r = (int*)FUN_00d01260(beg, end, key, *(unsigned char*)(s + 0x14));
    if (r == end || (unsigned)*key < (unsigned)*r) {
        Key8 k;
        k.k = *key;
        k.c = 0;
        if (r == end || (unsigned)*r <= (unsigned)k.k) {
            r = (int*)FUN_00d01260(r, end, &k, *(unsigned char*)(s + 0x14));
        } else {
            r = (int*)FUN_00d01260(beg, r, &k, *(unsigned char*)(s + 0x14));
        }
        if (r == end || (unsigned)k.k < (unsigned)*r)
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
    void* sm = SP_StarManager_00b3d2a0();
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

// @ 0x00c737a0
void FUN_00c737a0(void* self, void* a, void* b)
{
    char* s = (char*)self;
    void* pd = *(void**)(s + 0x13c);
    void* gd = FUN_00b8de30(pd);
    FUN_00a16a90(gd);
    void* sm = SP_StarManager_00b3d2a0(b);
    (void)sm;
    (void)a;
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

// @ 0x00c73f80
void PlanetCls_s00c7_3cb0::FUN_00c73f80(void* key)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[1];
    if (!IsSpeciesScanned(key))
        ((Notifier*)FUN_00b3d4f0(FUN_00ba57f0(key, 2)))->Notify();
    *(char*)m->insert(key) = 1;
}

// @ 0x00c741a0
char PlanetCls_s00c7_3cb0::FUN_00c741a0(void* key)
{
    void* local[2];
    local[0] = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&local[0]);
    EaMap* m = &node->mMaps[2];
    m->find(&local[0], key);
    char* cur = (char*)local[0];
    if (cur == (char*)local[1]) cur = (char*)m->end;
    char* end = (char*)m->end;
    if (cur != end) return *(char*)(cur + 0xc);
    return 0;
}

// @ 0x00c74400
char PlanetCls_s00c7_3cb0::FUN_00c74400(void* key)
{
    void* local[2];
    local[0] = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&local[0]);
    EaMap* m = &node->mMaps[3];
    m->find(&local[0], key);
    char* cur = (char*)local[0];
    if (cur == (char*)local[1]) cur = (char*)m->end;
    char* end = (char*)m->end;
    if (cur != end) return *(char*)(cur + 0xc);
    return 0;
}

// @ 0x00c74550
char PlanetCls_s00c7_3cb0::FUN_00c74550(unsigned* key)
{
    char r = FUN_00c744e0(key);
    if (r == 0) {
        void* y = ((NounMgr*)NounManager())->FUN_00b25f40(*key);
        void* x = FUN_00ba5a60(y, 1);
        ((Notifier*)FUN_00b3d4f0(x))->Notify();
    }
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    char* mp = (char*)node + 0x68;
    *(char*)((PlanetCls_s00c7_3cb0*)mp)->FUN_00c735e0(key) = 1;
    return r;
}

// @ 0x00c745d0
void PlanetCls_s00c7_3cb0::FUN_00c745d0(char flag, void* key)
{
    ComCtxRef* pd = mPData;
    if (pd != 0) {
        EaVec* vec = flag ? &pd->mVecBC : &pd->mVecD0;
        void* end = vec->end;
        void* e = FUN_00ac0d80(vec->begin, end, key);
        if (e != end)
            ((VecEraser*)vec)->eraseElem(e);
        void* k;
        k = ((ComCtxRef*)mPData)->GetCommContext();
        PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
        ScanNode* node = (ScanNode*)s->mScanned.find(&k);
        char* mp = (char*)node + 8;
        ((PlanetCls_s00c7_3cb0*)mp)->FUN_00c73350((int*)key);
    }
}

// @ 0x00c74690
void PlanetCls_s00c7_3cb0::FUN_00c74690(void* key, char b2, char b3)
{
    void* k;
    k = ((ComCtxRef*)mPData)->GetCommContext();
    PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
    ScanNode* node = (ScanNode*)s->mScanned.find(&k);
    EaMap* m = &node->mMaps[0];
    if (b3 != 0 && b2 != 0) {
        if (!SetSpeciesAsScanned(key)) {
            void* e;
            unsigned t = *(unsigned*)((char*)key + 4);
            if (t != 0x2b978c46) {
                if (t != 0x438f6347) goto done;
                e = FUN_00ba57f0(key, 2);
            } else {
                e = FUN_00ba5650(key, 2);
            }
            if (e) ((Notifier*)FUN_00b3d4f0(e))->Notify();
        }
    }
done:
    *(char*)m->insert(key) = b2;
}

// @ 0x00c74730
void PlanetCls_s00c7_3cb0::FUN_00c74730(void* k1, void* k2)
{
    unsigned* a1 = (unsigned*)k1;
    unsigned* a2 = (unsigned*)k2;
    if (a2[0] != a1[0] || a2[1] != a1[1] || a2[2] != a1[2]) {
        ComCtxRef* pd = mPData;
        void* e = FUN_00ac0d80(pd->mVecD0.begin, pd->mVecD0.end, a1);
        if (e != pd->mVecD0.end) {
            ((unsigned*)e)[0] = a2[0];
            ((unsigned*)e)[1] = a2[1];
            ((unsigned*)e)[2] = a2[2];
        }
        if (SetSpeciesAsScanned(a1)) {
            void* k;
            k = ((ComCtxRef*)mPData)->GetCommContext();
            PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
            ScanNode* node = (ScanNode*)s->mScanned.find(&k);
            *(char*)node->mMaps[0].insert(a2) = 1;
        }
        {
            void* k;
            k = ((ComCtxRef*)mPData)->GetCommContext();
            PlanetCls_s00c7_3cb0* s = (PlanetCls_s00c7_3cb0*)((NounMgr*)NounManager())->GetCurrentTerrainSphere();
            ScanNode* node = (ScanNode*)s->mScanned.find(&k);
            ((PlanetCls_s00c7_3cb0*)((char*)node + 8))->FUN_00c73350((int*)a1);
        }
    }
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

// ---- civ/city helper functions from slice s00c6f6e0 (landed by hand: stubs spelled with the _c7 suffix)
static void* vc_c7(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }
struct CivData_c7;
struct CityData_c7;
struct WorldObject_c7 {                    // the `b8de30`/`b8dab0`/`b8dad0` result
    uchar      pad_000[0x3c];
    void**     mpVec3c_3c;              // 0x3c  vector<X*>::begin
    void**     mpVec3c_40;              // 0x40  vector<X*>::end
    uchar      pad_044[0x40];
    int        mPlayerID_84;            // 0x84
    void  Func70860();                  // 0xb8de30 -> later vtable call
    int   GetType();                    // 0xbb9ae0
    void  SetSomething(void* a);        // 0xbb9b90
};
struct CivData_c7 {
    CityData_c7** mpCities_00;             // 0x00 begin
    CityData_c7** mpCities_04;             // 0x04 end
    uchar      pad_008[0x84 - 8];
    int        mOwner_84;               // 0x84

    CityData_c7** GetCities() const;            // 0x5c65e0
    int        GetOwnerMaybe() const;        // 0xff0420
};
struct CityData_c7 {
    int  GetNumBuildings() const;            // 0xff0870
    int  GetNumTurrets() const;              // 0xff0760
    float GetValue() const;                  // 0xfd9410
    void AddValue(float v) const;            // 0xff0350
    int  GetPercent() const;                 // 0xff0400
};
struct SimCivObject_c7 {
    uchar        pad_000[0x15c];
    CivData_c7**    mpCivBegin_15c;        // 0x15c  eastl vector<cCivData*>::begin
    CivData_c7**    mpCivEnd_160;          // 0x160  eastl vector<cCivData*>::end
    uchar        pad_164[0x30];
    int          mTechLevel_194;        // 0x194

    int        GetRecordType();                              // 0xb8dab0
    void*      GetKeyMaybe();                                // 0xb8dad0 (int[3] key)
    void*      GetSubObject(int index);                      // 0xb8dec0
    WorldObject_c7* GetWorldObj();                              // 0xb8de30
    void       RebuildCivs();                                // 0xb8de60
    void       RebuildCivs2();                               // 0xb8df20

    bool  IsHomePlanetOfPlayer(WorldObject_c7* pObj);           // 0x00c70150
    bool  AnyCityHasBuildings();                             // 0x00c70260
    int   CountBuildings();                                  // 0x00c702f0
    void  GetTurretAndBuildingCounts(int* pBuildings, int* pTurrets); // 0x00c70380
    int   CountCities();                                     // 0x00c70420
    int   GetPercentMaybe();                                 // 0x00c70470
    bool  Func704a0(int a, int b, int c, float amount);      // 0x00c704a0
    int   Func705c0(int amount);                             // 0x00c705c0
    void  SetPlanetTechLevel(int level);                     // 0x00c706d0
};
extern float  DAT_013f4fd0_c7;                            // 4294967296.0f (uint->float bias)
extern void*  DAT_0167a60c_c7;                            // SimSingleton singleton
void* __cdecl FUN_0067dcc0_c7();                         // 0x67dcc0  MessageServer
void* __cdecl FUN_00ae3740_c7(void* a);                  // 0xae3740
void* __cdecl FUN_00ae5c30_c7(void* a);                  // 0xae5c30  SimSingleton::SimSingleton
void* __cdecl FUN_00aea720_c7(void* a, void* b, void* c); // 0xaea720 SpaceTool::RemoveMatching
void* __cdecl FUN_00aeab40_c7(void* a, void* b);         // 0xaeab40  SpaceTool::RemoveByKey
void* __cdecl FUN_00b1fdb0_c7(void* a);                  // 0xb1fdb0  cGameNounManager::GetAvatar
void* __cdecl FUN_00b3d2a0_c7(void* a);                  // 0xb3d2a0  SP::StarManager
void* __cdecl FUN_00b3d4a0_c7(void* a);                  // 0xb3d4a0  CommManager
void* __cdecl FUN_00b5b800_c7();                         // 0xb5b800  SP::GetCurrentGameMode
void* __cdecl FUN_00b8de60_c7(void* a);                  // 0xb8de60
void* __cdecl FUN_00b8df20_c7(void* a);                  // 0xb8df20
void* __cdecl FUN_00ba9370_c7(void* a);                  // 0xba9370  cStarManager::GetEmpireByID
void* __cdecl FUN_00bb9ae0_c7(void* a);                  // 0xbb9ae0
void* __cdecl FUN_00bb9b90_c7(void* a);                  // 0xbb9b90
void* __cdecl FUN_00c35810_c7(void* a, void* b);         // 0xc35810
void* __cdecl FUN_00c8b5e0_c7(void* a);                  // 0xc8b5e0
void* __cdecl FUN_00ce6950_c7(void* a);                  // 0xce6950  cStarRecordRef::GetCommContext
void* __cdecl FUN_00f473a0_c7(int a, const char* tag, int b, int c, int d, int e); // 0xf473a0 operator new
void* __cdecl FUN_01021080_c7();                         // 0x1021080  cSPLivingUniverse::GetUniverseContext
void* __cdecl FUN_01021090_c7();                         // 0x1021090  GetPlayerEmpireID
void* __cdecl FUN_01021260_c7();                         // 0x1021260  cSPLivingUniverse::GetActivePlanet
void* __cdecl FUN_01021300_c7();                         // 0x1021300  cSPLivingUniverse (ptr)

// @ 0x00c70150
bool SimCivObject_IsHomePlanetOfPlayer(SimCivObject_c7* self, WorldObject_c7* pObj, char flag) {
    if (self->GetRecordType() != 5) return false;
    int n = (int)((char*)self->mpCivEnd_160 - (char*)self->mpCivBegin_15c) >> 2;
    for (int i = 0; i < n; ++i) {
        CivData_c7* pCiv = self->mpCivBegin_15c[i];
        if (pCiv->GetOwnerMaybe() == pObj->mPlayerID_84) {
            void** pVec = (void**)(void*)pCiv->GetCities();
            void** pBegin = (void**)pVec[0];
            int m = (int)((char*)pVec[1] - (char*)pBegin) >> 2;
            for (int j = 0; j < m; ++j) {
                if (flag == 0) return true;
                if (((CityData_c7*)pBegin[j])->GetNumBuildings() > 1) return true;
            }
        }
    }
    if (FUN_01021080_c7() != 0) return false;
    void* pSingleton = DAT_0167a60c_c7;
    if (pSingleton == 0) {
        pSingleton = FUN_00f473a0_c7(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (pSingleton != 0)
            pSingleton = ((void* (__thiscall*)(void*))FUN_00ae5c30_c7)(pSingleton);
        DAT_0167a60c_c7 = pSingleton;
    }
    return ((bool (__thiscall*)(void*))FUN_00ae3740_c7)(pSingleton) != 0;
}

// @ 0x00c70260
bool SimCivObject_AnyCityHasBuildings(SimCivObject_c7* self) {
    int n = (int)((char*)self->mpCivEnd_160 - (char*)self->mpCivBegin_15c) >> 2;
    if (n <= 0) return false;
    for (int i = 0; i < n; ++i) {
        WorldObject_c7* pObj = (WorldObject_c7*)self->GetSubObject(i);
        char* begin = (char*)pObj->mpVec3c_3c;
        int m = (int)((char*)pObj->mpVec3c_40 - begin) >> 2;
        for (int j = 0; j < m; ++j) {
            CityData_c7* pCity = *(CityData_c7**)(begin + j * 4);
            if (pCity->GetValue() >= 1.0f) return true;
        }
    }
    return false;
}

// @ 0x00c702f0
int SimCivObject_CountBuildings(SimCivObject_c7* self) {
    int total = 0;
    int n = (int)((char*)self->mpCivEnd_160 - (char*)self->mpCivBegin_15c) >> 2;
    for (int i = 0; i < n; ++i) {
        void** pVec = (void**)(void*)self->mpCivBegin_15c[i]->GetCities();
        void** pBegin = (void**)pVec[0];
        int m = (int)((char*)pVec[1] - (char*)pBegin) >> 2;
        for (int j = 0; j < m; ++j)
            total += ((CityData_c7*)pBegin[j])->GetNumBuildings();
    }
    return total;
}

// @ 0x00c70380
void GetTurretAndBuildingCounts(SimCivObject_c7* self, int* pBuildings, int* pTurrets) {
    int n = (int)((char*)self->mpCivEnd_160 - (char*)self->mpCivBegin_15c) >> 2;
    for (int i = 0; i < n; ++i) {
        void** pVec = (void**)(void*)self->mpCivBegin_15c[i]->GetCities();
        void** pBegin = (void**)pVec[0];
        int m = (int)((char*)pVec[1] - (char*)pBegin) >> 2;
        for (int j = 0; j < m; ++j) {
            CityData_c7* pCity = (CityData_c7*)pBegin[j];
            *pBuildings += pCity->GetNumBuildings();
            *pTurrets   += pCity->GetNumTurrets();
        }
    }
}

// 0x00c70420 (byte-exact lifted version: match/slices/s00c70420/s00c70420.cpp)
int SimCivObject_CountCities(SimCivObject_c7* self) {
    int total = 0;
    int n = (int)((char*)self->mpCivEnd_160 - (char*)self->mpCivBegin_15c) >> 2;
    for (int i = 0; i < n; ++i) {
        void** pVec = (void**)(void*)self->mpCivBegin_15c[i]->GetCities();
        total += (int)((char*)pVec[1] - (char*)pVec[0]) >> 2;
    }
    return total;
}

// @ 0x00c70470
int SimCivObject_GetPercentMaybe(SimCivObject_c7* self) {
    int d = (int)((char*)self->mpCivEnd_160 - (char*)self->mpCivBegin_15c);
    unsigned n = (unsigned)(d >> 2);
    if (n <= 1 && n != 0)
        return ((CityData_c7*)self->mpCivBegin_15c[0])->GetPercent();
    return 0;
}

// @ 0x00c704a0
bool SimCivObject_Func704a0(SimCivObject_c7* self, int a, int b, int c, float amount) {
    int* pKey = (int*)self->GetKeyMaybe();
    if (a == pKey[0] && b == pKey[1] && c == pKey[2]) {
        int n = (int)((char*)self->mpCivEnd_160 - (char*)self->mpCivBegin_15c) >> 2;
        for (int i = 0; i < n; ++i) {
            WorldObject_c7* pObj = (WorldObject_c7*)self->GetSubObject(i);
            char* begin = (char*)pObj->mpVec3c_3c;
            int m = (int)((char*)pObj->mpVec3c_40 - begin) >> 2;
            for (int j = 0; j < m; ++j) {
                if (amount > 0.0f) {
                    CityData_c7* pCity = *(CityData_c7**)(begin + j * 4);
                    float v = pCity->GetValue();
                    float take = v;
                    if (amount < v) take = amount;
                    pCity->AddValue(-take);
                    amount -= take;
                }
            }
        }
    }
    return true;
}

#pragma float_control(precise, on, push)   // the slice builds without /fp:fast
// @ 0x00c705c0
int SimCivObject_Func705c0(SimCivObject_c7* self, int amount) {
    if (FUN_01021300_c7() == 0) return 0;
    FUN_01021090_c7();
    float budget = (float)amount;
    if (amount < 0) budget += DAT_013f4fd0_c7;
    float spent = 0.0f;
    int n = (int)((char*)self->mpCivEnd_160 - (char*)self->mpCivBegin_15c) >> 2;
    for (int i = 0; i < n; ++i) {
        WorldObject_c7* pObj = (WorldObject_c7*)self->GetSubObject(i);
        char* begin = (char*)pObj->mpVec3c_3c;
        int m = (int)((char*)pObj->mpVec3c_40 - begin) >> 2;
        for (int j = 0; j < m; ++j) {
            CityData_c7* pCity = *(CityData_c7**)(begin + j * 4);
            float v = pCity->GetValue();
            spent += v;
            if (budget > 0.0f) {
                if (v > budget) v = budget;
                pCity->AddValue(-v);
                budget -= v;
            }
        }
    }
    return (int)spent;
}
#pragma float_control(pop)

// @ 0x00c706d0
void SimCivObject_SetPlanetTechLevel(SimCivObject_c7* self, int level) {
    WorldObject_c7* pWorld = (WorldObject_c7*)self->GetWorldObj();
    SimPlanet* pActive = (SimPlanet*)FUN_01021260_c7();
    if (pActive != 0 && pActive->mRecord_13c != (PlanetRecord*)self) pActive = 0;

    if (self->mTechLevel_194 == 5 && level != 5) {
        void* pAvatar = ((void* (__thiscall*)(void*))FUN_00b1fdb0_c7)(pWorld);
        void* pMgr = ((void* (__stdcall*)(void*))FUN_00b3d2a0_c7)(pAvatar);
        void* pEmpire = ((void* (__thiscall*)(void*))FUN_00ba9370_c7)(pMgr);
        if (pEmpire != 0)
            ((void (__thiscall*)(void*, void*))FUN_00c35810_c7)(pEmpire, self);
        void* pCtx1 = ((void* (__thiscall*)(void*))FUN_00ce6950_c7)(self);
        ((void (__thiscall*)(void*))FUN_00aeab40_c7)(
            ((void* (__stdcall*)(void*))FUN_00b3d4a0_c7)(pCtx1));
        ((void (__thiscall*)(void*, void*, void*))FUN_00aea720_c7)(
            ((void* (__stdcall*)(void*))FUN_00b3d4a0_c7)(pAvatar),
            ((void* (__thiscall*)(void*))FUN_00ce6950_c7)(self),
            0);
    }
    self->mTechLevel_194 = level;
    if (level == 1 || level == 0) {
        ((void (__thiscall*)(void*))FUN_00b8de60_c7)(self);
        ((void (__thiscall*)(void*))FUN_00b8df20_c7)(self);
    }
    if (pActive != 0) {
        if ((int)FUN_00b5b800_c7() == 0x1654c05) {
            void* pMsg = FUN_0067dcc0_c7();
            ((void (__thiscall*)(void*, int, int, int, int))vc_c7(pMsg, 0x18))(pMsg, 0x490d429, 0, 0, 0);
        }
    }
    FUN_00c8b5e0_c7(pWorld);
    if (((int (__thiscall*)(void*))FUN_00bb9ae0_c7)(pWorld) < 2) {
        int x[3] = { 0, 0, 0 };
        ((void (__thiscall*)(void*, void*))FUN_00bb9b90_c7)(pWorld, x);
    }
}

// ===========================================================================
// Simulator cOrnament
// ===========================================================================

// base sub-object stubs whose only observable behaviour here is their ctor
struct GameDataBase { void ctor(); };              // 0xb18660
struct SpatialBase  { void ctor(); };              // 0xc89630
struct CombatantBase{ void ctor(); };              // 0xbfd4e0
struct IntTargetBase{ void ctor(); };              // 0xac03d0

// ---- InitTreeSpawnerAttributes from slice s01317d30 (landed by hand: attribute macros renamed *_T3)
namespace Simulator {
extern AttrSlot cTreeSpawner_sAttributes[17];   // 0x01567428

// Callbacks (all outside this slice), by address.
bool Read_00b6e3a0_t3(ISerializerReadStream*, void*);   // Vector3
bool Read_00572810_t3(ISerializerReadStream*, void*);   // raw 4 bytes
bool Read_00ae3430_t3(ISerializerReadStream*, void*);   // ResourceKey
bool Read_00b04d20_t3(ISerializerReadStream*, void*);
bool Read_00b0a310_t3(ISerializerReadStream*, void*);
bool Write_00ac88c0_t3(ISerializerWriteStream*, void*);
bool Write_00572840_t3(ISerializerWriteStream*, void*);
bool Write_00ac88f0_t3(ISerializerWriteStream*, void*);
bool Write_00ae3450_t3(ISerializerWriteStream*, void*);
bool Write_00aca730_t3(ISerializerWriteStream*, void*);
bool Write_00b00390_t3(ISerializerWriteStream*, void*);
void ReadText_006930f0_t3(const string8_s0131_5a50&, void*);
void ReadText_006930b0_t3(const string8_s0131_5a50&, void*);
void ReadText_00693090_t3(const string8_s0131_5a50&, void*);
void ReadText_00692ff0_t3(const string8_s0131_5a50&, void*);
void ReadText_00693150_t3(const string8_s0131_5a50&, void*);
void ReadText_00c2e4e0_t3(const string8_s0131_5a50&, void*);
void WriteText_00695010_t3(char*, void*);
void WriteText_00694fc0_t3(char*, void*);
void WriteText_00694f00_t3(char*, void*);
void WriteText_00694ee0_t3(char*, void*);
void WriteText_00695080_t3(char*, void*);
void WriteText_00692fb0_t3(char*, void*);
bool Validate_00b1fbf0_t3();
bool Validate_00b6f860_t3();
bool Validate_00b00400_t3();
bool ToXml_00acbba0_t3(void*, const char*, int);
bool ToXml_00acbb80_t3(void*, const char*, int);
bool ToXml_00675ca0_t3(void*, const char*, int);
bool ToXml_0057cde0_t3(void*, const char*, int);
bool ToXml_00ae5720_t3(void*, const char*, int);
bool ToXml_00c6c390_t3(void*, const char*, int);
bool ToXml_00b03fd0_t3(void*, const char*, int);

// Per-field set-default callbacks.
void SetDefault_00b00350_t3(Attribute*);   // mPosition
void SetDefault_00affa00_t3(Attribute*);
void SetDefault_00affa20_t3(Attribute*);
void SetDefault_00affa40_t3(Attribute*);
void SetDefault_00affa60_t3(Attribute*);
void SetDefault_00affa80_t3(Attribute*);
void SetDefault_00affaa0_t3(Attribute*);
void SetDefault_00affac0_t3(Attribute*);
void SetDefault_00affae0_t3(Attribute*);
void SetDefault_00affb30_t3(Attribute*);
void SetDefault_00affb80_t3(Attribute*);

// Class statics written between the records (unguarded).
extern float    sDefault_0167baec;
extern uint32_t sDefault_0167baf0;
extern uint32_t sDefault_0167baf4;
extern uint32_t sDefault_0167baf8;
extern uint32_t sDefault_0167bafc;
extern float    sDefault_0167bb00;
extern float    sDefault_0167bb04;
extern uint32_t sDefault_0167bb30;   // 4 bytes written after the third species key
extern uint32_t sDefault_0167bb10;
extern uint32_t sDefault_0167bb20;

// Guarded 12-byte function-local defaults: three zeroed ResourceKeys and one Vector3 copy.
struct Triple { uint32_t a, b, c; };
extern Triple gVec3Zero;   // 0x0167af5c
extern uint8_t  sFlag_0167bb4c; extern Triple sVec3_0167bb40;
extern uint8_t  sFlag_0167bb14; extern Triple sKey_0167bb08;
extern uint8_t  sFlag_0167bb24; extern Triple sKey_0167bb18;
extern uint8_t  sFlag_0167bb34; extern Triple sKey_0167bb28;

#define VEC3_ATTR_T3  Read_00b6e3a0_t3, Write_00ac88c0_t3, ReadText_006930f0_t3, WriteText_00695010_t3, Validate_00b1fbf0_t3, ToXml_00acbba0_t3
#define FLOAT_ATTR_T3 Read_00572810_t3, Write_00ac88f0_t3, ReadText_006930b0_t3, WriteText_00694fc0_t3, Validate_00b1fbf0_t3, ToXml_00acbb80_t3
#define UINT_ATTR_T3  Read_00572810_t3, Write_00572840_t3, ReadText_00693090_t3, WriteText_00694f00_t3, Validate_00b1fbf0_t3, ToXml_00675ca0_t3
#define INT_ATTR_T3   Read_00572810_t3, Write_00572840_t3, ReadText_00692ff0_t3, WriteText_00694ee0_t3, Validate_00b1fbf0_t3, ToXml_0057cde0_t3
#define KEY_ATTR_T3   Read_00ae3430_t3, Write_00ae3450_t3, ReadText_00693150_t3, WriteText_00695080_t3, Validate_00b1fbf0_t3, ToXml_00ae5720_t3
#define TREES_ATTR_T3 Read_00b04d20_t3, Write_00aca730_t3, ReadText_00c2e4e0_t3, WriteText_00692fb0_t3, Validate_00b6f860_t3, ToXml_00c6c390_t3
#define DEPR_ATTR_T3  Read_00b0a310_t3, Write_00b00390_t3, ReadText_00c2e4e0_t3, WriteText_00692fb0_t3, Validate_00b00400_t3, ToXml_00b03fd0_t3

#define ADD3(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cTreeSpawner_sAttributes[IDX] = a; }

// @ 0x01317d30
void InitTreeSpawnerAttributes()
{
    if (!(sFlag_0167bb4c & 1)) sFlag_0167bb4c |= 1;
    sVec3_0167bb40.a = gVec3Zero.a;
    sVec3_0167bb40.b = gVec3Zero.b;
    sVec3_0167bb40.c = gVec3Zero.c;
    ADD3(0,  "mPosition", 0x056690e8, 0x0, VEC3_ATTR_T3, SetDefault_00b00350_t3)
    ADD3(1,  "mRadius", 0x056690e9, 0xc, FLOAT_ATTR_T3, SetDefault_00affa00_t3)
    ADD3(2,  "mSeqId", 0x056690ea, 0x10, UINT_ATTR_T3, SetDefault_00affa20_t3)
    ADD3(3,  "mMaxLargeTreeFruit", 0x05669d6b, 0x14, INT_ATTR_T3, SetDefault_00affa40_t3)
    sDefault_0167baec = 0.0f;
    sDefault_0167baf0 = 0;
    sDefault_0167baf4 = 0;
    ADD3(4,  "mMaxMediumTreeFruit", 0x05669d6c, 0x18, INT_ATTR_T3, SetDefault_00affa60_t3)
    sDefault_0167baf8 = 0;
    ADD3(5,  "mMaxSmallTreeFruit", 0x05669d6d, 0x1c, INT_ATTR_T3, SetDefault_00affa80_t3)
    ADD3(6,  "mDropRate", 0x06288473, 0x14c, FLOAT_ATTR_T3, SetDefault_00affaa0_t3)
    ADD3(7,  "mRegrowRate", 0x06288a5e, 0x150, FLOAT_ATTR_T3, SetDefault_00affac0_t3)
    if (!(sFlag_0167bb14 & 1)) sFlag_0167bb14 |= 1;
    sDefault_0167bafc = 0;
    sDefault_0167bb00 = -1.0f;
    sDefault_0167bb04 = -1.0f;
    sKey_0167bb08.a = 0; sKey_0167bb08.b = 0;
    ADD3(8,  "mLargeSpecies", 0x062d70cf, 0x20, KEY_ATTR_T3, SetDefault_00affae0_t3)
    sKey_0167bb08.c = 0;
    if (!(sFlag_0167bb24 & 1)) sFlag_0167bb24 |= 1;
    sKey_0167bb18.a = 0; sKey_0167bb18.b = 0;
    ADD3(9,  "mMediumSpecies", 0x062d832b, 0x2c, KEY_ATTR_T3, SetDefault_00affb30_t3)
    sKey_0167bb18.c = 0;
    if (!(sFlag_0167bb34 & 1)) sFlag_0167bb34 |= 1;
    sKey_0167bb28.a = 0; sKey_0167bb28.b = 0;
    ADD3(10, "mSmallSpecies", 0x062d70d8, 0x38, KEY_ATTR_T3, SetDefault_00affb80_t3)
    sKey_0167bb28.c = 0;
    ADD3(11, "mLargeTrees", 0x06abf140, 0x44, TREES_ATTR_T3)
    ADD3(12, "mMediumTrees", 0x06abf141, 0x9c, TREES_ATTR_T3)
    ADD3(13, "mSmallTrees", 0x06abf142, 0xf4, TREES_ATTR_T3)
    ADD3(14, "mDeprecated_LargeTrees", 0x056690eb, 0x158, DEPR_ATTR_T3)
    ADD3(15, "mDeprecated_MediumTrees", 0x056690ec, 0x970, DEPR_ATTR_T3)
    ADD3(16, "mDeprecated_SmallTrees", 0x056690ed, 0x1188, DEPR_ATTR_T3)
}
#undef ADD3
}  // namespace Simulator
