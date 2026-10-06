// Slice s009568c0 - UTFWin 2D render system, display/renderable list pools,
// EASTL vector helpers and Object/UI::Image layer code.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-  (SSE2 float code).
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);        // 0xf473a0 (EA allocator, name/flags form)
void* __cdecl operator_new(unsigned int, const char*, int, int, const char*, int); // 0xf473a0 (EASTL allocator.h form)
void  __cdecl operator delete(void*) throw();                                      // 0xf47380
void  __cdecl operator_delete__(void*) throw();                                    // 0xf47380

void __cdecl chkstk();
int* __cdecl _DoInsertValue_(void*, void*, int);          // 0x11e0744 memcpy thunk (vector DoInsertValue)
void __cdecl _ushort_insert_(void*, void*);               // 0x6f5bc0
void __cdecl InitFontSystem();                            // 0x951c60
void* __cdecl FUN_00920090();
void __cdecl FUN_009574f0();
void __cdecl FUN_00951360();
void __cdecl FUN_009513b0();
void __cdecl FUN_00956870(void*);
void __cdecl FUN_00952f30();
void __cdecl FUN_009558c0();
void __fastcall ObjectAddRef(void*);                       // 0x95f990
void __fastcall FUN_00957530(int*);                        // 0x957530 (defined below)
extern char g_154ecf0[];                                   // 0x154ecf0
extern char g_154edd8[];                                   // 0x154edd8

// ---------------------------------------------------------------------------
// 2D system interfaces
// ---------------------------------------------------------------------------
struct SysInfo { char pad0[0x34]; int f34; char pad38[0x10]; int f48; };
struct I2DSystem {
    virtual void v0();
    virtual void v1();
    virtual void Init(int, int);                 // +8
    virtual void Shutdown();                     // +0xc
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual SysInfo* GetInfo(int, int);          // +0x30
};
struct IFontObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual bool Init();                         // +0x20
    virtual void Shutdown();                     // +0x24
};
struct IFontMgr {
    virtual void v0();
    virtual void Release();                      // +4
    virtual void v2();
    virtual IFontObj* Get(int id);               // +0xc
};
struct R2DMemoryManager { char pad[0x68]; R2DMemoryManager(); ~R2DMemoryManager(); };   // 0x953430 / 0x952800
struct R2DPool {
    int f0, f4, f8, fc, f10, f14;
    R2DPool() : f0(0), f4(0), f8(0), f14(0) { Reserve(200); }
    ~R2DPool();                                  // 0x9535a0
    void Reserve(int n);                         // 0x9529d0
};
struct TwoDState { const void* pDefault; int f4; float f8, fc, f10, f14; int f18, f1c, f20; };

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern I2DSystem* g_pI2DSystem;      // 0x166aab8
extern long g_refCount2D;            // 0x166aac8
extern R2DMemoryManager* g_pR2DMemoryManager;   // 0x166aac4
extern R2DPool* g_pR2DPool;          // 0x166aac0
extern IFontMgr* g_pFontMgr;         // 0x166ae74
extern void*  g_pFreeRLChunk;        // 0x166b0f8
extern void*  g_pFreeDLHead;         // 0x154ed20
extern void*  g_pFreeDLTail;         // 0x154ed24
extern int    g_154ecd4;             // 0x154ecd4
extern void*  g_pSerTypeTable[4096]; // 0x154eea0
extern char   g_mutexHeaps[0x18];    // 0x166b100
extern char   g_uiImage[0x40];       // 0x166aacc
extern TwoDState g_twoDState;        // 0x166aad0
extern int    g_166b134;
extern const char g_scopeHeaps[];    // 0x1440548
extern char   g_154ecd0[];           // 0x154ecd0

// Mutex helpers (thiscall members on g_mutexHeaps)
struct Mutex {
    void Lock(const char*);
    void Unlock();
};

// vtable-call helpers
typedef void (__thiscall *VFn0)(void*);
typedef void (__thiscall *VFn1i)(void*, int);
typedef void (__thiscall *VFn2ii)(void*, int, int);
typedef int* (__thiscall *VFn2pii)(void*, int, int);
typedef int* (__thiscall *VFn1pi)(void*, int);
typedef int  (__thiscall *VFn1p1)(void*, int);
typedef int* (__thiscall *VFn0p)(void*);

