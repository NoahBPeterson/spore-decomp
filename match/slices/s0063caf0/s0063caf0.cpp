// slice s0063caf0: cSPPlayModeSubModeMovie YouTube registration + upload helpers.
#include "../s00636320/s00636320.h"

struct cEditorYouTubeAuthenticationMessage {   // 0x34
    eastl::string mUsername;
    eastl::string mPassword;
    eastl::string mSource;
    bool mCheckRegistration;
    ~cEditorYouTubeAuthenticationMessage();
};

struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
    virtual void s6(); virtual void s7(); virtual void s8();
    virtual void AddHandler(void* handler, uint32_t id);            // +0x24
};
IMessageServer* GetMessageServer();   // 0x0067DCC0

struct cProp {
    char pad12[0x12]; short mType;
    char* GetBool();        // 0x0041E920
    uint32_t* GetUInt();    // 0x0041EA00
    float* GetFloat();      // 0x0041EA70
};
struct IPropList {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8();
    virtual bool GetProp(uint32_t id, void** out);   // +0x24
    bool GetDescription(uint32_t id);                // 0x006A25A0 (non-virtual, ret 4)
};
extern IPropList* gAppProperties;   // 0x015FD918

struct IMovieSystem {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual void m10(); virtual void m11();
    virtual bool IsRecording();                                      // +0x30
};
IMovieSystem* MovieSystem();   // 0x0067CB10

struct IConfigMgr {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9();
    virtual void c10(); virtual void c11();
    virtual int GetValue(uint32_t id);                               // +0x30
};
IConfigMgr* GetConfigManager();   // 0x0067DD30

struct IAuthManager {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8();
    virtual bool v24();                                              // +0x24
    virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
    virtual void a15(); virtual void a16();
    virtual void v44();                                              // +0x44
    virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21();
    virtual bool v58();                                              // +0x58
};
IAuthManager* GetAuthManager();   // 0x00607A60

struct IApp15e4ef0 {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9();
    virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
    virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual void a20(); virtual void a21();
    virtual void v58();                                              // +0x58
};
extern IApp15e4ef0* gApp15e4ef0;   // 0x015E4EF0

struct cMovieUI : cSPPlayModeUI {
    void SetYTPrompt(bool b);                  // 0x00635310
    void ShowMovieSavedDialogCustom();         // 0x00638430
    bool FUN_00634b00();                       // 0x00634B00
    void ShowSendEmail(void* p);               // 0x00637860 (ret 4)
};

struct cTextTable {   // *0x015F7CF4
    char pad0[0x18];
    const wchar_t* m18;
    const wchar_t* m1c;
    char pad20[0x30 - 0x20];
    const wchar_t* m30;
    char pad34[0x58 - 0x34];
    const wchar_t* m58;
};
extern cTextTable* gTextTable;   // 0x015F7CF4
extern const wchar_t gDfltText[];   // 0x013EC468

namespace SP {
class cString {
public:
    cString();                                                       // 0x006B5060
    ~cString();                                                      // 0x006B5240
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* dflt);   // 0x006B54B0
    const wchar_t* GetText();                                        // 0x006B55C0
    char pad[0x14];
};
}
extern const wchar_t gDflt13fe144[];   // 0x013FE144
extern const wchar_t gFmt13fe12c[];    // 0x013FE12C
void __cdecl WStr_Format(void* str, const wchar_t* fmt, ...);        // 0x0041E050

struct SubModeParams { char pad[0x1c]; cMovieUI* mUI; };
struct cMsg;
extern const uint32_t gMsgTable[12];   // 0x013FF09C

struct cSPPlayModeSubModeMovie;
struct cSubModeBase {
    char pad[0x18];
    void Init(SubModeParams* p);   // 0x0063B270 (non-virtual call, ret 4)
};

