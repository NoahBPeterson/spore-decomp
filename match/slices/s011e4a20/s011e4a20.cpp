// Slice s011e4a20 -- RenderWare 4 core: rw::core::arena section (de)serialization.
// Range 0x011e4a20..0x011e59e0.  Module: Native Release/rwarenasections.obj
// (RenderWare 4 core LTCG range 0x011e2000..0x0120bc50).  Equivalence-only: the LTCG
// build does not reproduce byte-for-byte under a normal compile, so this slice targets
// behavioural equivalence (tools/difftest/equiv.py), not byte matching.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (see nonmatching.txt)
#include "types.h"

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef int                int32;

// ------------------------------------------------------------------ extern callees
uint32 __cdecl FUN_011e21b0(uint32 typeId);                  // rw_FindTypeReg
void   __cdecl FUN_011e45c0(void* typeReg);                  // rw_BaseResourceSetupTypeRegPtrs
void*  __cdecl FUN_011e4910(void* manifest, uint32 n);       // ArenaSectionManifest::Initialize
uint32 __cdecl FUN_011e22c0(uint32 typeId);                  // ArenaTypeRegGetType
uint32 __cdecl FUN_011e22b0(void* arena);                    // arena header lookup
void*  __cdecl FUN_011e22a0(void* arena);                    // ArenaSectionManifest::ExternalArenas
void*  __cdecl FUN_011e3e10(uint32 id);                      // arena lookup by id
void*  __cdecl FUN_011e5e90(void* a, void* b);               // stream ctor
uint32 __cdecl FUN_011e5ff0(const char* s, int n);           // string length helper
uint32 __cdecl FUN_011e8b20(char* dst, const char* src);     // StringCopy
uint32 __cdecl FUN_011e8c40(const char* s);                  // string length
char*  __cdecl FUN_011e8c60(const char* s, int c);           // string find-char
void   __cdecl FUN_011ea8f0(void* p, uint32 n);              // free
void*  __cdecl FUN_011e6d20(uint32 size);                    // operator new
void   __cdecl FUN_011e07ef(void* fn);                       // atexit

// Absolute data symbols reached through their addresses (kept as arrays so a
// relocation, not a folded constant, is emitted).
extern uint8 g_arenaMgrVtbl[];      // 0x0140a578  ("@ l" literal / ArenaManager vtable)
extern uint8 g_arenaMgrData[];      // 0x0140a57c
extern uint32 g_atomInitFlag;       // 0x016f4b00
extern uint32 g_atomInitFlag2;      // 0x016f4b08
extern void*  g_atomListHead;       // 0x016f4af4
extern uint8  g_atomHeadStorage[];  // 0x016f4afc
extern uint8* g_streamListHead;     // 0x016f4b0c

void __cdecl FUN_013cb3f0();        // atexit trampoline (0x013cb3f0)

// ------------------------------------------------------------------ section headers
struct SectionBase {
    uint32 typeReg;                 // +0x00
    uint32 count;                   // +0x04
    uint32 data;                    // +0x08
    uint32 pad0c;                   // +0x0c
};

// ------------------------------------------------------------------ path holder
struct ArenaPathHolder {
    uint8  pad00[0x14];
    void*  base;                    // +0x14
    uint32 baseLen;                 // +0x18
    uint32 count;                   // +0x1c
    void*  pieces;                  // +0x20

    void Split(const char* path);   // 0x011e5900
};

// ------------------------------------------------------------------ thiscall host
// The arena serializer (`Arena`, called `param_3`/`esi` in the cards) walks a section
// through a pair of function pointers at +0x2c (no-context form) and +0x30 (context
// form). Only the fields the slice touches are modelled.
struct Arena {
    uint8  pad00[0x28];
    uint32 serial28;                // +0x28  serial position used by the advance callbacks
    void   (__thiscall* writeNoCtx)(void* self, void* data, uint32 n, uint32 param);   // +0x2c
    void   (__thiscall* writeCtx)(void* self, void* data, uint32 n, uint32 param, uint32 ctx); // +0x30
    uint32 writeCtxArg;             // +0x34
    uint8  pad38[0x7c - 0x38];
    uint32 serialPos;               // +0x7c
    uint8  pad80[0xc0 - 0x80];
    uint32 pos;                     // +0xc0
    uint32 align;                   // +0xc4