static inline void** Vt(void* p) { return *(void***)p; }

void __fastcall FUN_00957530(int*);

// ===========================================================================
// @ 0x009568c0  EA::UTFWin::InternalInit2DSystem
// ===========================================================================
bool __cdecl InternalInit2DSystem(I2DSystem* pSystem) {
    if (g_pI2DSystem == 0)
        g_pI2DSystem = pSystem;
    g_pI2DSystem->Init(1, 0);
    if (_InterlockedIncrement(&g_refCount2D) - 1 == 0) {
        if (g_pR2DMemoryManager == 0)
            g_pR2DMemoryManager = new("UTFWin/Renderable2DMemoryManager", 0, 0, 0, 0) R2DMemoryManager;
        if (g_pR2DPool == 0)
            g_pR2DPool = new("UTFWin/Renderable2DPool", 0, 0, 0, 0) R2DPool;
        SysInfo* pInfo = g_pI2DSystem->GetInfo(0, 0);
        g_154ecd4 = pInfo->f34;
        ObjectAddRef(g_uiImage);
        g_twoDState.f8 = 0.0f;
        g_twoDState.fc = 0.0f;
        g_twoDState.pDefault = g_154ecd0;
        g_twoDState.f4 = 0;
        g_twoDState.f10 = 1.0f;
        g_twoDState.f14 = 1.0f;
        g_twoDState.f18 = pInfo->f48;
        g_twoDState.f1c = pInfo->f48;
        g_twoDState.f20 = 0;
        InitFontSystem();
        if (g_pFontMgr != 0) {
            IFontObj* pFont = g_pFontMgr->Get(0x838293);
            if (pFont != 0) {
                if (!pFont->Init()) {
                    FUN_00952f30();
                    return false;
                }
            }
        }
    }
    return true;
}

// ===========================================================================
// @ 0x00956a30  EA::UTFWin::Shutdown2DSystem
// ===========================================================================
void __cdecl FUN_00956a30() {
    if (_InterlockedDecrement(&g_refCount2D) == 0) {
        if (g_pFontMgr != 0) {
            IFontObj* pFont = g_pFontMgr->Get(0x838293);
            if (pFont != 0)
                pFont->Shutdown();
            if (g_pFontMgr != 0) {
                IFontMgr* pMgr = g_pFontMgr;
                g_pFontMgr = 0;
                pMgr->Release();
            }
        }
        FUN_00957530((int*)g_uiImage);
        FUN_00952f30();
        g_pI2DSystem->Shutdown();
        g_pI2DSystem = 0;
        if (g_pR2DPool) {
            delete g_pR2DPool;
            g_pR2DPool = 0;
        }
        if (g_pR2DMemoryManager) {
            delete g_pR2DMemoryManager;
            g_pR2DMemoryManager = 0;
        }
    }
}

// ===========================================================================
// @ 0x00956af0  intrusive refcount release
// ===========================================================================
int __fastcall FUN_00956af0(void* self) {
    int n = _InterlockedDecrement((volatile long*)((char*)self + 0x28));
    if (n == 0) {
        if (self != 0)
            ((VFn1i)Vt(self)[2])(self, 1);
    } else if (n == 1) {
        FUN_00956870(self);
    }
    return n;
}

// ===========================================================================
// @ 0x00956b30 / 0x00956c40  GlyphRenderer::DrawText overloads (layout text, hand glyph run to the target)
// ===========================================================================
struct GlyphDisplayEntry { char data[0x28]; };

struct GlyphFixedVec {                     // eastl::fixed_vector<GlyphDisplayEntry, 256>
    GlyphDisplayEntry* mpBegin;
    GlyphDisplayEntry* mpEnd;
    GlyphDisplayEntry* mpCapacity;
    int                mAllocFlags;
    GlyphDisplayEntry* mpPoolBegin;
    int                mAllocPad;
    GlyphDisplayEntry  mBuffer[256];
    GlyphFixedVec() {
        mpEnd = mBuffer;
        mpPoolBegin = mBuffer;
        mpCapacity = mBuffer + 256;
        mpBegin = mBuffer;
    }
    ~GlyphFixedVec() {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator_delete__(mpBegin);
    }
    void resize(unsigned int n);           // 0x955850
};

