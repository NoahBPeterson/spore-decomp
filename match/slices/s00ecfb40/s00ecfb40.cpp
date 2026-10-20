// Slice s00ecfb40 -- SP editor verb-tray page, economy value holders and the
// complexity-meter / rollover page helpers. The original objects are COM-style classes
// with several vtable bases; the stubs below reproduce only the member offsets and
// vtable slots that these functions touch (retail offsets are noted per field).

typedef unsigned int uint32_t;

// ---------------------------------------------------------------- call thunks
typedef void  (__thiscall *Fn0)(void*);
typedef void  (__thiscall *Fn1)(void*, int);
typedef void  (__thiscall *Fn1U)(void*, unsigned int);
typedef void  (__thiscall *Fn1F)(void*, float);
typedef void  (__thiscall *Fn2)(void*, int, int);
typedef void  (__thiscall *Fn3)(void*, void*, int, int);
typedef void  (__thiscall *Fn4)(void*, int, void*, int, int);
typedef void  (__thiscall *FnV2)(void*, void*, float, float);
typedef void* (__thiscall *Fn0P)(void*);
typedef void* (__thiscall *Fn1P)(void*, void*);
typedef void* (__thiscall *Fn2P)(void*, int, int);
typedef int   (__thiscall *Fn2I)(void*, void*, int);
typedef unsigned char (__thiscall *Fn0B)(void*);

struct cSettingsBlock;

// ---------------------------------------------------------------- external helpers
void __cdecl operator_delete(void*);                                      // 0x00f47380
void __cdecl EA_MultiHeapDelete(void*);                                   // 0x00951330
void __cdecl EA_RemoveHandler(void*, void*, void*, void*, void*);         // 0x00571db0
void* __cdecl EA_Allocate(unsigned int, const char*, int, int, int, int); // 0x00f473a0

float GetElapsedSeconds();                                                // 0x00805080
void  SP_ApplyVector(void*, float*);                                      // 0x00808230
void* SP_MessageServer();                                                 // 0x0067dcc0
void* SP_WindowManager();                                                 // 0x0067caa0
unsigned int SP_ColorRGBAToU32(float*);                                   // 0x004580c0
unsigned int SP_ColorRGBToU32(float*);                                    // 0x00458a40
void  Rollover_Reset(void*);                                              // 0x00605300
void  Rollover_Update(void*);                                             // 0x006052f0

extern float g_colorR, g_colorG, g_colorB;                                // 0x015abf30/34/38
extern int   g_complexityMax;                                             // 0x015abf2c
extern void* g_vtbl_gmeEditorResBase;                                     // 0x013eb938
extern void* g_vtbl_IMsgHandler;                                          // 0x013eb394
extern void* g_vtbl_RefCount;                                             // 0x013ec458
extern void* g_vtbl_EditorPage0;                                          // 0x014898e0
extern void* g_vtbl_EditorPage1;                                          // 0x014898d8
extern void* g_vtbl_EditorPage2;                                          // 0x014898c8
extern void* g_vtbl_Meter0;                                               // 0x01489938
extern void* g_vtbl_Meter8;                                               // 0x01489930
extern void* g_vtbl_SmallRef;                                             // 0x014898b0
extern unsigned int g_msgIds[3];                                          // 0x014898fc
extern const wchar_t g_emptyString16[];                                   // 0x01667bac
extern const wchar_t g_labelFormat[];                                     // 0x013ec468
extern void* g_editorSingleton;                                           // 0x016c7aa4
extern const char g_editorAllocName[];                                    // 0x013eb430
extern float g_unusedFloat;                                               // 0x01485720

// ---------------------------------------------------------------- UI stubs
struct IWindow { void** mpVtbl; };

struct cSPUILayout {
    void** mpVtbl;                                                      // 0x00
    IWindow* FindWindowByID(unsigned int id, bool recurse);              // 0x008105b0
    bool Init(const void* key, bool a, unsigned int b);                  // 0x008120d0
    bool SetParentWin(IWindow* parent, bool a, unsigned int b);          // 0x008121b0
    void Shutdown(unsigned int flags);                                   // 0x00811ad0
};

struct cString {
    unsigned int mBegin;                    // 0x00
    unsigned int mEnd;                      // 0x04
    unsigned int mCapacity;                 // 0x08
    int mTable;                             // 0x0c
    int mId;                                // 0x10
    cString(unsigned int table, unsigned int id, const wchar_t* text); // 0x006b5770
    void Load(unsigned int table, unsigned int id, int a);              // 0x006b54b0
    const wchar_t* GetText();                                           // 0x006b55c0
    void Destroy();                                                     // 0x006b5240
};

