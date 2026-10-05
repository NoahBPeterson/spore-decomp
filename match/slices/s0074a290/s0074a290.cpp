// Slice s0074a290: SP::cModelWorld methods (~0x0074a290-0x0074b150).
// /O2, frame pointer omitted, SSE scalar float moves -> /arch:SSE /fp:fast.
// All callees/globals are masked relocations, so their declarations only need
// the right calling convention and argument shape.
#include "../../include/types.h"

static inline void** VT(void* p) { return *(void***)p; }

// vector deallocate (FUN_00f47380)
extern "C" void __cdecl eastl_dealloc(void* p);

// cSPTransform (2 words + 4 floats + 3x3 matrix = 0x38)
struct cSPTransform {
    uint16_t f0;
    uint16_t f2;
    float    f4;
    float    f8;
    float    fc;
    float    f10;
    float    m[9];        // +0x14
    void operator=(const cSPTransform& o);
};
typedef char cSPTransform_size_check[(sizeof(cSPTransform) == 0x38) ? 1 : -1];

// result of `anonymous_namespace'::translateTransform (FUN_006271a0)
extern cSPTransform translateTransform(const void* xform, const void* src);

// cModelInstance-like object held at cModelWorld+0x9c (FUN_00743270 thiscall)
struct cModelInstance {
    bool BuildBaked(cSPTransform* t, void* arg);   // FUN_00743270
    bool GetMeshesX(void* arg);       // FUN_0073eb90
};

namespace SP {

struct cModelWorld {
    char pad[0x800];

    void ReleaseTransformedHull(void** pp);              // 0074a650
    void FreeTransformedBuffer();                        // 0074b150
    void RemoveOccluder(int idx);                        // 0074a8c0
    bool GetBakedMeshes(void* model, void* arg2);        // 0074a690
    bool GetBakedMeshesUnscaled(void* model, void* arg2); // 0074a700
    bool GetBakedMeshes2(void* model, void* arg2, cSPTransform* out);  // 0074a780
    bool GetMeshes(void* model, void* arg2, cSPTransform* out);        // 0074a850
    static void SetExternalEffectsTransform(void* a, void* b, void* c);  // 0074a290
    void SubA490(void* a, void* b);                      // 0074a490
    void SubA920(void* a, void* b);                      // 0074a920
};

} // namespace SP

// ---------------------------------------------------------------------------
// @ 0x0074A650  SP::cModelWorld::ReleaseTransformedHull
// ---------------------------------------------------------------------------
struct HullVtbl { virtual void slot0(); virtual void slot1(); };

struct TransformedHull {
    char pad0[0x10];
    void* p10;      // +0x10
    char pad1[4];
    HullVtbl* p18;  // +0x18
};

void SP::cModelWorld::ReleaseTransformedHull(void** pp)
{
    TransformedHull* h = (TransformedHull*)*pp;
    if (h) {
        eastl_dealloc(h->p10);
        HullVtbl* p = h->p18;
        if (p)
            p->slot1();
        eastl_dealloc(h);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0074B150  SP::cModelWorld::FreeTransformedBuffer
// ---------------------------------------------------------------------------
void SP::cModelWorld::FreeTransformedBuffer()
{
    void* p = *(void**)((char*)this + 0x44);
    if (p && p != *(void**)((char*)this + 0x54))
        eastl_dealloc(p);
}

// ---------------------------------------------------------------------------
// @ 0x0074A8C0  SP::cModelWorld::RemoveOccluder
// ---------------------------------------------------------------------------
struct OccluderSlot { uint32_t w[5]; };

struct SlotVectorBase {
    OccluderSlot* mBegin;   // +0x00
    char pad0[0x10];
    int f14;                // +0x14
    int f18;                // +0x18

    int next(int idx);      // FUN_00745520
};

void SP::cModelWorld::RemoveOccluder(int idx)
{
    SlotVectorBase* v = (SlotVectorBase*)((char*)this + 0x2bc);
    uint32_t old = v->f18;
    uint32_t* slot = &v->mBegin[idx].w[0];
    *slot = (*slot & 0xC0000000u) | (old & 0x3FFFFFFFu) | 0x80000000u;
    v->f18 = idx;
    if (v->f14 == idx)
        v->f14 = v->next(idx);
}

// ---------------------------------------------------------------------------
// @ 0x0074A690  SP::cModelWorld::GetBakedMeshes
// ---------------------------------------------------------------------------
bool SP::cModelWorld::GetBakedMeshes(void* model, void* arg2)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    if (*(int*)(base + 0x9c) != 0) {
        cSPTransform t = translateTransform(base + 0xe4, base + 0x10);
        cModelInstance* inst = *(cModelInstance**)(base + 0x9c);
        return inst->BuildBaked(&t, arg2);
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0074A700  SP::cModelWorld::GetBakedMeshesUnscaled
// ---------------------------------------------------------------------------
bool SP::cModelWorld::GetBakedMeshesUnscaled(void* model, void* arg2)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    if (*(int*)(base + 0x9c) != 0) {
        cSPTransform t = translateTransform(base + 0xe4, base + 0x10);
        ++t.f2;
        t.f10 = 1.0f;
        cModelInstance* inst = *(cModelInstance**)(base + 0x9c);
        return inst->BuildBaked(&t, arg2);
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0074A780  SP::cModelWorld::GetBakedMeshes2
// ---------------------------------------------------------------------------
extern float g_162eb0c, g_162eb10, g_162eb14, g_1485720;
extern char g_162ec4c[];
struct Matrix3 { void Assign(const void* src); };

bool SP::cModelWorld::GetBakedMeshes2(void* model, void* arg2, cSPTransform* out)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    if (*(int*)(base + 0x9c) != 0) {
        *out = translateTransform(base + 0xe4, base + 0x10);
        cSPTransform r;
        r.f0 = 0;
        r.f2 = 0;
        r.f4 = g_162eb0c;
        r.f8 = g_162eb10;
        r.fc = g_162eb14;
        r.f10 = g_1485720;
        ((Matrix3*)((char*)&r + 0x14))->Assign((const void*)g_162ec4c);
        cModelInstance* inst = *(cModelInstance**)(base + 0x9c);
        return inst->BuildBaked(&r, arg2);
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0074A850  SP::cModelWorld::GetMeshes
// ---------------------------------------------------------------------------
bool SP::cModelWorld::GetMeshes(void* model, void* arg2, cSPTransform* out)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    if (*(int*)(base + 0x9c) != 0) {
        *out = translateTransform(base + 0xe4, base + 0x10);
        cModelInstance* inst = *(cModelInstance**)(base + 0x9c);
        return inst->GetMeshesX(arg2);
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0074A290  SP::cModelWorld::SetExternalEffectsTransform
// partial: index/slot walk over the occluder transform array omitted.
// ---------------------------------------------------------------------------
void SP::cModelWorld::SetExternalEffectsTransform(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ---------------------------------------------------------------------------
// @ 0x0074A490  SP::cModelWorld::SubA490
// partial: EASTL vector build path partly omitted.
// ---------------------------------------------------------------------------
void SP::cModelWorld::SubA490(void* a, void* b)
{
    (void)a; (void)b;
}

// ---------------------------------------------------------------------------
// @ 0x0074A920  SP::cModelWorld::SubA920
// partial: refcount/list walk partly omitted.
// ---------------------------------------------------------------------------
void SP::cModelWorld::SubA920(void* a, void* b)
{
    (void)a; (void)b;
}
