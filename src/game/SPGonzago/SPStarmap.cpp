// src/game/SPGonzago/SPStarmap.cpp -- migrated from slice(s) s010488e0, s01047850, s01046160, s01045200, s00995b20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPStarmap.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cStarRecord.h"
#include <math.h>
#include <string.h>
#include "SP/cEmpire.h"
#include "SP/cSpaceTradeRouteManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl FUN_00f47380(void* p);

// ---- items of slice s00995b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00f47380(void* p);
#define EA_DELETE_ARRAY(p) FUN_00f47380(p)
class StarDeque {
public:
    uint8_t mPad00[8];
    void*   mBegin;      // @0x08
    void*   mField0c;    // @0x0c
    void*   mField10;    // @0x10
    void*   mItBegin;    // @0x14  (iterator array ptr)
    void*   mEnd;        // @0x18
    void*   mpPool;      // @0x1c  (current block)
    void*   mField20;    // @0x20
    void*   mItEnd;      // @0x24
    void clear();
};
// ---- items of slice s00995b20 end

// ---- items of slice s01045200 begin (TODO(rewrite): local stubs, replace by canonical classes)
class VEffect {
 public:
  virtual void v00();
  virtual void Release();                     // +0x04
  virtual void SetVisible(bool);              // +0x08
  virtual void Destroy(bool);                 // +0x0c
  virtual void v10();                         // +0x10
  virtual void SetTransform(void*);           // +0x14
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
  virtual void SetParam(int, void*, int);     // +0x44
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
  virtual int64_t GetKey();                   // +0x60
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void vA0();
virtual void vA4();
virtual void vA8();
virtual void vAc();
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBc();
  virtual void Detach();                      // +0xc0
};
class EffectsMgr {
 public:
virtual void t00();
virtual void t04();
virtual void t08();
virtual void t0c();
virtual void t10();
virtual void t14();
virtual void t18();
virtual void t1c();
virtual void t20();
virtual void t24();
virtual void t28();
  virtual bool Create(uint32_t id, int a, VEffect** out);      // +0x2c
};
class cStarRecord;
template <typename T>
struct DequeIter {
  T* mpCurrent;
  T* mpBegin;
  T* mpEnd;
  T** mpCurrentArrayPtr;
};
template <typename T>
struct Deque64 {
  T** mpPtrArray;              // +0x00
  uint32_t mnPtrArraySize;     // +0x04
  DequeIter<T> mItBegin;       // +0x08
  DequeIter<T> mItEnd;         // +0x18
  uint32_t mAllocator;         // +0x28
  uint32_t mPad2c;             // +0x2c

  void clear();                // eastl::deque<T>::clear (thiscall)
};
class cStarRecord {
 public:
  virtual void r00();          // +0x00
  virtual void Release();      // +0x04
  uint8_t mPad08[0x6c];        // +0x04 .. +0x6f
  void* mpInstance;            // +0x70
};
struct StarMapVisual {
  VEffect* mpObject;           // +0x14 in the node
  uint32_t mKey;               // +0x18
  uint32_t mGroup;             // +0x1c
  uint32_t mFlags;             // +0x20
};
struct RBNode {
  RBNode* mpLeft;
  RBNode* mpRight;
  RBNode* mpParent;
  uint32_t mColor;
  void* mpKey;                 // +0x10
  StarMapVisual mValue;        // +0x14
};
struct NodeRange {
  RBNode* mpFirst;
  RBNode* mpSecond;
};
struct RBTree {
  uint32_t mAlloc;             // +0x00
  RBNode* mpAnchorLeft;        // +0x04
  RBNode* mpAnchorRight;       // +0x08
  RBNode* mpRoot;              // +0x0c
  uint32_t mField10;           // +0x10
  uint32_t mnSize;             // +0x14
  uint32_t mPad18;             // +0x18

  void equal_range(NodeRange* out, const uint32_t* key);   // 0x00d4b450
};
struct VisualCtx;
class cStarMap {
 public:
  uint8_t mPad00[0x20];
  Deque64<cStarRecord*> mTravelTrail;   // 0x20
  float mTravelTrailLength;            // 0x50
  VEffect* mRelationshipScreenEffect;  // 0x54
  RBTree mObjectVisuals;               // 0x58
  uint32_t mVisualCount;               // 0x74

  VEffect* CreateVisual(cStarRecord* rec, int kind, int key, int group,
                        bool flagA, bool flagB);
  VEffect* CreateStarRecordVisual(cStarRecord* rec, int key, int group);
  VEffect* CreatePlanetRecordVisual(cStarRecord* rec, int key, int group,
                                    bool flagA, bool flagB);
  void RemoveVisual(VEffect* object, bool destroy);
  void RemoveVisual(uint32_t mapKey, uint32_t keyLo, uint32_t keyHi, bool destroy);
  void RemoveVisualGroup(int group, bool destroy);
  void ResetTravelTrail();
  void FilterHelperRemove(int filter);
  void FilterHelperTravelTrail(int filter);
  void FilterHelperVisited(uint32_t filter);
  void SetInitialVisuals();
  void BuildVisual(VisualCtx* ctx, void* object);
  void Init();                 // SP::cStarMap::Init
};
void   operator_delete__(void* p);                        // 0x00f47380
void   RBTreeInsert(void* node, RBNode* parent, RBNode** anchor, int side); // 0x009216a0
RBNode* RBTreeIncrement(RBNode* node);                    // 0x00921580
void   RBTreeErase(RBNode* node, RBNode** anchor);        // 0x00921880
RBNode* FUN_010450b0(void* key);                          // 0x010450b0
EffectsMgr* EffectsManagerPtr();                          // 0x0067ddd0
void*  cStarRecordRef_GetCommContext(void* ref);          // 0x00ce6950
char   FUN_01044bf0(cStarMap* self, cStarRecord* rec);    // 0x01044bf0
void*  cSPLivingUniverse_GetPlayerEmpire();               // 0x01021300
class EmpireContext {
 public:
  void* GetSelectedRecord();                              // 0x00c30c60
};
static void DequeClear(Deque64<cStarRecord*>* d)
{
  d->clear();
}
static void VisualDestroy(VEffect* obj, bool a)
{
  if (obj != 0)
    obj->Destroy(a);
}
struct VisualCtx {
  VEffect* mpEffect;
  uint32_t mPad04;
  uint32_t mPad08;
  uint32_t mKind;
};
// ---- items of slice s01045200 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_01045370(Deque64<cStarRecord*>* d, cStarRecord** value);  // 0x01045370 (stays in the slice: not this object's)

