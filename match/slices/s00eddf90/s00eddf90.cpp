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
void  __fastcall FUN_00f45a80(void* mgr); // 0xf45a80
void  __fastcall FUN_00f3c0b0(void* mgr); // 0xf3c0b0
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

// ================================================================ creature-field setters
// Six copies of the same setter (one float field at a fixed offset inside each 0x4e0-byte fragment);
// FUN_00ede2b0 (0x48c) additionally copies two flag bytes out of the incoming struct.
// Shape notes (0xede400 family): the original keeps its status byte in bl, sets it right before the
// notify/kill call of each arm and shares one kill block between the short and the main arm; every
// count expression is recomputed per iteration.
#define MGR (*(void**)(g_16c7aa4 + 0x74))
#define FIELD_COUNT(s) ((*(volatile int*)((s) + 0x74) - *(volatile int*)((s) + 0x70)) / 0x4e0)
#define DEF_FRAG(NAME, OFF) \
    struct NAME { char pad0[OFF]; float f; char pad1[0x4e0 - OFF - 4]; };

DEF_FRAG(Frag484, 0x484)
DEF_FRAG(Frag4a0, 0x4a0)
DEF_FRAG(Frag49c, 0x49c)
DEF_FRAG(Frag498, 0x498)
DEF_FRAG(Frag490, 0x490)
DEF_FRAG(Frag494, 0x494)
DEF_FRAG(Frag48c, 0x48c)

// @ 0x00ede400
bool __cdecl FUN_00ede400(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x484);
    char r;
    int i;
    Frag484* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag484*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag484*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede530
bool __cdecl FUN_00ede530(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x4a0);
    char r;
    int i;
    Frag4a0* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag4a0*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag4a0*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede660
bool __cdecl FUN_00ede660(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x49c);
    char r;
    int i;
    Frag49c* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag49c*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag49c*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede790
bool __cdecl FUN_00ede790(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x498);
    char r;
    int i;
    Frag498* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag498*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag498*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede8c0
bool __cdecl FUN_00ede8c0(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x490);
    char r;
    int i;
    Frag490* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag490*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag490*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede9f0
bool __cdecl FUN_00ede9f0(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x494);
    char r;
    int i;
    Frag494* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag494*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) ((Frag494*)*(int*)(s + 0x70))[i].f = fv;
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
}

// @ 0x00ede2b0
bool __cdecl FUN_00ede2b0(int p1, int p2, float v)
{
    char* s = (char*)p1;
    float fv = *(float*)(p2 + 0x48c);
    char r;
    int i;
    Frag48c* e;
    if (*(s + 0x20) != 0) {
        for (i = 0, e = (Frag48c*)*(int*)(s + 0x70); i < FIELD_COUNT(s); i++, e++)
            if (e->f != v) goto store;
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else {
          store:
            r = 1;
            for (i = 0; i < FIELD_COUNT(s); i++) {
                ((Frag48c*)*(int*)(s + 0x70))[i].f = fv;
                ((char*)*(int*)(s + 0x70))[i * 0x4e0 + 2] = ((char*)p2)[2];
                ((char*)*(int*)(s + 0x70))[i * 0x4e0 + 1] = ((char*)p2)[1];
            }
            FUN_00f45a80(MGR);
        }
    } else {
        if (v == fv) { r = 0; FUN_00f3c0b0(MGR); }
        else { r = 1; FUN_00f45a80(MGR); }
    }
    return r;
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
