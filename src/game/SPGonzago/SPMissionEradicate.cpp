// src/game/SPGonzago/SPMissionEradicate.cpp -- migrated from slice(s) s0133ed00, s00c4fe60, s00c4ef00, s00c4dbf0, s00c4bc00 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionEradicate.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPMissionBase.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cPollinator.h"
#include "SP/cSPMission.h"
#pragma warning(disable : 4100)

// ---- items of slice s00c4bc00 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct tGridPos {
    uint32_t mA;                                        // +0x00
    uint32_t mB;                                        // +0x04
    uint32_t mC;                                        // +0x08
};
}
namespace SP {
class IProperty;
}
namespace SP {
bool __cdecl GetPropertyAsKey(IProperty* pProperty, uint32_t keyId, void* pOut); // 0x006a1250
}
namespace SP {
struct tUShortVector {
    uint16_t* mpBegin;                                  // +0x00
    uint16_t* mpEnd;                                    // +0x04
    uint16_t* mpCapacity;                               // +0x08
};
}
namespace SP {
class cSPMissionBase_s00c4_bc00 {
public:
    void SetSerializer();                               // 0x00c2e4e0
    void TriggerUIUpdate();                             // 0x00c47d80
    void FUN_00c48db0(tUShortVector* pVector);          // 0x00c48db0

    uint8_t      pad000[0x180];                         // +0x000 .. +0x17f
    IProperty*   mpMissionKey;                          // +0x180
    uint8_t      pad184[0x6c];                          // +0x184 .. +0x1ef
    int32_t      mState;                                // +0x1f0
};
}
namespace SP {
class cSPMissionEradicate : public cSPMissionBase_s00c4_bc00 {
public:
    uint32_t GetDiseaseEffectID();
};
}
// ---- items of slice s00c4bc00 end

// ---- items of slice s00c4dbf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
namespace SP {
class ThisStubs
{
  public:
    void  A();               // 0x00c48e90 cGenericPressureEvent ctor
    void  B();               // 0x00c47680 cSPMission dtor
    bool  Init();            // 0x00c4ad50
    bool  IsActive();        // 0x00c44c80
    u32   ReadTargetType();  // 0x00c45b40
    void* GetPlanetRec(int); // 0x00c474b0
    float ReadMinRange();    // 0x00c45b80
    float ReadMaxRange();    // 0x00c45bd0
    int   ReadNumJumps();    // 0x00c45c20
    int   CalcDuration();    // 0x00c45a10
    void  BaseInitA();       // 0x00c44b80
    void  BaseInitB();       // 0x00c44bd0
    void  SetSerializer();   // 0x00c2e4e0
    void  GetText(int key, void* out);   // 0x00c487d0
    void  GetUITitle(void* out);         // 0x00c48d40
    void  TriggerUIUpdate();             // 0x00c47d80
    void* PickPlanet(void* a);           // 0x00c47e20
    void* GetTargetPlanet();             // 0x00970b30
    int   Update(int a);                 // 0x00c478b0
    void  SetText(void* a);              // 0x0057cb60 eastl wstring operator=
    void  vt14c(int a);                  // mission list register
    void  vt150(int a);                  // mission list register
    void  RemoveEvent();                 // 0x00dd6d10 cSPUIEventLog::RemoveEvent
    bool  RegisterCallback();            // 0x00dd6b20 cSPUIEventLog::RegisterCallback
    void  MoveNestInit(void* a, void* b);  // 0x00c4db90
    void  PostInit();                    // 0x00c4a0c0
};
}
// ---- items of slice s00c4dbf0 end

// ---- items of slice s00c4ef00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmpty16;                  // 0x01667bac
extern wchar_t gEmpty16b;                 // 0x01667bae
extern float gNegOne;                                   // 0x013eb1bc (-1.0f)
typedef unsigned int  uint;
#define VT(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
struct Key { uint mA, mB, mC; };                    // 12 bytes
struct WString {
  wchar_t* mpBegin;         // +0x00
  wchar_t* mpEnd;           // +0x04
  void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};
