// Slice s00a43d30: SPAudioSystem.obj -- SP::Audio::cSystem startup/teardown and the EAPD
// group/sound map helpers.
//   /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// Retail layout (the dev PDB is too small to be trusted, every offset below was read off the
// retail code):
//   * the audio engine object (`cAudioSystem`, this of Shutdown/InitCurve) starts with a vtable,
//     has an IHandlerRC at +0x04, its own flags at +0x96/+0x99/+0x1fc/+0x200 and embeds the
//     SP::Audio::cSystem member at +0x15bc18 (whose members therefore sit at +0x15bc18 + k);
//   * every Init access at a negative displacement from `this` (`lea ecx,[esi-0x15bc18]`,
//     `[esi-0x4a4]`, ...) is that embedded engine, addressed exactly the way the original does.
#include "game/types.h"

#ifndef NULL
#define NULL 0
#endif

struct Vector3
{
    float x;    // +0x00
    float y;    // +0x04
    float z;    // +0x08
};

// ---------------------------------------------------------------- allocator
void* operator new(unsigned int size, const char* pName, int flags = 0, unsigned int debugFlags = 0,
                   const char* pFile = 0, int line = 0);   // 0x00f473a0
void operator delete(void* p);                              // 0x00f47380
void operator delete[](void* p);

extern "C" double modf(double value, double* pIntPart);
extern "C" double pow(double base, double exponent);
extern "C" double sqrt(double value);
extern "C" double fabs(double value);

// ---------------------------------------------------------------- SP::Sys
namespace SP {

// ESndSys surface.  Only the slots this object file calls are named, the rest are the unnamed
// virtuals of the retail vtable (slot names are the retail byte offsets).
struct Sys
{
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();  virtual void v28();  virtual void v2c();
    virtual void v30();  virtual void v34();  virtual void v38();  virtual void v3c();
    virtual void v40();  virtual void v44();  virtual void v48();  virtual void v4c();
    virtual void v50();  virtual void v54();  virtual void v58();  virtual void v5c();
    virtual void v60();  virtual void v64();  virtual void v68();  virtual void v6c();
    virtual void v70();  virtual void v74();  virtual void v78();  virtual void v7c();
    virtual void v80();  virtual void v84();  virtual void v88();  virtual void v8c();
    virtual void v90();  virtual void v94();  virtual void v98();  virtual void v9c();
    virtual void va0();  virtual void va4();  virtual void va8();  virtual void vac();
    virtual void vb0();  virtual void vb4();  virtual void vb8();  virtual void vbc();
    virtual void vc0();  virtual void vc4();  virtual void vc8();  virtual void vcc();
    virtual void vd0();  virtual void vd4();  virtual void vd8();  virtual void vdc();
    virtual void ve0();  virtual void ve4();  virtual void ve8();  virtual void vec();
    virtual void vf0();  virtual void vf4();  virtual void vf8();
    virtual void ConfigureSpeakerMode(unsigned int id, float value);   // +0xfc
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158();
    virtual int  GetSoundFromHandle(int handle, int unused);           // +0x15c
    virtual void v160(); virtual void v164(); virtual void v168(); virtual void v16c();
    virtual void v170(); virtual void v174();
    virtual bool GetSoundDefinition(int definition, unsigned int* pOut);  // +0x178
    virtual void v17c(); virtual void v180(); virtual void v184();
    virtual bool FindSoundInstance(unsigned int* pKey, int* pOut);     // +0x188
    virtual bool GetSoundInstance(unsigned int* pKey, void** pOut);    // +0x18c
    virtual void v190(); virtual void v194(); virtual void v198(); virtual void v19c();
    virtual void v1a0();
    virtual int  StartSoundDefinition(int definition);                 // +0x1a4

    bool Init();            // 0x00a252b0  System::Init
    bool Shutdown();        // 0x00a207d0  ?Shutdown@Sys@@QAE_NXZ
};

float GetPropertyAsFloatArray(void* pConfiguration, unsigned int name, float** ppValues,
                              int* pnValues);   // 0x006a08b0
}

// ---------------------------------------------------------------- EA::Messaging
namespace EA {
namespace Messaging {

struct IHandler
{
    virtual void v00();
    virtual void v04();
};

struct Server
{
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();
    virtual void AddHandler(IHandler* pHandler, unsigned int messageID);   // +0x24
};

Server* GetServer();                                                     // 0x00883860
void RemoveHandler(Server* pServer, IHandler* pHandler, const unsigned int* pIDs,
                   unsigned int count, int priority);                     // 0x00571db0

}   // namespace Messaging
}   // namespace EA

