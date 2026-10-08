// Slice s00ed74f0 -- scenario-editor toolbar message handler (UTFWin button clicks).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- data types
struct Key12 {                       // resource key: instance/type/group
    uint32_t a, b, c;
};

// ---------------------------------------------------------------- globals
extern char     g_16065f8;           // 0x016065f8: UI enabled flag
extern Key12    g_15ac220;   // 0x015ac220
extern Key12    g_15ac22c;   // 0x015ac22c
extern Key12    g_15ac238;   // 0x015ac238
extern Key12    g_15ac250;   // 0x015ac250
extern Key12    g_15ac25c;   // 0x015ac25c
extern Key12    g_15ac268;   // 0x015ac268
extern const wchar_t g_13ec468[];    // L"" 0x013ec468

// ---------------------------------------------------------------- UTFWin pieces
struct IWindow {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6();
    virtual uint32_t GetControlID();                 // +0x1c
};
struct Message {
    IWindow* source;                                 // +0
    uint32_t pad4;
    uint32_t type;                                   // +8
};

// ---------------------------------------------------------------- external objects
struct cMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint32_t id, int a, int b);    // +0x14
};
struct cAudioSystem {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual int  GetState();                         // +0x20
};
struct cUIGate {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual bool IsBlocked();                        // +0x38
};
extern cUIGate* g_15ad298;                           // 0x015ad298

struct cNotifyTarget {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void SetText(const wchar_t* text, int flags);   // +0x34
};
struct cNotifyHost {                                 // 0x0067de40 singleton
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual cNotifyTarget* GetTarget();              // +0x20
};
struct cText { const wchar_t* GetText(); };          // 0x006b55c0
struct cUIHint {
    char pad[0x78];
    cText mText;                                     // +0x78
};
struct cUIHints {
    cUIHint* FindByID(uint32_t id);                  // 0x0067aee0
    void     ShowHint(uint32_t id);                  // 0x0067c830
};
struct cNode;
struct cSim {                                        // *(g + 0x74)
    bool   Classify(int* out);                       // 0x00f41270
    bool   f3b920();                                 // 0x00f3b920
    bool   f3b950();                                 // 0x00f3b950
    cNode* ff3f00();                                 // 0x00ff3f00
    bool   f41420(cNode* n, int a, int b, int c);    // 0x00f41420
    void   f45970();                                 // 0x00f45970
    int    f3bf60();                                 // 0x00f3bf60
    void   f3bcc0(int n);                            // 0x00f3bcc0
    void   f45a80();                                 // 0x00f45a80
    void   f427c0();                                 // 0x00f427c0
};
struct cTutorials {
    void MarkDirty();                                // 0x00ef72c0
    void f8860();                                    // 0x00ef8860
};
struct cHintPanel { void f69a0(int a); };            // *(g + 0xd8); 0x00f069a0
struct cOwned {                                      // *(this + 0x3c)
    void e02e80();                                   // 0x00e02e80
    void e018c0(int a);                              // 0x00e018c0
};
struct cGlobals {
    char        pad0[0x74];
    cSim*       sim;                                 // +0x74
    char        pad1[0xd4 - 0x78];
    cTutorials* tutorials;                           // +0xd4
    cHintPanel* hints;                               // +0xd8
};
extern cGlobals* g_16c7aa4;                          // 0x016c7aa4

struct cSporeGuide { void FUN_00ed4930(); };         // thiscall on a global object (ignores ecx)
extern cSporeGuide g_16c7680;                       // 0x016c7680

cMessageServer* __cdecl MessageServer();             // 0x0067dcc0
cUIHints*       __cdecl UIHints();                   // 0x0067cac0
cNotifyHost*    __cdecl NotifyHost();                // 0x0067de40
cAudioSystem*   __cdecl GetSystemAT();               // 0x00a206f0
int             __cdecl GetRecorderState();          // 0x00435e90
void            __cdecl PlayUISound(uint32_t id, int state);   // 0x00435ed0
int             __cdecl GetCurrentGameMode();        // 0x00b5b800
void            __cdecl ShowSettingsWindow(int mode);          // 0x006035d0
void            __cdecl ShowContextSensitiveSporeGuide();      // 0x00e02200
void            __cdecl CalloutMessageBox(void* where, const Key12* key);   // 0x00809db0
int             __stdcall HintForState(int state);   // 0x00f3b2c0 ($E366)

// ---------------------------------------------------------------- the panel
struct Panel {                                       // primary object; the handler is its base at +8
    char pad0[0xc];
    char mCallout[0x48];                             // +0x0c
    int  mCalloutKey;                                // +0x54
    int  mMode;                                      // +0x58
    void FUN_00ed5910();                             // 0x00ed5910
    void FUN_00ed5640();                             // 0x00ed5640
    void FUN_00ed6720(int i);                        // 0x00ed6720
    void FUN_00ed76e0(int i);                        // 0x00ed76e0
};

