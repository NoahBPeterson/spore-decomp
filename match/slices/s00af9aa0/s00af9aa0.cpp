// Slice s00af9aa0: a Havok-listener object (hkArray of uint + hkEntityListener base at +0x60),
// SP::cActionCircle slot helpers (tSlot vector at +0x50), tSlot copy/reserve helpers, and a few
// free-standing math / copy loops. Reconstructed from the retail disassembly.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// external globals (values are masked by relocation; symbol identity is what matters)
// ---------------------------------------------------------------------------
extern float g_fOne;          // 0x1485720 = 1.0f
extern float g_f200;          // 0x1477fbc = 200.0f
extern float g_fPiOver3;      // 0x1567344 = 1.0471976f
extern int   g_n16;           // 0x1567338 = 16
extern float g_fFLTMax;       // 0x145c45c = FLT_MAX
extern float g_fEps;          // 0x13ec4b8 = 1e-8f
extern float g_fPoint01;      // 0x13eb960 = 0.01f
extern float g_fNegPoint01;   // 0x140ced4 = -0.01f
extern float g_quatIdent[4];  // 0x156737c = {0,0,0,1}
extern float g_defFacing[4];  // 0x167af08
extern float g_defCenter[3];  // 0x167aec4
extern float g_altZero[1];    // 0x167af10 continues defFacing

extern void* g_vftableA;      // 0x145c428
extern void* g_vftableB;      // 0x145c414

extern unsigned long g_hkThreadMemoryTls;   // 0x16e4174

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);

namespace hkArrayUtil {
void _reserveMore(void* array, int elemSize);                  // 0x107f530
void _reserveExactly(void* array, int count, int elemSize);    // 0x107f4a0
}

class hkThreadMemory {
 public:
  void deallocateChunk(void* p, int size, int align);          // 0x107db10
};

namespace EA {

class IRefCounted {
 public:
  virtual int AddRef();
  virtual int Release();
};

template <class T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) {
      T* const old = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}  // namespace EA

namespace SP {

struct cSPVector3 { float mX, mY, mZ; };
struct cSPQuaternion { float x, y, z, w; };

class cGameData : public EA::IRefCounted {};

class cInteractionAgent : public EA::IRefCounted {};

// ---------------------------------------------------------------------------
// SP::cActionCircle -- only the members needed here are modelled (mSlots at +0x50)
// ---------------------------------------------------------------------------
class cActionCircle {
 public:
  class tSlot { public:
    bool mOccupied;                                 // +0x0
    char _pad0[3];
    EA::AutoRefCount<cGameData> mpReservingNoun;    // +0x4
    unsigned int mReservingId;                      // +0x8
    cSPVector3 mPos;                                // +0xc

    void Reserve(cGameData* noun);                  // 0xafa030
    void ReserveId(unsigned int id);                // 0xafa070
    void Clear();                                   // 0xafa0a0
    tSlot* CopyConstruct(const tSlot* src);         // 0xafa110
    tSlot* Assign(const tSlot* src);                // 0xafa230
  };

  cSPVector3 mFacing;                               // +0x0
  float mRadius;                                    // +0xc
  float mSlotRadius;                                // +0x10
  cSPVector3 mCenter;                               // +0x14
  float mAltitude;                                  // +0x20
  int mPacking;                                     // +0x24
  bool mbRelative;                                  // +0x28
  char _pad28[3];
  cSPQuaternion mOrientation;                       // +0x2c
  struct SlotVec {                                  // eastl::sp_vector<Agent> at +0x3c
    EA::AutoRefCount<cInteractionAgent>* mpBegin;
    EA::AutoRefCount<cInteractionAgent>* mpEnd;
    EA::AutoRefCount<cInteractionAgent>* mpCapacity;
    int mAllocator[2];
  } mAgents;
  struct SlotVector {                               // eastl::sp_vector<tSlot> at +0x50
    tSlot* mpBegin;
    tSlot* mpEnd;
    tSlot* mpCapacity;
    int mAllocator[2];
  } mSlots;

