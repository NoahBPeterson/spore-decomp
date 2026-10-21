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

  void Slot0(void* a, void* b, int);
  void Slot1();
  void Slot2(int);
  void Slot3(int);
  bool SetKey(int id, KeyFrame* k, int);
  void Eval(int, float t, int);
};

// @ 0x007EF2A0
void CTrack::Slot0(void* a, void* b, int) {
  mpIface = ((void*(__thiscall*)(void*))VSLOT(a, 0x20))(a);
  mOther = ((int(__thiscall*)(void*))VSLOT(b, 0xa0))(b);
  if (mpIface) {
    int* md = (int*)mDataOffset;
    struct Slot0Arg {
      int f0;
      int f4;
      unsigned char b8, b9, ba, bb;
      unsigned short wc;
      unsigned short padE;
      float f10;
      int f14;
      int f18;
    };
    Slot0Arg t;
    t.f0 = md[0x28 / 4];
    t.f4 = md[0x2c / 4];
    t.b8 = 7;
    t.b9 = 0xf;
    t.ba = 0;
    t.bb = 0;
    t.wc = 0;
    t.f10 = 0.0f;
    t.f14 = -1;
    t.f18 = -1;
    ((void(__thiscall*)(void*, void*, void*, void*))VSLOT(mpIface, 0x18))
        (mpIface, (char*)this + 0xc, &t, (char*)this + 0x1c);
    ((void(__thiscall*)(void*, int, void*))VSLOT(mpIface, 0x10))(mpIface, 7, (char*)this + 0x20);
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

struct VBaseA { virtual void va(); virtual ~VBaseA() throw() {} };
struct VBaseB { virtual void vb(); virtual ~VBaseB() throw() {} int mB; VBaseB() : mB(0) {} };
struct VBaseC { virtual void vc(); virtual ~VBaseC() throw() {} };

extern float g_v2c, g_v30, g_v38, g_v3c, g_v40;
extern const float g_mat3[9];


struct Buf {
  void* begin;  // +0
  void* end;    // +4
  void* cap;    // +8
  ~Buf() { if (begin != 0 && ((int*)begin)[-1] != 0) operator delete[](begin); }
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
  Buf vA;              // +0x12c
  int g138, g13c;      // +0x138
  Buf vB;              // +0x140
  VolState(int a);
  ~VolState() throw();
  void UpdateFromFrame(int a, void* frame);
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
  vA.begin = 0;
  vA.end = 0;
  vA.cap = 0;
  vB.begin = 0;
  vB.end = 0;
  vB.cap = 0;
}

// @ 0x007EF560
VolState::~VolState() throw() {
}

// ---------------------------------------------------------------------------
// cVolumeEffectCommand (vtable 0x01414744): cBlockCommandT<cEffectsParser>
// base + cVolumeState + an EASTL string.  0x007EF220 is its scalar deleting
// destructor.
// ---------------------------------------------------------------------------


struct EString {
  char* mpBegin;  // +0
  char* mpEnd;    // +4
  char* mpCap;    // +8
  ~EString() {
    if (mpCap - mpBegin > 1 && mpBegin != 0) operator delete[](mpBegin);
  }
};

struct cVolumeDescLite {
  virtual ~cVolumeDescLite() {}
  int mRef;
};
struct cBlockCommandBase {
  virtual ~cBlockCommandBase() throw();   // 0x0083cd90
  char pad[0x34];
};
struct cVolumeStateLite {
  char pad[8];
  cVolumeDescLite mDesc;   // +0x40 in the derived object
  void InitDesc(const void* src);   // 0x007ee7f0
  char pad2[0x130 - 0x48];
};
struct cVolumeEffectCommand : cBlockCommandBase {
  cVolumeStateLite mVolumeState;  // +0x38
  EString mDescName;              // +0x130
  virtual void Execute(void* args);
};
// @ 0x007EF220  scalar deleting destructor
void ForceVolumeEffect(cVolumeEffectCommand* p) {
  delete p;
}
cVolumeEffectCommand* ForceVolumeEffectNew() { return new cVolumeEffectCommand; }

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
// Remaining slice functions.
// ===========================================================================
extern void  cErrorCtor(void* buf, const char* msg);   // 0x0052df30
extern void  CxxThrow(void* obj, void* info);          // 0x011e0912
extern char  TypeInfo_cError;                          // 0x014f9174
struct ArgErrBuf { void* m[4]; };
#define ARG_THROW(msg) do { ArgErrBuf _eb; cErrorCtor(&_eb, (msg)); CxxThrow(&_eb, (void*)&TypeInfo_cError); } while (0)
extern void* operator new(unsigned size, const char* name, int, int, const char*, int);  // 0x00f473a0
extern void* UninitCopy24(void* first, void* last, void* dst);   // 0x00a88250
extern void  CopyBack24(void* first, void* last, void* dst);     // 0x00cc8b50

// Callees that live in other object files.  They are declared under their real
// qualified names so both the matcher and the equivalence resolver can tie each
// call site back to the original function.
namespace EA { namespace ArgScript {
  int ParseEnum(void* s, const char* name);                      // 0x00840bb0
  class cArguments { public:
    void* MainArguments(int* out, int a, int b);                 // 0x00838020
  };
  class cCommandBase { public:
    cCommandBase();                                              // 0x0083c800
  };
}}
namespace EA { namespace Swarm {
  class cEffectsParser { public:
    void* GetInheritedDescription(void* args, int n, int size);  // 0x00a6f090
  };
}}
namespace SP {
  struct cVolumeDescription {
    cVolumeDescription();                                        // 0x007ee540
    char pad[0x24];
  };
}
struct EStringLite {
  void assign(const char* first, const char* last);              // 0x00454cb0
};
struct AppPropsFields {
  AppPropsFields();                                              // 0x0083cdd0
};
struct SPTLite {
  void PreTransformBy(int a);                                    // 0x00537f40
  void AssignFrom(const void* src);                              // 0x00537dc0
};
extern char VtblVolumeEffect;    // 0x01414744
extern char VtblGroupVolume;     // 0x0141472c
extern char Data1667bac;         // 0x01667bac
extern const char* g_sVolume;    // 0x0154038c  pointer to "volume"
extern float g_v15407b4;         // 0x015407b4  FLT_MAX

struct cVolumeSetCommand {
  virtual void Execute(EA::ArgScript::cArguments* args);
};

// @ 0x007EED10  cVolumeSetCommand::Execute
void cVolumeSetCommand::Execute(EA::ArgScript::cArguments* args) {
  int count;
  char** a = (char**)args->MainArguments(&count, 2, 8);
  int sel = EA::ArgScript::ParseEnum(a[0], "corner");
  void* mgr = *(void**)((char*)this + 4);
  char* data = *(char**)((char*)this + 0xc);
  switch (sel) {
  case 0: {
    if (count < 5) ARG_THROW("Wrong number of arguments.");
    unsigned n = ((unsigned(__thiscall*)(void*, void*))VSLOT(mgr, 0xa0))(mgr, a[1]);
    unsigned m = n;
    if ((int)n > 8) {
      m = 0;
      if (n & 1) m = 1;
      if (((int)n / 10) & 1) m |= 2;
      if ((int)n >= 100) m |= 4;
    }
    float f4 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[4]);
    float f3 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[3]);
    float f2 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[2]);
    unsigned off = m * 0x18;
    *(float*)(data + off + 0x38) = f2;
    *(float*)(data + off + 0x3c) = f3;
    *(float*)(data + off + 0x40) = f4;
    if (count >= 8) {
      float g7 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[7]);
      float g6 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[6]);
      float g5 = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[5]);
      *(float*)(data + off + 0x44) = g5;
      *(float*)(data + off + 0x48) = g7;
      *(float*)(data + off + 0x4c) = g6;
    }
    break;
  }
  case 1: {
    if (count < 2) ARG_THROW("Wrong number of arguments.");
    float v = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[1]);
    *(float*)(data + 0x40) = v;
    *(float*)(data + 0x58) = v;
    *(float*)(data + 0x70) = v;
    *(float*)(data + 0x88) = v;
    if (count >= 3) {
      float w = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[2]);
      *(float*)(data + 0x4c) = w;
      *(float*)(data + 0x64) = w;
      *(float*)(data + 0x7c) = w;
      *(float*)(data + 0x94) = w;
    }
    break;
  }
  case 2: {
    if (count < 2) ARG_THROW("Wrong number of arguments.");
    float v = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[1]);
    *(float*)(data + 0xa0) = v;
    *(float*)(data + 0xb8) = v;
    *(float*)(data + 0xd0) = v;
    *(float*)(data + 0xe8) = v;
    if (count >= 3) {
      float w = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[2]);
      *(float*)(data + 0xac) = w;
      *(float*)(data + 0xc4) = w;
      *(float*)(data + 0xdc) = w;
      *(float*)(data + 0xf4) = w;
    }
    break;
  }
  case 3: {
    if (count < 2) ARG_THROW("Wrong number of arguments.");
    float h = ((float(__thiscall*)(void*, void*))VSLOT(mgr, 0x98))(mgr, a[1]) * 0.5f;
    *(float*)(data + 0x38) = -h;
    *(float*)(data + 0x3c) = -h;
    *(float*)(data + 0x50) = h;
    *(float*)(data + 0x54) = -h;
    *(float*)(data + 0x68) = -h;
    *(float*)(data + 0x6c) = h;
    *(float*)(data + 0x80) = h;
    *(float*)(data + 0x84) = h;
    *(float*)(data + 0x98) = -h;
    *(float*)(data + 0x9c) = -h;
    *(float*)(data + 0xb0) = h;
    *(float*)(data + 0xb4) = -h;
    *(float*)(data + 0xc8) = -h;
    *(float*)(data + 0xcc) = h;
    *(float*)(data + 0xe0) = h;
    *(float*)(data + 0xe4) = h;
    break;
  }
  default:
    break;
  }
}

