// Declarations for slice s00bfcc80: SP::cCombatant (ctor/dtor/TakeHit/PartialRepair and
// the hostile-entry record helpers) plus the cGameData definition-id helpers.
//
// Retail cCombatant here is 0xc8 bytes, larger than the 0x98-byte SP::cCombatant in the
// PDB, so the layout below is the observed one; names come from the PDB where the offset
// and type agree and are coined from the ctor/dtor accesses otherwise.
#pragma once
#include "types.h"

// --- SP::cCombatant ---------------------------------------------------------
struct RcMap    { void* mRoot; void NukeSubtree(void* key); };  // 0x009A9600-style thiscall
#pragma pack(push, 1)
struct Combatant {
    void**   vftable;                                           // +0x00
    uint32_t pad04;                                             // +0x04
    unsigned char mIgnoreCombatLineTest;                        // +0x08
    unsigned char mLineTestIgnoresFriendlies;                   // +0x09
    unsigned char pad0a[2];                                     // +0x0a
    RcMap    mMap0c;                                            // +0x0c intrusive hostile tree
    void*    mDamageState10;                                    // +0x10 (intrusive list head, points at itself)
    void*    mList14;                                           // +0x14
    void*    mList18;                                           // +0x18
    unsigned char mByte1c;                                      // +0x1c
    unsigned char pad1d[3];                                     // +0x1d
    uint32_t mField20;                                          // +0x20
    void*    mActiveTarget24;                                   // +0x24
    void*    mNextTarget28;                                     // +0x28
    float    mField2c;                                          // +0x2c
    void*    mField30;                                          // +0x30
    uint32_t mField34;                                          // +0x34
    float    mHealth38;                                         // +0x38
    uint32_t mDamageState3c;                                    // +0x3c
    float    mField40;                                          // +0x40
    void*    mField44;                                          // +0x44
    void*    mField48;                                          // +0x48
    float    mField4c;                                          // +0x4c
    float    mField50;                                          // +0x50
    float    mField54;                                          // +0x54
    void*    mHostileBegin58;                                   // +0x58
    void*    mHostileEnd5c;                                     // +0x5c
    void*    mHostileCap60;                                     // +0x60
    uint32_t pad64[2];                                          // +0x64
    unsigned char mStunFlag6c;                                  // +0x6c
    unsigned char pad6d[3];                                     // +0x6d
    uint32_t mStunTimer70;                                      // +0x70
    float    mField74;                                          // +0x74
    float    mField78;                                          // +0x78
    float    mField7c;                                          // +0x7c
    unsigned char mByte80;                                      // +0x80
    unsigned char mByte81;                                      // +0x81
    unsigned char pad82[2];                                     // +0x82
    void*    mVec84Begin;                                       // +0x84
    void*    mVec84End;                                         // +0x88
    void*    mVec84Cap;                                         // +0x8c
    uint32_t pad90[2];                                          // +0x90
    uint32_t mTimer98[9];                                       // +0x98 (cGonzagoTimer, 0x24 bytes)
    void*    mSlotsBc[3];                                       // +0xbc

    Combatant();                                                // 0x00BFD4E0
    ~Combatant();                                               // 0x00BFCD00
    void  TakeHit(float amount, void* pos, int type, void* flags, void* source); // 0x00BFCDD0
    void  PartialRepair(float amount);                          // 0x00BFD1A0
};
#pragma pack(pop)

// --- small math value types -------------------------------------------------
struct Vector3 { float x, y, z; };                              // 0x0c
#pragma pack(push, 1)
struct Matrix3 { float m[9]; };                                 // 0x24 (column-major rows)
struct SpVec3 {                                                 // eastl-style vector of Vector3
    Vector3* begin;                                             // +0x00
    Vector3* end;                                               // +0x04
    Vector3* cap;                                               // +0x08
    void erase(Vector3* first, Vector3* last);                  // 0x0050F740
    void DoInsertValue(Vector3* pos, const Vector3* v);         // 0x004B5AD0
};
// The placement/transform record FUN_00bfd2b0 hands to the object at +0x30.
struct Placement {
    unsigned short flags;                                       // +0x00
    short          count;                                       // +0x02
    Vector3        pos;                                         // +0x04
    float          scale;                                       // +0x10
    Matrix3        basis;                                       // +0x14
};
// The receiver of FUN_00bfd2b0 (a spatial object owning the effect handle at +0x30).
struct OrientObject {
    void** vftable;                                             // +0x00
    unsigned char pad04[0x2c];                                  // +0x04..+0x30
    void*  mEffectHandle30;                                     // +0x30
};
struct RcHandle {                                               // effect handle, Apply at vtable +0x18
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4(); virtual void _v5();
    virtual void Apply(Placement* p);                           // vtable +0x18
};
#pragma pack(pop)

