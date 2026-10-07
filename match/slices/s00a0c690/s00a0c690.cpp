// Slice s00a0c690 -- SP::cSPCreatureAnimWorld::Update(float dt, cViewer* viewer)
// (PDB candidate name, caller-scored): reads the animation tuning properties, frustum-culls every
// animating creature and measures its projected size, sorts the creatures, drops trailing null
// entries, then pushes each creature's transform/target/state into its creature_instance_data and
// ticks its blender.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the AutoRefCount temporary gets no EH frame).
#include "types.h"

#define VPAD(n) virtual void vpad##n()

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

// ------------------------------------------------------------------ math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

struct Quaternion {
    float x, y, z, w;
    Quaternion& operator=(const Quaternion& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};

// ------------------------------------------------------------------ App::Property
extern const bool     kDefaultBoolValue;        // 015d115d
extern const int      kDefaultInt32Value;       // 015d1160
extern const uint32_t kDefaultUInt32Value;      // 015d1164
extern const float    kDefaultFloatValue;       // 015d1168
extern const float    kAnimDefaultFloatValue;   // 015d9c6c (this module's own copy)
extern const bool     kAnimDefaultBoolValue;    // 015d9c70

struct Property {
    void*    mpData;      // +0x00 (external data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;     // +0x10 (0x30 = external data)
    uint16_t mnType;      // +0x12

    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    const bool* GetValueBool(const bool* def)
    {
        if (mnType == 1 || mnType == 0x10)
            return (const bool*)GetValuePtr();
        return def;
    }
    const int* GetValueInt32()
    {
        if (mnType == 9 || mnType == 0x10)
            return (const int*)GetValuePtr();
        return &kDefaultInt32Value;
    }
    const uint32_t* GetValueUInt32()
    {
        if (mnType == 10 || mnType == 0x10)
            return (const uint32_t*)GetValuePtr();
        return &kDefaultUInt32Value;
    }
    const float* GetValueFloat(const float* def)
    {
        if (mnType == 13 || mnType == 0x10)
            return (const float*)GetValuePtr();
        return def;
    }
};

struct cPropertyList {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    virtual Property* GetProperty(uint32_t id);                         // +0x28
};

// ------------------------------------------------------------------ viewer / frustum
struct cViewer {
    uint32_t pad[0xc0 / 4];
    uint32_t mViewProjection[0x10];                                     // +0xc0
    void GetCameraLocationInfo(Vector3* pos, int, int, Vector3* dir);   // 007c3d30
    void ProjectToScreen(Vector3* out, const Vector3* in);              // 007c4180
};

struct cRenderManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11);
    virtual cViewer* GetViewer(int index);                              // +0x30
};
cRenderManager* RenderManager();                                        // 0067dd50

struct cApp {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20); VPAD(21);
    virtual cViewer* GetViewer();                                       // +0x58
};
cApp* App();                                                            // 0067dd10

struct Frustum {
    uint32_t mData[0xf0 / 4];
    void Set(const uint32_t* viewProjection);                           // 006ffe00
    uint32_t Test(const Vector3* center, float radius);                 // 006ffbd0
};

// ------------------------------------------------------------------ creature anim data
struct creature_static_bounds {
    uint32_t pad[0x358 / 4];
    Vector3 mBoundsOrigin;                                              // +0x358
    Vector3 mBoundsSize;                                                // +0x364
    float   mBoundsRadius;                                              // +0x370
};

struct creature_mesh_instance_data {
    void SetStateInWorld(bool a, bool b, bool c);                       // 009c6440
};

struct creature_instance_data;

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& o)
    {
        T* const pNew = o.mpObject;
        T* const pOld = mpObject;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            mpObject = pNew;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
};