// ---------------------------------------------------------------- bigger systems
// Reference counted object whose count sits at +0x04 (AddRef/Release inlined by their users).
struct RefCounted
{
    virtual void v00(int);
    int mnRefCount;                     // +0x04
    int AddRef() { return ++mnRefCount; }
    void Release()
    {
        if (--mnRefCount == 0) {
            mnRefCount = 1;
            v00(1);
        }
    }
};

// Reference counted object with virtual AddRef/Release (slots +0x04/+0x08).
struct IRefCounted
{
    virtual void v00();                 // +0x00
    virtual void AddRef();              // +0x04
    virtual void Release();             // +0x08
    virtual void v0c();                 // +0x0c
};

// Reference counted object whose Release is the second virtual slot (+0x04).
struct IVirtualRelease
{
    virtual void v00();                 // +0x00
    virtual void Release();             // +0x04
    virtual void v08();                 // +0x08
    virtual void v0c();                 // +0x0c
    // These objects are only ever add-ref'd by their own interface; RefPtr's add-ref branch is
    // never taken (it is only used to clear the pointers), so it stays empty.
    void AddRef() {}
};

// Intrusive pointer for RefCounted / IRefCounted objects.
template <class T>
struct RefPtr
{
    T* mpObject;
    RefPtr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// Handler base of the engine (+0x04) and of the messaging/refcount sub-objects.
struct IHandlerRC
{
    virtual void v00();                 // +0x00  deleting destructor
    virtual void v04();                 // +0x04
    virtual void v08();                 // +0x08  AddRef
    virtual void v0c();                 // +0x0c  Release
    virtual void v10();
};

class ModelManager
{
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();  virtual void v28();
    virtual void SetListener(void* pListener);      // +0x2c
    virtual void ClearListener(void* pListener);    // +0x30
};
ModelManager* GetModelManager();                    // 0x0067dd80

class cProperty;

class cPropertyList
{
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(unsigned int name, cProperty** ppProperty);   // +0x24
};
extern cPropertyList* gpAppPreferences;             // 0x015fd91c

class cProperty
{
public:
    unsigned int* GetUInt();                        // 0x0041ea00
    bool* GetBool();                                // 0x0041e920
    char mPad_00[0x12];
    unsigned short mnType;                          // +0x12
};

class ConfigManager
{
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();  virtual void v28();  virtual void v2c();
    virtual unsigned int GetValue(unsigned int name);   // +0x30
};
ConfigManager* GetConfigManager();                  // 0x0067dd30

class CheatManager
{
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();
    virtual void Execute(char* pCommand);           // +0x1c
};
CheatManager* GetCheatManager();                    // 0x0067de20
extern char* gpCheatInvulnerable;                   // 0x01553fac
extern char* gpCheatAllPowerups;                    // 0x01553fb0
extern char* gpCheatUsermusic;                      // 0x01553fb8

void SetGlobalProperty(unsigned int name, float value);   // 0x005ca880

// Audio playback API used by the EAPD helpers.
class AudioAT
{
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();
    virtual int  GetVoiceHandle();                  // +0x24
    virtual void v28();
    virtual void SetGroupActive(void* pGroup);      // +0x2c
    virtual void v30();
    virtual void v34();  virtual void v38();  virtual void v3c();  virtual void v40();
    virtual void v44();  virtual void v48();  virtual void v4c();  virtual void v50();
    virtual void v54();  virtual void v58();  virtual void v5c();  virtual void v60();
    virtual void v64();  virtual void v68();  virtual void v6c();  virtual void v70();
    virtual void v74();  virtual void v78();
    virtual Vector3* GetListener(int index);        // +0x7c
};
namespace EA {
namespace Audio {
AudioAT* GetSystemAT();                             // 0x00a206f0
void AudioSetListener3(void* pGroup, float x, float y, float z);   // 0x009fbc50
}
}

// Sound-owner object shared by the EAPD entry points (node value of the group map).
struct SoundGroup
{
    virtual void v00();
    virtual void Stop();                // +0x04
    char mPad_04[0x1c];
    int mnVoice;                        // +0x20
};

struct SoundName
{
    unsigned int mnName;
};

void ReleaseGroupRef(void* pGroup, int unused);     // 0x00572020
int* GetSoundHandle(unsigned int name);             // 0x005727b0  returns the handle slot
int  GetPlaybackHandle();                           // 0x00a34e90
void Start3dSoundByName(void* pSound, int nVoice, float x, float y, float z);  // 0x00571f80

// ---------------------------------------------------------------- EA::CommandLine
struct WString
{
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    void* mAlloc;           // +0x0c
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};

namespace EA {
struct CommandLine
{
    virtual void v00();
    WString* at(unsigned int index);                                   // 0x0092b1b0
    unsigned int FindSwitch(const wchar_t* pSwitch, bool exact, WString* pOut, unsigned int start);
};
}

namespace EA {
namespace IO {

class FilePath
{
public:
    wchar_t mPath[520];                             // +0x000
    wchar_t* Set(const wchar_t* pPath);             // 0x00930f60
    unsigned int GetDriveAndDirectory(wchar_t* pBuffer, unsigned int maxLen);   // 0x00930d20
};
bool EnsureTrailingPathSeparator(wchar_t* pPath, int maxLen);       // 0x0092fe00

}
}

// ---------------------------------------------------------------- sound map (cSystem +0x320)
// eastl::hashtable layout: functors +0x00, bucket array +0x04, bucket count +0x08,
// element count +0x0c.  Nodes keep the key/record inline and carry the playing object at +0x24.
// The bucket array holds mnBucketCount + 1 entries; the last one points at the first node of
// the sentinel bucket, which is how the original code spells `end()`.
class SoundMap
{
public:
    // Owner of a curve's property configuration (erase releases it through vtable slot +0x04).
    struct ConfigRef
    {
        virtual void v00();             // +0x00
        virtual void Release();         // +0x04
    };

