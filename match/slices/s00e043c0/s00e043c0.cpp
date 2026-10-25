// Slice s00e043c0 - SporeApp 0x00e043c0..0x00e05120
// SP::cSPUIGlobalUICiv (comm / relationship panel) and its progress-bar helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// Window lookup chain: cSPUIGlobalUI::FindWindowByID(this, id) reads this+0x08 (the cSPUILayout)
// and forwards to cSPUILayout::FindWindowByID(id, 1). Every window is then spoken to through its
// vtable (see the W* helpers below), which is also how the retail code is written.
#include "types.h"

typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
struct cSPUINewProgressBar {
    void** mpVptr;                                   // +0x00
    int    mRefCount;                                // +0x04
    u8     mData[0x30];                              // +0x08 (retail allocation is 0x38 bytes)

    void Update(float value, int mode);              // 0x00e29da0
    void SetMode(int mode);                          // 0x00e29c80
    void Shutdown();                                 // 0x00e28a80
    void Release()                                   // inline refcount drop, vtbl[0] at zero
    {
        if (--mRefCount == 0) {
            mRefCount = 1;
            ((void (__thiscall*)(void*, int))mpVptr[0])(this, 1);
        }
    }
};

// SP::cString: the engine's string object used by the SPUI helpers.
struct cString {
    char        mData[0x18];
    cString();                                    // 0x006b5060
    void Load(int key, int table, int flags);     // 0x006b54b0
    const char* c_str(int unused, int alloc);     // 0x006b55c0
    ~cString();                                   // 0x006b5240
};

struct cSPUILayout {
    char          mPad00[0x14];
    void*         mpWindows;                                  // +0x14 (hash table)
    void*         FindWindowByID(int id, int flag);           // 0x008105b0
    bool          Init(void* a, int b, int c, void* d);       // 0x00812160
    void          SetVisibility(int visible);                 // 0x00810590
    void          Shutdown(int flag);                         // 0x00811ad0
};

struct cSPUIGlobalUI {
    char          mPad00[8];
    cSPUILayout*  mpLayout;                                   // +0x08
    void*         FindWindowByID(int id);                     // 0x00e012b0
};

void __cdecl SPUIHelpers_SetWindowSPMaterial(void* window, int material, int flags); // 0x00808ad0
void __cdecl SPUIHelpers_SetTooltipText(void* window, const char* text);             // 0x00806de0
void* __cdecl SPUIHelpers_ConstructLayout(void* mem);                                // 0x00810000
void __cdecl RemoveHandler(void* a, void* b, void* c, void* d, void* e);             // 0x00571db0
void* __cdecl AppAllocate(unsigned size, const char* name, int a, int b,
                          const char* file, int line);                               // 0x00f473a0
void* __cdecl MessageServer();                                                       // 0x0067dcc0
void* __cdecl NounManagerInstance();                                                 // 0x00b3d300
int   __cdecl GameTime();                                                            // 0x011e0810
void* __cdecl GetActivePlanet();                                                     // 0x01021260
int   __cdecl ProgressLookup(int value);                                             // 0x00b6f0c0
int   __cdecl ProgressToColor(int value);                                            // 0x00458a40
int   __cdecl StateToMode(int index);                                                // 0x00bef920
int   __fastcall GetStateIndex(void* p, int edx);                                    // 0x00bf0f40
float __fastcall GetProgressFloat(void* p, int edx);                                 // 0x00bd80d0

