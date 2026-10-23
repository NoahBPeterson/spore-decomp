// Slice s01112230 (Havok 4.x GSK: collide the swept points of one vertex against the
// plane of another).
//
//   0x01112230  hk4dGskCollideInitMatrices
//   0x01112490  hk4dGskCollidePointWithPlaneFinal
//   0x01112600  hk4dGskCollidePointsWithPlane
//
// Compile flags: /vc71 /O2 /MD /Gy /TP   (Havok 4.x, cl 13.10.3077)

#include <math.h>

typedef float hkReal;

class hkRotation;

class __declspec(align(16)) hkVector4
{
public:
    hkReal x, y, z, w;

    void setRotatedDir(const hkRotation& r, const hkVector4& v);             // 0x010814a0
    void setTransformedPos(const hkRotation& r, const hkVector4& v);         // 0x01081360
    void setRotatedInverseDir(const hkRotation& r, const hkVector4& v);      // 0x01081440
};

class __declspec(align(16)) hkMatrix3
{
public:
    hkVector4 m_col0, m_col1, m_col2;
};

class hkRotation : public hkMatrix3
{
};

class hkTransform
{
public:
    hkRotation m_rotation;      // 0x00
    hkVector4   m_translation;  // 0x30

    void setMulInverseMul(const hkTransform& a, const hkTransform& b);       // 0x010810f0
};

class hkSweptTransform
{
public:
    hkReal m_0x00;              // 0x00  start time
    hkReal m_0x04;              // 0x04
    hkReal m_0x08;              // 0x08  inverse delta time
    hkReal m_0x0c;              // 0x0c
};

class hkSweptTransformUtil
{
public:
    static void lerp2Ha(const hkSweptTransform& from, hkReal t0, hkReal t1,
                        hkTransform& to);                                    // 0x01209f50
};

struct hk4dGskVertexCollidePointsInput
{
    const void*  m_p0;          // 0x00  first swept shape (its transform is at +0x40)
    const void*  m_p1;          // 0x04  second swept shape (its hkVector4 is at +0x80)
    hkReal*      m_points;      // 0x08  4 floats per collide point
    int          m_numPoints;   // 0x0c
    hkReal       m_0x10;        // 0x10
    hkReal       m_0x14;        // 0x14  negated into hk4dGskCollideMatrices::m_0xc0.w
    hkReal       m_0x18;        // 0x18
    hkReal       m_0x1c;        // 0x1c
    hkVector4    m_0x20;        // 0x20  direction handed to setRotatedDir
    hkVector4    m_0x30;        // 0x30  position handed to setTransformedPos
    const hkSweptTransform* m_swept;  // 0x40
    hkReal       m_0x44;        // 0x44
    hkReal       m_0x48;        // 0x48
    hkReal       m_0x4c;        // 0x4c
    hkTransform  m_0x50;        // 0x50  rows at +0x60/+0x70, translation at +0x80
};

struct hk4dGskTolerances
{
    hkReal m_0x00;              // 0x00
    hkReal m_0x04;              // 0x04
    hkReal m_0x08;              // 0x08
    hkReal m_0x0c;              // 0x0c
    hkReal m_0x10;              // 0x10  radial tolerance
};

struct hk4dGskVertexCollidePointsOutput
{
    hkReal m_0x00;              // 0x00  smallest hit distance seen
};

struct hk4dGskCollideMatrices
{
    hkTransform m_0x00;         // 0x00  interpolated first vertex frame
    hkTransform m_0x40;         // 0x40  interpolated second vertex frame
    hkTransform m_0x80;         // 0x80  first^-1 * second
    hkVector4   m_0xc0;         // 0xc0  collide direction, .w = -in.m_0x14
    hkVector4   m_0xd0;         // 0xd0  collide origin
    hkVector4   m_0xe0;         // 0xe0  second vertex, relative to the collide frame
    hkVector4   m_0xf0;         // 0xf0  first vertex rows difference
    hkVector4   m_0x100;        // 0x100 first vertex translation in the collide frame
};

float __cdecl hk4dGskCollidePointWithPlaneFinal(const hk4dGskVertexCollidePointsInput& in,
                                                const hk4dGskTolerances& tol,
                                                const hkVector4& point,
                                                hkReal tA, hkReal tB,
                                                hkReal time, hkReal dist, hkReal slope,
                                                hk4dGskVertexCollidePointsOutput& out);