    struct Node
    {
        unsigned int mnName;            // +0x00  symbol key
        char mKeyPad_04[0x0c];          // +0x04
        double mf10;                    // +0x10
        float mf18;                     // +0x18
        float mf1c;                     // +0x1c
        float mf20;                     // +0x20
        ConfigRef* mpConfig;            // +0x24
        Node* mpNext;                   // +0x28
    };

    struct iterator
    {
        Node* mpNode;                   // +0x00
        Node** mpBucket;                // +0x04
    };

    unsigned int mFunctors;             // +0x00
    Node** mpBucketArray;               // +0x04
    unsigned int mnBucketCount;         // +0x08
    unsigned int mnElementCount;        // +0x0c
    char mRehashPolicy[0x0c];           // +0x10
    char mAllocator[0x08];              // +0x1c

    iterator find(const unsigned int* pName) const;                     // 0x00b41b30
    iterator erase(iterator position);                                  // 0x00a443c0
    bool isEnd(const iterator& it) const
    {
        return mpBucketArray[mnBucketCount] == it.mpNode;
    }
    void DoFreeNodes(Node** pBucketArray, unsigned int nBucketCount);   // 0x00a43c90
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
};

// ---------------------------------------------------------------- EAPD group map (+0xd4)
// eastl::hashtable<Symbol, Symbol const, Group*>: same header as SoundMap, the nodes carry the
// owning group at +0x08 and their hash chain at +0x0c.
struct Playing
{
    void* mpGroup;                      // +0x00  owning group object
    void* mpSound;                      // +0x04
    int mnVoice;                        // +0x08
};

class GroupMap
{
public:
    struct Node
    {
        unsigned int mnName;            // +0x00  symbol key
        char mPad_04[0x04];             // +0x04
        void* mpGroup;                  // +0x08
        Node* mpNext;                   // +0x0c
    };

    struct iterator
    {
        Node* mpNode;                   // +0x00
        Node** mpBucket;                // +0x04
    };

    unsigned int mFunctors;             // +0x00
    Node** mpBucketArray;               // +0x04
    unsigned int mnBucketCount;         // +0x08
    unsigned int mnElementCount;        // +0x0c

    iterator find(const unsigned int* pName) const;     // 0x00685f30
    iterator erase(iterator position);                  // 0x00b51cc0
    iterator insert(const Playing& value);                      // 0x00a44390
    iterator insertPlaying(const Playing& value, bool bForce);  // 0x00a43b10
    bool isEnd(const iterator& it) const
    {
        return mpBucketArray[mnBucketCount] == it.mpNode;
    }
};

class IConfiguration;

// Group descriptor handed to the EAPD entry points: symbol name first, position at +0x0c and
// the group's property configuration at +0x90.
struct EapdGroupParam
{
    unsigned int mnName;                // +0x00
    char mPad_04[0x08];                 // +0x04
    Vector3 mPosition;                  // +0x0c
    char mPad_18[0x90 - 0x18];          // +0x18
    IConfiguration* mpConfig;           // +0x90
};

// The EAPD-aware object owning the group map (+0xd4) and the curve map (+0x320).
class Eapd
{
public:
    void Remove(unsigned int name);                                     // 0x00a441b0
    void SetListener(const EapdGroupParam* pGroup);                     // 0x00a44230
    float GetCurveValue(unsigned int name);                             // 0x00a44290
    void Play(const EapdGroupParam* pGroup);                            // 0x00a449a0
    void PlayOrStop(const EapdGroupParam* pGroup, bool bStart);         // 0x00a44a80