// ---------------------------------------------------------------------------------------------
// Vtable-slot dispatch helpers
//
// The retail code calls every UI window through its vtable. Spelling the dispatch out inline (as
// function-pointer casts) keeps the object file free of undefined cSPUIWindow members, which the
// equivalence harness cannot resolve.
// ---------------------------------------------------------------------------------------------
static inline void  WShow(void* w)                        { ((void (__thiscall*)(void*))(*(void***)w)[0])(w); }
static inline void  WSetFloat(void* w, float v)           { ((void (__thiscall*)(void*, float))(*(void***)w)[1])(w, v); }
static inline void  WRelease(void* w)                     { ((void (__thiscall*)(void*))(*(void***)w)[1])(w); }
static inline int   WGetInt(void* w, int id)              { return ((int (__thiscall*)(void*, int))(*(void***)w)[3])(w, id); }
static inline void* WSetText10(void* w, const char* s)    { return ((void* (__thiscall*)(void*, const char*))(*(void***)w)[4])(w, s); }
static inline int   WGetFlags(void* w)                    { return ((int (__thiscall*)(void*))(*(void***)w)[8])(w); }
static inline void* WCall9(void* w, void* self, void* a)  { return ((void* (__thiscall*)(void*, void*, void*))(*(void***)w)[9])(w, self, a); }
static inline void  WSetProp(void* w, int a, int b)       { ((void (__thiscall*)(void*, int, int))(*(void***)w)[0xa])(w, a, b); }
static inline void  WSetMaterial(void* w, int a, int b)   { ((void (__thiscall*)(void*, int, int))(*(void***)w)[0x1f])(w, a, b); }
static inline void  WSetTitle(void* w, const char* s)     { ((void (__thiscall*)(void*, const char*))(*(void***)w)[0x20])(w, s); }
static inline void  WRefresh(void* w)                     { ((void (__thiscall*)(void*))(*(void***)w)[0x24])(w); }
static inline void* WGetChild(void* w)                    { return ((void* (__thiscall*)(void*))(*(void***)w)[0x2a])(w); }
static inline void* WSetCallback(void* w, int id, void* h) { return ((void* (__thiscall*)(void*, int, void*))(*(void***)w)[0x3c])(w, id, h); }
static inline void  WSetText104(void* w, const char* s)   { ((void (__thiscall*)(void*, const char*))(*(void***)w)[0x41])(w, s); }
static inline void  WSetText108(void* w, const char* s)   { ((void (__thiscall*)(void*, const char*))(*(void***)w)[0x42])(w, s); }

void __stdcall FlashCivCommButton(int unused1, void* window, int unused3);  // 0x00e04a50

// ---------------------------------------------------------------------------------------------
// Civ state -> icon tables (jump-table switches over a small civ-state enum)
// ---------------------------------------------------------------------------------------------
// @ 0x00e043c0
// Civ state 0..11 -> icon resource id; anything above 11 shares the "?" entry (case 2).
int __cdecl CivComm_GetStateIconName(int state)
{
    switch (state) {
    case 3:  return 0x10033;
    case 10: return 0x10031;
    case 9:  return 0x10035;
    case 11: return 0x10039;
    case 6:  return 0x1003b;
    case 0:  return 0x10037;
    case 4:  return 0x1003f;
    case 7:  return 0x10041;
    case 1:  return 0x1003d;
    case 5:  return 0x1006b;
    case 8:  return 0x1006d;
    case 2:
    default: return 0x1006f;
    }
}

// @ 0x00e04450
// Civ state 0..11 -> one of four small icon ids. Retail folds this through a byte map plus a
// four-entry jump table; spelled out here as a plain switch so the result is self-contained.
int __cdecl CivComm_GetStateIconIndex(int state)
{
    switch (state) {
    case 0:  return 0x71;
    case 1:  return 0x72;
    case 2:  return 0x73;
    case 3:  return 0x70;
    case 4:  return 0x72;
    case 5:  return 0x73;
    case 6:  return 0x71;
    case 7:  return 0x72;
    case 8:  return 0x73;
    case 9:  return 0x70;
    case 10: return 0x70;
    case 11: return 0x71;
    default: return 0x1006f;
    }
}

// @ 0x00e044b0
// Same state enum, the second row of icon ids.
int __cdecl CivComm_GetStateIconName2(int state)
{
    switch (state) {
    case 3:  return 0x10034;
    case 10: return 0x10032;
    case 9:  return 0x10036;
    case 11: return 0x1003a;
    case 4:  return 0x1003c;
    case 0:  return 0x10038;
    case 7:  return 0x10040;
    case 6:  return 0x10042;
    case 1:  return 0x1003e;
    case 5:  return 0x1006c;
    case 8:  return 0x1006e;
    case 2:  return 0x10070;
    default: return 0x1006f;
    }
}

