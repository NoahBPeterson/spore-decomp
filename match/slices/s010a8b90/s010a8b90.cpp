// Slice s010a8b90: Spore/Havok narrowphase contact kernels.  Names are Claude-coined
// from usage and from the shared layout the five routines read.
//
// Layout model (offsets verified against every access in the disassembly):
//   Feature  0x34  one support/feature: plane-normal or point in m_v0 (+0x00), the
//                  companion plane-origin / surface-normal in m_v1 (+0x10), radius
//                  +0x20, margins +0x24/+0x28, normalised scale +0x2c, id +0x30.
//   Rec      0x0c  a 3-pointer collision record; m_p[1] is the sort-key feature.
//   Ctx      0x40  the contact-record set: m_recs[4] (+0x00), count (+0x30),
//                  the shape descriptor (+0x38) and the flag table (+0x3c).
//   Shape    0x4c  per-axis tolerances (+0x20), reference direction (+0x30) and the
//                  support-array base used by the index computation (+0x48).
//   IdTable  0x28  table->m_slots (+0x24) is the per-feature flag array base.
//
// Flags: /O2 /MD /Gy /TP (no /EHsc, no /arch:SSE, no /fp:fast) so the float math
// stays on x87 like the original.
#include "types.h"
#include <math.h>

// Shared float constants referenced by the x87 kernels.  They stay as externs so
// each operand encodes as a ds-relative displacement carrying a COFF relocation,
// exactly like the original (values read out of the retail image):
extern float kP1;       // 0x01485378   0.0f
extern float kP2;       // 0x014a2394   1.1920929e-07f  (FLT_EPSILON)
extern float kP3;       // 0x01485720   1.0f
extern float kP4;       // 0x013f9428   0.001f
extern float kP5;       // 0x01471064   0.5f
extern float kNegTiny;  // 0x013ef56c  -0.001f

// =============================================================================
// Shared layout
// =============================================================================

// Four-float output/point vector.
struct Vec4
{
    float x, y, z, w;
};

// One support feature.  The same object is addressed in a "plane" role (m_v0 is
// the plane normal, m_v1 the plane origin) and in a "point" role (m_v0 are the
// world coordinates, m_v1 the surface normal), which is why one layout serves both.
struct Feature
{
    float m_v0[4];      // +0x00  plane normal / point coordinates
    float m_v1[4];      // +0x10  plane origin / surface normal
    float m_radius;     // +0x20
    float m_marginA;    // +0x24
    float m_marginB;    // +0x28
    float m_scale;      // +0x2c
    int   m_id;         // +0x30
};

// A collision record: three features, only m_p[1] used as the sort key.
struct Rec
{
    Feature* m_p[3];    // +0x00  (stride 0x0c)
};

// Per-convex descriptor hung off the context at +0x38.
struct Shape
{
    char  m_pad0[0x20];
    float m_tol[4];     // +0x20  per-axis tolerance (xyz used)
    float m_dir[4];     // +0x30  reference direction (xyz used)
    char  m_pad1[0x8];
    char* m_base;       // +0x48  support-array base for the flag-index computation
};

// Flag table hung off the context at +0x3c.  +0x24 holds a base pointer kept as an
// int in the original; the kernels add a feature-relative byte offset to it.
struct IdTable
{
    char  m_pad0[0x24];
    char* m_slots;      // +0x24
};

// The contact-record context (also the object 010a8b90 sorts in place).
struct Ctx
{
    Rec      m_recs[4]; // +0x00
    int      m_count;   // +0x30
    char     m_pad0[4]; // +0x34
    Shape*   m_shape;   // +0x38
    IdTable* m_table;   // +0x3c
};

// Havok marks a support's entry in the shape's flag array.  The original computes
// the slot from the feature's byte position in the support array:
//   slot = table->m_slots + ((feature - shape->m_base) >> 6 << 4) + 0xc
inline void MarkFeature(Shape* pShape, IdTable* pTable, const void* pFeature, int value)
{
    char* pSlot = pTable->m_slots +
                  ((((char*)pFeature - pShape->m_base) >> 6) << 4) + 0xc;
    *(int*)pSlot = value;
}