struct UintVec {
  uint* mpBegin;            // +0x00
  uint* mpEnd;              // +0x04
  uint* mpCap;              // +0x08
  void DoInsertValue(uint* pos, const uint& v);       // 0x004558a0
  void push_back(const uint& v) {
    uint* end = mpEnd;
    if (end < mpCap) {
      mpEnd = end + 1;
      if (end)
        *end = v;
    } else {
      DoInsertValue(end, v);
    }
  }
};
struct PtrVec {
  void** mpBegin;           // +0x00
  void** mpEnd;             // +0x04
  void** mpCap;             // +0x08
  void   FUN_00d01790(int n);   // 0x00d01790
};
struct WStringN {
  wchar_t* mpBegin;         // +0x00
  wchar_t* mpEnd;           // +0x04
  wchar_t* mpCap;           // +0x08
};
void* __stdcall  SP_EventLog2(int a, void* b);          // 0x00b3d3e0 (2-arg form)
int   __fastcall ModifyEventText(void* log);            // 0x00dd6df0
int   __fastcall SetEventDuration(void* log);           // 0x00dd6ac0
void  __fastcall DeallocateSelf(void* ws);              // 0x00933960
void* __cdecl   FUN_00ffbe50();                         // 0x00ffbe50
void* __fastcall GetPlayerInventory(void* sim);         // 0x00a1ad60
void* __cdecl   RandomDirection3(void* out, void* inv); // 0x00b7e560
void* __fastcall GetSpeciesProfile2(void* c);           // 0x00c0bbd0
uint  __fastcall FUN_00c03180b(void* c);                // 0x00c03180
struct cGenericPressureEvent {
  void InitBase();                                    // 0x00c48e90
};
struct cSPMission : public cGenericPressureEvent {
  bool   IsActive();                                  // 0x00c44c80
  void   GetText(uint key, void* out);                // 0x00c487d0
  void   TriggerUIUpdate();                           // 0x00c47d80
  int    UpdateBase(int dt);                          // 0x00c478b0
  void*  GetTargetPlanet();                           // 0x00970b30
  bool   Init();                                      // 0x00c4ad50
  uint   ReadTargetPlanetType();                      // 0x00c45b40
  void*  GetPlanetRecordFromTargetType(uint t);       // 0x00c474b0
  uint   ReadTargetAnimalSpeciesType(Key* k);         // 0x00c45b60
  void   GetAnimalSpeciesFromType(uint t);            // 0x00c47610
  void   FUN_00c47180(void* p);                       // 0x00c47180
  void*  PickPlanet(void* req);                       // 0x00c47e20
};
struct cEradicateTarget {
  char pad00[0x2c];         // +0x0000
  uint mFlags2c;            // +0x002c
  char pad30[0xa0];         // +0x0030..0x00cf
  int  mD0;                 // +0x00d0
  int  mD4;                 // +0x00d4
};
struct RandomLCG {
  uint RandomUint32Uniform(int n);                    // 0x00a68fb0
};
struct cSPMissionEradicate_s00c4_ef00 : cSPMission {
  void*  mpVtbl0;           // +0x000
  void*  mpVtbl1;           // +0x004
  char   mPad008[0x1c];     // +0x008..0x023
  uint   mPoliticalID;      // +0x024
  char   mPad028[0x0c];     // +0x028..0x033
  void*  mpVtbl2;           // +0x034
  char   mPad038[0x40];     // +0x038..0x077
  uint   mMissionID;        // +0x078
  char   mPad07c[0xb4];     // +0x07c..0x12f
  uint   mFlags130;         // +0x130
  UintVec mVec134;          // +0x134
  char   mPad140[0x0c];     // +0x140..0x14b
  WString mDesc14c;         // +0x14c
  char   mPad154[0x18];     // +0x154..0x16b
  void*  mp16c;             // +0x16c
  Key    mKey170;           // +0x170
  void*  mp17c;             // +0x17c
  void*  mp180;             // +0x180
  char   mPad184[0x6c];     // +0x184..0x1ef
  uint   mMissionType;      // +0x1f0
  uint   mState;            // +0x1f4
  int    m1f8;              // +0x1f8
  int    m1fc;              // +0x1fc
  int    m200;              // +0x200
  int    m204;              // +0x204
  int    m208;              // +0x208
  int    m20c;              // +0x20c
  int    m210;              // +0x210
  char   mBool214;          // +0x214
  char   mPad215[3];        // +0x215..0x217
  int    mAlertEvent;       // +0x218
  int    mWarningEvent;     // +0x21c
  PtrVec mVec220;           // +0x220

  void* Init();                                       // 0x00c4f7b0
  void GetUIMediumDescription(void* out);             // 0x00c4ef00
  void GetUILongDescription(void* out);               // 0x00c4ef90
  char CheckType();                                   // 0x00c4f060
  float FUN_00c4f0e0(cEradicateTarget* t, void* p2);  // 0x00c4f0e0
  float FUN_c44d00(cEradicateTarget* t, void* p2);    // 0x00c44d00
  void  FUN_00c4f160();                               // 0x00c4f160
  void  ValidateHerds();                              // 0x00c4f220
  void  FUN_00c472e0();                                   // 0x00c472e0
  void  FUN_00c471c0();                                   // 0x00c471c0
  uint  GetDiseaseEffectID();                         // 0x00c4bd60
  void  FUN_00c4f320();                               // 0x00c4f320
  char  FUN_00c4f4e0();                               // 0x00c4f4e0
  void  FUN_00c4a0c0();                               // 0x00c4a0c0
  int   Update(int dt);                               // 0x00c4f750
  void  GetUIShortDescription(void* out);             // 0x00c4f890
  void  PostAlertEvent();                             // 0x00c4f960
  void  PostWarningEvent();                           // 0x00c4f9d0
  int   FUN_00c44c70();                               // 0x00c44c70
  void  FUN_00c4ecf0();                               // 0x00c4ecf0
  void  FUN_00c4ec90();                               // 0x00c4ec90
  void  FUN_00c4ecc0();                               // 0x00c4ecc0
  void  FUN_00c4fa40();                               // 0x00c4fa40
  void  OnAbduction(void* arg);                       // 0x00c4fc00
  void  FUN_00c48e50(void* a);                        // 0x00c48e50
};
void* __cdecl  SP_SpaceGameGet();                       // 0x01002bd0
void* __fastcall GetPlayerTribe(void* gm);              // 0x00bfc5f0
void* __cdecl FUN_0067cb30();                           // 0x0067cb30
void* __cdecl  FUN_01021240();                          // 0x01021240
void* __fastcall FUN_00bb9b80(void* s);                 // 0x00bb9b80
void* __cdecl  SP_GetUniverseContext();                 // 0x01021080
void* __cdecl  FUN_01021260();                          // 0x01021260
void  __cdecl  AddInfectedAnimalsToHerd(void*, void*, int, uint, uint);  // 0x00fefbb0
bool  __cdecl  SP_GetPropertyAsKey(void* prop, uint hash, Key* out);     // 0x006a1250
void  __cdecl  FUN_00feff80(void*, int, int, int, uint, uint, void*);    // 0x00feff80
void  __fastcall FUN_00c55ca0(void* self);              // 0x00c55ca0
void* __stdcall SP_EventLog(int, int, int, int, int, int);               // 0x00b3d3e0
int   __fastcall FUN_00dd8640(void* self);              // 0x00dd8640
void  __stdcall FUN_00d01790(int);                      // 0x00d01790
int   __fastcall FUN_00b8dab0(void* self);              // 0x00b8dab0
char  __fastcall FUN_00c46790(void* self);              // 0x00c46790
struct cTribeLike {
  void FUN_00fe5430(int a, int b);                      // 0x00fe5430
};
struct cPollinator {
  void FUN_0060d860(uint a, const void* b);             // 0x0060d860
};
// ---- items of slice s00c4ef00 end

