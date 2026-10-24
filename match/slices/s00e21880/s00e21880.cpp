// SporeApp.exe slice s00e21880 -- SPUI posse / posse-item UI (gold6, worker 36)

#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// shared small types
// ---------------------------------------------------------------------------

struct ResourceKey {
    uint32_t mInstanceID;                                   // +0x00
    uint32_t mGroupID;                                      // +0x04
    uint32_t mTypeID;                                       // +0x08
};

struct IWindow;

// Window interface: vtable slots are numbered by their byte offset.
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

// Window interface as reached through the window manager / layout object
// collection (different slot signatures from IWindow at +0xb4).
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

// SPUILayout: the UI layout sub-object owned by every dialog / window object.
struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t nID, bool bRecursive) const;   // 0x008105b0
    void     Shutdown(uint32_t nFlags);                             // 0x00811ad0

    char     mPad000[0x18];
};

// Context that owns the layout object collection at +0x10.
struct cUIContext {
    char      mPad000[0x10];
    IWindow*  mpWindow10;                                   // +0x10
};

// Reference-counted base interface.
struct cRefCounted {
    virtual void v000();                                    // +0x00
    virtual void v004();                                    // +0x04
    virtual void v008();                                    // +0x08
};

// UI message delivered to a posse item.
struct cUIMessage {
    char       mPad000[8];                                  // +0x00
    IWindow*   mpSender;                                    // +0x08
    char       mPad00c[4];                                  // +0x0c
    uint32_t   mValue;                                      // +0x10
};

// Message handler sub-object of cSPUIPosseItem (lives at item + 0x0c).
struct cItemMessageHandler {
    virtual void v000();                                    // +0x00
    virtual void v004();
    virtual void v008();

    bool HandleMessage(uint32_t nMessageID, cUIMessage* pMessage);
};

