// slice s00efc270 -- scenario tutorial / checklist support helpers: global checklist pointer,
// type predicates, planet-position helpers, sound/hint triggers.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE  (SSE scalar float math, x87 for float returns).
#include "types.h"

extern void** g_016c7b88;              // 0x016c7b88
extern void*  gSimulator;              // 0x016c7aa4
extern void*  g_15fd918;               // 0x015fd918
extern uint8_t g_16c7b50, g_16c7b51;   // 0x016c7b50 / 0x016c7b51
extern uint8_t g_15ad344;              // 0x015ad344
extern uint8_t g_16c7d18;              // 0x016c7d18
extern float  g_16c7b98, g_16c7b9c, g_16c7ba0;  // Vector3 globals
extern float  g_15ad338, g_15ad33c, g_15ad340, g_15ad29c;
extern float  g_1485720, g_1471064, g_13ec4d0, g_1477fc0, g_1441a88;

extern "C" void* memcpy(void*, const void*, unsigned);

int   __cdecl SP_App();
void* __cdecl FUN_00d20430(int);
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);
void* __cdecl SP_GameInputManager();
void* __cdecl SP_MessageServer();
void* __cdecl SP_ConfigManager();
void* __cdecl FUN_00b18e00(void*);
void* __cdecl FUN_00b3d280();
void* __cdecl FUN_00eebf80(void*);
void __cdecl FUN_00f35f70(void*);
void* __cdecl FUN_00f40ea0(void*, int);
void* __cdecl FUN_00f326d0(void*, int);
void* __cdecl FUN_00f46410(void*, void*, void*);
void* __cdecl FUN_00f38330(void*, int);
void* __cdecl FUN_00f34560(void*);
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);

typedef int   (__thiscall *FN0_i)(void*);
typedef float (__thiscall *FN0_f)(void*);
typedef void  (__thiscall *FN2_ii)(void*, int, int);

// 0x00efc520
int __cdecl FUN_00efc520()
{
    if (g_016c7b88 != 0)
        return *(int*)g_016c7b88;
    return 0;
}

// 0x00efc530
bool __cdecl FUN_00efc530(int* p)
{
    if (p != 0) {
        int t = ((FN0_i)((*(void***)p)[0xe]))(p);
        if (t == 0x7a309fb || t == 0x76c67df || t == 0x771ad6a || t == 0x7a81824 || t == 0x7abdd8d)
            return true;
    }
    return false;
}

// 0x00efc6c0
void __fastcall FUN_00efc6c0(char* p, int v)
{
    int* q = *(int**)(p + 0xc);
    if (q != 0 && *q == v)
        *q = -1;
}

// 0x00efc850
void __cdecl FUN_00efc850()
{
    char* sim = (char*)gSimulator;
    char* o = *(char**)(sim + 0x18);
    FUN_00f35f70(o);
}
// 0x00efc860
void __cdecl FUN_00efc860()
{
    if (*(int*)((char*)g_016c7b88 + 0xc) != 0) {
        void* im = SP_GameInputManager();
        ((FN2_ii)((*(void***)im)[0x19]))(im, 0x96b6b02c, 1);
    }
}

// 0x00efc890
void __cdecl FUN_00efc890()
{
    char* g = (char*)g_016c7b88;
    int o = *(int*)(g + 0xc);
    if (o != 0) {
        char* r = (char*)FUN_00b18e00((void*)o);
        *(uint8_t*)(r + 0x6e) = 1;
        void* im = SP_GameInputManager();
        ((FN2_ii)((*(void***)im)[0x19]))(im, 0x96b6b02c, 1);
    }
}

// 0x00efc8c0
void __cdecl FUN_00efc8c0(int v)
{
    int* g = (int*)g_016c7b88;
    int old = *g;
    *g = v;
    if (old != v)
        FUN_00f46410((void*)1, (void*)old, (void*)v);
}

// 0x00efc8f0
int __cdecl FUN_00efc8f0()
{
    int r = 0;
    if (g_016c7b88 != 0 && *(int*)((char*)g_016c7b88 + 8) != 0)
        r = (int)FUN_00eebf80(*(void**)((char*)g_016c7b88 + 8));
    return r;
}

// 0x00efc910
int __cdecl FUN_00efc910()
{
    int r = 0;
    if (g_016c7b88 != 0)
        r = (int)FUN_00eebf80(*(void**)((char*)g_016c7b88 + 4));
    return r;
}

// 0x00efc7a0
bool __fastcall FUN_00efc7a0(char* p)
{
    if (*(char*)(p + 5) != 0) {
        FUN_00f38330(*(void**)(p + 8), 1);
        FUN_00f34560(*(void**)(p + 8));
        *(char*)(p + 5) = 0;
    }
    return true;
}

// 0x00efc660
bool __fastcall FUN_00efc660(char* p, int pad, int a)
{
    if (a == 0)
        return false;
    char* o = (char*)FUN_00b18e00((void*)a);
    if (o == 0 || *(char*)(o + 0x6e) != 0)
        return false;
    char r = (char)FUN_00f40ea0(*(void**)(p + 8), a);
    if (r == 0) {
        void* ms = SP_MessageServer();
        ((FN2_ii)((*(void***)ms)[5]))(ms, 0x78c406b, 0);
    }
    return r != 0;
}

// 0x00efc7d0
bool __fastcall FUN_00efc7d0(char* p, int pad, int a, int b)
{
    char* o = (char*)FUN_00b18e00((void*)a);
    if (o != 0 && *(char*)(o + 0x6e) != 0)
        return false;
    char r = (char)FUN_00f326d0(*(void**)(p + 8), b);
    if (r == 0) {
        void* ms = SP_MessageServer();
        ((FN2_ii)((*(void***)ms)[5]))(ms, 0x78c406b, 0);
    }
    return r != 0;
}