    uint32 IdToObject(void* id);    // 0x011e2300  __thiscall
    uint32 ObjectToId(void* obj);   // 0x011e3c30  __thiscall
};

// rw::core::atom::StaticAtomTable -- only the thunked Fixup is needed.
struct AtomTable {
    uint32 pad00;
    uint32 Fixup(Arena* arena);     // 0x011eb040  __thiscall (ret 4)
};

// ArenaManager::Data is reached through the function pointer slot at 0x0140a57c.
typedef uint32 (__thiscall* ArenaMgrDataFn)(void*);

// 0x011eb950  __fastcall: writes the manager vtable into *(void**)this.
struct VtblHolder { void SetVtbl(); };

// 0x016f4afc subsingleton: Init() returns `this` unchanged.
struct AtomSingleton { void* Init(); };

// ------------------------------------------------------------------ slab helpers
// @ 0x011e4a20
void* __cdecl rw_ArenaSectionTypes_Initialize(void** out, uint32 n)
{
    uint32* p = (uint32*)*out;
    uint32  bytes = n * 4 + 0xc;
    uint8*  q = (uint8*)p;
    for (uint32 i = 0; i < bytes; ++i)
        q[i] = 0;
    p[0] = FUN_011e21b0(0x10005);
    p[1] = n;
    p[2] = (uint32)(p + 3);
    *(uint32*)(p[2]) = FUN_011e21b0(0);
    *(uint32*)(p[2] + 0x10) = FUN_011e21b0(0x10010);
    FUN_011e45c0((void*)(p + 2));
    return p;
}

// @ 0x011e4aa0
void __cdecl rw_section_types_advance(void* section, void* ctx)
{
    *(uint32*)((char*)ctx + 0x28) += *(uint32*)((char*)section + 4) * 4 + 0xc;
}

// @ 0x011e4ad0
void __cdecl rw_section_init_table12(uint32* p, uint32 n)
{
    p[1] = 1;
    p[3] = 1;
    p[0] = 0;
    p[2] = 0;
    p[5] = 1;
    p[4] = 0;
    p[7] = 1;
    p[6] = 0;
    p[0] = n * 8 + 0xc;
    p[1] = 4;
}

// @ 0x011e4b20
void* __cdecl rw_ArenaSectionExternalArenas_Initialize(void** out, uint32 n)
{
    uint32* p = (uint32*)*out;
    uint32  bytes = n * 8 + 0xc;
    uint8*  q = (uint8*)p;
    for (uint32 i = 0; i < bytes; ++i)
        q[i] = 0;
    p[0] = FUN_011e21b0(0x10006);
    p[1] = n;
    p[2] = (uint32)((char*)p + n * 4 + 0xc);
    uint32 vmgr = 0x0140a578;
    ArenaMgrDataFn dataFn = *(ArenaMgrDataFn*)&g_arenaMgrData;
    uint32 iVar3 = *(uint32*)(dataFn(&vmgr) + 8);
    *(uint32*)(p[2]) = 0;
    p[3] = 0;
    *(uint32*)(p[2] + 4) = *(uint32*)(iVar3 + 0x30);
    p[4] = iVar3;
    *(uint32*)(p[2] + 8) = 0;
    p[5] = 0;
    return p;
}

// @ 0x011e4bb0
void __cdecl rw_section_ext_advance(void* section, void* ctx)
{
    *(uint32*)((char*)ctx + 0x28) += *(uint32*)((char*)section + 4) * 8 + 0xc;
}

// @ 0x011e4be0
void __cdecl rw_section_init_table1c(uint32* p)
{
    p[1] = 1;
    p[3] = 1;
    p[0] = 0;
    p[2] = 0;
    p[5] = 1;
    p[4] = 0;
    p[7] = 1;
    p[6] = 0;
    p[0] = 0x1c;
    p[1] = 4;
}

// @ 0x011e4c30
void __cdecl rw_section_init_table0c(uint32* p)
{
    p[1] = 1;
    p[3] = 1;
    p[0] = 0;
    p[2] = 0;
    p[5] = 1;
    p[4] = 0;
    p[7] = 1;
    p[6] = 0;
    p[0] = 0xc;
    p[1] = 4;
}

