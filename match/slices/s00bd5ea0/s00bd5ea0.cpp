// Slice s00bd5ea0 (0x00bd5ea0..0x00bd7085) — SPGonzago/SPGameNounManager.obj:
// a cCheatObject noun/template factory (0x00bd5ea0), cCelestialBody
// ctor/dtor/orbit-position helpers, cCheatObject ctor/dtor/Write/Read/QueryInterface/
// field-values, the cheat IHandlerRC registration and the cCityInputStrategy
// commodity-menu builders, plus a GB1-derived cGonzagoSubsystem ctor.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc)

#include "types.h"
#include <math.h>

#pragma warning(disable: 4100)

typedef unsigned int   uint;
typedef unsigned short ushort;

typedef void* (__thiscall* Fn_p_v)(void*);
typedef void  (__thiscall* Fn_x_v)(void*);
typedef int   (__thiscall* Fn_i_v)(void*);
typedef void  (__thiscall* Fn_x_vi)(void*, int);
typedef void* (__thiscall* Fn_p_vi)(void*, int);

struct IV {  // pure vtable stub (48 slots covers every call site here)
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
  virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
  virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
};
#define VT(p, off)     (*(void**)((char*)(*(void**)(p)) + (off)))
#define VCALL0(p, off) ((Fn_x_v)VT(p, off))(p)

// ---------------------------------------------------------------- free callees
void* __cdecl SP_ObjectTemplateDB();                         // 0x0067cb40
void* __cdecl SP_NounManager(int id);                        // 0x00b3d300
void* __cdecl SP_ResourceMan_GetManager();                   // 0x0067dcd0
void* __cdecl SP_MessageServer();                            // 0x0067dcc0
void* __cdecl SP_GameInputManager();                         // 0x00b3d250
void* __cdecl FUN_00b25f40(void* nounMgr, uint id);          // 0x00b25f40
void  __cdecl FUN_004e39a0(void* a, void* b);                // 0x004e39a0
void  __cdecl FUN_004e39d0(void* a, void* b);                // 0x004e39d0
void  __cdecl FUN_00606880(void* v);                         // 0x00606880
void  __cdecl operator_delete__(void* p);                    // 0x00f47380
void  __cdecl FUN_00ba5df0(void* a, void* b);                // 0x00ba5df0
bool  __cdecl FUN_00bf2c80(void* a, void* b);                // 0x00bf2c80
void* __cdecl FUN_00bf9700(void* a, void* b);                // 0x00bf9700
void  __cdecl FUN_00bf4a60(void* a, void* b, void* c);       // 0x00bf4a60
void* __cdecl FUN_00bf9770(void* a, void* b);                // 0x00bf9770
void  __cdecl FUN_00bf4b10(void* a, void* b, void* c);       // 0x00bf4b10
void  __cdecl FUN_00b7d390(void* p);                         // 0x00b7d390
void  __cdecl FUN_00b7d2e0(void* self, const wchar_t* name, int a, int b); // 0x00b7d2e0
void  __cdecl FUN_00b7cc60(void* a, void* b);                // 0x00b7cc60
struct cVarListSerializer {
  uint32_t mData[645];                                   // size 0xa14
  void ctor(void* owner, const void* table, uint id);    // 0x00692f90
  int  Write(void* s);                                   // 0x00692900
  int  Read(void* s);                                    // 0x00693e10
  int  GetFields(void* out);                             // 0x00695960
};
void  __fastcall FUN_00ac0450(void* p);                      // 0x00ac0450
void* __cdecl FUN_00ac0320(void* p);                         // 0x00ac0320
void* __cdecl FUN_00b18460(void* p);                         // 0x00b18460
void* __cdecl FUN_00c884f0(void* p);                         // 0x00c884f0
void  __fastcall FUN_00c8b2e0(void* p);                      // 0x00c8b2e0
void  __fastcall FUN_00ac0520(void* p);                      // 0x00ac0520
void  __fastcall FUN_00c8a420(void* p);                      // 0x00c8a420
void  __fastcall FUN_00ac03d0(void* p);                      // 0x00ac03d0
void  __fastcall FUN_00c89630(void* p);                      // 0x00c89630
void  __fastcall FUN_00b18660(void* p);                      // 0x00b18660
void  __fastcall FUN_00b184c0(void* p);                      // 0x00b184c0
void  __cdecl FUN_00c88a90(void* p, void* s);                // 0x00c88a90
void  __cdecl FUN_00b18590(void* p, void* s);                // 0x00b18590
void  __cdecl FUN_00c88b00(void* p, void* s);                // 0x00c88b00
void  __cdecl FUN_00b18600(void* p, void* s);                // 0x00b18600
int   __cdecl FUN_00b18420(void* p, void* v);                // 0x00b18420
void  __cdecl Constraint_ctor(void* out, uint key, int kind, uint value);  // 0x00558960
void* __cdecl FUN_00fe8780(void* out, void* a, void* b, void* c, float f); // 0x00fe8780
void* __cdecl SP_normalized_safe(void* out, void* v);        // 0x00449c20
void  __cdecl MatrixFromTwoVectors(void* out, const void* up, const void* fwd);  // 0x0069b1c0
struct cXform { void RotateZ(float a); };                    // 0x007d1ac0 (__thiscall)
double __cdecl EA_RandomDoubleUniform(void* rng);            // 0x009360d0
struct cRandomLinearCongruential {                            // RNG singleton @0x01601760
  double __thiscall RandomDoubleUniform();                   // 0x009360d0
};
void  __cdecl FUN_00f924e0_hack(float v);                    // 0x00f924e0
void  __cdecl FUN_00c0b9d0_hack(float v);                    // 0x00c0b9d0

