// slice s006e2b50: cube-map prefilter (writes colour samples) and a camera
// transform copy.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;
typedef unsigned char byte;

extern "C" double sqrt(double);
extern "C" void AddColourSample(float* colour, int n, float* dir, void* dst);

// ---------------------------------------------------------------------------
// @ 0x006e2b50  SP::PrefilterCube
// ---------------------------------------------------------------------------
void SP_PrefilterCube(void* dst, int size, int face, int pixels, float px, float py, float pz,
                      char flag) {
    int y = 0;
    if (0 < size) {
        float half = (float)size * 0.5f;
        byte* row = (byte*)(pixels + 2);
        do {
            float fy = ((float)y - half) / half;
            float fy2 = fy * fy;
            int x = 0;
            byte* p = row;
            do {
                float fx = ((float)x - half) / half;
                float fx2 = fx * fx;
                float base = fx2 + fy2 + 1.0f;
                // The original writes the direction only for faces 0..5; any other face reads
                // the untouched stack slots (undefined in C, 0xCC under the harness).
                float dir[4];
                if (face == 0 || face == 2) {
                    float n = (float)(1.0 / sqrt((double)base));
                    dir[1] = n;
                    dir[0] = n * fy;
                    dir[2] = n * fx;
                    if (face == 2) { dir[1] = -dir[1]; dir[0] = -dir[0]; }
                } else if (face == 1 || face == 3) {
                    float n = (float)(1.0 / sqrt((double)base));
                    dir[0] = n;
                    dir[1] = -(n * fy);
                    dir[2] = n * fx;
                    if (face == 3) { dir[0] = -dir[0]; dir[1] = -dir[1]; }
                } else if (face == 4 || face == 5) {
                    float n = (float)(1.0 / sqrt((double)base));
                    dir[0] = n * fy;
                    dir[1] = -(n * fx);
                    dir[2] = n;
                    if (face == 5) { dir[0] = -dir[0]; dir[1] = -dir[1]; }
                }
                float n0 = dir[1];
                float n1 = dir[0];
                float n2 = dir[2];
                float len3 = (n0 * n0 + n1 * n1) + 1.0f;
                float c2 = (float)p[-2] * 0.003921569f;
                float c1 = (float)p[-1] * 0.003921569f;
                float c0 = (float)*p * 0.003921569f;
                float ca = (float)p[1] * 0.003921569f;
                float wt = 4.0f / (((len3 * len3) / (float)sqrt((double)len3)) *
                                   (float)(size * size));
                if (flag != '\0') {
                    float dx = n1 - px, dy = n2 - py, dz = n0 - pz;
                    float d = (float)sqrt((double)(dx * dx + (dy * dy + dz * dz)));
                    if (d < 1.0f) {
                        float t = 1.0f - d;
                        c0 = c0 + t;
                        c1 = c1 + t;
                        c2 = c2 + t;
                        ca = ca + t;
                    }
                }
                float colour[5];
                colour[0] = wt * c0;
                colour[1] = wt * c1;
                colour[2] = wt * c2;
                colour[3] = wt * ca;
                colour[4] = 0.0f;
                AddColourSample(colour, 5, dir, dst);
                x = x + 1;
                p = p + 1;
            } while (x < size);
            row = row + size;
            y = y + 1;
        } while (y < size);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e3000  SP::cViewer::UpdateTransforms
// ---------------------------------------------------------------------------
struct Matrix44 {
    float xAxis[4];
    float yAxis[4];
    float zAxis[4];
    float wAxis[4];
};

struct cViewer {
    Matrix44 mCameraToWorldTransform;   // +0x0
    cViewer* UpdateTransforms(float* p);
};

// Retail loads EAX with ECX (this) at the entry and never rewrites it, so the function returns the
// viewer (`this`) in EAX although callers ignore it.
cViewer* cViewer::UpdateTransforms(float* p) {
    // Retail fills a stack temporary with the 12 axis components and then copies the whole 4x4
    // into the viewer, so the w lanes of the viewer get whatever the temporary's w lanes hold --
    // they are never written (the copy at 0x006e3040 loads the untouched stack slot).
    Matrix44 m;
    m.xAxis[0] = p[0];
    m.xAxis[1] = p[1];
    m.xAxis[2] = p[2];
    m.yAxis[0] = p[3];
    m.yAxis[1] = p[4];
    m.yAxis[2] = p[5];
    m.zAxis[0] = p[6];
    m.zAxis[1] = p[7];
    m.zAxis[2] = p[8];
    m.wAxis[0] = p[9];
    m.wAxis[1] = p[10];
    m.wAxis[2] = p[11];
    mCameraToWorldTransform = m;
    return this;
}
