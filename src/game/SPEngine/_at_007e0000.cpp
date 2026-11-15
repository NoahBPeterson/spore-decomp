// src/game/SPEngine/_at_007e0000.cpp -- migrated from slice(s) s007efd10, s007eed10, s007e06b0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_007e0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cError.h"
#include <new>
#include <math.h>
#include <xmmintrin.h>

// unnamed retail callees and globals (address in the comment)
extern const float gZero3[3];        // 0x01638f7c
extern const float gOne;             // 0x01485720

// ---- items of slice s007e06b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl EFree(void* p);                       // 0x00f47380 EASTL_allocator_deallocate
struct Matrix33 { float m[9]; void Assign(const Matrix33& o); };
struct VtblObj;
struct cSPTransform_s007e_06b0 {
    uint16_t mFlags;        // +0x00
    uint16_t mModCount;     // +0x02
    float    mTranslation[3]; // +0x04
    float    mScale;        // +0x10
    Matrix33 mRotation;     // +0x14
    cSPTransform_s007e_06b0& operator=(const cSPTransform_s007e_06b0& o);   // 0x00537dc0
};
struct SplitEffectBase1 {
    virtual void w0();
    virtual void w1();
    virtual void w2();
};
struct SplitEffectBase0 {
    virtual void e0();
    virtual void e1();
};
struct cSplitControllerEffect : SplitEffectBase0, SplitEffectBase1 {
    int   field08;              // +0x08
    void* mpOwner;              // +0x0c
    int   field10;              // +0x10
    char  field14;              // +0x14
    void* mpState;              // +0x18
    void* vecBegin;             // +0x1c
    void* vecEnd;               // +0x20
    void* vecCap;               // +0x24
    int   field28;              // +0x28
    int   field2c;              // +0x2c
    cSPTransform_s007e_06b0 mTransform;    // +0x30
    float f68, f6c, f70;        // +0x68

    cSplitControllerEffect(void* owner);                         // 007e1010
    ~cSplitControllerEffect();                                   // 007e0f70
    void UpdateInstances(int unused);                            // 007e0f00
    void AddInstance(int a, void* b);                            // 007e10c0
    void CopyFrom(void* src);                                    // 007e1450
    void Start(int unused);                                      // 007e15b0
    void OnMessage(void* a, VtblObj* b, void* c);                // 007e1540
    char HandleMessage(int type, VtblObj* b);                    // 007e1580
};
extern const float gZero3[3];        // 0x01638f7c
extern const float gOne;             // 0x01485720
extern const Matrix33 gIdentity33;   // 0x01639100
void FUN_00537f40(void);   // 0x00537f40  cTransform::PreTransformBy (__thiscall: ecx=this)
void FUN_0079a0d0(void);   // 0x0079a0d0  cLabelOps::Propagate (__thiscall: ecx=this)
typedef void (__thiscall* PreTransformFn)(void* self, void* p);
typedef void (__thiscall* PropagateFn)(void* self, void* p);
struct SplitInstanceOps { int mPad; };          // +0x00..+0x03 of the +4 subobject
struct SplitInstanceRecord {
    int field00;                                // +0x00
    SplitInstanceOps ops;                       // +0x04
    cSPTransform_s007e_06b0 transform;                     // +0x08
};
void* FUN_0099efa0(void* begin, void* end, void* dst);   // 0x0099efa0
void* RBTreeIncrement(void* it);                          // 0x00921480
struct MyVector8 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void resize(unsigned n);
    void DoInsertValue(void* pos, void* v);   // 0x007e1340
};
void* AddSplitInstance(void* out, int key, cSPTransform_s007e_06b0* t, int flag);  // 0x007d7640
struct VtblObj {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void v6(int a, int b);   // +0x18
};
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0
// ---- items of slice s007e06b0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const Matrix33 gIdentity33;   // 0x01639100

