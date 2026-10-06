// Slice s008068d0 (w2g6 #17): SPUIHelpers window/drawable helpers + allocator pieces.
// 32-bit MSVC 2008 SP1. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" void* SP_WindowManager();
extern "C" void* FUN_0067dd60();
extern "C" void* FUN_009512c0();
extern "C" void* FUN_009512d0(int, int, const char*, void*);
extern "C" void* FUN_008051b0(int);
extern "C" void* FUN_008055a0(void*);
extern "C" char  FUN_008055c0(void*, void*);
extern "C" char  FUN_0082aa20(void*, void*, int);
extern "C" void  FUN_0082a450();
extern "C" void  FUN_0082a500();
extern "C" void  FUN_008053e0();
extern "C" void  FUN_00805400();
extern "C" void* GetImageFromLayout(void*, int);           // 0x008061c0
extern "C" void  FUN_00926640(void*);
struct ObjDtor { void dtor(); };
extern "C" void  FUN_00830cf0(void*, int);
extern "C" void  FUN_00830d10(void);
extern "C" void  FUN_008311f0(void);
extern "C" void* operator_new(unsigned size, const char* name, int, int, int, int);  // 0x00f473a0
extern "C" void  operator_delete(void*);                   // 0x00f47380

struct StdDraw {
    void  SetImageIcon(int, void*);     // 0x00831760
    void  SetImageIconColor(int, void*);// 0x00831380
    void  GetIconColor(void*, int);     // 0x00830d60
    int   FUN_00830d10(int);            // 0x00830d10
    void  FUN_008311f0(int, int);       // 0x008311f0
    void* Pick(int);                    // 0x00830cf0
};
struct StdDrawCtor { void* ctor(); };   // 0x00988420
struct ImgDrawCtor { void* ctor(); };   // 0x0097d8d0
struct ScrollCtor  { void* ctor(); };   // 0x0082a040
struct Layout { void Shutdown(int); };  // 0x00811ad0 (cSPUILayout::Shutdown, this=+8)
struct Tooltip { void SetText(void*, void*, void*); };  // 0x00835ed0

extern unsigned char DAT_01544384;
extern unsigned char DAT_01544388;
extern unsigned char DAT_0154438c;
extern unsigned char DAT_01544390;
extern float DAT_01471064;
extern void* PTR_FUN_01417958;
extern void* PTR_FUN_01403934;

typedef uint32_t u32;

#define S(n) virtual void* v##n();
struct W {
    S(00) S(04) S(08)
    virtual void* m0c(int);          // +0x0c
    virtual void* m10(int);          // +0x10
    virtual void  m14(int);          // +0x14
    S(18)
    S(1c) S(20) S(24) S(28) S(2c) S(30)
    S(34) S(38)
    S(3c) S(40) S(44) S(48) S(4c) S(50) S(54) S(58) S(5c) S(60)
    virtual void  m64(float, float); // +0x64
    S(68)
    virtual void  m6c(void*);        // +0x6c
    virtual void  m70(float, float); // +0x70
    S(74) S(78) S(7c) S(80) S(84) S(88)
    virtual void  m8c(int);          // +0x8c
    S(90) S(94) S(98) S(9c) S(a0) S(a4) S(a8) S(ac)
    virtual void  mB0(void*);        // +0xb0
    virtual void* mB4(int);          // +0xb4
    virtual void  mB8(int, void*);   // +0xb8
    S(bc)
    virtual void* mC0(void*, int, int);// +0xc0
    S(c4) S(c8) S(cc) S(d0) S(d4) S(d8) S(dc) S(e0) S(e4) S(e8) S(ec)
    S(f0) S(f4) S(f8) S(fc) S(100) S(104)
    virtual void  m108(void*);       // +0x108
    virtual void* m10c(void*);       // +0x10c
};

static inline void* VSlot(void* p, unsigned byteOff) {
    return (void*)&((void**)*(void**)p)[byteOff / 4];
}

