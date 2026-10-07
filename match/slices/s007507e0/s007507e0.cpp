// slice s007507e0 -- SP::cModelWorld per-layer visibility pass (0x007507e0).
//
// The PDB pairing ("caller-scored") labels this SP::EditorUtils::cRegisterSkinModelJob::Stage2, but the
// code is a SP::cModelWorld method (thiscall, ret 0xc): for one draw set it
//   1. clears the visible-model list and the opaque / alpha cDrawModelInfo lists;
//   2. reads the camera transform and, if occlusion is enabled, turns every live occluder sphere into a
//      cone record (direction, distance, sin/cos of the half angle) in a 16-entry fixed_vector, sorted;
//   3. sets up the frustum culler from the camera (plus an optional property-driven tweak);
//   4. gathers candidate models (hierarchical-grid frustum query, or the whole model list);
//   5. for each candidate applies the draw-set group masks, frustum, horizon (planet) and occluder-cone
//      tests, updates its LOD, writes the model transform into the chosen LOD mesh and appends
//      {model, distance} to the opaque or alpha draw list.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast (scalar SSE float math with inline x87 fsqrt,
// as in the original; /fp:precise calls _CIsqrt instead; no /GS cookie, EH frame for the fixed_vector).
#include "types.h"
#include <math.h>

namespace SP {

struct Vec3 { float x, y, z; };

struct Matrix3 {
    float m[9];
    void Assign(const Matrix3& src);                    // 0x0041cb40
};

struct cSPTransform {                                   // 0x38 bytes
    uint16_t mFlags;                                    // +0x00
    uint16_t mFlags2;                                   // +0x02
    Vec3     mOffset;                                   // +0x04
    float    mScale;                                    // +0x10
    Matrix3  mRotation;                                 // +0x14
    cSPTransform& operator=(const cSPTransform& o);     // 0x00537dc0
    void Accumulate(const cSPTransform* other);         // 0x0040ccb0
};

// Draw mesh of one LOD (intrusive ref count).
struct cMWMesh {
    virtual void DeleteThis(int flags);                 // slot 0: scalar deleting destructor
    int mnRefCount;                                     // +0x04
    char pad08[0x70 - 8];
    cSPTransform mTransform;                            // +0x70
    char padA8[0xc8 - 0xa8];
    uint8_t mDrawFlags;                                 // +0xc8 (bit 0: alpha)

    void Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            DeleteThis(1);
        }
    }
};

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
};

struct cMWModelInternal {
    cMWModelInternal* mpNext;                           // +0x00 (model list hook)
    char pad04[0xc - 4];
    uint32_t mFlags;                                    // +0x0c
    cSPTransform mTransform;                            // +0x10
    char pad48[0x4c - 0x48];
    uint32_t mGroupMask[2];                             // +0x4c
    char pad54[0x60 - 0x54];
    float mAlpha;                                       // +0x60
    char pad64[0x74 - 0x64];
    float mBoundingRadius;                              // +0x74
    char pad78[0x8c - 0x78];
    float mHorizonRadius;                               // +0x8c
    float mLODDistance;                                 // +0x90
    char pad94[0x9c - 0x94];
    AutoRefCount<cMWMesh> mLODs[4];                     // +0x9c
    char padAC[0xb0 - 0xac];
    cMWMesh* mpLowLODMesh;                              // +0xb0
    char padB4[0xd4 - 0xb4];
    float* mpLODThresholds;                             // +0xd4
    char padD8[0xe4 - 0xd8];
    cSPTransform mExtraTransform;                       // +0xe4
    char pad11c[0x128 - 0x11c];
    uint8_t mLOD;                                       // +0x128
    uint8_t mNumLODs;                                   // +0x129
    char pad12a[0x130 - 0x12a];
    uint32_t mLastVisibleFrame;                         // +0x130
};

struct cDrawModelInfo {
    cMWModelInternal* mpModel;
    float mDistance;
};

