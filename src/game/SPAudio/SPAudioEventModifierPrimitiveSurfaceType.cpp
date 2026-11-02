// src/game/SPAudio/SPAudioEventModifierPrimitiveSurfaceType.cpp -- migrated from slice(s) s00a3af80 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEventModifierPrimitiveSurfaceType.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/Command.h"
#include "EA/Audio/IConfiguration.h"
#include "EA/Audio/ResponseCurve.h"
#include "SP/Audio/cEventModifierPrimitive.h"
#include "SP/Audio/cListener.h"

// ---- items of slice s00a3af80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define V  virtual void CAT(pad_, __COUNTER__)();
#define V4 V V V V
namespace EA {
namespace Audio {
struct ResourceKey;
}
}
namespace EA {
namespace Audio {
struct IConfiguration_s00a3_af80;
}
}
namespace EA {
namespace Audio {
struct Command_s00a3_af80 {
    bool GetUint32(uint32 nKey, uint32* pValue);                             // 0x00a0fab0
};
}
}
namespace EA {
namespace Audio {
struct IConfiguration_s00a3_af80 {
    V
    virtual void Release();                                        // slot 1  +0x04
    V
    virtual void GetKeys(void* pKeys, int nFlags);                 // slot 3  +0x0c
    V4 V4 V4
    virtual char* GetDisplayName(uint32 nKey);                     // slot 16 +0x40
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitive_s00a3_af80 {
    void*  mpVtable;                             // +0x00
    int    mnRefCount;                           // +0x04
    uint32 mKeyInstance;                         // +0x08
    uint32 mKeyType;                             // +0x0c
    uint32 mKeyGroup;                            // +0x10
    EA::Audio::IConfiguration_s00a3_af80* mConfiguration;   // +0x14
    bool ReadTuningValues(const EA::Audio::ResourceKey* pKey);    // 0x00a3a610
    void Append(char* pDst, int nCapacity, char* pStr, bool bSep); // 0x00a3a4c0
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitiveSurfaceType : cEventModifierPrimitive_s00a3_af80 {
    void ModifyEvent(EA::Audio::Command_s00a3_af80* pCmd, uint32 a2, char* pDst, int nCapacity); // 0x00a3b9a0
};
}
}
// ---- items of slice s00a3af80 end

// @ 0x00a3b9a0
namespace SP { namespace Audio {
void cEventModifierPrimitiveSurfaceType::ModifyEvent( EA::Audio::Command_s00a3_af80* pCmd, uint32 a2, char* pDst, int nCapacity)
{
    uint32 v = 0;
    if (!pCmd->GetUint32(0x39fa376u, &v)) return;
    switch (v) {
    case 1u:           Append(pDst, nCapacity, (char*)"_wade", false);   return;
    case 2u:           Append(pDst, nCapacity, (char*)"_splash", false); return;
    case 3u:           Append(pDst, nCapacity, (char*)"_grass", false);  return;
    case 4u:           Append(pDst, nCapacity, (char*)"_ice", false);    return;
    case 5u:           Append(pDst, nCapacity, (char*)"_lava", false);   return;
    case 0x2fe99727u:  Append(pDst, nCapacity, (char*)"_sand", false);   return;
    case 0x7aab588au:  Append(pDst, nCapacity, (char*)"_wood", false);   return;
    case 0x7fd0653au:  Append(pDst, nCapacity, (char*)"_rock", false);   return;
    case 0x920790dfu:  Append(pDst, nCapacity, (char*)"_glass", false);  return;
    case 0x9375c65eu:  Append(pDst, nCapacity, (char*)"_metal", false);  return;
    default:           Append(pDst, nCapacity, (char*)"_dirt", false);   return;
    }
}
}}  // namespace SP::Audio
