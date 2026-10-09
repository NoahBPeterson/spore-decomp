// Slice s011e0560 -- OpenSSL (dso_win32.c), MSVC 2008 CRT internals, and the
// RenderWare "arena" module (rw::core::arena).  /O2, thiscall/__stdcall mix.
//
// Many entries below are prebuilt-library code (OpenSSL / MSVCR90) whose exact
// source is not present in this tree; those are marked PARTIAL.
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef int intptr_t;

// --- opaque callees / globals (masked relocations) -------------------------
extern void* CRYPTO_malloc(int n, const char* file, int line);
extern void  CRYPTO_free(void* p);
extern void  ERR_put_error(int lib, int func, int reason, const char* file, int line);
extern char  PTR_FUN_0140a578;
extern void* FUN_0140a57c;
extern int   ArenaSectionManifest_Types(void* manifest);
extern void* ArenaSectionManifest_ExternalArenas(void* manifest);
extern void* rw_ArenaTypeRegistry_Find(void* reg, int type);
extern void* rw_ArenaTypeRegistry_Add(void* reg, int type);
extern void* FUN_011e4620(void*);
extern void* FUN_011eb170(void*);
extern void* FUN_011eb160(void*);
extern void* FUN_011eb150(void*);
extern void* FUN_011eab70(void*);
extern void* FUN_011eb180(void*);
extern void  FUN_011eaaa0(void);
extern void  FUN_011eaad0(void);
extern void  FUN_011eaef0(void*);

