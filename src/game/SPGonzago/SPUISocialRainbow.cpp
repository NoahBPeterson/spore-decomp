// src/game/SPGonzago/SPUISocialRainbow.cpp -- migrated from slice(s) s00e33270, s00e32580, s00e31670, s00e22860 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUISocialRainbow.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIAnimator.h"
#include "cSPUILayout.h"
#include "EA/Variant.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/Image.h"
#include "EA/UTFWin/Message.h"
#include "EA/UTFWin/RenderContext.h"
#include "SP/cSPSwatch.h"

// ---- items of slice s00e22860 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
struct cEmbeddedObject {
    void* mpVtbl0;                 // 0x00
};
struct cHolderObj {
    u8              mPad0000[0x0c];
    cEmbeddedObject mEmbedded0c;   // 0x0c
};
static inline void* VT_0C_1(void* p, int a)
{
    return ((void* (__thiscall*)(void*, int))(*(void***)p)[0x03])(p, a);
}
static inline void* VT_10_1(void* p, int a)
{
    return ((void* (__thiscall*)(void*, int))(*(void***)p)[0x04])(p, a);
}
static inline void* VT_18_0(void* p)
{
    return ((void* (__thiscall*)(void*))(*(void***)p)[0x06])(p);
}
static inline int VT_A8_0(void* p)
{
    return ((int (__thiscall*)(void*))(*(void***)p)[0x2a])(p);
}
// ---- items of slice s00e22860 end

// ---- items of slice s00e31670 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
void  F0e31d60(cSPUISocialRainbow* self);   // 0x00e31d60
// ---- items of slice s00e31670 end

// ---- items of slice s00e32580 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _ReadWriteBarrier(void);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl atan2(double, double);
extern "C" double __cdecl acos(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(_ReadWriteBarrier)
typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef double f64;
#define VT(p) (*(void***)(p))
struct cSPUISocialRainbow_s00e3_2580;
struct COps {
    // cSPUILayout
    u8    FUN_008120d0(void* key, u8 b, u32 hash);   // 0x008120d0 Init
    void  FUN_00810090(void* cb, void* user);        // 0x00810090 SetReloadCallback
    void* FUN_008105b0(u32 id, u8 b);                // 0x008105b0 FindWindowByID
    void  FUN_00810000();                            // 0x00810000 ctor
    void  FUN_00811fe0();                            // 0x00811fe0 dtor
    // cSPUIAnimator
    void  FUN_007f83e0();                            // 0x007f83e0 ctor
    void  FUN_007f8c20();                            // 0x007f8c20 dtor
    u8    FUN_007f6210(void* win, s32 id);           // 0x007f6210 RemoveAnimation
};
#define MOPS(p) ((COps*)(p))
struct cSPUILayout_s00e3_2580 {
    u8 pad0[0x18];
};
struct cSPUIAnimator_s00e3_2580 {
    u8    pad0[0x20];
    void* mOwner;
};
struct cSide {
    void* mBegin;       // +0x00
    void* mEnd;         // +0x04
    void* mCap;         // +0x08
    u8    pad0c[4];     // +0x0c
    void* mBase;        // +0x10
    u8    pad14[4];     // +0x14
    u8    mBuf[0x78];   // +0x18
    f32   m90;          // +0x90
    f32   m94;          // +0x94
    f32   m98;          // +0x98
    u8    m9c;          // +0x9c
    u8    m9d;          // +0x9d
    u8    pad9e[2];     // +0x9e
    void* mObj;         // +0xa0
};
struct cSPUISocialRainbow_s00e3_2580 {
    void* mVtbl;            // 0x000
    void* mVtbl2;           // 0x004
    u32   m08;              // 0x008
    cSPUILayout_s00e3_2580 mLayout;    // 0x00c
    u8    m24;              // 0x024
    u8    m25;              // 0x025
    u8    m26;              // 0x026
    u8    pad27;            // 0x027
    f32   m28;              // 0x028
    f32   m2c;              // 0x02c
    f32   m30;              // 0x030
    f32   m34;              // 0x034
    f32   m38;              // 0x038
    f32   m3c;              // 0x03c
    f32   m40;              // 0x040
    u32   m44;              // 0x044
    cSPUIAnimator_s00e3_2580 mAnimator; // 0x048
    void* m6c;              // 0x06c
    void* m70;              // 0x070
    void* m74;              // 0x074
    void* m78;              // 0x078
    void* m7c;              // 0x07c
    void* m80;              // 0x080
    void* m84;              // 0x084
    void* m88;              // 0x088
    void* m8c;              // 0x08c
    void* m90;              // 0x090
    u8    pad94[0xc];       // 0x094
    u32   mA0;              // 0x0a0
    cSide mSide0;           // 0x0a4
    cSide mSide1;           // 0x148
    void* m1ec;             // 0x1ec
    void* m1f0;             // 0x1f0
    void* m1f4;             // 0x1f4
    void* m1f8;             // 0x1f8
    void* m1fc;             // 0x1fc

    void FUN_00e32160(s32); // 0x00e32160
    void FUN_00e32c80();
    u8   FUN_00e32de0();
    void FUN_00e32f00();
    cSPUISocialRainbow_s00e3_2580* FUN_00e330c0();
};
struct cB20Arg {
    u8  pad0[0x1c];
    s32 m1c;    // +0x1c
    s32 m20;    // +0x20
};
extern f32 g13f0e84;
extern f32 g15a5794;
extern f32 g1477fc0;
extern f32 g13ec4d0;
extern f32 g15a5790;
extern f32 g13eb1bc;
void  __cdecl FUN_00f47380(void*);                 // 0x00f47380 operator delete[]
void* __cdecl FUN_00e232b0(void*);                 // 0x00e232b0 sGetWindowImage
void  __cdecl FUN_00808230(void*, f32*);           // 0x00808230
void* __cdecl FUN_00805ea0(void*);                 // 0x00805ea0 GetMainWindowArea
// ---- items of slice s00e32580 end

// ---- items of slice s00e33270 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct IUnknown32 {
    virtual int AddRef();                    // +0x00
    virtual int Release();                   // +0x04
    virtual void v08();                      // +0x08
};
class RefCountVTemplate {
 public:
    virtual ~RefCountVTemplate();            // +0x00 scalar deleting destructor

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
struct IWindow;
struct IWinProc : public IUnknown32 {
    virtual bool DoMessage(IWindow* pWindow, void* pMessage);    // +0x0c
};
struct IViewBehavior : public IUnknown32 {
};
struct IViewBehavior2 : public IUnknown32 {
};
struct Image : public IUnknown32 {
    uint mPad[5];                            // +0x08
    int mWidth;                              // +0x1c
    int mHeight;                             // +0x20
};
struct IRenderable : public IUnknown32 {
};
struct IViewEffect : public IUnknown32 {
    virtual void Stop(bool bImmediate);      // +0x0c
    virtual void v10();                      // +0x10
};
struct IWindow : public IUnknown32 {
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
    virtual void SetWinProc(IWinProc* proc);               // +0x108
};
class cSPUILayout_s00e3_3270 : public RefCountVTemplate {
 public:
    virtual int AddRef();                                        // vtable slot 4
    virtual int Release();                                       // vtable slot 8
    void SetReloadCallback(void (__cdecl*)(void*, cSPUILayout_s00e3_3270*, bool), void*);  // 0x00810090
    IWindow* FindWindowByID(uint id, bool recursive) const;      // 0x008105b0
    void Shutdown(uint destroy);                                 // 0x00811ad0

