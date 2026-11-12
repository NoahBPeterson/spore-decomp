// src/game/SPEditors/SPEditorSpine.cpp -- migrated from slice(s) s005d53e0, s005d36e0, s005d27e0, s005d4630, s005d1f30, s005d12c0, s005d02d0, s005cf830, s005ce9b0, s005cdd00, s005ccc90 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorSpine.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include "SP/cSPEditorSpine.h"
#include <math.h>
#include <float.h>
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorVertebraInfo.h"
#include "SP/cSPEditorHandleSpine.h"
#include <xmmintrin.h>
#include <intrin.h>
#include "SP/cEditorsTokenTranslator.h"
#include "SP/cStringTokenTranslator.h"

// ---- items of slice s005ccc90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
class cRefCounted {
 public:
  int mPad0;
  int mRef;  // +4
  void IncRef(int unused);
  void DecRef(int unused);

  char pad0[4];
};
class cTimeObj {
 public:
  PV(0) PV(1)
  virtual int GetType();  // +0x8
  int mPad4, mPad8;
  float mFloat0c;         // +0xc
  cTimeObj* mChild;       // +0x10
};
inline float Clamp(float x, float lo, float hi)
{
  __asm {
    movss xmm0, x
    maxss xmm0, lo
    minss xmm0, hi
    movss x, xmm0
  }
  return x;
}
class cInterp {
 public:
  char pad0[0x88];
  float mFloat88;  // +0x88
  float mFloat8c;  // +0x8c
  float mFloat90;  // +0x90
  float mFloat94;  // +0x94
  float mFloat98;  // +0x98
  void Interp(float a, float b, float* out1, float* out2);
};
// ---- items of slice s005ccc90 end

// ---- items of slice s005cdd00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_004a5970(void*, ...);
struct __declspec(align(16)) hkVector4_s005c_dd00 {
  float x, y, z, w;
  hkVector4_s005c_dd00() {}
  hkVector4_s005c_dd00(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
struct hkTransform_s005c_dd00 {
  char pad[0x40];
};
class hkEntity_s005c_dd00 {
 public:
  void removeReference();
  void addCollisionListener(void* listener);
};
class hkRigidBody_s005c_dd00 : public hkEntity_s005c_dd00 {
 public:
  void setTransform(const hkTransform_s005c_dd00& t);
};
class hkWorld_s005c_dd00 {
 public:
  hkEntity_s005c_dd00* addEntity(hkEntity_s005c_dd00* e, int activation);
};
class cHandleish {
 public:
  void SetEnabled(int enabled);  // 0x005a8a80
};
class hkGenericConstraintData {
 public:
  hkGenericConstraintData();
};
class hkMemory {
 public:
  virtual void* slot0();
  virtual void* slot1();
  virtual void* slot2();
  virtual void* slot3();
  virtual void* allocate(int size, int memClass);  // vtable +0x10
};
extern hkMemory* g_hkMemory;  // 0x016e4178
class hkConstraintConstructionKit {
 public:
  char pad[0x1c];
  void begin(hkGenericConstraintData* data);
  int setPivotA(const hkVector4_s005c_dd00& v);
  int setPivotB(const hkVector4_s005c_dd00& v);
  int setLinearDofWorld(const hkVector4_s005c_dd00& v, int dof);
  void constrainLinearDof(int dof);
  void setAngularBasisABodyFrame();
  void setAngularBasisBBodyFrame();
  void constrainToAngularDof(int dof);
  void end();
};
namespace SP {
namespace EditorUtils {
float GetExactSkinRadiusFromVertebra(float scale);  // 0x004a5b70
}
}
namespace SP {
class cSPEditorSpine_s005c_dd00 {
 public:
  char pad00[0x14];
  hkWorld_s005c_dd00* mpWorld;            // +0x14
  void* mpCollisionListener;   // +0x18
  char pad1c[0x40 - 0x1c];
  hkConstraintConstructionKit* mChainConstraint;  // +0x40 (unused here)
  void* mpCursorSpring;                           // +0x44
  char pad48[0x54 - 0x48];
  float mSpineNewVertebraRelativeScale;  // +0x54
  int mSpineHavokWorldNumSolverIters;    // +0x58
  int mSpineHavokWorldSimType;           // +0x5c
  float mSpineHavokWorldSolverTau;       // +0x60
  float mSpineHavokWorldSolverDamp;      // +0x64
  float mSpineFrictionConstant;          // +0x68
  float mSpineVertebraAllowedPenetrationDepth;  // +0x6c
  float mSpineVertebraMaxMassProportion;        // +0x70
  char pad74[0x9c - 0x74];
  int mSpineField9c;                     // +0x9c
  float mSpineFieldA0;                   // +0xa0
  float mSpineFieldA4;                   // +0xa4
  float mSpineLooseLinearDamping;        // +0xa8
  float mSpineLooseAngularDamping;       // +0xac
  float mSpineTightLinearDamping;        // +0xb0
  float mSpineTightAngularDamping;       // +0xb4
  float mSpineMouseSpringDamping;        // +0xb8
  float mSpineMouseSpringElasticity;     // +0xbc
  float mSpineMouseMaxForceFactor;       // +0xc0
  char padc4[0x11c - 0xc4];
  float mVertebraHalfWidth;              // +0x11c
  char pad120[0x12c - 0x120];

  hkRigidBody_s005c_dd00* CreateVertebraBody(float scale, hkTransform_s005c_dd00* transform);  // 0x005cdd00 (SP::cSPEditorSpine::CreateVertebraBody)
  int* AddVertebraBody(int* out, float scale, hkTransform_s005c_dd00* transform);
  void LoadDynamicTuning();  // 0x005ce300 (SP::cSPEditorSpine::LoadDynamicTuning)
  void CalcVertebraPhysicsBoundingBox(float param, unsigned char* shape, float* out);  // 0x005ce680 (SP::cSPEditorSpine::CalcVertebraPhysicsBoundingBox)
};
}
namespace SP {
class cSpineHelper {
 public:
  char pad00[0xe8];
  void* mFieldE8;   // +0xe8
  void* mFieldEC;   // +0xec
  char padF0[0xf4 - 0xf0];
  cHandleish* mFieldF4;  // +0xf4
  cHandleish* mFieldF8;  // +0xf8

  void SetEnabled(int enabled);       // 005ce210
  void ReleaseE8();                   // 005ce250
  void* GetHandle(int id);            // 005ce270
};
}
// ---- items of slice s005cdd00 end

// ---- items of slice s005ce9b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct E20 {
  int a;
  int b;
  float c;
  float d;
  int e;
  E20() {}
  E20(const E20& o) : a(o.a), b(o.b), c(o.c), d(o.d), e(o.e) {}
};
}
namespace SP {
struct E20Iter {
  E20* mpNode;
  E20Iter() {}
  E20Iter(E20* p) : mpNode(p) {}
  E20& operator*() const { return *mpNode; }
  bool operator!=(const E20Iter& o) const { return mpNode != o.mpNode; }
  E20Iter& operator++() {
    ++mpNode;
    return *this;
  }
};
}
namespace SP {
struct Vec2 { float x, y; };
}
namespace SP {
struct V3 { float x, y, z; };
}
namespace SP {
struct Hit;
}
namespace SP {
struct Circle {            // 0x24-byte record of the spine "belt" outline
  uint32_t id;
  float x, y, r;
  uint32_t pad[5];
  float FindHit(const Vec2* pt, int ccw, Hit** out);   // 0x005D53E0, thiscall
};
}
namespace SP {
struct Hit {
  Circle* a;
  Circle* b;
  float x, y;
  int kind;                // 0 = tangent hop, 1 = search, 2 = finish
};
}
namespace SP {
struct CircleVec { Circle* begin; Circle* end; };
}
namespace SP {
struct OutPath {           // vector of dwords + helpers
  uint32_t* begin;
  uint32_t* end;
  void Arc(const Vec2* center, float r, const Vec2* pt, float ang);   // 0x005D5A30
  void Join(const Vec2* a, const Vec2* b);                            // 0x005D5AD0
};
}
namespace SP {
struct Curve { void Eval(Vec2* out, float t); };                      // 0x005D5050
}
namespace SP {
struct SpineNode {
  uint32_t pad0[0x13];
  float px, py;            // +0x4c, +0x50
  uint32_t pad1[(0xdc0 - 0x54) / 4];
  float param;             // +0xdc0
  uint32_t pad2;
  uint32_t flags;          // +0xdc8
};
}
namespace SP {
struct KeyHolder { uint32_t pad[0x16]; uint32_t key; };
}
namespace SP {
struct Block {
  uint32_t pad[10];
  KeyHolder* holder;       // +0x28
  int GetSymmetryIndex();  // 0x0044F220
};
}
namespace SP {
struct SpineHandle {
  uint32_t pad0[0x3a];
  SpineNode* n1;           // +0xe8
  SpineNode* n2;           // +0xec
  uint32_t pad1[(0x120 - 0xf0) / 4];
  Curve* c1;               // +0x120
  Curve* c2;               // +0x124
  Vec2* NearestParam(Vec2* res, SpineNode* o);                        // 0x005CF110
  void Extrude(Block* blk, float t, float s, int a4);                 // 0x005CF4F0
};
}
float* FUN_004a5d10(void* out, SP::SpineNode* n);
float FUN_004a5bd0(SP::SpineNode* n);
void FUN_0049d6b0(SP::Block* b, SP::V3 c, SP::V3 d, int a4, int flag, float mx);
void FUN_0069b650(SP::Vec2* out, const SP::Vec2* p, const SP::Vec2* a, const SP::Vec2* b);
char FUN_005d4ff0(const SP::Vec2* p, const SP::Vec2* q, const SP::Vec2* r);
int FUN_005d5630(SP::Vec2 a, SP::Vec2 b, SP::V3 circ, float* out4);
template <class T> inline const T& MaxRef(const T& a, const T& b) { return (b < a) ? a : b; }
template <class T> inline const T& MinRef(const T& a, const T& b) { return (a < b) ? a : b; }
// ---- items of slice s005ce9b0 end

// ---- items of slice s005d02d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void EASTL_allocator_deallocate(void* p);  // 0x00f47380
namespace SP {
struct Leg {
  char pad[0xdc0];
  float mFieldDC0;  // +0xdc0
};
}
namespace SP {
class LimbVector {
 public:
  Leg** mpBegin;
  Leg** mpEnd;
  Leg** mpCapacity;
  void* mReserved0;
  void* mReserved1;
  LimbVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~LimbVector() {
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  Leg* operator[](unsigned int i) const { return mpBegin[i]; }
};
}
namespace SP {
namespace EditorUtils {
void GetAllLimbs(void* manager, LimbVector* out, int flag);  // 0x004a0020
}
}
namespace SP {
namespace EditorUtils {
void* GetFirstFootBlock(void* leg);                          // 0x004a9840
}
}
namespace SP {
class cSPEditorSpine_s005d_02d0 {
 public:
  char pad00[0xe8];
  void* mpLimbs;  // +0xe8

  Leg* GetFirstLeg();   // 005d0ce0 0x005d0ce0
  Leg* GetLastLeg();    // 005d0d90 0x005d0d90
};
}
// ---- items of slice s005d02d0 end

// ---- items of slice s005d12c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Sub24 {
  int mW[5];
  Sub24(const Sub24& other);
  Sub24& operator=(const Sub24& other);
};
}
namespace SP {
struct Elem24 {
  int mA;
  float mB;
  float mC;
  float mD;
  Sub24 mSub;
  Elem24(const Elem24& other) : mA(other.mA), mB(other.mB), mC(other.mC), mD(other.mD), mSub(other.mSub) {}
};
}
namespace SP {
class cSpine75 {
 public:
  char pad00[0xc5];
  bool mFieldC5;  // +0xc5

  void SetFlag(bool enable, int unused);  // 005d1600
  void EnableBody();                      // 005d1530
  void DisableBody();                     // 005d14a0
};
}
// ---- items of slice s005d12c0 end

// ---- items of slice s005d1f30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct RBNodeBase {
  RBNodeBase* mpNodeRight;   // +0
  RBNodeBase* mpNodeLeft;    // +4
  RBNodeBase* mpNodeParent;  // +8
  int mnColor;               // +0xc
};
}
namespace SP {
struct RBNode : RBNodeBase {
  unsigned int mKey;  // +0x10
};
}
namespace SP {
struct cSPEditorVertebraInfo_s005d_1f30 {
  void* mpRigidBody;         // +0
  void* mpHingeConstraint;   // +4
  void* mpPlanarConstraint;  // +8
  int mOrderInSpine;         // +0xc
};
}
namespace SP {
struct VertebraMap {
  char pad0[4];         // +0x00 comparator / allocator (empty)
  RBNodeBase mAnchor;   // +0x04 (sentinel); begin() = mAnchor.mpNodeLeft
  int mnSize;           // +0x14
  int pad18;            // +0x18 (the map object spans 0x1c bytes)

  RBNode** find(RBNode** it, const unsigned int* key) const;    // 0x00e5c780
  cSPEditorVertebraInfo_s005d_1f30& operator[](const unsigned int& key);   // 0x00632e90
};
}
namespace SP {
struct hkRefObj {
  virtual void vDestroy(int deleteIt);  // slot 0
  unsigned short mMemSizeAndFlags;      // +4
  unsigned short mReferenceCount;       // +6

  void Release() {
    if (mMemSizeAndFlags) {
      if (--mReferenceCount == 0) vDestroy(1);
    }
  }
};
}
namespace SP {
class hkMemory_s005d_1f30 {
 public:
  virtual void* pad0();
  virtual void* pad1();
  virtual void* pad2();
  virtual void* pad3();
  virtual void* allocate(int size, int align);  // slot at vtable +0x10
};
}
namespace SP {
class hkWorld {
 public:
  void* addConstraint(void* constraint);      // 0x01086da0
  void removeConstraint(char* out, void* c);  // 0x01086e90
};
}
namespace SP {
struct hkRigidMotion {
  char pad0[0xc8];
  float mLinearDamping;   // +0xc8
  float mAngularDamping;  // +0xcc
  float getMass() const;  // 0x01088270
};
}
namespace SP {
struct hkRigidBody_s005d_1f30 {
  void* mpVtbl;          // +0
  char pad04[0x54];
  hkRigidMotion* mBody;  // +0x58 (motion sub-object)
};
}
namespace SP {
struct hkTransform_s005d_1f30 {
  float m[16];
};
}
namespace SP {
struct hkConstraintInstance {
  void* mpVtbl;  // +0
  char pad04[8];
};
}
namespace SP {
struct hkLimitedHingeConstraintData : hkRefObj {
  void* mpEntityA;                          // +8
  float mSpineChainDamping;                 // +0xc
  float mSpineHingeAngularLimitsTauFactor;  // +0x10
  float mSpineMassTimesFactor;              // +0x14
  float mSpineChainTau;                     // +0x18
  float mAxisA[4];                          // +0x20
  char pad30[0x30];
  float mAxisB[4];  // +0x60
  char pad70[0x26];
  unsigned short mFlags96;  // +0x96

