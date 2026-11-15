// src/game/SPEditors/_at_00620000.cpp -- migrated from slice(s) s0062f6e0, s0062e7e0, s0062da00, s0062ca80, s00623f90, s00622f20, s00621830 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00620000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* gAppearance1520f9c;  // 0x15f5f9c
#include <intrin.h>
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/XHTML/DOM/Document.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include "SP/cPropertyList.h"
#include "EA/UTFWinExtras/WinXHTML.h"
#include "SP/cPollinator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"
#include <new>
#include <string.h>
#include <math.h>
#include <float.h>
#include <wchar.h>
#include "SP/cSPEditorAnimatedCreatureData.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayMode_Creature.h"
#include "cSPVector3.h"
#include "SP/cJob.h"
#include "SP/cPlayModePhoto.h"
#include "SP/cSPPlayModeBGInfo.h"
#include "SP/cSPPlayModeBGMgr.h"
#include "SP/cSPPlayModePhotoBrowser.h"
#include "SP/cSPPlayModeUI.h"

// ---- items of slice s00621830 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl EA_Free(void* p);                                              // 0xf47380
extern void* gAppearance1520f9c;  // 0x15f5f9c
static inline void** Vt(void* p) { return *(void***)p; }
struct Drawable {
  virtual void dtor();     // +0x00 (slot 0)
  virtual void AddRef();   // +0x04 (slot 1)
  virtual void Release();  // +0x08 (slot 2)
};
struct ControlDrawable {
  uint32_t  mId;          // +0x00
  Drawable* mpDrawable;   // +0x04
  void AddRefIfAny() { if (mpDrawable) ((void(__thiscall*)(Drawable*))Vt(mpDrawable)[0])(mpDrawable); }
};
struct WinXHTML {
  void SetFormControlDrawable(uint32_t id, Drawable* p);
  void SetScrollbarDrawable(int which, void* p);
};
struct cXHTMLControlAppearance {
  virtual void v0();          // +0x00
  uint32_t mPad4;             // +0x04
  ControlDrawable* mpBegin;   // +0x08
  ControlDrawable* mpEnd;     // +0x0c
  ControlDrawable* mpCap;     // +0x10
  uint32_t mPad14;            // +0x14
  uint32_t mPad18;            // +0x18
  Drawable* mpScroll1;        // +0x1c
  Drawable* mpScroll2;        // +0x20

  cXHTMLControlAppearance();                       // 0x621ee0
  virtual ~cXHTMLControlAppearance();              // 0x621f00 (the VA is the ??_G deleting dtor)
  static void operator delete(void* p) { EA_Free(p); }
  void Apply(WinXHTML* w);                         // 0x621bf0
  bool CreateHitMaskFromResource(int* p1, int* p2, void** out);  // 0x621db0
};
// ---- items of slice s00621830 end

// ---- items of slice s00622f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" __declspec(dllimport) double __cdecl wcstod(const wchar_t*, wchar_t**);
extern "C" __declspec(dllimport) int __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned int);
extern const wchar_t* gLinkPrefix;    // 0x015212c8
extern unsigned int gLinkPrefixLen;   // 0x015f61a4
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(strlen)
#define PV(n) virtual void pv##n();
namespace SP {
class IAppSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
  virtual void OpenURL(const wchar_t* url);  // +0x5c
};
}
namespace SP {
IAppSystem* AppSystem();  // 0x0067dd00
}
inline unsigned int WStrLen(const wchar_t* s) {
  const wchar_t* ps = s + 1;
  do {
  } while (*s++);
  return (unsigned int)(s - ps);
}
namespace SP {
namespace Pollen {
struct LinkMessage {
  uint32_t pad[2];
  uint32_t mEventType;  // +8
  uint32_t pad2[3];
  const wchar_t** mppURL;  // +0x18
};
}
}
// ---- items of slice s00622f20 end

