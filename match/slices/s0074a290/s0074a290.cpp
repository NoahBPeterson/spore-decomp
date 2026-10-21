// Slice s0074a290: SP::cModelWorld methods (~0x0074a290-0x0074b150).
// /O2, frame pointer omitted, SSE scalar float moves -> /arch:SSE /fp:fast.
// All callees/globals are masked relocations, so their declarations only need
// the right calling convention and argument shape.
#include "../../include/types.h"

static inline void** VT(void* p) { return *(void***)p; }

// Refcounted slot release (inlined in SubA920): clear the slot, drop a refcount;
// when it reaches zero, restore it to 1 and call the object's vtbl[0](1) dtor.
static __forceinline void ReleaseSlot(void** slot)
{
    void* q = *slot;
    if (q) {
        *slot = 0;
        uint32_t* rc = (uint32_t*)((char*)q + 4);
        if (--*rc == 0) {
            *rc = 1;
            ((void(__thiscall*)(void*, int))VT(q)[0])(q, 1);
        }
    }
}

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
    void operator=(const cSPTransform& o);   // 0x537dc0
    void Compose(const cSPTransform* o);   // ComposeTransforms 0x40ccb0
};
typedef char cSPTransform_size_check[(sizeof(cSPTransform) == 0x38) ? 1 : -1];

// result of `anonymous_namespace'::translateTransform (FUN_006271a0)
extern cSPTransform translateTransform(const void* xform, const void* src);   // 0x6271a0

extern float g_162eb0c, g_162eb10, g_162eb14, g_1485720;
extern char g_162ec4c[];
struct Matrix3 {
    float m[9];
    void Assign(const void* src);   // 0x41cb40
};
typedef char Matrix3_size_check[(sizeof(Matrix3) == 0x24) ? 1 : -1];

extern void __cdecl PropGetTransforms(void* list, unsigned key, int* count, void* out);  // 0x6a0c30

// cModelInstance-like object held at cModelWorld+0x9c (FUN_00743270 thiscall)
struct cModelInstance {
    bool BuildBaked(cSPTransform* t, void* arg);   // FUN_00743270
    bool GetMeshesX(void* arg);       // FUN_0073eb90
};

namespace SP {

class cModelWorld { public:
    char pad[0x800];