  void setInBodySpace(const hkTransform_s005d_1f30& a, const hkTransform_s005d_1f30& b, const hkTransform_s005d_1f30& c,
                      const hkTransform_s005d_1f30& d, const hkTransform_s005d_1f30& e, const hkTransform_s005d_1f30& f);
  // 0x0108aec0
};
}
namespace SP {
struct cSPEditorBlock_s005d_1f30 {
  char pad00[0x48];
  float mField48;  // +0x48
  float mField4c;  // +0x4c
  float mField50;  // +0x50
  char pad54[0xc];
  float mOrientation60[12];  // +0x60
  char pad90[0x148];
  float mField1d8;  // +0x1d8
};
}
namespace SP {
struct hkConstraintChainState : hkRefObj {
  char pad08[0x10];
  int mSpineMinCollisionDeadZoneDistance;  // +0x18
  int mSpineUseFewerAxialConstraints;      // +0x1c
};
}
namespace SP {
extern void* g_hkMemoryInstance;  // 0x016e4178
}
namespace SP {
RBNode* RBTreeIncrement(RBNodeBase* node);  // 0x00921580
}
namespace SP {
void* FUN_004a5970(void* key);              // 0x004a5970 (next vertebra block key)
}
namespace SP {
void* CreateAxialConstraintData(int unused);                            // 0x005ce0c0
}
namespace SP {
void* FUN_0108bb00(void* self);                                         // 0x0108bb00
}
namespace SP {
void* FUN_0108bf10(void* self, void* a, void* b, void* c, int d);       // 0x0108bf10
}
namespace SP {
void* FUN_0108ba70(void* a, void* b);                                   // 0x0108ba70
}
namespace SP {
void* FUN_0108acb0(void* self);                                         // 0x0108acb0
}
namespace SP {
void* FUN_0108ac30(void* self, void* entity);                           // 0x0108ac30
}
namespace SP {
void FUN_0108ae30(void* self);                                          // 0x0108ae30
}
namespace SP {
void HavokAlignedRoutine(void* src, void* dst);  // 0x004a92c0
}
namespace SP {
void SpineBigStub(void* a, void* b);             // 0x005cd670
}
namespace SP {
static hkRefObj* hkAlloc(int size) {
  void* p = ((hkMemory_s005d_1f30*)g_hkMemoryInstance)->allocate(size, 0x29);
  ((hkRefObj*)p)->mMemSizeAndFlags = (unsigned short)size;
  return (hkRefObj*)p;
}
}
namespace SP {
class cSpine76 {
 public:
  char pad00[0x14];
  hkWorld* mpHavokWorld_14;  // +0x14
  char pad18[4];
  hkWorld* mpHavokWorld;  // +0x1c
  char pad20[0x18];
  void* mpChain;  // +0x38
  char pad3c[0x3c];
  bool mSpineVertebraHavokPaddingFactor;  // +0x78
  char pad79[3];
  int mSpineMinCollisionDeadZoneDistance;  // +0x7c
  bool mSpineUseFewerAxialConstraints;     // +0x80
  char pad81[3];
  float mSpineChainTau;                     // +0x84
  float mSpineChainDamping;                 // +0x88
  float mSpineHingeAngularLimitsTauFactor;  // +0x8c
  char pad90[0xc];
  int mMaxFlexIndex;                        // +0x9c
  float mScaleOfLeastFlexibility;           // +0xa0
  float mSpineDampingMaxInfluenceDistance;  // +0xa4
  float mSpineLooseLinearDamping;           // +0xa8
  float mSpineLooseAngularDamping;          // +0xac
  char padb0[0x1c];
  VertebraMap mVertebrae;          // +0xcc
  cSPEditorBlock_s005d_1f30* mFirstVertebra;  // +0xe8
  cSPEditorBlock_s005d_1f30* mLastVertebra;   // +0xec
  char padf0[0x2c];
  float mVertebraHalfWidth;  // +0x11c

  void SetTuning(int unused);                        // 005d2740
  void Refresh(int unused);                          // 005d2790
  __declspec(noinline) void FUN_005d1ba0();          // 005d1ba0
  __declspec(noinline) void FUN_005d1e70();          // 005d1e70
  __declspec(noinline) void FUN_005d1d40();          // 005d1d40
  void FUN_005d1f30();                               // 005d1f30 (ReconstructChain)
  __declspec(noinline) void FUN_005d2480(int key);   // 005d2480
  __declspec(noinline) void FUN_005d25c0(unsigned int key);  // 005d25c0
  __declspec(noinline) int* AddVertebraBody(int* pOut, float f, const hkTransform_s005d_1f30& t);
  // 0x005ce060
  void FUN_005cdae0(cSPEditorVertebraInfo_s005d_1f30* info);  // 0x005cdae0
};
}
namespace SP {
volatile int g_spine76Sink = 0;
}
using SP::cSPEditorBlock_s005d_1f30;
using SP::cSPEditorVertebraInfo_s005d_1f30;
using SP::cSpine76;
using SP::RBNode;
using SP::RBTreeIncrement;
using SP::hkRefObj;
using SP::hkRigidBody_s005d_1f30;
using SP::hkTransform_s005d_1f30;
// ---- items of slice s005d1f30 end

// ---- items of slice s005d27e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long idx);
extern unsigned long g_tlsThreadMem;                 // 0x016e4174
extern char vtbl_collector[];                       // 0x013ef55c
extern char vtbl_13f89d4[], vtbl_13f89c4[], vtbl_cEditorResource[], vtbl_cContentValidationSummarizer[];
extern float g_015ba0d0, g_015ba0d4;
void operator_delete__(void* p);   // 0x00f47380 (cdecl)
struct RefObj {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
};
struct HandleObj {
    virtual void v0();
    virtual void Release();
virtual void v2();
virtual void v3();
    virtual void Delete(int flag);
virtual void v5();
virtual void v6();
    virtual void Reset();
    void SetState(RefObj* o);            // 0x005a8a60 cHandleish::SetState
};
struct HkRef {
    virtual void* Destroy(int flags);
    unsigned short memSize;
    short refCount;
    void removeReference();              // 0x0109ae60 hkWorldObject::removeReference
    void release() { if (memSize != 0) { if (--refCount == 0) Destroy(1); } }
};
struct HkWorld : HkRef {
    void removeAction(HkRef* a);                     // 0x01086f40 hkWorld::removeAction
    void removeConstraint(char* tmp, void* c);       // 0x01086e90 hkWorld::removeConstraint
    void removeEntity(char* tmp, void* b);           // 0x01083110
    void addPhantom(HkRef* p);                       // 0x01083320 hkWorld::addPhantom
    void removePhantom(HkRef* p);                    // 0x01083400 hkWorld::removePhantom
};
struct hkThreadMem {
    void deallocateChunk(void* p, int size, int type);   // 0x0107db10
};
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0 (EA)
struct Block_s005d_27e0;
Block_s005d_27e0* NextVertebra(Block_s005d_27e0* b);           // 0x004a5970 (cdecl)
template <class T> struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    AutoRef(T* p) : mp(p) { if (p) p->AddRef(); }
    ~AutoRef() { if (mp) mp->Release(); }
    AutoRef& operator=(T* p) {
        if (p != mp) { if (p) p->AddRef(); T* old = mp; mp = p; if (old) old->Release(); }
        return *this;
    }
};
struct RbNode {
    RbNode* mpRight; RbNode* mpLeft; RbNode* mpParent; int color;
    unsigned key;            // +0x10
    void* body;              // +0x14  (value.first)
};
struct VertVal { void* body; void* pad4; void* constraint; void* pad12; };
struct VIter { RbNode* node; };
RbNode* RBTreeIncrement(RbNode* n);                  // 0x00921580 (cdecl)
void RBTreeErase(RbNode* n, RbNode* anchor);         // 0x00921880 (cdecl)
struct VMap {                       // eastl::map<unsigned, VertVal> at spine+0xcc
    int pad0;
    RbNode* anchorRight;            // +0xd0 anchor node base
    RbNode* anchorLeft;
    RbNode* root;                   // +0xd8
    char color;
    unsigned size;                  // +0xe0
    VertVal* Index(const unsigned* k);                   // 0x00632e90 map::operator[]
    VIter* Find(VIter* out, const unsigned* k);          // 0x00e5c780 rbtree::find
    void DoNukeSubtree(RbNode* n);                       // 0x009a9600
    ~VMap() { DoNukeSubtree(root); }
    __forceinline void Clear() {
        RbNode* p = root;
        RbNode* nxt = 0;
        while (p) {
            DoNukeSubtree(p->mpRight);
            nxt = p->mpLeft;
            operator_delete__(p);
            p = nxt;
        }
        RbNode* anchor = Anchor();
        anchorRight = anchor;
        anchorLeft = anchor;
        root = nxt;
        color = 0;
        size = 0;
    }
    RbNode* Anchor() { return (RbNode*)&anchorRight; }
    __forceinline RbNode* LowerFind(unsigned key) {
        RbNode* cur = root;
        RbNode* best = Anchor();
        while (cur) {
            if (!(cur->key < key)) { best = cur; cur = cur->mpLeft; }
            else cur = cur->mpRight;
        }
        if (best != Anchor() && !(key < best->key)) return best;
        return Anchor();
    }
};
class hkMotion_s005d_27e0 { public: float getMass(); };                // 0x01088270 hkRigidMotion::getMass
struct hkBody { char pad[0x58]; hkMotion_s005d_27e0* motion; };
struct ModelT { char pad[0x58]; float f58; };     // cMWModel: +0x58 packs mHighlightType/mCustomPickLevel/+0x5a
struct Cookie {                                    // object at block+0x28 (editor model owner)
    float F4adaa0(int a, int b, int c);            // 0x004adaa0 (fastcall; returns +0x38)
    struct PhysW* F4ad450();                       // 0x004ad450 (fastcall; returns +0x30)
    void F4abaf0(struct BlockT* b, int v);         // 0x004abaf0
};
struct BlockT : RefObj {
    char pad4[0x10 - 4];
    ModelT* model;               // +0x10
    char pad14[0x28 - 0x14];
    Cookie* cookie;              // +0x28
    char pad2c[0x48 - 0x2c];
    float px, py, pz;            // +0x48
    char pad54[0x60 - 0x54];
    float m[9];                  // +0x60 3x3 rotation, rows
    char pad84[0x1d8 - 0x84];
    float scale;                 // +0x1d8
    char pad1dc[4];
    float minScale, maxScale;    // +0x1e0 +0x1e4
    char pad1e8[0x33c - 0x1e8];
    BlockT* nextVertebra;        // +0x33c
    char children[4];            // +0x340 (source container for FixedVec8::Fill)
    char pad3[0xdc8 - 0x344];
    unsigned flags;              // +0xdc8
    BlockT();                                           // 0x004346b0
    void FUN_00438700(BlockT* o);                       // 0x00438700
    void BuildBlock(void* a, unsigned b, void* c, void* world, float x, int d, int e, int f);   // 0x00441440
    void FUN_00448e90(float* pos, int v);               // 0x00448e90
    void FUN_00449420(float* rot, int v);               // 0x00449420
    void FUN_00440090(float s, int v);                  // 0x00440090
    void FUN_00440020(float s, int v);                  // 0x00440020
};
struct FixedVec8 {
    BlockT** mpBegin; BlockT** mpEnd; BlockT** mpCap;
    unsigned pad[2];
    unsigned overflowFlag;
    BlockT* buf[8];
    FixedVec8() : mpBegin(buf), overflowFlag(0), mpEnd(buf), mpCap(buf + 8) {}
    ~FixedVec8() {
        BlockT** e = mpEnd;
        for (BlockT** p = mpBegin; p < e; p++)
            if (*p) (*p)->Release();
        if (mpBegin && mpBegin[-1]) operator_delete__(mpBegin);
    }
    void Fill(void* src);                       // 0x00453f20
};
struct Ob {
    void FUN_0048a4c0();
    void FUN_005d59c0();
    void FUN_00438700(BlockT* b);
    void FUN_004acab0(BlockT* b, int v);
};
class hkTransform_s005d_27e0 { public: float rot[3][4]; float pos[4]; };
struct Mat3 { float m[9]; };
void FUN_004a92c0(Mat3* rot, hkTransform_s005d_27e0* xf);   // 0x004a92c0 (cdecl)
void FUN_005cd670(hkTransform_s005d_27e0* xf, int axis);    // 0x005cd670 (cdecl)
struct PhysW { void* World(); };                    // 0x004b91c0 (fastcall; returns +8)
struct hkMem { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
               virtual void* Alloc(int size, int type); };      // vtbl+0x10
extern hkMem* g_hkMemory_s005d_27e0;                           // 0x016e4178
struct CdPoint { char pad[0x1c]; float dist; struct Coll* a; unsigned pad24; struct Coll* b; unsigned pad2c; };
struct Coll { void* timeObj; char pad[0x1c - 4]; unsigned flags; };
struct PointCollector {                             // hkCdPointCollector over a fixed hkArray (8 inline points)
    void* vt; float earlyOut; unsigned pad8, padc;
    CdPoint* data; int size; unsigned capFlags; unsigned pad1c;
    CdPoint buf[8];
};
class hkSimpleShapePhantom : public HkRef { public:
    hkSimpleShapePhantom(HkRef* shape, const hkTransform_s005d_27e0* xf, unsigned key);   // 0x0108c750
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual void getClosestPoints(PointCollector* c);       // vtbl+0x34
};
float TimeObjValue(void* t);                        // 0x005cd910 (cdecl)
struct Spine {
    void* vt0;                   // +0x00
    int refCount;                // +0x04
    void* vt8;                   // +0x08
    float f0c, f10;              // +0x0c +0x10
    HkWorld* world;              // +0x14
    HandleObj* p18;              // +0x18
    HkRef* hk1c;                 // +0x1c hkWorldObject
    char pad20[0x3c - 0x20];
    HkRef* action;               // +0x3c
    char pad40[0x4c - 0x40];
    float maxBlockScale;         // +0x4c
    char pad50[0xc5 - 0x50];
    char dirty;                  // +0xc5
    char padc6[0xcc - 0xc6];
    VMap vertebrae;              // +0xcc
    char padE4[0xe8 - 0xe4];
    AutoRef<RefObj> firstVertebra;   // +0xe8
    AutoRef<RefObj> lastVertebra;    // +0xec
    void* pF0;                       // +0xf0
    AutoRef<HandleObj> firstHandle;  // +0xf4
    AutoRef<HandleObj> lastHandle;   // +0xf8
    void* pFC;                       // +0xfc
    unsigned u100;
    unsigned inst104;                // +0x104 (model key instance)
    unsigned* vecBegin;          // +0x108
    unsigned* vecEnd;            // +0x10c
    char pad110[0x11c - 0x110];
    float halfWidth;             // +0x11c
    Ob* route1;                  // +0x120
    Ob* route2;                  // +0x124

