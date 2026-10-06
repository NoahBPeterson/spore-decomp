// Slice s006515a0 -- cSPUIAssetGrid asset-entry heap helpers + grid ctor/dtor/layout methods.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <intrin.h>

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* lpPerformanceCount);

// ---------------------------------------------------------------------------
// Refcounted interface pieces
// ---------------------------------------------------------------------------
struct IRefCount { virtual int AddRef(); virtual int Release(); };
struct EntryPrimary { virtual void v(); char pad0[0xc]; };
struct EntryView : EntryPrimary, IRefCount {};   // IRefCount at +0x10
struct EntryData : IRefCount {};

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount&);
    void Set(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
    }
};

struct GridEntry {
    void* m00;                       // +0x00
    void* m04;                       // +0x04
    void* m08;                       // +0x08
    AutoRefCount<EntryView> m0c;     // +0x0c
    AutoRefCount<EntryData> m10;     // +0x10
    float m14;                       // +0x14
    float m18;                       // +0x18
    bool  m1c;                       // +0x1c
    bool  m1d;                       // +0x1d
    GridEntry() {}
    GridEntry& operator=(const GridEntry&);   // 0x0064f450
};

struct CompareA {                 // 0x0064ff90: two entries BY VALUE
    bool operator()(GridEntry a, GridEntry b) const;
};
struct TypeGridEntrySort {        // 0x0066a830: two entries BY REFERENCE
    bool operator()(const GridEntry& a, const GridEntry& b) const;
};

// ---------------------------------------------------------------------------
// EASTL heap/median primitives on GridEntry
// ---------------------------------------------------------------------------
namespace eastl {

// @ 0x006515a0
template <typename T, typename Compare>
__declspec(noinline) const T& median(const T& a, const T& b, const T& c, Compare compare) {
    if (compare(a, b)) {
        if (compare(b, c)) return b;
        else if (compare(a, c)) return c;
        else return a;
    } else if (compare(a, c)) return a;
    else if (compare(b, c)) return c;
    return b;
}

// defined in slice s0064eb60 (@ 0x0064f990)
template <typename It, typename Distance, typename T, typename Compare>
void promote_heap_ref(It first, Distance topPosition, Distance position, T value, Compare& compare);

// @ 0x006516a0
template <typename It, typename Distance, typename T, typename Compare>
__declspec(noinline) void adjust_heap_ref(It first, Distance topPosition, Distance heapSize,
                                          Distance position, T value, Compare& compare) {
    Distance childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    eastl::promote_heap_ref<It, Distance, T, Compare>(first, topPosition, position, value, compare);
}

// @ 0x00651910
template <typename It, typename Compare>
__declspec(noinline) void pop_heap_ref(It first, It last, Compare& compare) {
    const GridEntry tempBottom(*(last - 1));
    *(last - 1) = *first;
    eastl::adjust_heap_ref<It, int, GridEntry, Compare>(first, 0, (int)(last - first - 1), 0,
                                                        tempBottom, compare);
}

// @ 0x006517c0
template <typename It, typename Distance, typename T, typename Compare>
__declspec(noinline) void promote_heap(It first, Distance topPosition, Distance position, T value,
                                       Compare compare) {
    for (Distance parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}

template const GridEntry& median<GridEntry, CompareA>(const GridEntry&, const GridEntry&, const GridEntry&, CompareA);
template void adjust_heap_ref<GridEntry*, int, GridEntry, TypeGridEntrySort>(GridEntry*, int, int, int, GridEntry, TypeGridEntrySort&);
template void pop_heap_ref<GridEntry*, TypeGridEntrySort>(GridEntry*, GridEntry*, TypeGridEntrySort&);
template void promote_heap<GridEntry*, int, GridEntry, CompareA>(GridEntry*, int, int, GridEntry, CompareA);

}  // namespace eastl

// ---------------------------------------------------------------------------
// UI window/layout interfaces (vtable slots as used by this slice)
// ---------------------------------------------------------------------------
struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(float ax, float ay) : x(ax), y(ay) {}
    Vec2(const Vec2& o) : x(o.x), y(o.y) {}
};
struct Rect {
    float l, t, r, b;
    float Width() const { return r - l; }
};

