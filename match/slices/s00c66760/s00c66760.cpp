// Slice s00c66760 -- SPGonzago/SPGameNounManager.obj: orbit-ring camera-controller helpers,
// 0x00c66760..0x00c67557.
//
// These four functions belong to the same retail-only controller object whose `Update` is
// reconstructed by the sibling slice s00c67560 (0x00c678f0).  The controller embeds a target-driven,
// event-sourcing sub-object at +0x34 (vtable slots +0x2c GetPosition, +0x3c SetOrientation(const
// Quat*), +0x5c a three-vector direction query, +0x60 a two-out-param extents query) and keeps an
// orbit axis (+0x170), a reference direction (+0x17c), a base orientation quaternion (+0x188) and
// direction / orientation accumulators (+0x15c, +0x198, +0x1a4) that it pushes into the +0x34
// sub-object.  The orientation-source state is +0x1b8 (0/1/2).
//
//  0x00c66760 (1199 B): frame update.  Sample the camera ray and the tracked target position, intersect
//                       the ray with the plane through the target whose normal is the orbit axis,
//                       derive the offset direction, build a differential rotation about the axis,
//                       compose it onto the base orientation, normalise and store it.
//  0x00c66c10  (592 B): flush the accumulated orientation into the +0x34 sub-object, choosing the
//                       source by state: a sin/cos table quaternion (0), a second sin/cos table
//                       quaternion (1), or the stored quaternion (+0x1a4) verbatim (2).  The tables
//                       are built from 0.15777a8 on first use (flags at 0x1693d64).
//  0x00c66e60 (1502 B): approach update.  Ray/sphere test around the target, refine the offset
//                       direction, constrain it, rotate the target-to-camera direction onto it, and
//                       (when it changed) store and publish the new orientation via the +0x34 object.
//  0x00c67440  (278 B): eastl::vector<X,sp_vector_allocator>::push_back for the 0x10-byte element kind
//                       used by this class.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast, no EH frame.  The bodies mix x87 and SSE float math
// under /fp:fast, so they are not byte-exact-able; this is behaviourally-equivalent source.
#include "types.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sqrt, sin, cos)

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return (float)sqrt((double)(x * x + y * y + z * z)); }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline Vector3 operator*(float s, const Vector3& a) { return Vector3(s * a.x, s * a.y, s * a.z); }
inline float Dot(const Vector3& a, const Vector3& b) { return (a.x * b.x + a.y * b.y) + a.z * b.z; }

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};

static const float kEpsilon = 1e-8f;
inline float InvSqrtEps(float sq) { return 1.0f / (float)sqrt((double)sq + (double)kEpsilon); }

// ---- callees (address in the comment) ----
Quaternion* Vec4Transform(void* out, const void* q, const void* v);                      // 0x0059aed0
float AngleAroundAxis(const Vector3* d);                                                 // 0x006994a0
bool IntersectRaySphere(const Vector3* org, const Vector3* dir, const Vector3* center,
                        float radius, float* outT);                                      // 0x005a9c40
void* AppGet();                                                                          // 0x0067dd10  SP::App
bool GetCameraRay(void* viewer, Vector3* origin, Vector3* dir);                          // 0x007c4900
Vector3* ConstrainToPlane(Vector3* out, const Vector3* in);                              // 0x00c650d0
void CtrlNotifyChanged(void* self);                                                      // 0x00c65610
void CtrlResetBase(void* self);                                                          // 0x00c63cb0
void* PlanetModelGet();                                                                  // 0x00b3d350
void BuildSurfaceOrientation_2(Vector3* out, const Vector3* a, const Vector3* b);        // 0x00b7f1f0
void QuaternionFromDirections(Quaternion* out, const Vector3* fwd, const Vector3* up);   // 0x00698180
Quaternion* Vec4Rotate(void* out, const Quaternion* q, const Vector3* v);                // 0x007dcb00
void* CopyRange(const void* first, const void* last, void* dest);                        // 0x00b115c0
void* AllocVectorBytes(int size);                                                        // 0x00f473a0
void FreeVectorBytes(void* p);                                                           // 0x00f47380

