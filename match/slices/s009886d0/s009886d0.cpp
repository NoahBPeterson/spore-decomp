// Slice s009886d0 -- EA::UTFWinControls::WinText / WinTextEdit members.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// Real C++ member functions of the UTFWin text window class.  Field accesses go
// through byte offsets (macro F/FF) because only a handful of members are known,
// but the virtual calls are declared as genuine virtual methods on interface
// structs so the compiler emits the original `mov eax,[ecx]; mov edx,[eax+slot];
// call edx` shape (a __fastcall cast would force an extra `xor edx,edx`).
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uintptr_t;

#define F(o, off)   (*(uint32_t*)((uint8_t*)(o) + (off)))
#define FF(o, off)  (*(float*)((uint8_t*)(o) + (off)))
#define GF(addr)    (*(float*)(uintptr_t)(addr))

// ---------------------------------------------------------------------------
// Interface layouts.  Each struct carries enough dummy virtuals to place the
// slots the slice actually calls at the right offsets.  Slot N lives at byte
// offset 4*N.
// ---------------------------------------------------------------------------

// The object at this+4 of the WinText object.  Virtual slot N is at byte 4*N.
struct Iface {
    virtual void  s00();                             // slot 0
    virtual void  s01();                             // 0x04
    virtual void  s02();
    virtual void* s03();                             // 0x0c
    virtual void  s04();                             // 0x10
    virtual void* s05();                             // 0x14  returns object with vtable
    virtual void  s06();
    virtual uint8_t s07(uint32_t);                   // 0x1c
    virtual char  s08(void*, uint32_t, uint32_t);    // 0x20
    virtual void  s09();
    virtual uint32_t s10();                          // 0x28
    virtual void  s11(); virtual void s12(); virtual void s13();
    virtual void  s14(); virtual void s15();
    virtual void  s16(void*, int);                   // 0x40
    virtual void  s17(); virtual void s18(); virtual void s19();
    virtual void  s20(); virtual void s21(); virtual void s22();
    virtual void  s23(uint32_t, uint32_t);           // 0x5c
    virtual void  s24(); virtual void s25(); virtual void s26();
    virtual void  s27(void*);                        // 0x6c
    virtual void  s28(); virtual void s29(); virtual void s30();
    virtual void  s31(); virtual void s32(); virtual void s33();
    virtual void  s34();
    virtual void  s35(uint32_t, void*);              // 0x8c
    virtual void  s36();                             // 0x90
    virtual void  s37(); virtual void s38(); virtual void s39();
    virtual void  s40(); virtual void s41(); virtual void s42();
    virtual void  s43(); virtual void s44(); virtual void s45();
    virtual void  s46(); virtual void s47(); virtual void s48();
    virtual void  s49(); virtual void s50(); virtual void s51();
    virtual void  s52(); virtual void s53(); virtual void s54();
    virtual void  s55(); virtual void s56(); virtual void s57();
    virtual void  s58(); virtual void s59(); virtual void s60();
    virtual void  s61(); virtual void s62();
    virtual char  s63(int);                          // 0xfc
    virtual char  s64(uint32_t);                     // 0x100
    virtual void  s65(); virtual void s66(); virtual void s67();
    virtual void  s68();
    virtual void  s69(void*);                        // 0x114
};

// The WinText object itself is a Window whose vtable slots 0x1c..0x94 are used.
// Virtual slot N lives at byte offset 4*N.
struct WinBase {
    virtual void  v00();                           // slot 0
    virtual void  v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void  v05(); virtual void v06();
    virtual void* v07(uint32_t);                   // 0x1c
    virtual void  v08(); virtual void v09();
    virtual uint32_t v10();                        // 0x28
    virtual void  v11(); virtual void v12();
    virtual void  v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void  v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void  v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void  v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void  v29();
    virtual void  v30(int, int, int, int, int);   // 0x78
    virtual void  v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void  v35(uint32_t, void*);           // 0x8c
    virtual void  v36();                          // 0x90
    virtual void  v37(uint32_t, uint32_t);        // 0x94
};