    char mPad_000[0xd4];                // +0x000
    GroupMap mGroups;                   // +0x0d4
    char mPad_0e4[0x320 - 0x0e4];       // +0x0e4
    SoundMap mCurves;                   // +0x320
};

// ---------------------------------------------------------------- SP::Audio::cSystem
// Embedded in the engine at +0x15bc18 (see the header comment).
struct cSystem
{
    void* mpUnused00;                       // +0x000
    IHandlerRC mModelListener;              // +0x004
    void* mUnused08;                        // +0x008

    struct MessageRegistration
    {
        EA::Messaging::Server* mpServer;    // +0x00 (cSystem +0x08)
        EA::Messaging::IHandler* mpHandler; // +0x04
        const unsigned int* mpIDArray;      // +0x08
        unsigned int mnIDCount;             // +0x0c
        int mnPriority;                     // +0x10
    } mMessageReg;                          // +0x008
    char mPad_01c[0x5c - 0x1c];             // +0x01c

    RefPtr<IVirtualRelease> mpGroupList;    // +0x05c
    char mPad_060[0xcc - 0x60];             // +0x060

    RefPtr<struct AudioCache> mpCache;       // +0x0cc
    RefPtr<struct cAudioPreferences> mpPreferences;   // +0x0d0
    RefPtr<IVirtualRelease> mpGroupHandle;  // +0x0d4
    char mPad_0d8[0x310 - 0xd8];            // +0x0d8

    WString mAppDir;                        // +0x310
    SoundMap mPlaying;                      // +0x320

    bool Init(EA::CommandLine* pCommandLine);   // 0x00a43d30
};

struct AudioCache : RefCounted
{
    AudioCache();                           // 0x00a3c970
    void Initialize();                      // 0x00a3c710
    void Stop();                            // 0x00a3bb60
    char mData[0x734 - 0x08];               // sizeof(AudioCache) == 0x734
};

struct cAudioPreferences : IRefCounted
{
    cAudioPreferences();                    // 0x00a41000
    void Init();                            // 0x00a41010
    int mnValue;                            // +0x04
};

// The audio engine: vtable + handler, engine state, then the embedded cSystem.
class cAudioSystem : public SP::Sys
{
public:
    IHandlerRC mHandler;                    // +0x004
    char mPad_014[0x96 - 0x14];             // +0x014
    bool mbSilent;                          // +0x096
    char mPad_097[0x99 - 0x97];             // +0x097
    bool mbPropertyBool;                    // +0x099
    char mPad_09a[0x1fc - 0x9a];            // +0x09a
    bool mbVerboseAudio;                    // +0x1fc
    char mPad_1fd[0x200 - 0x1fd];           // +0x1fd
    unsigned int mnSampleRate;              // +0x200
    char mPad_204[0x15b774 - 0x204];        // +0x204
    bool mbNoSampleCache;                   // +0x15b774
    char mPad_15b775[0x15bc18 - 0x15b775];  // +0x15b775
    cSystem mSystem;                        // +0x15bc18

