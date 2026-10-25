// Slice s0082dc00 (batch w2g7, slice 30).
// UTFWin cSPUILayerIdWinProc / layer helpers plus assorted renderer and
// allocator helpers.
#include "types.h"
#include <math.h>

// ---- globals referenced by the disassembly ----
extern int* sLayerRCs;         // 0x154744c : pointer to layer reference counts
extern void* g_appProps;       // 0x15fd918
extern void* g_layerPool;      // 0x164e910
extern char g_layerFlag0d;     // 0x164e90d
extern char g_layerFlag0c;     // 0x164e90c
extern int g_rectGlobal[4];    // 0x164e8fc
extern void* g_d3d;            // 0x16f89d0
extern void* g_counter;        // 0x16f6e78
extern char g_ctrlBlob;        // 0xc2e4e0 (SetSerializer tag)
extern void* g_obj164e8fc;     // 0x164e8fc (viewer object for Update)

// ---- layer window proxy ----
struct ImgHolder { int mDummy; void GetImageResource(void* r); };
struct LayerWinProc {
  char pad0[0x178];
  int mLayer;        // +0x178
  int mRefCount;     // +0x17c
  ImgHolder mImg[2]; // +0x180 (two 4-byte image-holder slots)
  float mFloats[0x10];  // +0x188
  bool SetLayer(int v);
  int ReleaseRef();
  void SetImage(unsigned i, void* r);
  float* FloatAt(int i);
  float GetFloat(unsigned i);
  void SetFloat(float v, unsigned i);
  void* AsInterface(int id);
  void CopyFloats(float* src, int start, int count);
  void SetImage2(unsigned* p, unsigned unused);
};

struct LayerFrame { void Init(void* param); };
struct ShaderBlob { unsigned char Init(); };
struct RectHandler { void Handle(); };
struct RefObj { virtual void AddRef(); virtual void Release(); };
struct RelObj { virtual void r00(); virtual void r01(); virtual void r02(int); };
struct IfaceObj { virtual void i00(); virtual void i01(); virtual void i02(); virtual void* Query(unsigned); };
struct Global15474a0 { virtual void g00(); virtual void g01(); virtual void g02(); virtual void g03(void*, int); };
struct CallbackObj {
  virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03(); virtual void c04();
  virtual void* GetX();                       // 0x14
  virtual void c06();
  virtual bool SetCb(void*, void*);           // 0x1c
};
struct Renderer2 { void Draw(void*, void*, unsigned); void DrawC(void*, void*, unsigned); };
Renderer2* __cdecl GetRenderer2();            // 0x67cad0

// ---- LayerFrame::Init helpers ----
struct UpdObj { void Update(); };             // 0x7c4fd0
struct BlobObj { unsigned Init(); };          // 0x962da0
struct MatMgr {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
  virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
  virtual void* GetMaterial(void*);
};
MatMgr* __cdecl GetMatMgr();                  // 0x67dd70
int __cdecl Handle(int);                      // 0x11fa000
typedef void (__stdcall *DevFn3)(void*, unsigned, void*);
typedef void (__stdcall *DevFn2)(void*, void*);
struct R16 { int v[4]; };
struct LO { char pad[0xc]; char c; unsigned char u; short pad2; void* v; void* q; };

// ---- cSPUISerializeHelper helpers ----
struct Stream {
  virtual void s0();
  virtual void AddRef();
  virtual void Release();
  Stream* Ctor(void*, void*, void*);          // 0x93c270
  void Set(int, float);                       // 0x93bb40
};
struct DispObj { void Dispose(); };           // 0x903120
struct Q4 { int a, b, c, d; };
struct LayoutMgr {
  Q4 q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15;
  int extra;
  void Ctor(void*, void*);                    // 0x82c810
  void Dtor();                                // 0x82c5a0
  bool ProcessTokens();                       // 0x82dc00
};
void* __cdecl NewMem(unsigned, void*, int, int, int, int);   // 0xf473a0
void __cdecl DeleteMem(void*);                                // 0xf47380

extern char g_obj15474a0;                     // 0x15474a0

// @ 0x0082E340
void LayerWinProc::SetFloat(float v, unsigned i) {
  if (i < 0x10) mFloats[i] = v;
}

// @ 0x0082E360
float LayerWinProc::GetFloat(unsigned i) {
  if (i < 0x10) return mFloats[i];
  return 0.0f;
}

// @ 0x0082E3F0
float* LayerWinProc::FloatAt(int i) {
  return &mFloats[i];
}

// @ 0x0082E670
bool LayerWinProc::SetLayer(int v) {
  int old = mLayer;
  if (old != v) {
    if ((unsigned)old <= 0xe) --sLayerRCs[old];
    mLayer = v;
    if (v >= 0) {
      if (v < 0xf) ++sLayerRCs[v];
    }
  }
  return true;
}

