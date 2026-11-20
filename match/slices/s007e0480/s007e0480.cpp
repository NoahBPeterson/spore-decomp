// @ 0x007e0480
#include "game/types.h"
#include "cSPVector3.h"

namespace EA { namespace ArgScript {
struct cError {
    unsigned int mMessage[4];
    cError(const char* format, ...); // 0x0052df30
};
} }

// cl predeclares _CxxThrowException(void*, _ThrowInfo*) under /EH without __declspec(noreturn), so it is declared
// here through the same x86-cdecl decoration (the object symbol stays _CxxThrowException) with noreturn, which the
// original relies on: the copy block below is only reachable through the switch, never by falling out of the call.
extern "C" __declspec(noreturn) void __cdecl CxxThrowException(void* exceptionObject, void* throwInfo); // 0x011e0912
extern const unsigned char cErrorThrowInfo[]; // 0x014f9174

namespace SP {
struct cSplitModelKernelDescription {
    struct cSafeDynamicKernelStorage {
        int mKernelType;
        void* mKernelData;
        void* mKernelDataVariation;
        void SetOrigin(const cSPVector3& origin, const cSPVector3& variation);
    };
};
}

// @ 0x007e0480
void SP::cSplitModelKernelDescription::cSafeDynamicKernelStorage::SetOrigin(
    const cSPVector3& origin, const cSPVector3& variation)
{
    // Only the vector kernel types (1 and 2) keep an origin; both store it the same way.  The two case labels
    // keep separate bodies: written as one grouped label cl folds them into a range test, while the original
    // dispatches with the `sub eax,1 / je` chain and merges the identical tails afterwards.
    switch (mKernelType) {
    default: {
        EA::ArgScript::cError error(
            "Either type not specified or type does not support this parameter");
        CxxThrowException(&error, (void*)cErrorThrowInfo);
    }
    case 1:
        *static_cast<cSPVector3*>(mKernelData) = origin;
        *static_cast<cSPVector3*>(mKernelDataVariation) = variation;
        return;
    case 2:
        *static_cast<cSPVector3*>(mKernelData) = origin;
        *static_cast<cSPVector3*>(mKernelDataVariation) = variation;
        return;
    }
}
