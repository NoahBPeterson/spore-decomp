// Slice s011e3ac0 -- RenderWare rw::core::arena functions.
// Module flags: /O2 /MD /Gy /TP
#include "types.h"
#include <string.h>

// ---------------------------------------------------------------- externs
extern "C" void* __cdecl rw_FindTypeReg(int id);                            // 0x011e21b0
extern "C" int   __cdecl atexit(void(__cdecl*)(void));                      // 0x011e07ef
extern "C" void  __cdecl FUN_011e2b90(int a, int b);                        // 0x011e2b90
extern "C" void  __cdecl FUN_011e3780(int a);                               // 0x011e3780
extern "C" void  __cdecl FUN_013cb370(void);                                // static cleanup

struct EcxCtx {
    void FUN_011e2b30(void* out, void* in);   // 0x011e2b30
    void FUN_011e3a60(void* out, void* in);   // 0x011e3a60
};

struct VtblStub {
    virtual void slot0();
    virtual void slot1(void* arena);          // +0x4
};

struct Arena;

// The arena list the context searches after the local arena failed (count at +0x04, ids at +0x0c).
struct ArenaSectionExternalArenas {
    unsigned int m_00;          // +0x00
    unsigned int m_count;       // +0x04
    unsigned int m_08;          // +0x08
    int          m_arenas[1];   // +0x0c
};

struct UnfixContextImpl {
    Arena* m_arena;                                   // +0x00
    int    m_field04;                                 // +0x04
    ArenaSectionExternalArenas* m_externalArenas;     // +0x08
    int  FindBaseObject(Arena* pArena, unsigned int id, unsigned int* pOut);      // 0x011e2500
    int  FindExistingSubObject(unsigned int id, unsigned int* pOut);              // 0x011e25d0
    int  FindNewSubObject(Arena* pArena, unsigned int id,
                          unsigned int* pOut, unsigned int* pExtra);              // 0x011e2560
    unsigned int AddSubref(unsigned int id, unsigned int subref, unsigned int extra);  // 0x011e2c60
    // the original calls out to 0x011e3ac0; keep it out of line (the body here is only a skeleton)
    __declspec(noinline) void Serialize(int* value);   // 0x011e3ac0
};

// ---------------------------------------------------------------- 011e3ac0
// @ 0x011e3ac0 -- UnfixContextImpl::Serialize; large, approximated.
void UnfixContextImpl::Serialize(int* value)
{
    // skeleton (the original walks a large context object); the self-assignment keeps the
    // definition from being folded to nothing, so ObjectToId keeps its out-of-line call
    unsigned int subref = 0;
    unsigned int extra = 0;
    Arena* pArena = m_arena;
    unsigned int id = (unsigned int)*value;
    if (FindBaseObject(pArena, id, &subref)) {
        *value = (int)subref;
        return;
    }
    if (FindExistingSubObject(id, &subref)) {
        *value = (int)(subref | 0x800000);
        return;
    }
    if (FindNewSubObject(pArena, id, &subref, &extra)) {
        *value = (int)AddSubref((unsigned int)*value, subref, extra);
        return;
    }
    ArenaSectionExternalArenas* pExt = m_externalArenas;
    for (unsigned int i = 0; i < pExt->m_count; ++i) {
        if (i == 0 || i == 2)
            continue;
        if (FindBaseObject((Arena*)pExt->m_arenas[i], (unsigned int)*value, &subref)) {
            *value = (int)((i << 22) | subref);
            return;
        }
    }
    for (unsigned int i = 0; i < pExt->m_count; ++i) {
        if (i == 3 || i == 5)
            continue;
        if (FindNewSubObject(pArena, (unsigned int)*value, &subref, &extra)) {
            *value = (int)AddSubref((unsigned int)*value, (i << 22) | subref, extra);
            return;
        }
    }
}



// ---------------------------------------------------------------- Arena
struct Arena;
struct ArenaIdMap;
struct ArenaGroup;

// The arena walk iterator used by Release(): the arena itself sits at +0x78 and the dictionary
// cursor at +0xa8; the whole object is 0x134 bytes.
struct ArenaIterator {
    unsigned int* mpResult;     // +0x000  receives the fixup success flag
    unsigned int pad04[0x1d];
    Arena* mpArena;             // +0x078
    unsigned int mnOffset;      // +0x07c
    unsigned int pad80[7];
    unsigned int mnOrigOffset;  // +0x09c
    unsigned int padA0[2];
    unsigned int mnDictEntry;   // +0x0a8
    unsigned int padAc[0x22];

