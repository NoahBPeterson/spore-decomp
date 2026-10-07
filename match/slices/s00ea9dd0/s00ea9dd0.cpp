// Slice s00ea9dd0 (op3_mid slice 141): this file holds
//   0x00EA9DD0  SP::Audio::cMixModeManager::HandleMessage   (2538 bytes, __thiscall, ret 8)
//
// Maps game messages to audio mix modes: most messages start (0x00ea9a40) or stop
// (0x00ea9a80) one named mix mode; a few look the mode up in one of three global
// message-key -> mix-mode sorted maps (0x016c7144 / 0x016c715c / 0x016c7174), switch the
// "context" mode kept in mCurrentContext (+0x60), or set the retail-only flag at +0x68.
// Returns true for every handled message, false otherwise.
// Helper names (StartMixMode/StopMixMode/IsMixModeActive) are descriptive: they are the
// out-of-line hash_map lookups + cMixMode::Start / stop / is-active calls.
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#pragma warning(disable: 4100)

namespace SP { namespace Audio {

struct cMixMode {
    void Start();                                       // 0x00ea8f90 (cMixMode::Start)
};

template <class T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
};

struct ModeNode {
    uint32_t first;
    AutoRefCount<cMixMode> second;
    ModeNode* mpNext;
};

struct ModeIterator {
    ModeNode* mpNode;
    ModeNode** mpBucket;
    ModeNode* operator->() const { return mpNode; }
};

// eastl::hash_map<unsigned int, AutoRefCount<cMixMode>> (0x20 bytes)
struct ModeHashMap {
    uint32_t mRehashPolicy;
    ModeNode** mpBucketArray;                           // +0x04
    uint32_t mnBucketCount;                             // +0x08
    uint32_t mnElementCount;
    char mAllocator[0x10];
    ModeIterator find(const uint32_t& key) const;       // 0x00645ed0 (ICF-shared hashtable::find)
    ModeNode* end_node() const { return mpBucketArray[mnBucketCount]; }
};

// Sorted message-key -> mix-mode-id maps (eastl::vector_map<uint32_t, uint32_t>).
struct KeyModePair { uint32_t first; uint32_t second; };
struct MessageModeMap {
    KeyModePair* mpBegin;
    KeyModePair* mpEnd;
    KeyModePair* mpCapacity;
    char mAllocator[0x8];
    KeyModePair* find(const uint32_t& key);             // 0x00ea9bb0
    KeyModePair* end() const { return mpEnd; }
};
extern MessageModeMap sMessageModes1;                   // 0x016c7144
extern MessageModeMap sMessageModes2;                   // 0x016c715c
extern MessageModeMap sMessageModes3;                   // 0x016c7174

struct cAudioSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void SetPause(float value);                 // +0x18
};

struct cGameStateD0 { char pad[0xd0]; int mValueD0; };
extern cGameStateD0* gGameState16c7aa4;                 // 0x016c7aa4

} // namespace Audio
Audio::cAudioSystem* AudioSystem();                     // 0x0067cb00 (SP::AudioSystem)

namespace Audio {

class cMixModeManager {
public:
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);
    void StartMixMode(uint32_t id);                     // 0x00ea9a40
    void StopMixMode(uint32_t id, bool flag);           // 0x00ea9a80
    bool IsMixModeActive(uint32_t id);                  // 0x00ea9ac0

    char pad04[0x8];
    ModeHashMap mModes;                                 // +0x0c
    char pad2c[0x60 - 0x2c];
    uint32_t mCurrentContext;                           // +0x60
    uint32_t mCurrentPauseElements;                     // +0x64
    bool mbFlag68;                                      // +0x68 (retail only)
};

