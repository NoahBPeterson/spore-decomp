// Slice s00749370 (0x00749370..0x0074A070): SP::cModelWorld frustum/pick queries,
// /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <new>
#include <string.h>

struct Vec3 { float x, y, z; };
struct cSPTransform {
    unsigned short mFlags; unsigned short mModificationCount;
    Vec3 mTranslation; float mScale; float mRotation[9];
};
struct cSPBoundingBox { Vec3 mMin; Vec3 mMax; };

// --- callees / globals -----------------------------------------------------
void  translateTransform(void* out, void* a, const void* b);
void  cSPTransform_Assign(void* dst, const void* src);
int   FUN_00700c80(const void* a, const void* b, const float* p, float r, void* out);
int   FUN_0073e080(const void* a, const void* b, const void* xf, void* out);
int   FUN_0073e410(const void* a, const void* b, const void* xf, const void* p, void* o1, void* o2, void* x, void* y);
int   FUN_00744050(const void* a, const void* b, const void* xf, const void* box, void* out);
int   FUN_00743fb0(const void* p, float r, const void* box);
int   cModelInstance_IntersectsSphere(void* inst, const float* pos, const void* xf, bool b);
int   cModelInstance_PickLine(void* inst, const float* pos, float r, const void* xf, bool b);
void  Matrix3_Assign(void* dst, const void* src);
extern float g_f162eb0c, g_f162eb10, g_f162eb14, g_f162ec38, g_f1485720;
extern int g_appProps;

// Model-cull argument object (retail offsets used by these queries).
struct CMWModel {
    unsigned char pad0[0x04];
    uint32_t mFlags;         // +0x04
    unsigned char pad8[0x44 - 0x08];
    uint32_t mMaskA;         // +0x44
    uint32_t mMaskB;         // +0x48
    unsigned char pad4c[0x5d - 0x4c];
    unsigned char mC0;       // +0x5d
    unsigned char pad5e[0x6c - 0x5e];
    float mRadius;           // +0x6c
    float mBoxMinX;          // +0x70
    unsigned char pad74[0x7c - 0x74];
    float mBoxMaxX;          // +0x7c
    unsigned char pad80[0x94 - 0x80];
    void* mInst1;            // +0x94
    unsigned char pad98[0xa4 - 0x98];
    void* mInst2;            // +0xa4
    unsigned char pada8[0xdc - 0xa8];
    unsigned char mTransform[0x38]; // +0xdc
};
struct FilterArg {
    uint32_t a, b, c, d;
    int (__cdecl* cb)(void*);
    unsigned char e, f;
};

// @ 0x00749bd0 : SP::cModelWorld::FindModelsInFrustum
int FindModelsInFrustum(const void* frustumA, const void* frustumB, CMWModel* model,
                        void* out, FilterArg* arg)
{
    if (model == 0 || (int)model == 8) return 0;
    if (!(model->mFlags & 1)) return 0;
    if ((arg->a != 0 || arg->b != 0) &&
        ((model->mMaskB & arg->b) == 0 && (model->mMaskA & arg->a) == 0))
        return 0;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 0;
    if (arg->cb != 0 && !arg->cb(model))
        return 0;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;

    cSPTransform local;
    memset(&local, 0, sizeof(local));
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);
    cSPTransform_Assign(&local, model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }
    float pos[3];
    pos[0] = local.mTranslation.x;
    pos[1] = local.mTranslation.y;
    pos[2] = local.mTranslation.z;
    if (!FUN_00700c80(frustumA, frustumB, pos, model->mRadius * local.mScale, out))
        return 0;

    if ((b < 3 || model->mInst1 == 0) || *(int*)((char*)model->mInst1 + 0xcc) == 0) {
        if ((b < 2 || model->mInst2 == 0) || *(int*)((char*)model->mInst2 + 0xcc) == 0) {
            if (b == 0) return 1;
            if (model->mBoxMaxX <= model->mBoxMinX && model->mBoxMinX != model->mBoxMaxX)
                return 1;
            if (FUN_00744050(frustumA, frustumB, &local, &model->mBoxMinX, out) != 0)
                return 0;
            return 0;
        }
        char tmp[56];
        translateTransform(tmp, model->mTransform, &local);
        if (FUN_0073e080(frustumA, frustumB, tmp, out) != 0) return 0;
        return 0;
    }
    char tmp[56];
    translateTransform(tmp, model->mTransform, &local);
    if (FUN_0073e080(frustumA, frustumB, tmp, out) != 0) return 0;
    return 0;
}

