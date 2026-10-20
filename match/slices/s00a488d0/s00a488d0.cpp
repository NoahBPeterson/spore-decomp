// slice s00a488d0 -- EA::Audio::Eapd (EA's embedded Pd 0.4x): m_class.c / m_sched.c / s_loader.c core.
//  00a488d0 zgetfn                 00a490f0 clock_set            00a49390 pd_new
//  00a48910 class_addfloat          00a49170 clock_pause          00a493d0 pd_free
//  00a48980 class_addcreator        00a491a0 clock_unpause        00a49450 sys_register_loader
//  00a48a30 class_addmethod0        00a491d0 clock_ispaused       00a49490 pd_pushsym
//  00a48a80 class_addmethod1        00a491e0 clock_delay          00a49500 pd_popsym
//  00a48ad0 class_addmethod2        00a49210 clock_getlogicaltime 00a49560 pd_bang
//  00a48b30 class_addmethod4        00a49220 clock_gettimesince  00a49570 outlet_float
//  00a48b90 class_addmethod5        00a49240 clock_getlogicaltimeafter 00a49590 pd_symbol
//  00a48bf0 class_new                00a49260 clock_free           00a495b0 pd_list
//  00a48db0 class_addcreator (m)    00a492c0 clock_setftime       00a495e0 conf_init
//  00a48e00 class_addcreator (m)    00a492e0 sched_tick           00a49610 getbytes
//  00a48e50 class_new (m)           00a49390 pd_new             00a49650 freebytes
//  00a48ea0 class_new (m)
//  00a48f00 class_new (m)
//  00a48f60 mess_init
//  00a49080 clock_new
//  00a490b0 clock_unset
// Names follow symbols/pdb_names.json (EA::Audio::Eapd::*), the Pd 0.4x source names
// (m_class.c, m_sched.c, s_loader.c). Struct layouts are EA's: only the fields these functions
// touch are declared, at their binary offsets. Callees are masked relocations.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (see manifest).
#include "types.h"

typedef unsigned int uintptr_t;   // VS2008 <stdint.h> absent from types.h

