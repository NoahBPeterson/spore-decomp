// src/game/SPGonzago/SPUIPosse.cpp -- migrated from slice(s) s00e255c0, s00e25460, s00e253c0, s00e25240, s00e24f10, s00e24d10, s00e24a50, s00e25710, s00fc7430, s00e27310, s00e26680, s00e24700, s00e23710, s00e22860, s00e21880, s00e20860 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIPosse.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" void FUN_00e22760();
extern "C" char g_1480788[];
extern "C" char g_1480798[];
extern "C" char g_14807b0[];
extern "C" char g_1480894[];
extern "C" char g_14808a4[];
extern "C" char g_14808c0[];
extern "C" char g_14809a4[];
extern "C" char g_14809b4[];
extern "C" char g_14809d0[];
extern "C" char g_1480ab4[];
extern "C" char g_1480ac4[];
extern "C" char g_1480ae0[];
extern "C" char g_1480bc4[];
extern "C" char g_1480bd4[];
extern "C" char g_1480bf0[];
extern "C" char g_1480cd4[];
extern "C" char g_1480ce4[];
extern "C" char g_1480d00[];
extern "C" char g_1480de4[];
extern "C" char g_1480df4[];
extern "C" char g_1480e10[];
extern "C" char g_15a5524[];
extern "C" char g_16ac2c8[];

#include "game/types.h"
#include "sse_helpers.h"
#include "cSPUILayout.h"
#include <math.h>
#include "cSPUIAnimator.h"
#include <intrin.h>
#include "EA/Variant.h"
#include "EA/UTFWin/RenderContext.h"

// ---- items of slice s00e20860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float DAT_013ec4d0;                               // 1.0f clamp
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;
void* __cdecl FUN_00b3d350();        // 0x00b3d350 SP::PlanetModel()
struct PlanetModel_s00e2_17c0 {
  int FUN_00b88590(const void* pPos);   // 0x00b88590 SP::cPlanetModel::GetContinent (thiscall, ret 4)
};
struct PosSource_s00e2_17c0 {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10();
  virtual const void* GetPosition();    // +0x2c
};
void  __cdecl FUN_00881ea0(double, void*, int, const wchar_t*); // 0x00881ea0 SetNumberString
void* __cdecl FUN_008061c0(void*, int); // 0x008061c0 SPUIHelpers::GetImageFromLayout
u32   __cdecl FUN_007f5eb0(u32, u32, float); // 0x007f5eb0 Color::Lerp
void  __cdecl FUN_00808210(void*, float);    // 0x00808210 SetWindowScale
class cSPUIPosseItem;
struct VObj1 { void** vtbl; };
class cSPUIPosseItem2 {
public:
  void**  vtbl;                 // +0x00
  u8      pad04[0x94 - 0x04];
  s32     mState;               // +0x94 (retail; PDB 0x98)
  u8      pad98[0xa8 - 0x98];
  s32     mDistress[3];         // +0xa8 (retail; PDB 0xac)
  u8      padb4[0xb8 - 0xb4];
  u32     mBlinkerColorFrom;    // +0xb8 (retail; PDB 0xc0)
  u32     mBlinkerColorTo;      // +0xbc
  float   mBlinkerScaleFrom;    // +0xc0
  float   mBlinkerScaleTo;      // +0xc4
};
// ---- items of slice s00e20860 end

// ---- items of slice s00e21880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;                                   // 0x01485720
extern const double kTwo;                                  // 0x013f1298
extern const double kHalf;                                 // 0x0140c4f0
extern const float kNegOne;                                // 0x013eb1bc
struct ResourceKey {
    uint32_t mInstanceID;                                   // +0x00
    uint32_t mGroupID;                                      // +0x04
    uint32_t mTypeID;                                       // +0x08
};
struct IWindow;
struct IWindow {
    virtual void      v000();                               // +0x00
    virtual void      v004();                               // +0x04
    virtual void      v008();                               // +0x08
    virtual void*     Cast(uint32_t nType);                 // +0x0c
    virtual IWindow*  GetParent();                          // +0x10
    virtual void      v014();
    virtual void      v018();
    virtual uint32_t  GetTypeID();                          // +0x1c
    virtual uint32_t  GetFlags();                           // +0x20
    virtual void      v024();
    virtual void      v028(int32_t nSlot, void* pValue);    // +0x28
    virtual void      v02c();
    virtual void      v030();
    virtual void      v034();
    virtual float*    GetRect();                            // +0x38
    virtual void      v03c();
    virtual void      v040();
    virtual IWindow*  v044(const float* pPoint);            // +0x44
    virtual void      v048();
    virtual void      v04c();
    virtual void      v050();
    virtual IWindow*  v054(bool bUnknown);                  // +0x54
    virtual void      v058(bool bArg1, bool bArg2);         // +0x58
    virtual void      v05c();
    virtual void      v060();
    virtual void      v064();
    virtual void      v068();
    virtual void      v06c();
    virtual void      v070(float fX, float fY);             // +0x70
    virtual void      v074(float fWidth, float fHeight);    // +0x74
    virtual void      v078();
    virtual void      v07c(bool bArg1, bool bArg2);         // +0x7c
    virtual void      v080(const char* pText);              // +0x80
    virtual void      v084();
    virtual void      v088();
    virtual int32_t   v08c();                               // +0x8c
    virtual void      v090();
    virtual void      v094();
    virtual void      v098();
    virtual void      v09c();
    virtual void      v0a0(void (*pfnCallback)(), void* pArg);  // +0xa0
    virtual void      v0a4();
    virtual void      v0a8();
    virtual void      v0ac();
    virtual void      v0b0();
    virtual bool      v0b4();                               // +0xb4
    virtual void      v0b8(IWindow* pArg1, IWindow* pArg2); // +0xb8
    virtual void      v0bc();
    virtual float*    v0c0(const float* pPoint);            // +0xc0
    virtual IWindow*  v0c4();                               // +0xc4
    virtual void      v0c8();
    virtual void      v0cc();
    virtual void      v0d0();
    virtual void      v0d4();
    virtual void      v0d8();
    virtual void      v0dc(void* pArg);                     // +0xdc
    virtual void      v0e0();
    virtual void      v0e4();
    virtual void      v0e8(IWindow* pWindow);               // +0xe8
    virtual void      v0ec();
    virtual IWindow*  FindWindowByID(uint32_t nID, bool bRecursive);   // +0xf0
    virtual void      v0f4();
    virtual void      v0f8();
    virtual void      v0fc();
    virtual void      v100();
    virtual void      v104();
    virtual void      v108(void* pArg);                     // +0x108
};
struct cHitWindow {
    virtual void         v000();
    virtual void         v004();
    virtual void         v008();
    virtual cHitWindow*  Cast(uint32_t nType);              // +0x0c
    virtual void         v010();
    virtual void         v014();
    virtual void         v018();
    virtual uint32_t     GetTypeID();                       // +0x1c
    virtual void         v020();
    virtual void         v024();
    virtual void         v028();
    virtual void         v02c();
    virtual void         v030();
    virtual void         v034();
    virtual void         v038();
    virtual void         v03c();
    virtual void         v040();
    virtual void         v044();
    virtual void         v048();
    virtual void         v04c();
    virtual void         v050();
    virtual void         v054();
    virtual void         v058();
    virtual void         v05c();
    virtual void         v060();
    virtual void         v064();
    virtual void         v068();
    virtual void         v06c();
    virtual void         v070();
    virtual void         v074();
    virtual void         v078();
    virtual void         v07c();
    virtual void         v080();
    virtual void         v084();
    virtual void         v088();
    virtual void         v08c();
    virtual void         v090();
    virtual void         v094();
    virtual void         v098();
    virtual void         v09c();
    virtual void         v0a0();
    virtual void         v0a4();
    virtual void         v0a8();
    virtual void         v0ac();
    virtual void         v0b0();
    virtual cHitWindow*  GetNamedWindow(uint32_t nID);      // +0xb4
    virtual void         SetMotive(int32_t nMotive);        // +0xb8
};
struct cSPUILayout_s00e2_1880 {
    IWindow* FindWindowByID(uint32_t nID, bool bRecursive) const;   // 0x008105b0
    void     Shutdown(uint32_t nFlags);                             // 0x00811ad0

    char     mPad000[0x18];
};
struct cUIContext {
    char      mPad000[0x10];
    IWindow*  mpWindow10;                                   // +0x10
};
struct cUIMessage {
    char       mPad000[8];                                  // +0x00
    IWindow*   mpSender;                                    // +0x08
    char       mPad00c[4];                                  // +0x0c
    uint32_t   mValue;                                      // +0x10
};
struct cItemMessageHandler {
    virtual void v000();                                    // +0x00
    virtual void v004();
    virtual void v008();

    bool HandleMessage(uint32_t nMessageID, cUIMessage* pMessage);
};
struct cSPUIPosseItem_s00e2_1880 {
    // vtable slots used by this slice
    virtual void      v000();                               // +0x00
    virtual void      v004();                               // +0x04
    virtual void      v008();                               // +0x08
    virtual void      v00c();
    virtual void      v010();
    virtual void      v014();
    virtual void      v018();
    virtual void      v01c();
    virtual void      v020();
    virtual void      v024();
    virtual void      v028();
    virtual void      v02c();
    virtual void      v030();
    virtual void      v034();
    virtual void      v038();
    virtual void      v03c();
    virtual void      v040();
    virtual void      v044();
    virtual void      v048();
    virtual void      v04c();
    virtual void      v050();
    virtual void      v054();
    virtual void      v058();
    virtual void      v05c();
    virtual void      v060();
    virtual void      v064();
    virtual void      v068();
    virtual void      v06c();
    virtual void      v070();
    virtual void      v074();
    virtual void      v078();
    virtual void      v07c();
    virtual void      v080();
    virtual void      v084();
    virtual void      v088();
    virtual int32_t   v08c();                               // +0x8c
    virtual void      v090();
    virtual void      v094();
    virtual void      v098();
    virtual void      v09c();
    virtual void      v0a0();
    virtual void      v0a4();
    virtual void      v0a8();
    virtual void      v0ac();
    virtual void      v0b0();
    virtual bool      v0b4();                               // +0xb4
    virtual void      v0b8(int32_t nValue);                 // +0xb8
    virtual void      v0bc();
    virtual void      v0c0();
    virtual IWindow*  v0c4();                               // +0xc4
    virtual void      v0c8();
    virtual void      v0cc();
    virtual void      v0d0();
    virtual uint32_t  v0d4(int32_t nIndex);                 // +0xd4
    virtual int32_t   v0d8();                               // +0xd8
    virtual void      v0dc(int32_t* pOut);                  // +0xdc
    virtual void      v0e0();
    virtual void      v0e4();
    virtual void      v0e8();
    virtual void      v0ec();
    virtual void      v0f0();
    virtual void      v0f4();
    virtual void      v0f8();
    virtual void      v0fc();
    virtual void      v100();
    virtual void      v104();
    virtual void      v108(void* pArg);                     // +0x108

    char              mPad004[8];                           // +0x004 .. +0x00b
    cItemMessageHandler mHandler;                           // +0x00c
    float             mRect10[4];                           // +0x010 (background 0x56cec38)
    float             mRect20[4];                           // +0x020 (bars 0x56bd170)
    float             mRect30[4];                           // +0x030 (motive 0)
    float             mRect40[4];                           // +0x040 (motive 1)
    IWindow*          mpField50;                            // +0x050
    char              mPad054[0xc];                         // +0x054 .. +0x05f
    ResourceKey       mIconKey;                             // +0x060 (task icon resource key)
    uint32_t          mTaskIconID;                          // +0x06c
    ResourceKey       mItemKey;                             // +0x070 (item icon resource key)
    cSPUILayout_s00e2_1880       mLayout;                              // +0x07c
    uint32_t          mField94;                             // +0x094 (motive kind)
    void*             mpField98;                            // +0x098
    IWindow*          mpField9c;                            // +0x09c
    uint8_t           mFieldA0;                             // +0x0a0
    uint8_t           mFieldA1;                             // +0x0a1
    uint8_t           mFieldA2;                             // +0x0a2
    uint8_t           mFieldA3;                             // +0x0a3
    uint32_t          mFieldA4;                             // +0x0a4
    int32_t           mFieldA8[4];                          // +0x0a8
    char              mPad0B8[0x1c];                        // +0x0b8 .. +0x0d3
    cUIContext*       mpFieldD4;                            // +0x0d4
    char              mPad0D8[0x64];                        // +0x0d8 .. +0x13b
    IWindow*          mpField13c;                           // +0x13c

    void SetSomething(void* pField);                        // 0x00e21ba0
    void SetTaskKey(const ResourceKey* pKey, int32_t nFlags);   // 0x00e21bd0
    void SetTaskIcon(uint32_t nTaskIconID, void* pImage, int32_t nFlags);  // 0x00e21c40
    void SetBlinkerMotiveVisible(bool bShow);               // 0x00e21ca0
    void SetBlinkerMotive(int32_t nMotive, char bForce);    // 0x00e21cf0
    void SetItemKeyIcon(const ResourceKey* pKey, int32_t nUnused);    // 0x00e21e50
    void SetItemIcon(void* pImage, int32_t nUnused);        // 0x00e21ea0
    void AttachToParent();                                  // 0x00e21ee0
    void MotiveBarsAndBackgroundReposition(bool bShow);     // 0x00e21f30
    void MotiveBarsAndBackgroundCollectInitialMetrics();    // 0x00e22270
    char Shutdown();                                        // 0x00e22370
    bool OnMouseUp(IWindow* pWindow, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00e22420
    bool OnMouseMove(IWindow* pWindow, float fX, float fY, uint32_t nFlags);            // 0x00e22470
    bool OnFocusChange(uint32_t nArg1, int32_t nReason, IWindow* pWindow);              // 0x00e22550
    void SetFrameCallback();                                // 0x00e22740
    void OnMotiveValueChanged(uint32_t nValue);             // 0x00e215d0
};
struct cPosseItemEntry;
struct cSPUIPosseSortable {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
virtual void v080();
virtual void v084();
virtual void v088();
    virtual int32_t  v08c();                                // +0x8c (sort key)
virtual void v090();
virtual void v094();
virtual void v098();
virtual void v09c();
virtual void v0a0();
virtual void v0a4();
virtual void v0a8();
virtual void v0ac();
virtual void v0b0();
virtual void v0b4();
virtual void v0b8();
virtual void v0bc();
    virtual void v0c0();
    virtual IWindow* v0c4();                                // +0xc4 (content window)
};
struct cSPUIPosse {
    char             mPad000[0xa4];                         // +0x000 .. +0x0a3
    cPosseItemEntry* mpItemsA4;                             // +0x0a4 (first item)
    cPosseItemEntry* mpItemsA8;                             // +0x0a8 (past last item)
    char             mPad0AC[0x90];                         // +0x0ac .. +0x13b
    IWindow*         mpField13c;                            // +0x13c
    char             mPad140[0x7c];                         // +0x140 .. +0x1bb
    cSPUILayout_s00e2_1880      mLayout;                               // +0x1bc
    uint8_t     mField1d4;                                  // +0x1d4
    char        mPad1d5[3];                                 // +0x1d5 .. +0x1d7
    float       mField1d8;                                  // +0x1d8
    float       mField1dc;                                  // +0x1dc
    char        mPad1e0[0xc];                               // +0x1e0 .. +0x1eb
    uint8_t     mField1ec;                                  // +0x1ec

    void SetCaptionIcon(void* pImage);                      // 0x00e21880
    void SetItemIcon(void* pImage);                         // 0x00e218b0
    void SetPosseMemberCount(float fCount);                 // 0x00e218e0
    void ForEachItem(bool (*pfnCallback)(void*, void*), void* pContext);   // 0x00e227f0
    void SetPlacement(float fX, float fY, int32_t nUnused, bool bVisible); // 0x00e22830
    static bool CompareWith(cSPUIPosseSortable* pA, cSPUIPosseSortable* pB);   // 0x00e22760
    bool GetItemFlag();                                     // 0x00e226c0
    void SetItemFlag(void* pValue);                         // 0x00e22700
};
struct cPosseItemEntry {
    uint32_t         mIndex;                                // +0x00
    cSPUIPosseItem_s00e2_1880*  mpItem;                                // +0x04
};
struct cNamedItem;
struct cWindowManager {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
    virtual void v040();
    virtual IWindow* v044(const float* pPoint);             // +0x44
virtual void v048();
virtual void v04c();
virtual void v050();
    virtual IWindow* v054(bool bArg);                       // +0x54
    virtual void v058(bool bArg1, bool bArg2);              // +0x58
};
struct cMessageServer {
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
    virtual void PostMessage(void* pTarget, uint32_t nMessageID, int32_t nValue);   // +0x2c
};
namespace SPUIHelpers {
    char __cdecl SetWindowImage(IWindow* pWindow, const void* pImage, int32_t nFlags);   // 0x00807bb0
}
namespace UI {
    char __cdecl SetWindowImage(IWindow* pWindow, const void* pImage, int32_t nFlags);   // 0x008068d0
}
namespace EA {
namespace Locale {
    void __cdecl SetNumberString(double fValue, char* pBuffer, int32_t nBufferSize, const wchar_t* pFormat);   // 0x00881ea0
}
}
namespace SP {
    cWindowManager* __cdecl WindowManager();                // 0x0067caa0
}
cMessageServer* __cdecl MessageServer_s00e2_1880();                   // 0x0067dcc0
uint32_t        __cdecl GetModifierState();                // 0x008d2db0
bool            __cdecl Contains(const uint32_t* pContainer, const uint32_t* pValue);   // 0x00805150
float*          __cdecl GetBoundingScreenRect(float* pOut, IWindow* pWindow, char bArg);   // 0x00808d20
void            __cdecl AnchorWindowToWindow(IWindow* pParent, IWindow* pChild, int32_t nFlags, int32_t nArg);  // 0x00807340
void            __cdecl SPUIFrameCallbackA();              // 0x00e21700
bool            __cdecl FUN_00e217c0(cNamedItem* pA, cNamedItem* pB);           // 0x00e217c0
// ---- items of slice s00e21880 end

// ---- items of slice s00e22860 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cVec3 {
    float x;                       // 0x00
    float y;                       // 0x04
    float z;                       // 0x08
};
struct cVec2 {
    cVec2() {}
    cVec2(float ax, float ay) : x(ax), y(ay) {}
    cVec2(const cVec2& other) : x(other.x), y(other.y) {}
    float x;                       // 0x00
    float y;                       // 0x04
};
struct cVec4 {
    float x;                       // 0x00
    float y;                       // 0x04
    float z;                       // 0x08
    float w;                       // 0x0c
};
struct cSPUIWindow;
struct cSPUILayout_s00e2_2860 {
    u8           mPad0000[0x18];
    cSPUIWindow* FindWindowByID(int windowID, int recurse);   // 0x008105b0
};
struct cSPUIAnimator_s00e2_2860 {
    void Update();                 // 0x007f63b0
};
struct cAudioObject;
struct cAnimatorFrame {
    int mFirst;                    // 0x00
    int mSecond;                   // 0x04
};
struct cAudioEntry {
    int            mField0;        // 0x00
    cAudioObject*  mpObject4;      // 0x04
};
struct cPossePart {
    u8    mPad0000[0x10];
    void* mpField10;               // 0x10
};
cVec4* __cdecl GetMainWindowArea(cVec4* out);                // 0x00805ea0
char   __cdecl SetWindowImage(void* window, const void* rect, int mode);   // 0x00807bb0
void   __cdecl BuildAnimatorRect(void* a, void* b);          // 0x00804ed0
static inline int VT_1C_0(void* p)
{
    return ((int (__thiscall*)(void*))(*(void***)p)[0x07])(p);
}
static inline cVec4* VT_38_0(void* p)
{
    return ((cVec4* (__thiscall*)(void*))(*(void***)p)[0x0e])(p);
}
static inline void* VT_0C_1(void* p, int a)
{
    return ((void* (__thiscall*)(void*, int))(*(void***)p)[0x03])(p, a);
}
static inline void VT_14_1(void* p, int a)
{
    ((void (__thiscall*)(void*, int))(*(void***)p)[0x05])(p, a);
}
static inline void* VT_F0_2(void* p, int a, int b)
{
    return ((void* (__thiscall*)(void*, int, int))(*(void***)p)[0x3c])(p, a, b);
}
static inline float VT_C0_0(void* p)
{
    return ((float (__thiscall*)(void*))(*(void***)p)[0x30])(p);
}
static inline void VT_6C_1(void* p, const cVec4* v)
{
    ((void (__thiscall*)(void*, const cVec4*))(*(void***)p)[0x1b])(p, v);
}
static inline void VT_70_2F(void* p, float a, float b)
{
    ((void (__thiscall*)(void*, float, float))(*(void***)p)[0x1c])(p, a, b);
}
static inline void VT_7C_2(void* p, int a, int b)
{
    ((void (__thiscall*)(void*, int, int))(*(void***)p)[0x1f])(p, a, b);
}
static inline const int& max_i(const int& a, const int& b)
{
    return (a < b) ? b : a;
}
static inline const int& min_i(const int& a, const int& b)
{
    return (a > b) ? b : a;
}
static inline float fmax_v(float a, float b)
{
    return (a > b) ? a : b;
}
static inline float fmin_v(float a, float b)
{
    return (a < b) ? a : b;
}
static inline char VT_28_0(void* p)
{
    return ((char (__thiscall*)(void*))(*(void***)p)[0x0a])(p);
}
#define VT_C0_2(p, out, v) \
    ((void (__thiscall*)(void*, cVec2*, cVec2))(*(void***)(p))[0x30])((p), (out), (v))
