// Slice s01050070 (0x01050070..0x01050baa) — SP::cSPToolManager tool-use.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc)

#include "types.h"
#include <string.h>

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef __int64        int64;
typedef unsigned __int64 uint64;

#define VT(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

// ---------------------------------------------------------------------------
// Helper objects / externs shared by the functions in this slice.
// ---------------------------------------------------------------------------
struct cSPTimer;

struct cSPUISpace {
  void ShowToolChargeBar();                                      // 0x01065ea0
  void HideToolChargeBar();                                      // 0x01065ed0
};

struct cSPSimulatorSpaceGame {
  int* GetPlayerInventory();                                     // 0x00a1ad60
};

struct Msg {                       // message posted to the FX system
  char   pad00[0x04];              // +0x00..0x03
  float  m04;                      // +0x04
  int    m08;                      // +0x08
  int    m0c;                      // +0x0c
  ushort m0e;                      // +0x0e
  ushort m10;                      // +0x10
  short  m12;                      // +0x12
  int    m14;                      // +0x14
  int    m18;                      // +0x18
  int    m1c[9];                   // +0x1c..0x3f (matrix)
  void   ctor();                   // 0x00434040
};

void* __cdecl eOperatorNew(unsigned size, const char* name, int a, int b,
                           const char* file, int line);          // 0x00f473a0
void  __cdecl eOperatorDeleteArray(void* p);                     // 0x00f47380
void  __cdecl FUN_0104f140(void* a, uint b, void* c);            // 0x0104f140
void  __cdecl FUN_0104f100(void* a, void* b, void* c, void* d, void* e); // 0x0104f100
void  __cdecl FUN_0104f1b0(void* a, void* b, void* c);           // 0x0104f1b0
void  __cdecl FUN_0104f900(void* a, void* b, void* c);           // 0x0104f900
void  __cdecl FUN_006606a0(void* a);                             // 0x006606a0
bool  __cdecl SP_GetPropertyAsKeyInstance(int obj, uint key, int* out); // 0x006a12a0
void* __cdecl SP_EffectsManager();                               // 0x0067ddd0
void  __cdecl FUN_0104fcd0(void* p);                             // 0x0104fcd0
void  __cdecl PtrField_assign(void* p);                          // 0x00ad7ec0
void* __cdecl GetUFOSimulator();                                 // 0x00ffbe50
int*  __cdecl QuaternionToMatrix(void* out, int quat);           // 0x004a9b40
void* __cdecl GetCurrentGameMode();                              // 0x00b5b800
void* __cdecl FUN_010666a0();                                    // 0x010666a0
void* __cdecl MessageServer();                                   // 0x0067dcc0
void* __cdecl SpaceGameGet();                                    // 0x01002bd0
void  __cdecl FUN_00ff4540(void* p);                             // 0x00ff4540
void  __cdecl FUN_00c31a00(int a);                               // 0x00c31a00
void  __cdecl FUN_00c389f0(float a);                             // 0x00c389f0

struct cInventory { char pad00[0x34]; void* m34; };              // player inventory view

void* __cdecl GetPlayerEmpire();                                 // cSPLivingUniverse::GetPlayerEmpire

extern char DAT_01654c05;              // current game-mode identity

// ---------------------------------------------------------------------------
// cSPTimer — 0x20-byte timer object (methods only; padding fixes the size).
// ---------------------------------------------------------------------------
struct cSPTimer {
  char   pad[0x20];              // +0x00..0x1f
  void   Restart();              // 0x00bc3130
  void   Stop();                 // 0x00bc3170
  uint64 GetElapsedTime();       // 0x00bc3190
  bool   IsRunning();            // 0x00feba90
};

struct cSPToolManager;

// ---------------------------------------------------------------------------
// cProperty — property object (only the fields needed here).
// ---------------------------------------------------------------------------
struct cProperty {
  char     pad00[0x12];          // +0x00..0x11
  ushort   m12;                  // +0x12
  char*    GetBool();            // 0x0041e920
};

// EA/eastl array allocations store their element count 4 bytes before the returned buffer;
// operator delete[] inspects that header before freeing.
struct ArrayHeader { int count; };   // +0x00: element count; buffer begins at +0x04

cSPToolManager* __cdecl FUN_00b3d390();              // 0x00b3d390
void __cdecl DoChargeEffects(cSPToolManager* self);  // 0x0104ea80