// @ 0x007EF080  cVolumeEffectCommand::Execute
void cVolumeEffectCommand::Execute(void* args) {
  int count = 0;
  char** a = (char**)((EA::ArgScript::cArguments*)args)->MainArguments(&count, 1, 3);
  const char* s = a[0];
  const char* e = s;
  while (*e != 0) ++e;
  ((EStringLite*)((char*)this + 0x130))->assign(s, e);
  SP::cVolumeDescription tmp;
  void* t = &tmp;
  mVolumeState.InitDesc(t);
  if (count > 1) {
    void* inh = ((EA::Swarm::cEffectsParser*)(*(void**)((char*)this + 0x30)))->GetInheritedDescription(a, count, 0x28);
    if (inh) mVolumeState.InitDesc(inh);
  }
  void* mgr = *(void**)((char*)this + 4);
  ((void(__thiscall*)(void*, void*))VSLOT(mgr, 0x8c))(mgr, this);
}

// @ 0x007EF120  CommandManager::RegisterVolumeCommands
void RegisterVolumeCommands(void* unused, void* mgr) {
  void* cmd = operator new(0x140, "ArgScript/VolumeEffect", 0, 0, 0, 0);
  if (cmd) {
    new (cmd) AppPropsFields();
    *(void**)cmd = &VtblVolumeEffect;
    *(int*)((char*)cmd + 0x38) = 0x2cf2626;
    new ((void*)((char*)cmd + 0x40)) SP::cVolumeDescription();
    *(void**)((char*)cmd + 0x130) = &Data1667bac;
    *(void**)((char*)cmd + 0x134) = &Data1667bac;
    *(void**)((char*)cmd + 0x138) = (void*)0x1667bad;
  }
  ((void(__thiscall*)(void*, const char*, void*))VSLOT(mgr, 0x14))(mgr, g_sVolume, cmd);
  void* grp = operator new(0x10, "ArgScript/GroupVolume", 0, 0, 0, 0);
  if (grp) {
    new (grp) EA::ArgScript::cCommandBase();
    *(void**)grp = &VtblGroupVolume;
  }
  ((void(__thiscall*)(void*, const char*, void*))VSLOT(mgr, 0x18))(mgr, g_sVolume, grp);
}

