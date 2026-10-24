// Slice s00ec9e20 -- Text/UI analysis + palette window glue.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

extern char* g_16c757c;   // 0x016c757c
extern char* g_16c7584;   // 0x016c7584
extern char* g_16c7aa4;   // 0x016c7aa4

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)

// ---------------------------------------------------------------- callees
void* __cdecl FUN_00ec9a80(int, int);   // 0xec9a80
void  __cdecl FUN_00ec7b90(int, void*); // 0xec7b90
void  __cdecl FUN_00ec98d0(void);       // 0xec98d0
int   __cdecl ScenarioTutorials_GetActive(void); // 0xefc520

void* __cdecl FUN_00ec6d00(void);                    // 0x00ec6d00
void* __cdecl FUN_00ec79f0(int, int);                // 0x00ec79f0
int   __cdecl FUN_00ec6ab0(int);                     // 0x00ec6ab0
void  __cdecl FUN_00ec6ee0(void*, void*, int);       // 0x00ec6ee0
void  __cdecl FUN_00ec7770(int, int, int, int, int); // 0x00ec7770
int   __cdecl FUN_00ec6940(const void*, float);      // 0x00ec6940
char  __cdecl FUN_00ec68f0(void*, void*);            // 0x00ec68f0
void  __cdecl FUN_00ec8f40(int);                     // 0x00ec8f40
void  __cdecl FUN_00ec7950(int);                     // 0x00ec7950
void  __cdecl FUN_00ec9690(int, int);                // 0x00ec9690
void  __cdecl FUN_00ec96f0(int, int);                // 0x00ec96f0
void* __cdecl FUN_00806880(void*, int, int);         // 0x00806880
char  __cdecl FUN_00806aa0(void*, void*);            // 0x00806aa0

// ---------------------------------------------------------------- helper objects
// 0x20-byte analysis payload FUN_00ec9b30 builds from a region's 5 args (b[]).
struct Elem { int v[8]; };
Elem __cdecl FUN_00ec9b30(const int* args);             // 0x00ec9b30

struct VecHdr { int* begin; int* end; };

struct Lookup {
    VecHdr* FUN_00ec9530(const void* key);   // 0x00ec9530
    VecHdr* FUN_00ec9820(const void* key);   // 0x00ec9820
};

struct cSPUILayout {
    void* FindWindowByID(unsigned int id, int deep);   // 0x008105b0
};

struct AnalysisInfoVec {
    int* begin;   // +0x00
    int* end;     // +0x04
    int* cap;     // +0x08
    int* erase(int* first, int* last);       // 0x00899420
    void FUN_00ec8ed0(int count);            // 0x00ec8ed0
};

struct TutorCtx {
    void FUN_00f45970();                     // 0x00f45970
    void FUN_00f45a80();                     // 0x00f45a80
};

// *g_16c7584 + 4 + 0x20*k : a window-region slot.
struct Region {
    char  enabled;    // +0x00
    char  _pad0[3];
    void* window;     // +0x04
    int   index;      // +0x08
    int   args[5];    // +0x0c
};

struct Layout { void* Find(int, int); };

typedef int (__thiscall *TF0)(void*);
typedef int (__thiscall *TF1)(void*, int);
typedef int (__thiscall *TFu)(void*, unsigned);
typedef int (__thiscall *TFii)(void*, int, int);
typedef int (__thiscall *TFui)(void*, unsigned, int);
typedef int (__thiscall *TFp)(void*, void*);
typedef int (__thiscall *TFff)(void*, float, float);