struct TextLayout {                        // EA::Text::Layout
    int LayoutTextLine(const wchar_t* text, int len, float x, float y, const void* style,
                       GlyphDisplayEntry* out, unsigned int cap, void* extra);                    // 0x890570
    int LayoutTextLine(float a, float b, float c, float d, const wchar_t* text, int len, const void* style,
                       GlyphDisplayEntry* out, unsigned int cap, void* extra);                    // 0x890830
};
extern char g_defaultTextStyle[];          // 0x166ae78
extern TextLayout g_defaultTextLayout;     // 0x166aaf8

struct GlyphRenderer {
    void* mpTarget;                        // +4 (after vptr); defaults to this+0x24
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void DrawGlyphs(GlyphDisplayEntry* pGlyphs, int nCount, const void* pStyle);     // +0x34
    void DrawText(float x, float y, const wchar_t* pText, int nLen, const void* pStyle,
                  TextLayout* pLayout, void* pExtra);
    void DrawText(float a, float b, float c, float d, const wchar_t* pText, int nLen, const void* pStyle,
                  TextLayout* pLayout, void* pExtra);
};

void GlyphRenderer::DrawText(float x, float y, const wchar_t* pText, int nLen, const void* pStyle,
                             TextLayout* pLayout, void* pExtra) {
    if (mpTarget == 0)
        mpTarget = (char*)this + 0x24;
    if (nLen == -1) {
        const wchar_t* p = pText;
        while (*p++ != 0)
            ;
        nLen = (int)(p - (pText + 1));
    }
    if (pStyle == 0)
        pStyle = g_defaultTextStyle;
    if (pLayout == 0)
        pLayout = &g_defaultTextLayout;
    GlyphFixedVec glyphs;
    glyphs.resize(nLen * 2);
    int n = pLayout->LayoutTextLine(pText, nLen, x, y, pStyle, glyphs.mpBegin, nLen * 2, pExtra);
    DrawGlyphs(glyphs.mpBegin, n, pStyle);
}

void GlyphRenderer::DrawText(float a, float b, float c, float d, const wchar_t* pText, int nLen, const void* pStyle,
                             TextLayout* pLayout, void* pExtra) {
    if (mpTarget == 0)
        mpTarget = (char*)this + 0x24;
    if (nLen == -1) {
        const wchar_t* p = pText;
        while (*p++ != 0)
            ;
        nLen = (int)(p - (pText + 1));
    }
    if (pStyle == 0)
        pStyle = g_defaultTextStyle;
    if (pLayout == 0)
        pLayout = &g_defaultTextLayout;
    GlyphFixedVec glyphs;
    glyphs.resize(nLen * 2);
    int n = pLayout->LayoutTextLine(a, b, c, d, pText, nLen, pStyle, glyphs.mpBegin, nLen * 2, pExtra);
    DrawGlyphs(glyphs.mpBegin, n, pStyle);
}

// ===========================================================================
// @ 0x00956d60  deleting destructor (UI resource)
// ===========================================================================
struct UIRes { void* Dtor(unsigned char flags); };

void* UIRes::Dtor(unsigned char flags) {
    void* self = this;
    *(void**)self = (void*)0x14404ac;
    FUN_009558c0();
    *(void**)self = (void*)0x13eb938;
    if (flags & 1)
        operator_delete__(self);
    return self;
}

// ===========================================================================
// @ 0x00956d90
// ===========================================================================
void __cdecl FUN_00956d90() {
    void* p = (void*)FUN_00920090();
    ((VFn2ii)Vt(p)[1])(p, (int)g_154ecf0, 0);
    FUN_009574f0();
    FUN_00951360();
    FUN_009513b0();
}