    void FUN_005d14a0();
    void FUN_005d1e70();
    void FUN_005d1f30();
    void FUN_005d2740(unsigned k);
    BlockT* FUN_005d27e0(BlockT* src, float* dir, float* rot);
    HkRef* CreateVertebraShape(float scale);            // 0x005cd9a0
    unsigned MakeVertKey(float scale, int idx);         // 0x005cdb30
    void FUN_005ce060(VertVal* out, float scale, class hkTransform_s005d_27e0* xf);   // 0x005ce060
    void FUN_005d2790();
    bool FUN_005d3010(unsigned key, int, int, int, int, int, int);
    float FUN_005d3100();
    void FUN_005d31b0();
    void FUN_005d3300(BlockT* b);
    void FUN_005d35c0();
};
// ---- items of slice s005d27e0 end

// ---- items of slice s005d36e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_WallThickness;  // @ 0x015180c8
extern float g_WallDepth;      // @ 0x015ee448
class hkMemory_s005d_36e0 { public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
  virtual void* allocate(int size, int type);  // vtbl +0x10
};
extern hkMemory_s005d_36e0* g_hkMemory_s005d_36e0;  // @ 0x016e4178
__declspec(align(16)) struct hkVector4 { float x, y, z, w; };
class hkTransform_s005d_36e0 { public: float rot[12]; float trans[4]; };
class hkReferencedObject_s005d_36e0 { public:
  virtual void deleteThis(int);
  uint16_t memSizeAndFlags;  // +4
  uint16_t referenceCount;   // +6
  void removeReference() {
    if (memSizeAndFlags != 0) {
      referenceCount--;
      if (referenceCount == 0) deleteThis(1);
    }
  }
};
class hkMouseSpringAction_s005d_36e0 : public hkReferencedObject_s005d_36e0 { public:
  uint32_t pad[0x12];
  hkMouseSpringAction_s005d_36e0* Construct(const hkVector4& posInRb, const hkVector4& mousePos, float damping,
                                 float elasticity, float maxForce, class hkRigidBody_s005d_36e0* rb);  // @ 0x011278b0
  void setMaxRelativeForce(float f);  // @ 0x00c87bc0 (ICF'd as SetMaxCargoAmount)
};
class hkRigidMotion_s005d_36e0 { public:
  uint32_t pad[0x10];
  float pos[4];  // +0x40
  float getMass() const;  // @ 0x01088270
};
class hkRigidBody_s005d_36e0 { public:
  uint32_t pad[0x16];
  hkRigidMotion_s005d_36e0* motion;  // +0x58
  void setMotionType(int type, int a, int b);  // @ 0x01087520
  void addCollisionListener(void* l);          // @ 0x01088c90
  void removeReference();                      // @ 0x0109ae60
};
class hkWorld_s005d_36e0 { public:
  void removeAction(hkMouseSpringAction_s005d_36e0* a);  // @ 0x01086f40
  void addAction(hkMouseSpringAction_s005d_36e0* a);     // @ 0x01085e60
  hkRigidBody_s005d_36e0* addEntity(hkRigidBody_s005d_36e0* e, int a);  // @ 0x01082ee0
};
#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
struct cSPEditorBlock {
  virtual void* Dtor(int);  // +0
  virtual void AddRef();    // +4
  virtual void Release();   // +8
  uint32_t pad0[0x11];
  float pos[3];  // +0x48
  uint32_t pad1[3];
  float xform[4];  // +0x60
  uint32_t pad2[0x5a];
  float scale;  // +0x1d8
  uint32_t pad3;
  float defaultOrient[2];  // +0x1e0
  cSPEditorBlock();  // @ 0x004346b0
  bool BuildBlock(uint32_t instance, uint32_t group, void* pWorld, void* pParent, float field30,
                  bool a, bool b, bool c);  // @ 0x00441440, ret 0x20
  void Shutdown2();                          // @ 0x00451400
  void SetPosition(const float* v, int flag);  // @ 0x00448e90
  void LinkNext(cSPEditorBlock* o);           // @ 0x00438700
};
struct cSPEditorHandleSpine {
  virtual void AddRef();   // +0
  virtual void Release();  // +4
  cSPEditorHandleSpine();  // @ 0x005a8ad0
  void Init(cSPEditorBlock* blk, const float* offset, const float* basis);  // @ 0x005a8970, ret 0xc
};
void* operator new(unsigned int, const char*, int, int, int, int);  // @ 0x00f473a0
struct Tuning { uint32_t pad[7]; float f1c; };
Tuning* EditorTuning();  // @ 0x00401070
struct VNodeBase { VNodeBase* right; VNodeBase* left; VNodeBase* parent; uint32_t color; };
struct VNode : VNodeBase { cSPEditorBlock* key; hkRigidBody_s005d_36e0* body; uint32_t pad[3]; };
struct VInfo { hkRigidBody_s005d_36e0* body; uint32_t a, b, c; };
struct VIter_s005d_36e0 {
  VNodeBase* node;
  VIter_s005d_36e0() {}
  VIter_s005d_36e0(const VIter_s005d_36e0& o) : node(o.node) {}
};
struct VMap_s005d_36e0 {
  uint32_t cmp;
  VNodeBase anchor;  // +4 (this+0xd0 in the spine)
  uint32_t size, alloc;
  VIter_s005d_36e0 find(cSPEditorBlock* const& key);       // @ 0x00e5c780
  VInfo* subscript(cSPEditorBlock* const& key);  // @ 0x00632e90
};
void* RBTreeIncrement(void* n);  // @ 0x00921580
struct cBlockList {
  uint32_t Count();                    // @ 0x004accf0
  cSPEditorBlock* At(uint32_t i);      // @ 0x004accb0
};
cSPEditorBlock* NextBlock(cSPEditorBlock* b);  // @ 0x004a5970 (cdecl)
void FUN_004a92c0(float* a, hkTransform_s005d_36e0* t);
void FUN_005cd670(hkTransform_s005d_36e0* t, int);
struct cPhysWorldHolder { hkWorld_s005d_36e0* World(); };  // @ 0x004b91c0
struct cEditorCtx {
  void FUN_004ad280();
  float FUN_004adaa0();
  float FUN_004adb00();
  float FUN_004adb40();
  cPhysWorldHolder* FUN_004ad450();
  void FUN_004abaf0(cSPEditorBlock* b, int flag);
};
extern Mat3 g_BasisMat;  // @ 0x015ee4dc
struct cSPEditorSpine {
  uint32_t pad0[5];
  hkWorld_s005d_36e0* world;                // +0x14
  void* listener;                // +0x18
  uint32_t pad0b;
  float wallX0, wallZ0, wallX1, wallZ1;  // +0x20..0x2c
  bool wallsCreated;             // +0x30
  uint8_t pad0c[3];
  uint32_t pad1[2];
  hkMouseSpringAction_s005d_36e0* spring;   // +0x3c
  float f40, f44;                // +0x40, +0x44
  uint32_t pad2[0x1a];
  float springDamping;           // +0xb0
  float springElasticity;        // +0xb4
  float springMaxForce;          // +0xb8
  uint32_t pad3[2];
  uint8_t pad4[1];
  bool simulating;               // +0xc5
  uint8_t pad5[2];
  uint32_t pad6;
  VMap_s005d_36e0 vertebrae;                // +0xcc
  cSPEditorBlock* firstBlock;    // +0xe8
  cSPEditorBlock* lastBlock;     // +0xec
  cSPEditorBlock* sceneBlock;    // +0xf0
  cSPEditorHandleSpine* firstHandle;  // +0xf4
  cSPEditorHandleSpine* lastHandle;   // +0xf8
  uint32_t keyInstance;          // +0xfc
  uint32_t keyType;              // +0x100
  uint32_t keyGroup;             // +0x104
  uint32_t pad8[5];
  float vertebraHalfWidth;       // +0x11c

  void FUN_005d1530();
  void FUN_005d25c0(cSPEditorBlock* b);
  float FUN_005d3100();
  void FUN_005d31b0();
  void FUN_005d2790();
  hkRigidBody_s005d_36e0* CreateVertebraBody(float scale, hkTransform_s005d_36e0* t);  // @ 0x005cdd00

  __forceinline void BuildHandles() {
    Tuning* tuning = EditorTuning();
    cSPEditorHandleSpine* h = new ("Editor", 0, 0, 0, 0) cSPEditorHandleSpine;
    cSPEditorHandleSpine* old = firstHandle;
    if (h != old) {
      if (h) h->AddRef();
      firstHandle = h;
      if (old) old->Release();
    }
    float V[3];
    V[0] = 0.0f; V[1] = -tuning->f1c; V[2] = 0.0f;
    firstHandle->Init(firstBlock, V, g_BasisMat.m);
    Mat3 M = g_BasisMat;
    M.m[4] = -1.0f;
    M.m[8] = -1.0f;
    h = new ("Editor", 0, 0, 0, 0) cSPEditorHandleSpine;
    old = lastHandle;
    if (h != old) {
      if (h) h->AddRef();
      lastHandle = h;
      if (old) old->Release();
    }
    V[0] = 0.0f; V[1] = tuning->f1c; V[2] = 0.0f;
    lastHandle->Init(lastBlock, V, M.m);
  }

  bool FUN_005d43d0(cSPEditorBlock** pBlock, float a, float b, float c, float d, float e, float f);
  void FUN_005d3f10(cBlockList* blocks, cSPEditorBlock* sceneBlk);
  void FUN_005d36e0(struct cEditorCtx* ctx, cSPEditorBlock* sceneWorld, uint32_t n);
  void CreateWallBoxAndAddToWorld(const float* halfExt, const float* pos, hkWorld_s005d_36e0* w);  // @ 0x005cdbf0
  void FUN_005d1e70();
  void FUN_005d2480(cSPEditorBlock* b);
  void FUN_005d1f30();
};
// ---- items of slice s005d36e0 end

// ---- items of slice s005d4630 begin (TODO(rewrite): local stubs, replace by canonical classes)
__forceinline float ClampFloat(float v, float lo, float hi) {
  __m128 t = _mm_load_ss(&v);
  t = _mm_max_ss(t, _mm_load_ss(&lo));
  t = _mm_min_ss(t, _mm_load_ss(&hi));
  return _mm_cvtss_f32(t);
}
struct E20_s005d_4630 {
  int a;
  int b;
  float c;
  float d;
  int e;
  E20_s005d_4630() {}
  E20_s005d_4630(const E20_s005d_4630& o) : a(o.a), b(o.b), c(o.c), d(o.d), e(o.e) {}
};
struct PathSegment {
  virtual float Length();                     // vtable slot 0
  virtual void  Eval(float* out, float t);    // vtable slot 1
};
struct PathCurve {
  PathSegment** mpBegin;     // +0x00
  PathSegment** mpEnd;       // +0x04
  PathSegment** mpCapacity;  // +0x08
  char pad0c[8];
  float mTotalLength;        // +0x14

  float* Walk(float* out, float t);
};
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);   // 0x00F473A0
void operator delete(void* p);                                                                                           // 0x00F47380
namespace SPB {
struct Vec2_s005d_4630 { float x, y; };
}
namespace SPB {
template <class T> struct sp_vector {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  uint32_t mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  sp_vector(const sp_vector& o);                                  // out of line (0x005D1240 for E20)
  sp_vector& operator=(const sp_vector& o);                       // out of line (0x005D12C0 for E20)
  ~sp_vector() {
    if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0) operator delete(mpBegin);
  }
};
}
namespace SPB {
struct Circle_s005d_4630 {          // 0x24 bytes
  uint32_t id;
  float x, y, r;
  sp_vector<E20_s005d_4630> arcs;   // +0x10
  Circle_s005d_4630(int idx, struct SpineNode_s005d_4630* n);                       // 0x005D57D0 (thiscall, ret 8)
  Circle_s005d_4630(const Circle_s005d_4630& o) : id(o.id), x(o.x), y(o.y), r(o.r), arcs(o.arcs) {}
  // The retail copy-assignment moves the 4-dword trivial prefix with integer moves (bitwise) and
  // only then runs sp_vector::operator= for the trailing container.
  Circle_s005d_4630& operator=(const Circle_s005d_4630& o)
  {
    *(uint32_t*)&id = *(const uint32_t*)&o.id;
    *(uint32_t*)&x  = *(const uint32_t*)&o.x;
    *(uint32_t*)&y  = *(const uint32_t*)&o.y;
    *(uint32_t*)&r  = *(const uint32_t*)&o.r;
    arcs = o.arcs;
    return *this;
  }
  ~Circle_s005d_4630() {}
  void FUN_005d5be0(Circle_s005d_4630* other);                           // 0x005D5BE0 (thiscall, ret 4)
  void FUN_005d5cf0(Vec2_s005d_4630* p0, Vec2_s005d_4630* p1, Circle_s005d_4630* c);           // 0x005D5CF0 (thiscall, ret 0xc)
  void FUN_005d5b60(Vec2_s005d_4630* p, int a, int b);                   // 0x005D5B60 (thiscall, ret 0xc)
};
}
namespace SPB {
struct CircleVec_s005d_4630 {
  Circle_s005d_4630* mpBegin;
  Circle_s005d_4630* mpEnd;
  Circle_s005d_4630* mpCapacity;
  CircleVec_s005d_4630() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~CircleVec_s005d_4630() {
    destruct(mpBegin, mpEnd);
    if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0) operator delete(mpBegin);
  }
  void DoInsertValue(Circle_s005d_4630* pos, const Circle_s005d_4630& v);           // 0x005D47C0 (thiscall, ret 8)
  static void destruct(Circle_s005d_4630* first, Circle_s005d_4630* last) {
    for (; first < last; ++first) first->~Circle_s005d_4630();
  }
  void push_back(const Circle_s005d_4630& v) {
    if (mpEnd < mpCapacity) {
      Circle_s005d_4630* p = mpEnd++;
      if (p) new ((void*)p) Circle_s005d_4630(v);
    } else
      DoInsertValue(mpEnd, v);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
};
}
namespace SPB {
Circle_s005d_4630* UninitCopyCircle(Circle_s005d_4630* first, Circle_s005d_4630* last, Circle_s005d_4630* dest);      // 0x005D13F0
}
namespace SPB {
void    DestroyCircleRange(Circle_s005d_4630* first, Circle_s005d_4630* last, Circle_s005d_4630* dest);    // 0x005CF7F0
}
namespace SPB {
Circle_s005d_4630* CopyBackwardCircle(Circle_s005d_4630* first, Circle_s005d_4630* last, Circle_s005d_4630* destEnd); // 0x005D1450
}
namespace SPB {
struct PathObj {         // 0x18 bytes, allocated with the EA "Editor" allocator
  PathObj();             // 0x005D57B0
  ~PathObj();            // 0x005D59C0
};
}
namespace SPB {
struct SpineNode_s005d_4630 {
  char pad0[0x64];
  float m64, m68, m6c;
  float m70, m74, m78;
  float m7c, m80;
  char pad84[0xdc0 - 0x84];
  uint32_t param0, param1;   // +0xdc0, +0xdc4
};
}
namespace SPB {
SpineNode_s005d_4630* NextNode(SpineNode_s005d_4630* n);   // 0x004A5970 (cdecl)
}
namespace SPB {
extern float gDirX;   // 0x01517F44
}
namespace SPB {
extern float gDirY;   // 0x01517F48
}
namespace SPB {
extern float gDirZ;   // 0x01517F4C
}
namespace SPB {
struct HkVector4 { float x, y, z, w; };
}
namespace SPB {
struct HkMotion { float getMass(); };                 // 0x01088270 hkRigidMotion::getMass
}
namespace SPB {
struct HkBody { char pad0[0x58]; HkMotion* motion; };  // hkRigidBody: motion at +0x58
}
namespace SPB {
struct MouseSpring {                                   // hkMouseSpringAction (refcounted)
  virtual void* Destroy(int flags);                    // +0
  uint16_t memSize;                                    // +4
  short refCount;                                      // +6
  char pad8[0x30 - 8];
  HkVector4 mMouse;                                    // +0x30 target point of the spring
  char pad40[0x48 - 0x40];
  void setMaxRelativeForce(float f);                   // 0x00C87BC0 (writes +0x48)
};
}
namespace SPB {
struct RbNode_s005d_4630 {
  RbNode_s005d_4630* mpRight;    // +0
  RbNode_s005d_4630* mpLeft;     // +4
  RbNode_s005d_4630* mpParent;   // +8
  int color;          // +0xc
  unsigned key;       // +0x10
  void* body;         // +0x14
};
}
namespace SPB {
struct VIter_s005d_4630 { RbNode_s005d_4630* node; };
}
namespace SPB {
struct VInfo_s005d_4630 { void* body; uint32_t a, b, c; };
}
namespace SPB {
struct VMap_s005d_4630 {                    // eastl::map at spine+0xcc (anchor node base at +4)
  int pad0;
  RbNode_s005d_4630* anchorRight;           // +0xcc+4
  RbNode_s005d_4630* anchorLeft;
  RbNode_s005d_4630* root;
  char color;
  unsigned size;
  VIter_s005d_4630* Find(VIter_s005d_4630* out, const unsigned* k);   // 0x00E5C780  rbtree find, returns `out`
  VInfo_s005d_4630* Index(const unsigned* k);              // 0x00632E90  map subscript
  RbNode_s005d_4630* Anchor() { return (RbNode_s005d_4630*)&anchorRight; }
};
}
namespace SPB {
struct SpineHandle_s005d_4630 {
  char pad0[0x20];
  float wallX0;          // +0x20  min X of the editor wall box
  float wallZ0;          // +0x24  max Z
  float wallX1;          // +0x28  max X
  float wallZ1;          // +0x2c  min Z
  char pad30[0x3c - 0x30];
  MouseSpring* action;   // +0x3c  the mouse spring action currently dragging a vertebra
  char pad40[0xb8 - 0x40];
  float springMaxForce;  // +0xb8
  char padbc[0xcc - 0xbc];
  VMap_s005d_4630 vertebrae;        // +0xcc
  char padE4[0xe8 - 0xe4];
  SpineNode_s005d_4630* n1;         // +0xe8
  SpineNode_s005d_4630* n2;         // +0xec
  char pad1[0x120 - 0xf0];
  PathObj* c1;           // +0x120
  PathObj* c2;           // +0x124

