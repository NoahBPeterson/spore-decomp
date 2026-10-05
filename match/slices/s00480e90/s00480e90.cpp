// Slice s00480e90: SP::cSPEditorHandleDeform::RecordHandlePosition, a 4202-byte
// /Od /Ob1 /arch:SSE routine.  PARTIAL: signature and the opening local-transform
// copy are reproduced; the large matrix/bbox/vector body is omitted.
#include "types.h"

// @ 0x00480e90
void RecordHandlePosition(char* self, bool update)
{
    // mBlock = *(void**)(self+0x10); entity = *(void**)(mBlock+0x10)
    char* entity = *(char**)(*(char**)(self + 0x10) + 0x10);
    char matrix[0x38];
    void GetLocalTransform(void*, void*);        // @ 0x0040ce80 region helper
    GetLocalTransform(entity + 8, matrix);
    (void)update;
}