// ---- items of slice s007eed10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_v2c, g_v30, g_v38, g_v3c, g_v40;
extern const float g_mat3[9];
extern void* UninitCopy24(void* first, void* last, void* dst);   // 0x00a88250
extern void  CopyBack24(void* first, void* last, void* dst);     // 0x00cc8b50
extern float g_v15407b4;         // 0x015407b4  FLT_MAX
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
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
struct HeapNode {
  double d;
  uint32_t x, y;
};
inline bool operator<(const HeapNode& a, const HeapNode& b) { return a.d < b.d; }
struct EmptyCmp { char x; };
struct PQ {
  HeapNode* mpBegin;     // +0x00
  HeapNode* mpEnd;       // +0x04
  HeapNode* mpCapacity;  // +0x08
  char pad[8];
  EmptyCmp mCmp;         // +0x14

  void DoInsertValue(void* position, const HeapNode& v);
  void Push(const HeapNode& v);
};
struct Matrix3 {
  float v[9];
  void Assign(const void* p);
  Matrix3(const void* p) { Assign(p); }
  Matrix3() {}
};
struct VBaseA { virtual void va(); virtual ~VBaseA() throw() {} };
struct VBaseB { virtual void vb(); virtual ~VBaseB() throw() {} int mB; VBaseB() : mB(0) {} };
struct VBaseC { virtual void vc(); virtual ~VBaseC() throw() {} };
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
extern void* operator new(unsigned size, const char* name, int, int, const char*, int);  // 0x00f473a0
struct SPTLite {
  void PreTransformBy(int a);                                    // 0x00537f40
  void AssignFrom(const void* src);                              // 0x00537dc0
};
struct Vec24 {
  char* begin;   // +0
  char* end;     // +4
  char* cap;     // +8
  void insert(char* pos, const char* value);
};
// ---- items of slice s007eed10 end

// ---- items of slice s007efd10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Edge;
struct HeapNode_s007e_fd10 {
  double d;      // event depth (heap key, max-heap)
  Edge* edge;    // edge whose far corner is at depth d
  uint32_t y;    // unused
};
void AdjustHeap(HeapNode_s007e_fd10* first, int top, int length, int hole, HeapNode_s007e_fd10 value, EmptyCmp cmp);
void MakeHeap(HeapNode_s007e_fd10* first, HeapNode_s007e_fd10* last, EmptyCmp cmp);
inline void PopHeap(HeapNode_s007e_fd10* first, HeapNode_s007e_fd10* last, EmptyCmp cmp) {
  const HeapNode_s007e_fd10 tempBottom(*(last - 1));
  *(last - 1) = *first;
  AdjustHeap(first, 0, (int)((last - 1) - first), 0, tempBottom, cmp);
}
void SpVectorDealloc(void* p);  // operator delete[] (sp_vector_allocator)
struct PQ_s007e_fd10 {
  HeapNode_s007e_fd10* mpBegin;     // +0x00
  HeapNode_s007e_fd10* mpEnd;       // +0x04
  HeapNode_s007e_fd10* mpCapacity;  // +0x08
  uint32_t mAlloc[2];    // +0x0c
  EmptyCmp mCmp;         // +0x14

