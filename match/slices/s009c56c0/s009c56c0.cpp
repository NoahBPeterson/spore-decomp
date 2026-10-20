// slice s009c56c0 -- nSPCreatureAnim creature-mesh bookkeeping: body-mesh world
// state updates, the mesh-instance vector copy/fill/destroy helpers and a 3x3
// transpose.
//
//   009c56c0  creature_instance_data::creature_instance_data
//   009c5cb0  creature_mesh_instance_data::UpdateBodyShapes
//   009c5e90  UpdateBodyShapes2
//   009c6440  creature_mesh_instance_data::SetStateInWorld
//   009c6500  UcopyOut
//   009c6560  Ufill
//   009c65b0  UcopyRange
//   009c6600  DestroyRange
//   009c6660  Transpose3x3
//
// Retail offsets are used throughout (the dev PDB predates this build).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

typedef unsigned char uint8;
typedef unsigned int  uint32;

// --------------------------------------------------------------------- types

struct RefCounted {
    void* vptr;         // +0x00
    int   f04;          // +0x04
    char  pad08[0x38];  // +0x08
    int   refCount;     // +0x40
};

struct mesh_instance {
    float        x;      // +0x00
    float        y;      // +0x04
    float        z;      // +0x08
    RefCounted*  object; // +0x0c
    int          index;  // +0x10
};

struct cMWModel;

// One element of the body-shape list at +0xa8: flag word, three floats.
struct body_shape {
    int   flags;   // +0x00
    float a;       // +0x04
    float b;       // +0x08
    float c;       // +0x0c
};
// +0x04 holds a pointer to the model/pose object reached through the vtable.
// +0xa0 is the body-shape count, +0xa8 the array itself.

// creature_mesh_instance_data: only the members touched here.
struct creature_mesh_instance_data {
    char       pad00[0x04];  // +0x00
    void*      poseModel;    // +0x04
    cMWModel*  mesh_lo;      // +0x08
    char       pad0c[0x1c];  // +0x0c
    mesh_instance* bodyBegin; // +0x28
    mesh_instance* bodyEnd;   // +0x2c

    void SetStateInWorld(int, int, void* world);
    void UpdateBodyShapes(int body, int arg2, int arg3);
};

// Out-of-slice helpers.
void GetBonePos(void* self, float* out, int, int);            // 0x009cd580
void ConstructAt2f8(void* self);                              // 0x009e3ec0
void ConstructAt17a0(void* self, void* a, void* b);           // 0x009c1630

// The ground reference used by UpdateBodyShapes2 lives in the game's .data at
// 0x0166c350, where 0x01302200 stores (0,0,1,0) during startup.  It is read
// through that address (rather than copied here) so the projection keeps the
// original's load order, and its multiply-by-zero, instead of being folded away
// under /fp:fast.
#define g_upVector ((float*)0x0166c350)

// The three pose methods are thiscall members of the model object reached through
// +0x04; only the slots this slice calls are named.
struct shape_model {
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20();
    virtual void slot21(); virtual void slot22(); virtual void slot23();
    virtual void slot24(); virtual void slot25(); virtual void slot26();
    virtual void slot27(); virtual void slot28();                    // +0x70
    virtual void setValue(int body, int id, float v, int arg3);      // +0x74
    virtual void setWeight(int body, int id, float v, int arg3);     // +0x78
    virtual void slot31();                                           // +0x7c
    virtual void setRange(int body, int id, float* lo, float* hi,
                          int arg3);                                 // +0x80
};

// ------------------------------------------------------------------- helpers

// @ 0x009c6500
// Copies [first,last) to dest and writes the advanced destination into *out.
void UcopyOut(mesh_instance** out, mesh_instance* first, mesh_instance* last,
              mesh_instance* dest)
{
    *out = dest;
    if (first != last) {
        do {
            if (dest != 0) {
                dest->x = first->x;
                dest->y = first->y;
                dest->z = first->z;
                RefCounted* o = first->object;
                dest->object = o;
                if (o != 0)
                    ++o->refCount;
                dest->index = first->index;
            }
            first = (mesh_instance*)((char*)first + 0x14);
            dest = (mesh_instance*)((char*)dest + 0x14);
        } while (first != last);
        *out = dest;
    }
}

