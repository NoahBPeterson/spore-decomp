// Slice s005b94b0 -- SP::cSPEditorManipulation* (Spore creature editor)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
#include <xmmintrin.h>

struct cSPVector3 {
  float x, y, z;
  cSPVector3() {}
  cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {}
  cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
  cSPVector3 operator+(const cSPVector3& v) const { return cSPVector3(x + v.x, y + v.y, z + v.z); }
  cSPVector3 operator-(const cSPVector3& v) const { return cSPVector3(x - v.x, y - v.y, z - v.z); }
  cSPVector3 operator*(float f) const { return cSPVector3(x * f, y * f, z * f); }
  float Dot(const cSPVector3& v) const { return x * v.x + y * v.y + z * v.z; }
};

namespace EA {
template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin; T* mpEnd; T* mpCapacity; int mAllocator[2];
  ~sp_vector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin); }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  T* erase(T* first, T* last);      // 0x454280
};
template <typename T>
T* remove_copy(T* first, T* last, T* result, const T& value);   // 0x5aa740
template <typename T>
T* remove(T* first, T* last, const T& value) {
  while (first != last && !(*first == value)) ++first;
  if (first != last) { T* i = first; return remove_copy(++i, last, first, value); }
  return first;
}
}

namespace SP {
struct cSPMatrix3 { float m[9]; cSPMatrix3(); cSPMatrix3(const cSPMatrix3& o); };   // copy ctor 0x41cb40
class cSPRigidBody {
 public:
  char pad0[0x58];
  void* m_pMotion;                    // +0x58 (hkMotion*)
  // hkMotionState::m_transform::m_translation (motion + 0x10 + 0x30)
  const cSPVector3& GetPosition() const {
    return *(const cSPVector3*)((const char*)m_pMotion + 0x40);
  }
};
// AABB (matches hkAabb: 4-float min, 4-float max).
struct __declspec(align(16)) cSPAabbScratch {
  float mMinX, mMinY, mMinZ, mMinW;   // +0x00
  float mMaxX, mMaxY, mMaxZ, mMaxW;   // +0x10
};
class cSPEditorBlock {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad04[0x28 - 4];
  void* mEditorModel;                  // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3 mPosition3;                // +0x48
  char pad54c[0xa8 - 0x54];
  cSPMatrix3 mTransform;                // +0xa8
  char padcc[0x18c - 0xcc];
  cSPRigidBody* mpRigidBody;             // +0x18c
  char pad190[0x33c - 0x190];
  cSPEditorBlock* mpParent;            // +0x33c
  char pad340[0xdc8 - 0x340];
  unsigned mBooleanAttributes0;        // +0xdc8
  bool SetUIState(int state, bool a, bool b, bool c);   // 0x43a5e0
  bool F43bbc0(int x);                                  // 0x43bbc0
};

class cSPEditorManipulationObject {
 public:
  __declspec(noinline) cSPEditorManipulationObject();
  virtual ~cSPEditorManipulationObject() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};

class cSPEditorManipulation56 : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  void* m1c;                                  // +0x1c
  void* m20;                                  // +0x20
  cSPEditorBlock* mBlock;                     // +0x24
  eastl::sp_vector<cSPEditorBlock*> mVec;     // +0x28
  cSPVector3 mV3c;                            // +0x3c
  cSPVector3 mV48;                            // +0x48
  cSPVector3 mV54;                            // +0x54
  cSPVector3 mV60;                            // +0x60
  cSPVector3 mV6c;                            // +0x6c
  cSPVector3 mV78;                            // +0x78
  int m84;                                    // +0x84
  char pad88[0x89 - 0x88];
  bool m89;                                   // +0x89
  bool m8a;                                   // +0x8a

  cSPEditorManipulation56();
  bool DoOnMouseDown(int button, float x, float y, int modifiers);
  void Update(float dt);
  void SetBlock(cSPEditorBlock* block, cSPVector3 offset, bool b);
  void Other1(cSPEditorBlock* block, int mode, cSPVector3 rayOrigin, cSPVector3 rayDirection,
              cSPVector3* out);
  void* CopyOut(void* dst);
  void Other2(int a, cSPVector3 pos);
};