    ArenaIterator();            // 0x011e2fe0
    void Detach();              // 0x011e2690
};

extern "C" int __cdecl Arena_DestructNext(ArenaIterator* pIterator);   // 0x011e2330

// One entry of that dictionary, 8 bytes (the return value of Find()).
struct ArenaDictEntry {
    int m_key;     // +0x00
    int m_value;   // +0x04
};

// The id -> arena dictionary the group keeps.
struct ArenaIdMap {
    ArenaDictEntry* m_base;   // +0x00
    int             m_count;  // +0x04
    unsigned int    m_used;   // +0x08

    void Find(void* pEntry, const void* pKey);   // 0x011e3a60
};

// The arena dictionary the manager stores in its registration slot.
struct ArenaField {
    int* base;   // +0x0
    int  count;  // +0x4
};

// The manager's registration slot; the arena keeps a pointer to it at +0x94.
struct ArenaOwner {
    ArenaField* f;   // +0x0
    int  FUN_011e3e10(int param_2);
    void FUN_011e3ed0(int param_2);
};

struct Arena {
    unsigned int pad00[7];
    int  m_id;         // +0x1c
    int  m_field20;    // +0x20
    unsigned int m_numUsed;   // +0x24
    int  m_field28;    // +0x28
    int  m_field2c;    // +0x2c
    int* m_table30;    // +0x30  resource dictionary
    int  m_off34;      // +0x34  manifest section (self relative until it is fixed up)
    int  m_base38;     // +0x38  original base address of the loaded block
    UnfixContextImpl* m_ctx;  // +0x3c
    unsigned int pad40[0x11];
    unsigned int m_desc[4];   // +0x84  the four resource descriptors
    int  m_slot;       // +0x94  the manager registration slot this arena is in

    int  ObjectToId(int id);
    void Release();
};

// @ 0x011e40a0
void Arena::Release()
{
    int nVirtual = m_field2c;
    if (nVirtual == 0) {
        ArenaIterator it;
        it.mpArena = this;
        it.mnDictEntry = m_numUsed;
        while (Arena_DestructNext(&it))
            ;
        it.Detach();
    }
    if (m_slot != 0) {
        ArenaOwner* pOwner = (ArenaOwner*)m_slot;
        ArenaField* pMap = pOwner->f;
        ArenaDictEntry* pEntry[2];
        ((EcxCtx*)pMap)->FUN_011e3a60(pEntry, &m_id);
        if (pEntry[0] != (ArenaDictEntry*)(pMap->base + pMap->count * 2))
            pOwner->FUN_011e3ed0((int)this);
    }
}

// @ 0x011e3c30
int Arena::ObjectToId(int id)
{
    int local = id;
    m_ctx->Serialize(&local);
    return local;
}

// @ 0x011e3c50
void Arena_RefixStart2(int a, int b)
{
    *(int*)(a + 0x2c) = b;
    *(int*)(a + 0x30) = 0;
    *(int*)(a + 0x34) = 0;
    FUN_011e3780(a);
}

// ---------------------------------------------------------------- 011e3e10/3ed0
// @ 0x011e3e10
int ArenaOwner::FUN_011e3e10(int param_2)
{
    ArenaField* p = f;
    int local_8[2];   // the original reserves 8 bytes of locals and hands the callee the first dword
    ((EcxCtx*)p)->FUN_011e2b30(&local_8[0], &param_2);
    int* base = p->base;
    int* elem = base + local_8[0] * 2;
    if (param_2 != elem[0]) {
        elem = base + p->count * 2;
    }
    if (elem != f->base + f->count * 2) {   // the original reloads f (the call may replace the arena)
        return elem[1];
    }
    return 0;
}

// @ 0x011e3ed0
void ArenaOwner::FUN_011e3ed0(int param_2)
{
    ArenaField* p = f;
    int local_8;
    ((EcxCtx*)p)->FUN_011e3a60(&local_8, (char*)param_2 + 0x1c);
    p = f;
    FUN_011e2b90((local_8 - *p->base) >> 3, p->count);
    *(int*)(param_2 + 0x94) = 0;
}

