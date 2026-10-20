// nSPCreatureAnim root-update helpers (0x009b95d0-0x009ba180).
//
// Same family as slice s009b4e00: an array of "bone" records (stride 0x468) hung
// off +0x384, records carrying a local offset at +0x10c, a transform at
// +0x118..0x344, world positions at +0x344 and +0x350, linked indices at
// +0x1f8/+0x1fc, a child span at +0x204/+0x208 and a bit set at +0x1b8.
//
// Offsets follow the retail image.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#pragma intrinsic(fabs)
#pragma intrinsic(sqrt)

// float constants (declared extern so the load emits as a relocation)
extern const float g_14471fc;  // 0.0f               0x014471fc
extern const float g_1485720;  // 1.0f               0x01485720
extern const float g_1485378;  // 0.1f               0x01485378
extern const float g_1488874;  // 0.0f sentinel      0x01488874
extern const float g_1485544;  // 0.75f              0x01485544
extern const float g_13eb960;  // 0.01f              0x013eb960
extern const float g_1471064;  // 0.5f               0x01471064
extern const float g_1550d2c;  // quat w             0x01550d2c
extern const float g_1550d30;  // quat x             0x01550d30
extern const float g_1550d34;  // quat y             0x01550d34
extern const float g_1550d38;  // angle scale        0x01550d38
extern const float g_1550d14;  // axis x             0x01550d14
extern const float g_1550d18;  // axis y             0x01550d18
extern const float g_1550d1c;  // axis z             0x01550d1c
extern const float g_1550d04;  // clamp high         0x01550d04
extern const float g_1550d7c;  // scale x            0x01550d7c
extern const float g_1550d80;  // scale y            0x01550d80
extern const float g_1550d84;  // scale z            0x01550d84
extern const float g_13eb8b0;  // sign mask          0x013eb8b0
extern int g_15509e4;          // root-update enable 0x015509e4
extern int g_15509e8;          // extra-update enable 0x015509e8
extern char g_1550c2c;         // flag source select 0x01550c2c

// image functions
void* __cdecl FUN_009b9250(void* q);                                     // 0x009b9250
void* __cdecl FUN_009b9340(void* out, int inst, int b, float scale);     // 0x009b9340
float __cdecl FUN_009b3110(void* p);                                     // 0x009b3110
void  __cdecl FUN_009b39e0(float v);                                     // 0x009b39e0
void  __cdecl FUN_0099cae0(void* out, void* in, int mode);               // 0x0099cae0 quat normalize
int   __cdecl FUN_009d0460(void* out, float a);                          // 0x009d0460
double __cdecl FUN_009d3530(void* g);                                    // 0x009d3530
double __cdecl FUN_009ce700(void* g);                                    // 0x009ce700
void  __cdecl FUN_009d0a40(void* out, void* obj);                        // 0x009d0a40
int   __cdecl FUN_00ff3ba0(void* h);                                     // 0x00ff3ba0
int   __cdecl GetPoliticalID(void* g);                                   // 0x0097e850
float __cdecl GetFootprintRadius(void* o);                               // 0x00c37030

// slice s009b4e00 entry points
void __cdecl FUN_009b95d0(void* a, int b, int c, float d);
void __cdecl FUN_009b9ac0(void* a, int b, int c);

struct Bone {
    unsigned char pad0[0x1f8];
    int mPrevIndex;                 // +0x1f8
    int mNextIndex;                 // +0x1fc
    int mChildFirst;                // +0x204
    int mChildCount;                // +0x208
    unsigned char pad1[0x344 - 0x20c];
    float mPosX;                    // +0x344
    float mPosY;                    // +0x348
    float mPosZ;                    // +0x34c
    float mAttX;                    // +0x350
    float mAttY;                    // +0x354
    float mAttZ;                    // +0x358
};

