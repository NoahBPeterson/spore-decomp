// src/game/SPGonzago/SPTerraformingManager.cpp -- migrated from slice(s) s00bbca30 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTerraformingManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_00b3d350();                       // SP::PlanetModel

// ---- items of slice s00bbca30 begin (TODO(rewrite): local stubs, replace by canonical classes)
class TObj {
public:
    // ---- reused __thiscall callees (addresses in comments) -------------------
    void* F_4df550(void*);              // 0x4df550  GetProfile(const Key&)
    void* F_c745d0(int, void*);         // 0xc745d0
    void* F_8414c0();                   // 0x8414c0
    void  F_c80680(int, void*);         // 0xc80680
    void  F_f921d0(int, int);           // 0xf921d0
    void  F_b2a750();                   // 0xb2a750
    void  F_bbc870(void* out, int a, void* b, int c);   // 0xbbc870
    void  F_bbc540(void* out, void* p);                 // 0xbbc540  UpdateCargoSlots
    void  F_bbc950(void* out, int a, int b, int c);     // 0xbbc950
    void  F_c70a00(float);                              // 0xc70a00
    void  F_c70a50(float);                              // 0xc70a50
    float F_c71d30();                                   // 0xc71d30
    void  F_c71da0(float);                              // 0xc71da0
    char  F_c70a70();                                   // 0xc70a70
    void  F_c70aa0(float);                              // 0xc70aa0
    void* F_c71e30();                                   // 0xc71e30
    void  F_c70de0(int);                                // 0xc70de0
    float F_fbda80();                                   // 0xfbda80
    void  F_fbddb0(float, float, void*);                // 0xfbddb0
    int   F_bbc670(int);                                // 0xbbc670
    char  F_c308b0();                                   // 0xc308b0
    void  F_ffaa90();                                   // 0xffaa90
    void  F_dd8640(int, int, int, int, int, int);       // 0xdd8640
    void* F_b1fdb0();                                   // 0xb1fdb0
    void  F_01034880();                                 // 0x1034880

    // ---- slice targets -------------------------------------------------------
    int*  FUN_00bbca30(int* out, int index, int planet);   // 0xbbca30
    void  FUN_00bbcb10(void* key, void* planet);           // 0xbbcb10
    char  FUN_00bbcb90(int param_1, int param_2);          // 0xbbcb90
    void  FUN_00bbcf00(void* planet, float f2, float f3, int param_4);  // 0xbbcf00
    void  FUN_00bbd0a0(int delta);                         // 0xbbd0a0
    int*  FUN_00bbd0e0(int* node, int param_3, int** param_4);  // 0xbbd0e0
};
template<class T> const T& MinT(const T& a, const T& b) { return a <= b ? a : b; }
extern "C" void* __cdecl FUN_00b3d350();                       // SP::PlanetModel
// ---- items of slice s00bbca30 end

// @ 0x00bbd0a0
void TObj::FUN_00bbd0a0(int delta)
{
    FUN_00b3d350();
    int cap = 2000;
    int& m = *(int*)((char*)this + 0x64);
    m = m + delta;
    m = MinT(m, cap);
}