bool cMixModeManager::HandleMessage(uint32_t messageID, void* pMessage)
{
    uint32_t* msg = (uint32_t*)pMessage;
    switch (messageID) {
    case 0x238de9c:
        StopMixMode(0xcc2efa4a, false);
        return true;
    case 0x22d1adc: {
        StopMixMode(0x3ed3bf9, false);
        uint32_t key = msg[2];
        KeyModePair* it = sMessageModes1.find(key);
        if (it == sMessageModes1.end())
            return true;
        uint32_t mode = it->second;
        if (mbFlag68 || key != 0x2ccd1d2 || mode != 0xf9fe9926)
            StartMixMode(mode);
        if (mode == 0xa7cf8068) {
            if (!gGameState16c7aa4)
                return true;
            if (gGameState16c7aa4->mValueD0 == 0) {
                if (IsMixModeActive(0x2d329d5f))
                    StopMixMode(0x2d329d5f, false);
                StartMixMode(0x1a27f146);
            }
            else {
                if (IsMixModeActive(0x1a27f146))
                    StopMixMode(0x1a27f146, false);
                StartMixMode(0x2d329d5f);
            }
            return true;
        }
        if (IsMixModeActive(0x2d329d5f))
            StopMixMode(0x2d329d5f, false);
        if (IsMixModeActive(0x1a27f146))
            StopMixMode(0x1a27f146, false);
        return true;
    }
    case 0x212d3e7: {
        uint32_t key = msg[4];
        KeyModePair* it = sMessageModes1.find(key);
        if (it != sMessageModes1.end()) {
            uint32_t mode = it->second;
            StopMixMode(mode, false);
            if (mode == 0x69676f4d)
                StopMixMode(mCurrentContext, false);
        }
        StartMixMode(0x3ed3bf9);
        AudioSystem()->SetPause(0.0f);
        return true;
    }
    case 0x248975f:
        StopMixMode(mCurrentContext, false);
        StartMixMode(0xc2b96aae);
        mCurrentContext = 0xc2b96aae;
        return true;
    case 0x248976a:
        StopMixMode(mCurrentContext, false);
        StartMixMode(0xd69af078);
        mCurrentContext = 0xd69af078;
        return true;
    case 0x2489766:
        StopMixMode(mCurrentContext, false);
        StartMixMode(0x79e526cb);
        mCurrentContext = 0x79e526cb;
        return true;
    case 0x3867294:
        if (pMessage)
            StartMixMode(0xa1638df0);
        else
            StopMixMode(0xa1638df0, false);
        return true;
    case 0x3e9a620:
        StartMixMode(0xf8bfa142);
        return true;
    case 0x3ac86ad:
        StartMixMode(0x2a04d2ef);
        return true;
    case 0x3e9a625:
        StopMixMode(0xf8bfa142, false);
        return true;
    case 0x47d2b68: {
        uint32_t key = msg[0];
        KeyModePair* it = sMessageModes2.find(key);
        if (it != sMessageModes2.end())
            StopMixMode(it->second, false);
        StopMixMode(0xc3b6e28f, false);
        return true;
    }
    case 0x4471c60:
        StopMixMode(0x38432c22, false);
        return true;
    case 0x47d7cc5:
        StartMixMode(0xed1b527e);
        return true;
    case 0x49731a9:
        StartMixMode(0x321723de);
        return true;
    case 0x490a868: {
        StartMixMode(0xc3b6e28f);
        uint32_t key = msg[0];
        KeyModePair* it = sMessageModes2.find(key);
        if (it != sMessageModes2.end())
            StartMixMode(it->second);
        return true;
    }
    case 0x47d7cc6:
        StopMixMode(0xed1b527e, false);
        return true;
    case 0x49731ad:
        StopMixMode(0x321723de, false);
        return true;
    case 0x4a07018:
        StartMixMode(0x38432c22);
        return true;
    case 0x49790b2:
        StartMixMode(0xcc2efa4a);
        return true;
    case 0x4c7032b:
        StartMixMode(0x41601d81);
        return true;
    case 0x4c70cc0:
        StartMixMode(0xb667073e);
        return true;
    case 0x4c703a5:
        StopMixMode(0x41601d81, false);
        return true;
    case 0x4c70ce5:
        StopMixMode(0xb667073e, false);
        return true;
    case 0x4fd2bd3:
        StopMixMode(0xb6755dd6, false);
        return true;
    case 0x4fd2bce:
        StartMixMode(0xb6755dd6);
        return true;
    case 0x539a4ce: {
        ModeIterator it = mModes.find(0xe50be14b);
        if (it.mpNode != mModes.end_node())
            it->second->Start();
        return true;
    }
    case 0x5b07bda:
        StartMixMode(0x47395ae5);
        return true;
    case 0x546bbb8:
        if (pMessage)
            StartMixMode(0x1dfbe8cc);
        else
            StopMixMode(0x1dfbe8cc, false);
        return true;
    case 0x539a4cf:
        StopMixMode(0xe50be14b, false);
        return true;
    case 0x5b07be5:
        StopMixMode(0x47395ae5, false);
        return true;
    case 0x5c81b25:
        StopMixMode(0xdf1030f7, false);
        return true;
    case 0x5c81b19:
        StartMixMode(0xdf1030f7);
        return true;
    case 0x5e902d3:
        StopMixMode(0xcdde2d78, false);
        return true;
    case 0x604c6e0:
        StartMixMode(0x4bbc71ca);
        return true;
    case 0x604a973:
        StartMixMode(0xcdde2d78);
        return true;
    case 0x604c6f4:
        StopMixMode(0x4bbc71ca, false);
        return true;
    case 0x604d85d:
        StopMixMode(0xf3f05329, false);
        return true;
    case 0x604d856:
        StartMixMode(0xf3f05329);
        return true;
    case 0x60c8707: {
        uint32_t key = msg[2];
        KeyModePair* it = sMessageModes3.find(key);
        if (it != sMessageModes3.end())
            StartMixMode(it->second);
        return true;
    }
    case 0x6202731:
        StopMixMode(0x577eef2b, false);
        StartMixMode(0xcbc1c57);
        return true;
    case 0x61d72de:
        StopMixMode(0x321723de, true);
        return true;
    case 0x60c874f: {
        uint32_t key = msg[2];
        KeyModePair* it = sMessageModes3.find(key);
        if (it != sMessageModes3.end())
            StopMixMode(it->second, false);
        return true;
    }
    case 0x66f8f25:
        StartMixMode(0xf9fe9926);
        mbFlag68 = true;
        return true;
    case 0x695d2ed:
        StartMixMode(0xcbc1c57);
        return true;
    case 0x691a1c3:
        StopMixMode(0xcbc1c57, false);
        StartMixMode(0x577eef2b);
        return true;
    case 0x695d2f5:
        StopMixMode(0xcbc1c57, false);
        return true;
    case 0x74baf67: {
        uint32_t startIndex = msg[2];
        uint32_t stopIndex = msg[4];
        uint32_t modes[3] = { 0x2e1a0bf7, 0x2d329d5f, 0x1fec7fdf };
        if (stopIndex < 3)
            StopMixMode(modes[stopIndex], false);
        if (startIndex < 3)
            StartMixMode(modes[startIndex]);
        return true;
    }
    case 0x3ac86b5:
    case 0x69c3314:
        StopMixMode(0x2a04d2ef, false);
        return true;
    case 0x7c7686f:
        StartMixMode(0xcc2efa4a);
        StartMixMode(0xf9fe9926);
        mbFlag68 = true;
        return true;
    case 0x7e36045:
        if (!pMessage)
            StopMixMode(0xfff641ab, false);
        else
            StopMixMode(0x250fc692, false);
        return true;
    case 0x7e36032:
        if (!pMessage)
            StartMixMode(0xfff641ab);
        else
            StartMixMode(0x250fc692);
        return true;
    }
    return false;
}

}} // namespace SP::Audio