struct cSPPlayModeSubModeMovie : cSubModeBase {
    IMovieSystem* mMovieSystem;     // +0x18
    uint32_t mWidth;                // +0x1C
    uint32_t mHeight;               // +0x20
    float mFPS;                     // +0x24
    float mTime;                    // +0x28
    float mQuality;                 // +0x2C
    bool mAudio;                    // +0x30
    char pad31[3];
    cMovieUI* mUI;                  // +0x34
    char mCurrFilename[260];        // +0x38
    char mCurrPathname[260];        // +0x13C
    eastl::string16 mTableA[260];   // +0x240
    eastl::string16 mTableB[260];   // +0x1280
    bool mb22c0;                    // +0x22C0
    bool mb22c1;                    // +0x22C1
    char pad22c2[0x22c8 - 0x22c2];
    uint32_t mField22c8;            // +0x22C8
    uint32_t mField22cc;            // +0x22CC
    IMessageServer* mAutoServer;    // +0x22D0
    void* mAutoHandler;             // +0x22D4
    const uint32_t* mAutoTable;     // +0x22D8
    uint32_t mAutoCount;            // +0x22DC
    uint32_t mAutoE;                // +0x22E0
    int mDialogInProgress;          // +0x22E4
    char pad22e8[0x22fc - 0x22e8];
    uint32_t mField22fc;            // +0x22FC
    char pad2300[0x231c - 0x2300];
    bool mb231c;                    // +0x231C
    bool mb231d;                    // +0x231D
    bool mb231e;                    // +0x231E
    bool mb231f;                    // +0x231F
    bool mb2320;                    // +0x2320
    bool mb2321;                    // +0x2321
    char pad2322[0x234c - 0x2322];
    uint32_t mField234c;            // +0x234C
    char pad2350[0x235d - 0x2350];
    bool mb235d;
    bool mb235e;

    void CheckYouTubeRegistration();   // 0x0063CED0
    void FUN_0063cf90();               // 0x0063CF90
    void FUN_0063caf0(SubModeParams* p);
    __declspec(noinline) void FUN_0063cd30();
    void ConstructYouTubeVideoUploadXMLRequest(eastl::string* out);   // 0x0063D050
    static bool ConstructVideoURL(eastl::string16* in, eastl::string16* out);   // 0x0063D170
    void FUN_0063d2f0();
    void FUN_0063b760();
    void ToggleRecordingIndicator(char b);          // 0x0063D910
    void LoadYouTubeCredentials();     // 0x0063C7F0
    void OnMovieRecorded();            // 0x0063C8F0
    void ShowMovieSavedDialog();       // 0x0063C640
    void ShowYouTubeLoginDialog();     // 0x0063BEC0
    void SetStateB();                  // 0x0063B910
    static bool GetYTPrompt();         // 0x0063B890
};


struct cStrObj { char pad[0xc]; const char* mStr; };
struct cMsg { uint32_t f00, f04, f08, f0c, f10, f14, f18, f1c, f20; };
extern char gKey15247e0[12], gKey15247ec[12];
extern void* gCalloutWhere;                                          // 0x0152481C
void __cdecl CalloutMessageBox(void* where, const void* key);        // 0x00809DB0
void __cdecl OpenBrowser(const wchar_t* url, int flag);              // 0x00935FB0
void CreateConnectingDialog();                                       // 0x0063BC70
void __cdecl DestroyConnectingDialog(bool b);                        // 0x0063C060
struct CAch { void AutoTest(); };                                    // 0x00676E90
CAch* __stdcall AchievementsController(uint32_t a, int b);           // 0x00675250
struct cAppPropsX { char pad[0x3c]; struct { char pad[0x118]; int f118; }* p3c; };

