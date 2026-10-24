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

extern "C" void __cdecl FUN_00f47380(void* pBuffer);   // 0x00f47380 operator delete

class IConfiguration;

// EA::Audio::ResponseCurve (0x364 bytes): 13-entry inline array at +0, spill buffer at +0x10
struct ResponseCurve {
    ResponseCurve();                               // 0x00a1aa50 thiscall
    ~ResponseCurve() { if (mpBegin != 0 && mpBegin != mpCapacity) FUN_00f47380(mpBegin); }
    bool InitFromConfiguration(IConfiguration* pConfig, uint32_t tag);   // 0x00a1a9d0 thiscall ret 8
    float GetOutputValue(float x);                 // 0x00a1a110
    bool GetMinInput(float* out);                  // 0x00a1a1c0
    bool GetMaxInput(float* out);                  // 0x00a1a1a0
    void*    mpBegin;                              // +0x00
    void*    mpEnd;                                // +0x04
    uint32_t m08;                                  // +0x08
    uint32_t m0c;                                  // +0x0c
    void*    mpCapacity;                           // +0x10
    uint32_t m14;                                  // +0x14
    uint8_t  pad18[0x364 - 0x18];                  // +0x18
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
class IHandler;
struct MessageServer {
    virtual void pad0() {} virtual void pad1() {} virtual void pad2() {} virtual void pad3() {}
    virtual void pad4() {}
    virtual void Post(uint32_t id, const void* msg, int flag);   // slot 5 (+0x14)
    virtual void pad6() {} virtual void pad7() {} virtual void pad8() {}
    virtual void AddHandler(IHandler* pHandler, uint32_t id);    // slot 9 (+0x24)
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

// reference-counted base: vtable at +0x00, count at +0x04
class cRefCountBase {
public:
    virtual void Release();
    virtual ~cRefCountBase() {}
    int32_t mRefCount;                             // +0x04
    cRefCountBase() : mRefCount(0) {}
};

// message handler base at +0x08
class IHandler {
public:
    virtual bool HandleMessage(uint32_t id, void* pMsg);   // 0x00a3c830
    virtual ~IHandler() {}
};

class cListener : public cRefCountBase, public IHandler {
public:
    cListener();                                   // 0x00a3c970
    bool Init();                                   // 0x00a3c710
    void ReadTuningValues();                       // 0x00a3c5a0
    void SetTuningId(uint32_t id);                 // 0x00a3c800
    uint32_t mTuningId;                            // +0x0c
    uint32_t mPendingId;                           // +0x10
    bool mbStaticMic;                              // +0x14
    bool mbEnableBoom;                             // +0x15
    uint8_t pad16[2];                              // +0x16
    ResponseCurve mCurveBoom;                      // +0x18
    ResponseCurve mCurveOffset;                    // +0x37c
    V3 mListenerOffset;                            // +0x6e0
    V3 mListenerPosition;                          // +0x6ec
    M33 mListenerMatrix;                           // +0x6f8
    V3 mCellMicrophonePos;                         // +0x71c
    V3 mAnchorPos;                                 // +0x728
    ResponseCurve* CurveBoom() { return &mCurveBoom; }
    ResponseCurve* CurveOffset() { return &mCurveOffset; }
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

// ---------------------------------------------------------------------------------
// tuning / message plumbing
// ---------------------------------------------------------------------------------

extern "C" void* __cdecl FUN_00f473a0(uint32_t nSize, const char* pName,
                                      int32_t a1, int32_t a2, int32_t a3, int32_t a4);  // 0x00f473a0 operator new

// AutoRefCount<T>: one reference-counted pointer, released on destruction
template <class T>
class AutoRefCount {
public:
    T* mpPtr;                                      // +0x00
    AutoRefCount() : mpPtr(0) {}
    ~AutoRefCount() { if (mpPtr) { T* p = mpPtr; mpPtr = 0; p->Release(); } }
    T* operator->() const { return mpPtr; }
};

// audio configuration object handed out by the audio system
class IConfiguration {
public:
    virtual void v00();
    virtual void Release();                                                   // slot 1 (+0x04)
    virtual void v08() {} virtual void v0c() {} virtual void v10() {}
    virtual void GetConfiguration(uint32_t id, AutoRefCount<IConfiguration>* pOut, uint32_t tag);  // +0x14
    virtual bool GetBool(uint32_t id);                                        // +0x18
    virtual void v1c() {} virtual void v20() {}
    virtual void SetPointer(uint32_t id, void* pValue);                       // +0x24
    virtual void v28() {} virtual void v2c() {} virtual void v30() {} virtual void v34() {}
    virtual void v38() {} virtual void v3c() {} virtual void v40() {}
    virtual bool QueryValue(uint32_t id, void* pOutA, void* pOutB);           // +0x44
};

namespace EA { namespace Audio {
struct IAudioSystem {
    virtual void v00() {} virtual void v04() {} virtual void v08() {}
    virtual void v0c() {} virtual void v10() {}
    virtual void GetConfiguration(uint32_t id, AutoRefCount<IConfiguration>* pOut, uint32_t tag);  // +0x14
};
IAudioSystem* GetSystemAT();                       // 0x00a206f0
}}

// payload of the cell microphone message (one value every 8 bytes)
struct cMicrophoneMessage {
    uint32_t mA;                                   // +0x00
    uint32_t mB;                                   // +0x04
    float    mX;                                   // +0x08
    uint32_t mXTag;                                // +0x0c
    float    mY;                                   // +0x10
    uint32_t mYTag;                                // +0x14
    float    mZ;                                   // +0x18
    uint32_t mZTag;                                // +0x1c
};

namespace EA { namespace IO {
struct IWriter;
struct IReader;
void WriteUint32(IWriter* pWriter, const void* pValue, int32_t nCount, int32_t nFlags);   // 0x0093aa70
void ReadInt32(IReader* pReader, void* pValue, int32_t nCount, int32_t nFlags);           // 0x0093a780
}}

// Swarm::MapDescription record (vtable 0x01453948), 0x14 bytes
struct cMapDescription {
    void*    mpVt00;                               // +0x00
    uint32_t m04;                                  // +0x04
    uint32_t m08;                                  // +0x08
    float    m0c;                                  // +0x0c
    float    m10;                                  // +0x10
};

// @ 0x00a3c5a0
void cListener::ReadTuningValues()
{
    mListenerOffset = V3(0.0f, 0.0f, 0.0f);
    mbStaticMic = false;
    mbEnableBoom = false;
    if (mTuningId == 0)
        return;
    AutoRefCount<IConfiguration> cfg;
    EA::Audio::IAudioSystem* pSystem = EA::Audio::GetSystemAT();
    pSystem->GetConfiguration(mTuningId, &cfg, 0x21407ee);
    if (cfg.mpPtr) {
        cfg->SetPointer(0xfd5197b0, &mbStaticMic);
        uint32_t nPad = 0;
        float* pValue = 0;
        if (cfg->QueryValue(0x64d7be3c, &nPad, &pValue))
            mListenerOffset = *(const V3*)pValue;
        mCurveOffset.InitFromConfiguration(cfg.mpPtr, 0xb0f0b4a5);
        bool bBoom = false;
        if (!mbStaticMic)
            bBoom = cfg->GetBool(0x16074fa6);
        mbEnableBoom = bBoom;
        if (bBoom)
            mCurveBoom.InitFromConfiguration(cfg.mpPtr, 0x16074fa6);
    }
}

// @ 0x00a3c710
bool cListener::Init()
{
    MessageServer* pServer = GetMessageServer();
    if (pServer) {
        pServer->AddHandler(this, 0x02b0c259);
        pServer->AddHandler(this, 0x022d1adc);
        pServer->AddHandler(this, 0x0248975f);
        pServer->AddHandler(this, 0x02489766);
        pServer->AddHandler(this, 0x0248976a);
        pServer->AddHandler(this, 0x052d9bab);
        pServer->AddHandler(this, 0x0539a4ce);
        pServer->AddHandler(this, 0x0539a4cf);
    }
    ReadTuningValues();
    return true;
}

// @ 0x00a3c800
void cListener::SetTuningId(uint32_t id)
{
    uint32_t nOld = mTuningId;
    if (id == nOld)
        return;
    if (nOld == 0x96ccccb8) {
        mPendingId = id;
        return;
    }
    mPendingId = nOld;
    mTuningId = id;
    ReadTuningValues();
}

// @ 0x00a3c830
bool IHandler::HandleMessage(uint32_t id, void* pMsg)
{
    cListener& listener = static_cast<cListener&>(*this);
    if (id == 0x052d9bab) {
        const cMicrophoneMessage* pMic = (const cMicrophoneMessage*)pMsg;
        listener.mCellMicrophonePos = V3(pMic->mX, pMic->mY, pMic->mZ);
        return true;
    }
    if (id == 0x02b0c259) {
        listener.ReadTuningValues();
        return true;
    }
    uint32_t nCurrent = listener.mTuningId;
    uint32_t nNew = nCurrent;
    if (id > 0x0248976a) {
        if (id == 0x0539a4ce)
            nNew = 0x96ccccb8;
        else if (id == 0x0539a4cf)
            nNew = listener.mPendingId;
    } else if (id == 0x0248976a) {
        nNew = 0x12ef46b8;
    } else if (id == 0x022d1adc) {
        switch (*(const uint32_t*)((const uint8_t*)pMsg + 8)) {
        case 0x01654c00: nNew = 0xbba5a414; break;
        case 0x01654c01: nNew = 0x1f401827; break;
        case 0x01654c02: nNew = 0x13a11a34; break;
        case 0x01654c04: nNew = 0xa21a6196; break;
        case 0x01654c10: nNew = 0xdb193f1e; break;
        case 0x02ccd1d2: nNew = 0x12ef46b8; break;
        }
    } else if (id == 0x0248975f) {
        nNew = 0x608310c6;
    } else if (id == 0x02489766) {
        nNew = 0xa602a723;
    }
    if (nNew == nCurrent)
        return true;
    if (nCurrent == 0x96ccccb8 && id != 0x0539a4cf) {
        listener.mPendingId = nNew;
        return true;
    }
    listener.mPendingId = nCurrent;
    listener.mTuningId = nNew;
    listener.ReadTuningValues();
    return true;
}

// @ 0x00a3c970
cListener::cListener()
    : mTuningId(0), mPendingId(0), mbStaticMic(false), mbEnableBoom(false),
      mCellMicrophonePos(kZeroVec), mAnchorPos(kZeroVec)
{
}

// @ 0x00a3cac0
void FUN_00a3cac0(cMapDescription* pDesc, EA::IO::IWriter* pWriter)
{
    {
        uint32_t nValue = pDesc->m08;
        EA::IO::WriteUint32(pWriter, &nValue, 1, 0);
    }
    {
        float fValue = pDesc->m0c;
        EA::IO::WriteUint32(pWriter, &fValue, 1, 0);
    }
    {
        float fValue = pDesc->m10;
        EA::IO::WriteUint32(pWriter, &fValue, 1, 0);
    }
}

// @ 0x00a3cb20
cMapDescription* FUN_00a3cb20(EA::IO::IReader* pReader, int32_t nVersion)
{
    cMapDescription* pDesc;
    void* pMemory = FUN_00f473a0(0x14, "Swarm", 0, 0, 0, 0);
    if (pMemory != 0) {
        cMapDescription* pNew = (cMapDescription*)pMemory;
        pNew->m0c = 1.0f;
        pNew->m04 = 0;
        pNew->mpVt00 = (void*)0x01453948;
        pNew->m08 = 0;
        pNew->m10 = 0.0f;
        pDesc = pNew;
    } else {
        pDesc = 0;
    }
    EA::IO::ReadInt32(pReader, &pDesc->m08, 1, 0);
    EA::IO::ReadInt32(pReader, &pDesc->m0c, 1, 0);
    if (nVersion > 1)
        EA::IO::ReadInt32(pReader, &pDesc->m10, 1, 0);
    return pDesc;
}
