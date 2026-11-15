// src/game/Spui/_at_00810000.cpp -- migrated from slice(s) s0081c9c0, s0081a790, s00817cb0, s00816d40, s00815dd0, s008124a0 by tools/migrate/rewrite.py
// Object file: Spui/_at_00810000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"
#include "cSPUILayoutObjectCollection.h"
#include <intrin.h>
#include "cSPUILayoutManager.h"
#include "cSPUILayout.h"
#include "cSPUIMessageBox.h"
#include "SP/cString.h"
#include "EA/DateTime/DateTime.h"
#include <new>
#include <math.h>
#include "EA/Text/LineLayout.h"
#include "EA/Text/Typesetter.h"
#include <wchar.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void*   SP_MessageServer(); // 0x0067dcc0
extern "C" void*   SP_CheatManager();
extern "C" void* __cdecl memcpy(void*, const void*, size_t);   // 0x011e0744
extern "C" void* __cdecl memset(void*, int, size_t);

// ---- items of slice s008124a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Mouse;
struct Rect4f { float x0, y0, x1, y1; };
struct Rect4i { int x0, y0, x1, y1; };
struct Sub {
    virtual void   s00();
    virtual void   s01();
    virtual void   s02();
    virtual void   s03();
    virtual void   s04();
    virtual Mouse* s05();
    virtual void   s06();
    virtual void   s07();
    virtual void   s08();
    virtual void   s09();
    virtual void   s0a();
    virtual void   s0b();
    virtual void   s0c();
    virtual Rect4f* s0d();
};
struct Y {
virtual void y00();
virtual void y01();
virtual void y02();
virtual void y03();
virtual void y04();
virtual void y05();
virtual void y06();
virtual void y07();
    virtual void y08(int);          // 0x20
    virtual void y09(int);          // 0x24
    virtual bool y10(int, int);     // 0x28
    virtual bool y11(int, int);     // 0x2c
};
struct X {
virtual void x00();
virtual void x01();
virtual void x02();
virtual void x03();
virtual void x04();
virtual void x05();
virtual void x06();
virtual void x07();
virtual void x08();
virtual void x09();
virtual void x0a();
    virtual Y*   x0b();
virtual void x0c();
virtual void x0d();
    virtual Y*   x0e();
virtual void x0f();
virtual void x10();
virtual void x11();
virtual void x12();
    virtual void x13();
    virtual X*   x14();
};
struct ZoomWin {
virtual void z00();
virtual void z01();
virtual void z02();
virtual void z03();
    virtual ZoomWin* z04();
virtual void z05();
virtual void z06();
virtual void z07();
virtual void z08();
virtual void z09();
virtual void z0a();
virtual void z0b();
virtual void z0c();
    virtual float* z0d();
    virtual float* z0e();
};
struct W9 {
virtual void w0();
virtual void w1();
virtual void w2();
virtual void w3();
virtual void w4();
virtual void w5();
virtual void w6();
virtual void w7();
virtual void w8();
virtual void w9();
};
struct Canvas {
virtual void  c00();
virtual void  c01();
virtual void  c02();
virtual void  c03();
virtual void  c04();
virtual void  c05();
virtual void  c06();
virtual void  c07();
virtual void  c08();
virtual void  c09();
virtual void  c10();
virtual void  c11();
virtual void  c12();
virtual void  c13();
virtual void  c14();
virtual void* c15(void*);
virtual void  c16();
virtual void  c17();
virtual void  c18();
virtual void  c19();
virtual void  c20();
virtual void  c21();
virtual void  c22();
virtual void  c23();
virtual void  c24();
virtual void  c25();
virtual void  c26();
virtual void  c27();
virtual void  c28();
virtual void  c29();
virtual void  c30();
virtual void  c31(int, int);
};
struct Q12 {
virtual void q0();
virtual void q1();
virtual void q2();
virtual void q3();
virtual void q4();
virtual void q5();
virtual void q6();
virtual void q7();
virtual void q8();
virtual void q9();
virtual void q10();
virtual void q11();
    virtual void q12(int, int, int);
};
extern "C" Canvas* SP_Canvas();        // 0x0067dcf0
extern "C" void*   SP_MessageServer(); // 0x0067dcc0
extern "C" void*   SP_CheatManager();
#define sMouseXScale (*(float*)0x15451e8)
#define sMouseYScale (*(float*)0x15451ec)
struct ZoomBase {
    void SetStyleWindow(int);
};
struct Zoom : ZoomBase {
    char pad0[0x10];
    float m10, m14, m18, m1c;   // +0x10 mMyArea
    float m20, m24, m28, m2c;   // +0x20 mMyPhysicalArea
    float m30, m34, m38, m3c;   // +0x30 mRelArea
    void* mpMyWindow;           // +0x40

