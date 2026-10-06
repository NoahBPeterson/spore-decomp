// Slice s00ed9150 -- terrain/posse effect placement and UI cursor helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef void  (__thiscall *FV_v)(void*);
typedef void* (__thiscall *FV_p)(void*);
typedef void  (__thiscall *FV_i)(void*, int);
typedef void* (__thiscall *FV_ip)(void*, int);
typedef void  (__thiscall *FV_ii)(void*, int, int);
typedef int   (__thiscall *FV_ir)(void*, int);
typedef int   (__thiscall *FV_r0)(void*);

// thiscall callee stubs
struct S_f3e8a0 { void* f(int); };     // 0xf3e8a0
struct S_f25530 { char f(); };          // 0xf25530

// free callees
void* __cdecl FUN_00ed9040(int, float*);
extern float g_1470f1c;
void  __cdecl FUN_00ed9150(void*, void*, void*, float);
void* __cdecl SP_GetGameTerrainCursor(void);   // 0xb30d70
void  __cdecl FUN_00572020(void*, int);        // 0x572020
void  __cdecl SetGlobalProperty(int, float);   // 0x5ca880
void* __cdecl SP_GameInputManager(void);       // 0xb3d250
void  __cdecl SP_cTribeInputStrategy_ToggleBanningContent(int); // 0xdd17f0
void  __cdecl SP_cUIBanningContent_EndBanMode(int);             // 0xdd1840
void  __cdecl FUN_00e099d0(int);
void  __cdecl FUN_00e09a50(int);
void  __cdecl FUN_00571db0(int,int,int,int,int);
void* __cdecl FUN_00efc510(void);
char  __cdecl FUN_00efcd90(void);
void* __cdecl FUN_0067cab0(void);
int   __cdecl FUN_008013c0(void);
void  __cdecl FUN_00801bb0(int);

// ================================================================ 0x00ed9150 (approximate)
void __cdecl FUN_00ed9150_v(void* a, void* b, void* c, float d)
{
    (void)a; (void)b; (void)c; (void)d;
}

// ================================================================ 0x00ed9560
void FUN_00ed9560(int* out, void* p2, int p3)
{
    int* obj = (int*)FUN_00ed9040(p3, (float*)p2);
    if (obj != 0) {
        float f = g_1470f1c;
        void* v = (void*)((FV_p)(*(void***)obj)[0x2c / 4])(obj);
        FUN_00ed9150(out, p2, v, f);
    }
    char c = (char)((FV_r0)(*(void***)out)[0x10 / 4])(out);
    if (c == 0) {
        if (obj != 0)
            ((FV_i)(*(void***)out)[8 / 4])(out, 0);
    } else {
        if (obj == 0)
            ((FV_i)(*(void***)out)[0xc / 4])(out, 0);
    }
}

// ================================================================ 0x00ed95d0 (approximate)
int __cdecl FUN_00ed95d0(int a, int b)
{
    (void)a; (void)b;
    return 0;
}

// ================================================================ 0x00ed9990 (approximate)
void __fastcall FUN_00ed9990(void* self, int b)
{
    (void)self; (void)b;
}

// ================================================================ 0x00ed9b10
struct Obj9b10 { char pad0[0x50]; char m50; char pad1[0x17]; int* m68; void f(); };
void Obj9b10::f()
{
    char* s = (char*)this;
    if (*(s + 0x50) == 0) {
        *(s + 0x50) = 1;
        int* cur = (int*)SP_GetGameTerrainCursor();
        *(int**)(s + 0x68) = cur;
        ((FV_i)(*(void***)cur)[0xb8 / 4])(cur, 0);
    }
}

// ================================================================ 0x00ed9b40
struct Obj9b40 { void f(int a); };
void Obj9b40::f(int a)
{
    (void)a;
    char* s = (char*)this;
    int v = *(int*)(s + 0x6c);
    if (v != 0) {
        FUN_00572020((void*)v, 0);
        *(int*)(s + 0x6c) = 0;
        SetGlobalProperty(0x8dff6314, 0.0f);
    }
}

// ================================================================ 0x00ed9b80
void FUN_00ed9b80(void)
{
    int* gm = (int*)SP_GameInputManager();
    int st = (int)((FV_p)(*(void***)gm)[0x34 / 4])(gm);
    if (st != 4) {
        SP_cTribeInputStrategy_ToggleBanningContent(1);
        int* gm2 = (int*)SP_GameInputManager();
        ((FV_i)(*(void***)gm2)[0x38 / 4])(gm2, 4);
        return;
    }
    SP_cUIBanningContent_EndBanMode(1);
    int* gm3 = (int*)SP_GameInputManager();
    ((FV_i)(*(void***)gm3)[0x38 / 4])(gm3, 0);
}

// ================================================================ 0x00ed9bd0
void FUN_00ed9bd0(void)
{
    int* gm = (int*)SP_GameInputManager();
    int st = (int)((FV_p)(*(void***)gm)[0x34 / 4])(gm);
    if (st != 5) {
        FUN_00e099d0(0);
        int* gm2 = (int*)SP_GameInputManager();
        ((FV_i)(*(void***)gm2)[0x38 / 4])(gm2, 5);
        return;
    }
    FUN_00e09a50(0);
    int* gm3 = (int*)SP_GameInputManager();
    ((FV_i)(*(void***)gm3)[0x38 / 4])(gm3, 0);
}

// ================================================================ 0x00ed9c20
struct Obj9c20 { char pad0[0x14]; unsigned m14; int m18; char m20; void f(); };
void Obj9c20::f()
{
    char* s = (char*)this;
    if (*(s + 0x20) != 0 && *(unsigned*)(s + 0x14) > 0) {
        unsigned e = *(unsigned*)(s + 0x14) - 1;
        *(unsigned*)(s + 0x14) = e;
        *(s + 0x20) = 0;
        int* p = *(int**)(*(int*)s + e * 4);
        ((FV_v)(*(void***)p)[0x10 / 4])(p);
        *(int*)(s + 0x18) += 1;
        *(s + 0x20) = 1;
    }
}

// ================================================================ 0x00ed9c60
struct Obj9c60 { int* m0; int* m4; char pad0[0xc]; unsigned m14; int m18; int m1c; char m20; void f(); };
void Obj9c60::f()
{
    if (m20 != 0 && m14 < (unsigned)((int*)m4 - (int*)m0)) {
        unsigned i = m14;
        m14 = i + 1;
        m20 = 0;
        int* p = *(int**)((char*)m0 + i * 4);
        ((FV_v)(*(void***)p)[0x14 / 4])(p);
        m18 += 1;
        m20 = 1;
    }
}

// ================================================================ 0x00ed9ca0
struct Obj9ca0 { char pad0[0x54]; int m54; int m58; int m5c; int m60; int m64; void f(); };
void Obj9ca0::f()
{
    int h = m54;
    if (h != 0) {
        m54 = 0;
        FUN_00571db0(h, m58, m5c, m60, m64);
    }
    *(char*)((char*)this + 0x50) = 0;
}

// ================================================================ 0x00ed9cd0 (approximate)
int __cdecl FUN_00ed9cd0(int a)
{
    (void)a;
    return 1;
}

// ================================================================ 0x00ed9e60 (approximate)
bool __cdecl FUN_00ed9e60(char a)
{
    (void)a;
    return false;
}