  void SetAtCenter(const cSPVector3* center, float radius, const cSPVector3* facing, float altitude);  // 0xaf9cf0
  void SetRelative(const cSPVector3* center, const cSPQuaternion* orient, float radius);              // 0xaf9d60
  int IsNonDefault() const;                          // 0xaf9ee0
  tSlot* FindFreeSlot();                             // 0xaf9f30
  int CountFreeSlots();                              // 0xaf9f60
  int CountOccupiedSlots();                          // 0xaf9fa0
  tSlot* SlotAt(unsigned int index);                 // 0xaf9ff0
  int FindClosestFreeSlot(const cSPVector3* p);      // 0xafa5d0
  int FindClosestFreeSlotWeighted(const cSPVector3* p, const cSPVector3* q, float weight);  // 0xafa7c0
};

// ---------------------------------------------------------------------------
// Havok listener object (vtable at +0x60, hkArray<uint> at +0x9c)
// ---------------------------------------------------------------------------
struct hkArrayUint {
  unsigned int* m_data;      // +0x0
  int m_size;                // +0x4
  int m_capacityAndFlags;    // +0x8

  void push_back(unsigned int v) {
    if (m_size == (m_capacityAndFlags & 0x3fffffff))
      hkArrayUtil::_reserveMore(this, 4);
    m_data[m_size] = v;
    m_size++;
  }
};

class cEntityListener {
 public:
  bool m0;                    // +0x0
  char _pad0[3];
  void* m4;                   // +0x4
  char _pad8[8];              // +0x8
  float m10, m14, m18, m1c;   // +0x10
  float m20, m24, m28, m2c;   // +0x20
  float m30, m34, m38;        // +0x30
  bool m3c;                   // +0x3c
  char _pad3c[3];
  float m40, m44;             // +0x40
  char m48, m49, m4a;         // +0x48
  char _pad4b;
  int m4c;                    // +0x4c
  float m50, m54, m58, m5c;   // +0x50
  void* m_vtbl;               // +0x60
  cEntityListener* m64;       // +0x64
  void* m68;                  // +0x68
  char _pad6c[4];             // +0x6c
  float m70, m74, m78, m7c;   // +0x70
  float m80, m84, m88, m8c;   // +0x80
  float m90, m94, m98;        // +0x90
  hkArrayUint m9c;            // +0x9c
  float mac;                  // +0xac
  int mb0, mb4;               // +0xb0

  void Attach(int, int, int);          // 0xaf8840
  void AddId(unsigned int id);         // 0xaf9ac0
  void RemoveId(unsigned int id);      // 0xaf9b00
  cEntityListener();                   // 0xaf9b50
  void Destroy();                      // 0xaf9ca0
};

// Holder that owns a pointer to a listener at +0x4.
class cListenerHolder {
 public:
  char _pad0[4];
  cEntityListener* m_pListener;        // +0x4
  void Detach(int unused);             // 0xaf9aa0
};

}  // namespace SP

using SP::cSPVector3;
using SP::cSPQuaternion;
using SP::cEntityListener;
using SP::cActionCircle;
using SP::cGameData;

namespace eastl {

// Functor whose only state is the query origin; operator() lives at 0xac0730.
struct AgentDistanceCompare {
  cSPVector3 mOrigin;
  bool operator()(SP::cInteractionAgent* a, SP::cInteractionAgent* b) const;
};

}  // namespace eastl

// ===========================================================================
// @ 0xaf9aa0
// ===========================================================================
void SP::cListenerHolder::Detach(int unused) {
  m_pListener->Attach(0, 0, 0);
}

// ===========================================================================
// @ 0xaf9ac0
// ===========================================================================
void SP::cEntityListener::AddId(unsigned int id) {
  m9c.push_back(id);
}

