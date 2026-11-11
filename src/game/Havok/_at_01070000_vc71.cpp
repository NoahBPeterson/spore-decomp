// VC7.1 Havok leaf isolated from the migrated module's VS2008-only casts.
#include "_at_01070000_thread_memory.h"

class hkThreadMemoryDeletionView {
public:
    virtual void setStackArea(void* area, int size);
    virtual void releaseCachedMemory();
    virtual ~hkThreadMemoryDeletionView();
};

// @ 0x0107d790
void hkThreadMemory::removeReference()
{
    if (--mnRefCount == 0)
        delete (hkThreadMemoryDeletionView*)this;
}
