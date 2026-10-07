// SP::cSPUITimeline UI construction / layout setup  @ 0x00e40700  (6649 bytes, /O2).
//
// Reconstructed from the Ghidra decompile plus the 2017 Spore-ModAPI UTFWin headers
// (real virtual-slot offsets for IWindow).  Behaviorally-equivalent; NOT byte-exact
// (see nonmatching.txt).  The owning class's retail layout is larger than the 2008
// dev-PDB SP::cSPUITimeline, so a purpose-built view struct is declared below.

#include "../../include/types.h"
#include <intrin.h>

// ------------------------------------------------------------------ UTFWin model
struct Object {
    virtual int  AddRef();                 // +0x00
    virtual int  Release();                // +0x04
    virtual void scalarDeletingDtor();     // +0x08
};

struct Rect  { float x, y, z, w; };
struct Point { float x, y; };

struct IWindow : Object {
    virtual void pad0c();                              // +0x0c
    virtual IWindow* GetParent();                      // +0x10
    virtual void pad14();                              // +0x14
    virtual void pad18();                              // +0x18
    virtual void pad1c();                              // +0x1c
    virtual void pad20();                              // +0x20
    virtual void pad24();                              // +0x24
    virtual void pad28();                              // +0x28
    virtual void pad2c();                              // +0x2c
    virtual void pad30();                              // +0x30
    virtual const Rect* GetArea();                     // +0x34
    virtual const Rect* GetRealArea();                 // +0x38
    virtual void pad3c();                              // +0x3c
    virtual void pad40();                              // +0x40
    virtual void pad44();                              // +0x44
    virtual void pad48();                              // +0x48
    virtual void pad4c();                              // +0x4c
    virtual void pad50();                              // +0x50
    virtual void pad54();                              // +0x54
    virtual void pad58();                              // +0x58
    virtual void SetShadeColor(uint32_t c);            // +0x5c
    virtual void pad60();                              // +0x60
    virtual void pad64();                              // +0x64
    virtual void pad68();                              // +0x68
    virtual void SetLayoutArea(const Rect& r);         // +0x6c
    virtual void SetLayoutLocation(float x, float y);  // +0x70
    virtual void pad74();                              // +0x74
    virtual void pad78();                              // +0x78
    virtual void pad7c();                              // +0x7c
    virtual void pad80();                              // +0x80
    virtual void pad84();                              // +0x84
    virtual void pad88();                              // +0x88
    virtual void pad8c();                              // +0x8c
    virtual void pad90();                              // +0x90
    virtual void pad94();                              // +0x94
    virtual void pad98();                              // +0x98
    virtual void pad9c();                              // +0x9c
    virtual void padA0();                              // +0xa0
    virtual void padA4();                              // +0xa4
    virtual void padA8();                              // +0xa8
    virtual void padAc();                              // +0xac
    virtual void padB0();                              // +0xb0
    virtual void padB4();                              // +0xb4
    virtual void padB8();                              // +0xb8
    virtual void padBc();                              // +0xbc
    virtual Point ToGlobalCoordinates(Point p);         // +0xc0
    virtual void padC4();                              // +0xc4
    virtual void padC8();                              // +0xc8
    virtual void padCc();                              // +0xcc
    virtual void padD0();                              // +0xd0
    virtual void padD4();                              // +0xd4
    virtual void AddWindow(IWindow* w);                // +0xd8
    virtual void RemoveWindow(IWindow* w);             // +0xdc
};

struct cSPUILayout : Object {
    IWindow* FindWindowByID(uint32_t id, bool recursive);
    void     Init(const void* key, int a, uint32_t b);
    void     SetVisibility(int visible);
};

struct cSPUIPropertyLayout : cSPUILayout {
    IWindow* GetRootWindow();
};

struct cSPPaletteItemRollover : cSPUIPropertyLayout {
    virtual void Reset();                 // +0x1c
};

// eastl::vector<AutoRefCount<T> > - only the three used pointers matter here.
struct RefVec { Object** begin; Object** end; Object** cap; };

// ------------------------------------------------------------------ EA allocator
extern "C" void* EA_Alloc(uint32_t size, const char* tag, int a, int b, int c, int d);