struct creature_instance_data {
    creature_static_bounds* mpStatic;                                   // +0x00
    uint32_t pad04[2];
    uint8_t  mbReady;                                                   // +0x0c
    uint32_t mSkippedUpdates;                                           // +0x10
    uint32_t pad14;
    Vector3  mPosition;                                                 // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    Quaternion mOrientation;                                            // +0x3c
    uint32_t pad4c[(0x6c - 0x4c) / 4];
    float    mScale;                                                    // +0x6c
    uint32_t pad70[(0xd8 - 0x70) / 4];
    float    mAngularSpeed;                                             // +0xd8
    Vector3  mVelocity;                                                 // +0xdc
    uint32_t pade8[(0x270 - 0xe8) / 4];
    uint8_t  mbFlag270;                                                 // +0x270
    uint8_t  pad271[3];
    int      mTargetMode;                                               // +0x274
    Vector3  mTargetPosition;                                           // +0x278
    Quaternion mTargetOrientation;                                      // +0x284
    AutoRefCount<creature_instance_data> mTarget;                       // +0x294
    uint32_t mTargetContextMode;                                        // +0x298
    uint32_t mTargetContextValue;                                       // +0x29c
    uint32_t m2a0;                                                      // +0x2a0
    uint32_t m2a4;                                                      // +0x2a4
    uint32_t mRestIdle;                                                 // +0x2a8
    uint32_t mMoveIdle;                                                 // +0x2ac
    void*    mpDataEvents;                                              // +0x2b0
    uint32_t mDataEventStride;                                          // +0x2b4
    void*    mpTargetData;                                              // +0x2b8
    uint32_t mTargetDataStride;                                         // +0x2bc
    creature_mesh_instance_data* mpMesh;                                // +0x2c0
    Vector3  mColor;                                                    // +0x2c4
    uint8_t  pad2d0[6];
    uint8_t  mbFlag2d6;                                                 // +0x2d6
    uint32_t pad2d8[(0x2e4 - 0x2d8) / 4];
    uint8_t* mpAnimsBegin;                                              // +0x2e4 (700-byte elements)
    uint8_t* mpAnimsEnd;                                                // +0x2e8

    void AddRef();                                                      // 00a17060
    void Release();                                                     // 009c4cc0
};

bool IsValidTargetPosition(const Vector3* pos);                         // 0059ab70

struct anim_anim_size { uint8_t data[700]; };

// The instance accepts its target only while the target mode is still satisfiable.
__forceinline bool HasValidTarget(creature_instance_data* inst)
{
    switch (inst->mTargetMode) {
    case 0:
    case 1:
        return IsValidTargetPosition(&inst->mTargetPosition);
    case 2:
        switch (inst->mTargetContextMode & 0x100003) {
        case 0:
        case 1:
            return inst->mTarget.mpObject && inst->mTarget.mpObject->mbReady;
        case 3:
            return inst->mTarget.mpObject && inst->mTarget.mpObject->mbReady &&
                   inst->mTargetContextValue <
                       (uint32_t)((anim_anim_size*)inst->mTarget.mpObject->mpAnimsEnd -
                                  (anim_anim_size*)inst->mTarget.mpObject->mpAnimsBegin);
        }
        break;
    }
    return false;
}

struct queued_blender {
    void Update(float dt, bool lowLOD, bool noLOD, bool paused);       // 00a01f40
};

struct cModel;

struct cAnimatingCreature {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20);
    virtual void UpdateLOD(int);                                        // +0x54
    VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26);
    virtual void PrepareUpdate();                                       // +0x6c

    Vector3  mPosition;                                                 // +0x04
    Quaternion mOrientation;                                            // +0x10
    uint32_t pad20[(0x3c - 0x20) / 4];
    float    mScale;                                                    // +0x3c
    float    mAngularSpeed;                                             // +0x40
    Vector3  mVelocity;                                                 // +0x44
    int      mLODCount;                                                 // +0x50
    int      mLODForced;                                                // +0x54
    uint32_t pad58;
    bool     mbInFrustum;                                               // +0x5c
    uint8_t  pad5d[3];
    float    mScreenSize;                                               // +0x60
    bool     mbDoUpdate;                                                // +0x64
    uint8_t  pad65[3];
    uint32_t pad68[(0x74 - 0x68) / 4];
    Vector3  mColor;                                                    // +0x74
    uint32_t pad80;
    bool     mbHasColor;                                                // +0x84
    uint8_t  pad85[3];
    uint32_t pad88;
    uint32_t mDataEvents[(0x14c - 0x8c) / 4];                           // +0x8c
    uint32_t mTargetData[1];                                            // +0x14c
    uint8_t  mbFlag150;                                                 // +0x150
    uint8_t  mbFlag151;                                                 // +0x151
    uint8_t  pad152[2];
    int      mTargetModeRequest;                                        // +0x154
    int      mTargetContextModeRequest;                                 // +0x158
    cAnimatingCreature* mpTargetCreature;                               // +0x15c
    uint32_t mTargetContextValue;                                       // +0x160
    Vector3  mTargetPosition;                                           // +0x164
    uint32_t mRestIdle;                                                 // +0x170
    uint32_t mMoveIdle;                                                 // +0x174
    uint32_t pad178;
    AutoRefCount<creature_instance_data> mpInstance;                    // +0x17c
    cModel*  mpModel;                                                   // +0x180
    queued_blender* mpBlender;                                          // +0x184
    uint32_t pad188[(0x194 - 0x188) / 4];
    uint32_t mIndex;                                                    // +0x194

    void SetRestIdleAnimHandle();                                       // 00a02c40
};

