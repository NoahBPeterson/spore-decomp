// Slice s00eea7c0: an internal Spore UI "color gradient / curve editor view"
// (the class is unnamed in the public PDB; its ctor writes the three vtables
// 0x148ad1c / 0x148ad00 / 0x148acf0). It owns a layout and a set of ref-counted
// child windows, plus a sorted list of control points ("Entry"), each with a
// normalized position and an RGB color. The functions interpolate the color along
// the sorted points, show/hide the child windows, and rebuild the point list from
// an input record. (0xeea7c0-0xeeb764)
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <intrin.h>

struct View;  struct Entry;
struct Vec3 { float x, y, z; };

// cSPUILayout: ref-counted layout object; +0x04 Release, +0x08 Shutdown.
struct IWindow;
class cSPUILayout { public:
    virtual void V0() {}
    virtual void Release() {}
    virtual void Shutdown() {}
    uint8_t  Init(const void* pKey, uint8_t a, uint32_t id);              // 0x8120d0
    uint8_t  SetParentWin(IWindow* pWin, uint8_t a, uint32_t id);         // 0x8121b0
    IWindow* FindWindowByID(uint32_t id, uint8_t recurse) const;          // 0x8105b0
    void     Shutdown(uint32_t a);                                       // 0x811ad0 (non-virtual)
};

// ------------------------------------------------------------------ callees
cSPUILayout* MakeLayout();                                                       // 0x810000

void*  EAAllocate(uint32_t size, const char* pTag, int a, int b, int c, int d);  // 0xf473a0
void   RemoveHandler(void* a, void* b, void* c, void* d, void* e);               // 0x571db0
void*  MessageServer();                                                          // 0x67dcc0
void   SetIRefCount(void* msg, int a, void* p);                                  // 0x5726e0

uint32_t ColorRGBToU32(const float* pColor);            // 0x458a40
float*   ColorToVector3(float* out, uint32_t c);        // 0x576ab0
int      Snprintf16(uint16_t* buf, int n, const wchar_t* fmt, ...); // 0x939a30
void     FUN_00881ed0(double d, char* buf, int n, int a);           // 0x881ed0
void     FUN_00efbbe0(int a, int b);                                // 0xefbbe0
void     FUN_00bbe970(void* b, void* e);                            // 0xbbe970
void     FUN_00b90a40(void* b, void* e);                            // 0xb90a40
void     FUN_00e26410(void* b, void* e, int depth, int cmp);        // 0xe26410
void     FUN_00e25bd0(void* b, void* e);                            // 0xe25bd0 (vector erase)
void     FUN_00aea5d0(void* pEnd, void** pValue);                   // 0xaea5d0 (vector push)
struct RawVec { void* begin; void* end; void* cap;
                void dtor(); void erase(void* b, void* e); };      // 0xae6970 / 0xe25bd0

// local constants
static const float kOne  = 1.0f;      // 0x1485720
static const float kHalf = 0.5f;      // 0x1471064
static const float kDefR = 0.3254902f;
static const float kDefG = 0.3254902f;
static const float kDefB = 0.3254902f;