// ---- items of slice s00623f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Random {
class RandomLinearCongruential_s0062_3f90 {
public:
    uint32_t mnSeed;
    void SetSeed(uint32_t seed);  // 0x00936090 (EA::Random::RandomLinearCongruential::SetSeed)
    double RandomDoubleUniform();  // 0x009360d0 (EA::Random::RandomLinearCongruential::RandomDoubleUniform)
};
}
}
extern EA::Random::RandomLinearCongruential_s0062_3f90 sMathRandomA;   // 0x1601760
extern EA::Random::RandomLinearCongruential_s0062_3f90 sMathRandomB;   // 0x15f6470
__forceinline float RandomRangeClampedA(float a, float b)
{
    const double lo = a;
    const double hi = b;
    double d = lo + (hi - lo) * sMathRandomA.RandomDoubleUniform();
    if (d >= hi)
        return (float)hi;
    if (d < lo)
        return (float)lo;
    return (float)d;
}
__forceinline float RandomMaxA(float b)
{
    const double hi = b;
    double d = sMathRandomA.RandomDoubleUniform() * hi;
    if (d >= hi)
        d = hi;
    else if (d < 0)
        d = 0;
    return (float)d;
}
__forceinline float RandomRangeClampedB(float a, float b)
{
    const double lo = a;
    const double hi = b;
    double d = lo + (hi - lo) * sMathRandomB.RandomDoubleUniform();
    if (d >= hi)
        return (float)hi;
    if (d < lo)
        return (float)lo;
    return (float)d;
}
__forceinline float RandomMaxB(float b)
{
    const double hi = b;
    double d = sMathRandomB.RandomDoubleUniform() * hi;
    if (d >= hi)
        d = hi;
    else if (d < 0)
        d = 0;
    return (float)d;
}
struct Vector3 { float x, y, z; Vector3() {} Vector3(float a, float b, float c) : x(a), y(b), z(c) {} };
static inline Vector3 operator*(const Vector3& v, float s) { return Vector3(v.x * s, v.y * s, v.z * s); }
struct Quaternion { float x, y, z, w; };
struct RandomOwner {
    virtual void v0();
    RandomOwner();
};
Vector3* __cdecl FUN_00699600(Vector3* out, const Vector3* a, const Vector3* b, float t);
void __cdecl FUN_0069b840(float a, float b, float c);
void __cdecl FUN_0069b760(int a, int b, int c);
void __cdecl FUN_00699730(float a, float b);
Quaternion* __cdecl QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing, const Vector3* up);
Quaternion* __cdecl FUN_005b2500(Quaternion* tmp, const Vector3* axis, const Vector3* b, float f);
struct T9f0 { void FUN_006b9440(void* p); };
// ---- items of slice s00623f90 end

// ---- items of slice s0062ca80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gVt13fe1bc;    // 0x13fe1bc
extern void* gVt13ec458;    // 0x13ec458
extern void __fastcall VecDtorFn(void*);
extern "C" void __cdecl EASTL_free(void*);
extern const float kGridStep;  // 0x013fe21c  (1/63)
extern const float kNegHalf;   // 0x013ec488  (-0.5)
typedef void (__thiscall *TF0)(void*);
struct Vec12 { void* a; void* b; void* c; };
struct BlockPath { void BlockCircle(float x, float y, float z, int one); };
struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct RefCountObj {
  virtual void slot0();
  virtual int AddRef();
  virtual int Release();
  int mnRefCount;
};
struct PathT : RefCountObj {
  Vec3 mTarget;
  Vec3 mTeleport;
  float mSpeed;
  float mReached;
  unsigned char mType, mCount, mPriority, mRoom;
  PathT() { mnRefCount = 0; }
};
template <class T> struct ARC {
  T* p;
  __forceinline ARC& operator=(T* q) {
    if (q != p) {
      T* old = p;
      if (q) q->AddRef();
      p = q;
      if (old) old->Release();
    }
    return *this;
  }
  __forceinline void Reset() {
    T* t = p;
    if (t) { p = 0; t->Release(); }
  }
};
struct PlayModeCreature;
struct AnimCreature { char pad0[4]; Vec3 mPosition; Quat mRotation; };
struct AnimData {
  char pad0[0x2c];                 // +0x00
  Vec3 mTargetPosition;            // +0x2c
  Vec3 mActualPosition;            // +0x38
  char pad1[0x4c - 0x44];          // +0x44
  float mMovementSpeed;            // +0x4c
  float mRotationSpeed;            // +0x50
  void SetTargetPosition(const Vec3* p, int a, int b);  // 0x59b0f0
  void SetTargetAngle(float angle, int b);              // 0x59b2f0
};
struct PlayMode {
  char pad[0x7c];
  struct { ARC<PlayModeCreature>* mpBegin; ARC<PlayModeCreature>* mpEnd; } mCreatures;
  void StopWalk(AnimCreature* c, unsigned id);  // 0x62a1a0
  void FUN_00628960(AnimCreature* c, unsigned id);  // 0x00628960
};
struct CasualPath {
  void SetPositionOffset(float x, float y);                      // 0x62da00
  bool FindPath(float x, float y, float tx, float ty);           // 0x62e010
  void StartPath();                                              // 0x62dbf0
  bool GetNextPathPoint(Vec3* out);                              // 0x62de30
};
struct PathVec {
  ARC<PathT>* mpBegin;
  ARC<PathT>* mpEnd;
  ARC<PathT>* mpCap;
  void EraseFirst(ARC<PathT>* it);                              // 0x6b5990
  void PushBack(ARC<PathT>* end, ARC<PathT>* value);            // 0x5c8480
};
struct PlayModeCreature : RefCountObj {
  AnimCreature* mAnimCreature;   // +8
  void* mEditorBaseMode;         // +0xc
  AnimData* mData;               // +0x10
  PlayMode* mPlayMode;           // +0x14
  CasualPath* mPath;             // +0x18
  unsigned mCreatureID;          // +0x1c
  float mCollisionRadius;        // +0x20
  bool mCollision;               // +0x24
  float mPathWaitTime;           // +0x28
  float mSaveSpeed;              // +0x2c
  float mSaveRot;                // +0x30
  float mWaitAfter;              // +0x34
  ARC<PathT> mPathInWaiting;     // +0x38
  PathVec mPathList;             // +0x3c

