// src/game/SPGonzago/SPOrnament.cpp -- migrated from slice(s) s00c8db30, s00c8c9d0, s00c68280, s00c404c0, s00c3ee20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPOrnament.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cHitSphere.h"
#include "SP/cInteractableObject.h"
#include "SP/cOrnament.h"
#include "SP/cSolarHitSphere.h"
#include "SP/cSpatialObject.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCombatant.h"
#include "SP/cInterCityRoad.h"
#include <new>
#include "SP/cMovableDestructibleOrnament.h"
#include "SP/cLocomotiveObject.h"
#include <stdlib.h>
#include <math.h>
#include "SP/cCity.h"
#include "SP/cCivData.h"
#include "SP/cPlanet.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTotemPole.h"

// unnamed retail callees and globals (address in the comment)
extern const void* sOrnamentFields;

// ---- items of slice s00c3ee20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned int uintptr_t;
#define nullptr 0
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);   // 0x0c
    virtual void v10();
};
class IOStream {
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
    virtual IOStream* GetStream();         // 0x20
    virtual void GetStream2();             // 0x24
    virtual void ReadBlock(void* pDest, uint nCount);   // 0x34
};
class ISerializer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual bool Serialize(void* pData);
    virtual int GetFields(int nFlags);
    virtual IOStream* GetStream();
    virtual void ReadBlock(void* pDest, int nCount);
};
void WriteUint32(IOStream* pStream, void* pSource, int nCount, int bFlag);
class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const void* pFields, int nFlags);
    bool Serialize(void* pData);
    int GetFields(int nFlags);
    uint8_t mPad00[0x414];
};
class cSpatialObject : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual Vec3* GetPosition();          // 0x2c
    virtual Vec3* GetDirection();         // 0x30
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
    virtual void va8(int nState, int bA, int bB);   // 0xac
    virtual void* GetModel();                        // 0xb0
    virtual void vb4();
    virtual void vb8();
    virtual void vbc(int a);
    virtual void vc0();
    virtual bool vc4();

    Vec3 mPosition;                 // 0x04
    uint8_t mPad10[0x24];           // 0x10
    Vec3 mLocalExtentsMin;          // 0x34
    Vec3 mLocalExtentsMax;          // 0x40
    Vec3 mOriginalExtentsLower;     // 0x4c
    Vec3 mOriginalExtentsUpper;     // 0x58
    float mFootprintRadius;         // 0x64
    uint8_t mPad68[0x20];           // 0x68
    uint32_t mFlags;                // 0x88
    uint8_t mPad8c[0x18];           // 0x8c
    uint8_t mVisible;               // 0xa4
    uint8_t mHidden;                // 0xa5
    uint8_t mPadA6[0x87];           // 0xa6
    uint8_t mModelStateIndex;       // 0x12d
    uint8_t mPad12e[0x02];          // 0x12e
    uint8_t mModelReady;            // 0x130

    bool LoadModel(void* pModel);
    bool Write(void* pData);
};
class cGameData : public cSpatialObject {
public:
    bool Read(void* pData);
    bool Write(void* pData);
    bool Init(void* pData, int a, int b);
    int GetFieldValues(int nFlags);
    void RemoveOwner();
};
class cInteractableObject : public cGameData {
public:
    uint8_t mPad134[0x50];          // 0x134
    uint64_t mDefinitionWord;       // 0x184
    uint32_t mModelId;              // 0x18c
    uint32_t mOrnamentId;           // 0x190
    float mScale;                   // 0x194
    uint8_t mPad198[0x14];          // 0x198
    IRefCounted* mpOwner;           // 0x1ac
    uint32_t mEffectState;          // 0x1b0
    uint8_t mPad1b4[0x08];          // 0x1b4

    cInteractableObject();
    bool Write(void* pData);
    bool Read(void* pData);
    int GetFieldValues(int nFlags);
    void SetEffectId(int nEffectId);
    bool LoadModelChecked(void* pModel);
    void SetModelState(int nState, bool bForce);
    bool InitFromDefinition(void* pData, int a, uint flags);
    void Destroy(int bDelete);
    void Shutdown();
    void AttachEffect(void* pEffect);
    void ClearEffectState();
};
class cInteractiveOrnament : public cInteractableObject {
public:
    uint8_t mPad1bc[0x84];          // 0x1bc
    int mDestructedState;           // 0x240
    int mDestructedCount;           // 0x244
    int mDestructedStep;            // 0x248
    int mDestructedMax;             // 0x24c
    uint32_t mOrnamentFlags;        // 0x250
    uint8_t mOrnamentState;         // 0x254

    bool Write(void* pData);
    int SetNextDestructedState();
    void ShutdownOrnament();
    void AttachEffect(void* pEffect);
};
void* CastHitSphereBase(void* pObject);
extern const void* sOrnamentFields;
// ---- items of slice s00c3ee20 end

// ---- items of slice s00c404c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int     u32;
typedef signed   int     i32;
typedef unsigned char    u8;
typedef float            f32;
typedef double           f64;
extern "C" f32 g_13eb960;            // 0x013eb960
extern "C" f32 g_13ec5b4;            // 0x013ec5b4  (1000.0f)
extern "C" f32 g_146cb48;            // 0x0146cb48  (FLT_MAX)
extern "C" f32 g_13f9428;            // 0x013f9428
extern "C" f32 g_1485720;            // 0x01485720  (_HK_REAL_ONE)
extern "C" f64 g_1447a10;            // 0x01447a10
extern "C" u8  g_168e65c;            // 0x0168e65c
void* __cdecl   FUN_00f21760(void* obj, void* arg);                       // 0x00f21760
void* __stdcall SP_NounManager(void* arg);                                // 0x00b3d300 (ret 4)
void  __cdecl   FUN_00f47380(void* p);                                    // 0x00f47380 operator delete[]
void  __cdecl   FUN_00571d90(void* self);                                 // 0x00571d90
extern "C" f64 pow(f64 base, f64 exp);
struct RelObj;      // reference counted object: vtable slot 1 == Release
struct Key { u32 w[3]; };                                     // 0x0c bytes
struct RelObj {
    void Release() { (**(void (__thiscall**)(void*))(*(void***)this + 1))(this); }
};
struct cSpatialObject_s00c4_04c0 {
    void* mVtbl_00;                                           // +0x34
    u8    pad_04[0x50 - 0x04];
    void  Ctor_00c89630();                                    // 0x00c89630
    void  Dtor_00c8a420();                                    // 0x00c8a420
    void  Dtor_00c8b2e0();                                    // 0x00c8b2e0
    bool  Write(void* stream);                                // 0x00c88a90
    bool  Read(void* stream);                                 // 0x00c88b00
    void* Cast_00c884f0(i32 typeID);                          // 0x00c884f0
};
struct cInteractableObject_s00c4_04c0 {
    cInteractableObject_s00c4_04c0();                                    // 0x00c3f9b0
    void* mVtbl_00;                                           // +0x00
    void* mVtbl_04;                                           // +0x04
    u8    pad_08[0x2c - 0x08];
    void* mpOwner_2c;                                         // +0x2c
    u8    pad_30[4];
    cSpatialObject_s00c4_04c0 mSpatial;                                  // +0x34

