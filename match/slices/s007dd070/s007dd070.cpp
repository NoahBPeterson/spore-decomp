// Slice s007dd070 (w2g5 slice 22).  Region: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast.
// The single function here is SP::cSmoothCameraController::Update, a ~2 KB
// per-frame camera update.  Only a skeleton is provided (see partial.txt).
#include "types.h"

struct cSmoothCameraController_Update {
    void Update(float dt);
};

void cSmoothCameraController_Update::Update(float dt)
{
    // 0x007dd070: full per-frame camera update (2049 bytes) not reproduced.
    (void)dt;
}
