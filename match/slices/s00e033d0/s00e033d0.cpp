// s00e033d0 -- Spore global-UI ban list / pause helper slice (retail Spore).
// Offsets and call sequences come from work/match/scratch_s00e033d0_cards.txt.
// Every function has exactly one `// @ 0x<VA>` marker above it.

typedef void  (__thiscall* TFnV)(void*);
typedef void  (__thiscall* TFnVI)(void*, int);
typedef void  (__thiscall* TFnVII)(void*, int, int);
typedef void  (__thiscall* TFnVIII)(void*, int, int, int);
typedef void  (__thiscall* TFnVIIII)(void*, int, int, int, int);
typedef void  (__thiscall* TC_VIIII)(void*, int, int, int, int);
typedef void  (__thiscall* TFnVPPP)(void*, void*, void*, void*);
typedef void  (__thiscall* TFnVP)(void*, void*);
typedef int   (__thiscall* TFnI)(void*);
typedef int   (__thiscall* TFnII)(void*, int);
typedef void* (__thiscall* TFnP)(void*);
typedef void* (__thiscall* TFnPI)(void*, int);
typedef void* (__thiscall* TFnPII)(void*, int, int);
typedef long long (__thiscall* TFnLL)(void*);

// explicit thiscall shapes for helpers reached through raw addresses
typedef void  (__thiscall* TC_V)(void*);
typedef void  (__thiscall* TC_VI)(void*, int);
typedef void  (__thiscall* TC_VII)(void*, int, int);
typedef void  (__thiscall* TC_VP)(void*, void*);
typedef int   (__thiscall* TC_I)(void*);
typedef int   (__thiscall* TC_II)(void*, int);
typedef long long (__thiscall* TC_LL)(void*);
typedef void* (__thiscall* TC_P)(void*);
typedef void* (__thiscall* TC_PI)(void*, int);
typedef void* (__thiscall* TC_PII)(void*, int, int);

#define VT(o, off) (*(void***)(o))[(off) / 4]

extern "C" void  __cdecl cof_delete(void*);                 // 0xf47380 operator_delete_array
extern "C" void* __cdecl cof_new(unsigned, const char*, int, int, const char*, int); // 0xf473a0
extern "C" void* __cdecl memcpy_(void*, const void*, unsigned); // 0x11e0744

// ---------------------------------------------------------------------------
// EASTL wide string (begin/end/capacity triple, as seen in the copy paths).

struct wstring {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08

    void __thiscall Assign(const wchar_t* first, const wchar_t* last); // 0x423650
    void __thiscall AllocateSelf(int n);                               // 0x429760
    void __thiscall RangeInit(const wchar_t* str);                     // 0x579a90
    void __thiscall Destroy();                                         // 0x5725a0
};

// ---------------------------------------------------------------------------
// One ban-list row (0x24 bytes).

struct BanVec;

struct BanEntry {
    int     miId;      // +0x00
    wstring mName;     // +0x04
    int     miUnk10;   // +0x10
    wstring mText;     // +0x14
    int     miExtra;   // +0x20

    BanEntry* __thiscall CopyFrom(const BanEntry& src);   // 0x00e03830
};

struct BanVec {
    BanEntry* mpBegin;   // +0x00
    BanEntry* mpEnd;     // +0x04
    BanEntry* mpCap;     // +0x08

    BanEntry* __thiscall EraseLast(BanEntry* pos);                    // 0x00e03c30
    BanEntry* __thiscall Insert(BanEntry* pos, const BanEntry& val);  // 0x00e03ca0
};

// Derived string-token translator embedded in the ban content (this = translator base).
struct BanTranslator {
    void*    mpVtbl;     // +0x00
    int      miUnk04;    // +0x04
    char     mbActive;   // +0x08 (BanContent+0x0c)
    char     mbHold;     // +0x09 (BanContent+0x0d)
    short    miPad0A;    // +0x0a
    int      miId;       // +0x0c
    wstring  mText;      // +0x10
    int      miUnk1C;    // +0x1c
    wstring  mExtra;     // +0x20
    int      miUnk2C;    // +0x2c
    BanVec   mList;      // +0x30

    bool __thiscall Format(const wchar_t* key, wchar_t* out);      // 0x00e03b80
};

// Ban content sub-object (0x40 bytes), embedded in the UI at +0xc.
struct BanContent {
    void*         mpVtbl;    // +0x00
    BanTranslator mTokens;   // +0x04

