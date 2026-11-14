// src/game/SPGonzago/_at_00e30000.cpp -- migrated from slice(s) s00e39ab0, s00e36150, s00e34290, s00e33270, s00e31670, s00e30790, s00e2f6e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00e30000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <math.h>
#include "EA/Variant.h"
#include "cSPUIAnimator.h"
#include "cSPUILayout.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/Image.h"
#include "EA/UTFWin/Message.h"
#include "EA/UTFWin/RenderContext.h"
#include "SP/cSPSwatch.h"
#include "EA/Stopwatch.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include <stddef.h>

// unnamed retail callees and globals (address in the comment)
extern const float gRotationAngle;

// ---- items of slice s00e2f6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef int intptr_t;
#define nullptr 0
struct Rect {
    float mX;
    float mY;
    float mWidth;
    float mHeight;
};
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class IWindow : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void SetVisible(bool bVisible);
    virtual void v20();
    virtual void v24();
    virtual void v28(int a);
    virtual void v2c();
    virtual Rect* GetArea();
    virtual void SetPosition(float fX, float fY);
    virtual void SetScale(float fScale);
};
class cSPUILayout_s00e2_f6e0 {
public:
    void Init(const wchar_t* pName, uint32_t a, int b, uint32_t c);  // 0x00812160 (cSPUILayout::Init)
    IWindow* FindWindowByID(uint32_t nId, int bFind);  // 0x008105b0 (cSPUILayout::FindWindowByID)
};
class cMessageServer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20(void* pTarget, uint32_t nMessage);
    virtual void v24();
    virtual void v28(void* pTarget, uint32_t nMessage, int nData);
    virtual void v2c(void* pTarget, uint32_t nMessage, int nData);
};
class cSPUIAnimator_s00e2_f6e0 {
public:
    void AddAnimation(void* pAnimation, void* pTarget, int nKind);  // 0x007f8d10 (cSPUIAnimator::AddAnimation)
    void RemoveAnimation(void* pTarget, int nIndex);  // 0x007f6210 (cSPUIAnimator::RemoveAnimation)
    void Update();  // 0x007f63b0 (cSPUIAnimator::Update)
};
class cSPAssetData : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    bool IsDiscovered();
    uint8_t mPad18[0x08];
};
class cSPUIAssetView : public IWindow {
public:
    void Bind(IWindow* pParent, cSPAssetData* pData, int a, int b);
};
class cMessageTarget {
public:
    virtual void v00();
    virtual void v04();
};
class cSPUIAssetDiscoveryCard : public IRefCounted {
public:
    void Init();
    void ApplyFrame(int* pData);
    cSPUIAssetDiscoveryCard* Clone();

    cSPUILayout_s00e2_f6e0* mpLayout;              // 0x00
    IWindow* mpParentWin;               // 0x04
    uint8_t mPad08[0x08];               // 0x08
    IWindow* mpTextWindow;              // 0x10
    cSPAssetData* mpAssetData;          // 0x14
    cSPUIAssetView* mpAssetView;        // 0x18
};
class cSPUIAssetDiscoveryManager : public cMessageTarget {
public:
    void Init();
    void ReloadTuning();
    void Shutdown();
    void Reset();
    void Update(uint nMilliseconds);
    int HandleCardMessage(int nMessage, int nData, int nFlags);
    int HandleAssetMessage(int nMessage, int nData);
    void ReleaseCurrentCard();
    void PushCard(cSPUIAssetDiscoveryCard** ppCard, int nFlags);

    uint8_t mPad14[0x0c];               // 0x14
    void* mpMessageTarget;              // 0x20
    uint8_t mPad24[0x08];               // 0x24
    cSPUIAssetDiscoveryCard** mpCardsBegin;   // 0x2c
    cSPUIAssetDiscoveryCard** mpCardsCur;     // 0x30
    cSPUIAssetDiscoveryCard** mpCardsEnd;     // 0x34
    cSPUIAssetDiscoveryCard** mpCardsCap;     // 0x38
    cSPUIAssetDiscoveryCard* mpCurrentCard;   // 0x3c
    cSPUIAssetDiscoveryCard* mpSelectedCard;  // 0x50
    int mnPaused;                       // 0x54
    int mnAnimationState;               // 0x58
    cSPUIAnimator_s00e2_f6e0* mpAnimator;          // 0x5c
    uint64_t mnElapsed;                 // 0x60
    int mnSlideInStart;                 // 0x68
    int mnSlideOutStart;                // 0x6c
    int mnRotateStart;                  // 0x70
    int mnZoomStart;                    // 0x74
    int mnStopLow;                      // 0x78
    int mnStopHigh;                     // 0x7c
    int mnScaleLow;                     // 0x80
    int mnScaleHigh;                    // 0x84
    int mnRotateLow;                    // 0x88
    int mnRotateHigh;                   // 0x8c
    int mnZoomLow;                      // 0x90
    int mnZoomHigh;                     // 0x94
    int mnFinalLow;                     // 0x98
    int mnFinalHigh;                    // 0x9c
    float mFinalScale;                  // 0xa0
    float mTimeStart;                   // 0xa4
    float mTimeScaleBack;               // 0xa8
    float mTimeRotate;                  // 0xac
    float mTimeStop;                    // 0xb0
    float mTime;                        // 0xb4
    int mCount;                         // 0xb8
    int64_t mTimeStopMS;                // 0xbc
    int64_t mTimeStartMS;               // 0xc4
    int64_t mTimeScaleBackMS;           // 0xcc
    int64_t mTimeRotateMS;              // 0xd4
    int64_t mTimeMS;                    // 0xdc
};
void* operator_new(size_t nSize, const char* pName, int a, int b, const char* pFile, int nLine);
void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void operator_delete__(void* pMemory);
void* MessageServer();
uint32_t GetCurrentGameMode();
void SetGlobalProperty(uint32_t key, uint32_t valueBits);
void GetMainWindowArea(Rect* pOut);
float GetElapsedSeconds(int nStart, int a, void* pTarget, int b);
void* CreateScaleAnimation(void* pBuffer, void* pTarget, int nStart, float fDuration);
void* CreateRotationAnimation(void* pBuffer, void* pTarget, int a, int b, int c, float fAngle,
                             float fDuration);
void* CreateTimerInterpolation(void* pBuffer, float fDuration);
void* CreateScaleAnimationFloat(void* pBuffer, void* pTarget, uint32_t fScale, void* pTimer);
void SetWindowScale(void* pWindow, int a);
void SetWindowPosition(void* pWindow, float fX, float fY);
void UpdateWindowState(void* pWindow);
void* GetTutorialArea(Rect* pOut);
void GetTribeArea(Rect* pOut);
void ResetCardState();
void FlushCardAnimations();
void PushCardInternal();
void ResetAnimationState();
void ResetDiscoveryAnimation();
bool IsCardVisible(void* pCard);
void* GetCardTarget(void* pCard);
extern uint8_t gGameModeSpace;
extern uint8_t gGameModeTribe;
extern const float gRotationAngle;
// ---- items of slice s00e2f6e0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern uint8_t gGameModeSpace;
extern uint8_t gGameModeTribe;

// ---- items of slice s00e30790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl sinf(float);
extern void* g_vt_card0;     // 0x1481968
extern void* g_vt_paint;     // 0x13eb394
extern void* g_vt_gon0;      // 0x14818d8
extern void* g_vt_gon1;      // 0x14818d0
extern void* g_vt_gon2;      // 0x14818c0
#pragma intrinsic(sinf)
void* __cdecl operator_new(unsigned, const char*, int, int, int, int);        // 0xf473a0
void  __cdecl operator_delete(void*);                                          // 0xf47380
void* __cdecl FUN_00847ff0(void*, void*, void*);                               // 0x847ff0
void  __cdecl EA_RemoveHandler(int, int, int, int, int);                       // 0x571db0
int   __cdecl SP_PropertyManager(void);                                        // 0x67de30
void* __cdecl SPUIShader_AcquireShaderProxy(void);                             // 0x82f630
void* __cdecl FUN_00e2e8a0(void*, void*, void*, int);                          // 0xe2e8a0
void  __cdecl FUN_00ac9480(void*, void**);                                     // 0xac9480
struct TC {
    void  f_d73090(void*, void*);      // 0x00d73090
    void  f_d018d0(void*, void*);      // 0x00d018d0
    void  f_ca09f0(int);               // 0x00ca09f0
    void  f_60e660(void);              // 0x0060e660
    void  f_b5b9a0(void);              // 0x00b5b9a0
    void  f_b5b960(void);              // 0x00b5b960
    void  f_e2f480(void*);             // 0x00e2f480
    void* f_e30740(void*);             // 0x00e30740
    void  f_e2f3f0(void*, unsigned);   // 0x00e2f3f0
    void  f_e2ff50(void*, void*);      // 0x00e2ff50
    void  f_ac9480(void*);             // 0x00ac9480
    void  f_e2fcb0(void*);             // 0x00e2fcb0
    void  f_b5f950(void*);             // 0x00b5f950
    void  f_e30010(void*);             // 0x00e30010
    void  f_a3b2c0(void*, void*);      // 0x00a3b2c0  hashtable::find
    void  f_811ad0(int);               // 0x00811ad0
    char  f_810070(void);              // 0x00810070
    void  f_e2f6e0(int);               // 0x00e2f6e0
    void  f_e63d60(void*, void*);      // 0x00e63d60
};
struct AllocHeader {
    int mRefCount;   // +0x00 (-4 from the element pointer)
};
struct Elem1c {
    uint32_t f0, f4, f8;
    void*    fc;
    uint32_t f10;
    uint8_t  f14;
    char     _pad[3];
    uint32_t f18;
};
struct NodeList {
    uint32_t pad0;
    void**   array;   // +0x04
    int      count;   // +0x08
    int      cap;     // +0x0c
    void destroy(void** a, unsigned n);   // 0x00e308d0
};
struct Vec1c {
    Elem1c* begin;    // +0x00
    Elem1c* end;      // +0x04
    Elem1c* cap;      // +0x08
    void  insert_(Elem1c* pos, const Elem1c* val);   // 0x00e30790
    void  push_back_default();                       // 0x00e30c00
    void  erase(void* a, void* b);                   // 0x00d018d0
    Elem1c* erasedAt(Elem1c* p);                     // 0x00e30740
};
struct VecHolder {
    char   pad0[0x10];
    Elem1c* begin;    // +0x10
    Elem1c* end;      // +0x14
    void  remove_head(uint32_t key);                 // 0x00e30a60
    void  remove_off8(uint32_t key);                 // 0x00e30ae0
};
struct MgrVec {
    char   pad0[0x0c];
    int    counter;   // +0x0c
    Vec1c  vec;       // +0x10
    char   pad1[0x24 - 0x1c];
    char   ht[0x0c];  // +0x24
    void  update(int dt);   // 0x00e30990
};
struct HashNode {
    HashNode* mpNext;                             // +0x00
    uint32_t  mKey;                               // +0x04  (pair<const unsigned int, wstring> starts here)
    void*     mpNameBegin;                        // +0x08
    void*     mpNameEnd;                          // +0x0c
    void*     mpNameCap;                          // +0x10
};
struct HashIter {
    HashNode* mpNode;                             // +0x00
    uint32_t  mBucket;                            // +0x04
};
struct HashValue {
    uint32_t  mKey;                               // +0x00
    void*     mpName;                             // +0x04
    uint32_t  mPad08;                             // +0x08
    void*     mpOwner0;                           // +0x0c
    void*     mpOwner1;                           // +0x10
};
struct RefOwner {
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
};
struct HT {
    char       pad0[4];
    HashNode** buckets;   // +0x04
    int        nbuckets;  // +0x08
    char       pad1[4];
    void  find(HashIter* out, void* key);        // 0x00a3b2c0
    void  insert(HashIter* out, const HashValue* v, int flag);  // 0x00e2ff50
    void* find_or_add(void* key);                // 0x00e30b60
};
struct MgrA {
    void** vt0;      // +0x00
    void** vt1;      // +0x04
    char   pad0[0x1c - 0x08];
    void** vt2;      // +0x1c
    char   pad1[0x24 - 0x20];
    char   sub24[0x2c]; // +0x24 .. +0x50
    void*  p50;         // +0x50
    MgrA* scalar_dtor(int flag);
};
struct AutoRefCount {
    void* mp;                                      // +0x00
    AutoRefCount& assign(void* p);                 // 0x00b5f950
};
struct FrameValue {
    uint32_t     mDelay;                           // +0x00  milliseconds the frame stays up
    AutoRefCount mText;                            // +0x04  IWinText reference
    uint8_t      mFlag08;                          // +0x08
    char         _pad09[3];
    void*        mProp;                            // +0x0c  filled by 0x00ac9480
    uint32_t     mPad10;                           // +0x10
};
struct FrameProp {
    void AddRef();                                 // +0x00
    void Release();                                // +0x04
};
struct PropertyManager {
    char pad0[0x2c];
    bool get(int key, const wchar_t* name, void** out);   // +0x2c
};
struct MgrCard {
    char   pad0[0x10];
    Vec1c  vec;                         // +0x10  element vector (see 0x00e30c00)
    char   pad1[0x24 - 0x1c];
    HT     ht;                          // +0x24  frame hash table
    char   pad2[0x44 - 0x34];
    void Add(void** out, int p);
    void AddOrUpdate(int a, void* p, unsigned c, uint8_t flag, int e);
    void Wrapper(int a, int b, int c, int d);
    void Destroy();
    void applyFrame(FrameValue* fv);   // 0x00e2fcb0
};
struct Card {
    void** vt0;    // +0x00
    int    rc;     // +0x04
    void*  p08;
    void*  p0c;
    void*  p10;
    void*  p14;
    void*  p18;
};
struct CardView {
    void** vt0;      // +0x00
    void** vt1;      // +0x04
    void*  p08;      // +0x08
    void*  p0c;      // +0x0c
    void*  vecBegin; // +0x10
    void*  vecEnd;   // +0x14
    void*  vecCap;   // +0x18
    void*  p1c;      // +0x1c
    void*  buf20;    // +0x20
    char   pad[0x68 - 0x24];
    float  f68;      // +0x68
    char   pad2[0x7c - 0x6c];
    uint8_t b7c;     // +0x7c
    char   pad3[0x80 - 0x7d];
    void*  a80;      // +0x80
    void*  a84;      // +0x84
    void*  a88;      // +0x88
    void*  a8c;      // +0x8c
    void*  a90;      // +0x90
    void*  a94;      // +0x94
    void*  a98;      // +0x98
    void*  a9c;      // +0x9c
    void*  aa0;      // +0xa0
    void*  aa4;      // +0xa4
    void dtor();
    void update(float dt);
    void hide();
    void show();
    void add(uint32_t a, uint32_t b);
};
// ---- items of slice s00e30790 end

