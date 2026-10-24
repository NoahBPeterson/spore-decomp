// Slice s00a41c40: SP::Audio sound/system object file (0xa41c40-0xa42c30).
//   cSound gain/commit/ctor/dtor, the SP::Audio cSystem startup helpers, the audio engine's
//   context/polyphony/property/update/command entry points, and two EAPD/audio thunks.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
//
// Retail layout notes (read off the disassembly; the dev PDB is too small to be trusted):
//   * cSound has THREE vtable pointers at +0x00/+0x04/+0x08 (a Sound base plus the curve-source
//     and a trivial third base), four EA::Audio::ResponseCurve members at +0x1e10/+0x2174/+0x24d8/
//     +0x283c, then +0x2ba0 int, +0x2ba4/+0x2ba5 bools and an eastl string at +0x2ba8 (sizeof 0x2bb8).
//   * the audio engine object (this of the PreInit/GetProperty/Update/... entry points) carries the
//     fields at +0x15bc38..+0x15bcec directly; SP::Audio::cSystem is the sub-object at +0x15bc18.
#include "types.h"
#include <math.h>

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();
#define VP2 VP VP
#define VP4 VP VP VP VP
#define VP8 VP4 VP4
#define VP16 VP8 VP8

void* operator new(unsigned int, const char*, int, int, const char*, int);
void* operator new(unsigned int);
void operator delete(void*);
void operator delete[](void*);

struct Vector3
{
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
};

struct CurveDesc;

extern const float kOne;        // 0x01485720
extern const float kZero;       // 0x01485378
extern const float kEpsilon;    // 0x013ec4b8
extern char gEmptyString16[];   // 0x01667bac
extern char PTR_FUN_013eb428[]; // 0x013eb428

// ---------------------------------------------------------------- stopwatch
union LARGE_INTEGER
{
    struct
    {
        unsigned int LowPart;   // +0x00
        int HighPart;           // +0x04
    };
    unsigned __int64 QuadPart;
};
unsigned __int64 GetStopwatchFrequency();                                   // 0x0093a470
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER*);

extern double gSecondsPerTick;      // 0x0166f398
extern LARGE_INTEGER gStart;        // 0x0166f3a0
extern int gTimerFlags;             // 0x0166f3a8

// ---------------------------------------------------------------- allocator
namespace EA {
namespace Audio {

class ResponseCurve
{
public:
    ResponseCurve();                                        // 0x00a1aa50
    ~ResponseCurve() throw();
    float GetOutputValue(float value) const;                // 0x00a1a110

    void* mpData;               // +0x00
    char mPad_04[0x0c];         // +0x04
    void* mpAllocation;         // +0x10
    char mPad_14[0x350];        // +0x14  (sizeof == 0x364)
};

ResponseCurve::~ResponseCurve() throw()
{
    if (mpData && mpData != mpAllocation)
        operator delete(mpData);
}

class Sound
{
public:
    Sound();                                                // 0x00a1fbb0
    virtual ~Sound();                                       // 0x00a1f4d0
    void CommitAllProperties();                             // 0x00a1d080
};

}   // namespace Audio
}   // namespace EA

// ---------------------------------------------------------------- eastl string
struct TeString
{
    const void* mpBegin;        // +0x00
    const void* mpEnd;          // +0x04
    const void* mpCapacity;     // +0x08

    TeString()
        : mpBegin(gEmptyString16),
          mpEnd(gEmptyString16),
          mpCapacity((char*)gEmptyString16 + 1)
    {
    }
    ~TeString() throw();
};

TeString::~TeString() throw()
{
    if ((const char*)mpCapacity - (const char*)mpBegin > 1 && mpBegin)
        operator delete((void*)mpBegin);
}

