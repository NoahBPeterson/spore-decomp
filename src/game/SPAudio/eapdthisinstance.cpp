// src/game/SPAudio/eapdthisinstance.cpp -- migrated from slice(s) s00a62ec0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdthisinstance.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a62ec0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PgSymbol {              // t_symbol: by-value pair (hash, name pointer)
    uint32_t    mHash;         // +0x00
    const char* mpName;        // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct XThisInstance {
    uint32_t    mGobj[0x28 / 4];  // +0x00
    void*       mpInstance;       // +0x28
    uint32_t    pad2c[0xc];       // +0x2c .. +0x5b (12 dwords)
    uint8_t     mbInstanceFlag;   // +0x5c
    bool        StoreFlag(uint8_t flag);   // 0x00a633e0
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gpInstanceClass;     // 0x01675860
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol* gensym(PgSymbol* out, const char* s);                       // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new7(PgSymbol name, int size, void* freemethod, void* newmethod,
                     int a1, int a2, int a3);                         // 0x00a48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool      class_addmethod1(t_class* c, void* fn, PgSymbol name, int a1, int a2); // 0x00a48a80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* instance_new();                                                // 0x00a632e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  busy_float(XThisInstance* x, float f);                         // 0x00a63310
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  gpInstanceClass;      // 0x01675860
}
}
}
// ---- items of slice s00a62ec0 end

// @ 0x00a63350
namespace EA {
namespace Audio {
namespace Eapd {
bool x_thisinstance_setup()
{
    PgSymbol s;
    bool ok;

    gpInstanceClass = class_new7(*gensym(&s, "thisinstance"), 0x2c, (void*)instance_new, 0, 0, 0, 0);
    ok = gpInstanceClass != 0;
    ok &= class_addmethod1(gpInstanceClass, (void*)busy_float, *gensym(&s, "busy"), 1, 0);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd
