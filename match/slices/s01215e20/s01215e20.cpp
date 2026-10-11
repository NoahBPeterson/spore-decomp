// Batch gold1 slice s01215e20, 0x01215e20-0x01217570.
//
// Every VA in this slice is a compiler-generated MSVC EH cleanup funclet: the entry
// reads the *caller's* frame via EBP ([ebp-N] locals / [ebp+N] args) and either tail-jumps
// into a RAII destructor/deallocator (eastl::basic_string<...>::~basic_string,
// SpVec::DeallocateSelf, eastl::vector<...>::~vector, AutoRefCount::release, Holder::~Holder,
// UTFWin::ILayoutElement::SetSerializer, ...) or calls operator_delete(ptr, file, line, ...)
// for arrays, then ends with `mov eax,<TI descriptor>; jmp 0x11e090c` (the C++ EH handler).
// They are the try/catch/scope-exit fragments of enclosing functions whose bodies are
// outside this slice, so they cannot be reconstructed from the fragment alone. Placeholders
// below keep the TU complete; all are listed in partial.txt.
#include "types.h"

// @ 0x01215e20
void __cdecl FUN_01215e20() {}
// @ 0x01215ef0
void __cdecl FUN_01215ef0() {}
// @ 0x01215f30
void __cdecl FUN_01215f30() {}
// @ 0x01216090
void __cdecl FUN_01216090() {}
// @ 0x01216110
void __cdecl FUN_01216110() {}
// @ 0x01216170
void __cdecl FUN_01216170() {}
// @ 0x012161c0
void __cdecl FUN_012161c0() {}
// @ 0x01216210
void __cdecl FUN_01216210() {}
// @ 0x012162a0
void __cdecl FUN_012162a0() {}
// @ 0x01216400
void __cdecl FUN_01216400() {}
// @ 0x012166f0
void __cdecl FUN_012166f0() {}
// @ 0x01216810
void __cdecl FUN_01216810() {}
// @ 0x01216890
void __cdecl FUN_01216890() {}
// @ 0x01216960
void __cdecl FUN_01216960() {}
// @ 0x01216a90
void __cdecl FUN_01216a90() {}
// @ 0x01216c00
void __cdecl FUN_01216c00() {}
// @ 0x01216c30
void __cdecl FUN_01216c30() {}
// @ 0x01216cf0
void __cdecl FUN_01216cf0() {}
// @ 0x01216df0
void __cdecl FUN_01216df0() {}
// @ 0x01216e30
void __cdecl FUN_01216e30() {}
// @ 0x01216ea0
void __cdecl FUN_01216ea0() {}
// @ 0x01216ee0
void __cdecl FUN_01216ee0() {}
// @ 0x01216fe0
void __cdecl FUN_01216fe0() {}
// @ 0x01217240
void __cdecl FUN_01217240() {}
// @ 0x01217330
void __cdecl FUN_01217330() {}
// @ 0x01217470
void __cdecl FUN_01217470() {}
// @ 0x01217570
void __cdecl FUN_01217570() {}