// ---- items of slice s00e31670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double fabs(double);
struct cSPUIWindow;
struct cSPUIAnimator_s00e3_1670;
struct RainbowInstance {
    void*   mpBegin;        // +0x00  round-entry array begin
    void*   mpEnd;          // +0x04  round-entry array end
    char    mPad08[0x90 - 0x08];
    float   mBase;          // +0x90
    float   mCurrent;       // +0x94
    float   mTarget;        // +0x98
    char    mFlag;          // +0x9c
    char    mActive;        // +0x9d
    char    mPad9e[0x06];   // +0x9e .. +0xa4
};
struct cSPUILayout_s00e3_1670 {
    char    mPad00[0x18];
    void*   FindWindowByID(unsigned int id, int a);      // 0x008105b0
};
struct cSPUIAnimator_s00e3_1670 {
    char    mPad00[0x20];
    bool    HasAnimation(void* anim, unsigned int id);    // 0x007f62c0
};
struct cSPUIWindow {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetMode(int n);      // +0x14
};
struct cSPUISocialRainbow {
    char            mPad00[0x0c];    // +0x00
    cSPUILayout_s00e3_1670     mLayout;         // +0x0c
    char            mFlag24;         // +0x24
    char            mPad25[0x3c - 0x25];
    float           mF3c;            // +0x3c
    float           mF40;            // +0x40
    char            mPad44[0x48 - 0x44];
    cSPUIAnimator_s00e3_1670   mAnimator;       // +0x48
    void*           mpAnimRef;       // +0x68
    char            mPad6c[0xa4 - 0x6c];
    RainbowInstance mInstances[2];   // +0xa4 (rows 0 and 1)
    char            mPad1ec[0x1f8 - 0x1ec];
    cSPUIWindow*    mpF1f8;          // +0x1f8
    void*           mpF1fc;          // +0x1fc

    void  F0e31670(void);                                   // 0x00e31670
    void  SetCurrent(int i, float t);                       // 0x00e319d0
    double Ratio(int i);                                    // 0x00e31a30
    bool  HasAnim(int i, char flag);                        // 0x00e31aa0
    void  GetRoundBounds(int a, int b, float* o1, float* o2); // 0x00e31bb0
    void  Mode(int p);                                      // 0x00e31cb0
    void  F0e31d60(void);                                   // 0x00e31d60
    void  Fwd(void);                                        // 0x00e31c90
    __declspec(noinline) void Helper160(int i);             // 0x00e32160
    __declspec(noinline) void Helper250(int i, int x, int y);// 0x00e32250
    void  StartDrain(int i, float t, float v);              // 0x00e32460
    void  Stop(int i);                                      // 0x00e324f0
};
struct Variant {
    void*   mpData;         // +0x00
    char    mPad04[0x10 - 0x04];
    unsigned int mFlags;    // +0x10 (bit 0x30 => by-ref/pointer)
    unsigned short mType;   // +0x12
    char    mPad14[0x04];

    void SetFloat(const float& v);          // 0x00428060
};
void  F0e31d60(cSPUISocialRainbow* self);   // 0x00e31d60
// ---- items of slice s00e31670 end

// ---- items of slice s00e33270 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char gColourCfgName[];      // 0x013f6b3c
extern const wchar_t gMissingText[];     // 0x013ffd4c L"<Missing>"
struct IUnknown32_s00e3_3270 {
    virtual int AddRef();                    // +0x00
    virtual int Release();                   // +0x04
    virtual void v08();                      // +0x08
};
class RefCountVTemplate_s00e3_3270 {
 public:
    virtual ~RefCountVTemplate_s00e3_3270();            // +0x00 scalar deleting destructor

    int AddRef() { return ++mRefCount; }
    int Release()
    {
        // The count update has to be spelled out (rather than "--mRefCount") so that it is
        // materialised in a register: the retail call sites reload the count, decrement it and
        // store it back before testing it.
        int nCount = mRefCount - 1;
        mRefCount = nCount;
        if (nCount == 0) {
            mRefCount = 1;
            delete this;
        }
        return nCount;
    }

    int mRefCount;                           // +0x04
};
struct IWindow_s00e3_3270;
struct IWinProc_s00e3_3270 : public IUnknown32_s00e3_3270 {
    virtual bool DoMessage(IWindow_s00e3_3270* pWindow, void* pMessage);    // +0x0c
};
struct IViewEffect : public IUnknown32_s00e3_3270 {
    virtual void Stop(bool bImmediate);      // +0x0c
    virtual void v10();                      // +0x10
};
struct IWindow_s00e3_3270 : public IUnknown32_s00e3_3270 {
    virtual void* Cast(uint type);           // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
    virtual uint GetControlID();             // +0x1c
virtual void v20();
virtual void v24();
    virtual bool IsVisible();                // +0x28
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
    virtual void SetFlag(int flag, bool value);            // +0x7c
    virtual void SetCaption(const wchar_t* text);          // +0x80
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual void Refresh();                                // +0x90
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
virtual void ve8();
virtual void vec();
virtual void vf0();
virtual void vf4();
virtual void vf8();
virtual void vfc();
virtual void v100();
    virtual void SetLayoutArea(void* area);                // +0x104
    virtual void SetWinProc(IWinProc_s00e3_3270* proc);               // +0x108
};
struct IPropertyList {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void v2c();
    virtual void SetProperty(uint id, void* value);          // +0x30
};
class cSPUILayout_s00e3_3270 : public RefCountVTemplate_s00e3_3270 {
 public:
    virtual int AddRef();                                        // vtable slot 4
    virtual int Release();                                       // vtable slot 8
    void SetReloadCallback(void (__cdecl*)(void*, cSPUILayout_s00e3_3270*, bool), void*);  // 0x00810090
    IWindow_s00e3_3270* FindWindowByID(uint id, bool recursive) const;      // 0x008105b0
    void Shutdown(uint destroy);                                 // 0x00811ad0

    unsigned char mResourceKey[12];                              // +0x08
    void** mpObjectCollection;                                   // +0x14
};
class IViewNameProvider {
 public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual const wchar_t* GetTitle();        // +0x0c
    virtual const wchar_t* GetDescription();  // +0x10

    uint mPad04[3];                           // +0x04
    IUnknown32_s00e3_3270 mRefCount;                     // +0x10

    void Release() { mRefCount.Release(); }
};
template <class T>
class AutoRefCount_s00e3_3270 {
 public:
    AutoRefCount_s00e3_3270() : mpObject(0) {}

    AutoRefCount_s00e3_3270& operator=(T* pObject)
    {
        if (mpObject != pObject) {
            if (pObject)
                pObject->AddRef();
            T* pOld = mpObject;
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }

    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* Get() const { return mpObject; }
    T** AsPPTypeParam() { return &mpObject; }

    T* mpObject;
};
class ColourCfg : public RefCountVTemplate_s00e3_3270 {
 public:
    ColourCfg();                                         // 0x0066bd40
    void ApplyLayout(cSPUILayout_s00e3_3270* pLayout);              // 0x0066bd80
    void ResetColour();                                  // 0x0066bf20
};
namespace SP {
IPropertyList* __cdecl PropertyManager();                // 0x0067de30
}
namespace EA {
namespace ResourceMan {
class Key_s00e3_3270 {
 public:
    Key_s00e3_3270() : mInstanceID(0), mTypeID(0) {}
    uint mInstanceID;   // +0x00
    uint mTypeID;       // +0x04
};
}
}
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }
inline void  operator delete(void*, void*) throw() {}
extern "C" void       __cdecl SetWindowAreaToParent(IWindow_s00e3_3270* pWindow);                     // 0x00806bf0
struct PA_Agg : public IUnknown32_s00e3_3270 {
};
struct cContentValidationSummarizer : public IUnknown32_s00e3_3270 {
};
class cUISporepediaPlanetLargeAssetView : public IWinProc_s00e3_3270,
                                          public PA_Agg,
                                          public cContentValidationSummarizer {
 public:
    cUISporepediaPlanetLargeAssetView();          // 0x00e33de0
    ~cUISporepediaPlanetLargeAssetView();         // 0x00e33e70

    void Destroy();                               // 0x00e33f30
    void ReleaseWindows();                        // 0x00e33f90
    void LoadLayout();                            // 0x00e34020

    void* mpUnused0c;                             // +0x0c
    AutoRefCount_s00e3_3270<cSPUILayout_s00e3_3270> mpLayout;           // +0x10
    AutoRefCount_s00e3_3270<IWindow_s00e3_3270> mpIconWindow;           // +0x14
    AutoRefCount_s00e3_3270<IWindow_s00e3_3270> mpIcon2Window;          // +0x18
    AutoRefCount_s00e3_3270<IWindow_s00e3_3270> mpTitleWindow;          // +0x1c
    AutoRefCount_s00e3_3270<IWindow_s00e3_3270> mpDescriptionWindow;    // +0x20
    AutoRefCount_s00e3_3270<IWindow_s00e3_3270> mpValueWindow;          // +0x24
    AutoRefCount_s00e3_3270<ColourCfg> mpColourCfg;          // +0x28
    AutoRefCount_s00e3_3270<IViewNameProvider> mpNameProvider;   // +0x2c
    AutoRefCount_s00e3_3270<IUnknown32_s00e3_3270> mpMessageListener;       // +0x30
    IViewEffect* mpEffects[5];                    // +0x34 .. +0x44 (not released by the dtor)
    bool mbVisible;                               // +0x48
    bool mbInitialized;                           // +0x49
    bool mbPending;                               // +0x4a
};
class cViewModel {
 public:
    void Unload();                               // 0x005f0a60
};
cViewModel* __stdcall CastToViewModel(void* pModel);        // 0x00401020
struct IHandler_s00e3_3270 : public IUnknown32_s00e3_3270 {
};
class cSPSwatch_s00e3_3270 : public IWinProc_s00e3_3270, public RefCountVTemplate_s00e3_3270, public IHandler_s00e3_3270 {
 public:
    cSPSwatch_s00e3_3270();                                             // 0x005f6bd0
    void AddModelKey(EA::ResourceMan::Key_s00e3_3270 const& key);       // 0x005f58f0
    void Shutdown();                                         // 0x005f68a0

