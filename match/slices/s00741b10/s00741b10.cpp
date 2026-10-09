// Slice s00741b10 (0x00741b10-0x00742b30): SP::cModelInstance::AddAnimationsFromArena.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
// Retail cModelInstance layout differs from the 2008 PDB (flags dword at +8, vectors at 0x14 stride):
// the class below declares only the members this function touches, at their retail offsets.
#include "types.h"
#include <new>

void operator delete[](void* p);                           // 0x00f47380

namespace SP {

struct Obj;
struct Blender;

struct Res { uint32_t w0, w4, w8, resId; int key; };

// Generic "arena object": views used by this function, at retail offsets.
struct Obj {
    uint32_t w0, w4;
    int key;                 // +8
    Res* r0c;                // +0xc
    Res* r10;                // +0x10
    uint32_t w14;
    int k18;                 // +0x18
    uint32_t pad1c[3];
    uint32_t* p28;           // +0x28
    uint32_t pad2c[4];
    Obj* p3c;                // +0x3c
    void Prepare(void (*cb)());   // 0x00fccdd0 (thiscall)
};

struct RefObj { virtual ~RefObj(); int rc; };

struct cMaterial {           // 0xc4 bytes
    Blender* bl;
    uint32_t w4;
    Obj* info;
    RefObj* ref;
    uint32_t pad[0xc4 / 4 - 4];
    cMaterial(Obj* o, int p3, uint16_t* p4, uint16_t* p5);   // 0x0073f000
    cMaterial(const cMaterial& o);                           // 0x0073f1c0
    ~cMaterial() {
        RefObj* r = ref;
        if (r) {
            if (--r->rc == 0) { r->rc = 1; delete r; }
        }
    }
};

struct E12 { Blender* bl; uint8_t b0, b1; uint16_t pad; Obj* obj; };
struct P8 { uint32_t first, second; };
struct E8 { uint8_t a, b; uint16_t c; uint8_t d, e; uint16_t f; };   // anim group record

template <class T>
struct Vec {
    T* mpBegin; T* mpEnd; T* mpCap; uint32_t pad[2];
    void Grow(T* pos, const T& v);       // out-of-line slow path (thiscall)
    void PushSlow(const T& v);           // out-of-line push_back (thiscall)
    void Insert(T* pos, uint32_t n, const T& v);
    void push(const T& v) {
        if (mpEnd < mpCap) {
            T* p = mpEnd;
            mpEnd = p + 1;
            if (p) new (p) T(v);
        } else {
            Grow(mpEnd, v);
        }
    }
    int size() const { return (int)(mpEnd - mpBegin); }
};

// 16-slot small-buffer vector living on the stack (begin/end/cap, allocator, pool ptr, buffer)
struct FixedObjVec {
    Obj** mpBegin; Obj** mpEnd; Obj** mpCap; uint32_t alloc; Obj** mpPool; uint32_t alloc2;
    Obj* buf[16];
    FixedObjVec() { mpBegin = buf; mpEnd = buf; mpCap = buf + 16; mpPool = buf; }
    ~FixedObjVec() { if (mpBegin && mpBegin != mpPool) operator delete[](mpBegin); }
    void Grow(Obj** pos, Obj* const& v);          // 0x006c1570
    void push(Obj* o) {
        Obj* v = o;
        if (mpEnd < mpCap) {
            Obj** p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            Grow(mpEnd, v);
        }
    }
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct Matrix3 { float m[9]; Matrix3(const Matrix3& src); };   // 0x0041cb40
extern const Matrix3 g_Matrix0162e9cc;
extern const float g_f0162e88c;                            // 0x0162e88c
extern const float g_f0162e890;                            // 0x0162e890
extern const float g_f0162e894;                            // 0x0162e894
extern const float g_f01485720;                            // 0x01485720

struct Xf {
    uint16_t a, b; float f0, f1, f2, w; Matrix3 m;
    Xf() : m(g_Matrix0162e9cc) { f0 = g_f0162e88c; f1 = g_f0162e890; f2 = g_f0162e894; a = 0; b = 0; w = g_f01485720; }
};

struct Elem { uint32_t a, b; Elem(); ~Elem(); };               // 0x006c0fa0 / 0x00c2e4e0
struct Desc { Elem arr[4]; };
struct ExpObj { uint32_t type; Obj* obj; uint32_t z[4]; Elem arr[4]; };
struct Handle { uint32_t h, z0, z1, z2; };

struct Arena {
    int GetNumExportedObjects();                           // 0x011e23a0
    void GetExportedObjectByIndex(int idx, ExpObj* out);   // 0x011e28e0
};
struct ArenaOwner { char pad[0x18]; Arena* arena; };

struct Pool {
    uint32_t LockedAligned(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);  // 0x00928a30
};
extern Pool* g_pool;                                       // 0x016c8b44

struct PropList { char GetDescription(const void* key); }; // 0x006a25a0
extern PropList* g_props;                                  // 0x015fd918
static const uint32_t kPropKey = 0x0138fdbe;              // property id (immediate, not an address)

struct BlenderVT {
    void* s0; void* s1; void* s2; void* s3;
    float (__thiscall* getTime)(Blender*);
    void  (__thiscall* setTime)(Blender*, float);
    void  (__thiscall* setFlags)(Blender*, uint32_t);
};
struct Blender {
    uint32_t w0; BlenderVT* vt;
    void SetBlending(Obj* res, int z);        // 0x0075b790
    void M1(uint32_t v);                      // 0x011fdff0
    void M2(Obj* first, float t);             // 0x011fdba0
};

Desc GetResourceDescriptor(uint32_t res, uint32_t flags, int count, int a, int b);   // 0x0075b190
Desc Describe(uint32_t res, uint32_t flags, int z);                                  // 0x011fdf00
Blender* MakeMulti(Handle* h, uint32_t res, uint32_t flags, int count, uint32_t a, void* b, int c); // 0x0075c9d0
Blender* MakeSingle(Handle* h, uint32_t res, uint32_t flags, int z);                 // 0x011fdd40
int ClassifyItem(Obj* o);                                                            // 0x006c1c30
void ObjCallback();                                                                  // 0x00798d30

struct cModelInstance {
    uint32_t vt, rc, flags;
    uint32_t pad0c[2];
    Vec<E8> v14;
    Vec<cMaterial> v28;
    Vec<E12> v3c;
    Vec<E12> v50;
    Vec<Blender*> v64;
    Vec<P8> v78;