// eastl::string16 layout with the out-of-line members the callers use.
struct WStr16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    WStr16() : mpBegin(eastl::gEmptyString16), mpEnd(eastl::gEmptyString16), mpCapacity(eastl::gEmptyString16 + 1) {}
    ~WStr16() { if ((mpCapacity - mpBegin) > 1 && mpBegin) operator delete(mpBegin); }
    WStr16 substr(uint32_t pos, uint32_t n) const;                 // 0x00453D20 (thiscall, hidden return, ret 12)
    void assign(const wchar_t* b, const wchar_t* e);               // 0x00423650 (thiscall, ret 8)
    WStr16& operator=(const WStr16& o) { if (&o != this) assign(o.mpBegin, o.mpEnd); return *this; }
};
const wchar_t* FindLastOf16(const wchar_t* first, const wchar_t* last, const wchar_t* sb, const wchar_t* se);   // 0x005728F0 (cdecl)
extern const wchar_t gUrlDelims[];   // 0x013FA030
static inline uint32_t StrLen16(const wchar_t* p) { while (*p) ++p; return 0; }
static inline uint32_t StrLenB16(const wchar_t* p) { const wchar_t* p1 = p + 1; const wchar_t* q = p; while (*q++) {} return (uint32_t)(q - p1); }
static inline const uint32_t& MinRef(const uint32_t& a, const uint32_t& b) { return (b > a) ? a : b; }


struct cMovieHandler {   // IHandler subobject at movie+0x14: offsets are movie offsets minus 0x14
    void* mVptr;
    char pad04[0x20 - 4];
    cMovieUI* mUI;                  // +0x20
    char pad24[0x22d0 - 0x24];
    int mState;                     // +0x22D0
    char pad22d4[0x22d8 - 0x22d4];
    eastl::string mAuthToken;       // +0x22D8
    eastl::string mUsername;        // +0x22E8
    WStr16 mURL;                    // +0x22F8
    bool mb2308, mb2309, mb230a, mb230b, mb230c, mb230d, mb230e, mb230f, mb2310;
    char pad2311[3];
    uint32_t mStatusCode;           // +0x2314
    eastl::string mStatusMsg;       // +0x2318
    char pad2328[0x2349 - 0x2328];
    bool mb2349, mb234a;

    cSPPlayModeSubModeMovie* Movie() { return (cSPPlayModeSubModeMovie*)((char*)this - 0x14); }
    bool HandleMessage(uint32_t id, cMsg* msg);   // 0x0063D2F0
};
void KillSetiEffects(uint32_t id, uint32_t state);   // 0x00435ED0 (cdecl)
extern char* gRecordingStopped;                       // 0x0152443C

struct IAudioSystem {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7();
    virtual uint32_t v8();                            // +0x20
};
IAudioSystem* GetSystemAT();                          // 0x00A206F0

// @ 0x0063CED0
void cSPPlayModeSubModeMovie::CheckYouTubeRegistration()
{
    cEditorYouTubeAuthenticationMessage msg;
    mb231e = true;
    mb231d = false;
    mb231c = false;
    msg.mUsername.sprintf("%s", (const char*)mField22fc);
    msg.mPassword.sprintf("%s", (const char*)mField234c);
    msg.mSource.sprintf("%s", "scc");
    msg.mCheckRegistration = true;
    GetMessageServer()->PostMessage(0x55be439, &msg, 0);
}

// @ 0x0063CF90
void cSPPlayModeSubModeMovie::FUN_0063cf90()
{
    cEditorYouTubeAuthenticationMessage msg;
    mb2321 = true;
    mb2320 = false;
    mb231f = false;
    msg.mUsername.sprintf("%s", (const char*)mField22fc);
    msg.mPassword.sprintf("%s", (const char*)mField234c);
    msg.mSource.sprintf("%s", "scc");
    msg.mCheckRegistration = false;
    GetMessageServer()->PostMessage(0x55be439, &msg, 0);
}

static __forceinline bool GetTyped(IPropList* pl, uint32_t id, short type, void** out)
{
    return pl->GetProp(id, out) && ((cProp*)*out)->mType == type;
}