// ---------------------------------------------------------------------------------------------
// FlashCivCommButton
// ---------------------------------------------------------------------------------------------
// @ 0x00e04a50
// Re-applies the civ-button material unless the window's child already carries it.
void __stdcall FlashCivCommButton(int unused1, void* window, int unused3)
{
    (void)unused1;
    (void)unused3;
    if (window != 0)
        WGetInt(window, 0x8ed27e7a);
    void* child = ((void* (__thiscall*)(void*))(*(void***)window)[0x13])(window);
    if (child == 0) {
        SPUIHelpers_SetWindowSPMaterial(window, 0x0147f2c8, 0);
    } else if (WGetInt(child, 0x5234b49) == 0) {
        SPUIHelpers_SetWindowSPMaterial(window, 0x0147f2c8, 0);
    }
}

// ---------------------------------------------------------------------------------------------
// cSPUIGlobalUICiv: the comm / relationship panel
// ---------------------------------------------------------------------------------------------
// Four civ entries start at +0x8c; each is 0xc bytes: icon id, a flash/visible byte pair and the
// entry's bound callback object.
struct CivButtonEntry {
    int   mIconIndex;            // +0x00
    u8    mbFlash;               // +0x04
    u8    mbVisible;             // +0x05
    u8    mPad06[2];             // +0x06
    void* mpCallback;            // +0x08
};

struct cSPUIGlobalUICiv : cSPUIGlobalUI {
    u8                    mPad000C[0x5c];      // +0x0c
    void*                 mvpField68;          // +0x68 vptr of the first embedded sub-object
    u8                    mPad6C[4];           // +0x6c
    void*                 mvpField70;          // +0x70 vptr of the message-handler sub-object
    void*                 mpField74;           // +0x74 message handler holder
    void*                 mpField78;           // +0x78 (handler identity: this)
    void*                 mpField7C;           // +0x7c (handler id table)
    int                   mField80;            // +0x80
    int                   mField84;            // +0x84
    u8                    mbField88;           // +0x88 minimap toggle byte
    u8                    mPad89[3];           // +0x89
    CivButtonEntry        mButtons[4];         // +0x8c .. +0xbb
    u8                    mPadBC[4];           // +0xbc
    cSPUINewProgressBar*  mpProgressBarC0;     // +0xc0
    cSPUILayout*          mpFieldC4;           // +0xc4 panel layout
    int                   mFieldC8;            // +0xc8
    int                   mFieldCC;            // +0xcc
    int                   mFieldD0;            // +0xd0
    int                   mFieldD4;            // +0xd4
    u8                    mbFieldsD8[4];       // +0xd8
    u8                    mPadDC[4];           // +0xdc (rbtree anchor starts here)
    u8                    mFieldE0[0x10];      // +0xe0

    void  SetProgress(float value, int mode);                       // 0x00e04540
    void  SetMinimapStateFromButton(int mode);                      // 0x00e04560
    void  SetStanceButtonsState(int a, int b, int c, int d, int e); // 0x00e046b0
    void  ActivateCommRelPanel(int index);                          // 0x00e04770
    void  UpdateButtonState(int index);                             // 0x00e04960
    void  OnPlayerCivChanged();                                     // 0x00e04aa0
    bool  Initialize();                                             // 0x00e04b40
    void  SetButtonProgress(int index);                             // 0x00e04d10
    cSPUIGlobalUICiv* Destroy();                                    // 0x00e04f10
    bool  CreatePanel(int param);                                   // 0x00e05000
    void  RemovePanel();                                            // 0x00e05120
};

// ---------------------------------------------------------------------------------------------
// Progress bar forwarding
// ---------------------------------------------------------------------------------------------
// @ 0x00e04540
// Forwards a progress value and its display mode to the owned progress bar.
void cSPUIGlobalUICiv::SetProgress(float value, int mode)
{
    mpProgressBarC0->Update(value, mode);
}

