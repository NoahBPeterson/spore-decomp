// Slice s00bc74d0 (0x00bc74d0..0x00bc83df) — SP::cWorldEventsData: a vector-like
// container of 0x3c-byte records (begin/end/cap at +0/+4/+8, free/active cursors
// at +0x14/+0x18, embedded SP::cHierGrid at +0x1c) plus a first pair of helpers for
// the 0x7b4-byte "civ" array that this file also owns.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

#pragma warning(disable: 4100)

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// External callees / operators (relocation-masked).
// ---------------------------------------------------------------------------
extern "C" void* __cdecl op_new(int size, const char* name, int, int, const char* file, int line);
extern "C" void  __cdecl op_delete_(void* p);
extern "C" void  __cdecl op_delete(void* p);
extern "C" void* __cdecl FUN_00bc4630();
extern "C" void  __cdecl FUN_00bc4730();
extern "C" void  __cdecl FUN_00bc7170(void* end, uint n, void* hint);
extern "C" void  __cdecl FUN_00bc7110(void* dst, void* end);
extern "C" void  __cdecl FUN_00bc5730(int a, int b, int c);
extern "C" int*  __cdecl FUN_00bc79f0(void* last, void* first, void* dst);
extern "C" int*  __cdecl FUN_00bc7a30(void* first, void* last, void* dst);

struct RefObj {
    virtual void Add();       // vtbl + 0
    virtual void Release();   // vtbl + 4
};

struct cHierGrid { char b[0x84]; };
void __fastcall cHierGrid_ctor(void* p);
void __fastcall cHierGrid_Shutdown(void* p);
void __fastcall cHierGrid_Init(void* p, void* box, float v, int a, int b);

struct Rec {
    unsigned flags;   // 0x00
    int   f04;        // 0x04
    int   f08;        // 0x08
    int   f0c;        // 0x0c  (float in some paths)
    int   f10;        // 0x10
    int   f14;        // 0x14
    int   f18;        // 0x18
    int   f1c;        // 0x1c
    void* p20;        // 0x20
    void* p24;        // 0x24
    union { int f28; void* p28; };  // 0x28 (int in copy, refcounted ptr in assign)
    int   f2c;        // 0x2c
    int   f30;        // 0x30
    int   f34;        // 0x34
    int   f38;        // 0x38

    Rec* FUN_00bc76d0(Rec* src);   // operator=
    Rec* FUN_00bc7850(Rec* src);   // copy-construct
    Rec* FUN_00bc7920(Rec* src);   // assign / reset
};

struct WE {
    Rec* begin;   // 0x00
    Rec* end;     // 0x04
    Rec* cap;     // 0x08
    int  f0c;     // 0x0c
    int  f10;     // 0x10
    int  freeI;   // 0x14
    int  activeI; // 0x18
    cHierGrid grid; // 0x1c .. 0xa0

    void  FUN_00bc74d0(uint n);
    int   FUN_00bc7680(int index);
    void  FUN_00bc77e0(int index);
    void  FUN_00bc7a70(void** out, Rec* at);
    void  FUN_00bc7b70(uint n);
    int   FUN_00bc7c40(int first, int last);
    void  FUN_00bc7ca0(Rec* at, int* val);
    void  FUN_00bc7e20();
    uint  FUN_00bc7e80(int src);
};

// ===========================================================================
// @ 0x00bc74d0 — grow the 0x7b4-byte civ array if needed.
// ===========================================================================
struct Rec7 { char b[0x7b4]; };
void WE::FUN_00bc74d0(uint param_2)
{
    Rec7* b = (Rec7*)begin;
    Rec7* e = (Rec7*)end;
    if ((uint)(e - b) < param_2) {
        void* uVar1 = FUN_00bc4630();
        FUN_00bc7170(end, param_2 - (uint)(e - b), uVar1);
        FUN_00bc4730();
        return;
    }
    FUN_00bc7110((char*)begin + param_2 * 0x7b4, end);
}