// ---- items of slice s00c4fe60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   __cdecl FUN_00f47380(void* p);                 // operator delete
extern "C" void* __cdecl FUN_00b3d300();                        // SP_NounManager
extern "C" void* __cdecl FUN_00b3d3e0();                        // SP::EventLog getter
extern "C" void  __cdecl FUN_00aca360(void* p);
extern "C" int   __cdecl FUN_00c03180(void* p);
extern "C" void  __cdecl FUN_00c17350d(void* a, int b);         // 0x00c1735d raw 2-arg helper
extern "C" void  __cdecl FUN_00b93c60(int n, void* p);
extern "C" void* __cdecl FUN_00b21340(void* self, void* a, void* b, void* c, void* d, void* e);
extern "C" void  __cdecl FUN_00fefbb0(void* ctx, void* animal, int n, void* herd, int eff);
extern "C" void  __cdecl FUN_00e25bd0(void* begin, void* end);  // vector erase
extern "C" int   __cdecl FUN_0041e050(void* out, void* fmt, int v);          // 0x0041e050 WStr_Format
extern "C" void  __cdecl FUN_006a1250(void* a, int key, void* out);           // 0x006a1250 SP::GetPropertyAsKey
extern "C" void  __cdecl FUN_004b5ad0(void* pos, void* val);    // 0x004b5ad0 SpVector<Vector3>::DoInsertValue
extern "C" void  __cdecl FUN_00829110(void* out, void* a, void* b, void* c, void* d);  // 0x00829110
extern "C" int   __cdecl FUN_00bd8160d(void* p);                // 0x00bd8160
extern "C" void  __cdecl FUN_00bd8140d(void* p, int a);         // 0x00bd8140
extern "C" void* __cdecl FUN_00b3d480d(void* p);                // 0x00b3d480
extern "C" void* __cdecl FUN_00ae33b0d(void* p);                // 0x00ae33b0 cSPMissionBiosphere::OnAbduction
extern "C" void* __cdecl FUN_00c04590d(void* p);                // 0x00c04590 Get()
extern "C" void* __cdecl FUN_00c4bdc0v(void* out, void* vec, int v);   // 0x00c4bdc0
typedef unsigned char u8;
class Mob
{
  public:
    void* GetTargetPlanet();              // 0x00970b30 SP::cSPMission::GetTargetPlanet
    void  OnCombatantKilled(void* p);     // 0x00c4fe60
    void  OnCityDestroyed(void* p);       // 0x00c50190
    void  DestroyHerds();                 // 0x00c504a0
    void  OnPlanetDeactivate();           // 0x00c505a0
    void  OnPlanetActivate();             // 0x00c50600
    void  HandleMessage(u32 msg, void* arg);  // 0x00c4a6b0 cSPMission::HandleMessage
    int   GetTagStringBase(int tag, void* o); // 0x00c491c0 cSPMission::GetTagString
    int   GetDiseaseEffectID(int a);      // 0x00c4bd60
    void  GetText(int key, void* out);    // 0x00c487d0 SP::cSPMission::GetText
    void  TriggerUIUpdate();              // 0x00c47d80
    void  PostWarningEvent();             // 0x00c4f9d0
    void  UnkEin();                       // 0x00c4ed20
    void  UnkFfa();                       // 0x00c4fa40
    void  UnkF160();                      // 0x00c4f160
    void  UnkF320();                      // 0x00c4f320
    void  UnkFC00(void* a);               // 0x00c4fc00
    void  Unk471c0();                     // 0x00c471c0
    void  Unk472e0();                     // 0x00c472e0
    void  Unk47a10();                     // 0x00c47a10
    void  Unk48e50(int id);               // 0x00c48e50
    void  SetState(int v);                // 0x00c4eec0
    int   UnkC2b0();                      // 0x00c4c2b0
    void  BaseGetProp(void* out);          // 0x00c4bda0
    void  SerializeRecord(void* rec);     // 0x00c50ba0
    int   GetClosestDiseasedAnimalInner(void* a, void* out); // 0x00c4bdc0
    int   GetUIntField();                 // 0x008e7f80
};
class EventLog
{
  public:
    bool RegisterCallback(int id);                   // 0x00dd6b20  ret 4
    void RemoveEvent(int id, int b);                 // 0x00dd6d10  ret 8
    void ModifyEventText(int id, void* ws);          // 0x00dd6df0  ret 8
    int  AddEvent(int a, int b, int c, int d, int e, int f);  // 0x00dd8640 PostFeedbackEvent ret 0x18
};
static inline int  ld32(void* p, int off) { return *(int*)((char*)p + off); }
static inline void st32(void* p, int off, int v) { *(int*)((char*)p + off) = v; }
static inline u8   ldb(void* p, int off) { return *(u8*)((char*)p + off); }
static inline void** vtbl(void* p) { return *(void***)p; }
// ---- items of slice s00c4fe60 end