  bool FUN_005d4970();
  bool Drag(SpineNode_s005d_4630** pBlock, float a, float b, float c, float d, float e, float f);          // 0x005D4630
  float Mass();                                                                                  // 0x005D3100
  uint32_t* NearestParam(Vec2_s005d_4630* res, SpineNode_s005d_4630* o);                                              // 0x005CF110 (thiscall, ret 8)
  bool WalkBelt(PathObj* out, CircleVec_s005d_4630* v, int idx, float px, float py, unsigned flag);        // 0x005CE9B0 (thiscall, ret 0x18; this unused)
};
}
namespace SPB {
char FindEnd(CircleVec_s005d_4630* v, Vec2_s005d_4630* dir, Circle_s005d_4630* from, char flag, Vec2_s005d_4630* out, uint32_t* idx);       // 0x005CE7B0 (cdecl)
}
// ---- items of slice s005d4630 end

// ---- items of slice s005d53e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744
extern float kTwoPi;  // 0x015ee798
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags, const char* file,
                     int line);
struct Vector2 {
  float x, y;
  Vector2() {}
  Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};
struct Point2 {
  float x, y;
};
namespace eastl {
template <typename T>
inline const T& min(const T& a, const T& b) {
  return (b < a) ? b : a;
}
}
namespace eastl {
template <typename T>
inline const T& max(const T& a, const T& b) {
  return (a < b) ? b : a;
}
}
namespace eastl {
template <typename T>
class sp_vector_s005d_53e0 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
  void DoInsertValue(T* position, const T& value);
  void push_back(const T& value);
  void push_back_inline(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}
class cPathShape;
struct PathIntersection {
  PathIntersection() {}
  PathIntersection(cPathShape* shape, cPathShape* other, const Vector2& position, int flags)
      : mpShape(shape), mpOther(other), mFlags(flags) {
    mPosition = position;
  }
  cPathShape* mpShape;   // +0x0
  cPathShape* mpOther;   // +0x4
  Vector2 mPosition;     // +0x8
  int mFlags;            // +0x10
};
int CircleLineIntersection(Vector2 p1, Vector2 p2, Vector2 center, float radius, float* result);  // below
struct Circle_s005d_53e0 {
  Vector2 mCenter;
  float mRadius;
  int Intersect(const Circle_s005d_53e0& other, Vector2* points);  // 0x005d5250
};
struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
Vector3 GetPosition(const void* desc);  // 0x004a5d10
float GetRadius(const void* desc);    // 0x004a5bd0
class cPathShape {
 public:
  cPathShape(int type, const void* desc);
  float FindNextIntersection(const Vector2& point, bool clockwise, PathIntersection** result);
  void AddIntersection(const Vector2& position, int flags, cPathShape* other);
  void IntersectWith(cPathShape* other);
  void IntersectLine(const Vector2& p1, const Vector2& p2, cPathShape* other);

  int mType;                                       // +0x0
  Circle_s005d_53e0 mCircle;                                  // +0x4
  eastl::sp_vector_s005d_53e0<PathIntersection> mIntersections;  // +0x10
};
class cPathSegment {
 public:
  virtual float GetLength();
};
class cArcSegment : public cPathSegment {
 public:
  cArcSegment(const Point2& center, float sweep, const Point2& start, float radius)
      : mCenter(center), mStart(start), mRadius(radius), mSweep(sweep) {}
  virtual float GetLength();
  Point2 mCenter;  // +0x4
  Point2 mStart;   // +0xc
  float mRadius;    // +0x14
  float mSweep;     // +0x18
};
class cLineSegment : public cPathSegment {
 public:
  cLineSegment(const Point2& start, const Point2& end) : mStart(start), mEnd(end) {}
  virtual float GetLength();
  Point2 mStart;  // +0x4
  Point2 mEnd;    // +0xc
};
class cPathSegmentList {
 public:
  cPathSegmentList();
  ~cPathSegmentList();
  void AddArc(const Point2& center, float sweep, const Point2& start, float radius);
  void AddLine(const Point2& start, const Point2& end);

