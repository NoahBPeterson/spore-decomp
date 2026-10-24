// SP::cGameplayMarkerView marker helpers and SP::cCityDisplayStrategy's
// minimap-icon updater (retail 0x00ae3ed0..0x00ae4ec0).
//
// Retail passes the record in ECX for the Init/Release/Assign helpers, so those
// are modelled as members of the record type; the range/effect helpers take
// their arguments on the stack and are free functions.  The 8-byte intrusive
// list header at view+0x28 precedes the tMarker payload (node+8).
//
// Two record flavours:
//  * tMarker     (0x3c) -- payload of a list node; id at +0, position at +4.
//  * tMarkerNode (0x64) -- record reached through view+0x14 (end view+0x18,
//                          count view+0xac).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (VS2008 x86 SSE build; /fp:fast
// required for the scalar mulss/subss/checks the retail code uses for floats).

#include "types.h"
#include <intrin.h>
#pragma intrinsic(_InterlockedExchangeAdd)

namespace SP {

class cGameplayMarkerView;
struct tMarkerNode;

// List-node payload (node+8); id at +0, position at +4.
struct tMarker {
  int mId;               // +0x00
  float mPosition[3];    // +0x04
  void* mpUnk10;         // +0x10
  void* mpOrientation;   // +0x14
  void* mpArgument;      // +0x18
  int mUnk1c;            // +0x1c
  float mSurface[4];     // +0x20
  int mStyle;            // +0x30
  int mUnk34;            // +0x34
  int mUnk38;            // +0x38
};

// 4-byte intrusive image handle; Assign is a thiscall (dst in ECX, src on the
// stack), see 0x00576650.
struct ImageRef {
  void* mpPtr;                 // +0x00
  void Assign(void* src);      // 0x00576650
};

// A 3-float vector POD; assigning it whole yields integer moves (as the
// original does when copying a marker's position).
struct Vec3f {
  float v[3];
};

struct tMarkerNode {
  int mId;                     // +0x00
  Vec3f mPosition;             // +0x04
  int mUnk10;                  // +0x10
  void* mpUnk14;               // +0x14
  void* mpUnk18;               // +0x18
  int mUnk1c;                  // +0x1c
  int mUnk20;                  // +0x20
  bool mFlag24;                // +0x24
  bool mFlag25;                // +0x25
  bool mFlag26;                // +0x26
  int mUnk28;                  // +0x28
  int mUnk2c;                  // +0x2c
  bool mFlag30;                // +0x30
  bool mFlag31;                // +0x31
  int mUnk34;                  // +0x34
  void* mpModel;               // +0x38
  int mUnk3c;                  // +0x3c
  bool mFlag40;                // +0x40
  int mUnk44[4];               // +0x44..+0x50
  int mUnk54[3];               // +0x54..+0x5c
  ImageRef mEffect;            // +0x60

  tMarkerNode* InitMarkerNode();                  // 0x00ae4230 (returns this in eax)
  void ReleaseMarkerNode();                       // 0x00ae42a0
  tMarkerNode* AssignMarkerNode(tMarkerNode* s);  // 0x00ae4430
};

// The intrusive list sentinel at view+0x28.
struct tMarkerList {
  tMarkerList* mpNext;   // +0x00
  tMarkerList* mpPrev;   // +0x04

  tMarkerNode* AllocMarkerNode();  // 0x00ae43a0
};

class cGameplayMarkerView {
 public:
  unsigned char mPad0[0x14];       // +0x00
  tMarkerNode* mpArrayBegin;       // +0x14
  tMarkerNode* mpArrayEnd;         // +0x18
  unsigned char mPad1[0x0c];       // +0x1c
  tMarkerList mListHead;           // +0x28
  unsigned char mPad2[0x7c];       // +0x30
  int mCount;                      // +0xac