// @ 0x00749e50 : SP::cModelWorld::PickAgainstModel
int PickAgainstModel(float* pos, float radius, CMWModel* model, FilterArg* arg)
{
    if (model == 0 || (int)model == 8) return 0;
    if (!(model->mFlags & 1)) return 0;
    if (!((arg->a == 0 && arg->b == 0) ||
          (model->mMaskB & arg->b) != 0 || (model->mMaskA & arg->a) != 0))
        return 0;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 0;
    if (arg->cb != 0 && !arg->cb(model))
        return 0;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;

    cSPTransform local;
    memset(&local, 0, sizeof(local));
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);
    cSPTransform_Assign(&local, model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }
    float reach = model->mRadius * local.mScale + radius;
    float dx = pos[0] - local.mTranslation.x;
    float dy = pos[1] - local.mTranslation.y;
    float dz = pos[2] - local.mTranslation.z;
    if (dx * dx + dy * dy + dz * dz >= reach * reach)
        return 0;
    if ((b < 3 || model->mInst1 == 0) || *(int*)((char*)model->mInst1 + 0xcc) == 0) {
        if (b != 0 &&
            (model->mBoxMinX < model->mBoxMaxX || model->mBoxMinX == model->mBoxMaxX) &&
            FUN_00743fb0(pos, radius, &model->mBoxMinX) == 0)
            return 0;
    } else {
        char tmp[56];
        translateTransform(tmp, model->mTransform, &local);
        if (cModelInstance_PickLine(model->mInst1, pos, radius, tmp, false) == 0) return 0;
    }
    return 1;
}

// @ 0x0074a070 : model sphere-box filter
int FUN_0074a070(float* pos, CMWModel* model, FilterArg* arg)
{
    if (model == 0 || (int)model == 8) return 0;
    if (!(model->mFlags & 1)) return 0;
    if (!((arg->a == 0 && arg->b == 0) ||
          (model->mMaskB & arg->b) != 0 || (model->mMaskA & arg->a) != 0))
        return 0;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 0;
    if (arg->cb != 0 && !arg->cb(model))
        return 0;
    unsigned char b = ((arg->f & 1) && ((model->mFlags >> 8) & 1)) ? model->mC0 : arg->e;

    cSPTransform local;
    memset(&local, 0, sizeof(local));
    local.mTranslation.x = g_f162eb0c;
    local.mTranslation.y = g_f162eb10;
    local.mTranslation.z = g_f162eb14;
    local.mScale = g_f1485720;
    Matrix3_Assign(local.mRotation, &g_f162ec38);
    cSPTransform_Assign(&local, model->mTransform);
    if (((model->mFlags >> 7) & 1) || (arg->f & 2)) {
        local.mModificationCount++;
        local.mScale = g_f1485720;
    }
    float reach = model->mRadius * local.mScale;
    float dx0 = local.mTranslation.x - pos[0];
    if (!(local.mTranslation.x < pos[0] || pos[3] < local.mTranslation.x)) dx0 = 0.0f;
    else dx0 = local.mTranslation.x - pos[3];
    float acc = dx0 * dx0;
    {
        float d = 0.0f;
        if (local.mTranslation.y < pos[1]) d = local.mTranslation.y - pos[1];
        else if (pos[4] < local.mTranslation.y) d = local.mTranslation.y - pos[4];
        acc += d * d;
    }
    {
        float d = 0.0f;
        if (local.mTranslation.z < pos[2]) d = local.mTranslation.z - pos[2];
        else if (pos[5] < local.mTranslation.z) d = local.mTranslation.z - pos[5];
        acc += d * d;
    }
    if (acc <= reach * reach) {
        if (b > 2 && model->mInst1 != 0 && *(int*)((char*)model->mInst1 + 0xcc) != 0) {
            char tmp[56];
            translateTransform(tmp, model->mTransform, &local);
            if (cModelInstance_IntersectsSphere(model->mInst1, pos, tmp, false) == 0) return 0;
        }
        return 1;
    }
    return 0;
}

// @ 0x00749370 : cModelWorld ray/frustum model query (huge; see partial.txt)
int* FUN_00749370(int self, float* a, float* b, float* c, float* d, float* e,
                  FilterArg* arg, void* out1, void* out2)
{
    unsigned char* base = (unsigned char*)self;
    int* best = 0;
    if (*(int*)(base + 0x13c) == *(int*)(base + 0x140) ||
        *(int*)(*(int*)(g_appProps + 0x3c) + 0x2c) < 2) {
        int* n = *(int**)(base + 0x19c);
        int* anchor = (int*)(base + 0x19c);
        if (n == anchor) return 0;
        do {
            CMWModel* m = (CMWModel*)n;
            if (m->mFlags & 1) {
                float* pos = c;
                float r = 0.0f;
                FUN_00700c80(a, b, pos, m->mRadius * 1.0f, out1);
                if (m->mInst1 && *(int*)((char*)m->mInst1 + 0xcc) != 0) {
                    char tmp[56];
                    translateTransform(tmp, m->mTransform, 0);
                    FUN_0073e410(a, b, tmp, out1, out2, 0, 0, 0);
                    best = n;
                }
            }
            n = (int*)n[0];
        } while (n != anchor);
    }
    (void)d; (void)e; (void)arg;
    return best;
}