struct cWString {
    unsigned int mBegin;                    // 0x00
    unsigned int mEnd;                      // 0x04
    unsigned int mCapacity;                 // 0x08
    void Construct();                          // 0x005a7810
    void RangeInitialize(const wchar_t* text); // 0x00579a90
    void Destroy();                            // 0x006b5240
};

struct Variant {
    unsigned int mData;                     // 0x00
    unsigned int mPad[3];                   // 0x04
    unsigned char mFlags;                   // 0x10
    void Destruct(bool a);                  // 0x0093db80
};

struct cSelectionServer {
    void* mUnk00;                           // 0x00
    void* Lookup(int id);                   // 0x00f3e8a0
    unsigned char HasSetting(int id);       // 0x00f3ec90
    unsigned char HasSettingSmall(int id);  // 0x00f326d0
    void GetPairA(void** a, void** b);      // 0x00f25110
    void GetPairB(void** a, void** b);      // 0x00f25190
    void FinalizeString(void** s);          // 0x00f28b80
};

struct cVerbIconRollover {
    void** mpVtbl;                          // 0x00
    cVerbIconRollover* Construct();         // 0x006051d0
    void SetValue(int id, void* value, int a, int b);         // 0x00828c30
    void SetVisibility(unsigned int id, unsigned int v);      // 0x006052c0
    void Layout(int a);                                       // 0x006053a0
    void* GetRootWindow();                                    // 0x00828100
    void BeginUpdate();                                       // 0x006052f0
    void SetPositionAndOffset(float x, float y, float w, float h); // 0x008283a0
};

struct cConnectionDialog {
    cConnectionDialog* Construct();         // 0x00810000
};

// 0x00ecfd50's object: two vtable pointers at +0x6c/+0x70 and a child at +0x7c.
struct cEditorResource2 {
    char pad00[0x6c];
    void** mpVtbl6c;                        // 0x6c
    void** mpVtbl70;                        // 0x70
    char pad74[8];
    void* mpChild;                          // 0x7c
    void BaseDestroy();                     // 0x00ecdd70
    void* Destroy(unsigned int flags);      // 0x00ecfd50
};

// Base subobject of the verb-tray page (lives at this-0x24).
struct cTrayBase {
    char pad00[0x10];
    int mDescriptionId;                     // 0x10 (page-relative -0x14)
    void Rebind();                          // 0x00ecf000
    void Refresh();                         // 0x00ece790
};

// 0x00ecfb40 / 0x00ecfd90: verb-tray page.
struct cVerbTrayPage {
    char pad00[0x28];
    void* mpDescription;                    // 0x28
    cSPUILayout* mpLayout;                  // 0x2c
    char pad30[0x0c];
    void* mpRenderTarget;                   // 0x3c
    char pad40[4];
    unsigned char mActive;                  // 0x44
    void Refresh(int unused);               // 0x00ecfb40
    void RefreshAndFlush(int unused);       // 0x00ecfd90
};

// 0x00ecfc40 / 0x00ecfdb0 / 0x00ecfdf0: page controls.
struct cPageControls {
    void** mpVtbl;                          // 0x00
    char pad04[0x0c];
    int mPageId;                            // 0x10
    char pad14[0x3c];
    cSPUILayout* mpLayout;                  // 0x50
    char pad54[0x14];
    unsigned char mInitialized;             // 0x68
    void RefreshFromSelection();            // 0x00ecfc40
    void SetPageId(int id);                 // 0x00ecfdb0
    void OnChanged();                       // 0x00ecfdf0
    void RefreshInner();                    // 0x00ecf940
};

// 0x00ecfe30/70/c0: the eight editable economy values.
struct cEconomyValues {
    char pad00[8];
    int mValue;                             // 0x08, followed by further ints
    int GetValue(int index);                // 0x00ecfe30
    void AddValue(int index, int delta);    // 0x00ecfe70
    void SetValue(int index, int value);    // 0x00ecfec0
    void SendChangedMessage();              // 0x005a7840
};

// 0x00ecff90: small ref-counted holder.
struct cSmallRef {
    void** mpVtbl;                          // 0x00
    int mRefCount;                          // 0x04
    cSelectionServer* mpServer;             // 0x08
    cSmallRef(cSelectionServer* server);    // 0x00ecff90
    unsigned int Load(int id, cSettingsBlock* settings); // 0x00ecffd0
};

