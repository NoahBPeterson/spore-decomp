// Slice s00a9a630 -- EA::Swarm particle-emitter storage and math helpers.
//
//  0x00a9a630  cElemVec::Insert(cElem* pos, const cElem* v)
//  0x00a9a7a0  cElemVec::push_back(const cElem* v)
//  0x00a9a7f0  cElemVector::operator=(const cElemVector&)
//  0x00a9a930  ReadEmitter(stream, version, char* obj)
//  0x00a9ae00  cTimedState::Advance(float dt)
//  0x00a9ae50  TransformPoint(const float* m, float* v)
//  0x00a9af40  ApproxAtan2(const float* p)
//  0x00a9aff0  WigglePoint(float t, const void* list, const float* a, float* b)
//  0x00a9b120  SpinPoint(int a1, const float* a2, const float* a3, float a4, void* a5)
//  0x00a9b1d0  cField::~cField()
//  0x00a9b270  cField::Reset(int)
//  0x00a9b410  cField::SetObject(void*)

typedef unsigned char byte;
#include <math.h>
#pragma intrinsic(sqrt)
#pragma intrinsic(fabs)

// ------------------------------------------------------------------ types
struct Vec3 {
    float x, y, z;
};

struct cElem {
    float w;        // +0x00
    float m[3];     // +0x04
    float v[3];     // +0x10
};

struct cElemVec {
    cElem* m_begin;     // +0x00
    cElem* m_end;       // +0x04
    cElem* m_cap;       // +0x08

    void Insert(cElem* pos, const cElem* v);
    void push_back(const cElem* v);
};

struct KeyDesc;

struct Vector2_s004d_f2d0 {
    float lo, hi;
};

// ---------------------------------------------------------------- externs
extern "C" void* __cdecl EAAllocate(unsigned size, const char* name, int flags,
                                    int a4, int a5, const char* where);  // 0xf473a0
extern "C" void __cdecl operator_delete__(void* p);                         // 0xf47380
extern "C" cElem* __cdecl FUN_00a99190(const cElem* first, const cElem* last,
                                       cElem* dst);                          // 0xa99190
extern "C" void __cdecl FUN_004aa350(int n, const void* src);                // 0x4aa350
extern "C" void* __cdecl eastl_vector_insert(void* dst, const void* src,
                                             unsigned bytes);                // 0x11e0744

// EA::IO readers
struct cStream;
extern "C" void __cdecl ReadInt32(cStream* s, void* out, int n, int a4);     // 0x93a780
extern "C" void __cdecl FUN_0093a6c0(cStream* s, void* out, int n);          // 0x93a6c0
extern "C" void __cdecl FUN_0093a800(cStream* s, void* out, int n, int a4);  // 0x93a800
extern "C" void __cdecl FUN_007d27d0(cStream* s, void* out);                 // 0x7d27d0
extern "C" void __cdecl FUN_007ed920(cStream* s, void* out);                 // 0x7ed920
extern "C" void __cdecl FUN_00a87f50(cStream* s, void* out);                 // 0xa87f50
extern "C" void __cdecl FUN_00a7b9a0(cStream* s, void* out);                 // 0xa7b9a0
extern "C" void __cdecl FUN_00a7ba10(cStream* s, void* out);                 // 0xa7ba10
extern "C" void __cdecl FUN_00a9a870(cStream* s, void* out);                 // 0xa9a870
extern "C" void __cdecl FUN_00a9a8d0(cStream* s, void* out);                 // 0xa9a8d0

extern "C" void __cdecl FUN_007cdbe0(void* out, const void* in);             // 0x7cdbe0
extern "C" double __cdecl FUN_007cdb90(void* in);                            // 0x7cdb90
struct cRWState {
    void Update(void* p);       // 0xa790a0
};
extern "C" void __cdecl FUN_00a790a0(void* state);                           // 0xa790a0
extern "C" void __cdecl FUN_00a79430(void* state, const void* key,
                                     const Vec3* v, bool flag);              // 0xa79430

extern "C" float DAT_01565424;      // angle scale constant
extern "C" float DAT_01678ffc;      // angle divisor constant
extern "C" float DAT_01678f38;      // wiggle frequency
extern "C" float DAT_01678fe8;      // wiggle wrap scale
extern "C" float DAT_01677840[];    // wiggle table (interleaved pairs)