// ---- items of slice s0133ed00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (*AttrFn)();
struct Attribute {
    const char* mpName;    // +0x00  attribute name ("mHealth", ...)
    u32         mKey;      // +0x04  hashed property key
    u32         mOffset;   // +0x08  byte offset of the member in the owner
    u32         mUnk0c;    // +0x0c  uninitialised in the original
    u32         mUnk10;    // +0x10  uninitialised in the original
    u32         mUnk14;    // +0x14  uninitialised in the original
    u32         mFlags18;  // +0x18  always 0
    u32         mFlags1c;  // +0x1c  always 0
    AttrFn      mpfn20;    // +0x20  default/offset accessor (0x692ca0)
    AttrFn      mpfn24;    // +0x24  writer/reader A
    AttrFn      mpfn28;    // +0x28  writer A
    AttrFn      mpfn2c;    // +0x2c  parser/reader A
    AttrFn      mpfn30;    // +0x30  parser A
    AttrFn      mpfn34;    // +0x34  init hook (0xb1fbf0)
    AttrFn      mpfn38;    // +0x38  serialiser
};
Attribute s_diseaseAttrs[10];         // 0x015756d8
#define ATTR(dst, nm, k, off, f0, f1, f2, f3, f4, f5, f6)          \
    do {                                                           \
        Attribute t;                                               \
        t.mpName = (nm);                                           \
        t.mKey = (k);                                              \
        t.mFlags18 = 0;                                            \
        t.mFlags1c = 0;                                            \
        t.mpfn20 = (AttrFn)(f0);                                   \
        t.mpfn24 = (AttrFn)(f1);                                   \
        t.mpfn28 = (AttrFn)(f2);                                   \
        t.mpfn2c = (AttrFn)(f3);                                   \
        t.mpfn30 = (AttrFn)(f4);                                   \
        t.mpfn34 = (AttrFn)(f5);                                   \
        t.mpfn38 = (AttrFn)(f6);                                   \
        t.mOffset = (off);                                         \
        (dst) = t;                                                 \
    } while (0)
// ---- items of slice s0133ed00 end

// @ 0x00c4bd60
namespace SP {
uint32_t __thiscall cSPMissionEradicate::GetDiseaseEffectID()
{
    uint32_t effectId;
    if (mpMissionKey) {
        tGridPos key = {0, 0, 0};
        GetPropertyAsKey(mpMissionKey, 0x7a2db2dd, &key);
        effectId = key.mA;
    } else {
        effectId = 0xffffffff;
    }
    return effectId;
}
}  // namespace SP

// @ 0x00c4ed50
int __fastcall FUN_00c4ed50(void* ecx_this, void* edx)
{
    int a = *(int*)((char*)ecx_this + 0x208);
    int b = *(int*)((char*)ecx_this + 0x204);
    int ge = (a >= b) ? 1 : 0;
    int r = (ge - 1) & 0x2ee1aa4e;
    r = r + (int)0xa2b7bfa8;
    return r;
}