struct cSPUIPosse_s00e2_2860 {
    u8            mPad0000[0xc];
    void**        mpItemBegin0c;           // 0xc  (item pointer array)
    void**        mpItemEnd10;             // 0x10
    u8            mPad0014[0x50 - 0x14];
    void*         mpField50;               // 0x50
    u8            mPad0054[0x60 - 0x54];
    int           mField60;                // 0x60
    u8            mPad0064[0x6c - 0x64];
    int           mField6c;                // 0x6c
    cVec3         mRect70;                 // 0x70
    cSPUILayout_s00e2_2860   mLayout7c;               // 0x7c
    u8            mPad0094[0xa4 - 0x94];
    cAudioEntry*  mpAudioBeginA4;          // 0xa4
    cAudioEntry*  mpAudioEndA8;            // 0xa8
    u8            mPad00ac[0xd4 - 0xac];
    cPossePart*   mpPartD4;                // 0xd4
    u8            mPad00d8[0x1bc - 0xd8];
    cSPUILayout_s00e2_2860   mLayout1bc;              // 0x1bc
    u8            mFlag1d4;                // 0x1d4
    u8            mPad01d5[0x1d8 - 0x1d5];
    float         mField1d8;               // 0x1d8
    float         mField1dc;               // 0x1dc
    int           mField1e0;               // 0x1e0
    u8            mFlag1e4;                // 0x1e4
    u8            mFlag1e5;                // 0x1e5
    u8            mPad01e6[0x1e8 - 0x1e6];
    float         mField1e8;               // 0x1e8
    u8            mFlag1ec;                // 0x1ec
    u8            mPad01ed[0x208 - 0x1ed];
    cSPUIAnimator_s00e2_2860* mpAnimator208;          // 0x208

    void  UpdateLayout(bool bSnap);        // 0x00e22b50
    void  SetToolWindowState(int a, int b);// 0x00e21bd0
    void  RefreshToolWindow(int a);        // 0x00e21ca0

    cVec4 GetWindowBounds();               // 0x00e22860
    void  SnapToPosition();                // 0x00e22a60
    void  SetScaleF(float scale);          // 0x00e23130
    bool  SetVisibility(void* window);     // 0x00e231a0
    void  SetScale(int scale);             // 0x00e23200
    int   GetAudioCount();                 // 0x00e23250
    void  SetWindowImages(void* image);    // 0x00e235e0
    int   GetWindowImageCount();           // 0x00e23670
    void  GetWindowImageRange(int* out);   // 0x00e23680
    void  ClearToolWindow(int a, int b);   // 0x00e236a0
    void  ClearToolWindowOne(int a);       // 0x00e236b0
    void  SetWindowRect(const cVec3* rect, int unused);   // 0x00e236c0
};
// ---- items of slice s00e22860 end

// ---- items of slice s00e23710 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* DAT_016ac278;
typedef void   (__thiscall *TFv)(void*);
typedef void   (__thiscall *TFvi)(void*, int);
typedef void   (__thiscall *TFvp)(void*, void*);
typedef s32    (__thiscall *TFi)(void*);
typedef u32    (__thiscall *TFu)(void*);
typedef u8     (__thiscall *TFb)(void*);
typedef void*  (__thiscall *TFpii)(void*, u32, void*);
typedef u8     (__thiscall *TFuii)(void*, u32, void**);
typedef void*  (__thiscall *TFpp)(void*, void**);   // FUN_00e23e80(ecx, pair*)
typedef void   (__thiscall *TFvpp)(void*, void*, int);
u32    __cdecl FUN_008d2db0(void);                 // 0x008d2db0 GetModifierState
void   __cdecl FUN_00f47380(void* p);              // 0x00f47380 operator_delete_array
struct SPUILayoutC {
  void* FindWindowByID(u32 id, int b);
  u8 Init(u32 key, int a, u32 b);
  u8 InitStr(void* name, int a, int b, u32 c);
};  // modeled thiscall targets (0x008105b0 / 0x008120d0 / 0x00812160)
struct SPUIPosseC { void SelectAll(u32 a); };                // modeled thiscall target (FUN_00e22b50)
struct CopyImplC { void Copy(void* src); };                 // modeled thiscall target (FUN_006237d0, ecx=0x15a5524)
struct Vec2bC { void Free(); };                             // modeled thiscall target (FUN_008e2b20)
struct LayoutDtorC { void Dtor(); };                        // modeled thiscall target (FUN_00811fe0)
struct PosseItemC { void SetBlinkerMotive(u32 a, u8 b); };  // modeled thiscall target (FUN_00e21cf0)
void*  __cdecl FUN_0067de30(void);                 // 0x0067de30 SP::PropertyManager
float  __cdecl FUN_00805080_f(void);               // 0x00805080 SPUIHelpers::GetElapsedSeconds (float ret)
void*  __cdecl FUN_00e23250(void);                 // 0x00e23250 EA::Audio::GetSystem
void*  __cdecl FUN_00a206f0(void);                 // 0x00a206f0 EA::Audio::GetSystemAT
void   __cdecl FUN_00e21700(void);                 // 0x00e21700
void   __cdecl FUN_00e21720(void);                 // 0x00e21720
typedef void* Ref;
// ---- items of slice s00e23710 end

// ---- items of slice s00e24700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* vtbl_BehaviorMessageBase[];                   // 0x013eb90c
extern void* vtbl_BehaviorMessage[];                       // 0x013eb844
extern float g_clickThreshold;                             // 0x01480568 (0.25f)
extern void* g_pMsgRef;                                    // 0x016ac278 (pending message)
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
struct Msg40 {
  void*    vptr;                                            // +0x00
  long     refcount;                                        // +0x04
  uint32_t mData[10];                                       // +0x08 .. +0x2f
  uint32_t mId;                                             // +0x30
  uint32_t mPad34;                                          // +0x34
  uint32_t mRCFlags;                                        // +0x38
  uint32_t mPad3c;                                          // +0x3c
  Msg40(uint32_t id) : mId(id) {
    vptr = vtbl_BehaviorMessageBase;
    _InterlockedExchange(&refcount, 0);
    vptr = vtbl_BehaviorMessage;
    mRCFlags = 0;
  }
  void AddRef()  { ((void(__thiscall*)(Msg40*))((void**)vptr)[1])(this); }
  void Release() { ((void(__thiscall*)(Msg40*))((void**)vptr)[2])(this); }
  void SetIRefCount(int idx, uint32_t p);                   // 0x005726e0 (ret 8)
};
struct MsgServer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
  virtual void MessageSend(uint32_t id, void* msg, int a, int b);   // +0x18
};
MsgServer* MessageServer();                                 // 0x0067dcc0
struct Vtbl { void (*slot[128])(); };
typedef void (__thiscall* FnVoidI)(void*, int);
typedef int  (__thiscall* FnInt0)(void*);
struct MsgIn { uint8_t mPad00[8]; int mField08; int mField0c; };
struct cSPUIPosseItem_s00e2_4700 {
  Vtbl*   mpVtable;                                         // +0x00
  uint8_t mPad004[0x4c];
  void*   mField50;                                         // +0x50
  uint8_t mPad054[0x40];
  int     mField94;                                         // +0x94
  void FUN_00950ef0(int, MsgIn*);                           // 0x00950ef0

  void FUN_00e24700(int state);
  void FUN_00e247f0(int param_2, MsgIn* param_3);
};
struct cSPUILayout_s00e2_4700 {
  uint8_t mData[0x200];
  void* FindWindowByID(uint32_t id, uint32_t flags);       // 0x008105b0
  void  Shutdown(uint32_t mode);                            // 0x00811ad0
};
struct ItemNode {
  void* mField00;       // +0x00
  void* mField04;       // +0x04
};
void FUN_00e24d10(uint32_t id, void* ctx);                 // 0x00e24d10 (cdecl)
float GetElapsedSeconds();                                 // 0x00805080 (SPUIHelpers, cdecl)
typedef void     (__thiscall* FnVoid0)(void*);
typedef void     (__thiscall* FnVoidII)(void*, int, int);
typedef uint32_t (__thiscall* FnU32_0)(void*);
struct WindowMgr { Vtbl* mpVtable;  /* +0x00 */ };
WindowMgr* WindowManager_s00e2_4700();                                // 0x0067caa0
struct cSPUIPosse_s00e2_4700 {
  Vtbl*    mpVtable;                                        // +0x00
  uint8_t  mPad004[0x4c];                                   // +0x04 .. +0x4f
  void*    mField50;                                        // +0x50
  uint8_t  mPad054[0x40];                                   // +0x54 .. +0x93
  int      mField94;                                        // +0x94
  uint8_t  mPad098[0x09];                                   // +0x98 .. +0xa0
  uint8_t  mFieldA1;                                        // +0xa1
  uint8_t  mFieldA2;                                        // +0xa2
  uint8_t  mFieldA3;                                        // +0xa3
  ItemNode* mFieldA4;                                       // +0xa4
  ItemNode* mFieldA8;                                       // +0xa8
  uint8_t  mPad0ac[0x90];                                   // +0xac .. +0x13b
  int      mField13c;                                       // +0x13c
  uint8_t  mField140;                                       // +0x140
  uint8_t  mPad141[0x03];                                   // +0x141 .. +0x143
  int      mField144;                                       // +0x144
  float    mField148;                                       // +0x148
  uint8_t  mPad14c[0x70];                                   // +0x14c .. +0x1bb
  cSPUILayout_s00e2_4700 mLayout;                                      // +0x1bc

  char      FUN_00e248b0(int p2, float p3, float p4, int p5, int p6); // 0x00e248b0
  char      FUN_00e24b10();                                 // 0x00e24b10
  void      toggle_select_all();                            // 0x00e23d50
  ItemNode* find_item(int id);                              // 0x00e24ba0

  void* FUN_00e24c90(int id);
  char  FUN_00e24cc0(void* p2, void* p3, void* p4, void* p5, void* p6);
  char  FUN_00e24eb0(int p2, float p3, float p4, int p5, int p6);
  char  FUN_00e250a0(int p2, float p3, float p4, int p5, int p6);
  char  FUN_00e25120(int p2, float p3, float p4, int p5, int p6);
};
// ---- items of slice s00e24700 end

// ---- items of slice s00e26680 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* FUN_00e24290(void*, void*, void*);         // 0x00e24290  eastl range move
void FUN_00e24310(void*, void*, void*, void*, void*); // 0x00e24310
struct EaVec {
    void* mpBegin;               // +0x00
    void* mpEnd;                 // +0x04
    void* mpCapacity;            // +0x08
    void* mpUnused0c;            // +0x0c
    void* mpPool;                // +0x10

    void  resize(size_t n);                                   // 0x00e26ba0
    void* eraseAt(void* pos);                                 // 0x00e26bf0
    void  insertAt(void* pos, size_t n, const void* val);     // 0x00e25c30
    void  eraseRange(void* first, void* last);                // 0x00e25bd0
};
struct EaPair {                  // 8-byte element (two ref-counted pointers)
    void* mFirst;                // +0x00
    void* mSecond;               // +0x04
};
struct EaVec8 {
    void* mpBegin;               // +0x00
    void* mpEnd;                 // +0x04
    void* mpCapacity;            // +0x08
    void* mpUnused0c;            // +0x0c
    void* mpPool;                // +0x10

    void* eraseAt(void* pos);                                 // 0x00e26bf0
    void  insertRange(EaPair* first, EaPair* last, void* extra); // 0x00e27170
    void  insert(EaPair* pos, const EaPair* value);           // 0x00e26c80
    void  insertN(EaPair* pos, size_t count, const EaPair* value); // 0x00e26e50
    void  commit(void* first, void* last);                    // 0x00e23870
    void* grow(size_t n, void* first, void* last);            // 0x00e25ee0
};
char     g_1654c02;              // 0x01654c02  game-mode tag compared by pointer
float    g_016ac288;             // 0x016ac288  minimum window height
void* SP_GetCurrentGameMode();               // 0x00b5b800
void* SP_cTribeModeStrategy_Instance();      // 0x00cd40b0
void  FUN_00cca0a0();                        // 0x00cca0a0  thiscall
char  FUN_00cca090();                        // 0x00cca090  thiscall, returns char
void  EA_Audio_GetSystem();                  // 0x00e23250  thiscall, returns uint
struct cSPUILayout_s00e2_6680 {
    void* FindWindowByID(uint32_t id, int a3);      // 0x008105b0
};
struct cSPUISpace {
    char        _p000[0x0a4];
    void*       mpBeginA4;               // +0x0a4
    void*       mpEndA8;                 // +0x0a8
    char        _p0ac[0x1bc - 0x0ac];
    cSPUILayout_s00e2_6680 mLayout;                 // +0x1bc
    char        _p1c0[0x1f0 - 0x1c0];
    int         m1f0;                    // +0x1f0  total count
    int         m1f4;                    // +0x1f4  current count
    void*       mp1f8;                   // +0x1f8  caption text begin
    void*       mp1fc;                   // +0x1fc  caption text end

    void ToggleSelectedButton(bool flag);       // 0x00e26a90
    void UpdateCaption();                       // 0x00e26680
};
void  FUN_004c0530(void*, const wchar_t*, ...);   // 0x004c0530  swprintf-style helper
void  FUN_0057cb80(void*);                        // 0x0057cb80  eastl::fixed_string<wchar_t,16,1> dtor
void  SPUIHelpers_AnchorWindowToWindow(void*, void*);  // 0x00807340
EaPair* FUN_00e264b0(EaPair*, EaPair*);       // 0x00e264b0  partition
void  FUN_00e26530(EaPair*, EaPair*, EaPair*, void*);   // 0x00e26530  insertion sort
void* FUN_00e23ee0(void*, void*, void*, int); // 0x00e23ee0  lower_bound on cControlValue map
void* FUN_00b97140();                         // 0x00b97140  map insert (thiscall)
double FUN_009360d0();                        // 0x009360d0  random double (thiscall)
double   g_randMul;              // 0x01480fe8  = 29.0
double   g_randMax;              // 0x0140ba0  = 30.0
char     g_randRng;              // 0x01601760  RandomLinearCongruential object
struct cControlValue {                 // value half of the map's pair<>
    float    value;                    // +0x04
    uint8_t  percentage;               // +0x08
    uint8_t  setDistress;              // +0x09
    char     _p0a[2];
    uint32_t updateTick;               // +0x0c
};
struct ControlValueMap {
    void*   mpBegin;                   // +0x00
    void*   mpEnd;                     // +0x04
    void*   mpCapacity;                // +0x08
    char    _p0c[0x14 - 0x0c];
    uint8_t mPoolTag;                  // +0x14
};
struct cSPUIPosseItem_s00e2_6680 {
    char            _p000[0x0ac];
    int32_t         mDistress[3];      // +0x0ac
    char            _p0b8[0x124 - 0x0b8];
    ControlValueMap mControlValues;    // +0x124

    uint8_t SetControlValue(uint32_t id, float value, bool percentage, bool setDistress);  // 0x00e27230
};
// ---- items of slice s00e26680 end

// ---- items of slice s00e27310 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short     u16;
typedef signed int         i32;
#define VT(p)   (*(void***)(p))
#define MOPS(p) ((COps*)(p))
static inline void AddRefI(void* p)  { ((void (__thiscall*)(void*))VT(p)[0])(p); }
static inline void ReleaseI(void* p) { ((void (__thiscall*)(void*))VT(p)[1])(p); }
void* __cdecl FUN_00f473a0(u32 size, void* file, int a, int b, int c, int d); // 0x00f473a0
void* __cdecl FUN_00b5b800();                              // 0x00b5b800
void* __cdecl FUN_0067dcc0();                              // 0x0067dcc0
float __cdecl FUN_00805080();                              // 0x00805080
void* __cdecl FUN_007f81d0(void* out, void* win, float scale, float t, float k, int z); // 0x007f81d0
void* __cdecl FUN_00cd40b0();                              // 0x00cd40b0
void  __cdecl FUN_00435ed0(u32 a, void* b);                // 0x00435ed0
void  __cdecl FUN_00e26de0(void* a, void* b, void* fn);    // 0x00e26de0
u8    __stdcall FUN_00950ef0(u32 a, void* b);              // 0x00950ef0
struct COps
{
    void FUN_00e26680();                     // 0x00e26680
    void FUN_00cca0a0();                     // 0x00cca0a0
    u8   FUN_00cca090();                     // 0x00cca090
    u8   FUN_00e27be0(u32 a, void* obj);     // 0x00e27be0
};
class cSPUILayout_s00e2_7310
{
public:
    bool  Init(const void* key, bool a, u32 b);       // 0x008120d0
    void* FindWindowByID(u32 id, bool recurse);       // 0x008105b0
    u8    pad[0x18];
};
struct cRefPair
{
    void* mpFirst;                                     // +0x00
    void* mpSecond;                                    // +0x04
};
struct cBarList
{
    cRefPair* mpBegin;                                 // +0x00
    cRefPair* mpEnd;                                   // +0x04
    void* FUN_00e23870(void* a, void* b);              // 0x00e23870
    void  FUN_00e25bd0(void* a, void* b);              // 0x00e25bd0
};
struct cRefList
{
    void* mpBegin;                                     // +0x00
    void* mpEnd;                                       // +0x04
    void  FUN_00e25bd0(void* a, void* b);              // 0x00e25bd0
};
struct cWindowVec
{
    void* mpBegin;                                     // +0x00
    void* mpEnd;                                       // +0x04
    void  FUN_00e25c30(void* pos, u32 n, void* value); // 0x00e25c30
    void  FUN_00e25bd0(void* a, void* b);              // 0x00e25bd0
};
struct cWindowArray
{
    void** mpData;                                     // +0x00
    void   FUN_00e26ba0(int n);                        // 0x00e26ba0
};
struct cWString
{
    u8 pad[0x10];
    void assign(const u16* first, const u16* last);    // 0x00423650
};
struct cVec8;
class cSPUIPosse_s00e2_7310;
class cSPUIPosseItem_s00e2_7310
{
public:
    u8          pad00[0x0c];                 // +0x00
    cRefList    mRefs;                       // +0x0c
    u8          pad14[0x3c];                 // +0x14
    void*       mpField50;                   // +0x50
    u8          mKey[0x28];                  // +0x54
    cSPUILayout_s00e2_7310 mLayout;                     // +0x7c
    i32         mState;                      // +0x94
    u8          pad98[0x04];                 // +0x98
    cSPUIPosse_s00e2_7310* mpPosse;                     // +0x9c
    u8          padA0;                       // +0xa0
    u8          mStateSwap;                  // +0xa1
    u8          padA2[0x02];                 // +0xa2
    cBarList    mBars;                       // +0xa4
    void*       mpFieldAC;                   // +0xac
    float       mBlinkerStart;               // +0xb0
    u8          padB4[0x20];                 // +0xb4
    cWindowArray mWindows;                   // +0xd4
    u8          padD8[0x28];                 // +0xd8
    cWindowVec  mColorWindows;               // +0x100
    u8          pad108[0x1c];                // +0x108
    u8*         mControlValuesBegin;         // +0x124
    u8*         mControlValuesEnd;           // +0x128
    u8          pad12c[0x10];                // +0x12c
    void*       mpStateRootWindow;           // +0x13c
    u8          pad140[0x0c];                // +0x140
    float       mControlValue01;             // +0x14c
    u8          pad150[0x84];                // +0x150
    u8          mFlag1d4;                    // +0x1d4
    u8          pad1d5[0x1b];                // +0x1d5
    u32         mField1f0;                   // +0x1f0
    u32         mField1f4;                   // +0x1f4
    cWString    mCaption;                    // +0x1f8

    u8   init(cSPUIPosse_s00e2_7310* posse);                                  // 0x00e277b0
    __declspec(noinline) void SetStateWithoutNotification(u32 state); // 0x00e27310
    void SetState_BlinkGuard(u32 state);                           // 0x00e27df0
    void SetState_SpaceGuard(u32 state);                           // 0x00e27f60
    void SetState_Skip24(u32 state);                               // 0x00e27fa0
    void SetState_Only1(u32 state);                                // 0x00e28010
    void SetState_Skip234(u32 state);                              // 0x00e28030
    void FUN_00e281a0(u8 flag);                                    // 0x00e281a0
    void FUN_00e28230();                                           // 0x00e28230
    u8   SetControlValue(u32 id, float value, u32 a, u32 b);       // 0x00e27230
    void update_control_value(u32 id);                             // 0x00e25fa0
    void motive_bars_and_background_reposition(u32 a);             // 0x00e21f30
    void motive_bars_and_background_collect_initial_metrics();     // 0x00e22270
    void FUN_00e27c30(u32 a, u32 b);                               // 0x00e27c30
};
class cSPUIPosse_s00e2_7310
{
public:
    u8          pad00[0xa4];                 // +0x00
    void*       mpBarBegin;                  // +0xa4
    void*       mpBarEnd;                    // +0xa8
    u8          padAC[0x110];                // +0xac
    cSPUILayout_s00e2_7310 mLayout;                     // +0x1bc
    u8          pad1d4[0x24];                // +0x1d4
    cWString    mCaption;                    // +0x1f8
    void*       mpAnimator;                  // +0x208

    void FUN_00e23de0();                     // 0x00e23de0
    void toggle_select_all();                // 0x00e23d50
    i32  FUN_00e23250();                     // 0x00e23250
    u8   OnCtrlActivated(void* ctrl, u32 a2, u32 id, u32 a4);  // 0x00e27b20
    void SetCaptionText(const u16* text);                      // 0x00e27c50
};
struct cSPUIAnimator_s00e2_7310
{
    void AddAnimation(void* target, void* win, u32 id);   // 0x007f8d10
};
class cSPUIPosseItemTribeBaby : public cSPUIPosseItem_s00e2_7310
{
public:
    u8 init(cSPUIPosse_s00e2_7310* posse);                                        // 0x00e27c90
    u8 SetControlValue(u32 id, float value, u32 a, u32 b);             // 0x00e27d30
};
class cSPUIPosseItemTribe : public cSPUIPosseItem_s00e2_7310
{
public:
    u8 init(cSPUIPosse_s00e2_7310* posse);                                        // 0x00e27e20
};
class cSPUIPosseItemSpace : public cSPUIPosseItem_s00e2_7310
{
public:
    u8 init(cSPUIPosse_s00e2_7310* posse);                                        // 0x00e27ef0
};
class cSPUIPosseItemCreature : public cSPUIPosseItem_s00e2_7310
{
public:
    u8 init(cSPUIPosse_s00e2_7310* posse);                                        // 0x00e27fc0
};
class cSPUIPosseItemPlot : public cSPUIPosseItem_s00e2_7310
{
public:
    u8 init(cSPUIPosse_s00e2_7310* posse);                                        // 0x00e28050
};
struct cVec8
{
    cRefPair* mpBegin;                                 // +0x00
    cRefPair* mpEnd;                                   // +0x04
    cRefPair* mpCap;                                   // +0x08
    void* FUN_00e23870(void* a, void* b);              // 0x00e23870
    void  FUN_00e26e50(void* pos, u32 n, void* value); // 0x00e26e50
    void  FUN_00e26c80(void* pos, cRefPair* value);    // 0x00e26c80
    void  push_back(cRefPair* src);                    // 0x00e280e0
    void  resize(u32 n);                               // 0x00e28250
};
struct AnimOut
{
    u32  mValue0;      // +0x00
    u32  mValue1;      // +0x04
    u32  mValue2;      // +0x08
    void* mpRef;       // +0x0c
    u8   mRest[0x34];  // +0x10
};
// ---- items of slice s00e27310 end

