// s00be4000.cpp — SporeApp colony / defense-target tool region.
// Reconstructed from Ghidra decompiles + disassembly.
//
// cl rejects __thiscall on free functions, so every __thiscall entry point is
// declared as a member of S (methods keep the FUN_ names so run_all's substring
// match finds them).

#include <stddef.h>
#include <math.h>

inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
inline void* VCall0(void* o, int off) { return ((void* (*)(void*))VFn(o, off))(o); }

// ---- imports / runtime helpers ---------------------------------------------
extern "C" void  FUN_00be3720();                 // 0xbe3720
extern "C" void  FUN_00bf9770();                 // 0xbf9770  SP::cCivilization::GetModelTypeKey
extern "C" void  FUN_00bd1ab0();                 // 0xbd1ab0
extern "C" void* __cdecl FUN_00b3d300();         // 0xb3d300  SP::NounManager
extern "C" void  FUN_00b21340();                 // 0xb21340  cGameNounManager::GetGameDataVector
extern "C" void  FUN_00bf1780();                 // 0xbf1780
extern "C" void* __cdecl FUN_00b3d390(int*, void*, void*, int, int, int, int); // 0xb3d390 erase
extern "C" void  FUN_01050070();                 // 0x1050070 SP::cSPToolManager::UseToolStart
extern "C" void  FUN_00b25ca0();                 // 0xb25ca0  cGameNounManager::GetCivilizationList
extern "C" void* __cdecl FUN_00b3d2c0(int, int); // 0xb3d2c0  SP::RelationshipManager
extern "C" void  FUN_00d06240();                 // 0xd06240  cRelationshipManager::RecordEvent
extern "C" void* __cdecl FUN_00675250(int);      // 0x675250  AchievementsController
extern "C" void  FUN_00676710();                 // 0x676710  AwardAchievement
extern "C" void  FUN_00ca71d0();                 // 0xca71d0
extern "C" void  FUN_00bce5c0();                 // 0xbce5c0
extern "C" void  FUN_00b25f40();                 // 0xb25f40
extern "C" void  FUN_00be2e60();                 // 0xbe2e60
extern "C" void  FUN_00ae6d20();                 // 0xae6d20  vector grow
extern "C" void  FUN_00ae6a70();                 // 0xae6a70  cCitySimulator ctor
extern "C" void  FUN_00ae7100();                 // 0xae7100  AddSubsystem
extern "C" void* __cdecl FUN_00f473a0(unsigned, const char*, int, int, int, int); // 0xf473a0 EAAllocate
extern "C" void  __cdecl FUN_00f47380(void*);    // 0xf47380 operator delete
extern "C" void  FUN_00c9f250();                 // 0xc9f250
extern "C" void  FUN_00cac000();                 // 0xcac000
extern "C" int*  DAT_0167a690;                   // 0x167a690

struct Key3 { int a, b, c; };

struct S {
  void  FUN_00be4a10(void* civ);                 // 0xbe4a10
  void  FUN_00be4b30(void* civ);                 // 0xbe4b30
  void  FUN_00be41b0();                          // 0xbe41b0
  void  FUN_00be4400();                          // 0xbe4400
  char  FUN_00be4000(int* param_2, char param_3); // 0xbe4000
};

// ===========================================================================
// @ 0x00be4a10
void S::FUN_00be4a10(void* civ)
{
  if (civ != 0) {
    Key3 k = *((Key3* (__thiscall*)(void*, unsigned))FUN_00bf9770)(civ, 0x99e92f05);
    if (k.a != 0)
      ((void (__thiscall*)(void*, unsigned, Key3))FUN_00be3720)(this, 0x99e92f05, k);
    k = *((Key3* (__thiscall*)(void*, unsigned))FUN_00bf9770)(civ, 0x4e3f7777);
    if (k.a != 0)
      ((void (__thiscall*)(void*, unsigned, Key3))FUN_00be3720)(this, 0x4e3f7777, k);
    k = *((Key3* (__thiscall*)(void*, unsigned))FUN_00bf9770)(civ, 0x47c10953);
    if (k.a != 0)
      ((void (__thiscall*)(void*, unsigned, Key3))FUN_00be3720)(this, 0x47c10953, k);
    k = *((Key3* (__thiscall*)(void*, unsigned))FUN_00bf9770)(civ, 0x72c49181);
    if (k.a != 0)
      ((void (__thiscall*)(void*, unsigned, Key3))FUN_00be3720)(this, 0x72c49181, k);
  }
}

