// Slice s00a61f50 -- the 0x00a61f50..0x00a62ec0 run: EAPd reflected "FX component"
// (kFXCmpt*) class family.  Object: SPAudio (un-named object in the modmap gap between
// eapdmenu.obj and eapdtable.obj).
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast   (see manifest.txt)
#include "fxcmpt.h"

// Forward declarations for registration helpers defined further down.
void* __cdecl fx_alloc_sound(uint32 a, uint32 b);   // 0x00a62b60

// ------------------------------------------------------------------ 0x00a61f50
// Element-array bulk set: memcpy `count` elements from `src` over the front, then fill
// the freshly-inserted [start, end) tail with `{state = 1, value = v}` (SSE 4-wide).
// @ 0x00a61f50
void __cdecl fx_array_set_range(FXTableBase* self, int start, int end, const void* src, float v)
{
    int count = end - start;
    if (start < 0)
        return;
    if (self->capacity < end)
        return;
    FUN_011e0744((char*)self->elems + start * 0xc, src, count * 0xc);
    if (start >= end)
        return;
    for (int i = start; i < end; ++i) {
        FXElem* e = (FXElem*)((char*)self->elems + i * 0xc);
        if (e->state != 1) {
            e->state = 1;
            e->value = v;
        }
    }
}

// @ 0x00a620e0
void __cdecl fx_array_fill(FXTableBase* self, float v)
{
    int i = 0;
    if (self->count > i) {
        do {
            self->elems[i].state = 1;
            self->elems[i].value = v;
            ++i;
        } while (i < self->count);
    }
}

// @ 0x00a62080
void __cdecl fx_array_resize_and_set(FXTableBase* self, float nf, const void* src)
{
    int n = (int)nf;
    if (n >= 1 && n <= self->capacity)
        self->count = n;
    fx_array_set_range(self, 0, (int)nf, src, nf);
}

// @ 0x00a620b0
void __cdecl fx_array_dump(FXTableBase* self)
{
    FUN_00a49e40(*(uint32*)((char*)self + 0xc), g_eapdB_16758b0, g_eapdA_16758ac,
                  self->count, self->elems);
}

// ------------------------------------------------------------------ 0x00a62120
// Max |value| over the element array (4-way x87 unroll), result in the accumulator.
// @ 0x00a62120
float __cdecl fx_array_max_abs(FXTableBase* self)
{
    float best = 0.0f;
    int i = 0;
    int n = self->count;
    for (; i + 4 <= n; i += 4) {
        float a0 = (float)FUN_00a68fe0((double)*(float*)((char*)self->elems + (i + 0) * 0xc + 4));
        float a1 = (float)FUN_00a68fe0((double)*(float*)((char*)self->elems + (i + 1) * 0xc + 4));
        float a2 = (float)FUN_00a68fe0((double)*(float*)((char*)self->elems + (i + 2) * 0xc + 4));
        float a3 = (float)FUN_00a68fe0((double)*(float*)((char*)self->elems + (i + 3) * 0xc + 4));
        if (best <= a0) best = a0;
        if (best <= a1) best = a1;
        if (best <= a2) best = a2;
        if (best <= a3) best = a3;
    }
    for (; i < n; ++i) {
        float a = (float)FUN_00a68fe0((double)*(float*)((char*)self->elems + i * 0xc + 4));
        if (best <= a) best = a;
    }
    self->accum = best;
    return best;
}

// ------------------------------------------------------------------ 0x00a62270
// Sum the positive values, normalise into [0,1] using the total, apply, and propagate.
// @ 0x00a62270
float __cdecl fx_array_sum_pos(FXTableBase* self)
{
    float total = 0.0f;
    int i = 0;
    int n = self->count;
    for (; i + 4 <= n; i += 4) {
        float v0 = *(float*)((char*)self->elems + (i + 0) * 0xc + 4);
        float v1 = *(float*)((char*)self->elems + (i + 1) * 0xc + 4);
        float v2 = *(float*)((char*)self->elems + (i + 2) * 0xc + 4);
        float v3 = *(float*)((char*)self->elems + (i + 3) * 0xc + 4);
        if (v0 > 0.0f) total += v0;
        if (v1 > 0.0f) total += v1;
        if (v2 > 0.0f) total += v2;
        if (v3 > 0.0f) total += v3;
    }
    for (; i < n; ++i) {
        float v = *(float*)((char*)self->elems + i * 0xc + 4);
        if (v > 0.0f) total += v;
    }
    if (total > 0.0f) {
        total = FUN_00a68fe0(self, total);
        total = total * *(float*)&self;  // scaled by the component's rate
        if (total >= 0.0f) {
            ++g_refDepth_167545c;
            if (g_refDepth_167545c < 1000) {
                for (void* it = *(void**)((char*)self + 8); it != 0; it = *(void**)it)
                    FUN_00a49570(it, total);
            }
            --g_refDepth_167545c;
        }
    }
    return total;
}

