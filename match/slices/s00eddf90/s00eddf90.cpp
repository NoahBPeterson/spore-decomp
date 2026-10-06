// Slice s00eddf90 -- scenario edit-mode behavior UI and creature-field setters.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef void  (__thiscall *FV_v)(void*);
typedef void* (__thiscall *FV_p)(void*);
typedef void  (__thiscall *FV_i)(void*, int);
typedef void* (__thiscall *FV_ip)(void*, int);
typedef void  (__thiscall *FV_ii)(void*, int, int);
typedef void  (__thiscall *FV_iip)(void*, int, int, void*);

void  __cdecl FUN_00edcf60(void*);            // 0xedcf60
void* __cdecl FUN_00edd240(void*, int, int);  // 0xedd240
void  __cdecl SPUIHelpers_SetWindowImage(void*, void*); // 0x807bb0
void  __cdecl FUN_00571db0(int,int,int,int,int);
void  __cdecl FUN_00f45a80(void);
void  __cdecl FUN_00f3c0b0(void);
extern char* g_16c7aa4;
void* __fastcall FUN_00ed85e0(void*);
void  __fastcall FUN_00ed8610(void*);

// ================================================================ 0x00eddf90 (approximate)
void __cdecl FUN_00eddf90(int* w)
{
    if (w == 0) return;
    ((FV_i)(*(void***)w)[0x7c / 4])(w, 1);
    ((FV_ip)(*(void***)w)[0xf0 / 4])(w, 0x7918378);
    ((FV_ip)(*(void***)w)[0xf0 / 4])(w, 0x742cd10);
    FUN_00edcf60(0);
}

// ================================================================ 0x00ede040 (approximate)
void __cdecl FUN_00ede040(int* w, int a, int b)
{
    (void)a;
    if (w == 0) return;
    int* p = (int*)((FV_ip)(*(void***)w)[0xf0 / 4])(w, 0x742d068);
    if (p) ((FV_i)(*(void***)p)[0x7c / 4])(p, 1);
    if (b != -1) {
        int* q = (int*)((FV_ip)(*(void***)w)[0xf0 / 4])(w, 0x742c8d0);
        if (q) ((FV_i)(*(void***)q)[0x7c / 4])(q, 1);
        int* r = (int*)((FV_ip)(*(void***)w)[0xf0 / 4])(w, 0x742c8f8);
        if (r) ((FV_i)(*(void***)r)[0x7c / 4])(r, 1);
        if (r) SPUIHelpers_SetWindowImage(r, (void*)FUN_00edd240(0, b, -1));
    }
}

// ================================================================ 0x00ede110 (approximate)
int __cdecl FUN_00ede110(int a, int b, int c)
{
    (void)a; (void)b; (void)c;
    return 0;
}

// ================================================================ setters
#define DEF_SETTER(NAME, OFF)                                                    \
int __cdecl NAME(int p1, int p2, float v)                                        \
{                                                                                \
    char* s = (char*)p1;                                                          \
    float fv = *(float*)(p2 + OFF);                                               \
    if (*(s + 0x20) == 0) {                                                       \
        if (v != fv) { FUN_00f45a80(); return 1; }                                \
        FUN_00f3c0b0(); return 0;                                                 \
    }                                                                             \
    int n = (*(int*)(s + 0x74) - *(int*)(s + 0x70)) / 0x4e0;                       \
    char* e = (char*)(*(int*)(s + 0x70) + OFF);                                    \
    int i = 0;                                                                    \
    for (; i < n; i++, e += 0x4e0) if (*(float*)e != v) break;                     \
    if (i == n && v == fv) { FUN_00f3c0b0(); return 0; }                          \
    int m = (*(int*)(s + 0x74) - *(int*)(s + 0x70)) / 0x4e0;                       \
    int j = 0, k = 0;                                                             \
    for (; j < m; j++, k += 0x4e0) *(float*)(*(int*)(s + 0x70) + k + OFF) = fv;    \
    FUN_00f45a80(); return 1;                                                      \
}