static void* EANew(uint32_t size, const char* tag) {
    return EA_Alloc(size, tag, 0, 0, 0, 0);
}

template <class T>
static void Assign(T*& slot, T* p) {
    if (slot != p) {
        if (p)    p->AddRef();
        T* old = slot;
        slot = p;
        if (old)  old->Release();
    }
}

static void RefVecPush(RefVec* v, Object* p) {
    if (p) p->AddRef();
    if (v->end < v->cap) { *v->end++ = p; return; }
    uint32_t n = (uint32_t)(v->end - v->begin);
    uint32_t newCap = n ? n * 2 : 1;
    Object** ncap = (Object**)EANew(newCap * sizeof(Object*), "eastl vector");
    for (uint32_t i = 0; i < n; ++i) ncap[i] = v->begin[i];
    v->begin = ncap;
    v->end = ncap + n;
    v->cap = ncap + newCap;
    *v->end++ = p;
}

// ------------------------------------------------------- unnamed retail callees
void     FUN_00ddddf0(uint32_t a, int b);
void     FUN_00e3f010();
extern "C" int __stdcall QueryPerformanceCounter(int64_t* out);
uint32_t SP_ColorRGBAToU32(const void* color);        // SP::ColorRGBAToU32
void*    SP_GetPropertyAsKeyArray();                  // SP::GetPropertyAsKeyArray
void*    SP_MessageServer();                          // SP::MessageServer
void*    FUN_00685520(int mode);                      // galactic-adventures predicate
void*    FUN_0067de40();                              // HSM accessor
void     FUN_00e3e350(int a, int b, int c);
float*   SPUI_GetMainWindowArea(float* out);          // SPUIHelpers::GetMainWindowArea
void*    SPUI_CenterWindowInRect(void* mem);          // ctor used for cSPUILayout
Object*  sGetWindowImage(IWindow* w);                 // anonymous-namespace helper
void     FUN_00e462c0(void* eventRollover, void* owner); // attach rollover to window
void*    cSPUIAnimator_ctor(void* mem);               // cSPUIAnimator::cSPUIAnimator
void*    cPaletteItem_ctor(void* mem);                // FUN_005c66a0
void*    cPaletteInfo_ctor(void* mem);                // FUN_005c64e0
void*    cPaletteRollover_ctor(void* mem, int v);     // SP::cSPPaletteItemRollover
void*    cEventRollover_ctor(void* mem);              // FUN_00e46260
Object** MapFindByHash(uint32_t hash);                // FUN_00e3ec20
Object** MapFindByRef(Object* obj);                   // FUN_00ceb2b0
uint32_t* MapFindIndex(uint32_t key);                 // FUN_00de7630
void     CopyRange(int* first, int* last);            // eastl copy do_copy

// Resource-key / message-id data referenced by address.
extern "C" const char g_key_timeline[];               // DAT_015a59b8
extern "C" const char g_key_atlased[];                // DAT_015a59c4
extern "C" const char g_key_transA[];                 // DAT_015a59d0
extern "C" const char g_key_transB[];                 // DAT_015a59dc
extern "C" const char g_key_transC[];                 // DAT_015a59e8
extern "C" const uint32_t g_timelineMsgIDs[];         // DAT_01481edc (2 entries)
extern "C" int* g_appProperties;                      // _sAppProperties

struct AppPropertyList {
    virtual void pad0(); virtual void pad1(); virtual void pad2();
    virtual void pad3(); virtual void pad4(); virtual void pad5();
    virtual void pad6(); virtual void pad7(); virtual void pad8();
    virtual bool GetProperty(uint32_t id, void* out); // +0x24
};

struct MsgHandler {
    virtual void pad0(); virtual void pad1(); virtual void pad2();
    virtual void pad3(); virtual void pad4(); virtual void pad5();
    virtual void pad6(); virtual void pad7(); virtual void pad8();
    virtual void AddHandler(void* handler, uint32_t msgID); // +0x24
};

// ------------------------------------------------------------------ view object
struct TimelineView {
    virtual void Setup(); static void Dummy();