// settings block used by the two Load helpers (two 0x14-byte strings + a dword).
void cWString_Set(Variant* variant, cWString* text);                      // 0x005a74a0

struct cSettingsBlock {
    cString mName;                          // 0x00
    cString mDesc;                          // 0x14
    unsigned int mUnk28;                    // 0x28
    unsigned int mFlags;                    // 0x2c
};

// 0x00ed02c0 .. 0x00ed0750: editor page with three vtable bases and the rollover child.
struct cEditorPage {
    void** mpVtbl0;                         // 0x00
    void** mpVtbl1;                         // 0x04
    void** mpVtbl2;                         // 0x08
    int mUnk0c;                             // 0x0c
    void* mpLayout;                         // 0x10
    void* mpWinMeter;                       // 0x14
    void* mpWinFrame;                       // 0x18
    void* mpWinSlider;                      // 0x1c
    void* mpData;                           // 0x20
    float mRect[4];                         // 0x24
    float mPercent;                         // 0x34
    int mTimeCounter;                       // 0x38
    unsigned char mFlag3c;                  // 0x3c
    unsigned char mFlag3d;                  // 0x3d
    unsigned char mFlag3e;                  // 0x3e
    char pad3f;                             // 0x3f
    void* mpRollover;                       // 0x40
    void* mpServer;                         // 0x44
    void* mpHandler;                        // 0x48
    void* mpMsgIds;                         // 0x4c
    int mMsgCount;                          // 0x50
    int mMsgUser;                           // 0x54
    cEditorPage();                          // 0x00ed02c0
    void Destroy();                         // 0x00ed0340
    void Update(int delta);                 // 0x00ed0030
    unsigned char HandleMessage(int msg, void** data); // 0x00ed01a0
    void* AsInterface(int id);              // 0x00ed0260
    void Init(void* parent, void* source);  // 0x00ed0400
    void Shutdown();                        // 0x00ed0660
    unsigned char HandleEvent(int id, void* ev); // 0x00ed0750
};

// 0x00ed0ab0/0x00ed0b00.
struct cMeterChild {
    void** mpVtbl0;                         // 0x00
    int mUnk04;                             // 0x04
    void** mpVtbl8;                         // 0x08
    unsigned char mFlag0c;                  // 0x0c
    char pad0d[3];
    void* mPtr10;                           // 0x10
    void* mPtr14;                           // 0x14
    char pad18[8];
    void* mpServer;                         // 0x20
    char pad24[0x10];
    void* mpChild;                          // 0x34
    char pad38[4];
    cMeterChild();                          // 0x00ed0ab0
    void Destroy();                         // 0x00ed0b00
};

// @ 0x00ecfb40
void cVerbTrayPage::Refresh(int)
{
    if (!mActive)
        return;

    bool visible = false;
    if (*(int*)((char*)this - 0x14) == -1) {
        if (mpRenderTarget)
            ((Fn2)(*(void***)mpRenderTarget)[0x7c / 4])(mpRenderTarget, 1, 0);
        mActive = 0;
    } else {
        int* desc = *(int**)((char*)mpDescription + 0x118);
        if (desc && ((desc[1] >> 0xe) & 1) && ((desc[1] >> 0x12) & 1) == 0) {
            visible = false;
            ((cTrayBase*)((char*)this - 0x24))->Rebind();
        } else {
            visible = true;
            if (mpRenderTarget) {
                float t = GetElapsedSeconds();
                float v[4];
                v[0] = 0.0f;
                v[1] = 0.0f;
                v[2] = 1.0f;
                v[3] = -(t + t);
                SP_ApplyVector(mpRenderTarget, v);
            }
        }
    }

    if (mpLayout) {
        unsigned int ids[3];
        ids[0] = 0x73d54a0;
        ids[1] = 0x73272b0;
        ids[2] = 0x4a1cb6d;
        for (int i = 0; i < 3; ++i) {
            IWindow* w = mpLayout->FindWindowByID(ids[i], true);
            if (w)
                ((Fn2)(*(void***)w)[0x7c / 4])(w, 2, !visible);
        }
    }
}

