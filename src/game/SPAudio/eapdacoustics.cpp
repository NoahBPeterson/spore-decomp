// src/game/SPAudio/eapdacoustics.cpp -- migrated from slice(s) s00a52080, s00a510e0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdacoustics.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a510e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
bool x_acoustics_setup();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool thunk_FUN_00a5ebe0();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool FUN_00a5c7c0();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool FUN_00a60470();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool x_arithmetic_setup();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool FUN_00a5da10();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool x_random_setup();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool FUN_00a4c610();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool FUN_00a5d5a0();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool x_input_setup();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool x_thisinstance_setup();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool FUN_00a598d0();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool FUN_00a5eb20();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool FUN_00a62e90();
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool x_menu_setup();
}
}
}
// ---- items of slice s00a510e0 end

// ---- items of slice s00a52080 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct t_symbol { const char* s_name; int s_thing; };   // 8 bytes
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl class_new7(t_symbol* s, t_symbol* help, void* makefn,
                         void* freefn, int size, int flags, int a1);        // 0xa48e50 (7-arg)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
unsigned char __cdecl class_doaddfloat(void* cls, void* fn);       // 0xa47f30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  __cdecl class_sethelpsymbol(void* cls, int a, int b);        // 0xa47fc0
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
extern void* spMtofClass;           // 0x167550c
extern void* spFtomClass;           // 0x1675500
extern void* spPowtodbClass;        // 0x1675504
extern void* spRmstodbClass;        // 0x1675510
extern void* spDbtopowClass;        // 0x1675514
extern void* spDbtormsClass;        // 0x1675508
// ---- items of slice s00a52080 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void* __cdecl FUN_00a52080();  // 0x00a52080 (stays in the slice: not this object's)
void __cdecl FUN_00a520b0(void* obj, float a);  // 0x00a520b0 (stays in the slice: not this object's)
void* __cdecl FUN_00a52170();  // 0x00a52170 (stays in the slice: not this object's)
void __cdecl FUN_00a521a0(void* obj, float a);  // 0x00a521a0 (stays in the slice: not this object's)
void* __cdecl FUN_00a52230();  // 0x00a52230 (stays in the slice: not this object's)
void __cdecl FUN_00a52260(void* obj, float a);  // 0x00a52260 (stays in the slice: not this object's)
void* __cdecl FUN_00a522f0();  // 0x00a522f0 (stays in the slice: not this object's)
void __cdecl FUN_00a52320(void* obj, float a);  // 0x00a52320 (stays in the slice: not this object's)
void* __cdecl FUN_00a523b0();  // 0x00a523b0 (stays in the slice: not this object's)
void __cdecl FUN_00a523e0(void* obj, float a);  // 0x00a523e0 (stays in the slice: not this object's)
void* __cdecl FUN_00a52490();  // 0x00a52490 (stays in the slice: not this object's)
void __cdecl FUN_00a524c0(void* obj, float a);  // 0x00a524c0 (stays in the slice: not this object's)

// @ 0x00a51f90
namespace EA { namespace Audio { namespace Eapd {
bool control_objects_init()
{
    bool ok = true;
    ok &= x_acoustics_setup();
    ok &= thunk_FUN_00a5ebe0();
    ok &= FUN_00a5c7c0();
    ok &= FUN_00a60470();
    ok &= x_arithmetic_setup();
    ok &= FUN_00a5da10();
    ok &= x_random_setup();
    ok &= FUN_00a4c610();
    ok &= FUN_00a5d5a0();
    ok &= x_input_setup();
    ok &= x_thisinstance_setup();
    ok &= FUN_00a598d0();
    ok &= FUN_00a5eb20();
    ok &= FUN_00a62e90();
    ok &= x_menu_setup();
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a52570
namespace EA {
namespace Audio {
namespace Eapd {
bool x_acoustics_setup()
{
  t_symbol* help = gensymS("acoustics.pd");
  int hs = help->s_thing;
  unsigned char r = 1;
  void* c;

  c = EA::Audio::Eapd::class_new7(gensymS("mtof"), help, (void*)&FUN_00a52080,
                                 0, 0x28, 0, 0);
  spMtofClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a520b0);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("ftom"), help, (void*)&FUN_00a52170,
                                 0, 0x28, 0, 0);
  spFtomClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a521a0);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("powtodb"), help, (void*)&FUN_00a522f0,
                                 0, 0x28, 0, 0);
  spPowtodbClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a52320);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("rmstodb"), help, (void*)&FUN_00a52230,
                                 0, 0x28, 0, 0);
  spRmstodbClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a52260);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("dbtopow"), help, (void*)&FUN_00a523b0,
                                 0, 0x28, 0, 0);
  spDbtopowClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a523e0);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  c = EA::Audio::Eapd::class_new7(gensymS("dbtorms"), help, (void*)&FUN_00a52490,
                                 0, 0x28, 0, 0);
  spDbtormsClass = c;
  r &= (unsigned char)(c != 0);
  r &= EA::Audio::Eapd::class_doaddfloat(c, (void*)&FUN_00a524c0);
  EA::Audio::Eapd::class_sethelpsymbol(c, hs, help->s_thing);

  return r;
}
}
}
}  // namespace EA::Audio::Eapd
