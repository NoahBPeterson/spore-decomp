// slice s006596b0: SP::cSPUIAssetView rollover/cleanup methods.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

struct TextZoomNameS69 {
    void Shutdown();   // 0x00834e30
};

struct AVTarget;
struct AVOwner {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
    virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47();
    virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55();
    virtual void Detach(AVTarget* target);   // +0xe0
};
struct AVTarget {
    virtual void t0();
    virtual void Release();                  // +0x04
    virtual void t2();
    virtual void t3();
    virtual AVOwner* GetOwner();             // +0x10
};
struct AVZoom {
    virtual void z0();
    virtual void z1();
    virtual void Release();                  // +0x08
};
struct AssetViewS69 {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
    virtual void a12();
    virtual void OnDetach();                 // +0x34
    char pad04[0x20 - 4];
    int m20;                                 // +0x20
    char pad24[0x54 - 0x24];
    AVTarget* mpTarget;                      // +0x54
    char pad58[0x94 - 0x58];
    AVZoom* mpZoom;                          // +0x94
    void Cleanup();   // 0x00659e30
    void ReleaseTargets();   // 0x00659340
};

// ------------------------------------------------------------------ s006596b0 helpers
// Retail dispatches reached from this slice (relocation-masked in the original).
struct cSPUILayoutS69 {                                      // this+0x20
    void* FindWindowByID(uint32_t id, bool recurse);         // 0x008105B0
};
void  FUN_00659270(void* self);                              // 0x00659270
void  FUN_008068D0(void* pWin, void* pImage, int flags);     // 0x008068D0
void  SPUIHelpers_SetWindowImage(void* pWin, const void* pRect, int b);  // 0x00807BB0
void  SPUIHelpers_GetBoundingScreenRect(void* pRect, void* pWin, int b);
int   PropertyManager();                                     // 0x0067DE30
int   GetPropertyAsKey(void* pKey, uint32_t id, void* pOut); // 0x006A1250
void* FUN_008332D0(...);                                     // 0x008332D0
void* FUN_008332A0(void* p);                                 // 0x008332A0
// The retail debug allocator: operator new(size_t, const char*, int, int, int, int).  It cannot be
// spelled `operator new` here (that name is reserved and already declared), so it is named DbgNew.
void* DbgNew(int n, const char* szFile, int a, int b, int c, int d);
void  operator_delete_(void* p);
void* FUN_005C1CE0(int p);                                   // 0x005C1CE0
bool  cSPAssetDataList_SetAssetData(void* p);                // 0x005C??????
void  FUN_00657640(float x, int y, int z, int a, int b, int c, int d, void* e, void* f);
void* Editor_GetConfigFromModelType(void* p);
void* EA_AutoRefCount_AsPPTypeParam(void* p = 0);

// UI::Image, whose ctor takes the source image and a transform.
struct UIImageS69 {
    // In-place construction, exactly as the retail sites do with `new (pMem) UI::Image(...)`.
    // It is modelled as an ordinary member so that no placement operator new has to be declared.
    void Init(void* pSrc, void* pTransform, void* pTransform2);
    virtual void i0();
    virtual void i1();
    virtual void i2(); virtual void i3(); virtual void i4(); virtual void i5();
    virtual void i6(); virtual void i7(); virtual void i8(); virtual void i9();
    virtual void i10(); virtual void i11(); virtual void i12(); virtual void i13();
    virtual void i14(); virtual void i15(); virtual void i16(); virtual void i17();
    virtual void i18(); virtual void i19(); virtual void i20(); virtual void i21();
    virtual void i22(); virtual void i23(); virtual void i24(); virtual void i25();
    virtual void i26(); virtual void i27(); virtual void i28(); virtual void i29();
    virtual void i30(); virtual void i31(); virtual void i32(); virtual void i33();
    virtual void i34(); virtual void i35(); virtual void i36(); virtual void i37();
    virtual void i38(); virtual void i39(); virtual void i40(); virtual void i41();
    virtual void i42(); virtual void i43(); virtual void i44(); virtual void i45();
    virtual void i46(); virtual void i47(); virtual void i48(); virtual void i49();
    virtual void i50(); virtual void i51(); virtual void i52(); virtual void i53();
    virtual void i54(); virtual void i55(); virtual void i56(); virtual void i57();
    virtual void i58(); virtual void i59();
    virtual void Release();                                  // +0x04
};

namespace S69 {
namespace UI { namespace Image { UIImageS69* Image(void* pSrc); } }
}

