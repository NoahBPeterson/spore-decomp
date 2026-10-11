// slice s01085a80 -- Havok 3.1 hkWorld batch add/remove + penetration queries.
// Module flags: /vc71 (Havok dependency).
//
// These are macro-heavy Havok internals (HK_TIMER_*, hkArray::pushBack via
// hkArrayUtil::_reserve, hkThreadMemory stack allocs, hkMonitorStream TLS).  The
// source below reproduces the control flow, the array/timer traffic and the
// error-report structure faithfully, but the timer/alloc macros are modelled as
// helpers, so the result is behaviourally equivalent rather than byte-exact.
#include "types.h"

typedef unsigned int u32;
typedef unsigned long u32d;   // DWORD in TLS indices

// ---- TLS / profiling -------------------------------------------------------
extern "C" void* __stdcall TlsGetValue(u32d index);
extern "C" int   __stdcall TlsSetValue(u32d index, void* value);
extern unsigned int DAT_016e42a8;
extern unsigned int DAT_016e42a4;
extern unsigned int _s_threadMemoryInstance_hkThreadMemory__2V__hkThreadLocalData_PAVhkThreadMemory____A;
unsigned long long __cdecl rdtsc(void);

static inline void hkTimerBegin(const char* a, const char* b) {
    void* pvVar4 = TlsGetValue(DAT_016e42a8);
    void* pvVar5 = TlsGetValue(DAT_016e42a4);
    if (pvVar5 < pvVar4) {
        unsigned int* pu = (unsigned int*)TlsGetValue(DAT_016e42a4);
        pu[0] = (unsigned int)a;
        if (b != 0) pu[3] = (unsigned int)b;
        unsigned long long v = rdtsc();
        pu[1] = (unsigned int)v;
        TlsSetValue(DAT_016e42a4, pu + ((b != 0) ? 4 : 3));
    }
}
static inline void hkTimerEnd(const char* a) {
    void* pvVar4 = TlsGetValue(DAT_016e42a8);
    void* pvVar5 = TlsGetValue(DAT_016e42a4);
    if (pvVar5 < pvVar4) {
        unsigned int* pu = (unsigned int*)TlsGetValue(DAT_016e42a4);
        pu[0] = (unsigned int)a;
        unsigned long long v = rdtsc();
        pu[1] = (unsigned int)v;
        TlsSetValue(DAT_016e42a4, pu + 3);
    }
}

// hkThreadMemory stack-array alloc: returns a pointer plus keeps the bookkeeping
// local (local_8=caps|flag, local_c/live size).  Modelled on the raw fields.
struct hkStackArray {
    int*   m_data;      // +0
    u32    m_size;      // +4
    u32    m_caps;      // +8
    void  hkStackReserve(u32 bytes);
};
void hkStackArray::hkStackReserve(u32 bytes) {
    int* mem = (int*)TlsGetValue(
        _s_threadMemoryInstance_hkThreadMemory__2V__hkThreadLocalData_PAVhkThreadMemory____A);
    m_data = (int*)mem[8];
    u32 need = (bytes + 0x10) & 0xfffffff0;
    u32 end = (u32)m_data + need;
    if ((u32)mem[0xb] < end)
        m_data = (int*)(*(int(**)(u32))(*mem + 0xc))(need);
    else
        mem[8] = (int)end;
}

// hkArray<T>::pushBack (data ptr at off, size at off+4, caps at off+8)
void FUN_0107f530(int* arr, int elem);
static inline void hkArrPush(void* obj, int off, int val) {
    int** slot = (int**)((char*)obj + off);
    int* size = (int*)((char*)obj + off + 4);
    u32*  cap  = (u32*)((char*)obj + off + 8);
    if ((u32)*size == (*cap & 0x3fffffff))
        FUN_0107f530((int*)slot, 4);
    (*slot)[*size] = val;
    *size = *size + 1;
}

// error/warning report accumulator used by the *Batch guard paths
struct HkOpReport { int flag; int* p; u32 n; };

