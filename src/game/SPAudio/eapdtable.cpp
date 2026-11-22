// src/game/SPAudio/eapdtable.cpp -- migrated from slice(s) s00a61f50 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdtable.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __cdecl fx_register_sequence();  // 0x00a62410 (stays in the slice: not this object's)
bool __cdecl fx_register_decal();  // 0x00a62720 (stays in the slice: not this object's)
bool __cdecl fx_register_metaparticles();  // 0x00a62a50 (stays in the slice: not this object's)
bool __cdecl fx_register_sound();  // 0x00a62ba0 (stays in the slice: not this object's)
bool __cdecl fx_register_core();  // 0x00a62cc0 (stays in the slice: not this object's)

// ---- items of slice s00a61f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_refDepth_167545c;        // 0x0167545c  (recursion guard, limit 1000)
extern const char g_fxEmptyStr_13f2ce4[];  // 0x013f2ce4
extern const char g_fxMetaStr_14546a4[];   // 0x014546a4
extern const char g_fxTableStr_145454c[];  // 0x0145454c "table"
extern const char g_fxFmt_1432d80[];       // 0x01432d80
extern const char g_fxFmt3_1455518[];      // 0x01455518
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
typedef unsigned char      uint8;
typedef unsigned int       uint32;
struct EapdInterned { uint32 name; uint32 id; };
EapdInterned* __cdecl FUN_00a675f0(EapdInterned* out, const char* s);          // 0x00a675f0
void* __cdecl FUN_00a48ea0(uint32 a, uint32 b, void* ctor, uint32 size,
                                uint32 d, uint32 e, uint32 f, uint32 g);     // 0x00a48ea0
bool  __cdecl FUN_00a47f30(void* cls, void* handler);                      // 0x00a47f30
bool  __cdecl FUN_00a48a80(void* cls, void* method, uint32 a, uint32 b,
                            uint32 c, uint32 d, uint32 e, uint32 f);         // 0x00a48a80
bool  __cdecl FUN_00a48a30(void* cls, void* method, uint32 a, uint32 b,
                             uint32 c);                            // 0x00a48a30
void* __cdecl FUN_00a49390(void* cls);                                   // 0x00a49390
void  __cdecl FUN_00a49d30(void* obj, uint32 b, uint32 c);           // 0x00a49d30
void  __cdecl FUN_00a49e40(uint32 a, uint32 b, uint32 c, int n, void* arr); // 0x00a49e40
void  __cdecl FUN_00a49a00(void* obj, float* v);                  // 0x00a49a00
void  __cdecl FUN_00a48100(void* tbl, uint32 a, uint32 b, uint32 c, uint32 d); // 0x00a48100
void  __cdecl FUN_00a487f0(const char* fmt, ...);                                 // 0x00a487f0
void  __cdecl FUN_00a49570(void* it, float v);                                // 0x00a49570
void* __cdecl FUN_00a671f0(uint32 a, uint32 b, uint32 c);                   // 0x00a671f0
extern uint32 g_fxCmptMeta_167583c;      // 0x0167583c
extern uint32 g_fxCmptSoundMeta_1675840; // 0x01675840
extern uint32 g_fxCmptMeta2_1675844;     // 0x01675844
extern uint32 g_fxCmptMeta3_1675850;     // 0x01675850
extern uint32 g_eapdA_16758ac;           // 0x016758ac
extern uint32 g_eapdB_16758b0;           // 0x016758b0
extern uint32 g_eapdC_16758c4;           // 0x016758c4
extern uint32 g_eapdD_16758c8;           // 0x016758c8
struct FXElem {                         // 0x0c
    int   state;                        // +0x00
    float value;                        // +0x04
    float pad;                          // +0x08
};
struct FXTableBase {                    // reflected component base
    uint8  pad00[0x28];
    uint32 nameA;                       // +0x28
    uint32 nameB;                       // +0x2c
    int    count;                       // +0x30
    int    capacity;                    // +0x34
    FXElem* elems;                      // +0x38
    float  accum;                       // +0x3c
};
void* __cdecl fx_alloc_sound(uint32 a, uint32 b);   // 0x00a62b60
// ---- items of slice s00a61f50 end

// @ 0x00a625f0
void __cdecl fx_notify_value(FXTableBase* self, float nf)
{
    void* tbl = FUN_00a671f0(self->nameA, self->nameB, (uint32)g_fxCmptMeta_167583c);
    if (tbl == 0)
        return;
    int i = (int)nf;
    if (i < 0) i = 0;
    else if (i >= *(int*)((char*)tbl + 0x30)) i = *(int*)((char*)tbl + 0x30) - 1;
    float v;
    if (*(int*)((char*)tbl + 0x30) != 0)
        v = *(float*)((char*)(*(void**)((char*)tbl + 0x38)) + i * 0xc + 4);
    else
        v = 0.0f;
    if (++g_refDepth_167545c < 1000) {
        for (void* it = *(void**)((char*)(*(void**)((char*)self + 0xc)) + 8); it != 0; it = *(void**)it)
            FUN_00a49570(*(void**)((char*)it + 4), v);
    }
    --g_refDepth_167545c;
}

// @ 0x00a62690
void __cdecl fx_dump(FXTableBase* self)
{
    void* tbl = FUN_00a671f0(self->nameA, self->nameB, (uint32)g_fxCmptMeta_167583c);
    if (tbl == 0)
        return;
    FUN_00a49e40(*(uint32*)((char*)self + 0xc), g_eapdB_16758b0, g_eapdA_16758ac,
                  *(int*)((char*)tbl + 0x30), *(void**)((char*)tbl + 0x38));
}