// ================================================================================================
// 0x01112230  build the collision frame of the two swept vertices at time t
// ================================================================================================
// @ 0x01112230 hk4dGskCollideInitMatrices
void __cdecl hk4dGskCollideInitMatrices(const hk4dGskVertexCollidePointsInput& in,
                                        hkReal t,
                                        hk4dGskCollideMatrices& out)
{
    const hkSweptTransform* swept = in.m_swept;

    hkSweptTransformUtil::lerp2Ha(*(const hkSweptTransform*)((const char*)in.m_p0 + 0x40),
                                  swept->m_0x00, t * swept->m_0x08, out.m_0x00);
    hkSweptTransformUtil::lerp2Ha(*(const hkSweptTransform*)((const char*)in.m_p1 + 0x40),
                                  swept->m_0x00, t * swept->m_0x08, out.m_0x40);

    out.m_0x80.setMulInverseMul(out.m_0x00, out.m_0x40);
    out.m_0xc0.setRotatedDir(out.m_0x80.m_rotation, in.m_0x20);
    out.m_0xd0.setTransformedPos(out.m_0x80.m_rotation, in.m_0x30);
    out.m_0xc0.w = -in.m_0x14;

    const hkRotation& rotA = out.m_0x00.m_rotation;
    const hkRotation& rotI = in.m_0x50.m_rotation;

    const hkReal r1x = rotI.m_col1.x;
    const hkReal r1y = rotI.m_col1.y;
    const hkReal r1z = rotI.m_col1.z;
    const hkReal r2x = rotI.m_col2.x;
    const hkReal r2y = rotI.m_col2.y;
    const hkReal r2z = rotI.m_col2.z;

    const hkReal d0 = r1y * rotA.m_col0.y + (rotA.m_col0.x * r1x + rotA.m_col0.z * r1z);
    const hkReal d1 = rotA.m_col1.x * r1x + (rotA.m_col1.y * r1y + rotA.m_col1.z * r1z);
    const hkReal d2 = rotA.m_col2.x * r1x + (rotA.m_col2.y * r1y + rotA.m_col2.z * r1z);

    out.m_0xf0.w = 0.0f;
    out.m_0xf0.x = (r2y * rotA.m_col0.y + (rotA.m_col0.x * r2x + rotA.m_col0.z * r2z)) - d0;
    out.m_0xf0.y = (rotA.m_col1.x * r2x + (rotA.m_col1.y * r2y + rotA.m_col1.z * r2z)) - d1;
    out.m_0xf0.z = (rotA.m_col2.x * r2x + (rotA.m_col2.y * r2y + rotA.m_col2.z * r2z)) - d2;

    out.m_0x100.setTransformedPos(out.m_0x80.m_rotation,
                                  *(const hkVector4*)((const char*)in.m_p1 + 0x80));

    const hkReal dx = out.m_0x100.x - *(const hkReal*)((const char*)in.m_p0 + 0x80);
    const hkReal dy = out.m_0x100.y - *(const hkReal*)((const char*)in.m_p0 + 0x84);
    const hkReal dz = out.m_0x100.z - *(const hkReal*)((const char*)in.m_p0 + 0x88);

    out.m_0xe0.setRotatedInverseDir(out.m_0x00.m_rotation, in.m_0x50.m_rotation.m_col0);
    out.m_0xe0.w = out.m_0xe0.w;    // the original re-reads and re-stores this slot here
    out.m_0xe0.x = out.m_0xe0.x - (dy * d2 - dz * d1);
    out.m_0xe0.y = out.m_0xe0.y - (dz * d0 - d2 * dx);
    out.m_0xe0.z = out.m_0xe0.z - (d1 * dx - dy * d0);
}

// ================================================================================================
// 0x01112490  bisect for the time at which one collide point crosses the plane
// ================================================================================================
// @ 0x01112490 hk4dGskCollidePointWithPlaneFinal
float __cdecl hk4dGskCollidePointWithPlaneFinal(const hk4dGskVertexCollidePointsInput& in,
                                                const hk4dGskTolerances& tol,
                                                const hkVector4& point,
                                                hkReal tA, hkReal tB,
                                                hkReal time, hkReal dist, hkReal slope,
                                                hk4dGskVertexCollidePointsOutput& out)
{
    hk4dGskCollideMatrices m;

    const hkReal tolQuarter = tol.m_0x10 * 0.25f;
    hkReal best = tA;

    for (int i = 0; i < 10; i++)
    {
        if (time <= tol.m_0x00 || -tolQuarter < dist - time)
            break;

        hkReal frac = (tol.m_0x00 - time) / (dist - time);
        if (0.1f < frac)
        {
            if (0.9f <= frac)
                frac = 0.9f;
        }
        else
        {
            frac = 0.1f;
        }

        best = frac * tB + (1.0f - frac) * tA;
        hk4dGskCollideInitMatrices(in, best, m);

        const hkReal d = ((point.x - m.m_0xd0.x) * m.m_0xc0.x +
                          (m.m_0xc0.y * (point.y - m.m_0xd0.y) + m.m_0xc0.z * (point.z - m.m_0xd0.z)))
                         + m.m_0xc0.w;
        if (fabsf(d - tol.m_0x00) < tolQuarter)
            break;

        if (d < tol.m_0x00)
        {
            tB = best;
            dist = d;
        }
        else
        {
            time = d;
            tA = best;
        }
    }

    if (best < out.m_0x00)
        out.m_0x00 = best;

    return best;
}