volatile int g_s56_sink;
__declspec(noinline) cSPEditorManipulationObject::cSPEditorManipulationObject() { g_s56_sink = 1; }

// @ 0x005ba060
cSPEditorManipulation56::cSPEditorManipulation56() : m1c(0) {
  mBlock = 0;
  mVec.mpBegin = 0;
  mVec.mpEnd = 0;
  mVec.mpCapacity = 0;
  mV3c.x = 0.0f;
  mV3c.y = 0.0f;
  mV3c.z = 0.0f;
  m89 = false;
  m8a = false;
  mChangedObject = false;
}

namespace {
class cSPEditorAnimatedEventInfo {
 public:
  cSPEditorAnimatedEventInfo();          // 0x59d960
  virtual void v0();
  virtual int AddRef();                  // +4
  virtual int Release();                 // +8
  void MessagePost(uint32_t id, cSPEditorBlock* b, void* model, int a, int c, float d, int e, int f, float g);  // 0x59d840
  char pad[0x30 - 4];
};
void UpdateBlockState(cSPEditorBlock* b, void* pileList, int, int, int, int, int, int);  // 0x4a6d20
void DeleteInvalidBlocks(cSPEditorBlock* b, void* pileList);                              // 0x4a6f10
void SetSymmetricBlocksUIState(cSPEditorBlock* b, void* pileList, int state);              // 0x4a7f30
void Apply2(cSPVector3* v, int z);                                                            // 0x448e90
void F496300(cSPEditorBlock* b, void* p, cSPVector3 o, cSPVector3 d, cSPVector3 pt, int a);   // 0x496300
cSPEditorAnimatedEventInfo* ctorAnimatedEventInfo(void* p) {
  return new (p) cSPEditorAnimatedEventInfo();
}

struct cViewer {
  void GetWorldRayFromScreenCoords(float x, float y, cSPVector3& origin, cSPVector3& dir);   // 0x7c4730
  void GetCameraLocationInfo(cSPVector3* pos, cSPVector3* dir, cSPVector3* up, cSPVector3* right);  // 0x7c3d30
};
struct cAppSystem {
  virtual void v00();
  virtual void v01();
  virtual void v02();
  virtual void v03();
  virtual void v04();
  virtual void v05();
  virtual void v06();
  virtual void v07();
  virtual void v08();
  virtual void v09();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual void v20();
  virtual void v21();
  virtual cViewer* GetViewer();             // slot 22 (+0x58)
};
cAppSystem* App();                          // 0x67dd10

extern const float g_013f9428;             // 0.001f  (millisecond scale)
extern const float g_013ec478;             // 0.05f   (max step)
extern const float g_013f6b68;             // 12.0f   (spring rate)
extern const float g_01471064;             // 0.5f
extern const float g_013eb8b0;             // sign mask (-0.0f)
extern const float g_013eb1bc;             // -1.0f
extern const float g_01486e98;             // grid-ray direction scale
extern float g_015ea5a8;                   // shared editor scratch float (grid height)
extern const float g_013f781c;             // inf
extern const float g_01485548;             // 1.5f
extern const float g_013ec4d0;             // 100.0f
extern const float g_015ea5d0;             // plane point x (editor scratch vector)
extern const float g_015ea5d4;             // plane point y
extern const float g_015ea5d8;             // plane point z
extern cSPVector3 kSPUpAxis;               // 0x015ea68c (x at +0, y at +4, z at +8)

class cSPEditorPhysicsWorld {
 public:
  virtual void v00(); virtual void v04(); virtual void v08(); virtual int GetGroundObject();
};
class cSPEditorModel {
 public:
  cSPEditorPhysicsWorld* GetPhysicsWorld();   // 0x4ad450
  float GetGridSize();                        // 0x4adaa0
  float GetMinHeight();                       // 0x4adb00
  float GetMaxHeight();                       // 0x4adb40
  bool IsUsingSymmetry();                     // 0x4adc40
};
int F493640(cSPVector3* pos, float f0, float fa, float fb, int i);   // 0x493640
void BuildPileList(cSPEditorBlock* block, void* list, int b);       // 0x48c790
void RemoveSymmetricPartners(cSPEditorBlock* block, void* list);    // 0x4961d0
void ClearSymmetry(cSPEditorBlock* block, void* list);              // 0x4a8860
float GetAlignmentPosition(cSPEditorBlock* block, void* list, cSPVector3 pos, cSPMatrix3 m2,
                           float* a, float* b, bool* c, int d, cSPMatrix3 m1);   // 0x490a70

class cSPPhysicsProbe { public: void Probe(); };   // call target reached through the object vtable (+0xc)
typedef void (__fastcall *ProbeFn)(void* self, void* edx, void* p, float f, cSPVector3* out);
struct cSPGridScratch {
  cSPVector3 v0;      // +0x00
  cSPVector3 v1;      // +0x10
  float f18;          // +0x18
  int pad[5];
};

typedef void (__fastcall *GetAabbFn)(void* self, void* edx, void* transform, float tol, void* out);
}