// @ 0x006596b0  SP::cSPUIAssetView::UpdateDisplayImages (870 bytes).
// Rebuilds the two image windows (this+0x3c and this+0x40) from the currently selected asset,
// scaling each image to the window's aspect ratio.
void FUN_006596b0(void* pSelf)
{
    char* self = (char*)pSelf;

    // Both asset images must be available; otherwise rescan the list.
    if (*(int*)(self + 0x98) == 0 || *(int*)(self + 0x9c) == 0)
        FUN_00659270(pSelf);

    void* pThumb = *(void**)(self + 0x90);
    if (pThumb == 0)
        return;

    // ---------------- main image (self+0x3c) ----------------
    if (*(int*)(self + 0x3c) != 0) {
        bool bZoomed = ((bool (*)(void*))(*(void***)pThumb)[0x58 / 4])(pThumb);
        if (!bZoomed) {
            if (*(int*)(self + 0x98) == 0) {
                // No asset image: just give the window the thumbnail bitmap.
                void* pBitmap = ((void* (*)(void*, int))(*(void***)pThumb)[0x18 / 4])(pThumb, -1);
                SPUIHelpers_SetWindowImage(*(void**)(self + 0x3c), pBitmap, -1);
            } else {
                // Build a UIImage over the asset's image and hand it to the window.
                UIImageS69* pImage = 0;
                void* pSrc = DbgNew(0x14, "\x01", 0, 0, 0, 0);
                if (pSrc)
                    pSrc = (void*)S69::UI::Image::Image(*(void**)(self + 0x98));
                void* pMem = DbgNew(0x2c, "UI/Image", 0, 0, 0, 0);
                if (pMem) {
                    void* pT1 = FUN_008332D0();
                    void* pT2 = FUN_008332A0(pT1);
                    pImage = (UIImageS69*)pMem;
                    pImage->Init(pSrc, pT1, pT2);
                    (void)pT2;
                    if (pImage)
                        ((void (*)(UIImageS69*))(*(void***)pImage)[0])(pImage);
                }
                FUN_008068D0(*(void**)(self + 0x3c), pImage, -1);
                if (pImage)
                    pImage->Release();
            }
        } else {
            FUN_008068D0(*(void**)(self + 0x3c), 0, -1);
        }
    }

    // ---------------- rollover image (self+0x40) ----------------
    if (*(int*)(self + 0x40) == 0)
        return;

    float fRect[3] = { 0.0f, 0.0f, 0.0f };
    bool bZoomed2 = ((bool (*)(void*))(*(void***)pThumb)[0x58 / 4])(pThumb);

    int nAsset;
    void* pSrcRect;
    if (!bZoomed2) {
        nAsset = *(int*)(self + 0x9c);
        pSrcRect = ((void* (*)(void*, float*))(*(void***)pThumb)[0x1c / 4])(pThumb, fRect);
    } else {
        nAsset = *(int*)(self + 0x98);
        pSrcRect = ((void* (*)(void*, float*))(*(void***)pThumb)[0x18 / 4])(pThumb, fRect);
    }
    float fSrc[3];
    fSrc[0] = ((float*)pSrcRect)[0];
    fSrc[1] = ((float*)pSrcRect)[1];
    fSrc[2] = ((float*)pSrcRect)[2];

    if (nAsset == 0) {
        SPUIHelpers_SetWindowImage(*(void**)(self + 0x40), fSrc, -1);
        return;
    }

    void* pSrc = DbgNew(0x14, "\x01", 0, 0, 0, 0);
    if (pSrc)
        pSrc = (void*)S69::UI::Image::Image((void*)nAsset);

    // Fit the source rect into the window's client rect.
    float fOffY = 0.0f;
    float fOffX = 0.0f;
    float fScaleX = 1.0f;
    float fScaleY = 1.0f;
    if (bZoomed2) {
        void* pWin = *(void**)(self + 0x40);
        void* pT1 = FUN_008332D0();
        void* pT2 = FUN_008332A0(pT1);
        int nSrcW = (int)pT1;
        int nSrcH = (int)pT2;
        float* pRect = ((float* (*)(void*))(*(void***)pWin)[0x38 / 4])(pWin);
        float fWinW = pRect[2];
        float fWinX = pRect[0];
        float* pRect2 = ((float* (*)(void*))(*(void***)pWin)[0x38 / 4])(pWin);
        float fWinH = pRect2[3] - pRect2[1];

        if (nSrcW > 0 && nSrcH > 0 && fWinW - fWinX > 0.0f && fWinH > 0.0f) {
            float fAspectSrc = (fWinW - fWinX) / fWinH;
            float fRatio = fAspectSrc / ((float)nSrcW / (float)nSrcH);
            if (1.0f <= fAspectSrc) {
                fScaleY = 1.0f / fRatio;
                fOffX = (1.0f - fScaleY) * 0.5f;
            } else {
                fOffY = (1.0f - fRatio) * 0.5f;
                fScaleX = fRatio;
            }
        }
    }

    void* pMem = DbgNew(0x2c, "UI/Image", 0, 0, 0, 0);
    UIImageS69* pImage = 0;
    if (pMem) {
        void* pT1 = FUN_008332D0();
        void* pT2 = FUN_008332A0(pT1);
        pImage = (UIImageS69*)pMem;
        pImage->Init(pSrc, pT1, pT2);
        (void)pT2;
        if (pImage)
            ((void (*)(UIImageS69*))(*(void***)pImage)[0])(pImage);
    }
    FUN_008068D0(*(void**)(self + 0x40), pImage, -1);
    if (pImage)
        pImage->Release();
}