// ---- items of slice s00fc7430 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator {
struct cBuilding {
  float GetCost();
};
}
// ---- items of slice s00fc7430 end

// ---- items of slice s00e25710 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00e25240(void*, int, int, int);
extern "C" void  __cdecl FUN_00e253c0(void*, void*, void*);
extern "C" void  __cdecl FUN_00e25df0(void*, void*, void*, void*);
extern "C" void  __cdecl FUN_00e25f40(void*, void*, void*);
extern "C" void  __cdecl FUN_00e26410(void*, void*, int, void*);
extern "C" void  __cdecl FUN_00bbf1a0(void*, void*, void*);
extern "C" void  __cdecl FUN_00bbea40(void*, int, int, int);
extern "C" void* __cdecl FUN_00bbc7c0(void*, void*, void*, void*, void*);
extern "C" void* __cdecl FUN_00b95480(void*, void*);
extern "C" void* __cdecl FUN_00829110(void*, void*, void*, void*);
extern "C" void* __cdecl FUN_006782c0(void*, void*, void*);
extern "C" void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
extern "C" void  __cdecl operator_delete__(void*);
extern "C" void  __cdecl FUN_00e255c0_dlg(void*);
extern "C" void* __cdecl FUN_007f83e0(void*);
struct cSPUIPosseItemBase {
  char pad0[0x98];
  int  mState;            // +0x98
  char pad9c[0x14c - 0x9c];
  float f14c;             // +0x14c
  void ctor(int a, const wchar_t* name, unsigned flags);   // 0x00e255c0
};
class cSPUIPosseItemTribe_s00e2_5710 : public cSPUIPosseItemBase { public: void* ctor(int a2); };
class cSPUIPosseItemTribeBaby_s00e2_5710 : public cSPUIPosseItemBase { public: void* ctor(int a2); };
class cSPUIPosseItemCiv : public cSPUIPosseItemBase { public: void* ctor(int a2); };
class cSPUIPosseItemSpace_s00e2_5710 : public cSPUIPosseItemBase { public: void* ctor(int a2); };
struct cSPUIPosseItemTribeGhostShell : cSPUIPosseItemBase { void* ctor(); };
struct cScenarioEditPosseItemBase {
  char pad0[0x148];
  void ctor(int a, int b);   // 0x00e25460
};
struct cSPUIPosseItem2_s00e2_5710 : cScenarioEditPosseItemBase { void* ctor(int a2, int a3); };
struct cSPUIPosseItem3 : cScenarioEditPosseItemBase { void* ctor(int a2); };
typedef void (__thiscall *ReleaseFn)(void*);
static inline void RefRelease(void* p) {
  if (p) ((ReleaseFn*)*(void**)p)[1](p);
}
struct cUIPosse15 { char pad[0x210]; void* ctor(); };
struct cVec15 { void* f(void** First, void** Last); };
struct cVec15b { int f(void* pos, unsigned n, void* src); };
struct cPosseItem15 {
  char pad0[0xb4];
  int  mDistress;              // +0xb4
  char padb8[0xd0 - 0xb8];
  float mBlinkerFrequency;     // +0xd0
  char padd4[0x124 - 0xd4];
  char* mControlValuesBegin;   // +0x124
  char* mControlValuesEnd;     // +0x128
  char pad12c[0x138 - 0x12c];
  unsigned char f138;          // +0x138
  void update_control_value(unsigned key);
  void update_control_values(char force);
  bool OnTick(void* msg);
};
// ---- items of slice s00e25710 end

// ---- items of slice s00e24a50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Owned_s00e2_4a50 {
    virtual ~Owned_s00e2_4a50();
};
struct WString_s00e2_4a50 {
    wchar_t* mpBegin;     // +0x0
    wchar_t* mpEnd;       // +0x4
    wchar_t* mpCapacity;  // +0x8

    ~WString_s00e2_4a50()
    {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator delete(mpBegin);
        }
    }
};
struct Element_s00e2_4a50 {
    char pad00[0x10];
};
struct FixedVector_s00e2_4a50 {
    Element_s00e2_4a50* mpBegin;      // +0x00
    Element_s00e2_4a50* mpEnd;        // +0x04
    Element_s00e2_4a50* mpCapacity;   // +0x08
    int mOverflowAllocator;           // +0x0c
    Element_s00e2_4a50* mpPoolBegin;  // +0x10
    char mBuffer[0x1bc - 0xa4 - 0x14];

    ~FixedVector_s00e2_4a50()
    {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete(mpBegin);
    }
    void DoDestroyValues(Element_s00e2_4a50* first, Element_s00e2_4a50* last);  // 0x00e23870
};
struct Member0c_s00e2_4a50 {
    char pad00[0xa4 - 0xc];
    ~Member0c_s00e2_4a50();  // 0x008e2b20
};
struct Member1bc_s00e2_4a50 {
    char pad00[0x1f8 - 0x1bc];
    ~Member1bc_s00e2_4a50();  // 0x00811fe0
};
struct BaseA_s00e2_4a50 {
    virtual ~BaseA_s00e2_4a50() {}
};
struct BaseB_s00e2_4a50 {
    virtual ~BaseB_s00e2_4a50() {}
};
struct Object_s00e2_4a50 : BaseA_s00e2_4a50, BaseB_s00e2_4a50 {
    char pad08[4];
    Member0c_s00e2_4a50 m0c;           // +0x00c
    FixedVector_s00e2_4a50 mItems;     // +0x0a4
    Member1bc_s00e2_4a50 m1bc;         // +0x1bc
    WString_s00e2_4a50 mName;          // +0x1f8
    char pad204[4];
    Owned_s00e2_4a50* mpOwned;         // +0x208

    virtual ~Object_s00e2_4a50();
};
// ---- items of slice s00e24a50 end

// ---- items of slice s00e24d10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Variant;
struct cRefCounted {
    virtual void slot00();
    virtual void Release();                                    // +0x04
};
struct cPropertyList : cRefCounted {
virtual void slot08();
virtual void slot0c();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1c();
    virtual void SetValue(int nIndex, const Variant& value);   // +0x20
};
struct cPropListFactory {
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0c();
virtual void slot10();
virtual void slot14();
    virtual void Create(cPropertyList** ppOut);                // +0x18
virtual void slot1c();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2c();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3c();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4c();
virtual void slot50();
    virtual void Submit(uint32_t nID, cPropertyList* pFirst,
                        cPropertyList* pSecond);               // +0x54
};
struct Variant {
    uint32_t mData[4];                                         // +0x00 .. +0x0f
    uint16_t mFlags;                                           // +0x10
    uint16_t mType;                                            // +0x12

    void     SetPointer(const void* p);                        // 0x00e21b30
    Variant& SetU32(const uint32_t* pValue);                   // 0x00422eb0
    Variant& SetVec3(const float* pValue);                     // 0x006a3570
    void     Destruct(int bReset);                             // 0x0093db80
};
cPropListFactory* PropListFactory();                           // 0x006895b0
template <class T>
struct RefPtr {
    T* mpObject;                                               // +0x00

    RefPtr() : mpObject(0) {}
    void release() {
        if (mpObject) mpObject->Release();
    }
    void reset() {
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
    }
};
// ---- items of slice s00e24d10 end

// ---- items of slice s00e24f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_015a547c;
extern float g_016ac2cc;
struct cSPUIVtbl_s00e2_4f10 { void (*slot[128])(); };
#define VT_s00e2_4f10(p) (*(cSPUIVtbl_s00e2_4f10**)(p))
typedef void     (__thiscall* FnVoid0_s00e2_4f10)(void*);
typedef uint32_t (__thiscall* FnU32_0_s00e2_4f10)(void*);
struct RectF_s00e2_4f10 {
  float mLeft;    // +0x00
  float mTop;     // +0x04
  float mRight;   // +0x08
  float mBottom;  // +0x0c
};
struct Point2_s00e2_4f10 {
  float mX;       // +0x00
  float mY;       // +0x04
  Point2_s00e2_4f10(float x, float y) : mX(x), mY(y) {}
};
struct MsgIn_s00e2_4f10 {
  uint8_t mPad00[8];   // +0x00
  int32_t mField08;    // +0x08
  uint8_t mPad0c[0x0c];// +0x0c
  void*   mField18;    // +0x18
};
class cSPUIPosseItem_s00e2_4f10 {
public:
  void*   mpVtable;         // +0x00
  uint8_t mPad04[0x148];    // +0x04 .. +0x14b
  float   mControlValue01;  // +0x14c

  char DoMessage(void* win, MsgIn_s00e2_4f10* msg);   // 0x00e247f0, base handler
};
class cSPUIPosseItemTribeBaby_s00e2_4f10 : public cSPUIPosseItem_s00e2_4f10 {
public:
  char DoMessage(void* win, MsgIn_s00e2_4f10* msg);   // 0x00e24f10
};
void* __cdecl sGetWindowImage(void* win);
struct RenderContext_s00e2_4f10 {
  void* Begin2D(int flags);   // 0x0095bc10
  void  End2D();              // 0x0095bb20
};
void __cdecl FUN_00e23340(void* batch, float halfWidth, float halfHeight, float width,
                          float height, int32_t a, int32_t b, float angleFrom,
                          float angleTo, void* image, float alpha);
// ---- items of slice s00e24f10 end

// ---- items of slice s00e25240 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef u8    (__cdecl   *TPred)(void*, void*);
struct IPtr {
  void* p;
  IPtr(const IPtr& o) : p(o.p) { if (p) ((TFv)(*(void***)p)[0])(p); }
  ~IPtr() { if (p) ((TFv)(*(void***)p)[1])(p); }
  IPtr& operator=(const IPtr& o) {
    void* n = o.p;
    void* t = p;
    if (n != t) {
      if (n) ((TFv)(*(void***)n)[0])(n);
      p = n;
      if (t) ((TFv)(*(void***)t)[1])(t);
    }
    return *this;
  }
};
struct Pair {
  IPtr a;
  IPtr b;
  __forceinline Pair& operator=(const Pair& o) {
    a = o.a;
    b = o.b;
    return *this;
  }
};
void __cdecl FUN_00e243f0(void* base, s32 top, s32 hole, Pair value, TPred pred);
// ---- items of slice s00e25240 end

// ---- items of slice s00e253c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef bool   (__cdecl   *TPred_s00e2_53c0)(void*, void*);
void* __cdecl FUN_00e23e80(void* self, void** src);   // 0x00e23e80 pair assign
struct IPtr_s00e2_53c0 {
  void* p;
  IPtr_s00e2_53c0(const IPtr_s00e2_53c0& o) : p(o.p) { if (p) ((TFv)(*(void***)p)[0])(p); }
  ~IPtr_s00e2_53c0() { if (p) ((TFv)(*(void***)p)[1])(p); }
};
struct Pair_s00e2_53c0 {
  IPtr_s00e2_53c0 a;
  IPtr_s00e2_53c0 b;
};
void  __cdecl FUN_00e25240(Pair_s00e2_53c0* first, s32 holeIndex, s32 len, s32 topIndex,
                           Pair_s00e2_53c0 value, TPred_s00e2_53c0 compare);
// ---- items of slice s00e253c0 end

// ---- items of slice s00e25460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_13eb384[];
extern "C" char g_13fa72c[];
extern "C" char g_148058c[];
extern "C" char g_148059c[];
extern "C" char g_14805b8[];
extern "C" char g_16ac238[];
typedef void (__thiscall* TFv_s00e2_5460)(void*);
struct LayoutCtorC { void ctor(); };                    // 0x00810000  embedded layout constructor
struct cSPUIPosse_s00e25460 {
  void* ctor(void* pOwner, const u32* pKey);
};
// ---- items of slice s00e25460 end

// ---- items of slice s00e255c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (__thiscall* TFv_s00e2_55c0)(void*);
u32 __cdecl FNV1_String16(const void* pName, u32 basis, int lower);   // 0x00932f30
struct cSPUIPosseItem_s00e255c0 {
  void* ctor(void* pOwner, const void* pName, u32 typeId);
};
// ---- items of slice s00e255c0 end

