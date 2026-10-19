// src/game/Spui/SPUICOM.cpp -- migrated from slice(s) s007ffc70 by tools/migrate/rewrite.py
// Object file: Spui/SPUICOM.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern bool  g_164bbd8;
extern bool  g_164bbd9;
extern char g_1543400[], g_1543404[], g_1543408[], g_154340c[];
extern char g_1543440[], g_154343c[], g_1543438[], g_1543410[], g_1543414[];
extern char g_1543418[], g_154341c[], g_1543420[], g_1543424[], g_154342c[];
extern char g_1543428[], g_1543430[], g_1543434[], g_1543444[], g_1543448[];
extern char g_154344c[], g_1543450[], g_1543454[], g_1543458[], g_154345c[];
extern char g_1543460[], g_1543464[], g_1543468[], g_154346c[], g_1543470[];
#include <new>
#include <intrin.h>

// ---- items of slice s007ffc70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __stdcall f_9512c0();
void* __cdecl f_9512d0(unsigned size, int align, const char* name, void* alloc);
void* __cdecl f_883860();                     // EA::Messaging::GetServer
void* __cdecl f_920090();                     // messaging registration
struct IFactoryObj {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void* v3(uint32_t id);
};
struct MsgServer { virtual void m0(); virtual void Reg(const void* p, int flags); };
struct cSPUIFrameSequencer { cSPUIFrameSequencer(); };
extern bool  g_164bbd8;
extern bool  g_164bbd9;
extern char g_1543400[], g_1543404[], g_1543408[], g_154340c[];
extern char g_1543440[], g_154343c[], g_1543438[], g_1543410[], g_1543414[];
extern char g_1543418[], g_154341c[], g_1543420[], g_1543424[], g_154342c[];
extern char g_1543428[], g_1543430[], g_1543434[], g_1543444[], g_1543448[];
extern char g_154344c[], g_1543450[], g_1543454[], g_1543458[], g_154345c[];
extern char g_1543460[], g_1543464[], g_1543468[], g_154346c[], g_1543470[];
#define REGMSG(g) ((MsgServer*)f_920090())->Reg((g), 0)
// ---- items of slice s007ffc70 end

// @ 0x008005f0
void f_8005f0()
{
  if (!g_164bbd9) {
    g_164bbd9 = true;
    g_164bbd8 = (f_883860() == 0);
    REGMSG(g_1543400);
    REGMSG(g_1543404);
    REGMSG(g_1543408);
    REGMSG(g_154340c);
    REGMSG(g_1543440);
    REGMSG(g_154343c);
    REGMSG(g_1543438);
    REGMSG(g_1543410);
    REGMSG(g_1543414);
    REGMSG(g_1543418);
    REGMSG(g_154341c);
    REGMSG(g_1543420);
    REGMSG(g_1543424);
    REGMSG(g_154342c);
    REGMSG(g_1543428);
    REGMSG(g_1543430);
    REGMSG(g_1543434);
    REGMSG(g_1543444);
    REGMSG(g_1543448);
    REGMSG(g_154344c);
    REGMSG(g_1543450);
    REGMSG(g_1543454);
    REGMSG(g_1543458);
    REGMSG(g_154345c);
    REGMSG(g_1543460);
    REGMSG(g_1543464);
    REGMSG(g_1543468);
    REGMSG(g_154346c);
    REGMSG(g_1543470);
  }
}

// @ 0x008008b0
void* __stdcall f_8008b0(int unused, void* alloc)
{
  if (!alloc)
    alloc = f_9512c0();
  cSPUIFrameSequencer* p = (cSPUIFrameSequencer*)f_9512d0(0x60, 4, "UTFWin/cSPUIFrameSequencer", alloc);
  if (p) {
    p = new (p) cSPUIFrameSequencer();
    if (p)
      return ((IFactoryObj*)((char*)p + 8))->v3(0x105a94b);
  }
  return 0;
}
