// s00a33ee0: EA::Audio::VoiceContainer / Submix connection logic
#include "types.h"

namespace rw { namespace audio { namespace core {
struct PlugInDescRunTime { char pad[0x28]; uint32_t guid; };   // guid at +0x28
struct PlugInConfig {
    void* pConstructorParams;
    PlugInDescRunTime* plugInHandle;
    uint8_t outputChannels;
};
struct Voice { void Release(); };                               // 0x0112e950
struct PlugIn {
    char pad[0x10];
    PlugInDescRunTime* mpDesc;                                  // +0x10
    void Connect(int slot, void* value);                        // 0x0112ccc0
    bool GetAttribute(int attr, float* out);                    // 0x0112cc80
    bool SetAttribute(int attr, float value);                   // 0x0112ccf0
};
// Global audio lock (DAT_016e61a8)
struct System {
    void Enter();                                               // 0x0112c600
    void Leave();                                               // 0x0112c620
    PlugIn* GetMasteringVoice();                                // 0x00ff35d0
};
Voice* __cdecl CreateVoice(int flag, int numPlugins, PlugInConfig* configs, PlugIn*** outPlugins, System* sys);  // 0x0112e720
}}}
using namespace rw::audio::core;

extern System* g_pAudioSystem;   // 0x016e61a8

struct ScopedLock {
    ScopedLock() { System* s = g_pAudioSystem; if (s) s->Enter(); }
    ~ScopedLock() { System* s = g_pAudioSystem; if (s) s->Leave(); }
};

namespace EA { namespace Audio {

struct tBinding {
    uint32_t mProperty;     // +0
    uint32_t mPluginId;     // +4
    uint32_t mPluginGUID;   // +8
    int      mAttribute;    // +0xc
    float    mDefault;      // +0x10
    PlugIn*  mpPlugin;      // +0x14
    bool     mbFirst;       // +0x18
    float    mLast;         // +0x1c
    uint32_t mFlags;        // +0x20
};

struct Submix;
template<class T> struct RawVec {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
};
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
    virtual Submix* GetSubmix(uint32_t id);   // slot 95 (+0x17c)
};
AudioSystem* __cdecl GetSystemAT();         // 0x00a206f0

struct VoiceContainer {
    Voice*          mpVoice;                // +0
    PlugIn**        mppPlugins;             // +4
    RawVec<PlugInConfig> mChain;            // +8 (begin), +0xc (end), +0x10 (capacity)
    char            pad14[0x184 - 0x14];
    RawVec<tBinding> mBindings;             // +0x184 begin, +0x188 end, +0x18c capacity
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

    VoiceContainer();
    bool SetProperty(uint32_t prop, float value);
    bool GetProperty(uint32_t prop, float* out);
    void MaskPluginBindings(const uint32_t* props, int count);
    int  FindPluginIndex(uint32_t guid);
    PlugIn* FindPlugin(uint32_t guid);
    PlugIn* FindPluginIndexById(uint32_t id);
    bool Create(uint8_t flag);
    void Destroy();
    bool ConnectToMasteringVoice(PlugIn* plugin);
    bool DisconnectFromMasteringVoice(PlugIn* plugin);
    void DtorTail();
    bool DisconnectFromSubmix(uint32_t submixId, PlugIn* plugin);
    bool Disconnect();
    bool ConnectToSubmix(uint32_t submixId, PlugIn* plugin);
    bool Connect();
    bool Reconnect();
    bool AddPropertyBinding(uint32_t prop, uint32_t pluginId, uint32_t guid, int attr, const float* pDefault);
    void SetSendId(uint32_t id);
    bool HasPropertyBinding(uint32_t prop);
};

struct HashSetRaw {                          // eastl hash set of PlugIn*, reached at Submix+0x160c
    uint32_t pad[1];
    uint32_t* mpBuckets;                     // +4
    uint32_t mnBucketCount;                  // +8
    uint32_t End() { uint32_t* p = mpBuckets + mnBucketCount; return *p; }
    void* Find(uint32_t* outIter, PlugIn** key);                           // FUN_00a23ef0
    void  Erase(uint32_t* outIter, uint32_t node, uint32_t bucket);        // FUN_00a23db0
    void  Insert(uint32_t* outIter, PlugIn** key, uint32_t flag);          // FUN_00a26be0
};

struct Submix {
    void**          vtbl;
    char            pad4[0xc];
    VoiceContainer  mVoiceContainer;         // +0x10
    char            pad970[4];
    uint32_t        mSendNameBegin;          // +0x974
    char            pad978[0x15fc - 0x978];
    bool            mbDefaultToMasterIfDisabled;   // +0x15fc
    bool            mbSendsEnabled;                // +0x15fd
    char            pad15fe[0x160c - 0x15fe];
    HashSetRaw      mSendPlugins;            // +0x160c

