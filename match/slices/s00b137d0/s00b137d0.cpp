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
    uint32_t pad_3c[(0x10c - 0x3c) / 4];
    float distCurrent;        // +0x10c
    uint32_t pad_110[(0x180 - 0x110) / 4];
    float* keysBegin;         // +0x180
    float* keysEnd;           // +0x184
    uint32_t pad_188[(0x274 - 0x188) / 4];
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
    uint32_t pad_304[2];
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