// ---------------------------------------------------------------- SP::Audio
namespace SP {
namespace Audio {

// The curve-source sub-object of cSound (its vtable sits at cSound + 4).
struct __declspec(novtable) CurveSource
{
    VP VP VP
    virtual void Slot0c(unsigned int id, float value, int flag);   // +0x0c
    virtual bool Slot10(unsigned int id, float* pOut);             // +0x10
};

// A trivial polymorphic third base of cSound (its vtable sits at cSound + 8).
struct __declspec(novtable) ThirdBase
{
    VP VP
};

class cSound : public EA::Audio::Sound, public CurveSource, public ThirdBase
{
public:
    static void* operator new(unsigned int size);           // 0x00a41cc0

    cSound();
    ~cSound();

    float ComputeGainAttenuation(float a, float b, float c, float d, float e);  // 0x00a41c40
    void CommitAllProperties();                             // 0x00a41d30

    char mPad_0c[0x44 - 0x0c];      // +0x0c
    void* mpObj44;                  // +0x44
    char mPad_48[0xce4 - 0x48];     // +0x48
    unsigned int mFlags;            // +0xce4
    char mPad_ce8[0x1e10 - 0xce8];  // +0xce8
    EA::Audio::ResponseCurve mCurve1e10;    // +0x1e10
    EA::Audio::ResponseCurve mCurve2174;    // +0x2174
    EA::Audio::ResponseCurve mCurve24d8;    // +0x24d8
    EA::Audio::ResponseCurve mCurve283c;    // +0x283c
    int mStartContext;              // +0x2ba0
    bool mb2ba4;                    // +0x2ba4
    bool mb2ba5;                    // +0x2ba5
    TeString mName;                 // +0x2ba8
    int mPad_2bb4;                  // +0x2bb4  (sizeof == 0x2bb8)
};

// @ 0x00a41ed0
cSound::cSound() : mStartContext(0), mb2ba4(0), mb2ba5(0)
{
}

// @ 0x00a41e10
cSound::~cSound()
{
}

// ---------------------------------------------------------------- engine vtable
// Only the slots this object file dispatches are named; the rest are the unnamed virtuals of the
// retail vtable (slot names are the retail byte offsets).
class cAudioSystem
{
public:
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP     // 0x00..0x34
    virtual void V38(unsigned int id);             // +0x38
    VP                                             // +0x3c
    virtual void V40(unsigned int id, int value);  // +0x40
    VP VP VP VP VP                                 // +0x44..0x54
    virtual void V58();                            // +0x58
    VP16 VP16 VP16 VP16                            // +0x5c..0x158
    virtual int V15c(int arg);                     // +0x15c

    // data (the vptr lives at +0, these follow it)
    char mPad_04[0x29 - 0x04];          // +0x04
    bool mbNoFocus;                     // +0x29
    char mPad_2a[0x60 - 0x2a];          // +0x2a
    void* mp60;                         // +0x60
    char mPad_64[0x94 - 0x64];          // +0x64
    bool mb94;                          // +0x94
    char mPad_95[0xa4 - 0x95];          // +0x95
    void* mpA4;                         // +0xa4
    char mPad_a8[0x128aec - 0xa8];      // +0xa8
    int mn128aec;                       // +0x128aec
    char mPad_128af0[0x132814 - 0x128af0];
    int mn132814;                       // +0x132814
    char mPad_132818[0x15bbe4 - 0x132818];
    Vector3 mCameraPos;                 // +0x15bbe4
    bool mb15bbf0;                      // +0x15bbf0
    char mPad_15bbf1[0x15bc38 - 0x15bbf1];
    void* mpCurrentContext;             // +0x15bc38
    int mn15bc3c;                       // +0x15bc3c
    unsigned char mb15bc40;             // +0x15bc40
    char mPad_15bc41[0x15bc42 - 0x15bc41];
    bool mb15bc42;                      // +0x15bc42
    char mPad_15bc43[0x15bc44 - 0x15bc43];
    Vector3 mV44;                       // +0x15bc44
    Vector3 mV50;                       // +0x15bc50
    Vector3 mV5c;                       // +0x15bc5c
    Vector3 mV68;                       // +0x15bc68
    void* mp15bc74;                     // +0x15bc74
    void* mp15bc78;                     // +0x15bc78
    char mPad_15bc7c[0x15bc80 - 0x15bc7c];
    void* mp15bc80;                     // +0x15bc80
    int mn15bc84;                       // +0x15bc84
    int mn15bc88;                       // +0x15bc88
    int mn15bc8c;                       // +0x15bc8c
    int mn15bc90;                       // +0x15bc90
    int mn15bc94;                       // +0x15bc94
    int mn15bc98;                       // +0x15bc98
    int mn15bc9c;                       // +0x15bc9c
    int mn15bca0;                       // +0x15bca0
    char mPad_15bca4[0x15bce4 - 0x15bca4];
    void* mp15bce4;                     // +0x15bce4
    char mPad_15bce8[0x15bcec - 0x15bce8];
    void* mp15bcec;                     // +0x15bcec
    char mPad_15bcf0[0x15bf24 - 0x15bcf0];
    int mn15bf24;                       // +0x15bf24