// @ 0x0063CAF0
void cSPPlayModeSubModeMovie::FUN_0063caf0(SubModeParams* p)
{
    Init(p);
    mUI = p->mUI;
    mMovieSystem = MovieSystem();
    mb22c0 = false;
    mb22c1 = false;
    mCurrFilename[0] = 0;
    mCurrPathname[0] = 0;
    mb235d = false;
    mb235e = false;
    IPropList* pl = gAppProperties;
    if (pl) {
        void* pr;
        if (GetTyped(pl, 0x456f974, 0xd, &pr))
            mTime = *((cProp*)pr)->GetFloat();
        if (GetTyped(pl, 0x456f975, 10, &pr))
            mWidth = *((cProp*)pr)->GetUInt();
        if (GetTyped(pl, 0x456f976, 10, &pr))
            mHeight = *((cProp*)pr)->GetUInt();
        if (GetTyped(pl, 0x456f977, 0xd, &pr))
            mFPS = *((cProp*)pr)->GetFloat();
        if (GetTyped(pl, 0x456f978, 0xd, &pr))
            mQuality = *((cProp*)pr)->GetFloat();
        if (GetTyped(pl, 0x456f979, 1, &pr))
            mAudio = *((cProp*)pr)->GetBool();
    }
    mField22c8 = mWidth;
    mField22cc = mHeight;
    LoadYouTubeCredentials();
    mUI->SetYTUsername(*(eastl::string*)&mField22fc);
    mUI->SetYTPassword(*(eastl::string*)&mField234c);
    mUI->SetYTPrompt(GetConfigManager()->GetValue(0x5664a8b) != 0);
    IMessageServer* ms = GetMessageServer();
    void* h = (char*)this + 0x14;
    mAutoServer = ms;
    mAutoHandler = h;
    mAutoTable = gMsgTable;
    mAutoCount = 0xc;
    mAutoE = 0;
    if (ms && h) {
        for (uint32_t i = 0; i < 12; ++i)
            ms->AddHandler(h, gMsgTable[i]);
    }
    if (mMovieSystem->IsRecording())
        OnMovieRecorded();
}
// @ 0x0063CD30
__declspec(noinline) void cSPPlayModeSubModeMovie::FUN_0063cd30()
{
    eastl::string16 name = EA::ConvertToString16(mCurrFilename, -1);
    gTextTable->m18 = name.c_str();
    eastl::string16 path = EA::ConvertToString16(mCurrPathname, -1);
    if (gAppProperties->GetDescription(0x61b67b6)) {
        SP::cString s1, s2, s3;
        s1.Load(0x19f76d11, 0x5ca8d97, gDflt13fe144);
        s3.Load(0x19f76d11, 0x5ca8d98, gDflt13fe144);
        WStr_Format(&mTableB[0], L" %s%s", s1.GetText(), s3.GetText());
        gTextTable->m1c = mTableB[0].c_str();
        s2.Load(0x19f76d11, 0x61b68c1, gDflt13fe144);
        WStr_Format(&mTableA[0], gFmt13fe12c, s2.GetText());
        gTextTable->m58 = mTableA[0].c_str();
    } else {
        gTextTable->m1c = path.c_str();
        gTextTable->m58 = gDfltText;
    }
    mUI->ShowMovieSavedDialogCustom();
    mDialogInProgress = 1;
}
// @ 0x0063D050
void cSPPlayModeSubModeMovie::ConstructYouTubeVideoUploadXMLRequest(eastl::string* out)
{
    char bPrivate = 0;
    if (gAppProperties) {
        void* p;
        if (gAppProperties->GetProp(0x8608be4, &p) && ((cProp*)p)->mType == 1)
            bPrivate = *((cProp*)p)->GetBool();
    }

    out->clear();
    out->append_sprintf("%s", "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    out->append_sprintf("%s", "<entry xmlns=\"http://www.w3.org/2005/Atom\"\n");
    out->append_sprintf("%s", "\txmlns:media=\"http://search.yahoo.com/mrss/\"\n");
    out->append_sprintf("%s", "\txmlns:yt=\"http://gdata.youtube.com/schemas/2007\">\n");
    out->append_sprintf("%s", "\t<media:group>\n");
    out->append_sprintf("%s", "\t\t<media:title>Spore Creature Creator Video</media:title>\n");
    out->append_sprintf("%s", "\t\t<media:description>This video was created using the Spore Creature Creator.</media:description>\n");
    out->append_sprintf("%s", "\t\t<media:category scheme=\"http://gdata.youtube.com/schemas/2007/categories.cat\">Entertainment</media:category>\n");
    out->append_sprintf("%s", "\t\t<media:keywords>spore, creature</media:keywords>\n");
    if (bPrivate == 0)
        out->append_sprintf("%s", "\t<yt:private/>\n");
    out->append_sprintf("%s", "\t</media:group>\n");
    out->append_sprintf("%s", "</entry>\n");
}
// @ 0x0063D170
bool cSPPlayModeSubModeMovie::ConstructVideoURL(eastl::string16* in, eastl::string16* out)
{
    WStr16 str;
    bool ok = true;
    const wchar_t* e = gUrlDelims;
    while (*e) e += 1;
    const wchar_t* dEnd = gUrlDelims + (e - gUrlDelims);
    const wchar_t* b = in->mpBegin;
    uint32_t len = (uint32_t)(in->mpEnd - b);
    if (len) {
        uint32_t npos = (uint32_t)-1;
        uint32_t pos = len - 1;
        const wchar_t* r = FindLastOf16(b + MinRef(pos, npos) + 1, b, gUrlDelims, dEnd);
        if (r != b) {
            int idx = (int)((r - 1) - b);
            if (idx != -1) {
                str = ((WStr16*)in)->substr(idx + 1, StrLenB16(b) - idx);
                out->clear();
                WStr_Format(out, L"http://www.youtube.com/watch?v=%s", str);
                goto done;
            }
        }
    }
    ok = false;
done:
    return ok;
}