    unsigned char mResourceKey[12];                              // +0x08
    void** mpObjectCollection;                                   // +0x14
};
struct Vec2f {
    float x;
    float y;
};
class cSPUIAnimator_s00e3_3270 {
 public:
    void ClearAll();                                             // 0x007f8f00
    void Update();                                               // 0x007f63b0

    void** mpVftable;                                            // +0x00
    void*  mpAnimationInfosBegin;                                // +0x04
    void*  mpAnimationInfosEnd;                                  // +0x08
    void*  mpAnimationInfosCapacity;                             // +0x0c
    void*  mpAnimationInfosAllocator;                            // +0x10
    float  mLastUpdateTime;                                      // +0x14
    int    mPad;                                                 // +0x18 (aligns the 0x1c retail size)
};
struct cRound {
    float mArcTo;          // +0x00
    float mNumSegments;    // +0x04
    uint  mColor;          // +0x08
    float mRate;           // +0x0c
    float mMinRate;        // +0x10
};
class cRoundVector {
 public:
    void DoInsertValue(cRound* position, const cRound& value);   // 0x00e33850

    cRound* mpBegin;                 // +0x00
    cRound* mpEnd;                   // +0x04
    cRound* mpCapacity;              // +0x08
    void*   mpAllocator;             // +0x0c
    cRound* mpInlineStorage;         // +0x10
    cRound  mInlineStorage[6];       // +0x14
    uint    mInlineCapacity;         // +0x8c
    uint    mCapacityValue;          // +0x90
};
class cSideInfo {
 public:
    void Clear();                                            // 0x00e33990

    cRoundVector mRounds;                                    // +0x00
    float mArcSize;                                          // +0x94
    float mArcSizeTarget;                                    // +0x98
    bool  mbStopBarAnimation;                                // +0x9c
    bool  mbBarDone;                                         // +0x9d
    IViewEffect* mpDraw;                                     // +0xa0
};
class cSPUISocialRainbow_s00e3_3270 : public IWinProc, public IViewBehavior, public IViewBehavior2 {
 public:
    enum eState {
        kStateEmpty = 1,
        kStateFull = 2,
        kStatePartial = 3,
    };