// Squared length of the key vector, in 80-bit x87.  The original compares the two sums with a
// bare `fcompp` and never rounds either operand to float32, and the inputs routinely make the
// sum denormal (the support vectors hold raw small ints as float bits), so a float32-typed
// expression would round the sum to zero and flip the tie-break.  `long double` is MSVC's 80-bit
// x87 type on this target, so the expression is evaluated exactly like the original's.
inline long double LenSq(const Feature* pKey)
{
    return (long double)pKey->m_v1[0] * pKey->m_v1[0] +
           (long double)pKey->m_v1[1] * pKey->m_v1[1] +
           (long double)pKey->m_v1[2] * pKey->m_v1[2];
}

inline float Abs(float x)
{
    return x < 0.0f ? -x : x;
}

// =============================================================================
// Functions
// =============================================================================

// @ 0x010a8b90  ascending swell/selection sort over pCtx->m_recs.  For i = 1..n-1
// the pass pulls the smallest remaining record up to i-1: it scans j = i..n-1 and
// swaps recs[i-1] with recs[j] whenever recs[j]'s key sorts first.  Ordering is by
// the key feature's id; equal ids keep the shorter squared m_v1 vector first.
// Returns the fresh record count the original leaves in eax on both exit paths.
int FUN_010a8b90(Ctx* pCtx)
{
    Rec* p;
    Rec* q;
    int  i;
    int  j;

    if (pCtx->m_count <= 1)
        return pCtx->m_count;

    i = 1;
    p = pCtx->m_recs;
    while (i < pCtx->m_count)
    {
        j = i;
        q = p + 1;
        do
        {
            Feature* kb = q->m_p[1];
            Feature* ka = p->m_p[1];
            if (ka->m_id < kb->m_id)
                goto next;
            if (ka->m_id == kb->m_id)
            {
                if (LenSq(ka) < LenSq(kb))
                    goto next;
            }
            {
                Rec tmp = *p;
                *p = *q;
                *q = tmp;
            }
        next:
            ++j;
            ++q;
        } while (j < pCtx->m_count);
        ++i;
        ++p;
    }
    return pCtx->m_count;
}

// @ 0x010a8cb0  plane-side predicate.  Register ABI: ecx = point, eax = plane,
// edx = out bool; returns edx.  *pOut = 1 when dot(point - planeOrigin, planeNormal)
// is below -0.001, else 0.  Declared here with the register values as explicit
// parameters so the body is plain C++ (custom register ABI).
bool* FUN_010a8cb0(const Feature* pPoint, const Feature* pPlane, bool* pOut)
{
    float dx = pPoint->m_v0[0] - pPlane->m_v1[0];
    float dy = pPoint->m_v0[1] - pPlane->m_v1[1];
    float dz = pPoint->m_v0[2] - pPlane->m_v1[2];

    *pOut = (dz * pPlane->m_v0[2] + dy * pPlane->m_v0[1] + dx * pPlane->m_v0[0]) < kNegTiny;
    return pOut;
}