  PathT* NewPath(const Vec3* pos, float speed, char type, float reached);  // 0x62cb20
  bool AtFirstTarget(const Vec3* p);                                      // 0x62cbc0
  void BlockOthers();                                                      // 0x62ca80
  void AddPathTarget(PathT* p, bool replace);                              // 0x62ce00

  bool MoveTo(int unused, int unused2, bool go, bool follow);  // @ 0x0062d0f0
};
struct GridCell {
  float x;                 // +0x00
  float y;                 // +0x04
  GridCell* n[8];          // +0x08  [0]=left [2]=down [4]=right [6]=up; odd slots null
  char pad28[8];           // +0x28
  unsigned char flag;      // +0x30
  char pad31[0x0f];        // +0x31
};
struct GridTable {
  char pad00[8];           // +0x00
  float mWidth;            // +0x08
  float mHeight;           // +0x0c
  float mStepX;            // +0x10
  float mStepY;            // +0x14
  float mOriginX;          // +0x18
  float mOriginY;          // +0x1c
  char pad20[0x18];        // +0x20
  GridCell mCells[64 * 64];  // +0x38

  void Build(float width, float height);  // 0x0062d8a0
};
// ---- items of slice s0062ca80 end

// ---- items of slice s0062da00 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete(void* p);                      // 0x00f47380 (EASTL/EA allocator free)
void* memcpy(void*, const void*, unsigned int); // 0x011e0744
struct Vec2 { float x, y; };
inline float Length(const Vec2& v) { return sqrtf(v.x * v.x + v.y * v.y); }
struct PathNode {
  Vec2 mPosition;            // +0x00
  PathNode* mLinks[8];       // +0x08
  PathNode* mParent;         // +0x28
  PathNode* mChild;          // +0x2c
  uint8_t mPassable;         // +0x30
  bool mProcessed;           // +0x31
  float mEstDistToGoal;      // +0x34
  float mDistFromStart;      // +0x38
  float mTotalDistance;      // +0x3c
};
struct NodeVector {
  PathNode** mpBegin;
  PathNode** mpEnd;
  PathNode** mpCapacity;
  ~NodeVector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin); }
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  bool empty() const { return mpEnd == mpBegin; }
  PathNode*& operator[](uint32_t i) { return mpBegin[i]; }
  void DoInsertValue(PathNode** pos, PathNode* const& value);
  void push_back(PathNode* const& value) {
    if (mpEnd < mpCapacity) {
      new (mpEnd++) PathNode*(value);
    } else {
      DoInsertValue(mpEnd, value);
    }
  }
  PathNode** erase(PathNode** first, PathNode** last) {
    memcpy(first, last, (mpEnd - last) * sizeof(PathNode*));
    mpEnd -= (last - first);
    return first;
  }
  void clear() { erase(mpBegin, mpEnd); }
};
class RefCountVTemplate {
 public:
  int mRefCount;
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
};
class cSPCasual_Path : public RefCountVTemplate {
 public:
  float mWidth;              // +0x08
  float mLength;             // +0x0c
  float mWidthIncr;          // +0x10
  float mLengthIncr;         // +0x14
  Vec2 mStartingOffset;      // +0x18
  Vec2 mPositionOffset;      // +0x20
  bool mPathFound;           // +0x28
  bool mDebugging;           // +0x29
  PathNode* mStartNode;      // +0x2c
  PathNode* mGoalNode;       // +0x30
  PathNode* mCurrentPathNode;// +0x34
  PathNode mGrid[64][64];    // +0x38
  NodeVector mOpenList;      // +0x40038

