// src/game/SPAudio/AudioVoiceContainer.cpp -- migrated from slice(s) s00a33ee0 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioVoiceContainer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/VoiceContainer.h"
#include "EA/Audio/Command.h"
#include "EA/Audio/Submix.h"
#include "EA/Audio/System.h"
#include "rw/audio/core/System.h"

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
struct Voice_s00a3_3ee0 { void Release(); };                               // 0x0112e950
}
}
}
namespace rw {
namespace audio {
namespace core {
struct PlugIn_s00a3_3ee0 {
    char pad[0x10];
    PlugInDescRunTime_s00a3_3ee0* mpDesc;                                  // +0x10
    void Connect(int slot, void* value);                        // 0x0112ccc0
    bool GetAttribute(int attr, float* out);                    // 0x0112cc80
    bool SetAttribute(int attr, float value);                   // 0x0112ccf0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
struct System_s00a3_3ee0 {
    void Enter();                                               // 0x0112c600
    void Leave();                                               // 0x0112c620
    PlugIn_s00a3_3ee0* GetMasteringVoice();                                // 0x00ff35d0
};
}
}
}
namespace rw {
namespace audio {
namespace core {
Voice_s00a3_3ee0* __cdecl CreateVoice(int flag, int numPlugins, PlugInConfig_s00a3_3ee0* configs, PlugIn_s00a3_3ee0*** outPlugins, System_s00a3_3ee0* sys);  // 0x0112e720
}
}
}
extern rw::audio::core::System_s00a3_3ee0* g_pAudioSystem_s00a3_3ee0;   // 0x016e61a8
struct ScopedLock {
    ScopedLock() { rw::audio::core::System_s00a3_3ee0* s = g_pAudioSystem_s00a3_3ee0; if (s) s->Enter(); }
    ~ScopedLock() { rw::audio::core::System_s00a3_3ee0* s = g_pAudioSystem_s00a3_3ee0; if (s) s->Leave(); }
};
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
struct Submix_s00a3_3ee0;
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
struct AudioSystem {                        // EA::Audio::GetSystemAT() result
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual Submix_s00a3_3ee0* GetSubmix(uint32_t id);   // slot 95 (+0x17c)
};
}
}
namespace EA {
namespace Audio {
AudioSystem* __cdecl GetSystemAT();         // 0x00a206f0
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
    bool Connect();
    bool Reconnect();  // 0x00a34c90 (EA::Audio::VoiceContainer::Reconnect)
    bool AddPropertyBinding(uint32_t prop, uint32_t pluginId, uint32_t guid, int attr, const float* pDefault);
    void SetSendId(uint32_t id);
    bool HasPropertyBinding(uint32_t prop);  // 0x00a33e90 (EA::Audio::VoiceContainer::HasPropertyBinding)
};
}
}
namespace EA {
namespace Audio {
struct HashSetRaw {                          // eastl hash set of PlugIn*, reached at Submix+0x160c
    uint32_t pad[1];
    uint32_t* mpBuckets;                     // +4
    uint32_t mnBucketCount;                  // +8
    uint32_t End() { uint32_t* p = mpBuckets + mnBucketCount; return *p; }
    void* Find(uint32_t* outIter, rw::audio::core::PlugIn_s00a3_3ee0** key);                           // FUN_00a23ef0
    void  Erase(uint32_t* outIter, uint32_t node, uint32_t bucket);        // FUN_00a23db0
    void  Insert(uint32_t* outIter, rw::audio::core::PlugIn_s00a3_3ee0** key, uint32_t flag);          // FUN_00a26be0
};
}
}
namespace EA {
namespace Audio {
struct Submix_s00a3_3ee0 {
    void**          vtbl;
    char            pad4[0xc];
    VoiceContainer_s00a3_3ee0  mVoiceContainer;         // +0x10
    char            pad970[4];
    uint32_t        mSendNameBegin;          // +0x974
    char            pad978[0x15fc - 0x978];
    bool            mbDefaultToMasterIfDisabled;   // +0x15fc
    bool            mbSendsEnabled;                // +0x15fd
    char            pad15fe[0x160c - 0x15fe];
    HashSetRaw      mSendPlugins;            // +0x160c

