// slice s00efb4e0 -- UI::cScenarioTutorialsChecklistUI (continued): category setup / teardown,
// tutorial checklist window updates, hint/perk selection handlers.
//
// Module flags: /O2 /MD /Gy /TP  (no /EHsc; x87 for float args; memories are embedded hash
// tables / window pointers).
#include "types.h"

struct Vector3 { float x, y, z; };

extern int   g_16c7aa4;                 // 0x016c7aa4  (Simulator*)
extern float gVecBase[];                // 0x015ad198  (Vector3 table used by FUN_00ef8390)
extern char  g_16c7b60[];               // 0x016c7b60

struct Simulator;
extern Simulator* gSimulator;

// ---------------------------------------------------------------------------
// helper shapes
// ---------------------------------------------------------------------------
typedef void  (__thiscall *FN1_i)(void*, int);
typedef int   (__thiscall *FN1_ir)(void*, int);
typedef void  (__thiscall *FN2_ii)(void*, int, int);
typedef void* (__thiscall *FN0_p)(void*);
typedef void* (__thiscall *FN2_pii)(void*, int, int);
typedef int   (__thiscall *FN0_i)(void*);

// external helpers (defined elsewhere in the module)
void  __cdecl cUIHints_Update();
void  __cdecl SetBoolProperty(void*);
void  __cdecl SetTimeLimit(void*, int, int);
bool  __cdecl LimitStopwatch_IsTimeUp(void*);

struct CUI {
    void  f_efb4e0();
    void  f_efb9c0(int, int);
    void  f_efbbe0(int, int);
    void  f_efbc90(int, int);
    void  f_efbce0();
    void  f_efbdf0();
    void  f_efbe40(int, int);
    void  f_efbf00();
    bool  f_efc120(int, int);
    // helpers defined elsewhere in this TU
    bool  f_ef8820(int);
    void  f_ef8390(Vector3, int, int, int);
    void  f_efa0b0(int, int);
    void  f_efa110(int, int);
    void  f_ef9d00();
    void  f_ef9000();
    void  f_ef9af0(int);
    void  f_ef7a80();
    void  f_ef7a00();
    void  f_ef7b00();
    void  f_ef7b40();
    bool  f_ef76f0();
    unsigned int f_ef7330(int);
    int   f_ef72d0(int);
    void  f_ef8a10(int);
    void  f_ef7ec0(int);
    void  f_efa1b0();
    void  f_efa040();
    void  f_ef8ed0(int);
    void  f_ef8860();
};

void  __cdecl FUN_00a23ef0(void*, void*);
void  __cdecl FUN_00a23d20(void*);
void  __cdecl FUN_00804ed0(void*, void*);
void  __cdecl FUN_00efcae0();
void  __cdecl FUN_0067cac0();
void  __cdecl FUN_0067c830(int);
void  __cdecl FUN_00804ed0_2();
void* __cdecl FUN_00985e40();
void* __cdecl FUN_00ed4b50(int);
void  __cdecl SP_KillSetiEffects(int, int);
void* __cdecl EA_GetSystemAT();
void* __cdecl SP_ConfigManager();

struct CSpace { void* f_00985e40(); void* f_00ed4b50(int); };
struct CMap { void f_00a23ef0(void*, void*); void f_00a23d20(void*); };
struct CWindow { void* v(int); };
struct CLimit { void SetTimeLimit(int, int); };

// ===========================================================================
// @ 0x00efb4e0
// ===========================================================================
void CUI::f_efb4e0()
{
    char* self = (char*)this;
    // Table of (window id, action) processed in order until a window is missing.
    // action 0: create from Vector3, action 1: remove, action 2: seti effect.
    struct Entry { int id; int action; int a; int b; int vec; };
    static const Entry kEntries[] = {
        { 0xa4, 0, 0, 0, 0x204 }, { 0xa6, 1, 0xa5, 0, 0 }, { 0xa7, 0, 0, 0, 0x210 },
        { 0xa9, 1, 0xa8, 0, 0 }, { 0xab, 2, 0xaa, 0x218e06f7, 0 },
        { 0xac, 2, 0xac, 0x55f3a99b, 0 },
        { 0x87, 0, 0, 0, 0x198 }, { 0x88, 0, 0, 0, 0x1a4 }, { 0x8a, 1, 0x89, 0, 0 },
        { 0x8b, 0, 0, 0, 0x1b0 }, { 0x8d, 2, 0x8c, 0x4f8dbb28, 0 }, { 0x8e, 0, 0, 0, 0x1bc },
        { 0x90, 1, 0x8f, 0, 0 }, { 0x91, 0, 0, 0, 0x1c8 }, { 0x93, 2, 0x92, 0x624e5aa, 0 },
        { 0x95, 2, 0x94, 0x5f3e51b0, 0 }, { 0x97, 2, 0x96, 0xcacb7102, 0 }, { 0x98, 0, 0, 0, 0x1d4 },
        { 0x99, 2, 0x99, 0x50a2f4e4, 0 }, { 0x9e, 0, 0, 0, 0x1e0 }, { 0xa0, 1, 0x9f, 0, 0 },
        { 0xa2, 2, 0xa1, 0xccbe21d, 0 }, { 0xa3, 0, 0, 0, 0x1ec }, { 0x9a, 0, 0, 0, 0x1f8 },
        { 0x9c, 1, 0x9b, 0, 0 }, { 0x9d, 2, 0x9d, 0x56221c05, 0 },
    };
    for (int i = 0; i < (int)(sizeof(kEntries) / sizeof(kEntries[0])); i++) {
        if (f_ef8820(kEntries[i].id))
            continue;
        if (kEntries[i].action == 0)
            f_ef8390(*(Vector3*)((char*)gVecBase + kEntries[i].vec * 4), kEntries[i].id, 0, 0);
        else if (kEntries[i].action == 1)
            f_efa0b0(kEntries[i].a, 0);
        else
            f_efa110(kEntries[i].a, kEntries[i].b);
        return;
    }
    (void)self;
}

