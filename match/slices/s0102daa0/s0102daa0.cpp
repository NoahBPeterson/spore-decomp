// s0102daa0.cpp -- gold6 batch, worker 25
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Partial reconstruction of FUN_0102daa0 (0x0102daa0, 1138 bytes).  The routine
// rebuilds the global "requested planets" SPVector<unsigned> at 0x016decac..b4.
// Only the vector-clear prologue is reconstructed here; the remainder is left
// unemitted (see partial.txt for the full description of what was analysed).

#include "types.h"

typedef unsigned int uint;

// 0x011e0744 -- the image's memcpy/memmove helper.
extern "C" void* FUN_011e0744(void* dst, const void* src, size_t n);

// 0x016decac: SPVector<unsigned> of requested-planet ids (begin/end/capacity).
extern unsigned* g_pPlanetsBegin;   // 0x016decac
extern unsigned* g_pPlanetsEnd;     // 0x016decb0
extern unsigned* g_pPlanetsCap;     // 0x016decb4

// The routine is a cdecl function taking one object whose GetAvatar/GetCities
// members are invoked with `this` in ecx.
struct cGameNounManager {
    cGameNounManager* GetAvatar();                  // 0x00b1fdb0
    void*             GetCities(void* a = 0, void* b = 0);   // 0x005c65e0
};

// @ 0x0102daa0
void FUN_0102daa0(cGameNounManager* param_1) {
    // Phase 0 (0x0102daa3..0x0102dada): erase(begin, end) of the global vector.
    FUN_011e0744(g_pPlanetsBegin, g_pPlanetsEnd, 0);
    g_pPlanetsEnd = g_pPlanetsEnd - (g_pPlanetsEnd - g_pPlanetsBegin);

    // Phase 1..N: not reconstructed.  The original gathers a civilization list
    // (GetAvatar / GetUFOSimulator / GetMaxTravelDistance / GetCities /
    // StarManager / GetStarRecords), maintains an inlined eastl rbtree /
    // CivCounterMap keyed by avatar with per-civilization nearest-city distance
    // selection, calls FUN_01000660, runs the FUN_00bba790 / FUN_00b8dab0==5 /
    // cStarRecordRef::GetCommContext scan that appends to the global vector via
    // SPVector<unsigned>::DoInsertValueI (0x004558a0), and finally releases the
    // AutoRefCount map values and frees the two local vectors (see partial.txt).
    cGameNounManager* pAvatar = param_1->GetAvatar();
    void*             pCities = param_1->GetCities();
    (void)pAvatar;
    (void)pCities;
}