    bool DisconnectSendFromSubmix(rw::audio::core::PlugIn_s00a3_3ee0* plugin);  // 0x00a34660 (EA::Audio::Submix::DisconnectSendFromSubmix)
    bool ConnectSendToSubmix(rw::audio::core::PlugIn_s00a3_3ee0* plugin);  // 0x00a34a10 (EA::Audio::Submix::ConnectSendToSubmix)
};
}
}
namespace EA {
namespace Audio {
static inline int ChainCount(const VoiceContainer_s00a3_3ee0* c) { return (int)(c->mChain.mpEnd - c->mChain.mpBegin); }
}
}
namespace EA {
namespace Audio {
const uint32_t kGuidSend = 0x53656e30;     // 'Sen0'
}
}
namespace EA {
namespace Audio {
const uint32_t kGuidSubmix = 0x53756230;   // 'Sub0'
}
}
namespace EA {
namespace Audio {
struct BindingVector {
    tBinding_s00a3_3ee0* mpBegin;
    tBinding_s00a3_3ee0* mpEnd;
    tBinding_s00a3_3ee0* mpCapacity;
    void DoInsertValue(tBinding_s00a3_3ee0* position, const tBinding_s00a3_3ee0& value);
};
}
}
namespace EA {
namespace Audio {
tBinding_s00a3_3ee0* __cdecl do_move_start(tBinding_s00a3_3ee0* first, tBinding_s00a3_3ee0* last, tBinding_s00a3_3ee0* result);   // 0x00a33d90
}
}
// ---- items of slice s00a33ee0 end

// @ 0x00a33ee0
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::SetProperty(uint32_t prop, float value)
{
    int n = mBindings.size();
    int i = 0;
    if (0 < n) {
        tBinding_s00a3_3ee0* b = mBindings.mpBegin;
        do {
            if (b->mProperty == prop) {
                if (b->mpPlugin && !(b->mFlags & 2)) {
                    if (b->mbFirst != false) {
                        b->mbFirst = false;
                    } else {
                        float* pLast = &b->mLast;
                        if (value == *pLast)
                            return true;
                    }
                    b->mLast = value;
                    ScopedLock lock;
                    b->mpPlugin->SetAttribute(b->mAttribute, value);
                    return true;
                }
                break;
            }
            ++i;
            ++b;
        } while (i < n);
    }
    return false;
}
}}  // namespace EA::Audio

// @ 0x00a33fd0
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::GetProperty(uint32_t prop, float* out)
{
    int n = mBindings.size();
    int i = 0;
    if (0 < n) {
        tBinding_s00a3_3ee0* b = mBindings.mpBegin;
        do {
            if (b->mProperty == prop) {
                if (b->mpPlugin) {
                    if (b->mbFirst == false) {
                        *out = b->mLast;
                        return true;
                    }
                    ScopedLock lock;
                    b->mpPlugin->GetAttribute(b->mAttribute, out);
                    return true;
                }
                break;
            }
            ++i;
            ++b;
        } while (i < n);
    }
    return false;
}
}}  // namespace EA::Audio

// @ 0x00a340b0
namespace EA { namespace Audio {
void VoiceContainer_s00a3_3ee0::MaskPluginBindings(const uint32_t* props, int count)
{
    int n = mBindings.size();
    if (0 < n) {
        int off = 0;
        do {
            uint32_t* pf = (uint32_t*)((int)&mBindings.mpBegin->mFlags + off);
            *pf &= 0xfffffffd;
            off += sizeof(tBinding_s00a3_3ee0);
            --n;
        } while (n != 0);
    }
    while (count != 0) {
        uint32_t prop = *props;
        --count;
        n = mBindings.size();
        ++props;
        int i = 0;
        if (0 < n) {
            tBinding_s00a3_3ee0* b = mBindings.mpBegin;
            do {
                if (b->mProperty == prop) {
                    b->mFlags |= 2;
                    if ((b->mFlags & 1) && b->mpPlugin) {
                        ScopedLock lock;
                        b->mpPlugin->SetAttribute(b->mAttribute, b->mDefault);
                    }
                    break;
                }
                ++i;
                ++b;
            } while (i < n);
        }
    }
}
}}  // namespace EA::Audio

