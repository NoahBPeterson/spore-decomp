// src/game/SPAudio/eapdmenu.cpp -- migrated from slice(s) s00a60ef0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdmenu.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a60ef0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint;
typedef unsigned char  byte;
namespace Eapd {
struct t_symbol {                 // by-value pair
    uint        mHash;            // +0x00
    const char* mpName;           // +0x04
};
}
namespace Eapd {
struct t_class;                   // opaque
}
namespace Eapd {
struct t_atom { uint a; uint b; };        // 8 bytes
}
namespace Eapd {
struct TX {                       // generic object with the common tail
    uint   mGobj[0x28 / 4];       // +0x00
    void*  mpA28;                 // +0x28
    void*  mpB2c;                 // +0x2c
    int    mC30;                  // +0x30
    int    mD34;                  // +0x34
    void*  mpE38;                 // +0x38
    int    mF3c;                  // +0x3c
};
}
namespace Eapd {
t_class* gpMenuClass;             // 0x01675834
}
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* s);                       // 0x00a675f0
}
namespace Eapd {
t_class*  class_new(t_symbol name, void* newmethod, void* freemethod,
                    int size, int a5, int a6, int a7);                // 0x00a48ea0
}
namespace Eapd {
byte      class_doaddfloat(t_class* c, void* fn);                     // 0x00a47f30
}
namespace Eapd {
byte      class_addlist(t_class* c, void* fn);                        // 0x00a47f70
}
namespace Eapd {
bool      class_addmethod_m(t_class* c, void* fn, t_symbol name, int a4, int a5); // 0x00a48a80 (trailing free method)
}
namespace Eapd {
bool      class_addmethod(t_class* c, void* fn, t_symbol name, int a4);   // 0x00a48a30
}
namespace Eapd {
void* menu_new(int argc, t_atom* argv);                               // 0x00a618c0
}
namespace Eapd {
void  menu_free(TX* x);                                               // 0x00a619c0
}
namespace Eapd {
int   menu_float(TX* x, float f);                                     // 0x00a619e0
}
namespace Eapd {
bool  menu_list(TX* x, t_symbol s, int argc, t_atom* argv);           // 0x00a61ad0
}
namespace Eapd {
bool  menu_append(TX* x, t_symbol s, int argc, t_atom* argv);         // 0x00a61b10
}
namespace Eapd {
void  menu_clear(TX* x);                                              // 0x00a61b50
}
// ---- items of slice s00a60ef0 end

// @ 0x00a61b60
namespace Eapd {
byte x_menu_setup(void)
{
    t_symbol s;
    t_symbol* p = gensym(&s, "menu");
    gpMenuClass = class_new(*p, (void*)menu_new, (void*)menu_free, 0x3c, 0, 9, 0);
    byte ok = gpMenuClass != 0;
    ok &= 1;
    ok &= class_doaddfloat(gpMenuClass, (void*)menu_float);
    ok &= class_addlist(gpMenuClass, (void*)menu_list);
    p = gensym(&s, "append");
    ok &= class_addmethod_m(gpMenuClass, (void*)menu_append, *p, 9, 0);
    p = gensym(&s, "clear");
    ok &= class_addmethod(gpMenuClass, (void*)menu_clear, *p, 0);
    return ok;
}
}  // namespace Eapd
