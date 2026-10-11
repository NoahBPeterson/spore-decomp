// Batch gold1 slice s0120fad0, 0x0120fad0-0x01210fa0.
//
// Every VA in this slice is a compiler-generated MSVC EH cleanup funclet: the entry
// reads the *caller's* frame via EBP ([ebp-N] locals / [ebp+4] args) and tail-jumps into
// RAII destructors (eastl::sp_vector_allocator::deallocate, AutoRefCount::~AutoRefCount,
// SP::MutexLock::~MutexLock, rbtree/vector destructors, operator_delete, ...). They are
// the try/catch/scope-exit fragments of enclosing functions whose bodies are outside this
// slice, so they cannot be reconstructed from the fragment alone. Placeholders below
// keep the TU complete; all are listed in partial.txt.
#include "types.h"

// @ 0x0120fad0
void __cdecl FUN_0120fad0() {}
// @ 0x0120fb10
void __cdecl FUN_0120fb10() {}
// @ 0x0120fbe0
void __cdecl FUN_0120fbe0() {}
// @ 0x0120fcb0
void __cdecl FUN_0120fcb0() {}
// @ 0x0120fd00
void __cdecl FUN_0120fd00() {}
// @ 0x0120fe00
void __cdecl FUN_0120fe00() {}
// @ 0x0120fea0
void __cdecl FUN_0120fea0() {}
// @ 0x0120ff40
void __cdecl FUN_0120ff40() {}
// @ 0x01210090
void __cdecl FUN_01210090() {}
// @ 0x01210110
void __cdecl FUN_01210110() {}
// @ 0x01210190
void __cdecl FUN_01210190() {}
// @ 0x01210230
void __cdecl FUN_01210230() {}
// @ 0x01210270
void __cdecl FUN_01210270() {}
// @ 0x01210380
void __cdecl FUN_01210380() {}
// @ 0x01210580
void __cdecl FUN_01210580() {}
// @ 0x01210630
void __cdecl FUN_01210630() {}
// @ 0x01210960
void __cdecl FUN_01210960() {}
// @ 0x01210980
void __cdecl FUN_01210980() {}
// @ 0x01210ad0
void __cdecl FUN_01210ad0() {}
// @ 0x01210ba0
void __cdecl FUN_01210ba0() {}
// @ 0x01210c40
void __cdecl FUN_01210c40() {}
// @ 0x01210de0
void __cdecl FUN_01210de0() {}
// @ 0x01210e60
void __cdecl FUN_01210e60() {}
// @ 0x01210ea0
void __cdecl FUN_01210ea0() {}
// @ 0x01210f00
void __cdecl FUN_01210f00() {}
// @ 0x01210fa0
void __cdecl FUN_01210fa0() {}