// @ 0x008068d0
char FUN_008068d0(W* w, int param2, int param3) {
    W* a; W* b; void* alloc; void* mem; void* obj; W* sd; W* im; void* r;
    void* curp;
    if (w == 0) return 0;
    a = (W*)w->va8();
    if (a != 0) a = (W*)a->m0c(0x103c1908);
    else a = 0;
    b = (W*)w->va8();
    if (b != 0) b = (W*)b->m0c(0xef3c47cf);
    else b = 0;
    if (a != 0) goto do_assign;
    if (b != 0) goto lab2;
    alloc = FUN_009512c0();
    if ((unsigned)param3 < 8u) {
        mem = FUN_009512d0(0x7c, 4, "UI/StdDrawable", alloc);
        sd = 0;
        if (mem != 0) {
            obj = ((StdDrawCtor*)mem)->ctor();
            sd = obj ? (W*)((char*)obj + 0xc) : 0;
        }
        r = FUN_008055a0(sd);
        w->mB0(r);
        if (sd == 0) return 1;
        a = sd;
        goto do_assign;
    }
    mem = FUN_009512d0(0x50, 4, "UI/ImageDrawable", alloc);
    im = 0;
    if (mem != 0) {
        obj = ((ImgDrawCtor*)mem)->ctor();
        if (obj != 0) im = (W*)((char*)obj + 0xc);
    }
    if (im != 0) {
        r = im->m0c(0x6ec581fd);
        w->mB0(r);
        b = im;
    } else {
        w->mB0(0);
    }
    if (b == 0) return 1;
lab2:
    {
        curp = (void*)(*(void*(__thiscall**)(void*))VSlot(b, 0x18))(b);
        if (curp != (void*)param2) {
            (*(void(__thiscall**)(void*, int))VSlot(b, 0x14))(b, param2);
            w->v90();
        }
    }
    return 1;
do_assign:
    {
        if (param3 < 0 || param3 >= 8) param3 = 0;
        curp = (void*)(*(void*(__thiscall**)(void*, int))VSlot(a, 0x10))(a, param3);
        if (curp == (void*)w) return 1;
        (*(void(__thiscall**)(void*, int, void*))VSlot(a, 0x14))(a, param3, w);
        w->v90();
    }
    return 1;
}

// @ 0x00806a60
char FUN_00806a60(W* w, void* layout, int id, int param4) {
    void* img = GetImageFromLayout(layout, id);
    if (img == 0) return 0;
    if (param4 == -1) param4 = 0;
    return FUN_008068d0(w, (int)img, param4);
}

// @ 0x00806aa0
char FUN_00806aa0(W* w, int idx) {
    if (w == 0) return 0;
    W* d = (W*)w->va8();
    if (d == 0) return 0;
    StdDraw* sd = (StdDraw*)d->m0c(0x53eb526);
    if (sd == 0) return 0;
    if (idx < 0 || idx >= 8) idx = 0;
    void* cur = sd->Pick(idx);
    if (cur != (void*)w) {
        sd->SetImageIcon(idx, w);
        w->v90();
    }
    return 1;
}

// @ 0x00806b20
char FUN_00806b20(W* w, int param2, int param3) {
    if (w == 0 || param3 == 0) return 0;
    W* d = (W*)w->va8();
    if (d == 0) return 0;
    StdDraw* sd = (StdDraw*)d->m0c(0x53eb526);
    if (sd == 0) return 0;
    int count = param3;
    int tmp = 8;
    int* arr;
    if (count > 8) arr = &tmp;
    else arr = &param2;
    param2 = *arr;
    int changed = 0;
    for (int i = 0, u = 0; i < 8; i++, u++) {
        int v = ((int*)w)[((count <= u) ? 0 : u)];
        int cur = sd->FUN_00830d10(i);
        if (cur != v) {
            changed = 1;
            sd->FUN_008311f0(i, v);
        }
    }
    if (changed) w->v90();
    return 1;
}

// @ 0x00806bf0 SPUIHelpers::SetWindowAreaToParent
void SetWindowAreaToParent(W* w) {
    if (w == 0) return;
    W* p = (W*)w->m10(0);
    if (p == 0) return;
    float* a = (float*)p->v38();
    float wd = a[2] - a[0];
    float hd = a[3] - a[1];
    float r[4];
    r[0] = 0; r[1] = 0; r[2] = wd; r[3] = hd;
    w->m6c(r);
}