    unsigned char mPad10[0x140 - 0x10];                      // +0x10 .. +0x13f
};
class cSPUISwatchView : public cSPSwatch_s00e3_3270 {
 public:
    cSPUISwatchView();                                       // 0x00e34220
    void AddConfiguredModelKey();                            // 0x00e33d60
    void ShutdownView();                                     // 0x00e33d70

    unsigned char mPad140[0x17c - 0x140];                    // +0x140 .. +0x17b
    EA::ResourceMan::Key_s00e3_3270 mConfiguredModelKey;                // +0x17c
    void* mpUnused184;                                       // +0x184
    void* mpUnused188;                                       // +0x188
    AutoRefCount_s00e3_3270<IViewEffect> mpEffectA;                     // +0x18c
    AutoRefCount_s00e3_3270<IViewEffect> mpEffectB;                     // +0x190
};
// ---- items of slice s00e33270 end

// ---- items of slice s00e34290 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCounted_s00e3_4290 {
    virtual void     v00();                                 // +0x00
    virtual uint32_t Release();                             // +0x04
    virtual uint32_t v08();                                 // +0x08
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();                                  // +0x18
    virtual void     v1c();
    virtual void     v20();                                  // +0x20
    virtual void     v24();                                  // +0x24
};
struct RefBlock;
struct RefBlockVtbl {
    void   (*pAddRef)(RefBlock*);                           // +0x00
    void   (*pRelease)(RefBlock*);                          // +0x04
    void*  mpUnused08[0x5a];                                // +0x08 .. +0x16c
    void (__stdcall *pDestroy)(RefBlock*, bool bDelete);    // +0x170
};
struct RefBlock {
    RefBlockVtbl* mpVtbl;                                   // +0x00
    int32_t       mFlags;                                   // +0x04
    char          mPad08[0x38];                             // +0x08 .. +0x3f
    int32_t       mRefCount;                                // +0x40
};
struct IWindow_s00e3_4290 {
    virtual void     v00();                                 // +0x00
    virtual void     v04();                                 // +0x04
    virtual void     v08();                                 // +0x08
    virtual IWindow_s00e3_4290* v0c(uint32_t id);                      // +0x0c
    virtual void     v10();                                 // +0x10
    virtual void     v14();                                 // +0x14
    virtual void     v18();                                 // +0x18
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24(uint32_t a, uint32_t b);           // +0x24
    virtual void     v28();
    virtual void     v2c();
    virtual void     v30();
    virtual void     v34();
    virtual void     v38();
    virtual void     v3c();
    virtual void     v40();
    virtual void     v44();
    virtual void     v48();
    virtual void     v4c();
    virtual void     v50();
    virtual void     v54();
    virtual void     v58();
    virtual void     v5c();
    virtual void     v60();
    virtual void     v64();
    virtual void     v68();
    virtual void     v6c();
    virtual void     v70();
    virtual void     v74();
    virtual void     v78();
    virtual void     v7c();
    virtual void     v80();
    virtual void     v84();
    virtual void     v88();
    virtual void     v8c();
    virtual void     v90();
};
struct cSPUIRolloverCivRelationship {
    void ShowRelationshipRollover(int32_t a, int32_t b, int32_t c);   // 0x00e2d6a0
};
struct EAKey {
    uint32_t m0;
    uint32_t m4;
    uint32_t m8;

    EAKey() : m0(0), m4(0), m8(0) {}
    EAKey(uint32_t a, uint32_t b, uint32_t c) : m0(a), m4(b), m8(c) {}
};
struct cSPUILayout_s00e3_4290 {
    virtual void v00();                                               // +0x00
    virtual void v04();
    virtual void v08();

    cSPUILayout_s00e3_4290* ctor();                                              // 0x00810000
    bool Init(const EAKey& key, bool flag, uint32_t group);           // 0x008120d0
    bool SetParentWin(IWindow_s00e3_4290* pParent, bool flag, uint32_t group);   // 0x008121b0
    void SetReloadCallback(void (*pCallback)(void*, cSPUILayout_s00e3_4290*), void* pContext);  // 0x00810090
};
void* operator new(uint32_t cb, void* pAllocator, int32_t a, int32_t b, int32_t c, int32_t d);  // 0x00f473a0
struct cToolButton {
    char     mPad00[0x1a];
    bool     mbActive;                                      // +0x1a
    uint32_t mToolId;                                       // +0x1c
    char     mPad20[1];
    bool     mbEnabled;                                     // +0x21

    bool SetTool(uint32_t toolId, uint32_t data);           // 0x00e34eb0
    void SetEnabled(bool enabled);                          // 0x00e34ea0
};
struct cNounTag;
struct ViewRecord {                                         // at cAssetView+0x34
    uint32_t m00;
    uint32_t m04;
    uint32_t m08;
};
struct cNounTag {
    bool IsValid();                                         // 0x00b7d4f0
};
struct cRefHolder {
    uint32_t Release();                                     // 0x0066bf70
};
struct cAssetView {
    char     mPad00[0x18];
    cSPUIRolloverCivRelationship* mpRollover;               // +0x18
    char     mPad1c[0x0c];
    cRefHolder* mpHolder;                                   // +0x28
    char     mPad2c[0x08];
    ViewRecord mRecord;                                     // +0x34
    char     mPad40[0x0a];
    bool     mbRecordValid;                                 // +0x4a

    void RefreshRecord(uint32_t flags);                     // 0x00e34da0
    void RefreshSwatch();                                   // 0x00e34af0
    void ShowRelationship(int32_t a, int32_t b, bool show);  // 0x00e35290
};
cNounTag* __stdcall ResolveNounTag(ViewRecord* pRecord);    // 0x00b3d360
struct ITracerBase {
    virtual ~ITracerBase();                                 // +0x00
    virtual void     v00();
    virtual void     v04();
};
struct CVSBase {
    virtual void     v00();                                 // +0x00 (this+0x04)
    virtual void     Update(int32_t delta);                 // 0x005f6f40
    uint32_t         mValue;                                // +0x04
};
struct PaintBase {
    virtual void     v00();                                 // +0x00 (this+0x0c)
    virtual void     v04();
    virtual void     v08();
    virtual void     v0c();
    virtual void     v10();
    virtual void     v14();
    virtual void     v18();
    virtual void     v1c();
    virtual void     v20();
    virtual void     v24();
};
struct cXform {
    void RotateZ(float angle);                              // 0x007d1ac0
    void Assign(const float* pMatrix);                      // 0x0041cb40
};
struct cSPSwatchModel {
    char mPad00[0x08];
    void PreRotateY(float angle);                           // 0x004099b0
};
struct cModelSource {
    void* GetModel(uint32_t* pKey);                         // 0x00e20f10
};
struct cSPSwatchView : ITracerBase, CVSBase, PaintBase {
    char         mPad10[0x108];                             // +0x10 .. +0x117
    void*        mpCreature;                                // +0x118
    char         mPad1c[0x60];                              // +0x11c .. +0x17b
    uint32_t     m17c;                                      // +0x17c (asset id triple)
    uint32_t     m180;                                      // +0x180
    uint32_t     m184;                                      // +0x184
    RefBlock*    mpSwatchRef;                               // +0x188
    IRefCounted_s00e3_4290* mpTarget;                                  // +0x18c
    IRefCounted_s00e3_4290* mpExtra;                                   // +0x190

    ~cSPSwatchView();                                       // 0x00e34290
    void Update(int32_t delta);                             // 0x00e34310
    void InitSwatch(const ViewRecord& key, const ViewRecord& outer,
                    uint32_t a, uint32_t b, uint32_t c);    // 0x00e34540
};
struct cAssetSwatchWidget {
    char              mPad00[0x10];
    cSPUILayout_s00e3_4290*      mpLayout;                             // +0x10
    IWindow_s00e3_4290*          mpParent;                             // +0x14
    char              mPad18[0x0c];
    void*             mpAsset;                              // +0x24
    char              mPad28[0x08];
    cSPSwatchView*    mpView;                               // +0x30
    ViewRecord*       mpRecordKey;                          // +0x34 -> record triple
    char              mPad38[0x08];
    uint32_t          m40;                                  // +0x40
    uint32_t          m44;                                  // +0x44

    void InitLayout();                                      // 0x00e34470
    void LoadLayout();                                      // 0x00e34020
    void CreateSwatch();                                    // 0x00e34af0
    bool HandleMessage();                                   // 0x00e34a00
    void HandleMessage2();                                  // 0x00e34bd0
};
void __fastcall LoadLayoutOfWidget(cAssetSwatchWidget* pThis);   // 0x00e34020
void ReloadAssetSwatch(void* pContext, cSPUILayout_s00e3_4290* pLayout);  // 0x00e34200
// ---- items of slice s00e34290 end

// ---- items of slice s00e36150 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t* gspUIElementBase;                // 0x01440aec
struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};
struct RectF {
    float x0;
    float y0;
    float x1;
    float y1;
};
struct cTooltipSlot {
    float m_fX;
    float m_fY;
    float m_fW;
};
class IBase {
public:
    virtual void* Slot00() = 0;
    virtual void* Slot04() = 0;
    virtual void* Slot08() = 0;
    virtual void* Slot0c() = 0;
    virtual void* Slot10() = 0;
    virtual void* Slot14() = 0;
    virtual void* Slot18() = 0;
    virtual void* Slot1c() = 0;
    virtual void* Slot20() = 0;
    virtual void* Slot24() = 0;
    virtual void* Slot28() = 0;
    virtual void* Slot2c() = 0;
    virtual void* Slot30() = 0;
    virtual void* Slot34() = 0;
    virtual void* Slot38() = 0;
    virtual void* Slot3c() = 0;
    virtual void* Slot40() = 0;
    virtual void* Slot44() = 0;
    virtual void* Slot48() = 0;
    virtual void* Slot4c() = 0;
    virtual void* Slot50() = 0;
    virtual void* Slot54() = 0;
    virtual void* Slot58() = 0;
    virtual void* Slot5c() = 0;
    virtual ~IBase() {}
};
namespace EA {
class Stopwatch_s00e3_6150 {
public:
    Stopwatch_s00e3_6150() {}
    Stopwatch_s00e3_6150(int32_t nSource, bool bStart);     // 0x0093a560
    void Restart();                              // 0x00571e80
    int64_t GetElapsedTime();                    // 0x0093a5e0
    int64_t GetElapsedTimeFloat();               // 0x0093a3a0
    void SetBoolProperty();                      // 0x0093a2e0

