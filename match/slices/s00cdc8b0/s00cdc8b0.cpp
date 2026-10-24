#include "types.h"

// ---------------------------------------------------------------------------
// SP::cTribeModeStrategy slice s00cdc8b0.
//
// All four functions in this slice are large (304..1413 bytes) transition-flow
// methods that read a global settings/property bag through a virtual slot,
// walk the game-data vector through five helper pointers, and perturb the
// strategy's transition-target vector (0x1c-stride records) with ownership
// transfers whose cleanup calls a non-null-checked operator delete. The field
// identities could not be recovered from the decompile within the round budget
// without resorting to unnamed raw-offset reads, so no function is emitted and
// all four rows live in partial.txt.
// ---------------------------------------------------------------------------
