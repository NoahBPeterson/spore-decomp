// Slice s00e76880 -- SPGonzago/SPCellGame.obj (cell stage): the leak/attachment
// spawn helpers and the loot-drop routine, plus two small per-frame updaters.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
#include "types.h"

#pragma intrinsic(sqrt)
#pragma intrinsic(sin)
#pragma intrinsic(cos)
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

// ---------------------------------------------------------------- raw offset accessors
#define I(p,o) (*(int*)((char*)(p) + (o)))
#define U(p,o) (*(uint32*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define B(p,o) (*(uint8*)((char*)(p) + (o)))
#define GF(a)  (*(float*)(a))
#define GI(a)  (*(int*)(a))

struct cSPTransform {                 // 0x38 bytes, embedded at cell + 0x48
    uint16 mFlags;
    uint16 mModCount;
    float  mTranslation[3];
    float  mScale;
    float  mRotation[9];
};

struct ResourceKey { uint32 instanceID, typeID, groupID; };
int* GetCellResource(ResourceKey key);                       // 0x00e679e0

struct ObjectPool {                   // cSPObjectPool, at gspCellGame+0x1c
    void* Get(int id);                // 0x00b72210
    void* GetSafe(int id);            // 0x00b721d0
};
extern char* gspCellGame;             // 0x016b3c04

struct RandomLCG {                    // EA::Random::RandomLinearCongruential
    uint32 RandomUint32Uniform(uint32 range);   // 0x00a68fb0
    double RandomDoubleUniform();               // 0x009360d0
};
extern RandomLCG gRandomLCG;          // 0x01601760

extern float gOrientUp[3];            // 0x015a7c34 orientation basis
extern float gUp_015a7c40[3];         // 0x015a7c40 reference "up"
extern float gMatrix_016b3dac;        // 0x016b3dac identity matrix source
extern float gOne;                    // 0x01485720 = 1.0f
extern float gMinPos;                 // 0x014851ec = 1.5258789e-05f

// ---------------------------------------------------------------- helpers
unsigned FUN_00e68630(int cell);                                   // 0x00e68630
char     FUN_00e69580(int* cell);                                  // 0x00e69580
void     FUN_00e68000(int cell, int arg, cSPTransform* xf);        // 0x00e68000
void     FUN_00e76660(int* cell, int arg, void* xf);               // 0x00e76660
void     FUN_00e71980(float dt);                                   // 0x00e71980
void     FUN_00e82130(void* iter);                                 // 0x00e82130
void     FUN_00743b50(void* iter);                                 // 0x00743b50
void*    FUN_00e4cc40(int id, void* iter);                         // 0x00e4cc40 (thunk)
int      FUN_00e4cce0(int id);                                     // 0x00e4cce0
void     FUN_00e61b90(int a, int b);                               // 0x00e61b90
char     FUN_00e699b0(void* a, int b);                             // 0x00e699b0
char     FUN_00e5d340();                                           // 0x00e5d340
int      FUN_00e50990(int a);                                      // 0x00e50990
void     FUN_00e780a0(int handle, int a, int b, int c);            // 0x00e780a0
float*   FUN_00e5cae0();                                           // 0x00e5cae0
int      FUN_00e76480(int a, int b, const void* c, const void* d,
                      const void* e, int f, int g, int h, int i, int j, int k); // 0x00e76480
int      FUN_00e74a20(int a1, float* pos, int a3, int a4, int a5, float a6,
                      float a7, float a8, const void* def, int a10);   // 0x00e74a20
void     sAttach(int handle, int idx, int obj, cSPTransform* xf, int flag); // 0x00e5f450

// math helpers
void     Matrix33_ctor(void* self, const void* src);               // 0x0041cb40
float*   Matrix3FromFacingAndUp(float* out, const float* facing, const float* up); // 0x0069b440
float*   Matrix3FromQuaternion(float* out, const float* q);        // 0x0059c190
void     QuaternionFromFacingAndUp(float* out, const float* facing, const float* up); // 0x0069b600
void     FUN_0040efa0(void* self);                                 // 0x0040efa0
void     ComposeTransforms(cSPTransform* xf);                      // 0x0040ccb0

