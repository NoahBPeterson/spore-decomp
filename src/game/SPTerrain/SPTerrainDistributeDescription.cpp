// src/game/SPTerrain/SPTerrainDistributeDescription.cpp -- migrated from slice(s) s00f62930 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainDistributeDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_01667bac;                    // empty wide string
extern void* g_01667bad;
extern void* PTR_s_terrainDistribute;

// ---- items of slice s00f62930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_01667bac;                    // empty wide string
extern void* g_01667bad;
extern void* PTR_s_terrainDistribute;
void* __cdecl operator_new(int, const char*, int, int, int, int);
void  __cdecl EA_IO_WriteUint32(void*, void*, int, int);
void  __cdecl FUN_0083c780(int, int);
struct cArguments {
    int  MainArguments(int def);
    int* OptionArguments(const char* name, int n);
    char HasFlag(const char* name);
};
// The two overloads the terrain commands actually call (annotated instead of matched by name:
// the PDB's cArguments::MainArguments for 0x00838020 is the 3-argument internal form).
struct cArguments3 {
    int* MainArgsThree(int* out, int a, int b);   // 0x00838020 (thiscall, ret 0xc)
};
struct cArguments1 {
    int* MainArgsOne(int def);                    // 0x00838320 (thiscall, ret 4)
};
// virtual call through the object's vtable: VPTR(ret, obj, byte-offset, argtypes...)(obj, args...)
#define VPTR(ret, obj, slot, ...) \
    ((ret (__thiscall*)(void*, __VA_ARGS__))((void**)*(void**)(obj))[(slot) / 4])
// ---- items of slice s00f62930 end

