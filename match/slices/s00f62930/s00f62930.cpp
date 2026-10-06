// slice s00f62930 -- Swarm "terrain distribute" effect command
// (0x00f62930..0x00f63850).  Real PDB names: SP::cTerrainDistributeDescription,
// cTDDebugCommand, cTerrainDistributeEffectCommand, cTDEffectCommand,
// SWARM_TerrainDistributeAddCommands.  Module flags /O2 /MD /Gy /TP.
#include "types.h"

extern float kFXMaxFloat;                   // 0x015b0cb0
extern float g_1488874;                     // 0.1f constant
extern float g_1485720;                     // 1.0f constant
extern void* g_01667bac;                    // empty wide string
extern void* g_01667bad;
extern void* PTR_s_showLevels;              // "showLevels"
extern void* PTR_s_heights;                 // "heights"
extern void* PTR_s_types;                   // "types"
extern void* PTR_s_active;                  // "active"
extern void* PTR_s_debug;
extern void* PTR_s_level;
extern void* PTR_s_effect;
extern void* PTR_s_distance;
extern void* PTR_s_facing;
extern void* PTR_s_terrainDistribute;

void* __cdecl operator_new(int, const char*, int, int, int, int);
void  __cdecl operator_del(void*);
void  __cdecl EA_IO_WriteUint32(void*, void*, int, int);
void  __cdecl FUN_00f62580(int*);
void* __cdecl SP_TerrainEditor();
void* __cdecl FUN_00b2afb0();
void  __cdecl FUN_0083c780(int, int);
void  __cdecl FUN_0089a510();
void  __cdecl FUN_007f1890(void*, void*, void*, void*, void*);
void  __cdecl FUN_0092a100(void*, void*);
float __cdecl FUN_00a6eaf0(int);
char  __cdecl EA_ParseEnum(int, void*);
int   __cdecl EA_GetPropertyAsKey(void*, int, void*);
void  __cdecl EA_cCommandBase_ctor(void*);

// thiscall cArguments
struct cArguments {
    int  MainArguments(int def);
    int* OptionArguments(const char* name, int n);
    char HasFlag(const char* name);
};

struct cTerrainEditor { void* GetCurrentTerrainSphere(); };

// ===========================================================================
// 0x00f62930 -- bind the effect to the current terrain sphere
// ===========================================================================
void __fastcall FUN_00f62930(int self, int dummy, int a, int b) {
    (void)dummy; (void)a; (void)b;
    cTerrainEditor* te = (cTerrainEditor*)SP_TerrainEditor();
    void* sphere = te->GetCurrentTerrainSphere();
    int* ref = *(int**)(self + 0x1ac);
    if (ref) {
        *(int*)(self + 0x1ac) = 0;
        int n = ref[1];
        ref[1] = n - 1;
        if (n - 1 == 0) { ref[1] = 1; (*(void(__cdecl**)(int*,int))*(void***)ref)(ref, 1); }
    }
    (void)sphere;
}

// ===========================================================================
// 0x00f62b70 -- cTerrainDistributeInfo default constructor
// ===========================================================================
void __fastcall FUN_00f62b70(int* p) {
    ((float*)p)[1] = 0.1f;
    ((float*)p)[2] = kFXMaxFloat;
    p[0] = 0;
    ((float*)p)[3] = 1.0f;
    p[0xe] = 0;
    p[4] = 0; p[5] = 0; p[6] = 0; p[7] = 0; p[8] = 0; p[9] = 0;
    p[10] = 0; p[0xb] = 0; p[0xc] = 0; p[0xd] = 0;
}

