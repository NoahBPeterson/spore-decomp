// SP::cStarMap::FilterHelperEmpires (0x01047850): per-empire star markers plus trade-route lines.
#include "types.h"
#include <math.h>

struct IEffect { virtual void AddRef(); virtual void Release(); virtual void Init(int a); };
struct IEffectInst { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
  virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8();
  virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13();
  virtual void p14(); virtual void p15();
  virtual void SetValue(int type, const float* v, int n);       // +0x40
  virtual void SetVertices(int type, const float* v, int n); }; // +0x44
struct IEffectsManager { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
  virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8();
  virtual void p9(); virtual void p10();
  virtual bool Create(uint32_t hash, int a, IEffect** out); };  // +0x2c

struct Ref {
  IEffect* p;
  Ref() : p(0) {}
  ~Ref() { if (p) p->Release(); }
  void reset() { if (p) { IEffect* t = p; p = 0; t->Release(); } }
};

struct VisualPair {
  uint32_t key;
  IEffect* effect;
  int id;
  int param;
  int one;
  uint8_t flags;
  ~VisualPair() { if (effect) effect->Release(); }
};

struct VisualMap {
  char pad[0x1c];
  void DoInsertValueImpl(void* ret, VisualPair* p, bool b);   // 0x1045490
};

struct CItem {
  char pad[0x70];
  uint32_t key;
  bool FUN_00bb9bd0();               // 0xbb9bd0
  uint32_t GetItemInstanceID();      // 0xc87040
};
struct ItemVec { CItem** b; CItem** e; };

struct CEmpire {
  char pad[0x70];
  uint32_t key;
  ItemVec* GetStars();               // 0xc308d0
  bool FUN_00c31bc0(CEmpire* o);     // 0xc31bc0
  CItem* FUN_00c30c60();             // 0xc30c60
  void GetColor(float* out);         // 0xc32cd0
  int GetAvatar();                   // 0xb1fdb0
  float* GetCities();                // 0x5c65e0
};

struct EmpNode { char pad[0x14]; CEmpire* empire; };
struct EmpireMap { int a; int sentinel; EmpNode* leftmost; };
struct TradeMgr {
  char pad[8]; int anchor; void* leftmost;
  float SystemHasTradeRouteWithPlayer(uint32_t key, int avatar);   // 0x1037dd0
};
struct TradeNode { char pad[0x24]; int idA; int idB; };
struct CStarManager {
  EmpireMap* FUN_00ba6430();         // 0xba6430
  TradeMgr* FUN_00ba6490();          // 0xba6490
  CEmpire* FUN_00ba6d80(int id);     // 0xba6d80
  CEmpire* GetEmpireByID(int id);    // 0xba9370
};
struct CFlagSrc { bool FUN_00feb0b0(CEmpire* e); };   // 0xfeb0b0, global at 0x16e0688


#define AT(T, p, off) (*(T*)((char*)(p) + (off)))

struct CSingleton {
  char raw[0x78];
  void ZeroSub(int a);               // 0xca09f0 (ecx = this+0x20)
  IEffectInst* FUN_01045120(uint32_t key, int id);   // 0x1045120
};
extern CSingleton* g_Singleton;      // 0x16e00d4
struct CSingletonCtor { CSingleton* Ctor(); };     // 0x1046e40
void* __cdecl operator_new6(size_t n, const char* tag, int a, int b, int c, int d);   // 0xf473a0
void  __cdecl operator_delete_arr(void* p);        // 0xf47380
void* __cdecl RBTreeIncrement(void* n);            // 0x921580
CStarManager* __cdecl StarManager();               // 0xb3d2a0
IEffectsManager* __cdecl EffectsManager();         // 0x67ddd0
CEmpire* __cdecl GetPlayerEmpire();                // 0x1021300
int __cdecl GetPlayerEmpireID();                   // 0x1021090
void* __cdecl Memcpy(void* d, void* s, int n);     // 0x11e0744
extern CFlagSrc g_FlagSrc;                         // 0x16e0688

struct FVec {
  float* b; float* e; float* cap;
  void Grow(float* pos, float* v);   // 0x455660
  void Reserve(int bytes);           // 0x4e0880
  void Push(float v) {
    if (e < cap) { float* p = e; e = e + 1; if (p) *p = v; }
    else Grow(e, &v);
  }
};

struct CStarMap {
  bool mCheatOmniscience;            // +0
  bool mRequestZoom;
  char pad[0x56];
  VisualMap mObjectVisuals;          // +0x58
  uint32_t mVisualCount;             // +0x74