    bool LoadModelChecked(void* model);                       // 0x00c3f890
    bool InitFromDefinition(void* p, i32 a, u32 b);           // 0x00c3fc80 (ret 0xc)
    void FUN_00c3f9a0(void* arg);                             // 0x00c3f9a0
    void Destroy(i32 arg);                                    // 0x00c3fa70
};
struct cCombatant {
    u8   mBytes_00[0xc8];
    void Ctor_00bfd4e0();                                     // 0x00bfd4e0
    void Dtor_00bfcd00();                                     // 0x00bfcd00
};
struct OrnModelImpl;
typedef void (__thiscall *OrnModelFn)(OrnModelImpl* self, void* model, i32 flag);
struct OrnModelImpl { void** mVtbl_00; };                     // +0x00 = vtable
struct OrnModel {
    OrnModelImpl* mpImpl_00;                                  // +0x00
    u32           mFlags_04;                                  // +0x04
    u8            pad_08[0x58 - 0x08];
    f32           mAlpha_58;                                  // +0x58
    void Notify_16c(void* owner, i32 flag) {
        OrnModelImpl* impl = mpImpl_00;
        OrnModelFn fn = (OrnModelFn)(*(void**)((u8*)impl->mVtbl_00 + 0x16c));
        fn(impl, owner, flag);
    }
};
static __forceinline f32 Clamp(f32 value, f32 lo, f32 hi)
{
    __asm {
        movss xmm0, value
        maxss xmm0, lo
        minss xmm0, hi
        movss value, xmm0
    }
    return value;
}
struct cInteractiveOrnament_s00c4_04c0 : cInteractableObject_s00c4_04c0 {
    u32   mFlags_84;                                          // +0x84
    i32   mState_88;                                          // +0x88
    u8    pad_8c[0x9c - 0x8c];
    void* mpSub_9c;                                           // +0x9c (has a u32 flag at +4)
    u8    pad_a0[0xa3 - 0xa0];
    u8    mByte_a3;                                           // +0xa3
    u8    pad_a4[1];
    u8    mByte_a5;                                           // +0xa5
    u8    pad_a6[3];
    u8    mByte_a9;                                           // +0xa9
    u8    pad_aa[0xd0 - 0xaa];
    OrnModel* mpModel_d0;                                     // +0xd0
    u8    pad_d4[0x110 - 0xd4];
    i32   mType_110;                                          // +0x110
    u8    pad_114[0x130 - 0x114];
    void* mVtbl_130;                                          // +0x130
    RelObj* mpRef_134;                                        // +0x134
    RelObj* mpRef_138;                                        // +0x138
    RelObj* mpRef_13c;                                        // +0x13c
    RelObj* mpRef_140;                                        // +0x140
    u8    mByte_144;                                          // +0x144
    u8    pad_145[3];
    RelObj* mpRef_148;                                        // +0x148
    RelObj* mpRef_14c;                                        // +0x14c
    RelObj* mpRef_150;                                        // +0x150
    u8    pad_154[0xc];
    u8    mByte_160;                                          // +0x160
    u8    pad_161[3];
    f32   mField_164;                                         // +0x164
    RelObj* mpRef_168;                                        // +0x168
    u8    pad_16c[4];
    cCombatant mCombatant_170;                                // +0x170
    u32   mFlags_238;                                         // +0x238
    u8    mByte_23c;                                          // +0x23c
    u8    pad_23d[3];
    i32   mLifetime_240;                                      // +0x240
    i32   mTimer_244;                                         // +0x244
    i32   mField_248;                                         // +0x248
    Key*  mKeys_24c;                                          // +0x24c
    Key*  mKeysEnd_250;                                       // +0x250
    Key*  mKeysCap_254;                                       // +0x254

    cInteractiveOrnament_s00c4_04c0();                                   // 0x00c404c0
    void  Dtor_00c40720(i32 arg);
    bool  LoadModel_00c407d0(void* model);
    void  Attach_00c40800(void* effect);
    void  SetLifetime_00c40830(f32 seconds, u8 keepModel);
    void  Update_00c408f0(i32 dt);
    u32   InitFromDefinition_00c40ab0(void* def, i32 a, u32 b);
    void* Cast_00c40cd0(i32 typeID);
    void  AttachEffect(void* effect);                         // 0x00c3ff10
};
// ---- items of slice s00c404c0 end

