// Slice s00f2f830 -- Simulator scenario object region (bfs2), part 1.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// The 8 functions are members of one large scenario/editor object.  Retail
// layout is reached through raw byte offsets on `this`; direct callees are
// declared with their original VA so the equivalence resolver can map them.
#include "types.h"

// --- direct callees (address comments; call targets are relocations) --------
// cVarListSerializer over `this`.
void* __cdecl cVarListSerializer_Construct(void* dst, void* owner, void* desc, unsigned id); // 0x00692F90
bool  __cdecl cVarListSerializer_Serialize(void* self, void* stream);                        // 0x00693E10
void* __cdecl cVarListSerializer_ctorA(void*, void*, void*, void*, void*);                   // 0x00693CD0
void  __cdecl cVarListSerializer_a(void*);                                                   // 0x00692EC0
void  __cdecl cVarListSerializer_b(void*);                                                   // 0x00692EA0
void  __cdecl cVarListSerializer_dtor(void*);                                                // 0x00693900

// Allocation / streams.
void* __cdecl EA_Allocate(unsigned, const char*, int, int, int, int);   // 0x00F473A0 (6-arg new)
void  __cdecl EA_Delete(void*);                                        // 0x00F47380
void* __cdecl EA_Trace_ZoneObject_new(int, int, int);                  // 0x00926020
void* __cdecl memstream_ctor(void*, int, int);                         // 0x0093BA40
bool  __cdecl memstream_SetData(void*, void*, void*);                  // 0x0093B8E0
void* __cdecl DatabasePackedFile_ctor(void*, const wchar_t*, void*);   // 0x008D9F80
void* __cdecl cObjectDatabase_ctor(void*, void*);                      // 0x0069FA60
void* __cdecl byte_vector_ctor(void*, void*);                          // 0x006B73E0

// Container ops.
void  __cdecl set_capacity_27e8(void*, unsigned);       // 0x00F2EC10
void  __cdecl set_capacity_18(void*, unsigned);         // 0x00F2ADA0
void  __cdecl Erase27e0(void*, void*, void*);           // 0x00F2F2E0
void  __cdecl elem_reset(void*, void*);                 // 0x00DFEE80
void* __cdecl map_lookup_lhs(void*, void*, void*);      // 0x00ED37C0 (map,key,el) -> element
void  __cdecl elem_copy_44(void*, void*);               // 0x00DFCB00 vector<0x44>::operator=
void* __cdecl eastl_copy(void*, void*, void*);          // 0x00DFB930
void  __cdecl pod_array_dtor(void*, void*, unsigned);   // 0x00DFAAF0
bool  __cdecl check_something(void*);                   // 0x00F278F0
struct B3D8C0 { void __thiscall init(); };              // 0x00B3D8C0 (some ctor)
float __cdecl SqrtF(float);                             // inlined sqrt (x87 fsqrt)
float __cdecl AreaRect(float, float);                   // 0x00f301e0 (s00f2f830_fast.cpp)
bool  __cdecl ReadInt32(void*, void*, int, int);        // 0x0093A780

// --- data -------------------------------------------------------------------
extern void* g_15af500;              // 0x015AF500
extern float g_15b0120;              // 0x015B0120
extern float g_15b00c4;              // 0x015B00C4
extern float g_15b00c8;              // 0x015B00C8
extern float g_15b011c;              // 0x015B011C
extern float g_1485378;              // 0x01485378
extern float g_1582f3c;              // 0x01582F3C
extern float g_1550ac4;              // 0x01550AC4
extern const char g_simName[];       // 0x013F09B4 "Simulator"
extern void* g_1897c18;              // 0x01897C18
extern int g_13f94d4;                // 0x013F94D4