    bool PreInit(void* pCommandLine);                   // 0x00a42220
    void SetupTypePriorities();                         // 0x00a42310
    void SetTypePriority(unsigned int id, float value); // 0x00a42360
    int ResolveCurve(struct CurveDesc* d);              // 0x00a423a0
    void ResetCurveIds();                               // 0x00a424b0
    bool UpdateAndTestRunTimePolyphonyForSound(void* snd, int count);   // 0x00a424e0
    bool GetProperty(unsigned int id, float* out);      // 0x00a42640
    void SetCurrentContext(void* ctx);                  // 0x00a426f0
    int GetContextId();                                 // 0x00a42740
    void GetListenerVectors(Vector3* a, Vector3* b, Vector3* c, Vector3* d);   // 0x00a42750
    void RegisterModules();                             // 0x00a427e0
    void Update(float dt);                              // 0x00a428a0
    void CommandResolve(void* cmd);                     // 0x00a429a0
    bool OnEventModifier(void* cmd);                    // 0x00a42aa0
    float GetDistance(Vector3* p);                      // 0x00a42ad0
    bool RegisterHandler(unsigned int index, void* obj);    // 0x00a42c10
    bool UnregisterHandler(unsigned int index);             // 0x00a42c30

    // non-virtual callees (bodies outside this object file)
    bool Map_266e0(unsigned int id, float value);       // 0x00a266e0
    void Map_26530();                                   // 0x00a26530
    void UpdateInternal(float dt);                      // 0x00a25c40
    void RegisterBuiltInModules();                      // 0x00a21170
};

// The SP::Audio::cSystem sub-object lives at engine + 0x15bc18.
struct cSystem
{
    char mPad_00[0x29];             // +0x000
    bool mb29;                      // +0x029
    char mPad_2a[0x30c - 0x2a];     // +0x02a
    int mn30c;                      // +0x30c

    cAudioSystem* Engine() { return (cAudioSystem*)((char*)this - 0x15bc18); }
    void SetupContext();            // 0x00a422c0
};

// @ 0x00a422c0
void cSystem::SetupContext()
{
    cAudioSystem* pEngine = Engine();
    pEngine->V38(0x44888b0);
    pEngine->V40(0x34753a0, 1);
    pEngine->V58();
    mn30c = 0x14;
}

// @ 0x00a42350
cAudioSystem* cSystemEngine(cSystem* pThis)
{
    return (cAudioSystem*)((char*)pThis - 0x15bc18);
}

unsigned int StaticConvertSymbolToId(const char* name);     // 0x00a42200

}   // namespace Audio
}   // namespace SP

using SP::Audio::cAudioSystem;
using SP::Audio::cSound;
using SP::Audio::cSystem;

// ---------------------------------------------------------------- command line
namespace EA {
struct WString
{
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    void* mAlloc;           // +0x0c
};

struct CommandLine
{
    unsigned int FindSwitch(const wchar_t* pSwitch, bool exact, WString* pOut, unsigned int start);
};

class cProperty;
class cPropertyList
{
public:
    VP VP VP VP VP VP VP VP VP
    virtual bool GetProperty(unsigned int name, cProperty** ppProperty);   // +0x24
};
}   // namespace EA