// @ 0x00e76880  per-frame "leak" / drip update (subject arrives in ESI)
void FUN_00e76880(void* cell, float dt)
{
    B(cell, 0x1ac) = 0;
    if (FUN_00e68630((int)cell)) {
        B(cell, 0x1ac) = 1;
        FUN_00e69580((int*)cell);
        int* res = GetCellResource(*(ResourceKey*)((char*)cell + 0xfc));
        float s = F(cell, 0x90) * F(cell, 0x90) +
                  F(cell, 0x94) * F(cell, 0x94) +
                  F(cell, 0x98) * F(cell, 0x98);
        float f = (float)sqrt((double)s);
        f = ((f + f) + 1.0f) * dt + F(cell, 0x374);
        F(cell, 0x374) = f;

        int n = I(res, 0x1274);
        if (1.0f < f && 0 < n) {
            cSPTransform xf;
            xf.mFlags = 0;
            xf.mModCount = 0;
            xf.mTranslation[0] = gOrientUp[0];
            xf.mTranslation[1] = gOrientUp[1];
            xf.mTranslation[2] = gOrientUp[2];
            xf.mScale = gOne;
            Matrix33_ctor(xf.mRotation, &gMatrix_016b3dac);
            for (int i = 0; i < n; i++) {
                FUN_00e68000((int)cell, I(res, 0x1278 + i * 4), &xf);
                FUN_00e76660((int*)cell, I(res, 0x1278 + i * 4), &xf);
                F(cell, 0x374) = 0.0f;
            }
        }
    }
}

// @ 0x00e76a80  accumulates a timer and re-runs the leak update (subject in EAX)
void FUN_00e76a80(void* cell, float dt)
{
    float f = dt + F(cell, 0x154);
    F(cell, 0x154) = f;
    while (0.3f < f) {
        f = F(cell, 0x154) - 0.3f;
        F(cell, 0x154) = f;
    }
    FUN_00e71980(dt);
    FUN_00e76880(cell, dt);
}

// @ 0x00e76af0  SP::sCreateLeakAttachment
int sCreateLeakAttachment(void* obj, float* pos, int a3, int a4, int a5)
{
    float facing[3];
    facing[0] = gOrientUp[0];
    facing[1] = gOrientUp[1];
    facing[2] = gOrientUp[2];

    float dx = F(obj, 0x4c) - pos[0];
    float dy = F(obj, 0x50) - pos[1];
    float dz = F(obj, 0x54) - pos[2];
    if (gMinPos < dx * dx + dy * dy + dz * dz) {
        float inv = (float)(1.0 / sqrt((double)(dx * dx + dy * dy + dz * dz)));
        facing[0] = inv * dx;
        facing[1] = dy * inv;
        facing[2] = dz * inv;
    }

    cSPTransform xf;
    xf.mFlags = 0;
    xf.mModCount = 0;
    Matrix33_ctor(xf.mRotation, &gMatrix_016b3dac);
    xf.mTranslation[0] = pos[0];
    xf.mTranslation[1] = pos[1];
    xf.mTranslation[2] = pos[2];
    xf.mFlags |= 4;
    xf.mModCount += 1;

    float mat[9];
    Matrix3FromFacingAndUp(mat, facing, gUp_015a7c40);
    xf.mScale = F(obj, 0x58);
    for (int i = 0; i < 9; i++)
        xf.mRotation[i] = mat[i];

    cSPTransform parent;
    parent.mFlags = *(uint16*)((char*)obj + 0x48);
    parent.mModCount = *(uint16*)((char*)obj + 0x4a);
    xf.mFlags |= 2;
    parent.mTranslation[0] = F(obj, 0x4c);
    parent.mTranslation[1] = F(obj, 0x50);
    parent.mTranslation[2] = F(obj, 0x54);
    parent.mScale = F(obj, 0x58);
    Matrix33_ctor(parent.mRotation, (char*)obj + 0x5c);

    FUN_0040efa0(parent.mRotation);
    ComposeTransforms(&xf);

    float quat[4];
    QuaternionFromFacingAndUp(quat, facing, gUp_015a7c40);

    int created = FUN_00e74a20(I(obj, 0x35c), pos, I(obj, 0x80), a4, a3, F(obj, 0x58),
                               0.0f, 1.0f, quat, 0);
    sAttach(I(obj, 0), a5, created, &parent, 1);
    void* pool = (char*)gspCellGame + 0x1c;
    int inst = (int)((ObjectPool*)pool)->Get(created);
    I(inst, 0x14c) = I(obj, 0);
    return created;
}