// @ 0x00a341e0
namespace EA { namespace Audio {
int VoiceContainer_s00a3_3ee0::FindPluginIndex(uint32_t guid)
{
    int n = mChain.size();
    uint32_t i = 0;
    if (n != 0) {
        rw::audio::core::PlugInConfig_s00a3_3ee0* c = mChain.mpBegin;
        do {
            if (c->plugInHandle->guid == guid)
                return (int)i;
            ++i;
            ++c;
        } while (i < (uint32_t)n);
    }
    return -1;
}
}}  // namespace EA::Audio

// @ 0x00a34230
namespace EA { namespace Audio {
rw::audio::core::PlugIn_s00a3_3ee0* VoiceContainer_s00a3_3ee0::FindPlugin(uint32_t guid)
{
    int i = FindPluginIndex(guid);
    if (i < 0)
        return 0;
    return mppPlugins[i];
}
}}  // namespace EA::Audio

// @ 0x00a34260
namespace EA { namespace Audio {
rw::audio::core::PlugIn_s00a3_3ee0* VoiceContainer_s00a3_3ee0::FindPluginIndexById(uint32_t id)
{
    int n = mChain.size();
    int i = 0;
    if (0 < n) {
        uint32_t* p = mpIdBegin;
        do {
            if (*p == id) {
                if (i < 0)
                    return 0;
                return mppPlugins[i];
            }
            ++i;
            ++p;
        } while (i < n);
    }
    return 0;
}
}}  // namespace EA::Audio

