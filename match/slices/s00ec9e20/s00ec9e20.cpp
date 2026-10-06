// Slice s00ec9e20 -- Text/UI analysis + palette window glue.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

extern char* g_16c757c;   // 0x016c757c
extern char* g_16c7584;   // 0x016c7584

// ---------------------------------------------------------------- callees
void* __cdecl FUN_00ec9a80(int, int);   // 0xec9a80
void  __cdecl FUN_00ec7b90(int, void*); // 0xec7b90
void  __cdecl FUN_00ec98d0(void);       // 0xec98d0
int   __cdecl ScenarioTutorials_GetActive(void); // 0xefc520

struct Layout { void* Find(int, int); };

// ---------------------------------------------------------------- 0x00ec9e20 (partial)
void __cdecl FUN_00ec9e20(void* a, void* b) { (void)a; (void)b; }

// ---------------------------------------------------------------- 0x00eca010 (partial)
void __cdecl FUN_00eca010(int a) { (void)a; }

// ---------------------------------------------------------------- 0x00eca0f0 (partial)
int __cdecl FUN_00eca0f0(int a) { (void)a; return 1; }

// ---------------------------------------------------------------- 0x00eca1d0 (partial)
void __cdecl FUN_00eca1d0(void) {}

// ---------------------------------------------------------------- 0x00eca2f0
void __cdecl FUN_00eca2f0(void)
{
    void* layout = *(void**)g_16c7584;
    void* w = ((Layout*)layout)->Find((int)0x8de6958, 1);
    if (((int(__thiscall*)(void*))(*(void***)w)[0x28 / 4])(w) & 1) {
        void* w2 = ((Layout*)layout)->Find((int)0x8de6960, 1);
        ((void(__thiscall*)(void*, int, int))(*(void***)w2)[0x7c / 4])(w2, 0x400, 1);
        for (int i = 0; i < 0x140; i += 0x20) {
            void* o = *(void**)((char*)g_16c7584 + i + 8);
            ((void(__thiscall*)(void*, int, int))(*(void***)o)[0x7c / 4])(o, 1, 0);
            *(char*)((char*)g_16c7584 + i + 4) = 0;
        }
        *g_16c757c = 0;
        ScenarioTutorials_GetActive();
        FUN_00ec98d0();
        void* w3 = ((Layout*)layout)->Find((int)0x8de6958, 1);
        ((void(__thiscall*)(void*, int, int))(*(void***)w3)[0x7c / 4])(w3, 1, 0);
    }
}

// ---------------------------------------------------------------- 0x00eca3b0 (partial)
void __cdecl FUN_00eca3b0(int a) { (void)a; }

// ---------------------------------------------------------------- 0x00eca460
void __cdecl FUN_00eca460(int a, int b, int c)
{
    int* pi = (int*)FUN_00ec9a80(a, b);
    int edx = pi[1] - pi[0];
    int i = 0;
    if ((edx & ~7) > 0) {
        do {
            FUN_00ec7b90(c, (void*)(pi[0] + i * 8));
            edx = pi[1] - pi[0];
            ++i;
        } while (i < (edx >> 3));
    }
}

// ---------------------------------------------------------------- 0x00eca4b0 (partial)
int* __cdecl FUN_00eca4b0(int* a, int b, int* c) { (void)a; (void)b; (void)c; return 0; }

// ---------------------------------------------------------------- 0x00eca670 (partial)
void __cdecl FUN_00eca670(int* a, int b) { (void)a; (void)b; }

// ---------------------------------------------------------------- 0x00eca920 (partial)
void __cdecl FUN_00eca920(void) {}

// ---------------------------------------------------------------- 0x00eca9c0 (partial)
void __cdecl FUN_00eca9c0(void) {}

// ---------------------------------------------------------------- 0x00ecaab0 (partial)
void __cdecl FUN_00ecaab0(void) {}

// ---------------------------------------------------------------- 0x00ecabc0 (partial)
void __cdecl FUN_00ecabc0(void) {}
