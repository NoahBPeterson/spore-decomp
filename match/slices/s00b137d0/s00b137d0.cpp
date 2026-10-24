// SP::cTerrainCameraController per-frame update (0x00b13c50, 1811 bytes; name guessed).
// Steps: clamp dt to 0.1 s, read the camera FOV and derive the two half-extents tan(2*atan(f)),
// run the interpolation helpers, track the height above the water, then keep the camera anchor
// above the terrain: sample the ground at the anchor and at three points of the view frustum
// footprint, push the anchor radius out to the highest ground (plus a margin) and, in the
// scenario game mode, shift the interpolation targets by the same amount. Finally push the
// transform / near / far to the camera object and send a 5-slot message.
// Retail layout: 2008 PDB layout up to +0x16c, everything after the 0x3c-byte splines is +0x30.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame)
#include "types.h"
#include <math.h>

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {}
};

template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template <class T> inline const T& Min(const T& a, const T& b) { return (b > a) ? a : b; }

extern const cSPVector3 kDirA;   // 0x0167bd44 (rotated by the camera basis when flag 2 is set)
extern const cSPVector3 kDirB;   // 0x0167bd50
extern const cSPVector3 kDirC;   // 0x0167bd38 (kDirA - 0xc)
extern const cSPVector3 kOrientDir; // 0x0167bbf8 (default target orientation direction)

extern cSPVector3 gScaledForward;    // 0x0167bd60 (forwardDir * current)
extern uint32_t   gScaledForwardInit; // 0x0167bd6c (lazy-init flag, bit 0)

extern const float kMinDirLengthSq;  // 0x0145cd14 (1.5258789e-05)
extern const float kAngleScale;      // 0x01567da8
extern const float kForwardStep;     // 0x01567dac
extern const float kOne;             // 0x01485720 (1.0f)

struct cSPQuaternion {   // 12 bytes: only x/y/z are used by the orientation helpers
    float x, y, z;
};

struct cSPSlerpQuaternion {   // 16 bytes: the slerp also returns the blend weight
    float x, y, z, w;
};

void SlerpOrientation(cSPSlerpQuaternion* out, const cSPVector3* a, const cSPQuaternion* b,
                      const cSPVector3* c, const cSPQuaternion* d);   // 0x00b12f90

namespace SP {

class cTerrainMapSet {
public:
    float GetHeightAt(const cSPVector3& pos);   // 0x00f927c0
};

class cTerrainSphere {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual cTerrainMapSet* GetTerrainMapSet();   // slot 3 (+0xc)
    float GetSurfaceRadius();                     // 0x00f987f0
};
cTerrainSphere* GetActiveTerrainSphere();         // 0x00f48aa0

}  // namespace SP

// Camera object (ecx = ebp in the original): +0x170 -> projection data.
struct CameraObj {
    void GetFov(float* tanX, float* tanY);        // 0x007c40c0 (ret 8)
    void SetTransform(const void* xform);         // 0x007c4d00 (ret 4)
    void SetNearClip(float n);                    // 0x007c4ba0 (ret 4)
    void SetFarClip(float f);                     // 0x007c4bc0 (ret 4)
};

// App -> simulator -> camera chain used by the camera push.
class cCameraHost {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual CameraObj* GetCamera();               // slot 7 (+0x1c)
};

class cApp {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual cCameraHost* GetSimulator();          // slot 20 (+0x50)
};
cApp* App();                                      // 0x0067dd10

// 5-slot message: vtable 0x13eb90c (base) then 0x13eb844 (derived), dtor 0x00421cf0.
struct SlotMessage {
    virtual void vf0();
    volatile long mRef;
    float mSlot[10];
    uint32_t m30;
    uint32_t m34;
    uint32_t mMask;
    SlotMessage() : mRef(0) {}
    ~SlotMessage();                               // 0x00421cf0 (Destruct)
};
struct SlotMessageBasic : public SlotMessage {
    virtual void vf0();
    SlotMessageBasic(float a, float b) : SlotMessage() {
        m30 = 0;
        mMask = 0;
        mSlot[0] = a;
        mSlot[2] = b;
    }
};

struct IMessageServer {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void Send(uint32_t id, SlotMessage* msg, int flags);   // slot 5 (+0x14)
};
IMessageServer* MessageServer();                  // 0x0067dcc0
bool FUN_00809970();                              // 0x00809970
void ApplyStateFromProperty(void* prop, float v); // 0x006f32e0 (cdecl)
uint32_t GetCurrentGameMode();                    // 0x00b5b800