// @ 0x00e213f0
bool __cdecl FUN_00e213f0(void* obj, float value, char flag)
{
  if (!obj)
    return false;
  wchar_t buf[42];

  if (flag) {
    if (value < 0.0f) value = 0.0f;
    float cap = DAT_013ec4d0;
    if (value > cap) value = cap;
    void* lbl = ((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(obj, 0x10edf11);
    if (lbl) {
      ((void(__thiscall*)(void*, float))(*(void***)lbl)[4 / 4])(lbl, 0.0f);
      return true;
    }
    lbl = ((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(obj, 0xeeee8218);
    if (!lbl)
      return false;
    FUN_00881ea0((double)value, buf, 0x20, L"%-F%-p");
    wchar_t* p = buf;
    while (p[0]) p++;
    *(u32*)p  = 0x00250020;   // append L" %"
    p[2] = 0;
    ((void(__thiscall*)(void*, wchar_t*))(*(void***)lbl)[0x80 / 4])(lbl, buf);
    return true;
  }

  void* lbl = ((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(obj, 0xeeee8218);
  if (!lbl)
    return false;
  FUN_00881ea0((double)value, buf, 0x20, L"%-F%-p");
  ((void(__thiscall*)(void*, wchar_t*))(*(void***)lbl)[0x80 / 4])(lbl, buf);
  return true;
}

// @ 0x00e21530
void __fastcall FUN_00e21530(void* self_, void*, int id, void* layout, void* extra)
{
  int cur = *(int*)((char*)self_ + 0x6c);
  if (id == cur)
    return;
  void* img = FUN_008061c0(layout, id);
  ((void(__thiscall*)(void*, int, void*, void*))(*(void***)self_)[0xa0 / 4])(self_, id, img, extra);
}

// @ 0x00e21590
u32 __stdcall FUN_00e21590(int idx)
{
  switch (idx) {
  case 0: return 0x3d99162;
  case 1: return 0x3d99184;
  default: return 0x3d99162;
  }
}

// @ 0x00e215b0
int __fastcall FUN_00e215b0(cSPUIPosseItem* self)
{
  return *(const s32*)((const char*)self + 0xa8) <= *(const s32*)((const char*)self + 0xac);
}

// @ 0x00e215d0
void __fastcall FUN_00e215d0(void* self_, s32, u8 flags)
{
  u32 state;
  if (flags & 1) {
    state = (flags & 2) ? 4 : 2;
  } else {
    state = (flags & 2) | 1;
  }
  if (*(u32*)((char*)self_ + 0x94) == state)
    return;
  ((void(__thiscall*)(void*, u32))(*(void***)self_)[0xd0 / 4])(self_, state);
}

// @ 0x00e21620
void __stdcall FUN_00e21620(u32* out)
{
  out[0] = 0;
  out[1] = 1;
}

// @ 0x00e21640
bool __fastcall cSPUIPosseItem_blink_for_a_motive(cSPUIPosseItem2* self, s32, void* window, int idx, float t)
{
  if (self->mDistress[idx - 1] == 2 /* kDistressHigh */) {
    float scale = (self->mBlinkerScaleTo - self->mBlinkerScaleFrom) * t + self->mBlinkerScaleFrom;
    u32 color = FUN_007f5eb0(self->mBlinkerColorFrom, self->mBlinkerColorTo, t);
    ((void(__thiscall*)(void*, u32))(*(void***)window)[0x5c / 4])(window, color);
    FUN_00808210(window, scale);
    return true;
  }
  if (0.1f > t) {
    ((void(__thiscall*)(void*, u32))(*(void***)window)[0x5c / 4])(window, 0xffffffff);
    FUN_00808210(window, 1.0f);
  }
  return 0.1f <= t;
}

// @ 0x00e21700
bool __cdecl FUN_00e21700(void* p)
{
  VObj1* w = (VObj1*)p;
  ((void(__thiscall*)(VObj1*, int))w->vtbl[0xb8 / 4])(w, 1);
  return true;
}

// @ 0x00e21720
bool __cdecl FUN_00e21720(void* p)
{
  VObj1* w = (VObj1*)p;
  ((void(__thiscall*)(VObj1*, int))w->vtbl[0xb8 / 4])(w, 2);
  return true;
}

// @ 0x00e21750
void __fastcall FUN_00e21750(void* self_, s32, void* obj, u32 kind, u32)
{
  void* inner = ((void*(__thiscall*)(void*))(*(void***)obj)[0x14 / 4])(obj);
  u32 r = ((u32(__thiscall*)(void*, u32))(*(void***)inner)[0x48 / 4])(inner, kind);
  ((void(__thiscall*)(void*, void*, u32, u32))(*(void***)self_)[0x40 / 4])(self_, obj, kind, r);
}

// @ 0x00e217c0
bool __cdecl FUN_00e217c0(void* a, void* b)
{
  if (!a || !b)
    return false;
  s32 ia = *(s32*)((char*)a + 0xb1c);
  s32 ib = *(s32*)((char*)b + 0xb1c);
  if (ia != ib)
    return ia < ib;
  if (ia != 2) {
    PlanetModel_s00e2_17c0* pm = (PlanetModel_s00e2_17c0*)FUN_00b3d350();
    if (pm) {
      int ca = pm->FUN_00b88590(((PosSource_s00e2_17c0*)((char*)a + 0x34))->GetPosition());
      int cb = pm->FUN_00b88590(((PosSource_s00e2_17c0*)((char*)b + 0x34))->GetPosition());
      if (ca != cb)
        return ca < cb;
    }
  }
  return *(u32*)((char*)a + 0x24) < *(u32*)((char*)b + 0x24);
}

// @ 0x00e21880
void cSPUIPosse::SetCaptionIcon(void* pImage)
{
    IWindow* pWindow = mLayout.FindWindowByID(0x3dae414, true);
    SPUIHelpers::SetWindowImage(pWindow, pImage, 0);
}

// @ 0x00e218b0
void cSPUIPosse::SetItemIcon(void* pImage)
{
    IWindow* pWindow = mLayout.FindWindowByID(0x3dae414, true);
    UI::SetWindowImage(pWindow, pImage, 0);
}

// @ 0x00e218e0
void cSPUIPosse::SetPosseMemberCount(float fCount)
{
    IWindow* pWindow = mLayout.FindWindowByID(0x3dae413, true);
    if (pWindow) {
        IWindow* pNumber = (IWindow*)pWindow->Cast(0xeeee8218);
        if (pNumber) {
            char aBuffer[0x40];
            EA::Locale::SetNumberString((double)fCount, aBuffer, 0x20, L"%-F%-p");
            pNumber->v080(aBuffer);
        }
    }
}

// @ 0x00e219a0
void SPUIComputeCirclePoint(float fAngle, float* pSin, float* pCos)
{
    static const float kSqrtTwo  = (float)sqrt(kTwo);
    static const float kSqrtHalf = (float)sqrt(kHalf);

    float fScale = kSqrtTwo;
    *pSin = (float)sin(fAngle);
    *pCos = (float)cos(fAngle);
    *pSin = *pSin * fScale;

    float fCos = *pCos * fScale;
    *pCos = fCos;
    if (fCos >= kOne) {
        *pCos = kOne;
        *pSin = *pSin / (fCos * kSqrtHalf);
        return;
    }
    if (fCos <= kNegOne) {
        *pCos = kNegOne;
        *pSin = *pSin / -(fCos * kSqrtHalf);
        return;
    }
    float fSin = *pSin;
    if (fSin >= kOne) {
        *pSin = kOne;
        *pCos = *pCos / (fSin * kSqrtHalf);
        return;
    }
    if (fSin <= kNegOne) {
        *pSin = kNegOne;
        *pCos = *pCos / -(fSin * kSqrtHalf);
    }
}

// @ 0x00e21ae0
void __stdcall SPUIInitPairA(uint32_t* pPair)
{
    pPair[0] = 0;
    pPair[1] = 0xffffffff;
}

// @ 0x00e21b00
void __stdcall SPUIInitPairB(uint32_t* pPair)
{
    pPair[0] = 0xffffffff;
    pPair[1] = 0xffffffff;
}

// @ 0x00e21ba0
void cSPUIPosseItem_s00e2_1880::SetSomething(void* pField)
{
    mpField98 = pField;
    if (mpField9c)
        mpField9c->v08c();
}

// @ 0x00e21bd0
void cSPUIPosseItem_s00e2_1880::SetTaskKey(const ResourceKey* pKey, int32_t nFlags)
{
    IWindow* pWindow = mpFieldD4->mpWindow10->FindWindowByID(0x3d99141, true);
    ResourceKey* pMine = &mIconKey;
    if (pKey->mInstanceID != pMine->mInstanceID || pKey->mGroupID != pMine->mGroupID ||
        pKey->mTypeID != pMine->mTypeID) {
        *pMine = *pKey;
        SPUIHelpers::SetWindowImage(pWindow, pMine, nFlags);
    }
    pWindow->v07c(true, true);
}

// @ 0x00e21c40
void cSPUIPosseItem_s00e2_1880::SetTaskIcon(uint32_t nTaskIconID, void* pImage, int32_t nFlags)
{
    IWindow* pWindow = mpFieldD4->mpWindow10->FindWindowByID(0x3d99141, true);
    if (nTaskIconID != mTaskIconID) {
        mTaskIconID = nTaskIconID;
        UI::SetWindowImage(pWindow, pImage, nFlags);
    }
    pWindow->v07c(true, true);
}

// @ 0x00e21ca0
void cSPUIPosseItem_s00e2_1880::SetBlinkerMotiveVisible(bool bShow)
{
    if (!bShow && mTaskIconID == 0 && mIconKey.mInstanceID == 0)
        return;
    uint32_t nValue = bShow ? mTaskIconID : 0;
    mTaskIconID = nValue;
    mIconKey.mInstanceID = 0;
    IWindow* pWindow = mpFieldD4->mpWindow10->FindWindowByID(0x3d99141, true);
    pWindow->v07c(true, bShow);
}

// @ 0x00e21cf0
void cSPUIPosseItem_s00e2_1880::SetBlinkerMotive(int32_t nMotive, char bForce)
{
    do {
        if (bForce || mFieldA0) {
            IWindow* aWindows[2];
            for (int32_t i = 0; i < 2; ++i) {
                if (i != 1 || v0b4()) {
                    uint32_t nWindowID = v0d4(i);
                    aWindows[i * 2] = mLayout.FindWindowByID(nWindowID, true);
                    aWindows[i * 2 + 1] = mLayout.FindWindowByID(nWindowID + 1, true);
                    if (aWindows[i * 2 + 1])
                        aWindows[i * 2 + 1]->v07c(true, false);
                }
            }
            if (bForce) {
                if (mField94 != 1 && mField94 != 2)
                    return;
                IWindow* pMotive = aWindows[nMotive * 2 + 1];
                mFieldA0 = 1;
                if (!pMotive)
                    return;
                pMotive->v000();
                IWindow* pContainer = mpFieldD4->mpWindow10->FindWindowByID(0x3d99151, true);
                if (pMotive->GetParent() != pContainer) {
                    IWindow* pOldParent = pMotive->GetParent();
                    if (pOldParent)
                        pOldParent->v0dc(pMotive);
                    pContainer->v0dc(pMotive);
                }
                AnchorWindowToWindow(pContainer, pMotive, 0x300, 0);
                pMotive->v07c(true, true);
                pMotive->v004();
                return;
            }
            mFieldA0 = 0;
        }
        int32_t nIndex = v0d8();
        if (mFieldA8[nIndex] != 2)
            return;
        bForce = 1;
        nMotive = nIndex;
    } while (true);
}

// @ 0x00e21e50
void cSPUIPosseItem_s00e2_1880::SetItemKeyIcon(const ResourceKey* pKey, int32_t nUnused)
{
    mItemKey = *pKey;
    IWindow* pWindow = mpFieldD4->mpWindow10->FindWindowByID(0x3d99151, true);
    SPUIHelpers::SetWindowImage(pWindow, &mItemKey, 0);
}

struct ResourceKeyZero_e21ea0 : ResourceKey {
    ResourceKeyZero_e21ea0() { mInstanceID = 0; mGroupID = 0; mTypeID = 0; }
};

// @ 0x00e21ea0
void cSPUIPosseItem_s00e2_1880::SetItemIcon(void* pImage, int32_t nUnused)
{
    mItemKey = ResourceKeyZero_e21ea0();
    uint32_t nNone = 0;
    IWindow* pWindow = mpFieldD4->mpWindow10->FindWindowByID(0x3d99151, true);
    UI::SetWindowImage(pWindow, pImage, nNone);
}

// @ 0x00e21ee0
void cSPUIPosseItem_s00e2_1880::AttachToParent()
{
    IWindow* pWindow = mpFieldD4->mpWindow10;
    IWindow* pParent = pWindow->GetParent();
    pWindow->v07c(true, true);
    pParent->v0e8(pWindow);
    pParent->GetParent()->v0e8(pParent);
}

// @ 0x00e21f30
void cSPUIPosseItem_s00e2_1880::MotiveBarsAndBackgroundReposition(bool bShow)
{
    IWindow* pBars = mLayout.FindWindowByID(0x56cec38, true);
    IWindow* pBackground = mLayout.FindWindowByID(0x56bd170, true);
    IWindow* aMotives[2];
    aMotives[0] = mLayout.FindWindowByID(0x3d99162, true);
    aMotives[1] = v0b4() ? mLayout.FindWindowByID(0x3d99184, true) : 0;
    pBackground->GetRect();

    int32_t aIndices[2];
    v0dc(aIndices);
    if (aIndices[0] == -1)
        return;

    if (bShow) {
        IWindow* pMotive = aMotives[aIndices[0]];
        if (pMotive->v0b4())
            return;
        pMotive->v0b8(pMotive, pMotive);
        IWindow* pMotiveBg = pMotive->FindWindowByID(0x56bd1b8, true);
        float* pBgRect = pMotiveBg->GetRect();
        float fWidth = pBgRect[2] - pBgRect[0];

        float aBehind[2];
        float aBars[2];
        GetBoundingScreenRect(aBehind, pMotiveBg, 0);
        GetBoundingScreenRect(aBars, pBackground, 0);

        for (int32_t i = 0; i < 2; ++i) {
            int32_t nIndex = aIndices[i];
            if (nIndex == -1)
                continue;
            IWindow* pMotiveWindow = aMotives[nIndex];
            float* pRect = &mRect30[nIndex * 4];
            if (!pMotiveWindow)
                continue;
            pMotiveWindow->v070(pRect[0] + aBars[1], pRect[1]);
            pMotiveWindow->v074(pRect[2] - aBars[1], pRect[3]);
            IWindow* pSub = pMotiveWindow->FindWindowByID(0x56bd1b8, true);
            float* pSubRect = pSub->GetRect();
            pSub->v070(pSubRect[0] - aBars[1], pSubRect[1]);
        }
        pBars->v070(mRect10[0], mRect10[1]);
        pBars->v074(mRect10[2], mRect10[3]);
        return;
    }

    IWindow* pMotive = aMotives[aIndices[0]];
    if (!pMotive->v0b4())
        return;
    pMotive->v0b8(0, pMotive);
    IWindow* pMotiveBg = aMotives[aIndices[0]]->FindWindowByID(0x56bd1b8, true);
    float* pBgRect = pMotiveBg->GetRect();
    float fWidth = pBgRect[2] - pBgRect[0];
    pBars->v070(mRect10[0], mRect10[1]);
    pBars->v074(mRect10[2], mRect10[3]);
    pBackground->GetRect();

    for (int32_t i = 0; i < 2; ++i) {
        int32_t nIndex = aIndices[i];
        if (nIndex == -1)
            continue;
        IWindow* pMotiveWindow = aMotives[nIndex];
        float* pRect = &mRect30[nIndex * 4];
        pMotiveWindow->v070(pRect[0], pRect[1]);
        pMotiveWindow->v074(pRect[2], pRect[3]);
        IWindow* pSub = pMotiveWindow->FindWindowByID(0x56bd1b8, true);
        float* pSubRect = pSub->GetRect();
        pSub->v070(pSubRect[0] + fWidth, pSubRect[1]);
    }
}

// @ 0x00e22270
void cSPUIPosseItem_s00e2_1880::MotiveBarsAndBackgroundCollectInitialMetrics()
{
    IWindow* aWindows[4];
    aWindows[0] = mLayout.FindWindowByID(0x3d99162, true);
    aWindows[1] = v0b4() ? mLayout.FindWindowByID(0x3d99184, true) : 0;
    aWindows[3] = mLayout.FindWindowByID(0x56cec38, true);
    IWindow* pBars = mLayout.FindWindowByID(0x56bd170, true);
    (void)pBars;

    for (int32_t i = 0; i < 4; ++i) {
        IWindow* pWindow = aWindows[i];
        if (!pWindow)
            continue;
        float* pRect;
        switch (pWindow->GetTypeID()) {
        case 0x56cec38:
            pRect = mRect10;
            break;
        case 0x56bd170:
            pRect = mRect20;
            break;
        case 0x3d99162:
            pRect = mRect30;
            break;
        case 0x3d99184:
            pRect = mRect40;
            break;
        default:
            continue;
        }
        float* pSource = pWindow->GetRect();
        pRect[0] = pSource[0];
        pRect[1] = pSource[1];
        pRect[2] = pSource[2] - pSource[0];
        pRect[3] = pSource[3] - pSource[1];
    }
}

// 0x00e22370 (byte-exact lifted version: match/slices/s00e22370/s00e22370.cpp)
char cSPUIPosseItem_s00e2_1880::Shutdown()
{
    if (mpField13c && MessageServer_s00e2_1880())
        MessageServer_s00e2_1880()->PostMessage(&mHandler, 0x3e41916, -0x270f);
    if (mpField9c) {
        IWindow* pWindow = mpField9c;
        mpField9c = 0;
        pWindow->v004();
    }
    if (mpField50) {
        IWindow* pWindow = mpField50;
        mpField50 = 0;
        pWindow->v004();
    }
    if (mpField13c) {
        mpField13c->v108(this);
        if (mpField13c) {
            IWindow* pWindow = mpField13c;
            mpField13c = 0;
            pWindow->v004();
        }
    }
    mLayout.Shutdown(1);
    return 1;
}

// @ 0x00e22420
bool cSPUIPosseItem_s00e2_1880::OnMouseUp(IWindow* pWindow, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    mFieldA2 = 0;
    mFieldA3 = 0;
    if (mpField13c == pWindow) {
        if (pWindow == SP::WindowManager()->v054(true))
            SP::WindowManager()->v058(true, false);
    }
    return false;
}

// @ 0x00e22470
bool cSPUIPosseItem_s00e2_1880::OnMouseMove(IWindow* pWindow, float fX, float fY, uint32_t nFlags)
{
    if (mFieldA2) {
        float aPoint[2];
        aPoint[0] = fX;
        aPoint[1] = fY;
        float* pScreen = pWindow->v0c0(aPoint);
        float aLocal[2];
        aLocal[0] = pScreen[0];
        aLocal[1] = pScreen[1];
        cHitWindow* pWindowHit = (cHitWindow*)SP::WindowManager()->v044(aLocal);
        if (pWindowHit) {
            if (pWindowHit->GetTypeID() == 0x3d98299) {
                cHitWindow* pNamed = pWindowHit->GetNamedWindow(0x3e43b66);
                if (pNamed) {
                    cHitWindow* pMotive = pNamed->Cast(0x3deb129);
                    if (pMotive) {
                        if (mFieldA4 == 1 || mFieldA4 == 2)
                            pMotive->SetMotive(mFieldA4);
                    }
                }
            }
        }
    }
    return false;
}

// @ 0x00e22550
bool cSPUIPosseItem_s00e2_1880::OnFocusChange(uint32_t nArg1, int32_t nReason, IWindow* pWindow)
{
    (void)nArg1;
    if (nReason != 1)
        return false;
    uint32_t nModifiers = GetModifierState();
    bool bCtrl = ((nModifiers >> 1) & 1) != 0;
    if (!mpField13c)
        return false;
    if (mFieldA1)
        mFieldA1 = (pWindow == mpField13c);
    switch (mField94) {
    case 1:
        if (!Contains((const uint32_t*)mpField13c, (const uint32_t*)pWindow))
            return false;
        if (mFieldA2 || bCtrl)
            return false;
        v0b8(3);
        return false;
    case 2:
        if (!Contains((const uint32_t*)mpField13c, (const uint32_t*)pWindow))
            v0b8(1);
        return false;
    case 3:
        if (Contains((const uint32_t*)mpField13c, (const uint32_t*)pWindow)) {
            if (mFieldA2 || bCtrl)
                return false;
            v0b8(4);
        }
        return false;
    case 4:
        if (!Contains((const uint32_t*)mpField13c, (const uint32_t*)pWindow))
            v0b8(2);
        return false;
    }
    return false;
}

// @ 0x00e22670
bool cItemMessageHandler::HandleMessage(uint32_t nMessageID, cUIMessage* pMessage)
{
    if (pMessage && nMessageID == 0x3e41916) {
        cSPUIPosseItem_s00e2_1880* pItem = (cSPUIPosseItem_s00e2_1880*)((char*)this - 0xc);
        IWindow* pSender = pMessage->mpSender;
        if (pSender == pItem->v0c4()) {
            pItem->OnMotiveValueChanged(pMessage->mValue);
            return true;
        }
    }
    return false;
}

// @ 0x00e226c0
bool cSPUIPosse::GetItemFlag()
{
    IWindow* pWindow = mpField13c->FindWindowByID(0x7c4b4a0, true);
    if (pWindow) {
        IWindow* pProperty = (IWindow*)pWindow->Cast(0x8ed27e7a);
        if (pProperty)
            return (pProperty->GetFlags() >> 2) & 1;
    }
    return false;
}

// @ 0x00e22700
void cSPUIPosse::SetItemFlag(void* pValue)
{
    IWindow* pWindow = mpField13c->FindWindowByID(0x7c4b4a0, true);
    if (!pWindow)
        return;
    IWindow* pProperty = (IWindow*)pWindow->Cast(0x8ed27e7a);
    if (!pProperty)
        return;
    pProperty->v028(4, pValue);
}

// @ 0x00e22740
void cSPUIPosseItem_s00e2_1880::SetFrameCallback()
{
    mpField9c->v0a0(SPUIFrameCallbackA, 0);
}

// @ 0x00e22760
bool cSPUIPosse::CompareWith(cSPUIPosseSortable* pA, cSPUIPosseSortable* pB)
{
    IWindow* pWinA = pA->v0c4();
    cNamedItem* pNameA = pWinA ? (cNamedItem*)pWinA->Cast(0x137e8e0) : 0;
    IWindow* pWinB = pB->v0c4();
    cNamedItem* pNameB = pWinB ? (cNamedItem*)pWinB->Cast(0x137e8e0) : 0;
    if (pNameA && pNameB)
        return FUN_00e217c0(pNameA, pNameB);
    return pA->v08c() < pB->v08c();
}

// @ 0x00e227f0
void cSPUIPosse::ForEachItem(bool (*pfnCallback)(void*, void*), void* pContext)
{
    cPosseItemEntry* pEntry = mpItemsA4;
    while (pEntry < mpItemsA8) {
        if (!pfnCallback(pEntry->mpItem, pContext))
            return;
        ++pEntry;
    }
}

// @ 0x00e22830
void cSPUIPosse::SetPlacement(float fX, float fY, int32_t nUnused, bool bVisible)
{
    mField1d8 = fX;
    mField1dc = fY;
    mField1ec = (uint8_t)bVisible;
    mField1d4 = 1;
}

// @ 0x00e22860
cVec4 cSPUIPosse_s00e2_2860::GetWindowBounds()
{
    cVec4 result = { 0.0f, 0.0f, 0.0f, 0.0f };

    cSPUIWindow* window = mLayout1bc.FindWindowByID(0x3d98298, 0);
    if (window != 0) {
        cVec4* rect = VT_38_0(window);
        result.x = rect->x;
        result.y = rect->y;
        result.z = rect->z;
        result.w = rect->w;
        cVec2 topLeft;
        VT_C0_2(window, &topLeft, cVec2(0.0f, 0.0f));
        cVec2 bottomRight;
        VT_C0_2(window, &bottomRight, cVec2(result.z - result.x, result.w - result.y));
        result.x = topLeft.x;
        result.y = topLeft.y;
        result.z = bottomRight.x;
        result.w = bottomRight.y;
    }

    cSPUIWindow* handle = mLayout1bc.FindWindowByID(0x3dae412, 1);
    if (handle != 0 && (VT_28_0(handle) & 1) != 0) {
        cVec4* rect = VT_38_0(handle);
        cVec4 area;
        area.x = rect->x;
        area.y = rect->y;
        area.z = rect->z;
        area.w = rect->w;
        cVec2 topLeft;
        VT_C0_2(handle, &topLeft, cVec2(0.0f, 0.0f));
        cVec2 bottomRight;
        VT_C0_2(handle, &bottomRight, cVec2(area.z - area.x, area.w - area.y));
        result.x = fmin_v(result.x, topLeft.x);
        result.y = fmin_v(result.y, topLeft.y);
        result.z = fmax_v(result.z, bottomRight.x);
        result.w = fmax_v(result.w, bottomRight.y);
    }

    return result;
}

// @ 0x00e22a60
void cSPUIPosse_s00e2_2860::SnapToPosition()
{    cSPUIWindow* window = mLayout1bc.FindWindowByID(0x3d98298, 0);
    cVec4* area = VT_38_0(window);
    cVec4 v;
    v.x = area->x;
    v.y = area->y;
    v.z = area->z;
    v.w = area->w;
    float offset = mField1d8;
    cVec4 mainArea;
    if (mFlag1ec == 0) {
        cVec4* m = GetMainWindowArea(&mainArea);
        offset = ((m->z - m->x) - mField1d8) - (v.z - v.x);
    }
    cVec4* m2 = GetMainWindowArea(&mainArea);
    VT_70_2F(window, offset, ((m2->w - m2->y) - mField1dc) - (v.w - v.y));
}

// @ 0x00e22b50
void cSPUIPosse_s00e2_2860::UpdateLayout(bool bSnap)
{
    if (mFlag1d4 == 0)
        return;
    mFlag1d4 = 0;

    cSPUIWindow* pSel = mLayout1bc.FindWindowByID(0x3d98298, 1);
    cSPUIWindow* pOther = mLayout1bc.FindWindowByID(0x3d982ff, 1);

    if (mpAudioBeginA4 != mpAudioEndA8 || mFlag1e5 != 0) {
        int nMax = mField1e0;
        if (nMax < 1)
            nMax = 10000;

        float fItemHeight = 0.0f;
        float fItemWidth = 0.0f;
        float fHeight = 0.0f;
        if (mpAudioBeginA4 != mpAudioEndA8) {
            void* pItem = *mpItemBegin0c;
            cSPUIWindow* pItemWin = ((cSPUILayout_s00e2_2860*)((char*)pItem + 0x7c))->FindWindowByID(0x3d98299, 1);
            fItemHeight = VT_C0_0(pItem);
            cVec4* pRect = VT_38_0(pItemWin);
            fItemWidth = pRect->z - pRect->x;
            pRect = VT_38_0(pItemWin);
            fHeight = pRect->w - pRect->y;
        }

        float fScale = mField1e8;
        float fDelta = fScale - 1.0f;
        float fOffsetX = fDelta * fHeight * 0.5f;
        float fOffsetY = fDelta * fItemWidth * 0.5f;
        float fScaledWidth = fScale * fItemWidth;
        float fScaledHeight = fScale * fHeight;

        cSPUIWindow* pWinA = (cSPUIWindow*)VT_F0_2(pSel, 0x3dae410, 1);
        cVec4* pRectA = VT_38_0(pWinA);
        float fHeightA = pRectA->w - pRectA->y;

        cSPUIWindow* pWinB = (cSPUIWindow*)VT_F0_2(pSel, 0x3dae411, 1);
        cVec4* pRectB = VT_38_0(pWinB);
        float fHeightB = pRectB->w - pRectB->y;

        int nCount = (int)(mpAudioEndA8 - mpAudioBeginA4);
        const int& nMin = min_i(nMax, nCount);
        int nRows = max_i(nMin, 1);
        float fRows = (float)(u32)nRows;
        float fBaseY = fRows * fScaledHeight + fHeightB + fHeightA;

        cSPUIWindow* pHandle = mLayout1bc.FindWindowByID(0x3dae412, 1);
        cVec4* pRectH = VT_38_0(pHandle);
        float fHandleX = pRectH->x;
        float fHandleY = pRectH->y;
        float fHandleZ = pRectH->z;
        float fHandleW = pRectH->w;

        cVec4 mainArea;
        cVec4* pMain = GetMainWindowArea(&mainArea);
        float fHandleHeight = fHandleW - fHandleY;
        float fAvailable = ((pMain->w - pMain->y) - mField1dc) - fHandleHeight;

        if (fBaseY > fAvailable) {
            while (fRows > 1.0f) {
                fRows = fRows - 1.0f;
                fBaseY = fRows * fScaledHeight + fHeightB + fHeightA;
                if (!(fBaseY > fAvailable))
                    break;
            }
        }

        nCount = (int)(mpAudioEndA8 - mpAudioBeginA4);
        float fColumnCount = (float)floor(((double)(u32)nCount + fRows - 1.0f) / fRows);
        float fRowExtent = fColumnCount * fScaledWidth + fItemHeight;

        cVec4 v;
        v.z = fRowExtent;
        v.x = 0.0f;
        v.y = 0.0f;
        v.w = fBaseY;
        VT_6C_1(pOther, &v);
        v.x = 0.0f;
        v.y = 0.0f;
        v.w = fBaseY;
        VT_6C_1(pSel, &v);
        v.x = 0.0f;
        v.y = 0.0f;
        v.w = fHeightA;
        VT_6C_1(pWinA, &v);
        v.x = 0.0f;
        v.y = fBaseY - fHeightB;
        v.w = fBaseY;
        VT_6C_1(pWinB, &v);

        float fClipX;
        if (mFlag1ec != 0)
            fClipX = 0.0f;
        else
            fClipX = fRowExtent - (fHandleZ - fHandleX);
        VT_70_2F(pSel, fClipX, -fHandleHeight);

        float fY = fColumnCount - 1.0f;
        if (fY >= 0.0f) {
            int nItem = 0;
            bool bAlive = true;
            do {
                float fX;
                if (mFlag1ec != 0)
                    fX = (fColumnCount - 1.0f) - fY;
                else
                    fX = fY;
                float fAcc = 0.0f;
                if (fRows > 0.0f) {
                    do {
                        if (nItem >= (int)(mpItemEnd10 - mpItemBegin0c)) {
                            bAlive = false;
                            break;
                        }
                        void* pItem = mpItemBegin0c[nItem];
                        cSPUIWindow* pItemWin = ((cSPUILayout_s00e2_2860*)((char*)pItem + 0x7c))->FindWindowByID(0x3d98299, 1);
                        VT_70_2F(pItemWin, fX * fScaledWidth + fOffsetY, fAcc * fScaledHeight + fHeightA + fOffsetX);
                        fAcc += 1.0f;
                        ++nItem;
                    } while (fAcc < fRows);
                }
                fY -= 1.0f;
            } while (bAlive && fY >= 0.0f);
        }
    }

    if (bSnap)
        return;

    SnapToPosition();
    bool bVisible = false;
    if (mFlag1e4 != 0) {
        if (mFlag1e5 != 0 || mpAudioBeginA4 != mpAudioEndA8)
            bVisible = true;
    }
    VT_7C_2(pSel, 1, bVisible);
}

// @ 0x00e23130
void cSPUIPosse_s00e2_2860::SetScaleF(float scale)
{
    mField1e8 = SseClamp(scale, 0.25f, 1.0f);
    mFlag1d4 = 1;
    UpdateLayout(0);
}

// @ 0x00e231a0
bool cSPUIPosse_s00e2_2860::SetVisibility(void* window)
{
    if (VT_1C_0(window) != 0x3d98298)
        return false;
    if (mFlag1d4 != 0)
        UpdateLayout(0);
    cAnimatorFrame frame;
    BuildAnimatorRect(&frame.mFirst, &frame.mSecond);
    mpAnimator208->Update();
    return true;
}

// @ 0x00e23200
void cSPUIPosse_s00e2_2860::SetScale(int scale)
{
    mFlag1e4 = scale;
    cSPUIWindow* window = mLayout1bc.FindWindowByID(0x3d98298, 1);
    if (window != 0) {
        VT_7C_2(window, 1, scale);
        if ((u8)scale != 0) {
            mFlag1d4 = 1;
            UpdateLayout(0);
        }
    }
}

// @ 0x00e235e0
void cSPUIPosse_s00e2_2860::SetWindowImages(void* image)
{
    cSPUIWindow* window = mLayout7c.FindWindowByID(0x3d99184, 1);
    if (window != 0) {
        void* holder = VT_F0_2(window, 0x56bd1b8, 1);
        if (holder != 0) {
            void* obj = VT_0C_1(holder, 0x105a93d);
            if (obj != 0)
                VT_14_1(obj, (int)image);
        }
        cSPUIWindow* window2 = mLayout7c.FindWindowByID(0x3d99185, 1);
        if (window2 != 0) {
            void* obj = VT_0C_1(window2, 0x105a93d);
            if (obj != 0)
                VT_14_1(obj, (int)image);
        }
    }
}

// @ 0x00e23670
int cSPUIPosse_s00e2_2860::GetWindowImageCount()
{
    return (mpField50 != 0) + 1;
}

// @ 0x00e23680
void cSPUIPosse_s00e2_2860::GetWindowImageRange(int* out)
{
    *out = mpField50 ? 0 : -1;
    out[1] = -1;
}

// @ 0x00e236a0
void cSPUIPosse_s00e2_2860::ClearToolWindow(int a, int b)
{
    if (mpField50 != 0)
        SetToolWindowState(a, b);
}

// @ 0x00e236b0
void cSPUIPosse_s00e2_2860::ClearToolWindowOne(int a)
{
    if (mpField50 != 0)
        RefreshToolWindow(a);
}

// @ 0x00e236c0
void cSPUIPosse_s00e2_2860::SetWindowRect(const cVec3* rect, int unused)
{
    if (mpField50 != 0) {
        cVec3& target = mRect70;
        u32 x = *(const u32*)rect;
        cPossePart* part = mpPartD4;
        *(u32*)&target = x;
        ((u32*)&target)[1] = ((const u32*)rect)[1];
        ((u32*)&target)[2] = ((const u32*)rect)[2];
        void* image = VT_F0_2(part->mpField10, 0x3d99151, 1);
        SetWindowImage(image, &target, 0);
    }
}

// @ 0x00e23710
u8 __fastcall FUN_00e23710(void* self, void* dummy, void* hit, s32 mode)
{
  (void)dummy;
  if (mode != 1) return 0;
  u32 modState = FUN_008d2db0();
  Ref mSel = *(Ref*)((char*)self + 0x13c);
  u8 bit = (u8)((modState >> 1) & 1);
  if (mSel == 0) return 0;
  void* layoutObj = *(void**)((char*)self + 0xd4);
  void* subObj = *(void**)((char*)layoutObj + 0x10);
  void* other = (void*)((TFpii)(*(void***)subObj)[0xf0 / 4])(subObj, 0x614a0c4, (void*)1);
  if (*(u8*)((char*)self + 0xa1)) {
    u8 sel = (hit == (void*)mSel || hit == other) ? (u8)1 : (u8)0;
    *(u8*)((char*)self + 0xa1) = sel;
  }
  switch (*(s32*)((char*)self + 0x94) - 1) {
    case 0:
      if ((hit != (void*)mSel && hit != other) || *(u8*)((char*)self + 0xa2) || bit) break;
      ((TFvi)(*(void***)self)[0xb8 / 4])(self, 3);
      break;
    case 1:
      if ((hit != (void*)mSel && hit != other) || *(u8*)((char*)self + 0xa2) || bit) break;
      ((TFvi)(*(void***)self)[0xb8 / 4])(self, 4);
      break;
    case 2:
      if (hit == 0) break;
      if (hit == (void*)mSel || hit == other) break;
      if (((TFu)(*(void***)hit)[0x1c / 4])(hit) == 0x4acfcaf) break;
      ((TFvi)(*(void***)self)[0xb8 / 4])(self, 1);
      break;
    case 3:
      if (hit == 0) {
        ((TFvi)(*(void***)self)[0xb8 / 4])(self, 2);
        break;
      }
      if (hit == (void*)mSel || hit == other) break;
      if (((TFu)(*(void***)hit)[0x1c / 4])(hit) == 0x4acfcaf) break;
      ((TFvi)(*(void***)self)[0xb8 / 4])(self, 2);
      break;
  }
  return 0;
}

// @ 0x00e23870
void __stdcall FUN_00e23870(void* begin, void* end)
{
  for (void* p = begin; (u32)p < (u32)end; p = (char*)p + 8) {
    Ref b = *(Ref*)((char*)p + 4);
    if (b) ((TFv)(*(void***)b)[1])(b);
    Ref a = *(Ref*)((char*)p);
    if (a) ((TFv)(*(void***)a)[1])(a);
  }
}

struct IRef_e238b0 { virtual int AddRef(); };

// @ 0x00e238b0
void __cdecl FUN_00e238b0(void* dst, u32 n, void* src)
{
  Ref* cur = (Ref*)dst;
  for (; n > 0; --n, cur += 2) {
    if (cur) {
      Ref a = *(Ref*)src;
      cur[0] = a;
      if (a) ((IRef_e238b0*)a)->AddRef();
      Ref b = *(Ref*)((char*)src + 4);
      cur[1] = b;
      if (b) ((IRef_e238b0*)b)->AddRef();
    }
  }
}

// @ 0x00e23900
void* __cdecl FUN_00e23900(void* first, void* last, void* out)
{
  if (first != last) {
    do {
      if (out) {
        Ref a = *(Ref*)first;
        *(Ref*)out = a;
        if (a) ((TFv)(*(void***)a)[0])(a);
        Ref b = *(Ref*)((char*)first + 4);
        *(Ref*)((char*)out + 4) = b;
        if (b) ((TFv)(*(void***)b)[0])(b);
      }
      first = (char*)first + 8;
      out = (char*)out + 8;
    } while (first != last);
  }
  return out;
}

// @ 0x00e23950
void* __cdecl FUN_00e23950(void* first, void* last, void* out)
{
  if (first != last) {
    do {
      Ref b = *(Ref*)((char*)first + 4);
      if (b) ((TFv)(*(void***)b)[1])(b);
      Ref a = *(Ref*)first;
      if (a) ((TFv)(*(void***)a)[1])(a);
      first = (char*)first + 8;
      out = (char*)out + 8;
    } while (first != last);
  }
  return out;
}

// @ 0x00e239a0
void __fastcall FUN_00e239a0(void* self, void* dummy, s32 idx, s32 level)
{
  (void)dummy;
  ((TFv)(*(void***)self)[0xd8 / 4])(self);
  *(s32*)((char*)self + 0xa8 + (idx - 1) * 4) = level;
  s32 distress0 = *(s32*)((char*)self + 0xa8);
  u8 flag = ((TFb)(*(void***)self)[0xb4 / 4])(self);
  u8 b3 = (u8)(distress0 == 2);
  if (flag) {
    ((PosseItemC*)self)->SetBlinkerMotive(1, (u8)(*(s32*)((char*)self + 0xa8) == 2));
  }
  u8 b4 = b3;
  if (!b3 && *(s32*)((char*)self + 0xa8) != 2) b4 = 0;
  ((PosseItemC*)self)->SetBlinkerMotive(0, (u8)(*(s32*)((char*)self + 0xa8) == 2));
  if (!b4) return;
  if (*(float*)((char*)self + 0xd0) == *(float*)0x1485378) {
    *(float*)((char*)self + 0xc8) = *(float*)0x13eb95c;
    *(float*)((char*)self + 0xd0) = FUN_00805080_f();
  }
  s32 st = *(s32*)((char*)self + 0x94);
  if (st == 1 || st == 2) {
    *(float*)((char*)self + 0xc0) = *(float*)0x1485544;
    *(float*)((char*)self + 0xc4) = *(float*)0x1485720;
    *(s32*)((char*)self + 0xb8) = 0x60ff0000;
    *(s32*)((char*)self + 0xbc) = (s32)0xd0ff0000;
  } else {
    *(float*)((char*)self + 0xc0) = *(float*)0x1485720;
    *(s32*)((char*)self + 0xb8) = -1;
    *(s32*)((char*)self + 0xbc) = 0xffff3f00;
    *(float*)((char*)self + 0xc4) = *(float*)0x13ec4b4;
  }
}

// @ 0x00e23ae0
s32 __fastcall FUN_00e23ae0(void* self, void* dummy, u32 id)
{
  (void)dummy;
  void* pm = FUN_0067de30();
  if (DAT_016ac278) {
    void* old = DAT_016ac278;
    DAT_016ac278 = 0;
    ((TFv)(*(void***)old)[1])(old);
  }
  u8 ok = ((TFuii)(*(void***)pm)[0x30 / 4])(pm, 0x5c770db7, &DAT_016ac278);
  if (ok) {
    ((CopyImplC*)g_15a5524)->Copy(DAT_016ac278);
  }
  u8 r = ((SPUILayoutC*)((char*)self + 0x1bc))->Init(id, 1, 0x8d0f4fb);
  if (r) {
    if (((TFb)(*(void***)self)[0xcc / 4])(self)) return 1;
  }
  return 0;
}

// @ 0x00e23b70
s32 __fastcall FUN_00e23b70(void* self, void* dummy, void* name, int id)
{
  (void)dummy;
  void* pm = FUN_0067de30();
  if (DAT_016ac278) {
    void* old = DAT_016ac278;
    DAT_016ac278 = 0;
    ((TFv)(*(void***)old)[1])(old);
  }
  u8 ok = ((TFuii)(*(void***)pm)[0x30 / 4])(pm, 0x5c770db7, &DAT_016ac278);
  if (ok) {
    ((CopyImplC*)g_15a5524)->Copy(DAT_016ac278);
  }
  u8 r = ((SPUILayoutC*)((char*)self + 0x1bc))->InitStr(name, id, 1, 0x8d0f4fb);
  if (r) {
    if (((TFb)(*(void***)self)[0xcc / 4])(self)) return 1;
  }
  return 0;
}

// @ 0x00e23ca0
u8 __fastcall FUN_00e23ca0(void* self, void* dummy)
{
  (void)dummy;
  void* layout = (char*)self + 0x1bc;
  void* w;
  w = ((SPUILayoutC*)layout)->FindWindowByID(0x3dae410, 1);
  ((TFvi)(*(void***)w)[0xac / 4])(w, 0);
  ((TFvp)(*(void***)w)[0x104 / 4])(w, self);
  w = ((SPUILayoutC*)layout)->FindWindowByID(0x3dae411, 1);
  ((TFvi)(*(void***)w)[0xac / 4])(w, 0);
  ((TFvp)(*(void***)w)[0x104 / 4])(w, self);
  w = ((SPUILayoutC*)layout)->FindWindowByID(0x3d98298, 1);
  ((TFvp)(*(void***)w)[0x104 / 4])(w, self);
  w = ((SPUILayoutC*)layout)->FindWindowByID(0x3dae412, 1);
  ((TFvp)(*(void***)w)[0x104 / 4])(w, self);
  ((SPUIPosseC*)self)->SelectAll(0);
  return 1;
}

// @ 0x00e23d50
void __fastcall FUN_00e23d50(void* self, void* dummy)
{
  (void)dummy;
  void* sys = FUN_00e23250();
  void** vt = *(void***)self;
  void (*cb)(void) = FUN_00e21720;
  if (sys != 0) cb = FUN_00e21700;
  ((TFvpp)vt[0xa0 / 4])(self, (void*)cb, 0);
  void* at = FUN_00a206f0();
  u32 uVar3 = 0;
  if (at != 0) uVar3 = ((TFu)(*(void***)at)[0x20 / 4])(at);
  at = FUN_00a206f0();
  if (at) {
    ((TFvi)(*(void***)at)[0x38 / 4])(at, 0x3475365);
    ((TFvp)(*(void***)at)[0x40 / 4])(at, (void*)(u32)0xa715736e);
    ((TFvp)(*(void***)at)[0x40 / 4])(at, (void*)uVar3);
    ((TFv)(*(void***)at)[0x58 / 4])(at);
  }
}

// @ 0x00e23de0
void __fastcall FUN_00e23de0(void* self, void* dummy)
{
  (void)dummy;
  void** end = *(void***)((char*)self + 0x10);
  void** begin = *(void***)((char*)self + 0xc);
  while (end > begin) {
    if (((TFi)(*(void***)end[-1])[0xbc / 4])(end[-1]) == 3 ||
        ((TFi)(*(void***)end[-1])[0xbc / 4])(end[-1]) == 4) {
      ((TFv)(*(void***)end[-1])[0xa8 / 4])(end[-1]);
    }
    --end;
  }
}

// @ 0x00e23e30
void* __cdecl FUN_00e23e30(void* first, void* last, void* val, u8(__cdecl* pred)(void*, void*))
{
  s32 n = (s32)((char*)last - (char*)first) >> 3;
  while (n > 0) {
    s32 half = n >> 1;
    void* mid = (char*)first + half * 8;
    if (pred(mid, val)) {
      first = (char*)mid + 8;
      n = n - half - 1;
    } else {
      n = half;
    }
  }
  return first;
}

// @ 0x00e23e80
void* __fastcall FUN_00e23e80(void* self, void* dummy, void** src)
{
  (void)dummy;
  Ref old0 = *(Ref*)self;
  Ref new0 = *(Ref*)src;
  if (new0 != old0) {
    if (new0) ((TFv)(*(void***)new0)[0])(new0);
    *(Ref*)self = new0;
    if (old0) ((TFv)(*(void***)old0)[1])(old0);
  }
  Ref new1 = *(Ref*)((char*)src + 4);
  Ref old1 = *(Ref*)((char*)self + 4);
  if (new1 != old1) {
    if (new1) ((TFv)(*(void***)new1)[0])(new1);
    *(Ref*)((char*)self + 4) = new1;
    if (old1) ((TFv)(*(void***)old1)[1])(old1);
  }
  return self;
}

// @ 0x00e23ee0
void* __cdecl FUN_00e23ee0(void* first, void* last, u32* key)
{
  s32 n = (s32)((char*)last - (char*)first) >> 4;
  while (n > 0) {
    s32 half = n >> 1;
    void* mid = (char*)first + half * 16;
    if (*(u32*)mid < *key) {
      first = (char*)mid + 16;
      n = n - half - 1;
    } else {
      n = half;
    }
  }
  return first;
}

// @ 0x00e23f30
void __cdecl FUN_00e23f30(void* first, void* last, u8(__cdecl* pred)(void*, void*))
{
  if (first == last) return;
  for (void* cur = (char*)first + 8; cur != last; cur = (char*)cur + 8) {
    Ref local0 = *(Ref*)cur;
    if (local0) ((TFv)(*(void***)local0)[0])(local0);
    Ref local1 = *(Ref*)((char*)cur + 4);
    if (local1) ((TFv)(*(void***)local1)[0])(local1);
    void* hole = cur;
    while (hole != first) {
      void* prev = (char*)hole - 8;
      if (!pred(&local0, prev)) break;
      /* shift prev into hole */
      Ref os0 = *(Ref*)hole;
      Ref ns0 = *(Ref*)prev;
      if (ns0 != os0) {
        if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
        *(Ref*)hole = ns0;
        if (os0) ((TFv)(*(void***)os0)[1])(os0);
      }
      Ref os1 = *(Ref*)((char*)hole + 4);
      Ref ns1 = *(Ref*)((char*)prev + 4);
      if (ns1 != os1) {
        if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
        *(Ref*)((char*)hole + 4) = ns1;
        if (os1) ((TFv)(*(void***)os1)[1])(os1);
      }
      hole = prev;
    }
    /* place local into hole */
    Ref d0 = *(Ref*)hole;
    if (local0 != d0) {
      if (local0) ((TFv)(*(void***)local0)[0])(local0);
      *(Ref*)hole = local0;
      if (d0) ((TFv)(*(void***)d0)[1])(d0);
    }
    Ref d1 = *(Ref*)((char*)hole + 4);
    if (local1 != d1) {
      if (local1) ((TFv)(*(void***)local1)[0])(local1);
      *(Ref*)((char*)hole + 4) = local1;
      if (d1) ((TFv)(*(void***)d1)[1])(d1);
    }
    if (local1) ((TFv)(*(void***)local1)[1])(local1);
    if (local0) ((TFv)(*(void***)local0)[1])(local0);
  }
}

// @ 0x00e240b0
void __cdecl FUN_00e240b0(void* first, void* last, u8(__cdecl* pred)(void*, void*))
{
  for (void* cur = first; cur != last; cur = (char*)cur + 8) {
    Ref local0 = *(Ref*)cur;
    if (local0) ((TFv)(*(void***)local0)[0])(local0);
    Ref local1 = *(Ref*)((char*)cur + 4);
    if (local1) ((TFv)(*(void***)local1)[0])(local1);
    void* hole = (char*)cur - 8;
    u8 go = pred(&local0, hole);
    while (go) {
      Ref os0 = *(Ref*)cur;
      Ref ns0 = *(Ref*)hole;
      if (ns0 != os0) {
        if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
        *(Ref*)cur = ns0;
        if (os0) ((TFv)(*(void***)os0)[1])(os0);
      }
      Ref os1 = *(Ref*)((char*)cur + 4);
      Ref ns1 = *(Ref*)((char*)hole + 4);
      if (ns1 != os1) {
        if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
        *(Ref*)((char*)cur + 4) = ns1;
        if (os1) ((TFv)(*(void***)os1)[1])(os1);
      }
      cur = hole;
      hole = (char*)hole - 8;
      go = pred(&local0, hole);
    }
    Ref d0 = *(Ref*)cur;
    if (local0 != d0) {
      if (local0) ((TFv)(*(void***)local0)[0])(local0);
      *(Ref*)cur = local0;
      if (d0) ((TFv)(*(void***)d0)[1])(d0);
    }
    Ref d1 = *(Ref*)((char*)cur + 4);
    if (local1 != d1) {
      if (local1) ((TFv)(*(void***)local1)[0])(local1);
      *(Ref*)((char*)cur + 4) = local1;
      if (d1) ((TFv)(*(void***)d1)[1])(d1);
    }
    if (local1) ((TFv)(*(void***)local1)[1])(local1);
    if (local0) ((TFv)(*(void***)local0)[1])(local0);
  }
}

// @ 0x00e24220
void __cdecl FUN_00e24220(void* first, void* last, void* src)
{
  for (; first != last; first = (char*)first + 8) {
    Ref ns0 = *(Ref*)src;
    Ref os0 = *(Ref*)first;
    if (ns0 != os0) {
      if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
      *(Ref*)first = ns0;
      if (os0) ((TFv)(*(void***)os0)[1])(os0);
    }
    Ref ns1 = *(Ref*)((char*)src + 4);
    Ref os1 = *(Ref*)((char*)first + 4);
    if (ns1 != os1) {
      if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
      *(Ref*)((char*)first + 4) = ns1;
      if (os1) ((TFv)(*(void***)os1)[1])(os1);
    }
  }
}

// @ 0x00e24290
void* __cdecl FUN_00e24290(void* first, void* last, void* out)
{
  if (first != last) {
    do {
      Ref ns0 = *(Ref*)first;
      Ref os0 = *(Ref*)out;
      if (ns0 != os0) {
        if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
        *(Ref*)out = ns0;
        if (os0) ((TFv)(*(void***)os0)[1])(os0);
      }
      Ref ns1 = *(Ref*)((char*)first + 4);
      Ref os1 = *(Ref*)((char*)out + 4);
      if (ns1 != os1) {
        if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
        *(Ref*)((char*)out + 4) = ns1;
        if (os1) ((TFv)(*(void***)os1)[1])(os1);
      }
      first = (char*)first + 8;
      out = (char*)out + 8;
    } while (first != last);
  }
  return out;
}

struct RefPairIter_e24310 {
  Ref* p;
  RefPairIter_e24310(const RefPairIter_e24310& o) : p(o.p) {}
  bool operator!=(const RefPairIter_e24310& o) const { return p != o.p; }
  RefPairIter_e24310& operator++() { p += 2; return *this; }
};

// @ 0x00e24310
void* __cdecl FUN_00e24310(void** out, RefPairIter_e24310 first, RefPairIter_e24310 last, void* val)
{
  *out = val;
  for (; first != last; ++first) {
    Ref* dst = (Ref*)*out;
    if (dst) {
      Ref* src = first.p;
      Ref a = src[0];
      dst[0] = a;
      if (a) ((TFv)(*(void***)a)[0])(a);
      Ref b = src[1];
      dst[1] = b;
      if (b) ((TFv)(*(void***)b)[0])(b);
    }
    *out = (void*)((char*)*out + 8);
  }
  return out;
}

// @ 0x00e24370
void* __cdecl FUN_00e24370(void* first, void* last, void* out)
{
  if (last == first) return out;
  do {
    void* src = (char*)last - 8;
    void* dst = (char*)out - 8;
    last = src;
    out = dst;
    Ref ns0 = *(Ref*)src;
    Ref os0 = *(Ref*)dst;
    if (ns0 != os0) {
      if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
      *(Ref*)dst = ns0;
      if (os0) ((TFv)(*(void***)os0)[1])(os0);
    }
    Ref ns1 = *(Ref*)((char*)src + 4);
    Ref os1 = *(Ref*)((char*)dst + 4);
    if (ns1 != os1) {
      if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
      *(Ref*)((char*)dst + 4) = ns1;
      if (os1) ((TFv)(*(void***)os1)[1])(os1);
    }
  } while (last != first);
  return out;
}

// @ 0x00e243f0
void __cdecl FUN_00e243f0(void* base, s32 start, s32 pos, void* v0, void* v1, u8(__cdecl* pred)(void*, void*))
{
  s32 child;
  while (start < pos) {
    child = (pos - 1) >> 1;
    if (!pred((char*)base + child * 8, &v0)) break;
    {
      void* dst = (char*)base + pos * 8;
      Ref ns0 = *(Ref*)((char*)base + child * 8);
      Ref os0 = *(Ref*)dst;
      if (ns0 != os0) {
        if (ns0) ((TFv)(*(void***)ns0)[0])(ns0);
        *(Ref*)dst = ns0;
        if (os0) ((TFv)(*(void***)os0)[1])(os0);
      }
      Ref ns1 = *(Ref*)((char*)base + child * 8 + 4);
      Ref os1 = *(Ref*)((char*)dst + 4);
      if (ns1 != os1) {
        if (ns1) ((TFv)(*(void***)ns1)[0])(ns1);
        *(Ref*)((char*)dst + 4) = ns1;
        if (os1) ((TFv)(*(void***)os1)[1])(os1);
      }
    }
    pos = child;
  }
  {
    void* dst = (char*)base + pos * 8;
    Ref os0 = *(Ref*)dst;
    if (v0 != os0) {
      if (v0) ((TFv)(*(void***)v0)[0])(v0);
      *(Ref*)dst = v0;
      if (os0) ((TFv)(*(void***)os0)[1])(os0);
    }
    Ref os1 = *(Ref*)((char*)dst + 4);
    if (v1 != os1) {
      if (v1) ((TFv)(*(void***)v1)[0])(v1);
      *(Ref*)((char*)dst + 4) = v1;
      if (os1) ((TFv)(*(void***)os1)[1])(os1);
    }
  }
  if (v1) ((TFv)(*(void***)v1)[1])(v1);
  if (v0) ((TFv)(*(void***)v0)[1])(v0);
}

// @ 0x00e245c0
void __cdecl FUN_00e245c0(void* a, void* b)
{
  Ref t0 = *(Ref*)a;
  if (t0) ((TFv)(*(void***)t0)[0])(t0);
  Ref t1 = *(Ref*)((char*)a + 4);
  if (t1) ((TFv)(*(void***)t1)[0])(t1);
  ((TFpp)FUN_00e23e80)(b, &t0);
  ((TFpp)FUN_00e23e80)(a, &t0);
  if (t1) ((TFv)(*(void***)t1)[1])(t1);
  if (t0) ((TFv)(*(void***)t0)[1])(t0);
}

// @ 0x00e24630
void __fastcall FUN_00e24630(void* self, void* dummy)
{
  (void)dummy;
  *(void**)self = (void*)0x14805b8;
  *(void**)((char*)self + 4) = (void*)0x148059c;
  *(void**)((char*)self + 0xc) = (void*)0x148058c;
  Ref r = *(Ref*)((char*)self + 0x13c);
  if (r) ((TFv)(*(void***)r)[1])(r);
  void* arr = *(void**)((char*)self + 0x124);
  if (arr) FUN_00f47380(arr);
  ((Vec2bC*)((char*)self + 0x100))->Free();
  ((Vec2bC*)((char*)self + 0xd4))->Free();
  Ref s = *(Ref*)((char*)self + 0x9c);
  if (s) ((TFv)(*(void***)s)[1])(s);
  ((LayoutDtorC*)((char*)self + 0x7c))->Dtor();
  Ref m = *(Ref*)((char*)self + 0x50);
  if (m) ((TFv)(*(void***)m)[1])(m);
  *(void**)((char*)self + 0xc) = (void*)0x13eb394;
  *(void**)((char*)self + 4) = (void*)0x13eb938;
  *(void**)self = (void*)0x13eb938;
}

// @ 0x00e24700
void cSPUIPosseItem_s00e2_4700::FUN_00e24700(int state)
{
  int old = mField94;
  ((FnVoidI)mpVtable->slot[0xd0 / 4])(this, state);
  if (old != state) {
    if (((FnInt0)mpVtable->slot[0xc4 / 4])(this) != 0) {
      Msg40* msg = new ("UI", 0, 0, 0, 0) Msg40(0x3deb129);
      if (msg)
        msg->AddRef();
      uint32_t v = (uint32_t)((FnInt0)mpVtable->slot[0xc4 / 4])(this);
      msg->SetIRefCount(0, v);
      uint32_t flags = 0;
      if (state == 2 || state == 4)
        flags = 1;
      if (state == 3 || state == 4)
        flags |= 2;
      msg->mData[2] = flags;
      MessageServer()->MessageSend(msg->mId, msg, 0, 0);
      msg->Release();
    }
  }
}

// @ 0x00e247f0
void cSPUIPosseItem_s00e2_4700::FUN_00e247f0(int param_2, MsgIn* param_3)
{
  if (param_3->mField08 == 0x287259f6 && param_3->mField0c == 0x4acfcaf) {
    MessageServer()->MessageSend(0x4e54d0c, 0, 0, 0);
    Msg40* msg = new ("UI", 0, 0, 0, 0) Msg40(0x14051500);
    msg->mData[0] = (uint32_t)mField50;
    msg->SetIRefCount(4, (uint32_t)mField50);
    MessageServer()->MessageSend(0x14051500, msg, 0, 0);
  }
  FUN_00950ef0(param_2, param_3);
}

// @ 0x00e248b0
char cSPUIPosse_s00e2_4700::FUN_00e248b0(int param_2, float param_3, float param_4, int param_5, int param_6)
{
  uint32_t recent = (param_5 == mField144) && ((GetElapsedSeconds() - mField148) < g_clickThreshold);
  mField140 = (uint8_t)recent;
  mField148 = GetElapsedSeconds();
  mField144 = param_5;
  if (param_5 == 1000) {
    if (mField13c == param_2) {
      WindowMgr* wm = WindowManager_s00e2_4700();
      ((FnVoidII)wm->mpVtable->slot[0x58 / 4])(wm, 1, param_2);
    }
    int held = (param_6 & 3) != 0;
    mFieldA2 = 1;
    mFieldA3 = (uint8_t)held;
    if (!held)
      ((FnVoid0)mpVtable->slot[0xe0 / 4])(this);
    switch (mField94) {
    case 1:
    case 3:
      mFieldA1 = 1;
      ((FnVoidI)mpVtable->slot[0xb8 / 4])(this, 2);
      break;
    case 2:
      mFieldA1 = 1;
      if (mFieldA3)
        ((FnVoidI)mpVtable->slot[0xb8 / 4])(this, 1);
      break;
    case 4:
      mFieldA1 = 1;
      if (mFieldA3)
        ((FnVoidI)mpVtable->slot[0xb8 / 4])(this, 1);
      else
        ((FnVoidI)mpVtable->slot[0xb8 / 4])(this, 2);
      break;
    }
    uint32_t r = ((FnU32_0)mpVtable->slot[0xbc / 4])(this);
    mFieldA4 = (ItemNode*)r;
    return 0;
  }
  if (param_5 == 0x3ea) {
    Msg40* msg = new ("UI", 0, 0, 0, 0) Msg40(0x3deb12a);
    if (msg)
      msg->AddRef();
    uint32_t v = ((FnU32_0)mpVtable->slot[0xc4 / 4])(this);
    msg->SetIRefCount(0, v);
    MessageServer()->MessageSend(msg->mId, msg, 0, 0);
    msg->Release();
  }
  return 0;
}

// @ 0x00e24a50
Object_s00e2_4a50::~Object_s00e2_4a50()
{
    delete mpOwned;
    mpOwned = 0;
}

// @ 0x00e24b10
char cSPUIPosse_s00e2_4700::FUN_00e24b10()
{
  void* pending = g_pMsgRef;
  if (pending) {
    g_pMsgRef = 0;
    ((FnVoid0)(((void**)*(void**)pending)[1]))(pending);
  }
  if (mFieldA8 != mFieldA4) {
    do {
      void* item = mFieldA8[-1].mField04;
      ((FnVoid0)(((void**)*(void**)item)[0xcc / 4]))(item);
      mFieldA8 -= 1;
      ItemNode* e = mFieldA8;
      void* f4 = e->mField04;
      if (f4)
        ((FnVoid0)(((void**)*(void**)f4)[1]))(f4);
      void* f0 = e->mField00;
      if (f0)
        ((FnVoid0)(((void**)*(void**)f0)[1]))(f0);
    } while (mFieldA8 != mFieldA4);
  }
  mLayout.Shutdown(1);
  return 1;
}

// @ 0x00e24c90
void* cSPUIPosse_s00e2_4700::FUN_00e24c90(int id)
{
  ItemNode* n = find_item(id);
  if (n != mFieldA8)
    return n->mField04;
  return 0;
}

// @ 0x00e24cc0
char cSPUIPosse_s00e2_4700::FUN_00e24cc0(void* p2, void* p3, void* p4, void* p5, void* p6)
{
  if (p2 == mLayout.FindWindowByID(0x3dae410, 1) ||
      p2 == mLayout.FindWindowByID(0x3dae411, 1))
    toggle_select_all();
  return 0;
}

// @ 0x00e24d10
void FUN_00e24d10(uint32_t nID, void* pValue)
{
    RefPtr<cPropertyList> pList;
    RefPtr<cPropertyList> pOwner;
    uint32_t nZero;
    float    vecZero[3];
    Variant  value;

    cPropListFactory* pFactory = PropListFactory();

    // Lists are re-created from scratch: the slot is cleared first.
    pList.reset();
    pFactory->Create(&pList.mpObject);
    pOwner.reset();
    pFactory->Create(&pOwner.mpObject);

    {
        cPropertyList* pTarget = pList.mpObject;
        value.mFlags = 0;
        value.mType = 0;
        value.SetPointer(pValue);
        pTarget->SetValue(0, value);
        if (value.mFlags & 4) value.Destruct(0);
    }
    {
        cPropertyList* pTarget = pList.mpObject;
        nZero = 0;
        value.mFlags = 0;
        value.mType = 0;
        value.SetU32(&nZero);
        pTarget->SetValue(1, value);
        if (value.mFlags & 4) value.Destruct(0);
    }
    {
        cPropertyList* pTarget = pList.mpObject;
        vecZero[0] = 0.0f;
        vecZero[1] = 0.0f;
        vecZero[2] = 0.0f;
        value.mFlags = 0;
        value.mType = 0;
        value.SetVec3(vecZero);
        pTarget->SetValue(3, value);
        if (value.mFlags & 4) value.Destruct(0);
    }

    pFactory->Submit(nID, pList.mpObject, pOwner.mpObject);

    // Slots are released in reverse declaration order, as destructors would.
    pOwner.release();
    pList.release();
}

// @ 0x00e24eb0
char cSPUIPosse_s00e2_4700::FUN_00e24eb0(int p2, float p3, float p4, int p5, int p6)
{
  char r = FUN_00e248b0(p2, p3, p4, p5, p6);
  if (mField140 != 0 && p5 == 1000)
    FUN_00e24d10(0x6204441, mField50);
  return r;
}

// @ 0x00e24f10
char cSPUIPosseItemTribeBaby_s00e2_4f10::DoMessage(void* win, MsgIn_s00e2_4f10* msg)
{
  if (((FnU32_0_s00e2_4f10)VT_s00e2_4f10(win)->slot[0x1c / 4])(win) == 0x3dea7f0u &&
      msg->mField08 == 13) {
    void* ctx = msg->mField18;
    void* image = sGetWindowImage(win);
    if (image) {
      ((FnVoid0_s00e2_4f10)VT_s00e2_4f10(image)->slot[0])(image);

      void* batch = ((RenderContext_s00e2_4f10*)ctx)->Begin2D(0);

      RectF_s00e2_4f10* rc =
          ((RectF_s00e2_4f10* (__thiscall*)(void*))VT_s00e2_4f10(win)->slot[0x38 / 4])(win);
      Point2_s00e2_4f10 topLeft(rc->mLeft, rc->mTop);
      Point2_s00e2_4f10 bottomRight(rc->mRight, rc->mBottom);
      float w = bottomRight.mX - topLeft.mX;
      float h = bottomRight.mY - topLeft.mY;

      FUN_00e23340(batch, w * 0.5f, h * 0.5f, w, h, -1, -1, g_015a547c,
                   (1.0f - mControlValue01) * g_016ac2cc + g_015a547c, image, 0.05f);

      ((RenderContext_s00e2_4f10*)ctx)->End2D();
      ((FnVoid0_s00e2_4f10)VT_s00e2_4f10(image)->slot[1])(image);
      return 1;
    }
  }
  return cSPUIPosseItem_s00e2_4f10::DoMessage(win, msg);
}

// @ 0x00e250a0
char cSPUIPosse_s00e2_4700::FUN_00e250a0(int p2, float p3, float p4, int p5, int p6)
{
  char r = FUN_00e248b0(p2, p3, p4, p5, p6);
  if (mField140 != 0 && p5 == 1000)
    FUN_00e24d10(0x346048a, mField50);
  return r;
}

// @ 0x00e25120
char cSPUIPosse_s00e2_4700::FUN_00e25120(int p2, float p3, float p4, int p5, int p6)
{
  if (mField50 != 0)
    return FUN_00e248b0(p2, p3, p4, p5, p6);
  return 1;
}

// @ 0x00e251c0
char __stdcall FUN_00e251c0(void* p2, void* p3, void* p4, void* p5, void* p6)
{
  Msg40* msg = new ("UI", 0, 0, 0, 0) Msg40(0x337f07d8);
  if (msg)
    msg->AddRef();
  MessageServer()->MessageSend(msg->mId, msg, 0, 0);
  msg->Release();
  return 1;
}

// @ 0x00e25240
void __cdecl FUN_00e25240(Pair* first, s32 topIndex, s32 len, s32 holeIndex, Pair value, TPred compare)
{
  s32 child = 2 * holeIndex + 2;
  while (child < len) {
    if (compare(&first[child], &first[child - 1])) --child;
    first[holeIndex] = first[child];
    holeIndex = child;
    child = 2 * child + 2;
  }
  if (child == len) {
    first[holeIndex] = first[child - 1];
    holeIndex = child - 1;
  }
  FUN_00e243f0(first, topIndex, holeIndex, value, compare);
}

// @ 0x00e253c0
void __cdecl FUN_00e253c0(Pair_s00e2_53c0* first, Pair_s00e2_53c0* last, TPred_s00e2_53c0 compare)
{
  Pair_s00e2_53c0* tail = last - 1;
  Pair_s00e2_53c0 value = *tail;
  ((TFpp)FUN_00e23e80)(tail, (void**)first);
  FUN_00e25240(first, 0, (s32)(last - first) - 1, 0, value, compare);
}

// @ 0x00e25460
void* cSPUIPosse_s00e25460::ctor(void* pOwner, const u32* pKey)
{
  // inlined base constructors, then the derived vptrs
  *(void* volatile*)((char*)this + 4) = (void*)g_13fa72c;
  *(u32* volatile*)((char*)this + 8) = 0;
  *(void* volatile*)((char*)this + 0xc) = (void*)g_13eb384;
  *(void**)((char*)this)      = (void*)g_14805b8;
  *(void**)((char*)this + 4)  = (void*)g_148059c;
  *(void**)((char*)this + 0xc) = (void*)g_148058c;

  // owner reference
  *(void**)((char*)this + 0x50) = pOwner;
  if (pOwner)
    ((TFv_s00e2_5460)(*(void***)pOwner)[0])(pOwner);

  // resource key (three dwords)
  *(u32*)((char*)this + 0x54) = pKey[0];
  *(u32*)((char*)this + 0x58) = pKey[1];
  *(u32*)((char*)this + 0x5c) = pKey[2];

  // zeroed slots around the embedded layout object
  *(u32*)((char*)this + 0x60) = 0;
  *(u32*)((char*)this + 0x64) = 0;
  *(u32*)((char*)this + 0x68) = 0;
  *(u32*)((char*)this + 0x6c) = 0;

  _ReadWriteBarrier();

  *(u32*)((char*)this + 0x70) = 0;
  *(u32*)((char*)this + 0x74) = 0;
  *(u32*)((char*)this + 0x78) = 0;

  ((LayoutCtorC*)((char*)this + 0x7c))->ctor();

  *(u32*)((char*)this + 0x94) = 0;
  *(u32*)((char*)this + 0x98) = ++*(u32*)g_16ac238;    // global monotonic id
  *(u32*)((char*)this + 0x9c) = 0;
  *(u8*) ((char*)this + 0xa1) = 0;
  *(u8*) ((char*)this + 0xa2) = 0;
  *(u8*) ((char*)this + 0xa3) = 0;
  *(u32*)((char*)this + 0xb4) = 0;
  *(u8*) ((char*)this + 0xa0) = 1;
  *(float*)((char*)this + 0xb0) = 0.0f;
  *(float*)((char*)this + 0xd0) = 0.0f;

  _ReadWriteBarrier();

  // inline-buffer vector A: buffer at +0xec, 0x14 bytes
  {
    void* pBufA = (char*)this + 0xec;
    *(void**)((char*)this + 0xe4) = pBufA;
    *(void**)((char*)this + 0xd8) = pBufA;
    *(void**)((char*)this + 0xd4) = pBufA;
    *(void**)((char*)this + 0xdc) = (char*)pBufA + 0x14;
  }

  // inline-buffer vector B: buffer at +0x118, 0xc bytes
  {
    void* pBufB = (char*)this + 0x118;
    *(void**)((char*)this + 0x110) = pBufB;
    *(void**)((char*)this + 0x104) = pBufB;
    *(void**)((char*)this + 0x100) = pBufB;
    *(void**)((char*)this + 0x108) = (char*)pBufB + 0xc;
  }

  *(u32*)((char*)this + 0x124) = 0;
  *(u32*)((char*)this + 0x128) = 0;
  *(u32*)((char*)this + 0x12c) = 0;
  *(u32*)((char*)this + 0x13c) = 0;
  *(u8*) ((char*)this + 0x140) = 0;
  *(u32*)((char*)this + 0x144) = 0;
  *(float*)((char*)this + 0x148) = 0.0f;

  _ReadWriteBarrier();

  *(u32*)((char*)this + 0xa8) = 0;
  *(u32*)((char*)this + 0xac) = 0;

  return this;
}

// @ 0x00e255c0
void* cSPUIPosseItem_s00e255c0::ctor(void* pOwner, const void* pName, u32 typeId)
{
  // inlined base constructors, then the derived vptrs
  *(void* volatile*)((char*)this + 4) = (void*)g_13fa72c;
  *(u32* volatile*)((char*)this + 8) = 0;
  *(void* volatile*)((char*)this + 0xc) = (void*)g_13eb384;
  *(void**)((char*)this)      = (void*)g_14805b8;
  *(void**)((char*)this + 4)  = (void*)g_148059c;
  *(void**)((char*)this + 0xc) = (void*)g_148058c;

  // owner reference
  *(void**)((char*)this + 0x50) = pOwner;
  if (pOwner)
    ((TFv_s00e2_55c0)(*(void***)pOwner)[0])(pOwner);

  // hashed name key, caller type id, class type constant
  u32 nameKey = FNV1_String16(pName, 0x811c9dc5, 1);
  *(u32 volatile*)((char*)this + 0x5c) = typeId;
  *(u32 volatile*)((char*)this + 0x54) = nameKey;
  *(u32 volatile*)((char*)this + 0x58) = 0x510a95b;

  // zeroed slots around the embedded layout object
  *(u32 volatile*)((char*)this + 0x60) = 0;
  *(u32 volatile*)((char*)this + 0x64) = 0;
  *(u32 volatile*)((char*)this + 0x68) = 0;
  *(u32 volatile*)((char*)this + 0x6c) = 0;

  _ReadWriteBarrier();

  *(u32 volatile*)((char*)this + 0x70) = 0;
  *(u32*)((char*)this + 0x74) = 0;
  *(u32*)((char*)this + 0x78) = 0;

  ((LayoutCtorC*)((char*)this + 0x7c))->ctor();

  *(u32*)((char*)this + 0x94) = 0;
  *(u32*)((char*)this + 0x98) = ++*(u32*)g_16ac238;    // global monotonic id
  *(u32*)((char*)this + 0x9c) = 0;
  *(u8*) ((char*)this + 0xa1) = 0;
  *(u8*) ((char*)this + 0xa2) = 0;
  *(u8*) ((char*)this + 0xa3) = 0;
  *(u32*)((char*)this + 0xb4) = 0;
  *(u8*) ((char*)this + 0xa0) = 1;
  *(float*)((char*)this + 0xb0) = 0.0f;
  *(float*)((char*)this + 0xd0) = 0.0f;

  _ReadWriteBarrier();

  // inline-buffer vector A: buffer at +0xec, 0x14 bytes
  {
    void* pBufA = (char*)this + 0xec;
    *(void**)((char*)this + 0xe4) = pBufA;
    *(void**)((char*)this + 0xd8) = pBufA;
    *(void**)((char*)this + 0xd4) = pBufA;
    *(void**)((char*)this + 0xdc) = (char*)pBufA + 0x14;
  }

  // inline-buffer vector B: buffer at +0x118, 0xc bytes
  {
    void* pBufB = (char*)this + 0x118;
    *(void**)((char*)this + 0x110) = pBufB;
    *(void**)((char*)this + 0x104) = pBufB;
    *(void**)((char*)this + 0x100) = pBufB;
    *(void**)((char*)this + 0x108) = (char*)pBufB + 0xc;
  }

  *(u32*)((char*)this + 0x124) = 0;
  *(u32*)((char*)this + 0x128) = 0;
  *(u32*)((char*)this + 0x12c) = 0;
  *(u32*)((char*)this + 0x13c) = 0;
  *(u8*) ((char*)this + 0x140) = 0;
  *(u32*)((char*)this + 0x144) = 0;
  *(float*)((char*)this + 0x148) = 0.0f;

  _ReadWriteBarrier();

  *(u32*)((char*)this + 0xa8) = 0;
  *(u32*)((char*)this + 0xac) = 0;

  return this;
}

// @ 0x00e25710
void* cUIPosse15::ctor()
{
  char* s = (char*)this;
  *(void**)(s + 4) = (void*)0x13fa72c;
  *(void**)s = (void*)0x14806b8;
  *(void**)(s + 4) = (void*)0x148069c;
  char* p24 = s + 0x24;
  *(void**)(s + 8) = 0;
  *(void**)(s + 0x1c) = p24;
  *(void**)(s + 0x10) = p24;
  *(void**)(s + 0xc) = p24;
  *(void**)(s + 0x14) = p24 + 0x80;
  char* pbc = s + 0xbc;
  *(void**)(s + 0xb4) = pbc;
  *(void**)(s + 0xa8) = pbc;
  *(void**)(s + 0xa4) = pbc;
  *(void**)(s + 0xac) = pbc + 0x100;
  FUN_00e255c0_dlg(s + 0x1bc);
  *(unsigned char*)(s + 0x1d4) = 1;
  *(float*)(s + 0x1d8) = 0.0f;
  *(float*)(s + 0x1dc) = 1.0f;
  *(unsigned char*)(s + 0x1e4) = 1;
  *(unsigned char*)(s + 0x1ec) = 1;
  *(int*)(s + 0x1e0) = -1;
  *(unsigned char*)(s + 0x1e5) = 0;
  *(float*)(s + 0x1e8) = 1.0f;
  *(int*)(s + 0x1f0) = 0;
  *(int*)(s + 0x1f4) = 0;
  *(int*)(s + 0x1f8) = 0x1667bac;
  *(int*)(s + 0x1fc) = 0x1667bac;
  *(int*)(s + 0x200) = 0x1667bae;
  void* a = operator_new(0x20, (const char*)0x13f6b3c, 0, 0, 0, 0);
  *(void**)(s + 0x208) = a ? FUN_007f83e0(a) : 0;
  return this;
}

// @ 0x00e25840
void* cSPUIPosseItemTribe_s00e2_5710::ctor(int a2)
{
  cSPUIPosseItemBase::ctor(a2, L"PosseItemTribe", 0x40464100);
  *(void**)this = (void*)g_14807b0;
  *(void**)((char*)this + 4) = (void*)g_1480798;
  *(void**)((char*)this + 0xc) = (void*)g_1480788;
  this->f14c = 1.0f;
  return this;
}

// @ 0x00e258d0
void* cSPUIPosseItemTribeBaby_s00e2_5710::ctor(int a2)
{
  cSPUIPosseItemBase::ctor(a2, L"PosseItemTribeBaby", 0x40464100);
  *(void**)this = (void*)g_14808c0;
  *(void**)((char*)this + 4) = (void*)g_14808a4;
  *(void**)((char*)this + 0xc) = (void*)g_1480894;
  this->f14c = 0.0f;
  return this;
}

// @ 0x00e25950
void* cSPUIPosseItemCiv::ctor(int a2)
{
  cSPUIPosseItemBase::ctor(a2, L"PosseItemCiv", 0x40464100);
  *(void**)this = (void*)g_14809d0;
  *(void**)((char*)this + 4) = (void*)g_14809b4;
  *(void**)((char*)this + 0xc) = (void*)g_14809a4;
  return this;
}

// @ 0x00e259d0
void* cSPUIPosseItemSpace_s00e2_5710::ctor(int a2)
{
  cSPUIPosseItemBase::ctor(a2, a2 ? L"PosseItemSpace" : L"PosseItemSpaceGhostShell", 0x40464100);
  *(void**)this = (void*)g_1480ae0;
  *(void**)((char*)this + 4) = (void*)g_1480ac4;
  *(void**)((char*)this + 0xc) = (void*)g_1480ab4;
  if (a2 == 0) this->mState = 0x7fffffff;
  return this;
}

// @ 0x00e25a60
void* cSPUIPosseItem2_s00e2_5710::ctor(int a2, int a3)
{
  cScenarioEditPosseItemBase::ctor(a2, a3);
  *(void**)this = (void*)g_1480bf0;
  *(void**)((char*)this + 4) = (void*)g_1480bd4;
  *(void**)((char*)this + 0xc) = (void*)g_1480bc4;
  return this;
}

// @ 0x00e25ad0
void* cSPUIPosseItem3::ctor(int a2)
{
  cScenarioEditPosseItemBase::ctor(0, a2);
  *(void**)this = (void*)g_1480d00;
  *(void**)((char*)this + 4) = (void*)g_1480ce4;
  *(void**)((char*)this + 0xc) = (void*)g_1480cd4;
  *(int*)((char*)this + 0x98) = 0x7fffffff;
  return this;
}

// @ 0x00e25b50
void* cSPUIPosseItemTribeGhostShell::ctor()
{
  cSPUIPosseItemBase::ctor(0, L"PosseItemTribeGhostShell", 0x40464100);
  *(void**)this = (void*)g_1480e10;
  *(void**)((char*)this + 4) = (void*)g_1480df4;
  *(void**)((char*)this + 0xc) = (void*)g_1480de4;
  this->mState = 0x7fffffff;
  return this;
}

// @ 0x00e25bd0
void* cVec15::f(void** First, void** Last)
{
  char* s = (char*)this;
  void** end = *(void***)(s + 4);
  void* newEnd = FUN_006782c0(Last, end, First);
  for (void** it = (void**)newEnd; it < end; ++it) RefRelease(*it);
  int n = (int)(((char*)Last - (char*)First) >> 2);
  *(void***)(s + 4) = (void**)((char*)end - n * 4);
  return First;
}

// @ 0x00e25c30
int cVec15b::f(void* pos, unsigned n, void* src)
{
  char* s = (char*)this;
  char* begin = *(char**)s;
  char* end   = *(char**)(s + 4);
  unsigned cap = (unsigned)(*(char**)(s + 8) - begin) >> 2;
  if (cap < n) {
    unsigned oldN = (unsigned)(end - begin) >> 2;
    unsigned newCap = oldN * 2; if (oldN == 0) newCap = 1;
    unsigned want = oldN + n; if (want > newCap) newCap = want;
    char* nb = newCap ? (char*)operator_new(newCap * 4, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    unsigned pre = (unsigned)((char*)pos - begin);
    char* p1 = (char*)FUN_00829110(nb, begin, (void*)pre, 0);
    char* mid = p1 + pre;
    FUN_00829110(mid, pos, (void*)n, 0);
    FUN_00829110(mid + n * 4, end, (void*)((char*)end - (char*)pos), 0);
    if (begin && begin != *(char**)(s + 0x10)) operator_delete__(begin);
    *(char**)s = nb; *(char**)(s + 4) = mid; *(char**)(s + 8) = nb + newCap * 4;
    return 0;
  }
  (void)src;
  return 0;
}

// @ 0x00e25df0
void __cdecl FUN_00e25df0(void* first, void* last, void* end, void* pred)
{
  unsigned char (*fn)(void*, void*) = (unsigned char (*)(void*, void*))pred;
  char* f = (char*)first; char* l = (char*)last;
  FUN_00bbf1a0(first, last, pred);
  for (; l < (char*)end; l += 4) {
    if (fn(*(void**)f, *(void**)l)) {
      char* a = *(char**)l;
      if (a) { void* o = *(void**)a; ((void(__thiscall*)(void*))o)(a); }
      char* fa = *(char**)f;
      RefRelease(*(void**)l);
      *(void**)l = fa;
      FUN_00bbea40(first, 0, (int)((char*)last - (char*)first) >> 2, 0);
      RefRelease(a);
    }
  }
}

struct PairRef_e25f40 {
    virtual void AddRef();
};
struct RefPtr_e25f40 {
    PairRef_e25f40* p;
    RefPtr_e25f40(const RefPtr_e25f40& o) : p(o.p)
    {
        if (p) p->AddRef();
    }
};
struct Pair_e25f40 {
    RefPtr_e25f40 a;
    RefPtr_e25f40 b;
};
// The adjust-heap helper takes the moved pair by value (callee destroys it).
void __cdecl FUN_00e25240(char* begin, int hole, int n, int top, Pair_e25f40 v, void* ctx);  // 0x00e25240

// @ 0x00e25f40
void __cdecl FUN_00e25f40(char* begin, char* end, void* ctx)
{
  int n = (int)((end - begin) >> 3);
  if (n >= 2) {
    int i = ((n - 2) >> 1) + 1;
    do {
      --i;
      FUN_00e25240(begin, i, n, i, *(Pair_e25f40*)(begin + i * 8), ctx);
    } while (i != 0);
  }
}

// @ 0x00e25fa0
void cPosseItem15::update_control_value(unsigned key)
{
  char* s = (char*)this;
  char* end = mControlValuesEnd;
  char* found = (char*)FUN_00e23ee0(mControlValuesBegin, end, &key, f138);
  char* match = end;
  if (found != end && *(unsigned*)found <= key && found != found + 0x10) match = found;
  if (match == end) return;
  if (key == 0x3d99184) {
    bool (*vf)(void*) = (bool (*)(void*))(*(void***)s)[0xb4 / 4];
    if (!vf(this)) return;
  }
  char* blinker = *(char**)(s + 0xd4);
  void* w = (*(void*(__thiscall**)(void*, unsigned, int))(**(void***)(blinker + 0x10)))(*(void**)(blinker + 0x10), key, 1);
  if (w) FUN_00e213f0(w, *(float*)(match + 4), *(unsigned char*)(match + 8));
  if (*(unsigned char*)(match + 8) && *(unsigned char*)(match + 9)) {
    float v = *(float*)(match + 4);
    unsigned lvl = 0;
    if (v >= 30.0f) { if (v < 60.0f) lvl = 1; } else lvl = 2;
    void* fn = (*(void***)s)[0x84 / 4];
    if (key == 0x3d99184) ((void(__thiscall*)(void*, int, unsigned))fn)(this, 1, lvl);
    else if (key == 0x3d99162) ((void(__thiscall*)(void*, int, unsigned))fn)(this, 0, lvl);
  }
  *(int*)(match + 0xc) = 0;
}

// 0x00e260a0 (byte-exact lifted version: match/slices/s00e260a0/s00e260a0.cpp)
void cPosseItem15::update_control_values(char force)
{
  char* p = mControlValuesBegin;
  char* end = mControlValuesEnd;
  while (p != end) {
    int key = *(int*)p;
    int tick = *(int*)(p + 0xc);
    if (force != 0 || (tick != 0 && mDistress > tick))
      update_control_value(key);
    p += 0x10;
  }
}

// @ 0x00e260f0
bool cPosseItem15::OnTick(void* msg)
{
  unsigned id = (*(unsigned(__thiscall**)(void*))(**(void***)msg))(msg);
  if (id != 0x3d98299) return false;
  ++mDistress;
  update_control_values(0);
  if (mBlinkerFrequency > 0.0f) {
    // TODO: fcos blink computation and blink_for_a_motive loop
    return false;
  }
  return false;
}

// @ 0x00e26410
void __cdecl FUN_00e26410(char* first, char* last, int depth, void* ctx)
{
  while ((int)(((last - first) & 0xfffffffc)) > 0x70 && depth > 0) {
    char* pivot = (char*)FUN_00bbc7c0(first, first + (((last - first) >> 2) >> 1) * 4, last - 4, ctx, ctx);
    void* a = *(void**)pivot;
    if (a) { void* o = *(void**)a; ((void(__thiscall*)(void*))o)(a); }
    char* mid = (char*)FUN_00b95480(first, last);
    FUN_00e26410(mid, last, depth - 1, ctx);
    last = mid;
  }
  if (depth == 0) FUN_00e25df0(first, last, last, ctx);
}

// 0x00e264b0 (byte-exact lifted version: match/slices/s00e264b0/s00e264b0.cpp)
void* __cdecl FUN_00e264b0(char* first, char* last, char** out1, char** out2, void* pred)
{
  unsigned char (*fn)(void*, void*) = (unsigned char (*)(void*, void*))pred;
  while (true) {
    while (fn(first, out1)) first += 8;
    last -= 8;
    while (fn(out1, last)) last -= 8;
    if (last <= first) break;
    FUN_00e245c0(first, last);
    first += 8;
  }
  RefRelease((void*)*out2);
  RefRelease((void*)*out1);
  return first;
}

// @ 0x00e26530
void __cdecl FUN_00e26530(char* first, char* last, char* end, void* pred)
{
  unsigned char (*fn)(void*, void*) = (unsigned char (*)(void*, void*))pred;
  FUN_00e25f40(first, last, pred);
  char* i = last;
  for (; i < end; i += 8) {
    if (!fn(i, first)) continue;
    char* a = *(char**)i;
    char* b = *(char**)(i + 4);
    RefRelease(a); RefRelease(b);
    char* fa = *(char**)first;
    char* fb = *(char**)(first + 4);
    if (fa != a) { RefRelease(a); *(char**)i = fa; }
    if (fb != b) { RefRelease(b); *(char**)(i + 4) = fb; }
    FUN_00e25240(first, 0, (int)((char*)last - (char*)first) >> 3, 0);
    RefRelease(b); RefRelease(a);
  }
  for (; (int)((last - first) & 0xfffffff8) > 8; last -= 8)
    FUN_00e253c0(first, last, pred);
}

// @ 0x00e26680
void cSPUISpace::UpdateCaption()
{
    void* w1 = mLayout.FindWindowByID(0x064a90a0, 1);
    if (w1 != 0)
        w1 = (void*)((uint32_t(__thiscall*)(void*, uint32_t)) (*(void***)w1)[0xc / 4])(w1, 0x0f15f4bd);
    else
        w1 = 0;

    void* w2 = mLayout.FindWindowByID(0x0649a840, 1);
    if (w2 != 0)
        w2 = (void*)((uint32_t(__thiscall*)(void*, uint32_t)) (*(void***)w2)[0xc / 4])(w2, 0x0f15f4bd);
    else
        w2 = 0;

    if (w1 == 0 || w2 == 0)
        return;

    float textH = g_016ac288;
    if ((int)(((char*)mp1fc - (char*)mp1f8) >> 1) != 0) {
        void* o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
        ((void(__thiscall*)(void*, void*)) (*(void***)o)[0x80 / 4])(o, mp1f8);
        ((void(__thiscall*)(void*, int)) (*(void***)w1)[0x14 / 4])(w1, 0);
        o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
        float* r = (float*)((uint32_t(__thiscall*)(void*)) (*(void***)o)[0x38 / 4])(o);
        textH = r[2] - r[0];
    }

    int cur = m1f4;
    int tot = m1f0;
    if (tot > 0 && cur >= 0) {
        wchar_t buf[128];
        buf[0] = 0;
        FUN_004c0530(buf, L"%i/%i", cur, tot);

        void* o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w2)[0x10 / 4])(w2);
        ((void(__thiscall*)(void*, void*)) (*(void***)o)[0x80 / 4])(o, buf);
        ((void(__thiscall*)(void*, int)) (*(void***)w2)[0x14 / 4])(w2, 0);

        void* o3 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
        ((void(__thiscall*)(void*)) (*(void***)o3)[0x38 / 4])(o3);
        FUN_0057cb80(buf);      // scratch eastl::fixed_string<wchar_t,16,1> destroyed
    }

    float on  = (textH <= 0.0f) ? 0.0f : 1.0f;
    void* o4 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
    ((void(__thiscall*)(void*, int, float)) (*(void***)o4)[0x7c / 4])(o4, 1, on);

    float on2 = (textH <= 0.0f) ? 0.0f : 1.0f;
    void* o5 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w2)[0x10 / 4])(w2);
    ((void(__thiscall*)(void*, int, float)) (*(void***)o5)[0x7c / 4])(o5, 1, on2);

    // Vertical stacking: when the total height of the two label rows exceeds the
    // available height the counter row is folded away and re-anchored above the
    // caption row.
    float rowH = m1f4 >= 0 ? textH : textH;
    if (0.0f < rowH + textH) {
        void* w3 = mLayout.FindWindowByID(0x03dae412, 1);
        void* b3 = (w3 == 0) ? 0
                 : (void*)((uint32_t(__thiscall*)(void*, uint32_t)) (*(void***)w3)[0xc / 4])(w3, 0x8ed27e7a);
        float* pr = (float*)((uint32_t(__thiscall*)(void*)) (*(void***)w3)[0x38 / 4])(w3);
        float f12 = pr[1];

        float qa, qb, qc, qd;
        ((void(__thiscall*)(void*, float*, float*, float*, void*)) (*(void***)b3)[0x50 / 4])(b3, &qa, &qb, &qc, &qd);
        ((void(__thiscall*)(void*, float*, float*)) (*(void***)b3)[0x58 / 4])(b3, &qa, &qb);

        f12 = ((f12 + rowH) + on) + qc;
        if (f12 < g_016ac288)
            f12 = g_016ac288;

        float hh = textH - (f12 - (on2 - textH));
        ((void(__thiscall*)(void*, float, float)) (*(void***)w3)[0x70 / 4])(w3, hh, on2);
        ((void(__thiscall*)(void*, float*, float)) (*(void***)w3)[0x74 / 4])(w3, &qa, on2 - on);

        if (0.0f < qa) {
            void* o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
            ((void(__thiscall*)(void*, void*)) (*(void***)o)[0x28 / 4])(o, w3);
            void* o2 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
            ((void(__thiscall*)(void*, void*, int)) (*(void***)o2)[0x70 / 4])(o2, w3, 0);
            SPUIHelpers_AnchorWindowToWindow(w3, w1);
        }
        if (0.0f < qb) {
            void* o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w2)[0x10 / 4])(w2);
            ((void(__thiscall*)(void*, void*)) (*(void***)o)[0x28 / 4])(o, w3);
            void* o2 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w2)[0x10 / 4])(w2);
            ((void(__thiscall*)(void*, void*, int)) (*(void***)o2)[0x70 / 4])(o2, w3, 0);
            SPUIHelpers_AnchorWindowToWindow(w3, w2);
        }
    }
}

