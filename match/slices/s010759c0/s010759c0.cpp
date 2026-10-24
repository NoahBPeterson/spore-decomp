// Slice s010759c0 -- SP::cSPUISpaceTrading (space-trading UI panel) cluster.
// Region 0x010759c0..0x01076540.  32-bit x86, MSVC 2008 SP1.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-
#include "types.h"

#define PAD(n) virtual void pad##n()

// ---------------------------------------------------------------------------
// EA::UTFWin::IWindow -- only the slots touched by this slice are named; the
// rest are padding virtuals so each named slot lands at the right index.
// ---------------------------------------------------------------------------
struct IWindow {
    PAD(0); PAD(1); PAD(2);
    virtual void* Slot0C(unsigned key);            // +0x0c
    virtual IWindow* GetParent();                  // +0x10
    virtual void Slot14(int a);                    // +0x14
    PAD(6);
    virtual unsigned GetControlID();               // +0x1c
    PAD(8); PAD(9);
    virtual unsigned GetFlags();                   // +0x28
    virtual void* Slot2C();                        // +0x2c
    virtual void* Slot30(void* out);               // +0x30
    PAD(13);
    virtual float* Slot38();                       // +0x38  (4-float rect)
    PAD(15); PAD(16); PAD(17); PAD(18); PAD(19); PAD(20); PAD(21); PAD(22); PAD(23);
    PAD(24); PAD(25); PAD(26); PAD(27); PAD(28);
    virtual void Slot74(float w, float h);         // +0x74
    PAD(30);
    virtual void SetFlag(unsigned flag, int value);// +0x7c
    virtual void Slot80(void* a);                  // +0x80
    PAD(33); PAD(34); PAD(35); PAD(36); PAD(37); PAD(38); PAD(39); PAD(40); PAD(41);
    PAD(42); PAD(43); PAD(44); PAD(45); PAD(46); PAD(47); PAD(48); PAD(49); PAD(50);
    PAD(51); PAD(52); PAD(53); PAD(54); PAD(55); PAD(56); PAD(57); PAD(58); PAD(59);
    virtual IWindow* FindWindowByID(unsigned id, int recursive);   // +0xf0
    PAD(61); PAD(62); PAD(63); PAD(64);
    virtual void Slot104(void* owner);             // +0x104
};

// Generic reference-counted object: slot 0 / 1 / 2 by table offset 0 / 4 / 8.
struct RefObj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct RefObjA {                                   // v0 takes one argument
    virtual void v0(int a);
    virtual void v1(int a);
};

struct cSPUILayout {
    IWindow* FindWindowByID(unsigned id, int recursive);   // 0x008105b0
    void     Shutdown(unsigned a);                          // 0x00811ad0
};

// ---------------------------------------------------------------------------
// UI timed-tooltip subobject living at +0x50 of the trading panel.
// ---------------------------------------------------------------------------
struct cUITimedTooltip {
    char  pad0[0x60];
    float mMaxWidth;                               // +0x60  (0xb0 from the panel)

    void* FindWindow(unsigned id, bool recursive); // 0x00e36650
    void  UpdateLayout();                          // 0x00e369f0
    void  Shutdown();                              // 0x00e36500
    void  UpdateTimeoutA();                        // 0x00e36540
    void  UpdateTimeoutB(IWindow* w);              // 0x00e365a0
    void  Hide();                                  // 0x00e36620
    cUITimedTooltip* Construct();                  // 0x00e36480
    void  Destroy();                               // 0x00e364d0
};

// ---------------------------------------------------------------------------
// SP::cString (0x14 bytes).
// ---------------------------------------------------------------------------
struct cString {
    char pad0[0x14];
    void Construct();                              // 0x006b5060
    void Destroy();                                // 0x006b5240
    const wchar_t* GetText();                      // 0x006b55c0
};

