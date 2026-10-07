// slice s005ac950 — tail of SP::cSPEditorManipulationCellPinning plus editor manipulation
// helper methods (block pinning/interpenetration state setters).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "../s005aad00/s005aad00.h"
#include <math.h>

using namespace SP;

// @ 0x005ac950
void* cSPEditorManipulationCellPinning::AsInterface(uint32_t typeID) {
  void* result = this;
  if (typeID != 0xee3f516e && typeID != 0xefdf6da5)
    result = 0;
  return result;
}

// ---- state helpers (offsets taken from the retail code; class identity unconfirmed) ----
struct RefA {  // AddRef at slot 1 (+4), Release at slot 2 (+8)
  virtual ~RefA();
  virtual int AddRef();
  virtual int Release();
};
struct RefB {  // Release at vtable slot 1 (+4)
  virtual int AddRef();
  virtual int Release();
};

// @ 0x005acc30
struct SPin30 {
  char pad_0[4];
  bool mChanged;   // +0x4
  char pad_5[0x1c - 0x5];
  void* m1c;       // +0x1c
  void* m20;       // +0x20
  char pad_24[0x40 - 0x24];
  float mX;        // +0x40
  float mY;        // +0x44
  int m48;         // +0x48
  bool DoOnMouseMove(float x, float y, int z);
};
bool SPin30::DoOnMouseMove(float x, float y, int z) {
  if (m1c == 0 || m20 == 0)
    return false;
  if ((mX != x || mY != y) && !mChanged)
    mChanged = true;
  m48 = z;
  mX = x;
  mY = y;
  return true;
}

// @ 0x005acc90
struct SPin90 {
  char pad_0[0x1c];
  RefA* m1c;   // +0x1c
  RefB* m20;   // +0x20
  int m24;     // +0x24
  void Shutdown();
};
void SPin90::Shutdown() {
  if (m20) {
    RefB* p = m20;
    m20 = 0;
    p->Release();
  }
  if (m1c) {
    RefA* p = m1c;
    m1c = 0;
    p->Release();
  }
  m24 = 0;
}

// @ 0x005ad930
struct SPin930 {
  char pad_0[0x1c];
  RefA* m1c;         // +0x1c
  void* m20;         // +0x20
  char pad_24[0x38 - 0x24];
  uint32_t m38;      // +0x38
  uint32_t m3c;      // +0x3c
  uint32_t m40;      // +0x40
  bool m44;          // +0x44
  void SetBlock(RefA** src, uint32_t a, uint32_t b, uint32_t c, bool d);
};
void SPin930::SetBlock(RefA** src, uint32_t a, uint32_t b, uint32_t c, bool d) {
  RefA* blk = *src;
  RefA* old = m1c;
  if (blk != old) {
    if (blk)
      blk->AddRef();
    m1c = blk;
    if (old)
      old->Release();
  }
  m38 = a;
  m3c = b;
  m40 = c;
  m44 = d;
  if (m1c)
    m20 = *(void**)((char*)m1c + 0x33c);
}

