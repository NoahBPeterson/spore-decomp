// SP::cSPPlayMode play-mode subsystem (SporeEP1_RL). Region 0x629c50-0x62abc5.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

static inline void** Vt(void* p) { return *(void***)p; }
static inline void Release2(void* p) { if (p) ((void(__thiscall*)(void*))Vt(p)[2])(p); }

struct cSPPlayMode { char pad[0x3620]; };

// external callees
void* __cdecl FUN_0062cb20(const float* p, float a, int b, float c);   // 0x62cb20
void  __cdecl FUN_0062cb90();                                        // 0x62cb90
void  __cdecl FUN_006289a0();                                        // 0x6289a0
void* __cdecl PropertyManager();                                     // 0x67dd? 
void* __cdecl ModelManager();                                        // 0x67dd80
void  __cdecl SetAllBabySitUp(cSPPlayMode* m);                       // 0x628? 
uint32_t __cdecl GetMouthPartIdx(cSPPlayMode* m);                    // 0x628a80
void  __cdecl cSPEditorAnimMgr_GetCreature(char* cm, void* id);      // 0x59ca70
void  __cdecl FUN_00478db0(void* p);

struct Mgr029 {
  void* Find(int id);        // 0x9cab60
  void  Remove(void* p);     // 0x9cb460
};

void SetBabySitState(cSPPlayMode* m, uint32_t index);
void WakeupCreature(cSPPlayMode* m);

// @ 0x00629d90
void __stdcall FUN_00629d90(int arg1, int arg2) {
  if (arg2 == -1) return;
  void* v = (*(Mgr029**)(arg1 + 0x17c))->Find(arg2);
  if (v == 0) return;
  if (*(void**)((char*)v + 0x8c)) {
    void* o = *(void**)((char*)v + 0x8c);
    ((void(__thiscall*)(void*, int))Vt(o)[3])(o, 1);
  }
  (*(Mgr029**)(arg1 + 0x17c))->Remove(v);
}

// @ 0x0062ab80
void SetAllBabySitState(cSPPlayMode* m) {
  char* cm = *(char**)((char*)m + 0x3610);
  int n = (*(int*)(cm + 0x370) - *(int*)(cm + 0x36c)) / 0x30;
  for (int i = 0; i < n; ++i) SetBabySitState(m, (uint32_t)i);
}

// @ 0x0062aa90
void SetBabySitState(cSPPlayMode* m, uint32_t index) {
  char* cm = *(char**)((char*)m + 0x3610);
  char* vec = *(char**)(cm + 0x36c);
  int n = (*(int*)(cm + 0x370) - (int)vec) / 0x30;
  void* id = (index < (uint32_t)n) ? *(void**)(vec + index * 0x30) : *(void**)vec;
  int off = index * 0x30;
  if (*(int*)(vec + off + 0x2c) != -1) {
    cSPEditorAnimMgr_GetCreature(*(char**)(cm + 0x360), id);
    int h = *(int*)(vec + off + 0x2c);
    if (h != -1) {
      Mgr029* mgr = *(Mgr029**)((char*)m + 0x3610);
      (void)mgr;
      void* v = 0;
      if (v) {
        if (*(void**)((char*)v + 0x8c)) {
          void* o = *(void**)((char*)v + 0x8c);
          ((void(__thiscall*)(void*, int))Vt(o)[3])(o, 1);
        }
      }
    }
    *(int*)(vec + off + 0x2c) = -1;
  }
  *(uint32_t*)(vec + off + 0x24) = 0;
  *(uint32_t*)(vec + off + 0x28) = 0;
  *(uint8_t*)(vec + off + 0x1c) = 0;
}

// @ 0x0062a360
bool HasActivePath(cSPPlayMode* m, int creatureID) {
  char* cm = *(char**)((char*)m + 0x3610);
  int n = (*(int*)(cm + 0x370) - *(int*)(cm + 0x36c)) / 0x30;
  char* begin = *(char**)(cm + 0x36c);
  int i = 0;
  while (*(int*)(*(char**)(begin + i * 4) + 0x1c) != creatureID) {
    ++i;
    if ((unsigned)i >= (unsigned)n) return false;
  }
  if ((unsigned)i < (unsigned)n) {
    char* c = *(char**)(begin + i * 4);
    if (*(float*)(c + 0x34) > 0.0f) return true;
    char* c0 = *(char**)begin;
    if (*(char*)(c0 + 0x24) != 0 && *(char*)(c + 0x24) != 0) return true;
  }
  return false;
}