// ===========================================================================
// @ 0xaf9b00
// ===========================================================================
void SP::cEntityListener::RemoveId(unsigned int id) {
  int i = 0;
  int n = m9c.m_size;
  if (0 < n) {
    unsigned int* p = m9c.m_data;
    do {
      if (*p == id) goto found;
      i++;
      p++;
    } while (i < n);
    return;
  found:
    if (i != -1) {
      m9c.m_size--;
      m9c.m_data[i] = m9c.m_data[m9c.m_size];
    }
  }
}

// ===========================================================================
// @ 0xaf9b50
// ===========================================================================
SP::cEntityListener::cEntityListener() {
  float one = g_fOne;
  float twohundred = g_f200;
  m_vtbl = &g_vftableA;
  m9c.m_data = 0;
  m9c.m_size = 0;
  m9c.m_capacityAndFlags = (int)0x80000000;
  m0 = false;
  m10 = m14 = m18 = m1c = 0.0f;
  m20 = m24 = m28 = m2c = 0.0f;
  m30 = one;
  m34 = one;
  m38 = 0.0f;
  m3c = true;
  m40 = 0.0f;
  m44 = twohundred;
  m4c = 0;
  m50 = 0.0f;
  m54 = 0.0f;
  m58 = one;
  m5c = 0.0f;
  m64 = this;
  m68 = 0;
  m70 = m74 = m78 = m7c = 0.0f;
  m80 = m84 = m88 = m8c = 0.0f;
  m48 = 0;
  m49 = 0;
  m4a = 0;
  m90 = g_fPiOver3;
  m94 = (float)cos(g_fPiOver3);
  m98 = 0.0f;
  if ((m9c.m_capacityAndFlags & 0x3fffffff) < g_n16)
    hkArrayUtil::_reserveExactly(&m9c, g_n16, 4);
  mac = one;
  mb0 = 0;
  mb4 = 0;
}

// ===========================================================================
// @ 0xaf9ca0
// ===========================================================================
void SP::cEntityListener::Destroy() {
  Attach(0, 0, 0);
  if ((m9c.m_capacityAndFlags & 0x80000000) == 0) {
    int count = m9c.m_capacityAndFlags & 0x3fffffff;
    hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    tm->deallocateChunk(m9c.m_data, count * 4, 0x14);
  }
  m_vtbl = &g_vftableB;
}

// ===========================================================================
// @ 0xaf9cf0
// ===========================================================================
void SP::cActionCircle::SetAtCenter(const cSPVector3* center, float radius,
                                    const cSPVector3* facing, float altitude) {
  mbRelative = false;
  mOrientation.x = g_quatIdent[0];
  mOrientation.y = g_quatIdent[1];
  mOrientation.z = g_quatIdent[2];
  mOrientation.w = g_quatIdent[3];
  mCenter = *center;
  mRadius = radius;
  mFacing = *facing;
  mAltitude = altitude;
}

// ===========================================================================
// @ 0xaf9d60
// ===========================================================================
void SP::cActionCircle::SetRelative(const cSPVector3* center, const cSPQuaternion* orient,
                                    float radius) {
  mbRelative = true;
  mOrientation = *orient;
  mCenter = *center;
  mRadius = radius;
  mFacing.mX = g_defFacing[0];
  mFacing.mY = g_defFacing[1];
  mFacing.mZ = g_defFacing[2];
  mAltitude = 0.0f;
}

// ===========================================================================
// @ 0xaf9dd0
// ===========================================================================
long double FUN_00af9dd0(float param_1, int param_2) {
  param_2 = param_2 - 1;
  float step = param_1 * 2.0f;
  if (0 < param_2) {
    int i = 6;
    do {
      param_2 = param_2 - i;
      param_1 = step + param_1;
      i = i + 6;
    } while (0 < param_2);
  }
  return (long double)param_1;
}

