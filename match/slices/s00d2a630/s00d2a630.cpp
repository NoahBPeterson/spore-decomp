// slice s00d2a630 -- SP::cCreatureCamera standard-control camera update + SetTransform.
//   0x00d2a630  SP::cCreatureCamera::UpdateCamera_StandardControl(float dt)
//   0x00d2a980  SP::cCreatureCamera::SetTransform(float dt)  (per-frame mode dispatch)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <math.h>
#include "types.h"

#pragma intrinsic(sqrt, fabs)

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// The module's SSE clamp helper (maxss then minss).
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

extern float g_15827b0;    // 0x015827b0
extern float g_1485720;    // 0x01485720  (1.0f)
extern float g_158280c;    // 0x0158280c
extern float g_13ec4b8;    // 0x013ec4b8  (epsilon)
extern float g_147a31c;    // 0x0147a31c  (1.5258789e-05f)
extern float g_147a2fc;    // 0x0147a2fc
extern float g_15827ec;    // 0x015827ec
extern int   g_169df74;    // 0x0169df74
extern float g_169df70;    // 0x0169df70
extern unsigned char g_169de85;  // 0x0169de85

float __cdecl FUN_005b4f20(float);                              // 0x005b4f20
void  __cdecl RotateTowards(float*, float*, float*, float);      // 0x00b0fd00

struct IGameInputManager {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual bool IsKeyDown(int);                                 // +0x18
};
IGameInputManager* __cdecl GameInputManager();                   // 0x00b3d250
struct cGameNounManager { void* GetAvatar(); };
cGameNounManager* __cdecl NounManager();                         // 0x00b3d300
void* __cdecl GetCurrentGameMode();                              // 0x00b5b800

namespace SP {

class cCreatureCamera {
public:
    // callees (thiscall unless noted)
    void FUN_00d27300();                    // 0x00d27300
    void ManageAutoCameraMovement(float);   // 0x00d22300
    void FUN_00d24550();                    // 0x00d24550
    void FUN_00d209b0();                    // 0x00d209b0
    void ApplyPlayerRequests();             // 0x00d26790
    void FUN_00d20f00();                    // 0x00d20f00
    void FUN_00d26030();                    // 0x00d26030
    void ApplyPlayerDeltas(bool);           // 0x00d27a70
    void UpdateDesiredLookAt();             // 0x00d28900
    void FUN_00d29ca0();                    // 0x00d29ca0
    void FUN_00d20c70();                    // 0x00d20c70
    void FUN_00d22f30();                    // 0x00d22f30
    void FUN_00d27810(int);                 // 0x00d27810
    void FUN_00d23840();                    // 0x00d23840
    float FUN_00d20620(float);              // 0x00d20620
    void FUN_00d28300(float);               // 0x00d28300  (free-look camera update)
    void SetTransform(float);               // 0x00d2a980
    void UpdateCamera_StandardControl(float); // 0x00d2a630