  bool FUN_01044bf0(void* obj);                       // 0x1044bf0
  IEffectInst* FUN_01045120(uint32_t key, int id);    // 0x1045120
  void FUN_01045200(IEffect** e, uint32_t key);       // 0x1045200
  void FilterHelperEmpires(int mode);                 // 0x1047850

  __forceinline bool MakeVisual(void* obj, uint32_t key, uint32_t hash, int param, bool force, int* outId)
  {
    uint32_t id = mVisualCount;
    mVisualCount = id + 1;
    Ref effect;
    uint8_t flags = 0;
    if (force || FUN_01044bf0(obj)) {
      flags |= 2;
      IEffectsManager* mgr = EffectsManager();
      effect.reset();
      if (mgr->Create(hash, 0, &effect.p)) {
        effect.p->Init(0);
        FUN_01045200(&effect.p, key);
        VisualPair pr;
        pr.key = key;
        pr.effect = effect.p;
        if (pr.effect) pr.effect->AddRef();
        pr.id = id;
        pr.param = param;
        pr.one = 1;
        pr.flags = flags;
        char ret[8];
        mObjectVisuals.DoInsertValueImpl(ret, &pr, false);
        *outId = id;
        return true;
      }
    }
    return false;
  }
};

static inline bool SpecialMode(int m) {
  return m == 0x166521a5 || m == 0x70930c64 || m == -0x3c0935d8;
}

static inline int RoundToInt(float f) {
  __int64 r;
  __asm { fld f
          fistp r }
  return (int)r;
}

static CSingleton* GetSingleton()
{
  if (!g_Singleton) {
    void* mem = operator_new6(0x78, "Simulator", 0, 0, 0, 0);
    CSingleton* s;
    if (mem) {
      char* c = (char*)mem;
      c[0] = 0; c[1] = 0;
      AT(uint32_t, c, 0x20) = 0; AT(uint32_t, c, 0x24) = 0; AT(uint32_t, c, 0x28) = 0;
      AT(uint32_t, c, 0x2c) = 0; AT(uint32_t, c, 0x30) = 0; AT(uint32_t, c, 0x34) = 0;
      AT(uint32_t, c, 0x38) = 0; AT(uint32_t, c, 0x3c) = 0; AT(uint32_t, c, 0x40) = 0;
      AT(uint32_t, c, 0x44) = 0;
      ((CSingleton*)(c + 0x20 - 0x20))->ZeroSub(0);
      AT(float, c, 0x4c) = 500.0f;
      AT(int, c, 0x50) = 1;
      AT(int, c, 0x54) = 0;
      AT(int, c, 0x60) = 0;
      AT(int, c, 0x64) = 0;
      AT(char, c, 0x68) = 0;
      AT(int, c, 0x6c) = 0;
      AT(void*, c, 0x5c) = c + 0x5c;
      AT(void*, c, 0x60) = c + 0x5c;
      s = (CSingleton*)c;
    } else {
      s = 0;
    }
    g_Singleton = s;
  }
  return g_Singleton;
}

