// SP::Audio::cListener::Update (0x00a3bc70): recompute the audio listener position/orientation
// from the camera (or the cell microphone/anchor when boom is enabled) and push it to the audio system.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct V3 { float x, y, z; V3() {} V3(const V3& o) : x(o.x), y(o.y), z(o.z) {} V3(float a, float b, float c) : x(a), y(b), z(c) {}
    V3 operator*(float s) const { return V3(x * s, y * s, z * s); }
    friend V3 operator*(float s, const V3& v) { return V3(s * v.x, s * v.y, s * v.z); }
    V3& operator+=(const V3& o) { x += o.x; y += o.y; z += o.z; return *this; } };
struct M33 { float m[9]; };

extern const V3 kZeroVec;                          // 0x0166eae0..e8
extern const V3 kAVec;                             // 0x0166ebf0..f8
extern const V3 kBVec;                             // 0x0166eba8..b0
extern const V3 kCVec;                             // 0x0166ebb8..c0
extern const float kTinyX;                         // 0x013eb960 (0.01f)
extern const float kOne;                           // 0x01485720 (1.0f)

union FloatBits { float f; uint32_t i; };

static inline bool IsDenormal(float f)
{
    FloatBits u; u.f = f;
    return (u.i & 0x7fffffff) - 1 < 0x7fffff;
}

bool IsFiniteFloat(float f);                       // 0x0059ab10 (cdecl, other TU)
static inline bool IsFiniteInline(float f)
{
    FloatBits u; u.f = f;
    return (u.i & 0x7fffffff) == 0 || ((u.i - 0x800000) & 0x7f800000) < 0x7f000000;
}
bool Vector3_NotEqual(const V3* a, const V3* b);   // 0x0041dd30 (cdecl)
V3* normalized_safe(V3* out, const V3* v);         // 0x00449c20 (cdecl)
bool Matrix33_NotEqual(const M33* a, const M33* b);// 0x0041dd90 (cdecl)
void Matrix33_Convert(M33* out, const M33* in);    // 0x0041ded0 (cdecl)

#define PAD(n) virtual void pad##n() {}

struct ResponseCurve {
    float GetOutputValue(float x);                 // 0x00a1a110
    bool GetMinInput(float* out);                  // 0x00a1a1c0
    bool GetMaxInput(float* out);                  // 0x00a1a1a0
};

struct AudioListenerSet {
    virtual void pad0() {} virtual void pad1() {} virtual void pad2() {}
    virtual void SetListener(int index, const V3* pos, const M33* m);   // slot 3
};
struct AudioSystem {
    virtual void pad0() {} virtual void pad1() {} virtual void pad2() {} virtual void pad3() {}
    virtual void pad4() {} virtual void pad5() {} virtual void pad6() {}
    virtual AudioListenerSet* GetListenerSet();    // slot 7 (+0x1c)
    virtual void pad8() {} virtual void pad9() {} virtual void pad10() {} virtual void pad11() {}
    virtual void pad12() {} virtual void pad13() {}
    virtual int GetMode();                         // slot 14 (+0x38)
};
struct MessageServer {
    virtual void pad0() {} virtual void pad1() {} virtual void pad2() {} virtual void pad3() {}
    virtual void pad4() {}
    virtual void Post(uint32_t id, const void* msg, int flag);   // slot 5 (+0x14)
};
struct CamObj2 {
    virtual void p0() {} virtual void p1() {} virtual void p2() {} virtual void p3() {} virtual void p4() {}
    virtual void p5() {} virtual void p6() {} virtual void p7() {} virtual void p8() {} virtual void p9() {}
    virtual void p10() {} virtual void p11() {} virtual void p12() {} virtual void p13() {}
    virtual void p14() {} virtual void p15() {} virtual void p16() {} virtual void p17() {} virtual void p18() {}
    virtual void p19() {} virtual void p20() {}
    virtual V3* GetPosition(V3* tmp);              // slot 21 (+0x54)
};
struct CamObj1 {
    virtual void p0() {} virtual void p1() {} virtual void p2() {} virtual void p3() {} virtual void p4() {}
    virtual void p5() {} virtual void p6() {} virtual void p7() {} virtual void p8() {} virtual void p9() {}
    virtual void p10() {} virtual void p11() {} virtual void p12() {} virtual void p13() {}
    virtual CamObj2* GetSub();                     // slot 14 (+0x38)
};
static __forceinline bool IsBadFloatExt(float f)
{
    FloatBits u; u.f = f;
    return !IsFiniteFloat(u.f) && !IsDenormal(u.f);
}
struct App {
    virtual void p0() {} virtual void p1() {} virtual void p2() {} virtual void p3() {} virtual void p4() {}
    virtual void p5() {} virtual void p6() {} virtual void p7() {} virtual void p8() {} virtual void p9() {}
    virtual void p10() {} virtual void p11() {} virtual void p12() {} virtual void p13() {}
    virtual void* GetCurrentMode();                // slot 14 (+0x38)
    virtual void p15() {} virtual void p16() {} virtual void p17() {} virtual void p18() {} virtual void p19() {}
    virtual CamObj1* GetCamera();                  // slot 20 (+0x50)
};
App* GetApp();                                     // 0x0067dd10
MessageServer* GetMessageServer();                 // 0x0067dcc0
AudioSystem* GetAudioSystem();                     // 0x0067cb00