// ===========================================================================
// @ 0x00efb9c0
// ===========================================================================
void CUI::f_efb9c0(int param_2, int param_3)
{
    char* self = (char*)this;
    void* old = *(void**)(self + 0xc);
    if ((void*)param_2 != old) {
        if (param_2 != 0)
            ((FN0_p)((*(void***)param_2)[0]))((void*)param_2);
        *(int*)(self + 0xc) = param_2;
        if (old != 0)
            ((FN0_p)((*(void***)old)[1]))(old);
    }
    bool bVar8 = true;
    *(int*)(self + 0x28) = param_3;
    if (param_3 == 0) {
        *(int*)(self + 0x2c) = 0;
        *(int*)(self + 0x30) = 0xc;
        void* cm = SP_ConfigManager();
        if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) == 0)
            bVar8 = false;
    } else if (param_3 == 1) {
        *(int*)(self + 0x2c) = 2;
        *(int*)(self + 0x30) = 5;
        bVar8 = false;
    }
    f_ef9d00();
    f_ef7a80();
    if (bVar8) {
        void* cm = SP_ConfigManager();
        if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) == 0)
            goto afterWindow;
    } else {
        f_ef7b40();
    }
    if (*(void**)(self + 0x14) != 0)
        ((FN2_ii)((*(void***)*(void**)(self + 0x14))[0x1f]))(*(void**)(self + 0x14), 1, bVar8 ? 1 : 0);
afterWindow:
    if (*(int*)(self + 0x30) > 0) {
        void* w = ((FN2_pii)((*(void***)*(void**)(self + 0x14))[0x3c]))(*(void**)(self + 0x14), 100, 1);
        (void)w;
    }
    (void)self;
}

// ===========================================================================
// @ 0x00efbbe0
// ===========================================================================
void CUI::f_efbbe0(int param_2, int param_3)
{
    char* self = (char*)this;
    int local[2];
    int a2 = param_2;
    ((CMap*)(self + 0x5c))->f_00a23ef0(local, &a2);
    if (local[0] != *(int*)(*(int*)(self + 0x60) + *(int*)(self + 100) * 4)) {
        int a3 = param_3;
        ((CMap*)(self + 0x5c))->f_00a23ef0(local, &a3);
        if (local[0] == *(int*)(*(int*)(self + 0x60) + *(int*)(self + 100) * 4)) {
            f_ef8a10(param_3);
            f_ef7ec0(param_3);
            unsigned int st = f_ef7330(param_3);
            if (st > 0) {
                ((CLimit*)(self + 0x10))->SetTimeLimit(st, 1);
                *(uint8_t*)(self + 0x3b) = 1;
            }
            f_ef9af0(param_3);
            if (f_ef72d0(param_3)) {
                if (*(int*)(self + 0x30) != -1)
                    f_efbce0();
            }
        }
    }
}

// ===========================================================================
// @ 0x00efbc90
// ===========================================================================
void CUI::f_efbc90(int param_2, int param_3)
{
    char* self = (char*)this;
    int local[2];
    int key = param_2;
    ((CMap*)(self + 0x5c))->f_00a23ef0(local, &key);
    if (local[0] == *(int*)(*(int*)(self + 0x60) + *(int*)(self + 100) * 4))
        f_efa0b0(key, param_3);
}

// ===========================================================================
// @ 0x00efbce0
// ===========================================================================
void CUI::f_efbce0()
{
    char* self = (char*)this;
    bool b = false;
    void* cm = SP_ConfigManager();
    if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) != 0 &&
        *(int*)(self + 0x30) != -1 && *(int*)(self + 0x34) != -1) {
        if (!f_ef76f0()) {
            *(uint8_t*)(self + 0x3e) = 1;
            return;
        }
        *(uint16_t*)(self + 0x38) = 0;
        *(uint8_t*)(self + 0x3a) = 0;
        if (*(char*)(self + 0x3b) != 0) {
            FUN_00efcae0();
            float a, c2;
            FUN_00804ed0(&a, &c2);
            char* sim = (char*)gSimulator;
            ((void (__thiscall*)(void*, int, int, float, float))(*(void***)sim)[0xc])(sim, 1000, 8, a, a); (void)c2;
            ((void (__thiscall*)(void*, int, int, float, float))(*(void***)sim)[0xc])(sim, 0x3ea, 0x20, a, a);
            ((void (__thiscall*)(void*, int, int, float, float))(*(void***)sim)[0xc])(sim, 0x3e9, 0x10, a, a);
            ((FN2_ii)((*(void***)sim)[10]))(sim, 0x10, 0);
            *(uint8_t*)(self + 0x3b) = 0;
        }
        int m = *(int*)(self + 0x34);
        if (m == 0) {
            f_efa1b0();
        } else if (m == 1) {
            f_efb4e0();
        }
    }
    (void)b;
}