extern const float kOnePointFive;                 // 0x013fec70 (1500.0f)

struct cTerrainCameraController {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual void OnUpdate(float dt);              // slot 22 (+0x58)

    uint32_t pad_04[(0x18 - 0x04) / 4];
    bool  targetChanged;      // +0x18
    bool  targetMoving;       // +0x19
    uint16_t pad_1a;
    float currentTime;        // +0x1c
    float targetTime;         // +0x20
    float start;              // +0x24
    float current;            // +0x28
    float end;                // +0x2c
    float target;             // +0x30
    float velocity;           // +0x34
    float targetVelocity;     // +0x38
    bool  angleInitialized;   // +0x3c (cleared after an angle change)
    bool  clampAngle;         // +0x3d (limit the angle step to the target delta)
    uint16_t pad_3e;
    float angleStart;         // +0x40
    float angleTarget;        // +0x44
    uint32_t pad_48[(0x54 - 0x48) / 4];
    cSPVector3 forwardDir;    // +0x54 (scaled by `current` into gScaledForward)
    cSPVector3 prevCenter;    // +0x60
    cSPVector3 currCenter;    // +0x6c
    uint32_t pad_78[(0x84 - 0x78) / 4];
    cSPVector3 centerVelocity; // +0x84
    uint8_t pad_90;           // +0x90
    bool  flag91;             // +0x91
    uint8_t pad_92[(0xac - 0x92)];
    cSPVector3 cameraDir;     // +0xac
    uint32_t pad_b8[(0x10c - 0xb8) / 4];
    float distCurrent;        // +0x10c
    uint32_t pad_110[(0x168 - 0x110) / 4];
    bool  noOrientUpdate;     // +0x168 (skip the orientation update)
    uint8_t pad_169[(0x180 - 0x169)];
    float* keysBegin;         // +0x180
    float* keysEnd;           // +0x184
    uint32_t pad_188[(0x25c - 0x188) / 4];
    float dt;                 // +0x25c (inverse frame time)
    uint32_t pad_260[(0x274 - 0x260) / 4];
    float heightAboveWater;   // +0x274
    uint32_t pad_278[(0x2b4 - 0x278) / 4];
    float minHeight;          // +0x2b4
    uint32_t pad_2b8[(0x2cc - 0x2b8) / 4];
    union {
        uint16_t xflags;      // +0x2cc (bit 1: basis valid, bit 2: moved)
        uint8_t  xflagsLo;
    };
    uint16_t xcount;          // +0x2ce
    cSPVector3 pos;           // +0x2d0
    float scale;              // +0x2dc
    float basis[9];           // +0x2e0 (three columns)
    bool  basisDirty;         // +0x304 (refreshed by FUN_00b134a0)
    uint8_t pad_305[(0x30c - 0x305)];
    void* config;             // +0x30c
    float nearClip;           // +0x310
    float farClip;            // +0x314
    uint8_t pad_318[3];
    bool  dirty;              // +0x31b
    uint32_t pad_31c[(0x364 - 0x31c) / 4];
    uint8_t pad_364;
    bool  keyboardEnabled;    // +0x365

    void UpdateCurrentHeight();              // 0x00b102c0
    void FUN_00b10a90(float dt);             // 0x00b10a90
    void ClampSpread();                      // 0x00b0f770
    void UpdateInterpolation(float dt);      // 0x00b119f0
    void FUN_00b134a0();                     // 0x00b134a0
    void GetTargetOrientation(cSPQuaternion* out);   // 0x00b137d0
    void GetOrientationDirA(cSPQuaternion* out);     // 0x00b13900 (kDirA, no translation)
    void GetOrientationDirC(cSPQuaternion* out);     // 0x00b13a10 (kDirC, no translation)
    void PushToCamera();                     // 0x00b13b50
    void FUN_00b13bb0(cSPQuaternion* out, int blend);   // 0x00b13bb0
    void BlendOrientation(cSPQuaternion* out, const cSPSlerpQuaternion* slerped, int w);   // 0x00b12dd0
    float InterpByAngle();                   // 0x00b0f880
    void FUN_00b14520(const cSPVector3* dir, const cSPVector3* delta);   // 0x00b14520
    void Update(uint32_t ms, CameraObj* cam);   // 0x00b13c50