// --- the 0x28-byte hostile-entry record (vtable 0x01464450) ------------------
struct HostileEntry {
    void*    vftable;                                           // +0x00
    uint32_t mRefCount4;                                        // +0x04
    uint32_t mField08;                                          // +0x08
    uint32_t mField0c;                                          // +0x0c
    uint32_t mField10;                                          // +0x10
    uint32_t mField14;                                          // +0x14
    unsigned char mByte18;                                      // +0x18
    uint32_t mField1c;                                          // +0x1c
    uint32_t mField20;                                          // +0x20
    uint32_t pad24;                                             // +0x24
};

// --- Simulator::cGameData ---------------------------------------------------
// The definition-id list is a vector of 0xc-byte records at +0x58 with the flag at +0x6c.
struct GameData {
    void**   vftable;                                           // +0x00
    uint32_t pad04[0x15];                                       // +0x04..+0x58
    SpVec3   mDefs;                                             // +0x58 definition-id vector
    uint32_t pad64[2];                                          // +0x64
    unsigned char mFlag6c;                                      // +0x6c

    void SetDefinitionID();                                     // 0x00BFD800
    float* SetGameDataOwner(float* out, int index);             // 0x00BFD840
    void Cleanup();                                             // 0x00BFD610
};

// --- callees ---------------------------------------------------------------
void*  EffectsManagerPtr();                                     // 0x0067DDD0
void*  MessageServer();                                         // 0x0067DCC0
char   FUN_00bfc900(void* a);                                   // 0x00BFC900
char   FUN_00b673c0(void* a);                                   // 0x00B673C0
float  FUN_00b685e0(void* a);                                   // 0x00B685E0
void   FUN_00b69930(void* a, float f);                          // 0x00B69930
void   operator_delete__(void* p);                              // 0x00F47380

void*  GetCurrentGameMode();                                    // 0x00B5B800
void*  SpaceGameGet();                                          // 0x01002BD0
void*  GetPlayerInventory(void* game);                          // 0x00A1AD60
int    GetToolFromToolID(void* inv, void* id);                  // 0x00FF3D40
char   FUN_0104bde0(void* tool);                                // 0x0104BDE0
float  FUN_0104bdc0(void* tool);                                // 0x0104BDC0
char   TimerIsRunning(void* t);                                 // 0x00FEBA90
int    TimerGetElapsedTime(void* t);                            // 0x00BC3190
void*  GetUFOSimulator();                                       // 0x00FFBE50
void*  FUN_0108db30(void* sim);                                 // 0x0108DB30
int    GetPlayerEmpireID();                                     // 0x01021090
void*  FUN_00d61ce0(void* out, unsigned a, void* b, void* c);   // 0x00D61CE0
void   FUN_00bfca80(void* o);                                   // 0x00BFCA80
void*  FUN_00b18530(void* gd);                                  // 0x00B18530
char   FUN_00f25370(void* gd);                                  // 0x00F25370
void   FUN_00f24b30(void* o);                                   // 0x00F24B30
void   SlotMessage_Construct(void* m, int z);                   // 0x00421C80
void   SlotMessage_Destruct(void* m);                           // 0x00421CF0
void*  PlanetModelGet(void* out, void* model);                  // 0x00B3D350
void*  PlanetModelNormal(void* self, void* vec);                // 0x00B7E3B0
void   OrthogonalVector(Vector3* out, const Vector3* in);       // 0x006985B0
Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up); // 0x0069B440
char   FUN_006a0990(void* a, unsigned key, float* out, void** arr); // 0x006A0990
void   Matrix3_Assign(void* self, const void* src);             // 0x0041CB40
extern "C" void cSpatialObject_LocalToWorldTransform(void* self, const void* m); // 0x00C897E0