// ---- items of slice s01046160 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_13eb1bc;      // 0x013eb1bc
extern float g_1488874;      // 0x01488874
extern float g_1499dac;      // 0x01499dac
extern float g_1465544;      // 0x01465544
void*  __cdecl FUN_01002bd0();                                        // 0x01002bd0
void*  __cdecl FUN_00a1ad60(void* a);                                 // 0x00a1ad60
void*  __cdecl FUN_00ffbe50();                                        // 0x00ffbe50
float  __cdecl FUN_00ffbfd0(void* a);                                 // 0x00ffbfd0
void*  __cdecl FUN_01021240(void* a, void* b);                        // 0x01021240
void*  __cdecl FUN_005c65e0(void* a);                                 // 0x005c65e0
void*  __cdecl FUN_00b3d2a0(void* a);                                 // 0x00b3d2a0
void*  __cdecl FUN_00bb1080(void* a);                                 // 0x00bb1080
bool   __cdecl FUN_01044bf0(void* a, void* b);                        // 0x01044bf0
void*  __cdecl FUN_0067ddd0();                                        // 0x0067ddd0
void*  __cdecl FUN_01045200(void* a, void* b, void* c);               // 0x01045200
void   __cdecl FUN_01045490(void* a, void* b, void* c, void* d);      // 0x01045490
void*  __cdecl FUN_00feb0f0(void* a);                                 // 0x00feb0f0
void*  __cdecl FUN_0067dd50();                                        // 0x0067dd50
void   __cdecl FUN_01045b90(void* a, int b, int c);                   // 0x01045b90
void   __cdecl FUN_01045a60(void* a, void* b, int c);                 // 0x01045a60
void*  __cdecl FUN_00996460(void* a);                                 // 0x00996460
void*  __cdecl FUN_0093a780(void* a, void* b, int c, int d);          // 0x0093a780
void   __cdecl FUN_00692f90(void* a, void* b, int c, int d);          // 0x00692f90
void   __cdecl FUN_00693e10(void* a, void* b);                        // 0x00693e10
bool   __cdecl FUN_00bb9af0(void* a, int b);                          // 0x00bb9af0
void*  __cdecl FUN_01045120(void* a, void* b, void* c);               // 0x01045120
void*  __cdecl FUN_00ba6f20(void* a);                                 // 0x00ba6f20
void   __cdecl FUN_004e0880(void* a, int b);                          // 0x004e0880
void   __cdecl FUN_00455660(void* a, void* b, void* c);               // 0x00455660
void*  __cdecl FUN_00feb9f0();                                        // 0x00feb9f0
bool   __cdecl FUN_00fecbf0(void* a);                                 // 0x00fecbf0
void*  __cdecl FUN_00b3d2c0();                                        // 0x00b3d2c0
void*  __cdecl FUN_00b3d300();                                        // 0x00b3d300
void*  __cdecl FUN_00f67d90(void* a);                                 // 0x00f67d90
void*  __cdecl FUN_01021090();                                        // 0x01021090
bool   __cdecl FUN_00c7a710(void* a, void* b);                        // 0x00c7a710
bool   __cdecl FUN_00d01f20(void* a, void* b, void* c);               // 0x00d01f20
void*  __cdecl FUN_00ba9370(void* a);                                 // 0x00ba9370
bool   __cdecl FUN_00c75d70(void* a, void* b, void* c);               // 0x00c75d70
void*  __cdecl FUN_00c308d0(void* a);                                 // 0x00c308d0
void*  __cdecl FUN_00bba790(void* a);                                 // 0x00bba790
int    __cdecl FUN_00b8dab0(void* a);                                 // 0x00b8dab0
bool   __cdecl FUN_00fee3d0(void* a, void* b, void* c);               // 0x00fee3d0
float  __cdecl FUN_010434c0(void* a, void* b);                        // 0x010434c0
bool   __cdecl FUN_00bba870(void* a, int b);                          // 0x00bba870
void*  __cdecl FUN_00921580(void* a);                                 // 0x00921580
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
struct V3 { float x, y, z; };
struct VecPtr {                 // std::vector<ptr> header (12 bytes)
    void** mFirst;
    void** mLast;
    void** mEnd;
};
struct PropReq {                // stack request descriptor
    uint32_t mField00;
    uint32_t mField04;
    uint32_t mField08;
    float    mField0c;
    float    mField10;
    float    mField14;
    uint32_t mField18;
};
struct PropReq2 {               // larger stack request descriptor (010463b0)
    uint32_t mField00;
    uint32_t mField04;
    uint32_t mField08;
    float    mField0c;
    float    mField10;
    float    mField14;
    uint32_t mField18;
    uint32_t mField1c;
    uint8_t  mField20;
    uint8_t  mPad21[3];
};
struct cMatItem {
    uint8_t  mPad00[0x70];
    void*    mpField70;         // +0x70
    uint8_t  mPad74[0x38];
    uint8_t  mFieldAc;          // +0xac
};
struct cHandle {
    void*    mpObj;             // +0x00
    uint32_t mField04;          // +0x04
    uint32_t mField08;          // +0x08
    uint32_t mField0c;          // +0x0c
    uint8_t  mField10;          // +0x10
    uint8_t  mPad11[3];
};
struct cSub1 {
    uint32_t mData[10];         // +0x00 .. +0x27
    uint8_t  mPad28[4];         // +0x28 .. +0x2b
    void Init(int a);           // 0x00ca09f0
    void Destroy();             // 0x00996460
    void Zero() { for (int i = 0; i < 10; ++i) mData[i] = 0; }
};
struct cFillLocal {
    V3       mValue;            // +0x0000
    uint8_t  mPad[0x0a18 - 12]; // +0x000c
};
struct cIntList {
    void*    mpNext;            // +0x00
    void*    mpHead;            // +0x04
    uint32_t mCount;            // +0x08
    union {
        uint32_t mFlag32;       // +0x0c
        uint8_t  mFlagByte;     // +0x0c
    };
    uint32_t mSize;             // +0x10
};
struct cNode {
    uint8_t  mPad00[0x18];
    void*    mpField18;         // +0x18
};
struct cListNode {
    uint8_t  mPad00[0x10];
    void*    mpField10;         // +0x10
};
struct cGameRoot {
    uint8_t  mPad00[0x30];
    void*    mpField30;         // +0x30 -> cViewList*
};
struct cViewList {
    uint8_t  mPad00[0x90];
    uint32_t mField90;          // +0x90
    void*    mpEnd;             // +0x94 (sentinel)
    void*    mpCur;             // +0x98
};
struct VecF32 { float* mFirst; float* mLast; float* mEnd; };
struct cVecHdr { uint32_t mPool; };
struct cContainer { void** mFirst; void** mLast; };
class cPropView {
public:
    cPropView();                                        // 0x01046e40
    ~cPropView();                                       // 0x01046eb0
    void Pump_01046160(uint32_t key);                   // 0x01046160
    void Pump_010463b0(uint32_t key);                   // 0x010463b0
    void Pump_010468f0(uint32_t key);                   // 0x010468f0
    void Fill_01046f30(void* arg);                      // 0x01046f30
    void Bind(void* cand, uint32_t key, uint32_t propKey);