// @ 0x00e26a90
void cSPUISpace::ToggleSelectedButton(bool flag)
{
    if (flag && SP_GetCurrentGameMode() == (void*)&g_1654c02) {
        void* s = SP_cTribeModeStrategy_Instance();
        if (((uint32_t(__thiscall*)(void*)) (*(void***)s)[0x6c / 4])(s) != 0) {
            void* s2 = SP_cTribeModeStrategy_Instance();
            void* r = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)s2)[0x6c / 4])(s2);
            ((void(__thiscall*)(void*)) FUN_00cca0a0)(r);
            return;
        }
    }

    void* w = mLayout.FindWindowByID(0x03dae412, 1);
    if (w == 0)
        return;

    void* b = (void*)((uint32_t(__thiscall*)(void*, uint32_t)) (*(void***)w)[0xc / 4])(w, 0x8ed27e7a);
    if (b == 0)
        return;

    char cond;
    if (SP_GetCurrentGameMode() == (void*)&g_1654c02) {
        void* s = SP_cTribeModeStrategy_Instance();
        if (((uint32_t(__thiscall*)(void*)) (*(void***)s)[0x6c / 4])(s) == 0)
            goto other;

        void* s2 = SP_cTribeModeStrategy_Instance();
        void* r = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)s2)[0x6c / 4])(s2);
        cond = ((char(__thiscall*)(void*)) FUN_00cca090)(r);
    } else {
        uint32_t n = (uint32_t)(((char*)mpEndA8 - (char*)mpBeginA4) >> 3);
        cond = (char)(((uint32_t(__thiscall*)(void*)) EA_Audio_GetSystem)(this) == n);
    }

    if (cond) {
        if (((unsigned char(__thiscall*)(void*)) (*(void***)b)[0x20 / 4])(b) & 4)
            return;
        ((void(__thiscall*)(void*, int, int)) (*(void***)b)[0x28 / 4])(b, 4, 1);
    } else {
    other:
        if (!(((unsigned char(__thiscall*)(void*)) (*(void***)b)[0x20 / 4])(b) & 4))
            return;
        ((void(__thiscall*)(void*, int, int)) (*(void***)b)[0x28 / 4])(b, 4, 0);
    }

    UpdateCaption();
}

