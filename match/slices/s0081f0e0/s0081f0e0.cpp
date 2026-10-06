// Slice s0081f0e0 -- SP::cPropertyUI property-modify overloads.
// Flags (whole cluster): /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// The three functions in this slice (ModifyResourceKey 0x81f0e0, ModifyVec2
// 0x81f490, ModifyVec3 0x81f900) are ~900-1150 byte /O2 bodies whose bulk is
// inlined AutoRefCount refcounting, eastl vector iteration and EA::Variant
// construction. They were not reconstructed within budget; see partial.txt.
#include "types.h"

// 0x0081f0e0  SP::cPropertyUI::ModifyResourceKey
// 0x0081f490  SP::cPropertyUI::ModifyVec2
// 0x0081f900  SP::cPropertyUI::ModifyVec3