// @ 0x00806c60
float* FUN_00806c60(float* out, void* wp) {
    W* w = (W*)wp;
    out[0] = 0; out[1] = 0;
    if (w == 0) return out;
    float* a = (float*)w->v34();
    out[0] = a[0];
    float* b = (float*)w->v34();
    out[1] = b[1];
    return out;
}

// @ 0x00806ca0
void FUN_00806ca0(W* w, float x, float y) {
    if (w == 0) return;
    float* a = (float*)w->v34();
    w->m64(x - (a[2] - a[0]) * DAT_01471064, y - (a[3] - a[1]) * DAT_01471064);
}

// @ 0x00806d10 SP::Pollinator
void Pollinator(W* w, float* r) {
    if (w == 0) return;
    float* a = (float*)w->v38();
    float x = r[0];
    float dy = (((r[3] - r[1]) - (a[3] - a[1])) * 0.5f + r[1]);
    float dx = (((r[2] - x) - (a[2] - a[0])) * 0.5f + x);
    (*(void(__thiscall**)(void*, float, float))VSlot(w, 0x64))(w, dx, dy);
}

// @ 0x00806db0
unsigned char FUN_00806db0(W* w, void* p) {
    w->m8c(*(int*)p);
    w->v90();
    return *(unsigned char*)((char*)p + 4);
}

// @ 0x00806de0 SPUIHelpers::SetTooltipText
void SetTooltipText(W* w, void* text) {
    if (w == 0) return;
    W* it = (W*)w->m10c(0);
    if (it == 0) return;
    for (;;) {
        Tooltip* t = (Tooltip*)(*(void*(__thiscall**)(void*, int))VSlot(it, 0xc))(it, 0x3796ce5);
        if (t != 0) { t->SetText(text, w, (void*)0); return; }
        it = (W*)w->m10c(it);
        if (it == 0) return;
    }
}

// @ 0x00806e40 SPUIHelpers::AutoSizeWindowForText
void AutoSizeWindowForText(W* w, int param2) {
    if (w == 0) return;
    float* a = (float*)w->v38();
    float wd = a[2] - a[0];
    W* p = (W*)w->m0c(0x8ed27e7a);
    if (p == 0) p = (W*)w->m0c(0x0f15f4bd);
    if (p != 0) p->m14(param2);
    if ((char)wd != 0) {
        float* b = (float*)w->v38();
        w->m70((b[0] + 0.0f) - (b[2] - b[0]), b[1]);
    }
}

// @ 0x00806ee0
void FUN_00806ee0(W* w) {
    if (w == 0) return;
    W* d = (W*)w->va8();
    if (d == 0) return;
    StdDraw* sd = (StdDraw*)d->m0c(0x53eb526);
    if (sd == 0) return;
    float pad[2];
    for (int i = 0; i < 8; i++) {
        sd->GetIconColor(pad, i);
        pad[0] = pad[0] + 0.0f;
        sd->SetImageIconColor(i, pad);
    }
}

// @ 0x00806f50
int __fastcall FUN_00806f50(void* s) {
    float* f = (float*)s;
    if (f[3] == 0.0f && f[4] == 0.0f && f[5] == 1.0f && f[6] == 1.0f) {
        if (FUN_008055c0((char*)s + 0x1c, &DAT_01544384)) return 1;
    }
    return 0;
}

// @ 0x00806fc0
void FUN_00806fc0(W* w) {
    if (w == 0) return;
    W* p = (W*)FUN_008051b0(0x3ec2e62);
    if (p == 0) return;
    float* d = (float*)p->m0c(0x3ec2e62);
    if (d != 0) {
        d[5] = 1.0f;   // +0x14
        d[6] = 1.0f;   // +0x18
        if ((char)FUN_00806f50(d)) w->m108(p);
    }
    w->v98();
    w->v90();
}

