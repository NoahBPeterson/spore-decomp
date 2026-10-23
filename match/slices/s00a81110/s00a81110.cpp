// Slice s00a81110 -- EA::Swarm::cSurfaceDecalManager::AddDecal and the neighbouring
// SurfaceDecal / cVisualEffect helpers in Swarm/SurfaceDecalManager.obj.
//
// The retail build's member offsets differ from the dev PDB (the PDB is one build off), so
// every function below is written against the offsets that appear in its own disassembly.
// Members used:
//   cSurfaceDecalManager retail: +0x10 mSurface, +0x14 mRenderer, +0x74 mSurfaceData,
//                                +0x84 mTextureToQuadSets, +0xa4 mQuadSets, +0xac mDecals
//   cVisualEffect       dev:     +0x10 mRefCount, +0x14 mName, +0x28 mEffectID, +0x2c mFlags,
//                                +0x74/+0xac/+0xe4/+0x11c the four cTransforms, +0x144 mComponentRecs
//
// Flags: /O2 /MD /Gy /EHsc /TP
// (x87 codegen.  SSE2 arch and fp fast change the FP shape and never help here -- nonmatching.txt)
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// ---------------------------------------------------------------- constant data
extern const float DAT_01485720;                       // 1.0f
extern const float DAT_01471064;                       // 0.5f
extern const float DAT_013eb1bc;
extern const float DAT_013f7120;
extern const float DAT_01485378;
extern const float DAT_013eb95c;                       // 3.0f
extern const float DAT_013eb8a0;                       // 0.25f
extern const float DAT_013eb8b0;                       // -0.0f / sign mask
extern const float DAT_0167790c;
extern const float DAT_0167776c, DAT_01677770, DAT_01677774;
extern const float DAT_01677a2c, DAT_01677a30, DAT_01677a34;
extern const float DAT_01677a04, DAT_01677a08, DAT_01677a0c;
extern const float DAT_016779fc, DAT_01677a00;
extern char  DAT_01677818[];                           // source Matrix3 for Matrix3::Assign
extern char  DAT_01677ad8[];                           // identity Matrix3
extern const char DAT_01457d88[];                      // "Swarm/SurfaceDecals"

struct Matrix3 { float m[9]; };                        // 0x24

// ---------------------------------------------------------------- external helpers
struct ExtCallees {
    void* __thiscall ctorCell();                       // 0x00a80920
    void* __thiscall ctorSurfaceDecals();              // 0x00a80ac0
    void* __thiscall mapInsert(u32 key);               // 0x00a810a0
    void* __thiscall mapFind(void** out, u32 key);     // 0x00a7bf40  (ret 8)
    void  __thiscall resize(int n);                    // 0x004c0410  (ret 4)
    void* __thiscall assign(const void* src);          // 0x00537dc0  (ret 4)
    void* __thiscall insert(void* pos, void** val);    // 0x00a80dd0  (ret 8)
};