    char pad00[0x24];
    Object*       mAnimatorA;         // +0x24
    cSPUILayout*  mLayout;            // +0x28
    cSPUILayout*  mAtlasedLayout;     // +0x2c
    IWindow*      mWin30;             // +0x30
    IWindow*      mWin34;             // +0x34
    IWindow*      mWin38;             // +0x38
    IWindow*      mWin3c;             // +0x3c
    IWindow*      mWin40;             // +0x40
    IWindow*      mWin44;             // +0x44
    IWindow*      mWin48;             // +0x48
    IWindow*      mWin4c;             // +0x4c
    IWindow*      mWin50;             // +0x50
    IWindow*      mWin54;             // +0x54
    IWindow*      mWin58;             // +0x58
    char pad5c[0x10];
    Object*       mImage6c;           // +0x6c
    float mF70, mF74, mF78, mF7c;     // +0x70
    float mF80, mF84, mF88, mF8c, mF90, mF94; // +0x80
    char pad98[0x10];
    uint32_t mTimeLo, mTimeHi;        // +0xa8
    uint32_t mB0, mB4;                // +0xb0
    uint32_t mMode;                   // +0xb8
    char padbc[0xb0];                 // ..+0x16c
    RefVec   mPropVec;                // +0x16c
    char pad174[0x50];                // ..+0x1c4
    Object*  mPaletteItem;            // +0x1c4
    Object*  mPaletteInfo;            // +0x1c8
    Object*  mPaletteRollover;        // +0x1cc
    Object*  mEventRollover;          // +0x1d0
    char pad1d4[0x0c];
    char     mColor1e0[0x20];         // +0x1e0
    char     mColor200[0x20];         // +0x200
    char     mColor220[0x20];         // +0x220
    char pad240[0xec];                // ..+0x32c
    void*    mMsgServer;              // +0x32c
    void*    mMsgHandler;             // +0x330
    const uint32_t* mMsgIDs;          // +0x334
    uint32_t mMsgCount;               // +0x338
    uint32_t mMsgState;               // +0x33c
    cSPUILayout* mTransitionLayout;   // +0x340
    cSPUILayout* mTransitionLayout2;  // +0x344
    char pad348[0x24];
    IWindow* mWin36C[10];             // +0x36c
    IWindow* mWin394[10];             // +0x394
    char pad3bc[4];
    IWindow* mWin3C0[10];             // +0x3c0
    char pad3e8[0x68];
    Object*  mAnimatorB;              // +0x450
    char pad454[4];
    RefVec   mVec458;                 // +0x458
    char pad460[0xc];
    RefVec   mVec46c;                 // +0x46c
    char pad474[0xc];
    uint32_t mTileCount;              // +0x480
    bool     mFlag484;                // +0x484

    void SetupIconStrip();
    void SetupColorWindows();
    void SetupIconPairs();
    void SetupPalette();
    void SetupTrackRows();
    void RegisterMessages();
};

void TimelineView::Dummy() {}

