// slice s00708f40: cLightingWorld global-state evaluation + cLightingManager ctor.
#include <new>
#include "types.h"

extern int g_lm_vtbl0;
extern int g_lm_vtbl1;
extern int g_lm_vtbl2;
extern int g_lm_vtbl3;
extern int g_lm_vtbl4;
extern float g_lm_f0;   // 0x1535980
extern float g_lm_f1;   // 0x1535984
extern float g_lm_f2;   // 0x1535988

struct LightingManager {
    void Init();
};

// @ 0x00709c40
void LightingManager::Init()
{
    char* p = (char*)this;
    int z = 0;
    *(void**)(p + 4) = &g_lm_vtbl0;
    *(void**)(p + 8) = &g_lm_vtbl1;
    *(int*)(p + 0xc) = z;
    *(void**)(p) = &g_lm_vtbl2;
    *(void**)(p + 4) = &g_lm_vtbl3;
    *(void**)(p + 8) = &g_lm_vtbl4;
    *(int*)(p + 0x10) = 4;
    *(int*)(p + 0x14) = 0x10;
    *(int*)(p + 0x18) = z;
    *(int*)(p + 0x1c) = z;
    *(int*)(p + 0x20) = z;
    *(int*)(p + 0x34) = z;
    *(int*)(p + 0x38) = z;
    *(int*)(p + 0x3c) = z;
    void** q = (void**)(p + 0x30);
    *q = q;
    *(void**)(p + 0x34) = q;
    *(int*)(p + 0x38) = z;
    *(char*)(p + 0x3c) = (char)z;
    *(int*)(p + 0x40) = z;
    *(float*)(p + 0x48) = g_lm_f0;
    *(float*)(p + 0x4c) = g_lm_f1;
    *(float*)(p + 0x50) = g_lm_f2;
    *(int*)(p + 0x54) = z;
}

// ===========================================================================
// Large lighting state evaluators (not reconstructed; see partial.txt)
// ===========================================================================
struct cLightingWorld {
    void ApplyGlobalState(int* state);
    void UpdateGlobalSamples(int* state);
};

// @ 0x00708f40
void cLightingWorld::ApplyGlobalState(int* state)
{
    (void)state;
}

// @ 0x007094c0
void cLightingWorld::UpdateGlobalSamples(int* state)
{
    (void)state;
}