struct IOStream {
  virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
  virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
  virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18();
};
bool __cdecl EA_IO_WriteUint32(IOStream* s, const void* p, int n, int z);  // 0x0093aa70

// ---------------------------------------------------------------- classes
struct IRef {
  virtual int AddRef();
  virtual int Release();
};
struct cSPVector3 { float x, y, z; };

struct GameDataVec { void* mpBegin; void* mpEnd; void* mpCapacity; };
struct cGameNounManager {
  void RemoveNoun(void* noun);                               // 0x00b225d0
  void RemoveNounsOfType(int type);                          // 0x00b22650
  GameDataVec* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, uint tag);  // 0x00b21340
};
cGameNounManager* __cdecl NounManager();                     // 0x00b3d300

// eastl::vector<SP::FunctionalMatch::Constraint> (retail: 0x10 header + allocator)
namespace SP { namespace FunctionalMatch { struct Constraint; } }
struct ConstraintVector {
  SP::FunctionalMatch::Constraint* mpBegin;   // +0x00
  SP::FunctionalMatch::Constraint* mpEnd;     // +0x04
  SP::FunctionalMatch::Constraint* mpCapacity;// +0x08
  uint mAllocator;                            // +0x0c
  ConstraintVector() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(0) {}
  void push_back(const SP::FunctionalMatch::Constraint& v);   // 0x004e18e0
};

namespace SP {

extern int g_GameDataCount;   // 0x0167be2c

#pragma pack(push, 4)
// Retail cGameData is 0x34 bytes (the 2008 dev PDB has 0x2c).
class cGameData : public IRef {
 public:
  char  pad04[8];
  void* mpNext;                  // +0x0c
  void* mpPrev;                  // +0x10
  bool  mIsDestroyed;            // +0x14
  char  pad15[3];
  uint  mID;                     // +0x18
  uint  mDefinitionID;           // +0x1c
  bool  mb20;                    // +0x20
  bool  mb21;                    // +0x21
  char  pad22[2];
  uint  m24;                     // +0x24
  void* mView;                   // +0x28
  IRef* mpGameDataOwner;         // +0x2c
  uint  mPoliticalID;            // +0x30

  cGameData();                                            // 0x00b18660
  int GetFieldValues(void* vec);                         // 0x00b18420
  uint GetPoliticalID() const;                            // 0x00804830
  uint GetNounID() const;                                 // vtable slot 0x20
  uint GetNounKey() const;                                // vtable slot 0x4c
  void WriteData(void* s) const;                          // 0x00b18590
  void ReadData(void* s);                                 // 0x00b18600
  void WriteTagged(void* s);                              // 0x00bd6230
  void DtorBody();                                        // 0x00b184c0
  void* AsInterfaceQuery(uint id);                        // 0x00b18460
};
#pragma pack(pop)

namespace FunctionalMatch {
struct Constraint {   // 0x24 bytes
  Constraint(uint property, uint op, uint value);   // 0x00558960
  uint mData[4];
  uint mSub[4];
  uint mFlags;
};
}

struct cEllipticalOrbit {   // retail size 0x68; +0x38 relative to cCelestialBody
  bool  mNullOrbit;          // +0x00
  char  pad01[3];
  cSPVector3 mPlaneNormal;   // +0x04
  float mEccentricity;       // +0x10
  cSPVector3 mPerihelion;    // +0x14
  float mPeriod;             // +0x20
  float a;                   // +0x24
  float a2;                  // +0x28
  float b;                   // +0x2c
  float b2;                  // +0x30
  float c;                   // +0x34
  float c2;                  // +0x38
  float e2;                  // +0x3c
  float area;                // +0x40
  cSPVector3 planeRelativeXAxis;  // +0x44
  cSPVector3 planeRelativeYAxis;  // +0x50
  cSPVector3 centerToFocus;       // +0x5c
};

class cSolarHitSphere;
class cIVisualEffect;

// Retail cCelestialBody is the dev-PDB layout shifted +8 (cGameData is 0x34).
class cCelestialBody : public cGameData {
 public:
  enum eType { kUnknownCelestialBody = -1, kStar = 0, kAsteroidBelt = 1, kComet = 2 };

