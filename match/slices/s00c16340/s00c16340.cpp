// s00c16340 -- terrain "wave height" helper.
//
// flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// Object with the virtual at vtable+0x24 (slot 9): takes (resource id, void**
// out) and returns bool.  The same object type is returned by the Fn1 lookup.
struct GameModeObj {
    virtual bool vf0();
    virtual bool vf1();
    virtual bool vf2();
    virtual bool vf3();
    virtual bool vf4();
    virtual bool vf5();
    virtual bool vf6();
    virtual bool vf7();
    virtual bool vf8();
    virtual bool vf9(int id, void** out);
    GameModeObj* Fn1(void* mode, int flag);
};

// Object handed back through the vf9 out-parameter; the property read is a
// member at 0x41ea70 (SP::GetPropertyAsFloat).
struct PropObj {
    float* GetFloat();
};

struct TerrainObj {
    char pad_e58[0xe58];
    float f_e58;
    void ApplyWave(float v);                                             // 0x00c15dc0
};

extern "C" GameModeObj* __cdecl FUN_00b5b800();                          // SP::GetCurrentGameMode
extern "C" GameModeObj* __cdecl FUN_00b3d320();                          // global game-mode getter

// @ 0x00c16340
double FUN_00c16340(float param_1, TerrainObj* param_2)
{
    GameModeObj* p = FUN_00b3d320()->Fn1(FUN_00b5b800(), 1);
    float f = 100.0f;
    if (p != 0) {
        PropObj* out;
        if (p->vf9(0x7422b3b, (void**)&out) && *(int16_t*)((char*)out + 0x12) == 0xd) {
            f = *out->GetFloat();
        }
    }
    float v = param_1;
    if (f * param_1 > param_2->f_e58) {
        v = param_2->f_e58 / f;
    }
    param_2->ApplyWave(v * f);
    return (double)param_1 - (double)v;
}
