// SP::cStarMap::Helper47300 (0x01047300): for every colonizable planet of the
// player's empire, find its star record (skipping the home star) and attach a
// 0x41bc3bc4 star visual coloured with the player empire's colour.
#include "types.h"

struct cStarRecord;
struct cPlanetRecord;
struct IEffect;
struct CEmpire;

// ---- effect instance: SetValue is vtable slot +0x40 -------------------------
struct IEffectInst {
  virtual void p0();  virtual void p1();  virtual void p2();  virtual void p3();
  virtual void p4();  virtual void p5();  virtual void p6();  virtual void p7();
  virtual void p8();  virtual void p9();  virtual void p10(); virtual void p11();
  virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
  virtual void SetValue(int type, const float* values, int count);   // +0x40
};

// ---- vtable slot helper -----------------------------------------------------
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
#define RELEASE(o)  ((void(__thiscall*)(void*))VF(o, 4))(o)

struct cStarRecord {
  char pad[0x70];
  uint32_t mpInstance;                       // +0x70
};

struct cPlanetRecord {
  cStarRecord* GetStarRecord();              // 0xb8de30
};

struct PlanetVec {                 // eastl vector header (0x14 bytes)
  cPlanetRecord** mBegin;          // +0x00
  cPlanetRecord** mEnd;            // +0x04
  cPlanetRecord** mCapacity;       // +0x08
  uint32_t mPad0c;                 // +0x0c
  uint32_t mPad10;                 // +0x10
};

struct CEmpire {
  cStarRecord* GetHomeStar();                            // 0xc30c60
  bool CollectColonizable(PlanetVec* out, void* arg);    // 0xc344f0
  void GetColor(float* out);                             // 0xc32cd0
};

struct CSingleton {
  IEffectInst* FindInstance(uint32_t key, IEffect* effect);   // 0x1045120
};
struct CSingletonCtor { CSingleton* Ctor(); };               // 0x1046e40

struct CStarMap {
  IEffect* CreateVisual(cStarRecord* rec, int kind, uint32_t key,
                        uint32_t group, bool flagA, bool flagB);   // 0x1045740
  void Helper47300(uint32_t which);
};

extern CSingleton* g_Singleton;                              // 0x16e00d4
void* __cdecl operator_new6(size_t size, const char* tag, int a, int b, int c, int d); // 0xf473a0
void  __cdecl operator_delete_arr(void* p);                  // 0xf47380
CEmpire* __cdecl GetPlayerEmpire();                          // 0x1021300

static CSingleton* GetSingleton()
{
  CSingleton* sg = g_Singleton;
  if (!sg) {
    void* mem = operator_new6(0x78, "Simulator", 0, 0, 0, 0);
    sg = mem ? ((CSingletonCtor*)mem)->Ctor() : 0;
    g_Singleton = sg;
  }
  return sg;
}

// @ 0x01047300
void CStarMap::Helper47300(uint32_t which)
{
  float color[3];
  PlanetVec items;
  items.mBegin = 0;
  items.mEnd = 0;
  items.mCapacity = 0;

  CEmpire* player = GetPlayerEmpire();
  cStarRecord* home = player->GetHomeStar();

  if (player)
    player->CollectColonizable(&items, 0);

  int count = (int)(items.mEnd - items.mBegin);
  for (int i = 0; i < count; ++i) {
    cPlanetRecord* planet = items.mBegin[i];
    cStarRecord* rec = planet->GetStarRecord();
    if (rec == home)
      continue;

    IEffect* effect = CreateVisual(rec, 0, which, 0x41bc3bc4, false, true);
    if (!effect)
      continue;

    uint32_t key = rec->mpInstance;
    CSingleton* sg = GetSingleton();
    IEffectInst* inst = sg->FindInstance(key, effect);
    if (!inst)
      continue;

    player->GetColor(color);
    inst->SetValue(5, color, 1);
  }

  cPlanetRecord** end = items.mEnd;
  for (cPlanetRecord** it = items.mBegin; it < end; ++it) {
    if (*it)
      RELEASE(*it);
  }
  if (items.mBegin && ((int*)items.mBegin)[-1] != 0)
    operator_delete_arr(items.mBegin);
}