// @ 0x00c4ee90
int __fastcall FUN_00c4ee90(void* ecx_this, void* edx, int planet, int b)
{
    (void)b;
    if (*(int*)((char*)ecx_this + 0x1f0) == 0x1e8763) {
        int tp = (int)((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
        if (planet == tp)
            return 1;
    }
    return 0;
}

// @ 0x00c4eee0
void __fastcall FUN_00c4eee0(void* ecx_this, void* edx)
{
    int d = ((SP::ThisStubs*)ecx_this)->CalcDuration();
    *(int*)((char*)ecx_this + 0x80) = d * *(int*)((char*)ecx_this + 0x204);
}

// @ 0x00c4ef00
void cSPMissionEradicate_s00c4_ef00::GetUIMediumDescription(void* out)
{
  if (!IsActive())
    return;
  switch (mState) {
    case 0: GetText(0xd79a86a8, out); return;
    case 1: GetText(0x81128ae1, out); return;
    case 3: GetText(0xa6f2b74a, out); return;
    case 2: GetText(0xd777dfbd, out); break;
  }
}

// @ 0x00c4ef90
void cSPMissionEradicate_s00c4_ef00::GetUILongDescription(void* out)
{
  if (!IsActive())
    return;
  switch (mState) {
    case 0: GetText(0x247d8d51, out); return;
    case 1: GetText(0xba93258e, out); return;
    case 3: GetText(0x1ec90679, out); return;
    case 2: GetText(0x405a577e, out); break;
  }
}

// @ 0x00c4f060
char cSPMissionEradicate_s00c4_ef00::CheckType()
{
  if (mMissionType == 0x389683f8) {
    if (mMissionID == 0x509cc23f && mp17c) {
      void* q = ((void*(__thiscall*)(void*, uint))VT(mp17c, 0xc))(mp17c, 0x422227d);
      if (q) {
        void* r = ((void*(__thiscall*)(void*))VT(q, 0xb0))(q);
        mp16c = r;
        if (r) {
          mKey170 = *(Key*)((char*)r + 0x504);
          return 1;
        }
      }
    }
    return FUN_00c46790(this);
  }
  return 1;
}

// @ 0x00c4f0e0
float cSPMissionEradicate_s00c4_ef00::FUN_00c4f0e0(cEradicateTarget* t, void* p2)
{
  float r = FUN_c44d00(t, p2);
  if (r <= 0.0f)
    return r;
  if (mMissionType != 0x1e8763) {
    if (mMissionType == 0x389683f8) {
      if (t->mD0 == t->mD4 || (t->mFlags2c & 0x800) != 0)
        return gNegOne;
    }
  } else {
    int k = FUN_00b8dab0(t);
    if (k != 4 && k != 5)
      return gNegOne;
  }
  return 1.0f;
}

// @ 0x00c4f160
void cSPMissionEradicate_s00c4_ef00::FUN_00c4f160()
{
  if (mState != 0)
    return;
  ((void(__thiscall*)(void*))VT(this, 0x6c))(this);
  if (mState != 1) {
    mState = 1;
    TriggerUIUpdate();
  }
  FUN_00c472e0();
  FUN_00c471c0();
  void* t = GetPlayerTribe(SP_SpaceGameGet());
  if (t)
    ((cTribeLike*)t)->FUN_00fe5430(8, 1);
  if (mMissionType == 0x389683f8) {
    ((cPollinator*)FUN_0067cb30())->FUN_0060d860(0xbe96cd0, (char*)mp16c + 0x504);
    return;
  }
  if (mMissionType == 0x1e8763) {
    void* v = FUN_00bb9b80(FUN_01021240());
    ((cPollinator*)FUN_0067cb30())->FUN_0060d860(0xbe96cd0, v);
  }
}

// @ 0x00c4f220
void cSPMissionEradicate_s00c4_ef00::ValidateHerds()
{
  if (mMissionType != 0x389683f8)
    return;
  if (SP_GetUniverseContext() != 0)
    return;
  void* target = GetTargetPlanet();
  if (FUN_01021260() != target)
    return;
  void** it = mVec220.mpBegin;
  void** end = mVec220.mpEnd;
  int count = 0;
  for (; it != end; ++it) {
    char* obj = (char*)*it;
    uint* b = *(uint**)(obj + 0x40);
    uint* e = *(uint**)(obj + 0x44);
    for (; b != e; ++b) {
      char* c = (char*)*b;
      if (c[0xb62] != 0 && c[0xb5e] == 0)
        count++;
    }
  }
  int need = ((int(__thiscall*)(void*))VT(this, 0x1b0))(this);
  if (count >= need)
    return;
  if (mVec220.mpBegin == mVec220.mpEnd)
    return;
  int total = ((int(__thiscall*)(void*))VT(this, 0x1b0))(this);
  int n = (int)(mVec220.mpEnd - mVec220.mpBegin);
  uint idx = ((RandomLCG*)0x1601760)->RandomUint32Uniform(n);
  void* elem = mVec220.mpBegin[idx];
  uint disease = GetDiseaseEffectID();
  AddInfectedAnimalsToHerd(mp16c, elem, total - count, mPoliticalID, disease);
}

// @ 0x00c4f320
void cSPMissionEradicate_s00c4_ef00::FUN_00c4f320()
{
  int n = ((int(__thiscall*)(void*))VT(this, 0x1b0))(this);
  if (n <= 0)
    return;
  uint key;
  if (mp180 != 0) {
    Key k;
    k.mA = 0;
    k.mB = 0;
    k.mC = 0;
    SP_GetPropertyAsKey(mp180, 0x7a2db2dd, &k);
    key = k.mA;
  } else {
    key = 0xffffffff;
  }
  FUN_00feff80(mp16c, n, m1fc, m200, mPoliticalID, key, &mVec220);
}

// @ 0x00c4f750
int cSPMissionEradicate_s00c4_ef00::Update(int dt)
{
  int r = UpdateBase(dt);
  if (r == 3 && mState == 0) {
    if (mMissionID != 0x509cc23f) {
      ValidateHerds();
      return r;
    }
    void* p = mp17c;
    if (p) {
      void* q = ((void*(__thiscall*)(void*, uint))VT(p, 0xc))(p, 0x422227d);
      if (q)
        FUN_00c55ca0(q);
    }
  }
  return r;
}

// @ 0x00c4f7b0
void* cSPMissionEradicate_s00c4_ef00::Init()
{
  InitBase();
  mState = 0;
  mMissionType = -1;
  mAlertEvent = -1;
  mWarningEvent = -1;
  mpVtbl0 = (void*)0x146e248;
  mpVtbl1 = (void*)0x146e238;
  mpVtbl2 = (void*)0x146e228;
  m1f8 = 0;
  m204 = 0;
  m208 = 0;
  m20c = 0;
  m210 = 0;
  mBool214 = 1;
  PtrVec& v = mVec220;
  v.mpBegin = 0;
  v.mpEnd = 0;
  v.mpCap = 0;
  mVec220.FUN_00d01790(10);
  return this;
}

// @ 0x00c4f890
void cSPMissionEradicate_s00c4_ef00::GetUIShortDescription(void* out)
{
  WString* self = &mDesc14c;
  if (mDesc14c.mpBegin == mDesc14c.mpEnd) {
    switch (mState) {
      case 0: GetText(0xaad9c0b3, out); break;
      case 1: GetText(0x4e1f8fa8, out); break;
      case 2: GetText(0xb4dfecf, out); break;
      case 3: GetText(0xa5ed0254, out); break;
    }
    if (out != self)
      self->assign(((WString*)out)->mpBegin, ((WString*)out)->mpEnd);
  } else {
    if (out != self)
      ((WString*)out)->assign(mDesc14c.mpBegin, mDesc14c.mpEnd);
  }
}

// @ 0x00c4f960
void cSPMissionEradicate_s00c4_ef00::PostAlertEvent()
{
  if (mAlertEvent != -1)
    return;
  void* log = SP_EventLog(0x6c0fa994, 0x131a9f54, 0, 0, 1, 0);
  uint id = FUN_00dd8640(log);
  mAlertEvent = id;
  mVec134.push_back(id);
}

// @ 0x00c4f9d0
void cSPMissionEradicate_s00c4_ef00::PostWarningEvent()
{
  if (mWarningEvent != -1)
    return;
  void* log = SP_EventLog(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
  uint id = FUN_00dd8640(log);
  mWarningEvent = id;
  mVec134.push_back(id);
}

// @ 0x00c4fa40
void cSPMissionEradicate_s00c4_ef00::FUN_00c4fa40()
{
  if (FUN_00c44c70() != 3)
    return;
  if (SP_GetUniverseContext() != 0)
    return;
  switch (mState) {
    case 0: {
      int n = m20c - m210;
      if (n > 3 || n < 1)
        return;
      WStringN s;
      s.mpBegin = &gEmpty16;
      s.mpEnd = &gEmpty16;
      s.mpCap = &gEmpty16b;
      GetText(0xbf13693a, &s);
      FUN_00c4ecf0();
      PostAlertEvent();
      void* log = SP_EventLog2(mAlertEvent, s.mpBegin);
      ModifyEventText(log);
      log = SP_EventLog2(mAlertEvent, (void*)0xbf800000);
      SetEventDuration(log);
      DeallocateSelf(&s);
      return;
    }
    case 1:
      FUN_00c4ec90();
      FUN_00c4ecc0();
      return;
    case 2: {
      WStringN s;
      s.mpBegin = &gEmpty16;
      s.mpEnd = &gEmpty16;
      s.mpCap = &gEmpty16b;
      GetText(0xc4deccc8, &s);
      PostAlertEvent();
      void* log = SP_EventLog2(mAlertEvent, s.mpBegin);
      ModifyEventText(log);
      log = SP_EventLog2(mAlertEvent, (void*)0xbf800000);
      SetEventDuration(log);
      FUN_00c4ecc0();
      DeallocateSelf(&s);
      return;
    }
    case 3: {
      WStringN s;
      s.mpBegin = &gEmpty16;
      s.mpEnd = &gEmpty16;
      s.mpCap = &gEmpty16b;
      GetText(0xa2c33a6e, &s);
      PostAlertEvent();
      void* log = SP_EventLog2(mAlertEvent, s.mpBegin);
      ModifyEventText(log);
      log = SP_EventLog2(mAlertEvent, (void*)0xbf800000);
      SetEventDuration(log);
      FUN_00c4ecc0();
      DeallocateSelf(&s);
      return;
    }
  }
}

// @ 0x00c4fc00
void cSPMissionEradicate_s00c4_ef00::OnAbduction(void* arg)
{
  if (GetTargetPlanet() != FUN_01021260())
    return;
  if (mMissionType == 0x1e8763) {
    if (arg == 0)
      return;
    void* c = ((void*(__thiscall*)(void*, uint))VT(arg, 0xc))(arg, 0x4f176642);
    if (c == 0)
      return;
    WStringN s;
    s.mpBegin = &gEmpty16;
    s.mpEnd = &gEmpty16;
    s.mpCap = &gEmpty16b;
    uint h = (*(char*)((char*)c + 0xb62) != 0) ? 0x0325959a : 0x2e555b9b;
    GetText(h, &s);
    void* ev = SP_EventLog(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
    int fb = FUN_00dd8640(ev);
    void* log = SP_EventLog2(fb, s.mpBegin);
    ModifyEventText(log);
    FUN_00c48e50((void*)fb);
    void* inv = GetPlayerInventory(FUN_00ffbe50());
    void* pbase = (inv == 0) ? 0 : (void*)((char*)inv + 0x508);
    void* pl = (void*)((char*)c + 0x5a8);
    float dir[3];
    RandomDirection3(dir, pbase);
    int r = ((int(__thiscall*)(void*, int, int, void*))VT(pl, 0x58))(pl, -1, 0, dir);
    ((void(__thiscall*)(void*, float))VT(pl, 0x18))(pl, (float)r);
    DeallocateSelf(&s);
    return;
  }
  if (mMissionType != 0x389683f8)
    return;
  if (arg == 0)
    return;
  void* c = ((void*(__thiscall*)(void*, uint))VT(arg, 0xc))(arg, 0xd0036e08);
  if (c == 0)
    return;
  if (GetSpeciesProfile2(c) != mp16c)
    return;
  if (FUN_00c03180b(c) != mPoliticalID)
    return;
  WStringN s;
  s.mpBegin = &gEmpty16;
  s.mpEnd = &gEmpty16;
  s.mpCap = &gEmpty16b;
  uint h = (*(char*)((char*)c + 0xb62) != 0) ? 0x0325959a : 0x2e555b9b;
  GetText(h, &s);
  void* ev = SP_EventLog(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
  int fb = FUN_00dd8640(ev);
  void* log = SP_EventLog2(fb, s.mpBegin);
  ModifyEventText(log);
  FUN_00c48e50((void*)fb);
  void* inv = GetPlayerInventory(FUN_00ffbe50());
  void* pbase = (inv == 0) ? 0 : (void*)((char*)inv + 0x508);
  void* pl = (void*)((char*)c + 0x5a8);
  float dir[3];
  RandomDirection3(dir, pbase);
  int r = ((int(__thiscall*)(void*, int, int, void*))VT(pl, 0x58))(pl, -1, 0, dir);
  ((void(__thiscall*)(void*, float))VT(pl, 0x18))(pl, (float)r);
  DeallocateSelf(&s);
}

// @ 0x00c50190
void __fastcall FUN_00c50190(void* ecx_this, void* edx, void* arg)
{
    (void)edx; (void)arg;
    Mob* self = (Mob*)ecx_this;
    if (ldb(ecx_this, 0x214) == 0)
        return;
    int v = ld32(ecx_this, 0x20c);
    void** vtp = vtbl(ecx_this);
    st32(ecx_this, 0x210, v);
    (*(void (__thiscall**)(void*))((char*)vtp + 0x70))(ecx_this);
    if (ld32(ecx_this, 0x1f4) != 2) {
        st32(ecx_this, 0x1f4, 2);
        self->TriggerUIUpdate();
    }
    self->Unk472e0();
    self->UnkFfa();
}

// @ 0x00c501e0
char __fastcall FUN_00c501e0(void* ecx_this, void* edx, int tag, void* out)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    if (tag == 0x3f80b6b3) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x1f8));
        return 1;
    }
    if (tag == (int)0xcd3e21a2) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x208));
        return 1;
    }
    if (tag == (int)0xc1a31746) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x1f8) - ld32(ecx_this, 0x208));
        return 1;
    }
    if (tag == (int)0xd34ef208) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x210));
        return 1;
    }
    if (tag == (int)0xbd31ee03) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x20c) - ld32(ecx_this, 0x210));
        return 1;
    }
    if (tag == 0x218e9bda) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x204) - ld32(ecx_this, 0x208));
        return 1;
    }
    if (tag == (int)0x85df68ab) {
        FUN_0041e050(out, (void*)0x13f01bc, ld32(ecx_this, 0x204));
    }
    return (char)self->GetTagStringBase(tag, out);
}

