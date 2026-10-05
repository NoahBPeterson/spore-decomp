// Slice s007bde20 — cThumbnailManager Shutdown / palette capture routines.
// All three are large /O2 /arch:SSE2 /EHsc object-construction + cleanup
// routines; only entry signatures are reconstructed.  See partial.txt.
#include "types.h"

// @ 0x007bde20  SP::cThumbnailManager::Shutdown  (this in ecx)
void __fastcall FUN_007bde20(void* p) { (void)p; }

// @ 0x007be430  SP::cThumbnailManager::CapturePaletteThumbnail (this, arg, arg)
void FUN_007be430(void* pThis, void* a, void* b) { (void)pThis; (void)a; (void)b; }

// @ 0x007bea00 (this, arg, arg)
void FUN_007bea00(void* pThis, void* a, void* b) { (void)pThis; (void)a; (void)b; }