  bool HasMarker(unsigned int id);                              // 0x00ae4180
  tMarkerNode* FindMarkerNear(float* position, float radius);   // 0x00ae41b0
  void RemoveMarker();                                          // 0x00ae4610
  void UpdateMarkerTransform(unsigned int id, float* position,
                             float* quaternion);                // 0x00ae46f0
  tMarker* AddMarker(int a1, unsigned int id, float* position, int a4, void* a5,
                     int style, void* state, bool playSound);   // 0x00ae49d0
  tMarker* AddMarkerSimple(int a0, unsigned int id, float* position, int a3,
                           int a4, int a5, int a6, void* state);  // 0x00ae4d10
  bool HandleSimulationUpdate(unsigned int a1, unsigned int a2,
                              unsigned int a3);                 // 0x00ae3ed0
};

class cCityDisplayStrategy {
 public:
  unsigned char mPad0[0x14];       // +0x00
  void* mpArrayBegin;              // +0x14
  unsigned char mPad1[0x94];       // +0x18
  int mCount;                      // +0xac

  void UpdateMinimapCityIcon(int icon);  // 0x00ae4ec0
};

}  // namespace SP

namespace {

struct Quaternion {
  float x, y, z, w;
};

// 3x3 float matrix; Assign is a thiscall (dst in ECX, src pushed).
struct Matrix33T {
  float m[9];
  void Assign(const void* src);  // 0x0041cb40
};

// The message handed to the effect objects.
struct XformMsg {
  unsigned short mStatus;  // +0x00
  short mField2;           // +0x02
  float mPosition[3];      // +0x04
  float mField10;          // +0x10
  Matrix33T mMatrix;       // +0x14
};

struct IRefCounted {
  virtual void AddRef();   // +0x0
  virtual void Release();  // +0x4
};

// vtable slots used across the slice.
struct IEffect {
  virtual void f0();                          // +0x00
  virtual void Release();                     // +0x04
  virtual void SetFlag0(int);                 // +0x08
  virtual void fc();                          // +0x0c
  virtual void f10();                         // +0x10
  virtual void f14();                         // +0x14
  virtual void SetTransform(XformMsg*);       // +0x18
  virtual void f1c();                         // +0x1c
  virtual void SetPosition(XformMsg*);        // +0x20
  virtual void f24();                         // +0x24
  virtual void f28();                         // +0x28
  virtual void f2c();                         // +0x2c
  virtual void f30();                         // +0x30
  virtual void f34();                         // +0x34
  virtual void f38();                         // +0x38
  virtual void f3c();                         // +0x3c
  virtual void f40();                         // +0x40
  virtual void SetParam(int, float*, int);    // +0x44
};

struct IImageSource {
  virtual void f0();   // +0x00
  virtual void f4();   // +0x04
  virtual void f8();   // +0x08
  virtual void fc();   // +0x0c
  virtual void f10();  // +0x10
  virtual void f14();  // +0x14
  virtual void f18();  // +0x18
  virtual void* GetImage(unsigned int a, unsigned int b, unsigned int c,
                         int d);  // +0x1c
};

struct IManager {
  virtual void f0();   // +0x00
  virtual void f4();   // +0x04
  virtual void f8();   // +0x08
  virtual void fc();   // +0x0c
  virtual void f10();  // +0x10
  virtual void f14();  // +0x14
  virtual void f18();  // +0x18
  virtual void f1c();  // +0x1c
  virtual void f20();  // +0x20
  virtual void f24();  // +0x24
  virtual void f28();  // +0x28
  virtual bool GetEntry(unsigned int key, int a, void* value);  // +0x2c
};

// Icon object: only the flag word at +0x04 is touched.
struct IconFlagWord {
  unsigned int mFlags;  // +0x00 (object base: the +4 flag is modelled at +0x04)
};

// Minimap sub-object: the object at root->+0x34.
struct IMinimapEntry {
  virtual void f0();   // +0x00
  virtual void f4();   // +0x04
  virtual void f8();   // +0x08
  virtual void fc();   // +0x0c
  virtual void f10();  // +0x10
  virtual void f14();  // +0x14
  virtual void f18();  // +0x18
  virtual void f1c();  // +0x1c
  virtual void f20();  // +0x20
  virtual void f24();  // +0x24
  virtual void f28();  // +0x28
  virtual float* GetQuaternion(float* q);  // +0x2c
  virtual float* GetPosition();            // +0x30
  virtual void f34();  // +0x34
  virtual void f38();  // +0x38
  virtual void f3c();  // +0x3c
  virtual void f40();  // +0x40
  virtual void f44();  // +0x44
  virtual bool IsActive();                 // +0x48
  virtual void f4c();  // +0x4c
  virtual void f50();  // +0x50
  virtual void f54();  // +0x54
  virtual void f58();  // +0x58
  virtual void f5c();  // +0x5c
  virtual void f60();  // +0x60
  virtual void f64();  // +0x64
  virtual void f68();  // +0x68
  virtual void f6c();  // +0x6c
  virtual void f70();  // +0x70
  virtual void f74();  // +0x74
  virtual void f78();  // +0x78
  virtual void f7c();  // +0x7c
  virtual void f80();  // +0x80
  virtual void f84();  // +0x84
  virtual void f88();  // +0x88
  virtual void f8c();  // +0x8c
  virtual void f90();  // +0x90
  virtual void f94();  // +0x94
  virtual void f98();  // +0x98
  virtual void f9c();  // +0x9c
  virtual void fa0();  // +0xa0
  virtual void fa4();  // +0xa4
  virtual void fa8();  // +0xa8
  virtual unsigned int* GetIconObject();   // +0xac (returns ptr with a flag at +4)
};

// Minimap root object: the pointer stored in the record.
struct IMinimapRoot {
  virtual void f0();   // +0x00
  virtual void f4();   // +0x04
  virtual void f8();   // +0x08
  virtual void fc();   // +0x0c
  virtual void f10();  // +0x10
  virtual void f14();  // +0x14
  virtual void f18();  // +0x18
  virtual void f1c();  // +0x1c
  virtual void f20();  // +0x20
  virtual void f24();  // +0x24
  virtual void f28();  // +0x28
  virtual void f2c();  // +0x2c
  virtual void f30();  // +0x30
  virtual void f34();  // +0x34
  virtual void f38();  // +0x38
  virtual void f3c();  // +0x3c
  virtual void f40();  // +0x40
  virtual void f44();  // +0x44
  virtual void f48();  // +0x48
  virtual void f4c();  // +0x4c
  virtual void f50();  // +0x50
  virtual void f54();  // +0x54
  virtual void f58();  // +0x58
  virtual void f5c();  // +0x5c
  virtual void f60();  // +0x60
  virtual void f64();  // +0x64
  virtual void f68();  // +0x68
  virtual void f6c();  // +0x6c
  virtual void f70();  // +0x70
  virtual void f74();  // +0x74
  virtual void f78();  // +0x78
  virtual void f7c();  // +0x7c
  virtual void f80();  // +0x80
  virtual void f84();  // +0x84
  virtual void f88();  // +0x88
  virtual void f8c();  // +0x8c
  virtual void f90();  // +0x90
  virtual void f94();  // +0x94
  virtual void f98();  // +0x98
  virtual void f9c();  // +0x9c
  virtual void fa0();  // +0xa0
  virtual void fa4();  // +0xa4
  virtual void fa8();  // +0xa8
  virtual void* GetEntry34();              // +0xac (returns ptr; sub-object at +0x34)
  virtual void fb0();  // +0xb0
  virtual void fb4();  // +0xb4
  virtual void fb8();  // +0xb8
  virtual void** GetVec();                 // +0xbc (returns {begin,end} ptr)
};

}  // namespace

