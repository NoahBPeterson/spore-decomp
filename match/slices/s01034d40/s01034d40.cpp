// Slice s01034d40 -- 0x01035000: a render layer's ILayer::DrawLayer(flags, layerIndex, viewers, stats).
//
// The layer owns three cViewer copies (this+4, this+0x178, this+0x2ec) and a near/far/fov triple
// (+0x460/+0x464/+0x468).  For the layer indices it understands it copies the caller's viewer into one of
// its own viewers, adjusts that copy, and forwards the draw to other layers:
//   index 5  (universe context 0): orbit-camera: put viewer0 at the active planet's position/orientation
//                                  (view transform composed with the planet's rotation), draw the model-world
//                                  layer and the layer at b3d470()+0xa0 (index 0x12), restore render mode 6.
//   index 4  (not UFO-skipped)   : viewer1 = copy of the caller's viewer with this->near/far, view angle and
//                                  a distance-faded camera transform (fade = clamp((2190 - (|pos| - 10)) / 2190)),
//                                  draw through the layer at b3d470()+0xa8 as index 0x12.
//   index 6  (universe context 0): viewer2 = copy of the caller's viewer, draw through b3d470()+0xb4 as index 0x12.
//   index 0xd                    : forward to the Gonzago model world's layer (and in context 1, to the main
//                                  model world with its render groups temporarily set to 6, plus debug-flag
//                                  gated extra draws).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).  Names come from the ModAPI headers where the vtable slot or
// address agrees (IModelWorld::GetActive/AsLayer/SetRenderGroups, ILayer::DrawLayer, cViewer, Transform);
// layouts are the retail offsets read from the disassembly.
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

struct Matrix3
{
    float m[9];
    Matrix3(const Matrix3& other);                              // 0x0041cb40 (out of line copy)
    Matrix3() {}
    Matrix3& operator=(const Matrix3& o) { for (int i = 0; i < 9; i++) m[i] = o.m[i]; return *this; }
};

extern Vector3 gZeroVector;                                      // 0x016df344
extern Matrix3 gIdentityMatrix;                                  // 0x016df3b4
extern const float kCameraFarPlane;                              // 0x0146299c (200000.0f)

struct Transform
{
    uint16_t mnFlags;
    int16_t  mnCount;
    Vector3  mOffset;
    float    mfScale;
    Matrix3  mRotation;
    Transform();                                                 // 0x00409930 (out of line)
    void Reset();                                                // 0x005aa530
    // inline field-by-field initialisation (the default Transform state)
    explicit Transform(int)
        : mnFlags(0), mnCount(0), mfScale(1.0f), mRotation(gIdentityMatrix)
    {
        mOffset.x = gZeroVector.x;
        mOffset.y = gZeroVector.y;
        mOffset.z = gZeroVector.z;
    }
    void SetRotation(const Matrix3& r) { mRotation = r; mnFlags |= 2; mnCount++; }
    void SetOffset(const Vector3& v) { mOffset = v; mnFlags |= 4; mnCount++; }
};

struct cViewer
{
    char pad[0x174];
    void Copy(const cViewer* src, int a, int b);                 // 0x007c50b0
    void GetViewTransform(Transform* out);                       // 0x007c40f0
    void SetNearPlane(float n);                                  // 0x007c4ba0
    void SetFarPlane(float f);                                   // 0x007c4bc0
    void SetCameraTransform(const Transform* t);                 // 0x007c4d00
    void SetViewAngle(float a);                                  // 0x007c5350
    void SetRenderMode(int mode);                                // 0x007c3c50
    float GetNearPlane();                                        // 0x007c3c90
    float GetFarPlane();                                         // 0x007c3ca0
};

struct RenderStatistics;
struct ILayer
{
    virtual int AddRef();
    virtual int Release();
    virtual ~ILayer();
    virtual void DrawLayer(int flags, int layerIndex, cViewer** viewers, RenderStatistics* stats);   // +0x0c
};

struct Bits64 { uint32_t w[2]; Bits64() { w[0] = 0; w[1] = 0; } };

// placeholder virtual slots (the vtable slots between the ones that are actually called)
#define VP1(n) virtual void n();
#define VP4(n) VP1(n##a) VP1(n##b) VP1(n##c) VP1(n##d)
#define VP16(n) VP4(n##a) VP4(n##b) VP4(n##c) VP4(n##d)