    uint8_t   mFlag0;           // +0x00
    uint8_t   mFlag1;           // +0x01
    uint8_t   mPad02[2];        // +0x02
    void*     mArray[7];        // +0x04 .. +0x1f
    cSub1     mSub1;            // +0x20
    float     mField4c;         // +0x4c
    uint32_t  mField50;         // +0x50
    void*     mpField54;        // +0x54
    uint8_t   mPad58[4];        // +0x58
    cIntList  mList;            // +0x5c
    uint32_t  mField70;         // +0x70
    uint32_t  mField74;         // +0x74
};
static void PushF32(VecF32* v, float f)                 // vector<float> push_back
{
    if (v->mFirst < v->mLast)
        *v->mFirst++ = f;
    else
        FUN_00455660(v, v->mFirst, &f);
}
void cPropView::Bind(void* candv, uint32_t key, uint32_t propKey)
{
    cMatItem* cand = (cMatItem*)candv;
    void*     p70  = cand->mpField70;
    cHandle   h;

    mField74++;
    h.mpObj    = 0;
    h.mField04 = mField74;
    h.mField08 = key;
    h.mField0c = 1;
    h.mField10 = 0;

    if (key != 0x166521a5u && key != 0x70930c64u && key != 0xc3f6ca28u) {
        if (!((bool(__thiscall*)(void*, void*))FUN_01044bf0)(this, cand)) {
            if (h.mpObj != 0) {
                void* p = h.mpObj;
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            }
            return;
        }
    }

    h.mField10 |= 2;
    void* d = FUN_0067ddd0();
    if (h.mpObj != 0) {
        void* p = h.mpObj;
        h.mpObj = 0;
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    }

    if (((bool(__thiscall*)(void*, uint32_t, int, void*))VF(d, 0x2c))(d, propKey, 0, &h)) {
        {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*, int))VF(p, 8))(p, 0);
        }
        FUN_01045200(this, &h, p70);
        {
            cHandle copy;
            copy.mpObj    = p70;
            copy.mField04 = h.mField04;
            copy.mField08 = h.mField08;
            copy.mField0c = h.mField0c;
            copy.mField10 = h.mField10;
            if (h.mpObj != 0) {
                void* q = h.mpObj;
                ((void(__thiscall*)(void*))VF(q, 0))(q);
            }
            FUN_01045490(&mPad58, &copy, &h, 0);
        }
    }

    if (h.mpObj != 0) {
        void* p = h.mpObj;
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    }
}
// ---- items of slice s01046160 end

// ---- items of slice s01047850 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IEffect { virtual void AddRef(); virtual void Release(); virtual void Init(int a); };
struct IEffectInst { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
  virtual void SetValue(int type, const float* v, int n);       // +0x40
  virtual void SetVertices(int type, const float* v, int n); }; // +0x44
struct IEffectsManager { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
  virtual bool Create(uint32_t hash, int a, IEffect** out); };  // +0x2c
struct Ref {
  IEffect* p;
  Ref() : p(0) {}
  ~Ref() { if (p) p->Release(); }
  void reset() { if (p) { IEffect* t = p; p = 0; t->Release(); } }
};
struct VisualPair {
  uint32_t key;
  IEffect* effect;
  int id;
  int param;
  int one;
  uint8_t flags;
  ~VisualPair() { if (effect) effect->Release(); }
};
struct VisualMap {
  char pad[0x1c];
  void DoInsertValueImpl(void* ret, VisualPair* p, bool b);   // 0x1045490
};
struct CItem {
  char pad[0x70];
  uint32_t key;
  bool FUN_00bb9bd0();               // 0xbb9bd0
  uint32_t GetItemInstanceID();      // 0xc87040
};
struct ItemVec { CItem** b; CItem** e; };
struct CEmpire {
  char pad[0x70];
  uint32_t key;
  ItemVec* GetStars();               // 0xc308d0
  bool FUN_00c31bc0(CEmpire* o);     // 0xc31bc0
  CItem* FUN_00c30c60();             // 0xc30c60
  void GetColor(float* out);         // 0xc32cd0
  int GetAvatar();                   // 0xb1fdb0
  float* GetCities();                // 0x5c65e0
};
struct EmpNode { char pad[0x14]; CEmpire* empire; };
struct EmpireMap { int a; int sentinel; EmpNode* leftmost; };
struct TradeMgr {
  char pad[8]; int anchor; void* leftmost;
  float SystemHasTradeRouteWithPlayer(uint32_t key, int avatar);   // 0x1037dd0
};
struct TradeNode { char pad[0x24]; int idA; int idB; };
struct CStarManager {
  EmpireMap* FUN_00ba6430();         // 0xba6430
  TradeMgr* FUN_00ba6490();          // 0xba6490
  CEmpire* FUN_00ba6d80(int id);     // 0xba6d80
  CEmpire* GetEmpireByID(int id);    // 0xba9370
};
struct CFlagSrc { bool FUN_00feb0b0(CEmpire* e); };   // 0xfeb0b0, global at 0x16e0688
#define AT(T, p, off) (*(T*)((char*)(p) + (off)))
struct CSingleton {
  char raw[0x78];
  void ZeroSub(int a);               // 0xca09f0 (ecx = this+0x20)
  IEffectInst* FUN_01045120(uint32_t key, int id);   // 0x1045120
};
extern CSingleton* g_Singleton;      // 0x16e00d4
void* __cdecl operator_new6(size_t n, const char* tag, int a, int b, int c, int d);   // 0xf473a0
void  __cdecl operator_delete_arr(void* p);        // 0xf47380
void* __cdecl RBTreeIncrement(void* n);            // 0x921580
CStarManager* __cdecl StarManager();               // 0xb3d2a0
IEffectsManager* __cdecl EffectsManager();         // 0x67ddd0
CEmpire* __cdecl GetPlayerEmpire();                // 0x1021300
int __cdecl GetPlayerEmpireID();                   // 0x1021090
void* __cdecl Memcpy(void* d, void* s, int n);     // 0x11e0744
extern CFlagSrc g_FlagSrc;                         // 0x16e0688
struct FVec {
  float* b; float* e; float* cap;
  void Grow(float* pos, float* v);   // 0x455660
  void Reserve(int bytes);           // 0x4e0880
  void Push(float v) {
    if (e < cap) { float* p = e; e = e + 1; if (p) *p = v; }
    else Grow(e, &v);
  }
};
struct CStarMap {
  bool mCheatOmniscience;            // +0
  bool mRequestZoom;
  char pad[0x56];
  VisualMap mObjectVisuals;          // +0x58
  uint32_t mVisualCount;             // +0x74

  bool FUN_01044bf0(void* obj);                       // 0x1044bf0
  IEffectInst* FUN_01045120(uint32_t key, int id);    // 0x1045120
  void FUN_01045200(IEffect** e, uint32_t key);       // 0x1045200
  void FilterHelperEmpires(int mode);                 // 0x1047850

