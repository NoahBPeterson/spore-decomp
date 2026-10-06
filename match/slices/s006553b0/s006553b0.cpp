// slice s006553b0: SP::cSPUIAssetGrid asset-state refresh / key lookup / feed load / per-frame update.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <intrin.h>
#include <math.h>

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* lpPerformanceCount);

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

// ---------------------------------------------------------------------------
// Basic types
// ---------------------------------------------------------------------------
struct Key {                           // EA::ResourceMan::Key (instance, type, group)
    int a, b, c;
};
struct Rect { float l, t, r, b; };
struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(float ax, float ay) : x(ax), y(ay) {}
    Vec2(const Vec2& o) : x(o.x), y(o.y) {}
};

struct IRefCount { virtual int AddRef(); virtual int Release(); };

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void Reset()
    {
        T* old = mpObject;
        if (old) {
            mpObject = 0;
            old->Release();
        }
    }
};

// ---------------------------------------------------------------------------
// Objects referenced by the grid
// ---------------------------------------------------------------------------
struct AssetDataPrimary {              // primary vtable of a cached asset record; IRefCount sub-object at +0x10
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool IsReady();                    // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual const Key* GetKey();               // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c();
    virtual bool PassesFilterC();              // 0x60
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual bool PassesFilterB();              // 0x74
    virtual bool PassesFilterA();              // 0x78
    virtual void v7c(); virtual void v80();
    virtual bool IsHidden();                   // 0x84
    char pad0[0xc];
};
struct AssetData : AssetDataPrimary, IRefCount {};

struct AssetView {                             // UI::AssetDiscovery_View
    virtual int AddRef();                      // 0x00
    virtual int Release();                     // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Attach(void* win, AssetData* data, int a, int b);   // 0x1c
    virtual void v20();
    virtual void OnUpdate(int arg, bool flag); // 0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void SetEnabled(bool enabled);     // 0x38
    char pad04[0xf4 - 4];
    bool mSelectable;                          // +0xf4
    void SetPos(Vec2 pos, bool flag);          // 0x00658e00
    void SelectAsset(int a, bool b, const Rect* rc, int c, int d);   // 0x00657a30
    void Destroy();                            // 0x00659340
};
struct FcObj {                                 // object pointed to by the grid's +0xfc member
    char pad0[0x10];
    AssetView* mpView;                         // +0x10
};

struct IWindow {
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void SetPos(float x, float y);     // 0x64
    virtual void SetSize(float w, float h);    // 0x68
    virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetVisible(bool a, bool b);   // 0x7c
    virtual void SetText(const wchar_t* text); // 0x80
};
struct IScrollbar {
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual int GetMin();                      // 0x40
};
struct ScrollFrame {
    virtual int AddRef(); virtual int Release();
    char pad4[0x1c];
    IScrollbar* mScrollbar;                    // +0x20
};
struct IAppSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c();
    virtual void SetFlag(int v);               // 0x40
};
struct IMsg {
    virtual void v00();
    virtual int AddRef();                      // 0x04
    virtual int Release();                     // 0x08
};
struct IMsgServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMessage(unsigned id, IMsg* msg, int flag);      // 0x14
};
struct cString {                               // SP::cString (one word)
    int mData;
    cString();                                                       // 0x006b5060
    void Load(unsigned tableId, unsigned groupId, const wchar_t* fallback);   // 0x006b54b0
    const wchar_t* GetText();                                        // 0x006b55c0
    ~cString();                                                      // 0x006b5240
};