    void __thiscall Dtor();                     // 0x00e03930
    void __thiscall SetText(int id, const wchar_t* text, const void* extras); // 0x00e03590
    void __thiscall OnDeactivate(int a, int b); // 0x00e03e10
    void __thiscall OnToggle(char on);          // 0x00e03f40
    void __thiscall AddRow(int id, const wchar_t* name, const wchar_t* text); // 0x00e03e50
    void __thiscall Reactivate();               // 0x00e02e80 (external)
};

// One-stopwatch pause state used by the civ ban dialog.
struct Stopwatch {
    long long mTicks;     // +0x00
    int       miPad08;    // +0x08
    int       miPad0C;    // +0x0c
    int       miPad10;    // +0x10
    float     mfScale;    // +0x14
};

struct CivPauseUI {
    int       miPad00[9];  // +0x00
    int       miState;     // +0x24
    Stopwatch mStop1;      // +0x28
    Stopwatch mStop2;      // +0x40
    int       miHandler;   // +0x58

    void __thiscall Pause();                  // 0x00e033d0
    bool __thiscall OnMessage(int id, int arg); // 0x00e03a90
};

// Options object reachable from the UI at +4.
struct UIMessage {
    int miPad00;   // +0x00
    int miPad04;   // +0x04
    int miType;    // +0x08
    int miId;      // +0x0c
    int miSub;     // +0x10
    int miFlag;    // +0x14
};

struct cSPUIGlobalOptions {
    int   miPad00[3];   // +0x00
    int   miType;       // +0x0c
    int   miId;         // +0x10
    int   miSub;        // +0x14

    void __thiscall Reactivate();                        // 0x00e02e80
    void __thiscall Enable(int on);                      // 0x00e018c0
    bool __thiscall HandleMessage(int arg, UIMessage* msg); // 0x00e039d0
};

struct cSPUILayout;

// The global UI root, with the ban content embedded at +0xc.
struct cSPUIGlobalUI {
    void*            mpVtbl;        // +0x00
    cSPUIGlobalOptions* mpOptions;  // +0x04
    cSPUILayout*     mpLayout;      // +0x08
    BanContent       mBan;          // +0x0c
    int              miPad4C;       // +0x4c
    int              miPad50;       // +0x50
    void*            mpHandler;     // +0x54
    void*            mpHandlerThis; // +0x58
    int              miHandlerTag;  // +0x5c
    int              miHandlerCount;// +0x60
    int              miHandlerExtra;// +0x64

    bool __thiscall Init(int param);                                // 0x00e03620
    bool __thiscall Shutdown();                                     // 0x00e03740
    void* __thiscall Construct();                                   // 0x00e03ab0
    void __thiscall Destroy();                                      // 0x00e03b20
    void* __thiscall FindWindowByID(unsigned id);                   // 0x00e012b0
    void __thiscall ShowOptionWindows(char on);                     // 0x00e042d0
    bool __thiscall HandleMessage(unsigned msg, int arg);           // 0x00e03f80
    bool __thiscall AnyCivSlotUsed();                               // 0x00e042b0
    void* __thiscall AsInterface(unsigned id);                      // 0x00e04270
};

// ---------------------------------------------------------------------------
// external helpers (addresses from the cards)