struct IModelWorld
{
    VP16(p0) VP16(p1) VP16(p2) VP16(p3) VP4(q0) VP1(r0) VP1(r1) VP1(r2)          // slots 0..70
    virtual void SetRenderGroups(Bits64* a, Bits64* b, int drawSet);             // +0x11c
    virtual void GetRenderGroups(Bits64* a, Bits64* b, int drawSet);             // +0x120
    VP4(s0) VP1(t0)                                                              // slots 73..77
    virtual bool GetActive();                                                    // +0x138
    virtual ILayer* AsLayer();                                                   // +0x13c
};
struct IWorldManager                                                             // returned by 0x00b3d240
{
    VP16(a0) VP4(b0) VP4(b1) VP4(b2)                                             // slots 0..27
    virtual IModelWorld* GetModelWorld();                                        // +0x70
};
struct ILayerProvider                                                            // object at (b3d470() + 0xa0 / 0xa8 / 0xb4)
{
    VP16(a0) VP16(a1) VP4(a2) VP4(a3)                                            // slots 0..39
    virtual ILayer* GetLayer();                                                  // +0xa0
};
struct LayerTable                                                                // returned by 0x00b3d470
{
    char pad[0xa0];
    ILayerProvider* mpLayer0;                                                    // +0xa0
    char pad2[4];
    ILayerProvider* mpLayer1;                                                    // +0xa8
    char pad3[8];
    ILayerProvider* mpLayer2;                                                    // +0xb4
};

struct IPlanet                                                                   // returned by GetActivePlanet()
{
    VP4(a0) VP4(a1) VP1(a2) VP1(a3) VP1(a4)                                        // slots 0..10
    virtual Vector3* GetPosition();                                              // +0x2c
    virtual Quaternion* GetOrientation();                                        // +0x30
};

IPlanet* GetActivePlanet();                                                      // 0x01021260 SP::cSPLivingUniverse::GetActivePlanet
int GetUniverseContext();                                                        // 0x01021080 SP::cSPLivingUniverse::GetUniverseContext
IWorldManager* GetWorldManager();                                                // 0x00b3d240
LayerTable* GetLayerTable();                                                     // 0x00b3d470
IModelWorld* GonzagoModelWorld();                                                // 0x00b3d520 SP::GonzagoModelWorld
Vector3* RotateByQuaternion(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);               // 0x0059c190 SP::Matrix3FromQuaternion

extern bool gDebugDrawGonzago;                                                   // 0x015b773a
extern bool gDebugDrawModelWorld;                                                // 0x015b773b
extern bool gDebugDrawLayer12;                                                   // 0x015b7739
extern bool gDebugDrawPlanetWorld;                                               // 0x015b7738

inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

struct cSpaceRenderLayer : ILayer
{
    cViewer mViewer0;                                            // +0x004
    cViewer mViewer1;                                            // +0x178
    cViewer mViewer2;                                            // +0x2ec
    float mNearPlane;                                            // +0x460
    float mFarPlane;                                             // +0x464
    float mViewAngle;                                            // +0x468
    void DrawLayer(int flags, int layerIndex, cViewer** viewers, RenderStatistics* stats);   // 0x01035000
};

