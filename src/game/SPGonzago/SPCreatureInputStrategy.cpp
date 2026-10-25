// src/game/SPGonzago/SPCreatureInputStrategy.cpp -- migrated from slice(s) s00d366c0, s00d35190, s00d34f90, s00d31a70, s00d311b0, s00d30830, s00d2f940, s00d2ec50, s00d2dd20, s00b1a7b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureInputStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "cSPUILayout.h"
#include "SP/cSPUINewProgressBar.h"
#include "SP/cTerrainSphere.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <string.h>
#include "SP/cLocomotiveObject.h"
#include "SP/cViewer.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpatialObject.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cSPTimer.h"
#include "SP/cMWModel.h"
#include "SP/cRenderer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern void* gScriptOwner;       // 0x0167be94
#pragma intrinsic(memcpy)

// ---- items of slice s00b1a7b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete[](void* p);  // 0x00f47380
struct RBNodeBase {
  RBNodeBase* mpNodeRight;   // +0
  RBNodeBase* mpNodeLeft;    // +4
  RBNodeBase* mpNodeParent;  // +8
  char mColor;               // +0xc
};
struct string16 {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  ~string16() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) delete[] mpBegin;
  }
};
struct ResourceKey { unsigned instanceID, typeID, groupID; };
#define PV(n) virtual void pv##n();
struct IArgScriptParser {
  PV(0) PV(1)
  virtual void Reset();                                  // +8
  PV(3) PV(4)
  virtual void Declare(const char* name, void* owner);   // +0x14
  PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void Parse(void* stream);                      // +0x3c
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
  virtual void SetCheats(void* p);                       // +0xbc
};
struct IResourceManager {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  virtual void MakeKey(ResourceKey* out, const wchar_t* name, unsigned type, unsigned group);  // +0x78
};
struct ICheatInner {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
  PV(47) PV(48)
  virtual void* GetCheatTable();  // +0xc4
};
struct ICheatManager {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual ICheatInner* GetInner();  // +0x38
};
IArgScriptParser* CreateParser();                               // 0x008408d0 (EA::ArgScript::CreateParser)
IResourceManager* GetManager();                                 // 0x0067dcd0
ICheatManager* CheatManager();                                  // 0x0067de20
string16* __cdecl ConvertToString16(string16* out, const char* in, int n);  // 0x0093c5a0
void* __cdecl OpenRecordAsStream(ResourceKey* key, void** outStream);       // 0x00686490
void __cdecl EraseEntry(void* rec);                                         // 0x006861d0
struct ParserPtrVector {
  IArgScriptParser** mpBegin;
  IArgScriptParser** mpEnd;
  IArgScriptParser** mpCapacity;
  ParserPtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~ParserPtrVector() { if (mpBegin) delete[] mpBegin; }
  void __thiscall DoInsertValue(IArgScriptParser** position, IArgScriptParser* const& value);  // 0x00b96600
  void push_back(IArgScriptParser* const& value) {
    if (mpEnd < mpCapacity) {
      IArgScriptParser** p = mpEnd;
      ++mpEnd;
      if (p) *p = value;
    } else {
      DoInsertValue(mpEnd, value);
    }
  }
};
struct StrNukeMap {
  int mDummy;
  RBNodeBase mAnchor;
  unsigned mnSize;
  void __thiscall DoNuke(RBNodeBase* pNode);  // 0x00e84940
};
extern StrNukeMap gScriptNames;  // 0x015682ec
extern void* gScriptOwner;       // 0x0167be94
extern IArgScriptParser* gScriptParser;  // 0x0167be98
struct cStateMachineHost {
  char pad[0x10];
  struct { char pad[0x30]; void* mpOwner; }* mpInfo;  // +0x10
  void LoadStateMachine(const char* name);           // 0x00b1b410
};
    void operator delete(void*); // 0x00f47380
// ---- items of slice s00b1a7b0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern StrNukeMap gScriptNames;  // 0x015682ec
extern IArgScriptParser* gScriptParser;  // 0x0167be98

// ---- items of slice s00d2dd20 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
#pragma pack(pop)
class cGameInputManager {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual bool IsKeyDown(int key);             // +0x18
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual int  FUN_0034();                     // +0x34
    virtual void FUN_0038(int mode);             // +0x38
};
cGameInputManager* GameInputManager();           // 0x00b3d250
bool IsModifierKeyDown(int key);                 // 0x008d2fb0
class cSub128 {
public:
    void FUN_00d2d560(float value);              // 0x00d2d560
    void FUN_00d2d0b0(int tick);                 // 0x00d2d0b0
};
class cCreatureModeEventSink {
public:
    __declspec(noinline) void Update(float value);   // 0x00d2e2e0  (this file)

    unsigned char mPad00[0x128];
    cSub128       mSub;      // +0x128
};
class cPropertyList;
class cCreatureModeStrategy {
public:
    static cCreatureModeStrategy* Instance();                 // 0x00d38840
    static void NotifyEvent(float amount);                    // 0x00d2e8a0  (this file)
    void FUN_00d39360(unsigned int id, void* data);           // 0x00d39360

    unsigned char           mPad00[0x68];
    cCreatureModeEventSink* mpSink;       // +0x68
    unsigned char           mPad6c[0xb4 - 0x6c];
    cPropertyList*          mpPropList;   // +0xb4
};
class cCreatureModeInputStrategy {
public:
    void* AsInterface(unsigned int iid);   // 0x00d2ea80  (this file)
    bool  IsStrafeLeftDown();              // 0x00d2eab0  (this file)
    bool  IsStrafeRightDown();             // 0x00d2eaf0  (this file)

    unsigned char mPad00[8];
    unsigned char mIface8;                 // +0x08
};
void  ToggleBanningContent(void* arg);                   // 0x00dd17f0
void  EndBanMode(int arg);                               // 0x00dd1840
void  FUN_00e099d0(void* arg);                           // 0x00e099d0
void  FUN_00e09a50(void* arg);                           // 0x00e09a50
void  SPUIHelpers_EndModal(void* window, int a, int b);  // 0x00809c50
// ---- items of slice s00d2dd20 end

// ---- items of slice s00d2ec50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __stdcall FUN_00b3d320(void*, int);
#pragma warning(disable : 4100)
typedef unsigned int  u32;
typedef unsigned char u8;
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct IRefCount {                                       // +0x00 AddRef, +0x04 Release
    virtual void AddRef();
    virtual void Release();
};
struct IVtB8 : VPad<46, IEmpty> {                        // +0xb8
    virtual void* v_b8(u32);
};
struct cMgr {
    void* FUN_00b1daf0();                                // 0x00b1daf0 (GameModeMgr)
};
// ---- items of slice s00d2ec50 end

// ---- items of slice s00d2f940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gFlag01582df6;                       // 0x01582df6
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV_s00d2_f940 virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV_s00d2_f940 PV_s00d2_f940
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Vec3 { float x, y, z; };
struct Matrix3 { float m[9]; };
struct BBox { Vec3 mMin, mMax; };
struct cSPTransform_s00d2_f940 {
    uint16_t mFlags;
    uint16_t mModCount;
    Vec3     mOffset;
    float    mScale;
    Matrix3  mRotation;
    cSPTransform_s00d2_f940();                         // 0x00409930
    void SetOffset(const Vec3& v) { mOffset = v; mFlags |= 4; mModCount++; }
    void SetOffsetOOL(const Vec3* v);       // 0x00571d40 (out-of-line copy)
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; mModCount++; }
};
struct XformMsg {
    uint16_t mFlags;
    uint16_t mCount;
    Vec3     mPos;
    float    mScale;
    Matrix3  mRot;
    XformMsg();                             // 0x00434040
    void SetPos(const Vec3& v)  { mPos = v; mFlags |= 4; ++mCount; }
    void SetScale(float s)      { mScale = s; ++mCount; }
    void SetRot(const Matrix3& m) { mRot = m; mFlags |= 2; ++mCount; }
};
struct cSpatialObject {
    PV8 PV8 PV4 PV2
    virtual bool VSlot58();                 // 0x58
    PV4
    virtual BBox GetBBox();                 // 0x6c (struct returned through a hidden pointer)
    void LocalToWorldTransform(cSPTransform_s00d2_f940* out);   // 0x00c897e0
};
struct IVisualEffect {
    virtual void AddRef();
    virtual void Release();
    virtual void Start(int hard);           // 0x08
    virtual void Stop(int hard);            // 0x0c
virtual void v10();
virtual void v14();
    virtual void SetSourceTransform(XformMsg* m);    // 0x18
};
struct EffectPtr {
    IVisualEffect* p;
    EffectPtr() : p(0) {}
    EffectPtr(IVisualEffect* q) : p(q) { if (p) p->AddRef(); }
    ~EffectPtr() { if (p) p->Release(); }
    void reset() { IVisualEffect* q = p; if (q) { p = 0; q->Release(); } }
    EffectPtr& operator=(const EffectPtr& o);        // 0x00ac9480
};
struct IEffectsManager {
    PV8 PV2 PV_s00d2_f940
    virtual bool CreateEffect(uint32_t id, uint32_t group, EffectPtr* out);   // 0x2c
};
IEffectsManager* __cdecl EffectsManager();           // 0x0067ddd0
struct cPlanetModel {
    Vec3* SnapA(Vec3* out, const Vec3* in, int flag);     // 0x00b82b40
    Vec3* SnapB(Vec3* out, const Vec3* in, int flag);     // 0x00b82970
    Vec3* Facing(Vec3* out, const Vec3* in);              // 0x00b7e3b0
};
cPlanetModel* __cdecl PlanetModel();                      // 0x00b3d350
void __cdecl normalized_safe(Vec3* out, const Vec3* in);  // 0x00449c20
void __cdecl OrthogonalVector(Vec3* out, const Vec3* in);         // 0x006985b0
void __cdecl Matrix3FromFacingAndUp(Matrix3* out, const Vec3* f, const Vec3* up);   // 0x0069b440
struct ObjHdr {
    PV_s00d2_f940 PV_s00d2_f940 PV_s00d2_f940
    virtual void* Query(uint32_t id);       // 0x0c
    PV4
    virtual uint32_t GetTypeID();           // 0x20
    PV2
    virtual bool IsDestroyed();             // 0x2c
};
void* __cdecl ObjCast(ObjHdr* obj, uint32_t typeId);      // 0x00ac80d0
struct cEffectOwner { char pad[0x48]; EffectPtr mEffect; };      // field +0x48 holds the live effect
struct OwnerRef {                           // smart-pointer-like holder at strategy+0x68
    cEffectOwner* mp;
    bool IsNull() const { return mp == 0; }
    cEffectOwner* operator->() const { return mp; }
};
struct VoidRef { void* mp; void* get() const { return mp; } };
struct cCreatureModeStrategy_s00d2_f940 {
    char pad[0x68];
    OwnerRef mOwner;                        // +0x68
    char pad6c[0xb4 - 0x6c];
    VoidRef  mRefB4;                        // +0xb4
    static cCreatureModeStrategy_s00d2_f940* Instance();           // 0x00d38840
};
struct ObjSpatial34 : ObjHdr { char pad04[0x34 - 4]; cSpatialObject mSp34; };   // +0x34
struct ObjFlags : ObjHdr { char pad04[0x34 - 4]; cSpatialObject mSp34; char pad38[0x84 - 0x38]; uint32_t mFlags; };   // +0x84
struct ObjWithState : ObjFlags { char pad88[0x16c - 0x88]; int mState; };        // +0x16c
struct ObjWithMode : ObjFlags { char pad88[0x110 - 0x88]; int mMode; };          // +0x110
struct ObjWithSp0 : ObjHdr { char pad04[0xc0 - 4]; cSpatialObject mSpC0; };      // +0xc0
struct cSPCreatureBase;
struct cInteractionState {                       // gGlobals->mpState (+0x78)
    int  FUN_00f1a320(cSPCreatureBase* who, ObjHdr* target, char* outFlag);   // 0x00f1a320
    bool FUN_00f1a640(int idx);                  // 0x00f1a640
    bool FUN_00f1a440(int idx, ObjHdr* target);  // 0x00f1a440
};
struct cInteractionGlobals { char pad[0x78]; cInteractionState* mpState; };
extern cInteractionGlobals* gInteraction;        // 0x016c7aa4
struct cSPCreatureBase {
    PV8 PV8 PV8 PV8 PV8 PV8 PV4 PV_s00d2_f940
    virtual bool VSlotD4();                      // 0xd4
    char pad[0xb20 - 4 - 0xd4 - 4];
    int  mB20;
    char padb24[0xb48 - 0xb24];
    struct cSub48* mpB48;
    struct cSub4c* mpB4C;
    char padb50[0xb58 - 0xb50];
    uint32_t mB58;
    char padb5c[0xb5e - 0xb5c];
    char mB5E;
    // methods (all thiscall)
    int   FUN_00c0ee60();                        // returns +0xe7c
    cSPCreatureBase* GetTargetAsCreature();      // 0x00c0ee70
    int   FUN_00c0f620();
    int   FUN_00c0f780();
    int   FUN_00c0f8a0(int idx);
    int   FUN_00c0f8f0(void* o);
    struct cB2* FUN_00c04750();
    float FUN_00c0bb10();
    bool  FUN_00c0b770();
    int   FUN_00c0bc00();
    bool  FUN_00c0c0e0();
    int   GetSocialGoal();                       // 0x00c0e6a0
    bool  FUN_00bfc480();
    bool  FUN_00c13c60(int a, int b, bool c);
    int   FUN_00c6aa30();
};
struct cSub48 { int FUN_00bca0c0(int a, int b, int c, int d); };
struct cSub4c { char pad[0x1d8]; int mState; };
struct cB2 { char pad[2]; char mB2; };
struct cAvatarSystem { int FUN_00ba3f90(int a, void* b, void* c); };
cAvatarSystem* __cdecl FUN_00b3d4c0();           // singleton getter
struct cNounManager {
    cSPCreatureBase* GetAvatar();                // 0x00b1fdb0
    struct cTerrainSphere* GetCurrentTerrainSphere(uint32_t id);   // 0x00f67d90
};
struct cTerrainSphere { bool FUN_00c773d0(); };
cNounManager* __cdecl NounManager();             // 0x00b3d300
int  __cdecl GetCurrentGameMode();               // 0x00b5b800
bool __cdecl FUN_00f0a690(ObjHdr* o);
struct cObjB { char pad[0x38]; int mF38; };
cObjB* __cdecl FUN_00bd8460(ObjHdr* o);
cSPCreatureBase* __cdecl FUN_00ae6740(ObjHdr* o);
ObjHdr* __cdecl FUN_00ae66d0(int h);
int  __cdecl FUN_00d2e490();
int  __cdecl FUN_00d2ec30(int h);
bool __cdecl FUN_00d2ede0(int h);
bool __cdecl FUN_0064f350(void* a, uint32_t id, int b);
struct cObjC { char pad[0x110]; int mF110; };
cObjC* __cdecl FUN_00c0c3c0(void* o);
struct cEvtTarget { char pad[0x50]; uint32_t mF50; char pad54[0x70 - 0x54]; char mF70; };   // result of the +0xc query
struct cObjF4 { char pad[0xa4]; int mA4; };
struct cObjClick2a034cd : ObjHdr { char pad4[0x1e8 - 4]; int mState; char pad1ec[0x1f4 - 0x1ec]; cObjF4* mpF4; };
struct cObjClick2c9cc91 : ObjHdr { char pad4[0xa4 - 4]; char mA4; char pada5[0x16c - 0xa5]; int mState; };
struct cObjSp34 : ObjHdr { char pad4[0x34 - 4]; cSpatialObject mSp34; int FUN_00c6aa30(); };
// ---- items of slice s00d2f940 end