// @ 0x010a8cf0  x87 closest-point / penetration kernel.  Register ABI: ecx =
// pCollider, eax = pPoint, esi = pOut, [esp+4] = pCtx.  Computes the point on the
// collider's plane nearest the support point, walks it back onto the plane's
// toleranced disc, and writes the resulting world-space contact into pOut.
void FUN_010a8cf0(Feature* pCollider, Ctx* pCtx, Feature* pPoint, Vec4* pOut)
{
    float rad;      // collider radius
    float scale;    // collider normalised direction scale
    float margin;   // active margin (+0x24 or +0x28)
    float dx, dy, dz, dw;   // tangential part of (point - origin)
    float len2;     // |point - origin|^2
    float distSq;   // squared distance along the plane normal
    float proj;     // signed projection of (dy,dz,dw) onto the disc normal
    float invLen;   // 1/|disc normal|
    float nx, ny, nz;
    float tmp;
    int   outOrigin = 0;
    Shape* pShape;

    rad    = pCollider->m_radius;
    scale  = pCollider->m_scale;
    pShape = pCtx->m_shape;

    dx = pPoint->m_v0[0] - pCollider->m_v1[0];
    dy = pPoint->m_v0[1] - pCollider->m_v1[1];
    dz = pPoint->m_v0[2] - pCollider->m_v1[2];

    distSq = dx * pCollider->m_v0[0] +
             (dz * pCollider->m_v0[2] + dy * pCollider->m_v0[1]);
    len2 = dx * dx + (dy * dy + dz * dz);

    dx = dx - distSq * pCollider->m_v0[0];
    dy = dy - distSq * pCollider->m_v0[1];
    dz = dz - distSq * pCollider->m_v0[2];
    dw = (pPoint->m_v0[3] - pCollider->m_v1[3]) - distSq * pCollider->m_v0[3];
    distSq = distSq * distSq;

    if (dx * pShape->m_dir[0] +
        (dy * pShape->m_dir[1] + dz * pShape->m_dir[2]) <= kP1)
        margin = pCollider->m_marginB;
    else
        margin = pCollider->m_marginA;

    nx = 0.0f;
    ny = 0.0f;
    nz = 0.0f;
    invLen = 0.0f;
    proj = 0.0f;

    if (margin <= kP1)
    {
        if (len2 <= (rad * rad + kP3) * distSq)
            outOrigin = 1;
    }
    else
    {
        nx = pShape->m_dir[1] * pCollider->m_v0[2] - pShape->m_dir[2] * pCollider->m_v0[1];
        ny = pShape->m_dir[2] * pCollider->m_v0[0] - pShape->m_dir[0] * pCollider->m_v0[2];
        nz = pShape->m_dir[0] * pCollider->m_v0[1] - pCollider->m_v0[0] * pShape->m_dir[1];
        tmp = nx * nx + (ny * ny + nz * nz);
        if (kP2 < tmp)
        {
            invLen = kP3 / sqrtf(tmp);
            nx = nx * invLen;
            ny = ny * invLen;
            nz = nz * invLen;
            invLen = invLen * kP1;
            proj = nx * dx + (ny * dy + nz * dz);
            tmp = (rad * rad) * distSq;
            if ((proj * proj < tmp) != (proj * proj == tmp))
            {
                dx = dx - nx * proj;
                dy = dy - ny * proj;
                dz = dz - nz * proj;
                tmp = invLen * proj;
                proj = kP1;
                dw = dw - tmp;
            }
        }
        rad = ((margin + rad) * (margin + rad)) * distSq;
        distSq = (len2 - proj * proj) - distSq;
        if ((distSq < rad) != (distSq == rad))
        {
            if (proj == kP1)
            {
                outOrigin = 1;
            }
            else
            {
                dx = nx * proj;
                dy = ny * proj;
                dz = nz * proj;
                dw = invLen * proj;
            }
        }
    }

    if (outOrigin)
    {
        pOut->x = pCollider->m_v1[0];
        pOut->y = pCollider->m_v1[1];
        pOut->z = pCollider->m_v1[2];
        pOut->w = pCollider->m_v1[3];
        return;
    }

    if (scale < kP3)
    {
        rad = dx * dx + (dy * dy + dz * dz);
        if (kP2 <= rad && len2 * kP4 < rad)
        {
            scale = (kP3 - scale) * sqrtf(len2 / rad) + scale;
            tmp = (scale * dx) * pCollider->m_v0[0] +
                  ((dz * scale) * pCollider->m_v0[2] + (dy * scale) * pCollider->m_v0[1]);
            dx = scale * dx - tmp * pCollider->m_v0[0];
            dy = dy * scale - tmp * pCollider->m_v0[1];
            dz = dz * scale - tmp * pCollider->m_v0[2];
            dw = dw * scale - tmp * pCollider->m_v0[3];
        }
    }

    pOut->x = dx + pCollider->m_v1[0];
    pOut->y = dy + pCollider->m_v1[1];
    pOut->z = dz + pCollider->m_v1[2];
    pOut->w = dw + pCollider->m_v1[3];
}

