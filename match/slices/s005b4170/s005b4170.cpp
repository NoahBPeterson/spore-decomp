// slice s005b4170 — SP editor manipulation objects: planar interpenetration ctor/setter and
// mouse-move state helper.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <math.h>
#include "../s005aad00/s005aad00.h"

using namespace SP;
using namespace EA;

namespace {
struct RefA {  // AddRef slot 1, Release slot 2
  virtual ~RefA();
  virtual int AddRef();
  virtual int Release();
};
struct RefB {  // Release slot 1
  virtual int AddRef();
  virtual int Release();
};
struct BaseManip : EA::COM::IUnknown32 {
  virtual ~BaseManip();
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  char pad_7;
  float mDeadZoneSize;   // +0x8
  float mInitialX;       // +0xc
  float mInitialY;       // +0x10
  BaseManip();
};

// eastl::sp_vector<AutoRefCount<cSPEditorBlock> > layout: three pointers followed by the
// 8-byte retail sp_vector_allocator.  Elements are reference-counted block pointers.
struct PileList {
  RefA** mpBegin;
  RefA** mpEnd;
  RefA** mpCapacity;
  uint32_t mAllocator[2];
  PileList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  void erase(RefA** first, RefA** last);                        // 0x00454280
  void DoInsertValueEnd(RefA** position, RefA* const& value);   // 0x00454ee0
};

struct IObject {
  virtual void* Cast(uint32_t id);   // +0x00
  virtual int AddRef();              // +0x04
  virtual int Release();             // +0x08
};

// Handle object whose vtable slot 0x30 takes two ints.
struct RefHandle {
  virtual void* Cast(uint32_t id);   // +0x00
  virtual int AddRef();              // +0x04
  virtual int Release();             // +0x08
  virtual void v3();                 // +0x0c
  virtual void v4();                 // +0x10
  virtual void v5();                 // +0x14
  virtual void v6();                 // +0x18
  virtual void v7();                 // +0x1c
  virtual void v8();                 // +0x20
  virtual void v9();                 // +0x24
  virtual void v10();                // +0x28
  virtual void v11();                // +0x2c
  virtual void SetState(int a, int b);   // +0x30
};
}  // namespace

namespace SP {
class cSPEditorAnimatedEventInfo : public IObject {
 public:
  uint32_t mData[11];
  cSPEditorAnimatedEventInfo();   // 0x0059d960
  void MessagePost(uint32_t id, void* block, void* model, uint32_t a, bool b, float c, int d, int e,
                   float f);   // 0x0059d840
};
}  // namespace SP