extern "C" int   __cdecl FUN_00685520(int);                     // 0x00685520 IsWorldLayoutFlagSet
extern "C" void  __cdecl FUN_00809db0(void*, void*);            // 0x00809db0 CalloutMessageBox
extern "C" void* __cdecl FUN_0067de40();                        // 0x0067de40
extern "C" void* __cdecl FUN_0067de20();                        // 0x0067de20
extern "C" void* __cdecl FUN_008105b0(int, int, int);           // 0x008105b0
extern "C" void* __cdecl FUN_0067dd20();                        // 0x0067dd20
extern "C" void* __cdecl FUN_0067dcc0();                        // 0x0067dcc0 MessageServer
extern "C" void* __cdecl FUN_0067cab0(int);                     // 0x0067cab0
extern "C" void* __cdecl FUN_0067cac0();                        // 0x0067cac0
extern "C" void  __cdecl FUN_0067ca40(void*);                   // 0x0067ca40
extern "C" void* __cdecl FUN_00b3d340(int, int);                // 0x00b3d340
extern "C" void* __cdecl FUN_00b3d380();                        // 0x00b3d380 GameTimeManager
extern "C" void* __cdecl FUN_00b5b800();                        // 0x00b5b800 GetCurrentGameMode
extern "C" void* __cdecl FUN_00b5b820();                        // 0x00b5b820 GetCurrentGameModeAlt
extern "C" void* __cdecl FUN_01021370();                        // 0x01021370 home planet
extern "C" void* __cdecl FUN_00e01620(int, int);                // 0x00e01620
extern "C" char  __cdecl FUN_00e00ac0();                        // 0x00e00ac0
extern "C" char  __cdecl FUN_00e09540();                        // 0x00e09540
extern "C" char  __cdecl FUN_00dd1230();                        // 0x00dd1230
extern "C" void  __cdecl FUN_00e009f0();                        // 0x00e009f0
extern "C" void  __cdecl FUN_00e02200();                        // 0x00e02200
extern "C" void  __cdecl FUN_00e09600();                        // 0x00e09600
extern "C" void  __cdecl FUN_00e097c0();                        // 0x00e097c0
extern "C" void  __cdecl FUN_00dd14b0();                        // 0x00dd14b0
extern "C" void  __cdecl FUN_00dd12f0();                        // 0x00dd12f0
extern "C" void  __cdecl FUN_00571db0(void*, void*, int, int, int); // 0x00571db0 RemoveHandler
extern "C" void  __cdecl FUN_00e02c60(void*, void*);            // 0x00e02c60 vector clear
extern "C" void* __cdecl FUN_00e038e0(void*, void*, void*);     // 0x00e038e0
extern "C" void* __cdecl FUN_00e02cc0(void*, void*, void*);     // 0x00e02cc0
extern "C" void  __cdecl FUN_00e02d30(void*, void*, void*);     // 0x00e02d30
extern "C" void  __cdecl FUN_00e02da0(void*, void*, void*);     // 0x00e02da0
extern "C" void  __cdecl FUN_00e02e10(void*);                   // 0x00e02e10
extern "C" void  __cdecl FUN_00e02af0(void*);                   // 0x00e02af0
extern "C" int   __cdecl WStr_Format(wchar_t*, unsigned, ...);  // 0x0041e050
extern "C" unsigned __cdecl FNV1_String16(const wchar_t*, unsigned, int); // 0x00932f30
extern "C" void  __cdecl FUN_0076d( );                          // placeholder-free

// globals
static unsigned char& g_bPaused        = *(unsigned char*)0x016a1890;
static void*&         g_pTranslator    = *(void**)0x0169e3e8;
static const unsigned kGameModeBase    = 0x01654c00;
static const unsigned kUIStrings       = 0x0147f238;

// small callthrough helpers
static inline void  GameTime_Dec(unsigned gate) { ((TC_VI)0x00b32250)(FUN_00b3d380(), (int)gate); }
static inline void  GameTime_Inc(unsigned gate) { ((TC_VI)0x00b32220)(FUN_00b3d380(), (int)gate); }

// ===========================================================================
// @ 0x00e033d0
void CivPauseUI::Pause()
{
    if (this->mStop1.mTicks != 0) {
        long long t = ((TC_LL)0x0093a3a0)(&this->mStop1);
        if (1500.0f < (float)t * this->mStop1.mfScale) {
            if (g_bPaused != 0)
                GameTime_Dec(0x4bf38a7);
            g_bPaused = 0;
            ((TC_V)0x0093a2e0)(&this->mStop1);

            void* cur = FUN_0067cab0(this->miHandler);
            ((TC_I)0x00801b60)(cur);

            void* gd = (void*)((TC_I)0x00b294c0)(FUN_00b3d340(0, 1));
            if (gd != 0) {
                void* home = FUN_01021370();
                const wchar_t* name = (const wchar_t*)((TC_P)0x00ecdba0)(home);
                wstring tmp;
                tmp.RangeInit(name);
                void* a = FUN_0067de40();
                void* b = ((TFnP)VT(a, 0x20))(a);
                ((TFnVII)VT(b, 0x34))(b, 0, 0);
                FUN_00809db0((void*)0x015a4878, (void*)0x015a4818);
                if ((((unsigned)((char*)tmp.mpCap - (char*)tmp.mpBegin)) & 0xfffffffe) > 2 &&
                    tmp.mpBegin != 0)
                    cof_delete(tmp.mpBegin);
            } else {
                this->miState = 5;
                FUN_00809db0((void*)0x015a4878, (void*)0x015a4824);
            }
        }
    }

    if (this->mStop2.mTicks != 0) {
        long long t = ((TC_LL)0x0093a3a0)(&this->mStop2);
        if (1500.0f < (float)t * this->mStop2.mfScale) {
            if (g_bPaused != 0)
                GameTime_Dec(0x4bf38a7);
            g_bPaused = 0;
            ((TC_V)0x0093a2e0)(&this->mStop2);

            void* a = FUN_0067dd20();
            ((TFnV)VT(a, 0x40))(a);

            if (this->miState == 9) {
                void* cheat = FUN_0067de20();
                ((TFnVI)VT(cheat, 0x20))(cheat, (int)0x014137f8);   // "quit"
            }
            this->miState = 0;
        }
    }

    if (this->mStop1.mTicks != 0 || this->mStop2.mTicks != 0) {
        void* ms = FUN_0067dcc0();
        ((TFnVIIII)VT(ms, 0x18))(ms, 0x685d440, 0, 0, 0);
    }
}