struct GridEntry {
    Key                     mKey;      // +0x00
    AutoRefCount<AssetData> mData;     // +0x0c
    AutoRefCount<AssetView> mView;     // +0x10
    float                   mX;        // +0x14
    float                   mY;        // +0x18
    bool                    mEnabled;  // +0x1c
    bool                    mHasData;  // +0x1d
    GridEntry(const Key* key, AssetData* data, AssetView* view, bool a, bool b);   // 0x0064e6e0
    GridEntry(const GridEntry& x);                                                  // 0x0064f3b0
};
struct GridVec {
    GridEntry* mpBegin;
    GridEntry* mpEnd;
    GridEntry* mpCapacity;
    void reserve(int n);                                                 // 0x00652b00
    void DoInsertValue(GridEntry* pos, const GridEntry& v);              // 0x006535b0
    void FUN_654490(int x);                                              // 0x00654490
    void push_back(const GridEntry& v)
    {
        if (mpEnd < mpCapacity) {
            GridEntry* p = mpEnd;
            mpEnd = p + 1;
            if (p) new (p) GridEntry(v);
        } else
            DoInsertValue(mpEnd, v);
    }
};

struct KeyVec {                                // eastl::vector<Key>
    Key* mpBegin;
    Key* mpEnd;
    Key* mpCapacity;
    void reserve(int n);                       // 0x0041e4d0
};

struct KeyIter { void* mpNode; bool operator==(const KeyIter& o) const { return mpNode == o.mpNode; } };
struct KeyMap {                                // eastl::map<Key, AssetData*> embedded at +0x48 of the feed item
    KeyIter* find(KeyIter* out, const Key* key);                         // 0x00a21dc0
};
struct FeedListItem {                          // SP::cSPUIFeedListItem (what the grid shows)
    char   pad0[0x48];
    KeyMap mMap;                               // +0x48
    char   pad4c[0x5c - 0x4c];
    int    mTotal;                             // +0x5c
    bool   FUN_642910();                       // 0x00642910
    int    FUN_643060();                       // 0x00643060
    int    FUN_642900();                       // 0x00642900
    void   FUN_644040(KeyVec* out);            // 0x00644040
    bool   FUN_6442e0(const Key* key);         // 0x006442e0
};
struct FeedFilter {                            // SP::cSPUIFeedFilter (+0xe0)
    char pad0[0x14];
    int  mF14;
    int  mF18;
    bool Check(AssetData* data, int mode);                 // 0x00660880
    void FUN_662750(int a, int b, int c);                  // 0x00662750
    void FUN_10829f0(int arg);                             // 0x010829f0
};
struct SearchBox {                             // SP::cSPUISearchBox (+0xe4)
    bool Match(AssetData* data);               // 0x00672200
    void FUN_6720e0();                         // 0x006720e0
    void Update(int arg);                      // 0x00672040
};
struct AssetContainer {
    char pad0[4];
    void* mpEnd;                               // +4
    struct IterPair { void* first; void* second; };
    void FindEntry(IterPair* out, GridEntry* e);                         // 0x00646d10
};
struct AssetBrowser {
    char pad0[0x18];
    void* mpTool;                              // +0x18
    AssetContainer* GetContainer();                                      // 0x00644a70
    AssetView* GetViewFor(AssetData* data);                              // 0x006462b0
    AssetView* GetDefaultView();                                         // 0x006452c0
};
struct GlobalStats { char pad[0x28]; int mFilteredOut; };

extern AssetBrowser* __cdecl GetAssetBrowser();                          // 0x00401030
extern IAppSystem* __cdecl GetAppSystem();                               // 0x0067dd00
extern IMsgServer* __cdecl GetMessageServer();                           // 0x0067dcc0
extern int __cdecl GetTutorialToolPrice(void* tool, unsigned id, int def);   // 0x004e1c30
extern void* __cdecl EASTL_allocator_allocate(unsigned n, const char* name, int a, int b, int c, int d);  // 0xf473a0
extern void  __cdecl EASTL_allocator_deallocate(void* p);                // 0xf47380
extern const char g_assetViewName[];                                     // 0x013f6b3c
extern GlobalStats* g_pStats;                                            // 0x015ee298
extern IMsg* __fastcall AssetMsg_ctor(void* mem, void* edx, AssetView* view, int a, int b, int c, int d);   // 0x0064e740 (thiscall)

struct Stopwatch {
    unsigned long long mStart;
    unsigned long long mElapsed;
    int mMode;
    int mUnits;
    unsigned long long GetElapsedTime();                                 // 0x0093a5e0
    void Restart();                                                      // 0x00571e80
    void Start()
    {
        unsigned long long t;
        if (mMode == 1) t = __rdtsc();
        else QueryPerformanceCounter((long long*)&t);
        mStart = t;
        mElapsed = 0;
    }
};