  cCelestialBody(eType type);                       // 0x00bd6410
  ~cCelestialBody();                                // 0x00bd6530
  void RemoveOwner();                               // 0x00bd61c0
  void UpdateOrbit();                               // 0x00bd6300
  void UpdatePosition(float dt);                    // 0x00bd6590

  eType            mType;         // +0x34
  cEllipticalOrbit mOrbit;        // +0x38
  cSPVector3       mPosition;     // +0xa0
  float            mRotationRate;  // +0xac
  wchar_t*         mNameBegin;    // +0xb0
  wchar_t*         mNameEnd;      // +0xb4
  wchar_t*         mNameCap;      // +0xb8
  uint             mNameD;        // +0xbc
  IRef*            mEffect;       // +0xc0
  IRef*            mHitSphere;    // +0xc4
  float            mHitSphereSize;// +0xc8
};

class cSpatialObject {
 public:
  virtual ~cSpatialObject();
  bool WriteSpatial(void* s) const;                 // 0x00c88a90
  bool ReadSpatial(void* s);                        // 0x00c88b00
  virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
  virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
  virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();

  cSpatialObject();                                 // 0x00c89630
  void DtorBody();                                  // 0x00c8a420
  void* AsInterfaceQuery(uint id);                  // 0x00c884f0
  char pad80[0x6c];
  bool mbSpatialFlag;                               // +0x70 (retail)
  char pad71[0x63];                                 // -> retail size 0xd4
};

class cInteractionTarget {
 public:
  virtual ~cInteractionTarget();
  virtual void* AsInterface(uint id);
  virtual void RemoveInteraction(void* i);
  virtual void AddInteraction(void* i);
  virtual void Shutdown();
  virtual int Release();
  cInteractionTarget();                             // 0x00ac03d0
  void DtorBody();                                  // 0x00ac0520
  void* QueryInterfaceHere(uint id);                // 0x00ac0320
  char pad04[0x14];                                 // -> retail size 0x18
};

// Retail cCheatObject: cGameData@0, cSpatialObject@0x34, cInteractionTarget@0x108.
class cCheatObject : public cGameData, public cSpatialObject, public cInteractionTarget {
 public:
  cCheatObject();                                   // 0x00bd6a80
  ~cCheatObject();                                  // 0x00bd6c10
  void BindCheatHandlers();                         // 0x00bd6c60
  void DtorBases();                                 // 0x00bd6750
  void* QueryInterface(uint id);                    // 0x00bd6770
  void WriteBody(void* s) const;                    // 0x00bd67c0
  void ReadBody(void* s);                           // 0x00bd6810
  int GetFieldValuesAll(void* vec);                 // 0x00bd6b10
  IRef* mpDataObject;                               // +0x120
  bool  mFlag124;                                   // +0x124
  char  pad125[3];
};

}  // namespace SP

using SP::cGameData;
using SP::cCelestialBody;
using SP::cCheatObject;
using SP::FunctionalMatch::Constraint;

// ---------------------------------------------------------------- data globals
#define VT_cCelestialBody0 ((void*)0x01467e80)
#define VT_cCelestialBody1 ((void*)0x01467e6c)
#define VT_cCheatObject0   ((void*)0x014680b8)
#define VT_cCheatObject1   ((void*)0x014680a4)
#define VT_cCheatObject2   ((void*)0x01467fe0)
#define VT_cCheatObject3   ((void*)0x01467fc0)
#define VT_GB1             ((void*)0x013eb384)

extern float gPos_168bc90[3];      // 0x0168bc90 (0,0,0)
extern float gOne_1485720;         // 0x01485720 (1.0f)
extern wchar_t gEmptyString16[];   // 0x01667bac
extern char  gVarTable_A[];        // 0x0156e0c8
extern char  gVarTable_B[];        // 0x0156df10
extern char  gVarTable_C[];        // 0x0157a1f8

// ===========================================================================
// @ 0x00bd5ea0  cCheatObject noun/template spawn helper
// Resolve the body's resource key, pick a template matching the noun type via
// a two-constraint FunctionalMatch query, then (re)create the matching model
// nouns / vehicles.
// ===========================================================================
extern char gTemplateSlotTable[];   // 0x0168caf0, stride 0x1c up to 0x0168cb44
extern char gTemplateSlotEnd[];     // 0x0168cb44