// ===========================================================================
// @ 0x00bc7570 — (complex) load a civ list through PropertyManager; approximate.
// ===========================================================================
void __cdecl FUN_00bc7570(int param_1, int param_2, int param_3)
{
    // best-effort structural reproduction (not matched)
    if (0 < (int)((param_3 - param_2) >> 2))
        FUN_00bc5730(*(int*)param_2, param_1, param_3);
}

// ===========================================================================
// @ 0x00bc7610 — (complex) hashtable lookup of a resource factory list; approx.
// ===========================================================================
void* __cdecl FUN_00bc7610(int param_1, int param_2, char param_3)
{
    (void)param_1; (void)param_2; (void)param_3;
    return 0;
}

// ===========================================================================
// @ 0x00bc7680 — find the next active ("in use") record at/after index.
// ===========================================================================
int WE::FUN_00bc7680(int param_2)
{
    unsigned* puVar2 = (unsigned*)((char*)begin + param_2 * 0x3c);
    unsigned uVar1 = *puVar2;
    if ((uVar1 >> 0x1e & 1) == 0) {
        do {
            uVar1 = puVar2[0xf];
            puVar2 = puVar2 + 0xf;
            param_2 = param_2 + 1;
            if ((int)uVar1 >= 0) {
                return param_2;
            }
        } while ((uVar1 >> 0x1e & 1) == 0);
    }
    return 0x3fffffff;
}

// ===========================================================================
// @ 0x00bc76d0 — record assignment (moves the two refcounted pointers).
// ===========================================================================
Rec* Rec::FUN_00bc76d0(Rec* param_2)
{
    flags = param_2->flags;
    f04 = param_2->f04;
    f08 = param_2->f08;
    *(float*)&f0c = *(float*)&param_2->f0c;
    *(float*)&f10 = *(float*)&param_2->f10;
    f14 = param_2->f14;
    f18 = param_2->f18;
    f1c = param_2->f1c;
    void* piVar1 = param_2->p20;
    void* piVar2 = p20;
    if (piVar1 != piVar2) {
        if (piVar1 != 0) ((RefObj*)piVar1)->Add();
        p20 = piVar1;
        if (piVar2 != 0) ((RefObj*)piVar2)->Release();
    }
    piVar1 = param_2->p24;
    piVar2 = p24;
    if (piVar1 != piVar2) {
        if (piVar1 != 0) ((RefObj*)piVar1)->Add();
        p24 = piVar1;
        if (piVar2 != 0) ((RefObj*)piVar2)->Release();
    }
    f28 = param_2->f28;
    f2c = param_2->f2c;
    f30 = param_2->f30;
    f34 = param_2->f34;
    return this;
}

// ===========================================================================
// @ 0x00bc7780 — destroy a range of records (release pointers of active ones).
// ===========================================================================
int __cdecl FUN_00bc7780(Rec* param_1, Rec* param_2, int param_3)
{
    if (param_1 != param_2) {
        do {
            if ((param_1->flags >> 0x1f & 1) == 0) {
                void* piVar1 = *(void**)((char*)param_1 + 0x28);
                if (piVar1 != 0) ((RefObj*)piVar1)->Release();
                void* piVar2 = *(void**)((char*)param_1 + 0x24);
                if (piVar2 != 0) ((RefObj*)piVar2)->Release();
            }
            param_1 = (Rec*)((char*)param_1 + 0x3c);
            param_3 = param_3 + 0x3c;
        } while (param_1 != param_2);
    }
    return param_3;
}

// ===========================================================================
// @ 0x00bc77e0 — release the record at index and mark it free.
// ===========================================================================
void WE::FUN_00bc77e0(int param_2)
{
    int iVar2;
    unsigned* puVar1 = (unsigned*)((char*)begin + param_2 * 0x3c);
    void* p10 = *(void**)(puVar1 + 10);
    if (p10 != 0) ((RefObj*)p10)->Release();
    void* p9 = *(void**)(puVar1 + 9);
    if (p9 != 0) ((RefObj*)p9)->Release();
    *puVar1 = (activeI & 0x3fffffffU) | (*puVar1 & 0xc0000000) | 0x80000000;
    activeI = param_2;
    if (freeI == param_2) {
        iVar2 = FUN_00bc7680(param_2);
        freeI = iVar2;
    }
}