// ---------------------------------------------------------------------------
// SP::cSPUIAssetGrid (retail layout; every field the functions of this slice touch)
// ---------------------------------------------------------------------------
struct GB0 { virtual ~GB0() {} virtual void b0f1(); };
struct GB1 { virtual ~GB1() {} virtual void b1f1(); };
struct GB2 { virtual void b2f0(); virtual void b2f1(); };
struct GB3 { GB3() : mRefCount(0) {} virtual ~GB3() {} int mRefCount; };

struct cSPUIAssetGrid : GB0, GB1, GB2, GB3 {
    bool mIsVisible;                              // +0x14
    char pad18[0x2c - 0x18];
    AutoRefCount<IWindow> mWinFeedHeader;         // +0x2c
    AutoRefCount<IWindow> mWinFeedFilter;         // +0x30
    char pad34[0x60 - 0x34];
    AutoRefCount<IWindow> mWinMessagePrimary;     // +0x60
    AutoRefCount<IWindow> mWinMessageSecondary;   // +0x64
    char pad68[0xe0 - 0x68];
    FeedFilter* mFeedFilter;                      // +0xe0
    SearchBox*  mSearchBox;                       // +0xe4
    GridVec     mGridEntries;                     // +0xe8
    char padF4[0xfc - 0xf4];
    FcObj*      mpFc;                             // +0xfc
    bool        m100;                             // +0x100
    float       mCardWidth;                       // +0x104
    float       mCardHeight;                      // +0x108
    bool        m10c;                             // +0x10c
    char pad110[0x150 - 0x110];
    Stopwatch   mTimerA;                          // +0x150
    Stopwatch   mTimerB;                          // +0x168
    float       m180, m184;                       // +0x180
    char pad188[0x18c - 0x188];
    ScrollFrame* mpScrollFrame;                   // +0x18c
    char pad190[0x194 - 0x190];
    int         m194;                             // +0x194
    int         m198;                             // +0x198
    struct ViewState { char pad[0x16]; bool f16; };
    ViewState*  mpViewState;                      // +0x19c
    char pad1a0[0x1a8 - 0x1a0];
    int         mNumTotal;                        // +0x1a8
    int         mNumShown;                        // +0x1ac
    int         mNumEnabled;                      // +0x1b0
    int         mNumPending;                      // +0x1b4
    bool        m1b8, m1b9, m1ba, m1bb;           // +0x1b8
    char pad1bc[4];
    FeedListItem* mpFeed;                         // +0x1c0
    Key         mPendingKey;                      // +0x1c4
    bool        mPendingA;                        // +0x1d0
    bool        mPendingB;                        // +0x1d1
    char pad1d2[2];
    float       mPendingL, mPendingT, mPendingR, mPendingB2;   // +0x1d4
    bool        mLoadingFeed;                     // +0x1e4
    bool        m1e5;                             // +0x1e5
    bool        mNeedsRefresh;                    // +0x1e6
    bool        mNeedsFocus;                      // +0x1e7
    bool        m1e8;                             // +0x1e8

    void RefreshAssetStates();                                   // @ 0x006553b0
    bool SelectKey(const Key* key, bool a, bool b, const Rect* rc);   // @ 0x00655840
    void AddEntries(KeyVec* keys);                               // @ 0x00655b00
    void Update(int arg);                                        // @ 0x00655ed0
    void UpdateAll();                                            // 0x0064ecc0
    void FUN_654d00();                                           // 0x00654d00
    void UpdateStatsText();                                      // 0x006528f0
    void UpdateScrollRegion();                                   // 0x006524a0
    int  FindFirstVisibleEntry();                                // 0x00653b80
    void FUN_654e20(AssetView* v);                               // 0x00654e20
    void FUN_654f50(FeedListItem* feed, ViewState* st);          // 0x00654f50
    bool FUN_64fde0(int* p);                                     // 0x0064fde0
    void FUN_64e880(bool a, unsigned pct);                       // 0x0064e880
    bool FUN_64e7d0(int i);                                      // 0x0064e7d0
    void FUN_650470();                                           // 0x00650470
    void UpdateScrolling(int a);                                 // 0x0064fa20
};

