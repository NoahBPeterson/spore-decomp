// src/game/SPAudio/eapdcontrol.cpp -- migrated from slice(s) s00a52080 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdcontrol.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a52080 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct t_symbol { const char* s_name; int s_thing; };   // 8 bytes
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl class_new(t_symbol* s, t_symbol* help, void* makefn,
                        void* freefn, int size, int flags, int a1, int a2); // 0xa48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
unsigned char __cdecl class_addanything(void* cls, void* fn);      // 0xa47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
unsigned char __cdecl class_addmethod(void* cls, void* fn, t_symbol* s, int a1); // 0xa48a30/0xa48a80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* __cdecl gensym(t_symbol* out, const char* name);         // 0xa675f0
}
}
}
static __forceinline t_symbol* gensymS(const char* s) {
  t_symbol tmp;
  return EA::Audio::Eapd::gensym(&tmp, s);
}
void __cdecl FUN_00a52840(char* obj, int a, int b, int argc, int* argv);
// ---- items of slice s00a52080 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void* spControlClass;        // 0x1675518

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl FUN_00a52780(char* obj);  // 0x00a52780 (stays in the slice: not this object's)
void __cdecl FUN_00a527b0(char* obj, int sym, int a);  // 0x00a527b0 (stays in the slice: not this object's)
void* __cdecl FUN_00a527f0(int sym, int a);  // 0x00a527f0 (stays in the slice: not this object's)
void __cdecl FUN_00a528b0(char* obj, int a, int b, int argc, int* argv);  // 0x00a528b0 (stays in the slice: not this object's)

// @ 0x00a528e0
namespace EA {
namespace Audio {
namespace Eapd {
bool a_control_setup()
{
  t_symbol* cls = gensymS("control");
  void* c = EA::Audio::Eapd::class_new(cls, (t_symbol*)0xc2e4e0,
                                       (void*)&FUN_00a527f0, 0, 0x38, 0, 6, 0);
  spControlClass = c;
  unsigned char r = (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_addanything(c, (void*)&FUN_00a52840);
  r &= EA::Audio::Eapd::class_addmethod(c, (void*)&FUN_00a528b0,
                                        gensymS("set"), 9);
  r &= EA::Audio::Eapd::class_addmethod(c, (void*)&FUN_00a527b0,
                                        gensymS("use"), 2);
  r &= EA::Audio::Eapd::class_addmethod(c, (void*)&FUN_00a52780,
                                        gensymS("reset"), 0);
  return r;
}
}
}
}  // namespace EA::Audio::Eapd
