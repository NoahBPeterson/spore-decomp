// Slice s00f0f8f0 (gold7 #241) -- SP::cSPUISpace (Sporepedia large asset view HUD).
//
// NOTE: this slice id is shared with the older cl2 slice whose source is
// s00f0f8f0.cpp (CreatureHud::Init @ 0x00f10030).  That file is left untouched.
// The gold7 VAs are the cSPUISpace constructor / shutdown / minimap setup and
// the red-black-tree find-or-insert helper:
//
//   00f0f8f0  cSPUISpace::Shutdown          (tear the whole HUD down)
//   00f0fbc0  cSPUISpace::CreateMinimap     (PDB candidate: GetPlanetNameTextWin)
//   00f0fe60  cTree::MapEntry               (eastl::map operator[] find-or-insert)
//   00f0fef0  cSPUISpace::cSPUISpace        (constructor)
//
// Flags: VS2008-era cl 15, /O2 /MD /Gy /EHsc /TP /arch:SSE /GS- (default fp)
//
// The class layout below is the same one reconstructed in s00f0ea20 (its
// 0x00f0f740 destructor and 0x00f0f290 ResetMinimap use the same offsets), so
// the fields keep those names.

#include "types.h"
#include <math.h>

#define CAT2(a, b) a##b
#define CAT(a, b)  CAT2(a, b)
#define P1 virtual void CAT(pad_, __COUNTER__)();
#define P2 P1 P1
#define P4 P2 P2
#define P8 P4 P4
#define P16 P8 P8
#define P32 P16 P16

// ---------------------------------------------------------------------------
// external callees
// ---------------------------------------------------------------------------
struct EAAllocator;
void* EAAlloc(int size, int align, const char* name, void* allocator);   // 0x009512d0
void* GetEAAllocator();                                                 // 0x009512c0

void* GetNounManager();                                                 // 0x00b3d300
void* GetTerrainManager();                                              // 0x00b3d320
void* GetMessageServer();                                               // 0x0067dcc0

struct NounManager { void* GetAvatar(); };                              // 0x00b1fdb0
struct TerrainMgr  { void* GetTerrain(); };                             // 0x00b1de80

struct RewardUI    { void Shutdown(); };    // 0x00f17ea0
struct Rainbow     { void Init(); };        // 0x00e33a00
struct ProgressBar { void Clear(); };       // 0x00f18d60
struct Panel       { void Func_f04ad0(); };// 0x00f04ad0

// 0x00d2c9f0  cListIterator* cNodeList::Erase(cListIterator*, cListNode*, cListNode**)
struct cListIterator;
struct cListNode;

// node key/value pair of the eastl tree at +0x14c
struct cMapNode {
    cMapNode* mLeft;      // +0x00
    cMapNode* mRight;     // +0x04
    cMapNode* mParent;    // +0x08
    uint32_t  mPad0c;     // +0x0c
    uint32_t  mKey;       // +0x10
    uint32_t  mValue;     // +0x14
};

// 0x00abff10  insert-or-assign with a caller-provided hint / query pair
struct cTree {
    uint32_t  mPad00;     // +0x00
    cMapNode  mEnd;       // +0x04 (anchor; mEnd.mParent at +0x0c is the root)
    uint32_t* MapEntry(const uint32_t* pKey);   // @ 0x00f0fe60
    uint32_t* InsertValue(uint32_t* hintOut, cMapNode* hint,
                          uint32_t* query, uint8_t flag);   // 0x00abff10
};

// ---------------------------------------------------------------------------
// class layout (same as s00f0ea20's cSPUISpace)
// ---------------------------------------------------------------------------
struct TimerOwner {
    void*  mVtbl;          // +0x00
    uint8_t mPad04[0x34];  // +0x04
    TimerOwner* Ctor();    // 0x00af14b0
};
struct PA_Agg {
    void* mVtbl;           // +0x38
};
struct cListenerBase {
    void* mVtbl;           // +0x3c
};
struct cContentValidationSummarizer {
    void* mVtbl;           // +0x40
};

struct GlobalUI {
    virtual void Destroy(int);              // +0x00
    virtual void v04();                     // +0x04
    virtual void Load(const void* pData);   // +0x08
    virtual void Shutdown();                // +0x0c
    struct Window* FindWindowByID(uint32_t id);   // 0x00e012b0 (ret 4)
};

