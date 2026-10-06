// Slice s00e600a0: cell-stage camera update (Simulator::Cell, retail 0x00e600a0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE floats, inline x87 exp via f2xm1).
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }

struct BoundingBox { Vector3 lower, upper; };

// eastl::min / max: return references.
template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

// SSE clamp helper of the /arch:SSE cell module (minss/maxss written in asm in the original).
inline float Saturate(float v)
{
    float one = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, v
        minss xmm0, one
        movss v, xmm0
    }
    return v;
}

// Simulator::Cell::cCellUI (ModAPI layout; global sCellUI at 0x016b3c0c).
struct cCellUI {
    uint32_t mGameInput[0x48 / 4];
    Vector3  mCameraPos;     // +0x48
    Vector3  mFocus;         // +0x54
    Vector3  mFocusTrail;    // +0x60
    Vector3  mOffset;        // +0x6c
    Vector3  mOffsetTarget;  // +0x78
    float    mOffsetZVel;    // +0x84
    int      mOffsetMode;    // +0x88
    float    mOffsetSpeed;   // +0x8c
    uint32_t pad90[(0xbc - 0x90) / 4];
    float    mFollowBlend;   // +0xbc
    uint32_t padc0[(0xe0 - 0xc0) / 4];
    int      mTargetCellID;  // +0xe0
    bool     mHasFixedFocus; // +0xe4
    Vector3  mFixedFocus;    // +0xe8
    float    mFocusSpeed;    // +0xf4
    float    mZoom;          // +0xf8
    uint32_t padfc[(0x908 - 0xfc) / 4];
    float    mZoomBlend;     // +0x908
    uint32_t pad90c[(0x934 - 0x90c) / 4];
    bool     field_934[2];
    bool     mCinematic;     // +0x936
};

struct cCellObject {
    uint32_t pad0[0x4c / 4];
    Vector3  mPosition;      // +0x4c
    uint32_t pad58[(0x90 - 0x58) / 4];
    Vector3  mVelocity;      // +0x90
    uint32_t pad9c[(0x1b0 - 0x9c) / 4];
    int      mType;          // +0x1b0
    void* GetEffectProps_00e51900();  // 0x00e51900
};

struct cCellPool {
    cCellObject* Get_00b721d0(int id);  // 0x00b721d0
};

struct cCellGame {
    uint32_t pad0[0x1c / 4];
    cCellPool mCells;        // +0x1c
    char pad20[0x411c - 0x20];
    int  midPlayerCell;      // +0x411c
};

struct cGameModeState {
    char pad0[0x2a];
    bool mbPaused;           // +0x2a
    char pad2b;
    int  mState;             // +0x2c
};

struct Matrix4 { float m[16]; };

struct cViewer {
    void SetNearPlane_007c4ba0(float v);         // 0x007c4ba0
    void SetFarPlane_007c4bc0(float v);          // 0x007c4bc0
    void SetViewAngle_007c5350(float v);         // 0x007c5350
    void SetCameraToWorld_007c4c40(const Matrix4& m);  // 0x007c4c40
};

struct cApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cViewer* GetViewer();       // +0x58
};

extern cCellGame* gspCellGame_016b3c04;
extern cCellUI*   sCellUI_016b3c0c;
extern Vector3    gCellFocusTarget_016b3c28;
extern const Vector3 kUp_015a7c34;

cGameModeState* FUN_00b3d4d0();
float FUN_00e837c0(uint32_t curveID, float x);                       // evaluate tuning curve
void  FUN_00e5ba90(Vector3* cur, const Vector3* target, float speed, float dt); // chase point
float VectorLength_0040ae50(const Vector3* v);
namespace SP { Vector3 normalized_safe_00449c20(const Vector3& v); }          // 0x00449c20
float FUN_00e50ed0(float t, float speed);                            // smoothstep/ease
Vector3 FUN_00e5ba10(const BoundingBox& box, const Vector3& p);      // clamp point to box
void  FUN_00e50a10(float* cur, float* vel, float target, float speed, float dt); // slide
float FUN_00e513d0(float a, float b, float x, float c, float d);     // lerp from curve value
bool  FUN_00e83380(void* props, uint32_t id, float* out);            // get float property
Vector3 FUN_00e83350(void* props);                                   // get vector property
namespace SP { cApp* App_0067dd10(); }                                        // 0x0067dd10
void  FUN_01043580(const Vector3* eye, const Vector3* target, const Vector3* up, Matrix4* out); // look-at
void  FUN_00e549b0();