// @ 0x00e26ba0
void EaVec::resize(size_t n)
{
    if (n > (size_t)((void**)mpEnd - (void**)mpBegin)) {
        void* zero = 0;
        insertAt(mpEnd, n - (size_t)((void**)mpEnd - (void**)mpBegin), &zero);
    } else {
        eraseRange((void**)mpBegin + n, mpEnd);
    }
}

// @ 0x00e26bf0
void* EaVec8::eraseAt(void* pos)
{
    if ((char*)pos + 8 < (char*)mpEnd)
        FUN_00e24290((char*)pos + 8, mpEnd, pos);

    mpEnd = (char*)mpEnd - 8;
    void** p = (void**)mpEnd;
    void* q1 = p[1];
    if (q1 != 0)
        ((void(__thiscall*)(void*)) (*(void***)q1)[4 / 4])(q1);
    void* q0 = p[0];
    if (q0 != 0)
        ((void(__thiscall*)(void*)) (*(void***)q0)[4 / 4])(q0);

    return pos;
}

// @ 0x00e27060
void FUN_00e27060(EaPair* first, EaPair* last, int depth, char (*cmp)(const EaPair&, const EaPair&))
{
    size_t size = (size_t)((char*)last - (char*)first) & 0xfffffff8;

    for (;;) {
        if (size < 0xe1 || depth < 1) {
            if (depth == 0)
                FUN_00e26530(first, last, last, (void*)cmp);
            return;
        }

        EaPair* mid = first + (size / 8) / 2;
        EaPair* p;

        if (cmp(*first, *mid)) {
            if (cmp(*last, *(last - 1))) {
                p = mid;
            } else if (cmp(*first, *(last - 1))) {
                p = last - 1;
            } else {
                p = first;
            }
        } else {
            if (cmp(*first, *(last - 1)) == 0) {
                p = first;
            } else if (cmp(*mid, *(last - 1))) {
                p = last - 1;
            } else {
                p = mid;
            }
        }

        // Move the pivot out of the way (ref-counted copy into a temporary).
        EaPair tmp;
        tmp.mFirst = p->mFirst;
        if (tmp.mFirst != 0)
            ((void(__thiscall*)(void*)) (*(void***)tmp.mFirst)[0])(tmp.mFirst);
        tmp.mSecond = p->mSecond;
        if (tmp.mSecond != 0)
            ((void(__thiscall*)(void*)) (*(void***)tmp.mSecond)[0])(tmp.mSecond);

        EaPair* split = FUN_00e264b0(first, last);

        FUN_00e27060(split, last, depth - 1, cmp);

        last = split;
        size = (size_t)((char*)split - (char*)first) & 0xfffffff8;
        if (size <= 0xe0) {
            if (depth - 1 == 0)
                FUN_00e26530(first, last, last, (void*)cmp);
            return;
        }
    }
}