struct Window {
    P8 P4 P2                                        // slots 0..13
    virtual float* GetRect();                       // +0x38
    P16 P1                                          // slots 15..31
    virtual void SetArg(void* p);                   // +0x80
    P16 P4 P1                                       // slots 33..53
    virtual void SetMinimap(void* p);               // +0xd8
    P8 P2                                           // slots 55..64
    virtual void AddWinProc(void* pProc);           // +0x104
    virtual void RemoveWinProc(void* pProc);        // +0x108
};

struct cGonzagoTimer {
    uint8_t mPad[0x20];
    cGonzagoTimer* Ctor();                          // 0x00b63890
};

struct cCreatureTimerBar {
    uint8_t mPad[0x78];
    void Ctor();                                    // 0x00d2ba60
    void Shutdown();                                // 0x00d2bc60
};

struct cListIterator {
    void* mNode;   // +0x00
    void* mPrev;   // +0x04
};

struct cNodeList {
    void*          mVtbl;         // +0x00
    cListNode**    mBuckets;      // +0x04  (object +0x150)
    uint32_t       mBucketCount;  // +0x08  (object +0x154)
    uint8_t        mPad0c[0x190 - 0x0c];
    void Ctor(const void* a, const void* b);                       // 0x00d2d5c0
    cListIterator* Erase(cListIterator* it, cListNode* node, cListNode** out); // 0x00d2c9f0
};

struct cListNode {
    cListNode* mNext;    // +0x00
    void*      mData;    // +0x04
};

struct cIconData {
    uint8_t  mPad00[0xb54];
    void*    mpTarget;   // +0xb54
    uint32_t mFlags;     // +0xb58
};
struct cIconTarget {
    uint8_t mPad00[0x80];
    float   mAlpha;      // +0x80
};

struct MinimapTree {
    uint32_t mPad00;      // +0x00 (object +0x2ec)
    void*    mLeft;       // +0x04 (object +0x2f0)
    void*    mRight;      // +0x08 (object +0x2f4)
    void*    mParent;     // +0x0c (object +0x2f8)
    uint8_t  mColor;      // +0x10 (object +0x2fc)
    uint8_t  mPad11[3];
    uint32_t mSize;       // +0x14 (object +0x300)
};

struct cSPUIMinimapWin {
    cSPUIMinimapWin* Ctor(int w, int h, const void* a, const void* b, float f, int z); // 0xe0fc90
    void Init();                 // 0x00e0be50
    void SetDirection(void* d);  // 0x00e0c1f0
    void SetZoom(float z);       // 0x00e0c2a0
    void SetViewMode(int m);     // 0x00e0ad00
};

struct cSPUISpace {
    TimerOwner                    mTimerOwner;        // +0x0000
    PA_Agg                        mAgg;               // +0x0038
    cListenerBase                 mListener;          // +0x003c
    cContentValidationSummarizer  mSummarizer;        // +0x0040
    uint32_t                      m44;                // +0x0044
    void*                         m48;                // +0x0048
    void*                         m4c;                // +0x004c
    void*                         m50;                // +0x0050
    void*                         m54;                // +0x0054
    uint8_t                       m58;                // +0x0058
    uint8_t                       m59;                // +0x0059
    uint8_t                       m5a[2];             // +0x005a
    GlobalUI*                     mGlobalUI;          // +0x005c
    void*                         mPosse;             // +0x0060
    void*                         mRainbow;           // +0x0064
    void*                         mProgressBar;       // +0x0068
    uint8_t                       m6c[4];             // +0x006c
    cGonzagoTimer                 mTimer70;           // +0x0070
    cGonzagoTimer                 mTimer90;           // +0x0090
    cCreatureTimerBar             mTimerBar;          // +0x00b0
    void*                         m128;               // +0x0128
    void*                         mRewardUI;          // +0x012c
    float                         m130;               // +0x0130
    float                         m134;               // +0x0134
    float                         m138;               // +0x0138
    uint8_t                       m13c;               // +0x013c
    uint8_t                       m13d[3];            // +0x013d
    void*                         mEffect140;         // +0x0140
    void*                         mEffect144;         // +0x0144
    void*                         mCard;              // +0x0148
    cNodeList                     mTable;             // +0x014c
    void*                         m2dc;               // +0x02dc
    cSPUIMinimapWin*              mMinimap;           // +0x02e0
    float                         mTimer;             // +0x02e4
    uint8_t                       mFlag2e8;           // +0x02e8
    uint8_t                       m2e9[3];            // +0x02e9
    MinimapTree                   mTree;              // +0x02ec