// @ 0x011e4c80
void __cdecl rw_section_pad_advance(void* section, void* ctx)
{
    uint32 v = *(uint32*)((char*)ctx + 0x28);
    *(uint32*)((char*)section + 8) = 0;
    v = (v + 3u & 0xfffffffc) + 0xc;
    *(uint32*)((char*)ctx + 0x28) = v;
}

// @ 0x011e4cd0
void __cdecl rw_ArenaSectionAtoms_Refix(void** obj, uint32 param2, Arena* ar)
{
    uint32 block[3];
    block[0] = *(uint32*)*obj;
    block[1] = (uint32)obj[1];
    block[2] = (uint32)obj[2];
    if (ar->writeNoCtx == 0)
        ar->writeCtx((void*)*(uint32*)obj, block, 0xc, 0, ar->writeCtxArg);
    else
        ar->writeNoCtx(block, block, 0xc, 0);
    ar->serialPos += 0xc;
    uint32 u = ar->align;
    ar->pos = ar->pos;
    if (u < 2)
        u = 1;
    ar->align = u;
    ar->pos += 0xc;
    if (obj[2] != 0)
        obj[2] = (void*)(uint32)((Arena*)*(void**)((char*)ar + 0x78))->IdToObject(obj[2]);
    (void)param2;
}

// @ 0x011e4d70
uint32 __cdecl rw_ArenaSectionAtoms_Fixup(void* section, Arena* ar)
{
    void* p = *(void**)((char*)section + 8);
    if (p != 0) {
        p = (void*)(uint32)((Arena*)*(void**)((char*)ar + 0x78))->IdToObject(p);
        *(void**)((char*)section + 8) = p;
        ((AtomTable*)p)->Fixup(ar);
        *(void**)((char*)ar + 4) = *(void**)((char*)section + 8);
    }
    return 1;
}

struct AtomsSection {
    uint8  pad00[8];
    void*  atomTable;               // +0x08

    void SetAtomTable(void* table, Arena* arena);   // 0x011e4db0
};

// @ 0x011e4db0
void AtomsSection::SetAtomTable(void* table, Arena* arena)
{
    atomTable = table;
    if (table != 0)
        atomTable = (void*)(uint32)arena->ObjectToId(table);
}

// @ 0x011e4dd0
void __cdecl rw_section_init_combined(uint32* p, uint32 n1, uint32, uint32 n2)
{
    p[1] = 1;
    p[3] = 1;
    p[0] = 0;
    p[2] = 0;
    p[5] = 1;
    p[4] = 0;
    p[7] = 1;
    p[6] = 0;
    p[0] = n1 * 4 + n2 * 8 + 0x88;
    p[1] = 4;
}

// ------------------------------------------------------------------ sections init
// @ 0x011e4e70
void* __cdecl rw_ArenaSectionsInitialize(int* a, int nTypes, int typeIds, int nExt, int* ext)
{
    int iVar1 = (int)FUN_011e4910(&a, 4);
    uint32 local_20[4];
    local_20[0] = (uint32)(iVar1 + 0x1c);
    local_20[1] = 0;
    local_20[2] = 0;
    local_20[3] = 0;
    int iVar2 = (int)rw_ArenaSectionTypes_Initialize((void**)local_20, (uint32)nTypes + 5);
    **(int**)(iVar1 + 8) = iVar2;
    if (nTypes != 0) {
        int iVar5 = 0x14;
        int cnt = nTypes;
        do {
            uint32 u = FUN_011e21b0(*(uint32*)(typeIds - 0x14 + iVar5));
            *(uint32*)(*(int*)(iVar2 + 8) + iVar5) = u;
            iVar5 += 4;
        } while (--cnt != 0);
    }
    local_20[0] = (uint32)(iVar2 + nTypes * 4 + 0xc);
    local_20[1] = 0;
    local_20[2] = 0;
    local_20[3] = 0;
    int iVar4 = (int)rw_ArenaSectionExternalArenas_Initialize((void**)local_20, (uint32)nExt + 3);
    *(int*)(*(int*)(iVar1 + 8) + 4) = iVar4;
    if (nExt != 0) {
        int* slot = (int*)(iVar4 + 0x18);
        int  cnt = nExt;
        int  off = 0xc;
        do {
            *(uint32*)((char*)ext + *(int*)(iVar4 + 8) + off - 0xc) = *(uint32*)(*ext + 0x30);
            *slot = *ext;
            ++slot;
            ++ext;
            off += 4;
        } while (--cnt != 0);
    }
    local_20[1] = 4;
    uint32* puVar6 = (uint32*)((nExt + 3) * 8 + 0xc + iVar4);
    puVar6[0] = FUN_011e21b0(0x10007);
    puVar6[1] = 0;
    puVar6[6] = 0;
    puVar6[4] = 0;
    puVar6[5] = 0;
    puVar6[2] = 0;
    puVar6[3] = 0;
    *(uint32**)(*(int*)(iVar1 + 8) + 8) = puVar6;
    local_20[1] = 4;
    puVar6[7] = FUN_011e21b0(0x10008);
    puVar6[8] = 0;
    puVar6[9] = 0;
    *(uint32**)(*(int*)(iVar1 + 8) + 0xc) = puVar6 + 7;
    return (void*)iVar1;
}

