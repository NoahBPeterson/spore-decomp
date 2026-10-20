// src/game/SPAudio/SPAudioEventModifierPrimitive.cpp -- migrated from slice(s) s00a39ce0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEventModifierPrimitive.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Audio/cEventModifierPrimitive.h"
#include "EA/Audio/Command.h"
#include "EA/Audio/IConfiguration.h"
#include "EA/Audio/ResponseCurve.h"
#include "SP/Audio/cEventModifier.h"
#include <ctype.h>
#include <string.h>

// ---- items of slice s00a39ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define V virtual void CAT(pad_, __COUNTER__)();
#define V4 V V V V
#define V16 V4 V4 V4 V4
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
namespace EA {
struct Property {
    uint32_t* mpData;
    int mPad;
    int mnCount;
    int mnSize;
    uint16_t mnFlags;
    uint16_t mnType;
};
}
namespace EA {
struct RbNode {
    RbNode* mpRight;
    RbNode* mpLeft;
    RbNode* mpParent;
    uint32_t mColor;
    uint32_t mKey;
};
}
namespace EA {
struct RbAnchorNode {
    RbNode* mpRight;
    RbNode* mpLeft;
    RbNode* mpParent;
    uint32_t mColor;
};
}
namespace EA {
struct RbTreeData {
    int mAlloc;
    RbAnchorNode mAnchor;
    int mnSize;
    RbNode*& mpRight_() { return mAnchor.mpRight; }
    RbTreeData() : mAnchor() {
        mAnchor.mpRight = (RbNode*)&mAnchor;
        mAnchor.mpLeft = (RbNode*)&mAnchor;
        mAnchor.mpParent = 0;
        *(uint8_t*)&mAnchor.mColor = 0;
        mnSize = 0;
    }
    void DoNukeSubtree(RbNode* node);   // 0x009a9600
};
}
namespace EA {
struct IConfiguration {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual void GetKeys(RbTreeData* out, int flags);
    V V V
    virtual void GetProperty(uint32_t key, Property*& out);
    V4 V4
    virtual const char* GetString(uint32_t key);
};
}
namespace EA {
struct AutoRefConfig {
    IConfiguration* mp;
    AutoRefConfig() : mp(0) {}
    ~AutoRefConfig() { if (mp) mp->Release(); }
    void Reset() {
        IConfiguration* p = mp;
        if (p) {
            mp = 0;
            p->Release();
        }
    }
};
}
namespace EA {
uint32_t FNV1_String8(const char* s, uint32_t seed, int flag);
}
namespace EA {
namespace Audio {
struct Command_s00a3_9ce0 {
    bool GetUint32(uint32_t key, uint32_t* out);  // 0x00a0fab0 (EA::Audio::Command::GetUint32)
    bool GetFloat(uint32_t key, float* out);   // 0x00a0fa70 (named GetBool in symbols; reads a float)
    void SetFloat(uint32_t key, float v);  // 0x00a0fd30 (EA::Audio::Command::SetFloat)
};
}
}
namespace EA {
namespace Audio {
struct AudioSystem {
    V16 V16 V16 V4 V4 V V V
    virtual char* GetFootName(uint32_t id);   // slot 59, +0xec
    virtual void unused60();
    virtual uint32_t HashName(const char* s);       // slot 61, +0xf4
    V16
    virtual bool GetConfiguration(uint32_t instance, AutoRefConfig* out, uint32_t group);   // slot 78, +0x138
};
}
}
namespace EA {
namespace Audio {
AudioSystem* GetSystemAT();
}
}
namespace SP {
namespace Audio {
using namespace EA;
}
}
namespace SP {
namespace Audio {
using namespace EA::Audio;
}
}
namespace SP {
namespace Audio {
struct IEventModifier {
    virtual ~IEventModifier() {}
    virtual bool Init() = 0;
    virtual void pad2() = 0;
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity) = 0;
    virtual bool ReadTuningValues(const ResourceKey* key) = 0;
};
}
}
namespace SP {
namespace Audio {
struct RefCountBase {
    int mRefCount;   // +4 (after the vptr)
    RefCountBase() : mRefCount(0) {}
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitive_s00a3_9ce0 : RefCountBase, IEventModifier {
    ResourceKey mKey;               // +8
    AutoRefConfig mConfiguration;   // +0x14

    cEventModifierPrimitive_s00a3_9ce0(const char* name)
        : mKey(FNV1_String8(name, 0x811c9dc5, 1), 0x2b9f662, 0x21407ee), mConfiguration() {}
    virtual bool Init();                                    // 0xa3a4b0
    virtual void pad2();
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity);
    virtual bool ReadTuningValues(const ResourceKey* key);  // 0xa3a610
    virtual int AddRef();
    virtual int Release();
    __declspec(noinline) void Append(char* dst, int capacity, char* str, bool sep);   // 0xa3a4c0
};
}
}
// ---- items of slice s00a39ce0 end

// @ 0x00a3a4b0
bool SP::Audio::cEventModifierPrimitive::Init()
{
    ReadTuningValues(mKey);
    return true;
}

// @ 0x00a3a4c0
namespace SP { namespace Audio {
void cEventModifierPrimitive_s00a3_9ce0::Append(char* dst, int capacity, char* str, bool sep)
{
    unsigned dstLen = strlen(dst);
    int n = (strlen(str) + sep) ? 1 : (int)dstLen;
    if (n < capacity) {
        if (sep) dst[dstLen++] = '_';
        strcpy(dst + dstLen, str);
    }
}
}}  // namespace SP::Audio

// @ 0x00a3a610
namespace SP { namespace Audio {
bool cEventModifierPrimitive_s00a3_9ce0::ReadTuningValues(const ResourceKey* key)
{
    if (key->instanceID == mKey.instanceID && key->typeID == mKey.typeID &&
        key->groupID == mKey.groupID) {
        AudioSystem* sys = GetSystemAT();
        mConfiguration.Reset();
        return sys->GetConfiguration(mKey.instanceID, &mConfiguration, 0x21407ee);
    }
    return false;
}
}}  // namespace SP::Audio