// ---- callees ---------------------------------------------------------------
void  __cdecl FUN_0109afe0(void* report);
void  __cdecl FUN_010cc480(int a, int b);
void  __cdecl FUN_010f0bb0(int* a, int b);
void  __cdecl FUN_01082bf0(void);
void  __cdecl FUN_0107db10(int a, int b, int c);
int   __cdecl FUN_0109ec50(int a, int* e);
void  __cdecl FUN_0109ea00(int* e);
void  __cdecl FUN_010a03c0(int a, int* e);
void  __cdecl FUN_0109ae60(void);
void  __cdecl FUN_0109eaa0(int a, int* e);
void  __cdecl FUN_010a24b0(int* e);
void  __cdecl FUN_010a1170(int a, int* b, int* c);
void  __cdecl FUN_0109eb30(int a, int* e);
void  __cdecl FUN_010a20b0(int* e);
void  __cdecl FUN_01082590(void);
void  __cdecl FUN_0109ed70(int a, int* e);
void  __cdecl FUN_0108e370(void);
void  __cdecl FUN_010cc410(int a, int b, int c);
void  __cdecl FUN_0109ee00(int a, int e);
void  __cdecl FUN_0108e300(void);

static inline int hkTlsPop(int off) {
    int* p = (int*)TlsGetValue(
        _s_threadMemoryInstance_hkThreadMemory__2V__hkThreadLocalData_PAVhkThreadMemory____A);
    (void)off; return 0;
}
static void hkThreadFree(int ptr, int size, int align) {
    int* mem = (int*)TlsGetValue(
        _s_threadMemoryInstance_hkThreadMemory__2V__hkThreadLocalData_PAVhkThreadMemory____A);
    mem[8] = ptr;
    if (ptr == mem[10])
        (*(void(**)(int))(*mem + 0x10))(ptr);
    (void)size; (void)align;
}

// ===========================================================================
// @ 0x01085a80  hkWorld::removeEntityBatch
// ===========================================================================
struct hkWorld {
    void FUN_01085a80(int* param_2, u32 param_3);
    int* FUN_01085e60(int* param_2);
    void FUN_01086030(int* param_2);
    void FUN_010861c0(int param_2, u32 param_3);
    void FUN_01086500(int param_2, u32 param_3);
    void FUN_010867a0(int* param_2, int* param_3, int param_4);
};

void hkWorld::FUN_01085a80(int* param_2, u32 param_3)
{
    int param_1 = (int)this;
    if (0 < (int)param_3) {
        if (*(int*)(param_1 + 0x8c) != 0) {
            HkOpReport r; r.flag = 7; r.p = param_2; r.n = param_3;
            FUN_0109afe0(&r);
            return;
        }
        *(int*)(param_1 + 0x8c) = 1;
        hkTimerBegin("LtRemEntities", "Init+CallBck");
        hkStackArray a1; a1.m_size = 0; a1.m_caps = 0x80000000;
        a1.hkStackReserve(param_3 * 4);
        a1.m_caps = param_3 | 0x80000000;
        int* end = param_2 + param_3;
        for (; param_2 != end; param_2 = param_2 + 1) {
            if (*(int*)(*param_2 + 0x1c) != 0) {
                a1.m_data[a1.m_size] = *param_2 + 0x30;
                a1.m_size = a1.m_size + 1;
            }
        }
        hkTimerBegin("StBroadPhase", 0);
        u32 n = *(u32*)(param_1 + 0x2e4);
        hkStackArray a2; a2.m_size = 0; a2.m_caps = 0x80000000;
        a2.hkStackReserve(n * 8);
        a2.m_caps = n | 0x80000000;
        (*(void(**)(void*, void*))(**(int**)(param_1 + 100) + 0x14))(&a1, &a2);
        hkTimerBegin("StDelAgents", 0);
        FUN_010cc480(0, (int)end);
        hkThreadFree((int)a2.m_data, a2.m_size << 3, 0x14);
        int* list = a1.m_data;
        if (3 < *(int*)(param_1 + 0xc4))
            FUN_010f0bb0(a1.m_data, 0);
        hkTimerBegin("StRemoveCb", 0);
        for (; list != 0; list = list + 1) {
            FUN_0109ec50(param_1, list);
            FUN_0109ea00(list);
            FUN_010a03c0(param_1, list);
            if ((short)((int*)*list)[1] == 0)
                (*(void(**)(void))(*(int*)*list + 0x10))();
            FUN_0109ae60();
        }
        hkTimerEnd("\x01");
        int* piVar7 = (int*)(param_1 + 0x8c);
        *piVar7 = *piVar7 + -1;
        if ((*piVar7 == 0) && (*(int*)(param_1 + 0x88) != 0) && (*(char*)(param_1 + 0x94) == 0))
            FUN_01082bf0();
        hkThreadFree((int)a1.m_data, a1.m_size << 2, 0x14);
    }
}

