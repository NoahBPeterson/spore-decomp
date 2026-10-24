// Slice s0097f390 -- EA::UTFWinControls WinMessageBox, ModulateEffect/Navigator/PerspectiveEffect
// factory helpers (0x0097fb40..0x00980680, 17 functions).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
//
// Layout notes (retail):
//   WinMessageBox has base vptrs at +0, +4 (IWindow), +0x20c (IWinDialog) and a tail
//   sub-object at +0x338 (IWinMessageBox).  The tail methods SetMessageText / InitButton /
//   RemoveAll are entered with `this` == WinMessageBox+0x338 and reach the owner through
//   negative displacements (-0x334 -> owner+4, -0x128 -> owner+0x210).

#include "types.h"

extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP

// ---- external helpers ----------------------------------------------------------------------
void* WinButton_CreateDefault(int a, int b, int c);              // 0x009671c0
void* GetDefaultAllocator();                                     // 0x009512c0
void* AllocObject(int size, int align, const char* name, void* allocator);  // 0x009512d0
void  FreeMem(void* p);                                          // 0x00f47380
void  MultiHeapDelete(void* p);                                  // 0x00951330
void __fastcall WinDialog_Shutdown(void* p);                     // 0x0096bd00
uint32_t WinColor_Lerp(uint32_t a, uint32_t b, float t);         // 0x007f5eb0

