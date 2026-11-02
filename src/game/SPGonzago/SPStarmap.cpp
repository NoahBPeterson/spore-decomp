// src/game/SPGonzago/SPStarmap.cpp -- migrated from slice(s) s01044360, s010488e0, s01047850, s01046160, s01045200, s00995b20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPStarmap.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cStarRecord.h"
#include <math.h>
#include <string.h>
#include "SP/cEmpire.h"
#include "SP/cSpaceTradeRouteManager.h"
#include "SP/cCivData.h"
#include "SP/cGameNounManager.h"
#include "SP/cPropertyManager.h"
#include "SP/cVarListSerializer.h"

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
extern const char kAllocatorFile[];                       // 0x013f09b4 "…/EASTL/allocator.h"
extern float gMatrixDefault;        // 0x016e0690
extern float gVisualPosX;           // 0x016e06b4
extern float gVisualPosY;           // 0x016e06b8
extern float gVisualPosZ;           // 0x016e06bc
extern const float kRealOne;        // 0x01485720
typedef unsigned char byte;
struct Vector3_s0104_5200 { float x, y, z; };
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
class SeqStream {
 public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
  virtual void* Handle();                     // +0x18
};
class SeqReader {
 public:
virtual void q00();
virtual void q04();
virtual void q08();
virtual void q0c();
virtual void q10();
virtual void q14();
  virtual void q18();
  virtual void End();                         // +0x1c
  virtual SeqStream* Stream();                // +0x20
  virtual void* ReadItem();                   // +0x28
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
struct PtrVector {
  void** mpBegin;
  void** mpEnd;
  void** mpCap;
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
void*  StarManager(cStarRecord* rec);                     // 0x00b3d2a0
void   FUN_00b3d2a0(PtrVector* vec);                      // 0x00b3d2a0
int    FUN_00baf460(PtrVector* vec);                      // 0x00baf460
void*  FUN_00ba6dc0(void* mgr, cStarRecord* rec);         // 0x00ba6dc0
void*  FUN_00ba6d80(void* mgr, cStarRecord* rec);         // 0x00ba6d80
void*  cCivData_GetCities(void* civ);                     // 0x005c65e0
void*  cCivData_GetCitiesOverload(void* civ, float r, void* out); // 0x00b8de30
char   FUN_00fe3b30(void* x);                             // 0x00fe3b30
int    cSPLivingUniverse_GetUniverseContext();            // 0x01021080
void*  cStarManager_GetOrActivatePlanet(void* mgr, cStarRecord* rec); // 0x00bb59b0
void*  BioProtectorSort_op(void* x);                      // 0x00b8de30
void   Matrix3_Assign(void* dst, const void* src);        // 0x0041cb40
void   FUN_01044f80(Deque64<cStarRecord*>* d, int a, int b);// 0x01044f80
void*  operator_new(uint32_t size, const char* name, int a, int b,
                    const char* file, int line);          // 0x00f473a0
void   operator_delete__(void* p);                        // 0x00f47380
int32_t EA_IO_ReadInt32(void* stream, void* dst, int a, int b); // 0x0093a780
void   RBTreeInsert(void* node, RBNode* parent, RBNode** anchor, int side); // 0x009216a0
RBNode* RBTreeIncrement(RBNode* node);                    // 0x00921580
void   RBTreeErase(RBNode* node, RBNode** anchor);        // 0x00921880
RBNode* FUN_010450b0(void* key);                          // 0x010450b0
EffectsMgr* EffectsManagerPtr();                          // 0x0067ddd0
void*  cStarRecordRef_GetCommContext(void* ref);          // 0x00ce6950
char   FUN_01044bf0(cStarMap* self, cStarRecord* rec);    // 0x01044bf0
void*  FUN_01045120(cStarMap* self, void* key, uint32_t id); // 0x01045120
void   FUN_01043d10(void* x);                             // 0x01043d10
void*  cSPLivingUniverse_GetPlayerEmpire();               // 0x01021300
class EmpireContext {
 public:
  void* GetSelectedRecord();                              // 0x00c30c60
};
static cStarRecord** DequeAllocBlock()
{
  return (cStarRecord**)operator_new(0x100, "Simulator", 0, 0, kAllocatorFile, 0xd1);
}
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
class DebugWriter {
 public:
  virtual void Begin(const uint16_t* name);   // +0x00
  virtual void End(const uint16_t* name);     // +0x04
};
bool FUN_00ac8050(DebugWriter* writer, int zero, cStarRecord* rec); // 0x00ac8050
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

// ---- items of slice s01044360 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl SqrtF(float);
namespace SP {
struct Vector3 { float x, y, z; };
}
namespace SP {
struct RBNode_s0104_4360 {
    RBNode_s0104_4360*  mpLeft;       // +0x00
    RBNode_s0104_4360*  mpRight;      // +0x04
    RBNode_s0104_4360*  mpParent;     // +0x08
    uint32_t mColor;       // +0x0c
    uint32_t mPad10;       // +0x10
    uint32_t mValue;       // +0x14
    uint32_t mKey;         // +0x18
    uint32_t mPad1c;       // +0x1c
    uint32_t mPad20;       // +0x20
    uint8_t  mFlags;       // +0x24
    uint8_t  mPad25[3];    // +0x25
};
}
namespace SP {
struct NodeRange_s0104_4360 {
    RBNode_s0104_4360* mpFirst;
    RBNode_s0104_4360* mpSecond;
};
}
namespace SP {
struct RBTree_s0104_4360 {
    uint32_t mPad00;       // +0x00
    RBNode_s0104_4360*  mpEnd;        // +0x04 (sentinel; also the end iterator)
    RBNode_s0104_4360*  mpRoot;       // +0x08
    RBNode_s0104_4360*  mpRightmost;  // +0x0c
    uint32_t mSize;        // +0x10
    uint32_t mPad14;       // +0x14
    uint32_t mPad18;       // +0x18
    uint32_t mPad1c;       // +0x1c
    void equal_range(NodeRange_s0104_4360* out, const uint32_t* key); // 0x00d4b450
};
}
namespace SP {
RBNode_s0104_4360* __cdecl RBTreeIncrement_s0104_4360(RBNode_s0104_4360* node);                                       // 0x00921580
}
namespace SP {
struct cSink;
}
namespace SP {
struct cIOStream {
    void* mpVtable;                                        // +0x00
    cSink* GetSink() {
        return ((cSink* (__thiscall*)(cIOStream*))((void**)mpVtable)[0x20 / 4])(this);
    }
    void* GetStream() {
        return ((void* (__thiscall*)(cIOStream*))((void**)mpVtable)[0x1c / 4])(this);
    }
    void WriteRef(void* value) {
        ((void (__thiscall*)(cIOStream*, void*))((void**)mpVtable)[0x2c / 4])(this, value);
    }
};
}
namespace SP {
struct cSink {
    void* mpVtable;                                        // +0x00
    void* GetStream() {
        return ((void* (__thiscall*)(cSink*))((void**)mpVtable)[0x18 / 4])(this);
    }
};
}
namespace SP {
struct cVarListSerializer_s0104_4360 {
    uint32_t mData[7];                                     // 0x1c bytes
    void Init(void* owner, const void* list, uint32_t line); // 0x00692f90
    bool Serialize(cIOStream* stream);                     // 0x00692900
};
}
namespace SP {
void* __cdecl MemAlloc(uint32_t size, const char* tag, int a, int b,
                       const char* file, uint32_t line);                               // 0x00f473a0
}
namespace SP {
void  __cdecl MemFreeArray(void* p);                                                   // 0x00f47380
}
namespace SP {
void* __cdecl MemCopy(void* dst, const void* src, uint32_t size);                      // 0x011e0744
}
namespace SP {
void* __cdecl MemMove(void* dst, const void* src, uint32_t size);                      // memmove
}
namespace SP {
extern const char  gBannerName;    // 0x016e0688
}
namespace SP {
extern const char  gSerializerList;// 0x015b85a0
}
namespace SP {
extern const char  gAllocatorFile; // 0x013ebb38
}
namespace SP {
extern const char  gAllocatorTag;  // 0x013f09b4 ("Simulator")
}
namespace SP {
extern const char  gEntryName;     // 0x0179c807
}
namespace SP {
struct cEmbeddedSource {
    void* mpVtable;                                        // +0x00
    void* GetKey() {
        return ((void* (__thiscall*)(cEmbeddedSource*))((void**)mpVtable)[0x2c / 4])(this);
    }
    Vector3* GetPosition() {
        return ((Vector3* (__thiscall*)(cEmbeddedSource*))((void**)mpVtable)[0x2c / 4])(this);
    }
};
}
namespace SP {
struct cItemOwner {
    void* mpVtable;                                        // +0x00
    bool HasItem(const void* id) {
        return ((bool (__thiscall*)(cItemOwner*, const void*))
            ((void**)mpVtable)[0x74 / 4])(this, id);
    }
};
}
namespace SP {
struct cPlayerInventory {
    cItemOwner* mpOwner;                                   // +0x00
    uint32_t mPad04[0x30 / 4];                             // +0x04
    cEmbeddedSource mKeySource;                            // +0x34
};
}
namespace SP {
struct cStarMapView {
    void* mpVtable;                                        // +0x00
    long long GetId() {
        return ((long long (__thiscall*)(cStarMapView*))((void**)mpVtable)[0x60 / 4])(this);
    }
};
}
namespace SP {
struct cMiniCaptureHost {
    cStarMapView* mpView;                                  // +0x00
};
}
namespace SP {
struct cBannerList {
    void* mpVtable;                                        // +0x00
    int FindEntry(uint32_t key);                           // 0x00ba6d80
    void Reset();                                          // 0x00ba6490
};
}
namespace SP {
struct cProperty {
    void* mpVtable;                                        // +0x00
    uint8_t mPad04[0x0e];                                  // +0x04
    uint16_t mType;                                        // +0x12
    bool Query(uint32_t id, cProperty** out) {
        return ((bool (__thiscall*)(cProperty*, uint32_t, cProperty**))
            ((void**)mpVtable)[0x24 / 4])(this, id, out);
    }
    int* GetInt();                                         // 0x0041e990
    float* GetFloat();                                     // 0x0041ea70
};
}
namespace SP {
struct cPropertyManager_s0104_4360 {
    void* mpVtable;                                        // +0x00
    void GetProperty(uint32_t a, uint32_t b, cProperty** out) {
        ((void (__thiscall*)(cPropertyManager_s0104_4360*, uint32_t, uint32_t, cProperty**))
            ((void**)mpVtable)[0x2c / 4])(this, a, b, out);
    }
};
}
namespace SP {
void* __cdecl GetUFOSimulator();                           // 0x00ffbe50
}
namespace SP {
cPropertyManager_s0104_4360* __cdecl PropertyManager();               // 0x0067de30
}
namespace SP {
void __cdecl FUN_00feb060(const void* table);              // 0x00feb060
}
namespace SP {
cBannerList* __cdecl StarManager_s0104_4360();                        // 0x00b3d2a0
}
namespace SP {
float __cdecl FUN_00c8c5d0(int index, float* out);         // 0x00c8c5d0
}
namespace SP {
void __cdecl WriteUint32(void* stream, const uint32_t* value,
                         int count, int flags);            // 0x0093aa70
}
namespace SP {
struct cSPSimulatorSpaceGame {
    void* mpVtable;                                        // +0x00
    cPlayerInventory* GetPlayerInventory();                // 0x00a1ad60
    float GetMaxZ();                                       // 0x00ffbfd0
};
}
namespace SP {
struct cCivData_s0104_4360 {
    void* mpVtable;                                        // +0x00
    float* GetCities();                                    // 0x005c65e0
    float* GetCityPosition();                              // 0x005c65e0
};
}
namespace SP {
struct cPlayerCityData {
    uint32_t mPad00[0x718 / 4];                            // +0x00
    Vector3  mCityPosition;                                // +0x718
};
}
namespace SP {
 bool __stdcall UpdateMiniCaptureBar(cMiniCaptureHost* self, float value);   // 0x01044b00 (defined below; used by a stub's inline body)
}
namespace SP {
struct cStarMap_s0104_4360 {
    uint8_t       mFirstFlag;          // +0x00
    bool          mRequestZoom;        // +0x01
    uint8_t       mPad02[2];           // +0x02
    uint32_t      mSlots[8];           // +0x04
    uint32_t      mPad24[0x28 / 4];    // +0x24 .. +0x4b
    float         mZoomRequestHeight;  // +0x4c
    int           mTravelTrailLength;  // +0x50
    uint32_t      mPad54;              // +0x54
    RBTree_s0104_4360        mTree;               // +0x58
    uint32_t      mVisualCount;        // +0x74

