// Slice s00a5fff0: EA::Audio::Eapd (EA's embedded Pure Data) - the pipe,
// function, bng and toggle object families (0xa5fff0-0xa60ee1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc)
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
typedef t_class* t_pd;

// t_symbol is passed by value (hash, name); symbols compare by their first word only.
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};

struct t_atom {
    int a_type;                 // +0
    union {
        float    w_float;       // +4
        t_symbol w_symbol;      // +4
    } a_w;
};

struct t_outlet;
struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_outlet*     oc_to;      // +4
};

struct t_outlet {             // 0x1c
    void*         o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol      o_symfrom;      // +0x0c
    t_symbol      o_symto;        // +0x14
};

struct IntrusiveList {        // 8
    IntrusiveList* mpNext;    // +0
    IntrusiveList* mpPrev;    // +4
    ~IntrusiveList();
};

// Function-node record hung off a function object.
struct FuncNode {
    FuncNode* mpNext;   // +0
    FuncNode* mpPrev;   // +4
    float     m8;       // +8
    float     mC;       // +0xc
};

// ---------------------------------------------------------------- globals
extern int       gOutletCount;             // 0x167545c
extern t_symbol  gFloatSymbol;             // 0x16758c4
extern t_symbol  gSymbolSymbol;            // 0x1675894
extern t_symbol  gBangSymbol;              // 0x16758b4
extern t_symbol  sGuiEmptySymbol;          // 0x167580c
extern t_class*  spPipeClass;              // 0x16757fc
extern t_class*  spFunctionClass;          // 0x1675804
extern t_class*  spToggleClass;            // 0x1675808
extern t_class*  spBngClass;               // 0x1675828

// --------------------------------------------------------------- callees
t_symbol* gensym(t_symbol* out, const char* s);                          // 0xa675f0
t_class*  class_new7(t_symbol name, void* newmethod, void* freemethod,
                     int size, int flags, int a1, int a2);               // 0xa48ea0
bool class_doaddfloat(t_class* c, void* fn);                             // 0xa47f30
bool class_addbang(t_class* c, void* fn);                                // 0xa47f10
bool class_addsymbol(t_class* c, void* fn);                              // 0xa47f50
bool class_addlist(t_class* c, void* fn);                                // 0xa47f70
bool class_addanything(t_class* c, void* fn);                            // 0xa47f90
bool class_addmethod1(t_class* c, void* fn, t_symbol name, int a1);      // 0xa48a30
bool class_addmethod2(t_class* c, void* fn, t_symbol name, int a1, int a2);  // 0xa48a80
bool class_addmethod3(t_class* c, void* fn, t_symbol name,
                      int a1, int a2, int a3);                           // 0xa48ad0
void class_setsavefn(t_class* c, void* fn);                              // 0xa48030

void* pd_new(t_class* c);                                                // 0xa49390
void  pd_free(void* p);                                                  // 0xa493d0
void* getbytes(int n, const char* tag);                                  // 0xa49610
void  freebytes(void* p, int n);                                         // 0xa49650

void* outlet_new(void* owner, t_symbol name);                            // 0xa49d30
void* floatinlet_new(void* owner, void* dest);                           // 0xa49a00
void* symbolinlet_new(void* owner, void* dest);                          // 0xa49ab0
void  outlet_bang(void* o);                                              // 0xa49da0
void  outlet_float(void* o, float f);                                    // 0xa49570
void  pd_send_bang(int hash, int name);                                  // 0xa67210
void  pd_send_float(int hash, int name, float f);                        // 0xa67230

void* canvas_getcurrent();                                               // 0xa4a430
void  gfxstub_deleteforkey(void* x);                                     // 0xa4c170

void*  clock_new(void* pd, void* fn);                                    // 0xa49080
void   clock_unset(void* c);                                             // 0xa490b0
void   clock_pause(void* c);                                             // 0xa49170
void   clock_unpause(void* c);                                           // 0xa491a0
bool   clock_ispaused(void* c);                                          // 0xa491d0
double clock_gettimesince(double t);                                     // 0xa49220
double clock_getlogicaltimeafter(float t);                               // 0xa49240
void   clock_free(void* c);                                              // 0xa49260
void   pipe_tick(void* x);                                               // 0xa5ff10
void   pipe_list(void* x);                                               // 0xa5fe20