// External callees and constants of the original image.  The '// 0x...' marker on
// each declaration binds it to the retail address (tools/difftest/resolve.py).
void* EAAllocate(unsigned int size, const char* tag, int a, int b,
                 const char* file, int line);  // 0x00f473a0
IManager* PropertyManager();                             // 0x0067de30
IManager* EffectsManager();                              // 0x0067ddd0
IImageSource* GetImageSrc();                             // 0x0067dd60
bool GetPropertyAsKey(void* out, int key, IManager* value);  // 0x006a1250
void* Fun00bd8750(void* dst, void* src);                 // 0x00bd8750
void* PlanetModel(void* out, float* position);           // 0x00b3d350
void* BuildSurfaceOrientation(void* self, void* scratch);  // 0x00b7f250
void* DirectionToSurfacePosition(void* self, float* dir, void* out);  // 0x00b815a0
void* BlendImages(unsigned int imageId);                 // 0x00bef920
void* CombineImages(void* a, void* b);                   // 0x00bebc90
void* GetSurfacePosition(unsigned int id);               // 0x00b6f0c0
void* GetRecorderState();                                // 0x00435e90
void Start3dSoundByName(unsigned int name, void* state); // 0x00571f80
float* Matrix3FromQuaternion(Matrix33T* dst, Quaternion* q);  // 0x0059c190
float* QuaternionToMatrixSP(Matrix33T* dst, Quaternion* q);   // 0x004a9b40
void XformMsgCtor(XformMsg* msg);                        // 0x00434040
unsigned int PropertyGetUInt(void* prop);                // 0x0041ea00
bool GetPropertyKey(void* dst, void* key);               // 0x006a1250 (2-arg form)