  eastl::sp_vector_s005d_53e0<cPathSegment*> mSegments;  // +0x0
  float mLength;                              // +0x14
};
// ---- items of slice s005d53e0 end

// @ 0x005cd670
void SpineBigStub(void* a, void* b, void* c)
{
  (void)a;
  (void)b;
  (void)c;
}

// @ 0x005cd870
void cInterp::Interp(float a, float b, float* out1, float* out2)
{
  float t = ((a + b) * 0.5f) / mFloat98;
  t = Clamp(t, 0.0f, 1.0f);
  t = (mFloat94 - mFloat90) * (1.0f - t) + mFloat90;
  *out1 = mFloat88 * t;
  *out2 = mFloat8c * t;
}

// @ 0x005cd910
float TimeObjValue(cTimeObj* obj)
{
  if (obj->GetType() != 0xe)
    return 0.0f;
  cTimeObj* child = obj->mChild;
  if (child->GetType() != 8)
    return 0.0f;
  return child->mFloat0c;
}

// @ 0x005cd9a0
void CreateVertebraShapeStub(float r)
{
  (void)r;
}

// @ 0x005cdbb0
void cRefCounted::IncRef(int unused)
{
  (void)unused;
  mRef++;
}

// @ 0x005cdbc0
void cRefCounted::DecRef(int unused)
{
  (void)unused;
  mRef--;
}

// @ 0x005cdbf0
void CreateWallBoxStub(void* a, void* b)
{
  (void)a;
  (void)b;
}

// @ 0x005cdd00
hkRigidBody_s005c_dd00* SP::cSPEditorSpine_s005c_dd00::CreateVertebraBody(float scale, hkTransform_s005c_dd00* transform)
{
  (void)scale;
  (void)transform;
  return 0;
}

// @ 0x005ce060
int* SP::cSPEditorSpine_s005c_dd00::AddVertebraBody(int* out, float scale, hkTransform_s005c_dd00* transform)
{
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;
  out[3] = 0;
  out[0] = (int)CreateVertebraBody(scale, transform);
  mpWorld->addEntity((hkEntity_s005c_dd00*)out[0], 1);
  ((hkEntity_s005c_dd00*)out[0])->removeReference();
  ((hkEntity_s005c_dd00*)out[0])->addCollisionListener(mpCollisionListener);
  *(unsigned short*)((char*)out[0] + 0x96) = 0;
  return out;
}

// @ 0x005ce0c0
hkGenericConstraintData* CreateAxialConstraintData(int dof)
{
  void* mem = g_hkMemory->allocate(0x4c, 0x29);
  *(unsigned short*)((char*)mem + 4) = 0x4c;
  hkGenericConstraintData* data = new (mem) hkGenericConstraintData();
  hkConstraintConstructionKit kit;
  kit.begin(data);
  hkVector4_s005c_dd00 zeroA;
  zeroA.x = 0.0f; zeroA.y = 0.0f; zeroA.z = 0.0f; zeroA.w = 0.0f;
  kit.setPivotA(zeroA);
  hkVector4_s005c_dd00 zeroB;
  zeroB.x = 0.0f; zeroB.y = 0.0f; zeroB.z = 0.0f; zeroB.w = 0.0f;
  kit.setPivotB(zeroB);
  hkVector4_s005c_dd00 axisX;
  axisX.x = 1.0f; axisX.y = 0.0f; axisX.z = 0.0f; axisX.w = 0.0f;
  hkVector4_s005c_dd00 axisY;
  axisY.x = 0.0f; axisY.y = 1.0f; axisY.z = 0.0f; axisY.w = 0.0f;
  hkVector4_s005c_dd00 axisZ;
  axisZ.x = 0.0f; axisZ.y = 0.0f; axisZ.z = 1.0f; axisZ.w = 0.0f;
  kit.setLinearDofWorld(axisX, 0);
  kit.setLinearDofWorld(axisY, 1);
  kit.setLinearDofWorld(axisZ, 2);
  kit.constrainLinearDof(dof);
  kit.setAngularBasisABodyFrame();
  kit.setAngularBasisBBodyFrame();
  kit.constrainToAngularDof(dof);
  kit.end();
  return data;
}

// @ 0x005ce210
void SP::cSpineHelper::SetEnabled(int enabled)
{
  if (mFieldF4 != 0 && mFieldF8 != 0) {
    mFieldF4->SetEnabled(enabled);
    mFieldF8->SetEnabled(enabled);
  }
}

// @ 0x005ce250
void SP::cSpineHelper::ReleaseE8()
{
  void* block = *(void* volatile*)&mFieldE8;
  ::FUN_004a5970(block);
  _ReadWriteBarrier();
}

// @ 0x005ce270
void* SP::cSpineHelper::GetHandle(int id)
{
  if ((int)mFieldE8 == id)
    return mFieldF4;
  if ((int)mFieldEC == id)
    return mFieldF8;
  return 0;
}

// @ 0x005ce2a0
void NormalizeVector2(float* out, const float* in)
{
  float x = in[0];
  float len = sqrtf(x * x + in[1] * in[1] + 1e-8f);
  volatile float scale = 1.0f / len;
  out[1] = in[1] * scale;
  out[0] = x * scale;
}

// @ 0x005ce300
void SP::cSPEditorSpine::LoadDynamicTuning()
{}

// Layout of the vertebra shape buffer passed in as `shape` by the caller.
struct cVertebraShape {
  unsigned char mFlags;   // +0x00
  unsigned char mPad[3];  // +0x01
  float mCenterX;         // +0x04
  float mCenterY;         // +0x08
  float mCenterZ;         // +0x0c
  float mScale;           // +0x10
  float mRow0X;           // +0x14
  float mRow0Y;           // +0x18
  float mRow0Z;           // +0x1c
  float mRow1X;           // +0x20
  float mRow1Y;           // +0x24
  float mRow1Z;           // +0x28
  float mRow2X;           // +0x2c
  float mRow2Y;           // +0x30
  float mRow2Z;           // +0x34
};

// @ 0x005ce680
void SP::cSPEditorSpine_s005c_dd00::CalcVertebraPhysicsBoundingBox(float scale, unsigned char* shape, float* out)
{
  cVertebraShape* vs = (cVertebraShape*)shape;
  __declspec(align(16)) float offset = SP::EditorUtils::GetExactSkinRadiusFromVertebra(scale) +
                 (mVertebraHalfWidth + mVertebraHalfWidth) * mSpineVertebraMaxMassProportion * 0.25f;
  float dx = scale * -0.15993178f;
  float x = 0.0f;
  float y = 0.0f;
  float z = dx;
  if (vs->mFlags & 2) {
    x = (vs->mRow1X + vs->mRow0X) * 0.0f + vs->mRow2X * dx;
    y = (vs->mRow1Y + vs->mRow0Y) * 0.0f + vs->mRow2Y * dx;
    z = (vs->mRow1Z + vs->mRow0Z) * 0.0f + vs->mRow2Z * dx;
  }
  float m01 = vs->mScale;
  float cx = vs->mCenterX + m01 * x;
  float cy = vs->mCenterY + m01 * y;
  float cz = vs->mCenterZ + m01 * z;
  out[0] = cx - offset;
  out[1] = cy - offset;
  out[2] = cz - offset;
  out[3] = cx + offset;
  out[4] = cy + offset;
  out[5] = cz + offset;
}

// @ 0x005ce7b0
int FUN_005ce7b0(void*, float*, int, char, float*, void*)
{ return 0; }

// @ 0x005ce9b0
int __stdcall FUN_005ce9b0(SP::OutPath* out, SP::CircleVec* v, int idx, float px, float py, unsigned flag)
{
  SP::Circle* cur = v->begin + idx;
  SP::Vec2 pt;
  pt.x = px;
  pt.y = py;
  uint32_t id = cur->id;
  SP::Hit* hit;
  float ang = cur->FindHit(&pt, flag, &hit);
  int kind = hit->kind;
  for (;;) {
    if (kind == 2) {
      SP::Vec2 c;
      c.x = cur->x;
      c.y = cur->y;
      out->Arc(&c, cur->r, &pt, ang);
      return 1;
    }
    SP::Circle* next = 0;
    if (kind == 0) {
      next = hit->a;
      if (next->id == id) next = hit->b;
      SP::Vec2 c;
      c.x = cur->x;
      c.y = cur->y;
      out->Arc(&c, cur->r, &pt, ang);
      pt.x = hit->x;
      pt.y = hit->y;
    } else if (kind == 1) {
      uint32_t j = hit->b->id;
      SP::Circle* c2 = v->begin + j;
      float dx, dy;
      do {
        next = c2;
        if (j >= (uint32_t)(v->end - v->begin)) return 0;
        dx = next->x - cur->x;
        dy = next->y - cur->y;
        float dist2 = dx * dx + dy * dy;
        ++j;
        c2 = next + 1;
        if (!(cur->r > sqrtf(dist2))) break;
      } while (true);
      float r2 = next->r;
      float r1 = cur->r;
      float dist = sqrtf(dx * dx + dy * dy);
      float a = acosf(fabsf(r2 - r1) / dist);
      if (r1 < r2) a = 3.14159265f - a;
      if ((char)flag == 0) a = -a;
      float cs = cosf(a), sn = sinf(a);
      float ry = dx * sn + dy * cs;
      float rx = dx * cs - dy * sn;
      float inv = 1.0f / sqrtf(ry * ry + rx * rx + 1e-8f);
      rx = inv * rx;
      ry = inv * ry;
      SP::Vec2 q, q2;
      q.x = cur->x + rx * r1;
      q.y = cur->y + ry * r1;
      q2.x = next->x + rx * next->r;
      q2.y = next->y + ry * next->r;
      float ex = pt.x - cur->x, ey = pt.y - cur->y;
      float inv2 = 1.0f / sqrtf(ex * ex + ey * ey + 1e-8f);
      float nx = inv2 * ex, ny = inv2 * ey;
      SP::Vec2 cc;
      cc.x = cur->x;
      cc.y = cur->y;
      char c = FUN_005d4ff0(&cc, &pt, &q);
      if ((char)flag == 0) c = (c == 0);
      if (c) {
        float a2 = acosf(nx * rx + ny * ry);
        if ((char)flag == 0) a2 = -a2;
        SP::Vec2 c3;
        c3.x = cur->x;
        c3.y = cur->y;
        out->Arc(&c3, cur->r, &pt, a2);
      } else {
        q.x = pt.x;
        q.y = pt.y;
      }
      float bx = q2.x - q.x, by = q2.y - q.y;
      float best = sqrtf(bx * bx + by * by);
      SP::Vec2 bp = q2;
      for (uint32_t k = 0; k < (uint32_t)(v->end - v->begin); ++k) {
        if (k != cur->id) {
          SP::Circle* o = v->begin + k;
          SP::V3 oc;
          oc.x = o->x;
          oc.y = o->y;
          oc.z = o->r;
          float res[4];
          if (FUN_005d5630(q, q2, oc, res) == 2) {
            float vx = res[0] - q.x, vy = res[1] - q.y;
            if (vy * by + vx * bx > -1.5258789e-05f) {
              float l = sqrtf(vx * vx + vy * vy);
              if (l > 1.5258789e-05f && best > l) {
                bp.x = res[0];
                bp.y = res[1];
                best = l;
                next = o;
              }
            }
            vx = res[2] - q.x;
            vy = res[3] - q.y;
            if (vy * by + vx * bx > -1.5258789e-05f) {
              float l = sqrtf(vx * vx + vy * vy);
              if (l > 1.5258789e-05f && best > l) {
                bp.x = res[2];
                bp.y = res[3];
                best = l;
                next = o;
              }
            }
          }
        }
      }
      out->Join(&q, &bp);
      pt = bp;
    } else {
      // kind other than 0/1/2: nothing emitted, fall through to the loop guard
    }
    if ((int)(out->end - out->begin) > (int)(v->end - v->begin) * 4) return 0;
    cur = next;
    id = cur->id;
    ang = cur->FindHit(&pt, flag, &hit);
    kind = hit->kind;
  }
}

// @ 0x005cf110
SP::Vec2* SP::SpineHandle::NearestParam(Vec2* res, SpineNode* o)
{
  if (!c1 || !c2) return res;
  SP::Vec2 P;
  P.x = o->px;
  P.y = o->py;
  if ((o->flags >> 7) & 1) {
    float tmp[3];
    float* p = FUN_004a5d10(tmp, o);
    P.x = p[1];
    P.y = p[2];
  }
  float bestT = 0.0f, bestD = 1e6f;
  float t = 0.05f;
  SP::Vec2 A, B, Q;
  do {
    c1->Eval(&A, t);
    c2->Eval(&B, t);
    FUN_0069b650(&Q, &P, &A, &B);
    float d = sqrtf((Q.y - P.y) * (Q.y - P.y) + (Q.x - P.x) * (Q.x - P.x));
    if (d < bestD) {
      bestT = t;
      bestD = d;
    }
    t += 0.05f;
  } while (t < 0.99f);
  float a = bestT - 0.15f, z = 0.0f;
  float lo = MaxRef(a, z);
  float b = bestT + 0.15f, one = 1.0f;
  float hi = MinRef(b, one);
  float mid = (hi + lo) * 0.5f;
  for (;;) {
    c1->Eval(&A, mid);
    c2->Eval(&B, mid);
    FUN_0069b650(&Q, &P, &A, &B);
    float d = sqrtf((Q.y - P.y) * (Q.y - P.y) + (Q.x - P.x) * (Q.x - P.x));
    if (d <= 0.001f) break;
    if (FUN_005d4ff0(&P, &B, &A)) lo = mid;
    else hi = mid;
    if (hi - lo < 1e-5f) break;
    mid = (hi + lo) * 0.5f;
  }
  float bx = A.x - B.x, by = A.y - B.y;
  float qx = A.x - Q.x, qy = A.y - Q.y;
  res->x = (hi + lo) * 0.5f;
  res->y = sqrtf(qy * qy + qx * qx) / sqrtf(by * by + bx * bx);
  return res;
}

// @ 0x005cf4f0
void SP::SpineHandle::Extrude(Block* blk, float t, float s, int a4)
{
  SP::Vec2 A, B;
  c1->Eval(&A, t);
  c2->Eval(&B, t);
  float dx = B.x - A.x, dy = B.y - A.y;
  float qx = dx * s + A.x, qy = A.y + dy * s;
  float mx = dx * 0.5f + A.x, my = A.y + dy * 0.5f;
  if (s < 0.5f) {
    dy = -dy;
    dx = -dx;
  }
  float k = (float)fabs((double)(s - 0.5f));
  float ex = dx * k, ey = dy * k;
  float r1 = sqrtf(ex * ex + ey * ey);
  float hx = dx * 0.5f, hy = dy * 0.5f;
  float r = sqrtf(hx * hx + hy * hy);
  SP::V3 C;
  if (n1->param > t) {
    float tmp[3];
    float* p = FUN_004a5d10(tmp, n1);
    C = *(SP::V3*)p;
    r = FUN_004a5bd0(n1);
  } else if (t > n2->param) {
    float tmp[3];
    float* p = FUN_004a5d10(tmp, n2);
    C = *(SP::V3*)p;
    r = FUN_004a5bd0(n2);
  } else {
    C.x = 0.0f;
    C.y = mx;
    C.z = my;
  }
  float res;
  if (r1 < r - 1.5258789e-05f) res = sqrtf(r * r - r1 * r1);
  else res = 0.0f;
  float o = (float)blk->GetSymmetryIndex() * res;
  int flag = blk->holder->key != 0xdfad9f51;
  SP::V3 D;
  D.x = o - C.x;
  D.y = qx - C.y;
  D.z = qy - C.z;
  FUN_0049d6b0(blk, C, D, a4, flag, FLT_MAX);
}

// @ 0x005cf7a0
SP::E20Iter CopyE20(SP::E20Iter first, SP::E20Iter last, SP::E20Iter dest)
{
  SP::E20Iter currentDest(dest);
  for (; first != last; ++first, ++currentDest)
    if (&*currentDest) new ((void*)&*currentDest) SP::E20(*first);
  return currentDest;
}

// @ 0x005cf830
void SP::cSPEditorSpine::LoadStaticTuning()
{}

// @ 0x005cfde0
void FUN_005cfde0(int, int, float*, int, float*, float*, int, char)
{}

// @ 0x005d02d0
void FUN_005d02d0(int, int, float, float)
{}

// @ 0x005d07f0
void FUN_005d07f0(int)
{}

// @ 0x005d0ce0
namespace SP {
Leg* cSPEditorSpine_s005d_02d0::GetFirstLeg()
{
  LimbVector limbs;
  EditorUtils::GetAllLimbs(mpLimbs, &limbs, 1);
  Leg* best = 0;
  for (unsigned int i = 0; i < limbs.size(); ++i) {
    Leg* leg = limbs[i];
    if (EditorUtils::GetFirstFootBlock(leg) != 0) {
      if (best == 0 || leg->mFieldDC0 < best->mFieldDC0)
        best = leg;
    }
  }
  return best;
}
}  // namespace SP

// @ 0x005d0d90
namespace SP {
Leg* cSPEditorSpine_s005d_02d0::GetLastLeg()
{
  LimbVector limbs;
  EditorUtils::GetAllLimbs(mpLimbs, &limbs, 1);
  Leg* best = 0;
  for (unsigned int i = 0; i < limbs.size(); ++i) {
    Leg* leg = limbs[i];
    if (EditorUtils::GetFirstFootBlock(leg) != 0) {
      if (best == 0 || leg->mFieldDC0 > best->mFieldDC0)
        best = leg;
    }
  }
  return best;
}
}  // namespace SP

// @ 0x005d0ea0
void FUN_005d0ea0(int)
{}

// @ 0x005d12c0
namespace SP {
void RecordBlockCoordinatesSkeleton(void*, void*)
{}
}  // namespace SP

// @ 0x005d13f0
namespace SP {
Elem24* CopyElem24(Elem24* first, Elem24* last, Elem24* dest)
{
  if (first != last) {
    do {
      if (dest) {
        dest->mA = first->mA;
        dest->mB = first->mB;
        dest->mC = first->mC;
        dest->mD = first->mD;
        new ((void*)&dest->mSub) Sub24(first->mSub);
      }
      ++first;
      ++dest;
    } while (first != last);
  }
  return dest;
}
}  // namespace SP

// @ 0x005d1450
namespace SP {
Elem24* RelocateElem24Backward(Elem24* first, Elem24* last, Elem24* dest)
{
  if (last == first) return dest;
  do {
    --last;
    --dest;
    dest->mA = last->mA;
    dest->mB = last->mB;
    dest->mC = last->mC;
    dest->mD = last->mD;
    dest->mSub = last->mSub;
  } while (last != first);
  return dest;
}
}  // namespace SP

// @ 0x005d14a0
namespace SP {
void FUN_005d14a0(int)
{}
}  // namespace SP

// @ 0x005d1530
namespace SP {
void FUN_005d1530(int)
{}
}  // namespace SP

// @ 0x005d1600
namespace SP {
void cSpine75::SetFlag(bool enable, int)
{
  if (enable) {
    if (!mFieldC5) {
      EnableBody();
      mFieldC5 = true;
    }
  } else {
    if (mFieldC5) {
      DisableBody();
      mFieldC5 = false;
    }
  }
}
}  // namespace SP

// @ 0x005d1640
namespace SP {
void FUN_005d1640(int)
{}
}  // namespace SP

// @ 0x005d1780
namespace SP {
void FUN_005d1780(int)
{}
}  // namespace SP

// @ 0x005d19e0
namespace SP {
void FUN_005d19e0(int)
{}
}  // namespace SP

// @ 0x005d1ba0
namespace SP {
__declspec(noinline) void cSpine76::FUN_005d1ba0()
{ g_spine76Sink = 2; }
}  // namespace SP

// @ 0x005d1d40
void SP::cSPEditorSpine::UpdateVertebraeOrderAndCollisionFilters()
{ g_spine76Sink = 4; }

// @ 0x005d1e70
namespace SP {
__declspec(noinline) void cSpine76::FUN_005d1e70()
{ g_spine76Sink = 3; }
}  // namespace SP

// @ 0x005d1f30
namespace SP {
void cSpine76::FUN_005d1f30()
{
  FUN_005d1e70();

  hkConstraintChainState* chainState = (hkConstraintChainState*)hkAlloc(0x28);
  void* chain = FUN_0108bb00(chainState);
  bool bAbort = false;

  FUN_005d1d40();

  unsigned int key = (unsigned int)(size_t)mFirstVertebra;
  for (;;) {
    if (key == 0) break;

    RBNode* hit;
    cSPEditorVertebraInfo_s005d_1f30* info =
        (*mVertebrae.find(&hit, &key) == (RBNode*)&mVertebrae.mAnchor) ? 0 : &mVertebrae[key];

    if (!mSpineVertebraHavokPaddingFactor || key == (unsigned int)(size_t)mFirstVertebra ||
        key == (unsigned int)(size_t)mLastVertebra) {
      // axial (planar) constraint between this vertebra and the world
      hkRefObj* axialData = (hkRefObj*)CreateAxialConstraintData(0);
      hkRefObj* ci = hkAlloc(0x28);
      hkConstraintInstance* inst =
          (hkConstraintInstance*)FUN_0108bf10(ci, mpHavokWorld, info->mpRigidBody, axialData, 1);
      axialData->Release();
      mpHavokWorld_14->addConstraint(inst);
      ((hkRefObj*)inst)->Release();
      info->mpPlanarConstraint = inst;

      if (key == (unsigned int)(size_t)mLastVertebra) break;
    }

    // hinge constraint linking this vertebra to the next one
    unsigned int nextKey = (unsigned int)(size_t)FUN_004a5970((void*)(size_t)key);
    RBNode* nextHit;
    if (*mVertebrae.find(&nextHit, &nextKey) == (RBNode*)&mVertebrae.mAnchor) {
      bAbort = true;
      break;
    }
    cSPEditorVertebraInfo_s005d_1f30* nextInfo = &mVertebrae[nextKey];

    float halfWidth = mVertebraHalfWidth;
    float fStep = (halfWidth * 2.0f) * 0.25f;
    float fUp = fStep + halfWidth;
    float fBack = halfWidth - 0.025f;
    float fDown = -halfWidth - fStep;

    float vA[4] = {0.0f, 0.0f, 0.0f, fDown};
    float vB[4] = {fBack, 0.0f, 0.0f, 0.0f};
    FUN_0108ba70(vA, vB);
    void* planar = nextInfo->mpPlanarConstraint;
    if (planar) {
      char dummy;
      mpHavokWorld_14->removeConstraint(&dummy, planar);
      nextInfo->mpPlanarConstraint = 0;
    }

    hkRefObj* hinge = hkAlloc(0x90);
    FUN_0108ae30(hinge);
    hkLimitedHingeConstraintData* hd = (hkLimitedHingeConstraintData*)hinge;

    float a[16] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float b[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    hd->setInBodySpace(*(hkTransform_s005d_1f30*)b, *(hkTransform_s005d_1f30*)a, *(hkTransform_s005d_1f30*)b, *(hkTransform_s005d_1f30*)b,
                       *(hkTransform_s005d_1f30*)a, *(hkTransform_s005d_1f30*)a);

    hd->mSpineChainDamping = mSpineChainDamping;
    hd->mSpineHingeAngularLimitsTauFactor = mSpineHingeAngularLimitsTauFactor;
    hd->mAxisA[0] = fBack;
    hd->mAxisA[1] = 0.0f;
    hd->mAxisA[2] = 0.0f;
    hd->mAxisA[3] = fUp;
    hd->mAxisB[0] = fBack;
    hd->mAxisB[1] = 0.0f;
    hd->mAxisB[2] = 0.0f;
    hd->mAxisB[3] = fDown;
    hd->mSpineMassTimesFactor = ((hkRigidBody_s005d_1f30*)info->mpRigidBody)->mBody->getMass() * 0.7f;
    hd->mSpineChainTau = mSpineChainTau;

    hkRefObj* hingeInst = hkAlloc(0x28);
    hkConstraintInstance* inst2 =
        (hkConstraintInstance*)FUN_0108bf10(hingeInst, mpHavokWorld, info->mpRigidBody, hinge, 1);
    hd->Release();
    mpHavokWorld_14->addConstraint(inst2);
    info->mpHingeConstraint = inst2;

    key = (unsigned int)(size_t)FUN_004a5970((void*)(size_t)key);
  }

  if (bAbort) {
    chainState->Release();
    mpChain = 0;
    return;
  }

  chainState->mSpineMinCollisionDeadZoneDistance = mSpineMinCollisionDeadZoneDistance;
  chainState->mSpineUseFewerAxialConstraints = mSpineUseFewerAxialConstraints ? 1 : 0;
  void* chainBody = FUN_0108acb0(chainState);
  chainState->Release();

  for (unsigned int k = (unsigned int)(size_t)mFirstVertebra; k != 0;
       k = (unsigned int)(size_t)FUN_004a5970((void*)(size_t)k)) {
    RBNode* hit;
    cSPEditorVertebraInfo_s005d_1f30* vi =
        (*mVertebrae.find(&hit, &k) == (RBNode*)&mVertebrae.mAnchor) ? 0 : &mVertebrae[k];
    FUN_0108ac30(chainBody, vi ? vi->mpRigidBody : 0);
  }

  mpHavokWorld_14->addConstraint(chainBody);
  ((hkRefObj*)chainBody)->Release();
  FUN_005d1ba0();
  mpChain = chainBody;
}
}  // namespace SP

// @ 0x005d2480
namespace SP {
void cSpine76::FUN_005d2480(int key)
{
  if (key == 0) return;
  cSPEditorBlock_s005d_1f30* block = (cSPEditorBlock_s005d_1f30*)key;

  unsigned int keyLocal = (unsigned int)key;
  RBNode* node;
  cSPEditorVertebraInfo_s005d_1f30* info = (*mVertebrae.find(&node, &keyLocal) == (RBNode*)&mVertebrae.mAnchor)
                                    ? 0
                                    : &mVertebrae[keyLocal];

  FUN_005cdae0(info);

  __declspec(align(16)) hkTransform_s005d_1f30 xf = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  xf.m[12] = block->mField48;
  xf.m[13] = block->mField4c;
  xf.m[14] = block->mField50;
  xf.m[15] = 0.0f;

  float f = block->mField1d8;

  HavokAlignedRoutine(&block->mOrientation60[0], &xf);
  SpineBigStub(&xf, 0);

  int out[4];
  int* p = AddVertebraBody(out, f, xf);
  info->mpRigidBody = (void*)(size_t)p[0];
  info->mpHingeConstraint = (void*)(size_t)p[1];
  info->mpPlanarConstraint = (void*)(size_t)p[2];
  info->mOrderInSpine = p[3];
}
}  // namespace SP

// @ 0x005d25c0
void SP::cSpine76::FUN_005d25c0(unsigned int key)
{
  RBNode* node;
  cSPEditorVertebraInfo_s005d_1f30* info =
      (*mVertebrae.find(&node, &key) == (RBNode*)&mVertebrae.mAnchor) ? 0 : &mVertebrae[key];

  int order = info->mOrderInSpine;
  if (order < 0 || order >= mVertebrae.mnSize) return;

  unsigned int it = (unsigned int)(size_t)mFirstVertebra;
  if (it == 0) return;

  int idx = -order;
  while (it != 0) {
    RBNode* hit;
    cSPEditorVertebraInfo_s005d_1f30* itInfo =
        (*mVertebrae.find(&hit, &it) == (RBNode*)&mVertebrae.mAnchor) ? 0 : &mVertebrae[it];

    int j = (idx >= 0) ? idx : order;
    float f;
    if (j < mMaxFlexIndex) {
      f = (1.0f - cosf((float)j * 3.1415927f / (float)mMaxFlexIndex)) * 0.5f;
    } else {
      f = 1.0f;
    }

    hkRigidBody_s005d_1f30* body = (hkRigidBody_s005d_1f30*)itInfo->mpRigidBody;
    hkRigidMotion* motion = body->mBody;
    motion->mLinearDamping =
        mScaleOfLeastFlexibility + (mSpineLooseLinearDamping - mScaleOfLeastFlexibility) * f;
    motion->mAngularDamping = mSpineDampingMaxInfluenceDistance +
                              (mSpineLooseAngularDamping - mSpineDampingMaxInfluenceDistance) * f;

    it = (unsigned int)(size_t)FUN_004a5970((void*)(size_t)it);
    ++idx;
    --order;
  }
}

// @ 0x005d2740
namespace SP {
void cSpine76::SetTuning(int)
{
  RBNodeBase* end = &mVertebrae.mAnchor;
  for (RBNodeBase* n = end->mpNodeLeft; n != end; n = RBTreeIncrement(n)) {
    cSPEditorVertebraInfo_s005d_1f30* info = (cSPEditorVertebraInfo_s005d_1f30*)((char*)n + sizeof(RBNode));
    hkRigidBody_s005d_1f30* body = (hkRigidBody_s005d_1f30*)info->mpRigidBody;
    hkRigidMotion* motion = body->mBody;
    motion->mLinearDamping = mSpineLooseLinearDamping;
    motion->mAngularDamping = mSpineLooseAngularDamping;
  }
  FUN_005d1ba0();
}
}  // namespace SP

// @ 0x005d2790
namespace SP {
void cSpine76::Refresh(int)
{
  FUN_005d1e70();
  RBNodeBase* end = &mVertebrae.mAnchor;
  for (RBNodeBase* n = end->mpNodeLeft; n != end; n = RBTreeIncrement(n)) {
    FUN_005d2480((int)(size_t)((RBNode*)n)->mKey);
  }
  FUN_005d1f30();
}
}  // namespace SP

// @ 0x005d27e0
BlockT* Spine::FUN_005d27e0(BlockT* src, float* dir, float* rot)
{
    if ((RefObj*)src != firstVertebra.mp && (RefObj*)src != lastVertebra.mp)
        return 0;
    float lo = src->minScale;
    float hi = src->maxScale;
    bool ok = false;
    float scale = src->scale * maxBlockScale;
    scale = scale > lo ? scale : lo;
    scale = scale < hi ? scale : hi;

    float e = halfWidth * 2.0f * 0.25f + halfWidth;
    float ox = dir[0] * e;
    float oy = dir[1] * e;
    float oz = dir[2] * e;
    float pos[3];
    pos[1] = (src->py + oy) + ((oy * rot[4] + oz * rot[7]) + ox * rot[1]);
    pos[2] = (src->pz + oz) + ((oy * rot[5] + oz * rot[8]) + ox * rot[2]);
    pos[0] = (ox + src->px) + ((oy * rot[3] + oz * rot[6]) + ox * rot[0]);

    Mat3 m9;
    const float* sm = src->m;
    m9.m[0] = (sm[0] * rot[0] + sm[1] * rot[3]) + sm[2] * rot[6];
    m9.m[1] = (sm[0] * rot[1] + sm[1] * rot[4]) + sm[2] * rot[7];
    m9.m[2] = (sm[0] * rot[2] + sm[1] * rot[5]) + sm[2] * rot[8];
    m9.m[3] = (sm[3] * rot[0] + sm[4] * rot[3]) + sm[5] * rot[6];
    m9.m[4] = (sm[3] * rot[1] + sm[4] * rot[4]) + sm[5] * rot[7];
    m9.m[5] = (sm[3] * rot[2] + sm[4] * rot[5]) + sm[5] * rot[8];
    m9.m[6] = (sm[6] * rot[0] + sm[7] * rot[3]) + sm[8] * rot[6];
    m9.m[7] = (sm[6] * rot[1] + sm[7] * rot[4]) + sm[8] * rot[7];
    m9.m[8] = (sm[6] * rot[2] + sm[7] * rot[5]) + sm[8] * rot[8];

    hkTransform_s005d_27e0 xf;
    xf.rot[0][0] = 1.0f; xf.rot[0][1] = 0.0f; xf.rot[0][2] = 0.0f; xf.rot[0][3] = 0.0f;
    xf.rot[1][0] = 0.0f; xf.rot[1][1] = 1.0f; xf.rot[1][2] = 0.0f; xf.rot[1][3] = 0.0f;
    xf.rot[2][0] = 0.0f; xf.rot[2][1] = 0.0f; xf.rot[2][2] = 1.0f; xf.rot[2][3] = 0.0f;
    xf.pos[0] = pos[0]; xf.pos[1] = pos[1]; xf.pos[2] = pos[2]; xf.pos[3] = 0.0f;
    Mat3 m9c = m9;
    FUN_004a92c0(&m9c, &xf);
    FUN_005cd670(&xf, 0);

    HkRef* shape = CreateVertebraShape(scale);
    unsigned key = MakeVertKey(scale, (RefObj*)src == firstVertebra.mp ? -1 : (int)vertebrae.size);
    hkSimpleShapePhantom* ph =
        new (g_hkMemory_s005d_27e0->Alloc(0x130, 0x2e)) hkSimpleShapePhantom(shape, &xf, key);
    ph->memSize = 0x130;
    world->addPhantom(ph);
    ph->removeReference();

    PointCollector col;
    col.vt = vtbl_collector;
    col.earlyOut = 3.4028200e38f;
    col.data = col.buf;
    col.capFlags = 0x80000008;
    col.size = 0;
    ph->getClosestPoints(&col);
    int n = col.size;
    if (n > 0) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            CdPoint& pt = col.data[i];
            float d = pt.dist;
            if (d >= 0.0f) {
                count++;
            } else {
                float ad = d < 0.0f ? -d : d;
                if ((pt.a->flags & 0x1f) == 2 && (pt.b->flags & 0x1f) == 2) {
                    float ta = TimeObjValue(pt.a->timeObj);
                    float tb = TimeObjValue(pt.b->timeObj);
                    if (ad < ta && ad < tb)
                        count++;
                }
            }
        }
        if (count == n && n <= 1)
            ok = true;
    } else {
        ok = true;
    }
    world->removePhantom(ph);
    shape->release();