  cSPCasual_Path();
  virtual ~cSPCasual_Path();
  void SetPositionOffset(float x, float y);
  PathNode* FindPassableNeighbor(PathNode* node, PathNode* exclude);
  bool StartPath();
  void RemoveFromOpenList(PathNode* node);
  PathNode* GetBestOpenNode();
  void BlockCircle(float x, float y, float radius, bool blocked);
  bool GetNextPathPoint(Vec2* out);
  void ExpandNode(PathNode* node);
  bool FindPath(float sx, float sy, float gx, float gy);
};
// ---- items of slice s0062da00 end

// ---- items of slice s0062e7e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int gResourceTypeFilter;              // 0x01522db0
struct ResourceKey;
class cString {
 public:
  uint32_t mData[5];
  cString();
  ~cString();
  void Load(uint32_t table, uint32_t group, const wchar_t* def);
  const wchar_t* c_str();
};
struct RefCountVTemplate_s0062_e7e0 {
  int mRefCount;
  RefCountVTemplate_s0062_e7e0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0062_e7e0() {}
  virtual int AddRef() { return ++mRefCount; }
  virtual int Release();
};
struct IWindow {
virtual void v0();
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
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
  virtual void v30();
  virtual void SetFlag(int flag, bool value);          // +0x7c
  virtual void SetCaption(const wchar_t* text);        // +0x80
};
struct UITooltip {
  void SetText(const wchar_t* text, int a, int b);    // cSPUITooltipWinProc::SetText
};
struct cSPPlayModeUI {
  IWindow* FindPlayModeUIWindow(uint32_t id);
  void SetUIGroupVisible(uint32_t group, bool visible);
  bool IsUIGroupEnabled(uint32_t group);
  void SetAnimButtonsEnabled(bool enabled);
  void SetExpansionAnimButtonsEnabled(bool enabled);
};
class cSPPlayModeAnimLoadInfo;
struct LoadInfoVector {
  cSPPlayModeAnimLoadInfo** mpBegin;
  cSPPlayModeAnimLoadInfo** mpEnd;
  cSPPlayModeAnimLoadInfo** mpCapacity;
  uint32_t mAllocator;
  LoadInfoVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~LoadInfoVector();     // out of line (0x005c7f10)
  void DoInsertValue(cSPPlayModeAnimLoadInfo** pos, cSPPlayModeAnimLoadInfo* const& v);   // 0x005c8480
};
class cSPPlayModeAnimPanelInfo : public RefCountVTemplate_s0062_e7e0 {
 public:
  uint32_t mOrder;                  // +0x08
  uint32_t mIconID;                 // +0x0c
  uint32_t mIconShadowID;           // +0x10
  LoadInfoVector mAnimLoadInfo;     // +0x14
  uint32_t mPad24;                  // +0x24
  virtual ~cSPPlayModeAnimPanelInfo();
};
struct PanelVector {
  cSPPlayModeAnimPanelInfo** mpBegin;
  cSPPlayModeAnimPanelInfo** mpEnd;
  cSPPlayModeAnimPanelInfo** mpCapacity;
  uint32_t mAllocator;
  void DoInsertValue(cSPPlayModeAnimPanelInfo** pos, cSPPlayModeAnimPanelInfo* const& v);   // 0x005c8480
  void Insert(cSPPlayModeAnimPanelInfo** pos, cSPPlayModeAnimPanelInfo* const& v);          // 0x005c21d0
};
class cSPPlayModeAnimation {
 public:
  void* vftable;
  void* mEditorBase;             // +0x04
  uint32_t mCurrAnimID;          // +0x08
  PanelVector mAnimPanelInfo;    // +0x0c
  uint32_t pad1c;                // +0x1c
  uint32_t mPageCount;           // +0x20
  uint32_t mNumPages;            // +0x24
  cSPPlayModeUI* mUI;            // +0x28
  UITooltip* pTooltip[24];       // +0x2c