// @ 0x006553b0  recompute which entries pass the current filters and notify their views
void cSPUIAssetGrid::RefreshAssetStates()
{
    mNeedsRefresh = false;
    if (mpFc) {
        if (mpFc->mpView)
            mpFc->mpView->Destroy();
        mpFc = 0;
    }
    m100 = false;
    mNumTotal = 0;
    mNumShown = 0;
    mNumEnabled = 0;
    if (mFeedFilter && mSearchBox) {
        int count = (int)(mGridEntries.mpEnd - mGridEntries.mpBegin);
        for (int i = 0; i < count; ++i) {
            GridEntry* e = mGridEntries.mpBegin + i;
            if (e->mData.mpObject && e->mView.mpObject) {
                bool notFiltered = !mFeedFilter->Check(e->mData.mpObject, 1);
                bool tryMatch;
                if (mFeedFilter->mF14 == mFeedFilter->mF18)
                    tryMatch = notFiltered;
                else
                    tryMatch = notFiltered && !mFeedFilter->Check(mGridEntries.mpBegin[i].mData.mpObject, 0);
                bool enabled = tryMatch && mSearchBox->Match(mGridEntries.mpBegin[i].mData.mpObject);
                if (m1bb && !mGridEntries.mpBegin[i].mData.mpObject->PassesFilterA()) {
                    enabled = false;
                    notFiltered = false;
                }
                if (m1b9 && !mGridEntries.mpBegin[i].mData.mpObject->PassesFilterB()) {
                    enabled = false;
                    notFiltered = false;
                }
                if (m1ba && !mGridEntries.mpBegin[i].mData.mpObject->PassesFilterC()) {
                    enabled = false;
                    notFiltered = false;
                }
                if (mGridEntries.mpBegin[i].mData.mpObject->IsHidden()) {
                    notFiltered = false;
                    enabled = false;
                }
                mNumTotal++;
                if (notFiltered)
                    mNumShown++;
                if (enabled)
                    mNumEnabled++;
                bool enabledArg = enabled;
                mGridEntries.mpBegin[i].mView.mpObject->SetEnabled(enabledArg);
                if (!enabled) {
                    AssetContainer* cont = GetAssetBrowser()->GetContainer();
                    AssetContainer::IterPair r;
                    cont->FindEntry(&r, mGridEntries.mpBegin + i);
                    void* it = r.first;
                    if (it == r.second)
                        it = cont->mpEnd;
                    if (it != cont->mpEnd) {
                        void* mem = EASTL_allocator_allocate(0x1c, g_assetViewName, 0, 0, 0, 0);
                        IMsg* msg;
                        if (mem) {
                            msg = AssetMsg_ctor(mem, 0, mGridEntries.mpBegin[i].mView.mpObject, 0, 0, 1, 0);
                            if (msg)
                                msg->AddRef();
                        } else
                            msg = 0;
                        GetMessageServer()->PostMessage(0x94174b89, msg, 0);
                        if (msg)
                            msg->Release();
                    }
                }
            }
        }
    }
    UpdateAll();
    FUN_654d00();
    UpdateStatsText();
    UpdateScrollRegion();
    int shown = mNumShown;
    int enabledCount = mNumEnabled;
    IWindow* w;
    bool flag;
    if (shown == enabledCount) {
        w = mWinMessagePrimary.mpObject;
        if (!w)
            goto done;
        flag = false;
    } else {
        int idx = enabledCount;
        if (mpViewState == 0) {
            if (m1b8)
                idx = enabledCount + 1;
        } else if (m1b8 && mpViewState->f16) {
            idx = enabledCount + 1;
        }
        if (idx >= (int)(mGridEntries.mpEnd - mGridEntries.mpBegin)
            || !mGridEntries.mpBegin[idx].mHasData
            || !mWinMessagePrimary.mpObject)
            goto done;
        if (mWinMessageSecondary.mpObject) {
            g_pStats->mFilteredOut = shown - enabledCount;
            cString s;
            s.Load(0x21671745, 0x30007, L"*Filtered out items*");
            IWindow* w2 = mWinMessageSecondary.mpObject;
            w2->SetText(s.GetText());
        }
        int price = 5;
        if (GetAssetBrowser() && GetAssetBrowser()->mpTool)
            price = GetTutorialToolPrice(GetAssetBrowser()->mpTool, 0x86cf5fc5, 5);
        GridEntry* e = mGridEntries.mpBegin + idx;
        mWinMessagePrimary.mpObject->SetPos(e->mX + (float)price, e->mY + (float)price);
        mWinMessagePrimary.mpObject->SetSize(mCardWidth - (float)(price * 2), mCardHeight - (float)(price * 2));
        w = mWinMessagePrimary.mpObject;
        flag = true;
    }
    w->SetVisible(true, flag);
done:
    if (mNeedsFocus) {
        int first = FindFirstVisibleEntry();
        if (first >= 0) {
            AssetView* v = mGridEntries.mpBegin[first].mView.mpObject;
            if (v) {
                v->AddRef();
                FUN_654e20(v);
                v->Release();
            }
        }
        mNeedsFocus = false;
    }
}

