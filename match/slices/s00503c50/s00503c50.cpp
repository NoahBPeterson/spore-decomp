// slice s00503c50 -- single large function at 0x00503c50.
//
// 0x00503c50 (5402 bytes, /Od SSE) is the Mahovsky & Wyvill ray/AABB overlap test
// using Pluecker coordinates ("Fast Ray-Axis Aligned Bounding Box Overlap Tests
// with Pluecker Coordinates", JGT 2004).  Instead of the paper's switch on a
// precomputed ray classification, the eight direction-sign classes (MMM .. PPP)
// are selected by nested `dir[i] < 0` tests.  Each class:
//   1. rejects rays whose origin lies beyond the box on a side the ray moves away
//      from (origin < min for a negative component, origin > max for a positive);
//   2. computes the six box-corner offsets from the origin (xa..zb, one block-
//      scoped set per class -> the 0xc0-byte frame of 8 x 6 floats);
//   3. rejects on six Pluecker side tests (d[i]*a - d[j]*b < 0 or > 0).
// The original ends with an unreachable `return false;`.
//
// Origin and direction are passed by value (3 floats each), the box by pointer
// {min, max}.  Every component access goes through an inline operator[]
// (the `xor r,r; shl r,2` / `mov r,k; shl r,2` index pattern).
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast

struct Vector3 {
    float v[3];
    float& operator[](int i) { return v[i]; }
    const float& operator[](int i) const { return v[i]; }
};

struct BoundingBox {
    Vector3 min;   // +0x00
    Vector3 max;   // +0x0c
};

