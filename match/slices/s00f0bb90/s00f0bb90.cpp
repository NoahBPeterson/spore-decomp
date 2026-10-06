// Slice s00f0bb90: the "marker text dialog" UI controller (allocated with tag
// "UI/marker_text_dialog", 0x88 bytes).  Optimized module: /O2 /MD /Gy /EHsc /TP,
// x87 for float args/returns, SSE for float copies (compiler default /arch:SSE2).
//
// Layout recovered from the constructors FUN_00f08db0/FUN_00f08ef0 and the
// accessors below:
//   +0x00  cSPUILayout*        mpLayout
//   +0x04  int                 mId
//   +0x08  void*               mpOwner
//   +0x0C  int                 mMode
//   +0x10  Slot[6]             mSlots   (5 item slots + slot[5] = scroll/drag state)
//   +0x70  int                 mPad70
//   +0x74  IWindow*            mpSelectedWindow
//   +0x78  int                 mPad78
//   +0x7C  int                 mPad7C
//   +0x80  Slot*               mpCurrentSlot
//   +0x84  char                mFlag84
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#include <math.h>

// ---------------------------------------------------------------------------
// UTFWin stubs.  Offsets are taken from the annotated disassembly (and the
// ModAPI IWindow header, whose low vtable slots agree with this build).
// ---------------------------------------------------------------------------
struct IWindowManager;
struct IWindow;

struct Vector2 { float x, y; };

struct IWindow {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual IWindow* Cast(uint32_t type);          // +0x0C
    virtual IWindow* GetParent() const;            // +0x10
    virtual IWindowManager* GetWindowManager() const; // +0x14
    virtual int v18() const;                       // +0x18
    virtual uint32_t GetControlID() const;         // +0x1C
    virtual uint32_t GetCommandID() const;         // +0x20
    virtual uint32_t GetCursorID() const;          // +0x24
    virtual void v28(int, int);                    // +0x28
    virtual int v2C() const;                       // +0x2C
    virtual uint32_t GetShadeColor() const;        // +0x30
    virtual const float* GetArea() const;          // +0x34
    virtual void v38();                            // +0x38
    virtual int v3C();                             // +0x3C
    virtual uint32_t GetTextFontID() const;        // +0x40
    virtual void v44();                            // +0x44
    virtual int v48() const;                       // +0x48
    virtual void v4C();                            // +0x4C
    virtual void v50();                            // +0x50
    virtual void v54();                            // +0x54
    virtual void v58();                            // +0x58
    virtual void SetShadeColor(int color);         // +0x5C
    virtual void v60();                            // +0x60
    virtual void SetLocation(float fX, float fY);// +0x64
    virtual void v68();                            // +0x68
    virtual void v6C();                            // +0x6C
    virtual void v70();                            // +0x70
    virtual void v74();                            // +0x74
    virtual void v78();                            // +0x78
    virtual void SetFlag(int flag, int value);     // +0x7C
    virtual void v80(int);                         // +0x80
    virtual void v84();                            // +0x84
    virtual void v88(); virtual void v8C(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9C(); virtual void vA0(); virtual void vA4();
    virtual void vA8(); virtual void vAC(); virtual void vB0(); virtual void vB4();
    virtual void vB8(); virtual void vBC();
    virtual Vector2 vC0(Vector2 v);                 // +0xC0
    virtual void vC4();
    virtual void vC8(); virtual void vCC(); virtual void vD0(); virtual void vD4();
    virtual void vD8();                            // +0xD8
    virtual void vDC(); virtual void vE0(); virtual void vE4(); virtual void vE8();
    virtual void vEC();                            // +0xEC
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive); // +0xF0
    virtual void vF4(); virtual void vF8(); virtual void vFC();
    virtual void v100();
    virtual void v104();                           // +0x104
};

