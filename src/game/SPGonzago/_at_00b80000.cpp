// src/game/SPGonzago/_at_00b80000.cpp -- migrated from slice(s) s00b8f230, s00b8e180, s00b8d190, s00b8bb70 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00b80000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cCivilization.h"
#include "SP/cPlanet.h"
#include "SP/cPlanetModel.h"
#include "SP/cRenderer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" uint32_t* __cdecl Memset32(uint32_t* pDst, uint32_t nValue, int nCount);  // 0x0092cb00
extern "C" void __cdecl FUN_00f48af0(int nValue);                      // 0x00f48af0
#include <math.h>
#include <intrin.h>
#include <stddef.h>
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)

// ---- items of slice s00b8bb70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
struct SVector3 {
    float x, y, z;
};
class RCSub {
public:
    virtual void Del(int);
    volatile long mnRefCount;                  // +0x04
    long Release()
    {
        long n = _InterlockedDecrement(&mnRefCount);
        if (n == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            if (this)
                Del(1);
        }
        return n;
    }
};
class cMinimapGfx {
public:
    char     pad00[0x0c];
    bool     mbDirty;                          // +0x0c
    char     pad0d[0x24 - 0x0d];
    RCSub*   mpRefObject;                      // +0x24
    bool     mbActive;                         // +0x28
};
class cPlanet {
public:
    void SetRampEnabled(bool bEnabled);        // 0x00fbd6b0
};
class cTerrainEditor {
public:
    void SetActiveObject(void* pObject);       // 0x00f67a60
};
class cInputManager {
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
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual void SetMode(int nMode);           // +0x50
};
class cMessageServer {
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
virtual void v24();
virtual void v28();
    virtual void Post(void* pSender, uint32_t nMessage, int nFlags);   // +0x2c
};
class cEffectsManager {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void SetTime(int nA, int nB);      // +0x20
};
class cRenderer {
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
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
    virtual void SetFlag(int nValue);          // +0x3c
};
class IWorldEditor {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual cPlanet* v10();                    // +0x10
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
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
virtual void vA0();
virtual void vA4();
virtual void vA8();
virtual void vAC();
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBC();
virtual void vC0();
virtual void vC4();
virtual void vC8();
virtual void vCC();
virtual void vD0();
virtual void vD4();
virtual void vD8();
virtual void vDC();
virtual void vE0();
virtual void vE4();
virtual void vE8();
virtual void vEC();
virtual void vF0();
virtual void vF4();
virtual void vF8();
virtual void vFC();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void v10C();
    virtual void ShutdownScene();              // +0x110
};
class IPlanetSphere {
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
virtual void v24();
virtual void v28();
virtual void v2c();
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
    virtual void SetInputManager(void* pManager);        // +0x90
virtual void v94();
virtual void v98();
virtual void v9c();
    virtual void vA0();
    virtual void vA4();                        // +0xa4
    virtual void vA8();
    virtual void vAC();                        // +0xac
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBC();
virtual void vC0();
virtual void vC4();
virtual void vC8();
virtual void vCC();
virtual void vD0();
virtual void vD4();
virtual void vD8();
virtual void vDC();
virtual void vE0();
virtual void vE4();
virtual void vE8();
    virtual void vEC();                        // +0xec
virtual void vF0();
virtual void vF4();
    virtual void vF8();                        // +0xf8
};
struct CityPair {
    void* mpFirst;
    void* mpSecond;
};
struct LandRoute {
    uint8_t mData[0x1c];
};
class CityPairVector {
public:
    CityPair* mpBegin;                         // +0x00
    CityPair* mpEnd;                           // +0x04
    CityPair* mpCapacity;                      // +0x08
    uint32_t  mAllocator;                      // +0x0c
    void EraseRange(CityPair* pFirst, CityPair* pLast);        // 0x00d018d0
    void Clear() { EraseRange(mpBegin, mpEnd); }
};
class LandRouteVector {
public:
    LandRoute* mpBegin;                        // +0x00
    LandRoute* mpEnd;                          // +0x04
    LandRoute* mpCapacity;                     // +0x08
    uint32_t   mAllocator;                     // +0x0c
    void EraseRange(LandRoute* pFirst, LandRoute* pLast);      // 0x00b897d0
    void Clear() { EraseRange(mpBegin, mpEnd); }
};
class cCivilization {
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
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual int GetID();                       // +0x4c
};
class IPositionSource {
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
virtual void v24();
virtual void v28();
    virtual const SVector3* GetPosition();     // +0x2c
};
class cCity {
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
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual int GetOwnerID(bool bPrimary);     // +0x4c
    char              pad04[0x34 - 0x04];
    IPositionSource   mNodeValue;              // +0x34
    char              pad38[0x120 - 0x38];
    IPositionSource   mPosition;               // +0x120
    cCivilization*    GetCivilization();       // 0x00bd9bf0
};
struct GraphNodeValue {
    uint32_t mValue[3];
};
struct GraphNode {
    int32_t         mnID;                      // +0x00
    GraphNodeValue  mValue;                    // +0x04
    bool            mbResourceNode;            // +0x10
    bool            mbDirty;                   // +0x11
    uint16_t        pad12;
    cCity*          mpCity;                    // +0x14
};
class GraphNodeVector {
public:
    GraphNode* mpBegin;                        // +0x00
    GraphNode* mpEnd;                          // +0x04
    GraphNode* mpCapacity;                     // +0x08
    uint32_t   mAllocator;                     // +0x0c
};
struct IVec3U {
    uint32_t mX, mY, mZ;
    IVec3U() {}
    IVec3U(uint32_t x, uint32_t y, uint32_t z) : mX(x), mY(y), mZ(z) {}
};
class cPlanetModel {
public:
    char            pad00[0x20];
    IWorldEditor*   mpWorldEditor;             // +0x20
    IPlanetSphere*  mpISphere;                 // +0x24
    char            pad28[0x2c - 0x28];
    IVec3U          mField2C;                  // +0x2c
    uint16_t*       mpIndexBegin;              // +0x38
    uint16_t*       mpIndexEnd;                // +0x3c
    char            pad40[0x48 - 0x40];
    bool            mbRegistered;              // +0x48
    char            pad49[0x4c - 0x49];
    uint32_t*       mContinentMap;             // +0x4c
    char            pad50[0x64 - 0x50];
    uint8_t*        mContinentAboveWater;      // +0x64
    char            pad68[0x7c - 0x68];
    uint32_t*       mpCellNibbles;             // +0x7c
    GraphNodeVector mNodes;                    // +0x80
    char            pad90[0x94 - 0x90];
    uint8_t*        mpZoneMap;                 // +0x94
    uint8_t*        mpZoneMapEnd;              // +0x98
    char            pad9c[0xa8 - 0x9c];
    cMinimapGfx*    mpMinimapGfx;              // +0xa8
    CityPairVector  mSeaTradeRoutes;           // +0xac
    char            padBC[0xc0 - 0xbc];
    CityPairVector  mLandTradeRoutes;          // +0xc0
    char            padD0[0xd4 - 0xd0];
    LandRouteVector mPathRoutes;               // +0xd4
    char            padE4[0xe8 - 0xe4];
    bool            mbSeaRoutesDirty;          // +0xe8
    bool            mbLandRoutesDirty;         // +0xe9
    bool            mbPathRoutesDirty;         // +0xea

    bool RayCast(const SVector3* pOrigin, float fDirection, SVector3* pOut,
                 float fRadius, bool bLayer, uint32_t nMask);          // 0x00b88770
    bool FindClosestWater(const SVector3* pOrigin, float fDirection,
                          SVector3* pOut);                             // 0x00b8bb70
    void Reset();                                                      // 0x00b87bb0
    int  AddNode(const SVector3* pValue, bool bResourceNode);          // 0x00b86500
    void SetNodeFlag(int nIndex, bool bValue);                         // 0x00b7ea30
    void SetNodeID(int nIndex, int nValue);                            // 0x00b841a0
    int  GetContinent(const SVector3* pPosition);                      // 0x00b88590
    void BuildPoliticalZoneMap();                                      // 0x00b8aea0
    void Shutdown();                                                   // 0x00b8c0f0
    void AddResourceNodes();                                           // 0x00b8bba0
};
extern cInputManager* InputManager();          // 0x0067dd50
extern cMessageServer* MessageServer();        // 0x0067dcc0
extern cEffectsManager* EffectsManagerPtr();   // 0x0067ddd0
extern cRenderer* g_Renderer;                  // 0x0167ea54
extern "C" uint32_t* __cdecl Memset32(uint32_t* pDst, uint32_t nValue, int nCount);  // 0x0092cb00
extern "C" cTerrainEditor* __cdecl TerrainEditor();                    // 0x00f48a70
extern "C" void __cdecl FUN_00f48af0(int nValue);                      // 0x00f48af0
// ---- items of slice s00b8bb70 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cInputManager* InputManager();          // 0x0067dd50
extern cMessageServer* MessageServer();        // 0x0067dcc0
extern cEffectsManager* EffectsManagerPtr();   // 0x0067ddd0
extern cRenderer* g_Renderer;                  // 0x0167ea54
extern "C" cTerrainEditor* __cdecl TerrainEditor();                    // 0x00f48a70

