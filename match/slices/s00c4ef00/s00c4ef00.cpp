// Slice s00c4ef00 (0x00c4ef00..0x00c4fe6d) — SP::cSPMissionEradicate.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc)

#include "types.h"

typedef unsigned int  uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

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

// property object behind mp180 (vcall +0x24 yields one of these)
struct cProperty {
  char   pad00[0x12];       // +0x00..0x11
  ushort m12;               // +0x12
  char*  GetBool();         // 0x0041e920
};

// request struct handed to PickPlanet
struct PickReq {
  int    mType;             // +0x00
  int    mA4;               // +0x04
  int    mA8;               // +0x08
  char   pad0c[2];          // +0x0c..0x0d
  uchar  m0e;               // +0x0e
  void   FUN_00ba7bd0();    // 0x00ba7bd0
  void   FUN_00ba8220();    // 0x00ba8220
};

// species manager returned (as this) by GetSetting9
struct cSpeciesManager {
  void*  GetProfile(const Key& k);        // 0x004df550
};
void* __cdecl GetSetting9(const Key* k);  // 0x00401090
extern uint gKeyG1;                       // 0x016901c4
extern uint gKeyG2;                       // 0x016901c8
extern uint gKeyG3;                       // 0x016901cc

// 3-pointer string temp (begin/end/cap)
struct WStringN {
  wchar_t* mpBegin;         // +0x00
  wchar_t* mpEnd;           // +0x04
  wchar_t* mpCap;           // +0x08
};
extern wchar_t gEmpty16;                  // 0x01667bac
extern wchar_t gEmpty16b;                 // 0x01667bae

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

// target object handed to FUN_00c4f0e0 (planet/tribe record-ish)
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