DEF_SETTER(FUN_00ede400, 0x484)
DEF_SETTER(FUN_00ede530, 0x4a0)
DEF_SETTER(FUN_00ede660, 0x49c)
DEF_SETTER(FUN_00ede790, 0x498)
DEF_SETTER(FUN_00ede8c0, 0x490)
DEF_SETTER(FUN_00ede9f0, 0x494)

// ================================================================ 0x00ede2b0 (offset 0x48c + bytes)
int __cdecl FUN_00ede2b0(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x48c);
    if (*(s + 0x20) == 0) {
        if (v != fv) { FUN_00f45a80(); return 1; }
        FUN_00f3c0b0(); return 0;
    }
    int n = (*(int*)(s + 0x74) - *(int*)(s + 0x70)) / 0x4e0;
    char* e = (char*)(*(int*)(s + 0x70) + 0x48c);
    int i = 0;
    for (; i < n; i++, e += 0x4e0) if (*(float*)e != v) break;
    if (i == n && v == fv) { FUN_00f3c0b0(); return 0; }
    int m = (*(int*)(s + 0x74) - *(int*)(s + 0x70)) / 0x4e0;
    int j = 0, k = 0;
    for (; j < m; j++, k += 0x4e0) {
        *(float*)(*(int*)(s + 0x70) + k + 0x48c) = fv;
        *(unsigned char*)(*(int*)(s + 0x70) + k + 2) = *(unsigned char*)(p2 + 2);
        *(unsigned char*)(*(int*)(s + 0x70) + k + 1) = *(unsigned char*)(p2 + 1);
    }
    FUN_00f45a80(); return 1;
}

// ================================================================ 0x00edeb20
struct ObjEB20 { void* f(); };
void* ObjEB20::f()
{
    char* s = (char*)this;
    *(int*)(s + 4) = 0x13ec458;
    *(int*)(s + 8) = 0;
    *(int*)(s + 0xc) = 0x14426a0;
    *(int*)s = 0x148a864;
    *(int*)(s + 4) = 0x148a854;
    *(int*)(s + 0xc) = 0x148a838;
    *(int*)(s + 0x10) = 0;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x20) = -1;
    *(int*)(s + 0x24) = 0;
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x30) = 0;
    *(int*)(s + 0x34) = 0;
    FUN_00ed85e0(s + 0x48);
    return s;
}

// ================================================================ 0x00edebb0
struct ObjEBB0 { void f(); };
void ObjEBB0::f()
{
    char* s = (char*)this;
    *(int*)s = 0x148a864;
    *(int*)(s + 4) = 0x148a854;
    *(int*)(s + 0xc) = 0x148a838;
    if (*(int*)(s + 0x70) != 0) {
        int h = *(int*)(s + 0x70);
        *(int*)(s + 0x70) = 0;
        FUN_00571db0(h, *(int*)(s + 0x74), *(int*)(s + 0x78), *(int*)(s + 0x7c), *(int*)(s + 0x80));
    }
    FUN_00ed8610(s + 0x48);
    if (*(int**)(s + 0x34)) ((FV_v)(*(void***)*(int**)(s + 0x34))[4 / 4])(*(int**)(s + 0x34));
    if (*(int**)(s + 0x30)) ((FV_v)(*(void***)*(int**)(s + 0x30))[4 / 4])(*(int**)(s + 0x30));
    if (*(int**)(s + 0x18)) ((FV_v)(*(void***)*(int**)(s + 0x18))[4 / 4])(*(int**)(s + 0x18));
    if (*(int**)(s + 0x10)) ((FV_v)(*(void***)*(int**)(s + 0x10))[8 / 4])(*(int**)(s + 0x10));
    *(int*)(s + 0xc) = 0x13eb938;
    *(int*)(s + 4) = 0x13ec458;
    *(int*)s = 0x13eb394;
}

// ================================================================ 0x00edec50 (approximate)
void __fastcall FUN_00edec50(void* self, int a, int b)
{
    (void)self; (void)a; (void)b;
}