// ---------------------------------------------------------------------------------------------
// Minimap / stance button state
// ---------------------------------------------------------------------------------------------
// @ 0x00e04560
// Picks the minimap button state from the mode flag and the minimap toggle, then pushes the
// matching tooltip string onto the minimap button.
void cSPUIGlobalUICiv::SetMinimapStateFromButton(int mode)
{
    void* a = FindWindowByID(0x562a141);
    void* b = FindWindowByID(0x562a0f7);
    void* c = FindWindowByID(0x55d626f);
    void* d = FindWindowByID(0x46977ff);

    cString text;

    int textId;
    if (mode == 0 && (WGetFlags(a) & 4) == 0) {
        WSetProp(b, 4, 0);
        WSetMaterial(d, 1, 0);
        WSetMaterial(c, 1, mbField88);
        textId = 0x615ffa7;
    } else {
        WSetProp(b, 4, 1);
        int flag = (mode == 0 && mbField88 != 0) ? 1 : 0;
        WSetMaterial(d, 1, flag);
        WSetMaterial(c, 1, 0);
        textId = 0x615ffa8;
    }
    text.Load(0xc0152a6d, textId, 0);
    const char* str = text.c_str(-1, 1);
    void* target = WSetText10(c, str);
    SPUIHelpers_SetTooltipText(target, str);
}

// @ 0x00e046b0
// Sets the two stance buttons (window ids 0x4c61dd8 / 0x4c61b50) from five state bytes.
void cSPUIGlobalUICiv::SetStanceButtonsState(int a0, int a1, int a2, int a3, int a4)
{
    if (a0 != 0) {
        a3 = 1;
        a1 = 1;
    }

    void* w1 = FindWindowByID(0x4c61dd8);
    int icon1 = (int)WGetInt(w1, 0x8ed27e7a);
    WSetMaterial(w1, 2, a1);
    WSetProp((void*)icon1, 4, a1);
    WRefresh(w1);

    void* w2 = FindWindowByID(0x4c61b50);
    int icon2 = (int)WGetInt(w2, 0x8ed27e7a);
    WSetMaterial(w2, 2, a3);
    WSetProp((void*)icon2, 4, a3);
    WRefresh(w2);
    (void)a2;
    (void)a4;
}

// ---------------------------------------------------------------------------------------------
// Comm / relationship panel
// ---------------------------------------------------------------------------------------------
// @ 0x00e04770
// Activates the comm/relationship panel for one civ entry: rebinds the entry's two button pairs,
// pushes the entry's current value into the label colours and animates the panel fly-in.
void cSPUIGlobalUICiv::ActivateCommRelPanel(int index)
{
    CivButtonEntry* entry = (CivButtonEntry*)((char*)this + 0x8c + index * 12);
    int   icon    = entry->mIconIndex;
    void* context = entry->mpCallback;

    void* w1 = FindWindowByID(0x46977ff);
    void* child1 = WSetCallback(w1, icon, 0);

    void* w2 = FindWindowByID(0x55d626f);
    void* child2 = WSetCallback(w2, icon, 0);

    void* w3 = FindWindowByID(0x46977ff);
    void* child3 = WSetCallback(w3, icon + 0x323776, 0);

    void* w4 = FindWindowByID(0x55d626f);
    void* child4 = WSetCallback(w4, icon + 0x323776, 0);

    WSetMaterial(child2, 1, 0);
    WSetMaterial(child1, 1, 1);
    WSetMaterial(child4, 1, 1);
    WSetMaterial(child3, 1, 1);

    // Current value for the entry, mapped to a label colour.
    int value = 0;
    if (context != 0)
        value = ProgressToColor(ProgressLookup(*(int*)((char*)context + 0x40)));

    void* label1 = WGetChild(child1);
    int labelId1 = 0;
    if (label1 != 0)
        labelId1 = WGetInt(label1, 0x53eb526);
    ((void (__thiscall*)(void*, int, int))0x00831170)((void*)labelId1, 0, value);
    ((void (__thiscall*)(void*, int, int))0x00831170)((void*)labelId1, 2, value);

    void* label2 = WGetChild(child2);
    int labelId2 = 0;
    if (label2 != 0)
        labelId2 = WGetInt(label2, 0x53eb526);
    ((void (__thiscall*)(void*, int, int))0x00831170)((void*)labelId2, 0, value);
    ((void (__thiscall*)(void*, int, int))0x00831170)((void*)labelId2, 2, value);

    // Fly-in value: 0 for mode 1, 67.0f for mode 2, otherwise 100.0f.
    int mode = StateToMode(GetStateIndex(context, 0));
    float target = 100.0f;
    if (mode == 1)
        target = 0.0f;
    else if (mode == 2)
        target = 67.0f;

    void* title = WSetCallback(child1, 0x55d5429, (void*)1);
    int titleId = WGetInt(title, 0x10edf11);
    WSetFloat((void*)titleId, target);
}