// ---- items of slice s00d30830 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CNoun
{
    virtual void vfn00();
    virtual void vfn01();
    virtual void vfn02();
    virtual uint32_t GetInteractionTarget();    // slot 0x0c

    CNoun* GetSelectedNoun();                   // 0x00c0ee60
};
struct CNounManager
{
    CNoun* GetAvatar();                         // 0x00b1fdb0
};
CNounManager* GetNounManager();                 // 0x00b3d300
uint32_t ClassifyTarget(uint32_t nValue, bool* pbIsTarget);
struct CSpTimer
{
    bool     IsRunning();        // 0x00feba90
    uint64_t GetElapsedTime();   // 0x00bc3190
    void     Restart();          // 0x00bc3130
};
struct CRBTreeNode
{
    /* 000h */ uint8_t   mPad_000[0x14];
    /* 014h */ CSpTimer* mpTimer;    // tree value
};
struct CRBTreeIterator
{
    /* 000h */ CRBTreeNode* mpNode;
};
struct CRBTree
{
    /* 000h */ uint8_t     mPad_000[4];
    /* 004h */ CRBTreeNode  mAnchor;          // sentinel; &mAnchor is end()

    void find(CRBTreeIterator* pIt, const uint32_t& nKey);   // 0x00e5c780
};
struct cCreatureModeInputStrategy_s00d3_0830
{
    /* 000h */ uint8_t mPad_000[0x6c];
    /* 06ch */ CRBTree mTimerMap;

    bool DidDoubleClick(uint32_t nKey);  // 0x00d30ee0 (cCreatureModeInputStrategy::DidDoubleClick)
};
uint32_t gnDoubleClickThreshold;
// ---- items of slice s00d30830 end

// ---- items of slice s00d311b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_GetCurrentGameMode(void);               // 0x00b5b800
extern "C" int   FUN_00d30830(void* p);                     // 0x00d30830
#define PV_s00d3_11b0 virtual void PVCAT(pv_, __COUNTER__)();
#define PV1 PV_s00d3_11b0
#define PV2_s00d3_11b0 PV_s00d3_11b0 PV_s00d3_11b0
#define PV4_s00d3_11b0 PV2_s00d3_11b0 PV2_s00d3_11b0
#define PV8_s00d3_11b0 PV4_s00d3_11b0 PV4_s00d3_11b0
struct HeapObj {
    PV8_s00d3_11b0 PV8_s00d3_11b0 PV8_s00d3_11b0 PV8_s00d3_11b0 PV8_s00d3_11b0 PV4_s00d3_11b0 PV2_s00d3_11b0 PV1
    virtual void AddRef();                                 // vtable +0xbc
    virtual void Release();                                // vtable +0xc0
};
struct Ref {
    HeapObj* p;                                            // +0x00
    Ref() : p(0) {}
    Ref(const Ref& o) { p = o.p; if (p) p->AddRef(); }
    Ref& operator=(const Ref& o)
    {
        HeapObj* old = p;
        HeapObj* nw  = o.p;
        if (nw != old) {
            if (nw) nw->AddRef();
            p = nw;
            if (old) old->Release();
        }
        return *this;
    }
    ~Ref() { if (p) p->Release(); }
    operator HeapObj*() const { return p; }                 // read as a raw ptr
};
struct Cmp {
    float px;                                              // +0x00
    float py;                                              // +0x04
    float pz;                                              // +0x08
    bool operator()(HeapObj* a, HeapObj* b) const;         // 0x00d2f3c0
};
struct Prior {
    float mF[7];
};
struct Value {
    Ref   mRef;                                            // +0x00
    Cmp   mCmp;                                            // +0x04
    float mF[4];                                           // +0x10
    Value() {}
    Value(const Prior& src, HeapObj* owner)
    {
        mCmp.px = src.mF[0];
        mCmp.py = src.mF[1];
        mCmp.pz = src.mF[2];
        mF[0] = src.mF[3];
        mF[1] = src.mF[4];
        mF[2] = src.mF[5];
        mF[3] = src.mF[6];
        mRef.p = owner;
        if (mRef.p) mRef.p->AddRef();
    }
    Value(const Value& o)
    {
        mCmp.px = o.mCmp.px;
        mCmp.py = o.mCmp.py;
        mCmp.pz = o.mCmp.pz;
        mF[0] = o.mF[0];
        mF[1] = o.mF[1];
        mF[2] = o.mF[2];
        mF[3] = o.mF[3];
        mRef.p = o.mRef.p;
        if (mRef.p) mRef.p->AddRef();
    }
};
extern "C" void FUN_00d2f880(Ref* first, int top, int hole, Value val);  // 0x00d2f880
// ---- items of slice s00d311b0 end

// ---- items of slice s00d31a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
#define VFUNC(obj, off) ((*(void***)(obj))[(off) / 4])
}
namespace SP {
struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
}
namespace SP {
Vector3* __cdecl normalized_safe(Vector3* out, const Vector3* in);   // 0x00449c20
}
namespace SP {
struct cLocomotionRequest {
  uint32_t mData[0x1c];
  cLocomotionRequest();                                        // 0x00ac9850
  ~cLocomotionRequest();                                       // 0x007a41a0
};
}
namespace SP {
class cLocomotiveObject_s00d3_1a70 {
public:
virtual void vf00();
virtual void vf04();
virtual void vf08();
virtual void vf0c();
virtual void vf10();
virtual void vf14();
virtual void vf18();
virtual void vf1c();
virtual void vf20();
virtual void vf24();
virtual void vf28();
  virtual const Vector3& GetPosition();              // 0x2c
virtual void vf30();
virtual void vf34();
virtual void vf38();
virtual void vf3c();
virtual void vf40();
virtual void vf44();
virtual void vf48();
virtual void vf4c();
virtual void vf50();
virtual void vf54();
virtual void vf58();
virtual void vf5c();
virtual void vf60();
virtual void vf64();
virtual void vf68();
virtual void vf6c();
  virtual void vf70();
  virtual float GetRadius();                         // 0x74
virtual void vf78();
virtual void vf7c();
virtual void vf80();
virtual void vf84();
virtual void vf88();
virtual void vf8c();
virtual void vf90();
virtual void vf94();
virtual void vf98();
virtual void vf9c();
virtual void vfa0();
virtual void vfa4();
virtual void vfa8();
virtual void vfac();
virtual void vfb0();
virtual void vfb4();
virtual void vfb8();
virtual void vfbc();
virtual void vfc0();
virtual void vfc4();
virtual void vfc8();
virtual void vfcc();
virtual void vfd0();
virtual void vfd4();
  virtual void vfd8();
  virtual void RequestMove(const cLocomotionRequest& request);   // 0xdc
};
}
namespace SP {
struct cBehaviorTreeData_s00d3_1a70 {
  char pad[0x1c8];
  uint64_t mFlags;   // +0x1c8
};
}
namespace SP {
struct cCreatureAnimal {
  void PlayAnimation(uint64_t flags, float range, int a, int b, int c, int d);    // 0x00c03190
  void MoveToPointAndFacingAtSpeed(int mode, const Vector3* p, const Vector3* d, float s0, float s1);  // 0x00c1c5c0
  void MoveToPointFacing(int mode, const Vector3* p, const Vector3* d, float s0, float s1);            // 0x00c1c080

  char pad0[0xc0];
  cLocomotiveObject_s00d3_1a70 mLoco;            // +0xc0
  char padc4[0xb4c - 0xc4];
  cBehaviorTreeData_s00d3_1a70* mpBehavior;      // +0xb4c
  char padb50[0xb5e - 0xb50];
  bool mbDead;                        // +0xb5e
};
}
namespace SP {
class cGameNounManager_s00d3_1a70 { public: cCreatureAnimal* GetAvatar(); };   // 0x00b1fdb0
}
namespace SP {
class cGameInputManager_s00d3_1a70 { public:
  bool IsKeyDown(int key) { return ((bool(__thiscall*)(void*, int))VFUNC(this, 0x18))(this, key); }
};
}
namespace SP {
struct cPickedThing {
  void* Cast(uint32_t id) { return ((void*(__thiscall*)(void*, uint32_t))VFUNC(this, 0x0c))(this, id); }
};
}
namespace SP {
struct cPosSource {
  Vector3* GetPickPosition(Vector3* out, int n) { return ((Vector3*(__thiscall*)(void*, Vector3*, int))VFUNC(this, 0x3c))(this, out, n); }
  cPickedThing* GetPicked() { return ((cPickedThing*(__thiscall*)(void*))VFUNC(this, 0x30))(this); }
};
}
namespace SP {
class cViewer_s00d3_1a70 { public:
  void GetCameraRayPoints(Vector3* origin, Vector3* end);   // 0x007c46f0
};
}
namespace SP {
struct cRenderThing { cViewer_s00d3_1a70* GetViewer() { return ((cViewer_s00d3_1a70*(__thiscall*)(void*))VFUNC(this, 0x1c))(this); } };
}
namespace SP {
struct cAppObj { cRenderThing* GetRender() { return ((cRenderThing*(__thiscall*)(void*))VFUNC(this, 0x50))(this); } };
}
namespace SP {
struct cRayQuery {              // 0x16 bytes as built on the stack
  uint32_t a, b, c, d, e;
  uint8_t mode, flag;
};
}
namespace SP {
struct cRayCaster {             // vtable slot 0x44: cast a ray, return fraction of the segment hit
  bool Cast(Vector3* p0, Vector3* p1, void* ignore, float* t, cRayQuery* q) {
    return ((bool(__thiscall*)(void*, Vector3*, Vector3*, void*, float*, cRayQuery*))VFUNC(this, 0x44))(this, p0, p1, ignore, t, q);
  }
};
}
namespace SP {
struct cRaySubobject {          // subobject at +0x34 of the 0x52aa6122 component
  cRayCaster* GetCaster() { return ((cRayCaster*(__thiscall*)(void*))VFUNC(this, 0xb0))(this); }
  void* GetIgnore() { return ((void*(__thiscall*)(void*))VFUNC(this, 0xac))(this); }
};
}
namespace SP {
struct cRayComponent { char pad[0x34]; cRaySubobject sub; };
}
namespace SP {
class cSPTimer_s00d3_1a70 { public: uint64_t GetElapsedTime(); };   // 0x00bc3190
}
namespace SP {
cGameNounManager_s00d3_1a70* NounManager_s00d3_1a70();              // 0x00b3d300
}
namespace SP {
cGameInputManager_s00d3_1a70* GameInputManager_s00d3_1a70();        // 0x00b3d250
}
namespace SP {
cPosSource* PosSource();                      // 0x00b3d240
}
namespace SP {
cAppObj* App();                               // 0x0067dd10
}
namespace SP {
void* __cdecl interface_cast_IID(void* obj, uint32_t iid);   // 0x00ac80d0
}
namespace SP {
void GetCameraMoveVectors(Vector3* forward, Vector3* right);   // 0x00d2ee70
}
namespace SP {
bool IsStrafeLeftDown();                      // 0x00d2eab0
}
namespace SP {
bool IsStrafeRightDown();                     // 0x00d2eaf0
}
namespace SP {
void SetAvatarMoveTarget(cCreatureAnimal* avatar, const Vector3* target);   // 0x00d2ec50
}
namespace SP {
extern bool g_bAutoRun;                  // 0x0169e37c
}
namespace SP {
extern const Vector3 g_NoGoal;           // 0x0169e17c
}
namespace SP {
extern float g_StopMaxDistance;          // 0x01582ba8
}
namespace SP {
extern float g_MoveGoalMinDist;          // 0x01582bac
}
namespace SP {
extern float g_MoveGoalMaxDist;          // 0x01582bb0
}
namespace SP {
extern uint32_t g_ClickMoveTimeMs;       // 0x01582bc8
}
namespace SP {
extern float g_StopRadiusCap;            // 0x01582bd0
}
namespace SP {
extern float g_MaxRayLength;             // 0x013ec5b4 (1000.0)
}
namespace SP {
extern float g_StepLength;               // 0x01486114 (2.5)
}
namespace SP {
extern float g_HalfFactor;               // 0x01471064 (0.5)
}
namespace SP {
const float kFloatMax = 3.4028234663852886e+38f;
}
namespace SP {
class cCreatureModeInputStrategy_s00d3_1a70 {
public:
  bool UpdateAvatarGoal(bool a, bool b);       // 0x00d31a70
  void SpawnMovementGoalEffect(const Vector3* goal);   // 0x00d30fb0