extern unsigned int* sTestSystem;  // 0x015fd928
extern float g_IdQ0;               // 0x0167a610
extern float g_IdQ1;               // 0x0167a614
extern float g_IdQ2;               // 0x0167a618
extern Matrix33T g_IdentityMatrix; // 0x0167a65c
extern float g_ZeroVector[3];      // 0x0167a680
extern float g_One;                // 0x01485720
extern float g_NodeConsts[4];      // 0x015665a8

namespace {

const char kAllocatorHeader[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// Refcount release for a pointer whose counter lives at +8.
void IntrusiveRelease(void* p) {
  if (p == 0)
    return;
  volatile long* c = (volatile long*)((char*)p + 8);
  _InterlockedExchangeAdd(c, -1);
  if (_InterlockedExchangeAdd(c, 0) < 1)
    _InterlockedExchangeAdd(c, 1);
  else
    _InterlockedExchangeAdd(c, 0);
}

// Effect-object release (this + 0x60 through MP).
void ReleaseEffectField(SP::tMarkerNode* n) {
  IntrusiveRelease(n->mEffect.mpPtr);
  if (n->mpModel != 0)
    ((IEffect*)n->mpModel)->Release();
}

void __stdcall FreeMarkerNodeRange(SP::tMarkerNode* first, SP::tMarkerNode* last);  // 0x00ae4930
void __stdcall StartEffect(float* position, float* quaternion);  // 0x00ae4810
SP::tMarkerNode* DestroyMarkerNodeRange(SP::tMarkerNode* first,
                                        SP::tMarkerNode* last,
                                        SP::tMarkerNode* out);    // 0x00ae4520

}  // namespace

// ---- SP::cGameplayMarkerView -------------------------------------------------

namespace SP {

// @ 0x00ae4180
bool cGameplayMarkerView::HasMarker(unsigned int id) {
  tMarkerList* end = &mListHead;
  tMarkerList* node = end->mpNext;
  if (node == end)
    return false;
  do {
    if (((tMarker*)((char*)node + 8))->mId == (int)id)
      return true;
    node = node->mpNext;
  } while (node != end);
  return false;
}

// @ 0x00ae41b0
tMarkerNode* cGameplayMarkerView::FindMarkerNear(float* position, float radius) {
  tMarkerList* end = &mListHead;
  tMarkerList* node = end->mpNext;
  if (node == end)
    return 0;
  float r2 = radius * radius;
  float px = position[0];
  float py = position[1];
  float pz = position[2];
  do {
    tMarker* m = (tMarker*)((char*)node + 8);
    float dx = m->mPosition[0] - px;
    float dy = m->mPosition[1] - py;
    float dz = m->mPosition[2] - pz;
    if (dx * dx + dy * dy + dz * dz < r2)
      return (tMarkerNode*)((char*)node + 8);
    node = node->mpNext;
  } while (node != end);
  return 0;
}

// @ 0x00ae4230
tMarkerNode* tMarkerNode::InitMarkerNode() {
  tMarkerNode& r = *this;
  r.mId = -1;
  r.mPosition.v[0] = g_IdQ0;
  r.mPosition.v[1] = g_IdQ1;
  r.mPosition.v[2] = g_IdQ2;
  r.mUnk20 = -1;
  r.mFlag24 = false;
  r.mFlag25 = true;
  r.mFlag26 = false;
  r.mUnk28 = -1;
  r.mUnk2c = -1;
  r.mFlag30 = false;
  r.mFlag31 = false;
  r.mUnk34 = 0;
  r.mpModel = 0;
  r.mUnk3c = 0;
  r.mFlag40 = false;
  r.mUnk44[0] = 0;
  r.mUnk44[1] = 0;
  r.mUnk44[2] = 0;
  r.mUnk44[3] = 0;
  r.mUnk54[0] = 0;
  r.mUnk54[1] = 0;
  r.mUnk54[2] = 0;
  r.mEffect.mpPtr = 0;
  return this;
}

// @ 0x00ae42a0
void tMarkerNode::ReleaseMarkerNode() {
  IntrusiveRelease(mEffect.mpPtr);
  void* model = mpModel;
  if (model != 0)
    ((IRefCounted*)model)->Release();
}

// @ 0x00ae43a0
tMarkerNode* tMarkerList::AllocMarkerNode() {
  char* p = (char*)EAAllocate(0x44, "Simulator", 0, 0, kAllocatorHeader, 0xd1);
  char* r = p + 8;
  if (r != 0) {
    *(int*)(r + 0x00) = -1;
    *(float*)(r + 0x04) = 0.0f;
    *(float*)(r + 0x08) = 0.0f;
    *(float*)(r + 0x0c) = 0.0f;
    *(int*)(r + 0x10) = 0;
    *(int*)(r + 0x14) = 0;
    *(int*)(r + 0x18) = 0;
    *(int*)(r + 0x1c) = 0;
    *(float*)(r + 0x20) = g_NodeConsts[0];
    *(float*)(r + 0x24) = g_NodeConsts[1];
    *(float*)(r + 0x28) = g_NodeConsts[2];
    *(float*)(r + 0x2c) = g_NodeConsts[3];
    *(int*)(r + 0x30) = 0;
    *(int*)(r + 0x38) = 0;
  }
  return (tMarkerNode*)p;
}

// @ 0x00ae4430
tMarkerNode* tMarkerNode::AssignMarkerNode(tMarkerNode* src) {
  mId = src->mId;
  mPosition = src->mPosition;
  mUnk10 = src->mUnk10;
  mpUnk14 = src->mpUnk14;
  mpUnk18 = src->mpUnk18;
  mUnk1c = src->mUnk1c;
  mUnk20 = src->mUnk20;
  mFlag24 = src->mFlag24;
  mFlag25 = src->mFlag25;
  mFlag26 = src->mFlag26;
  mUnk28 = src->mUnk28;
  mUnk2c = src->mUnk2c;
  mFlag30 = src->mFlag30;
  mFlag31 = src->mFlag31;
  mUnk34 = src->mUnk34;
  void* now = src->mpModel;
  void* old = mpModel;
  if (now != old) {
    if (now != 0)
      ((IRefCounted*)now)->AddRef();
    mpModel = now;
    if (old != 0)
      ((IRefCounted*)old)->Release();
  }
  mUnk3c = src->mUnk3c;
  mFlag40 = src->mFlag40;
  for (int i = 0; i < 4; i++)
    mUnk44[i] = src->mUnk44[i];
  for (int i = 0; i < 3; i++)
    mUnk54[i] = src->mUnk54[i];
  mEffect.Assign(src->mEffect.mpPtr);
  return this;
}

// @ 0x00ae4610
void cGameplayMarkerView::RemoveMarker() {
  int count = mCount;
  int best = 0x7fffffff;
  int bestIndex = -1;
  if (count > 1) {
    tMarkerNode* rec = mpArrayBegin + 1;
    int i = 1;
    do {
      if (!rec->mFlag30 && rec->mUnk2c < best) {
        best = rec->mUnk2c;
        bestIndex = i;
      }
      i++;
      rec++;
    } while (i < count);
  }
  if (bestIndex == -1)
    return;
  tMarkerNode* marker = mpArrayBegin + bestIndex;
  ImageRef tmp;
  tmp.mpPtr = 0;
  if (marker->mEffect.mpPtr != 0)
    return;
  if (marker->mUnk54[0] == 0)
    return;
  IImageSource* src = GetImageSrc();
  void* img = src->GetImage((unsigned int)marker->mUnk54[0],
                            (unsigned int)marker->mUnk54[1],
                            (unsigned int)marker->mUnk54[2], 0);
  tmp.Assign(img);
  if (tmp.mpPtr != 0) {
    marker->mEffect.Assign(tmp.mpPtr);
    IntrusiveRelease(tmp.mpPtr);
  }
}

// @ 0x00ae46f0
void cGameplayMarkerView::UpdateMarkerTransform(unsigned int id,
                                                float* position,
                                                float* quaternion) {
  tMarkerList* end = &mListHead;
  tMarkerList* node = end->mpNext;
  bool done = false;
  if (node == end)
    return;
  do {
    if (done)
      return;
    if (*(unsigned int*)((char*)node + 8) == id) {
      void* object = *(void**)((char*)node + 0x18);
      if (object != 0) {
        XformMsg msg;
        msg.mPosition[0] = g_ZeroVector[0];
        msg.mPosition[1] = g_ZeroVector[1];
        msg.mPosition[2] = g_ZeroVector[2];
        msg.mStatus = 0;
        msg.mField2 = 0;
        msg.mField10 = g_One;
        msg.mMatrix.Assign(&g_IdentityMatrix);
        ((IEffect*)object)->SetPosition(&msg);
        msg.mPosition[0] = position[0];
        msg.mPosition[1] = position[1];
        msg.mPosition[2] = position[2];
        msg.mStatus |= 4;
        msg.mField2++;
        Quaternion* q = (Quaternion*)quaternion;
        Matrix3FromQuaternion(&msg.mMatrix, q);
        msg.mStatus |= 2;
        msg.mField2++;
        ((IEffect*)object)->SetTransform(&msg);
      }
      done = true;
    }
    node = node->mpNext;
  } while (node != end);
}

// @ 0x00ae49d0
tMarker* cGameplayMarkerView::AddMarker(int a1, unsigned int id, float* position,
                                        int a4, void* a5, int style, void* state,
                                        bool playSound) {
  tMarkerNode* node = mListHead.AllocMarkerNode();
  tMarkerList* head = &mListHead;
  void* base = (char*)head + 0;
  (void)base;
  // link the new node in front of the sentinel (head is the sentinel)
  ((tMarkerList*)node)->mpNext = head;
  ((tMarkerList*)node)->mpPrev = head->mpPrev;
  head->mpPrev->mpNext = (tMarkerList*)node;
  head->mpPrev = (tMarkerList*)node;
  tMarker* rec = (tMarker*)((char*)node + 8);

  rec->mPosition[0] = position[0];
  rec->mPosition[1] = position[1];
  rec->mPosition[2] = position[2];
  rec->mpOrientation = (void*)a4;
  rec->mpArgument = a5;
  rec->mUnk1c = a1;
  rec->mId = (int)id;
  if (a5 == 0) {
    float tmp[12];
    Fun00bd8750(tmp, position);
    void* model = PlanetModel(tmp, position);
    float* surface = (float*)BuildSurfaceOrientation(model, tmp);
    rec->mSurface[0] = surface[0];
    rec->mSurface[1] = surface[1];
    rec->mSurface[2] = surface[2];
    rec->mSurface[3] = surface[3];
  } else {
    float* src = (float*)a5;
    rec->mSurface[0] = src[0];
    rec->mSurface[1] = src[1];
    rec->mSurface[2] = src[2];
    rec->mSurface[3] = src[3];
  }
  rec->mStyle = style;

  const void* key = 0;
  switch ((unsigned int)a4) {
    case 0: key = (const void*)0x4fe5f63; break;
    case 1: key = (const void*)0x4fe5f6a; break;
    case 2: key = (const void*)0x4fe5f70; break;
    case 3: key = (const void*)0x4fe5f75; break;
  }
  IManager* pm = PropertyManager();
  void* prop = 0;
  (void)prop;
  if (pm->GetEntry(0x2e4b4cc, (int)a5, &prop)) {
    if (key != 0 && pm != 0) {
      bool ok = pm->GetEntry((unsigned int)key, (int)pm, &prop);
      (void)ok;
    }
  }
  (void)playSound;
  (void)state;
  return rec;
}

// @ 0x00ae4d10
tMarker* cGameplayMarkerView::AddMarkerSimple(int a0, unsigned int id,
                                              float* position, int a3, int a4,
                                              int a5, int a6, void* state) {
  tMarkerNode* node = mListHead.AllocMarkerNode();
  tMarkerList* head = &mListHead;
  ((tMarkerList*)node)->mpNext = head;
  ((tMarkerList*)node)->mpPrev = head->mpPrev;
  head->mpPrev->mpNext = (tMarkerList*)node;
  head->mpPrev = (tMarkerList*)node;
  tMarker* rec = (tMarker*)((char*)node + 8);

  rec->mPosition[0] = position[0];
  rec->mPosition[1] = position[1];
  rec->mPosition[2] = position[2];
  rec->mSurface[0] = *(float*)&a3;
  rec->mSurface[1] = *(float*)&a4;
  rec->mSurface[2] = *(float*)&a5;
  rec->mSurface[3] = *(float*)&a6;
  rec->mUnk1c = a0;
  rec->mId = (int)id;
  rec->mStyle = (int)state;
  (void)state;
  return rec;
}

// @ 0x00ae3ed0
bool cGameplayMarkerView::HandleSimulationUpdate(unsigned int arg1,
                                                 unsigned int /*arg2*/,
                                                 unsigned int /*arg3*/) {
  int count = (int)(long)(((char*)mpArrayEnd - (char*)mpArrayBegin) / 0x64);
  bool found = false;
  int best = 0x7fffffff;
  int bestIdx = 0x7fffffff;
  int sel = 0;
  int lastFlag = 0;
  if (count > 0) {
    tMarkerNode* rec = mpArrayBegin;
    int i = 0;
    do {
      if (!rec->mFlag24) {
        if (rec->mFlag30 == false && rec->mUnk2c < best) {
          found = true;
          best = rec->mUnk2c;
          bestIdx = i;
        }
      } else {
        lastFlag = i;
        if (arg1 != 0) {
          sel = lastFlag;
          goto use;
        }
      }
      i++;
      rec++;
    } while (i < count);
  }
  sel = lastFlag;
  if (arg1 == 0) {
    if (!found)
      return false;
    if (bestIdx != 0x7fffffff)
      sel = bestIdx;
  }
use:;
  tMarkerNode* rec = mpArrayBegin + sel;
  void* imgA = BlendImages((unsigned int)rec->mUnk28);
  void* imgB = CombineImages(imgA, (void*)rec->mUnk34);
  (void)imgB;
  bool flag25 = rec->mFlag25;
  bool flag31 = rec->mFlag31;
  unsigned int sel2 = flag25 ? (flag31 ? 2u : 0u) : (flag31 ? 3u : 1u);
  const void* key = 0;
  switch (sel2) {
    case 0: key = (const void*)0x4fe5f63; break;
    case 1: key = (const void*)0x4fe5f6a; break;
    case 2: key = (const void*)0x4fe5f70; break;
    case 3: key = (const void*)0x4fe5f75; break;
  }
  IManager* pm = PropertyManager();
  void* prop = 0;
  if (pm->GetEntry(0x2e4b4cc, (int)imgB, &prop)) {
    if (key != 0 && prop != 0) {
      void* out = 0;
      pm->GetEntry(0x40828100, (int)prop, &out);
    }
  }
  return true;
}

}  // namespace SP

// ---- free helpers ------------------------------------------------------------

namespace {

// @ 0x00ae4520
SP::tMarkerNode* DestroyMarkerNodeRange(SP::tMarkerNode* first,
                                        SP::tMarkerNode* last,
                                        SP::tMarkerNode* out) {
  if (first == last)
    return out;
  do {
    IntrusiveRelease(first->mEffect.mpPtr);
    if (first->mpModel != 0)
      ((IEffect*)first->mpModel)->Release();
    first++;
    out++;
  } while (first != last);
  return out;
}

// @ 0x00ae4810
void __stdcall StartEffect(float* position, float* quaternion) {
  IManager* mgr = EffectsManager();
  void* effect = 0;
  if (effect != 0) {
    effect = 0;
    ((IEffect*)effect)->Release();
  }
  if (mgr->GetEntry(0x8e31aec8, 0, &effect)) {
    XformMsg msg;
    msg.mPosition[0] = g_ZeroVector[0];
    msg.mPosition[1] = g_ZeroVector[1];
    msg.mPosition[2] = g_ZeroVector[2];
    msg.mStatus = 0;
    msg.mField2 = 0;
    msg.mField10 = g_One;
    msg.mMatrix.Assign(&g_IdentityMatrix);
    msg.mPosition[0] = position[0];
    msg.mPosition[1] = position[1];
    msg.mPosition[2] = position[2];
    msg.mStatus |= 4;
    msg.mField2++;
    Quaternion* q = (Quaternion*)quaternion;
    QuaternionToMatrixSP(&msg.mMatrix, q);
    msg.mStatus |= 2;
    msg.mField2++;
    ((IEffect*)effect)->SetTransform(&msg);
    ((IEffect*)effect)->SetFlag0(0);
  }
  if (effect != 0)
    ((IEffect*)effect)->Release();
}

// @ 0x00ae4930
void __stdcall FreeMarkerNodeRange(SP::tMarkerNode* first, SP::tMarkerNode* last) {
  while ((unsigned int)first < (unsigned int)last) {
    IntrusiveRelease(first->mEffect.mpPtr);
    if (first->mpModel != 0)
      ((IEffect*)first->mpModel)->Release();
    first++;
  }
}

}  // namespace

// ---- SP::cCityDisplayStrategy ------------------------------------------------

namespace SP {

// A vector element: a small object whose +0x34 embeds the minimap entry.
struct MinimapVectorElem {
  unsigned char mPad0[0x34];
  IMinimapEntry mEntry;  // +0x34
};

// @ 0x00ae4ec0
void cCityDisplayStrategy::UpdateMinimapCityIcon(int icon) {
  int count = mCount;
  if (count <= 0)
    return;
  char* rec = (char*)mpArrayBegin + 0x38;
  int i = 0;
  IMinimapRoot* root = 0;
  for (;;) {
    if (rec[-8] == 1) {
      root = *(IMinimapRoot**)rec;
      if (root != 0)
        break;
    }
    i++;
    rec += 0x64;
    if (i >= count)
      return;
  }
  char* owner = (char*)root->GetEntry34();
  if (owner == 0)
    return;
  IMinimapEntry* entry = (IMinimapEntry*)(owner + 0x34);
  if (!entry->IsActive())
    return;
  if (icon == 1) {
    float* a = entry->GetPosition();
    float* q = entry->GetQuaternion(a);
    StartEffect(q, a);
  } else if (icon == 2) {
    entry->GetIconObject()[1] &= ~1u;
  }
  void** vec = root->GetVec();
  MinimapVectorElem** it = (MinimapVectorElem**)vec[0];
  MinimapVectorElem** stop = (MinimapVectorElem**)vec[1];
  for (; it != stop; it++) {
    IMinimapEntry* e = &(*it)->mEntry;
    if (icon == 1) {
      float* a = e->GetPosition();
      float* q = e->GetQuaternion(a);
      StartEffect(q, a);
    } else if (icon == 2) {
      e->GetIconObject()[1] &= ~1u;
    }
  }
}

}  // namespace SP