// @ 0x00655840  select (and optionally scroll to) the entry for a key; returns true when it was applied
bool cSPUIAssetGrid::SelectKey(const Key* key, bool a, bool b, const Rect* rc)
{
    Rect zero;
    if (key->a == 0 && key->b == 0 && key->c == 0)
        return false;
    if (mLoadingFeed) {
        if (a) {
            if (!mpFeed)
                goto lookup;
            KeyIter it;
            KeyMap* m = &mpFeed->mMap;
            KeyIter endIt;
            endIt.mpNode = (char*)m + 4;
            if (!(*m->find(&it, key) == endIt))
                goto lookup;
        }
        if (mpFeed && mpFeed->FUN_6442e0(key)) {
            mPendingKey = *key;
            mPendingA = a;
            mPendingB = b;
            if (!rc) {
                zero.l = 0.0f;
                zero.t = 0.0f;
                zero.r = 0.0f;
                zero.b = 0.0f;
                rc = &zero;
            }
            mPendingL = rc->l;
            mPendingT = rc->t;
            mPendingR = rc->r;
            mPendingB2 = rc->b;
            return true;
        }
    }
lookup:
    AssetData* data = 0;
    AssetView* view = 0;
    int count = (int)(mGridEntries.mpEnd - mGridEntries.mpBegin);
    for (int i = 0; i < count; ++i) {
        AssetData* d = mGridEntries.mpBegin[i].mData.mpObject;
        if (d) {
            const Key* k = d->GetKey();
            if (k->a == key->a && k->b == key->b && k->c == key->c)
                goto found;
        }
        {
            const GridEntry* e = mGridEntries.mpBegin + i;
            if (e->mKey.a == key->a && e->mKey.b == key->b && e->mKey.c == key->c)
                goto found;
        }
        continue;
    found:
        d = mGridEntries.mpBegin[i].mData.mpObject;
        if (d) {
            d->AddRef();
            data = d;
        }
        AssetView* v = mGridEntries.mpBegin[i].mView.mpObject;
        if (v) {
            v->AddRef();
            view = v;
        }
        break;
    }
    if (mSearchBox && !mSearchBox->Match(data))
        mSearchBox->FUN_6720e0();
    if (mFeedFilter && mFeedFilter->Check(data, 0) && !mFeedFilter->Check(data, 1)) {
        int f = mFeedFilter->mF14;
        mFeedFilter->FUN_662750(f, f, 0);
    }
    if (mNeedsRefresh)
        RefreshAssetStates();
    if (view) {
        if (view->mSelectable) {
            view->SelectAsset((int)a, b, rc, 0, 0);
            view->Release();
            if (data)
                data->Release();
            return true;
        }
        view->Release();
    }
    if (data)
        data->Release();
    return false;
}