// ---------------------------------------------------------------------------
// Readable little helpers over the raw object.
static inline int&  RI(void* p, int off) { return *(int*)((char*)p + off); }
static inline int&  RI(int p, int off) { return *(int*)((char*)p + off); }
static inline char& RB(void* p, int off) { return *(char*)((char*)p + off); }
static inline char& RB(int p, int off) { return *(char*)((char*)p + off); }
// vtable function-pointer fetch: (*(void***)obj)[off/4]
static inline void* vfn(void* obj, int off) { return (void*)((char*)(*(void**)obj) + off); }

// The serializer block used locally (0x34 bytes on stack).
struct VarListSerializer { char pad[0x34]; };

struct PairBlock;

// The scenario object; only the offsets this slice touches matter.
struct Scenario {
    bool SerializeAll(void* stream);
    bool LoadFrom(void* stream);
};

// ---------------------------------------------------------------------------
// @ 0x00f2f830
bool Scenario::SerializeAll(void* stream)
{
    char* self = (char*)this;
    VarListSerializer v;
    cVarListSerializer_Construct(&v, self, &g_15af500, 0x1a80d26);
    char ok = (char)cVarListSerializer_Serialize(&v, stream);

    if (RI(self, 0x2bf4) == RI(self, 0x2bf8)) {
        set_capacity_27e8((char*)self + 0x2c6c,
                          (unsigned)((RI(self, 0x2c70) - RI(self, 0x2c6c)) / 0x27e0));
        int n = (RI(self, 0x2c70) - RI(self, 0x2c6c)) / 0x27e0;
        int count = 0;
        for (; count < n; ++count) {
            int el = count * 0x27e0 + RI(self, 0x2c6c);
            void* slot = map_lookup_lhs((char*)self + 0x2bf4, &count, (void*)el);
            elem_reset(slot, (void*)el);
        }
        Erase27e0((char*)self + 0x2c6c, (void*)RI(self, 0x2c6c), (void*)RI(self, 0x2c70));
    }

    if (RI(self, 0x178) == RI(self, 0x17c) &&
        RI(self, 0x2c80) != RI(self, 0x2c84)) {
        set_capacity_18((char*)self + 0x2c80,
                        (unsigned)((RI(self, 0x2c84) - RI(self, 0x2c80)) / 0xc));
        int n = (RI(self, 0x2c84) - RI(self, 0x2c80)) / 0xc;
        int dst = 0;
        for (int i = 0; i < n; ++i) {
            unsigned* out = (unsigned*)(RI(self, 0x178) + dst);
            unsigned* src = (unsigned*)(RI(self, 0x2c80) + i * 0xc);
            out[0] = src[0];
            out[1] = src[1];
            out[2] = src[2];
            dst += 0x38;
            RI(self, 0x2c84) += ((RI(self, 0x2c84) - RI(self, 0x2c80)) / 0xc) * 0xc;
        }
    }

    // Object type id dispatch: several refresh passes.
    if ((*(unsigned(__thiscall**)(void*))vfn(stream, 0x3c))(stream) < 6) {
        int i0 = 0, d0 = 0, d1 = 0;
        for (;;) {
            if ((RI(self, 0x240) - RI(self, 0x23c)) / 0x534 == i0) break;
            int obj = RI(self, 0x23c) + d0;
            int j = 0, off = 0;
            for (;;) {
                if ((RI(obj, 0x88) - RI(obj, 0x84)) / 0x188 == j) break;
                int* e = (int*)(RI(obj, 0x84) + off);
                if (*e == 2) {
                    void* m = (void*)map_lookup_lhs((char*)self + 0x2bf4, e + 1, 0);
                    if (!check_something((void*)(RI(m, 0x70) + d1 + 0x170))) {
                        elem_copy_44((void*)(d1 + 0x170 + RI((void*)map_lookup_lhs((char*)self + 0x2bf4, e + 1, 0), 0x70)),
                                     e + 6);
                    }
                }
                ++j; off += 0x188;
            }
            ++i0; d1 += 0x4e0; d0 += 0x534;
            if (d0 >= 0x1a04) break;
        }
    }

    if ((*(unsigned(__thiscall**)(void*))vfn(stream, 0x3c))(stream) < 0xf) {
        int i0 = 0, d0 = 0, d1 = 0;
        for (;;) {
            if ((RI(self, 0x240) - RI(self, 0x23c)) / 0x534 == i0) break;
            int obj = RI(self, 0x23c) + d0;
            int j = 0, off = 0;
            for (;;) {
                if ((RI(obj, 0x88) - RI(obj, 0x84)) / 0x188 == j) break;
                int* e = (int*)(RI(obj, 0x84) + off);
                if (*e == 2) {
                    void* m = (void*)map_lookup_lhs((char*)self + 0x2bf4, e + 1, 0);
                    if (!check_something((void*)(RI(m, 0x70) + d1 + 0x170))) {
                        unsigned* dst = (unsigned*)(RI((void*)map_lookup_lhs((char*)self + 0x2bf4, e + 1, 0), 0x70) + d1 + 0x170);
                        elem_copy_44(dst, e + 6);
                        unsigned* q = (unsigned*)(RI((void*)map_lookup_lhs((char*)self + 0x2bf4, e + 1, 0), 0x70) + d1 + 0x170);
                        unsigned lo = q[0];
                        unsigned hi = q[1];
                        unsigned* ne = (unsigned*)eastl_copy((void*)hi, (void*)hi, (void*)lo);
                        pod_array_dtor(q, ne, q[1]);
                        q[1] += ((q[1] - lo) / 0x44) * 0x44;
                    }
                }
                ++j; off += 0x188;
            }
            ++i0; d1 += 0x4e0; d0 += 0x534;
            if (d0 >= 0x1a04) break;
        }
    }

    if ((*(unsigned(__thiscall**)(void*))vfn(stream, 0x3c))(stream) < 0xe) {
        unsigned b = (unsigned)(RB(self, 0x64) != 0);
        RI(self, 0x68) = b;
        RI(self, 0x6c) = b;
        RI(self, 0x70) = b;
        RI(self, 0x74) = b;
        RB(self, 0x64) = 0;
    }

    if ((*(unsigned(__thiscall**)(void*))vfn(stream, 0x3c))(stream) < 0xf) {
        RI(self, 0x130) = RI(self, 0x2c94);
        RI(self, 0x134) = RI(self, 0x2c98);
        RI(self, 0x138) = RI(self, 0x2c9c);
        RI(self, 0x2c94) = 0;
        RI(self, 0x140) = RI(self, 0x2ca0);
        RI(self, 0x144) = RI(self, 0x2ca4);
        RI(self, 0x2c98) = 0;
        RI(self, 0x2c9c) = 0;
        RI(self, 0x2ca0) = -1;
        RI(self, 0x2ca4) = -1;
    }

    return ok != 0;
}