// @ 0x00ecfc40
void cPageControls::RefreshFromSelection()
{
    if (mPageId == -1)
        goto tail;

    {
        cSelectionServer* server = *(cSelectionServer**)((char*)g_editorSingleton + 0x74);
        ((Fn1)(*(void***)this)[0x30 / 4])(this, (int)server->Lookup(mPageId));

        server = *(cSelectionServer**)((char*)g_editorSingleton + 0x74);
        cSelectionServer* sel = (cSelectionServer*)server->Lookup(mPageId);

        void* pairA0;
        void* pairA1;
        sel->GetPairA(&pairA0, &pairA1);
        ((Fn2)(*(void***)this)[0x38 / 4])(this, (int)&pairA0, (int)pairA1);

        void* pairB0;
        void* pairB1;
        sel->GetPairB(&pairB0, &pairB1);
        ((Fn2)(*(void***)this)[0x3c / 4])(this, (int)&pairB0, (int)pairB1);

        const wchar_t* text[3];
        text[0] = g_emptyString16;
        text[1] = g_emptyString16;
        text[2] = g_emptyString16 + 1;
        sel->FinalizeString((void**)&text[0]);
        ((Fn1)(*(void***)this)[0x40 / 4])(this, (int)text[0]);

        ((cTrayBase*)((char*)this - 0x24))->Rebind();

        unsigned int span = ((unsigned int)text[2] - (unsigned int)text[0]) & 0xfffffffe;
        if (span > 2 && text[0])
            operator_delete((void*)text[0]);
    }

tail:
    if (mpLayout) {
        IWindow* w = mpLayout->FindWindowByID(0x4a1cb6e, true);
        if (w)
            ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, mPageId != -1);
    }
    mInitialized = 1;
}

// @ 0x00ecfd50
void* cEditorResource2::Destroy(unsigned int flags)
{
    if (mpChild)
        ((Fn0)(*(void***)mpChild)[8 / 4])(mpChild);
    mpVtbl70 = &g_vtbl_gmeEditorResBase;
    mpVtbl6c = &g_vtbl_gmeEditorResBase;
    BaseDestroy();
    if (flags & 1)
        EA_MultiHeapDelete(this);
    return this;
}

// @ 0x00ecfd90
void cVerbTrayPage::RefreshAndFlush(int unused)
{
    Refresh(unused);
    ((cTrayBase*)((char*)this - 0x24))->Refresh();
}

// @ 0x00ecfdb0
void cPageControls::SetPageId(int id)
{
    if (id == -1) {
        mPageId = id;
        ((Fn0)(*(void***)this)[0x18 / 4])(this);
    } else {
        mPageId = id;
        ((Fn0)(*(void***)this)[0x14 / 4])(this);
    }
    RefreshInner();
}

// @ 0x00ecfdf0
void cPageControls::OnChanged()
{
    RefreshFromSelection();
    RefreshInner();
    int id = mPageId;
    void* server = SP_MessageServer();
    ((Fn3)(*(void***)server)[0x14 / 4])(server, (void*)0x796d3a0, id, 0);
}

// @ 0x00ecfe30
int cEconomyValues::GetValue(int index)
{
    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
        return ((int*)((char*)this + 8))[index];
    case 4:
    case 5:
    case 6:
    case 7:
        return ((int*)((char*)this + 0xc))[index];
    }
    return 0;
}

// @ 0x00ecfe70
void cEconomyValues::AddValue(int index, int delta)
{
    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
        ((int*)((char*)this + 8))[index] += delta;
        SendChangedMessage();
        return;
    case 4:
    case 5:
    case 6:
    case 7:
        ((int*)((char*)this + 0xc))[index] += delta;
        break;
    }
    SendChangedMessage();
}

// @ 0x00ecfec0
void cEconomyValues::SetValue(int index, int value)
{
    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
        if (((int*)((char*)this + 8))[index] == value)
            return;
        ((int*)((char*)this + 8))[index] = value;
        SendChangedMessage();
        return;
    case 4:
    case 5:
    case 6:
    case 7:
        if (((int*)((char*)this + 0xc))[index] == value)
            return;
        ((int*)((char*)this + 0xc))[index] = value;
        SendChangedMessage();
        break;
    }
}

// @ 0x00ecff30
unsigned int __stdcall LoadEconomySettings(int id, cSettingsBlock* settings)
{
    cSelectionServer* server = *(cSelectionServer**)((char*)g_editorSingleton + 0x74);
    if (!server->HasSetting(id)) {
        if (settings) {
            settings->mName.Load(0x81219557, 0x7426209, 0);
            settings->mDesc.Load(0x81219557, 0x742620a, 0);
            settings->mFlags = 0x22c4855f;
        }
        return 3;
    }
    return 1;
}

// @ 0x00ecff90
cSmallRef::cSmallRef(cSelectionServer* server)
{
    mRefCount = 0;
    mpVtbl = &g_vtbl_SmallRef;
    mpServer = server;
    if (server)
        ((Fn0)(*(void***)server)[8 / 4])(server);
}