// @ 0x00a623f0
void __cdecl fx_set_accum(FXTableBase* self, float v)
{
    ((FxAccum*)&self->accum)->Set(v);       // 0x00936090, thiscall
}

// @ 0x00a62410
bool __cdecl fx_register_sequence()
{
    EapdInterned a, b;
    FUN_00a675f0("kFXCmptSequence", &a);
    void* cls = FUN_00a48ea0(a.name, a.id, (void*)0xa61c20, 0x40,
                                  0, 9, 0, (uint32)(void*)FUN_00a61e50);
    bool ok = cls != 0;
    g_fxCmptSeqA_1675838 = (uint32)cls;
    ok &= FUN_00a47f30(cls, (void*)FUN_00a61e50);
    FUN_00a47f70(cls, (void*)FUN_00a62050);
    FUN_00a675f0("kFXCmptSound", &b);
    ok &= FUN_00a48a80(cls, (void*)FUN_00a61ec0, b.name, b.id, 1, 0, 0, 0);
    FUN_00a675f0("kFXCmptShake", &a);
    ok &= FUN_00a48a80(cls, (void*)0xa62080, a.name, a.id, 9, 0, 0, 0);
    ok &= FUN_00a47f30(cls, (void*)fx_array_sum_pos);
    FUN_00a675f0("kFXCmptDecal", &b);
    ok &= FUN_00a48a80(cls, (void*)fx_array_resize_and_set, b.name, b.id, 1, 0, 0, 0);
    return ok;
}

// @ 0x00a625f0
void __cdecl fx_notify_value(FXTableBase* self, float nf)
{
    void* tbl = FUN_00a671f0((uint32)g_fxCmptMeta_167583c, self->nameB, self->nameA);
    if (tbl == 0)
        return;
    int i = (int)nf;
    if (i < 0) i = 0;
    else if (i >= *(int*)((char*)tbl + 0x30)) i = *(int*)((char*)tbl + 0x30) - 1;
    float v = 0.0f;
    if (*(int*)((char*)tbl + 0x30) != 0)
        v = *(float*)((char*)(*(void**)((char*)tbl + 0x38)) + i * 0xc + 4);
    if (++g_refDepth_167545c < 1000) {
        for (void* it = *(void**)((char*)self + 0xc + 8); it != 0; it = *(void**)it)
            FUN_00a49570(it, v);
    }
    --g_refDepth_167545c;
}

// @ 0x00a62690
void __cdecl fx_dump(FXTableBase* self)
{
    void* tbl = FUN_00a671f0((uint32)g_fxCmptMeta_167583c, self->nameB, self->nameA);
    if (tbl == 0)
        return;
    FUN_00a49e40(*(uint32*)((char*)self + 0xc), g_eapdB_16758b0, g_eapdA_16758ac,
                  *(int*)((char*)tbl + 0x30), *(void**)((char*)tbl + 0x38));
}

// @ 0x00a626e0
void* __cdecl fx_alloc_insert(uint32 a, uint32 b)
{
    void* obj = FUN_00a49390((void*)g_fxCmptMeta2_1675844);
    if (obj == 0)
        return 0;
    *(uint32*)((char*)obj + 0x28) = a;
    *(uint32*)((char*)obj + 0x2c) = b;
    FUN_00a49d30(g_eapdC_16758c4, g_eapdD_16758c8, 0, obj);
    return obj;
}

// @ 0x00a62a10
void* __cdecl fx_alloc_insert2(uint32 a, uint32 b)
{
    return fx_alloc_insert(a, b);
}

// @ 0x00a62720
bool __cdecl fx_register_decal()
{
    EapdInterned a, b;
    FUN_00a675f0("kFXCmptDecal", &a);
    void* cls = FUN_00a48ea0(a.name, a.id, (void*)fx_alloc_insert, 0x30,
                                  0, 6, 0, 0);
    bool ok = cls != 0;
    g_fxCmptMeta2_1675844 = (uint32)cls;
    ok &= FUN_00a47f30(cls, (void*)fx_notify_value);
    FUN_00a675f0("kFXCmptShake", &b);
    ok &= FUN_00a48a80(cls, (void*)0xa62690, b.name, b.id, 0, 0, 0, 0);
    FUN_00a675f0("kFXCmptSound", &a);
    ok &= FUN_00a48a80(cls, (void*)0xa57730, a.name, a.id, 2, 0, 0, 0);
    return ok;
}