// A 3-pointer eastl vector; only destroyed here.
struct Vec3 {
    void* mpBegin;                                 // +0x00
    void* mpEnd;                                   // +0x04
    void* mpCap;                                   // +0x08
    void Destroy();                                // 0x005c7f10
};

// ---------------------------------------------------------------------------
// A trade item; the data members used here are count (+0x10) and +0x30.
// ---------------------------------------------------------------------------
struct TradeItem {
    virtual void  p0();  virtual void  p1();  virtual void  p2();  virtual void  p3();
    virtual void  p4();  virtual void  p5();  virtual void  p6();  virtual void  p7();
    virtual void  p8();  virtual void  p9();
    virtual void* Slot28();                        // +0x28
    virtual void* Slot2C();                        // +0x2c
    virtual void* Slot30(void* out);               // +0x30
    char  pad0[0xc];                               // +0x04..+0x0f
    int   mCount;                                  // +0x10
    char  pad14[0x1c];                             // +0x14..+0x2f
    int   mField30;                                // +0x30
    int   Fn6C0200();                              // 0x006c0200
};

// Result of the "which item" lookup in UpdateMidPanel.
struct ItemInfo { char pad[0x10]; int mValue; };

// The space-trading transaction manager (SP::cSPSpaceTrading).
struct cSPSpaceTrading {
    TradeItem* GetUserItem(unsigned idx);          // 0x01039ab0
    TradeItem* GetNPCItem(unsigned idx);           // 0x01039ad0
    int   Fn103B950(unsigned a, unsigned isUser, TradeItem* item, unsigned d); // 0x0103b950
    void  Fn103DBD0(unsigned a);                   // 0x0103dbd0
    void* Fn1039C00();                             // 0x01039c00
    int   Fn1039B70();                             // 0x01039b70
};

// Audio system (EA::Audio), vtable slots named by offset.
struct AudioSystem {
    PAD(0); PAD(1); PAD(2); PAD(3); PAD(4); PAD(5); PAD(6); PAD(7);
    virtual unsigned Slot20();                     // +0x20
    PAD(9); PAD(10); PAD(11); PAD(12); PAD(13);
    virtual void Slot38(unsigned a);               // +0x38
    virtual void Slot3C(unsigned a, float b);      // +0x3c
    virtual void Slot40(unsigned a, unsigned b);   // +0x40
    PAD(17); PAD(18); PAD(19); PAD(20); PAD(21);
    virtual void Slot58();                         // +0x58
};

struct MessageServerT {
    PAD(0); PAD(1); PAD(2); PAD(3); PAD(4); PAD(5);
    virtual void Slot18(unsigned a, int b, int c, int d);   // +0x18
};

struct Global16E0D08 { char pad[0x38]; int mField38; };

// ---------------------------------------------------------------------------
// external callees
// ---------------------------------------------------------------------------
extern "C" cSPSpaceTrading* GetSpaceTrading(void);             // 0x00b3d3d0
extern "C" cSPUILayout*     FUN_00dd1ca0(void);                // 0x00dd1ca0 (global layout getter)
extern "C" AudioSystem*     GetSystemAT(void);                 // 0x00a206f0
extern "C" MessageServerT*  MessageServer(void);               // 0x0067dcc0
extern "C" void RemoveHandler(void* h, void* a, void* b, void* c, void* d); // 0x00571db0
extern "C" void operator_delete_array(void* p);                // 0x00f47380
extern "C" void SetImageFromKey(IWindow* w, void* key);        // 0x00e2f5c0
extern "C" void FUN_008822e0(double v, void* buf, int n, int a, int b);   // 0x008822e0
extern "C" void SetNumberString(int lo, int hi, void* buf, int n);        // 0x00881ae0
extern "C" wchar_t* wcsncat_(wchar_t* dst, const wchar_t* src, unsigned n);// 0x13cc380
extern Global16E0D08* g_16e0d08;                               // 0x016e0d08
extern void* g_15b9448;                                        // 0x015b9448