// ---------------------------------------------------------------- 0x005b4340
namespace PM {
inline float SqrtF(float v) { return (float)sqrt((double)v); }
struct V3 {
  float x, y, z;
  V3() {}
  V3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  V3(const V3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct M3 {
  V3 a, b, c;
  M3() {}
  M3(const M3& m);  // out of line: Matrix3::Assign (0x0041cb40)
};
struct BBox {
  V3 mn, mx;
};
struct Blk;
struct Model {
  float GetScale();                  // 0x004adaa0
  float GetFloorZ();                 // 0x004adb00
  void SetUsingSymmetry(bool);       // 0x004adc20
  bool UsingSymmetry();              // 0x004adc40
  unsigned GetBlockCount();          // 0x004accf0
  Blk* GetBlock(unsigned index);     // 0x004accb0
};
struct Blk {
  char pad0[0x28];
  Model* model;  // +0x28
  char pad2c[0x48 - 0x2c];
  V3 pos;  // +0x48
  char pad54[0xa8 - 0x54];
  M3 orient;  // +0xa8
  char padcc[0x33c - 0xcc];
  void* socket;       // +0x33c
  Blk** kidsBegin;    // +0x340
  Blk** kidsEnd;      // +0x344
  char pad348[0x3e0 - 0x348];
  Blk* sym;           // +0x3e0
  char pad3e4[0xdc8 - 0x3e4];
  uint32_t flags;     // +0xdc8
  void SetBooleanAttribute(int id, bool v);      // 0x00435a10
  BBox* GetBBox(BBox* out, int a, int b, int c);  // 0x0044ae00
  void SetPosition(const V3& p, bool notify);     // 0x00448e90
  void SetOrientation(const M3& m, bool notify);  // 0x00449420
  void SetSymmetrySign(int sign);                 // 0x0044e980
  void AddToEffectsMask(cSPVector3 pos, bool flag);   // 0x00448690
  void F3cad0();                                  // 0x0043cad0
};
struct Viewer {
  void GetWorldRayFromScreenCoords(float x, float y, V3& origin, V3& dir);  // 0x007c4730
};
struct App {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21();
  virtual Viewer* GetViewer();  // +0x58
};
App* GetApp();  // 0x0067dd10
struct MsgMgr {
  void SetTransform(uint32_t id, Blk* b);  // 0x0045b080
  void Remove(uint32_t key);               // 0x0045b150
  void PlayFrom(uint32_t key, int mode, char* src, int key2);   // 0x0045ae40
};
MsgMgr* GetMsgMgr();  // 0x00401050
V3 Mirror(const V3& v);                // 0x004a8f40 (x -> -x)
M3 MirrorMatrix(const M3& m, int axis);  // 0x004a8e10
void MoveBlockAndPile(Blk* block, void* pile, V3 pos, M3 orient);  // 0x0049ecf0
void UpdateBlockAndPile(Blk* block, void* pile, int a, int b, int c, int d, int e, int f);  // 0x004a6d20
void BuildPileList(Blk* block, void* pile, int depth);   // 0x0048c790
void RecordBlockAndPileHistory(Blk* block, void* pile);  // 0x004961d0
void ReleaseRefs(Blk* block, void* pile);                // 0x004a8860
void SetSymmetricBlocksUIState(Blk* block, void* pile, int state);  // 0x004a7f30
void DeleteInvalidBlocks(Blk* block, void* pile);        // 0x004a6f10
RefA** RemoveCopyBlocks(RefA** first, RefA** last, RefA** result, RefA* const* value);  // 0x005aa740
}  // namespace PM

// Inlined eastl::remove over the pile: locate `block`, then shift the tail down with
// remove_copy (0x005aa740).  Returns end when the block is not present.
inline RefA** RemoveBlockFromPile(RefA** first, RefA** last, RefA* const& block) {
  while (first != last && *first != block)
    ++first;
  if (first != last) {
    RefA** next = first + 1;
    return PM::RemoveCopyBlocks(next, last, first, &block);
  }
  return first;
}

// @ 0x005b4b40
class PlanarInter : public BaseManip, public EA::RefCountVTemplate<int> {
 public:
  RefA* m1c;     // +0x1c
  void* m20;     // +0x20
  PileList mPile;  // +0x24 (eastl sp_vector<AutoRefCount<block> >)
  cSPVector3 mV;  // +0x38
  bool m44;       // +0x44
  bool m45;       // +0x45
  bool m46;       // +0x46 originally-used-symmetry
  PlanarInter();
  bool OnMouseUp(int button, float x, float y, int mods);      // 0x005b4170
  bool DoOnMouseMove(float x, float y, int mods);   // 0x005b4340
  bool DoOnMouseDown(int button, float x, float y, int mods);  // 0x005b4bf0
  void SetBlock(RefA** src, uint32_t a, uint32_t b, uint32_t c, bool d, bool e);
};
PlanarInter::PlanarInter()
    : m1c(0), m20(0), mPile(), mV(), m44(false), m45(false) {
  mChangedObject = false;
}


// @ 0x005b4340
bool PlanarInter::DoOnMouseMove(float x, float y, int mods) {
  using namespace PM;
  V3 origin, dir;
  GetApp()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);
  bool outside = false;
  Blk* block = (Blk*)m1c;
  if (block) {
    V3 bp(block->pos);
    float maxLen = 6.0f;
    float tol = 2.0f;
    if (block->model) {
      maxLen = block->model->GetScale() * 1.5f;
      tol = block->model->GetScale() * 0.1f;
    }
    origin.x = mV.x + origin.x;
    origin.y = mV.y + origin.y;
    origin.z = mV.z + origin.z;
    float vx = -origin.x;
    float vy = -origin.y;
    float l2 = vx * vx + vy * vy;
    float len = SqrtF(l2);
    float inv = 1.0f / len;
    float nx = inv * vx;
    float ny = inv * vy;
    float nz = inv * 0.0f;
    float a = fabsf(nx * 1.0f + (ny * 0.0f + nz * 0.0f));
    float Nx = 1.0f, Ny = 0.0f, Nz = 0.0f;
    if (a < 0.5f) {
      float sign = 1.0f;
      if ((origin.x > 0.0f && origin.y < 0.0f) || (origin.x < 0.0f && origin.y > 0.0f))
        sign = -1.0f;
      float t = a * 2.0f;
      Nx = t;
      Ny = sign + (-sign) * t;
      Nz = t * 0.0f;
    }
    V3 H(block->pos);
    float denom = (dir.z * Nz + dir.y * Ny) + dir.x * Nx;
    float planeD = -((Nx * bp.x + Nz * bp.z) + Ny * bp.y);
    if (denom != 0.0f) {
      float t = -((((Nx * origin.x + Ny * origin.y) + Nz * origin.z)) + planeD) / denom;
      if (!(t < 0.0f)) {
        H.x = dir.x * t + origin.x;
        float ahx = fabsf(H.x);
        H.y = dir.y * t + origin.y;
        H.z = dir.z * t + origin.z;
        if (ahx > tol) {
          outside = true;
          block->SetBooleanAttribute(0xf, false);
          float q = tol * 0.25f;
          V3 L(bp);
          if (q > ahx) {
            float s = ahx / q;
            float lx = (H.x - bp.x) * s;
            float ly = (H.y - bp.y) * s;
            float lz = (H.z - bp.z) * s;
            L = V3(lx + bp.x, bp.y + ly, bp.z + lz);
          }
          float planeD2 = -((L.z * dir.z + L.y * dir.y) + L.x * dir.x);
          float denom2 = (dir.z * dir.z + dir.y * dir.y) + dir.x * dir.x;
          if (denom2 != 0.0f) {
            float t2 = -((((dir.x * origin.x + dir.z * origin.z) + dir.y * origin.y)) + planeD2) / denom2;
            if (!(t2 < 0.0f)) {
              H = V3(t2 * dir.x + origin.x, origin.y + dir.y * t2, origin.z + dir.z * t2);
            }
          }
        } else {
          if (!(block->flags & 1)) {
            block->SetBooleanAttribute(0xf, true);
            H.x = 0.0f;
          }
        }
        float len2 = (H.z * H.z + H.y * H.y) + H.x * H.x;
        if (maxLen < SqrtF(len2)) {
          float k = 1.0f / SqrtF(len2);
          H.x = (k * H.x) * maxLen;
          H.y = (H.y * k) * maxLen;
          H.z = (H.z * k) * maxLen;
        }
      }
    }
    block->model->SetUsingSymmetry(false);
    MoveBlockAndPile(block, &mPile, H, block->orient);
    if (!block->socket && block->sym && (((char*)block->kidsEnd - (char*)block->kidsBegin) & ~3) == 0) {
      Blk* sym = block->sym;
      sym->SetPosition(Mirror(H), false);
      sym = block->sym;
      sym->SetOrientation(MirrorMatrix(block->orient, 0), false);
    }
    BBox bb;
    block->GetBBox(&bb, 0, 0, 0);
    float floorZ = block->model->GetFloorZ();
    bool adjusted = false;
    if (bb.mn.z < floorZ) {
      H.z = (floorZ - bb.mn.z) + H.z;
      adjusted = true;
    }
    bool doUpdate = adjusted;
    if (floorZ > H.z) {
      H.z = floorZ;
      doUpdate = true;
    }
    if (doUpdate)
      MoveBlockAndPile(block, &mPile, H, block->orient);
    block->model->SetUsingSymmetry(m46);
  }
  ((Blk*)m1c)->model->SetUsingSymmetry(false);
  UpdateBlockAndPile((Blk*)m1c, &mPile, 0, 0, 0, outside, 1, 1);
  ((Blk*)m1c)->model->SetUsingSymmetry(m46);
  if (!mChangedObject)
    mChangedObject = true;
  GetMsgMgr()->SetTransform(0x16d0daed, (Blk*)m1c);
  return true;
}

// @ 0x005b4ad0
void PlanarInter::SetBlock(RefA** src, uint32_t a, uint32_t b, uint32_t c, bool d, bool e) {
  RefA* blk = *src;
  RefA* old = m1c;
  if (blk != old) {
    if (blk)
      blk->AddRef();
    m1c = blk;
    if (old)
      old->Release();
  }
  *(uint32_t*)&mV.x = a;
  *(uint32_t*)&mV.y = b;
  *(uint32_t*)&mV.z = c;
  m44 = e;
  m45 = d;
  if (m1c)
    m20 = *(void**)((char*)m1c + 0x33c);
}

// @ 0x005b50a0
struct SPin50 {
  char pad_0[4];
  bool mChanged;   // +0x4
  char pad_5[0x20 - 0x5];
  void* m20;       // +0x20
  char pad_24[0x140 - 0x24];
  float mX;        // +0x140
  float mY;        // +0x144
  char pad_148[0x154 - 0x148];
  int m154;        // +0x154
  bool DoOnMouseMove(float x, float y, int z);
};
bool SPin50::DoOnMouseMove(float x, float y, int z) {
  if (m20) {
    if ((mX != x || mY != y) && !mChanged)
      mChanged = true;
    m154 = z;
    mX = x;
    mY = y;
    return true;
  }
  return false;
}

// ---- planar interpenetration: mouse up / mouse down ----

// Posts the editor event selected by the block's flags, records the pile transform, drops
// blocks that lost their socket and notifies the message map.
// @ 0x005b4170
bool PlanarInter::OnMouseUp(int button, float x, float y, int mods) {
  (void)button; (void)x; (void)y; (void)mods;
  if (mChangedObject) {
    using namespace PM;
    Blk* block = (Blk*)m1c;
    uint32_t flags = block->flags;
    uint32_t id = 0;
    bool post = true;
    if ((flags >> 1) & 1)
      id = 0x428e920;
    else if ((flags >> 2) & 1)
      post = false;
    else if (m44)
      id = 0x8e04ce1a;
    else
      id = 0xda95baa5;
    if (post) {
      cSPEditorAnimatedEventInfo* msg = new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo();
      if (msg)
        msg->AddRef();
      Blk* target = (Blk*)m1c;
      Model* model = target ? target->model : 0;
      msg->MessagePost(id, target, model, 0, false, 0.0f, 0, -1, 1.0f);
      if (msg)
        msg->Release();
    }
  }
  {
    using namespace PM;
    Blk* block = (Blk*)m1c;
    Model* model = block->model;
    if (model) {
      int count = (int)model->GetBlockCount();
      for (int i = 0; i < count; ++i) {
        if (model->GetBlock(i)->socket == 0)
          model->GetBlock(i)->SetSymmetrySign(-2);
      }
    }
    DeleteInvalidBlocks(block, &mPile);
  }
  PM::GetMsgMgr()->Remove(0x16d0daed);
  return true;
}

// Rebuilds the pile around the manipulated block, optionally snaps the block onto the
// x = 0 symmetry plane, then refreshes symmetry bookkeeping and posts the transform.
// @ 0x005b4bf0
bool PlanarInter::DoOnMouseDown(int button, float x, float y, int mods) {
  (void)button; (void)mods;
  using namespace PM;
  Blk* block = (Blk*)m1c;
  Model* model = block->model;

  mPile.erase(mPile.mpBegin, mPile.mpEnd);
  m46 = model->UsingSymmetry();

  if (m45) {
    int count = (int)model->GetBlockCount();
    for (int i = 0; i < count; ++i) {
      if (model->GetBlock(i)->socket == 0) {
        BuildPileList(model->GetBlock(i), &mPile, 0);
        RefA* child = (RefA*)model->GetBlock(i);
        if (child)
          child->AddRef();
        mPile.DoInsertValueEnd(mPile.mpEnd, child);
        if (child)
          child->Release();
      }
    }
  } else {
    BuildPileList(block, &mPile, 0);
    Blk* sym = block->sym;
    if (sym) {
      BuildPileList(sym, &mPile, 0);
      RefA* child = (RefA*)sym;
      child->AddRef();
      mPile.DoInsertValueEnd(mPile.mpEnd, child);
      child->Release();
    }
  }

  RefA** end = mPile.mpEnd;
  RefA** it = RemoveBlockFromPile(mPile.mpBegin, end, m1c);
  mPile.erase(it, end);
  RecordBlockAndPileHistory(block, &mPile);

  V3 origin, dir;
  GetApp()->GetViewer()->GetWorldRayFromScreenCoords(x, y, origin, dir);

  float vx = -origin.x;
  float vy = -origin.y;
  float inv = 1.0f / SqrtF(vx * vx + vy * vy);
  float alignment = fabsf((inv * vy + inv * 0.0f) * 0.0f + inv * vx);
  if (alignment > 0.5f && (block->flags & 1) == 0) {
    block->model->SetUsingSymmetry(false);
    MoveBlockAndPile(block, &mPile, V3(0.0f, block->pos.y, block->pos.z), block->orient);
    block->model->SetUsingSymmetry(m46);
  }

  if (!model->UsingSymmetry())
    ReleaseRefs(block, &mPile);
  SetSymmetricBlocksUIState(block, &mPile, 0);
  GetMsgMgr()->PlayFrom(0x16d0daed, 1, (char*)block, 0);
  return true;
}
// @ 0x005b4f20
// Angle wrap into (-pi, pi].  The period lives in a mutable global (0x15e9fd8, 0 in the
// emulated image, so the fmod yields NaN and the wraps are skipped - the same as retail);
// retail keeps the fmod result in st0 and reloads the global for each correction.
float Stub_005b4f20(float angle)
{
  float r = (float)fmod(angle, *(volatile float*)0x15e9fd8);
  if (r > 3.1415927410125732f)
    return r - *(volatile float*)0x15e9fd8;
  if (r < -3.1415927410125732f)
    return r + *(volatile float*)0x15e9fd8;
  return r;
}
// ---- rotation handle ----

class RotationHandle : public BaseManip, public EA::RefCountVTemplate<int> {
 public:
  RefHandle* m1c;   // +0x1c rotation handle
  PM::Blk* m20;     // +0x20 rotated block
  PileList mPile;   // +0x24
  bool OnMouseUp(int button, float x, float y, int mods);
};

// Clears the handle effects and posts the block-changed event when anything moved.
// @ 0x005b4fa0
bool RotationHandle::OnMouseUp(int button, float x, float y, int mods) {
  (void)button; (void)x; (void)y; (void)mods;
  if (m1c && m20) {
    m20->AddToEffectsMask(cSPVector3(1.0f, 1.0f, 1.0f), false);
    m1c->SetState(3, 1);
    m20->F3cad0();
    if (mChangedObject) {
      cSPEditorAnimatedEventInfo* msg = new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo();
      if (msg)
        msg->AddRef();
      PM::Blk* block = m20;
      PM::Model* model = block ? block->model : 0;
      msg->MessagePost(0x211685f7, block, model, 0, false, 0.0f, 0, -1, 1.0f);
      if (msg)
        msg->Release();
    }
    PM::DeleteInvalidBlocks(m20, &mPile);
  }
  return true;
}