bool __fastcall FUN_00bd5ea0(cCheatObject* self) {
  bool result = true;
  IV* spatial = (IV*)((char*)self + 0x34);
  uint* key = (uint*)((Fn_p_v)VT(spatial, 0x98))(spatial);
  uint kInstance = key[0];
  uint kType     = key[1];
  uint kGroup    = key[2];
  if (kInstance == 0)
    return result;

  IV* rm = (IV*)SP_ResourceMan_GetManager();
  if (((char(__thiscall*)(IV*, const void*, int, int, int, int, int))VT(rm, 0xc))
        (rm, key, 0, 0, 0, 0, 0))
    return result;

  uint nounId = self->GetNounKey();
  SP_NounManager(nounId);
  FUN_00b25f40(SP_NounManager(nounId), nounId);

  ConstraintVector constraints;
  uint prop = 0x4e3f7777;
  uint type = self->GetNounID();
  if (type == 0x1a56aba)
    prop = 0x72c49181;
  else if (type == 0x18ea1eb || type == 0x70703b3)
    prop = 0x99e92f05;
  else if (type == 0x18ea2cc)
    prop = 0x47c10953;
  constraints.push_back(Constraint(0x2dc9d1e, 0, prop));
  constraints.push_back(Constraint(0x3cc89b1, 0, 0x913b23be));

  IV* db = (IV*)SP_ObjectTemplateDB();
  uint found = 0, pad = 0, found2 = 0;
  if (!((char(__thiscall*)(IV*, uint*, int, uint*))VT(db, 0x24))(db, &found, 1, &pad)) {
    result = false;
  } else {
    db = (IV*)SP_ObjectTemplateDB();
    ((void(__thiscall*)(IV*, uint, int))VT(db, 0x58))(db, found, 1);
    uint local2[3];
    FUN_00ba5df0(&local2[0], key);
    for (char* slot = gTemplateSlotTable; slot < gTemplateSlotEnd; slot += 0x1c) {
      if (FUN_00bf2c80(slot, (void*)prop)) {
        uint* p = (uint*)FUN_00bf9700(slot, (void*)prop);
        if (p[0] == kInstance && p[1] == kType && p[2] == kGroup)
          FUN_00bf4a60(slot, (void*)prop, (void*)found);
      }
    }
    GameDataVec* v = NounManager()->GetGameDataVector(
        (void*)0x00b21080, (void*)0x00d3d420, (void*)0x00b236c0, (void*)0x00b1e500, 0x18c816a);
    for (void** it = (void**)v->mpBegin; it != (void**)v->mpEnd; ++it) {
      uint* mk = (uint*)FUN_00bf9770(*it, (void*)prop);
      if (mk[0] == kInstance && mk[1] == kType && mk[2] == kGroup)
        FUN_00bf4b10(*it, (void*)prop, (void*)found);
    }
  }
  return result;
}

// ===========================================================================
// @ 0x00bd6180
// Flush a pending transform then hand back the sub-object at +0x344.
// ===========================================================================
void FUN_00bd40a0(void* p);   // 0x00bd40a0

void* __fastcall FUN_00bd6180(char* self) {
  if (self[0x340])
    ((void(__fastcall*)(char*))FUN_00bd40a0)(self);
  return self + 0x344;
}

// ===========================================================================
// @ 0x00bd61c0  SP::cCelestialBody::RemoveOwner
// ===========================================================================
void cCelestialBody::RemoveOwner() {
  IRef* owner = mEffect;
  if (owner) {
    ((void(__thiscall*)(IRef*, int))VT(owner, 0xc))(owner, 1);
    owner = mEffect;
    if (owner) {
      mEffect = 0;
      ((void(__thiscall*)(IRef*))VT(owner, 4))(owner);
    }
  }
  IRef* noun = mHitSphere;
  if (noun) {
    NounManager()->RemoveNoun(noun);
    noun = mHitSphere;
    if (noun) {
      mHitSphere = 0;
      ((void(__thiscall*)(IRef*))VT(noun, 4))(noun);
    }
  }
}

// ===========================================================================
// @ 0x00bd6230  Simulator::ISimulatorSerializable::Write
// ===========================================================================
void cGameData::WriteTagged(void* stream) {
  cVarListSerializer s;
  IV* obj = (IV*)stream;
  IV* writer = (IV*)((Fn_p_v)VT(obj, 0x20))(obj);
  uint magic = 0x38cfb68;
  void* w = ((Fn_p_v)VT(writer, 0x18))(writer);
  EA_IO_WriteUint32((IOStream*)w, &magic, 1, 0);
  s.ctor(this, gVarTable_B, 0x1a80d26);
  s.Write(stream);
}

// ===========================================================================
// @ 0x00bd6300  cCelestialBody::UpdateOrbit
// Pick a random true anomaly and place the body on its ellipse.
// ===========================================================================
extern float gOrbitAngle_156def8;   // 0x0156def8

void cCelestialBody::UpdateOrbit() {
  double range = gOrbitAngle_156def8;
  double nrange = -range;
  double angle = ((cRandomLinearCongruential*)0x01601760)->RandomDoubleUniform() * (range - nrange) + nrange;
  if (angle >= range)
    angle = range;
  else if (angle < nrange)
    angle = nrange;
  float ca = (float)cos(angle);
  float denom = (1.0f - mOrbit.e2) * mOrbit.a;
  float r = denom / (mOrbit.mEccentricity * ca + 1.0f);
  float rsa = (float)(r * sin(angle));
  mPosition.x = mOrbit.planeRelativeXAxis.x * (r * ca) + mOrbit.planeRelativeYAxis.x * rsa;
  mPosition.y = mOrbit.planeRelativeXAxis.y * (r * ca) + mOrbit.planeRelativeYAxis.y * rsa;
  mPosition.z = mOrbit.planeRelativeXAxis.z * (r * ca) + mOrbit.planeRelativeYAxis.z * rsa;
}

