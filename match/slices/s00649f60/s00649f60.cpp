// Slice s00649f60 -- cSPUIAssetBrowser show/hide/launch helpers.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"

struct State {
    uint8_t pad[0x1c];
    uint8_t mField1C;   // +0x1c
};

extern "C" State* __cdecl SporeGuide();     // 0x00401040
extern "C" State* __cdecl AssetBrowser();   // 0x00401030
extern "C" void  __cdecl UpdateMouseFocus(int); // 0x00804f50

// ---- globals --------------------------------------------------------------
extern "C" void* g_15ee298;                          // 0x015ee298
extern "C" unsigned int g_152579c;                   // 0x0152579c
extern "C" const char g_szAssetAnimatorName[];       // 0x013ff910
extern "C" const char g_szSporepediaName[];          // 0x013fa29c
extern "C" const wchar_t g_szWelcome[];              // 0x013ff92c
extern "C" void* g_13ff890[29];                      // 0x013ff890
extern "C" void* g_13ff904[3];                       // 0x013ff904

// _sAppProperties: +0x3c -> inner object whose +0x118 is a "modal active" flag.
struct AppPropsInner { uint8_t pad[0x118]; void* mField118; };
struct AppProps { uint8_t pad[0x3c]; AppPropsInner* mpInner; };
extern "C" AppProps* g_sAppProperties;               // 0x015fd918

// ---- engine callouts ------------------------------------------------------
extern "C" void* __cdecl FUN_00f473a0(unsigned int size, const char* name,
                                      int, int, int, int); // 0x00f473a0 operator new
extern "C" void  __cdecl FUN_00f47380(void*);            // 0x00f47380 operator delete
extern "C" void* __cdecl FUN_0067de30();                 // 0x0067de30 SP::PropertyManager
extern "C" void* __cdecl FUN_0067de40();                 // 0x0067de40
extern "C" void* __cdecl FUN_0067dcc0();                 // 0x0067dcc0 MessageServer
extern "C" void* __cdecl FUN_0067caa0();                 // 0x0067caa0 SP::WindowManager
extern "C" void* __cdecl FUN_0067ddd0();                 // 0x0067ddd0 EffectsManagerPtr
extern "C" void* __cdecl FUN_0067dd50();                 // 0x0067dd50
extern "C" void  __cdecl FUN_0067cb30();                 // 0x0067cb30
extern "C" void  __cdecl FUN_00612270();                 // 0x00612270
extern "C" void* __cdecl FUN_0067cac0(int, int);         // 0x0067cac0
extern "C" int   FUN_0067c420();                         // 0x0067c420
extern "C" void  __cdecl FUN_00649340(void*, void*, int);// 0x00649340 cSPUIAssetBrowser::ReloadCallback
extern "C" void* __cdecl FUN_00a206f0();                 // 0x00a206f0 EA::Audio::GetSystemAT
extern "C" void  __cdecl FUN_00435ed0(void*, void*);     // 0x00435ed0 SP::cSPUISpace::KillSetiEffects
extern "C" void  __cdecl FUN_008098b0(int);              // 0x008098b0 set894
extern "C" void  __cdecl FUN_00571db0(void*, void*, void*, int, void*); // 0x00571db0 RemoveHandler
extern "C" void* __cdecl FUN_00805070();                 // 0x00805070 SPUIHelpers::GetLayoutManager
extern "C" void  __cdecl FUN_008099a0(void*, int, int);  // 0x008099a0 SPUIHelpers_BeginModal
extern "C" void  __cdecl FUN_00809c50(void*, int, int);  // 0x00809c50 SPUIHelpers_EndModal
extern "C" void* __cdecl FUN_00607a60();                 // 0x00607a60 SP::Pollen::AuthManager
extern "C" void  FUN_007f83e0();                         // 0x007f83e0 MissionCardAnimator ctor
extern "C" void  FUN_00810000();                         // 0x00810000 cConnectionDialog ctor
extern "C" void  FUN_005ccbb0();                         // 0x005ccbb0
extern "C" void  FUN_008120d0();                         // 0x008120d0 cSPUILayout::Init
extern "C" void  FUN_008121b0();                         // 0x008121b0 cSPUILayout::SetParentWin
extern "C" void  FUN_00810090();                         // 0x00810090 cSPUILayout::SetReloadCallback
extern "C" void  FUN_008105b0();                         // 0x008105b0 cSPUILayout::FindWindowByID
extern "C" void  FUN_00810660();                         // 0x00810660 cSPUILayoutManager::Method10660
extern "C" void  FUN_008106a0();                         // 0x008106a0 cSPUILayoutManager::SetAllWorldsVisibility
extern "C" void  FUN_00693230();                         // 0x00693230 eastl::hashtable DoFreeBuckets
extern "C" void  FUN_006961d0();                         // 0x006961d0 eastl::hashtable DoFreeNodes
extern "C" void  FUN_0065b1b0();                         // 0x0065b1b0 cSPUIAssetWebBrowser::Shutdown
extern "C" void  FUN_0065ca10();                         // 0x0065ca10 cSPUIFeedEdit::Shutdown
extern "C" void  FUN_00811ad0();                         // 0x00811ad0 cSPUILayout::Shutdown
extern "C" void  FUN_00662920();                         // 0x00662920 FeedList
extern "C" void  FUN_006629e0();                         // 0x006629e0 FeedList
extern "C" void  FUN_006634d0();                         // 0x006634d0
extern "C" void  FUN_0064eaf0();                         // 0x0064eaf0 child-window visibility
extern "C" void  FUN_0065b510();                         // 0x0065b510 cSPUIAssetWebBrowser
extern "C" void  FUN_0065b2a0();                         // 0x0065b2a0 cSPUIAssetWebBrowser::SetActive
extern "C" void  FUN_006b5060();                         // 0x006b5060 cString ctor
extern "C" void  FUN_006b54b0();                         // 0x006b54b0 cString::Load
extern "C" void  FUN_006b55c0();                         // 0x006b55c0 cString::GetText
extern "C" void  FUN_006b5240();                         // 0x006b5240 cString dtor