// @ 0x00ec9e20
// Five-stage key lookup: vector1 -> b[0], then three maps keyed by v1[b[0]]
// (0x18/0x34/0x50/0x6c offsets of *g_16c757c) fill b[1..4].
void __cdecl FUN_00ec9e20(int* a, int* b)
{
    int* v1 = *(int**)(g_16c757c + 4);
    int  n  = (*(int*)(g_16c757c + 8) - (int)v1) >> 2;
    int  i;

    b[0] = -1; b[1] = -1; b[2] = -1; b[3] = -1; b[4] = -1;
    for (i = 0; i < n; ++i)
        if (v1[i] == a[3]) { b[0] = i; break; }
    if (b[0] == -1) b[0] = 0;

    int key = v1[b[0]];
    VecHdr* r = ((Lookup*)(g_16c757c + 0x18))->FUN_00ec9530(&key);
    if (r->begin != r->end) {
        int m = ((int)r->end - (int)r->begin) >> 3;
        for (i = 0; i < m; ++i)
            if (r->begin[i * 2] == a[4] && r->begin[i * 2 + 1] == a[5]) { b[1] = i; break; }
        if (b[1] == -1) b[1] = 0;
    }

    key = v1[b[0]];
    r = ((Lookup*)(g_16c757c + 0x34))->FUN_00ec9530(&key);
    if (r->begin != r->end) {
        int m = ((int)r->end - (int)r->begin) >> 3;
        for (i = 0; i < m; ++i)
            if (r->begin[i * 2] == a[6] && r->begin[i * 2 + 1] == a[7]) { b[2] = i; break; }
        if (b[2] == -1) b[2] = 0;
    }

    key = v1[b[0]];
    r = ((Lookup*)(g_16c757c + 0x50))->FUN_00ec9820(&key);
    {
        int m = ((int)r->end - (int)r->begin) >> 2;
        for (i = 0; i < m; ++i)
            if (r->begin[i] == a[0]) { b[3] = i; break; }
    }
    if (b[3] == -1) b[3] = 0;

    i = b[3];
    if (b[0] == -1 || i == -1) {
        key = -1;
    } else {
        key = (*(int**)(g_16c757c + 4))[b[0]];
        r = ((Lookup*)(g_16c757c + 0x50))->FUN_00ec9820(&key);
        key = r->begin[i];
    }

    r = ((Lookup*)(g_16c757c + 0x6c))->FUN_00ec9530(&key);
    if (r->begin != r->end) {
        int m = ((int)r->end - (int)r->begin) >> 3;
        for (i = 0; i < m; ++i)
            if (r->begin[i * 2] == a[1] && r->begin[i * 2 + 1] == a[2]) { b[4] = i; break; }
        if (b[4] == -1) b[4] = 0;
    }
}

// @ 0x00eca010
// Rebuild one analysis record's AnalysisInfo vector from the live regions.
void __cdecl FUN_00eca010(int param_1)
{
    int base = param_1 * 0x4e0 + *(int*)(*(int*)g_16c757c + 0x70);
    AnalysisInfoVec* vec = (AnalysisInfoVec*)(base + 0x4cc);

    *(char*)(base + 0x4c8) = 1;
    *(int*)(base + 0x4ac) = 0;
    vec->erase(vec->begin, vec->end);
    int count = *(int*)(g_16c7584 + 0x144);
    if (*(int*)(g_16c7584 + 0x14c) != 0) count -= 1;
    vec->FUN_00ec8ed0(count);

    for (int off = 0; off < 0x140; off += 0x20) {
        Region* r = (Region*)(g_16c7584 + off + 4);
        if (r->enabled != 0 && *(int*)(g_16c7584 + 0x14c) != (int)r) {
            Elem e = FUN_00ec9b30(r->args);
            *(Elem*)(vec->begin + (r->index << 3)) = e;
        }
    }
}

// @ 0x00eca0f0
// 0 == the record's AnalysisInfo vector still matches the live regions.
char __cdecl FUN_00eca0f0(int param_1)
{
    int base = param_1 * 0x4e0 + *(int*)(*(int*)g_16c757c + 0x70);

    if (*(char*)(base + 0x4c8) == 0) return 1;
    int count = *(int*)(g_16c7584 + 0x144);
    if (*(int*)(g_16c7584 + 0x14c) != 0) count -= 1;
    if (((*(int*)(base + 0x4d0) - *(int*)(base + 0x4cc)) >> 5) != count) return 1;

    AnalysisInfoVec* vec = (AnalysisInfoVec*)(base + 0x4cc);
    for (int off = 0; off < 0x140; off += 0x20) {
        Region* r = (Region*)(g_16c7584 + off + 4);
        if (r->enabled != 0 && *(int*)(g_16c7584 + 0x14c) != (int)r) {
            Elem e = FUN_00ec9b30(r->args);
            if (FUN_00ec68f0(&e, (void*)(vec->begin + (r->index << 3))) == 0) return 1;
        }
    }
    return 0;
}

