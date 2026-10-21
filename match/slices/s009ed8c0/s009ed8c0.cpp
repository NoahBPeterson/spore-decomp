// Slice s009ed8c0 -- checkerlib vector / matrix / quaternion helpers used by the
// nSPCreatureAnim IK solver.  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Register conventions in the original:
//   0x009ed8c0  ECX = offset, EDX = normal, ESI = anchor, stack = (out, d), returns out in EAX.
//               A non-standard register ABI (an argument lives in ESI), so it is modelled here as
//               a plain 5-argument cdecl, exactly as the caller slice s009f1990 declares it.  This
//               is why s009ed8c0 can never be byte-exact.
//   0x009edb70  ordinary cdecl with a hidden sret matrix pointer (first stack arg).
//   0x009edcf0  ordinary __thiscall (ECX = out quaternion, 4 stack args, ret 0x10).
#include <math.h>
#pragma intrinsic(sqrt)

namespace checkerlib
{

class vector_3 { public: float x, y, z; };
class vector_4 { public: float x, y, z, w; };

// A 3x3 rotation matrix, row-major: row r = (el[3r], el[3r+1], el[3r+2]).
class matrix_3x3
{ public:
    float el[9];
    // Rotation about a unit axis built from cos/sin (Rodrigues).
    void SetAxisCosSin(const vector_3& axis, float c, float s);   // 0x009e6cf0
};

// Normalised copy of a vector with an optional length out.
extern "C" vector_3* __cdecl NormalizeVec3(vector_3* out, const vector_3* in, float* lengthOut);   // 0x009a49d0
// Two orthonormal vectors perpendicular to `dir`.
extern "C" void __cdecl PerpPair(const vector_3* dir, vector_3* o1, vector_3* o2);                 // 0x009a4a70

// The point on the plane { x : n.x = d } that is at the same distance from `anchor` as `off`
// describes:  moved = off + n*d - n*(n.(anchor+off)), perp = off - n*(n.off),
// disc = (perp.moved)^2 - (|moved|^2 - |off|^2)*|perp|^2,
// t = (sqrt(disc) - perp.moved) / (|perp|^2 + 1e-8), out = anchor + perp*t + moved.
// @ 0x009ed8c0
vector_3* SolvePlaneTarget(const vector_3* off, const vector_3* n, const vector_3* anchor,
                           vector_3* out, float d)
{
    float nx = n->x, ny = n->y, nz = n->z;
    float ox = off->x, oy = off->y, oz = off->z;
    float ax = anchor->x, ay = anchor->y, az = anchor->z;

    float dot = (nx * (ax + ox) + ny * (ay + oy)) + nz * (az + oz);
    float mx = (ox + nx * d) - nx * dot;
    float my = (oy + ny * d) - ny * dot;
    float mz = (oz + nz * d) - nz * dot;

    float dot2 = (nz * oz + ny * oy) + nx * ox;
    float px = ox - nx * dot2;
    float py = oy - ny * dot2;
    float pz = oz - nz * dot2;

    float p2 = (py * py + pz * pz) + px * px;
    float f5 = (pz * mz + py * my) + px * mx;
    float disc = f5 * f5 - (((my * my + mz * mz) + mx * mx) - ((oz * oz + oy * oy) + ox * ox)) * p2;
    if (disc > 0.0f)
        disc = (float)sqrt((double)disc);
    else
        disc = 0.0f;
    float t = (disc - f5) / (p2 + 1e-8f);
    out->x = ax + (px * t + mx);
    out->y = ay + (py * t + my);
    out->z = az + (pz * t + mz);
    return out;
}

// Rotation matrix taking direction a onto direction b.  *pCos (if non-null) receives a.b.  When a
// and b are parallel the identity is returned if they point the same way; otherwise the rotation
// is 180 degrees about pFallback (used as an axis), or about a fresh axis from PerpPair.
// @ 0x009edb70
matrix_3x3 RotationAtoB(const vector_3& a, const vector_3& b, float* pCos, const matrix_3x3* pFallback)
{
    matrix_3x3 out;
    float dot = (a.y * b.y + a.x * b.x) + a.z * b.z;
    if (pCos)
        *pCos = dot;

    vector_3 axis;
    axis.x = b.z * a.y - b.y * a.z;
    axis.y = a.z * b.x - b.z * a.x;
    axis.z = b.y * a.x - a.y * b.x;

    vector_3 naxis;
    float len = 0.0f;
    NormalizeVec3(&naxis, &axis, &len);

    if (!(len > 0.0f))
    {
        if (dot > 0.0f)
        {
            out.el[0] = 1.0f; out.el[1] = 0.0f; out.el[2] = 0.0f;
            out.el[3] = 0.0f; out.el[4] = 1.0f; out.el[5] = 0.0f;
            out.el[6] = 0.0f; out.el[7] = 0.0f; out.el[8] = 1.0f;
            return out;
        }
        const vector_3* perp;
        vector_3 o1, o2;
        if (pFallback)
            perp = (const vector_3*)pFallback;
        else
        {
            PerpPair(&a, &o1, &o2);
            perp = &o1;
        }
        out.SetAxisCosSin(*perp, -1.0f, 0.0f);
        return out;
    }
    out.SetAxisCosSin(naxis, dot, len);
    return out;
}

// Quaternion from a rotation axis: (axis*c, s + 1), normalised when non-zero.  The 4th argument
// is not used (the callee pops it with ret 0x10).
struct quaternion
{
    float x, y, z, w;
    quaternion* FromAxisSC(const vector_3* axis, float s, float c, int flag);   // 0x009edcf0
};

// @ 0x009edcf0
quaternion* quaternion::FromAxisSC(const vector_3* axis, float s, float c, int flag)
{
    float px = axis->x * c;
    float py = axis->y * c;
    float pz = axis->z * c;
    float pw = s + 1.0f;
    x = px; y = py; z = pz; w = pw;
    float n = (float)sqrt((((double)px * px + (double)pw * pw) + (double)pz * pz) + (double)py * py);
    if (n != 0.0f)
    {
        float inv = 1.0f / n;
        x = px * inv;
        y = py * inv;
        z = pz * inv;
        w = pw * inv;
    }
    return this;
}

} // namespace checkerlib