  char pad0[0xa0];
  cSPTimer_s00d3_1a70 mMouseDownTimer;    // +0xa0
  char pada4[0xc0 - 0xa4];
  bool mbUpdateAvatarGoals;    // +0xc0
};
}
// ---- items of slice s00d31a70 end

// ---- items of slice s00d34f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vtbl { void* mSlots[0x200 / 4]; };
typedef void  (__thiscall *VFn_vvc)(void*, void*, uint8_t);
#define VSLOT(o, n) (((Vtbl*)*(void**)(o))->mSlots[(n) / 4])
struct Vector3_s00d3_4f90 {
    float x, y, z;
    Vector3_s00d3_4f90() {}
    Vector3_s00d3_4f90(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00d3_4f90(const Vector3_s00d3_4f90& v) { x = v.x; y = v.y; z = v.z; }
};
struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(const Quaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; }
};
struct IGameInputManager;
struct IModelWorld;
struct Transform {
    uint16_t mFlags;      // 0x00
    uint16_t mnChanges;   // 0x02
    Vector3_s00d3_4f90  mOffset;     // 0x04
    float    mScale;      // 0x10
    Matrix3  mRotation;   // 0x14
};
struct cMWModel {
    IModelWorld* mpWorld;     // 0x00
    uint32_t     mFlags;      // 0x04
    Transform    mTransform;  // 0x08
    int32_t      mRefCount;   // 0x40
    uint8_t      mPad44[0x60 - 0x44];
    uint32_t     mType;       // 0x60
    uint8_t      mPad64[0x6c - 0x64];
    float        mDefaultBoundingRadius;   // 0x6c

