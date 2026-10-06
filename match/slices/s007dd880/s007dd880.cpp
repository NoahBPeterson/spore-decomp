// Slice s007dd880 (w2g5 slice 23).  Region: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast.
// The single function here is SP::cSmoothCameraController::ConfigUpdated, a
// ~3.9 KB property-driven reconfiguration.  Only a skeleton is provided.
#include "types.h"

struct cSmoothCameraController_Config {
    void ConfigUpdated();
};

void cSmoothCameraController_Config::ConfigUpdated()
{
    // 0x007dd880: full config re-read (3907 bytes) not reproduced.
}