// @ 0x00e76d70  SP::sCreateCellAttachment
int sCreateCellAttachment(void* obj, char flag, float* pos, int a4, int a5, int a6)
{
    float facing[3];
    facing[0] = gOrientUp[0];
    facing[1] = gOrientUp[1];
    facing[2] = gOrientUp[2];

    float dx = F(obj, 0x4c) - pos[0];
    float dy = F(obj, 0x50) - pos[1];
    float dz = F(obj, 0x54) - pos[2];
    if (gMinPos < dx * dx + dy * dy + dz * dz) {
        float inv = (float)(1.0 / sqrt((double)(dx * dx + dy * dy + dz * dz)));
        facing[0] = inv * dx;
        facing[1] = dy * inv;
        facing[2] = dz * inv;
    }

    float q[4];
    QuaternionFromFacingAndUp(q, facing, gUp_015a7c40);

    if (flag != 0) {
        double ang = (double)(gUp_015a7c40[0] * 0.0f) + (double)GF(0x015a7c1c);
        float sn = (float)sin(ang);
        float cs = (float)cos(ang);
        float v0 = sn * gUp_015a7c40[0];
        float v1 = sn * gUp_015a7c40[1];
        float v2 = sn * gUp_015a7c40[2];
        float q0 = q[0], q1 = q[1], q2 = q[2], q3 = q[3];
        float r0 = q1 * v2 - q2 * v1;
        float r1 = q2 * v0 - v2 * q0;
        float r2 = v1 * q0 - q1 * v0;
        float c1 = q2 * v2;
        float r3 = q3 * v0 + cs * q0;
        float r4 = q3 * v1 + q1 * cs;
        float r5 = q3 * v2 + q2 * cs;
        q2 = r5 + r2;
        q1 = q3 * cs - ((q0 * v0 + c1) + q1 * v1);
        q0 = r3 + r0;
        q3 = r4 + r1;
    }

    int created = FUN_00e74a20(I(obj, 0x35c), pos, I(obj, 0x80), a5, a4, 1.0f, 0.0f, 1.0f,
                               q, a6);
    int inst = (int)((ObjectPool*)((char*)gspCellGame + 0x1c))->Get(created);

    cSPTransform xf;
    xf.mFlags = 0;
    xf.mModCount = 0;
    Matrix33_ctor(xf.mRotation, &gMatrix_016b3dac);
    xf.mTranslation[0] = pos[0];
    xf.mTranslation[1] = pos[1];
    xf.mTranslation[2] = pos[2];
    xf.mFlags |= 4;
    xf.mModCount += 1;

    float mat[9];
    Matrix3FromQuaternion(mat, q);
    xf.mScale = F(inst, 0x58);
    for (int i = 0; i < 9; i++)
        xf.mRotation[i] = mat[i];

    cSPTransform parent;
    parent.mFlags = *(uint16*)((char*)obj + 0x48);
    parent.mModCount = *(uint16*)((char*)obj + 0x4a);
    xf.mFlags |= 2;
    parent.mTranslation[0] = F(obj, 0x4c);
    parent.mTranslation[1] = F(obj, 0x50);
    parent.mTranslation[2] = F(obj, 0x54);
    parent.mScale = F(obj, 0x58);
    Matrix33_ctor(parent.mRotation, (char*)obj + 0x5c);

    FUN_0040efa0(parent.mRotation);
    ComposeTransforms(&xf);

    sAttach(I(obj, 0), -1, created, &parent, 1);
    return created;
}

