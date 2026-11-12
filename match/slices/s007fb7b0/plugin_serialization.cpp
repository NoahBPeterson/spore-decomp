#include "cSPUIWinProc.h"
#include "EA/UTFWin/SerInfo.h"
#include "EA/UTFWin/SerTypeInfo.h"

extern EA::UTFWin::SerTypeInfo gPluginSerTypeInfo; // 0x014159d4

// The serialization entry receives the ISerializable subobject at owner + 4.
class cSPUIPluginProc : public cSPUIWinProc {
public:
    virtual void GetSerializationInfo(EA::UTFWin::SerInfo& info);
};

typedef char PluginInfoSize[sizeof(EA::UTFWin::SerInfo) == 0x10 ? 1 : -1];
typedef char PluginDescriptorSize[sizeof(EA::UTFWin::SerTypeInfo) == 0x20 ? 1 : -1];
typedef char PluginObjectSize[sizeof(cSPUIPluginProc) == 0x18 ? 1 : -1];

// @ 0x007fbed0
void cSPUIPluginProc::GetSerializationInfo(EA::UTFWin::SerInfo& info)
{
    info.mpType = &gPluginSerTypeInfo;
    info.mpBase = this;
    info.mCount = 1;
    info.mClassId = GetClassId();
}