// @ 0x007EF730  VolState::UpdateFromFrame
void VolState::UpdateFromFrame(int a, void* frame) {
  char loc[0x3c];
  *(short*)(loc + 0x00) = *(short*)((char*)frame + 0);
  *(short*)(loc + 0x02) = *(short*)((char*)frame + 2);
  *(float*)(loc + 0x04) = *(float*)((char*)frame + 4);
  *(float*)(loc + 0x08) = *(float*)((char*)frame + 8);
  *(float*)(loc + 0x0c) = *(float*)((char*)frame + 0xc);
  *(float*)(loc + 0x10) = *(float*)((char*)frame + 0x10);
  ((Matrix3*)(loc + 0x14))->Assign((char*)frame + 0x14);
  ((SPTLite*)loc)->PreTransformBy(a);
  ((SPTLite*)((char*)this + 0x34))->AssignFrom(loc);

  float* s = (float*)(char*)this;
  float lo0 = g_v15407b4, lo1 = g_v15407b4, lo2 = g_v15407b4;
  float hi0 = -g_v15407b4, hi1 = -g_v15407b4, hi2 = -g_v15407b4;
  int base = *(int*)((char*)this + 0x10);
  for (int i = 0; i < 8; ++i) {
    float* src = (float*)(base + 0x30 + i * 0x18);
    float* dst = (float*)((char*)this + 0x6c + i * 0x18);
    dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
    dst[3] = src[3]; dst[4] = src[4]; dst[5] = src[5];
    if (*(short*)((char*)this + 0x34) & 2) {
      float x = dst[0], y = dst[1], z = dst[2];
      dst[0] = s[0x54 / 4] * y + s[0x60 / 4] * z + x * s[0x48 / 4];
      dst[1] = s[0x4c / 4] * x + s[0x58 / 4] * y + s[0x64 / 4] * z;
      dst[2] = s[0x50 / 4] * x + s[0x5c / 4] * y + s[0x68 / 4] * z;
    }
    float k = s[0x44 / 4];
    dst[0] = dst[0] * k + s[0x38 / 4];
    dst[1] = dst[1] * k + s[0x3c / 4];
    dst[2] = dst[2] * k + s[0x40 / 4];
    if (dst[0] < lo0) lo0 = dst[0];
    if (hi0 < dst[0]) hi0 = dst[0];
    if (dst[1] < lo1) lo1 = dst[1];
    if (hi1 < dst[1]) hi1 = dst[1];
    if (dst[2] < lo2) lo2 = dst[2];
    if (hi2 < dst[2]) hi2 = dst[2];
  }
  float box[6] = { lo0, lo1, lo2, hi0, hi1, hi2 };
  void* iface = *(void**)((char*)this + 0x14);
  ((void(__thiscall*)(void*, int, void*, int))VSLOT(iface, 0x20))(iface, *(int*)((char*)this + 0x1c), box, 0);
}