  __forceinline bool MakeVisual(void* obj, uint32_t key, uint32_t hash, int param, bool force, int* outId)
  {
    uint32_t id = mVisualCount;
    mVisualCount = id + 1;
    Ref effect;
    uint8_t flags = 0;
    if (force || FUN_01044bf0(obj)) {
      flags |= 2;
      IEffectsManager* mgr = EffectsManager();
      effect.reset();
      if (mgr->Create(hash, 0, &effect.p)) {
        effect.p->Init(0);
        FUN_01045200(&effect.p, key);
        VisualPair pr;
        pr.key = key;
        pr.effect = effect.p;
        if (pr.effect) pr.effect->AddRef();
        pr.id = id;
        pr.param = param;
        pr.one = 1;
        pr.flags = flags;
        char ret[8];
        mObjectVisuals.DoInsertValueImpl(ret, &pr, false);
        *outId = id;
        return true;
      }
    }
    return false;
  }
};
static inline bool SpecialMode(int m) {
  return m == 0x166521a5 || m == 0x70930c64 || m == -0x3c0935d8;
}
static inline int RoundToInt(float f) {
  __int64 r;
  __asm { fld f
          fistp r }
  return (int)r;
}
static CSingleton* GetSingleton()
{
  if (!g_Singleton) {
    void* mem = operator_new6(0x78, "Simulator", 0, 0, 0, 0);
    CSingleton* s;
    if (mem) {
      char* c = (char*)mem;
      c[0] = 0; c[1] = 0;
      AT(uint32_t, c, 0x20) = 0; AT(uint32_t, c, 0x24) = 0; AT(uint32_t, c, 0x28) = 0;
      AT(uint32_t, c, 0x2c) = 0; AT(uint32_t, c, 0x30) = 0; AT(uint32_t, c, 0x34) = 0;
      AT(uint32_t, c, 0x38) = 0; AT(uint32_t, c, 0x3c) = 0; AT(uint32_t, c, 0x40) = 0;
      AT(uint32_t, c, 0x44) = 0;
      ((CSingleton*)(c + 0x20 - 0x20))->ZeroSub(0);
      AT(float, c, 0x4c) = 500.0f;
      AT(int, c, 0x50) = 1;
      AT(int, c, 0x54) = 0;
      AT(int, c, 0x60) = 0;
      AT(int, c, 0x64) = 0;
      AT(char, c, 0x68) = 0;
      AT(int, c, 0x6c) = 0;
      AT(void*, c, 0x5c) = c + 0x5c;
      AT(void*, c, 0x60) = c + 0x5c;
      s = (CSingleton*)c;
    } else {
      s = 0;
    }
    g_Singleton = s;
  }
  return g_Singleton;
}
// ---- items of slice s01047850 end

// ---- items of slice s010488e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void GetUniverseContext();                        // 0x01021080 (thiscall)
namespace SP {
struct cStarMap_s0104_88e0 {
    uint8_t mPad00;                                          // +0x00
    uint8_t mRequestZoom;                                    // +0x01
    uint8_t mPad02[2];                                       // +0x02 .. +0x03
    int32_t mFilterStates[8];                                // +0x04 ..

    void FilterHelperRebuild(uint32_t index);                // 0x01048c10
    void FilterHelper();                                     // 0x01047000
    void FilterHelperRebuildAll();  // 0x01048ce0 (SP::cStarMap::FilterHelperRebuildAll)
    void FilterHelperAdd(uint32_t which);
    void FilterHelperEmpires(uint32_t which);                // 0x01047850
    void FilterHelperRelationships(uint32_t which);          // 0x01047440
    void FilterHelperVisited(uint32_t which);                // 0x01045f90
    void FilterHelperWormholes(uint32_t which);              // 0x010463b0
    void FilterHelperTravelTrail(uint32_t which);            // 0x01045c80
    void FilterHelperHome(uint32_t which);                   // 0x010488e0
    void FilterHelperSeti(uint32_t which);                   // 0x01046160
    void Helper468f0(uint32_t which);                        // 0x010468f0
    void Helper47300(uint32_t which);                        // 0x01047300
    void FilterHelperLayer(int32_t index, uint32_t value);   // 0x01044a10
    void FilterHelperSpecial(uint32_t value);                // 0x01044df0
    void FilterHelperRemove(int32_t index);                  // 0x01045c30
    void FilterHelper(int32_t index, int32_t mode);  // 0x01048b40 (SP::cStarMap::FilterHelper)
};  // namespace SP
}
// ---- items of slice s010488e0 end

// @ 0x00996460
void __thiscall StarDeque::clear()
{
    if (mItBegin != mItEnd && mpPool != 0)
        EA_DELETE_ARRAY(mpPool);
    void** p = (void**)((char*)mItBegin + 4);
    if (p < (void**)mItEnd) {
        do {
            if (*p != 0)
                EA_DELETE_ARRAY(*p);
            p++;
        } while (p < (void**)mItEnd);
    }
    mEnd    = mBegin;
    mpPool  = mField0c;
    mField20 = mField10;
    mItEnd  = mItBegin;
}

// @ 0x01045490
void DoInsertValueImpl(RBTree* tree, const void* key, const void* value, uint32_t force)
{
  RBNode* parent = (RBNode*)&tree->mpAnchorLeft;
  if (tree->mpRoot != 0) {
    RBNode* node = tree->mpRoot;
    do {
      parent = node;
      if ((uint32_t)key < (uint32_t)node->mpKey)
        node = node->mpRight;
      else
        node = node->mpLeft;
    } while (node != 0);
  }

  bool left = ((parent == (RBNode*)&tree->mpAnchorLeft) ||
               ((uint32_t)key < (uint32_t)parent->mpKey));

  RBNode* fresh = FUN_010450b0((void*)key);
  RBTreeInsert(fresh, parent, (RBNode**)&tree->mpAnchorLeft, left ? 0 : 1);
  tree->mnSize = tree->mnSize + 1;
  (void)value;
  (void)force;
}

// @ 0x01045500
void cStarMap::SetInitialVisuals()
{
  int i = 0;
  do {
    uint32_t* p = (uint32_t*)((uint8_t*)this + 4 + i * 4);
    if ((i == 0) || (i > 4 && i <= 6))
      *p = 1;
    else
      *p = 0;
    ++i;
  } while (i < 7);

  Deque64<cStarRecord*>* dq = &mTravelTrail;
  if (dq->mItBegin.mpCurrent == dq->mItEnd.mpCurrent) {
    void* empire = cSPLivingUniverse_GetPlayerEmpire();
    if (empire != 0) {
      cStarRecord* rec = (cStarRecord*)((EmpireContext*)empire)->GetSelectedRecord();
      if (rec != 0) {
        if (dq->mItEnd.mpCurrent + 1 != dq->mItEnd.mpEnd) {
          cStarRecord** slot = dq->mItEnd.mpCurrent;
          dq->mItEnd.mpCurrent = slot + 1;
          if (slot != 0)
            *slot = rec;
        } else {
          FUN_01045370(dq, &rec);
        }
      }
    }
  }
  Init();
}

// @ 0x01045590
void MultiMapErase(RBTree* tree, RBNode** out, RBNode* node)
{
  tree->mnSize = tree->mnSize - 1;
  RBNode* next = RBTreeIncrement(node);
  RBTreeErase(node, (RBNode**)&tree->mpAnchorLeft);
  VEffect* obj = node->mValue.mpObject;
  if (obj != 0)
    obj->Release();
  operator_delete__(node);
  *out = next;
}

// @ 0x01045740
VEffect* cStarMap::CreateVisual(cStarRecord* rec, int kind, int key, int group, bool flagA, bool flagB)
{
  uint32_t id = this->mVisualCount;
  this->mVisualCount = id + 1;

  void* commCtx = 0;
  if (rec == 0) {
    commCtx = rec ? (void*)rec->mpInstance : 0;
  } else {
    commCtx = cStarRecordRef_GetCommContext(rec);
  }

  if (rec != 0 &&
      key != 0x166521a5 && key != 0x70930c64 &&
      key != (int)0xc3f6ca28 &&
      group != 0x7c2917e7 && group != 0x41bc3bc4 &&
      FUN_01044bf0(this, rec) == 0) {
    return 0;
  }

  VisualCtx ctx;
  ctx.mpEffect = 0;
  ctx.mPad04 = 0;
  ctx.mPad08 = 0;
  ctx.mKind = kind;
  (void)commCtx;

  if (flagA) ctx.mPad04 |= 1;
  if (flagB) ctx.mPad04 |= 2;

  EffectsMgr* mgr = EffectsManagerPtr();
  VEffect* eff = 0;
  if (!mgr->Create((uint32_t)group, 0, &eff))
    return 0;

  eff->SetVisible(false);
  BuildVisual(&ctx, rec);

  // store into the map keyed by the object pointer
  RBNode node;
  node.mpKey = (void*)id;
  node.mValue.mpObject = eff;
  node.mValue.mGroup = (uint32_t)group;
  node.mValue.mFlags = 0;
  DoInsertValueImpl(&this->mObjectVisuals, (const void*)id, &node.mValue, 0);

  return eff;
}