// @ 0x01047850
void CStarMap::FilterHelperEmpires(int mode)
{
  CEmpire* player = GetPlayerEmpire();
  EmpireMap* empires = StarManager()->FUN_00ba6430();
  EmpNode* node = empires->leftmost;
  TradeMgr* trade = StarManager()->FUN_00ba6490();
  void* end = &empires->sentinel;

  if (node != end) {
    do {
      CEmpire* empire = node->empire;
      ItemVec* stars = empire->GetStars();
      bool allied = player->FUN_00c31bc0(empire);
      if (g_FlagSrc.FUN_00feb0b0(empire) && (empire->GetStars()->e - empire->GetStars()->b) != 0) {
        bool go = false;
        if (mode == 0) { if (empire == player) go = true; }
        else if (mode == 1 && empire != player) go = true;
        if (go) {
          int count = (int)(stars->e - stars->b);
          for (int i = 0; i < count; i++) {
            CItem* item = stars->b[i];
            if (mCheatOmniscience || item->FUN_00bb9bd0() || allied) {
              float color[3];
              empire->GetColor(color);
              int id = 0;
              if (empire->FUN_00c30c60() == item) {
                if (empire != player) {
                  if (MakeVisual(item, item->key, 0x700d0f8c, mode, SpecialMode(mode), &id)) {
                    if (id != 0) {
                      IEffectInst* inst = FUN_01045120(item->key, id);
                      if (inst) inst->SetValue(5, color, 1);
                    }
                  }
                }
                id = 0;
                if (!MakeVisual(item, item->key, 0x8e2b9b61, mode, SpecialMode(mode), &id)) id = 0;
              } else {
                uint32_t iid = item->GetItemInstanceID();
                uint32_t hash = (iid & 0x100) ? 0x14f60b83 : 0x76c3a43d;
                if (!MakeVisual(item, item->key, hash, mode, SpecialMode(mode), &id)) id = 0;
              }
              if (id != 0) {
                IEffectInst* inst = FUN_01045120(item->key, id);
                if (inst) inst->SetValue(5, color, 1);
              }
            }
          }
        }
      }
      node = (EmpNode*)RBTreeIncrement(node);
    } while (node != end);
  }

  if (mode == 0) {
    void* tn = trade->leftmost;
    void* tend = &trade->anchor;
    if (tn != tend) {
      do {
        TradeNode* t = (TradeNode*)tn;
        CEmpire* a = StarManager()->FUN_00ba6d80(t->idA);
        CEmpire* b = StarManager()->FUN_00ba6d80(t->idB);
        float colorA[3], colorB[3];
        StarManager()->GetEmpireByID(a->GetAvatar())->GetColor(colorA);
        StarManager()->GetEmpireByID(b->GetAvatar())->GetColor(colorB);
        if (a->GetAvatar() == GetPlayerEmpireID()) {
          float tmp[3];
          tmp[0] = colorA[0]; tmp[1] = colorA[1]; tmp[2] = colorA[2];
          colorA[0] = colorB[0]; colorA[1] = colorB[1]; colorA[2] = colorB[2];
          colorB[0] = tmp[0]; colorB[1] = tmp[1]; colorB[2] = tmp[2];
          CEmpire* t2 = a; a = b; b = t2;
        }
        float w = trade->SystemHasTradeRouteWithPlayer(a->key, a->GetAvatar());
        if (w > 0.0f) {
          int dummy = 0;
          if (w >= 100.0f) {
            MakeVisual(a, a->key, 0xce8e2034, 0, false, &dummy);
          }
          float* c0 = a->GetCities();
          float pos[3];
          pos[0] = c0[0]; pos[1] = c0[1]; pos[2] = c0[2];
          float* c1 = b->GetCities();
          float dx = c1[0] - pos[0];
          float dz = c1[2] - pos[2];
          float dy = c1[1] - pos[1];
          float len = (float)sqrt(dx * dx + dz * dz + dy * dy) * 10.0f;
          int n = RoundToInt(len);
          FVec verts;
          verts.b = 0; verts.e = 0; verts.cap = 0;
          uint32_t cnt = n + 2;
          verts.Reserve(cnt * 12);
          uint32_t np1 = n + 1;
          float inv = 1.0f / (float)np1;
          float step[3];
          step[0] = dx * inv; step[1] = inv * dy; step[2] = inv * dz;
          int vid = 0;
          if (!MakeVisual(a, a->key, 0xdcc022f7, 0, false, &vid)) vid = 0;
          CSingleton* sg = GetSingleton();
          IEffectInst* inst = sg->FUN_01045120(a->key, vid);
          if (inst) {
            inst->SetValue(5, colorA, 1);
            if (cnt != 0) {
              uint32_t k = cnt;
              do {
                verts.Push(pos[0]);
                verts.Push(pos[1]);
                verts.Push(pos[2]);
                k--;
                pos[0] = step[0] + pos[0];
                pos[1] = pos[1] + step[1];
                pos[2] = pos[2] + step[2];
              } while (k != 0);
            }
            inst->SetVertices(0xd, verts.b, cnt * 3);
          }
          int vid2 = 0;
          if (!MakeVisual(b, b->key, 0xdcc022f7, 0, false, &vid2)) vid2 = 0;
          sg = GetSingleton();
          IEffectInst* inst2 = sg->FUN_01045120(b->key, vid2);
          if (inst2) {
            inst2->SetValue(5, colorB, 1);
            Memcpy(verts.b, verts.e, 0);
            verts.e = verts.e - (verts.e - verts.b);
            if (cnt != 0) {
              uint32_t k = cnt;
              do {
                verts.Push(pos[0]);
                verts.Push(pos[1]);
                verts.Push(pos[2]);
                k--;
                pos[0] = pos[0] - step[0];
                pos[1] = pos[1] - step[1];
                pos[2] = pos[2] - step[2];
              } while (k != 0);
            }
            inst2->SetVertices(0xd, verts.b, cnt * 3);
          }
          if (verts.b && ((int*)verts.b)[-1] != 0) operator_delete_arr(verts.b);
        }
        tn = RBTreeIncrement(tn);
      } while (tn != tend);
    }
  }
}