// @ 0x007EFA20  vector<T(24)>::insert
struct Vec24 {
  char* begin;   // +0
  char* end;     // +4
  char* cap;     // +8
  void insert(char* pos, const char* value);
};
void Vec24::insert(char* pos, const char* value) {
  char* e = end;
  if (e == cap) {
    int n = (int)((e - begin) / 0x18);
    n = (n == 0) ? 1 : n * 2;
    char* nb = (char*)operator new(n * 0x18, "App", 0, 0, 0, 0);
    char* p = (char*)UninitCopy24(begin, pos, nb);
    if (p) {
      *(void**)(p + 0) = *(void**)(value + 0);
      *(void**)(p + 4) = *(void**)(value + 4);
      *(void**)(p + 8) = *(void**)(value + 8);
      *(void**)(p + 0xc) = *(void**)(value + 0xc);
      *(void**)(p + 0x10) = *(void**)(value + 0x10);
      *(void**)(p + 0x14) = *(void**)(value + 0x14);
    }
    char* p2 = (char*)UninitCopy24(pos, e, p + 0x18);
    if (begin) operator delete[](begin);
    begin = nb;
    end = p2;
    cap = nb + n * 0x18;
  } else {
    if (pos <= value && value < e) value += 0x18;
    if (e) {
      *(void**)(e + 0) = *(void**)(e - 0x18 + 0);
      *(void**)(e + 4) = *(void**)(e - 0x18 + 4);
      *(void**)(e + 8) = *(void**)(e - 0x18 + 8);
      *(void**)(e + 0xc) = *(void**)(e - 0x18 + 0xc);
      *(void**)(e + 0x10) = *(void**)(e - 0x18 + 0x10);
      *(void**)(e + 0x14) = *(void**)(e - 0x18 + 0x14);
    }
    CopyBack24(pos, e - 0x18, e);
    *(void**)(pos + 0) = *(void**)(value + 0);
    *(void**)(pos + 4) = *(void**)(value + 4);
    *(void**)(pos + 8) = *(void**)(value + 8);
    *(void**)(pos + 0xc) = *(void**)(value + 0xc);
    *(void**)(pos + 0x10) = *(void**)(value + 0x10);
    *(void**)(pos + 0x14) = *(void**)(value + 0x14);
    end = e + 0x18;
  }
}