// @ 0x01035000
void cSpaceRenderLayer::DrawLayer(int flags, int layerIndex, cViewer** viewers, RenderStatistics* stats)
{
    IPlanet* planet = GetActivePlanet();
    int context = GetUniverseContext();

    if (context == 0)
    {
        if (layerIndex == 5)
        {
            cViewer* viewer = viewers[0];
            Transform xf(0);
            viewer->GetViewTransform(&xf);

            Vector3 p;
            p.x = xf.mOffset.x * 0.01f;
            p.y = xf.mOffset.y * 0.01f;
            p.z = xf.mOffset.z * 0.01f;
            Vector3 rotated;
            const Vector3* r = RotateByQuaternion(&rotated, &p, planet->GetOrientation());
            const Vector3* pos = planet->GetPosition();
            p.x = pos->x + r->x;
            p.y = pos->y + r->y;
            p.z = pos->z + r->z;

            Matrix3 mbuf;
            const Matrix3* m = Matrix3FromQuaternion(&mbuf, planet->GetOrientation());
            const float* a = xf.mRotation.m;
            const float* b = m->m;
            Matrix3 rot;
            rot.m[0] = (a[0] * b[0] + a[1] * b[3]) + a[2] * b[6];
            rot.m[1] = (a[0] * b[1] + a[1] * b[4]) + a[2] * b[7];
            rot.m[2] = (a[0] * b[2] + a[1] * b[5]) + a[2] * b[8];
            rot.m[3] = (a[3] * b[0] + a[4] * b[3]) + a[5] * b[6];
            rot.m[4] = (a[3] * b[1] + a[4] * b[4]) + a[5] * b[7];
            rot.m[5] = (a[3] * b[2] + a[4] * b[5]) + a[5] * b[8];
            rot.m[6] = (a[6] * b[0] + a[7] * b[3]) + a[8] * b[6];
            rot.m[7] = (a[6] * b[1] + a[7] * b[4]) + a[8] * b[7];
            rot.m[8] = (a[6] * b[2] + a[7] * b[5]) + a[8] * b[8];

            Transform xf2(0);
            xf2.SetRotation(rot);
            xf2.SetOffset(p);

            mViewer0.Copy(viewer, 0, 0);
            mViewer0.SetFarPlane(kCameraFarPlane);
            mViewer0.SetCameraTransform(&xf2);

            cViewer* out[4];
            out[0] = &mViewer0;
            out[1] = viewers[1];
            out[2] = viewers[2];
            out[3] = viewers[3];

            IModelWorld* world = GetWorldManager()->GetModelWorld();
            if (world && world->GetActive())
                world->AsLayer()->DrawLayer(flags, 5, out, stats);
            GetLayerTable()->mpLayer0->GetLayer()->DrawLayer(flags, 0x12, out, stats);
            viewer->SetRenderMode(6);
            return;
        }
        if (layerIndex == 0xd)
        {
            GonzagoModelWorld()->AsLayer()->DrawLayer(flags, 0xd, viewers, stats);
            return;
        }
    }
    else if (context == 1 && layerIndex == 0xd)
    {
        IModelWorld* world = GetWorldManager()->GetModelWorld();
        if (world && world->GetActive() && gDebugDrawModelWorld)
        {
            Bits64 groupsA, groupsB;
            world->GetRenderGroups(&groupsA, &groupsB, 6);
            world->SetRenderGroups(&groupsA, &groupsB, 6);
            world->AsLayer()->DrawLayer(flags | 6, 0xd, viewers, stats);
            world->SetRenderGroups(&groupsA, &groupsB, 6);
        }
        if (gDebugDrawGonzago)
            GonzagoModelWorld()->AsLayer()->DrawLayer(flags, 0xd, viewers, stats);
        if (gDebugDrawLayer12)
            GetLayerTable()->mpLayer0->GetLayer()->DrawLayer(flags, 0x12, viewers, stats);
        if (world && world->GetActive() && gDebugDrawPlanetWorld)
        {
            IModelWorld* world2 = GetWorldManager()->GetModelWorld();
            Bits64 groupsA, groupsB;
            world2->GetRenderGroups(&groupsA, &groupsB, 6);
            world2->SetRenderGroups(&groupsA, &groupsB, 6);
            world2->AsLayer()->DrawLayer(flags | 6, 0xd, viewers, stats);
            world2->SetRenderGroups(&groupsA, &groupsB, 6);
        }
        return;
    }

    if (layerIndex == 4)
    {
        if (flags & 0x1000000)
            return;
        cViewer* viewer = viewers[0];
        viewer->GetFarPlane();
        viewer->GetNearPlane();
        Transform xf;
        xf.Reset();
        viewer->GetViewTransform(&xf);
        float fade = (2190.0f - (sqrtf(xf.mOffset.x * xf.mOffset.x + xf.mOffset.y * xf.mOffset.y
                                       + xf.mOffset.z * xf.mOffset.z) - 10.0f)) * 0.000456621f;
        fade = Clamp(fade, 0.0f, 1.0f);
        float angle = mViewAngle;
        mViewer1.Copy(viewer, 0, 0);
        mViewer1.SetNearPlane(mNearPlane);
        mViewer1.SetFarPlane(mFarPlane);
        mViewer1.SetCameraTransform(&xf);
        mViewer1.SetViewAngle(angle);

        cViewer* out[4];
        out[0] = &mViewer1;
        out[1] = viewers[1];
        out[2] = viewers[2];
        out[3] = viewers[3];
        GetLayerTable()->mpLayer1->GetLayer()->DrawLayer(flags, 0x12, out, stats);
        return;
    }

    if (layerIndex == 0xd)
    {
        GonzagoModelWorld()->AsLayer()->DrawLayer(flags, 0xd, viewers, stats);
        return;
    }
    if (layerIndex != 6)
        return;
    if (context != 0)
        return;

    mViewer2.Copy(viewers[0], 0, 0);
    cViewer* out[4];
    out[0] = &mViewer2;
    out[1] = viewers[1];
    out[2] = viewers[2];
    out[3] = viewers[3];
    GetLayerTable()->mpLayer2->GetLayer()->DrawLayer(flags, 0x12, out, stats);
}