struct IWindowManager {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0C(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1C(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2C(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3C(); virtual void v40(); virtual void v44();
    virtual IWindow* GetMainWindowIndex(int index); // +0x48
    virtual void v4C(int, IWindow*);                // +0x4C
    virtual void v50();
};

struct IUISystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual int v20();                              // +0x20
    virtual void v24(); virtual void v28(); virtual void v2C(); virtual void v30();
    virtual void v34();
    virtual void v38(int);                          // +0x38
    virtual void v3C();
    virtual void v40(int, int);                     // +0x40
    virtual void v44(); virtual void v48(); virtual void v4C(); virtual void v50();
    virtual void v54();
    virtual void v58();                             // +0x58
};

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10();
    virtual void v14(int, int, int);                // +0x14
};

// ---------------------------------------------------------------------------
// cSPUILayout: reference-counted layout object (low vtable slot +0x08 = Release).
// ---------------------------------------------------------------------------
struct cSPUILayout {
    virtual void v00();
    virtual int AddRef();
    virtual int Release();                          // +0x08
    IWindow* FindWindowByID(uint32_t id, bool recursive);
    void SetVisibility(int visible);
    void Init(const void* key, int a, uint32_t b);
    void Shutdown(int a);
};

// ---------------------------------------------------------------------------
// Manager global + marker-dialog globals.
// ---------------------------------------------------------------------------
struct cScenarioTutorialsChecklistUI {
    void ToggleHint(int, int);
};
struct cSomeManager {
    int GetValue(int id);
};
struct cGlobalUIManager {
    char pad74[0x74];
    cSomeManager* mpManager74;                      // +0x74
    char pad_74_d4[0xd4 - 0x78];
    cScenarioTutorialsChecklistUI* mpChecklist;     // +0xd4
};
extern cGlobalUIManager* g_pGlobalUIManager;        // 0x016c7aa4

struct cMarkerTextDialog {
    struct Slot {
        IWindow* mpWindow;      // +0x00
        int      mIndex;        // +0x04
        int      mPad0;         // +0x08
        int      mPad1;         // +0x0C
    };
    cSPUILayout* mpLayout;      // +0x00
    int          mId;           // +0x04
    void*        mpOwner;       // +0x08
    int          mMode;         // +0x0C
    Slot         mSlots[6];     // +0x10
    Slot*        mpSlot70;      // +0x70 (selected slot)
    IWindow*     mpSelectedWindow; // +0x74
    int          mPad78;        // +0x78
    int          mPad7C;        // +0x7C
    Slot*        mpCurrentSlot; // +0x80
    char         mFlag84;       // +0x84
};

extern cMarkerTextDialog* g_pActive;   // 0x016c7d90
extern cMarkerTextDialog* g_pDialog1;  // 0x016c7d94
extern cMarkerTextDialog* g_pDialog2;  // 0x016c7d98

// ---------------------------------------------------------------------------
// Externals defined elsewhere in the binary.
// ---------------------------------------------------------------------------
void FUN_00f0aa80();
void FUN_00f0b8b0();
void FUN_00f0ba10();
void FUN_00f0b940(int mode);
void FUN_00f0bec0(IWindow* win);
void FUN_00f0c000(cMarkerTextDialog::Slot* slot);
void FUN_00f0c210();
void FUN_00f0c310(float dt);
void* FUN_00f0b420(int index);
int  FUN_00f078b0(const Vector2* v, float dy);
void FUN_00f088c0(IWindow* win, const Vector2* v);
void FUN_00f08890(int);
void FUN_00f089a0(void*);
int  FUN_008d3200(int, int);
char FUN_008d2fb0(int);

void* operator_new(uint32_t size, const char* tag, int a, int b, int c, int d);
void operator_delete__(void* p);

IWindowManager* SP_WindowManager();
IMessageServer* SP_MessageServer();
void SP_KillSetiEffects(int, int);
IUISystem* EA_Audio_GetSystemAT();
void SPUIHelpers_BeginModal(IWindow*, int, int);
void SPUIHelpers_EndModal(IWindow*, int, int);

// ---------------------------------------------------------------------------
// @ 0x00f0bb90  Close/destroy the active marker-text dialog.
// ---------------------------------------------------------------------------
void FUN_00f0bb90() {
    cMarkerTextDialog* d = g_pActive;
    if (d != 0 && d->mpCurrentSlot != 0) {
        FUN_00f0ba10();
    }
    if (g_pActive == g_pDialog1) {
        cSPUILayout* layout = g_pActive->mpLayout;
        layout->FindWindowByID(0x7de6958, true)->SetFlag(1, 0);
        if (g_pActive == g_pDialog1) {
            layout = g_pActive->mpLayout;
            layout->FindWindowByID(0x7de6960, true)->SetFlag(0x400, 1);
        }
    } else if (g_pActive == g_pDialog2) {
        cSPUILayout* layout = g_pActive->mpLayout;
        IWindow* w = layout->FindWindowByID(0x7de6958, true);
        SPUIHelpers_EndModal(w, 0, 1);
        layout = g_pActive->mpLayout;
        layout->SetVisibility(0);
    }
    if (g_pActive != 0) {
        g_pActive->mSlots[5].mpWindow->SetFlag(1, 0);
        g_pActive->mSlots[5].mIndex = -1;
        g_pActive = 0;
    }
    IMessageServer* s = SP_MessageServer();
    s->v14(0x7ef2d80, 0, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00f0bc80  Open the marker-text dialog bound to the given record.
// ---------------------------------------------------------------------------
extern int FUN_00f3e8a0(int);

void FUN_00f0bc80(int* param) {
    if (g_pActive != 0) {
        FUN_00f0bb90();
    }
    cMarkerTextDialog* d = g_pDialog2;
    g_pActive = d;
    d->mpSelectedWindow = 0;      // +0x74
    d->mpCurrentSlot = 0;         // +0x80
    cSPUILayout* layout = d->mpLayout;
    IWindow* win = layout->FindWindowByID(0x7de6958, true);
    cSPUILayout* layout2 = g_pActive->mpLayout;
    layout2->SetVisibility(1);
    int v = g_pGlobalUIManager->mpManager74->GetValue(param[1]);
    int mode = 3;
    g_pActive->mpOwner = param;
    g_pActive->mId = v;
    g_pActive->mMode = mode;
    SPUIHelpers_BeginModal(win, 0, 1);
    cSPUILayout* layout3 = g_pActive->mpLayout;
    IWindow* w2 = layout3->FindWindowByID(0xcefa0002, true);
    if (w2 != 0) {
        IWindow* w3 = w2->Cast(0x8ed27e7a);
        if (w3 != 0) w3->v28(4, 1);
    }
    cMarkerTextDialog* d2 = g_pActive;
    d2->mMode = mode;

    IWindow* slotWin = 0;
    int i = 0;
    do {
        i++;
        if (d2->mSlots[i - 1].mIndex == 0) {
            slotWin = d2->mSlots[i - 1].mpWindow;
            break;
        }
    } while (i < 5);
    IWindow* w4 = slotWin->FindWindowByID(0xcefa1100, true);
    IWindowManager* wm = SP_WindowManager();
    wm->v4C(0, w4);
    FUN_00f0b8b0();
}

// ---------------------------------------------------------------------------
// @ 0x00f0bd90  Open dialog #1 (shared tail with FUN_00f0bdf0).
// ---------------------------------------------------------------------------
void FUN_00f0bd90(int arg1, int arg2) {
    cMarkerTextDialog* d = g_pDialog1;
    g_pActive = d;
    d->mpSelectedWindow = 0;   // +0x74
    d->mpCurrentSlot = 0;      // +0x80
    cSPUILayout* lay = d->mpLayout;
    lay->FindWindowByID(0x7de6958, true)->SetFlag(1, 1);
    cMarkerTextDialog* d2 = g_pActive;
    d2->mId = arg1;
    d2->mpOwner = 0;
    FUN_00f0b940(arg2);
}

// ---------------------------------------------------------------------------
// @ 0x00f0bdf0  Toggle the marker-text dialog between the two layouts.
// ---------------------------------------------------------------------------
void FUN_00f0bdf0(int arg1, int arg2) {
    if (g_pActive == 0) {
        IUISystem* sys = EA_Audio_GetSystemAT();
        int v = sys ? sys->v20() : 0;
        SP_KillSetiEffects(0x72d342a9, v);
        FUN_00f0bd90(arg1, arg2);
        return;
    }
    if (g_pActive != g_pDialog1) return;
    IUISystem* sys = EA_Audio_GetSystemAT();
    int v = sys ? sys->v20() : 0;
    SP_KillSetiEffects(0x1db24d95, v);
    FUN_00f0bb90();
}

// ---------------------------------------------------------------------------
// @ 0x00f0be80  Close if the active dialog's id doesn't match.
// ---------------------------------------------------------------------------
void FUN_00f0be80(int id) {
    if (g_pActive == 0) return;
    if (g_pActive->mId != id) {
        FUN_00f0bb90();
        return;
    }
    FUN_00f0b8b0();
}

// ---------------------------------------------------------------------------
// @ 0x00f0bea0  Close if dialog #1 is active.
// ---------------------------------------------------------------------------
void FUN_00f0bea0() {
    if (g_pActive != 0 && g_pActive == g_pDialog1) {
        FUN_00f0bb90();
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f0c210  Switch to the "marker" preset.
// ---------------------------------------------------------------------------
void FUN_00f0c210() {
    IUISystem* sys = EA_Audio_GetSystemAT();
    int v = sys ? sys->v20() : 0;
    sys = EA_Audio_GetSystemAT();
    if (sys != 0) {
        sys->v38(0x3475365);
        sys->v40(0x3475381, 0x1db24d95);
        sys->v40(0x3475385, v);
        sys->v58();
    }
    FUN_00f0bb90();
    g_pGlobalUIManager->mpChecklist->ToggleHint(0x6c, 0x6d);
}

// ---------------------------------------------------------------------------
// @ 0x00f0c290  Shut the dialogs down and delete them.
// ---------------------------------------------------------------------------
void FUN_00f0c290() {
    FUN_00f0bb90();
    cSPUILayout* lay = g_pDialog1->mpLayout;
    if (lay != 0) {
        g_pDialog1->mpLayout = 0;
        lay->Release();
    }
    if (g_pDialog1 != 0) {
        if (g_pDialog1->mpLayout != 0) g_pDialog1->mpLayout->Release();
        operator_delete__(g_pDialog1);
    }
    g_pDialog2->mpLayout->Shutdown(1);
    if (g_pDialog2 != 0) {
        if (g_pDialog2->mpLayout != 0) g_pDialog2->mpLayout->Release();
        operator_delete__(g_pDialog2);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f0bec0  Select the tool slot whose parent window is `param`.
// ---------------------------------------------------------------------------
struct cSlotInfo { char pad[0x40]; int field40; };

// EA::UTFWin / Messaging message passed to window procedures (fields used by c680).
struct Message {
    IWindow* mpSource;      // +0x00
    int      field04;       // +0x04
    uint32_t mType;         // +0x08
    int      field0C;       // +0x0C (command id)
    int      field10;       // +0x10
    int      field14;       // +0x14
    IWindow* mpDest;        // +0x18
};

void FUN_00f0b4d0(void*);
void FUN_00f0c680_impl();
char FUN_00f08c20();
void FUN_00f08b70(void*);
void FUN_00f08920();
void FUN_00f077c0(IWindow*, int, int);
void FUN_00f0ab50(IWindow*, int, int);
int  FUN_00edc9e0(void*, int);
int  FUN_00435e90();
float FUN_00f07960(float, float, uint32_t);

void FUN_00f0bec0(IWindow* param) {
    IWindow* parent = param->GetParent();
    cMarkerTextDialog* d = g_pActive;
    cMarkerTextDialog::Slot* slot = d->mSlots;
    int i = 0;
    while (slot->mpWindow != parent) {
        i++;
        slot++;
        if (i >= 5) { slot = 0; break; }
    }
    int id = slot->mIndex < 3 ? 0x1742be58 : 0x1742be59;
    IWindow* win = d->mpLayout->FindWindowByID(id, true);
    cSlotInfo* info = (cSlotInfo*)FUN_00f0b420(slot->mIndex);
    IWindow* w2 = param->Cast(0x8ed27e7a);
    if (w2 != 0) w2->v28(4, 1);
    IWindow* w3 = win->FindWindowByID(info->field40 + 0x742cbe0, true);
    if (w3 != 0) {
        IWindow* w4 = w3->Cast(0x8ed27e7a);
        if (w4 != 0) w4->v28(4, 1);
    }
    IWindow* w5 = slot->mpWindow->FindWindowByID(0x742bed0, true);
    Vector2 v = w5->vC0(Vector2());
    FUN_00f088c0(win, &v);
    d->mpSelectedWindow = param;
    win->SetFlag(1, 1);
    d->mpSlot70 = slot;
}

// ---------------------------------------------------------------------------
// @ 0x00f0c000  Move the dragged slot's window into the target slot.
// ---------------------------------------------------------------------------
void FUN_00f0c000(cMarkerTextDialog::Slot* param) {
    IWindow* w = param->mpWindow;
    const float* r = w->GetArea();
    Vector2 v;
    v.x = r[0];
    v.y = r[1];
    const float* r2 = w->GetArea();
    int idx = FUN_00f078b0(&v, r2[3] - r2[1]);
    if (idx == -1) return;
    cMarkerTextDialog* d = g_pActive;
    cMarkerTextDialog::Slot* slot = 0;
    int target = (idx == 4) ? 0 : 4;
    for (int i = 0; i < 5; i++) {
        if (d->mSlots[i].mIndex == target) { slot = &d->mSlots[i]; break; }
    }
    cMarkerTextDialog::Slot* cur = &d->mSlots[5];
    IWindow* savedWin = cur->mpWindow;
    *cur = *slot;
    *slot = *param;
    slot->mpWindow = savedWin;
    savedWin->SetLocation(v.x, v.y);
    slot->mpWindow->SetShadeColor(0xffffffff);
    slot->mpWindow->SetFlag(1, 1);
    IWindow* a = slot->mpWindow->FindWindowByID(0xcefa1100, false);
    IWindow* b = param->mpWindow->FindWindowByID(0xcefa1100, false);
    a->v80(b->v3C());
    if (idx == 4) {
        for (int i = 0; i < 5; i++)
            if (&d->mSlots[i] != param) d->mSlots[i].mIndex += -1;
    } else {
        for (int i = 0; i < 5; i++)
            if (&d->mSlots[i] != param && d->mSlots[i].mIndex >= idx)
                d->mSlots[i].mIndex++;
    }
    FUN_00f0aa80();
    FUN_00f0b8b0();
}

// ---------------------------------------------------------------------------
// @ 0x00f0c310  Per-frame update of the marker-text dialog (scroll animation).
// ---------------------------------------------------------------------------
void FUN_00f0c310(float dt) {
    if (g_pActive == 0) return;
    char ban = FUN_008d2fb0(1000);
    if (ban == 0) {
        if (g_pActive->mpCurrentSlot != 0) FUN_00f0ba10();
    } else if (g_pActive->mpCurrentSlot != 0) {
        FUN_00f089a0(g_pActive->mpCurrentSlot);
    }
    cMarkerTextDialog* d = g_pActive;
    for (int i = 0; i < 5; i++) {
        cMarkerTextDialog::Slot* p = &d->mSlots[i];
        if (p != d->mpCurrentSlot) {
            const float* r = p->mpWindow->GetArea();
            float dy = (r[3] - r[1]) * (float)p->mIndex;
            const float* r2 = p->mpWindow->GetArea();
            float x = r2[0];
            float y = r2[1];
            float nx;
            if (4.0f <= fabsf(x)) {
                float neg = -x;
                nx = neg * 0.2f + x;
                if (fabsf(x - nx) < 4.0f) nx = (fabsf(neg) / neg) * 4.0f + x;
            } else {
                nx = 0.0f;
            }
            if (4.0f <= fabsf(y - dy)) {
                float diff = dy - y;
                dy = diff * 0.2f + y;
                if (fabsf(y - dy) < 4.0f) dy = y + (fabsf(diff) / diff) * 4.0f;
            }
            p->mpWindow->SetLocation(nx, dy);
        }
    }
    d = g_pActive;
    if (d->mFlag84 == 0) {
        char c = (char)FUN_008d3200(0x12, 0x3ff);
        if (c != 0 && d->mpCurrentSlot != 0) {
            FUN_00f0c000(d->mpCurrentSlot);
            d = g_pActive;
            d->mFlag84 = 1;
        } else {
            d->mFlag84 = 0;
        }
    } else {
        char c = (char)FUN_008d3200(0x12, 0x3ff);
        d = g_pActive;
        if (c == 0) d->mFlag84 = 0;
    }
    if (d->mSlots[5].mIndex != -1) {
        IWindow* sw = d->mSlots[5].mpWindow;
        uint32_t t = sw->GetShadeColor();
        uint32_t elapsed = (uint32_t)(dt * 1000.0f);
        if ((t >> 24) <= elapsed) {
            sw->SetFlag(1, 0);
            d = g_pActive;
            d->mSlots[5].mIndex = -1;
        }
        if (d->mSlots[5].mIndex != -1) {
            IWindow* sw2 = d->mSlots[5].mpWindow;
            uint32_t cur = sw2->GetShadeColor();
            sw2->SetShadeColor((int)((cur & 0xffffff) | (((t >> 24) - elapsed) << 24)));
            sw2->SetFlag(1, 1);
            const float* r = sw2->GetArea();
            float h = r[3] - r[1];
            if (d->mSlots[5].mIndex == 4) h = h * 5.0f; else h = -h;
            float res = FUN_00f07960(r[1], h, elapsed);
            sw2->SetLocation(r[0], res);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f0c680  Window-procedure message handler (bool __stdcall(int, Message*)).
// ---------------------------------------------------------------------------
static IWindow* FindSlotWindow(cMarkerTextDialog* d, int target) {
    for (int i = 0; i < 5; i++)
        if (d->mSlots[i].mIndex == target) return d->mSlots[i].mpWindow;
    return 0;
}

static int AddSlotWindowToManager(cMarkerTextDialog* d, int mode) {
    d->mMode = mode;
    IWindow* win = FindSlotWindow(d, 0);
    IWindow* found = win->FindWindowByID(0xcefa1100, true);
    IWindowManager* wm = SP_WindowManager();
    wm->v4C(0, found);
    FUN_00f0b8b0();
    return 1;
}

static int C680CommonTail(Message* msg) {
    if (msg->field0C != 0) return 0;
    IWindow* w = msg->mpDest;
    int id = (int)w->GetControlID();
    if (id == (int)0xcefa1230 || id == (int)0xcefa1100 /* -0x3105ef00 */ ||
        id == (int)0xcefa1210 || id == (int)0xcefa1220 ||
        id == (int)0xcefa1240 || id == 0x742bdd0) {
        IWindow* r = w->GetParent();
        FUN_00f0b4d0(r);
    }
    return 0;
}

int __stdcall FUN_00f0c680(void* pWindow, Message* msg) {
    (void)pWindow;
    uint32_t type = msg->mType;
    int cmd = msg->field0C;
    if (type < 0x1c) {
        if (type != 0x1b) {
            if (type == 1) {
                if (msg->field10 != 0x1b) return 0;
                FUN_00f0c210();
                return 1;
            }
            if (type != 0x18) return 0;
            if (msg->mpSource == 0) return 0;
            if (msg->mpSource->GetControlID() != 0xcefa1100) return 0;
            FUN_00f0aa80();
            FUN_00f0b8b0();
            return 0;
        }
    } else {
        if (type == 0x1c) {
            if (cmd != 0) return 0;
            int cid = (int)msg->mpDest->GetControlID();
            if (cid == (int)0xcefa1100) {
                FUN_00f0aa80();
                FUN_00f0b8b0();
            }
            IWindow* mw = SP_WindowManager()->GetMainWindowIndex(0);
            if (g_pActive->mpSelectedWindow != 0 &&
                FUN_00edc9e0(mw, 0x1742be59) == 0 &&
                FUN_00edc9e0(mw, 0x1742be58) == 0) {
                FUN_00f08920();
                FUN_00f0b8b0();
            }
            if (FUN_00f08c20() == 0) return 0;
            FUN_00f0bb90();
            return 0;
        }
        if (type != 0x287259f6) return 0;

        int flag = 0;   // set by the KillSetiEffects lab
        if (cmd < (int)0xcefa1231) {
            if (cmd == (int)0xcefa1230) { flag = 1; }
            else if (cmd < (int)0xcefa0003) {
                if (cmd == (int)0xcefa0002) {
                    int r = FUN_00435e90();
                    SP_KillSetiEffects(0xe76c9b4f, r);
                } else if (cmd == (int)0xcefa0000) {
                    int r = FUN_00435e90();
                    SP_KillSetiEffects(0xe76c9b4f, r);
                    FUN_00f0b940(1);
                    return 1;
                } else if (cmd == (int)0xcefa0001) {
                    FUN_00435e90();
                    SP_KillSetiEffects(0xe76c9b4f, 0);
                    IWindow* w = g_pActive->mpLayout->FindWindowByID(0xcefa0001, true);
                    if (w != 0) {
                        IWindow* c = w->Cast(0x8ed27e7a);
                        if (c != 0) c->v28(4, 1);
                    }
                    return AddSlotWindowToManager(g_pActive, 2);
                }
            } else if (cmd == (int)0xcefa1210 || cmd == (int)0xcefa1220) {
                flag = 1;
            }
        } else if (cmd < 0x595e0ba) {
            if (cmd == 0x595e0b9) {
                FUN_00f08890(0);
                IWindow* r = msg->mpSource->GetParent();
                FUN_00f08b70(r);
                return 1;
            }
            if (cmd == (int)0xcefa1240) flag = 1;
            else if (cmd == 0x595e0a8) { FUN_00f0c210(); return 1; }
        } else {
            if (cmd == 0x742bdd0) {
                FUN_00435e90();
                SP_KillSetiEffects(0xe76c9b4f, 0);
                if (g_pActive->mpSelectedWindow != 0) {
                    FUN_00f08920();
                    FUN_00f0b8b0();
                    return 1;
                }
                FUN_00f0bec0(msg->mpSource);
                FUN_00f08890(0);
                return 1;
            }
            if (cmd > 0x742cbdf && cmd < 0x742cbe5) {
                int r = FUN_00435e90();
                SP_KillSetiEffects(0xe76c9b4f, r);
                FUN_00f0ab50(msg->mpSource, 0xcc089e57, r);
                return 1;
            }
        }
        if (flag) {
            IUISystem* sys = EA_Audio_GetSystemAT();
            int r = sys ? sys->v20() : 0;
            SP_KillSetiEffects(0xe76c9b4f, r);
            FUN_00f077c0(msg->mpSource, 0xe76c9b4f, r);
            FUN_00f0aa80();
            FUN_00f0b8b0();
            IWindow* p = msg->mpSource->GetParent();
            IWindow* found = p->FindWindowByID(0xcefa1100, false);
            IWindowManager* wm = SP_WindowManager();
            wm->v4C(0, found);
            return 1;
        }
    }
    return C680CommonTail(msg);
}