    cSPUISpace();                                     // @ 0x00f0fef0
    void Shutdown();                                  // @ 0x00f0f8f0
    void CreateMinimap();                             // @ 0x00f0fbc0
    void ResetMinimap();                              // 0x00f0f290 (external)
};

// ---------------------------------------------------------------------------
// globals / vtables
// ---------------------------------------------------------------------------
struct HudHost {
    uint8_t mPad[0xd0];
    int     mValueD0;       // +0xd0
    int     mPadD4;
    void*   mpPanelD8;      // +0xd8
};
extern HudHost* gpHudHost_016c7aa4;      // 0x016c7aa4

struct Cursor {
    void Reset(int a, int b);            // 0x00d2bef0 (ret 8)
    int mf0, mf4, mf8, mfC;
};
extern Cursor gCursor_016c8050;          // 0x016c8050

extern float g_15ad5e8;                  // 0x015ad5e8
extern float g_15ad5ec;                  // 0x015ad5ec

struct Property {
    uint8_t  mPad00[0x12];
    uint16_t mType;          // +0x12
    float*   GetFloat();     // 0x0041ea70
};

struct Terrain {
    P8 P1
    virtual bool GetProperty(uint32_t id, void** out);   // +0x24
};

struct IMessageListener { virtual void ml0(); };

extern char g_vtbl_PA_Agg;                        // 0x14426a0
extern char g_vtbl_cListenerBase;                 // 0x13eb384
extern char g_vtbl_cContentValidationSummarizer;  // 0x13ec458
extern char g_vtbl_cSPUISpace;                    // 0x148bd60
extern char g_vtbl_cSPUISpace38;                  // 0x148bd44
extern char g_vtbl_cSPUISpace3c;                  // 0x148bd34
extern char g_vtbl_cSPUISpace40;                  // 0x148bd24

// ---------------------------------------------------------------------------
// small vtable-offset call helpers (inline; vtable offsets are accepted here)
// ---------------------------------------------------------------------------
static inline void vt_call0(void* o, int off)
{
    (*(void (__thiscall**)(void*))(*(char**)o + off))(o);
}
static inline void vt_call1i(void* o, int off, int a)
{
    (*(void (__thiscall**)(void*, int))(*(char**)o + off))(o, a);
}
static inline void vt_call1p(void* o, int off, void* a)
{
    (*(void (__thiscall**)(void*, void*))(*(char**)o + off))(o, a);
}
static inline float* vt_callRect(void* o, int off)
{
    return (*(float* (__thiscall**)(void*))(*(char**)o + off))(o);
}

// ---------------------------------------------------------------------------
// 0x00f0fe60 -- eastl::map<unsigned, unsigned>::operator[] find-or-insert
// ---------------------------------------------------------------------------
// @ 0x00f0fe60
uint32_t* cTree::MapEntry(const uint32_t* pKey)
{
    cMapNode* node  = mEnd.mParent;
    cMapNode* found = &mEnd;
    while (node != 0) {
        if (node->mKey < *pKey) {
            node = node->mLeft;
        } else {
            found = node;
            node = node->mRight;
        }
    }
    if (found != &mEnd && found->mKey <= *pKey) {
        return &found->mValue;
    }
    uint32_t query[3];
    query[0] = *pKey;
    query[1] = 0xffffffff;
    query[2] = 0xffffffff;
    uint8_t flag = 0;
    InsertValue((uint32_t*)&found, found, query, flag);
    return (uint32_t*)((char*)found + 0x14);
}