// ---------------------------------------------------------------------------
// SP::cSPUISpaceTrading
// ---------------------------------------------------------------------------
struct cSPUISpaceTrading {
    // The three sub-object vtable slots.  The original constructor and
    // destructor write base-then-derived (and, in the destructor,
    // derived-then-base) vtable pointers as observable stores, so they are
    // modelled as volatile: the compiler must neither drop nor reorder them.
    void* volatile mpVtbl0;                        // +0x00
    void* volatile mpVtbl1;                        // +0x04
    int   mField08;                                // +0x08
    void* volatile mpVtbl2;                        // +0x0c
    void* mField10;                                // +0x10
    void* mField14;                                // +0x14
    void* mField18;                                // +0x18
    void* mField1C;                                // +0x1c
    void* mField20;                                // +0x20
    void* mField24;                                // +0x24
    Vec3  mItems;                                  // +0x28
    char  pad34[8];                                // +0x34..+0x3b
    Vec3  mAnims;                                  // +0x3c
    char  pad48[8];                                // +0x48..+0x4f
    cUITimedTooltip mTooltip;                      // +0x50
    cString mStrB4;                                // +0xb4
    cString mStrC8;                                // +0xc8
    cString mStrDC;                                // +0xdc
    cString mStrF0;                                // +0xf0
    cSPUILayout* mLayout;                          // +0x104
    void* mHandler;                                // +0x108
    void* mH10C;                                   // +0x10c
    void* mH110;                                   // +0x110
    void* mH114;                                   // +0x114
    void* mH118;                                   // +0x118
    bool  mField11C;                               // +0x11c
    char  pad11D[3];                               // +0x11d..+0x11f
    int   mField120;                               // +0x120
    bool  mField124;                               // +0x124

    void Fn10759C0(IWindow* w, TradeItem* item, unsigned isUser);
    void Fn1075DB0();                              // destructor body 0x01075db0
    void Deactivate();
    void Fn10762D0();
    cSPUISpaceTrading* Fn10762E0();                // constructor body 0x010762e0
    void Fn10763C0();
    void UpdateMidPanel();
    void Init();
    void Fn1075810(unsigned a, TradeItem* item);   // 0x01075810
    void Fn1075510();                              // 0x01075510
    void Fn1075570();                              // 0x01075570
    void Fn1075760();                              // 0x01075760
};

// ===========================================================================
// @ 0x01075db0  Fn1075DB0  (cSPUISpaceTrading destructor body)
// ===========================================================================
void cSPUISpaceTrading::Fn1075DB0()
{
    mpVtbl0 = (void*)0x149c590;
    mpVtbl1 = (void*)0x149c580;
    mpVtbl2 = (void*)0x149c578;

    if (mHandler != 0) {
        void* h = mHandler;
        mHandler = 0;
        RemoveHandler(h, mH10C, mH110, mH114, mH118);
    }
    if (mLayout != 0) {
        ((RefObj*)mLayout)->v2();
    }
    mStrF0.Destroy();
    mStrDC.Destroy();
    mStrC8.Destroy();
    mStrB4.Destroy();
    mTooltip.Destroy();

    if (mAnims.mpBegin != 0) {
        if (*(int*)((char*)mAnims.mpBegin - 4) != 0) {
            operator_delete_array(mAnims.mpBegin);
        }
    }
    mItems.Destroy();
    if (mField24 != 0) ((RefObj*)mField24)->v1();
    if (mField20 != 0) ((RefObj*)mField20)->v1();
    if (mField1C != 0) ((RefObj*)mField1C)->v1();
    if (mField18 != 0) ((RefObj*)mField18)->v1();
    if (mField14 != 0) ((RefObj*)mField14)->v1();
    if (mField10 != 0) ((RefObj*)mField10)->v1();

    mpVtbl2 = (void*)0x13eb394;
    mpVtbl1 = (void*)0x13ec458;
    mpVtbl0 = (void*)0x13eb938;
}