// @ 0x00eca1d0
// Validate then rebuild every analysis record, around a tutorial-manager step.
void __cdecl FUN_00eca1d0(void)
{
    char* obj = *(char**)g_16c757c;
    if (*(char*)(obj + 0x20) != 0) {
        int n = (*(int*)(obj + 0x74) - *(int*)(obj + 0x70)) / 0x4e0;
        int i = 0;
        if (n > 0) {
            do {
                if (FUN_00eca0f0(i) == 0) return;
                ++i;
                obj = *(char**)g_16c757c;
                n = (*(int*)(obj + 0x74) - *(int*)(obj + 0x70)) / 0x4e0;
            } while (i < n);
        }
    } else {
        if (FUN_00eca0f0(ScenarioTutorials_GetActive()) == 0) return;
    }

    ((TutorCtx*)*(void**)(g_16c7aa4 + 0x74))->FUN_00f45970();

    obj = *(char**)g_16c757c;
    if (*(char*)(obj + 0x20) != 0) {
        int n = (*(int*)(obj + 0x74) - *(int*)(obj + 0x70)) / 0x4e0;
        int i = 0;
        if (n > 0) {
            do {
                FUN_00eca010(i);
                ++i;
                obj = *(char**)g_16c757c;
                n = (*(int*)(obj + 0x74) - *(int*)(obj + 0x70)) / 0x4e0;
            } while (i < n);
        }
    } else {
        FUN_00eca010(ScenarioTutorials_GetActive());
    }

    ((TutorCtx*)*(void**)(g_16c7aa4 + 0x74))->FUN_00f45a80();
}

// ---------------------------------------------------------------- 0x00eca2f0
// @ 0x00eca2f0
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

// @ 0x00eca3b0
// Push every window listed under v1[page] through FUN_00ec7770.
void __cdecl FUN_00eca3b0(int param_1, int param_2)
{
    int key = (*(int**)(g_16c757c + 4))[param_1];
    VecHdr* r = ((Lookup*)(g_16c757c + 0x50))->FUN_00ec9820(&key);
    int i = 0;
    if ((((int)r->end - (int)r->begin) & ~3) > 0) {
        do {
            unsigned int id = (unsigned int)FUN_00ec6ab0(r->begin[i]);
            cSPUILayout* lay = (cSPUILayout*)*(void**)g_16c7584;
            void* w = lay->FindWindowByID(id, 1);
            int   a = ((TFui)((*(void***)w)[0xf0 / 4]))(w, 0xcdfb1002, 0);
            void* s = (void*)((TFui)((*(void***)w)[0xf0 / 4]))(w, 0xcdfb1003, 0);
            int   v = ((TF0)((*(void***)s)[0x3c / 4]))(s);
            FUN_00ec7770(param_2, a, 0, 0, v);
            ++i;
        } while (i < (((int)r->end - (int)r->begin) >> 2));
    }
}

// @ 0x00eca460
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

// @ 0x00eca4b0
// Palette action dispatch: pick the target from the cdfb10xx family, then run
// the matching handler for this record.
int* __cdecl FUN_00eca4b0(int* param_1, unsigned int param_2, int* param_3)
{
    int uVar1;
    if (param_1 == 0) uVar1 = 0;
    else uVar1 = ((TFu)((*(void***)param_1)[0xc / 4]))(param_1, 0x4c058d5);

    int* p;
    switch (param_2) {
    case 0xcdfb1000: p = (int*)param_3[0]; break;
    case 0xcdfb1020: p = (int*)param_3[1]; break;
    case 0xcdfb1030: p = (int*)param_3[2]; break;
    case 0xcdfb1040: p = (int*)param_3[3]; break;
    case 0xcdfb1050: p = (int*)param_3[4]; break;
    default:         p = param_1;         break;
    }
    if (p == (int*)0xffffffff) return (int*)0xffffffff;

    FUN_00ec8f40(uVar1);
    switch (param_2) {
    case 0xcdfb1000: FUN_00ec7950(uVar1); break;
    case 0xcdfb1020: FUN_00ec9690(param_3[0], uVar1); break;
    case 0xcdfb1030: FUN_00ec96f0(param_3[0], uVar1); break;
    case 0xcdfb1040: FUN_00eca3b0(param_3[0], uVar1); break;
    case 0xcdfb1050: FUN_00eca460(param_3[0], param_3[3], uVar1); break;
    }
    return p;
}

