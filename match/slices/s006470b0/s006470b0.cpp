// Slice s006470b0 -- cSPUIAssetBrowser large card / popup handling.
// Module flags: /O2 /MD /Gy /TP /arch:SSE (scalar movss/comiss).
#include "types.h"

void* __cdecl operator new(unsigned size, const void* tag, int, int, int, int);
extern char g_allocTag[];                       // 0x13f6b3c
extern char g_animTargetVtbl[];                 // 0x13f6400
extern char g_animTargetVtbl2[];                // 0x13f63fc

struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};
struct IRefCounted2 {
    virtual int AddRef();
    virtual int Release();
};
struct cISPLargeAssetView : IRefCounted2 {      // secondary interface living at +0xc of the concrete view
    virtual void Show(int a, int b, int c, int d, int e);   // slot 2
    virtual void Hide();                                    // slot 3
};
struct LargeViewBase0 { virtual void Reserved(); int pad; };
// concrete large-asset view object (0xd0 bytes): primary IRefCounted at +0, interface at +0xc
struct LargeAssetView : IRefCounted, LargeViewBase0, cISPLargeAssetView {
    char pad[0xd0 - 0x14];
    LargeAssetView* __thiscall Construct(int n);   // 0x66cbd0 (returns this)
};

struct LargeViewMap {
    cISPLargeAssetView*& __thiscall operator[](const unsigned int& key);   // 0x646f40
};
struct LargeViewRef {                           // AutoRefCount<cISPLargeAssetView>
    cISPLargeAssetView* p;
    void __thiscall Assign(cISPLargeAssetView** src);                        // 0xac9480
};

// ---- UI types used by SetLargeCardVisibililty (stubs; vtable slots verified against the binary) ----
struct IWindowS {
    virtual int AddRef();
    virtual int Release();
    virtual void vpad2();
    virtual void vpad3();
    virtual IWindowS* GetParent();
    virtual void vpad5();
    virtual void vpad6();
    virtual void vpad7();
    virtual void vpad8();
    virtual void vpad9();
    virtual void vpad10();
    virtual void vpad11();
    virtual void vpad12();
    virtual void vpad13();
    virtual const float* GetArea();
    virtual void vpad15();
    virtual void vpad16();
    virtual void vpad17();
    virtual void vpad18();
    virtual void vpad19();
    virtual void vpad20();
    virtual void vpad21();
    virtual void vpad22();
    virtual void vpad23();
    virtual void vpad24();
    virtual void SetLocation(float x, float y);
    virtual void vpad26();
    virtual void vpad27();
    virtual void vpad28();
    virtual void vpad29();
    virtual void vpad30();
    virtual void SetFlag(int flag, int on);
    virtual void vpad32();
    virtual void vpad33();
    virtual void vpad34();
    virtual void vpad35();
    virtual void vpad36();
    virtual void vpad37();
    virtual void vpad38();
    virtual void vpad39();
    virtual void vpad40();
    virtual void vpad41();
    virtual void vpad42();
    virtual void vpad43();
    virtual void vpad44();
    virtual void vpad45();
    virtual void vpad46();
    virtual void vpad47();
    virtual void vpad48();
    virtual float* ToLocal(float* out, float x, float y);
};
struct IAssetViewS {   // selected-asset object returned by FUN_00645300
    virtual void vpad0();
    virtual void vpad1();
    virtual void vpad2();
    virtual void vpad3();
    virtual void vpad4();
    virtual void vpad5();
    virtual void vpad6();
    virtual void vpad7();
    virtual void vpad8();
    virtual unsigned GetID();
    virtual void vpad10();
    virtual void vpad11();
    virtual void vpad12();
    virtual void vpad13();
    virtual void vpad14();
    virtual void vpad15();
    virtual void vpad16();
    virtual void vpad17();
    virtual void vpad18();
    virtual void vpad19();
    virtual void vpad20();
    virtual void vpad21();
    virtual void vpad22();
    virtual void vpad23();
    virtual bool IsReady();
};
struct AnimTarget {    // temporary animation target; its inlined dtor resets two vptrs and releases a window ref
    void* vtbl;
    int pad;
    void* vtbl2;
    IWindowS* pWin;
    ~AnimTarget() { vtbl = g_animTargetVtbl; vtbl2 = g_animTargetVtbl2; if (pWin) pWin->Release(); }
};
struct cSPUIAnimator {
    void __thiscall RemoveAnimation(IWindowS* win, int channel);                 // 0x7f6210
    void __thiscall AddAnimation(AnimTarget* t, IWindowS* win, int channel);     // 0x7f8d10
};
struct IMessageServer {
    virtual void vpad0(); virtual void vpad1(); virtual void vpad2(); virtual void vpad3(); virtual void vpad4();
    virtual void PostMessage(unsigned id, int a, int b);                         // slot 5
};
struct IAudioSystem {
    virtual void vpad0(); virtual void vpad1(); virtual void vpad2(); virtual void vpad3(); virtual void vpad4();
    virtual void vpad5(); virtual void vpad6(); virtual void vpad7(); virtual int GetSetiHandle();   // slot 8
};