// @ 0x010458f0
VEffect* cStarMap::CreateStarRecordVisual(cStarRecord* rec, int key, int group)
{
  return CreateVisual(rec, 0, key, group, false, true);
}

// @ 0x01045910
VEffect* cStarMap::CreatePlanetRecordVisual(cStarRecord* rec, int key, int group, bool flagA, bool flagB)
{
  uint32_t id = this->mVisualCount;
  this->mVisualCount = id + 1;

  void* instance = (rec != 0) ? rec->mpInstance : 0;

  VisualCtx ctx;
  ctx.mpEffect = 0;
  ctx.mPad04 = 0;
  ctx.mPad08 = 0;
  ctx.mKind = 0;
  if (flagA) ctx.mPad04 |= 1;
  if (flagB) ctx.mPad04 |= 2;

  EffectsMgr* mgr = EffectsManagerPtr();
  VEffect* eff = 0;
  if (!mgr->Create((uint32_t)group, 0, &eff))
    return 0;

  eff->SetVisible(false);
  BuildVisual(&ctx, rec);
  (void)instance;

  RBNode node;
  node.mpKey = (void*)id;
  node.mValue.mpObject = eff;
  node.mValue.mGroup = (uint32_t)group;
  node.mValue.mFlags = 0;
  DoInsertValueImpl(&this->mObjectVisuals, (const void*)id, &node.mValue, 0);
  return eff;
}

// @ 0x01045a60
void cStarMap::RemoveVisual(VEffect* object, bool destroy)
{
  RBNode* anchor = (RBNode*)&this->mObjectVisuals.mpAnchorLeft;
  RBNode* node = this->mObjectVisuals.mpAnchorRight;
  while (node != anchor) {
    if (object == node->mValue.mpObject) {
      VisualDestroy(node->mValue.mpObject, destroy);
      this->mObjectVisuals.mnSize = this->mObjectVisuals.mnSize - 1;
      RBNode* next = RBTreeIncrement(node);
      RBTreeErase(node, (RBNode**)&this->mObjectVisuals.mpAnchorLeft);
      if (node->mValue.mpObject != 0)
        node->mValue.mpObject->Release();
      operator_delete__(node);
      node = next;
    } else {
      node = RBTreeIncrement(node);
    }
  }
}

// @ 0x01045ae0
void cStarMap::RemoveVisual(uint32_t mapKey, uint32_t keyLo, uint32_t keyHi, bool destroy)
{
  NodeRange range;
  this->mObjectVisuals.equal_range(&range, &mapKey);
  RBNode* node = range.mpFirst;
  while (node != range.mpSecond) {
    if (node->mValue.mpObject == 0) {
      // fall through to erase
    } else {
      int64_t k = node->mValue.mpObject->GetKey();
      int64_t want = ((int64_t)keyHi << 32) | keyLo;
      if (k != want) {
        node = RBTreeIncrement(node);
        continue;
      }
      node->mValue.mpObject->Destroy(destroy);
    }
    this->mObjectVisuals.mnSize = this->mObjectVisuals.mnSize - 1;
    RBNode* next = RBTreeIncrement(node);
    RBTreeErase(node, (RBNode**)&this->mObjectVisuals.mpAnchorLeft);
    if (node->mValue.mpObject != 0)
      node->mValue.mpObject->Release();
    operator_delete__(node);
    node = next;
  }
}

// @ 0x01045b90
void cStarMap::RemoveVisualGroup(int group, bool destroy)
{
  RBNode* node = this->mObjectVisuals.mpAnchorRight;
  while (node != (RBNode*)&this->mObjectVisuals.mpAnchorLeft) {
    if ((uint32_t)group == node->mValue.mGroup) {
      VEffect* obj = node->mValue.mpObject;
      if (obj != 0)
        obj->Destroy(destroy);
      this->mObjectVisuals.mnSize = this->mObjectVisuals.mnSize - 1;
      RBNode* next = RBTreeIncrement(node);
      RBTreeErase(node, (RBNode**)&this->mObjectVisuals.mpAnchorLeft);
      if (node->mValue.mpObject != 0)
        node->mValue.mpObject->Release();
      operator_delete__(node);
      node = next;
    } else {
      node = RBTreeIncrement(node);
    }
  }
}

// @ 0x01045c10
void cStarMap::ResetTravelTrail()
{
  RemoveVisualGroup(4, false);
  DequeClear(&this->mTravelTrail);
}

// @ 0x01045c30
void cStarMap::FilterHelperRemove(int filter)
{
  RemoveVisualGroup(filter, false);
  if (filter != 0 && filter != 1 && filter == 2 &&
      this->mRelationshipScreenEffect != 0) {
    VEffect* eff = this->mRelationshipScreenEffect;
    eff->Destroy(false);
    eff = this->mRelationshipScreenEffect;
    if (eff != 0) {
      this->mRelationshipScreenEffect = 0;
      eff->Release();
    }
  }
}

// @ 0x01046160
void cPropView::Pump_01046160(uint32_t key)
{
    void* w = FUN_01002bd0();
    void* g = ((void*(__thiscall*)(void*))FUN_00a1ad60)(w);
    if (g == 0)
        return;
    if (!((bool(__thiscall*)(void*, uint32_t))VF(g, 0x74))(g, 0x016e01a8u))
        return;

    VecPtr  vec;                                       // esp+0x2c
    PropReq req;                                       // esp+0x58
    vec.mFirst = 0;
    vec.mLast  = 0;
    vec.mEnd   = 0;
    req.mField04 = 0x3f;
    req.mField08 = 0;
    req.mField10 = g_13eb1bc;
    req.mField14 = g_13eb1bc;
    req.mField18 = 0;
    req.mField00 = 4;
    req.mField0c = g_13eb1bc;
    req.mField10 = ((float(__thiscall*)(void*))FUN_00ffbfd0)(FUN_00ffbe50());

    void* r = FUN_01021240(&req, &vec);
    void* s = ((void*(__thiscall*)(void*))FUN_005c65e0)(r);
    void* t = FUN_00b3d2a0(s);
    ((void(__thiscall*)(void*))FUN_00bb1080)(t);

    void** it  = vec.mFirst;
    void** end = vec.mLast;
    if (it == end)
        goto done;

    for (; it != end; ++it) {
        void*     obj = *it;
        cMatItem* mi  = (cMatItem*)obj;
        cHandle   h;

        mField74++;
        h.mpObj    = 0;
        h.mField04 = mField74;
        h.mField08 = key;
        h.mField0c = 1;
        h.mField10 = 0;

        if (key != 0x166521a5 && key != 0x70930c64 && key != 0xc3f6ca28) {
            if (((bool(__thiscall*)(void*, void*))FUN_01044bf0)(this, obj))
                goto keep;
            if (h.mpObj != 0) {
                void* p = h.mpObj;
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            }
            continue;
        }

    keep:
        h.mField10 |= 2;
        void* d = FUN_0067ddd0();
        if (h.mpObj != 0) {
            void* p = h.mpObj;
            h.mpObj = 0;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
        bool ok = ((bool(__thiscall*)(void*, uint32_t, int, void*))VF(d, 0x2c))
                      (d, 0x28684c04u, 0, &h);
        if (!ok) {
            if (h.mpObj != 0) {
                void* p = h.mpObj;
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            }
            continue;
        }
        {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*, int))VF(p, 8))(p, 0);
        }
        FUN_01045200(this, &h, mi->mpField70);
        {
            cHandle h2 = h;
            if (h2.mpObj != 0) {
                void* p = h2.mpObj;
                ((void(__thiscall*)(void*))VF(p, 0))(p);
            }
        }
        FUN_01045490(&mPad58, &h, &h, 0);
        if (h.mpObj != 0) {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
    }