struct Body {
    unsigned char pad0[0x7c];
    float mVelX;                    // +0x7c
    float mVelY;                    // +0x80
    float mVelZ;                    // +0x84
    float mVelW;                    // +0x88
    float mRadX;                    // +0x8c
    float mRadY;                    // +0x90
    float mRadZ;                    // +0x94
    float mRadW;                    // +0x98
    float mBlend;                   // +0x9c
    float mScaleX;                  // +0xa0
    float mScaleY;                  // +0xa4
    float mScaleZ;                  // +0xa8
};

struct Quat { float x, y, z, w; };

static inline Quat qmul(const Quat& a, const Quat& b)
{
    Quat r;
    r.x = ((a.x * b.w + a.w * b.x) - a.y * b.z) + a.z * b.y;
    r.y = ((a.y * b.w + a.w * b.y) + a.z * b.x) - a.x * b.z;
    r.z = ((a.z * b.w - a.y * b.x) + a.x * b.y) + a.w * b.z;
    r.w = ((a.w * b.w - a.x * b.x) - a.y * b.y) - a.z * b.z;
    return r;
}

// @ 0x009b95d0
// ghost `ecx` holds the anim owner; the first stack arg is the creature instance.
// Declared __fastcall so `ecx` is live and the owner is reachable at slot 0.
void __fastcall UpdateRootPosition(int* inst, int* unused, float dt, int* owner, float scale)
{
    Body* body = *(Body**)((char*)inst + 0);
    float vx, vy, vz;
    if (*(char*)((char*)inst + 0x24) == 0) {
        float* a = (float*)FUN_009b9250((char*)body + 0x10);
        float* b = (float*)FUN_009b9340((void*)0, (int)inst, (int)owner, scale);
        vx = b[0] + a[0];
        vy = b[1] + a[1];
        vz = b[2] + a[2];
    } else {
        double f = FUN_009d3530((char*)owner + 0x15b8);
        float* q = (float*)FUN_009d0460((void*)0, (float)f);
        vx = q[0];
        vy = q[1];
        vz = q[2];
    }
    int* b0 = *(int**)((char*)body + 0);
    if (body->mVelW <= 1e-06f) {
        float s = *(float*)((char*)body + 4);
        body->mVelX = (*(float*)((char*)b0 + 0x10c) * s + vx) * dt;
        body->mVelY = (*(float*)((char*)b0 + 0x110) * s + vy) * dt;
        body->mVelZ = (*(float*)((char*)b0 + 0x114) * s + vz) * dt;
        body->mVelW = dt;
    } else {
        float inv = 1.0f / body->mVelW;
        body->mVelX = body->mVelX + (inv * body->mVelX + vx) * dt;
        body->mVelY = body->mVelY + (inv * body->mVelY + vy) * dt;
        body->mVelZ = body->mVelZ + (inv * body->mVelZ + vz) * dt;
        body->mVelW = body->mVelW + dt;
    }
    if (0.0f < dt) {
        unsigned int idx = *(unsigned int*)(b0 + 0x1f8);
        unsigned char* p = (unsigned char*)(*(int*)((char*)body + 4) + 0x1b8 + ((idx & 0x7fffffff) >> 2));
        *p = *p | (unsigned char)(2 << ((idx * 2) & 7));
    }
}

