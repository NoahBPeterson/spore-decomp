// src/game/SPAudio/eapdio.cpp -- migrated from slice(s) s00a60ef0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdio.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
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
struct t_glist;                   // opaque canvas
}
namespace Eapd {
struct t_inlet;                   // opaque
}
namespace Eapd {
struct t_outlet;                  // opaque
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
t_class* gpInletClass;            // 0x0167582c
}
namespace Eapd {
t_class* gpOutletClass;           // 0x01675830
}
namespace Eapd {
t_symbol gEmptySymbol;            // 0x0167589c
}
namespace Eapd {
t_symbol* gensym(t_symbol* out, const char* s);                       // 0x00a675f0
}
namespace Eapd {
t_class*  class_new(t_symbol name, void* newmethod, void* freemethod,
                    int size, int a5, int a6, int a7);                // 0x00a48ea0
}
namespace Eapd {
byte      class_addbang(t_class* c, void* fn);                        // 0x00a47f10
}
namespace Eapd {
byte      class_doaddfloat(t_class* c, void* fn);                     // 0x00a47f30
}
namespace Eapd {
byte      class_addsymbol(t_class* c, void* fn);                      // 0x00a47f50
}
namespace Eapd {
byte      class_addlist(t_class* c, void* fn);                        // 0x00a47f70
}
namespace Eapd {
byte      class_addanything(t_class* c, void* fn);                    // 0x00a47f90
}
namespace Eapd {
bool      class_sethelpsymbol(t_class* c, t_symbol name);             // 0x00a47fc0
}
namespace Eapd {
void*     pd_new(t_class* c);                                         // 0x00a49390
}
namespace Eapd {
void*     inlet_new(void* owner, void* owner2, t_symbol s, t_symbol s2,
                    t_symbol s3, t_symbol s4);                        // 0x00a49740
}
namespace Eapd {
void*     canvas_getcurrent();                                        // 0x00a4a430
}
namespace Eapd {
t_outlet* canvas_addoutlet(t_glist* g, void* owner, t_symbol s);         // 0x00a4e0b0
}
namespace Eapd {
void      canvas_rminlet(t_glist* g, t_inlet* i);                     // 0x00a4d440
}
namespace Eapd {
void      canvas_rmoutlet(t_glist* g, t_outlet* o);                   // 0x00a4d610
}
namespace Eapd {
void      outlet_symbol(t_outlet* o, t_symbol s);                     // 0x00a49df0
}
namespace Eapd {
void      outlet_bang(t_outlet* o);                                   // 0x00a49da0
}
namespace Eapd {
void*     atom_vectorgensym(t_symbol* out, int argc, t_atom* argv);   // 0x00a46830
}
namespace Eapd {
void      inlet_setempty(t_inlet* i, t_symbol s);                     // 0x00a49720
}
namespace Eapd {
void      outlet_setempty(t_outlet* o, t_symbol s);                   // 0x00a49d10
}
namespace Eapd {
void* vinlet_new(int argc, t_atom* argv);                             // 0x00a613c0
}
namespace Eapd {
void* voutlet_new(int argc, t_atom* argv);                            // 0x00a61610
}
namespace Eapd {
void  vinlet_list(void* x, t_symbol s, int argc, t_atom* argv);       // 0x00a614b0
}
namespace Eapd {
void  vinlet_anything(void* x, t_symbol s, int argc, t_atom* argv);   // 0x00a614e0
}
namespace Eapd {
void  voutlet_list(void* x, t_symbol s, int argc, t_atom* argv);      // 0x00a61730
}
namespace Eapd {
void  voutlet_anything(void* x, t_symbol s, int argc, t_atom* argv);  // 0x00a61760
}
namespace Eapd {
void  inlet_bang_all(void* x);                                        // 0x00a59db0
}
namespace Eapd {
void  inlet_symbol(void* x, t_symbol s);                              // 0x00a5a140
}
// ---- items of slice s00a60ef0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace Eapd { void inlet_float_all(TX* x, float f); }  // 0x00a61460 (stays in the slice: not this object's)