// ===========================================================================
// @ 0x01085e60  hkWorld::addEntityBatch
// ===========================================================================
int* hkWorld::FUN_01085e60(int* param_2)
{
    int param_1 = (int)this;
    int* retval = 0;
    if (*(int*)(param_1 + 0x8c) != 0) {
        HkOpReport r; r.flag = 10; r.p = param_2; r.n = 0;
        FUN_0109afe0(&r);
        return 0;
    }
    if ((short)param_2[1] != 0)
        *(short*)((int)param_2 + 6) = (short)(*(short*)((int)param_2 + 6) + 1);
    *(int*)(param_1 + 0x8c) = *(int*)(param_1 + 0x8c) + 1;

    hkStackArray arr; arr.m_size = 0; arr.m_caps = 0x80000004;
    u32 live = 0;
    (*(void(**)(void*))(*param_2 + 0xc))(&arr);
    live = arr.m_size;
    int iVar6 = 0;
    param_2[2] = param_1;
    if (0 < (int)live) {
        int iVar7 = 0;
        do {
            int iVar2 = *(int*)((int)arr.m_data + iVar7 * 4);
            int iVar3 = *(int*)(iVar2 + 0x5c);
            int* piVar1 = (int*)(iVar2 + 0xc0);
            int iVar4 = 0;
            if (0 < *(int*)(iVar2 + 0xc4)) {
                int* piVar5 = (int*)*piVar1;
                do {
                    if (*piVar5 == 0) {
                        if (-1 < iVar4) {
                            *(int**)(*piVar1 + iVar4 * 4) = retval;
                            goto LAB_01085f46;
                        }
                        break;
                    }
                    iVar4 = iVar4 + 1;
                    piVar5 = piVar5 + 1;
                } while (iVar4 < *(int*)(iVar2 + 0xc4));
            }
            if (*(u32*)(iVar2 + 0xc4) == (*(u32*)(iVar2 + 200) & 0x3fffffff))
                FUN_0107f530(piVar1, 4);
            *(int**)(*piVar1 + *(int*)(iVar2 + 0xc4) * 4) = retval;
            *(int*)(iVar2 + 0xc4) = *(int*)(iVar2 + 0xc4) + 1;
        LAB_01085f46:
            if (*(short*)(iVar3 + 0x20) != -1) {
                if (iVar6 == 0) {
                    iVar6 = *(int*)((int)arr.m_data + iVar7 * 4);
                    FUN_010a24b0(retval);
                } else {
                    int iVar2b = *(int*)((int)arr.m_data + iVar7 * 4);
                    if (*(int*)(iVar6 + 0x5c) != *(int*)(iVar2b + 0x5c))
                        FUN_010a1170(0, (int*)iVar6, (int*)iVar2b);
                }
            }
            iVar7 = iVar7 + 1;
        } while (iVar7 < (int)live);
        if (iVar6 != 0) goto LAB_01085fbc;
    }
    FUN_010a24b0(param_2);
    retval = param_2;
LAB_01085fbc:
    {
        int* piVar1 = (int*)(param_1 + 0x8c);
        *piVar1 = *piVar1 + -1;
        if ((*piVar1 == 0) && (*(int*)(param_1 + 0x88) != 0) && (*(char*)(param_1 + 0x94) == 0))
            FUN_01082bf0();
    }
    FUN_0109eaa0(param_1, retval);
    hkThreadFree((int)arr.m_data, arr.m_size << 2, 0x14);
    return retval;
}