class cProperty
{
public:
    unsigned int* GetUInt();        // 0x0041ea00
    bool* GetBool();                // 0x0041e920
    char mPad_00[0x12];
    unsigned short mnType;          // +0x12
};

extern EA::cPropertyList* gpAppPreferences;     // 0x015fd91c

class ConfigManager
{
public:
    VP16 VP8 VP4
    virtual unsigned int GetValue(unsigned int name);   // +0x30
};
ConfigManager* GetConfigManager();                  // 0x0067dd30

void SetGlobalProperty(unsigned int name, float value);     // 0x005ca880

// Resource manager (the object returned by GetManager()).
class ResourceManager
{
public:
    VP16 VP4 VP VP
    virtual int V58(void* pDesc);                   // +0x58
};
ResourceManager* GetManager();                      // 0x0067dcd0

void FUN_00a3cdb0();                                // 0x00a3cdb0
void FUN_00a3cea0();                                // 0x00a3cea0
void FUN_00a37680();                                // 0x00a37680
extern void* gFn1675f58;                            // 0x01675f58

// ---------------------------------------------------------------- EAPD
namespace EA {
namespace Audio {
namespace Eapd {

class ISystem
{
public:
    VP16 VP
    virtual void V44(unsigned int id, float value);     // +0x44
};
ISystem* GetSingletonPtr();                             // 0x00a67c60

namespace Debug {
class EapdObj
{
public:
    VP16 VP8 VP4
    virtual void V70(int a, void* desc);                // +0x70
};
class EapdEvent
{
public:
    EapdEvent(unsigned int id) : mId(id) {}
    virtual ~EapdEvent() {}     // user dtor: registers the EH cleanup (0x1219d80-style)
    unsigned int mId;   // +0x04
};
EapdObj* ObjectError();                                 // 0x008de1a0
}   // namespace Debug

}   // namespace Eapd

class SystemAT
{
public:
    VP16 VP16 VP16 VP8 VP4 VP
    virtual unsigned int SymbolToId(const char* name);      // +0xf4
};
SystemAT* GetSystemAT();                                    // 0x00a206f0

}   // namespace Audio
}   // namespace EA

// ---------------------------------------------------------------- emitters
namespace SP {
namespace Audio {

class cEmitterSndPlayer
{
public:
    static void* operator new(unsigned int size);   // 0x00a38f30
    cEmitterSndPlayer();                            // 0x00a38d90
    char mData[0xe08];
};

class cEmitterEAPD
{
public:
    static void* operator new(unsigned int size);   // 0x00a37a70
    cEmitterEAPD();                                 // 0x00a37b10
    char mData[0x38];
};

class cEmitterModelSound
{
public:
    static void* operator new(unsigned int size);   // 0x00a37f70
    cEmitterModelSound();                           // 0x00a38c70
    char mData[0xe18];
};

}   // namespace Audio
}   // namespace SP

// ---------------------------------------------------------------- SP::App / messaging
namespace SP {
class cViewer
{
public:
    void GetCameraLocationInfo(Vector3* a, Vector3* b, Vector3* c, Vector3* d);  // 0x007c3d30
};
class cListener
{
public:
    void Update(void* pViewer);                     // 0x00a3bc70
};
class AppType
{
public:
    VP16 VP4 VP VP
    virtual cViewer* V58();                         // +0x58
};
AppType* App();                                     // 0x0067dd10
}   // namespace SP

class MessageServer
{
public:
    VP VP VP VP VP VP
    virtual void V18(unsigned int id, int a, int b, int c);     // +0x18
};
MessageServer* GetMessageServer();                  // 0x0067dcc0

// ---------------------------------------------------------------- audio command
class Command
{
public:
    int Type();                                     // 0x00fc7e50
    bool SetT(unsigned int id, int a, int b);       // 0x00a0fa50
    char* GetString8(unsigned int id);              // 0x00a0fb60
    bool GetBool(unsigned int id, void* out);       // 0x00a0fa70
    void SetUint64(unsigned int id, unsigned int value);        // 0x00a0fcf0
};