// @ 0x00e04960
// Re-binds one civ entry's two button pairs, releasing the previous callback and clearing the
// entry's visible flag.
void cSPUIGlobalUICiv::UpdateButtonState(int index)
{
    CivButtonEntry* entry = (CivButtonEntry*)((char*)this + 0x8c + index * 12);
    int icon = entry->mIconIndex;

    void* w1 = FindWindowByID(0x46977ff);
    void* child1 = WSetCallback(w1, icon, 0);

    void* w2 = FindWindowByID(0x55d626f);
    void* child2 = WSetCallback(w2, icon, 0);

    if (entry->mpCallback != 0) {
        void* old = entry->mpCallback;
        entry->mpCallback = 0;
        WRelease(old);
    }

    WSetMaterial(child1, 1, 0);
    WSetMaterial(child2, 1, 0);

    void* w3 = FindWindowByID(0x46977ff);
    void* child3 = WSetCallback(w3, icon + 0x323776, 0);

    void* w4 = FindWindowByID(0x55d626f);
    void* child4 = WSetCallback(w4, icon + 0x323776, 0);

    WSetMaterial(child3, 1, 1);
    WSetMaterial(child4, 1, 1);

    entry->mbVisible = 0;
}

// @ 0x00e04aa0
// Refreshes the panel when the active player civilization changed since the last call.
void cSPUIGlobalUICiv::OnPlayerCivChanged()
{
    void* civ = ((void* (__thiscall*)(void*))0x00b25fb0)(NounManagerInstance());
    if (civ == 0)
        return;

    ((void (__thiscall*)(void*, int))0x00bf6fa0)(civ, 0);
    int id = GameTime();
    if (id == *(int*)0x015a4880)
        return;

    void* w = FindWindowByID(0xabcd1001);
    *(int*)0x015a4880 = id;
    ((void (__thiscall*)(void*, void*))0x00cfe780)(*(void**)0x0169d3c8, civ);

    cString text;
    text.Load(0xc0152a6d, 0x65f79f0, 0);
    SPUIHelpers_SetTooltipText(w, text.c_str(-1, 1));
    WRefresh(w);
}

// ---------------------------------------------------------------------------------------------
// Panel lifetime
// ---------------------------------------------------------------------------------------------
// @ 0x00e04b40
// Builds the panel: labels the title and the four civ slots, resets the entry table, registers the
// three message handlers and sets the panel title to the active planet's name.
bool cSPUIGlobalUICiv::Initialize()
{
    void* title = FindWindowByID(-1);
    if (title != 0) {
        WShow(title);
        WSetText104(title, (const char*)this + 0x70);
    }

    static const int kSlotIds[4] = { 0x5a55b10, 0x5a55b20, 0x5a55b30, 0x5a55b40 };
    for (int i = 0; i < 4; ++i) {
        void* w = FindWindowByID(kSlotIds[i]);
        if (w != 0)
            WSetText104(w, (const char*)this + 0x70);
    }

    // Reset the four entry slots and drop their old callbacks.
    for (int i = 0; i < 4; ++i) {
        CivButtonEntry* e = &mButtons[i];
        e->mIconIndex = 0x4655fd5 + i;
        e->mbFlash = 0;
        e->mbVisible = 0;
        void* cb = e->mpCallback;
        e->mpCallback = 0;
        if (cb != 0)
            WRelease(cb);
    }

    // Register the async message holder and its three handlers.
    void* holder = MessageServer();
    mpField74 = holder;
    mpField78 = this;
    mpField7C = (void*)0x15a4884;
    mField80 = 3;
    mField84 = 0;
    if (holder != 0 && this != 0) {
        for (int off = 0; off < 0xc; off += 4) {
            void* arg = *(void**)(off + 0x15a4884);
            WCall9(holder, this, arg);
        }
    }

    for (int i = 0; i < 4; ++i) {
        mButtons[i].mbFlash = 0;
        UpdateButtonState(i);
    }

    void* nameWin = FindWindowByID(0x562a0f7);
    void* nameChild = WSetCallback(nameWin, 0x562a2da, (void*)1);
    void* planet = GetActivePlanet();
    const char* name = (const char*)((void* (__thiscall*)(void*))0x00c707e0)(planet);
    name = *(const char**)name;
    WSetTitle(nameChild, name);

    if (title != 0)
        WRelease(title);
    return true;
}

