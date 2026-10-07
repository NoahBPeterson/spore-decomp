// Slice s00a8f6a0 (batch big0, slice 14):
//   EA::Swarm::cDistributeEffect::CreateClusteredMatchingSamples2D
// __thiscall (ecx = this), /O2 with an aligned frame (and esp,-16 + sub esp,0x454).
// Behavioural transcription of the Ghidra decompile. The class member offsets are
// the 2008 dev-PDB layout of EA::Swarm::cDistributeEffect (mDesc +0x14, mFlags
// +0x28, mSourceTransform +0x2c, mSamples +0xb8, mEffects +0xd0,
// mSubdivOffset +0xf8, mSubdivScale +0x104, mSubdivOwner +0x110,
// mSurfaceRecs +0x114, mColorScale +0x15c).  EASTL vector growth and the 3x3
// rotations are expressed with the same masked helpers the original calls.
#include "types.h"
#include <math.h>

struct V3 { float x, y, z; };
struct M33 { V3 x, y, z; };

// masked callees
extern void  FUN_00a8bf60(int);
extern void  FUN_00a8cc40(int);
extern void  FUN_00a8c540(void* p, void* rec);
extern void  FUN_00a8ce30(void* p, void* rec);
extern void  FUN_00a89de0(void* rec);
extern char  FUN_00a89a90(const void* v, int n, int count);
extern int   FUN_00a89980(void* rec, float f);
extern void  FUN_00537f40(void* p);
extern void* FUN_007d5590(void* buf, void* p, void* a, int b);
extern float* CubeToSphereSurface(float* out, float* v);     // anonymous-namespace helper
extern float DAT_0156502c, _DAT_01678300, DAT_01678278;
extern float DAT_01677840[], DAT_01677844[];
extern float DAT_01678230, DAT_01678234, DAT_01678238, DAT_0167827c, DAT_01678280,
             DAT_01678284;
extern float DAT_01678318, DAT_0167831c, DAT_01678320, DAT_01678324;

#define SF(off) (*(float*)((char*)self + (off)))
#define SI(off) (*(int*)((char*)self + (off)))

// cSPTransform-style scratch (translation, rotation, scale, flags, modCount).
struct Transform {
    float tx, ty, tpad;
    M33   rot;
    float scale;
    short flags, mod;
};

// Append one cDistributeSample to this->mSamples (EASTL vector at +0xb8).
static void PushSample(void* self, void* rec)
{
    void* pEnd   = (void*)SI(0xb8 + 4);
    void* pCap   = (void*)SI(0xb8 + 8);
    if (pEnd < pCap) {
        SI(0xb8 + 4) = (int)pEnd + 0x30;
        if (pEnd) FUN_00a89de0(rec);
    } else {
        FUN_00a8ce30(pEnd, rec);
    }
}

// Sample record written by the original (position, direction, 3x3, time, flags).
struct Sample {
    float px, py, pz;
    float dx, dy, dz;
    M33   m;
    float time;
    float scale;
    unsigned short flags;
    unsigned short mod;
};