    bool DoMessage(IWindow* pWindow, void* pMessage);          // 0x00e33270
    void Reset();                                              // 0x00e33ce0
    bool ReleaseResources();                                   // 0x00e33a00
    void StartFill(int nSide, int nSegments, float fMinRate, float fRate,
                   float fFraction, uint color, void* pParam); // 0x00e33ab0

    void Init();                                               // 0x00e32de0
    void set_full();                                           // 0x00e32f00
    void UpdateSide(int nSide);                                // 0x00e324f0
    void UpdateSideDisplay(int nSide, int nShow, void* pParam);// 0x00e32250
    void get_round_bounds(int nSide, int nRound, float* pFrom, float* pTo);  // 0x00e31bb0

    cSPUILayout_s00e3_3270 mLayout;                       // +0x0c
    bool  mbRebuild;                           // +0x24
    bool  mbInitialized;                       // +0x25
    bool  mbFull;                              // +0x26
    unsigned char mPad27;                      // +0x27
    Vec2f mScreenPos;                          // +0x28
    Vec2f mArcCenter;                          // +0x30
    float mArcRadius;                          // +0x38
    float mArcAngleFrom;                       // +0x3c
    float mArcAngleTo;                         // +0x40
    int   mSegmentCount;                       // +0x44
    cSPUIAnimator_s00e3_3270 mAnimator;                   // +0x48
    IUnknown32* mpAnimationObject;             // +0x64
    Image* mpImageRightBarEndNotch;            // +0x68
    Image* mpImageLeftBarEndNotch;             // +0x6c
    Image* mpImageBarNotch;                    // +0x70
    Image* mpImageBar;                         // +0x74
    Image* mpImageBarBackground;               // +0x78
    Image* mpImageBarHighlight;                // +0x7c
    Image* mpImageBarFull;                     // +0x80
    IRenderable* mpBackgroundRenderable;       // +0x84
    Vec2f* mpDebugPointsBegin;                 // +0x88
    Vec2f* mpDebugPointsEnd;                   // +0x8c
    Vec2f* mpDebugPointsCapacity;              // +0x90
    eState mState;                             // +0x94
    uint  mStateFlagsFull;                     // +0x98
    unsigned char mPad9c[8];                   // +0x9c
    cSideInfo mSideInfos[2];                   // +0xa4 (sizeof(cSideInfo) == 0xa4)
    IRenderable* mpArcRenderable;              // +0x1ec
    IRenderable* mpFullBarRenderable;          // +0x1f0
    IRenderable* mpSegmentsRenderable;         // +0x1f4
    IRenderable* mpRelationshipIcon;           // +0x1f8
    IRenderable* mpStarburst;                  // +0x1fc
};
class RenderCtx {
 public:
    void AddRenderable(IRenderable* pRenderable);        // 0x0095bbc0
    void* Begin2D(void* pRenderMode);                    // 0x0095bc10
};
void  operator delete[](void* p);
inline void  operator delete(void*, void*) throw() {}
extern "C" IRenderable* __cdecl FUN_00828e30(RenderCtx* pCtx, IWindow* pWindow, void** ppOut);  // 0x00828e30
extern "C" void       __cdecl FUN_00828ef0(RenderCtx* pCtx, void* pRenderable);                 // 0x00828ef0
extern "C" void       __cdecl FUN_00e31d60(void* pBatch, float x, float y, float radius, int a, int b,
float angleFrom, float angleTo, Image* pImage, float step);
struct Message {
    void* mpVftable;          // +0x00
    int   mPad04;
    int   mMessageID;         // +0x08
    int   mPad0c;
    int   mPad10;
    int   mPad14;
    RenderCtx* mpRenderContext;  // +0x18
};
struct ArcSegment {
    int   mSide;              // +0x00
    float mAngleEnd;          // +0x04
    float mAngleStart;        // +0x08
    Image* mpImage;           // +0x0c
};
// ---- items of slice s00e33270 end

// @ 0x00e232b0
void* sGetWindowImage(void* window)
{
    if (window != 0) {
        if (VT_A8_0(window) != 0) {
            void* inner = (void*)VT_A8_0(window);
            if (inner != 0) {
                void* obj = VT_0C_1(inner, 0xef3c47cf);
                if (obj != 0)
                    return VT_18_0(obj);
                obj = VT_0C_1(inner, 0x103c1908);
                if (obj != 0)
                    return VT_10_1(obj, 0);
                obj = VT_0C_1(inner, 0x053eb526);
                if (obj != 0) {
                    cHolderObj* holder = (cHolderObj*)obj;
                    return VT_10_1(&holder->mEmbedded0c, 0);
                }
            }
        }
    }
    return 0;
}

// @ 0x00e31c90
void cSPUISocialRainbow::Fwd(void)
{
    void* w = mpF1fc;
    void** vt = *(void***)w;
    ((void(__thiscall*)(void*, int, int))vt[0x7c / 4])(w, 1, 1);
}

// @ 0x00e31cb0
void cSPUISocialRainbow::Mode(int p)
{
    switch (p) {
    case 4: mpF1f8->SetMode(4); break;
    case 3: mpF1f8->SetMode(3); break;
    case 1: mpF1f8->SetMode(2); break;
    case 2: mpF1f8->SetMode(1); break;
    case 5: mpF1f8->SetMode(0); break;
    case 6: mpF1f8->SetMode(5); break;
    }
}

// @ 0x00e320c0
void F0e320c0(void* unused, unsigned int* a, unsigned int* b, unsigned int* c, float t)
{
    char* dst;
    if ((a[4] & 0x30) != 0)
        dst = (char*)*a;
    else
        dst = (*(unsigned short*)((char*)a + 0x12) != 0) ? (char*)a : 0;

    float* p2;
    unsigned short ty2 = *(unsigned short*)((char*)b + 0x12);
    if (ty2 == 0xd || ty2 == 0x10) {
        if ((b[4] & 0x30) != 0)
            p2 = (float*)*b;
        else
            p2 = (ty2 != 0) ? (float*)b : 0;
    } else
        p2 = (float*)0x015d1168;

    float* p3;
    unsigned short ty3 = *(unsigned short*)((char*)c + 0x12);
    if (ty3 == 0xd || ty3 == 0x10) {
        if ((c[4] & 0x30) != 0)
            p3 = (float*)*c;
        else
            p3 = (ty3 != 0) ? (float*)c : 0;
    } else
        p3 = (float*)0x015d1168;

    *(float*)(dst + 0x94) = (*p3 - *p2) * t + *p2;
}

// @ 0x00e32580
void __cdecl FUN_00e32580(cSPUISocialRainbow_s00e3_2580* self, void* layout, u8 reload)
{
    if (self)
        ((void (__thiscall*)(void*))VT(self)[0])(self);

    void* winC = 0;
    if (reload == 0) {
        void* w = MOPS(&self->mLayout)->FUN_008105b0(0x562bd40, 1);
        if (w)
            ((void (__thiscall*)(void*, void*))VT(w)[0x108 / 4])(w, self);
    } else {
        self->mAnimator.mOwner = self;
        void* w = MOPS(&self->mLayout)->FUN_008105b0(0x562bd40, 1);
        ((void (__thiscall*)(void*, void*))VT(w)[0x104 / 4])(w, self);

        void* img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x563bb08, 1));
        void* old = self->m6c;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m6c = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x563bb10, 1));
        old = self->m70;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m70 = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        winC = MOPS(&self->mLayout)->FUN_008105b0(0x563bb18, 1);
        img = FUN_00e232b0(winC);
        old = self->m74;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m74 = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }
        ((void (__thiscall*)(void*, s32, s32))VT(winC)[0x7c / 4])(winC, 1, 0);

        img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x563bb38, 1));
        old = self->m78;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m78 = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x564eeb8, 1));
        old = self->m7c;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m7c = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x564ee80, 1));
        old = self->m80;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m80 = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        void* winA = MOPS(&self->mLayout)->FUN_008105b0(0x563bb50, 1);
        f32 apos[4];
        f32* ap = (f32*)((void* (__thiscall*)(void*))VT(winA)[0x38 / 4])(winA);
        apos[0] = ap[0];
        apos[1] = ap[1];
        apos[2] = ap[2];
        apos[3] = ap[3];
        ((void (__thiscall*)(void*, void*))VT(winA)[0x104 / 4])(winA, self);

        void* winB = MOPS(&self->mLayout)->FUN_008105b0(0x562c1a0, 1);
        f32 bpos[4];
        f32* bp = (f32*)((void* (__thiscall*)(void*))VT(winB)[0x38 / 4])(winB);
        bpos[0] = bp[0];
        bpos[1] = bp[1];
        bpos[2] = bp[2];
        bpos[3] = bp[3];
        ((void (__thiscall*)(void*, f32, f32))VT(winB)[0x70 / 4])(winB, bpos[0], apos[1]);
        bp = (f32*)((void* (__thiscall*)(void*))VT(winB)[0x38 / 4])(winB);
        bpos[0] = bp[0];
        bpos[2] = bp[2];
        ((void (__thiscall*)(void*, void*))VT(winB)[0x104 / 4])(winB, self);

        f32* cp = (f32*)((void* (__thiscall*)(void*))VT(winC)[0x38 / 4])(winC);
        f32 s0 = (apos[2] + apos[0]) * 0.5f;
        f32 s1 = (bpos[2] + bpos[0]) * 0.5f;
        f32 s2 = (apos[3] + apos[1]) * 0.5f;
        f32 s3 = (cp[3] + cp[1]) * 0.5f;
        f32 num = s2 - s3;
        f32 den = s0 - (s1 + s0) * 0.5f;
        f32 q = g13eb1bc / (den / num);
        f32 ang = (f32)atan2((f64)q, 1.0);

        f32 mat[5];
        mat[0] = 0.0f;
        mat[1] = 0.0f;
        mat[2] = 1.0f;
        mat[3] = -ang - g15a5794;
        FUN_00808230(winA, mat);
        mat[0] = 0.0f;
        mat[1] = 0.0f;
        mat[2] = 1.0f;
        mat[3] = g15a5794 + ang;
        FUN_00808230(winB, mat);

        f32 out1[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(winA)[0xc0 / 4])(winA, out1, s0 - s1, 0.0f);
        void* tr1 = (void*)((void* (__thiscall*)(void*))VT(winA)[0x10 / 4])(winA);
        f32 out2[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(tr1)[0xc4 / 4])(tr1, out2, s0, s2);

        f32 out3[2];
        ((void (__thiscall*)(void*, f32*, s32, s32))VT(winB)[0xc0 / 4])(winB, out3, 0, 0);
        void* tr2 = (void*)((void* (__thiscall*)(void*))VT(winB)[0x10 / 4])(winB);
        f32 out4[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(tr2)[0xc4 / 4])(tr2, out4, out2[0], out2[1]);

        f32 out5[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(winA)[0xc0 / 4])(winA, out5, s1, s3);
        void* tr3 = (void*)((void* (__thiscall*)(void*))VT(winA)[0x10 / 4])(winA);
        f32 out6[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(tr3)[0xc4 / 4])(tr3, out6, out4[0], out4[1]);

        f32 A = out5[0];
        f32 B = out6[0];
        f32 C = s1;
        f32 D = out5[1];
        f32 E = out6[1];
        f32 r = ((E - D) * (C - A)) / (B - A) + D;
        f32 t = D - r;
        self->m30 = C;
        self->m34 = r;
        self->m38 = (f32)sqrt((f64)(t * t + C * (C - A)));
        f32 ac = (f32)acos((f64)(t / num));
        self->m24 = 1;
        self->m3c = g15a5794 - ac;
        self->m40 = g15a5794 + ac;
    }

    self->m25 = reload;
    ((void (__thiscall*)(void*))VT(self)[1])(self);
}