    int64_t m_nStart;                            // +0x00
    int64_t m_nStop;                             // +0x08
    int32_t m_nSource;                           // +0x10
    float m_fRate;                               // +0x14
};
}
class cSPUILayout_s00e3_6150 {
public:
    virtual void AddRef0();                      // +0x00
    virtual void Release1();                     // +0x04
    virtual void Release2();                     // +0x08
    void Shutdown(uint32_t nFlags);              // 0x00811ad0
    void SetVisibility(bool bVisible);           // 0x00810590
    bool IsVisible();                            // 0x00810070
    void* FindWindowByID(uint32_t nId, bool bFlag);            // 0x008105b0
    bool SetParentWin(void* pWin, bool bFlag, uint32_t nId);   // 0x008121b0
    bool Init(const void* pKey, bool bFlag, uint32_t nId);     // 0x008120d0
    void SetReloadCallback(void (__cdecl* pCallback)(void*, cSPUILayout_s00e3_6150*,
                                                     bool),
                           void* pUser);                       // 0x00810090
    void* GetWindow();                                         // 0x00810570
    cSPUILayout_s00e3_6150* InitDocument();                               // 0x00810000
};
class IWin {
public:
    virtual void AddRef0();                      // +0x00
    virtual void Release1();                     // +0x04
    virtual void SetVisible2(bool bVisible);     // +0x08
virtual void W0c();
virtual void W10();
virtual void W14();
virtual void W18();
virtual void W1c();
virtual void W20();
virtual void W24();
virtual void W28();
virtual void W2c();
virtual void W30();
virtual void W34();
virtual void W38();
virtual void W3c();
virtual void W40();
virtual void W44();
virtual void W48();
virtual void W4c();
virtual void W50();
virtual void W54();
virtual void W58();
virtual void W5c();
virtual void W60();
virtual void W64();
virtual void W68();
    virtual void SetRect6c(RectF* pRect);        // +0x6c
virtual void W70();
virtual void W74();
virtual void W78();
    virtual void SetFlags7c(bool bFlag, bool bOther);          // +0x7c
virtual void W80();
virtual void W84();
virtual void W88();
virtual void W8c();
virtual void W90();
virtual void W94();
virtual void W98();
virtual void W9c();
virtual void Wa0();
virtual void Wa4();
virtual void Wa8();
virtual void Wac();
virtual void Wb0();
virtual void Wb4();
virtual void Wb8();
virtual void Wbc();
virtual void Wc0();
virtual void Wc4();
virtual void Wc8();
virtual void Wcc();
virtual void Wd0();
virtual void Wd4();
    virtual void SetParentd8(IWin* pParent);     // +0xd8
};
class cSPUIAnimator_s00e3_6150 : public IBase {
public:
    bool Empty();                                // 0x007f6340
};
class IWinNode : public IBase {
public:
    virtual void* S00() = 0;  virtual void* S04() = 0;  virtual void* S08() = 0;
    virtual void* S0c() = 0;  virtual void* S10() = 0;  virtual void* S14() = 0;
    virtual void* S18() = 0;  virtual void* S1c() = 0;  virtual void* S20() = 0;
    virtual void* S24() = 0;
    virtual uint32_t S28() = 0;
    virtual void* S2c() = 0;  virtual void* S30() = 0;  virtual void* S34() = 0;
    virtual RectF* S38() = 0;
    virtual void* S3c() = 0;  virtual void* S40() = 0;  virtual void* S44() = 0;
    virtual void* S48() = 0;  virtual void* S4c() = 0;  virtual void* S50() = 0;
    virtual void* S54() = 0;  virtual void* S58() = 0;  virtual void* S5c() = 0;
    virtual void* S60() = 0;  virtual void* S64() = 0;  virtual void* S68() = 0;
    virtual void* S6c() = 0;
    virtual void S70(float fX, float fY) = 0;
    virtual void S74(float fWidth, float fHeight) = 0;
    virtual void* S78() = 0;  virtual void* S7c() = 0;  virtual void* S80() = 0;
    virtual void* S84() = 0;  virtual void* S88() = 0;  virtual void* S8c() = 0;
    virtual void* S90() = 0;  virtual void* S94() = 0;  virtual void* S98() = 0;
    virtual void* S9c() = 0;  virtual void* SA0() = 0;  virtual void* SA4() = 0;
    virtual void* SA8() = 0;  virtual void* SAc() = 0;  virtual void* SB0() = 0;
    virtual void* SB4() = 0;  virtual void* SB8() = 0;  virtual void* SBc() = 0;
    virtual void* SC0() = 0;  virtual void* SC4() = 0;  virtual void* SC8() = 0;
    virtual void Scc(uint32_t** ppIter) = 0;
    virtual void Sd0(uint32_t** ppEnd) = 0;
};
class cWindowManager {
public:
    virtual void M00();
    virtual void* GetView();                     // +0x04
    virtual void SetWindow(IWin* pWindow, bool bFlag);            // +0x08
    virtual void SetViewport(float fWidth, float fHeight);        // +0x0c
virtual void M10();
virtual void M14();
virtual void M18();
virtual void M1c();
    virtual void M20();
    virtual void Reset24();                      // +0x24
};
class IView {
public:
    virtual void AddRef0();                      // +0x00
    virtual void Release1();                     // +0x04
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
virtual void V2c();
virtual void V30();
    virtual Vector4* GetBounds();                // +0x34
};
class cViewer {
public:
    cViewer* Construct();                        // 0x007c3f70
    bool Init(bool bFlag);                       // 0x007c4dd0
    void SetRaster(void* pRaster, bool bFlag);   // 0x007c4be0
    void Shutdown();                             // 0x007c4000
};
class cBoundingBox {
public:
    virtual void* S00();
    virtual void* S04();
    virtual void* S08();
    virtual void AddPoints(uint32_t a1, uint32_t a2, const Vector4* pPoints,
                           uint32_t a3);         // +0x0c
};
void* __cdecl SP_WindowManager();                // 0x0067caa0
void* __cdecl cSPBoundingBox_AddBoundingBox();   // 0x0067cad0
void __cdecl FUN_00808b20(IWin* pTarget, IWin* pSource, char cArg);   // 0x00808b20
void* __cdecl FUN_009512c0();                    // 0x009512c0
void* __stdcall FUN_009512d0(uint32_t nSize, uint32_t nAlign,
                             const char* pType, void* pAlloc);         // 0x009512d0
void* __stdcall FUN_00962a10(void* pWindow);     // 0x00962a10
void* __stdcall operator_new(uint32_t nSize, const void* pFile,
                             uint32_t a, uint32_t b, uint32_t c,
                             uint32_t d);        // 0x00f473a0
void __stdcall operator_delete_array(void* pObject);           // 0x00f47380
Vector4* __cdecl AccumulateBounds(Vector4* pOut, IWinNode* pNode, bool bDeep,
                                  bool bFilter);  // 0x00e36670
class cSPUITooltipPanel : public IBase {
public:
    cSPUITooltipPanel(float fSize, cSPUILayout_s00e3_6150* pLayout, void* pRaster,
                      void* pOwner);                            // 0x00e36150
    ~cSPUITooltipPanel();                                       // 0x00e36260
    void Render(uint32_t a1, uint32_t a2, uint32_t a3,
                uint32_t a4);                                   // 0x00e362f0

    uint32_t m_nKey08;                           // +0x008
    IWin* m_pWindow0c;                           // +0x00c
    cSPUILayout_s00e3_6150* m_pLayout10;                    // +0x010
    void* m_pRaster14;                           // +0x014
    void* m_pOwner18;                            // +0x018
    IWin* m_pTargetWin1c;                        // +0x01c
    RectF m_rect20;                              // +0x020
};
class cUITimedTooltip : public IBase {
public:
    cUITimedTooltip();                                          // 0x00e36480
    ~cUITimedTooltip();                                         // 0x00e364d0
    void Shutdown();                                            // 0x00e36500
    void UpdateTimeoutA();                                      // 0x00e36540
    void UpdateTimeoutB(IWin* pWindow);                         // 0x00e365a0
    void Hide();                                                // 0x00e36620
    void* FindWindow(uint32_t nId, bool bFlag);                 // 0x00e36650
    void* DestroyDeleting(bool bDelete);                        // 0x00e36890
    void UpdateLayout();                                        // 0x00e369f0
    bool Init(const uint32_t& nKey, uint32_t nId, uint32_t nWidth,
              uint32_t nHeight, uint32_t a5, uint32_t a6);      // 0x00e36b30
    void ResetState();                                          // 0x00e36de0
    bool UpdateA();                                             // 0x00e36cd0
    bool UpdateB();                                             // 0x00e36d30
    bool UpdateC();                                             // 0x00e36d80
    bool UpdateD();                                             // 0x00e36e20
    bool UpdateE();                                             // 0x00e36e80
    cTooltipSlot* GetSlot(int32_t nIndex);                      // 0x00e36fb0

    uint32_t m_nPad04;                           // +0x004
    uint32_t m_nKey08;                           // +0x008
    cSPUILayout_s00e3_6150* m_pLayout;                      // +0x00c
    IWin* m_pWindow;                             // +0x010
    uint8_t mPad14[0x4];                         // +0x014
    EA::Stopwatch_s00e3_6150 m_swA;                         // +0x018
    EA::Stopwatch_s00e3_6150 m_swB;                         // +0x030
    uint32_t m_nTimeoutA;                        // +0x048
    uint32_t m_nTimeoutB;                        // +0x04c
    float m_f50;                                 // +0x050
    float m_f54;                                 // +0x054
    float m_f58;                                 // +0x058
    float m_f5c;                                 // +0x05c
    uint8_t mPad60[0x390];                       // +0x060
    uint32_t m_nMode3f0;                         // +0x3f0
    uint8_t mPad3f4[0x4];                        // +0x3f4
    EA::Stopwatch_s00e3_6150 m_sw3f8;                       // +0x3f8
    float m_fThreshold410;                       // +0x410
    uint8_t mPad414[0x4];                        // +0x414
    EA::Stopwatch_s00e3_6150 m_sw418;                       // +0x418
    float m_fThreshold430;                       // +0x430
    uint8_t mPad434[0x4];                        // +0x434
    EA::Stopwatch_s00e3_6150 m_sw438;                       // +0x438
    float m_fThreshold450;                       // +0x450
    bool m_bFlag454;                             // +0x454
    uint8_t mPad455[0x3];                        // +0x455
    cSPUIAnimator_s00e3_6150* m_pAnimator458;               // +0x458
    uint8_t mPad45c[0x4c];                       // +0x45c
    EA::Stopwatch_s00e3_6150 m_sw4a8;                       // +0x4a8
    float m_fThreshold4c0;                       // +0x4c0
    uint8_t mPad4c4[0x4];                        // +0x4c4
    EA::Stopwatch_s00e3_6150 m_sw4c8;                       // +0x4c8
    float m_fThreshold4e0;                       // +0x4e0
    uint8_t mPad4e4[0x9c];                       // +0x4e4
    cTooltipSlot m_slots[4];                     // +0x580
};
// ---- items of slice s00e36150 end

// ---- items of slice s00e39ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Variant_s00e3_9ab0 {
    union {
        uint32_t  mData[4];
        uint32_t* mpData;      // payload when mFlags holds kFlagByReference (0x30)
    };
    uint16_t mFlags;           // +0x10
    uint16_t mTypeId;          // +0x12
};
class IPropertyList_s00e3_9ab0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual bool GetProperty(uint32_t id, Variant_s00e3_9ab0** ppValue);   // +0x24
};
float* GetDefaultColor();              // 0x006bb610
struct ColorPropertyBinding {
    void*    mpVtbl;           // +0x00
    uint32_t mPropertyId;      // +0x04
    uint32_t mField08;         // +0x08
    float    mValue[4];        // +0x0c
    bool SetValue(IPropertyList_s00e3_9ab0* pList);
};
// ---- items of slice s00e39ab0 end

// @ 0x00e30010
void cSPUIAssetDiscoveryManager::PushCard(cSPUIAssetDiscoveryCard** ppCard, int nFlags)
{
    cSPUIAssetDiscoveryCard* pCard = (cSPUIAssetDiscoveryCard*)*ppCard;
    if (pCard != nullptr)
        pCard->AddRef();

    if (mpCardsEnd - mpCardsCur <= 1)
        PushCardInternal();

    uint32_t pBlock = (uint32_t)(intptr_t)operator_new(0x100, "Simulator", 0, 0,
                                                       "EASTL/allocator.h", 0xd1);
    *(uint32_t*)(mpCardsCap + 1) = pBlock;
    if (mpCardsCur != nullptr) {
        *mpCardsCur = pCard;
        if (pCard != nullptr)
            pCard->AddRef();
    }

    cSPUIAssetDiscoveryCard** ppBlockStart = mpCardsCap;
    mpCardsCap = ppBlockStart + 1;
    mpCardsEnd = (cSPUIAssetDiscoveryCard**)(intptr_t)*(uint32_t*)(ppBlockStart + 1);
    mpCardsCur = mpCardsEnd;
    mpCardsBegin = mpCardsCur;

    if (pCard != nullptr)
        pCard->Release();
    (void)nFlags;
}