    bool ShutdownSystem();                                          // 0x00a44440
    bool InitCurve(void* pCurve, int nDefault, int nCurve,
                   void* pConfiguration, const Vector3* pPosition);  // 0x00a445a0
};

cAudioSystem* gpAudioSystem;                // 0x0166f118

static const unsigned int knEngineOffset = 0x15bc18;

// SP::Audio::cSystem lives knEngineOffset bytes into the engine object; Init reaches the
// engine fields through that displacement, exactly like the original code does.
inline cAudioSystem* GetAudioSystem(cSystem* pSystem)
{
    return (cAudioSystem*)((char*)pSystem - knEngineOffset);
}

// Publishes the engine in the global smart pointer (release old, store, add-ref new).
inline void PublishAudioSystem(cAudioSystem* pSystem)
{
    if (gpAudioSystem)
        gpAudioSystem->mHandler.v0c();
    gpAudioSystem = pSystem;
    if (pSystem)
        pSystem->mHandler.v08();
}

static const unsigned int kanAudioMessageIDs[15] = {
    0x1453f30, 0x1453f34, 0x1453f38, 0x1453f3c, 0x1453f40, 0x1453f44, 0x1453f48, 0x1453f4c,
    0x1453f50, 0x1453f54, 0x1453f58, 0x1453f5c, 0x1453f60, 0x1453f64, 0x1453f68
};

// @ 0x00a43d30
bool cSystem::Init(EA::CommandLine* pCommandLine)
{
    cAudioSystem* pAudioSystem = GetAudioSystem(this);
    wchar_t appPath[0x104];
    EA::IO::FilePath filePath;
    filePath.Set(pCommandLine->at(0)->mpBegin);
    filePath.GetDriveAndDirectory(appPath, 0x104);
    EA::IO::EnsureTrailingPathSeparator(appPath, -1);

    wchar_t* pEnd = appPath;
    while (*pEnd)
        ++pEnd;
    mAppDir.assign(appPath, pEnd);

    if (pCommandLine->FindSwitch(L"nosamplecache", false, 0, 0) != (unsigned int)-1)
        pAudioSystem->mbNoSampleCache = true;
    if (pCommandLine->FindSwitch(L"verboseaudio", false, 0, 0) != (unsigned int)-1)
        pAudioSystem->mbVerboseAudio = true;

    bool bHaveChannelMode = false;
    cProperty* pProperty = 0;
    if (gpAppPreferences && gpAppPreferences->GetProperty(0x49d4c74d, &pProperty) &&
        pProperty->mnType == 0x0a) {
        unsigned int nChannelMode = *pProperty->GetUInt();
        float fMode;
        if (nChannelMode == 4)
            fMode = 2.0f;
        else if (nChannelMode == 5)
            fMode = 3.0f;
        else
            fMode = 1.0f;
        pAudioSystem->ConfigureSpeakerMode(0x435b383, fMode);
        bHaveChannelMode = true;
    }
    if (!bHaveChannelMode) {
        float fMode;
        if (pCommandLine->FindSwitch(L"mono", false, 0, 0) != (unsigned int)-1)
            fMode = 0.0f;
        else if (pCommandLine->FindSwitch(L"stereo", false, 0, 0) != (unsigned int)-1)
            fMode = 1.0f;
        else if (pCommandLine->FindSwitch(L"quad", false, 0, 0) != (unsigned int)-1)
            fMode = 2.0f;
        else if (pCommandLine->FindSwitch(L"surround", false, 0, 0) != (unsigned int)-1)
            fMode = 3.0f;
        else
            goto noChannelMode;
        pAudioSystem->ConfigureSpeakerMode(0x435b383, fMode);
    }
noChannelMode:

    if (pCommandLine->FindSwitch(L"silent", false, 0, 0) != (unsigned int)-1)
        pAudioSystem->mbSilent = true;

    pAudioSystem->mnSampleRate = GetConfigManager()->GetValue(0x7d8ed666);

    if (gpAppPreferences && gpAppPreferences->GetProperty(0x899eb157, &pProperty) &&
        pProperty->mnType == 1)
        pAudioSystem->mbPropertyBool = *pProperty->GetBool();

    if (!pAudioSystem->Init())
        return false;

    PublishAudioSystem(pAudioSystem);

    EA::Messaging::Server* pServer = EA::Messaging::GetServer();
    mMessageReg.mpServer = pServer;
    mMessageReg.mpHandler = (EA::Messaging::IHandler*)&pAudioSystem->mHandler;
    mMessageReg.mpIDArray = kanAudioMessageIDs;
    mMessageReg.mnIDCount = 15;
    mMessageReg.mnPriority = 0;
    if (pServer && mMessageReg.mpHandler) {
        for (unsigned int i = 0; i < 15; ++i)
            pServer->AddHandler(mMessageReg.mpHandler, kanAudioMessageIDs[i]);
    }

    mpCache = new ("Audio") AudioCache;
    mpCache->Initialize();

    if (pCommandLine->FindSwitch(L"nodefaultvox", false, 0, 0) != (unsigned int)-1)
        SetGlobalProperty(0x5ac702f0, 0.0f);

    mpPreferences = new ("Audio") cAudioPreferences;
    mpPreferences->Init();

    GetModelManager()->SetListener(&pAudioSystem->mSystem.mModelListener);
    return true;
}

// @ 0x00a44440
bool cAudioSystem::ShutdownSystem()
{
    cAudioSystem* pAudioSystem = GetAudioSystem(&mSystem);

    if (GetModelManager())
        GetModelManager()->ClearListener(&pAudioSystem->mSystem.mModelListener);

    if (mSystem.mMessageReg.mpServer) {
        EA::Messaging::Server* pServer = mSystem.mMessageReg.mpServer;
        EA::Messaging::RemoveHandler(pServer, mSystem.mMessageReg.mpHandler,
                                     mSystem.mMessageReg.mpIDArray,
                                     mSystem.mMessageReg.mnIDCount,
                                     mSystem.mMessageReg.mnPriority);
        mSystem.mMessageReg.mpServer = 0;
    }

    if (mSystem.mpCache) {
        mSystem.mpCache->Stop();
        mSystem.mpCache = 0;
    }

    CheatManager* pCheats = GetCheatManager();
    if (pCheats) {
        pCheats->Execute(gpCheatInvulnerable);
        pCheats->Execute(gpCheatAllPowerups);
        pCheats->Execute(gpCheatUsermusic);
    }

    if (mSystem.mpGroupList) {
        mSystem.mpGroupList->v0c();
        mSystem.mpGroupList = 0;
    }

    mSystem.mpGroupHandle = 0;

    mSystem.mPlaying.clear();

    Sys::Shutdown();

    if (gpAudioSystem)
        gpAudioSystem->mHandler.v0c();
    gpAudioSystem = 0;
    return true;
}

// ---------------------------------------------------------------- response curves
namespace EA {
namespace Audio {

class ResponseCurve
{
public:
    ResponseCurve();                                            // 0x00a1aa50
    ~ResponseCurve();
    bool InitFromConfiguration(void* pConfiguration, unsigned int name);   // 0x00a1a9d0
    float GetOutputValue(float value);                          // 0x00a1a110