    BlockT* nb = 0;
    if (ok) {
        VertVal tmp;
        void* cookie = src->cookie;
        FUN_005ce060(&tmp, scale, &xf);
        BlockT* blk = new ("Editor", 0, 0, 0, 0) BlockT();
        nb = blk;
        float x = ((Cookie*)cookie)->F4adaa0(1, 1, 1);
        PhysW* pw = ((Cookie*)cookie)->F4ad450();
        void* wld = pw->World();
        nb->BuildBlock(pFC, inst104, pF0, wld, x, 1, 1, 1);
        nb->model;  // SP::ModelManager()
        if (nb->model)
            nb->model->f58 = 0.0f;
        nb->FUN_00448e90(pos, 0);
        nb->FUN_00449420(m9c.m, 0);
        nb->FUN_00440090(scale, 0);
        nb->FUN_00440020(scale, 1);
        unsigned k2 = (unsigned)nb;
        VertVal* v = vertebrae.Index(&k2);
        *v = tmp;
        if ((RefObj*)src == firstVertebra.mp) {
            nb->FUN_00438700((BlockT*)firstVertebra.mp);
            ((Cookie*)cookie)->F4abaf0(nb, 1);
            firstVertebra = (RefObj*)nb;
            firstHandle.mp->SetState(firstVertebra.mp);
        } else {
            ((BlockT*)lastVertebra.mp)->FUN_00438700(nb);
            ((Cookie*)cookie)->F4abaf0(nb, 1);
            lastVertebra = (RefObj*)nb;
            lastHandle.mp->SetState(lastVertebra.mp);
        }
        FUN_005d2790();
    }
    col.vt = vtbl_collector;
    if ((int)col.capFlags >= 0) {
        hkThreadMem* tm = (hkThreadMem*)TlsGetValue(g_tlsThreadMem);
        tm->deallocateChunk(col.data, (col.capFlags & 0x3fffffff) * 0x30, 0x14);
    }
    return nb;
}

// @ 0x005d3010
bool Spine::FUN_005d3010(unsigned key, int, int, int, int, int, int)
{
    int n = (int)(vecEnd - vecBegin);
    int i = 0;
    if (n > 0) {
        do {
            ((Ob*)vecBegin[i])->FUN_0048a4c0();
            i++;
        } while (i < n);
    }
    if (dirty) {
        FUN_005d14a0();
        dirty = 0;
    }
    unsigned k = key;
    key = k;
    RbNode* endN = (RbNode*)((char*)this + 0xd0);
    RbNode* it = vertebrae.LowerFind(k);
    if (it != endN && vertebrae.Index(&key)) {
        FUN_005d2740(k);
        if (action) {
            world->removeAction(action);
            action->release();
            action = 0;
        }
        return true;
    }
    return false;
}