// @ 0x00e300f0
void cSPUIAssetDiscoveryManager::Shutdown()
{
    cMessageServer* pServer = (cMessageServer*)MessageServer();
    pServer->v2c((cMessageTarget*)this, 0xf62defu, 0xffffd8f1);
    pServer = (cMessageServer*)MessageServer();
    pServer->v2c((cMessageTarget*)this, 0xd33b6aa2u, 0xffffd8f1);
    pServer = (cMessageServer*)MessageServer();
    pServer->v2c((cMessageTarget*)this, 0x533b6aa4u, 0xffffd8f1);

    if (mpSelectedCard != nullptr) {
        ((IRefCounted*)mpSelectedCard)->Release();
        ResetCardState();
        cSPUIAssetDiscoveryCard* pOldCard = mpSelectedCard;
        if (pOldCard != nullptr) {
            mpSelectedCard = nullptr;
            ((IRefCounted*)pOldCard)->Release();
        }
    }

    while (mpCardsBegin != mpCardsEnd) {
        ResetCardState();
        cSPUIAssetDiscoveryCard** ppCurrent = mpCardsBegin;
        if (ppCurrent + 1 == mpCardsEnd) {
            if (*ppCurrent != nullptr)
                (*ppCurrent)->Release();
            if (mpCardsCur != nullptr)
                operator_delete__(mpCardsCur);
            mpCardsCap = mpCardsEnd + 1;
            mpCardsEnd = (cSPUIAssetDiscoveryCard**)(intptr_t)*mpCardsCap;
            mpCardsCur = mpCardsEnd;
            mpCardsBegin = mpCardsCur;
        } else {
            mpCardsBegin = ppCurrent + 1;
            if (*ppCurrent != nullptr)
                (*ppCurrent)->Release();
        }
    }

    if (mpAnimator != nullptr) {
        mpAnimator->Update();
        mpAnimator = nullptr;
    }
}

// @ 0x00e30230
void cSPUIAssetDiscoveryManager::Update(uint nMilliseconds)
{
    if (mnPaused >= 1)
        return;

    mnElapsed += nMilliseconds;
    switch (mnAnimationState) {
    case 0:
        if (mpCardsBegin != mpCardsEnd) {
            cSPUIAssetDiscoveryCard* pCard = *mpCardsBegin;
            if (IsCardVisible(pCard)) {
                ResetDiscoveryAnimation();
                SetGlobalProperty(0xb6225e24u, 0x3f800000u);
                void* pTarget = GetCardTarget(mpSelectedCard);
                SetWindowScale(pTarget, 0);

                cSPUIAssetDiscoveryCard* pView = *(cSPUIAssetDiscoveryCard**)(mpSelectedCard + 1);
                if (pView != nullptr) {
                    Rect bounds;
                    bounds.mX = 0.0f;
                    bounds.mY = 0.0f;
                    bounds.mWidth = 0.0f;
                    bounds.mHeight = 0.0f;
                    uint32_t nMode = GetCurrentGameMode();
                    if (nMode == (uint32_t)(intptr_t)&gGameModeSpace)
                        GetTutorialArea(&bounds);
                    else if (nMode == (uint32_t)(intptr_t)&gGameModeTribe)
                        GetTribeArea(&bounds);

                    Rect* pArea = ((IWindow*)pView)->GetArea();
                    float fOffset = pArea->mWidth < bounds.mY ? 0.0f : bounds.mWidth - bounds.mX;
                    SetWindowPosition(pTarget, pArea->mX - fOffset, pArea->mY);
                }

                float fDuration = GetElapsedSeconds(mnSlideInStart, 1, pTarget, 0);
                void* pAnimation = nullptr;
                pAnimation = CreateScaleAnimation(nullptr, pTarget, mnScaleLow, fDuration);
                mpAnimator->AddAnimation(pAnimation, pTarget, 0);
                UpdateWindowState(pTarget);
                ((IRefCounted*)pTarget)->AddRef();
                ReleaseCurrentCard();
                mnElapsed = 0;
                mnAnimationState = 1;
            }
        }
        break;

    case 1:
        if (mnElapsed >= (uint64_t)mnStopHigh) {
            if (mnElapsed != (uint64_t)mnStopHigh || (uint64_t)mnStopLow < mnElapsed) {
                void* pTarget = GetCardTarget(mpSelectedCard);
                mpAnimator->RemoveAnimation(pTarget, -1);
                float fDuration = GetElapsedSeconds(mnSlideOutStart, 1, pTarget, 0);
                void* pAnimation = CreateScaleAnimation(nullptr, pTarget, 0x3f800000, fDuration);
                mpAnimator->AddAnimation(pAnimation, pTarget, 0);
                UpdateWindowState(pTarget);
                mnElapsed = 0;
                mnAnimationState = 2;
            }
        }
        break;

    case 2:
        if (mnElapsed >= (uint64_t)mnScaleHigh) {
            if (mnElapsed != (uint64_t)mnScaleHigh || (uint64_t)mnScaleLow < mnElapsed) {
                void* pTarget = GetCardTarget(mpSelectedCard);
                mpAnimator->RemoveAnimation(pTarget, -1);
                float fDuration = GetElapsedSeconds(mnRotateStart, 1, pTarget, 2);
                void* pAnimation = CreateRotationAnimation(nullptr, pTarget, 0, 0x3f800000, 0,
                                                           gRotationAngle, fDuration);
                mpAnimator->AddAnimation(pAnimation, pTarget, 2);
                UpdateWindowState(pTarget);
                mnElapsed = 0;
                mnAnimationState = 3;
            }
        }
        break;

    case 3:
        if (mnElapsed >= (uint64_t)mnRotateHigh) {
            if (mnElapsed != (uint64_t)mnRotateHigh || (uint64_t)mnRotateLow < mnElapsed) {
                mnElapsed = 0;
                mnAnimationState = 4;
            }
        }
        break;

    case 4:
        if (mnElapsed >= (uint64_t)mnZoomHigh) {
            if (mnElapsed != (uint64_t)mnZoomHigh || (uint64_t)mnZoomLow < mnElapsed) {
                void* pTarget = GetCardTarget(mpSelectedCard);
                mpAnimator->RemoveAnimation(pTarget, -1);
                Rect area;
                GetMainWindowArea(&area);
                float fDuration = GetElapsedSeconds(mnZoomStart, 1, pTarget, 0);
                void* pTimer = CreateTimerInterpolation(nullptr, fDuration);
                void* pAnimation = CreateScaleAnimationFloat(nullptr, pTarget, 0x3d4ccccd, pTimer);
                mpAnimator->AddAnimation(pAnimation, pTarget, 0);
                UpdateWindowState(pTarget);
                ResetAnimationState();
                mnElapsed = 0;
                mnAnimationState = 5;
            }
        }
        break;

    case 5:
        if (mnElapsed >= (uint64_t)mnFinalHigh) {
            if (mnElapsed != (uint64_t)mnFinalHigh || (uint64_t)mnFinalLow < mnElapsed) {
                mnElapsed = 0;
                void* pCard = mpSelectedCard;
                ((IRefCounted*)pCard)->Release();
                ResetCardState();
                cSPUIAssetDiscoveryCard* pOldCard = mpSelectedCard;
                if (pOldCard != nullptr) {
                    mpSelectedCard = nullptr;
                    ((IRefCounted*)pOldCard)->Release();
                }
                mnAnimationState = 0;
            }
        }
        break;
    }

    if (mpSelectedCard != nullptr) {
        cSPUIAssetDiscoveryCard* pCard = mpSelectedCard;
        if (pCard->mpTextWindow != nullptr)
            pCard->mpTextWindow->v2c();
        if (pCard->mpParentWin != nullptr)
            FlushCardAnimations();
    }
    mpAnimator->Update();
}

// @ 0x00e30680
void cSPUIAssetDiscoveryManager::Reset()
{
    if (mpSelectedCard != nullptr) {
        ((IRefCounted*)mpSelectedCard)->Release();
        ResetCardState();
        cSPUIAssetDiscoveryCard* pOldCard = mpSelectedCard;
        if (pOldCard != nullptr) {
            mpSelectedCard = nullptr;
            ((IRefCounted*)pOldCard)->Release();
        }
    }

    while (mpCardsBegin != mpCardsEnd) {
        ResetCardState();
        cSPUIAssetDiscoveryCard** ppCurrent = mpCardsBegin;
        if (ppCurrent + 1 == mpCardsEnd) {
            if (*ppCurrent != nullptr)
                (*ppCurrent)->Release();
            if (mpCardsCur != nullptr)
                operator_delete__(mpCardsCur);
            mpCardsCap = mpCardsEnd + 1;
            mpCardsEnd = (cSPUIAssetDiscoveryCard**)(intptr_t)*mpCardsCap;
            mpCardsCur = mpCardsEnd;
            mpCardsBegin = mpCardsCur;
        } else {
            mpCardsBegin = ppCurrent + 1;
            if (*ppCurrent != nullptr)
                (*ppCurrent)->Release();
        }
    }

    mnAnimationState = 0;
}

// @ 0x00e30790
void Vec1c::insert_(Elem1c* pos, const Elem1c* val)
{
    if (end != cap) {
        const Elem1c* v = val;
        if ((char*)v >= (char*)pos && (char*)v < (char*)end)
            v = v + 1;
        if (end) *end = end[-1];
        for (Elem1c* p = end - 1; p != pos; --p)
            p[0] = p[-1];
        *pos = *v;
        ++end;
        return;
    }
    Elem1c* oldBegin = begin;
    unsigned count = (unsigned)(end - begin);
    unsigned ncap = count ? count * 2 : 1;
    Elem1c* nb = 0;
    if (ncap)
        nb = (Elem1c*)operator_new(ncap * sizeof(Elem1c), "Simulator", 0, 0, 0x13ebb38, 0xd1);
    Elem1c* at = (Elem1c*)FUN_00847ff0(oldBegin, pos, nb);
    if (at != 0)
        *at = *val;                                  // slot for the new element
    Elem1c* ne = (Elem1c*)FUN_00847ff0(end, pos, nb + 1);
    if (begin && ((AllocHeader*)begin)[-1].mRefCount)
        operator_delete(begin);
    end = ne;
    begin = nb;
    cap = nb + ncap;
}

// @ 0x00e308d0
void NodeList::destroy(void** a, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        void* p = a[i];
        if (p) {
            do {
                void* o10 = *(void**)((char*)p + 0x10);
                void* next = *(void**)((char*)p + 0x14);
                if (o10) ((void(__thiscall*)(void*))(*(void***)o10)[1])(o10);
                void* o8 = *(void**)((char*)p + 0x8);
                if (o8) ((void(__thiscall*)(void*))(*(void***)o8)[1])(o8);
                operator_delete(p);
                p = next;
            } while (p);
        }
        a[i] = 0;
    }
}

// @ 0x00e30990
void MgrVec::update(int dt)
{
    if (vec.begin == vec.end) {
        counter = 0;
        return;
    }
    counter += dt;
    float t = (float)(unsigned)counter;
    float s = sinf(t * 0.01f);
    unsigned c = ((unsigned)(uint8_t)(int)((s + 1.0f) * 0.5f * 255.0f) << 24) | 0xffffffu;
    for (Elem1c* e = vec.begin; e != vec.end; ) {
        e->f10 += dt;
        uint32_t limit = e->f18 ? *(uint32_t*)e->f18 : 0x1388u;
        if (limit != 0xffffffffu && e->f10 >= limit) {
            ((TC*)this)->f_e2f480(e);
            e = vec.erasedAt(e);
        } else {
            ((TC*)this)->f_e2f3f0(e, c);
            e += 1;
        }
    }
}