// ===========================================================================
// 0x00f62bc0 -- serialize a description (operator<<)
// ===========================================================================
void __cdecl FUN_00f62bc0(int writer, int* d) {
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

// ===========================================================================
// 0x00f62d80 -- cTerrainDistributeEffectCommand constructor
// ===========================================================================
void __fastcall FUN_00f62d80(int* p) {
    float fmax = kFXMaxFloat;
    p[1] = 0;
    p[2] = 0;
    p[0] = 0;
    p[1] = 0;
    int* q = p + 4;
    for (int i = 8; i >= 0; i--) {
        q[0] = 0;
        ((float*)q)[1] = 0.1f;
        ((float*)q)[2] = fmax;
        ((float*)q)[3] = 1.0f;
        q[0xe] = 0;
        q[4] = 0; q[5] = 0; q[6] = 0;
        q[7] = q[5]; q[8] = q[6]; q[9] = q[7]; q[10] = q[8]; q[0xb] = q[9]; q[0xc] = q[10]; q[0xd] = q[0xb];
        q += 0x10;
    }
    p[0x94] = 0; p[0x95] = 0; p[0x96] = 0;
}

// ===========================================================================
// 0x00f62e60 -- cTerrainDistributeDescription destructor
// ===========================================================================
void __fastcall FUN_00f62e60(int* p) {
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

// ===========================================================================
// 0x00f62ea0 -- cTerrainDistributeInfo::SetInfoFromProps (approximate)
// ===========================================================================
void __fastcall FUN_00f62ea0(int self, int idx, void* props) {
    (void)self; (void)idx; (void)props;
}

// ===========================================================================
// 0x00f63000 -- cTerrainDistributeDescription constructor (approximate)
// ===========================================================================
void __fastcall FUN_00f63000(int* p) {
    for (int i = 0; i < 0x98/4; i++) p[i] = 0;
    ((float*)p)[0x10/4] = 1.0f;
}

// ===========================================================================
// 0x00f63120 -- SP::WriteDescription
// ===========================================================================
void __cdecl FUN_00f63120(int writer, int p) {
    int v = *(int*)(p + 8);
    EA_IO_WriteUint32((void*)writer, &v, 1, 0);
    int q = p + 0xc;
    for (int i = 5; i != 0; i--) { FUN_00f62bc0(writer, (int*)q); q += 0x28; }
}

// ===========================================================================
// 0x00f63190 -- cTerrainDistributeEffectCommand constructor
// ===========================================================================
void __fastcall FUN_00f63190(int* p) {
    p[0xd] = 0x33109bb;
    FUN_00f63000(p + 0xe);
    p[0x44] = 0;
    p[0x45] = (int)&g_01667bac;
    p[0x46] = (int)&g_01667bac;
    p[0x47] = (int)&g_01667bad;
}

// ===========================================================================
// 0x00f631e0 -- store a value then call a base init
// ===========================================================================
void __fastcall FUN_00f631e0(int self, int dummy, int v, int w) {
    (void)dummy; (void)w;
    *(int*)(self + 0x30) = v;
    FUN_0083c780(v, v);
}

// ===========================================================================
// 0x00f631f0 -- cTDDebugCommand::Execute
// ===========================================================================
void __fastcall FUN_00f631f0(int self, int dummy, cArguments* args) {
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

// ===========================================================================
// 0x00f63280 -- cTDLevelCommand::Execute (approximate)
// ===========================================================================
void __fastcall FUN_00f63280(int self, int dummy, cArguments* args) {
    (void)dummy;
    int* a = (int*)args->MainArguments(1);
    int n = 0; (void)a;
    if (n < 1) { int* pi = (int*)(*(int*)(self + 0x30) + 0xd8); *pi = *pi + 1; }
    else {
        int v = (*(int(__cdecl**)(int))(*(void**)((char*)*(int**)(self + 4) + 0x9c)))(*a);
        *(int*)(*(int*)(self + 0x30) + 0xd8) = v;
    }
    int lvl = *(int*)(*(int*)(self + 0x30) + 0xd8);
    if (lvl >= -1 && lvl < 5) (*(void(__cdecl**)(int))(*(void**)((char*)*(int**)(self + 4) + 0x8c)))(self);
}

// ===========================================================================
// 0x00f632f0 -- cTDDistanceCommand::Execute
// ===========================================================================
void __fastcall FUN_00f632f0(int self, int dummy, cArguments* args) {
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

// ===========================================================================
// 0x00f63360 -- cTDFacingCommand::Execute
// ===========================================================================
void __fastcall FUN_00f63360(int self, int dummy, cArguments* args) {
    (void)dummy;
    int a = args->MainArguments(1);
    int d = *(int*)(self + 0xc);
    float f = (float)(*(int(__cdecl**)(int))(*(void**)((char*)*(int**)(self + 4) + 0x98)))(a);
    *(float*)(d + 0x1c + *(int*)(d + 0xd8) * 0x28) = f;
}

// ===========================================================================
// 0x00f633a0 -- cTerrainDistributeEffectCommand::OnRegister (approximate)
// ===========================================================================
void __fastcall FUN_00f633a0(int self, int dummy, int a, int b) {
    (void)self; (void)dummy; (void)a; (void)b;
}

// ===========================================================================
// 0x00f63650 -- SWARM_TerrainDistributeAddCommands
// ===========================================================================
void __cdecl FUN_00f63650(int cmds, int* b) {
    (void)b;
    void* obj = operator_new(0x124, "ArgScript/TerrainDistributeEffect", 0, 0, 0, 0);
    
    (*(void(__cdecl**)(void*, int))(*(void**)((char*)*(void**)cmds + 0x14)))((void*)PTR_s_terrainDistribute, (int)obj);
}

// ===========================================================================
// 0x00f636f0 -- cTDEffectCommand::Execute (approximate)
// ===========================================================================
void __fastcall FUN_00f636f0(int self, int dummy, cArguments* args) {
    (void)self; (void)dummy; (void)args;
}

// ===========================================================================
// 0x00f63850 -- cTerrainDistributeEffectCommand::OnEndBlock (approximate)
// ===========================================================================
void __fastcall FUN_00f63850(int self, int dummy, char end) {
    (void)self; (void)dummy; (void)end;
}
