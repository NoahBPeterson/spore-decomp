// Slice s00f05110: cSPPlayModeSubModeMovie YouTube upload UI (Spore Galactic Adventures).
// String feed builder, YouTube authentication message senders and the upload
// progress/panel layout code.

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

template<class T> inline T& at(void* p, int off) { return *(T*)((char*)p + off); }
template<class T> inline T& at(int p, int off) { return *(T*)((char*)(long)p + off); }

// ---------------------------------------------------------------- eastl string
// 0x10 bytes in this build: begin/end/capacity plus a trailing dword that the
// trivial default constructor never writes.
struct EaStr
{
    char* mpBegin;      // 0x00
    char* mpEnd;        // 0x04
    char* mpCap;        // 0x08
    char* mpSpare;      // 0x0c
    EaStr();
    int    sprintf(const char* fmt, ...);            // 0x472fe0
    EaStr& append_sprintf(const char* fmt, ...);     // 0x5f9450
};

extern "C" const char gEmptyString16[];              // 0x1667bac

inline EaStr::EaStr()
{
    mpBegin = (char*)gEmptyString16;
    mpEnd   = (char*)gEmptyString16;
    mpCap   = (char*)gEmptyString16 + 1;
}

// ------------------------------------------------- cEditorYouTubeAuthenticationMessage
// Three strings plus a "private" flag; the destructor lives in the binary.
struct YtAuthMsg
{
    EaStr mToken;       // 0x00
    EaStr mUser;        // 0x10
    EaStr mExtra;       // 0x20
    uchar mPrivate;     // 0x30
    ~YtAuthMsg();       // ??1cEditorYouTubeAuthenticationMessage@@QAE@XZ
};

extern "C" void* __cdecl MessageServer();            // 0x67dcc0

// ---------------------------------------------------------------- host object
struct Movie
{
    void SendPublicAuth();      // 00f05c40
    void LoginToYouTube();      // 00f05d00
    void CloseUpload();         // 00f05b00
    void RefreshPanel();        // 00f05790
    void LayoutYouTube();       // 00f05110
    void SaveUploadSettings();  // 00f055c0
};

// ------------------------------------------------------------------ 00f05c40
// Annonymous/public YouTube login: builds the authentication message and hands
// it to the message server with the "public" flag set.
// @ 0x00f05c40
void Movie::SendPublicAuth()
{
    YtAuthMsg msg;

    at<uchar>(this, 0xbe) = 1;
    at<uchar>(this, 0xbd) = 0;
    at<uchar>(this, 0xbc) = 0;
    msg.mToken.sprintf((const char*)0x13f5b98, at<int>(this, 0x8c));
    msg.mUser.sprintf((const char*)0x13f5b98, at<int>(this, 0x9c));
    msg.mExtra.sprintf((const char*)0x13f5b98, (const char*)0x13ff0d8);
    msg.mPrivate = 1;
    void* srv = MessageServer();
    ((void (__thiscall*)(void*, int, YtAuthMsg*, int))
     ((void**)*(void**)srv)[0x14 / 4])(srv, 0x55be439, &msg, 0);
}

// ------------------------------------------------------------------ 00f05d00
// @ 0x00f05d00
void Movie::LoginToYouTube()
{
    YtAuthMsg msg;

    at<uchar>(this, 0xc1) = 1;
    at<uchar>(this, 0xc0) = 0;
    at<uchar>(this, 0xbf) = 0;
    msg.mToken.sprintf((const char*)0x13f5b98, at<int>(this, 0x8c));
    msg.mUser.sprintf((const char*)0x13f5b98, at<int>(this, 0x9c));
    msg.mExtra.sprintf((const char*)0x13f5b98, (const char*)0x13ff0d8);
    msg.mPrivate = 0;
    void* srv = MessageServer();
    ((void (__thiscall*)(void*, int, YtAuthMsg*, int))
     ((void**)*(void**)srv)[0x14 / 4])(srv, 0x55be439, &msg, 0);
}