// ---------------------------------------------------------------------------
// 0x00f0fef0 -- cSPUISpace constructor
// ---------------------------------------------------------------------------
// @ 0x00f0fef0
cSPUISpace::cSPUISpace()
{
    mTimerOwner.Ctor();
    *(void* volatile*)&mAgg.mVtbl        = &g_vtbl_PA_Agg;
    *(void* volatile*)&mListener.mVtbl   = &g_vtbl_cListenerBase;
    *(void* volatile*)&mSummarizer.mVtbl = &g_vtbl_cContentValidationSummarizer;
    int zero = 0;
    *(int volatile*)&m44 = zero;
    *(void* volatile*)&mTimerOwner.mVtbl = &g_vtbl_cSPUISpace;
    *(void* volatile*)&mAgg.mVtbl        = &g_vtbl_cSPUISpace38;
    *(void* volatile*)&mListener.mVtbl   = &g_vtbl_cSPUISpace3c;
    *(void* volatile*)&mSummarizer.mVtbl = &g_vtbl_cSPUISpace40;
    m48 = (void*)zero;
    m4c = (void*)zero;
    m50 = (void*)zero;
    m54 = (void*)zero;
    m58 = 1;
    m59 = 1;
    mGlobalUI = (GlobalUI*)zero;
    mPosse = (void*)zero;
    mRainbow = (void*)zero;
    mProgressBar = (void*)zero;
    mTimer70.Ctor();
    mTimer90.Ctor();
    mTimerBar.Ctor();
    m128 = (void*)zero;
    mRewardUI = (void*)zero;
    m130 = 0.0f;
    m134 = 0.0f;
    m138 = 0.0f;
    m13c = 1;
    mEffect140 = (void*)zero;
    mEffect144 = (void*)zero;
    uint8_t alloc = 0;
    mTable.Ctor(&alloc, &alloc);
    m2dc = (void*)zero;
    mMinimap = (cSPUIMinimapWin*)zero;
    mFlag2e8 = 0;
    mTimer = 0.0f;
    mTree.mRight  = (void*)zero;
    mTree.mParent = (void*)zero;
    *(uint32_t*)&mTree.mColor = 0;
    mTree.mRight  = &mTree.mLeft;
    mTree.mLeft   = &mTree.mLeft;
    mTree.mParent = (void*)zero;
    mTree.mColor  = 0;
    mTree.mSize   = 0;
}