// ---- items of slice s00b8d190 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace SP {
    void* __stdcall StarManager(uint32_t id);             // 0x00b3d2a0
}
namespace SP {
    void* __stdcall GetMissionManager(uint32_t id);        // 0x00feb9f0
}
namespace SP {
    void  GetPropertyAsKey(uint32_t property, uint32_t key, void* out); // 0x006a1250
}
void* __cdecl FUN_00f48a80();                             // 0x00f48a80
void  __cdecl FUN_00f47380(void* block);                  // 0x00f47380 (operator delete[])
uint32_t __cdecl FUN_0067dd50();                          // 0x0067dd50
struct cKeyService {                                      // returned by 0x00f48a80
    PV(0)
    virtual int32_t v1(uint32_t* key);                    // +0x04
};
struct cHandlerHost {
    PV(0)  PV(1)  PV(2)  PV(3)  PV(4)  PV(5)  PV(6)  PV(7)  PV(8)  PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42)
    virtual void v43();                                   // +0xac
};
struct cCursorHost {
    PV(0)  PV(1)  PV(2)  PV(3)  PV(4)  PV(5)  PV(6)  PV(7)  PV(8)  PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void v35(uint32_t value);                     // +0x8c
};
struct cStarObject {
    int32_t  FUN_00bb99e0();                              // 0x00bb99e0
    uint32_t FUN_00ba6440();                              // 0x00ba6440
    void     FUN_00ba6660();                              // 0x00ba6660
    uint32_t FUN_00ba6d80();                              // 0x00ba6d80
    void*    FUN_00bb9b80();                              // 0x00bb9b80
};
struct cMission {
    int32_t FUN_00c4b220();                               // 0x00c4b220
};
struct cMissionManager {
    cMission* FUN_00fee220();                             // 0x00fee220
};
struct cOwnedElem {
    void FUN_00ff2e30();                                  // 0x00ff2e30
};
struct cOwnedElem2 {
    void FUN_00c2e4e0();                                  // 0x00c2e4e0
};
struct cKey3 {                                            // three-word property key
    uint32_t m0;                                          // +0x00
    uint32_t m4;                                          // +0x04
    uint32_t m8;                                          // +0x08
    cKey3() : m0(0), m4(0), m8(0) {}
};
struct cBioElem {                                         // 0x2c-byte bio-protector record
    int32_t  m00;                                         // +0x00
    float    m04;                                         // +0x04
    float    m08;                                         // +0x08
    float    m0C;                                         // +0x0c
    uint16_t m10;                                         // +0x10
    uint8_t  m12;                                         // +0x12
    uint8_t  mPad13;                                      // +0x13
    float    m14;                                         // +0x14
    int32_t  m18;                                         // +0x18
    int32_t  m1C;                                         // +0x1c
    int32_t  m20;                                         // +0x20
    int32_t  m24;                                         // +0x24
    uint8_t  m28;                                         // +0x28
    uint8_t  mPad29[3];                                   // +0x29
};
struct cPlanetModel_s00b8_d190 {
    uint8_t  mPad00[0x20];                                // +0x000
    cHandlerHost* mField20;                               // +0x020
    cCursorHost*  mField24;                               // +0x024
    int32_t  mField28;                                    // +0x028
    uint32_t mField2C;                                    // +0x02c
    uint8_t  mPad30[0x48];                                // +0x030
    uint8_t  mField78;                                    // +0x078
    uint8_t  mPad79[0x5b];                                // +0x079
    char*    mFieldD4;                                    // +0x0d4
    char*    mFieldD8;                                    // +0x0d8
    char*    mFieldDC;                                    // +0x0dc
    uint8_t  mPadE0[0x0a];                                // +0x0e0
    uint8_t  mFieldEA;                                    // +0x0ea
    uint8_t  mPadEB;                                      // +0x0eb
    int32_t  mFieldEC;                                    // +0x0ec
    uint8_t  mPadF0[0x44];                                // +0x0f0
    char*    mField134;                                   // +0x134
    char*    mField138;                                   // +0x138
    uint8_t  mPad13C[0x20];                               // +0x13c
    char*    mField15C;                                   // +0x15c
    char*    mField160;                                   // +0x160
    uint8_t  mPad164[0x0c];                               // +0x164
    char*    mField170;                                   // +0x170
    char*    mField174;                                   // +0x174
    uint8_t  mPad178[0x0c];                               // +0x178
    uint32_t mField184;                                   // +0x184
    uint8_t  mPad188[0x0c];                               // +0x188
    int32_t  mField194;                                   // +0x194
    uint8_t  mPad198[0x0c];                               // +0x198
    uint32_t mField1A4;                                   // +0x1a4
    uint32_t mField1A8;                                   // +0x1a8
    uint32_t mField1AC;                                   // +0x1ac

    void  UpdateMinimap(int32_t a, int32_t b, int32_t c);  // 0x00b8c330
    void  FUN_00b8c0f0();                                  // 0x00b8c0f0
    bool  HandleMessage(uint32_t id, void* msg);           // 0x00b8d2a0
    void  FUN_00b8d2f0();                                  // 0x00b8d2f0
    bool  FUN_00b8d750(uint32_t a, uint32_t b);            // 0x00b8d750
    bool  FUN_00b8d8a0(uint32_t a, bool refresh, uint32_t c); // 0x00b8d8a0
    uint32_t FUN_00b8d8f0();                               // 0x00b8d8f0
    void  FUN_00b8d910();                                  // 0x00b8d910
    void  FUN_00b8d920(bool flag);                         // 0x00b8d920
    void  FUN_00b8d950(bool flag);                         // 0x00b8d950
    void  FUN_00b8d980(bool flag);                         // 0x00b8d980
    int32_t FUN_00b8d9b0();                                // 0x00b8d9b0
    bool  FUN_00b8d9f0();                                  // 0x00b8d9f0
    int32_t FUN_00b8da70();                                // 0x00b8da70
    cKey3* FUN_00b8dd60(cKey3* out);                       // 0x00b8dd60
    void  FUN_00b8dde0(cKey3* key, int32_t unused);        // 0x00b8dde0
    void  FUN_00b8de60();                                  // 0x00b8de60
    int32_t FUN_00b8dec0(int32_t index);                   // 0x00b8dec0
    int32_t FUN_00b8def0(int32_t index);                   // 0x00b8def0
    void  FUN_00b8df20();                                  // 0x00b8df20
    void  FUN_00b8df80(int32_t index);                     // 0x00b8df80
    void  FUN_00b8dfe0(int32_t index);                     // 0x00b8dfe0
    bool  FUN_00b8e040(uint32_t id);                       // 0x00b8e040
    cKey3* FUN_00b8e090();                                 // 0x00b8e090
};
// ---- items of slice s00b8d190 end

// ---- items of slice s00b8e180 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_PlanetAttrs;         // 0x0156b758
extern unsigned char g_flag15d8b4c; // 0x015d8b4c
#pragma intrinsic(_InterlockedExchange)
typedef unsigned undefined4;
void __cdecl operator_delete(void* p);                                        // 0x00f47380
void* __cdecl VectorInsert(void* dst, void* src, unsigned n);                 // 0x011e0744
struct RuleObj {
    void Destroy();                                                        // 0x00ff2e30
};
#define ObjDtor(o) ((RuleObj*)(o))->Destroy()
struct PtrVec {
    void* begin;   // +0
    void* end;     // +4
    void* cap;     // +8
    // 0x00b968b0 (__thiscall): grow to hold n elements; returns the new buffer.
    void* allocateToFit(unsigned n, void* srcBegin, void* srcEnd);
    // 0x00b8ef40 (__thiscall): copy assignment.
    PtrVec* assignSlow(const PtrVec& o);
    // 0x00fea240 (__thiscall, two stack args): erase a range.
    void eraseRange(void* b, void* e);                                         // 0x00fea240
};
#define KeyVecAssign(d, s) ((PtrVec*)(d))->assignSlow(*(const PtrVec*)(s))
#define FloatVecAssign(d, s) ((PtrVec*)(d))->assignSlow(*(const PtrVec*)(s))
#define RuleVecAssign(d, s) ((PtrVec*)(d))->assignSlow(*(const PtrVec*)(s))
#define PtrVecAssign(d, s) ((PtrVec*)(d))->assignSlow(*(const PtrVec*)(s))
void* __cdecl EAAllocate(unsigned size, const char* name, int a, int b,
                         int c, int d);                                       // 0x00f473a0