// @ 0x009b97c0
// __thiscall BuildOrientation(quat, instance, spatialObject): 4 stack args (ret 0xc)
int* BuildOrientation(int* out, int* inst, char* so, void* self, float scale)
{
    Quat ext;
    ext.x = *(float*)(so + 0x3c);
    ext.y = *(float*)(so + 0x40);
    ext.z = *(float*)(so + 0x44);
    int* b = *(int**)((char*)inst + 0);
    float s = *(float*)(*(int*)((char*)((char*)b + 0)) + 0x70);
    Quat ax;
    ax.x = (float)b[0x10c / 4] * s;
    ax.y = (float)b[0x110 / 4] * s;
    ax.z = (float)b[0x114 / 4] * s;
    float lim = (ext.z <= 0.1f) ? 0.1f : ext.z;
    float r = lim * 0.75f;
    if (r <= 0.01f)
        r = 0.01f;
    float dia = GetFootprintRadius(so) * 2.0f;
    if (r <= dia)
        r = 0;
    if (r != 0) { /* keep r */ }
    float ratio = (r != 0 ? r : dia) / r;
    if (ratio > 1.0f)
        ratio = 1.0f;
    double t = FUN_009d3530((char*)self + 0x15b8);
    double st = FUN_009ce700((char*)self + 0x15b8);
    (void)t; (void)st;
    float k = ratio;
    float px, py, pz;
    FUN_009d0a40((void*)&px, so);
    (void)py;
    ext.x = ((ext.x * g_1550d80) * k) * ext.x;
    ext.y = ((ext.y * g_1550d84) * k) * ext.y;
    ext.z = ((ext.z * g_1550d7c) * k) * ext.z;
    float lo = -g_1550d04;
    if (ext.x < lo) ext.x = lo;
    if (g_1550d04 < ext.x) ext.x = g_1550d04;
    if (ext.y < lo) ext.y = lo;
    if (g_1550d04 < ext.y) ext.y = g_1550d04;
    if (ext.z < lo) ext.z = lo;
    if (g_1550d04 < ext.z) ext.z = g_1550d04;
    out[0] = (int)0;
    out[0] = 0;
    return out;
}

// @ 0x009b9a00
// The out pointer arrives in `esi` (ghost register argument), then `[esp+4]` is
// the stacked float.  Modelled with an explicit register parameter.
float* QuatFromAxisAngle(float angle, float out[4], float unused)
{
    out[0] = g_1550d2c;
    out[1] = g_1550d30;
    out[2] = g_1550d34;
    out[3] = g_1550d38;
    if (fabsf(angle) > 1e-06f) {
        FUN_009b39e0(angle);
        float s = g_1550d38 * 0.5f;
        float sn = (float)sin((double)s);
        float cs = (float)cos((double)s);
        out[0] = g_1550d14 * sn;
        out[1] = g_1550d18 * sn;
        out[2] = g_1550d1c * sn;
        out[3] = cs;
    }
    return out;
}

// @ 0x009b9ac0
// __thiscall IntegrateOrientation(instance, h, prim, dt): 3 stack args (ret 0xc).
// Composes the frame quaternion with the instance quaternion, normalises, and
// then either seeds or accumulate-normalises the body quaternion.
void __fastcall FUN_009b9ac0(int* self, int* inst, int h, int prim, float dt)
{
    Body* body = *(Body**)((char*)inst + 0);
    Quat a;
    BuildOrientation((int*)&a, inst, (char*)prim, self, dt);
    Quat b;
    QuatFromAxisAngle(*(float*)((char*)self + 0x15c4), (float*)&b, 0.0f);
    Quat q = qmul(b, a);
    if (body->mBlend <= 1e-06f) {
        Quat w = qmul(a, *(Quat*)((char*)body + 0));
        Quat n;
        FUN_0099cae0((void*)&n, (void*)&w, 0);
        body->mVelX = n.x * dt;
        body->mVelY = n.y * dt;
        body->mVelZ = n.z * dt;
        body->mVelW = n.w * dt;
        body->mBlend = dt;
    } else {
        float len = sqrtf(((body->mVelX * body->mVelX + body->mVelY * body->mVelY) +
                           body->mVelZ * body->mVelZ) + body->mVelW * body->mVelW);
        if (len != 0.0f) {
            float inv = g_1485720 / len;
            body->mVelX = body->mVelX * inv;
            body->mVelY = body->mVelY * inv;
            body->mVelZ = body->mVelZ * inv;
            body->mVelW = body->mVelW * inv;
        }
        Quat cur = *(Quat*)((char*)body + 0x0);
        Quat n;
        FUN_0099cae0((void*)&n, (void*)&cur, 0);
        n.x = n.x * dt;
        n.y = n.y * dt;
        n.z = n.z * dt;
        n.w = n.w * dt;
        if (0.0f <= ((body->mVelX * n.x + body->mVelY * n.y) + body->mVelZ * n.z) + body->mVelW * n.w) {
            body->mVelX = body->mVelX + n.x;
            body->mVelY = body->mVelY + n.y;
            body->mVelZ = body->mVelZ + n.z;
            body->mVelW = body->mVelW + n.w;
        } else {
            body->mVelX = body->mVelX - n.x;
            body->mVelY = body->mVelY - n.y;
            body->mVelZ = body->mVelZ - n.z;
            body->mVelW = body->mVelW - n.w;
        }
        body->mBlend = body->mBlend + dt;
    }
    if (0.0f < dt) {
        unsigned int idx = *(unsigned int*)((char*)body + 4 - 4);
        (void)idx;
        unsigned int link = *(unsigned int*)(*(int*)((char*)body + 0) + 0x1f8);
        unsigned char* p = (unsigned char*)(*(int*)((char*)body + 4) + 0x1b8 + ((link & 0x7fffffff) >> 2));
        *p = *p | (unsigned char)(2 << ((link * 2) & 7));
    }
}