// ---- items of slice s00c68280 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 { float x, y, z; };
struct Vec {
    int** begin;
    int** end;
    int** cap;
    void erase(int** a, int** b);                 // 0x00e25bd0
    void F_00b05b40(int** pos, int** val);        // 0x00b05b40
    void DoInsertPtr(int** pos, int** val);       // 0x00aea5d0
};
struct Vector3Vec {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    void erase(Vector3* a, Vector3* b);           // 0x0050f740
    void DoInsertValue(Vector3* pos, Vector3* val); // 0x004b5ad0
    void push_back(Vector3* v) {
        Vector3* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e != 0) { e->x = v->x; e->y = v->y; e->z = v->z; }
        } else {
            DoInsertValue(e, v);
        }
    }
};
struct cSpatial {
    void** vt;
    float* GetPosition() {
        typedef float* (__thiscall* Fn)(cSpatial*);
        return ((Fn)vt[0x2c / 4])(this);
    }
    float* GetPositionI(int i) {
        typedef float* (__thiscall* Fn)(cSpatial*, int);
        return ((Fn)vt[0x2c / 4])(this, i);
    }
    void SetPosition(void* p) {
        ((void(__thiscall*)(cSpatial*, void*))vt[0x38 / 4])(this, p);
    }
    void F_00c421b0(void* p);                     // 0x00c421b0
    void Shutdown();                              // 0x00c43f90
};
struct cGameData_s00c6_8280 {
    void* mVt0;                                   // +0x00
    void* mVt4;                                   // +0x04
    char  pad08[0x34 - 0x08];
    cGameData_s00c6_8280();                                  // 0x00b18660
    ~cGameData_s00c6_8280();                                 // 0x00b184c0
};
struct cLocoBase {
    void* mVt;                                    // +0x00 (= obj +0x34)
    char  pad04[0xd4 - 0x04];
    void* mVtD4;                                  // +0xd4 (= obj +0x108)
    char  padD8[0x4d4 - 0xd8];
    cLocoBase();                                  // 0x00c43860
    ~cLocoBase();                                 // 0x00c432e0
};
struct cCombatant_s00c6_8280 {
    void* mVt;
    char  pad04[0xc8 - 0x04];
    cCombatant_s00c6_8280();                                 // 0x00bfd4e0
    ~cCombatant_s00c6_8280();                                // 0x00bfcd00
};
struct cSub5d0 {
    void* mVt;                                    // +0x00 (= obj +0x5d0)
    cSub5d0();                                    // 0x00abfe50
    ~cSub5d0();                                   // 0x00abfec0
};
struct cMovableDestructibleOrnament : cGameData_s00c6_8280 {
    cLocoBase  mLoco;                             // +0x34
    cCombatant_s00c6_8280 mCombatant;                        // +0x508
    cSub5d0    mSub;                              // +0x5d0
    cMovableDestructibleOrnament();               // 0x00c68e30
    ~cMovableDestructibleOrnament();              // 0x00c68ed0
};
struct COrnCombatantSlot { void* mVt; void F_00bfc720(); };  // 0x00bfc720
struct COrnTailSlot      { void* mVt; void F_00abf710(); };  // 0x00abf710
struct COrn {
    char   mByte0;                     // +0x00
    char   pad001[3];
    Vec    mVec4;                      // +0x04  noun-ref vector
    char   pad010[0x2c - 0x10];
    int*   mp2c;                       // +0x2c (interface, released in Shutdown)
    char   pad030[0x34 - 0x30];
    cSpatial mSpatial;                 // +0x34
    char   pad038[0xd0 - 0x38];
    int*   mpModel;                    // +0xd0
    char   pad0d4[0x118 - 0xd4];
    float  mPosX, mPosY, mPosZ;        // +0x118,+0x11c,+0x120
    char   mFlag124;                   // +0x124
    char   pad125[3];
    int    mKey128;                    // +0x128
    float  mF12c;                      // +0x12c
    int    mCount130;                  // +0x130 (segment count)
    int*   mVec134;                    // +0x134 (view / effect object)
    char   pad138[0x508 - 0x138];
    COrnCombatantSlot mCombatant;      // +0x508
    char   pad50c[0x5d0 - 0x50c];
    COrnTailSlot mTail;                // +0x5d0

    __declspec(noinline) void Update();  // 0xc68280
    void H3f90();                      // 0xc63f90
    void H4460(int x);                 // 0xc64460
    void E850(int* noun);              // 0xc68850
    void E930();                       // 0xc68930
    void E980(void* view);             // 0xc68980
    void Eaa0();                       // 0xc68aa0
    void Eae0(float* p);               // 0xc68ae0
    void Eb40(int key);                // 0xc68b40
    void Ebd0(float v);                // 0xc68bd0
    char Ed20(int* noun);              // 0xc68d20
    void Ed70(Vector3* pos, Vector3Vec* v); // 0xc68d70
    void F030();                       // 0xc69030
    void F090();                       // 0xc69090
    int  Ef30(int id);                 // 0xc68f30
    int  F1e0(int id);                 // 0xc691e0
    cSpatial* Spatial() { return (cSpatial*)((char*)this + 0x34); }
};
struct IQuery {
    int QI(int id);   // 0xb18460
    int QJ(int id);   // 0xc884f0
    int QK(int id);   // 0xc41d00
    int QL(int id);   // 0xbfc380
    int QM(int id);   // 0xabf740
};
// ---- items of slice s00c68280 end

// ---- items of slice s00c8c9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_new(uint32_t nSize, const char* pTag, int nA, int nB, const char* pFile, int nLine); // 0x00f473a0
extern "C" void  __cdecl operator_delete_array(void* pBlock);                                                          // 0x00f47380
extern char g_szSimulator[];        // 0x013f09b4 "Simulator"
extern char g_szEastlFile[];        // 0x013ebb38 ".../EASTL/allocator.h"
extern char g_varListBase[];        // 0x0157a9e0
extern "C" float __cdecl sqrtf(float fValue);   // x87 fsqrt
class cOutStream;
struct tAnalysisInfo {
    uint32_t mnKey;                 // +0x00
    uint32_t mnValue;               // +0x04
    uint32_t mnFlags;               // +0x08
};
class tAnalysisVector {             // eastl vector of 12-byte elements
public:
    tAnalysisInfo* mpBegin;         // +0x00
    tAnalysisInfo* mpEnd;           // +0x04
    tAnalysisInfo* mpCapacity;      // +0x08

    void Insert(tAnalysisInfo* pPosition, uint32_t nCount, const tAnalysisInfo& value); // 0x00c8d940
};
struct tRefPtr {                    // 4-byte element of the model vectors
    void* mpObject;                 // +0x00
};
class tMWModelVector {              // eastl vector of AutoRefCount<cMWModel> (0x14 bytes on the record)
public:
    tRefPtr* mpBegin;               // +0x00
    tRefPtr* mpEnd;                 // +0x04
    tRefPtr* mpCapacity;            // +0x08
    uint8_t  mPad0c[0x08];          // +0x0c

    tMWModelVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoDestroyValues(tRefPtr* pBegin, tRefPtr* pEnd);   // 0x005f3680
};
struct tGameDataBase {              // first base subobject (vtable at +0x00)
    virtual ~tGameDataBase() {}
};
struct tGameDataRefBase {           // second base subobject (vtable at +0x04, count at +0x08)
    virtual ~tGameDataRefBase() {}
    virtual void AddRef();          // 0x04
    int32_t mnRefCount;             // +0x04 (absolute +0x08)
};
class cGameData_s00c8_c9d0 : public tGameDataBase, public tGameDataRefBase {
public:
    cGameData_s00c8_c9d0();                    // 0x00b18660
    virtual ~cGameData_s00c8_c9d0();           // 0x00b184c0
    bool Write(cOutStream* pStream); // 0x00b18590
    uint8_t mPad0c[0x28];           // +0x00c
};
class cSpatialObject_s00c8_c9d0 {
public:
    cSpatialObject_s00c8_c9d0();                                   // 0x00c89630
    virtual ~cSpatialObject_s00c8_c9d0();                          // 0x00c8a420
    bool Write(cOutStream* pStream);                    // 0x00c88a90
    void SetLocalExtents(float fMin, float fMax);       // 0x00c89160
    uint8_t  mPad04[0x50];                              // +0x004
    int32_t  mn54;                                      // +0x054
    uint8_t  mPad58[0x38];                              // +0x058
    uint32_t mn90;                                      // +0x090
    uint32_t mn94;                                      // +0x094
    uint32_t mn98;                                      // +0x098
    uint8_t  mPad9c[0x38];                              // +0x09c
};
class tIStream {
public:
    virtual void v00();                                     // +0x00
};
class tStreamInner {
public:
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual tIStream* v18();                                // +0x18
};
class cOutStream {
public:
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual void v18();                                     // +0x18
    virtual void v1c();                                     // +0x1c
    virtual tStreamInner* v20();                            // +0x20
};
class cVarListSerializer_s00c8_c9d0 {
public:
    uint32_t mPad00[0x05];                                  // +0x00
    void Construct(void* pOwner, void* pVarList, int32_t nLine); // 0x00692f90
    bool Serialize(cOutStream* pStream);                    // 0x00692900
};
struct tVarListFrame {
    uint32_t            mnValue;            // +0x000
    cVarListSerializer_s00c8_c9d0  mSerializer;        // +0x004
    uint32_t            mPad18[0x280];      // +0x018
};
bool __cdecl EA_IO_WriteUint32(tIStream* pStream, const uint32_t* pValue, int32_t nCount, int32_t nFlags); // 0x0093aa70
class cTotemPole : public cGameData_s00c8_c9d0, public cSpatialObject_s00c8_c9d0 {
public:
    cTotemPole();                               // 0x00c8d6c0
    virtual ~cTotemPole();                      // 0x00c8d800
    bool Write(cOutStream* pStream);            // 0x00c8d330

    tMWModelVector mModels;                     // +0x108
    tMWModelVector mSegments;                   // +0x11c
    tMWModelVector mParts;                      // +0x130
    int32_t        mn144;                       // +0x144
    bool           mb148;                       // +0x148
};
class cSpatialNode {
public:
    uint8_t  mPad00[0x04];          // +0x000
    uint32_t mnFlags;               // +0x004
    uint8_t  mPad08[0x70];          // +0x008
    float    mf78;                  // +0x078
    uint8_t  mPad7c[0x08];          // +0x07c
    float    mf84;                  // +0x084
};
class cSimObject {
public:
    uint8_t      mPad00[0x38];      // +0x000
    float        mf38;              // +0x038
    float        mf3c;              // +0x03c
    float        mf40;              // +0x040
    float        mf44;              // +0x044
    float        mf48;              // +0x048
    float        mf4c;              // +0x04c
    uint8_t      mPad50[0x0c];      // +0x050
    float        mf5c;              // +0x05c
    uint8_t      mPad60[0x74];      // +0x060
    cSpatialNode** mpChildBegin;    // +0x0d4
    cSpatialNode** mpChildEnd;      // +0x0d8

    void SetLocalExtents(float fMin, float fMax);   // 0x00c89160
    void FUN_00c8d460(float fA, float fB);          // 0x00c8d460
};
void* __cdecl FUN_00951740(void** ppOut, tAnalysisInfo* pBegin, tAnalysisInfo* pEnd, tAnalysisInfo* pDst, tAnalysisInfo* pPos); // 0x00951740
void* __cdecl FUN_00abced0(tAnalysisInfo* pDstEnd, tAnalysisInfo* pBegin, tAnalysisInfo* pEnd);   // 0x00abced0
void  __cdecl FUN_00a177f0(tAnalysisInfo* pBegin, tAnalysisInfo* pEnd, const tAnalysisInfo* pValue); // 0x00a177f0
void* __cdecl FUN_006a4100(tAnalysisInfo* pDst, int32_t nCount, const tAnalysisInfo* pValue);     // 0x006a4100
void* __cdecl FUN_007ec550(void* pDst, const void* pSrc, uint32_t nBytes);                        // 0x007ec550
template <typename T>
inline const T& tMax(const T& a, const T& b)
{
    return a < b ? b : a;
}
// ---- items of slice s00c8c9d0 end

