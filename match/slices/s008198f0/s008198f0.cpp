// Slice s008198f0 (batch w2g7 #8), 32-bit MSVC 2008.
// cSPUIPieMenu / cSPUIPieMenuItem bulk destroy + copy helpers.

typedef unsigned int  u32;
typedef unsigned char u8;

struct IWindow;

static inline void Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}

extern "C" void FUN_00818650(void*);
extern "C" void FUN_008191b0_p();
extern "C" int  FUN_008190f0(int, int, int);
struct DestroyHelper { void Fn(); };

// same shape as FUN_008191b0 (slice 7): vtable 0x1418ef8 + release members
static inline void DestroyItem(char* p) {
    *(void**)p = (void*)0x1418ef8;
    ((DestroyHelper*)p)->Fn();
    void* q;
    q = *(void**)(p + 0x30); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x2c); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x28); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x24); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x20); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x1c); if (q) Vv0(q, 0x04);
}

struct Tail5 { float f0, f1, f2, f3; int i; };

// @ 0x00819e00
int __cdecl FUN_00819e00(char* a, char* b, char* c) {
    if (a == b) return (int)c;
    char* dst = c + 0x40;
    char* src = a + 0x40;
    do {
        if (c) {
            FUN_00818650(a);
            Tail5* d = (Tail5*)(dst - 8);
            Tail5* s = (Tail5*)(src - 8);
            d->f0 = s->f0;
            d->f1 = s->f1;
            d->f2 = s->f2;
            d->f3 = s->f3;
            d->i  = s->i;
        }
        a += 0x4c;
        src += 0x4c;
        c += 0x4c;
        dst += 0x4c;
    } while (a != b);
    return (int)c;
}

// @ 0x00819e60
int __cdecl FUN_00819e60(char* a, char* b, int c) {
    if (a == b) return c;
    do {
        DestroyItem(a);
        a += 0x4c;
        c += 0x4c;
    } while (a != b);
    return c;
}

// @ 0x00819f10
void __stdcall FUN_00819f10(char* a, char* b) {
    for (; a < b; a += 0x4c) DestroyItem(a);
}

// ===========================================================================
// incomplete / approximate (see partial.txt)
// ===========================================================================
struct PieStub {
    char pad_00[0x8000];
    void a() { *(volatile int*)pad_00 = 0; }
};
void stub_8198f0(PieStub* p) { p->a(); }
void stub_819ad0(PieStub* p) { p->a(); }
void stub_819f90(PieStub* p) { p->a(); }
void stub_81a1f0(PieStub* p) { p->a(); }
void stub_81a2b0(PieStub* p) { p->a(); }
void stub_81a350(PieStub* p) { p->a(); }
void stub_81a510(PieStub* p) { p->a(); }
void stub_81a6d0(PieStub* p) { p->a(); }
