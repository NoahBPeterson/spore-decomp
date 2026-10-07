// Slice s00964190: EA::UTFWinControls::WinButton (retail layout) event handlers, IWinButton thunks
// (this = WinButton+0x20c), OnRebuild and CalcSize.
// Retail layout differs from the dev PDB, so fields are accessed by raw offset (F macro) and virtual calls
// go through typed thiscall slot casts. WinButton sub-objects: +0 primary vptr, +4 IWindow vptr,
// +0x20c IWinButton vptr (flag byte at +0x210, button type at +0x214).
#include "types.h"

#define F(T, o) (*(T*)((char*)this + (o)))
#define VT(p, off) ((*(void***)(p))[(off) / 4])
#define VC0(R, p, off) (((R(__thiscall*)(void*))VT(p, off))(p))
#define VC1(R, A, p, off, a) (((R(__thiscall*)(void*, A))VT(p, off))(p, a))
#define VC2(R, A, B, p, off, a, b) (((R(__thiscall*)(void*, A, B))VT(p, off))(p, a, b))
#define VC3(R, A, B, C, p, off, a, b, c) (((R(__thiscall*)(void*, A, B, C))VT(p, off))(p, a, b, c))

template <class T> inline const T& eastl_max(const T& a, const T& b) { return b < a ? a : b; }

struct Msg {
    uint32_t src, dst, id;
    uint32_t p0, p1, p2, p3;
};

struct DropShadow {
    void SetMode1(uint32_t);               // 0x00830280
    void SetMode2(uint32_t);               // 0x00830150
    void F96e740(uint32_t h, uint32_t a, uint32_t b, int r, uint32_t c, uint32_t ch, bool flag);  // 0x0096e740
};
struct LineLayout {
    void Clear(int all);  // 0x0089cbc0
};
struct Typesetter {
    int  F89dc00(const uint16_t* text, int len, float l, float t, float r, float b, void* style, void* layout, int flags);  // 0x0089dc00
    void LayoutLine(const uint16_t* text, int len, float x, float y, void* style);  // 0x0089db20
};
struct StyleManager {
    void* GetStyle(uint32_t id, int arg);  // 0x00894670
};
StyleManager* __cdecl GetStyleManager(bool create);                              // 0x00885bd0
struct RenderContext { uint32_t Begin2D(int arg); };                              // 0x0095bc10
struct IMgr2;
IMgr2* __cdecl GetManager();                                                  // 0x00957f30

struct RenderContext;
struct IObjVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void* V10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual bool V8c();
};
struct IWinVt;
struct IFocusMgr {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void* GetFocus(int);
    virtual void SetFocus(int, IWinVt*);
    virtual void ReleaseFocus(int, IWinVt*);
};
struct IWinVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual IObjVt* GetObj();
    virtual void s18();
    virtual void s1c();
    virtual uint32_t V20();
    virtual void s24();
    virtual uint32_t GetFlags();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void SetFlags(uint32_t);
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void SetFlag(uint32_t, bool);
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void V90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sa0();
    virtual void sa4();
    virtual void sa8();
    virtual void sac();
    virtual void Vb0(void*);
    virtual void sb4();
    virtual void sb8();
    virtual void sbc();
    virtual void sc0();
    virtual void sc4();
    virtual void sc8();
    virtual void scc();
    virtual void sd0();
    virtual void sd4();
    virtual void sd8();
    virtual void sdc();
    virtual void se0();
    virtual void se4();
    virtual void se8();
    virtual void sec();
    virtual void sf0();
    virtual void sf4();
    virtual void sf8();
    virtual void sfc();
    virtual void s100();
    virtual void s104();
    virtual void s108();
    virtual void s10c();
    virtual void s110();
    virtual void Send(Msg*);
};
struct IBtnVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void SetFlag(uint32_t, bool);
};
struct IPrimVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void V4c(int, void*);
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void V88(uint32_t);
    virtual void s8c();
    virtual void s90();
    virtual void V94(uint32_t);
    virtual void V98();
    virtual void V9c();
};
struct IMgr2 {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void* V48(int);
};
struct IDrawVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void* Query(uint32_t);
};
struct IPainterVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void Paint(void*, void*, void*);
    virtual void s14();
    virtual void GetSize(float*, int, int);
};