// ===========================================================================
// @ 0x00bd6410  SP::cCelestialBody::cCelestialBody
// ===========================================================================
cCelestialBody::cCelestialBody(cCelestialBody::eType type) {
  *(void**)this = VT_cCelestialBody0;
  *(void**)((char*)this + 4) = VT_cCelestialBody1;
  mType = type;
  mOrbit.mNullOrbit = true;
  mPosition.x = gPos_168bc90[0];
  mPosition.y = gPos_168bc90[1];
  mPosition.z = gPos_168bc90[2];
  *(float volatile*)&mRotationRate = 0.0f;
  *(wchar_t* volatile*)&mNameBegin = gEmptyString16;
  *(wchar_t* volatile*)&mNameEnd = gEmptyString16;
  *(wchar_t* volatile*)&mNameCap = gEmptyString16 + 1;
  *(IRef* volatile*)&mEffect = 0;
  *(IRef* volatile*)&mHitSphere = 0;
  *(float volatile*)&mHitSphereSize = 1.0f;
  if (type == kStar) {
    mPosition = *(const cSPVector3*)gPos_168bc90;
    mOrbit.mNullOrbit = true;
  }
}

// ===========================================================================
// @ 0x00bd6530  SP::cCelestialBody::~cCelestialBody (dtor body)
// ===========================================================================
void __fastcall cCelestialBody_Dtor(cCelestialBody* self) {
  *(void* volatile*)self = VT_cCelestialBody0;
  *(void* volatile*)((char*)self + 4) = VT_cCelestialBody1;
  IRef* hs = *(IRef* volatile*)&self->mHitSphere;
  if (hs) {
    ((void(__thiscall*)(IRef*))VT(hs, 4))(hs);
  }
  if (self->mEffect) {
    ((void(__thiscall*)(IRef*))VT(self->mEffect, 4))(self->mEffect);
  }
  char* nameBegin = (char*)self->mNameBegin;
  int diff = (int)((char*)self->mNameCap - nameBegin);
  if (((diff & ~1) > 2) && nameBegin)
    operator_delete__(nameBegin);
  self->DtorBody();
}

// ===========================================================================
// @ 0x00bd6590  cCelestialBody::UpdatePosition
// ===========================================================================
struct Matrix3f {
  float m[9];
  void Assign(const float* src);   // 0x0041cb40  (__thiscall)
};
struct OrbitFrame {
  unsigned short mFlags;    // +0x00
  unsigned short mSerial;   // +0x02
  cSPVector3 mOrigin;       // +0x04
  Matrix3f mBasis;          // +0x10
};

extern float gOrbitUp_156defc[3];       // 0x0156defc
extern float gOrbitBasis_168bcc4[9];    // 0x0168bcc4
extern float gOrbitEye_168bce8[3];      // 0x0168bce8
extern float gOrbitZero_1485378;        // 0x01485378

void cCelestialBody::UpdatePosition(float dt) {
  {
    cSPVector3 tmp;
    cSPVector3* p = (cSPVector3*)FUN_00fe8780(&tmp, &mPosition, gPos_168bc90, &mOrbit, dt);
    mPosition = *p;
  }

  if (mEffect == 0)
    return;
  if (!((char(__thiscall*)(IRef*))VT(mEffect, 0x10))(mEffect))
    return;

  OrbitFrame frame;
  frame.mFlags = 0;
  frame.mSerial = 0;
  frame.mOrigin.x = gOrbitEye_168bce8[0];
  frame.mOrigin.y = gOrbitEye_168bce8[1];
  frame.mOrigin.z = gOrbitEye_168bce8[2];
  frame.mBasis.m[0] = 1.0f;
  frame.mBasis.Assign(gOrbitBasis_168bcc4);
  ((void(__thiscall*)(IRef*, OrbitFrame*))VT(mEffect, 0x20))(mEffect, &frame);

  if (mType == kComet) {
    cSPVector3 up;
    void* n = SP_normalized_safe(&up, &mPosition);
    Matrix3f tmp2;
    MatrixFromTwoVectors(&tmp2, gOrbitUp_156defc, n);
    frame.mBasis = tmp2;
    frame.mFlags |= 2;
    frame.mSerial++;
  } else if (mRotationRate != 0.0f) {
    frame.mFlags |= 4;
    frame.mSerial++;
    frame.mOrigin = *(cSPVector3*)gPos_168bc90;
    ((cXform*)&frame)->RotateZ(mRotationRate * dt);
  }

  frame.mOrigin = mPosition;
  frame.mFlags |= 4;
  frame.mSerial++;
  ((void(__thiscall*)(IRef*, OrbitFrame*))VT(mEffect, 0x18))(mEffect, &frame);
}

