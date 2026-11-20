// @ 0x007e0950
#include "game/types.h"

void __cdecl EFree(void* memory); // 0x00f47380
namespace EA {
namespace Swarm {
// The retail vtable of cDescription, restored during destruction.
extern void* cDescription_vtable[]; // 0x013ef094
}
namespace ArgScript {
struct cBlockCommandBase {
    char mCommandStorage[0x38];
    void DestroyBase(); // 0x0083cd90
};
}
}

struct cSplitControllerEffectCommand : EA::ArgScript::cBlockCommandBase {
    void** mDescriptionVtable;
    int mDescriptionRefCount;
    struct String {
        char* mpBegin;
        char* mpEnd;
        char* mpCapacity;
        void* mAllocator;
    } mName;
    void* ScalarDeletingDestructor(unsigned int flags);
};

// @ 0x007e0950
void* cSplitControllerEffectCommand::ScalarDeletingDestructor(unsigned int flags) {
    if (mName.mpCapacity - mName.mpBegin > 1 && mName.mpBegin)
        EFree(mName.mpBegin);
    mDescriptionVtable = EA::Swarm::cDescription_vtable;
    DestroyBase();
    if (flags & 1)
        EFree(this);
    return this;
}