struct IfWB;
struct WB {
    IWinVt* W() { return (IWinVt*)((char*)this + 4); }
    IBtnVt* Btn() { return (IBtnVt*)((char*)this + 0x20c); }
    IPrimVt* P() { return (IPrimVt*)this; }
    IFocusMgr* Mgr() { return *(IFocusMgr**)((char*)this + 0x34); }
    bool OnButtonClicked(int a);
    bool OnKeyDown(int a, int b, int c);
    bool OnKeyUp(int a, int b, int c);
    bool OnMouseDown(int a, int b, int c, uint32_t f);
    bool OnMouseUp(int a, int b, int c, uint32_t f);
    bool OnFocusChange(int a, void* w);
    bool OnTick();
    void SerUpdate();
    bool OnRebuild(RenderContext* rc);
    bool CalcSize(int a, float* out);
    void WindowSerUpdate();                       // 0x009614a0
    void WindowOnPaint(RenderContext* rc);        // 0x00960310
};

struct Win4 {                                      // IWindow subobject at WinButton+4
    void SetFlag(uint32_t mask, uint32_t val);     // 0x00961760
    void InvalidateLayout();                       // 0x009609b0
    void F964610();
    void F964640(uint32_t m, uint32_t v);
};

// ---- 0x00964190 ----
bool WB::OnButtonClicked(int arg)
{
    IWinVt* w = W();
    if (W()->GetFlags() & 2) {
        void* ic = (char*)this + 0x20c;
        int type = F(int, 0x214);
        switch (type) {
        case 2:
            Btn()->SetFlag(4, (uint8_t)(~(F(uint32_t, 0xac) >> 2)) & 1);
            break;
        case 3:
            Btn()->SetFlag(4, 1);
            Btn()->SetFlag(0x20, 1);
            break;
        }
        Msg m1;
        m1.id = 0x287259f6;
        m1.p0 = F(uint32_t, 0x84) ? F(uint32_t, 0x84) : F(uint32_t, 0x80);
        m1.p1 = w->V20();
        m1.p2 = (F(uint32_t, 0xac) >> 2) & 1;
        m1.p3 = arg;
        W()->Send(&m1);
        Msg m2;
        if (F(int, 0x214) == 2 || F(int, 0x214) == 3) {
            m2.id = 0x18;
            m2.p0 = F(uint32_t, 0x84);
            m2.p1 = 0;
            m2.p2 = (F(uint32_t, 0xac) >> 2) & 1;
        } else {
            m2.id = 0x17;
            m2.p0 = F(uint32_t, 0x84);
        }
        W()->Send(&m2);
    }
    return true;
}

// ---- 0x009642d0 ----
bool WB::OnKeyDown(int a, int b, int c)
{
    if (a == 0)
        return false;
    if (a >= 2 && b != 0x7d8)
        return false;
    if (!(F(uint32_t, 0xac) & 2)) {
        Btn()->SetFlag(2, 1);
        if (F(uint8_t, 0x218) & 1)
            P()->V94(c);
    }
    return true;
}

// ---- 0x00964330 ----
bool WB::OnKeyUp(int a, int b, int c)
{
    void* w = this ? (char*)this + 4 : 0;
    void* r = Mgr()->GetFocus(1);
    if (r == w && (F(uint32_t, 0xac) & 2))
        return false;
    if (a == 0)
        return false;
    if (a >= 2 && b != 0x7d8)
        return false;
    if (F(uint32_t, 0xac) & 2) {
        Btn()->SetFlag(2, 0);
        if (!(F(uint8_t, 0x218) & 1))
            P()->V94(c);
    }
    return true;
}

