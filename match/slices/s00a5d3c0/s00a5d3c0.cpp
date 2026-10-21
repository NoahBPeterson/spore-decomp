#include <windows.h>

typedef unsigned char byte;
typedef unsigned int u32;
typedef unsigned long long u64;

// EAPd (Pd external pack) objects: the list / serial / cputime / makenote / stripnote / poly
// classes, their setup functions and the shared small helpers.

namespace EA { namespace Audio { namespace Eapd {

// Pd's t_symbol is an 8-byte handle: the name plus the bound thing.
struct t_symbol {
    const char* s_name;     // +0x00
    void* s_thing;          // +0x04
};

} } }

using EA::Audio::Eapd::t_symbol;

// ---------------------------------------------------------------------------
// Pd runtime entry points.
// ---------------------------------------------------------------------------
t_symbol* gensym(t_symbol* s, const char* name);
void* class_new(const char* name, void* thing, void* newmethod, void* freemethod,
                int size, int flags, int type, ...);
int class_addlist(void* c, void* fn);
int class_addmethod(void* c, void* fn, ...);
int class_doaddfloat(void* c, void* fn);
int class_addbang(void* c, void* fn);
int class_sethelpsymbol(void* c, const char* name, void* thing);
int class_addcreator(void* fn, const char* name, void* thing, int type, int extra);
void* pd_new(void* c);
void* canvas_getcurrent();
int pd_bind(void* canvas, void* owner, const char* name);
void* outlet_new(void* x, const char* type, void* sel);
void* inlet_new(void* x, void* owner, const char* type, void* sel,
                const char* type2, void* sel2);
void* floatinlet_new(void* x, void* val);
void outlet_float(void* outlet, float f);
void* clock_new(void* owner, void* fn);
void clock_free(void* clk);
void clock_delay(void* clk, float del);
void* getbytes(int size, const char* tag);
void freebytes(void* ptr, int size);
void sys_vgui(void* canvas, void* name, const char* fmt);
void eapd_shell(const char* fmt, ...);
int sprintf(char* buf, const char* fmt, ...);

// ---------------------------------------------------------------------------
// Class globals, one per registered Pd class, and the shared Pd symbols.
// ---------------------------------------------------------------------------
void* g_listTrimClass_167568c;
void* g_listMessageClass_1675698;
void* g_cputimeClass_167569c;
void* g_serialClass_16756a0;
void* g_namecanvasClass_16756a4;
void* g_loadbangClass_16756a8;
void* g_polyClass_16756ac;
void* g_stripnoteClass_16756b0;
void* g_unknownClass_16756b4;
void* g_makenoteClass_16756b8;
void* g_newestObject_16753f4;

t_symbol g_emptySymbol_167589c;         // "" symbol
t_symbol g_listSymbol_16758ac;          // "list"
t_symbol g_bangSymbol_16758b4;          // "bang"
t_symbol g_floatSymbol_16758c4;         // "float"

int g_outletCount_167545c;

// Intra-slice callees and the Pd routines of the neighbouring slices.
void* list_append_new(int n, int flag, int ac, void* av);
void* list_prepend_new(int n, int flag, int ac, void* av);
void* list_split_new(float f);
void* list_trim_new();
void* list_message_new(const char* name, void* thing);
void* list_message_ctor(t_symbol* s);
void list_message_list(void* x, t_symbol* s, int ac, void* av);
float atom_getfloat_at(int i, int ac, void* av);
byte alist_setup();
byte list_append_setup();
byte list_prepend_setup();
byte list_split_setup();
byte list_trim_setup();
byte list_message_setup();
byte loadbang_setup();
byte serial_setup();
byte cputime_setup();
byte makenote_setup();
byte stripnote_setup();
void* loadbang_new(t_symbol* s);
void* list_new(void* x, int n, int flag, int ac, void* av);
void loadbang_bang(void* x);
void namcanvas_free(void* x);
void serial_float(void* x, float f);
void serial_new(float f);
void cputime_bang(void* x);
void cputime_bang2(void* x, float f);
void* cputime_new();
void* makenote_new(float f1, float f2);
void makenote_free_all(void* x);
void makenote_float(void* x, float f);
void makenote_release_all(void* x);
void makenote_tick(void* t);
void* namcanvas_new(t_symbol* s, char* name);
void* stripnote_new();
void stripnote_float(void* x, float f);
void* poly_new(float f1, float f2);

