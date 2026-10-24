// gold7 batch, worker 5 / slice s00be88d0: two cCity helpers that ride on the
// ChangeCivilization (0xbe88d0) path.
//   0x00be9250  a rbtree<int, pair<int,wstring>> lookup that converts a civ-count to a
//               float and feeds it through the 0x00ceeb80 helper (returns -1.0f when the
//               key is absent).
//   0x00be92e0  the "change this city's civilization" driver: it swaps the city's civ,
//               fires the tutorial/achievement/audio hooks and posts the CVG_Capture
//               trigger + message.
// The skeleton types mirror s00be88d0.cpp (same city layout / same callees).
// Module flags: /O2 /MD /Gy /TP /EHsc /GS- /arch:SSE /fp:fast
#include "types.h"
#include <xmmintrin.h>

struct Vec3 {
  float x, y, z;
  Vec3() {}
  Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

// ---------------------------------------------------------------- shared types
struct City;
struct CfgStr { uint32_t pad[6]; };

struct Timer {
  uint8_t _p[4];
  void Stop();                             // 0xbc3110
  void Restart();                          // 0xbc3130
};

struct NameSub { virtual void s0(); virtual const wchar_t* GetName(); };

struct SpatialSub {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
  virtual void s8(); virtual void s9(); virtual void s10();
  virtual Vec3* GetPosition();             // vt+0x2c
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
  virtual void s20(); virtual void s21();
  virtual bool Query58();                  // vt+0x58
};

struct Civ {
  virtual void AddRef();                   // vt+0
  virtual void Release();                  // vt+4
  virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
  virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
  virtual bool Query2c();                  // vt+0x2c
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18();
  virtual int GetID();                     // vt+0x4c
  uint8_t pad04[0xc4 - 4];
  float mPosX;                             // +0xc4
  float mPosY;                             // +0xc8
  float mPosZ;                             // +0xcc
  uint8_t padD0[0x44c - 0xd0];
  City* mCity44c;                          // +0x44c
  uint8_t pad450[0x4bc - 0x450];
  int mField4bc;                           // +0x4bc
  uint8_t pad4c0[0];
  int F_bf01e0();                          // 0xbf01e0
  int F_bf0f40();                          // 0xbf0f40
};

struct City;

// {0x00,0x04} of the map node: the payload is pair<const int, char-string>.
struct Node { void* left; void* right; void* parent; void* color; int key; uint32_t pad; };

// eastl::rbtree<int,pair<int,wstring>,...> at city+0x570.
struct DirTree {
  void** anchor_head;                      // +0x00
  void* root;                              // +0x04
  void** Find(void** out, const int* key); // 0xe39fb0 (returns out)
  float* GetNode(const int* key);          // 0xbe0790
};

struct NounMgr {
  Civ* GetCivById(int id);                 // 0xb25f40 ret 4
  Civ* GetPlayerCivilization();            // 0xb25fb0
};
struct CivStrategy {
  bool CanBuildSeaVehicles();              // 0xcf75d0
  void F_cf7520();                         // 0xcf7520
  void F_cf8e00();                         // 0xcf8e00
};
struct MsgServer {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
  virtual void s5();
  virtual void Post(uint32_t id, uint32_t a, int b, int c);   // vt+0x18
};
struct TerrainEd { void* GetCurrentTerrainSphere(); };        // 0xf67d90
struct TriggerMgr {
  void PostAction(uint32_t id, void* p, int a);               // 0xae09b0 ret 0xc
  void PostAction2(uint32_t id, void* p, int a);              // 0xae09b0 ret 0xc
  void PostTrigger(const wchar_t* name, int a, int b, int c, int d, int e);  // 0xae0930
  void PostStringCtx(uint32_t id, void* p, int a);            // 0xadde90
};
struct Player { bool HasFlagOrInsert(uint32_t flag); };       // 0xc77bf0
struct Cinfo { uint32_t pad[4]; };

struct City {
  uint8_t pad00[0x34];
  NameSub name;                            // +0x34
  uint8_t pad38[0x120 - 0x38];
  SpatialSub spatial;                      // +0x120
  uint8_t pad124[0x230 - 0x124];
  Timer timer230;                          // +0x230
  uint8_t pad234[0x29c - 0x234];
  int type;                                // +0x29c
  uint8_t pad2a0[0x2e0 - 0x2a0];
  uint8_t b2e0, b2e1, b2e2, b2e3, b2e4, b2e5, b2e6;
  uint8_t pad2e7[0x320 - 0x2e7];
  uint32_t* timer320;                      // +0x320
  uint8_t pad324[0x33c - 0x324];
  uint8_t pad33c[0x340 - 0x33c];
  uint32_t* timedBegin;                    // +0x340
  uint32_t* timedEnd;                      // +0x344
  uint8_t pad348[0x540 - 0x348];
  int vehSpec;                             // +0x540
  uint8_t pad544[0x570 - 0x544];
  void** anchor570;                        // +0x570
  void*  root574;                          // +0x574
  uint8_t pad578[0x590 - 0x578];
  Civ* civ;                                // +0x590
  uint8_t pad594[0x618 - 0x594];
  uint8_t pad618[0x6c0 - 0x618];
  uint8_t b6c0;
  uint8_t pad6c1[0x6c8 - 0x6c1];
  Timer timer6c8;                          // +0x6c8
  uint8_t pad6cc[0x748 - 0x6cc];
  float f748; int f74c; float f750; int f754; float f758; int f75c;   // +0x748
  uint8_t pad760[2];
  uint8_t b762;                            // +0x762
  uint8_t pad763[0x7d8 - 0x763];
  int f7d8; int f7dc; int f7e0; int f7e4; int f7e8; int f7ec;  // +0x7d8 (raw float bits)
  uint8_t pad7f0[0x810 - 0x7f0];
  uint32_t* ptr810;                        // +0x810