// ---- rotation / move manipulator helpers (class identity unconfirmed; offsets from retail) ----
struct V3 { float x, y, z; };
struct V3c {  // Vector3 passed by value with a member-wise (x87) copy
  float x, y, z;
  V3c(const V3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct V4 { float x, y, z, w; };
extern V4 g_01511b00;  // constant vec4 passed by value to Block::F448690

struct Block;
struct SkinMgr {
  void Update(int a, int b, int c, int d);  // 0x004c38e0 (cSPEditorSkinManager::Update)
};

struct Handle {  // rotation handle; AddRef slot 0, Release slot 1
  virtual int AddRef();
  virtual int Release();
  virtual void vs2(); virtual void vs3(); virtual void vs4(); virtual void vs5();
  virtual void vs6(); virtual void vs7(); virtual void vs8(); virtual void vs9();
  virtual void vs10(); virtual void vs11();
  virtual void Notify(int a, int b);  // slot 12 (+0x30)
  uint32_t pad_4[(0xb4 - 4) / 4];
  Handle* mRingB4;          // +0xb4
  uint32_t pad_b8[(0x11c - 0xb8) / 4];
  const char* mSoundName;   // +0x11c
  uint32_t pad_120[(0x180 - 0x120) / 4];
  float mAngle;             // +0x180
  Block* GetRigblock();                    // 0x0047e6c0
  void Reset();                            // 0x00480cf0 (Ring_Reset)
  void GetDir(V3* out, int a);             // 0x00482040
  void GetPoint9c(V3* out, int a);         // 0x00482130
  void GetPoint90(V3* out, int a);         // 0x00482200
  void F438700(Block* b);                  // 0x00438700
  void F438a40(Block* b);                  // 0x00438a40
};

struct Model {
  bool F4adc40();  // 0x004adc40
};

struct AnimInfo {  // SP::cSPEditorAnimatedEventInfo (size 0x30)
  virtual void vs0();
  virtual int AddRef();
  virtual int Release();
  uint32_t pad[11];
  AnimInfo();  // 0x0059d960
  void MessagePost(uint32_t id, Block* b, Model* m, int a, int c, float d, int e, int f, float g);  // 0x0059d840
};

struct Block {
  virtual ~Block();
  virtual int AddRef();
  virtual int Release();
  uint32_t pad_c[(0x28 - 4) / 4];
  Model* mModel;            // +0x28
  uint32_t pad_2c[(0x48 - 0x2c) / 4];
  float mX, mY, mZ;         // +0x48
  uint32_t pad_54[(0x33c - 0x54) / 4];
  Handle* m33c;             // +0x33c
  uint32_t pad_340[(0x3f0 - 0x340) / 4];
  V3* m3f0;                 // +0x3f0 (vec at +0xc)
  uint32_t pad_3f4[(0xdc8 - 0x3f4) / 4];
  uint32_t mFlags;          // +0xdc8
  bool Flag11() const { return (mFlags >> 11) & 1; }
  void F449ce0();                       // 0x00449ce0
  void F448a80();                       // 0x00448a80
  int F43c3d0(Handle* h, int a);        // 0x0043c3d0
  void F448480(int v);                  // 0x00448480
  void F43c450(Handle* h, float a, float* b, int c);  // 0x0043c450
  void F43cfc0(Handle* h, int a);       // 0x0043cfc0
  void F448690(V4 v);                   // 0x00448690
  void F43cad0();                       // 0x0043cad0
  void F448e90(V3* p, int a);           // 0x00448e90
  void F4360f0();                       // 0x004360f0
  void SetBooleanAttribute(int id, int v);  // 0x00435a10
  void* GetA();                         // 0x004511f0
  V3 GetVec14();                        // 0x004512e0
  void SnapToAnchor(void* a, V3 v);     // 0x00436d80
};

struct PileList {
  void* b; void* e; void* c; uint32_t alloc[2];
  PileList() : b(0), e(0), c(0) {}
  ~PileList();  // 0x00453eb0
};

void* __cdecl operator_new_dummy();
void __cdecl F4a02b0(Block* b, V3c a, V3c c);                         // 0x004a02b0
void __cdecl DeleteInvalidBlocks(Block* b, int a);                  // 0x004a6f10
void __cdecl BuildPileList(Block* b, PileList* l, int a);           // 0x0048c790
void __cdecl F4961d0(Block* b, PileList* l);                        // 0x004961d0
void __cdecl F4a8860(Block* b, PileList* l);                        // 0x004a8860
void __cdecl SetSymmetricBlocksUIState(Block* b, PileList* l, int a);  // 0x004a7f30
void __cdecl F4a6d20(Block* b, int a, int c, int d, int e, int f, int g, int h);  // 0x004a6d20
void __cdecl F4982b0(Block* b, int a, float f, int c);              // 0x004982b0
void __cdecl F496300(Block* b, uint32_t* p, V3 o, V3 d, V3 pt, int a);  // 0x00496300
void __cdecl SetSoundSymbol(uint32_t a, uint32_t b, const char* name);  // 0x00572070
void __cdecl PlayEditorSound(uint32_t a, uint32_t b, float v, int c);   // 0x00435f40

struct Viewer {
  void GetWorldRayFromScreenCoords(float x, float y, V3* origin, V3* dir);  // 0x007c4730
};
struct AppObj {
  virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
  virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
  virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
  virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
  virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
  virtual void a20(); virtual void a21();
  virtual Viewer* GetViewer();  // slot 22 (+0x58)
};
AppObj* AppGet();  // 0x0067dd10 (SP::App)

static __forceinline void PostBlockEvent(Block* const& blk, uint32_t id) {
  AnimInfo* info = new ("Editor", 0, 0, 0, 0) AnimInfo();
  if (info)
    info->AddRef();
  Model* m = blk ? blk->mModel : 0;
  info->MessagePost(id, blk, m, 0, 0, 0.0f, 0, -1, 1.0f);
  if (info)
    info->Release();
}

struct PinBase : public EA::COM::IUnknown32 {
  PinBase();  // 0x005b0f80
  virtual ~PinBase() {}
  bool mChanged;  // +4
  uint32_t pad_5[3];
};

// @ 0x005ac980
struct PinSimple : public PinBase, public EA::RefCountVTemplate<int> {
  PinSimple();
  virtual int AddRef();
  virtual int Release();
};
PinSimple::PinSimple() {}

// rotation manipulator
struct PinRot : public PinBase, public EA::RefCountVTemplate<int> {
  Block* mBlock;     // +0x1c
  Handle* mHandle;   // +0x20
  uint32_t m24;
  V3 mOffset;        // +0x28
  V3 m34;            // +0x34
  float mX;          // +0x40
  float mY;          // +0x44
  int mZ;            // +0x48
  float mAngle;      // +0x4c
  float mAngle2;     // +0x50
  float mMax;        // +0x54
  float mMin;        // +0x58
  PinRot();
  virtual int AddRef();
  virtual int Release();
  bool OnMouseUp(int b, float x, float y, int m);
  void Begin(Handle* h, V3 off, int d);
  bool DoOnMouseDown(int b, float x, float y, int m);
  void Update(int a);
  bool DoOnMouseUp2(int b, float x, float y, int m);
};

// @ 0x005ac9f0
PinRot::PinRot() {
  mBlock = 0; mHandle = 0; m24 = 0;
  mOffset.x = 0.0f; mOffset.y = 0.0f; mOffset.z = 0.0f;
  mZ = 0;
  mChanged = false;
  mX = 0.0f; mY = 0.0f;
  mMax = 1.0f; mMin = 0.0f;
}

// @ 0x005aca70
bool PinRot::OnMouseUp(int, float, float, int) {
  if (mHandle && mBlock) {
    mBlock->F43c450(mHandle, mAngle, 0, 1);
    if (mBlock->Flag11() && mBlock->m3f0 != 0)
      F4a02b0(mBlock, m34, *(V3*)((char*)mBlock->m3f0 + 0xc));
    mBlock->F449ce0();
    if (mChanged)
      PostBlockEvent(mBlock, 0x8fea0db4);
    DeleteInvalidBlocks(mBlock, 0);
    mHandle->Reset();
    mBlock->F448480(mBlock->F43c3d0(mHandle, 0));
    if (mHandle->mRingB4) {
      mHandle->mRingB4->Reset();
      mBlock->F448480(mBlock->F43c3d0(mHandle->mRingB4, 0));
    }
    mBlock->F448690(g_01511b00);
    mHandle->Notify(3, 1);
    mBlock->F43cad0();
  }
  return true;
}

// @ 0x005accc0
void PinRot::Begin(Handle* h, V3 off, int d) {
  Block* nb = h->GetRigblock();
  Block* ob = mBlock;
  if (nb != ob) {
    if (nb)
      nb->AddRef();
    mBlock = nb;
    if (ob)
      ob->Release();
  }
  Handle* oh = mHandle;
  if (h != oh) {
    if (h)
      h->AddRef();
    mHandle = h;
    if (oh)
      oh->Release();
  }
  mOffset = off;
  mAngle2 = mHandle->mAngle;
  mAngle = mHandle->mAngle;
  m24 = d;
}

// @ 0x005acdb0
bool PinRot::DoOnMouseDown(int, float x, float y, int z) {
  if (mHandle && mBlock) {
    mX = x;
    mY = y;
    mZ = z;
    Model* model = mBlock->mModel;
    mBlock->F448a80();
    PileList list;
    BuildPileList(mBlock, &list, 0);
    F4961d0(mBlock, &list);
    if (!model->F4adc40())
      F4a8860(mBlock, &list);
    SetSymmetricBlocksUIState(mBlock, &list, 0);
    Block* cb = mBlock;
    if (cb->Flag11() && cb->m3f0)
      m34 = *(V3*)((char*)cb->m3f0 + 0xc);
    mBlock->F43cfc0(mHandle, 1);
    mHandle->Notify(2, 1);
  }
  return false;
}

// @ 0x005acec0
void PinRot::Update(int) {
  if (!mBlock || !mHandle)
    return;
  V3 origin, dir;
  AppGet()->GetViewer()->GetWorldRayFromScreenCoords(mX, mY, &origin, &dir);
  origin.x = mOffset.x + origin.x;
  origin.y = mOffset.y + origin.y;
  origin.z = mOffset.z + origin.z;
  V3 p90, p9c, d;
  mHandle->GetPoint90(&p90, 1);
  mHandle->GetPoint9c(&p9c, 1);
  float dx = p9c.x - p90.x, dy = p9c.y - p90.y, dz = p9c.z - p90.z;
  float len = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
  mHandle->GetDir(&d, 1);
  float inv = 1.0f / (float)sqrt((double)(d.x * d.x + d.y * d.y + d.z * d.z));
  d.x *= inv; d.y *= inv; d.z *= inv;
  // C = dir x d ; E = d x C (dir projected perpendicular to d)
  float c0 = dir.y * d.z - dir.z * d.y;
  float c1 = dir.z * d.x - d.z * dir.x;
  float c2 = d.y * dir.x - dir.y * d.x;
  float e0 = c2 * d.y - c1 * d.z;
  e0 = -e0;
  float e1 = -(c0 * d.z - c2 * d.x);
  float e2 = -(c2 * 0.0f);
  e2 = d.x * c1 - d.y * c0;
  float inv2 = 1.0f / (float)sqrt((double)(e0 * e0 + e1 * e1 + e2 * e2));
  float nx = inv2 * e0, ny = inv2 * e1, nz = inv2 * e2;
  float denom = nx * dir.x + ny * dir.y + nz * dir.z;
  if (denom == 0.0f)
    return;
  float t = -((nx * origin.x + nz * origin.z + ny * origin.y + -(nx * p90.x + p90.z * nz + p90.y * ny)) / denom);
  if (t < 0.0f)
    return;
  float s = (((t * dir.x + origin.x - p90.x) * d.x) + ((origin.y + dir.y * t - p90.y) * d.y) +
             ((origin.z + dir.z * t - p90.z) * d.z)) / len;
  float hi = mMax;
  if (s > hi)
    s = hi;
  float lo = mMin;
  if (lo > s)
    s = lo;
  float old = mAngle2;
  mAngle = s;
  mAngle2 = s;
  if (s > hi)
    mAngle2 = hi;
  else if (lo > s)
    mAngle2 = lo;
  if (mBlock->Flag11() && mBlock->m3f0)
    m34 = *(V3*)((char*)mBlock->m3f0 + 0xc);
  mBlock->F43c450(mHandle, mAngle2, &mAngle, 1);
  mBlock->F449ce0();
  if (old != mAngle2) {
    const char* name = mHandle->mSoundName;
    if (*name != 0) {
      SetSoundSymbol(0xb07c3bbf, 0x1e8bda2a, name);
      PlayEditorSound(0xb07c3bbf, 0xfdedb725, mAngle2, 0);
    }
  }
  if (mBlock->Flag11() && mBlock->m3f0)
    F4a02b0(mBlock, m34, *(V3*)((char*)mBlock->m3f0 + 0xc));
  F4a6d20(mBlock, 0, 0, 0, 0, 0, 1, 1);
  if (m24) {
    SkinMgr* sk = (SkinMgr*)m24;
    sk->Update(0, 1, 0, 0);
  }
}

// @ 0x005ad430
bool PinRot::DoOnMouseUp2(int, float, float, int) {
  if (mChanged) {
    if (mHandle == 0) {
      if (mBlock->m33c != 0)
        PostBlockEvent(mBlock, 0x8e04ce1a);
    } else if (mBlock->m33c == 0) {
      PostBlockEvent(mBlock, 0x428e920);
    } else {
      PostBlockEvent(mBlock, 0xda95baa5);
    }
  }
  if (mBlock->m33c != 0) {
    if (mBlock->GetA()) {
      Block* b = mBlock;
      b->SnapToAnchor(b->GetA(), b->GetVec14());
    }
  }
  DeleteInvalidBlocks(mBlock, 0);
  return true;
}

// move manipulator
struct PinMove : public PinBase, public EA::RefCountVTemplate<int> {
  Block* mBlock;     // +0x1c
  Handle* mHandle;   // +0x20
  uint32_t m24;      // +0x24
  uint32_t pad_28[(0x38 - 0x28) / 4];
  float mOffX;       // +0x38
  float mOffY;       // +0x3c
  float mOffZ;       // +0x40
  bool mLockXY;      // +0x44
  PinMove();
  virtual int AddRef();
  virtual int Release();
  bool DoMouseMove(float x, float y, int m);
};

bool __cdecl F4902c0(Block* b, Handle* h);  // 0x004902c0

// @ 0x005ad5d0
bool PinMove::DoMouseMove(float x, float y, int) {
  V3 origin, dir;
  AppGet()->GetViewer()->GetWorldRayFromScreenCoords(x, y, &origin, &dir);
  Block* blk = mBlock;
  if (blk) {
    V3 pos;
    pos.x = blk->mX; pos.y = blk->mY; pos.z = blk->mZ;
    bool lock = mLockXY;
    origin.x = mOffX + origin.x;
    origin.y = mOffY + origin.y;
    origin.z = mOffZ + origin.z;
    float nx = 0.0f, ny = 0.0f, nz = 1.0f;
    if (lock) {
      float inv = 1.0f / (float)sqrt((double)(dir.x * dir.x + dir.y * dir.y));
      nx = dir.x * inv;
      ny = dir.y * inv;
      nz = inv * 0.0f;
    }
    float denom = dir.x * nx + dir.z * nz + dir.y * ny;
    if (denom != 0.0f) {
      float t = -((origin.x * nx + origin.z * nz + origin.y * ny + -(blk->mZ * nz + blk->mY * ny + blk->mX * nx)) / denom);
      if (t >= 0.0f) {
        V3 hit;
        hit.x = dir.x * t + origin.x;
        hit.y = dir.y * t + origin.y;
        hit.z = dir.z * t + origin.z;
        if (lock) {
          hit.x = blk->mX;
          hit.y = blk->mY;
        }
        blk->F448e90(&hit, 1);
      }
    }
    if (mBlock->mModel && mBlock->mModel->F4adc40())
      F4982b0(mBlock, 0, 4.0f, 1);
    F496300(mBlock, &m24, origin, dir, pos, 0);
  }
  if (mHandle) {
    bool r = F4902c0(mBlock, mHandle);
    Handle* h33c = mBlock->m33c;
    if (r) {
      if (h33c != mHandle) {
        if (h33c)
          h33c->F438a40(mBlock);
        mHandle->F438700(mBlock);
      }
      mBlock->F4360f0();
    } else {
      if (h33c)
        h33c->F438a40(mBlock);
      mBlock->SetBooleanAttribute(0x23, 1);
      mBlock->SetBooleanAttribute(0x33, 0);
    }
  }
  F4a6d20(mBlock, 0, 0, 0, 0, 0, 1, 1);
  if (!mChanged)
    mChanged = true;
  return true;
}