// ------------------------------------------------------------------ interfaces
// IWindow: the game's UI window interface. Only the vtable slots this slice
// reaches are named; the numbered stubs keep the offsets right.
// +0x04 Release, +0x08 (Shutdown) are inherited from the ref-counted base.
struct IWindow {
    virtual void  AddRef() {}
    virtual void  Release() {}
    virtual void  Shutdown() {}
    virtual void  V3()  {}
    virtual void  V4()  {} virtual void V5()  {} virtual void V6()  {} virtual void V7()  {}
    virtual void  V8()  {} virtual void V9()  {} virtual void V10() {} virtual void V11() {}
    virtual void  V12() {} virtual void V13() {}
    virtual float* GetBox() { return 0; }                     // 0x38
    virtual void  V15() {} virtual void V16() {} virtual void V17() {} virtual void V18() {}
    virtual void  V19() {} virtual void V20() {} virtual void V21() {} virtual void V22() {}
    virtual void  SetColor(uint32_t) {}                       // 0x5c
    virtual void  V24() {} virtual void V25() {} virtual void V26() {} virtual void V27() {}
    virtual void  V28() {} virtual void V29() {}
    virtual void  SetTextId(uint32_t) {}                      // 0x78
    virtual void  V31() {}
    virtual void  SetText(const void*) {}                     // 0x80
    virtual void  V33() {} virtual void V34() {} virtual void V35() {}
    virtual void  V90() {}                                    // 0x90
    virtual void  V37() {} virtual void V38() {} virtual void V39() {} virtual void V40() {}
    virtual void  V41() {} virtual void V42() {} virtual void V43() {} virtual void V44() {}
    virtual void  V45() {} virtual void V46() {} virtual void V47() {} virtual void V48() {}
    virtual void  V49() {} virtual void V50() {} virtual void V51() {} virtual void V52() {}
    virtual void  V53() {} virtual void V54() {} virtual void V55() {} virtual void V56() {}
    virtual void  V57() {} virtual void V58() {} virtual void V59() {} virtual void V60() {}
    virtual void  V61() {} virtual void V62() {} virtual void V63() {} virtual void V64() {}
    virtual void  Show(void*) {}                               // 0x104
    virtual void  Hide(void*) {}                               // 0x108
};

// Generic window-ish object reached through Entry::mWinA (slot 0x0c = AsInterface,
// slot 0x28 = a 2-arg command).
struct IWinObj {
    virtual void  V0() {}
    virtual void  V1() {}
    virtual void  V2() {}
    virtual void* AsInterface(uint32_t id) { return 0; }        // 0x0c
    virtual void  V4() {} virtual void V5() {} virtual void V6() {} virtual void V7() {}
    virtual void  V8() {} virtual void V9() {}
    virtual void  Cmd(uint32_t a, uint32_t b) {}                // 0x28
};

// Ref-counted object: +0x04 Release, +0x08 Shutdown.
struct IRefObj {
    virtual void V0() {}
    virtual void Release() {}
    virtual void Shutdown() {}
};