// ===========================================================================
// @ 0x00956e30  FreeRenderableListChunks
// ===========================================================================
struct RLChunk { RLChunk* p0; void* p4; };

void __cdecl FreeRenderableListChunks(RLChunk* p, RLChunk* q) {
    if (p == 0) return;
    if (q == 0) {
        q = p;
        while (q->p0)
            q = q->p0;
    }
    Mutex* m = (Mutex*)g_mutexHeaps;
    m->Lock(g_scopeHeaps);
    q->p0 = (RLChunk*)g_pFreeRLChunk;
    g_pFreeRLChunk = p;
    m->Unlock();
}

// ===========================================================================
// @ 0x00956e90  FreeDisplayListEntry
// ===========================================================================
void __cdecl FreeDisplayListEntry(int* e) {
    Mutex* m = (Mutex*)g_mutexHeaps;
    m->Lock(g_scopeHeaps);
    e[0] = (int)g_pFreeDLHead;
    e[1] = (int)&g_pFreeDLHead;
    g_pFreeDLHead = e;
    *(int**)(e[0] + 4) = e;
    m->Unlock();
}

// ===========================================================================
// @ 0x00956ed0  AllocRenderableListChunk
// ===========================================================================
RLChunk* __cdecl AllocRenderableListChunk() {
    Mutex* m = (Mutex*)g_mutexHeaps;
    m->Lock(g_scopeHeaps);
    RLChunk* p = (RLChunk*)g_pFreeRLChunk;
    if (p != 0)
        g_pFreeRLChunk = p->p0;
    m->Unlock();
    if (p == 0)
        p = (RLChunk*)operator_new(0x30, "UTFWin/RenderableListChunk", 0, 0, 0, 0);
    p->p4 = 0;
    p->p0 = 0;
    return p;
}

// ===========================================================================
// display-list free pool (intrusive circular list, anchor at 0x154ed20)
// ===========================================================================
struct DLNode { DLNode* mpNext; DLNode* mpPrev; };
struct DisplayList : DLNode {
    char pad[0x10];
    int  f18;
    int  f1c;
    char rest[0xe0];
    DisplayList() { mpNext = 0; mpPrev = 0; }
};
extern DLNode g_freeDL;                  // 0x154ed20 (next), 0x154ed24 (prev)

// ===========================================================================
// @ 0x00956f30  release all pooled display lists and renderable list chunks
// ===========================================================================
void __cdecl FUN_00956f30() {
    DLNode* pAnchor = &g_freeDL;
    while (g_freeDL.mpPrev != pAnchor) {
        DLNode* p = g_freeDL.mpNext;
        p->mpNext->mpPrev = pAnchor;
        g_freeDL.mpNext = g_freeDL.mpNext->mpNext;
        if (p != pAnchor) {
            p->mpPrev = 0;
            p->mpNext = 0;
        }
        operator_delete__(p);
    }
    RLChunk* pChunk = (RLChunk*)g_pFreeRLChunk;
    while (pChunk) {
        RLChunk* pNext = pChunk->p0;
        operator_delete__(pChunk);
        pChunk = pNext;
    }
    g_pFreeRLChunk = 0;
}

// ===========================================================================
// @ 0x00956fa0  FreeDisplayListEntries (splice a whole list onto the free pool)
// ===========================================================================
void __cdecl FreeDisplayListEntries(DLNode* pList) {
    Mutex* m = (Mutex*)g_mutexHeaps;
    m->Lock(g_scopeHeaps);
    DLNode* pFirst = pList->mpNext;
    if (pFirst != pList) {
        DLNode* pPos = g_freeDL.mpNext;
        DLNode* pBefore = pPos->mpPrev;
        DLNode* pLast = pList->mpPrev;
        pBefore->mpNext = pFirst;
        pFirst->mpPrev = pBefore;
        pLast->mpNext = pPos;
        pPos->mpPrev = pLast;
        pList->mpNext = pList;
        pList->mpPrev = pList;
    }
    m->Unlock();
}