    // @ 0x00741b10  SP::cModelInstance::AddAnimationsFromArena
    void AddAnimationsFromArena(ArenaOwner* src, int param_3, uint16_t* param_4, uint16_t* param_5);
    void ResizeV78(uint32_t n);
};

void cModelInstance::ResizeV78(uint32_t n)
{
    uint32_t sz = (uint32_t)(v78.mpEnd - v78.mpBegin);
    if (n > sz) {
        P8 z; z.first = 0; z.second = 0;
        v78.Insert(v78.mpEnd, n - sz, z);
    } else {
        P8* dst = v78.mpBegin + n;
        P8* d = dst;
        for (P8* s = v78.mpEnd; s != v78.mpEnd; ++s, ++d) *d = *s;
        v78.mpEnd -= (v78.mpEnd - d);
    }
}

static __forceinline Blender* MakeBlender(cModelInstance* self, uint32_t res, uint32_t flags, int count,
                            int descArg, uint32_t xa, void* xb, Obj* first)
{
    Blender* bl;
    Handle h;
    if (self->flags & 0x20) {
        {
            Desc d = GetResourceDescriptor(res, flags, count, descArg, 0);
            h.h = g_pool->LockedAligned(d.arr[0].a, d.arr[0].b, 0, 0, 0, 0, 0, 0);
            h.z0 = 0; h.z1 = 0; h.z2 = 0;
        }
        bl = MakeMulti(&h, res, flags, count, xa, xb, 0);
    } else {
        {
            Desc d = Describe(res, flags, 0);
            h.h = g_pool->LockedAligned(d.arr[0].a, d.arr[0].b, 0, 0, 0, 0, 0, 0);
            h.z0 = 0; h.z1 = 0; h.z2 = 0;
        }
        bl = MakeSingle(&h, res, flags, 0);
        bl->M1(*first->p28);
        bl->M2(first, 0.0f);
    }
    float t = bl->vt->getTime(bl);
    bl->vt->setTime(bl, t);
    bl->vt->setFlags(bl, flags);
    return bl;
}

void cModelInstance::AddAnimationsFromArena(ArenaOwner* src, int param_3, uint16_t* param_4,
                                            uint16_t* param_5)
{
    Arena* arena = src->arena;
    FixedObjVec v1;     // 0x70001 items (animation resources)
    FixedObjVec v2;     // 0xff0000 items (blend sources)

    Xf xf;
    if (!param_4) param_4 = &xf.a;
    if (!param_5) param_5 = &xf.a;

    struct Extra { P8* items; int count; };
    Extra* extra = 0;

    E8 E;
    E.a = 0xff; E.b = 0; E.c = 0; E.d = 0; E.e = 0; E.f = 0;
    Vec<E8>* pv14 = &v14;
    if (v14.mpBegin != v14.mpEnd) {
        E8* last = v14.mpEnd - 1;
        E.c = (uint16_t)((int8_t)last->b + last->c);
        E.f = (uint16_t)(v78.mpEnd - v78.mpBegin);
    }

    int matCount0 = v28.size();
    int numObjs = arena->GetNumExportedObjects();
    int maxCount = 0;

    for (int i = 0; i < numObjs; ++i) {
        ExpObj x;
        x.type = 0; x.obj = 0; x.z[0] = 0; x.z[1] = 0; x.z[2] = 0; x.z[3] = 0;
        x.arr[0].a = 0; x.arr[0].b = 1;
        arena->GetExportedObjectByIndex(i, &x);
        Obj* o = x.obj;
        switch (x.type) {
        case 0xff0000:
            flags |= 8;
            v2.push(o);
            break;
        case 0x70001:
            if (!(flags & 1)) v1.push(o);
            break;
        case 0x7000b:
            if (v14.mpBegin == v14.mpEnd) {
                E12 e; e.bl = 0; e.b0 = 0; e.b1 = 0; e.obj = o;
                v3c.PushSlow(e);
            }
            break;
        case 0x7000c: {
            {
                cMaterial tmp(o, param_3, param_4, param_5);
                v28.push(tmp);
            }
            Res* r = o->r10;
            if (r && r->w4 && E.a == 0xff) {
                E.a = (uint8_t)matCount0;
                E.b = (uint8_t)r->w4;
            }
            break;
        }
        case 0xff0001:
            extra = (Extra*)o;
            break;
        case 0xff0002:
            if (v14.mpBegin == v14.mpEnd) {
                E12 e; e.bl = 0; e.b0 = 0; e.b1 = 0; e.obj = o;
                v50.push(e);
            }
            break;
        }
    }

    if (v1.mpBegin != v1.mpEnd || param_3 != 0) {
        if ((flags & 0xa) != 0 || (v1.mpBegin == v1.mpEnd && param_3 != 0)) {
            if (!g_props->GetDescription((const void*)kPropKey)) flags |= 0x20;
        }
        flags |= 4;
        int n1 = v1.size();
        bool hasOther = false;
        uint8_t has1 = 0;
        if (n1 > 0) {
            for (int j = 0; j < n1; ++j) {
                int r = ClassifyItem(v1.mpBegin[j]);
                if (r == 1) has1 = (uint8_t)r; else hasOther = true;
            }
            if (has1 && hasOther) flags |= 0x20;
        }

        // pass 1: per mesh/material-info entry
        int n3 = (int)(v3c.mpEnd - v3c.mpBegin);
        for (int i = 0; i < n3; ++i) {
            E12* el = v3c.mpBegin + i;
            int cnt = 0; Obj* first = 0;
            Res* rr = el->obj->r10;
            for (int j = 0; j < n1; ++j) {
                Obj* it = v1.mpBegin[j];
                if (rr->key == it->key) { if (!first) first = it; ++cnt; }
            }
            if (cnt > 0) {
                uint32_t res = rr->resId;
                uint32_t fl; ((uint8_t*)&fl)[0] = 1; ((uint8_t*)&fl)[1] = 3; ((uint8_t*)&fl)[2] = 0;
                if (has1) ((uint8_t*)&fl)[1] = 6;
                Blender* bl = MakeBlender(this, res, fl, cnt, 0, 0, 0, first);
                v64.push(bl);
                el->bl = bl;
                if (maxCount < cnt) maxCount = cnt;
            }
        }

        // pass 2: materials appended by this call
        int n28 = v28.size();
        for (int i = matCount0; i < n28; ++i) {
            cMaterial* m = v28.mpBegin + i;
            int cnt = 0; Obj* first = 0;
            m->info->Prepare(ObjCallback);
            Res* rr = m->info->r0c;
            for (int j = 0; j < n1; ++j) {
                Obj* it = v1.mpBegin[j];
                if (rr->key == it->key) { if (!first) first = it; ++cnt; }
            }
            if (cnt > 0 || param_3 != 0) {
                uint32_t res = m->info->r0c->resId;
                uint32_t fl; ((uint8_t*)&fl)[0] = 1; ((uint8_t*)&fl)[1] = 3; ((uint8_t*)&fl)[2] = 0;
                if (has1) ((uint8_t*)&fl)[1] = 6;
                Blender* bl = MakeBlender(this, res, fl, cnt, 1, m->info->r10->w0, m->info->r0c, first);
                v64.push(bl);
                m->bl = bl;
                if (maxCount < cnt) maxCount = cnt;
            }
        }

        // pass 3: region map entries
        int n50 = (int)(v50.mpEnd - v50.mpBegin);
        for (int i = 0; i < n50; ++i) {
            E12* el = v50.mpBegin + i;
            int cnt = 0; Obj* first = 0;
            Obj* info = el->obj;
            for (int j = 0; j < n1; ++j) {
                Obj* it = v1.mpBegin[j];
                if (info->k18 == it->key) { if (!first) first = it; ++cnt; }
            }
            if (cnt > 0) {
                uint32_t res = (uint32_t)info->r0c;
                uint32_t fl; ((uint8_t*)&fl)[0] = 0; ((uint8_t*)&fl)[1] = 1; ((uint8_t*)&fl)[2] = 0;
                Blender* bl = MakeBlender(this, res, fl, cnt, 0, 0, 0, first);
                v64.push(bl);
                el->bl = bl;
                if (maxCount < cnt) maxCount = cnt;
            }
        }
        (void)maxCount;

        int total = v2.size();
        if (extra) total += extra->count;
        if (total == 0) {
            int n = (int8_t)v1.size();
            E.d = (uint8_t)v1.size();
            ResizeV78((uint32_t)((int16_t)E.f + n));
            for (int k = 0; k < n; ++k) {
                P8* s = &v78.mpBegin[(int16_t)E.f + k];
                s->first = (uint32_t)(((int16_t)E.f + k) ^ v1.mpBegin[k]->key);
                s->second = (uint32_t)v1.mpBegin[k];
            }
            E.e = (uint8_t)n;
        } else {
            E.d = (uint8_t)total;
            ResizeV78((uint32_t)((int16_t)E.f + (int8_t)total));
            int idx = (int16_t)E.f;
            if (extra) {
                for (int k = 0; k < extra->count; ++k) {
                    v78.mpBegin[idx].second = extra->items[k].second;
                    v78.mpBegin[idx].first = extra->items[k].first;
                    ++idx;
                }
            }
            E.e = (uint8_t)idx;
            int n2 = v2.size();
            for (int j = 0; j < n2; ++j) {
                Obj* it = v2.mpBegin[j];
                v78.mpBegin[idx].second = (uint32_t)it->p3c;
                v78.mpBegin[idx].first = it->w0;
                ++idx;
                if (flags & 0x20) {
                    Obj* res = v2.mpBegin[j]->p3c;
                    int c3 = (int)(v3c.mpEnd - v3c.mpBegin);
                    for (int k = 0; k < c3; ++k) {
                        E12* el = v3c.mpBegin + k;
                        if (el->obj->r10->key == res->key) el->bl->SetBlending(res, 0);
                    }
                    int c28 = v28.size();
                    for (int k = matCount0; k < c28; ++k) {
                        cMaterial* m = v28.mpBegin + k;
                        if (m->info->r0c->key == res->key) m->bl->SetBlending(res, 0);
                    }
                    int c50 = (int)(v50.mpEnd - v50.mpBegin);
                    for (int k = 0; k < c50; ++k) {
                        E12* el = v50.mpBegin + k;
                        if (el->obj->k18 == res->key) el->bl->SetBlending(res, 0);
                    }
                }
            }
        }
    }

    // append the animation-group record
    if (pv14->mpEnd < pv14->mpCap) {
        E8* p = pv14->mpEnd;
        pv14->mpEnd = p + 1;
        if (p) *p = E;
    } else {
        pv14->Grow(pv14->mpEnd, E);
    }
}

}  // namespace SP
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct SP {
    void g_f0162e894(...); // 0x0162e894
    void g_f01485720(...); // 0x01485720
    void g_f0162e890(...); // 0x0162e890
    void g_f0162e88c(...); // 0x0162e88c
};
}
