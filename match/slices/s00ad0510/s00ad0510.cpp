// Slice s00ad0510 - SP city visualizer helpers.
#include "types.h"

class cPlanetModel;
struct NounThing;

extern "C" {
    void* __stdcall PlanetModel(void* out, int a, int b, int c, int d, int e, int f); // 0xb3d350
    void* __stdcall AudioNounManager(int x);                                        // 0xb3d300
    int   __cdecl FUN_b23940(void* x);                                              // 0xb23940
    int   __cdecl FUN_c099e0(int a, int b, int c, int d, int e, int f);             // 0xc099e0
}

class cPlanetModel {
public:
    int DirectionToSurfacePosition();   // 0xb815a0
};

class CityVisualizer {
public:
    int FuncACEBD0(int a, int b);       // 0xacebd0
    int Ad0510(int param1, int param2); // @ 0xad0510
};

int CityVisualizer::Ad0510(int param1, int param2)
{
    uint32_t local[3];
    cPlanetModel* m = (cPlanetModel*)PlanetModel(local, param2, param1, 1, 0, 0, 0);
    int r = m->DirectionToSurfacePosition();
    void* n = AudioNounManager(r);
    int esi = FUN_b23940(n);
    if (!esi)
        return 0;
    int edi = FUN_c099e0(param2, param1, 1, esi, 0, 1);
    FuncACEBD0(esi, 0);
    return edi;
}

// ---- remaining functions (skeletons) ----------------------------------------
extern "C" int __cdecl Placeholder_590() { return 0; }
extern "C" int __cdecl Placeholder_710() { return 0; }
extern "C" int __cdecl Placeholder_8f0() { return 0; }
extern "C" int __cdecl Placeholder_b30() { return 0; }
extern "C" int __cdecl Placeholder_bd0() { return 0; }
extern "C" int __cdecl Placeholder_ca0() { return 0; }
extern "C" int __cdecl Placeholder_d90() { return 0; }
extern "C" int __cdecl Placeholder_1000() { return 0; }
extern "C" int __cdecl Placeholder_11f0() { return 0; }