extern "C" void* EAAllocate(u32 size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
extern "C" void  FUN_007cdbe0(float* out, float* box);                                 // 0x007cdbe0

struct RandomLCG { double __thiscall RandomDoubleUniform(); };   // 0x009360d0
extern RandomLCG g_sRandom;                                      // 0x016778dc

namespace EA { namespace Swarm {

// ---------------------------------------------------------------- class shells
class cVisualEffect {                                  // size 0x190 (dev layout)
public:
    int             Release();                         // 0x00a81d80
    unsigned __int64 GetEffectID();                    // 0x00a81db0
    void            Init(void* desc, int a, int b);    // 0x00a81e50
    void            Stop(int flag);                    // 0x00a82050
};

class cSurfaceDecalManager {                           // size 0xa8 (dev layout)
public:
    void* AddDecal(int unused, u32 key, const void* xform, float scale);  // 0x00a81110
    void  SetSurface(void* surface, void* transform);  // 0x00a81310
};

// SmoothStep helper, free function in the Swarm namespace.
float SmoothStepClamp(float x, float lo, float hi);    // 0x00a81de0

}} // namespace EA::Swarm

using EA::Swarm::cVisualEffect;
using EA::Swarm::cSurfaceDecalManager;

// ================================================================ AddDecal
// @ 0x00a81110  EA::Swarm::cSurfaceDecalManager::AddDecal
void* EA::Swarm::cSurfaceDecalManager::AddDecal(int /*unused*/, u32 key,
                                                const void* xform, float scale) {
    char* self = (char*)this;

    char* cell;
    void* mem = EAAllocate(0xa4, DAT_01457d88, 0, 0, 0, 0);
    if (mem) cell = (char*)((ExtCallees*)mem)->ctorCell();
    else     cell = 0;

    // intrusive list insert of `cell` into the list anchored at self+0xac (mDecals)
    {
        void* anchor = self + 0xac;
        void* next = *(void**)anchor;
        *(void**)(cell + 0x00) = next;
        *(void**)(cell + 0x04) = anchor;
        *(void**)anchor = cell;
        *(void**)((char*)*(void**)cell + 4) = cell;
    }

    void* map = self + 0x84;
    void* node = 0;
    ((ExtCallees*)map)->mapFind(&node, key);

    void** buckets = *(void***)((char*)map + 4);
    int    index   = *(int*)((char*)map + 8);
    if (node == buckets[index]) {
        // not found: create the quad set and register it
        char* sd;
        void* m2 = EAAllocate(0x40, DAT_01457d88, 0, 0, 0, 0);
        if (m2) sd = (char*)((ExtCallees*)m2)->ctorSurfaceDecals();
        else     sd = 0;

        void* anchor = self + 0xa4;                    // mQuadSets
        char* n2 = sd + 4;
        *(void**)(n2 + 0) = *(void**)anchor;
        *(void**)(sd + 8) = anchor;
        *(void**)anchor = n2;
        *(void**)((char*)*(void**)n2 + 4) = n2;

        void* slot = ((ExtCallees*)map)->mapInsert(key);
        *(void**)slot = sd;
        *(void**)(cell + 0x98) = sd;
    } else {
        *(void**)(cell + 0x98) = *(void**)((char*)node + 8);
    }

    // notify the renderer if the surface quad has not been created yet
    void* rend = *(void**)(self + 0x14);
    char* sd = *(char**)(cell + 0x98);
    if (rend != 0 && *(int*)(sd + 0xc) < 0) {
        void** vt = *(void***)rend;
        char ok = ((char(__thiscall*)(void*, void*, u32, void*))vt[6])(rend, sd, key, sd + 0xc);
        if (ok) {
            ((void(__thiscall*)(void*, void*, int))vt[9])(rend, *(void**)(sd + 0xc), 1);
            float box[6];
            box[0] = DAT_013eb1bc; box[1] = DAT_013eb1bc; box[2] = DAT_013eb1bc;
            box[3] = DAT_01485720; box[4] = DAT_01485720; box[5] = DAT_01485720;
            ((void(__thiscall*)(void*, void*, float*, int))vt[8])(rend, *(void**)(sd + 0xc), box, 0);
            ((void(__thiscall*)(void*, int, void*))vt[4])(rend, 0, sd + 0x10);
        }
    }

    // push the new cell onto the quad set's cell vector
    {
        char* vec = sd + 0x14;
        void* end = *(void**)(vec + 4);
        if (end < *(void**)(vec + 8)) {
            *(void**)(vec + 4) = (char*)end + 4;
            if (end) *(void**)end = cell;
        } else {
            void* tmp = cell;
            ((ExtCallees*)vec)->insert(end, &tmp);
            cell = (char*)tmp;
        }
    }

    char* xf = cell + 8;
    ((ExtCallees*)xf)->assign(xform);
    *(float*)(cell + 0x50) = scale;
    *(u16*)(cell + 0xa0) = 0xffff;
    *(float*)(cell + 0x70) = *(float*)(sd + 0x10);

    // this->vtable[5](xf)
    void** vt = *(void***)self;
    ((void(__thiscall*)(void*, void*))vt[5])(self, xf);
    return xf;
}

// ================================================================ SetSurface
// @ 0x00a81310  EA::Swarm::cSurfaceDecalManager::SetSurface
void EA::Swarm::cSurfaceDecalManager::SetSurface(void* surface, void* transform) {
    char* self = (char*)this;

    if (*(void**)(self + 0x10) != 0) {
        void* cur = *(void**)(self + 0x10);
        void** vt = *(void***)cur;
        ((void(__thiscall*)(void*, u32))vt[9])(cur, *(u32*)(self + 0x70));  // slot 0x24
        // clear the 0x70 vector: memmove(begin, end, 0) then end = begin
        *(void**)(self + 0x74) = *(void**)(self + 0x70);
    }

    void* old = *(void**)(self + 0x10);
    if (surface != old) {
        if (surface) ((void(__thiscall*)(void*))(*(void***)surface)[1])(surface);  // AddRef
        *(void**)(self + 0x10) = surface;
        if (old) ((void(__thiscall*)(void*))(*(void***)old)[0])(old);              // Release
    }

    void* s = *(void**)(self + 0x10);
    if (s == 0) return;

    int count = ((int(__thiscall*)(void*))(*(void***)s)[7])(s);                   // slot 0x1c
    char* vec = self + 0x70;
    ((ExtCallees*)vec)->resize(count);

    float* data = *(float**)(self + 0x70);
    void** vt = *(void***)s;
    if (transform != 0) {
        Matrix3 m1, m2;
        float v[3];
        v[0] = DAT_0167776c; v[1] = DAT_01677770; v[2] = DAT_01677774;
        m1 = *(Matrix3*)DAT_01677818;
        m2 = *(Matrix3*)DAT_01677818;
        ((void(__thiscall*)(void*, void*, Matrix3*, Matrix3*, float*))vt[8])(
            s, transform, &m1, &m2, data);
    } else {
        Matrix3 m1, m2;
        m1 = *(Matrix3*)DAT_01677818;
        m2 = *(Matrix3*)DAT_01677818;
        ((void(__thiscall*)(void*, void*, Matrix3*, Matrix3*, float*))vt[8])(
            s, self + 0x18, &m1, &m2, data);
    }
}

// ================================================================ trig table
// @ 0x00a81530  fill a 16-entry {sin,cos} table
void __fastcall FUN_00a81530(void* table) {
    float* t = (float*)table;
    float scale = DAT_01485720 / DAT_0167790c;
    for (int i = 0; i < 16; ++i) {
        float a = (float)i * scale;
        t[i * 2 + 0] = (float)sin((double)a);
        t[i * 2 + 1] = (float)cos((double)a);
    }
}

// ================================================================ 00a81580
// @ 0x00a81580  project `p` to the nearest point on/inside the box `box`, retrying while outside
float* FUN_00a81580(float* p, float* box) {
    float cx = (box[3] + box[0]) * 0.5f;
    float cy = (box[4] + box[1]) * 0.5f;
    float cz = (box[5] + box[2]) * 0.5f;
    float ex = box[3] - cx;
    float ey = box[4] - cy;
    float ez = box[5] - cz;
    ex *= ex; ey *= ey; ez *= ez;
    float ix = ex <= 0.0f ? 0.0f : 1.0f / ex;
    float iy = ey <= 0.0f ? 0.0f : 1.0f / ey;
    float iz = ez <= 0.0f ? 0.0f : 1.0f / ez;
    float dx, dy, dz;
    do {
        FUN_007cdbe0(p, box);
        dx = p[0] - cx;
        dy = p[1] - cy;
        dz = p[2] - cz;
    } while (1.0f < ix * (dx * dx) + iy * (dy * dy) + iz * (dz * dz));
    return p;
}

// ================================================================ 00a816d0
// @ 0x00a816d0  uniform point in the box `box`, written to `out`
void FUN_00a816d0(float* out, float* box) {
    float x, y, z;
    do {
        x = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        y = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        z = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
    } while (x * x + y * y + z * z > 1.0f);
    out[0] = ((box[3] - box[0]) * x + (box[0] + box[3])) * 0.5f;
    out[1] = ((box[4] - box[1]) * y + (box[1] + box[4])) * 0.5f;
    out[2] = ((box[5] - box[2]) * z + (box[2] + box[5])) * 0.5f;
}

// @ 0x00a817c0  point in the box biased to a shell of thickness `radius`
void FUN_00a817c0(float* out, float* box, float radius) {
    float x, y, z, len, t;
    do {
        x = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        y = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        z = (float)(g_sRandom.RandomDoubleUniform() * 2.0 - 1.0);
        len = sqrtf(x * x + y * y);
        t = len - 0.5f;
    } while (0.25f - t * t < z * z);
    float s = radius + (1.0f - radius) / sqrtf(x * x + y * y);
    out[0] = ((box[3] - box[0]) * (x * s) + (box[0] + box[3])) * 0.5f;
    out[1] = ((box[4] - box[1]) * (y * s) + (box[1] + box[4])) * 0.5f;
    out[2] = ((box[5] - box[2]) * (z * radius) + (box[2] + box[5])) * 0.5f;
}

// ================================================================ basis builders
// @ 0x00a818f0  build an orthonormal frame; rows 1..2 stored at out[3..8]
void FUN_00a818f0(float* in, float* out) {
    out[3] = in[0]; out[4] = in[1]; out[5] = in[2];
    float y  = in[1];
    float nx = -in[0];
    float len = sqrtf(nx * nx + y * y);
    float c0, c1, c2;
    if (len <= 0.0f) {
        out[0] = 0.0f; out[1] = 1.0f; out[2] = 0.0f;
        c0 = 1.0f; c1 = 0.0f; c2 = 0.0f;
    } else {
        float inv = 1.0f / len;
        float a = y * inv;
        float b = inv * nx;
        float c = inv * 0.0f;
        out[0] = a; out[1] = b; out[2] = c;
        c0 = in[2] * b - in[1] * c;
        c1 = in[0] * c - in[2] * a;
        c2 = in[1] * a - in[0] * b;
    }
    out[6] = c0; out[7] = c1; out[8] = c2;
}

// @ 0x00a81a20  build an orthonormal frame (second variant)
void FUN_00a81a20(float* in, float* out) {
    out[0] = in[0]; out[1] = in[1]; out[2] = in[2];
    float a = in[0];
    float b = -in[1];
    float len = sqrtf(a * a + b * b);
    float c0, c1, c2;
    if (len <= 0.0f) {
        out[3] = 1.0f; out[4] = 0.0f; out[5] = 0.0f;
        c0 = 0.0f; c1 = 1.0f; c2 = 0.0f;
    } else {
        float inv = 1.0f / len;
        float u = inv * b;
        float v = a * inv;
        float w = inv * -0.0f;
        out[3] = u; out[4] = v; out[5] = w;
        c0 = in[1] * w - in[2] * v;
        c2 = in[0] * v - in[1] * u;
        c1 = in[2] * u - in[0] * w;
    }
    out[6] = c0; out[7] = c1; out[8] = c2;
}

// @ 0x00a81b80  build an orthonormal frame (third variant)
void FUN_00a81b80(float* in, float* out) {
    out[6] = in[0]; out[7] = in[1]; out[8] = in[2];
    float ax = in[0], ay = in[1], az = in[2];
    if (fabsf(ay) < fabsf(ax)) {
        float nx = -ax;
        float nz = -az;
        float inv = 1.0f / sqrtf(nz * nz + nx * nx);
        float u = nx * inv;
        float v = inv * nz;
        float w = inv * -0.0f;
        out[3] = ay * u - az * w;
        out[4] = az * v - ax * u;
        out[0] = v;
        out[5] = ax * w - ay * v;
        out[1] = w;
        out[2] = u;
    } else {
        float ny = -ay;
        float inv = 1.0f / sqrtf(az * az + ny * ny);
        float u = az * inv;
        float v = ny * inv;
        float w = inv * 0.0f;
        out[0] = az * u - ay * v;
        out[1] = ax * v - az * w;
        out[3] = w;
        out[2] = ay * w - ax * u;
        out[4] = u;
        out[5] = v;
    }
}

// ================================================================ cVisualEffect
// @ 0x00a81d80  EA::Swarm::cVisualEffect::Release
int EA::Swarm::cVisualEffect::Release() {
    if (--*(int*)((char*)this + 0x10) > 0)
        return *(int*)((char*)this + 0x10);
    ((void(__thiscall*)(char*, int))(*(void***)((char*)this + 8))[0])((char*)this + 8, 1);
    return 0;
}

// @ 0x00a81db0  EA::Swarm::cVisualEffect::GetEffectID
unsigned __int64 EA::Swarm::cVisualEffect::GetEffectID() {
    return *(unsigned __int64*)((char*)this + 0x18);
}

static inline float SmoothClamp(float x, float lo, float hi) {
    x = x > lo ? x : lo;
    x = x < hi ? x : hi;
    return x;
}

// @ 0x00a81de0  EA::Swarm::SmoothStepClamp
float EA::Swarm::SmoothStepClamp(float x, float lo, float hi) {
    x = SmoothClamp(x, lo, hi);
    float r = hi - lo;
    float f = (x - lo) / r;
    return ((3.0f - (f + f)) * r) * f * f + lo;
}

// @ 0x00a81e50  EA::Swarm::cVisualEffect::Init
void EA::Swarm::cVisualEffect::Init(void* desc, int /*a*/, int /*b*/) {
    char* p = (char*)this;
    float one = DAT_01485720;

    *(u32*)(p + 0x28) = 0;
    *(u32*)(p + 0x44) = 0;

    *(Matrix3*)(p + 0x74) = *(Matrix3*)DAT_01677ad8;
    *(float*)(p + 0x70) = one;
    *(float*)(p + 0x64) = DAT_01677a2c;
    *(float*)(p + 0x68) = DAT_01677a30;
    *(float*)(p + 0x6c) = DAT_01677a34;
    *(u16*)(p + 0x62) = 0;
    *(u16*)(p + 0x60) = 0;

    *(Matrix3*)(p + 0xac) = *(Matrix3*)DAT_01677ad8;
    *(float*)(p + 0xa8) = one;
    *(float*)(p + 0x9c) = DAT_01677a2c;
    *(float*)(p + 0xa0) = DAT_01677a30;
    *(float*)(p + 0xa4) = DAT_01677a34;
    *(u16*)(p + 0x98) = 0;
    *(u16*)(p + 0x9a) = 0;

    *(Matrix3*)(p + 0xe4) = *(Matrix3*)DAT_01677ad8;
    *(float*)(p + 0xe0) = one;
    *(float*)(p + 0xd4) = DAT_01677a2c;
    *(float*)(p + 0xd8) = DAT_01677a30;
    *(float*)(p + 0xdc) = DAT_01677a34;
    *(u16*)(p + 0xd0) = 0;
    *(u16*)(p + 0xd2) = 0;

    *(Matrix3*)(p + 0x11c) = *(Matrix3*)DAT_01677ad8;
    *(float*)(p + 0x118) = one;
    *(float*)(p + 0x10c) = DAT_01677a2c;
    *(float*)(p + 0x110) = DAT_01677a30;
    *(float*)(p + 0x114) = DAT_01677a34;
    *(u16*)(p + 0x10a) = 0;
    *(u16*)(p + 0x108) = 0;

    *(float*)(p + 0x164) = DAT_013eb1bc;
    *(float*)(p + 0x16c) = DAT_013eb1bc;
    *(float*)(p + 0x54)  = one;

    *(void**)(p + 0x170) = desc;
    void** vt = *(void***)desc;
    *(float*)(p + 0x174) = ((float(__thiscall*)(void*))vt[11])(desc);   // slot 0x2c
    int kind = ((int(__thiscall*)(void*))vt[4])(desc);                  // slot 0x10

    if (kind == 1 || kind == 3) *(u32*)(p + 0x28) |= 1u;
    else                        *(u32*)(p + 0x28) &= ~1u;
    if (kind == 3)              *(u32*)(p + 0x28) |= 2u;
    else                        *(u32*)(p + 0x28) &= ~2u;

    *(float*)(p + 0x4c) = DAT_016779fc;
    *(float*)(p + 0x50) = DAT_01677a00;
    *(float*)(p + 0x2c) = DAT_01677a2c;
    *(float*)(p + 0x30) = DAT_01677a30;
    *(float*)(p + 0x34) = DAT_01677a34;
    *(float*)(p + 0x38) = DAT_01677a04;
    *(float*)(p + 0x3c) = DAT_01677a08;
    *(float*)(p + 0x40) = DAT_01677a0c;
}

// @ 0x00a82050  EA::Swarm::cVisualEffect::Stop
void EA::Swarm::cVisualEffect::Stop(int flag) {
    char* p = (char*)this;
    void* e = *(void**)(p + 0x28);
    if (e == 0) return;

    int b = flag;
    if (b == 0 && ((*(u32*)e >> 5) & 1)) b = 1;

    char* rec = *(char**)(p + 0x144);
    char* end = *(char**)(p + 0x148);
    for (; rec != end; rec += 0x5c) {
        void* c = *(void**)(rec + 0x38);
        ((void(__thiscall*)(void*, int))(*(void***)c)[3])(c, b);
    }

    if (b != 0) *(u32*)(p + 0x2c) &= 0xfffff9ffu;
    else        *(u32*)(p + 0x2c) |= 0x400u;
}