// @ 0x00f2fda0
bool Scenario::LoadFrom(void* stream)
{
    char* self = (char*)this;
    (*(void(__thiscall**)(void*, int))vfn(stream, 0x24))(stream, 0);
    int tag = 0;
    int ver = 0;
    bool ok = ReadInt32(stream, &tag, 1, 1);
    if (ok) ok = ReadInt32(stream, &ver, 1, 1);
    if (tag != (int)0xb523d4f9 || ver < 3) return false;
    RI(self, 0x2ca8) = ver;

    ok = ok && (*(bool(__thiscall**)(void*, void*))vfn((char*)self + 0x18, 0x3c))(
                    (char*)self + 0x18, stream);

    void* blk = 0;
    unsigned u0 = 0, u1 = 0;
    if (ok) {
        ok = ReadInt32(stream, &u0, 1, 1);
        if (ok) ok = ReadInt32(stream, &u1, 1, 1);
    }

    void* ms = 0;
    void* p = EA_Allocate(0x18, g_simName, 0, 0, 0, 0);
    if (p) { ms = memstream_ctor(p, 0, 0); if (ms) (*(void(__thiscall**)(void*))vfn(ms, 4))(ms); }

    void* packed = 0;
    void* dpf = EA_Trace_ZoneObject_new(0x388, (int)g_simName, 0);
    if (dpf) {
        packed = DatabasePackedFile_ctor(dpf, 0, 0);
        if (packed) (*(void(__thiscall**)(void*))vfn((char*)packed + 4, 0))((char*)packed + 4);
    }

    byte_vector_ctor(0, 0);

    ok = ok && (*(int(__thiscall**)(void*, void*, int))vfn(stream, 0x30))(stream, blk, 0) == 0;
    if (ok) ok = memstream_SetData(blk, 0, 0);
    if (ok) ok = (*(bool(__thiscall**)(void*, void*))vfn(packed, 0x50))(packed, ms);
    if (ok) ok = (*(bool(__thiscall**)(void*))vfn(packed, 4))(packed);

    void* odb = 0;
    void* po = EA_Trace_ZoneObject_new(0x24, (int)g_simName, 0);
    if (po) { odb = cObjectDatabase_ctor(po, packed); if (odb) (*(void(__thiscall**)(void*))vfn(odb, 0))(odb); }

    if (ok) {
        if ((*(bool(__thiscall**)(void*))vfn((char*)odb + 4, 4))((char*)odb + 4) &&
            (*(bool(__thiscall**)(void*, int, int))vfn((char*)odb + 4, 0x3c))((char*)odb + 4, 1, 0)) {
            cVarListSerializer_ctorA((char*)odb + 4, &g_1897c18, &g_1897c18, &g_1897c18, 0);
            cVarListSerializer_a(&u0);
            cVarListSerializer_b(&u1);
            (*(void(__thiscall**)(void*, void*))vfn((char*)odb + 4, 0x20))((char*)odb + 4, ms);
            bool r1 = SerializeAll(stream);
            bool r2 = (*(bool(__thiscall**)(void*))vfn((char*)odb + 4, 0x1c))((char*)odb + 4);
            bool r3 = (*(bool(__thiscall**)(void*))vfn((char*)odb + 4, 8))((char*)odb + 4);
            bool result = r1 && r2 && r3;
            cVarListSerializer_dtor((char*)odb + 4);
            (*(void(__thiscall**)(void*))vfn((char*)odb + 4, 4))((char*)odb + 4);
            if (packed) (*(void(__thiscall**)(void*))vfn((char*)packed + 4, 4))((char*)packed + 4);
            if (ms) (*(void(__thiscall**)(void*))vfn(ms, 8))(ms);
            if (blk && RI((char*)blk - 4, 0)) EA_Delete(blk);
            return result;
        }
    }

    if (odb) (*(void(__thiscall**)(void*))vfn((char*)odb + 4, 4))((char*)odb + 4);
    if (packed) (*(void(__thiscall**)(void*))vfn((char*)packed + 4, 4))((char*)packed + 4);
    if (ms) (*(void(__thiscall**)(void*))vfn(ms, 8))(ms);
    if (blk && RI((char*)blk - 4, 0)) EA_Delete(blk);
    return false;
}