// ===========================================================================
// @ 0x00efbdf0
// ===========================================================================
void CUI::f_efbdf0()
{
    char* self = (char*)this;
    Simulator* sim = gSimulator;
    if (sim == 0)
        return;
    char* d4 = *(char**)((char*)sim + 0xd4);
    if (d4 == 0)
        return;
    CSpace* sp = *(CSpace**)((char*)sim + 0x14);
    void* r = sp->f_00ed4b50(*(int*)(d4 + 0x34));
    ((CUI*)r)->f_ef7b00();
    int x = *(int*)(self + 4);
    if (x == 0)
        return;
    ((CUI*)*(void**)((char*)sim + 0xd4))->f_efbc90(x, 1);
}

// ===========================================================================
// @ 0x00efbe40
// ===========================================================================
void CUI::f_efbe40(int param_2, int param_3)
{
    char* self = (char*)this;
    void* cm = SP_ConfigManager();
    if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) == 0)
        return;
    f_ef8860();
    (void)param_3;
    int* table;
    if (param_3 == 0)
        table = (int*)((char*)0x0148b450 + param_2 * 0x10);
    else if (param_3 == 1)
        table = (int*)((char*)0x0148b510 + param_2 * 0x10);
    else
        table = 0;
    if (table != 0) {
        int lo = table[0];
        int hi = table[1];
        for (int i = lo; i <= hi; i++) {
            int v = i;
            ((CMap*)(self + 0x5c))->f_00a23d20(&v);
        }
    }
    *(int*)(self + 0x34) = param_3;
    *(int*)(self + 0x30) = param_2;
    SetBoolProperty(self + 0x10);
    char* sim = (char*)gSimulator;
    CSpace* sp = *(CSpace**)(sim + 0x14);
    void* r = sp->f_00ed4b50(0);
    (void)r;
}

// ===========================================================================
// @ 0x00efbf00
// ===========================================================================
void CUI::f_efbf00()
{
    char* self = (char*)this;
    FUN_0067cac0();
    cUIHints_Update();
    void* cm = SP_ConfigManager();
    if (((FN1_ir)((*(void***)cm)[0xc]))(cm, 0x4ea96cb) != 0) {
        if (*(int*)(self + 0x10) != 0 || *(int*)(self + 0x14) != 0) {
            if (LimitStopwatch_IsTimeUp(self + 0x10)) {
                SetBoolProperty(self + 0x10);
                f_efbce0();
            }
        }
        if (*(char*)(self + 0x3e) != 0) {
            *(uint8_t*)(self + 0x3e) = 0;
            f_efbce0();
        }
    }
}

// ===========================================================================
// @ 0x00efc120
// ===========================================================================
bool CUI::f_efc120(int param_2, int param_3)
{
    char* self = (char*)this;
    char* sim = (char*)gSimulator;
    CSpace* sp = *(CSpace**)(sim + 0x14);
    int r = (int)sp->f_00985e40();
    if (r != *(int*)(self + 0x2c))
        return false;
    if (*(int*)(param_3 + 8) != 0x287259f6)
        return false;
    int id = *(int*)(param_3 + 0xc);
    if (id == 0x7732678) {
        if (*(char*)(self + 0x25) != 0) {
            f_ef7a80();
            void* at = EA_GetSystemAT();
            int v = 0;
            if (at != 0)
                v = ((FN0_i)((*(void***)at)[8]))(at);
            SP_KillSetiEffects(0xcc089e57, v);
        } else {
            f_ef7a00();
            void* at = EA_GetSystemAT();
            int v = 0;
            if (at != 0)
                v = ((FN0_i)((*(void***)at)[8]))(at);
            SP_KillSetiEffects(0x6e649e21, v);
        }
        return false;
    }
    if (id == 0x7a27050) {
        void* cm = SP_ConfigManager();
        ((FN2_ii)((*(void***)cm)[0xb]))(cm, 0x4ea96cb, 0);
        char* d4 = *(char**)(sim + 0xd4);
        ((CUI*)d4)->f_ef8ed0(0);
        FUN_0067cac0();
        FUN_0067c830(0xe56e9897);
        return false;
    }
    if (id == 0x7a291ce) {
        char* d4 = *(char**)(sim + 0xd4);
        ((CUI*)d4)->f_efa040();
        return false;
    }
    {
        int a = id - 1;
        int b = *(int*)(self + 0x28);
        char* d4 = *(char**)(sim + 0xd4);
        ((CUI*)d4)->f_efbe40(a, b);
    }
    return false;
}