  int GetAnimCount();
  void UpdateButtonImages();
  void UpdatePageCount();
  void NextAnimWindowSet();
  void PreviousAnimWindowSet();
  void LoadAllAnimInfo();
  void LoadPanelInfo(const ResourceKey& key);
  void LoadAnimInfo(cSPPlayModeAnimPanelInfo* panel, ResourceKey* key);
  void Init(void* editorBase, cSPPlayModeUI* ui);
};
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct KeyVector {
  ResourceKey* mpBegin;
  ResourceKey* mpEnd;
  ResourceKey* mpCapacity;
  ~KeyVector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin); }
};
struct KeyFilter {
  virtual void v0();
  int a, b, c, d;
  KeyFilter() {}
};
struct IResourceManager {
virtual void v0();
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
virtual void v13();
  virtual int GetKeys(KeyVector* out, KeyFilter* filter, int flags);   // +0x38
};
IResourceManager* GetResourceManager();      // 0x008de1a0
class cSPPlayModeAnimLoadInfo : public RefCountVTemplate_s0062_e7e0 {
 public:
  uint32_t mAnimID;           // +0x08
  uint32_t mAnimBabyID;       // +0x0c
  float mAnimBabySpeed;       // +0x10
  float mAnimBabyDelay;       // +0x14
  uint32_t mImage[4];         // +0x18
  uint32_t mIconID;           // +0x28
  uint32_t mProp[4];          // +0x2c (loaded from 0x703212d, 0x70338db, 0x70338e4, 0x70338e9)
  cString mName;              // +0x3c
  virtual ~cSPPlayModeAnimLoadInfo();
  cSPPlayModeAnimLoadInfo() {}
};
// ---- items of slice s0062e7e0 end

// ---- items of slice s0062f6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement, _rotl)
struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};
template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    AutoRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRef(const AutoRef& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};
template <class T> struct SPVec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    SPVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SPVec();
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T* erase(T* first, T* last);
    T* insert(T* pos, const T& v);
    void DoInsertValueEnd(T* pos, const T& v);
};
struct cSPPlayModeUI_s0062_f6e0 {
    void* FindPlayModeUIWindow(uint32_t id);  // 0x00634dc0 (cSPPlayModeUI::FindPlayModeUIWindow)
    void* FindEditorUIWindow(uint32_t id);  // 0x00634e40 (cSPPlayModeUI::FindEditorUIWindow)
    void SetUIGroupVisible(uint32_t id, bool v);  // 0x00635760 (cSPPlayModeUI::SetUIGroupVisible)
    void SetEditorUIGroupVisible(uint32_t id, bool v);  // 0x00635790 (cSPPlayModeUI::SetEditorUIGroupVisible)
    void SetEditorUIEnabled(uint32_t id, bool v);  // 0x00634f20 (cSPPlayModeUI::SetEditorUIEnabled)
    void SetEnabled(uint32_t id, bool v);  // 0x00634ef0 (cSPPlayModeUI::SetEnabled)
    void ToggleUIGroup(uint32_t id, bool v);  // 0x006357c0 (cSPPlayModeUI::ToggleUIGroup)
};
struct UIWindow {
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
    virtual bool v0A();
virtual void v0B();
virtual void v0C();
virtual void v0D();
virtual void v0E();
virtual void v0F();
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
virtual void v1A();
virtual void v1B();
virtual void v1C();
virtual void v1D();
virtual void v1E();
    virtual void SetVisible(bool visible, bool animate);
};
struct cJob {
    int ContinueJob();         // 0x0068f970
    void Cancel(int);          // 0x00692400
    void AddRef();             // 0x0068f950
    void Release();            // 0x00690120
};
struct cPlayModePhoto {
    virtual void d0();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad[0x30 / 4 - 1];
    AutoRef<cJob> writeJob;    // +0x30 (retail layout; PDB has it at the same place)
    AutoRef<cJob> loadJob;     // +0x34
    uint8_t bIsSelected;       // +0x38
    uint8_t bIsLoaded;         // +0x39
};
struct UIImage : IRefCount {
    uint32_t pad[4];
    UIImage(void* raster);                   // 0x008333b0
    int GetWidth();                          // 0x008332a0
    int GetHeight();                         // 0x008332d0
};
struct UIImageView {
    UIImageView(UIImage* img, int w, int h, float u0, float v0, float u1, float v1, int flag); // 0x009579f0
};
struct cSPPlayModePhotoBrowser {
    virtual void v0();
    SPVec<AutoRef<cPlayModePhoto> > mPhotos;   // +0x04
    uint32_t pad0[2];
    uint32_t mCurrentFirstPhotoIndex;          // +0x18
    uint32_t mCurrentSelectedPhotoIndex;       // +0x1c
    uint32_t pad1;
    cSPPlayModeUI_s0062_f6e0* mUI;                        // +0x24
    uint32_t pad2[(0x54 - 0x28) / 4];
    uint32_t mMode;                            // +0x54
    uint32_t pad3[(0xe8c - 0x58) / 4];
    void* mAsyncHandle;                        // +0xe8c

