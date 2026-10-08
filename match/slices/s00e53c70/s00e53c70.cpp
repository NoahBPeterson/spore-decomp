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

__declspec(noinline) void FUN_00e53f70();                         // 0x00e53f70 allocate cell UI windows
void RepositionWindows(void* a, void* b, int mode);  // 0x00e540b0 reposition two windows (cdecl)

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
__declspec(noinline) void FUN_00e540b0(void* a, void* b, int mode) { (void)a; (void)b; (void)mode; }
// ---- HUD initialisation (0x00e54270) ---------------------------------------------------------
// Class and field names below are Claude-coined from usage.
#define V4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();

struct UIWindow {
  V4(a) V4(b) V4(c) virtual void d0(); virtual void d1();   // slots 0..13
  virtual float* GetArea();                                  // slot 14 (+0x38): float[4] rect
  V4(e) V4(f) V4(g)                                          // slots 15..26
  virtual void SetArea(const float* rect);                   // slot 27 (+0x6c)
  virtual void SetPosition(float x, float y);                // slot 28 (+0x70)
  V4(h) V4(i) V4(j) V4(k) V4(l) V4(m) V4(n) V4(o) V4(p)      // slots 29..64
  virtual void ApplyStyle(const void* style);                // slot 65 (+0x104)
};

struct ResKey { uint32_t a, b, c; };

struct UILayout {                       // cSPUILayout-like (vtable: dtor, AddRef, Release)
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad[0x14];
  UILayout();                                                // 0x00810000
  void Init(const ResKey* key, int a, int b);                // 0x008120d0
  UIWindow* FindWindowByID(int id, int flag);                // 0x008105b0
};
struct UIOptions {                      // cSPUIGlobalOptions-like (vtable: AddRef, Release)
  virtual void AddRef();
  virtual void Release();
  char pad[0x54];
  UIOptions();                                               // 0x00e00ec0
  void CreateDialog();                                       // 0x00e02430
  UIWindow* GetWindow();                                     // 0x00ff0420 (mov eax,[ecx+0x14])
};
struct UIRefObj {                       // non-virtual refcount at +4, virtual deleting dtor
  virtual ~UIRefObj();
  int mRefCount;
  char pad[0x30];
  UIRefObj(UILayout* layout, const char* name);              // 0x00e28a10
  void Setup();                                              // 0x00e29c80
};
struct UIPreload {                      // cTexturePreload-like (vtable: AddRef, Release)
  virtual void AddRef();
  virtual void Release();
  char pad[0x30];
  UIPreload(int a);                                          // 0x007b07e0
  void PreloadTextureList(const ResKey* key);                // 0x007b1e90
};
struct UIGrid { char pad[0x1c]; void Init(int a, int b); };  // 0x00b72080

struct Vec3f { float x, y, z; };
struct CellCtl {
  char pad00[0x48];
  Vec3f v48, v54, v60, v6c, v78;
  float f84;
  char pad88[0x90 - 0x88];
  UILayout* mLayout;      // +0x90
  UIRefObj* mObj94;       // +0x94
  UIOptions* mOptions;    // +0x98
  UIGrid mGrid;           // +0x9c
  int i_b8;               // +0xb8
  float f_bc;             // +0xbc
  int i_c0, i_c4;         // +0xc0 +0xc4
  char padc8[4];
  Vec3f vcc;              // +0xcc
  float f_d8;             // +0xd8
  int i_dc, i_e0;         // +0xdc +0xe0
  char b_e4;              // +0xe4
  char pade5[3];
  Vec3f ve8;              // +0xe8
  char padf4[8];
  int i_fc;               // +0xfc
  char pad100[0x900 - 0x100];
  int i_900;
  float f_904;
  char pad908[0x934 - 0x908];
  char b934, b935, b936, b937, b938;
  char pad939[3];
  float f93c, f940;
  void Reset();                                              // 0x00697980 cLocalInputState::Reset
};
struct CellGfx { char pad[0x3c]; UIPreload* mPreload; };      // +0x3c
struct TestSystem { char pad[0x70]; char* mListHead; };       // list anchor at +0x70