// ===========================================================================
// @ 0x00be4b30
void S::FUN_00be4b30(void* civ)
{
  char* self = (char*)this;
  self[0x2e2] = 0;
  void* u = ((void* (__thiscall*)(void*))(*(void***)civ)[0x4c / 4])(civ);

  int n = (*(int*)(self + 0x344) - *(int*)(self + 0x340)) >> 2;
  for (int i = 0; i < n; ++i) {
    void* e = ((void**)*(void**)(self + 0x340))[i];
    ((void (__thiscall*)(void*, void*))VFn(e, 0x48))(e, u);
  }

  n = (*(int*)(self + 0x358) - *(int*)(self + 0x354)) >> 2;
  for (int i = 0; i < n; ++i) {
    void* e = ((void**)*(void**)(self + 0x354))[i];
    ((void (__thiscall*)(void*, void*))VFn(e, 0x48))(e, u);
  }

  n = (*(int*)(self + 0x30c) - *(int*)(self + 0x308)) >> 2;
  for (int i = 0; i < n; ++i) {
    void* e = ((void**)*(void**)(self + 0x308))[i];
    ((void (__thiscall*)(void*, void*))VFn(e, 0x48))(e, u);
  }

  FUN_00be4a10(civ);
  ((void (__thiscall*)(void*, int))FUN_00bd1ab0)(*(void**)(self + 0x320), 1);
}

// ===========================================================================
// @ 0x00be4400
void S::FUN_00be4400()
{
  char* self = (char*)this;
  int u = ((int (__thiscall*)(void*))VFn(this, 0x4c))(this);
  void* nm = FUN_00b3d300();
  int* v = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      nm, 0xcd7d10, 0xd3d420, 0xacdff0, 0xb1e500, 0x18c43e8);
  int n = (*(int*)((char*)v + 8) - *(int*)((char*)v + 4)) >> 2;
  for (int i = 0; i < n; ++i) {
    int* elem = ((int**)((char*)v + 4))[i];
    if (((int (__thiscall*)(void*))VFn(elem, 0x4c))(elem) != u) {
      int* tool = (int*)((void* (__thiscall*)(void*, int))FUN_00bf1780)(*(void**)(self + 0x590), 8);
      char* sub = (char*)elem + 0x120;
      float* p = (float*)((void* (__thiscall*)(void*))VFn(sub, 0x2c))(sub);
      float x = p[0], y = p[1], z = p[2];
      float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-08f);
      float* q = (float*)((void* (__thiscall*)(void*))VFn(sub, 0x2c))(sub);
      float vec[3];
      vec[0] = q[0] + x * inv * 60.0f;
      vec[1] = q[1] + y * inv * 60.0f;
      vec[2] = q[2] + z * inv * 60.0f;
      char* t = *(char**)(self + 0x320);
      if (t) t += 0x34;
      void* r = FUN_00b3d390(tool, t, vec, -1, 0, 0, 1);
      ((void (__thiscall*)(void*))FUN_01050070)(r);
      ((char*)elem)[0x762] = 1;
    }
  }
}