// 0x00efcd90
int __cdecl FUN_00efcd90()
{
    int app = SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))((void*)app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b != 0) {
        int o = ((FN0_i)((*(void***)b)[3]))(b);
        if (o != 0 && (*(char*)(o + 0x319) == 0 || *(char*)(o + 0x11) != 0))
            return 1;
    }
    return 0;
}

// 0x00efcae0
void __cdecl FUN_00efcae0()
{
    int app = SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))((void*)app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b != 0) {
        int o = ((FN0_i)((*(void***)b)[3]))(b);
        if (o != 0) {
            *(uint8_t*)(o + 0x315) = 0;
            FUN_00d20430(0);
            return;
        }
    }
    void* m = FUN_00b3d280();
    if (m != 0) {
        FUN_00b0f950(m, 0);
        FUN_00b10c40(m, 0);
    }
}

// 0x00efcde0
void __fastcall FUN_00efcde0(void* p)
{
    int r;
    if (p == 0)
        r = 0;
    else
        r = ((FN0_i)((*(void***)p)[3]))(p);
    if (*(int*)(r + 0x54) != 0) {
        void* q = *(void**)(r + 0x54);
        if (q != 0) {
            int s = ((FN0_i)((*(void***)q)[3]))(q);
            ((FN2_ii)((*(void***)s)[0x15]))((void*)s, 0, 0);
            return;
        }
        FUN_00d20430(0);
    }
}

// 0x00efce30
void __fastcall FUN_00efce30(void* p)
{
    int r;
    if (p == 0)
        r = 0;
    else
        r = ((FN0_i)((*(void***)p)[3]))(p);
    if (*(int*)(r + 0x54) != 0) {
        void* q = *(void**)(r + 0x54);
        int s;
        if (q == 0)
            s = 0;
        else
            s = ((FN0_i)((*(void***)q)[3]))(q);
        ((FN2_ii)((*(void***)s)[0x15]))((void*)s, 1, 0);
        void* t = (void*)FUN_00b18e00(*(void**)(r + 0x54));
        ((FN0_i)((*(void***)t)[0xe]))(t);
        t = (void*)FUN_00b18e00(*(void**)(r + 0x54));
        ((FN0_i)((*(void***)t)[0xf]))(t);
        t = (void*)FUN_00b18e00(*(void**)(r + 0x54));
        ((FN0_i)((*(void***)t)[0x10]))(t);
    }
}

// ---------------------------------------------------------------------------
// externs
// ---------------------------------------------------------------------------
int   __cdecl SP_App();
void* __cdecl FUN_00d20430(int);
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);
void* __cdecl FUN_00d20430(int);
void* __cdecl SP_GameInputManager();
void* __cdecl SP_MessageServer();
void* __cdecl SP_ConfigManager();
void* __cdecl FUN_00b18e00(void*);
void* __cdecl FUN_00b3d280();
void* __cdecl FUN_00eebf80(void*);
void __cdecl FUN_00f35f70(void*);
void* __cdecl FUN_00f40ea0(void*, int);
void* __cdecl FUN_00f326d0(void*, int);
void* __cdecl FUN_00f46410(void*, void*, void*);
void* __cdecl FUN_00f38330(void*, int);
void* __cdecl FUN_00f34560(void*);
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);

// ---------------------------------------------------------------------------
// remaining functions (bodies approximated; see nonmatching.txt / partial.txt)
// ===========================================================================
void* __cdecl FUN_00f35f70_2(void*);
void* __cdecl FUN_00b3d250();
void* __cdecl FUN_00eeca30(void*);
void* __cdecl FUN_00b82620(void*, void*, void*, int);
void* __cdecl FUN_00f46410_2(int, int, int);

// @ 0x00efc270
int __stdcall FUN_00efc270(int a, int b)
{
    (void)a; (void)b;
    return 0;
}

// @ 0x00efc4c0
float __fastcall FUN_00efc4c0(char* p)
{
    float a = *(float*)(p + 0x178);
    float b = *(float*)(p + 0x174);
    if (a > b)
        return (*(float*)(p + 0x17c) - b) / (a - b);
    return 1.0f;
}

// @ 0x00efc570
bool __fastcall FUN_00efc570(char* p, int param, float f)
{
    (void)p; (void)param; (void)f;
    return true;
}

// @ 0x00efc5f0
int __fastcall FUN_00efc5f0(char* p, int param, float f)
{
    (void)p; (void)param; (void)f;
    return 0;
}

// @ 0x00efc6e0
void __stdcall FUN_00efc6e0(int* p)
{
    (void)p;
}

// @ 0x00efc930
int __cdecl FUN_00efc930()
{
    return 0;
}

// @ 0x00efc9c0
int __cdecl FUN_00efc9c0()
{
    return 0;
}

// @ 0x00efc9e0
int __cdecl FUN_00efc9e0()
{
    return 0;
}

// @ 0x00efca60
int __cdecl FUN_00efca60(int* p)
{
    (void)p;
    return 0;
}

// @ 0x00efcb40
float __fastcall FUN_00efcb40(char* p)
{
    (void)p;
    return 1.0f;
}

// @ 0x00efcbe0
void __cdecl FUN_00efcbe0(int a)
{
    (void)a;
}

// @ 0x00efccd0
void __fastcall FUN_00efccd0(char* p)
{
    (void)p;
}

// @ 0x00efcec0
void __stdcall FUN_00efcec0(int a)
{
    (void)a;
}

// @ 0x00efcfb0
int __cdecl FUN_00efcfb0(char* p)
{
    (void)p;
    return 0;
}