// ---------------------------------------------------------------------------
// cSPToolManager — only the fields touched by this slice.
// ---------------------------------------------------------------------------
struct cSPToolManager {
  char     pad00[0x0c];          // +0x00..0x0b
  char     m0c_sub[0x24];        // +0x0c..0x2f embedded effect-target owner object
  void*    m30;                  // +0x30
  char     pad34[0x48];          // +0x34..0x7b
  int      m7c;                  // +0x7c
  char     m80;                  // +0x80
  char     pad81[0x07];          // +0x81..0x87
  cSPTimer mTimer88;             // +0x88
  cSPTimer mTimerA8;             // +0xa8
  cSPTimer mTimerC8;             // +0xc8
  char     padE8[0x20];          // +0xe8..0x107
  void*    m108;                 // +0x108
  void*    m10c;                 // +0x10c
  void*    m110;                 // +0x110
  void*    m114;                 // +0x114
  void*    m118;                 // +0x118
  int      m11c;                 // +0x11c
  char     pad120[0x1c];         // +0x120..0x13b
  char     m13c;                 // +0x13c
  char     pad13d[0x33];         // +0x13d..0x16f
  void*    m170;                 // +0x170
  uint     m174;                 // +0x174
  void*    m178;                 // +0x178
  char     pad17c[0x20];         // +0x17c..0x19b
  int      m19c;                 // +0x19c
  char     pad1a0[0x04];         // +0x1a0..0x1a3
  int      m1a4;                 // +0x1a4
  float    m1a8;                 // +0x1a8
  char     pad1ac[0x14];         // +0x1ac..0x1bf
  float    m1c0;                 // +0x1c0
  float    m1c4;                 // +0x1c4
  char     pad1c8[0x0c];         // +0x1c8..0x1d3
  float    m1d4;                 // +0x1d4

  bool  FUN_0104fe50();          // 0x0104fe50
  bool  FUN_0104feb0();          // 0x0104feb0
  void* Lookup(uint key);        // 0x0104f850
  void  UseToolStop(cSPToolManager* self);                                   // 0x0104fa90
  char  UseToolStart(cSPToolManager* self, int a2, int a3, int a4, int a5,
                     int a6, int a7);                                        // 0x01050070
  char  UseToolUpdate(cSPToolManager* self, int a2, int a3, int a4);         // 0x010504a0
  int*  CreateGenericToolEffect(cSPToolManager* self);                      // 0x01050640
};

// ---------------------------------------------------------------------------
// cVec14 — eastl-style vector of 0x14-byte elements (begin/end/cap at +0/+4/+8).
// ---------------------------------------------------------------------------
struct cVec14 {
  char* begin;                   // +0x00
  char* end;                     // +0x04
  char* cap;                     // +0x08
  void  insert(void* pos, uint count, void* val);   // 0x01050850
};

// ===========================================================================
// @ 0x01050a60  FUN_01050a60
// ===========================================================================
float __fastcall FUN_01050a60(cSPToolManager* self) {
  float r = 0.0f;
  if (!self->FUN_0104fe50() && !self->FUN_0104feb0()) {
    int a = (int)(self->m1c0 * 1000.0f);
    if (a < 0)
      a = -1;
    float fa = (float)a;
    int b = (int)(self->m1c4 * 1000.0f);
    if (b < 0)
      b = -1;
    float fb = (float)b;
    if (fb > 0.0f) {
      if (self->mTimerA8.IsRunning()) {
        uint64 t = self->mTimerA8.GetElapsedTime();
        r = (float)((double)t / fb);
      }
    }
    if (fa > 0.0f) {
      if (self->mTimer88.IsRunning()) {
        uint64 t = self->mTimer88.GetElapsedTime();
        r = (float)((double)t / fa);
      }
    }
    if (r > 1.0f)
      r = 0.0f;
  }
  return r;
}

