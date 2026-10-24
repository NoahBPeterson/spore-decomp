// Slice s013cbf20: compiler-generated destructor thunk for the static arena object at 0x0171e6e5.
// The body loads the object address into ecx and tail-jumps to its rw::core::arena::Release routine.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

// rw::core::arena::Release sets this from ecx and decrements the arena refcount (0x016f2978);
// it ignores the incoming object pointer, so the thunk's only job is the tail call.
struct Arena {
    void Release();                      // 0x011e2080
};

Arena g_arenaObject;                     // 0x0171e6e5

// @ 0x013cbf20
void FUN_013cbf20() {
    g_arenaObject.Release();
}