// ---------------------------------------------------------------------------
struct Iface;

// Localised string helper (SP::cString token translator), 3 pointers.
struct cString { void* mp0; void* mp1; void* mp2; };

// EASTL allocator block header stored immediately before the payload pointer.
struct EastlBlockHeader { unsigned int pad; unsigned int mCount; };

// cSPUIAssetBrowserLaunch: launch-config payload passed to LoadConfigFile.
struct cSPUIAssetBrowserLaunch {
    unsigned int mField00;   // +0x00
    unsigned int mField04;   // +0x04
    unsigned int mField08;   // +0x08
    unsigned int mField0C;   // +0x0c
    uint8_t      mField10;   // +0x10
    uint8_t      mField11;   // +0x11
    uint8_t      mField12;   // +0x12
    uint8_t      mField13;   // +0x13
    uint8_t      mField14;   // +0x14
    uint8_t      pad15[3];   // +0x15..0x17
    unsigned int mField18;   // +0x18
    unsigned int mField1C;   // +0x1c
    unsigned int mField20;   // +0x20
    uint8_t      mField24;   // +0x24
    uint8_t      pad25[3];   // +0x25..0x27
    unsigned int mField28;   // +0x28
    uint8_t      mField2C;   // +0x2c
    uint8_t      pad2D[3];   // +0x2d..0x2f
    unsigned int mField30;   // +0x30
    unsigned int mField34;   // +0x34
    unsigned int mField38;   // +0x38
    unsigned int mField3C;   // +0x3c
    unsigned int mField40;   // +0x40
    unsigned int mField44;   // +0x44
};

// Message-associated payload posted through MessageServer (+0x14 handler).
struct MsgAssoc {
    unsigned int mField00;   // +0x00
    unsigned int mField04;   // +0x04
    unsigned int mField08;   // +0x08
    unsigned int mField0C;   // +0x0c
    unsigned int mField10;   // +0x10
    unsigned int mField14;   // +0x14
    uint8_t      mField18;   // +0x18
    uint8_t      pad19[3];   // +0x19..0x1b
    unsigned int mField1C;   // +0x1c
    unsigned int mField20;   // +0x20
    unsigned int mField24;   // +0x24
    unsigned int mField28;   // +0x28
    unsigned int mField2C;   // +0x2c
    uint8_t      mField30;   // +0x30
    uint8_t      mField31;   // +0x31
    uint8_t      mField32;   // +0x32
    uint8_t      mField33;   // +0x33
    unsigned int mField34;   // +0x34
    unsigned int mField38;   // +0x38
};

// EA::ResourceMan key blob handed to cSPUILayout::Init.
struct EaResourceKey {
    unsigned int mId;    // +0x00
    unsigned int mId2;   // +0x04
    unsigned int mType;  // +0x08
};

