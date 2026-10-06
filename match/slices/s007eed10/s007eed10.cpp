// Slice s007eed10: SP / EA::Swarm volume-effect state, its ArgScript commands,
// and the binary-heap helpers used by the volume's key frame queue.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE  (scalar movss/comiss with x87 float
// returns; see the neighbouring s007ee060 / s007ef42e0 slices).
#include "types.h"
#include <new>

#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]

// ---------------------------------------------------------------------------
// Volume-key track (vtable 0x01414920): the object built by 0x007EF630.
// ---------------------------------------------------------------------------
struct KeyFrame {
  char pad0[8];
  float k0;   // +0x8
  char pad1[8];
  float k1;   // +0x14
};

struct CTrack {
  char pad0[0x10];
  int mDataOffset;   // +0x10
  void* mpIface;     // +0x14
  bool mActive;      // +0x18
  char pad1[3];
  int mIndex;        // +0x1c
  int m20;           // +0x20
  int mOther;        // +0x24
  float mValue;      // +0x28
  float mMin;        // +0x2c
  float mMax;        // +0x30

  void Slot0(void* a, void* b);
  void Slot1();
  void Slot2(int);
  void Slot3(int);
  bool SetKey(int id, KeyFrame* k, int);
  void Eval(int, float t, int);
};

// @ 0x007EF2A0
void CTrack::Slot0(void* a, void* b) {
  mpIface = ((void*(__thiscall*)(void*))VSLOT(a, 0x20))(a);
  mOther = ((int(__thiscall*)(void*))VSLOT(b, 0xa0))(b);
  if (mpIface) {
    char loc[0x24] = {0};
    ((void(__thiscall*)(void*, void*, void*))VSLOT(mpIface, 0x18))(mpIface, loc, &mIndex);
    ((void(__thiscall*)(void*, int, void*))VSLOT(mpIface, 0x10))(mpIface, 7, &m20);
  }
}

// @ 0x007EF350
void CTrack::Slot1() {
  if (mIndex >= 0)
    ((void(__thiscall*)(void*, int))VSLOT(mpIface, 0x1c))(mpIface, mIndex);
}

// @ 0x007EF370
void CTrack::Slot2(int) {
  if (mpIface && !mActive) {
    mActive = true;
    if (mIndex >= 0)
      ((void(__thiscall*)(void*, int, int))VSLOT(mpIface, 0x24))(mpIface, mIndex, 1);
  }
}

// @ 0x007EF3A0
void CTrack::Slot3(int) {
  if (mActive) {
    mActive = false;
    if (mIndex >= 0)
      ((void(__thiscall*)(void*, int, int))VSLOT(mpIface, 0x24))(mpIface, mIndex, 0);
  }
}

// @ 0x007EF450
bool CTrack::SetKey(int id, KeyFrame* k, int) {
  if (id != 0x101) return false;
  mMin = k->k0;
  mMax = k->k1;
  return true;
}

// @ 0x007EF480
void CTrack::Eval(int, float t, int) {
  mValue = (mMax - mMin) * t + mMin;
}

// ---------------------------------------------------------------------------
// Binary heap of 16-byte nodes (first member double).  push/adjust/make_heap
// and the priority-queue push that wraps them.
// ---------------------------------------------------------------------------
struct HeapNode {
  double d;
  uint32_t x, y;
};
inline bool operator<(const HeapNode& a, const HeapNode& b) { return a.d < b.d; }

struct EmptyCmp { char x; };

// @ 0x007EF3D0
void SiftUp(HeapNode* first, int top, int hole, HeapNode value, EmptyCmp) {
  int parent = (hole - 1) >> 1;
  while (hole > top && first[parent] < value) {
    first[hole] = first[parent];
    hole = parent;
    parent = (hole - 1) >> 1;
  }
  first[hole] = value;
}

// @ 0x007EF4A0
void AdjustHeap(HeapNode* first, int top, int length, int hole, HeapNode value, EmptyCmp cmp) {
  int child = hole * 2 + 2;
  while (child < length) {
    if (first[child] < first[child - 1]) --child;
    first[hole] = first[child];
    hole = child;
    child = hole * 2 + 2;
  }
  if (child == length) {
    first[hole] = first[child - 1];
    hole = child - 1;
  }
  SiftUp(first, top, hole, value, cmp);
}

// @ 0x007EF5D0
void MakeHeap(HeapNode* first, HeapNode* last, EmptyCmp cmp) {
  int len = (int)(last - first);
  if (len < 2) return;
  int parent = ((len - 2) >> 1) + 1;
  do {
    --parent;
    HeapNode value = first[parent];
    AdjustHeap(first, parent, len, parent, value, cmp);
  } while (parent != 0);
}