// ===========================================================================
// @ 0x00956ff0  AllocDisplayListEntry
// ===========================================================================
DisplayList* __cdecl AllocDisplayListEntry() {
    Mutex* m = (Mutex*)g_mutexHeaps;
    DisplayList* p = 0;
    m->Lock(g_scopeHeaps);
    DLNode* pAnchor = &g_freeDL;
    if (g_freeDL.mpPrev != pAnchor) {
        p = (DisplayList*)g_freeDL.mpNext;
        p->mpNext->mpPrev = pAnchor;
        g_freeDL.mpNext = g_freeDL.mpNext->mpNext;
        if (p != pAnchor) {
            p->mpPrev = 0;
            p->mpNext = 0;
        }
    }
    m->Unlock();
    if (p == 0)
        p = new("UTFWin/DisplayList", 0, 0, 0, 0) DisplayList;
    p->f1c = 0;
    p->f18 = 0;
    return p;
}

// ===========================================================================
// @ 0x00957080  upper_bound over a sorted uint16 range
// ===========================================================================
const unsigned short* __cdecl FUN_00957080(const unsigned short* first, const unsigned short* last,
                                           const unsigned int* pKey) {
    int n = (int)(last - first);
    while (n > 0) {
        int half = n >> 1;
        const unsigned short* mid = first + half;
        if (!(*pKey < *mid)) {
            first = mid + 1;
            n -= half + 1;
        } else
            n = half;
    }
    return first;
}

// ===========================================================================
// eastl::vector<uint16_t> (runs of a 2D bit mask) and the mask built on it
// ===========================================================================
void* __cdecl operator new(unsigned int, void* p) { return p; }

struct UShortVec {
    unsigned short* mpBegin;
    unsigned short* mpEnd;
    unsigned short* mpCapacity;
    UShortVec& operator=(const UShortVec& x);                                                // 0x957160
    void swap(UShortVec& x);                                                                 // 0x9573e0
    unsigned short* DoAllocateAndCopy(unsigned int n, const unsigned short* first, const unsigned short* last);   // 0x957110
    void DoInsertValue(unsigned short* pPos, const unsigned short& v);                       // 0x6f5bc0
    void push_back(const unsigned short& v) {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) unsigned short(v);
        else
            DoInsertValue(mpEnd, v);
    }
    void clear() {
        unsigned short* pFirst = mpBegin;
        unsigned short* pLast = mpEnd;
        _DoInsertValue_(pFirst, pLast, (int)((char*)mpEnd - (char*)pLast));
        mpEnd -= (pLast - pFirst);
    }
};