// @ 0x005b9840
void cSPEditorManipulation56::SetBlock(cSPEditorBlock* block, cSPVector3 offset, bool b) {
  cSPEditorBlock* old = mBlock;
  if (block != old) {
    if (block) block->AddRef();
    mBlock = block;
    if (old) old->Release();
  }
  mV3c = offset;
  m89 = b;
  if (!mBlock) return;

  cSPEditorModel* model = (cSPEditorModel*)mBlock->mEditorModel;
  m1c = mBlock->mpParent;
  m20 = mBlock->mpParent;
  mV48 = mBlock->mPosition3;

  cSPVector3 blockPos = mBlock->mPosition3;

  cSPVector3 camPos, camDir;
  App()->GetViewer()->GetCameraLocationInfo(&camPos, &camDir, 0, 0);

  mV78.x = -camDir.x;
  mV78.y = -camDir.y;
  mV78.z = 0.0f;

  float len = sqrtf(mV78.x * mV78.x + mV78.y * mV78.y + mV78.z * mV78.z);
  float inv = 1.0f / len;
  mV78.x *= inv;
  mV78.y *= inv;
  mV78.z *= inv;

  float scale = model->GetGridSize() * g_01471064;
  mV6c.x = mV78.x * g_01486e98 * scale;
  mV6c.y = mV78.y * g_01486e98 * scale;
  mV6c.z = mV78.z * g_01486e98 * scale;

  if (F493640(&blockPos, model->GetGridSize(), model->GetMinHeight(), model->GetMaxHeight(), 0) == 3) {
    float dotN6 = mV78.x * mV6c.x + mV78.y * mV6c.y + mV78.z * mV6c.z;
    float dotNC = mV78.x * camPos.x + mV78.y * camPos.y + mV78.z * camPos.z;
    if (dotNC != 0.0f) {
      float t = (mV78.x * blockPos.x + mV78.y * blockPos.y + mV78.z * blockPos.z + (-dotN6)) / (-dotNC);
      if (t >= 0.0f) mV6c = blockPos;
    }
  }

  cSPEditorPhysicsWorld* phys = model->GetPhysicsWorld();
  void* obj = (void*)*(int*)((char*)phys + 0xc);
  cSPPhysicsProbe* probe = (cSPPhysicsProbe*)*(void**)((char*)obj + 0x1c);
  cSPEditorPhysicsWorld* phys2 = model->GetPhysicsWorld();
  int e2 = *(int*)((char*)phys2 + 0xc);
  void* arg0 = (char*)*(void**)((char*)e2 + 0x58) + 0x10;
  cSPGridScratch scratch;
  void** vt = *(void***)probe;
  ProbeFn fn = (ProbeFn)vt[3];
  fn(probe, 0, arg0, 0.0f, &scratch.v0);
  g_015ea5a8 = scratch.f18;
}