// @ 0x00e30a60
void VecHolder::remove_head(uint32_t key)
{
    if (begin == end) return;
    Elem1c* cur = begin;
    while (cur != end) {
        if (cur->f0 == key || cur->f8 == key) {
            ((TC*)this)->f_e2f480(cur);
            for (Elem1c* q = cur; q + 1 != end; ++q)
                q[0] = q[1];
            end = (Elem1c*)((char*)end - 0x1c);
        } else {
            cur += 1;
        }
    }
}

// @ 0x00e30ae0
void VecHolder::remove_off8(uint32_t key)
{
    if (begin == end) return;
    Elem1c* cur = begin;
    while (cur != end) {
        if (cur->f8 == key) {
            ((TC*)this)->f_e2f480(cur);
            for (Elem1c* q = cur; q + 1 != end; ++q)
                q[0] = q[1];
            end = (Elem1c*)((char*)end - 0x1c);
        } else {
            cur += 1;
        }
    }
}

// @ 0x00e30b60
void* HT::find_or_add(void* key)
{
    HashIter it;
    find(&it, key);
    if (it.mpNode != buckets[nbuckets])
        return &it.mpNode->mKey;
    HashValue val;
    val.mKey = *(const uint32_t*)key;
    val.mpName = it.mpNode;
    val.mPad08 = 0;
    val.mpOwner0 = 0;
    val.mpOwner1 = 0;
    insert(&it, &val, 0);
    if (val.mpOwner1)
        ((RefOwner*)val.mpOwner1)->Release();
    if (val.mpOwner0)
        ((RefOwner*)val.mpOwner0)->Release();
    return &it.mpNode->mKey;
}

// @ 0x00e30c00
void Vec1c::push_back_default()
{
    Elem1c* p = end;
    if (p < cap) {
        end = p + 1;
        if (p) {
            uint32_t* t = (uint32_t*)p;
            t[0] = 0; t[1] = 0; t[2] = 0; t[3] = 0; t[4] = 0; t[5] = 0; t[6] = 0;
        }
        return;
    }
    Elem1c tmp;
    uint32_t* t = (uint32_t*)&tmp;
    t[0] = 0; t[1] = 0; t[2] = 0; t[3] = 0; t[4] = 0; t[5] = 0; t[6] = 0;
    insert_(end, &tmp);
}

// @ 0x00e30c60
MgrA* __fastcall MgrA_ctor(MgrA* self)
{
    ((TC*)self)->f_b5b960();
    *(void* volatile*)((char*)self + 0x1c) = &g_vt_paint;
    char* ecx = (char*)self + 0x24;
    uint32_t z = 0;
    *(void* volatile*)((char*)self + 0) = &g_vt_gon0;
    *(void* volatile*)((char*)self + 4) = &g_vt_gon1;
    *(void* volatile*)((char*)self + 0x1c) = &g_vt_gon2;
    *(uint32_t*)(ecx + 0x00) = z;
    *(uint32_t*)(ecx + 0x04) = z;
    *(uint32_t*)(ecx + 0x08) = z;
    *(uint32_t*)(ecx + 0x0c) = z;
    *(uint32_t*)(ecx + 0x10) = z;
    *(uint32_t*)(ecx + 0x14) = z;
    *(uint32_t*)(ecx + 0x18) = z;
    *(uint32_t*)(ecx + 0x1c) = z;
    *(uint32_t*)(ecx + 0x20) = z;
    *(uint32_t*)(ecx + 0x24) = z;
    ((TC*)ecx)->f_ca09f0(0);
    *(uint32_t*)((char*)self + 0x50) = z;
    *(uint32_t*)((char*)self + 0x54) = z;
    *(uint32_t*)((char*)self + 0x58) = z;
    *(uint32_t*)((char*)self + 0x5c) = z;
    *(uint32_t*)((char*)self + 0x60) = z;
    *(uint32_t*)((char*)self + 0x64) = z;
    *(uint32_t*)((char*)self + 0x78) = z;
    *(uint32_t*)((char*)self + 0x7c) = z;
    *(uint32_t*)((char*)self + 0x80) = z;
    *(uint32_t*)((char*)self + 0x84) = z;
    *(uint32_t*)((char*)self + 0x88) = z;
    *(uint32_t*)((char*)self + 0x8c) = z;
    *(uint32_t*)((char*)self + 0x90) = z;
    *(uint32_t*)((char*)self + 0x94) = z;
    *(uint32_t*)((char*)self + 0x98) = z;
    *(uint32_t*)((char*)self + 0x9c) = z;
    *(float volatile*)((char*)self + 0x68) = 0.0f;
    *(float volatile*)((char*)self + 0x6c) = 0.0f;
    *(float volatile*)((char*)self + 0x70) = 0.0f;
    *(float volatile*)((char*)self + 0x74) = 0.0f;
    *(float volatile*)((char*)self + 0xa0) = 0.0f;
    return self;
}

// @ 0x00e30d20
void MgrCard::Add(void** out, int p)
{
    Card* c = (Card*)operator_new(0x1c, "UI/AssetDiscoveryCard", 0, 0, 0, 0);
    if (c) {
        c->rc = 0;
        ((void***)c)[1] = &g_vt_card0;
        c->p08 = 0; c->p0c = 0; c->p10 = 0; c->p14 = 0; c->p18 = 0;
    } else {
        c = 0;
    }
    if (c) ((void(__thiscall*)(void*))(*(void***)c)[1])(c);
    ((TC*)c)->f_e2f6e0(p);
    void** e = *(void***)((char*)this + 0x3c);
    void* n = (char*)e + 4;
    if (n == *(void**)((char*)this + 0x44)) {
        ((TC*)((char*)this + 0x24))->f_e30010(&c);
    } else {
        *(void**)((char*)this + 0x3c) = n;
        if (e) {
            *e = (void*)c;
            if (c) ((void(__thiscall*)(void*))(*(void***)c)[1])(c);
        }
    }
    if (c) ((void(__thiscall*)(void*))(*(void***)c)[2])(c);
}

// @ 0x00e30dc0
void MgrCard::Destroy()
{
    ((TC*)((char*)this + 0x10))->f_d73090(*(void**)((char*)this + 0x10), *(void**)((char*)this + 0x14));
    ((NodeList*)((char*)this + 0x24))->destroy(*(void***)((char*)this + 0x28), *(int*)((char*)this + 0x2c));
    *(uint32_t*)((char*)this + 0x30) = 0;
    int h = *(int*)((char*)this + 0x44);
    if (h) {
        *(uint32_t*)((char*)this + 0x44) = 0;
        EA_RemoveHandler(h, *(int*)((char*)this + 0x48), *(int*)((char*)this + 0x4c),
                        *(int*)((char*)this + 0x50), *(int*)((char*)this + 0x54));
    }
}

// @ 0x00e30e20
void MgrCard::AddOrUpdate(int a, void* p, unsigned c, uint8_t flag, int e)
{
    Elem1c* it = this->vec.begin;
    Elem1c* end = this->vec.end;
    while (it != end) {
        if (it->f0 == (uint32_t)a && it->f4 == (uint32_t)e)
            break;
        it += 1;
    }
    if (it != end) {
        it->f10 = 0;
        return;
    }
    Elem1c* found = 0;
    if (p) {
        Elem1c* r = (Elem1c*)FUN_00e2e8a0(this->vec.begin, this->vec.end, p, 0);
        if (r != this->vec.end)
            found = r;
    }
    this->vec.push_back_default();
    Elem1c* el = this->vec.end - 1;
    el->f0 = (uint32_t)a;
    el->f4 = (uint32_t)e;
    el->f8 = c;
    el->fc = p;
    el->f10 = found ? found->f10 : 0;
    el->f14 = flag;
    el->f18 = 0;

    FrameProp* prop = 0;                         // frame-property object handed back by the manager
    HashIter hit;
    this->ht.find(&hit, &c);
    if (hit.mpNode != this->ht.buckets[this->ht.nbuckets]) {
        el->f18 = (uint32_t)&hit.mpNode->mKey;
    } else {
        PropertyManager* pm = (PropertyManager*)SP_PropertyManager();
        if (prop) { FrameProp* old = prop; prop = 0; old->Release(); }
        if (pm->get((int)c, (const wchar_t*)0x689fa1a, (void**)&prop)) {
            FrameValue* fv = (FrameValue*)this->ht.find_or_add(&c);
            fv->mDelay = 0x1388;
            fv->mText.assign(SPUIShader_AcquireShaderProxy());
            fv->mFlag08 = 0;
            FUN_00ac9480(&fv->mProp, (void**)&prop);
            applyFrame(fv);
            el->f18 = (uint32_t)fv;
        }
    }
    if (prop) { FrameProp* old = prop; old->Release(); }
}

// @ 0x00e313c0
void CardView::update(float dt)
{
    if (b7c) {
        float v = f68 - dt * 0.4f;
        f68 = v;
        if (v <= 0.0f) {
            b7c = 0;
            f68 = 0.0f;
        }
        if (f68 <= 0.0f) {
            void* p = a94;
            ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 0);
            return;
        }
    } else {
        if (f68 >= 1.0f) {
            void* p = a88; ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 1);
            p = a90;       ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 1);
            p = a98;       ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 1);
            return;
        }
        float* e = (float*)vecEnd;
        float* p = (float*)vecBegin;
        for (; p != e; p += 2) {
            float* q = p + 2;
            float t = p[1] * dt;
            float* src = &t;
            if (*p <= t) src = p;
            float val = *src;
            f68 = val + f68;
            float d = *p - val;
            *p = d;
            if (d <= 0.0f) {
                uint32_t* endv = (uint32_t*)vecEnd;
                uint32_t* s = (uint32_t*)q;
                if (s < endv) {
                    uint32_t* dst = (uint32_t*)p;
                    do {
                        dst[0] = s[0];
                        dst[1] = s[1];
                        s += 2;
                        dst += 2;
                    } while (s != endv);
                }
                vecEnd = (char*)vecEnd - 8;
            }
        }
        if (f68 <= 0.0f)
            return;
    }
    void* p = a94;
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 1);
    ((void(__thiscall*)(void*, float, float))(*(void***)p)[0x68 / 4])(
        p, (*(float*)((char*)this + 0x74) - *(float*)((char*)this + 0x6c)) * f68,
        *(float*)((char*)this + 0x78) - *(float*)((char*)this + 0x70));
}

// @ 0x00e31550
void CardView::hide()
{
    ((void(__thiscall*)(void*, int, int))(*(void***)a84)[0x7c / 4])(a84, 1, 1);
    ((void(__thiscall*)(void*, int, int))(*(void***)a88)[0x7c / 4])(a88, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)a8c)[0x7c / 4])(a8c, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)a90)[0x7c / 4])(a90, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)a94)[0x7c / 4])(a94, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)a98)[0x7c / 4])(a98, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)aa4)[0x7c / 4])(aa4, 1, 0);
    f68 = 0.0f;
    _ReadWriteBarrier();
    Vec1c* v = (Vec1c*)((char*)this + 0x10);
    v->erase(v->begin, v->end);
    b7c = 0;
}

// @ 0x00e315f0
void CardView::add(uint32_t a, uint32_t b)
{
    uint32_t local[2];
    local[0] = a;
    local[1] = b;
    char* end = (char*)vecEnd;
    if (end < (char*)vecCap) {
        *(void**)((char*)this + 0x14) = end + 8;
        if (end) {
            *(uint32_t*)end = a;
            *(uint32_t*)(end + 4) = b;
        }
        return;
    }
    ((TC*)((char*)this + 0x10))->f_e63d60(end, local);
}

// @ 0x00e31670
void cSPUISocialRainbow::F0e31670(void)
{
    /* large frame update; not reconstructed */
}

// @ 0x00e319d0
void cSPUISocialRainbow::SetCurrent(int i, float t)
{
    RainbowInstance& r = mInstances[i];
    float f = r.mBase;
    r.mCurrent = (r.mTarget - f) * t + f;
    mFlag24 = 1;
}

// @ 0x00e31a30
double cSPUISocialRainbow::Ratio(int i)
{
    float a, b;
    if (i == 1) {
        a = mF40;
        b = mF40 - mInstances[1].mCurrent;
    } else {
        a = mF3c;
        b = mInstances[i].mCurrent + mF3c;
    }
    return fabs(a - b) / fabs(mF3c - mF40);
}

