// src/game/SPEngine/_at_006e0000.cpp
// Object file: SPEngine/_at_006e0000.obj.
// Graphics debug helpers: walk the vertex and index buffer lists, and register the buffer dump cheats.
// Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"

// Retail globals whose names are not known yet (address in the comment).
extern int   DAT_0170a6b4;   // 0x0170a6b4: head of the vertex buffer list
extern int   DAT_0170a798;   // 0x0170a798: head of the index buffer list
extern int   DAT_0140a944;   // 0x0140a944: flag name for the dump commands
extern void* PTR_DAT_01532db0;   // 0x01532db0: command object registered by RegisterBufferCheats
extern void* PTR_DAT_01532dac;   // 0x01532dac: command object registered by RegisterBufferCheats
extern void* PTR_FUN_0140a92c;   // 0x0140a92c: vtable for the vertex buffer cheat object
extern void* PTR_FUN_0140a9a8;   // 0x0140a9a8: vtable for the index buffer cheat object

extern "C" void* operator_new(unsigned n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void* SP_CheatManager();     // 0x0067de20 (equiv t2)

// Local stand-ins for the command classes. CreateBufferCheats is still non-matching and uses these shapes, so they stay.
// TODO(rewrite): replace with EA::ArgScript::cICommand / cCommandBase once CreateBufferCheats matches.
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
struct cCommandBase : cICommand {
    cCommandBase();   // 0x0083c800
    int mFields[3];
};
struct VertexBufferCheat : cCommandBase {
    virtual void v8();   // vtable 0x0140a92c
};
struct IndexBufferCheat : cCommandBase {
    virtual void v8();   // vtable 0x0140a9a8
};
void* operator new(unsigned n, const char* name, int a, int b, const char* file, int line);   // 0x00f473a0
void operator delete(void* p, const char* name, int a, int b, const char* file, int line);

// @ 0x006e0f90
void VisitCharts()
{
    unsigned int buf[6];
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
    unsigned int buf[5];
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
void __stdcall CommandDumpVertex(EA::ArgScript::cArguments* args)
{
    if (args->HasFlag((char const*)&DAT_0140a944))
        VisitCharts();
}

// @ 0x006e1070
void __stdcall CommandDumpIndex(EA::ArgScript::cArguments* args)
{
    if (args->HasFlag((char const*)&DAT_0140a944))
        VisitIndexBuffers();
}

// @ 0x006e10a0
void CreateBufferCheats()
{
    new ("Graphics/VertexBufferCheat", 0, 0, 0, 0) VertexBufferCheat;
    SP_CheatManager();
    new ("Graphics/IndexBufferCheat", 0, 0, 0, 0) IndexBufferCheat;
    SP_CheatManager();
}