    void AddRef() { mRefCount++; }
    void Release()
    {
        if (mRefCount > 1)
            --mRefCount;
        else
            ((VFn_vvc)VSLOT(mpWorld, 0x170))(mpWorld, this, (uint8_t)((mFlags >> 31) & 1));
    }
};
struct cMWModelPtr {
    cMWModel* mpObject;
    cMWModel* get() const { return mpObject; }
    cMWModelPtr& operator=(cMWModel* pObject)
    {
        if (pObject != mpObject) {
            cMWModel* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
struct MWModelVector {
    cMWModelPtr* mpBegin;     // 0x00
    cMWModelPtr* mpEnd;       // 0x04
    cMWModelPtr* mpCapacity;  // 0x08
    void resize(size_t n);    // 0x00473270
};
class cCreatureModeInputStrategy_s00d3_4f90 {
public:
    uint8_t        mPad00[0x54];            // 0x000
    uint8_t        mbActive;                // 0x054  substate active flag
    uint8_t        mPad55[0x58 - 0x55];     // 0x055
    MWModelVector  mCreatureHitBoxes;       // 0x058

    void UpdateCreaturePickBoxes();                        // 0x00d342d0
    void CleanUpCreatureHitBoxes();                        // 0x00d34230
    void FUN_00d32df0(IGameInputManager* pInput, int arg); // 0x00d32df0

    void FUN_00d34f90(int arg);
    void InitSubstate();
};
struct Compare7 {
    Vector3_s00d3_4f90    mPosition;
    Quaternion mOrientation;
};
void FUN_00d340d0(void* first, void* last, Compare7 compare);   // 0x00d340d0
// ---- items of slice s00d34f90 end

// ---- items of slice s00d35190 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4238)  // address of a temporary (Variant fallback below)
namespace SP {
struct Vector3_s00d3_5190 { float x, y, z; };
}
namespace SP {
struct Variant {
  uint32_t mValue[4];
  uint16_t mFlags;   // +0x10
  uint16_t mTypeId;  // +0x12
  Variant(const uint32_t& v);             // 0x005bf350
  ~Variant() { if (mFlags & 4) Destruct(false); }
  void Destruct(bool reset);              // 0x0093db80
  const uint32_t* GetUInt32() const;      // 0x005727b0
};
}
namespace SP {
struct Model { char pad[0x8c]; float mf8c; };
}
namespace SP {
class cSpatialObject_s00d3_5190 { public:
  const Vector3_s00d3_5190& GetPosition() { return ((const Vector3_s00d3_5190&(__thiscall*)(void*))VFUNC(this, 0x2c))(this); }
  Model* GetModel() { return ((Model*(__thiscall*)(void*))VFUNC(this, 0xac))(this); }
};
}
namespace SP {
class cGameData_s00d3_5190 { public:
  uint32_t GetPoliticalID() { return ((uint32_t(__thiscall*)(void*))VFUNC(this, 0x4c))(this); }
};
}
namespace SP {
class cCombatant_s00d3_5190 { public:
  cSpatialObject_s00d3_5190* ToSpatialObject() { return ((cSpatialObject_s00d3_5190*(__thiscall*)(void*))VFUNC(this, 0x8))(this); }
  cGameData_s00d3_5190* ToGameData() { return ((cGameData_s00d3_5190*(__thiscall*)(void*))VFUNC(this, 0xc))(this); }
  int TakeDamage(float damage, uint32_t attackerPID, int type, const Vector3_s00d3_5190& dir, cCombatant_s00d3_5190* attacker) {
    return ((int(__thiscall*)(void*, float, uint32_t, int, const Vector3_s00d3_5190&, cCombatant_s00d3_5190*))VFUNC(this, 0x18))(
        this, damage, attackerPID, type, dir, attacker);
  }
  float GetMaxHitPoints() { return ((float(__thiscall*)(void*))VFUNC(this, 0x58))(this); }
  int GetCombatState();          // 0x008e7f80
  bool IsInvulnerable();         // 0x00bfc480
  void PartialRepair(float f);   // 0x00bfd1a0
};
}
namespace SP {
struct MoveGoal {               // locomotion request (ctor 0x00ad29d0 / 0x00ac9850, dtor 0x007a41a0)
  uint32_t mData[0x1c];
  MoveGoal(const Vector3_s00d3_5190& target, float minDist, float maxDist);
  MoveGoal();
  ~MoveGoal();
};
}
namespace SP {
class cLocomotiveObject_s00d3_5190 { public:
  const Vector3_s00d3_5190& GetPosition() { return ((const Vector3_s00d3_5190&(__thiscall*)(void*))VFUNC(this, 0x2c))(this); }
  Vector3_s00d3_5190 GetDirection() {
    Vector3_s00d3_5190 r;
    ((Vector3_s00d3_5190*(__thiscall*)(void*, Vector3_s00d3_5190*))VFUNC(this, 0x5c))(this, &r);
    return r;
  }
  void RequestMove(const MoveGoal& g) { ((void(__thiscall*)(void*, const MoveGoal&))VFUNC(this, 0xdc))(this, g); }
  bool IsIdle() { return ((bool(__thiscall*)(void*))VFUNC(this, 0xf8))(this); }
  const Vector3_s00d3_5190& GetVelocity();  // 0x00d20610
};
}
namespace SP {
struct cBehaviorTreeData_s00d3_5190 {
  char pad0[8];
  struct Sub { void Notify(uint64_t flags, float range, int x); } mSub;   // +0x08 (0x00bc97f0)
  char pad9[0x1c8 - 0x9];
  uint64_t mFlags;   // +0x1c8
};
}
namespace SP {
struct cCreatureAnimal_s00d3_5190 {
  uint32_t GetPoliticalID() { return ((uint32_t(__thiscall*)(void*))VFUNC(this, 0x4c))(this); }
  void SetCreatureTarget(cCombatant_s00d3_5190* target, bool b, int intention) {
    ((void(__thiscall*)(void*, cCombatant_s00d3_5190*, bool, int))VFUNC(this, 0x84))(this, target, b, intention);
  }
  int GetCurrentBrainLevel() { return ((int(__thiscall*)(void*))VFUNC(this, 0xd8))(this); }
  void SetCurrentBrainLevel(int l) { ((void(__thiscall*)(void*, int))VFUNC(this, 0xdc))(this, l); }
  void SetFlagE8(int v) { ((void(__thiscall*)(void*, int))VFUNC(this, 0xe8))(this, v); }

  cCombatant_s00d3_5190* GetTarget();                                         // 0x00c0ee60
  void PlayAnimation(uint64_t flags, float range, int a, int b, int c, int d);   // 0x00c03190
  cCreatureAnimal_s00d3_5190* GetSpeciesTemplate();                           // 0x00c04590
  float GetHealth();                                               // 0x00c0b9c0
  void SetHealth(float h);                                         // 0x00c0b9d0
  bool IsInWater();                                                // 0x00c0c120
  void ReturnToIdle(int v);                                        // 0x00c14750
  void SetupFromTemplate(int v);                                   // 0x00c6ace0
  void FinishSetup();                                              // 0x00c6b540

  char pad0[0x88];
  uint32_t m88;                       // +0x88
  char pad8c[0xc0 - 0x8c];
  cLocomotiveObject_s00d3_5190 mLoco;            // +0xc0
  char padc1[0xf0 - 0xc1];
  uint32_t mf0;                       // +0xf0
  char padf4[0x110 - 0xf4];
  uint32_t mf110;                     // +0x110
  char pad114[0x137 - 0x114];
  bool mb137;                         // +0x137
  char pad138[0x5a8 - 0x138];
  cCombatant_s00d3_5190 mCombatant;              // +0x5a8
  char pad5a9[0xb20 - 0x5a9];
  void* mpSpeciesProfile;             // +0xb20
  char padb24[0xb28 - 0xb24];
  char mb28[0x24];                    // +0xb28
  cBehaviorTreeData_s00d3_5190* mpBehavior;      // +0xb4c
  char padb50[0xb58 - 0xb50];
  uint32_t mGeneralFlags;             // +0xb58
  bool mbB5C;                         // +0xb5c
  bool mbB5D;
  bool mbDead;                        // +0xb5e
  char padb5f[0x1124 - 0xb5f];
  char mNearbyCreatures[0x10];        // +0x1124
};
}
namespace SP {
struct NearbyIterator {
  void** mpCur;
  void** mpEnd;
  NearbyIterator(void* container, char* tag);   // 0x00b41a40
  void Next();                                  // 0x00b3d850
};
}
namespace SP {
struct ObjectRefVector {   // eastl::vector<AutoRefCount<cSpatialObject>, sp_vector_allocator>
  cSpatialObject_s00d3_5190** mpBegin;
  cSpatialObject_s00d3_5190** mpEnd;
  cSpatialObject_s00d3_5190** mpCapacity;
  uint32_t mAllocator;
  ObjectRefVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~ObjectRefVector();   // 0x00ad92d0
};
}
namespace SP {
struct TargetSortCompare {   // 0x1c-byte functor, ctor 0x00d2f380
  uint32_t mData[7];
  TargetSortCompare(const Vector3_s00d3_5190& camPos, const Vector3_s00d3_5190& camDir, float range);
};
}
namespace SP {
void SortTargets(cSpatialObject_s00d3_5190** first, cSpatialObject_s00d3_5190** last, TargetSortCompare cmp);   // 0x00d34fc0
}
namespace SP {
class cSPTimer_s00d3_5190 { public:
  bool IsRunning();             // 0x00feba90
  void Start();                 // 0x00bc30f0
  void Stop();                  // 0x00bc3170
  uint64_t GetElapsedTime();    // 0x00bc3190
  uint32_t mData[8];
};
}
namespace SP {
struct IMessageArgs {
  void* GetArg(int i) { return ((void*(__thiscall*)(void*, int))VFUNC(this, 0x1c))(this, i); }
};
}
namespace SP {
struct IMessageData {
  IMessageArgs* GetArgs() { return ((IMessageArgs*(__thiscall*)(void*))VFUNC(this, 0x10))(this); }
};
}
namespace SP {
struct cGameDataRef { void* GetObject(); };   // 0x00bd6a60
}
namespace SP {
class cGameInputManager_s00d3_5190 { public:
  int GetMode() { return ((int(__thiscall*)(void*))VFUNC(this, 0x34))(this); }
  void SetMode(int m) { ((void(__thiscall*)(void*, int))VFUNC(this, 0x38))(this, m); }
};
}
namespace SP {
struct cMessageServer {
  void Post(uint32_t id, int a, int b) { ((void(__thiscall*)(void*, uint32_t, int, int))VFUNC(this, 0x14))(this, id, a, b); }
};
}
namespace SP {
class cViewer_s00d3_5190 { public:
  void GetCameraLocationInfo(Vector3_s00d3_5190* pos, Vector3_s00d3_5190* right, Vector3_s00d3_5190* up, Vector3_s00d3_5190* forward);   // 0x007c3d30
};
}
namespace SP {
class cRenderer_s00d3_5190 { public: cViewer_s00d3_5190* GetViewer() { return ((cViewer_s00d3_5190*(__thiscall*)(void*))VFUNC(this, 0x1c))(this); } };
}
namespace SP {
class cApp { public: cRenderer_s00d3_5190* GetRenderer() { return ((cRenderer_s00d3_5190*(__thiscall*)(void*))VFUNC(this, 0x50))(this); } };
}
namespace SP {
struct cSpatialQuery {
  void FindObjects(const Vector3_s00d3_5190& center, float radius, ObjectRefVector* out, int a, int b, int c) {
    ((void(__thiscall*)(void*, const Vector3_s00d3_5190&, float, ObjectRefVector*, int, int, int))VFUNC(this, 0x48))(
        this, center, radius, out, a, b, c);
  }
};
}
namespace SP {
class cGameNounManager_s00d3_5190 { public:
  cCreatureAnimal_s00d3_5190* GetAvatar();                                                         // 0x00b1fdb0
  cCreatureAnimal_s00d3_5190* CreateCreature(const Vector3_s00d3_5190& pos, void* species, int a, int b, int c, int d);  // 0x00b23940
};
}
namespace SP {
class cPlanetModel_s00d3_5190 { public: Vector3_s00d3_5190 MakeRandomWorldPosition(const Vector3_s00d3_5190& pos, float minR, float maxR); };   // 0x00b81780
}
namespace SP {
class cPosseSimulator { public: char pad[0x18]; int mState; void Disband(int v); };  // 0x00d52e40
}
namespace SP {
struct cSettingsFlags { char pad[0x6c]; uint32_t mFlags; };
}
namespace SP {
struct cUIRefCounted { void Release() { ((void(__thiscall*)(void*))VFUNC(this, 0xc0))(this); } };
}
namespace SP {
struct cUIRefPtr { cUIRefCounted* mp; void Assign(void* p); };   // 0x00c70110
}
namespace SP {
struct cCanvas { bool IsVisible(); void SetVisible(bool v); };   // 0x00801400 / 0x008013d0
}
namespace SP {
struct cUIManagerA { void Reset(); };                            // 0x00ad7dc0
}
namespace SP {
struct cHintManager { void ShowHint(int a, uint32_t id, int b); };  // 0x00e3e350
}
namespace SP {
struct cGameModeMgr { void Leave(uint32_t id); };                // 0x00b1e410
}
namespace SP {
struct cTutorial { void Select(void* animal); void Tag(int k, void* where, void* animal); };  // 0x00ba4f30 / 0x00ba48b0
}
namespace SP {
struct cCinematic { void Stop(int v); };                         // 0x00e190c0
}
namespace SP {
struct cEditorLauncher { void Launch(int v) { ((void(__thiscall*)(void*, int))VFUNC(this, 0x28))(this, v); } };
}
namespace SP {
struct cSubStrategy { void Exit(int v); };                       // 0x00d2c200
}
namespace SP {
struct cUIRolloverTarget { void Activate() { ((void(__thiscall*)(void*))VFUNC(this, 0x48))(this); } };
}
namespace SP {
class cCreatureModeStrategy_s00d3_5190 {
public:
  static cCreatureModeStrategy_s00d3_5190* Instance();                 // 0x00d38840
  static cCreatureModeStrategy_s00d3_5190* spInstance;                 // 0x0169e294
  static void NotifyEvent(float value);                     // 0x00d2e8a0
  void NotifyWantToGoToEditor(int v);                       // 0x00d3c6a0
  void SignalCreatureEvent(uint32_t id);                    // 0x00d3cdc0
  void PostKillMessage(uint32_t id, void* data);            // 0x00d39360
  char pad[0x68];
  cSubStrategy* mpSub;   // +0x68
};
}
namespace SP {
class cUIBanningContent { public:
  static void EndBanMode(int v);                  // 0x00dd1840
  static void ShowConfirmationDialog(void* obj);  // 0x00dd1aa0
};
}
namespace SP {
class cSPUISpace { public: static void KillSetiEffects(uint32_t id, int state); };   // 0x00435ed0
}
namespace SP {
cGameInputManager_s00d3_5190* GameInputManager_s00d3_5190();        // 0x00b3d250
}
namespace SP {
cGameNounManager_s00d3_5190* NounManager_s00d3_5190();              // 0x00b3d300
}
namespace SP {
cPlanetModel_s00d3_5190* PlanetModel_s00d3_5190();                  // 0x00b3d350
}
namespace SP {
cMessageServer* MessageServer();              // 0x0067dcc0
}
namespace SP {
cApp* App_s00d3_5190();                                  // 0x0067dd10
}
namespace SP {
uint32_t GetCurrentGameMode();                // 0x00b5b800
}
namespace SP {
cUIManagerA* UIManagerA();                    // 0x00b3d4d0
}
namespace SP {
cHintManager* HintManager();                  // 0x00b3d410
}
namespace SP {
cGameModeMgr* GameModeManager();              // 0x00b3d320
}
namespace SP {
cSpatialQuery* SpatialQuery();                // 0x00b3d240
}
namespace SP {
cTutorial* Tutorial();                        // 0x00b3d4c0
}
namespace SP {
cCinematic* CinematicManager();               // 0x00b3d3f0
}
namespace SP {
cCanvas* MainCanvas();                        // 0x0067cab0
}
namespace SP {
cEditorLauncher* EditorLauncher();            // 0x00d37cb0
}
namespace SP {
cSettingsFlags* CreatureSettings();           // 0x00d51660
}
namespace SP {
cPosseSimulator* PosseSimulatorInstance();    // 0x00d539d0
}
namespace SP {
Vector3_s00d3_5190 normalized_safe(const Vector3_s00d3_5190& v);    // 0x00449c20
}
namespace SP {
float Dot3(const Vector3_s00d3_5190& a, const Vector3_s00d3_5190& b);   // 0x00455cc0
}
namespace SP {
int GetRecorderState();                       // 0x00435e90
}
namespace SP {
cCreatureAnimal_s00d3_5190* interface_cast_Animal(void* obj);           // 0x00ac8960
}
namespace SP {
cUIRolloverTarget* interface_cast_Rollover(void* obj);       // 0x00ac86f0
}
namespace SP {
cUIRefCounted* interface_cast_Selectable(void* obj);         // 0x00ac8710
}
namespace SP {
cCombatant_s00d3_5190* CombatantFromObject(cSpatialObject_s00d3_5190* obj);        // 0x00cb45b0
}
namespace SP {
bool IsSelectableTarget(cCombatant_s00d3_5190* c);                      // 0x00d30f60
}
namespace SP {
cCreatureAnimal_s00d3_5190* AnimalFromCombatant(cCombatant_s00d3_5190* c);         // 0x00ae33b0
}
namespace SP {
float GetCurrentDNA();                                       // 0x00d2e350
}
namespace SP {
int IsHUDHidden();                                           // 0x00d2e490
}
namespace SP {
void SetHUDHidden(int hidden, int animate);                  // 0x00d2e4a0
}
namespace SP {
void ToggleDebugDisplay();                                   // 0x00b676a0
}
namespace SP {
void TribeToolEndMode(int v);                                // 0x00e09a50
}
namespace SP {
void TribeToolConfirm(void* obj);                            // 0x00e09bf0
}
namespace SP {
void SetAvatarMoveTarget(cCreatureAnimal_s00d3_5190* avatar, const Vector3_s00d3_5190& target);   // 0x00d2ec50
}
namespace SP {
extern bool g_bAutoRunLocked;          // 0x0169e170
}
namespace SP {
extern bool g_bShowAvatarGoal;         // 0x0169e37e
}
namespace SP {
extern bool g_bFreeCamera;             // 0x0169e37c
}
namespace SP {
extern int g_CheatEventKind;           // 0x0169e370
}
namespace SP {
extern cUIRefPtr g_pSelectedUI;        // 0x0168e814
}
namespace SP {
extern float g_TargetPickRange;        // 0x01582d20
}
namespace SP {
extern int g_TargetPickMaxCount;       // 0x01582d1c
}
namespace SP {
extern float g_DNAReward[4];           // 0x01582e38
}
namespace SP {
extern const Vector3_s00d3_5190 g_KillDamageDir;  // 0x0169e17c
}
namespace SP {
extern const Vector3_s00d3_5190 g_SetiDamageDir;  // 0x0169e220
}
namespace SP {
struct cInputStrategyBase {        // cInputStrategy + cSPUICursorStrategy + IWinProc
  virtual void InputStrategy0();
  uint32_t mBase[0x11];
};
}
namespace SP {
struct IMessageHandler {           // at +0x48
  virtual bool HandleMessage(uint32_t messageID, IMessageData* pMessage) = 0;
};
}
namespace SP {
class cCreatureModeInputStrategy_s00d3_5190 : public cInputStrategyBase, public IMessageHandler {
public:
  virtual bool HandleMessage(uint32_t messageID, IMessageData* pMessage);  // 0x00d35190 (SP::cCreatureModeInputStrategy::HandleMessage)

  void BeginBanMode();                         // 0x00d2eb70
  void BeginTribeToolMode();                   // 0x00d2ebc0
  void ToggleAutoRun();                        // 0x00d32330
  void UpdateAvatarGoal(bool a, bool b);       // 0x00d31a70
  void SetRolloverObject(void* obj);           // 0x00d32fd0

  uint32_t m4c, m50;
  bool mbEnabled;              // +0x54
  char pad55[0xa0 - 0x55];
  cSPTimer_s00d3_5190 mMouseDownTime;     // +0xa0
  bool mbMoveOnRelease;        // +0xc0
  bool mbMouseMoved;           // +0xc1
  char padc2[0x104 - 0xc2];
  bool mbHoldingObject;        // +0x104
  bool mbReleaseHeld;          // +0x105
};
}
namespace SP {
inline float Clamp(float v, float lo, float hi) {
  float r = v < lo ? lo : v;
  return hi < r ? hi : r;
}
}
namespace SP {
static __forceinline bool PickTarget(cCreatureAnimal_s00d3_5190* avatar);
}
namespace SP {
static __forceinline bool PickTarget(cCreatureAnimal_s00d3_5190* avatar)
{
  cCombatant_s00d3_5190* target = 0;
  cCreatureAnimal_s00d3_5190* targetAnimal = 0;
  cCreatureAnimal_s00d3_5190* nearest = 0;
  const Vector3_s00d3_5190& avatarPos = avatar->mLoco.GetPosition();

  if (GetCurrentGameMode() == 0x1654c10) {
    // Creature game: pick the best enemy in the camera cone.
    float bestScore = kFloatMax;
    float bestForward = kFloatMax;
    cCombatant_s00d3_5190* bestBehind = 0;
    cCombatant_s00d3_5190* cur = avatar->GetTarget();
    Vector3_s00d3_5190 camPos, camRight, camUp, camForward;
    App_s00d3_5190()->GetRenderer()->GetViewer()->GetCameraLocationInfo(&camPos, &camRight, &camUp, &camForward);
    float curForward;
    if (cur) {
      const Vector3_s00d3_5190& p = cur->ToSpatialObject()->GetPosition();
      Vector3_s00d3_5190 d;
      d.x = p.x - camPos.x;
      d.y = p.y - camPos.y;
      d.z = p.z - camPos.z;
      Vector3_s00d3_5190 n = normalized_safe(d);
      curForward = n.y * camForward.y + n.z * camForward.z + camForward.x * n.x;
    }

    ObjectRefVector objs;
    SpatialQuery()->FindObjects(camPos, g_TargetPickRange, &objs, 1, 0, 0);
    SortTargets(objs.mpBegin, objs.mpEnd, TargetSortCompare(camPos, camRight, g_TargetPickRange));

    int count = (int)(objs.mpEnd - objs.mpBegin);
    int found = 0;
    for (int i = 0; i < count; ++i) {
      if (found >= g_TargetPickMaxCount)
        break;
      cSpatialObject_s00d3_5190* obj = objs.mpBegin[i];
      if (!obj->GetModel())
        continue;
      if (obj->GetModel()->mf8c > 0.0f)
        continue;
      cCombatant_s00d3_5190* c = CombatantFromObject(obj);
      if (!IsSelectableTarget(c))
        continue;
      if (c == &avatar->mCombatant)
        continue;
      cGameData_s00d3_5190* data = c->ToGameData();
      uint32_t myPID = avatar->GetPoliticalID();
      if (data->GetPoliticalID() == myPID)
        continue;
      if (c->GetCombatState() == 2)
        continue;
      if (c->IsInvulnerable())
        continue;
      if (c == cur)
        continue;
      cCreatureAnimal_s00d3_5190* an = AnimalFromCombatant(c);
      if (an && ((an->mGeneralFlags >> 8) & 1))
        continue;
      ++found;

      const Vector3_s00d3_5190& p = obj->GetPosition();
      Vector3_s00d3_5190 d;
      d.x = p.x - camPos.x;
      d.y = p.y - camPos.y;
      d.z = p.z - camPos.z;
      Vector3_s00d3_5190 n = normalized_safe(d);
      if (cur && cur->ToSpatialObject()->GetModel() && cur->ToSpatialObject()->GetModel()->mf8c == 0.0f) {
        // Cycle: the next target further along the camera axis.
        float fwd = n.x * camForward.x + n.y * camForward.y + n.z * camForward.z;
        if (bestForward > fwd) {
          bestForward = fwd;
          bestBehind = c;
        }
        if (fwd > curForward && bestScore > fwd) {
          target = c;
          bestScore = fwd;
        }
      } else {
        float score = camRight.x * n.x + camRight.y * n.y + camRight.z * n.z;
        if (target == 0 || score > bestScore) {
          target = c;
          bestScore = score;
        }
      }
    }
    if (target == 0) {
      if (bestBehind)
        target = bestBehind;
      else if (cur)
        target = cur;
    }
    if (target)
      targetAnimal = AnimalFromCombatant(target);
  } else {
    // Other modes: nearest creature of another species.
    float bestDist = kFloatMax;
    char tag;
    for (NearbyIterator it(avatar->mNearbyCreatures, &tag); it.mpCur != it.mpEnd; it.Next()) {
      cCreatureAnimal_s00d3_5190* c = interface_cast_Animal(((void**)*it.mpCur)[2]);
      if (c && !c->mbDead && !((c->mGeneralFlags >> 8) & 1) && c->mpSpeciesProfile != avatar->mpSpeciesProfile) {
        const Vector3_s00d3_5190& p = c->mLoco.GetPosition();
        float dx = p.x - avatarPos.x, dy = p.y - avatarPos.y, dz = p.z - avatarPos.z;
        float d2 = dx * dx + dz * dz + dy * dy;
        if (nearest == 0 || bestDist > d2) {
          nearest = c;
          bestDist = d2;
        }
      }
    }
    if (!nearest)
      return false;
    target = &nearest->mCombatant;
    targetAnimal = nearest;
  }

  if (!target)
    return false;
  if (target == avatar->GetTarget())
    return false;
  if (targetAnimal)
    Tutorial()->Select(targetAnimal);
  avatar->SetCreatureTarget(target, true, 0);
  if (targetAnimal && GetCurrentGameMode() != 0x1654c10)
    cCreatureModeStrategy_s00d3_5190::Instance()->SignalCreatureEvent(0x533535db);
  return true;
}
}
// ---- items of slice s00d35190 end

// ---- items of slice s00d366c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class CursorTable {
public:
    void* AddCursor(int nCursorId, const wchar_t* pCursorName, char cAlpha,
                    int nArg3, int nArg4);                          // 0x00802050
};
CursorTable* GetCursorTable();                                      // 0x0067cab0
class cMessageServer_s00d3_66c0 {
public:
    void* mpVtable;                                                 // 0x00
};
class cMessageHandler {
public:
    uint32_t mUnk000[0x10];                                         // 0x00
};
namespace EA {
namespace Messaging {
    cMessageServer_s00d3_66c0* GetServer();                                    // 0x00883860
}
}
class cProperty {
public:
    uint32_t mUnk000[4];                                            // 0x00
    uint16_t mUnk010;                                               // 0x10
    uint16_t mnType;                                                // 0x12

    char* GetBool();                                                // 0x0041e920
};
class cDirectPropertyList {
public:
    void* mpVtable;                                                 // 0x00
};
extern cDirectPropertyList* gAppProperties;                         // 0x015fd918
extern uint32_t gMessageIds[0x1b];                                  // 0x0147a610
class cStrategyBase {
public:
    uint32_t mUnk000[0x12];                                         // 0x00
};
class cCreatureModeInputStrategy_s00d3_66c0 : public cStrategyBase,
                                   public cMessageHandler {
public:
    cMessageServer_s00d3_66c0* mpMessageServer;                                // 0x088
    cMessageHandler* mpMessageHandler;                              // 0x08c
    uint32_t* mpMessageTable;                                       // 0x090
    uint32_t mnMessageCount;                                        // 0x094
    uint32_t mnUnk098;                                              // 0x098
    uint32_t mUnk09c[0x1a];                                         // 0x09c
    char mbUseKeyArray;                                             // 0x104
    char mbUnk105;                                                  // 0x105

public:
    void InitCursors();
    void SetInputPriorityStrategy(int nPriority);                   // 0x00d33ec0
    void InitSubstate();                                            // 0x00d35030
};
// ---- items of slice s00d366c0 end

// @ 0x00b1b410
void cStateMachineHost::LoadStateMachine(const char* name)
{
  static ParserPtrVector sParserStack;
  gScriptOwner = mpInfo->mpOwner;
  sParserStack.push_back(gScriptParser);
  gScriptParser = CreateParser();
  ResourceKey key = {0, 0, 0};
  void* stream = 0;
  IResourceManager* mgr = GetManager();
  {
    string16 tmp;
    wchar_t* w = ConvertToString16(&tmp, name, -1)->mpBegin;
    mgr->MakeKey(&key, w, 0x24a0e52, 0x24a4f5a);
  }
  void* rec = OpenRecordAsStream(&key, &stream);
  gScriptParser->Reset();
  gScriptParser->Declare("DeclareState", this);
  gScriptParser->Declare("DeclareMenu", this);
  gScriptParser->Declare("DeclareMessage", this);
  gScriptParser->Declare("AddTransition", this);
  gScriptParser->Declare("IncludeMachine", this);
  gScriptParser->SetCheats(CheatManager()->GetInner()->GetCheatTable());
  gScriptParser->Parse(stream);
  EraseEntry(rec);
  gScriptParser = *(sParserStack.mpEnd - 1);
  --sParserStack.mpEnd;
  if (!gScriptParser) {
    gScriptOwner = 0;
    gScriptNames.DoNuke(gScriptNames.mAnchor.mpNodeParent);
    gScriptNames.mAnchor.mpNodeRight = &gScriptNames.mAnchor;
    gScriptNames.mAnchor.mpNodeLeft = &gScriptNames.mAnchor;
    gScriptNames.mAnchor.mpNodeParent = 0;
    gScriptNames.mAnchor.mColor = 0;
    gScriptNames.mnSize = 0;
  }
}

// @ 0x00d2ea80
void* cCreatureModeInputStrategy::AsInterface(unsigned int iid)
{
    if (iid != 0x2f009dd0u) {
        if (iid == 0x305a9f63u)
            return (cCreatureModeStrategy*)((char*)this - 0x3c);
    } else {
        if ((cCreatureModeStrategy*)((char*)this - 0x3c) != 0)
            return &mIface8;
    }
    return 0;
}

// @ 0x00d2eab0
bool cCreatureModeInputStrategy::IsStrafeLeftDown()
{
    cGameInputManager* mgr = GameInputManager();
    if (mgr->IsKeyDown(5))
        return true;
    if (!IsModifierKeyDown(0x3ea))
        return false;
    return mgr->IsKeyDown(3);
}

// @ 0x00d2eaf0
bool cCreatureModeInputStrategy::IsStrafeRightDown()
{
    cGameInputManager* mgr = GameInputManager();
    if (mgr->IsKeyDown(6))
        return true;
    if (!IsModifierKeyDown(0x3ea))
        return false;
    return mgr->IsKeyDown(4);
}

// @ 0x00d2eb30
bool __stdcall OnDisplayStrategyModal(void* window, unsigned int* msg)
{
    if (msg[2] == 0x287259f6u && msg[3] == 0x01788526u) {
        SPUIHelpers_EndModal(window, 0, 1);
        return true;
    }
    return false;
}

// @ 0x00d2eb70
void ToggleBanningMode()
{
    switch (GameInputManager()->FUN_0034()) {
    case 2:
        EndBanMode(1);
        GameInputManager()->FUN_0038(0);
        break;
    default:
        ToggleBanningContent((void*)1);
        GameInputManager()->FUN_0038(2);
        break;
    }
}

// @ 0x00d2ebc0
void ToggleBuildMode()
{
    cGameInputManager* mgr = GameInputManager();
    if (mgr->FUN_0034() != 3) {
        FUN_00e099d0((void*)0);
        GameInputManager()->FUN_0038(3);
    } else {
        FUN_00e09a50((void*)0);
        GameInputManager()->FUN_0038(0);
    }
}

// @ 0x00d2ede0
u8 FUN_00d2ede0(void* p)
{
    if (p == 0)
        goto fail;
    {
        void* r = ((IVtB8*)p)->v_b8(0x3a25119);
        if (r == 0)
            return 0;
        u32 t = *(u32*)((u8*)r + 0x134);
        if (t == 0xd || t == 0xa)
            return 1;
    }
fail:
    return 0;
}

// @ 0x00d2ee20
u8 __stdcall FUN_00d2ee20(void** out)
{
    void* o = FUN_00b3d320((void*)0x1654c01, 1);
    IRefCount* mgr = (IRefCount*)((cMgr*)o)->FUN_00b1daf0();
    if (mgr != 0)
        mgr->AddRef();
    if (out != 0) {
        *out = mgr;
        return 1;
    }
    if (mgr != 0)
        mgr->Release();
    return 1;
}

// @ 0x00d2f940
void SpawnAcknowledgementEffect(int a1, int a2, ObjHdr* obj)
{
    if (cCreatureModeStrategy_s00d2_f940::Instance()->mOwner.IsNull()) return;
    EffectPtr effect(cCreatureModeStrategy_s00d2_f940::Instance()->mOwner->mEffect.p);
    if (effect.p) effect.p->Stop(1);
    effect.reset();
    if (!obj || obj->IsDestroyed()) goto done;
    {
        cSPTransform_s00d2_f940 xform;
        bool orient = false;        // A: build the rotation from the position direction
        bool snapA = false;         // B: snap to planet surface (variant 1)
        bool snapB = false;         // C: snap to planet surface (variant 2)
        bool facing = false;        // D: rotation from planet facing
        uint32_t effectId = 0;
        Vec3 dir;
        switch (obj->GetTypeID()) {
        case 0x2a8fb3f: {
            ObjSpatial34* o = (ObjSpatial34*)ObjCast(obj, 0x2a8fb3f);
            effectId = 0x4ae30884;
            const BBox& bb = o->mSp34.GetBBox();
            const BBox* b = &bb;
            dir.x = (b->mMin.x + b->mMax.x) * 0.5f;
            dir.y = (b->mMax.y + b->mMin.y) * 0.5f;
            dir.z = (b->mMax.z + b->mMin.z) * 0.5f;
            xform.SetOffset(dir);
            facing = true;
            snapB = true;
            break;
        }
        case 0x2a034cd: {
            ObjFlags* o = (ObjFlags*)ObjCast(obj, 0x2a034cd);
            facing = true;
            orient = (o->mFlags & 0x1000) == 0x1000;
            snapA = true;
            effectId = 0x4ae30884;
            const BBox& bb = o->mSp34.GetBBox();
            const BBox* b = &bb;
            dir.x = (b->mMin.x + b->mMax.x) * 0.5f;
            dir.y = (b->mMax.y + b->mMin.y) * 0.5f;
            dir.z = (b->mMax.z + b->mMin.z) * 0.5f;
            xform.SetOffset(dir);
            break;
        }
        case 0x18eb45e: {
            ObjWithSp0* o = (ObjWithSp0*)ObjCast(obj, 0x18eb45e);
            if (!((a1 == 8 && a2 == 0) || (a1 == 0x40000 && a2 == 0))) return;
            effectId = 0x4ae30884;
            o->mSpC0.LocalToWorldTransform(&xform);
            break;
        }
        case 0x2c9cc91: {
            ObjWithState* o = (ObjWithState*)ObjCast(obj, 0x2c9cc91);
            orient = (o->mFlags & 0x1000) == 0x1000;
            const BBox& bb = o->mSp34.GetBBox();
            const BBox* b = &bb;
            dir.x = (b->mMax.x + b->mMin.x) * 0.5f;
            dir.y = (b->mMax.y + b->mMin.y) * 0.5f;
            dir.z = (b->mMax.z + b->mMin.z) * 0.5f;
            xform.SetOffset(dir);
            int st = o->mState;
            if (st == 0 || st == 1 || st == 3) {
                effectId = 0x742deb5b;
            } else {
                facing = true;
                effectId = 0x4ae30884;
                snapA = true;
            }
            break;
        }
        case 0x3a2511e: {
            ObjWithMode* o = (ObjWithMode*)ObjCast(obj, 0x3a2511e);
            switch (o->mMode) {
            case 1:
            case 3:
                orient = (o->mFlags & 0x1000) == 0x1000;
                effectId = 0x4ae30884;
                break;
            case 2:
            case 6:
                effectId = 0x4ae30884;
                break;
            default:
                break;
            }
            facing = true;
            snapA = true;
            const BBox& bb = o->mSp34.GetBBox();
            const BBox* b = &bb;
            dir.x = (b->mMin.x + b->mMax.x) * 0.5f;
            dir.y = (b->mMax.y + b->mMin.y) * 0.5f;
            dir.z = (b->mMax.z + b->mMin.z) * 0.5f;
            xform.SetOffset(dir);
            if (effectId == 0) goto done;
            break;
        }
        case 0x52aa6122: {
            ObjSpatial34* o = (ObjSpatial34*)ObjCast(obj, 0x52aa6122);
            o->mSp34.LocalToWorldTransform(&xform);
            effectId = 0x4ae30884;
            break;
        }
        default:
            goto done;
        }

        cPlanetModel* pm = PlanetModel();
        Vec3 up;
        if (snapA) {
            xform.SetOffsetOOL(pm->SnapA(&up, &xform.mOffset, 0));
        } else if (snapB) {
            xform.SetOffsetOOL(pm->SnapB(&up, &xform.mOffset, 0));
        }
        Matrix3 rot;
        if (orient) {
            normalized_safe(&dir, &xform.mOffset);
            OrthogonalVector(&up, &dir);
            Matrix3FromFacingAndUp(&rot, &up, &dir);
            xform.mRotation = rot;
            xform.mFlags |= 2;
            xform.mModCount++;
        } else if (facing) {
            pm->Facing(&dir, &xform.mOffset);
            OrthogonalVector(&up, &dir);
            Matrix3FromFacingAndUp(&rot, &up, &dir);
            xform.mRotation = rot;
            xform.mFlags |= 2;
            xform.mModCount++;
        }
        XformMsg msg;
        msg.SetRot(xform.mRotation);
        msg.SetPos(xform.mOffset);
        msg.SetScale(1.0f);
        IEffectsManager* em = EffectsManager();
        effect.reset();
        if (em->CreateEffect(effectId, 0, &effect)) {
            effect.p->SetSourceTransform(&msg);
            effect.p->Start(0);
            cCreatureModeStrategy_s00d2_f940::Instance()->mOwner->mEffect = effect;
        }
    }
done:
    ;
}

// @ 0x00d2ffd0
int __cdecl ClassifyTarget(ObjHdr* obj, uint8_t* pHandled)
{
    *pHandled = 1;
    cSPCreatureBase* avatar = NounManager()->GetAvatar();
    bool inGameS;
    char flagS;
    int idxS;
    switch (obj->GetTypeID()) {
    case 0x18c88e4: {
        cObjB* ob = FUN_00bd8460(obj);
        if (GetCurrentGameMode() == 0x1654c10 && FUN_00f0a690(obj)) return 0x12;
        if (ob->mF38 != 0xf) goto notHandled;
        goto head2;
    }
    case 0x70703b3:
    head2:
        inGameS = GetCurrentGameMode() == 0x1654c10;
        if (inGameS && FUN_00f0a690(obj)) return 0x12;
        flagS = 0;
        idxS = inGameS ? gInteraction->mpState->FUN_00f1a320(avatar, obj, &flagS) : avatar->FUN_00c0f780();
        goto haveIdx;
    case 0x18c6de8:
        inGameS = GetCurrentGameMode() == 0x1654c10;
        if (inGameS && FUN_00f0a690(obj)) return 0x12;
        flagS = 0;
        idxS = inGameS ? gInteraction->mpState->FUN_00f1a320(avatar, obj, &flagS) : avatar->FUN_00c0f780();
    haveIdx:
        if (idxS == -1) {
            cSPCreatureBase* cr = FUN_00ae6740(obj);
            if (cr->FUN_00bfc480()) goto notHandled;
            if (avatar->FUN_00c0ee60() != (int)cr) return 7;
            return (FUN_00d2e490() != 0 ? 3 : 0) + 0xe;
        }
        if (FUN_00d2e490() == 0 || flagS) {
            if (avatar->mpB4C->mState == 0x39f6486) goto notHandled;
            if (inGameS && !gInteraction->mpState->FUN_00f1a440(idxS, obj)) goto notHandled;
            return 0xc;
        }
        if (inGameS && !gInteraction->mpState->FUN_00f1a640(idxS)) goto notHandled;
        return 0xd;
    case 0x18eb45e: {
        cSPCreatureBase* c = (cSPCreatureBase*)ObjCast(obj, 0x18eb45e);
        cSPCreatureBase* tgt = avatar->GetTargetAsCreature();
        bool isTarget = (c == tgt);
        bool sameTeam = (c->mB20 == avatar->mB20);
        if (avatar == c) {
            if (GetCurrentGameMode() == 0x1654c10) return 0x1c;
            int idx = avatar->FUN_00c0f780();
            if (idx == -1) return 0;
            ObjHdr* o = FUN_00ae66d0(avatar->FUN_00c0f8a0(idx));
            if (!o) return 0;
            uint32_t t = o->GetTypeID();
            if (t == 0x2a8fb3f || t == 0x3a2511e) return 6;
            return 0;
        }
        bool b = false;
        if (c->FUN_00c04750() && c->FUN_00c04750()->mB2 != 0) b = true;
        bool inGame = GetCurrentGameMode() == 0x1654c10;
        if (inGame && (c->mB5E == 0 || b)) {
            if (FUN_00f0a690(obj)) return 0x12;
        }
        if (c->mB5E != 0) {
            if (gFlag01582df6) {
                int idx = avatar->FUN_00c0f780();
                if (idx != -1 && FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) == 0) return 0x16;
            }
            if (sameTeam) return 0;
            if (!(c->FUN_00c0bb10() > 0.0f)) return 0;
            if (GetCurrentGameMode() == 0x1654c10) return 0;
            return 8;
        }
        char flag = 0;
        int idx = inGame ? gInteraction->mpState->FUN_00f1a320(avatar, obj, &flag) : avatar->FUN_00c0f780();
        if (idx != -1) {
            if (FUN_00d2e490() == 0 || flag) {
                if (c->FUN_00c0b770() && avatar->mpB4C->mState != 0x39f6486) {
                    int h = avatar->FUN_00c0f8a0(idx);
                    if (c->FUN_00c13c60(h, 1, !inGame)) {
                        if (!inGame) return 0xc;
                        if (gInteraction->mpState->FUN_00f1a440(idx, obj)) return 0xc;
                    }
                }
            } else if (!inGame || gInteraction->mpState->FUN_00f1a640(idx)) {
                int h = avatar->FUN_00c0f8a0(idx);
                if (!((c->mB58 >> 8 & 1) && FUN_00d2ede0(h))) return 0xd;
            }
        }
        uint32_t v = c->mB58;
        if (v >> 4 & 1) return 9;
        if (!isTarget) return 7;
        if (v >> 8 & 1) return 0xa;
        if (FUN_00d2e490() == 0) {
            if (avatar->mpB4C->mState == 0x39f6486) return 0xb;
            if (FUN_00b3d4c0()->FUN_00ba3f90(c->FUN_00c0bc00(), c, avatar) == 5 &&
                c->mpB48->FUN_00bca0c0(2, 1, 0, 0) == -1)
                return 0xe;
            if (GetCurrentGameMode() == 0x1654c10 && c->FUN_00c0c0e0()) return 0xe;
            if (c->GetSocialGoal() == 0 && c->VSlotD4()) return 0x10;
            return 0xf;
        }
        if (FUN_0064f350(cCreatureModeStrategy_s00d2_f940::Instance()->mRefB4.get(), 0x39b674a2, 0) &&
            avatar->FUN_00c13c60((int)((char*)c + 0xc0), 0, 1))
            return 0x19;
        return sameTeam ? 0 : 0x11;
    }
    case 0x18ebadc:
        return 0x1b;
    case 0x2a034cd: {
        cObjClick2a034cd* o = (cObjClick2a034cd*)ObjCast(obj, 0x2a034cd);
        if (o->mpF4 && o->mpF4->mA4 && o->mpF4->mA4 != avatar->mB20 && FUN_00d2e490() == 1 &&
            o->mState != 4 && o->mState != 5 && o->mState != 3) {
            if (FUN_00b3d4c0()->FUN_00ba3f90(o->mpF4->mA4 + 0x504, 0, 0) != 6) return 0x15;
        }
        int idx = avatar->FUN_00c0f780();
        if (idx == -1) goto notHandled;
        if (FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) != 0) goto notHandled;
        return 0x16;
    }
    case 0x2a8fb3f:
    case 0x3a2511e: {
        cEvtTarget* o = (cEvtTarget*)obj->Query(0x1186577);
        if (o->mF50 & 0x100) {
            return avatar->FUN_00c0f8f0(o) != -1 ? 0x18 : 0;
        }
        if (GetCurrentGameMode() == 0x1654c10 && FUN_00f0a690(obj)) return 0x12;
        if (o->mF70 == 0) goto notHandled;
        if (avatar->FUN_00c13c60((int)o, 0, GetCurrentGameMode() != 0x1654c10)) {
            if (avatar->FUN_00c0f620() == -1) {
                int idx = avatar->FUN_00c0f780();
                if (idx != -1 && FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) == 0) return 0x16;
            }
            return 0x19;
        }
        cObjC* t = FUN_00c0c3c0(o);
        if (t && t->mF110 == 2) return 0x1a;
        goto notHandled;
    }
    case 0x2c9cc91: {
        cObjClick2c9cc91* o = (cObjClick2c9cc91*)ObjCast(obj, 0x2c9cc91);
        if (o->mA4 == 0) goto notHandled;
        int st = o->mState;
        if (st == 4) goto notHandled;
        if (st == 0) {
            int idx = avatar->FUN_00c0f780();
            if (idx != -1 && FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) == 0) return 0x16;
        }
        return 0x17;
    }
    case 0x52aa6122: {
        cObjSp34* o = obj->GetTypeID() == 0x52aa6122 ? (cObjSp34*)obj : 0;
        if (o->FUN_00c6aa30() != avatar->mB20) goto notHandled;
        if (!o->mSp34.VSlot58()) {
            if (!NounManager()->GetCurrentTerrainSphere(0x514a219)->FUN_00c773d0()) return 0x14;
        }
        int idx = avatar->FUN_00c0f780();
        if (idx == -1) goto notHandled;
        if (FUN_00d2ec30(avatar->FUN_00c0f8a0(idx)) != 0) goto notHandled;
        return 0x13;
    }
    default:
        break;
    }