// @ 0x00807040
void FUN_00807040(W* w) {
    if (w == 0) return;
    W* p = (W*)FUN_008051b0(0x3ec2e62);
    if (p == 0) return;
    unsigned* d = (unsigned*)p->m0c(0x3ec2e62);
    if (d != 0) {
        d[7] = *(unsigned*)&DAT_01544384;   // +0x1c
        d[8] = *(unsigned*)&DAT_01544388;   // +0x20
        d[9] = *(unsigned*)&DAT_0154438c;   // +0x24
        d[10] = *(unsigned*)&DAT_01544390;  // +0x28
        if ((char)FUN_00806f50(d)) w->m108(p);
    }
    w->v98();
    w->v90();
}

// @ 0x008070d0 SPUIHelpers::AnchorWindowToScreen
void AnchorWindowToScreen(float* rect, W* win, int flags, W* other) {
    float lx = rect[0], ly = rect[1], lz = rect[2], lw = rect[3];
    float* wa = (float*)win->v38();
    float wd = wa[2] - wa[0];
    float hd = wa[3] - wa[1];
    float t1[2];
    win->mC0(t1, 0, 0);
    float t2[2];
    win->mC0(t2, 0, 0);
    float fx = 0, fy = 0;
    if (flags & 0x800) { lw = 0; }
    else if (flags & 0x200) { fx = (t1[1] + ly) * 0.5f; fy = (lz + fy) * 0.5f; fy = fy - fx; }
    else {
        if (flags & 1) { lw = ly - lw; }
        else if (flags & 2) { fx = ly; fy = fx - /*??*/0; }
        else if (flags & 4) { lw = t1[1] - lw; }
        else if (flags & 8) { fx = t1[1]; fy = fx - 0; }
    }
    (void)wd; (void)hd;
    if (!(flags & 0x400)) {
        if (flags & 0x100) { /* centered */ }
    }
    W* tgt = other ? other : win;
    float* ta = (float*)tgt->v38();
    float r2[4];
    r2[0] = ta[0] + fx;
    r2[1] = ta[1] + fy;
    r2[2] = ta[2] + fx;
    r2[3] = ta[3] + fy;
    tgt->m6c(r2);
}

// @ 0x00807340 SPUIHelpers::AnchorWindowToWindow
void AnchorWindowToWindow(W* w) {
    float* a = (float*)w->v38();
    float hd = a[3] - a[1];
    float t1[2];
    float zero = 0.0f;
    w->mC0(t1, 0, 0);
    float t2[2];
    w->mC0(t2, 0, 0);
    float rect[4];
    rect[0] = t1[0];
    rect[1] = t2[1];
    rect[2] = 0;
    rect[3] = 0;
    AnchorWindowToScreen(rect, w, 0, 0);
    (void)hd; (void)zero;
}

// @ 0x00807430
void FUN_00807430(W* w, float v) {
    W* o;
    if (w == 0) o = 0;
    else o = (W*)w->m0c(0x10edf11);
    float x = v * 100.0f;
    if (x <= 0.0f) x = 0.0f;
    if (x >= 100.0f) x = 100.0f;
    (*(void(__thiscall**)(void*, float))VSlot(o, 4))(o, x);
}

// @ 0x008074a0 SPUIHelpers::DestroyRolloverFrame
char DestroyRolloverFrame(W* w) {
    if (w == 0) return 0;
    W* a = (W*)w->mB4(0x4a61af0);
    if (a != 0) a = (W*)a->m0c(0x4a61af0);
    else a = 0;
    if (a != 0) a->v00();
    w->mB8(0x4a61af0, 0);
    if (a != 0) ((Layout*)((char*)a + 8))->Shutdown(1);
    W* b = (W*)w->mB4(0x4a61af1);
    if (b != 0) b = (W*)b->m0c(0x4a61af0);
    else b = 0;
    W* keep = a;
    if (b != a) {
        if (b != 0) b->v00();
        keep = b;
        if (a != 0) a->v04();
    }
    w->mB8(0x4a61af1, 0);
    if (keep != 0) {
        ((Layout*)((char*)keep + 8))->Shutdown(1);
        keep->v04();
    }
    return 1;
}