// ===========================================================================
// @ 0x01075ef0  Deactivate
// ===========================================================================
void cSPUISpaceTrading::Deactivate()
{
    mField11C = 0;
    mField120 = -1;

    if (mHandler != 0) {
        void* h = mHandler;
        mHandler = 0;
        RemoveHandler(h, mH10C, mH110, mH114, mH118);
    }

    GetSpaceTrading()->Fn103DBD0(1);

    while (mItems.mpBegin != mItems.mpEnd) {
        ((cSPUILayout**)mItems.mpEnd)[-1]->Shutdown(1);
        mItems.mpEnd = (char*)mItems.mpEnd - 4;
        void* o = *(void**)mItems.mpEnd;
        if (o != 0) {
            ((RefObj*)o)->v2();
        }
    }
    while (mAnims.mpBegin != mAnims.mpEnd) {
        void* o = *(void**)((char*)mAnims.mpEnd - 4);
        if (o != 0) {
            ((RefObjA*)o)->v0(1);
        }
        mAnims.mpEnd = (char*)mAnims.mpEnd - 4;
    }

    Fn1075510();
    Fn1075570();
    Fn1075760();
    mTooltip.Shutdown();

    MessageServer()->Slot18(0x4c70ce5, 0, 0, 0);
}

// ===========================================================================
// @ 0x01075ff0  UpdateMidPanel
// ===========================================================================
void cSPUISpaceTrading::UpdateMidPanel()
{
    if (mField120 != -1) {
        TradeItem* item = mField124 ? GetSpaceTrading()->GetUserItem(mField120)
                                    : GetSpaceTrading()->GetNPCItem(mField120);
        if (item != 0) {
            wchar_t money[0x18];
            wchar_t num[0x18];
            int v = item->Fn6C0200() * item->mCount;
            money[0] = 0;
            FUN_008822e0((double)v, money, 0x10, (int)g_15b9448, (int)0x149c570);

            IWindow* w1 = mLayout->FindWindowByID(0x4c1b588, 1);
            w1->SetFlag(1, 1);
            w1->Slot80(money);

            Fn1075810(mField124, item);

            SetNumberString(item->mCount, item->mCount >> 31, num, 0x10);
            num[0xf] = 0;
            wcsncat_(money, L"/", 0xf);

            int n;
            if (mField124) {
                void* p = GetSpaceTrading()->Fn1039C00();
                n = (p != 0) ? ((ItemInfo*)p)->mValue : 0;
            }
            else {
                n = GetSpaceTrading()->Fn1039B70();
            }
            wchar_t num2[0x18];
            SetNumberString(n, n >> 31, num2, 0x10);
            num2[0xf] = 0;
            wcsncat_(money, num2, 0xf);

            IWindow* w2 = mLayout->FindWindowByID(0x4c1510e, 1);
            w2->SetFlag(1, 1);
            w2->Slot80(money);
        }
    }
}

// ===========================================================================
// @ 0x01076180  Init
// ===========================================================================
void cSPUISpaceTrading::Init()
{
    cSPUILayout* q = *(cSPUILayout**)((char*)FUN_00dd1ca0() + 0xc);
    cSPUILayout* old = mLayout;
    if (q != old) {
        if (q != 0) ((RefObj*)q)->v1();
        mLayout = q;
        if (old != 0) ((RefObj*)old)->v2();
    }

    IWindow* w1 = mLayout->FindWindowByID(0x5da83b8, 1);
    w1->Slot104(this);
    w1->SetFlag(1, 1);

    IWindow* w2 = mLayout->FindWindowByID(0x5e62a48, 1);
    w2->Slot104(this);
    w2->SetFlag(1, 1);

    IWindow* w3 = mLayout->FindWindowByID(0x5da83b9, 1);
    void* old3 = mField1C;
    if (w3 != old3) {
        if (w3 != 0) ((RefObj*)w3)->v0();
        mField1C = w3;
        if (old3 != 0) ((RefObj*)old3)->v1();
    }

    IWindow* w4 = mLayout->FindWindowByID(0x5da83b8, 1);
    void* old4 = mField10;
    if (w4 != old4) {
        if (w4 != 0) ((RefObj*)w4)->v0();
        mField10 = w4;
        if (old4 != 0) ((RefObj*)old4)->v1();
    }

    IWindow* w5 = mLayout->FindWindowByID(0x5e3c090, 1);
    w5->SetFlag(1, 0);

    IWindow* w6 = mLayout->FindWindowByID(0x4c19a88, 1);
    w6->Slot104(this);
}

