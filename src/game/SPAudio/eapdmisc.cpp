// src/game/SPAudio/eapdmisc.cpp -- migrated from slice(s) s00a5d3c0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdmisc.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <windows.h>

// ---- items of slice s00a5d3c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol {
    const char* s_name;     // +0x00
    void* s_thing;          // +0x04
};
}
}
}
using EA::Audio::Eapd::t_symbol;
t_symbol* gensym(t_symbol* s, const char* name);
void* class_new(const char* name, void* thing, void* newmethod, void* freemethod,
                int size, int flags, int type, ...);
int class_addmethod(void* c, void* fn, ...);
int class_doaddfloat(void* c, void* fn);
int class_addbang(void* c, void* fn);
void* pd_new(void* c);
void* canvas_getcurrent();
int pd_bind(void* canvas, void* owner, const char* name);
void* outlet_new(void* x, const char* type, void* sel);
void* inlet_new(void* x, void* owner, const char* type, void* sel,
                const char* type2, void* sel2);
void outlet_float(void* outlet, float f);
void sys_vgui(void* canvas, void* name, const char* fmt);
void eapd_shell(const char* fmt, ...);
int sprintf(char* buf, const char* fmt, ...);
void* g_cputimeClass_167569c;
void* g_serialClass_16756a0;
void* g_namecanvasClass_16756a4;
void* g_loadbangClass_16756a8;
t_symbol g_bangSymbol_16758b4;          // "bang"
int g_outletCount_167545c;
byte loadbang_setup();
byte serial_setup();
byte cputime_setup();
void* loadbang_new(t_symbol* s);
void loadbang_bang(void* x);
void namcanvas_free(void* x);
void serial_float(void* x, float f);
void serial_new(float f);
void cputime_bang(void* x);
void cputime_bang2(void* x, float f);
void* cputime_new();
void* namcanvas_new(t_symbol* s, char* name);
void* loadbang_new(t_symbol* s)
{
    void* x = pd_new(g_loadbangClass_16756a8);
    if (x != 0)
    {
        outlet_new(x, g_bangSymbol_16758b4.s_name, g_bangSymbol_16758b4.s_thing);
        return x;
    }
    return x;
}
void serial_float(void* x, float f)
{
    char buf[0x1f4];
    int value = (int)f;
    int* opened = (int*)((char*)x + 0x2c);
    if (*opened == 0)
    {
        eapd_shell("com%d_open\n", *(int*)((char*)x + 0x28));
        *opened = 1;
    }
    sprintf(buf, "com%d_send \"\\%3.3o\"\n", *(int*)((char*)x + 0x28), value);
    eapd_shell(buf);
}
// ---- items of slice s00a5d3c0 end

// @ 0x00a5d620
byte loadbang_setup()
{
    t_symbol local;
    t_symbol* s = gensym(&local, "loadbang");
    g_loadbangClass_16756a8 = class_new(s->s_name, s->s_thing, (void*)loadbang_new,
                                        0, 0x28, 8, 0);
    byte ok = g_loadbangClass_16756a8 != 0;
    t_symbol* s2 = gensym(&local, "loadbang");
    byte added = class_addmethod(g_loadbangClass_16756a8, (void*)loadbang_bang,
                                 (void*)s2->s_name, s2->s_thing, 0);
    return (byte)(added & ok);
}

// @ 0x00a5d690
void* namcanvas_new(t_symbol* s, char* name)
{
    void* x = pd_new(g_namecanvasClass_16756a4);
    if (x != 0)
    {
        void* canvas = canvas_getcurrent();
        *(void**)((char*)x + 0x30) = canvas;
        *(t_symbol**)((char*)x + 0x28) = s;
        *(char**)((char*)x + 0x2c) = name;
        if (*name != 0)
            pd_bind(canvas, s, name);
    }
    return x;
}

// @ 0x00a5d6e0
void namcanvas_free(void* x)
{
    char* name = *(char**)((char*)x + 0x2c);
    if (*name != 0)
        sys_vgui(*(void**)((char*)x + 0x30), *(void**)((char*)x + 0x28), name);
}

// @ 0x00a5d770
void serial_new(float f)
{
    int n = (int)f;
    void* x = pd_new(g_serialClass_16756a0);
    if (x != 0)
    {
        if (n == 0)
            n = 1;
        *(int*)((char*)x + 0x28) = n;
        *(void**)((char*)x + 0x2c) = 0;
    }
}