// ---- items of slice s00c8db30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOneHalf;      // 0x01471064
struct Vec3_s00c8_db30 { float x, y, z; };
namespace EA {
namespace IO {
bool ReadInt32(void* pStream, void* pData, unsigned int uCount, int nFlags);
}
}
struct IOObject {
virtual void  v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void  v04();
virtual void v05();
    virtual void* v06();                 // +0x18 -> EA::IO stream
    virtual void  v07();                 // +0x1c -> finish hook
    virtual IOObject* v08();             // +0x20 -> reader/writer
};
struct Vec0C {
    uint8_t* mBegin;                     // +0x00
    uint8_t* mEnd;                       // +0x04
    uint8_t* mCap;                       // +0x08
    uint8_t* erase(uint8_t* pFirst, uint8_t* pLast);     // 0x009e0480
    void  DoResize(unsigned int n);                      // 0x00c8d890
    void  GrowTo(uint8_t* pEnd, int n, const Vec3_s00c8_db30& rValue); // 0x00c8d940
    void  DoInsertValue(uint8_t* pWhere, const Vec3_s00c8_db30& rValue); // 0x004b5ad0
    void  resize(unsigned int n, const Vec3_s00c8_db30& rValue);    // 0x00c8de50
};
struct U32Vec {
    uint32_t* mBegin;                    // +0x00
    uint32_t* mEnd;                      // +0x04
    uint32_t* mCap;                      // +0x08
    uint32_t* DoInsertValue(uint32_t* pWhere, uint32_t value);  // 0x004558a0
};
struct MWModel {
    void**       vt;                     // +0x00
    uint32_t     mFlags;                 // +0x04
    uint16_t     pad08;
    uint8_t      mb06;                   // +0x06
    uint8_t      pad07;
    uint32_t     mRefCount;              // +0x40
    uint32_t     pad44[2];               // +0x44..+0x4b
    Vec3_s00c8_db30         mColor;                 // +0x4c
    float        mAlpha;                 // +0x58
    uint32_t     mID;                    // +0x5c
    void*        mAttachment;            // +0x60
    void*        mpOwner;                // +0x64
    uint32_t     pad68;
    Vec3_s00c8_db30         mBBoxMax;               // +0x6c (.y @ +0x78)
    Vec3_s00c8_db30         mBBoxMin;               // +0x74
    float        mCameraLOD;             // +0x84
};
struct SpatialPrefix {
    void**   vt;                         // +0x00
    Vec3_s00c8_db30     mPosition;                  // +0x04
    uint32_t pad10[0x28 / 4];            // +0x10
    Vec3_s00c8_db30     mExtentsMin;                // +0x38
    Vec3_s00c8_db30     mExtentsMax;                // +0x44
    uint32_t pad50[3];                   // +0x50
    float    mBoundingRadius;            // +0x5c
    uint32_t pad60[5];                   // +0x60
    uint8_t  mbFlag_74;                  // +0x74
    uint8_t  pad75[0xa0 - 0x75];         // +0x75..+0x9f
    void     Teardown() const;           // 0x00c8b2e0 (thiscall, ret 0)
};
struct ModelList {
    MWModel** mBegin;                    // +0x00/+0x108
    MWModel** mEnd;                      // +0x04/+0x10c
    MWModel** mCap;                      // +0x08/+0x110
    void DestroyValues(MWModel** pFirst, MWModel** pLast); // 0x005f3680 (thiscall, ret 8)
};
struct SpatialBody {
    uint8_t      pad000[0xd4];           // +0x000..+0xd3
    ModelList    mModels;                // +0xd4
    void         Release() const;        // 0x00c898f0 (thiscall, tail-called)
};
struct TotemPole {
    uint32_t     pad00[0xd];             // +0x00..+0x33 (cGameData base)
    SpatialPrefix mSpatial;              // +0x34 (size 0xa0, ends at +0xd4)
    void*        mpModelFactory_d4;      // +0xd4 (slot 0x0c creates models)
    uint32_t     padD8[0xc];             // +0xd8..+0x107
    ModelList    mModels;                // +0x108 (begin/end/cap)
    uint32_t     pad114[2];              // +0x114..+0x11b
    uint32_t*    mSegmentsBegin;         // +0x11c
    uint32_t*    mSegmentsEnd;           // +0x120
    uint32_t*    mSegmentsCap;           // +0x124
    uint32_t     pad128[2];              // +0x128..+0x12f
    Vec3_s00c8_db30*        mColorsBegin;           // +0x130
    Vec3_s00c8_db30*        mColorsEnd;             // +0x134
    Vec3_s00c8_db30*        mColorsCap;             // +0x138
    bool         PostDataLoadBase(unsigned int nID) const; // 0x00b183f0 (thiscall)
    bool         PostDataLoad(unsigned int nID);          // 0x00c8df10 (thiscall)
};
struct IRawIface {
virtual void  v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void  v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void  v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void  v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void  v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void  v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void  v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void  v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void  v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void  v36();
virtual void v37();
virtual void v38();
virtual void v39();
};
void*   Sub_478db0(void* pSlot, void* pModel);      // 0x00478db0
void*   CopyRefs(void* pFirst, void* pLast, void* pOut); // 0x005f4e10 (eastl copy_impl::do_copy)
extern const Vec3_s00c8_db30  kSPColorRed;   // 0x0157a9d0
// ---- items of slice s00c8db30 end

// @ 0x00c40150
void* cInteractiveOrnamentCast(void* pObject, void* pType)
{
    if (pType == (void*)0x13f94d4) {
        if (pObject != nullptr)
            return (uint8_t*)pObject + 0x5c;
        return nullptr;
    }
    if (pType == (void*)0x3a25119)
        return pObject;
    if (pType != (void*)0x8367427)
        return CastHitSphereBase(pObject);
    if (pObject != nullptr)
        return (uint8_t*)pObject + 0x4c;
    return nullptr;
}

// @ 0x00c40200
int cInteractiveOrnament::SetNextDestructedState()
{
    int nNext = mDestructedState + 1;
    if (nNext < (mDestructedCount - mDestructedStep) / 0xc) {
        mDestructedState = nNext;
        void (*pCallback)(void*) = *(void (**)(void*))((uint8_t*)GetPosition() + 0x94);
        pCallback((uint8_t*)(uintptr_t)mDestructedStep + nNext * 0xc);
        mOrnamentState = 0;
        return 1;
    }
    return 0;
}

// @ 0x00c40270
bool cInteractiveOrnament::Write(void* pData)
{
    IOStream* pStream = ((ISerializer*)pData)->GetStream();
    uint32_t nType = 0x3a25119;
    WriteUint32(pStream->GetStream(), &nType, 1, 0);

    bool bOk = cInteractableObject::Write(pData);

    cVarListSerializer serializer(this, sOrnamentFields, 0x1a80d26);
    if (bOk)
        return serializer.Serialize(pData);
    return false;
}

// @ 0x00c404c0
cInteractiveOrnament_s00c4_04c0::cInteractiveOrnament_s00c4_04c0()
{
    mVtbl_130 = (void*)0x146c56c;
    mpRef_134 = 0;
    mpRef_138 = 0;
    mpRef_13c = 0;
    mpRef_140 = 0;
    mByte_144 = 0;
    mpRef_148 = 0;
    mpRef_14c = 0;
    mpRef_150 = 0;
    mByte_160 = 0;
    mField_164 = 0.0f;
    mpRef_168 = 0;
    mCombatant_170.Ctor_00bfd4e0();
    mVtbl_00 = (void*)0x146cca0;
    mVtbl_04 = (void*)0x146cc8c;
    mSpatial.mVtbl_00 = (void*)0x146cbc8;
    mVtbl_130 = (void*)0x146cbb8;
    *(void**)mCombatant_170.mBytes_00 = (void*)0x146cb50;
    mFlags_238 = 0;
    mTimer_244 = 0;
    mByte_23c = 1;
    mLifetime_240 = -1;
    mField_248 = -1;
    mKeys_24c = 0;
    mKeysEnd_250 = 0;
    mKeysCap_254 = 0;
    mFlags_84 |= 0x200;
    mByte_a5 = 0;
}

// @ 0x00c40720
void cInteractiveOrnament_s00c4_04c0::Dtor_00c40720(i32 arg)
{
    cCombatant* pCombat = &mCombatant_170;
    mVtbl_00 = (void*)0x146cca0;
    mVtbl_04 = (void*)0x146cc8c;
    mSpatial.mVtbl_00 = (void*)0x146cbc8;
    mVtbl_130 = (void*)0x146cbb8;
    *(void**)pCombat->mBytes_00 = (void*)0x146cb50;
    if (mKeys_24c != 0 && ((u32*)mKeys_24c)[-1] != 0)
        FUN_00f47380(mKeys_24c);
    pCombat->Dtor_00bfcd00();
    mVtbl_130 = (void*)0x146c56c;
    if (mpRef_168 != 0)
        mpRef_168->Release();
    if (mpRef_150 != 0)
        mpRef_150->Release();
    if (mpRef_14c != 0)
        mpRef_14c->Release();
    if (mpRef_148 != 0)
        mpRef_148->Release();
    cInteractableObject_s00c4_04c0::Destroy(arg);
}

