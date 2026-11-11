// @ 0x00e5add0
// Cell-stage value accessor: early-outs when the object is not ready, then returns the value
// the scene computes for it plus a tuning constant picked by that state.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct SceneObject {
    int mType;                  // +0x000
    char pad04[0xfc - 0x04];
    int mReady;                 // +0x0fc
    char pad100[0x248 - 0x100];
    int mLoaded;                // +0x248
    char pad24c[0x35c - 0x24c];
    int mState;                 // +0x35c
};

// Current level object (cApp at 0x016b3c04): its type at +0x411c and its state at +0x40fc
// are the two values compared with the object's own.
struct cApp {
    char pad0[0x40fc];
    int mState;                 // +0x40fc
    char pad4100[0x411c - 0x4100];
    int mType;                  // +0x411c
};

extern cApp* gApp;              // 0x016b3c04

float FUN_00e5acf0(SceneObject* o);   // 0x00e5acf0
int   FUN_00e57340(SceneObject* o);   // 0x00e57340

extern const float gZeroValue;  // 0x013ec4d0
extern const float gConstA;     // 0x013f7674
extern const float gConstB;     // 0x013f6b68
extern const float gConstC;     // 0x01473c70
extern const float gConstD;     // 0x014853e0

// @ 0x00e5add0
float FUN_00e5add0(SceneObject* o)
{
    if (o->mLoaded == 0)
        return 0.0f;
    if (o->mReady == 0)
        return 0.0f;
    if (o->mType == gApp->mType)
        return gZeroValue;

    float base = FUN_00e5acf0(o);
    int level = FUN_00e57340(o);

    if (o->mState == gApp->mState) {
        if (level >= 4)
            return base + gConstA;
        if (level >= 3)
            return base + gConstB;
        if (level >= 2)
            return base + gConstC;
        return base + gConstD;
    }
    if (level >= 4)
        return base + gConstD;
    if (level >= 3)
        return base + gConstC;
    return base + gConstB;
}
