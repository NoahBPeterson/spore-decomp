// Object file: SPAudio/SPAudioListener.obj.  Types, members and virtual calls use the canonical headers under
// src/game/include; each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Audio/cListener.h"
#include "EA/Audio/System.h"
#include "EA/Audio/IConfiguration.h"
#include "EA/Audio/ResponseCurve.h"
#include "SP/cViewer.h"

// A 3-float vector as the listener stores it (offset/size only; the canonical type is cSPVector3).
struct V3 {
    float x, y, z;
    V3() {}
    V3(const V3& o) : x(o.x), y(o.y), z(o.z) {}
    V3(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct M33 { float m[9]; };
extern const V3 kZeroVec;                          // 0x0166eae0..e8

extern "C" void __cdecl FUN_00f47380(void* pBuffer);   // 0x00f47380 operator delete

// EA::Audio::ResponseCurve as the listener stores it: {begin, end, size, capacity, ...} (0x364 bytes retail).
class IConfiguration_s00a3_bc70;
struct ResponseCurve_s00a3_bc70 {
    ResponseCurve_s00a3_bc70();                               // 0x00a1aa50 thiscall
    ~ResponseCurve_s00a3_bc70() { if (mpBegin != 0 && mpBegin != mpCapacity) FUN_00f47380(mpBegin); }
    bool InitFromConfiguration(IConfiguration_s00a3_bc70* pConfig, uint32_t tag);   // 0x00a1a9d0 thiscall ret 8
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

// The process-wide EA::Messaging::Server, seen through the two slots cListener uses.
class IHandler_s00a3_bc70;
struct MessageServer {
    virtual void pad0() {} virtual void pad1() {} virtual void pad2() {} virtual void pad3() {}
    virtual void pad4() {}
    virtual void Post(uint32_t id, const void* msg, int flag);   // slot 5 (+0x14)
    virtual void pad6() {} virtual void pad7() {} virtual void pad8() {}
    virtual void AddHandler(IHandler_s00a3_bc70* pHandler, uint32_t id);    // slot 9 (+0x24)
};
MessageServer* GetMessageServer();                 // 0x0067dcc0

// SP::cViewer, only the camera readout cListener::Update uses.
struct cViewer {
    void GetCameraLocationInfo(V3* pos, V3* a, V3* b, V3* c);   // 0x007c3d30
};

// cListener's owning base: a refcount (vptr + count) at +0x00.
class cRefCountBase {
public:
    virtual void Release();
    virtual ~cRefCountBase() {}
    int32_t mRefCount;                             // +0x04
    cRefCountBase() : mRefCount(0) {}
};

// cListener's message handler sub-object (IHandler at cListener+0x08).
class cListener;
class IHandler_s00a3_bc70 {
public:
    virtual bool HandleMessage(uint32_t id, void* pMsg);   // 0x00a3c830
    virtual ~IHandler_s00a3_bc70() {}
    // the listener that owns this sub-object
    cListener* Listener() { return (cListener*)((char*)this - sizeof(cRefCountBase)); }
};

class cListener : public cRefCountBase, public IHandler_s00a3_bc70 {
public:
    cListener();                                   // 0x00a3c970
    bool Init();                                   // 0x00a3c710
    void ReadTuningValues();                       // 0x00a3c5a0
    void SetTuningId(uint32_t id);                 // 0x00a3c800
    uint32_t mTuningId;                            // +0x0c  (canonical mListenerTuningId)
    uint32_t mPendingId;                           // +0x10  (canonical mPrevListenerTuningId)
    bool mbStaticMic;                              // +0x14
    bool mbEnableBoom;                             // +0x15
    uint8_t pad16[2];                              // +0x16
    ResponseCurve_s00a3_bc70 mCurveBoom;                      // +0x18  (canonical mCurveBoomDistance)
    ResponseCurve_s00a3_bc70 mCurveOffset;                    // +0x37c (canonical mCurveListenerOffset)
    V3 mListenerOffset;                            // +0x6e0
    V3 mListenerPosition;                          // +0x6ec
    M33 mListenerMatrix;                           // +0x6f8
    V3 mCellMicrophonePos;                         // +0x71c
    V3 mAnchorPos;                                 // +0x728
    void Update(cViewer* viewer);
};

// The microphone-position message cListener::HandleMessage consumes.
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
bool IHandler_s00a3_bc70::HandleMessage(uint32_t id, void* pMsg)
{
    // IHandler is the sub-object at cListener+0x08; the original folds that -8 into its
    // member displacements and only re-adjusts ecx before the ReadTuningValues calls.
    if (id == 0x052d9bab) {
        const cMicrophoneMessage* pMic = (const cMicrophoneMessage*)pMsg;
        Listener()->mCellMicrophonePos.x = pMic->mX;
        Listener()->mCellMicrophonePos.y = pMic->mY;
        Listener()->mCellMicrophonePos.z = pMic->mZ;
        return true;
    }
    if (id == 0x02b0c259) {
        Listener()->ReadTuningValues();
        return true;
    }
    uint32_t nCurrent = Listener()->mTuningId;
    uint32_t nNew = nCurrent;
    switch (id) {
    case 0x022d1adc: {
        // the message carries a mode tag at +0x08
        const uint32_t nMode = *(const uint32_t*)((const uint8_t*)pMsg + 8);
        switch (nMode) {
        case 0x01654c00: nNew = 0xbba5a414; break;
        case 0x01654c01: nNew = 0x1f401827; break;
        case 0x01654c02: nNew = 0x13a11a34; break;
        case 0x01654c04: nNew = 0xa21a6196; break;
        case 0x01654c10: nNew = 0xdb193f1e; break;
        case 0x02ccd1d2: nNew = 0x12ef46b8; break;
        }
        break;
    }
    case 0x0248975f: nNew = 0x608310c6; break;
    case 0x02489766: nNew = 0xa602a723; break;
    case 0x0248976a: nNew = 0x12ef46b8; break;
    case 0x0539a4ce: nNew = 0x96ccccb8; break;
    case 0x0539a4cf: nNew = Listener()->mPendingId; break;
    }
    if (nNew == nCurrent)
        return true;
    if (nCurrent == 0x96ccccb8 && id != 0x0539a4cf) {
        Listener()->mPendingId = nNew;
        return true;
    }
    Listener()->mPendingId = nCurrent;
    Listener()->mTuningId = nNew;
    Listener()->ReadTuningValues();
    return true;
}

// @ 0x00a3c970
cListener::cListener()
: mTuningId(0), mPendingId(0), mbStaticMic(false), mbEnableBoom(false),
      mCellMicrophonePos(kZeroVec), mAnchorPos(kZeroVec)
{
}