// @ 0x009c6560
// Fills count elements at dstBase with copies of *src.
void Ufill(mesh_instance* dstBase, unsigned count, const mesh_instance* src)
{
    if (count <= 0u)
        return;

    char* p = (char*)dstBase + 8;
    do {
        mesh_instance* dest = (mesh_instance*)(p - 8);
        if (dest != 0) {
            dest->x = src->x;
            dest->y = src->y;
            dest->z = src->z;
            RefCounted* o = src->object;
            dest->object = o;
            if (o != 0)
                ++o->refCount;
            dest->index = src->index;
        }
        --count;
        p += 0x14;
    } while (count > 0);
}

// @ 0x009c65b0
// Copies [first,last) to dest.
void UcopyRange(mesh_instance* first, mesh_instance* last, mesh_instance* dest)
{
    if (first == last)
        return;

    do {
        if (dest != 0) {
            dest->x = first->x;
            dest->y = first->y;
            dest->z = first->z;
            RefCounted* o = first->object;
            dest->object = o;
            if (o != 0)
                ++o->refCount;
            dest->index = first->index;
        }
        first = (mesh_instance*)((char*)first + 0x14);
        dest = (mesh_instance*)((char*)dest + 0x14);
    } while (first != last);
}

// @ 0x009c6600
// Releases every element of [first,last), returning dest advanced by the count.
mesh_instance* DestroyRange(mesh_instance* first, mesh_instance* last,
                            mesh_instance* dest)
{
    while (first != last) {
        RefCounted* obj = first->object;
        if (obj != 0) {
            if (obj->refCount > 1) {
                --obj->refCount;
            } else {
                unsigned flag = (unsigned)obj->f04 >> 31;
                void (__stdcall *release)(RefCounted*, unsigned) =
                    *(void (__stdcall **)(RefCounted*, unsigned))
                        ((char*)obj->vptr + 0x170);
                release(obj, flag);
            }
        }
        first = (mesh_instance*)((char*)first + 0x14);
        dest = (mesh_instance*)((char*)dest + 0x14);
    }

    return dest;
}

// @ 0x009c6660
// Row-major 3x3 transpose; returns dst (the original leaves it in eax).
float* Transpose3x3(float* dst, const float* src)
{
    float (*d)[3] = (float(*)[3])dst;
    const float (*s)[3] = (const float(*)[3])src;
    d[0][0] = s[0][0];
    d[1][0] = s[0][1];
    d[2][0] = s[0][2];
    d[0][1] = s[1][0];
    d[1][1] = s[1][1];
    d[2][1] = s[1][2];
    d[0][2] = s[2][0];
    d[1][2] = s[2][1];
    d[2][2] = s[2][2];
    return dst;
}

// ------------------------------------------- creature_instance_data (constructor)

// The full instance object is ~0x17b0 bytes; only the members touched below are
// named.  Two sub-objects are built in place, at +0x2f8 and at +0x17a0.
struct creature_instance_data {
    char pad00[0x14];
    int  flags14;                       // +0x14
    char pad18[0x17b0 - 0x18];
    void Clear(bool);                   // 0x009c4d40
    creature_instance_data();
};

// @ 0x009c56c0
creature_instance_data::creature_instance_data()
{
    ConstructAt2f8((char*)this + 0x2f8);
    char tmp[4];
    ConstructAt17a0((char*)this + 0x17a0, tmp, tmp);
    flags14 = 0;
    Clear(true);
}

// ------------------------------------------------------------- UpdateBodyShapes