// ===========================================================================
// @ 0x00bd6750  cCheatObject sub-object teardown
// ===========================================================================
void cCheatObject::DtorBases() {
  ((cInteractionTarget*)((char*)this + 0x108))->DtorBody();
  ((cSpatialObject*)((char*)this + 0x34))->DtorBody();
}

// ===========================================================================
// @ 0x00bd6770  cCheatObject::QueryInterface
// ===========================================================================
void* cCheatObject::QueryInterface(uint id) {
  if (id == 0x2a37e34)
    return this;
  void* r = ((cInteractionTarget*)((char*)this + 0x108))->QueryInterfaceHere(id);
  if (r == 0) {
    r = ((cGameData*)this)->AsInterfaceQuery(id);
    if (r == 0)
      r = ((cSpatialObject*)((char*)this + 0x34))->AsInterfaceQuery(id);
  }
  return r;
}

// ===========================================================================
// @ 0x00bd67c0  cCheatObject::Write
// ===========================================================================
void cCheatObject::WriteBody(void* stream) const {
  cVarListSerializer s;
  ((cSpatialObject*)((char*)this + 0x34))->WriteSpatial(stream);
  ((cGameData*)this)->WriteData(stream);
  s.ctor((void*)this, gVarTable_A, 0x1a80d26);
  s.Write(stream);
}

// ===========================================================================
// @ 0x00bd6810  cCheatObject::Read
// ===========================================================================
void cCheatObject::ReadBody(void* stream) {
  cVarListSerializer s;
  ((cSpatialObject*)((char*)this + 0x34))->ReadSpatial(stream);
  ((cGameData*)this)->ReadData(stream);
  s.ctor(this, gVarTable_A, 0x1a80d26);
  s.Read(stream);
}

// ===========================================================================
// @ 0x00bd6870  set the "dirty" flag then call the virtual
// ===========================================================================
struct IDirty {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void Notify();    // slot 0x20
  virtual void NotifyOff(); // slot 0x24
  char pad08[0x1c];
  bool mb20;                // +0x20
};

void __fastcall FUN_00bd6870(IDirty* self) {
  if (self->mb20 == false) {
    self->mb20 = true;
    self->Notify();
  }
}

// ===========================================================================
// @ 0x00bd6890
// ===========================================================================
void __fastcall FUN_00bd6890(IDirty* self) {
  self->mb20 = false;
  self->NotifyOff();
}

// ===========================================================================
// @ 0x00bd68a0  remove every noun of a fixed type
// ===========================================================================
void FUN_00bd68a0() {
  NounManager()->RemoveNounsOfType(0x2a37e35);
}

// ===========================================================================
// @ 0x00bd68c0  append three commodity nodes then select the given object
// ===========================================================================
#define gStr_1467f50 ((const wchar_t*)0x01467f50)   // 0x01467f50
#define gStr_1467f48 ((const wchar_t*)0x01467f48)   // 0x01467f48
#define gStr_1467f40 ((const wchar_t*)0x01467f40)   // 0x01467f40

struct cCityInputStrategy {                        // singleton at 0x0168bd4c
  void Begin();                                    // 0x00b7d390
  void AddNode(const wchar_t* name, int id, int flags); // 0x00b7d2e0
  void SelectNode(void* obj, void* arg);           // 0x00b7cc60
};
#define kCityInputStrategy ((cCityInputStrategy*)0x0168bd4c)

void FUN_00bd68c0(cCheatObject* obj) {
  kCityInputStrategy->Begin();
  kCityInputStrategy->AddNode(gStr_1467f50, 0x1f41, 0);
  kCityInputStrategy->AddNode(gStr_1467f48, 0x1f43, 0);
  kCityInputStrategy->AddNode(gStr_1467f40, 0x1f42, 0);
  kCityInputStrategy->SelectNode(obj ? (char*)obj + 0x34 : 0, 0);
}

// ===========================================================================
// @ 0x00bd6940  civic commodity menu (energy / entertainment / happiness)
// ===========================================================================
#define gStrEnergy ((const wchar_t*)0x01467f90)         // 0x01467f90
#define gStrEntertainment ((const wchar_t*)0x01467f74)  // 0x01467f74
#define gStrHappiness ((const wchar_t*)0x01467f60)      // 0x01467f60
#define gStrAll ((const wchar_t*)0x01467f58)            // 0x01467f58