void binbuf_addv(void* buf, const char* fmt, ...);                       // 0xa47220
void binbuf_addsemi(void* buf);                                          // 0xa47540

float    atom_getfloat_at(int idx, int argc, t_atom* argv);              // 0xa468f0
t_symbol* atom_getsymbol_at(t_symbol* out, int idx, int argc, t_atom* argv); // 0xa46950

bool delay_setup();                                                      // 0xa5f1e0
bool metro_setup();                                                      // 0xa5f540
bool line_setup();                                                       // 0xa5fae0
bool timer_setup();                                                      // 0xa5fd70

// ------------------------------------------------------------- pipe object
// @ 0x00a5fff0  EA::Audio::Eapd::pipe_flush
void pipe_flush(void* x)
{
    while (*(int*)((char*)x + 0x48) != 0)
        pipe_tick(x);
    clock_unset(*(void**)((char*)x + 0x50));
}

// @ 0x00a60020  EA::Audio::Eapd::pipe_clear
void pipe_clear(char* x)
{
    clock_unset(*(void**)(x + 0x50));
    while (*(void**)(x + 0x48) != 0) {
        char* e = *(char**)(x + 0x48);
        *(void**)(x + 0x48) = *(void**)e;
        *(void**)e = *(void**)(x + 0x4c);
        *(char**)(x + 0x4c) = e;
    }
}

// @ 0x00a60050  EA::Audio::Eapd::pipe_pause
void pipe_pause(char* x, float f)
{
    if (0.0f != f) {
        if (!clock_ispaused(*(void**)(x + 0x50))) {
            *(double*)(x + 0x38) = clock_gettimesince(*(double*)(x + 0x38));
            clock_pause(*(void**)(x + 0x50));
        }
        return;
    }
    if (clock_ispaused(*(void**)(x + 0x50))) {
        *(double*)(x + 0x38) = clock_getlogicaltimeafter(-(float)*(double*)(x + 0x38));
        clock_unpause(*(void**)(x + 0x50));
    }
}

// @ 0x00a600d0  EA::Audio::Eapd::pipe_free
void pipe_free(char* x)
{
    if (*(void**)(x + 0x40) != 0)
        freebytes(*(void**)(x + 0x40), *(int*)(x + 0x28) << 4);
    if (*(void**)(x + 0x44) != 0) {
        int k = *(int*)(x + 0x28);
        k--;
        int sz = k * 3;
        sz = sz * 4 + 0x14;
        freebytes(*(void**)(x + 0x44), sz * *(int*)(x + 0x2c));
    }
    if (*(void**)(x + 0x50) != 0)
        clock_free(*(void**)(x + 0x50));
}