// @ 0x0082EB80
void LayerWinProc::SetImage(unsigned i, void* r) {
  if (i < 2) mImg[i].GetImageResource(r);
}

// @ 0x0082EBA0
void DestroyLayerProc(LayerWinProc* p);
int LayerWinProc::ReleaseRef() {
  int old = mRefCount;
  int n = old - 1;
  mRefCount = n;
  if (n == 0 && g_layerFlag0d) DestroyLayerProc(this);
  return n;
}

// @ 0x0082E700
bool IsLayerUsed(unsigned v) {
  if (v <= 0xe) return sLayerRCs[v] > 0;
  return false;
}

// ---- misc small helpers ----
// @ 0x0082E400
bool AppFlagSet() {
  void* a = g_appProps;
  int* b = *(int**)((char*)a + 0x3c);
  return b[0x110 / 4] != 0;
}

// @ 0x0082E420
void* LayerWinProc::AsInterface(int id) {
  if (id <= 0x838293) {
    if (id == 0x838293) return this;
    if (id == (int)0xae9cb0fa) return this;
    if (id == (int)0xee3f516e) return this;
  } else {
    if (id == 0x5234b49) return this;
    if (id == (int)0x6ed3e59b) return this;
  }
  return 0;
}

// @ 0x0082E4C0
void CopyRectGlobal(int* p) {
  g_rectGlobal[0] = p[0];
  g_rectGlobal[1] = p[1];
  g_rectGlobal[2] = p[2];
  g_rectGlobal[3] = p[3];
}

// @ 0x0082E4F0
int RectNotEqual(int* a, int* b) {
  if (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3]) return 0;
  return 1;
}

// @ 0x0082E870
void LayerWinProc::SetImage2(unsigned* p, unsigned unused) {
  (void)unused;
  int* fa = *(int**)((char*)this + 4);
  *p = fa[4];
  fa[4] = (int)p;
}

// ---- fixed allocator Pop loops ----
struct Chunk { Chunk* mpNext; };
struct FixedAllocatorBase {
  char pad0[0x10];
  Chunk* mpHeadChunk;   // +0x10
  bool AddCore(int a, int b);
};
struct Pool5 {
  char pad0[4];
  FixedAllocatorBase* mpAlloc;   // +4
  Chunk* Pop5(int, int, int, int, int);
};
struct Pool3 {
  char pad0[4];
  FixedAllocatorBase* mpAlloc;   // +4
  Chunk* Pop3(int, int, int);
};

// @ 0x0082E520
Chunk* Pool5::Pop5(int, int, int, int, int) {
  FixedAllocatorBase* p = mpAlloc;
  do {
    if (p->mpHeadChunk) {
      Chunk* c = p->mpHeadChunk;
      p->mpHeadChunk = c->mpNext;
      return c;
    }
  } while (p->AddCore(0, 0));
  return 0;
}

// @ 0x0082E840
Chunk* Pool3::Pop3(int, int, int) {
  FixedAllocatorBase* p = mpAlloc;
  do {
    if (p->mpHeadChunk) {
      Chunk* c = p->mpHeadChunk;
      p->mpHeadChunk = c->mpNext;
      return c;
    }
  } while (p->AddCore(0, 0));
  return 0;
}

// ---- large / complex members (not reconstructed) ----
// @ 0x0082DC00
void LayerWinProcInit() {
}

// @ 0x0082E1D0
bool __cdecl LayerProc1(char* p) {
  if (*(void**)(p + 0x1c)) {
    void* m = NewMem(0x24, (void*)0x13f6b3c, 0, 0, 0, 0);
    Stream* s = m ? ((Stream*)m)->Ctor(0, 0, (void*)0x13ebacc) : 0;
    if (s) s->AddRef();
    s->Set(1, 1.0f);
    LayoutMgr mgr;
    mgr.Ctor(s, *(void**)(p + 0x1c));
    if (!mgr.ProcessTokens()) {
      mgr.Dtor();
      if (s) s->Release();
      return false;
    }
    s->Set(1, 0.0f);
    mgr.Dtor();
    Stream* old = *(Stream**)(p + 0x18);
    if (s != old) {
      if (s) s->AddRef();
      *(Stream**)(p + 0x18) = s;
      if (old) old->Release();
    }
    DispObj* q = *(DispObj**)(p + 0x20);
    *(void**)(p + 0x1c) = 0;
    if (q) {
      q->Dispose();
      DeleteMem(q);
    }
    *(void**)(p + 0x20) = 0;
    if (s) s->Release();
    return true;
  }
  return false;
}

// @ 0x0082E300
typedef void (__stdcall *DrawProc)(void*, void*, int*, int);
void LayerProcDraw(void* a1, void* a2, int a3) {
  (void)a2;
  int* c = (int*)g_counter;
  void** vt = *(void***)g_d3d;
  if (a3)
    ((DrawProc)vt[0x178 / 4])(g_d3d, a1, c + 1, c[0] * 6);
  else
    ((DrawProc)vt[0x1b4 / 4])(g_d3d, a1, c + 1, c[0] * 6);
}