// The Window subobject at this-0x208 (Ghidra's WinText this-pointer).
struct SubWin {
    virtual void  c00();                           // slot 0
    virtual void  c01(); virtual void c02(); virtual void c03(); virtual void c04();
    virtual void  c05(); virtual void c06(); virtual void c07(); virtual void c08();
    virtual void  c09(); virtual void c10(); virtual void c11(); virtual void c12();
    virtual void  c13(); virtual void c14(); virtual void c15(); virtual void c16();
    virtual void  c17(); virtual void c18(); virtual void c19(); virtual void c20();
    virtual void  c21(); virtual void c22(); virtual void c23(); virtual void c24();
    virtual void  c25(); virtual void c26();
    virtual void  c27(void*);                     // 0x6c
    virtual void  c28(); virtual void c29(); virtual void c30(); virtual void c31();
    virtual void  c32(); virtual void c33(); virtual void c34(); virtual void c35();
    virtual void  c36();                          // 0x90
};

// ---------------------------------------------------------------------------
// The WinText object: only the members this slice touches are described.
// ---------------------------------------------------------------------------
struct WinText {
    WinBase w;                       // +0x000 vtable pair (base)

    // Members used through byte offsets by the bodies below.
    // 0x009886d0
    void __thiscall m_9886d0(int* p);
    // 0x00988710
    void __thiscall m_988710(uint32_t flag, uint8_t value);
    // 0x00988760
    void __thiscall m_988760(void* p);
    // 0x00988780
    void __thiscall m_988780(int v);
    // 0x009887b0
    void __thiscall m_9887b0(float v);
    // 0x009887e0
    void __thiscall m_9887e0(float a, float b, float c, float d);
    // 0x00988860
    void __thiscall m_988860(uint32_t v);
    // 0x00988890
    void __thiscall m_988890();
    // 0x009888c0
    void __thiscall m_9888c0(uint32_t v);
    // 0x00988920
    uint8_t __thiscall m_988920(void* ctx, Iface* styleMgr);
    // 0x00988ad0
    uint8_t __thiscall m_988ad0(uint32_t p2, float* out);
    // 0x00988c40
    void __thiscall m_988c40(uint32_t p2);
    // 0x00988c90
    void __thiscall m_988c90(uint32_t p2);
    // 0x00988cd0
    uint8_t __thiscall m_988cd0(float* out, uint8_t p3, uint8_t p4);
    // 0x00988f60
    char __thiscall m_988f60(uint32_t p2, float* p3);
    // 0x00988f90
    void __thiscall m_988f90();
    // 0x00989000
    WinText* __thiscall m_989000();
    // 0x009890d0
    WinText* __thiscall m_9890d0(uint8_t p2);
    // 0x00989130
    static WinText* __cdecl Factory(void* p1);
    // 0x00989240
    void __thiscall m_989240(uint32_t p2);
    // 0x00989290
    uint32_t __thiscall m_989290(uint32_t i);
    // 0x009892b0
    void __thiscall m_9892b0(uint32_t i, uint32_t v);
    // 0x00989370
    void __thiscall m_989370(uint32_t v);
    // 0x00989390
    void __thiscall m_989390(uint32_t a, uint32_t b, uint32_t c);
    // 0x009893b0
    void __thiscall m_9893b0(uint32_t a, uint32_t b);
    // 0x009893d0
    void __thiscall m_9893d0(uint32_t a);
    // 0x00989410
    void __thiscall m_989410(uint32_t a, uint8_t flag);
    // 0x00989450
    int __thiscall m_989450(int, int, int, int, int);
    // 0x00989460
    void __thiscall m_989460(uint32_t v);
    // 0x009894a0
    uint32_t __thiscall m_9894a0(uint32_t i);
    // 0x009894c0
    char __thiscall m_9894c0(int, int, int, int);
    // 0x00989500
    uint32_t __thiscall m_989500(uint32_t p2, uint32_t p3);
    // 0x00989660
    void __thiscall m_989660(uint8_t p2);
};