notHandled:
    *pHandled = 0;
    return 0;
}

// @ 0x00d30ee0
bool cCreatureModeInputStrategy_s00d3_0830::DidDoubleClick(uint32_t nKey)
{
    bool bResult = false;
    CRBTreeIterator it;
    mTimerMap.find(&it, nKey);
    if (it.mpNode != &mTimerMap.mAnchor)
    {
        CSpTimer* pcTimer = it.mpNode->mpTimer;
        if (pcTimer->IsRunning() && pcTimer->GetElapsedTime() <= gnDoubleClickThreshold)
        {
            pcTimer->Restart();
            bResult = true;
        }
        else
        {
            pcTimer->Restart();
        }
    }
    return bResult;
}

// @ 0x00d30f60
bool FUN_00d30f60(CNoun* pNoun)
{
    if (pNoun != 0)
    {
        if (GetNounManager()->GetAvatar()->GetSelectedNoun() == pNoun)
            return true;

        uint32_t nTarget   = pNoun->GetInteractionTarget();
        bool     bIsTarget = false;
        uint32_t eTarget   = ClassifyTarget(nTarget, &bIsTarget);
        if (bIsTarget && eTarget == 7)
            return true;
    }
    return false;
}

// @ 0x00d317e0
bool FUN_00d317e0(int param_1)
{
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        return false;
    }
    switch (FUN_00d30830((void*)param_1)) {
    case 3:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
        return true;
    }
    return false;
}