    uint32_t* FindNode(int key);
uint32_t* FindNodeValue(int key);
void SetNodeFlag(int key, char on);
    void SetNodeFlag2(int key, char on);
    void SyncEntryFlags(char enable);
    bool IsSlotSet(int index);
    void Notify(int id, char flag);
    void UpdateDesiredCamera();  // 0x01044b70 (SP::cStarMap::UpdateDesiredCamera)
    bool UpdateMiniCaptureBar(float value);  // 0x01044b00 (SP::cStarMap::UpdateMiniCaptureBar)
    void Init();  // 0x01044c60 (SP::cStarMap::Init)
    void SerializeSlots(cIOStream* stream);
    uint32_t FindValue(uint32_t bucket, int key);
    uint32_t FindEntryByLongId(uint32_t key, uint32_t lo, uint32_t hi);
};
}
namespace SP {
struct cFlagGrid {
    uint32_t mPad00;                   // +0x00
    uint32_t mPad04;                   // +0x04
    int*     mpBegin;                  // +0x08
    uint32_t mPad0c;                   // +0x0c
    int*     mpRowEnd;                 // +0x10
    int**    mpRowBase;                // +0x14
    int*     mpEnd;                    // +0x18
    int*     mpEndCap;                 // +0x1c
    uint32_t mPad20;                   // +0x20
    int*     mpLastRowEnd;             // +0x24
};
}
namespace SP {
struct cBitVector {
    uint32_t* mpData;                  // +0x00
    uint32_t  mCapacity;               // +0x04
    uint32_t  mPad08;                  // +0x08
    uint32_t  mFirstValue;             // +0x0c
    uint32_t  mFirstCap;               // +0x10
    uint32_t* mpBegin;                 // +0x14
    uint32_t  mPad18;                  // +0x18
    uint32_t  mLastValue;              // +0x1c
    uint32_t  mLastCap;                // +0x20
    uint32_t* mpEnd;                   // +0x24
    void __thiscall InsertAtFront(uint32_t count, uint32_t value);
};
}
namespace SP {
struct cFlagEntry {
    void* mpVtable;                    // +0x00
    void SerializeInto(void* stream) {
        ((void (__thiscall*)(cFlagEntry*, void*))((void**)mpVtable)[0x1c / 4])(this, stream);
    }
    void* GetName(const void* id) {
        return ((void* (__thiscall*)(cFlagEntry*, const void*))
            ((void**)mpVtable)[0x0c / 4])(this, id);
    }
};
}
namespace SP {
struct cFlagObj {
    void* mpVtable;                    // +0x00
    void AddRef() {
        ((void (__thiscall*)(cFlagObj*))((void**)mpVtable)[0x00 / 4])(this);
    }
};
}
namespace SP {
struct SharedRefSrc {
    uint32_t  mValue;                  // +0x00
    cFlagObj* mpRef;                   // +0x04
    uint32_t  mA;                      // +0x08
    uint32_t  mB;                      // +0x0c
    uint32_t  mC;                      // +0x10
    uint8_t   mD;                      // +0x14
};
}
namespace SP {
struct SharedRefData {
    uint32_t  mValue;                  // +0x00
    cFlagObj* mpRef;                   // +0x04
    uint32_t  mA;                      // +0x08
    uint32_t  mB;                      // +0x0c
    uint32_t  mC;                      // +0x10
    uint8_t   mD;                      // +0x14
};
}
namespace SP {
struct SharedRefBlock {
    uint32_t      mHeader[4];          // +0x00 .. +0x0f
    SharedRefData mData;               // +0x10
};
}
// ---- items of slice s01044360 end

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

// @ 0x01044a70
namespace SP {
void cStarMap_s0104_4360::SerializeSlots(cIOStream* stream)
{
    for (int i = 0; i < 7; ++i) {
        uint32_t value = mSlots[i];
        cSink* sink = stream->GetSink();
        WriteUint32(sink->GetStream(), &value, 1, 0);
    }
    cVarListSerializer_s0104_4360 serializer;
    serializer.Init(this, &gSerializerList, 0x1a80d26);
    serializer.Serialize(stream);
}
}  // namespace SP

// @ 0x01044b00
namespace SP {
bool __stdcall UpdateMiniCaptureBar(cMiniCaptureHost* self, float value)
{
    cBannerList* list = StarManager_s0104_4360();
    int index = list->FindEntry(*(uint32_t*)&value);
    float ratio = -1.0f;
    StarManager_s0104_4360()->Reset();
    long long id = self->mpView->GetId();
    if ((uint32_t)id == 0xff8bbb2b && (uint32_t)(id >> 32) == 0xffffffff)
        ratio = FUN_00c8c5d0(index, &ratio);
    return !(0.0f < ratio);
}
}  // namespace SP

// @ 0x01044bf0
namespace SP {
bool __cdecl FUN_01044bf0(cCivData_s0104_4360* civData)
{
    cSPSimulatorSpaceGame* simulator = (cSPSimulatorSpaceGame*)GetUFOSimulator();
    float maxZ = simulator->GetMaxZ();
    cPlayerCityData* inventory = (cPlayerCityData*)simulator->GetPlayerInventory();
    float* city = civData->GetCities();
    float dx = city[0] - inventory->mCityPosition.x;
    float dy = city[1] - inventory->mCityPosition.y;
    float dz = city[2] - inventory->mCityPosition.z;
    float dist = SqrtF(dy * dy + (dz * dz + dx * dx));
    return dist < maxZ;
}
}  // namespace SP

// @ 0x01044c60
namespace SP {
void cStarMap_s0104_4360::Init()
{
    mVisualCount = 0;
    FUN_00feb060(&gBannerName);
    cProperty* property = 0;
    cPropertyManager_s0104_4360* manager = PropertyManager();
    if (property) {
        property->mpVtable = 0;
    }
    manager->GetProperty(0xddb63e53, 0x2ae0c7e, &property);
    if (!property)
        return;
    cProperty* value = 0;
    if (property->Query(0x2ba603e, &value)) {
        if (value->mType == 9)
            mTravelTrailLength = *value->GetInt();
    }
    cProperty* zoom = 0;
    if (property->Query(0x54030ee, &zoom)) {
        if (zoom->mType == 0xd)
            mZoomRequestHeight = *zoom->GetFloat();
    }
    ((void (__thiscall*)(cProperty*))((void**)property->mpVtable)[1])(property);
}
}  // namespace SP

// @ 0x01044d30
namespace SP {
uint32_t* cStarMap_s0104_4360::FindNode(int key)
{
    RBNode_s0104_4360* end = (RBNode_s0104_4360*)&mTree.mpEnd;
    RBNode_s0104_4360* node = mTree.mpRoot;
    if (node != end) {
        do {
            if (key == (int)node->mKey)
                return &node->mValue;
            node = RBTreeIncrement_s0104_4360(node);
        } while (node != end);
    }
    return 0;
}
}  // namespace SP

// @ 0x01044d70
namespace SP {
void cStarMap_s0104_4360::SetNodeFlag(int key, char on)
{
    RBNode_s0104_4360* end = (RBNode_s0104_4360*)&mTree.mpEnd;
    RBNode_s0104_4360* node = mTree.mpRoot;
    if (node != end) {
        do {
            if (key == (int)node->mKey) {
                if (on)
                    node->mFlags &= (uint8_t)~8u;
                else
                    node->mFlags |= 8;
                return;
            }
            node = RBTreeIncrement_s0104_4360(node);
        } while (node != end);
    }
}
}  // namespace SP

// @ 0x01044db0
namespace SP {
void cStarMap_s0104_4360::SetNodeFlag2(int key, char on)
{
    RBNode_s0104_4360* end = (RBNode_s0104_4360*)&mTree.mpEnd;
    RBNode_s0104_4360* node = mTree.mpRoot;
    if (node != end) {
        do {
            if (key == (int)node->mKey) {
                if (on)
                    node->mFlags &= (uint8_t)~4u;
                else
                    node->mFlags |= 4;
                return;
            }
            node = RBTreeIncrement_s0104_4360(node);
        } while (node != end);
    }
}
}  // namespace SP

// @ 0x01044df0
namespace SP {
void cStarMap_s0104_4360::SyncEntryFlags(char enable)
{
    RBNode_s0104_4360* end = (RBNode_s0104_4360*)&mTree.mpEnd;
    for (RBNode_s0104_4360* node = mTree.mpRoot; node != end; node = RBTreeIncrement_s0104_4360(node)) {
        if ((node->mKey == 0x70930c64 || node->mKey == 0x166521a5)
            && ((bool)enable != ((node->mFlags & 8) != 8))) {
            uint32_t key = node->mKey;
            RBNode_s0104_4360* other = mTree.mpRoot;
            while (other != end) {
                if (key == other->mKey) {
                    if (enable)
                        other->mFlags &= (uint8_t)~8u;
                    else
                        other->mFlags |= 8;
                    break;
                }
                other = RBTreeIncrement_s0104_4360(other);
            }
        }
    }
}
}  // namespace SP

// @ 0x01044e70
namespace SP {
void __cdecl SerializeFlagGrid(cIOStream* stream, const cFlagGrid* grid)
{
    int rows = (((int)grid->mpLastRowEnd - (int)grid->mpRowBase) >> 2) - 1;
    int cols = ((int)grid->mpEnd - (int)grid->mpEndCap) >> 2;
    int width = ((int)grid->mpRowEnd - (int)grid->mpBegin) >> 2;
    uint32_t index = (uint32_t)(rows * 0x40 + cols + width);
    cSink* sink = stream->GetSink();
    void* out = sink->GetStream();
    WriteUint32(out, &index, 1, 0);

    int* it = grid->mpBegin;
    int* rowEnd = grid->mpRowEnd;
    int** rowBase = grid->mpRowBase;
    int* last = grid->mpEnd;
    while (it != last) {
        void* value = 0;
        if (*it)
            value = ((cFlagEntry*)*it)->GetName(&gEntryName);
        stream->WriteRef(value);
        ++it;
        if (it == rowEnd) {
            it = rowBase[1];
            ++rowBase;
            rowEnd = it + 0x40;
        }
    }
    ((void (__thiscall*)(cIOStream*))((void**)stream->mpVtable)[0x1c / 4])(stream);
}
}  // namespace SP

// @ 0x01044f30
namespace SP {
bool __cdecl ForEachFlagEntry(void* stream, const cFlagGrid* grid)
{
    int* rowEnd = grid->mpRowEnd;
    int* last = grid->mpEnd;
    int* it = grid->mpBegin;
    int** rowBase = grid->mpRowBase;
    while (it != last) {
        if (*it)
            ((cFlagEntry*)*it)->SerializeInto(stream);
        ++it;
        if (it == rowEnd) {
            it = rowBase[1];
            ++rowBase;
            rowEnd = it + 0x40;
        }
    }
    return true;
}
}  // namespace SP

// @ 0x01044f80
namespace SP {
void __thiscall cBitVector::InsertAtFront(uint32_t count, uint32_t value)
{
    uint32_t used = (uint32_t)(mpEnd - mpBegin);
    uint32_t newSize = used + 1 + count;
    uint32_t* dst;
    if (mCapacity > newSize * 2) {
        dst = mpData + (mCapacity - newSize) / 2 + (value ? count : 0);
        if (dst < mpBegin)
            MemCopy(dst, mpBegin, (used + 1) * 4);
        else
            MemMove(dst + (newSize - (used + 1)), mpBegin, (used + 1) * 4);
    } else {
        uint32_t capacity = (mCapacity > count ? mCapacity : count) + mCapacity + 2;
        uint32_t* data = (uint32_t*)MemAlloc(capacity * 4, &gAllocatorTag, 0, 0,
                                             &gAllocatorFile, 0xd1);
        dst = data + (mpBegin - mpData) + (value ? count : 0);
        if (mpData)
            MemCopy(dst, mpBegin, (used + 1) * 4);
        if (mpData)
            MemFreeArray(mpData);
        mpData = data;
        mCapacity = capacity;
    }
    mpBegin = dst;
    mFirstValue = *dst;
    mFirstCap = mFirstValue + 0x100;
    mpEnd = dst + used;
    mLastValue = *mpEnd;
    mLastCap = mLastValue + 0x100;
}
}  // namespace SP

// @ 0x010450b0
namespace SP {
SharedRefBlock* __stdcall AllocSharedRef(const SharedRefSrc* source)
{
    SharedRefBlock* block = (SharedRefBlock*)MemAlloc(0x28, &gAllocatorTag, 0, 0,
                                                      &gAllocatorFile, 0xd1);
    SharedRefData* target = &block->mData;
    if (target) {
        target->mValue = source->mValue;
        target->mpRef = source->mpRef;
        if (target->mpRef)
            target->mpRef->AddRef();
        target->mA = source->mA;
        target->mB = source->mB;
        target->mC = source->mC;
        target->mD = source->mD;
    }
    return block;
}
}  // namespace SP

// @ 0x01045120
namespace SP {
uint32_t cStarMap_s0104_4360::FindValue(uint32_t bucket, int key)
{
    if (bucket == 0) {
        uint32_t* value = FindNode(key);
        if (value)
            return *value;
        return 0;
    }
    NodeRange_s0104_4360 range;
    mTree.equal_range(&range, &bucket);
    for (RBNode_s0104_4360* node = range.mpFirst; node != range.mpSecond; node = RBTreeIncrement_s0104_4360(node)) {
        if ((int)node->mKey == key)
            return node->mValue;
    }
    return 0;
}
}  // namespace SP

// @ 0x01045190
namespace SP {
uint32_t cStarMap_s0104_4360::FindEntryByLongId(uint32_t key, uint32_t lo, uint32_t hi)
{
    NodeRange_s0104_4360 range;
    mTree.equal_range(&range, &key);
    RBNode_s0104_4360* node = range.mpFirst;
    RBNode_s0104_4360* end = range.mpSecond;
    if (node != end) {
        do {
            unsigned long long id = (unsigned long long)((cStarMapView*)node->mValue)->GetId();
            if ((uint32_t)id == lo && (uint32_t)(id >> 32) == hi)
                return node->mValue;
            node = RBTreeIncrement_s0104_4360(node);
        } while (node != end);
    }
    return 0;
}
}  // namespace SP

// @ 0x01045200
void cStarMap::BuildVisual(VisualCtx* ctx, void* object)
{
  cStarRecord* rec = (cStarRecord*)object;
  float x, y, z;

  if (ctx->mKind == 0) {
    void* mgr = StarManager(rec);
    void* civ = FUN_00ba6dc0(mgr, rec);
    if (FUN_00fe3b30(civ) != 0 &&
        cSPLivingUniverse_GetUniverseContext() == 1) {
      void* planet = cStarManager_GetOrActivatePlanet(FUN_00ba6dc0(mgr, rec), rec);
      VEffect* vis = (VEffect*)planet;
      const Vector3_s0104_5200* p = (const Vector3_s0104_5200*)vis;
      x = p->x; y = p->y; z = p->z;
      if (vis != 0)
        vis->Detach();
    } else {
      void* civ2 = BioProtectorSort_op(civ);
      const Vector3_s0104_5200* p = (const Vector3_s0104_5200*)cCivData_GetCities(civ2);
      x = p->x; y = p->y; z = p->z;
    }
  } else if (ctx->mKind == 1) {
    void* mgr = StarManager(rec);
    void* civ = FUN_00ba6d80(mgr, rec);
    const Vector3_s0104_5200* p = (const Vector3_s0104_5200*)cCivData_GetCities(civ);
    x = p->x; y = p->y; z = p->z;
  } else {
    x = y = z = 0.0f;
  }

  struct RenderBlock {
    uint16_t mFlags;
    int16_t  mCount;
    float    mPosX, mPosY, mPosZ;
    float    mScale;
    float    mMatrix[9];
  } block;

  block.mPosX = gVisualPosX;
  block.mPosY = gVisualPosY;
  block.mPosZ = gVisualPosZ;
  block.mCount = 0;
  block.mFlags = 0;
  block.mScale = kRealOne;
  Matrix3_Assign(&block.mMatrix[0], &gMatrixDefault);
  block.mFlags |= 4;
  block.mCount = (int16_t)(block.mCount + 1);

  if (ctx->mpEffect != 0) {
    block.mPosX = x;
    block.mPosY = y;
    block.mPosZ = z;
    ctx->mpEffect->SetTransform(&block);
  }
}

// @ 0x01045370
void FUN_01045370(Deque64<cStarRecord*>* d, cStarRecord** value)
{
  cStarRecord* v = *value;
  if ((int)(((char*)d->mItEnd.mpCurrentArrayPtr - (char*)d->mpPtrArray) >> 2) + 1
      >= (int)d->mnPtrArraySize)
    FUN_01044f80(d, 1, 1);

  cStarRecord** block = DequeAllocBlock();
  d->mItEnd.mpCurrentArrayPtr[1] = block;
  if (d->mItEnd.mpCurrent != 0)
    *d->mItEnd.mpCurrent = v;

  cStarRecord*** cur = d->mItEnd.mpCurrentArrayPtr;
  d->mItEnd.mpCurrentArrayPtr = cur + 1;
  block = cur[1];
  d->mItEnd.mpBegin = block;
  d->mItEnd.mpEnd = block + 0x40;
  d->mItEnd.mpCurrent = d->mItEnd.mpBegin;
}

// @ 0x010453f0
void FUN_010453f0(SeqReader* reader, Deque64<cStarRecord*>* d)
{
  DequeClear(d);

  uint32_t count = 0;
  SeqStream* stream = reader->Stream();
  EA_IO_ReadInt32(stream->Handle(), &count, 1, 0);

  for (uint32_t i = 0; i < count; ++i) {
    cStarRecord* rec = (cStarRecord*)reader->ReadItem();
    if (d->mItEnd.mpCurrent + 1 == d->mItEnd.mpEnd) {
      FUN_01045370(d, &rec);
    } else {
      cStarRecord** slot = d->mItEnd.mpCurrent;
      d->mItEnd.mpCurrent = slot + 1;
      if (slot != 0)
        *slot = rec;
    }
  }
  reader->End();
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

// @ 0x010455e0
byte FUN_010455e0(DebugWriter* writer, const char* label, Deque64<cStarRecord*>* dq)
{
  byte ok = 1;
  if (dq->mItBegin.mpCurrent == dq->mItEnd.mpCurrent)
    return ok;

  const uint16_t* name = (label != 0) ? (const uint16_t*)label
                                      : (const uint16_t*)L"list";
  writer->Begin(name);

  cStarRecord** it = dq->mItBegin.mpCurrent;
  cStarRecord** blockEnd = dq->mItBegin.mpEnd;
  cStarRecord*** blockPtr = dq->mItBegin.mpCurrentArrayPtr;
  cStarRecord** end = dq->mItEnd.mpCurrent;

  while (it != end) {
    if (ok)
      ok = FUN_00ac8050(writer, 0, *it) ? 1 : 0;
    else
      ok = 0;

    ++it;
    if (it == blockEnd) {
      it = blockPtr[1];
      ++blockPtr;
      blockEnd = it + 0x40;
    }
  }
  writer->End(name);
  return ok;
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

// @ 0x01045c80
void cStarMap::FilterHelperTravelTrail(int filter)
{
  Deque64<cStarRecord*>& q = this->mTravelTrail;
  uint32_t count = (uint32_t)(((q.mItEnd.mpCurrentArrayPtr - q.mItBegin.mpCurrentArrayPtr) >> 2) - 1) * 0x40
                 + (uint32_t)((q.mItEnd.mpCurrent - q.mItEnd.mpBegin) >> 2)
                 + (uint32_t)((q.mItBegin.mpEnd - q.mItBegin.mpCurrent) >> 2);
  if (count <= 1)
    return;

  cStarRecord** it = q.mItEnd.mpCurrent;
  cStarRecord** beginBlock = q.mItEnd.mpBegin;
  cStarRecord** endBlock = q.mItEnd.mpEnd;
  cStarRecord*** blockPtr = q.mItEnd.mpCurrentArrayPtr;
  cStarRecord* prev = 0;
  int index = 0;

  while (it != q.mItBegin.mpCurrent) {
    cStarRecord** cur = it;
    if (it == beginBlock) {
      cur = blockPtr[-1] + 0x40;
    }
    cStarRecord* rec = cur[-1];
    if (it == beginBlock) {
      beginBlock = blockPtr[-1];
      blockPtr = blockPtr - 1;
      it = beginBlock + 0x40;
      endBlock = it;
    }
    it = it - 1;
    if (it == q.mItBegin.mpCurrent)
      break;

    cur = it;
    if (it == beginBlock)
      cur = blockPtr[-1] + 0x40;
    cStarRecord* next = cur[-1];
    if (rec != next) {
      uint32_t id = this->mVisualCount;
      this->mVisualCount = id + 1;

      VEffect* eff = 0;
      if (filter == 0x166521a5 || filter == 0x70930c64 ||
          filter == (int)0xc3f6ca28 || FUN_01044bf0(this, rec) != 0) {
        EffectsMgr* mgr = EffectsManagerPtr();
        if (mgr->Create(0x3ab4709, 0, &eff)) {
          eff->SetVisible(false);
          VisualCtx ctx;
          ctx.mpEffect = 0;
          ctx.mPad04 = 0;
          ctx.mPad08 = 0;
          ctx.mKind = 0;
          BuildVisual(&ctx, rec);

          RBNode node;
          node.mpKey = (void*)id;
          node.mValue.mpObject = eff;
          node.mValue.mGroup = 0;
          node.mValue.mFlags = 0;
          DoInsertValueImpl(&this->mObjectVisuals, (const void*)id, &node.mValue, 0);

          if (id != 0) {
            VEffect* obj = (VEffect*)FUN_01045120(this, rec->mpInstance, id);
            if (obj != 0) {
              float f = ((float)index / this->mTravelTrailLength) * -0.45f + 0.5f;
              obj->SetParam(4, &f, 1);
              void* cities = 0;
              cCivData_GetCitiesOverload((void*)rec, 0.1f, &cities);
              FUN_01043d10(cities);
              obj->SetParam(0xd, cities, 0);
            }
          }
        }
      }
      ++index;
    }
  }
}

// @ 0x01045f90
void cStarMap::FilterHelperVisited(uint32_t filter)
{
  PtrVector visited;
  visited.mpBegin = 0;
  visited.mpEnd = 0;
  visited.mpCap = 0;

  FUN_00b3d2a0(&visited);
  if (FUN_00baf460(&visited) != 0) {
    for (void** p = visited.mpBegin; p != visited.mpEnd; ++p) {
      cStarRecord* rec = (cStarRecord*)*p;
      uint32_t id = this->mVisualCount;
      this->mVisualCount = id + 1;
      void* instance = rec->mpInstance;

      VEffect* eff = 0;
      if (filter == 0x166521a5 || filter == 0x70930c64 ||
          filter == (uint32_t)0xc3f6ca28 || FUN_01044bf0(this, rec) != 0) {
        EffectsMgr* mgr = EffectsManagerPtr();
        if (eff != 0) {
          eff->Release();
          eff = 0;
        }
        if (mgr->Create(0xbfdea3f7, 0, &eff)) {
          eff->SetVisible(false);
          VisualCtx ctx;
          ctx.mpEffect = eff;
          ctx.mPad04 = 0;
          ctx.mPad08 = 0;
          ctx.mKind = 0;
          BuildVisual(&ctx, instance);

          RBNode node;
          node.mpKey = instance;
          node.mValue.mpObject = eff;
          node.mValue.mGroup = filter;
          node.mValue.mFlags = 0;
          if (eff != 0)
            eff->v00();                 // AddRef before publishing
          DoInsertValueImpl(&this->mObjectVisuals, instance, &node.mValue, 0);
          if (eff != 0)
            eff->Release();
        }
      }
      if (eff != 0)
        eff->Release();
    }
  }

  for (void** p = visited.mpBegin; p != visited.mpEnd; ++p) {
    cStarRecord* rec = (cStarRecord*)*p;
    if (rec != 0)
      rec->Release();
  }
  if (visited.mpBegin != 0 && ((uint32_t*)visited.mpBegin)[-1] != 0)
    operator_delete__(visited.mpBegin);
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