    char  pad00[0x1c];
    float mDt;                 // +0x1c
    float mOsc;                // +0x20
    char  pad24[0x38 - 0x24];
    Vec3  m38;                 // +0x38
    char  pad44[0x48 - 0x44];
    Vec3  m48;                 // +0x48
    Vec3  m54;                 // +0x54
    Quat  m60;                 // +0x60
    char  pad70[0xb8 - 0x70];
    Vec3  mB8;                 // +0xb8
    char  padC4[0x104 - 0xc4];
    bool  mb104;               // +0x104
    bool  mb105;               // +0x105
    char  pad106[0x114 - 0x106];
    Vec3  m114;                // +0x114
    char  pad120[0x13c - 0x120];
    Vec3  m13C;                // +0x13c
    Vec3  m148;                // +0x148
    Quat  m154;                // +0x154
    bool  mb164;               // +0x164
    char  pad165[0x174 - 0x165];
    float m174;                // +0x174
    float m178;                // +0x178
    float m17c;                // +0x17c
    char  pad180[0x1e8 - 0x180];
    int   mI1E8;               // +0x1e8
    int   mI1EC;               // +0x1ec
    char  pad1f0[0x208 - 0x1f0];
    float m208;                // +0x208
    float m20C;                // +0x20c
    float m210;                // +0x210
    float m214;                // +0x214
    float m220;                // +0x220
    char  pad224[0x299 - 0x224];
    bool  mCamReverse;         // +0x299
    char  pad29a[0x2b1 - 0x29a];
    bool  mb2b1;               // +0x2b1
    bool  mb2b2;               // +0x2b2
    bool  mb2b3;               // +0x2b3
    bool  mb2b4;               // +0x2b4
    char  pad2b5[0x2b8 - 0x2b5];
    float m2b8;                // +0x2b8
    unsigned m2bc;             // +0x2bc
    char  pad2c0[0x314 - 0x2c0];
    bool  mb314;               // +0x314
    bool  mb315;               // +0x315
};

// @ 0x00d2a630
void cCreatureCamera::UpdateCamera_StandardControl(float dt)
{
    mDt = dt;
    FUN_00d27300();
    ManageAutoCameraMovement(dt);
    FUN_00d24550();
    FUN_00d209b0();

    if (mI1EC == 0) {
        float inv = 1.0f / sqrtf((m114.x * m114.x + m114.y * m114.y + m114.z * m114.z) + g_13ec4b8);
        float nx = m114.x * inv;
        float ny = m114.y * inv;
        float nz = m114.z * inv;
        float d = nz * m38.z + ny * m38.y + nx * m38.x;
        float rx = m38.x - nx * d;
        float ry = m38.y - ny * d;
        float rz = m38.z - nz * d;
        float inv2 = 1.0f / sqrtf((rx * rx + rz * rz) + ry * ry + g_13ec4b8);
        m38.x = rx * inv2;
        m38.y = ry * inv2;
        m38.z = rz * inv2;
    } else if (mI1EC == 1) {
        float t = g_15827b0 * dt;
        float lo = g_1485720;
        float sel = (lo <= t) ? lo : t;
        sel = Clamp(sel, 0.0f, lo);
        Vec3 out;
        RotateTowards((float*)&out, (float*)&m38, (float*)&mB8, sel);
        float inv = 1.0f / sqrtf((out.x * out.x + out.z * out.z) + out.y * out.y + g_13ec4b8);
        m38.x = out.x * inv;
        m38.y = out.y * inv;
        m38.z = out.z * inv;
    }

    ApplyPlayerRequests();
    if (NounManager()->GetAvatar() != 0)
        FUN_00d20f00();
    FUN_00d26030();
    FUN_00d27810(1);

    if (GetCurrentGameMode() == (void*)0x01654c05)
        UpdateDesiredLookAt();
    else if (GetCurrentGameMode() == (void*)0x01654c10)
        FUN_00d29ca0();
    else
        mb164 = false;

    m48 = m13C;
    m54 = m148;
    FUN_00d20c70();
    FUN_00d22f30();
    FUN_00d27810(0);
    m60 = m154;
    mOsc += mDt;
    FUN_00d23840();
}

// @ 0x00d2a980
void cCreatureCamera::SetTransform(float dt)
{
    float f = mb315 ? (dt + m2b8) : 0.0f;
    m2b8 = f;

    switch (mI1E8) {
    case 1:
        m174 = m174 - g_158280c * dt;
        g_169de85 = 1;
        break;
    case 2:
        m174 = g_158280c * dt + m174;
        g_169de85 = 1;
        break;
    case 3:
        m17c = (g_1485720 - dt) * m17c;
        break;
    case 4:
        m17c = (dt + g_1485720) * m17c;
        break;
    case 5: {
        g_169de85 = 1;
        float e = (float)exp((double)(dt / g_15827ec) * (double)-0.30103f);
        float v = (m20C - m178) * (1.0f - e) + m178;
        m178 = Clamp(v, m208, m20C);
        break;
    }
    case 6: {
        g_169de85 = 1;
        float e = (float)exp((double)(dt / g_15827ec) * (double)-0.30103f);
        float v = (m208 - m178) * (1.0f - e) + m178;
        m178 = Clamp(v, m208, m20C);
        break;
    }
    case 7: {
        bool bl = true;
        if ((g_169df74 & 1) == 0) {
            g_169df74 |= 1;
            g_169df70 = g_158280c;
        }
        float theta = m174;
        float g = FUN_005b4f20(-theta);
        float v = g_169df70 * dt;
        float cl = Clamp(g, -v, v);
        if (fabsf(cl) <= g_147a31c) {
            m174 = 0.0f;
        } else {
            m174 = cl + theta;
            bl = false;
        }
        float dx = m114.x - m48.x;
        float dy = m114.y - m48.y;
        float dz = m114.z - m48.z;
        float dist = sqrtf((dx * dx + dz * dz) + dy * dy);
        float d2 = FUN_00d20620(dist);
        float hi = m20C * dt;
        float lo2 = -(fabsf(m208) * dt);
        float c2 = Clamp(d2 - m178, lo2, hi);
        if (fabsf(c2) <= g_147a31c) {
            m178 = d2;
        } else {
            m178 = c2 + m178;
            bl = false;
        }
        m38 = mB8;
        if (bl)
            mI1E8 = 0;
        break;
    }
    }

    if (((m2bc >> 18) & 1) == 0 || ((m2bc >> 17) & 1) == 0)
        m17c = Clamp(m17c, m210, m214);
    else
        m17c = Clamp(m17c, m220, g_147a2fc);

    bool rev = mCamReverse;
    bool changed = (mb104 != rev);
    mb105 = changed;
    mb104 = rev;

    IGameInputManager* im = GameInputManager();
    if (im != 0) {
        if (mb2b1) {
            if (im->IsKeyDown(1) || im->IsKeyDown(2)) {
                if (!mb315) {
                    mb2b4 = false;
                    mb2b1 = false;
                }
            }
            mb2b2 = true;
        }
        mb2b3 = true;
        mb2b4 = true;
        if (mb314)
            g_169de85 = 1;
    }

    if (mI1EC >= 0) {
        if (mI1EC <= 1) {
            UpdateCamera_StandardControl(dt);
        } else if (mI1EC == 2) {
            FUN_00d28300(dt);
            return;
        }
    }
}

}  // namespace SP