// @ 0x00e32b20
void __cdecl FUN_00e32b20(void* a1, f32 a2, f32 a3, f32 a4, u32 a5, u32 a6, f32 a7, void* a8)
{
    cB20Arg* arg = (cB20Arg*)a8;
    f32 sn = (f32)sin((f64)a7);
    f32 cs = (f32)cos((f64)a7);

    f32 x = cs * a4 + a2;
    f32 y = a3 - sn * a4;
    f32 a4b = a4 - (f32)arg->m20;
    f32 x2 = cs * a4b + a2;
    f32 y2 = a3 - sn * a4b;
    f32 h = ((f32)arg->m1c * cs) * 0.5f;
    f32 v = (-sn * (f32)arg->m1c) * 0.5f;

    f32 m[16];
    m[0]  = x - v;
    m[1]  = y + h;
    m[2]  = (f32)a6;
    m[3]  = 1.0f;
    m[4]  = 0.0f;
    m[5]  = x + v;
    m[6]  = y - h;
    m[7]  = (f32)a6;
    m[8]  = 0.0f;
    m[9]  = 0.0f;
    m[10] = x2 + v;
    m[11] = y2 - h;
    m[12] = (f32)a5;
    m[13] = 0.0f;
    m[14] = 1.0f;
    m[15] = x2 - v;

    ((void (__thiscall*)(void*, f32*, s32, void*))VT(a1)[0x54 / 4])(a1, m, 1, a8);
}

