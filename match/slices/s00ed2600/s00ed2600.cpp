// Slice s00ed2600 -- Simulator palette/UI container glue.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

extern char* g_16c757c;   // 0x016c757c
extern char* g_16c7584;   // 0x016c7584
extern char* g_16c7aa4;   // 0x016c7aa4

// ---------------------------------------------------------------- callees
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);  // 0xf473a0
void  __cdecl operator_delete(void*);                                           // 0xf47380
void  __cdecl FUN_00ed1f00_v(void*);
int   __stdcall FUN_00ed1f00(void*, int);                                         // 0xed1f00
void* __cdecl FUN_00ed1f40_v(void*, void*);
void  __cdecl FUN_00ed3120_v(void*, int, int);
int   __cdecl FUN_00f3c7f0_v(void*);       // thiscall helper (see stub below)
void* __cdecl eastl_RBTreeIncrement(void*); // 0x921580
void  __cdecl eastl_RBTreeErase(void*, void*); // 0x921880
int   __cdecl FUN_00f280f0_v(void*);        // 0xf280f0

// thiscall stubs
struct Pal {
    void* f_ed1f40(void*);
    void  f_ed3120(int, int);
    void* f_280f0();
    void  f_dfbba0();
    void  f_ed3350(int a);
    void  f_ed33a0(int a);
};
struct Obj74 { int f_3c7f0(int); };

// ---------------------------------------------------------------- 0x00ed2970
void __stdcall FUN_00ed2970(int* a, int* b)
{
    for (; a < b; a = (int*)((char*)a + 0x14)) {
        int p = a[1];
        if (p) ((void(__thiscall*)(int))(*(int**)p)[3])(p);
        p = a[0];
        if (p) ((void(__thiscall*)(int))(*(int**)p)[2])(p);
    }
}

// ---------------------------------------------------------------- 0x00ed29b0
int* __cdecl FUN_00ed29b0(int* a, int* b, int* key)
{
    int n = (int)((char*)b - (char*)a) / 0x27e8;
    while (n > 0) {
        int half = n >> 1;
        int* mid = (int*)((char*)a + half * 0x27e8);
        if (*mid < *key) {
            a = (int*)((char*)mid + 0x27e8);
            n = n - 1 - half;
        } else {
            n = half;
        }
    }
    return a;
}

// ---------------------------------------------------------------- 0x00ed2a50 (partial)
void __fastcall FUN_00ed2a50(int* self, int* out, int a, int b, int c, char d)
{
    (void)self; (void)out; (void)a; (void)b; (void)c; (void)d;
}

// ---------------------------------------------------------------- 0x00ed2ae0 (partial)
void __fastcall FUN_00ed2ae0(void* self, void* out, void* node)
{
    (void)self; (void)out; (void)node;
}

// ---------------------------------------------------------------- 0x00ed2bc0 (partial)
void __fastcall FUN_00ed2bc0(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }

// ---------------------------------------------------------------- 0x00ed2e40 (partial)
void __fastcall FUN_00ed2e40(void* self, void* a) { (void)self; (void)a; }

// ---------------------------------------------------------------- 0x00ed2f30 (partial)
void __fastcall FUN_00ed2f30(void* self, int a) { (void)self; (void)a; }

// ---------------------------------------------------------------- 0x00ed2600 (partial)
void __fastcall FUN_00ed2600(void* self, int a, int b, int c) { (void)self; (void)a; (void)b; (void)c; }

// ---------------------------------------------------------------- 0x00ed3120 (partial)
void __fastcall FUN_00ed3120(void* self, void* a, char b) { (void)self; (void)a; (void)b; }

// ---------------------------------------------------------------- 0x00ed3350
void Pal::f_ed3350(int a)
{
    if (a == -2)
        return;
    char* p70 = (char*)this + 0x70;
    if (FUN_00ed1f00(p70, a))
        return;
    void** p = (void**)f_ed1f40(p70);
    if (!p)
        return;
    ((void(__thiscall*)(void*, int))(*(void***)*p)[0x1c / 4])(*p, a);
    f_ed3120((int)p[1], 1);
}

// ---------------------------------------------------------------- 0x00ed33a0
void Pal::f_ed33a0(int a)
{
    void* r = (void*)FUN_00ed1f00((char*)this + 0x70, a);
    if (a != -2 && r) {
        if (((Obj74*)(*(char**)(g_16c7aa4 + 0x74)))->f_3c7f0(a) == 0) {
            void* q = *(void**)r;
            ((void(__thiscall*)(void*))(*(void***)q)[0x20 / 4])(q);
            f_ed3120(((int*)r)[1], 1);
        }
    }
}

// ---------------------------------------------------------------- 0x00ed33f0 (partial)
void __fastcall FUN_00ed33f0(void* self, int a, int b) { (void)self; (void)a; (void)b; }

// ---------------------------------------------------------------- 0x00ed34a0 (partial)
int __cdecl FUN_00ed34a0(int a, int b, int c)
{
    if (a != b) {
        char* p = (char*)(a + 0x78);
        do {
            ((Pal*)(p + 0x2718))->f_280f0();
            char* e = *(char**)(p + 4);
            for (char* i = *(char**)p; i < e; i += 0x4e0)
                ((Pal*)i)->f_dfbba0();
            void* base = *(void**)p;
            if (base && *(int*)((char*)base - 4))
                operator_delete(base);
            c += 0x27e8;
            a += 0x27e8;
            p += 0x27e8;
        } while (a != b);
    }
    return c;
}

// ---------------------------------------------------------------- 0x00ed3570
struct Inner { void copy(Inner* src); };
struct Big27e8 { char pad[0x27e8]; };

int* __cdecl FUN_00ed3570(int* first, int* last, int* dst)
{
    while (last != first) {
        last = (int*)((char*)last - 0x27e8);
        dst  = (int*)((char*)dst  - 0x27e8);
        *dst = *last;
        ((Inner*)((char*)dst + 8))->copy((Inner*)((char*)last + 8));
    }
    return dst;
}

// ---------------------------------------------------------------- 0x00ed35d0 (partial)
void __fastcall FUN_00ed35d0(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }

// ---------------------------------------------------------------- 0x00ed3740 (partial)
int __fastcall FUN_00ed3740(void* self, int a, int b) { (void)self; (void)a; (void)b; return 0; }