// ===========================================================================
// @ 0x00e03590
void BanContent::SetText(int id, const wchar_t* text, const void* extras)
{
    this->mTokens.miId = id;
    this->mTokens.mbActive = 1;

    const wchar_t* e = text;
    while (*e != 0)
        ++e;
    unsigned n = (unsigned)(e - text);
    this->mTokens.mText.Assign(text, text + n);

    if (extras != 0) {
        void* a = FUN_0067de40();
        void* b = ((TFnP)VT(a, 0x20))(a);
        ((TFnVII)VT(b, 0x2c))(b, (int)extras, (int)&this->mTokens.mExtra);
        FUN_00809db0(this, (void*)0x015a4860);
    } else {
        FUN_00809db0(this, (void*)0x015a4854);
    }
}

// ===========================================================================
// @ 0x00e03620
bool cSPUIGlobalUI::Init(int param)
{
    FUN_00dd12f0();
    FUN_00e09600();

    void* ms = FUN_0067dcc0();
    this->mpHandler      = ms;
    this->mpHandlerThis  = this;
    this->miHandlerTag   = (int)0x0147f238;
    this->miHandlerCount = 0xb;
    this->miHandlerExtra = 0;
    if (ms != 0 && this != 0) {
        for (unsigned i = 0; i < 0x2c; i += 4) {
            int tag = *(int*)(kUIStrings + i);
            ((TFnVII)VT(ms, 0x24))(ms, (int)this, tag);
        }
    }

    void* dlg = cof_new(0x18, "Simulator", 0, 0, 0, 0);
    if (dlg != 0)
        dlg = (void*)((TC_P)0x00810000)(dlg);

    void* old = this->mpLayout;
    if (dlg != old) {
        if (dlg != 0)
            ((TFnV)VT(dlg, 4))(dlg);
        this->mpLayout = (cSPUILayout*)dlg;
        if (old != 0)
            ((TFnV)VT(old, 8))(old);
    }

    bool ok = false;
    if (this->mpLayout != 0) {
        if (((TFnPII)VT(this->mpLayout, 0x00))(this->mpLayout, 0, 0)) {
            ((TC_V)0x00e02af0)(this);
            ok = true;
        }
    }

    if (FUN_0067de40() != 0) {
        void* a = FUN_0067de40();
        void* b = ((TFnP)VT(a, 0x20))(a);
        if (b != 0) {
            void* p = (this != 0) ? (void*)((char*)this + 0x10) : 0;
            void* c = FUN_0067de40();
            void* d = ((TFnP)VT(c, 0x20))(c);
            ((TFnVP)VT(d, 0x1c))(d, p);
        }
    }
    return ok;
}

// ===========================================================================
// @ 0x00e03740
bool cSPUIGlobalUI::Shutdown()
{
    if (this->mpLayout != 0) {
        ((TC_VI)0x00811ad0)(this->mpLayout, 1);
        cSPUILayout* p = this->mpLayout;
        if (p != 0) {
            this->mpLayout = 0;
            ((TFnV)VT(p, 8))(p);
        }
    }
    if (this->mpOptions != 0) {
        FUN_00e02e10(this->mpOptions);
        cSPUIGlobalOptions* p = this->mpOptions;
        if (p != 0) {
            this->mpOptions = 0;
            ((TFnV)VT(p, 4))(p);
        }
    }
    FUN_00dd14b0();
    FUN_00e097c0();

    if (this->mpHandler != 0) {
        void* h = this->mpHandler;
        this->mpHandler = 0;
        ((TC_VIIII)0x00571db0)(h, (int)this->mpHandlerThis, this->miHandlerTag,
                               this->miHandlerCount, this->miHandlerExtra);
    }

    FUN_0067cac0();
    ((TC_V)0x0067ca40)(FUN_0067cac0());

    void* a = FUN_0067de40();
    void* b = ((TFnP)VT(a, 0x20))(a);
    ((TFnVI)VT(b, 0x20))(b, (int)g_pTranslator);
    g_pTranslator = 0;

    if (FUN_0067de40() != 0) {
        void* c = FUN_0067de40();
        void* d = ((TFnP)VT(c, 0x20))(c);
        if (d != 0) {
            void* p = (this != 0) ? (void*)((char*)this + 0x10) : 0;
            void* e = FUN_0067de40();
            void* f = ((TFnP)VT(e, 0x20))(e);
            ((TFnVI)VT(f, 0x20))(f, (int)p);
        }
    }
    return true;
}

