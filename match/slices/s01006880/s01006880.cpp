// Slice s01006880 (batch gold6, worker 44). Region 0x01006880-0x01007430.
// SP::cSPSimulatorSpaceGame destructor plus Init/PostLoad/UpdatePosseUFO cluster.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;

// ---- external callees (address in comment) ------------------------------
void  __cdecl FUN_01005320(void* self);              // 0x01005320 SimGame::f5320
void* __cdecl FUN_006fab90(void* a, void* b);        // 0x006fab90 SP::cFragmentDecl::~cFragmentDecl
void  __cdecl FUN_00f47380(void* p);                 // 0x00f47380 operator_delete_array
void* __cdecl FUN_00b638b0(void* self);              // 0x00b638b0 cGonzagoTimer::~cGonzagoTimer
void* __cdecl FUN_00ae6970(void* self);              // 0x00ae6970 vector dtor
void  __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e); // 0x00571db0 EA::Messaging::RemoveHandler
void* __cdecl FUN_00b3d330();                        // 0x00b3d330 SP::SimTicker
void* __cdecl FUN_00f473a0(u32 size, const char*, int, int, int, int); // 0x00f473a0 operator new
void* __cdecl FUN_00fe4fa0(void* self);              // 0x00fe4fa0 cSPBadgeManager ctor
void* __cdecl FUN_00ae6a70(void* self);              // 0x00ae6a70 cCitySimulator ctor
void* __cdecl FUN_00ae7350(void* self);              // 0x00ae7350 cCitySimulator::AttachSubsystems
void* __cdecl FUN_010154f0(void* self);              // 0x010154f0 cSimulatorUniverse ctor
void* __cdecl FUN_00b6f4c0(void* self);              // 0x00b6f4c0
void* __cdecl FUN_01000740(void* self);              // 0x01000740 cSPSimulatorPlayerUFO ctor
void* __cdecl FUN_00ffc160(void* a, void* b, void* c);// 0x00ffc160
void* __cdecl FUN_00fecc90(void* self);              // 0x00fecc90
void* __cdecl FUN_00fedb50(void* self);              // 0x00fedb50 cSPMissionManager::InitForGame
void* __cdecl FUN_010164d0(void* self);              // 0x010164d0 cSPSimulatorWalkAround ctor
void* __cdecl FUN_01015f50(void* self);              // 0x01015f50
void* __cdecl FUN_00579a90(void* self, const void* wstr); // 0x00579a90 eastl::wstring::range_initialize
void* __cdecl FUN_00d0d200(void* self);              // 0x00d0d200 Simulator::cCommunityEditor ctor
void* __cdecl FUN_00d0a760(void* self, void* a, u32 b, void* c, void* d); // 0x00d0a760 cCommunityEditor::Init
void* __cdecl FUN_00ff5190(void* self);              // 0x00ff5190 Simulator::cPlayerInventory ctor
void* __cdecl FUN_00883860();                        // 0x00883860 EA::Messaging::GetServer
void* __cdecl FUN_01070ba0(void* self);              // 0x01070ba0 cSPUISpace ctor
void* __cdecl FUN_01073700(void* self);              // 0x01073700 cSPUISpace::Init
void* __cdecl FUN_010762e0(void* self);              // 0x010762e0
void* __cdecl FUN_01075490(void* self);              // 0x01075490
void* __cdecl FUN_00b3d300();                        // 0x00b3d300 SP::NounManager
void* __cdecl FUN_00b22960(void* self);              // 0x00b22960 cGNM2::ProcessPending
void* __cdecl FUN_00ffbe50();                        // 0x00ffbe50 SP::GetUFOSimulator
void* __cdecl FUN_00a1ad60(void* self);              // 0x00a1ad60 GetPlayerInventory
void* __cdecl FUN_00c37180(void* self, void* a, int b); // 0x00c37180 cSPGameDataUFO::SetDesiredModel
void* __cdecl FUN_00fe7160(void* self);              // 0x00fe7160
void* __cdecl FUN_00bc3130(void* self);              // 0x00bc3130 cSPTimer::Restart
void* __cdecl FUN_010060d0(void* self);              // 0x010060d0 cSPSimulatorSpaceGame::ConfigUpdated
void* __cdecl FUN_00f67d90(void* self);              // 0x00f67d90 GetCurrentTerrainSphere
void* __cdecl FUN_00c75a50(void* self);              // 0x00c75a50
void* __cdecl FUN_01005d80(void* self, int a, int b); // 0x01005d80
void* __cdecl FUN_008de1a0();                        // 0x008de1a0 ObjectError
void* __cdecl FUN_00926020(int a, u32 b, int c, int d, int e, int f); // 0x00926020 ZoneObject_new
void* __cdecl FUN_00998820(void* self);              // 0x00998820
void* __cdecl FUN_0067dcd0();                        // 0x0067dcd0 GetManager
void* __cdecl FUN_00b6a530();                        // 0x00b6a530
void* __cdecl FUN_00ff5b50(void* self);              // 0x00ff5b50
void* __cdecl FUN_00ffbf60(void* self);              // 0x00ffbf60
void* __cdecl FUN_00feb9f0();                        // 0x00feb9f0 SP::GetMissionManager
void* __cdecl FUN_00fee310(void* self);              // 0x00fee310
void* __cdecl FUN_00e184d0(void* self);              // 0x00e184d0
void* __cdecl FUN_00685520(int flag);                // 0x00685520 IsWorldLayoutFlagSet
void* __cdecl FUN_00b3d400();                        // 0x00b3d400
void* __cdecl FUN_01021300();                        // 0x01021300
void* __cdecl FUN_00c32980(void* self);              // 0x00c32980
void* __cdecl FUN_0102b620();                        // 0x0102b620
float __cdecl FUN_00c3ae70();                        // 0x00c3ae70
void* __cdecl FUN_0059aed0(void* out, void* a, void* b); // 0x0059aed0
void* __cdecl FUN_00c3bfe0(void* self, void* v);     // 0x00c3bfe0 cSPGameDataUFO::SetDestination
void* __cdecl FUN_00b3d2a0(void* a);                 // 0x00b3d2a0 SP::StarManager
void* __cdecl FUN_00ba9370(void* self, void* a);     // 0x00ba9370 cStarManager::GetEmpireByID
void* __cdecl FUN_00c309e0(void* self);              // 0x00c309e0 cEmpire::IsHostileToPlayer
void* __cdecl FUN_0069b600(void* out, void* a, void* b, void* c, void* d); // 0x0069b600 QuaternionFromFacingAndUp
void* __cdecl FUN_005b26f0(void* out, void* a, void* b, void* c); // 0x005b26f0 SlerpWrap