void __cdecl ReadInt32(void* s, unsigned* dst, unsigned n, int z);            // 0x0093a780
struct PushVec {
    void* begin;   // +0
    void* end;     // +4
    void* cap;     // +8
    void pushBack(void** v);                                                  // 0x00b96600
};
void __stdcall RuleVecPush(void* self, void* dst, void* src);                 // 0x00acb810
#define PushPtrBack(pv, p)  ((PushVec*)(pv))->pushBack((void**)(p))
#define PushRuleBack(pv, d, s) RuleVecPush(pv, d, s)
void* __cdecl VarListConstruct(void* self, void* global, unsigned id);        // 0x00692f90
char __stdcall VarListSerialize(void* self, void* stream);                    // 0x00693e10
void __cdecl WStrFromLit(void* dst, int lit);                                 // 0x004010a0
void* __stdcall WStrResolve(void* from, int lit);                             // 0x005ecf80
struct CtorObj {
    void Ctor();          // 0x00ff3440 (cCivData)
    void CtorTribe();     // 0x00ff0700 (cTribeData)
};
#define CIV_CTOR(p)   ((CtorObj*)(p))->Ctor()
#define TRIBE_CTOR(p) ((CtorObj*)(p))->CtorTribe()
struct Deser {
    bool From(void* s);   // 0x00ff2e80 (cCivData)
    bool TribeFrom(void* s); // 0x00ff0590 (cTribeData operator>>)
    bool CommodityFrom(void* s); // 0x00bfe2d0 (cCommodityNodeData)
    bool RuleFrom(void* s);      // 0x00bc3230 (Rule)
};
#define CIV_FROM(p, s)  ((Deser*)(p))->From(s)
#define TRIBE_FROM(p, s) ((Deser*)(p))->TribeFrom(s)
#define COMM_FROM(p, s) ((Deser*)(p))->CommodityFrom(s)
#define RULE_FROM(p, s) ((Deser*)(p))->RuleFrom(s)
void __stdcall WString_Assign(const void* b, const void* e);                  // 0x00423650
void __cdecl TypedValueWrite(void* self, const void* value);                  // 0x00694f60
void __cdecl ConvertToString16Impl(void* dst, const char* src, unsigned len); // 0x0093c5a0
void* __cdecl ConvertToString16(void* dst, const void* src);                  // 0x0093c6d0
struct Vec4 {
    void** mpBegin;   // +0
    void** mpEnd;     // +4
    void** mpCap;     // +8
};
struct WString16 {
    void* mpBegin;      // +0
    void* mpEnd;        // +4
    void* mpCapacity;   // +8
    void CopyFrom(const WString16& src);   // 0x0056e2d0 (__thiscall)
};
struct Rule {
    uint32_t w[0x2c / 4];
};
struct GmeEditorResBase {
    void* mvtbl;                       // +0: 0x14655a0 then 0x13eb938 on destruction
};
struct cPropertyList : GmeEditorResBase {
    uint32_t m04;                      // +0x04  (interlocked)
    uint32_t m08, m0c, m10, m14;       // +0x08
    uint32_t m18, m1c, m20;            // +0x18 wide-string range (begin/end/cap)
    uint32_t m24;                      // +0x24
    int32_t  m28;                      // +0x28
    uint32_t m2c;                      // +0x2c
    uint8_t  m30[0x98 - 0x30];         // +0x30
    uint8_t  m98;                      // +0x98
    uint8_t  m99[0x9c - 0x99];         // +0x99
    float    m9cf;                     // +0x9c
    float    ma0f;                     // +0xa0
    float    ma4f;                     // +0xa4
    float    ma8;                      // +0xa8
    uint8_t  mac, mad;                 // +0xac
    float    mb0, mb4, mb8;            // +0xb0
    Vec4     mbc;                      // +0xbc
    uint32_t mC8[2];                   // +0xc8
    Vec4     md0;                      // +0xd0
    uint32_t mDC[2];                   // +0xdc
    Vec4     me4;                      // +0xe4
    uint32_t mF0[2];                   // +0xf0
    Vec4     mf8;                      // +0xf8
    uint32_t m104[3];                  // +0x104
    Vec4     m110;                     // +0x110
    uint32_t m11C[2];                  // +0x11c
    uint32_t m124;                     // +0x124
    float    m128, m12c;               // +0x128
    uint8_t  m130;                     // +0x130
    Vec4     m134;                     // +0x134
    uint32_t m140[2];                  // +0x140
    Vec4     m148;                     // +0x148
    uint32_t m154[2];                  // +0x154
    Vec4     m15c;                     // +0x15c
    uint32_t m168[2];                  // +0x168
    Vec4     m170;                     // +0x170
    uint32_t m17C[2];                  // +0x17c
    uint32_t m184;                     // +0x184
    uint32_t m188, m18c, m190;         // +0x188
    uint32_t m194;                     // +0x194
    uint32_t m198, m19c, m1a0;         // +0x198
    uint32_t m1a4, m1a8, m1ac;         // +0x1a4

    void Ctor();
    void Dtor();
    cPropertyList& operator=(const cPropertyList& o);
    cPropertyList& AssignCopy(const cPropertyList& o);
    bool Serialize(void* stream);
    void AssignRange(const Vec4& r);
    void PurgeEmptyRules();
    void EraseRule(int key);
    void EraseAllRules();
};
struct IMatcher {
    virtual char M0(const void* key);                 // vtable +0x0
    virtual char M1(const void* key);                 // vtable +0x4
    virtual char M2(const void* a, const void* b);    // vtable +0x8
    virtual char M3(const void* value);               // vtable +0xc
};
struct LayoutElem {
    void SetSerializer();                                                  // 0x00c2e4e0
};
#define ElemDtor(p) ((LayoutElem*)(p))->SetSerializer()
struct ISerialStream {
virtual void vt00();
virtual void vt04();
virtual void vt08();
virtual void vt0c();
virtual void vt10();
virtual void vt14();
virtual void vt18();
virtual void vt1c();
    virtual void* GetSerializer();            // slot +0x20 -> index 8
};
struct ISerializer {
virtual void vt00();
virtual void vt04();
virtual void vt08();
virtual void vt0c();
virtual void vt10();
virtual void vt14();
    virtual void* GetReader();                // slot +0x18 -> index 6
};
static void* Reader(ISerialStream* s);  // 0x00b8eaa0 (defined below; used by a stub's inline body)
bool cPropertyList::Serialize(void* stream)
{
    int* a = (int*)this;
    ISerialStream* s = (ISerialStream*)stream;
    unsigned count;

    // --- civ data (0x50-byte cCivData*) ---
    ReadInt32(Reader(s), &count, 1, 0);
    {
        int* ve = a + 0x15c / 4;                 // {begin,end,cap}
        VectorInsert((void*)ve[0], (void*)ve[1], 0);
        ve[1] += (((ve[1] - ve[0]) >> 2) * -4);
    }
    for (unsigned i = 0; i < count; i++) {
        void* o = EAAllocate(0x50, "Simulator/cCivData", 0, 0, 0, 0);
        void* v = o ? (CIV_CTOR(o), o) : 0;
        CIV_FROM(v, s);
        int* ve = a + 0x15c / 4;
        if (ve[1] < ve[2]) {
            int* slot = (int*)ve[1];
            ve[1] += 4;
            if (slot) *slot = (int)v;
        } else {
            PushPtrBack(ve, &v);
        }
    }

    // --- tribe data (0x18-byte cTribeData*) ---
    ReadInt32(Reader(s), &count, 1, 0);
    {
        int* ve = a + 0x170 / 4;
        VectorInsert((void*)ve[0], (void*)ve[1], 0);
        ve[1] += (((ve[1] - ve[0]) >> 2) * -4);
    }
    for (unsigned i = 0; i < count; i++) {
        void* o = EAAllocate(0x18, "Simulator/cTribeData", 0, 0, 0, 0);
        void* v = o ? (TRIBE_CTOR(o), o) : 0;
        TRIBE_FROM(v, s);
        int* ve = a + 0x170 / 4;
        if (ve[1] < ve[2]) {
            int* slot = (int*)ve[1];
            ve[1] += 4;
            if (slot) *slot = (int)v;
        } else {
            PushPtrBack(ve, &v);
        }
    }

    // --- rules (0x2c-byte) ---
    ReadInt32(Reader(s), &count, 1, 0);
    PtrVec* rv = (PtrVec*)(a + 0x134 / 4);
    rv->eraseRange(rv->begin, rv->end);
    for (unsigned i = 0; i < count; i++) {
        unsigned char rule[0x2c];
        unsigned* r = (unsigned*)rule;
        r[0] = 0; r[1] = 0; r[2] = 0; r[3] = 0;
        *(unsigned short*)(rule + 0x10) = 0;
        rule[0x12] = 1;
        RULE_FROM(rule, s);
        int* ve = a + 0x138 / 4;
        if (ve[1] < ve[2]) {
            unsigned* slot = (unsigned*)ve[1];
            ve[1] += 0x2c;
            if (slot) {
                for (int k = 0; k < 0xb; k++) slot[k] = r[k];
            }
        } else {
            PushRuleBack(ve, (void*)ve[1], rule);
        }
    }

    // --- commodity node data (8-byte) ---
    ReadInt32(Reader(s), &count, 1, 0);
    {
        int* ve = a + 0xe4 / 4;
        VectorInsert((void*)ve[0], (void*)ve[1], 0);
        ve[1] += (((ve[1] - ve[0]) >> 2) * -4);
    }
    for (unsigned i = 0; i < count; i++) {
        void* o = EAAllocate(8, "Simulator/cCommodityNodeData", 0, 0, 0, 0);
        if (o) { ((unsigned*)o)[0] = 0xffffffff; ((unsigned*)o)[1] = 0xffffffff; }
        COMM_FROM(o, s);
        int* ve = a + 0xe4 / 4;
        if (ve[1] < ve[2]) {
            int* slot = (int*)ve[1];
            ve[1] += 4;
            if (slot) *slot = (int)o;
        } else {
            PushPtrBack(ve, &o);
        }
    }

    // --- variable list ---
    {
        void* vls = VarListConstruct(0, g_PlanetAttrs, 0x1a80d26);
        char ok = VarListSerialize(vls, s);
        // compare the stored name against the global wstring, update if it matches
        {
            unsigned char tmp[0x30];
            WStrFromLit(tmp, 0x7e1310a);
            int* p = (int*)WStrResolve(tmp, 0x7e1310a);
            if (p[0] != p[1] && (*(unsigned char*)((int)a + 0x2c) & 1) == 0
                && p != a + 6)
                WString_Assign((void*)p[0], (void*)p[1]);
            int b = ((int*)tmp)[0], e = ((int*)tmp)[4];
            if ((((e - b) & 0xfffffffe) > 2) && b != 0)
                operator_delete((void*)b);
        }
        return ok != 0;
    }
}
// ---- items of slice s00b8e180 end