// ===========================================================================
// @ 0x00e03830
BanEntry* BanEntry::CopyFrom(const BanEntry& src)
{
    this->miId = src.miId;
    this->mName.mpBegin = 0;
    this->mName.mpEnd   = 0;
    this->mName.mpCap   = 0;
    unsigned n = (unsigned)(src.mName.mpEnd - src.mName.mpBegin);
    this->mName.AllocateSelf((int)n + 1);
    wchar_t* dst = this->mName.mpBegin;
    memcpy_(dst, src.mName.mpBegin, n * 2);
    this->mName.mpEnd = dst + n;
    *this->mName.mpEnd = 0;

    this->mText.mpBegin = 0;
    this->mText.mpEnd   = 0;
    this->mText.mpCap   = 0;
    n = (unsigned)(src.mText.mpEnd - src.mText.mpBegin);
    this->mText.AllocateSelf((int)n + 1);
    dst = this->mText.mpBegin;
    memcpy_(dst, src.mText.mpBegin, n * 2);
    this->mText.mpEnd = dst + n;
    *this->mText.mpEnd = 0;
    return this;
}

// ===========================================================================
// @ 0x00e03930
void BanContent::Dtor()
{
    this->mpVtbl = (void*)0x0147f27c;
    this->mTokens.mpVtbl = (void*)0x0147f264;

    FUN_00e02c60(this->mTokens.mList.mpBegin, this->mTokens.mList.mpEnd);
    BanEntry* p = this->mTokens.mList.mpBegin;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        cof_delete(p);

    if ((((unsigned)((char*)this->mTokens.mExtra.mpCap - (char*)this->mTokens.mExtra.mpBegin)) & 0xfffffffe) > 2 &&
        this->mTokens.mExtra.mpBegin != 0)
        cof_delete(this->mTokens.mExtra.mpBegin);

    if ((((unsigned)((char*)this->mTokens.mText.mpCap - (char*)this->mTokens.mText.mpBegin)) & 0xfffffffe) > 2 &&
        this->mTokens.mText.mpBegin != 0)
        cof_delete(this->mTokens.mText.mpBegin);

    ((TC_V)0x005725a0)(&this->mTokens);
}