    void ReleaseTransformedHull(void** pp);              // 0074a650
    void FreeTransformedBuffer();                        // 0074b150
    void RemoveOccluder(int idx);                        // 0074a8c0
    bool GetBakedMeshes(void* model, void* arg2);        // 0074a690
    bool GetBakedMeshesUnscaled(void* model, void* arg2); // 0074a700
    bool GetBakedMeshes2(void* model, void* arg2, cSPTransform* out);  // 0074a780
    bool GetMeshes(void* model, void* arg2, cSPTransform* out);        // 0074a850
    static void __stdcall SetExternalEffectsTransform(void* a, void* b, void* c);  // 0074a290
    void SubA490(void* a, void* b);                      // 0074a490
    void SubA920(void* list, void* obj, uint32_t flags); // 0074a920
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

bool SP::cModelWorld::GetBakedMeshes2(void* model, void* arg2, cSPTransform* out)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    if (*(int*)(base + 0x9c) != 0) {
        cSPTransform r = translateTransform(base + 0xe4, base + 0x10);
        *out = r;
        r.f0 = 0;
        r.f2 = 0;
        r.f4 = g_162eb0c;
        r.f8 = g_162eb10;
        r.fc = g_162eb14;
        r.f10 = g_1485720;
        ((Matrix3*)&r.m[0])->Assign((const void*)g_162ec4c);
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
// ---------------------------------------------------------------------------
struct EffRec {
    uint32_t id;       // +0x00
    uint32_t id2;      // +0x04
    void*    obj;      // +0x08
    cSPTransform xf;   // +0x0c
    uint32_t pad;      // +0x44
};
typedef char EffRec_size_check[(sizeof(EffRec) == 0x48) ? 1 : -1];

void SP::cModelWorld::SetExternalEffectsTransform(void* a, void* b, void* c)
{
    char* model = a ? (char*)a - 8 : 0;
    EffRec* rec = *(EffRec**)(model + 0xdc);
    if (rec == 0)
        return;

    if (b != 0) {
        if (rec->obj == 0)
            return;
        do {
            if (c == 0 || (c == (void*)rec->id && rec->id2 == 0)) {
                rec->xf = *(cSPTransform*)b;
                void* obj = rec->obj;
                cSPTransform t;
                t.f0 = *(uint16_t*)((char*)a + 8);
                t.f2 = *(uint16_t*)((char*)a + 0xa);
                t.f4 = *(float*)((char*)a + 0xc);
                t.f8 = *(float*)((char*)a + 0x10);
                t.fc = *(float*)((char*)a + 0x14);
                t.f10 = *(float*)((char*)a + 0x18);
                ((Matrix3*)&t.m[0])->Assign((char*)a + 0x1c);
                t.Compose(&rec->xf);
                ((void(__thiscall*)(void*, cSPTransform*))VT(obj)[0x18 / 4])(obj, &t);
            }
            rec++;
        } while (rec->obj);
        return;
    }

    int count = 0;
    void* data = 0;
    PropGetTransforms(*(void**)((char*)a + 0x90), 0x2a907b6, &count, &data);
    rec = *(EffRec**)(model + 0xdc);
    if (rec->obj == 0)
        return;
    int i = 0;
    do {
        if (c == 0 || (c == (void*)rec->id && rec->id2 == 0)) {
            void* obj = rec->obj;
            void* arg;
            if (i < count) {
                rec->xf = ((cSPTransform*)data)[i];
                cSPTransform t = translateTransform(&rec->xf, (char*)a + 8);
                arg = &t;
            } else {
                rec->xf.f0 = 0;
                rec->xf.f2 = 0;
                rec->xf.f4 = g_162eb0c;
                rec->xf.f8 = g_162eb10;
                rec->xf.fc = g_162eb14;
                rec->xf.f10 = g_1485720;
                *(Matrix3*)&rec->xf.m[0] = *(Matrix3*)g_162ec4c;
                arg = (char*)a + 8;
            }
            ((void(__thiscall*)(void*, void*))VT(obj)[0x18 / 4])(obj, arg);
        }
        i++;
        rec++;
    } while (rec->obj);
}

// ---------------------------------------------------------------------------
// @ 0x0074A490  SP::cModelWorld::SubA490
// ---------------------------------------------------------------------------
typedef void (__cdecl *Sub9510Fn)(void*, unsigned, void*, unsigned);   // 0x6b9510
typedef void (__cdecl *VecCopyFn)(void*, const void*, unsigned);       // 0x11e0744
extern "C" void* __cdecl GfxAlloc(unsigned size, const char* name, int, int, int, int);  // 0xf473a0

void SP::cModelWorld::SubA490(void* model, void* outp)
{
    ((void(__thiscall*)(void*, void*))VT(this)[0x58 / 4])(this, model);
    char* base = model ? (char*)model - 8 : 0;
    uint32_t* p = *(uint32_t**)outp;
    if (p == 0) {
        p = (uint32_t*)GfxAlloc(0x28, "Graphics", 0, 0, 0, 0);
        if (p) {
            p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0;
            p[5] = 0; p[6] = 0; p[7] = 0; p[8] = 0; p[9] = 0;
        }
        void* arg = base ? base + 8 : 0;
        ((void(__thiscall*)(void*, void*, void*))VT(this)[0xd8 / 4])(this, arg, p);
        p[8] = p[0];
        p[9] = p[4];
        p[7] = p[2];
        uint32_t n = p[2];
        p[0] = 0xc;
        p[4] = (uint32_t)GfxAlloc(n * 0xc, "Graphics", 0, 0, 0, 0);
        *(uint32_t**)outp = p;
    } else {
        ((void(__thiscall*)(void*, void*, void*))VT(this)[0x17c / 4])(this, model, p);
    }

    cSPTransform t;
    t.f0 = *(uint16_t*)(base + 0x10);
    t.f2 = *(uint16_t*)(base + 0x12);
    t.f4 = *(float*)(base + 0x14);
    t.f8 = *(float*)(base + 0x18);
    t.fc = *(float*)(base + 0x1c);
    t.f10 = *(float*)(base + 0x20);
    ((Matrix3*)&t.m[0])->Assign(base + 0x24);
    t.Compose((cSPTransform*)(base + 0xe4));

    void* src = (void*)p[9];
    void* dst = (void*)p[4];
    if (p[8] == p[0]) {
        ((VecCopyFn)0x11e0744)(dst, src, p[2] * p[0]);
    } else {
        uint32_t* s = (uint32_t*)src;
        uint32_t* d = (uint32_t*)dst;
        for (uint32_t k = p[2]; k > 0; k--) {
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            s = (uint32_t*)((char*)s + p[8]);
            d += 3;
        }
    }
    ((Sub9510Fn)0x6b9510)(&t, p[2], (void*)p[4], 0xc);
}

// ---------------------------------------------------------------------------
// @ 0x0074A920  SP::cModelWorld::SubA920
// ---------------------------------------------------------------------------
struct PropKey { uint32_t id; uint32_t id2; int idx; };             // 0xc bytes
extern bool __cdecl GetPropertyAsKey(void* list, unsigned key, PropKey* out);   // 0x6a1250
extern bool __cdecl CreateModelInstance(unsigned id, unsigned idx, void** out, unsigned flags); // 0x754ba0
extern void __cdecl Sub7340(void* obj);                              // 0x747340
extern "C" float __cdecl sqrtf(float);
struct cSPBoundingBox {
    float w[6];
    void TransformBy(const void* xf);   // 0x409dd0
};

void SP::cModelWorld::SubA920(void* list, void* obj, uint32_t flags)
{
    char* o = (char*)obj;
    for (int i = 0; i < 6; i++) {
        ReleaseSlot((void**)(o + 0x9c + i * 4));
        ReleaseSlot((void**)(o + 0xb4 + i * 4));
        *(uint8_t*)(o + 0xcc + i) = 0xff;
    }

    PropKey k;
    k.id = 0; k.id2 = 0; k.idx = 0;
    for (int i = 0; i < 4; i++) {
        if (!GetPropertyAsKey(list, i + 0xf9efbb, &k))
            break;
        void** slot = (void**)(o + 0x9c + i * 4);
        ReleaseSlot(slot);
        int idx = (k.idx == -1) ? *(int*)((char*)list + 0x10) : k.idx;
        CreateModelInstance(k.id, idx, slot, flags);
    }

    if ((flags & 0x20) && GetPropertyAsKey(list, 0xf9efc1, &k)) {
        void** slot = (void**)(o + 0xb0);
        int idx = (k.idx == -1) ? *(int*)((char*)list + 0x10) : k.idx;
        ReleaseSlot(slot);
        CreateModelInstance(k.id, idx, slot, 0);
    }

    if (GetPropertyAsKey(list, 0xf9efc0, &k)) {
        void** slot = (void**)(o + 0xac);
        int idx = (k.idx == -1) ? 0 : k.idx;
        ReleaseSlot(slot);
        CreateModelInstance(k.id, idx, slot, 0);
    }

    Sub7340(obj);

    void** pslot = (void**)(o + 0x9c);
    if (*pslot == 0)
        pslot = (void**)(o + 0xac);
    void* src = *pslot;
    if (src == 0)
        goto tail;

    if (!(*(uint8_t*)(o + 0xe) & 1)) {
        *(uint32_t*)(o + 0x84) = *(uint32_t*)((char*)src + 0xb4);
        *(uint32_t*)(o + 0x88) = *(uint32_t*)((char*)src + 0xb8);
        *(uint32_t*)(o + 0x8c) = *(uint32_t*)((char*)src + 0xbc);
        *(uint32_t*)(o + 0x78) = *(uint32_t*)((char*)src + 0xa8);
        *(uint32_t*)(o + 0x7c) = *(uint32_t*)((char*)src + 0xac);
        *(uint32_t*)(o + 0x80) = *(uint32_t*)((char*)src + 0xb0);
        if (*(float*)(o + 0xf4) != 1.0f || (*(uint8_t*)(o + 0xe4) & 6))
            ((cSPBoundingBox*)(o + 0x78))->TransformBy(o + 0xe4);
    }

    if (!((*(uint32_t*)(o + 0xc) >> 0x11) & 1)) {
        float v = *(float*)((char*)src + 0xc0);
        *(float*)(o + 0x74) = v;
        if (*(float*)(o + 0xf4) != 1.0f || (*(uint8_t*)(o + 0xe4) & 6)) {
            v = *(float*)(o + 0xf4) * *(float*)(o + 0x74);
            *(float*)(o + 0x74) = v;
            float dx = *(float*)(o + 0xe8);
            float dy = *(float*)(o + 0xec);
            float dz = *(float*)(o + 0xf0);
            *(float*)(o + 0x74) = sqrtf(dx * dx + dy * dy + dz * dz) + v;
        }
    }

tail:
    *(uint32_t*)(o + 0xc) |= 0x4000;
    ++*(uint16_t*)(o + 0x70);
    void* q = *(void**)(o + 0x6c);
    if (q) {
        void* r = ((void*(__thiscall*)(void*, unsigned))VT(q)[0xc / 4])(q, 0x7bbc4ff);
        if (r)
            ((void(__thiscall*)(void*, void*))VT(r)[0])(r, o + 8);
    }
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