// ---------------------------------------------------------------------------
// Callees.  Functions that use the __thiscall ABI are declared as member
// functions of an opaque type so the compiler emits `mov ecx,self; call`
// without materialising an extra register (__fastcall would emit `xor edx,edx`).
// ---------------------------------------------------------------------------
extern "C" void* __cdecl EA_Text_GetStyleManager(int unk);                      // 0x885bd0
extern "C" void  __cdecl FUN_00951330(void*);                                   // 0x951330
extern "C" void* __cdecl FUN_009512c0(void);                                    // 0x9512c0
extern "C" void* __cdecl FUN_009512d0(int, int, const char*, void*);            // 0x9512d0

// Thunks: method shapes only, bodies live in the original image.
struct C_894670 { void* __thiscall GetStyle(uint32_t, void*); };
struct C_89cbc0 { void __thiscall Clear(int); };
struct C_89dc00 { void* __thiscall Layout(uint32_t, int, uint32_t, uint32_t,
                                         float, float, void*, void*, void*); };struct C_95bc10 { void* __thiscall Begin2D(void*); };
struct C_96e740 { int __thiscall Run(void*, uint32_t, uint32_t, void*, int, int, int); };
struct C_9614a0 { void __thiscall SerUpdate(); };
struct C_830280 { void __thiscall SetMode1(int); };
struct C_830150 { void __thiscall SetMode2(int); };
struct C_950bb0 { void __thiscall Rem(void*); };
struct C_961760 { void __thiscall SetFlag(uint32_t, uint8_t); };
struct C_961f20 { void __thiscall Set(void*); };
struct C_8323d0 { void __thiscall Dtor(); };
struct C_89c540 { void __thiscall Dtor(); };
struct C_962740 { void __thiscall Free(); };
struct C_962a10 { void __thiscall Ctor(); };
struct C_89d820 { void __thiscall Ctor(int); };
struct C_898bd0 { void __thiscall Ctor(int); };
struct C_960310 { void __thiscall OnPaint(void*); };

// @ 0x009886d0
void __thiscall WinText::m_9886d0(int* p)
{
    if (p[2] == 0x76376e3) {
        uint32_t base = (uint32_t)(this ? (uint8_t*)this + 4 : 0);
        if (base == (uint32_t)*p) {
            ((Iface*)((uint8_t*)this + 4))->s36();
        }
    }
    ((C_950bb0*)this)->Rem(p);
}

// @ 0x00988710
void __thiscall WinText::m_988710(uint32_t flag, uint8_t value)
{
    uint8_t old = (uint8_t)w.v10();
    ((C_961760*)this)->SetFlag(flag, value);
    if (((old ^ 0xff) & 1) != 0) {
        if ((uint8_t)w.v10() & 1) {
            F(this, 0x804) = 0;
        }
    }
}

// @ 0x00988760
void __thiscall WinText::m_988760(void* p)
{
    ((C_961f20*)this)->Set(p);
    F(this, 0x804) = 0;
}

// @ 0x00988780
void __thiscall WinText::m_988780(int v)
{
    if (F(this, 4) != (uint32_t)v) {
        F(this, 4) = v;
        ((SubWin*)((uint8_t*)this - 0x208))->c36();
    }
}

// @ 0x009887b0
void __thiscall WinText::m_9887b0(float v)
{
    if (FF(this, 8) != v) {
        SubWin* s = (SubWin*)((uint8_t*)this - 0x208);
        void (__thiscall* fn)(void*) = *(void (__thiscall**)(void*))((void**)*(void**)s + (0x90 / 4));
        FF(this, 8) = v;
        fn(s);
    }
}

