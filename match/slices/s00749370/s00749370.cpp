// Slice s00749370 (0x00749370..0x0074A070): SP::cModelWorld frustum/pick queries,
// /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <new>
#include <string.h>
#include <float.h>

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
extern float g_f162eb0c;   // 0x0162eb0c
extern float g_f162eb10;   // 0x0162eb10
extern float g_f162eb14;   // 0x0162eb14
extern float g_f162ec38;   // 0x0162ec38
extern float g_f1485720;   // 0x01485720
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

// @ 0x00749370 : SP::cModelWorld::FindClosestModelHit (thiscall, ret 0x20)
// Finds the nearest model hit by the segment a->b; returns the model (node + 8) or 0.
struct Matrix3 {
    float m[9];
    Matrix3(const Matrix3& src);                                  // 0x0041cb40 (thiscall, ret 4)
};
extern const Matrix3 kIdentityRot;                                // 0x0162ec4c
struct ZeroVec3 : Vec3 {
    ZeroVec3() { x = g_f162eb0c; y = g_f162eb10; z = g_f162eb14; }
};
struct Xf {                                                       // SP::cSPTransform (0x38 bytes)
    uint16_t mFlags;
    uint16_t mModCount;
    ZeroVec3 mTranslation;
    float    mScale;
    Matrix3  mRotation;
    Xf() : mFlags(0), mModCount(0), mScale(g_f1485720), mRotation(kIdentityRot) {}
    Xf& operator=(const Xf& rhs);                                 // 0x00537dc0 (thiscall, ret 4)
};

struct CMWInstance {
    char pad[0xcc];
    void* mpField_cc;                                             // +0xcc
    bool Trace(const float* a, const float* b, const Xf* xf, float* t,
               float* point, float* dir, int* out1, int* out2);  // 0x0073e410 (thiscall, ret 0x20)
};
#pragma pack(push, 4)
struct FilterArg64 {
    uint64_t   mInclude;     // +0x00
    uint64_t   mExclude;     // +0x08
    bool (__cdecl* mCallback)(void*);   // +0x10
    uint8_t    mLevel;       // +0x14
    uint8_t    mFlags;       // +0x15
};
struct CMWNode {
    CMWNode*   mpNext;       // +0x00
    uint8_t    pad04[8];
    uint32_t   mFlags;       // +0x0c
    Xf         mWorld;       // +0x10
    uint8_t    pad48[4];
    uint64_t   mMask;        // +0x4c
    uint8_t    pad54[0x11];
    uint8_t    mLevel;       // +0x65
    uint8_t    pad66[0xe];
    float      mRadius;      // +0x74
    float      mBoxMinX;     // +0x78
    uint8_t    pad7c[8];
    float      mBoxMaxX;     // +0x84
    uint8_t    pad88[0x14];
    CMWInstance* mInst1;     // +0x9c
    uint8_t    pada0[0xc];
    CMWInstance* mInst2;     // +0xac
    uint8_t    padb0[0x34];
    Xf         mXform2;      // +0xe4
};
#pragma pack(pop)
struct SpatialIndex {
    int Query(const float* a, const float* b, float r, int maxCount, CMWNode** out);   // 0x00702860 (thiscall, ret 0x14)
};
struct AppPropsInner { uint8_t pad[0x2c]; int mDetail; };
struct AppPropsOuter { uint8_t pad[0x3c]; AppPropsInner* mpInner; };
extern AppPropsOuter* g_pAppProps;                                // 0x015fd918
void* __cdecl translateXform(void* out, const Xf* a, const Xf* b);   // 0x006271a0
bool  __cdecl SegmentSphere(const float* a, const float* b, const float* center, float radius, float* t);   // 0x00700c80
bool  __cdecl SegmentBox(const float* a, const float* b, const Xf* xf, const float* box, float* t);          // 0x00744050

struct cModelWorld {
    uint8_t pad000[0x118];
    SpatialIndex mIndex;     // +0x118
    uint8_t pad11c[0x20];
    int     mField13c;       // +0x13c
    int     mField140;       // +0x140
    uint8_t pad144[0x58];
    CMWNode* mListHead;      // +0x19c (circular list anchor)
    CMWNode* FindClosestModelHit(const float* a, const float* b, float* outT, float* outPoint,
                                 float* outNormal, FilterArg64* arg, int* out1, int* out2);
};

struct HitState {
    float    bestT;
    CMWNode* best;
    int      bestOut1;
    int      bestOut2;
    float    point[3];
    float    dir[3];
};