struct IWin {                                    // generic refcounted UI window
    virtual int AddRef();                        // 0x00
    virtual int Release();                       // 0x04
};
struct IWindow : IWin {
    virtual void v08(); virtual void v0c();
    virtual IWindow* GetParent();                // 0x10
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34();
    virtual Rect* GetArea();                     // 0x38
    virtual void v3c();
    virtual int GetAreaBottomInt();              // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68();
    virtual void SetArea(const Rect* r);         // 0x6c
    virtual void v70();
    virtual void SetSize(float w, float h);      // 0x74
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual Vec2* ConvertPoint(Vec2* out, Vec2 pt);   // 0xc4
    virtual void vc8(); virtual void vcc(); virtual void vd0(); virtual void vd4();
    virtual void SetParentWin(IWindow* w);       // 0xd8
    virtual void SetPoint(IWindow* w);           // 0xdc
};
struct ILayout {                                 // AddRef at slot 1 (+4), Release at slot 2 (+8)
    virtual void v00();
    virtual int AddRef();
    virtual int Release();
    void Init(void* key, int a, unsigned int b);                       // @ 0x8120d0
    void SetParentWin(IWindow* w, int a, unsigned int b);              // @ 0x8120b0
    void SetReloadCallback(void* cb, void* ctx);                       // @ 0x810090
};
struct AssetView {                               // UI::AssetDiscovery_View (0x108 bytes)
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Attach(IWindow* w, int a, int b, int c);              // 0x1c
    virtual void Detach();                                              // 0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void Layout(int a, int b);                                  // 0x30
    float GetHeight();                                                  // @ 0x6578d0
    float GetWidth();                                                   // @ 0x6578f0
};
struct IMsgServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void AddHandler(void* handler, unsigned int id);            // 0x24
};
struct IAppSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c();
    virtual void SetFlag(int v);                                        // 0x40
};

struct IWinScrollbar : IWin {
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual int GetMax();                        // 0x38
    virtual void v3c();
    virtual int GetMin();                        // 0x40
};
struct ScrollFrame : IWin {                      // object held in w18c
    char pad4[0x14];
    IWindow* mArea;                              // +0x18
    char pad1c[4];
    IWinScrollbar* mScrollbar;                   // +0x20
    void UpdateVertical(int a);                  // @ 0x82a500 (SPUIHelpers::UpdateScrollFrameVertical)
};

extern "C" void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern "C" void  EASTL_allocator_deallocate(void* p);                   // 0xf47380
IAppSystem* AppSystem();                                                // @ 0x67dd00
IMsgServer* MessageServer();                                            // @ 0x67dcc0
void RemoveHandler(IMsgServer* server, void* handler, const unsigned int* ids, int count, int x); // @ 0x571db0
void __cdecl GetBoundingScreenRect(Rect* out, IWindow* w, int flags);   // @ 0x808d20
AssetView* __fastcall AssetView_ctor(void* mem);                        // @ 0x657f70 (thiscall)
ILayout* __fastcall Layout_ctor(void* mem);                             // @ 0x810000 (thiscall)
extern unsigned int g_layoutKeyId;                                      // 0x01525e7c
extern const char g_assetViewName[];                                    // 0x013f6b3c
extern const unsigned int g_msgIds[3];                                  // 0x013ffaec

// ---------------------------------------------------------------------------
// EA::Stopwatch (24 bytes): start tick / elapsed, mode at +0x10
// ---------------------------------------------------------------------------
struct Stopwatch {
    unsigned long long mStart;      // +0x00
    unsigned long long mElapsed;    // +0x08
    int mMode;                      // +0x10
    int mUnits;                     // +0x14
    Stopwatch(int units, int a);                                         // @ 0x93a560
    void Start() {
        unsigned long long t;
        if (mMode == 1) t = __rdtsc();
        else QueryPerformanceCounter((long long*)&t);
        mStart = t;
        mElapsed = 0;
    }
};