// ===========================================================================
// @ 0x00be41b0
void S::FUN_00be41b0()
{
  char* self = (char*)this;
  int u = ((int (__thiscall*)(void*))VFn(this, 0x4c))(this);
  void* nm = FUN_00b3d300();
  int* v = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      nm, 0xcd7d10, 0xd3d420, 0xacdff0, 0xb1e500, 0x18c43e8);
  int n = (*(int*)((char*)v + 8) - *(int*)((char*)v + 4)) >> 2;
  int* tool = (int*)((void* (__thiscall*)(void*, int))FUN_00bf1780)(*(void**)(self + 0x590), 2);
  int count = 0;
  for (int i = 0; i < n; ++i) {
    int* elem = ((int**)((char*)v + 4))[i];
    if (((int (__thiscall*)(void*))VFn(elem, 0x4c))(elem) != u) {
      char* sub = (char*)elem + 0x120;
      float* p = (float*)((void* (__thiscall*)(void*))VFn(sub, 0x2c))(sub);
      float x = p[0], y = p[1], z = p[2];
      float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-08f);
      float* q = (float*)((void* (__thiscall*)(void*))VFn(sub, 0x2c))(sub);
      float vec[3];
      vec[0] = q[0] + x * inv * 10.0f;
      vec[1] = q[1] + y * inv * 10.0f;
      vec[2] = q[2] + z * inv * 10.0f;
      char* t = *(char**)(self + 0x320);
      if (t) t += 0x34;
      void* r = FUN_00b3d390(tool, t, vec, -1, 0, 0, 1);
      ((void (__thiscall*)(void*))FUN_01050070)(r);
      ++count;
      ((char*)elem)[0x762] = 1;
    }
  }
  void* nm2 = FUN_00b3d300();
  int* civs = (int*)((int* (__thiscall*)(void*))FUN_00b25ca0)(nm2);
  int m = (civs[1] - civs[0]) >> 2;
  for (int i = 0; i < m; ++i) {
    int* civ = ((int**)civs[0])[i];
    int* me = *(int**)(self + 0x590);
    if (civ != me) {
      int a = ((int (__thiscall*)(void*, int, float))VFn(me, 0x4c))(me, 0x5776d99, 1.0f);
      int b = ((int (__thiscall*)(void*))VFn(civ, 0x4c))(civ);
      void* rm = FUN_00b3d2c0(b, a);
      ((void (__thiscall*)(void*))FUN_00d06240)(rm);
    }
  }
  char c = ((char (__thiscall*)(void*))VFn((char*)self + 0x120, 0x58))((char*)self + 0x120);
  if (c != 0 && count > 0) {
    void* ctrl = FUN_00675250(0x1696afcf);
    ((void (__thiscall*)(void*))FUN_00676710)(ctrl);
  }
}