// @ 0x009887e0
void __thiscall WinText::m_9887e0(float a, float b, float c, float d)
{
    if (FF(this, 0xc) != a || FF(this, 0x10) != b || FF(this, 0x14) != c || FF(this, 0x18) != d) {
        void* fn = *(void**)(*(uint32_t*)((uint8_t*)this - 0x208) + 0x90);
        FF(this, 0xc)  = a;
        FF(this, 0x10) = b;
        FF(this, 0x14) = c;
        FF(this, 0x18) = d;
        ((void (__thiscall*)(void*))fn)((uint8_t*)this - 0x208);
    }
}

// @ 0x00988860
void __thiscall WinText::m_988860(uint32_t v)
{
    void** vt = *(void***)this;
    void* sm = EA_Text_GetStyleManager(1);
    ((void (__thiscall*)(void*, uint32_t, void*))vt[0x8c / 4])(this, v, sm);
}

// @ 0x00988890
void __thiscall WinText::m_988890()
{
    ((C_9614a0*)this)->SerUpdate();
    void* p = (uint8_t*)this + 0x80c;
    ((C_830280*)p)->SetMode1(F(this, 0x80c));
    ((C_830150*)p)->SetMode2(F(this, 0x810));
}

// @ 0x009888c0
void __thiscall WinText::m_9888c0(uint32_t v)
{
    w.v07(v);
    ((SubWin*)((uint8_t*)this - 0x208))->c36();
}

// @ 0x00988920
uint8_t __thiscall WinText::m_988920(void* ctx, Iface* styleMgr)
{
    ((C_960310*)this)->OnPaint(ctx);
    if (F(this, 0xb0) == F(this, 0xb4)) return 1;
    if (styleMgr == 0) return 1;
    void* style = ((C_894670*)styleMgr)->GetStyle(F(this, 0xc0), 0);
    if (style == 0) return 1;
    float saved = FF(style, 0x200);
    float over = FF(this, 0x214);
    if (over != 0.0f) {
        FF(style, 0x200) = over;
    }
    void* layout = (uint8_t*)this + 0x758;
    ((C_89cbc0*)layout)->Clear(1);
    int w_ = F(this, 0xb4) - F(this, 0xb0);
    float fw = FF(this, 0x94) - FF(this, 0x8c) - FF(this, 0x224);
    float fh = FF(this, 0x90) - FF(this, 0x88) - FF(this, 0x220);
    void* out = ((C_89dc00*)((uint8_t*)this + 0x228))->Layout(F(this, 0xb0), w_ >> 1,
        F(this, 0x218), F(this, 0x21c), fh, fw, style, layout, (void*)0x14);
    void* batch = ((C_95bc10*)ctx)->Begin2D(0);
    Iface* sub = (Iface*)((uint8_t*)this + 4);
    void* unk = sub->s05();
    uint8_t mode = (uint8_t)((uint32_t (__thiscall*)(void*))((void**) *(void**)unk)[0x23])(unk);
    ((C_96e740*)((uint8_t*)this + 0x80c))->Run(batch,
                 F(this, 0x784), F(this, 0x7ac), out,
                 (int)F(this, 0x210), *(uint16_t*)(uintptr_t)F(this, 0xb0), (int)mode);
    FF(style, 0x200) = saved;
    return 1;
}

// @ 0x00988ad0
uint8_t __thiscall WinText::m_988ad0(uint32_t p2, float* out)
{
    if (F(this, 0xb0) != F(this, 0xb4)) {
        void* styleMgr = EA_Text_GetStyleManager(1);
        if (styleMgr != 0) {
            void* style = ((C_894670*)styleMgr)->GetStyle(F(this, 0xc0), 0);
            if (style != 0) {
                float local0 = FF(style, 0x200) * GF(0x14853bc);
                void* layout = (uint8_t*)this + 0x758;
                ((C_89cbc0*)layout)->Clear(1);
                ((C_89dc00*)((uint8_t*)this + 0x228))->Layout(F(this, 0xb0),
                    (F(this, 0xb4) - F(this, 0xb0)) >> 1,
                    0, 0, local0, GF(0x13f6d90), style, layout, (void*)0);
                float y = FF(this, 0x7f4) + FF(this, 0x220) + FF(this, 0x218);
                float lim = GF(0x13f7674);
                float arr[2];
                arr[0] = y;
                arr[1] = lim;
                *out = (y > lim) ? arr[0] : arr[1];
                float fi = (float)(int32_t)F(this, 0x800);
                if ((int32_t)F(this, 0x800) < 0) fi += GF(0x13f4fd0);
                float h = (FF(this, 0x7f8) - FF(this, 0x7fc)) * fi + FF(this, 0x224) + FF(this, 0x21c);
                arr[0] = lim;
                arr[1] = h;
                out[1] = (h > lim) ? arr[1] : arr[0];
                return 1;
            }
        }
    }
    *out = 0.0f;
    out[1] = 0.0f;
    return 0;
}