extern float gF_1471064;      // 0x1471064  half (0.5f)
extern float gF_13ec4b8;      // 0x13ec4b8  epsilon (1e-8f)
extern float gF_1485378;      // 0x1485378  _HK_REAL_ZERO (0.0f)
extern float gF_15777a8;      // 0x15777a8  sin/cos table build angle
extern float gF_1693de0;      // 0x1693de0  table 1 basis X
extern float gF_1693de4;      // 0x1693de4  table 1 basis Y
extern float gF_1693de8;      // 0x1693de8  table 1 basis Z
extern float gF_1693dc8;      // 0x1693dc8  table 2 basis X
extern float gF_1693dcc;      // 0x1693dcc  table 2 basis Y
extern float gF_1693dd0;      // 0x1693dd0  table 2 basis Z
extern Quaternion gQ_1693d54; // 0x1693d54  cached sin/cos quaternion (state 1)
extern Quaternion gQ_1693d44; // 0x1693d44  cached sin/cos quaternion (state 0)
extern uint32_t gF_1693d64;   // 0x1693d64  table-built flags
extern Vector3 gV_1693dd4;    // 0x1693dd4  reference up direction

// Embedded target / event sub-object at controller+0x34.
struct TargetSub {
    PV8 PV2 PV
    virtual const Vector3* GetPosition();             // +0x2c
    virtual void SetOrientation(const Quaternion& q); // +0x3c
    PV8 PV8
    virtual Vector3* GetDirPoint(Vector3* out, const Vector3* a, const Vector3* b);  // +0x5c
    PV
    virtual const void* GetExtents(void* out);        // +0x60
};

// The controller, retail offsets.
struct Ctrl {
    uint32_t pad00[0xd];
    TargetSub mTarget;              // +0x34  embedded target/event sub-object
    uint32_t pad38[0x34];           // 0x38..0x108
    Vector3 mFocus;                 // +0x108  tracked focus point
    uint32_t pad114;
    void* mConstrain;               // +0x118  constraint object (ConstrainToPlane)
    uint32_t pad11c[0x10];          // 0x11c..0x15c
    uint8_t mb120;                  // +0x120  accumulator-valid flag
    uint32_t pad124;
    Quaternion mZeroQuat;           // +0x128  accumulator zeroed by the frame update
    uint32_t pad138[0x9];           // 0x138..0x15c
    Quaternion mApproach;           // +0x15c  derived approach orientation
    uint32_t pad16c;
    Vector3 mAxis;                  // +0x170  orbit axis / plane normal
    Vector3 mDirRef;                // +0x17c  reference direction
    Quaternion mBase;               // +0x188  base orientation
    Quaternion mCached;             // +0x198  last published orientation
    Quaternion mOut;                // +0x1a4  current output orientation
    float mScaleA;                  // +0x1b4
    int32_t mState;                 // +0x1b8  orientation source state (0/1/2)
    uint32_t pad1bc;
    float mScaleB;                  // +0x1c0

    void FrameUpdate();             // 0x00c66760
    void FlushOrientation();        // 0x00c66c10
    void Approach();                // 0x00c66e60
};

