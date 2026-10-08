// Slice s00be88d0: cCity::ChangeCivilization (0xbe88d0, 2428 bytes)
//
// this = cCity (retail layout, see ModAPI cCity.h: +0x29c city type 0/1/2, +0x33c mbIsPlayerCity,
// +0x590 mpCivilization). The city is handed to civilization `newId` (arg1): the old civilization
// is held (AddRef) for the whole call, the city counters of both civilizations are updated, the
// city-type specific tutorial / achievement / audio hooks run in civ mode (0x1654c04), culture
// targets are refreshed and a message (id 0x164b4eb) is posted.
#include "types.h"
#include <intrin.h>

struct Vec3 {
  float x, y, z;
  Vec3() {}
  Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct ResKey { uint32_t a, b, c; ResKey() : a(0), b(0), c(0) {} };

struct City;
struct Civ;

struct VecPtr { char* begin; char* end; };

struct Profile { uint32_t pad[0x141]; };   // object at civ->bef950(); +0x504 is the key field

struct Partner12 { uint32_t a, b, c; };

struct Timer {
  void Restart();                           // 0xbc3130
};

struct NameSub {                            // city+0x34 sub-object
  virtual void s0();
  virtual const wchar_t* GetName();        // vt+4
};

struct SpatialSub {                         // city+0x120 sub-object
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
  virtual void s8(); virtual void s9(); virtual void s10();
  virtual Vec3* GetPosition();              // vt+0x2c
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
  virtual void s20(); virtual void s21();
  virtual bool Query58();                   // vt+0x58
};

struct CulTarget {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
  virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17();
  virtual void Notify(int a);               // vt+0x48
};

struct Civ3c { int f0; int f4; int B6f310(); };   // civ+0x3c sub-object; 0xb6f310 is its method

struct Civ {
  virtual void AddRef();                    // vt+0
  virtual void Release();                   // vt+4
  virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
  virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
  virtual bool Query2c();                   // vt+0x2c
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18();
  virtual int GetID();                      // vt+0x4c
  uint32_t pad04[14];
  Civ3c sub3c;                              // +0x3c
  uint32_t pad44[(0x9c - 0x44) / 4];
  VecPtr vec9c;                             // +0x9c
  uint32_t pada4[(0x4c0 - 0xa4) / 4];
  int cnt4c0, cnt4c4, cnt4c8;               // +0x4c0 city counts by type
  void F_bf45f0(City* c, int z);            // 0xbf45f0 ret 8
  void F_bf4370(City* c);                   // 0xbf4370 ret 4
  void F_bf0b00(City* c);                   // 0xbf0b00 ret 4
  void F_bf0be0(City* c);                   // 0xbf0be0 ret 4
  void F_bf0b70(City* c);                   // 0xbf0b70 ret 4
  int  F_bf0f40();                          // 0xbf0f40
  int  F_bf01e0();                          // 0xbf01e0
  Civ3c* GetSub() { return &sub3c; }
  Profile* GetProfile();                    // 0xbef950
  VecPtr* GetVec();                         // 0xbef6c0 (this+0x9c)
};

struct NounMgr {
  Civ* GetCivById(int id);                  // 0xb25f40 ret 4
  Civ* GetPlayerCivilization();             // 0xb25fb0
  VecPtr* GetAll();                         // 0xb25ca0
};
struct RelMgr { int Relation(int a, int b, int c); };       // 0xd00a70 ret 0xc
struct EvLog { void RemoveAllEventsOfSameType(uint32_t a, uint32_t b, uint32_t c); };   // 0xdd7620 ret 0xc
struct CivStrategy {
  void DoNextCivTutorial(uint32_t id, int f);               // 0xcfa990 ret 8
  bool CanBuildSeaVehicles();                               // 0xcf75d0
  void DoCVGCompletionAchievements();                       // 0xcf7630
  void F_cf9ba0();                                          // 0xcf9ba0
};
struct MsgServer {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
  virtual void Post(uint32_t id, uint32_t arg, int flag);   // vt+0x14
};
struct MsgServer2 {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
  virtual void Post(uint32_t id, void* msg, int flag);      // vt+0x14
};
struct AudioSys {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
  virtual void* Get20();                                    // vt+0x20
};
struct Effect {
  void* pad[3];
  struct { uint32_t pad[9]; uint32_t f24; }* inner;         // +0xc
  void F_7eb820(int a);                                     // ret 4
};
struct EffMgr { Effect* Spawn(int kind, Vec3 pos); };       // 0xae37c0 ret 0x10
struct Planet {
  void F_b7e4b0();                                          // 0xb7e4b0
  int  F_b7ea80(Vec3* p);                                   // ret 4
  void F_b841a0(int a, int b, City* c);                     // ret 0xc
};
struct PropSink { void F_60f370(uint32_t id, void* key, int a, int b); };   // ret 0x10
struct UiCtl { void F_ac8cd0(City* c, int a); bool F_ac8d60(City* c); };
struct UiSt { uint32_t pad[0xb]; int f2c; };
struct RandLC { int RandomUint32Uniform(int n); };          // 0xa68fb0 ret 4

struct City {
  uint32_t pad00[13];
  NameSub name;                              // +0x34
  uint32_t pad38[(0x120 - 0x38) / 4];
  SpatialSub spatial;                        // +0x120
  uint32_t pad124[(0x29c - 0x124) / 4];
  int type;                                  // +0x29c
  uint8_t b2a0; uint8_t pad2a1[0x3f];        // +0x2a0
  uint8_t b2e0, b2e1, b2e2, b2e3, b2e4, b2e5, b2e6; uint8_t pad2e7[0x33c - 0x2e7];
  uint8_t bIsPlayer;                         // +0x33c
  uint8_t pad33d[0x518 - 0x33d];
  uint8_t b518; uint8_t pad519[0x540 - 0x519];
  int vehSpec;                               // +0x540
  uint32_t pad544[(0x55c - 0x544) / 4];
  Partner12* partnersBegin;                  // +0x55c
  Partner12* partnersEnd;                    // +0x560
  uint32_t pad564[(0x58c - 0x564) / 4];
  uint8_t b58c; uint8_t pad58d[3];
  Civ* civ;                                  // +0x590
  uint32_t pad594[(0x618 - 0x594) / 4];
  char* cultureInfo;                         // +0x618
  uint32_t pad61c[(0x62c - 0x61c) / 4];
  CulTarget** targetsBegin;                  // +0x62c
  CulTarget** targetsEnd;                    // +0x630
  uint32_t pad634[(0x6c0 - 0x634) / 4];
  uint8_t b6c0; uint8_t pad6c1[7];
  Timer timer6c8;                            // +0x6c8
  uint8_t pad6c9[0x762 - 0x6c9];
  uint8_t b762;