// ---------------------------------------------------------------------------
// Receiver structs: the original reaches each helper's `this` through ecx, so the
// calls are modelled as member functions (a real thiscall: mov ecx,recv; call).
// The ones the original dispatches through a vftable are declared virtual.
// ---------------------------------------------------------------------------
struct RcSlot {                                                 // a released effect handle
    virtual void _v0();
    virtual void Release4();                                    // vtable +0x04
    virtual void _v2(); virtual void _v3();
    virtual char IsActive();                                    // vtable +0x10
    virtual void _v5(); virtual void _v6(); virtual void _v7(); virtual void _v8();
    virtual void _v9(); virtual void _v10(); virtual void _v11(); virtual void _v12();
    virtual void _v13(); virtual void _v14(); virtual void _v15(); virtual void _v16();
    virtual void _v17(); virtual void _v18(); virtual void _v19(); virtual void _v20();
    virtual void _v21(); virtual void _v22(); virtual void _v23(); virtual void _v24();
    virtual void Release64();                                   // vtable +0x64
};
struct RcEffectMgr {                                            // effect manager (SP::EffectsManager)
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual void _v8(); virtual void _v9(); virtual void _v10();
    virtual char AddSlot(unsigned id, int zero, void** slot);   // vtable +0x2c
};
struct RcTimer {                                                // SP::cGonzagoTimer
    void Dtor();                                                // 0x00B638B0
    void Ctor();                                                // 0x00B63890
};
struct RcVecStore { uint32_t mElemCount; };                     // SGI vector header word before begin
struct CombatantListHead {                                      // the intrusive list head embedded at cCombatant+0x10
    void*    mNext;                                             // +0x00
    void*    mPrev;                                             // +0x04
    void*    mLive;                                             // +0x08
    uint32_t mField0c;                                          // +0x0c (mByte1c plus padding, written as a dword)
};
struct RcMatrix { void Assign(const void* src); };              // 0x0041CB40 Matrix3::Assign
struct RcGameData { void Cleanup(); };                          // 0x00BFD610
struct RcSpatial { void LocalToWorldTransform(const void* m); };// 0x00C897E0
struct RcMsg {                                                  // MessageServer
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4();
    virtual void Send(unsigned id, void* msg, unsigned flags);   // vtable +0x14
};
// The object returned by the vslots, with the accessors the two data helpers use.
struct RcTmpObj {
    virtual void _v0(); virtual void _v1();
    virtual void* GetSlot0c();                                  // +0x0c (indirect)
    virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual void _v8(); virtual void _v9(); virtual void _v10(); virtual void _v11();
    virtual void _v12(); virtual void _v13(); virtual void _v14(); virtual void _v15();
    virtual void _v16(); virtual void _v17(); virtual void _v18(); virtual void _v19();
    virtual void _v20(); virtual void _v21(); virtual void _v22(); virtual void _v23();
    virtual void _v24(); virtual void _v25(); virtual void _v26(); virtual void _v27();
    virtual void _v28(); virtual void _v29(); virtual void _v30(); virtual void _v31();
    virtual void _v32(); virtual void _v33(); virtual void _v34(); virtual void _v35();
    virtual void _v36(); virtual void _v37(); virtual void _v38(); virtual void _v39();
    virtual void _v40(); virtual void _v41(); virtual void _v42(); virtual void _v43();
    virtual void _v44(); virtual void _v45(); virtual void _v46(); virtual void _v47();
    virtual void _v48(); virtual void _v49(); virtual void _v50(); virtual void _v51();
    virtual void _v52(); virtual void _v53(); virtual void _v54(); virtual void _v55();
    virtual void _v56(); virtual void _v57(); virtual void _v58(); virtual void _v59();
    virtual void _v60(); virtual void _v61(); virtual void _v62(); virtual void _v63();
    virtual void _v64(); virtual void _v65(); virtual void _v66(); virtual void _v67();
    virtual void _v68(); virtual void _v69(); virtual void _v70(); virtual void _v71();
    virtual void _v72(); virtual void _v73(); virtual void _v74(); virtual void _v75();
};

// Random generator singleton used by SetDefinitionID.
struct RandomLCG { unsigned RandomUint32Uniform(unsigned n); };  // 0x00A68FB0
extern RandomLCG gRandomLCG;                                    // 0x01601760