#define CLOSE_DIALOG do { mState = 0; BeginProfScope(1, 1)->End(); return true; } while (0)
// @ 0x0063D2F0
bool cMovieHandler::HandleMessage(uint32_t id, cMsg* msg)
{
    IAuthManager* auth = GetAuthManager();
    switch (id) {
    case 0x5b98f52:
        if (mState != 7 && mState != 8)
            return false;
        Movie()->FUN_0063cd30();
        BeginProfScope(0, 1)->End();
        return false;
    case 0x55e5212: {
        uint32_t f10 = msg->f10;
        uint32_t f8 = msg->f08;
        if (f10 != 0)
            mb2309 = true;
        else
            mb230c = true;
        if (f8 != 0) {
            if (f10 != 0) {
                mb2308 = true;
                return true;
            }
            mAuthToken.sprintf("%s", ((cStrObj*)msg->f18)->mStr);
            mUsername.sprintf("%s", ((cStrObj*)msg->f20)->mStr);
            mb230b = true;
            return true;
        }
        mb2308 = false;
        mb230b = false;
        mStatusCode = msg->f18;
        mStatusMsg.sprintf("%s", ((cStrObj*)msg->f20)->mStr);
        return true;
    }
    case 0x44db12e:
        if (msg == 0)
            return false;
        if (mState != 7 && mState != 8)
            return false;
        if (mb2349) {
            mb234a = true;
            return false;
        }
        if (cSPPlayModeSubModeMovie::GetYTPrompt()) {
            Movie()->ShowYouTubeLoginDialog();
            gApp15e4ef0->v58();
            return false;
        }
        CreateConnectingDialog();
        Movie()->CheckYouTubeRegistration();
        gApp15e4ef0->v58();
        return false;
    case 0x5493aeb: {
        uint32_t btn = msg->f08;
        if (btn == 0x1510d07)
            return false;
        switch (mState) {
        case 1:
            switch (btn) {
            case 0x5107b17:
                Movie()->ShowMovieSavedDialog();
                OpenBrowser(L"http://youtube.com/t/terms", 1);
                break;
            case 0x5107b19:
                mState = 0;
                return true;
            case 0x5107b1a:
                if (!auth->v58()) {
                    mState = 8;
                    CalloutMessageBox(&gCalloutWhere, gKey15247ec);
                } else if (auth->v24()) {
                    mState = 7;
                    CalloutMessageBox(&gCalloutWhere, gKey15247e0);
                } else {
                    if (cSPPlayModeSubModeMovie::GetYTPrompt()) {
                        Movie()->ShowYouTubeLoginDialog();
                        return true;
                    }
                    CreateConnectingDialog();
                    Movie()->CheckYouTubeRegistration();
                    return true;
                }
                BeginProfScope(0, 1)->End();
                return true;
            }
            return true;
        case 2:
            switch (btn) {
            case 0x5107b19:
                goto closeDialog;
            case 0x5107b1a:
                Movie()->ShowYouTubeLoginDialog();
                return true;
            default:
                return true;
            }
        case 3:
            mState = 0;
            return true;
        case 7:
        case 8:
            switch (btn) {
            case 0x5107b19:
                goto closeDialog;
            case 0x5107b1a:
                auth->v44();
                return true;
            default:
                return true;
            }
        case 5:
            switch (btn) {
            case 0x5107b19:
                goto closeDialog;
            case 0x5107b1a:
                mUI->ShowSendEmail(&mURL);
                return true;
            default:
                return true;
            }
        case 10:
        case 11:
            if (btn != 0xfffffff1)
                return true;
        case 4:
        case 6:
        closeDialog:
            CLOSE_DIALOG;
        case 12:
            switch (btn) {
            case 0x5107b19:
                Movie()->ShowYouTubeLoginDialog();
                break;
            case 0x5107b1a:
                Movie()->ShowYouTubeLoginDialog();
                OpenBrowser(L"http://www.youtube.com/signup", 1);
                break;
            }
            return true;
        case 13:
            switch (btn) {
            case 0x5107b19:
                Movie()->FUN_0063cd30();
                break;
            case 0x5107b1a:
                Movie()->FUN_0063cd30();
                OpenBrowser(L"http://youtube.com/t/terms", 1);
                break;
            }
            return true;
        default:
            return false;
        }
    }
    case 0x55e8be4: {
        if (msg->f08 != 0)
            mb230e = true;
        if (mb230e) {
            WStr16 tmp;
            WStr_Format(&tmp, L"%s", ((cStrObj*)msg->f10)->mStr);
            if (!cSPPlayModeSubModeMovie::ConstructVideoURL((eastl::string16*)&tmp, (eastl::string16*)&mURL))
                mURL = tmp;
            gTextTable->m30 = mURL.mpBegin;
        } else {
            mStatusCode = msg->f10;
            mStatusMsg.sprintf("%s", ((cStrObj*)msg->f18)->mStr);
        }
        if (((cAppPropsX*)gAppProperties)->p3c->f118 == 0)
            AchievementsController(0xb4c2a66b, 1)->AutoTest();
        mb2310 = true;
        return true;
    }
    case 0x5b96086:
        if (mUI->FUN_00634b00())
            return true;
        if (!auth->v58())
            return true;
        CLOSE_DIALOG;
    case 0x5dd52c7:
        mb2349 = false;
        if (mb234a) {
            mb234a = false;
            if (cSPPlayModeSubModeMovie::GetYTPrompt()) {
                Movie()->ShowYouTubeLoginDialog();
                gApp15e4ef0->v58();
                return false;
            }
            CreateConnectingDialog();
            Movie()->CheckYouTubeRegistration();
            gApp15e4ef0->v58();
            return false;
        }
        return false;
    case 0x5bd6378:
        mb2349 = true;
        return false;
    case 0x5d2c5c0: {
        DestroyConnectingDialog(false);
        Movie()->SetStateB();
        uint32_t m = 0x55e7aed;
        GetMessageServer()->PostMessage(0x5d313c7, &m, 0);
        return true;
    }
    case 0x62ff413:
        Movie()->OnMovieRecorded();
        return false;
    }
    return false;
}

// @ 0x0063D910
void cSPPlayModeSubModeMovie::ToggleRecordingIndicator(char b)
{
    if (b == 0) {
        IAudioSystem* s = GetSystemAT();
        KillSetiEffects(0xcb4ad069, s ? s->v8() : 0);
        FUN_0063cd30();
    }
    IWindow* w = mUI->FindPlayModeUIWindow(0x42cadb8);
    if (w)
        w->SetCaption(EA::ConvertToString16(gRecordingStopped, -1).c_str());
    mb22c0 = false;
    mUI->SetUIGroupVisible(0x3f434ac, false);
    mUI->SetUIGroupVisible(0x3fc1740, true);
    if (mb22c1)
        FUN_0063b760();
}
