// src/game/SPAudio/_at_00a30000.cpp -- migrated from slice(s) s00a3ec00, s00a3cbb0, s00a3bc70, s00a3af80, s00a37dd0, s00a36d60, s00a35d20, s00a34e80, s00a33ee0 by tools/migrate/rewrite.py
// Object file: SPAudio/_at_00a30000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <math.h>
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"
#include "SP/Audio/cEAPDVoiceManager.h"
#include "EA/Audio/Command.h"
#include "EA/Audio/IConfiguration.h"
#include "SP/Audio/cEventModifierPrimitive.h"
#include "SP/Audio/cListener.h"
#include "EA/Audio/System.h"
#include "SP/cViewer.h"

// ---- items of slice s00a33ee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
struct PlugInDescRunTime_s00a3_3ee0 { char pad[0x28]; uint32_t guid; };   // guid at +0x28
}
}
}
namespace rw {
namespace audio {
namespace core {
struct PlugInConfig_s00a3_3ee0 {
    void* pConstructorParams;
    PlugInDescRunTime_s00a3_3ee0* plugInHandle;
    uint8_t outputChannels;
};
}
}
}
namespace rw {
namespace audio {
namespace core {
class Voice_s00a3_3ee0 { public: void Release(); };                               // 0x0112e950
}
}
}
namespace rw {
namespace audio {
namespace core {
class PlugIn_s00a3_3ee0 { public:
    char pad[0x10];
    PlugInDescRunTime_s00a3_3ee0* mpDesc;                                  // +0x10
    void Connect(int slot, void* value);                        // 0x0112ccc0
    bool GetAttribute(int attr, float* out);                    // 0x0112cc80
    bool SetAttribute(int attr, float value);                   // 0x0112ccf0
};
}
}
}
namespace EA {
namespace Audio {
struct tBinding_s00a3_3ee0 {
    uint32_t mProperty;     // +0
    uint32_t mPluginId;     // +4
    uint32_t mPluginGUID;   // +8
    int      mAttribute;    // +0xc
    float    mDefault;      // +0x10
    rw::audio::core::PlugIn_s00a3_3ee0*  mpPlugin;      // +0x14
    bool     mbFirst;       // +0x18
    float    mLast;         // +0x1c
    uint32_t mFlags;        // +0x20
};
}
}
namespace EA {
namespace Audio {
template<class T> struct RawVec {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
};
}
}
namespace EA {
namespace Audio {
struct VoiceContainer_s00a3_3ee0 {
    rw::audio::core::Voice_s00a3_3ee0*          mpVoice;                // +0
    rw::audio::core::PlugIn_s00a3_3ee0**        mppPlugins;             // +4
    RawVec<rw::audio::core::PlugInConfig_s00a3_3ee0> mChain;            // +8 (begin), +0xc (end), +0x10 (capacity)
    char            pad14[0x184 - 0x14];
    RawVec<tBinding_s00a3_3ee0> mBindings;             // +0x184 begin, +0x188 end, +0x18c capacity
    char            pad190[0x8a0 - 0x190];
    uint32_t*       mpSendBegin;            // +0x8a0
    uint32_t*       mpSendEnd;              // +0x8a4
    uint32_t*       mpSendCap;              // +0x8a8
    uint32_t*       pad8ac;
    uint32_t*       mpSendBuf;              // +0x8b0
    char            pad8b4[0x8cc - 0x8b4];
    uint32_t*       mpIdBegin;              // +0x8cc
    uint32_t*       mpIdEnd;                // +0x8d0
    uint32_t*       mpIdCap;                // +0x8d4
    uint32_t*       pad8d8;
    uint32_t*       mpIdBuf;                // +0x8dc
    char            pad8e0[0x95c - 0x8e0];
    bool            mbCreated;              // +0x95c
    bool            mbConnected;            // +0x95d
    char            pad95e[2];