__forceinline cCellObject* GetCell(int id) { return gspCellGame_016b3c04->mCells.Get_00b721d0(id); }

// @ 0x00e600a0
void FUN_00e600a0(float dt, bool bFrozen)
{
    if (FUN_00b3d4d0()->mbPaused)
        return;

    cCellObject* player = GetCell(gspCellGame_016b3c04->midPlayerCell);

    if (!bFrozen) {
        float focusRate = 1.5f;
        float leadScale = 6.0f;
        float speed = 0.0f;
        if (player) {
            const Vector3& v = player->mVelocity;
            speed = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
            leadScale = FUN_00e837c0(0x7b41f3e9, speed);
            focusRate = FUN_00e837c0(0xce31f6a1, speed);
        }

        cCellObject* target = GetCell(sCellUI_016b3c0c->mTargetCellID);
        cCellUI* ui = sCellUI_016b3c0c;
        if (ui->mHasFixedFocus) {
            FUN_00e5ba90(&ui->mFocus, &ui->mFixedFocus, ui->mFocusSpeed, dt);
            FUN_00e5ba90(&sCellUI_016b3c0c->mFocusTrail, &sCellUI_016b3c0c->mFixedFocus,
                         sCellUI_016b3c0c->mFocusSpeed, dt);
        } else if (target) {
            FUN_00e5ba90(&ui->mFocus, &target->mPosition, ui->mFocusSpeed, dt);
            FUN_00e5ba90(&sCellUI_016b3c0c->mFocusTrail, &target->mPosition,
                         sCellUI_016b3c0c->mFocusSpeed, dt);
        } else if (player) {
            Vector3 pos = player->mPosition;
            float chase = VectorLength_0040ae50(&player->mVelocity) * 1.5f;
            Vector3 d = pos - ui->mFocus;
            if (d.x * d.x + d.y * d.y + d.z * d.z > 0.25f) {
                Vector3 n = SP::normalized_safe_00449c20(ui->mFocus - pos);
                Vector3 p = n * 0.5f + pos;
                FUN_00e5ba90(&ui->mFocus, &p, chase, dt);
                ui = sCellUI_016b3c0c;
            }
            Vector3 e = ui->mFocus - ui->mFocusTrail;
            if (e.x * e.x + e.y * e.y + e.z * e.z > 1.0f) {
                Vector3 n = SP::normalized_safe_00449c20(ui->mFocusTrail - ui->mFocus);
                Vector3 p = ui->mFocus + n;
                FUN_00e5ba90(&ui->mFocusTrail, &p, chase, dt);
                ui = sCellUI_016b3c0c;
            }
            if (speed > 0.25f)
                FUN_00e5ba90(&ui->mFocusTrail, &ui->mFocus, 0.5f, dt);
        }

        ui = sCellUI_016b3c0c;
        float t = 1.0f - (float)exp(-(focusRate * dt));
        Vector3 desired = (ui->mFocus - ui->mFocusTrail) * leadScale + ui->mFocus;
        Vector3& cam = ui->mCameraPos;
        cam = (desired - cam) * t + cam;

        if (player && sCellUI_016b3c0c->mTargetCellID == 0) {
            float blend = dt * 0.2f + sCellUI_016b3c0c->mFollowBlend;
            sCellUI_016b3c0c->mFollowBlend = blend;
            blend = Saturate(blend);
            sCellUI_016b3c0c->mFollowBlend = blend;
            float r = FUN_00e50ed0(sCellUI_016b3c0c->mFollowBlend, speed);

            static const Vector3 kFollowBox(7.0f, 5.0f, 0.0f);
            Vector3& camPos = sCellUI_016b3c0c->mCameraPos;
            Vector3 half(r * kFollowBox.x, r * kFollowBox.y, r * kFollowBox.z);
            Vector3 d = camPos - player->mPosition;
            float len = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
            if (len > 1.5258789e-05f) {
                float inv = 1.0f / len;
                Vector3 n(inv * d.x, inv * d.y, inv * d.z);
                float m = Min(fabsf(half.x / n.x), len);
                m = Min(fabsf(half.y / n.y), m);
                camPos = player->mPosition + n * m;
            }
            BoundingBox box;
            box.lower = camPos - half;
            box.upper = camPos + half;
            Vector3& trail = sCellUI_016b3c0c->mFocusTrail;
            trail = FUN_00e5ba10(box, trail);
        }
    }

    cGameModeState* gm = FUN_00b3d4d0();
    float zoomTarget;
    if (gm->mState == 1 || gm->mState == 2 || sCellUI_016b3c0c->mCinematic)
        zoomTarget = 1.0f;
    else
        zoomTarget = FUN_00e837c0(0x71cb8a60, sCellUI_016b3c0c->mZoom);
    float decay = (float)exp(-4.0f * dt);
    cCellUI* ui = sCellUI_016b3c0c;
    ui->mZoomBlend = (zoomTarget - ui->mZoomBlend) * (1.0f - decay) + ui->mZoomBlend;

    ui = sCellUI_016b3c0c;
    Vector3 offTarget = ui->mOffsetTarget;
    switch (ui->mOffsetMode) {
    case 0: {
        float t = 1.0f - decay;
        Vector3& o = ui->mOffset;
        o = o + (offTarget - o) * t;
        if (o.x == offTarget.x && o.y == offTarget.y && o.z == offTarget.z)
            ui->mOffsetMode = 1;
        break;
    }
    case 1:
        FUN_00e50a10(&ui->mOffset.z, &ui->mOffsetZVel, offTarget.z, 1.0f, dt);
        break;
    case 2:
        FUN_00e50a10(&ui->mOffset.z, &ui->mOffsetZVel, offTarget.z, ui->mOffsetSpeed, dt);
        break;
    }

    ui = sCellUI_016b3c0c;
    Vector3 pos = ui->mCameraPos;
    float zoom = ui->mZoomBlend;
    Vector3 focus(ui->mOffset.x, ui->mOffset.y, ui->mOffset.z * zoom);
    if (player) {
        float k = FUN_00e513d0(0.5f, 1.0f, zoom, 0.5f, 1.0f);
        pos.x = (pos.x - player->mPosition.x) * k + player->mPosition.x;
        pos.y = (pos.y - player->mPosition.y) * k + player->mPosition.y;
    }

    void* props;
    if (!bFrozen && player && (props = player->GetEffectProps_00e51900()) != 0) {
        float amount;
        switch (player->mType) {
        case 0x2e: {
            FUN_00e83380(props, 0x98c942b3, &amount);
            float m = Min(amount, 0.95f);
            Vector3 p = FUN_00e83350(props);
            pos = pos + (p - pos) * m;
            focus = focus + (gCellFocusTarget_016b3c28 - focus) * m;
            break;
        }
        case 0x29: {
            float w;
            FUN_00e83380(props, 0x98c942b2, &w);
            cCellObject* target = GetCell(sCellUI_016b3c0c->mTargetCellID);
            if (target)
                pos = pos + (target->mPosition - pos) * w;
            FUN_00e83380(props, 0x98c942b3, &amount);
            float m = Min(amount, 0.95f);
            focus = focus + (gCellFocusTarget_016b3c28 - focus) * m;
            break;
        }
        case 7:
        case 8:
        case 9:
        case 0x2b:
        case 0x2c: {
            FUN_00e83380(props, 0x98c942b3, &amount);
            float m = Min(amount, 0.95f);
            focus = focus + (gCellFocusTarget_016b3c28 - focus) * m;
            break;
        }
        }
    }

    static const Vector3 kRaise(0.0f, -0.5f, 0.0f);
    float h = FUN_00e513d0(20.0f, 0.0f, focus.z, 1.0f, 0.0f);
    Vector3 raise(h * kRaise.x, h * kRaise.y, kRaise.z * h);
    cViewer* viewer = SP::App_0067dd10()->GetViewer();
    Vector3 eye = pos + raise;
    Vector3 at = (pos + focus) + raise;
    Matrix4 m;
    FUN_01043580(&at, &eye, &kUp_015a7c34, &m);
    viewer->SetNearPlane_007c4ba0(2.0f);
    viewer->SetFarPlane_007c4bc0(2000.0f);
    viewer->SetViewAngle_007c5350(50.0f);
    viewer->SetCameraToWorld_007c4c40(m);
    FUN_00e549b0();
}