// ===========================================================================
// @ 0x00be4000
char S::FUN_00be4000(int* param_2, char param_3)
{
  void* nm = FUN_00b3d300();
  int* v = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      nm, 0xcd7d10, 0xd3d420, 0xae72d0, 0xb1e500, 0x18c6de8);
  int** p = *(int***)((char*)v + 4);
  int** end = *(int***)((char*)v + 8);
  for (;;) {
    if (p == end)
      return 0;
    int* elem = *p;
    char b;
    if (param_3 == 0)
      b = ((int (__thiscall*)(void*))VFn(elem, 0x4c))(elem)
          != ((int (__thiscall*)(void*))VFn(param_2, 0x4c))(param_2);
    else
      b = ((int (__thiscall*)(void*))VFn(elem, 0x4c))(elem)
          == ((int (__thiscall*)(void*))VFn(param_2, 0x4c))(param_2);
    if (b) {
      int* pi = (int*)((int* (__thiscall*)(void*))FUN_00ca71d0)(elem);
      int type = pi[4];
      if (type == 1) {
        int* a = *(void**)pi ? (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0xe9cb8ba) : 0;
        int* d = *(void**)pi ? (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0x436f315) : 0;
        if (a && ((int (__thiscall*)(void*))VFn(a, 0x84))(a) == (int)this)
          return 1;
        if (d) {
          int r = ((int (__thiscall*)(void*))FUN_00bce5c0)(d);
          if (r == (int)this)
            return 1;
        }
      }
      else if (type == 2) {
        if (*(void**)pi) {
          int r = ((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0xee9b2232);
          if (r && r == (int)this)
            return 1;
        }
      }
      else if (type == 3) {
        int r1 = *(void**)pi ? ((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0xee9b2232) : 0;
        int* r2 = *(void**)pi ? (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0x3d5c477) : 0;
        if (r1 && r1 == (int)this)
          return 1;
        if (r2) {
          int* r3 = (int*)((int (__thiscall*)(void*))VFn(r2, 0x30))(r2);
          int r4 = r3 ? ((int (__thiscall*)(void*, int))VFn(r3, 0xc))(r3, 0xee9b2232) : 0;
          if (r4 == (int)this)
            return 1;
        }
      }
    }
    ++p;
  }
}

// ===========================================================================
struct Vec { void** begin; void** cur; void** cap; };

static void vecPush(Vec* v, void* obj)
{
  if (v->cur < v->cap) {
    void** slot = v->cur;
    v->cur = slot + 1;
    if (slot) {
      *slot = obj;
      if (obj) ((void (__thiscall*)(void*))VFn(obj, 0xc))(obj);
    }
  } else {
    void* tmp = obj;
    ((void (__thiscall*)(void*, void**, void**))FUN_00ae6d20)(v, v->cur, &tmp);
    obj = tmp;
  }
  if (obj) ((void (__thiscall*)(void*))VFn(obj, 8))(obj);
}

// @ 0x00be45b0
void FUN_00be45b0(int param_1, int param_2)
{
  void* mgr = FUN_00b3d300();
  int* v = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      mgr, 0xcd7d10, 0xd3d420, 0xbe2e60, 0xb1e500, 0x24270c5);
  int n = (*(int*)((char*)v + 8) - *(int*)((char*)v + 4)) >> 2;
  Vec vec;
  vec.begin = 0;
  vec.cur = 0;
  vec.cap = 0;
  for (int i = 0; i < n; ++i) {
    int* elem = ((int**)((char*)v + 4))[i];
    if (param_2 == 0) {
      int* p = *(int**)(*(int*)((char*)elem + 0x518) + 0x114);
      if (p) {
        int* q = (int*)((int (__thiscall*)(void*, int))VFn(p, 0xb8))(p, 0x137e8e0);
        if (q && (*(int*)((char*)q + 0xb20) == 0 || *(int*)((char*)q + 0xb20) == 1)) {
          if (param_1 != 0) {
            int u = ((int (__thiscall*)(void*))VFn((char*)q + 0x508, 0x10))((char*)q + 0x508);
            if (((int (__thiscall*)(void*, int))FUN_00b25f40)(FUN_00b3d300(), u) != param_1)
              continue;
          }
          void* obj = (char*)elem + 0x504;
          if (obj) ((void (__thiscall*)(void*))VFn(obj, 0xc))(obj);
          vecPush(&vec, obj);
        }
      }
    } else {
      int* p5 = *(int**)((char*)elem + 0x5d8);
      if (p5) {
        int* q = (int*)((int (__thiscall*)(void*, int))VFn(p5, 0xb8))(p5, 0x17f243b);
        if (q) {
          int* a = (int*)((int (__thiscall*)(void*, int))VFn(q, 0xc))(q, 0xe9cb8ba);
          int* d = (int*)((int (__thiscall*)(void*, int))VFn(q, 0xc))(q, 0x436f315);
          if ((a && ((int (__thiscall*)(void*))VFn(a, 0x84))(a) == param_2) ||
              (d && ((int (__thiscall*)(void*))FUN_00bce5c0)(d) == param_2)) {
            void* obj = (char*)elem + 0x504;
            if (obj) ((void (__thiscall*)(void*))VFn(obj, 0xc))(obj);
            vecPush(&vec, obj);
          }
        }
      }
    }
  }
  int m = (int)((char*)vec.cur - (char*)vec.begin) >> 2;
  for (int i = 0; i < m; ++i) {
    int* obj = ((int**)vec.begin)[i];
    if (DAT_0167a690 == 0) {
      void* p = FUN_00f473a0(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
      if (p == 0)
        DAT_0167a690 = 0;
      else
        DAT_0167a690 = (int*)((int* (__thiscall*)(void*))FUN_00ae6a70)(p);
    }
    ((void (__thiscall*)(void*, void*))FUN_00ae7100)(DAT_0167a690, obj);
  }
  void* mgr2 = FUN_00b3d300();
  int* v2 = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))FUN_00b21340)(
      mgr2, 0xcd7d10, 0xd3d420, 0xae72d0, 0xb1e500, 0x18c6de8);
  int n2 = (*(int*)((char*)v2 + 8) - *(int*)((char*)v2 + 4)) >> 2;
  for (int i = 0; i < n2; ++i) {
    int* elem = ((int**)((char*)v2 + 4))[i];
    int t = *(int*)((char*)elem + 0xb20);
    if (t == 0 || t == 1) {
      if (param_1 != 0) {
        int u = ((int (__thiscall*)(void*))VFn((char*)elem + 0x508, 0x10))((char*)elem + 0x508);
        if (((int (__thiscall*)(void*, int))FUN_00b25f40)(FUN_00b3d300(), u) != param_1)
          continue;
      }
      int* pi = (int*)((int* (__thiscall*)(void*))FUN_00ca71d0)(elem);
      if (pi[4] == (t != 0) + 2) {
        int* r2 = 0;
        if (*(void**)pi) r2 = (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0x3d5c477);
        if (param_2 == 0 || *(int*)pi == param_2) {
          ((void (__thiscall*)(void*))FUN_00c9f250)(elem);
          ((void (__thiscall*)(void*, int, int, int))FUN_00cac000)(elem, 0, 0xc, 0);
        } else if (r2) {
          int* r3 = (int*)((int (__thiscall*)(void*))VFn(r2, 0x30))(r2);
          int ok;
          if (r3 == 0)
            ok = (param_2 == 0);
          else
            ok = (((int (__thiscall*)(void*, int))VFn(r3, 0xc))(r3, 0xee9b2232) == param_2);
          if (ok) {
            ((void (__thiscall*)(void*))FUN_00c9f250)(elem);
            ((void (__thiscall*)(void*, int, int, int))FUN_00cac000)(elem, 0, 0xc, 0);
          }
        }
      } else if (pi[4] == 1) {
        int* a = 0;
        int* d = 0;
        if (*(void**)pi) a = (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0xe9cb8ba);
        if (*(void**)pi) d = (int*)((int (__thiscall*)(void*, int))VFn(*(void**)pi, 0xc))(*(void**)pi, 0x436f315);
        if (a && ((int (__thiscall*)(void*))VFn(a, 0x84))(a) == param_2) {
          ((void (__thiscall*)(void*))FUN_00c9f250)(elem);
          ((void (__thiscall*)(void*, int, int, int))FUN_00cac000)(elem, 0, 0xc, 0);
        } else if (d && ((int (__thiscall*)(void*))FUN_00bce5c0)(d) == param_2) {
          ((void (__thiscall*)(void*))FUN_00c9f250)(elem);
          ((void (__thiscall*)(void*, int, int, int))FUN_00cac000)(elem, 0, 0xc, 0);
        }
      }
    }
  }
  for (void** pp = vec.begin; pp != vec.cur; ++pp) {
    void* o = *pp;
    if (o) ((void (__thiscall*)(void*))VFn(o, 8))(o);
  }
  if (vec.begin && ((int*)vec.begin)[-1] != 0)
    FUN_00f47380(vec.begin);
}