// @ 0x00e04d10
// Pushes the entry's current progress value into the two paired buttons and clamps it to 0..100.
void cSPUIGlobalUICiv::SetButtonProgress(int index)
{
    CivButtonEntry* entry = (CivButtonEntry*)((char*)this + 0x8c + index * 12);
    int   icon    = entry->mIconIndex;
    void* context = entry->mpCallback;

    void* w1 = FindWindowByID(0x46977ff);
    void* child1 = WSetCallback(w1, icon, 0);

    void* w2 = FindWindowByID(0x55d626f);
    void* child2 = WSetCallback(w2, entry->mIconIndex, 0);

    if (context != 0 && *(int*)((char*)context + 0x2a0) != -1) {
        bool visible = ((bool (__thiscall*)(void*))0x00ae9f10)(
            ((void* (__thiscall*)(void*))0x00b3d4a0)(context));
        if (!visible) {
            entry->mbVisible = 1;
            FlashCivCommButton(0, child1, 0);
            FlashCivCommButton(0, child2, 0);
            goto clamp;
        }
    }

    if (entry->mbVisible != 0) {
        int c1 = (int)WGetInt(child1, 0x8ed27e7a);
        int c2 = (int)WGetInt(child2, 0x8ed27e7a);
        WSetProp((void*)c1, 8, 0);
        SPUIHelpers_SetWindowSPMaterial((void*)c1, 0x13f9c70, 0);
        WSetProp((void*)c2, 8, 0);
        SPUIHelpers_SetWindowSPMaterial((void*)c2, 0x13f9c70, 0);
        entry->mbVisible = 0;
    }

clamp:
    void* label1 = WSetCallback(child1, 0x46adf86, (void*)1);
    void* label2 = WSetCallback(child2, 0x46adf86, (void*)1);

    float value = GetProgressFloat(context, 0);
    if (value < 0.0f)
        value = 0.0f;
    if (value > 100.0f)
        value = 100.0f;

    WSetFloat(label1, value);
    WSetFloat(label2, value);
}

// @ 0x00e04f10
// Tears the panel down: resets the sub-object vptrs, nukes the tree anchor, releases the layout and
// progress bar, drops the four entry callbacks and unregisters the message handlers.
cSPUIGlobalUICiv* cSPUIGlobalUICiv::Destroy()
{
    *(void**)this = (void*)0x147f394;
    mvpField68 = (void*)0x147f384;
    mvpField70 = (void*)0x147f368;

    void* anchor = (char*)this + 0xdc;
    ((void (__thiscall*)(void*, void*))0x009a9600)(anchor, *(void**)((char*)anchor + 0xc));

    if (mpFieldC4 != 0)
        ((void (__thiscall*)(void*))(*(void***)mpFieldC4)[2])(mpFieldC4);
    if (mpProgressBarC0 != 0)
        mpProgressBarC0->Release();

    for (int i = 3; i >= 0; --i) {
        void* cb = mButtons[i].mpCallback;
        if (cb != 0)
            WRelease(cb);
    }

    if (mpField74 != 0) {
        void* handler = mpField74;
        mpField74 = 0;
        RemoveHandler(handler, mpField78, mpField7C, (void*)mField80, (void*)mField84);
    }

    mvpField70 = (void*)0x13eb938;
    mvpField68 = (void*)0x13ec458;
    // Retail tails into the base-class destructor, so its result is this function's result.
    return ((cSPUIGlobalUICiv* (__thiscall*)(void*))0x00e03b20)(this);
}