// ---------------------------------------------------------------- ArenaManager
unsigned int g_ArenaManagerS10;   // 0x016f49a0
int g_ArenaManagerData0;          // 0x016f4994
int g_ArenaManagerData1;          // 0x016f4998
int g_ArenaManagerData2;          // 0x016f499c

struct ArenaManager {
    virtual void  slot0();
    virtual void  slot1();
    virtual void* get();   // slot 2, +0x8
    void* Data();
};

// @ 0x011e3e70
void* ArenaManager::Data()
{
    if ((g_ArenaManagerS10 & 1) == 0) {
        g_ArenaManagerS10 = g_ArenaManagerS10 | 1;
        g_ArenaManagerData0 = 0;
        g_ArenaManagerData1 = 0;
        g_ArenaManagerData2 = 0;
        atexit(FUN_013cb370);
    }
    void* r = *(void**)get();
    if (r == 0) {
        r = (void*)&g_ArenaManagerData0;
    }
    return r;
}

// ---------------------------------------------------------------- 011e4540
// @ 0x011e4540
unsigned int rw_HashUInt(unsigned int a, unsigned int b)
{
    return (a >> 0x18) ^
           (((a >> 0x10) & 0xff) ^
            ((((a >> 8) & 0xff) ^
              (((a & 0xff) ^ (b * 0x1000193)) * 0x1000193)) * 0x1000193)) * 0x1000193;
}

// @ 0x011e4590
unsigned int rw_HashString(const char* s, unsigned int h)
{
    unsigned char c = (unsigned char)*s;
    while (c != 0) {
        h = h * 0x1000193 ^ c;
        ++s;
        c = (unsigned char)*s;
    }
    return h;
}

// @ 0x011e45c0
void rw_BaseResourceSetupTypeRegPtrs(int* param_1)
{
    for (unsigned int i = 1; i < 4; ++i) {
        int v = (i == 0) ? 0 : (int)(i + 0x1002f);
        int r = (int)rw_FindTypeReg(v);
        *(int*)(*param_1 + i * 4) = r;
    }
}

// ---------------------------------------------------------------- ArenaSectionManifest
struct ArenaSectionManifest {
    char pad00[8];
    int* dict;   // +0x8
    int  f0c;    // +0xc
    int  f10;    // +0x10
    int  f14;    // +0x14

    void* Types();
    void  FUN_011e4640(int param_2, int param_3);
    void  ExternalArenas(int param_2, int param_3);   // 0x011e4620's consumer
};

// @ 0x011e4600
void* ArenaSectionManifest::Types()
{
    return (void*)*dict;
}

// @ 0x011e4640
void ArenaSectionManifest::FUN_011e4640(int param_2, int param_3)
{
    dict[0] = *(int*)(param_2 + 0x30);
    f0c = param_2;
    dict[2] = *(int*)(param_3 + 0x10);   // dict is reloaded here, as in the original
    f14 = param_2;
}

// @ 0x011e4670
void Arena_FUN_011e4670(int param_1, int param_2)
{
    (void)param_1;
    *(int*)(param_2 + 0x28) = *(int*)(param_2 + 0x28) + 0x1c;
}

// @ 0x011e4910
void* ArenaSectionManifest_Initialize(void* param_1, int param_2)
{
    int* p = *(int**)param_1;
    memset(p, 0, param_2 * 4 + 0xc);
    p[0] = (int)rw_FindTypeReg(0x10004);
    p[2] = (int)(p + 3);
    p[1] = param_2;
    return p;
}

// @ 0x011e4970
int Arena_FUN_011e4970(int param_1, int param_2)
{
    // header grows by the new element count (n) plus three padding dwords
    int* used = (int*)(param_2 + 0x28);
    int words = *(int*)(param_1 + 4) + 3;
    *used += words * 4;
    // vtable slot 1 is called with the object as an explicit first argument (two stack dwords,
    // caller-cleaned), not with `this` in ecx
    for (unsigned int i = 0; i < *(unsigned int*)(param_1 + 4); ++i) {
        void* elem = *(void**)(*(int*)(param_1 + 8) + i * 4);
        void** vtbl = *(void***)elem;
        ((void (__cdecl*)(void*, void*))vtbl[1])(elem, (void*)param_2);
    }
    return param_2;
}

