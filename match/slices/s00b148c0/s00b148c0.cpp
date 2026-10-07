// Slice s00b148c0: SP::cTerrainCameraController::MoveCamera (PDB candidate; retail field offsets read
// from the disassembly, they differ from the 2008 PDB layout).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame)
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

typedef unsigned int u32;
typedef unsigned char u8;

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// cInterpolationData<float>
struct FloatBlock {
    bool  targetChanged, targetMoving;
    float currentTime, targetTime, start, current, end, target, velocity, targetVelocity;
};

// cInterpolationData<cSPVector3>
struct DirBlock {
    bool  targetChanged, targetMoving;
    float currentTime, targetTime;
    Vec3  start, current, end, target, velocity, targetVelocity;
    void Reset(float t);                      // 0x00b0fbe0
    void Set(const Vec3* v, int force);       // 0x00b0fae0
};

// cInterpolationData<cSPQuaternion>
struct OrientBlock {
    bool  targetChanged, targetMoving;
    float currentTime, targetTime;
    Quat  start, current, end, target, velocity, targetVelocity;
    void Reset(float t);                      // 0x00b10de0
    void Set(const Quat* q, int force);       // 0x00f4ff00
};

struct IInput { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                virtual void v4(); virtual void v5(); virtual bool IsDown(int key); };
struct IMsgServer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                    virtual void v4(); virtual void Post(int id, void* msg, int arg); };
struct IWindow { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                 virtual void v4(); virtual void v5(); virtual void v6(); virtual void* GetRectOwner(); };
struct IApp { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
              virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
              virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
              virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
              virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
              virtual IWindow* GetWindow(); };
struct IConfig { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                 virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                 virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
                 virtual int Lookup(unsigned id); };
struct IInputDevice { char pad[0x10]; u8 mb10; };
struct IWindowMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                    virtual void v4(); virtual void v5(); virtual void v6(); virtual IInputDevice* GetDevice(); };
struct IMapSet { float GetHeightAt(const Vec3* pos); };   // SP::cTerrainMapSet::GetHeightAt 0x00f927c0
struct IDistGrid {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual IMapSet* GetMapSet();                          // vtable +0xc
    float GetBaseHeight();                                 // FUN_00f987f0
    void  BuildSurfaceOrientation(Quat* out, const Vec3* pos, const Quat* ref);  // 0x00f9c660
    void  BuildSurfaceOrientationDir(Quat* out, const Vec3* pos, const Vec3* dir);  // 0x00f9c960 (overload of BuildSurfaceOrientation)
};
struct VarMap { float GetVar(const char* name); };         // 0x007f2590
struct SlotMessage {
    u32 d[4];
    SlotMessage(int);     // 0x00421c80
    ~SlotMessage();       // 0x00421cf0
};

extern VarMap g_varMap;           // 0x0167bc78
extern float  g_ballistA;         // 0x0167bda8
extern float  g_ballistB;         // 0x0167bda4
extern float  g_ballistC;         // 0x0167bda0
extern float  g_ballistD;         // 0x0167bd9c
extern float  g_rotL;             // 0x0167bd98
extern float  g_rotR;             // 0x0167bd94
extern u8     g_edgeFlag;         // 0x0167bd91
extern u8     g_wasMoving;        // 0x0167bd90
extern float  g_lastDeltaX;       // 0x0167bd84
extern float  g_lastDeltaY;       // 0x0167bd80
extern u32    g_bbf0;             // 0x0167bbf0
extern u32    g_bbf4;             // 0x0167bbf4
extern Vec3   g_axisZ;            // 0x0167bd38
extern const float kDegToRad;     // 0x0145ccfc = 0.017453292
extern const float kDegToRad10;   // 0x01412cb0 = 0.17453292 (mouse y)

bool        FUN_00809970();                       // window-manager busy test
IInput*     GameInputManager();                   // 0x00b3d250
IApp*       SP_App();                             // 0x0067dd10
IWindowMgr* FUN_0067dd50();
IConfig*    ConfigManager();                      // 0x0067dd30
unsigned    GetCurrentGameMode();                 // 0x00b5b800
IMsgServer* MessageServer();                      // 0x0067dcc0
IDistGrid*  DebugDrawGrid();                      // 0x00f48aa0
float       FUN_00b0f060(float lo, float hi, float x);     // clamp((x - lo)/(hi - lo))
void        FUN_007c4010(void* owner, int* rect);          // 0x007c4010 (thiscall, rect[4])
float       VectorLength(const Vec3* v);                   // 0x0040ae50
float*      FUN_005ce2a0(float* out, const float* in);     // 0x005ce2a0
Quat*       FUN_0059b060(Quat* out, const Vec3* axis, float angle);   // axis-angle to quaternion
Quat*       QuatMul(Quat* out, const Quat* a, const Quat* b);         // 0x007dcb00
Vec3*       QuatRotate(Vec3* out, const Vec3* v, const Quat* q);      // 0x0059aed0
void        normalized_safe(Vec3* out, const Vec3* in);               // SP::normalized_safe 0x00449c20
extern "C" double acos(double);