// @ 0x00f62bc0
void __cdecl FUN_00f62bc0(int writer, int* d)
{
    int v;
    v = d[0]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = d[1]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = d[2]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = d[3]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = d[4]; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    v = (d[6] - d[5]) >> 4; EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    int n = (d[6] - d[5]) >> 4;
    int off = 0;
    while (n > 0) {
        v = *(int*)(off + d[5]); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(int*)(d[5] + 4 + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(int*)(d[5] + 8 + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(unsigned char*)(d[5] + 0xc + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(unsigned char*)(d[5] + 0xd + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        v = *(unsigned char*)(d[5] + 0xe + off); EA_IO_WriteUint32((void*)writer, &v, 1, 0);
        off += 0x10; n--;
    }
}

// @ 0x00f62e60
void __fastcall FUN_00f62e60(int* p)
{
    int i = 4;
    int* q = p + 1 + 10 * 4;             // this[1].mLevelInfo[1] area
    (void)q;
    // free the four inline eastl vectors
    for (int k = 0; k < 5; k++) {
        int* v = (int*)((char*)p + 0x10 + k * 0x28 + 0);
        (void)v;
    }
    // base vtable store
    *(int*)p = 0;
    (void)i;
}

// @ 0x00f62ea0
void __fastcall FUN_00f62ea0(int self, int idx, void* props)
{
    (void)self; (void)idx; (void)props;
}

// @ 0x00f63000
void __fastcall FUN_00f63000(int* p)
{
    for (int i = 0; i < 0x98/4; i++) p[i] = 0;
    ((float*)p)[0x10/4] = 1.0f;
}

// @ 0x00f63120
void __cdecl FUN_00f63120(int writer, int p)
{
    int v = *(int*)(p + 8);
    EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    int q = p + 0xc;
    for (int i = 5; i != 0; i--) { FUN_00f62bc0(writer, (int*)q); q += 0x28; }
}

// @ 0x00f63190
void __fastcall FUN_00f63190(int* p)
{
    p[0xd] = 0x33109bb;
    FUN_00f63000(p + 0xe);
    p[0x44] = 0;
    p[0x45] = (int)&g_01667bac;
    p[0x46] = (int)&g_01667bac;
    p[0x47] = (int)&g_01667bad;
}

// @ 0x00f631e0
void __fastcall FUN_00f631e0(int self, int dummy, int v, int w)
{
    (void)dummy; (void)w;
    *(int*)(self + 0x30) = v;
    FUN_0083c780(v, v);
}

// @ 0x00f631f0
void __fastcall FUN_00f631f0(int self, int dummy, cArguments* args)
{
    (void)dummy;
    args->MainArguments(0);
    int tmp;
    args->OptionArguments("showLevels", 2);
    if (args->HasFlag("heights")) *(int*)(*(int*)(self + 0xc) + 0xc) |= 1;
    else                       *(int*)(*(int*)(self + 0xc) + 0xc) &= 0xfffffffe;
    if (args->HasFlag("types")) *(int*)(*(int*)(self + 0xc) + 0xc) |= 2;
    else                        *(int*)(*(int*)(self + 0xc) + 0xc) &= 0xfffffffd;
    (void)tmp;
    if (args->HasFlag("active")) { *(int*)(*(int*)(self + 0xc) + 0xc) |= 4; return; }
    *(int*)(*(int*)(self + 0xc) + 0xc) &= 0xfffffffb;
}

// @ 0x00f63280
void __fastcall FUN_00f63280(int self, int dummy, cArguments* args)
{
    (void)dummy;
    int n = 0;
    int* a = ((cArguments3*)args)->MainArgsThree(&n, 0, 1);
    if (n > 0) {
        void* obj = *(void**)(self + 4);
        int v = VPTR(int, obj, 0x9c, int)(obj, a[0]);
        *(int*)(*(int*)(self + 0x30) + 0xd8) = v;
    } else {
        ++*(int*)(*(int*)(self + 0x30) + 0xd8);
    }
    int lvl = *(int*)(*(int*)(self + 0x30) + 0xd8);
    if (lvl >= 0 && lvl < 5) {
        void* obj = *(void**)(self + 4);
        VPTR(void, obj, 0x8c, int)(obj, self);
    }
}

// @ 0x00f632f0
void __fastcall FUN_00f632f0(int self, int dummy, cArguments* args)
{
    (void)dummy;
    int a = args->MainArguments(1);
    int d = *(int*)(self + 0xc);
    float f = (float)(*(int(__cdecl**)(int))(*(void**)((char*)*(int**)(self + 4) + 0x98)))(a);
    *(float*)(d + 0x10 + *(int*)(d + 0xd8) * 0x28) = f;
    int* o = args->OptionArguments("verticalWeight", 1);
    if (o) {
        d = *(int*)(self + 0xc);
        float g = (float)(*(int(__cdecl**)(int))(*(void**)((char*)*(int**)(self + 4) + 0x98)))(*o);
        *(float*)(d + 0x18 + *(int*)(d + 0xd8) * 0x28) = g;
    }
}

// @ 0x00f63360
void __fastcall FUN_00f63360(int self, int dummy, cArguments* args)
{
    (void)dummy;
    int* a = ((cArguments1*)args)->MainArgsOne(1);
    void* obj = *(void**)(self + 4);
    float f = VPTR(float, obj, 0x98, int)(obj, a[0]);
    int d = *(int*)(self + 0xc);
    *(float*)(d + *(int*)(d + 0xd8) * 0x28 + 0x1c) = f;
}

// @ 0x00f633a0
void __fastcall FUN_00f633a0(int self, int dummy, int a, int b)
{
    (void)self; (void)dummy; (void)a; (void)b;
}

// @ 0x00f63650
void __cdecl FUN_00f63650(int cmds, int* b)
{
    (void)b;
    void* obj = operator_new(0x124, "ArgScript/TerrainDistributeEffect", 0, 0, 0, 0);
    
    (*(void(__cdecl**)(void*, int))(*(void**)((char*)*(void**)cmds + 0x14)))((void*)PTR_s_terrainDistribute, (int)obj);
}

// @ 0x00f636f0
void __fastcall FUN_00f636f0(int self, int dummy, cArguments* args)
{
    (void)self; (void)dummy; (void)args;
}

// @ 0x00f63850
void __fastcall FUN_00f63850(int self, int dummy, char end)
{
    (void)self; (void)dummy; (void)end;
}