// ======================================================================
// 0x01006880 - SP::cSPSimulatorSpaceGame::~cSPSimulatorSpaceGame. thiscall.
// ======================================================================

// @ 0x01006880
void __fastcall FUN_01006880(void* self, void* /*edx*/) {
  char* p = (char*)self;
  *(u32*)(p + 0) = 0x0149544c;
  *(u32*)(p + 8) = 0x01495428;
  *(u32*)(p + 0x10) = 0x01495418;
  {
    void* a = *(void**)(p + 0x28);
    if (a != 0) {
      *(void**)(p + 0x28) = 0;
      (*(void(__thiscall**)(void*))(*(void***)a + 1))(a);
    }
  }
  {
    void* b = *(void**)(p + 0x30);
    if (b != 0) {
      (*(void(__thiscall**)(void*, int))*(void***)b)(b, 1);
    }
  }
  *(void**)(p + 0x30) = 0;
  *(u32*)0x016dc0fc = 0;
  ((void(__thiscall*)(void*))FUN_01005320)(p + 0xdc);
  ((void(__thiscall*)(void*, void*, void*))FUN_006fab90)(
      p + 0xc8, *(void**)(p + 0xc8), *(void**)(p + 0xcc));
  {
    void* c = *(void**)(p + 0xc8);
    if (c != 0 && *(u32*)((char*)c - 4) != 0) {
      FUN_00f47380(c);
    }
  }
  {
    void* d = *(void**)(p + 0xc0);
    if (d != 0) (*(void(__thiscall**)(void*))(*(void***)d + 2))(d);
  }
  {
    void* e = *(void**)(p + 0xbc);
    if (e != 0) (*(void(__thiscall**)(void*))(*(void***)e + 2))(e);
  }
  {
    void* f = *(void**)(p + 0xb8);
    if (f != 0) (*(void(__thiscall**)(void*))(*(void***)f + 2))(f);
  }
  {
    void* g = *(void**)(p + 0xb4);
    if (g != 0) (*(void(__thiscall**)(void*))(*(void***)g + 2))(g);
  }
  ((void(__thiscall*)(void*))FUN_00b638b0)(p + 0x90);
  ((void(__thiscall*)(void*))FUN_00ae6970)(p + 0x78);
  {
    void* h = *(void**)(p + 0x70);
    if (h != 0) (*(void(__thiscall**)(void*))(*(void***)h + 2))(h);
  }
  {
    void* i = *(void**)(p + 0x58);
    if (i != 0) {
      *(void**)(p + 0x58) = 0;
      FUN_00571db0(i, *(void**)(p + 0x5c), *(void**)(p + 0x60),
                   *(void**)(p + 0x64), *(void**)(p + 0x68));
    }
  }
  {
    void* j = *(void**)(p + 0x54);
    if (j != 0) (*(void(__thiscall**)(void*))(*(void***)j + 2))(j);
  }
  {
    char* k = *(char**)(p + 0x48);
    if (k != 0) {
      char* kk = k + 8;
      --*(s32*)kk;
      s32 old = *(s32*)kk;
      if (old < 1) {
        ++*(s32*)kk;
      } else {
        volatile s32 dummy = *(s32*)kk;
        (void)dummy;
      }
    }
  }
  {
    void* l = *(void**)(p + 0x44);
    if (l != 0) (*(void(__thiscall**)(void*))(*(void***)l + 2))(l);
  }
  {
    void* m = *(void**)(p + 0x40);
    if (m != 0) (*(void(__thiscall**)(void*))(*(void***)m + 1))(m);
  }
  {
    void* n = *(void**)(p + 0x28);
    if (n != 0) (*(void(__thiscall**)(void*))(*(void***)n + 1))(n);
  }
  {
    void* o = *(void**)(p + 0x24);
    if (o != 0) (*(void(__thiscall**)(void*))(*(void***)o + 2))(o);
  }
  {
    void* q = *(void**)(p + 0x20);
    if (q != 0) (*(void(__thiscall**)(void*))(*(void***)q + 3))(q);
  }
  {
    void* r = *(void**)(p + 0x18);
    if (r != 0) (*(void(__thiscall**)(void*))(*(void***)r + 1))(r);
  }
  {
    void* s = *(void**)(p + 0x14);
    if (s != 0) (*(void(__thiscall**)(void*))(*(void***)s + 1))(s);
  }
  *(u32*)(p + 0x10) = 0x013eb394;
  *(u32*)(p + 8) = 0x013eb938;
  *(u32*)(p + 0) = 0x013ec458;
}