// random
namespace EA { namespace Random {
struct RandomLinearCongruential {
    double RandomDoubleUniform();
};
}}
extern EA::Random::RandomLinearCongruential g_Random;

// @ 0x00a9a630
void cElemVec::Insert(cElem* pos, const cElem* v)
{
    cElem* end = m_end;

    if (end != m_cap) {
        if (pos >= (cElem*)this && pos < end)
            pos = (cElem*)((char*)pos + 0x1c);

        if (end != 0)
            *end = end[-1];

        cElem* dst = end;
        cElem* src = (cElem*)((char*)end - 0x1c);
        while (src != pos) {
            src = (cElem*)((char*)src - 0x1c);
            dst = (cElem*)((char*)dst - 0x1c);
            *dst = *src;
        }
        *pos = *v;
        m_end = (cElem*)((char*)m_end + 0x1c);
        return;
    }

    int n = (int)((end - m_begin)) / 0x1c;
    cElem* buf;
    if (n == 0) {
        n = 1;
    }
    else {
        n = n * 2;
        if (n == 0) {
            buf = 0;
            goto have;
        }
    }
    buf = (cElem*)EAAllocate((unsigned)(n * 0x1c), "EASTL", 0xd1, 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h");
have:
    cElem* p = FUN_00a99190(m_begin, pos, buf);
    if (p != 0)
        *p = *v;
    cElem* ne = FUN_00a99190(pos, m_end, (cElem*)((char*)p + 0x1c));
    if (m_begin != 0 && *(int*)((char*)m_begin - 4) != 0)
        operator_delete__((char*)m_begin - 4);
    m_end = ne;
    m_begin = buf;
    m_cap = (cElem*)((char*)buf + n * 0x1c);
}

// @ 0x00a9a7a0
void cElemVec::push_back(const cElem* v)
{
    cElem* p = m_end;
    if (p < m_cap) {
        m_end = (cElem*)((char*)p + 0x1c);
        if (p != 0) {
            p->w = v->w;
            p->m[0] = v->m[0];
            p->m[1] = v->m[1];
            p->m[2] = v->m[2];
            p->v[0] = v->v[0];
            p->v[1] = v->v[1];
            p->v[2] = v->v[2];
        }
        return;
    }
    Insert(p, v);
}

struct cElemVector {
    cElem     m_elem;               // +0x00
    float*    m_begin;              // +0x1c
    float*    m_end;                // +0x20
    char      m_pad24[0x28 - 0x24];
    void*     m_alloc;              // +0x28
    char      m_pad2c[0x30 - 0x2c];
    byte      m_30;                 // +0x30

    cElemVector* operator=(const cElemVector* src);
};

// @ 0x00a9a7f0
cElemVector* cElemVector::operator=(const cElemVector* src)
{
    m_elem = src->m_elem;
    FUN_004aa350((int)(src->m_end - src->m_begin) >> 2, src->m_alloc);
    unsigned bytes = (unsigned)((char*)src->m_end - (char*)src->m_begin);
    void* p = eastl_vector_insert(m_begin, src->m_begin, bytes);
    m_end = (float*)((char*)p + (bytes >> 2) * 4);
    m_30 = src->m_30;
    return this;
}

// @ 0x00a9a930
void __cdecl FUN_00a9a930(cStream* s, int version, void* obj)
{
    char* o = (char*)obj;
    int   tmp;

    ReadInt32(s, &tmp, 1, 0);
    *(int*)(o + 0x8) = 0;
    *(unsigned int*)(o + 0xc) = tmp & 0xff;
    ReadInt32(s, &tmp, 1, 0);
    *(unsigned int*)(o + 0x8) |= tmp;

    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x10, 8);
    ReadInt32(s, o + 0x18, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x1c, 8);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x24, 8);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x2c, 0xc);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x38, 0xc);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x44, 8);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x4c, 0xc);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x58, 0xc);
    ReadInt32(s, o + 0x64, 1, 0);
    FUN_007d27d0(s, o + 0x68);
    ReadInt32(s, o + 0x7c, 1, 0);
    ReadInt32(s, o + 0x80, 1, 0);
    FUN_007d27d0(s, o + 0x84);
    ReadInt32(s, o + 0x98, 1, 0);
    FUN_007d27d0(s, o + 0x9c);
    FUN_007d27d0(s, o + 0xb0);
    FUN_007d27d0(s, o + 0xc4);
    ReadInt32(s, o + 0xd8, 1, 0);
    ReadInt32(s, o + 0xdc, 1, 0);
    ReadInt32(s, o + 0xe0, 1, 0);
    ReadInt32(s, o + 0xe4, 1, 0);
    ReadInt32(s, o + 0xe8, 1, 0);
    ReadInt32(s, o + 0xec, 1, 0);
    FUN_007ed920(s, o + 0xf0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x104, 0xc);
    FUN_007d27d0(s, o + 0x110);
    ReadInt32(s, o + 0x124, 1, 0);
    ReadInt32(s, o + 0x128, 1, 0);
    if (version > 1)
        ReadInt32(s, o + 0x12c, 1, 0);
    ReadInt32(s, o + 0x130, 1, 0);
    FUN_0093a6c0(s, o + 0x134, 1);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x138, 0xc);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x144, 0xc);
    ReadInt32(s, o + 0x150, 1, 0);
    ReadInt32(s, o + 0x154, 1, 0);
    ReadInt32(s, o + 0x158, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x15c, 0xc);
    ReadInt32(s, o + 0x168, 1, 0);
    ReadInt32(s, o + 0x16c, 1, 0);
    FUN_00a9a870(s, o + 0x170);
    FUN_0093a6c0(s, o + 0x184, 1);
    FUN_0093a6c0(s, o + 0x185, 1);
    FUN_0093a6c0(s, o + 0x186, 1);
    FUN_0093a6c0(s, o + 0x187, 1);
    FUN_007ed920(s, o + 0x188);
    FUN_007d27d0(s, o + 0x19c);
    FUN_00a87f50(s, o + 0x1b0);
    ReadInt32(s, o + 0x1c4, 1, 0);
    ReadInt32(s, o + 0x1c8, 1, 0);
    ReadInt32(s, o + 0x1cc, 1, 0);
    ReadInt32(s, o + 0x1d0, 1, 0);
    ReadInt32(s, o + 0x1d4, 1, 0);
    ReadInt32(s, o + 0x1d8, 1, 0);
    ReadInt32(s, o + 0x1dc, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x1e0, 8);
    FUN_0093a800(s, o + 0x1e8, 1, 0);
    FUN_0093a800(s, o + 0x1f0, 1, 0);
    FUN_0093a800(s, o + 0x1f8, 1, 0);
    char* p = o + 0x200;
    for (int i = 2; i != 0; i--) {
        FUN_00a7b9a0(s, p);
        p += 0x34;
    }
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x268, 0xc);
    ReadInt32(s, o + 0x274, 1, 0);
    ReadInt32(s, o + 0x278, 1, 0);
    ReadInt32(s, o + 0x27c, 1, 0);
    (*(void (__thiscall**)(void*, void*, int))((char*)*(void**)s + 0x30))(s, o + 0x280, 0xc);
    FUN_00a7ba10(s, o + 0x28c);
    FUN_00a9a8d0(s, o + 0x2a8);
    ReadInt32(s, o + 0x2bc, 1, 0);
}