// ---------------------------------------------------------------------------
// SP::cSPUIAssetGrid (retail layout, only what this slice touches)
// ---------------------------------------------------------------------------
struct GridVec {
    GridEntry* mpBegin;
    GridEntry* mpEnd;
    GridEntry* mpCapacity;
    GridVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoDestroyValues(GridEntry* first, GridEntry* last);             // @ 0x0064f410
    ~GridVec() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && ((unsigned*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
};

struct AutoHandler {                 // EA::Messaging::AutoHandler
    IMsgServer* mpServer;
    void* mpHandler;
    const unsigned int* mpIdArray;
    int mCount;
    int mX;
    AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mCount(0), mX(0) {}
    ~AutoHandler() {
        if (mpServer) {
            IMsgServer* s = mpServer;
            void* h = mpHandler; const unsigned int* ids = mpIdArray; int n = mCount; int x = mX;
            mpServer = 0;
            RemoveHandler(s, h, ids, n, x);
        }
    }
};

struct GB0 { virtual ~GB0() {} virtual void b0f1(); };
struct GB1 { virtual ~GB1() {} virtual void b1f1(); };
struct GB2 { virtual void b2f0(); virtual void b2f1(); };
struct GB3 { GB3() : mRefCount(0) {} virtual ~GB3() {} int mRefCount; };

struct cSPUIAssetGrid : GB0, GB1, GB2, GB3 {
    // GB0 @0, GB1 @4, GB2 @8, GB3 @0xc (mRefCount @0x10)
    bool mIsVisible;                              // +0x14
    AutoRefCount<ILayout> mLayout;                // +0x18
    AutoRefCount<IWin> w1c;
    AutoRefCount<IWindow> w20;
    AutoRefCount<IWindow> w24;
    AutoRefCount<IWin> w28;
    AutoRefCount<IWindow> w2c;
    AutoRefCount<IWin> w30, w34, w38, w3c, w40, w44;
    AutoRefCount<IWindow> w48;
    AutoRefCount<IWindow> w4c;
    AutoRefCount<IWin> w50,
                       w54, w58, w5c, w60, w64, w68, w6c, w70, w74, w78, w7c;
    AutoRefCount<IWin> mWinArray[24];             // +0x80
    AutoRefCount<IWin> we0;                       // +0xe0
    AutoRefCount<IWin> we4;                       // +0xe4
    GridVec mGridEntries;                         // +0xe8
    unsigned int padF4[2];                        // +0xf4
    unsigned int mFC;                             // +0xfc
    bool m100;                                    // +0x100
    float m104, m108;                             // +0x104
    bool m10c;                                    // +0x10c
    int m110, m114;                               // +0x110
    float m118, m11c, m120, m124, m128, m12c, m130, m134;   // +0x118
    AutoHandler mHandler;                         // +0x138
    unsigned int pad14c;                          // +0x14c
    Stopwatch mTimerA;                            // +0x150
    Stopwatch mTimerB;                            // +0x168
    float m180, m184, m188;                       // +0x180
    AutoRefCount<ScrollFrame> w18c;               // +0x18c
    bool m190;                                    // +0x190
    int m194, m198;                               // +0x194
    AutoRefCount<IWin> w19c;                      // +0x19c
    int m1a0, m1a4;                               // +0x1a0
    int m1a8, m1ac, m1b0, m1b4;                   // +0x1a8
    bool m1b8, m1b9, m1ba, m1bb;                  // +0x1b8
    unsigned int pad1bc;                          // +0x1bc
    AutoRefCount<IWin> w1c0;                      // +0x1c0
    int m1c4, m1c8, m1cc;                         // +0x1c4
    unsigned int pad1d0[5];                       // +0x1d0
    bool m1e4, m1e5, m1e6, m1e7, m1e8;            // +0x1e4

    cSPUIAssetGrid();                             // @ 0x00651990
    ~cSPUIAssetGrid();                            // @ 0x00651c80
    void SetupWindows(IWindow* a, IWindow* b, IWindow* c);   // @ 0x00651ff0
    void UpdateScrollRegion();                    // @ 0x006524a0
    static void __cdecl ReloadCallback(cSPUIAssetGrid* self, ILayout* l, int flag);   // @ 0x650630
    void ComputeCardLayoutParameters();           // @ 0x650020
    void UpdateScrolling(int a);                  // @ 0x64fa20
    void FUN_650470();                            // @ 0x650470
    void FUN_66bd00();                            // @ 0x66bd00
    void FUN_64e5d0(int rows, float* out);        // @ 0x64e5d0
};

// @ 0x00651990
cSPUIAssetGrid::cSPUIAssetGrid()
    : mIsVisible(false),
      mFC(0), m100(false), m104(0.0f), m108(0.0f), m10c(false), m110(0), m114(0),
      m118(0.0f), m11c(0.0f), m120(0.0f), m124(0.0f), m128(0.0f), m12c(0.0f), m130(0.0f), m134(0.0f),
      mTimerA(4, 0), mTimerB(4, 0),
      m180(0.0f), m184(0.0f), m188(0.0f), m190(false), m194(1), m198(1),
      m1a0(0x18), m1a4(1), m1a8(0), m1ac(0), m1b0(0), m1b4(0),
      m1b8(false), m1b9(false), m1ba(false), m1bb(false),
      m1c4(0), m1c8(0), m1cc(0),
      m1e4(false), m1e5(false), m1e6(false), m1e7(false), m1e8(false)
{
}

// @ 0x00651c80
cSPUIAssetGrid::~cSPUIAssetGrid()
{
    if (m10c) {
        AppSystem()->SetFlag(0);
        m10c = false;
    }
}

// @ 0x00651f30  (called with this = the GB2 subobject at +8, so fields are shifted by -8)
struct GridSub8 {
    char pad0[0x24];
    IWindow* w24;                  // full +0x2c
    char pad28[0xe0 - 0x28];
    GridEntry* mpBegin;            // full +0xe8
    GridEntry* mpEnd;              // full +0xec
    char padE8[0x100 - 0xe8];
    float m100;                    // full +0x108
    char pad104[0x114 - 0x104];
    float m114;                    // full +0x11c
    char pad118[0x120 - 0x118];
    float m120;                    // full +0x128
    char pad124[0x1a4 - 0x124];
    int m1a4;                      // full +0x1ac
    int m1a8;                      // full +0x1b0
    float ContentHeight(float width);
};

float GridSub8::ContentHeight(float width)
{
    if (mpBegin == mpEnd)
        return 0.0f;
    Rect* r = w24->GetArea();
    float top = r->t;
    float bottom = r->b;
    w24->SetSize(width, bottom - top);
    cSPUIAssetGrid* g = (cSPUIAssetGrid*)((char*)this - 8);
    g->ComputeCardLayoutParameters();
    int across = m1a8;
    int rows = across - 1;
    ScrollFrame* f = (ScrollFrame*)g->w19c.mpObject;
    bool cond;
    if (f == 0)
        cond = g->m1b8;
    else
        cond = g->m1b8 && *((char*)f + 0x16);
    if (cond) rows++;
    if (across != m1a4) rows++;
    float t[2];
    g->FUN_64e5d0(rows, t);
    return m120 + m114 + m100 + t[1];
}

// @ 0x00651ff0
void cSPUIAssetGrid::SetupWindows(IWindow* a, IWindow* b, IWindow* c)
{
    FUN_66bd00();
    w1c.Set((IWin*)a);
    w20.Set(b);
    w24.Set(c);

    void* mem = EASTL_allocator_allocate(0x108, g_assetViewName, 0, 0, 0, 0);
    AssetView* view = mem ? AssetView_ctor(mem) : 0;
    if (view) view->AddRef();
    view->Attach((IWindow*)w1c.mpObject, 0, 0, 0);
    view->Layout(0, 0);
    m108 = view->GetHeight();
    m104 = view->GetWidth();
    view->Detach();
    view->Release();

    void* lmem = EASTL_allocator_allocate(0x18, "Sporepedia", 0, 0, 0, 0);
    ILayout* layout = lmem ? Layout_ctor(lmem) : 0;
    mLayout.Set(layout);
    unsigned int key[3];
    key[0] = g_layoutKeyId;
    key[1] = 0xd525562b;
    key[2] = 0x510a95b;
    mLayout.mpObject->Init(key, 1, 0x5b598fa);
    mLayout.mpObject->SetParentWin((IWindow*)w1c.mpObject, 1, 0x5b598fa);
    mLayout.mpObject->SetReloadCallback((void*)ReloadCallback, this);
    ReloadCallback(this, mLayout.mpObject, 1);

    if (w48.mpObject && w20.mpObject) {
        Rect rc;
        GetBoundingScreenRect(&rc, w48.mpObject, 0);
        w48.mpObject->GetParent()->SetPoint(w48.mpObject);
        w20.mpObject->SetParentWin(w48.mpObject);
        Vec2 o1, o2;
        Vec2 p2(rc.r, rc.b);
        Vec2* r1 = w20.mpObject->ConvertPoint(&o1, Vec2(rc.l, rc.t));
        float x1 = r1->x, y1 = r1->y;
        Vec2* r2 = w20.mpObject->ConvertPoint(&o2, p2);
        rc.l = x1; rc.t = y1; rc.r = r2->x; rc.b = r2->y;
        w48.mpObject->SetArea(&rc);
    }
    if (w4c.mpObject && w24.mpObject) {
        Rect rc;
        GetBoundingScreenRect(&rc, w4c.mpObject, 0);
        w4c.mpObject->GetParent()->SetPoint(w4c.mpObject);
        w24.mpObject->SetParentWin(w4c.mpObject);
        Vec2 o1, o2;
        Vec2 p2(rc.r, rc.b);
        Vec2* r1 = w24.mpObject->ConvertPoint(&o1, Vec2(rc.l, rc.t));
        float x1 = r1->x, y1 = r1->y;
        Vec2* r2 = w24.mpObject->ConvertPoint(&o2, p2);
        rc.l = x1; rc.t = y1; rc.r = r2->x; rc.b = r2->y;
        w4c.mpObject->SetArea(&rc);
    }

    mTimerA.Start();
    mTimerB.Start();

    void* handler = (char*)this + 4;
    IMsgServer* server = MessageServer();
    mHandler.mpServer = server;
    mHandler.mpHandler = handler;
    mHandler.mpIdArray = g_msgIds;
    mHandler.mCount = 3;
    mHandler.mX = 0;
    if (server && handler) {
        for (unsigned int i = 0; i < 0xc; i += 4)
            server->AddHandler(handler, *(const unsigned int*)((const char*)g_msgIds + i));
    }
}

// @ 0x006524a0
void cSPUIAssetGrid::UpdateScrollRegion()
{
    if (w18c.mpObject && w2c.mpObject) {
        Rect* p = w2c.mpObject->GetArea();
        Rect rc;
        rc.l = p->l; rc.t = p->t; rc.r = p->r; rc.b = p->b;
        w18c.mpObject->UpdateVertical(0);
        IWinScrollbar* sb = w18c.mpObject->mScrollbar;
        int hi = sb->GetMax();
        int lo = sb->GetMin();
        m188 = (float)(hi - lo);
        Rect* q = w18c.mpObject->mArea->GetArea();
        rc.r = q->Width() + q->l;
        w2c.mpObject->SetArea(&rc);
    }
    UpdateScrolling(0);
    FUN_650470();
}
