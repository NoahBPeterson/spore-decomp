// src/game/SPGonzago/SPUIPosse.cpp -- migrated from slice(s) s00fc7430, s00e27310, s00e26680, s00e24700, s00e23710, s00e22860, s00e21880, s00e20860 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIPosse.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include <math.h>
#include "cSPUIAnimator.h"
#include <intrin.h>

// ---- items of slice s00e20860 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
typedef          int   s32;
void* __cdecl FUN_00b3d350();        // 0x00b3d350 SP::PlanetModel()
void* __cdecl FUN_00b88590(void*);   // 0x00b88590 SP::cPlanetModel::GetContinent
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
uint32_t        __cdecl GetModifierState();                // 0x008d2db0
bool            __cdecl Contains(const uint32_t* pContainer, const uint32_t* pValue);   // 0x00805150
void            __cdecl SPUIFrameCallbackA();              // 0x00e21700
bool            __cdecl FUN_00e217c0(cNamedItem* pA, cNamedItem* pB);           // 0x00e217c0
// ---- items of slice s00e21880 end

// ---- items of slice s00e22860 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cVec3 {
    float x;                       // 0x00
    float y;                       // 0x04
    float z;                       // 0x08
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
static inline const float& max_f(const float& a, const float& b)
{
    return (a < b) ? b : a;
}
static inline const float& min_f(const float& a, const float& b)
{
    return (a > b) ? b : a;
}
static inline int VT_1C_0(void* p)
{
    return ((int (__thiscall*)(void*))(*(void***)p)[0x07])(p);
}
static inline cVec4* VT_38_0(void* p)
{
    return ((cVec4* (__thiscall*)(void*))(*(void***)p)[0x0e])(p);
}
static inline void* VT_F0_2(void* p, int a, int b)
{
    return ((void* (__thiscall*)(void*, int, int))(*(void***)p)[0x3c])(p, a, b);
}
static inline void VT_70_2F(void* p, float a, float b)
{
    ((void (__thiscall*)(void*, float, float))(*(void***)p)[0x1c])(p, a, b);
}
static inline void VT_7C_2(void* p, int a, int b)
{
    ((void (__thiscall*)(void*, int, int))(*(void***)p)[0x1f])(p, a, b);
}
struct cSPUIPosse_s00e2_2860 {
    u8            mPad0000[0x50];
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
    u8            mPad01e0[0x1e4 - 0x1e0];
    u8            mFlag1e4;                // 0x1e4
    u8            mPad01e5[0x1e8 - 0x1e5];
    float         mField1e8;               // 0x1e8
    u8            mFlag1ec;                // 0x1ec
    u8            mPad01ed[0x208 - 0x1ed];
    cSPUIAnimator_s00e2_2860* mpAnimator208;          // 0x208