// @ 0x009ba040
void __fastcall UpdateRoots(char* self, void* unused, float param)
{
    if (!(g_14471fc < param) || *(char*)(self + 0x262) == 0)
        return;
    {
        int* p = (int*)GetPoliticalID(self + 0x15b8);
        int n = (p[1] - p[0]) / 0x104;
        if (n <= 0)
            return;
        {
            int stride = 0;
            do {
                p = (int*)GetPoliticalID(self + 0x15b8);
                int base = p[0];
                p = (int*)FUN_00ff3ba0(self + 0x15b8);
                int cnt = (p[1] - p[0]) / 0x38;
                if (0 < cnt) {
                    int off = 0;
                    do {
                        p = (int*)FUN_00ff3ba0(self + 0x15b8);
                        int node = *(int*)(p[0] + off);
                        int ptr = p[0] + off;
                        if (0.0f < *(float*)(node + 0x4c) &&
                            ((*(unsigned int*)(*(int*)(node + 0)) >> 4 & 1) == 0)) {
                            if (g_15509e4 != 0)
                                FUN_009b95d0((void*)ptr, base + stride, 0, 1.0f);
                            if (g_15509e8 != 0)
                                FUN_009b9ac0((void*)ptr, base + stride, 0);
                        }
                        off += 0x38;
                        --cnt;
                    } while (cnt != 0);
                }
                stride += 0x104;
                --n;
            } while (n != 0);
        }
    }
}

// @ 0x009ba180
// __fastcall FindRootChain(this, out, a, b, node, dbg, hasParent, checkKids, a9, a10, a11)
// where `out` and the three characters arrive in edx/stack slots and `this`
// (the anim owner) is in ecx.
int __fastcall FindRootChain(int* self, int* out, int a, int b, int node, char dbg,
                             char hasParent, char checkKids, char a9, char a10, char a11)
{
    if (a10 == 0 && (*(unsigned char*)(node + 0x154) & 4) != 0)
        return 0;
    if (a11 == 0) {
        for (int n = *(int*)(node + 0x214); n != 0; n = *(int*)(n + 0x214)) {
            if ((*(unsigned char*)(n + 0x154) & 4) != 0)
                return 0;
        }
    }
    if (checkKids != 0) {
        unsigned int cnt = *(unsigned int*)(node + 0x208);
        unsigned int i = 0;
        if (cnt != 0) {
            int k = *(int*)(node + 0x204) * 0x468 + 0x150 + *(int*)((char*)self + 900);
            do {
                if (*(int*)(k + 0xb8) > 0)
                    return 0;
                if (FUN_009b3110((void*)k) != 0)
                    return 0;
                ++i;
                k += 0x468;
            } while (i < cnt);
        }
    }
    unsigned int nflags = 0;
    int* walk = (int*)(node + 0x158);
    while (nflags < 0x20) {
        if (*walk == 0)
            break;
        ++nflags;
        ++walk;
    }
    if (checkKids == 0 && 0 < nflags)
        return 0;
    if (dbg != 0) {
        out[0] = *(int*)(node + 0x1f8);
        out[1] = -1;
        return 1;
    }
    return 0;
}