// @ 0x00ecffd0
unsigned int cSmallRef::Load(int id, cSettingsBlock* settings)
{
    if (!mpServer->HasSettingSmall(id)) {
        if (settings) {
            settings->mName.Load(0x81219557, 0x7426209, 0);
            settings->mDesc.Load(0x81219557, 0x742620a, 0);
            settings->mFlags = 0x22c4855f;
        }
        return 3;
    }
    return 1;
}

// @ 0x00ed0030
void cEditorPage::Update(int delta)
{
    if (mpWinMeter && mpWinFrame && mpWinFrame) {
        void* win = mpWinFrame;
        void* meter = ((Fn1P)(*(void***)win)[0xc / 4])(win, (void*)0x10edf11);
        if (meter) {
            float pct = mPercent * 100.0f;
            if (pct < 0.0f)
                pct = 0.0f;
            if (pct > 100.0f)
                pct = 100.0f;
            ((Fn1F)(*(void***)meter)[4 / 4])(meter, pct);
        }
    }

    if (mFlag3c) {
        if (!mFlag3d) {
            mTimeCounter = 0;
            mFlag3d = 1;
        }
    }
    if (!mFlag3d)
        return;

    int half = g_complexityMax / 2;
    int v = mTimeCounter;
    if (v < half)
        v = half - v;
    else
        v = v - half;
    float ratio = (float)v / (float)half;

    float rgba[4];
    rgba[0] = g_colorR;
    rgba[1] = g_colorG;
    rgba[2] = g_colorB;
    rgba[3] = ratio;
    unsigned int color = SP_ColorRGBAToU32(rgba);

    void* frame = mpWinFrame;
    ((Fn1U)(*(void***)frame)[0x5c / 4])(frame, color);
    mTimeCounter += delta;

    if (mTimeCounter <= g_complexityMax)
        return;

    if (!mFlag3c && !mFlag3e) {
        unsigned int reset = SP_ColorRGBToU32(&g_colorR);
        ((Fn1U)(*(void***)frame)[0x5c / 4])(frame, reset);
        mFlag3d = 0;
        return;
    }

    mTimeCounter %= g_complexityMax;
    mFlag3e = 0;
}

// @ 0x00ed01a0
unsigned char cEditorPage::HandleMessage(int msg, void** data)
{
    if (((Fn0B)(*(void***)mpWinSlider)[0x28 / 4])(mpWinSlider) & 1) {
        if (msg == 0x522f9cd) {
            if (*data) {
                void* res = ((Fn1P)(*(void***)(*data))[0xc / 4])(*data, (void*)0x31e56741);
                if (res && mpData) {
                    cWString textA;
                    cWString textB;
                    textA.Construct();
                    textB.Construct();
                    int r = ((Fn2I)(*(void***)mpData)[0x10 / 4])(mpData, (char*)res + 0x4c, 0);
                    unsigned char* flags = (unsigned char*)((char*)this + 0x38);
                    if (r == 3) {
                        flags[0] = 1;
                        flags[2] = 0;
                    } else {
                        flags[0] = 0;
                    }
                    textB.Destroy();
                    textA.Destroy();
                }
            }
            return 1;
        }
        if (msg == 0x522f9ce) {
            *(unsigned char*)((char*)this + 0x38) = 0;
            return 1;
        }
        if (msg == 0x78c406b) {
            unsigned char* flags = (unsigned char*)((char*)this + 0x38);
            flags[1] = 1;
            flags[2] = 1;
        }
    }
    return 0;
}

// @ 0x00ed0260
void* cEditorPage::AsInterface(int id)
{
    void* slider = mpWinSlider;
    if (slider)
        return ((Fn2P)(*(void***)slider)[0x7c / 4])(slider, 1, id);
}

// @ 0x00ed02c0
cEditorPage::cEditorPage()
{
    *(void* volatile*)((char*)this + 4) = &g_vtbl_IMsgHandler;
    *(void* volatile*)((char*)this + 8) = &g_vtbl_RefCount;
    mUnk0c = 0;
    mpVtbl0 = &g_vtbl_EditorPage0;
    mpVtbl1 = &g_vtbl_EditorPage1;
    mpVtbl2 = &g_vtbl_EditorPage2;
    mpLayout = 0;
    mpWinMeter = 0;
    mpWinFrame = 0;
    mpWinSlider = 0;
    mpData = 0;
    mPercent = 0.0f;
    mTimeCounter = 0;
    mFlag3c = 0;
    mFlag3d = 0;
    mFlag3e = 0;
    mpRollover = 0;
    mpServer = 0;
    mpHandler = 0;
    mpMsgIds = 0;
    mMsgCount = 0;
    mMsgUser = 0;
}