  float F_be9250(int key);                 // @ 0xbe9250
  float F_be6d90(float v);                 // 0xbe6d90 thiscall -> x87 float
  bool  F_be92e0(int newId, int a2, int a3, char a4, int a5);   // @ 0xbe92e0 ret 0x14
  void ChangeCivilization(int newId, int arg2, int arg3);   // 0xbe88d0 ret 0xc
};

// A timed-object slot in the city's 0x340..0x344 vector; TimedStop is 0xbfc6a0.
struct Sub340 { uint32_t pad[(0x120) / 4]; void TimedStop(); };

// cActionTarget-family stack object (0xad7xxx).
struct ActionTarget { uint8_t pad[0x30]; };
struct CamInfo { uint32_t pad[3]; float f0c; };
struct TerrainSphere { uint32_t pad[4]; };
struct TerrainEdSph { void* GetCurrentTerrainSphere(); };   // 0xf67d90

// Game-mode sentinel + civ strategy / terrain helpers.
NounMgr* NounManager();                     // 0xb3d300
uint32_t GetCurrentGameMode();              // 0xb5b800
MsgServer* MessageServer();                 // 0x67dcc0
CivStrategy* CivStrategyGet();              // 0xcf74c0
TerrainEd* GetTerrainEditor();              // (SP::NounManager()->0xf67d90)
TriggerMgr* GetTriggerMgr();                // 0xb3d4d0
City* Fn_00b3d4e0();                        // 0xb3d4e0 (returns object with +0x68 Vec3)
void   Fn_00ad7a30(ActionTarget* self, void* target);      // 0xad7a30
void*  Fn_00ad7b70(ActionTarget* self);                    // 0xad7b70
void   Fn_00ad79d0(CamInfo* self, void* p);                // 0xad79d0
void   Fn_00ad7ad0(ActionTarget* self);                    // 0xad7ad0 dtor
bool   Fn_00c772c0(TerrainSphere* sphere, uint32_t flag);  // 0xc772c0
void   Fn_00c77bf0(TerrainSphere* sphere, uint32_t flag);  // 0xc77bf0
void   Fn_00cf7520();                                      // 0xcf7520
void   Fn_00cf8e00();                                      // 0xcf8e00
void   Fn_00be45b0(int a, City* c);                        // 0xbe45b0
void   Fn_00be2440(City* c, int a, int b);                 // 0xbe2440
void   Fn_00dc4c60();                                      // 0xdc4c60
uint32_t Fn_00befab0();                                    // 0xbefab0
void   Fn_00bd7f70(void* a, void* b);                      // 0xbd7f70
void   Fn_00b3d4d0(uint32_t id, void* p, int a);           // 0xb3d4d0 (trigger ctx helper)
struct CfgObj { float F_ceeb80(float a, float b); };       // object at 0x169c254, 0xceeb80

// @ 0x00be9250  (137 bytes)
float City::F_be9250(int key)
{
  int k = key;
  void* node;
  DirTree* tree = (DirTree*)((char*)this + 0x570);
  void** rr = tree->Find(&node, &k);
  if (*rr != (char*)this + 0x574) {
    float* pv = tree->GetNode(&k);
    float fn = (float)civ->F_bf01e0();
    float conv = F_be6d90(fn);
    return ((CfgObj*)0x169c254)->F_ceeb80(*pv, conv);
  }
  return -1.0f;
}

// @ 0x00be92e0  (1391 bytes)
bool City::F_be92e0(int newId, int a3, int a4, char a5, int a6)
{
  type = a3;

  Civ* oldCiv = civ;
  int oldId = oldCiv->GetID();
  if (newId == oldId)
    return false;
  if (oldCiv) oldCiv->AddRef();

  Civ* newCiv = NounManager()->GetCivById(newId);
  if (newCiv == 0) {
    if (oldCiv) oldCiv->Release();
    return false;
  }

  spatial.Query58();
  Civ* playerCiv = NounManager()->GetPlayerCivilization();
  newCiv->mCity44c = this;
  newCiv->mField4bc = (int)Fn_00befab0();
  b2e0 = b2e1 = b2e2 = b2e3 = b2e4 = b2e5 = b2e6 = 1;
  f74c = -1; f748 = 0.0f;
  f754 = -1; f750 = 0.0f;
  f75c = -1; f758 = 0.0f;

  {
    char* rec = (char*)Fn_00b3d4e0();
    float px = newCiv->mPosX, py = newCiv->mPosY, pz = newCiv->mPosZ;
    *(float*)(rec + 0x68) = px;
    *(float*)(rec + 0x6c) = py;
    *(float*)(rec + 0x70) = pz;
  }
  union FB { float f; int i; };
  f7d8 = ((FB&)oldCiv->mPosX).i;
  f7dc = ((FB&)oldCiv->mPosY).i;
  f7e0 = ((FB&)oldCiv->mPosZ).i;
  f7e4 = ((FB&)newCiv->mPosX).i;
  f7e8 = ((FB&)newCiv->mPosY).i;
  f7ec = ((FB&)newCiv->mPosZ).i;

  if (type == 0 || type == 1) {
    Fn_00be45b0(0, this);
    MessageServer()->Post(0x66e0e11, 0, 0, 0);
  }

  if (GetCurrentGameMode() != 0x1654c04 || newCiv != playerCiv) {
    ChangeCivilization(newId, a4, a6);
    goto tail;
  }

  if (ptr810 && ((bool(*)(void*))((void**)ptr810)[0x10 / 4])(ptr810)) {
    ((void(*)(void*, int))((void**)ptr810)[0x0c / 4])(ptr810, 0);
    Fn_00dc4c60();
    timer230.Stop();
    for (int i = 0; i < (int)(timedEnd - timedBegin); i++)
      ((Sub340*)timedBegin[i])->TimedStop();
    Fn_00be2440(this, 0, 0);
  }

  TerrainEdSph* tes = (TerrainEdSph*)NounManager();
  TerrainSphere* sphere = (TerrainSphere*)tes->GetCurrentTerrainSphere();

  if ((char)a4 != 0 || b762 != 0) {
    ChangeCivilization(newId, a4, a6);
    CivStrategyGet()->CanBuildSeaVehicles();
    if (CivStrategyGet()->CanBuildSeaVehicles()) {
      Fn_00cf8e00();
      Fn_00cf7520();
    }
    goto tail;
  }

  {
    void* target = (timer320 == 0) ? 0 : (char*)timer320 + 0x34;
    ActionTarget at;
    Fn_00ad7a30(&at, target);
    GetTriggerMgr()->PostAction(0x115fa309, &at, 0);

    CamInfo ci;
    void* camOut;
    ActionTarget at2;
    Fn_00bd7f70(&camOut, &ci);
    void* p = Fn_00ad7b70(&at);
    Fn_00ad79d0(&ci, p);
    ci.f0c = *(float*)&camOut;
    GetTriggerMgr()->PostAction(0x3f04cafe, &at2, 0);

    int spec = vehSpec;
    bool inserted = false;
    int id = 0;
    if (spec == 0) {
      if (!Fn_00c772c0(sphere, 0x46bddaa)) { Fn_00c77bf0(sphere, 0x46bddaa); inserted = true; }
    } else if (spec == 1) {
      if (!Fn_00c772c0(sphere, 0x46bdddc)) { Fn_00c77bf0(sphere, 0x46bdddc); inserted = true; }
    } else if (spec == 2 && !Fn_00c772c0(sphere, 0x46bdde0)) {
      Fn_00c77bf0(sphere, 0x46bdde0); inserted = true;
    }

    if ((type == 0 && spec == 0) || (type == 1 && spec == 1) || (type == 2 && spec == 2)) {
      if (type == 0) id = 0x803;
      else if (type == 1) id = 0x804;
      else if (type == 2) id = 0x805;
    } else if (spec == 0) {
      if (inserted) id = (type != 1 ? 1 : 0) * 2 + 0x902;
      else          id = (type != 1 ? 1 : 0) * 8 + 0x908;
    } else if (spec == 1) {
      if (inserted) id = (type != 0 ? 5 : 0) + 0x900;
      else          id = (type != 0 ? 0xb : 0) + 0x906;
    } else if (spec == 2) {
      if (inserted) id = (type != 0 ? 1 : 0) * 2 + 0x901;
      else          id = (type != 0 ? 1 : 0) * 2 + 0x907;
    }
    Fn_00b3d4d0(0x3988d136, &id, 0);
    GetTriggerMgr()->PostStringCtx(0x3988d136, &id, 0);

    const wchar_t* name = (a5 == 0) ? L"CVG_Capture" : L"CVG_Capture_Nuked";
    GetTriggerMgr()->PostTrigger(name, 1, 0, 0, 0, 0);
    MessageServer()->Post(0x6130eb9, 0, 0, 0);
    b6c0 = 0;
    timer6c8.Restart();
    Fn_00ad7ad0(&at2);
    Fn_00ad7ad0(&at);
  }
  goto tail;

tail:
  oldCiv->Release();
  return true;
}