// @ 0x0062a760
void WakeupCreature(cSPPlayMode* m) {
  if (*(char*)((char*)m + 0x1f0) != 0) {
    void* ui = *(void**)((char*)m + 0x1f8);
    if (ui != 0) {
      ((void(__thiscall*)(void*))Vt(ui)[3])(ui);
      ui = *(void**)((char*)m + 0x1f8);
      if (ui != 0) {
        *(void**)((char*)m + 0x1f8) = 0;
        ((void(__thiscall*)(void*))Vt(ui)[1])(ui);
      }
    }
  }
  uint8_t b = *(uint8_t*)((char*)m + 0x1f1);
  *(void**)((char*)m + 0x200) = 0;
  *(float*)((char*)m + 0x1f4) = 0.0f;
  *(uint8_t*)((char*)m + 0x1f0) = 0;
  if (b > 1) {
    if (b == 3) { /* effect trigger; see partial.txt */ }
    *(uint8_t*)((char*)m + 0x1f1) = 0;
    *(int*)((char*)m + 0x1fc) = 0;
    SetAllBabySitUp(m);
  }
}

// @ 0x0062a7f0
uint8_t OnMouseDown(cSPPlayMode* m, void* a, void* b, void* c, void* d) {
  WakeupCreature(m);
  *(uint8_t*)((char*)m + 0x1f) = 0;
  *(uint8_t*)((char*)m + 0x20) = 0;
  *(uint32_t*)((char*)m + 0x34) = 0;
  *(uint32_t*)((char*)m + 0x38) = 0;
  uint8_t r = 0;
  int* p = (int*)((char*)m + 0xc8);
  for (int i = 4; i != 0; --i, ++p) {
    if (*p != 0) {
      uint8_t x = ((uint8_t(__thiscall*)(void*, void*, void*, void*, void*))Vt((void*)*p)[6])
                      ((void*)*p, a, b, c, d);
      r = (uint8_t)(r | x);
    }
  }
  return r;
}

// @ 0x0062a230
void SetBabyPath(cSPPlayMode* m, uint32_t id, float x, float y, float z) {
  char* begin = *(char**)((char*)m + 0x7c);
  char* end = *(char**)((char*)m + 0x80);
  uint32_t n = (uint32_t)((end - begin) >> 2);
  uint32_t i = 0;
  for (; i < n; ++i)
    if (*(int*)(*(char**)(begin + i * 4) + 0x1c) == (int)id) break;
  if (i >= n) return;
  char* c = *(char**)(begin + i * 4);
  char* data = *(char**)(c + 0x10);
  if (data == 0) return;
  if (((*(float*)(data + 0x38) != x) || (*(float*)(data + 0x3c) != y)) || z != 0.0f) {
    FUN_0062cb90();
    void* t = FUN_0062cb20(&x, 1.0f, 0, 0.5f);
    *(uint8_t*)((char*)t + 0x2a) = 1;
    (void)t;
  }
}

// @ 0x0062a990
void BabyStartSocialCallEffect(cSPPlayMode* m) {
  uint32_t idx = GetMouthPartIdx(m);
  if (idx == 0xffffffffu) return;
}

// @ 0x0062a550
void FUN_0062a550(cSPPlayMode* m) { (void)m; }
// @ 0x0062a860
void SetupFromConfigFile(cSPPlayMode* m) {
  Release2(*(void**)((char*)m + 0x1b8));
  *(void**)((char*)m + 0x1b8) = 0;
  (void)PropertyManager();
  (void)ModelManager();
}
// @ 0x0062a3d0
void PlayMode_Init(cSPPlayMode* m, void* a, uint8_t b) {
  *(void**)((char*)m + 0x3624) = a;
  *(uint8_t*)((char*)m + 0x3628) = b;
}
// @ 0x0062a1a0
void StopWalk(cSPPlayMode* m, void* a, int b) { (void)m; (void)a; (void)b; }
// @ 0x00629de0
void FUN_00629de0(cSPPlayMode* m) { (void)m; }
// @ 0x00629c50
void FUN_00629c50(cSPPlayMode* m) { (void)m; }