// ---------------------------------------------------------------------------
// 0x00f0f8f0 -- cSPUISpace::Shutdown
// ---------------------------------------------------------------------------
// @ 0x00f0f8f0
void cSPUISpace::Shutdown()
{
    ResetMinimap();

    if (mGlobalUI != 0) {
        Window* w = mGlobalUI->FindWindowByID(0x7104132);
        if (w) w->RemoveWinProc(&mAgg);
        w = mGlobalUI->FindWindowByID(0x7104130);
        if (w) w->RemoveWinProc(&mAgg);
    }

    if (mRewardUI != 0) {
        ((RewardUI*)mRewardUI)->Shutdown();
        if (mRewardUI != 0) {
            mRewardUI = 0;
            vt_call0(mRewardUI, 4);
        }
    }

    if (mPosse != 0) {
        vt_call0(mPosse, 0x88);
        mPosse = 0;
    }

    if (m2dc != 0) {
        m2dc = 0;
        vt_call0(m2dc, 0x64);
    }

    if (gpHudHost_016c7aa4->mValueD0 == 0) {
        ((Panel*)gpHudHost_016c7aa4->mpPanelD8)->Func_f04ad0();
    }

    if (mGlobalUI != 0) {
        vt_call0(mGlobalUI, 0x0c);
        if (mGlobalUI != 0) {
            vt_call1i(mGlobalUI, 0, 1);
        }
        mGlobalUI = 0;
    }

    {
        void* ms = GetMessageServer();
        (*(void (__thiscall**)(void*, void*, uint32_t, int))
            (*(char**)ms + 0x2c))(ms, &mListener, 0x14051500, 0xffffd8f1);
    }

    gCursor_016c8050.Reset(gCursor_016c8050.mf4, gCursor_016c8050.mf8);
    gCursor_016c8050.mfC = 0;

    if (mRainbow != 0) {
        ((Rainbow*)mRainbow)->Init();
        if (mRainbow != 0) {
            mRainbow = 0;
            vt_call0(mRainbow, 4);
        }
    }

    if (mProgressBar != 0) {
        ((ProgressBar*)mProgressBar)->Clear();
        if (mProgressBar != 0) {
            mProgressBar = 0;
            vt_call0(mProgressBar, 4);
        }
    }

    mTimerBar.Shutdown();

    if (mEffect140 != 0) {
        vt_call1i(mEffect140, 0x0c, 1);
        if (mEffect140 != 0) {
            mEffect140 = 0;
            vt_call0(mEffect140, 4);
        }
    }
    if (mEffect144 != 0) {
        vt_call1i(mEffect144, 0x0c, 1);
        if (mEffect144 != 0) {
            mEffect144 = 0;
            vt_call0(mEffect144, 4);
        }
    }
    if (m48 != 0) {
        vt_call1i(m48, 0x0c, 1);
        if (m48 != 0) {
            m48 = 0;
            vt_call0(m48, 4);
        }
    }
    if (m4c != 0) {
        m4c = 0;
        vt_call0(m4c, 0x64);
    }
    if (m50 != 0) {
        vt_call1i(m50, 0x0c, 1);
    }
    if (m50 != 0) {
        m50 = 0;
        vt_call0(m50, 4);
    }

    m54 = 0;
    m58 = 1;

    {
        cListNode** bucket = mTable.mBuckets;
        cListNode* node = *bucket;
        if (node == 0) {
            do {
                ++bucket;
                node = *bucket;
            } while (node == 0);
        }
        cListNode** end = mTable.mBuckets + mTable.mBucketCount;
        while (node != *end) {
            void* data = node->mData;
            if (data != 0) {
                cIconData* d = (cIconData*)data;
                if (d->mpTarget != 0) {
                    ((cIconTarget*)d->mpTarget)->mAlpha = 1.0f;
                    d->mFlags &= ~0x800u;
                }
            }
            cListIterator it;
            it.mNode = node;
            it.mPrev = bucket;
            cListNode* out = 0;
            cListIterator* r = mTable.Erase(&it, node, &out);
            node   = (cListNode*)r->mNode;
            bucket = (cListNode**)r->mPrev;
        }
    }

    if (mCard != 0) {
        vt_call0(mCard, 0x1c);
        if (mCard != 0) {
            mCard = 0;
            vt_call0(mCard, 4);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00f0fbc0 -- cSPUISpace::CreateMinimap
// ---------------------------------------------------------------------------
// @ 0x00f0fbc0
void cSPUISpace::CreateMinimap()
{
    ResetMinimap();

    void* avatar = ((NounManager*)GetNounManager())->GetAvatar();
    if (avatar == 0)
        return;

    void* terrain = ((TerrainMgr*)GetTerrainManager())->GetTerrain();
    if (terrain != 0) {
        Property* prop;
        if (((Terrain*)terrain)->GetProperty(0xde67264f, (void**)&prop) &&
            prop->mType == 0x000d) {
            g_15ad5e8 = *prop->GetFloat();
        }
        if (((Terrain*)terrain)->GetProperty(0xf7dc67f7, (void**)&prop) &&
            prop->mType == 0x000d) {
            g_15ad5ec = *prop->GetFloat();
        }
    }

    Window* w = mGlobalUI->FindWindowByID(0x562a2da);
    if (w != 0) {
        void* a = *(void**)((char*)gpHudHost_016c7aa4 + 0x74);
        void* b = *(void**)((char*)a + 4);
        void* fn = *(void**)((char*)b + 4);
        void* r = ((void* (__thiscall*)(void*))fn)((char*)a + 4);
        vt_call1p(w, 0x80, r);
    }

    w = mGlobalUI->FindWindowByID(0x190722e);
    if (w != 0) {
        float* r = vt_callRect(w, 0x38);
        float dw = r[2] - r[0];
        int width = (int)floorf(dw);
        float dh = r[3] - r[1];
        int height = (int)floorf(dh);

        cSPUIMinimapWin* mm = (cSPUIMinimapWin*)EAAlloc(
            0x9a8, 8, "UI/AdventureMinimap", GetEAAllocator());
        if (mm != 0) {
            float boxA[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
            float boxB[4] = { 0.0f, 1.0f, 0.0f, -1.0f };
            mm = mm->Ctor(width, height, boxA, boxB, 0.0f, 0);
        } else {
            mm = 0;
        }

        cSPUIMinimapWin* old = mMinimap;
        if (mm != old) {
            if (mm != 0)
                vt_call0(mm, 0);
            mMinimap = mm;
            if (old != 0)
                vt_call0(old, 4);
        }

        void* slot = mMinimap != 0 ? (char*)mMinimap + 4 : 0;
        vt_call1p(w, 0xd8, slot);
        mTimer = 0.0f;
        mFlag2e8 = 1;
        mMinimap->Init();

        void* sub = (char*)avatar + 0xc0;
        void* vtbl = *(void**)sub;
        void* dir = ((void* (__thiscall*)(void*))
            (*(void**)((char*)vtbl + 0x2c)))(sub);
        mMinimap->SetDirection(dir);
        mMinimap->SetZoom(g_15ad5e8);
        mMinimap->SetViewMode(4);
    }

    w = mGlobalUI->FindWindowByID(0x562a141);
    if (w != 0)
        vt_call1p(w, 0x104, &mAgg);
}