class cEventModifier
{
public:
    bool ModifyEvent(Command* cmd);                 // 0x00a39620
};

// Vtable-only helper types dispatched by the engine entry points (bodies live elsewhere).
class Obj44
{
public:
    VP8 VP VP VP
    virtual void Slot2c(unsigned int id, float value, int flag);   // +0x2c
};

class ListenerObj
{
public:
    VP VP VP VP VP VP
    virtual void V18(float dt);                     // +0x18
};

class EventMod
{
public:
    VP VP
    virtual unsigned int V08(float* pValue);        // +0x08
};

class HandlerTable
{
public:
    bool Register(unsigned int index, void* obj);   // 0x00a39280
    bool Unregister(unsigned int index);            // 0x00a392d0
};

// The slot-0 virtual hook invoked on a freshly constructed sound.
class SoundInit
{
public:
    virtual void V00();
};

class cTypeMapHolder
{
public:
    void SetTypePriority(unsigned int id, unsigned int priority);  // 0x00a2f180
};

// The rw audio core object reached through the engine's +0xa4 handle (bodies outside this object file).
class RwVoiceList
{
public:
    void RegisterBuiltIn();             // 0x0112dca0
};
class RwDecoderRegistry
{
public:
    void RegisterBuiltInPlugIns();      // 0x0112dbd0
};
class RwAudioSystem
{
public:
    RwVoiceList* GetVoiceList();            // 0x0112ce00
    RwDecoderRegistry* GetDecoderRegistry();    // 0x0112dc80
};

// The vtable-bearing argument of UpdateAndTestRunTimePolyphonyForSound.
class SoundObj
{
public:
    VP VP VP VP VP VP VP VP
    virtual bool V20(int a, int b);                 // +0x20
    VP VP VP VP VP VP VP VP
    virtual int V44(int arg);                       // +0x44

    int FUN_00a1b3f0();                             // 0x00a1b3f0
    int FUN_00a1ad70();                             // 0x00a1ad70
    int FUN_00a1ad80();                             // 0x00a1ad80
    int FUN_00a1ad90();                             // 0x00a1ad90
    int FUN_00a1ada0();                             // 0x00a1ada0
};

// The polymorphic curve-descriptor consumed by ResolveCurve.
struct CurveDesc
{
    char m00;               // +0x00
    char m01;               // +0x01
    char m02;               // +0x02
    char m03;               // +0x03
    char mPad_04[0x20];     // +0x04
    unsigned int m24;       // +0x24
    unsigned int m28;       // +0x28
    unsigned int m2c;       // +0x2c
    unsigned int m30;       // +0x30
    unsigned int m34;       // +0x34
    unsigned int m38;       // +0x38
    unsigned int m3c;       // +0x3c
    unsigned int m40;       // +0x40
    unsigned int m44;       // +0x44
};

// ---------------------------------------------------------------- cSound bodies
// @ 0x00a41c40
float cSound::ComputeGainAttenuation(float a, float b, float c, float d, float e)
{
    float t;
    if (e != kOne)
        t = (kOne / e) * a;
    else
        t = a;
    if (c > t || b == kZero)
        return 1.0f;
    if (t > d)
        return 0.0f;
    return mCurve2174.GetOutputValue((t - c) / (d - c));
}

// @ 0x00a41d30
void cSound::CommitAllProperties()
{
    ((EA::Audio::Sound*)this)->CommitAllProperties();
    if (mFlags & 0x80000) {
        float v;
        if (((CurveSource*)this)->Slot10(0x39f9e0f, &v)) {
            float out = mCurve1e10.GetOutputValue(v);
            ((Obj44*)mpObj44)->Slot2c(0x82beafe0, out, 1);
        }
    }
    float v2;
    if (((CurveSource*)this)->Slot10(0x39fb000, &v2)) {
        if (mFlags & 0x100000) {
            float out = mCurve24d8.GetOutputValue(v2);
            ((CurveSource*)this)->Slot0c(0x71bc3009, out, 1);
        }
        if (mFlags & 0x200000) {
            float out = mCurve283c.GetOutputValue(v2);
            ((CurveSource*)this)->Slot0c(0x25df0108, out, 1);
        }
    }
}