// @ 0x00f300d0
bool __cdecl Scenario_TryLoad(void* a, void* obj, void* c, unsigned id)
{
    if (id == 0x191c3c61 || id == 0xe22261b7) return false;
    if (!obj) return false;
    void* h = (*(void*(__thiscall**)(void*, unsigned))vfn(obj, 0xc))(obj, 0xe742574a);
    if (!h) return false;
    void* stream = (*(void*(__thiscall**)(void*))vfn(obj, 0x18))(obj);
    return ((Scenario*)h)->LoadFrom(stream);
}

// @ 0x00f301e0  -- AreaRect lives in s00f2f830_fast.cpp (needs /fp:fast).

// @ 0x00f30210
struct PairBlock {
    void* p0;                // +0x00
    void* p1;                // +0x04
    unsigned payload[0x1f];  // +0x08 .. +0x84
    void __thiscall ctor(void* p0, void* p1, const void* src);
    void __thiscall dtor();
};

// @ 0x00f30210
void PairBlock::ctor(void* p0, void* p1, const void* src)
{
    this->p0 = 0;
    this->p1 = 0;
    ((B3D8C0*)((char*)this + 8))->init();
    if (p0 != this->p0) {
        if (p0) (*(void(__thiscall**)(void*))vfn(p0, 0))(p0);
        void* old = this->p0;
        this->p0 = p0;
        if (old) (*(void(__thiscall**)(void*))vfn(old, 4))(old);
    }
    if (p1 != this->p1) {
        if (p1) (*(void(__thiscall**)(void*))vfn(p1, 0))(p1);
        void* old = this->p1;
        this->p1 = p1;
        if (old) (*(void(__thiscall**)(void*))vfn(old, 4))(old);
    }
    unsigned* d = this->payload;
    const unsigned* s = (const unsigned*)src;
    for (int i = 0x1f; i != 0; --i) *d++ = *s++;
}

