// Slice s00edbfc0 -- asset-browser / swatch item UI glue (linked-list lookups).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

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

// ---------------------------------------------------------------- stubs (incomplete)
void FUN_00edbfc0(void) {}
void FUN_00edc0e0(void) {}
void FUN_00edcb40(void) {}
void FUN_00edcd30(void) {}
void FUN_00edce70(void) {}