// @ 0x00988c40
void __thiscall WinText::m_988c40(uint32_t p2)
{
    uint32_t buf[4];
    if (((Iface*)this)->s08(buf, p2, 1)) {
        ((SubWin*)((uint8_t*)this - 0x208))->c27(buf);
    }
    ((SubWin*)((uint8_t*)this - 0x208))->c36();
}

// @ 0x00988c90
void __thiscall WinText::m_988c90(uint32_t p2)
{
    uint32_t buf[4];
    if (((Iface*)this)->s08(buf, p2, 0)) {
        ((SubWin*)((uint8_t*)this - 0x208))->c27(buf);
    }
}

// @ 0x00988cd0
uint8_t __thiscall WinText::m_988cd0(float* out, uint8_t p3, uint8_t p4)
{
    uint8_t* b = (uint8_t*)this;
    if (*(int*)(b - 0x15c) == *(int*)(b - 0x158)) {
        if (p3 != 0) {
            float a = *(float*)(b - 0x180);
            float c = *(float*)(b - 0x17c);
            out[0] = *(float*)(b - 0x184);
            out[1] = a;
            out[2] = c;
            out[3] = a;
            return 1;
        }
        void* sm = EA_Text_GetStyleManager(1);
        if (sm != 0) {
            void* style = ((C_894670*)sm)->GetStyle(*(uint32_t*)(b - 0x14c), 0);
            float a = *(float*)(b - 0x180);
            float c = (*(int*)((uint8_t*)style + 0x244) == 2) ? *(float*)(b - 0x17c)
                                                              : *(float*)(b - 0x184);
            out[0] = c;
            out[1] = a;
            out[2] = c;
            out[3] = a;
            return 1;
        }
        return 0;
    }
    void* sm = EA_Text_GetStyleManager(1);
    if (sm == 0) return 0;
    void* style = ((C_894670*)sm)->GetStyle(*(uint32_t*)(b - 0x14c), 0);
    if (style == 0) return 0;
    void* layout = b + 0x54c;
    ((C_89cbc0*)layout)->Clear(1);
    int i0 = *(int*)(b - 0x15c);
    int half = (*(int*)(b - 0x158) - i0) >> 1;
    if (p3 != 0) {
        ((C_89dc00*)(b + 0x1c))->Layout(i0, half, F(b, 0xc), F(b, 0x10),
            (*(float*)(b - 0x17c) - *(float*)(b - 0x184)) - *(float*)(b + 0x14),
            GF(0x13f6d90), style, layout, (void*)0);
        float f4 = *(float*)(b + 0x5ec);
        float f5 = *(float*)(b + 0x5f0);
        float fa = *(float*)(b - 0x180);
        float fc = *(float*)(b - 0x17c);
        float fi = (float)*(int*)(b + 0x5f4);
        if (*(int*)(b + 0x5f4) < 0) fi += GF(0x13f4fd0);
        out[0] = *(float*)(b - 0x184);
        out[1] = fa;
        out[2] = fc;
        out[3] = ((fi * (f4 - f5) + *(float*)(b + 0x18)) + *(float*)(b + 0x10)) + fa;
        return 1;
    }
    ((C_89dc00*)(b + 0x1c))->Layout(i0, half, F(b, 0xc), F(b, 0x10),
        GF(0x13f6d90), GF(0x13f6d90), style, layout, (void*)0);
    if (p4 != 0 && *(int*)((uint8_t*)style + 0x244) == 2) {
        float fc = *(float*)(b - 0x17c);
        float fa = *(float*)(b - 0x180);
        out[0] = fc - ((*(float*)(b + 0x5e4) + *(float*)(b + 0x14)) + *(float*)(b + 0xc));
        out[2] = fc;
        out[3] = *(float*)(b - 0x178);
        out[1] = fa;
        return 1;
    }
    float fa = *(float*)(b - 0x180);
    float fb = *(float*)(b - 0x184);
    out[0] = fb;
    out[2] = ((*(float*)(b + 0x5e4) + *(float*)(b + 0x14)) + *(float*)(b + 0xc)) + fb;
    out[3] = *(float*)(b - 0x178);
    out[1] = fa;
    return 1;
}