// @ 0x00c66760
void Ctrl::FrameUpdate()
{
    CtrlResetBase(this);

    Vector3 origin, dir;
    GetCameraRay(*((void**)((char*)AppGet() + 0)), &origin, &dir);

    // mAxis <- current extents sample; mBase <- previous output orientation.
    mTarget.GetExtents(&mAxis);
    mBase = mOut;

    const Vector3* pos = mTarget.GetPosition();
    float axisDotDir = Dot(dir, mAxis);
    if (axisDotDir == 0.0f)
        return;

    float t = -((Dot(origin, mAxis) - Dot(*pos, mAxis)) / axisDotDir);
    if (!(t >= 0.0f))
        return;

    const Vector3* pos2 = mTarget.GetPosition();
    Vector3 hit = origin + dir * t - *pos2;
    mDirRef = hit * InvSqrtEps(hit.SquaredLength());

    Vector3 surf;
    BuildSurfaceOrientation_2(&surf, mTarget.GetPosition(), (const Vector3*)&mOut);

    Vector3 about;
    mTarget.GetDirPoint(&about, &mDirRef, &mAxis);

    float half = AngleAroundAxis(&about) * gF_1471064;
    float sh = (float)sin((double)half);
    float ch = (float)cos((double)half);
    Quaternion q(sh * mDirRef.x, sh * mDirRef.y, sh * mDirRef.z, ch);

    Quaternion rot;
    Vec4Transform(&rot, &q, &mAxis);

    Quaternion R;
    R.x = (rot.w * mBase.x + rot.x * mBase.w) + (rot.z * mBase.y - rot.y * mBase.z);
    R.y = (rot.w * mBase.y + rot.y * mBase.w) + (rot.z * mBase.x - rot.x * mBase.z);
    R.z = (rot.w * mBase.z + rot.z * mBase.w) + (rot.y * mBase.x - rot.x * mBase.y);
    R.w = rot.w * mBase.w - ((rot.z * mBase.z + rot.y * mBase.y) + rot.x * mBase.x);

    mZeroQuat.x = 0.0f;
    mZeroQuat.y = 0.0f;
    mZeroQuat.z = 0.0f;
    mZeroQuat.w = 0.0f;
    mb120 = 0;

    float inv = InvSqrtEps(R.x * R.x + R.y * R.y + R.z * R.z + R.w * R.w);
    mApproach.x = inv * R.x;
    mApproach.y = inv * R.y;
    mApproach.z = inv * R.z;
    mApproach.w = inv * R.w;
    (void)surf;
}