static __forceinline float ClampF(float v, float lo, float hi)
{
    __m128 r = _mm_min_ss(_mm_max_ss(_mm_set_ss(v), _mm_set_ss(lo)), _mm_set_ss(hi));
    return _mm_cvtss_f32(r);
}

static __forceinline const float& MaxRef(const float& a, const float& b) { return (a < b) ? b : a; }

struct cTerrainCameraController {
    char  pad00[0x10];
    bool  mDoEdgeScroll;            // +0x10
    bool  mMouseScrollIsActive;     // +0x11
    bool  mStopCameraTarget;        // +0x12
    bool  mUIZoomIn;                // +0x13
    bool  mUIZoomOut;               // +0x14
    bool  mUIRotateR;               // +0x15
    bool  mUIRotateL;               // +0x16
    bool  mb17;                     // +0x17
    FloatBlock radius;              // +0x18
    DirBlock   dir;                 // +0x3c
    OrientBlock orient;             // +0x90
    FloatBlock distance;            // +0xfc
    FloatBlock pitch;               // +0x120
    FloatBlock yaw;                 // +0x144
    bool  mBallisticMotion;         // +0x168
    bool  mAltZoomMode;             // +0x169
    char  pad16a[0x260 - 0x16a];
    float mPlayerPreferredPhi;      // +0x260
    char  pad264[0x298 - 0x264];
    float mRotateSensX;             // +0x298
    float mRotateSensY;             // +0x29c
    float mZoomStep;                // +0x2a0
    float mScrollSens;              // +0x2a4
    float mEdgeScrollSens;          // +0x2a8
    float mMinPitch;                // +0x2ac
    float mMaxPitch;                // +0x2b0
    float mMinHeight;               // +0x2b4
    char  pad2b8[0x308 - 0x2b8];
    u32   mKey5;                    // +0x308
    char  pad30c[0x31c - 0x30c];
    u32   mButtons;                 // +0x31c
    char  pad320[0x33c - 0x320];
    u32   mKeyboardFlags;           // +0x33c
    char  pad340[0x348 - 0x340];
    float mMouseX;                  // +0x348
    float mMouseY;                  // +0x34c
    char  pad350[0x364 - 0x350];
    bool  mbKeyboard;               // +0x364
    char  pad365[3];
    float mKeyRampTime;             // +0x368
    float mKeyMoveScale;            // +0x36c
    float mKeyRotScale;             // +0x370
    float mDecelSpeed;              // +0x374
    char  pad378[0x388 - 0x378];
    float mWinOffsetX;              // +0x388
    float mWinOffsetY;              // +0x38c
    bool  mb390;                    // +0x390

    float* GetAnchorDirection0();                                   // 0x00b10200
    void   RunCameraScript(float, float, float, float, float);      // 0x00b0f270
    void   FUN_00b13bb0(Vec3* v, int force);                        // 0x00b13bb0
    void   MoveCamera(float yawDelta, float pitchDelta, float zoom, float dt);   // 0x00b148c0
};

static inline void SetYawTarget(FloatBlock& b, float t)
{
    if (t != b.target) {
        b.target = t;
        b.start = b.current;
        b.targetChanged = true;
    }
}

