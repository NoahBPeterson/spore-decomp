// src/game/SPEngine/_at_006e0000.cpp -- migrated from slice(s) s006e0fd0, s006e0030 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_006e0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern int   DAT_0170a6b4;

// ---- items of slice s006e0030 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
extern int   DAT_0170a6b4;
// ---- items of slice s006e0030 end

// ---- items of slice s006e0fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* operator_new(unsigned n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern int  DAT_0170a798;
extern void* PTR_DAT_01532db0;
extern void* PTR_DAT_01532dac;
extern int  DAT_0140a944;
extern void* PTR_FUN_0140a92c;
extern void* PTR_FUN_0140a9a8;
extern "C" void* SP_CheatManager();   // 0x0067de20 (equiv t2)
extern "C" void  FUN_006e0f90();
extern "C" void  FUN_006e0fd0();
struct cICommand {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void Register(void* arg);   // +0x1c
};
struct cCommandBase {
    cICommand base_cICommand;
};
struct cArguments {
    char HasFlag(const void* flag);
};
extern "C" void  cCommandBase_ctor(cCommandBase* p);   // 0x0083c800 (equiv t2)
// ---- items of slice s006e0fd0 end

// @ 0x006e0f90
void VisitCharts()
{
    uint buf[6];
    for (int p = DAT_0170a6b4; p != 0; p = *(int*)(p + 0xc)) {
        for (int* q = *(int**)(p + 8); q != 0; q = (int*)q[1]) {
            int* obj = (int*)*q;
            (*(void(__stdcall**)(int*, void*))(*obj + 0x34))(obj, buf);
        }
    }
}

// @ 0x006e0fd0
void VisitIndexBuffers()
{
    uint buf[5];
    for (int p = DAT_0170a798; p != 0; p = *(int*)(p + 0xc)) {
        for (int* q = *(int**)(p + 8); q != 0; q = (int*)q[1]) {
            int* obj = (int*)*q;
            (*(void(__stdcall**)(int*, void*))(*obj + 0x34))(obj, buf);
        }
    }
}

// @ 0x006e1010
void RegisterBufferCheats()
{
    cCommandBase* p = (cCommandBase*)SP_CheatManager();
    (*(void(__thiscall**)(void*, void*))(*(int*)p + 0x1c))(p, PTR_DAT_01532db0);
    p = (cCommandBase*)SP_CheatManager();
    (*(void(__thiscall**)(void*, void*))(*(int*)p + 0x1c))(p, PTR_DAT_01532dac);
}

// @ 0x006e1040
void __stdcall CommandDumpVertex(cArguments* args)
{
    if (args->HasFlag(&DAT_0140a944) != '\0')
        FUN_006e0f90();
}

// @ 0x006e1070
void __stdcall CommandDumpIndex(cArguments* args)
{
    if (args->HasFlag(&DAT_0140a944) != '\0')
        FUN_006e0fd0();
}

// @ 0x006e10a0
void CreateBufferCheats()
{
    cCommandBase* p = (cCommandBase*)operator_new(0x10, "Graphics/VertexBufferCheat", 0, 0, 0, 0);
    if (p != 0) {
        cCommandBase_ctor(p);
        *(void**)p = PTR_FUN_0140a92c;
    }
    SP_CheatManager();
    p = (cCommandBase*)operator_new(0x10, "Graphics/IndexBufferCheat", 0, 0, 0, 0);
    if (p != 0) {
        cCommandBase_ctor(p);
        *(void**)p = PTR_FUN_0140a9a8;
    }
    SP_CheatManager();
}