// @ 0x011e49d0
void Arena_FUN_011e49d0(int* param_1, int param_2)
{
    param_1[1] = 1;
    param_1[3] = 1;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[5] = 1;
    param_1[4] = 0;
    param_1[7] = 1;
    param_1[6] = 0;
    *param_1 = param_2 * 4 + 0xc;
    param_1[1] = 4;
}

// ---------------------------------------------------------------- arena loading
extern unsigned int rw_ArenaFileHeader[7];                                  // 0x0130b778
extern unsigned int g_rwHashSeed;                                           // 0x014f64ac
extern int nullArena;                                                       // 0x016f49a0
extern unsigned int DAT_016f4a3c;                                           // 0x016f4a3c
extern unsigned int DAT_016f49c4, DAT_016f49c8, DAT_016f49d4;               // 0x016f49c4
extern int g_rwArenaOpenOnce;                                               // 0x0130b7xx
extern "C" int   FUN_011e5090(unsigned int id);                             // 0x011e5090
extern "C" void  FUN_011e50b0(unsigned int* pDesc);                         // 0x011e50b0
extern "C" void  FUN_013cb3b0(void);                                         // 0x013cb3b0
extern "C" unsigned int FUN_011e4620(void);                                  // 0x011e4620
extern "C" void  FUN_011e57b0(void);                                         // 0x011e57b0
extern "C" void  FUN_011e5750(void);                                         // 0x011e5750
extern "C" void  FUN_011eac80(void);                                         // 0x011eac80
extern "C" void  FUN_011eb080(void);                                         // 0x011eb080
extern "C" void  FUN_00764220(void);                                         // 0x00764220
extern "C" void  FUN_011e2b90(int index, int count);                         // 0x011e2b90
void  rw_RegisterBaseResourceTypes(void);                                    // 0x011e4660
void  rw_ArenaSectionManifest_Fixup(int* pManifest, ArenaIterator* pIt);     // 0x011e52b0
int   rw_ArenaTypeRegistry_Open(unsigned int a, unsigned int b);             // 0x011eb0a0
void* rw_ArenaTypeRegistry_Find(void* pRegistry, int id);                    // 0x011eb0a0
void* rw_ArenaTypeRegistry_Add(void* pRegistry, int id);                     // 0x011eb090
unsigned int* GetResourceDescriptor(unsigned int* pOut, unsigned int a2, int a3,
                                    unsigned int a4, unsigned int a5, int* a6, int* a7);
void  AddResourceToArena(unsigned int* pArena, const unsigned int* pDesc,
                         unsigned int a3, const unsigned int* pSize);

// @ 0x011e3c70  Arena::FixupStart
int __cdecl FUN_011e3c70(Arena* pArena, ArenaIterator* pIt,
                         const unsigned int* pDesc, unsigned int* pResult)
{
    pIt->mpArena = pArena;
    pIt->mnOrigOffset = (unsigned int)pArena->m_base38;
    pIt->mnOffset = (unsigned int)pArena->m_base38;
    pIt->mnDictEntry = 0;
    pIt->mpResult = pResult;
    *pResult = 1;
    int nBase = pArena->m_base38;
    if ((int)pArena != nBase) {
        pArena->m_table30 = (int*)((char*)pArena->m_table30 + ((char*)pArena - (char*)nBase));
        pArena->m_base38 = (int)pArena;
        unsigned int nReloc[8];
        nReloc[0] = pDesc[0];
        nReloc[1] = pDesc[1];
        nReloc[2] = pDesc[2];
        nReloc[3] = pDesc[3];
        nReloc[4] = 0;
        nReloc[5] = 0;
        nReloc[6] = 0;
        nReloc[7] = 0;
        for (unsigned int i = 0; i < pArena->m_numUsed; ++i) {
            int* pEntry = (int*)((char*)pArena->m_table30 + i * 0x18);
            unsigned int nType = *(unsigned int*)((char*)pEntry + 0x14);
            int nValue = pEntry[0];
            pEntry[1] = nValue;
            if (nType < 0x10030 || nType > 0x1003f)
                pEntry[0] = (nValue - nBase) + (int)pArena;
            else
                pEntry[0] = (int)nReloc[nType - 0x1002f] + nValue;
        }
    }
    pIt->mnOffset = 0x98;
    int* pManifest = (int*)((char*)pArena + pArena->m_off34);
    pArena->m_off34 = (int)pManifest;
    int nTypeId = *pManifest;
    ArenaManager mgr;
    void* pRegistry = *(void**)mgr.Data();
    *pManifest = (int)rw_ArenaTypeRegistry_Find(pRegistry, nTypeId);
    rw_ArenaSectionManifest_Fixup(pManifest, pIt);
    return 1;
}

