// Flags: /O2 /MD /Gy /TP
// Scalar deleting destructor. Resets the vtable at +0xd4, then ~cSpatialObject,
// and operator delete when the low flag bit is set.
#include "types.h"

extern void* vtbl_013ef094; // 0x013ef094

struct cSpatialObject {
    char mPad00[0xd4];
    ~cSpatialObject(); // 0x00c8a420
};

struct cSpatialDerived : cSpatialObject {
    void** mpVtblD4; // +0xd4
    static void operator delete(void* p);
    void* FUN_00ad33a0(unsigned int flags);
};

// @ 0x00ad33a0
void* cSpatialDerived::FUN_00ad33a0(unsigned int flags)
{
    mpVtblD4 = &vtbl_013ef094;
    cSpatialObject::~cSpatialObject();
    if (flags & 1)
        operator delete(this);
    return this;
}