// ===========================================================================
// @ 0x00bc7850 — copy-construct a record (adds refs to the two pointers).
// ===========================================================================
Rec* Rec::FUN_00bc7850(Rec* param_2)
{
    flags = param_2->flags;
    f04 = param_2->f04;
    f08 = param_2->f08;
    *(float*)&f0c = *(float*)&param_2->f0c;
    *(float*)&f10 = *(float*)&param_2->f10;
    *(float*)&f14 = *(float*)&param_2->f14;
    *(float*)&f18 = *(float*)&param_2->f18;
    *(float*)&f1c = *(float*)&param_2->f1c;
    p20 = param_2->p20;
    if (p20 != 0) ((RefObj*)p20)->Add();
    p24 = param_2->p24;
    if (p24 != 0) ((RefObj*)p24)->Add();
    int* s = &param_2->f28;
    f28 = param_2->f28;
    f2c = s[1];
    f30 = s[2];
    f34 = s[3];
    return this;
}

// ===========================================================================
// @ 0x00bc78d0 — destroy a [first,last) range of records.
// ===========================================================================
void __stdcall FUN_00bc78d0(Rec* param_1, Rec* param_2)
{
    if (param_1 < param_2) {
        do {
            if ((param_1->flags >> 0x1f & 1) == 0) {
                void* piVar1 = *(void**)((char*)param_1 + 0x28);
                if (piVar1 != 0) ((RefObj*)piVar1)->Release();
                void* piVar2 = *(void**)((char*)param_1 + 0x24);
                if (piVar2 != 0) ((RefObj*)piVar2)->Release();
            }
            param_1 = (Rec*)((char*)param_1 + 0x3c);
        } while (param_1 < param_2);
    }
}

// ===========================================================================
// @ 0x00bc7920 — assign the record from param_2, keeping pointer lifetimes.
// ===========================================================================
Rec* Rec::FUN_00bc7920(Rec* param_2)
{
    if ((*&param_2->flags < 0) && ((*&flags >= 0))) {
        if (p28 != 0) {
            ((RefObj*)p28)->Release();
        }
        if (p24 != 0) {
            ((RefObj*)p24)->Release();
            flags = param_2->flags;
            return this;
        }
    }
    else if (*&param_2->flags >= 0) {
        if (*&flags < 0) {
            if (this != (Rec*)0xfffffffc) {
                ((Rec*)((char*)this + 4))->FUN_00bc7850((Rec*)((char*)param_2 + 4));
                flags = param_2->flags;
                return this;
            }
        }
        else {
            ((Rec*)((char*)this + 4))->FUN_00bc76d0((Rec*)((char*)param_2 + 4));
        }
    }
    flags = param_2->flags;
    return this;
}

// ===========================================================================
// @ 0x00bc79a0 — copy a [first,last) range into an uninitialised buffer.
// ===========================================================================
Rec* __cdecl FUN_00bc79a0(Rec* param_1, Rec* param_2, Rec* param_3)
{
    if (param_1 == param_2) {
        return param_3;
    }
    do {
        if (param_3 != 0) {
            param_3->flags = param_1->flags;
            if ((int)param_1->flags >= 0 && param_3 != (Rec*)0xfffffffc) {
                (param_3 + 1)->FUN_00bc7850(param_1 + 1);
            }
        }
        param_1 = (Rec*)((char*)param_1 + 0x3c);
        param_3 = (Rec*)((char*)param_3 + 0x3c);
    } while (param_1 != param_2);
    return param_3;
}