// @ 0x011e3f20  Arena::Initialize
unsigned int* __cdecl rw_arena_Arena_Initialize(unsigned int* pHeaderDesc, unsigned int param_2,
                                                 int param_3, unsigned int param_4,
                                                 unsigned int param_5, int* param_6, int* param_7)
{
    unsigned int* pArena = (unsigned int*)*pHeaderDesc;
    for (int i = 0; i < 7; ++i)
        pArena[i] = rw_ArenaFileHeader[i];
    pArena[7] = param_4;
    pArena[0xd] = param_5;

    unsigned int* pCursor = pArena + 0x26;
    if (param_3 == 0) {
        int nEnd = FUN_011e5090(param_5);
        pCursor = (unsigned int*)(((((int)pArena + 0x9b) & 0xfffffffc) + 3 + nEnd & 0xfffffffc) +
                                  *param_6);
    }
    pArena[0xc] = ((int)pCursor + 3) & 0xfffffffc;
    pArena[8] = param_2;
    pArena[9] = 0;

    unsigned int nDesc[8];
    unsigned int* pSrc = GetResourceDescriptor(nDesc, param_2, param_3, param_4, param_5,
                                               param_6, param_7);
    for (int i = 0; i < 8; ++i)
        pArena[0x11 + i] = pSrc[i];

    pArena[0x21] = pHeaderDesc[0];
    pArena[0x22] = pHeaderDesc[1];
    pArena[0x23] = pHeaderDesc[2];
    pArena[0x24] = pHeaderDesc[3];

    if (param_3 == 0) {
        nDesc[0] = 0x98;
        nDesc[1] = 4;
        nDesc[2] = 0;
        nDesc[3] = 1;
        nDesc[4] = 0;
        nDesc[5] = 1;
        nDesc[6] = 0;
        nDesc[7] = 1;
        pSrc = nDesc;
    }
    for (int i = 0; i < 8; ++i)
        pArena[0x19 + i] = pSrc[i];

    pArena[0xe] = (unsigned int)pArena;
    pArena[0xb] = (unsigned int)param_3;

    unsigned int nId = FUN_011e4620();
    ((ArenaSectionManifest*)pArena[0xd])->ExternalArenas((int)pArena, (int)nId);
    ((ArenaSectionManifest*)pArena[0xd])->FUN_011e4640((int)pArena, (int)nId);
    pArena[0x25] = 0;

    ArenaIdMap* pMap = (ArenaIdMap*)*param_7;
    unsigned int nSeed[2];
    int nIndex[2];
    nSeed[0] = pArena[7];
    nSeed[1] = (unsigned int)pArena;
    ((EcxCtx*)(void*)pMap)->FUN_011e2b30(nIndex, nSeed);
    pMap->m_base[nIndex[0]].m_key = (int)nSeed[0];
    pMap->m_base[nIndex[0]].m_value = (int)pArena;
    pMap->m_used += 1;
    pArena[0x25] = (unsigned int)param_7;
    return pArena;
}