  void ChangeCivilization(int newId, bool arg2, bool arg3);   // 0xbe88d0 ret 0xc
  void F_bd8fe0(int a, int b);               // ret 8
  void F_be73d0(int a, int b);               // ret 8
  void F_be4b30(Civ* c);                     // ret 4
  void F_bd9ed0(int i);                      // ret 4
  void F_bd9060(Civ* c);                     // ret 4
  City* F_bdf9e0(int id);                    // ret 4
  void F_bdb0b0();
};

NounMgr* NounManager();                     // 0xb3d300
RelMgr* RelationshipManager();              // 0xb3d2c0
uint32_t GetCurrentGameMode();              // 0xb5b800
EvLog* EventLog();                          // 0xb3d3e0
MsgServer* MessageServer();                 // 0x67dcc0
CivStrategy* CivStrategyGet();              // 0xcf74c0
AudioSys* GetSystemAT();                    // 0xa206f0
Planet* PlanetModel();                      // 0xb3d350
UiCtl* GetUiCtl();                          // 0xb3d480
UiSt* GetUiSt();                            // 0xb3d4d0
MsgServer2* GetMessagingServer();            // 0x883860
EffMgr* GetEffMgr();                        // 0xb26930
PropSink* GetPropSink();                    // 0x67cb30
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int f);   // 0x932f30 cdecl
int Fn_bef920(int a);                       // cdecl
void Fn_435ed0(uint32_t id, void* p);       // cdecl
void Fn_e3c7c0(uint32_t ev, void* pa, void* pb, ResKey* k, int a, int b, int c);   // cdecl
extern RandLC sMathRandom;                  // 0x1601760