// @ 0x005d3100
float Spine::FUN_005d3100()
{
    float total = 0.0f;
    BlockT* nextB = (BlockT*)firstVertebra.mp;
    BlockT* b;
    while (b = nextB, b != 0) {
        nextB = 0;
        unsigned key = (unsigned)b;
        RbNode* it = vertebrae.LowerFind(key);
        VertVal* v;
        if (it != (RbNode*)((char*)this + 0xd0))
            v = vertebrae.Index(&key);
        else
            v = 0;
        total = ((hkBody*)v->body)->motion->getMass() + total;
        if (b != (BlockT*)lastVertebra.mp)
            nextB = (BlockT*)NextVertebra((Block_s005d_27e0*)b);
    }
    return total;
}

// @ 0x005d31b0
void Spine::FUN_005d31b0()
{
    FUN_005d14a0();
    FUN_005d1e70();
    char tmp;
    RbNode* anchor = vertebrae.Anchor();
    for (RbNode* n = vertebrae.anchorLeft; n != anchor; n = RBTreeIncrement(n))
        world->removeEntity(&tmp, n->body);
    vertebrae.Clear();
    if (firstHandle.mp) {
        firstHandle.mp->Reset();
        HandleObj* h = firstHandle.mp;
        if (h) { firstHandle.mp = 0; h->Release(); }
    }
    if (lastHandle.mp) {
        lastHandle.mp->Reset();
        HandleObj* h = lastHandle.mp;
        if (h) { lastHandle.mp = 0; h->Release(); }
    }
    RefObj* r = firstVertebra.mp;
    if (r) { firstVertebra.mp = 0; r->Release(); }
    r = lastVertebra.mp;
    if (r) { lastVertebra.mp = 0; r->Release(); }
    Ob* rt = route1;
    if (rt) {
        rt->FUN_005d59c0();
        operator_delete__(rt);
        route1 = 0;
    }
    rt = route2;
    if (rt) {
        rt->FUN_005d59c0();
        operator_delete__(rt);
        route2 = 0;
    }
}

// @ 0x005d3300
void Spine::FUN_005d3300(BlockT* b)
{
    void* cookie = b->cookie;
    FUN_005d1e70();
    char tmp;
    unsigned key = (unsigned)b;
    VIter it;
    VIter* found = vertebrae.Find(&it, &key);
    VertVal* v;
    if (found->node != vertebrae.Anchor())
        v = vertebrae.Index(&key);
    else
        v = 0;
    RefObj* next = 0;
    if (v->constraint) {
        world->removeConstraint(&tmp, v->constraint);
        v->constraint = 0;
    }
    if (v->body)
        world->removeEntity(&tmp, v->body);
    v->body = 0;
    v->pad12 = 0;
    if ((RefObj*)b == firstVertebra.mp) {
        RefObj* n = (RefObj*)NextVertebra((Block_s005d_27e0*)b);
        if (n) {
            n->AddRef();
            next = n;
        }
        firstVertebra = next;
        firstHandle.mp->SetState(firstVertebra.mp);
    }
    if ((RefObj*)b == lastVertebra.mp) {
        RefObj* n2 = b->nextVertebra;
        if (n2 != next) {
            RefObj* old = next;
            if (n2) n2->AddRef();
            next = n2;
            if (old) old->Release();
        }
        lastVertebra = next;
        lastHandle.mp->SetState(lastVertebra.mp);
    }
    if (!next) {
        RefObj* n3 = b->nextVertebra;
        if (n3) {
            n3->AddRef();
            next = n3;
        }
    }
    FixedVec8 vec;
    vec.Fill(b->children);
    for (int i = (int)(vec.mpEnd - vec.mpBegin) - 1; i >= 0; i--) {
        AutoRef<BlockT> c(vec.mpBegin[i]);
        if (!((c.mp->flags >> 7) & 1))
            ((Ob*)next)->FUN_00438700(c.mp);
    }
    RbNode* y = vertebrae.LowerFind(key);
    if (y != vertebrae.Anchor()) {
        vertebrae.size--;
        RBTreeIncrement(y);
        RBTreeErase(y, vertebrae.Anchor());
        operator_delete__(y);
    }
    ((Ob*)cookie)->FUN_004acab0(b, 0);
    FUN_005d1f30();
    if (next) next->Release();
}

// @ 0x005d35c0
void Spine::FUN_005d35c0()
{
    float a = f10;
    float c = f0c;
    vt0 = vtbl_13f89d4;
    vt8 = vtbl_13f89c4;
    g_015ba0d0 = c;
    g_015ba0d4 = a;
    if (hk1c) hk1c->removeReference();
    if (action) action->release();
    if (world) world->release();
    FUN_005d31b0();
    if (p18) p18->Delete(1);
    unsigned* arr = vecBegin;
    if (arr && arr[-1]) operator_delete__(arr);
    if (lastHandle.mp) lastHandle.mp->Release();
    if (firstHandle.mp) firstHandle.mp->Release();
    if (lastVertebra.mp) lastVertebra.mp->Release();
    if (firstVertebra.mp) firstVertebra.mp->Release();
    vertebrae.~VMap();
    vt8 = vtbl_cEditorResource;
    vt0 = vtbl_cContentValidationSummarizer;
}

// @ 0x005d36e0
void cSPEditorSpine::FUN_005d36e0(cEditorCtx* ctx, cSPEditorBlock* sceneWorld, uint32_t n)
{
  sceneBlock = sceneWorld;
  if (firstBlock) { cSPEditorBlock* p = firstBlock; firstBlock = 0; p->Release(); }
  if (lastBlock) { cSPEditorBlock* p = lastBlock; lastBlock = 0; p->Release(); }
  ctx->FUN_004ad280();
  FUN_005d31b0();
  cSPEditorBlock* tmp = new ("Editor", 0, 0, 0, 0) cSPEditorBlock;
  tmp->BuildBlock(keyInstance, keyGroup, sceneBlock, 0, 0.0f, false, false, true);
  f40 = tmp->defaultOrient[0];
  f44 = tmp->defaultOrient[1];
  tmp->Shutdown2();
  tmp->Dtor(1);
  if (!wallsCreated) {
    float width = ctx->FUN_004adaa0();
    wallZ1 = ctx->FUN_004adb00();
    wallZ0 = ctx->FUN_004adb40();
    wallX0 = -0.5f * width;
    wallX1 = width * 0.5f;
    float W = g_WallThickness;
    float depth = g_WallDepth;
    float h = wallZ0 - wallZ1;
    float H[4];
    float P[4];
    H[0] = depth * 0.5f;
    H[1] = ((wallX1 - wallX0) + W * 2.0f) * 0.5f;
    H[2] = W * 0.5f;
    H[3] = 0.0f;
    P[0] = 0.0f; P[1] = 0.0f; P[2] = (wallZ1 - W * 0.5f) - 0.02f; P[3] = 0.0f;
    CreateWallBoxAndAddToWorld(H, P, world);
    P[0] = 0.0f; P[1] = 0.0f; P[2] = (W * 0.5f + wallZ0) + 0.02f; P[3] = 0.0f;
    CreateWallBoxAndAddToWorld(H, P, world);
    H[0] = depth * 0.5f;
    H[1] = W * 0.5f;
    H[2] = (W * 2.0f + h) * 0.5f;
    H[3] = 0.0f;
    P[0] = 0.0f; P[1] = (wallX1 + W * 0.5f) + 0.02f; P[2] = h * 0.5f + wallZ1; P[3] = 0.0f;
    CreateWallBoxAndAddToWorld(H, P, world);
    P[0] = 0.0f; P[1] = (wallX0 - W * 0.5f) - 0.02f; P[2] = h * 0.5f + wallZ1; P[3] = 0.0f;
    CreateWallBoxAndAddToWorld(H, P, world);
    wallsCreated = true;
  }
  ctx->FUN_004adaa0();
  ctx->FUN_004adaa0();
  float third = ctx->FUN_004adaa0() * 0.33333334f;
  float sp = vertebraHalfWidth * 2.0f * 1.5f;
  float start = sp * 0.5f - ((float)n * sp) * 0.5f;
  for (uint32_t i = 0; i < n; i++) {
    float off = (float)i * sp + start;
    hkTransform_s005d_36e0 T;
    T.rot[0] = 1.0f; T.rot[1] = 0.0f; T.rot[2] = 0.0f; T.rot[3] = 0.0f;
    T.rot[4] = 0.0f; T.rot[5] = 1.0f; T.rot[6] = 0.0f; T.rot[7] = 0.0f;
    T.rot[8] = 0.0f; T.rot[9] = 0.0f; T.rot[10] = 1.0f; T.rot[11] = 0.0f;
    T.trans[0] = 0.0f; T.trans[1] = off; T.trans[2] = third; T.trans[3] = 0.0f;
    hkRigidBody_s005d_36e0* rb = CreateVertebraBody(1.0f, &T);
    world->addEntity(rb, 1);
    rb->removeReference();
    rb->addCollisionListener(listener);
    *(uint16_t*)((char*)rb + 0x96) = 0;
    cSPEditorBlock* blk = new ("Editor", 0, 0, 0, 0) cSPEditorBlock;
    float f30 = ctx->FUN_004adaa0();
    blk->BuildBlock(keyInstance, keyGroup, sceneBlock, ctx->FUN_004ad450()->World(), f30, true, true, true);
    float V[3];
    V[0] = 0.0f; V[1] = off; V[2] = third;
    blk->SetPosition(V, 0);
    VInfo* info = vertebrae.subscript(blk);
    info->body = rb; info->a = 0; info->b = 0; info->c = 0;
    ctx->FUN_004abaf0(blk, 1);
    if (firstBlock == 0) {
      cSPEditorBlock* old = firstBlock;
      if (blk != old) {
        if (blk) blk->AddRef();
        firstBlock = blk;
        if (old) old->Release();
      }
    } else if (lastBlock) {
      lastBlock->LinkNext(blk);
    }
    cSPEditorBlock* old2 = lastBlock;
    if (blk != old2) {
      if (blk) blk->AddRef();
      lastBlock = blk;
      if (old2) old2->Release();
    }
  }
  FUN_005d1e70();
  for (VNodeBase* nd = vertebrae.anchor.left; nd != &vertebrae.anchor; nd = (VNodeBase*)RBTreeIncrement(nd))
    FUN_005d2480(((VNode*)nd)->key);
  FUN_005d1f30();
  BuildHandles();
}

// @ 0x005d3f10
void cSPEditorSpine::FUN_005d3f10(cBlockList* blocks, cSPEditorBlock* sceneBlk)
{
  if (firstBlock) { cSPEditorBlock* p = firstBlock; firstBlock = 0; p->Release(); }
  if (lastBlock) { cSPEditorBlock* p = lastBlock; lastBlock = 0; p->Release(); }
  FUN_005d31b0();
  uint32_t n = blocks->Count();
  for (uint32_t i = 0; i < n; i++) {
    cSPEditorBlock* blk = blocks->At(i);
    if (((AT(uint32_t, blk, 0xdc8)) >> 7) & 1) {
      float scale = blk->scale;
      hkTransform_s005d_36e0 T;
      T.rot[0] = 1.0f; T.rot[1] = 0.0f; T.rot[2] = 0.0f; T.rot[3] = 0.0f;
      T.rot[4] = 0.0f; T.rot[5] = 1.0f; T.rot[6] = 0.0f; T.rot[7] = 0.0f;
      T.rot[8] = 0.0f; T.rot[9] = 0.0f; T.rot[10] = 1.0f; T.rot[11] = 0.0f;
      T.trans[0] = blk->pos[0]; T.trans[1] = blk->pos[1]; T.trans[2] = blk->pos[2]; T.trans[3] = 0.0f;
      FUN_004a92c0(blk->xform, &T);
      FUN_005cd670(&T, 0);
      hkRigidBody_s005d_36e0* rb = CreateVertebraBody(scale, &T);
      world->addEntity(rb, 1);
      rb->removeReference();
      rb->addCollisionListener(listener);
      *(uint16_t*)((char*)rb + 0x96) = 0;
      VInfo* info = vertebrae.subscript(blk);
      info->body = rb; info->a = 0; info->b = 0; info->c = 0;
      if (AT(uint32_t, blk, 0x33c) == 0) {
        cSPEditorBlock* old = firstBlock;
        if (blk != old) {
          blk->AddRef();
          firstBlock = blk;
          if (old) old->Release();
        }
      }
    }
  }
  cSPEditorBlock* p = firstBlock;
  while (p && !lastBlock) {
    cSPEditorBlock* nx = NextBlock(p);
    if (nx) {
      p = nx;
    } else {
      cSPEditorBlock* old = lastBlock;
      if (p != old) {
        if (p) p->AddRef();
        lastBlock = p;
        if (old) old->Release();
      }
    }
  }
  if (firstBlock && lastBlock) {
    sceneBlock = sceneBlk;
    FUN_005d2790();
    BuildHandles();
    return;
  }
  if (firstBlock) { cSPEditorBlock* p2 = firstBlock; firstBlock = 0; p2->Release(); }
  if (lastBlock) { cSPEditorBlock* p2 = lastBlock; lastBlock = 0; p2->Release(); }
}

// @ 0x005d43d0
bool cSPEditorSpine::FUN_005d43d0(cSPEditorBlock** pBlock, float a, float b, float c, float d, float e, float f)
{
  cSPEditorBlock* key = *pBlock;
  if (vertebrae.find(key).node != &vertebrae.anchor) {
    VInfo* info = vertebrae.subscript(key);
    if (info) {
      if (!simulating) {
        FUN_005d1530();
        simulating = true;
      }
      for (VNodeBase* n = vertebrae.anchor.left; n != &vertebrae.anchor; n = (VNodeBase*)RBTreeIncrement(n))
        ((VNode*)n)->body->setMotionType(1, 1, 0);
      FUN_005d25c0(*pBlock);
      float den = (f + e) * 0.0f + d;
      if (den != 0.0f) {
        float t = -(((c + b) * 0.0f + a) / den);
        if (t >= 0.0f) {
          float x = a + d * t;
          float y = b + e * t;
          float z = c + f * t;
          hkVector4 mouse;
          mouse.x = x; mouse.y = y; mouse.z = z; mouse.w = 0.0f;
          hkRigidMotion_s005d_36e0* m = info->body->motion;
          hkVector4 local;
          local.x = x - m->pos[0];
          local.y = y - m->pos[1];
          local.z = z - m->pos[2];
          local.w = -m->pos[3];
          local.x = 0.0f;
          mouse.x = 0.0f;
          if (spring) {
            world->removeAction(spring);
            spring->removeReference();
          }
          hkMouseSpringAction_s005d_36e0* act = (hkMouseSpringAction_s005d_36e0*)g_hkMemory_s005d_36e0->allocate(0x50, 0x26);
          act->memSizeAndFlags = 0x50;
          act = act->Construct(local, mouse, springDamping, springElasticity, 1.0f, info->body);
          spring = act;
          float s = FUN_005d3100();
          float mass = info->body->motion->getMass();
          spring->setMaxRelativeForce(springMaxForce / mass * s);
          world->addAction(spring);
        }
      }
      return true;
    }
  }
  return false;
}

