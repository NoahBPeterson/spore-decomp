// src/game/SPAudio/SPAudioEapdMessage.cpp -- migrated from slice(s) s00a33ee0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEapdMessage.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/Command.h"
#include "EA/Audio/Submix.h"
#include "EA/Audio/System.h"
#include "EA/Audio/VoiceContainer.h"

// ---- items of slice s00a33ee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
struct Command_s00a3_3ee0 {
    uint32_t* EnumParameter(uint32_t* pOffset, uint32_t* pType, void* pUnused, int flags);   // 0x00a0f880
};
}
}
namespace SP {
namespace Audio {
struct cEapdMessage {
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

// @ 0x00a34e30
namespace SP { namespace Audio {
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
}}  // namespace SP::Audio