// @ 0x00988f60
char __thiscall WinText::m_988f60(uint32_t p2, float* p3)
{
    if (m_988ad0(p2, p3)) {
        ((Iface*)((uint8_t*)this + 4))->s36();
    }
    return 1;
}

// @ 0x00988f90
void __thiscall WinText::m_988f90()
{
    F(this, 0) = 0x1445530;
    F(this, 4) = 0x1445410;
    F(this, 0x20c) = 0x14453d0;
    ((C_8323d0*)((uint8_t*)this + 0x758))->Dtor();
    ((C_89c540*)((uint8_t*)this + 0x228))->Dtor();
    F(this, 0x20c) = 0x13eb938;
    ((C_962740*)this)->Free();
}

// @ 0x00989000
WinText* __thiscall WinText::m_989000()
{
    ((C_962a10*)this)->Ctor();
    F(this, 0x20c) = 0x14085f0;
    F(this, 0) = 0x1445530;
    F(this, 4) = 0x1445410;
    F(this, 0x20c) = 0x14453d0;
    F(this, 0x210) = 0xffffffff;
    FF(this, 0x214) = 0.0f;
    FF(this, 0x218) = 0.0f;
    FF(this, 0x21c) = 0.0f;
    FF(this, 0x220) = 0.0f;
    FF(this, 0x224) = 0.0f;
    ((C_89d820*)((uint8_t*)this + 0x228))->Ctor(0);
    ((C_898bd0*)((uint8_t*)this + 0x758))->Ctor(0);
    F(this, 0x808) = 0;
    F(this, 0x80c) = 0;
    F(this, 0x810) = 2;
    F(this, 0x814) = 3;
    FF(this, 0x820) = 0.0f;
    FF(this, 0x824) = 0.0f;
    FF(this, 0x818) = 0.0f;
    FF(this, 0x81c) = 0.0f;
    F(this, 0x830) = 0;
    ((C_830150*)((uint8_t*)this + 0x80c))->SetMode2(2);
    return this;
}

// @ 0x009890d0
WinText* __thiscall WinText::m_9890d0(uint8_t p2)
{
    F(this, 0) = 0x1445530;
    F(this, 4) = 0x1445410;
    F(this, 0x20c) = 0x14453d0;
    ((C_8323d0*)((uint8_t*)this + 0x758))->Dtor();
    ((C_89c540*)((uint8_t*)this + 0x228))->Dtor();
    F(this, 0x20c) = 0x13eb938;
    ((C_962740*)this)->Free();
    if (p2 & 1) {
        FUN_00951330(this);
    }
    return this;
}