// ---------------------------------------------------------------- properties
extern "C" void* gAppProperties;                     // 0x15fd918
struct Prop { uchar* GetBool(); };                   // 0x41e920
struct PropList { uchar GetDescription(uint id); };   // 0x6a25a0

// ------------------------------------------------------------------ 00f05dc0
// Appends the YouTube "Atom entry" XML document describing the uploaded movie
// to the caller's string. The <yt:private/> element is only emitted when the
// "private upload" property is off.
// @ 0x00f05dc0
void __stdcall BuildYtFeed(EaStr* out)
{
    char priv = 0;

    if (gAppProperties != 0) {
        void* pl = gAppProperties;
        int prop;
        if (((uchar (__thiscall*)(void*, int, int*))
             ((void**)*(void**)pl)[0x24 / 4])(pl, 0x8608be4, &prop) &&
            at<ushort>(prop, 0x12) == 1)
            priv = *((Prop*)prop)->GetBool();
    }
    if (out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff2f0);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff2c4);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff294);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff260);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff250);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x148b964);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x148b900);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff140);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x148b8bc);
    if (!priv)
        out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff0fc);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff0e8);
    out->append_sprintf((const char*)0x13f5b98, (const char*)0x13ff0dc);
}

// ---------------------------------------------------------------- wide string
extern "C" void __cdecl operator_delete(void* p);    // 0xf47380

struct EaStr16
{
    char* mpBegin;      // 0x00
    char* mpEnd;        // 0x04
    char* mpCap;        // 0x08
    int   mSpare;       // 0x0c
    EaStr16();
    ~EaStr16();
    void Format(const char* fmt, ...);      // 0x41e050
};

inline EaStr16::EaStr16()
{
    mpBegin = (char*)gEmptyString16;
    mpEnd   = (char*)gEmptyString16;
    mpCap   = (char*)gEmptyString16 + 2;
}

inline EaStr16::~EaStr16()
{
    if (((int)(mpCap - mpBegin) & ~1) > 2 && mpBegin != 0)
        operator_delete(mpBegin);
}

extern "C" void* __cdecl Audio_GetSystemAT();                      // 0xa206f0
extern "C" void __cdecl ScenarioTutorials_CloseWindow();           // 0xefcae0
extern "C" void* __cdecl GetTriggerMgr();                          // 0xb3d4d0
extern "C" void __cdecl UpdateMouseFocus(int on);                  // 0x804f50
extern "C" void* __cdecl SP_GetSaveArea(int id);                   // 0x6b1f90

// ------------------------------------------------------------------ 00f05b00
// Leave the upload flow: silence the audio system, close the tutorial window,
// refresh the panel, hide both buttons and hand the finished movie to the
// share panel under its "<name>.avi" caption.
// @ 0x00f05b00
void Movie::CloseUpload()
{
    void* sys = Audio_GetSystemAT();
    int   vol = sys != 0
              ? ((int (__thiscall*)(void*))((void**)*(void**)sys)[0x20 / 4])(sys)
              : 0;

    sys = Audio_GetSystemAT();
    if (sys != 0) {
        ((void (__thiscall*)(void*, int))((void**)*(void**)sys)[0x38 / 4])(sys, 0x3475365);
        ((void (__thiscall*)(void*, int, int))((void**)*(void**)sys)[0x40 / 4])(sys, 0x3475381, 0xcb4ad069);
        ((void (__thiscall*)(void*, int, int))((void**)*(void**)sys)[0x40 / 4])(sys, 0x3475385, vol);
        ((void (__thiscall*)(void*))((void**)*(void**)sys)[0x58 / 4])(sys);
    }

    ScenarioTutorials_CloseWindow();
    void* trig = GetTriggerMgr();
    int   mode = at<int>(trig, 0x2c);
    if (mode != 1 && mode != 2)
        this->RefreshPanel();

    at<uchar>(this, 0x78) = 0;
    void* btn1 = at<void*>(this, 0x30);
    ((void (__thiscall*)(void*, int, int))((void**)*(void**)btn1)[0x7c / 4])(btn1, 1, 0);
    void* btn2 = at<void*>(this, 0x34);
    ((void (__thiscall*)(void*, int, int))((void**)*(void**)btn2)[0x7c / 4])(btn2, 1, 1);

    UpdateMouseFocus(1);
    void* area = SP_GetSaveArea(0x11ac197);
    int   panel = area != 0
                ? ((int (__thiscall*)(void*, int))
                   ((void**)*(void**)((char*)area + 4))[0xc / 4])((char*)area + 4, 0x226a1de)
                : 0;

    EaStr16 name;
    name.Format((const char*)0x13ff3dc, at<int>(this, 0x54));
    ((void (__thiscall*)(void*, char*, int, int))
     ((void**)*(void**)panel)[0x54 / 4])((void*)panel, name.mpBegin, 0, 2);
}