// ===========================================================================
// @ 0x010504a0  SP::cSPToolManager::UseToolUpdate
// ===========================================================================
char cSPToolManager::UseToolUpdate(cSPToolManager* self, int a2, int a3, int a4) {
  cSPToolManager* mgr = this;
  void* piVar4;
  if (self->m178) {
    piVar4 = FUN_00b3d390()->Lookup((uint)self->m178);
    if (!piVar4)
      piVar4 = FUN_00b3d390()->Lookup(0xb0da49d9);
  } else {
    piVar4 = FUN_00b3d390()->Lookup(0xb0da49d9);
  }
  if (piVar4)
    ((void(__thiscall*)(void*))VT(piVar4, 0))(piVar4);

  void* p30 = self->m30;
  char flag = 0;
  if (p30) {
    void* prop;
    if (((bool(__thiscall*)(void*, uint, void**))VT(p30, 0x24))(p30, 0x341eb76, &prop)
        && ((cProperty*)prop)->m12 == 1
        && *((cProperty*)prop)->GetBool() != 0
        && self->m13c != 0) {
      mgr->UseToolStop(self);
      if (piVar4)
        ((void(__thiscall*)(void*))VT(piVar4, 4))(piVar4);
      return 0;
    }
  }
  ((void(__thiscall*)(void*, void*, void*))VT(piVar4, 0x28))(piVar4, self, (void*)a2);
  DoChargeEffects(self);
  int f = (int)(self->m1d4 * 1000.0f);
  uint64 el = self->mTimerC8.GetElapsedTime();
  if (el >= (uint64)(int64)f || f <= 0) {
    int g = (int)(self->m1c4 * 1000.0f);
    if (g < 0)
      g = -1;
    cSPTimer& t = self->mTimerA8;
    if (!t.IsRunning() || (g > -1 && t.GetElapsedTime() >= (uint64)(int64)g)) {
      flag = mgr->UseToolStart(self, (int)self->m114, a2, a3, a4, (int)self->m118, 1);
      if (!flag)
        mgr->UseToolStop(self);
    }
  }
  if (piVar4)
    ((void(__thiscall*)(void*))VT(piVar4, 4))(piVar4);
  return flag;
}

// ===========================================================================
// @ 0x01050850  FUN_01050850 — vector<0x14-byte>::insert (best-effort)
// ===========================================================================
void cVec14::insert(void* pos, uint count, void* val) {
  if ((uint)((end - begin) / 0x14) < count) {
    int   oldn = (int)((end - begin) / 0x14);
    uint  cap2 = (uint)oldn * 2;
    if (oldn == 0)
      cap2 = 1;
    uint  newcap = (uint)oldn + count;
    if (newcap < cap2)
      newcap = cap2;
    char* nb;
    if (newcap == 0)
      nb = 0;
    else
      nb = (char*)eOperatorNew(newcap * 0x14, "Simulator", 0, 0,
                               (const char*)0x13ebb38, 0xd1);
    int   s6  = (int)pos - (int)begin;
    char* p1  = (char*)memcpy(nb, begin, (size_t)s6);
    char* p2  = p1 + (s6 / 0x14) * 0x14;
    FUN_0104f140(p2, count, val);
    int   s6b = (int)end - (int)pos;
    char* p3  = (char*)memcpy(p2 + count * 0x14, pos, (size_t)s6b);
    if (begin != 0 && ((ArrayHeader*)begin - 1)->count != 0)
      eOperatorDeleteArray(begin);
    begin = nb;
    end   = p3 + (s6b / 0x14) * 0x14;
    cap   = nb + newcap * 0x14;
  } else if (count != 0) {
    int local14[5];
    FUN_006606a0(val);
    uint  u4 = (uint)((end - (char*)pos) / 0x14);
    char* e  = end;
    char* p7;
    if (count < u4) {
      char* p5 = end - count * 0x14;
      FUN_0104f100(&val, p5, end, end, pos);
      end = end + count * 0x14;
      FUN_0104f1b0(pos, p5, e);
      p7 = (char*)(count * 0x14 + (int)pos);
    } else {
      FUN_0104f140(end, count - u4, local14);
      end = end + (count - u4) * 0x14;
      FUN_0104f100(&pos, pos, e, end, pos);
      end = end + u4 * 0x14;
      p7  = e;
    }
    FUN_0104f900(pos, p7, local14);
    if (local14[0] != 0 && (((ArrayHeader*)(void*)local14[0]) - 1)->count != 0)
      eOperatorDeleteArray((void*)local14[0]);
  }
}