// @ 0x00eca670
// Wire one palette family (cdfb10xx) into a newly created record.
void __cdecl FUN_00eca670(void* param_1, unsigned int param_2, int* param_3, int param_4)
{
    (void)param_4;

    int* piVar1 = (int*)((TFui)((*(void***)param_1)[0xf0 / 4]))(param_1, param_2, 1);
    int* piVar2 = (int*)((TFui)((*(void***)piVar1)[0xf0 / 4]))(piVar1, 0xcdfb1001, 1);
    ((TFii)((*(void***)piVar2)[0x7c / 4]))(piVar2, 1, 0);

    int iVar3 = (int)FUN_00eca4b0(piVar2, param_2, param_3);
    if (iVar3 == -1) {
        ((TFii)((*(void***)piVar1)[0x7c / 4]))(piVar1, 1, 0);
        return;
    }
    ((TFii)((*(void***)piVar1)[0x7c / 4]))(piVar1, 1, 1);

    int iVar4 = ((TFu)((*(void***)piVar2)[0xc / 4]))(piVar2, 0x4c058d5);
    *(int*)(iVar4 + 0x8b0) = iVar3;
    *(int*)(iVar4 + 0x8ac) = iVar3;
    int* ebx = (int*)FUN_00ec79f0(iVar4, iVar3);

    int* piVar12 = (int*)((TFui)((*(void***)piVar1)[0xf0 / 4]))(piVar1, 0xcdfb1014, 1);
    int* piVar5  = (int*)((TFui)((*(void***)piVar1)[0xf0 / 4]))(piVar1, 0xcdfb1012, 1);
    int* piVar6  = (int*)((TFui)((*(void***)piVar1)[0xf0 / 4]))(piVar1, 0xcdfb1013, 1);
    if (piVar5 != 0 && piVar6 != 0 && piVar12 != 0) {
        ((TFii)((*(void***)piVar12)[0x7c / 4]))(piVar12, 1, 0);
        ((TFii)((*(void***)piVar6)[0x7c / 4]))(piVar6, 1, 0);
        ((TFii)((*(void***)piVar5)[0x7c / 4]))(piVar5, 1, 0);

        int* piVar7 = (int*)((TFui)((*(void***)ebx)[0xf0 / 4]))(ebx, 0xcdfb1002, 1);
        if (piVar7 != 0 && (((TF0)((*(void***)piVar7)[0x28 / 4]))(piVar7) & 1) != 0) {
            FUN_00ec6ee0(piVar5, piVar7, 1);
            ((TFii)((*(void***)piVar5)[0x7c / 4]))(piVar5, 1, 1);
        }

        int* piVar5b = (int*)((TFui)((*(void***)ebx)[0xf0 / 4]))(ebx, 0xcdfb1004, 1);
        if (piVar5b != 0 && (((TF0)((*(void***)piVar5b)[0x28 / 4]))(piVar5b) & 1) != 0) {
            void* uVar9 = FUN_00806880(piVar5b, 0, 0);
            FUN_00806aa0(piVar6, uVar9);
            ((TFii)((*(void***)piVar6)[0x7c / 4]))(piVar6, 1, 1);
        }

        int* piVar5c = (int*)((TFui)((*(void***)ebx)[0xf0 / 4]))(ebx, 0xcdfb1005, 1);
        if (piVar5c != 0 && (((TF0)((*(void***)piVar5c)[0x28 / 4]))(piVar5c) & 1) != 0) {
            FUN_00ec6ee0(piVar12, piVar5c, 0);
            ((TFii)((*(void***)piVar12)[0x7c / 4]))(piVar12, 1, 1);
        }
    }

    int* piVar1b = (int*)((TFui)((*(void***)piVar1)[0xf0 / 4]))(piVar1, 0xcdfb1011, 1);
    if (piVar1b != 0) {
        int* w3 = (int*)((TFui)((*(void***)ebx)[0xf0 / 4]))(ebx, 0xcdfb1003, 1);
        void* text = (w3 == 0)
                   ? (void*)0x013ec468
                   : (void*)((TF0)((*(void***)w3)[0x3c / 4]))(w3);
        ((TFp)((*(void***)piVar1b)[0x80 / 4]))(piVar1b, text);
    }
}

// @ 0x00eca920
// Select/deselect a region: replay all five palette families against it.
void __cdecl FUN_00eca920(int param_1)
{
    int b = (param_1 == *(int*)(g_16c7584 + 0x14c));
    int* args = (int*)(param_1 + 0xc);

    FUN_00eca670((void*)*(int*)(param_1 + 4), 0xcdfb1000, args, b);
    FUN_00eca670((void*)*(int*)(param_1 + 4), 0xcdfb1020, args, b);
    FUN_00eca670((void*)*(int*)(param_1 + 4), 0xcdfb1030, args, b);
    FUN_00eca670((void*)*(int*)(param_1 + 4), 0xcdfb1040, args, b);
    FUN_00eca670((void*)*(int*)(param_1 + 4), 0xcdfb1050, args, b);

    void* obj = (void*)*(int*)(param_1 + 4);
    if (b != 0) ((TF1)((*(void***)obj)[0x5c / 4]))(obj, 0x77ffffff);
    else        ((TF1)((*(void***)obj)[0x5c / 4]))(obj, -1);
}