// ---- items of slice s00b8f230 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EastlNew(unsigned int size, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EastlDelete(void* p);                                             // 0x00f47380
extern "C" void  __cdecl FUN_0093b8e0(void* stream, int len);                              // 0x0093b8e0
extern "C" void* __cdecl EA_ZoneNew(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00926020
extern "C" int   __cdecl FUN_00693cd0(void* db, int a, int b, int c);                      // 0x00693cd0
extern "C" int   __cdecl FUN_00693d60(void* db, int a, int b, int c);                      // 0x00693d60
extern "C" void  __cdecl FUN_00692ea0(void);                                               // 0x00692ea0
extern "C" void  __cdecl FUN_00692ec0(void* p);                                            // 0x00692ec0
extern "C" void  __cdecl FUN_00693900(void);                                               // 0x00693900
extern "C" char  __cdecl FUN_00c87580(void* stream);                                       // 0x00c87580
extern "C" char  __cdecl FUN_00c879a0(void* stream);                                       // 0x00c879a0
extern "C" void* __cdecl FUN_00401090(void* key);                                          // 0x00401090
extern "C" void* __cdecl FUN_004df440(void* mgr, void* key);                               // 0x004df440
extern "C" void* __cdecl FUN_00ac0d80(void* first, void* last, void* key);                 // 0x00ac0d80
extern "C" void* __cdecl FUN_010212a0(void);                                               // 0x010212a0
extern "C" void* __cdecl FUN_0093aa70(void* stream, void* data, int n, int a);             // 0x0093aa70
extern "C" void* __cdecl FUN_0093a780(void* stream, void* data, int n, int a);             // 0x0093a780
extern "C" void* __cdecl FUN_00692f90(void* self, void* a, void* b, unsigned c);           // 0x00692f90
extern "C" char  __cdecl FUN_00692900(void* self, void* stream);                           // 0x00692900
extern "C" char  __cdecl FUN_00693e10(void* self, void* stream);                           // 0x00693e10
extern "C" void  __cdecl FUN_00b8fc10(void** out, void* pos, void* key, int b);            // 0x00b8fc10 (thiscall-ish; ECX=tree)
extern "C" void  __cdecl FUN_00b8fc80(void* out, void* key, unsigned b);                   // 0x00b8fc80
extern "C" void* __cdecl FUN_00b8e180(void);                                               // 0x00b8e180
extern "C" void  __cdecl FUN_00b8eaa0(void* p);                                            // 0x00b8eaa0
extern "C" void  __cdecl FUN_00b8db70(void* p);                                            // 0x00b8db70
extern "C" char __cdecl FUN_00b8f230(void* param, void* a, void* b, void* c);   // 0x00b8f230
extern "C" char __cdecl FUN_00b8f470(void* param, void* a, void* b, void* c);   // 0x00b8f470
extern "C" void FUN_00b8fd90();                                                    // 0x00b8fd90
extern "C" void FUN_00b5b960();                                                    // 0x00b5b960
extern "C" void FUN_00b5b9a0();                                                    // 0x00b5b9a0
#define ALLOC_H "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct RCObj { virtual void AddRef(); virtual void Release(); };
inline void AddRef(void* o) { if (o) ((RCObj*)o)->AddRef(); }
inline void Release(void* o) { if (o) ((RCObj*)o)->Release(); }
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
struct TreeNode {
  TreeNode* right;
  TreeNode* left;
  TreeNode* parent;
  int color;
  int k0;              // +0x10
  int k1;              // +0x14
  int k2;              // +0x18
  void* value;         // +0x1c
};
struct RBTree {
  char pad[4];
  TreeNode anchor;        // +4 .. +0x13 (anchor.left/right used as sentinel)
  TreeNode* root;         // +0xc
  char pad2[4];
  int count;              // +0x14
};
struct cPlantCargoInfo {
  void* vf0;                    // +0x00
  char pad0[4];
  void* vf1;                    // +0x08
  void* vf2;                    // +0x0c
  char pad1[0x70];              // +0x10 .. +0x7f
  int   f7c;                    // +0x7c
  int   f80;                    // +0x80
  int   f84;                    // +0x84
  int   f88;                    // +0x88
  int   f8c;                    // +0x8c
  float f90;                    // +0x90
  float f94;                    // +0x94
  float f98;                    // +0x98
  float f9c;                    // +0x9c
  int   fa0;                    // +0xa0
};
struct S {
  // Simulator::cPlantCargoInfo
  cPlantCargoInfo* FUN_00b8f690();                                          // 0x00b8f690
  cPlantCargoInfo* FUN_00b8f730(cPlantCargoInfo* other);                    // 0x00b8f730
  void  FUN_00b8f7f0(void** out);                                           // 0x00b8f7f0
  int   FUN_00b8f860();                                                     // 0x00b8f860
  void  FUN_00b8f9b0(int* out);                                             // 0x00b8f9b0
  char  FUN_00b8fa40(void* stream);                                         // 0x00b8fa40
  char  FUN_00b8fad0(void* stream);                                         // 0x00b8fad0
  char  FUN_00b8fb70();                                                     // 0x00b8fb70
  int   FUN_00b8fbb0(void* src);                                            // 0x00b8fbb0
  void* FUN_00b8fdd0(void** out, TreeNode* pos, int* key);                  // 0x00b8fdd0
  void  FUN_00b8ff60();                                                     // 0x00b8ff60
  void* FUN_00b8ff90();                                                     // 0x00b8ff90
  void* FUN_00b8ffd0(char del);                                             // 0x00b8ffd0
  void* FUN_00b90010(void* key);                                            // 0x00b90010
  void  FUN_00b900a0(void* speciesProfile);                                 // 0x00b900a0
  void* FUN_00b90410(void* key);                                            // 0x00b90410
};
struct ResourceKey { unsigned int a, b, c; };     // plain data (EA::ResourceMan::Key)
class DefaultRefCounted {
public:
  virtual ~DefaultRefCounted();
  virtual void AddRef();
  virtual void Release();
  virtual int  GetReferenceCount();
};
class cSpaceInventoryItem : public DefaultRefCounted {
public:
  virtual int  GetType();
  virtual void SetItemID(ResourceKey* id);
  virtual const ResourceKey* GetItemID();        // vftable0 slot 6 (0x18)
};
// ---- items of slice s00b8f230 end

// @ 0x00b8c0f0
void cPlanetModel::Shutdown()
{
    cMinimapGfx* gfx = mpMinimapGfx;
    RCSub** ppRef = &gfx->mpRefObject;
    if (RCSub* pRef = *ppRef) {
        *ppRef = 0;
        pRef->Release();
    }

    cMinimapGfx* gfx2 = mpMinimapGfx;
    if (gfx2->mbActive) {
        InputManager()->SetMode(9);
        InputManager()->SetMode(0x19);
    }
    gfx2->mbActive = false;

    mSeaTradeRoutes.Clear();
    mLandTradeRoutes.Clear();
    mPathRoutes.Clear();
    mbSeaRoutesDirty = true;
    mbPathRoutesDirty = true;
    mbLandRoutesDirty = true;

    if (mbRegistered) {
        mbRegistered = false;
        MessageServer()->Post(this, 0x1b537e5, 0xffffd8f1);
        MessageServer()->Post(this, 0x182c582, 0xffffd8f1);
        MessageServer()->Post(this, 0x44448ed, 0xffffd8f1);
        MessageServer()->Post(this, 0x45fe992, 0xffffd8f1);
    }

    EffectsManagerPtr()->SetTime(0, -1);
    TerrainEditor()->SetActiveObject(0);
    FUN_00f48af0(0);

    if (mpISphere != 0) {
        cPlanet* pPlanet = mpWorldEditor->v10();
        pPlanet->SetRampEnabled(false);
        mpISphere->SetInputManager(InputManager());
        mpISphere->vAC();
        g_Renderer->SetFlag(0);
        mpISphere->vA4();
        mpISphere->vEC();
        mpISphere->vF8();
        mpWorldEditor->ShutdownScene();
        if (mpWorldEditor != 0) {
            IWorldEditor* pOld = mpWorldEditor;
            mpWorldEditor = 0;
            pOld->v04();
        }
        mpISphere = 0;
    }

    Memset32(mpCellNibbles, 0, 0x3000);

    uint32_t* pCells = mContinentMap;
    for (int i = 0; i < 0x18000; ++i)
        pCells[i] &= 0xc3ffffff;

    Reset();

    if (mpIndexBegin != mpIndexEnd) {
        *mpIndexBegin = 0;
        mpIndexEnd = mpIndexBegin;
    }

    mField2C = IVec3U(0, 0, 0);
}

// @ 0x00b8d8a0
bool cPlanetModel_s00b8_d190::FUN_00b8d8a0(uint32_t a, bool refresh, uint32_t c)
{
    bool inserted = FUN_00b8d750(a, c);
    if (refresh) {
        mField24->v35(FUN_0067dd50());
    }
    return inserted;
}

// @ 0x00b8d8f0
uint32_t cPlanetModel_s00b8_d190::FUN_00b8d8f0()
{
    uint32_t result = ((cStarObject*)SP::StarManager(mField184))->FUN_00ba6440();
    _ReadWriteBarrier();
    return result;
}

// @ 0x00b8d910
void cPlanetModel_s00b8_d190::FUN_00b8d910()
{
    mField2C |= 0x400;
}

// @ 0x00b8d920
void cPlanetModel_s00b8_d190::FUN_00b8d920(bool flag)
{
    mField2C = (mField2C & 0xffffffbfu) | (flag ? 0x40u : 0u);
}

// @ 0x00b8d950
void cPlanetModel_s00b8_d190::FUN_00b8d950(bool flag)
{
    mField2C = (mField2C & 0xfffffeffu) | (flag ? 0x100u : 0u);
}

// @ 0x00b8d980
void cPlanetModel_s00b8_d190::FUN_00b8d980(bool flag)
{
    mField2C = (mField2C & 0xfffffdffu) | (flag ? 0x200u : 0u);
}

// @ 0x00b8d9b0
int32_t cPlanetModel_s00b8_d190::FUN_00b8d9b0()
{
    int32_t result = ((cStarObject*)SP::StarManager((uint32_t)(void*)this))->FUN_00bb99e0();
    if (result == 0) {
        cMission* mission =
            ((cMissionManager*)SP::GetMissionManager((uint32_t)(void*)this))->FUN_00fee220();
        if (mission != 0) {
            return mission->FUN_00c4b220();
        }
    }
    return result;
}

// @ 0x00b8d9f0
bool cPlanetModel_s00b8_d190::FUN_00b8d9f0()
{
    if (mField28 == 0) {
        return false;
    }
    if (mField28 == 1) {
        return false;
    }
    uint32_t state = (mField2C >> 8) & 1;
    if (state != 0) {
        return false;
    }
    if (FUN_00b8d9b0() != 0) {
        return false;
    }
    if (mField2C & 0x800) {
        return false;
    }
    return true;
}

// @ 0x00b8da70
int32_t cPlanetModel_s00b8_d190::FUN_00b8da70()
{
    return (int32_t)mField184 - 0x1000000;
}

// @ 0x00b8dd60
cKey3* cPlanetModel_s00b8_d190::FUN_00b8dd60(cKey3* out)
{
    out->m0 = 0;
    out->m4 = 0;
    out->m8 = 0;
    if (mField1A4 != 0) {
        int32_t found = ((cKeyService*)FUN_00f48a80())->v1(&mField1A4);
        if (found == 0) {
            mField1A4 = 0;
            mField1A8 = 0;
            mField1AC = 0;
            ((cStarObject*)SP::StarManager((uint32_t)(void*)this))->FUN_00ba6660();
            found = ((cKeyService*)FUN_00f48a80())->v1(&mField1A4);
            if (found == 0) {
                return out;
            }
        }
        SP::GetPropertyAsKey((uint32_t)found, 0x3d03f84, out);
    }
    return out;
}

// @ 0x00b8dde0
void cPlanetModel_s00b8_d190::FUN_00b8dde0(cKey3* key, int32_t unused)
{
    if (key->m0 != mField1A4 || key->m4 != mField1A8 || key->m8 != mField1AC) {
        mField1A4 = key->m0;
        mField1A8 = key->m4;
        mField1AC = key->m8;
    }
}

// @ 0x00b8de60
void cPlanetModel_s00b8_d190::FUN_00b8de60()
{
    while (mField15C != mField160) {
        cOwnedElem* element = *(cOwnedElem**)(mField160 - 4);
        mField160 -= 4;
        if (element != 0) {
            element->FUN_00ff2e30();
            FUN_00f47380(element);
        }
    }
}

// @ 0x00b8dec0
int32_t cPlanetModel_s00b8_d190::FUN_00b8dec0(int32_t index)
{
    if (index < (int32_t)(mField160 - mField15C) >> 2) {
        return *(int32_t*)(mField15C + index * 4);
    }
    return 0;
}

// @ 0x00b8def0
int32_t cPlanetModel_s00b8_d190::FUN_00b8def0(int32_t index)
{
    if (index < (int32_t)(mField174 - mField170) >> 2) {
        return *(int32_t*)(mField170 + index * 4);
    }
    return 0;
}

// @ 0x00b8df20
void cPlanetModel_s00b8_d190::FUN_00b8df20()
{
    while (mField170 != mField174) {
        void* element = *(void**)(mField174 - 4);
        mField174 -= 4;
        if (element != 0) {
            ((cOwnedElem2*)element)->FUN_00c2e4e0();
            FUN_00f47380(element);
        }
    }
}

// @ 0x00b8df80
void cPlanetModel_s00b8_d190::FUN_00b8df80(int32_t index)
{
    int32_t count = (int32_t)((char*)mField160 - (char*)mField15C) >> 2;
    if (index >= count) {
        return;
    }
    int32_t* element = (int32_t*)FUN_00b8dec0(index);
    if (element != 0) {
        ((cOwnedElem*)element)->FUN_00ff2e30();
        FUN_00f47380(element);
    }
    int32_t* end = (int32_t*)mField160;
    int32_t* begin = (int32_t*)mField15C;
    int32_t value = *--end;
    begin[index] = value;
    mField160 = (char*)end;
}

// @ 0x00b8dfe0
void cPlanetModel_s00b8_d190::FUN_00b8dfe0(int32_t index)
{
    int32_t count = (int32_t)((char*)mField174 - (char*)mField170) >> 2;
    if (index >= count) {
        return;
    }
    int32_t* element = (int32_t*)FUN_00b8def0(index);
    if (element != 0) {
        ((cOwnedElem2*)element)->FUN_00c2e4e0();
        FUN_00f47380(element);
    }
    int32_t* end = (int32_t*)mField174;
    int32_t* begin = (int32_t*)mField170;
    int32_t value = *--end;
    begin[index] = value;
    mField174 = (char*)end;
}

// @ 0x00b8e040
bool cPlanetModel_s00b8_d190::FUN_00b8e040(uint32_t id)
{
    int32_t count = (int32_t)((mField138 - mField134) / 0x2c);
    for (int32_t i = 0; i < count; ++i) {
        if (((cBioElem*)mField134)[i].m00 == (int32_t)id) {
            return true;
        }
    }
    return false;
}

// @ 0x00b8e090
cKey3* cPlanetModel_s00b8_d190::FUN_00b8e090()
{
    static cKey3 sEmptyKey;
    if (mField194 > 1) {
        uint32_t banner = ((cStarObject*)SP::StarManager(mField184))->FUN_00ba6440();
        uint32_t list = ((cStarObject*)SP::StarManager(banner))->FUN_00ba6d80();
        return (cKey3*)((cStarObject*)list)->FUN_00bb9b80();
    }
    return &sEmptyKey;
}

// @ 0x00b8e0f0
void* __cdecl FUN_00b8e0f0(void** out, const cBioElem* first, const cBioElem* last, cBioElem* dest)
{
    *out = dest;
    while (first != last) {
        if (dest != 0) {
            *dest = *first;
        }
        ++first;
        ++dest;
    }
    *out = dest;
    return out;
}

// @ 0x00b8e180
void cPropertyList::Ctor()
{
    undefined4* p = (undefined4*)this;
    p[0] = (undefined4)0x013ebcdc;       // PropBaseA22 vtable
    _InterlockedExchange((volatile long*)(p + 1), 0);
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[0] = (undefined4)0x014655a0;       // Editor::cPropertyList vtable
    p[8] = (undefined4)0x01667bae;
    p[6] = (undefined4)0x01667bac;       // eastl::gEmptyString16
    p[7] = (undefined4)0x01667bac;
    p[0xb] = 0;
    p[10] = 0xffffffff;
    *((uint8_t*)p + 0x30) = 1;
    *((uint8_t*)p + 0x98) = 1;
    *((float*)p + 0x27) = *(const float*)0x0156b730;
    *((float*)p + 0x28) = *(const float*)0x0156b734;
    *((float*)p + 0x29) = *(const float*)0x0156b738;
    *((float*)p + 0x2a) = *(const float*)0x01485720;
    *((float*)p + 0x2c) = *(const float*)0x013eb1bc;
    *((float*)p + 0x2d) = *((float*)p + 0x2c);
    *((float*)p + 0x2e) = *((float*)p + 0x2c);
    *((uint8_t*)p + 0xac) = 0xff;
    *((uint8_t*)p + 0xad) = 0xff;
    p[0x2f] = 0; p[0x30] = 0; p[0x31] = 0;
    p[0x34] = 0; p[0x35] = 0; p[0x36] = 0;
    p[0x39] = 0; p[0x3a] = 0; p[0x3b] = 0;
    p[0x3e] = 0; p[0x3f] = 0; p[0x40] = 0;
    p[0x44] = 0; p[0x45] = 0; p[0x46] = 0;
    p[0x49] = 0; p[0x4a] = 0; p[0x4b] = 0;
    *((uint8_t*)p + 0x130) = 0;
    p[0x4d] = 0; p[0x4e] = 0; p[0x4f] = 0;
    p[0x52] = 0; p[0x53] = 0; p[0x54] = 0;
    p[0x57] = 0; p[0x58] = 0; p[0x59] = 0;
    p[0x5c] = 0; p[0x5d] = 0; p[0x5e] = 0;
    p[0x61] = 0xffffffff;
    p[0x62] = 0; p[99] = 0; p[100] = 0; p[0x65] = 0;
    p[0x66] = *(const uint32_t*)0x016882ac;
    p[0x67] = *(const uint32_t*)0x016882b0;
    p[0x68] = *(const uint32_t*)0x016882b4;
    p[0x69] = 0; p[0x6a] = 0; p[0x6b] = 0;
}

// @ 0x00b8e3f0
void cPropertyList::AssignRange(const Vec4& r)
{
    int* a = (int*)this;
    if (r.mpBegin != r.mpEnd && (a[0x2c / 4] & 1) == 0 && (const int*)&r != a + 6)
        WString_Assign(r.mpBegin, r.mpEnd);
}

// @ 0x00b8e590
bool __cdecl TypedMatcherMatch(IMatcher* self, const char* key, const void* value, const void* typeName)
{
    void* gEmpty = (void*)0x01667bac;
    WString16 valueStr;
    valueStr.mpBegin = gEmpty;
    valueStr.mpEnd = gEmpty;
    valueStr.mpCapacity = (void*)0x01667bad;
    TypedValueWrite(&valueStr, value);
    bool result = true;
    if (valueStr.mpBegin == valueStr.mpEnd)
        goto cleanup_value;

    {
        WString16 keyTmp;
        WString16 keyCopy;
        if (key == 0) {
            keyTmp.mpBegin = gEmpty;
            keyTmp.mpEnd = gEmpty;
            keyTmp.mpCapacity = (void*)0x01667bae;
        } else {
            ConvertToString16Impl(&keyTmp, key, 0xffffffff);
        }
        keyCopy.CopyFrom(keyTmp);
        if ((int)(((int)keyTmp.mpCapacity - (int)keyTmp.mpBegin) & 0xfffffffe) > 2
                && keyTmp.mpBegin != 0)
            operator_delete(keyTmp.mpBegin);

        WString16 valueCopy;
        ConvertToString16(&valueCopy, &valueStr);

        bool matched = false;
        if (keyCopy.mpBegin == keyCopy.mpEnd) {
            if (self->M0(typeName) != 0 && self->M3(valueCopy.mpBegin) != 0)
                matched = true;
        } else {
            char c = self->M0(keyCopy.mpBegin);
            if (g_flag15d8b4c == 0) {
                if (c != 0 && self->M3(valueCopy.mpBegin) != 0)
                    matched = true;
            } else if (c != 0) {
                if (self->M2((const void*)0x013f36bc, typeName) != 0
                        && self->M3(valueCopy.mpBegin) != 0)
                    matched = true;
            }
        }
        if (keyCopy.mpBegin == keyCopy.mpEnd) {
            if (!matched || self->M1(typeName) == 0)
                result = false;
        } else {
            if (!matched || self->M1(keyCopy.mpBegin) == 0)
                result = false;
        }
        if ((int)(((int)valueCopy.mpCapacity - (int)valueCopy.mpBegin) & 0xfffffffe) > 2
                && valueCopy.mpBegin != 0)
            operator_delete(valueCopy.mpBegin);
        if ((int)(((int)keyCopy.mpCapacity - (int)keyCopy.mpBegin) & 0xfffffffe) > 2
                && keyCopy.mpBegin != 0)
            operator_delete(keyCopy.mpBegin);
    }

cleanup_value:
    if ((int)(((int)valueStr.mpCapacity - (int)valueStr.mpBegin) & 0xfffffffe) > 2
            && valueStr.mpBegin != 0)
        operator_delete(valueStr.mpBegin);
    return result;
}

// @ 0x00b8e760
void cPropertyList::PurgeEmptyRules()
{
    int* a = (int*)this;
    int* dst = (int*)a[0x15c / 4];
    if (dst == (int*)a[0x160 / 4])
        return;
    int* src = dst + 1;
    do {
        int* o = (int*)*dst;
        if (((o[0x40 / 4] - o[0x3c / 4]) & 0xfffffffc) == 0) {
            if (o != 0) {
                ObjDtor(o);
                operator_delete(o);
            }
            if (src < (int*)a[0x160 / 4])
                VectorInsert(dst, src, (unsigned)((int)a[0x160 / 4] - (int)src));
            a[0x160 / 4] -= 4;
        } else {
            dst++;
            src++;
        }
    } while (dst != (int*)a[0x160 / 4]);
}

// @ 0x00b8e7d0
void cPropertyList::EraseRule(int key)
{
    int* a = (int*)this;
    Rule* p = (Rule*)a[0x134 / 4];
    Rule* end = (Rule*)a[0x138 / 4];
    for (; p != end; p++)
        if (*(int*)p == key)
            break;
    if (p == end)
        return;
    Rule* q = p + 1;
    if (q < end) {
        do {
            *p = *q;
            p++;
            q++;
        } while (q != end);
    }
    a[0x138 / 4] -= 0x2c;
}

// @ 0x00b8e830
void cPropertyList::EraseAllRules()
{
    PtrVec* v = (PtrVec*)this;
    v->eraseRange(v->begin, v->end);
}

// @ 0x00b8e860
void cPropertyList::Dtor()
{
    int* a = (int*)this;
    mvtbl = (void*)0x014655a0;
    // +0x170: vector of LayoutElem*
    {
        int n = (a[0x174 / 4] - a[0x170 / 4]) >> 2;
        for (int i = 0; i < n; i++) {
            int v = ((int*)a[0x170 / 4])[i];
            if (v != 0) { ElemDtor(v); operator_delete((void*)v); }
        }
        int end = a[0x174 / 4], beg = a[0x170 / 4];
        VectorInsert((void*)beg, (void*)end, 0);
        a[0x174 / 4] += ((end - beg) >> 2) * -4;
    }
    // +0x15c: vector of RuleObj*
    {
        int n = (a[0x160 / 4] - a[0x15c / 4]) >> 2;
        for (int i = 0; i < n; i++) {
            int v = ((int*)a[0x15c / 4])[i];
            if (v != 0) { ObjDtor(v); operator_delete((void*)v); }
        }
        int end = a[0x160 / 4], beg = a[0x15c / 4];
        VectorInsert((void*)beg, (void*)end, 0);
        a[0x160 / 4] += ((end - beg) >> 2) * -4;
    }
    // +0xe4: vector of raw pointers
    {
        int n = (a[0xe8 / 4] - a[0xe4 / 4]) >> 2;
        for (int i = 0; i < n; i++)
            operator_delete((void*)((int*)a[0xe4 / 4])[i]);
        int end = a[0xe8 / 4], beg = a[0xe4 / 4];
        VectorInsert((void*)beg, (void*)end, 0);
        a[0xe8 / 4] += ((end - beg) >> 2) * -4;
    }
#define FREE_OWNED(off) { int v = a[(off) / 4]; \
        if (v != 0 && *(int*)(v - 4) != 0) operator_delete((void*)v); }
    FREE_OWNED(0x170) FREE_OWNED(0x15c) FREE_OWNED(0x148) FREE_OWNED(0x134)
    FREE_OWNED(0x110) FREE_OWNED(0xf8)  FREE_OWNED(0xe4)  FREE_OWNED(0xd0)
    FREE_OWNED(0xbc)
#undef FREE_OWNED
    {
        int b = a[0x18 / 4], e = a[0x20 / 4];
        if ((int)((e - b) & 0xfffffffe) > 2 && b != 0)
            operator_delete((void*)b);
    }
    mvtbl = (void*)0x013eb938;   // GmeEditorResBase vtable
}