  PQ_s007e_fd10() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mCmp.x = 0;
    MakeHeap(mpBegin, mpEnd, mCmp);
  }
  ~PQ_s007e_fd10() {
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) SpVectorDealloc(mpBegin);
  }
  const HeapNode_s007e_fd10& top() const { return *mpBegin; }
  void pop() {
    PopHeap(mpBegin, mpEnd, mCmp);
    --mpEnd;
  }
  void Push(const HeapNode_s007e_fd10& v);   // 0x007efc90
};
struct SliceVertex {
  float x, y, z;
  float u, v, w;
};
inline SliceVertex Scaled(const SliceVertex& a, float s) {
  SliceVertex r;
  r.x = a.x * s; r.y = a.y * s; r.z = a.z * s;
  r.u = a.u * s; r.v = a.v * s; r.w = a.w * s;
  return r;
}
inline SliceVertex Diff(const SliceVertex& a, const SliceVertex& b) {
  SliceVertex r;
  r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z;
  r.u = a.u - b.u; r.v = a.v - b.v; r.w = a.w - b.w;
  return r;
}
inline SliceVertex AddScaled(const SliceVertex& a, const SliceVertex& d, float t) {
  SliceVertex r;
  r.x = a.x + d.x * t; r.y = a.y + d.y * t; r.z = a.z + d.z * t;
  r.u = a.u + d.u * t; r.v = a.v + d.v * t; r.w = a.w + d.w * t;
  return r;
}
struct SliceVertexVector {   // eastl::vector<SliceVertex>
  SliceVertex* mpBegin;
  SliceVertex* mpEnd;
  SliceVertex* mpCapacity;
  void DoInsertValue(SliceVertex* position, const SliceVertex& value);   // 0x007efa20
  void push_back(const SliceVertex& value) {
    if (mpEnd < mpCapacity)
      new (mpEnd++) SliceVertex(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
struct UIntVector {          // eastl::vector<unsigned int, sp_vector_allocator>
  unsigned* mpBegin;
  unsigned* mpEnd;
  unsigned* mpCapacity;
  void DoInsertValue(unsigned* position, const unsigned& value);   // 0x004558a0
  void push_back(const unsigned& value) {
    if (mpEnd < mpCapacity)
      new (mpEnd++) unsigned(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
struct Edge {
  bool done;           // +0x00 far corner already retired
  int from;            // +0x04 corner index
  int to;              // +0x08 corner index
  SliceVertex cur;     // +0x0c intersection with the current slice plane
  SliceVertex delta;   // +0x24 per-slice step
  Edge* prev;          // +0x3c
  Edge* next;          // +0x40
};
struct SliceCamera {
  char pad0[8];
  float px, py, pz;      // +0x08 reference point
  float mSliceSpacing;   // +0x14
};
struct VolState_s007e_fd10 {
  char pad0[0x10];
  SliceCamera* mpCamera;       // +0x10
  char pad14[0x6c - 0x14];
  SliceVertex mCorners[8];     // +0x6c

  void BuildSlices(float dx, float dy, float dz, SliceVertexVector& verts, UIntVector& counts);
};
__forceinline void InitEdge(VolState_s007e_fd10* self, Edge* e, int from, int to, float dFrom, float dTo, float sliceD) {
  e->done = false;
  e->from = from;
  e->to = to;
  float dd = dTo - dFrom;
  if (dd != 0.0f) {
    float inv = 1.0f / dd;
    e->delta = Scaled(Diff(self->mCorners[to], self->mCorners[from]), inv);
    e->cur = AddScaled(self->mCorners[from], e->delta, sliceD - dFrom);
    float s = self->mpCamera->mSliceSpacing;
    e->delta.x *= s; e->delta.y *= s; e->delta.z *= s;
    e->delta.u *= s; e->delta.v *= s; e->delta.w *= s;
  }
}
// ---- items of slice s007efd10 end

// @ 0x007e0f00
void cSplitControllerEffect::UpdateInstances(int unused)
{
    (void)unused;
    if (field14 && mpState) {
        int* end = (int*)vecEnd;
        for (int* it = (int*)vecBegin; it != end; it += 2) {
            int i = it[0];
            int j = it[1];
            int* base = *(int**)((char*)mpState + 0x40);
            char* elem = (char*)base + i * 0x1c;
            *(int*)(*(int*)(elem + 4) + j * 0x78) = *(int*)elem;
            --*(int*)(elem + 0x18);
            *(int*)elem = j;
        }
        field14 = 0;
    }
}

// @ 0x007e0f70
cSplitControllerEffect::~cSplitControllerEffect()
{
    if (vecBegin && *(int*)((char*)vecBegin - 4))
        EFree(vecBegin);
    if (mpState) {
        int n = *(int*)((char*)mpState + 4) - 1;
        *(int*)((char*)mpState + 4) = n;
        if (n == 0) {
            *(int*)((char*)mpState + 4) = 1;
            ((void(__thiscall*)(void*, int))(*(void***)mpState)[0])(mpState, 1);
        }
    }
}

// @ 0x007e1010
cSplitControllerEffect::cSplitControllerEffect(void* owner)
{
    field08 = 0;
    mpOwner = owner;
    field10 = 0;
    field14 = 0;
    mpState = 0;
    vecBegin = 0;
    vecEnd = 0;
    vecCap = 0;
    mTransform.mModCount = 0;
    mTransform.mFlags = 0;
    mTransform.mTranslation[0] = gZero3[0];
    mTransform.mTranslation[1] = gZero3[1];
    mTransform.mTranslation[2] = gZero3[2];
    mTransform.mScale = gOne;
    mTransform.mRotation = gIdentity33;
}

// @ 0x007e10c0
void cSplitControllerEffect::AddInstance(int a, void* b)
{
    cSPTransform_s007e_06b0 local;
    const uint8_t* src = (const uint8_t*)b;
    local.mFlags = *(const uint16_t*)src;
    local.mModCount = *(const uint16_t*)(src + 2);
    local.mTranslation[0] = *(const float*)(src + 4);
    local.mTranslation[1] = *(const float*)(src + 8);
    local.mTranslation[2] = *(const float*)(src + 0xc);
    local.mScale = *(const float*)(src + 0x10);
    local.mRotation.Assign(*(const Matrix33*)(src + 0x14));

    ((PreTransformFn)FUN_00537f40)(&local, (void*)a);
    mTransform = local;

    float s = *(const float*)(src + 0x10);
    float nx = -f68 * s;
    float ny = -f6c * s;
    float nz = -f70 * s;
    mTransform.mTranslation[0] +=
        mTransform.mRotation.m[0] * nx + mTransform.mRotation.m[3] * ny + mTransform.mRotation.m[6] * nz;
    mTransform.mTranslation[1] +=
        mTransform.mRotation.m[1] * nx + mTransform.mRotation.m[4] * ny + mTransform.mRotation.m[7] * nz;
    mTransform.mTranslation[2] +=
        mTransform.mRotation.m[2] * nx + mTransform.mRotation.m[5] * ny + mTransform.mRotation.m[8] * nz;
    mTransform.mFlags |= 4;
    ++mTransform.mModCount;

    if (field14) {
        int* end = (int*)vecEnd;
        for (int* it = (int*)vecBegin; it != end; it += 2) {
            int i = it[0];
            int j = it[1];
            int* base = *(int**)((char*)mpState + 0x40);
            char* elem = (char*)base + i * 0x1c;
            SplitInstanceRecord* inst = (SplitInstanceRecord*)(*(int*)(elem + 4) + j * 0x78);
            inst->transform = mTransform;
            ((PropagateFn)FUN_0079a0d0)(&inst->ops, (char*)mpState + 8);
        }
    }
}

// @ 0x007e12b0
void MyVector8::resize(unsigned n)
{
    if (n > (unsigned)(((int)mpCapacity - (int)mpBegin) >> 3)) {
        char* p = n ? (char*)operator new(n * 8, "App", 0, 0,
                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                    : 0;
        FUN_0099efa0(mpBegin, mpEnd, p);
        if (mpBegin && *(int*)((char*)mpBegin - 4))
            EFree(mpBegin);
        int count = ((int)mpEnd - (int)mpBegin) >> 3;
        char* cap = (char*)p + n * 8;
        char* end = (char*)p + count * 8;
        mpBegin = p;
        mpEnd = end;
        mpCapacity = cap;
    }
}

// @ 0x007e1450
void cSplitControllerEffect::CopyFrom(void* src)
{
    if (!src)
        return;
    char was = field14;
    if (was)
        ((void(__thiscall*)(void*, int))(*(void***)this)[3])(this, 1);
    f68 = *(float*)((char*)src + 0x28);
    f6c = *(float*)((char*)src + 0x2c);
    f70 = *(float*)((char*)src + 0x30);
    void* np = *(void**)((char*)src + 0x34);
    void* op = mpState;
    if (np != op) {
        if (np)
            ++*(int*)((char*)np + 4);
        mpState = np;
        if (op) {
            int n = *(int*)((char*)op + 4) - 1;
            *(int*)((char*)op + 4) = n;
            if (n == 0) {
                *(int*)((char*)op + 4) = 1;
                ((void(__thiscall*)(void*, int))(*(void***)op)[0])(op, 1);
            }
        }
    }
    MyVector8* v = (MyVector8*)&vecBegin;
    v->resize(*(unsigned*)((char*)src + 0x20));
    void* stop = (char*)src + 0x10;
    for (void* it = *(void**)((char*)src + 0x14); it != stop; it = RBTreeIncrement(it)) {
        int val = *(int*)((char*)it + 0x10);
        int zero = 0;
        char* end = (char*)v->mpEnd;
        if (end < (char*)v->mpCapacity) {
            v->mpEnd = end + 8;
            if (end) { *(int*)end = val; *((int*)end + 1) = zero; }
        } else {
            v->DoInsertValue(end, &val);
        }
    }
    if (was)
        ((void(__thiscall*)(void*, int))(*(void***)this)[2])(this, 1);
}

// @ 0x007e1540
void cSplitControllerEffect::OnMessage(void* a, VtblObj* b, void* c)
{
    (void)a;
    field10 = ((int(__thiscall*)(VtblObj*))(*(void***)b)[40])(b);
    void* p = *(void**)((char*)c + 0xc8);
    if (p) {
        void* r = (void*)((int(__thiscall*)(void*, int))(*(void***)p)[3])(p, 0x32f9668);
        CopyFrom(r);
    }
}

// @ 0x007e1580
char cSplitControllerEffect::HandleMessage(int type, VtblObj* b)
{
    if (type == 5) {
        void* r = (void*)((int(__thiscall*)(VtblObj*, int))(*(void***)b)[3])(b, 0x32f9668);
        CopyFrom(r);
        return 1;
    }
    return 0;
}

// @ 0x007e15b0
void cSplitControllerEffect::Start(int unused)
{
    (void)unused;
    if (!field14 && mpState) {
        int* end = (int*)vecEnd;
        int* it = (int*)vecBegin;
        if (it != end) {
            do {
                int pair[2];
                AddSplitInstance(pair, *it, &mTransform, 0);
                it[0] = pair[0];
                it[1] = pair[1];
                it += 2;
            } while (it != end);
        }
        field14 = 1;
    }
}

// @ 0x007ef2a0
void CTrack::Slot0(void* a, void* b, int)
{
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

// @ 0x007ef350
void CTrack::Slot1()
{
  if (mIndex >= 0)
    ((void(__thiscall*)(void*, int))VSLOT(mpIface, 0x1c))(mpIface, mIndex);
}

// @ 0x007ef370
void CTrack::Slot2(int)
{
  if (mpIface && !mActive) {
    mActive = true;
    if (mIndex >= 0)
      ((void(__thiscall*)(void*, int, int))VSLOT(mpIface, 0x24))(mpIface, mIndex, 1);
  }
}

// @ 0x007ef3a0
void CTrack::Slot3(int)
{
  if (mActive) {
    mActive = false;
    if (mIndex >= 0)
      ((void(__thiscall*)(void*, int, int))VSLOT(mpIface, 0x24))(mpIface, mIndex, 0);
  }
}

// @ 0x007ef3d0
void SiftUp(HeapNode* first, int top, int hole, HeapNode value, EmptyCmp)
{
  int parent = (hole - 1) >> 1;
  while (hole > top && first[parent] < value) {
    first[hole] = first[parent];
    hole = parent;
    parent = (hole - 1) >> 1;
  }
  first[hole] = value;
}

// @ 0x007ef450
bool CTrack::SetKey(int id, KeyFrame* k, int)
{
  if (id != 0x101) return false;
  mMin = k->k0;
  mMax = k->k1;
  return true;
}

// @ 0x007ef480
void CTrack::Eval(int, float t, int)
{
  mValue = (mMax - mMin) * t + mMin;
}

// @ 0x007ef4a0
void AdjustHeap(HeapNode* first, int top, int length, int hole, HeapNode value, EmptyCmp cmp)
{
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

// @ 0x007ef560
VolState::~VolState() throw()
{
}

// @ 0x007ef5d0
void MakeHeap(HeapNode* first, HeapNode* last, EmptyCmp cmp)
{
  int len = (int)(last - first);
  if (len < 2) return;
  int parent = ((len - 2) >> 1) + 1;
  do {
    --parent;
    HeapNode value = first[parent];
    AdjustHeap(first, parent, len, parent, value, cmp);
  } while (parent != 0);
}

// @ 0x007ef630
VolState::VolState(int a)
{
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

// @ 0x007ef730
void VolState::UpdateFromFrame(int a, void* frame)
{
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

// @ 0x007efa20
void Vec24::insert(char* pos, const char* value)
{
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

// @ 0x007efc90
void PQ::Push(const HeapNode& v)
{
  if (mpEnd < mpCapacity) {
    HeapNode* p = mpEnd++;
    new (p) HeapNode(v);
  } else {
    DoInsertValue(mpEnd, v);
  }
  SiftUp(mpBegin, 0, (int)(mpEnd - mpBegin) - 1, *(mpEnd - 1), mCmp);
}

// @ 0x007efd10
void VolState_s007e_fd10::BuildSlices(float dx, float dy, float dz, SliceVertexVector& verts, UIntVector& counts)
{
  // The three neighbours of each box corner.
  int neighbours[8][3] = {
    { 1, 2, 4 }, { 0, 5, 3 }, { 0, 3, 6 }, { 1, 7, 2 },
    { 0, 6, 5 }, { 1, 4, 7 }, { 2, 7, 4 }, { 3, 5, 6 },
  };
  // nextCorner[v][p]: walking around corner v, the neighbour that follows p.
  int nextCorner[8][8] = {
    { -1,  2,  4, -1,  1, -1, -1, -1 },
    {  5, -1, -1,  0, -1,  3, -1, -1 },
    {  3, -1, -1,  6, -1, -1,  0, -1 },
    { -1,  7,  1, -1, -1, -1, -1,  2 },
    {  6, -1, -1, -1, -1,  0,  5, -1 },
    { -1,  4, -1, -1,  7, -1, -1,  1 },
    { -1, -1,  7, -1,  2, -1, -1,  4 },
    { -1, -1, -1,  5, -1,  6,  3, -1 },
  };

  float depth[8];
  for (int i = 0; i < 8; ++i) {
    const SliceVertex& c = mCorners[i];
    // Original order: ((x*dx) + (z*dz)) + (y*dy).  /fp:fast would otherwise
    // reassociate to (x*dx + y*dy) + z*dz, a one-ULP difference.
    __m128 xz = _mm_add_ss(_mm_mul_ss(_mm_set_ss(c.x), _mm_set_ss(dx)),
                           _mm_mul_ss(_mm_set_ss(c.z), _mm_set_ss(dz)));
    depth[i] = _mm_cvtss_f32(_mm_add_ss(xz, _mm_mul_ss(_mm_set_ss(c.y), _mm_set_ss(dy))));
  }

  float maxD = depth[0];
  float minD = depth[0];
  int maxIdx = 0;
  for (int i = 1; i < 8; ++i) {
    float d = depth[i];
    if (minD > d)
      minD = d;
    else if (d > maxD) {
      maxD = d;
      maxIdx = i;
    }
  }

  SliceCamera* cam = mpCamera;
  float spacing = cam->mSliceSpacing;
  // Original order: ((px*dx) + (pz*dz)) + (py*dy).
  __m128 b_xz = _mm_add_ss(_mm_mul_ss(_mm_set_ss(cam->px), _mm_set_ss(dx)),
                           _mm_mul_ss(_mm_set_ss(cam->pz), _mm_set_ss(dz)));
  float base = _mm_cvtss_f32(_mm_add_ss(b_xz, _mm_mul_ss(_mm_set_ss(cam->py), _mm_set_ss(dy))));
  // The original divides in single precision (SSE divss) before widening the
  // quotient to double for floor(); /fp:fast would otherwise contract the whole
  // expression into an extended-precision x87 fsub/fdiv chain.
  __m128 ratio = _mm_div_ss(_mm_sub_ss(_mm_set_ss(maxD), _mm_set_ss(base)), _mm_set_ss(spacing));
  float n = (float)floor((double)_mm_cvtss_f32(ratio));
  float sliceD = spacing * n + base;

  Edge edges[12];
  Edge* pFree = edges;
  Edge* pFirst = edges;
  PQ_s007e_fd10 pq;

  // Three edges leave the farthest corner.
  float topD = depth[maxIdx];
  for (int i = 0; i < 3; ++i) {
    int to = neighbours[maxIdx][i];
    InitEdge(this, pFree, maxIdx, to, topD, depth[to], sliceD);
    pFree->prev = &edges[(i + 2) % 3];
    pFree->next = &edges[(i + 1) % 3];
    HeapNode_s007e_fd10 ev;
    ev.d = depth[to];
    ev.edge = pFree;
    pq.Push(ev);
    ++pFree;
  }

  while (sliceD > minD) {
    // Retire every corner above the current plane.
    while (pq.top().d >= sliceD) {
      if (pFree - edges >= 12)
        break;
      Edge* e = pq.top().edge;
      int v = e->to;
      if (e->done) {
        pq.pop();
        continue;
      }
      if (v == e->prev->to || v == e->next->to) {
        // Two adjacent edges meet at v: replace them by one edge.
        Edge* a;
        Edge* b;
        if (v == e->prev->to) {
          a = e->prev;
          b = e;
        } else {
          a = e;
          b = e->next;
        }
        float dv = depth[v];
        b->done = true;
        a->done = true;
        int to = nextCorner[v][a->from];
        float dTo = depth[to];
        InitEdge(this, pFree, v, to, dv, dTo, sliceD);
        pFree->prev = a->prev;
        a->prev->next = pFree;
        pFree->next = b->next;
        b->next->prev = pFree;
        HeapNode_s007e_fd10 ev = pq.top();
        pq.pop();
        ev.d = dTo;
        ev.edge = pFree;
        pFirst = pFree;
        pq.Push(ev);
        ++pFree;
      } else {
        // One edge reaches v: split it into two edges.
        float dv = depth[v];
        e->done = true;
        int to1 = nextCorner[v][e->from];
        float d1 = depth[to1];
        InitEdge(this, pFree, v, to1, dv, d1, sliceD);
        Edge* e1 = pFree;
        e1->prev = e->prev;
        e->prev->next = e1;
        e1->next = e1 + 1;
        HeapNode_s007e_fd10 ev = pq.top();
        pq.pop();
        ev.d = d1;
        ev.edge = e1;
        pq.Push(ev);
        ++pFree;
        if (pFree - edges >= 12)
          break;

        int to2 = nextCorner[v][to1];
        float d2 = depth[to2];
        InitEdge(this, pFree, v, to2, dv, d2, sliceD);
        pFree->prev = pFree - 1;
        pFree->next = e->next;
        e->next->prev = pFree;
        pFirst = pFree;
        HeapNode_s007e_fd10 ev2;
        ev2.d = d2;
        ev2.edge = pFree;
        pq.Push(ev2);
        ++pFree;
      }
    }

    // Drop events of retired edges.
    while (pq.top().edge->done)
      pq.pop();

    if (sliceD > pq.top().d) {
      // Emit the polygon and advance every edge to the next plane.
      unsigned count = 0;
      Edge* p = pFirst;
      do {
        verts.push_back(p->cur);
        ++count;
        p->cur.x -= p->delta.x;
        p->cur.y -= p->delta.y;
        p->cur.z -= p->delta.z;
        p->cur.u -= p->delta.u;
        p->cur.v -= p->delta.v;
        p->cur.w -= p->delta.w;
        p = p->next;
      } while (p != pFirst);
      counts.push_back(count);
    }

    sliceD -= mpCamera->mSliceSpacing;
  }
}
