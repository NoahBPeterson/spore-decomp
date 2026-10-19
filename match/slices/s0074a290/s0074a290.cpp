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
    void Compose(const cSPTransform* o);   // ComposeTransforms 0x40ccb0
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
    void AddAttachments(char* model);                    // 0074ac80
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

// ---------------------------------------------------------------------------
// @ 0x0074AC80  SP::cModelWorld::AddAttachments
// ---------------------------------------------------------------------------
struct IRel { virtual void v0(); virtual void Release(); };

struct Rec48 {
    uint32_t id;       // +0
    uint32_t id2;      // +4
    IRel*    obj;      // +8
    cSPTransform xf;   // +0xc
    uint8_t  flag;     // +0x44
    Rec48();                                    // 0x746de0
    ~Rec48() { if (obj) obj->Release(); }       // 0xae9670
};

void* operator new[](size_t, const char*, int, int, int, int);   // 0xf473a0
void operator delete[](void*, const char*, int, int, int, int);
extern "C" void* __cdecl EffectsManager();     // 0x67ddd0
extern bool __cdecl PropReserve(void* list, unsigned key, int* count, void* out);     // 0x6a0ae0
extern void __cdecl PropGetTransforms(void* list, unsigned key, int* count, void* out);  // 0x6a0c30
extern bool __cdecl PropGetFloats(void* list, unsigned key, int* count, void* out);   // 0x6a08b0
extern bool __cdecl PropGetInts(void* list, unsigned key, int* count, void* out);     // 0x6a0990
extern void* __cdecl GfxAlloc(unsigned size, const char* name, int, int, int, int);   // 0xf473a0
extern "C" void* __cdecl memset(void*, int, unsigned);

#define VCALL(T, obj, off) ((T)VT(obj)[(off) / 4])

void SP::cModelWorld::AddAttachments(char* m)
{
    cSPTransform t;
    Rec48* r;
    char* var;
    int n; int first; int c2;
    int cnt1; void* data1; int cnt2; void* data2; int cnt3; void* data3;
    uint32_t flags = *(uint32_t*)(m + 0x138);
    if (!(flags & 8)) {
        void* list = *(void**)(m + 0x98);
        if (!(flags & 4) && PropReserve(list, 0x2a907b5, &cnt1, &data1)) {
            int good = 0;
            cnt2 = 0;
            PropGetTransforms(list, 0x2a907b6, &cnt2, &data2);
            cnt3 = 0;
            data3 = 0;
            PropReserve(list, 0x2a907b9, &cnt3, &data3);
            void* defModel = *(void**)((char*)this + 0x5c8);
            if (defModel == 0) {
                void* e = EffectsManager();
                defModel = VCALL(void*(__thiscall*)(void*), e, 0x5c)(e);
            }
            for (int i = 0; i < cnt1; i++) {
                void* e = EffectsManager();
                if (VCALL(bool(__thiscall*)(void*, unsigned, int), e, 0x28)(e, *(unsigned*)((char*)data1 + i * 12), 0))
                    good++;
            }
            Rec48* recs = new ("Graphics", 0, 0, 0, 0) Rec48[good + 1];
            *(Rec48**)(m + 0xdc) = recs;
            int j = 0;
            for (int i = 0; i < cnt1; i++) {
                r = (Rec48*)(*(char**)(m + 0xdc) + j * 0x48);
                void* mdl;
                if (i < cnt3) {
                    void* e = EffectsManager();
                    mdl = VCALL(void*(__thiscall*)(void*, unsigned), e, 0x54)(e, *(unsigned*)((char*)data3 + i * 12));
                    if (mdl == 0) mdl = defModel;
                } else {
                    mdl = defModel;
                }
                if (r->obj) {
                    IRel* o = r->obj;
                    r->obj = 0;
                    o->Release();
                }
                if (VCALL(bool(__thiscall*)(void*, unsigned, int, void*), mdl, 8)(mdl, *(unsigned*)((char*)data1 + i * 12), 0, &r->obj)) {
                    void* o = r->obj;
                    VCALL(void(__thiscall*)(void*, int, void*), o, 0x4c)(o, 6, (char*)this + 0xc);
                    if (i < cnt2) {
                        r->xf = ((cSPTransform*)data2)[i];
                        t.f0 = *(uint16_t*)(m + 0x10);
                        t.f2 = *(uint16_t*)(m + 0x12);
                        t.f4 = *(float*)(m + 0x14);
                        t.f8 = *(float*)(m + 0x18);
                        t.fc = *(float*)(m + 0x1c);
                        t.f10 = *(float*)(m + 0x20);
                        ((Matrix3*)&t.m[0])->Assign(m + 0x24);
                        t.Compose(&r->xf);
                        void* o2 = r->obj;
                        VCALL(void(__thiscall*)(void*, cSPTransform*), o2, 0x18)(o2, &t);
                    } else {
                        void* o2 = r->obj;
                        VCALL(void(__thiscall*)(void*, void*), o2, 0x18)(o2, m + 0x10);
                    }
                    if ((*(uint32_t*)(m + 0xc) >> 0x13) & 1) {
                        void* o3 = r->obj;
                        VCALL(void(__thiscall*)(void*, int), o3, 8)(o3, 0);
                    }
                    if (!(*(uint8_t*)(m + 0xc) & 1)) {
                        void* o4 = r->obj;
                        VCALL(void(__thiscall*)(void*, int), o4, 0x30)(o4, 1);
                    }
                    r->id = *(uint32_t*)((char*)data1 + i * 12);
                    r->id2 = 0;
                    j++;
                }
            }
            if (!(*(uint32_t*)(m + 0x138) & 0x20000000)) {
                *(float*)(m + 0x124) = 0.0f;
                if (list) {
                    if (VCALL(bool(__thiscall*)(void*, unsigned, char**), list, 0x24)(list, 0x2a907b8, &var)
                        && *(uint16_t*)(var + 0x12) == 0xd) {
                        char* p = var;
                        if (*(uint8_t*)(var + 0x10) & 0x30) p = *(char**)var;
                        *(float*)(m + 0x124) = *(float*)p;
                    }
                }
            }
        }
        if (*(int*)((char*)this + 0x1cc) != 0) {
            if (PropGetFloats(list, 0x49fc837, &n, &first)) {
                unsigned size = n * 4 + 0x14;
                int* p = (int*)GfxAlloc(size, "Graphics", 0, 0, 0, 0);
                memset(p, 0, size);
                p[0] = n;
                for (int k = 0; k < n; k++) p[5 + k] = -1;
                *(int**)(m + 0xe0) = p;
                p[1] = first;
                if (PropGetInts(list, 0x49fc838, &c2, *(char**)(m + 0xe0) + 8) && c2 != n)
                    (*(int**)(m + 0xe0))[2] = 0;
                if (PropGetInts(list, 0x49fc83a, &c2, *(char**)(m + 0xe0) + 0x10) && c2 != n)
                    (*(int**)(m + 0xe0))[4] = 0;
                if (PropGetFloats(list, 0x49fc839, &c2, *(char**)(m + 0xe0) + 0xc) && c2 != n)
                    (*(int**)(m + 0xe0))[3] = 0;
            }
        }
        char* mgr = *(char**)((char*)this + 0x18);
        void** it = *(void***)(mgr + 0x4c);
        void** end = *(void***)(mgr + 0x50);
        for (; it != end; ++it) {
            void* o = *it;
            VCALL(void(__thiscall*)(void*, void*), o, 0)(o, m + 8);
        }
    }
}