// ===========================================================================
// @ 0x01086030  hkWorld::removeActionImmediately
// ===========================================================================
void hkWorld::FUN_01086030(int* param_2)
{
    int param_1 = (int)this;    if ((short)param_2[1] != 0)
        *(short*)((int)param_2 + 6) = (short)(*(short*)((int)param_2 + 6) + 1);
    *(int*)(param_1 + 0x8c) = *(int*)(param_1 + 0x8c) + 1;
    FUN_0109eb30(param_1, param_2);

    hkStackArray arr; arr.m_size = 0; arr.m_caps = 0x80000004;
    u32 live = 0;
    (*(void(**)(void*))(*param_2 + 0xc))(&arr);
    live = arr.m_size;
    int iVar5 = 0;
    if (0 < (int)live) {
        do {
            int iVar2 = *(int*)((int)arr.m_data + iVar5 * 4);
            int iVar3 = 0;
            if (0 < *(int*)(iVar2 + 0xc4)) {
                u32* puVar4 = *(u32**)(iVar2 + 0xc0);
                do {
                    if ((int*)*puVar4 == param_2) goto LAB_010860bf;
                    iVar3 = iVar3 + 1;
                    puVar4 = puVar4 + 1;
                } while (iVar3 < *(int*)(iVar2 + 0xc4));
            }
            iVar3 = -1;
        LAB_010860bf:
            *(u32*)(*(int*)(iVar2 + 0xc0) + iVar3 * 4) = 0;
            iVar5 = iVar5 + 1;
        } while (iVar5 < (int)live);
    }
    int iVar5b = param_2[3];
    FUN_010a20b0(param_2);
    param_2[2] = 0;
    if (((short)param_2[1] != 0) &&
        (*(short*)((int)param_2 + 6) = (short)(*(short*)((int)param_2 + 6) - 1),
         *(short*)((int)param_2 + 6) == 0))
        (*(void(**)(int))*param_2)(1);
    int iVar2b = *(int*)(iVar5b + 0x1c);
    if (*(short*)(iVar5b + 0x22) == -1) {
        *(unsigned short*)(iVar5b + 0x22) = *(unsigned short*)(iVar2b + 0x54);
        if (*(u32*)(iVar2b + 0x54) == (*(u32*)(iVar2b + 0x58) & 0x3fffffff))
            FUN_0107f530((int*)(iVar2b + 0x50), 4);
        *(int*)(*(int*)(iVar2b + 0x50) + *(int*)(iVar2b + 0x54) * 4) = iVar5b;
        *(int*)(iVar2b + 0x54) = *(int*)(iVar2b + 0x54) + 1;
    }
    hkThreadFree((int)arr.m_data, arr.m_size << 2, 0x14);
    {
        int* piVar1 = (int*)(param_1 + 0x8c);
        *piVar1 = *piVar1 + -1;
        if ((*piVar1 == 0) && (*(int*)(param_1 + 0x88) != 0) && (*(char*)(param_1 + 0x94) == 0))
            FUN_01082bf0();
    }
    if (((short)param_2[1] != 0) &&
        (*(short*)((int)param_2 + 6) = (short)(*(short*)((int)param_2 + 6) - 1),
         *(short*)((int)param_2 + 6) == 0))
        (*(void(**)(int))*param_2)(1);
}