// ------------------------------------------------------------------ size calculators
// @ 0x011e5000
uint32 __cdecl rw_sections_size(uint32 n1, uint32 n2)
{
    return n1 * 4 + n2 * 8 + 0x5c;
}

// @ 0x011e5090
uint32 __cdecl rw_sections_size_from(void* manifest)
{
    uint32* a = *(uint32**)((char*)manifest + 8);
    return rw_sections_size(*(uint32*)(*a + 4), *(uint32*)(a[1] + 4));
}

// @ 0x011e50b0
void* __cdecl rw_NullSections_Initialize(int* param)
{
    int iVar1 = *param;
    uint32 local_10[4];
    local_10[1] = 0;
    local_10[2] = 0;
    local_10[3] = 0;
    local_10[0] = (uint32)iVar1;
    FUN_011e4910(local_10, 4);
    local_10[0] = (uint32)(iVar1 + 0x1c);
    local_10[1] = 0;
    local_10[2] = 0;
    local_10[3] = 0;
    rw_ArenaSectionTypes_Initialize((void**)local_10, 5);
    local_10[0] = (uint32)(iVar1 + 0x3c);
    local_10[1] = 0;
    local_10[2] = 0;
    local_10[3] = 0;
    rw_ArenaSectionExternalArenas_Initialize((void**)local_10, 3);
    *(uint32*)(iVar1 + 0x60) = FUN_011e21b0(0x10007);
    *(uint32*)(iVar1 + 0x64) = 0;
    *(uint32*)(iVar1 + 0x78) = 0;
    *(uint32*)(iVar1 + 0x70) = 0;
    *(uint32*)(iVar1 + 0x74) = 0;
    *(uint32*)(iVar1 + 0x68) = 0;
    *(uint32*)(iVar1 + 0x6c) = 0;
    *(uint32*)(iVar1 + 0x7c) = FUN_011e21b0(0x10008);
    *(uint32*)(iVar1 + 0x80) = 0;
    *(uint32*)(iVar1 + 0x84) = 0;
    *(uint32*)(iVar1 + 0xc) = (uint32)(iVar1 + 0x1c);
    *(uint32*)(iVar1 + 0x14) = (uint32)(iVar1 + 0x60);
    *(uint32*)(iVar1 + 0x10) = (uint32)(iVar1 + 0x3c);
    *(uint32*)(iVar1 + 0x18) = (uint32)(iVar1 + 0x7c);
    return (void*)iVar1;
}

// ------------------------------------------------------------------ arena walk
// @ 0x011e5170
void __cdecl rw_section_manifest_walk(void** section, uint32 param2, Arena* ar)
{
    uint32 block[3];
    block[0] = *(uint32*)*section;
    block[1] = (uint32)section[1];
    block[2] = (uint32)((int)section[2] - (int)section);
    if (ar->writeNoCtx == 0)
        ar->writeCtx((void*)*(uint32*)section, block, 0xc, 0, ar->writeCtxArg);
    else
        ar->writeNoCtx(block, block, 0xc, 0);
    ar->serialPos += 0xc;
    uint32 u = ar->align;
    ar->pos = ar->pos;
    if (u < 2)
        u = 1;
    ar->align = u;
    ar->pos += 0xc;
    uint32 i = 0;
    if (section[1] != 0) {
        do {
            uint32 v = (uint32)(*(int*)((char*)section[2] + i * 4) - (int)section);
            if (ar->writeNoCtx == 0)
                ar->writeCtx((void*)*(uint32*)((char*)section + 8), &v, 4, 0, ar->writeCtxArg);
            else
                ar->writeNoCtx(&v, &v, 4, 0);
            ar->serialPos += 4;
            uint32 w = ar->align;
            ar->pos = ar->pos;
            if (w < 2)
                w = 1;
            ar->align = w;
            ar->pos += 4;
            ++i;
        } while (i < (uint32)section[1]);
    }
    i = 0;
    if (section[1] != 0) {
        do {
            void** pi = *(void***)((char*)section[2] + i * 4);
            (*(void(__cdecl**)(void**, uint32, Arena*))(*(uint32*)pi + 8))(pi, param2, ar);
            ++i;
        } while (i < (uint32)section[1]);
    }
}