// ===========================================================================
// @ 0xaf9e20
// ===========================================================================
long double FUN_00af9e20(float param_1, int param_2) {
  param_2 = param_2 - 1;
  float f = param_1 * 2.0f;
  int i = 2;
  while (0 < param_2) {
    f = f + param_1 * 2.0f;
    param_2 = param_2 - i;
    i = i + 1;
  }
  return (long double)f;
}

// ===========================================================================
// @ 0xaf9ee0
// ===========================================================================
int SP::cActionCircle::IsNonDefault() const {
  if (mCenter.mX == g_defCenter[0] && mCenter.mY == g_defCenter[1] &&
      mCenter.mZ == g_defCenter[2] && !mbRelative)
    return 0;
  return 1;
}

// ===========================================================================
// @ 0xaf9f30
// ===========================================================================
SP::cActionCircle::tSlot* SP::cActionCircle::FindFreeSlot() {
  tSlot* e = mSlots.mpEnd;
  tSlot* p = mSlots.mpBegin;
  while (p != e && p->mOccupied) p++;
  return (p != e) ? p : 0;
}

// ===========================================================================
// @ 0xaf9f60
// ===========================================================================
int SP::cActionCircle::CountFreeSlots() {
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (!mSlots.mpBegin[i].mOccupied) count++;
  }
  return count;
}

// ===========================================================================
// @ 0xaf9fa0
// ===========================================================================
int SP::cActionCircle::CountOccupiedSlots() {
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  int c = 0;
  tSlot* p = mSlots.mpBegin;
  for (int i = 0; i < n; i++) {
    if (!p->mOccupied) c++;
    p++;
  }
  return (int)(mSlots.mpEnd - mSlots.mpBegin) - c;
}

// ===========================================================================
// @ 0xaf9ff0
// ===========================================================================
SP::cActionCircle::tSlot* SP::cActionCircle::SlotAt(unsigned int index) {
  if (index < (unsigned int)(mSlots.mpEnd - mSlots.mpBegin))
    return mSlots.mpBegin + index;
  return 0;
}

// ===========================================================================
// @ 0xafa030
// ===========================================================================
void SP::cActionCircle::tSlot::Reserve(cGameData* noun) {
  mOccupied = true;
  mpReservingNoun = noun;
}

// ===========================================================================
// @ 0xafa070
// ===========================================================================
void SP::cActionCircle::tSlot::ReserveId(unsigned int id) {
  mOccupied = true;
  mReservingId = id;
  cGameData* old = mpReservingNoun.mpObject;
  mpReservingNoun.mpObject = (cGameData*)0;
  if (old) old->Release();
}

// ===========================================================================
// @ 0xafa0a0
// ===========================================================================
void SP::cActionCircle::tSlot::Clear() {
  mOccupied = false;
  mReservingId = 0;
  mpReservingNoun = (cGameData*)0;
}

// ===========================================================================
// @ 0xafa0c0
// ===========================================================================
void FUN_00afa0c0(cSPVector3* dst, const cSPVector3* a, const cSPVector3* b, const cSPVector3* c) {
  dst[0] = *c;
  dst[1] = *a;
  dst[2] = *b;
}

// ===========================================================================
// @ 0xafa110
// ===========================================================================
SP::cActionCircle::tSlot* SP::cActionCircle::tSlot::CopyConstruct(const tSlot* src) {
  mOccupied = src->mOccupied;
  mpReservingNoun.mpObject = src->mpReservingNoun.mpObject;
  if (mpReservingNoun.mpObject) mpReservingNoun.mpObject->AddRef();
  mReservingId = src->mReservingId;
  mPos.mX = src->mPos.mX;
  mPos.mY = src->mPos.mY;
  mPos.mZ = src->mPos.mZ;
  return this;
}