// @ 0x00655b00  create entries for the loaded keys of the current feed
void cSPUIAssetGrid::AddEntries(KeyVec* keys)
{
    if (mpFc) {
        if (mpFc->mpView)
            mpFc->mpView->Destroy();
        mpFc = 0;
    }
    m100 = false;
    if (mWinFeedHeader.mpObject && mpFeed) {
        int existing = (int)(mGridEntries.mpEnd - mGridEntries.mpBegin);
        mGridEntries.reserve(existing + (int)(keys->mpEnd - keys->mpBegin));
        int n = (int)(keys->mpEnd - keys->mpBegin);
        for (int i = 0; i < n; ++i) {
            Key* key = keys->mpBegin + i;
            KeyIter it;
            if (mpFeed->mMap.find(&it, key)->mpNode == (char*)&mpFeed->mMap + 4)
                goto next;
            {
                AssetData* data = *(AssetData**)((char*)it.mpNode + 0x1c);
                if (data->IsReady()) {
                    AssetView* view = GetAssetBrowser()->GetViewFor(data);
                    if (view)
                        view->AddRef();
                    GridEntry tmp(key, data, view, false, false);
                    view->Attach(mWinFeedHeader.mpObject, data, 0, 1);
                    mGridEntries.push_back(tmp);
                    view->Release();
                } else {
                    mNumPending++;
                }
                Key* cur = &mPendingKey;
                if (cur->a != 0 || cur->b != 0 || cur->c != 0) {
                    bool match = (cur->a == key->a && cur->b == key->b && cur->c == key->c);
                    if (!match) {
                        const Key* dk = data->GetKey();
                        if (!(cur->a == dk->a && cur->b == dk->b && cur->c == dk->c))
                            goto next;
                    }
                    bool pa = mPendingA;
                    if (pa) {
                        const Rect* rc = (const Rect*)&mPendingL;
                        if (mPendingL == mPendingR || mPendingT == mPendingB2)
                            rc = 0;
                        SelectKey(cur, pa, mPendingB, rc);
                        cur->a = 0;
                        cur->b = 0;
                        cur->c = 0;
                    }
                }
            }
        next:;
        }
    }
    if (!mpFeed->FUN_642910())
        return;
    mLoadingFeed = false;
    FeedListItem* feed = mpFeed;
    if (feed) {
        mpFeed = 0;
        ((IRefCount*)feed)->Release();
    }
    mNeedsRefresh = true;
    mNeedsFocus = true;
    UpdateScrolling(0);
    FUN_650470();
    m194 = 1;
    mTimerA.Start();
    mGridEntries.FUN_654490(-1);
    Key* cur = &mPendingKey;
    if (cur->a == 0 && cur->b == 0 && cur->c == 0) {
        AssetView* v = GetAssetBrowser()->GetDefaultView();
        if (v) {
            v->AddRef();
            FUN_654e20(v);
            v->Release();
        }
    } else {
        const Rect* rc = (const Rect*)&mPendingL;
        if (mPendingL == mPendingR || mPendingT == mPendingB2)
            rc = 0;
        SelectKey(cur, mPendingA, mPendingB, rc);
        cur->a = 0;
        cur->b = 0;
        cur->c = 0;
    }
}