done:
    {
        void** b = vec.mFirst;
        void** e = vec.mLast;
        while (b < e) {
            void* p = *b;
            if (p != 0)
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            ++b;
        }
        if (vec.mFirst != 0 && ((cVecHdr*)vec.mFirst - 1)->mPool != 0)
            FUN_00f47380(vec.mFirst);
    }
}

// @ 0x010463b0
void cPropView::Pump_010463b0(uint32_t key)
{
    void* w = FUN_01002bd0();
    void* g = ((void*(__thiscall*)(void*))FUN_00a1ad60)(w);
    if (g == 0)
        return;
    if (!((bool(__thiscall*)(void*, uint32_t))VF(g, 0x74))(g, 0x016e01a8u))
        return;

    VecPtr   vec;                                      // esp+0x64
    PropReq2 req;                                      // esp+0x90
    vec.mFirst = 0;
    vec.mLast  = 0;
    vec.mEnd   = 0;
    req.mField04 = 0x3f;
    req.mField08 = 0;
    req.mField10 = g_13eb1bc;
    req.mField14 = g_13eb1bc;
    req.mField18 = 0;
    req.mField00 = 4;
    req.mField0c = g_13eb1bc;
    req.mField10 = ((float(__thiscall*)(void*))FUN_00ffbfd0)(FUN_00ffbe50());

    void* r = FUN_01021240(&req, &vec);
    void* s = ((void*(__thiscall*)(void*))FUN_005c65e0)(r);
    void* t = FUN_00b3d2a0(s);
    ((void(__thiscall*)(void*))FUN_00bb1080)(t);

    void** it  = vec.mFirst;
    void** end = vec.mLast;
    if (it == end)
        goto done;

    for (; it != end; ++it) {
        cMatItem* mi = (cMatItem*)*it;
        if (!((bool(__thiscall*)(void*, int))FUN_00bb9af0)(mi, 0x10000))
            continue;

        cHandle h;
        mField74++;
        h.mpObj    = 0;
        h.mField04 = mField74;
        h.mField08 = key;
        h.mField0c = 1;
        h.mField10 = 0;

        if (key != 0x166521a5u && key != 0x70930c64u && key != 0xc3f6ca28u) {
            if (!((bool(__thiscall*)(void*, void*))FUN_01044bf0)(this, mi)) {
                if (h.mpObj != 0) {
                    void* p = h.mpObj;
                    ((void(__thiscall*)(void*))VF(p, 4))(p);
                }
                continue;
            }
        }

        h.mField10 |= 2;
        void* d = FUN_0067ddd0();
        if (h.mpObj != 0) {
            void* p = h.mpObj;
            h.mpObj = 0;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
        if (!((bool(__thiscall*)(void*, uint32_t, int, void*))VF(d, 0x2c))
                 (d, 0x4ac5fb61u, 0, &h)) {
            if (h.mpObj != 0) {
                void* p = h.mpObj;
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            }
            continue;
        }
        {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*, int))VF(p, 8))(p, 0);
        }
        FUN_01045200(this, &h, mi->mpField70);
        {
            cHandle hi = h;
            if (hi.mpObj != 0) {
                void* p = hi.mpObj;
                ((void(__thiscall*)(void*))VF(p, 0))(p);
            }
        }

        void* sel = FUN_01045120(this, h.mpObj, mi->mpField70);
        if (sel != 0) {
            float* ca = (float*)((void*(__thiscall*)(void*))FUN_005c65e0)(mi);
            float* cb = (float*)((void*(__thiscall*)(void*))FUN_005c65e0)
                            (((void*(__thiscall*)(void*))FUN_00ba6f20)(FUN_00b3d2a0(mi)));

            VecF32 tmp;
            tmp.mFirst = 0;
            tmp.mLast  = 0;
            tmp.mEnd   = 0;
            FUN_004e0880(&tmp, 0x1c5);

            V3 va;
            va.x = ca[0]; va.y = ca[1]; va.z = ca[2];
            V3 vb;
            vb.x = cb[0]; vb.y = cb[1]; vb.z = cb[2];

            float dx = vb.x - va.x;
            float dy = vb.y - va.y;
            float dz = vb.z - va.z;
            float len = 1.0f / (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
            V3 n;
            n.x = dx * len * g_1488874;
            n.y = dy * len * g_1488874;
            n.z = dz * len * g_1488874;

            PushF32(&tmp, va.x);
            PushF32(&tmp, va.y);
            PushF32(&tmp, va.z);
            PushF32(&tmp, n.x);
            PushF32(&tmp, n.y);
            PushF32(&tmp, n.z);
            PushF32(&tmp, va.x);
            PushF32(&tmp, va.y);
            PushF32(&tmp, va.z);

            float* pd = (float*)FUN_00b3d2a0(mi);
            PushF32(&tmp, pd[0]);
            PushF32(&tmp, pd[1]);
            PushF32(&tmp, pd[2]);

            int nverts = (int)(tmp.mFirst - (float*)tmp.mFirst) + 4;
            ((void(__thiscall*)(void*, float*, int, int))VF(h.mpObj, 0x44))
                (h.mpObj, (float*)tmp.mFirst, nverts, 0);
            FUN_00f47380((float*)tmp.mFirst);
        }

        if (h.mpObj != 0) {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
    }

done:
    {
        void** b = vec.mFirst;
        void** e = vec.mLast;
        while (b < e) {
            void* p = *b;
            if (p != 0)
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            ++b;
        }
        if (vec.mFirst != 0 && ((cVecHdr*)vec.mFirst - 1)->mPool != 0)
            FUN_00f47380(vec.mFirst);
    }
}