// @ 0x00c407d0
bool cInteractiveOrnament_s00c4_04c0::LoadModel_00c407d0(void* model)
{
    if (LoadModelChecked(model)) {
        u32* pFlags = (u32*)((u8*)mpSub_9c + 4);
        *pFlags &= 0xfffffffd;
        return true;
    }
    return false;
}

// @ 0x00c40800
void cInteractiveOrnament_s00c4_04c0::Attach_00c40800(void* effect)
{
    FUN_00f21760(this, effect);
    mFlags_238 |= 1;
    AttachEffect(effect);
}

// @ 0x00c40830
void cInteractiveOrnament_s00c4_04c0::SetLifetime_00c40830(f32 seconds, u8 keepModel)
{
    f32 t = Clamp(seconds, 0.0f, g_146cb48);
    mLifetime_240 = (i32)(t * g_13ec5b4);
    if (mLifetime_240 <= 0) {
        mFlags_238 &= 0xfffffffd;
    } else {
        mFlags_238 |= 2;
    }
    if (keepModel == 0) {
        mFlags_238 |= 4;
        OrnModel* model = mpModel_d0;
        if (model != 0)
            model->Notify_16c(model, 1);
    } else {
        mFlags_238 &= 0xfffffffb;
    }
    OrnModel* model2 = mpModel_d0;
    if (model2 != 0)
        model2->mAlpha_58 = g_1485720;
}

// @ 0x00c408f0
void cInteractiveOrnament_s00c4_04c0::Update_00c408f0(i32 dt)
{
    if (mByte_a9 == 0) {
        OrnModel* model = mpModel_d0;
        if (model == 0)
            return;
        if (((model->mFlags_04 >> 15) & 1) == 0)
            return;
        model->Notify_16c(model, 0);
        return;
    }
    if (mFlags_238 & 1)
        return;
    if ((mFlags_238 & 2) == 0)
        return;
    i32 life = mLifetime_240;
    if (life > 0) {
        life -= dt;
        mLifetime_240 = life;
        if (life <= 0) {
            mLifetime_240 = 0;
            mTimer_244 = 0xbb8;
        }
    }
    if (mTimer_244 <= 0)
        return;
    OrnModel* model = mpModel_d0;
    if (model != 0) {
        mTimer_244 -= dt;
        if (mTimer_244 > 0) {
            f32 secs = (f32)dt * g_13f9428;
            f64 f = pow(g_1447a10, (f64)secs);
            model->mAlpha_58 = (f32)(f * (f64)model->mAlpha_58)
                             + (f32)((1.0 - f) * (f64)g_13eb960);
            mpModel_d0->mFlags_04 |= 2;
            return;
        }
        if (mFlags_238 & 4)
            model->mAlpha_58 = 0.0f;
    }
    if (mFlags_238 & 4) {
        (**(void (__thiscall**)(void*, i32))(*(void***)this + 0xd))(this, 0);
        (**(void (__thiscall**)(void*, void*))(*(void***)&mSpatial + 0xe))(&mSpatial, &g_168e65c);
        mByte_a9 = 0;
        OrnModel* m = mpModel_d0;
        if (m != 0)
            FUN_00571d90(m);
    } else {
        void* nm = SP_NounManager(this);
        (**(void (__thiscall**)(void*, void*))(*(void***)nm + 0xd))(nm, this);
        mTimer_244 = 0;
    }
}

// @ 0x00c68e30
cMovableDestructibleOrnament::cMovableDestructibleOrnament()
{
    mLoco.mVt = (void*)0x1471598;
    mVt0 = (void*)0x1471540;
    mVt4 = (void*)0x1471530;
    mLoco.mVtD4 = (void*)0x1471528;
    mSub.mVt = (void*)0x14714c0;
    mCombatant.mVt = (void*)0x1471458;
}

// @ 0x00c68f30
int COrn::Ef30(int id)
{
    if (id == 0x283d961)
        return (int)this;
    int r = ((IQuery*)&mSpatial)->QK(id);
    if (r == 0) {
        r = ((IQuery*)((char*)this + 0x508))->QL(id);
        if (r == 0) {
            r = ((IQuery*)this)->QI(id);
            if (r == 0)
                r = ((IQuery*)((char*)this + 0x5d0))->QM(id);
        }
    }
    return r;
}

// @ 0x00c8d330
bool cTotemPole::Write(cOutStream* pStream)
{
    tVarListFrame frame;
    frame.mnValue = 0x055cf8e3;
    tIStream* pSink = pStream->v20()->v18();
    EA_IO_WriteUint32(pSink, &frame.mnValue, 1, 0);
    bool bOk = cGameData_s00c8_c9d0::Write(pStream) && cSpatialObject_s00c8_c9d0::Write(pStream);
    frame.mSerializer.Construct(this, g_varListBase, 0x1a80d26);
    if (bOk)
    {
        if (frame.mSerializer.Serialize(pStream))
            return true;
    }
    return false;
}

// @ 0x00c8d460
void cSimObject::FUN_00c8d460(float fA, float fB)
{
    SetLocalExtents(fA, fB);

    int32_t nCount = (int32_t)(mpChildEnd - mpChildBegin);
    for (int32_t i = 0; i < nCount; ++i)
    {
        cSpatialNode* pNode = mpChildBegin[i];
        if (pNode != 0)
        {
            uint32_t nFlags = pNode->mnFlags;
            if (((nFlags >> 14) & 1) != 0 || ((nFlags >> 16) & 1) != 0)
                mf4c = pNode->mf84 - pNode->mf78 + mf4c;
        }
    }

    float fMidX = (mf38 + mf44) * 0.5f;
    float fMidY = (mf48 + mf3c) * 0.5f;
    float fMidZ = (mf4c + mf40) * 0.5f;
    float fAx = mf44 - fMidX;
    float fAy = mf48 - fMidY;
    float fAz = mf4c - fMidZ;
    float fBx = mf38 - fMidX;
    float fBy = mf3c - fMidY;
    float fBz = mf40 - fMidZ;
    mf5c = tMax(sqrtf(fAx * fAx + fAy * fAy + fAz * fAz), sqrtf(fBx * fBx + fBy * fBy + fBz * fBz));
}

// @ 0x00c8d6c0
cTotemPole::cTotemPole()
: mModels(), mSegments(), mParts(), mn144(5), mb148(true)
{
    mn54 = 2;
    mn90 = 0x093256ba;
    mn98 = 0xf37c24e6;
}