// @ 0x011e52b0
uint32 __cdecl rw_ArenaSectionManifest_Fixup(int section, uint32 param2)
{
    int* piVar1;
    uint32 i = 0;
    *(int*)(section + 8) = *(int*)(section + 8) + section;
    if (*(int*)(section + 4) != 0) {
        do {
            *(int*)(*(int*)(section + 8) + i * 4) = *(int*)(*(int*)(section + 8) + i * 4) + section;
            piVar1 = *(int**)(*(int*)(section + 8) + i * 4);
            int iVar2 = (int)FUN_011e21b0((uint32)*piVar1);
            (*(void(__cdecl**)(int*, uint32))(iVar2 + 0xc))(piVar1, param2);
            *piVar1 = iVar2;
            ++i;
        } while (i < *(uint32*)(section + 4));
    }
    return 1;
}

// @ 0x011e5310
void __cdecl rw_ArenaSectionTypes_Fixup(void** section, uint32 param2, Arena* ar)
{
    uint32 block[3];
    block[0] = *(uint32*)*section;
    block[1] = (uint32)section[1];
    block[2] = (uint32)((int)section[2] - (int)section);
    if (ar->writeNoCtx == 0)
        ar->writeCtx((void*)*(uint32*)section, block, 0xc, 0, ar->writeCtxArg);
    else
        ar->writeNoCtx(block, block, 0xc, 0);
    ar->serialPos += 0xc;
    uint32 u = ar->align;
    ar->pos = ar->pos;
    if (u < 2)
        u = 1;
    ar->align = u;
    ar->pos += 0xc;
    uint32 i = 0;
    if (section[1] != 0) {
        do {
            uint32 v = 0;
            void** p = *(void***)((char*)section[2] + i * 4);
            if (p != 0)
                v = *(uint32*)p;
            if (ar->writeNoCtx == 0)
                ar->writeCtx((void*)*(uint32*)((char*)section + 8), &v, 4, 0, ar->writeCtxArg);
            else
                ar->writeNoCtx(&v, &v, 4, 0);
            ar->serialPos += 4;
            uint32 w = ar->align;
            ar->pos = ar->pos;
            if (w < 2)
                w = 1;
            ar->align = w;
            ar->pos += 4;
            ++i;
        } while (i < (uint32)section[1]);
    }
    (void)param2;
}

// @ 0x011e54a0
void __cdecl rw_ArenaSectionExternalArenas_ser(void** section, uint32 param2, Arena* ar)
{
    uint32 block[3];
    block[0] = *(uint32*)*section;
    block[1] = (uint32)section[1];
    block[2] = (uint32)((int)section[2] - (int)section);
    if (ar->writeNoCtx == 0)
        ar->writeCtx((void*)*(uint32*)section, block, 0xc, 0, ar->writeCtxArg);
    else
        ar->writeNoCtx(block, block, 0xc, 0);
    ar->serialPos += 0xc;
    uint32 u = ar->align;
    ar->pos = ar->pos;
    if (u < 2)
        u = 1;
    ar->align = u;
    ar->pos += 0xc;
    uint32 i = 0;
    if (section[1] != 0) {
        void** slot = section + 3;
        do {
            uint32 v = *(uint32*)((char*)(*slot) + 0x1c);
            if (ar->writeNoCtx == 0)
                ar->writeCtx((void*)*slot, &v, 4, 0, ar->writeCtxArg);
            else
                ar->writeNoCtx(&v, &v, 4, 0);
            ar->serialPos += 4;
            uint32 w = ar->align;
            ar->pos = ar->pos;
            if (w < 2)
                w = 1;
            ar->align = w;
            ar->pos += 4;
            ++i;
            ++slot;
        } while (i < (uint32)section[1]);
    }
    uint32 sz = (uint32)section[1] * 4;
    if (ar->writeNoCtx == 0)
        ar->writeCtx((void*)ar->writeCtxArg, 0, 0, sz, ar->writeCtxArg);
    else
        ar->writeNoCtx((void*)ar->align, 0, 0, sz);
    ar->serialPos += sz;
    uint32 x = ar->align;
    ar->pos = ar->pos;
    if (x < 2)
        x = 1;
    ar->align = x;
    ar->pos += sz;
    (void)param2;
}