    void EnterMoveMode();
    void EnterDeleteMode();
    void ExitDeleteMode();
    void ExitMoveMode();
    uint8_t IsSendPhotoWinVisible();
    cPlayModePhoto* GetPhotoAt(uint32_t idx, bool relative);
    void SelectAll(bool v);
    static UIImageView* __stdcall GetImageFromRaster(void* raster);
    cPlayModePhoto* FindPhotoByGuid(uint32_t guid);
    void ReleaseAsyncHandle();
    cJob* CancelAllPendingLoadJobs();
    int IsPhotosWriting();
    bool AnyWriteJobActive();
    void UpdatePageButtons(int unused);
};
// ---- items of slice s0062f6e0 end

// @ 0x00621bf0
void cXHTMLControlAppearance::Apply(WinXHTML* w)
{
  if (w == 0) return;
  ControlDrawable* e = mpEnd;
  for (ControlDrawable* p = mpBegin; p != e; ++p)
    w->SetFormControlDrawable(p->mId, p->mpDrawable);
  w->SetScrollbarDrawable(0, mpScroll2 ? (char*)mpScroll2 + 0xc : 0);
  if (mpScroll1) w->SetScrollbarDrawable(1, (char*)mpScroll1 + 0xc);
  else w->SetScrollbarDrawable(1, 0);
}

// @ 0x00621c80
void SetGlobalAppearance(Drawable* p)
{
  Drawable* old = (Drawable*)gAppearance1520f9c;
  if (p != old) {
    if (p) ((void(__thiscall*)(Drawable*))Vt(p)[1])(p);   // AddRef
    gAppearance1520f9c = p;
    if (old) ((void(__thiscall*)(Drawable*))Vt(old)[2])(old);  // Release
  }
}

// @ 0x00622f20
namespace SP { namespace Pollen {
double ToDouble(const wchar_t* s)
{
  wchar_t* end;
  return wcstod(s, &end);
}
}}  // namespace SP::Pollen

// @ 0x00622f40
namespace SP { namespace Pollen {
bool __stdcall HandleLinkMessage(void* unused, const LinkMessage* msg)
{
  if (msg->mEventType == 0x3326e8a) {
    const wchar_t** pp = msg->mppURL;
    if (*pp && wcsncmp(*pp, gLinkPrefix, gLinkPrefixLen) == 0 && WStrLen(*pp) > gLinkPrefixLen) {
      AppSystem()->OpenURL(*pp + gLinkPrefixLen);
      return true;
    }
  }
  return false;
}
}}  // namespace SP::Pollen

// @ 0x006249b0
RandomOwner::RandomOwner()
{
    sMathRandomB.SetSeed(0);
}

// @ 0x006249d0
Quaternion* __stdcall w_6249d0(Quaternion* out, const Vector3* facing, const Vector3* up)
{
    QuaternionFromFacingAndUp(out, facing, up);
    return out;
}

// @ 0x006249f0
void* __stdcall w_6249f0(void* out, T9f0* self)
{
    self->FUN_006b9440(out);
    return out;
}

// @ 0x00624a10
Vector3* __stdcall w_624a10(Vector3* out, const Vector3* a, const Vector3* b, float t)
{
    FUN_00699600(out, a, b, t);
    return out;
}

// @ 0x00624a40
void __stdcall w_624a40(float a, float b, float c)
{
    FUN_0069b840(a, b, c);
}

// @ 0x00624a70
void __stdcall w_624a70(int a, int b, int c)
{
    FUN_0069b760(a, b, c);
}

// @ 0x00624ab0
void __stdcall w_624ab0(float a, float b)
{
    FUN_00699730(a, b);
}

// @ 0x00624b80
float __stdcall w_624b80(float m)
{ return RandomMaxA(m); }

// @ 0x00624bc0
float __stdcall w_624bc0(float a, float b)
{ return RandomRangeClampedA(a, b); }