// @ 0x00c8d800
cTotemPole::~cTotemPole()
{
    tRefPtr* pParts = mParts.mpBegin;
    if (pParts != 0 && ((int32_t*)pParts)[-1] != 0)
        operator_delete_array(pParts);
    tRefPtr* pSegments = mSegments.mpBegin;
    if (pSegments != 0 && ((int32_t*)pSegments)[-1] != 0)
        operator_delete_array(pSegments);
    mModels.DoDestroyValues(mModels.mpBegin, mModels.mpEnd);
    tRefPtr* pModels = mModels.mpBegin;
    if (pModels != 0 && ((int32_t*)pModels)[-1] != 0)
        operator_delete_array(pModels);
}

// @ 0x00c8d940
void tAnalysisVector::Insert(tAnalysisInfo* pPosition, uint32_t nCount, const tAnalysisInfo& value)
{
    if ((uint32_t)(mpCapacity - mpEnd) < nCount)
    {
        uint32_t nOld = (uint32_t)((uint8_t*)mpEnd - (uint8_t*)mpBegin) / sizeof(tAnalysisInfo);
        uint32_t nCapacity = nOld * 2;
        if (nOld == 0)
            nCapacity = 1;
        uint32_t nNeeded = nOld + nCount;
        if (nCapacity < nNeeded)
            nCapacity = nNeeded;
        tAnalysisInfo* pNew = 0;
        if (nCapacity != 0)
            pNew = (tAnalysisInfo*)operator_new(nCapacity * sizeof(tAnalysisInfo), g_szSimulator, 0, 0, g_szEastlFile, 0xd1);
        void* pMid = FUN_007ec550(mpBegin, pPosition, (uint32_t)pNew);
        FUN_006a4100((tAnalysisInfo*)pMid, (int32_t)nCount, &value);
        uint32_t nBytes = nCount * sizeof(tAnalysisInfo);
        void* pEnd = FUN_007ec550(pPosition, mpEnd, (uint32_t)((uint8_t*)pMid + nBytes));
        if (mpBegin != 0 && ((int32_t*)mpBegin)[-1] != 0)
            operator_delete_array(mpBegin);
        mpBegin = pNew;
        mpEnd = (tAnalysisInfo*)pEnd;
        mpCapacity = (tAnalysisInfo*)((uint8_t*)pNew + nCapacity * sizeof(tAnalysisInfo));
        return;
    }
    if (nCount == 0)
        return;

    tAnalysisInfo copy = value;
    uint32_t nElements = (uint32_t)(mpEnd - pPosition);
    if (nCount < nElements)
    {
        uint32_t nBytes = nCount * sizeof(tAnalysisInfo);
        tAnalysisInfo* pMoveFrom = (tAnalysisInfo*)((uint8_t*)mpEnd - nBytes);
        void* pOut = 0;
        FUN_00951740(&pOut, pMoveFrom, mpEnd, mpEnd, pPosition);
        mpEnd = (tAnalysisInfo*)((uint8_t*)mpEnd + nBytes);
        tAnalysisInfo* pNew = (tAnalysisInfo*)pOut;
        FUN_00abced0(pNew, (tAnalysisInfo*)((uint8_t*)mpEnd - nBytes), mpEnd);
        FUN_00a177f0(pNew, (tAnalysisInfo*)((uint8_t*)pNew + nBytes), &copy);
    }
    else
    {
        uint32_t nExtra = nCount - nElements;
        FUN_006a4100(mpEnd, (int32_t)nExtra, &copy);
        tAnalysisInfo* pOldEnd = mpEnd;
        mpEnd = (tAnalysisInfo*)((uint8_t*)mpEnd + nExtra * sizeof(tAnalysisInfo));
        void* pOut = 0;
        FUN_00951740(&pOut, pPosition, pOldEnd, mpEnd, pPosition);
        mpEnd = (tAnalysisInfo*)((uint8_t*)mpEnd + nElements * sizeof(tAnalysisInfo));
        FUN_00a177f0(pPosition, pOldEnd, &copy);
    }
}

// @ 0x00c8db30
void __cdecl F8db30(IOObject* pStream, Vec0C* pVec)
{
    pVec->erase(pVec->mBegin, pVec->mEnd);
    unsigned int nCount = 0;
    EA::IO::ReadInt32(pStream->v08()->v06(), &nCount, 1, 0);
    pVec->DoResize(nCount);
    for (unsigned int i = 0; i < nCount; ++i) {
        Vec3_s00c8_db30 tmp;
        EA::IO::ReadInt32(pStream->v08()->v06(), &tmp, 3, 0);
        if (pVec->mEnd < pVec->mCap) {
            Vec3_s00c8_db30* pSlot = (Vec3_s00c8_db30*)pVec->mEnd;
            pVec->mEnd = (uint8_t*)(pSlot + 1);
            if (pSlot != 0) {
                pSlot->x = tmp.x;
                pSlot->y = tmp.y;
                pSlot->z = tmp.z;
            }
        } else {
            pVec->DoInsertValue(pVec->mEnd, tmp);
        }
    }
    return pStream->v07();
}

