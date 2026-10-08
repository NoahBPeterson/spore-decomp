// Slice s00edbfc0 -- asset-browser / swatch item UI glue (linked-list lookups).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <new>

// ---------------------------------------------------------------- globals
extern int   g_148a544[];    // 0x0148a544
extern int   g_148a694[];    // 0x0148a694

// ---------------------------------------------------------------- callees
void  __cdecl SetGlobalProperty(int, float);            // 0x005ca880
void  __cdecl FUN_00572020(int, int);                   // 0x00572020
void* __fastcall FUN_00e09c80(void*);                   // 0x00e09c80
void* __cdecl FUN_00e09c90(void*, unsigned);            // 0x00e09c90
void* __cdecl SP_MessageServer(void);                   // 0x0067dcc0
void  __cdecl FUN_00ed8780(int);                        // 0x00ed8780
void  __cdecl FUN_00ed8690(void);                       // 0x00ed8690
void  __cdecl EA_RemoveHandler(int, int, int, int, int);    // 0x00571db0
void  __fastcall FUN_00ece300(char*);                   // 0x00ece300
void* __cdecl FUN_00e7f54d0(void*);                     // 0x007f54d0
void  __cdecl EA_Free(void*);                           // 0x00f47380
void  __cdecl FUN_00f3bcb0(void);                       // 0x00f3bcb0

typedef int   (__thiscall *FGi)(void*);
typedef void* (__thiscall *FGp)(void*);
typedef int   (__thiscall *FI_1)(void*);
typedef void* (__thiscall *FV_i)(void*, int);
typedef void  (__thiscall *FV_ii)(void*, int, int);
typedef void  (__thiscall *FV_v)(void*);
typedef int   (__thiscall *FI_i)(void*, int);
struct ILayout { void* FindWindowByID(unsigned, int); };

// ---------------------------------------------------------------- 0x00edc9e0
int* FUN_00edc9e0(int* p, int id)
{
    while (p != 0 && ((FGi)(*(void***)p)[0x1c / 4])(p) != id)
        p = (int*)((FGp)(*(void***)p)[0x10 / 4])(p);
    return p;
}