// @ 0x00b8eaa0
static void* Reader(ISerialStream* s)
{
    ISerializer* ser = (ISerializer*)s->GetSerializer();
    return ser->GetReader();
}

// @ 0x00b8ef40
PtrVec* PtrVec::assignSlow(const PtrVec& o)
{
    if (&o == this)
        return this;
    int n = (int)((char*)o.end - (char*)o.begin) >> 2;
    if ((unsigned)((int)((char*)cap - (char*)begin) >> 2) < (unsigned)n) {
        void* p = allocateToFit((unsigned)n, o.begin, o.end);
        if (begin != 0 && *(int*)((int)begin - 4) != 0)
            operator_delete(begin);
        begin = p;
        cap = (void*)((int)p + n * 4);
        end = (void*)((int)p + n * 4);
        return this;
    }
    unsigned have = (unsigned)((int)((char*)end - (char*)begin) >> 2);
    if (have < (unsigned)n) {
        VectorInsert(begin, o.begin, have * 4);
        void* src = (void*)((int)o.begin + ((int)((char*)end - (char*)begin) >> 2) * 4);
        VectorInsert(end, src, (unsigned)((int)((char*)o.end - (int)src)));
        end = (void*)((int)begin + n * 4);
        return this;
    }
    VectorInsert(begin, o.begin, (unsigned)((int)((char*)o.end - (int)o.begin)));
    end = (void*)((int)begin + n * 4);
    return this;
}