// ===========================================================================
// @ 0xafa230
// ===========================================================================
SP::cActionCircle::tSlot* SP::cActionCircle::tSlot::Assign(const tSlot* src) {
  mOccupied = src->mOccupied;
  mpReservingNoun = src->mpReservingNoun.mpObject;
  mReservingId = src->mReservingId;
  mPos = src->mPos;
  return this;
}

// ===========================================================================
// @ 0xafa290
// ===========================================================================
void FUN_00afa290(EA::AutoRefCount<SP::cInteractionAgent>* first,
                  EA::AutoRefCount<SP::cInteractionAgent>* last,
                  eastl::AgentDistanceCompare cmp) {
  for (; first != last; ++first) {
    SP::cInteractionAgent* cur = first->mpObject;
    if (cur) cur->AddRef();
    EA::AutoRefCount<SP::cInteractionAgent>* hole = first;
    while (cmp(cur, (hole - 1)->mpObject)) {
      EA::AutoRefCount<SP::cInteractionAgent>* prev = hole - 1;
      hole->mpObject = prev->mpObject;
      prev->mpObject = 0;
      hole = prev;
    }
    hole->mpObject = cur;
    if (cur) cur->Release();
  }
}

// ===========================================================================
// @ 0xafa380
// ===========================================================================
SP::cActionCircle::tSlot* FUN_00afa380(SP::cActionCircle::tSlot* first,
                                       SP::cActionCircle::tSlot* last,
                                       SP::cActionCircle::tSlot* dst) {
  while (first != last) {
    dst->CopyConstruct(first);
    first++;
    dst++;
  }
  return dst;
}

// ===========================================================================
// @ 0xafa430
// ===========================================================================
SP::cActionCircle::tSlot* FUN_00afa430(SP::cActionCircle::tSlot* first,
                                       SP::cActionCircle::tSlot* last,
                                       SP::cActionCircle::tSlot* dst) {
  while (first != last) {
    dst->Assign(first);
    first++;
    dst++;
  }
  return dst;
}

// ===========================================================================
// @ 0xafa4a0
// ===========================================================================
SP::cActionCircle::tSlot* FUN_00afa4a0(SP::cActionCircle::tSlot* first,
                                       SP::cActionCircle::tSlot* last,
                                       SP::cActionCircle::tSlot* dst) {
  while (last != first) {
    last--;
    dst--;
    dst->Assign(last);
  }
  return dst;
}

// ===========================================================================
// @ 0xafa510
// ===========================================================================
extern void* SP_PlanetModel(void* out, const float* dir);              // 0xb3d350
struct cPlanetModel {
  float* __thiscall DirectionToSurfacePosition(void* out, const float* dir);  // 0xb815a0
};

void FUN_00afa510(float* out, const float* dir, float radius) {
  float dx = dir[0];
  float dy = dir[1];
  float dz = dir[2];
  float inv = 1.0f / (float)sqrt((double)((dx * dx + dy * dy) + dz * dz) + g_fEps);
  float local[3];
  cPlanetModel* model = (cPlanetModel*)SP_PlanetModel(local, dir);
  float* surf = model->DirectionToSurfacePosition(local, dir);
  out[0] = surf[0] + (dx * inv) * radius;
  out[1] = surf[1] + (dy * inv) * radius;
  out[2] = surf[2] + (dz * inv) * radius;
}