// @ 0x010a90b0  x87 contact kernel B.  Register ABI: edi = pA, [esp+4] = pCtx,
// [esp+8] = pB, [esp+0xc] = pC, [esp+0x10] = pOut.  Builds the closest point
// between the two support features (pB, pA) and pC, falling back to two
// plane-side solves (010a8cf0) when the edge normal is degenerate.
void FUN_010a90b0(Ctx* pCtx, Feature* pB, Feature* pC, Vec4* pOut, Feature* pA)
{
    float f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13;
    int   bX, bY, bZ;
    Shape* pShape;

    f2 = pA->m_v0[2] * pB->m_v0[1] - pB->m_v0[2] * pA->m_v0[1];
    f4 = pB->m_v0[2] * pA->m_v0[0] - pA->m_v0[2] * pB->m_v0[0];
    f5 = pA->m_v0[1] * pB->m_v0[0] - pA->m_v0[0] * pB->m_v0[1];
    f3 = f2 * f2 + (f5 * f5 + f4 * f4);

    if (f3 > kP2)
    {
        f3 = kP3 / sqrtf(f3);
        f2 = f2 * f3;
        f4 = f4 * f3;
        f5 = f5 * f3;
        f6 = f3 * kP1;
        pShape = pCtx->m_shape;

        f7 = ((pB->m_v0[0] + pA->m_v0[0]) * f2 +
              ((pA->m_v0[2] + pB->m_v0[2]) * f5 +
               (pA->m_v0[1] + pB->m_v0[1]) * f4)) * kP5;
        f10 = pB->m_v1[0] * pB->m_v0[0] +
              (pB->m_v1[1] * pB->m_v0[1] + pB->m_v1[2] * pB->m_v0[2]);
        f8 = pA->m_v0[0] * pA->m_v1[0] +
             (pA->m_v1[1] * pA->m_v0[1] + pA->m_v1[2] * pA->m_v0[2]);

        f12 = ((pA->m_v0[2] * pB->m_v0[1] - pB->m_v0[2] * pA->m_v0[1]) * f7 +
               ((f5 * pA->m_v0[1] - f4 * pA->m_v0[2]) * f10 +
                (f4 * pB->m_v0[2] - f5 * pB->m_v0[1]) * f8)) * f3;
        f11 = ((pB->m_v0[2] * pA->m_v0[0] - pA->m_v0[2] * pB->m_v0[0]) * f7 +
               ((f2 * pA->m_v0[2] - f5 * pA->m_v0[0]) * f10 +
                (f5 * pB->m_v0[0] - f2 * pB->m_v0[2]) * f8)) * f3;
        f3  = ((f2 * pB->m_v0[1] - f4 * pB->m_v0[0]) * f8 +
               ((pA->m_v0[1] * pB->m_v0[0] - pA->m_v0[0] * pB->m_v0[1]) * f7 +
                (f4 * pA->m_v0[0] - f2 * pA->m_v0[1]) * f10)) * f3;

        bZ = Abs(f3)  < pShape->m_tol[2];
        bY = Abs(f11) < pShape->m_tol[1];
        bX = Abs(f12) < pShape->m_tol[0];
        if (bX && bY && bZ)
        {
            f7  = pC->m_v0[0] - f12;
            f9  = pC->m_v0[1] - f11;
            f8  = pC->m_v0[2] - f3;
            f10 = f9 * f9 + (f8 * f8 + f7 * f7);
            f13 = f2 * pShape->m_dir[0] +
                  (f5 * pShape->m_dir[2] + f4 * pShape->m_dir[1]);
            f7  = f7 * f2 + (f8 * f5 + f9 * f4);

            if (f7 * f13 <= kP1)
                f8 = pB->m_marginB + pA->m_marginB;
            else
                f8 = pB->m_marginA + pA->m_marginA;

            f9  = (f8 * f13 + (pB->m_radius + pA->m_radius)) * kP5;
            f13 = (pB->m_scale + pA->m_scale) * kP5;
            f8  = f7 * f7;

            if (f8 <= (f9 * f9) * (f10 - f8))
            {
                pOut->w = f6;
                pOut->x = f12;
                pOut->y = f11;
                pOut->z = f3;
                return;
            }

            if (f13 < kP3 && f10 * kP4 < f8)
                f7 = ((kP3 - f13) * (sqrtf(f10) * Abs(kP3 / f7)) + f13) * f7;

            pOut->x = f2 * f7 + f12;
            pOut->y = f4 * f7 + f11;
            pOut->z = f5 * f7 + f3;
            pOut->w = f6 * f7 + f6;
            return;
        }
    }

    MarkFeature(pCtx->m_shape, pCtx->m_table, pB, 2);
    MarkFeature(pCtx->m_shape, pCtx->m_table, pA, 2);

    if (pA->m_id < pB->m_id)
    {
        FUN_010a8cf0(pA, pCtx, pC, pOut);
        FUN_010a8cf0(pB, pCtx, (Feature*)pOut, pOut);
    }
    else
    {
        FUN_010a8cf0(pB, pCtx, pC, pOut);
        FUN_010a8cf0(pA, pCtx, (Feature*)pOut, pOut);
    }
}