// @ 0x00503c50  (Claude-coined name)
bool RayIntersectsBox(Vector3 o, Vector3 d, const BoundingBox* b)
{
    if (d[0] < 0.0f) {
        if (d[1] < 0.0f) {
            if (d[2] < 0.0f) {
                // MMM
                if (o[0] < b->min[0] || o[1] < b->min[1] || o[2] < b->min[2])
                    return false;
                float xa = b->min[0] - o[0];
                float ya = b->min[1] - o[1];
                float za = b->min[2] - o[2];
                float xb = b->max[0] - o[0];
                float yb = b->max[1] - o[1];
                float zb = b->max[2] - o[2];
                if (d[0] * ya - d[1] * xb < 0.0f ||
                    d[0] * yb - d[1] * xa > 0.0f ||
                    d[0] * zb - d[2] * xa > 0.0f ||
                    d[0] * za - d[2] * xb < 0.0f ||
                    d[1] * za - d[2] * yb < 0.0f ||
                    d[1] * zb - d[2] * ya > 0.0f)
                    return false;
                return true;
            } else {
                // MMP
                if (o[0] < b->min[0] || o[1] < b->min[1] || o[2] > b->max[2])
                    return false;
                float xa = b->min[0] - o[0];
                float ya = b->min[1] - o[1];
                float za = b->min[2] - o[2];
                float xb = b->max[0] - o[0];
                float yb = b->max[1] - o[1];
                float zb = b->max[2] - o[2];
                if (d[0] * ya - d[1] * xb < 0.0f ||
                    d[0] * yb - d[1] * xa > 0.0f ||
                    d[0] * zb - d[2] * xb > 0.0f ||
                    d[0] * za - d[2] * xa < 0.0f ||
                    d[1] * za - d[2] * ya < 0.0f ||
                    d[1] * zb - d[2] * yb > 0.0f)
                    return false;
                return true;
            }
        } else {
            if (d[2] < 0.0f) {
                // MPM
                if (o[0] < b->min[0] || o[1] > b->max[1] || o[2] < b->min[2])
                    return false;
                float xa = b->min[0] - o[0];
                float ya = b->min[1] - o[1];
                float za = b->min[2] - o[2];
                float xb = b->max[0] - o[0];
                float yb = b->max[1] - o[1];
                float zb = b->max[2] - o[2];
                if (d[0] * ya - d[1] * xa < 0.0f ||
                    d[0] * yb - d[1] * xb > 0.0f ||
                    d[0] * zb - d[2] * xa > 0.0f ||
                    d[0] * za - d[2] * xb < 0.0f ||
                    d[1] * zb - d[2] * yb < 0.0f ||
                    d[1] * za - d[2] * ya > 0.0f)
                    return false;
                return true;
            } else {
                // MPP
                if (o[0] < b->min[0] || o[1] > b->max[1] || o[2] > b->max[2])
                    return false;
                float xa = b->min[0] - o[0];
                float ya = b->min[1] - o[1];
                float za = b->min[2] - o[2];
                float xb = b->max[0] - o[0];
                float yb = b->max[1] - o[1];
                float zb = b->max[2] - o[2];
                if (d[0] * ya - d[1] * xa < 0.0f ||
                    d[0] * yb - d[1] * xb > 0.0f ||
                    d[0] * zb - d[2] * xb > 0.0f ||
                    d[0] * za - d[2] * xa < 0.0f ||
                    d[1] * zb - d[2] * ya < 0.0f ||
                    d[1] * za - d[2] * yb > 0.0f)
                    return false;
                return true;
            }
        }
    } else {
        if (d[1] < 0.0f) {
            if (d[2] < 0.0f) {
                // PMM
                if (o[0] > b->max[0] || o[1] < b->min[1] || o[2] < b->min[2])
                    return false;
                float xa = b->min[0] - o[0];
                float ya = b->min[1] - o[1];
                float za = b->min[2] - o[2];
                float xb = b->max[0] - o[0];
                float yb = b->max[1] - o[1];
                float zb = b->max[2] - o[2];
                if (d[0] * yb - d[1] * xb < 0.0f ||
                    d[0] * ya - d[1] * xa > 0.0f ||
                    d[0] * za - d[2] * xa > 0.0f ||
                    d[0] * zb - d[2] * xb < 0.0f ||
                    d[1] * za - d[2] * yb < 0.0f ||
                    d[1] * zb - d[2] * ya > 0.0f)
                    return false;
                return true;
            } else {
                // PMP
                if (o[0] > b->max[0] || o[1] < b->min[1] || o[2] > b->max[2])
                    return false;
                float xa = b->min[0] - o[0];
                float ya = b->min[1] - o[1];
                float za = b->min[2] - o[2];
                float xb = b->max[0] - o[0];
                float yb = b->max[1] - o[1];
                float zb = b->max[2] - o[2];
                if (d[0] * yb - d[1] * xb < 0.0f ||
                    d[0] * ya - d[1] * xa > 0.0f ||
                    d[0] * za - d[2] * xb > 0.0f ||
                    d[0] * zb - d[2] * xa < 0.0f ||
                    d[1] * za - d[2] * ya < 0.0f ||
                    d[1] * zb - d[2] * yb > 0.0f)
                    return false;
                return true;
            }
        } else {
            if (d[2] < 0.0f) {
                // PPM
                if (o[0] > b->max[0] || o[1] > b->max[1] || o[2] < b->min[2])
                    return false;
                float xa = b->min[0] - o[0];
                float ya = b->min[1] - o[1];
                float za = b->min[2] - o[2];
                float xb = b->max[0] - o[0];
                float yb = b->max[1] - o[1];
                float zb = b->max[2] - o[2];
                if (d[0] * yb - d[1] * xa < 0.0f ||
                    d[0] * ya - d[1] * xb > 0.0f ||
                    d[0] * za - d[2] * xa > 0.0f ||
                    d[0] * zb - d[2] * xb < 0.0f ||
                    d[1] * zb - d[2] * yb < 0.0f ||
                    d[1] * za - d[2] * ya > 0.0f)
                    return false;
                return true;
            } else {
                // PPP
                if (o[0] > b->max[0] || o[1] > b->max[1] || o[2] > b->max[2])
                    return false;
                float xa = b->min[0] - o[0];
                float ya = b->min[1] - o[1];
                float za = b->min[2] - o[2];
                float xb = b->max[0] - o[0];
                float yb = b->max[1] - o[1];
                float zb = b->max[2] - o[2];
                if (d[0] * yb - d[1] * xa < 0.0f ||
                    d[0] * ya - d[1] * xb > 0.0f ||
                    d[0] * za - d[2] * xb > 0.0f ||
                    d[0] * zb - d[2] * xa < 0.0f ||
                    d[1] * zb - d[2] * ya < 0.0f ||
                    d[1] * za - d[2] * yb > 0.0f)
                    return false;
                return true;
            }
        }
    }
    return false;
}
