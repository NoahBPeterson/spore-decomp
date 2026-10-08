// Slice s00eb92d0 -- 0x00EB9760: the adventure creature large-view's activation handler (vtable slot 6 of the
// 0x014887E4 vtable; __thiscall, 5 stack args, ret 0x14).  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-.
//
// After the base handler (0x0066CE00) accepts the event it
//   * stores the target object the event queries (interface 0x5cd3f947) in this+0xdc,
//   * shows/hides the three label windows (0x07fb1c78, 0x07fb2ed0, 0x07cce580) depending on whether the target
//     is "active" (target+0x78), giving each a cSPUITextZoom (this+0xf4 / +0xf8) bound to its text window,
//   * looks up the event object's property list (resource key from vtable slot 0x40) and, when it has the
//     creature level properties (0x5888ef41, 0xcf837237), fills the level tooltip window 0x07cce570 (image,
//     two numbers, "v2/v3" tooltip text) and slides the 0x07cd1588 bar by the level fraction,
//   * creates the "Sporepedia" helper (this+0xec) and the 0xE8 helper object, refreshes them,
//   * clears this+0x110, positions the 0x07eb4153 window against this+0x34 and creates the last text zoom
//     (this+0xf0).
#include "types.h"

#define PV(n) virtual void pv##n();

struct ResourceKey { uint32_t instance, type, group; };

struct IRefCount { virtual void AddRef(); virtual void Release(); };
struct IRefCount2 { virtual void v0(); virtual void AddRef(); virtual void Release(); };   // slots +4 / +8

struct Rect { float x, y, z, w; };

struct IWindow {
    virtual void AddRef(); virtual void Release(); PV(2)
    virtual IWindow* Query(uint32_t id);               // +0x0c
    virtual IWindow* GetParent();                      // +0x10
    virtual void vf14(int a);                          // +0x14
    PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual const Rect* GetRect();                     // +0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    virtual void SetRect(const Rect* r);               // +0x6c
    PV(28) PV(29) PV(30)
    virtual void SetFlag(int a, int b);                // +0x7c
    virtual void SetText(const wchar_t* s);            // +0x80
};

struct Zero3 { int a, b, c; Zero3() : a(0), b(0), c(0) {} };

struct TextZoomName {                                  // 0x78 bytes, "UI/cSPUITextZoom"
    uint32_t data[30];
    TextZoomName();                                    // 0x008345c0 (returns this)
    void SetTargetWindow(IWindow* w, int a, int b, int c, Zero3 z);   // 0x00834fa0, ret 0x1c
};
struct ZoomHolder {                                    // EA::AutoRefCount<TextZoomName>, out-of-line operator=
    TextZoomName* mp;
    void Assign(TextZoomName* p);                      // 0x00572620, ret 4
};

struct Sporepedia {                                    // 0x80 bytes, "Sporepedia"
    uint32_t data[32];
    Sporepedia();                                      // 0x0059a270
    void FUN_0059a7f0(IWindow* w);                     // ret 4
};
struct Helper {                                        // 0x80 bytes
    uint32_t data[32];
    Helper();                                          // 0x00f46dd0
    void FUN_00f46eb0(uint32_t a);                     // ret 4
    void FUN_00f47080(int a);                          // ret 4
    void FUN_00f47170(uint32_t a, uint32_t b);         // ret 8
};
void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void __cdecl operator delete[](void* p);                                                  // 0x00f47380

struct cString {                                       // 0x14 bytes
    uint32_t data[5];
    cString(uint32_t table, uint32_t id, int a);       // 0x006b5770, ret 0xc
    ~cString();                                        // 0x006b5240
    const wchar_t* GetText();                          // 0x006b55c0
};

struct Layout {                                        // cSPUILayout
    IWindow* FindWindowByID(uint32_t id, int recursive);   // 0x008105b0, ret 8
};

struct PropList { virtual void AddRef(); virtual void Release(); };
bool __cdecl FUN_005bf0e0(const ResourceKey* key, PropList** out);
bool __cdecl TryGetUIntProperty(PropList* pl, uint32_t id, uint32_t* out);      // 0x00410370
int  __cdecl FUN_00eec580(int v);
bool __cdecl SetImageFromLayout(IWindow* w, Layout* l, uint32_t id, int a);     // 0x00807c70
void __cdecl SetNumberString(long long v, wchar_t* buf, int n);                 // 0x00881ae0
void __cdecl SetTooltipText(IWindow* w, const wchar_t* s, int a, int b);        // 0x00806de0

struct FixedWStr {                                     // fixed buffer wide string, 62 chars
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    wchar_t* mpPool;
    wchar_t  mBuf[64];
    FixedWStr() { mpPool = mBuf; mpBegin = mBuf; mpCapacity = mBuf + 62; mpEnd = mBuf; mBuf[0] = 0; }
    ~FixedWStr() { if ((mpCapacity - mpBegin) > 1 && mpBegin && mpBegin != mpPool) ::operator delete[](mpBegin); }
    void append(const wchar_t* s);                     // 0x006ec1c0, ret 4
};
FixedWStr* __cdecl FUN_00eb96a0(FixedWStr* s, const wchar_t* fmt, const wchar_t* arg);