// ---------------------------------------------------------------------------
// 0x00a5d3c0  list_message_setup
// ---------------------------------------------------------------------------
// @ 0x00a5d3c0
byte list_message_setup()
{
    t_symbol local;
    t_symbol* s = gensym(&local, "list message");
    g_listMessageClass_1675698 = class_new(s->s_name, s->s_thing, (void*)list_message_ctor,
                                           0, 0x30, 0, 6, 0);
    byte ok = g_listMessageClass_1675698 != 0;
    byte added = class_addlist(g_listMessageClass_1675698, (void*)list_message_list);
    class_sethelpsymbol(g_listTrimClass_167568c, g_listSymbol_16758ac.s_name,
                        g_listSymbol_16758ac.s_thing);
    return (byte)(added & ok);
}

// ---------------------------------------------------------------------------
// 0x00a5d430  list_new: dispatch the "append"/"prepend"/"split"/... selector
// ---------------------------------------------------------------------------
// @ 0x00a5d430
void* list_new(void* x, int n, int flag, int ac, void* av)
{
    if (ac != 0 && *(int*)av == 2)
    {
        int selector = ((int*)av)[1];
        t_symbol local;

        if (selector == (int)gensym(&local, "append")->s_name)
        {
            g_newestObject_16753f4 = list_append_new(n, flag, ac - 1, (char*)av + 0xc);
        }
        else if (selector == (int)gensym(&local, "prepend")->s_name)
        {
            g_newestObject_16753f4 = list_prepend_new(n, flag, ac - 1, (char*)av + 0xc);
        }
        else if (selector == (int)gensym(&local, "split")->s_name)
        {
            g_newestObject_16753f4 = list_split_new(atom_getfloat_at(1, ac, av));
        }
        else if (selector == (int)gensym(&local, "trim")->s_name)
        {
            g_newestObject_16753f4 = list_trim_new();
        }
        else if (selector == (int)gensym(&local, "message")->s_name)
        {
            t_symbol* args;
            if (ac > 1 && ((int*)av)[3] == 2)
                args = (t_symbol*)((char*)av + 0x10);
            else
                args = &g_emptySymbol_167589c;
            g_newestObject_16753f4 = list_message_new(args->s_name, args->s_thing);
        }
        else
        {
            g_newestObject_16753f4 = 0;
        }
        return g_newestObject_16753f4;
    }

    g_newestObject_16753f4 = list_append_new(n, flag, ac, av);
    return g_newestObject_16753f4;
}

// ---------------------------------------------------------------------------
// 0x00a5d5a0  x_list_setup: installs every list class and the "list" creator
// ---------------------------------------------------------------------------
// @ 0x00a5d5a0
byte x_list_setup()
{
    byte a = alist_setup();
    byte b = list_append_setup();
    byte c = list_prepend_setup();
    byte d = list_split_setup();
    byte e = list_trim_setup();
    byte f = list_message_setup();
    byte g = class_addcreator((void*)list_new, g_listSymbol_16758ac.s_name,
                              g_listSymbol_16758ac.s_thing, 9, 0);
    return (byte)(g & a & 1 & b & c & d & e & f);
}

// 0x00a5d5f0 (unnamed in the binary): the loadbang object itself, its single outlet
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

// ---------------------------------------------------------------------------
// 0x00a5d620  loadbang_setup
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00a5d690  namcanvas_new
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00a5d6e0  namcanvas free method: redraw the bind name
// ---------------------------------------------------------------------------
// @ 0x00a5d6e0
void namcanvas_free(void* x)
{
    char* name = *(char**)((char*)x + 0x2c);
    if (*name != 0)
        sys_vgui(*(void**)((char*)x + 0x30), *(void**)((char*)x + 0x28), name);
}

// 0x00a5d700 (unnamed in the binary): the serial object's float method, talks Tcl to the com port
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

// ---------------------------------------------------------------------------
// 0x00a5d770  serial_new
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00a5d7a0  serial_setup
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00a5d7f0  cputime_bang: sample the process times into the object
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00a5d840  cputime_bang2: elapsed process time in 100us units, fanned out
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00a5d900  cputime_new
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00a5d990  cputime_setup
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00a5da10  x_misc_setup: loadbang, namecanvas, serial, cputime
// ---------------------------------------------------------------------------
// @ 0x00a5da10
int x_misc_setup()
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

