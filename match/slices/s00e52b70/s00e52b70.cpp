// @ 0x00e52b70
// Cell-stage accessor: reads a mode from the current scene, then returns the matching float
// from the object the scene resolves for this frame (default value when no mode is set).
#include "types.h"

// Four-byte scratch value built and torn down around the lookup.
struct Temp {
    void* mPtr;
    void Init() throw();       // 0x00743b50
    void Destroy() throw();    // 0x00e82130
};

struct ResolvedValues {
    char pad0[0xfc];
    float mValue1;    // +0xfc
    float mValue2;    // +0x100
};
ResolvedValues* Resolve(Temp* temp);   // 0x00e4ce40

struct ModeHolder {
    char pad0[0x7c];
    int mMode;        // +0x7c
};

struct cApp {
    char pad0[0x5190];
    ModeHolder* mpModeHolder;   // +0x5190
};

extern cApp* gApp;                 // 0x016b3c04
extern float gDefaultValue;        // 0x013eecd8

// @ 0x00e52b70
float FUN_00e52b70()
{
    int mode = gApp->mpModeHolder->mMode;
    if (mode == 1) {
        Temp temp;
        temp.Init();
        float value = Resolve(&temp)->mValue1;
        temp.Destroy();
        return value;
    }
    if (mode == 2) {
        Temp temp;
        temp.Init();
        float value = Resolve(&temp)->mValue2;
        temp.Destroy();
        return value;
    }
    return gDefaultValue;
}