// @ 0x00ed0340
void cEditorPage::Destroy()
{
    mpVtbl0 = &g_vtbl_EditorPage0;
    mpVtbl1 = &g_vtbl_EditorPage1;
    mpVtbl2 = &g_vtbl_EditorPage2;
    if (mpServer) {
        void* server = mpServer;
        mpServer = 0;
        EA_RemoveHandler(server, mpHandler, mpMsgIds, (void*)mMsgCount, (void*)mMsgUser);
    }
    if (mpRollover)
        ((Fn0)(*(void***)mpRollover)[4 / 4])(mpRollover);
    if (mpData) {
        int* ref = (int*)mpData;
        ref[1] += -1;
        if (ref[1] == 0) {
            ref[1] = 1;
            ((Fn1)(*(void***)ref)[0 / 4])(ref, 1);
        }
    }
    if (mpWinSlider)
        ((Fn0)(*(void***)mpWinSlider)[4 / 4])(mpWinSlider);
    if (mpWinFrame)
        ((Fn0)(*(void***)mpWinFrame)[4 / 4])(mpWinFrame);
    if (mpWinMeter)
        ((Fn0)(*(void***)mpWinMeter)[4 / 4])(mpWinMeter);
    if (mpLayout)
        ((Fn0)(*(void***)mpLayout)[8 / 4])(mpLayout);
    mpVtbl2 = &g_vtbl_RefCount;
    mpVtbl1 = &g_vtbl_IMsgHandler;
    mpVtbl0 = &g_vtbl_gmeEditorResBase;
}

// @ 0x00ed0400
void cEditorPage::Init(void* parent, void* source)
{
    if (source != mpData) {
        if (source)
            ++((int*)source)[1];
        void* old = mpData;
        mpData = source;
        if (old && --((int*)old)[1] == 0) {
            ((int*)old)[1] = 1;
            ((Fn1)(*(void***)old)[0 / 4])(old, 1);
        }
    }

    void* mem = EA_Allocate(0x18, g_editorAllocName, 0, 0, 0, 0);
    cConnectionDialog* dialog = mem ? ((cConnectionDialog*)mem)->Construct() : 0;
    void* oldLayout = mpLayout;
    if (dialog != oldLayout) {
        if (dialog)
            ((Fn0)(*(void***)dialog)[4 / 4])(dialog);
        mpLayout = dialog;
        if (oldLayout)
            ((Fn0)(*(void***)oldLayout)[8 / 4])(oldLayout);
    }

    unsigned int key[3];
    key[0] = 0xc01318c2;
    key[1] = 0x510a95b;
    key[2] = 0x40464100;
    ((cSPUILayout*)mpLayout)->Init(key, true, 0x5b598fa);
    ((cSPUILayout*)mpLayout)->SetParentWin((IWindow*)parent, true, 0x5b598fa);

    IWindow* win = ((cSPUILayout*)mpLayout)->FindWindowByID(0x330c1ca5, true);
    if (win != (IWindow*)mpWinSlider) {
        if (win)
            ((Fn0)(*(void***)win)[0 / 4])(win);
        void* old = mpWinSlider;
        mpWinSlider = win;
        if (old)
            ((Fn0)(*(void***)old)[4 / 4])(old);
    }
    if (mpWinSlider)
        ((Fn2)(*(void***)mpWinSlider)[0x7c / 4])(mpWinSlider, 1, 1);

    win = ((cSPUILayout*)mpLayout)->FindWindowByID(0x530c12d0, true);
    if (win != (IWindow*)mpWinMeter) {
        if (win)
            ((Fn0)(*(void***)win)[0 / 4])(win);
        void* old = mpWinMeter;
        mpWinMeter = win;
        if (old)
            ((Fn0)(*(void***)old)[4 / 4])(old);
    }

    win = ((cSPUILayout*)mpLayout)->FindWindowByID(0x5bad010, true);
    if (win != (IWindow*)mpWinFrame) {
        if (win)
            ((Fn0)(*(void***)win)[0 / 4])(win);
        void* old = mpWinFrame;
        mpWinFrame = win;
        if (old)
            ((Fn0)(*(void***)old)[4 / 4])(old);
    }

    if (mpWinMeter) {
        float* area = (float*)((Fn0P)(*(void***)mpWinMeter)[0x34 / 4])(mpWinMeter);
        mRect[0] = area[0];
        mRect[1] = area[1];
        mRect[2] = area[2];
        mRect[3] = area[3];
    }

    mem = EA_Allocate(0x78, g_editorAllocName, 0, 0, 0, 0);
    cVerbIconRollover* roll = mem ? ((cVerbIconRollover*)mem)->Construct() : 0;
    if (roll != (cVerbIconRollover*)mpRollover) {
        if (roll)
            ((Fn0)(*(void***)roll)[0 / 4])(roll);
        void* old = mpRollover;
        mpRollover = roll;
        if (old)
            ((Fn0)(*(void***)old)[4 / 4])(old);
    }
    ((Fn0)(*(void***)mpRollover)[0x1c / 4])(mpRollover);

    if (mpWinFrame)
        ((Fn1)(*(void***)mpWinFrame)[0x104 / 4])(mpWinFrame, (int)this);

    void* server = SP_MessageServer();
    mpServer = server;
    mpHandler = (char*)this + 4;
    mpMsgIds = &g_msgIds;
    mMsgCount = 3;
    mMsgUser = 0;
    if (server && mpHandler) {
        for (int i = 0; i < 3; ++i)
            ((Fn2)(*(void***)server)[0x24 / 4])(server, (int)mpHandler, (int)g_msgIds[i]);
    }
}

