// src/game/SPAudio/eapdconnective.cpp -- migrated from slice(s) s00a5c460, s00a5b510, s00a5a590, s00a59690 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdconnective.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <malloc.h>

// ---- items of slice s00a59690 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uintptr_t;
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol { void* s_name; void* s_name2; };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* gensym(t_symbol* buf, const char* name);                                  // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* class_new(void* s_name, void* s_name2, void* nnew,
                void* a, int size, int b, int nargs, int c);                        // 0x00a48ea0 / 0x00a48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* class_addcreator(void* fn, void* s_name, void* s_name2, int nargs, int c);    // 0x00a48db0 / 0x00a48e00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   class_addbang(void* c, void* fn);                                             // 0x00a47f10
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   class_doaddfloat(void* c, void* fn);                                          // 0x00a47f30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   class_addsymbol(void* c, void* fn);                                           // 0x00a47f50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   class_addlist(void* c, void* fn);                                             // 0x00a47f70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   class_addanything(void* c, void* fn);                                         // 0x00a47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_new(void* cls);                                                            // 0x00a49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_free(void* obj);                                                           // 0x00a493d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                                             // 0x00a49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool  pd_bind(void* obj, void* a, void* b);                                         // 0x00a67620
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* obj, void* a, void* b);                                      // 0x00a49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_bang(void* out);                                                       // 0x00a49da0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_float(void* out, float f);                                             // 0x00a49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_symbol(void* out, void* a, void* b);                                   // 0x00a49df0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* floatinlet_new(void* obj, void* p);                                           // 0x00a49a00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* symbolinlet_new(void* obj, void* p);                                          // 0x00a49ab0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_send_bang(uint32_t a, uint32_t b);                                         // 0x00a67210
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_send_symbol(uint32_t a, uint32_t b, uint32_t c, uint32_t d);               // 0x00a67250
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_send_float(uint32_t a, uint32_t b, float f);                               // 0x00a67230
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_typedmess_bindings(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t); // 0x00a672b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pd_list_bindings(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t); // 0x00a67280
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
float atom_getfloat_at(int a, int b, void* atoms);                                  // 0x00a468f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol* atom_getsymbol_at(t_symbol* out, int a, int b, void* atoms);              // 0x00a46950
}
}
}
using EA::Audio::Eapd::t_symbol;
#define g_spPdintClass    (*(void**)0x0167562cu)
#define g_spPdfloatClass  (*(void**)0x01675678u)
#define g_spPdsymbolClass (*(void**)0x01675640u)
#define g_spBangClass     (*(void**)0x01675664u)
#define g_spSendClass     (*(void**)0x01675654u)
#define g_spForwardClass  (*(void**)0x01675630u)
#define g_spReceiveClass  (*(void**)0x01675648u)
#define g_spSelectClass   (*(void**)0x0167565cu)
#define g_spSelect2Class  (*(void**)0x01675660u)
#define g_gFloatSymbol    (*(t_symbol*)0x016758c4u)
#define g_gSymbolSymbol   (*(t_symbol*)0x01675894u)
#define g_gBangSymbol     (*(t_symbol*)0x016758b4u)
#define g_gEmptySymbol    (*(t_symbol*)0x0167589cu)
#define g_gFloatSymbol2   (*(void**)0x016758c8u)
#define g_gSymbolSymbol2  (*(void**)0x01675898u)
#define g_gBangSymbol2    (*(void**)0x016758b8u)
#define g_gEmptySymbol2   (*(void**)0x016758a0u)
#define g_gpNewestObject  (*(void**)0x016753f4u)
#define g_gOutletCount    (*(int*)0x0167545cu)
struct PdObject
{
    uint32_t pad_00[3];     // +0x00
    void*    pOb;           // +0x0c  (points at a struct whose +0x08 is the outlet list head)
    uint32_t pad_10[6];     // +0x10
    uint32_t mAt28;         // +0x28
    uint32_t mAt2c;         // +0x2c
};
struct SelectElement
{
    float    fKey;          // +0x00
    uint32_t symName2;      // +0x04
    void*    mOutlet;       // +0x08
};
struct PdPayload
{
    uint32_t at28;          // +0x00 (object +0x28)
    uint32_t at2c;          // +0x04 (object +0x2c)
};
void* FUN_00a598f0(float f);
void  FUN_00a59940(PdObject* o);
void  FUN_00a599a0(PdObject* o, float v);
void* pdfloat_new(float f, ...);
void* pdfloat_new2(float f);
void  FUN_00a59b50(PdObject* o, float v);
void* pdsymbol_new(uint32_t a, uint32_t b, uint32_t c);
void  pdsymbol_symbol(PdObject* o);
void  pdsymbol_anything(PdObject* o, void* a, void* b);
void* bang_new2();
void  FUN_00a59db0(void* o);
void  FUN_00a59e90(PdObject* o);
void  send_symbol(PdObject* o, void* a, void* b);
void  FUN_00a59ed0(PdObject* o, void* a, void* b, void* c, void* d);
void* FUN_00a59f00(uint32_t a, uint32_t b);
void  FUN_00a5a000(PdObject* o, float f);
void  FUN_00a5a020(PdObject* o, void* a, void* b, void* c, void* d);
void* forward_new(uint32_t a, uint32_t b);
void  FUN_00a5a140(PdObject* o, void* a, void* b);
void* receive_new(uint32_t a, uint32_t b);
void* FUN_00a598f0(float f);
void FUN_00a59940(PdObject* o);
void FUN_00a599a0(PdObject* o, float v);
void* pdfloat_new(float f, ...);
void* pdfloat_new2(float f);
void FUN_00a59b50(PdObject* o, float v);
void* pdsymbol_new(uint32_t a, uint32_t b, uint32_t c);
void pdsymbol_symbol(PdObject* o);
void pdsymbol_anything(PdObject* o, void* a, void* b);
void* bang_new2();
void FUN_00a59db0(void* o);
void FUN_00a59e90(PdObject* o);
void send_symbol(PdObject* o, void* a, void* b);
void FUN_00a59ed0(PdObject* o, void* a, void* b, void* c, void* d);
void* FUN_00a59f00(uint32_t a, uint32_t b);
bool send_setup();
void FUN_00a5a000(PdObject* o, float f);
void FUN_00a5a020(PdObject* o, void* a, void* b, void* c, void* d);
void* forward_new(uint32_t a, uint32_t b);
bool forward_setup();
void FUN_00a5a140(PdObject* o, void* a, void* b);
void* receive_new(uint32_t a, uint32_t b);
bool receive_setup();
void FUN_00a5a280(PdObject* o, float v);
void sel1_symbol(PdObject* o, int sym, void* b);
void sel2_float(PdObject* o, float v);
void sel2_symbol(PdObject* o, int sym, void* b);
void* select_new(int argc, void* argv, int mode, int* atoms);
// ---- items of slice s00a59690 end

