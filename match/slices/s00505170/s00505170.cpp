// w1g1 slice s00505170
//   0x505170  ray-triangle intersection (Moeller-Trumbore), outputs t/u/v, cull flag
//   0x5056d0  squared distance from a point to an axis-aligned box (per-axis clamp)
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (scalar movss/comiss; x87 only for the float
// return of the distance helper).

typedef unsigned int uint32_t;

// ---------------------------------------------------------------------------
// @ 0x00505170
// int __cdecl RayTri(const float* orig, const float* dir, const float* v0,
//                    const float* v1, const float* v2, float* t, float* u,
//                    float* v, char cull)
// ---------------------------------------------------------------------------
int __cdecl RayTri(const float* orig, const float* dir, const float* v0,
                   const float* v1, const float* v2, float* t, float* u,
                   float* v, char cull)
{
    const float e1x = v1[0] - v0[0];
    const float e1y = v1[1] - v0[1];
    const float e1z = v1[2] - v0[2];
    const float e2x = v2[0] - v0[0];
    const float e2y = v2[1] - v0[1];
    const float e2z = v2[2] - v0[2];

    const float px = dir[1] * e2z - dir[2] * e2y;
    const float py = dir[2] * e2x - dir[0] * e2z;
    const float pz = dir[0] * e2y - dir[1] * e2x;

    float det = (e1x * px + e1y * py) + e1z * pz;
    const float inv = 1.0f / det;

    float tx, ty, tz, qx, qy, qz;

    if (det <= 1e-06f) {
        if (cull != 0 || -1e-06f <= det)
            return 0;
        tx = orig[0] - v0[0];
        ty = orig[1] - v0[1];
        tz = orig[2] - v0[2];
        *u = (tx * px + ty * py) + tz * pz;
        if (0.0f < *u || (*u <= det && det != *u))
            return 0;
        qx = ty * e1z - tz * e1y;
        qy = tz * e1x - tx * e1z;
        qz = tx * e1y - ty * e1x;
        *v = (dir[0] * qx + dir[1] * qy) + dir[2] * qz;
        if (0.0f < *v || *u + *v < det)
            return 0;
    } else {
        tx = orig[0] - v0[0];
        ty = orig[1] - v0[1];
        tz = orig[2] - v0[2];
        *u = (tx * px + ty * py) + tz * pz;
        if ((*u <= 0.0f && *u != 0.0f) || det < *u)
            return 0;
        qx = ty * e1z - tz * e1y;
        qy = tz * e1x - tx * e1z;
        qz = tx * e1y - ty * e1x;
        *v = (dir[0] * qx + dir[1] * qy) + dir[2] * qz;
        if ((*v <= 0.0f && *v != 0.0f) || det < *u + *v)
            return 0;
    }

    *t = ((e2x * qx + e2y * qy) + e2z * qz) * inv;
    *u = *u * inv;
    *v = *v * inv;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x005056d0
// float __cdecl DistPointBoxSq(const float* p, const float* lo, const float* hi)
// ---------------------------------------------------------------------------
float __cdecl DistPointBoxSq(const float* p, const float* lo, const float* hi)
{
    float result;
    float d;

    result = 0.0f;
    if (lo[0] <= p[0]) {
        if (p[0] > hi[0]) {
            d = p[0] - hi[0];
            result = d * d + 0.0f;
        }
    } else {
        d = p[0] - lo[0];
        result = d * d + 0.0f;
    }

    if (lo[1] <= p[1]) {
        if (p[1] > hi[1]) {
            d = p[1] - hi[1];
            result = d * d + result;
        }
    } else {
        d = p[1] - lo[1];
        result = d * d + result;
    }

    if (lo[2] <= p[2]) {
        if (p[2] > hi[2]) {
            d = p[2] - hi[2];
            result = d * d + result;
        }
    } else {
        d = p[2] - lo[2];
        result = d * d + result;
    }

    return result;
}