// @ 0x00e32c80
void cSPUISocialRainbow_s00e3_2580::FUN_00e32c80()
{
    *(volatile void**)&mVtbl = (void*)0x14819b0;
    *(volatile void**)&mVtbl2 = (void*)0x1481994;
    _ReadWriteBarrier();
    if (m1fc) ((void (__thiscall*)(void*))VT(m1fc)[1])(m1fc);
    if (m1f8) ((void (__thiscall*)(void*))VT(m1f8)[1])(m1f8);
    if (m1f4) ((void (__thiscall*)(void*))VT(m1f4)[1])(m1f4);
    if (m1f0) ((void (__thiscall*)(void*))VT(m1f0)[1])(m1f0);
    if (m1ec) ((void (__thiscall*)(void*))VT(m1ec)[1])(m1ec);
    _ReadWriteBarrier();

    cSide* p = &mSide1 + 1;
    for (s32 i = 1; i >= 0; i--) {
        void* obj = p[-1].mObj;
        p--;
        if (obj) ((void (__thiscall*)(void*))VT(obj)[1])(obj);
        if (p->mBegin && p->mBegin != p->mBase)
            FUN_00f47380(p->mBegin);
    }

    if (m88 && ((u32*)m88)[-1] != 0)
        FUN_00f47380(m88);
    if (m84) ((void (__thiscall*)(void*))VT(m84)[1])(m84);
    if (m80) ((void (__thiscall*)(void*))VT(m80)[1])(m80);
    if (m7c) ((void (__thiscall*)(void*))VT(m7c)[1])(m7c);
    if (m78) ((void (__thiscall*)(void*))VT(m78)[1])(m78);
    if (m74) ((void (__thiscall*)(void*))VT(m74)[1])(m74);
    if (m70) ((void (__thiscall*)(void*))VT(m70)[1])(m70);
    if (m6c) ((void (__thiscall*)(void*))VT(m6c)[1])(m6c);

    MOPS(&mAnimator)->FUN_007f8c20();
    MOPS(&mLayout)->FUN_00811fe0();
    mVtbl2 = (void*)0x13eb938;
    mVtbl = (void*)0x13eb938;
}