// @ 0x009c5cb0
// Walks the per-bone body-shape list.  The first pass sums a scale so the second
// pass can turn every bone's scale into a 0..1 weight; each shape is then fed to
// three virtual pose calls (blend range, blended value, weight).
void creature_mesh_instance_data::UpdateBodyShapes(int body, int arg2, int arg3)
{
    float total = 0.0f;
    int count = *(int*)((char*)body + 0xa0);

    for (int i = 0; i < count; ++i) {
        body_shape* s = (body_shape*)((char*)body + 0xa8 + i * 0x14);
        if ((s->flags & 1) == 0)
            total += s->c;
    }

    for (int i = 0; i < count; ++i) {
        body_shape* s = (body_shape*)((char*)body + 0xa8 + i * 0x14);
        if (s->flags & 1)
            continue;

        int id = *(int*)((char*)s - 4);

        float angle;
        if (s->flags & 2) {
            // atan2 in turns, wrapped into [0,1)
            angle = atan2f(s->b, s->a) * 0.159154937f;
            if (angle < 0.0f)
                angle += 1.0f;
        } else {
            angle = s->a / (s->c + 9.99999994e-09f);
        }

        float weight;
        if (total > 0.0f)
            weight = s->c / total;
        else
            weight = 0.0f;

        shape_model* model = (shape_model*)poseModel;
        float lo, hi;
        model->setRange(arg2, id, &lo, &hi, arg3);
        model = (shape_model*)poseModel;
        model->setValue(arg2, id, lo + (hi - lo) * angle, arg3);
        model = (shape_model*)poseModel;
        model->setWeight(arg2, id, weight, arg3);
    }
}

// ------------------------------------------------------------ UpdateBodyShapes2

// @ 0x009c5e90
// Rotates the three basis rows of `m` (a 4x4 with the w column carried along)
// so that they lean `angle` away from the ground plane, after lifting them by the
// pose offset stored on `state`.
//
// The original normalises with rsqrtps plus two Newton-Raphson steps, so the
// reciprocal square root is reproduced here instead of with a divide.
static float rsqrt_fast(float x)
{
    float r = _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x)));
    r = (1.0f - (r * r) * x) * (r * 0.5f) + r;
    r = (1.0f - (r * r) * x) * (r * 0.5f) + r;
    return r;
}

// Dot product with the ground reference, written with SSE intrinsics so that the
// multiply by zero (and therefore 0*Inf/NaN) is not folded away under /fp:fast.
static float DotUp(float x0, float x1, float x2)
{
    __m128 s = _mm_mul_ss(_mm_set_ss(g_upVector[0]), _mm_set_ss(x0));
    s = _mm_add_ss(s, _mm_mul_ss(_mm_set_ss(g_upVector[1]), _mm_set_ss(x1)));
    s = _mm_add_ss(s, _mm_mul_ss(_mm_set_ss(g_upVector[2]), _mm_set_ss(x2)));
    return _mm_cvtss_f32(s);
}