// ------------------------------------------------------------------ world
struct IModelWorld {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20); VPAD(21); VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29);
    VPAD(30); VPAD(31); VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38); VPAD(39);
    VPAD(40);
    virtual void SetModelGroup(cModel* model, uint32_t group, int index);   // +0xa4
    virtual uint32_t GetModelGroup(cModel* model, int index);               // +0xa8
};

struct cSPCreatureAnimManager {
    uint32_t pad[0x50 / 4];
    cPropertyList* mpProperties;                                        // +0x50
    uint32_t pad54[(0x84 - 0x54) / 4];
    uint32_t mHiddenGroup;                                              // +0x84
};

struct ICoreAllocator;
ICoreAllocator* GetDefaultAllocator();                                  // 00921240

// Orders creatures by projected screen size (comparator carries the LOD-1 threshold).
struct CreatureSizeCompare {
    float mThreshold;
    CreatureSizeCompare(float t) : mThreshold(t) {}
};
void StableSortCreatures(cAnimatingCreature** first, cAnimatingCreature** last,
                         ICoreAllocator& allocator, CreatureSizeCompare compare);   // 00a0a4b0

// eastl::stable_sort(first, last, compare): forwards to the allocator overload.
template <class Compare>
inline void stable_sort(cAnimatingCreature** first, cAnimatingCreature** last, Compare compare)
{
    StableSortCreatures(first, last, *GetDefaultAllocator(), compare);
}

struct CreatureVector {     // eastl::vector<cAnimatingCreature*, sp_vector_allocator>
    typedef cAnimatingCreature* value_type;
    cAnimatingCreature** mpBegin;
    cAnimatingCreature** mpEnd;
    cAnimatingCreature** mpCapacity;
    uint32_t mAllocator;

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void DoInsertValues(cAnimatingCreature** position, uint32_t n, cAnimatingCreature* const& value);  // 00999dd0
    void erase(cAnimatingCreature** first, cAnimatingCreature** last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
    }
    void resize(uint32_t n)
    {
        if (n > (uint32_t)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value_type());
        else
            erase(mpBegin + n, mpEnd);
    }
};

extern int      gAnimFlagB04;       // 01550b04
extern int      gAnimIntB6C;        // 01550b6c
extern float    gAnimFloatB74;      // 01550b74
extern float    gAnimFloatB78;      // 01550b78
extern uint32_t gAnimUIntB7C;       // 01550b7c
extern uint32_t gAnimUIntB80;       // 01550b80

class cSPCreatureAnimWorld {
public:
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15);
    virtual void SetCreatureLOD(cAnimatingCreature* creature, int lod, int flags);     // +0x40
    VPAD(17);
    virtual void SetMaxCreatureByLOD(int lod, int count);                   // +0x48
    VPAD(19); VPAD(20);
    virtual bool IsPaused();                                                // +0x54

    void Update(float dt, cViewer* viewer);

    uint32_t pad04[(0x1c - 4) / 4];
    cSPCreatureAnimManager* mpManager;                                  // +0x1c
    uint32_t pad20;
    CreatureVector mCreatures;                                          // +0x24
    uint32_t pad34[(0x44 - 0x34) / 4];
    IModelWorld* mpModelWorld;                                          // +0x44
    uint32_t pad48[(0x5c - 0x48) / 4];
    int mCurrentCreatureByLOD[3];                                       // +0x5c
};