struct cSPUIAssetBrowser {
    uint8_t  pad00[0x14];      // +0x00..+0x13
    void*    mpAnimator;       // +0x14
    void*    mpProperty;       // +0x18
    uint8_t  mIsVisible;       // +0x1c
    uint8_t  mField1D;         // +0x1d
    uint8_t  mField1E;         // +0x1e
    uint8_t  mField1F;         // +0x1f
    unsigned int mField20;     // +0x20
    uint8_t  mField24;         // +0x24
    uint8_t  mField25;         // +0x25
    uint8_t  pad26[0x02];      // +0x26..+0x27
    uint8_t  mField28;         // +0x28
    uint8_t  mField29;         // +0x29
    uint8_t  mField2A;         // +0x2a
    uint8_t  pad2B[0x2d];      // +0x2b..+0x57
    void*    mpLayout;         // +0x58
    void*    mpField5C;        // +0x5c
    void*    mpField60;        // +0x60
    void*    mpField64;        // +0x64 (feed editor frame)
    uint8_t  pad68[0x08];      // +0x68..+0x6f
    void*    mpField70;        // +0x70
    uint8_t  pad74[0x0c];      // +0x74..+0x7f
    void*    mpField80;        // +0x80
    void*    mpField84;        // +0x84
    void*    mpField88;        // +0x88
    void*    mpField8c;        // +0x8c
    void*    mpField90;        // +0x90
    void*    mpField94;        // +0x94
    void*    mpField98;        // +0x98
    uint8_t  pad9c[0x08];      // +0x9c..+0xa3
    void*    mpFieldA4;        // +0xa4
    uint8_t  padA8[0x04];      // +0xa8..+0xab
    void*    mpFieldAC;        // +0xac
    uint8_t  padB0[0x04];      // +0xb0..+0xb3
    void*    mpFieldB4;        // +0xb4
    uint8_t  padB8[0x04];      // +0xb8..+0xbb
    void*    mpFieldBC;        // +0xbc
    void*    mpFieldC0;        // +0xc0
    void*    mpFieldC4;        // +0xc4
    uint8_t  padC8[0x30];      // +0xc8..+0xf7
    unsigned int mFieldF8;     // +0xf8
    void*    mpFieldFC;        // +0xfc
    void*    mpField100;       // +0x100
    unsigned int mField104;    // +0x104
    uint8_t  pad108[0x10];     // +0x108..+0x117
    unsigned int mField118;    // +0x118
    void*    mpField11C;       // +0x11c
    void*    mpField120;       // +0x120
    unsigned int mField124;    // +0x124
    uint8_t  pad128[0x10];     // +0x128..+0x137
    unsigned int mField138;    // +0x138
    void*    mpField13C;       // +0x13c
    void*    mpField140;       // +0x140
    unsigned int mField144;    // +0x144
    uint8_t  pad148[0x34];     // +0x148..+0x17b
    void*    mpField17C;       // +0x17c
    void*    mpField180;       // +0x180
    void*    mpField184;       // +0x184
    void*    mpField188;       // +0x188
    unsigned int mField18C;    // +0x18c
    void*    mpField190;       // +0x190
    uint8_t  pad194[0x0c];     // +0x194..+0x19f
    void*    mpField1A0;       // +0x1a0
    void*    mpField1A4;       // +0x1a4
    void*    mpField1A8;       // +0x1a8
    uint8_t  pad1AC[0x04];     // +0x1ac..+0x1af
    void*    mpField1B0;       // +0x1b0
    void*    mpField1B4;       // +0x1b4
    uint8_t  pad1B8[0x04];     // +0x1b8..+0x1bb
    void*    mpField1BC;       // +0x1bc
    uint8_t  pad1C0[0x08];     // +0x1c0..+0x1c7
    uint8_t  mField1C8;        // +0x1c8
    uint8_t  pad1C9[0x47];     // +0x1c9..+0x20f
    void*    mpField210;       // +0x210
    uint8_t  pad214[0x04];     // +0x214..+0x217
    void*    mpField218;       // +0x218
    void*    mpField21C;       // +0x21c
    void*    mpField220;       // +0x220
    void*    mpField224;       // +0x224
    uint8_t  pad228[0x0c];     // +0x228..+0x233
    uint8_t  mField234;        // +0x234

    void FUN_00648d90(int arg);                 // 0x00648d90
    void FUN_006470b0();                        // 0x006470b0 CreateLargeAssetViews
    void FUN_00645010();                        // 0x00645010 PreloadTextures
    void LoadConfigFile(const cSPUIAssetBrowserLaunch& cfg, bool& flag); // 0x00645620
    void SetWebBrowserVisibility(bool visible, unsigned int id);         // 0x00644b90
    void FUN_00649f60(void* param_2, char param_3); // 0x00649f60
    void FUN_0064a220();                        // 0x0064a220 Shutdown
    void SetVisibility(int a, int b, int c);    // 0x0064a400 (declared)
    void Update();                              // 0x0064ab20
};

// @ 0x0064ab20
void cSPUIAssetBrowser::Update() {
    if (!mIsVisible)
        return;
    if (!mField25)
        return;
    if (!mField29 && SporeGuide()->mField1C)
        return;
    void* const p = mpFieldBC;
    if (p && (mField234 || mField1C8) && p)
        return;

    bool v = false;
    if (mField29) {
        if (AssetBrowser()->mField1C)
            v = true;
    }
    SetVisibility(0, 1, v);
    UpdateMouseFocus(1);
}