// @ 0x00624c10
float __stdcall w_624c10(const float* r)
{ return RandomRangeClampedA(r[0], r[1]); }

// @ 0x00624c60
float __stdcall w_624c60(float m)
{ return RandomRangeClampedA(-m, m); }

// @ 0x00624cb0
float __stdcall w_624cb0(float c, float r)
{ return RandomRangeClampedA(c - r, c + r); }

// @ 0x00624d10
float __stdcall w_624d10(float m)
{ return RandomMaxB(m); }

// @ 0x00624d50
float __stdcall w_624d50(float a, float b)
{ return RandomRangeClampedB(a, b); }

// @ 0x00624da0
float __stdcall w_624da0(const float* r)
{ return RandomRangeClampedB(r[0], r[1]); }

// @ 0x00624df0
Quaternion* __stdcall w_624df0(Quaternion* out, const Vector3* axis, float angle)
{
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    Vector3 v = *axis * s;
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
    out->w = c;
    return out;
}

// @ 0x00624e40
Quaternion* __stdcall w_624e40(Quaternion* out, const Vector3* a, const Vector3* b, float f)
{
    Quaternion tmp;
    Quaternion* p = FUN_005b2500(&tmp, a, b, f);
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    out->w = p->w;
    return out;
}

// @ 0x0062ca80
void __fastcall FUN_0062ca80(void* self)
{
  char* s = (char*)self;
  char* mgr = *(char**)(s + 0x14);
  int n = (*(int*)(mgr + 0x80) - *(int*)(mgr + 0x7c)) >> 2;
  if (n == 1) return;
  for (int i = 0; i < n; ++i) {
    char* c = *(char**)(*(int*)(mgr + 0x7c) + i * 4);
    if (c == s) continue;
    char* e = *(char**)(*(char**)(c + 8) + 0x180);
    float x = *(float*)(c + 0x20) + *(float*)(s + 0x20);
    ((BlockPath*)*(void**)(s + 0x18))->BlockCircle(*(float*)(e + 0xc), *(float*)(e + 0x10), x, 1);
  }
}

// @ 0x0062cb90
void __fastcall FUN_0062cb90(void* self)
{
  char* s = (char*)self;
  int n = (*(int*)(s + 0x40) - *(int*)(s + 0x3c)) >> 2;
  if (n > 0) {
    do {
      *(int*)(s + 0x40) -= 4;
      int o = **(int**)(s + 0x40);
      if (o != 0) {
        char* vt = *(char**)o;
        ((TF0)(*(void**)(vt + 8)))((void*)o);
      }
      --n;
    } while (n != 0);
  }
}

// @ 0x0062cbc0
bool PlayModeCreature::AtFirstTarget(const Vec3* p)
{
  PathT* t = mPathList.mpBegin[0].p;
  float d[2];
  d[0] = t->mTarget.x - p->x;
  d[1] = t->mTarget.y - p->y;
  if (fabsf(d[0]) < 1.52587890625e-05f &&
      fabsf(d[1]) < 1.52587890625e-05f)
    return true;
  return false;
}

// @ 0x0062cd30
void* __fastcall FUN_0062cd30(void* self)
{
  char* s = (char*)self;
  *(int*)(s + 4) = 0;
  *(void**)s = (void*)&gVt13fe1bc;
  *(int*)(s + 0x18) = 0;
  *(int*)(s + 0x38) = 0;
  Vec12* vec = (Vec12*)(s + 0x3c);
  vec->a = 0; vec->b = 0; vec->c = 0;
  *(int*)(s + 8) = 0;
  *(int*)(s + 0xc) = 0;
  *(int*)(s + 0x10) = 0;
  *(int*)(s + 0x1c) = -1;
  *(float*)(s + 0x20) = 0.0f;
  *(unsigned char*)(s + 0x24) = 0;
  *(float*)(s + 0x28) = 0.0f;
  *(float*)(s + 0x34) = 0.0f;
  return self;
}

// @ 0x0062cdb0
void* __fastcall FUN_0062cdb0(void* self, char flag)
{
  char* s = (char*)self;
  *(void**)s = (void*)&gVt13fe1bc;
  VecDtorFn(s + 0x3c);
  {
    void* p = *(void**)(s + 0x38);
    if (p != 0) { ((TF0)(*(void**)(*(char**)p + 8)))(p); }
  }
  {
    void* p = *(void**)(s + 0x18);
    if (p != 0) { ((TF0)(*(void**)(*(char**)p + 8)))(p); }
  }
  *(void**)s = (void*)&gVt13ec458;
  if (flag & 1) {
    EASTL_free(s);
  }
  return self;
}