// ------------------------------------------------------------------ the function
// @ 0x00a0c690
void cSPCreatureAnimWorld::Update(float dt, cViewer* viewer)
{
    if (mCreatures.mpBegin == mCreatures.mpEnd)
        return;

    dt *= *mpManager->mpProperties->GetProperty(0xf29f5604)->GetValueFloat(&kDefaultFloatValue);
    gAnimFlagB04 = *mpManager->mpProperties->GetProperty(0xf113323d)->GetValueBool(&kDefaultBoolValue);
    gAnimIntB6C = *mpManager->mpProperties->GetProperty(0xcbb76b7a)->GetValueInt32();
    float lod2Size = *mpManager->mpProperties->GetProperty(0xa22260b1)->GetValueFloat(&kAnimDefaultFloatValue);
    CreatureSizeCompare sizeCompare(*mpManager->mpProperties->GetProperty(0x18c01e40)->GetValueFloat(&kAnimDefaultFloatValue));
    bool hideWhenOutOfGroup = *mpManager->mpProperties->GetProperty(0xe0e98b25)->GetValueBool(&kAnimDefaultBoolValue);
    SetMaxCreatureByLOD(2, *mpManager->mpProperties->GetProperty(0x17128238)->GetValueInt32());
    SetMaxCreatureByLOD(1, *mpManager->mpProperties->GetProperty(0xf2f23c29)->GetValueInt32());
    SetMaxCreatureByLOD(0, *mpManager->mpProperties->GetProperty(0xf987c782)->GetValueInt32());
    gAnimFloatB74 = *mpManager->mpProperties->GetProperty(0xb9a5e29c)->GetValueFloat(&kDefaultFloatValue);
    gAnimFloatB78 = *mpManager->mpProperties->GetProperty(0xee48fd58)->GetValueFloat(&kDefaultFloatValue);
    gAnimUIntB7C = *mpManager->mpProperties->GetProperty(0x52451e18)->GetValueUInt32();
    gAnimUIntB80 = *mpManager->mpProperties->GetProperty(0x71ae0ceb)->GetValueUInt32();

    mCurrentCreatureByLOD[0] = 0;
    mCurrentCreatureByLOD[1] = 0;
    mCurrentCreatureByLOD[2] = 0;

    Vector3 cameraDir;
    Vector3 cameraPos;
    Frustum frustum;
    if (!viewer)
        viewer = RenderManager()->GetViewer(0);
    if (viewer) {
        viewer->GetCameraLocationInfo(&cameraPos, 0, 0, &cameraDir);
        frustum.Set(viewer->mViewProjection);
    }

    // Cull and measure every creature.
    uint32_t count = mCreatures.size();
    for (uint32_t i = 0; i < count; ++i) {
        cAnimatingCreature* creature = mCreatures.mpBegin[i];
        if (!creature)
            continue;
        creature_instance_data* inst = creature->mpInstance.mpObject;
        if (!inst)
            continue;
        inst->mbFlag2d6 = creature->mbFlag151;

        const creature_static_bounds* bounds = inst->mpStatic;
        float scale = creature->mScale;
        Vector3 origin(bounds->mBoundsOrigin.x * scale, bounds->mBoundsOrigin.y * scale, bounds->mBoundsOrigin.z * scale);
        Vector3 size(bounds->mBoundsSize.x * scale, bounds->mBoundsSize.y * scale, bounds->mBoundsSize.z * scale);
        float diameter = bounds->mBoundsRadius * scale;
        Vector3 center(origin.x + size.x * 0.5f, origin.y + size.y * 0.5f, origin.z + size.z * 0.5f);
        float radius = diameter * 0.5f;

        const Quaternion& q = inst->mOrientation;
        float yw = q.y * q.w, xw = q.x * q.w, zw = q.z * q.w;
        float xx = -(q.x * q.x), yx = q.y * q.x, zx = q.z * q.x;
        float yy = -(q.y * q.y), zy = q.z * q.y, zz = -(q.z * q.z);
        // rotate the local center by the instance orientation: v + 2 * (M' * v)
        Vector3 rotated;
        rotated.x = (zz + yy) * center.x + (yx - zw) * center.y + (zx + yw) * center.z;
        rotated.z = (zx - yw) * center.x + (zy + xw) * center.y + (yy + xx) * center.z;
        Vector3 worldCenter(
            inst->mPosition.x + (rotated.x * 2.0f + center.x),
            inst->mPosition.y + (((yx + zw) * center.x + (zz + xx) * center.y + (zy - xw) * center.z) * 2.0f + center.y),
            inst->mPosition.z + (rotated.z * 2.0f + center.z));

        creature->mbInFrustum = (~(frustum.Test(&worldCenter, radius) >> 6)) & 1;
        if (creature->mbInFrustum) {
            Vector3 screenCenter;
            App()->GetViewer()->ProjectToScreen(&screenCenter, &worldCenter);
            Vector3 edge(cameraDir.x * radius + worldCenter.x,
                         cameraDir.y * radius + worldCenter.y,
                         cameraDir.z * radius + worldCenter.z);
            Vector3 screenEdge;
            App()->GetViewer()->ProjectToScreen(&screenEdge, &edge);
            float dx = screenEdge.x - screenCenter.x;
            float dy = screenEdge.y - screenCenter.y;
            float dz = screenEdge.z - screenCenter.z;
            creature->mScreenSize = dx * dx + dz * dz + dy * dy;
        } else {
            creature->mScreenSize = 0.0f;
        }
    }

    stable_sort(mCreatures.mpBegin, mCreatures.mpEnd, sizeCompare);

    // Drop everything from the first null entry on.
    count = mCreatures.size();
    for (uint32_t i = 0; i < count; ++i) {
        if (!mCreatures.mpBegin[i]) {
            mCreatures.resize(i);
            break;
        }
    }

    count = mCreatures.size();
    for (uint32_t i = 0; i < count; ++i) {
        cAnimatingCreature* creature = mCreatures.mpBegin[i];
        creature_instance_data* inst = creature->mpInstance.mpObject;
        creature->mIndex = i;
        if (!inst)
            continue;

        if (!creature->mbDoUpdate) {
            if (inst->mpMesh)
                inst->mpMesh->SetStateInWorld(true, true, false);
            continue;
        }

        if (!creature->mbInFrustum)
            SetCreatureLOD(creature, 0, 0);
        else if (creature->mScreenSize >= lod2Size)
            SetCreatureLOD(creature, 2, 0);
        else if (creature->mScreenSize >= sizeCompare.mThreshold)
            SetCreatureLOD(creature, 1, 0);
        else
            SetCreatureLOD(creature, 0, 0);

        int lodCount = creature->mLODForced == 4 ? creature->mLODCount : creature->mLODForced;
        if (lodCount > 0)
            creature->UpdateLOD(0);
        else
            creature->mpInstance.mpObject->mSkippedUpdates++;

        if (creature->mpModel && mpManager->mHiddenGroup) {
            uint32_t group = mpModelWorld->GetModelGroup(creature->mpModel, -1);
            if (hideWhenOutOfGroup) {
                if (!group)
                    mpModelWorld->SetModelGroup(creature->mpModel, mpManager->mHiddenGroup, -1);
            } else if (group == mpManager->mHiddenGroup) {
                mpModelWorld->SetModelGroup(creature->mpModel, 0, -1);
            }
        }

        inst->mbFlag270 = creature->mbFlag150;
        inst->mPosition = creature->mPosition;
        inst->mOrientation = creature->mOrientation;
        inst->mScale = creature->mScale;
        inst->mVelocity = creature->mVelocity;
        inst->mAngularSpeed = creature->mAngularSpeed;
        creature->mAngularSpeed = 0.0f;
        creature->mVelocity.x = 0.0f;
        creature->mVelocity.y = 0.0f;
        creature->mVelocity.z = 0.0f;

        switch (creature->mTargetModeRequest) {
        case 0:  inst->mTargetMode = 2; break;
        case 2:  inst->mTargetMode = 1; break;
        default: inst->mTargetMode = 0; break;
        }

        inst->mTarget = creature->mpTargetCreature ? creature->mpTargetCreature->mpInstance
                                                   : AutoRefCount<creature_instance_data>();

        inst->mTargetPosition = creature->mTargetPosition;
        inst->mTargetOrientation.x = 0.0f;
        inst->mTargetOrientation.y = 0.0f;
        inst->mTargetOrientation.z = 0.0f;
        inst->mTargetOrientation.w = 1.0f;

        uint32_t contextMode;
        switch (creature->mTargetContextModeRequest) {
        case 1:  contextMode = 1; break;
        case 2:  contextMode = 3; break;
        default: contextMode = 0; break;
        }
        inst->mTargetContextMode = contextMode;
        inst->mTargetContextValue = creature->mTargetContextValue;
        inst->m2a0 = 0;
        inst->m2a4 = 0;

        if (!HasValidTarget(inst)) {
            inst->mTargetMode = 0;
            inst->mTargetPosition.x = 0.0f;
            inst->mTargetPosition.y = -10.0f;
            inst->mTargetPosition.z = 1.0f;
        }

        creature->PrepareUpdate();
        inst->mRestIdle = creature->mRestIdle;
        inst->mMoveIdle = creature->mMoveIdle;
        inst->mpDataEvents = creature->mDataEvents;
        inst->mpTargetData = creature->mTargetData;
        inst->mTargetDataStride = 0x10;
        inst->mDataEventStride = 0xc;
        inst->mColor = creature->mbHasColor ? creature->mColor : Vector3(1.0f, 1.0f, 1.0f);

        creature->mpBlender->Update(dt, lodCount < 2, lodCount == 0, IsPaused());
        creature->SetRestIdleAnimHandle();
    }
}