// @ 0x00a627d0
void __cdecl fx_decal_update(FXTableBase* self, float v)
{
    void* tbl = FUN_00a671f0((uint32)g_fxCmptMeta_167583c, self->nameB, self->nameA);
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

// @ 0x00a62a50
bool __cdecl fx_register_metaparticles()
{
    EapdInterned a, b;
    FUN_00a675f0("kFXCmptMetaParticles", &a);
    void* cls = FUN_00a48ea0(a.name, a.id, (void*)fx_alloc_insert2, 0x30,
                                  0, 6, 0, 0);
    bool ok = cls != 0;
    g_fxCmptMeta3_1675850 = (uint32)cls;
    ok &= FUN_00a47f30(cls, (void*)fx_decal_update);
    FUN_00a675f0(g_fxEmptyStr_13f2ce4, &b);
    ok &= FUN_00a48a80(cls, (void*)0xa57730, b.name, b.id, 2, 0, 0, 0);
    return ok;
}

// @ 0x00a62ba0
bool __cdecl fx_register_sound()
{
    EapdInterned a, b;
    FUN_00a675f0("kFXCmptSound", &a);
    void* cls = FUN_00a48ea0(a.name, a.id, (void*)fx_alloc_sound, 0x34,
                                  0, 6, 0, 0);
    bool ok = cls != 0;
    g_fxCmptSoundMeta_1675840 = (uint32)cls;
    ok &= FUN_00a47f30(cls, (void*)0xa62ad0);
    FUN_00a675f0("kFXCmptShake", &b);
    ok &= FUN_00a48a80(cls, (void*)0xa62b20, b.name, b.id, 9, 0, 0, 0);
    FUN_00a675f0(g_fxEmptyStr_13f2ce4, &a);
    ok &= FUN_00a48a80(cls, (void*)0xa57730, a.name, a.id, 2, 0, 0, 0);
    return ok;
}

// @ 0x00a62ad0
void __cdecl fx_sound_notify(FXTableBase* self, float v)
{
    void* tbl = FUN_00a671f0((uint32)g_fxCmptMeta_167583c, self->nameB, self->nameA);
    if (tbl == 0)
        return;
    FUN_00a487f0(g_fxFmt_1432d80, (double)*(float*)((char*)self + 0x30), (double)v);
}

// @ 0x00a62b60
void* __cdecl fx_alloc_sound(uint32 a, uint32 b)
{
    void* obj = FUN_00a49390((void*)g_fxCmptSoundMeta_1675840);
    if (obj == 0)
        return 0;
    *(float*)((char*)obj + 0x30) = 0.0f;
    *(uint32*)((char*)obj + 0x28) = a;
    *(uint32*)((char*)obj + 0x2c) = b;
    FUN_00a49a00(obj, obj, (float*)((char*)obj + 0x30));
    return obj;
}

// @ 0x00a62b20
void __cdecl fx_base_addop(FXTableBase* self, uint32 a, uint32 b, uint32 c)
{
    void* tbl = FUN_00a671f0((uint32)g_fxCmptMeta_167583c, self->nameB, self->nameA);
    if (tbl == 0)
        return;
    FUN_00a487f0(g_fxFmt2_1432d80, a, b, c, 0);
}

// @ 0x00a62c50
void __cdecl fx_meta_particles_cb(void* a, uint32 b, const char* c, uint32 d, float v)
{
    EapdInterned s, t;
    FUN_00a675f0(c, &s);
    FUN_00a675f0(g_fxMetaStr_14546a4, &t);
    FUN_00a487f0(g_fxFmt3_1455518, s.name, s.id, t.name, t.id, b, d, 0, 0, (double)v);
}

// @ 0x00a62cc0
bool __cdecl fx_register_core()
{
    EapdInterned a, b;
    FUN_00a675f0(g_fxCoreStr_1455520, &a);
    g_fxCmptSeqB_1675848 = a.name;
    g_fxCmptSeqC_167584c = a.id;
    FUN_00a675f0("kFXCmptShake", &b);
    void* cls = FUN_00a48ea0(b.name, b.id, (void*)0xa61c20, 0x40,
                                  0, 9, 0, (uint32)(void*)FUN_00a61e50);
    bool ok = cls != 0;
    g_fxCmptMeta_167583c = (uint32)cls;
    ok &= FUN_00a47f30(cls, (void*)FUN_00a61e50);
    FUN_00a47f70(cls, (void*)FUN_00a62050);
    FUN_00a675f0("kFXCmptSound", &a);
    ok &= FUN_00a48a80(cls, (void*)0xa57730, a.name, a.id, 1, 0, 0, 0);
    FUN_00a675f0(g_fxCoreStr2_1409198, &b);
    ok &= FUN_00a48b30(cls, (void*)fx_meta_particles_cb, b.name, b.id,
                           2, 1, 2, 5, 0);
    return ok;
}

// @ 0x00a62e90
bool __cdecl fx_register_all()
{
    bool ok = fx_register_core();
    ok &= fx_register_sequence();
    ok &= fx_register_decal();
    ok &= fx_register_metaparticles();
    bool last = fx_register_sound();
    return last & ok;
}