// @ 0x00a5d7a0
byte serial_setup()
{
    t_symbol local;
    t_symbol* s = gensym(&local, "serial");
    g_serialClass_16756a0 = class_new(s->s_name, s->s_thing, (void*)serial_new, 0, 0x30, 0, 5, 0);
    byte ok = g_serialClass_16756a0 != 0;
    byte added = class_doaddfloat(g_serialClass_16756a0, (void*)serial_float);
    return (byte)(added & ok);
}

// @ 0x00a5d7f0
void cputime_bang(void* x)
{
    _FILETIME creation;
    _FILETIME exit;
    LPFILETIME kernel = (LPFILETIME)((char*)x + 0x28);
    LPFILETIME user = (LPFILETIME)((char*)x + 0x30);
    if (!GetProcessTimes(GetCurrentProcess(), &creation, &exit, kernel, user))
    {
        *(int*)((char*)x + 0x38) = 1;
        *(u32*)((char*)x + 0x28) = 0;
        *(u32*)((char*)x + 0x2c) = 0;
        *(u32*)((char*)x + 0x30) = 0;
        *(u32*)((char*)x + 0x34) = 0;
    }
}

// @ 0x00a5d840
void cputime_bang2(void* x, float f)
{
    _FILETIME creation;
    _FILETIME exit;
    _FILETIME kernel;
    _FILETIME user;

    if (!GetProcessTimes(GetCurrentProcess(), &creation, &exit, &kernel, &user))
    {
        f = 0.0f;
    }
    else
    {
        u64 kernelTime = ((u64)kernel.dwHighDateTime << 32) | kernel.dwLowDateTime;
        u64 userTime = ((u64)user.dwHighDateTime << 32) | user.dwLowDateTime;
        u64 elapsed = kernelTime - *(u64*)((char*)x + 0x30)
                                 - *(u64*)((char*)x + 0x28) + userTime;
        f = (float)(__int64)elapsed * 0.0001f;
    }

    if (g_outletCount_167545c + 1 > 999)
        return;
    g_outletCount_167545c++;

    for (void** o = *(void***)(*(int*)((char*)x + 0xc) + 8); o != 0; o = (void**)*o)
        outlet_float(o[1], f);

    g_outletCount_167545c--;
}

// @ 0x00a5d900
void* cputime_new()
{
    void* x = pd_new(g_cputimeClass_167569c);
    if (x != 0)
    {
        t_symbol local1;
        t_symbol* f = gensym(&local1, "float");
        outlet_new(x, f->s_name, f->s_thing);

        t_symbol local2;
        t_symbol local3;
        t_symbol* b2 = gensym(&local2, "bang2");
        t_symbol* bang = gensym(&local3, "bang");
        inlet_new(x, x, bang->s_name, bang->s_thing, b2->s_name, b2->s_thing);

        *(int*)((char*)x + 0x38) = 0;
        cputime_bang(x);
    }
    return x;
}

// @ 0x00a5d990
byte cputime_setup()
{
    t_symbol local;
    t_symbol* s = gensym(&local, "cputime");
    g_cputimeClass_167569c = class_new(s->s_name, s->s_thing, (void*)cputime_new, 0, 0x40, 0, 0);
    byte ok = g_cputimeClass_167569c != 0;
    byte b1 = class_addbang(g_cputimeClass_167569c, (void*)cputime_bang);
    t_symbol* s2 = gensym(&local, "bang2");
    byte b2 = class_addmethod(g_cputimeClass_167569c, (void*)cputime_bang2,
                              (void*)s2->s_name, s2->s_thing, 0);
    return (byte)(b2 & ok & b1);
}

// @ 0x00a5da10
namespace EA {
namespace Audio {
namespace Eapd {
bool x_misc_setup()
{
    t_symbol local;
    loadbang_setup();
    t_symbol* s = gensym(&local, "namecanvas");
    g_namecanvasClass_16756a4 = class_new(s->s_name, s->s_thing, (void*)namcanvas_new,
                                          (void*)namcanvas_free, 0x34, 8, 6, 0);
    serial_setup();
    cputime_setup();
    return (byte)1;
}
}
}
}  // namespace EA::Audio::Eapd