// @ 0x00b8f030
cPropertyList& cPropertyList::AssignCopy(const cPropertyList& o)
{
    int* a = (int*)this;
    const int* b = (const int*)&o;
    if ((void*)((int)b + 0x18) != (void*)(a + 6))
        WString_Assign((const void*)b[0x18 / 4], (const void*)b[0x1c / 4]);
    a[0x28 / 4] = b[0x28 / 4];
    a[0x2c / 4] = b[0x2c / 4];
    {
        const int* s = b + 0x30 / 4;
        int* d = a + 0x30 / 4;
        for (int i = 0x1a; i != 0; i--)
            *d++ = *s++;
    }
    *(uint8_t*)((int)a + 0x98) = *(const uint8_t*)((int)b + 0x98);
    a[0x9c / 4] = b[0x9c / 4];
    a[0xa0 / 4] = b[0xa0 / 4];
    a[0xa4 / 4] = b[0xa4 / 4];
    a[0xa8 / 4] = b[0xa8 / 4];
    *(uint8_t*)((int)a + 0xac) = *(const uint8_t*)((int)b + 0xac);
    *(uint8_t*)((int)a + 0xad) = *(const uint8_t*)((int)b + 0xad);
    a[0xb0 / 4] = b[0xb0 / 4];
    a[0xb4 / 4] = b[0xb4 / 4];
    a[0xb8 / 4] = b[0xb8 / 4];
    KeyVecAssign((int)a + 0xbc, (int)b + 0xbc);
    KeyVecAssign((int)a + 0xd0, (int)b + 0xd0);
    PtrVecAssign((int)a + 0xe4, (int)b + 0xe4);
    FloatVecAssign((int)a + 0xf8, (int)b + 0xf8);
    a[0x10c / 4] = b[0x10c / 4];
    FloatVecAssign((int)a + 0x110, (int)b + 0x110);
    a[0x124 / 4] = b[0x124 / 4];
    a[0x128 / 4] = b[0x128 / 4];
    a[0x12c / 4] = b[0x12c / 4];
    *(uint8_t*)((int)a + 0x130) = *(const uint8_t*)((int)b + 0x130);
    RuleVecAssign((int)a + 0x134, (int)b + 0x134);
    FloatVecAssign((int)a + 0x148, (int)b + 0x148);
    PtrVecAssign((int)a + 0x15c, (int)b + 0x15c);
    PtrVecAssign((int)a + 0x170, (int)b + 0x170);
    a[0x184 / 4] = b[0x184 / 4];
    a[0x194 / 4] = b[0x194 / 4];
    a[0x198 / 4] = b[0x198 / 4];
    a[0x19c / 4] = b[0x19c / 4];
    a[0x1a0 / 4] = b[0x1a0 / 4];
    {
        const int* s = b + 0x1a4 / 4;
        int* d = a + 0x1a4 / 4;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
    }
    return *this;
}

