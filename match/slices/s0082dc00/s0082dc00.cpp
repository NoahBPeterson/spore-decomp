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
void LayerProc1() {
}

// @ 0x0082E300
void LayerProcDraw(int a, int b, int c) {
  (void)a; (void)b; (void)c;
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
void LayerFrameInit(int param) {
  (void)param;
}

// @ 0x0082E6B0
void LayerPoolTick() {
  // g_layerPool->Tick(...) (single-arg method)
}

// @ 0x0082E6C0
void LayerProcRelease(LayerWinProc* p) {
  if ((unsigned)p->mLayer < 0xf) --sLayerRCs[p->mLayer];
}

// @ 0x0082E750
void RenderLayer(void* p) { (void)p; }

// @ 0x0082E7A0
bool LayerWinProcSetChild(LayerWinProc* p) { (void)p; return false; }

// @ 0x0082E890
void LayerFrameUpdate() {
}

// @ 0x0082EBD0 : cSPUILayerIdWinProc constructor (vtable/field init; full
// base-class hierarchy with the secondary vptr at +4 not reconstructed)
void LayerWinProcCtor(LayerWinProc* p) {
  p->mLayer = 0;
}