unsigned short* UShortVec::DoAllocateAndCopy(unsigned int n, const unsigned short* first, const unsigned short* last) {
    unsigned short* pNew = n ? (unsigned short*)operator_new(n * 2, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    _DoInsertValue_(pNew, (void*)first, (int)((char*)last - (char*)first));
    return pNew;
}

struct HitMask {
    char     pad[0xc];
    int      mWidth;        // +0xc
    int      mHeight;       // +0x10
    UShortVec mRuns;        // +0x14
    bool Contains(const int* pt);                                          // 0x9570c0
    void BuildFromMask(const int* dims, int stride, const unsigned char* data);     // 0x957230
    void BuildFromAlpha(const int* dims, int stride, const unsigned char* data);    // 0x957300
    void BuildAssign(const int* dims, UShortVec* runs);                    // 0x9574c0
};

// @ 0x009570c0  HitMask::Contains
bool HitMask::Contains(const int* pt) {
    if (pt[0] >= 0 && pt[0] < mWidth && pt[1] >= 0 && pt[1] < mHeight) {
        unsigned int idx = pt[1] * mWidth + pt[0];
        const unsigned short* p = FUN_00957080(mRuns.mpBegin, mRuns.mpEnd, &idx);
        return ((p - mRuns.mpBegin) & 1) != 0;
    }
    return false;
}

// ===========================================================================
// @ 0x00957160  UShortVec::operator=
// ===========================================================================
UShortVec& UShortVec::operator=(const UShortVec& x) {
    if (&x != this) {
        const unsigned int n = (unsigned int)(x.mpEnd - x.mpBegin);
        if (n > (unsigned int)(mpCapacity - mpBegin)) {
            unsigned short* pNew = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                operator_delete__(mpBegin);
            mpBegin = pNew;
            mpCapacity = pNew + n;
            mpEnd = pNew + n;
        } else if (n > (unsigned int)(mpEnd - mpBegin)) {
            _DoInsertValue_(mpBegin, x.mpBegin, (int)(mpEnd - mpBegin) * 2);
            _DoInsertValue_(mpEnd, (void*)(x.mpBegin + (mpEnd - mpBegin)),
                            (int)((char*)x.mpEnd - (char*)(x.mpBegin + (mpEnd - mpBegin))));
            mpEnd = mpBegin + n;
        } else {
            _DoInsertValue_(mpBegin, x.mpBegin, (int)((char*)x.mpEnd - (char*)x.mpBegin));
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}

// ===========================================================================
// @ 0x00957230  HitMask::BuildFromMask (non-zero byte => set)
// ===========================================================================
void HitMask::BuildFromMask(const int* dims, int stride, const unsigned char* data) {
    mRuns.clear();
    bool bPrev = false;
    for (int y = 0; y < dims[1]; ++y) {
        for (int x = 0; x < dims[0]; ++x) {
            bool bCur = data[x] != 0;
            if (bCur != bPrev) {
                unsigned short v = (unsigned short)((short)dims[0] * (short)y + (short)x);
                mRuns.push_back(v);
                bPrev = bCur;
            }
        }
        data += stride;
    }
    mWidth = dims[0];
    mHeight = dims[1];
}

// ===========================================================================
// @ 0x00957300  HitMask::BuildFromAlpha (alpha > 0x7f => set; 4 bytes per pixel)
// ===========================================================================
void HitMask::BuildFromAlpha(const int* dims, int stride, const unsigned char* data) {
    mRuns.clear();
    bool bPrev = false;
    for (int y = 0; y < dims[1]; ++y) {
        for (int x = 0; x < dims[0]; ++x) {
            bool bCur = data[x * 4 + 3] > 0x7f;
            if (bCur != bPrev) {
                unsigned short v = (unsigned short)((short)dims[0] * (short)y + (short)x);
                mRuns.push_back(v);
                bPrev = bCur;
            }
        }
        data += stride * 4;
    }
    mWidth = dims[0];
    mHeight = dims[1];
}

// ===========================================================================
// @ 0x009573e0  UShortVec::swap
// ===========================================================================
void UShortVec::swap(UShortVec& x) {
    if ((mpBegin && ((int*)mpBegin)[-1] == 0) || (x.mpBegin && ((int*)x.mpBegin)[-1] == 0)) {
        UShortVec temp;
        unsigned int n = (unsigned int)(mpEnd - mpBegin);
        unsigned short* const pNew = n ? (unsigned short*)operator_new(n * 2, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        unsigned short* const pCap = pNew + n;
        temp.mpBegin = pNew;
        temp.mpCapacity = pCap;
        int nBytes = (int)((char*)mpEnd - (char*)mpBegin);
        unsigned short* pDest = (unsigned short*)_DoInsertValue_(pNew, mpBegin, nBytes);
        temp.mpEnd = pDest + (nBytes >> 1);
        *this = x;
        x = temp;
        if (pNew && ((int*)pNew)[-1] != 0)
            operator_delete__(pNew);
    } else {
        unsigned short* t;
        t = mpBegin; mpBegin = x.mpBegin; x.mpBegin = t;
        t = mpEnd; mpEnd = x.mpEnd; x.mpEnd = t;
        t = mpCapacity; mpCapacity = x.mpCapacity; x.mpCapacity = t;
    }
}

// ===========================================================================
// @ 0x009574c0
// ===========================================================================
void HitMask::BuildAssign(const int* dims, UShortVec* runs) {
    mRuns.swap(*runs);
    mWidth = dims[0];
    mHeight = dims[1];
}

// ===========================================================================
// @ 0x00957530
// ===========================================================================
__declspec(noinline) void __fastcall FUN_00957530(int* self) {
    int* p = (int*)self[1];
    if (p != 0) {
        ((VFn0)Vt(p)[1])(p);
        self[1] = 0;
    }
}

// ===========================================================================
// @ 0x00957550  Object::Release
// ===========================================================================
struct UIObj {
    int   Release();
    void* Cast(unsigned int id);
    void* VirtualDtor(unsigned char flags);
    int*  Ctor(int* p2, int* p3, float* r, int extra);
    void  SetPos(int* p);
    void  GetRect(float* out);
    void  SetRect(float* in);
};

int UIObj::Release() {
    int* self = (int*)this;
    int n = _InterlockedDecrement((volatile long*)((char*)self + 0x28));
    if (n == 0 && self != 0)
        ((VFn1i)Vt(self)[2])(self, 1);
    return n;
}

// ===========================================================================
// @ 0x00957570  Object::Cast
// ===========================================================================
void* UIObj::Cast(unsigned int id) {
    switch (id) {
    case 0xee3f516e: return this;
    case 0x1be6ab3:  return this;
    case 0x2f84737:  return (char*)this + 0x1c;
    case 0xeec58382: return this;
    }
    return 0;
}

// ===========================================================================
// property-copy callbacks (serialization descriptors)
// ===========================================================================
struct IRefObj {
    virtual void AddRef();                          // +0
    virtual void Release();                         // +4
    virtual void v2();
    virtual IRefObj* Cast(unsigned int id);         // +0xc
};
struct SerOps { void* fn[16]; };
struct SerObj { void* vtbl; void* mpData; };
struct SerDesc {
    int f0;
    SerOps* mpOps;                                  // +4
    int f8;
    unsigned short mTypeId;                         // +0xc
    unsigned short f0e;
    unsigned int mOffset;                           // +0x10
    unsigned int mCount;                            // +0x14
};
struct SerValue {
    virtual void* Alloc(unsigned int size, unsigned int align);
    void* mpData;                                   // +4
    unsigned int mCount;                            // +8
};
struct Int2 { int x, y; Int2() {} Int2(const Int2& o) : x(o.x), y(o.y) {} };
struct Float4 {
    float l, t, r, b;
    Float4& operator=(const Float4& o) { l = o.l; t = o.t; r = o.r; b = o.b; return *this; }
};

// @ 0x009575f0  copy an array of intrusive refs (cast to interface 0x1be8ca6)
bool __cdecl FUN_009575f0(SerObj* pDst, SerObj* pSrc, SerDesc* pDesc) {
    IRefObj** pSrcArr = (IRefObj**)pSrc->mpData;
    IRefObj** pDstArr = (IRefObj**)((char*)pDst->mpData + pDesc->mOffset);
    for (unsigned int i = 0; i < pDesc->mCount; ++i) {
        IRefObj* pOld = *pDstArr;
        IRefObj* pNew = 0;
        if (pOld)
            pOld->Release();
        if (*pSrcArr) {
            pNew = (*pSrcArr)->Cast(0x1be8ca6);
            if (pNew)
                pNew->AddRef();
        }
        *pDstArr = pNew;
        ++pDstArr;
        ++pSrcArr;
    }
    return true;
}

// @ 0x009576f0  invoke the descriptor's setter (ops slot 4) with the source value
typedef void (__thiscall *SetterFn)(void* pObj, void* pValue);
bool __cdecl FUN_009576f0(SerObj* pDst, SerObj* pSrc, SerDesc* pDesc) {
    ((SetterFn)pDesc->mpOps->fn[4])(pDst->mpData, pSrc->mpData);
    return true;
}

// @ 0x00957710  read an Int2 array property through the getter (ops slot 3)
typedef Int2 (__thiscall *GetInt2Fn)(void* pObj);
bool __cdecl FUN_00957710(SerObj* a, SerObj* pObj, SerDesc* pDesc, SerValue* pOut) {
    void* pTarget = pObj->mpData;
    SerOps* pOps = pDesc->mpOps;
    Int2* pDest = (Int2*)pOut->Alloc(pDesc->mCount * 8, 4);
    if (pDest) {
        Int2 v = ((GetInt2Fn)pOps->fn[3])(pTarget);
        *pDest = v;
        pOut->mpData = pDest;
        pOut->mCount = pDesc->mCount;
        *(void**)pOut = g_pSerTypeTable[pDesc->mTypeId & 0xfff];
    }
    return true;
}

// ===========================================================================
// @ 0x00957790
// ===========================================================================
void UIObj::SetPos(int* p) {
    char* self = (char*)this;
    *(int*)(self + 0x1c) = p[0];
    *(int*)(self + 0x20) = p[1];
}

// ===========================================================================
// @ 0x009577b0
// ===========================================================================
void UIObj::GetRect(float* out) {
    char* self = (char*)this;
    float x = *(float*)(self + 0xc);
    float h = *(float*)(self + 0x14);
    float y = *(float*)(self + 0x10);
    float w = *(float*)(self + 0x18);
    out[0] = x;
    out[1] = y;
    out[2] = h + x;
    out[3] = w + y;
}

// ===========================================================================
// @ 0x009577f0
// ===========================================================================
void UIObj::SetRect(float* in) {
    char* self = (char*)this;
    *(float*)(self + 0xc) = in[0];
    *(float*)(self + 0x10) = in[1];
    *(float*)(self + 0x14) = in[2] - in[0];
    *(float*)(self + 0x18) = in[3] - in[1];
}

// ===========================================================================
// @ 0x00957850
// ===========================================================================
void __fastcall FUN_00957850(int* self) {
    self[0] = 0x144064c;
    if (self[1] != 0) {
        ((VFn0)Vt((void*)self[1])[1])((void*)self[1]);
        self[1] = 0;
    }
    self[0] = 0x13eb938;
}

// ===========================================================================
// @ 0x00957880
// ===========================================================================
void** __cdecl FUN_00957880(int a, int b) {
    if ((g_166b134 & 1) == 0) {
        g_166b134 |= 1;
        *(int*)0x154ede4 = a;
        *(int*)0x154ede8 = b;
        *(int*)0x154edec = 0;
    }
    return (void**)0x154edd8;
}

// ===========================================================================
// @ 0x009578c0  read a Float4 (rect) array property through the getter (ops slot 3)
// ===========================================================================
typedef Float4 (__thiscall *GetFloat4Fn)(void* pObj);
bool __cdecl FUN_009578c0(SerObj* a, SerObj* pObj, SerDesc* pDesc, SerValue* pOut) {
    void* pTarget = pObj->mpData;
    SerOps* pOps = pDesc->mpOps;
    Float4* pDest = (Float4*)pOut->Alloc(pDesc->mCount << 4, 4);
    if (pDest) {
        Float4 v = ((GetFloat4Fn)pOps->fn[3])(pTarget);
        *pDest = v;
        pOut->mpData = pDest;
        pOut->mCount = pDesc->mCount;
        *(void**)pOut = g_pSerTypeTable[pDesc->mTypeId & 0xfff];
    }
    return true;
}

// ===========================================================================
// @ 0x00957940  Object::_virtual_dtor
// ===========================================================================
void* UIObj::VirtualDtor(unsigned char flags) {
    int* self = (int*)this;
    self[0] = 0x144064c;
    if (self[1] != 0) {
        ((VFn0)Vt((void*)self[1])[1])((void*)self[1]);
        self[1] = 0;
    }
    self[0] = 0x13eb938;
    if (flags & 1)
        operator_delete__(self);
    return self;
}

// ===========================================================================
// @ 0x00957980  UI::Image ctor
// ===========================================================================
int* UIObj::Ctor(int* p2, int* p3, float* r, int extra) {
    int* self = (int*)this;
    self[0] = 0x144064c;
    _InterlockedExchange((volatile long*)(self + 10), 0);
    self[1] = (int)p2;
    if (p2 != 0)
        ((VFn0)Vt(p2)[0])(p2);
    self[7] = p3[0];
    self[8] = p3[1];
    *(float*)(self + 3) = r[0];
    *(float*)(self + 4) = r[1];
    *(float*)(self + 5) = r[2] - r[0];
    *(float*)(self + 6) = r[3] - r[1];
    self[9] = extra;
    return self;
}