// @ 0x010468f0
void cPropView::Pump_010468f0(uint32_t key)
{
    // ---- phase 1: scan the game-data view list for the best renderable ----
    void* a = FUN_00feb9f0();
    if (((bool(__thiscall*)(void*))FUN_00fecbf0)(a)) {
        void* ctx = FUN_00b3d2c0();
        void* e1  = ((void*(__thiscall*)(void*))FUN_00f67d90)(FUN_00b3d300());
        void* e2  = FUN_01021090();
        void* clr = ((void*(__thiscall*)(void*))FUN_005c65e0)
                        (((void*(__cdecl*)())FUN_01021240)());

        cGameRoot* root = (cGameRoot*)FUN_01002bd0();
        cViewList* list = (cViewList*)root->mpField30;
        void** it  = (void**)list->mpCur;
        void** end = &list->mpEnd;

        while (it != end) {
            cListNode* node = (cListNode*)it;
            void* item = node->mpField10;
            if (item != e2
                && ((bool(__thiscall*)(void*, void*))FUN_00c7a710)(e1, item)
                && !((bool(__thiscall*)(void*, void*, void*))FUN_00d01f20)(ctx, item, e2)) {
                void* o = ((void*(__thiscall*)(void*))FUN_00ba9370)(FUN_00b3d2a0(item));
                if (o != 0
                    && ((bool(__thiscall*)(void*, void*, void*))FUN_00c75d70)(e1, o, 0)) {
                    void*        tag = FUN_00feb9f0();
                    cContainer*  cnt = (cContainer*)FUN_00c308d0(o);
                    float        best = g_1499dac;
                    void*        bestObj = 0;

                    for (void** p = cnt->mFirst; p != cnt->mLast; ++p) {
                        cMatItem* cand = (cMatItem*)*p;
                        if (cand->mFieldAc == 0)
                            continue;
                        cContainer* lst = (cContainer*)FUN_00bba790(cand);
                        for (void** k = lst->mFirst; k != lst->mLast; ++k) {
                            void* sub = *k;
                            if (FUN_00b8dab0(sub) == 5
                                && ((bool(__thiscall*)(void*, void*, void*))FUN_00fee3d0)(tag, o, sub)) {
                                float f = ((float(__thiscall*)(void*, void*))FUN_010434c0)
                                              (((void*(__thiscall*)(void*))FUN_005c65e0)(cand), clr);
                                if (f > best) {
                                    best    = f;
                                    bestObj = cand;
                                }
                            }
                        }
                    }

                    if (bestObj != 0)
                        Bind(bestObj, key, 0x57dfe741u);
                }
            }
            it = (void**)FUN_00921580(it);
        }
    }

    // ---- phase 2: build the colour/vertex request and bind every renderable ----
    VecPtr  vec;                                       // esp+0x7c
    PropReq req;                                       // esp+0x90
    vec.mFirst = 0;
    vec.mLast  = 0;
    vec.mEnd   = 0;
    req.mField04 = 0x3f;
    req.mField08 = 0;
    req.mField10 = g_13eb1bc;
    req.mField14 = g_13eb1bc;
    req.mField18 = 0;
    req.mField00 = 0x1ff1;
    req.mField0c = g_13eb1bc;
    req.mField10 = ((float(__thiscall*)(void*))FUN_00ffbfd0)(FUN_00ffbe50());

    void* r = FUN_01021240(&req, &vec);
    void* s = ((void*(__thiscall*)(void*))FUN_005c65e0)(r);
    void* t = FUN_00b3d2a0(s);
    ((void(__thiscall*)(void*))FUN_00bb1080)(t);

    for (void** it = vec.mFirst; it != vec.mLast; ++it) {
        void* obj = *it;
        if (((bool(__thiscall*)(void*, int))FUN_00bba870)(obj, 1))
            Bind(obj, key, 0x7a10d0cdu);
    }

    // ---- cleanup ----
    {
        void** b = vec.mFirst;
        void** e = vec.mLast;
        while (b < e) {
            void* p = *b;
            if (p != 0)
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            ++b;
        }
        if (vec.mFirst != 0 && ((cVecHdr*)vec.mFirst - 1)->mPool != 0)
            FUN_00f47380(vec.mFirst);
    }
}

// @ 0x01046e40
cPropView::cPropView()
{
    uint32_t* q = mSub1.mData;

    mFlag0 = 0;
    mFlag1 = 0;

    q[0] = 0; q[1] = 0; q[2] = 0; q[3] = 0; q[4] = 0;
    q[5] = 0; q[6] = 0; q[7] = 0; q[8] = 0; q[9] = 0;

    mSub1.Init(0);

    mField4c = g_1465544;
    mField50 = 1;
    mpField54 = 0;

    cIntList* p = &mList;
    memset(&p->mpHead, 0, 0x0c);

    p->mpHead = p;
    p->mpNext = p;
    p->mCount = 0;
    p->mFlagByte = 0;
    p->mSize = 0;
}