// ===========================================================================
// @ 0x01050640  SP::cSPToolManager::CreateGenericToolEffect (best-effort)
// ===========================================================================
int* cSPToolManager::CreateGenericToolEffect(cSPToolManager* self) {
  if (!self->m30)
    return 0;
  int local64[5];
  if (!SP_GetPropertyAsKeyInstance((int)self->m30, 0x306c86ef, local64))
    return 0;

  void* src = 0;
  void* effects = SP_EffectsManager();
  if (src) {
    src = 0;
    ((void(__thiscall*)(void*))VT(src, 4))(src);
  }
  if (!((char(__thiscall*)(void*, int, int, void**))VT(effects, 0x2c))
          (effects, local64[0], 0, &src))
    return 0;

  ((void(__thiscall*)(void*, int, void*))VT(src, 0x4c))(src, 1, self->m0c_sub);

  Msg msg;
  msg.ctor();                                       // 0x00434040

  void* m114 = self->m114;
  void* quat = ((void*(__thiscall*)(void*))VT(m114, 0x30))(m114);
  QuaternionToMatrix(&msg.m1c[0], (int)quat);
  msg.m10 = (ushort)(msg.m10 | 2);
  msg.m12 = (short)(msg.m12 + 1);

  int* v3 = (int*)((int*(__thiscall*)(void*))VT(m114, 0x2c))(m114);
  msg.m14 = v3[0];
  msg.m18 = v3[1];
  msg.m04 = (float)v3[2];
  msg.m10 = (ushort)(msg.m10 | 4);
  msg.m12 = (short)(msg.m12 + 1);

  ((void(__thiscall*)(void*, Msg*))VT(src, 0x18))(src, &msg);

  float fVar10 = 1.0f;
  if (m114 &&
      ((int(__thiscall*)(void*, uint))VT(m114, 0xb8))(m114, 0xb033b403) != 0) {
    cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)GetUFOSimulator();
    int* inv = sim->GetPlayerInventory();
    void* ph = inv ? ((cInventory*)inv)->m34 : 0;
    fVar10 = ((float(__thiscall*)(void*))VT(ph, 0x34))(ph);
  }
  msg.m0e = (ushort)(msg.m0e + 1);
  msg.m04 = fVar10;
  ((void(__thiscall*)(void*, Msg*))VT(src, 0x18))(src, &msg);
  ((void(__thiscall*)(void*, int))VT(src, 8))(src, 0);

  int local1c = 0;
  FUN_0104fcd0(&local1c);
  PtrField_assign(&self->m114);
  if (local1c)
    ((void(__thiscall*)(void*))VT((void*)local1c, 4))((void*)local1c);
  return (int*)local1c;
}