// @ 0x00d31840
void FUN_00d31840(Ref* first, int top, int len, int hole, Value val)
{
    int idx;
    for (; (idx = 2 * hole + 2) < len; hole = idx) {
        if (val.mCmp(first[idx], first[idx - 1])) {
            --idx;
        }
        first[hole] = first[idx];
    }
    if (len == idx) {
        first[hole] = first[idx - 1];
        hole = idx - 1;
    }
    FUN_00d2f880(first, top, hole, val);
}

// @ 0x00d31980
void FUN_00d31980(Ref* first, Ref* last, Prior val)
{
    Ref tmp(*(last - 1));

    *(last - 1) = *first;

    FUN_00d31840(first, 0, (int)(last - first) - 1, 0, Value(val, tmp.p));
}

// @ 0x00d31a70
namespace SP {
bool cCreatureModeInputStrategy_s00d3_1a70::UpdateAvatarGoal(bool mouseMode, bool spawnEffect)
{
  cCreatureAnimal* avatar = NounManager_s00d3_1a70()->GetAvatar();
  Vector3 forward, right;
  GetCameraMoveVectors(&forward, &right);

  bool issued = false;
  if (avatar->mbDead || !mbUpdateAvatarGoals)
    return issued;

  Vector3 goal = g_NoGoal;
  bool applyMoveTarget = true;
  bool moveKeys = false;

  if (!mouseMode) {
    goal = avatar->mLoco.GetPosition();
    cGameInputManager_s00d3_1a70* input = GameInputManager_s00d3_1a70();
    if (IsStrafeLeftDown() || IsStrafeRightDown() ||
        (input->IsKeyDown(2) && !input->IsKeyDown(1)))
      moveKeys = true;
    else
      moveKeys = false;
    if (IsStrafeLeftDown()) {
      goal.x = goal.x - right.x * g_StepLength;
      goal.y = goal.y - right.y * g_StepLength;
      goal.z = goal.z - right.z * g_StepLength;
    }
    if (IsStrafeRightDown()) {
      goal.x = right.x * g_StepLength + goal.x;
      goal.y = right.y * g_StepLength + goal.y;
      goal.z = right.z * g_StepLength + goal.z;
    }
    if (GameInputManager_s00d3_1a70()->IsKeyDown(2)) {
      goal.x = goal.x - forward.x * g_StepLength;
      goal.y = goal.y - forward.y * g_StepLength;
      goal.z = goal.z - forward.z * g_StepLength;
    }
    if (GameInputManager_s00d3_1a70()->IsKeyDown(1) || g_bAutoRun) {
      goal.x = forward.x * g_StepLength + goal.x;
      goal.y = forward.y * g_StepLength + goal.y;
      goal.z = forward.z * g_StepLength + goal.z;
    }
  } else {
    Vector3 tmp;
    goal = *PosSource()->GetPickPosition(&tmp, 1);

    cPickedThing* picked = PosSource()->GetPicked();
    if (picked) {
      cPickedThing* obj = (cPickedThing*)picked->Cast(0x17f243b);
      if (obj && ((uint32_t(__thiscall*)(void*))VFUNC(obj, 0x20))(obj) == 0x52aa6122) {
        cRayComponent* comp = (cRayComponent*)interface_cast_IID(obj, 0x52aa6122);
        cRayCaster* caster = comp->sub.GetCaster();
        void* ignore = comp->sub.GetIgnore();
        if (caster && ignore) {
          float t = 0.0f;
          Vector3 origin, end;
          App()->GetRender()->GetViewer()->GetCameraRayPoints(&origin, &end);
          Vector3 delta(end.x - origin.x, end.y - origin.y, end.z - origin.z);
          float len = sqrtf((delta.z * delta.z + delta.y * delta.y) + delta.x * delta.x);
          if (len > g_MaxRayLength) {
            float f = g_MaxRayLength / len;
            end.x = delta.x * f + origin.x;
            end.y = delta.y * f + origin.y;
            end.z = delta.z * f + origin.z;
          }
          cRayQuery q;
          q.a = q.b = q.c = q.d = q.e = 0;
          q.mode = 3;
          q.flag = 1;
          if (caster->Cast(&origin, &end, ignore, &t, &q)) {
            goal.x = (end.x - origin.x) * t + origin.x;
            goal.y = (end.y - origin.y) * t + origin.y;
            goal.z = (end.z - origin.z) * t + origin.z;
            applyMoveTarget = false;
          }
        }
      }
    }
    const Vector3& apos = avatar->mLoco.GetPosition();
    float dx = goal.x - apos.x, dy = goal.y - apos.y, dz = goal.z - apos.z;
    float dist = sqrtf((dz * dz + dy * dy) + dx * dx);
    float r = avatar->mLoco.GetRadius();
    if (dist < r * g_HalfFactor)
      return false;
  }

  if (goal.x != g_NoGoal.x || goal.y != g_NoGoal.y || goal.z != g_NoGoal.z) {
    Vector3 pos = avatar->mLoco.GetPosition();
    Vector3 delta(goal.x - pos.x, goal.y - pos.y, goal.z - pos.z);
    Vector3 dir = delta;
    float len = sqrtf(delta.x * delta.x + (delta.y * delta.y + delta.z * delta.z));
    if (len > g_StopMaxDistance) {
      float f = g_StopMaxDistance / len;
      goal.x = delta.x * f + pos.x;
      goal.y = delta.y * f + pos.y;
      goal.z = delta.z * f + pos.z;
      pos = goal;
    } else {
      float speed = avatar->mLoco.GetRadius();
      const float* m = &g_StopRadiusCap;
      if (!(speed > g_StopRadiusCap))
        m = &speed;
      if (len < *m) {
        cLocomotionRequest req;
        avatar->mLoco.RequestMove(req);
        if ((avatar->mpBehavior->mFlags & 0x10801) == 0) {
          avatar->PlayAnimation(0x100000, kFloatMax, 0, 0, 0, 0);
          SpawnAcknowledgementEffect(0x100000, 0, 0);
        }
        return true;
      }
      if (mMouseDownTimer.GetElapsedTime() > (uint64_t)g_ClickMoveTimeMs) {
        float speed2 = avatar->mLoco.GetRadius();
        const float* m2 = &len;
        if (!(len > speed2))
          m2 = &speed2;
        Vector3 n;
        Vector3* nd = normalized_safe(&n, &dir);
        goal.x = nd->x * *m2 + pos.x;
        goal.y = nd->y * *m2 + pos.y;
        goal.z = nd->z * *m2 + pos.z;
      }
    }
    if (applyMoveTarget)
      SetAvatarMoveTarget(avatar, &goal);

    bool newAutoRun = g_bAutoRun && !mouseMode;
    if (!mouseMode && moveKeys) {
      Vector3 face = forward;
      avatar->MoveToPointFacing(2, &goal, &face, g_MoveGoalMinDist, g_MoveGoalMaxDist);
    } else {
      Vector3 face;
      normalized_safe(&face, &dir);
      avatar->MoveToPointAndFacingAtSpeed(2, &goal, &face, g_MoveGoalMinDist, g_MoveGoalMaxDist);
    }
    if ((avatar->mpBehavior->mFlags & 0x10801) == 0) {
      avatar->PlayAnimation(0x100000, kFloatMax, 1, 0, 0, 0);
      SpawnAcknowledgementEffect(0x100000, 0, 0);
    }
    g_bAutoRun = newAutoRun;
    issued = true;
  }
  if (mouseMode && issued && spawnEffect)
    SpawnMovementGoalEffect(&goal);
  return issued;
}
}  // namespace SP

