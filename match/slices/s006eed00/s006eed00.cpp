// Slice s006eed00 — `anonymous namespace'::CreateTestModel (3213 bytes).
// A large procedural mesh/model builder. Reconstructed as a skeleton only.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"

namespace {
// Builds a hard-coded test model from an RTTI/resource request; returns the model.
void* CreateTestModel(void* pRequest, int a1, int a2)
{
    (void)pRequest; (void)a1; (void)a2;
    return 0;
}
}

// Keep the symbol emitted even though it is only a skeleton.
void* CreateTestModel_ref(void* p, int a1, int a2) { return CreateTestModel(p, a1, a2); }