// ======================================================================
// 0x01006a40 - SP::cSPSimulatorSpaceGame::UpdatePosseUFO. thiscall, ret 20.
// ======================================================================

// @ 0x01006a40
void __fastcall FUN_01006a40(void* self, void* /*edx*/, void* arg1, int arg2,
                             int arg3, float arg4, float arg5) {
  char* p = (char*)self;
  char* ufo = (char*)arg1;
  char* gd = *(char**)(ufo + 0x68c);
  if (gd == 0) return;

  float r = FUN_00c3ae70();
  float fscale = (r <= arg4) ? arg4 : r;

  char* g1 = *(char**)(ufo + 0x68c);
  float best = 0.0f;
  void* bestObj = 0;

  if (g1[0x74c] != 0) {
    // rotational branch
    float rad = (float)arg3;
    if (arg3 < 0) rad += 4294967300.0f;
    rad *= *(float*)0x013f999c;
    float sn = (float)0;
    float cs = (float)0;
    (void)sn; (void)cs;
    float fwd[3];
    fwd[0] = 0; fwd[1] = 0; fwd[2] = 0;
    float out[3];
    out[0] = 0; out[1] = 0; out[2] = 0;
    FUN_0059aed0(out, ufo + 0x6a0, fwd);
    float* mp = (float*)(*(void*(__thiscall**)(void*))(*(void***)(g1 + 0x34) + 0x2c / 4))(g1 + 0x34);
    float dx = mp[0] - *(float*)(ufo + 0x750);
    float dy = mp[1] - *(float*)(ufo + 0x754);
    float dz = mp[2] - *(float*)(ufo + 0x758);
    float dist = 0.0f;
    (void)dx; (void)dy; (void)dz; (void)dist;
    ufo[0x624] = 1;
  } else {
    // positional branch
    int idx = *(int*)(ufo + 0x6b0);
    char* off = (char*)(0x016dc060 + idx * 12);
    float x = *(float*)(off + 0) * (float)arg2 * fscale;
    float y = *(float*)(off + 4) * (float)arg2 * fscale;
    float z = *(float*)(off + 8) * (float)arg2 * fscale;
    float base[3];
    base[0] = x; base[1] = y; base[2] = z;
    void* m = (*(void*(__thiscall**)(void*))(*(void***)(g1 + 0x34) + 0x30 / 4))(g1 + 0x34);
    float* pos = (float*)FUN_0059aed0(pos, base, m);
    float out[3];
    out[0] = *(float*)(g1 + 0x750) + pos[0];
    out[1] = *(float*)(g1 + 0x754) + pos[1];
    out[2] = *(float*)(g1 + 0x758) + pos[2];
    FUN_00c3bfe0(ufo, out);
    ufo[0x624] = 1;
  }

  if (*(int*)(ufo + 0x76c) != 3) {
    void* owner = (*(void*(__thiscall**)(void*))(*(void***)(ufo + 0x34) + 0x2c / 4))(ufo + 0x34);
    float* op = (float*)owner;
    best = *(float*)0x149538c;
    char* it = *(char**)(p + 0x78);
    char* e = *(char**)(p + 0x7c);
    for (; it != e; it += 4) {
      char* cand = *(char**)it;
      if (*(int*)(cand + 0x714) == 8 && *(int*)(cand + 0x76c) != 3) {
        void* co = (*(void*(__thiscall**)(void*))(*(void***)(cand + 0x34) + 0x2c / 4))(cand + 0x34);
        float* cp = (float*)co;
        float dx = op[0] - cp[0];
        float dy = op[1] - cp[1];
        float dz = op[2] - cp[2];
        float d2 = dx * dx + dy * dy + dz * dz;
        if (d2 < best) {
          int id = (*(int(__thiscall**)(void*))(*(void***)cand + 0x4c / 4))(cand);
          void* sm = FUN_00b3d2a0((void*)id);
          void* emp = FUN_00ba9370(sm, 0);
          if (emp == 0 || FUN_00c309e0(emp) != 0) {
            best = d2;
            bestObj = cand;
          }
        }
      }
    }
  }
  void* res = bestObj ? (char*)bestObj + 0x508 : 0;
  (*(void(__thiscall**)(void*, void*))(*(void***)(ufo + 0x508) + 0x50 / 4))(ufo + 0x508, res);
}

// ======================================================================
// 0x01006ef0 - SP::cSPSimulatorSpaceGame::Init. thiscall, ret 4.
// ======================================================================

// @ 0x01006ef0
void __fastcall FUN_01006ef0(void* self, void* /*edx*/, char* arg1) {
  char* p = (char*)self;
  char* a1 = arg1;

  void* tick = FUN_00b3d330();
  (*(void(__thiscall**)(void*, void*))(*(void***)tick + 0x50 / 4))(tick, self);

  if (*(void**)(p + 0x70) == 0) {
    char* nb = (char*)FUN_00f473a0(0xc0, "Simulator", 0, 0, 0, 0);
    char* created = nb ? (char*)FUN_00fe4fa0(nb) : 0;
    char* old = *(char**)(p + 0x70);
    if (created != old) {
      if (created != 0) (*(void(__thiscall**)(void*))(*(void***)created + 1))(created);
      *(char**)(p + 0x70) = created;
      if (old != 0) (*(void(__thiscall**)(void*))(*(void***)old + 2))(old);
    }
    void* tk2 = FUN_00b3d330();
    (*(void(__thiscall**)(void*, char*))(*(void***)tk2 + 0x50 / 4))(tk2, *(char**)(p + 0x70));
  }

  if (*(void**)0x0167a690 == 0) {
    char* nb = (char*)FUN_00f473a0(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
    *(void**)0x0167a690 = nb ? (void*)FUN_00ae6a70(nb) : 0;
  }
  char* sim = *(char**)0x0167a690;
  FUN_00ae7350(sim);
  void* tk3 = FUN_00b3d330();
  (*(void(__thiscall**)(void*, char*))(*(void***)tk3 + 0x50 / 4))(tk3, sim);

  char* nb1 = (char*)FUN_00f473a0(0x1b8, "Simulator", 0, 0, 0, 0);
  char* uni = nb1 ? (char*)FUN_010154f0(nb1) : 0;
  char* oldU = *(char**)(p + 0xc0);
  if (uni != oldU) {
    if (uni != 0) (*(void(__thiscall**)(void*))(*(void***)uni + 1))(uni);
    *(char**)(p + 0xc0) = uni;
    if (oldU != 0) (*(void(__thiscall**)(void*))(*(void***)oldU + 2))(oldU);
  }
  FUN_00b6f4c0(*(void**)(p + 0xc0));

  char* nb2 = (char*)FUN_00f473a0(0xe0, "Simulator", 0, 0, 0, 0);
  char* pu = nb2 ? (char*)FUN_01000740(nb2) : 0;
  char* oldP = *(char**)(p + 0xb4);
  if (pu != oldP) {
    if (pu != 0) (*(void(__thiscall**)(void*))(*(void***)pu + 1))(pu);
    *(char**)(p + 0xb4) = pu;
    if (oldP != 0) (*(void(__thiscall**)(void*))(*(void***)oldP + 2))(oldP);
  }
  FUN_00ffc160(*(void**)(a1 + 0), *(void**)(a1 + 4), 0);
  (void)0;

  char* nb3 = (char*)FUN_00f473a0(0x144, "Simulator", 0, 0, 0, 0);
  char* mm = nb3 ? (char*)FUN_00fecc90(nb3) : 0;
  char* oldM = *(char**)(p + 0xb8);
  if (mm != oldM) {
    if (mm != 0) (*(void(__thiscall**)(void*))(*(void***)mm + 1))(mm);
    *(char**)(p + 0xb8) = mm;
    if (oldM != 0) (*(void(__thiscall**)(void*))(*(void***)oldM + 2))(oldM);
  }
  FUN_00fedb50(*(void**)(p + 0xb8));

  char* nb4 = (char*)FUN_00f473a0(0x70, "Simulator", 0, 0, 0, 0);
  char* wa = nb4 ? (char*)FUN_010164d0(nb4) : 0;
  char* oldW = *(char**)(p + 0xbc);
  if (wa != oldW) {
    if (wa != 0) (*(void(__thiscall**)(void*))(*(void***)wa + 1))(wa);
    *(char**)(p + 0xbc) = wa;
    if (oldW != 0) (*(void(__thiscall**)(void*))(*(void***)oldW + 2))(oldW);
  }
  FUN_01015f50(*(void**)(p + 0xbc));

  u32 wstr[3];
  wstr[0] = 0; wstr[1] = 0; wstr[2] = 0;
  FUN_00579a90(wstr, (const void*)0x014772a0);
  char* nb5 = (char*)FUN_00f473a0(0x2fc, "Simulator/cCommunityEditor", 0, 0, 0, 0);
  char* ce = nb5 ? (char*)FUN_00d0d200(nb5) : 0;
  char* oldC = *(char**)(p + 0x20);
  if (ce != oldC) {
    if (ce != 0) (*(void(__thiscall**)(void*))(*(void***)ce + 2))(ce);
    *(char**)(p + 0x20) = ce;
    if (oldC != 0) (*(void(__thiscall**)(void*))(*(void***)oldC + 3))(oldC);
  }
  FUN_00d0a760(*(void**)(p + 0x20), wstr, 0x54e13add, 0, (void*)1);

  if (*(void**)(p + 0x40) == 0) {
    char* nb6 = (char*)FUN_00f473a0(0x98, "Simulator", 0, 0, 0, 0);
    char* pi = nb6 ? (char*)FUN_00ff5190(nb6) : 0;
    char* oldI = *(char**)(p + 0x40);
    if (pi != oldI) {
      if (pi != 0) (*(void(__thiscall**)(void*))(*(void***)pi + 0))(pi);
      *(char**)(p + 0x40) = pi;
      if (oldI != 0) (*(void(__thiscall**)(void*))(*(void***)oldI + 1))(oldI);
    }
    (*(void(__thiscall**)(void*))(*(void***)*(void**)(p + 0x40) + 0x54 / 4))(*(void**)(p + 0x40));
  }

  char* srv = (char*)FUN_00883860();
  *(char**)(p + 0x58) = srv;
  *(char**)(p + 0x5c) = p + 0x10;
  *(u32*)(p + 0x60) = 0x014952a0;
  *(u32*)(p + 0x64) = 0x2f;
  *(u32*)(p + 0x68) = 0;
  if (srv != 0 && (p + 0x10) != 0) {
    for (u32 off = 0; off < 0xbc; off += 4) {
      u32 v = *(u32*)(0x014952a0 + off);
      (*(void(__thiscall**)(void*, char*, u32))(*(void***)srv + 0x24 / 4))(srv, p + 0x10, v);
    }
  }

  if (*(void**)(p + 0x14) == 0) {
    char* nb7 = (char*)FUN_00f473a0(0x6ac, "Simulator", 0, 0, 0, 0);
    char* us = nb7 ? (char*)FUN_01070ba0(nb7) : 0;
    char* oldS = *(char**)(p + 0x14);
    if (us != oldS) {
      if (us != 0) (*(void(__thiscall**)(void*))(*(void***)us + 0))(us);
      *(char**)(p + 0x14) = us;
      if (oldS != 0) (*(void(__thiscall**)(void*))(*(void***)oldS + 1))(oldS);
    }
    FUN_01073700(*(void**)(p + 0x14));
  }
  if (*(void**)(p + 0x18) == 0) {
    char* nb8 = (char*)FUN_00f473a0(0x128, "Simulator", 0, 0, 0, 0);
    char* o8 = nb8 ? (char*)FUN_010762e0(nb8) : 0;
    char* old8 = *(char**)(p + 0x18);
    if (o8 != old8) {
      if (o8 != 0) (*(void(__thiscall**)(void*))(*(void***)o8 + 0))(o8);
      *(char**)(p + 0x18) = o8;
      if (old8 != 0) (*(void(__thiscall**)(void*))(*(void***)old8 + 1))(old8);
    }
    FUN_01075490(*(void**)(p + 0x18));
  }
  FUN_00b22960(FUN_00b3d300());

  if (a1[0] != 0 && *(int*)(a1 + 0x58) != 0) {
    char* uf = (char*)FUN_00ffbe50();
    char* inv = (char*)FUN_00a1ad60(uf);
    if (inv != 0) {
      FUN_00c37180(inv, a1 + 0x58, 1);
    }
  }
  FUN_00fe7160(*(void**)(p + 0x30));
  FUN_00bc3130(p + 0x90);
  FUN_010060d0(self);
  FUN_00f67d90(FUN_00b3d300());
  FUN_00c75a50((void*)0);
  FUN_01005d80(self, 1, 1);
  FUN_008de1a0();

  if (*(void**)(p + 0x44) == 0) {
    char* nb9 = (char*)FUN_00926020(0xc, 0, 0, 0, 0, 0);
    char* b9 = nb9 ? (char*)FUN_00998820(nb9) : 0;
    char* old9 = *(char**)(p + 0x44);
    if (b9 != old9) {
      if (b9 != 0) (*(void(__thiscall**)(void*))(*(void***)b9 + 1))(b9);
      *(char**)(p + 0x44) = b9;
      if (old9 != 0) (*(void(__thiscall**)(void*))(*(void***)old9 + 2))(old9);
    }
    void* rm = FUN_0067dcd0();
    (*(void(__thiscall**)(void*, int, char*, int))(*(void***)rm + 0x44 / 4))(rm, 1, *(char**)(p + 0x44), 0);
  }
}

// ======================================================================
// 0x01007430 - SP::cSPSimulatorSpaceGame::PostLoad. thiscall.
// ======================================================================

// @ 0x01007430
void __fastcall FUN_01007430(void* self, void* /*edx*/) {
  char* p = (char*)self;

  void* tick = FUN_00b3d330();
  (*(void(__thiscall**)(void*, void*))(*(void***)tick + 0x50 / 4))(tick, self);
  FUN_00b6a530();

  char* handler = (p != 0) ? p + 0x10 : 0;
  char* srv = (char*)FUN_00883860();
  *(char**)(p + 0x58) = srv;
  *(char**)(p + 0x5c) = handler;
  *(u32*)(p + 0x60) = 0x014952a0;
  *(u32*)(p + 0x64) = 0x2f;
  *(u32*)(p + 0x68) = 0;
  if (srv != 0 && handler != 0) {
    for (u32 off = 0; off < 0xbc; off += 4) {
      u32 v = *(u32*)(0x014952a0 + off);
      (*(void(__thiscall**)(void*, char*, u32))(*(void***)srv + 0x24 / 4))(srv, handler, v);
    }
  }

  if (*(void**)(p + 0x54) != 0) {
    FUN_00ff5b50(*(void**)(p + 0x54));
  }

  char* uf = (char*)FUN_00ffbe50();
  char* oldU = *(char**)(p + 0xb4);
  if (uf != oldU) {
    if (uf != 0) (*(void(__thiscall**)(void*))(*(void***)uf + 1))(uf);
    *(char**)(p + 0xb4) = uf;
    if (oldU != 0) (*(void(__thiscall**)(void*))(*(void***)oldU + 2))(oldU);
  }
  FUN_00ffbf60(*(void**)(p + 0xb4));

  char* mm = (char*)FUN_00feb9f0();
  char* oldM = *(char**)(p + 0xb8);
  if (mm != oldM) {
    if (mm != 0) (*(void(__thiscall**)(void*))(*(void***)mm + 1))(mm);
    *(char**)(p + 0xb8) = mm;
    if (oldM != 0) (*(void(__thiscall**)(void*))(*(void***)oldM + 2))(oldM);
  }
  FUN_00fee310(*(void**)(p + 0xb8));

  {
    char* g = *(char**)0x016dcd54;
    char* oldG = *(char**)(p + 0xbc);
    if (g != oldG) {
      if (g != 0) (*(void(__thiscall**)(void*))(*(void***)g + 1))(g);
      *(char**)(p + 0xbc) = g;
      if (oldG != 0) (*(void(__thiscall**)(void*))(*(void***)oldG + 2))(oldG);
    }
    FUN_00b6f4c0(*(void**)(p + 0xbc));
  }
  {
    char* g = *(char**)0x016dc798;
    char* oldG = *(char**)(p + 0xc0);
    if (g != oldG) {
      if (g != 0) (*(void(__thiscall**)(void*))(*(void***)g + 1))(g);
      *(char**)(p + 0xc0) = g;
      if (oldG != 0) (*(void(__thiscall**)(void*))(*(void***)oldG + 2))(oldG);
    }
    FUN_00b6f4c0(*(void**)(p + 0xc0));
  }

  if (*(void**)(p + 0x40) != 0) {
    (*(void(__thiscall**)(void*))(*(void***)*(void**)(p + 0x40) + 0x40 / 4))(*(void**)(p + 0x40));
  }

  u32 wstr[3];
  wstr[0] = 0; wstr[1] = 0; wstr[2] = 0;
  FUN_00579a90(wstr, (const void*)0x014772a0);
  char* nb5 = (char*)FUN_00f473a0(0x2fc, "Simulator/cCommunityEditor", 0, 0, 0, 0);
  char* ce = nb5 ? (char*)FUN_00d0d200(nb5) : 0;
  char* oldC = *(char**)(p + 0x20);
  if (ce != oldC) {
    if (ce != 0) (*(void(__thiscall**)(void*))(*(void***)ce + 2))(ce);
    *(char**)(p + 0x20) = ce;
    if (oldC != 0) (*(void(__thiscall**)(void*))(*(void***)oldC + 3))(oldC);
  }
  FUN_00d0a760(*(void**)(p + 0x20), wstr, 0x54e13add, 0, (void*)1);

  if (*(void**)(p + 0x44) == 0) {
    char* nb9 = (char*)FUN_00926020(0xc, 0, 0, 0, 0, 0);
    char* b9 = nb9 ? (char*)FUN_00998820(nb9) : 0;
    char* old9 = *(char**)(p + 0x44);
    if (b9 != old9) {
      if (b9 != 0) (*(void(__thiscall**)(void*))(*(void***)b9 + 1))(b9);
      *(char**)(p + 0x44) = b9;
      if (old9 != 0) (*(void(__thiscall**)(void*))(*(void***)old9 + 2))(old9);
    }
    void* rm = FUN_0067dcd0();
    (*(void(__thiscall**)(void*, int, char*, int))(*(void***)rm + 0x44 / 4))(rm, 1, *(char**)(p + 0x44), 0);
  }
  if (*(void**)(p + 0x14) == 0) {
    char* nb7 = (char*)FUN_00f473a0(0x6ac, "Simulator", 0, 0, 0, 0);
    char* us = nb7 ? (char*)FUN_01070ba0(nb7) : 0;
    char* oldS = *(char**)(p + 0x14);
    if (us != oldS) {
      if (us != 0) (*(void(__thiscall**)(void*))(*(void***)us + 0))(us);
      *(char**)(p + 0x14) = us;
      if (oldS != 0) (*(void(__thiscall**)(void*))(*(void***)oldS + 1))(oldS);
    }
    FUN_01073700(*(void**)(p + 0x14));
  }
  FUN_00e184d0(FUN_00b3d400());

  if (*(void**)(p + 0x18) == 0) {
    char* nb8 = (char*)FUN_00f473a0(0x128, "Simulator", 0, 0, 0, 0);
    char* o8 = nb8 ? (char*)FUN_010762e0(nb8) : 0;
    char* old8 = *(char**)(p + 0x18);
    if (o8 != old8) {
      if (o8 != 0) (*(void(__thiscall**)(void*))(*(void***)o8 + 0))(o8);
      *(char**)(p + 0x18) = o8;
      if (old8 != 0) (*(void(__thiscall**)(void*))(*(void***)old8 + 1))(old8);
    }
    FUN_01075490(*(void**)(p + 0x18));
  }

  FUN_00fe7160(*(void**)(p + 0x30));
  if (FUN_00685520(2) != 0) {
    FUN_00c75a50(FUN_00f67d90(FUN_00b3d300()));
    FUN_00c32980(FUN_01021300());
  }
  FUN_01005d80(self, 0, 0);
  FUN_010060d0(self);
  FUN_0102b620();
}