// @ 0x00e27170
void EaVec8::insertRange(EaPair* first, EaPair* last, void* extra)
{
    size_t n = (size_t)(last - first);

    if (n > (size_t)((EaPair*)mpCapacity - (EaPair*)mpBegin)) {
        EaPair* p = (EaPair*)grow(n, first, last);
        commit(mpBegin, mpEnd);
        if (mpBegin != 0 && mpBegin != mpPool)
            FUN_00f47380(mpBegin);
        EaPair* e = p + n;
        mpBegin = p;
        mpEnd = e;
        mpCapacity = e;
        return;
    }

    unsigned int size = (unsigned int)((EaPair*)mpEnd - (EaPair*)mpBegin);
    if (n <= size) {
        EaPair* moved = (EaPair*)FUN_00e24290(first, last, mpBegin);
        commit(moved, mpEnd);
        mpEnd = moved;
        return;
    }

    EaPair* mid = first + size;
    FUN_00e24290(first, mid, mpBegin);
    void* t;
    FUN_00e24310(&t, mid, last, mpEnd, last);
    mpEnd = t;

    (void)extra;
}

// @ 0x00e27230
uint8_t cSPUIPosseItem_s00e2_6680::SetControlValue(uint32_t id, float value, bool percentage, bool setDistress)
{
    uint32_t key = id;
    void*    end = mControlValues.mpEnd;

    void* it = FUN_00e23ee0(mControlValues.mpBegin, end, &key, mControlValues.mPoolTag);
    if (it == end || id < *(uint32_t*)it)
        it = ((void*(__thiscall*)(ControlValueMap*, void*, uint32_t*)) FUN_00b97140)(&mControlValues, it, &key);

    cControlValue* cv = (cControlValue*)((char*)it + 4);
    cv->value       = value;
    cv->percentage  = percentage ? 1 : 0;
    cv->setDistress = setDistress ? 1 : 0;

    if (cv->updateTick == 0) {
        double r  = ((double(__thiscall*)(void*)) FUN_009360d0)(&g_randRng);
        double t  = r * g_randMul + 1.0;
        double mx = g_randMax;
        if (mx <= t)
            r = mx;
        else if (1.0 <= t)
            r = t;
        else
            r = 1.0;
        cv->updateTick = (uint32_t)(mDistress[2] + (int)(float)r);
    }

    return 1;
}