// @ 0x00a8f6a0
void cDistributeEffect_CreateClusteredMatchingSamples2D(void* self, int param_2)
{
    Transform tf;
    void* desc = (void*)SI(0x14);
    int   count = SI(0xd0 + 4);          // mEffects.mpEnd (element count)
    float inv = 1.0f / (float)count;

    // copy mSourceTransform (this+0x2c)
    {
        char* s = (char*)self + 0x2c;
        tf.tx = *(float*)(s + 0);
        tf.ty = *(float*)(s + 4);
        tf.tpad = *(float*)(s + 8);
        tf.rot.x.x = *(float*)(s + 12);
        tf.rot.x.y = *(float*)(s + 16);
        tf.rot.x.z = *(float*)(s + 20);
        tf.rot.y.x = *(float*)(s + 24);
        tf.rot.y.y = *(float*)(s + 28);
        tf.rot.y.z = *(float*)(s + 32);
        tf.rot.z.x = *(float*)(s + 36);
        tf.rot.z.y = *(float*)(s + 40);
        tf.rot.z.z = *(float*)(s + 44);
        tf.scale = *(float*)(s + 48);
        tf.flags = *(short*)(s + 52);
        tf.mod = *(short*)(s + 54);
    }
    // optional per-surface override (mSurfaceRecs at +0x114)
    {
        void* srEnd = (void*)SI(0x114 + 4);
        if (srEnd) tf = *(Transform*)srEnd; // cSPTransform::operator=
    }

    float preScale = *(float*)((char*)desc + 0) * tf.scale;   // mPreTransform * mScale
    tf.flags = (short)(tf.flags | 1);
    tf.mod   = (short)(tf.mod + 1);
    float colorScale = *(float*)((char*)self + 0x15c);
    float subdivScaleZ = SF(0x104 + 8);      // mSubdivScale.PaddingForAlignment[0]
    float subdivScaleX = SF(0x104 + 0);
    float subdivScaleY = SF(0x104 + 4);
    float subdivOff    = SF(0xf8 + 8);       // mSubdivOffset.PaddingForAlignment[0]
    int   subdivOwner  = SI(0x110);
    int   surfBegin    = SI(0x114);
    float timeAcc = 0.0f;

    float base = inv;
    float step = inv * 2.0f;
    float s3 = subdivScaleZ * inv;
    float sOwner = (float)subdivOwner * inv;
    float sSurf = (float)surfBegin * inv;

    if (((*(unsigned*)((char*)desc + 4)) >> 9 & 1) != 0) {   // mDesc->mFlags bit 9
        tf.flags = (short)(tf.flags | 1);
        tf.mod   = (short)(tf.mod + 1);
        preScale = (subdivScaleZ * inv) * preScale;
    }

    int format = *(unsigned char*)((char*)desc + 8);   // mSourceSize byte (mSourceFormat)
    float halfExtent = (float)(count - 1) * 0.5f;

    switch (format) {
    case 0: {
        FUN_00a8bf60(count * count);
        FUN_00a8cc40(count * count);
        if (count <= 0) break;
        for (int i = 0; i < count; ++i) {
            float fi = ((float)i - halfExtent) * step;
            for (int j = 0; j < count; ++j) {
                float u = fi * subdivScaleX + subdivOff;
                float v = ((float)j - halfExtent) * step * (float)subdivOwner + subdivScaleY;
                float w = 0.0f + subdivScaleZ;
                Sample rec;
                rec.px = u; rec.py = v; rec.pz = w;
                rec.scale = preScale;
                PushSample(self, &rec);
                float rx = u, ry = v, rz = w;
                // optional cube->sphere mapping
                if (((SI(0x28) >> 4) & 1) == 0) {
                    if ((SI(0x28) >> 5) & 1) {
                        float* c = CubeToSphereSurface((float*)&rec.m, &u);
                        rx = c[0]; ry = c[1]; rz = c[2];
                    }
                } else {
                    float t = (v * DAT_0156502c) * DAT_01678278 + 12582912.0f;
                    float rad = sqrtf(1.0f - u * u);
                    float a = DAT_01677840[((unsigned)t & 0xf) * 2];
                    float d = v * DAT_0156502c - (float)((int)t - 0x4b400000) * _DAT_01678300;
                    float b = DAT_01677844[((unsigned)t & 0xf) * 2];
                    rx = (b - ((b * d) * 0.5f + a) * d) * rad;
                    ry = ((b - (a * d) * 0.5f) * d + a) * rad;
                    rz = u;
                }
                // rotate if the rigid flag is set
                if ((tf.flags & 2) != 0) {
                    float ox = rx, oy = ry, oz = rz;
                    rx = ox * tf.rot.x.x + oz * tf.rot.z.x + oy * tf.rot.y.x;
                    ry = ox * tf.rot.x.y + oz * tf.rot.z.y + oy * tf.rot.y.y;
                    rz = ox * tf.rot.x.z + oz * tf.rot.z.z + oy * tf.rot.y.z;
                }
                tf.flags |= 4;
                tf.mod = (short)(tf.mod + 1);
                float wx = rx * preScale + tf.tx;
                float wy = tf.ty + ry * preScale;
                float wz = tf.tpad + rz * preScale;
                if (!(colorScale != 0.0f) || FUN_00a89a90(&wx, (int)timeAcc + 1, count) == 0) {
                    // build the mSamples record (with or without the pre-transform)
                    FUN_00537f40(desc);
                    (void)FUN_00a89980(&rec, timeAcc);
                    PushSample(self, &rec);
                    timeAcc = (float)((int)timeAcc + 1);
                }
            }
        }
        return;
    }
    case 3: {
        int n = count * count * 2;
        FUN_00a8bf60(n);
        FUN_00a8cc40(n);
        SI(0x28) = SI(0x28) | 0x10;
        float halfY = (float)subdivOwner * 0.5f;
        if (count <= 0) break;
        for (int i = 0; i < count; ++i) {
            float fi = ((float)i - halfExtent) * step;
            for (int j = 0; j < count * 2; ++j) {
                float u = fi * subdivScaleX + subdivOff;
                float v = ((((float)j - (float)(count * 2 - 1) * 0.5f) * step) * 0.5f) *
                          (float)subdivOwner + subdivScaleY;
                float w = 0.0f + subdivScaleZ;
                Sample rec;
                rec.px = u; rec.py = v; rec.pz = w; rec.scale = preScale;
                PushSample(self, &rec);
                float t = (v * DAT_0156502c) * DAT_01678278 + 12582912.0f;
                float rad = sqrtf(1.0f - u * u);
                float a = DAT_01677840[((unsigned)t & 0xf) * 2];
                float d = v * DAT_0156502c - (float)((int)t - 0x4b400000) * _DAT_01678300;
                float b = DAT_01677844[((unsigned)t & 0xf) * 2];
                float rx = (b - ((d * b) * 0.5f + a) * d) * rad;
                float ry = ((b - (d * a) * 0.5f) * d + a) * rad;
                float rz = u;
                if ((tf.flags & 2) != 0) {
                    float ox = rx, oy = ry, oz = rz;
                    rx = oz * tf.rot.z.x + oy * tf.rot.y.x + ox * tf.rot.x.x;
                    ry = oz * tf.rot.z.y + oy * tf.rot.y.y + ox * tf.rot.x.y;
                    rz = oz * tf.rot.z.z + oy * tf.rot.y.z + ox * tf.rot.x.z;
                }
                tf.flags |= 4;
                tf.mod = (short)(tf.mod + 1);
                float wx = rx * preScale + tf.tx;
                float wy = tf.ty + ry * preScale;
                float wz = tf.tpad + rz * preScale;
                if (!(colorScale != 0.0f) || FUN_00a89a90(&wx, (int)timeAcc + 1, count) == 0) {
                    FUN_00537f40(desc);
                    (void)FUN_00a89980(&rec, timeAcc);
                    PushSample(self, &rec);
                    timeAcc = (float)((int)timeAcc + 1);
                }
            }
        }
        return;
    }
    case 4: {
        int n = count * count * count;
        FUN_00a8bf60(n);
        FUN_00a8cc40(n);
        for (int i = 0; i < count; ++i) {
            float fi = ((float)i - halfExtent) * step;
            for (int j = 0; j < count; ++j) {
                float fj = ((float)j - halfExtent) * step;
                for (int k = 0; k < count; ++k) {
                    float fk = ((float)k - halfExtent) * step;
                    float x = fi * subdivScaleX + subdivOff;
                    float y = ((float)j - halfExtent) * step * (float)subdivOwner + subdivScaleY;
                    float z = fk * (float)surfBegin + subdivScaleZ;
                    float u = x + subdivOff;
                    float v = subdivScaleX + y;
                    float w = subdivScaleY + z;
                    Sample rec;
                    rec.px = u; rec.py = v; rec.pz = w; rec.scale = preScale;
                    PushSample(self, &rec);
                    float rx = u, ry = v, rz = w;
                    if ((tf.flags & 2) != 0) {
                        float ox = rx, oy = ry, oz = rz;
                        rx = oz * tf.rot.z.x + oy * tf.rot.y.x + ox * tf.rot.x.x;
                        ry = oz * tf.rot.z.y + oy * tf.rot.y.y + ox * tf.rot.x.y;
                        rz = oz * tf.rot.z.z + oy * tf.rot.y.z + ox * tf.rot.x.z;
                    }
                    tf.flags |= 4;
                    tf.mod = (short)(tf.mod + 1);
                    float wx = rx * preScale + tf.tx;
                    float wy = tf.ty + ry * preScale;
                    float wz = tf.tpad + rz * preScale;
                    if (!(colorScale != 0.0f) || FUN_00a89a90(&wx, (int)timeAcc + 1, count) == 0) {
                        FUN_00537f40(desc);
                        (void)FUN_00a89980(&rec, timeAcc);
                        PushSample(self, &rec);
                        timeAcc = (float)((int)timeAcc + 1);
                    }
                }
            }
        }
        return;
    }
    case 6: {
        int n = count * count * 6;
        FUN_00a8bf60(n);
        FUN_00a8cc40(n);
        SI(0x28) = SI(0x28) | 0x20;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < count; ++j) {
                float fj = ((float)j - halfExtent) * step;
                for (int k = 0; k < count; ++k) {
                    float fk = ((float)k - halfExtent) * step;
                    float u = fj * subdivScaleX + subdivOff;
                    float v = (float)i * (float)surfBegin + subdivScaleY;
                    float w = fk * (float)subdivOwner + subdivScaleZ;
                    Sample rec;
                    rec.px = u; rec.py = v; rec.pz = w; rec.scale = preScale;
                    PushSample(self, &rec);
                    float invLen = 1.0f / sqrtf((u * u + v * v) + 1.0f);
                    int tbl = (((int)u) >> 1) * 4;   // use u as the face coordinate
                    float sgn = ((int)u & 1) ? -invLen : invLen;
                    float n[3];
                    n[0] = sgn * u;
                    n[1] = invLen * v;
                    n[2] = sgn;
                    if ((tf.flags & 2) != 0) {
                        float ox = n[0], oy = n[1], oz = n[2];
                        n[0] = ox * tf.rot.x.x + oy * tf.rot.y.x + oz * tf.rot.z.x;
                        n[1] = ox * tf.rot.x.y + oy * tf.rot.y.y + oz * tf.rot.z.y;
                        n[2] = ox * tf.rot.x.z + oy * tf.rot.y.z + oz * tf.rot.z.z;
                    }
                    tf.flags |= 4;
                    tf.mod = (short)(tf.mod + 1);
                    float wx = n[0] * preScale + tf.tx;
                    float wy = tf.ty + n[1] * preScale;
                    float wz = tf.tpad + n[2] * preScale;
                    if (!(colorScale != 0.0f) || FUN_00a89a90(&wx, (int)timeAcc + 1, count) == 0) {
                        FUN_00537f40(desc);
                        (void)FUN_00a89980(&rec, timeAcc);
                        PushSample(self, &rec);
                        timeAcc = (float)((int)timeAcc + 1);
                    }
                    (void)tbl;
                }
            }
        }
        return;
    }
    default: {
        // single sample at the mPreTransform origin
        Sample rec;
        rec.px = DAT_0167827c; rec.py = DAT_01678280; rec.pz = DAT_01678284;
        rec.scale = DAT_01678230;
        PushSample(self, &rec);
        return;
    }
    }
}