// @ 0x00807590 SPUIHelpers::RemoveWindowCallback
void RemoveWindowCallback(W* w, int cb) {
    if (w == 0 || cb == 0) return;
    W* it = (W*)w->m10c(0);
    if (it == 0) return;
    for (;;) {
        void* h = (void*)(*(void*(__thiscall**)(void*, int))VSlot(it, 0xc))(it, 0x4a61af2);
        if (h != 0 && *(int*)((char*)h + 0xc) == cb) break;
        it = (W*)w->m10c(it);
        if (it == 0) return;
    }
    w->m108(it);
}

// @ 0x00807600
void* FUN_00807600(void* p1, void* p2, void* p3) {
    void* piVar5 = 0;
    void* mem = operator_new(0x48, "UI/ScrollFrameVertical", 0, 0, 0, 0);
    void* sf = 0;
    if (mem != 0) sf = ((ScrollCtor*)mem)->ctor();
    if (sf != 0) (*(void(__thiscall**)(void*))VSlot(sf, 0))(sf);
    char ok = FUN_0082aa20(p1, p3, 0);
    if (ok == 0) {
        if (sf != 0) {
            (*(void(__thiscall**)(void*))VSlot(sf, 4))(sf);
            return 0;
        }
    } else {
        piVar5 = *(void**)((char*)sf + 0x10);
        ((W*)piVar5)->mB8(0x4a61af1, sf);
        void* q = *(void**)((char*)sf + 0x18);
        *(void**)p2 = q;
        (*(void(__thiscall**)(void*))VSlot(q, 0))(q);
        (*(void(__thiscall**)(void*))VSlot(sf, 4))(sf);
    }
    return piVar5;
}

// @ 0x00807690
char FUN_00807690(W* w) {
    W* a = (W*)w->mB4(0x4a61af1);
    if (a == 0) return 0;
    W* b = (W*)a->m0c(0x4a61af2);
    if (b == 0) return 0;
    b->v00();
    FUN_0082a500();
    b->v04();
    return 1;
}

// @ 0x008076f0
char FUN_008076f0(W* w) {
    if (w == 0) return 0;
    W* a = (W*)w->mB4(0x4a61af0);
    if (a == 0) return 0;
    W* b = (W*)a->m0c(0x4a61af2);
    if (b == 0) return 0;
    b->v00();
    w->mB8(0x4a61af0, 0);
    FUN_0082a450();
    b->v04();
    return 1;
}

struct FixedAllocCtor {
    void* ctor(int, int, int, int, int, void*, void*, int);  // EA::Allocator::FixedAllocatorBase
};

// @ 0x00807760
void* __fastcall FUN_00807760(void* p) {
    *(void**)p = &PTR_FUN_01417958;
    int local8 = 5;
    int iVar4 = 0x10;
    void* cur = p;
    do {
        cur = (char*)cur + 4;
        int local4 = (iVar4 + 0x9c3) / iVar4;
        int* pi = &local8;
        if (local4 > 4) pi = &local4;
        void* mem = operator_new(0x20, "UI/FixedAllocationBin", 0, 0, 0, 0);
        void* obj = 0;
        if (mem != 0) {
            obj = ((FixedAllocCtor*)mem)->ctor(iVar4, 0, *pi, 0, -1, (void*)FUN_008053e0, (void*)FUN_00805400, 0);
        }
        *(void**)cur = obj;
        iVar4 += 0x10;
    } while (iVar4 < 0x9f0);
    return p;
}

// @ 0x008077f0
void __fastcall DoErase(void* p) {
    *(void**)p = &PTR_FUN_01417958;
    void** cur = (void**)((char*)p + 4);
    int n = 0x9e;
    do {
        void* v = *cur;
        if (v != 0) {
            ((ObjDtor*)v)->dtor();
            operator_delete(v);
        }
        *cur = 0;
        cur++;
        n--;
    } while (n != 0);
    *(void**)p = &PTR_FUN_01403934;
}