// @ 0x00f307e0
void PairBlock::dtor(void)
{
    void* a = this->p1;
    if (a) (*(void(__thiscall**)(void*))vfn(a, 4))(a);
    void* b = this->p0;
    if (b) (*(void(__thiscall**)(void*))vfn(b, 4))(b);
}

// --- helpers used by the 00f30290 / 00f305d0 touch-damage pair --------------
void* __cdecl SP_normalized_safe(void* out, const float* a, const float* b);   // 0x00449C20
void  __cdecl RayCastParts(const float*, const float*, void*, unsigned*, float*, float*, float*); // 0x009B6450
void  __cdecl HitBody(void*, unsigned, const float*, unsigned, bool, float);   // 0x009BB680
void  __cdecl RefHolder_Release(void*);                                        // 0x00AE6670
void* __cdecl vfy_00c9f330(void*);                                             // 0x00C9F330
float __cdecl SqrtF(float x);

float __cdecl SqrtF(float x)
{
    float r;
    __asm { fld dword ptr [x] }
    __asm { fsqrt }
    __asm { fstp dword ptr [r] }
    return r;
}

// @ 0x00f30290
void __cdecl Scenario_TouchDamage(int* a, int* b, int, int, float* dir, int,
                                  float* p7, int, float* nrm, int, float scale)
{
    float vx = dir[0], vy = dir[1], vz = dir[2];
    float n2 = (vx * vx + vy * vy) + vz * vz;
    if (n2 <= g_15b011c) return;
    if ((nrm[2] * vz + nrm[1] * vy) + nrm[0] * vx <= g_1485378) return;

    bool hitPred = false;
    if (RB(b, 0xb5e) == 0) {
        (*(void(__thiscall**)(int*))(*a + 0x20))(a);
        int h1 = (*(int(__thiscall**)(int*, unsigned))(*a + 0xc))(a, 0x398420d);
        int h2 = (*(int(__thiscall**)(int*, unsigned))(*a + 0xc))(a, 0x137e8e0);
        if (h2 == 0) {
            hitPred = false;
        } else {
            int pa = (*(int(__thiscall**)(int*))(*a + 0x4c))(a);
            int pb = (*(int(__thiscall**)(int*))(*b + 0x4c))(b);
            hitPred = (pa != pb);
        }
        if (h2 != 0) vfy_00c9f330((void*)h2);

        if ((h1 != 0 || hitPred) && g_15b0120 < n2 && g_15b00c4 < scale) {
            float amount = (g_15b00c8 * n2) * scale;
            if (amount > 0.0f) {
                int* owner;
                if (h1 == 0) { owner = 0; }
                else { owner = (int*)RI((void*)h1, 0x10c); }
                if (!(h1 == 0) && owner != 0) {
                    (*(void(__thiscall**)(int*))(*owner + 100))(owner);
                }
                unsigned id;
                if (owner == 0) id = 0xffffffff;
                else id = (*(unsigned(__thiscall**)(int*))(*owner + 0x10))(owner);
                float tmp[3];
                void* out = SP_normalized_safe(tmp, dir, (const float*)owner);
                (*(void(__thiscall**)(int, unsigned, int, void*))(*(int*)(b[0x16a]) + 0x18))(
                    b[0x16a], *(unsigned*)&amount, 6, out);
                if (tmp[0] != 0.0f) RefHolder_Release(0);
            }
        }
    }

    if (RB((char*)b + 0xc0, 0) == 0) return;
    int* anim = (int*)RI(b, 0xb54);
    if (anim == 0) return;
    if (RI(anim, 0x17c) == 0) return;
    if ((*(int(__thiscall**)(int*))(*a + 0x20))(a) == 0x3a2511e) return;

    float base[3];
    base[0] = dir[0];
    base[1] = dir[1];
    base[2] = dir[2];
    float out[3];
    float* n = (float*)SP_normalized_safe(out, nrm, 0);
    float nb[3];
    nb[0] = n[0]; nb[1] = n[1]; nb[2] = n[2];
    float store = 0.0f;
    RayCastParts(base, nb, (void*)RI(anim, 0x17c), (unsigned*)&store, 0, 0, 0);

    float* pmin = &g_1582f3c;
    float len = SqrtF(n2);
    if (g_1582f3c <= len) pmin = &len;
    float k = *pmin;
    nb[0] *= k; nb[1] *= k; nb[2] *= k;

    HitBody((void*)RI(anim, 0x17c), (unsigned)store, (const float*)0, (unsigned)0,
            (bool)0, g_1550ac4);
}