// ---------------------------------------------------------------- ui helpers
struct RectF
{
    float left, top, right, bottom;
    uchar Intersect(const RectF& a, const RectF& b);   // 0x634b60
};

struct cString
{
    char pad[0x10];
    cString(uint id, uint key, const void* text);      // 0x6b5770
    ~cString();                                        // 0x6b5240
    const void* GetText();                             // 0x6b55c0
};

struct UIHints { int SetFlag(char flag, int value); }; // 0x67c420
struct SpGameTime { void IncPauseGate(int tag); };     // 0xb32220
struct Layout
{
    void* FindWindowByID(uint id, char recurse);       // 0x8105b0
};

extern "C" void* __cdecl UIHints_Get();                // 0x67cac0
extern "C" void* __cdecl WindowManager();              // 0x67caa0
extern "C" void* __cdecl GameTimeManager();            // 0xb3d380
extern "C" void __cdecl SPUIHelpers_BeginModal(void*, int, int);      // 0x8099a0
extern "C" void __cdecl AutoSizeWindowForText(void* win, int a, int b); // 0x806e40
extern "C" void __cdecl WString_Assign(void* dst, const void* first, const void* last); // 0x423650

// ------------------------------------------------------------------ 00f05790
// Rebuild the share panel: fill in the movie title/description in the layout
// database, size the caption windows, run the sub-layout and pop the dialog
// modally the first time it is shown.
// @ 0x00f05790
void Movie::RefreshPanel()
{
    void* ui = *(void**)0x15f7cf4;
    at<int>(ui, 0x18) = at<int>(this, 0x54);
    if (!((PropList*)gAppProperties)->GetDescription(0x61b67b6)) {
        at<int>(*(void**)0x15f7cf4, 0x1c) = at<int>(this, 0x64);
        at<void*>(*(void**)0x15f7cf4, 0x58) = (void*)0x13ec468;
    } else {
        EaStr16 name, desc;
        cString cfg1(0x19f76d11, 0x5ca8d97, 0);
        cString cfg2(0x19f76d11, 0x5ca8d98, 0);
        name.Format((const char*)0x13ff0cc, cfg1.GetText(), cfg2.GetText());
        at<void*>(*(void**)0x15f7cf4, 0x1c) = name.mpBegin;
        cString cfg3(0x19f76d11, 0x61b68c1, 0);
        desc.Format((const char*)0x13fe12c, cfg3.GetText());
        at<void*>(*(void**)0x15f7cf4, 0x58) = desc.mpBegin;
    }

    void* hints = UIHints_Get();
    ((UIHints*)hints)->SetFlag(0, 1);

    cString caption(0x7518573e, 0x54c1e63, (const void*)0x13febb4);
    Layout* lay = (Layout*)at<void*>(this, 0x2c);
    void* win1 = lay->FindWindowByID(0x5b5f5c8, 1);
    ((void (__thiscall*)(void*, const void*))((void**)*(void**)win1)[0x80 / 4])(win1, caption.GetText());

    float h = 0.0f;
    void* win2 = lay->FindWindowByID(0x5b5ef51, 1);
    if (win2 != 0) {
        AutoSizeWindowForText(win2, 1, 0);
        void* win3 = lay->FindWindowByID(0x5b5ef52, 1);
        if (win3 != 0) {
            AutoSizeWindowForText(win3, 0, 0);
            RectF* r3 = ((RectF* (__thiscall*)(void*))((void**)*(void**)win3)[0x38 / 4])(win3);
            float w = r3->right - r3->left;
            RectF* r2 = ((RectF* (__thiscall*)(void*))((void**)*(void**)win2)[0x38 / 4])(win2);
            ((void (__thiscall*)(void*, float, float))
             ((void**)*(void**)win3)[0x70 / 4])(win3, r2->left - w, r3->top);
            void* win4 = lay->FindWindowByID(0x5b5ef53, 1);
            if (win4 != 0) {
                AutoSizeWindowForText(win4, 0, 0);
                RectF* r4 = ((RectF* (__thiscall*)(void*))((void**)*(void**)win4)[0x38 / 4])(win4);
                RectF* r3b = ((RectF* (__thiscall*)(void*))((void**)*(void**)win3)[0x38 / 4])(win3);
                RectF res;
                res.Intersect(*r4, *r3b);
                h = res.right - res.left;
            }
        }
    }

    this->LayoutYouTube();

    void* panel = lay->FindWindowByID(0x5b5ef50, 1);
    ((void (__thiscall*)(void*, int, int))((void**)*(void**)panel)[0x7c / 4])(panel, 1, 1);
    if (h > 0.0f) {
        RectF* rp = ((RectF* (__thiscall*)(void*))((void**)*(void**)panel)[0x38 / 4])(panel);
        ((void (__thiscall*)(void*, float, float))((void**)*(void**)panel)[0x74 / 4])(
            panel, (rp->right - rp->left) + h, rp->bottom - rp->top);
    }

    void* dialog = lay->FindWindowByID(0xffffffff, 1);
    void* wm = WindowManager();
    if (!((uchar (__thiscall*)(void*, void*))((void**)*(void**)wm)[0x80 / 4])(wm, dialog)) {
        SPUIHelpers_BeginModal(dialog, 0, 0);
        void* gt = GameTimeManager();
        ((SpGameTime*)gt)->IncPauseGate(0x4bf38a4);
    }
    at<int>(this, 0x28) = 1;
}