// @ 0x00a60130  EA::Audio::Eapd::pipe_new
void* pipe_new(void* a, void* b, int argc, t_atom* argv)
{
    float v1 = 0.0f;
    int   n  = argc;
    int   m;

    if (n != 0 && argv[n - 1].a_type == 1) {
        v1 = argv[n - 1].a_w.w_float;
        n--;
    }
    if (n != 0 && argv[n - 1].a_type == 1) {
        m = (int)argv[n - 1].a_w.w_float;
        n--;
    } else {
        m = (int)(v1 * 0.1f);
    }
    if (m < 1)
        m = 100;

    t_atom local;
    if (n == 0) {
        argv = &local;
        n    = 1;
        local.a_type      = 1;
        local.a_w.w_float = 0.0f;
    }

    char*  pipe  = (char*)pd_new(spPipeClass);
    char*  out   = (char*)getbytes(n << 4, "EAPd/t_pipeout");
    int    recsz = n * 0xc + 8;
    char*  hang  = (char*)getbytes(recsz * m, "EAPd/t_hang");
    void*  clock = clock_new(pipe, (void*)pipe_tick);

    if (pipe == 0)
        return pipe;
    if (out == 0 || hang == 0 || clock == 0) {
        pd_free(pipe);
        return pipe;
    }

    *(int*)(pipe + 0x28)   = n;
    *(int*)(pipe + 0x2c)   = m;
    *(float*)(pipe + 0x30) = v1;
    *(char**)(pipe + 0x40) = out;
    *(char**)(pipe + 0x44) = hang;
    *(void**)(pipe + 0x48) = 0;
    *(char**)(pipe + 0x4c) = hang;
    *(void**)(pipe + 0x50) = clock;

    for (int i = 0; i < n; i++) {
        char*   rec = out + i * 0x10;
        t_atom* at  = argv + i;

        if (at->a_type == 2) {
            t_symbol  tmp;
            t_symbol* fs = gensym(&tmp, "f");
            if (at->a_w.w_symbol.mHash == fs->mHash) {
                at->a_type      = 1;
                at->a_w.w_float = 0.0f;
            } else {
                *(void**)(rec + 0xc) = outlet_new(pipe, gSymbolSymbol);
                if (i != 0)
                    symbolinlet_new(pipe, rec + 4);
            }
        }
        if (at->a_type == 1) {
            *(void**)(rec + 0xc) = outlet_new(pipe, gFloatSymbol);
            if (i != 0)
                floatinlet_new(pipe, rec + 4);
        }
        *(int*)(rec + 0) = at->a_type;
        *(int*)(rec + 4) = *(int*)((char*)at + 4);
        *(int*)(rec + 8) = *(int*)((char*)at + 8);
    }

    floatinlet_new(pipe, pipe + 0x30);

    char* p = *(char**)(pipe + 0x4c);
    char* e = (char*)((m - 1) * recsz + (int)p);
    while (p < e) {
        *(char**)p = p + recsz;
        p += recsz;
    }
    *(void**)e = 0;

    return pipe;
}

// @ 0x00a60390  EA::Audio::Eapd::pipe_setup
bool pipe_setup()
{
    t_symbol  s;
    t_symbol* sym;

    sym = gensym(&s, "pipe");
    spPipeClass = class_new7(*sym, (void*)pipe_new, (void*)pipe_free, 0x58, 0, 9, 0);
    bool ok = spPipeClass != 0;
    ok &= class_addlist(spPipeClass, (void*)pipe_list);
    sym = gensym(&s, "flush");
    ok &= class_addmethod1(spPipeClass, (void*)pipe_flush, *sym, 0);
    sym = gensym(&s, "clear");
    ok &= class_addmethod1(spPipeClass, (void*)pipe_clear, *sym, 0);
    sym = gensym(&s, "pause");
    ok &= class_addmethod2(spPipeClass, (void*)pipe_pause, *sym, 1, 0);
    return ok;
}

// @ 0x00a60470  EA::Audio::Eapd::x_time_setup
bool x_time_setup()
{
    bool ok = delay_setup() & 1;
    ok &= metro_setup();
    ok &= line_setup();
    ok &= timer_setup();
    ok = pipe_setup() & ok;
    return ok;
}

// --------------------------------------------------------- function object
// @ 0x00a604a0  EA::Audio::Eapd::function_inrange
void function_inrange(char* x, float a, float b)
{
    if (x == 0)
        return;
    if (a != b) {
        if (b < a) {
            float t = a;
            a = b;
            b = t;
        }
        *(float*)(x + 0x2c) = a;
        *(float*)(x + 0x30) = b - a;
    }
}

// @ 0x00a604e0  EA::Audio::Eapd::function_outrange
void function_outrange(char* x, float a, float b)
{
    if (x == 0)
        return;
    if (a != b) {
        if (b < a) {
            float t = a;
            a = b;
            b = t;
        }
        *(float*)(x + 0x34) = a;
        *(float*)(x + 0x38) = b - a;
    }
}