// ---- items of slice s00a5a590 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_a590 {               // 0x08, passed by value in the message API
    const char* name;           // +0x00
    int hash;                   // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Atom {                   // 0x0c
    int type;                   // +0x00
    union {
        float f;                // +0x04
        int i;
        t_symbol_s00a5_a590 sym;           // +0x04
    };
};
}
}
}
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
struct Dest {                   // 0x08
    Dest* next;                 // +0x00
    void* outlet;               // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Outlet {                 // 0x0c
    char pad[8];
    Dest* dests;                // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RouteElement {           // 0x0c
    union {
        float key;              // +0x00
        t_symbol_s00a5_a590 sym;           // +0x00
    };
    void* outlet;               // +0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct OutElem {                // 0x08
    int type;                   // +0x00
    void* outlet;               // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct RouteObj {               // 0x38
    char pad0[0x28];
    int mode;                   // +0x28  (type of the first argument: 1 = float keys)
    int count;                  // +0x2c
    RouteElement* elems;        // +0x30
    void* outlet;               // +0x34
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PackObj {                // 0x34
    char pad0[0x0c];
    void* outlet;               // +0x0c
    char pad1[0x18];
    int count;                  // +0x28
    Atom* atoms;                // +0x2c
    Atom* atoms2;               // +0x30
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct UnpackObj {              // 0x30
    char pad0[0x28];
    int count;                  // +0x28
    OutElem* outs;              // +0x2c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct TriggerObj {             // 0x30
    char pad0[0x28];
    int count;                  // +0x28
    OutElem* outs;              // +0x2c
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_a590 gListSymbol;        // 0x016758ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_a590 gBangSymbol;        // 0x016758b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_a590 gSymbolSymbol;      // 0x01675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_a590 gEmptySymbol;       // 0x0167589c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_a590 gFloatSymbol;       // 0x016758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_a590 gAnythingSymbol;    // 0x016758cc
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern int gOutletCount;            // 0x0167545c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gSelectClass;       // 0x0167565c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gSelect2Class;      // 0x01675660
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spRouteClass;       // 0x01675668
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gPackClass;         // 0x0167566c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spUnpackClass;      // 0x0167563c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spTriggerClass;     // 0x01675638
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol_s00a5_a590* __cdecl gensym(t_symbol_s00a5_a590* buf, const char* name);              // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class* __cdecl class_new(t_symbol_s00a5_a590 name, void* newfn, void* freefn, int size, int flags,
                           int type);                                   // 0x00a48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class* __cdecl class_new(t_symbol_s00a5_a590 name, void* newfn, void* freefn, int size, int flags,
                           int type, int arg);                          // 0x00a48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
byte __cdecl class_addcreator(void* fn, t_symbol_s00a5_a590 name, int type, int arg);  // 0x00a48e00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
byte __cdecl class_addbang(t_class* c, void* fn);                       // 0x00a47f10
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
byte __cdecl class_doaddfloat(t_class* c, void* fn);                    // 0x00a47f30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
byte __cdecl class_addsymbol(t_class* c, void* fn);                     // 0x00a47f50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
byte __cdecl class_addlist(t_class* c, void* fn);                       // 0x00a47f70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
byte __cdecl class_addanything(t_class* c, void* fn);                   // 0x00a47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl pd_new(t_class* c);                                       // 0x00a49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl outlet_new(void* obj, t_symbol_s00a5_a590 s);                        // 0x00a49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void __cdecl outlet_symbol(void* outlet, t_symbol_s00a5_a590 s);                   // 0x00a49df0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void __cdecl outlet_list(void* outlet, t_symbol_s00a5_a590 s, int argc, Atom* argv);   // 0x00a49e40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void __cdecl outlet_anything(void* outlet, t_symbol_s00a5_a590 s, int argc, Atom* argv);  // 0x00a49eb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void __cdecl obj_list(void* obj, t_symbol_s00a5_a590 s, int argc, Atom* argv);     // 0x00a49b40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void __cdecl freebytes(void* p, int size);                              // 0x00a49650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
float __cdecl atom_getfloat(Atom* a);                                   // 0x00a46760
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol_s00a5_a590* __cdecl atom_getsymbol(t_symbol_s00a5_a590* buf, Atom* a);               // 0x00a46790
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
float __cdecl atom_getfloat_at(int i, int argc, Atom* argv);            // 0x00a468f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol_s00a5_a590* __cdecl atom_getsymbol_at(t_symbol_s00a5_a590* buf, int i, int argc, Atom* argv);  // 0x00a46950
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void route_free(RouteObj* obj);     // 0x00a5a960
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void sel1_float();                  // 0x00a5a280
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void sel1_symbol();                 // 0x00a5a2f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void sel2_float();                  // 0x00a5a330
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void sel2_symbol();                 // 0x00a5a3c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* select_new(t_symbol_s00a5_a590* s, int argc, Atom* argv);                    // 0x00a5a410
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void route_anything(RouteObj* obj, t_symbol_s00a5_a590 s, int argc, Atom* argv);   // 0x00a5a690
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* unpack_new(t_symbol_s00a5_a590* s, int argc, Atom* argv);                    // 0x00a5aeb0
}
}
}
// ---- items of slice s00a5a590 end

// ---- items of slice s00a5b510 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_b510 {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_object;
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
    t_object*     o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol_s00a5_b510      o_symfrom;      // +0x0c
    t_symbol_s00a5_b510      o_symto;        // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_b510 gEmptySymbol_s00a5_b510;               // 0x167589c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_b510 gFloatSymbol_s00a5_b510;               // 0x16758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_b510 gSymbolSymbol_s00a5_b510;              // 0x1675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_b510 gListSymbol_s00a5_b510;                // 0x16758ac
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_b510 gListSender;                // 0x16758b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spSpigotClass;              // 0x1675670
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spGateClass;                // 0x167567c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spSwitchClass;              // 0x1675658
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spMosesClass;               // 0x167564c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spUntilClass;               // 0x1675644
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spMakefilenameClass;        // 0x1675628
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spSwapClass;                // 0x1675674
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spChangeClass;              // 0x1675650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol_s00a5_b510* gensym(t_symbol_s00a5_b510* out, const char* s);                          // 0xa675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new_t1(t_symbol_s00a5_b510 name, void* newmethod, void* freemethod,
                       int size, int flags, int a1);                     // 0xa48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new_t2(t_symbol_s00a5_b510 name, void* newmethod, void* freemethod,
                       int size, int flags, int a1, int a2);             // 0xa48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new_t3(t_symbol_s00a5_b510 name, void* newmethod, void* freemethod,
                       int size, int flags, int a1, int a2, int a3);     // 0xa48f00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addcreator(void* newmethod, t_symbol_s00a5_b510 name, int a1, int a2);   // 0xa48e00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addsymbol_s00a5_b510(t_class* c, void* fn);                              // 0xa47f50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addlist_s00a5_b510(t_class* c, void* fn);                                // 0xa47f70
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addanything_s00a5_b510(t_class* c, void* fn);                            // 0xa47f90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addmethod1(t_class* c, void* fn, t_symbol_s00a5_b510 name, int a1);      // 0xa48a30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool class_addmethod2(t_class* c, void* fn, t_symbol_s00a5_b510 name, int a1, int a2);  // 0xa48a80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_float(char* to, float f);                                   // 0xa49570
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_bang(char* to);                                             // 0xa49da0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_symbol(char* to, t_symbol_s00a5_b510 s);                               // 0xa49df0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  trigger_list(char* x, unsigned int s, unsigned int a, int argc, void* argv); // 0xa5b330int   espd_sprintf(char*, const char*, ...);                             // msvcr90!sprintf
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_list(char* to, t_symbol_s00a5_b510 s, int argc, void* argv);           // 0xa49e40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  outlet_anything(char* to, t_symbol_s00a5_b510 s, int argc, void* argv);       // 0xa49eb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* owner, t_symbol_s00a5_b510 a, t_symbol_s00a5_b510 b);                   // 0xa49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* inlet_new(void* owner, void* dest, t_symbol_s00a5_b510 a, t_symbol_s00a5_b510 b,
                t_symbol_s00a5_b510 c, t_symbol_s00a5_b510 d);                                 // 0xa49740
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   espd_sprintf(char*, const char*, ...);                             // msvcr90!sprintf
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline float  objF(char* x, int off)  { return *(float*)(x + off); }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline void   setObjF(char* x, int off, float v) { *(float*)(x + off) = v; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline int    objI(char* x, int off)  { return *(int*)(x + off); }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline void   setObjI(char* x, int off, int v) { *(int*)(x + off) = v; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline void*  objP(char* x, int off)  { return *(void**)(x + off); }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline void   setObjP(char* x, int off, void* v) { *(void**)(x + off) = v; }
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
inline void outlet_cnt(t_outlet* lst, float v)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = lst->o_connections; oc; oc = oc->oc_next)
            outlet_float((char*)oc->oc_to, v);
    }
    gOutletCount--;
}
}
}
}
// ---- items of slice s00a5b510 end