// ---------------------------------------------------------------------------
// 0x00a5da60  makenote_new
// ---------------------------------------------------------------------------
// @ 0x00a5da60
void* makenote_new(float f1, float f2)
{
    void* x = pd_new(g_makenoteClass_16756b8);
    if (x != 0)
    {
        void* f2inlet = (char*)x + 0x2c;
        *(float*)((char*)x + 0x28) = f1;
        *(float*)f2inlet = f2;
        floatinlet_new(x, (char*)x + 0x28);
        floatinlet_new(x, f2inlet);
        *(void**)((char*)x + 0x30) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(void**)((char*)x + 0x34) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(int*)((char*)x + 0x38) = 0;
    }
    return x;
}

// ---------------------------------------------------------------------------
// 0x00a5dae0  makenote_tick: the hung note expires
// ---------------------------------------------------------------------------
// @ 0x00a5dae0
void makenote_tick(void* t)
{
    void** tick = (void**)t;
    int* x = (int*)tick[3];

    g_outletCount_167545c++;
    if (g_outletCount_167545c < 1000)
    {
        for (void** o = *(void***)(x[0x34 / 4] + 8); o != 0; o = (void**)*o)
            outlet_float(o[1], 0.0f);
    }
    float value = ((float*)tick)[2];
    if (g_outletCount_167545c < 1000)
    {
        for (void** o = *(void***)(x[0x30 / 4] + 8); o != 0; o = (void**)*o)
            outlet_float(o[1], value);
    }
    g_outletCount_167545c--;

    void** prev = (void**)x[0x38 / 4];
    if (prev == tick)
    {
        x[0x38 / 4] = (int)tick[1];
    }
    else
    {
        for (void** cur = (void**)prev[1]; cur != 0; cur = (void**)cur[1])
        {
            if (cur == tick)
            {
                prev[1] = cur[1];
                break;
            }
            prev = cur;
        }
    }
    clock_free(tick[0]);
    freebytes(tick, 0x10);
}

// ---------------------------------------------------------------------------
// 0x00a5dbd0  makenote_float
// ---------------------------------------------------------------------------
// @ 0x00a5dbd0
void makenote_float(void* x, float f)
{
    float velocity = *(float*)((char*)x + 0x28);
    if (velocity != 0.0f)
    {
        g_outletCount_167545c++;
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x34) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], velocity);
        }
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x30) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], f);
        }
        g_outletCount_167545c--;

        void** tick = (void**)getbytes(0x10, "EAPd/t_hang");
        tick[1] = *(void**)((char*)x + 0x38);
        *(void***)((char*)x + 0x38) = tick;
        ((float*)tick)[2] = f;
        tick[3] = x;
        tick[0] = clock_new(tick, (void*)makenote_tick);

        float delay = *(float*)((char*)x + 0x2c);
        if (delay >= 0.0f)
            clock_delay(tick[0], delay);
        else
            clock_delay(tick[0], 0.0f);
    }
}

// ---------------------------------------------------------------------------
// 0x00a5dcf0  makenote stop method: release every hung note
// ---------------------------------------------------------------------------
// @ 0x00a5dcf0
void makenote_release_all(void* x)
{
    void** tick = *(void***)((char*)x + 0x38);
    while (tick != 0)
    {
        g_outletCount_167545c++;
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x34) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], 0.0f);
        }
        float value = ((float*)tick)[2];
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x30) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], value);
        }
        g_outletCount_167545c--;

        *(void***)((char*)x + 0x38) = (void**)tick[1];
        clock_free(tick[0]);
        freebytes(tick, 0x10);
        tick = *(void***)((char*)x + 0x38);
    }
}

// ---------------------------------------------------------------------------
// 0x00a5ddc0  makenote_free: drop the pending ticks without output
// ---------------------------------------------------------------------------
// @ 0x00a5ddc0
void makenote_free_all(void* x)
{
    void** tick = *(void***)((char*)x + 0x38);
    while (tick != 0)
    {
        *(void***)((char*)x + 0x38) = (void**)tick[1];
        clock_free(tick[0]);
        freebytes(tick, 0x10);
        tick = *(void***)((char*)x + 0x38);
    }
}

