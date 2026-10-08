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
}  // namespace


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
struct Model {
  float GetScale();             // 0x004adaa0
  float GetFloorZ();            // 0x004adb00
  void SetUsingSymmetry(bool);  // 0x004adc20
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
};
MsgMgr* GetMsgMgr();  // 0x00401050
V3 Mirror(const V3& v);                // 0x004a8f40 (x -> -x)
M3 MirrorMatrix(const M3& m, int axis);  // 0x004a8e10
void MoveBlockAndPile(Blk* block, void* pile, V3 pos, M3 orient);  // 0x0049ecf0
void UpdateBlockAndPile(Blk* block, void* pile, int a, int b, int c, int d, int e, int f);  // 0x004a6d20
}  // namespace PM

// @ 0x005b4b40
class PlanarInter : public BaseManip, public EA::RefCountVTemplate<int> {
 public:
  RefA* m1c;   // +0x1c
  void* m20;   // +0x20
  void* m24;   // +0x24
  void* m28;   // +0x28
  void* m2c;   // +0x2c
  char pad_30[0x38 - 0x30];
  cSPVector3 mV;  // +0x38
  bool m44;       // +0x44
  bool m45;       // +0x45
  bool m46;       // +0x46 originally-used-symmetry
  PlanarInter();
  bool DoOnMouseMove(float x, float y, int mods);   // 0x005b4340
  void SetBlock(RefA** src, uint32_t a, uint32_t b, uint32_t c, bool d, bool e);
};
PlanarInter::PlanarInter()
    : m1c(0), m20(0), m24(0), m28(0), m2c(0), mV(), m44(false), m45(false) {
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
    MoveBlockAndPile(block, &m24, H, block->orient);
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
      MoveBlockAndPile(block, &m24, H, block->orient);
    block->model->SetUsingSymmetry(m46);
  }
  ((Blk*)m1c)->model->SetUsingSymmetry(false);
  UpdateBlockAndPile((Blk*)m1c, &m24, 0, 0, 0, outside, 1, 1);
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

// ---- not translated ----
// @ 0x005b4170
void Stub_005b4170() {}
// @ 0x005b4bf0
void Stub_005b4bf0() {}
// @ 0x005b4f20
void Stub_005b4f20() {}
// @ 0x005b4fa0
void Stub_005b4fa0() {}