// @ 0x00c50300
char __fastcall FUN_00c50300(void* ecx_this, void* edx, void* param_2, void* outVec)
{
    (void)edx;
    int* pList;
    void* p = (void*)ld32(ecx_this, 0x17c);
    if (p && (pList = (int*)(*(void* (__thiscall**)(void*, u32))((char*)vtbl(p) + 0xc))(p, 0x4222277u)) != 0)
        pList = (int*)((char*)pList + 0x240);
    else
        pList = (int*)((char*)ecx_this + 0x220);
    int count = (int)(((char*)pList[1] - (char*)pList[0]) >> 2);
    void* v_begin = 0;
    void* v_end = 0;
    void* v_cap = 0;
    int i = 0;
    if (count > 0) {
        do {
            int sub = *(int*)(pList[0] + i * 4);
            int n = (int)((*(int*)(sub + 0x44) - *(int*)(sub + 0x40)) >> 2);
            int j = 0;
            if (n > 0) {
                do {
                    void* a = *(void**)(*(int*)(sub + 0x40) + j * 4);
                    if (ldb(a, 0xb62) != 0 && ldb(a, 0xb5e) == 0) {
                        void* pos = (*(void* (__thiscall**)(void*))((char*)vtbl((void*)((char*)a + 0xc0)) + 0x2c))((char*)a + 0xc0);
                        if (v_begin < v_cap) {
                            v_end = (char*)v_end + 12;
                            if (v_begin) {
                                *(int*)v_begin = *(int*)pos;
                                *((int*)v_begin + 1) = *((int*)pos + 1);
                                *((int*)v_begin + 2) = *((int*)pos + 2);
                            }
                        } else {
                            FUN_004b5ad0(v_end, pos);
                        }
                    }
                    j++;
                } while (j < n);
            }
            i++;
        } while (i < count);
    }
    char b = (v_begin != v_end);
    if (b) {
        int* r = (int*)FUN_00c4bdc0v((char*)outVec - 12, &v_begin, (int)param_2);
        *(int*)outVec = r[0];
        *((int*)outVec + 1) = r[1];
        *((int*)outVec + 2) = r[2];
    }
    if (v_begin && *(int*)((char*)v_begin - 4) != 0)
        FUN_00f47380(v_begin);
    return b;
}