struct cTimedState {
    void Advance(float dt);
};

// @ 0x00a9ae00
void cTimedState::Advance(float dt)
{
    char*  s = (char*)this;
    float* p;
    int    i = 0;
    p = (float*)(s + 0xd8);

    do {
        *p = *p - dt;
        while (*p < 0.0f)
            ((cRWState*)p)->Update((char*)(*(int*)(s + 0xc) + 0x200 + i));
        i += 0x34;
        p += 6;
    } while (i < 0x68);
}

// @ 0x00a9ae50
void __cdecl FUN_00a9ae50(const float* m, float* v)
{
    float x = v[0];
    float y = v[1];
    float z = v[2];

    float w = 1.0f / (((m[3] * x + m[7] * y) + m[11] * z) + m[15]);

    v[0] = w * (((m[4] * y + m[8] * z) + m[0] * x) + m[12]);
    v[1] = w * (((m[1] * x + m[5] * y) + m[9] * z) + m[13]);
    v[2] = w * (((m[2] * x + m[6] * y) + m[10] * z) + m[14]);
}

// @ 0x00a9af40
double __cdecl FUN_00a9af40(const float* p)
{
    float b = (float)(fabs((double)p[1]) + 1.0e-10);
    float a = (float)fabs((double)p[0]);
    float r = (b - a) / (a + b);
    float angle = (0.9817f - (r * r) * 0.1963f) * r;

    if (p[0] < 0.0f)
        angle = DAT_01565424 * 3.0f - angle;
    else
        angle = DAT_01565424 + angle;
    if (p[1] < 0.0f)
        angle = -angle;

    return (1.0 / DAT_01678ffc) * angle;
}