// @ 0x00e31b30
void F0e31b30(void* unused, unsigned int* raw, Variant* out)
{
    char* base;
    if ((raw[4] & 0x30) != 0)
        base = (char*)*raw;
    else
        base = (*(unsigned short*)((char*)raw + 0x12) != 0) ? (char*)raw : 0;
    out->SetFloat(*(float*)(base + 0x94));
}

// @ 0x00e31b70
bool F0e31b70(void* unused, unsigned int* raw, int v)
{
    unsigned int base;
    if ((raw[4] & 0x30) != 0)
        base = *raw;
    else
        base = (*(unsigned short*)((char*)raw + 0x12) != 0) ? (unsigned int)raw : 0;
    if (v == 0)
        *(char*)(base + 0x9c) = 0;
    else if (v == 1)
        *(char*)(base + 0x9c) = 1;
    return true;
}

// @ 0x00e33d40
void __stdcall SetSporepediaLargeAssetValue(void* pValue)
{
    SP::PropertyManager()->SetProperty(0x120b89ce, pValue);
}

// @ 0x00e33d60
void cSPUISwatchView::AddConfiguredModelKey()
{
    AddModelKey(mConfiguredModelKey);
}

// @ 0x00e33d70
void cSPUISwatchView::ShutdownView()
{
    if (mpEffectA) {
        mpEffectA->Stop(true);
        mpEffectA = 0;
    }
    if (mpEffectB) {
        mpEffectB->Stop(true);
        mpEffectB = 0;
    }
    Shutdown();
}

// @ 0x00e33de0
cUISporepediaPlanetLargeAssetView::cUISporepediaPlanetLargeAssetView()
: mpUnused0c(0), mbVisible(false), mbInitialized(false), mbPending(false)
{
    for (int i = 0; i < 5; ++i)
        mpEffects[i] = 0;
}

// @ 0x00e33e70
cUISporepediaPlanetLargeAssetView::~cUISporepediaPlanetLargeAssetView()
{
    if (mpMessageListener)
        mpMessageListener->Release();
    if (mpNameProvider)
        mpNameProvider->Release();
    if (mpColourCfg)
        mpColourCfg->Release();
    mpValueWindow = 0;
    mpDescriptionWindow = 0;
    mpTitleWindow = 0;
    mpIcon2Window = 0;
    mpIconWindow = 0;
    mpLayout = 0;
}

// @ 0x00e33f30
void cUISporepediaPlanetLargeAssetView::Destroy()
{
    mbVisible = false;
    if (mpMessageListener) {
        CastToViewModel(mpMessageListener.Get())->Unload();
        mpMessageListener = 0;
    }
    if (mpLayout) {
        mpLayout->Shutdown(1);
        mpLayout = 0;
    }
}

// @ 0x00e33f90
void cUISporepediaPlanetLargeAssetView::ReleaseWindows()
{
    if (!mbInitialized)
        return;
    if (mpColourCfg)
        mpColourCfg->ResetColour();
    mpColourCfg = 0;
    if (mpIcon2Window)
        mpIcon2Window->SetWinProc((IWinProc_s00e3_3270*)(PA_Agg*)this);
    mpIcon2Window = 0;
    mpTitleWindow = 0;
    mpDescriptionWindow = 0;
    mbInitialized = false;
}

// @ 0x00e34020
void cUISporepediaPlanetLargeAssetView::LoadLayout()
{
    if (mbInitialized)
        return;

    mpIconWindow = mpLayout->FindWindowByID(0xf3c6dc19, true);
    if (mpIconWindow.Get()) {
        mpIconWindow->SetLayoutArea((void*)(PA_Agg*)this);
        SetWindowAreaToParent(mpIconWindow.Get());
    }

    mpTitleWindow = mpLayout->FindWindowByID(0x53d6fe29, true);
    if (mpTitleWindow.Get() && mpNameProvider) {
        const wchar_t* pText = mpNameProvider->GetTitle();
        if (!pText)
            pText = gMissingText;
        mpTitleWindow->SetCaption(pText);
    }

    mpDescriptionWindow = mpLayout->FindWindowByID(0x53d6fe2a, true);
    if (mpDescriptionWindow.Get() && mpNameProvider) {
        const wchar_t* pText = mpNameProvider->GetDescription();
        if (!pText)
            pText = gMissingText;
        mpDescriptionWindow->SetCaption(pText);
    }

    mpValueWindow = mpLayout->FindWindowByID(0x5e62a30, true);

    ColourCfg* pCfg = (ColourCfg*)operator new(0x20, gColourCfgName, 0, 0, 0, 0);
    if (pCfg)
        pCfg = new (pCfg) ColourCfg();
    mpColourCfg = pCfg;
    mpColourCfg->ApplyLayout(mpLayout.Get());
    mbInitialized = true;
}

// @ 0x00e34220
cSPUISwatchView::cSPUISwatchView()
: mpUnused184(0), mpUnused188(0)
{
}

// @ 0x00e34290
cSPSwatchView::~cSPSwatchView()
{
    if (mpExtra)
        mpExtra->Release();
    if (mpTarget)
        mpTarget->Release();
    if (mpSwatchRef) {
        int32_t count = mpSwatchRef->mRefCount;
        if (count > 1) {
            mpSwatchRef->mRefCount = count - 1;
        } else {
            mpSwatchRef->mpVtbl->pDestroy(mpSwatchRef, mpSwatchRef->mFlags >> 31);
        }
    }
}

// @ 0x00e34310
void cSPSwatchView::Update(int32_t delta)
{
    CVSBase::Update(delta);
    float angle = (float)delta / 1000.0f * 360.0f;
    cSPSwatchModel* pModel = (cSPSwatchModel*)mpCreature;
    if (pModel) {
        ((cModelSource*)pModel)->GetModel(0);
        pModel->PreRotateY(angle);
    }
    cSPSwatchModel* pSwatch = (cSPSwatchModel*)mpSwatchRef;
    if (pSwatch) {
        ((cModelSource*)pSwatch)->GetModel(0);
        pSwatch->PreRotateY(angle);
    }
    if (mpTarget) {
        uint32_t color[4];
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        color[3] = 0x3f800000;
        cXform xform;
        xform.Assign((const float*)&color[0]);
        mpTarget->v20();
        xform.RotateZ(angle);
        mpTarget->v18();
    }
}

// @ 0x00e34470
void cAssetSwatchWidget::InitLayout()
{
    cSPUILayout_s00e3_4290* pNew = (cSPUILayout_s00e3_4290*)operator new(0x18, (void*)0x013f6b3c, 0, 0, 0, 0);
    if (pNew)
        pNew = pNew->ctor();
    else
        pNew = 0;
    cSPUILayout_s00e3_4290* pOld = mpLayout;
    if (pNew != pOld) {
        if (pNew)
            pNew->v04();
        mpLayout = pNew;
        if (pOld)
            pOld->v08();
    }
    mpLayout->Init(EAKey(0xf0f17503, 0x0510a95b, 0x40464100), true, 0x05b598fa);
    mpLayout->SetParentWin(mpParent, true, 0x05b598fa);
    mpLayout->SetReloadCallback(ReloadAssetSwatch, this);
    LoadLayoutOfWidget(this);
}

// @ 0x00e34540
void cSPSwatchView::InitSwatch(const ViewRecord& key, const ViewRecord& outer, uint32_t a, uint32_t b, uint32_t c)
{
    m17c = outer.m00;
    m180 = outer.m04;
    m184 = outer.m08;
    CVSBase::Update(0);
    (void)a;
    (void)b;
    (void)c;
    (void)key;
    if (mpCreature) {
        cSPSwatchModel* pModel = (cSPSwatchModel*)mpCreature;
        ((cModelSource*)pModel)->GetModel(0);
        pModel->PreRotateY(0.0f);
    }
}

// @ 0x00e34a00
bool cAssetSwatchWidget::HandleMessage()
{
    return mpAsset != 0;
}

// @ 0x00e34af0
void cAssetSwatchWidget::CreateSwatch()
{
    if (!mpAsset)
        return;
    ViewRecord key;
    key.m00 = mpRecordKey->m00;
    key.m04 = mpRecordKey->m04;
    key.m08 = mpRecordKey->m08;
    cNounTag* pTag = ResolveNounTag(&key);
    if (!pTag->IsValid())
        return;
}

// @ 0x00e34bd0
void cAssetSwatchWidget::HandleMessage2()
{
    (void)mpView;
}

// @ 0x00e34da0
void cAssetView::RefreshRecord(uint32_t flags)
{
    if (!mbRecordValid) {
        cNounTag* pTag = ResolveNounTag(&mRecord);
        mbRecordValid = pTag->IsValid();
        if (mbRecordValid)
            RefreshSwatch();
    }
    if (mpHolder)
        mpHolder->Release();
    (void)flags;
}

// @ 0x00e34eb0
bool cToolButton::SetTool(uint32_t toolId, uint32_t data)
{
    switch (toolId) {
    case 0x03e9a620:
        mbActive = true;
        mToolId = data;
        return true;
    case 0x03e9a625:
        mbActive = false;
        mToolId = 0;
        return true;
    }
    return false;
}

// @ 0x00e34f40
void AssetSwatchUpdate(void* pWidget)
{
    (void)pWidget;
}

// @ 0x00e35290
void cAssetView::ShowRelationship(int32_t a, int32_t b, bool show)
{
    mpRollover->ShowRelationshipRollover(a, b, show == 0);
}

// @ 0x00e36150
cSPUITooltipPanel::cSPUITooltipPanel(float fSize, cSPUILayout_s00e3_6150* pLayout, void* pRaster, void* pOwner)
: m_nKey08(0),
      m_pWindow0c(0),
      m_pLayout10(pLayout),
      m_pRaster14(pRaster),
      m_pOwner18(pOwner),
      m_pTargetWin1c(0)
{
    if (m_pLayout10 != nullptr)
        m_pLayout10->Release1();

    m_rect20.x0 = 0.0f;
    m_rect20.y0 = 0.0f;
    m_rect20.x1 = fSize;
    m_rect20.y1 = fSize;

    m_pTargetWin1c = (IWin*)m_pLayout10->GetWindow();
    m_pWindow0c = (IWin*)FUN_009512d0(0x20c, 4, "UI/UTFWin/Window",
                                      FUN_009512c0());
    if (m_pWindow0c != nullptr)
        m_pWindow0c = (IWin*)FUN_00962a10(m_pWindow0c);

    m_pLayout10->SetParentWin(m_pWindow0c, true, 0x5b598fa);
}

// @ 0x00e36260
cSPUITooltipPanel::~cSPUITooltipPanel()
{
    if (m_pLayout10 == nullptr) {
        if (m_pTargetWin1c != nullptr) {
            m_pTargetWin1c->SetParentd8(m_pWindow0c);
            m_pWindow0c->SetRect6c(&m_rect20);
        }
    } else {
        m_pLayout10->SetParentWin(m_pTargetWin1c, false, 0x5b598fa);
    }

    if (m_pTargetWin1c != nullptr)
        m_pTargetWin1c->Release1();
    if (m_pLayout10 != nullptr)
        m_pLayout10->Release2();
    if (m_pWindow0c != nullptr)
        m_pWindow0c->Release1();
}

// @ 0x00e362f0
void cSPUITooltipPanel::Render(uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4)
{
    cWindowManager* pManager = (cWindowManager*)SP_WindowManager();
    cViewer viewer;
    viewer.Construct();
    viewer.Init(false);
    viewer.SetRaster(&m_pRaster14, true);

    IView* pView = (IView*)pManager->GetView();
    if (pView != nullptr)
        pView->AddRef0();

    Vector4 bounds = *pView->GetBounds();
    pManager->SetWindow(m_pWindow0c, false);
    pManager->SetViewport(m_rect20.x1 - m_rect20.x0,
                          m_rect20.y1 - m_rect20.y0);
    pManager->Reset24();

    Vector4 points;
    points.x = 0.0f;
    points.y = 0.0f;
    points.z = 0.0f;
    points.w = 0.0f;
    cBoundingBox* pBox = (cBoundingBox*)cSPBoundingBox_AddBoundingBox();
    pBox->AddPoints(a4, a4, &points, a4);

    pManager->SetViewport(m_rect20.x1 - m_rect20.x0 + (bounds.x - a3),
                          m_rect20.y1 - m_rect20.y0 + (bounds.y - a4));
    pManager->Reset24();
    pManager->SetWindow(m_pWindow0c, false);

    if (pView != nullptr)
        pView->Release1();
    viewer.Shutdown();
}