struct cSPUIPosseItem {
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
    cSPUILayout       mLayout;                              // +0x07c
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

// Vtable view of the objects ordered by cSPUIPosse::CompareWith.
struct cSPUIPosseSortable {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088();
    virtual int32_t  v08c();                                // +0x8c (sort key)
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc();
    virtual void v0c0();
    virtual IWindow* v0c4();                                // +0xc4 (content window)
};

// Posse dialog: layout sub-object at +0x1bc.
struct cSPUIPosse {
    char             mPad000[0xa4];                         // +0x000 .. +0x0a3
    cPosseItemEntry* mpItemsA4;                             // +0x0a4 (first item)
    cPosseItemEntry* mpItemsA8;                             // +0x0a8 (past last item)
    char             mPad0AC[0x90];                         // +0x0ac .. +0x13b
    IWindow*         mpField13c;                            // +0x13c
    char             mPad140[0x7c];                         // +0x140 .. +0x1bb
    cSPUILayout      mLayout;                               // +0x1bc
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

// Posse item list entry (8 bytes).
struct cPosseItemEntry {
    uint32_t         mIndex;                                // +0x00
    cSPUIPosseItem*  mpItem;                                // +0x04
};

struct cNamedItem;

// Window manager returned by SP::WindowManager().
struct cWindowManager {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040();
    virtual IWindow* v044(const float* pPoint);             // +0x44
    virtual void v048(); virtual void v04c(); virtual void v050();
    virtual IWindow* v054(bool bArg);                       // +0x54
    virtual void v058(bool bArg1, bool bArg2);              // +0x58
};

// Message server returned by MessageServer().
struct cMessageServer {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028();
    virtual void PostMessage(void* pTarget, uint32_t nMessageID, int32_t nValue);   // +0x2c
};

// ---------------------------------------------------------------------------
// external engine entry points
// ---------------------------------------------------------------------------

namespace SPUIHelpers {
    char __cdecl SetWindowImage(IWindow* pWindow, const void* pImage, int32_t nFlags);   // 0x00807bb0
}

namespace UI {
    char __cdecl SetWindowImage(IWindow* pWindow, const void* pImage, int32_t nFlags);   // 0x008068d0
}

namespace EA { namespace Locale {
    void __cdecl SetNumberString(double fValue, char* pBuffer, int32_t nBufferSize, const wchar_t* pFormat);   // 0x00881ea0
}}

namespace SP {
    cWindowManager* __cdecl WindowManager();                // 0x0067caa0
}

cMessageServer* __cdecl MessageServer();                   // 0x0067dcc0
uint32_t        __cdecl GetModifierState();                // 0x008d2db0

bool            __cdecl Contains(const uint32_t* pContainer, const uint32_t* pValue);   // 0x00805150
float*          __cdecl GetBoundingScreenRect(float* pOut, IWindow* pWindow, char bArg);   // 0x00808d20
void            __cdecl AnchorWindowToWindow(IWindow* pParent, IWindow* pChild, int32_t nFlags, int32_t nArg);  // 0x00807340

void            __cdecl SPUIFrameCallbackA();              // 0x00e21700
void            __cdecl SPUIFrameCallbackB();              // 0x00e21720
void            __cdecl FUN_00e215d0(cSPUIPosseItem* pItem, uint32_t nValue);   // 0x00e215d0
bool            __cdecl FUN_00e217c0(cNamedItem* pA, cNamedItem* pB);           // 0x00e217c0

extern const float kOne;                                   // 0x01485720
extern const double kTwo;                                  // 0x013f1298
extern const double kHalf;                                 // 0x0140c4f0
extern const float kNegOne;                                // 0x013eb1bc
extern const float kSignMask;                              // 0x013eb8b0

// ---------------------------------------------------------------------------
// functions
// ---------------------------------------------------------------------------

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

// @ 0x00e21960
void __fastcall PosseSetFrameCallbackA(IWindow* pThis)
{
    pThis->v0a0(SPUIFrameCallbackA, 0);
}

// @ 0x00e21980
void __fastcall PosseSetFrameCallbackB(IWindow* pThis)
{
    pThis->v0a0(SPUIFrameCallbackB, 0);
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

// @ 0x00e21ab0
int32_t SPUIInvalidIndex()
{
    return -1;
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
void cSPUIPosseItem::SetSomething(void* pField)
{
    mpField98 = pField;
    if (mpField9c)
        mpField9c->v08c();
}

// @ 0x00e21bd0
void cSPUIPosseItem::SetTaskKey(const ResourceKey* pKey, int32_t nFlags)
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
void cSPUIPosseItem::SetTaskIcon(uint32_t nTaskIconID, void* pImage, int32_t nFlags)
{
    IWindow* pWindow = mpFieldD4->mpWindow10->FindWindowByID(0x3d99141, true);
    if (nTaskIconID != mTaskIconID) {
        mTaskIconID = nTaskIconID;
        UI::SetWindowImage(pWindow, pImage, nFlags);
    }
    pWindow->v07c(true, true);
}

// @ 0x00e21ca0
void cSPUIPosseItem::SetBlinkerMotiveVisible(bool bShow)
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
void cSPUIPosseItem::SetBlinkerMotive(int32_t nMotive, char bForce)
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
void cSPUIPosseItem::SetItemKeyIcon(const ResourceKey* pKey, int32_t nUnused)
{
    mItemKey = *pKey;
    IWindow* pWindow = mpFieldD4->mpWindow10->FindWindowByID(0x3d99151, true);
    SPUIHelpers::SetWindowImage(pWindow, &mItemKey, 0);
}

// @ 0x00e21ea0
void cSPUIPosseItem::SetItemIcon(void* pImage, int32_t nUnused)
{
    uint32_t nNone = 0;
    mItemKey.mInstanceID = nNone;
    mItemKey.mGroupID = nNone;
    mItemKey.mTypeID = nNone;
    IWindow* pWindow = mpFieldD4->mpWindow10->FindWindowByID(0x3d99151, true);
    UI::SetWindowImage(pWindow, pImage, nNone);
}

// @ 0x00e21ee0
void cSPUIPosseItem::AttachToParent()
{
    IWindow* pWindow = mpFieldD4->mpWindow10;
    IWindow* pParent = pWindow->GetParent();
    pWindow->v07c(true, true);
    pParent->v0e8(pWindow);
    pParent->GetParent()->v0e8(pParent);
}

// @ 0x00e21f30
void cSPUIPosseItem::MotiveBarsAndBackgroundReposition(bool bShow)
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
void cSPUIPosseItem::MotiveBarsAndBackgroundCollectInitialMetrics()
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

// @ 0x00e22370
char cSPUIPosseItem::Shutdown()
{
    if (mpField13c && MessageServer())
        MessageServer()->PostMessage(&mHandler, 0x3e41916, -0x270f);
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
bool cSPUIPosseItem::OnMouseUp(IWindow* pWindow, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
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
bool cSPUIPosseItem::OnMouseMove(IWindow* pWindow, float fX, float fY, uint32_t nFlags)
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
bool cSPUIPosseItem::OnFocusChange(uint32_t nArg1, int32_t nReason, IWindow* pWindow)
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
        cSPUIPosseItem* pItem = (cSPUIPosseItem*)((char*)this - 0xc);
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
void cSPUIPosseItem::SetFrameCallback()
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