// ---------------------------------------------------------------- 0x00edca20
int* FUN_00edca20(int* p)
{
    while (p != 0) {
        unsigned id = (unsigned)((FGi)(*(void***)p)[0x1c / 4])(p);
        if (id >= 0x715cde0 && id < 0x715cde3)
            return p;
        p = (int*)((FGp)(*(void***)p)[0x10 / 4])(p);
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00edca60
int FUN_00edca60(int p)
{
    int* q = FUN_00edca20((int*)p);
    if (q != 0)
        return ((FGi)(*(void***)q)[0x1c / 4])(q) - 0x715cde0;
    return 0;
}

// ---------------------------------------------------------------- 0x00edca90
int FUN_00edca90(int id)
{
    if (id != 0x715cdc0 && id != 0x7394420 && id != 0x75e1200)
        return 0;
    return 1;
}

// ---------------------------------------------------------------- 0x00edcac0
void FUN_00edcac0(int* out, int idx)
{
    out[0] = g_148a544[idx];
    out[1] = 0x2f7d0004;
    out[2] = (int)0x8a7be0c0;
}

// ---------------------------------------------------------------- 0x00edcb10
struct ObjCB10 {
    char pad[0x30];
    int  p30;       // +0x30
    void f();
};
void ObjCB10::f()
{
    if (p30 != 0) {
        SetGlobalProperty(0x8dff6314, 0.0f);
        FUN_00572020(p30, 0);
        p30 = 0;
    }
}

// ---------------------------------------------------------------- 0x00edcc80
void __fastcall FUN_00edcc80(char* self)
{
    *(int*)(self + 0x104) = (int)0x867a9ee9;
}

// ---------------------------------------------------------------- 0x00edcc90
struct ObjCC90 { void f(int); };
void ObjCC90::f(int param)
{
    char* base = (char*)this + 0x4c;
    unsigned n = (unsigned)FUN_00e09c80(base);
    for (unsigned i = 0; i < n; ++i) {
        char* w = (char*)FUN_00e09c90(base, i);
        char* wnd = (char*)((ILayout*)w)->FindWindowByID(0x7b52f20, 1);
        ((FV_ii)(*(void***)wnd)[0x7c / 4])(wnd, 2, param);
    }
}

// ---------------------------------------------------------------- 0x00edcce0
int FUN_00edcce0(int* p)
{
    for (;;) {
        if (p == 0)
            return 0;
        int id = ((FGi)(*(void***)p)[0x1c / 4])(p);
        for (unsigned j = 0; j < 0xc; j += 4) {
            if (id == g_148a694[j / 4])
                return id;
        }
        p = (int*)((FGp)(*(void***)p)[0x10 / 4])(p);
    }
}

// ---------------------------------------------------------------- 0x00edce00
bool FUN_00edce00(int p)
{
    if (FUN_00edc9e0((int*)p, 0x2791ba0) == 0)
        return false;
    return true;
}

// ---------------------------------------------------------------- 0x00edce20
struct ObjCE20 {
    char pad[0x14];
    char* p14;      // +0x14
    int   p20;      // +0x20
    void f(int);
};
void ObjCE20::f(int arg)
{
    if (p14 != 0) {
        int saved = p20;
        if (saved != (int)FUN_00e7f54d0(p14))
            ((FV_i)(*(void***)p14)[0x1c / 4])(p14, saved);
        ((FV_i)(*(void***)(p14 + 0x24))[0x18 / 4])(p14 + 0x24, arg);
        FUN_00ece300(p14);
    }
}

// ---------------------------------------------------------------- 0x00edcec0
int FUN_00edcec0(int* p, int* arr, unsigned* count)
{
    unsigned n = *count;
    if (n == 0)
        return -1;
    int key = *p;
    for (unsigned i = 0; i < n; ++i) {
        if (key == arr[i])
            return (int)i;
    }
    return -1;
}

// ---------------------------------------------------------------- 0x00edcf10
struct ObjCF10 {
    char pad[4];
    void* vt4;      // +0x4
    void* f(char);
};
void* ObjCF10::f(char param)
{
    vt4 = (void*)0x13eb394;
    if (param & 1)
        EA_Free(this);
    return this;
}

// ---------------------------------------------------------------- 0x00edcf30
int FUN_00edcf30(int* p)
{
    if (p == 0)
        return 0;
    char* q = (char*)((FV_i)(*(void***)p)[0xc / 4])(p, 0x8ed27e7a);
    if (q == 0)
        return 0;
    unsigned v = (unsigned)((FI_1)(*(void***)q)[0x20 / 4])(q);
    return (v >> 2) & 1;
}

// ---------------------------------------------------------------- 0x00edcf60
void FUN_00edcf60(int* p, float f)
{
    if (p == 0)
        return;
    char* q = (char*)((FV_i)(*(void***)p)[0xc / 4])(p, 0xf00a8a0);
    if (q == 0)
        return;
    int a = ((FI_1)(*(void***)q)[0x28 / 4])(q);
    int b = ((FI_1)(*(void***)q)[0x30 / 4])(q);
    int r = a + (int)((float)(b - a) * f);
    ((FV_ii)(*(void***)q)[0x1c / 4])(q, r, 0);
}

// ---------------------------------------------------------------- 0x00edcbc0
int FUN_00edcbc0(int a, int* p)
{
    (void)a;
    unsigned v = *(unsigned*)((char*)p + 0x14);
    int bit0 = (int)(v & 1);
    int bit1 = (int)((v >> 1) & 1);
    int bit2 = (int)((v >> 2) & 1);
    bool any = !(bit0 == 0 && bit1 == 0 && bit2 == 0);
    unsigned u = *(unsigned*)((char*)p + 0x10);
    if (*(int*)((char*)p + 8) == 1) {
        if (u == 0x56 && bit1 != 0 && bit0 == 0 && bit2 == 0)
            return 1;
    } else if (*(int*)((char*)p + 8) == 5) {
        if ((u < 0x30 || u > 0x39) && !any)
            return 1;
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00edc0e0
// Tab-strip layout update: lays the eleven strip windows out left to right (the selected tab
// is followed by the extra button element), shows/hides them and resizes the selected tab.
namespace tb {

struct Rect { float l, t, r, b; };
static inline float RectW(const Rect* a) { return a->r - a->l; }
static inline float RectH(const Rect* a) { return a->b - a->t; }

struct ISub {                                   // sub-interface at +0x20c of a strip window
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void SetState(int which, bool on);   // +0x28
};
struct WinX { char pad[0x20c]; ISub mSub; };

struct ITextStyle {                             // interface 0xcf428691
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void SetText(const wchar_t* text, int flags);   // +0x60
    virtual void s25();
    virtual void SetLimit(int n);               // +0x68
};

struct IWindow {
    virtual void w00();
    virtual void w01();
    virtual void w02();
    virtual void* QueryInterface(uint32_t id);                  // +0x0c
    virtual void w04();
    virtual void w05();
    virtual void w06();
    virtual void w07();
    virtual void w08();
    virtual void w09();
    virtual void w10();
    virtual void w11();
    virtual void w12();
    virtual void w13();
    virtual const Rect* GetArea();                              // +0x38
    virtual void w15();
    virtual void w16();
    virtual void w17();
    virtual void w18();
    virtual void w19();
    virtual void w20();
    virtual void w21();
    virtual void w22();
    virtual void w23();
    virtual void w24();
    virtual void w25();
    virtual void w26();
    virtual void SetArea(const Rect* r);                        // +0x6c
    virtual void w28();
    virtual void w29();
    virtual void w30();
    virtual void SetFlag(int which, bool on);                   // +0x7c
    virtual void SetText(const wchar_t* text);                  // +0x80
    virtual void w33();
    virtual void w34();
    virtual void w35();
    virtual void w36();
    virtual void w37();
    virtual void w38();
    virtual void w39();
    virtual void w40();
    virtual void w41();
    virtual void w42();
    virtual void w43();
    virtual void w44();
    virtual void w45();
    virtual void w46();
    virtual void w47();
    virtual void w48();
    virtual void w49();
    virtual void w50();
    virtual void w51();
    virtual void w52();
    virtual void w53();
    virtual void w54();
    virtual void w55();
    virtual void w56();
    virtual void w57();
    virtual void w58();
    virtual void AddChild(IWindow* child);                      // +0xec
    virtual IWindow* FindChild(uint32_t id, int deep);          // +0xf0
    virtual void w61();
    virtual void w62();
    virtual bool IsFocusedChild(int which);                     // +0xfc
};

struct IWindowManager {
    virtual void m00();
    virtual void m01();
    virtual void m02();
    virtual void m03();
    virtual void m04();
    virtual void m05();
    virtual void m06();
    virtual void m07();
    virtual void m08();
    virtual void m09();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void Focus(int which, IWindow* w);                  // +0x4c
};

struct TabLayout { IWindow* FindWindowByID(uint32_t id, int deep); };   // 0x008105b0

struct Image { char pad[0x1c]; int mWidth; int mHeight; };               // +0x1c, +0x20

struct TextObj { const wchar_t* GetText(); };                            // 0x00f26360

struct TabInfo {
    TextObj mName;                              // +0x00
    char pad04[0x3c - 1];
    TextObj mDesc;                              // +0x3c
    char pad3d[0x78 - 0x3d];
    int mIcon;                                  // +0x78
    bool mFlag;                                 // +0x7c
};

struct TabManager {
    int GetCount();                             // 0x00f3be30
    TabInfo* GetTab(int i);                     // 0x00f3be60
};
struct TabBarHost { char pad[0x74]; TabManager* mpMgr; };
extern TabBarHost* g_pTabHost;                  // 0x016c7aa4

struct StripWidget {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual void SetActive(bool on);            // +0x1c
    void Select(int icon);                      // 0x00f38bc0
};

struct CStr {
    CStr();                                     // 0x006b5060
    CStr(uint32_t table, uint32_t id, int flags);   // 0x006b5770
    ~CStr();                                    // 0x006b5240
    void Load(uint32_t table, uint32_t id, int flags);   // 0x006b54b0
    const wchar_t* GetText();                   // 0x006b55c0
    uint32_t mData[5];
};

Image* GetWindowImage(IWindow* w, int which);                       // 0x008067f0
void SetDrawableImage(IWindow* w, Image* img, int flags);           // 0x008068d0
void SetTooltipText(IWindow* w, const wchar_t* text, int a, int b); // 0x00806de0
IWindowManager* GetWindowManager();                                 // 0x0067caa0

struct Entry { IWindow* win; bool vis; float pos; float end; };

struct EntryVec {
    Entry* mpBegin;
    Entry* mpEnd;
    Entry* mpCap;
    uint32_t mName;
    Entry* mpBuf;
    uint32_t mFlag;
    Entry mBuf[10];
    EntryVec() { mpBuf = mBuf; mpEnd = mBuf; mpBegin = mBuf; mpCap = mBuf + 10; }
    ~EntryVec() { if (mpBegin && mpBegin != mpBuf) EA_Free(mpBegin); }
    void DoInsertValue(Entry* pos, const Entry& v);     // 0x00edbfc0
    void push_back(const Entry& v) {
        if (mpEnd < mpCap) {
            ::new((void*)mpEnd++) Entry(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

}  // namespace tb

struct TabBar {
    char pad00[0xc];
    tb::TabLayout* mLayout;                     // +0x0c
    char pad10[0x4c - 0x10];
    tb::StripWidget* mStrip;                    // +0x4c
    void Update(int selected);
};

// @ 0x00edc0e0
void TabBar::Update(int selected)
{
    using namespace tb;
    IWindow* container = mLayout->FindWindowByID(0x743b980, 1);
    uint32_t ids[11] = { 0x7bd2d40, 0x743b8e1, 0x743b8e2, 0x743b8e3, 0x743b8e4, 0x743b8e5,
                         0x743b8e6, 0x743b8e7, 0x743b8e8, 0x7bd2dd0, 0x7bd2db8 };
    for (int j = 8; j > selected + 1; --j) {
        uint32_t b = ids[j + 1];
        uint32_t a = ids[j];
        ids[j] = b;
        ids[j + 1] = a;
    }

    EntryVec vec;
    for (unsigned i = 0; i < 11; ++i) {
        Entry e;
        e.win = mLayout->FindWindowByID(ids[i], 1);
        e.vis = true;
        e.pos = 0.0f;
        e.end = -1.0f;
        vec.push_back(e);
    }

    float cw = RectW(container->GetArea());
    float ch = RectH(container->GetArea());
    Entry* cur = vec.mpBegin;
    cur->pos = 0.0f;
    cur->end = RectW(cur->win->GetArea()) + cur->pos;
    float x = cur->end;

    IWindow* sel = mLayout->FindWindowByID(0x7bd2dc0, 1);
    sel->SetFlag(1, false);
    {
        ISub* q = (ISub*)sel->QueryInterface(0x8ed27e7a);
        WinX* wx = q ? (WinX*)((char*)q - 0x20c) : 0;
        wx->mSub.SetState(4, false);
    }

    for (int i = 0; i < 8; ++i) {
        ++cur;
        cur->pos = x;
        bool vis;
        if ((unsigned)i <= 8)
            vis = i < g_pTabHost->mpMgr->GetCount();
        else
            vis = false;
        cur->vis = vis;
        if (!vis)
            continue;
        x += 32.0f;
        cur->end = x;
        IWindow* w = cur->win;
        if (i == selected) {
        Image* img = GetWindowImage(w->FindChild(0x7428d90, 0), 0);
        sel->SetFlag(1, true);
        {
            ISub* q = (ISub*)sel->QueryInterface(0x8ed27e7a);
            WinX* wx = q ? (WinX*)((char*)q - 0x20c) : 0;
            wx->mSub.SetState(4, true);
        }
        if (cur->win->IsFocusedChild(0))
            GetWindowManager()->Focus(0, sel);
        cur->win->SetFlag(1, false);
        cur->win = sel;
        IWindow* picture = sel->FindChild(0x7428d90, 0);
        SetDrawableImage(picture, img, 0);
        {
            Rect r = *picture->GetArea();
            float dh = ((float)img->mHeight - (r.b - r.t)) * 0.5f;
            r.t = r.t - dh;
            r.r = (((float)img->mWidth - (r.r - r.l)) * 0.5f) * 2.0f + r.r;
            r.b = r.b + dh;
            picture->SetArea(&r);
        }
        TabInfo* info = g_pTabHost->mpMgr->GetTab(i);
        {
            CStr label(0xefdb68ec, 0x760b0f8, 0);
            cur->win->FindChild(0x7959d08, 1)->SetText(label.GetText());
            IWindow* nameWin = cur->win->FindChild(0x743b978, 1);
            const wchar_t* nameText = info->mName.GetText();
            if (nameWin) {
                ITextStyle* ts = (ITextStyle*)nameWin->QueryInterface(0xcf428691);
                if (ts) {
                    ts->SetLimit(0x20);
                    ts->SetText(nameText, 0);
                }
            }
            IWindow* descWin = cur->win->FindChild(0x710a140, 1);
            const wchar_t* descText = info->mDesc.GetText();
            if (descWin) {
                ITextStyle* ts = (ITextStyle*)descWin->QueryInterface(0xcf428691);
                if (ts) {
                    ts->SetLimit(0xc0);
                    ts->SetText(descText, 0);
                }
            }
            cur->win->FindChild(0x743bc38, 1)->SetFlag(1, g_pTabHost->mpMgr->GetCount() > 1);
            bool hasIcon = info->mIcon != -1;
            IWindow* w1 = mLayout->FindWindowByID(0x7462210, 1);
            if (w1) {
                ISub* q = (ISub*)w1->QueryInterface(0x8ed27e7a);
                if (q)
                    q->SetState(4, hasIcon);
            }
            IWindow* w2 = mLayout->FindWindowByID(0x7467fa8, 1);
            if (w2)
                w2->SetFlag(1, hasIcon);
            IWindow* w3 = mLayout->FindWindowByID(0x7c3fbfe, 1);
            if (w3)
                w3->SetFlag(1, hasIcon);
            if (hasIcon) {
                if (mStrip) {
                    mStrip->SetActive(true);
                    mStrip->Select(info->mIcon);
                }
                IWindow* w4 = mLayout->FindWindowByID(0x7e1fe70, 1);
                bool flag = info->mFlag;
                if (w4) {
                    ISub* q = (ISub*)w4->QueryInterface(0x8ed27e7a);
                    if (q)
                        q->SetState(4, flag);
                }
                CStr tip;
                if (info->mFlag)
                    tip.Load(0xc0152a6d, 0x615ffa8, 0);
                else
                    tip.Load(0xc0152a6d, 0x615ffa7, 0);
                SetTooltipText(w4, tip.GetText(), -1, 1);
            }
            ++cur;
            cur->vis = g_pTabHost->mpMgr->GetCount() < 8;
            if (cur->win)
                cur->win->SetFlag(2, true);
            CStr tip2(0xf3108302, 0x74663b1, 0);
            SetTooltipText(cur->win, tip2.GetText(), -1, 1);
            if (cur->vis) {
                cur->pos = x;
                x += 32.0f;
                cur->end = x;
            }
        }
        } else {
            if (w) {
                ISub* q = (ISub*)w->QueryInterface(0x8ed27e7a);
                WinX* wx = q ? (WinX*)((char*)q - 0x20c) : 0;
                wx->mSub.SetState(4, false);
            }
        }
    }

    ++cur;
    cur->pos = x;
    cur->end = RectW(cur->win->GetArea()) + cur->pos;
    x = cur->end;

    float shown = 0.0f;
    for (unsigned k = 0; k < (unsigned)(vec.mpEnd - vec.mpBegin); ++k) {
        Entry* e = &vec.mpBegin[k];
        e->win->SetFlag(1, e->vis);
        if (e->vis) {
            shown = shown + 1.0f;
            container->AddChild(e->win);
        }
    }

    float spare = (shown - 1.0f) * 4.0f + (cw - x);
    uint32_t selId = selected + 0x743b8e1;
    float run = 4.0f;
    for (unsigned k = 0; k < (unsigned)(vec.mpEnd - vec.mpBegin); ++k) {
        Entry* e = &vec.mpBegin[k];
        if (e->vis) {
            float width = e->end - e->pos;
            run = run - 4.0f;
            e->pos = run;
            if (ids[k] == selId)
                width = width + spare;
            run = run + width;
            e->end = run;
        }
    }

    for (unsigned k = 0; k < (unsigned)(vec.mpEnd - vec.mpBegin); ++k) {
        Entry* e = &vec.mpBegin[k];
        if (e->vis) {
            Rect r;
            r.l = e->pos;
            r.t = 0.0f;
            r.r = e->end;
            r.b = ch;
            e->win->SetArea(&r);
        }
    }
}

// ---------------------------------------------------------------- stubs (incomplete)
void FUN_00edbfc0(void) {}
void FUN_00edcb40(void) {}
void FUN_00edcd30(void) {}
void FUN_00edce70(void) {}