struct cSPUIAssetBrowser {
    char pad0[0x14];
    cSPUIAnimator* mAnimator;                      // +0x14
    char pad1[0x24 - 0x18];
    bool mFlag24;                                  // +0x24
    char pad2[0x3c - 0x25];
    float mLargeCardHideTime;                      // +0x3c
    char pad3[0x84 - 0x40];
    IWindowS* mWinLargeCardInputBlocker;           // +0x84
    char pad4[0x9c - 0x88];
    IWindowS* mWinLargeCard;                       // +0x9c
    void* mpMsgServerHandle;                       // +0xa0
    char pad5[0x138 - 0xa4];
    LargeViewMap mLargeAssetViews;                 // +0x138 (retail layout)
    char pad6[0x158 - 0x13c];
    LargeViewRef mCurrentLargeAssetView;           // +0x158
    char pad7[0x1a8 - 0x15c];
    int mCallerID;                                 // +0x1a8
    char pad8[0x23d - 0x1ac];
    bool mFlag23d;                                 // +0x23d
    void __thiscall CreateLargeAssetViews();
    void __thiscall SetLargeCardVisibililty(bool visible, const float* rect, bool immediate);
    IAssetViewS* __thiscall GetSelectedAsset();    // 0x645300
};

cSPUIAssetBrowser* __cdecl AssetBrowser();         // SP::AssetBrowser (0x401030)
IMessageServer* __cdecl MessageServer();           // SP::MessageServer (0x67dcc0)
IAudioSystem* __cdecl GetSystemAT();               // EA::Audio::GetSystemAT (0xa206f0)
void __cdecl KillSetiEffects(unsigned id, int handle);   // SP::cSPUISpace::KillSetiEffects (0x435ed0)
float __cdecl GetElapsedSeconds(float duration, int zero);                        // SPUIHelpers::GetElapsedSeconds (0x805080)
AnimTarget* __cdecl CreatePositionTarget(AnimTarget* out, IWindowS* win, float x, float y, float dur);   // 0x7f80d0
AnimTarget* __cdecl CreateShadeAlphaTarget(AnimTarget* out, IWindowS* win, int alpha, float dur);        // 0x7f8290
AnimTarget* __cdecl CreateScaleTarget(AnimTarget* out, IWindowS* win, float scale, float dur);           // 0x7f81d0
void __cdecl SetWindowAlpha(IWindowS* win, float a);                                                     // 0x804fc0
void __cdecl SetScale(IWindowS* win, float sx, float sy);                                                // UI::cWindowTransform::SetScale (0x808190)

#define ASSIGN(k) { \
        key = (k); \
        cISPLargeAssetView*& slot = mLargeAssetViews[key]; \
        cISPLargeAssetView* old = slot; \
        if (p != old) { if (p) p->AddRef(); slot = p; if (old) old->Release(); } }