    Zoom();
    void SetWindow(void* p);
    void Transform(const float* r, float* out);
    bool Init(ZoomWin* p);
};
struct MainWin {
    char pad0[0x4];
    Sub  sub;                   // +0x4
    char pad1[0x260 - 0x4 - sizeof(Sub)];
    W9*  mp260;                 // +0x260
    char pad2[0x268 - 0x260 - 4];
    X*   mp268;                 // +0x268
    X*   mp26c;                 // +0x26c
    char pad3[0x284 - 0x26c - 4];
    uint8_t b284, b285, b286;   // +0x284
    char pad4[0x28d - 0x287];
    uint8_t b28d;               // +0x28d
    char pad5[0x2dc - 0x28e];
    uint8_t b2dc;               // +0x2dc

    void BaseSetup();
    unsigned GetFlags();
    void Teardown(int);
    bool BuildMouseMsg(const void* in, void* out);
    void OnMouse(bool active);
    void UpdateMouseScale();
    void SetFocusObj(X* p);
    void ApplyToFocus(int arg);
    bool RouteKey(int a, int key, int mod);
};
struct Mouse {
    void GetPositionStatic(int, int);
};
extern "C" void* __cdecl memcpy(void*, const void*, size_t);   // 0x011e0744
extern "C" void* __cdecl memset(void*, int, size_t);
struct MsgEnv {
    uint32_t  id;        // +0x0
    Canvas*   canvas;    // +0x4
    uint32_t* payload;   // +0x8
    uint32_t  data[8];   // +0xc
};
void __cdecl FUN_008d2f30(int*, int*);
struct Stopwatch_s0081_24a0 {
    char pad[0x14];
    float mScale;                    // +0x14
    int64_t GetElapsedTimeFloat();   // 0x93a3a0
};
struct MainWinTimer {
    char pad[0x228];
    Stopwatch_s0081_24a0 mTimer;                // +0x228
    float GetScaledElapsed();
};
struct AutoRefPair {
    char pad[0x250];
    uint32_t lo, hi;
    uint64_t Get();
};
namespace EA {
namespace ArgScript {
class cArguments_s0081_24a0 { public:
    void    MainArguments(int);                                  // 0x00838320
    int     NumArguments();                                      // 0x00837f30
    char**  OptionArguments(const char* name, int* pNum, int a, int b); // 0x00838130
    char**  OptionArguments(const char* name, int a);            // 0x00838330
    bool    HasFlag(const char* name);                           // 0x008380b0
};
}
}
namespace EA {
namespace ArgScript {
class cCommandBase_s0081_24a0 { public:
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
    virtual ~cCommandBase_s0081_24a0();
    char* mParser;      // +4
    int   mRefCount;    // +8
    void* mState;       // +0xc
};
}
}
using EA::ArgScript::cArguments_s0081_24a0;
using EA::ArgScript::cCommandBase_s0081_24a0;
struct LayoutMap {
    char pad0[0x0c];
    void* mRoot;         // +0xc
    char pad1[0x1c - 0x10];
    void DoNukeSubtree(void* root);
    ~LayoutMap();
};
inline LayoutMap::~LayoutMap() { DoNukeSubtree(mRoot); }
class cSPUILayoutCheat_s0081_24a0 : public cCommandBase_s0081_24a0 { public:
    LayoutMap mLayouts;                 // +0x10
    cSPUILayoutCheat_s0081_24a0();
    void Execute(cArguments_s0081_24a0* args);  // 0x008124a0 (cSPUILayoutCheat::Execute)
};
cSPUILayoutCheat_s0081_24a0::cSPUILayoutCheat_s0081_24a0() {
    mParser = 0;
    mRefCount = 0;
    mState = 0;
    *(void**)((char*)this + 0x14) = (char*)this + 0x14;
    *(void**)((char*)this + 0x18) = (char*)this + 0x14;
    *(int*)((char*)this + 0x1c) = 0;
    *(uint8_t*)((char*)this + 0x20) = 0;
    *(int*)((char*)this + 0x24) = 0;
}
// ---- items of slice s008124a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" Canvas* SP_Canvas();        // 0x0067dcf0