// @ 0x00e40700
void TimelineView::Setup() {
    FUN_00ddddf0(0x8c509d6c, 0);

    mAnimatorA = (Object*)cSPUIAnimator_ctor(EANew(0x20, "UI/cUITimeline/Animator"));

    if (g_appProperties != 0) {
        int64_t tmp = 0;
        char ok = ((AppPropertyList*)g_appProperties)->GetProperty(0x064a44a8, &tmp);
        if (ok && *(int16_t*)((int)tmp + 0x12) == 1)
            mFlag484 = *(uint8_t*)SP_GetPropertyAsKeyArray() != 0;
    }

    mAnimatorB = (Object*)cSPUIAnimator_ctor(EANew(0x20, "UI/cUITimeline/Animator"));

    CopyRange((int*)mVec458.begin, (int*)mVec458.end);
    CopyRange((int*)mVec46c.begin, (int*)mVec46c.end);

    if (!mFlag484) {
        mTileCount = 1;
    } else {
        float a[8];
        SPUI_GetMainWindowArea(a);
        int height = (int)(a[3] - a[1]);
        float b[8];
        SPUI_GetMainWindowArea(b);
        mTileCount = (b[2] - b[0] <= (float)height * 1.3333334f) ? 8 : 10;
    }

    FUN_00e3f010();
    if (*(int*)((char*)this + 0xb8) == 1) {
        uint64_t t = __rdtsc();
        mTimeLo = (uint32_t)t;
        mTimeHi = (uint32_t)(t >> 32);
    } else {
        int64_t qpc = 0;
        QueryPerformanceCounter(&qpc);
        mTimeLo = (uint32_t)qpc;
        mTimeHi = (uint32_t)(qpc >> 32);
    }
    mB0 = 0;
    mB4 = 0;

    Assign(mLayout, (cSPUILayout*)SPUI_CenterWindowInRect(
                        EANew(0x18, "UI/cUITimeline/mTimelineLayout")));
    mLayout->Init(g_key_timeline, 1, 0x8c509d6c);

    Assign(mAtlasedLayout, (cSPUILayout*)SPUI_CenterWindowInRect(
                               EANew(0x18, "UI/cUITimeline/mAtlasedIconsLayout")));
    mAtlasedLayout->Init(g_key_atlased, 1, 0x8c509d6c);
    mAtlasedLayout->SetVisibility(0);

    Assign(mWin30, mLayout->FindWindowByID(0xffffffff, true));
    Assign(mWin34, mLayout->FindWindowByID(0x54e504cd, true));
    Assign(mWin38, mLayout->FindWindowByID(0x54e53d9d, true));
    Assign(mWin3c, mLayout->FindWindowByID(0xf54a5ddc, true));
    Assign(mWin40, mLayout->FindWindowByID(0xd5543432, true));
    Assign(mWin4c, mLayout->FindWindowByID(0x06134392, true));
    Assign(mWin50, mLayout->FindWindowByID(0x75120794, true));
    Assign(mWin54, mLayout->FindWindowByID(0x061f0640, true));
    Assign(mWin58, mLayout->FindWindowByID(0x06119986, true));

    if (mWin58) {
        Point org; org.x = 0.0f; org.y = 0.0f;
        Point p = mWin58->ToGlobalCoordinates(org);
        mF70 = p.x;
        mF74 = p.y;
        const Rect* r = mWin58->GetRealArea();
        mF78 = r->x;
        mF7c = r->y;
    }
    if (mWin54) {
        Point org; org.x = 0.0f; org.y = 0.0f;
        Point p = mWin54->ToGlobalCoordinates(org);
        mF80 = p.x;
        mF84 = p.y;
    }

    IWindow* w = mLayout->FindWindowByID(0x064178c8, true);
    if (w) {
        const Rect* r = w->GetRealArea();
        mF88 = r->x;
        mF8c = r->y;
    }
    w = mLayout->FindWindowByID(0x064178d0, true);
    if (w) {
        const Rect* r = w->GetRealArea();
        mF90 = r->x;
        mF94 = r->y;
    }

    w = mLayout->FindWindowByID(0x75581f48, true);
    if (w)
        Assign(mImage6c, sGetWindowImage(w));

    SetupIconStrip();
    SetupColorWindows();
    SetupIconPairs();

    // register "find window by hash" slots (cell/creature/tribe/civ/space image sets)
    {
        static const uint32_t kHashes[5] = {
            0xa426730b, 0xad56080c, 0xf71fa311, 0xbeb528cb, 0x2db6dad3 };
        static const uint32_t kWindowIDs[5] = {
            0x74ed2970, 0x74ed2971, 0x74ed2972, 0x74ed2973, 0x74ed2974 };
        for (int i = 0; i < 5; ++i)
            Assign(*MapFindByHash(kHashes[i]),
                   (Object*)mLayout->FindWindowByID(kWindowIDs[i], true));
        uint32_t* z = MapFindIndex(0);
        *z = 0;
        for (int i = 0; i < 5; ++i)
            *MapFindIndex(kHashes[i]) = (uint32_t)(i + 1);
    }

    // icon strip: pair a control window with its detail window in a lookup
    {
        static const uint32_t kKey[5]   = { 0x74ed2970, 0x74ed2971, 0x74ed2972, 0x74ed2973, 0x74ed2974 };
        static const uint32_t kIconA[5] = { 0xb54a5880, 0xb54a5881, 0xb54a5882, 0xb54a5883, 0xb54a5884 };
        static const uint32_t kIconB[5] = { 0x60be2e0, 0x60be2e1, 0x60be2e2, 0x60be2e3, 0x60be2e4 };
        for (int i = 0; i < 5; ++i) {
            Object* key = (Object*)mLayout->FindWindowByID(kKey[i], true);
            if (key) key->AddRef();
            Assign(*MapFindByRef(key), (Object*)mLayout->FindWindowByID(kIconA[i], true));
            if (key) key->Release();
        }
        for (int i = 0; i < 5; ++i) {
            Object* img = (Object*)mLayout->FindWindowByID(kIconA[i], true);
            RefVecPush(&mPropVec, img);
            if (img) img->Release();
        }
        for (int i = 0; i < 5; ++i) {
            Object* key = (Object*)mLayout->FindWindowByID(kKey[i], true);
            if (key) key->AddRef();
            Assign(*MapFindByRef(key), (Object*)mLayout->FindWindowByID(kIconB[i], true));
            if (key) key->Release();
        }
        for (int i = 0; i < 5; ++i) {
            Object* key = (Object*)mLayout->FindWindowByID(kIconB[i], true);
            if (key) key->AddRef();
            Assign(*MapFindByRef(key), (Object*)mLayout->FindWindowByID(kKey[i], true));
            if (key) key->Release();
        }
    }

    // place the five event windows along the strip
    for (uint32_t id = 0x60be2e0; id < 0x60be2e5; ++id) {
        IWindow* win = mLayout->FindWindowByID(id, true);
        if (!win) continue;
        IWindow* parent = win->GetParent();
        if (!parent) continue;
        const Rect* pr = parent->GetRealArea();
        const Rect* r  = win->GetRealArea();
        float width = r->z - r->x;
        float slot = (float)(int)(id - 0x60be2e0) * 0.2f;
        float x = slot * width + 3.0f;
        if (id == 0x60be2e0) x += 3.0f;
        float y = (slot + 0.2f) * width - 3.0f;
        if (id == 0x60be2e4) y -= 3.0f;
        (void)pr;
        win->SetLayoutLocation(x, y);
    }

    SetupPalette();
    SetupTrackRows();
    RegisterMessages();
}