// @ 0x00b8f230
char __cdecl FUN_00b8f230(void* param, void* a, void* b, void* c)
{
  (void)a; (void)b; (void)c;
  void* buf = EastlNew(50000, "Simulator", 0, 0, 0, 0);
  char* stream = (char*)param;
  char* io = (char*)((void* (*)(void*))VFn(stream, 0x18))(stream);   // param->vfn[0x18]() -> stream
  unsigned readv = 0;
  FUN_0093a780(io, &readv, 1, 0);         // ReadInt32(io, &local, 1, 0)
  int len = (int)((int (*)(void*))VFn(io, 0x1c))(io);
  ((void (*)(void*, int))VFn(io, 0x30))(io, len);

  int zu = 0;
  void* mem = EA_ZoneNew(0x18, "App/memorystream", 0, 0, 0, 0);
  if (mem) { mem = (void*)((void* (*)(void*, int))0x00d9a1b0)(mem, 0); }

  int l2 = (int)((int (*)(void*))VFn(stream, 0x1c))(stream);
  FUN_0093b8e0(buf, l2);
  ((void (*)(void*, int))VFn(mem, 0x28))(mem, 0);
  zu = 0;

  void* dpf = EA_ZoneNew(0x388, "Simulator", 0, 0, 0, 0);
  if (dpf) { dpf = (void*)((void* (*)(void*, int, int))0x008d9f80)(dpf, 0, 0); }

  void* odb = EA_ZoneNew(0x24, "Simulator", 0, 0, 0, 0);
  if (odb) { odb = (void*)((void* (*)(void*, void*))0x0069fa60)(odb, dpf); }

  ((void (*)(void*, void*, int))VFn(dpf, 0x50))(dpf, mem, 0);
  ((void (*)(void*, int, int))VFn(odb, 0x3c))(odb, 1, 0);
  ((void (*)(void*, int))VFn(odb, 0x20))(odb, zu);
  FUN_00693cd0(odb, 1, 1, 1);
  FUN_00692ea0();
  FUN_00692ec0(0);

  void* res = EA_ZoneNew(0x1b0, "Simulator", 0, 0, 0, 0);
  if (res) res = FUN_00b8e180();
  *(void**)b = res;                         // *unaff_EBP = res
  ((void (*)(void*))VFn(res, 0))(res);
  FUN_00b8eaa0(0);
  FUN_00693900();
  ((void (*)(void*))VFn(odb, 0x1c))(odb);
  ((void (*)(void*))VFn(odb, 0x08))(odb);
  EastlDelete(0);
  ((void (*)(void*))VFn(odb, 0x04))(odb);
  ((void (*)(void*))VFn(dpf, 0x04))(dpf);
  ((void (*)(void*))VFn(mem, 0x08))(mem);
  return 1;
}

// @ 0x00b8f470
char __cdecl FUN_00b8f470(void* param, void* a, void* b, void* c)
{
  (void)a; (void)b; (void)c;
  void* buf = EastlNew(50000, "Simulator", 0, 0, 0, 0);
  char* stream = (char*)param;
  int* io = (int*)VFn(stream, 0x18);
  (void)io;

  void* mem = EA_ZoneNew(0x18, "App/memorystream", 0, 0, 0, 0);
  if (mem) { mem = (void*)((void* (*)(void*, int))0x00d9a1b0)(mem, 0); }

  FUN_0093b8e0(buf, 50000);
  ((void (*)(int))VFn(mem, 0x20))(0);
  ((void (*)(int, int))VFn(mem, 0x28))(0, 0);

  void* dpf = EA_ZoneNew(0x388, "Simulator", 0, 0, 0, 0);
  if (dpf) { dpf = (void*)((void* (*)(void*, int, int))0x008d9f80)(dpf, 0, 0); }

  void* odb = EA_ZoneNew(0x24, "Simulator", 0, 0, 0, 0);
  if (odb) { odb = (void*)((void* (*)(void*, void*))0x0069fa60)(odb, dpf); }

  ((void (*)(void*, int))VFn(odb, 0x3c))(odb, 1);
  FUN_00693d60(odb, 1, 1, 1);
  FUN_00692ea0();
  ((void (*)(void*))VFn(odb, 0x2c))(odb);
  ((void (*)(void*))VFn(odb, 0x1c))(odb);
  ((void (*)(void*))VFn(odb, 0x08))(odb);
  FUN_00b8db70(0);

  void* p1 = VFn(mem, 0x18);
  (void)p1;
  int iVar2 = (int)VFn(mem, 0x1c);
  FUN_0093aa70(io, 0, 1, 0);              // WriteUint32(io, &val, 1, 0)
  void* w = VFn(io, 0x18);
  ((void (*)(int, int))VFn(w, 0x38))(iVar2, 0);
  EastlDelete(0);
  ((void (*)(void*))VFn(odb, 0x04))(odb);
  ((void (*)(void*))VFn(dpf, 0x04))(dpf);
  ((void (*)(void*))VFn(mem, 0x08))(mem);
  return 1;
}

// @ 0x00b8f690
cPlantCargoInfo* S::FUN_00b8f690()
{
  cPlantCargoInfo* self = (cPlantCargoInfo*)this;
  ((void (__thiscall*)(void*))0x00c87660)(this);   // Simulator::cAnimalCargoInfo ctor
  self->f90 = *(float*)0x01470f1c;
  self->f7c = 0;
  self->f80 = 0;
  self->f84 = 0;
  self->f88 = 0;
  self->f8c = 0;
  self->fa0 = 0;
  self->vf0 = (void*)0x01465798;
  self->vf1 = (void*)0x01465790;
  self->vf2 = (void*)0x0146576c;
  self->f94 = 0.0f;
  self->f98 = 0.0f;
  self->f9c = 0.0f;
  return self;
}

// @ 0x00b8f730
cPlantCargoInfo* S::FUN_00b8f730(cPlantCargoInfo* other)
{
  char* self = (char*)this;
  ((void (__thiscall*)(void*, void*))0x00c870b0)(this, other);
  if (self != (char*)other) {
    *(int*)(self + 0x7c) = *(int*)((char*)other + 0x7c);
    *(int*)(self + 0x80) = *(int*)((char*)other + 0x80);
    *(int*)(self + 0x84) = *(int*)((char*)other + 0x84);
    *(int*)(self + 0x88) = *(int*)((char*)other + 0x88);
    *(int*)(self + 0x8c) = *(int*)((char*)other + 0x8c);
    *(float*)(self + 0x90) = *(float*)((char*)other + 0x90);
    *(float*)(self + 0x94) = *(float*)((char*)other + 0x94);
    *(float*)(self + 0x98) = *(float*)((char*)other + 0x98);
    *(float*)(self + 0x9c) = *(float*)((char*)other + 0x9c);
    *(int*)(self + 0xa0) = *(int*)((char*)other + 0xa0);
  }
  return (cPlantCargoInfo*)self;
}