// ===========================================================================
// @ 0xafa5d0
// ===========================================================================
int SP::cActionCircle::FindClosestFreeSlot(const cSPVector3* p) {
  float best = g_fFLTMax;
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  int i = 0;
  int found = -1;
  if (3 < n) {
    tSlot* a = mSlots.mpBegin;
    tSlot* b = mSlots.mpBegin + 1;
    tSlot* c = mSlots.mpBegin + 2;
    tSlot* d = mSlots.mpBegin + 3;
    do {
      if (!a->mOccupied) {
        float dx = p->mX - a->mPos.mX, dy = p->mY - a->mPos.mY, dz = p->mZ - a->mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i; best = dist; }
      }
      if (!b->mOccupied) {
        float dx = p->mX - b->mPos.mX, dy = p->mY - b->mPos.mY, dz = p->mZ - b->mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 1; best = dist; }
      }
      if (!c->mOccupied) {
        float dx = p->mX - c->mPos.mX, dy = p->mY - c->mPos.mY, dz = p->mZ - c->mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 2; best = dist; }
      }
      if (!d->mOccupied) {
        float dx = p->mX - d->mPos.mX, dy = p->mY - d->mPos.mY, dz = p->mZ - d->mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 3; best = dist; }
      }
      i += 4;
      a += 4;
      b += 4;
      c += 4;
      d += 4;
    } while (i < n - 3);
  }
  for (; i < n; i++) {
    tSlot* s = mSlots.mpBegin + i;
    if (!s->mOccupied) {
      float dx = p->mX - s->mPos.mX, dy = p->mY - s->mPos.mY, dz = p->mZ - s->mPos.mZ;
      float dist = (dx * dx + dy * dy) + dz * dz;
      if (dist < best) { found = i; best = dist; }
    }
  }
  return found;
}

// ===========================================================================
// @ 0xafa7c0
// ===========================================================================
int SP::cActionCircle::FindClosestFreeSlotWeighted(const cSPVector3* p, const cSPVector3* q, float weight) {
  float best = g_fFLTMax;
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  int i = 0;
  int found = -1;
  if (3 < n) {
    tSlot* a = mSlots.mpBegin;
    tSlot* b = mSlots.mpBegin + 1;
    tSlot* c = mSlots.mpBegin + 2;
    tSlot* d = mSlots.mpBegin + 3;
    do {
      if (!a->mOccupied) {
        float px = p->mX - a->mPos.mX, py = p->mY - a->mPos.mY, pz = p->mZ - a->mPos.mZ;
        float qx = q->mX - a->mPos.mX, qy = q->mY - a->mPos.mY, qz = q->mZ - a->mPos.mZ;
        float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
        if (dist < best) { found = i; best = dist; }
      }
      if (!b->mOccupied) {
        float px = p->mX - b->mPos.mX, py = p->mY - b->mPos.mY, pz = p->mZ - b->mPos.mZ;
        float qx = q->mX - b->mPos.mX, qy = q->mY - b->mPos.mY, qz = q->mZ - b->mPos.mZ;
        float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
        if (dist < best) { found = i + 1; best = dist; }
      }
      if (!c->mOccupied) {
        float px = p->mX - c->mPos.mX, py = p->mY - c->mPos.mY, pz = p->mZ - c->mPos.mZ;
        float qx = q->mX - c->mPos.mX, qy = q->mY - c->mPos.mY, qz = q->mZ - c->mPos.mZ;
        float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
        if (dist < best) { found = i + 2; best = dist; }
      }
      if (!d->mOccupied) {
        float px = p->mX - d->mPos.mX, py = p->mY - d->mPos.mY, pz = p->mZ - d->mPos.mZ;
        float qx = q->mX - d->mPos.mX, qy = q->mY - d->mPos.mY, qz = q->mZ - d->mPos.mZ;
        float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
        if (dist < best) { found = i + 3; best = dist; }
      }
      i += 4;
      a += 4;
      b += 4;
      c += 4;
      d += 4;
    } while (i < n - 3);
  }
  for (; i < n; i++) {
    tSlot* s = mSlots.mpBegin + i;
    if (!s->mOccupied) {
      float px = p->mX - s->mPos.mX, py = p->mY - s->mPos.mY, pz = p->mZ - s->mPos.mZ;
      float qx = q->mX - s->mPos.mX, qy = q->mY - s->mPos.mY, qz = q->mZ - s->mPos.mZ;
      float dist = ((py * py + px * px + pz * pz) * weight + qz * qz) + qy * qy + qx * qx;
      if (dist < best) { found = i; best = dist; }
    }
  }
  return found;
}