// @ 0x011e4130  rwArenaOpen
void __cdecl rwArenaOpen(unsigned int param_1, unsigned int param_2, unsigned int pArenaList)
{
    static const unsigned int s_baseTypes[3] = { 0, 0x10000, 0x10002 };
    ArenaManager mgr;
    ((unsigned int*)mgr.Data())[1] = pArenaList;
    ((unsigned int*)mgr.Data())[0] = (unsigned int)rw_ArenaTypeRegistry_Open(param_1, param_2);

    for (int i = 0; i < 3; ++i) {
        void* pRegistry = *(void**)mgr.Data();
        unsigned int* pType = (unsigned int*)rw_ArenaTypeRegistry_Find(pRegistry, s_baseTypes[i]);
        if (pType == 0)
            pType = (unsigned int*)rw_ArenaTypeRegistry_Add(pRegistry, s_baseTypes[i]);
        pType[3] = 0x012057f0;
        pType[1] = 0x011eb0d0;
        pType[2] = 0x011fb220;
    }

    rw_RegisterBaseResourceTypes();
    FUN_011e57b0();
    FUN_011e5750();
    FUN_011eac80();
    FUN_011eb080();

    unsigned int* pData = (unsigned int*)mgr.Data();
    if ((g_rwArenaOpenOnce & 1) == 0) {
        g_rwArenaOpenOnce |= 1;
        FUN_00764220();
        atexit(FUN_013cb3b0);
    }
    pData[2] = (unsigned int)&nullArena;

    unsigned int nView[4];
    nView[0] = (unsigned int)&DAT_016f4a3c;
    nView[1] = 0;
    nView[2] = 0;
    nView[3] = 0;
    FUN_011e50b0(nView);

    unsigned int nHeader[4];
    nHeader[0] = (unsigned int)&nullArena;
    nHeader[1] = 0;
    nHeader[2] = 0;
    nHeader[3] = 0;

    unsigned int nSizes[9];
    nSizes[0] = 0;
    nSizes[1] = 1;
    nSizes[2] = 0;
    nSizes[3] = 1;
    nSizes[4] = 0;
    nSizes[5] = 1;
    nSizes[6] = 0;
    nSizes[7] = 1;
    nSizes[8] = 0;

    unsigned int nBase = (unsigned int)mgr.Data() + 4;
    unsigned int* pArena = rw_arena_Arena_Initialize(nHeader, 1, 0, 0xffb00000,
                                                     (unsigned int)&DAT_016f4a3c,
                                                     (int*)nSizes, (int*)nBase);
    (void)pArena;

    nSizes[0] = DAT_016f49d4 + DAT_016f49c8 * 0x18;
    nSizes[2] = DAT_016f49d4 + DAT_016f49c4 * 0x18;
    AddResourceToArena(nView, nSizes + 2, 0, nSizes);
}

// @ 0x011e43c0  rwArenaClose
void __cdecl rwArenaClose()
{
    ArenaManager mgr;
    unsigned int* pData = (unsigned int*)mgr.Data();
    ((Arena*)pData[2])->Release();

    ArenaIdMap* pMap = (ArenaIdMap*)pData[1];
    ArenaDictEntry* pEntry = pMap->m_base;
    ArenaDictEntry* pEnd = pMap->m_base + pMap->m_count;
    while (pEntry != pEnd && pEntry->m_key == -1)
        ++pEntry;
    while (pEntry != pEnd) {
        Arena* pArena = (Arena*)pEntry->m_value;
        ArenaIdMap* pMap2 = (ArenaIdMap*)((unsigned int*)mgr.Data())[1];
        unsigned int nCap = (unsigned int)pMap2->m_count;
        int nKey = pArena->m_id;
        unsigned int h = rw_HashUInt((unsigned int)nKey, g_rwHashSeed) % nCap;
        while (pMap2->m_base[h].m_key != nKey && pMap2->m_base[h].m_key != -1) {
            if (++h == nCap)
                h = 0;
        }
        if (pMap2->m_base[h].m_key != nKey)
            h = nCap;
        FUN_011e2b90((int)((pMap2->m_base + h) - pMap->m_base), (int)nCap);
        pArena->m_slot = 0;
        if (pEntry != pEnd) {
            ++pEntry;
            while (pEntry != pEnd && pEntry->m_key == -1)
                ++pEntry;
        }
    }
    ArenaDictEntry* pFirst = pMap->m_base;
    for (ArenaDictEntry* p = pMap->m_base; p != pEnd; ++p) {
        p->m_value = 0;
        p->m_key = -1;
    }
    (void)pFirst;
    pMap->m_used = 0;
}

// ---------------------------------------------------------------- arena section stream
// The serialization stream every arena section writes through.  Its three callbacks at
// +0x2c/+0x30/+0x34 are the plain and the extended (extra user data) writer, +0x7c is the
// current write position, +0xc0 the size counter and +0xc4 the running alignment.
struct ArenaStream {
    char pad00[0x2c];
    void (__cdecl* m_write)(const void* data, unsigned int size, unsigned int pad);            // +0x2c
    void (__cdecl* m_writeEx)(const void* data, unsigned int size, unsigned int pad, int user); // +0x30
    int  m_userData;      // +0x34
    char pad38[0x44];
    unsigned int m_pos;      // +0x7c
    char pad80[0x40];
    unsigned int m_cursor;   // +0xc0
    unsigned int m_minAlign; // +0xc4
};