// @ 0x011e5610
uint32 __cdecl rw_ArenaSectionAtoms_serialize(void** section, int ar)
{
    uint32* puVar6 = (uint32*)(*(int*)((char*)section + 8) + (int)section);
    *(uint32**)((char*)section + 8) = puVar6;
    *puVar6 = *(uint32*)(*(int*)(ar + 0x78) + 0x30);
    *(uint32*)((char*)section + 0xc) = *(uint32*)((char*)ar + 0x78);
    uint32 vmgr = 0x0140a578;
    ArenaMgrDataFn dataFn = *(ArenaMgrDataFn*)&g_arenaMgrData;
    int iVar3 = *(int*)(dataFn(&vmgr) + 8);
    *(uint32*)(*(int*)((char*)section + 8) + 4) = *(uint32*)(iVar3 + 0x30);
    *(uint32*)((char*)section + 0x10) = (uint32)iVar3;
    int iVar4 = (int)FUN_011e22b0((void*)ar);
    int off = *(int*)(*(int*)((char*)ar + 0x78) + 0x34);
    *(uint32*)(*(int*)((char*)section + 8) + 8) =
        (uint32)(*(int*)(iVar4 + 0x10 + off) + iVar4 + off);
    *(uint32*)((char*)section + 0x14) = *(uint32*)((char*)ar + 0x78);
    if (3 < *(uint32*)((char*)section + 4)) {
        uint32* pi = (uint32*)((char*)section + 0x18);
        uint32  i = 3;
        do {
            int v = (int)FUN_011e3e10(*pi);
            if (v == 0)
                *(uint32*)(*(int*)((char*)section + 8) + i * 4) = 0;
            else
                *(uint32*)(*(int*)((char*)section + 8) + i * 4) = *(uint32*)(v + 0x30);
            *pi = (uint32)v;
            ++i;
            ++pi;
        } while (i < *(uint32*)((char*)section + 4));
    }
    return 1;
}

// @ 0x011e56d0
uint32 __cdecl rw_ArenaSectionAtoms_fixup(void* ar, uint32* section)
{
    uint32* hdr = *(uint32**)((char*)section + 0x10);
    hdr = (uint32*)((char*)hdr + *(uint32*)((char*)ar + 0x78));
    *(uint32**)((char*)section + 0x10) = hdr;
    uint32* ar2 = (uint32*)((char*)hdr + *(uint32*)((char*)section + 0x14));
    ar2 = (uint32*)((char*)ar2 + *(uint32*)((char*)ar + 0x78));
    *(uint32**)((char*)section + 0x14) = ar2;
    if (*(uint32*)((char*)section + 0x18) > 0) {
        uint32 i = 0;
        uint32 off = 0;
        do {
            uint32* e = (uint32*)(*(int*)((char*)section + 0x14) + i * 8);
            uint32   a = e[0];
            uint32   b = e[1];
            void*    o = (void*)(uint32)((Arena*)*(void**)((char*)ar + 0x78))->IdToObject((void*)a);
            *(uint32*)((char*)hdr + off) = (uint32)o + b;
            ++i;
            off += 0x18;
        } while (i < *(uint32*)((char*)section + 0x18));
    }
    uint32 e2 = (uint32)FUN_011e22a0((void*)ar);
    *(uint32*)(*(int*)(e2 + 8) + 8) = *(uint32*)((char*)section + 0x10);
    return 1;
}