void FUN_00bd6940(cCheatObject* obj) {
  kCityInputStrategy->Begin();
  kCityInputStrategy->AddNode(gStrEnergy, 0x1f47, 0);
  kCityInputStrategy->AddNode(gStrEntertainment, 0x1f49, 0);
  kCityInputStrategy->AddNode(gStrHappiness, 0x1f4a, 0);
  kCityInputStrategy->AddNode(gStrAll, 0x1f4b, 0);
  kCityInputStrategy->SelectNode(obj ? (char*)obj + 0x34 : 0, 0);
}

// ===========================================================================
// @ 0x00bd69d0  creature commodity menu (hunger / energy / health)
// ===========================================================================
#define gStrHunger ((const wchar_t*)0x01467fb0)   // 0x01467fb0
#define gStrHealth ((const wchar_t*)0x01467fa0)   // 0x01467fa0

void FUN_00bd69d0(cCheatObject* obj) {
  kCityInputStrategy->Begin();
  kCityInputStrategy->AddNode(gStrHunger, 0x1f46, 0);
  kCityInputStrategy->AddNode(gStrEnergy, 0x1f47, 0);
  kCityInputStrategy->AddNode(gStrHealth, 0x1f48, 0);
  kCityInputStrategy->AddNode(gStrAll, 0x1f4b, 0);
  kCityInputStrategy->SelectNode(obj ? (char*)obj + 0x34 : 0, 0);
}

// ===========================================================================
// @ 0x00bd6a60  resolve an AutoRefCount-like { value, refcount } to a pointer
// ===========================================================================
void* __fastcall FUN_00bd6a60(char* self) {
  if (*(uint*)(self + 0x10) & 0x30)
    return *(void**)self;
  return (*(ushort*)(self + 0x12) != 0) ? (void*)self : 0;
}

// ===========================================================================
// @ 0x00bd6a80  SP::cCheatObject::cCheatObject
// ===========================================================================
cCheatObject::cCheatObject() {
  *(void**)this = VT_cCheatObject0;
  *(void**)((char*)this + 4) = VT_cCheatObject1;
  *(void**)((char*)this + 0x34) = VT_cCheatObject2;
  *(void**)((char*)this + 0x108) = VT_cCheatObject3;
  *(IRef* volatile*)&mpDataObject = 0;
  *(bool volatile*)&((cSpatialObject*)((char*)this + 0x34))->mbSpatialFlag = false;
  IRef* p = *(IRef* volatile*)&mpDataObject;
  if (p) {
    mpDataObject = 0;
    ((void(__thiscall*)(IRef*))VT(p, 4))(p);
  }
}

// ===========================================================================
// @ 0x00bd6b10  cCheatObject::GetFieldValuesAll
// ===========================================================================
int cCheatObject::GetFieldValuesAll(void* vec) {
  cVarListSerializer s;
  int n = GetFieldValues(vec);
  s.ctor((char*)this + 0x34, gVarTable_C, 0x1a80d26);
  return s.GetFields(vec) + n;
}

// ===========================================================================
// @ 0x00bd6c10  SP::cCheatObject::~cCheatObject
// ===========================================================================
void __fastcall cCheatObject_Dtor(cCheatObject* self) {
  void* sp = (char*)self + 0x34;
  void* it = (char*)self + 0x108;
  *(void**)self = VT_cCheatObject0;
  *(void**)((char*)self + 4) = VT_cCheatObject1;
  *(void**)sp = VT_cCheatObject2;
  *(void**)it = VT_cCheatObject3;
  IRef* p = *(IRef* volatile*)&self->mpDataObject;
  if (p) {
    ((void(__thiscall*)(IRef*))VT(p, 4))(p);
  }
  FUN_00ac0520(it);
  FUN_00c8a420(sp);
  FUN_00b184c0(self);
}

// ===========================================================================
// @ 0x00bd6c60  cCheatObject::BindCheatHandlers
// ===========================================================================
struct ICheatSink {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void RegPart(uint id, const char* name);   // vtable slot 0x40
};

#define gCheatCmd0 ((const char*)0x01468294)
#define gCheatCmd1 ((const char*)0x01468274)
#define gCheatCmd2 ((const char*)0x01468258)
#define gCheatCmd3 ((const char*)0x0146823c)
#define gCheatCmd4 ((const char*)0x01468220)
#define gCheatCmd5 ((const char*)0x01468208)
#define gCheatCmd6 ((const char*)0x014681f0)
#define gCheatCmd7 ((const char*)0x014681d8)
#define gCheatCmd8 ((const char*)0x014681b8)
#define gCheatCmd9 ((const char*)0x0146819c)
#define gCheatCmdA ((const char*)0x01468184)
#define gCheatCmdB ((const char*)0x01468168)
#define gCheatCmdC ((const char*)0x01468150)
#define gCheatCmdD ((const char*)0x01468134)
extern uint gCheatHandlerIds[3];  // 0x01468128