// @ 0x009643c0
bool WB::OnMouseDown(int a, int b, int c, uint32_t f)
{
    if (!(f & 8) || (f & 0x30))
        return false;
    void* w = this ? (char*)this + 4 : 0;
    if (Mgr()->GetFocus(1) != w)
        {
            IFocusMgr* m = Mgr();
            void** vt = *(void***)m;
            ((void(__thiscall*)(void*, int, void*))vt[0x58 / 4])(m, 1, W());
        }
    uint32_t fl = F(uint32_t, 0xac);
    if (!(fl & 2) && (fl & 8)) {
        Btn()->SetFlag(2, 1);
        if (F(uint8_t, 0x218) & 1)
            P()->V94(f);
    }
    return true;
}

// @ 0x00964450
bool WB::OnMouseUp(int a, int b, int c, uint32_t f)
{
    if (!(f & 8)) {
        void* w = this ? (char*)this + 4 : 0;
        if (Mgr()->GetFocus(1) == w)
            {
            IFocusMgr* m = Mgr();
            void** vt = *(void***)m;
            ((void(__thiscall*)(void*, int, void*))vt[0x5c / 4])(m, 1, W());
        }
        if (F(uint32_t, 0xac) & 2) {
            Btn()->SetFlag(2, 0);
            if (!(F(uint8_t, 0x218) & 1))
                P()->V94(f);
        }
        return true;
    }
    return false;
}

// ---- 0x009644d0 ----
bool WB::OnFocusChange(int a, void* other)
{
    IWinVt* w = W();
    if (!(W()->GetFlags() & 2))
        return false;
    void* ic = (char*)this + 0x20c;
    if (a == 1) {
        if (other == w) {
            Btn()->SetFlag(8, 1);
            void** vt = *(void***)Btn();
            ((void(__thiscall*)(void*, uint32_t, bool))vt[0x28 / 4])(Btn(), 2, Mgr()->GetFocus(1) == w);
            return true;
        }
        Btn()->SetFlag(8, 0);
        Btn()->SetFlag(2, 0);
        Btn()->SetFlag(0x10, 0);
        return true;
    }
    Btn()->SetFlag(0x10, other == w);
    if (other != w)
        Btn()->SetFlag(2, 0);
    return true;
}

// ---- 0x009645a0 ----
bool WB::OnTick()
{
    P()->V98();
    return true;
}

// ---- IWinButton thunks (this = WinButton + 0x20c) ----
struct IfWB {
    int vptr;
    bool flag;          // +4
    char pad5[3];
    uint32_t f8;        // +8
    uint32_t fc;        // +0xc
    uint32_t f10;       // +0x10
    uint32_t f14;       // +0x14
    void F9645c0(uint32_t a);
    void F964900(void* o);
    void F964970(uint32_t v);
    void F964a20(uint32_t v);
    void F964a50(uint32_t v);
    void F964a90(uint32_t v);
    void F964ac0(uint32_t v);
    void* GetDrawable();
    void Dirty()
    {
        if (flag == 0) {
            flag = 1;
            ((IWinVt*)((char*)this - 0x208))->SetFlag(8, 1);
        }
    }
};

// 0x009645c0
void IfWB::F9645c0(uint32_t a)
{
    char* wb = (char*)this - 0x20c;
    ((IPrimVt*)wb)->V98();
    ((IPrimVt*)wb)->V88(a);
    ((IWinVt*)((char*)this - 0x208))->V90();
}

// 0x00964610
void Win4::F964610()
{
    char* wb = (char*)this - 4;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
    InvalidateLayout();
}