// @ 0x00e771d0  SP::sDropLoot
void sDropLoot(int a1, void* key, int a3, float* pos, float radius, int lvl,
               int a7, int a8, void* out, int* outCount)
{
    if (a7 == 0)
        return;
    if (B(gspCellGame, 0x518c) != 0 && a1 != FUN_00e4cce0(1))
        return;

    int it[4];
    FUN_00743b50(it);
    int* tbl = (int*)FUN_00e4cc40(a7, it);
    if (tbl[6] != 0)
        FUN_00e61b90(a3 != I(gspCellGame, 0x40fc) ? 1 : 0, 0);

    int count = tbl[1];
    int chosen = -1;
    float acc = 0.0f;
    if (0 < count) {
        int off = 0;
        int i = 0;
        do {
            int* e = (int*)(tbl[0] + off);
            bool skip = false;
            if (*e != 1) {
                skip = true;
            } else {
                int it2[4];
                FUN_00743b50(it2);
                int* slot = (int*)FUN_00e4cc40(e[1], it2);
                if (I(slot, 0xb4) != 6) {
                    FUN_00e82130(it2);
                    skip = true;
                } else {
                    int sub = I(slot, 0xb8);
                    FUN_00e82130(it2);
                    if (sub == 0) {
                        skip = true;
                    } else if (I(I(gspCellGame, 0x5190), 0x34 + sub * 4) == 0) {
                        if ((B(tbl, 0x1c) == 0 || FUN_00e699b0(key, sub)) &&
                            !FUN_00e5d340()) {
                            float minY = GF(0x016b3c8c);
                            float minZ = GF(0x016b3c90);
                            float maxX = GF(0x016b3c94);
                            float maxY = GF(0x016b3c98);
                            float maxZ = GF(0x016b3c9c);
                            float cy = (maxY + minY) * 0.5f;
                            float cz = (maxZ + minZ) * 0.5f;
                            float cx = (maxX + minY) * 0.5f;
                            float loY = (minY - cy) * 0.75f + cy;
                            float loZ = (minZ - cz) * 0.75f + cz;
                            bool inside =
                                ((maxX - cx) * 0.75f + cx <= pos[0] && pos[0] <= cx) &&
                                loY <= pos[1] &&
                                pos[1] <= (maxY - cy) * 0.75f + cy &&
                                loZ <= pos[2] &&
                                pos[2] <= (maxZ - cz) * 0.75f + cz;
                            if (inside || B(gspCellGame, 0x518c) != 0)
                                skip = true;
                        }
                    }
                }
            }
            if (skip) {
                acc += (float)e[3];
                double r = gRandomLCG.RandomDoubleUniform() * (double)acc;
                if (r < 0.0)
                    r = 0.0;
                if (r < (double)(float)e[3])
                    chosen = i;
            }
            off += 0x1c;
            i++;
        } while (i < count);
    }

    if (chosen != -1) {
        int base = tbl[0] + chosen * 0x1c;
        int kind = I(base, 0);
        if (kind == 2) {
            int n = (int)gRandomLCG.RandomUint32Uniform(U(base, 0x14));
            int num = I(base, 0x10) + n;
            if (0 < num) {
                do {
                    sDropLoot(a1, key, a3, pos, radius, lvl, I(base, 8), a8, out, outCount);
                    num--;
                } while (num != 0);
                FUN_00e82130(it);
                return;
            }
        } else if (kind == 1) {
            float lo = (float)I(base, 8);
            float hi = (float)I(base, 0xc);
            if (hi == 0.0f)
                hi = radius;
            int n = (int)gRandomLCG.RandomUint32Uniform(U(base, 0x14));
            int num = I(base, 0x10) + n;
            int hasPool = 0;
            int r = FUN_00e50990(I(base, 4));
            if (r != 0) {
                int ex = I(gspCellGame, 0x516c);
                int c = (int)((ObjectPool*)((char*)gspCellGame + 0x1c))->GetSafe(ex);
                if (c != 0) {
                    B(c, 0x354) = 0;
                    FUN_00e780a0(ex, 0, 0, 0);
                    I(gspCellGame, 0x516c) = 0;
                }
                hasPool = 1;
            }
            if (0 < num) {
                int cnt = num;
                do {
                    double rnd = gRandomLCG.RandomDoubleUniform();
                    float t = (float)((double)(hi - lo) * rnd + (double)lo);
                    float* o1 = FUN_00e5cae0();
                    float p0 = pos[0] + t * o1[0];
                    float p1 = pos[1] + o1[1] * t;
                    float p2 = pos[2] + o1[2] * t;
                    float* o2 = FUN_00e5cae0();
                    float rr = (float)tbl[5];
                    float r0 = o2[0] * rr;
                    float r1 = o2[1] * rr;
                    float r2 = o2[2] * rr;
                    int sub = I(base, 0x18) + a7;
                    if (sub < 0 || 0x13 < sub)
                        sub = 0x13;
                    int made = FUN_00e76480(I(base, 4), a3, &sub, &p0, &r0, 0, tbl[4],
                                            a8, tbl[8], 0x3f400000, -1);
                    if (hasPool) {
                        int c2 = (int)((ObjectPool*)((char*)gspCellGame + 0x1c))->GetSafe(
                                     I(gspCellGame, 0x516c));
                        if (c2 != 0)
                            *(int*)((char*)c2 + *outCount * 4) = made;
                        (void)c2;
                    }
                    cnt--;
                } while (cnt != 0);
            }
            int ex2 = I(gspCellGame, 0x516c);
            int c3 = (int)((ObjectPool*)((char*)gspCellGame + 0x1c))->GetSafe(ex2);
            if (c3 != 0)
                B(c3, 0x354) = 1;
        }
    }
    FUN_00e82130(it);
}