    bool DisconnectSendFromSubmix(PlugIn* plugin);
    bool ConnectSendToSubmix(PlugIn* plugin);
};

// Plug-in chain helpers (inline in the original)
static inline int ChainCount(const VoiceContainer* c) { return (int)(c->mChain.mpEnd - c->mChain.mpBegin); }
static inline int BindCount(const VoiceContainer* c)  { return (int)(c->mBindings.mpEnd - c->mBindings.mpBegin); }

const uint32_t kGuidSend = 0x53656e30;     // 'Sen0'
const uint32_t kGuidSubmix = 0x53756230;   // 'Sub0'

// @ 0x00a33ee0
bool VoiceContainer::SetProperty(uint32_t prop, float value)
{
    int n = mBindings.size();
    int i = 0;
    if (0 < n) {
        tBinding* b = mBindings.mpBegin;
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

// @ 0x00a33fd0
bool VoiceContainer::GetProperty(uint32_t prop, float* out)
{
    int n = mBindings.size();
    int i = 0;
    if (0 < n) {
        tBinding* b = mBindings.mpBegin;
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

// @ 0x00a340b0
void VoiceContainer::MaskPluginBindings(const uint32_t* props, int count)
{
    int n = mBindings.size();
    if (0 < n) {
        int off = 0;
        do {
            uint32_t* pf = (uint32_t*)((int)&mBindings.mpBegin->mFlags + off);
            *pf &= 0xfffffffd;
            off += sizeof(tBinding);
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
            tBinding* b = mBindings.mpBegin;
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

// @ 0x00a341e0
int VoiceContainer::FindPluginIndex(uint32_t guid)
{
    int n = mChain.size();
    uint32_t i = 0;
    if (n != 0) {
        PlugInConfig* c = mChain.mpBegin;
        do {
            if (c->plugInHandle->guid == guid)
                return (int)i;
            ++i;
            ++c;
        } while (i < (uint32_t)n);
    }
    return -1;
}

// @ 0x00a34230
PlugIn* VoiceContainer::FindPlugin(uint32_t guid)
{
    int i = FindPluginIndex(guid);
    if (i < 0)
        return 0;
    return mppPlugins[i];
}

// @ 0x00a34260
PlugIn* VoiceContainer::FindPluginIndexById(uint32_t id)
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

// @ 0x00a342c0
bool VoiceContainer::Create(uint8_t flag)
{
    mbConnected = false;
    ScopedLock lock;
    mpVoice = CreateVoice(flag, ChainCount(this), mChain.mpBegin, &mppPlugins, g_pAudioSystem);
    if (!mpVoice)
        return false;
    int n = mBindings.size();
    for (int i = 0; i < n; ++i) {
        tBinding* b = &mBindings.mpBegin[i];
        b->mpPlugin = FindPluginIndexById(b->mPluginId);
    }
    mbCreated = true;
    return true;
}

// @ 0x00a343e0
void VoiceContainer::Destroy()
{
    int n = mBindings.size();
    if (n > 0) {
        int off = 0;
        do {
            *(PlugIn**)((int)&mBindings.mpBegin->mpPlugin + off) = 0;
            off += sizeof(tBinding);
        } while (--n);
    }
    if (mpVoice) {
        mpVoice->Release();
        mpVoice = 0;
    }
    mbCreated = false;
}

// @ 0x00a34440
bool VoiceContainer::ConnectToMasteringVoice(PlugIn* plugin)
{
    System* sys = g_pAudioSystem;
    if (!sys)
        return false;
    if (!plugin) {
        if (mChain.empty())
            return false;
        int n = mChain.size();
        PlugIn* last = mppPlugins[n - 1];
        if (mChain[n - 1].plugInHandle->guid != kGuidSend)
            return false;
        plugin = last;
    }
    ScopedLock lock;
    PlugIn* master = sys->GetMasteringVoice();
    plugin->Connect(0, &master);
    return true;
}

// @ 0x00a34530
bool VoiceContainer::DisconnectFromMasteringVoice(PlugIn* plugin)
{
    System* sys = g_pAudioSystem;
    if (!sys)
        return false;
    if (!plugin) {
        if (mChain.empty())
            return false;
        int n = mChain.size();
        PlugIn* last = mppPlugins[n - 1];
        if (mChain[n - 1].plugInHandle->guid != kGuidSend)
            return false;
        plugin = last;
    }
    ScopedLock lock;
    PlugIn* none = 0;
    plugin->Connect(0, &none);
    return true;
}

// @ 0x00a34620  (tail of ~VoiceContainer: release overflow buffers of the id vectors)
void VoiceContainer::DtorTail()
{
    uint32_t* p = mpIdBegin;
    if (p && p != mpIdBuf)
        operator delete(p);
    p = mpSendBegin;
    if (p && p != mpSendBuf)
        operator delete(p);
}

// @ 0x00a34660
bool Submix::DisconnectSendFromSubmix(PlugIn* plugin)
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
    typedef void (__thiscall *Fn)(Submix*);
    ((Fn)vtbl[1])(this);
    {
        ScopedLock lock;
        PlugIn* none = 0;
        plugin->Connect(0, &none);
    }
    return true;
}

// @ 0x00a34760
VoiceContainer::VoiceContainer()
{
    mpVoice = 0;
    mppPlugins = 0;
    mChain.mpEnd = (PlugInConfig*)((char*)this + 0x1c);
    mChain.mpBegin = mChain.mpEnd;
    mChain.mpCapacity = (PlugInConfig*)((char*)mChain.mpEnd + 0x168);
    mBindings.mpBegin = (tBinding*)((char*)this + 0x198);
    mBindings.mpEnd = mBindings.mpBegin;
    mBindings.mpCapacity = (tBinding*)((char*)mBindings.mpBegin + 0x708);
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

// @ 0x00a347f0  (PDB candidate: DisconnectFromSubmix)
bool VoiceContainer::DisconnectFromSubmix(uint32_t submixId, PlugIn* plugin)
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
    Submix* sm = GetSystemAT()->GetSubmix(submixId);
    if (!sm)
        return DisconnectFromMasteringVoice(plugin);
    sm->DisconnectSendFromSubmix(plugin);
    return true;
}

// @ 0x00a34890
bool VoiceContainer::Disconnect()
{
    bool ok = true;
    if (mbConnected) {
        int n = mChain.size();
        int i = 0;
        if (0 < n) {
            int k = 0;
            int off = 0;
            do {
                if (((PlugInConfig*)((char*)mChain.mpBegin + off))->plugInHandle->guid == kGuidSend) {
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

// vector<tBinding>::DoInsertValue (fixed_vector_allocator<36,50,4,0,0>)
struct BindingVector {
    tBinding* mpBegin;
    tBinding* mpEnd;
    tBinding* mpCapacity;
    void DoInsertValue(tBinding* position, const tBinding& value);
};
tBinding* __cdecl do_move_start(tBinding* first, tBinding* last, tBinding* result);   // 0x00a33d90

// @ 0x00a34930
void BindingVector::DoInsertValue(tBinding* position, const tBinding& value)
{
    if (mpEnd != mpCapacity) {
        const tBinding* pv = &value;
        if (pv >= position && pv < mpEnd)
            ++pv;
        if (mpEnd)
            *mpEnd = mpEnd[-1];
        tBinding* dst = mpEnd;
        tBinding* src = mpEnd - 1;
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
        tBinding* const pNewData = 0;                 // fixed allocator: no overflow
        tBinding* pNewEnd = pNewData;
        pNewEnd = do_move_start(mpBegin, position, pNewEnd);
        if (pNewEnd)
            *pNewEnd = value;
        pNewEnd = do_move_start(position, mpEnd, pNewEnd + 1);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNew;
    }
}

// @ 0x00a34a10
bool Submix::ConnectSendToSubmix(PlugIn* plugin)
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
    typedef void (__thiscall *Fn)(Submix*);
    ((Fn)vtbl[0])(this);
    PlugIn* target = 0;
    if (!mbSendsEnabled) {
        target = *mVoiceContainer.mppPlugins;
    } else if (mbDefaultToMasterIfDisabled) {
        Submix* sm = GetSystemAT()->GetSubmix(mSendNameBegin);
        if (sm)
            target = *sm->mVoiceContainer.mppPlugins;
    }
    {
        ScopedLock lock;
        plugin->Connect(0, &target);
    }
    return true;
}

// @ 0x00a34b50
bool VoiceContainer::ConnectToSubmix(uint32_t submixId, PlugIn* plugin)
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
    Submix* sm = GetSystemAT()->GetSubmix(submixId);
    if (!sm)
        return ConnectToMasteringVoice(plugin);
    if (sm->mVoiceContainer.mChain.mpBegin->plugInHandle->guid != kGuidSubmix)
        return false;
    sm->ConnectSendToSubmix(plugin);
    mbConnected = true;
    return true;
}

// @ 0x00a34bf0  (PDB candidate: VoiceContainer::Connect)
bool VoiceContainer::Connect()
{
    int n = mChain.size();
    int i = 0;
    bool ok = true;
    if (0 < n) {
        int k = 0;
        int off = 0;
        do {
            if (((PlugInConfig*)((char*)mChain.mpBegin + off))->plugInHandle->guid == kGuidSend) {
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

// @ 0x00a34c90
bool VoiceContainer::Reconnect()
{
    bool r = true;
    if (mbConnected) {
        Disconnect();
        r = Connect();
    }
    return r;
}


// @ 0x00a34cb0  (PDB candidate: AddPropertyBinding)
bool VoiceContainer::AddPropertyBinding(uint32_t prop, uint32_t pluginId, uint32_t guid, int attr, const float* pDefault)
{
    if (HasPropertyBinding(prop))
        return false;
    tBinding tmp;
    tmp.mProperty = 0;
    tmp.mPluginId = 0;
    tmp.mPluginGUID = 0;
    tmp.mAttribute = 0;
    tmp.mDefault = 0.0f;
    tmp.mpPlugin = 0;
    tmp.mbFirst = true;
    tmp.mLast = 0.0f;
    tmp.mFlags = 0;
    BindingVector* v = (BindingVector*)&mBindings.mpBegin;
    if (v->mpEnd < v->mpCapacity) {
        tBinding* p = v->mpEnd;
        v->mpEnd = p + 1;
        if (p)
            *p = tmp;
    } else {
        v->DoInsertValue(v->mpEnd, tmp);
    }
    tBinding* b = &mBindings.mpEnd[-1];
    b->mProperty = prop;
    b->mPluginId = pluginId;
    b->mPluginGUID = guid;
    b->mAttribute = attr;
    if (pDefault) {
        b->mDefault = *pDefault;
        b->mFlags |= 1;
    }
    return true;
}

}} // namespace EA::Audio

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

// @ 0x00a34d70
void EA::Audio::VoiceContainer::SetSendId(uint32_t id)
{
    U32Vec* v = (U32Vec*)&mpSendBegin;
    if (v->empty()) {
        v->push_back(id);
        return;
    }
    v->back() = id;
}

// ---------------------------------------------------------------------------
// SP::Audio::cEapdMessage
namespace EA { namespace Audio {
struct Command {
    uint32_t* EnumParameter(uint32_t* pOffset, uint32_t* pType, void* pUnused, int flags);   // 0x00a0f880
};
}}
namespace SP { namespace Audio {
struct cEapdMessage {
    EA::Audio::Command* mpCommand;      // +0
    uint32_t mValue;                    // +4
    uint32_t mOffset;                   // +8
    uint32_t mCurrentOffset;            // +0xc
    bool Init(EA::Audio::Command* cmd);
    bool GetNextFloat(float* out);
};

// @ 0x00a34dc0  (PDB candidate: cEapdMessage::Init)
bool cEapdMessage::Init(EA::Audio::Command* cmd)
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

// @ 0x00a34e30
bool cEapdMessage::GetNextFloat(float* out)
{
    uint32_t type;
    char unused[4];
    bool ok = false;
    uint32_t* p = mpCommand->EnumParameter(&mCurrentOffset, &type, unused, 0);
    if (p && type == 0x40fdffb) {
        *out = *(float*)p;
        return true;
    }
    return ok;
}
}}