// ---------------------------------------------------------------- elapsed time
// @ 0x00a41fc0
double FUN_00a41fc0()
{
    LARGE_INTEGER li;
    if (!(gTimerFlags & 1)) {
        gTimerFlags |= 1;
        QueryPerformanceCounter(&li);
        gStart = li;
    }
    if (!(gTimerFlags & 2)) {
        gTimerFlags |= 2;
        unsigned __int64 freq = GetStopwatchFrequency();
        gSecondsPerTick = 1.0 / (double)freq;
    }
    QueryPerformanceCounter(&li);
    return (double)(li.QuadPart - gStart.QuadPart) * gSecondsPerTick;
}

// ---------------------------------------------------------------- emitter factories
// @ 0x00a420d0
SP::Audio::cEmitterSndPlayer* ConstructcEmitterSndPlayer()
{
    return new SP::Audio::cEmitterSndPlayer();
}

// @ 0x00a42130
SP::Audio::cEmitterEAPD* ConstructcEmitterEAPD()
{
    SP::Audio::cEmitterEAPD* p = new SP::Audio::cEmitterEAPD();
    return p ? (SP::Audio::cEmitterEAPD*)((char*)p + 4) : 0;
}

// @ 0x00a42190
SP::Audio::cEmitterModelSound* ConstructcEmitterModelSound()
{
    SP::Audio::cEmitterModelSound* p = new SP::Audio::cEmitterModelSound();
    return p ? (SP::Audio::cEmitterModelSound*)((char*)p + 4) : 0;
}

// ---------------------------------------------------------------- engine bodies
// @ 0x00a42200
unsigned int SP::Audio::StaticConvertSymbolToId(const char* name)
{
    return EA::Audio::GetSystemAT()->SymbolToId(name);
}

// @ 0x00a42220
bool cAudioSystem::PreInit(void* pCommandLine)
{
    EA::CommandLine* pCmd = (EA::CommandLine*)pCommandLine;
    FUN_00a3cdb0();
    if (pCmd->FindSwitch(L"noSound", false, 0, 0) != (unsigned int)-1)
        return false;
    if (pCmd->FindSwitch(L"nofocus", false, 0, 0) != (unsigned int)-1)
        mbNoFocus = false;
    unsigned int desc[3];
    desc[0] = 0xe611314a;
    desc[1] = 0x2b9f662;
    desc[2] = 0x21407ee;
    if (GetManager()->V58(desc) == 0)
        return false;
    FUN_00a3cea0();
    gFn1675f58 = (void*)&FUN_00a37680;
    return true;
}

// @ 0x00a42310
void cAudioSystem::SetupTypePriorities()
{
    ((cTypeMapHolder*)this)->SetTypePriority(0x3055f61, 0);
    ((cTypeMapHolder*)this)->SetTypePriority(0x2b9f662, 1);
    ((cTypeMapHolder*)this)->SetTypePriority(0x1a527db, 2);
    ((cTypeMapHolder*)this)->SetTypePriority(0x22d2c83, 3);
}

// @ 0x00a42360
void cAudioSystem::SetTypePriority(unsigned int id, float value)
{
    EA::Audio::Eapd::ISystem* pSystem = EA::Audio::Eapd::GetSingletonPtr();
    if (pSystem)
        pSystem->V44(id, value);
    Map_266e0(id, value);
}