// @ 0x00ed0660
void cEditorPage::Shutdown()
{
    if (mpServer) {
        void* server = mpServer;
        mpServer = 0;
        EA_RemoveHandler(server, mpHandler, mpMsgIds, (void*)mMsgCount, (void*)mMsgUser);
    }
    if (mpWinSlider) {
        void* p = mpWinSlider;
        mpWinSlider = 0;
        ((Fn0)(*(void***)p)[4 / 4])(p);
    }
    if (mpWinFrame) {
        void* p = mpWinFrame;
        mpWinFrame = 0;
        ((Fn0)(*(void***)p)[4 / 4])(p);
    }
    if (mpWinMeter) {
        void* p = mpWinMeter;
        mpWinMeter = 0;
        ((Fn0)(*(void***)p)[4 / 4])(p);
    }
    if (mpLayout) {
        ((cSPUILayout*)mpLayout)->Shutdown(1);
        void* p = mpLayout;
        mpLayout = 0;
        ((Fn0)(*(void***)p)[8 / 4])(p);
    }
    if (mpRollover) {
        ((Fn0)(*(void***)mpRollover)[0x24 / 4])(mpRollover);
        void* p = mpRollover;
        mpRollover = 0;
        ((Fn0)(*(void***)p)[4 / 4])(p);
    }
    if (mpData) {
        int* ref = (int*)mpData;
        mpData = 0;
        int count = ref[1] - 1;
        ref[1] = count;
        if (count == 0) {
            ref[1] = 1;
            ((Fn1)(*(void***)ref)[0 / 4])(ref, 1);
        }
    }
}