// @ 0x00a9aff0
void __cdecl FUN_00a9aff0(float t, const void* list, const float* a, float* b)
{
    float dx = b[0] - a[0];
    float dy = b[1] - a[1];
    float dz = b[2] - a[2];

    const cElem* begin = *(const cElem**)list;
    const cElem* end = *(const cElem**)((const char*)list + 4);

    for (const cElem* e = begin; e != end; e++) {
        float f = ((e->m[1] * dx + e->v[2] * dz) + e->m[2] * dy) + e->w * t;

        float g = DAT_01678f38 * f + 12582912.0f;
        int   bits = *(int*)&g;
        unsigned idx = (unsigned)bits & 0xf;

        float frac = f - (float)(bits + (int)0xb4c00000) * DAT_01678fe8;
        float s0 = DAT_01677840[idx * 2];
        float s1 = DAT_01677840[idx * 2 + 1];
        float s = (s1 - (s0 * frac) * 0.5f) * frac + s0;

        b[1] = b[1] + e->v[0] * s;
        b[0] = b[0] + e->m[0] * s;
        b[2] = e->v[1] * s + b[2];
    }
}

// @ 0x00a9b120
void __cdecl FUN_00a9b120(const void* a1, const float* a2, const float* a3,
                          float a4, void* a5)
{
    float vx = a2[0];
    float vy = a2[1];
    float vz = a2[2];

    float num = a3[1] * vx - a3[0] * vy;
    float len = (float)sqrt((double)(vy * vy + (vx * vx + vz * vz)));
    if (len > 0.0f)
        num = num / len;

    char* o = (char*)a5;
    float f = *(float*)(o + 0x44) -
              (*(float*)((char*)a1 + 0x27c) * *(float*)(o + 0x44)) * a4;
    *(float*)(o + 0x44) = f;
    *(float*)(o + 0x44) = f - (*(float*)((char*)a1 + 0x278) * num) * a4;
}

// ------------------------------------------------------------- field class
struct cField {
    void*           m_vtbl;         // 0x000
    char            m_pad04[0x0c - 0x04];
    void*           m_0c;           // 0x0c
    char            m_pad10[0x14 - 0x10];
    int             m_14;           // 0x14
    char            m_pad18[0x20 - 0x18];
    byte            m_20;           // 0x20
    byte            m_21;           // 0x21
    char            m_pad22[0xa0 - 0x22];
    double          m_a0;           // 0xa0
    byte            m_a8;           // 0xa8
    char            m_padA9[0xb0 - 0xa9];
    double          m_b0;           // 0xb0
    int             m_b8;           // 0xb8
    char            m_padBC[0xc8 - 0xbc];
    float           m_c8;           // 0xc8
    int             m_cc;           // 0xcc
    int             m_d0;           // 0xd0
    int             m_d4;           // 0xd4
    char            m_d8[0x124 - 0xd8];
    int             m_124;          // 0x124
    int             m_128;          // 0x128
    float           m_12c;          // 0x12c
    char            m_pad130[0x194 - 0x130];
    void*           m_194;          // 0x194
    void*           m_198;          // 0x198
    void*           m_19c;          // 0x19c
    char            m_pad1a0[0x248 - 0x1a0];
    void*           m_248;          // 0x248
    byte            m_24c;          // 0x24c

    void Destroy();
    void Reset(int arg);
    void SetObject(cField* obj);
};

