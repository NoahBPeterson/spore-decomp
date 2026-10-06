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

struct UnfixContextImpl {
    void Serialize(int* value);               // 0x011e3ac0
};

// ---------------------------------------------------------------- 011e3ac0
// @ 0x011e3ac0 -- UnfixContextImpl::Serialize; large, approximated.
void UnfixContextImpl::Serialize(int* value)
{
    (void)value;
}

// ---------------------------------------------------------------- Arena
struct Arena {
    char pad00[0x2c];
    int  m_field2c;    // +0x2c
    int  m_field30;    // +0x30
    int  m_field34;    // +0x34
    int  m_field38;    // +0x38
    UnfixContextImpl* m_ctx;  // +0x3c

    int  ObjectToId(int id);
};

// @ 0x011e3c30
int Arena::ObjectToId(int id)
{
    m_ctx->Serialize(&id);
    return id;
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
struct ArenaField {
    int* base;   // +0x0
    int  count;  // +0x4
};

struct ArenaOwner {
    ArenaField* f;   // +0x0
    int  FUN_011e3e10(int param_2);
    void FUN_011e3ed0(int param_2);
};

// @ 0x011e3e10
int ArenaOwner::FUN_011e3e10(int param_2)
{
    ArenaField* p = f;
    int local_8;
    ((EcxCtx*)p)->FUN_011e2b30(&local_8, &param_2);
    int* base = p->base;
    int* elem = base + local_8 * 2;
    if (param_2 != elem[0]) {
        elem = base + p->count * 2;
    }
    int* end = base + p->count * 2;
    if (elem != end) {
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
};

// @ 0x011e4600
void* ArenaSectionManifest::Types()
{
    return (void*)*dict;
}

// @ 0x011e4640
void ArenaSectionManifest::FUN_011e4640(int param_2, int param_3)
{
    int* d = dict;
    *d = *(int*)(param_2 + 0x30);
    f0c = param_2;
    *(int*)((char*)d + 8) = *(int*)(param_3 + 0x10);
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
    *(int*)(param_2 + 0x28) = *(int*)(param_2 + 0x28) + *(int*)(param_1 + 4) * 4 + 0xc;
    for (unsigned int i = 0; i < *(unsigned int*)(param_1 + 4); ++i) {
        int* pi = *(int**)(*(int*)(param_1 + 8) + i * 4);
        VtblStub* v = (VtblStub*)*(void**)pi;
        v->slot1((void*)param_2);
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

// ---------------------------------------------------------------- skeletons (partial)
// @ 0x011e3c70
void FUN_011e3c70() {}
// @ 0x011e3f20
void rw_arena_Arena_Initialize() {}
// @ 0x011e40a0
void rw_arena_Arena_Release() {}
// @ 0x011e4130
void rwArenaOpen() {}
// @ 0x011e43c0
void rwArenaClose() {}
// @ 0x011e4680
void FUN_011e4680() {}
// @ 0x011e4720
void ArenaSectionSubreferences_UnfixData() {}
// @ 0x011e4820
void ArenaSectionSubreferences_RefixData() {}