// @ 0x00989130
WinText* __cdecl WinText::Factory(void* p1)
{
    void* r = FUN_009512d0(0x834, 4, "UTFWin/WinText", FUN_009512c0());
    if (r == 0) return 0;
    WinText* t = ((WinText*)r)->m_989000();
    if (t == 0) return 0;
    Iface* s = (Iface*)((uint8_t*)t + 0x20c);
    if (s != 0) {
        ((void (__thiscall*)(void*, void*))((void**)*(void**)s)[0x28 / 4])(s, p1);
        void* o = ((void* (__thiscall*)(void*))((void**)*(void**)s)[0x10 / 4])(s);
        ((void (__thiscall*)(void*, void*))((void**)*(void**)o)[0x84 / 4])(o, p1);
    }
    return (WinText*)s;
}

// @ 0x00989240
void __thiscall WinText::m_989240(uint32_t p2)
{
    uint32_t buf[7];
    buf[2] = 0x9b1552db;
    uint32_t v = F(this, 0x84);
    if (v == 0) v = F(this, 0x80);
    buf[3] = v;
    Iface* iface = (Iface*)((uint8_t*)this + 4);
    void (__thiscall* fn)(void*, void*) =
        *(void (__thiscall**)(void*, void*))((void**)*(void**)iface + (0x114 / 4));
    buf[4] = p2;
    fn(iface, buf);
}

// @ 0x00989290
uint32_t __thiscall WinText::m_989290(uint32_t i)
{
    if (i <= 7) return F(this, 0x38 + i * 4);
    return 0;
}

// @ 0x009892b0
void __thiscall WinText::m_9892b0(uint32_t i, uint32_t v)
{
    if (i <= 7 && F(this, 0x38 + i * 4) != v) {
        F(this, 0x38 + i * 4) = v;
        ((SubWin*)((uint8_t*)this - 0x208))->c36();
    }
}

// @ 0x00989370
void __thiscall WinText::m_989370(uint32_t v)
{
    if (v != F(this, 0x58)) {
        WinBase* b = (WinBase*)this;
        F(this, 0x58) = v;
        b->v30(v, -1, 0, 0, 1);
    }
}

// @ 0x00989390
void __thiscall WinText::m_989390(uint32_t a, uint32_t b, uint32_t c)
{
    ((WinBase*)this)->v30(F(this, 0x5c), 0, a, b, c);
}

// @ 0x009893b0
void __thiscall WinText::m_9893b0(uint32_t a, uint32_t b)
{
    ((WinBase*)this)->v30(F(this, 0x5c), a, 0, 0, b);
}

// @ 0x009893d0
void __thiscall WinText::m_9893d0(uint32_t a)
{
    ((WinBase*)this)->v30(0, -1, 0, 0, a);
}

// @ 0x00989410
void __thiscall WinText::m_989410(uint32_t a, uint8_t flag)
{
    WinBase* b = (WinBase*)this;
    if (flag) {
        b->v37(a, F(this, 0x60));
    } else {
        b->v37(a, a);
    }
}

// @ 0x00989450
int __thiscall WinText::m_989450(int, int, int, int, int)
{
    return -1;
}

// @ 0x00989460
void __thiscall WinText::m_989460(uint32_t v)
{
    F(this, 0xc) |= 4;
    F(this, 0x10) = v;
}

// @ 0x009894a0
uint32_t __thiscall WinText::m_9894a0(uint32_t i)
{
    return F(this, 0x37c + i * 0x14);
}

// @ 0x009894c0
char __thiscall WinText::m_9894c0(int, int, int, int)
{
    Iface* sub = (Iface*)((uint8_t*)this + 4);
    if (sub->s64(1)) {
        void* o = sub->s05();
        ((void (__thiscall*)(void*, uint32_t, void*))((void**)*(void**)o)[0x5c / 4])(o, 1, sub);
    }
    return 1;
}