struct PQ {
  HeapNode* mpBegin;     // +0x00
  HeapNode* mpEnd;       // +0x04
  HeapNode* mpCapacity;  // +0x08
  char pad[8];
  EmptyCmp mCmp;         // +0x14

  void DoInsertValue(void* position, const HeapNode& v);
  void Push(const HeapNode& v);
};

// ---------------------------------------------------------------------------
// Volume-state object (vtable 0x01414920) built at 0x007EF630.
// ---------------------------------------------------------------------------
struct Matrix3 {
  float v[9];
  void Assign(const void* p);
  Matrix3(const void* p) { Assign(p); }
  Matrix3() {}
};

struct VBaseA { virtual void va(); };
struct VBaseB { virtual void vb(); int mB; VBaseB() : mB(0) {} };
struct VBaseC { virtual void vc(); };

extern float g_v2c, g_v30, g_v38, g_v3c, g_v40;
extern const float g_mat3[9];
extern void BufDealloc(void* p);

struct Buf {
  void* begin;  // +0
  void* end;    // +4
  void* cap;    // +8
  ~Buf() { if (begin != 0 && ((int*)begin)[-1] != 0) BufDealloc(begin); }
};

struct VolState : VBaseA, VBaseB, VBaseC {
  int m10;             // +0x10
  void* m14;           // +0x14
  bool m18;            // +0x18
  char pad18[3];
  int m1c;             // +0x1c
  int m20;             // +0x20 (uninitialized)
  int m24;             // +0x24
  float m28, m2c, m30; // +0x28
  short m34, m36;      // +0x34
  float m38, m3c, m40, m44;  // +0x38
  Matrix3 m48;         // +0x48
  uint32_t mSamples[0x30];   // +0x6c .. +0x12c
  void* vA_begin;      // +0x12c
  void* vA_end;        // +0x130
  void* vA_cap;        // +0x134
  int g138, g13c;      // +0x138
  void* vB_begin;      // +0x140
  void* vB_end;        // +0x144
  void* vB_cap;        // +0x148
  VolState(int a);
};

// @ 0x007EF630
VolState::VolState(int a) {
  m10 = a;
  m14 = 0;
  m18 = false;
  m1c = -1;
  m24 = 0;
  m28 = 1.0f;
  m2c = g_v2c;
  m30 = g_v30;
  m34 = 0;
  m36 = 0;
  m38 = g_v38;
  m3c = g_v3c;
  m40 = g_v40;
  m44 = 1.0f;
  m48.Assign(g_mat3);
  vA_begin = 0;
  vA_end = 0;
  vA_cap = 0;
  vB_begin = 0;
  vB_end = 0;
  vB_cap = 0;
}

// @ 0x007EF560
void VolStateDestroy(VolState* self) {
  if (self->vB_begin != 0 && ((int*)self->vB_begin)[-1] != 0) BufDealloc(self->vB_begin);
  if (self->vA_begin != 0 && ((int*)self->vA_begin)[-1] != 0) BufDealloc(self->vA_begin);
}

// ---------------------------------------------------------------------------
// cVolumeEffectCommand (vtable 0x01414744): cBlockCommandT<cEffectsParser>
// base + cVolumeState + an EASTL string.  0x007EF220 is its scalar deleting
// destructor.
// ---------------------------------------------------------------------------
extern void EAllocDealloc(void* p);

struct EString {
  char* mpBegin;  // +0
  char* mpEnd;    // +4
  char* mpCap;    // +8
  ~EString() {
    if (mpCap - mpBegin > 1 && mpBegin != 0) EAllocDealloc(mpBegin);
  }
};

struct cVolumeDescLite {
  virtual ~cVolumeDescLite() {}
  int mRef;
};
struct cBlockCommandBase {
  virtual ~cBlockCommandBase();
  char pad[0x34];
};
struct cVolumeStateLite {
  char pad[8];
  cVolumeDescLite mDesc;   // +0x40 in the derived object
  char pad2[0x130 - 0x44];
};
struct cVolumeEffectCommand : cBlockCommandBase {
  cVolumeStateLite mVolumeState;  // +0x38
  EString mDescName;              // +0x130
  virtual void Execute(void* args);
};
void ForceVolumeEffect() {
  cVolumeEffectCommand* p = new cVolumeEffectCommand;
  delete p;
}

