// Slice s00ca3f20 -- managed-object release (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct cInterface {
    void* mpVtable;                                          // +0x00
};

struct cManaged {
    cInterface* mpInterface;                                 // +0x00
    uint32_t    mFlags04;                                    // +0x04
    uint32_t    mPad08[14];                                  // +0x08 .. +0x3f
    int32_t     mRefCount40;                                 // +0x40
};

struct cOwner {
    uint8_t   mPad00[0xd0];                                  // +0x00 .. +0xcf
    cManaged* mpManaged;                                     // +0xd0

    void Clear();
};

// @ 0x00ca42c0
void cOwner::Clear()
{
    if (mpManaged) {
        cInterface* iface = mpManaged->mpInterface;
        ((void (__thiscall*)(cInterface*, cManaged*, int))
            ((void**)iface->mpVtable)[0x16c / 4])(iface, mpManaged, 0);
    }
    if (mpManaged) {
        cManaged* p = mpManaged;
        mpManaged = 0;
        if (p->mRefCount40 > 1) {
            --p->mRefCount40;
        } else {
            cInterface* iface = p->mpInterface;
            unsigned char flag = (unsigned char)((p->mFlags04 >> 31) & 1);
            ((void (__thiscall*)(cInterface*, cManaged*, unsigned char))
                ((void**)iface->mpVtable)[0x170 / 4])(iface, p, flag);
        }
    }
}