struct cSPMissionEradicate : cSPMission {
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

// ---- external callees -------------------------------------------------------
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

extern float gNegOne;                                   // 0x013eb1bc (-1.0f)

// cGameNounManager-ish object returned by GetPlayerTribe
struct cTribeLike {
  void FUN_00fe5430(int a, int b);                      // 0x00fe5430
};

struct cPollinator {
  void FUN_0060d860(uint a, const void* b);             // 0x0060d860
};

// ===========================================================================
// @ 0x00c4ef00  cSPMissionEradicate::GetUIMediumDescription
// ===========================================================================
void cSPMissionEradicate::GetUIMediumDescription(void* out) {
  if (!IsActive())
    return;
  switch (mState) {
    case 0: GetText(0xd79a86a8, out); return;
    case 1: GetText(0x81128ae1, out); return;
    case 3: GetText(0xa6f2b74a, out); return;
    case 2: GetText(0xd777dfbd, out); break;
  }
}

// ===========================================================================
// @ 0x00c4ef90  cSPMissionEradicate::GetUILongDescription
// ===========================================================================
void cSPMissionEradicate::GetUILongDescription(void* out) {
  if (!IsActive())
    return;
  switch (mState) {
    case 0: GetText(0x247d8d51, out); return;
    case 1: GetText(0xba93258e, out); return;
    case 3: GetText(0x1ec90679, out); return;
    case 2: GetText(0x405a577e, out); break;
  }
}

// ===========================================================================
// @ 0x00c4f060  cSPMissionEradicate::CheckType
// ===========================================================================
char cSPMissionEradicate::CheckType() {
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

// ===========================================================================
// @ 0x00c4f0e0  cSPMissionEradicate::FUN_00c4f0e0
// ===========================================================================
float cSPMissionEradicate::FUN_00c4f0e0(cEradicateTarget* t, void* p2) {
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

// ===========================================================================
// @ 0x00c4f160  cSPMissionEradicate::FUN_00c4f160
// ===========================================================================
void cSPMissionEradicate::FUN_00c4f160() {
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

// ===========================================================================
// @ 0x00c4f220  cSPMissionEradicate::ValidateHerds
// ===========================================================================
void cSPMissionEradicate::ValidateHerds() {
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

// ===========================================================================
// @ 0x00c4f320  cSPMissionEradicate::FUN_00c4f320
// ===========================================================================
void cSPMissionEradicate::FUN_00c4f320() {
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

// ===========================================================================
// @ 0x00c4f4e0  cSPMissionEradicate::FUN_00c4f4e0
// ===========================================================================
char cSPMissionEradicate::FUN_00c4f4e0() {
  m1f8 = ((int(__thiscall*)(void*))VT(this, 0x1ac))(this);
  m204 = ((int(__thiscall*)(void*))VT(this, 0x1a8))(this);
  m20c = ((int(__thiscall*)(void*))VT(this, 0x1a4))(this);
  m1fc = ((int(__thiscall*)(void*))VT(this, 0x1b4))(this);
  m200 = ((int(__thiscall*)(void*))VT(this, 0x1b8))(this);
  m210 = 0;
  if (m204 == 0)
    m204 = m1f8;
  if (!cSPMission::Init())
    return 0;
  ((void(__thiscall*)(void*))VT(this, 0x16c))(this);
  Key k;
  k.mA = 0;
  k.mB = 0;
  k.mC = 0;
  if (SP_GetPropertyAsKey(mp180, 0x3eb161a1, &k))
    mMissionType = k.mA;
  if (mp180 != 0) {
    void* prop = 0;
    if (((bool(__thiscall*)(void*, uint, void**))VT(mp180, 0x24))(mp180, 0x7a2db2de, &prop)
        && ((cProperty*)prop)->m12 == 1)
      mBool214 = *((cProperty*)prop)->GetBool();
  }
  void* rec = GetPlanetRecordFromTargetType(ReadTargetPlanetType());
  if (rec != 0)
    FUN_00c47180(rec);
  if (((mFlags130 >> 3) & 1) != 0 && mMissionID == 0x509cc23f) {
    GetAnimalSpeciesFromType(ReadTargetAnimalSpeciesType(&mKey170));
    if (mKey170.mA == gKeyG1 && mKey170.mB == gKeyG2 && mKey170.mC == gKeyG3)
      return 0;
    mp16c = ((cSpeciesManager*)GetSetting9((Key*)&mKey170))->GetProfile(mKey170);
    if (mp16c == 0)
      return 0;
  }
  if (GetTargetPlanet() == 0) {
    PickReq req;
    req.FUN_00ba7bd0();
    req.mType = 0x38;
    if (mMissionType != 0x1e8763) {
      if (mMissionType == 0x389683f8) {
        req.m0e = 1;
        req.mA4 = req.mA8 = 2;
      }
    } else {
      req.mA4 = req.mA8 = 0x30;
    }
    void* pl = PickPlanet(&req);
    if (pl == 0) {
      req.FUN_00ba8220();
      return 0;
    }
    FUN_00c47180(pl);
    req.FUN_00ba8220();
  }
  if (mKey170.mA == gKeyG1 && mKey170.mB == gKeyG2 && mKey170.mC == gKeyG3) {
    if (!((bool(__thiscall*)(void*))VT(this, 0x18c))(this))
      return 0;
  }
  if (!((bool(__thiscall*)(void*))VT(this, 0x128))(this))
    return 0;
  FUN_00c4a0c0();
  ((void(__thiscall*)(void*))VT(this, 0x170))(this);
  return 1;
}

// ===========================================================================
// @ 0x00c4f750  cSPMissionEradicate::Update
// ===========================================================================
int cSPMissionEradicate::Update(int dt) {
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

// ===========================================================================
// @ 0x00c4f7b0  cSPMissionEradicate::Init
// ===========================================================================
void* cSPMissionEradicate::Init() {
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

// ===========================================================================
// @ 0x00c4f890  cSPMissionEradicate::GetUIShortDescription
// ===========================================================================
void cSPMissionEradicate::GetUIShortDescription(void* out) {
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

// ===========================================================================
// @ 0x00c4f960  cSPMissionEradicate::PostAlertEvent
// ===========================================================================
void cSPMissionEradicate::PostAlertEvent() {
  if (mAlertEvent != -1)
    return;
  void* log = SP_EventLog(0x6c0fa994, 0x131a9f54, 0, 0, 1, 0);
  uint id = FUN_00dd8640(log);
  mAlertEvent = id;
  mVec134.push_back(id);
}

// ===========================================================================
// @ 0x00c4f9d0  cSPMissionEradicate::PostWarningEvent
// ===========================================================================
void cSPMissionEradicate::PostWarningEvent() {
  if (mWarningEvent != -1)
    return;
  void* log = SP_EventLog(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
  uint id = FUN_00dd8640(log);
  mWarningEvent = id;
  mVec134.push_back(id);
}

// ===========================================================================
// @ 0x00c4fa40  cSPMissionEradicate::FUN_00c4fa40
// ===========================================================================
void cSPMissionEradicate::FUN_00c4fa40() {
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

// ===========================================================================
// @ 0x00c4fc00  cSPMissionEradicate::OnAbduction
// ===========================================================================
void cSPMissionEradicate::OnAbduction(void* arg) {
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