// 0x00964640
void Win4::F964640(uint32_t m, uint32_t v)
{
    SetFlag(m, v);
    if (m & 2) {
        uint32_t cur = (*(uint32_t*)((char*)this + 0x28) >> 1) & 1;
        if ((*(uint32_t*)((char*)this + 0xa8) & 1) ^ cur) {
            ((IBtnVt*)((char*)this + 0x208))->SetFlag(1, cur == 1);
            char* wb = (char*)this - 4;
            if (*(uint8_t*)(wb + 0x210) == 0) {
                *(uint8_t*)(wb + 0x210) = 1;
                ((IWinVt*)(wb + 4))->SetFlag(8, 1);
            }
            IMgr2* mgr = GetManager();
            void** vt = *(void***)wb;
            ((void(__thiscall*)(void*, int, void*))vt[0x4c / 4])(wb, 1, mgr->V48(1));
        }
    }
}

// 0x00964710: AutoRefCount-style set
struct IRef { virtual void AddRef(); virtual void Release(); };
struct RefHolder {
    int pad;
    IRef* p;
    uint8_t b;
    void Set(IRef* np, uint8_t nb);
};
void RefHolder::Set(IRef* np, uint8_t nb)
{
    if (np != p) {
        if (p)
            p->Release();
        p = np;
        if (np)
            np->AddRef();
    }
    b = nb;
}

// 0x00964770 / 0x009647b0: text-size helpers (x = glyph width * k, y = glyph height)
struct TextSized {
    int pad[4];
    char* font;          // +0x10 -> object with ints at +0x1c / +0x20
    bool F964770(float* out, int, int);
    bool F9647b0(float* out, int, int);
};
bool TextSized::F964770(float* out, int, int)
{
    if (font != 0) {
        out[0] = (float)*(int*)(font + 0x1c) * 0.25f;
        out[1] = (float)*(int*)(font + 0x20);
        return true;
    }
    return false;
}
bool TextSized::F9647b0(float* out, int, int)
{
    if (font != 0) {
        out[0] = (float)*(int*)(font + 0x1c) * 0.16666667f;
        out[1] = (float)*(int*)(font + 0x20);
        return true;
    }
    return false;
}

// 0x00964890
void WB::SerUpdate()
{
    char* wb = (char*)this;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
    WindowSerUpdate();
    DropShadow* ds = (DropShadow*)((char*)this + 0x860);
    ds->SetMode1(F(uint32_t, 0x860));
    ds->SetMode2(F(uint32_t, 0x864));
    Btn()->SetFlag(1, (F(uint32_t, 0x2c) >> 1) & 1);
}

// 0x00964900
void IfWB::F964900(void* o)
{
    char* wb = (char*)this - 0x20c;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
    void* r = o ? ((IObjVt*)o)->V10() : 0;
    ((IWinVt*)(wb + 4))->Vb0(r);
}

// 0x00964950 (this = WinButton + 0x2c)
struct Sub2c {
    void* GetDrawable();
};
void* Sub2c::GetDrawable()
{
    void* p = *(void**)((char*)this - 0x2c);
    if (p)
        return ((IDrawVt*)p)->Query(0x2f02135c);
    return 0;
}

// 0x00964970
void IfWB::F964970(uint32_t v)
{
    if (*(uint32_t*)((char*)this - 0x160) == v)
        return;
    if (!(v & 1))
        v &= 0xffffffe5;
    IWinVt* w = (IWinVt*)((char*)this - 0x208);
    w->SetFlags(v);
    char* wb = (char*)this - 0x20c;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
    uint32_t cur = *(uint32_t*)((char*)this - 0x160);
    if ((cur ^ v) & 1) {
        uint32_t b = cur & 1;
        if (((*(uint32_t*)((char*)this - 0x1e0) >> 1) & 1) ^ b) {
            w->SetFlag(2, b == 1);
            IMgr2* mgr = GetManager();
            void** vt = *(void***)wb;
            ((void(__thiscall*)(void*, int, void*))vt[0x4c / 4])(wb, 1, mgr->V48(1));
        }
    }
}