// @ 0x00e32de0
u8 cSPUISocialRainbow_s00e3_2580::FUN_00e32de0()
{
    union {
        u32 key[4];
        u8  area[0x10];
    } buf;
    buf.key[0] = 0xe539924e;
    buf.key[1] = 0x0510a95b;
    buf.key[2] = 0x40464100;
    if (!MOPS(&mLayout)->FUN_008120d0(buf.key, 1, 0x3f608b3e))
        return 0;

    MOPS(&mLayout)->FUN_00810090((void*)FUN_00e32580, this);
    FUN_00e32580(this, &mLayout, 1);

    void* win = MOPS(&mLayout)->FUN_008105b0(0x53daa60, 1);
    if (win) {
        void** vt = VT(win);
        void* p = FUN_00805ea0(buf.area);
        ((void (__thiscall*)(void*, void*))vt[0x6c / 4])(win, p);
        ((void (__thiscall*)(void*))VT(win)[0x94 / 4])(win);
    }

    void* w2 = MOPS(&mLayout)->FUN_008105b0(0x53daa70, 1);
    void* img = (void*)((void* (__thiscall*)(void*, u32))VT(w2)[0x0c / 4])(w2, 0x105a93d);
    void* old = m1f8;
    if (img != old) {
        if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
        m1f8 = img;
        if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
    }

    void* w3 = MOPS(&mLayout)->FUN_008105b0(0x741ff10a, 1);
    old = m1fc;
    if (w3 != old) {
        if (w3) ((void (__thiscall*)(void*))VT(w3)[0])(w3);
        m1fc = w3;
        if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
    }

    return m25;
}

// @ 0x00e32f00
void cSPUISocialRainbow_s00e3_2580::FUN_00e32f00()
{
    if (m26 != 0)
        return;

    *(volatile u8*)&m24 = 1;
    *(volatile f32*)&mSide1.m98 = *(volatile f32*)&mSide1.m94;
    FUN_00e32160(1);
    if (mSide1.m98 == 0.0f) {
        void* win = MOPS(&mLayout)->FUN_008105b0(0x562c170, 1);
        if (((u8 (__thiscall*)(void*))VT(win)[0x28 / 4])(win) & 1)
            ((void (__thiscall*)(void*, s32, s32))VT(win)[0x7c / 4])(win, 1, 0);
    }

    *(volatile u8*)&m24 = 1;
    *(volatile f32*)&mSide0.m98 = *(volatile f32*)&mSide0.m94;
    FUN_00e32160(0);
    if (mSide0.m98 == 0.0f) {
        void* win = MOPS(&mLayout)->FUN_008105b0(0x562c1b8, 1);
        if (((u8 (__thiscall*)(void*))VT(win)[0x28 / 4])(win) & 1)
            ((void (__thiscall*)(void*, s32, s32))VT(win)[0x7c / 4])(win, 1, 0);
    }

    MOPS(&mAnimator)->FUN_007f6210(MOPS(&mLayout)->FUN_008105b0(0x562c170, 1), -1);

    void* arr[2];
    arr[0] = MOPS(&mLayout)->FUN_008105b0(0x562c1b8, 1);
    arr[1] = MOPS(&mLayout)->FUN_008105b0(0x562c170, 1);
    for (u32 k = 0; k < 2; k++) {
        void* w = arr[k];
        if (w) {
            MOPS(&mAnimator)->FUN_007f6210(w, -1);
            void** vt = VT(w);
            u32 v = ((u32 (__thiscall*)(void*))vt[0x30 / 4])(w);
            ((void (__thiscall*)(void*, u32))vt[0x5c / 4])(w, (v & 0xffffff) - 0x1000000);
        }
    }

    arr[0] = MOPS(&mLayout)->FUN_008105b0(0x562c178, 1);
    arr[1] = MOPS(&mLayout)->FUN_008105b0(0x564f020, 1);
    u32 i2;
    for (i2 = 0; i2 < 2; i2++) {
        void* w = arr[i2];
        if (w) {
            ((void (__thiscall*)(void*, s32, s32))VT(w)[0x7c / 4])(w, 1, 1);
            u32* vt2 = (u32*)VT(w);
            u32 v = ((u32 (__thiscall*)(void*))vt2[0x30 / 4])(w);
            ((void (__thiscall*)(void*, u32))vt2[0x5c / 4])(w, (v & 0xffffff) - 0x1000000);
        }
    }

    m24 = 1;
    m26 = 1;
}