// @ 0x00d34f90
void cCreatureModeInputStrategy_s00d3_4f90::FUN_00d34f90(int arg)
{
    IGameInputManager* pInput = (IGameInputManager*)GameInputManager();
    if (pInput) {
        if (mbActive)
            UpdateCreaturePickBoxes();
        FUN_00d32df0(pInput, arg);
    }
}

// @ 0x00d34fc0
void FUN_00d34fc0(void* first, void* last, Compare7 compare)
{
    FUN_00d340d0(first, last, compare);
}

// @ 0x00d35190
namespace SP {
bool cCreatureModeInputStrategy_s00d3_5190::HandleMessage(uint32_t messageID, IMessageData* pMessage)
{
  if (messageID == 0x477f66c) {
    UIManagerA()->Reset();
    cCreatureModeStrategy_s00d3_5190::Instance()->mpSub->Exit(0);
    HintManager()->ShowHint(1, 0x1654c02, 1);
    if (mbHoldingObject) {
      mbReleaseHeld = true;
      return true;
    }
    GameModeManager()->Leave(0x1654c02);
    return true;
  }
  if (messageID == 0xd33b6aa2) {
    mMouseDownTime.Stop();
    return true;
  }
  if (!mbEnabled)
    return true;

  // Banning mode.
  if (messageID == 0x44eaa93) {
    BeginBanMode();
    return true;
  }
  if (GameInputManager_s00d3_5190()->GetMode() == 2) {
    if (messageID == 0x452e0ca) {
      cUIBanningContent::EndBanMode(1);
      GameInputManager_s00d3_5190()->SetMode(0);
    } else if (messageID == 0xb332763d) {
      cGameDataRef* ref = (cGameDataRef*)pMessage->GetArgs()->GetArg(0);
      if (ref) {
        void* obj = ref->GetObject();
        if (obj)
          cUIBanningContent::ShowConfirmationDialog(obj);
      }
    } else if (messageID == 0xf3327645) {
      BeginBanMode();
    }
    return true;
  }

  // Tribe-tool mode.
  if (messageID == 0x620222b) {
    BeginTribeToolMode();
    return true;
  }
  if (GameInputManager_s00d3_5190()->GetMode() == 3) {
    if (messageID == 0x620271c) {
      TribeToolEndMode(0);
      GameInputManager_s00d3_5190()->SetMode(0);
    } else if (messageID == 0x62663dc) {
      cGameDataRef* ref = (cGameDataRef*)pMessage->GetArgs()->GetArg(0);
      if (ref) {
        void* obj = ref->GetObject();
        if (obj)
          TribeToolConfirm(obj);
      }
    } else if (messageID == 0x62663dd) {
      BeginTribeToolMode();
    }
    return true;
  }

  cCreatureAnimal_s00d3_5190* avatar = NounManager_s00d3_5190()->GetAvatar();
  if (avatar->mbDead)
    return true;

  // Message arguments: picked object and an optional integer.
  cGameDataRef* picked;
  const Variant* pValue = 0;
  IMessageArgs* args;
  if (pMessage != 0 && (args = pMessage->GetArgs()) != 0) {
    picked = (cGameDataRef*)args->GetArg(0);
    pValue = (const Variant*)args->GetArg(1);
    args->GetArg(2);
  } else {
    picked = 0;
  }
  uint32_t value = *(pValue ? pValue : &Variant(0))->GetUInt32();

  if ((CreatureSettings()->mFlags >> 4) & 1) {
    if (messageID == 0x1c41da1) {
      avatar->SetFlagE8(1);
      cPosseSimulator* posse = PosseSimulatorInstance();
      if (posse)
        posse->Disband(1);
      avatar->SetCreatureTarget(0, false, 0);
    }
    return true;
  }

  switch (messageID) {
  case 0x1c0e5ee: {   // DNA cheat
    float dna = GetCurrentDNA();
    cCreatureModeStrategy_s00d3_5190::NotifyEvent(dna * 1.1f + 50.0f - dna);
    return true;
  }

  case 0x19edcf3:     // start moving with the mouse
    avatar->mbB5C = false;
    if (!mMouseDownTime.IsRunning()) {
      mMouseDownTime.Start();
      mbMouseMoved = false;
    }
    UpdateAvatarGoal(true, false);
    g_bShowAvatarGoal = true;
    return true;

  case 0x19d5174:     // auto-run
    if (g_bAutoRunLocked) {
      ToggleAutoRun();
      g_bShowAvatarGoal = false;
    } else {
      UpdateAvatarGoal(true, true);
      g_bShowAvatarGoal = true;
    }
    return true;

  case 0x1c0e6e7: {   // brain level up cheat
    int maxLevel = 4;
    int level = avatar->GetCurrentBrainLevel() + 1;
    avatar->SetCurrentBrainLevel(maxLevel < level ? maxLevel : level);
    cPosseSimulator* posse = PosseSimulatorInstance();
    if (posse)
      posse->mState = 3;
    return true;
  }

  case 0x1c38e3b:     // rollover
    SetRolloverObject(picked ? picked->GetObject() : 0);
    return true;

  case 0x1c41da1:     // cancel / deselect
    if (avatar->GetTarget() != 0) {
      avatar->SetCreatureTarget(0, false, 0);
    } else if (GameInputManager_s00d3_5190()->GetMode() == 0) {
      MessageServer()->Post(0x64eb18e, 0, 0);
    }
    return true;

  case 0x1c6d8ad: {   // heal cheat
    cCreatureAnimal_s00d3_5190* creature = avatar;
    if (picked) {
      void* obj = picked->GetObject();
      if (obj) {
        cCreatureAnimal_s00d3_5190* c = (cCreatureAnimal_s00d3_5190*)interface_cast_IID(obj, 0x18eb45e);
        if (c)
          creature = c;
      }
    }
    if (creature && creature->mpSpeciesProfile) {
      creature->mCombatant.PartialRepair(20.0f);
      creature->SetHealth(creature->GetHealth() + 20.0f);
    }
    return true;
  }

  case 0x248d179:
    cCreatureModeStrategy_s00d3_5190::Instance()->NotifyWantToGoToEditor(1);
    return true;

  case 0x274847c: {   // select / deselect UI object
    if (!picked)
      return true;
    void* obj = picked->GetObject();
    if (!obj)
      return true;
    cUIRefCounted* p = interface_cast_Selectable(obj);
    if (!p)
      return true;
    if (g_pSelectedUI.mp == p) {
      cUIRefCounted* old = g_pSelectedUI.mp;
      if (old) {
        g_pSelectedUI.mp = 0;
        old->Release();
      }
    } else {
      g_pSelectedUI.Assign(p);
    }
    return true;
  }

  case 0x2c4bfda: {   // toggle HUD canvas
    bool visible = MainCanvas()->IsVisible();
    MainCanvas()->SetVisible(!visible);
    return true;
  }

  case 0x2c4bfde:
    mbMouseMoved = (value == 0);
    return true;

  case 0x3c7560d:
    avatar->PlayAnimation(0x0004000000000000ULL, kFloatMax, 2, 0, 0, 0);
    SpawnAcknowledgementEffect(0, 0x40000, 0);
    return true;

  case 0x4fe41c0: {   // SETI zap of the picked creature
    if (!picked)
      return true;
    void* obj = picked->GetObject();
    if (!obj)
      return true;
    cCreatureAnimal_s00d3_5190* c = (cCreatureAnimal_s00d3_5190*)interface_cast_IID(obj, 0x18eb45e);
    if (!c || !c->mpSpeciesProfile)
      return true;
    cSPUISpace::KillSetiEffects(0x65f6559d, GetRecorderState());
    cCombatant_s00d3_5190* combatant = &c->mCombatant;
    combatant->TakeDamage(combatant->GetMaxHitPoints() * 0.25f, (uint32_t)-1, 2, g_SetiDamageDir, 0);
    return true;
  }

  case 0x65fa504:
    ToggleDebugDisplay();
    return true;

  case 0x64d50e0: {   // target the picked creature
    if (!picked)
      return true;
    cCreatureAnimal_s00d3_5190* c = interface_cast_Animal(picked->GetObject());
    if (!c)
      return true;
    Tutorial()->Select(c);
    avatar->SetCreatureTarget(&c->mCombatant, false, 0);
    avatar->mpBehavior->mSub.Notify(0x100000, kFloatMax, 0);
    return true;
  }

  case 0x51893a3:     // pick a target
    if (PickTarget(avatar))
      avatar->mpBehavior->mSub.Notify(0x100000, kFloatMax, 0);
    return true;

  case 0x13cdf6fa:
    SetHUDHidden(IsHUDHidden() == 0, 1);
    return true;

  case 0x50e6232d: {
    if (!picked)
      return true;
    void* obj = picked->GetObject();
    if (!obj)
      return true;
    cUIRolloverTarget* r = interface_cast_Rollover(obj);
    if (r)
      r->Activate();
    return true;
  }

  case 0x53c4bde7:
    g_bFreeCamera = !g_bFreeCamera;
    if (g_bFreeCamera)
      ToggleAutoRun();
    return true;

  case 0x716b83ff: {  // kill cheat: everything of another kind within 10 m
    char tag;
    for (NearbyIterator it(avatar->mNearbyCreatures, &tag); it.mpCur != it.mpEnd; it.Next()) {
      cCreatureAnimal_s00d3_5190* c = interface_cast_Animal(((void**)*it.mpCur)[2]);
      if (c && !c->mbDead && !((c->mGeneralFlags >> 8) & 1)) {
        const Vector3_s00d3_5190& a = avatar->mLoco.GetPosition();
        const Vector3_s00d3_5190& b = c->mLoco.GetPosition();
        float dx = b.x - a.x, dy = b.y - a.y, dz = b.z - a.z;
        if (100.0f > dz * dz + dy * dy + dx * dx) {
          c->mCombatant.TakeDamage(1000.0f, 0, 2, g_KillDamageDir, 0);
          if (c->mCombatant.GetCombatState() == 2) {
            struct { cCreatureAnimal_s00d3_5190* killer; cCreatureAnimal_s00d3_5190* victim; int x; } msg = { avatar, c, 0 };
            cCreatureModeStrategy_s00d3_5190::spInstance->PostKillMessage(0xd335362c, &msg);
          }
        }
      }
    }
    return true;
  }

  case 0x940666d2:
    CinematicManager()->Stop(0);
    return true;

  case 0x915a6a39: {  // tag every creature within 10 m
    char tag;
    for (NearbyIterator it(avatar->mNearbyCreatures, &tag); it.mpCur != it.mpEnd; it.Next()) {
      cCreatureAnimal_s00d3_5190* c = interface_cast_Animal(((void**)*it.mpCur)[2]);
      if (c && !c->mbDead && !((c->mGeneralFlags >> 8) & 1)) {
        const Vector3_s00d3_5190& a = avatar->mLoco.GetPosition();
        const Vector3_s00d3_5190& b = c->mLoco.GetPosition();
        float dx = b.x - a.x, dy = b.y - a.y, dz = b.z - a.z;
        if (100.0f > dz * dz + dy * dy + dx * dx) {
          c->mGeneralFlags |= 0x80;
          Tutorial()->Tag(3, c->mb28, c);
        }
      }
    }
    EditorLauncher()->Launch(0);
    return true;
  }

  case 0xb0ee272f: {  // spawn a creature of the avatar's species nearby
    NounManager_s00d3_5190();
    Vector3_s00d3_5190 pos = PlanetModel_s00d3_5190()->MakeRandomWorldPosition(avatar->mLoco.GetPosition(), 3.0f, 6.0f);
    cCreatureAnimal_s00d3_5190* c = NounManager_s00d3_5190()->CreateCreature(pos, avatar->mpSpeciesProfile, 1, 0, 0, 0);
    if (c) {
      cCreatureAnimal_s00d3_5190* t = avatar->GetSpeciesTemplate();
      c->m88 = t->m88;
      c->mf0 = t->mf0;
      c->SetupFromTemplate(1);
      c->FinishSetup();
    }
    return true;
  }

  case 0xd34b9713:    // max brain cheat
    avatar->SetCurrentBrainLevel(4);
    g_CheatEventKind = 4;
    cCreatureModeStrategy_s00d3_5190::NotifyEvent(g_DNAReward[0] + g_DNAReward[1] + g_DNAReward[2] + g_DNAReward[3]);
    return true;

  case 0xd02dcc68: {  // mouse released
    cSPTimer_s00d3_5190* timer = &mMouseDownTime;
    if (timer->GetElapsedTime() > g_ClickMoveTimeMs && mbMoveOnRelease) {
      cLocomotiveObject_s00d3_5190* loco = &avatar->mLoco;
      const Vector3_s00d3_5190& pos = loco->GetPosition();
      Vector3_s00d3_5190 dir = loco->GetDirection();
      float dist = avatar->IsInWater() ? 4.5f : 2.0f;
      Vector3_s00d3_5190 target;
      target.x = dir.x * dist + pos.x;
      target.y = pos.y + dir.y * dist;
      target.z = pos.z + dir.z * dist;
      SetAvatarMoveTarget(avatar, target);

      float cosA = Dot3(loco->GetDirection(), loco->GetVelocity());
      cosA = Clamp(cosA, -1.0f, 1.0f);
      float turn = Clamp(acosf(cosA) * 1.4285715f, 0.0f, 1.0f);
      float d = turn * 1.1f + 0.4f;
      loco->RequestMove(MoveGoal(target, d + g_MoveGoalMinDist, d + g_MoveGoalMaxDist));
      if (!avatar->mb137 && !(avatar->mf110 & 0x1000))
        loco->RequestMove(MoveGoal());
      if ((avatar->mpBehavior->mFlags & 0x10801) == 0) {
        avatar->PlayAnimation(0x100000, kFloatMax, 0, 0, 0, 0);
        SpawnAcknowledgementEffect(0x100000, 0, 0);
      }
    } else if (value > 0) {
      avatar->mbB5C = false;
      UpdateAvatarGoal(true, true);
      if (!avatar->mLoco.IsIdle())
        avatar->ReturnToIdle(1);
    }
    g_bShowAvatarGoal = !g_bAutoRunLocked;
    timer->Stop();
    mbMouseMoved = true;
    return true;
  }
  }
  return true;
}
}  // namespace SP