// @ 0x00659A20  SP::cSPUIAssetView::OnRollover (1000 bytes).
// Reaction to the mouse entering the asset tile: shows the rollover widgets, pushes the selected
// asset's config into the property manager and starts/【reverses】 the highlight animation.
void FUN_00659a20(void* pSelf, void* pEvent)
{
    (void)pEvent;
    char* self = (char*)pSelf;

    void* pW = *(void**)(self + 0x78);
    if (pW == 0)
        return;
    ((void (*)(void*, int, int))(*(void***)pW)[0x7c / 4])(pW, 1, 1);

    void* pSel = *(void**)(self + 0x90);
    if (pSel == 0)
        return;
    void* pCtl = ((void* (*)(void*, int))(*(void***)pSel)[0x40 / 4])(pSel, 0);
    bool bOk = cSPAssetDataList_SetAssetData(*(void**)((char*)pCtl + 4));
    if (!bOk)
        return;

    // Raise the rollover widgets.
    void* p2 = *(void**)(self + 0x7c);
    if (p2)
        ((void (*)(void*, int, int))(*(void***)p2)[0x7c / 4])(p2, 1, 1);

    void* pHl = *(void**)(self + 0x80);
    if (pHl) {
        ((void (*)(void*, int, int))(*(void***)pHl)[0x7c / 4])(pHl, 1, 1);
        ((void (*)(void*, int, int))(*(void***)pHl)[0x7c / 4])(pHl, 0x40, 1);
    }
    void* pTxt = *(void**)(self + 0x84);
    if (pTxt) {
        ((void (*)(void*, int, int))(*(void***)pTxt)[0x7c / 4])(pTxt, 1, 1);
        ((void (*)(void*, int, int))(*(void***)pTxt)[0x7c / 4])(pTxt, 0x40, 1);
    }

    // Push the asset config into the property manager (first time only).
    if (*(int*)(self + 0xb0) == 0) {
        void* pData = ((void* (*)(void*, int))(*(void***)(*(void**)(self + 0x90)))[0x24 / 4])(
            *(void**)(self + 0x90), 0);
        /* the retail code first resolves the asset-data interface through
           EA::COM::interface_cast and cross-checks the verb collection of the asset browser,
           then falls back to the browser's model type when the two disagree */
        void* pCfg = Editor_GetConfigFromModelType(pData);
        int pPM = PropertyManager();
        void* pParam = EA_AutoRefCount_AsPPTypeParam(pData);
        ((void (*)(int, void*, uint32_t, void*))(*(void***)pPM)[0x2c / 4])(pPM, pCfg, 0x015263ec, pParam);
    }

    // Highlight a newly selected asset (first time only).
    if (*(int*)(self + 0xb8) == 0) {
        void* pData2 = ((void* (*)(void*, int))(*(void***)(*(void**)(self + 0x90)))[0x24 / 4])(
            *(void**)(self + 0x90), 0);
        void* pInfo = ((void* (*)(void*, int))(*(void***)(*(void**)(self + 0x90)))[0x40 / 4])(
            *(void**)(self + 0x90), 0);
        if (*(int*)((char*)pInfo + 4) == 0x2b978c46) {
            float fX = *(float*)(self + 0x1d0);
            int nY = *(int*)(self + 0x1d4);
            int nZ = *(int*)(self + 0x1d8);
            if (*(char*)(self + 0x1c) != 0 && fX != 0.0f &&
                *(int*)(self + 0x80) != 0 && *(float*)(self + 0x84) != 0.0f) {
                void* pParam = EA_AutoRefCount_AsPPTypeParam(pData2);
                FUN_00657640(fX, nY, nZ, 0, 0, 0, *(int*)(self + 0x80), pParam, pData2);
            }
        }
        if (*(int*)(self + 0xb8) == 0)
            return;
    }

    // Drive the highlight window's width from the timer.
    float* pRect = ((float* (*)(void*))(*(void***)(*(void**)(self + 0x80)))[0x38 / 4])(
        *(void**)(self + 0x80));
    ((void (*)(void*, float, int))(*(void***)(*(void**)(self + 0x84)))[0x70 / 4])(
        *(void**)(self + 0x84), pRect[2] - pRect[0], 0);

    void* pCtl2 = FUN_005C1CE0(0);
    if (pCtl2) {
        void* pInner = ((void* (*)(void*, int))(*(void***)pCtl2)[0x30 / 4])(pCtl2, 0);
        float rcOuter[4];
        float rcInner[4];
        SPUIHelpers_GetBoundingScreenRect(rcOuter, *(void**)(self + 0x90), 0);
        SPUIHelpers_GetBoundingScreenRect(rcInner, pInner, 0);
        if (rcOuter[2] < rcInner[2]) {
            float* pRect2 = ((float* (*)(void*))(*(void***)pInner)[0x38 / 4])(pInner);
            ((void (*)(void*, float, int))(*(void***)(*(void**)(self + 0x84)))[0x70 / 4])(
                *(void**)(self + 0x84), -(pRect2[2] - pRect2[0]), 0);
        }
    }
}

