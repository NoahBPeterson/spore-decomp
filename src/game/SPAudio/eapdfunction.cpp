// src/game/SPAudio/eapdfunction.cpp -- migrated from slice(s) s00a5fff0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdfunction.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a5fff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_atom {
    int a_type;                 // +0
    union {
        float    w_float;       // +4
        t_symbol w_symbol;      // +4
    } a_w;
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_outlet*     oc_to;      // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet {             // 0x1c
    void*         o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol      o_symfrom;      // +0x0c
    t_symbol      o_symto;        // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct IntrusiveList {        // 8
    IntrusiveList* mpNext;    // +0
    IntrusiveList* mpPrev;    // +4
    ~IntrusiveList();
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct FuncNode {
    FuncNode* mpNext;   // +0
    FuncNode* mpPrev;   // +4
    float     m8;       // +8
    float     mC;       // +0xc
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern int       gOutletCount;             // 0x167545c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol  gFloatSymbol;             // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class*  spFunctionClass;          // 0x1675804
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* s);                          // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new7(t_symbol name, void* newmethod, void* freemethod,
                     int size, int flags, int a1, int a2);               // 0xa48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_doaddfloat(t_class* c, void* fn);                             // 0xa47f30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addmethod3(t_class* c, void* fn, t_symbol name,
                      int a1, int a2, int a3);                           // 0xa48ad0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void class_setsavefn(t_class* c, void* fn);                              // 0xa48030
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_new(t_class* c);                                                // 0xa49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_free(void* p);                                                  // 0xa493d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                                  // 0xa49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  freebytes(void* p, int n);                                         // 0xa49650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* owner, t_symbol name);                            // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_float(void* o, float f);                                    // 0xa49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* canvas_getcurrent();                                               // 0xa4a430
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  gfxstub_deleteforkey(void* x);                                     // 0xa4c170
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void binbuf_addv(void* buf, const char* fmt, ...);                       // 0xa47220
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void binbuf_addsemi(void* buf);                                          // 0xa47540
}
}
}
// ---- items of slice s00a5fff0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Audio { namespace Eapd { void function_inrange(char* x, float a, float b); }}}  // 0x00a604a0 (stays in the slice: not this object's)
namespace EA { namespace Audio { namespace Eapd { void function_outrange(char* x, float a, float b); }}}  // 0x00a604e0 (stays in the slice: not this object's)

// @ 0x00a60520
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60650
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60740
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a60970
namespace EA { namespace Audio { namespace Eapd {
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
}}}  // namespace EA::Audio::Eapd

// @ 0x00a609d0
namespace EA {
namespace Audio {
namespace Eapd {
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
}
}
}  // namespace EA::Audio::Eapd
