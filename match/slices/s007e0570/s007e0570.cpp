// @ 0x007e0570
#include "game/types.h"
#include "cSPVector3.h"

namespace EA { namespace ArgScript {
struct cError {
    unsigned int mMessage[4];
    cError(const char* format, ...); // 0x0052df30
};
} }

__declspec(noreturn) void __stdcall _CxxThrowException(
    void* exceptionObject, const void* throwInfo); // 0x011e0912
extern const unsigned char cErrorThrowInfo[]; // 0x014f9174

namespace SP {
struct cSplitModelKernelDescription {
    struct cSafeDynamicKernelStorage {
        int mKernelType;
        void* mKernelData;
        void* mKernelDataVariation;
        void SetDirection(const cSPVector3& direction, const cSPVector3& variation);
    };
};
}

// @ 0x007e0570
void SP::cSplitModelKernelDescription::cSafeDynamicKernelStorage::SetDirection(
    const cSPVector3& direction, const cSPVector3& variation)
{
    switch (mKernelType) {
    default: {
        EA::ArgScript::cError error(
            "Either type not specified or type does not support this parameter");
        _CxxThrowException(&error, cErrorThrowInfo);
    }
    case 2:
        *reinterpret_cast<cSPVector3*>(static_cast<char*>(mKernelData) + 12) = direction;
        *reinterpret_cast<cSPVector3*>(static_cast<char*>(mKernelDataVariation) + 12) = variation;
        return;
    }
}