// ------------------------------------------------------------ property / variant
extern "C" void* __cdecl PropertyManager();                       // 0x67de30
extern "C" void* __cdecl EAAllocate(int size, const char* name, int a, int b, int c, int d); // 0xf473a0
extern "C" void __cdecl Encrypt(EaStr* dst, const void* src);     // 0x60bcf0
extern "C" uchar __cdecl SP_SaveNamedResource(void* key, const void* name, void* area); // 0x6b4010
extern "C" void* g_ytLoginKey;                                     // 0x15ad36c

struct Variant
{
    int mFlags;             // type flags (bit 2 = destructible)
    int mPad[0x0b];
    void Construct(int type, int sub, const void* data, int size, int count);  // 0x93dd80
    void Destruct(bool free);                                                  // 0x93db80
};

struct CPropList { CPropList* init(); };      // 0x6a1c40

// ------------------------------------------------------------------ 00f055c0
// Store the uploader credentials/description for the YouTube share panel in the
// persistent property list and flush it to the save area.
// @ 0x00f055c0
void Movie::SaveUploadSettings()
{
    void* pm = PropertyManager();
    void* pl = 0;
    ((void (__thiscall*)(void*, int, int, void**))
     ((void**)*(void**)pm)[0x2c / 4])(pm, 0x3a39cb0d, 0x11ac192, &pl);

    if (pl == 0) {
        void* mem = EAAllocate(0x38, (const char*)0x148b8a4, 0, 0, 0, 0);
        pl = mem != 0 ? ((CPropList*)mem)->init() : 0;
        at<int>(pl, 8)  = 0x3a39cb0d;
        at<int>(pl, 0xc) = 0xb1b104;
        at<int>(pl, 0x10) = 0x11ac192;
    }

    Variant v;
    v.Construct(0x12, 9, (char*)this + 0x8c, 0x10, 1);
    ((void (__thiscall*)(void*, int, Variant*))
     ((void**)*(void**)pl)[0x14 / 4])(pl, 0x5664bf5, &v);
    if (v.mFlags & 4)
        v.Destruct(0);

    EaStr enc;
    Encrypt(&enc, (char*)this + 0x9c);

    Variant v2;
    v2.Construct(0x12, 9, &enc, 0x10, 1);
    ((void (__thiscall*)(void*, int, Variant*))
     ((void**)*(void**)pl)[0x14 / 4])(pl, 0x5664bf6, &v2);
    if (v2.mFlags & 4)
        v2.Destruct(0);

    void* area = SP_GetSaveArea(0x11ac192);
    if (area != 0)
        SP_SaveNamedResource(g_ytLoginKey, enc.mpBegin, area);
}