// @ 0x00a60520  EA::Audio::Eapd::function_save
void function_save(char* x, void* buf)
{
    if (x == 0 || *(void**)(x + 0x44) == 0)
        return;

    int i1 = *(short*)(x + 0x14);
    int i2 = *(short*)(x + 0x16);
    t_symbol s;
    t_symbol* s1 = gensym(&s, "function");
    t_symbol* s2 = gensym(&s, "obj");
    t_symbol* s3 = gensym(&s, "#X");

    binbuf_addv(buf, "ssiis", *s3, *s2, i1, i2, *s1);
    binbuf_addv(buf, "ii", *(int*)(x + 0x5c), *(int*)(x + 0x60));
    binbuf_addv(buf, "iii", *(int*)(x + 0x64), *(int*)(x + 0x68), *(int*)(x + 0x6c));
    binbuf_addv(buf, "ffff",
                (double)*(float*)(x + 0x2c), (double)*(float*)(x + 0x30),
                (double)*(float*)(x + 0x34), (double)*(float*)(x + 0x38));

    FuncNode* head = (FuncNode*)(x + 0x3c);
    for (FuncNode* p = head->mpNext; p != head; p = p->mpNext)
        binbuf_addv(buf, "ff", (double)p->m8, (double)p->mC);
    binbuf_addsemi(buf);
}

// @ 0x00a60650  EA::Audio::Eapd::function_float
void function_float(char* x, float f)
{
    if (x == 0 || *(void**)(x + 0x28) == 0)
        return;

    float t = (f - *(float*)(x + 0x2c)) / *(float*)(x + 0x30);
    float v = 0.0f;

    FuncNode* head = (FuncNode*)(x + 0x3c);
    FuncNode* p    = head->mpNext;
    if (p != head) {
        FuncNode* first = p;
        v = *(float*)(*(char**)(x + 0x40) + 0xc);
        do {
            if (t <= p->m8) {
                if (p == first || t == p->m8) {
                    v = p->mC;
                } else {
                    float a = *(float*)((char*)p->mpPrev + 8);
                    float b = *(float*)((char*)p->mpPrev + 0xc);
                    v = ((p->mC - b) * (t - a)) / (p->m8 - a) + b;
                }
                break;
            }
            p = p->mpNext;
        } while (p != head);
    }

    float out = *(float*)(x + 0x38) * v + *(float*)(x + 0x34);
    if (++gOutletCount < 1000) {
        t_outlet* o = *(t_outlet**)(x + 0x28);
        for (t_outconnect* oc = o->o_connections; oc != 0; oc = oc->oc_next)
            outlet_float(oc->oc_to, out);
    }
    gOutletCount--;
}

// @ 0x00a60740  EA::Audio::Eapd::function_new
void* function_new(void* a, void* b, int argc, t_atom* argv)
{
    char* x = (char*)pd_new(spFunctionClass);
    if (x == 0)
        return x;

    FuncNode* head = (FuncNode*)(x + 0x3c);
    if (head != 0) {
        head->mpPrev = head;
        head->mpNext = head;
    }
    *(void**)(x + 0x44) = canvas_getcurrent();
    *(void**)(x + 0x28) = outlet_new(x, gFloatSymbol);

    bool error = false;
    if (argc == 0) {
        *(float*)(x + 0x34) = 0.0f;
        *(float*)(x + 0x2c) = 0.0f;
        *(int*)(x + 0x5c)   = 0xc8;
        *(int*)(x + 0x60)   = 0x64;
        *(int*)(x + 0x6c)   = 0xff0;
        *(int*)(x + 0x68)   = 0;
        *(int*)(x + 0x64)   = 0xddd;
        *(float*)(x + 0x38) = 1.0f;
        *(float*)(x + 0x30) = 1.0f;
    } else if (argc < 9) {
        error = true;
    } else {
        for (int i = 0; i < 9; i++) {
            if (argv[i].a_type != 1)
                error = true;
        }
        if (!error) {
            *(int*)(x + 0x5c) = (int)argv[0].a_w.w_float;
            *(int*)(x + 0x60) = (int)argv[1].a_w.w_float;
            *(int*)(x + 0x64) = (int)argv[2].a_w.w_float;
            *(int*)(x + 0x68) = (int)argv[3].a_w.w_float;
            *(int*)(x + 0x6c) = (int)argv[4].a_w.w_float;
            *(float*)(x + 0x2c) = argv[5].a_w.w_float;
            *(float*)(x + 0x30) = argv[6].a_w.w_float;
            *(float*)(x + 0x34) = argv[7].a_w.w_float;
            *(float*)(x + 0x38) = argv[8].a_w.w_float;

            int n = argc - 10;
            if (n > 0) {
                t_atom* at = argv + 9;
                int k = 0;
                do {
                    if (at[0].a_type != 1 || at[1].a_type != 1) {
                        error = true;
                        break;
                    }
                    FuncNode* nd = (FuncNode*)getbytes(0x10, "EAPd/FunctionNode");
                    if (nd == 0) {
                        error = true;
                        break;
                    }
                    nd->mpNext = 0;
                    nd->mpPrev = 0;
                    nd->m8     = at[0].a_w.w_float;
                    nd->mC     = at[1].a_w.w_float;
                    nd->mpPrev = head->mpPrev;
                    nd->mpNext = head;
                    head->mpPrev->mpNext = nd;
                    head->mpPrev = nd;
                    at += 2;
                    k += 2;
                } while (k < n);
            }
        }
    }

    *(float*)(x + 0x54) = (float)(*(int*)(x + 0x5c) - 10);
    *(float*)(x + 0x58) = (float)(*(int*)(x + 0x60) - 10);
    if (error || *(void**)(x + 0x44) == 0 || *(void**)(x + 0x28) == 0) {
        pd_free(x);
        return 0;
    }
    return x;
}