// @ icons + their frames (0x00e41110 region of the original)
void TimelineView::SetupIconStrip() {
    IWindow* a = mLayout->FindWindowByID(0x61388da, true);
    IWindow* b = mLayout->FindWindowByID(0x61388db, true);
    if (!a || !b) return;

    IWindow* parent = a->GetParent();
    if (!parent) return;
    int ph = (int)(parent->GetRealArea()->w - parent->GetRealArea()->y);

    const Rect* ar = a->GetRealArea();
    float ay0 = (float)ph * 0.33333334f - (ar->w - ar->y) * 0.5f;
    Rect ao = { ar->x, ay0, ar->z, ay0 + (ar->w - ar->y) };
    a->SetLayoutArea(ao);

    const Rect* br = b->GetRealArea();
    float by0 = (float)ph * 0.6666667f - (br->w - br->y) * 0.5f;
    Rect bo = { br->x, by0, br->z, by0 + (br->w - br->y) };
    b->SetLayoutArea(bo);
}

// @ colored event markers (0x00e412a0 region)
void TimelineView::SetupColorWindows() {
    IWindow* a = mLayout->FindWindowByID(0xf537d890, true);
    IWindow* b = mLayout->FindWindowByID(0xf537d891, true);
    IWindow* c = mLayout->FindWindowByID(0xf537d892, true);
    if (!a || !b || !c) return;

    const Rect* ar = a->GetRealArea();
    Rect ao = { ar->x, ar->y, ar->z, (ar->w + ar->y) * 0.5f };
    a->SetLayoutArea(ao);
    a->SetShadeColor(SP_ColorRGBAToU32(mColor1e0));

    const Rect* br = b->GetRealArea();
    Rect bo = { br->x, br->y, br->z, (br->w + br->y) * 0.5f };
    b->SetLayoutArea(bo);
    b->SetShadeColor(SP_ColorRGBAToU32(mColor200));

    const Rect* cr = c->GetRealArea();
    Rect co = { cr->x, cr->y, cr->z, cr->w };
    c->SetLayoutArea(co);
    c->SetShadeColor(SP_ColorRGBAToU32(mColor220));
}