// @ 0x005b94b0
bool cSPEditorManipulation56::DoOnMouseDown(int button, float x, float y, int modifiers) {
    (void)button; (void)x; (void)y; (void)modifiers;
    if (mChangedObject || m89) {
        unsigned att = *(unsigned*)((char*)mBlock + 0xdc8);
        uint32_t id = 0;
        bool post = true;
        if ((att >> 1) & 1) {
            id = 0x0428e920u;
        } else if (att & 0x4) {
            post = false;
        } else if (m89) {
            id = 0x8e04ce1au;
        } else {
            id = 0xda95baa5u;
        }
        if (post) {
            cSPEditorAnimatedEventInfo* ev = 0;
            void* raw = EASTL_allocator_allocate(0x30, (const char*)0x13eb430, 0, 0, 0, 0);
            if (raw) ev = ctorAnimatedEventInfo(raw);
            if (ev) ev->AddRef();
            void* model = 0;
            if (mBlock) model = *(void**)((char*)mBlock + 0x28);
            (*(cSPEditorAnimatedEventInfo**)&ev)->MessagePost(id, mBlock, model, 0, 0, 0.0f, 0, -1, 1.0f);
            if (ev) ev->Release();
        }
    }

    if (mBlock->mpParent) {
        mBlock->mpParent->SetUIState(m84, true, false, true);
    }
    UpdateBlockState(mBlock, &mVec, 1, 0, 0, 0, 1, 1);
    DeleteInvalidBlocks(mBlock, &mVec);
    return true;
}

// @ 0x005b9660
void cSPEditorManipulation56::Update(float dt) {
    cSPEditorBlock* block = mBlock;
    if (!block) return;

    cSPVector3 pos(block->mPosition3.x, block->mPosition3.y, block->mPosition3.z);
    if (pos.x == mV60.x && pos.y == mV60.y && pos.z == mV60.z) return;

    float s = dt * g_013f9428;
    cSPVector3 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(mV54.x, mV54.y, origin, dir);
    if (s > g_013ec478) s = g_013ec478;

    cSPVector3 newPos;
    newPos.x = pos.x + ((mV60.x - pos.x) * s) * g_013f6b68;
    newPos.y = pos.y + ((mV60.y - pos.y) * s) * g_013f6b68;
    newPos.z = pos.z + ((mV60.z - pos.z) * s) * g_013f6b68;
    Apply2(&newPos, 1);

    F496300(mBlock, &mVec, origin, dir, newPos, 0);
    SetSymmetricBlocksUIState(mBlock, &mVec, 0);
    UpdateBlockState(mBlock, &mVec, 1, 0, 0, 0, 1, 1);
}
// @ 0x005b9b40
//
// Projects the mouse ray onto the editor's working plane to produce the dragged position.
// `block` supplies the rigid body whose AABB gives the vertical snap target; `rayOrigin` /
// `rayDirection` are the world-space pick ray; `out` receives the resulting position.
void cSPEditorManipulation56::Other1(cSPEditorBlock* block, int mode, cSPVector3 rayOrigin,
                                     cSPVector3 rayDirection, cSPVector3* out) {
  (void)mode;
  cSPRigidBody* body = block->mpRigidBody;              // +0x18c

  cSPAabbScratch aabb;
  cSPVector3 bodyPos = body->GetPosition();
  float zDiff = block->mPosition3.z - bodyPos.z;

  void* shape = *(void**)((char*)body + 0x1c);          // collidable.m_shape
  void** shapeVt = *(void***)shape;
  GetAabbFn getAabb = (GetAabbFn)shapeVt[3];
  getAabb(shape, 0, (void*)0x15b9b20, 0.0f, &aabb);

  cSPEditorModel* model = (cSPEditorModel*)block->mEditorModel;
  float scale = g_013f781c;                             // +inf when no model
  if (model) scale = model->GetGridSize() * g_01485548;

  cSPVector3 dir = rayDirection;
  cSPVector3 origin = rayOrigin;
  float dirxySq = dir.x * dir.x + dir.y * dir.y;
  float dirLenSq = dirxySq + dir.z * dir.z;

  cSPVector3 nd(-dir.x, -dir.y, -dir.z);
  float s2 = -(dir.x * scale * nd.x + dir.y * scale * nd.y);
  float num1 = origin.x * nd.x + origin.y * nd.y + origin.z * nd.z + s2;
  float t = -(num1 / -dirLenSq);
  if (!(t >= 0.0f)) return;

  cSPVector3 hit = origin + dir * t;
  out->x = hit.x;
  out->y = hit.y;
  out->z = hit.z;

  float v = zDiff + hit.z - aabb.mMaxZ;
  if (g_015ea5a8 > v)
    out->z = hit.z + (g_015ea5a8 - v);

  cSPVector3 up = kSPUpAxis;
  float g = g_015ea5a8;
  float planeD = -(g * up.z + up.y * g_015ea5d4 + up.x * g_015ea5d0);
  float denom2 = dir.z * up.z + dir.y * up.y + dir.x * up.x;

  float dl = 0.0f;
  if (denom2 != 0.0f) {
    float t2 = -((origin.y * up.y + origin.z * up.z + origin.x * up.x + planeD) / denom2);
    if (t2 >= 0.0f) {
      cSPVector3 h2 = origin + dir * t2;
      float len = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(dirxySq)));
      float len2 = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(h2.x * h2.x + h2.y * h2.y + h2.z * h2.z)));
      float r = 1.0f / (len * len2);
      float proj = r * h2.x * (t2 * dir.x) + r * h2.y * (t2 * dir.y);
      dl = (proj < 0.0f) ? 1.0f : 0.0f;
    }
  }

  if (0.0f > origin.z)
    dl = (dl == 0.0f) ? 1.0f : 0.0f;
  if (dl == 0.0f) return;

  out->z = aabb.mMaxZ + g_015ea5a8;

  cSPVector3 A = mV6c;                                  // +0x6c
  cSPVector3 B = mV78;                                  // +0x78
  float c = g_013ec4d0;                                 // 100.0f
  float nAB = -(A.x * B.x + A.y * B.y + A.z * B.z);
  float px = out->x - c * dir.x;
  float py = out->y - c * dir.y;
  float pz = out->z - c * dir.z;

  float dotB = dir.z * B.z + dir.y * B.y + dir.x * B.x;
  if (!(dotB != 0.0f)) return;

  float val = -(px * B.x + py * B.y + pz * B.z + nAB) / dotB;
  if (val < 0.0f) return;

  out->x = px + dir.x * val;
  out->y = py + dir.y * val;
}