// @ 0x01046eb0
cPropView::~cPropView()
{
    void* a = FUN_0067dd50();
    ((void(__thiscall*)(void*, int))VF(a, 0x50))(a, 0x17);

    ((void(__thiscall*)(void*))FUN_00feb0f0)((void*)0x016e0688);

    ((void(__thiscall*)(void*, int, int))FUN_01045b90)(this, 2, 0);

    if (mpField54 != 0) {
        ((void(__thiscall*)(void*, int))VF(mpField54, 0x0c))(mpField54, 0);

        if (mpField54 != 0) {
            void* p = mpField54;
            mpField54 = 0;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
    }

    while (mList.mSize != 0) {
        void* h = mList.mpHead;
        ((void(__thiscall*)(void*, void*, int))FUN_01045a60)
            (this, ((cNode*)h)->mpField18, 1);
    }

    ((void(__thiscall*)(void*))FUN_00996460)(&mSub1);
}

// @ 0x01046f30
void cPropView::Fill_01046f30(void* arg)
{
    ((void(__thiscall*)(void*, int, int))FUN_01045b90)(this, 4, 0);
    ((void(__thiscall*)(void*))FUN_00996460)(&mSub1);

    cFillLocal local;

    for (int i = 0; i < 7; ++i) {
        void* p = ((void*(__thiscall*)(void*))VF(arg, 0x20))(arg);
        void* q = ((void*(__thiscall*)(void*))VF(p, 0x18))(p);
        FUN_0093a780(q, &local.mValue, 1, 0);
        mArray[i] = *(void**)&local.mValue;
    }

    ((void(__thiscall*)(void*, void*, int, int))FUN_00692f90)
        (&local.mValue.y, this, 0x015b85a0, 0x01a80d26);
    ((void(__thiscall*)(void*, void*))FUN_00693e10)(&local.mValue.y, arg);
}

// @ 0x01047850
void CStarMap::FilterHelperEmpires(int mode)
{
  CEmpire* player = GetPlayerEmpire();
  EmpireMap* empires = StarManager()->FUN_00ba6430();
  EmpNode* node = empires->leftmost;
  TradeMgr* trade = StarManager()->FUN_00ba6490();
  void* end = &empires->sentinel;

  if (node != end) {
    do {
      CEmpire* empire = node->empire;
      ItemVec* stars = empire->GetStars();
      bool allied = player->FUN_00c31bc0(empire);
      if (g_FlagSrc.FUN_00feb0b0(empire) && (empire->GetStars()->e - empire->GetStars()->b) != 0) {
        bool go = false;
        if (mode == 0) { if (empire == player) go = true; }
        else if (mode == 1 && empire != player) go = true;
        if (go) {
          int count = (int)(stars->e - stars->b);
          for (int i = 0; i < count; i++) {
            CItem* item = stars->b[i];
            if (mCheatOmniscience || item->FUN_00bb9bd0() || allied) {
              float color[3];
              empire->GetColor(color);
              int id = 0;
              if (empire->FUN_00c30c60() == item) {
                if (empire != player) {
                  if (MakeVisual(item, item->key, 0x700d0f8c, mode, SpecialMode(mode), &id)) {
                    if (id != 0) {
                      IEffectInst* inst = FUN_01045120(item->key, id);
                      if (inst) inst->SetValue(5, color, 1);
                    }
                  }
                }
                id = 0;
                if (!MakeVisual(item, item->key, 0x8e2b9b61, mode, SpecialMode(mode), &id)) id = 0;
              } else {
                uint32_t iid = item->GetItemInstanceID();
                uint32_t hash = (iid & 0x100) ? 0x14f60b83 : 0x76c3a43d;
                if (!MakeVisual(item, item->key, hash, mode, SpecialMode(mode), &id)) id = 0;
              }
              if (id != 0) {
                IEffectInst* inst = FUN_01045120(item->key, id);
                if (inst) inst->SetValue(5, color, 1);
              }
            }
          }
        }
      }
      node = (EmpNode*)RBTreeIncrement(node);
    } while (node != end);
  }

  if (mode == 0) {
    void* tn = trade->leftmost;
    void* tend = &trade->anchor;
    if (tn != tend) {
      do {
        TradeNode* t = (TradeNode*)tn;
        CEmpire* a = StarManager()->FUN_00ba6d80(t->idA);
        CEmpire* b = StarManager()->FUN_00ba6d80(t->idB);
        float colorA[3], colorB[3];
        StarManager()->GetEmpireByID(a->GetAvatar())->GetColor(colorA);
        StarManager()->GetEmpireByID(b->GetAvatar())->GetColor(colorB);
        if (a->GetAvatar() == GetPlayerEmpireID()) {
          float tmp[3];
          tmp[0] = colorA[0]; tmp[1] = colorA[1]; tmp[2] = colorA[2];
          colorA[0] = colorB[0]; colorA[1] = colorB[1]; colorA[2] = colorB[2];
          colorB[0] = tmp[0]; colorB[1] = tmp[1]; colorB[2] = tmp[2];
          CEmpire* t2 = a; a = b; b = t2;
        }
        float w = trade->SystemHasTradeRouteWithPlayer(a->key, a->GetAvatar());
        if (w > 0.0f) {
          int dummy = 0;
          if (w >= 100.0f) {
            MakeVisual(a, a->key, 0xce8e2034, 0, false, &dummy);
          }
          float* c0 = a->GetCities();
          float pos[3];
          pos[0] = c0[0]; pos[1] = c0[1]; pos[2] = c0[2];
          float* c1 = b->GetCities();
          float dx = c1[0] - pos[0];
          float dz = c1[2] - pos[2];
          float dy = c1[1] - pos[1];
          float len = (float)sqrt(dx * dx + dz * dz + dy * dy) * 10.0f;
          int n = RoundToInt(len);
          FVec verts;
          verts.b = 0; verts.e = 0; verts.cap = 0;
          uint32_t cnt = n + 2;
          verts.Reserve(cnt * 12);
          uint32_t np1 = n + 1;
          float inv = 1.0f / (float)np1;
          float step[3];
          step[0] = dx * inv; step[1] = inv * dy; step[2] = inv * dz;
          int vid = 0;
          if (!MakeVisual(a, a->key, 0xdcc022f7, 0, false, &vid)) vid = 0;
          CSingleton* sg = GetSingleton();
          IEffectInst* inst = sg->FUN_01045120(a->key, vid);
          if (inst) {
            inst->SetValue(5, colorA, 1);
            if (cnt != 0) {
              uint32_t k = cnt;
              do {
                verts.Push(pos[0]);
                verts.Push(pos[1]);
                verts.Push(pos[2]);
                k--;
                pos[0] = step[0] + pos[0];
                pos[1] = pos[1] + step[1];
                pos[2] = pos[2] + step[2];
              } while (k != 0);
            }
            inst->SetVertices(0xd, verts.b, cnt * 3);
          }
          int vid2 = 0;
          if (!MakeVisual(b, b->key, 0xdcc022f7, 0, false, &vid2)) vid2 = 0;
          sg = GetSingleton();
          IEffectInst* inst2 = sg->FUN_01045120(b->key, vid2);
          if (inst2) {
            inst2->SetValue(5, colorB, 1);
            Memcpy(verts.b, verts.e, 0);
            verts.e = verts.e - (verts.e - verts.b);
            if (cnt != 0) {
              uint32_t k = cnt;
              do {
                verts.Push(pos[0]);
                verts.Push(pos[1]);
                verts.Push(pos[2]);
                k--;
                pos[0] = pos[0] - step[0];
                pos[1] = pos[1] - step[1];
                pos[2] = pos[2] - step[2];
              } while (k != 0);
            }
            inst2->SetVertices(0xd, verts.b, cnt * 3);
          }
          if (verts.b && ((int*)verts.b)[-1] != 0) operator_delete_arr(verts.b);
        }
        tn = RBTreeIncrement(tn);
      } while (tn != tend);
    }
  }
}

// @ 0x01048aa0
void SP::cStarMap_s0104_88e0::FilterHelperAdd(uint32_t which)
{
    mRequestZoom = 1;
    switch (which) {
    case 0:
        FilterHelperEmpires(0);
        return;
    case 1:
        FilterHelperEmpires(1);
        return;
    case 2:
        FilterHelperRelationships(2);
        return;
    case 3:
        FilterHelperVisited(3);
        FilterHelperWormholes(3);
        return;
    case 4:
        FilterHelperTravelTrail(4);
        return;
    case 5:
        Helper468f0(5);
        return;
    case 6:
        FilterHelperHome(6);
        Helper47300(6);
        FilterHelperSeti(6);
        return;
    }
}

// @ 0x01048b40
void SP::cStarMap_s0104_88e0::FilterHelper(int32_t index, int32_t mode)
{
    const int32_t kFilterOff = 0;
    const int32_t kFilterOn = 1;
    const int32_t kFilterPreview = 2;
    const int32_t kFilterOnPreview = 3;
    const int32_t kFilterOffPreview = 4;

    bool changed = false;
    uint32_t value = 0;

    switch (mode) {
    case kFilterOff:
        if (mFilterStates[index] == kFilterOnPreview) {
            changed = true;
            value = 1;
            mode = kFilterOn;
        }
        break;
    case kFilterOn:
        changed = true;
        value = 1;
        if (mFilterStates[index] == kFilterOnPreview)
            mode = kFilterOnPreview;
        break;
    case kFilterPreview:
        changed = true;
        value = 1;
        if (mFilterStates[index] == kFilterOff) {
            mode = kFilterOffPreview;
        } else if (mFilterStates[index] == kFilterOn) {
            mode = kFilterOnPreview;
        } else {
            return;
        }
        break;
    }

    int32_t oldState = mFilterStates[index];
    mFilterStates[index] = mode;

    if (index >= 0) {
        if (index <= 1)
            FilterHelperLayer(index, value);
        else if (index == 5)
            FilterHelperSpecial(value);
    }

    if (changed) {
        if (oldState == kFilterOff)
            FilterHelperAdd((uint32_t)index);
    } else {
        FilterHelperRemove(index);
    }
}

// @ 0x01048ce0
void SP::cStarMap_s0104_88e0::FilterHelperRebuildAll()
{
    if (((void* (__thiscall*)(SP::cStarMap_s0104_88e0*))GetUniverseContext)(this)) {
        for (uint32_t i = 0; i < 7; ++i)
            FilterHelperRebuild(i);
        FilterHelper();
    }
}