#define NEXT_P() { LargeAssetView* t = view; p = t ? static_cast<cISPLargeAssetView*>(t) : 0; }

// @ 0x006470b0  (creates one shared large-asset view and registers it for every card type key)
void __thiscall cSPUIAssetBrowser::CreateLargeAssetViews() {
    unsigned int key;
    LargeAssetView* volatile view;
    LargeAssetView* v;
    cISPLargeAssetView* p;
    void* mem = operator new(0xd0, g_allocTag, 0, 0, 0, 0);
    if (mem == 0) {
        view = 0;
    } else {
        v = ((LargeAssetView*)mem)->Construct(1);
        view = v;
        if (v) {
            ((IRefCounted*)v)->AddRef();
            p = static_cast<cISPLargeAssetView*>(v);
            goto have_p;
        }
    }
    p = 0;
have_p:
    ASSIGN(0xdfad9f51);
    NEXT_P();
    ASSIGN(0x9ea3031a);
    NEXT_P();
    ASSIGN(0x372e2c04);
    NEXT_P();
    ASSIGN(0xccc35c46);
    NEXT_P();
    ASSIGN(0x65672ade);
    NEXT_P();
    ASSIGN(0x99e92f05);
    NEXT_P();
    ASSIGN(0x4e3f7777);
    NEXT_P();
    ASSIGN(0xbdd15f3d);
    NEXT_P();
    ASSIGN(0x47c10953);
    NEXT_P();
    ASSIGN(0x72c49181);
    NEXT_P();
    ASSIGN(0x7d433fad);
    NEXT_P();
    ASSIGN(0xf670aa43);
    NEXT_P();
    ASSIGN(0x9ad7d4aa);
    NEXT_P();
    ASSIGN(0xbc1041e6);
    NEXT_P();
    ASSIGN(0xc0b74287);
    NEXT_P();
    ASSIGN(0x8f963dcb);
    NEXT_P();
    ASSIGN(0x2a5147a9);
    NEXT_P();
    ASSIGN(0x1f2a25b6);
    NEXT_P();
    ASSIGN(0xc15695da);
    NEXT_P();
    ASSIGN(0x441cd3e6);
    NEXT_P();
    ASSIGN(0x1a4e0708);
    NEXT_P();
    ASSIGN(0x449c040f);
    NEXT_P();
    ASSIGN(0x2090a11b);
    NEXT_P();
    ASSIGN(0x98e03c0d);
    NEXT_P();
    ASSIGN(0xbcd73e89);
    NEXT_P();
    ASSIGN(0xb8669ec9);
    NEXT_P();
    ASSIGN(0x37148141);
    NEXT_P();
    ASSIGN(0xffffffff);
    { LargeAssetView* t = view; if (t) ((IRefCounted*)t)->Release(); }
}