// @ 0x00a61510
namespace Eapd {
void vinlet_free(TX* x)
{
    canvas_rminlet((t_glist*)*(void**)((char*)x + 0x28), (t_inlet*)*(void**)((char*)x + 0x2c));
}
}  // namespace Eapd

// @ 0x00a61530
namespace Eapd {
byte vinlet_setup(void)
{
    t_symbol s;
    t_symbol* p = gensym(&s, "inlet");
    gpInletClass = class_new(*p, (void*)vinlet_new, (void*)vinlet_free, 0x30, 8, 9, 0);
    byte ok = gpInletClass != 0;
    ok &= 1;
    ok &= class_addbang(gpInletClass, (void*)inlet_bang_all);
    ok &= class_doaddfloat(gpInletClass, (void*)inlet_float_all);
    ok &= class_addsymbol(gpInletClass, (void*)inlet_symbol);
    ok &= class_addlist(gpInletClass, (void*)vinlet_list);
    ok &= class_addanything(gpInletClass, (void*)vinlet_anything);
    p = gensym(&s, "helpsym");
    class_sethelpsymbol(gpInletClass, *p);
    return ok;
}
}  // namespace Eapd

// @ 0x00a61610
namespace Eapd {
void* voutlet_new(int argc, t_atom* argv)
{
    TX* x = (TX*)pd_new(gpOutletClass);
    if (x != 0) {
        void* cur = canvas_getcurrent();
        *(void**)((char*)x + 0x28) = cur;
        *(void**)((char*)x + 0x2c) = canvas_addoutlet((t_glist*)cur, x, gEmptySymbol);
        void* in = inlet_new(x, x, gEmptySymbol, gEmptySymbol, gEmptySymbol, gEmptySymbol);
        if (argc != 0) {
            t_symbol s;
            atom_vectorgensym(&s, argc, argv);
            inlet_setempty((t_inlet*)in, s);
            outlet_setempty((t_outlet*)*(void**)((char*)x + 0x2c), s);
        }
    }
    return x;
}
}  // namespace Eapd

// @ 0x00a616b0
namespace Eapd {
void voutlet_bang(TX* x)
{
    outlet_bang((t_outlet*)*(void**)((char*)x + 0x2c));
}
}  // namespace Eapd

// @ 0x00a61710
namespace Eapd {
void voutlet_symbol(TX* x, t_symbol s)
{
    outlet_symbol((t_outlet*)*(void**)((char*)x + 0x2c), s);
}
}  // namespace Eapd

// @ 0x00a61790
namespace Eapd {
void voutlet_free(TX* x)
{
    canvas_rmoutlet((t_glist*)*(void**)((char*)x + 0x28), (t_outlet*)*(void**)((char*)x + 0x2c));
}
}  // namespace Eapd

// @ 0x00a617c0
namespace Eapd {
byte voutlet_setup(void)
{
    t_symbol s;
    t_symbol* p = gensym(&s, "outlet");
    gpOutletClass = class_new(*p, (void*)voutlet_new, (void*)voutlet_free, 0x30, 8, 9, 0);
    byte ok = gpOutletClass != 0;
    ok &= 1;
    ok &= class_addbang(gpOutletClass, (void*)voutlet_bang);
    ok &= class_doaddfloat(gpOutletClass, (void*)inlet_float_all);
    ok &= class_addsymbol(gpOutletClass, (void*)voutlet_symbol);
    ok &= class_addlist(gpOutletClass, (void*)voutlet_list);
    ok &= class_addanything(gpOutletClass, (void*)voutlet_anything);
    p = gensym(&s, "helpsym");
    class_sethelpsymbol(gpOutletClass, *p);
    return ok;
}
}  // namespace Eapd

// @ 0x00a618a0
namespace Eapd {
byte g_io_setup(void)
{
    byte a = vinlet_setup();
    a &= 1;
    byte b = voutlet_setup();
    b &= a;
    return b;
}
}  // namespace Eapd