// @ 0x00a423a0
int cAudioSystem::ResolveCurve(CurveDesc* d)
{
    unsigned int magic = d->m3c;
    if (magic == 0xa852cbd1)
        return 5;
    if (d->m02 != 0)
        return 5;
    switch (d->m30) {
    case 0:
    case 4:
        d->m34 = mn15bc88;
        d->m38 = mn15bc98;
        break;
    case 1:
    case 5:
    case 6:
    case 7:
        d->m34 = mn15bc84;
        d->m38 = mn15bc94;
        break;
    default:
        return 1;
    }
    switch (magic) {
    case 0x20681cd4: d->m40 = mn15bc8c; d->m44 = mn15bc9c; break;
    case 0x6f394b77: d->m40 = mn15bc90; d->m44 = mn15bca0; break;
    default: d->m40 = 0; d->m44 = 0xffffffff; break;
    }
    if (d->m28 < d->m2c && d->m34 < d->m38 && d->m40 < d->m44)
        return 5;
    if (d->m01 != 0)
        return 3;
    if (d->m28 >= d->m2c && d->m24 == 0xee8347b0)
        return 2;
    return 4;
}

// @ 0x00a424b0
void cAudioSystem::ResetCurveIds()
{
    Map_26530();
    mn15bc84 = 0;
    mn15bc88 = 0;
    mn15bc8c = 0;
    mn15bc90 = 0;
}

// @ 0x00a424e0
bool cAudioSystem::UpdateAndTestRunTimePolyphonyForSound(void* pSound, int count)
{
    SoundObj* snd = (SoundObj*)pSound;
    if (snd->FUN_00a1b3f0())
        return true;
    unsigned int diff = (unsigned int)(V15c(snd->V44(count)) - count);
    unsigned int q = snd->FUN_00a1ad70();
    unsigned int* p2 = 0;
    unsigned int limit2;
    if (snd->FUN_00a1ad90() == 0x20681cd4) {
        p2 = (unsigned int*)&mn15bc8c;
        limit2 = (unsigned int)mn15bc9c;
    } else if (snd->FUN_00a1ad90() == 0x6f394b77) {
        p2 = (unsigned int*)&mn15bc90;
        limit2 = (unsigned int)mn15bca0;
    }
    unsigned int limit1;
    unsigned int* p1 = 0;
    if (!snd->V20(-1, 0)) {
        switch (snd->FUN_00a1ad80()) {
        case 0:
        case 4:
            limit1 = (unsigned int)mn15bc98;
            p1 = (unsigned int*)&mn15bc88;
            break;
        case 1:
        case 5:
        case 6:
        case 7:
            limit1 = (unsigned int)mn15bc94;
            p1 = (unsigned int*)&mn15bc84;
            break;
        default:
            limit1 = (unsigned int)count;
            break;
        }
    } else {
        limit1 = (unsigned int)count;
    }
    if (count >= 0) {
        if (diff >= q)
            return false;
        if (p1 && *p1 >= limit1)
            return false;
        if (p2 && *p2 >= limit2)
            return false;
    }
    if (count != 0) {
        if (p1)
            *p1 += snd->FUN_00a1ada0() * count;
        if (p2)
            *p2 += count;
    }
    return true;
}
// @ 0x00a42640
bool cAudioSystem::GetProperty(unsigned int id, float* out)
{
    bool result = true;
    if (id != 0x5ac702f0)
        result = false;
    else
        *out = (float)mb15bc40;
    return result;
}

// @ 0x00a42670
bool __stdcall CreateSound(cSound** ppOut)
{
    if (ppOut == 0)
        return false;
    cSound* p = new cSound();
    *ppOut = p;
    ((SoundInit*)p)->V00();
    return true;
}

// @ 0x00a426f0
void cAudioSystem::SetCurrentContext(void* ctx)
{
    mpCurrentContext = ctx;
    V38(0x43390fd);
    V40(0x433911b, (int)ctx);
    V58();
}

// @ 0x00a42740
int cAudioSystem::GetContextId()
{
    return mn15bc3c;
}

// @ 0x00a42750
void cAudioSystem::GetListenerVectors(Vector3* a, Vector3* b, Vector3* c, Vector3* d)
{
    if (a)
        *a = mV44;
    if (b)
        *b = mV50;
    if (c)
        *c = mV5c;
    if (d)
        *d = mV68;
}

