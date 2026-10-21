// Slice s01217850, 0x01217850-0x01218f3d.
//
// flags: /O2 /MD /Gy /EHsc /TP
//
// All 29 slice VAs are compiler-generated MSVC EH cleanup funclets, not source-level
// functions. Each fragment has no
// prologue of its own: it reads the *enclosing* function's frame through EBP (locals at
// [ebp-N], arguments at [ebp+N]) and tail-jumps into RAII destructors (eastl
// basic_string/hash_map/rbtree, MutexLock, WString::DeallocateSelf, operator_delete, ...)
// or overwrites a vptr; the last fragment of a group installs the enclosing function's
// exception handler (`mov eax, <__ehfuncinfo>; jmp __CxxFrameHandler3`).
//
// They are the try/catch/scope-exit fragments of functions whose bodies lie outside this
// slice, so they cannot be reconstructed from the fragment alone. The placeholders below
// keep the translation unit complete; every VA is listed in partial.txt.
#include "types.h"

// @ 0x01217850
void __cdecl FUN_01217850() {}
// @ 0x01217b10
void __cdecl FUN_01217b10() {}
// @ 0x01217c10
void __cdecl FUN_01217c10() {}
// @ 0x01217d50
void __cdecl FUN_01217d50() {}
// @ 0x01217df0
void __cdecl FUN_01217df0() {}
// @ 0x01217e80
void __cdecl FUN_01217e80() {}
// @ 0x01217f70
void __cdecl FUN_01217f70() {}
// @ 0x01217fa0
void __cdecl FUN_01217fa0() {}
// @ 0x012181a0
void __cdecl FUN_012181a0() {}
// @ 0x01218200
void __cdecl FUN_01218200() {}
// @ 0x01218290
void __cdecl FUN_01218290() {}
// @ 0x01218370
void __cdecl FUN_01218370() {}
// @ 0x01218390
void __cdecl FUN_01218390() {}
// @ 0x012186c0
void __cdecl FUN_012186c0() {}
// @ 0x01218810
void __cdecl FUN_01218810() {}
// @ 0x01218870
void __cdecl FUN_01218870() {}
// @ 0x012188a0
void __cdecl FUN_012188a0() {}
// @ 0x01218950
void __cdecl FUN_01218950() {}
// @ 0x012189c0
void __cdecl FUN_012189c0() {}
// @ 0x012189f0
void __cdecl FUN_012189f0() {}
// @ 0x01218a20
void __cdecl FUN_01218a20() {}
// @ 0x01218b60
void __cdecl FUN_01218b60() {}
// @ 0x01218c10
void __cdecl FUN_01218c10() {}
// @ 0x01218c40
void __cdecl FUN_01218c40() {}
// @ 0x01218ce0
void __cdecl FUN_01218ce0() {}
// @ 0x01218d10
void __cdecl FUN_01218d10() {}
// @ 0x01218d90
void __cdecl FUN_01218d90() {}
// @ 0x01218de0
void __cdecl FUN_01218de0() {}
// @ 0x01218ea0
void __cdecl FUN_01218ea0() {}
// @ 0x01218f10
void __cdecl FUN_01218f10() {}

// Slice header (stable: pastes into the committed .cpp unchanged).
//
// flags: /O2 /MD /Gy /EHsc /TP
//
// All 29 slice VAs are MSVC compiler-generated EH cleanup funclets, not
// source-level functions: each fragment has no prologue, reads the *enclosing*
// function's frame through the caller's EBP (locals at [ebp-N], arguments at
// [ebp+N]) and tail-jumps into RAII destructors (eastl basic_string/hash_map/
// rbtree, MutexLock, WString::DeallocateSelf, operator_delete) or overwrites a
// vptr. The last fragment of each group installs the enclosing function's
// exception handler (mov eax, <__ehfuncinfo>; jmp __CxxFrameHandler3).
//
// Their enclosing functions' bodies lie OUTSIDE this slice (the EH prolog is in
// another region), so they cannot be reconstructed from the fragments alone:
// reproducing the exact byte sequence would require the whole enclosing
// function in this translation unit and cl emitting the same funclet split.
// Every one is in partial.txt; the empty definitions above only keep this TU
// compilable. The trailing FUN_01218f3f has no // @ marker naming a slice VA -
// it is the last section's end, not a function.