// @ 0x00a60970  EA::Audio::Eapd::function_free
void function_free(char* x)
{
    if (x == 0)
        return;
    FuncNode* head = (FuncNode*)(x + 0x3c);
    FuncNode* p    = head->mpNext;
    while (p != head) {
        FuncNode* nx = p->mpNext;
        FuncNode* pv = p->mpPrev;
        nx->mpPrev = pv;
        pv->mpNext = nx;
        p->mpNext = 0;
        p->mpPrev = 0;
        freebytes(p, 0x10);
        p = nx;
    }
    gfxstub_deleteforkey(x);
    ((IntrusiveList*)head)->~IntrusiveList();
}

// @ 0x00a609d0  EA::Audio::Eapd::g_function_setup
bool g_function_setup()
{
    t_symbol  s;
    t_symbol* sym;

    sym = gensym(&s, "function");
    spFunctionClass = class_new7(*sym, (void*)function_new, (void*)function_free, 0x70, 0, 9, 0);
    bool ok = spFunctionClass != 0;
    ok &= class_doaddfloat(spFunctionClass, (void*)function_float);
    sym = gensym(&s, "inrange");
    ok &= class_addmethod3(spFunctionClass, (void*)function_inrange, *sym, 1, 1, 0);
    sym = gensym(&s, "outrange");
    ok &= class_addmethod3(spFunctionClass, (void*)function_outrange, *sym, 1, 1, 0);
    class_setsavefn(spFunctionClass, (void*)function_save);
    return ok;
}

// ------------------------------------------------------------ bng object
// @ 0x00a60aa0  EA::Audio::Eapd::bng_new
void* bng_new(void* a, void* b, int argc, t_atom* argv)
{
    char* x = (char*)pd_new(spBngClass);
    if (x == 0)
        return x;

    outlet_new(x, gBangSymbol);
    *(char*)(x + 0x28) = 0;
    *(t_symbol*)(x + 0x2c) = sGuiEmptySymbol;
    *(t_symbol*)(x + 0x34) = sGuiEmptySymbol;

    if (argc == 0xe) {
        t_symbol  tmp;
        *(bool*)(x + 0x28) = 0.0f != atom_getfloat_at(3, 0xe, argv);
        t_symbol* ts = atom_getsymbol_at(&tmp, 4, 0xe, argv);
        *(t_symbol*)(x + 0x2c) = *ts;
        ts = atom_getsymbol_at(&tmp, 5, 0xe, argv);
        *(t_symbol*)(x + 0x34) = *ts;
    }
    return x;
}

// @ 0x00a60b70  EA::Audio::Eapd::bng_any
void bng_any(char* x)
{
    outlet_bang(*(void**)(x + 0xc));
    if (*(int*)(x + 0x2c) != sGuiEmptySymbol.mHash
        && *(int*)(x + 0x2c) != *(int*)(x + 0x34))
        pd_send_bang(*(int*)(x + 0x2c), *(int*)(x + 0x30));
}