// @ 0x00e05000
// Creates the panel widgets (progress bar and layout) and initialises the four entry modes.
bool cSPUIGlobalUICiv::CreatePanel(int param)
{
    if (!((bool (__thiscall*)(void*, int, void*))0x00e03620)(this, param, this))
        return false;
    if (!Initialize())
        return false;

    void* mem = AppAllocate(0x38, (const char*)0x147f400, 0, 0, 0, 0);
    cSPUINewProgressBar* bar;
    if (mem != 0) {
        void* arg = ((void* (__thiscall*)(void*, void*))0x0093b6c0)(this, (void*)0x147f3ec);
        bar = (cSPUINewProgressBar*)((void* (__thiscall*)(void*, void*))0x00e28a10)(mem, arg);
    } else {
        bar = 0;
    }
    ((void (__thiscall*)(void**, void*))0x00572680)((void**)&mpProgressBarC0, bar);
    if (mpProgressBarC0 != 0)
        mpProgressBarC0->SetMode(0);

    void* mem2 = AppAllocate(0x18, (const char*)0x147f3cc, 0, 0, 0, 0);
    cSPUILayout* layout;
    if (mem2 != 0)
        layout = (cSPUILayout*)SPUIHelpers_ConstructLayout(mem2);
    else
        layout = 0;

    if (layout != mpFieldC4) {
        if (layout != 0)
            ((void (__thiscall*)(void*))(*(void***)layout)[1])(layout);
        cSPUILayout* old = mpFieldC4;
        mpFieldC4 = layout;
        if (old != 0)
            ((void (__thiscall*)(void*))(*(void***)old)[2])(old);
    }

    bool ok = mpFieldC4->Init((void*)0x147f3a4, 0x40464100, 1, (void*)0x5b598fa);
    if (ok)
        mpFieldC4->SetVisibility(0);

    for (int i = 0; i < 4; ++i) {
        (&mFieldC8)[i] = 0xc;
        mbFieldsD8[i] = 0;
    }
    return true;
}

// @ 0x00e05120
// Removes the panel: unregisters the handlers, clears the four labels, nukes the tree anchor,
// destroys the layout and progress bar and detaches the message holder.
void cSPUIGlobalUICiv::RemovePanel()
{
    if (mpField74 != 0) {
        void* handler = mpField74;
        mpField74 = 0;
        RemoveHandler(handler, mpField78, mpField7C, (void*)mField80, (void*)mField84);
    }

    void* w0 = FindWindowByID(-1);
    if (w0 != 0) {
        WShow(w0);
        WSetText108(w0, (const char*)this + 0x70);
    }

    static const int kSlotIds[4] = { 0x5a55b10, 0x5a55b20, 0x5a55b30, 0x5a55b40 };
    for (int i = 0; i < 4; ++i) {
        void* w = FindWindowByID(kSlotIds[i]);
        if (w != 0)
            WSetText108(w, (const char*)this + 0x70);
    }

    void* anchor = (char*)this + 0xdc;
    ((void (__thiscall*)(void*, void*))0x009a9600)(anchor, *(void**)((char*)anchor + 0xc));
    *(void**)((char*)anchor + 8) = (char*)anchor + 4;
    *(void**)((char*)anchor + 0xc) = 0;
    *(u8*)((char*)anchor + 0x10) = 0;
    *(void**)((char*)anchor + 0x14) = 0;
    *(void**)((char*)anchor + 4) = (char*)anchor + 4;

    if (mpProgressBarC0 != 0) {
        mpProgressBarC0->Shutdown();
        if (mpProgressBarC0 != 0) {
            cSPUINewProgressBar* bar = mpProgressBarC0;
            mpProgressBarC0 = 0;
            bar->Release();
        }
    }

    if (mpFieldC4 != 0) {
        mpFieldC4->Shutdown(1);
        if (mpFieldC4 != 0) {
            cSPUILayout* p = mpFieldC4;
            mpFieldC4 = 0;
            ((void (__thiscall*)(void*))(*(void***)p)[2])(p);
        }
    }

    ((void (__thiscall*)(void*))0x00e03740)(this);
}