    void  UpdateLayout(int mode);          // 0x00e22b50
    void  SetToolWindowState(int a, int b);// 0x00e21bd0
    void  RefreshToolWindow(int a);        // 0x00e21ca0

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
const wchar_t* __stdcall FUN_00e21590(int idx)
{
  switch (idx) {
  case 1:  return (const wchar_t*)0x3d99184;
  case 0:
  default: return (const wchar_t*)0x3d99162;
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
    bool b = (flags & 2) != 0;
    state = b * 2 + 2;
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
    void* pm = FUN_00b3d350();
    if (pm) {
      void* oa = *(void**)((char*)a + 0x34);
      void* ca = FUN_00b88590(
          ((void*(__thiscall*)(void*))(*(void***)oa)[0x2c / 4])(oa));
      void* ob = *(void**)((char*)b + 0x34);
      void* cb = FUN_00b88590(
          ((void*(__thiscall*)(void*))(*(void***)ob)[0x2c / 4])(ob));
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

// @ 0x00e21e50
void cSPUIPosseItem_s00e2_1880::SetItemKeyIcon(const ResourceKey* pKey, int32_t nUnused)
{
    mItemKey = *pKey;
    IWindow* pWindow = mpFieldD4->mpWindow10->FindWindowByID(0x3d99151, true);
    SPUIHelpers::SetWindowImage(pWindow, &mItemKey, 0);
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

// @ 0x00e22a60
void cSPUIPosse_s00e2_2860::SnapToPosition()
{
    cSPUIWindow* window = mLayout1bc.FindWindowByID(0x3d98298, 0);
    cVec4* area = VT_38_0(window);
    float x = area->x;
    float y = area->y;
    float z = area->z;
    float w = area->w;
    float offset = mField1d8;
    cVec4 mainArea;
    if (mFlag1ec == 0) {
        cVec4* m = GetMainWindowArea(&mainArea);
        offset = ((m->z - m->x) - mField1d8) - (z - x);
    }
    cVec4* m2 = GetMainWindowArea(&mainArea);
    VT_70_2F(window, offset, ((m2->w - m2->y) - mField1dc) - (w - y));
}

// @ 0x00e23130
void cSPUIPosse_s00e2_2860::SetScaleF(float scale)
{
    float value = scale;
    float lo = 0.25f;
    float hi = 1.0f;
    value = max_f(value, lo);
    value = min_f(value, hi);
    mField1e8 = value;
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
        target = *rect;
        void* image = VT_F0_2(mpPartD4->mpField10, 0x3d99151, 1);
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

// @ 0x00e238b0
void __cdecl FUN_00e238b0(void* dst, u32 n, void* src)
{
  if (n == 0) return;
  do {
    if (dst) {
      Ref a = *(Ref*)src;
      *(Ref*)dst = a;
      if (a) ((TFv)(*(void***)a)[0])(a);
      Ref b = *(Ref*)((char*)src + 4);
      *(Ref*)((char*)dst + 4) = b;
      if (b) ((TFv)(*(void***)b)[0])(b);
    }
    n--;
    dst = (char*)dst + 8;
  } while (n != 0);
}

// @ 0x00e23900
void* __cdecl FUN_00e23900(void* first, void* last, void* out)
{
  if (first == last) return out;
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
  return out;
}

// @ 0x00e23950
void* __cdecl FUN_00e23950(void* first, void* last, void* out)
{
  if (first == last) return out;
  do {
    Ref b = *(Ref*)((char*)first + 4);
    if (b) ((TFv)(*(void***)b)[1])(b);
    Ref a = *(Ref*)first;
    if (a) ((TFv)(*(void***)a)[1])(a);
    first = (char*)first + 8;
    out = (char*)out + 8;
  } while (first != last);
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
    ((CopyImplC*)0x15a5524)->Copy(DAT_016ac278);
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
    ((CopyImplC*)0x15a5524)->Copy(DAT_016ac278);
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
  void* end = *(void**)((char*)self + 0x10);
  void* begin = *(void**)((char*)self + 0xc);
  while ((u32)end > (u32)begin) {
    end = (char*)end - 4;
    void* item = *(void**)end;
    if (((TFi)(*(void***)item)[0xbc / 4])(item) == 3) {
      ((TFv)(*(void***)item)[0xa8 / 4])(item);
    } else if (((TFi)(*(void***)item)[0xbc / 4])(item) == 4) {
      ((TFv)(*(void***)item)[0xa8 / 4])(item);
    }
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
void __cdecl FUN_00e23ee0(void* first, void* last, u32* key)
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
  if (first == last) return out;
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
  return out;
}

// @ 0x00e24310
void* __cdecl FUN_00e24310(void** out, void* first, void* last, void* val)
{
  *out = val;
  for (; first != last; first = (char*)first + 8) {
    Ref* dst = (Ref*)*out;
    if (dst) {
      Ref a = *(Ref*)first;
      dst[0] = a;
      if (a) ((TFv)(*(void***)a)[0])(a);
      Ref b = *(Ref*)((char*)first + 4);
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

// @ 0x00e24eb0
char cSPUIPosse_s00e2_4700::FUN_00e24eb0(int p2, float p3, float p4, int p5, int p6)
{
  char r = FUN_00e248b0(p2, p3, p4, p5, p6);
  if (mField140 != 0 && p5 == 1000)
    FUN_00e24d10(0x6204441, mField50);
  return r;
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

// @ 0x00e27b20
u8 cSPUIPosse_s00e2_7310::OnCtrlActivated(void* ctrl, u32 a2, u32 id, u32 a4)
{
    u32 v = ((u32 (__thiscall*)(void*))VT(ctrl)[0x1c / 4])(ctrl);
    if (v != 0x3d98298)
        return 0;
    if (id != 0x3dae412)
        return 0;

    void* mode = FUN_00b5b800();
    if (mode != (void*)0x1654c02 && mode != (void*)0x1654c04)
    {
        toggle_select_all();
        MOPS(this)->FUN_00e26680();
        return 0;
    }

    void* obj = FUN_00f473a0(0x40, (void*)0x13f6b3c, 0, 0, 0, 0);
    if (obj != 0)
    {
        *(u32*)((char*)obj + 0x30) = 0x61ed580;
        *(void**)obj = (void*)0x13eb90c;
        *(u32*)((char*)obj + 4) = 0;
        *(void**)obj = (void*)0x13eb844;
        *(u32*)((char*)obj + 0x38) = 0;
    }
    *(void**)((char*)obj + 8) = this;

    void* server = FUN_0067dcc0();
    ((void (__thiscall*)(void*, u32, void*, int, int))VT(server)[0x18 / 4])(server, 0x61ed580, obj, 0, 0);
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

        FUN_00435ed0(*(u32*)0x16ac2c8, r);
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
        float v = value;
        if (v < 0.0f)
            v = 0.0f;
        if (v > 100.0f)
            v = 100.0f;
        mControlValue01 = v * 0.01f;

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

// @ 0x00e281a0
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
    FUN_00e26de0(mRefs.mpBegin, mRefs.mpEnd, (void*)0x00e22760);
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
