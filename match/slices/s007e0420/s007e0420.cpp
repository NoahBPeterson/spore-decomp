// @ 0x007e0420
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
        void SetNormal(const cSPVector3& normal, const cSPVector3& variation);
    };
};
}

// @ 0x007e0420
void SP::cSplitModelKernelDescription::cSafeDynamicKernelStorage::SetNormal(
    const cSPVector3& normal, const cSPVector3& variation)
{
    if (mKernelType != 0) {
        EA::ArgScript::cError error(
            "Either type not specified or type does not support this parameter");
        _CxxThrowException(&error, cErrorThrowInfo);
    }
    *static_cast<cSPVector3*>(mKernelData) = normal;
    *static_cast<cSPVector3*>(mKernelDataVariation) = variation;
}