// @ 0x0082E380
void LayerWinProc::CopyFloats(float* src, int start, int count) {
  float* d = mFloats + start;
  float* e = d + count;
  while (d < e) *d++ = *src++;
}

// @ 0x0082E470
extern void RegisterCtl(int, void*, void*, void*, void*);
void RegisterE300() {
  RegisterCtl(0x234, &g_ctrlBlob, &g_ctrlBlob, &g_ctrlBlob, &LayerProcDraw);
}

// @ 0x0082E550
void __fastcall LayerFrameInit(char* self, int dummy, char* param) {
  (void)dummy;
  ((UpdObj*)g_obj164e8fc)->Update();
  *(char*)self = (char)((BlobObj*)(self + 0xc28))->Init();
  *(int*)(self + 0x614) = 0;
  *(int*)(self + 4) = 0;
  *(int*)(self + 8) = 0;
  *(int*)(self + 0xc) = 0;
  *(int*)(self + 0x10) = 0;
  *(char**)(self + 0xc68) = param;
  void* m;
  if (*(int*)(param + 0x174) == 0)
    m = 0;
  else
    m = GetMatMgr()->GetMaterial(*(void**)(param + 0x174));
  *(void**)(self + 0xc64) = m;
  void* state = *(void**)(self + 0xc2c);
  int h = Handle(1);
  g_layerFlag0c = (*(int*)(*(int*)((char*)g_appProps + 0x3c) + 0xb8) != 0);
  if (g_layerFlag0c) {
    ((DevFn3)(*(void***)g_d3d)[0xe8 / 4])(g_d3d, 0xae, self + 0xc5c);
    R16* r = (R16*)(self + 0xc4c);
    ((DevFn2)(*(void***)g_d3d)[0x130 / 4])(g_d3d, r);
    ((DevFn3)(*(void***)g_d3d)[0xe4 / 4])(g_d3d, 0xae, (void*)1);
    int e = *(int*)(self + 0xc58), c = *(int*)(self + 0xc54), b = *(int*)(self + 0xc50), a = r->v[0];
    int* d = (int*)(self + 0xc18);
    d[0] = a; d[1] = b; d[2] = c; d[3] = e;
    h = Handle(2);
  }
  *(int*)((char*)state + 0x18) = h;
}

// @ 0x0082E6B0
void __fastcall LayerPoolTick(void* arg) {
  ((LayerFrame*)g_layerPool)->Init(arg);
}

// @ 0x0082E6C0
bool __cdecl LayerProcRelease(LayerWinProc* p) {
  unsigned idx = p->mLayer;
  if (idx <= 0xe) sLayerRCs[idx] = sLayerRCs[idx] - 1;
  ((RelObj*)p)->r02(0);
  ((Global15474a0*)&g_obj15474a0)->g03(p, 0);
  return true;
}

// @ 0x0082E750
void RenderLayer(void* p) {
  LO* o;
  if (p) o = (LO*)((IfaceObj*)p)->Query(0x2f009dd0);
  else o = 0;
  if (o->q) {
    unsigned u = o->u;
    if (o->c) {
      void* v = o->v;
      GetRenderer2()->DrawC(o->q, v, u);
    } else {
      void* v = o->v;
      GetRenderer2()->Draw(o->q, v, u);
    }
  }
}

// @ 0x0082E7A0
bool __fastcall LayerWinProcSetChild(LayerWinProc* self, int dummy, CallbackObj* child) {
  (void)dummy;
  RefObj* old = *(RefObj**)((char*)self + 0x14);
  if ((void*)child != (void*)old) {
    if (child) ((RefObj*)child)->AddRef();
    *(CallbackObj**)((char*)self + 0x14) = child;
    if (old) old->Release();
  }
  CallbackObj* x = (CallbackObj*)child->GetX();
  void* y;
  if (self) y = ((IfaceObj*)self)->Query(0xee3f516e);
  else y = 0;
  bool r = x->SetCb((void*)&RenderLayer, y);
  return r & 0xffffff00;
}

// @ 0x0082E890
void LayerFrameUpdate() {
}

// @ 0x0082EBD0 : cSPUILayerIdWinProc constructor (vtable/field init; full
// base-class hierarchy with the secondary vptr at +4 not reconstructed)
LayerWinProc* __fastcall LayerWinProcCtor(LayerWinProc* p) {
  volatile int* d = (volatile int*)p;
  int zero = 0;
  char one = 1;
  d[1] = 0x13fa72c;
  d[2] = zero;
  d[0] = 0x141a550;
  d[1] = 0x141a538;
  *(volatile char*)((char*)p + 0xc) = one;
  *(volatile char*)((char*)p + 0xd) = one;
  d[4] = zero;
  d[5] = zero;
  return p;
}