namespace EA {
namespace UTFWinControls {

// ---- interfaces ----------------------------------------------------------------------------
struct IWindow;

struct IWinButton {
    virtual void      AddRef();          // +0x00
    virtual void      Release();         // +0x04
    VP VP                                // +0x08, +0x0c
    virtual IWindow*  GetWindow();       // +0x10
};

struct IWindow {
    VP4 VP4 VP4 VP4 VP4                               // 0x00..0x4c
    virtual void SetParam(void* p);                    // 0x50
    VP VP VP VP VP VP VP VP VP VP                     // 0x54..0x78
    virtual void SetFlag(int a, int b);                // 0x7c
    virtual void SetParent(void* p);                   // 0x80
    VP4 VP4 VP4 VP4 VP4 VP                            // 0x84..0xd4
    virtual bool AddChild(void* p);                    // 0xd8
    VP                                                // 0xdc
    virtual void RemoveChild(void* p);                 // 0xe0
};

struct IObj;
struct IObjNoArg {
    VP VP VP VP                                       // 0x00..0x0c
    virtual IObj* self10();
    virtual IObj* v14();                               // 0x14 (slot 5, no argument)
};

struct IObjArg {
    VP VP VP VP                                       // 0x00..0x0c
    virtual void* self10();
    virtual void* v14(int x);                          // 0x14 (slot 5, one argument)
};

struct IObj {
    VP VP VP VP                                       // 0x00..0x0c
    virtual IObj* v10();                               // 0x10
    virtual IObj* v14(int x = 0);                      // 0x14
    VP4 VP4 VP4                                       // 0x18..0x44
    virtual IObj* v48(int x);                          // 0x48
    VP4 VP4 VP4 VP4 VP VP VP                          // 0x4c..0x94
    virtual void  v98();                               // 0x98
};

struct Arg2;

struct IOwner {
    VP VP VP VP VP                                    // 0x00..0x10
    virtual int  v14();                                // 0x14
    VP4 VP4 VP4 VP4 VP4 VP4                           // 0x18..0x78
    VP VP                                             // 0x7c
    virtual void v80(void* p);                         // 0x80 (slot 32)
    char pad04[0xc];                                   // +0x04..0x0f
    int  m10;                                          // +0x10
    int  m14;                                          // +0x14
    bool Process(IObj* arg1, Arg2* arg2);
    bool Process2(IObj* arg1, Arg2* arg2);
};

struct IColorTarget {
    VP4 VP4 VP4 VP4 VP4                               // 0x00..0x4c
    VP VP VP                                          // 0x50..0x58
    virtual void SetColor(uint32_t c);                 // 0x5c
};

struct IRefCounted {
    virtual void AddRef();                             // +0x00
    virtual void Release();                            // +0x04
};

struct FloatSink {
    void Set(float v);                                 // 0x0095ee40
};

// ---- auto-ref pointer + button vector -------------------------------------------------------
struct AutoRef {
    IWinButton* mpObject;
    AutoRef() : mpObject(0) {}
    AutoRef(IWinButton* p) : mpObject(p) {}
};

struct ButtonVec {
    AutoRef* mpBegin;        // +0x00
    AutoRef* mpEnd;          // +0x04
    AutoRef* mpCapacity;     // +0x08
    void Insert(AutoRef* pos, const AutoRef* value);   // 0x006650c0
    void erase(AutoRef* first, AutoRef* last);         // 0x00e25bd0
    void DestroyVector();                              // 0x00ae6970
    void push_back(const AutoRef& v) {
        if (mpEnd < mpCapacity) {
            AutoRef* p = mpEnd++;
            if (p) {
                IWinButton* o = v.mpObject;
                p->mpObject = o;
                if (o) o->AddRef();
            }
        } else {
            Insert(mpEnd, &v);
        }
    }
};

// ---- hashtable / string --------------------------------------------------------------------
struct EaHashtable {
    char  pad0[4];           // +0x00
    void* mpBucketArray;     // +0x04
    uint32_t mnBucketCount;  // +0x08
    int   mnElementCount;    // +0x0c
    void DoFreeBuckets(void* p, int n);   // 0x00693230
};

struct WString {
    wchar_t* mpBegin;        // +0x00
    wchar_t* mpEnd;          // +0x04
    wchar_t* mpCapacity;     // +0x08
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};

// ---- WinMessageBox -------------------------------------------------------------------------
struct WinMessageBox;

struct WinMessageBoxTail {
    void*  mpVtbl;           // +0x00  (0x338)
    int    m004;             // +0x04
    float  m008;             // +0x08
    float  m00c, m010, m014, m018, m01c, m020, m024, m028;  // +0x0c..0x28
    float  m02c, m030, m034, m038, m03c;                    // +0x2c..0x3c
    int    m040;             // +0x40
    int    m044;             // +0x44
    ButtonVec mButtons;      // +0x48
    char   pad54[8];         // +0x54..0x5b
    EaHashtable mKeyList;    // +0x5c
    float  m06c;             // +0x6c
    float  m070;             // +0x70
    int    m074;             // +0x74
    int    m078;             // +0x78
    WString msMessageText;   // +0x7c
    int    mUninit;          // +0x88
    int    m08c;             // +0x8c
    int    m090;             // +0x90
    IRefCounted* mpMessageText;     // +0x94
    IRefCounted* mpButtonDrawable;  // +0x98

    WinMessageBox* Owner();
    void SetMessageText(const wchar_t* text);
    bool InitButton(int parent, int param, int a3, int a4);
    void RemoveAll();
};

struct WinMessageBox {
    void* mpVtbl0;                 // +0x000
    void* mpVtbl4;                 // +0x004
    char  pad008[0x204];           // +0x008..0x20b
    void* mpVtbl20c;               // +0x20c
    uint8_t m210;                  // +0x210
    char  pad211[0x127];           // +0x211..0x337
    WinMessageBoxTail mTail;       // +0x338