// @ 0x00a342c0
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::Create(uint8_t flag)
{
    mbConnected = false;
    ScopedLock lock;
    mpVoice = rw::audio::core::CreateVoice(flag, ChainCount(this), mChain.mpBegin, &mppPlugins, g_pAudioSystem_s00a3_3ee0);
    if (!mpVoice)
        return false;
    int n = mBindings.size();
    for (int i = 0; i < n; ++i) {
        tBinding_s00a3_3ee0* b = &mBindings.mpBegin[i];
        b->mpPlugin = FindPluginIndexById(b->mPluginId);
    }
    mbCreated = true;
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a343e0
namespace EA { namespace Audio {
void VoiceContainer_s00a3_3ee0::Destroy()
{
    int n = mBindings.size();
    if (n > 0) {
        int off = 0;
        do {
            *(rw::audio::core::PlugIn_s00a3_3ee0**)((int)&mBindings.mpBegin->mpPlugin + off) = 0;
            off += sizeof(tBinding_s00a3_3ee0);
        } while (--n);
    }
    if (mpVoice) {
        mpVoice->Release();
        mpVoice = 0;
    }
    mbCreated = false;
}
}}  // namespace EA::Audio

// @ 0x00a34440
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::ConnectToMasteringVoice(rw::audio::core::PlugIn_s00a3_3ee0* plugin)
{
    rw::audio::core::System_s00a3_3ee0* sys = g_pAudioSystem_s00a3_3ee0;
    if (!sys)
        return false;
    if (!plugin) {
        if (mChain.empty())
            return false;
        int n = mChain.size();
        rw::audio::core::PlugIn_s00a3_3ee0* last = mppPlugins[n - 1];
        if (mChain[n - 1].plugInHandle->guid != kGuidSend)
            return false;
        plugin = last;
    }
    ScopedLock lock;
    rw::audio::core::PlugIn_s00a3_3ee0* master = sys->GetMasteringVoice();
    plugin->Connect(0, &master);
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a34530
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::DisconnectFromMasteringVoice(rw::audio::core::PlugIn_s00a3_3ee0* plugin)
{
    rw::audio::core::System_s00a3_3ee0* sys = g_pAudioSystem_s00a3_3ee0;
    if (!sys)
        return false;
    if (!plugin) {
        if (mChain.empty())
            return false;
        int n = mChain.size();
        rw::audio::core::PlugIn_s00a3_3ee0* last = mppPlugins[n - 1];
        if (mChain[n - 1].plugInHandle->guid != kGuidSend)
            return false;
        plugin = last;
    }
    ScopedLock lock;
    rw::audio::core::PlugIn_s00a3_3ee0* none = 0;
    plugin->Connect(0, &none);
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a34620
namespace EA { namespace Audio {
void VoiceContainer_s00a3_3ee0::DtorTail()
{
    uint32_t* p = mpIdBegin;
    if (p && p != mpIdBuf)
        operator delete(p);
    p = mpSendBegin;
    if (p && p != mpSendBuf)
        operator delete(p);
}
}}  // namespace EA::Audio

// @ 0x00a34660
namespace EA { namespace Audio {
bool Submix_s00a3_3ee0::DisconnectSendFromSubmix(rw::audio::core::PlugIn_s00a3_3ee0* plugin)
{
    if (!plugin)
        return false;
    if (plugin->mpDesc->guid != kGuidSend)
        return false;
    uint32_t it[2];
    mSendPlugins.Find(it, &plugin);
    if (it[0] == mSendPlugins.End())
        return false;
    mSendPlugins.Erase(it, it[0], it[1]);
    typedef void (__thiscall *Fn)(Submix_s00a3_3ee0*);
    ((Fn)vtbl[1])(this);
    {
        ScopedLock lock;
        rw::audio::core::PlugIn_s00a3_3ee0* none = 0;
        plugin->Connect(0, &none);
    }
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a34760
namespace EA { namespace Audio {
VoiceContainer_s00a3_3ee0::VoiceContainer_s00a3_3ee0()
{
    mpVoice = 0;
    mppPlugins = 0;
    mChain.mpEnd = (rw::audio::core::PlugInConfig_s00a3_3ee0*)((char*)this + 0x1c);
    mChain.mpBegin = mChain.mpEnd;
    mChain.mpCapacity = (rw::audio::core::PlugInConfig_s00a3_3ee0*)((char*)mChain.mpEnd + 0x168);
    mBindings.mpBegin = (tBinding_s00a3_3ee0*)((char*)this + 0x198);
    mBindings.mpEnd = mBindings.mpBegin;
    mBindings.mpCapacity = (tBinding_s00a3_3ee0*)((char*)mBindings.mpBegin + 0x708);
    mpSendBuf = (uint32_t*)((char*)this + 0x8b8);
    mpSendEnd = mpSendBuf;
    mpSendBegin = mpSendBuf;
    mpSendCap = (uint32_t*)((char*)mpSendBuf + 0x14);
    mpIdBuf = (uint32_t*)((char*)this + 0x8e4);
    mpIdEnd = mpIdBuf;
    mpIdBegin = mpIdBuf;
    mpIdCap = (uint32_t*)((char*)mpIdBuf + 0x78);
    mbCreated = false;
    mbConnected = false;
}
}}  // namespace EA::Audio

// @ 0x00a347f0
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::DisconnectFromSubmix(uint32_t submixId, rw::audio::core::PlugIn_s00a3_3ee0* plugin)
{
    mbConnected = false;
    if (submixId == 0)
        submixId = 0xf1cc1687;
    if (!plugin) {
        if (mChain.mpBegin == mChain.mpEnd)
            return false;
        int n = mChain.size();
        if (mChain[n - 1].plugInHandle->guid != kGuidSend)
            return false;
        plugin = mppPlugins[n - 1];
        if (!plugin)
            return false;
    }
    Submix_s00a3_3ee0* sm = GetSystemAT()->GetSubmix(submixId);
    if (!sm)
        return DisconnectFromMasteringVoice(plugin);
    sm->DisconnectSendFromSubmix(plugin);
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a34890
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::Disconnect()
{
    bool ok = true;
    if (mbConnected) {
        int n = mChain.size();
        int i = 0;
        if (0 < n) {
            int k = 0;
            int off = 0;
            do {
                if (((rw::audio::core::PlugInConfig_s00a3_3ee0*)((char*)mChain.mpBegin + off))->plugInHandle->guid == kGuidSend) {
                    uint32_t id = *(uint32_t*)(k + (int)mpSendBegin);
                    k += 4;
                    ok &= DisconnectFromSubmix(id, mppPlugins[i]);
                }
                off += 0xc;
                ++i;
            } while (i < n);
        }
        mbConnected = false;
    }
    return ok;
}
}}  // namespace EA::Audio

// @ 0x00a34930
namespace EA { namespace Audio {
void BindingVector::DoInsertValue(tBinding_s00a3_3ee0* position, const tBinding_s00a3_3ee0& value)
{
    if (mpEnd != mpCapacity) {
        const tBinding_s00a3_3ee0* pv = &value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd)
            *mpEnd = mpEnd[-1];
        tBinding_s00a3_3ee0* dst = mpEnd;
        tBinding_s00a3_3ee0* src = mpEnd - 1;
        while (src != position) {
            --src;
            --dst;
            *dst = *src;
        }
        *position = *pv;
        ++mpEnd;
    } else {
        int nPrev = (int)(mpEnd - mpBegin);
        int nNew = nPrev ? nPrev * 2 : 1;
        tBinding_s00a3_3ee0* const pNewData = 0;                 // fixed allocator: no overflow
        tBinding_s00a3_3ee0* pNewEnd = pNewData;
        pNewEnd = do_move_start(mpBegin, position, pNewEnd);
        if (pNewEnd)
            *pNewEnd = value;
        pNewEnd = do_move_start(position, mpEnd, pNewEnd + 1);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNew;
    }
}
}}  // namespace EA::Audio

// @ 0x00a34a10
namespace EA { namespace Audio {
bool Submix_s00a3_3ee0::ConnectSendToSubmix(rw::audio::core::PlugIn_s00a3_3ee0* plugin)
{
    if (!plugin)
        return false;
    if (plugin->mpDesc->guid != kGuidSend)
        return false;
    uint32_t it[2];
    mSendPlugins.Find(it, &plugin);
    if (it[0] != mSendPlugins.End())
        return false;
    mSendPlugins.Insert(it, &plugin, 0);
    typedef void (__thiscall *Fn)(Submix_s00a3_3ee0*);
    ((Fn)vtbl[0])(this);
    rw::audio::core::PlugIn_s00a3_3ee0* target = 0;
    if (!mbSendsEnabled) {
        target = *mVoiceContainer.mppPlugins;
    } else if (mbDefaultToMasterIfDisabled) {
        Submix_s00a3_3ee0* sm = GetSystemAT()->GetSubmix(mSendNameBegin);
        if (sm)
            target = *sm->mVoiceContainer.mppPlugins;
    }
    {
        ScopedLock lock;
        plugin->Connect(0, &target);
    }
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a34b50
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::ConnectToSubmix(uint32_t submixId, rw::audio::core::PlugIn_s00a3_3ee0* plugin)
{
    if (submixId == 0)
        submixId = 0xf1cc1687;
    if (!plugin) {
        int n = mChain.size();
        if (mChain[n - 1].plugInHandle->guid != kGuidSend)
            return false;
        plugin = mppPlugins[n - 1];
        if (!plugin)
            return false;
    }
    Submix_s00a3_3ee0* sm = GetSystemAT()->GetSubmix(submixId);
    if (!sm)
        return ConnectToMasteringVoice(plugin);
    if (sm->mVoiceContainer.mChain.mpBegin->plugInHandle->guid != kGuidSubmix)
        return false;
    sm->ConnectSendToSubmix(plugin);
    mbConnected = true;
    return true;
}
}}  // namespace EA::Audio

// @ 0x00a34bf0
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::Connect()
{
    int n = mChain.size();
    int i = 0;
    bool ok = true;
    if (0 < n) {
        int k = 0;
        int off = 0;
        do {
            if (((rw::audio::core::PlugInConfig_s00a3_3ee0*)((char*)mChain.mpBegin + off))->plugInHandle->guid == kGuidSend) {
                uint32_t id = *(uint32_t*)(k + (int)mpSendBegin);
                k += 4;
                ok &= ConnectToSubmix(id, mppPlugins[i]);
            }
            off += 0xc;
            ++i;
        } while (i < n);
    }
    mbConnected = true;
    return ok;
}
}}  // namespace EA::Audio

// @ 0x00a34c90
namespace EA { namespace Audio {
bool VoiceContainer_s00a3_3ee0::Reconnect()
{
    bool r = true;
    if (mbConnected) {
        Disconnect();
        r = Connect();
    }
    return r;
}
}}  // namespace EA::Audio
