// src/game/SPAudio/eapdmemory.cpp -- migrated from slice(s) s00a49670, s00a488d0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdmemory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdio.h>
#include <string.h>

// ---- items of slice s00a488d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_pdinstance {
    virtual void  pad0();
    virtual void* alloc(int n, const char* tag);   // +4
    virtual void  pad2();
    virtual void  freemem(void* p);                // +0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_pdinstance* pdinstance();                                                    // 0xa67cb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  memfill(void* d, int c, int n);                                          // 0x11e073e
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                                        // 0xa49610
}
}
}
// ---- items of slice s00a488d0 end

// ---- items of slice s00a49670 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline bool operator==(const t_symbol& a, const t_symbol& b) { return a.mHash == b.mHash; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct EapdAllocator {
    virtual void  Slot0();
    virtual void* Alloc(unsigned size, unsigned tag);
    virtual void  Slot2();
    virtual void  Free(void* p);
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
EapdAllocator* System_GetAllocator();                            // 0xa67cb0
}
}
}
// ---- items of slice s00a49670 end

// @ 0x00a49610
namespace EA { namespace Audio { namespace Eapd {
__declspec(noinline) void* getbytes(int n, const char* tag)
{
    if ((unsigned)n < 1u)
        n = 1;
    void* r = pdinstance()->alloc(n, tag);
    if (r)
        memfill(r, 0, n);
    return r;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49650
namespace EA {
namespace Audio {
namespace Eapd {
void freebytes(void * p, unsigned int n)
{
    pdinstance()->freemem(p);
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a49670
namespace EA { namespace Audio { namespace Eapd {
void* resizebytes(void* ptr, uint32_t oldsize, uint32_t newsize, uint32_t tag)
{
    void* newp;

    if (newsize < 1)
        newsize = 1;
    if (oldsize < 1)
        oldsize = 1;
    if (newsize == oldsize)
        return ptr;
    uint32_t n = newsize;
    if (n < 1)
        n = 1;
    EapdAllocator* a = System_GetAllocator();
    newp = a->Alloc(n, tag);
    if (!newp)
        return 0;
    memset(newp, 0, n);
    if (!newp)
        return 0;
    if (newsize > oldsize) {
        memcpy(newp, ptr, oldsize);
        memset((char*)newp + oldsize, 0, newsize - oldsize);
    } else {
        memcpy(newp, ptr, newsize);
    }
    System_GetAllocator()->Free(ptr);
    return newp;
}
}}}  // namespace EA::Audio::Eapd
