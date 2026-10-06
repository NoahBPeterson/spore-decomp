// Slice s00e53c70 (batch bfs3, slice 18). Region 0xe53c70-0xe54bf6.
// Cell-game medal/save UI glue. Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

struct cGuard18 { void* p; cGuard18(); ~cGuard18(); };

extern "C" {
  void*  __cdecl FUN_00b721d0(int id);
  void   __cdecl FUN_00e82690(int id, float v);
  void   __cdecl FUN_00e53660(int a, int b);
  void   __cdecl FUN_00e53b40();
  void   __cdecl FUN_00e539c0();
  void   __cdecl FUN_00e4fca0();
  void*  __cdecl FUN_0067de90(int a);
  void   __cdecl FUN_007ebce0(void* a);
  void*  __cdecl SP_MessageServer();
  void   __cdecl SP_PatchSoundStart(const char* s, int b);
  unsigned __cdecl FNV1_String8(const char* s, unsigned basis, int len);
  void*  __cdecl operator_new(unsigned size, const char* name, int a, int b,
                              const char* file, int line);
  void*  __cdecl FUN_00e11e073e(void* p, int a, int n);
  void*  __cdecl FUN_00b3d400(int a);
  void*  __cdecl FUN_00b3d3f0(int a);
  void   __cdecl FUN_00e19010(void* a);
  void   __cdecl FUN_00e190c0(void* a);
  void   __cdecl FUN_00e28a00(int a);
  void   __cdecl FUN_00e3c6f0(int a, int b);
  void*  __cdecl FUN_00e4ce40(void* out);
  void   __cdecl FUN_00e4fac0(char* state);
  void   __cdecl FUN_00e4ce40_dummy();
}
extern char g_16b3c04[];
extern char g_16b3c0c[];
extern int  g_15a7bb0, g_15a7bac;

static inline void** Vt(void* p) { return *(void***)p; }

struct cSPUILayout18 {
  void* FindWindowByID(int id, int flag);   // 0x8105b0
  void  SetVisibility(int v);               // 0x810590
  void  Init(void* a, int b, int c);        // 0x8120d0
};

// @ 0x00e53c70
bool FUN_00e53c70(float f) {
  char* e = (char*)FUN_00b721d0(*(int*)(g_16b3c04 + 0x411c));
  if (!e) return false;
  FUN_00e82690(0x8a4d210e, 1.0f);
  e[0x17c] = 1; e[0x17b] = 1; e[0x17f] = 1;
  e[0x178] = 1; e[0x17a] = 1; e[0x17e] = 1;
  e[0x188] = 1; e[0x16c] = 1; e[0x189] = 1;
  if (f > 0.0f) *(int*)(e + 0x18c) = 0x44;
  g_16b3c0c[0xe4] = 1;
  *(int*)(g_16b3c0c + 0xe8) = *(int*)(e + 0x4c);
  *(int*)(g_16b3c0c + 0xec) = *(int*)(e + 0x50);
  *(int*)(g_16b3c0c + 0xf0) = *(int*)(e + 0x54);
  *(float*)(g_16b3c0c + 0xf4) = 3.0f;
  g_16b3c04[0x51dc] = 1;
  return true;
}

// @ 0x00e53d50
bool FUN_00e53d50(float a, float b) {
  char* x = (char*)FUN_00b721d0(*(int*)(g_16b3c04 + 0x51d4));
  char* y = (char*)FUN_00b721d0(*(int*)(g_16b3c04 + 0x411c));
  if (!x || !y) return false;
  if (a < 8.0f) x[0x18b] = 1;
  if (a < 4.0f) y[0x18b] = 1;
  if (b > 0.0f) {
    switch (*(int*)(y + 0x18c)) {
      case 0: case 1: case 2: case 3:
      case 0x15: case 0x16: case 0x28: case 0x31:
        *(int*)(y + 0x18c) = 0x43;
    }
  }
  return true;
}

// @ 0x00e53f20
void SP_sOnButtonSaveClick() {
  void* t = FUN_0067de90(-1);
  FUN_007ebce0(t);
  SP_PatchSoundStart("ui_global_save", 0);
  void* ms = SP_MessageServer();
  (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(ms) + 0x14))(ms, 0x1cd20f0, 0, 0);
  g_16b3c04[0x51da] = 1;
}

// @ 0x00e54050
int FUN_00e54050(int id) {
  int i = 0;
  int* p = (int*)0x15a7bac;
  do {
    if (p[-1] == id) {
      int n = *p;
      for (int j = 0; j < n; ++j) {
        if (((char*)0x16b4278)[i] == 0) {
          ((char*)0x16b4278)[i] = 1;
          return ((int*)0x16b4178)[i];
        }
        ++i;
      }
    } else {
      i += *p;
    }
    p += 3;
  } while ((int)p < 0x15a7bb8);
  return 0;
}

// @ 0x00e53f70
void FUN_00e53f70() {
  if (*(int*)0x15a7bac <= 0) return;
  int* slot = (int*)0x16b4178;
  int n = *(int*)0x15a7bac;
  for (int i = 0; i < n; ++i, ++slot) {
    void* w = operator_new(0x18, "Simulator/Cell/UI", 0, 0, 0, 0);
    void* w2 = w ? (*(void*(__thiscall**)(void*))((char*)Vt(w) + 4))(w) : 0;
    if (w2 != (void*)*slot) {
      if (w2) (*(void(__thiscall**)(void*, int))((char*)Vt(w2) + 4))(w2, 0);
      *slot = (int)w2;
    }
    int args[3];
    args[0] = g_15a7bb0;
    args[1] = 0x510a95b;
    args[2] = 0x40464100;
    ((cSPUILayout18*)(*slot))->Init(args, 1, 0x2edd95ca);
    ((cSPUILayout18*)(*slot))->SetVisibility(0);
  }
  FUN_00e11e073e((void*)0x16b4278, 0, 0x40);
}

// @ 0x00e53e30  closest-point on 3D box -- approximated x87
void FUN_00e53e30(float* out, float* box, float* ext) {
  float midz = (box[2] + box[0]) * 0.5f;
  float midy = (box[4] + box[1]) * 0.5f;
  float midx = (box[5] + box[3]) * 0.5f;
  float ax = (box[3] - box[0]) / ext[0];
  float ay = (box[4] - box[1]) / ext[1];
  float t = (ax < 0 ? -ax : ax) * 0.5f;
  float t2 = (ay < 0 ? -ay : ay) * 0.5f;
  if (t2 < t) t = t2;
  out[0] = ext[0] * t + midz;
  out[1] = ext[1] * t + midy;
  out[2] = ext[2] * t + midx;
}

// ---- remaining slice-18 functions: not reconstructed ---------------------
// @ 0x00e540b0
void FUN_00e540b0(void* a, void* b, int mode) { (void)a; (void)b; (void)mode; }
// @ 0x00e54270
void FUN_00e54270() {}
// @ 0x00e54880
void FUN_00e54880() {}
// @ 0x00e548d0
void FUN_00e548d0() {}
// @ 0x00e549b0
void FUN_00e549b0() {}
// @ 0x00e54ab0
void FUN_00e54ab0() {}