// ===========================================================================
// @ 0x010762d0  Fn10762D0
// ===========================================================================
void cSPUISpaceTrading::Fn10762D0()
{
    if (mField11C != 0) {
        Deactivate();
    }
}

// ===========================================================================
// @ 0x010762e0  Fn10762E0  (cSPUISpaceTrading constructor body)
// ===========================================================================
cSPUISpaceTrading* cSPUISpaceTrading::Fn10762E0()
{
    mpVtbl1 = (void*)0x13ec458;
    mField08 = 0;
    mpVtbl2 = (void*)0x13eb394;
    mpVtbl0 = (void*)0x149c590;
    mpVtbl1 = (void*)0x149c580;
    mpVtbl2 = (void*)0x149c578;

    mField10 = 0;
    mField14 = 0;
    mField18 = 0;
    mField1C = 0;
    mField20 = 0;
    mField24 = 0;
    mItems.mpBegin = 0;
    mItems.mpEnd = 0;
    mItems.mpCap = 0;
    mAnims.mpBegin = 0;
    mAnims.mpEnd = 0;
    mAnims.mpCap = 0;

    mTooltip.Construct();
    mStrB4.Construct();
    mStrC8.Construct();
    mStrDC.Construct();
    mStrF0.Construct();

    mLayout = 0;
    mHandler = 0;
    mH10C = 0;
    mH110 = 0;
    mH114 = 0;
    mH118 = 0;
    mField11C = 0;
    mField120 = -1;
    return this;
}