// @ 0x00e41480 region onwards: palette objects + event rollover + transitions
void TimelineView::SetupPalette() {
    Assign(mPaletteItem,   (Object*)cPaletteItem_ctor(EANew(0x54, "UI/cUITimeline/mPaletteItem")));
    Assign(mPaletteInfo,   (Object*)cPaletteInfo_ctor(EANew(0x34, "UI/cUITimeline/mPaletteInfo")));
    Assign(mPaletteRollover, (Object*)cPaletteRollover_ctor(
                                 EANew(0xc8, "UI/cUITimeline/mPaletteItemRollover"), 1));
    if (mPaletteRollover)
        ((cSPPaletteItemRollover*)mPaletteRollover)->Reset();

    IWindow* root = ((cSPUIPropertyLayout*)mPaletteRollover)->GetRootWindow();
    if (root) {
        IWindow* parent = root->GetParent();
        if (parent && mWin30) {
            parent->RemoveWindow(root);
            mWin30->AddWindow(root);
        }
    }

    Assign(mEventRollover, (Object*)cEventRollover_ctor(
                               EANew(0x88, "UI/cUITimeline/mTimelineEventRollover")));
    FUN_00e462c0(mWin30, mEventRollover);

    mLayout->SetVisibility(0);

    cSPUILayout* t = (cSPUILayout*)SPUI_CenterWindowInRect(
                         EANew(0x18, "UI/cUITimeline/mTransitionLayout"));
    Assign(mTransitionLayout, t);
    mTransitionLayout->Init(mFlag484 ? g_key_transB : g_key_transA, 1, 0x5b598f7);

    if (!FUN_00685520(2)) {
        Assign(mTransitionLayout2, (cSPUILayout*)0);
    } else {
        cSPUILayout* t2 = (cSPUILayout*)SPUI_CenterWindowInRect(
                              EANew(0x18, "UI/cUITimeline/mTransitionLayout"));
        Assign(mTransitionLayout2, t2);
        mTransitionLayout2->Init(g_key_transC, 1, 0x5b598f7);
    }

    FUN_00e3e350(0, 0xffffffff, 0);
}

// @ 0x00e41faf: ten rows of the transition layout, each a pair of windows
void TimelineView::SetupTrackRows() {
    if (!mTransitionLayout) return;
    for (int i = 0; i < 10; ++i) {
        uint32_t rowID = 0x6314188 + i;
        uint32_t cellID = 0x64dce90 + i;
        Assign(mWin36C[i], mTransitionLayout->FindWindowByID(rowID, true));
        if (mFlag484)
            Assign(mWin394[i], mTransitionLayout->FindWindowByID(cellID, true));
        Assign(mWin3C0[i], (IWindow*)0);
    }
}

// @ 0x00e42078: register with the message server and an HSM
void TimelineView::RegisterMessages() {
    mMsgServer  = SP_MessageServer();
    mMsgHandler = (char*)this - 8;
    mMsgIDs     = g_timelineMsgIDs;
    mMsgCount   = 2;
    mMsgState   = 0;
    if (mMsgServer && mMsgHandler) {
        MsgHandler* h = (MsgHandler*)mMsgServer;
        for (uint32_t off = 0; off < 8; off += 4)
            h->AddHandler(mMsgHandler, *(const uint32_t*)((const char*)g_timelineMsgIDs + off));
    }

    void* sub = (this == 0) ? 0 : (char*)this + 0x1c;
    void* hsm = FUN_0067de40();
    void** vt = *(void***)hsm;
    hsm = ((void*(*)(void*))vt[8])(hsm);          // vtable +0x20
    ((void(*)(void*, void*))vt[7])(hsm, sub);     // vtable +0x1c
}