// @ 0x00659E30  SP::cSPUIAssetView::Cleanup
void AssetViewS69::Cleanup() {
    if (m20 != 0)
        OnDetach();
    if (mpZoom != 0) {
        ((TextZoomNameS69*)mpZoom)->Shutdown();
        if (mpZoom != 0) {
            AVZoom* p = mpZoom;
            mpZoom = 0;
            p->Release();
        }
    }
    ReleaseTargets();
    if (mpTarget != 0 && mpTarget->GetOwner() != 0) {
        mpTarget->GetOwner()->Detach(mpTarget);
        if (mpTarget != 0) {
            AVTarget* p = mpTarget;
            mpTarget = 0;
            p->Release();
        }
    }
}

// @ 0x00659EC0  SP::cSPUIAssetView::UpdateRolloverWidgets (420 bytes).
// Walks the asset-list model and toggles a pair of hit widgets per asset, then hides the
// rollover window again.
void FUN_00659ec0(void* pSelf)
{
    char* self = (char*)pSelf;
    bool bAny = false;

    void* pModel = *(void**)(self + 0x90);
    if (pModel == 0)
        goto hide;

    {
        // The model exposes an array of asset entries via vtable+0x8c into a local vector.
        void* pBegin = 0;
        void* pEnd = 0;
        void* pCap = 0;
        bool bHave = ((bool (*)(void*, void*, void*, void*))(*(void***)pModel)[0x8c / 4])(
            pModel, &pBegin, &pEnd, &pCap);
        int nCount = ((char*)pEnd - (char*)pBegin) >> 2;
        if (bHave && nCount > 0) {
            // Two adjacent window ids per entry, starting at 0x4b2511... - 0x10 and incrementing.
            uint32_t id = 0xb4daee50;
            int nIdx = 0;
            for (int i = nCount; i != 0; --i) {
                void* pWinA = ((cSPUILayoutS69*)(self + 0x20))->FindWindowByID(id - 0x10, true);
                void* pWinB = ((cSPUILayoutS69*)(self + 0x20))->FindWindowByID(id, true);
                if (pWinA && pWinB) {
                    if (*(int*)((char*)pBegin + nIdx) == 0) {
                        ((void (*)(void*, int, int))(*(void***)pWinB)[0x7c / 4])(pWinB, 1, 0);
                        ((void (*)(void*, int, int))(*(void***)pWinA)[0x7c / 4])(pWinA, 1, 0);
                    } else {
                        bAny = true;
                        ((void (*)(void*, int, int))(*(void***)pWinB)[0x7c / 4])(pWinB, 1, 1);
                        ((void (*)(void*, int, int))(*(void***)pWinA)[0x7c / 4])(pWinA, 1, 1);

                        void* pKey = 0;
                        int pPM = PropertyManager();
                        bool bGs = ((bool (*)(int, uint32_t, uint32_t, void*))(*(void***)pPM)[0x2c / 4])(
                            pPM, *(uint32_t*)((char*)pBegin + nIdx), 0xf865c777, &pKey);
                        if (bGs && GetPropertyAsKey(pKey, 0x54d95162, &pKey)) {
                            SPUIHelpers_SetWindowImage(pWinA, &pKey, -1);
                        }
                        if (pKey)
                            ((void (*)(void*))(*(void***)pKey)[1])(pKey);
                    }
                }
                nIdx += 4;
                ++id;
            }
        }
        if (pBegin && *(int*)((char*)pBegin - 4) != 0)
            operator_delete_(pBegin);
    }

hide:
    void* pRollover = *(void**)(self + 0x64);
    if (pRollover)
        ((void (*)(void*, int, int))(*(void***)pRollover)[0x7c / 4])(pRollover, 1, 0);
}
