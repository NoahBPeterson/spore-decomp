// Slice s01218f70, 0x01218f70-0x01226f30.
//
// Thirty-four of the VAs are compiler-generated MSVC EH cleanup funclets: each starts by
// reading the *caller's* frame through EBP ([ebp-N] locals / [ebp+4] args) and tail-jumps
// into RAII destructors (eastl rbtree/hashtable/vector/fixed_hash_map teardown, Mutex
// destructors, operator_delete, ...) or, at the end of a group, installs the enclosing
// function's exception handler (mov eax, <__ehfuncinfo>; jmp __CxxFrameHandler3). They are
// the try/catch/scope-exit fragments of enclosing functions whose bodies are outside this
// slice, so they cannot be reconstructed from the fragment alone. Placeholders below keep
// the TU complete; all are listed in partial.txt.
//
// 0x01219d80 is likewise an unwind/handler fragment (and dword [0x166f3a8], ~2; ret,
// immediately followed by an __ehhandler stub), listed in partial.txt.
//
// Four VAs are complete, self-contained global dynamic initializers and are reconstructed
// byte-exact below (compiled /Od like the original):
//   0x01225310 / 0x01225340 / 0x01225370  construct the singleton at 0x15d2c60 /
//       0x15d29c8 / 0x15d2964 and register its destructor with atexit
//   0x01226f30  zero-initialise the smart-pointer global 0x15d2dbc and register its destructor
// The three ctor+atexit initializers reserve a dead 12-byte frame (char pad[12]) exactly as
// the original does, and compile with /GS- so no security cookie is emitted.
#include "types.h"

extern "C" int atexit(void (__cdecl*)());

// ---------------------------------------------------------------------------
// EH cleanup funclets (placeholders; see partial.txt)
// ---------------------------------------------------------------------------

// @ 0x01218f70
void __cdecl FUN_01218f70() {}
// @ 0x01219280
void __cdecl FUN_01219280() {}
// @ 0x01219620
void __cdecl FUN_01219620() {}
// @ 0x01219660
void __cdecl FUN_01219660() {}
// @ 0x01219770
void __cdecl FUN_01219770() {}
// @ 0x012197e0
void __cdecl FUN_012197e0() {}
// @ 0x01219860
void __cdecl FUN_01219860() {}
// @ 0x01219910
void __cdecl FUN_01219910() {}
// @ 0x01219950
void __cdecl FUN_01219950() {}
// @ 0x01219b00
void __cdecl FUN_01219b00() {}
// @ 0x01219b50
void __cdecl FUN_01219b50() {}
// @ 0x01219bf0
void __cdecl FUN_01219bf0() {}
// @ 0x01219c70
void __cdecl FUN_01219c70() {}
// @ 0x01219cf0
void __cdecl FUN_01219cf0() {}
// @ 0x01219d10
void __cdecl FUN_01219d10() {}
// @ 0x01219e00
void __cdecl FUN_01219e00() {}
// @ 0x01219f10
void __cdecl FUN_01219f10() {}
// @ 0x01219fa0
void __cdecl FUN_01219fa0() {}
// @ 0x0121a090
void __cdecl FUN_0121a090() {}
// @ 0x0121a180
void __cdecl FUN_0121a180() {}
// @ 0x0121a210
void __cdecl FUN_0121a210() {}
// @ 0x0121a290
void __cdecl FUN_0121a290() {}
// @ 0x0121a2d0
void __cdecl FUN_0121a2d0() {}
// @ 0x0121a310
void __cdecl FUN_0121a310() {}
// @ 0x0121a350
void __cdecl FUN_0121a350() {}
// @ 0x0121a390
void __cdecl FUN_0121a390() {}
// @ 0x0121a3d0
void __cdecl FUN_0121a3d0() {}
// @ 0x0121a450
void __cdecl FUN_0121a450() {}
// @ 0x0121a470
void __cdecl FUN_0121a470() {}
// @ 0x0121a4b0
void __cdecl FUN_0121a4b0() {}
// @ 0x0121a520
void __cdecl FUN_0121a520() {}
// @ 0x0121a600
void __cdecl FUN_0121a600() {}
// @ 0x0121a620
void __cdecl FUN_0121a620() {}
// @ 0x0121a680
void __cdecl FUN_0121a680() {}

// ---------------------------------------------------------------------------
// Unwind + __ehhandler fragment (partial; see partial.txt)
// ---------------------------------------------------------------------------

// @ 0x01219d80  (static-init guard reset; the following __ehhandler stub shares the
// analysis function boundary, so the 24-byte function cannot be reproduced standalone)
void __cdecl FUN_01219d80()
{
    *(uint32_t*)0x166f3a8 &= ~2u;
}

// ---------------------------------------------------------------------------
// Global dynamic initializers
// ---------------------------------------------------------------------------

// The singleton constructors live in another translation unit; only the initializer shape
// matters (the call target is a masked relocation).
struct Singleton { void ctor(); };

// @ 0x01225310
void FUN_01225310()
{
    char pad[12];
    (void)pad;   // dead frame, matching the original dynamic initializer
    ((Singleton*)0x15d2c60)->ctor();
    atexit((void (__cdecl*)())0x13bc9f0);
}

// @ 0x01225340
void FUN_01225340()
{
    char pad[12];
    (void)pad;
    ((Singleton*)0x15d29c8)->ctor();
    atexit((void (__cdecl*)())0x13bca10);
}

// @ 0x01225370
void FUN_01225370()
{
    char pad[12];
    (void)pad;
    ((Singleton*)0x15d2964)->ctor();
    atexit((void (__cdecl*)())0x13bca30);
}

// @ 0x01226f30
void FUN_01226f30()
{
    *(uint32_t*)0x15d2dbc = 0;
    atexit((void (__cdecl*)())0x13bca50);
}