    __forceinline cSPVector3 Rotate(const cSPVector3& v) const
    {
        if (xflagsLo & 2)
            return cSPVector3((basis[6] * v.z + basis[3] * v.y) + basis[0] * v.x,
                              (basis[7] * v.z + basis[4] * v.y) + basis[1] * v.x,
                              (basis[8] * v.z + basis[5] * v.y) + basis[2] * v.x);
        return v;
    }
};

// @ 0x00b13c50
void cTerrainCameraController::Update(uint32_t ms, CameraObj* cam)
{
    if (FUN_00809970())
        return;

    float dtRaw = (float)ms * 0.001f;
    float dtMax = 0.1f;
    float dt = Min(dtRaw, dtMax);

    float tx, ty;
    cam->GetFov(&tx, &ty);
    float tanA = tanf(atan2f(tx, 1.0f) * 2.0f);
    float tanB = tanf(atan2f(ty, 1.0f) * 2.0f);

    FUN_00b10a90(dt);
    ClampSpread();
    if (dt > 0.0f)
        UpdateInterpolation(dt);

    SP::cTerrainSphere* sphere = SP::GetActiveTerrainSphere();
    if (sphere) {
        float len = (float)sqrt((double)pos.x * pos.x + (double)pos.y * pos.y + (double)pos.z * pos.z);
        float h = len - sphere->GetSurfaceRadius();
        heightAboveWater = h;
        ApplyStateFromProperty(config, h);
    }

    FUN_00b134a0();
    if (keyboardEnabled)
        OnUpdate(dt);
    if (dirty) {
        dirty = false;
        UpdateCurrentHeight();
    }

    if (sphere) {
        cSPVector3 p(pos.x, pos.y, pos.z);
        float groundP = sphere->GetTerrainMapSet()->GetHeightAt(p);
        float radius = sphere->GetSurfaceRadius();

        float ax = kDirA.x, ay = kDirA.y, az = kDirA.z;
        if (xflagsLo & 2) {
            ax = (basis[6] * kDirA.z + basis[3] * kDirA.y) + basis[0] * kDirA.x;
            ay = (basis[7] * kDirA.z + basis[4] * kDirA.y) + basis[1] * kDirA.x;
            az = (basis[8] * kDirA.z + basis[5] * kDirA.y) + basis[2] * kDirA.x;
        }
        float s = scale;
        float bx = kDirB.x, by = kDirB.y, bz = kDirB.z;
        if (xflagsLo & 2) {
            bx = (basis[6] * kDirB.z + basis[3] * kDirB.y) + basis[0] * kDirB.x;
            by = (basis[7] * kDirB.z + basis[4] * kDirB.y) + basis[1] * kDirB.x;
            bz = (basis[8] * kDirB.z + basis[5] * kDirB.y) + basis[2] * kDirB.x;
        }

        float nc = nearClip;
        cSPVector3 c(nc * (s * ax) + p.x, (ay * s) * nc + p.y, (az * s) * nc + p.z);
        float w = nearClip * tanA;
        float dx = (s * bx) * w;
        float dy = (by * s) * w;
        float dz = (bz * s) * w;
        cSPVector3 q1(dx + c.x, dy + c.y, dz + c.z);
        cSPVector3 q2(c.x - dx, c.y - dy, c.z - dz);

        float hC = sphere->GetTerrainMapSet()->GetHeightAt(c);
        if (hC < radius) hC = radius;
        float h1 = sphere->GetTerrainMapSet()->GetHeightAt(q1);
        if (h1 < radius) h1 = radius;
        float h2 = sphere->GetTerrainMapSet()->GetHeightAt(q2);
        if (h2 < radius) h2 = radius;

        const float& hQ = Max(h1, h2);
        const float& hB = Max(groundP, hC);
        float target = (nearClip * tanB + minHeight) + Max(hB, hQ);

        float lenP = (float)sqrt((double)p.x * p.x + ((double)p.y * p.y + (double)p.z * p.z));
        if (lenP < target) {
            xflags |= 4;
            xcount++;
            float inv = 1.0f / lenP;
            float nx = (inv * p.x) * target;
            float ny = (p.y * inv) * target;
            float nz = (p.z * inv) * target;
            pos.x = nx;
            pos.y = ny;
            pos.z = nz;
            if (GetCurrentGameMode() == 0x1654c06) {
                float delta = target - lenP;
                if (targetTime > currentTime) {
                    int n = (int)(keysEnd - keysBegin);
                    for (int i = 0; i < n; i++)
                        keysBegin[i] += delta;
                    current += delta;
                    end += delta;
                    this->target += delta;
                    float zero = 0.0f;
                    velocity = Max(zero, velocity);
                } else {
                    float t = this->target + delta;
                    this->target = t;
                    end = t;
                    current = t;
                    start = t;
                    velocity = t * 0.0f;
                    targetVelocity = t * 0.0f;
                    targetChanged = false;
                    targetMoving = false;
                }
            }
        }
    }

    cam->SetTransform(&xflags);
    cam->SetNearClip(nearClip);
    cam->SetFarClip(farClip);

    IMessageServer* ms2 = MessageServer();
    if (ms2) {
        SlotMessageBasic msg(distCurrent, kOnePointFive);
        ms2->Send(0x60e4e46e, &msg, 0);
    }
}