// @ 0x00c8dc10
void __fastcall TP_AddSegment(TotemPole* pSelf, int, unsigned int nMode, const Vec3_s00c8_db30& rColor)
{
    if (pSelf->mpModelFactory_d4 != 0) {
        unsigned int nKey;
        if (nMode == 0) {
            nKey = 0xa1001c58;
        } else if (nMode == 1) {
            nKey = 0xbcb8a199;
        } else {
            goto append;
        }
        {
            IRawIface* pFactory = (IRawIface*)pSelf->mpModelFactory_d4;
            MWModel* pModel = (MWModel*)((void*(__thiscall*)(void*, unsigned int, unsigned int, int))
                                         (*(void***)pFactory)[0x0c / 4])(pFactory, nKey, 0xf37c24e6, 2);
            if (pModel != 0) {
                unsigned int nSeg = (unsigned int)(pSelf->mSegmentsEnd - pSelf->mSegmentsBegin);
                Sub_478db0(&pSelf->mModels.mBegin[nSeg], pModel);
                {
                    MWModel* pOld = (MWModel*)pModel->mpOwner;
                    if (pOld != (MWModel*)pSelf) {
                        (*(void(__thiscall**)(void*))*(void***)pSelf)(pSelf);
                        pModel->mpOwner = pSelf;
                        if (pOld != 0) {
                            ((void(__thiscall*)(void*))(*(void***)pOld)[1])(pOld);
                        }
                    }
                }
                pModel->mAttachment = (void*)((void*(__thiscall*)(void*))(*(void***)pSelf)[0x20 / 4])(pSelf);
                pModel->mFlags |= 4;
                pModel->mColor.x = rColor.x;
                pModel->mColor.y = rColor.y;
                pModel->mColor.z = rColor.z;
                if ((pModel->mb06 & 1) != 0) {
                    pSelf->mSpatial.mExtentsMax.z =
                        (pModel->mCameraLOD - pModel->mBBoxMax.y) + pSelf->mSpatial.mExtentsMax.z;
                    {
                        float fMidX = (pSelf->mSpatial.mExtentsMin.x + pSelf->mSpatial.mExtentsMax.x) * kOneHalf;
                        float fMidY = (pSelf->mSpatial.mExtentsMin.y + pSelf->mSpatial.mExtentsMax.y) * kOneHalf;
                        float fMidZ = (pSelf->mSpatial.mExtentsMin.z + pSelf->mSpatial.mExtentsMax.z) * kOneHalf;
                        float fA = ((pSelf->mSpatial.mExtentsMax.y - fMidY) * (pSelf->mSpatial.mExtentsMax.y - fMidY))
                                 + ((pSelf->mSpatial.mExtentsMax.z - fMidZ) * (pSelf->mSpatial.mExtentsMax.z - fMidZ))
                                 + ((pSelf->mSpatial.mExtentsMax.x - fMidX) * (pSelf->mSpatial.mExtentsMax.x - fMidX));
                        float fB = ((pSelf->mSpatial.mExtentsMin.y - fMidY) * (pSelf->mSpatial.mExtentsMin.y - fMidY))
                                 + ((pSelf->mSpatial.mExtentsMin.z - fMidZ) * (pSelf->mSpatial.mExtentsMin.z - fMidZ))
                                 + ((pSelf->mSpatial.mExtentsMin.x - fMidX) * (pSelf->mSpatial.mExtentsMin.x - fMidX));
                        float fR = (float)sqrt((double)fA);
                        float fL = (float)sqrt((double)fB);
                        pSelf->mSpatial.mBoundingRadius = (fL <= fR) ? fR : fL;
                    }
                }
                pSelf->mSpatial.mbFlag_74 = 1;
            }
        }
    }
append:
    {
        uint32_t* pEnd = pSelf->mSegmentsEnd;
        if (pEnd < pSelf->mSegmentsCap) {
            pSelf->mSegmentsEnd = pEnd + 1;
            if (pEnd != 0) {
                *pEnd = nMode;
            }
        } else {
            U32Vec* pSegVec = (U32Vec*)&pSelf->mSegmentsBegin;
            pSegVec->mBegin = pSelf->mSegmentsBegin;
            pSegVec->mEnd = pSelf->mSegmentsEnd;
            pSegVec->mCap = pSelf->mSegmentsCap;
            pSegVec->DoInsertValue(pEnd, nMode);
        }
    }
    {
        Vec3_s00c8_db30* pEnd = pSelf->mColorsEnd;
        if (pEnd < pSelf->mColorsCap) {
            pSelf->mColorsEnd = pEnd + 1;
            if (pEnd != 0) {
                pEnd->x = rColor.x;
                pEnd->y = rColor.y;
                pEnd->z = rColor.z;
            }
        } else {
            Vec0C* pColVec = (Vec0C*)&pSelf->mColorsBegin;
            pColVec->mBegin = (uint8_t*)pSelf->mColorsBegin;
            pColVec->mEnd = (uint8_t*)pSelf->mColorsEnd;
            pColVec->mCap = (uint8_t*)pSelf->mColorsCap;
            pColVec->DoInsertValue((uint8_t*)pEnd, rColor);
        }
    }
}

// @ 0x00c8de50
__declspec(noinline) void Vec0C::resize(unsigned int n, const Vec3_s00c8_db30& rValue)
{
    if (n > (unsigned int)((mEnd - mBegin) / 12)) {
        GrowTo(mEnd, (int)(n - (unsigned int)((mEnd - mBegin) / 12)), rValue);
        return;
    }
    erase(mBegin + n * 12, mEnd);
}

// @ 0x00c8deb0
void __fastcall TP_RemoveOwner(TotemPole* pSelf)
{
    MWModel** pBegin = pSelf->mModels.mBegin;
    MWModel** pEnd = pSelf->mModels.mEnd;
    MWModel** pNewEnd = (MWModel**)CopyRefs(pEnd, pEnd, pBegin);
    pSelf->mModels.DestroyValues(pNewEnd, pSelf->mModels.mEnd);
    unsigned int nCount = (unsigned int)(pEnd - pBegin);
    pSelf->mModels.mEnd -= nCount;
    {
        void* pOwner = *(void**)((char*)pSelf + 0x2c);
        if (pOwner != 0) {
            *(void**)((char*)pSelf + 0x2c) = 0;
            typedef void (__thiscall *ReleaseFn)(void*);
            void** pVtbl = *(void***)pOwner;
            ((ReleaseFn)pVtbl[1])(pOwner);
        }
    }
    pSelf->mSpatial.Teardown();
}

// @ 0x00c8df10
bool TotemPole::PostDataLoad(unsigned int nID)
{
    bool bRet = PostDataLoadBase(nID);
    if (nID < 0x15000b) {
        unsigned int nSeg = (unsigned int)(mSegmentsEnd - mSegmentsBegin);
        ((Vec0C*)&mColorsBegin)->resize(nSeg, kSPColorRed);
    }
    return bRet;
}

// @ 0x00c8df60
void __fastcall TP_ResetModels(SpatialBody* pSelf)
{
    ModelList* pList = &pSelf->mModels;
    for (MWModel** p = pSelf->mModels.mBegin; p != pSelf->mModels.mEnd; ++p) {
        MWModel* pModel = *p;
        if (pModel != 0) {
            ((void(__thiscall*)(void*, int))(*(void***)pModel)[0x16c / 4])(pModel, 0);
            void* pOwner = pModel->mpOwner;
            if (pOwner != 0) {
                pModel->mpOwner = 0;
                typedef void (__thiscall *ReleaseFn)(void*);
                ((ReleaseFn)(*(void***)pOwner)[1])(pOwner);
            }
        }
    }
    {
        MWModel** pB = pList->mBegin;
        MWModel** pE = pList->mEnd;
        MWModel** pW = (MWModel**)CopyRefs(pE, pE, pB);
        pList->DestroyValues(pW, pList->mEnd);
        pList->mEnd = (MWModel**)((char*)pList->mEnd + ((char*)pB - (char*)pE));
    }
    pSelf->Release();
}