// ------------------------------------------------------------------ 00f05110
// Centre the "youtube icon + caption" pair inside the share panel and resize
// both windows to the panel width.
// @ 0x00f05110
void Movie::LayoutYouTube()
{
    cString title(0x7518573e, 0x5e51108, 0);
    EaStr16 text;

    const ushort* p = (const ushort*)title.GetText();
    const ushort* end = p;
    while (*end != 0)
        end++;
    WString_Assign(&text, p, end);

    Layout* lay = (Layout*)at<void*>(this, 0x2c);
    void* icon  = lay->FindWindowByID(0x5e51108, 1);
    void* label = lay->FindWindowByID(0x5daa660, 1);

    bool compact = true;
    if (label != 0)
        ((void (__thiscall*)(void*, void*))((void**)*(void**)label)[0x80 / 4])(label, text.mpBegin);
    if (label != 0)
        AutoSizeWindowForText(label, 0, 0);

    RectF r1 = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)icon)[0x38 / 4])(icon);
    RectF r2 = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)label)[0x38 / 4])(label);

    if (!compact) {
        r2.left   = (r2.right - r2.left) + r1.left;
        r2.bottom = (r2.bottom - r2.top) + r2.top;
        ((void (__thiscall*)(void*, const RectF*))
         ((void**)*(void**)label)[0x6c / 4])(label, &r2);

        RectF r2b = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)label)[0x38 / 4])(label);
        float h = r2b.right + 3.0f;
        r1.right  = (r1.right - r1.left) + h;
        r1.bottom = (r1.bottom - r1.top) + r1.top;
        ((void (__thiscall*)(void*, const RectF*))
         ((void**)*(void**)icon)[0x6c / 4])(icon, &r1);
        r2.left = ((RectF* (__thiscall*)(void*))((void**)*(void**)label)[0x38 / 4])(label)->left;
    }

    RectF ir = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)icon)[0x38 / 4])(icon);
    float leftEdge = ir.left;
    RectF lr = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)label)[0x38 / 4])(label);

    void* panel = lay->FindWindowByID(0x5b5ef50, 1);
    RectF pr = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)panel)[0x38 / 4])(panel);

    float shift = (lr.left + leftEdge) * 0.5f - (pr.right - pr.left) * 0.5f;

    RectF io = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)icon)[0x38 / 4])(icon);
    io.left  = io.left - shift;
    io.right = (io.right - (io.left + shift)) + io.left;
    io.bottom = (io.bottom - io.top) + io.top;
    ((void (__thiscall*)(void*, const RectF*))
     ((void**)*(void**)icon)[0x6c / 4])(icon, &io);

    RectF lo = *(RectF*)((RectF* (__thiscall*)(void*))((void**)*(void**)label)[0x38 / 4])(label);
    lo.left  = lo.left - shift;
    lo.right = (lo.right - (lo.left + shift)) + lo.left;
    ((void (__thiscall*)(void*, const RectF*))
     ((void**)*(void**)label)[0x6c / 4])(label, &lo);
}