// @ 0x006478c0  SP::cSPUIAssetBrowser::SetLargeCardVisibililty
void __thiscall cSPUIAssetBrowser::SetLargeCardVisibililty(bool visible, const float* rect, bool immediate)
{
    cSPUIAnimator* anim = AssetBrowser() ? AssetBrowser()->mAnimator : 0;
    if (mWinLargeCard == 0) return;
    if (anim) {
        anim->RemoveAnimation(mWinLargeCard, -1);
        anim->RemoveAnimation(mWinLargeCardInputBlocker, -1);
    }
    if (visible) {
        if (mWinLargeCardInputBlocker) mWinLargeCardInputBlocker->SetFlag(1, visible);
        if (anim) {
            if (rect) {
                const float* area = mWinLargeCard->GetArea();
                float ch = area[3] - area[1];
                float sy = (rect[3] - rect[1]) / ch;
                float cw = area[2] - area[0];
                float sx = (rect[2] - rect[0]) / cw;
                SetScale(mWinLargeCard, sx, sy);
                const float* pt;
                float tmp[2];
                float centre[2];
                IWindowS* parent = mWinLargeCard->GetParent();
                if (parent) {
                    pt = mWinLargeCard->GetParent()->ToLocal(tmp, (rect[2] + rect[0]) * 0.5f, (rect[3] + rect[1]) * 0.5f);
                } else {
                    centre[0] = (rect[2] + rect[0]) * 0.5f;
                    centre[1] = (rect[3] + rect[1]) * 0.5f;
                    pt = centre;
                }
                float px = pt[0] - cw * 0.5f;
                float py = pt[1] - ch * 0.5f;
                mWinLargeCard->SetLocation(px, py);
                AnimTarget t;
                float d = GetElapsedSeconds(0.3f, 0);
                anim->AddAnimation(CreatePositionTarget(&t, mWinLargeCard, 0.0f, 0.0f, d), mWinLargeCard, 1);
            }
        }
        if (anim) {
            mWinLargeCard->SetLocation(0.0f, 0.0f);
            { AnimTarget t; float d = GetElapsedSeconds(0.3f, 0);
              anim->AddAnimation(CreateShadeAlphaTarget(&t, mWinLargeCard, 0xff, d), mWinLargeCard, 2); }
            { AnimTarget t; float d = GetElapsedSeconds(0.3f, 0);
              anim->AddAnimation(CreateScaleTarget(&t, mWinLargeCard, 1.0f, d), mWinLargeCard, 0); }
            SetWindowAlpha(mWinLargeCardInputBlocker, 0.0f);
            { AnimTarget t; float d = GetElapsedSeconds(0.15f, 0) + 0.3f;
              anim->AddAnimation(CreateShadeAlphaTarget(&t, mWinLargeCardInputBlocker, 0xff, d), mWinLargeCardInputBlocker, 2); }
        }
        IAssetViewS* cur = GetSelectedAsset();
        unsigned id = cur->GetID();
        cISPLargeAssetView*& slot = mLargeAssetViews[id];
        cISPLargeAssetView* old = mCurrentLargeAssetView.p;
        cISPLargeAssetView* nu = slot;
        if (nu != old) {
            if (nu) nu->IRefCounted2::AddRef();
            mCurrentLargeAssetView.p = nu;
            if (old) old->IRefCounted2::Release();
        }
        if (mCurrentLargeAssetView.p == 0) {
            unsigned defKey = 0xffffffff;
            mCurrentLargeAssetView.Assign(&mLargeAssetViews[defKey]);
        }
        bool flag = false;
        if (mFlag24) flag = cur->IsReady() ? true : false;
        mCurrentLargeAssetView.p->Show((int)mpMsgServerHandle, (int)cur, mCallerID, flag, mFlag23d);
        IAudioSystem* audio = GetSystemAT();
        KillSetiEffects(0x6c329b06, audio ? audio->GetSetiHandle() : 0);
        MessageServer()->PostMessage(0x5c81b19, 0, 0);
        return;
    }
    if (anim && !immediate) {
        { AnimTarget t; float d = GetElapsedSeconds(0.1f, 0);
          anim->AddAnimation(CreateScaleTarget(&t, mWinLargeCard, 0.001f, d), mWinLargeCard, 0); }
        { AnimTarget t; float d = GetElapsedSeconds(0.1f, 0);
          anim->AddAnimation(CreateShadeAlphaTarget(&t, mWinLargeCard, 0, d), mWinLargeCard, 2); }
        { AnimTarget t; float d = GetElapsedSeconds(0.1f, 0);
          anim->AddAnimation(CreateShadeAlphaTarget(&t, mWinLargeCardInputBlocker, 0, d), mWinLargeCardInputBlocker, 2); }
        mLargeCardHideTime = 0.1f;
    } else {
        if (mWinLargeCardInputBlocker) mWinLargeCardInputBlocker->SetFlag(1, 0);
    }
    if (mCurrentLargeAssetView.p == 0) return;
    mCurrentLargeAssetView.p->Hide();
    cISPLargeAssetView* v = mCurrentLargeAssetView.p;
    if (v) {
        mCurrentLargeAssetView.p = 0;
        v->IRefCounted2::Release();
    }
    MessageServer()->PostMessage(0x5c81b25, 0, 0);
}