// ===========================================================================
// @ 0x00e039d0
bool cSPUIGlobalOptions::HandleMessage(int arg, UIMessage* msg)
{
    (void)arg;
    if (msg->miType == 1) {
        if (msg->miFlag == 0) {
            if (msg->miSub == 0x1b) {
                if (g_bPaused == 0) {
                    if (FUN_00e09540() == 0 && FUN_00dd1230() == 0) {
                        this->Reactivate();
                        return true;
                    }
                    FUN_00e009f0();
                }
                return true;
            }
            if (msg->miSub == 0x48 || msg->miSub == 0xbf) {
                FUN_00e02200();
                return true;
            }
        }
        if (msg->miFlag == 1 && msg->miSub == 0xbf) {
            FUN_00e02200();
            return true;
        }
    } else if (msg->miType == 0x287259f6) {
        if (msg->miId == 0x10ed852 || msg->miId == 0x595e0a8) {
            this->Reactivate();
            if (FUN_00b5b800() != (void*)kGameModeBase)
                return true;
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00e03a90
bool CivPauseUI::OnMessage(int id, int arg)
{
    (void)arg;
    if (id == 0x685d440)
        ((CivPauseUI*)((char*)this - 4))->Pause();
    return false;
}

// ===========================================================================
// @ 0x00e03ab0
void* cSPUIGlobalUI::Construct()
{
    this->mpVtbl = (void*)0x0147f288;
    this->mpOptions = 0;
    this->mpLayout = 0;

    ((TC_V)0x006b5870)(&this->mBan.mTokens);      // cStringTokenTranslator ctor
    this->mBan.mTokens.mbActive = 0;
    this->mBan.mTokens.mbHold = 0;

    this->mBan.mpVtbl = (void*)0x0147f27c;
    this->mBan.mTokens.mpVtbl = (void*)0x0147f264;

    this->mBan.mTokens.mText.mpBegin = (wchar_t*)0x01667bac;
    this->mBan.mTokens.mText.mpEnd = (wchar_t*)0x01667bac;
    this->mBan.mTokens.mText.mpCap = (wchar_t*)0x01667bae;
    this->mBan.mTokens.mExtra.mpBegin = (wchar_t*)0x01667bac;
    this->mBan.mTokens.mExtra.mpEnd = (wchar_t*)0x01667bac;
    this->mBan.mTokens.mExtra.mpCap = (wchar_t*)0x01667bae;

    this->mBan.mTokens.mList.mpBegin = 0;
    this->mBan.mTokens.mList.mpEnd = 0;
    this->mBan.mTokens.mList.mpCap = 0;

    this->mpHandler = 0;
    this->mpHandlerThis = 0;
    this->miHandlerTag = 0;
    this->miHandlerCount = 0;
    this->miHandlerExtra = 0;
    return this;
}

// ===========================================================================
// @ 0x00e03b20
void cSPUIGlobalUI::Destroy()
{
    this->mpVtbl = (void*)0x0147f288;

    void* h = this->mpHandler;
    if (h != 0) {
        this->mpHandler = 0;
        FUN_00571db0(h, this->mpHandlerThis, this->miHandlerTag,
                     this->miHandlerCount, this->miHandlerExtra);
    }

    this->mBan.Dtor();

    if (this->mpLayout != 0)
        ((TFnV)VT(this->mpLayout, 8))(this->mpLayout);
    if (this->mpOptions != 0)
        ((TFnV)VT(this->mpOptions, 4))(this->mpOptions);

    this->mpVtbl = (void*)0x013eb394;   // PaintSystem vtable
}

// ===========================================================================
// @ 0x00e03b80
bool BanTranslator::Format(const wchar_t* key, wchar_t* out)
{
    unsigned h = FNV1_String16(key, 0x811c9dc5, 1);
    switch (h) {
    case 0x2f009dd8:
        WStr_Format(out, 0x013f01bc, this->miId);
        return true;
    case 0x989407d5:
        WStr_Format(out, 0x013f5b90, this->mExtra.mpBegin);
        return true;
    case 0xd5c6de59:
        WStr_Format(out, 0x013f5b90, this->mText.mpBegin);
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00e03c30
BanEntry* BanVec::EraseLast(BanEntry* pos)
{
    if ((char*)(pos + 1) < (char*)this->mpEnd)
        FUN_00e02d30(pos + 1, this->mpEnd, pos);

    this->mpEnd = (BanEntry*)((char*)this->mpEnd - 0x24);
    BanEntry* last = this->mpEnd;

    if ((int)((unsigned)((char*)last->mText.mpCap - (char*)last->mText.mpBegin) & 0xfffffffe) > 2 &&
        last->mText.mpBegin != 0)
        cof_delete(last->mText.mpBegin);
    if ((int)((unsigned)((char*)last->mName.mpCap - (char*)last->mName.mpBegin) & 0xfffffffe) > 2 &&
        last->mName.mpBegin != 0)
        cof_delete(last->mName.mpBegin);

    return pos;
}

// ===========================================================================
// @ 0x00e03ca0
BanEntry* BanVec::Insert(BanEntry* pos, const BanEntry& val)
{
    const BanEntry* src = &val;
    if (this->mpEnd != this->mpCap) {
        if (pos <= src && src < this->mpEnd)
            src = (const BanEntry*)((char*)src + 0x24);

        BanEntry* end = this->mpEnd;
        if (end != 0)
            end->CopyFrom(*(BanEntry*)((char*)end - 0x24));
        FUN_00e02da0(pos, (char*)end - 0x24, end);

        pos->miId = src->miId;
        if (&src->mName != &pos->mName)
            pos->mName.Assign(src->mName.mpBegin, src->mName.mpEnd);
        if (&src->mText != &pos->mText)
            pos->mText.Assign(src->mText.mpBegin, src->mText.mpEnd);

        this->mpEnd = (BanEntry*)((char*)end + 0x24);
        return pos;
    }

    unsigned count = (unsigned)(this->mpEnd - this->mpBegin);
    unsigned cap = count;
    BanEntry* buf = 0;
    if (cap == 0) {
        cap = 1;
    } else {
        cap *= 2;
    }
    if (cap != 0)
        buf = (BanEntry*)cof_new(cap * 0x24, "Simulator", 0, 0,
                                 (const char*)0x013ebb38, 0xd1);

    BanEntry* begin = this->mpBegin;
    BanEntry* mid = (BanEntry*)FUN_00e038e0(begin, pos, buf);
    FUN_00e02cc0(begin, pos, buf);
    if (mid != 0)
        mid->CopyFrom(val);

    BanEntry* oldEnd = this->mpEnd;
    BanEntry* newEnd = (BanEntry*)FUN_00e038e0(pos, oldEnd, mid + 1);
    FUN_00e02cc0(pos, oldEnd, mid + 1);

    if (this->mpBegin != 0 && *(int*)((char*)this->mpBegin - 4) != 0)
        cof_delete(this->mpBegin);

    this->mpEnd = newEnd;
    this->mpBegin = buf;
    this->mpCap = (BanEntry*)((char*)buf + cap * 0x24);
    return pos;
}

// ===========================================================================
// @ 0x00e03e10
void BanContent::OnDeactivate(int a, int b)
{
    (void)a;
    (void)b;
    this->mTokens.mbActive = 0;
    if (this->mTokens.mbHold != 0) {
        BanEntry* p = this->mTokens.mList.mpBegin;
        if (p != this->mTokens.mList.mpEnd) {
            this->SetText(p->miId, p->mName.mpBegin, p->mText.mpBegin);
            this->mTokens.mList.EraseLast(this->mTokens.mList.mpBegin);
        }
    }
}

// ===========================================================================
// @ 0x00e03e50
void BanContent::AddRow(int id, const wchar_t* name, const wchar_t* text)
{
    if (this->mTokens.mbActive == 0 && this->mTokens.mbHold != 0) {
        this->SetText(id, name, text);
        return;
    }

    BanEntry tmp;
    tmp.miId = id;
    tmp.mName.mpBegin = 0; tmp.mName.mpEnd = 0; tmp.mName.mpCap = 0;
    tmp.mName.RangeInit(name);
    tmp.mText.mpBegin = 0; tmp.mText.mpEnd = 0; tmp.mText.mpCap = 0;
    tmp.mText.RangeInit(text);

    BanEntry* end = this->mTokens.mList.mpEnd;
    BanVec* list = &this->mTokens.mList;
    if (end < list->mpCap) {
        list->mpEnd = end + 1;
        if (end != 0)
            end->CopyFrom(tmp);
    } else {
        list->Insert(end, tmp);
    }

    if ((int)((unsigned)((char*)tmp.mText.mpCap - (char*)tmp.mText.mpBegin) & 0xfffffffe) > 2 &&
        tmp.mText.mpBegin != 0)
        cof_delete(tmp.mText.mpBegin);
    if ((int)((unsigned)((char*)tmp.mName.mpCap - (char*)tmp.mName.mpBegin) & 0xfffffffe) > 2 &&
        tmp.mName.mpBegin != 0)
        cof_delete(tmp.mName.mpBegin);
}

// ===========================================================================
// @ 0x00e03f40
void BanContent::OnToggle(char on)
{
    this->mTokens.mbHold = on;
    if (on != 0 && this->mTokens.mbActive == 0) {
        BanEntry* p = this->mTokens.mList.mpBegin;
        if (p != this->mTokens.mList.mpEnd) {
            this->SetText(p->miId, p->mName.mpBegin, p->mText.mpBegin);
            this->mTokens.mList.EraseLast(this->mTokens.mList.mpBegin);
        }
    }
}

// ===========================================================================
// @ 0x00e03f80
bool cSPUIGlobalUI::HandleMessage(unsigned msg, int arg)
{
    if (msg <= 0x05d1536c) {
        if (msg == 0x05d1536c) {
            if (this->mpOptions != 0 && this->mpOptions->miType != 0) {
                void* w = FUN_008105b0(this->mpOptions->miType, 0x44ea79e, 1);
                if (w != 0) {
                    void* b = ((TFnPI)VT(w, 0x0c))(w, (int)0x8ed27e7a);
                    if (b != 0)
                        ((TFnVII)VT(b, 0x28))(b, 4, 0);
                }
                if (FUN_00e00ac0() != 0) {
                    this->mpOptions->Enable(1);
                    return true;
                }
            }
        } else if (msg < 0x05120263) {
            if (msg == 0x05120262) {
                if (FUN_00b5b800() != (void*)0x01654c10) {
                    FUN_00e01620(1, arg);
                    return true;
                }
                if (FUN_00b5b820() == (void*)0x01654c05) {
                    FUN_00e01620(1, arg);
                    return true;
                }
            } else if (msg == 0x03867294) {
                if (this->mpLayout != 0) {
                    void* w = ((TC_PII)0x008105b0)(this->mpLayout, 0xd305ca84, 1);
                    void* b = (void*)((TC_P)0x005ca960)(w);
                    if (b != 0) {
                        char str[8];
                        ((TC_V)0x006b5060)(str);
                        if ((*(unsigned char*)((char*)FUN_00b3d380() + 0x48) & 1) == 0) {
                            ((TFnVII)VT(b, 0x28))(b, 4, 0);
                            ((TC_VII)0x006b54b0)(str, 0xf81c278b, 0);
                        } else {
                            ((TFnVII)VT(b, 0x28))(b, 4, 1);
                            ((TC_VII)0x006b54b0)(str, 0x0655200d, 0);
                        }
                        ((TC_VII)0x006b54b0)(str, 0xc0152a6d, 0);
                        const wchar_t* txt = (const wchar_t*)((TC_P)0x006b55c0)(str);
                        void* w2 = ((TFnPI)VT(b, 0x10))(b, (int)txt);
                        ((TC_VP)0x00806de0)(this, w2);
                        ((TC_V)0x006b5240)(str);
                        return true;
                    }
                }
            } else if (msg == 0x04471c60) {
                GameTime_Dec(0x4bf38a4);
                return true;
            }
        } else if (msg == 0x0539a4ce) {
            if (arg == 0) {
                GameTime_Inc(0x4bf38a6);
                return true;
            }
        } else if (msg == 0x0539a4cf) {
            if (arg == 0) {
                GameTime_Dec(0x4bf38a6);
                return true;
            }
        }
    } else if (msg < 0x07bd0aab) {
        if (msg == 0x07bd0aaa) {
            if (FUN_00685520(2) != 0) {
                this->mBan.AddRow(arg, (const wchar_t*)*(int*)(arg + 4),
                                  (const wchar_t*)*(int*)(arg + 8));
                return true;
            }
        } else if (msg == 0x06202731) {
            if (this->mpOptions != 0 && this->mpOptions->miType != 0) {
                void* w = FUN_008105b0(this->mpOptions->miType, 0x62025f9, 1);
                void* b = (void*)((TC_P)0x005ca960)(w);
                if (b != 0)
                    ((TFnVII)VT(b, 0x28))(b, 4, 0);
                if (FUN_00e00ac0() != 0) {
                    this->mpOptions->Enable(1);
                    return true;
                }
            }
        } else if (msg == 0x064eb18e) {
            if (this->mpOptions != 0) {
                this->mpOptions->Reactivate();
                return true;
            }
        }
    } else if (msg == 0x080d7451) {
        this->mBan.OnToggle(*(int*)arg != 0);
    }
    return true;
}

// ===========================================================================
// @ 0x00e04270
void* cSPUIGlobalUI::AsInterface(unsigned id)
{
    void* pRet = 0;
    if (id != 0xee3f516e) {
        if (id == 0x0469a812)
            return (void*)((char*)this - 0x70);
        if (id != 0x2f009dd0)
            return pRet;
    }
    char* p = (char*)this - 0x70;
    return (void*)(p ? this : 0);
}

// ===========================================================================
// @ 0x00e042b0
bool cSPUIGlobalUI::AnyCivSlotUsed()
{
    for (int i = 0; i < 4; ++i) {
        if (*(char*)((char*)this + 0x91 + i * 0xc) != 0)
            return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00e042d0
void cSPUIGlobalUI::ShowOptionWindows(char on)
{
    void* w = this->FindWindowByID(0x6453746);
    ((TFnVII)VT(w, 0x7c))(w, 1, (int)on);

    w = this->FindWindowByID(0x652a628);
    ((TFnVII)VT(w, 0x7c))(w, 1, (int)on);

    w = this->FindWindowByID(0x44827b8);
    ((TFnVII)VT(w, 0x7c))(w, 1, (on == 0) ? 1 : 0);
}

// ===========================================================================
// @ 0x00e04330
int __cdecl FUN_00e04330(int type)
{
    switch (type) {
    case 3:  return 0x64bd00a;
    case 10: return 0x64bd00b;
    case 9:  return 0x64bd00c;
    case 11: return 0x64bd00d;
    case 6:  return 0x64bd00e;
    case 0:  return 0x64bd00f;
    case 4:  return 0x64bd010;
    case 7:  return 0x64bd011;
    case 1:  return 0x64bd012;
    case 5:  return 0x64bd013;
    case 8:  return 0x64bd014;
    case 2:  return 0x64bd015;
    default: return 0x64bd016;
    }
}