// thiscall vtable-call helper for a class with an opaque vtable at *p
// (member-function-pointer form: MSVC passes `this` in ecx, no stack push).
template <class T, int Off>
static inline void vcallv(T* p) {
    typedef void (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn;
    (p->*f)();
}
template <class T, int Off, class A>
static inline void vcallA(T* p, A a) {
    typedef void (T::*PMF)(A);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn;
    (p->*f)(a);
}

// Slice helpers (defined at the bottom) — forward decls.

// ------------------------------------------------------------------ Entry
// Control point: ref-counted; primary vtable 0x148acb8, secondary 0x148aca8.
struct Entry {
    void**   mpVtbl;      // +0x00 -> 0x148acb8
    void*    mRefVtbl;    // +0x04 -> 0x148aca8 (RefCountVTemplate<int>)
    int      mRefCount;   // +0x08
    int      mUnk0c;      // +0x0c
    int      mUnk10;      // +0x10
    void*    mWinA;       // +0x14  (IWindow*, matched against an id)
    void*    mWinB;       // +0x18  (IWindow*, matched against an id)
    int      mUnk1c;      // +0x1c
    int      mUnk20;      // +0x20
    void*    mLayout;     // +0x24  (used as the cSPUILayout* for FindWindowByID)
    int      mUnk28;      // +0x28
    uint8_t  mUnk2c;      // +0x2c
    float    mPos;        // +0x30  (sort key, normalized 0..1)
    float    mColorR;     // +0x34
    float    mColorG;     // +0x38
    float    mColorB;     // +0x3c
    uint8_t  mUnk40;      // +0x40
    uint8_t  mUnk41;      // +0x41
    int      mUnk44;      // +0x44
    int      mUnk48;      // +0x48
    float    mUnk4c;      // +0x4c
    uint8_t  mUnk50;      // +0x50

    void SetColor(float r, float g, float b);            // 0xeea190
    void Ctor();                                         // 0xee9be0
};
typedef Entry* EntryPtr;

// ------------------------------------------------------------------ View
struct View {
    void**   mpVtbl0;        // +0x00 -> 0x148ad1c
    void*    mpVtbl1;        // +0x04 -> 0x148ad00
    void*    mpVtbl2;        // +0x08 -> 0x148acf0
    int      mUnk0c;         // +0x0c
    IWindow* mWinParent;     // +0x10
    IRefObj* mAssetView;     // +0x14  (ref-counted asset view)
    IWindow* mWinB;          // +0x18
    IWindow* mWinRenderWindow;      // +0x1c
    IWindow* mWinBakingIndicator;   // +0x20
    cSPUILayout* mLayout;    // +0x24
    void*    mMsgServer;     // +0x28
    void*    mMsgTarget;     // +0x2c
    void*    mMsgIds;        // +0x30 -> 0x148ad44 (3 u32 ids)
    uint32_t mMsgCount;      // +0x34 (=3)
    uint32_t mMsgUser;       // +0x38 (=0)
    Entry**  mEntriesBegin;  // +0x3c
    Entry**  mEntriesEnd;    // +0x40
    Entry**  mEntriesCap;    // +0x44
    uint8_t  mUnk48[8];      // +0x48
    void*    mLayout2;       // +0x50  (ref-counted)
    float    mUnk54;         // +0x54
    float    mUnk58;         // +0x58

    // slice methods
    void     ShowChildren(uint8_t visible);              // 0xeea7c0
    void     OnAssetChanged(void* pChanged);             // 0xeea860
    Entry*   FindByWinID(void* id);                      // 0xeea8b0
    uint8_t  HasWin(void* id);                           // 0xeea8e0
    void     SetEntryColor(void* id, float r, float g, float b); // 0xeea910
    void     Dtor();                                     // 0xeea960
    uint8_t  DoMessage(uint32_t msgId, void* msg);       // 0xeeaa40
    void     GetEntryColor(float* pOut, void* id);       // 0xeeaa90
    void*    Ctor();                                     // 0xeeab00
    void     SampleColor(float* pOut, float x);          // 0xeeab90
    void     Bake(void* pTarget);                        // 0xeeacc0
    void     ShutdownView();                             // 0xeeae70
    void     Rebuild(uint8_t notify);                    // 0xeeaf00
    uint8_t  Init(IWindow* pParent);                     // 0xeeb280
    void     SetPoints(int* pPositions, int* pColors);   // 0xeeb580
    void     NotifyEntryChanged();                       // 0xeea260
};

// ================================================================== functions

// @ 0x00eea7c0
void View::ShowChildren(uint8_t visible)
{
    if (this->mLayout != 0) {
        IWindow* w = this->mLayout->FindWindowByID(0xf68ddb49, 1);
        if (w != 0) {
            if (visible) w->Show((uint8_t*)this + 4);
            else         w->Hide((uint8_t*)this + 4);
        }
        IWindow* wb = this->mWinB;
        if (wb != 0) {
            if (visible) wb->Show((uint8_t*)this + 4);
            else         wb->Hide((uint8_t*)this + 4);
        }
        IWindow* av = (IWindow*)this->mAssetView;
        if (av != 0) {
            if (visible) av->Show((uint8_t*)this + 4);
            else         av->Hide((uint8_t*)this + 4);
        }
    }
    Entry** it = this->mEntriesBegin;
    while (it != this->mEntriesEnd) {
        Entry* e = *it;
        vcallA<Entry, 0x28>(e, visible);
        ++it;
    }
}

// @ 0x00eea860
void View::OnAssetChanged(void* pChanged)
{
    Entry** it = this->mEntriesBegin;
    if (it != this->mEntriesEnd) {
        do {
            IWinObj* v = (IWinObj*)(*it)->mWinA;
            if (v != 0 && (void*)v != pChanged) {
                IWinObj* q = (IWinObj*)v->AsInterface(0x8ed27e7a);
                if (q != 0) {
                    q->Cmd(4, 0);
                }
            }
            ++it;
        } while (it != this->mEntriesEnd);
    }
}

// @ 0x00eea8b0
Entry* View::FindByWinID(void* id)
{
    Entry** it = this->mEntriesBegin;
    Entry** end = this->mEntriesEnd;
    while (it != end) {
        Entry* e = *it;
        if (e->mWinB == id) return e;
        if (e->mWinA == id) return e;
        ++it;
    }
    return 0;
}

// @ 0x00eea8e0
uint8_t View::HasWin(void* id)
{
    Entry** it = this->mEntriesBegin;
    Entry** end = this->mEntriesEnd;
    while (it != end) {
        if ((*it)->mWinA == id) return 1;
        ++it;
    }
    return 0;
}

// @ 0x00eea910
void View::SetEntryColor(void* id, float r, float g, float b)
{
    Entry** it = this->mEntriesBegin;
    Entry** end = this->mEntriesEnd;
    while (it != end) {
        Entry* e = *it;
        if (e->mWinA == id) {
            e->SetColor(r, g, b);
            return;
        }
        ++it;
    }
}
// @ 0x00eea960
void View::Dtor()
{
    void** v = (void**)this;
    v[0] = (void*)0x148ad1c;
    v[1] = (void*)0x148ad00;
    v[2] = (void*)0x148acf0;
    if (this->mLayout2 != 0) {
        ((IRefObj*)this->mLayout2)->Release();
    }
    ((RawVec*)&this->mEntriesBegin)->dtor();
    if (this->mMsgServer != 0) {
        void* h = this->mMsgServer;
        this->mMsgServer = 0;
        RemoveHandler(h, this->mMsgTarget, this->mMsgIds,
                      (void*)(uintptr_t)this->mMsgCount, (void*)(uintptr_t)this->mMsgUser);
    }
    if (this->mLayout != 0)             vcallv<cSPUILayout, 8>(this->mLayout);
    if (this->mWinBakingIndicator != 0) this->mWinBakingIndicator->Release();
    if (this->mWinRenderWindow != 0)    this->mWinRenderWindow->Release();
    if (this->mWinB != 0)               this->mWinB->Release();
    if (this->mAssetView != 0)          this->mAssetView->Release();
    if (this->mWinParent != 0)          this->mWinParent->Release();
    this->mpVtbl2 = (void*)0x13ec458;
    this->mpVtbl1 = (void*)0x13eb938;
    this->mpVtbl0 = (void**)0x13eb394;
}

// @ 0x00eeaa40
uint8_t View::DoMessage(uint32_t msgId, void* msg)
{
    switch (msgId) {
    case 0x7e19b84: {
        void* p = *(void**)((uint8_t*)msg + 8);
        if (p != 0) {
            OnAssetChanged(p);
        }
        break;
    }
    case 0xd69290d7:
    case 0xd69290d8:
        {
            IWindow* w = this->mWinB;
            if (w != 0) {
                w->V90();
            }
        }
        break;
    }
    return 0;
}

// @ 0x00eeaa90
void View::GetEntryColor(float* pOut, void* id)
{
    Entry** it = this->mEntriesBegin;
    Entry** end = this->mEntriesEnd;
    while (it != end) {
        Entry* e = *it;
        if (e->mWinA == id) {
            pOut[0] = e->mColorR;
            pOut[1] = e->mColorG;
            pOut[2] = e->mColorB;
            return;
        }
        ++it;
    }
    *(Vec3*)pOut = *(Vec3*)0x15ac870;
}

// @ 0x00eeab00
void* View::Ctor()
{
    View* p = this;
    p->mpVtbl1 = (void*)0x14426a0;   // base cSPScenarioModeSporepediaLargeAssetView
    p->mpVtbl2 = (void*)0x13ec458;   // RefCountVTemplate<int>
    p->mUnk0c = 0;
    p->mpVtbl0 = (void**)0x148ad1c;
    p->mpVtbl1 = (void*)0x148ad00;
    p->mpVtbl2 = (void*)0x148acf0;
    p->mWinParent = 0;
    p->mAssetView = 0;
    p->mWinB = 0;
    p->mWinRenderWindow = 0;
    p->mWinBakingIndicator = 0;
    p->mLayout = 0;
    p->mMsgServer = 0;
    p->mMsgTarget = 0;
    p->mMsgIds = 0;
    p->mMsgCount = 0;
    p->mMsgUser = 0;
    p->mEntriesBegin = 0;
    p->mEntriesEnd = 0;
    p->mEntriesCap = 0;
    p->mLayout2 = 0;
    p->mUnk54 = 0.0f;
    p->mUnk58 = 0.0f;
    return p;
}

// @ 0x00eeab90
void View::SampleColor(float* pOut, float x)
{
    Entry** begin = this->mEntriesBegin;
    int nbytes = (int)(this->mEntriesEnd - begin);
    int n = nbytes >> 2;
    if (n == 0) {
        pOut[0] = *(float*)0x16c78a8;
        pOut[1] = *(float*)0x16c78ac;
        pOut[2] = *(float*)0x16c78b0;
        return;
    }
    int i = 0;
    if ((nbytes & 0xfffffffc) > 0) {
        do {
            Entry* e = begin[i];
            if (e->mPos > x) {
                break;
            }
            ++i;
        } while (i < n);
        if (i < n) {
            if (i == 0) {
                Entry* e = begin[0];
                pOut[0] = e->mColorR; pOut[1] = e->mColorG; pOut[2] = e->mColorB;
                return;
            }
            Entry* lo = begin[i - 1];
            Entry* hi = begin[i];
            float t = (x - lo->mPos) / (hi->mPos - lo->mPos);
            pOut[0] = (hi->mColorR - lo->mColorR) * t + lo->mColorR;
            pOut[1] = (hi->mColorG - lo->mColorG) * t + lo->mColorG;
            pOut[2] = (hi->mColorB - lo->mColorB) * t + lo->mColorB;
            return;
        }
    }
    Entry* e = begin[n - 1];
    pOut[0] = e->mColorR; pOut[1] = e->mColorG; pOut[2] = e->mColorB;
}

// @ 0x00eeacc0
void View::Bake(void* pTarget)
{
    if (this->mWinB != 0) {
        float* box = this->mWinB->GetBox();
        float y0 = box[1];
        int count = (int)(box[3] - y0);
        float x0 = -box[0];
        float ybaseA = x0 + box[0];
        float ybase = -y0 + y0;
        float xOrigin = box[2] + x0;
        if (count > 0) {
            int denom = count - 1;
            for (int i = 0; i < count; ++i) {
                float col[3];
                SampleColor(col, (float)i / (float)denom);
                uint32_t c = ColorRGBToU32(col);
                void** vt = *(void***)pTarget;
                ((void (*)(void*, uint32_t))vt[1])(pTarget, c);
                float yTop = ybase + (float)i;
                float yBot = yTop + 1.0f;
                float pa[4] = { x0, ybase, yBot, x0 + box[0] };
                float pb[4] = { x0, ybase, yBot, yBot };
                float pc[4] = { xOrigin, ybaseA, ybaseA, yBot };
                ((void (*)(void*, float*, float*, float*, uint32_t*))vt[0x3c / 4])(pTarget, pa, pb, pc, &c);
            }
        }
    }
    if (this->mWinRenderWindow != 0) {
        float col[3];
        SampleColor(col, 0.0f);
        this->mWinRenderWindow->SetColor(ColorRGBToU32(col));
    }
    if (this->mWinBakingIndicator != 0) {
        float col[3];
        SampleColor(col, 1.0f);
        this->mWinBakingIndicator->SetColor(ColorRGBToU32(col));
    }
}

// @ 0x00eeae70
void View::ShutdownView()
{
    vcallA<View, 0x1c>(this, 0u);
    Entry** it = this->mEntriesBegin;
    if (it != this->mEntriesEnd) {
        do {
            vcallv<Entry, 0x20>(*it);
            ++it;
        } while (it != this->mEntriesEnd);
    }
    RawVec* vec = (RawVec*)&this->mEntriesBegin;
    vec->erase(vec->begin, vec->end);    if (this->mMsgServer != 0) {
        void* h = this->mMsgServer;
        this->mMsgServer = 0;
        RemoveHandler(h, this->mMsgTarget, this->mMsgIds,
                      (void*)(uintptr_t)this->mMsgCount, (void*)(uintptr_t)this->mMsgUser);
    }
    if (this->mWinParent != 0) {
        IWindow* q = this->mWinParent;
        this->mWinParent = 0;
        q->Release();
    }
    if (this->mLayout != 0) {
        this->mLayout->Shutdown(1u);
    }
}

// @ 0x00eeaf00
void View::Rebuild(uint8_t notify)
{
    bool added = false;
    Entry** begin = this->mEntriesBegin;
    Entry** end = this->mEntriesEnd;
    int n = (int)(end - begin);
    float x = 0.0f;
    float colR, colG, colB;

    if (n == 0) {
        colR = kDefR; colG = kDefG; colB = kDefB;
    } else if (n == 1) {
        Entry* e = begin[0];
        x = (e->mPos < kHalf) ? kOne : 0.0f;
        if (notify) {
            colR = e->mColorR; colG = e->mColorG; colB = e->mColorB;
        } else {
            uint32_t c = 0xffebd870;
            float* v = ColorToVector3(&colR, c);
            colR = v[0]; colG = v[1]; colB = v[2];
        }
        added = true;
    } else {
        float best = 0.0f;
        int bestIdx = 0;
        for (int i = 0; i <= n; ++i) {
            float hi = (i < n) ? begin[i]->mPos : kOne;
            float lo = (i > 0) ? begin[i - 1]->mPos : 0.0f;
            float d = hi - lo;
            if (d > best) { best = d; bestIdx = i; }
        }
        if (bestIdx == 0) {
            Entry* e = begin[0];
            colR = e->mColorR; colG = e->mColorG; colB = e->mColorB;
        } else if (bestIdx == n) {
            Entry* e = begin[n - 1];
            colR = e->mColorR; colG = e->mColorG; colB = e->mColorB;
            x = kOne;
        } else {
            Entry* lo = begin[bestIdx - 1];
            Entry* hi = begin[bestIdx];
            x = best * kHalf + lo->mPos;
            colR = (hi->mColorR - lo->mColorR) * kHalf + lo->mColorR;
            colG = (hi->mColorG - lo->mColorG) * kHalf + lo->mColorG;
            colB = (hi->mColorB - lo->mColorB) * kHalf + lo->mColorB;
        }
        added = true;
    }

    if (x < 0.0f || x > kOne) return;

    Entry* pEntry;
    void* p = EAAllocate(0x54, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (p != 0) { ((Entry*)p)->Ctor(); pEntry = (Entry*)p; } else pEntry = 0;

    ((void (*)(Entry*, void*, float, float, float, View*))((*(void***)pEntry)[0x1c / 4]))
        (pEntry, this->mAssetView, x, colR, colG, this);
    ((void (*)(Entry*, int))((*(void***)pEntry)[0x28 / 4]))(pEntry, 1);
    ((void (*)(Entry*))((*(void***)pEntry)[0]))(pEntry);

    if (this->mEntriesEnd < this->mEntriesCap) {
        *this->mEntriesEnd = pEntry;
        ++this->mEntriesEnd;
        ((void (*)(Entry*))((*(void***)pEntry)[0]))(pEntry);
    } else {
        EntryPtr tmp = pEntry;
        FUN_00aea5d0(this->mEntriesEnd, (void**)&tmp);
        pEntry = tmp;
    }
    ((void (*)(Entry*))((*(void***)pEntry)[4 / 4]))(pEntry);

    if (added) {
        NotifyEntryChanged();
    }
    if (notify) {
        void* ms = MessageServer();
        ((void (*)(void*, uint32_t, void*, void*))(((void**)*(void***)ms)[0x14 / 4]))(ms, 0xd69290d7, 0, 0);
    }
}

// @ 0x00eeb280
uint8_t View::Init(IWindow* pParent)
{
    if (pParent != this->mWinParent) {
        if (pParent != 0) pParent->AddRef();
        IWindow* old = this->mWinParent;
        this->mWinParent = pParent;
        if (old != 0) old->Release();
    }
    if (this->mLayout2 != 0) {
        IRefObj* q = (IRefObj*)this->mLayout2;
        this->mLayout2 = 0;
        q->Release();
    }
    if (this->mWinB != 0) {
        IWindow* q = this->mWinB;
        this->mWinB = 0;
        q->Release();
    }
    FUN_00e25bd0(this->mEntriesBegin, this->mEntriesEnd);

    if (this->mWinParent != 0) {
        void* layout;
        void* p = EAAllocate(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (p != 0) layout = MakeLayout(); else layout = 0;
        if (layout != this->mLayout) {
            if (layout != 0) ((IRefObj*)layout)->Release();
            cSPUILayout* old = this->mLayout;
            this->mLayout = (cSPUILayout*)layout;
            if (old != 0) old->Shutdown();
        }
        if (!this->mLayout->Init((const void*)0x15ac93c, 0, 0x5b598fa)) {
            vcallA<cSPUILayout, 8>(this->mLayout, (uint32_t)1);
            cSPUILayout* q = this->mLayout;
            if (q != 0) {
                this->mLayout = 0;
                q->Shutdown();
            }
            return 0;
        }
        this->mLayout->SetParentWin(this->mWinParent, 1, 0x5b598fa);

        this->mAssetView = (IRefObj*)this->mLayout->FindWindowByID(0xf68ddb4a, 1);
        if (this->mAssetView != 0) {
            ((IWindow*)this->mAssetView)->SetTextId(0x7e4330b);
        }
        this->mWinB = this->mLayout->FindWindowByID(0x168f59fc, 1);
        this->mWinRenderWindow = this->mLayout->FindWindowByID(0x7e23962, 1);
        this->mWinBakingIndicator = this->mLayout->FindWindowByID(0x7e23963, 1);

        char buf[0x80];
        FUN_00881ed0(*(double*)0x148ad68, buf, 0x40, 0);
        IWindow* w = this->mLayout->FindWindowByID(0x7ed9118, 1);
        if (w != 0) {
            uint16_t s[0x40];
            Snprintf16(s, 0x40, (const wchar_t*)0x148ad5c, buf);
            w->SetText(s);
        }
        w = this->mLayout->FindWindowByID(0x7ed9120, 1);
        if (w != 0) {
            uint16_t s[0x40];
            Snprintf16(s, 0x40, (const wchar_t*)0x148ad50, buf);
            w->SetText(s);
        }
    }

    void* ms = MessageServer();
    this->mMsgServer = ms;
    this->mMsgTarget = this;
    this->mMsgIds = (void*)0x148ad44;
    this->mMsgCount = 3;
    this->mMsgUser = 0;
    if (ms != 0) {
        for (uint32_t i = 0; i < 0xc; i += 4) {
            uint32_t id = *(uint32_t*)((uint8_t*)0x148ad44 + i);
            ((void (*)(void*, void*, uint32_t))(((void**)*(void***)ms)[0x24 / 4]))(ms, this, id);
        }
    }
    Rebuild(0);
    Rebuild(0);
    return 1;
}

// @ 0x00eeb580
void View::SetPoints(int* pPositions, int* pColors)
{
    int n = (pPositions[1] - pPositions[0]) >> 2;
    int m = (pColors[1] - pColors[0]) / 0xc;
    if (n != m || n == 0) return;

    Entry** it = this->mEntriesBegin;
    Entry** end = this->mEntriesEnd;
    while (it != end) {
        vcallv<Entry, 0x20>(*it);
        ++it;
    }
    FUN_00e25bd0(this->mEntriesBegin, this->mEntriesEnd);

    for (int i = 0; i < n; ++i) {
        Entry* pEntry;
        void* p = EAAllocate(0x54, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (p != 0) { ((Entry*)p)->Ctor(); pEntry = (Entry*)p; } else pEntry = 0;

        float* col = (float*)(pColors[0] + i * 0xc);
        float x = ((float*)pPositions[0])[i];
        ((void (*)(Entry*, void*, float, float, float, View*))((*(void***)pEntry)[0x1c / 4]))
            (pEntry, this->mAssetView, x, col[0], col[1], this);
        ((void (*)(Entry*, int))((*(void***)pEntry)[0x28 / 4]))(pEntry, 1);
        ((void (*)(Entry*))((*(void***)pEntry)[0]))(pEntry);

        if (this->mEntriesEnd < this->mEntriesCap) {
            *this->mEntriesEnd = pEntry;
            ++this->mEntriesEnd;
            ((void (*)(Entry*))((*(void***)pEntry)[0]))(pEntry);
        } else {
            EntryPtr tmp = pEntry;
            FUN_00aea5d0(this->mEntriesEnd, (void**)&tmp);
            pEntry = tmp;
        }
        ((void (*)(Entry*))((*(void***)pEntry)[4 / 4]))(pEntry);
    }

    Entry** b = this->mEntriesBegin;
    Entry** e = this->mEntriesEnd;
    if (b != e) {
        int cnt = (int)(e - b);
        int depth = 0;
        for (int k = cnt; k != 0; k >>= 1) ++depth;
        FUN_00e26410(b, e, depth * 2 - 2, 0xeea760);
        if (cnt <= 0x1c) {
            FUN_00bbe970(b, e);
        } else {
            FUN_00bbe970(b, (void*)((uint8_t*)b + 0x70));
            FUN_00b90a40((void*)((uint8_t*)b + 0x70), e);
        }
    }

    if (this->mWinB != 0) {
        this->mWinB->V90();
    }
}

// ------------------------------------------------------------------ helpers

// @ 0x00ee9be0
void Entry::Ctor()
{
    this->mRefVtbl = (void*)0x13ec458;
    this->mRefCount = 0;
    this->mpVtbl = (void**)0x148acb8;
    this->mRefVtbl = (void*)0x148aca8;
    this->mRefCount = 0;
    this->mUnk0c = 0;
    this->mUnk10 = 0;
    this->mWinA = 0;
    this->mWinB = 0;
    this->mUnk1c = 0;
    this->mUnk20 = 0;
    this->mLayout = 0;
    this->mUnk28 = 0;
    this->mUnk2c = 0;
    this->mPos = 0.0f;
    this->mColorR = *(float*)0x15ac834;
    this->mColorG = *(float*)0x15ac838;
    this->mColorB = *(float*)0x15ac83c;
    this->mUnk40 = 0;
    this->mUnk41 = 0;
    this->mUnk4c = 0.0f;
    this->mUnk50 = 0;
}

// @ 0x00eea260
void View::NotifyEntryChanged()
{
    if (this->mAssetView == 0) return;
    void* p = EAAllocate(0x40, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (p == 0) return;
    void* msg = p;
    *(int*)((uint8_t*)msg + 0x30) = 0;
    *(void**)msg = (void*)0x13eb90c;
    _InterlockedExchange((volatile long*)((uint8_t*)msg + 4), 0);
    *(void**)msg = (void*)0x13eb844;
    *(int*)((uint8_t*)msg + 0x38) = 0;
    ((void (*)(void*))(((void**)*(void***)msg)[1]))(msg);
    *(int*)((uint8_t*)msg + 0x30) = 0x7e19b84;
    SetIRefCount(msg, 0, this->mAssetView);
    void* ms = MessageServer();
    void* id = (void*)(unsigned)*(int*)((uint8_t*)msg + 0x30);
    ((void (*)(void*, void*, void*, void*))(((void**)*(void***)ms)[0x14 / 4]))(ms, id, msg, 0);
    ((void (*)(void*))(((void**)*(void***)msg)[2]))(msg);
}

// @ 0x00eea190  (Entry::SetColor)
void Entry::SetColor(float r, float g, float b)
{
    if (this->mColorR != r || this->mColorG != g || this->mColorB != b) {
        this->mColorR = r;
        this->mColorG = g;
        this->mColorB = b;
        void* ms = MessageServer();
        ((void (*)(void*, uint32_t, void*, void*))(((void**)*(void***)ms)[0x14 / 4]))(ms, 0xd69290d7, 0, 0);
    }
    FUN_00efbbe0(0x96, 0x97);
    if (this->mLayout != 0) {
        uint32_t c = ColorRGBToU32(&this->mColorR);
        IWindow* w = ((cSPUILayout*)this->mLayout)->FindWindowByID(0x7e099a4, 1);
        if (w != 0) {
            ((void (*)(IWindow*, uint32_t))(((void**)*(void***)w)[0x5c / 4]))(w, c);
        }
    }
}

// @ 0x00eea760  (sort predicate)
bool Entry_PosGreater(Entry* a, Entry* b)
{
    if (a->mPos <= b->mPos && b->mPos != a->mPos) return true;
    return false;
}