// @ 0x00a626e0
void* __cdecl fx_alloc_insert(uint32 a, uint32 b)
{
    void* obj = FUN_00a49390((void*)g_fxCmptMeta2_1675844);
    if (obj != 0) {
        *(uint32*)((char*)obj + 0x28) = a;
        _ReadWriteBarrier();
        *(uint32*)((char*)obj + 0x2c) = b;
        FUN_00a49d30(obj, g_eapdC_16758c4, g_eapdD_16758c8);
    }
    return obj;
}

// @ 0x00a62720
bool __cdecl fx_register_decal()
{
    EapdInterned a;
    FUN_00a675f0(&a, "tabread");
    void* cls = FUN_00a48ea0(a.name, a.id, (void*)fx_alloc_insert, 0x30,
                                  0, 6, 0, 0);
    g_fxCmptMeta2_1675844 = (uint32)cls;
    bool ok = (cls != 0) & FUN_00a47f30(cls, (void*)fx_notify_value);
    FUN_00a675f0(&a, "tolist");
    ok &= FUN_00a48a30((void*)g_fxCmptMeta2_1675844, (void*)0xa62690, a.name, a.id, 0);
    FUN_00a675f0(&a, "set");
    ok &= FUN_00a48a80((void*)g_fxCmptMeta2_1675844, (void*)0xa57730, a.name, a.id, 2, 0, 0, 0);
    return ok;
}

// @ 0x00a627d0
void __cdecl fx_decal_update(FXTableBase* self, float v)
{
    void* tbl = FUN_00a671f0(self->nameA, self->nameB, (uint32)g_fxCmptMeta_167583c);
    if (tbl == 0)
        return;
    if (*(int*)((char*)tbl + 0x30) >= 4)
        return;
    ++g_refDepth_167545c;
    if (g_refDepth_167545c >= 1000)
        return;
    for (void* it = *(void**)((char*)self + 0xc + 8); it != 0; it = *(void**)it)
        FUN_00a49570(it, 0.0f);
    --g_refDepth_167545c;
}

// @ 0x00a62a10
void* __cdecl fx_alloc_insert2(uint32 a, uint32 b)
{
    return fx_alloc_insert(a, b);
}

// @ 0x00a62a50
bool __cdecl fx_register_metaparticles()
{
    EapdInterned a;
    FUN_00a675f0(&a, "tabread4");
    void* cls = FUN_00a48ea0(a.name, a.id, (void*)fx_alloc_insert2, 0x30,
                                  0, 6, 0, 0);
    g_fxCmptMeta3_1675850 = (uint32)cls;
    bool ok = cls != 0;
    ok &= FUN_00a47f30(cls, (void*)fx_decal_update);
    FUN_00a675f0(&a, g_fxEmptyStr_13f2ce4);
    ok &= FUN_00a48a80((void*)g_fxCmptMeta3_1675850, (void*)0xa57730, a.name, a.id, 2, 0, 0, 0);
    return ok;
}

// @ 0x00a62ad0
void __cdecl fx_sound_notify(FXTableBase* self, float v)
{
    void* tbl = FUN_00a671f0(self->nameA, self->nameB, (uint32)g_fxCmptMeta_167583c);
    if (tbl == 0)
        return;
    FUN_00a487f0((const char*)tbl, g_eapdA_16758ac, g_eapdB_16758b0, g_fxFmt_1432d80,
                  (double)*(float*)((char*)self + 0x30), (double)v);
}

// @ 0x00a62b20
void __cdecl fx_base_addop(FXTableBase* self, uint32 a, uint32 b, uint32 c, uint32 d)
{
    void* tbl = FUN_00a671f0(self->nameA, self->nameB, (uint32)g_fxCmptMeta_167583c);
    if (tbl != 0)
        FUN_00a48100(tbl, a, b, c, d);
    _ReadWriteBarrier();
}

// @ 0x00a62b60
void* __cdecl fx_alloc_sound(uint32 a, uint32 b)
{
    FXTableBase* obj = (FXTableBase*)FUN_00a49390((void*)g_fxCmptSoundMeta_1675840);
    if (obj != 0) {
        *(float*)&obj->count = 0.0f;
        _ReadWriteBarrier();
        obj->nameA = a;
        _ReadWriteBarrier();
        obj->nameB = b;
        FUN_00a49a00(obj, (float*)&obj->count);
    }
    return obj;
}

// @ 0x00a62c50
void __cdecl fx_meta_particles_cb(void* a, uint32 b, const char* c, uint32 d, uint32 e, float v)
{
    EapdInterned s, t;
    EapdInterned* ps = FUN_00a675f0(&s, g_fxTableStr_145454c);
    EapdInterned* pt = FUN_00a675f0(&t, g_fxMetaStr_14546a4);
    FUN_00a487f0((const char*)a, pt->name, pt->id, g_fxFmt3_1455518,
                 0, 0, ps->name, ps->id, b, c, (double)v);
}

// @ 0x00a62e90
bool __cdecl fx_register_all()
{
    bool ok = true;
    ok &= fx_register_core();
    ok &= fx_register_sequence();
    ok &= fx_register_decal();
    ok &= fx_register_metaparticles();
    ok &= fx_register_sound();
    return ok;
}
