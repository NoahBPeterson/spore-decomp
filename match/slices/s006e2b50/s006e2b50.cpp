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
                float n0 = 0.0f, n1 = 0.0f, n2 = 0.0f;
                if (face == 0 || face == 2) {
                    n0 = (float)(1.0 / sqrt((double)base));
                    n1 = n0 * fy;
                    n2 = n0 * fx;
                    if (face == 2) { n0 = -n0; n1 = -n1; }
                } else if (face == 1 || face == 3) {
                    n1 = (float)(1.0 / sqrt((double)base));
                    n0 = -(n1 * fy);
                    n2 = n1 * fx;
                    if (face == 3) { n1 = -n1; n0 = -n0; }
                } else if (face == 4 || face == 5) {
                    n2 = (float)(1.0 / sqrt((double)base));
                    n1 = n2 * fy;
                    n0 = -(n2 * fx);
                    if (face == 5) { n2 = -n2; n0 = -n0; }
                }
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
                        ca = c2 + t;
                        c2 = c2 + t;
                    }
                }
                float local_40 = wt * c0;
                float fStack_3c = wt * c1;
                float fStack_38 = wt * c2;
                float fStack_34 = wt * ca;
                float local_4c = n1;
                float local_48 = n0;
                float local_44 = n2;
                (void)fStack_34;
                AddColourSample(&local_40, 5, &local_4c, dst);
                x = x + 1;
                p = p + 1;
                (void)local_44;
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
    void UpdateTransforms(float* p);
};

void cViewer::UpdateTransforms(float* p) {
    mCameraToWorldTransform.xAxis[0] = p[0];
    mCameraToWorldTransform.xAxis[1] = p[1];
    mCameraToWorldTransform.xAxis[2] = p[2];
    mCameraToWorldTransform.xAxis[3] = 0.0f;
    mCameraToWorldTransform.yAxis[0] = p[3];
    mCameraToWorldTransform.yAxis[1] = p[4];
    mCameraToWorldTransform.yAxis[2] = p[5];
    mCameraToWorldTransform.yAxis[3] = 0.0f;
    mCameraToWorldTransform.zAxis[0] = p[6];
    mCameraToWorldTransform.zAxis[1] = p[7];
    mCameraToWorldTransform.zAxis[2] = p[8];
    mCameraToWorldTransform.zAxis[3] = 0.0f;
    mCameraToWorldTransform.wAxis[0] = p[9];
    mCameraToWorldTransform.wAxis[1] = p[10];
    mCameraToWorldTransform.wAxis[2] = p[11];
    mCameraToWorldTransform.wAxis[3] = 0.0f;
}