// @ 0x00a60bb0  EA::Audio::Eapd::bng_loadbang
void bng_loadbang(char* x)
{
    if (*(char*)(x + 0x28) == 0)
        return;
    outlet_bang(*(void**)(x + 0xc));
    if (*(int*)(x + 0x2c) != sGuiEmptySymbol.mHash
        && *(int*)(x + 0x2c) != *(int*)(x + 0x34))
        pd_send_bang(*(int*)(x + 0x2c), *(int*)(x + 0x30));
}

// @ 0x00a60bf0  EA::Audio::Eapd::g_bng_setup
bool g_bng_setup()
{
    t_symbol  s;
    t_symbol* sym;

    sym = gensym(&s, "empty");
    sGuiEmptySymbol = *sym;
    sym = gensym(&s, "bng");
    spBngClass = class_new7(*sym, (void*)bng_new, 0, 0x3c, 0, 9, 0);
    bool ok = spBngClass != 0;
    ok &= class_addbang(spBngClass, (void*)bng_any);
    ok &= class_doaddfloat(spBngClass, (void*)bng_any);
    ok &= class_addsymbol(spBngClass, (void*)bng_any);
    ok &= class_addlist(spBngClass, (void*)bng_any);
    ok &= class_addanything(spBngClass, (void*)bng_any);
    sym = gensym(&s, "loadbang");
    ok &= class_addmethod1(spBngClass, (void*)bng_loadbang, *sym, 0);
    return ok;
}

// --------------------------------------------------------- toggle object
// @ 0x00a60ce0  EA::Audio::Eapd::toggle_new
void* toggle_new(void* a, void* b, int argc, t_atom* argv)
{
    char* x = (char*)pd_new(spToggleClass);
    if (x == 0)
        return x;

    outlet_new(x, gFloatSymbol);
    *(char*)(x + 0x28) = 0;
    *(t_symbol*)(x + 0x2c) = sGuiEmptySymbol;
    *(t_symbol*)(x + 0x34) = sGuiEmptySymbol;
    *(char*)(x + 0x3c)  = 0;
    *(float*)(x + 0x40) = 1.0f;

    if (argc == 0xe) {
        t_symbol  tmp;
        *(bool*)(x + 0x28) = 0.0f != atom_getfloat_at(1, 0xe, argv);
        t_symbol* ts = atom_getsymbol_at(&tmp, 2, 0xe, argv);
        *(t_symbol*)(x + 0x2c) = *ts;
        ts = atom_getsymbol_at(&tmp, 3, 0xe, argv);
        *(t_symbol*)(x + 0x34) = *ts;
        *(bool*)(x + 0x3c) = 0.0f != atom_getfloat_at(0xc, 0xe, argv);
        *(float*)(x + 0x40) = atom_getfloat_at(0xd, 0xe, argv);
    }
    return x;
}

// @ 0x00a60df0  EA::Audio::Eapd::toggle_output
void toggle_output(char* x)
{
    float v = *(char*)(x + 0x3c) ? *(float*)(x + 0x40) : 0.0f;

    if (++gOutletCount < 1000) {
        t_outlet* o = *(t_outlet**)(x + 0xc);
        for (t_outconnect* oc = o->o_connections; oc != 0; oc = oc->oc_next)
            outlet_float(oc->oc_to, v);
    }
    gOutletCount--;

    int sym = *(int*)(x + 0x2c);
    if (sym != sGuiEmptySymbol.mHash && sym != *(int*)(x + 0x34))
        pd_send_float(sym, *(int*)(x + 0x30), v);
}

// @ 0x00a60e70  EA::Audio::Eapd::toggle_bang
void toggle_bang(char* x)
{
    *(char*)(x + 0x3c) = *(char*)(x + 0x3c) == 0;
    toggle_output(x);
}

// @ 0x00a60e90  EA::Audio::Eapd::toggle_float
void toggle_float(char* x, float f)
{
    if (0.0f != f) {
        *(char*)(x + 0x3c)  = 1;
        *(float*)(x + 0x40) = f;
        toggle_output(x);
    } else {
        *(char*)(x + 0x3c) = 0;
        toggle_output(x);
    }
}

// @ 0x00a60ed0  EA::Audio::Eapd::toggle_loadbang
void toggle_loadbang(char* x)
{
    if (*(char*)(x + 0x28) != 0)
        toggle_output(x);
}

} } }  // namespace EA::Audio::Eapd