    void Init();                   // 0x0096e0c0
    void Destroy();                // 0x0096e260
    WinMessageBox();
    ~WinMessageBox();
    void Shutdown();
};

inline WinMessageBox* WinMessageBoxTail::Owner()
{
    return (WinMessageBox*)((char*)this - 0x338);
}

// ---- simple holder / effects ---------------------------------------------------------------
struct PairHolder {
    void* m000;
    int m004;
    int m008;
    void Get(uint32_t* a, uint32_t* b);
};

struct FadeEffect {
    void Ctor();                   // 0x00963db0
};

struct ModulateEffect {
    void* m00;                     // +0x00
    void* m04;                     // +0x04
    void* m08;                     // +0x08
    void* m0c;                     // +0x0c
    char  pad10[0x50];             // +0x10..0x5f
    void* volatile m60;            // +0x60
    volatile int m64;              // +0x64
    volatile int m68;              // +0x68
    void Ctor();                   // 0x00963db0
    void Update(IColorTarget* target, float t);
};

struct BasicFactory_ModulateEffect {
    void* CreateInstance(void* ctx, void* allocator);
};

struct PerspectiveEffect {
    void* m00;
    void* volatile m04;
    void* m08;
    void* volatile m0c;
    float m10;
};

struct BasicFactory_PerspectiveEffect {
    void* CreateInstance(void* ctx, void* allocator);
};

struct Navigator {
    void* m00;
    void* volatile m04;
    void* m08;
    void* volatile m0c;
    Navigator();
    ~Navigator();
};

struct ExplicitNavigator : Navigator {
    void* m10;
    void* m14;
    ExplicitNavigator();
};

struct CascadeEffect {
    void* m00;
    void* m04;
    void* m08;
    void* m0c;
    CascadeEffect* Destroy(uint8_t flags);
};

struct FloatHolder {
    char  pad0[0x10];
    float m10;
    void Apply(FloatSink* sink);
};

struct Arg2 {
    char  pad0[8];
    int   m08;                     // +0x08
    int   m0c;                     // +0x0c
    int   m10;                     // +0x10
    int   m14;                     // +0x14
    void* m18;                     // +0x18
};

// ---- HashOwner (unrelated small object with a hashtable at +0x5c) ---------------------------
struct HashOwner {
    char pad0[0x5c];
    EaHashtable mHash;             // +0x5c
    void Clear();
};

// ================================ definitions ===============================================

// @ 0x0097fb40
void HashOwner::Clear()
{
    EaHashtable* h = &mHash;
    h->DoFreeBuckets(h->mpBucketArray, h->mnBucketCount);
    h->mnElementCount = 0;
}

// @ 0x0097fb60
WinMessageBox::~WinMessageBox()
{
    *(void* volatile*)&mpVtbl0 = (void*)0x1443be8;
    *(void* volatile*)&mpVtbl4 = (void*)0x1443ac8;
    *(void* volatile*)&mpVtbl20c = (void*)0x1443a58;
    *(void* volatile*)&mTail.mpVtbl = (void*)0x14439c8;
    IRefCounted* p = *(IRefCounted* volatile*)&mTail.mpButtonDrawable;
    if (p)
        p->Release();
    IRefCounted* q = *(IRefCounted* volatile*)&mTail.mpMessageText;
    if (q)
        q->Release();
    {
        uint32_t n = (uint32_t)((char*)mTail.msMessageText.mpCapacity -
                                (char*)mTail.msMessageText.mpBegin);
        n &= ~1u;
        if ((int)n > 2 && mTail.msMessageText.mpBegin)
            FreeMem((void*)mTail.msMessageText.mpBegin);
    }
    EaHashtable* h = &mTail.mKeyList;
    h->DoFreeBuckets(h->mpBucketArray, h->mnBucketCount);
    h->mnElementCount = 0;
    if (h->mnBucketCount > 1)
        FreeMem(h->mpBucketArray);
    mTail.mButtons.DestroyVector();
    mTail.mpVtbl = (void*)0x13eb938;
    Destroy();
}

// @ 0x0097fd00
void WinMessageBoxTail::SetMessageText(const wchar_t* text)
{
    const wchar_t* p = text;
    while (*p)
        ++p;
    msMessageText.assign(text, text + (p - text));
    Owner()->m210 = 1;
}

#define VS_P(f, v) (*(void* volatile*)&(f) = (void*)(v))
#define VS_F(f, v) (*(volatile float*)&(f) = (v))
#define VS_I(f, v) (*(volatile int*)&(f) = (v))

// @ 0x0097fd40
WinMessageBox::WinMessageBox()
{
    Init();
    VS_P(mTail.mpVtbl, 0x1443910);
    VS_F(mTail.m008, 5.0f);
    VS_P(mpVtbl0, 0x1443be8);
    VS_P(mpVtbl4, 0x1443ac8);
    VS_P(mpVtbl20c, 0x1443a58);
    VS_P(mTail.mpVtbl, 0x14439c8);
    VS_I(mTail.m004, 1);
    VS_F(mTail.m00c, 5.0f);
    VS_F(mTail.m010, 5.0f);
    VS_F(mTail.m014, 5.0f);
    VS_F(mTail.m018, 5.0f);
    VS_F(mTail.m01c, 5.0f);
    VS_F(mTail.m020, 5.0f);
    VS_F(mTail.m024, 5.0f);
    VS_F(mTail.m028, 5.0f);
    VS_F(mTail.m02c, 70.0f);
    VS_F(mTail.m030, 30.0f);
    VS_F(mTail.m034, 10.0f);
    VS_F(mTail.m038, 0.0f);
    VS_F(mTail.m03c, 0.0f);
    VS_I(mTail.m044, 3);
    VS_I(mTail.m040, 0);
    VS_P(mTail.mButtons.mpBegin, 0);
    VS_P(mTail.mButtons.mpEnd, 0);
    VS_P(mTail.mButtons.mpCapacity, 0);
    VS_F(mTail.m06c, 1.0f);
    VS_F(mTail.m070, 2.0f);
    VS_I(mTail.mKeyList.mnBucketCount, 1);
    VS_I(mTail.mKeyList.mnElementCount, 0);
    VS_I(mTail.m074, 0);
    VS_P(mTail.mKeyList.mpBucketArray, 0x154df28);
    VS_P(mTail.msMessageText.mpCapacity, 0x1667bae);
    VS_P(mTail.msMessageText.mpBegin, 0x1667bac);
    VS_P(mTail.msMessageText.mpEnd, 0x1667bac);
    VS_I(mTail.m08c, 0);
    VS_I(mTail.m090, 0);
    VS_P(mTail.mpMessageText, 0);
    VS_P(mTail.mpButtonDrawable, 0);
}

#undef VS_P
#undef VS_F
#undef VS_I

// @ 0x0097ff10
void WinMessageBox::Shutdown()
{
    mTail.mButtons.erase(mTail.mButtons.mpBegin, mTail.mButtons.mpEnd);
    if (mTail.mpMessageText) {
        IRefCounted* p = mTail.mpMessageText;
        mTail.mpMessageText = 0;
        p->Release();
    }
    if (mTail.mpButtonDrawable) {
        IRefCounted* p = mTail.mpButtonDrawable;
        mTail.mpButtonDrawable = 0;
        p->Release();
    }
    WinDialog_Shutdown(this);
}

// @ 0x0097ff70
bool WinMessageBoxTail::InitButton(int parent, int param, int, int)
{
    IWinButton* b = (IWinButton*)WinButton_CreateDefault(1, 0, 0);
    AutoRef btn(b);
    if (b) {
        b->AddRef();
        b->GetWindow()->SetParam((void*)param);
        b->GetWindow()->SetParent((void*)parent);
        b->GetWindow()->SetFlag(0x200, 1);
        if (((IWindow*)((char*)Owner() + 4))->AddChild(b->GetWindow())) {
            ButtonVec* v = &mButtons;
            if (v->mpEnd < v->mpCapacity) {
                AutoRef* p = v->mpEnd++;
                if (p) {
                    p->mpObject = b;
                    b->AddRef();
                }
            } else {
                v->Insert(v->mpEnd, &btn);
                b = btn.mpObject;
            }
            Owner()->m210 = 1;
            if (b)
                b->Release();
            return true;
        }
        b->Release();
    }
    return false;
}

// @ 0x00980070
void WinMessageBoxTail::RemoveAll()
{
    AutoRef* it = mButtons.mpBegin;
    while (it != mButtons.mpEnd) {
        ((IWindow*)((char*)Owner() + 4))->RemoveChild(it->mpObject->GetWindow());
        ++it;
    }
    ButtonVec& v = mButtons;
    v.erase(v.mpBegin, v.mpEnd);
    Owner()->m210 = 1;
}

// @ 0x00980120
void ModulateEffect::Update(IColorTarget* target, float t)
{
    target->SetColor(WinColor_Lerp((uint32_t)m64, (uint32_t)m68, t));
}

// @ 0x00980150
void PairHolder::Get(uint32_t* a, uint32_t* b)
{
    *a = (uint32_t)m004;
    *b = (uint32_t)m008;
}

// @ 0x009802b0
void* BasicFactory_ModulateEffect::CreateInstance(void* ctx, void* allocator)
{
    if (!allocator)
        allocator = GetDefaultAllocator();
    ModulateEffect* p = (ModulateEffect*)AllocObject(
        0x70, 8, "UTFWin/EA::UTFWinControls::ModulateEffect", allocator);
    if (p) {
        p->Ctor();
        p->m60 = (void*)0x14426a0;
        p->m64 = -1;
        p->m68 = -1;
        p->m00 = (void*)0x1443d90;
        p->m04 = (void*)0x1443d74;
        p->m0c = (void*)0x1443d38;
        p->m60 = (void*)0x1443e5c;
        return p;
    }
    return 0;
}

// @ 0x00980360
bool IOwner::Process(IObj* arg1, Arg2* arg2)
{
    switch (arg2->m08) {
    case 1:
        if (arg2->m10 == m10) {
            IObj* r = ((IObjNoArg*)arg1)->v14()->v48(0);
            switch (m14) {
            case 1:
                if (r != arg1)
                    return false;
                break;
            case 2:
                if (r) {
                    if (r->v10() != arg1)
                        return false;
                }
                break;
            case 3:
                if (r == arg1)
                    return false;
                break;
            }
            v80(((IObjArg*)arg1)->v14(0));
        }
        break;
    }
    return false;
}

Navigator::Navigator()
{
    m04 = (void*)0x13fa72c;
    m08 = 0;
    m0c = (void*)0x1444434;
}

// @ 0x00980420
Navigator::~Navigator()
{
    m0c = (void*)0x13eb938;
    m04 = (void*)0x13eb938;
    m00 = (void*)0x13eb938;
}

// @ 0x00980430
ExplicitNavigator::ExplicitNavigator()
{
    m00 = (void*)0x1443f78;
    m04 = (void*)0x1443f5c;
    m0c = (void*)0x1443f38;
    m10 = 0;
    m14 = 0;
}

// @ 0x00980490
CascadeEffect* CascadeEffect::Destroy(uint8_t flags)
{
    m0c = (void*)0x13eb938;
    m04 = (void*)0x13eb938;
    m00 = (void*)0x13eb938;
    if (flags & 1)
        MultiHeapDelete(this);
    return this;
}

// @ 0x00980520
bool IOwner::Process2(IObj* arg1, Arg2* arg2)
{
    switch (arg2->m08) {
    case 0x15:
        if (v14() & 0x200)
            v80(arg2->m18);
        break;
    case 0xc:
        if (v14() & 0x200)
            arg1->v98();
        break;
    }
    return false;
}

// @ 0x00980580
void FloatHolder::Apply(FloatSink* sink)
{
    sink->Set(m10);
}

// @ 0x00980680
void* BasicFactory_PerspectiveEffect::CreateInstance(void* ctx, void* allocator)
{
    if (!allocator)
        allocator = GetDefaultAllocator();
    PerspectiveEffect* p = (PerspectiveEffect*)AllocObject(
        0x14, 4, "UTFWin/EA::UTFWinControls::PerspectiveEffect", allocator);
    if (p) {
        p->m04 = (void*)0x13fa72c;
        p->m08 = 0;
        p->m0c = (void*)0x14426a0;
        p->m00 = (void*)0x14440d0;
        p->m04 = (void*)0x14440b4;
        p->m0c = (void*)0x1444098;
        p->m10 = 400.0f;
        return p;
    }
    return 0;
}

}  // namespace UTFWinControls
}  // namespace EA
