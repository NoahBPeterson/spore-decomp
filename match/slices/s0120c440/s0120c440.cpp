// Batch bfs4 slice s0120c440, 0x0120c440-0x0120e110.
//
// Every VA in this slice is a compiler-generated MSVC EH cleanup funclet: the entry
// reads the *caller's* frame via EBP ([ebp-N] locals / [ebp+4] args) and tail-jumps into
// RAII destructors (eastl::basic_string::DeallocateSelf, eastl::vector<...>::~vector,
// rbtree DoNukeSubtree, operator_delete, MutexLock::~MutexLock, ...). They are the
// try/catch/scope-exit fragments of enclosing functions whose bodies are outside this
// slice, so they cannot be reconstructed from the fragment alone. Placeholders below
// keep the TU complete; all are listed in partial.txt.
#include "types.h"

// @ 0x0120c440
void __cdecl FUN_0120c440() {}
// @ 0x0120c550
void __cdecl FUN_0120c550() {}
// @ 0x0120c5d0
void __cdecl FUN_0120c5d0() {}
// @ 0x0120c640
void __cdecl FUN_0120c640() {}
// @ 0x0120c690
void __cdecl FUN_0120c690() {}
// @ 0x0120c700
void __cdecl FUN_0120c700() {}
// @ 0x0120c7c0
void __cdecl FUN_0120c7c0() {}
// @ 0x0120c7f0
void __cdecl FUN_0120c7f0() {}
// @ 0x0120c860
void __cdecl FUN_0120c860() {}
// @ 0x0120c930
void __cdecl FUN_0120c930() {}
// @ 0x0120c9c0
void __cdecl FUN_0120c9c0() {}
// @ 0x0120c9e0
void __cdecl FUN_0120c9e0() {}
// @ 0x0120cab0
void __cdecl FUN_0120cab0() {}
// @ 0x0120cc30
void __cdecl FUN_0120cc30() {}
// @ 0x0120cdd0
void __cdecl FUN_0120cdd0() {}
// @ 0x0120ce00
void __cdecl FUN_0120ce00() {}
// @ 0x0120cea0
void __cdecl FUN_0120cea0() {}
// @ 0x0120cf90
void __cdecl FUN_0120cf90() {}
// @ 0x0120d0e0
void __cdecl FUN_0120d0e0() {}
// @ 0x0120d190
void __cdecl FUN_0120d190() {}
// @ 0x0120d2c0
void __cdecl FUN_0120d2c0() {}
// @ 0x0120d2f0
void __cdecl FUN_0120d2f0() {}
// @ 0x0120d5a0
void __cdecl FUN_0120d5a0() {}
// @ 0x0120d620
void __cdecl FUN_0120d620() {}
// @ 0x0120d750
void __cdecl FUN_0120d750() {}
// @ 0x0120d840
void __cdecl FUN_0120d840() {}
// @ 0x0120d860
void __cdecl FUN_0120d860() {}
// @ 0x0120da20
void __cdecl FUN_0120da20() {}
// @ 0x0120dac0
void __cdecl FUN_0120dac0() {}
// @ 0x0120db60
void __cdecl FUN_0120db60() {}
// @ 0x0120dbb0
void __cdecl FUN_0120dbb0() {}
// @ 0x0120dc70
void __cdecl FUN_0120dc70() {}
// @ 0x0120dce0
void __cdecl FUN_0120dce0() {}
// @ 0x0120ddc0
void __cdecl FUN_0120ddc0() {}
// @ 0x0120de80
void __cdecl FUN_0120de80() {}
// @ 0x0120df00
void __cdecl FUN_0120df00() {}
// @ 0x0120df50
void __cdecl FUN_0120df50() {}
// @ 0x0120dfb0
void __cdecl FUN_0120dfb0() {}
// @ 0x0120e0a0
void __cdecl FUN_0120e0a0() {}
// @ 0x0120e110
void __cdecl FUN_0120e110() {}