// @ 0x00e330c0
cSPUISocialRainbow_s00e3_2580* cSPUISocialRainbow_s00e3_2580::FUN_00e330c0()
{
    *(volatile void**)&mVtbl2 = (void*)0x13fa72c;
    m08 = 0;
    *(volatile void**)&mVtbl = (void*)0x14819b0;
    *(volatile void**)&mVtbl2 = (void*)0x1481994;
    MOPS(&mLayout)->FUN_00810000();

    m24 = 1;
    m25 = 0;
    m26 = 0;
    m28 = g13f0e84;
    m2c = g1477fc0;
    *(volatile f32*)&m30 = *(volatile f32*)&m28;
    m34 = g1477fc0 + m38;
    m38 = g13ec4d0;
    m3c = g15a5790;
    m40 = g15a5794 + g15a5790;
    m44 = 0;

    MOPS(&mAnimator)->FUN_007f83e0();

    m6c = 0;
    m70 = 0;
    m74 = 0;
    m78 = 0;
    m7c = 0;
    m80 = 0;
    m84 = 0;
    m88 = 0;
    m8c = 0;
    m90 = 0;
    mA0 = 0;
    _ReadWriteBarrier();

    mSide0.mBase = mSide0.mBuf;
    mSide0.mEnd = mSide0.mBuf;
    mSide0.mBegin = mSide0.mBuf;
    *(volatile f32*)&mSide0.m90 = 0.0f;
    *(volatile f32*)&mSide0.m94 = 0.0f;
    *(volatile f32*)&mSide0.m98 = 0.0f;
    mSide0.m9c = 0;
    mSide0.m9d = 0;
    mSide0.mCap = mSide0.mBuf + 0x78;
    mSide0.mObj = 0;

    mSide1.mBase = mSide1.mBuf;
    mSide1.mEnd = mSide1.mBuf;
    mSide1.mBegin = mSide1.mBuf;
    *(volatile f32*)&mSide1.m90 = 0.0f;
    *(volatile f32*)&mSide1.m94 = 0.0f;
    *(volatile f32*)&mSide1.m98 = 0.0f;
    mSide1.m9c = 0;
    mSide1.m9d = 0;
    mSide1.mCap = mSide1.mBuf + 0x78;
    mSide1.mObj = 0;

    m1ec = 0;
    m1f0 = 0;
    m1f4 = 0;
    m1f8 = 0;
    m1fc = 0;
    _ReadWriteBarrier();

    ((void (__thiscall*)(void*))VT(&mLayout)[1])(&mLayout);

    return this;
}