// ---- items of slice s00a5c460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int gOutletCount;                                              // 0x0167545c
namespace EA {
namespace Audio {
namespace Eapd {
struct t_symbol_s00a5_c460 {
    int a;                              // 0x00
    int b;                              // 0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outlet_s00a5_c460 {                       // element of an outlet list
    t_outlet_s00a5_c460* next;                     // 0x00
    void* target;                       // 0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_outletlist {
    int pad0;                           // 0x00
    int pad1;                           // 0x04
    t_outlet_s00a5_c460* first;                    // 0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_change {
    int pad00;                          // 0x00
    int pad04;                          // 0x04
    int pad08;                          // 0x08
    t_outletlist* outlets;              // 0x0c
    int pad10[6];                       // 0x10
    float value;                        // 0x28
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_vcommon {
    int pad0;                           // 0x00
    int refs;                           // 0x04
    float value;                        // 0x08
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_value {
    int pad00;                          // 0x00
    int pad04;                          // 0x04
    int pad08;                          // 0x08
    t_outletlist* outlets;              // 0x0c
    int pad10[6];                       // 0x10
    t_symbol_s00a5_c460 key;                       // 0x28
    float* value;                       // 0x30
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_symbol_s00a5_c460* gensym(t_symbol_s00a5_c460* out, const char* name);                    // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class* class_new(t_symbol_s00a5_c460 name, void* newfn, void* freefn, int size,
                   int flags, int nargs, int arg);                     // 0x00a48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class* class_new(t_symbol_s00a5_c460 name, void* newfn, void* freefn, int size,
                   int flags, int nargs);                              // 0x00a48e50
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
byte class_addcreator(void* fn, t_symbol_s00a5_c460 sel, int nargs, int arg);     // 0x00a48e00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* pd_findbyclass(int a, int b, t_class* cls);                      // 0x00a671f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool pd_bind(void* obj, t_symbol_s00a5_c460 key);                                // 0x00a67620
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* outlet_new(void* obj, t_symbol_s00a5_c460 sel);                            // 0x00a49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void sys_vgui(void* a, int b, int c);                                 // 0x00a671b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spValueClass;                                         // 0x01675634
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* spVcommonClass;                                       // 0x01675680
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_symbol_s00a5_c460 gFloatSymbol_s00a5_c460;                                         // 0x016758c4
}
}
}
// ---- items of slice s00a5c460 end

// @ 0x00a59a10
namespace EA {
namespace Audio {
namespace Eapd {
bool pdint_setup()
{
    t_symbol sym;

    t_symbol* sp = EA::Audio::Eapd::gensym(&sym, "int");
    g_spPdintClass = EA::Audio::Eapd::class_new(sp->s_name, sp->s_name2, (void*)&FUN_00a598f0,
                                                0, 0x2c, 0, 5, 0);
    bool ok = (g_spPdintClass != 0);

    sp = EA::Audio::Eapd::gensym(&sym, "int");
    ok &= (EA::Audio::Eapd::class_addcreator((void*)&FUN_00a598f0, sp->s_name, sp->s_name2, 5, 0) != 0);

    ok &= (EA::Audio::Eapd::class_addbang(g_spPdintClass, (void*)&FUN_00a59940) != 0);
    ok &= (EA::Audio::Eapd::class_doaddfloat(g_spPdintClass, (void*)&FUN_00a599a0) != 0);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a59ab0
void* pdfloat_new(float f, ...)
{
    void* o = EA::Audio::Eapd::pd_new(g_spPdfloatClass);
    if (o != 0)
    {
        *(float*)((char*)o + 0x28) = f;
        EA::Audio::Eapd::outlet_new(o, g_gFloatSymbol.s_name, g_gFloatSymbol2);
        EA::Audio::Eapd::floatinlet_new(o, (char*)o + 0x28);
        g_gpNewestObject = o;
    }
    return o;
}

// @ 0x00a59b00
void* pdfloat_new2(float f)
{
    void* o = EA::Audio::Eapd::pd_new(g_spPdfloatClass);
    if (o != 0)
    {
        *(float*)((char*)o + 0x28) = f;
        EA::Audio::Eapd::outlet_new(o, g_gFloatSymbol.s_name, g_gFloatSymbol2);
        EA::Audio::Eapd::floatinlet_new(o, (char*)o + 0x28);
        g_gpNewestObject = o;
    }
    return o;
}

// @ 0x00a59b50
void FUN_00a59b50(PdObject* o, float v)
{
    o->mAt28 = *(uint32_t*)&v;
    if (g_gOutletCount + 1 >= 1000)
        return;
    ++g_gOutletCount;
    for (void* p = *(void**)((char*)o->pOb + 8); p != 0; p = *(void**)p)
        EA::Audio::Eapd::outlet_float(*(void**)((char*)p + 4), v);
    --g_gOutletCount;
}

// @ 0x00a59bb0
namespace EA {
namespace Audio {
namespace Eapd {
bool pdfloat_setup()
{
    t_symbol sym;

    t_symbol* sp = EA::Audio::Eapd::gensym(&sym, "float");
    g_spPdfloatClass = EA::Audio::Eapd::class_new(sp->s_name, sp->s_name2, (void*)&pdfloat_new,
                                                  0, 0x2c, 0, 1, 0);
    bool ok = (g_spPdfloatClass != 0);

    sp = EA::Audio::Eapd::gensym(&sym, "float");
    ok &= (EA::Audio::Eapd::class_addcreator((void*)&pdfloat_new2, sp->s_name, sp->s_name2, 5, 0) != 0);

    ok &= (EA::Audio::Eapd::class_addbang(g_spPdfloatClass, (void*)0x00a5c400) != 0);
    ok &= (EA::Audio::Eapd::class_doaddfloat(g_spPdfloatClass, (void*)&FUN_00a59b50) != 0);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a59c50
void* pdsymbol_new(uint32_t a, uint32_t b, uint32_t c)
{
    void* o = EA::Audio::Eapd::pd_new(g_spPdsymbolClass);
    if (o != 0)
    {
        PdPayload* p = (PdPayload*)((char*)o + 0x28);
        p->at28 = b;
        p->at2c = c;
        EA::Audio::Eapd::outlet_new(o, g_gSymbolSymbol.s_name, g_gSymbolSymbol2);
        EA::Audio::Eapd::symbolinlet_new(o, (char*)o + 0x28);
        g_gpNewestObject = o;
    }
    return o;
}

// @ 0x00a59ca0
void pdsymbol_symbol(PdObject* o)
{
    EA::Audio::Eapd::outlet_symbol(o->pOb, (void*)(uintptr_t)o->mAt28, (void*)(uintptr_t)o->mAt2c);
}

// @ 0x00a59cc0
void pdsymbol_anything(PdObject* o, void* a, void* b)
{
    PdPayload* p = (PdPayload*)((char*)o + 0x28);
    p->at28 = (uint32_t)(uintptr_t)a;
    p->at2c = (uint32_t)(uintptr_t)b;
    EA::Audio::Eapd::outlet_symbol(o->pOb, a, b);
}

// @ 0x00a59cf0
namespace EA {
namespace Audio {
namespace Eapd {
bool pdsymbol_setup()
{
    t_symbol sym;

    t_symbol* sp = EA::Audio::Eapd::gensym(&sym, "symbol");
    g_spPdsymbolClass = EA::Audio::Eapd::class_new(sp->s_name, sp->s_name2, (void*)&pdsymbol_new,
                                                   0, 0x30, 0, 2, 0);
    bool ok = (g_spPdsymbolClass != 0);

    ok &= (EA::Audio::Eapd::class_addbang(g_spPdsymbolClass, (void*)&pdsymbol_symbol) != 0);
    ok &= (EA::Audio::Eapd::class_addsymbol(g_spPdsymbolClass, (void*)&pdsymbol_anything) != 0);
    ok &= (EA::Audio::Eapd::class_addanything(g_spPdsymbolClass, (void*)&pdsymbol_anything) != 0);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a59d70
void* bang_new2()
{
    void* o = EA::Audio::Eapd::pd_new(g_spBangClass);
    if (o != 0)
    {
        EA::Audio::Eapd::outlet_new(o, g_gBangSymbol.s_name, g_gBangSymbol2);
        g_gpNewestObject = o;
    }
    return o;
}

// @ 0x00a59db0
void FUN_00a59db0(void* o)
{
    EA::Audio::Eapd::outlet_bang(*(void**)((char*)o + 0x0c));
}

// @ 0x00a59dc0
namespace EA {
namespace Audio {
namespace Eapd {
bool bang_setup()
{
    t_symbol sym;

    t_symbol* sp = EA::Audio::Eapd::gensym(&sym, "bang");
    g_spBangClass = EA::Audio::Eapd::class_new(sp->s_name, sp->s_name2, (void*)&bang_new2,
                                               0, 0x28, 0, 0, 0);
    bool ok = (g_spBangClass != 0);

    sp = EA::Audio::Eapd::gensym(&sym, "bang");
    ok &= (EA::Audio::Eapd::class_addcreator((void*)&bang_new2, sp->s_name, sp->s_name2, 0, 0) != 0);

    ok &= (EA::Audio::Eapd::class_addbang(g_spBangClass, (void*)&FUN_00a59db0) != 0);
    ok &= (EA::Audio::Eapd::class_doaddfloat(g_spBangClass, (void*)&FUN_00a59db0) != 0);
    ok &= (EA::Audio::Eapd::class_addsymbol(g_spBangClass, (void*)&FUN_00a59db0) != 0);
    ok &= (EA::Audio::Eapd::class_addlist(g_spBangClass, (void*)&FUN_00a59db0) != 0);
    ok &= (EA::Audio::Eapd::class_addanything(g_spBangClass, (void*)&FUN_00a59db0) != 0);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a59e90
void FUN_00a59e90(PdObject* o)
{
    EA::Audio::Eapd::pd_send_bang((uint32_t)(uintptr_t)o->mAt28, (uint32_t)(uintptr_t)o->mAt2c);
}

// @ 0x00a59eb0
void send_symbol(PdObject* o, void* a, void* b)
{
    EA::Audio::Eapd::pd_send_symbol((uint32_t)(uintptr_t)o->mAt28,
                                    (uint32_t)(uintptr_t)o->mAt2c,
                                    (uint32_t)(uintptr_t)a, (uint32_t)(uintptr_t)b);
}

// @ 0x00a59ed0
void FUN_00a59ed0(PdObject* o, void* a, void* b, void* c, void* d)
{
    EA::Audio::Eapd::pd_typedmess_bindings((uint32_t)(uintptr_t)o->mAt28,
                                           (uint32_t)(uintptr_t)o->mAt2c,
                                           (uint32_t)(uintptr_t)a, (uint32_t)(uintptr_t)b,
                                           (uint32_t)(uintptr_t)c, (uint32_t)(uintptr_t)d);
}

// @ 0x00a59f00
void* FUN_00a59f00(uint32_t a, uint32_t b)
{
    void* o = EA::Audio::Eapd::pd_new(g_spSendClass);
    if (o != 0)
    {
        PdPayload* p = (PdPayload*)((char*)o + 0x28);
        p->at28 = a;
        p->at2c = b;
    }
    return o;
}

// @ 0x00a59f30
bool send_setup()
{
    t_symbol sym;

    t_symbol* sp = EA::Audio::Eapd::gensym(&sym, "send");
    g_spSendClass = EA::Audio::Eapd::class_new(sp->s_name, sp->s_name2, (void*)&FUN_00a59f00,
                                               0, 0x30, 0, 6, 0);
    bool ok = (g_spSendClass != 0);

    sp = EA::Audio::Eapd::gensym(&sym, "send");
    ok &= (EA::Audio::Eapd::class_addcreator((void*)&FUN_00a59f00, sp->s_name, sp->s_name2, 6, 0) != 0);

    ok &= (EA::Audio::Eapd::class_addbang(g_spSendClass, (void*)&FUN_00a59e90) != 0);
    ok &= (EA::Audio::Eapd::class_doaddfloat(g_spSendClass, (void*)&FUN_00a5a000) != 0);
    ok &= (EA::Audio::Eapd::class_addsymbol(g_spSendClass, (void*)&send_symbol) != 0);
    ok &= (EA::Audio::Eapd::class_addlist(g_spSendClass, (void*)&FUN_00a5a020) != 0);
    ok &= (EA::Audio::Eapd::class_addanything(g_spSendClass, (void*)&FUN_00a59ed0) != 0);
    return ok;
}

// @ 0x00a5a000
void FUN_00a5a000(PdObject* o, float f)
{
    EA::Audio::Eapd::pd_send_float((uint32_t)(uintptr_t)o->mAt28,
                                   (uint32_t)(uintptr_t)o->mAt2c, f);
}

// @ 0x00a5a020
void FUN_00a5a020(PdObject* o, void* a, void* b, void* c, void* d)
{
    EA::Audio::Eapd::pd_list_bindings((uint32_t)(uintptr_t)o->mAt28,
                                      (uint32_t)(uintptr_t)o->mAt2c,
                                      (uint32_t)(uintptr_t)a, (uint32_t)(uintptr_t)b,
                                      (uint32_t)(uintptr_t)c, (uint32_t)(uintptr_t)d);
}

// @ 0x00a5a050
void* forward_new(uint32_t a, uint32_t b)
{
    void* o = EA::Audio::Eapd::pd_new(g_spForwardClass);
    if (o != 0)
    {
        PdPayload* p = (PdPayload*)((char*)o + 0x28);
        p->at28 = a;
        p->at2c = b;
        if (EA::Audio::Eapd::symbolinlet_new(o, (char*)o + 0x28) == 0)
        {
            EA::Audio::Eapd::pd_free(o);
            return 0;
        }
    }
    return o;
}

// @ 0x00a5a0a0
bool forward_setup()
{
    t_symbol sym;

    t_symbol* sp = EA::Audio::Eapd::gensym(&sym, "forward");
    g_spForwardClass = EA::Audio::Eapd::class_new(sp->s_name, sp->s_name2, (void*)&forward_new,
                                                  0, 0x30, 0, 6, 0);
    bool ok = (g_spForwardClass != 0);

    ok &= (EA::Audio::Eapd::class_addbang(g_spForwardClass, (void*)&FUN_00a59e90) != 0);
    ok &= (EA::Audio::Eapd::class_doaddfloat(g_spForwardClass, (void*)&FUN_00a5a000) != 0);
    ok &= (EA::Audio::Eapd::class_addsymbol(g_spForwardClass, (void*)&send_symbol) != 0);
    ok &= (EA::Audio::Eapd::class_addlist(g_spForwardClass, (void*)&FUN_00a5a020) != 0);
    ok &= (EA::Audio::Eapd::class_addanything(g_spForwardClass, (void*)&FUN_00a59ed0) != 0);
    return ok;
}

// @ 0x00a5a140
void FUN_00a5a140(PdObject* o, void* a, void* b)
{
    EA::Audio::Eapd::outlet_symbol(o->pOb, a, b);
}

// @ 0x00a5a160
void* receive_new(uint32_t a, uint32_t b)
{
    void* o = EA::Audio::Eapd::pd_new(g_spReceiveClass);
    if (o != 0)
    {
        PdPayload* p = (PdPayload*)((char*)o + 0x28);
        p->at28 = a;
        p->at2c = b;
        EA::Audio::Eapd::pd_bind(o, (void*)(uintptr_t)a, (void*)(uintptr_t)b);
        EA::Audio::Eapd::outlet_new(o, g_gEmptySymbol.s_name, g_gEmptySymbol2);
    }
    return o;
}

// @ 0x00a5a1b0
bool receive_setup()
{
    t_symbol sym;

    t_symbol* sp = EA::Audio::Eapd::gensym(&sym, "receive");
    g_spReceiveClass = EA::Audio::Eapd::class_new(sp->s_name, sp->s_name2, (void*)&receive_new,
                                                  (void*)0x00a4c2e0, 0x30, 8, 6, 0);
    bool ok = (g_spReceiveClass != 0);

    sp = EA::Audio::Eapd::gensym(&sym, "receive");
    ok &= (EA::Audio::Eapd::class_addcreator((void*)&receive_new, sp->s_name, sp->s_name2, 6, 0) != 0);

    ok &= (EA::Audio::Eapd::class_addbang(g_spReceiveClass, (void*)&FUN_00a59db0) != 0);
    ok &= (EA::Audio::Eapd::class_doaddfloat(g_spReceiveClass, (void*)0x00a61460) != 0);
    ok &= (EA::Audio::Eapd::class_addsymbol(g_spReceiveClass, (void*)&FUN_00a5a140) != 0);
    ok &= (EA::Audio::Eapd::class_addlist(g_spReceiveClass, (void*)0x00a614b0) != 0);
    ok &= (EA::Audio::Eapd::class_addanything(g_spReceiveClass, (void*)0x00a614e0) != 0);
    return ok;
}

// @ 0x00a5a280
void FUN_00a5a280(PdObject* o, float v)
{
    if (*(int*)((char*)o + 0x28) == 1 && v == *(float*)((char*)o + 0x2c))
    {
        EA::Audio::Eapd::outlet_bang(*(void**)((char*)o + 0x34));
        return;
    }
    int n = g_gOutletCount + 1;
    g_gOutletCount = n;
    if (n < 1000)
    {
        for (void* p = *(void**)((char*)*(void**)((char*)o + 0x38) + 8); p != 0; p = *(void**)p)
            EA::Audio::Eapd::outlet_float(*(void**)((char*)p + 4), v);
    }
    --g_gOutletCount;
}

// @ 0x00a5a2f0
void sel1_symbol(PdObject* o, int sym, void* b)
{
    if (*(int*)((char*)o + 0x28) == 2 && sym == *(int*)((char*)o + 0x2c))
    {
        EA::Audio::Eapd::outlet_bang(*(void**)((char*)o + 0x34));
        return;
    }
    EA::Audio::Eapd::outlet_symbol(*(void**)((char*)o + 0x38), (void*)(uintptr_t)sym, b);
}

// @ 0x00a5a330
void sel2_float(PdObject* o, float v)
{
    if (*(int*)((char*)o + 0x28) == 1)
    {
        int n = *(int*)((char*)o + 0x2c);
        SelectElement* e = *(SelectElement**)((char*)o + 0x30);
        while (n != 0)
        {
            --n;
            if (e->fKey == v)
            {
                EA::Audio::Eapd::outlet_bang(e->mOutlet);
                return;
            }
            ++e;
        }
    }
    int c = g_gOutletCount + 1;
    g_gOutletCount = c;
    if (c < 1000)
    {
        for (void* p = *(void**)((char*)*(void**)((char*)o + 0x34) + 8); p != 0; p = *(void**)p)
            EA::Audio::Eapd::outlet_float(*(void**)((char*)p + 4), v);
    }
    --g_gOutletCount;
}

// @ 0x00a5a3c0
void sel2_symbol(PdObject* o, int sym, void* b)
{
    if (*(int*)((char*)o + 0x28) == 2)
    {
        int n = *(int*)((char*)o + 0x2c);
        SelectElement* e = *(SelectElement**)((char*)o + 0x30);
        while (n != 0)
        {
            --n;
            if (*(int*)e == sym)
            {
                EA::Audio::Eapd::outlet_bang(e->mOutlet);
                return;
            }
            ++e;
        }
    }
    EA::Audio::Eapd::outlet_symbol(*(void**)((char*)o + 0x34), (void*)(uintptr_t)sym, b);
}

// @ 0x00a5a410
void* select_new(int argc, void* argv, int mode, int* atoms)
{
    if (argc == 0)
    {
        int local[3];
        local[0] = 1;
        local[1] = 0;
        local[2] = 0;
        atoms = local;
        mode = 1;
    }
    if (mode == 0 || mode == 1)
    {
        void* o = EA::Audio::Eapd::pd_new(g_spSelectClass);
        if (o != 0)
        {
            *(int*)((char*)o + 0x28) = atoms[0];
            *(int*)((char*)o + 0x2c) = atoms[1];
            *(int*)((char*)o + 0x30) = atoms[2];
            *(void**)((char*)o + 0x34) = EA::Audio::Eapd::outlet_new(o, g_gBangSymbol.s_name, g_gBangSymbol2);
            if (atoms[0] == 1)
                EA::Audio::Eapd::floatinlet_new(o, (char*)o + 0x2c);
            else
                EA::Audio::Eapd::symbolinlet_new(o, (char*)o + 0x2c);
            *(void**)((char*)o + 0x38) = atoms[0] == 1
                ? EA::Audio::Eapd::outlet_new(o, g_gFloatSymbol.s_name, g_gFloatSymbol2)
                : EA::Audio::Eapd::outlet_new(o, g_gSymbolSymbol.s_name, g_gSymbolSymbol2);
        }
        return o;
    }

    void* o = EA::Audio::Eapd::pd_new(g_spSelect2Class);
    if (o != 0)
    {
        *(int*)((char*)o + 0x2c) = mode;
        SelectElement* e = (SelectElement*)EA::Audio::Eapd::getbytes(mode * 0xc, "EAPd/t_selectelement");
        *(SelectElement**)((char*)o + 0x30) = e;
        *(int*)((char*)o + 0x28) = atoms[0];
        for (int i = 0; i < mode; ++i)
        {
            e->mOutlet = EA::Audio::Eapd::outlet_new(o, g_gBangSymbol.s_name, g_gBangSymbol2);
            int t = atoms[0];
            *(int*)((char*)o + 0x28) = t;
            if (t == 1)
                e->fKey = EA::Audio::Eapd::atom_getfloat_at(i, mode, atoms);
            else
                *(t_symbol*)e = *EA::Audio::Eapd::atom_getsymbol_at((t_symbol*)e, i, mode, atoms);
            ++e;
        }
        *(void**)((char*)o + 0x34) = EA::Audio::Eapd::outlet_new(o, g_gFloatSymbol.s_name, g_gFloatSymbol2);
    }
    return o;
}

// @ 0x00a5a590
namespace EA {
namespace Audio {
namespace Eapd {
bool select_setup()
{
    t_symbol_s00a5_a590 sym;
    gSelectClass = class_new(*gensym(&sym, "select"), 0, 0, 0x3c, 0, 0);
    byte ok = (byte)((gSelectClass != 0) & 1);
    ok &= class_doaddfloat(gSelectClass, (void*)sel1_float);
    ok &= class_addsymbol(gSelectClass, (void*)sel1_symbol);
    gSelect2Class = class_new(*gensym(&sym, "select"), 0, (void*)route_free, 0x38, 0, 0);
    byte ok2 = (byte)((gSelect2Class != 0) & 1);
    ok &= ok2;
    ok &= class_doaddfloat(gSelect2Class, (void*)sel2_float);
    ok &= class_addsymbol(gSelect2Class, (void*)sel2_symbol);
    ok &= class_addcreator((void*)select_new, *gensym(&sym, "select"), 9, 0);
    ok &= class_addcreator((void*)select_new, *gensym(&sym, "sel"), 9, 0);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a5a730
namespace EA { namespace Audio { namespace Eapd {
void route_list(RouteObj* obj, t_symbol_s00a5_a590 s, int argc, Atom* argv)
{
    if (obj->mode == 1) {
        if (argc == 0)
            return;
        float key = atom_getfloat(argv);
        RouteElement* e = obj->elems;
        int n = obj->count;
        while (n-- != 0) {
            if (e->key == key) {
                if (argc > 1 && argv[1].type == 2) {
                    outlet_anything(e->outlet, argv[1].sym, argc - 2, argv + 2);
                    return;
                }
                outlet_list(e->outlet, gListSymbol, argc - 1, argv + 1);
                return;
            }
            e++;
        }
    } else if (argc < 2) {
        if (argc == 0) {
            RouteElement* e = obj->elems;
            int n = obj->count;
            while (n-- != 0) {
                if (e->sym.name == gBangSymbol.name) {
                    outlet_bang(e->outlet);
                    return;
                }
                e++;
            }
        } else if (argv->type == 1) {
            RouteElement* e = obj->elems;
            int n = obj->count;
            while (n-- != 0) {
                if (e->sym.name == gFloatSymbol.name) {
                    float f = argv->f;
                    void* out = e->outlet;
                    gOutletCount++;
                    if (gOutletCount < 1000) {
                        for (Dest* d = ((Outlet*)out)->dests; d != 0; d = d->next)
                            outlet_float(d->outlet, f);
                    }
                    gOutletCount--;
                    return;
                }
                e++;
            }
        } else {
            RouteElement* e = obj->elems;
            int n = obj->count;
            while (n-- != 0) {
                if (e->sym.name == gSymbolSymbol.name) {
                    outlet_symbol(e->outlet, argv->sym);
                    return;
                }
                e++;
            }
        }
    } else {
        RouteElement* e = obj->elems;
        int n = obj->count;
        while (n-- != 0) {
            if (e->sym.name == gListSymbol.name) {
                if (argc > 0 && argv->type == 2) {
                    outlet_anything(e->outlet, argv->sym, argc - 1, argv + 1);
                    return;
                }
                outlet_list(e->outlet, gListSymbol, argc, argv);
                return;
            }
            e++;
        }
    }
    outlet_list(obj->outlet, gListSymbol, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5a960
namespace EA { namespace Audio { namespace Eapd {
void route_free(RouteObj* obj)
{
    freebytes(obj->elems, obj->count * sizeof(RouteElement));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5a980
namespace EA { namespace Audio { namespace Eapd {
void* route_new(t_symbol_s00a5_a590* s, int argc, Atom* argv)
{
    RouteObj* obj = (RouteObj*)pd_new(spRouteClass);
    if (obj == 0)
        return 0;
    Atom def[1];
    if (argc == 0) {
        argc = 1;
        argv = def;
        def[0].type = 1;
        def[0].f = 0.0f;
    }
    obj->mode = argv->type;
    obj->count = argc;
    obj->elems = (RouteElement*)getbytes(argc * sizeof(RouteElement), "EAPd/t_routeelement");
    for (int i = 0; i < argc; i++) {
        RouteElement* e = &obj->elems[i];
        e->outlet = outlet_new(obj, gListSymbol);
        if (obj->mode == 1) {
            e->key = atom_getfloat_at(i, argc, argv);
        } else {
            t_symbol_s00a5_a590 tmp;
            e->sym = *atom_getsymbol_at(&tmp, i, argc, argv);
        }
    }
    obj->outlet = outlet_new(obj, gListSymbol);
    return obj;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5aa70
namespace EA { namespace Audio { namespace Eapd {
byte route_setup()
{
    t_symbol_s00a5_a590 sym;
    spRouteClass = class_new(*gensym(&sym, "route"), (void*)route_new, (void*)route_free, 0x38, 0,
                             9, 0);
    byte ok = (byte)((spRouteClass != 0) & 1);
    ok &= class_addlist(spRouteClass, (void*)route_list);
    ok &= class_addanything(spRouteClass, (void*)route_anything);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5aae0
namespace EA { namespace Audio { namespace Eapd {
void* pack_new(t_symbol_s00a5_a590* s, int argc, Atom* argv)
{
    PackObj* obj = (PackObj*)pd_new(gPackClass);
    if (obj == 0)
        return 0;
    Atom def[2];
    if (argc == 0) {
        argc = 2;
        argv = def;
        def[0].type = 1;
        def[0].f = 0.0f;
        def[1].type = 1;
        def[1].f = 0.0f;
    }
    obj->count = argc;
    obj->atoms = (Atom*)getbytes(argc * sizeof(Atom), "EAPd/t_pack_atoms");
    obj->atoms2 = (Atom*)getbytes(argc * sizeof(Atom), "EAPd/t_pack_atoms");
    Atom* a = obj->atoms;
    for (int i = 0; i < argc; i++) {
        if (argv[i].type == 1) {
            a[i] = argv[i];
            if (i != 0)
                floatinlet_new(obj, &a[i].f);
        } else if (argv[i].type == 2) {
            if (argv[i].sym.name[0] == 's' || argv[i].sym.name[0] == 'S') {
                a[i].type = 2;
                a[i].sym = gSymbolSymbol;
                if (i != 0)
                    symbolinlet_new(obj, &a[i].sym);
            } else {
                a[i].type = 1;
                a[i].f = 0.0f;
                if (i != 0)
                    floatinlet_new(obj, &a[i].f);
            }
        }
    }
    obj->outlet = outlet_new(obj, gListSymbol);
    return obj;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ac40
namespace EA { namespace Audio { namespace Eapd {
void pack_bang(PackObj* obj)
{
    int alloc = 0;
    Atom* list = obj->atoms2;
    int size = obj->count * sizeof(Atom);
    if (list == 0) {
        list = (Atom*)getbytes(size, "EAPd/t_pack_atoms");
        alloc = 1;
    } else {
        obj->atoms2 = 0;
    }
    memcpy(list, obj->atoms, size);
    outlet_list(obj->outlet, gListSymbol, obj->count, list);
    if (alloc)
        freebytes(list, size);
    else
        obj->atoms2 = list;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5acc0
namespace EA { namespace Audio { namespace Eapd {
void pack_float(PackObj* obj, float f)
{
    Atom* a = obj->atoms;
    if (a->type == 1) {
        a->f = f;
        pack_bang(obj);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ace0
namespace EA { namespace Audio { namespace Eapd {
void pack_symbol(PackObj* obj, t_symbol_s00a5_a590 s)
{
    Atom* a = obj->atoms;
    if (a->type == 2) {
        a->sym = s;
        pack_bang(obj);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ad10
namespace EA { namespace Audio { namespace Eapd {
void pack_list(PackObj* obj, t_symbol_s00a5_a590 s, int argc, Atom* argv)
{
    obj_list(obj, s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ad40
namespace EA { namespace Audio { namespace Eapd {
void pack_anything(PackObj* obj, t_symbol_s00a5_a590 s, int argc, Atom* argv)
{
    int size = (argc * 3 + 3) * 4;
    Atom* list = (Atom*)getbytes(size, "EAPd/t_pack_atoms");
    for (int i = 0; i < argc; i++)
        list[i + 1] = argv[i];
    list[0].type = 2;
    list[0].sym = s;
    obj_list(obj, gListSymbol, argc + 1, list);
    freebytes(list, size);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5add0
namespace EA { namespace Audio { namespace Eapd {
void pack_free(PackObj* obj)
{
    freebytes(obj->atoms, obj->count * sizeof(Atom));
    freebytes(obj->atoms2, obj->count * sizeof(Atom));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ae10
namespace EA { namespace Audio { namespace Eapd {
byte pack_setup()
{
    t_symbol_s00a5_a590 sym;
    gPackClass = class_new(*gensym(&sym, "pack"), (void*)pack_new, (void*)pack_free, 0x34, 0, 9,
                           0);
    byte ok = (byte)((gPackClass != 0) & 1);
    ok &= class_addbang(gPackClass, (void*)pack_bang);
    ok &= class_doaddfloat(gPackClass, (void*)pack_float);
    ok &= class_addsymbol(gPackClass, (void*)pack_symbol);
    ok &= class_addlist(gPackClass, (void*)pack_list);
    ok &= class_addanything(gPackClass, (void*)pack_anything);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5afa0
namespace EA { namespace Audio { namespace Eapd {
void unpack_list(UnpackObj* obj, t_symbol_s00a5_a590 s, int argc, Atom* argv)
{
    if (argc > obj->count)
        argc = obj->count;
    OutElem* e = &obj->outs[argc - 1];
    int n = argc;
    Atom* a = &argv[argc - 1];
    while (n != 0) {
        n--;
        if (e->type == a->type) {
            if (e->type == 1) {
                float f = a->f;
                void* out = e->outlet;
                gOutletCount++;
                if (gOutletCount < 1000) {
                    for (Dest* d = ((Outlet*)out)->dests; d != 0; d = d->next)
                        outlet_float(d->outlet, f);
                }
                gOutletCount--;
            } else if (e->type == 2) {
                outlet_symbol(e->outlet, a->sym);
            }
        }
        e--;
        a--;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b070
namespace EA { namespace Audio { namespace Eapd {
void unpack_anything(UnpackObj* obj, t_symbol_s00a5_a590 s, int argc, Atom* argv)
{
    int size = (argc * 3 + 3) * 4;
    Atom* list = (Atom*)getbytes(size, "EAPd/t_unpack_atoms");
    for (int i = 0; i < argc; i++)
        list[i + 1] = argv[i];
    list[0].type = 2;
    list[0].sym = s;
    unpack_list(obj, gListSymbol, argc + 1, list);
    freebytes(list, size);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b100
namespace EA { namespace Audio { namespace Eapd {
void unpack_free(UnpackObj* obj)
{
    freebytes(obj->outs, obj->count * sizeof(OutElem));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b120
namespace EA { namespace Audio { namespace Eapd {
byte unpack_setup()
{
    t_symbol_s00a5_a590 sym;
    spUnpackClass = class_new(*gensym(&sym, "unpack"), (void*)unpack_new, (void*)unpack_free,
                              0x30, 0, 9, 0);
    byte ok = (byte)((spUnpackClass != 0) & 1);
    ok &= class_addlist(spUnpackClass, (void*)unpack_list);
    ok &= class_addanything(spUnpackClass, (void*)unpack_anything);
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b190
namespace EA { namespace Audio { namespace Eapd {
void* trigger_new(t_symbol_s00a5_a590* s, int argc, Atom* argv)
{
    TriggerObj* obj = (TriggerObj*)pd_new(spTriggerClass);
    if (obj == 0)
        return 0;
    Atom def[2];
    if (argc == 0) {
        argc = 2;
        argv = def;
        def[0].type = 2;
        def[0].sym = gBangSymbol;
        def[1] = def[0];
    }
    obj->count = argc;
    obj->outs = (OutElem*)getbytes(argc * sizeof(OutElem), "EAPd/t_triggerout");
    for (int i = 0; i < argc; i++) {
        char c = argv[i].type == 2 ? argv[i].sym.name[0] : (argv[i].type == 1 ? 'f' : 0);
        int type;
        t_symbol_s00a5_a590 sym;
        switch (c) {
        case 'a':
        case 'A':
            type = 4;
            sym = gAnythingSymbol;
            break;
        case 'b':
        case 'B':
            type = 0;
            sym = gBangSymbol;
            break;
        case 'f':
        case 'F':
            type = 1;
            sym = gFloatSymbol;
            break;
        case 'l':
        case 'L':
            type = 3;
            sym = gListSymbol;
            break;
        case 's':
        case 'S':
            type = 2;
            sym = gSymbolSymbol;
            break;
        default:
            type = 1;
            sym = gFloatSymbol;
            break;
        }
        obj->outs[i].type = type;
        obj->outs[i].outlet = outlet_new(obj, sym);
    }
    return obj;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b330
namespace EA { namespace Audio { namespace Eapd {
void trigger_list(TriggerObj* obj, t_symbol_s00a5_a590 s, int argc, Atom* argv)
{
    int n = obj->count;
    OutElem* e = &obj->outs[n - 1];
    while (n != 0) {
        n--;
        if (e->type == 1) {
            float f = argc != 0 ? atom_getfloat(argv) : 0.0f;
            void* out = e->outlet;
            gOutletCount++;
            if (gOutletCount < 1000) {
                for (Dest* d = ((Outlet*)out)->dests; d != 0; d = d->next)
                    outlet_float(d->outlet, f);
            }
            gOutletCount--;
        } else if (e->type == 0) {
            outlet_bang(e->outlet);
        } else if (e->type == 2) {
            if (argc == 0) {
                outlet_symbol(e->outlet, gEmptySymbol);
            } else {
                t_symbol_s00a5_a590 tmp;
                outlet_symbol(e->outlet, *atom_getsymbol(&tmp, argv));
            }
        } else {
            outlet_list(e->outlet, gListSymbol, argc, argv);
        }
        e--;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b450
namespace EA { namespace Audio { namespace Eapd {
void trigger_anything(TriggerObj* obj, t_symbol_s00a5_a590 s, int argc, Atom* argv)
{
    int n = obj->count;
    OutElem* e = &obj->outs[n - 1];
    while (n != 0) {
        n--;
        if (e->type == 0)
            outlet_bang(e->outlet);
        else if (e->type == 4)
            outlet_anything(e->outlet, s, argc, argv);
        e--;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b4b0
namespace EA { namespace Audio { namespace Eapd {
void trigger_bang(TriggerObj* obj)
{
    trigger_list(obj, gListSymbol, 0, 0);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b4d0
namespace EA { namespace Audio { namespace Eapd {
void trigger_float(TriggerObj* obj, float f)
{
    Atom a;
    a.type = 1;
    a.f = f;
    trigger_list(obj, gListSymbol, 1, &a);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b510
namespace EA { namespace Audio { namespace Eapd {
void trigger_symbol(char* x, t_symbol_s00a5_b510 s)
{
    struct { int type; t_symbol_s00a5_b510 sym; } atom;
    atom.type = 2;                    // A_SYMBOL
    atom.sym  = s;
    trigger_list(x, gListSymbol_s00a5_b510.mHash, gListSender.mHash, 1, &atom);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b550
namespace EA { namespace Audio { namespace Eapd {
bool trigger_setup(void)
{
    t_symbol_s00a5_b510 s;
    t_symbol_s00a5_b510* sym;
    bool ok = true;

    sym = gensym(&s, "trigger");
    spTriggerClass = class_new_t2(*sym, (void*)0xa5b190, (void*)0xa5b100, 0x30, 0, 9, 0);
    ok = ok && (spTriggerClass != 0);

    sym = gensym(&s, "t");           // 0x14335f8
    ok = class_addcreator((void*)0xa5b190, *sym, 9, 0) && ok;

    ok = class_addlist_s00a5_b510(spTriggerClass, (void*)0xa5b330) && ok;
    ok = class_addbang(spTriggerClass, (void*)0xa5b4b0) && ok;
    ok = class_doaddfloat(spTriggerClass, (void*)0xa5b4d0) && ok;
    ok = class_addsymbol_s00a5_b510(spTriggerClass, (void*)trigger_symbol) && ok;
    ok = class_addanything_s00a5_b510(spTriggerClass, (void*)0xa5b450) && ok;
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b620
namespace EA { namespace Audio { namespace Eapd {
char* spigot_new(float f)
{
    char* x = (char*)pd_new(spSpigotClass);
    if (x != 0) {
        floatinlet_new(x, x + 0x28);
        char* o = (char*)outlet_new(x, gEmptySymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gEmptySymbol_s00a5_b510 /*DAT_016758a0*/);
        setObjP(x, 0x2c, o);
        setObjF(x, 0x28, f);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b670
namespace EA { namespace Audio { namespace Eapd {
void spigot_bang(char* x)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_bang((char*)objP(x, 0x2c));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b6a0
namespace EA { namespace Audio { namespace Eapd {
void spigot_float(char* x, float f)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_cnt((t_outlet*)objP(x, 0x2c), f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b700
namespace EA { namespace Audio { namespace Eapd {
void spigot_symbol(char* x, t_symbol_s00a5_b510 s)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_symbol((char*)objP(x, 0x2c), s);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b730
namespace EA { namespace Audio { namespace Eapd {
void spigot_list(char* x, t_symbol_s00a5_b510 s, int argc, void* argv)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_list((char*)objP(x, 0x2c), s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b770
namespace EA { namespace Audio { namespace Eapd {
void spigot_anything(char* x, t_symbol_s00a5_b510 s, int argc, void* argv)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_anything((char*)objP(x, 0x2c), s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b7b0
namespace EA { namespace Audio { namespace Eapd {
bool spigot_setup(void)
{
    t_symbol_s00a5_b510 s;
    t_symbol_s00a5_b510* sym;
    bool ok = true;

    sym = gensym(&s, "spigot");
    spSpigotClass = class_new_t2(*sym, (void*)spigot_new, 0, 0x30, 0, 5, 0);
    ok = ok && (spSpigotClass != 0);

    ok = class_addbang(spSpigotClass, (void*)spigot_bang) && ok;
    ok = class_doaddfloat(spSpigotClass, (void*)spigot_float) && ok;
    ok = class_addsymbol_s00a5_b510(spSpigotClass, (void*)spigot_symbol) && ok;
    ok = class_addlist_s00a5_b510(spSpigotClass, (void*)spigot_list) && ok;
    ok = class_addanything_s00a5_b510(spSpigotClass, (void*)spigot_anything) && ok;
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b850
namespace EA { namespace Audio { namespace Eapd {
char* gate_new(float n, float init)
{
    static const float fOne = 1.0f;      // 0x1485720
    if (n < fOne)
        n = fOne;
    if (0.0f <= init) {
        if (n < init)
            init = n;
    } else {
        init = 0.0f;
    }

    char* x = (char*)pd_new(spGateClass);
    if (x != 0) {
        setObjI(x, 0x2c, (int)n);
        setObjF(x, 0x30, init);
        void* p = getbytes((int)n * 4, "EAPd/t_outlet*");
        setObjP(x, 0x28, p);
        if (p == 0) {
            pd_free(x);
            return x;
        }
        floatinlet_new(x, x + 0x30);
        for (int i = 0; i < objI(x, 0x2c); ++i) {
            void* o = outlet_new(x, gEmptySymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gEmptySymbol_s00a5_b510 /*DAT_016758a0*/);
            ((void**)objP(x, 0x28))[i] = o;
        }
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b920
namespace EA { namespace Audio { namespace Eapd {
void gate_free(char* x)
{
    if (objP(x, 0x28) != 0)
        freebytes(objP(x, 0x28), objI(x, 0x2c) * 4);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b940
namespace EA { namespace Audio { namespace Eapd {
void gate_bang(char* x)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_bang((char*)((void**)objP(x, 0x28))[i - 1]);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b970
namespace EA { namespace Audio { namespace Eapd {
void gate_float(char* x, float f)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_cnt((t_outlet*)((void**)objP(x, 0x28))[i - 1], f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5b9e0
namespace EA { namespace Audio { namespace Eapd {
void gate_symbol(char* x, t_symbol_s00a5_b510 s)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_symbol((char*)((void**)objP(x, 0x28))[i - 1], s);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ba20
namespace EA { namespace Audio { namespace Eapd {
void gate_list(char* x, t_symbol_s00a5_b510 s, int argc, void* argv)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_list((char*)((void**)objP(x, 0x28))[i - 1], s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5ba60
namespace EA { namespace Audio { namespace Eapd {
void gate_anything(char* x, t_symbol_s00a5_b510 s, int argc, void* argv)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_anything((char*)((void**)objP(x, 0x28))[i - 1], s, argc, argv);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5baa0
namespace EA { namespace Audio { namespace Eapd {
bool gate_setup(void)
{
    t_symbol_s00a5_b510 s;
    t_symbol_s00a5_b510* sym;
    bool ok = true;

    sym = gensym(&s, "gate");
    spGateClass = class_new_t3(*sym, (void*)gate_new, (void*)gate_free, 0x34, 0, 5, 5, 0);
    ok = ok && (spGateClass != 0);

    ok = class_addbang(spGateClass, (void*)gate_bang) && ok;
    ok = class_doaddfloat(spGateClass, (void*)gate_float) && ok;
    ok = class_addsymbol_s00a5_b510(spGateClass, (void*)gate_symbol) && ok;
    ok = class_addlist_s00a5_b510(spGateClass, (void*)gate_list) && ok;
    ok = class_addanything_s00a5_b510(spGateClass, (void*)gate_anything) && ok;
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bb50
namespace EA { namespace Audio { namespace Eapd {
char* switch_new(float n, float onoff)
{
    static const float fOne = 1.0f;      // 0x1485720
    if (n < fOne)
        n = fOne;
    if (0.0f <= onoff) {
        if (n < onoff)
            onoff = n;
    } else {
        onoff = 0.0f;
    }

    char* x = (char*)pd_new(spSwitchClass);
    if (x != 0) {
        setObjI(x, 0x2c, (int)n);
        setObjI(x, 0x30, (int)onoff);
        void* p = getbytes((int)n * 0x30, "EAPd/t_spigot");
        setObjP(x, 0x28, p);
        if (p == 0) {
            pd_free(x);
            return x;
        }
        void* o = outlet_new(x, gEmptySymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gEmptySymbol_s00a5_b510 /*DAT_016758a0*/);
        for (int i = 0; i < objI(x, 0x2c); ++i) {
            char* sp = (char*)objP(x, 0x28) + i * 0x30;
            setObjP(sp, 0x00, spSpigotClass);
            setObjP(sp, 0x2c, o);
            setObjF(sp, 0x28, (float)(i == objI(x, 0x30) - 1));
            inlet_new(x, sp, gEmptySymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gEmptySymbol_s00a5_b510 /*DAT_016758a0*/,
                      gEmptySymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gEmptySymbol_s00a5_b510 /*DAT_016758a0*/);
        }
        inlet_new(x, x, gEmptySymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gEmptySymbol_s00a5_b510 /*DAT_016758a0*/,
                  gEmptySymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gEmptySymbol_s00a5_b510 /*DAT_016758a0*/);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bc70
namespace EA { namespace Audio { namespace Eapd {
void switch_free(char* x)
{
    if (objP(x, 0x28) != 0)
        freebytes(objP(x, 0x28), objI(x, 0x2c) * 0x30);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bc90
namespace EA { namespace Audio { namespace Eapd {
void switch_float(char* x, float f)
{
    int i = (int)f;
    if (i < 0)
        i = 0;
    else if (objI(x, 0x2c) < i)
        i = objI(x, 0x2c);

    if (objI(x, 0x30) > 0)
        setObjF((char*)objP(x, 0x28) + objI(x, 0x30) * 0x30, -8, 0.0f);

    setObjI(x, 0x30, i);

    if (i > 0) {
        static const float fOne = 1.0f;      // 0x1485720
        setObjF((char*)objP(x, 0x28) + i * 0x30, -8, fOne);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bcf0
namespace EA { namespace Audio { namespace Eapd {
bool switch_setup(void)
{
    t_symbol_s00a5_b510 s;
    t_symbol_s00a5_b510* sym;
    bool ok = true;

    sym = gensym(&s, "switch");
    spSwitchClass = class_new_t3(*sym, (void*)switch_new, (void*)switch_free, 0x34, 8, 5, 5, 0);
    ok = ok && (spSwitchClass != 0);

    ok = class_doaddfloat(spSwitchClass, (void*)switch_float) && ok;
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bd50
namespace EA { namespace Audio { namespace Eapd {
char* moses_new(float f)
{
    char* x = (char*)pd_new(spMosesClass);
    if (x != 0) {
        floatinlet_new(x, x + 0x2c);
        outlet_new(x, gFloatSymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gFloatSymbol_s00a5_b510 /*DAT_016758c8*/);
        char* o = (char*)outlet_new(x, gFloatSymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gFloatSymbol_s00a5_b510 /*DAT_016758c8*/);
        setObjP(x, 0x28, o);
        setObjF(x, 0x2c, f);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bdb0
namespace EA { namespace Audio { namespace Eapd {
void moses_float(char* x, float f)
{
    if (objF(x, 0x2c) <= f)
        outlet_cnt((t_outlet*)objP(x, 0x28), f);
    else
        outlet_cnt((t_outlet*)objP(x, 0xc), f);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5be50
namespace EA { namespace Audio { namespace Eapd {
bool moses_setup(void)
{
    t_symbol_s00a5_b510 s;
    t_symbol_s00a5_b510* sym;
    bool ok = true;

    sym = gensym(&s, "moses");
    spMosesClass = class_new_t2(*sym, (void*)moses_new, 0, 0x30, 0, 5, 0);
    ok = ok && (spMosesClass != 0);

    ok = class_doaddfloat(spMosesClass, (void*)moses_float) && ok;
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bf20
namespace EA { namespace Audio { namespace Eapd {
void until_bang(char* x)
{
    setObjI(x, 0x28, 1);
    setObjI(x, 0x2c, -1);
    do {
        if (objI(x, 0x2c) == 0)
            return;
        setObjI(x, 0x2c, objI(x, 0x2c) - 1);
        outlet_bang((char*)objP(x, 0xc));
    } while (objI(x, 0x28) != 0);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bf60
namespace EA { namespace Audio { namespace Eapd {
void until_float(char* x, float f)
{
    setObjI(x, 0x28, 1);
    setObjI(x, 0x2c, (int)f);
    do {
        if (objI(x, 0x2c) == 0)
            return;
        setObjI(x, 0x2c, objI(x, 0x2c) - 1);
        outlet_bang((char*)objP(x, 0xc));
    } while (objI(x, 0x28) != 0);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bfa0
namespace EA { namespace Audio { namespace Eapd {
void until_bang2(char* x)
{
    setObjI(x, 0x28, 0);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5bfb0
namespace EA { namespace Audio { namespace Eapd {
bool until_setup(void)
{
    t_symbol_s00a5_b510 s;
    t_symbol_s00a5_b510* sym;
    bool ok = true;

    sym = gensym(&s, "until");
    spUntilClass = class_new_t1(*sym, (void*)0xa5bea0, 0, 0x30, 0, 0);
    ok = ok && (spUntilClass != 0);

    ok = class_addbang(spUntilClass, (void*)until_bang) && ok;
    ok = class_doaddfloat(spUntilClass, (void*)until_float) && ok;

    sym = gensym(&s, "bang2");
    ok = class_addmethod1(spUntilClass, (void*)until_bang2, *sym, 0) && ok;
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c040
namespace EA { namespace Audio { namespace Eapd {
char* makefilename_new(t_symbol_s00a5_b510 s, int hasFormat)
{
    char* x = (char*)pd_new(spMakefilenameClass);
    if (x != 0) {
        if (hasFormat == 0) {
            t_symbol_s00a5_b510 tmp;
            t_symbol_s00a5_b510* p = gensym(&tmp, "file.%d");
            s = *p;
        }
        outlet_new(x, gSymbolSymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gSymbolSymbol_s00a5_b510 /*DAT_01675898*/);
        *(t_symbol_s00a5_b510*)(x + 0x28) = s;
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c0b0
namespace EA { namespace Audio { namespace Eapd {
void makefilename_float(char* x, float f)
{
    char buf[1000];
    espd_sprintf(buf, (const char*)objP(x, 0x2c), (int)f);
    t_symbol_s00a5_b510 tmp;
    t_symbol_s00a5_b510* p = gensym(&tmp, buf);
    outlet_symbol((char*)objP(x, 0xc), *p);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c100
namespace EA { namespace Audio { namespace Eapd {
void makefilename_symbol(char* x, t_symbol_s00a5_b510 s)
{
    char buf[1000];
    espd_sprintf(buf, (const char*)objP(x, 0x2c), s.mpName);
    t_symbol_s00a5_b510 tmp;
    t_symbol_s00a5_b510* p = gensym(&tmp, buf);
    outlet_symbol((char*)objP(x, 0xc), *p);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c150
namespace EA { namespace Audio { namespace Eapd {
bool makefilename_setup(void)
{
    t_symbol_s00a5_b510 s;
    t_symbol_s00a5_b510* sym;
    bool ok = true;

    sym = gensym(&s, "makefilename");
    spMakefilenameClass = class_new_t2(*sym, (void*)makefilename_new, 0, 0x30, 0, 6, 0);
    ok = ok && (spMakefilenameClass != 0);

    ok = class_doaddfloat(spMakefilenameClass, (void*)makefilename_float) && ok;
    ok = class_addsymbol_s00a5_b510(spMakefilenameClass, (void*)makefilename_symbol) && ok;

    sym = gensym(&s, "set");           // 0x13f2ce4
    ok = class_addmethod2(spMakefilenameClass, (void*)0xa57730, *sym, 2, 0) && ok;
    return ok;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c1f0
namespace EA { namespace Audio { namespace Eapd {
char* swap_new(float f)
{
    char* x = (char*)pd_new(spSwapClass);
    if (x != 0) {
        setObjF(x, 0x30, f);
        setObjF(x, 0x2c, 0.0f);
        outlet_new(x, gFloatSymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gFloatSymbol_s00a5_b510 /*DAT_016758c8*/);
        char* o = (char*)outlet_new(x, gFloatSymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gFloatSymbol_s00a5_b510 /*DAT_016758c8*/);
        setObjP(x, 0x28, o);
        floatinlet_new(x, x + 0x30);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c260
namespace EA { namespace Audio { namespace Eapd {
void swap_bang(char* x)
{
    outlet_cnt((t_outlet*)objP(x, 0x28), objF(x, 0x2c));
    outlet_cnt((t_outlet*)objP(x, 0xc), objF(x, 0x30));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c300
namespace EA { namespace Audio { namespace Eapd {
void swap_float(char* x, float f)
{
    setObjF(x, 0x2c, f);
    swap_bang(x);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c320
namespace EA {
namespace Audio {
namespace Eapd {
bool swap_setup()
{
    t_symbol_s00a5_b510 s;
    t_symbol_s00a5_b510* sym;
    bool ok = true;

    sym = gensym(&s, "swap");          // 0x1455238
    spSwapClass = class_new_t2(*sym, (void*)swap_new, 0, 0x34, 0, 5, 0);
    ok = ok && (spSwapClass != 0);

    sym = gensym(&s, "fswap");         // 0x1455230
    ok = class_addcreator((void*)swap_new, *sym, 5, 0) && ok;

    ok = class_addbang(spSwapClass, (void*)swap_bang) && ok;
    ok = class_doaddfloat(spSwapClass, (void*)swap_float) && ok;
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a5c3c0
namespace EA { namespace Audio { namespace Eapd {
char* change_new(float f)
{
    char* x = (char*)pd_new(spChangeClass);
    if (x != 0) {
        setObjF(x, 0x28, f);
        outlet_new(x, gFloatSymbol_s00a5_b510, *(t_symbol_s00a5_b510*)&gFloatSymbol_s00a5_b510 /*DAT_016758c8*/);
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c400
namespace EA { namespace Audio { namespace Eapd {
void change_float(char* x, float f)
{
    if (999 < gOutletCount + 1)
        return;
    outlet_cnt((t_outlet*)objP(x, 0xc), objF(x, 0x28));
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c460
namespace EA { namespace Audio { namespace Eapd {
void change_float(t_change* self, float v)
{
    if (v != self->value) {
        self->value = v;
        t_outletlist* list = self->outlets;
        gOutletCount++;
        if (gOutletCount < 1000) {
            for (t_outlet_s00a5_c460* o = list->first; o != 0; o = o->next)
                outlet_float(o->target, v);
        }
        gOutletCount--;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c4c0
namespace EA { namespace Audio { namespace Eapd {
void change_set(t_change* self, float v)
{
    self->value = v;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c570
namespace EA { namespace Audio { namespace Eapd {
float* value_get(t_symbol_s00a5_c460 key)
{
    t_vcommon* p = (t_vcommon*)pd_findbyclass(key.a, key.b, spVcommonClass);
    if (p == 0) {
        p = (t_vcommon*)pd_new(spVcommonClass);
        p->value = 0.0f;
        p->refs = 0;
        pd_bind(p, key);
    }
    p->refs++;
    return &p->value;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c5d0
namespace EA { namespace Audio { namespace Eapd {
t_value* value_new(t_symbol_s00a5_c460 key)
{
    t_value* v = (t_value*)pd_new(spValueClass);
    if (v != 0) {
        v->key = key;
        v->value = value_get(key);
        outlet_new(v, gFloatSymbol_s00a5_c460);
    }
    return v;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c620
namespace EA { namespace Audio { namespace Eapd {
void value_bang(t_value* self)
{
    float v = *self->value;
    t_outletlist* list = self->outlets;
    gOutletCount++;
    if (gOutletCount < 1000) {
        for (t_outlet_s00a5_c460* o = list->first; o != 0; o = o->next)
            outlet_float(o->target, v);
    }
    gOutletCount--;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c680
namespace EA { namespace Audio { namespace Eapd {
void value_float(t_value* self, float v)
{
    *self->value = v;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c6a0
namespace EA { namespace Audio { namespace Eapd {
void value_free(t_value* self)
{
    int a = self->key.a;
    int b = self->key.b;
    t_vcommon* p = (t_vcommon*)pd_findbyclass(a, b, spVcommonClass);
    if (p != 0) {
        if (--p->refs == 0) {
            sys_vgui(p, a, b);
            pd_free(p);
        }
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a5c6f0
namespace EA { namespace Audio { namespace Eapd {
byte value_setup()
{
    t_symbol_s00a5_c460 tmp;
    t_symbol_s00a5_c460* s = gensym(&tmp, "value");
    spValueClass = class_new(*s, (void*)value_new, (void*)value_free, 0x34, 0, 6, 0);
    byte ok = (spValueClass != 0) & 1;
    s = gensym(&tmp, "float");
    ok = ok & class_addcreator((void*)value_new, *s, 6, 0);
    ok = ok & class_addbang(spValueClass, (void*)value_bang);
    ok = ok & class_doaddfloat(spValueClass, (void*)value_float);
    s = gensym(&tmp, "value");
    spVcommonClass = class_new(*s, 0, 0, 0xc, 1, 0);
    ok = ok & (spVcommonClass != 0);
    return ok;
}
}}}  // namespace EA::Audio::Eapd