// @ 0x00c66c10
void Ctrl::FlushOrientation()
{
    if ((gF_1693d64 & 1) == 0) {
        gF_1693d64 |= 1;
        float a = gF_15777a8 * gF_1471064 * gF_1471064;
        float sh = (float)sin((double)a);
        float ch = (float)cos((double)a);
        gQ_1693d54.x = gF_1693de0 * sh;
        gQ_1693d54.y = gF_1693de4 * sh;
        gQ_1693d54.z = gF_1693de8 * sh;
        gQ_1693d54.w = ch;
    }
    if ((gF_1693d64 & 2) == 0) {
        gF_1693d64 |= 2;
        float a = gF_15777a8 * gF_1471064 * gF_1471064;
        float sh = (float)sin((double)a);
        float ch = (float)cos((double)a);
        gQ_1693d44.x = gF_1693dc8 * sh;
        gQ_1693d44.y = gF_1693dcc * sh;
        gQ_1693d44.z = gF_1693dd0 * sh;
        gQ_1693d44.w = ch;
    }

    Quaternion q;
    switch (mState) {
    case 0: {
        Vec4Rotate(&q, &gQ_1693d44, (const Vector3*)&mOut);
        float inv = InvSqrtEps(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
        q.x = inv * q.x;
        q.y = inv * q.y;
        q.z = inv * q.z;
        q.w = q.w * inv;
        break;
    }
    case 1: {
        Vec4Rotate(&q, &gQ_1693d54, (const Vector3*)&mOut);
        float inv = InvSqrtEps(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
        q.x = inv * q.x;
        q.y = inv * q.y;
        q.z = inv * q.z;
        q.w = q.w * inv;
        break;
    }
    case 2:
        q = mOut;
        break;
    default:
        return;
    }
    mTarget.SetOrientation(q);
}

// @ 0x00c66e60
void Ctrl::Approach()
{
    Vector3 extA, extB;
    mTarget.GetExtents(&extA);

    // Radius of the target sphere from the stored output orientation components.
    float radius = mOut.w * mOut.y + mOut.z;

    Vector3 org, rayDir;
    float t;
    bool hit = IntersectRaySphere(&org, &rayDir, &mAxis, radius, &t);

    const Vector3* pos = mTarget.GetPosition();
    Vector3 delta;
    if (hit) {
        delta.x = (extA.x + org.x) - pos->x;
        delta.y = (extA.y + rayDir.y) - pos->y;
        delta.z = (extA.z + rayDir.z) - pos->z;
    } else {
        delta.x = pos->x - extA.x;
        delta.y = pos->y - extA.y;
        delta.z = pos->z - extA.z;
    }

    Vector3 approachDir = delta * InvSqrtEps(delta.SquaredLength());
    (void)extB;

    Vector3 constrained;
    ConstrainToPlane(&constrained, &approachDir);

    Vector3 ref;
    Vec4Transform(&ref, &gV_1693dd4, &mDirRef);
    Quaternion targetRot;
    QuaternionFromDirections(&targetRot, &ref, &constrained);

    Quaternion R;
    R.x = (targetRot.w * mBase.x + targetRot.x * mBase.w) + (targetRot.z * mBase.y - targetRot.y * mBase.z);
    R.y = (targetRot.w * mBase.y + targetRot.y * mBase.w) + (targetRot.x * mBase.z - targetRot.z * mBase.x);
    R.z = (targetRot.w * mBase.z + targetRot.z * mBase.w) + (targetRot.y * mBase.x - targetRot.x * mBase.y);
    R.w = targetRot.w * mBase.w - ((targetRot.z * mBase.z + targetRot.y * mBase.y) + targetRot.x * mBase.x);

    Quaternion N;
    float inv = InvSqrtEps(R.x * R.x + R.y * R.y + R.z * R.z + R.w * R.w);
    N.x = inv * R.x;
    N.y = inv * R.y;
    N.z = inv * R.z;
    N.w = R.w * inv;

    if (mCached.x != N.x || mCached.y != N.y || mCached.z != N.z || mCached.w != N.w) {
        mCached = N;
        mTarget.SetOrientation(mCached);
        CtrlNotifyChanged(this);
    }
}

// 0x10-byte vector element kind appended by 0x00c67440 (four floats).
struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
};

struct Vector4Array {
    Vector4* mpBegin;
    Vector4* mpEnd;
    Vector4* mpCapacity;
    void insert(Vector4* dest, const Vector4* value);
};

// Copies [first,last) backwards ending at resultEnd (eastl copy_backward, 0x00edba80).
void* CopyBackward(const void* first, const void* last, void* resultEnd);

// @ 0x00c67440
void Vector4Array::insert(Vector4* dest, const Vector4* value)
{
    Vector4* begin = mpBegin;
    Vector4* end = mpEnd;
    if (end != mpCapacity) {
        const Vector4* v = value;
        if (dest <= v && v < end)
            v = v + 1;
        if (end != 0)
            end[0] = end[-1];
        CopyBackward(dest, end - 1, end);
        *dest = *v;
        mpEnd = end + 1;
        return;
    }

    int newCap = (int)(end - begin) >> 4;
    if (newCap <= 0) {
        newCap = 1;
    } else {
        newCap = newCap * 2;
        if (newCap == 0) {
            mpBegin = 0;
            mpEnd = 0;
            mpCapacity = 0;
            return;
        }
    }

    Vector4* mem = (Vector4*)AllocVectorBytes(newCap << 4);
    Vector4* after = (Vector4*)CopyRange(begin, dest, mem);
    if (after != 0)
        *after = *value;
    Vector4* newEnd = (Vector4*)CopyRange(dest, end, after + 1);
    if (begin != 0 && ((int*)begin)[-1] != 0)
        FreeVectorBytes(begin);
    mpBegin = mem;
    mpEnd = newEnd;
    mpCapacity = (Vector4*)((newCap << 4) + (int)mem);
}