// 0x00964a20 / a50 / a90 / ac0
void IfWB::F964a20(uint32_t v)
{
    fc = v;
    char* wb = (char*)this - 0x20c;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
}
void IfWB::F964a50(uint32_t v)
{
    Dirty();
    f10 = v;
}
void IfWB::F964a90(uint32_t v)
{
    f14 = v;
    char* wb = (char*)this - 0x20c;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
}
void IfWB::F964ac0(uint32_t v)
{
    f8 = v;
    char* wb = (char*)this - 0x20c;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
}

// 0x00964af0: set four floats then dirty
struct IfWB2 {
    int vptr;
    bool flag;
    char pad[0x3c - 5];
    float v3c, v40, v44, v48, v4c, v50;
    char pad54[0x654 - 0x54];
    struct Blk { uint32_t d[10]; } block;
    void F964af0(float a, float b, float c, float d);
    void F964b40(float a, float b);
    void F964b90(const uint32_t* src);
};
void IfWB2::F964af0(float a, float b, float c, float d)
{
    v3c = a;
    v40 = b;
    v44 = c;
    v48 = d;
    char* wb = (char*)this - 0x20c;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
}
void IfWB2::F964b40(float a, float b)
{
    v4c = a;
    v50 = b;
    char* wb = (char*)this - 0x20c;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
}
void IfWB2::F964b90(const uint32_t* src)
{
    block = *(const Blk*)src;
    char* wb = (char*)this - 0x20c;
    if (wb[0x210] == 0) {
        wb[0x210] = 1;
        ((IWinVt*)(wb + 4))->SetFlag(8, 1);
    }
}

// 0x00964bd0: scale a point about the window center when zoomed
struct Point2 { float x, y; Point2(const Point2& o) { x = o.x; y = o.y; } };
struct ZoomWin {
    char pad[0x84];
    float l, t, r, b;       // +0x84..+0x90
    char pad94[0x18c - 0x94];
    float zx;               // +0x18c
    char pad190[0x1a0 - 0x190];
    float zy;               // +0x1a0
    void F960fe0(Point2 p);                       // 0x00960fe0
    void F964bd0(Point2 pt);
};
void ZoomWin::F964bd0(Point2 pt)
{
    float sx = zx;
    float sy = zy;
    if (sx > 1.0f || sy > 1.0f) {
        float hx = (r - l) * 0.5f;
        float hy = (b - t) * 0.5f;
        pt.x = (pt.x - hx) / (sx * 1.1f) + hx;
        pt.y = (pt.y - hy) / (sy * 1.1f) + hy;
    }
    F960fe0(pt);
}

// @ 0x00964c90
bool WB::OnRebuild(RenderContext* rc)
{
    P()->V9c();
    void* painter = F(void*, 0x1e0);
    if (painter == 0) {
        WindowOnPaint(rc);
    } else {
        uint32_t f = F(uint32_t, 0xac);
        bool b2 = (f >> 2) & 1;
        bool b1 = (f >> 1) & 1;
        bool b3 = (f >> 3) & 1;
        uint32_t wf = W()->GetFlags();
        uint32_t st[4];
        st[0] = 0;
        st[1] = 0;
        st[2] = F(uint32_t, 0x1dc);
        st[3] = F(uint32_t, 0x1d8);
        if (!((wf >> 1) & 1))
            st[0] = 1;
        int type = F(int, 0x214);
        if (type == 2 || type == 3) {
            if (b3) st[0] = 2;
            if (b2) st[0] |= 8;
            if (b1) st[0] |= 3;
        } else if (b1) {
            st[0] = 3;
        } else if (b3) {
            st[0] = 2;
        }
        ((IPainterVt*)painter)->Paint(rc, (char*)this + 0x228, st);
    }
    if (F(uint16_t*, 0xb0) != F(uint16_t*, 0xb4)) {
        StyleManager* sm = GetStyleManager(true);
        if (sm) {
            char* style = (char*)sm->GetStyle(F(uint32_t, 0xc0), 0);
            if (style) {
                uint32_t oldv = *(uint32_t*)(style + 0x224);
                *(uint32_t*)(style + 0x224) = F(uint32_t, 0x224);
                float l = F(float, 0x258) + F(float, 0x238);
                float t = F(float, 0x25c) + F(float, 0x23c);
                float r = F(float, 0x258) + F(float, 0x240);
                float b = F(float, 0x25c) + F(float, 0x244);
                LineLayout* ll = (LineLayout*)((char*)this + 0x7b0);
                ll->Clear(1);
                Typesetter* ts = (Typesetter*)((char*)this + 0x280);
                int res = ts->F89dc00(F(uint16_t*, 0xb0), (F(int, 0xb4) - F(int, 0xb0)) >> 1, l, t, r, b, style, ll, 0x14);
                uint32_t h = rc->Begin2D(0);
                bool flag = W()->GetObj()->V8c();
                ((DropShadow*)((char*)this + 0x860))->F96e740(h, F(uint32_t, 0x7dc), F(uint32_t, 0x804), res,
                                                             F(uint32_t, 0x224), *F(uint16_t*, 0xb0), flag);
                *(uint32_t*)(style + 0x224) = oldv;
            }
        }
    }
    return true;
}