struct PanelHandler {                                // sub-object at Panel+8
    virtual void h0();
    virtual bool DoMessage(IWindow* w, const Message* msg);
    Panel* panel() { return (Panel*)((char*)this - 8); }
    char   pad4[0x14 - 4];
    int    mActiveSet;                               // +0x14
    char   pad18[0x3c - 0x18];
    cOwned* mOwned;                                  // +0x3c
};

// @ 0x00ed7a10
bool PanelHandler::DoMessage(IWindow* w, const Message* msg)
{
    (void)w;
    if (!g_16065f8 || g_15ad298->IsBlocked())
        return false;
    if (msg->type != 0x287259f6)
        return false;

    switch (msg->source->GetControlID())
    {
    case 0x10f366e:
        mOwned->e02e80();
        MessageServer()->Post(0x101, 0, 0);
        g_16c7aa4->tutorials->f8860();
        return false;

    case 0x10f366d: {
        Panel* p = panel();
        cSim* sim = g_16c7aa4->sim;
        if (sim == 0) return false;
        p->mMode = 7;
        int* out = (int*)&msg;           // the original reuses the dead message-pointer slot
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac268;
            else               key = g_15ac250;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac25c;
            if (!sim->f3b920()) { p->FUN_00ed5910(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(p->mCallout, &key);
        p->mCalloutKey = key.a;
        return false;
    }

    case 0x2268ba4: {
        Panel* p = panel();
        cSim* sim = g_16c7aa4->sim;
        if (sim == 0) return false;
        p->mMode = 6;
        int* out = (int*)&msg;
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac268;
            else               key = g_15ac250;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac25c;
            if (!sim->f3b920()) { p->FUN_00ed5910(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(p->mCallout, &key);
        p->mCalloutKey = key.a;
        return false;
    }

    case 0x4766ff0: {
        PlayUISound(0xe76c9b4f, GetRecorderState());
        cSim* sim = g_16c7aa4->sim;
        Panel* p = panel();
        if (sim == 0) return false;
        p->mMode = 5;
        int* out = (int*)&msg;
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac238;
            else               key = g_15ac220;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac22c;
            if (!sim->f3b920()) { p->FUN_00ed5910(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(p->mCallout, &key);
        p->mCalloutKey = key.a;
        return false;
    }

    case 0x43b72d0:
        ShowSettingsWindow(GetCurrentGameMode());
        return false;

    case 0x447060a:
        ShowContextSensitiveSporeGuide();
        g_16c7aa4->tutorials->MarkDirty();
        return false;

    case 0x44ea79e:
        MessageServer()->Post(0x44eaa93, 0, 0);
        mOwned->e018c0(0);
        return true;

    case 0x62025f9:
        MessageServer()->Post(0x620222b, 0, 0);
        mOwned->e018c0(0);
        return true;

    case 0x6fcb630:
        g_16c7680.FUN_00ed4930();
        return false;

    case 0x6fcb638: {
        cAudioSystem* at = GetSystemAT();
        int state = at ? at->GetState() : 0;
        PlayUISound(0xcc089e57, state);
        MessageServer()->Post(0x101, 0, 0);
        return false;
    }

    case 0x7104130:
        if (mActiveSet == 0) return false;
        panel()->FUN_00ed6720(0);
        return false;

    case 0x7104131: {
        if (mActiveSet == 1) return false;
        cSim* sim = g_16c7aa4->sim;
        cNode* node = sim->ff3f00();
        if (node && sim->f41420(node, 0, 0, 0)) {
            panel()->FUN_00ed6720(1);
            return false;
        }
        UIHints()->ShowHint(0xb192f625);
        return false;
    }

    case 0x7104132:
        if (mActiveSet == 2) return false;
        panel()->FUN_00ed6720(2);
        return false;

    case 0x774b060: {
        g_16c7aa4->sim->f45970();
        cSim* sim = g_16c7aa4->sim;
        sim->f3bcc0(sim->f3bf60() + 1);
        g_16c7aa4->sim->f45a80();
        PlayUISound(0xcec93ef5, GetRecorderState());
        panel()->FUN_00ed5640();
        g_16c7aa4->sim->f427c0();
        return false;
    }

    case 0x78d57d8:
        g_16c7aa4->hints->f69a0(0);
        return false;

    case 0x90439d7c:
        PlayUISound(0xe76c9b4f, GetRecorderState());
        panel()->FUN_00ed76e0(1);
        return false;

    case 0xbbbb1001:
        PlayUISound(0xe76c9b4f, GetRecorderState());
        panel()->FUN_00ed76e0(3);
        return false;

    case 0xb006ef6e:
        MessageServer()->Post(0xc9d86390, 0, 0);
        return false;

    case 0xf006efa5:
        MessageServer()->Post(0xc9d86391, 0, 0);
        return false;
    }
    return false;
}