// @ 0x00eca9c0
// Allocate/activate a region slot and select it.
void __cdecl FUN_00eca9c0(void)
{
    *(Region**)(g_16c7584 + 0x14c) = (Region*)FUN_00ec6d00();

    if (*(int*)(g_16c7584 + 0x14c) != 0) {
        Region* r = *(Region**)(g_16c7584 + 0x14c);
        r->index = *(int*)(g_16c7584 + 0x144) - 1;

        void* w = r->window;
        int* iv = (int*)((TF0)((*(void***)w)[0x34 / 4]))(w);
        void* w2 = ((Region*)*(void**)(g_16c7584 + 0x14c))->window;
        ((TFff)((*(void***)w2)[0x64 / 4]))(w2, 0.0f,
              (*(float*)((char*)iv + 0xc) - *(float*)((char*)iv + 4) - 1.0f)
              * (float)r->index);

        ((Region*)*(void**)(g_16c7584 + 0x14c))->args[0] = 0;
        ((Region*)*(void**)(g_16c7584 + 0x14c))->args[1] = -1;
        ((Region*)*(void**)(g_16c7584 + 0x14c))->args[2] = -1;
        ((Region*)*(void**)(g_16c7584 + 0x14c))->args[3] = -1;
        ((Region*)*(void**)(g_16c7584 + 0x14c))->args[4] = -1;
        FUN_00eca920((int)*(void**)(g_16c7584 + 0x14c));
    }
}

// @ 0x00ecaab0
// Drop a region slot and renumber the ones above it.
void __cdecl FUN_00ecaab0(Region* param_1)
{
    for (int base = 0; base < 0x140; base += 0xa0) {
        for (int k = 0; k < 5; ++k) {
            Region* r = (Region*)(g_16c7584 + base + 4 + 0x20 * k);
            if (r->enabled != 0 && param_1->index != -1 && r->index > param_1->index)
                r->index -= 1;
        }
    }

    void* obj = param_1->window;
    ((TFii)((*(void***)obj)[0x7c / 4]))(obj, 1, 0);

    param_1->enabled = 0;
    *(int*)(g_16c7584 + 0x144) -= 1;
    if (*(int*)(g_16c7584 + 0x14c) == 0) FUN_00eca9c0();
}

// @ 0x00ecabc0
// Move a region slot: clone onto a fresh slot positioned at the source's rect.
void __cdecl FUN_00ecabc0(Region* param_1)
{
    void* obj = param_1->window;
    int* a1 = (int*)((TF0)((*(void***)obj)[0x34 / 4]))(obj);
    float pair[2];
    pair[0] = *(float*)((char*)a1 + 0x0);
    pair[1] = *(float*)((char*)a1 + 0x4);

    int* a2 = (int*)((TF0)((*(void***)obj)[0x34 / 4]))(obj);
    int iVar4 = FUN_00ec6940(pair,
                   (*(float*)((char*)a2 + 0xc) - *(float*)((char*)a2 + 4)) - 1.0f);
    if (iVar4 == -1) return;

    Region* slot;
    if (*(int*)(g_16c7584 + 0x144) == 10) {
        if (*(int*)(g_16c7584 + 0x14c) == 0) return;
        slot = *(Region**)(g_16c7584 + 0x14c);
        *(int*)(g_16c7584 + 0x14c) = 0;
    } else {
        slot = (Region*)FUN_00ec6d00();
    }

    void* keep = slot->window;
    memcpy(slot, param_1, 0x20);
    slot->window = keep;

    void* o2 = slot->window;
    ((TFff)((*(void***)o2)[0x64 / 4]))(o2, pair[0], pair[1]);
    ((TF1)((*(void***)o2)[0x5c / 4]))(o2, -1);
    ((TFii)((*(void***)o2)[0x7c / 4]))(o2, 1, 1);

    for (int base = 0; base < 0x140; base += 0xa0) {
        for (int k = 0; k < 5; ++k) {
            Region* r = (Region*)(g_16c7584 + base + 4 + 0x20 * k);
            if (r->enabled != 0 && r != param_1 && r->index >= iVar4)
                r->index += 1;
        }
    }

    FUN_00eca1d0();
    FUN_00eca920((int)slot);
}