// @ 0x00b148c0
void cTerrainCameraController::MoveCamera(float yawDelta, float pitchDelta, float zoom, float dt)
{
    if (FUN_00809970())
        return;
    if (mb390)
        return;

    float stepX = 0.0f;     // [esp+0x1c]
    float stepY = 0.0f;     // [esp+0x18]

    if (0.0f < fabsf(yawDelta)) {
        float t = yaw.target + yawDelta;
        if (t != yaw.target) {
            yaw.target = t;
            yaw.start = yaw.current;
            yaw.targetChanged = true;
        }
    }
    if (0.0f < fabsf(pitchDelta)) {
        float t = pitch.target + pitchDelta;
        t = ClampF(t, mMinPitch, mMaxPitch);
        if (t != pitch.target) {
            pitch.target = t;
            pitch.start = pitch.current;
            pitch.targetChanged = true;
        }
    }

    if ((mButtons >> 0x11) & 1)
        return;

    if (mKey5 == 0 || mBallisticMotion) {
        g_bbf0 = 0;
        g_bbf4 = 0;
        return;
    }

    float rot = 0.0f;       // [esp+0x2c]
    IInput* in = GameInputManager();
    bool movedFlag = false;     // [esp+0x14]
    bool zoomFlag = false;      // [esp+0x17]
    bool rotFlag = false;       // [esp+0x16]

    if (mKeyboardFlags == 0) {
        if (mbKeyboard && in->IsDown(1)) {
            g_ballistA = g_ballistA + dt;
            float e = FUN_00b0f060(0.0f, mKeyRampTime, g_ballistA);
            movedFlag = true;
            stepY = -(e * mKeyMoveScale);
        } else {
            g_ballistA = 0.0f;
        }
        if (mbKeyboard && in->IsDown(2)) {
            g_ballistB = g_ballistB + dt;
            float e = FUN_00b0f060(0.0f, mKeyRampTime, g_ballistB);
            movedFlag = true;
            stepY = e * mKeyMoveScale + stepY;
        } else {
            g_ballistB = 0.0f;
        }
        if (mbKeyboard && in->IsDown(4)) {
            g_ballistC = g_ballistC + dt;
            float e = FUN_00b0f060(0.0f, mKeyRampTime, g_ballistC);
            movedFlag = true;
            stepX = -(e * mKeyMoveScale);
        } else {
            g_ballistC = 0.0f;
        }
        if (mbKeyboard && in->IsDown(3)) {
            g_ballistD = g_ballistD + dt;
            float e = FUN_00b0f060(0.0f, mKeyRampTime, g_ballistD);
            movedFlag = true;
            stepX = e * mKeyMoveScale + stepX;
        } else {
            g_ballistD = 0.0f;
        }
        if (mUIZoomOut || (mbKeyboard && in->IsDown(9))) {
            zoom = mZoomStep;
            mUIZoomIn = true;
            zoomFlag = true;
        }
        if (mUIRotateR || (mbKeyboard && in->IsDown(0x10))) {
            zoom = -mZoomStep;
            mUIZoomIn = true;
            zoomFlag = true;
        }
    }

    if (mUIRotateL || (mbKeyboard && in->IsDown(0x12))) {
        g_rotL = g_rotL + dt;
        float e = FUN_00b0f060(0.0f, mKeyRampTime, g_rotL);
        rotFlag = true;
        rot = e * mKeyRotScale;
    } else {
        g_rotL = 0.0f;
    }
    if (mb17 || (mbKeyboard && in->IsDown(0x11))) {
        g_rotR = g_rotR + dt;
        float e = FUN_00b0f060(0.0f, mKeyRampTime, g_rotR);
        rotFlag = true;
        rot = rot - e * mKeyRotScale;
    } else {
        g_rotR = 0.0f;
    }

    float altThreshold = g_varMap.GetVar("alt_zoom_threshold");

    if (mPlayerPreferredPhi > 0.0f) {
        float t = mPlayerPreferredPhi - dt;
        float z = 0.0f;
        mPlayerPreferredPhi = MaxRef(t, z);
    }
    if (zoom > 0.0f && !mAltZoomMode && altThreshold >= distance.current) {
        if (mPlayerPreferredPhi == 0.0f) {
            mAltZoomMode = true;
            mPlayerPreferredPhi = -1.0f;
        } else if (0.0f > mPlayerPreferredPhi) {
            mPlayerPreferredPhi = g_varMap.GetVar("alt_zoom_timer");
        }
    }
    if (0.0f > zoom && mAltZoomMode && distance.current >= altThreshold)
        mAltZoomMode = false;

    RunCameraScript(stepX, stepY, zoom, rot, dt);

    stepX = g_varMap.GetVar("keyboard_scroll_x");
    stepY = g_varMap.GetVar("keyboard_scroll_y");
    mRotateSensX = g_varMap.GetVar("mouse_rotate_sensitivity_x") * kDegToRad;
    mRotateSensY = g_varMap.GetVar("mouse_rotate_sensitivity_y") * kDegToRad10;
    mScrollSens = g_varMap.GetVar("mouse_scroll_sensitivity");

    {
        float d = g_varMap.GetVar("distance");
        float lo = 0.1f;
        float t = MaxRef(d, lo);
        if (fabsf(distance.target - t) > 1.5258789e-05f && t != distance.target) {
            distance.start = distance.current;
            distance.target = t;
            distance.targetChanged = true;
        }
    }
    {
        float h = g_varMap.GetVar("min_height");
        float lo = 0.1f;
        mMinHeight = MaxRef(h, lo);
    }
    mMaxPitch = g_varMap.GetVar("max_pitch") * kDegToRad;
    mMinPitch = g_varMap.GetVar("min_pitch") * kDegToRad;
    {
        float p = g_varMap.GetVar("pitch") * kDegToRad;
        p = ClampF(p, mMinPitch, mMaxPitch);
        if (fabsf(pitch.target - p) > 1.5258789e-05f && p != pitch.target) {
            pitch.start = pitch.current;
            pitch.target = p;
            pitch.targetChanged = true;
        }
    }

    if (mMouseScrollIsActive) {
        IWindow* w = SP_App()->GetWindow();
        IWindow* w2 = (IWindow*)w->GetRectOwner();
        int rect[4];
        FUN_007c4010(w2, rect);
        int cy2 = (rect[3] + rect[1]) / 2;
        int cx2 = (rect[2] + rect[0]) / 2;
        float nx = ClampF((mMouseX - mWinOffsetX) / (float)cx2, -1.0f, 1.0f);
        float ny = ClampF((mMouseY - mWinOffsetY) / (float)cy2, -1.0f, 1.0f);
        stepX = fabsf(nx) * nx * mScrollSens + stepX;
        stepY = stepY - fabsf(ny) * ny * mScrollSens;
    } else {
        IInputDevice* dev = FUN_0067dd50()->GetDevice();
        bool edgeOk;
        if (g_edgeFlag == 0 && dev->mb10 == 0)
            edgeOk = false;
        else
            edgeOk = true;
        int cfg = ConfigManager()->Lookup(0x636ec26);
        if (cfg != 0 && mDoEdgeScroll && edgeOk) {
            float ty = g_varMap.GetVar("yaw") * kDegToRad;
            if (fabsf(yaw.target - ty) > 0.0f && ty != yaw.target) {
                yaw.target = ty;
                yaw.start = yaw.current;
                yaw.targetChanged = true;
            }
            float ax = -g_varMap.GetVar("anchor_delta_x");
            float ay = -g_varMap.GetVar("anchor_delta_y");
            if (ax != 0.0f || ay != 0.0f) {
                float s = mEdgeScrollSens;
                stepX = ax * s * dt + stepX;
                stepY = stepY - ay * s * dt;
                if (GetCurrentGameMode() == 0x1654c02 || GetCurrentGameMode() == 0x1654c04) {
                    IMsgServer* ms = MessageServer();
                    if (ms) {
                        SlotMessage msg(0);
                        ms->Post(0x6677221, &msg, 0);
                    }
                }
            }
        }
    }

    {
        float kr = g_varMap.GetVar("keyboard_rotate") * kDegToRad;
        if (0.0f < fabsf(kr)) {
            float t = yaw.target + kr;
            if (t != yaw.target) {
                yaw.target = t;
                yaw.start = yaw.current;
                yaw.targetChanged = true;
            }
        }
    }

    bool moving = (stepX != 0.0f || stepY != 0.0f);
    bool decel = !moving && g_wasMoving != 0;
    static float s_speed = mDecelSpeed;     // guard at 0x0167bd8c, value 0x0167bd88
    g_wasMoving = moving;

    if (decel) {
        float len = VectorLength(&dir.velocity) * s_speed * 250.0f;
        float in2[2];
        in2[0] = g_lastDeltaX;
        in2[1] = g_lastDeltaY;
        float out[2];
        float* r = FUN_005ce2a0(out, in2);
        stepX = r[0] * len;
        stepY = r[1] * len;
    }

    if (moving || decel) {
        g_lastDeltaX = stepX;
        g_lastDeltaY = stepY;
        if (!mStopCameraTarget) {
            Vec3 v;
            v.x = -stepX;
            v.y = -stepY;
            v.z = 0.0f;
            Quat qt;
            Quat q0 = *FUN_0059b060(&qt, &g_axisZ, yaw.current);
            Quat qm;
            Quat* qp = QuatMul(&qm, &orient.current, &q0);
            Vec3 rv;
            Vec3* rp = QuatRotate(&rv, &v, qp);
            float rx = rp->x, ry = rp->y, rz = rp->z;
            float* p = GetAnchorDirection0();
            Vec3 d;
            d.x = p[0] - rx;
            d.y = p[1] - ry;
            d.z = p[2] - rz;
            Vec3 n;
            normalized_safe(&n, &d);
            dir.Set(&n, 0);
            IDistGrid* dg = DebugDrawGrid();
            if (dg) {
                float h = dg->GetMapSet()->GetHeightAt(&n);
                float h0 = dg->GetBaseHeight();
                const float* pm = (h0 > h) ? &h0 : &h;
                float rr = mMinHeight + *pm;
                if (rr != radius.target) {
                    radius.start = radius.current;
                    radius.target = rr;
                    radius.targetChanged = true;
                }
                Quat q;
                dg->BuildSurfaceOrientation(&q, &n, &orient.current);
                orient.Set(&q, 0);
            }
        } else {
            float* p = GetAnchorDirection0();
            float x = p[0];
            float y = p[1];
            float r = radius.current;
            float hyp = sqrtf(y * y + x * x);
            float ang = (float)acos((double)(x / hyp));
            float* p2 = GetAnchorDirection0();
            float az = fabsf(p2[2]);
            float t3 = az * 3.0f;
            float k = (t3 + r) / (r * 6.0f);
            float f2 = (r * 2.0f + t3) / r;
            if (0.0f > p[1])
                ang = -ang;
            Vec3 pos;
            pos.x = x;
            pos.y = y;
            pos.z = 0.0f;
            if (stepX != 0.0f) {
                float a = k / stepX + ang;
                pos.x = cosf(a) * hyp;
                pos.y = sinf(a) * hyp;
            }
            pos.z = p[2];
            if (stepY != 0.0f) {
                float z = f2 * stepY + p[2];
                pos.z = z;
                if (z > r)
                    pos.z = r;
                else if (-r > z)
                    pos.z = -r;
            }
            if (!mb390) {
                if (!mStopCameraTarget) {
                    FUN_00b13bb0(&pos, 0);
                } else {
                    if (yaw.target != 0.0f) {
                        yaw.start = yaw.current;
                        yaw.target = 0.0f;
                        yaw.targetChanged = true;
                    }
                    IDistGrid* dg = DebugDrawGrid();
                    if (dg) {
                        float h0 = dg->GetBaseHeight();
                        float h = dg->GetMapSet()->GetHeightAt(&pos);
                        const float* pm = (h0 > h) ? &h0 : &h;
                        float rr = mMinHeight + *pm;
                        float inv = 1.0f / sqrtf((pos.z * pos.z + (pos.y * pos.y + pos.x * pos.x)) + 1e-08f);
                        Vec3 dn;
                        dn.x = inv * pos.x;
                        dn.y = inv * pos.y;
                        dn.z = inv * pos.z;
                        if (rr != radius.target) {
                            radius.start = radius.current;
                            radius.target = rr;
                            radius.targetChanged = true;
                        }
                        if (dn.x != dir.target.x || dn.y != dir.target.y || dn.z != dir.target.z) {
                            dir.start = dir.current;
                            dir.target = dn;
                            dir.targetChanged = true;
                        }
                        Vec3 sp;
                        sp.z = dn.z * rr;
                        sp.y = dn.y * rr;
                        sp.x = dn.x * rr;
                        float inv2 = 1.0f / sqrtf(sp.z * sp.z + sp.y * sp.y + sp.x * sp.x);
                        Vec3 dd;
                        dd.x = inv2 * sp.x;
                        dd.y = sp.y * inv2;
                        dd.z = sp.z * inv2 - -1.0f;
                        Quat q;
                        dg->BuildSurfaceOrientationDir(&q, &sp, &dd);
                        if (q.x != orient.target.x || q.y != orient.target.y ||
                            q.z != orient.target.z || q.w != orient.target.w) {
                            orient.start = orient.current;
                            orient.target = q;
                            orient.targetChanged = true;
                        }
                    }
                }
            }
        }
        if (decel) {
            dir.Reset(s_speed);
            radius.end = radius.target;
            radius.targetTime = s_speed;
            radius.targetVelocity = radius.targetVelocity * 0.0f;
            radius.currentTime = 0.0f;
            radius.targetChanged = false;
            orient.Reset(s_speed);
        }
    }

    if (movedFlag)
        MessageServer()->Post(0x7bb7345, 0, 0);
    if (zoomFlag)
        MessageServer()->Post(0x7bb7346, 0, 0);
    if (rotFlag)
        MessageServer()->Post(0x7bb7347, 0, 0);

    g_bbf0 = 0;
    g_bbf4 = 0;
}
