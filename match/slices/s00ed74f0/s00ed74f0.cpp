// Slice s00ed74f0 -- scenario-editor toolbar message handler (UTFWin button clicks).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- data types
struct Key12 {                       // resource key: instance/type/group
    uint32_t a, b, c;
};

// ---------------------------------------------------------------- globals
extern char     g_16065f8;           // 0x016065f8: UI enabled flag
extern Key12    g_15ac190;   // 0x015ac190
extern Key12    g_15ac19c;   // 0x015ac19c
extern Key12    g_15ac1cc;   // 0x015ac1cc
extern Key12    g_15ac1f0;   // 0x015ac1f0
extern Key12    g_15ac1fc;   // 0x015ac1fc
extern Key12    g_15ac208;   // 0x015ac208
extern Key12    g_15ac220;   // 0x015ac220
extern Key12    g_15ac22c;   // 0x015ac22c
extern Key12    g_15ac238;   // 0x015ac238
extern Key12    g_15ac250;   // 0x015ac250
extern Key12    g_15ac25c;   // 0x015ac25c
extern Key12    g_15ac268;   // 0x015ac268
extern const wchar_t g_13ec468[];    // L"" 0x013ec468
extern const float g_1488874;        // 0x01488874: 0.1f
extern const float g_1485378;        // 0x01485378: 0.0f
extern const float g_148a228;        // 0x0148a228: FLT_MAX
extern char     g_1489fe8;           // 0x01489fe8: terrain hint blocks, 0x30 bytes apart
extern char     g_148a018;           // 0x0148a018
extern char     g_148a048;           // 0x0148a048
extern char     g_148a078;           // 0x0148a078
extern char     g_148a0a8;           // 0x0148a0a8

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
class cUIHints { public:
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
// The callout/message object embedded at Panel+0x0c.  Its address is what
// UI::CalloutMessageBox fills in, and 0x00ed74f0 is a method of it.
struct cVerbIconTray {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void SetSelected(int on);                // +0x1c
};

struct PanelCallout {
    char pad00[0x20];
    cVerbIconTray* mpVerbTray;                       // +0x20  == Panel+0x2c
    char pad24[0x3c - 0x24];
    int  mParam;                                     // +0x3c  == Panel+0x48
    int  mType;                                      // +0x40  == Panel+0x4c
    int  mExtra;                                     // +0x44  == Panel+0x50
    int  mKey;                                       // +0x48  == Panel+0x54
    int  mMode;                                      // +0x4c  == Panel+0x58
    void Dispatch(unsigned unused, unsigned selected);   // 0x00ed74f0
};

struct Panel {                                       // primary object; the handler is its base at +8
    char pad0[0xc];
    PanelCallout mCallout;                           // +0x0c
    void ShowCallout();                              // 0x00ed5910
    void SelectionChanged(int index);                // 0x00ed7490
    void FUN_00ed5640();                             // 0x00ed5640
    void FUN_00ed6720(int i);                        // 0x00ed6720
    void FUN_00ed76e0(int i);                        // 0x00ed76e0
    bool FUN_00ed8130(int msg, int type, int extra); // 0x00ed8130
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
        p->mCallout.mMode = 7;
        int* out = (int*)&msg;           // the original reuses the dead message-pointer slot
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac268;
            else               key = g_15ac250;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac25c;
            if (!sim->f3b920()) { p->ShowCallout(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(&p->mCallout, &key);
        p->mCallout.mKey = key.a;
        return false;
    }

    case 0x2268ba4: {
        Panel* p = panel();
        cSim* sim = g_16c7aa4->sim;
        if (sim == 0) return false;
        p->mCallout.mMode = 6;
        int* out = (int*)&msg;
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac268;
            else               key = g_15ac250;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac25c;
            if (!sim->f3b920()) { p->ShowCallout(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(&p->mCallout, &key);
        p->mCallout.mKey = key.a;
        return false;
    }

    case 0x4766ff0: {
        PlayUISound(0xe76c9b4f, GetRecorderState());
        cSim* sim = g_16c7aa4->sim;
        Panel* p = panel();
        if (sim == 0) return false;
        p->mCallout.mMode = 5;
        int* out = (int*)&msg;
        Key12 key;
        if (sim->Classify(out)) {
            if (sim->f3b950()) key = g_15ac238;
            else               key = g_15ac220;
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(*out);
            key = g_15ac22c;
            if (!sim->f3b920()) { p->ShowCallout(); return false; }
            if (key.a == 0) return false;
            cUIHint* h = UIHints()->FindByID(hint);
            cNotifyTarget* t = NotifyHost()->GetTarget();
            if (h == 0) t->SetText(g_13ec468, 0);
            else        t->SetText(h->mText.GetText(), 0);
        }
        CalloutMessageBox(&p->mCallout, &key);
        p->mCallout.mKey = key.a;
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

// ------------------------------------------------- editor noun helpers (0x00ed82e0..)
// Property store methods reached through the noun pointers below.
struct cStoreObj;

struct cPropStore {                                  // first argument of the two wrappers
    bool          Find(void* key);                   // 0x00c88940
    cStoreObj*    FindObj(void* key);                // 0x00c888e0
    void          Remove(void* key, int value);      // 0x00c8ad30
    void          Set3(void* a, void* b, void* c);   // 0x00c8b130
    void          SetMax(void* key, float value);    // 0x00c88a00
    void          SetA(void* key, float value);      // 0x00c8a200
    void          SetB(void* key, char value);       // 0x00c8a110
};

struct cStoreObj {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual uint64_t GetValue();                     // +0x60
};

struct cModelObj {
    char  pad0[0x220];
    float mValue;                                    // +0x220
};

struct cGameData {
    char     pad0[4];
    uint32_t mKind;                                  // +0x04
};

struct cEditorNoun {
    char       pad0[0x18];
    cModelObj* mpModel;                              // +0x18
    int        mSpecies;                             // +0x1c
    cModelObj* GetModel();                           // 0x006c0200
    cGameData* GetGameData();                        // 0x00b18530
};

// @ 0x00ed74f0
void PanelCallout::Dispatch(unsigned unused, unsigned selected)
{
    (void)unused;
    unsigned key = mKey;
    mKey = 0;
    if (key == 0x3cc9f2f3) {
        ((Panel*)((char*)this - 0xc))->ShowCallout();
        return;
    }

    bool is17, is1a, is1b, is19;
    is17 = false;
    is1b = false;
    is1a = false;
    switch (key)
    {
    case 0x48ee60f0: case 0x53830374: case 0x7c1ea6a4: case 0xb016b570:
        is17 = (selected == 0x5107b17);
        is19 = (selected == 0x5107b19);
        is1a = (selected == 0x5107b1a);
        break;

    case 0x811778da:
        is19 = (selected == 0x5107b17);
        is1b = (selected == 0x5107b19);
        is1a = (selected == 0x5107b1a);
        break;

    case 0x12b8ba66: case 0x9d533cda: case 0x8bf4d3f2: case 0xbe186a9a:
        is17 = (selected == 0x5107b17);
        is19 = (selected == 0x5107b18);
        is1b = (selected == 0x5107b19);
        is1a = (selected == 0x5107b1a);
        break;

    case 0x3a5ea067: case 0x5cd172a9: case 0xc6bdfccc: case 0xe6c74f99: case 0xf46fbea9:
        is19 = (selected == 0x5107b17);
        is17 = (selected == 0x5107b1a);
        break;

    case 0xc2b30789: case 0xeb3bc709: case 0xcf4c3d25: case 0xebdc80d5:
        is17 = (selected == 0x5107b17);
        is19 = (selected == 0x5107b19);
        is1b = (selected == 0x5107b1a);
        break;

    default:
        return;
    }

    cAudioSystem* at = GetSystemAT();
    int state = at ? at->GetState() : 0;
    PlayUISound(0xe76c9b4f, state);

    if (is19) { mMode = 0; return; }
    if (is17) { ((Panel*)((char*)this - 0xc))->ShowCallout(); return; }
    if (is1a) { ((Panel*)((char*)this - 0xc))->SelectionChanged(0); return; }
    if (is1b) { ((Panel*)((char*)this - 0xc))->SelectionChanged(1); }
}

// @ 0x00ed76e0
void Panel::FUN_00ed76e0(int mode)
{
    if (mode == 0)
        return;
    cSim* sim = g_16c7aa4->sim;
    if (sim == 0)
        return;
    mCallout.mMode = mode;
    int sel = mode;

    if (mode == 1) {
        if (sim->f3b920()) {
            CalloutMessageBox(&mCallout, &g_15ac19c);
            mCallout.mKey = g_15ac19c.a;
            return;
        }
        ShowCallout();
        return;
    }

    Key12 key;

    if (sim->Classify(&mode)) {
        bool high = sim->f3b950();
        int idx = sel - 2;
        key.a = 0; key.b = 0; key.c = 0;
        if (high) {
            switch (idx) {
            case 0: key = g_15ac190; break;
            case 1: key = g_15ac1cc; break;
            case 2: key = g_15ac208; break;
            case 3: key = g_15ac238; break;
            case 4: case 5: key = g_15ac268; break;
            }
        } else {
            switch (idx) {
            case 0: case 1: SelectionChanged(0); return;
            case 2: key = g_15ac1f0; break;
            case 3: key = g_15ac220; break;
            case 4: case 5: key = g_15ac250; break;
            }
        }
        CalloutMessageBox(&mCallout, &key);
        mCallout.mKey = key.a;
        return;
    }

    key.a = 0; key.b = 0; key.c = 0;
    int hint = HintForState(mode);
    switch (sel)
    {
    case 3:
        if (mode == 5) { ShowCallout(); return; }
        /* fall through */
    case 2:
        if (mode == 4 && mCallout.mpVerbTray != 0)
            mCallout.mpVerbTray->SetSelected(1);
        if (hint != 0)
            UIHints()->ShowHint(hint);
        mCallout.mMode = 0;
        return;

    case 4:
        key = g_15ac1fc;
        if (!sim->f3b920()) { ShowCallout(); return; }
        break;

    case 5:
        key = g_15ac22c;
        if (!sim->f3b920()) { ShowCallout(); return; }
        break;

    case 6: case 7:
        key = g_15ac25c;
        if (!sim->f3b920()) { ShowCallout(); return; }
        break;
    }

    if (key.a != 0) {
        cUIHint* h = UIHints()->FindByID(hint);
        cNotifyTarget* t = NotifyHost()->GetTarget();
        if (h == 0) t->SetText(g_13ec468, 0);
        else        t->SetText(h->mText.GetText(), 0);
        CalloutMessageBox(&mCallout, &key);
        mCallout.mKey = key.a;
    }
}

// @ 0x00ed8130
bool Panel::FUN_00ed8130(int msg, int type, int extra)
{
    if (type != 0x366a930d)
        return false;

    mCallout.mParam = msg;
    mCallout.mType  = type;
    mCallout.mExtra = extra;

    cSim* sim = g_16c7aa4->sim;
    if (sim != 0) {
        mCallout.mMode = 4;
        int out;
        Key12 key;
        if (sim->Classify(&out)) {
            if (sim->f3b950()) {
                key = g_15ac208;
                CalloutMessageBox(&mCallout, &key);
                mCallout.mKey = key.a;
            } else {
                key = g_15ac1f0;
                CalloutMessageBox(&mCallout, &key);
                mCallout.mKey = key.a;
            }
        } else {
            key.a = 0; key.b = 0; key.c = 0;
            int hint = HintForState(out);
            key = g_15ac1fc;
            if (!sim->f3b920()) {
                ShowCallout();
            } else if (key.a != 0) {
                cUIHint* h = UIHints()->FindByID(hint);
                cNotifyTarget* t = NotifyHost()->GetTarget();
                if (h == 0) t->SetText(g_13ec468, 0);
                else        t->SetText(h->mText.GetText(), 0);
                CalloutMessageBox(&mCallout, &key);
                mCallout.mKey = key.a;
            }
        }
    }
    g_16c7aa4->tutorials->f8860();
    return true;
}

// @ 0x00ed82e0
void FUN_00ed82e0(cPropStore* store, void* key, void* extra, char remove, float a, char b)
{
    bool found = store->Find(key);
    if (remove == 0) {
        if (found)
            store->Remove(key, 0);
        return;
    }
    if (found)
        return;
    store->Set3(key, extra, key);
    store->SetMax(key, g_148a228);
    store->SetA(key, a);
    store->SetB(key, b);
}

// @ 0x00ed8350
void FUN_00ed8350(cPropStore* store, void* key, unsigned idLo, unsigned idHi, char flag, float a, char b)
{
    cStoreObj* obj = store->FindObj(key);
    char changed;
    if (obj != 0) {
        uint64_t value = obj->GetValue();
        if ((unsigned)value != idLo || (unsigned)(value >> 32) != idHi)
            changed = 1;
        else
            changed = 0;
    } else {
        changed = 0;
    }

    if (flag == changed) {
        if (obj == 0)
            return;
        store->Remove(key, 0);
        if (!flag)
            return;
        if (!changed && obj != 0)
            return;
    } else if (obj != 0) {
        return;
    }

    store->Set3((void*)idLo, (void*)idHi, key);
    store->SetMax(key, g_148a228);
    store->SetA(key, a);
    store->SetB(key, b);
}

// @ 0x00ed83f0
void* FUN_00ed83f0(cEditorNoun* noun)
{
    void* result = &g_1489fe8;
    cModelObj* model = noun->GetModel();
    float value = model->mValue;
    bool positive = (g_1488874 < fabsf(value)) && (g_1485378 < value);

    uint32_t kind = noun->GetGameData()->mKind;
    switch (kind) {
    case 0x2399be55:
        return positive ? &g_148a0a8 : &g_148a078;
    case 0x24682294:
    case 0x476a98c7:
        return positive ? &g_148a048 : &g_148a018;
    }
    return result;
}
