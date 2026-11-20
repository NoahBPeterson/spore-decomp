// @ 0x007e04f0
// Built like the rest of SPAppSplitModelDescription.obj: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
// (/arch:SSE is what makes the two float stores `movss` instead of x87 `fld`/`fstp`).
#include "game/types.h"

namespace EA { namespace ArgScript {
struct cError {
    unsigned int mMessage[4];
    cError(const char* format, ...); // 0x0052df30
};
} }

// cl predeclares _CxxThrowException(void*, _ThrowInfo*) under /EH without __declspec(noreturn); declaring it here
// through the same x86-stdcall decoration (the object symbol stays _CxxThrowException) adds noreturn, which the
// original relies on: the copy blocks below are only reachable through the switch, never by falling out of the call.
__declspec(noreturn) void __stdcall _CxxThrowException(
    void* exceptionObject, const void* throwInfo); // 0x011e0912
extern const unsigned char cErrorThrowInfo[]; // 0x014f9174

namespace SP {
struct cSplitModelKernelDescription {
    struct cSafeDynamicKernelStorage {
        int mKernelType;
        void* mKernelData;
        void* mKernelDataVariation;
        void SetRadius(float radius, float variation);
    };
};
}

// @ 0x007e04f0
void SP::cSplitModelKernelDescription::cSafeDynamicKernelStorage::SetRadius(
    float radius, float variation)
{
    switch (mKernelType) {
    default: {
        EA::ArgScript::cError error(
            "Either type not specified or type does not support this parameter");
        _CxxThrowException(&error, cErrorThrowInfo);
    }
    case 2:
        *reinterpret_cast<float*>(static_cast<char*>(mKernelData) + 0x18) = radius;
        *reinterpret_cast<float*>(static_cast<char*>(mKernelDataVariation) + 0x18) = variation;
        return;
    case 1:
        *reinterpret_cast<float*>(static_cast<char*>(mKernelData) + 0x0c) = radius;
        *reinterpret_cast<float*>(static_cast<char*>(mKernelDataVariation) + 0x0c) = variation;
        return;
    }
}