// @ 0x00d366c0
void cCreatureModeInputStrategy_s00d3_66c0::InitCursors()
{
    CursorTable* pCursors = GetCursorTable();
    pCursors->AddCursor(0x514ab7b0, L"cursor-target", 1, 0, 0);
    pCursors->AddCursor(0x314ab7b1, L"cursor-mate", 1, 0, 0);
    pCursors->AddCursor(0xf14ab7b3, L"cursor-heal", 1, 0, 0);
    pCursors->AddCursor(0xb14ab7b6, L"cursor-eat-fruit", 1, 0, 0);
    pCursors->AddCursor(0x514ab7b7, L"cursor-eat-carcass", 1, 0, 0);
    pCursors->AddCursor(0xb14ab7b9, L"cursor_atk", 1, 0, 0);
    pCursors->AddCursor(0x114ab7ba, L"cursor-evolve", 1, 0, 0);
    pCursors->AddCursor(0x514abe0b, L"cursor-validate", 1, 0, 0);
    pCursors->AddCursor(0x71664d85, L"cursor_social", 1, 0, 0);
    pCursors->AddCursor(0x755c4eb5, L"cursor_friend", 1, 0, 0);
    pCursors->AddCursor(0xf4f6c345, L"cursor_socialNo", 1, 0, 0);
    pCursors->AddCursor(0x03b360d8, L"cursor-crg-addposse", 1, 0, 0);
    pCursors->AddCursor(0x03b360dc, L"cursor-crg-pickup", 1, 0, 0);
    pCursors->AddCursor(0x03b360df, L"cursor-crg-putdown", 1, 0, 0);
    pCursors->AddCursor(0x7542cdb5, L"cur_ClaimNest", 1, 0, 0);
    pCursors->AddCursor(0x03b360e2, L"cursor-crg-give", 1, 0, 0);
    pCursors->AddCursor(0x03b360e4, L"cursor-crg-throw", 1, 0, 0);
    pCursors->AddCursor(0xf36a0c84, L"cursor-target-creature", 1, 0, 0);
    pCursors->AddCursor(0x342d221f, L"cursor_skeleton2", 1, 0, 0);

    cMessageServer_s00d3_66c0* pServer = EA::Messaging::GetServer();
    cMessageHandler* pHandler = this;
    mpMessageServer = pServer;
    mpMessageHandler = pHandler;
    mpMessageTable = gMessageIds;
    mnMessageCount = 0x1b;
    mnUnk098 = 0;
    if (pServer != 0 && pHandler != 0) {
        for (uint32_t nOffset = 0; nOffset < 0x6c; nOffset += 4)
            ((void (__thiscall*)(cMessageServer_s00d3_66c0*, cMessageHandler*, uint32_t))
                 ((void**)pServer->mpVtable)[0x24 / 4])(
                pServer, pHandler,
                *(uint32_t*)((char*)gMessageIds + nOffset));
    }

    SetInputPriorityStrategy(0);
    InitSubstate();

    cDirectPropertyList* pProperties = gAppProperties;
    cProperty* pProperty;
    if (pProperties != 0 &&
        ((bool (__thiscall*)(cDirectPropertyList*, int, cProperty**))
             ((void**)pProperties->mpVtable)[0x24 / 4])(
            pProperties, 0x064a44a8, &pProperty) &&
        pProperty->mnType == 1) {
        mbUseKeyArray = *pProperty->GetBool();
    }
    mbUnk105 = false;
}