// @ 0x00964f10
bool WB::CalcSize(int a, float* out)
{
    if (a != 0)
        return false;
    out[0] = eastl_max(F(float, 0x90) - F(float, 0x88), 14.0f);
    out[1] = eastl_max(F(float, 0x94) - F(float, 0x8c), 14.0f);
    float lxy[2];
    lxy[0] = 0.0f;
    lxy[1] = 0.0f;
    void* obj = F(void*, 0x1e0);
    if (obj)
        ((IPainterVt*)obj)->GetSize(lxy, 0, 0);
    if ((obj == 0 || (lxy[0] == 0.0f && lxy[1] == 0.0f)) && F(uint16_t*, 0xb0) == F(uint16_t*, 0xb4))
        return false;
    float pw = out[0];
    float tx = 0.0f, ty = 0.0f;
    float fv7 = 0.0f, fv8 = 0.0f;
    if (F(uint16_t*, 0xb0) != F(uint16_t*, 0xb4)) {
        StyleManager* sm = GetStyleManager(true);
        if (sm) {
            char* style = (char*)sm->GetStyle(F(uint32_t, 0xc0), 0);
            if (style) {
                float bh = F(float, 0x240) - F(float, 0x238);
                if (bh < 1.0f)
                    bh = 100.0f;
                LineLayout* ll = (LineLayout*)((char*)this + 0x7b0);
                Typesetter* ts = (Typesetter*)((char*)this + 0x280);
                ll->Clear(1);
                ts->F89dc00(F(uint16_t*, 0xb0), (F(int, 0xb4) - F(int, 0xb0)) >> 1, 0.0f, 0.0f, bh, 10000.0f, style, ll, 0);
                if (F(uint32_t, 0x858) < 2) {
                    ll->Clear(1);
                    ts->LayoutLine(F(uint16_t*, 0xb0), (F(int, 0xb4) - F(int, 0xb0)) >> 1, 0.0f, 0.0f, style);
                }
                float cnt = (float)F(uint32_t, 0x858);
                tx = (F(float, 0x848) + F(float, 0x254)) + F(float, 0x24c);
                ty = ((F(float, 0x850) - F(float, 0x854)) * cnt + F(float, 0x250)) + F(float, 0x248);
                fv7 = tx;
                fv8 = ty;
            }
        }
    }
    if (!(F(uint8_t, 0x218) & 2)) {
        pw = eastl_max(lxy[0], fv8);
    } else {
        uint32_t m = F(uint32_t, 0x21c);
        if (m != 0) {
            if (m > 2) {
                if (m == 3)
                    pw = lxy[0];
            } else {
                pw = fv8 + lxy[0];
            }
        }
    }
    float ph = eastl_max(lxy[1], fv7);
    out[0] = eastl_max(pw, 14.0f);
    out[1] = eastl_max(ph, 14.0f);
    return true;
}
