// Slice s00f3c060 -- Simulator content-validation / scenario region (bfs2 slice 14).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- globals / helpers
extern unsigned char g_16065f8;                  // 0x016065F8
extern void*         g_16065fc;                  // 0x016065FC
extern void*         g_16c7aa4;                  // 0x016C7AA4
extern int           g_15b0530;                  // 0x015B0530
void* __cdecl FUN_00ddddf0(int, int);            // 0x00DDDDF0
void* __cdecl FUN_00efc520();                    // 0x00EFC520 (ScenarioTutorials_GetActive)

struct X {
    virtual void s0();
    virtual void Release();
    virtual void* s2();
    virtual void* s3(int);
};
struct Y {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4();
};

// @ 0x00F3C060
void InitThing()
{
    if (g_16065f8 == 0) {
        if (g_16065fc) {
            Y* r = (Y*)((X*)g_16065fc)->s3(0x743bb11);
            if (r) {
                r->s4();
                if (g_16065fc) {
                    void* p = g_16065fc;
                    g_16065fc = 0;
                    ((X*)p)->Release();
                }
            }
        }
        g_16065f8 = 1;
    }
}

// @ 0x00F3C0B0
void KillThing()
{
    if (g_16065f8 == 0) {
        if (g_16065fc) {
            void* p = g_16065fc;
            g_16065fc = 0;
            ((X*)p)->Release();
        }
        g_16065f8 = 1;
    }
}

// @ 0x00F3C0E0
int GetThing()
{
    if (*(int*)((char*)g_16c7aa4 + 0xcc) == 2)
        return *(int*)(*(int*)((char*)g_16c7aa4 + 0x78) + 0xb8);
    return (int)FUN_00efc520();
}

struct W {
    char* begin;                 // +0x00
    char  pad4[0x10-4];
    void* m10;                   // +0x10
    char  pad14[0x8c-0x14];
    int   m8c;                   // +0x8c
    int IndexOf(void* p);
    int GetAt(int* p);
};

// @ 0x00F3C100
int W::IndexOf(void* p) { return (int)((char*)p - begin) / 0x238; }

// @ 0x00F3CB30
int W::GetAt(int* p)
{
    if (*p == -2) return m8c;
    return *(int*)((char*)m10 + 0x2c10) + p[0x8a] * 0x238 + 4;
}

// @ 0x00F3C1B0
struct Z { void fn(int, int); };
extern Z g_15b0534;                              // 0x015B0534
void CallD() { g_15b0534.fn(0x55c0377, g_15b0530); }

// ---------------------------------------------------------------- not yet matching
void FUN_00f3c120(void* self, void* out) { (void)self; (void)out; }   // @ 0x00F3C120
void FUN_00f3c160(void* self, int v) { (void)self; (void)v; }         // @ 0x00F3C160
void FUN_00f3c1d0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }  // @ 0x00F3C1D0
void FUN_00f3c2c0(void* self) { (void)self; }                         // @ 0x00F3C2C0
void FUN_00f3c330(void* self) { (void)self; }                         // @ 0x00F3C330
void FUN_00f3c420(void* self) { (void)self; }                         // @ 0x00F3C420
void FUN_00f3c500(void* self) { (void)self; }                         // @ 0x00F3C500
void FUN_00f3c610(void* self) { (void)self; }                         // @ 0x00F3C610
void FUN_00f3c750(void* self) { (void)self; }                         // @ 0x00F3C750
unsigned FUN_00f3c7f0(void* self, int v) { (void)self; (void)v; return 0; }  // @ 0x00F3C7F0
void FUN_00f3c870(void* self) { (void)self; }                         // @ 0x00F3C870
void FUN_00f3cb60(void* self) { (void)self; }                         // @ 0x00F3CB60
void FUN_00f3cc40(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }  // @ 0x00F3CC40
void FUN_00f3cd10(void* self) { (void)self; }                         // @ 0x00F3CD10
void FUN_00f3cd60(void* self, void* s) { (void)self; (void)s; }       // @ 0x00F3CD60
void FUN_00f3cdf0(void* self, void* s) { (void)self; (void)s; }       // @ 0x00F3CDF0
void FUN_00f3ce80(void* self, void* s) { (void)self; (void)s; }       // @ 0x00F3CE80