// @ 0x00c50460
void __fastcall FUN_00c50460(void* ecx_this, void* edx)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    if (ldb(ecx_this, 0x214) == 0)
        return;
    if (ld32(ecx_this, 0x1f4) != 0)
        return;
    st32(ecx_this, 0x1f4, 3);
    self->TriggerUIUpdate();
    self->Unk472e0();
    self->UnkFfa();
    self->Unk471c0();
}

// @ 0x00c504a0
void __fastcall FUN_00c504a0(void* ecx_this, void* edx)
{
    (void)edx;
    FUN_00b3d300();
    int eff;
    if (ld32(ecx_this, 0x180)) {
        int local = 0;
        FUN_006a1250((void*)ld32(ecx_this, 0x180), 0x7a2db2dd, &local);
        eff = local;
    } else {
        eff = -1;
    }
    int* begin = (int*)*(int*)((char*)ecx_this + 0x220);
    int* end = (int*)*(int*)((char*)ecx_this + 0x224);
    if (begin != end) {
        do {
            int sub = *begin;
            int n = (int)((*(int*)(sub + 0x44) - *(int*)(sub + 0x40)) >> 2);
            int j = 0;
            if (n > 0) {
                do {
                    void* a = *(void**)(*(int*)(sub + 0x40) + j * 4);
                    if (a && FUN_00c03180(a) == ld32(ecx_this, 0x204)) {
                        FUN_00c17350d(a, eff + 1);
                        FUN_00aca360(FUN_00b3d480d(a));
                    }
                    j++;
                } while (j < n);
            }
            begin++;
        } while (begin != end);
    }
    FUN_00e25bd0((void*)*(int*)((char*)ecx_this + 0x220), (void*)*(int*)((char*)ecx_this + 0x224));
}

// @ 0x00c505a0
void __fastcall FUN_00c505a0(void* ecx_this, void* edx)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    if (ld32(ecx_this, 0x78) != 0x509cc23f)
        self->DestroyHerds();
    int id = ld32(ecx_this, 0x218);
    if (id != -1) {
        ((EventLog*)FUN_00b3d3e0())->RemoveEvent(id, 0);
        st32(ecx_this, 0x218, -1);
    }
    int id2 = ld32(ecx_this, 0x21c);
    if (id2 != -1) {
        ((EventLog*)FUN_00b3d3e0())->RemoveEvent(id2, 0);
        st32(ecx_this, 0x21c, -1);
    }
}