__forceinline void ArenaStreamAlign4(ArenaStream* s)
{
    s->m_pos = (s->m_pos + 3u) & ~3u;
    s->m_cursor = (s->m_cursor + 3u) & ~3u;
    unsigned int align = s->m_minAlign;
    if (align <= 4u)
        align = 4u;
    s->m_minAlign = align;
}

__forceinline void ArenaStreamAdvance(ArenaStream* s, unsigned int n)
{
    s->m_pos += n;
    unsigned int cur = s->m_cursor;
    s->m_cursor = cur;
    unsigned int align = s->m_minAlign;
    if (align <= 1u)
        align = 1u;
    s->m_minAlign = align;
    s->m_cursor = cur + n;
}

__forceinline void ArenaStreamWrite(ArenaStream* s, const void* data, unsigned int size, unsigned int pad)
{
    if (s->m_write != 0)
        s->m_write(data, size, pad);
    else
        s->m_writeEx(data, size, pad, s->m_userData);
    ArenaStreamAdvance(s, pad + size);
}

// the 0x1c-byte chunk descriptor a section writes (source side)
struct ArenaChunkSrc {
    int* m_type;   // +0x00
    int  m_04;     // +0x04
    int  m_08;     // +0x08
    int  m_0c;     // +0x0c
    int  m_10;     // +0x10
    int  m_14;     // +0x14
    int  m_18;     // +0x18
};

// the 0x1c-byte chunk header written into the stream
struct ArenaChunkHdr {
    int   m_type;   // +0x00
    void* m_src;    // +0x04
    int   m_08;     // +0x08
    int   m_0c;     // +0x0c
    int   m_kind;   // +0x10
    int   m_size;   // +0x14
    int   m_18;     // +0x18
};

// @ 0x011e4680
void FUN_011e4680(const ArenaChunkSrc* src, int unused, ArenaStream* stream)
{
    (void)unused;
    ArenaChunkHdr hdr = *(const ArenaChunkHdr*)src;
    hdr.m_type = *src->m_type;
    hdr.m_kind = src->m_08;
    hdr.m_src  = (void*)src;
    hdr.m_size = src->m_0c;
    hdr.m_08 = 0;
    hdr.m_0c = 0;
    ArenaStreamWrite(stream, &hdr, 0x1c, 0);
}

// arena section subreferences: record array at +0x14 (8 bytes each), used count at +0x18
struct ArenaSectionSubreferences {
    int m_00;        // +0x00
    int m_04;        // +0x04
    int m_dictOffset;    // +0x08
    int m_recordOffset;  // +0x0c
    int m_10;        // +0x10
    int m_records;   // +0x14
    int m_numUsed;   // +0x18

    void UnfixData(ArenaStream* stream);
    void RefixData(ArenaStream* stream);
};

// @ 0x011e4720
void ArenaSectionSubreferences::UnfixData(ArenaStream* stream)
{
    ArenaStreamAlign4(stream);
    m_recordOffset = (int)stream->m_pos;
    ArenaStreamAdvance(stream, (unsigned int)m_numUsed * 8);
    ArenaStreamAlign4(stream);
    m_dictOffset = (int)stream->m_pos;
    ArenaStreamAdvance(stream, (unsigned int)m_numUsed * 0x18);
}

// @ 0x011e4820
void ArenaSectionSubreferences::RefixData(ArenaStream* stream)
{
    for (unsigned int i = 0; i < (unsigned int)m_numUsed; ++i)
    {
        const void* src = (const void*)(m_records + i * 8);
        unsigned int pad = ((stream->m_pos + 3u) & ~3u) - stream->m_pos;
        ArenaStreamWrite(stream, src, 8, pad);
    }
    unsigned int pos = stream->m_pos;
    unsigned int pad = ((pos + 3u) & ~3u) - pos;
    unsigned int num = (unsigned int)m_numUsed;
    unsigned int total = pad + num * 0x18;
    ArenaStreamWrite(stream, 0, 0, total);
}