namespace EA { namespace Audio { namespace Eapd {

// ---------------------------------------------------------------- Pd core types
struct t_class;
struct t_gobj;
// t_symbol is passed by value as two words (name, thing) in EA's Eapd ABI.
struct t_symbol {
    void* s_name;    // +0
    void* s_thing;   // +4
};
struct t_class {
    void* c_name;         // +0
    void* c_helpname;     // +4
    void* c_helpdir;      // +8
    char  pad0[0x10 - 0xc];
    void* c_filetypes;    // +0x10
    void* c_filedefault;  // +0x14
    unsigned c_size;      // +0x18
    void* c_methods;      // +0x1c
    int   c_nmethod;      // +0x20
    void* c_freemethod;   // +0x24
    void* c_bangmethod;   // +0x28
    void* c_floatmethod;  // +0x2c
    void* c_symbolmethod; // +0x30
    void* c_listmethod;   // +0x34
    void* c_anymethod;    // +0x38
    void* c_wb;           // +0x3c
    void* c_savefn;       // +0x40
    void* c_propertiesfn; // +0x44
    char  c_gobj;         // +0x48
    char  c_patchable;    // +0x49
    char  c_firstin;      // +0x4a
    t_class* c_next;      // +0x4c
};
struct t_gobj {
    t_class* g_pd;    // +0
    t_gobj*  g_next;  // +4
    char pad[0x24 - 8];
    void*    o_save;  // +0x24
    char pad2[0x49 - 0x28];
    char     o_flags; // +0x49
};
// atom slot: [0]=type code, [1]=payload word, [2]=payload word
struct t_atom {
    int   a_type;    // +0
    float a_w;       // +4
    void* a_w2;      // +8
};
struct t_clock {
    double   c_settime;   // +0
    int      c_set;       // +8
    void*    c_owner;     // +0xc
    void*    c_method;    // +0x10
    t_clock* c_next;      // +0x14
};
struct t_sysstack {         // 0x10-byte node
    t_gobj*     s_what;     // +0
    t_symbol*   s_sym_a;    // +4
    t_symbol*   s_sym_b;    // +8
    t_sysstack* s_next;     // +0xc
};
struct t_register {         // 0x10-byte loader node
    void*       r_interp;   // +0
    void*       r_key_a;    // +4
    void*       r_key_b;    // +8
    t_register* r_next;     // +0xc
};
// PD_THIS instance: alloc at vtable +4, free at vtable +0xc.
struct t_pdinstance {
    virtual void  pad0();
    virtual void* alloc(int n, const char* tag);   // +4
    virtual void  pad2();
    virtual void  freemem(void* p);                // +0xc
};

// ---------------------------------------------------------------- globals (masked relocs)
extern t_class*    gpObjectMaker;   // 0x16753e8
extern t_class*    gpTemplateMaker; // 0x1675408
extern t_class*    gclasslist;      // 0x167540c
extern t_symbol    gListSymbol;     // 0x16753ec  (list selector copy; 0x16753f8/0x1675400 are later copies)
extern t_symbol    gListSym3;       // 0x1675400  (third "list" copy)
extern t_symbol    gListSymB;       // 0x16753f8  (second "list" copy)
extern t_symbol    gFloatSymbol;    // 0x16758c4 / c8   ("float")
extern t_symbol    gBangSymbol;     // 0x16758b4 / b8   ("bang")
extern t_symbol    gSysSym;         // 0x16758bc / c0   (sys_gui selector)
extern t_symbol    gAnythingSym;    // 0x167589c / a0   ("anything")
extern t_symbol    gListSym2;       // 0x16758ac / b0   ("list", used by pd_list)
extern void*       gAnythingThing;  // 0x16753f0  (second word of the "anything" copy)
// Raw selector-name words (first word of the corresponding t_symbol).
extern void* gBangName;             // 0x16758b4  ("bang")
extern void* gFloatName;            // 0x16758c4  ("float")
extern void* gSymbolName;           // 0x1675894  ("symbol")
extern void* gListName;             // 0x16758ac  ("list")
extern void* gAnythingName;         // 0x16758cc  ("anything")
extern t_clock*    s_clocklist;     // 0x1675410
extern double      s_systime;       // 0x1675418
extern double      s_time;          // 0x1675420
extern double      s_realtime;      // 0x1675428
extern t_sysstack* s_stack;        // 0x1675444  (sys_register_loader / pd_pushsym list head)
extern t_symbol    gObjectSym;      // 0x16758a4 / a8
extern const double s_ctime;        // 0x1454410  (clock_new's initial c_settime constant)
extern const float  gTickScale;     // 0x145440c  (sched_tick's clamp constant)

// ---------------------------------------------------------------- externs (masked relocs)
inline unsigned int strlen(const char* s) { unsigned int n = 0; while (s[n]) ++n; return n; }
inline int strcmp(const char* a, const char* b) { while (*a && *a == *b) { ++a; ++b; } return (unsigned char)*a - (unsigned char)*b; }
void* gensym(t_symbol* out, const char* s);                                    // 0xa675f0
bool  class_addmethod(t_class* c, void* fn, void* sel_lo, void* sel_hi, int* atoms); // 0xa47e70
bool  class_addlist(t_class* c, void* fn);                                     // 0xa47f70
bool  class_addanything(t_class* c, void* fn);                                 // 0xa47f90
void  class_addpointer(t_class* c, void* fn, void* name_hi);                   // 0xa47fc0
void  sys_lock();                                                              // 0xa49d00
void  free_save_list(void* p);                                                 // 0xa49f20
void  free_gop_list(void* p);                                                  // 0xa49990
void  class_freemethod(void* o);                                               // 0xa46c50
void  sys_gui_acquire(void* obj, void* sel_a, void* sel_b);                    // 0xa671b0
void  sys_gui_release(void* obj, void* sel_a, void* sel_b);                    // 0xa67620
t_pdinstance* pdinstance();                                                    // 0xa67cb0
char  glob_init();                                                             // 0xa49be0
char  glob_setup();                                                            // 0xa51f40
char  s_loader_setup();                                                        // 0xa51f90
char  s_list_setup();                                                          // 0xa52000
void  memfill(void* d, int c, int n);                                          // 0x11e073e
void* getbytes(int n, const char* tag);                                        // 0xa49610
void  freebytes(void* p, int n);                                               // 0xa49650

// ============================================================ m_class.c

// @ 0x00a488d0
void* zgetfn(t_class** pp, void* name)
{
    t_class* c = *pp;
    int n = c->c_nmethod;
    char* e = (char*)c->c_methods + n * 0x24 - 0x24;
    while (n != 0) {
        --n;
        if (*(void**)e == name)
            return *(void**)(e + 8);
        e -= 0x24;
    }
    return 0;
}

// @ 0x00a48910
void class_addfloat(void* x, float f)
{
    t_class* c = *(t_class**)x;
    t_atom atoms[1];
    atoms[0].a_type = 1;
    atoms[0].a_w = f;
    if (c->c_listmethod != (void*)0x00a47d70) {
        typedef void (*ListFn)(void*, void*, void*, int, void*);
        ((ListFn)c->c_listmethod)(x, gListSym2.s_name, gListSym2.s_thing, 1, atoms);
    } else {
        typedef void (*SymFn)(void*, void*, void*, int, void*);
        ((SymFn)c->c_symbolmethod)(x, gFloatSymbol.s_name, gFloatSymbol.s_thing, 1, atoms);
    }
}

// @ 0x00a48980
bool class_addcreator(void* fn, void* sel, void* a3, void* a4)
{
    t_class* c = gpObjectMaker;
    char ok = 0;
    if (c) {
        if (sel == gBangName) {
            ok = 0;
            if (!fn)
                return ok;
            c->c_bangmethod = fn;
            return 1;
        }
        if (sel == gFloatName) {
            ok = 0;
            if (!fn)
                return ok;
            c->c_floatmethod = fn;
            return 1;
        }
        if (sel == gSymbolName) {
            ok = 0;
            if (!fn)
                return ok;
            c->c_symbolmethod = fn;
            return 1;
        }
        if (sel == gListName)
            return class_addlist(c, fn);
        if (sel == gAnythingName)
            return class_addanything(c, fn);
        return class_addmethod(c, fn, sel, a3, (int*)a4);
    }
    return ok != 0;
}

// @ 0x00a48a30
bool class_addmethod0(t_class* c, void* fn, t_symbol sel, void* t0)
{
    int atoms[7];
    atoms[6] = 0;
    atoms[1] = 0; atoms[2] = 0; atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}

// @ 0x00a48a80
bool class_addmethod1(t_class* c, void* fn, t_symbol sel, void* t0, void* t1)
{
    int atoms[7];
    atoms[6] = 1;
    atoms[2] = 0; atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}

// @ 0x00a48ad0
bool class_addmethod2(t_class* c, void* fn, t_symbol sel, void* t0, void* t1, void* t2)
{
    int atoms[7];
    atoms[6] = 2;
    atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[2] = (int)(uintptr_t)t2;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}

// @ 0x00a48b30
bool class_addmethod4(t_class* c, void* fn, t_symbol sel, void* t0, void* t1, void* t2, void* t3, void* t4)
{
    int atoms[7];
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[2] = (int)(uintptr_t)t2;
    atoms[3] = (int)(uintptr_t)t3;
    atoms[4] = (int)(uintptr_t)t4;
    atoms[6] = 4;
    atoms[5] = 0;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}

// @ 0x00a48b90
bool class_addmethod5(t_class* c, void* fn, t_symbol sel, void* t0, void* t1, void* t2, void* t3, void* t4, void* t5)
{
    int atoms[7];
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[2] = (int)(uintptr_t)t2;
    atoms[3] = (int)(uintptr_t)t3;
    atoms[4] = (int)(uintptr_t)t4;
    atoms[5] = (int)(uintptr_t)t5;
    atoms[6] = 5;
    return class_addmethod(c, fn, sel.s_name, sel.s_thing, atoms);
}

// @ 0x00a48bf0
t_class* class_new(t_symbol name, void* newmethod, void* freemethod, int size, int flags, t_atom* atoms)
{
    int type = flags & 3;
    if (type == 0)
        type = 3;
    if (newmethod) {
        class_addcreator(newmethod, name.s_name, name.s_thing, atoms);
        if (gListSymbol.s_name != gAnythingSym.s_name) {
            const char* p = (const char*)name.s_name;
            char n = (char)strlen(p);
            const char* q = (const char*)gAnythingThing;   // 0x16753f0
            char m = (char)strlen(q);
            if (m > n) {
                if (strcmp(p, q + (m - n)) == 0)
                    class_addcreator(name.s_name, *(void**)&gListSymbol.s_name, freemethod, atoms);
            }
        }
    }
    t_class* c = (t_class*)getbytes(0x50, "[class]");
    if (c != 0) {
        c->c_name = name.s_name;
        c->c_helpname = name.s_thing;
        class_addpointer(c, name.s_name, name.s_thing);
        c->c_size = (unsigned)size;
        c->c_methods = (void*)getbytes(0, "[methods]");
        c->c_nmethod = 0;
        c->c_freemethod = freemethod;
        c->c_bangmethod = (void*)0x00a47cb0;
        c->c_floatmethod = (void*)0x00a48910;
        c->c_symbolmethod = (void*)0x00a47d00;
        c->c_listmethod = (void*)0x00a47d70;
        c->c_anymethod = (void*)0x00c2e4e0;
        c->c_wb = (type != 3) ? (void*)0x01554364 : 0;
        c->c_gobj = (char)(type >= 2);
        c->c_firstin = (char)(~((unsigned)size >> 3) & 1);
        c->c_patchable = (char)(type == 3);
        {
            t_symbol* sel = &gListSymbol;
            if (sel->s_name == gAnythingSym.s_name)
                sel = &gListSym3;      // 0x1675400
            c->c_filetypes = sel->s_name;
            c->c_filedefault = sel->s_thing;
        }
        c->c_savefn = (type == 3) ? (void*)0x00a50e00 : (void*)0x00c2e4e0;
        c->c_next = gclasslist;
        gclasslist = c;
    }
    return c;
}

// @ 0x00a48db0  (class_addcreator with 1 extra atom)
bool class_addcreator_m(void* a0, void* a1, void* a2, void* a3, void* a4)
{
    int locals[7];
    locals[6] = 0;
    locals[1] = 0; locals[2] = 0; locals[3] = 0; locals[4] = 0; locals[5] = 0;
    locals[0] = (int)(uintptr_t)a3;
    return class_addcreator(a0, a1, a2, locals);
}

// @ 0x00a48e00  (class_addcreator with 2 extra atoms)
bool class_addcreator_m2(void* a0, void* a1, void* a2, void* a3, void* a4)
{
    int locals[7];
    locals[2] = 0; locals[3] = 0; locals[4] = 0; locals[5] = 0;
    locals[0] = (int)(uintptr_t)a3;
    locals[1] = (int)(uintptr_t)a4;
    locals[6] = 1;
    return class_addcreator(a0, a1, a2, locals);
}

// @ 0x00a48e50  (class_new with 1 leading type code)
t_class* class_new_m1(t_symbol name, void* newmethod, void* freemethod, int size, int flags, void* t0)
{
    int atoms[7];
    atoms[6] = 0;
    atoms[1] = 0; atoms[2] = 0; atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    return class_new(name, newmethod, freemethod, size, flags, (t_atom*)atoms);
}

// @ 0x00a48ea0  (class_new with 2 leading type codes)
t_class* class_new_m2(t_symbol name, void* newmethod, void* freemethod, int size, int flags, void* t0, void* t1)
{
    int atoms[7];
    atoms[2] = 0; atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[6] = 1;
    return class_new(name, newmethod, freemethod, size, flags, (t_atom*)atoms);
}

// @ 0x00a48f00  (class_new with 3 leading type codes)
t_class* class_new_m3(t_symbol name, void* newmethod, void* freemethod, int size, int flags, void* t0, void* t1, void* t2)
{
    int atoms[7];
    atoms[3] = 0; atoms[4] = 0; atoms[5] = 0;
    atoms[0] = (int)(uintptr_t)t0;
    atoms[1] = (int)(uintptr_t)t1;
    atoms[2] = (int)(uintptr_t)t2;
    atoms[6] = 2;
    return class_new(name, newmethod, freemethod, size, flags, (t_atom*)atoms);
}

// @ 0x00a48f60
bool mess_init()
{
    gListSymbol.s_name = gAnythingSym.s_name;
    gListSymbol.s_thing = gAnythingSym.s_thing;
    gListSymB.s_name = gAnythingSym.s_name;
    gListSymB.s_thing = gAnythingSym.s_thing;
    gListSym3.s_name = gAnythingSym.s_name;
    gListSym3.s_thing = gAnythingSym.s_thing;
    t_symbol tmp;
    t_symbol* s1 = (t_symbol*)gensym(&tmp, "list");
    int atoms[7];
    atoms[0] = 0; atoms[1] = 0; atoms[2] = 0; atoms[3] = 0;
    atoms[4] = 0; atoms[5] = 0; atoms[6] = 0;
    t_class* c1 = class_new(*s1, 0, 0, 4, 0, (t_atom*)atoms);
    gpObjectMaker = c1;
    char ok = (char)(c1 != 0);
    t_symbol tmp2;
    t_symbol* s2 = (t_symbol*)gensym(&tmp2, "object");
    atoms[0] = 0; atoms[1] = 0; atoms[2] = 0; atoms[3] = 0;
    atoms[4] = 0; atoms[5] = 0; atoms[6] = 0;
    t_class* c2 = class_new(*s2, 0, 0, 4, 0, (t_atom*)atoms);
    gpTemplateMaker = c2;
    ok &= (char)(c2 != 0);
    sys_gui_release(&gpTemplateMaker, gObjectSym.s_name, gObjectSym.s_thing);
    char al = 0;
    if (gpObjectMaker != 0 && (void*)0x00a48050 != 0) {
        gpObjectMaker->c_anymethod = (void*)0x00a48050;
        al = 1;
    }
    ok &= al;
    return ok != 0;
}

// @ 0x00a49080
t_clock* clock_new(void* owner, void* fn)
{
    t_clock* c = (t_clock*)getbytes(0x18, "clock");
    c->c_settime = s_ctime;
    c->c_set = 0;
    c->c_owner = owner;
    c->c_method = fn;
    c->c_next = 0;
    return c;
}

// @ 0x00a490b0
void clock_unset(t_clock* c)
{
    if (c->c_set == 1) {
        t_clock* o = s_clocklist;
        if (c == o) {
            s_clocklist = c->c_next;
            c->c_set = 0;
            return;
        }
        while (o->c_next != c)
            o = o->c_next;
        o->c_next = c->c_next;
    }
    c->c_set = 0;
}

// @ 0x00a490f0
void clock_set(t_clock* c, double systime)
{
    if (c->c_set == 1)
        clock_unset(c);
    double t = (s_time > systime) ? s_time : systime;
    c->c_settime = t;
    t_clock* cl = s_clocklist;
    if (cl == 0 || t < cl->c_settime) {
        c->c_next = cl;
        s_clocklist = c;
        c->c_set = 1;
    } else {
        t_clock* o = cl;
        t_clock* n = cl->c_next;
        while (n && n->c_settime <= t) {
            o = n;
            n = n->c_next;
        }
        o->c_next = c;
        c->c_set = 1;
        c->c_next = n;
    }
}

// @ 0x00a49170
void clock_pause(t_clock* c)
{
    if (c->c_set == 1) {
        double t = c->c_settime - s_time;
        clock_unset(c);
        c->c_set = 2;
        c->c_settime = t;
    }
}

// @ 0x00a491a0
void clock_unpause(t_clock* c)
{
    if (c->c_set == 2) {
        double t = c->c_settime + s_time;
        c->c_set = 0;
        clock_set(c, t);
    }
}

// @ 0x00a491d0
bool clock_ispaused(t_clock* c)
{
    return c->c_set == 2;
}

// @ 0x00a491e0
void clock_delay(t_clock* c, float delay)
{
    clock_set(c, (double)(delay * (float)0.001f) + s_time);
}

// @ 0x00a49210
double clock_getlogicaltime()
{
    return s_time;
}

// @ 0x00a49220
double clock_gettimesince(double systime)
{
    return (s_time - systime) * *(const double*)0x01454428;
}

// @ 0x00a49240
double clock_getlogicaltimeafter(float delay)
{
    return (double)delay * (float)0.001f + s_time;
}

// @ 0x00a49260
void clock_free(t_clock* c)
{
    if (c->c_set == 1) {
        t_clock* o = s_clocklist;
        if (c == o) {
            s_clocklist = c->c_next;
            c->c_set = 0;
            freebytes(c, 0x18);
            return;
        }
        while (o->c_next != c)
            o = o->c_next;
        o->c_next = c->c_next;
    }
    c->c_set = 0;
    freebytes(c, 0x18);
}

// @ 0x00a492c0
void clock_setftime(double systime)
{
    s_time = systime;
    s_realtime = systime;
}

// @ 0x00a492e0
void sched_tick(float nexttime)
{
    double base;
    if (nexttime > 0.0f) {
        base = s_realtime;
    } else {
        base = s_systime - s_realtime;
        if (base > (double)gTickScale)
            nexttime = gTickScale;
    }
    s_systime = base;
    double t = base + nexttime;
    while (s_clocklist && s_clocklist->c_settime <= t) {
        t_clock* c = s_clocklist;
        s_time = c->c_settime;
        if (c->c_set == 1)
            s_clocklist = c->c_next;
        c->c_set = 0;
        sys_lock();
        ((void (*)(void*))c->c_method)(c->c_owner);
    }
}

// @ 0x00a49390
void* pd_new(t_class* c)
{
    const char* tag = (const char*)c->c_helpname;
    t_gobj* o = (t_gobj*)getbytes(c->c_size, tag);
    o->g_pd = c;
    if (c->c_patchable) {
        *(void**)((char*)o + 0x10) = 0;
        *(void**)((char*)o + 0x0c) = 0;
        *(void**)((char*)o + 0x20) = gAnythingSym.s_name;
        *(void**)((char*)o + 0x24) = gAnythingSym.s_thing;
    }
    return o;
}

// @ 0x00a493d0
void pd_free(t_gobj* o)
{
    t_class* c = o->g_pd;
    if (c->c_freemethod)
        ((void (*)(void*))c->c_freemethod)(o);
    if (c->c_patchable) {
        void* p;
        while ((p = *(void**)((char*)o + 0x0c)) != 0) {
            free_save_list(p);
            if (!*(void**)((char*)o + 0x0c))
                break;
        }
        while ((p = *(void**)((char*)o + 0x10)) != 0) {
            free_gop_list(p);
            if (!*(void**)((char*)o + 0x10))
                break;
        }
        if (*(void**)((char*)o + 8))
            class_freemethod(*(void**)((char*)o + 8));
    }
    if (c->c_size)
        freebytes(o, c->c_size);
}

// @ 0x00a49450
bool sys_register_loader(void* a, void* b)
{
    t_sysstack* s = s_stack;
    s->s_sym_a = (t_symbol*)a;
    s->s_sym_b = (t_symbol*)b;
    t_sysstack* r = s->s_next;
    while (r) {
        if (r->s_sym_a == (t_symbol*)a)
            return true;
        r = r->s_next;
    }
    return false;
}

// @ 0x00a49490
void pd_pushsym(t_gobj* x)
{
    if (s_stack)
        sys_gui_acquire(*(void**)s_stack, gSysSym.s_name, gSysSym.s_thing);
    sys_gui_release(x, gSysSym.s_name, gSysSym.s_thing);
    t_sysstack* s = (t_sysstack*)getbytes(0x10, "sysstack");
    t_sysstack* next = s_stack;
    s->s_what = x;
    s->s_next = next;
    s->s_sym_a = (t_symbol*)gAnythingSym.s_name;
    s->s_sym_b = (t_symbol*)gAnythingSym.s_thing;
    s_stack = s;
}

// @ 0x00a49500
void pd_popsym(t_gobj* x)
{
    t_sysstack* s = s_stack;
    s_stack = s->s_next;
    freebytes(s, 0x10);
    sys_gui_acquire(x, gSysSym.s_name, gSysSym.s_thing);
    if (s_stack)
        sys_gui_release(*(void**)s_stack, gSysSym.s_name, gSysSym.s_thing);
}

// @ 0x00a49560
void pd_bang(t_gobj* x)
{
    t_class* c = *(t_class**)x;
    typedef void (*Fn)(void*);
    ((Fn)c->c_bangmethod)(x);
}

// @ 0x00a49570
void outlet_float(t_gobj* x, float f)
{
    void* c = *(void**)x;
    typedef void (*Fn)(void*, float);
    ((Fn)(*(void**)((char*)c + 0x2c)))(x, f);
}

// @ 0x00a49590
void pd_symbol(t_gobj* x, t_symbol s)
{
    void* c = *(void**)x;
    typedef void (*Fn)(void*, t_symbol);
    ((Fn)(*(void**)((char*)c + 0x30)))(x, s);
}

// @ 0x00a495b0
void pd_list(t_gobj* x, int a1, int a2, int n, void* argv)
{
    void* c = *(void**)x;
    typedef void (*Fn)(void*, void*, void*, int, void*);
    ((Fn)(*(void**)((char*)c + 0x34)))(x, gListSym2.s_name, gListSym2.s_thing, n, argv);
}

// @ 0x00a495e0
bool conf_init()
{
    bool ok = (mess_init() & 1) != 0;
    ok = ok & glob_init();
    ok = ok & glob_setup();
    ok = ok & s_loader_setup();
    ok = ok & s_list_setup();
    return ok;
}

// @ 0x00a49610
__declspec(noinline) void* getbytes(int n, const char* tag)
{
    if ((unsigned)n < 1u)
        n = 1;
    void* r = pdinstance()->alloc(n, tag);
    if (r)
        memfill(r, 0, n);
    return r;
}

// @ 0x00a49650
__declspec(noinline) void freebytes(void* p, int n)
{
    pdinstance()->freemem(p);
}

}}} // namespace EA::Audio::Eapd