// @ 0x00649f60
void cSPUIAssetBrowser::FUN_00649f60(void* param_2, char param_3) {
    void* old = mpField5C;
    if (param_2 != old) {
        if (param_2)
            ((void (__thiscall *)(void *))(*(void ***)param_2)[0])(param_2);
        mpField5C = param_2;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    mField29 = (uint8_t)param_3;
    if (param_3 == 0) {
        FUN_006470b0();
        FUN_00645010();
    }

    void* animMem = FUN_00f473a0(0x20, g_szAssetAnimatorName, 0, 0, 0, 0);
    void* anim = animMem ? ((void* (__thiscall *)(void *))FUN_007f83e0)(animMem) : 0;
    mpAnimator = anim;

    void* pm = FUN_0067de30();
    if (mpProperty) {
        void* t = mpProperty;
        mpProperty = 0;
        ((void (__thiscall *)(void *))(*(void ***)t)[1])(t);
    }
    ((void (__thiscall *)(void *, unsigned int, unsigned int, void **))
        (*(void ***)pm)[0x2c / 4])(pm, 0xb55619c2, 0x851d4139, &mpProperty);

    void* mem2 = FUN_00f473a0(0x18, g_szSporepediaName, 0, 0, 0, 0);
    void* obj = mem2 ? ((void* (__thiscall *)(void *))FUN_00810000)(mem2) : 0;
    void* oldLayout = mpLayout;
    if (obj != oldLayout) {
        if (obj)
            ((void (__thiscall *)(void *))(*(void ***)obj)[1])(obj);
        mpLayout = obj;
        if (oldLayout)
            ((void (__thiscall *)(void *))(*(void ***)oldLayout)[2])(oldLayout);
    }

    EaResourceKey key;
    key.mId = ((-(unsigned int)(param_3 != 0)) & 0xbb5ca683) + 0x7c6511a1;
    key.mId2 = 0x510a95b;
    key.mType = g_152579c;
    ((bool (__thiscall *)(void *, EaResourceKey *, int, int))FUN_008120d0)
        (mpLayout, &key, 0, 0x5b598fa);
    ((bool (__thiscall *)(void *, void *, int, int))FUN_008121b0)
        (mpLayout, mpField5C, 1, 0x5b598fa);
    ((void (__thiscall *)(void *, void (*)(void *, void *, int), void *))FUN_00810090)
        (mpLayout, FUN_00649340, this);
    FUN_00649340(this, mpLayout, 1);

    void* msg = FUN_0067dcc0();
    mpField184 = this;
    mpField190 = 0;
    mpField180 = msg;
    if (param_3 != 0) {
        mpField188 = g_13ff904;
        mField18C = 3;
        if (msg) {
            for (int i = 0; i < 3; ++i)
                ((void (__thiscall *)(void *, void *, void *))
                    (*(void ***)msg)[0x24 / 4])(msg, this, g_13ff904[i]);
        }
    } else {
        mpField188 = g_13ff890;
        mField18C = 0x1d;
        if (msg) {
            for (int i = 0; i < 0x1d; ++i)
                ((void (__thiscall *)(void *, void *, void *))
                    (*(void ***)msg)[0x24 / 4])(msg, this, g_13ff890[i]);
        }
    }

    void* mem3 = FUN_00f473a0(0x78, g_szSporepediaName, 0, 0, 0, 0);
    void* g = mem3 ? ((void* (__thiscall *)(void *))FUN_005ccbb0)(mem3) : 0;
    void* oldG = g_15ee298;
    if (g != oldG) {
        if (g)
            ((void (__thiscall *)(void *))(*(void ***)g)[1])(g);
        g_15ee298 = g;
        if (oldG)
            ((void (__thiscall *)(void *))(*(void ***)oldG)[2])(oldG);
    }
    void* a = FUN_0067de40();
    void* b = ((void* (__thiscall *)(void *))(*(void ***)a)[0x20 / 4])(a);
    ((void (__thiscall *)(void *, void *))(*(void ***)b)[0x1c / 4])(b, g_15ee298);

    if (g_sAppProperties->mpInner->mField118 != 0 && param_3 == 0) {
        void* w = ((void* (__thiscall *)(void *, unsigned int, int))FUN_008105b0)
                    (mpLayout, 0x447060a, 1);
        if (w) {
            ((void (__thiscall *)(void *, int, int))(*(void ***)w)[0x7c / 4])(w, 2, 0);
            ((void (__thiscall *)(void *, int, int))(*(void ***)w)[0x7c / 4])(w, 1, 0);
        }
    }
}

// @ 0x0064a220
void cSPUIAssetBrowser::FUN_0064a220() {
    FUN_00648d90(0);

    ((void (__thiscall *)(void *, void *, void *))FUN_00693230)
        (&mFieldF8, mpFieldFC, mpField100);
    mField104 = 0;
    ((void (__thiscall *)(void *, void *, void *))FUN_00693230)
        (&mField118, mpField11C, mpField120);
    mField124 = 0;
    ((void (__thiscall *)(void *, void *, void *))FUN_006961d0)
        (&mField138, mpField13C, mpField140);
    mField144 = 0;

    if (mpFieldA4) {
        ((void (__thiscall *)(void *))(*(void ***)mpFieldA4)[0x20 / 4])(mpFieldA4);
        if (mpFieldA4) {
            void* p = mpFieldA4;
            mpFieldA4 = 0;
            ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
        }
    }
    if (mpField21C) {
        ((void (__thiscall *)(void *))FUN_0065b1b0)(mpField21C);
        if (mpField21C) {
            void* p = mpField21C;
            mpField21C = 0;
            ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
        }
    }
    if (mpField220) {
        ((void (__thiscall *)(void *))FUN_0065b1b0)(mpField220);
        if (mpField220) {
            void* p = mpField220;
            mpField220 = 0;
            ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
        }
    }
    if (mpFieldC4) {
        ((void (__thiscall *)(void *))FUN_0065ca10)(mpFieldC4);
        if (mpFieldC4) {
            void* p = mpFieldC4;
            mpFieldC4 = 0;
            ((void (__thiscall *)(void *))(*(void ***)p)[2])(p);
        }
    }
    if (mpLayout) {
        ((void (__thiscall *)(void *, int))FUN_00811ad0)(mpLayout, 1);
        if (mpLayout) {
            void* p = mpLayout;
            mpLayout = 0;
            ((void (__thiscall *)(void *))(*(void ***)p)[2])(p);
        }
    }
    if (mpAnimator) {
        ((void (__thiscall *)(void *, int))(*(void ***)mpAnimator)[0])(mpAnimator, 1);
        mpAnimator = 0;
    }
    if (mpField1BC) {
        void* p = mpField1BC;
        mpField1BC = 0;
        ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
    }
    if (mpField180) {
        void* p = mpField180;
        mpField180 = 0;
        FUN_00571db0(p, mpField184, mpField188, (int)mField18C, mpField190);
    }
    if (g_15ee298) {
        void* a = FUN_0067de40();
        void* b = ((void* (__thiscall *)(void *))(*(void ***)a)[0x20 / 4])(a);
        ((void (__thiscall *)(void *, void *))(*(void ***)b)[0x20 / 4])(b, g_15ee298);
        if (g_15ee298) {
            void* p = g_15ee298;
            g_15ee298 = 0;
            ((void (__thiscall *)(void *))(*(void ***)p)[2])(p);
        }
    }
    if (mpField218) {
        void* p = mpField218;
        mpField218 = 0;
        ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
    }
}

// @ 0x0064a400
void cSPUIAssetBrowser::SetVisibility(int param_2, int param_3, int param_4) {
    // ORIG accesses these two arguments as bytes (cmp/byte); narrow them so the
    // behaviour matches when the harness passes whole dwords in those slots.
    unsigned char p3 = (unsigned char)param_3;
    unsigned char p4 = (unsigned char)param_4;

    if (g_sAppProperties->mpInner->mField118 != 0 && p4 == 0)
        FUN_008098b0(param_2);

    bool changed = (mIsVisible != (uint8_t)param_2);
    if (changed) {
        mIsVisible = (uint8_t)param_2;
        if (mField234 == 0) {
            void* sys = FUN_00a206f0();
            void* v = 0;
            if (sys)
                v = ((void* (__thiscall *)(void *))(*(void ***)sys)[0x20 / 4])(sys);
            unsigned int key = ((-(unsigned int)(mIsVisible != 0)) & 0x1a6a76db) + 0xcf6e96b7;
            FUN_00435ed0((void*)key, v);
        }
    } else {
        if (mField1D != 0)
            return;
    }
    mField1D = 1;

    if (mpFieldB4) {
        cString s;
        ((void (__thiscall *)(void *))FUN_006b5060)(&s);
        ((bool (__thiscall *)(void *, unsigned int, unsigned int, const wchar_t *))FUN_006b54b0)
            (&s, 0x7c6511a1, 0x5b1a59e, g_szWelcome);
        void* text = ((void* (__thiscall *)(void *))FUN_006b55c0)(&s);
        ((void (__thiscall *)(void *, void *))(*(void ***)mpFieldB4)[0x80 / 4])(mpFieldB4, text);
        ((void (__thiscall *)(void *))FUN_006b5240)(&s);
    }
    if (mpFieldAC) {
        ((void (__thiscall *)(void *, int, void *))(*(void ***)mpFieldAC)[0x7c / 4])
            (mpFieldAC, 1, (void*)param_2);
    }
    if (p3 != 0) {
        if (mpField1A0) {
            cString tmp;
            tmp.mp0 = 0; tmp.mp1 = 0; tmp.mp2 = 0;
            ((void (__thiscall *)(void *, cString *))(*(void ***)mpField1A0)[0])(mpField1A0, &tmp);
        }
        if (mpField1A4) {
            cString tmp;
            tmp.mp0 = 0; tmp.mp1 = 0; tmp.mp2 = 0;
            ((void (__thiscall *)(void *, cString *))(*(void ***)mpField1A4)[0])(mpField1A4, &tmp);
            if (tmp.mp0 != 0 && ((EastlBlockHeader*)tmp.mp0 - 1)->mCount != 0)
                FUN_00f47380(tmp.mp0);
        }
    }
    mpField1A0 = 0;
    mpField1A4 = 0;
    mpField1A8 = 0;
    if (mpField1B0) {
        void* p = mpField1B0;
        mpField1B0 = 0;
        ((void (__thiscall *)(void *))(*(void ***)p)[2])(p);
    }
    if (mpField1B4) {
        void* p = mpField1B4;
        mpField1B4 = 0;
        ((void (__thiscall *)(void *))(*(void ***)p)[2])(p);
    }
    if (mpFieldC0) {
        ((void (__thiscall *)(void *, int))FUN_00662920)(mpFieldC0, (int)mIsVisible);
        if (mIsVisible != 0) {
            if (mField1E != 0) {
                if (mField28 == 0)
                    ((void (__thiscall *)(void *))FUN_006629e0)(mpFieldC0);
                else {
                    mField1E = 1;
                    ((void (__thiscall *)(void *))FUN_006634d0)(mpFieldC0);
                }
            } else {
                mField1E = 1;
                ((void (__thiscall *)(void *))FUN_006634d0)(mpFieldC0);
            }
        }
    }
    if (mpFieldBC)
        ((void (__thiscall *)(void *, int))FUN_0064eaf0)(mpFieldBC, (int)mIsVisible);
    if (mpField224 && mIsVisible == 0 && mpField98) {
        ((void (__thiscall *)(void *, int, int))(*(void ***)mpField98)[0x7c / 4])(mpField98, 1, 0);
    }
    if (mIsVisible != 0) {
        if (mpField210)
            SetWebBrowserVisibility(mIsVisible != 0, (unsigned int)mpField210);
    } else {
        if (mpField21C)
            ((void (__thiscall *)(void *))FUN_0065b510)(mpField21C);
        p3 = 0;
        {
            void* auth = FUN_00607a60();
            ((void (__thiscall *)(void *))(*(void ***)auth)[0x24 / 4])(auth);
        }
        if (mpField64) {
            void* r = ((void* (__thiscall *)(void *, int, unsigned int))
                        (*(void ***)mpField64)[0xf0 / 4])(mpField64, 1, 0x561e0a8);
            if (r)
                ((void (__thiscall *)(void *, int, int))(*(void ***)r)[0x7c / 4])(r, 1, 0);
        }
        if (mpField90)
            ((void (__thiscall *)(void *, int, int))(*(void ***)mpField90)[0x7c / 4])(mpField90, 1, 0);
        if (mpField21C)
            ((void (__thiscall *)(void *, int))FUN_0065b2a0)(mpField21C, 0);
    }
    if (mIsVisible == 0) {
        {
            void* auth = FUN_00607a60();
            ((void (__thiscall *)(void *))(*(void ***)auth)[0x24 / 4])(auth);
        }
        if (mpField64) {
            void* r = ((void* (__thiscall *)(void *, int, unsigned int))
                        (*(void ***)mpField64)[0xf0 / 4])(mpField64, 1, 0x561e0a8);
            if (r)
                ((void (__thiscall *)(void *, int, int))(*(void ***)r)[0x7c / 4])(r, 1, 0);
        }
        if (mpField94)
            ((void (__thiscall *)(void *, int, int))(*(void ***)mpField94)[0x7c / 4])(mpField94, 1, 0);
        if (mpField220)
            ((void (__thiscall *)(void *, int))FUN_0065b2a0)(mpField220, 0);
    }
    if (mpField70)
        ((void (__thiscall *)(void *, int, int))(*(void ***)mpField70)[0x7c / 4])
            (mpField70, 1, (int)mIsVisible);
    if (mpField80)
        ((void (__thiscall *)(void *, int, int))(*(void ***)mpField80)[0x7c / 4])
            (mpField80, 1, (int)mIsVisible);
    if (mpField88)
        ((void (__thiscall *)(void *, int, int))(*(void ***)mpField88)[0x7c / 4])
            (mpField88, 1, p4 != 0 ? (int)mIsVisible : 0);
    if (mpField8c)
        ((void (__thiscall *)(void *, int, int))(*(void ***)mpField8c)[0x7c / 4])
            (mpField8c, 1, (int)mIsVisible);

    if (changed && p4 == 0) {
        void* lm = FUN_00805070();
        if (p3 == 0) {
            ((void (__thiscall *)(void *, unsigned int, int))FUN_00810660)(lm, 0x5b598f9, 0);
            ((void (__thiscall *)(void *, unsigned int, int))FUN_00810660)(lm, 0x5b598f6, 0);
            ((void (__thiscall *)(void *, unsigned int, int))FUN_00810660)(lm, 0x5b598f7, 0);
            ((void (__thiscall *)(void *, int))FUN_008106a0)(lm, 1);
        } else {
            ((void (__thiscall *)(void *, int))FUN_008106a0)(lm, 0);
            ((void (__thiscall *)(void *, unsigned int, int))FUN_00810660)(lm, 0x5b598f9, 1);
            ((void (__thiscall *)(void *, unsigned int, int))FUN_00810660)(lm, 0x5b598f6, 1);
            ((void (__thiscall *)(void *, unsigned int, int))FUN_00810660)(lm, 0x5b598f7, 1);
        }
    }

    if (mpField64) {
        if (mIsVisible != 0) {
            ((void (__thiscall *)(void *, int, int))(*(void ***)mpField64)[0x7c / 4])(mpField64, 1, 1);
            void* wm = FUN_0067caa0();
            ((void (__thiscall *)(void *, int, void *))(*(void ***)wm)[0x4c / 4])(wm, 1, mpField64);
            FUN_008099a0(mpField64, 0, 0);
        } else {
            FUN_00809c50(mpField64, 0, 0);
        }
        if (mpField5C && mpField80) {
            ((void (__thiscall *)(void *, void *))(*(void ***)mpField5C)[0xe8 / 4])(mpField5C, mpField80);
            ((void (__thiscall *)(void *, void *))(*(void ***)mpField5C)[0xe8 / 4])(mpField5C, mpField64);
        }
    }

    {
        void* ms = FUN_0067dcc0();
        if (ms) {
            if (p4 == 0) {
                ((void (__thiscall *)(void *, unsigned int, int, int))
                    (*(void ***)ms)[0x14 / 4])(ms, 0x539a4ce + (unsigned int)(mIsVisible == 0),
                                               (mField24 != 0), 0);
            }
            if (mIsVisible != 0) {
                if (mpFieldBC) {
                    FUN_0067cb30();
                    FUN_00612270();
                }
                ((void (__thiscall *)(void *, unsigned int, int, int))
                    (*(void ***)ms)[0x14 / 4])(ms, 0x53dd093, 0, 0);
            } else {
                if (mpField1BC) {
                    void* p = mpField1BC;
                    mpField1BC = 0;
                    ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
                }
            }
        }
    }

    FUN_00648d90(0);
    if (p4 == 0) {
        void* hints = FUN_0067cac0((mIsVisible == 0), 1);
        ((int (__thiscall *)(void *))FUN_0067c420)(hints);
        if (mIsVisible != 0) {
            void* em = FUN_0067ddd0();
            if (em) {
                if (mpField17C) {
                    void* p = mpField17C;
                    mpField17C = 0;
                    ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
                }
                bool ok = ((bool (__thiscall *)(void *, unsigned int, int, void **))
                            (*(void ***)em)[0x2c / 4])(em, 0x4c4ba0a9, 0, &mpField17C);
                if (ok) {
                    if (mpField17C)
                        ((void (__thiscall *)(void *, int))(*(void ***)mpField17C)[2])(mpField17C, 0);
                }
            }
            {
                void* ms = FUN_0067dcc0();
                ((void (__thiscall *)(void *, unsigned int, int, int, int))
                    (*(void ***)ms)[0x18 / 4])(ms, 0x5e7cb29, 0, 0, 0);
            }
            return;
        }
        if (mpField17C) {
            ((void (__thiscall *)(void *, int))(*(void ***)mpField17C)[0xc / 4])(mpField17C, 0);
            if (mpField17C) {
                void* p = mpField17C;
                mpField17C = 0;
                ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
            }
        }
        {
            void* e = FUN_0067dd50();
            ((void (__thiscall *)(void *, int, int))(*(void ***)e)[0x60 / 4])(e, 0x16, 2);
        }
    }
}

// @ 0x0064a990
void __cdecl FUN_0064a990(cSPUIAssetBrowserLaunch* param) {
    cSPUIAssetBrowser* b = (cSPUIAssetBrowser*)AssetBrowser();
    if (!b)
        return;

    bool flag = false;
    b->LoadConfigFile(*param, flag);
    b->SetVisibility(1, 0, 0);

    bool bl = (param->mField24 != 0 && param->mField18 != 0 && param->mField13 == 0);

    if (b->mpField60) {
        b->mField2A = (uint8_t)(bl ? 0 : 1);
        ((void (__thiscall *)(void *, int, int))(*(void ***)b->mpField60)[0x7c / 4])
            (b->mpField60, 1, bl ? 0 : 1);
    }
    if (b->mpField84) {
        unsigned int arg = bl ? 0 : 0x8d3c5672;
        ((void (__thiscall *)(void *, unsigned int))(*(void ***)b->mpField84)[0xac / 4])
            (b->mpField84, arg);
    }
    {
        void* np = (void*)param->mField40;
        void* op = b->mpField1B0;
        if (np != op) {
            if (np)
                ((void (__thiscall *)(void *))(*(void ***)np)[1])(np);
            b->mpField1B0 = np;
            if (op)
                ((void (__thiscall *)(void *))(*(void ***)op)[2])(op);
        }
    }
    {
        void* np = (void*)param->mField44;
        void* op = b->mpField1B4;
        if (np != op) {
            if (np)
                ((void (__thiscall *)(void *))(*(void ***)np)[1])(np);
            b->mpField1B4 = np;
            if (op)
                ((void (__thiscall *)(void *))(*(void ***)op)[2])(op);
        }
    }

    MsgAssoc msg;
    msg.mField00 = 0x13ff7f0;
    msg.mField04 = 0x13f6c9c;
    msg.mField08 = 0;
    msg.mField0C = 0x54495773;
    msg.mField10 = param->mField08;
    msg.mField14 = param->mField30;
    msg.mField18 = (uint8_t)param->mField2C;
    msg.pad19[0] = 0; msg.pad19[1] = 0; msg.pad19[2] = 0;
    msg.mField1C = param->mField38;
    msg.mField20 = param->mField3C;
    msg.mField24 = param->mField18;
    msg.mField28 = param->mField1C;
    msg.mField2C = param->mField20;
    msg.mField30 = (uint8_t)param->mField24;
    msg.mField31 = 0;
    msg.mField32 = flag ? 1 : 0;
    msg.mField33 = 0;
    msg.mField34 = param->mField34;
    msg.mField38 = param->mField28;

    void* ms = FUN_0067dcc0();
    ((void (__thiscall *)(void *, unsigned int, void *, int))(*(void ***)ms)[0x14 / 4])
        (ms, 0x54495773, &msg.mField04, 0);
}

// @ 0x0064aba0
void __cdecl FUN_0064aba0(void* param) {
    cSPUIAssetBrowser* b = (cSPUIAssetBrowser*)SporeGuide();
    if (!b)
        return;

    cSPUIAssetBrowserLaunch cfg;
    cfg.mField00 = (unsigned int)param;
    cfg.mField04 = 0;
    cfg.mField08 = 0;
    cfg.mField0C = 0;
    cfg.mField10 = 0;
    cfg.mField11 = 0;
    cfg.mField12 = 0;
    cfg.mField13 = 1;
    cfg.mField14 = 0;
    cfg.pad15[0] = 0; cfg.pad15[1] = 0; cfg.pad15[2] = 0;
    cfg.mField18 = 0;
    cfg.mField1C = 0;
    cfg.mField20 = 0;
    cfg.mField24 = 1;
    cfg.pad25[0] = 0; cfg.pad25[1] = 0; cfg.pad25[2] = 0;
    cfg.mField28 = 0;
    cfg.mField2C = 0;
    cfg.pad2D[0] = 0; cfg.pad2D[1] = 0; cfg.pad2D[2] = 0;
    cfg.mField30 = 0xad0e52;
    cfg.mField34 = 1;
    cfg.mField38 = 0;
    cfg.mField3C = 0;
    cfg.mField40 = 0;
    cfg.mField44 = 0;

    bool flag = false;
    b->LoadConfigFile(cfg, flag);
    cSPUIAssetBrowser* ab = (cSPUIAssetBrowser*)AssetBrowser();
    b->SetVisibility(1, 0, ab ? (int)ab->mIsVisible : 0);

    MsgAssoc msg;
    msg.mField00 = 0x13ff7f0;
    msg.mField04 = 0x13f6c9c;
    msg.mField08 = 0;
    msg.mField0C = 0x54495773;
    msg.mField10 = 0;
    msg.mField14 = 0;
    msg.mField18 = 0;
    msg.pad19[0] = 0; msg.pad19[1] = 0; msg.pad19[2] = 0;
    msg.mField1C = 0;
    msg.mField20 = 0;
    msg.mField24 = 0;
    msg.mField28 = 0;
    msg.mField2C = 0;
    msg.mField30 = 1;
    msg.mField31 = 0;
    msg.mField32 = 0;
    msg.mField33 = 0;
    msg.mField34 = 0;
    msg.mField38 = 0;

    void* ms = FUN_0067dcc0();
    ((void (__thiscall *)(void *, unsigned int, void *, int))(*(void ***)ms)[0x14 / 4])
        (ms, 0x54495773, &msg.mField04, 0);
}