// ---------------------------------------------------------------------------
// Orientation helpers (kOrientDir / kDirA / kDirC rotated by the camera basis),
// the camera push and the angle/centre-velocity update.
// ---------------------------------------------------------------------------

// @ 0x00b137d0
void cTerrainCameraController::GetTargetOrientation(cSPQuaternion* out)
{
    if (basisDirty)
        FUN_00b134a0();

    cSPVector3 dir = kOrientDir;
    out->x = dir.x;
    out->y = dir.y;
    out->z = dir.z;
    if (xflagsLo & 2) {
        out->x = (basis[6] * dir.z + basis[3] * dir.y) + basis[0] * dir.x;
        out->y = (basis[7] * dir.z + basis[4] * dir.y) + basis[1] * dir.x;
        out->z = (basis[8] * dir.z + basis[5] * dir.y) + basis[2] * dir.x;
    }
    float s = scale;
    out->x = s * out->x + pos.x;
    out->y = s * out->y + pos.y;
    out->z = out->z * s + pos.z;
}

// @ 0x00b13900
void cTerrainCameraController::GetOrientationDirA(cSPQuaternion* out)
{
    if (basisDirty)
        FUN_00b134a0();

    cSPVector3 dir = kDirA;
    out->x = dir.x;
    out->y = dir.y;
    out->z = dir.z;
    if (xflagsLo & 2) {
        out->x = (basis[6] * dir.z + basis[3] * dir.y) + basis[0] * dir.x;
        out->y = (basis[7] * dir.z + basis[4] * dir.y) + basis[1] * dir.x;
        out->z = (basis[8] * dir.z + basis[5] * dir.y) + basis[2] * dir.x;
    }
    float s = scale;
    out->x = s * out->x;
    out->y = s * out->y;
    out->z = out->z * s;
}

// @ 0x00b13a10
void cTerrainCameraController::GetOrientationDirC(cSPQuaternion* out)
{
    if (basisDirty)
        FUN_00b134a0();

    cSPVector3 dir = kDirC;
    out->x = dir.x;
    out->y = dir.y;
    out->z = dir.z;
    if (xflagsLo & 2) {
        out->x = (basis[6] * dir.z + basis[3] * dir.y) + basis[0] * dir.x;
        out->y = (basis[7] * dir.z + basis[4] * dir.y) + basis[1] * dir.x;
        out->z = (basis[8] * dir.z + basis[5] * dir.y) + basis[2] * dir.x;
    }
    float s = scale;
    out->x = s * out->x;
    out->y = s * out->y;
    out->z = out->z * s;
}

// @ 0x00b13b50
void cTerrainCameraController::PushToCamera()
{
    FUN_00b134a0();
    CameraObj* cam = App()->GetSimulator()->GetCamera();
    cam->SetTransform(&xflags);
    cam->SetNearClip(nearClip);
    cam->SetFarClip(farClip);
}

// @ 0x00b13bb0
void cTerrainCameraController::FUN_00b13bb0(cSPQuaternion* out, int blend)
{
    if (!(gScaledForwardInit & 1))
        gScaledForwardInit |= 1;

    float s = current;
    float sx = forwardDir.x * s;
    float sy = forwardDir.y * s;
    float sz = forwardDir.z * s;
    gScaledForward.x = sx;
    gScaledForward.y = sy;
    gScaledForward.z = sz;

    cSPQuaternion target;
    GetTargetOrientation(&target);

    cSPSlerpQuaternion slerped;
    SlerpOrientation(&slerped, &gScaledForward, out, &cameraDir, &target);
    BlendOrientation(out, &slerped, blend);
}