// ===========================================================================
// @ 0x01050070  SP::cSPToolManager::UseToolStart (best-effort)
// ===========================================================================
char cSPToolManager::UseToolStart(cSPToolManager* self, int a2, int a3, int a4,
                                  int a5, int a6, int a7) {
  char cVar4 = 0;

  void* tool = 0;
  if (self->m178)
    tool = FUN_00b3d390()->Lookup((uint)self->m178);
  if (!tool)
    tool = FUN_00b3d390()->Lookup(0xb0da49d9);
  void* piVar5 = ((void*(__thiscall*)(void*, int))VT(tool, 0x44))(tool, self->m1a4);

  self->m13c = 0;
  void* p6 = 0;
  if (self->m178)
    p6 = FUN_00b3d390()->Lookup((uint)self->m178);
  if (!p6) {
    p6 = FUN_00b3d390()->Lookup(0xb0da49d9);
  } else {
    ((void(__thiscall*)(void*))VT(p6, 0))(p6);
  }

  void* old114 = self->m114;
  if ((void*)self != old114) {
    if (self)
      ((void(__thiscall*)(void*))VT(self, 0xbc))(self);
    self->m114 = self;
    if (old114)
      ((void(__thiscall*)(void*))VT(old114, 0xc0))(old114);
  }
  self->m11c = a3;

  cVar4 = ((char(__thiscall*)(void*, void*, int))VT(p6, 0x24))(p6, (void*)a2, a7);
  if (cVar4 != 0) {
    self->m170 = 0;
    void* pv = 0;
    if (a2 != 0 &&
        (pv = ((void*(__thiscall*)(void*, uint))VT((void*)a2, 0xb8))((void*)a2, 0x17f243b)) != 0 &&
        ((char(__thiscall*)(void*))VT(pv, 0x2c))(pv) != 0) {
      a2 = 0;
    }
    void* old118 = self->m118;
    if ((void*)a2 != old118) {
      if (a2)
        ((void(__thiscall*)(void*))VT((void*)a2, 0xbc))((void*)a2);
      self->m118 = (void*)a2;
      if (old118)
        ((void(__thiscall*)(void*))VT(old118, 0xc0))(old118);
    }

    float fVar2 = self->m1d4;
    if (0 < (int)(fVar2 * 1000.0f)) {
      cSPTimer* tC8 = &self->mTimerC8;
      uint64 el = tC8->GetElapsedTime();
      if (el < (uint64)(int64)(int)(fVar2 * 1000.0f)) {
        if (!tC8->IsRunning()) {
          if (GetCurrentGameMode() == &DAT_01654c05) {
            cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)GetUFOSimulator();
            int* inv = sim->GetPlayerInventory();
            int* ip = inv ? (int*)((cInventory*)inv)->m34 : 0;
            if ((int*)self->m114 == ip)
              ((cSPUISpace*)FUN_010666a0())->ShowToolChargeBar();
          }
          tC8->Restart();
        }
        goto L262;
      }
    }

    if (GetCurrentGameMode() == &DAT_01654c05) {
      cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)GetUFOSimulator();
      int* inv = sim->GetPlayerInventory();
      int* ip = inv ? (int*)((cInventory*)inv)->m34 : 0;
      if ((int*)self->m114 == ip) {
        void** pk = &self->m108;
        for (int i = 3; i != 0; i--, pk++) {
          if (*pk != 0) {
            ((void(__thiscall*)(void*, int))VT(*pk, 0xc))(*pk, 0);
            void* pv2 = *pk;
            if (pv2) {
              *pk = 0;
              ((void(__thiscall*)(void*))VT(pv2, 4))(pv2);
            }
          }
        }
        ((cSPUISpace*)FUN_010666a0())->HideToolChargeBar();
      }
    }

    cVar4 = ((char(__thiscall*)(void*, int, void*))VT(piVar5, 0x34))(piVar5, 0, self);
    if (cVar4 != 0) {
      int iv = (int)(self->m1c4 * 1000.0f);
      if (iv < 0)
        iv = -1;
      if (0.0f <= (float)iv)
        self->mTimerA8.Stop();
      else
        self->mTimer88.Restart();
      self->mTimerA8.Restart();
      self->m80 = 1;

      if ((((uint)self->m174 >> 5) & 1) != 0) {
        self->m7c = self->m7c - self->m19c;
        if (GetCurrentGameMode() == &DAT_01654c05) {
          cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)GetUFOSimulator();
          int* inv = sim->GetPlayerInventory();
          int* ip = inv ? (int*)((cInventory*)inv)->m34 : 0;
          if ((int*)self->m114 == ip) {
            void* ms = MessageServer();
            ((void(__thiscall*)(void*, uint, void*, int))VT(ms, 0x14))(ms, 0x635ae7e, self, 0);
            if (self->m7c < 1) {
              cSPSimulatorSpaceGame* s2 = (cSPSimulatorSpaceGame*)SpaceGameGet();
              if (s2->GetPlayerInventory() != 0)
                FUN_00ff4540(self);
            }
          }
        }
      }

      if (GetCurrentGameMode() == &DAT_01654c05) {
        cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)GetUFOSimulator();
        int* inv = sim->GetPlayerInventory();
        int* ip = inv ? (int*)((cInventory*)inv)->m34 : 0;
        if ((int*)self->m114 == ip) {
          int   esi = 0;
          float ebp = 0.0f;
          if ((int)(self->m1c4 * 1000.0f) == 0) {
            float fv = (float)(int)self;
            if ((int)self < 0)
              fv = fv + 4.2949673e+09;
            ebp = (fv * 0.001f) * ebp;
            esi = (int)((float)esi * (fv * 0.001f));
          }
          GetPlayerEmpire();
          FUN_00c31a00(-esi);
          if ((int*)self->m114 != 0)
            ((void(__thiscall*)(void*, uint))VT(self->m114, 0xb8))(self->m114, 0xb033b403);
          FUN_00c389f0(-ebp);
        }
      }
    }
  }

L262:
  ((void(__thiscall*)(void*))VT(piVar5, 4))(piVar5);
  return cVar4;
}