// @ 0x00ed0750
unsigned char cEditorPage::HandleEvent(int, void* evp)
{
    int* ev = (int*)evp;
    if (ev[2] != 10 || ev[3] != 1)
        return 0;

    if (ev[6] != (int)mpWinFrame) {
        if (mpRollover)
            Rollover_Reset(mpRollover);
        return 0;
    }
    if (!mpRollover)
        return 0;

    cString name(0x81219557, 0x5f110b3, 0);
    cString desc(0x81219557, 0x5f110b4, 0);

    cWString text0;
    text0.RangeInitialize(g_labelFormat);
    cWString text1;
    text1.RangeInitialize(desc.GetText());
    cWString text2;
    text2.RangeInitialize(name.GetText());

    Variant v1;
    v1.mData = 0;
    v1.mPad[0] = 0;
    v1.mPad[1] = 0;
    v1.mPad[2] = 0;
    v1.mFlags = 0;
    cWString_Set(&v1, &text2);
    cVerbIconRollover* roll = (cVerbIconRollover*)mpRollover;
    roll->SetValue(0x331cc0e, &v1, 1, 0);
    if (v1.mFlags & 4)
        v1.Destruct(false);

    Variant v2;
    v2.mData = 0;
    v2.mPad[0] = 0;
    v2.mPad[1] = 0;
    v2.mPad[2] = 0;
    v2.mFlags = 0;
    cWString_Set(&v2, &text0);
    roll->SetValue(0x4d97708, &v2, 1, 0);
    if (v2.mFlags & 4)
        v2.Destruct(false);

    Variant v3;
    v3.mData = 0;
    v3.mPad[0] = 0;
    v3.mPad[1] = 0;
    v3.mPad[2] = 0;
    v3.mFlags = 0;
    cWString_Set(&v3, &text1);
    roll->SetValue(0x331cc0f, &v3, 1, 0);
    if (v3.mFlags & 4)
        v3.Destruct(false);

    roll->SetVisibility(0x4d97710, 0);
    ((Fn0)(*(void***)roll)[0x20 / 4])(roll);
    roll->Layout(0);

    float* frame = (float*)((Fn0P)(*(void***)mpWinFrame)[0x38 / 4])(mpWinFrame);
    void* slider = (void*)((Fn0P)(*(void***)mpWinFrame)[0x10 / 4])(mpWinFrame);
    float px = (frame[2] + frame[0]) * 0.5f;
    float py = (frame[3] + frame[1]) * 0.5f;
    float point[2];
    point[0] = 0.0f;
    point[1] = 0.0f;
    ((FnV2)(*(void***)slider)[0xc0 / 4])(slider, point, px, py);

    void* wm = SP_WindowManager();
    void* wmObj = ((Fn0P)(*(void***)wm)[4 / 4])(wm);
    float* screen = (float*)((Fn0P)(*(void***)wmObj)[0x34 / 4])(wmObj);
    float dx = (screen[2] - screen[0]) * 0.025f;
    float dy = (screen[3] - screen[1]) * 0.033333335f;

    IWindow* root = (IWindow*)roll->GetRootWindow();
    if (root) {
        float* rr = (float*)((Fn0P)(*(void***)root)[0x38 / 4])(root);
        if ((rr[2] - rr[0]) * 0.5f < point[0]) {
            rr = (float*)((Fn0P)(*(void***)root)[0x38 / 4])(root);
            dx = -(rr[2] - rr[0]) - dx;
        }
    }

    roll->BeginUpdate();
    roll->SetPositionAndOffset(point[0], point[1], dx, dy);

    if (((text0.mCapacity - text0.mBegin) & 0xfffffffe) > 2 && text0.mBegin)
        operator_delete((void*)text0.mBegin);
    if (((text1.mCapacity - text1.mBegin) & 0xfffffffe) > 2 && text1.mBegin)
        operator_delete((void*)text1.mBegin);
    if (((text2.mCapacity - text2.mBegin) & 0xfffffffe) > 2 && text2.mBegin)
        operator_delete((void*)text2.mBegin);

    desc.Destroy();
    name.Destroy();
    return 0;
}

// @ 0x00ed0ab0
cMeterChild::cMeterChild()
{
    mUnk04 = 0;
    *(void* volatile*)((char*)this + 8) = &g_vtbl_IMsgHandler;
    mpVtbl0 = &g_vtbl_Meter0;
    mpVtbl8 = &g_vtbl_Meter8;
    mFlag0c = 0;
    mPtr10 = 0;
    mPtr14 = 0;
    *(void**)((char*)this + 0x18) = 0;
    *(void**)((char*)this + 0x1c) = 0;
    mpServer = 0;
    *(void**)((char*)this + 0x24) = 0;
    *(void**)((char*)this + 0x28) = 0;
    *(void**)((char*)this + 0x2c) = 0;
    *(void**)((char*)this + 0x30) = 0;
    mpChild = 0;
    *(void**)((char*)this + 0x38) = 0;
}

// @ 0x00ed0b00
void cMeterChild::Destroy()
{
    *(void* volatile*)((char*)this + 0) = &g_vtbl_Meter0;
    *(void* volatile*)((char*)this + 8) = &g_vtbl_Meter8;
    void* child = *(void* volatile*)((char*)this + 0x34);
    if (child)
        ((Fn0)(*(void***)child)[8 / 4])(child);
    if (mpServer) {
        void* server = mpServer;
        mpServer = 0;
        EA_RemoveHandler(server, *(void**)((char*)this + 0x24),
                         *(void**)((char*)this + 0x28),
                         *(void**)((char*)this + 0x2c),
                         *(void**)((char*)this + 0x30));
    }
    if (mPtr14)
        ((Fn0)(*(void***)mPtr14)[4 / 4])(mPtr14);
    if (mPtr10)
        ((Fn0)(*(void***)mPtr10)[4 / 4])(mPtr10);
    *(void* volatile*)((char*)this + 0) = &g_vtbl_RefCount;
    *(void* volatile*)((char*)this + 8) = &g_vtbl_IMsgHandler;
}