// @ 0x00b14520
void cTerrainCameraController::FUN_00b14520(const cSPVector3* dir, const cSPVector3* delta)
{
    if (dir->x * dir->x + dir->y * dir->y + dir->z * dir->z > kMinDirLengthSq &&
        !noOrientUpdate) {
        float lx = dir->x + delta->x * kForwardStep;
        float ly = delta->y * kForwardStep + dir->y;
        float lz = delta->z * kForwardStep + dir->z;
        cSPQuaternion local = { lx, ly, lz };
        FUN_00b13bb0(&local, 0);

        float angle = InterpByAngle();
        float scaled = angle * kAngleScale;
        float prev = angleTarget - angleStart;
        if (clampAngle)
            angle = Max(prev, scaled);
        float inv = kOne / dt;
        angleTarget = angle;
        centerVelocity.y = (currCenter.y - prevCenter.y) * inv;
        centerVelocity.x = inv * (currCenter.x - prevCenter.x);
        centerVelocity.z = (currCenter.z - prevCenter.z) * inv;
        prevCenter = currCenter;
        angleStart = 0.0f;
        angleInitialized = false;
        clampAngle = true;
        targetMoving = true;
        flag91 = true;
    }
}

// ---------------------------------------------------------------------------
// EASTL vector<Typesetter::Text::EA::RunInfo>::insert(position, n, value)
// (the 16-byte run record, so every element pointer difference is a count >> 4)
// ---------------------------------------------------------------------------

struct RunInfo {          // Typesetter::Text::EA::RunInfo
    float mSlot[4];       // 16 bytes
};

RunInfo FUN_00b11530(RunInfo* a, RunInfo* b, RunInfo* c, RunInfo* d);            // 0x00b11530
RunInfo* FUN_00b115c0(RunInfo* first, RunInfo* last, RunInfo* dest);             // 0x00b115c0
void FUN_00b11580(RunInfo* first, uint32_t count, const RunInfo* value, RunInfo* pos);  // 0x00b11580
RunInfo* FUN_00edba80(RunInfo* first, RunInfo* last, RunInfo* dest);             // 0x00edba80 copy_backward
void FUN_00898580(RunInfo* first, RunInfo* last, const RunInfo* value);          // 0x00898580 fill
void* FUN_00f473a0(uint32_t size, const char* tag, int a, int b, const char* file, int line);  // 0x00f473a0
void FUN_00f47380(void* p);                                                      // 0x00f47380

struct RunInfoVector {
    RunInfo* mpBegin;     // +0x0
    RunInfo* mpEnd;       // +0x4
    RunInfo* mpCapacity;  // +0x8

    void Insert(RunInfo* pos, uint32_t n, const RunInfo& value);   // 0x00b14370
};

// @ 0x00b14370
void RunInfoVector::Insert(RunInfo* pos, uint32_t n, const RunInfo& value)
{
    if ((uint32_t)(mpCapacity - mpEnd) / 16 < n) {
        uint32_t oldSize = (uint32_t)(mpEnd - mpBegin) / 16;
        uint32_t newCapacity = oldSize * 2;
        if (oldSize == 0)
            newCapacity = 1;
        uint32_t newSize = oldSize + n;
        if (newCapacity < newSize)
            newCapacity = newSize;

        RunInfo* newBegin = 0;
        if (newCapacity != 0)
            newBegin = (RunInfo*)FUN_00f473a0(newCapacity * 16, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);

        RunInfo* newPos = FUN_00b115c0(mpBegin, pos, newBegin);
        FUN_00b11580(newPos, n, &value, pos);
        RunInfo* newEnd = FUN_00b115c0(pos, mpEnd, newPos + n);
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
            FUN_00f47380(mpBegin);
        mpBegin = newBegin;
        mpEnd = newEnd;
        mpCapacity = newBegin + newCapacity;
        return;
    }

    if (n == 0)
        return;

    RunInfo valueCopy = value;
    uint32_t available = (uint32_t)(mpEnd - pos) / 16;
    if (available <= n) {
        uint32_t extra = n - available;
        FUN_00b11580(mpEnd, extra, &valueCopy, pos);
        RunInfo* oldEnd = mpEnd;
        mpEnd = oldEnd + extra;
        FUN_00b11530(pos, oldEnd, mpEnd, pos);
        mpEnd = mpEnd + available;
        FUN_00898580(pos, oldEnd, &valueCopy);
        return;
    }

    RunInfo* oldEnd = mpEnd;
    RunInfo* dest = oldEnd - n;
    FUN_00b11530(dest, oldEnd, oldEnd, pos);
    mpEnd = oldEnd + n;
    FUN_00edba80(pos, dest, oldEnd);
    FUN_00898580(pos, pos + n, &valueCopy);
}