// @ 0x00989500
uint32_t __thiscall WinText::m_989500(uint32_t p2, uint32_t p3)
{
    Iface* sub = (Iface*)((uint8_t*)this + 4);
    uint32_t r = sub->s10() >> 4;
    if (r & 1) {
        return r & 0xffffff00;
    }
    switch (p3) {
    case 8: case 0xd: case 0x1b: case 0x20: case 0x21: case 0x22: case 0x23:
    case 0x24: case 0x25: case 0x26: case 0x27: case 0x28: case 0x2e:
    case 0x6a: case 0x6b: case 0x6d: case 0x6e: case 0x6f:
    case 0xba: case 0xbb: case 0xbc: case 0xbd: case 0xbe: case 0xbf: case 0xc0:
    case 0xdb: case 0xdc: case 0xde:
        return 1;
    case 0x2d:
        return ((uint32_t)*(uint8_t*)((uint8_t*)this + 0x214) >> 2) & 1;
    default:
        if ((p3 < 0x41 || p3 > 0x5a) && p3 - 0x30 > 9) {
            return r & 0xffffff00;
        }
        return 1;
    }
}

// @ 0x00989660
void __thiscall WinText::m_989660(uint8_t p2)
{
    uint8_t b;
    if (F(this, 0x2c) & 1) b = p2; else b = 0;
    if (F(this, 0x214) & 0x21) b = 0;
    Iface* sub = (Iface*)((uint8_t*)this + 4);
    if (!sub->s63(0)) {
        b = 0;
    }
    if (b != *(uint8_t*)((uint8_t*)this + 0x600)) {
        *(uint8_t*)((uint8_t*)this + 0x600) = b;
        sub->s36();
    }
}

// @ 0x009896d0
struct AllocIface_9896d0 {
    virtual void* alloc(uint32_t size, uint32_t align);   // slot 0
};

extern "C" char __cdecl sub_9896d0(uint32_t* out, int p2, int p3, uint32_t* allocObj)
{
    uint8_t* c = (uint8_t*)p3;
    uint32_t* src = (uint32_t*)(*(uint8_t**)((uint8_t*)p2 + 4) + *(int*)(c + 0x10));
    uint32_t* dst = (uint32_t*)((AllocIface_9896d0*)allocObj)->alloc(*(int*)(c + 0x14) * 4, 4);
    if (dst != 0) {
        out[1] = (uint32_t)dst;
        out[2] = *(uint32_t*)(c + 0x14);
        out[0] = ((uint32_t*)0x154eea0)[*(uint16_t*)(c + 0xc) & 0xfff];
        uint32_t* s = src;
        uint32_t* d = dst;
        for (uint32_t i = 0; i < *(uint32_t*)(c + 0x14); i++) {
            *d++ = *s++;
        }
        return 1;
    }
    return 0;
}

// @ 0x00989740
extern "C" void __cdecl sub_989740(uint32_t* first, uint32_t* last, uint32_t* dest)
{
    while (first != last) {
        if (dest != 0) {
            dest[0] = first[0];
            dest[1] = first[1];
            dest[2] = first[2];
            *(float*)(dest + 3) = *(float*)(first + 3);
            *(float*)(dest + 4) = *(float*)(first + 4);
            *(float*)(dest + 5) = *(float*)(first + 5);
        }
        first += 6;
        dest += 6;
    }
}

// @ 0x00989790
extern "C" void __cdecl sub_989790(uint32_t* first, uint32_t* last, uint32_t* dest)
{
    while (first != last) {
        dest[0] = first[0];
        dest[1] = first[1];
        dest[2] = first[2];
        *(float*)(dest + 3) = *(float*)(first + 3);
        *(float*)(dest + 4) = *(float*)(first + 4);
        *(float*)(dest + 5) = *(float*)(first + 5);
        first += 6;
        dest += 6;
    }
}

// @ 0x009897d0
extern "C" void __cdecl sub_9897d0(uint32_t* first, uint32_t* last, uint32_t* destEnd)
{
    while (last != first) {
        last -= 6;
        destEnd -= 6;
        destEnd[0] = last[0];
        destEnd[1] = last[1];
        destEnd[2] = last[2];
        *(float*)(destEnd + 3) = *(float*)(last + 3);
        *(float*)(destEnd + 4) = *(float*)(last + 4);
        *(float*)(destEnd + 5) = *(float*)(last + 5);
    }
}