// @ 0x00a9b1d0
void cField::Destroy()
{
    if (m_20 != 0) {
        void* v = *(void**)this;
        (*(void (__thiscall**)(void*, int))((char*)v + 0x0c))(this, 1);
    }
    if (m_194 != 0) {
        void* v = *(void**)m_194;
        (*(void (__thiscall**)(void*))((char*)v + 0x0c))(m_194);
        if (m_194 != 0) {
            void* o = m_194;
            m_194 = 0;
            void* ov = *(void**)o;
            (*(void (__thiscall**)(void*))((char*)ov + 0x04))(o);
        }
    }
    if (m_198 != 0) {
        void* v = *(void**)m_198;
        (*(void (__thiscall**)(void*))((char*)v + 0x0c))(m_198);
        if (m_198 != 0) {
            void* o = m_198;
            m_198 = 0;
            void* ov = *(void**)o;
            (*(void (__thiscall**)(void*))((char*)ov + 0x04))(o);
        }
    }
    if (m_19c != 0) {
        void* v = *(void**)m_19c;
        (*(void (__thiscall**)(void*))((char*)v + 0x0c))(m_19c);
        if (m_19c != 0) {
            void* o = m_19c;
            m_19c = 0;
            void* ov = *(void**)o;
            (*(void (__thiscall**)(void*))((char*)ov + 0x04))(o);
        }
    }
    m_0c = 0;
    m_14 = 0;
}

// @ 0x00a9b270
void cField::Reset(int arg)
{
    char* info = *(char**)((char*)this + 0xc);

    if (arg == 0)
        goto reset;
    if (*(int*)(info + 0x80) == 0)
        goto reset;
    if ((*(unsigned int*)(info + 8) >> 2) & 1)
        goto reset;
    if ((int)*(unsigned int*)(info + 8) < 0)
        goto reset;
    return;

reset:
    if (*(int*)(info + 0x128) >= 0) {
        m_b0 = 0.0;
        m_21 = 0;
        m_a0 = 0.0;
        m_20 = 1;
        m_b8 = 0;
        m_c8 = 0.0f;
        m_cc = *(int*)(info + 0x138);
        m_d0 = *(int*)(info + 0x13c);
        m_d4 = *(int*)(info + 0x140);

        if ((*(unsigned int*)(info + 8) >> 0x13) & 1) {
            Vec3 v;
            bool flag = (bool)((*(unsigned int*)(info + 8) >> 0x15) & 1);
            FUN_007cdbe0(&v, info + 0x2c);
            int i = 0;
            char* st = m_d8;
            do {
                char* base = *(char**)((char*)this + 0xc);
                FUN_00a79430(base + 0x200 + i, &v, (const Vec3*)st, flag);
                i += 0x34;
                st += 0x18;
            } while (i < 0x68);
        }

        info = *(char**)((char*)this + 0xc);
        if (*(float*)(info + 0x1c) < 0.0f) {
            if (*(float*)(info + 0x24) < 0.0f) {
                m_12c = 0.0f;
            }
            else {
                m_12c = (float)FUN_007cdb90(info + 0x24);
            }
        }
        else {
            double lo = (double)*(float*)(info + 0x1c);
            double hi = (double)*(float*)(info + 0x20);
            double r = g_Random.RandomDoubleUniform();
            double v = r * (hi - lo) + lo;
            if (hi <= v)
                m_12c = (float)hi;
            else if (v < lo)
                m_12c = (float)lo;
            else
                m_12c = (float)v;
        }

        m_124 = arg;
        m_128 = 0;
        m_a8 = (arg != 0) ? 1 : 0;
    }
}

// @ 0x00a9b410
void cField::SetObject(cField* n)
{
    cField* old = (cField*)m_248;

    if (n != old) {
        if (n != 0) {
            void* vt = *(void**)n;
            (*(void (__thiscall**)(void*))((char*)vt + 0x34))(n);
        }
        m_248 = n;
        if (old != 0) {
            void* vt = *(void**)old;
            (*(void (__thiscall**)(void*))((char*)vt + 0x38))(old);
            *(byte*)((char*)m_248 + 0x24c) = 1;
            return;
        }
        *(byte*)((char*)n + 0x24c) = 1;
        return;
    }
    *(byte*)((char*)old + 0x24c) = 1;
}
