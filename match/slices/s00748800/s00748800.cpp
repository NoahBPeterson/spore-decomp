// Slice s00748800 (0x00748800..0x00748C30): anonymous-namespace model filters and a
// model-list query, /O2 /MD /Gy /EHsc /TP.
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
void  cSPBoundingBox_Transform(cSPBoundingBox* box, const void* xf);
int   FUN_00511140(void* p);
int   FUN_00490330(float* p);
int   ComposeTransforms(void* xf);
int   FUN_0073e080(float* a, int b, void* c, int d);
int   FUN_006ba870(int a);
int   cModelInstance_IntersectsSphere(void* inst, const float* pos, const void* xf, bool b);
void  Matrix3_Assign(void* dst, const void* src);
extern float g_f162eb0c, g_f162eb10, g_f162eb14, g_f162ec38, g_f1485720;
extern int g_appProps;

struct CullModel {
    unsigned char pad0[0x0c];
    uint32_t mFlags;         // +0x0c
    unsigned char pad10[0x4c - 0x10];
    uint32_t mMaskA;         // +0x4c
    uint32_t mMaskB;         // +0x50
    unsigned char pad54[0x65 - 0x54];
    unsigned char mC0;       // +0x65
    unsigned char pad66[0x74 - 0x66];
    float mRadius;           // +0x74
    float mBoxMinX;          // +0x78
    unsigned char pad7c[0x84 - 0x7c];
    float mBoxMaxX;          // +0x84
    unsigned char pad88[0x9c - 0x88];
    void* mInst1;            // +0x9c
    unsigned char pada0[0xac - 0xa0];
    void* mInst2;            // +0xac
    unsigned char padb0[0xe4 - 0xb0];
    unsigned char mTransform[0x38]; // +0xe4
};
struct SphereArg {
    uint32_t a, b, c, d;
    int (__cdecl* cb)(void*);
    unsigned char e, f;
};

// @ 0x00748800 : `anonymous namespace'::FilterModelSphere
int FilterModelSphere2(CullModel* model, float* pos, SphereArg* arg)
{
    if (!(model->mFlags & 1)) return 1;
    if (!((arg->a == 0 && arg->b == 0) ||
          (model->mMaskB & arg->b) != 0 || (model->mMaskA & arg->a) != 0))
        return 1;
    if ((model->mMaskB & arg->d) != 0 || (model->mMaskA & arg->c) != 0)
        return 1;
    if (arg->cb != 0 && !arg->cb((char*)model + 8))
        return 1;
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

    float dx0 = local.mTranslation.x - pos[0];
    if (local.mTranslation.x < pos[0] || pos[3] < local.mTranslation.x)
        dx0 = local.mTranslation.x - pos[3];
    else
        dx0 = 0.0f;
    float acc = dx0 * dx0;
    if (local.mTranslation.y < pos[1] || pos[4] < local.mTranslation.y) {
        float d = local.mTranslation.y - pos[4];
        if (!(local.mTranslation.y < pos[1])) d = local.mTranslation.y - pos[4];
        else d = local.mTranslation.y - pos[1];
        acc += d * d;
    }
    {
        float d = 0.0f;
        if (local.mTranslation.z < pos[2] || pos[5] < local.mTranslation.z)
            d = local.mTranslation.z - (pos[5] < local.mTranslation.z ? pos[5] : pos[2]);
        acc += d * d;
    }
    float reach = model->mRadius * local.mScale;
    if (reach * reach < acc) return 1;

    if (b > 2 && model->mInst1 != 0 && *(int*)((char*)model->mInst1 + 0xcc) != 0) {
        char tmp[56];
        translateTransform(tmp, model->mTransform, &local);
        return cModelInstance_IntersectsSphere(model->mInst1, pos, tmp, b == 3) == 0;
    }
    if (b > 1 && model->mInst2 != 0 && *(int*)((char*)model->mInst2 + 0xcc) != 0) {
        char tmp[56];
        translateTransform(tmp, model->mTransform, &local);
        return cModelInstance_IntersectsSphere(model->mInst2, pos, tmp, true) == 0;
    }
    if (b != 0 && model->mBoxMinX <= model->mBoxMaxX) {
        cSPBoundingBox box;
        FUN_00511140(&model->mBoxMinX);
        cSPBoundingBox_Transform(&box, model->mTransform);
        return FUN_00490330(pos) == 0;
    }
    return 0;
}

// @ 0x00748ad0 : model pick/distance helper
struct PickSrc { unsigned short f0, f1; float a, b, c; int d; float rot[9]; };
int FUN_00748ad0(float* a, int b, unsigned short* src, int param_4, int param_5,
                 int model, int idx, int param_8, float radius)
{
    PickSrc local;
    local.f0 = src[0];
    local.f1 = src[1];
    local.a = *(float*)(src + 2);
    local.b = *(float*)(src + 4);
    local.c = *(float*)(src + 6);
    local.d = *(int*)(src + 8);
    memcpy(local.rot, src + 10, sizeof(local.rot));
    ComposeTransforms((void*)(model + 0xe4));
    if (radius <= 0.0f) {
        if (FUN_0073e080(a, b, &local, param_8)) return 1;
    } else {
        local.f0 |= 4;
        local.f1++;
        local.a += -a[0];
        local.b += -a[1];
        local.c += -a[2];
        FUN_006ba870(param_5);
        void* inst = *(void**)(model + 0x9c + idx * 4);
        if (cModelInstance_IntersectsSphere(inst, (float*)param_4, &local, false)) return 1;
    }
    return 0;
}

// @ 0x00748c30 : cModelWorld model-list query (best model in range)
int* FUN_00748c30(int self, int param_2, int param_3, float* param_4, uint32_t* param_5)
{
    unsigned char* b = (unsigned char*)self;
    int* best = 0;
    if (*(int*)(b + 0x13c) == *(int*)(b + 0x140) ||
        *(int*)(*(int*)(g_appProps + 0x3c) + 0x2c) < 2) {
        int* n = *(int**)(b + 0x19c);
        int* anchor = (int*)(b + 0x19c);
        if (n == anchor) return 0;
        float bestDist = 1.0e38f;
        do {
            // build the query transform and evaluate the node's filter
            float local[64];
            memset(local, 0, sizeof(local));
            int r = FUN_00748ad0(param_4, param_3, (unsigned short*)n, 0, 0, (int)n, 0, 0, bestDist);
            if (r && *(float*)(n + 0x134) < bestDist) {
                bestDist = *(float*)(n + 0x134);
                best = n;
            }
            n = (int*)n[0];
        } while (n != anchor);
    }
    (void)param_2;
    (void)param_5;
    return best;
}