inline unsigned TestBit(uint32_t v, int bit) { return (v >> bit) & 1; }

__forceinline void ConsiderNode(float& bestT, CMWNode*& best, int& bestOut1, int& bestOut2, float* bestPoint, float* bestDir, Xf& local, CMWNode* n, const float* a, const float* b, const FilterArg64* arg,
                                int* out1, int* out2)
{
    if (!(n->mFlags & 1)) return;
    if (arg->mInclude != 0 && (n->mMask & arg->mInclude) == 0)
        return;
    if ((n->mMask & arg->mExclude) != 0)
        return;
    if (arg->mCallback != 0 && !arg->mCallback((char*)n + 8))
        return;
    unsigned level;
    if ((arg->mFlags & 1) && TestBit(n->mFlags, 8))
        level = n->mLevel;
    else
        level = arg->mLevel;

    local = n->mWorld;
    if (TestBit(n->mFlags, 7) || (arg->mFlags & 2)) {
        local.mModCount++;
        local.mScale = g_f1485720;
    }
    Vec3 pos = local.mTranslation;
    float hitT;
    if (!SegmentSphere(a, b, &pos.x, n->mRadius * local.mScale, &hitT))
        return;

    float point[3], dir[3];
    char tmp[sizeof(Xf)];
    if (level >= 3 && n->mInst1 && n->mInst1->mpField_cc) {
        translateXform(tmp, &n->mXform2, &local);
        if (!n->mInst1->Trace(a, b, (const Xf*)tmp, &hitT, point, dir, out1, out2))
            return;
    } else if (level >= 2 && n->mInst2 && n->mInst2->mpField_cc) {
        translateXform(tmp, &n->mXform2, &local);
        if (!n->mInst2->Trace(a, b, (const Xf*)tmp, &hitT, point, dir, out1, out2))
            return;
    } else {
        if (level >= 1 && !(n->mBoxMinX > n->mBoxMaxX)) {
            if (!SegmentBox(a, b, &local, &n->mBoxMinX, &hitT))
                return;
        }
        dir[0] = b[0] - a[0];
        dir[1] = b[1] - a[1];
        dir[2] = b[2] - a[2];
        point[0] = a[0] + dir[0] * hitT;
        point[1] = a[1] + dir[1] * hitT;
        point[2] = a[2] + dir[2] * hitT;
    }

    if (bestT > hitT) {
        bestPoint[0] = point[0]; bestPoint[1] = point[1]; bestPoint[2] = point[2];
        bestDir[0] = dir[0]; bestDir[1] = dir[1]; bestDir[2] = dir[2];
        if (out1) bestOut1 = *out1;
        bestT = hitT;
        best = n;
        if (out2) bestOut2 = *out2;
    }
}

// @ 0x00749370
CMWNode* cModelWorld::FindClosestModelHit(const float* a, const float* b, float* outT, float* outPoint,
                                          float* outNormal, FilterArg64* arg, int* out1, int* out2)
{
    float bestT = FLT_MAX;
    CMWNode* best = 0;
    int bestOut1 = -1;
    int bestOut2 = -1;
    float bestPoint[3];
    float bestDir[3];
    Xf local;

    if (mField13c != mField140 && g_pAppProps->mpInner->mDetail > 1) {
        CMWNode* results[0x400];
        int count = mIndex.Query(a, b, 0.0f, 0x400, results);
        if (count <= 0)
            return 0;
        for (int i = 0; i < count; ++i)
            ConsiderNode(bestT, best, bestOut1, bestOut2, bestPoint, bestDir, local, results[i], a, b, arg, out1, out2);
    } else {
        CMWNode* anchor = (CMWNode*)&mListHead;
        CMWNode* n = mListHead;
        if (n == anchor)
            return 0;
        do {
            ConsiderNode(bestT, best, bestOut1, bestOut2, bestPoint, bestDir, local, n, a, b, arg, out1, out2);
            n = n->mpNext;
        } while (n != anchor);
    }

    if (!best)
        return 0;
    if (outT) *outT = bestT;
    if (outPoint) {
        outPoint[0] = bestPoint[0]; outPoint[1] = bestPoint[1]; outPoint[2] = bestPoint[2];
    }
    if (outNormal) {
        outNormal[0] = bestDir[0]; outNormal[1] = bestDir[1]; outNormal[2] = bestDir[2];
    }
    if (out1) *out1 = bestOut1;
    if (out2) *out2 = bestOut2;
    return (CMWNode*)((char*)best + 8);
}