// ---- items of slice s00815dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_WindowManager();
extern "C" void  SPUIHelpers_BeginModal(void*, void*, int);
extern "C" void  SPUIHelpers_AnchorWindowToWindow(void*, void*, int, int);
typedef unsigned int      u32;
typedef unsigned char     u8;
extern "C" void  SPUIHelpers_SetWindowSPMaterial(void*, void*, u8);
static inline void* Vcp1(void* p, int off, void* a) {
    return ((void*(__thiscall*)(void*, void*))(*(void***)p)[off / 4])(p, a);
}
static inline void* Vcp0(void* p, int off) {
    return ((void*(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void  Vv1(void* p, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void  Vv2(void* p, int off, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
static inline int   Vi0(void* p, int off) {
    return ((int(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline int   Vi1(void* p, int off, int a) {
    return ((int(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
struct IObj;
struct MaterialTarget {
    char pad_00[0x58];
    u32  mat;      // +0x58
    char pad_5c[0x80 - 0x5c];
    u32* tex;      // +0x80
    u8   flag;     // +0x84
};
struct MatEffect {
    char  pad_00[0x60];
    u32   f60, f64, f68, f6c;   // +0x60
    u32   f70, f74, f78, f7c;   // +0x70
    u32*  p80;                  // +0x80
    u8    b84;                  // +0x84
    char  pad_85[3];
    float f88;                  // +0x88

    void  sub8167d0(IObj* p, float f);
    MatEffect* ctor816860();
    void  dtor816910();
};
class cSPUILayout_s0081_5dd0 { public:
    char pad_00[0x0c];
    void* FindWindowByID(u32 id, int arg);     // 0x8105b0
    void  Init(u32 a, int b, int c, const wchar_t* s); // 0x812160
    void  Shutdown(int arg);                   // 0x811ad0
};
struct CalloutMessageBox {
    char        pad_00[0x0c];
    cSPUILayout_s0081_5dd0 layout;    // +0x0c
    char        pad_18[0x24 - 0x18];
    int         mEnterBtn; // +0x24
    int         mEscBtn;   // +0x28
    u8          b2c;       // +0x2c
    int         mResult;   // +0x30
    u8          b34;       // +0x34
    char        pad_35[0x38 - 0x35];
    char        stopwatch[0x20]; // +0x38
    void*       mpCallback;      // +0x58
    u8          b5c;             // +0x5c
    char        pad_5d[0x60 - 0x5d];
    u32         f60, f64, f68, f6c;
    u8          b70;

    bool  sub816990();
    void  sub816a20(int, int, int, int);
    void  sub816b20(int id, int owner);
    bool  sub816b90(int id, void* msg);
    void* sub816ca0();
    void  ctor816cb0(int cb);
};
// ---- items of slice s00815dd0 end

// ---- items of slice s00816d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_MovieSystem();
extern "C" void* FUN_0067de40();
extern "C" void  EA_Messaging_RemoveHandler(int, int, int, int, int);
extern "C" void* Property_GetBool();
extern "C" void* MsgServerW();              // 0x0067dcc0  SP::MessageServer
extern "C" void  MemFreeW(void*);           // 0x00f47380  operator delete
extern "C" u32   FNV1_String16(const wchar_t* s, u32 basis, int);
static inline void Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline char Vb0(void* p, int off) {
    return ((char(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline char Vb2(void* p, int off, int a, int b) {
    return ((char(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
struct EString {
    EString& operator=(const EString&);
    void     Load(u32, u32, const wchar_t*);
};
class cSPUILayout_s0081_6d40 { public:
    char  pad_00[0x0c];
    void* FindWindowByID(u32 id, int arg);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void  Shutdown(int arg);  // 0x00811ad0 (cSPUILayout::Shutdown)
    void  Init(u32 a, int b, int c, const wchar_t* s);  // 0x00812160 (cSPUILayout::Init)
    ~cSPUILayout_s0081_6d40();
};
struct MsgBoxB {
    char  pad_00[0x10];
    void* mLayout;     // +0x10
    void* mW1;         // +0x14
    void* mW2;         // +0x18
    void* mW3;         // +0x1c
    void* mHandler;    // +0x20
    u32   hA, hB, hC, hD; // +0x24..0x30
    void  teardown();
};
struct MsgBoxC {
    char  pad_00[0x14];
    void* mW1;   // +0x14
    void* mW2;   // +0x18
    void* mW3;   // +0x1c
    char  pad_20[0x35 - 0x20];
    u8    b35;   // +0x35
    void setVisible(int on);
};
struct MsgBoxD {
    char  pad_00[0x10];
    void* mLayout;  // +0x10
    void* mW1;      // +0x14
    void* mW2;      // +0x18
    void* mW3;      // +0x1c
    void rebind();
};
static void BindWin(void** slot, void* neu, int callOffset) {
    void* old = *slot;
    if (neu == old) return;
    if (neu) Vv0(neu, 0);
    *slot = neu;
    if (old) Vv0(old, 0x04);
}
struct MsgBoxE {
    char  pad_00[0x14];
    void* mW1;   // +0x14
    void* mW2;   // +0x18
    void* mW3;   // +0x1c
};
struct MsgBoxF {
    char pad_00[0x30];
    u8   b30;   // +0x30
    bool setMovieState(u32 id);
};
struct Helper817670 { void Fn(int arg); };
struct CellNameSrc {
    char     pad_00[0x30];
    EString* f30;  // +0x30
    EString* f34;  // +0x34
    EString* f38;  // +0x38
    EString* f3c;  // +0x3c
    bool getName(const wchar_t* key, EString* out);
};
struct ResourceKeyW {
  u32 instanceID, typeID, groupID;
  ResourceKeyW() {}
  ResourceKeyW(u32 i, u32 t, u32 g) : instanceID(i), typeID(t), groupID(g) {}
};
struct Prop {                                   // Property
  char pad_00[0x12];
  unsigned short mType;                         // +0x12
  bool* GetBool();                              // 0x0041e920 (thiscall)
  u32* GetUInt();                               // 0x0041ea00 (thiscall)
};
extern const u32 gMsgIds[4];                // 0x01418e40
extern const ResourceKeyW gLayoutKey;       // 0x01545b10
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);  // 0x00f473a0
struct cSPUILayoutR {
    char pad_00[0x18];
    cSPUILayoutR();                                           // 0x00810000
    bool Init(const ResourceKeyW& key, bool b, u32 flags);    // 0x008120d0
    bool SetParentWin(void* win, bool b, u32 flags);          // 0x008121b0
    void SetReloadCallback(void (__cdecl* fn)(void*, void*, bool), void* data); // 0x00810090
};
struct LayoutMgrW {
    void  Activate(u32 id, bool b);           // 0x00810660
    void* GetWorldMainWindow(u32 id);         // 0x00810620
};
LayoutMgrW* GetLayoutManagerW();              // 0x00805070
struct Str16 {
    void* mBegin;   // +0
    void* mEnd;     // +4
    void* mCap;     // +8
    u32   pad;      // +0xc
};
struct cTokBase {
    void* mVt;      // +0
    int   mRef;     // +4
    void  Construct();   // 0x006b5870
    void  Destroy();     // 0x005725a0
};
struct cSPUIMovieRecordUI {
    void*      mVt0;           // +0x00
    void*      mVt1;           // +0x04
    char       pad_08[8];      // +0x08 (base vptr + refcount)
    void*      mLayout;        // +0x10
    void*      mW1;            // +0x14
    void*      mW2;            // +0x18
    void*      mW3;            // +0x1c
    void*      mHandler;       // +0x20
    void*      mHandlerUser;   // +0x24
    const u32* mHandlerIds;    // +0x28
    int        mHandlerCount;  // +0x2c
    int        mHandlerFlags;  // +0x30
    u8         b34;            // +0x34
    bool       b35;            // +0x35
    char       pad_36[2];      // +0x36
    u32        f38, f3c, f40, f44;  // +0x38
    Str16      s48;            // +0x48
    Str16      s58;            // +0x58
    Str16      s68;            // +0x68
    Str16      s78;            // +0x78
    void reload(int arg);      // 0x008178b0
};
static inline void FreeStrW(Str16* s) {
    if ((int)(((u32)s->mCap - (u32)s->mBegin) & 0xfffffffe) > 2 && s->mBegin)
        MemFreeW(s->mBegin);
}
static inline void InitStrW(Str16* s) {
    s->mBegin = (void*)0x1667bac;
    s->mEnd   = (void*)0x1667bac;
    s->mCap   = (void*)0x1667bae;
}
static inline void Vv0c(void* p, int off) {
    void** vt = *(void***)p;
    void (__thiscall* fn)(void*) = (void (__thiscall*)(void*))vt[off / 4];
    fn(p);
}
static inline void Vv2c(void* p, int off, int a, int b) {
    void** vt = *(void***)p;
    void (__thiscall* fn)(void*, int, int) = (void (__thiscall*)(void*, int, int))vt[off / 4];
    fn(p, a, b);
}
static inline char Vb2c(void* p, int off, int a, int b) {
    void** vt = *(void***)p;
    char (__thiscall* fn)(void*, int, int) = (char (__thiscall*)(void*, int, int))vt[off / 4];
    return fn(p, a, b);
}
// ---- items of slice s00816d40 end

// ---- items of slice s00817cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma float_control(precise, off, push)   // fast-math codegen (inline fsqrt, SSE scalar)
struct WStr {                       // eastl::basic_string<wchar_t, eastl::allocator>
    unsigned short* mpBegin;        // +0
    unsigned short* mpEnd;          // +4
    unsigned short* mpCapacity;     // +8
    int             mAllocator;     // +0xc
};
WStr* __cdecl WStr_Format(WStr* s, const wchar_t* fmt, ...);   // 0x0041e050
struct DateTime {
    u32 mLow;
    u32 mHigh;
    void Set(int);                  // 0x0092e3d0
    int  GetParameter(int);         // 0x0092df80
};
struct PieMenuTimeText {
    char  pad_00[0x38];
    void* mp38;                     // +0x38
    void* mp3c;                     // +0x3c
    void* mp40;                     // +0x40
    void* mp44;                     // +0x44
    WStr  m48;                      // +0x48
    WStr  m58;                      // +0x58
    WStr  m68;                      // +0x68
    WStr  m78;                      // +0x78
    void UpdateTimeText();
};
// ---- items of slice s00817cb0 end

// ---- items of slice s0081a790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned wcslen(const wchar_t*);
extern void Mark1();
extern void Mark2();
extern void Mark3();
#pragma intrinsic(wcslen)
struct ItemWinCtor {
  char pad[0x888];
  int mChildIndex;
  void Ctor();
};
// ---- items of slice s0081a790 end

// ---- items of slice s0081c9c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])
struct S962a10 { S962a10* f(); };
struct RenderCtx {
  void* f95bc10(int mode);   // 0x0095bc10 Begin2D
  void  f95bb20();           // 0x0095bb20 End2D
};
namespace UTFWin {
struct cSPUIProgressBarWin {
  void*  mVtbl0;                 // +0x000
  void*  mVtbl4;                 // +0x004
  char   pad00[0x88 - 8];
  float  mX1;                    // +0x088
  float  mY1;                    // +0x08c
  float  mX2;                    // +0x090
  float  mY2;                    // +0x094
  char   pad01[0x20c - 0x98];
  void* volatile mIfaceVtbl20c;  // +0x20c
  int   volatile mUnknown210;    // +0x210
  void* volatile mIfaceVtbl214;  // +0x214
  float  mValue218;              // +0x218
  cSPUIProgressBarWin();
  bool Draw(RenderCtx* ctx);     // 0x0081d5e0
};
}
struct ImgRect { float x, y, w, h; };
struct ImgColor { unsigned r, g, b, a; };
// ---- items of slice s0081c9c0 end

// @ 0x008129c0
void RegisterLayoutCheat()
{
    cSPUILayoutCheat_s0081_24a0* p = new cSPUILayoutCheat_s0081_24a0();
    (void)p;
    SP_CheatManager();
}

// @ 0x00812a10
void Zoom::SetWindow(void* p)
{
    mpMyWindow = p;
    SetStyleWindow((int)p);
}

// @ 0x00812a20
void Zoom::Transform(const float* r, float* out)
{
    out[0] = (r[2] - r[0]) * m24;
    out[2] = (r[2] - r[0]) * m2c;
    out[1] = (r[3] - r[1]) * m28;
    out[3] = (r[3] - r[1]) * m30;
}

// @ 0x00812aa0
bool Zoom::Init(ZoomWin* p)
{
    mpMyWindow = p;
    if (p->z04()) {
        float* r = p->z0d();
        m10 = r[0]; m14 = r[1]; m18 = r[2]; m1c = r[3];
        float* s = p->z04()->z0e();
        float f = s[2] - s[0];
        if (f < 1.0f) f = 1.0f;
        m30 = m10 * (1.0f / f);
        m38 = m18 * (1.0f / f);
        float g = s[3] - s[1];
        if (g < 1.0f) g = 1.0f;
        m34 = m14 * (1.0f / g);
        m3c = m1c * (1.0f / g);
    }
    return false;
}

// @ 0x00812b70
Zoom::Zoom()
{
    *(uint32_t*)((char*)this + 0x4) = 0x13fa72c;
    *(int*)((char*)this + 0x8) = 0;
    *(uint32_t*)((char*)this + 0xc) = 0x14426a0;
    *(uint32_t*)((char*)this + 0x0) = 0x1418518;
    *(uint32_t*)((char*)this + 0x4) = 0x1418500;
    *(uint32_t*)((char*)this + 0xc) = 0x14184e4;
    m10 = m14 = m18 = m1c = 0.0f;
    m20 = m24 = m28 = m2c = 0.0f;
    m30 = m34 = 0.0f;
    m38 = m3c = 1.0f;
    mpMyWindow = 0;
}

// @ 0x00812c90
void __cdecl PostMouseEdgeMsg(void* data)
{
    Canvas* c = SP_Canvas();
    if (c == 0) return;
    if (data == 0) return;
    MsgEnv env;
    env.canvas = c;
    memset(&env.payload, 0, sizeof(env.payload));
    memcpy(env.data, data, 32);
    env.id = 0x1ee1001;
    env.payload = env.data;
    if (SP_MessageServer() != 0) {
        void* s = SP_MessageServer();
        typedef void (__thiscall *MsgPostFn)(void*, uint32_t, void*, int);
        ((MsgPostFn*)(*(void**)s))[0x14 / 4](s, env.id, &env, 0);
    }
}

// @ 0x00812d00
bool __cdecl DispatchMouseMsg(void*, void* p, Q12* q)
{
    if (*(int*)((char*)p + 8) == 6)
        q->q12(0, 0xc0, 0);
    return false;
}

// @ 0x00812d30
void MainWin::Teardown(int)
{
    BaseSetup();
    if (mp260) mp260->w9();
}

// @ 0x00812f70
void __stdcall GetScaledMouse(float* p1, float* p2)
{
    int l1, l2;
    FUN_008d2f30(&l1, &l2);
    Rect4i r;
    Canvas* c = SP_Canvas();
    int* q1 = (int*)c->c15(&r);
    l1 -= q1[0];
    Canvas* c2 = SP_Canvas();
    int* q2 = (int*)c2->c15(&r);
    l2 -= q2[1];
    float fx = (float)l1 * sMouseXScale;
    *(float*)p1 = fx;
    float fy = (float)l2 * sMouseYScale;
    *(float*)p2 = fy;
}

// @ 0x00812ff0
void __stdcall ScreenToClient(float x, float y)
{
    x /= sMouseXScale;
    y /= sMouseYScale;
    Canvas* c = SP_Canvas();
    int ix = (int)x;
    int iy = (int)y;
    c->c31(ix, iy);
}

// @ 0x00813040
void __stdcall ScaleXY(float x, float y, float* px, float* py)
{
    *px = sMouseXScale * x;
    *py = sMouseYScale * y;
}

// @ 0x00813070
float MainWinTimer::GetScaledElapsed()
{
    Stopwatch_s0081_24a0* t = &mTimer;
    return (float)t->GetElapsedTimeFloat() * t->mScale;
}

// @ 0x008130a0
uint64_t AutoRefPair::Get()
{ return *(uint64_t*)&lo; }

// @ 0x00816790
extern "C" void FUN_00816790(IObj* p)
{
    if (!p) return;
    MaterialTarget* o = (MaterialTarget*)Vcp1(p, 0x0c, (void*)0x2f009dd0);
    if (o && o->mat && o->tex)
        SPUIHelpers_SetWindowSPMaterial((void*)o->mat, (void*)*o->tex, o->flag);
}

// @ 0x008167d0
void MatEffect::sub8167d0(IObj* p, float f)
{
    if (f > 0.5f) {
        if (f88 > 0.5f) return;
        p80 = &f70;
    } else if (f < 0.5f) {
        if (f88 < 0.5f) return;
        p80 = &f60;
    } else {
        return;
    }
    void* x = Vcp0(p, 0x14);
    int   y = Vi1(this, 0x0c, 0xee3f516e);
    Vv2(x, 0x1c, 0x816790, y);
    f88 = f;
}

// @ 0x00816860
MatEffect* MatEffect::ctor816860()
{
    ((void(__thiscall*)(void*))0x963db0)(this);   // FadeEffect base ctor
    *(void**)((char*)this + 0x00) = (void*)0x1418d00;
    *(void**)((char*)this + 0x04) = (void*)0x1418ce4;
    *(void**)((char*)this + 0x0c) = (void*)0x1418ca8;
    f60 = f64 = 0x1667bac;
    f68 = 0x1667bae;
    f70 = f74 = 0x1667bac;
    f78 = 0x1667bae;
    p80 = 0;
    b84 = 0;
    f88 = 0.5f;
    return this;
}

// @ 0x00816910
void MatEffect::dtor816910()
{
    *(void**)((char*)this + 0x00) = (void*)0x1418d00;
    *(void**)((char*)this + 0x04) = (void*)0x1418ce4;
    *(void**)((char*)this + 0x0c) = (void*)0x1418ca8;
    if (((int)((f78 - f70) & 0xfffffffe)) > 2 && f70)
        ((void(__cdecl*)(void*))0xf47380)((void*)f70);
    if (((int)((f68 - f60) & 0xfffffffe)) > 2 && f60)
        ((void(__cdecl*)(void*))0xf47380)((void*)f60);
    ((void(__thiscall*)(void*))0x980420)(this);
}

// @ 0x00816a20
void CalloutMessageBox::sub816a20(int, int, int, int)
{
    layout.FindWindowByID(0x6318e78, 1);
    mResult = 0x1510d07;
    void* win = layout.FindWindowByID(0x6318e78, 1);
    void* wm = SP_WindowManager();
    if (win) {
        void* lm = ((void*(__cdecl*)(int))0x805070)(0x5b598f7);
        void* world = ((void*(__thiscall*)(void*))0x810620)(lm);
        if (b5c && Vi0(win, 0x10) == 0)
            Vv1(world, 0xd8, (int)win);
        Vv2(win, 0x7c, 1, 1);
        if (b5c) {
            int a = Vi0(wm, 0x04);
            SPUIHelpers_AnchorWindowToWindow((void*)a, win, 0x300, 0);
        }
        if (!Vi1(wm, 0x80, (int)win))
            SPUIHelpers_BeginModal(win, mpCallback, 0);
    }
}

// @ 0x008175a0
void __stdcall FUN_008175a0(EString* self)
{
    self->Load(0xacb4e314, 0x6329c6c, L"Movie Name (PLACEHOLDER)");
}

// @ 0x008175c0
void MsgBoxB::teardown()
{
    void* p = this ? (void*)((char*)this + 8) : 0;
    void* o = FUN_0067de40();
    o = Vcp0(o, 0x20);
    Vv1(o, 0x20, (int)p);
    if (mLayout) {
        if (mW1) { void* old = mW1; mW1 = 0; Vv0(old, 0x04); }
        if (mW2) { void* old = mW2; mW2 = 0; Vv0(old, 0x04); }
        if (mW3) { void* old = mW3; mW3 = 0; Vv0(old, 0x04); }
        ((cSPUILayout_s0081_6d40*)mLayout)->Shutdown(1);
        if (mLayout) { void* q = mLayout; mLayout = 0; Vv0(q, 0x08); }
    }
    if (mHandler) {
        void* h = mHandler;
        mHandler = 0;
        EA_Messaging_RemoveHandler((int)h, hA, hB, hC, hD);
    }
}

// @ 0x00817670
void MsgBoxC::setVisible(int on)
{
    if ((char)on) {
        if (*(void**)0x15fd918 == 0) goto show;
        {
            void* props = *(void**)0x15fd918;
            char ok = Vb2(props, 0x24, 0x641021a, (int)&on);
            if (ok && Property_GetBool()) b35 = *(u8*)Property_GetBool();
        }
        goto show;
    }
show:
    Vv2(mW1, 0x7c, 1, on);
    Vv2(mW2, 0x7c, 1, on);
    Vv2(mW3, 0x7c, 1, on);
}

// @ 0x00817720
void MsgBoxD::rebind()
{
    void* w = ((cSPUILayout_s0081_6d40*)mLayout)->FindWindowByID(0xffffffff, 1);
    BindWin(&mW1, w, 0);
    if (mW1) Vv1(mW1, 0x104, (int)this);
    w = ((cSPUILayout_s0081_6d40*)mLayout)->FindWindowByID(0x62ef978, 1);
    BindWin(&mW2, w, 0);
    w = ((cSPUILayout_s0081_6d40*)mLayout)->FindWindowByID(0x642d110, 1);
    BindWin(&mW3, w, 0);
}

// @ 0x008177e0
void FUN_008177e0(MsgBoxE* self, void* layout, bool flag)
{
    if (!flag) {
        void* p;
        p = self->mW2; if (p) { self->mW2 = 0; Vv0(p, 0x04); }
        p = self->mW3; if (p) { self->mW3 = 0; Vv0(p, 0x04); }
        if (self->mW1) Vv1(self->mW1, 0x108, (int)self);
    } else {
        ((MsgBoxD*)self)->rebind();
    }
}

// @ 0x00817840
bool MsgBoxF::setMovieState(u32 id)
{
    if (id > 0x62ff413) {
        if (id >= 0x62ff414 && id <= 0x62ff415) {
            b30 = 0;
            ((Helper817670*)((char*)this - 4))->Fn(0);
        }
    } else {
        if (id == 0x62ff413) {
            ((Helper817670*)((char*)this - 4))->Fn(1);
            return true;
        }
        if (id == 0x604c6e0) {
            void* ms = SP_MovieSystem();
            if (ms && Vb0(ms, 0x30))
                Vv0(ms, 0x38);
        }
    }
    return true;
}

// @ 0x008178b0
void cSPUIMovieRecordUI::reload(int arg)
{
    (void)arg;
    void* user = this ? (void*)((char*)this + 4) : 0;
    void* server = MsgServerW();
    mHandler = server;
    mHandlerUser = user;
    mHandlerIds = gMsgIds;
    mHandlerCount = 4;
    mHandlerFlags = 0;
    if (server && user) {
        for (u32 i = 0; i < 0x10; i += 4)
            Vv2c(server, 0x24, (int)user, (int)*(const u32*)((const char*)gMsgIds + i));
    }
    LayoutMgrW* lm = GetLayoutManagerW();
    lm->Activate(0x62efc8c, true);
    void* world = GetLayoutManagerW()->GetWorldMainWindow(0x62efc8c);
    cSPUILayoutR* lay = new ("UI/cSPUIMovieRecordUI", 0, 0, 0, 0) cSPUILayoutR();
    void* old = mLayout;
    if (lay != old) {
        if (lay) Vv0c(lay, 0x04);
        mLayout = lay;
        if (old) Vv0c(old, 0x08);
    }
    ((cSPUILayoutR*)mLayout)->Init(gLayoutKey, false, 0x5b598fa);
    ((cSPUILayoutR*)mLayout)->SetParentWin(world, true, 0x5b598fa);
    ((cSPUILayoutR*)mLayout)->SetReloadCallback((void (__cdecl*)(void*, void*, bool))FUN_008177e0, this);
    ((MsgBoxD*)this)->rebind();
    Vv2c(mW1, 0x7c, 1, 0);
    Vv2c(mW2, 0x7c, 1, 0);
    Vv2c(mW3, 0x7c, 1, 0);
    b34 = 0;
    b35 = 1;
    void* props = *(void**)0x15fd918;
    if (props) {
        Prop* pr;
        if (Vb2c(props, 0x24, 0x641021a, (int)&pr) && pr->mType == 1)
            b35 = *pr->GetBool();
    }
    void* base8 = (char*)this + 8;
    void* o = FUN_0067de40();
    o = Vcp0(o, 0x20);
    Vv1(o, 0x1c, (int)base8);
}

// @ 0x00817a40
cSPUIMovieRecordUI* __fastcall FUN_00817a40raw(cSPUIMovieRecordUI* p)
{
    void** slot = (void**)((char*)p + 0x10);
    *(void**)0x164d858 = (void*)slot;
    p->mVt0 = (void*)0x14426a0;
    p->mVt1 = (void*)0x13eb394;
    cTokBase& base = *(cTokBase*)((char*)p + 8);
    base.Construct();
    p->mVt0 = (void*)0x1418e70;
    p->mVt1 = (void*)0x1418e68;
    base.mVt = (void*)0x1418e50;
    *slot = 0;
    p->mW1 = 0;
    p->mW2 = 0;
    p->mW3 = 0;
    p->mHandler = 0;
    p->mHandlerUser = 0;
    p->mHandlerIds = 0;
    p->mHandlerCount = 0;
    p->mHandlerFlags = 0;
    p->b34 = 0;
    p->f38 = 0;
    p->f3c = 0;
    p->f40 = 0;
    p->f44 = 0;
    p->b35 = 1;
    InitStrW(&p->s48);
    InitStrW(&p->s58);
    InitStrW(&p->s68);
    InitStrW(&p->s78);
    return p;
}

// @ 0x00817b00
void __fastcall FUN_00817b00raw(cSPUIMovieRecordUI* p)
{
    cTokBase& base = *(cTokBase*)((char*)p + 8);
    p->mVt0 = (void*)0x1418e70;
    p->mVt1 = (void*)0x1418e68;
    base.mVt = (void*)0x1418e50;
    FreeStrW(&p->s78);
    FreeStrW(&p->s68);
    FreeStrW(&p->s58);
    FreeStrW(&p->s48);
    if (p->mHandler) {
        void* h = p->mHandler;
        p->mHandler = 0;
        EA_Messaging_RemoveHandler((int)h, (int)p->mHandlerUser, (int)p->mHandlerIds,
                                   p->mHandlerCount, p->mHandlerFlags);
    }
    if (p->mW3) Vv0(p->mW3, 0x04);
    if (p->mW2) Vv0(p->mW2, 0x04);
    if (p->mW1) Vv0(p->mW1, 0x04);
    if (p->mLayout) Vv0(p->mLayout, 0x08);
    base.Destroy();
    p->mVt1 = (void*)0x13eb394;
    p->mVt0 = (void*)0x13eb938;
    *(void**)0x164d858 = 0;
}

// @ 0x00817c40
bool CellNameSrc::getName(const wchar_t* key, EString* out)
{
    u32 h = FNV1_String16(key, 0x811c9dc5, 1);
    EString* m;
    if (h > 0xb148e703) {
        if (h != 0xce645bea) return false;
        m = f34;
    } else {
        if (h == 0xb148e703) m = f30;
        else if (h == 0x6933bb85) m = f38;
        else if (h != 0xae892933) return false;
        else m = f3c;
    }
    if (!m) return false;
    *out = *m;
    return true;
}

// @ 0x00817cb0
void PieMenuTimeText::UpdateTimeText()
{
    DateTime now;
    now.Set(2);
    WStr_Format(&m48, L"%04u", now.GetParameter(1));
    mp38 = m48.mpBegin;
    WStr_Format(&m58, L"%02u", now.GetParameter(2));
    mp3c = m58.mpBegin;
    WStr_Format(&m68, L"%02u", now.GetParameter(6));
    mp40 = m68.mpBegin;
    WStr_Format(&m78, L"%02u-%02u-%02u",
                now.GetParameter(8), now.GetParameter(9), now.GetParameter(10));
    mp44 = m78.mpBegin;
}

// @ 0x0081aa00
void ItemWinCtor::Ctor()
{
  *(void**)this = (void*)&Mark1;
  *(void**)((char*)this + 4) = (void*)&Mark2;
  *(void**)((char*)this + 0x20c) = (void*)&Mark3;
  mChildIndex = -1;
}

// @ 0x0081d510
UTFWin::cSPUIProgressBarWin::cSPUIProgressBarWin()
{
  ((S962a10*)this)->f();
  mIfaceVtbl20c = (void*)0x13ec458;
  mUnknown210 = 0;
  mIfaceVtbl214 = (void*)0x140af70;
  mVtbl0 = (void*)0x1419c70;
  mVtbl4 = (void*)0x1419b50;
  mIfaceVtbl20c = (void*)0x1419b3c;
  mIfaceVtbl214 = (void*)0x1419b34;
  mValue218 = 100.0f;
}

// @ 0x0081d5e0
bool UTFWin::cSPUIProgressBarWin::Draw(RenderCtx* ctx)
{
  void* batch = ctx->f95bc10(0);
  void* obj = ((void* (__thiscall*)(void*))VTSLOT((char*)this + 4, 0xa8))((char*)this + 4);
  if (obj != 0) {
    void* fn = VTSLOT(obj, 0x10);
    ImgRect rect = {0.0f, 0.0f, (mX2 - mX1) * mValue218 * 0.01f, mY2 - mY1};
    ImgColor color = {0, 0, 0, 0xffffffff};
    ((void (__thiscall*)(void*, RenderCtx*, ImgRect*, ImgColor*))fn)(
        obj, ctx, &rect, &color);
  } else {
    void* fn = VTSLOT(batch, 0x38);
    ((void (__thiscall*)(void*, float, float, float, float))fn)(
        batch, 0.0f, 0.0f, mX2 - mX1, mY2 - mY1);
  }
  ctx->f95bb20();
  return true;
}