// @ 0x00f305d0
void __cdecl Scenario_Impact(int* a, int* b, int, float* pa, float* dir,
                             float scale, int, int, float* pb, float* n2, int)
{
    float a0 = n2[0], a1 = n2[1], a2 = n2[2];
    float d0 = dir[0], d1 = dir[1], d2 = dir[2];

    float ddx = pa[0] - pb[0], ddy = pa[1] - pb[1], ddz = pa[2] - pb[2];
    if ((ddz * ddz + ddx * ddx) + ddy * ddy <= g_15b0120) return;

    int* q0 = 0;
    int e1 = (a == 0) ? 0 : (*(int(__thiscall**)(int*, unsigned))(*a + 0xc))(a, 0x398420d);
    int e2 = (b == 0) ? 0 : (*(int(__thiscall**)(int*, unsigned))(*b + 0xc))(b, 0x398420d);
    if (a != 0) q0 = (int*)(*(int(__thiscall**)(int*, void*))(*a + 0xc))(a, (void*)&g_13f94d4);
    int* q1 = 0;
    if (b != 0) q1 = (int*)(*(int(__thiscall**)(int*, void*))(*b + 0xc))(b, (void*)&g_13f94d4);

    if (e1 != 0 && RB((void*)e1, 0xa5) == 0 && q1 != 0) {
        float f = AreaRect((a0 * a0 + a1 * a1) + a2 * a2, scale);
        if (f > 0.0f) {
            float tmp[3];
            void* out = SP_normalized_safe(tmp, dir, (const float*)q0);
            (*(void(__thiscall**)(int*, float, int, int, void*))(*(int*)q1 + 0x18))(q1, f, 0, 8, out);
        }
    }

    if (e2 != 0 && RB((void*)e2, 0xa5) == 0 && g_15b00c4 < scale && q0 != 0) {
        float f = AreaRect((d0 * d0 + d1 * d1) + d2 * d2, scale);
        if (f > 0.0f) {
            float tmp[3];
            void* out = SP_normalized_safe(tmp, n2, (const float*)q1);
            (*(void(__thiscall**)(int*, float, int, int, void*))(*(int*)q0 + 0x18))(q0, f, 0, 8, out);
        }
    }
}