// @ 0x00c50600
void __fastcall FUN_00c50600(void* ecx_this, void* edx)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    int owner = ld32(ecx_this, 0x1f0);
    if (owner == 0x1e8763) {
        void* mgr = FUN_00b3d300();
        void* vec = (void*)FUN_00b21340(mgr, (void*)0xcd7d10, (void*)0xd3d420,
                                        (void*)0xacdff0, (void*)0xb1e500, (void*)0x18c43e8);
        int cnt = (int)((*(int*)((char*)vec + 8) - *(int*)((char*)vec + 4)) >> 2);
        FUN_00b93c60(cnt, (char*)vec + 0x10);
        int local[3] = {0, 0, 0};
        FUN_00829110(local, *(void**)((char*)vec + 4), *(void**)((char*)vec + 8), 0, 0);
        int n = (int)(((char*)local[1] - (char*)local[0]) >> 2);
        int avail = ld32(ecx_this, 0x1f8) - ld32(ecx_this, 0x208);
        if (n > 0 && avail > 0) {
            int cnt2 = 0;
            do {
                int j = 0;
                if (n > 0) {
                    cnt2 += n;
                    do {
                        void* a = ((void**)local[0])[j];
                        FUN_00bd8140d(a, FUN_00bd8160d(a) + 1);
                        j++;
                    } while (j < n);
                }
            } while (cnt2 < avail);
            self->UnkFfa();
        }
        int* pi = (int*)local[0];
        int* pe = (int*)local[1];
        for (; pi < pe; pi++)
            if (*pi)
                (*(void (__thiscall**)(int))((char*)vtbl((void*)*pi) + 4))(*pi);
        if (local[0] && *(int*)((char*)local[0] - 4) != 0)
            FUN_00f47380((void*)local[0]);
    } else if (owner == 0x389683f8) {
        if (ld32(ecx_this, 0x78) != 0x509cc23f)
            self->UnkF320();
    }
}

// @ 0x00c50740
void __fastcall FUN_00c50740(void* ecx_this, void* edx, u32 msg, void* arg)
{
    (void)edx;
    Mob* self = (Mob*)ecx_this;
    if (msg <= 0x3029f11u) {
        if (msg == 0x3029f11u) {
            void* tp = self->GetTargetPlanet();
            void* ap = FUN_01021260();
            if (ap == tp) {
                void* p = *(void**)((char*)arg + 8);
                if (!p)
                    self->UnkFC00(0);
                else {
                    void* v = (*(void* (__thiscall**)(void*, u32))((char*)vtbl(p) + 8))(p, 0xce9f6639u);
                    self->UnkFC00(v);
                }
            }
        } else if (msg == 0x1622184u) {
            void* tp = self->GetTargetPlanet();
            void* ap = FUN_01021260();
            if (ap == tp) {
                void* p = *(void**)((char*)arg + 8);
                void* q = *(void**)((char*)arg + 0x10);
                if (((Mob*)p)->GetUIntField() == 2) {
                    int o = ld32(ecx_this, 0x1bc);
                    if (o == 0x1e8763) {
                        self->OnCombatantKilled(p);
                    } else if (o == 0x389683f8) {
                        if (q && (*(void* (__thiscall**)(void*, u32))((char*)vtbl(q) + 0x5c))(q, 0xd0036e08u)) {
                            void* ani = FUN_00ae33b0d(p);
                            if (ani && ldb(ani, 0xb62) != 0) {
                                if (FUN_00c03180(ani) == ld32(ecx_this, 0x1e0)) {
                                    void* herd = FUN_00c04590d(ani);
                                    if (herd) {
                                        int eff = self->GetDiseaseEffectID(0);
                                        FUN_00fefbb0((void*)ld32(ecx_this, 0x138), herd, 1,
                                                     (void*)ld32(ecx_this, 0x1e0), eff);
                                    }
                                }
                            }
                        } else {
                            self->OnCombatantKilled(p);
                        }
                    }
                }
            }
        } else if (msg == 0x2489760u) {
            void* tp = self->GetTargetPlanet();
            if (*(int*)((char*)arg + 8) == (int)tp)
                self->OnPlanetDeactivate();
        }
    } else if (msg == 0x3337cbbu) {
        if (ld32(ecx_this, 0x1c0) == 0) {
            void* tp = self->GetTargetPlanet();
            void* ap = FUN_01021260();
            if (ap == tp) {
                void* p = *(void**)((char*)arg + 8);
                if (p) {
                    void* v = (*(void* (__thiscall**)(void*, u32))((char*)vtbl(p) + 0xc))(p, 0xee9b2232u);
                    if (v)
                        self->OnCityDestroyed(v);
                }
            }
        }
    } else if (msg == 0x5e37a53u) {
        void* ap = FUN_01021260();
        void* tp = self->GetTargetPlanet();
        if (ap == tp)
            self->OnPlanetActivate();
    }
    self->HandleMessage(msg, arg);
}

// @ 0x01340070
void FUN_01340070()
{
    ATTR(s_diseaseAttrs[0], "mEradicateType", 0x3852fb1, 0x1f0,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[1], "mEradicateMissionState", 0x3852fb2, 0x1f4,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[2], "mMaxNumDiseasedCreatures", 0x3852fb3, 0x1f8,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[3], "mNumDiseasedKills", 0x3852fb4, 0x208,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[4], "mMaxNumHealthyKills", 0x3852fb5, 0x20c,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[5], "mNumHealthyKills", 0x3852fb6, 0x210,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[6], "mTotalNumKillsNeeded", 0x3852fb7, 0x204,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[7], "mMinDiseasedPerHerd", 0x3852fb8, 0x1fc,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[8], "mMaxDiseasedPerHerd", 0x3852fb9, 0x200,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[9], "mCanFail", 0x3852fba, 0x214,
         0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00);
}