// @ 0x011e5750
void __cdecl rw_register_section_fixups(void)
{
    int r;
    r = (int)FUN_011e22c0(0x10004);
    *(void**)(r + 0xc) = (void*)&rw_ArenaSectionManifest_Fixup;
    r = (int)FUN_011e22c0(0x10005);
    *(void**)(r + 0xc) = (void*)&rw_ArenaSectionTypes_Fixup;
    r = (int)FUN_011e22c0(0x10006);
    *(void**)(r + 0xc) = (void*)&rw_ArenaSectionAtoms_serialize;
    r = (int)FUN_011e22c0(0x10007);
    *(void**)(r + 0xc) = (void*)&rw_ArenaSectionExternalArenas_ser;
    r = (int)FUN_011e22c0(0x10008);
    *(void**)(r + 0xc) = (void*)&rw_ArenaSectionAtoms_fixup;
}

// @ 0x011e57b0
void __cdecl rw_register_section_writers(void)
{
    int r;
    r = (int)FUN_011e22c0(0x10004);
    *(void**)(r + 4) = (void*)&rw_section_manifest_walk;
    *(void**)(r + 8) = (void*)&rw_ArenaSectionAtoms_serialize;
    r = (int)FUN_011e22c0(0x10005);
    *(void**)(r + 4) = (void*)&rw_section_types_advance;
    *(void**)(r + 8) = (void*)&rw_ArenaSectionTypes_Fixup;
    r = (int)FUN_011e22c0(0x10006);
    *(void**)(r + 4) = (void*)&rw_section_ext_advance;
    *(void**)(r + 8) = (void*)&rw_ArenaSectionExternalArenas_ser;
    r = (int)FUN_011e22c0(0x10007);
    *(void**)(r + 4) = (void*)&rw_section_init_table1c;
    *(void**)(r + 8) = (void*)&rw_ArenaSectionAtoms_fixup;
    r = (int)FUN_011e22c0(0x10008);
    *(void**)(r + 4) = (void*)&rw_section_pad_advance;
    *(void**)(r + 8) = (void*)&rw_ArenaSectionAtoms_Refix;
}

// ------------------------------------------------------------------ atom singleton
// @ 0x011e5870
void* AtomSingleton::Init()
{
    if ((g_atomInitFlag & 1) == 0) {
        g_atomInitFlag |= 1;
        ((VtblHolder*)g_atomHeadStorage)->SetVtbl();
        FUN_011e07ef((void*)&FUN_013cb3f0);
    }
    if (g_atomListHead == 0)
        g_atomListHead = g_atomHeadStorage;
    return this;
}

// @ 0x011e58c0
void* __cdecl rw_atom_singleton_get(void)
{
    if ((g_atomInitFlag2 & 1) == 0) {
        g_atomInitFlag2 |= 1;
        ((AtomSingleton*)((char*)&g_atomInitFlag2 - 4))->Init();
    }
    return g_atomListHead;
}

// @ 0x011e5900
void ArenaPathHolder::Split(const char* path)
{
    FUN_011ea8f0(base, baseLen);
    FUN_011ea8f0(pieces, count * 8);
    FUN_011e8b20((char*)base, path);
    int  i = 0;
    char* cur = (char*)base;
    while (cur != 0) {
        char* nxt = FUN_011e8c60(cur, 0x3b);
        if (nxt != 0) {
            char c = nxt[-1];
            *nxt = 0;
            if (c == '/' || c == '\\')
                nxt[-1] = 0;
            ++nxt;
        }
        *(char**)((char*)pieces + i * 8) = cur;
        *(uint32*)((char*)pieces + i * 8 + 4) = FUN_011e5ff0(cur, 0);
        ++i;
        cur = nxt;
    }
    char* last = *(char**)((char*)pieces + (i - 1) * 8);
    char* end  = last + FUN_011e8c40(last);
    if (end[-1] == '/' || end[-1] == '\\')
        end[-1] = 0;
}

// @ 0x011e59b0
void __cdecl rw_stream_push(int a, int b)
{
    void* p = FUN_011e6d20(0x130);
    if (p == 0) {
        p = 0;
    } else {
        p = FUN_011e5e90((void*)a, (void*)b);
    }
    uint32* head = (uint32*)g_streamListHead;
    uint32* slot = head + 1;
    uint32* prev = (uint32*)*slot;
    *(uint32*)p = 0;
    *slot = (uint32)p;
    head[2] = head[2] + 1;
    if (prev == 0)
        *head = (uint32)p;
    else
        *prev = (uint32)p;
}