struct Msg {                                // 0x40-byte stack message (MessageBasicRC<5>-like)
  uint32_t w[16];
};
extern char vtbl_BehaviorMessage[];         // 0x13eb90c
extern char vtbl_MessageBasicRC5[];         // 0x13eb844
extern char vtbl_LocaleChangeMessage[];     // 0x13eb918

static __forceinline void KillAudio(uint32_t id) {
  AudioSys* at = GetSystemAT();
  void* r = at ? at->Get20() : 0;
  Fn_435ed0(id, r);
}

static __forceinline void PostCivEvent(uint32_t ev, Civ* oldCiv, ResKey& k) {
  int idOld = oldCiv->sub3c.f4;
  Civ3c* ps = NounManager()->GetPlayerCivilization()->GetSub();
  int idPlayer = ps->f4;
  k.a = k.b = k.c = 0;
  Fn_e3c7c0(ev, (char*)NounManager()->GetPlayerCivilization()->GetProfile() + 0x504,
            (char*)oldCiv->GetProfile() + 0x504, &k, idPlayer, idOld, 0);
}

// @ 0x00be88d0  (2428 bytes)
void City::ChangeCivilization(int newId, bool arg2, bool arg3) {
  Civ* oldCiv = civ;
  b2e0 = 0;
  if (oldCiv) oldCiv->AddRef();
  Civ* newCiv = NounManager()->GetCivById(newId);
  int oldId = civ->GetID();
  SpatialSub* sp = &spatial;
  bool wasPlayer = sp->Query58();
  bool bNew = (newCiv == NounManager()->GetPlayerCivilization());
  bool bRel = RelationshipManager()->Relation(oldId, newId, 1) <= 1;
  if (GetCurrentGameMode() == 0x1654c05) F_bd8fe0(oldId, newId);
  oldCiv->F_bf45f0(this, 0);
  newCiv->F_bf4370(this);
  switch (type) {
    case 0: newCiv->cnt4c0++; break;
    case 1: newCiv->cnt4c4++; break;
    case 2: newCiv->cnt4c8++; break;
  }
  bIsPlayer = bNew;
  if (bNew) b518 = 1; else b58c = 0;
  if (GetCurrentGameMode() == 0x1654c04) {
    uint32_t h = FNV1_String16(name.GetName(), 0x811c9dc5, 1);
    EventLog()->RemoveAllEventsOfSameType(0x38320b95, 0, h);
    if (wasPlayer) {
      if (!bNew && !oldCiv->Query2c()) newCiv->F_bf0b00(this);
    } else if (bNew) {
      MessageServer()->Post(0x6579712, 0x2887b6de, 0);
      if (!oldCiv->Query2c()) {
        if (type == 0 || type == 1) newCiv->F_bf0be0(this);
      }
    } else {
      newCiv->F_bf0b70(this);
    }
    if (!bIsPlayer) {
      int n = newCiv->F_bf0f40();
      if (n != 1 || sMathRandom.RandomUint32Uniform(100) < 0x32)
        F_be73d0(Fn_bef920(newCiv->F_bf0f40()), 0);
      if (wasPlayer) {
        Effect* e = GetEffMgr()->Spawn(7, *sp->GetPosition());
        e->F_7eb820(10);
        e->inner->f24 = vehSpec;
        goto audio;
      }
    } else {
      Effect* e;
      int idx;
      switch (type) {
        case 0:
          e = GetEffMgr()->Spawn(3, *sp->GetPosition());
          CivStrategyGet()->DoNextCivTutorial(0xe9b77b0b, 1);
          idx = 0;
          break;
        case 1:
          e = GetEffMgr()->Spawn(4, *sp->GetPosition());
          CivStrategyGet()->DoNextCivTutorial(0x9a2cac7f, 1);
          idx = 1;
          break;
        case 2:
          e = GetEffMgr()->Spawn(5, *sp->GetPosition());
          CivStrategyGet()->DoNextCivTutorial(0x92a23f21, 1);
          idx = 2;
          break;
        default: goto tail;
      }
      GetPropSink()->F_60f370(0xcd416e62, (char*)oldCiv->GetProfile() + 0x504, idx, 0);
      if (e) {
        e->F_7eb820(10);
        e->inner->f24 = vehSpec;
      }
    tail:
      CivStrategyGet()->F_cf9ba0();
    audio:
      if (wasPlayer) {
        KillAudio(0x96379456);
        VecPtr* v = oldCiv->GetVec();
        if (v->begin == v->end) KillAudio(0xf155cbac);
      }
    }
    if (!bNew) KillAudio(0xcc8b5a12);
    if (arg3) F_be73d0(type, 0);
    if (CivStrategyGet()->CanBuildSeaVehicles()) CivStrategyGet()->DoCVGCompletionAchievements();
  }
  if (b2e2) F_be4b30(newCiv);
  int nt = (int)(targetsEnd - targetsBegin);
  for (int i = 0; i < nt; i++) {
    F_bd9ed0(i);
    cultureInfo[i * 0x80 + 0x20] = 1;
    targetsBegin[i]->Notify(newId);
  }
  VecPtr* all = NounManager()->GetAll();
  int na = (int)((all->end - all->begin) >> 2);
  for (int i = 0; i < na; i++) {
    Civ* o = ((Civ**)all->begin)[i];
    City* c = F_bdf9e0(o->GetID());
    if (c) c->spatial.Query58();
  }
  if (partnersEnd - partnersBegin) {
    Planet* pm = PlanetModel();
    if (pm) pm->F_b7e4b0();
  }
  b2e4 = 0;
  GetUiCtl()->F_ac8cd0(this, 1);
  if (b2e3) F_bd9060(newCiv);
  if (b2e1) {
    if (!arg2) {
      if (!wasPlayer || bNew || oldCiv->F_bf01e0() > 0) {
        b2e1 = 0;
        if (type >= 0 && type < 3) {
          UiSt* us = GetUiSt();
          if (us->f2c == 1 || us->f2c == 2 || GetUiCtl()->F_ac8d60(this)) {
            b6c0 = 0;
            timer6c8.Restart();
            b2a0 = 1;
          }
        }
      }
    } else {
      b2e1 = 0;
    }
  }
  if (b2e6) F_bdb0b0();

  Msg m;
  m.w[12] = 0x164b4eb;
  m.w[0] = (uint32_t)vtbl_BehaviorMessage;
  _InterlockedExchange((volatile long*)&m.w[1], 0);
  m.w[0] = (uint32_t)vtbl_MessageBasicRC5;
  m.w[14] = 0;
  m.w[2] = (uint32_t)this;
  m.w[4] = newCiv->sub3c.B6f310();
  GetMessagingServer()->Post(m.w[12], &m, 0);
  if (GetCurrentGameMode() != 0x1654c05 && bIsPlayer && b762) b762 = 0;
  PlanetModel()->F_b841a0(PlanetModel()->F_b7ea80(sp->GetPosition()), newId, this);
  if (GetCurrentGameMode() == 0x1654c04 && !arg2) {
    ResKey ka, kb, kc;
    if (bNew) {
      switch (type) {
        case 0: PostCivEvent(0x83cc488e, oldCiv, kc); break;
        case 1: PostCivEvent(0xfc3a94cc, oldCiv, kb); break;
        case 2: PostCivEvent(0x38612d40, oldCiv, ka); break;
      }
      if (oldCiv->F_bf01e0() == 0 && bRel) PostCivEvent(0x9810ca0b, oldCiv, kc);
    } else if (wasPlayer) {
      switch (type) {
        case 0: PostCivEvent(0x4a408125, oldCiv, kb); break;
        case 1: PostCivEvent(0xdd884571, oldCiv, kc); break;
      }
    }
  }
  // message destructor: release every slot flagged in the mask
  m.w[0] = (uint32_t)vtbl_MessageBasicRC5;
  {
    uint32_t bit = 1;
    for (int i = 0; i < 32; i++) {
      if ((m.w[14] & bit) != 0) {
        Civ* p = (Civ*)(*(&m.w[2] + i * 2));
        if (p) p->Release();
      }
      bit = _rotl(bit, 1);
    }
  }
  m.w[0] = (uint32_t)vtbl_LocaleChangeMessage;
  if (oldCiv) oldCiv->Release();
}