void cCheatObject::BindCheatHandlers() {
  ICheatSink* gm = (ICheatSink*)SP_GameInputManager();
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f40, gCheatCmd0);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f44, gCheatCmd1);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f41, gCheatCmd2);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f43, gCheatCmd3);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f42, gCheatCmd4);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f46, gCheatCmd5);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f47, gCheatCmd6);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f48, gCheatCmd7);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f49, gCheatCmd8);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f4a, gCheatCmd9);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f4b, gCheatCmdA);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f45, gCheatCmdB);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f4c, gCheatCmdC);
  ((void(__thiscall*)(ICheatSink*, uint, const char*))VT(gm, 0x40))(gm, 0x1f4d, gCheatCmdD);

  char* handler = (char*)this - 4;
  void* ms = SP_MessageServer();
  *(void**)((char*)this + 0x20) = ms;
  *(void**)((char*)this + 0x24) = handler;
  *(void**)((char*)this + 0x28) = (void*)&gCheatHandlerIds;
  *(uint*)((char*)this + 0x2c) = 3;
  *(uint*)((char*)this + 0x30) = 0;
  if (ms != 0 && handler != 0) {
    for (uint i = 0; i < 3; ++i)
      ((void(__thiscall*)(void*, char*, uint))VT(ms, 0x24))(ms, handler, gCheatHandlerIds[i]);
  }
}

// ===========================================================================
// @ 0x00bd6e00  cheat-mode creature commodity menu
// ===========================================================================
#define gStrSetMotive ((const wchar_t*)0x01468350)   // 0x01468350
#define gStrHappinessW ((const wchar_t*)0x01468324)  // 0x01468324
#define gStrToggleId ((const wchar_t*)0x01468300)    // 0x01468300
#define gStrMaxVehicles ((const wchar_t*)0x014682dc) // 0x014682dc

void FUN_00bd6e00(cCheatObject* obj) {
  kCityInputStrategy->Begin();
  kCityInputStrategy->AddNode(gStrSetMotive, 0x1f40, 0);
  kCityInputStrategy->AddNode(gStrHappinessW, 0x1f44, 0);
  kCityInputStrategy->AddNode(gStrToggleId, 0x1f4c, 0);
  kCityInputStrategy->AddNode(gStrMaxVehicles, 0x1f4d, 0);
  IRef* p = obj->mpDataObject;
  if (p) {
    int v = ((Fn_i_v)VT(p, 0x38))(p);
    if (v == (int)0xee9b2232)
      kCityInputStrategy->AddNode((const wchar_t*)0x014682ac, 0x1f45, 0);
  }
  kCityInputStrategy->SelectNode((SP::cSpatialObject*)obj, 0);
}

// ===========================================================================
// @ 0x00bd6eb0  set a creature-motive level across the current selection
// ===========================================================================
void __cdecl FUN_00bd6eb0(int* vec, int command, int amount) {
  switch (amount) {
    case 0x1f41: amount = 1;    break;
    case 0x1f42: amount = 0x32; break;
    case 0x1f43: amount = 100;  break;
  }

  uint i;
  if (command == 0x1f4b) {
    for (i = 0; i < (uint)((vec[1] - *vec) >> 2); i++) {
      void* e = (void*)(*(int*)(*vec + i * 4));
      FUN_00c0b9d0_hack((float)amount);
      float cur = ((float(__thiscall*)(void*))VT((char*)e + 0x5a8, 0x58))((char*)e + 0x5a8);
      FUN_00f924e0_hack(cur * ((float)amount * 0.01f));
    }
  } else {
    for (i = 0; i < (uint)((vec[1] - *vec) >> 2); i++) {
      void* e = (void*)(*(int*)(*vec + i * 4));
      switch (command) {
        case 0x1f48: {
          float cur = ((float(__thiscall*)(void*))VT((char*)e + 0x5a8, 0x58))((char*)e + 0x5a8);
          FUN_00f924e0_hack(cur * ((float)amount * 0.01f));
          break;
        }
        default:
          FUN_00c0b9d0_hack((float)amount);
          break;
      }
    }
  }
}

// ===========================================================================
// @ 0x00bd7010  cGonzagoSubsystem-derived ctor
// ===========================================================================
namespace SP {
class cGonzagoSubsystem {
 public:
  void Construct();                                 // 0x00b5b960
  char m00[0x1c];
};
}

void* __fastcall FUN_00bd7010(char* self) {
  SP::cGonzagoSubsystem* base = (SP::cGonzagoSubsystem*)(self + 4);
  *(void**)self = VT_GB1;
  base->Construct();
  *(char volatile*)(self + 0x20) = 0;
  *(void* volatile*)self = (void*)0x14683d0;
  *(void* volatile*)(self + 4) = (void*)0x1468380;
  *(void* volatile*)(self + 8) = (void*)0x146837c;
  *(uint volatile*)(self + 0x24) = 0;
  *(uint volatile*)(self + 0x28) = 0;
  *(uint volatile*)(self + 0x2c) = 0;
  *(uint volatile*)(self + 0x30) = 0;
  *(uint volatile*)(self + 0x34) = 0;
  return self;
}