    VoiceContainer_s00a3_3ee0();
    bool SetProperty(uint32_t prop, float value);  // 0x00a33ee0 (EA::Audio::VoiceContainer::SetProperty)
    bool GetProperty(uint32_t prop, float* out);  // 0x00a33fd0 (EA::Audio::VoiceContainer::GetProperty)
    void MaskPluginBindings(const uint32_t* props, int count);  // 0x00a340b0 (EA::Audio::VoiceContainer::MaskPluginBindings)
    int  FindPluginIndex(uint32_t guid);  // 0x00a341e0 (EA::Audio::VoiceContainer::FindPluginIndex)
    rw::audio::core::PlugIn_s00a3_3ee0* FindPlugin(uint32_t guid);  // 0x00a34230 (EA::Audio::VoiceContainer::FindPlugin)
    rw::audio::core::PlugIn_s00a3_3ee0* FindPluginIndexById(uint32_t id);  // 0x00a34260 (EA::Audio::VoiceContainer::FindPluginIndexById)
    bool Create(uint8_t flag);  // 0x00a342c0 (EA::Audio::VoiceContainer::Create)
    void Destroy();  // 0x00a343e0 (EA::Audio::VoiceContainer::Destroy)
    bool ConnectToMasteringVoice(rw::audio::core::PlugIn_s00a3_3ee0* plugin);  // 0x00a34440 (EA::Audio::VoiceContainer::ConnectToMasteringVoice)
    bool DisconnectFromMasteringVoice(rw::audio::core::PlugIn_s00a3_3ee0* plugin);  // 0x00a34530 (EA::Audio::VoiceContainer::DisconnectFromMasteringVoice)
    void DtorTail();
    bool DisconnectFromSubmix(uint32_t submixId, rw::audio::core::PlugIn_s00a3_3ee0* plugin);
    bool Disconnect();  // 0x00a34890 (EA::Audio::VoiceContainer::Disconnect)
    bool ConnectToSubmix(uint32_t submixId, rw::audio::core::PlugIn_s00a3_3ee0* plugin);  // 0x00a34b50 (EA::Audio::VoiceContainer::ConnectToSubmix)
    bool Connect();  // 0x00a21410 (EA::Audio::VoiceContainer::Connect)
    bool Reconnect();  // 0x00a34c90 (EA::Audio::VoiceContainer::Reconnect)
    bool AddPropertyBinding(uint32_t prop, uint32_t pluginId, uint32_t guid, int attr, const float* pDefault);
    void SetSendId(uint32_t id);
    bool HasPropertyBinding(uint32_t prop);  // 0x00a33e90 (EA::Audio::VoiceContainer::HasPropertyBinding)
};
}
}
struct U32Vec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity;
    void DoInsertValue(uint32_t* position, const uint32_t& value);   // FUN_00899480
    bool empty() const { return mpBegin == mpEnd; }
    uint32_t& back() { return mpEnd[-1]; }
    void push_back(const uint32_t& v) {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
namespace EA {
namespace Audio {
class Command_s00a3_3ee0 { public:
    uint32_t* EnumParameter(uint32_t* pOffset, uint32_t* pType, void* pUnused, int flags);   // 0x00a0f880
};
}
}
namespace SP {
namespace Audio {
class cEapdMessage { public:
    EA::Audio::Command_s00a3_3ee0* mpCommand;      // +0
    uint32_t mValue;                    // +4
    uint32_t mOffset;                   // +8
    uint32_t mCurrentOffset;            // +0xc
    bool Init(EA::Audio::Command_s00a3_3ee0* cmd);
    bool GetNextFloat(float* out);
};
}
}
// ---- items of slice s00a33ee0 end

// ---- items of slice s00a34e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
void* __cdecl EA_Audio_GetSystemAT(void);                    // 0x00a206f0
// ---- items of slice s00a34e80 end

// ---- items of slice s00a35d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
#define VFN(p, off) ((*(void***)(p))[(off) / 4])
namespace EA {
namespace Audio {
class PrimitiveAggregate_s00a3_5d20 { public:
    char pad[0x100];

    float CalculateAggregate();     // 0xa367a0
    bool  ShouldUpdate(u32 b);      // 0xa36750
    void  SetParam(float value, int param_3); // 0xa36990
};
}
}
// ---- items of slice s00a35d20 end

// ---- items of slice s00a36d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" char  g_gme_refcount;  // 0x013ef094  (GmeRefCount base)
extern "C" char  g_eapdTick_vtbl;   // 0x01453344
extern "C" char  g_eapdEmit_vtbl;   // 0x014532f8
extern "C" char  g_eapdRC_vtbl;     // 0x014532f0
extern "C" char  g_sound_vtbl;      // 0x0144934c
extern "C" char  g_eapdSound_vtbl1; // 0x01453e60
struct cEmitterEAPD {
    void* vtbl0;        // +0x00 ITickable
    void* vtbl1;        // +0x04 IEmitter
    void* vtbl2;        // +0x08 refcount
    int   mRefCount;    // +0x0c
    u32   mKey[3];      // +0x10
    u32   mhInstance;   // +0x1c
    void* mpPatch;      // +0x20
    u32   mId;          // +0x24
    u32   mGroupId;     // +0x28
    u32   mFlags;       // +0x2c
    u32   mConfig;      // +0x30
    u8    mPaused;      // +0x34

    cEmitterEAPD();                     // 0xa37b10
    u32  SetPropertyInternal(int a, float f); // 0xa379d0
    bool GetProperty(int key, float* out); // 0xa37930
    void Tick(int a, int b);            // 0xa37860
    ~cEmitterEAPD();                    // 0xa37c40
    bool Load();                        // 0xa37cc0
};
// ---- items of slice s00a36d60 end

// ---- items of slice s00a37dd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  g_01453470;        // 0x1453470 vtable
extern char  g_01453464;        // 0x1453464 vtable
extern char  g_01453460;        // 0x1453460 vtable
namespace EA {
namespace Audio {
class EmitterSndPlayer { public:
    EmitterSndPlayer();                                    // 0xa12d80
    char  Create();                                        // 0xa113c0
    bool  SetProperty(int id, float v, u32 b);             // 0xa116f0
    void  UpdateParameters(float a, u32 b);                 // 0xa11f50
};
}
}
namespace SP {
namespace Audio {
class cEmitterSndPlayer : public EA::Audio::EmitterSndPlayer { public:
    cEmitterSndPlayer();                                   // 0xa38d90
    bool Create();                                         // 0xa38dd0
    bool SetProperty(int id, float v, u32 b);              // 0xa38de0
    void UpdateParameters(float a, u32 b);                 // 0xa38e20
};
}
}
// ---- items of slice s00a37dd0 end

// ---- items of slice s00a3af80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define V  virtual void CAT(pad_, __COUNTER__)();
#define V4 V V V V
namespace SP {
struct IMessageServer {
    V4 V4 V V V
    virtual void Post(void* pPayload, uint32 nKey, int nParam); // slot 11 +0x2c
};
}
namespace SP {
IMessageServer* MessageServer();                                // 0x0067dcc0
}
struct cListener_s00a3_af80 {
    uint32 mPad0[2];    // +0x00 (EA::RefCountTemplate<int> then EA::Messaging::IHandler)
    bool Shutdown();    // 0x00a3bb60
};
// ---- items of slice s00a3af80 end

// ---- items of slice s00a3bc70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kTinyX;                         // 0x013eb960 (0.01f)
extern const float kOne;                           // 0x01485720 (1.0f)
extern "C" void __cdecl FUN_00f47380(void* pBuffer);   // 0x00f47380 operator delete
extern "C" void* __cdecl FUN_00f473a0(uint32_t nSize, const char* pName,
                                      int32_t a1, int32_t a2, int32_t a3, int32_t a4);  // 0x00f473a0 operator new
struct V3 { float x, y, z; V3() {} V3(const V3& o) : x(o.x), y(o.y), z(o.z) {} V3(float a, float b, float c) : x(a), y(b), z(c) {}
    V3 operator*(float s) const { return V3(x * s, y * s, z * s); }
    friend V3 operator*(float s, const V3& v) { return V3(s * v.x, s * v.y, s * v.z); }
    V3& operator+=(const V3& o) { x += o.x; y += o.y; z += o.z; return *this; } };
struct M33 { float m[9]; };
extern const V3 kZeroVec;                          // 0x0166eae0..e8
extern const V3 kAVec;                             // 0x0166ebf0..f8
extern const V3 kBVec;                             // 0x0166eba8..b0
extern const V3 kCVec;                             // 0x0166ebb8..c0
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
class IHandler_s00a3_bc70;
struct MessageServer_s00a3_bc70 {
    virtual void pad0() {} virtual void pad1() {} virtual void pad2() {} virtual void pad3() {}
    virtual void pad4() {}
    virtual void Post(uint32_t id, const void* msg, int flag);   // slot 5 (+0x14)
    virtual void pad6() {} virtual void pad7() {} virtual void pad8() {}
    virtual void AddHandler(IHandler_s00a3_bc70* pHandler, uint32_t id);    // slot 9 (+0x24)
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
MessageServer_s00a3_bc70* GetMessageServer();                 // 0x0067dcc0
AudioSystem* GetAudioSystem();                     // 0x0067cb00
struct cViewer {
    void GetCameraLocationInfo(V3* pos, V3* a, V3* b, V3* c);   // 0x007c3d30
};
class cRefCountBase {
public:
    virtual void Release();
    virtual ~cRefCountBase() {}
    int32_t mRefCount;                             // +0x04
    cRefCountBase() : mRefCount(0) {}
};
class cListener;
class IHandler_s00a3_bc70 {
public:
    virtual bool HandleMessage(uint32_t id, void* pMsg);   // 0x00a3c830
    virtual ~IHandler_s00a3_bc70() {}
    // the listener that owns this sub-object (IHandler sits at cListener+0x08)
    cListener* Listener() { return (cListener*)((char*)this - sizeof(cRefCountBase)); }
};
class cListener : public cRefCountBase, public IHandler_s00a3_bc70 {
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
    ResponseCurve_s00a3_bc70 mCurveBoom;                      // +0x18
    ResponseCurve_s00a3_bc70 mCurveOffset;                    // +0x37c
    V3 mListenerOffset;                            // +0x6e0
    V3 mListenerPosition;                          // +0x6ec
    M33 mListenerMatrix;                           // +0x6f8
    V3 mCellMicrophonePos;                         // +0x71c
    V3 mAnchorPos;                                 // +0x728
    ResponseCurve_s00a3_bc70* CurveBoom() { return &mCurveBoom; }
    ResponseCurve_s00a3_bc70* CurveOffset() { return &mCurveOffset; }
    void Update(cViewer* viewer);
};
template <class T>
class AutoRefCount {
public:
    T* mpPtr;                                      // +0x00
    AutoRefCount() : mpPtr(0) {}
    ~AutoRefCount() { if (mpPtr) { T* p = mpPtr; mpPtr = 0; p->Release(); } }
    T* operator->() const { return mpPtr; }
};
class IConfiguration_s00a3_bc70 {
public:
    virtual void v00();
    virtual void Release();                                                   // slot 1 (+0x04)
    virtual void v08() {} virtual void v0c() {} virtual void v10() {}
    virtual void GetConfiguration(uint32_t id, AutoRefCount<IConfiguration_s00a3_bc70>* pOut, uint32_t tag);  // +0x14
    virtual bool GetBool(uint32_t id);                                        // +0x18
    virtual void v1c() {} virtual void v20() {}
    virtual void SetPointer(uint32_t id, void* pValue);                       // +0x24
    virtual void v28() {} virtual void v2c() {} virtual void v30() {} virtual void v34() {}
    virtual void v38() {} virtual void v3c() {} virtual void v40() {}
    virtual bool QueryValue(uint32_t id, void* pOutA, void* pOutB);           // +0x44
};
namespace EA {
namespace IO {
struct IWriter;
}
}
namespace EA {
namespace IO {
struct IReader;
}
}
namespace EA {
namespace IO {
void WriteUint32(IWriter* pWriter, const void* pValue, int32_t nCount, int32_t nFlags);   // 0x0093aa70
}
}
namespace EA {
namespace IO {
void ReadInt32(IReader* pReader, void* pValue, int32_t nCount, int32_t nFlags);           // 0x0093a780
}
}
struct cMapDescription {
    void*    mpVt00;                               // +0x00
    uint32_t m04;                                  // +0x04
    uint32_t m08;                                  // +0x08
    float    m0c;                                  // +0x0c
    float    m10;                                  // +0x10
};
// ---- items of slice s00a3bc70 end

// ---- items of slice s00a3cbb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kMapGain;                      // 0x01485720 (default gain written by the MapDescription ctor)
extern char  PTR_FUN_01453998[];            // cCreatureAbility-derived vtable
extern char  PTR_FUN_014599e8[];            // override vtable
extern char  vtbl_GmeRefCount[];            // 0x013ef094  ??_7GmeRefCount@@6B@
extern int s_mixer, DAT_0166ee94, DAT_0166ee98, DAT_0166ee9c, spMixerClass;
void* operator new(unsigned int, const char*, int, int, int, int);
void* operator new(unsigned int, const char*, int, int, const char*, int);
void operator delete(void*);
void operator delete[](void*);
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
#define VP virtual void CAT(pad_, __COUNTER__)();
void SetGlobalProperty(int a, float b);
int  FNV1_String8(const char* s, unsigned seed, int flag);          // 0x00932e80
int  FUN_00a67d00(void);
void FUN_00a144c0(int* a, int* b);
void FUN_00fccdd0(int a);
void FUN_00a16fd0(int a);
int  FUN_00a17090(int n);
int  FUN_00a17100(int self);
struct PHTable {
    void FreeBuckets(int* buckets, unsigned n);
};
struct TrackCopy {
    void Reserve(int count, void* p);   // 0x00a3d4c0 (thiscall: this in ECX)
    int* CopyCtor(int* src);            // 0x00a3db50
};
bool eastl_hashtable_find(void* map, void* key);                    // 0x00645ed0
struct EObj;   // entry object destroyed by Mixer::Release (defined below)
namespace EA {
namespace ArgScript {
class cArguments_s00a3_cbb0 { public:
    int* MainArguments(int* outCount, int mn, int mx);   // 0x00838020
};
}
}
struct VtObj {
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // 0..15
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // 16..31
    VP VP VP VP VP VP                                   // 32..37
    virtual long double Slot38(const char* s);          // +0x98
};
namespace EA {
namespace Audio {
struct MixerObj {
    VP VP VP                                            // slots 0..2
    virtual void Slot3(int a, int b, int c);            // +0x0c
    VP                                                  // slot 4
    virtual void Slot5();                               // +0x14
    virtual void Slot6(int a);                          // +0x18
    virtual void Slot7(int a);                          // +0x1c
};
}
}
namespace EA {
namespace Audio {
struct SysObj {
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // slots 0..15
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // slots 16..31
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // slots 32..47
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP           // slots 48..61
    virtual int Slot62(int id);                         // +0xf8
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // slots 63..78
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP           // slots 79..92
    virtual MixerObj* Slot93(int x);                    // +0x174
};
}
}
namespace EA {
namespace Audio {
SysObj* GetSystemAT(void);                              // 0x00a206f0
}
}
namespace EA {
namespace Audio {
struct Mixer {
    char  pad0[4];
    int   m4;            // +0x04  (object passed to SysObj::Slot93)
    int   m8;            // +0x08
    int   mC;            // +0x0c
    int*  m10;           // +0x10  (track array)
    int   m14;           // +0x14  (track count)
    int   m18;           // +0x18  (active flag)
    char  pad1c[4];
    int*  mpBegin;       // +0x20  (entry list begin)
    int*  mpEnd;         // +0x24  (entry list end)
    int   m28;           // +0x28
    char  pad2c[4];
    int*  m30;           // +0x30
    int*  m34;           // +0x34
    char  pad38[4];
    int*  m3c;           // +0x3c
    void  Release();                                   // 0x00a3d150
    void  Command(int a, int b, int count, int* entries);  // 0x00a3cef0
    int   FindByIndex(int key);                        // 0x00a3d430
    int   FindByName(int key);                         // 0x00a3d480
};
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   pd_new(void* cls);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  freebytes(void* p, int n);
}
}
}
namespace EA {
namespace Hash {
int FNV1_String8(const char* s, unsigned seed, int flag);   // 0x00932e80
}
}
namespace EA {
namespace Swarm {
class cEffectsParser;
}
}
struct MapDescription {
    virtual void Dtor();     // slot 0 (scalar-deleting at vtable[0])
    int mRefCount;           // +0x04
    unsigned mHash;          // +0x08
    float mGain;             // +0x0c
    float mField;            // +0x10
    MapDescription();
};
MapDescription::MapDescription() : mRefCount(0), mHash(0), mGain(kMapGain), mField(0.0f) {}
namespace EA {
namespace Swarm {
class cEffectsParser { public:
    void AddAnonDescription(ArgScript::cArguments_s00a3_cbb0* args, int id, MapDescription* d, int flags);   // 0x00a6fd40
};
}
}
struct EObj {
    VP VP VP VP VP
    virtual void Slot5();          // +0x14
    virtual int  Slot6(int a);     // +0x18
};
typedef void (__thiscall *DelDtorFn)(void*, int);
inline char* VT(int obj) { return *(char**)obj; }
struct cMixEventInlineCommand {
    char pad0[4];
    VtObj* mpValueProvider;                 // +0x04
    char pad8[4];
    EA::Swarm::cEffectsParser* mpParser;    // +0x0c
    void Execute(EA::ArgScript::cArguments_s00a3_cbb0* args);   // 0x00a3cbb0
};
struct MixEnableCtx {
    char    pad0[0xc];
    int     mObj;      // +0x0c
    float   mOn;       // +0x10
    float   mOff;      // +0x14
    uint8_t mState;    // +0x18
    void Enable(int arg);     // 0x00a3cdf0
    void Disable(int arg);    // 0x00a3ce10
};
struct TeString {
    void* mpBegin;     // +0x00
    void* mpEnd;       // +0x04
    void* mpCapacity;  // +0x08
    void RangeInitialize(const char* s);   // 0x0057cc10
    ~TeString();                            // external
};
struct TrackVec {
    int* mpBegin;    // +0x00
    int* mpEnd;      // +0x04
    int* mpCapacity; // +0x08
    char padC[8];
    int  m14;        // +0x14
    TeString mStr;   // +0x18
    TrackVec* Ctor(int a, const char* b);         // 0x00a3d630
    void DoInsertValue(int* pos, int* value);     // 0x00a3d6e0
    void Erase(int* a, int* b);                   // 0x011e0744 (eastl vector erase)
    void Dtor();                                  // 0x00a3d690
};
// ---- items of slice s00a3cbb0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
int** FUN_00a3d810(int** out, int* first, int* last, int dst, int* src);  // 0x00a3d810 (stays in the slice: not this object's)

// ---- items of slice s00a3ec00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float _DAT_01485720;               // 0x01485720  1.0f
extern int  spSendGameClass;              // 0x0166eeec
extern int  DAT_0167589c, DAT_016758c4, DAT_01675894, DAT_016758ac;
extern int  DAT_0167545c;                 // 0x0167545c  outlet nesting guard
extern int  DAT_0166ef04;                 // 0x0166ef04  "shuffler" symbol
extern int  DAT_0166ef34;                 // 0x0166ef34  "rythm" symbol
extern int  DAT_0166ef2c, DAT_0166ef30;   // 0x0166ef2c / 0x0166ef30 list selector symbols
extern char DAT_040fdf2f[];               // 0x040fdf2f  debug format
extern char DAT_040fdfd9[];               // 0x040fdfd9
extern char DAT_040fe010[];               // 0x040fe010
extern char DAT_040fdffb[];               // 0x040fdffb
extern "C" void* __cdecl MemCopyRange(void* dst, const void* src, unsigned n);  // 0x011e0744 (memcpy thunk)
namespace EA {
namespace Audio {
namespace Eapd {
int   __cdecl symbolinlet_new(void* self, void* s);                                  // 0x00a49ab0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  __cdecl outlet_list(void* o, int a, int b, int n, void* list);                 // 0x00a49e40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  __cdecl outlet_bang(void* o);                                                  // 0x00a49da0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  __cdecl outlet_float(void* o, float f);                                        // 0x00a49570
}
}
}
bool  __cdecl KeyEq(const void* a, const void* b);                                   // 0x00555020 (eastl hashtable DoFindNode)
struct TeString_s00a3_ec00 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c
    void  Assign(char* first, char* last);   // 0x00454cb0
    void  RangeInit(int n);                  // 0x00475ab0 (eastl RangeInitialize)
    TeString_s00a3_ec00(const TeString_s00a3_ec00& s) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        int n = (int)(s.mpEnd - s.mpBegin);
        RangeInit(n + 1);
        MemCopyRange(mpBegin, s.mpBegin, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    ~TeString_s00a3_ec00() throw() {
        char* p = mpBegin;
        if (1 < (int)(mpCapacity - p) && p != 0) operator delete(p);
    }
};
struct tAtomVec {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    int   mA1;          // +0x0c
    int   mA2;          // +0x10
    tAtomVec() {}
    tAtomVec(const tAtomVec& s);         // 0x00a3d5b0 (vector<_atom> copy ctor)
    void CopyCtor(const tAtomVec& s);    // 0x00a3d5b0 (vector<_atom> copy ctor)
    void Assign(const tAtomVec& s);      // 0x00a6a6a0 (vector<_atom>::operator=)
};
struct tItem {          // 0x20 (3 dwords + vector<_atom>)
    u32 a, b, c;
    tAtomVec v;         // +0x0c
};
struct VecTItem {
    tItem* mpBegin;     // +0x00
    tItem* mpEnd;       // +0x04
    tItem* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    void DestroyItems(tItem* first, tItem* last);        // 0x00bdc770 (destroy range<tItem>)
    void Assign(const VecTItem& s);                      // 0x00a3e130 (vector<tItem>::operator=)
    void DoInsertAtom(tItem* pos, const tItem* value);   // 0x00a3f880
    void PushBackDefault();                              // 0x00a3fb00
    VecTItem(const VecTItem& s);                         // 0x00a3db50
    ~VecTItem() throw() {
        DestroyItems(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct TrackEntry {     // 0x24
    TeString_s00a3_ec00 mName;     // +0x00
    VecTItem mItems;    // +0x10
    TrackEntry(const TrackEntry& src);   // 0x00a3f5d0
    ~TrackEntry() throw();               // 0x00a3f3a0
};
struct VecTE {
    TrackEntry* mpBegin;    // +0x00
    TrackEntry* mpEnd;      // +0x04
    TrackEntry* mpCapacity; // +0x08
    int         mA1;        // +0x0c
    int         mA2;        // +0x10
    void DestroyRange(TrackEntry* first, TrackEntry* last);   // 0x00a3f520
    VecTE(const VecTE& src);                                  // 0x00a3fa50
    ~VecTE() throw() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct Track {          // 0x38
    TeString_s00a3_ec00 mName;     // +0x00
    VecTE    mShufflers;// +0x10
    VecTE    mRythms;   // +0x24
    Track(const Track& src);             // 0x00a3fb90
    ~Track() throw();                    // 0x00a3f770
};
struct TrackList {
    char    pad[0x20];
    Track*  mpBegin;     // +0x20
    Track*  mpEnd;       // +0x24
    Track*  FindByName(void* key);   // 0x00a3f050
};
struct Sys2 {
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 0..19
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 20..39
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 40..59
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 60..79
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 80..99
    VP VP VP VP VP VP VP                                          // 100..106
    virtual void* Slot1ac();                                      // +0x1ac
};
struct DbgCtx {
    void M_102e0(void* a);           // 0x00a102e0
    void M_10390(void* a, float f);  // 0x00a10390
    void M_103b0(void* a, int v);    // 0x00a103b0
    void M_0f940();                  // 0x00a0f940
};
// ---- items of slice s00a3ec00 end

// @ 0x00a34d70
void EA::Audio::VoiceContainer_s00a3_3ee0::SetSendId(uint32_t id)
{
    U32Vec* v = (U32Vec*)&mpSendBegin;
    if (v->empty()) {
        v->push_back(id);
        return;
    }
    v->back() = id;
}

// @ 0x00a34dc0
namespace SP { namespace Audio {
bool cEapdMessage::Init(EA::Audio::Command_s00a3_3ee0* cmd)
{
    bool ok0 = false;
    if (!cmd)
        return ok0;
    mOffset = 0;
    uint32_t type;
    void* unused;
    bool ok = false;
    uint32_t* p = cmd->EnumParameter(&mOffset, &type, &unused, 0);
    if (p && type == 0x40fdfd9) {
        mpCommand = cmd;
        mValue = *p;
        mCurrentOffset = mOffset;
        return true;
    }
    return ok;
}
}}  // namespace SP::Audio

// @ 0x00a34e80
void __fastcall FUN_00a34e80(int* self)
{
    *(int*)((char*)self + 0xc) = *(int*)((char*)self + 8);
}

// @ 0x00a34e90
int __cdecl FUN_00a34e90(void)
{
    char* p = (char*)EA_Audio_GetSystemAT();
    if (p != 0) {
        typedef int (__thiscall* Fn)(void*);
        return ((Fn)(*(void***)p)[0x24 / 4])(p);
    }
    return 0;
}

// @ 0x00a34eb0
void __fastcall FUN_00a34eb0(int* self)
{
    ((u8*)self)[0x27c] = (((u8*)self)[0x27c] == 0);
}

// @ 0x00a36750
namespace EA { namespace Audio {
bool PrimitiveAggregate_s00a3_5d20::ShouldUpdate(u32 b)
{
    char* self = (char*)this;
    if (*(bool*)(self + 0x50)) return true;
    if ((char)b != '\0') {
        void** begin = *(void***)(self + 0x10);
        void** end = *(void***)(self + 0x14);
        for (; begin != end; ++begin) {
            void* e = *begin;
            if (((bool(__thiscall*)(void*, u32))VFN(e, 0x20))(e, b)) return true;
        }
    }
    return *(bool*)(self + 0x50);
}
}}  // namespace EA::Audio

// @ 0x00a37b10
cEmitterEAPD::cEmitterEAPD()
{
    vtbl0 = &g_sound_vtbl;
    vtbl1 = &g_eapdSound_vtbl1;
    vtbl2 = &g_gme_refcount;
    _InterlockedExchange((volatile long*)&mRefCount, 0);
    vtbl0 = &g_eapdTick_vtbl;
    vtbl1 = &g_eapdEmit_vtbl;
    vtbl2 = &g_eapdRC_vtbl;
    mKey[0] = 0; mKey[1] = 0; mKey[2] = 0;
    mhInstance = 0;
    mpPatch = 0;
    mId = 0;
    mGroupId = 0;
    mFlags = 0;
    mConfig = 0;
    mPaused = 0;
}

// @ 0x00a38d90
SP::Audio::cEmitterSndPlayer::cEmitterSndPlayer()
{
    char* p = (char*)this;
    *(void**)(p + 0) = &g_01453470;
    *(void**)(p + 4) = &g_01453464;
    *(void**)(p + 8) = &g_01453460;
    *(u32*)(p + 0xe00) = 0;
    *(float*)(p + 0xe04) = 0.0f;
}

// @ 0x00a3bb60
bool cListener_s00a3_af80::Shutdown()
{
    SP::IMessageServer* pServer = SP::MessageServer();
    if (pServer) {
        pServer->Post(this ? (char*)this + 8 : 0, 0x2b0c259u, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x22d1adcu, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x248975fu, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x2489766u, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x248976au, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x52d9babu, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x539a4ceu, -9999);
        pServer->Post(this ? (char*)this + 8 : 0, 0x539a4cfu, -9999);
    }
    return true;
}

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
        MessageServer_s00a3_bc70* ms = GetMessageServer();
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

// @ 0x00a3cbb0
void cMixEventInlineCommand::Execute(EA::ArgScript::cArguments_s00a3_cbb0* args)
{
    int count;
    int* a = args->MainArguments(&count, 1, 3);
    if (!a) return;
    MapDescription* d = (MapDescription*)::operator new(0x14, "Swarm", 0, 0, 0, 0);
    if (d) new (d) MapDescription();
    if (d) d->mRefCount++;
    d->mHash = FNV1_String8((const char*)a[0], 0x811c9dc5, 1);
    if (count > 1)
        d->mGain = (float)mpValueProvider->Slot38((const char*)a[1]);
    if (count > 2)
        d->mField = (float)mpValueProvider->Slot38((const char*)a[2]);
    mpParser->AddAnonDescription(args, 0x2d, d, 0);
    if (--d->mRefCount == 0) {
        d->mRefCount = 1;
        ((DelDtorFn)(*(void***)d)[0])(d, 1);
    }
}

// @ 0x00a3cdf0
void MixEnableCtx::Enable(int arg)
{
    (void)arg;
    SetGlobalProperty(mObj, mOn);
    mState = 1;
}

// @ 0x00a3ce10
void MixEnableCtx::Disable(int arg)
{
    (void)arg;
    if (mState != 0) {
        SetGlobalProperty(mObj, mOff);
        mState = 0;
    }
}

// @ 0x00a3ce40
int* FUN_00a3ce40(int self)
{
    int* p = (int*)::operator new(0x1c, "Swarm", 0, 0, 0, 0);
    if (!p) return 0;
    p[1] = (int)(void*)vtbl_GmeRefCount;
    p[2] = 0;
    p[0] = (int)(void*)PTR_FUN_01453998;
    p[1] = (int)(void*)PTR_FUN_014599e8;
    p[3] = *(int*)(self + 8);
    *(float*)((char*)p + 0x10) = *(float*)(self + 0xc);
    *(uint8_t*)((char*)p + 0x18) = 0;
    *(float*)((char*)p + 0x14) = *(float*)(self + 0x10);
    return p;
}

// @ 0x00a3ced0
void FUN_00a3ced0(int self, int a, int b)
{
    int obj = *(int*)(*(int*)(self + 0x28) + 8);
    (*(void(__thiscall**)(void*, int, int, int))(VT(obj) + 0x14))((void*)obj, a, b, *(int*)(self + 0x28) + 4);
}

// @ 0x00a3cef0
void EA::Audio::Mixer::Command(int a, int b, int count, int* entries)
{
    if (count <= 0) return;
    for (int i = 0; i < count; i++, entries += 3) {
        int type = entries[0];
        if (type == 1) {
            int key = a;
            EA::Audio::SysObj* sys = EA::Audio::GetSystemAT();
            EA::Audio::MixerObj* mo;
            if (sys->Slot62(a) == 0) {
                sys = EA::Audio::GetSystemAT();
                mo = sys->Slot93(m4);
                if (mo) mo->Slot3(a, entries[1], 1);
            } else {
                if (eastl_hashtable_find((void*)((char*)this + 0xc), &key)) {
                    int obj = FUN_00a17090(0x1c);
                    if (obj) obj = FUN_00a17100((int)this);
                    if (obj) {
                        (*(void(__thiscall**)(int))VT(obj))(obj);
                    }
                    FUN_00fccdd0(a);
                    FUN_00a16fd0(key);
                    (*(void(__thiscall**)(int, int))(VT(obj) + 4))(obj, 0);
                    sys = EA::Audio::GetSystemAT();
                    mo = sys->Slot93(m4);
                    if (mo) mo->Slot6(a);
                }
            }
        } else if (type == 2) {
            int obj = m8;
            (*(void(__thiscall**)(int, int, int, int))(VT(obj) + 0x18))(obj, entries[1], entries[2], 0);
        }
    }
}

// @ 0x00a3d120
void FUN_00a3d120(int a1, int a2, int a3, int a4, int a5)
{
    ((EA::Audio::Mixer*)*(int*)(a1 + 0x28))->Command(a2, a3, a4, (int*)a5);
}

// @ 0x00a3d150
void EA::Audio::Mixer::Release()
{
    EA::Audio::SysObj* sys = EA::Audio::GetSystemAT();
    EA::Audio::MixerObj* mo = sys->Slot93(m4);
    if (mo) {
        int* p = m10;
        int first = *p;
        if (first == 0) {
            p++;
            first = *p;
            while (first == 0) { p++; first = *p; }
        }
        int last = *(int*)((char*)m10 + m14 * 4);
        while (first != last) {
            EObj* e = *(EObj**)(first + 4);
            e->Slot5();
            int v = e->Slot6((int)e);
            mo->Slot7(v);
            first = *(int*)(first + 8);
            while (first == 0) { p++; first = *p; }
        }
        ((PHTable*)((char*)this + 0xc))->FreeBuckets(m10, m14);
        m18 = 0;
    }
    ((PHTable*)((char*)this + 0xc))->FreeBuckets(m10, m14);
    int* v = m10;
    m18 = 0;
    if ((unsigned)m14 > 1 && v != m3c) {
        if (m30 <= v && v < m34) {
            *v = m28;
            m28 = (int)v;
            return;
        }
        operator delete[](v);
    }
}

// @ 0x00a3d2a0
int FUN_00a3d2a0(int a, int b, int c, int d)
{
    int r = EA::Audio::Eapd::pd_new((void*)spMixerClass);
    int* m = (int*)EA::Audio::Eapd::getbytes(0x444, "EAPd/Mixer");
    *(int**)(r + 0x28) = m;
    if (m) {
        *m = r;
        m[1] = 0;
        m[2] = FUN_00a67d00();
        FUN_00a144c0(&c, &c);
    } else {
        m = 0;
    }
    *(int**)(r + 0x28) = m;
    if (c == 1) {
        int obj = m[2];
        (*(void(__thiscall**)(int, int, int, int*))(VT(obj) + 0x14))(obj, *(int*)(d + 4), *(int*)(d + 8), m + 1);
    }
    return r;
}

// @ 0x00a3d360
void FUN_00a3d360(int self)
{
    ((EA::Audio::Mixer*)*(int*)(self + 0x28))->Release();
    EA::Audio::Eapd::freebytes(*(void**)(self + 0x28), 0x444);
}

// @ 0x00a3d430
int EA::Audio::Mixer::FindByIndex(int key)
{
    int p = (int)mpBegin;
    for (;;) {
        if (p == (int)mpEnd) return 0;
        if (*(int*)(p + 0x14) == key) break;
        p += 0x28;
    }
    return p;
}

// @ 0x00a3d480
int EA::Audio::Mixer::FindByName(int key)
{
    int a = (int)mpBegin;
    int b = (int)mpEnd;
    for (;;) {
        if (a == b) return 0;
        if (eastl_hashtable_find((void*)(a + 0x18), (void*)key)) break;
        a += 0x28;
    }
    return a;
}

// @ 0x00a3d690
void TrackVec::Dtor()
{
    void* i = mStr.mpBegin;
    if (1 < (int)((char*)mStr.mpCapacity - (char*)i) && i != 0) operator delete[](i);
    Erase(mpBegin, mpEnd);
    int b = (int)mpBegin;
    if (b != 0 && *(int*)(b - 4) != 0) operator delete[]((void*)b);
}

// @ 0x00a3db50
int* TrackCopy::CopyCtor(int* src)
{
    int* out = (int*)this;
    Reserve((src[1] - *src) >> 5, src + 3);
    FUN_00a3d810(&src, (int*)*src, (int*)src[1], *out, src);
    out[1] = (int)src;
    return out;
}

// @ 0x00a3eef0
int sendgame_new(int a, int b)
{
    int r = EA::Audio::Eapd::pd_new((void*)spSendGameClass);
    if (r) {
        int* p = (int*)(r + 0x28);
        p[0] = a;
        p[1] = b;
        EA::Audio::Eapd::symbolinlet_new((void*)r, (void*)p);
    }
    return r;
}

// @ 0x00a3ef30
void sendgame_anything(int self, int sym, int b, int argc, int* argv)
{
    (void)b;
    Sys2* sys = (Sys2*)EA::Audio::GetSystemAT();
    if (!sys) return;
    DbgCtx* d = (DbgCtx*)sys->Slot1ac();
    d->M_102e0(DAT_040fdf2f);
    if (DAT_0167589c == *(int*)(self + 0x28)) {
        d->M_103b0(DAT_040fdfd9, sym);
    } else {
        d->M_103b0(DAT_040fdfd9, *(int*)(self + 0x28));
        if (DAT_016758c4 != sym && DAT_01675894 != sym && DAT_016758ac != sym) {
            d->M_103b0(DAT_040fe010, sym);
        }
    }
    if (argc > 0) {
        int* it = argv + 1;
        int n = argc;
        do {
            if (it[-1] == 1)
                d->M_10390(DAT_040fdffb, *(float*)it);
            else
                d->M_103b0(DAT_040fe010, *it);
            it += 3;
        } while (--n != 0);
    }
    d->M_0f940();
}

// @ 0x00a3f050
Track* TrackList::FindByName(void* key)
{
    Track* p = mpBegin;
    Track* end = mpEnd;
    for (;;) {
        if (p == end) return 0;
        if (KeyEq(p, key)) break;
        p += 1;
    }
    return p;
}

// @ 0x00a3f090
void trixie_read(int self, int sym, int b, int argc, int* argv)
{
    (void)sym; (void)b;
    if (argc < 1) return;
    if (argc < 2) return;
    if (argv[0] != 2) return;
    if (argv[3] != 2) return;
    Track* tr = ((TrackList*)*(int*)(self + 0x28))->FindByName((void*)argv[2]);
    if (!tr) return;
    if (argc <= 2) {
        if (argv[4] == DAT_0166ef04) {
            u32 n = (u32)((int)((char*)tr->mShufflers.mpEnd - (char*)tr->mShufflers.mpBegin) / 0x24);
            float f = (float)n;
            int g = DAT_0167545c + 1;
            DAT_0167545c = g;
            if (g < 1000) {
                int* p = *(int**)(*(int*)(self + 0x2c) + 8);
                while (p) {
                    EA::Audio::Eapd::outlet_float((void*)p[1], f);
                    p = (int*)*p;
                }
            }
            DAT_0167545c = DAT_0167545c - 1;
            return;
        }
        if (argv[4] != DAT_0166ef34) return;
        {
            u32 n = (u32)((int)((char*)tr->mRythms.mpEnd - (char*)tr->mRythms.mpBegin) / 0x24);
            float f = (float)n;
            int g = DAT_0167545c + 1;
            DAT_0167545c = g;
            if (g < 1000) {
                int* p = *(int**)(*(int*)(self + 0x2c) + 8);
                while (p) {
                    EA::Audio::Eapd::outlet_float((void*)p[1], f);
                    p = (int*)*p;
                }
            }
            DAT_0167545c = DAT_0167545c - 1;
        }
        return;
    }
    int kind = argv[6];
    if (kind != 2 && kind != 1) return;
    TrackEntry* vec;
    if (argv[4] == DAT_0166ef04) vec = (TrackEntry*)((char*)tr + 0x10);
    else if (argv[4] == DAT_0166ef34) vec = (TrackEntry*)((char*)tr + 0x24);
    else return;
    int idx = 0;
    float fval = 0.0f;
    if (kind == 2) idx = argv[8];
    else fval = *(float*)&argv[7];
    TrackEntry* begin = (TrackEntry*)vec->mName.mpBegin;
    TrackEntry* end = (TrackEntry*)vec->mName.mpEnd;
    float acc = 0.0f;
    if (begin == end) return;
    for (;;) {
        if (idx != 0) {
            if (!KeyEq(begin, (void*)idx)) {
                acc = acc + _DAT_01485720;
                begin = (TrackEntry*)((char*)begin + 0x24);
                if (begin == end) return;
                continue;
            }
        } else {
            if (!(acc == fval)) {
                acc = acc + _DAT_01485720;
                begin = (TrackEntry*)((char*)begin + 0x24);
                if (begin == end) return;
                continue;
            }
        }
        break;
    }
    if (begin == 0) return;
    tItem* item = (tItem*)begin->mItems.mpBegin;
    tItem* itemEnd = (tItem*)begin->mItems.mpEnd;
    for (; item != itemEnd; item += 1) {
        EA::Audio::Eapd::outlet_list((void*)*(int*)(self + 0x2c), DAT_0166ef2c, DAT_0166ef30,
                                     (int)((char*)item->v.mpEnd - (char*)item->v.mpBegin) / 0xc,
                                     item->v.mpBegin);
    }
    EA::Audio::Eapd::outlet_bang((void*)*(int*)(self + 0x30));
}