// @ 0x00e33270
bool cSPUISocialRainbow_s00e3_3270::DoMessage(IWindow* pWindow, void* pMessageRaw)
{
    Message* pMessage = (Message*)pMessageRaw;

    if (pMessage->mMessageID == 0x0c) {                    // kMsgUpdate
        mAnimator.Update();

        bool bFull = mSideInfos[1].mArcSize + mSideInfos[0].mArcSize
                         >= mArcAngleTo - mArcAngleFrom
                  && mSideInfos[1].mRounds.mpBegin != mSideInfos[1].mRounds.mpEnd
                  && mSideInfos[0].mRounds.mpBegin != mSideInfos[0].mRounds.mpEnd;

        if (!mbFull) {
            if (bFull)
                set_full();
            if (!mbFull) {
                for (int nSide = 0; nSide < 2; ++nSide) {
                    if (mSideInfos[nSide].mbStopBarAnimation) {
                        mSideInfos[nSide].mbStopBarAnimation = false;
                        UpdateSide(nSide);
                    }
                }
            }
        }
        if (mSideInfos[1].mbBarDone && mSideInfos[1].mArcSize == mSideInfos[1].mArcSizeTarget)
            mSideInfos[1].mbBarDone = false;
        if (mSideInfos[0].mbBarDone && mSideInfos[0].mArcSize == mSideInfos[0].mArcSizeTarget)
            mSideInfos[0].mbBarDone = false;

        if (mbRebuild) {
            IWindow* pBar = mLayout.FindWindowByID(0x562bd40, true);
            pBar->Refresh();
        }
    } else if (pMessage->mMessageID == 0x0d) {              // kMsgRender
        if (pWindow->GetControlID() != 0x562bd40)
            return false;

        RenderCtx* pCtx = pMessage->mpRenderContext;

        if (!mpArcRenderable) {
            mpArcRenderable = FUN_00828e30(pCtx, pWindow, (void**)&mpArcRenderable);
            FUN_00e31d60(mpArcRenderable, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                         mArcAngleFrom, mArcAngleTo, mpImageBarHighlight, 0.1f);
            FUN_00828ef0(pCtx, mpArcRenderable);
        }
        pCtx->AddRenderable(mpArcRenderable);

        if (mbFull) {
            if (!mpFullBarRenderable) {
                IRenderable* pBatch =
                    FUN_00828e30(pCtx, pWindow, (void**)&mpFullBarRenderable);
                FUN_00e31d60(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                             mArcAngleFrom, mArcAngleTo, mpImageBarFull, 0.1f);
                FUN_00e31d60(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                             mArcAngleFrom, mArcAngleTo, mpImageBarBackground, 0.1f);
                FUN_00828ef0(pCtx, mpFullBarRenderable);
            }
            pCtx->AddRenderable(mpFullBarRenderable);
            return true;
        }

        ArcSegment segments[2];
        segments[0].mSide = 1;
        segments[0].mAngleEnd = mArcAngleTo;
        segments[0].mAngleStart = mArcAngleTo - mSideInfos[1].mArcSize;
        segments[0].mpImage = mpImageBarNotch;
        segments[1].mSide = 0;
        segments[1].mAngleEnd = mArcAngleFrom;
        segments[1].mAngleStart = mArcAngleFrom + mSideInfos[0].mArcSize;
        segments[1].mpImage = mpImageLeftBarEndNotch;

        for (int nSegment = 0; nSegment < 2; ++nSegment) {
            ArcSegment& segment = segments[nSegment];
            cSideInfo& side = mSideInfos[segment.mSide];
            bool bArcChanged = side.mArcSize != side.mArcSizeTarget;
            if (side.mRounds.mpBegin != side.mRounds.mpEnd) {
                if (!bArcChanged || side.mpDraw == 0) {
                    if (side.mpDraw) {
                        IViewEffect* pOld = side.mpDraw;
                        side.mpDraw = 0;
                        pOld->Release();
                    }
                    void* pBatch;
                    if (bArcChanged) {
                        pBatch = FUN_00828e30(pCtx, pWindow, (void**)&side.mpDraw);
                    } else {
                        pBatch = pCtx->Begin2D(0);
                    }
                    FUN_00e31d60(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                                 segment.mAngleEnd, segment.mAngleStart, mpImageBarBackground,
                                 0.1f);
                    FUN_00e32b20(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, -1, -1,
                                 segment.mAngleStart, segment.mpImage);
                    FUN_00828ef0(pCtx, side.mpDraw);
                }
                if (side.mpDraw)
                    pCtx->AddRenderable((IRenderable*)side.mpDraw);
            }
        }

        if ((uint)mSegmentCount > 0) {
            if (mpSegmentsRenderable) {
                IRenderable* pOld = mpSegmentsRenderable;
                mpSegmentsRenderable = 0;
                pOld->Release();
            }
            void* pBatch = FUN_00828e30(pCtx, pWindow, (void**)&mpSegmentsRenderable);

            float fLow = mArcAngleFrom < mArcAngleTo ? mArcAngleFrom : mArcAngleTo;
            float fCount = (float)(mSegmentCount * 2);
            float fStep = (mArcAngleTo - mArcAngleFrom) / fCount;

            float fNext = 0.0f;
            if (0.0f < fCount) {
                do {
                    FUN_00e32b20(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, 0x8f000000,
                                 0x8f000000, fNext * fStep + fLow, mpImageBar);
                    fNext = fNext + 1.0f;
                } while (fNext < fCount);
            }
            FUN_00e32b20(pBatch, mArcCenter.x, mArcCenter.y, mArcRadius, 0x8f000000, 0x8f000000,
                         (fNext * fStep + fLow) - 0.01f, mpImageBar);
            FUN_00828ef0(pCtx, mpSegmentsRenderable);
        }
        pCtx->AddRenderable(mpSegmentsRenderable);
        return true;
    }
    // IWinProc::DoMessage (0x00950ef0): the base message handler.
    return IWinProc::DoMessage(pWindow, pMessageRaw);
}