// @ 0x007EFC90
void PQ::Push(const HeapNode& v) {
  if (mpEnd < mpCapacity) {
    HeapNode* p = mpEnd++;
    new (p) HeapNode(v);
  } else {
    DoInsertValue(mpEnd, v);
  }
  SiftUp(mpBegin, 0, (int)(mpEnd - mpBegin) - 1, *(mpEnd - 1), mCmp);
}

// ===========================================================================
// Remaining slice functions.  These are behaviourally approximate (the exact
// ArgScript/SSE scheduling was not reproduced); see partial.txt.
// ===========================================================================
extern void* ArgMainArguments(void* args, void* out, int a, int b);
extern int ArgParseEnum(void* s, const char* name);
extern void ArgThrow(void* err, const char* msg);
extern void* GetInherited(void* parser, void* args, int n, int size);

// @ 0x007EED10  cVolumeSetCommand::Execute
void VolumeSetExecute(void* self, void* args) {
  int count = 0;
  void** a = (void**)ArgMainArguments(args, &count, 2, 8);
  int sel = ArgParseEnum(a[0], "corner");
  switch (sel) {
    case 0: {
      if (count < 5) ArgThrow(0, "Wrong number of arguments.");
      int* dst = *(int**)((char*)self + 0xc);
      dst[0] = 0;  // corner 0
      break;
    }
    case 1:
    case 2:
    case 3:
      if (count < 2) ArgThrow(0, "Wrong number of arguments.");
      break;
    default:
      break;
  }
}

// @ 0x007EF080  cVolumeEffectCommand::Execute
void VolumeEffectExecute(void* self, void* args) {
  int count = 0;
  void** a = (void**)ArgMainArguments(args, &count, 1, 3);
  const char* name = (const char*)a[0];
  int n = 0;
  while (name[n] != 0) ++n;
  ((void(__thiscall*)(void*, const char*, int))VSLOT((char*)self + 0x130, 0))(0, name, n);
  if (count > 1) {
    void* inh = GetInherited(*(void**)((char*)self + 0x30), a, count, 0x28);
    (void)inh;
  }
  ((void(__thiscall*)(void*))VSLOT(*(void**)((char*)self + 4), 0x8c))(self);
}

// @ 0x007EF120  CommandManager::RegisterVolumeCommands
extern void* EAAlloc6(unsigned size, const char* name, int, int, const char*, int);
void RegisterVolumeCommands(void* unused, void* mgr) {
  void* cmd = EAAlloc6(0x140, "ArgScript/VolumeEffect", 0, 0, 0, 0);
  if (cmd) {
    // ... base + cVolumeState + string construction elided
  }
  ((void(__thiscall*)(void*, void*, void*))VSLOT(*(void**)mgr, 0x14))(mgr, cmd, "volume");
  void* grp = EAAlloc6(0x10, "ArgScript/GroupVolume", 0, 0, 0, 0);
  ((void(__thiscall*)(void*, void*, void*))VSLOT(*(void**)mgr, 0x18))(mgr, grp, "volume");
}

// @ 0x007EF730  VolState::UpdateFromFrame
void VolStateUpdate(VolState* self, int arg, unsigned short* frame) {
  // Approximate: apply the frame transform to the 8 sample points, accumulate
  // their bounding box and hand it to the interface.
  float lo[3] = { 0, 0, 0 }, hi[3] = { 0, 0, 0 };
  for (int i = 0; i < 8; ++i) {
    float* p = (float*)((char*)self + 0x74 + i * 0x18 - 8);
    for (int k = 0; k < 3; ++k) {
      if (p[k] < lo[k]) lo[k] = p[k];
      if (p[k] > hi[k]) hi[k] = p[k];
    }
  }
  (void)arg;
  (void)frame;
  ((void(__thiscall*)(void*, int, void*, int))VSLOT(self->m14, 0x20))(self->m14, self->m1c, lo, 0);
}

// @ 0x007EFA20  vector<T(24)>::insert
extern void* EAAlloc6v2(unsigned size, const char* tag, int, int, const char* file, int line);
extern void MoveRange24(void* dst, void* src, void* end);
extern void MoveConstruct(void* dst, void* src);
void Vec24Insert(void* self, void* position, void* value) {
  char* end = *(char**)((char*)self + 4);
  char* cap = *(char**)((char*)self + 8);
  if (end == cap) return;  // reallocation path elided
  if (position <= value && value < end) value = (char*)value + 0x18;
  if (end) MoveConstruct(end, end - 0x18);
  MoveRange24(position, end - 0x18, end);
  *(void**)position = *(void**)value;  // 24-byte copy
  *(char**)((char*)self + 4) = end + 0x18;
}
