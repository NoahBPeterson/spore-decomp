// Slice s004c73f0: large editor model/creature build routine (12342 bytes, /Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"
#pragma pack(push, 4)

// @ 0x004c73f0
// PARTIAL skeleton: builds/updates a model from a property list: reads int/float/bool/
// vector/transform/key properties, resizes pointer and transform vectors, runs
// Matrix33FromEulerXYZ, and updates the scene. Body omitted (12KB).
void Editor_BuildModel73f0(void* self, void* propList)
{
    (void)self; (void)propList;
}

#pragma pack(pop)