// ---------------------------------------------------------------------------
// @ 0x011e0560  OpenSSL DSO_merge(dso, filespec1, filespec2)
// PARTIAL: only the two strdup arms are reproduced exactly.
// ---------------------------------------------------------------------------
char* DSO_merge(void* dso, char* a, char* b)
{
    char* p;
    char* out;
    if (a == 0) {
        if (b == 0)
            return 0;
        p = b + 1;
        while (*b++) ;
        out = (char*)CRYPTO_malloc((int)(b - p), ".\\crypto\\dso\\dso_win32.c", 0x232);
        if (out == 0)
            return 0;
        char* d = out;
        while ((*d++ = *p++) != 0) ;
        return out;
    }
    if (b == 0) {
        p = a + 1;
        while (*a++) ;
        out = (char*)CRYPTO_malloc((int)(a - p), ".\\crypto\\dso\\dso_win32.c", 0x227);
        if (out == 0)
            return 0;
        char* d = out;
        while ((*d++ = *p++) != 0) ;
        return out;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x011e07e6
// ---------------------------------------------------------------------------
void __cdecl crt_unlock_8(int n);
void crt_unlock_8_helper() { crt_unlock_8(8); }

// @ 0x011e0810  CRT float->long helper (ftol2).  PARTIAL.
long crt_ftol2_stub(double x) { return (long)x; }

// @ 0x011e0906  IAT thunk to floor().  PARTIAL.
double iat_floor(double x) { return x; }

// @ 0x011e0912 / @ 0x011e0b6d / @ 0x011e0bd2 / @ 0x011e0c47  CRT EH helpers.  PARTIAL.
void crt_eh_stub_0912(void* p, unsigned n, int flags) { (void)p; (void)n; (void)flags; }
void crt_eh_stub_0b6d(void* p, unsigned n, int sz) { (void)p; (void)n; (void)sz; }
void crt_eh_stub_0bd2(void* p, unsigned n, int sz) { (void)p; (void)n; (void)sz; }
void crt_eh_stub_0c47(void* p, unsigned n, int sz) { (void)p; (void)n; (void)sz; }

// @ 0x011e1368  CRT _amsg_exit table + atexit runner.  PARTIAL.
void crt_amsg_exit_stub(int code) { (void)code; }

// @ 0x011e1545
int crt_return_zero() { return 0; }

// @ 0x011e15de  CRT ___report_gsfailure.  PARTIAL.
void __cdecl crt_report_gsfailure_stub() { }

// ---------------------------------------------------------------------------
// RenderWare arena.
// ---------------------------------------------------------------------------
struct AlignInfo {
    uint32_t current;
    uint32_t alignment;
    void AlignUpTo(const AlignInfo* other);
    void Advance(const AlignInfo* other);
};

// @ 0x011e20a0
void AlignInfo::AlignUpTo(const AlignInfo* other)
{
    uint32_t cur = this->current;
    uint32_t a = other->alignment;
    if (a > 1)
        cur = (cur + a - 1) & ~(a - 1);
    this->current = cur;
    if (this->alignment < other->alignment)
        this->alignment = other->alignment;
}

// @ 0x011e20d0
void AlignInfo::Advance(const AlignInfo* other)
{
    uint32_t cur = this->current;
    uint32_t a = other->alignment;
    if (a > 1)
        cur = (cur + a - 1) & ~(a - 1);
    this->current = cur;
    if (this->alignment > other->alignment)
        this->alignment = this->alignment;
    else
        this->alignment = other->alignment;
    this->current = other->current + cur;
}

// @ 0x011e23b0
struct AlignInfo4 {
    AlignInfo e[4];
    void Advance4(const AlignInfo4* other);
};
void AlignInfo4::Advance4(const AlignInfo4* other)
{
    e[0].Advance(&other->e[0]);
    e[1].Advance(&other->e[1]);
    e[2].Advance(&other->e[2]);
    e[3].Advance(&other->e[3]);
}

// @ 0x011e2050
int g_16f2978;
void* __fastcall rw_addref_if_first(void* p)
{
    if (g_16f2978++ == 0)
        FUN_011eaaa0();
    return p;
}

// @ 0x011e2080
void rw_release_ref()
{
    if (--g_16f2978 == 0)
        FUN_011eaad0();
}

// @ 0x011e2160
int* g_16f4b7c;
int __stdcall rw_lookup_low(int unused, uint16_t idx)
{
    int* g = g_16f4b7c;
    return *(int*)(*(int*)((char*)g + 8) + (int)idx * 4) + *g;
}

// @ 0x011e2180
struct G2180 { void method(void* arg); };
void __stdcall rw_something_2180(int unused, void* arg)
{
    ((G2180*)0x16f4b7c)->method(arg);
}

// @ 0x011e21b0
struct ArenaManager { void* vftable; };
void* __fastcall rw_FindTypeReg(int type)
{
    ArenaManager mgr;
    mgr.vftable = &PTR_FUN_0140a578;
    void** data = (void**)((void*(__cdecl*)(ArenaManager*))FUN_0140a57c)(&mgr);
    mgr.vftable = &PTR_FUN_0140a578;
    return rw_ArenaTypeRegistry_Find(*data, type);
}

// @ 0x011e21e0
struct UnfixContext {
    void* m_arena;              // +0x00
    char pad[0x18 - 4];
    void* m_baseObjectPtr;      // +0x18
    void Serialize(void* param);
    int FindExistingSubObject(void* target, int* outIndex);
};
void UnfixContext::Serialize(void* param)
{
    int i = 0;
    int n = ArenaSectionManifest_Types(*(void**)((char*)this->m_arena + 0x34));
    while (**(int**)(n + 8) != *(int*)((char*)param + 0x14)) {
        ++i;
        n = ArenaSectionManifest_Types(*(void**)((char*)this->m_arena + 0x34));
    }
    this->m_baseObjectPtr = *(void**)param;
    n = ArenaSectionManifest_Types(*(void**)((char*)this->m_arena + 0x34));
    int entry = *(int*)(*(int*)(n + 8) + i * 4);
    ((void(__cdecl*)(void*, void*))*(void**)(entry + 4))(*(void**)param, this);
}

// @ 0x011e22a0 / @ 0x011e22b0
struct Manifest { void ExternalArenas(); void Slot4620(); };
struct ArenaObj { char pad[0x34]; Manifest* manifest; };
struct SelfArena { char pad[0x78]; ArenaObj* arena; };
void __fastcall rw_arena_manifest_22a0(void* p)
{
    SelfArena* s = (SelfArena*)p;
    s->arena->manifest->ExternalArenas();
}
void __fastcall rw_arena_manifest_22b0(void* p)
{
    SelfArena* s = (SelfArena*)p;
    s->arena->manifest->Slot4620();
}

// @ 0x011e22c0
void* __fastcall rw_ArenaTypeRegGetType(int type)
{
    ArenaManager mgr;
    mgr.vftable = &PTR_FUN_0140a578;
    void** data = (void**)((void*(__cdecl*)(ArenaManager*))FUN_0140a57c)(&mgr);
    void* reg = *data;
    void* r = rw_ArenaTypeRegistry_Find(reg, type);
    if (r == 0)
        r = rw_ArenaTypeRegistry_Add(reg, type);
    return r;
}

// @ 0x011e2330
int __stdcall rw_Arena_DestructNext(void* arena)
{
    for (;;) {
        int n = *(int*)((char*)arena + 0xa8);
        if (n == 0)
            return 0;
        *(int*)((char*)arena + 0xa8) = n - 1;
        int* entry = (int*)(*(int*)(*(int*)((char*)arena + 0x78) + 0x30) + (n - 1) * 0x18);
        int type = entry[5];
        if (type != 0) {
            ArenaManager mgr;
            mgr.vftable = &PTR_FUN_0140a578;
            void** data = (void**)((void*(__cdecl*)(ArenaManager*))FUN_0140a57c)(&mgr);
            mgr.vftable = &PTR_FUN_0140a578;
            int reg = (int)(intptr_t)rw_ArenaTypeRegistry_Find(*data, type);
            void (*dtor)(int) = *(void(**)(int))(reg + 0x10);
            if (dtor)
                dtor(*entry);
            return 1;
        }
    }
}

// @ 0x011e2500
int __stdcall UnfixContext_FindBaseObject(void* ctx, int id, int* outIndex)
{
    int* base = *(int**)((char*)ctx + 0x30);
    int* p = base;
    int* end = base + *(int*)((char*)ctx + 0x24) * 6;
    while (p != end) {
        if (*p == id) {
            *outIndex = (int)(((char*)p - (char*)base) / 0x18);
            return 1;
        }
        p += 6;
    }
    return 0;
}

// @ 0x011e2560
int __stdcall UnfixContext_FindNewSubObject(void* ctx, uint32_t addr, int* outIndex, uint32_t* outOffset)
{
    unsigned* base = *(unsigned**)((char*)ctx + 0x30);
    unsigned* p = base;
    unsigned* end = base + *(int*)((char*)ctx + 0x24) * 6;
    while (p != end) {
        unsigned start = *p;
        if (start <= addr && addr < p[2] + start) {
            *outIndex = (int)(((char*)p - (char*)base) / 0x18);
            *outOffset = addr - start;
            return 1;
        }
        p += 6;
    }
    return 0;
}

// @ 0x011e25d0
int UnfixContext::FindExistingSubObject(void* target, int* outIndex)
{
    char* subrefs = *(char**)((char*)this + 0xc);
    int* dict = *(int**)(subrefs + 0x10);
    int count = *(int*)(subrefs + 0x18);
    int* p = dict;
    int* end = dict + count * 6;
    while (p != end) {
        if (*(void**)p == target) {
            *outIndex = (int)(((char*)p - (char*)dict) / 0x18);
            return 1;
        }
        p += 6;
    }
    return 0;
}

// @ 0x011e2630
void __fastcall rw_free_block_30(void* self)
{
    int* p = (int*)((char*)self + 0x30);
    for (int i = 0; i < 4; ++i) {
        if (p[i] != 0) {
            if (self != 0) {
                void* owner = *(void**)((char*)self + 0xd4);
                ((void(__cdecl*)(void*))*(void**)owner)(p);
                return;
            }
            return;
        }
    }
}

// @ 0x011e2690
void __fastcall rw_cleanup_2690(void* self)
{
    int* p = (int*)((char*)self + 0x124);
    for (int i = 0; i < 4; ++i) {
        if (p[i] != 0) {
            void* owner = *(void**)((char*)self + 0xe0);
            ((void(__cdecl*)(void*))*(void**)owner)(p);
            break;
        }
    }
    FUN_011eab70((char*)self + 0xb0);
    FUN_011eb180((char*)self + 0xe4);
    if (self == 0)
        rw_free_block_30(0);
    else
        rw_free_block_30((char*)self + 0xc);
}

// @ 0x011e26f0
void __fastcall rw_UpdateSubreferencesData(void* self)
{
    int m = *(int*)((char*)self + 0x78);
    int n = (int)(intptr_t)FUN_011e4620(*(void**)(m + 0x34));
    *(int*)(n + 0x18) = (int)(intptr_t)FUN_011eb170((char*)self + 0xe4);
    n = (int)(intptr_t)FUN_011e4620(*(void**)(*(int*)((char*)self + 0x78) + 0x34));
    *(int*)(n + 0x10) = (int)(intptr_t)FUN_011eb160((char*)self + 0xe4);
    n = (int)(intptr_t)FUN_011e4620(*(void**)(*(int*)((char*)self + 0x78) + 0x34));
    *(int*)(n + 0x14) = (int)(intptr_t)FUN_011eb150((char*)self + 0xe4);
    n = (int)(intptr_t)ArenaSectionManifest_ExternalArenas(*(void**)(*(int*)((char*)self + 0x78) + 0x34));
    *(int*)(*(int*)(n + 8) + 8) = (int)(intptr_t)FUN_011eb160((char*)self + 0xe4);
}

// ---------------------------------------------------------------------------
// Remaining thiscall helpers on an opaque "arena-like" object.  The members
// below share one stub class purely to obtain __thiscall spelling.
// ---------------------------------------------------------------------------
struct Blob32 { int d[8]; };
struct ArenaSelf {
    void copy4(void* out);                         // 0x011e2240
    void callSubref(uint16_t idx);                 // 0x011e2270
    void* idToObject(uint32_t id);                 // 0x011e2300
    void grow(int n);                              // 0x011e2470
    void alignTo(uint32_t a);                      // 0x011e24b0
    void copyBlob(Blob32* out);                    // 0x011e2670
    void initRange(int* data, int n);              // 0x011e29c0
    void writeDictionary(void* p2);                // 0x011e2760 PARTIAL
    int getExportedObjectByIndex(unsigned index, void* out); // 0x011e28e0 PARTIAL
};

// @ 0x011e2240
void ArenaSelf::copy4(void* out)
{
    int* d = (int*)out;
    int* s = (int*)((char*)this + 0x30);
    d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3];
}

// @ 0x011e2270
void ArenaSelf::callSubref(uint16_t idx)
{
    int* p4 = *(int**)((char*)this + 4);
    int* p8 = *(int**)((char*)this + 8);
    int* reg = (int*)*p4;
    int obj = *(int*)(reg[2] + (int)idx * 4) + *reg;
    ((void(__cdecl*)(int))*(void**)(*p8 + 4))(obj);
}

// @ 0x011e2300
void* ArenaSelf::idToObject(uint32_t id)
{
    void* m = *(void**)((char*)this + 0x34);
    int n = (int)(intptr_t)ArenaSectionManifest_ExternalArenas(m);
    int* table = *(int**)(n + 8);
    int* chunk = (int*)table[id >> 0x16];
    return *(void**)((char*)chunk + (id & 0x3fffff) * 0x18);
}

// @ 0x011e2470
void ArenaSelf::grow(int n)
{
    *(int*)((char*)this + 0x7c) += n;
    uint32_t a = *(uint32_t*)((char*)this + 0xc4);
    int used = *(int*)((char*)this + 0xc0);
    *(int*)((char*)this + 0xc0) = used;
    if (a < 2)
        a = 1;
    *(uint32_t*)((char*)this + 0xc4) = a;
    *(int*)((char*)this + 0xc0) = used + n;
}

// @ 0x011e24b0
void ArenaSelf::alignTo(uint32_t a)
{
    uint32_t v = *(uint32_t*)((char*)this + 0x7c);
    if (a > 1)
        v = (v + (a - 1)) & ~(a - 1);
    *(uint32_t*)((char*)this + 0x7c) = v;
    v = *(uint32_t*)((char*)this + 0xc0);
    if (a > 1)
        v = (v + (a - 1)) & ~(a - 1);
    *(uint32_t*)((char*)this + 0xc0) = v;
    if (*(uint32_t*)((char*)this + 0xc4) < a)
        *(uint32_t*)((char*)this + 0xc4) = a;
    else
        *(uint32_t*)((char*)this + 0xc4) = *(uint32_t*)((char*)this + 0xc4);
}

// @ 0x011e2670
void ArenaSelf::copyBlob(Blob32* out)
{
    *out = *(Blob32*)((char*)this + 0x40);
}

// @ 0x011e29c0
void ArenaSelf::initRange(int* data, int n)
{
    *(int*)((char*)this + 4) = n;
    *(int**)this = data;
    if (n > 0) {
        for (int* p = data; p < data + n * 2; p += 2) {
            p[0] = -1;
            p[1] = 0;
        }
    }
}

// @ 0x011e2760  Arena::WriteDictionary.  PARTIAL.
void ArenaSelf::writeDictionary(void* p2) { (void)p2; }

// @ 0x011e28e0  Arena::GetExportedObjectByIndex.  PARTIAL.
int ArenaSelf::getExportedObjectByIndex(unsigned index, void* out)
{
    (void)index; (void)out;
    return 0;
}

// @ 0x011e2a00  AddResourceToArena<Adder>.  PARTIAL: template body approximated.
void rw_AddResourceToArena_stub(void* a, void* b, int c, int* d)
{
    (void)a; (void)b; (void)c; (void)d;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