// @ 0x00a427e0
void cAudioSystem::RegisterModules()
{
    RegisterBuiltInModules();
    if (mpA4) {
        ((RwAudioSystem*)mpA4)->GetVoiceList()->RegisterBuiltIn();
        ((RwAudioSystem*)mpA4)->GetDecoderRegistry()->RegisterBuiltInPlugIns();
    }
}

// @ 0x00a42830
bool FUN_00a42830()
{
    EA::Audio::Eapd::Debug::EapdObj* obj = EA::Audio::Eapd::Debug::ObjectError();
    if (obj) {
        EA::Audio::Eapd::Debug::EapdEvent ev(0x22d2c83);
        obj->V70(0, &ev);
    }
    return obj != 0;
}

// @ 0x00a428a0
void cAudioSystem::Update(float dt)
{
    if (mb94) {
        if (mp15bce4)
            ((SP::cListener*)mp15bce4)->Update(SP::App()->V58());
        SP::AppType* pApp = SP::App();
        if (pApp && pApp->V58())
            pApp->V58()->GetCameraLocationInfo(&mV44, &mV50, &mV5c, &mV68);
        UpdateInternal(dt);
        if (mp15bc74)
            ((ListenerObj*)mp15bc74)->V18(dt);
    }
    int n = mn15bf24;
    if (n > 0) {
        --n;
        mn15bf24 = n;
        if ((mn132814 == 0 && mn128aec == 0) || n == 0) {
            GetMessageServer()->V18(0x6e0aae1, 0, 0, 0);
            mn15bf24 = 0;
        }
    }
}

// @ 0x00a429a0
void cAudioSystem::CommandResolve(void* pCommand)
{
    Command* cmd = (Command*)pCommand;
    if (cmd->Type() != 0x3475365)
        return;
    if (!cmd->SetT(0x347537e, 0, 0))
        return;
    char* s = cmd->GetString8(0x347537e);
    if (!s || s[0] != 'f' || s[1] != 'o' || s[2] != 'o' || s[3] != 't')
        return;
    if (!mp15bcec)
        return;
    float a, b, c;
    cmd->GetBool(0x3475391, &a);
    cmd->GetBool(0x3475395, &b);
    cmd->GetBool(0x3475398, &c);
    float tmp[3];
    tmp[0] = a;
    tmp[1] = b;
    tmp[2] = c;
    unsigned int r = ((EventMod*)mp15bcec)->V08(tmp);
    cmd->SetUint64(0x39fa376, r);
}

// @ 0x00a42aa0
bool cAudioSystem::OnEventModifier(void* pCommand)
{
    if (mp15bc78)
        return ((cEventModifier*)mp15bc78)->ModifyEvent((Command*)pCommand);
}

// @ 0x00a42ad0
float cAudioSystem::GetDistance(Vector3* p)
{
    if (!mb15bbf0)
        return 0.0f;
    if (mb15bc42) {
        float len = sqrtf(mCameraPos.x * mCameraPos.x + mCameraPos.y * mCameraPos.y
                          + mCameraPos.z * mCameraPos.z);
        float px = p->x;
        float py = p->y;
        float pz = p->z;
        float sq = px * px + py * py + pz * pz + kEpsilon;
        float inv = 1.0f / sqrtf(sq);
        float dx = mCameraPos.x - px * inv * len;
        float dy = mCameraPos.y - py * inv * len;
        float dz = mCameraPos.z - pz * inv * len;
        return sqrtf(dx * dx + dy * dy + dz * dz);
    }
    float dx = mCameraPos.x - p->x;
    float dy = mCameraPos.y - p->y;
    float dz = mCameraPos.z - p->z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

// @ 0x00a42c10
bool cAudioSystem::RegisterHandler(unsigned int index, void* obj)
{
    if (mp60)
        return ((HandlerTable*)mp60)->Register(index, obj);
    return false;
}

// @ 0x00a42c30
bool cAudioSystem::UnregisterHandler(unsigned int index)
{
    if (mp60)
        return ((HandlerTable*)mp60)->Unregister(index);
    return false;
}