    void* mpData;                   // +0x00
    char mPad_04[0x0c];             // +0x04
    void* mpAllocation;             // +0x10
    char mPad_14[0x04];             // +0x14
};

ResponseCurve::~ResponseCurve()
{
    if (mpData && mpData != mpAllocation)
        operator delete(mpData);
}

}
}

class IConfiguration
{
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual bool GetString(unsigned int name, unsigned int* pOut);      // +0x20
    virtual bool GetProperty(unsigned int name, void* pOut);            // +0x24
    virtual void v28();
    virtual bool GetInt(unsigned int name, int* pOut);                  // +0x2c
    virtual bool GetFloat(unsigned int name, float* pOut);              // +0x30
    virtual void v34();
    virtual bool GetUInt(unsigned int name, unsigned int* pOut);        // +0x38
};

// Curve description filled in by InitCurve (node value of the curve map at +0x320).
struct CurveData
{
    bool mbEnabled;         // +0x00
    bool mbFlag1;           // +0x01
    bool mbFlag2;           // +0x02
    char mPad_03[0x01];     // +0x03
    float mf04;             // +0x04  max distance
    float mf08;             // +0x08  min distance
    float mf0c;             // +0x0c  output
    float mf10;             // +0x10  gain
    int mn14;               // +0x14
    int mn18;               // +0x18
    int mn1c;               // +0x1c
    unsigned int mn20;      // +0x20  sound name
    unsigned int mn24;      // +0x24
    int mn28;               // +0x28  sound handle
    int mn2c;               // +0x2c
    int mn30;               // +0x30  instance handle
    char mPad_34[0x08];     // +0x34
    int mn3c;               // +0x3c  play mode
};

// Instance of a started sound; the handle the curve keeps lives at +0x14.
struct SoundInstance
{
    char mPad_00[0x14];
    int mnHandle;           // +0x14
};

namespace EA {
namespace Audio {
float GetCurrentVolume();       // 0x00a41fc0
}
}

// @ 0x00a445a0
bool cAudioSystem::InitCurve(void* pCurveData, int nDefault, int nCurve, void* pConfiguration,
                             const Vector3* pPosition)
{
    CurveData* pCurve = (CurveData*)pCurveData;
    IConfiguration* pConfig = (IConfiguration*)pConfiguration;
    pCurve->mn14 = nDefault;
    pCurve->mn18 = nCurve;
    pConfig->GetProperty(0x12d2a4d4, &pCurve->mbEnabled);
    pConfig->GetProperty(0x6dd08218, &pCurve->mbFlag1);
    pConfig->GetProperty(0xba134192, &pCurve->mbFlag2);

    if (pCurve->mbEnabled) {
        if (!pConfig->GetFloat(0xf616b72, &pCurve->mf08))
            return false;
        if (!pConfig->GetFloat(0x3593710, &pCurve->mf04))
            return false;
        if (!pPosition)
            return false;

        int nListener = 0;
        pConfig->GetInt(0xed1f36d5, &nListener);
        Vector3* pListenerPos = EA::Audio::GetSystemAT()->GetListener(nListener);

        float dx = pPosition->x - pListenerPos->x;
        float dy = pPosition->y - pListenerPos->y;
        float dz = pPosition->z - pListenerPos->z;
        float fDistanceSq = dx * dx + dy * dy + dz * dz;
        float fDistance = fabs(sqrt(fDistanceSq));

        if (!pCurve->mbFlag1 && fDistance > pCurve->mf04)
            return false;

        float fGain = 1.0f;
        pConfig->GetFloat(0x2406a047, &fGain);
        float fOutputScale = 1.0f;
        pConfig->GetFloat(0x25df0108, &fOutputScale);

        float fValue;
        if (pCurve->mf08 > fDistance || fGain == 0.0f) {
            fValue = 1.0f;
        } else if (fDistance > pCurve->mf04) {
            fValue = 0.0f;
        } else {
            EA::Audio::ResponseCurve response;
            response.InitFromConfiguration(pConfig, 0x1e4db1eb);
            fValue = response.GetOutputValue((fDistance - pCurve->mf08) /
                                             (pCurve->mf04 - pCurve->mf08));
        }
        pCurve->mf0c = fValue * fOutputScale;
    }

    pCurve->mf10 = 1.0f;
    pConfig->GetFloat(0x393f7f7d, &pCurve->mf10);
    pCurve->mn1c = 1;
    pConfig->GetInt(0xd9ec19d6, &pCurve->mn1c);
    pCurve->mn24 = 0xee8347b0;
    pConfig->GetUInt(0x7f28acc, &pCurve->mn24);
    pCurve->mn28 = GetSoundFromHandle(nDefault, 0);
    pCurve->mn2c = 2;
    pConfig->GetInt(0xbaf7f4f9, &pCurve->mn2c);
    pConfig->GetInt(0x51997db2, &pCurve->mn3c);
    if (pCurve->mn3c == 0) {
        unsigned int nDefinition = 0;
        if (GetSoundDefinition(pCurve->mn14, &nDefinition) && nDefinition == 0x22d2c83)
            pCurve->mn3c = 0xa852cbd1;
    }
    pConfig->GetUInt(0x701ed91e, &pCurve->mn20);
    if (pCurve->mn20 == 0)
        pCurve->mn20 = nDefault;
    pCurve->mn30 = -1;
    if (pCurve->mn3c != 0xa852cbd1) {
        unsigned int key[3];
        key[0] = pCurve->mn20;
        key[1] = 0x3055f61;
        key[2] = 0x21407ee;
        int nInstance = 0;
        if (FindSoundInstance(key, &nInstance)) {
            void* pInstance = 0;
            if (GetSoundInstance(key, &pInstance))
                pCurve->mn30 = ((SoundInstance*)pInstance)->mnHandle;
        } else {
            pCurve->mn30 = StartSoundDefinition(pCurve->mn20);
        }
    }
    return true;
}

// @ 0x00a443c0
SoundMap::iterator SoundMap::erase(iterator position)
{
    Node* pNode = position.mpNode;
    iterator result;
    result.mpBucket = position.mpBucket;
    result.mpNode = pNode->mpNext;
    while (!result.mpNode) {
        ++result.mpBucket;
        result.mpNode = *result.mpBucket;
    }

    if (*position.mpBucket == pNode) {
        *position.mpBucket = pNode->mpNext;
    } else {
        Node* pPrev = *position.mpBucket;
        while (pPrev->mpNext != pNode)
            pPrev = pPrev->mpNext;
        pPrev->mpNext = pNode->mpNext;
    }

    if (pNode->mpConfig)
        pNode->mpConfig->Release();
    operator delete(pNode);
    --mnElementCount;
    return result;
}

// @ 0x00a441b0
void Eapd::Remove(unsigned int name)
{
    unsigned int key = name;
    GroupMap::iterator it = mGroups.find(&key);
    if (!mGroups.isEnd(it)) {
        GroupMap::Node* pNode = it.mpNode;
        if (pNode->mpGroup) {
            ReleaseGroupRef(pNode->mpGroup, 0);
            AudioAT* pAudioAT = EA::Audio::GetSystemAT();
            if (pAudioAT)
                pAudioAT->SetGroupActive(pNode->mpGroup);
        }
        mGroups.erase(it);
    }
}

// @ 0x00a44230
void Eapd::SetListener(const EapdGroupParam* pGroup)
{
    unsigned int key = (unsigned int)pGroup;
    GroupMap::iterator it = mGroups.find(&key);
    if (!mGroups.isEnd(it)) {
        EA::Audio::AudioSetListener3(it.mpNode->mpGroup, pGroup->mPosition.x,
                                     pGroup->mPosition.y, pGroup->mPosition.z);
    }
}

// @ 0x00a44290
float Eapd::GetCurveValue(unsigned int name)
{
    SoundMap::iterator it = mCurves.find(&name);
    if (mCurves.isEnd(it))
        return 0.0f;

    SoundMap::Node* pNode = it.mpNode;
    if (!pNode->mpConfig)
        return 0.0f;

    float* pValues;
    int nValues;
    if (!SP::GetPropertyAsFloatArray(pNode->mpConfig, 0xe888e2af, &pValues, &nValues))
        return 0.0f;

    double dIntPart;
    double dFraction = modf((EA::Audio::GetCurrentVolume() - pNode->mf10) * pNode->mf18,
                            &dIntPart);
    int nIndex = (int)dIntPart;

    float fValue;
    if (nIndex < nValues - 1)
        fValue = (float)(pValues[nIndex] +
                         (pValues[nIndex + 1] - pValues[nIndex]) * dFraction);
    else
        fValue = pValues[nValues - 1];

    if (pNode->mf20 != 0.0f)
        fValue = pNode->mf20 * fValue;
    if (pNode->mf1c != 0.0f)
        fValue = (float)pow(fValue, pNode->mf1c);
    return fValue;
}

// @ 0x00a449a0
void Eapd::Play(const EapdGroupParam* pGroup)
{
    unsigned int key = (unsigned int)pGroup;
    GroupMap::iterator it = mGroups.find(&key);
    if (!mGroups.isEnd(it))
        return;

    unsigned int nSoundName = 0;
    if (!pGroup || !pGroup->mpConfig)
        return;
    if (!pGroup->mpConfig->GetString(0x4a5b8d2, &nSoundName))
        return;

    void* pSound = (void*)(unsigned int)*GetSoundHandle(nSoundName);
    int nVoice = 0;
    AudioAT* pAudioAT = EA::Audio::GetSystemAT();
    if (pAudioAT)
        nVoice = pAudioAT->GetVoiceHandle();
    Start3dSoundByName(pSound, nVoice, pGroup->mPosition.x, pGroup->mPosition.y,
                       pGroup->mPosition.z);

    Playing playing;
    playing.mpGroup = (void*)pGroup;
    playing.mpSound = pSound;
    playing.mnVoice = nVoice;
    mGroups.insertPlaying(playing, false);
}

// @ 0x00a44a80
void Eapd::PlayOrStop(const EapdGroupParam* pGroup, bool bStart)
{
    unsigned int key = (unsigned int)pGroup;
    GroupMap::iterator it = mGroups.find(&key);
    if (!bStart) {
        if (!mGroups.isEnd(it)) {
            GroupMap::Node* pNode = it.mpNode;
            if (pNode->mpGroup) {
                ReleaseGroupRef(pNode->mpGroup, 0);
                AudioAT* pAudioAT = EA::Audio::GetSystemAT();
                if (pAudioAT)
                    pAudioAT->SetGroupActive(pNode->mpGroup);
            }
            mGroups.erase(it);
        }
        return;
    }

    if (!mGroups.isEnd(it))
        return;

    unsigned int nSoundName = 0;
    if (!pGroup || !pGroup->mpConfig)
        return;
    if (!pGroup->mpConfig->GetString(0x4a5b8d2, &nSoundName))
        return;

    void* pSound = (void*)(unsigned int)*GetSoundHandle(nSoundName);
    int nVoice = GetPlaybackHandle();

    Playing playing;
    playing.mpGroup = (void*)pGroup;
    playing.mpSound = pSound;
    playing.mnVoice = nVoice;
    mGroups.insert(playing);

    Start3dSoundByName(pSound, nVoice, pGroup->mPosition.x, pGroup->mPosition.y,
                       pGroup->mPosition.z);
}