// ===========================================================================
// @ 0x00bc7a70 — release the record at `at` and return the next free slot.
// ===========================================================================
void WE::FUN_00bc7a70(void** param_2, Rec* param_3)
{
    FUN_00bc77e0(((char*)param_3 - (char*)begin) / 0x3c);
    unsigned* puVar1;
    do {
        puVar1 = (unsigned*)((char*)param_3 + 0x3c);
        if ((*(unsigned*)param_3 >> 0x1e & 1) != 0) break;
        param_3 = (Rec*)puVar1;
    } while ((int)*puVar1 < 0);
    *param_2 = puVar1;
}

// ===========================================================================
// @ 0x00bc7ac0 — (complex) age records / expire the world events; approximate.
// ===========================================================================
void __fastcall FUN_00bc7ac0(WE** param_1, int param_2)
{
    (void)param_1; (void)param_2;
}

// ===========================================================================
// @ 0x00bc7b70 — grow the record array to at least param_2 entries.
// ===========================================================================
void WE::FUN_00bc7b70(uint param_2)
{
    int iVar1, iVar2, iVar3;
    if ((uint)(((char*)cap - (char*)begin) / 0x3c) < param_2) {
        if (param_2 == 0) {
            iVar3 = 0;
        } else {
            iVar3 = (int)op_new(param_2 * 0x3c, "Simulator", 0, 0,
                                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        }
        iVar1 = (int)begin;
        iVar2 = (int)end;
        FUN_00bc79a0((Rec*)iVar1, (Rec*)iVar2, (Rec*)iVar3);
        FUN_00bc7780((Rec*)iVar1, (Rec*)iVar2, iVar3);
        if (begin != 0) {
            op_delete_(begin);
        }
        iVar1 = (int)begin;
        begin = (Rec*)iVar3;
        end = (Rec*)(iVar3 + ((int)end - iVar1) / 0x3c * 0x3c);
        cap = (Rec*)(iVar3 + param_2 * 0x3c);
    }
}

// ===========================================================================
// @ 0x00bc7c40 — erase the range [first,last); returns `first`.
// ===========================================================================
int WE::FUN_00bc7c40(int param_2, int param_3)
{
    int* uVar1 = FUN_00bc79f0((void*)param_3, (void*)end, (void*)param_2);
    FUN_00bc78d0((Rec*)uVar1, end);
    int n = (param_3 - param_2) * 0x77777777;
    int iVar2 = (int)(((long long)n) >> 0x20) - (param_3 - param_2);
    end = (Rec*)((char*)end + ((iVar2 >> 5) - (iVar2 >> 0x1f)) * 0x3c);
    return param_2;
}

// ===========================================================================
// @ 0x00bc7ca0 — insert a record at `at` (grow + move + assign).
// ===========================================================================
void WE::FUN_00bc7ca0(Rec* param_2, int* param_3)
{
    Rec* piVar2 = end;
    if (piVar2 != cap) {
        if (param_2 <= (Rec*)param_3 && (Rec*)param_3 < piVar2) {
            param_3 = (int*)((char*)param_3 + 0x3c);
        }
        if (piVar2 != 0) {
            piVar2->flags = ((Rec*)((char*)piVar2 - 0x3c))->flags;
            if ((int)((Rec*)((char*)piVar2 - 0x3c))->flags >= 0 && piVar2 != (Rec*)0xfffffffc) {
                (piVar2 - 0xe)->FUN_00bc7850((Rec*)((char*)piVar2 - 0x38));
            }
        }
        FUN_00bc7a30((void*)param_2, (void*)((char*)end - 0x3c), end);
        ((Rec*)param_3)->FUN_00bc7920((Rec*)param_3);
        end = (Rec*)((char*)end + 0x3c);
        return;
    }
    int local_4 = ((char*)piVar2 - (char*)begin) / 0x3c;
    int local_8;
    if (local_4 == 0) {
        local_4 = 1;
    } else {
        local_4 = local_4 * 2;
        if (local_4 == 0) {
            local_8 = 0;
            goto LBL;
        }
    }
    local_8 = (int)op_new(local_4 * 0x3c, "Simulator", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
LBL:
    Rec* iVar1 = begin;
    Rec* piVar4 = FUN_00bc79a0(iVar1, param_2, (Rec*)local_8);
    FUN_00bc7780(iVar1, param_2, local_8);
    if (piVar4 != 0) {
        piVar4->flags = *(unsigned*)param_3;
        if ((int)*(unsigned*)param_3 >= 0 && piVar4 != (Rec*)0xfffffffc) {
            (piVar4 + 1)->FUN_00bc7850((Rec*)(param_3 + 1));
        }
    }
    Rec* iVar2 = end;
    Rec* iVar3 = FUN_00bc79a0(param_2, iVar2, piVar4 + 1);
    FUN_00bc7780(param_2, iVar2, (int)(piVar4 + 1));
    if (begin != 0) {
        op_delete_(begin);
    }
    end = iVar3;
    begin = (Rec*)local_8;
    cap = (Rec*)(local_8 + local_4 * 0x3c);
}

// ===========================================================================
// @ 0x00bc7e20 — append a default (free) record, growing if full.
// ===========================================================================
void WE::FUN_00bc7e20()
{
    Rec* puVar1 = end;
    if (puVar1 < cap) {
        end = (Rec*)((char*)puVar1 + 0x3c);
        if (puVar1 != 0) {
            puVar1->flags = 0x80000000;
            return;
        }
    }
    else {
        Rec tmp;
        tmp.flags = 0x80000000;
        FUN_00bc7ca0(puVar1, (int*)&tmp);
        if ((int)tmp.flags >= 0) {
            void* p28 = *(void**)((char*)&tmp + 0x28);
            if (p28 != 0) ((RefObj*)p28)->Release();
            void* p24 = *(void**)((char*)&tmp + 0x24);
            if (p24 != 0) ((RefObj*)p24)->Release();
        }
    }
}

// ===========================================================================
// @ 0x00bc7e80 — pop the record at the free cursor and reinitialise it.
// ===========================================================================
uint WE::FUN_00bc7e80(int param_2)
{
    uint uVar3 = activeI;
    if (uVar3 == 0x3fffffff) {
        ((Rec*)begin)->FUN_00bc7850((Rec*)param_2);
        uVar3 = ((char*)end - (char*)begin) / 0x3c;
        FUN_00bc7e20();
        if (uVar3 != 0) {
            unsigned* puVar2 = (unsigned*)((char*)begin + (uVar3 - 1) * 0x3c);
            *puVar2 = *puVar2 & 0xbfffffff;
        }
        int iVar1 = uVar3 * 0x3c;
        *(unsigned*)((char*)begin + iVar1) |= 0x40000000;
        *(unsigned*)((char*)begin + iVar1) &= 0x7fffffff;
        if ((char*)begin + iVar1 + 4 != 0) {
            ((Rec*)begin)->FUN_00bc7850((Rec*)param_2);
        }
    }
    else {
        int iVar1 = uVar3 * 0x3c;
        unsigned* puVar2 = (unsigned*)((char*)begin + iVar1);
        activeI = *(unsigned*)((char*)begin + iVar1) & 0x3fffffff;
        *puVar2 = *puVar2 & 0x7fffffff;
        if ((char*)begin + iVar1 + 4 != 0) {
            ((Rec*)begin)->FUN_00bc7850((Rec*)param_2);
        }
    }
    if (uVar3 < (uint)freeI) {
        freeI = uVar3;
    }
    return uVar3;
}

// ===========================================================================
// @ 0x00bc7f80 — allocate and initialise a cWorldEventsData (0xa0 bytes).
// ===========================================================================
WE** __fastcall FUN_00bc7f80(WE** param_1)
{
    WE* puVar1 = (WE*)op_new(0xa0, "Simulator/cWorldEventsData", 0, 0, 0, 0);
    if (puVar1 != 0) {
        puVar1->begin = 0;
        puVar1->end = 0;
        puVar1->cap = 0;
        puVar1->freeI = 0x3fffffff;
        puVar1->activeI = 0x3fffffff;
        puVar1->FUN_00bc7b70(0x32);
        cHierGrid_ctor((char*)puVar1 + 0x1c);
        *param_1 = puVar1;
        return param_1;
    }
    WE* p = puVar1;
    *param_1 = p;
    return param_1;
}

// ===========================================================================
// @ 0x00bc8040 — clear the container and shut the embedded grid down.
// ===========================================================================
void __fastcall FUN_00bc8040(WE** param_1)
{
    WE* puVar1 = *param_1;
    puVar1->FUN_00bc7c40((int)puVar1->begin, (int)puVar1->end);
    puVar1->freeI = 0x3fffffff;
    puVar1->activeI = 0x3fffffff;
    WE* iVar2 = *param_1;
    if (*(int*)((char*)iVar2 + 0x40) != *(int*)((char*)iVar2 + 0x44)) {
        cHierGrid_Shutdown((char*)iVar2 + 0x1c);
        return;
    }
}

// ===========================================================================
// @ 0x00bc8080 — (complex) spatial query; approximate.
// ===========================================================================
void __cdecl FUN_00bc8080(float* param_1, float param_2, int* param_3, int param_4)
{
    (void)param_1; (void)param_2; (void)param_3; (void)param_4;
}

// ===========================================================================
// @ 0x00bc8200 — (complex) re-init the embedded hier grid; approximate.
// ===========================================================================
extern float DAT_0168ab70;
extern float DAT_0168ab74;
extern float DAT_0168ab78;
void __fastcall FUN_00bc8200(WE** param_1)
{
    WE* puVar1 = *param_1;
    puVar1->FUN_00bc7c40((int)puVar1->begin, (int)puVar1->end);
    puVar1->freeI = 0x3fffffff;
    puVar1->activeI = 0x3fffffff;
    WE* iVar3 = *param_1;
    if (*(int*)((char*)iVar3 + 0x40) != *(int*)((char*)iVar3 + 0x44)) {
        cHierGrid_Shutdown((char*)iVar3 + 0x1c);
    }
    float local_38[4];
    float local_28;
    float local_18, local_14, local_10, local_c, local_8, local_4;
    local_c = DAT_0168ab70 + 650.0f;
    local_8 = DAT_0168ab74 + 650.0f;
    local_18 = DAT_0168ab70 - 650.0f;
    local_14 = DAT_0168ab74 - 650.0f;
    local_4 = DAT_0168ab78 + 650.0f;
    local_10 = DAT_0168ab78 - 650.0f;
    local_38[2] = local_4 - local_10;
    local_38[0] = local_c - local_18;
    local_38[1] = local_8 - local_14;
    float* pfVar2 = local_38 + 1;
    if (local_8 - local_14 <= local_c - local_18) {
        pfVar2 = local_38;
    }
    if (*pfVar2 <= local_38[2] && local_38[2] != *pfVar2) {
        pfVar2 = local_38 + 2;
    }
    local_38[0] = *pfVar2 * 2.0f;
    local_28 = local_38[0] * 9.999999f;
    local_38[0] = local_38[0] * 0.01f;
    int iVar3b = (int)(local_38[0] + 0.5f);
    if ((float)iVar3b < local_38[0]) iVar3b = iVar3b + 1;
    int iVar4 = 0;
    for (; iVar3b != 0; iVar3b = iVar3b >> 1) iVar4 = iVar4 + 1;
    int iVar3c = (int)(local_28 + 0.5f);
    if ((float)iVar3c < local_28) iVar3c = iVar3c + 1;
    int iVar5 = 0;
    for (; iVar3c != 0; iVar3c = iVar3c >> 1) iVar5 = iVar5 + 1;
    iVar3b = 0;
    if (0 < iVar4 + -1) iVar3b = iVar4 + -1;
    iVar4 = 7;
    if (iVar5 + -1 < 7) iVar4 = iVar5 + -1;
    if (iVar4 < iVar3b) iVar4 = iVar3b;
    cHierGrid_Init((char*)*param_1 + 0x1c, &local_18, *pfVar2, iVar3b, iVar4);
}