// @ 0x00e36480
cUITimedTooltip::cUITimedTooltip()
: m_nPad04(0),
      m_nKey08(0),
      m_pLayout(0),
      m_pWindow(0),
      m_swA(0, false),
      m_swB(0, false)
{
    m_nTimeoutA = 0;
    m_nTimeoutB = 0;
    m_f50 = 0.0f;
    m_f54 = 0.0f;
    m_f58 = 0.0f;
    m_f5c = 0.0f;
}

// @ 0x00e364d0
cUITimedTooltip::~cUITimedTooltip()
{
    _ReadWriteBarrier();
    if (m_pWindow != nullptr)
        m_pWindow->Release1();
    if (m_pLayout != nullptr)
        m_pLayout->Release2();
}

// @ 0x00e36500
void cUITimedTooltip::Shutdown()
{
    if (m_pLayout != nullptr)
        m_pLayout->Shutdown(1);
    if (m_pLayout != nullptr) {
        cSPUILayout_s00e3_6150* pLayout = m_pLayout;
        m_pLayout = nullptr;
        pLayout->Release2();
    }
    if (m_pWindow != nullptr) {
        IWin* pWindow = m_pWindow;
        m_pWindow = nullptr;
        pWindow->Release1();
    }
}

// @ 0x00e36540
void cUITimedTooltip::UpdateTimeoutA()
{
    if (m_pLayout == nullptr)
        return;
    if (m_swA.m_nStart == 0)
        return;
    if (m_swA.GetElapsedTime() > (int64_t)m_nTimeoutA) {
        m_pLayout->SetVisibility(true);
        m_swA.m_nStart = 0;
        m_swA.m_nStop = 0;
    }
}

// @ 0x00e365a0
void cUITimedTooltip::UpdateTimeoutB(IWin* pWindow)
{
    if (m_pLayout == nullptr)
        return;

    FUN_00808b20(pWindow, m_pWindow, 0);

    if (m_swB.m_nStart != 0) {
        if (m_swB.GetElapsedTime() > (int64_t)m_nTimeoutB) {
            m_pLayout->SetVisibility(true);
            m_swB.m_nStart = 0;
            m_swB.m_nStop = 0;
            return;
        }
    }
    m_swA.Restart();
}

// @ 0x00e36620
void cUITimedTooltip::Hide()
{
    if (m_pLayout == nullptr)
        return;
    if (!m_pLayout->IsVisible())
        return;
    m_pLayout->SetVisibility(false);
    m_swB.Restart();
}

// @ 0x00e36650
void* cUITimedTooltip::FindWindow(uint32_t nId, bool bFlag)
{
    void* result = nullptr;
    if (m_pLayout != nullptr)
        result = m_pLayout->FindWindowByID(nId, bFlag);
    return result;
}

// @ 0x00e36670
Vector4* __cdecl AccumulateBounds(Vector4* pOut, IWinNode* pNode, bool bDeep, bool bFilter)
{
    pOut->x = 0.0f;
    pOut->y = 0.0f;
    pOut->z = 0.0f;
    pOut->w = 0.0f;

    uint32_t* pIter;
    uint32_t* pEnd;
    pNode->Scc(&pIter);
    pNode->Sd0(&pEnd);

    while (pIter != pEnd) {
        IWinNode* pChild = (IWinNode*)(gspUIElementBase + *pIter);
        if (!bFilter || (pChild->S28() & 1) != 0) {
            RectF childRect = *pChild->S38();
            RectF grown = childRect;

            if (bDeep) {
                Vector4 inner;
                AccumulateBounds(&inner, pChild, bDeep, bFilter);
                grown.x0 = inner.x + childRect.x0;
                grown.y0 = inner.y + childRect.y0;
                grown.x1 = grown.x0 + (childRect.x1 - childRect.x0);
                grown.y1 = grown.y0 + (childRect.y1 - childRect.y0);

                if (childRect.x0 != childRect.x1
                    && childRect.y0 != childRect.y1) {
                    grown = childRect;
                    if (inner.x != inner.z && inner.y != inner.w) {
                        if (grown.x0 < inner.x)
                            grown.x0 = inner.x;
                        if (grown.y0 < inner.y)
                            grown.y0 = inner.y;
                        if (grown.x1 < inner.z)
                            grown.x1 = inner.z;
                        if (grown.y1 < inner.w)
                            grown.y1 = inner.w;
                    }
                }
            }

            if (pOut->x != pOut->z && pOut->y != pOut->w) {
                if (grown.x0 == grown.x1 || grown.y0 == grown.y1) {
                    grown.x0 = pOut->x;
                    grown.y0 = pOut->y;
                    grown.x1 = pOut->z;
                    grown.y1 = pOut->w;
                } else {
                    if (grown.x0 > pOut->x)
                        grown.x0 = pOut->x;
                    if (grown.y0 > pOut->y)
                        grown.y0 = pOut->y;
                    if (grown.x1 < pOut->z)
                        grown.x1 = pOut->z;
                    if (grown.y1 < pOut->w)
                        grown.y1 = pOut->w;
                }
            }

            pOut->x = grown.x0;
            pOut->y = grown.y0;
            pOut->z = grown.x1;
            pOut->w = grown.y1;
        }
        pIter = (uint32_t*)*pIter;
    }
    return pOut;
}

// @ 0x00e36890
void* cUITimedTooltip::DestroyDeleting(bool bDelete)
{
    if (m_pWindow != nullptr)
        m_pWindow->Release1();
    if (m_pLayout != nullptr)
        m_pLayout->Release2();
    if (bDelete)
        operator_delete_array(this);
    return this;
}

// @ 0x00e368e0
void __cdecl ReloadTooltip(void* pUser, cSPUILayout_s00e3_6150* pLayout, bool bDisplay)
{
    if (!bDisplay)
        return;

    cUITimedTooltip* pTooltip = (cUITimedTooltip*)pUser;
    IWin* pFound = nullptr;
    if (pTooltip->m_pLayout != nullptr)
        pFound = (IWin*)pTooltip->m_pLayout->FindWindowByID(pTooltip->m_nKey08,
                                                            true);

    if (pFound != pTooltip->m_pWindow) {
        if (pFound != nullptr)
            pFound->AddRef0();
        IWin* pOld = pTooltip->m_pWindow;
        pTooltip->m_pWindow = pFound;
        if (pOld != nullptr)
            pOld->Release1();
    }

    if (pTooltip->m_pWindow == nullptr) {
        if (pTooltip->m_pLayout != nullptr) {
            cSPUILayout_s00e3_6150* pOldLayout = pTooltip->m_pLayout;
            pTooltip->m_pLayout = nullptr;
            pOldLayout->Release2();
        }
        return;
    }

    pTooltip->m_pLayout->SetVisibility(false);
    pTooltip->m_pWindow->SetFlags7c(true, false);
    pTooltip->m_pLayout->SetParentWin(nullptr, true, 0x5b598f6);

    Vector4 bounds;
    AccumulateBounds(&bounds, (IWinNode*)pTooltip->m_pWindow, true, true);

    RectF* pRect = ((IWinNode*)pTooltip->m_pWindow)->S38();
    pTooltip->m_f50 = bounds.x;
    pTooltip->m_f54 = bounds.y;
    pTooltip->m_f58 = (pRect->x1 - pRect->x0) - bounds.z;
    pTooltip->m_f5c = (pRect->y1 - pRect->y0) - bounds.w;
}

// @ 0x00e369f0
void cUITimedTooltip::UpdateLayout()
{
    if (m_pLayout == nullptr)
        return;

    Vector4 bounds;
    AccumulateBounds(&bounds, (IWinNode*)m_pWindow, true, true);

    float fDX = m_f50 - bounds.x;
    float fDY = m_f54 - bounds.y;
    if (fDX != 0.0f || fDY != 0.0f) {
        uint32_t* pIter;
        uint32_t* pEnd;
        ((IWinNode*)m_pWindow)->Scc(&pIter);
        ((IWinNode*)m_pWindow)->Sd0(&pEnd);
        while (pIter != pEnd) {
            IWinNode* pNode = (IWinNode*)(gspUIElementBase + *pIter);
            RectF* pRect = pNode->S38();
            pNode->S70(pRect->x0 + fDX, pRect->y0 + fDY);
            pIter = (uint32_t*)*pIter;
        }
    }

    ((IWinNode*)m_pWindow)->S74(m_f58 + ((bounds.z - bounds.x) + m_f50),
                                m_f5c + ((bounds.w - bounds.y) + m_f54));
}

// @ 0x00e36b30
bool cUITimedTooltip::Init(const uint32_t& nKey, uint32_t nId, uint32_t nWidth, uint32_t nHeight, uint32_t a5, uint32_t a6)
{
    m_nTimeoutA = nWidth;
    m_nTimeoutB = nHeight;

    cSPUILayout_s00e3_6150* pLayout = (cSPUILayout_s00e3_6150*)operator_new(
        0x18, (const void*)0x13f6b3c, 0, 0, 0, 0);
    if (pLayout != nullptr)
        pLayout = pLayout->InitDocument();

    if (pLayout != m_pLayout) {
        if (pLayout != nullptr)
            pLayout->Release1();
        cSPUILayout_s00e3_6150* pOld = m_pLayout;
        m_pLayout = pLayout;
        if (pOld != nullptr)
            pOld->Release2();
    }

    if (!m_pLayout->Init(&nKey, false, 0x5b598f6)) {
        if (m_pLayout != nullptr) {
            cSPUILayout_s00e3_6150* pOld = m_pLayout;
            m_pLayout = nullptr;
            pOld->Release2();
        }
        return m_pLayout != nullptr;
    }

    m_nKey08 = nId;
    m_pLayout->SetReloadCallback(ReloadTooltip, this);
    ReloadTooltip(this, m_pLayout, true);
    return m_pLayout != nullptr;
}

// @ 0x00e36cd0
bool cUITimedTooltip::UpdateA()
{
    EA::Stopwatch_s00e3_6150& sw = m_sw418;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold430) {
        if (m_pAnimator458->Empty()) {
            sw.SetBoolProperty();
            return true;
        }
    }
    return false;
}

// @ 0x00e36d30
bool cUITimedTooltip::UpdateB()
{
    EA::Stopwatch_s00e3_6150& sw = m_sw3f8;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold410) {
        sw.SetBoolProperty();
        return true;
    }
    return false;
}

// @ 0x00e36d80
bool cUITimedTooltip::UpdateC()
{
    EA::Stopwatch_s00e3_6150& sw = m_sw438;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold450) {
        sw.SetBoolProperty();
        return true;
    }
    return false;
}

// @ 0x00e36de0
void cUITimedTooltip::ResetState()
{
    m_nMode3f0 = 9;
    m_bFlag454 = false;
}

// @ 0x00e39ec0
bool ColorPropertyBinding::SetValue(IPropertyList_s00e3_9ab0* pList)
{
    Variant_s00e3_9ab0* pValue;
    if (!pList->GetProperty(mPropertyId, &pValue))
        return false;
    uint16_t type = pValue->mTypeId;
    float* pData;
    if (type == 0x34 || type == 0x10)
        pData = (pValue->mFlags & 0x30) ? (float*)pValue->mpData
              : (float*)((type != 0 ? -1 : 0) & (int32_t)pValue);
    else
        pData = GetDefaultColor();
    float value[4] = { pData[0], pData[1], pData[2], pData[3] };
    if (mValue[0] == value[0] && mValue[1] == value[1]
        && mValue[2] == value[2] && mValue[3] == value[3])
        return false;
    mValue[0] = value[0];
    mValue[1] = value[1];
    mValue[2] = value[2];
    mValue[3] = value[3];
    return true;
}