// @ 0x0062d8a0
void GridTable::Build(float width, float height)
{
  mStepX = width * kGridStep;
  mWidth = width;
  mHeight = height;
  mStepY = height * kGridStep;
  mOriginX = width * kNegHalf;
  mOriginY = height * kNegHalf;
  for (int row = 0; row < 64; ++row) {
    for (int col = 0; col < 64; ++col) {
      GridCell* c = &mCells[row * 64 + col];
      c->x = (float)row * mStepX + mOriginX;
      c->y = (float)col * mStepY + mOriginY;
      c->flag = 0;
      for (int k = 0; k < 8; ++k) {
        switch (k) {
          case 0: c->n[0] = col > 0 ? c - 1 : 0; break;
          case 1:
          case 3:
          case 5:
          case 7: c->n[k] = 0; break;
          case 2: c->n[2] = row < 63 ? c + 64 : 0; break;
          case 4: c->n[4] = col < 63 ? c + 1 : 0; break;
          case 6: c->n[6] = row > 0 ? c - 64 : 0; break;
        }
      }
    }
  }
}

// @ 0x0062dbf0
bool cSPCasual_Path::StartPath()
{
  if (!mPathFound) return false;
  mCurrentPathNode = mStartNode;
  return true;
}

// @ 0x0062dce0
void cSPCasual_Path::BlockCircle(float x, float y, float radius, bool blocked)
{
  uint8_t value = 2;
  if (blocked) value = 1;
  float cx = x;
  float cy = y;
  float hw = mWidthIncr * 0.5f;
  float hl = mLengthIncr * 0.5f;
  if (cx < mStartingOffset.x - hw) cx = mStartingOffset.x;
  if (cy < mStartingOffset.y - hl) cy = mStartingOffset.y;
  float maxX = mWidth + mStartingOffset.x;
  if (maxX + hw < cx) cx = maxX;
  float maxY = mLength + mStartingOffset.y;
  if (maxY + hl < cy) cy = maxY;
  PathNode* node = &mGrid[0][0] + ((int)(((cx - mStartingOffset.x) + hw) / mWidthIncr) * 64 +
                                   (int)(((cy - mStartingOffset.y) + hl) / mLengthIncr));
  if (node != 0) node->mPassable = value;
  PathNode* p = &mGrid[0][0];
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      Vec2 d;
      d.y = (p->mPosition.y + mPositionOffset.y) - y;
      d.x = (mPositionOffset.x + p->mPosition.x) - x;
      if (Length(d) <= radius) p->mPassable = value;
      p++;
    }
  }
}

// @ 0x0062de30
bool cSPCasual_Path::GetNextPathPoint(Vec2* out)
{
  PathNode* node = mCurrentPathNode;
  bool atGoal = false;
  if (node == mGoalNode) atGoal = true;
  float x = node->mPosition.x + mPositionOffset.x;
  float y = node->mPosition.y + mPositionOffset.y;
  out->x = x;
  out->y = y;
  mCurrentPathNode = mCurrentPathNode->mChild;
  return atGoal;
}

// @ 0x0062f1e0
void cSPPlayModeAnimation::LoadAllAnimInfo()
{
  IResourceManager* rm = GetResourceManager();
  KeyVector keys;
  keys.mpBegin = 0;
  keys.mpEnd = 0;
  keys.mpCapacity = 0;
  KeyFilter filter;
  filter.a = -1;
  filter.b = gResourceTypeFilter;
  filter.c = 0xb1b104;
  filter.d = -1;
  rm->GetKeys(&keys, &filter, 0);
  for (ResourceKey* k = keys.mpBegin; k != keys.mpEnd; k++) {
    ResourceKey key = *k;
    LoadPanelInfo(key);
  }
}

// @ 0x0062fd60
uint8_t cSPPlayModePhotoBrowser::IsSendPhotoWinVisible()
{
    UIWindow* w = (UIWindow*)mUI->FindEditorUIWindow(0x3f67620);
    if (w) {
        uint8_t r = w->v0A();
        r &= 1;
        return r;
    }
    return false;
}

// @ 0x0062ff90
const char* RFindFirstOf(const char* last, const char* first, const char* s, const char* sEnd)
{
    for (; last != first; --last)
        for (const char* p = s; p != sEnd; ++p)
            if (last[-1] == *p)
                return last;
    return first;
}