// @ 0x00655ed0  SP::cSPUIAssetGrid::Update  (per-frame)
void cSPUIAssetGrid::Update(int arg)
{
    if (!m10c) {
        if (mLoadingFeed) {
            m10c = true;
            GetAppSystem()->SetFlag(1);
        }
    } else if (!mLoadingFeed) {
        m10c = false;
        GetAppSystem()->SetFlag(0);
    }
    if (m1e5) {
        int t = 2000;
        if (GetAssetBrowser() && GetAssetBrowser()->mpTool)
            t = GetTutorialToolPrice(GetAssetBrowser()->mpTool, 0x1df98401, 2000);
        if ((unsigned long long)(long long)t < mTimerB.GetElapsedTime()) {
            FUN_654f50(mpFeed, mpViewState);
            mTimerB.Restart();
        }
    }
    if (mLoadingFeed && mpFeed) {
        KeyVec keys;
        keys.mpBegin = 0;
        keys.mpEnd = 0;
        keys.mpCapacity = 0;
        if (!mpFeed->FUN_642910()) {
            FeedListItem* f = mpFeed;
            int n = f->FUN_643060();
            n += f->FUN_642900();
            keys.reserve(n);
            mpFeed->FUN_644040(&keys);
        }
        AddEntries(&keys);
        if (mLoadingFeed) {
            FeedListItem* f = mpFeed;
            int n = f->FUN_643060();
            n += f->FUN_642900();
            int done = mpFeed->mTotal;
            FUN_64e880(true, (unsigned)(done * 100) / (unsigned)(done + n));
        } else {
            if (mWinFeedFilter.mpObject)
                mWinFeedFilter.mpObject->SetVisible(true, false);
            if (mWinFeedHeader.mpObject)
                mWinFeedHeader.mpObject->SetVisible(true, true);
        }
        if (keys.mpBegin && ((int*)keys.mpBegin)[-1] != 0)
            EASTL_allocator_deallocate(keys.mpBegin);
    } else {
        if (mWinFeedFilter.mpObject)
            mWinFeedFilter.mpObject->SetVisible(true, false);
        if (mWinFeedHeader.mpObject)
            mWinFeedHeader.mpObject->SetVisible(true, true);
    }
    if (!mLoadingFeed) {
        if (mNeedsRefresh)
            RefreshAssetStates();
        if (m1e8)
            FUN_654d00();
        int t = 0x4b;
        if (GetAssetBrowser() && GetAssetBrowser()->mpTool)
            t = GetTutorialToolPrice(GetAssetBrowser()->mpTool, 0xb6c69eb8, 0x4b);
        if ((unsigned long long)(long long)t < mTimerA.GetElapsedTime() && m198 != 0
            && fabsf(m180 - m184) <= (float)mpScrollFrame->mScrollbar->GetMin()
            && FUN_64fde0(&m198))
            mTimerA.Restart();
        int count = (int)(mGridEntries.mpEnd - mGridEntries.mpBegin);
        for (int i = 0; i < count; ++i) {
            GridEntry* e = mGridEntries.mpBegin + i;
            AssetView* v = e->mView.mpObject;
            if (v && v->mSelectable) {
                Vec2 pos(e->mX, e->mY);
                mGridEntries.mpBegin[i].mView.mpObject->SetPos(pos, true);
                AssetView* v2 = mGridEntries.mpBegin[i].mView.mpObject;
                v2->OnUpdate(arg, FUN_64e7d0(i));
            }
        }
        if (mFeedFilter)
            mFeedFilter->FUN_10829f0(arg);
        if (mSearchBox)
            mSearchBox->Update(arg);
        UpdateScrolling(arg);
    }
}

// ---------------------------------------------------------------------------
// Pre-existing helper externs for 0x00656240 (filter-then-copy_if over 0x10-byte records)
extern "C" void FUN_00654050(void*, void*, void*);   // 0x00654050 (local vector ctor)
extern "C" int  FUN_006536e0(void*, void*, void*, void*, void*, void*, void*);  // filter
extern "C" int  FUN_00653780(int*, void*, int*, void*, void*, void*, int);      // copy_if

// @ 0x00656240  filter-then-copy_if over 0x10-byte records
int FUN_00656240(int* first, int* last, int* keysBegin, int* keysEnd, void* attr) {
    char local[0x94];
    FUN_00654050(keysBegin, keysEnd, first);           // build temp key vector
    int* pos = (int*)FUN_006536e0((void*)first, (void*)last, local, local, 0, 0, 0);
    if (pos != last) {
        FUN_00654050(keysBegin, keysEnd, first);
        pos = (int*)FUN_00653780(pos + 4, last, pos, local, local, 0, 0);
    }
    if (keysBegin && keysBegin != (int*)attr)
        EASTL_allocator_deallocate(keysBegin);
    return (int)pos;
}