// @ 0x00b8f7f0
void S::FUN_00b8f7f0(void** out)
{
  cPlantCargoInfo* p = (cPlantCargoInfo*)EastlNew(0xa4, "Simulator/cPlantCargoInfo", 0, 0, 0, 0);
  if (p == 0) { *out = 0; return; }
  int* q = (int*)((cPlantCargoInfo* (__thiscall*)(void*))0x00b8f690)(p);
  if (q) {
    ((cPlantCargoInfo* (__thiscall*)(void*, cPlantCargoInfo*))0x00b8f730)(q, (cPlantCargoInfo*)this);
    ((void (*)(void*))VFn(q, 0x04))(q);
    *out = q;
    return;
  }
  *out = 0;
}

// @ 0x00b8f860
int S::FUN_00b8f860()
{
  char* self = (char*)this;
  int a0 = *(int*)(self + 0xa0);
  if (a0 != 0) {
    int v = *(int*)(a0 + 0x57c);
    switch (v) {
      case (int)0xb8669ec9: return 0x29c388a;
      case (int)0xbcd73e89: return 0x6d60a1cc;
      case 0x37148141:      return 0x3a8be428;
    }
  }
  return 0x6d60a1cc;
}

// @ 0x00b8f9b0
void S::FUN_00b8f9b0(int* out)
{
  char* self = (char*)this;
  int p = *(int*)(self + 0xa0);
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;
  if (p != 0) {
    int v = *(int*)(p + 0x57c);
    if (v == (int)0xb8669ec9) {
      out[0] = *(int*)0x0156bd20;
      out[1] = *(int*)0x0156bd24;
      out[2] = *(int*)0x0156bd28;
      return;
    }
    if (v != (int)0xbcd73e89 && v == 0x37148141) {
      out[0] = *(int*)0x0156bd14;
      out[1] = *(int*)0x0156bd18;
      out[2] = *(int*)0x0156bd1c;
      return;
    }
  }
  out[0] = *(int*)0x0156bd2c;
  out[1] = *(int*)0x0156bd30;
  out[2] = *(int*)0x0156bd34;
}

// @ 0x00b8fa40
char S::FUN_00b8fa40(void* stream)
{
  unsigned key = 0x70a2863c;
  int* io = (int*)VFn(stream, 0x20);
  void* w = VFn(io, 0x18);
  FUN_0093aa70(w, &key, 1, 0);
  char c1 = FUN_00c87580(stream);
  char buf[0xa14];
  FUN_00692f90(buf, (char*)this - 0xc, (void*)0x0156bd78, 0x1a80d26);
  char c2 = FUN_00692900(buf, stream);
  return (c2 != 0 && c1 != 0) ? 1 : 0;
}

// @ 0x00b8fad0
char S::FUN_00b8fad0(void* stream)
{
  unsigned key = 0;
  int* io = (int*)VFn(stream, 0x20);
  void* r = VFn(io, 0x18);
  FUN_0093a780(r, &key, 1, 0);
  char c1 = FUN_00c879a0(stream);
  char buf[0xa14];
  FUN_00692f90(buf, (char*)this - 0xc, (void*)0x0156bd78, 0x1a80d26);
  char c2 = FUN_00693e10(buf, stream);
  char ok;
  if (c2 != 0 && c1 != 0) ok = 1; else ok = 0;
  char* self = (char*)this;
  void* mgr = FUN_00401090(self + 0x50);
  *(void**)(self + 0x94) = FUN_004df440(mgr, self + 0x50);
  return ok;
}

// @ 0x00b8fb70
char S::FUN_00b8fb70()
{
  char* self = (char*)this;
  char result = 0;
  char* p = (char*)FUN_010212a0();
  if (p != 0) {
    char* first = *(char**)(p + 0xbc);
    char* last = *(char**)(p + 0xc0);
    const ResourceKey* id = ((cSpaceInventoryItem*)self)->GetItemID();
    void* res = FUN_00ac0d80(first, last, (void*)id);
    result = (last != res);
  }
  return result;
}

// @ 0x00b8fbb0
int S::FUN_00b8fbb0(void* src)
{
  int node = (int)EastlNew(0x20, "Simulator", 0, 0, (const char*)ALLOC_H, 0xd1);
  char* e = (char*)(node + 0x10);
  if (e != 0) {
    *(int*)(e + 0x0) = *(int*)((char*)src + 0x0);
    *(int*)(e + 0x4) = *(int*)((char*)src + 0x4);
    *(int*)(e + 0x8) = *(int*)((char*)src + 0x8);
    int r = *(int*)((char*)src + 0xc);
    *(int*)(e + 0xc) = r;
    if (r != 0) (*(void(__thiscall*)(void*))((*(void***)r)[1]))((void*)r);
  }
  return node;
}

// @ 0x00b8fdd0
void* S::FUN_00b8fdd0(void** out, TreeNode* pos, int* key)
{
  char* self = (char*)this;
  RBTree* tree = (RBTree*)this;
  char* anchor = self + 4;
  if ((char*)pos != *(char**)anchor || (char*)pos == anchor) {
    // (both "empty" conditions funnel to the fast path below)
  }
  if ((char*)pos == (char*)tree->root) {
    // param_3 == tree->root (== *(int**)(param_1+4)) or == anchor
  }
  {
    char* p4 = (char*)pos;
    TreeNode* inc;
    if ((char*)pos == (char*)tree->root || (char*)pos == anchor) {
      if (tree->count != 0) {
        TreeNode* root = tree->root;
        bool lt = (unsigned)root->k0 < (unsigned)key[0];
        if (root->k0 == key[0] && (lt = (unsigned)root->k2 < (unsigned)key[2], root->k2 == key[2]))
          lt = (unsigned)root->k1 < (unsigned)key[1];
        if (lt) {
          FUN_00b8fc10(out, root, key, 0);
          return out;
        }
      }
      char tmp[8];
      FUN_00b8fc80(tmp, key, 0);
      *out = *(void**)tmp;
      return out;
    }
    inc = ((TreeNode* (*)(void*))0x00921580)(p4);        // RBTreeIncrement
    bool lt = (unsigned)pos->k0 < (unsigned)key[0];
    if (pos->k0 == key[0] && (lt = (unsigned)pos->k2 < (unsigned)key[2], pos->k2 == key[2]))
      lt = (unsigned)pos->k1 < (unsigned)key[1];
    if (lt) {
      bool lt2 = (unsigned)key[0] < (unsigned)inc->k0;
      if (key[0] == inc->k0 && (lt2 = (unsigned)key[2] < (unsigned)inc->k2, key[2] == inc->k2))
        lt2 = (unsigned)key[1] < (unsigned)inc->k1;
      if (lt2) {
        if ((char*)pos != 0) {
          int n = FUN_00b8fbb0(key);
          ((void (*)(int, TreeNode*, char*, int))0x009216a0)(n, inc, anchor, 0);
          tree->count += 1;
          *out = (void*)n;
          return out;
        }
        FUN_00b8fc10(out, pos, key, 0);
        return out;
      }
    }
    char tmp[8];
    FUN_00b8fc80(tmp, key, 0);
    *out = *(void**)tmp;
    return out;
  }
  (void)0;
}

// @ 0x00b8ff60
void S::FUN_00b8ff60()
{
  char* self = (char*)this;
  char* esi = self + 0x1c;
  *(char*)(self + 0x38) = 0;
  char* p = *(char**)(esi + 0xc);
  ((void (__thiscall*)(char*, char*))FUN_00b8fd90)(esi, p);
  char* a = esi + 4;
  *(int*)(esi + 0xc) = 0;
  *(char*)(esi + 0x10) = 0;
  *(int*)(esi + 0x14) = 0;
  *(int*)(esi + 8) = (int)a;
  *(int*)a = (int)a;
}

// @ 0x00b8ff90
void* S::FUN_00b8ff90()
{
  char* self = (char*)this;
  ((void (__thiscall*)(void*))FUN_00b5b960)(self);       // SP::cGonzagoSubsystem ctor
  *(void**)(self + 0x00) = (void*)0x01465858;
  *(void**)(self + 0x04) = (void*)0x01465850;
  _ReadWriteBarrier();
  char* eax = self + 0x20;
  *(int*)(eax + 4) = 0;
  *(int*)(eax + 8) = 0;
  *(int*)(eax + 0xc) = 0;
  *(int*)(self + 0x24) = (int)eax;
  *(int*)eax = (int)eax;
  *(int*)(self + 0x28) = 0;
  *(char*)(self + 0x2c) = 0;
  *(int*)(self + 0x30) = 0;
  *(char*)(self + 0x38) = 0;
  return self;
}

// @ 0x00b8ffd0
void* S::FUN_00b8ffd0(char del)
{
  char* self = (char*)this;
  char* ecx = self + 0x1c;
  *(void**)(self + 0x00) = (void*)0x01465858;
  *(void**)(self + 0x04) = (void*)0x01465850;
  char* p = *(char**)(ecx + 0xc);
  ((void (__thiscall*)(char*, char*))FUN_00b8fd90)(ecx, p);
  ((void (__thiscall*)(void*))FUN_00b5b9a0)(self);       // SP::cGonzagoSubsystem dtor
  if (del & 1) EastlDelete(self);
  return self;
}