// ===========================================================================
// @ 0x010861c0  hkWorld::addPhantomBatch
// ===========================================================================
void hkWorld::FUN_010861c0(int param_2, u32 param_3)
{
    int param_1 = (int)this;    if (*(int*)(param_1 + 0x90) + *(int*)(param_1 + 0x8c) != 0) {
        HkOpReport r; r.flag = 0xf; r.p = (int*)param_2; r.n = param_3;
        FUN_0109afe0(&r);
        return;
    }
    *(int*)(param_1 + 0x8c) = *(int*)(param_1 + 0x8c) + 1;

    hkStackArray a1; a1.m_size = 0; a1.m_caps = 0x80000000;
    a1.hkStackReserve(param_3 * 4);
    a1.m_caps = param_3 | 0x80000000;

    hkStackArray a2; a2.m_size = 0; a2.m_caps = 0x80000000;
    a2.hkStackReserve(param_3 * 0x20);
    a2.m_size = param_3;
    a1.m_size = param_3;           // local_1c / local_c aliasing in original
    a2.m_caps = param_3 | 0x80000000;

    int iVar5 = 0;
    if (0 < (int)param_3) {
        int local_40 = 0;
        do {
            int* piVar2 = *(int**)(param_2 + iVar5 * 4);
            if (piVar2[9] == 0) {
                int iVar3 = (*(int(**)(void))(*piVar2 + 0xc))();
                piVar2[9] = iVar3;
            }
            piVar2[2] = param_1;
            *(int**)((int)a1.m_data + iVar5 * 4) = piVar2 + 0xc;
            (*(void(**)(int))(*piVar2 + 0x14))(local_40 + (int)a2.m_data);
            FUN_01082590();
            hkArrPush((void*)param_1, 0xcc, (int)piVar2);
            FUN_0109ed70(param_1, piVar2);
            FUN_0108e370();
            iVar5 = iVar5 + 1;
            local_40 = local_40 + 0x20;
        } while (iVar5 < (int)param_3);
    }
    u32 n = *(u32*)(param_1 + 0x2e4);
    hkStackArray a3; a3.m_size = 0; a3.m_caps = 0x80000000;
    a3.hkStackReserve(n * 8);
    a3.m_caps = n | 0x80000000;
    (*(void(**)(void*, void*, void*))(**(int**)(param_1 + 100) + 0xc))(&a1, &a2, &a3);
    int iVar5b = (*(int*)(param_1 + 0x7c) == 0) ? 0 : *(int*)(param_1 + 0x7c) + 8;
    FUN_010cc410(0, param_2, iVar5b);
    {
        int* piVar2 = (int*)(param_1 + 0x8c);
        *piVar2 = *piVar2 + -1;
        if ((*piVar2 == 0) && (*(int*)(param_1 + 0x88) != 0) && (*(char*)(param_1 + 0x94) == 0))
            FUN_01082bf0();
    }
    hkThreadFree((int)a3.m_data, a3.m_size << 3, 0x14);
    hkThreadFree((int)a2.m_data, a2.m_size << 5, 0x14);
    hkThreadFree((int)a1.m_data, a1.m_size << 2, 0x14);
}

// ===========================================================================
// @ 0x01086500  hkWorld::removePhantomBatch
// ===========================================================================
void hkWorld::FUN_01086500(int param_2, u32 param_3)
{
    int param_1 = (int)this;    if (*(int*)(param_1 + 0x90) + *(int*)(param_1 + 0x8c) != 0) {
        HkOpReport r; r.flag = 0x10; r.p = (int*)param_2; r.n = param_3;
        FUN_0109afe0(&r);
        return;
    }
    *(int*)(param_1 + 0x8c) = *(int*)(param_1 + 0x8c) + 1;

    hkStackArray a1; a1.m_size = 0; a1.m_caps = 0x80000000;
    a1.hkStackReserve(param_3 * 4);
    a1.m_caps = param_3 | 0x80000000;
    if (0 < (int)param_3) {
        int iVar8 = 0;
        do {
            int iVar3 = *(int*)(param_2 + iVar8 * 4);
            *(int*)((int)a1.m_data + a1.m_size * 4) = iVar3 + 0x30;
            a1.m_size = a1.m_size + 1;
            FUN_0109ee00(param_1, iVar3);
            FUN_0108e300();
            iVar8 = iVar8 + 1;
        } while (iVar8 < (int)param_3);
    }
    u32 n = *(u32*)(param_1 + 0x2e4);
    hkStackArray a2; a2.m_size = 0; a2.m_caps = 0x80000000;
    a2.hkStackReserve(n * 8);
    a2.m_caps = n | 0x80000000;
    (*(void(**)(void*, void*))(**(int**)(param_1 + 100) + 0x14))(&a1, &a2);
    FUN_010cc480(0, 0);
    hkThreadFree((int)a2.m_data, a2.m_size << 3, 0x14);

    int iVar8 = 0;
    if (0 < (int)param_3) {
        do {
            int* piVar2 = *(int**)((int)a1.m_data + iVar8 * 4);
            int iVar3 = 0;
            piVar2[2] = 0;
            if (0 < *(int*)(param_1 + 0xd0)) {
                int* piVar7 = *(int**)(param_1 + 0xcc);
                do {
                    if ((int*)*piVar7 == piVar2) goto LAB_010866e1;
                    iVar3 = iVar3 + 1;
                    piVar7 = piVar7 + 1;
                } while (iVar3 < *(int*)(param_1 + 0xd0));
            }
            iVar3 = -1;
        LAB_010866e1:
            {
                int iVar4 = *(int*)(param_1 + 0xd0) - 1;
                *(int*)(param_1 + 0xd0) = iVar4;
                *(int*)(*(int*)(param_1 + 0xcc) + iVar3 * 4) =
                    *(int*)(*(int*)(param_1 + 0xcc) + iVar4 * 4);
            }
            if ((short)piVar2[1] == 0)
                (*(void(**)(void))(*(int*)piVar2 + 0x2c))();
            FUN_0109ae60();
            iVar8 = iVar8 + 1;
        } while (iVar8 < (int)param_3);
    }
    {
        int* piVar2 = (int*)(param_1 + 0x8c);
        *piVar2 = *piVar2 + -1;
        if ((*piVar2 == 0) && (*(int*)(param_1 + 0x88) != 0) && (*(char*)(param_1 + 0x94) == 0))
            FUN_01082bf0();
    }
    hkThreadFree((int)a1.m_data, a1.m_size << 2, 0x14);
}