// @ 0x010a9580  ray/SAT-style contact kernel.  Register ABI: eax = pA, ecx =
// pCollider, [esp+4] = pCtx, [esp+8] = pB, [esp+0xc] = p4, [esp+0x10] = p5,
// [esp+0x14] = pOut.  Intersects the support edge (pA, pB) with the collider plane;
// if that falls inside the shape tolerances it emits the contact directly,
// otherwise it sorts the context records and runs up to three 010a90b0 passes.
void FUN_010a9580(Feature* pCollider, Ctx* pCtx, Feature* pB, int p4, Feature* p5,
                  Vec4* pOut, Feature* pA)
{
    float f2, f3, f4, f5, f6, f7, f8, f9;
    int   bX, bY, bZ;
    int   snapshot;
    Shape* pShape;

    f2 = pB->m_v0[2] * pA->m_v0[1] - pA->m_v0[2] * pB->m_v0[1];
    f3 = pA->m_v0[2] * pB->m_v0[0] - pB->m_v0[2] * pA->m_v0[0];
    f7 = pA->m_v0[0] * pB->m_v0[1] - pB->m_v0[0] * pA->m_v0[1];
    f5 = f3 * pCollider->m_v0[1] +
         (f7 * pCollider->m_v0[2] + f2 * pCollider->m_v0[0]);

    if (kP2 <= Abs(f5))
    {
        f9 = pCollider->m_v0[0] * pCollider->m_v1[0] +
             (pCollider->m_v1[1] * pCollider->m_v0[1] +
              pCollider->m_v1[2] * pCollider->m_v0[2]);
        f6 = pA->m_v1[0] * pA->m_v0[0] +
             (pA->m_v1[1] * pA->m_v0[1] + pA->m_v1[2] * pA->m_v0[2]);
        f8 = pB->m_v0[0] * pB->m_v1[0] +
             (pB->m_v1[1] * pB->m_v0[1] + pB->m_v1[2] * pB->m_v0[2]);
        f5 = kP3 / f5;

        f4 = (f2 * f9 +
              ((pB->m_v0[1] * pCollider->m_v0[2] - pB->m_v0[2] * pCollider->m_v0[1]) * f6 +
               (pA->m_v0[2] * pCollider->m_v0[1] - pCollider->m_v0[2] * pA->m_v0[1]) * f8)) * f5;
        f3 = (f3 * f9 +
              ((pB->m_v0[2] * pCollider->m_v0[0] - pB->m_v0[0] * pCollider->m_v0[2]) * f6 +
               (pA->m_v0[0] * pCollider->m_v0[2] - pA->m_v0[2] * pCollider->m_v0[0]) * f8)) * f5;
        f2 = (f7 * f9 +
              ((pCollider->m_v0[1] * pB->m_v0[0] - pCollider->m_v0[0] * pB->m_v0[1]) * f6 +
               (pCollider->m_v0[0] * pA->m_v0[1] - pA->m_v0[0] * pCollider->m_v0[1]) * f8)) * f5;

        pShape = pCtx->m_shape;
        bX = Abs(f4) < pShape->m_tol[0];
        bY = Abs(f3) < pShape->m_tol[1];
        bZ = Abs(f2) < pShape->m_tol[2];
        if (bX && bY && bZ)
        {
            pOut->w = f5 * kP1;
            pOut->x = f4;
            pOut->y = f3;
            pOut->z = f2;
            return;
        }
    }

    if (p4 != 0)
    {
        FUN_010a8b90(pCtx);
        pCollider = pCtx->m_recs[0].m_p[1];
        pA = pCtx->m_recs[1].m_p[1];
        pB = pCtx->m_recs[2].m_p[1];
    }

    MarkFeature(pCtx->m_shape, pCtx->m_table, pCollider, 1);
    MarkFeature(pCtx->m_shape, pCtx->m_table, pA, 1);
    MarkFeature(pCtx->m_shape, pCtx->m_table, pB, 1);

    snapshot = pCtx->m_count;
    FUN_010a90b0(pCtx, pCollider, p5, pOut, pA);
    if (snapshot == pCtx->m_count)
        FUN_010a90b0(pCtx, pCollider, (Feature*)pOut, pOut, pB);
    if (snapshot != pCtx->m_count)
        return;
    FUN_010a90b0(pCtx, pA, (Feature*)pOut, pOut, pB);
}