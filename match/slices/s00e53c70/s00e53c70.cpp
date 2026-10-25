// Slice s00e53c70 (batch bfs3, slice 18). Region 0xe53c70-0xe54bf6.
// Cell-game medal/save UI glue. Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

struct cGuard18 { void* p; cGuard18(); ~cGuard18(); };

extern "C" {
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
extern char* g_16b3c04;
extern char* g_16b3c08;
extern char* g_16b3c0c;
extern int  g_15a7bb0, g_15a7bac;

static inline void** Vt(void* p) { return *(void***)p; }

// thiscall lookup on the manager sub-object at manager+0x1c
struct cCellLookup18 {
  void* Get(int id);   // 0x00b721d0
};

static inline void* CellById(int id) {
  return ((cCellLookup18*)(g_16b3c04 + 0x1c))->Get(id);
}

__declspec(noinline) void FUN_00e53f70();                         // 0x00e53f70 allocate cell UI windows
void RepositionWindows(void* a, void* b, int mode);  // 0x00e540b0 reposition two windows (cdecl)

struct cSPUILayout18 {
  void* FindWindowByID(int id, int flag);   // 0x8105b0
  void  SetVisibility(int v);               // 0x810590
  void  Init(void* a, int b, int c);        // 0x8120d0
  void  Shutdown(int a);                    // 0x811ad0
};

// Grid/list helper reached through the cell UI state at +0x9c (0xb72260 remove,
// 0xb720e0 destroy).
struct cCellGrid18 {
  void Remove(void* e);                     // 0xb72260
  void Destroy();                           // 0xb720e0
};

// The scoped helper object at 0x743b50/0xe82130 (stack object) and the float
// object returned by 0xe4ce40 (its field at +0x68 feeds the camera offset).
struct cGuard18b { void* p; };
struct GuardOps { void Ctor(); void Dtor(); };   // 0x743b50 / 0xe82130 (thiscall)

// The global cViewer at 0x016b42b8 (methods thiscall; float arg on the stack).
struct cViewer18 {
  void SetViewAngle(float a);                       // 0x7c5350
  void SetNearClip(float a);                        // 0x7c4ba0
  void SetFarClip(float a);                         // 0x7c4bc0
  void SetCameraToWorld(void* m);                   // 0x7c4c40
  void SetRaster(void* p, int b);                   // 0x7c4be0
  void Clear(int v);                                // 0x7c3c50
};
extern "C" void* FUN_0067dd40();                // 0x67dd40  render service
extern "C" void  FUN_01043580(void* out, void* pos, void* target, void* scratch);  // 0x1043580 view matrix
extern const float kF1483bcc;                   // 0x1483bcc
extern const float kF145c12c;                   // 0x145c12c
extern float g_15a7c40, g_15a7c44, g_15a7c48;   // 0x15a7c40..48
extern cViewer18 g_16b42b8;                     // 0x16b42b8 cViewer global
extern void* g_winSlots[0x40];                  // 0x16b4178 window table
extern unsigned char g_winUsed[0x40];           // 0x16b4278 slot-used flags

// Object returned by 0xe4ce40 (read for its +0x68 scalar, a focus/depth value).
struct cFocusRef18 {
  char  pad0[0x68];
  float mField68;           // +0x68
};

// Cell object whose medal/UI flags the two helpers below write (layout from usage).
struct cCell18 {
  char  pad0[0x4c];
  float mCenterX;            // +0x4c  box centre copied to the UI state
  float mCenterY;            // +0x50
  float mCenterZ;            // +0x54
  char  pad1[0x16c - 0x58];
  unsigned char mbFlag16c;   // +0x16c
  char  pad2[0x178 - 0x16d];
  unsigned char mbFlag178;   // +0x178
  char  pad3[0x17a - 0x179];
  unsigned char mbFlag17a;   // +0x17a
  unsigned char mbFlag17b;   // +0x17b
  unsigned char mbFlag17c;   // +0x17c
  char  pad4[0x17e - 0x17d];
  unsigned char mbFlag17e;   // +0x17e
  unsigned char mbFlag17f;   // +0x17f
  char  pad5[0x188 - 0x180];
  unsigned char mbFlag188;   // +0x188
  unsigned char mbFlag189;   // +0x189
  char  pad6[0x18b - 0x18a];
  unsigned char mbMedalShown; // +0x18b  set by the proximity check
  int   mMedalState;          // +0x18c  switch selector / 0x44 / 0x43
};

// Cell UI state object reached through the global pointer at 0x016b3c0c.
struct cCellUI18 {
  char  pad0[0x48];
  float mCamX;               // +0x48  camera target x (cell origin)
  float mCamY;               // +0x4c
  float mCamZ;               // +0x50
  char  pad1[0x6c - 0x54];
  float mCamOfsX;            // +0x6c  camera offset from the target
  float mCamOfsY;            // +0x70
  float mCamOfsZ;            // +0x74
  char  pad2[0x90 - 0x78];
  void* mpLayout;            // +0x90
  void* mpRefObj;            // +0x94
  void* mpOptions;           // +0x98
  char  pad3[0xe4 - 0x9c];
  unsigned char mbActive;    // +0xe4
  char  pad4[0xe8 - 0xe5];
  float mCenterX;            // +0xe8
  float mCenterY;            // +0xec
  float mCenterZ;            // +0xf0
  float mRadius;             // +0xf4
};

// Manager reached through the global pointer at 0x016b3c04.
struct cCellManager18 {
  char  pad0[0x411c];
  int   mMissionCellId;      // +0x411c
  char  pad1[0x51d4 - 0x4120];
  int   mMedalCellId;        // +0x51d4
  char  pad2[0x51dc - 0x51d8];
  unsigned char mbMissionStarted; // +0x51dc
};

// @ 0x00e53c70
bool FUN_00e53c70(float f) {
  cCellManager18* mgr = (cCellManager18*)g_16b3c04;
  cCell18* c = (cCell18*)CellById(mgr->mMissionCellId);
  if (!c) return false;
  FUN_00e82690(0x8a4d210e, 1.0f);
  c->mbFlag17c = 1; c->mbFlag17b = 1; c->mbFlag17f = 1;
  c->mbFlag178 = 1; c->mbFlag17a = 1; c->mbFlag17e = 1;
  c->mbFlag188 = 1; c->mbFlag16c = 1; c->mbFlag189 = 1;
  if (f > 0.0f) c->mMedalState = 0x44;
  cCellUI18* ui = (cCellUI18*)g_16b3c0c;
  ui->mbActive = 1;
  ui->mCenterX = c->mCenterX;
  ui->mCenterY = c->mCenterY;
  ui->mCenterZ = c->mCenterZ;
  ui->mRadius = 3.0f;
  mgr->mbMissionStarted = 1;
  return true;
}

// @ 0x00e53d50
bool FUN_00e53d50(float a, float b) {
  cCellManager18* mgr = (cCellManager18*)g_16b3c04;
  cCell18* x = (cCell18*)CellById(mgr->mMedalCellId);
  cCell18* y = (cCell18*)CellById(mgr->mMissionCellId);
  if (!x || !y) return false;
  if (a < 8.0f) x->mbMedalShown = 1;
  if (a < 4.0f) y->mbMedalShown = 1;
  if (b > 0.0f) {
    switch (y->mMedalState) {
      case 0: case 1: case 2: case 3:
      case 0x15: case 0x16: case 0x28: case 0x31:
        y->mMedalState = 0x43;
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

// @ 0x00e53e30  closest-point on 3D box -- x87 division, SSE midpoint/clamp
void FUN_00e53e30(float* out, float* box, float* ext) {
  float ax = (box[3] - box[0]) / ext[0];
  float ay = (box[4] - box[1]) / ext[1];
  float ta = fabsf(ax) * 0.5f;
  float tb = fabsf(ay) * 0.5f;
  float t = _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(tb), _mm_set_ss(ta)));
  __m128 tv = _mm_set_ss(t);
  float r0 = _mm_cvtss_f32(_mm_add_ss(_mm_mul_ss(tv, _mm_set_ss(ext[0])),
      _mm_mul_ss(_mm_add_ss(_mm_set_ss(box[0]), _mm_set_ss(box[3])), _mm_set_ss(0.5f))));
  float r1 = _mm_cvtss_f32(_mm_add_ss(_mm_mul_ss(tv, _mm_set_ss(ext[1])),
      _mm_mul_ss(_mm_add_ss(_mm_set_ss(box[1]), _mm_set_ss(box[4])), _mm_set_ss(0.5f))));
  float r2 = _mm_cvtss_f32(_mm_add_ss(_mm_mul_ss(tv, _mm_set_ss(ext[2])),
      _mm_mul_ss(_mm_add_ss(_mm_set_ss(box[2]), _mm_set_ss(box[5])), _mm_set_ss(0.5f))));
  volatile float* o = out;
  o[0] = r0;
  o[1] = r1;
  o[2] = r2;
}

// ---- remaining slice-18 functions: reconstructed below the type definitions --
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
  void Shutdown(int a);                                      // 0x00811ad0
};
struct UIOptions {                      // cSPUIGlobalOptions-like (vtable: AddRef, Release)
  virtual void AddRef();
  virtual void Release();
  char pad[0x54];
  UIOptions();                                               // 0x00e00ec0
  void CreateDialog();                                       // 0x00e02430
  UIWindow* GetWindow();                                     // 0x00ff0420 (mov eax,[ecx+0x14])
  void Destroy();                                            // 0x00e02e10
};
struct UIRefObj {                       // non-virtual refcount at +4, virtual deleting dtor
  virtual ~UIRefObj();
  int mRefCount;
  char pad[0x30];
  UIRefObj(UILayout* layout, const char* name);              // 0x00e28a10
  void Setup();                                              // 0x00e29c80
  void Teardown();                                           // 0x00e28a80
};
struct UIPreload {                      // cTexturePreload-like (vtable: AddRef, Release)
  virtual void AddRef();
  virtual void Release();
  char pad[0x30];
  UIPreload(int a);                                          // 0x007b07e0
  void PreloadTextureList(const ResKey* key);                // 0x007b1e90
};
struct UIGrid { char pad[0x1c]; void Init(int a, int b); void Remove(void* e); void Destroy(); };  // 0x00b72080 / 0xb72260 / 0xb720e0

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
struct CellGfx {
  char pad[0x3c];
  UIPreload* mPreload;        // +0x3c
  char pad2[0x161b0 - 0x40];
  void* mRenderObj;           // +0x161b0 render-target provider
};
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

// @ 0x00e540b0  reposition two windows according to mode (0=right,1=centred,2=left)
void FUN_00e540b0(void* a, void* b, int mode) {
  UIWindow* wa = (UIWindow*)a;
  UIWindow* wb = (UIWindow*)b;
  float rectLeft[4];
  float rectCentre[4];
  float rectRight[4];
  wa->GetArea();
  wb->GetArea();
  float* rb = wb->GetArea();
  float widthBefore = rb[2] - rb[0];
  AutoSizeWindowForText(wb, 0, 0);
  float* ra = wa->GetArea();
  float* rb2 = wb->GetArea();
  float delta = (rb2[2] - rb2[0]) - widthBefore;
  switch (mode) {
    case 0: {
      rectRight[0] = ra[0];
      rectRight[1] = ra[1];
      rectRight[2] = ra[2] + delta;
      rectRight[3] = ra[3];
      wa->SetArea(rectRight);
      break;
    }
    case 1: {
      float half = delta * 0.5f;
      rectCentre[0] = ra[0] - half;
      rectCentre[1] = ra[1];
      rectCentre[2] = ra[2] + half;
      rectCentre[3] = ra[3];
      wa->SetArea(rectCentre);
      break;
    }
    case 2: {
      rectLeft[0] = ra[0] - delta;
      rectLeft[1] = ra[1];
      rectLeft[2] = ra[2];
      rectLeft[3] = ra[3];
      wa->SetArea(rectLeft);
      wb->SetPosition(rb2[0] - delta, rb2[1]);
      break;
    }
  }
}

// @ 0x00e54880  hide a window slot, mark it unused, drop it from the grid
struct cHideWin18 {
  int            mGridKey;   // +0x00  key handed to the grid remove
  char           pad04[0x30];
  cSPUILayout18* mpSub;      // +0x34  layout sub-object (visibility target)
};
void FUN_00e54880(void* win) {
  cHideWin18* w = (cHideWin18*)win;
  cSPUILayout18* sub = w->mpSub;
  sub->SetVisibility(0);
  int i = 0;
  do {
    if (g_winSlots[i] == sub) {
      g_winUsed[i] = 0;
      break;
    }
    ++i;
  } while (i < 0x40);
  g_pCell->mGrid.Remove((void*)w->mGridKey);
}

// @ 0x00e548d0  cell HUD teardown: grid slots, options, layout, ref object, grid dtor
void FUN_00e548d0() {
  for (int i = 0; i < 0x40; ++i) {
    void* w = g_winSlots[i];
    if (w) {
      g_winSlots[i] = 0;
      (*(void(__thiscall**)(void*))((char*)Vt(w) + 8))(w);
    }
  }
  g_pCell->mOptions->Destroy();
  UIOptions* opts = g_pCell->mOptions;
  if (opts) {
    g_pCell->mOptions = 0;
    (*(void(__thiscall**)(void*))((char*)Vt(opts) + 4))(opts);
  }
  g_pCell->mLayout->Shutdown(1);
  UILayout* layout = g_pCell->mLayout;
  if (layout) {
    g_pCell->mLayout = 0;
    (*(void(__thiscall**)(void*))((char*)Vt(layout) + 8))(layout);
  }
  g_pCell->mObj94->Teardown();
  UIRefObj* obj = g_pCell->mObj94;
  if (obj) {
    g_pCell->mObj94 = 0;
    int n = obj->mRefCount - 1;
    obj->mRefCount = n;
    if (n == 0) {
      obj->mRefCount = 1;
      (*(void(__thiscall**)(void*, int))((char*)Vt(obj) + 0))(obj, 1);
    }
  }
  g_pCell->mGrid.Destroy();
}

// @ 0x00e549b0  build cell view matrix from the focused object and apply to the viewer
void FUN_00e549b0() {
  cGuard18 guard;
  cFocusRef18* u = (cFocusRef18*)FUN_00e4ce40((void*)&guard);
  float fz = u->mField68;
  ((GuardOps*)&guard)->Dtor();
  float sx = g_pCell->v48.x + g_pCell->v6c.x;
  float sy = g_pCell->v48.y + g_pCell->v6c.y;
  float sz = g_pCell->v48.z + g_pCell->v6c.z;
  float pos[3];
  pos[0] = sx + g_15a7c40 * fz;
  pos[1] = sy + g_15a7c44 * fz;
  pos[2] = sz + g_15a7c48 * fz;
  float view[16];
  FUN_01043580(pos, &g_pCell->v48, (void*)0x15a7c34, view);
  g_16b42b8.SetViewAngle(kF1483bcc);
  g_16b42b8.SetNearClip(1.0f);
  g_16b42b8.SetFarClip(kF145c12c);
  g_16b42b8.SetCameraToWorld(view);
}

// @ 0x00e54ab0  set raster/clear and issue two rendering passes (stdcall, 4 args)
struct RenderParams18 {
  unsigned pad0;      // +0x00
  unsigned x;         // +0x04
  unsigned y;         // +0x08
  unsigned z;         // +0x0c
};
struct RenderArg18 {
  unsigned viewer;    // +0x00 cViewer address
  unsigned x;         // +0x04
  unsigned y;         // +0x08
  unsigned z;         // +0x0c
};
void __stdcall FUN_00e54ab0(void* a, void* b, RenderParams18* c, void* d) {
  (void)b;
  unsigned local14 = 0xffffffff;
  unsigned local18 = 0xffffffff;
  void* s = FUN_0067dd40();
  (*(void(__thiscall**)(void*, int, void*, int, void*))((char*)Vt(s) + 0xa8))(s, 0, &local14, 0, &local14);
  g_16b42b8.SetRaster(&local18, 1);
  g_16b42b8.Clear(7);
  RenderArg18 ra;
  ra.viewer = 0x16b42b8;
  ra.x = c->x;
  ra.y = c->y;
  ra.z = c->z;
  void* o = g_pCellGfx->mRenderObj;
  void* r = (*(void*(__thiscall**)(void*))((char*)Vt(o) + 0xa0))(o);
  (*(void(__thiscall**)(void*, void*, int, void*, void*))((char*)Vt(r) + 0xc))(r, a, 3, &ra, d);
  o = g_pCellGfx->mRenderObj;
  r = (*(void*(__thiscall**)(void*))((char*)Vt(o) + 0xa0))(o);
  (*(void(__thiscall**)(void*, void*, int, void*, void*))((char*)Vt(r) + 0xc))(r, a, 0x12, &ra, d);
}