struct cViewer {
    void GetCameraLocationInfo(V3* pos, V3* a, V3* b, V3* c);   // 0x007c3d30
};

struct cListener {
    uint32_t pad0[5];
    bool mbStaticMic;                              // +0x14
    bool mbEnableBoom;                             // +0x15
    char pad16[2];
    char mCurveBoomDistanceBuf[0x37c - 0x18];      // +0x18 ResponseCurve
    char mCurveListenerOffsetBuf[0x6e0 - 0x37c];   // +0x37c ResponseCurve
    V3 mListenerOffset;                            // +0x6e0
    V3 mListenerPosition;                          // +0x6ec
    M33 mListenerMatrix;                           // +0x6f8
    V3 mCellMicrophonePos;                         // +0x71c
    V3 mAnchorPos;                                 // +0x728
    ResponseCurve* CurveBoom() { return (ResponseCurve*)mCurveBoomDistanceBuf; }
    ResponseCurve* CurveOffset() { return (ResponseCurve*)mCurveListenerOffsetBuf; }
    void Update(cViewer* viewer);
};

// @ 0x00a3bc70
void cListener::Update(cViewer* viewer)
{
    App* app = GetApp();
    if (!app)
        return;
    V3 camPos(kZeroVec);
    V3 p(kZeroVec);
    V3 vA(kAVec);
    V3 vB(kBVec);
    V3 vC(kCVec);
    if (mbStaticMic) {
        p = mListenerOffset;
        camPos = p;
    } else {
        viewer->GetCameraLocationInfo(&camPos, &vA, &vB, &vC);
        p = camPos;
        if (!IsFiniteInline(camPos.x) && !IsDenormal(camPos.x)) return;
        if (!IsFiniteInline(camPos.y) && !IsDenormal(camPos.y)) return;
        if (!IsFiniteInline(camPos.z) && !IsDenormal(camPos.z)) return;
        if (mbEnableBoom) {
            void* mode = app->GetCurrentMode();
            if (mode == (void*)0x1654c00) {
                mAnchorPos = mCellMicrophonePos;
            } else {
                V3 tmp;
                V3* r = app->GetCamera()->GetSub()->GetPosition(&tmp);
                mAnchorPos = *r;
            }
            if (IsBadFloatExt(mAnchorPos.x)) return;
            if (IsBadFloatExt(mAnchorPos.y)) return;
            if (IsBadFloatExt(mAnchorPos.z)) return;
            p = mAnchorPos;
            bool boom = false;
            switch ((uint32_t)mode) {
            case 0x1654c01: case 0x1654c02: case 0x1654c04: case 0x1654c10:
                boom = true;
                break;
            case 0x1654c05:
                boom = GetAudioSystem()->GetMode() == 1;
                break;
            }
            if (Vector3_NotEqual(&camPos, &mAnchorPos)) {
                V3 nrm;
                V3 dir(boom ? *normalized_safe(&nrm, &mAnchorPos) : vB);
                float dx = camPos.x - mAnchorPos.x;
                float dy = camPos.y - mAnchorPos.y;
                float dz = camPos.z - mAnchorPos.z;
                float dist = sqrtf((dz * dz + dy * dy) + dx * dx);
                float t = CurveBoom()->GetOutputValue(dist);
                p += dir * t;
                float lo, hi;
                CurveBoom()->GetMinInput(&lo);
                CurveBoom()->GetMaxInput(&hi);
                if (lo != hi) {
                    float u;
                    if (lo > dist) u = 0.0f;
                    else if (dist > hi) u = kOne;
                    else u = (dist - lo) / (hi - lo);
                    float w = CurveOffset()->GetOutputValue(u);
                    float o = mListenerOffset.x;
                    if (o != 0.0f) p += o * vC * w;
                    o = mListenerOffset.y;
                    if (o != 0.0f) p += o * vA * w;
                    o = mListenerOffset.z;
                    if (o != 0.0f) p += o * vB * w;
                }
            }
        } else {
            float o = mListenerOffset.x;
            if (o != 0.0f) p += o * vC;
            o = mListenerOffset.y;
            if (o != 0.0f) p += o * vA;
            o = mListenerOffset.z;
            if (o != 0.0f) p += o * vB;
        }
    }
    M33 conv;
    bool changed = false;
    {
        M33 m;
        m.m[0] = vC.x; m.m[1] = vC.y; m.m[2] = vC.z;
        m.m[3] = vA.x; m.m[4] = vA.y; m.m[5] = vA.z;
        m.m[6] = vB.x; m.m[7] = vB.y; m.m[8] = vB.z;
        if (p.x == 0.0f && p.y == 0.0f && p.z == 0.0f)
            p.x = kTinyX;
        if (p.x != mListenerPosition.x || p.y != mListenerPosition.y || p.z != mListenerPosition.z
            || Matrix33_NotEqual(&m, &mListenerMatrix)) {
            mListenerMatrix = m;
            mListenerPosition = p;
            Matrix33_Convert(&conv, &m);
            changed = true;
        }
    }
    if (changed) {
        MessageServer* ms = GetMessageServer();
        if (ms) {
            struct { V3 pos; M33 mat; } msg;
            msg.pos = p;
            msg.mat = conv;
            ms->Post(0x20c089c, &msg, 0);
        }
        AudioListenerSet* ls = GetAudioSystem()->GetListenerSet();
        ls->SetListener(0, &p, &conv);
        ls->SetListener(1, &camPos, &conv);
    }
}