struct EventSub {                                      // sub-object at event+0x10
    virtual void AddRef(); virtual void Release(); PV(2)
    virtual struct Target* Query(uint32_t id);         // +0x0c
};
struct Event {
    PV(0) PV(1) PV(2)
    virtual const wchar_t* GetName();                  // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15)
    virtual const ResourceKey* GetKey();               // +0x40
    uint32_t pad04[3];
    EventSub mSub;                                     // +0x10
};

struct Target {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
    PV(31) PV(32) PV(33) PV(34) PV(35)
    virtual bool vf90(uint32_t* out);                  // +0x90
    uint32_t pad04[3];
    IRefCount mRef;                                    // +0x10
    uint32_t pad14[(0x78 - 0x14) / 4];
    char     mbActive;                                 // +0x78
    bool FUN_006418e0();
};

struct SelRecord {                                     // *(g_016c7aa4 + 0x7c)
    uint32_t pad[5];
    ResourceKey key;                                   // +0x14
    int      mi20;
};
struct Globals { uint32_t pad[0x7c / 4]; SelRecord* mpSel; };
extern Globals* g_016c7aa4;

struct ViewOuter {                                     // this - 0xc
    void FUN_00eb90c0(const ResourceKey* key);         // ret 4
    void FUN_00eb9170(const ResourceKey* key);         // ret 4
};

struct SubObj { virtual void v0(); };

struct View {                                          // `this` (secondary base of the view object)
    uint32_t pad00[3];
    Layout*  mpLayout;                                 // +0x0c
    uint32_t pad10;
    uint32_t mField14;                                 // +0x14
    uint32_t pad18[(0x34 - 0x18) / 4];
    IWindow* mpWindow;                                 // +0x34
    uint32_t pad38[(0xc4 - 0x38) / 4];
    SubObj   mSub;                                     // +0xc4
    uint32_t padc8[(0xdc - 0xc8) / 4];
    Target*  mpTarget;                                 // +0xdc
    uint32_t pade0[2];
    Helper*  mpHelper;                                 // +0xe8
    Sporepedia* mpSporepedia;                          // +0xec
    TextZoomName* mpZoomF0;                            // +0xf0
    ZoomHolder mZoomF4;                                // +0xf4
    ZoomHolder mZoomF8;                                // +0xf8
    uint32_t padfc[(0x110 - 0xfc) / 4];
    char     mbFlag110;                                // +0x110

    char FUN_0066ce00(int a, Event* e, int b, int c, int d);   // base handler, ret 0x14
    char Activate(int a, Event* e, int b, int c, int d);
};

template<class T> static inline const T& Min2(const T& a, const T& b) { return (a < b) ? a : b; }