// @ 0x005ba0f0
namespace {
// dest vector head: mpBegin/mpEnd/mpCapacity, filled by the vector ctor + uninitialized copy.
struct EaVecCtorTarget {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
    void Ctor(int n, void* alloc);   // 0x66aec0: vector(n, alloc), thiscall, ret 8
};
void CopyAutoRefRange(void** result, void** first, void** last, void** dest, void* hint);  // 0x4b2220, cdecl
}

void* cSPEditorManipulation56::CopyOut(void* dst) {
    EaVecCtorTarget* out = (EaVecCtorTarget*)dst;
    out->Ctor(mVec.size(), &mVec.mAllocator[0]);
    void* copyEnd = 0;
    CopyAutoRefRange(&copyEnd, (void**)mVec.mpBegin, (void**)mVec.mpEnd, out->mpBegin, out);
    out->mpEnd = (void**)copyEnd;
    return dst;
}
// @ 0x005ba190 -- PARTIAL
void cSPEditorManipulation56::Other2(int a, cSPVector3 pos) {
  cSPEditorBlock* block = mBlock;
  cSPEditorModel* model = (cSPEditorModel*)block->mEditorModel;

  mVec.erase(mVec.mpBegin, mVec.mpEnd);
  BuildPileList(block, &mVec, 0);
  SetSymmetricBlocksUIState(block, &mVec, 0);

  if (block->mpParent) {
    m84 = *(int*)((char*)block->mpParent + 0x3c);
    block->mpParent->SetUIState(2, true, false, true);
  }

  cSPEditorBlock** end = mVec.mpEnd;
  mVec.erase(eastl::remove(mVec.mpBegin, end, block), end);
  RemoveSymmetricPartners(block, &mVec);
  if (!model->IsUsingSymmetry())
    ClearSymmetry(block, &mVec);
  SetSymmetricBlocksUIState(block, &mVec, 0);

  block->F43bbc0(0);

  mV60 = block->mPosition3;
  mV54 = pos;

  float ra = 0.0f, rb = 0.0f;
  bool flagC = false;
  float r = GetAlignmentPosition(block, &mVec, block->mPosition3, block->mTransform, &ra, &rb, &flagC, a,
                                 block->mTransform);
  if (!(r == g_013eb1bc)) m8a = true;
}

}  // namespace SP