extern CellCtl* g_pCell;           // 0x016b3c0c
extern CellGfx* g_pCellGfx;        // 0x016b3c08
extern TestSystem* g_pTestSystem;  // 0x015fd928
extern Vec3f gVecA;                // 0x016b3c28
extern Vec3f gVecB;                // 0x015a7d3c
extern const float kF1485720;      // 0x01485720
extern const float kF13eecd8;      // 0x013eecd8
extern char gStyle15a8418[];       // 0x015a8418
extern uint32_t gPreloadIds[3];    // 0x015a8530
void* operator new(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void __cdecl AutoSizeWindowForText(UIWindow* w, int a, int b);                                  // 0x00806e40

template <class T>
static inline void AssignAddRef(T*& dst, T* p) {
  T* old = dst;
  if (p != old) {
    if (p) p->AddRef();
    dst = p;
    if (old) old->Release();
  }
}

static inline void AssignRefCounted(UIRefObj*& dst, UIRefObj* p) {
  UIRefObj* old = dst;
  if (p != old) {
    if (p) ++p->mRefCount;
    dst = p;
    if (old) {
      int n = old->mRefCount - 1;
      old->mRefCount = old->mRefCount - 1;
      if (n == 0) {
        old->mRefCount = 1;
        delete old;
      }
    }
  }
}

// @ 0x00e54270 (cdecl; one bool/byte argument read from the stack)
void FUN_00e54270(char skipPreload) {
  FUN_00e53f70();
  g_pCell->b934 = 0;
  g_pCell->b935 = 0;
  g_pCell->b938 = 0;
  g_pCell->f93c = 0.0f;
  g_pCell->f940 = 0.0f;
  g_pCell->b936 = 0;
  g_pCell->b937 = 0;
  g_pCell->vcc = gVecA;
  g_pCell->v48 = gVecB;
  g_pCell->v54 = gVecB;
  g_pCell->v60 = gVecB;
  g_pCell->i_b8 = 0;
  g_pCell->i_e0 = 0;
  g_pCell->b_e4 = 0;
  g_pCell->ve8 = gVecA;
  g_pCell->f_bc = kF1485720;
  Vec3f* v = &g_pCell->v78;
  v->x = 0.0f;
  v->y = 0.0f;
  v->z = kF13eecd8;
  g_pCell->v6c = *v;
  g_pCell->f84 = 0.0f;
  g_pCell->Reset();
  g_pCell->i_c0 = 0;
  g_pCell->i_c4 = 0;
  g_pCell->i_fc = 0;
  g_pCell->f_904 = 0.0f;
  g_pCell->i_900 = 0;
  g_pCell->f_d8 = 0.0f;
  g_pCell->i_dc = 0;

  ResKey key;
  key.a = FNV1_String8("GlobalUICell-3", 0x811c9dc5, 1);
  key.b = 0x510a95b;
  key.c = 0x40464100;
  AssignAddRef(g_pCell->mLayout, new("Simulator/Cell/UI", 0, 0, 0, 0) UILayout());
  g_pCell->mLayout->Init(&key, 1, 0x2edd95ca);

  UIWindow* a = g_pCell->mLayout->FindWindowByID(0x5af4bf0, 1);
  UIWindow* b = g_pCell->mLayout->FindWindowByID(0x5af4af0, 1);
  RepositionWindows(a, b, 1);
  a = g_pCell->mLayout->FindWindowByID(0x5af4bf1, 1);
  b = g_pCell->mLayout->FindWindowByID(0x5af4af1, 1);
  RepositionWindows(a, b, 1);

  UIWindow* wa = g_pCell->mLayout->FindWindowByID(0x5af4bf2, 1);
  UIWindow* wb = g_pCell->mLayout->FindWindowByID(0x5af4af2, 1);
  wa->GetArea();
  wb->GetArea();
  float* rb0 = wb->GetArea();
  float widthBefore = rb0[2] - rb0[0];
  AutoSizeWindowForText(wb, 0, 0);
  float* ra = wa->GetArea();
  float* rb = wb->GetArea();
  float delta = (rb[2] - rb[0]) - widthBefore;
  {
    float rect[4];
    rect[0] = ra[0] - delta;
    rect[1] = ra[1];
    rect[2] = ra[2];
    rect[3] = ra[3];
    wa->SetArea(rect);
  }
  wb->SetPosition(rb[0] - delta, rb[1]);

  AssignAddRef(g_pCell->mOptions, new("Simulator/Cell/UI", 0, 0, 0, 0) UIOptions());
  g_pCell->mOptions->CreateDialog();

  AssignRefCounted(g_pCell->mObj94, new("Simulator/Cell/UI", 0, 0, 0, 0) UIRefObj(g_pCell->mLayout, "\x02"));
  g_pCell->mObj94->Setup();
  g_pCell->mGrid.Init(0x38, 0x20);
  g_pCell->mLayout->FindWindowByID(-1, 1)->ApplyStyle(gStyle15a8418);
  g_pCell->mOptions->GetWindow()->ApplyStyle(gStyle15a8418);

  if (!g_pTestSystem || g_pTestSystem->mListHead == (char*)g_pTestSystem + 0x70 || !skipPreload) {
    AssignAddRef(g_pCellGfx->mPreload, new("Simulator", 0, 0, 0, 0) UIPreload(-1));
    ResKey pk;
    pk.b = 0xefbda3ff;
    pk.c = 0x40464100;
    for (int i = 0; i < 3; ++i) {
      pk.a = gPreloadIds[i];
      g_pCellGfx->mPreload->PreloadTextureList(&pk);
    }
  }
}

// @ 0x00e54880
void FUN_00e54880() {}
// @ 0x00e548d0
void FUN_00e548d0() {}
// @ 0x00e549b0
void FUN_00e549b0() {}
// @ 0x00e54ab0
void FUN_00e54ab0() {}