// @ 0x00EB9760
char View::Activate(int a, Event* e, int b, int c, int d)
{
    char ok = FUN_0066ce00(a, e, b, c, d);
    if (ok) {

    Target* nt = e ? e->mSub.Query(0x5cd3f947) : 0;
    Target* old = mpTarget;
    if (nt != old) {
        if (nt) nt->mRef.AddRef();
        mpTarget = nt;
        if (old) old->mRef.Release();
    }

    IWindow* w1 = mpLayout->FindWindowByID(0x7fb1c78, 1);
    IWindow* w2 = mpLayout->FindWindowByID(0x7fb2ed0, 1);
    IWindow* w3 = mpLayout->FindWindowByID(0x7cce580, 1);
    if (mpTarget && mpTarget->mbActive) {
        SelRecord* rec = g_016c7aa4->mpSel;
        rec->key = *e->GetKey();
        rec->mi20 = -1;
        cString s1(0x623d2fc0, 0x7ceb169, 0);
        if (w1) {
            w1->SetFlag(1, 1);
            w1->SetText(s1.GetText());
            mZoomF4.Assign(new ("UI/cSPUITextZoom", 0, 0, 0, 0) TextZoomName());
            mZoomF4.mp->SetTargetWindow(w1->Query(0xf15f4bd), 0, 0, 0, Zero3());
        }
        if (w2)
            w2->SetFlag(1, 0);
        cString s2(0x623d2fc0, 0x7ceb16c, 0);
        if (w3) {
            w3->SetText(s2.GetText());
            mZoomF8.Assign(new ("UI/cSPUITextZoom", 0, 0, 0, 0) TextZoomName());
            mZoomF8.mp->SetTargetWindow(w3->Query(0xf15f4bd), 0, 0, 0, Zero3());
        }
    } else {
        if (w1)
            w1->SetFlag(1, 0);
        if (w2) {
            w2->SetFlag(1, 1);
            w2->SetText(e->GetName());
            mZoomF4.Assign(new ("UI/cSPUITextZoom", 0, 0, 0, 0) TextZoomName());
            mZoomF4.mp->SetTargetWindow(w2->Query(0xf15f4bd), 0, 0, 0, Zero3());
        }
        if (w3)
            w3->SetText((const wchar_t*)0x13ec468);
    }

    mSub.v0();

    IWindow* w4 = mpLayout->FindWindowByID(0x7cce570, 1);
    const ResourceKey* key = e->GetKey();
    PropList* pl = 0;
    if (FUN_005bf0e0(key, &pl)) {
      if (w4) {
        FixedWStr str;
        int v1 = 0;
        if (TryGetUIntProperty(pl, 0x5888ef41, (uint32_t*)&v1)) {
            int v2 = 0;
            TryGetUIntProperty(pl, 0xcf837237, (uint32_t*)&v2);
            int lvl = v1;
            int r3 = FUN_00eec580(lvl + 1);
            SetImageFromLayout(w4, mpLayout, lvl + 0x7d10de0, -1);
            wchar_t numbuf[32];
            IWindow* w5 = mpLayout->FindWindowByID(0x7cd1550, 1);
            if (w5) {
                SetNumberString(v1, numbuf, 0x20);
                w5->SetText(numbuf);
            }
            SetNumberString(v2, numbuf, 0x20);
            FUN_00eb96a0(&str, (const wchar_t*)0x1488848, numbuf);
            SetNumberString(r3, numbuf, 0x20);
            str.append(numbuf);
            SetTooltipText(w4, str.mpBegin, -1, 1);
            IWindow* w6 = mpLayout->FindWindowByID(0x7cd1588, 1);
            if (w6) {
                float fr3 = (float)r3;
                float fA = fr3 - 1.0f;
                float fB = (float)FUN_00eec580(v1);
                const float& m1 = Min2(fA, fB);
                float t = ((float)v2 - m1) / (fr3 - m1);
                float one = 1.0f;
                const float& m2 = Min2(one, t);
                const Rect* p = w6->GetRect();
                Rect r;
                r.x = p->x;
                r.y = p->y;
                r.z = p->z;
                r.w = (p->w - r.y) * (1.0f - m2) + r.y;
                w6->SetRect(&r);
            }
            ViewOuter* outer = (ViewOuter*)((char*)this - 0xc);
            outer->FUN_00eb90c0(key);
            outer->FUN_00eb9170(key);
            w4->SetFlag(1, 1);
        } else {
            w4->SetFlag(1, 0);
        }
      }
    } else {
        if (w4)
            w4->SetFlag(1, 0);
    }

    IWindow* w7 = mpLayout->FindWindowByID(0x760a5d8, 1);
    if (w7) {
        Sporepedia* sp = new ("Sporepedia", 0, 0, 0, 0) Sporepedia();
        Sporepedia* oldsp = mpSporepedia;
        if (sp != oldsp) {
            if (sp) ((IRefCount*)sp)->AddRef();
            mpSporepedia = sp;
            if (oldsp) ((IRefCount*)oldsp)->Release();
        }
        mpSporepedia->FUN_0059a7f0(w7);
    }

    Helper* h = new ((const char*)0x13f6b3c, 0, 0, 0, 0) Helper();
    Helper* oldh = mpHelper;
    if (h != oldh) {
        if (h) ((IRefCount*)h)->AddRef();
        mpHelper = h;
        if (oldh) ((IRefCount*)oldh)->Release();
    }
    mpHelper->FUN_00f46eb0(mField14);
    if (mpHelper) {
        uint32_t pair[2];
        if (mpTarget->vf90(pair) && !mpTarget->FUN_006418e0()) {
            mpHelper->FUN_00f47080(1);
            mpHelper->FUN_00f47170(pair[0], pair[1]);
        } else {
            mpHelper->FUN_00f47080(0);
        }
    }
    mbFlag110 = 0;
    IWindow* w8 = mpLayout->FindWindowByID(0x7eb4153, 1);
    IWindow* tz = w8 ? w8->Query(0xf15f4bd) : 0;
    if (mpWindow && tz) {
        const Rect* p = mpWindow->GetRect();
        Rect r;
        r.x = p->x;
        r.y = p->y;
        r.z = p->z;
        r.w = p->w;
        tz->vf14(0);
        r.x = tz->GetParent()->GetRect()->z;
        mpWindow->SetRect(&r);
    }
    if (mpWindow) {
        TextZoomName* z = new ("UI/cSPUITextZoom", 0, 0, 0, 0) TextZoomName();
        TextZoomName* oldz = mpZoomF0;
        if (z != oldz) {
            if (z) ((IRefCount2*)z)->AddRef();
            mpZoomF0 = z;
            if (oldz) ((IRefCount2*)oldz)->Release();
        }
        mpZoomF0->SetTargetWindow(mpWindow ? mpWindow->Query(0xf15f4bd) : 0, 0, 0, 0, Zero3());
    }
    if (pl)
        pl->Release();
    }
    return ok;
}