struct DrawModelVector {                                // eastl::vector<cDrawModelInfo>
    cDrawModelInfo* mpBegin;
    cDrawModelInfo* mpEnd;
    cDrawModelInfo* mpCapacity;
    cDrawModelInfo* erase(cDrawModelInfo* first, cDrawModelInfo* last);       // 0x00d018d0
    void DoInsertValue(cDrawModelInfo* position, const cDrawModelInfo& v);    // 0x006ec390
    void push_back(const cDrawModelInfo& v)
    {
        if (mpEnd < mpCapacity) {
            cDrawModelInfo* p = mpEnd++;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};

extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);       // memcpy thunk

struct ModelPtrVector {                                 // eastl::vector<cMWModelInternal*>
    cMWModelInternal** mpBegin;
    cMWModelInternal** mpEnd;
    cMWModelInternal** mpCapacity;
    void resize(int n);                                                         // 0x00758ee0
    void DoInsertValue(cMWModelInternal** position, cMWModelInternal* const& v);  // 0x006ec4a0
    cMWModelInternal** erase(cMWModelInternal** first, cMWModelInternal** last)
    {
        FUN_011e0744(first, last, (unsigned)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(cMWModelInternal* const& v)
    {
        if (mpEnd < mpCapacity) {
            cMWModelInternal** p = mpEnd++;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};

struct cOccluderSlot {                                  // spstl::slot_vector entry (0x14 bytes)
    uint32_t mFlags;                                    // bit 31: free
    Vec3 mCenter;
    float mRadius;
};

// Occluder cone seen from the camera (0x18 bytes).
struct cOccluder {
    Vec3 mDir;
    float mDistance;    // distance from the camera times cos(half angle)
    float mSinAngle;
    float mCosAngle;
};

void EA_operator_delete_array(void* p);                 // 0x00f47380 (operator delete[])

struct OccluderFixedVector {                            // eastl::fixed_vector<cOccluder, 16>
    cOccluder* mpBegin;
    cOccluder* mpEnd;
    cOccluder* mpCapacity;
    uint32_t mAllocator;
    cOccluder* mpPoolBegin;
    uint32_t mPad;
    cOccluder mBuffer[16];

    OccluderFixedVector()
    {
        cOccluder* p = mBuffer;
        mpEnd = p;
        mpPoolBegin = p;
        mpBegin = p;
        mpCapacity = (cOccluder*)((char*)mBuffer + sizeof(mBuffer));
    }
    ~OccluderFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            EA_operator_delete_array(mpBegin);
    }
    void push_back(const cOccluder& v);                 // 0x0074cdd0
};

typedef bool(__cdecl* OccluderCompare)(const cOccluder&, const cOccluder&);
bool __cdecl OccluderLess(const cOccluder& a, const cOccluder& b);                       // 0x00743920
void __cdecl quick_sort(cOccluder* first, cOccluder* last, OccluderCompare compare);     // 0x0074f3a0
int __cdecl FUN_00745660(cOccluderSlot* first, cOccluderSlot* last, uint32_t frame);     // 0x00745660

struct cFrustumCull {
    void Setup(const void* cameraFrustum);              // 0x006ffe00
    void FUN_006ffa80(float f);                         // 0x006ffa80
    uint8_t TestSphere(const Vec3* center, float radius);   // 0x006ffbd0 (bit 0x40: outside)
};

struct cHierGrid {
    int FrustumQuery(cFrustumCull* cull, int maxCount, cMWModelInternal** out);   // 0x007026d0
};

struct cCamera {
    char pad00[0xc0];
    char mFrustum[1];                                   // +0xc0
    void GetTransform(cSPTransform* out);               // 0x007c40f0
};

struct Property {
    void* mpData;                                       // +0x00 (value in place for small types)
    char pad04[0x10 - 4];
    uint8_t mFlags;                                     // +0x10 (0x30: value behind mpData)
    char pad11;
    uint16_t mType;                                     // +0x12 (0xd: float)
    float GetValueFloat() const { return *(const float*)((mFlags & 0x30) ? mpData : (const void*)this); }
};

struct cModelTuning {
    char pad00[0x2c];
    int mCullLevel;                                     // +0x2c
    char pad30[0x9c - 0x30];
    float mLODScale;                                    // +0x9c
    char padA0[0xe0 - 0xa0];
    float mAlphaThreshold;                              // +0xe0
};

struct cAppProperties {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
    char pad04[0x3c - 4];
    cModelTuning* mpTuning;                             // +0x3c
};

extern cAppProperties* g_AppProperties;                 // 0x015fd918
extern uint32_t g_FrameCounter;                         // 0x016f8cf8
extern uint32_t g_AlphaFadeFlags;                       // 0x01537bf0
extern Vec3 g_ZeroVector;                               // 0x0162eb0c
extern Matrix3 g_IdentityMatrix;                        // 0x0162ec4c

struct cDrawSetInfo {                                   // 0x20 bytes
    uint32_t mIncludeMask[2];
    uint32_t mExcludeMask[2];
    char pad10[0x10];
};

class cModelWorld {
public:
    char pad000[0x28];
    cFrustumCull mFrustumCuller;                        // +0x28
    char pad029[0x118 - 0x29];
    cHierGrid mHierGrid;                                // +0x118
    char pad119[0x138 - 0x119];
    int mGridModelCount;                                // +0x138
    void* mGridBegin;                                   // +0x13c
    void* mGridEnd;                                     // +0x140
    char pad144[0x19c - 0x144];
    cMWModelInternal* mModelListHead;                   // +0x19c (intrusive list anchor)
    char pad1a0[0x1bc - 0x1a0];
    cDrawSetInfo mDrawSets[(0x2b4 - 0x1bc) / 0x20];     // +0x1bc
    char pad2bc_[0x2b4 - 0x1bc - sizeof(cDrawSetInfo) * ((0x2b4 - 0x1bc) / 0x20)];
    float mHorizonCullFactor;                           // +0x2b4
    float mLODScale;                                    // +0x2b8
    cOccluderSlot* mOccludersBegin;                     // +0x2bc (spstl::slot_vector)
    cOccluderSlot* mOccludersEnd;                       // +0x2c0
    char pad2c4[0x2d0 - 0x2c4];
    uint32_t mOccludersFirstUsed;                       // +0x2d0
    char pad2d4[0x2d8 - 0x2d4];
    ModelPtrVector mDrawList;                           // +0x2d8
    char pad2e4[0x2ec - 0x2e4];
    DrawModelVector mOpaqueDrawList;                    // +0x2ec
    char pad2f8[0x300 - 0x2f8];
    DrawModelVector mAlphaDrawList;                     // +0x300
    char pad30c[0x8a0 - 0x30c];
    int mNumDrawModels;                                 // +0x8a0
    char pad8a4[0x8ac - 0x8a4];
    int mNumMeshesDrawn;                                // +0x8ac

    void UpdateVisibility(uint32_t flags, cCamera* camera, int drawSet);
};

// @ 0x007507e0
void cModelWorld::UpdateVisibility(uint32_t flags, cCamera* camera, int drawSet)
{
    cAppProperties* props = g_AppProperties;
    mDrawList.clear();
    mOpaqueDrawList.erase(mOpaqueDrawList.mpBegin, mOpaqueDrawList.mpEnd);
    mAlphaDrawList.erase(mAlphaDrawList.mpBegin, mAlphaDrawList.mpEnd);

    cSPTransform camXf;
    camXf.mFlags = 0;
    camXf.mFlags2 = 0;
    camXf.mOffset = g_ZeroVector;
    camXf.mScale = 1.0f;
    camXf.mRotation.Assign(g_IdentityMatrix);
    camera->GetTransform(&camXf);

    bool updateLOD = (flags >> 9) & 1;
    bool useOccluders = (flags >> 10) & 1;
    bool forceOpaque = (flags >> 16) & 1;
    Vec3 camPos = camXf.mOffset;
    int cullLevel = props->mpTuning->mCullLevel;
    float lodScale = mLODScale * props->mpTuning->mLODScale;
    uint32_t frame = g_FrameCounter;

    OccluderFixedVector occluders;
    if (cullLevel > 2 && useOccluders) {
        cOccluderSlot* first = mOccludersFirstUsed < 0x3fffffff ? mOccludersBegin + mOccludersFirstUsed
                                                                 : mOccludersEnd;
        int n = FUN_00745660(first, mOccludersEnd, frame);
        for (int i = 0; i < n; i++) {
            if ((uint32_t)i < (uint32_t)(mOccludersEnd - mOccludersBegin) &&
                !((mOccludersBegin[i].mFlags >> 31) & 1)) {
                const cOccluderSlot& e = mOccludersBegin[i];
                float dx = e.mCenter.x - camPos.x;
                float dy = e.mCenter.y - camPos.y;
                float dz = e.mCenter.z - camPos.z;
                float dist = sqrtf((dx * dx + dz * dz) + dy * dy);
                cOccluder occ;
                if (dist > e.mRadius) {
                    float inv = 1.0f / dist;
                    float s = inv * e.mRadius;
                    occ.mSinAngle = s;
                    occ.mCosAngle = sqrtf(1.0f - s * s);
                    occ.mDir.x = inv * dx;
                    occ.mDir.y = inv * dy;
                    occ.mDir.z = inv * dz;
                    if (!(s > 0.1f))
                        continue;
                } else {
                    occ.mSinAngle = 1.0f;
                    float inv = 1.0f / (dist + 1e-06f);
                    occ.mCosAngle = 0.0f;
                    occ.mDir.x = inv * dx;
                    occ.mDir.y = inv * dy;
                    occ.mDir.z = inv * dz;
                }
                float cx = camPos.x - e.mCenter.x;
                float cy = camPos.y - e.mCenter.y;
                float cz = camPos.z - e.mCenter.z;
                occ.mDistance = sqrtf((cx * cx + cz * cz) + cy * cy) * occ.mCosAngle;
                occluders.push_back(occ);
            }
        }
        quick_sort(occluders.mpBegin, occluders.mpEnd, OccluderLess);
    }

    cFrustumCull* cull = &mFrustumCuller;
    cull->Setup(camera->mFrustum);
    Property* prop;
    if (props->GetProperty(0x13d7382, prop) && prop->mType == 0xd)
        cull->FUN_006ffa80(prop->GetValueFloat());

    mNumDrawModels = 0;
    int count;
    if (mGridBegin != mGridEnd && cullLevel > 1) {
        mDrawList.resize(mGridModelCount);
        count = mHierGrid.FrustumQuery(cull, (int)(mDrawList.mpEnd - mDrawList.mpBegin), mDrawList.mpBegin);
    } else {
        for (cMWModelInternal* node = mModelListHead; node != (cMWModelInternal*)&mModelListHead;
             node = node->mpNext)
            mDrawList.push_back(node);
        count = (int)(mDrawList.mpEnd - mDrawList.mpBegin);
    }
    mNumDrawModels = count;
    mNumMeshesDrawn = 0;

    for (int i = 0; i < mNumDrawModels; i++) {
        cMWModelInternal* model = mDrawList.mpBegin[i];

        bool visible;
        if (!(model->mFlags & 1)) {
            visible = false;
        } else {
            const cDrawSetInfo& ds = mDrawSets[drawSet];
            if ((ds.mIncludeMask[1] | ds.mIncludeMask[0]) != 0 &&
                ((model->mGroupMask[0] & ds.mIncludeMask[0]) | (model->mGroupMask[1] & ds.mIncludeMask[1])) == 0)
                visible = false;
            else if ((model->mGroupMask[0] & ds.mExcludeMask[0]) != 0 ||
                     (model->mGroupMask[1] & ds.mExcludeMask[1]) != 0)
                visible = false;
            else
                visible = true;
        }

        Vec3 pos = model->mTransform.mOffset;
        float radius = model->mTransform.mScale * model->mBoundingRadius;
        if (cullLevel > 0) {
            if (visible && !(cull->TestSphere(&pos, radius) & 0x40))
                visible = true;
            else
                visible = false;
        }

        float dx = camPos.x - pos.x;
        float dy = camPos.y - pos.y;
        float dz = camPos.z - pos.z;
        float dist = sqrtf((dz * dz + dy * dy) + dx * dx);

        if (visible) {
            float horizon = mHorizonCullFactor;
            if (horizon != 0.0f && !((model->mFlags >> 4) & 1)) {
                // Horizon test: is the model hidden behind the planet?
                float p, q;
                if ((model->mFlags >> 5) & 1) {
                    float r = model->mHorizonRadius * model->mTransform.mScale;
                    const float* axis = &model->mTransform.mRotation.m[6];
                    p = (dz * axis[2] + dy * axis[1]) + dx * axis[0];
                    q = (dist * r) / sqrtf(r * r + horizon * horizon);
                } else {
                    float plen = sqrtf((pos.z * pos.z + pos.y * pos.y) + pos.x * pos.x);
                    float clen = sqrtf((camPos.z * camPos.z + camPos.y * camPos.y) + camPos.x * camPos.x);
                    float r2 = radius + radius;
                    if (clen < plen) {
                        float k = plen / clen;
                        float tz = camPos.z * k - pos.z;
                        float ty = camPos.y * k - pos.y;
                        float tx = camPos.x * k - pos.x;
                        p = (pos.z * tz + pos.y * ty) + pos.x * tx;
                    } else {
                        p = (pos.z * dz + pos.y * dy) + pos.x * dx;
                    }
                    q = ((r2 * plen) * dist) / sqrtf(r2 * r2 + horizon * horizon);
                }
                if (p < -q)
                    visible = false;
                else
                    visible = true;
            }

            if (visible && occluders.mpBegin != occluders.mpEnd) {
                // Occluder cones, sorted by decreasing angular size.
                float ratio = model->mBoundingRadius / dist;
                int n = (int)(occluders.mpEnd - occluders.mpBegin);
                for (int j = 0; j < n; j++) {
                    const cOccluder& o = occluders.mpBegin[j];
                    if (!(o.mSinAngle > ratio))
                        break;
                    if (dist > o.mDistance) {
                        float vy = pos.y - camPos.y;
                        float vx = pos.x - camPos.x;
                        float vz = pos.z - camPos.z;
                        float proj = (o.mDir.z * vz + o.mDir.y * vy) + o.mDir.x * vx;
                        float t = proj * o.mSinAngle - radius;
                        if (!(0.0f > t)) {
                            float perp = (((vx * vx + vz * vz) + vy * vy) - proj * proj) * o.mCosAngle * o.mCosAngle;
                            if (t * t >= perp) {
                                visible = false;
                                break;
                            }
                        }
                    }
                }
            }
        }

        float lodDist = dist * lodScale;
        if (updateLOD)
            model->mLODDistance = lodDist;
        if (!visible)
            continue;

        if (updateLOD) {
            float* thresholds = model->mpLODThresholds;
            model->mLastVisibleFrame = frame;
            if (thresholds) {
                float d = lodDist / model->mTransform.mScale;
                while (model->mLOD > 0 && thresholds[model->mLOD - 1] > d)
                    model->mLOD--;
                while (model->mLOD < model->mNumLODs && d > thresholds[model->mLOD])
                    model->mLOD++;
            }
        }

        cMWMesh* mesh = (model->mLOD < 4 ? model->mLODs[model->mLOD] : AutoRefCount<cMWMesh>()).get();
        if (model->mLOD == 0 && ((model->mFlags >> 13) & 1) && model->mpLowLODMesh)
            mesh = model->mpLowLODMesh;
        if (!mesh)
            continue;

        if (model->mExtraTransform.mScale != 1.0f || (model->mExtraTransform.mFlags & 6)) {
            cSPTransform xf = model->mTransform;
            xf.Accumulate(&model->mExtraTransform);
            mesh->mTransform = xf;
        } else {
            mesh->mTransform = model->mTransform;
        }

        cDrawModelInfo info;
        info.mpModel = model;
        info.mDistance = dist;
        if (forceOpaque) {
            mOpaqueDrawList.push_back(info);
        } else if ((model->mFlags & g_AlphaFadeFlags) && 1.0f > model->mAlpha) {
            if (model->mAlpha > props->mpTuning->mAlphaThreshold)
                mAlphaDrawList.push_back(info);
        } else if (!(mesh->mDrawFlags & 1) && !((model->mFlags >> 12) & 1)) {
            mOpaqueDrawList.push_back(info);
        } else {
            mAlphaDrawList.push_back(info);
        }
    }
}

}  // namespace SP