// ===========================================================================
// @ 0x010759c0  Fn10759C0  (ret 0xc)
// ===========================================================================
void cSPUISpaceTrading::Fn10759C0(IWindow* w, TradeItem* item, unsigned isUser)
{
    TradeItem* t;
    int idx = mField120;
    if (idx == -1) {
        t = 0;
    }
    else if (mField124) {
        t = GetSpaceTrading()->GetUserItem(idx);
    }
    else {
        t = GetSpaceTrading()->GetNPCItem(idx);
    }

    int saved = 0;
    if (t != 0) {
        saved = t->mCount;
        t->mCount = 0;
    }
    int kind = GetSpaceTrading()->Fn103B950(1, isUser, item, 0);
    if (t != 0) {
        t->mCount = saved;
    }

    IWindow* w1 = (IWindow*)mTooltip.FindWindow(0x51a37b8, true);
    if (w1 != 0) {
        IWindow* child = (IWindow*)w1->Slot0C(0xf15f4bd);
        if (child != 0) {
            w1->Slot80(item->Slot28());

            float wa = w1->Slot38()[2] - w1->Slot38()[0];
            child->Slot14(0);
            float wb = w1->Slot38()[2] - w1->Slot38()[0];
            float maxw = (wb > mTooltip.mMaxWidth) ? wb : mTooltip.mMaxWidth;

            float* r = w1->Slot38();
            w1->Slot74(maxw, r[3] - r[1]);

            IWindow* w2 = (IWindow*)mTooltip.FindWindow(0x5fd4ce0, true);
            float* r2 = w2->Slot38();
            w2->Slot74((r2[2] - r2[0]) + maxw - wa, r2[3] - r2[1]);
        }
    }

    IWindow* w3 = (IWindow*)mTooltip.FindWindow(0x6565a88, true);
    if (w3 != 0) {
        w3->SetFlag(1, kind == 4);
    }
    IWindow* w4 = (IWindow*)mTooltip.FindWindow(0x6565a90, true);
    if (w4 != 0) {
        w4->SetFlag(1, kind == 2);
    }

    IWindow* w5 = (IWindow*)mTooltip.FindWindow(0x6567fa0, true);
    if (w5 != 0) {
        IWindow* child5 = (IWindow*)w5->Slot0C(0xf15f4bd);
        if (child5 != 0) {
            g_16e0d08->mField38 = item->mField30;
            switch (kind) {
            case 0:
                w5->Slot80((void*)0x13ec468);
                break;
            case 1:
                w5->Slot80((void*)mStrDC.GetText());
                break;
            case 2:
                w5->Slot80((void*)mStrB4.GetText());
                break;
            case 3:
                w5->Slot80((void*)mStrC8.GetText());
                break;
            case 4:
                w5->Slot80((void*)mStrF0.GetText());
                break;
            }
            child5->Slot14(1);
        }
    }

    IWindow* w6 = (IWindow*)mTooltip.FindWindow(0x51a37b9, true);
    if (w6 != 0) {
        IWindow* child6 = (IWindow*)w6->Slot0C(0xf15f4bd);
        if (child6 != 0) {
            w6->Slot80(item->Slot2C());
            child6->Slot14(1);
        }
    }

    IWindow* w7 = (IWindow*)mTooltip.FindWindow(0x6567ff8, true);
    IWindow* w8 = (IWindow*)mTooltip.FindWindow(0x6568000, true);
    if (w7 != 0 && w8 != 0) {
        w7->SetFlag(1, 0);
        w8->SetFlag(1, 0);
        mTooltip.UpdateLayout();
        w7->SetFlag(1, kind == 4);
        w8->SetFlag(1, kind != 4);
    }

    unsigned st = 0;
    AudioSystem* at = GetSystemAT();
    if (at != 0) {
        st = at->Slot20();
    }
    AudioSystem* at2 = GetSystemAT();
    if (at2 != 0) {
        at2->Slot38(0x3475365);
        at2->Slot40(0x3475381, 0x8821b509);
        at2->Slot40(0x3475385, st);
        at2->Slot58();
    }
    mTooltip.UpdateTimeoutB(w);
}

// ===========================================================================
// @ 0x010763c0  Fn10763C0
// ===========================================================================
void cSPUISpaceTrading::Fn10763C0()
{
    if (mField120 != -1) {
        TradeItem* item = mField124 ? GetSpaceTrading()->GetUserItem(mField120)
                                    : GetSpaceTrading()->GetNPCItem(mField120);
        if (item != 0) {
            item->Slot28();

            bool flag = true;
            int kind = GetSpaceTrading()->Fn103B950(1, mField124, item, 1);
            if (kind - 1 == 0 || kind - 2 == 0 || kind - 3 == 0) {
                flag = false;
            }

            IWindow* w1 = mLayout->FindWindowByID(0x4c19a88, 1);
            w1->SetFlag(1, 1);
            void* key;
            SetImageFromKey(w1, item->Slot30(&key));

            UpdateMidPanel();

            IWindow* w2 = mLayout->FindWindowByID(0x4d149a8, 1);
            w2->SetFlag(1, 1);
            w2->Slot80(item->Slot28());

            IWindow* w3 = mLayout->FindWindowByID(0x4c1510a, 1);
            IWindow* w4 = mLayout->FindWindowByID(0x4c1510c, 1);
            if (mField124) {
                w3->SetFlag(2, flag);
                w4->SetFlag(2, 0);
            }
            else {
                w3->SetFlag(2, 0);
                w4->SetFlag(2, flag);
            }
        }
    }
}