// ---------------------------------------------------------------------------
// 0x00a5de00  makenote_setup
// ---------------------------------------------------------------------------
// @ 0x00a5de00
byte makenote_setup()
{
    t_symbol local;
    t_symbol* s = gensym(&local, "makenote");
    g_makenoteClass_16756b8 = class_new(s->s_name, s->s_thing, (void*)makenote_new,
                                        (void*)makenote_free_all, 0x3c, 0, 5, 5, 0);
    byte ok = g_makenoteClass_16756b8 != 0;
    byte b1 = class_doaddfloat(g_makenoteClass_16756b8, (void*)makenote_float);
    t_symbol* s2 = gensym(&local, "stop");
    byte b2 = class_addmethod(g_makenoteClass_16756b8, (void*)makenote_release_all,
                              (void*)s2->s_name, s2->s_thing, 0);
    t_symbol* s3 = gensym(&local, "clear");
    byte b3 = class_addmethod(g_makenoteClass_16756b8, (void*)makenote_free_all,
                              (void*)s3->s_name, s3->s_thing, 0);
    return (byte)(b3 & b2 & b1 & ok);
}

// ---------------------------------------------------------------------------
// 0x00a5deb0  stripnote_new
// ---------------------------------------------------------------------------
// @ 0x00a5deb0
void* stripnote_new()
{
    void* x = pd_new(g_stripnoteClass_16756b0);
    if (x != 0)
    {
        floatinlet_new(x, (char*)x + 0x28);
        *(void**)((char*)x + 0x2c) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(void**)((char*)x + 0x30) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
    }
    return x;
}

// ---------------------------------------------------------------------------
// 0x00a5df10  stripnote_float: pass the note through unless velocity is zero
// ---------------------------------------------------------------------------
// @ 0x00a5df10
void stripnote_float(void* x, float f)
{
    float velocity = *(float*)((char*)x + 0x28);
    if (velocity != 0.0f)
    {
        g_outletCount_167545c++;
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x30) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], velocity);
        }
        if (g_outletCount_167545c < 1000)
        {
            for (void** o = *(void***)(*(int*)((char*)x + 0x2c) + 8); o != 0; o = (void**)*o)
                outlet_float(o[1], f);
        }
        g_outletCount_167545c--;
    }
}

// ---------------------------------------------------------------------------
// 0x00a5dfc0  stripnote_setup
// ---------------------------------------------------------------------------
// @ 0x00a5dfc0
byte stripnote_setup()
{
    t_symbol local;
    t_symbol* s = gensym(&local, "stripnote");
    g_stripnoteClass_16756b0 = class_new(s->s_name, s->s_thing, (void*)stripnote_new, 0, 0x34, 0, 0);
    byte ok = g_stripnoteClass_16756b0 != 0;
    byte added = class_doaddfloat(g_stripnoteClass_16756b0, (void*)stripnote_float);
    return (byte)(added & ok);
}

// ---------------------------------------------------------------------------
// 0x00a5e010  poly_new: a polyphonic voice allocator
// ---------------------------------------------------------------------------
// @ 0x00a5e010
void* poly_new(float f1, float f2)
{
    int voices = (int)f1;
    void* x = pd_new(g_polyClass_16756ac);
    if (x != 0)
    {
        if (voices < 1)
            voices = 1;
        *(int*)((char*)x + 0x28) = voices;
        void** voice = (void**)getbytes(voices * 0xc, "EAPd/t_voice");
        *(void***)((char*)x + 0x2c) = voice;
        for (int i = voices; i != 0; --i)
        {
            *(float*)voice = 0.0f;
            voice[1] = 0;
            voice[2] = 0;
            voice += 3;
        }
        *(float*)((char*)x + 0x30) = 0.0f;
        *(int*)((char*)x + 0x40) = (f2 != 0.0f);
        floatinlet_new(x, (char*)x + 0x30);
        outlet_new(x, g_floatSymbol_16758c4.s_name, g_floatSymbol_16758c4.s_thing);
        *(void**)((char*)x + 0x34) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(void**)((char*)x + 0x38) = outlet_new(x, g_floatSymbol_16758c4.s_name,
                                                g_floatSymbol_16758c4.s_thing);
        *(int*)((char*)x + 0x3c) = 0;
    }
    return x;
}