// ===========================================================================
// @ 0x010867a0  hkWorld::getPenetrations
// ===========================================================================
void hkWorld::FUN_010867a0(int* param_2, int* param_3, int param_4)
{
    int param_1 = (int)this;
    int local_444 = param_1;
    (void)local_444;
    hkTimerBegin("LthkWorld::getPenetrations", "broadphase");

    int iStack_438 = 0;
    int iStack_434 = 0;
    int iStack_430 = 0;
    int* piStack_438p = (int*)&iStack_438;
    (void)piStack_438p;
    int local_440[2];

    (*(void(**)(int, float, int*))(*(int*)*param_2 + 0xc))
        (param_2[2], (float)param_3[2] - *(float*)(*(int*)(param_1 + 0x78) + 8) * 0.5f,
         local_440);

    int auStack_44c[2];
    int* puStack_42c = (int*)&iStack_430;
    u32 uStack_428 = 0;
    u32 uStack_424 = 0x80000080;
    (*(void(**)(int*, int**))(**(int**)(param_1 + 100) + 0x2c))
        (auStack_44c, &puStack_42c);

    int iVar8 = iStack_434;
    int iVar5 = (*(int(**)(void))(*(int*)*param_2 + 8))();

    hkTimerBegin("Stnarrowphase", 0);
    int iVar6 = iStack_430 + -1;
    if (-1 < iVar6) {
        int* piVar11 = (int*)(iVar8 + 4);
        do {
            int* piVar12 = (int*)((int)*(char*)(*piVar11 + 5) + *piVar11);
            char* pcVar7 = (char*)(*(int(**)(void*, int*, int*))
                (*(int*)(*(int*)(param_1 + 0x7c) + 8) + 4))(0, param_2, piVar12);
            if ((param_2 != piVar12) && (*pcVar7 != 0) && ((int*)*piVar12 != 0)) {
                iVar8 = (*(int(**)(void))(*(int*)*piVar12 + 8))();
                (*(void(**)(int*, int*, int*, int))
                    (*param_3 + 0x994 +
                     (u32)*((unsigned char*)(iVar5 * 0x20 + *param_3 + 400 + iVar8)) * 0x14))
                    (param_2, piVar12, param_3, param_4);
                if (*(char*)(param_4 + 4) != 0) break;
            }
            piVar11 = piVar11 + 2;
            iVar6 = iVar6 + -1;
        } while (-1 < iVar6);
    }
    hkTimerEnd("\x01");
    hkThreadFree(local_440[0], iStack_438 << 3, 0x14);
}