// @ 0x005d4630
namespace SPB {
bool SpineHandle_s005d_4630::Drag(SpineNode_s005d_4630** pBlock, float a, float b, float c, float d, float e, float f)
{
  unsigned key = (unsigned)*pBlock;
  VIter_s005d_4630 it;
  if (vertebrae.Find(&it, &key)->node == vertebrae.Anchor()) return false;
  VInfo_s005d_4630* info = vertebrae.Index(&key);
  if (!info) return false;
  float den = (f + e) * 0.0f + d;
  if (den == 0.0f) return true;
  float t = -(((c + b) * 0.0f + a) / den);
  if (t < 0.0f) return true;
  float cy = b + e * t;
  float cz = c + f * t;
  cy = ClampFloat(cy, wallX0, wallX1);
  cz = ClampFloat(cz, wallZ1, wallZ0);
  HkVector4* mouse = &action->mMouse;
  mouse->x = 0.0f;
  mouse->y = cy;
  mouse->z = cz;
  mouse->w = 0.0f;
  float s = Mass();
  float mass = ((HkBody*)info->body)->motion->getMass();
  action->setMaxRelativeForce(springMaxForce / mass * s);
  return true;
}
}  // namespace SPB

// @ 0x005d47c0
namespace SPB {
void CircleVec_s005d_4630::DoInsertValue(Circle_s005d_4630* position, const Circle_s005d_4630& value)
{
  if (mpEnd != mpCapacity) {
    const Circle_s005d_4630* pValue = &value;
    if (pValue >= position && pValue < mpEnd) ++pValue;
    ::new ((void*)mpEnd) Circle_s005d_4630(*(mpEnd - 1));
    CopyBackwardCircle(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
  } else {
    const int nPrevSize = (int)(mpEnd - mpBegin);
    int nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
    Circle_s005d_4630* pNewData = nNewSize
        ? (Circle_s005d_4630*)operator new(nNewSize * 0x24, "Editor", 0, 0,
                                "c:\\EASTL\\include\\EASTL/allocator.h", 0xd1)
        : 0;
    Circle_s005d_4630* pPos = position;
    Circle_s005d_4630* pOld = mpBegin;
    Circle_s005d_4630* pNewEnd = UninitCopyCircle(pOld, pPos, pNewData);
    DestroyCircleRange(pOld, pPos, pNewData);
    ::new ((void*)pNewEnd) Circle_s005d_4630(value);
    Circle_s005d_4630* pNewEnd2 = UninitCopyCircle(pPos, mpEnd, ++pNewEnd);
    DestroyCircleRange(pPos, mpEnd, pNewEnd2);
    if (pOld && ((uint32_t*)pOld)[-1] != 0) operator delete(pOld);
    mpBegin = pNewData;
    mpEnd = pNewEnd2;
    mpCapacity = pNewData + nNewSize;
  }
}
}  // namespace SPB

// @ 0x005d4970
bool SPB::SpineHandle_s005d_4630::FUN_005d4970()
{
  SPB::CircleVec_s005d_4630 circles;
  {
    int i = 0;
    SPB::SpineNode_s005d_4630* n = n1;
    while (n) {
      SPB::Circle_s005d_4630 c(i, n);
      circles.push_back(c);
      n = SPB::NextNode(n);
      ++i;
    }
  }
  unsigned count = (unsigned)circles.size();
  if (count) {
    unsigned k = 1;
    SPB::Circle_s005d_4630* a = circles.mpBegin;
    unsigned rem = count;
    do {
      if (k < count) {
        SPB::Circle_s005d_4630* q = a + 1;
        for (unsigned m = count - k; m; --m, ++q) a->FUN_005d5be0(q);
      }
      unsigned m = count - 1;
      if (m) {
        SPB::Circle_s005d_4630* q = circles.mpBegin + 1;
        for (; m; --m, ++q) {
          SPB::Vec2_s005d_4630 p1;
          p1.x = q->x;
          p1.y = q->y;
          SPB::Vec2_s005d_4630 p0;
          p0.x = q[-1].x;
          p0.y = q[-1].y;
          a->FUN_005d5cf0(&p0, &p1, q);
        }
      }
      ++k;
      ++a;
    } while (--rem);
  }
  SPB::Vec2_s005d_4630 dirEnd;
  dirEnd.x = (n2->m70 * SPB::gDirY + n2->m7c * SPB::gDirZ) + n2->m64 * SPB::gDirX;
  dirEnd.y = (n2->m74 * SPB::gDirY + n2->m80 * SPB::gDirZ) + n2->m68 * SPB::gDirX;
  SPB::Vec2_s005d_4630 hitB;
  uint32_t idxB;
  if (!SPB::FindEnd(&circles, &dirEnd, circles.mpBegin + count - 1, 0, &hitB, &idxB))
    return false;
  circles.mpBegin[idxB].FUN_005d5b60(&hitB, 2, 0);

  SPB::Vec2_s005d_4630 dirStart;
  float negX = -SPB::gDirX, negY = -SPB::gDirY, negZ = -SPB::gDirZ;
  dirStart.x = (n1->m64 * negX + n1->m70 * negY) + n1->m7c * negZ;
  dirStart.y = (n1->m68 * negX + n1->m74 * negY) + n1->m80 * negZ;
  SPB::Vec2_s005d_4630 hitA;
  uint32_t idxA;
  if (!SPB::FindEnd(&circles, &dirStart, circles.mpBegin, 1, &hitA, &idxA))
    return false;

  SPB::Circle_s005d_4630* c = circles.mpBegin;
  for (unsigned j = 0; j < count; ++j, ++c) {
    if (c->id != idxA) {
      float dx = c->x - hitA.x;
      float dy = c->y - hitA.y;
      float d = sqrtf(dx * dx + dy * dy);
      if (d < c->r + 1.5258789e-05f) return false;
    }
    if (c->id != idxB) {
      float dx = c->x - hitB.x;
      float dy = c->y - hitB.y;
      float d = sqrtf(dx * dx + dy * dy);
      if (d < c->r + 1.5258789e-05f) {
        circles.destruct(circles.mpBegin, circles.mpEnd);
        return false;
      }
    }
  }

  if (c1) {
    c1->~PathObj();
    operator delete(c1);
  }
  c1 = new ("Editor", 0, 0, 0, 0) SPB::PathObj();
  bool okA = WalkBelt(c1, &circles, idxA, hitA.x, hitA.y, 1);
  if (c2) {
    c2->~PathObj();
    operator delete(c2);
  }
  c2 = new ("Editor", 0, 0, 0, 0) SPB::PathObj();
  bool okB = WalkBelt(c2, &circles, idxA, hitA.x, hitA.y, 0);
  bool ok = okA & okB;
  if (!ok) {
    if (c1) {
      c1->~PathObj();
      operator delete(c1);
    }
    SPB::PathObj* t = c2;
    c1 = 0;
    if (t) {
      t->~PathObj();
      operator delete(t);
    }
    c2 = 0;
  } else {
    for (SPB::SpineNode_s005d_4630* n = n1; n; n = SPB::NextNode(n)) {
      uint32_t* r = NearestParam(&hitA, n);
      n->param0 = r[0];
      n->param1 = r[1];
    }
  }
  return ok;
}

// @ 0x005d4fe0
float __fastcall AbsAngleTimes(void* p)
{
  float* f = (float*)p;
  return fabsf(f[5]) * f[6];
}

// @ 0x005d4ff0
bool CrossSideCcw(float* p1, float* p2, float* p3)
{
  float v = (p1[1] - p2[1]) * (p3[0] - p2[0]) - (p3[1] - p2[1]) * (p1[0] - p2[0]);
  if (0.0f > v) return true;
  return false;
}

// @ 0x005d5050
float* PathCurve::Walk(float* out, float t)
{
  float remaining = mTotalLength * t;
  for (unsigned i = 0; i < (unsigned)(mpEnd - mpBegin); ++i) {
    PathSegment* seg = mpBegin[i];
    float len = seg->Length();
    if (len >= remaining) {
      seg->Eval(out, remaining / len);
      return out;
    }
    remaining -= len;
  }
  unsigned n = (unsigned)(mpEnd - mpBegin);
  if (n >= 1) {
    PathSegment* seg = mpBegin[n - 1];
    seg->Eval(out, 1.0f);
    return out;
  }
  out[0] = 0.0f;
  out[1] = 0.0f;
  return out;
}

// @ 0x005d53e0
float cPathShape::FindNextIntersection(const Vector2& point, bool clockwise, PathIntersection** result)
{
  float px = point.x;
  float py = point.y;
  float dx = px - mCircle.mCenter.x;
  float dy = py - mCircle.mCenter.y;
  float invLength = 1.0f / (float)sqrt(dx * dx + dy * dy);
  float dirX = invLength * dx;
  float dirY = invLength * dy;
  PathIntersection* best = 0;
  float bestAngle = kTwoPi;
  for (unsigned int i = 0; i < mIntersections.size(); i++) {
    PathIntersection& entry = mIntersections[i];
    if (fabs(px - entry.mPosition.x) > 1.52587890625e-05f || fabs(py - entry.mPosition.y) > 1.52587890625e-05f) {
      float ex = entry.mPosition.x;
      float ey = entry.mPosition.y;
      float edx = ex - mCircle.mCenter.x;
      float edy = ey - mCircle.mCenter.y;
      float invLen = 1.0f / (float)sqrt(edx * edx + edy * edy);
      float dot = invLen * edx * dirX + invLen * edy * dirY;
      if (dot > 1.0f)
        dot = 1.0f;
      else if (dot < -1.0f)
        dot = -1.0f;
      float angle = (float)acos(dot);
      float cross = (px - mCircle.mCenter.x) * (ey - mCircle.mCenter.y) -
                    (py - mCircle.mCenter.y) * (ex - mCircle.mCenter.x);
      if (!(cross < 0.0f))
        angle = kTwoPi - angle;
      if (!clockwise)
        angle = kTwoPi - angle;
      if (angle < bestAngle) {
        bestAngle = angle;
        best = &entry;
      }
    }
  }
  *result = best;
  return clockwise ? bestAngle : -bestAngle;
}

// @ 0x005d5630
int CircleLineIntersection(Vector2 p1, Vector2 p2, Vector2 center, float radius, float* result)
{
  float x2 = p2.x - center.x;
  float x1 = p1.x - center.x;
  float y2 = p2.y - center.y;
  float y1 = p1.y - center.y;
  float dy = y2 - y1;
  float dx = x2 - x1;
  float dr = (float)sqrt(dx * dx + dy * dy);
  float det = y2 * x1 - y1 * x2;
  float sign = dy < 0.0f ? -1.0f : 1.0f;
  float dr2 = dr * dr;
  float disc = dr2 * radius * radius - det * det;
  float root = (float)sqrt(disc);
  float absTerm = (float)(fabs(dy) * root);
  float signTerm = root * sign * dx;
  result[2] = (det * dy - signTerm) / (dr * dr);
  result[0] = (det * dy + signTerm) / (dr * dr) + center.x;
  result[1] = (absTerm - det * dx) / (dr * dr) + center.y;
  result[3] = (-(det * dx) - absTerm) / (dr * dr);
  result[2] = result[2] + center.x;
  result[3] = center.y + result[3];
  if (disc < 0.0f)
    return 0;
  return disc == 0.0f ? 1 : 2;
}

// @ 0x005d57b0
cPathSegmentList::cPathSegmentList()
{
  mSegments.mpBegin = 0;
  mSegments.mpEnd = 0;
  mSegments.mpCapacity = 0;
  mLength = 0.0f;
}

// @ 0x005d57d0
cPathShape::cPathShape(int type, const void* desc)
{
  mIntersections.mpBegin = 0;
  mIntersections.mpEnd = 0;
  mIntersections.mpCapacity = 0;
  mType = type;
  Vector3 position = GetPosition(desc);
  mCircle.mCenter.x = position.y;
  mCircle.mCenter.y = position.z;
  mCircle.mRadius = GetRadius(desc);
}

// @ 0x005d59c0
cPathSegmentList::~cPathSegmentList()
{
  for (unsigned int i = 0; i < mSegments.size(); i++)
    EASTL_allocator_deallocate(mSegments[i]);
  {
    cPathSegment** first = mSegments.mpBegin;
    cPathSegment** last = mSegments.mpEnd;
    EASTL_memmove(first, last, (unsigned int)((char*)mSegments.mpEnd - (char*)last));
    mSegments.mpEnd -= (last - first);
  }
  if (mSegments.mpBegin && ((int*)mSegments.mpBegin)[-1] != 0)
    EASTL_allocator_deallocate(mSegments.mpBegin);
}

// @ 0x005d5a30
void cPathSegmentList::AddArc(const Point2& center, float sweep, const Point2& start, float radius)
{
  cArcSegment* segment = new ("Editor", 0, 0, 0, 0) cArcSegment(center, sweep, start, radius);
  mLength += segment->GetLength();
  mSegments.push_back_inline(segment);
}

// @ 0x005d5ad0
void cPathSegmentList::AddLine(const Point2& start, const Point2& end)
{
  cLineSegment* segment = new ("Editor", 0, 0, 0, 0) cLineSegment(start, end);
  mLength += segment->GetLength();
  mSegments.push_back_inline(segment);
}

// @ 0x005d5b60
void cPathShape::AddIntersection(const Vector2& position, int flags, cPathShape* other)
{
  mIntersections.push_back_inline(PathIntersection(this, other, position, flags));
}

// @ 0x005d5be0
void cPathShape::IntersectWith(cPathShape* other)
{
  Vector2 points[2];
  int count = mCircle.Intersect(other->mCircle, points);
  if (count >= 1) {
    PathIntersection entry(this, other, points[0], 0);
    mIntersections.push_back_inline(entry);
    other->mIntersections.push_back_inline(entry);
    if (count >= 2) {
      entry.mPosition = points[1];
      mIntersections.push_back(entry);
      other->mIntersections.push_back(entry);
    }
  }
}

// @ 0x005d5cf0
void cPathShape::IntersectLine(const Vector2& p1, const Vector2& p2, cPathShape* other)
{
  float points[4];
  int count = CircleLineIntersection(p1, p2, mCircle.mCenter, mCircle.mRadius, points);
  if (count > 0) {
    float minX = eastl::min(p1.x, p2.x);
    float maxY = eastl::max(p1.y, p2.y);
    float maxX = eastl::max(p1.x, p2.x);
    float minY = eastl::min(p1.y, p2.y);
    if (points[0] >= minX && maxX >= points[0] && points[1] >= minY && maxY >= points[1])
      AddIntersection(*(Vector2*)&points[0], 1, other);
    if (count > 1 && points[2] >= minX && maxX >= points[2] && points[3] >= minY && maxY >= points[3])
      AddIntersection(*(Vector2*)&points[2], 1, other);
  }
}