// ================================================================================================
// 0x01112600  sweep every collide point and keep the earliest contact
// ================================================================================================
// @ 0x01112600 hk4dGskCollidePointsWithPlane
// The second parameter is read as a float array: [0..3] the plane, [4] the radial
// tolerance (the same object 01112490 receives as hk4dGskTolerances).
extern "C" void __cdecl hk4dGskCollidePointsWithPlane(const hk4dGskVertexCollidePointsInput& in,
                                                      const hkReal* plane,
                                                      hk4dGskVertexCollidePointsOutput& out)
{
    hk4dGskCollideMatrices m;

    hkReal t    = in.m_0x50.m_translation.x;
    hkReal tEnd = 1.0f;
    hkReal tPrev = t;

    for (;;)
    {
        hk4dGskCollideInitMatrices(in, t, m);

        const hkReal dt = tEnd - t;
        int remaining = in.m_numPoints;
        hkReal* point = in.m_points;
        const hkReal thickness = in.m_0x44;
        hkReal tNext = tEnd;

        if (remaining > 0)
        {
            hkReal* hit = point + 2;
            do
            {
                const hkReal fDist = ((point[0] - m.m_0xd0.x) * m.m_0xc0.x +
                                      (m.m_0xc0.y * (point[1] - m.m_0xd0.y) +
                                       m.m_0xc0.z * (point[2] - m.m_0xd0.z)))
                                     + m.m_0xc0.w;

                // The three guards are written as negated strict comparisons: MSVC's
                // "test ah,5; jnp" idiom tests for an *ordered* less-than, so the body is
                // still entered when an operand is NaN.  Written as `<=`/`>=` the compiler
                // folds "unordered" into the taken branch and the behaviour diverges.
                if (!(dt * thickness + plane[0] < fDist))
                {
                    const hkReal fSlope =
                        ((m.m_0xf0.z * (point[1] - m.m_0x100.y) - m.m_0xf0.y * (point[2] - m.m_0x100.z)) - m.m_0xe0.x) * m.m_0xc0.x +
                        (((m.m_0xf0.x * (point[2] - m.m_0x100.z) - m.m_0xf0.z * (point[0] - m.m_0x100.x)) - m.m_0xe0.y) * m.m_0xc0.y +
                         ((m.m_0xf0.y * (point[0] - m.m_0x100.x) - m.m_0xf0.x * (point[1] - m.m_0x100.y)) - m.m_0xe0.z) * m.m_0xc0.z);

                    if (!(fSlope * dt + (fDist - plane[0]) > ((dt * in.m_0x18) * dt) * 0.5f))
                    {
                        if (fDist < plane[0])
                        {
                            tEnd = hk4dGskCollidePointWithPlaneFinal(in, *(const hk4dGskTolerances*)plane,
                                                                     *(const hkVector4*)point,
                                                                     tPrev, t, point[3],
                                                                     fDist, fSlope, out);
                        }
                        else
                        {
                            const hkReal s0 = point[0];
                            const hkReal s1 = point[1];
                            const hkReal s2 = point[2];
                            const hkReal s3 = point[3];
                            point[0] = hit[-2];
                            point[1] = hit[-1];
                            point[2] = hit[0];
                            point[3] = hit[1];
                            hit[-2] = s0;
                            hit[-1] = s1;
                            hit[0]  = s2;
                            hit[1]  = s3;
                            hit[1]  = fDist;
                            hit += 4;

                            hkReal d2 = (fDist - plane[1]) * in.m_0x1c;
                            d2 = d2 + d2;
                            if (!(d2 > dt * dt))
                            {
                                const hkReal halfWidth = (plane[0] - plane[1]) * in.m_0x1c;
                                d2 = sqrtf(d2);
                                const hkReal radius = fSlope * in.m_0x1c;
                                if (fSlope < 0.0f)
                                {
                                    if (d2 < -radius)
                                        d2 = -radius;
                                }
                                else
                                {
                                    d2 = (radius + radius) + d2;
                                }

                                if (!(d2 > dt))
                                {
                                    d2 = sqrtf(halfWidth + halfWidth) + d2;
                                    if (!(d2 > plane[2]))
                                        d2 = plane[2];
                                    d2 = d2 + t;
                                    if (!(tNext < d2))
                                        tNext = d2;
                                }
                            }
                        }
                    }
                }

                point += 4;
                remaining--;
            } while (remaining != 0);
        }

        if (tEnd < t || (t == tNext && tEnd <= t))
            break;

        tPrev = t;
        t = tNext;
    }
}