// @ 0x00e27310
void cSPUIPosseItem_s00e2_7310::SetStateWithoutNotification(u32 state)
{
    if (state == (u32)mState)
        return;

    if ((state == 3 || state == 4) && mStateSwap != 0)
    {
        if (state == 3)
            state = 1;
        else if (state == 4)
            state = 2;
    }

    mState = (i32)state;
    mpPosse->FUN_00e23de0();

    u8 flagC = 0;
    u8 flag8 = 0;
    u8 flag4 = 0;
    switch (state)
    {
    case 4:
        flagC = 1;
    case 2:
        flag4 = 1;
    case 1:
        flag8 = 1;
        break;
    case 3:
        flagC = 1;
        flag8 = 1;
        break;
    }

    void* coll = mWindows.mpData[4];
    u32 ids[3] = { 0x3d99162, 0x3d99184, 0 };
    for (u32* idp = ids; *idp != 0; ++idp)
    {
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, *idp, 1);
        if (w != 0)
        {
            ((void (__thiscall*)(void*, int, u32))VT(w)[0x7c / 4])(w, 1, flag8);
            void* w2 = ((void* (__thiscall*)(void*, u32, int))VT(w)[0xf0 / 4])(w, 0x56bd1b8, 1);
            if (w2 != 0)
                ((void (__thiscall*)(void*, int, u32))VT(w2)[0x7c / 4])(w2, 1, flagC);
        }
    }

    void* w3 = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x4f656e8, 1);
    if (w3 != 0)
        ((void (__thiscall*)(void*, int, u32))VT(w3)[0x7c / 4])(w3, 1, flag4);

    float scale = 1.0f;
    if (mpPosse != 0 && mState != 4 && mState != 3)
        scale = ((float (__thiscall*)(void*))VT(mpPosse)[0xc8 / 4])(mpPosse);

    AnimOut out;
    FUN_007f81d0(&out, mpStateRootWindow, scale, FUN_00805080(), *(float*)0x1480574, 0);
    ((cSPUIAnimator_s00e2_7310*)mpPosse->mpAnimator)->AddAnimation(&out, mpStateRootWindow, 0x4f7b5dd);

    if (((u8 (__thiscall*)(void*))VT(this)[0xb0 / 4])(this) != 0)
    {
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x4acfcaf, 1);
        if (w != 0)
        {
            u8 mine = ((u8 (__thiscall*)(void*))VT(this)[0xac / 4])(this);
            u8 theirs = ((u8 (__thiscall*)(void*))VT(w)[0x28 / 4])(w);
            if (mine != (theirs & 1))
            {
                ((void (__thiscall*)(void*, int, u8))VT(w)[0x7c / 4])(w, 1, mine);

                float scale2 = 1.0f;
                if (mpPosse != 0 && mState != 4 && mState != 3)
                    scale2 = ((float (__thiscall*)(void*))VT(mpPosse)[0xc8 / 4])(mpPosse);

                AnimOut out2;
                FUN_007f81d0(&out2, w, scale2, FUN_00805080() + 0.075f, *(float*)0x1480574, 0);
                ((cSPUIAnimator_s00e2_7310*)mpPosse->mpAnimator)->AddAnimation(&out2, w, 0x4f7c3d1);
                if (out2.mpRef != 0)
                    ReleaseI(out2.mpRef);
            }
        }
    }

    ((void (__thiscall*)(void*, int, void*))VT(this)[0x84 / 4])(this, 0, mBars.mpEnd);
    if (((u8 (__thiscall*)(void*))VT(this)[0xb4 / 4])(this) != 0)
        ((void (__thiscall*)(void*, int, void*))VT(this)[0x84 / 4])(this, 1, mpFieldAC);

    for (u8* p = mControlValuesBegin; p != mControlValuesEnd; p += 0x10)
        update_control_value(*(u32*)p);

    motive_bars_and_background_reposition((mState == 3 || mState == 4) ? 1u : 0u);

    cSPUIPosse_s00e2_7310* posse = mpPosse;
    if (FUN_00b5b800() == (void*)0x1654c02)
    {
        void* strat = FUN_00cd40b0();
        void* r = ((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
        if (r != 0)
        {
            strat = FUN_00cd40b0();
            r = ((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
            MOPS(r)->FUN_00cca0a0();
            goto cleanup;
        }
    }

    {
        void* w = posse->mLayout.FindWindowByID(0x3dae412, true);
        if (w == 0)
            goto cleanup;
        void* f = ((void* (__thiscall*)(void*, u32))VT(w)[0xc / 4])(w, 0x8ed27e7a);
        if (f == 0)
            goto cleanup;

        u8 c;
        if (FUN_00b5b800() == (void*)0x1654c02)
        {
            void* strat = FUN_00cd40b0();
            void* r = ((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
            if (r == 0)
                goto check2;
            strat = FUN_00cd40b0();
            r = ((void* (__thiscall*)(void*))VT(strat)[0x6c / 4])(strat);
            c = MOPS(r)->FUN_00cca090();
        }
        else
        {
            u32 n = (u32)((u8*)posse->mpBarEnd - (u8*)posse->mpBarBegin) >> 3;
            c = (posse->FUN_00e23250() == (i32)n) ? 1 : 0;
        }

        if (c == 0)
            goto check2;
        if ((((u8 (__thiscall*)(void*))VT(f)[0x20 / 4])(f) & 4) != 0)
            goto cleanup;
        ((void (__thiscall*)(void*, u32, u32))VT(f)[0x28 / 4])(f, 4, 1);
        MOPS(posse)->FUN_00e26680();
        goto cleanup;

    check2:
        if ((((u8 (__thiscall*)(void*))VT(f)[0x20 / 4])(f) & 4) == 0)
            goto cleanup;
        ((void (__thiscall*)(void*, u32, u32))VT(f)[0x28 / 4])(f, 4, 0);
        MOPS(posse)->FUN_00e26680();
    }

cleanup:
    if (out.mpRef != 0)
        ReleaseI(out.mpRef);
}

// @ 0x00e277b0
u8 cSPUIPosseItem_s00e2_7310::init(cSPUIPosse_s00e2_7310* posse)
{
    if (posse == 0)
        return 0;

    cSPUIPosse_s00e2_7310* old = mpPosse;
    if (posse != old)
    {
        AddRefI(posse);
        mpPosse = posse;
        if (old != 0)
            ReleaseI(old);
    }

    ((void (__thiscall*)(void*))VT(mpPosse)[0x8c / 4])(mpPosse);

    if (!mLayout.Init(&mKey, false, 0x5b598fa))
        return 0;

    mWindows.FUN_00e26ba0(5);

    for (int i = 1; i < 5; ++i)
    {
        void* w = mLayout.FindWindowByID((u32)(i + 0x3d98300), true);
        void* prev = mWindows.mpData[i];
        if (w != prev)
        {
            if (w != 0)
                AddRefI(w);
            mWindows.mpData[i] = w;
            if (prev != 0)
                ReleaseI(prev);
        }
        if (w != 0)
        {
            ((void (__thiscall*)(void*, float, float))VT(w)[0x70 / 4])(w, 0.0f, 0.0f);
            ((void (__thiscall*)(void*, int))VT(w)[0xac / 4])(w, 0);
            ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, (i == 4) ? 1 : 0);

            void* c = ((void* (__thiscall*)(void*, u32, int))VT(w)[0xf0 / 4])(w, 0x3d99141, 1);
            if (c != 0)
                ((void (__thiscall*)(void*, int))VT(c)[0xac / 4])(c, 0);
            c = ((void* (__thiscall*)(void*, u32, int))VT(w)[0xf0 / 4])(w, 0x3d99151, 1);
            if (c != 0)
                ((void (__thiscall*)(void*, int))VT(c)[0xac / 4])(c, 0);
            c = ((void* (__thiscall*)(void*, u32, int))VT(w)[0xf0 / 4])(w, 0x4acfcaf, 1);
            if (c != 0)
                ((void (__thiscall*)(void*, int, int))VT(c)[0x7c / 4])(c, 1, 0);
        }
    }

    void* p = mLayout.FindWindowByID(0x3d98299, true);
    void* prev = mpStateRootWindow;
    if (p != prev)
    {
        if (p != 0)
            AddRefI(p);
        mpStateRootWindow = p;
        if (prev != 0)
            ReleaseI(prev);
    }

    ((void (__thiscall*)(void*, int))VT(p)[0xac / 4])(p, 0);
    ((void (__thiscall*)(void*, void*))VT(p)[0x104 / 4])(p, this);

    u32 v = ((u32 (__thiscall*)(void*, u32))VT(this)[0xc / 4])(this, 0xee3f516e);
    ((void (__thiscall*)(void*, u32, u32))VT(p)[0xb8 / 4])(p, 0x3e43b66, v);

    if (FUN_0067dcc0() != 0)
    {
        void* server = FUN_0067dcc0();
        ((void (__thiscall*)(void*, void*, u32))VT(server)[0x20 / 4])(server, &mRefs, 0x3e41916);
    }

    u32* cwBegin = (u32*)mColorWindows.mpBegin;
    u32* cwEnd = (u32*)mColorWindows.mpEnd;
    u32 have = (u32)(cwEnd - cwBegin);
    if (have < 3)
    {
        u32 zero = 0;
        mColorWindows.FUN_00e25c30(cwEnd, 3 - have, &zero);
    }
    else
    {
        mColorWindows.FUN_00e25bd0(cwBegin + 3, cwEnd);
    }

    u32* slots = (u32*)mColorWindows.mpBegin;
    for (int i = 0; i < 3; ++i)
    {
        void* w = mLayout.FindWindowByID((u32)(i + 0x3df0885), true);
        void* prev = (void*)slots[i];
        if (w != prev)
        {
            if (w != 0)
                AddRefI(w);
            slots[i] = (u32)w;
            if (prev != 0)
                ReleaseI(prev);
        }
        ((void (__thiscall*)(void*, int, int))VT((void*)slots[i])[0x7c / 4])((void*)slots[i], 1, 0);
    }

    motive_bars_and_background_collect_initial_metrics();
    ((void (__thiscall*)(void*, int))VT(this)[0xb8 / 4])(this, 1);
    u8 more = ((u8 (__thiscall*)(void*))VT(this)[0xb4 / 4])(this);

    u32 ids[3] = { 0x3d99162, more ? 0x3d99184u : 0u, 0 };
    for (u32* idp = ids; *idp != 0; ++idp)
    {
        void* w = mLayout.FindWindowByID(*idp + 1, true);
        if (w != 0)
            ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, 0);
    }

    return 1;
}

extern "C" const char g_13f6b3c[];
struct PosseCtrl { virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5(); virtual void f6(); virtual u32 GetId(); };
struct PosseMsgServer { virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5(); virtual void Post(u32 id, void* msg, int a, int b); };

// @ 0x00e27b20
u8 cSPUIPosse_s00e2_7310::OnCtrlActivated(void* ctrl, u32 a2, u32 id, u32 a4)
{
    u32 v = ((PosseCtrl*)ctrl)->GetId();
    if (v != 0x3d98298)
        return 0;
    if (id != 0x3dae412)
        return 0;

    void* mode = FUN_00b5b800();
    if (mode == (void*)0x1654c02 || mode == (void*)0x1654c04)
    {
        Msg40* obj = new (g_13f6b3c, 0, 0, 0, 0) Msg40(0x61ed580);
        obj->mData[0] = (uint32_t)this;
        ((PosseMsgServer*)FUN_0067dcc0())->Post(0x61ed580, obj, 0, 0);
    }
    else
        toggle_select_all();
    MOPS(this)->FUN_00e26680();
    return 0;
}

// @ 0x00e27be0
u8 COps::FUN_00e27be0(u32 a, void* obj)
{
    if (!FUN_00950ef0(a, obj))
    {
        if (*(u32*)((char*)obj + 8) == 0x13)
        {
            void* p = *(void**)obj;
            if (p != 0)
            {
                if (((u32 (__thiscall*)(void*))VT(p)[0x1c / 4])(p) == 0x3dae412)
                    FUN_00e26680();
            }
        }
        return 0;
    }
    return 1;
}

// @ 0x00e27c30
void cSPUIPosseItem_s00e2_7310::FUN_00e27c30(u32 a, u32 b)
{
    mField1f0 = b;
    mField1f4 = a;
    MOPS(this)->FUN_00e26680();
}

// @ 0x00e27c50
void cSPUIPosse_s00e2_7310::SetCaptionText(const u16* text)
{
    const u16* p = text;
    while (*p != 0)
        ++p;
    mCaption.assign(text, text + (p - text));
    MOPS(this)->FUN_00e26680();
}

// @ 0x00e27c90
u8 cSPUIPosseItemTribeBaby::init(cSPUIPosse_s00e2_7310* posse)
{
    if (cSPUIPosseItem_s00e2_7310::init(posse))
    {
        void* coll = mWindows.mpData[4];
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x3dea7f0, 1);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, 1);
        ((void (__thiscall*)(void*))VT(w)[0x90 / 4])(w);
        ((void (__thiscall*)(void*, void*))VT(w)[0x104 / 4])(w, this);

        void* sys = FUN_00a206f0();
        void* r = sys != 0 ? ((void* (__thiscall*)(void*))VT(sys)[0x20 / 4])(sys) : 0;

        FUN_00435ed0(*(u32*)g_16ac2c8, r);
        mBlinkerStart = FUN_00805080();
        return 1;
    }
    return 0;
}

// @ 0x00e27d30
u8 cSPUIPosseItemTribeBaby::SetControlValue(u32 id, float value, u32 a, u32 b)
{
    if (id == 0x3dea7f0)
    {
        mControlValue01 = SseClamp(value, 0.0f, 100.0f) * 0.01f;

        void* coll = mWindows.mpData[4];
        if (coll != 0)
        {
            void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x3dea7f0, 1);
            if (w != 0)
                ((void (__thiscall*)(void*))VT(w)[0x90 / 4])(w);
        }
        return 1;
    }
    return cSPUIPosseItem_s00e2_7310::SetControlValue(id, value, a, b);
}

// @ 0x00e27df0
void cSPUIPosseItem_s00e2_7310::SetState_BlinkGuard(u32 state)
{
    if (mControlValue01 < 1.0f && (state == 2 || state == 4 || state == 3))
        return;
    SetStateWithoutNotification(state);
}

// @ 0x00e27e20
u8 cSPUIPosseItemTribe::init(cSPUIPosse_s00e2_7310* posse)
{
    if (cSPUIPosseItem_s00e2_7310::init(posse))
    {
        void* coll = mWindows.mpData[4];
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x3dea7f0, 1);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 1, 1);
        ((void (__thiscall*)(void*))VT(w)[0x90 / 4])(w);
        ((void (__thiscall*)(void*, void*))VT(w)[0x104 / 4])(w, this);

        void* w2 = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x3d99141, 1);
        ((void (__thiscall*)(void*, int, int))VT(w2)[0x7c / 4])(w2, 1, 0);

        void* w3 = posse->mLayout.FindWindowByID(0x3dae412, true);
        ((void (__thiscall*)(void*, int, int))VT(w3)[0x7c / 4])(w3, 0x10, 1);
        ((void (__thiscall*)(void*, int, int))VT(w3)[0x7c / 4])(w3, 2, 0);
        ((void (__thiscall*)(void*, int, int))VT(w3)[0x7c / 4])(w3, 1, 0);
        return 1;
    }
    return 0;
}

// @ 0x00e27ef0
u8 cSPUIPosseItemSpace::init(cSPUIPosse_s00e2_7310* posse)
{
    u8 r = cSPUIPosseItem_s00e2_7310::init(posse);
    if (r != 0)
    {
        if (mpField50 != 0)
        {
            ((void (__thiscall*)(void*, int))VT(this)[0xb8 / 4])(this, 2);
            return r;
        }

        void* w = posse->mLayout.FindWindowByID(0x3dae412, true);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 0x10, 1);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 2, 0);
    }
    return r;
}

// @ 0x00e27f60
void cSPUIPosseItem_s00e2_7310::SetState_SpaceGuard(u32 state)
{
    if (mpField50 != 0)
    {
        if (state == 2 || state == 4)
            return;
        SetStateWithoutNotification(state);
    }
    else if (state == 1)
    {
        SetStateWithoutNotification(1);
    }
}

// @ 0x00e27fa0
void cSPUIPosseItem_s00e2_7310::SetState_Skip24(u32 state)
{
    if (state != 2 && state != 4)
        SetStateWithoutNotification(state);
}

// @ 0x00e27fc0
u8 cSPUIPosseItemCreature::init(cSPUIPosse_s00e2_7310* posse)
{
    if (cSPUIPosseItem_s00e2_7310::init(posse))
    {
        void* w = posse->mLayout.FindWindowByID(0x3dae412, true);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 0x10, 1);
        ((void (__thiscall*)(void*, int, int))VT(w)[0x7c / 4])(w, 2, 0);
        return 1;
    }
    return 0;
}

// @ 0x00e28010
void cSPUIPosseItem_s00e2_7310::SetState_Only1(u32 state)
{
    if (state == 1)
        SetStateWithoutNotification(1);
}

// @ 0x00e28030
void cSPUIPosseItem_s00e2_7310::SetState_Skip234(u32 state)
{
    if (state != 2 && state != 4 && state != 3)
        SetStateWithoutNotification(state);
}

// @ 0x00e28050
u8 cSPUIPosseItemPlot::init(cSPUIPosse_s00e2_7310* posse)
{
    if (cSPUIPosseItem_s00e2_7310::init(posse))
    {
        void* coll = mWindows.mpData[4];
        void* w = ((void* (__thiscall*)(void*, u32, int))VT(coll)[0xf0 / 4])(coll, 0x614a0c4, 1);
        ((void (__thiscall*)(void*, void*))VT(w)[0x104 / 4])(w, this);

        void* w2 = posse->mLayout.FindWindowByID(0x3dae412, true);
        ((void (__thiscall*)(void*, int, int))VT(w2)[0x7c / 4])(w2, 0x10, 1);
        ((void (__thiscall*)(void*, int, int))VT(w2)[0x7c / 4])(w2, 2, 0);
        ((void (__thiscall*)(void*, int, int))VT(w2)[0x7c / 4])(w2, 1, 0);
        return 1;
    }
    return 0;
}

// @ 0x00e280e0
void cVec8::push_back(cRefPair* src)
{
    cRefPair* p = mpEnd;
    if (p < mpCap)
    {
        mpEnd = p + 1;
        if (p != 0)
        {
            p->mpFirst = src->mpFirst;
            if (p->mpFirst != 0)
                AddRefI(p->mpFirst);

            p->mpSecond = src->mpSecond;
            if (p->mpSecond != 0)
            {
                AddRefI(p->mpSecond);
                return;
            }
        }
    }
    else
    {
        FUN_00e26c80(p, src);
    }
}

// 0x00e281a0 (byte-exact lifted version: match/slices/s00e281a0/s00e281a0.cpp)
void cSPUIPosseItem_s00e2_7310::FUN_00e281a0(u8 flag)
{
    if (flag != 0)
    {
        cRefPair* begin = mBars.mpBegin;
        cRefPair* end = mBars.mpEnd;
        for (cRefPair* p = begin; p != end; ++p)
        {
            void* o = p->mpSecond;
            ((void (__thiscall*)(void*))VT(o)[0xcc / 4])(o);
        }
    }

    cRefPair* begin = mBars.mpBegin;
    cRefPair* end = mBars.mpEnd;
    void* mid = FUN_00e24290(end, end, begin);
    mBars.FUN_00e23870(mid, (void*)mBars.mpEnd);
    mBars.mpEnd += begin - end;

    mRefs.FUN_00e25bd0(mRefs.mpBegin, mRefs.mpEnd);
    mFlag1d4 = 1;
}

// @ 0x00e28230
void cSPUIPosseItem_s00e2_7310::FUN_00e28230()
{
    FUN_00e26de0(mRefs.mpBegin, mRefs.mpEnd, (void*)FUN_00e22760);
}

// @ 0x00e28250
void cVec8::resize(u32 n)
{
    cRefPair* end = mpEnd;
    cRefPair* begin = mpBegin;
    i32 have = (i32)(end - begin);
    if (n > (u32)have)
    {
        cRefPair tmp;
        tmp.mpFirst = 0;
        tmp.mpSecond = 0;
        FUN_00e26e50(end, n - (u32)have, &tmp);
        return;
    }

    cRefPair* target = begin + n;
    void* r = FUN_00e24290(end, end, target);
    FUN_00e23870(r, (void*)mpEnd);
    mpEnd -= end - target;
}

// @ 0x00fc7f80
float Simulator::cBuilding::GetCost()
{
  return 0.0f;
}