void UpdateBodyShapes2(int, float* m, int, void* state)
{
    char* s = (char*)state;

    float v[3] = { 0.0f, 0.0f, 0.0f };
    GetBonePos(state, v, 0, 0);

    float vx = v[0] - *(float*)(s + 0x18);
    float vy = v[1] - *(float*)(s + 0x1c);
    float vz = v[2] - *(float*)(s + 0x20);

    float a = *(float*)(s + 0x3c);
    float b = *(float*)(s + 0x48);
    float c = *(float*)(s + 0x40);
    float d = *(float*)(s + 0x44);

    float nx = 2.0f * (((-(d * d) + -(c * c)) * vx + (c * a + d * b) * vy) +
                       (d * a - c * b) * vz) + vx;
    float ny = 2.0f * (((c * a - d * b) * vx + (-(d * d) + -(a * a)) * vy) +
                       (d * c + a * b) * vz) + vy;
    float nz = 2.0f * (((d * a + c * b) * vx + (-(c * c) + -(a * a)) * vz) +
                       (d * c - a * b) * vy) + vz;

    float r0x = m[0], r0y = m[1], r0z = m[2];
    float r1x = m[4], r1y = m[5], r1z = m[6];
    float r2x = m[8], r2y = m[9], r2z = m[10];

    // The ground reference is the world up vector (0,0,1) held in a runtime
    // initialised global, so the projection is written out as the original's
    // dot product (including its propagation of non-finite input components).
    float ux = DotUp(r0x, r1x, r2x);
    float uy = DotUp(r0y, r1y, r2y);
    float uz = DotUp(r0z, r1z, r2z);

    float len2 = uz * uz + uy * uy + ux * ux;
    float inv = rsqrt_fast(len2);
    ux *= inv;
    uy *= inv;
    uz *= inv;

    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;

    // The original's `comiss`/`jb` also takes this branch when the sum is
    // unordered (a NaN length), so the test is written the way the flags behave
    // rather than as a plain `n2 < 1e-8f`.
    float n2 = nz * nz + ny * ny + nx * nx;
    if (!(n2 >= 1.0e-8f)) {
        m00 = 1.0f; m01 = 0.0f; m02 = 0.0f;
        m10 = 0.0f; m11 = 1.0f; m12 = 0.0f;
        m20 = 0.0f; m21 = 0.0f; m22 = 1.0f;
    } else {
        float cx = uy * nz - uz * ny;
        float cy = uz * nx - ux * nz;
        float cz = ux * ny - uy * nx;

        float clen2 = cz * cz + cy * cy + cx * cx;
        float cinv = rsqrt_fast(clen2);
        cx *= cinv;
        cy *= cinv;
        cz *= cinv;

        float sn = sinf(0.523598790f);
        float cs = cosf(0.523598790f);
        float om = 1.0f - cs;

        float t0 = cy * om;
        float t1 = cx * om;
        float t2 = cz * om;

        m22 = cz * t2 + cs;
        m21 = cy * t2 - cx * sn;
        m12 = cz * t0 + cx * sn;
        m11 = cy * t0 + cs;
        m02 = cz * t1 - cy * sn;
        m01 = cy * t1 + cz * sn;
        m00 = cx * t1 + cs;
        m10 = cx * t0 - cz * sn;
        m20 = t2 * cx + cy * sn;
    }

    m[0] = (r0y * m10 + r0x * m00) + r0z * m20;
    m[1] = (r0y * m11 + r0x * m01) + r0z * m21;
    m[2] = (r0y * m12 + r0x * m02) + r0z * m22;
    m[3] = (r0y * m10 + r0x * m00) + r0z * m20;
    m[4] = (r1x * m00 + r1y * m10) + r1z * m20;
    m[5] = (r1x * m01 + r1y * m11) + r1z * m21;
    m[6] = (r1x * m02 + r1y * m12) + r1z * m22;
    m[7] = (r1x * m00 + r1y * m10) + r1z * m20;
    m[8] = (r2x * m00 + r2y * m10) + r2z * m20;
    m[9] = (r2x * m01 + r2y * m11) + r2z * m21;
    m[10] = (r2x * m02 + r2y * m12) + r2z * m22;
    m[11] = (r2x * m00 + r2y * m10) + r2z * m20;
}

// ------------------------------------------------------------- SetStateInWorld

// @ 0x009c6440
void creature_mesh_instance_data::SetStateInWorld(int, int, void* world)
{
    int n = (int)((char*)bodyEnd - (char*)bodyBegin) / 0x14;
    if (n != 0) {
        int count = n;
        int off = 0;
        do {
            mesh_instance* base = bodyBegin;
            if (*(cMWModel**)((char*)base + off + 0x0c) != 0) {
                cMWModel* model = *(cMWModel**)((char*)base + off + 0x0c);
                void* v = *(void**)model;
                void* t = *(void**)v;
                void (__stdcall *fn)(cMWModel*, void*) =
                    *(void (__stdcall **)(cMWModel*, void*))((char*)t + 0x16c);
                fn(model, world);
            }
            off += 0x14;
            --count;
        } while (count != 0);
    }

    if (mesh_lo != 0) {
        void* v = *(void**)mesh_lo;
        void* t = *(void**)v;
        void (__stdcall *fn)(cMWModel*, void*) =
            *(void (__stdcall **)(cMWModel*, void*))((char*)t + 0x16c);
        fn(mesh_lo, world);
    }
}
