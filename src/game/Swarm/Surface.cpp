// src/game/Swarm/Surface.cpp -- migrated from slice(s) s00a7c630 by tools/migrate/rewrite.py
// Object file: Swarm/Surface.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00a7c630 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  uint32;
static bool HasFlag(void* args, const char* name)
{ return ((bool (__fastcall*)(void*, int, const char*))0x008380b0)(args, 0, name); }
static const char** OptionArguments(void* args, const char* name, int n)
{ return ((const char** (__fastcall*)(void*, int, const char*, int))0x00838330)(args, 0, name, n); }
static const char** OptionArguments2(void* args, const char* name, void* out, int a, int b)
{ return ((const char** (__fastcall*)(void*, int, const char*, void*, int, int))0x00838130)
             (args, 0, name, out, a, b); }
static uintptr_t MapFindA(void* self, const char* name)
{ return ((uintptr_t (__fastcall*)(void*, int, const char*))0x00a6eaf0)(self, 0, name); }
static void MarkAllProcessed(void* args)
{ ((void (__fastcall*)(void*, int))0x00837f60)(args, 0); }
// ---- items of slice s00a7c630 end

// @ 0x00a7d280
void __cdecl ParseSurfaceOptions(void* a, void* b, uint32* opts, int* owner)
{
  int* xf = (int*)owner[5];
  void* args = 0;
  bool ok = ((bool (__thiscall*)(void*, void*, void**))
             (*(void***)owner[0x23])[0x18 / 4])((void*)owner[0x23], a, &args);
  if (!ok) {
    if (((bool (__thiscall*)(void*, int))(*(void***)owner)[0x14 / 4])(owner, 2))
      return;
    opts[2] = 0xffffffffu;
    opts[3] = 0xffffffffu;
  }

#define HASFLAG(s) HasFlag(args, s)
#define OPT1(s)    OptionArguments(args, s, 1)
  if (HASFLAG("pin")) {
    *opts |= 2;
  } else if (HASFLAG("pinMove")) {
    *opts |= 4;
  } else if (HASFLAG("pinEmit")) {
    *opts |= 8;
    const char** o = (const char**)OPT1("surfaceOffset");
    if (o) {
      float v = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o);
      *(float*)&opts[8] = v;
    }
  } else {
    const char** o = (const char**)OptionArguments(args, "repel", 2);
    if (o) {
      *(float*)&opts[9]  = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, o[0]);
      *(float*)&opts[10] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, o[1]);
      const char** s;
      if ((s = (const char**)OPT1("scout")))
        *(float*)&opts[11] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *s);
      if ((s = (const char**)OPT1("vertical")))
        *(float*)&opts[12] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *s);
      if ((s = (const char**)OPT1("killHeight")))
        *(float*)&opts[13] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *s);
    } else if (HASFLAG("align")) {
      *opts |= 0x20;
    } else {
      const char** o2 = (const char**)OptionArguments2(args, "bounce", &a, 1, 2);
      if (o2) {
        *(float*)&opts[4] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o2);
        *opts |= 1;
        if ((o = (const char**)OPT1("slide")))
          *(float*)&opts[5] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o);
        if ((o = (const char**)OPT1("radius")))
          *(float*)&opts[6] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o);
        if ((o = (const char**)OPT1("death")))
          *(float*)&opts[7] = ((float (__thiscall*)(int*, const char*))xf[0x98 / 4])(xf, *o);
        if ((o = (const char**)OPT1("collideEffect")))
          (uintptr_t&)opts[0xe] = MapFindA((void*)(uintptr_t)owner[5], *o);
        if ((o = (const char**)OPT1("deathEffect")))
          (uintptr_t&)opts[0xf] = MapFindA((void*)(uintptr_t)owner[5], *o);
      }
    }
  }

  if (HASFLAG("sourceSpace"))
    *opts |= 0x40;
  if (HASFLAG("worldSpace"))
    *opts |= 0x80;

  if (b != 0)
    ((void (__cdecl*)(void*, void*, uint32*))b)(xf, args, opts);
  MarkAllProcessed(args);
#undef HASFLAG
#undef OPT1
}
