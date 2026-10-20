// Slice s00a5b510: EA::Audio::Eapd (EA's embedded Pure Data) - the trigger, spigot,
// gate, switch, moses, until, makefilename, swap and change x_*.c object families.
// (0xa5b510-0xa5c458)
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;
typedef t_class* t_pd;

// t_symbol is passed by value (hash, name); symbols compare by their first word only.
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};

struct t_object;
struct t_inlet;
struct t_outlet;

struct t_outconnect {         // 8
    t_outconnect* oc_next;    // +0
    t_outlet*     oc_to;      // +4
};

struct t_outlet {             // 0x1c
    t_object*     o_owner;        // +0x00
    t_outlet*     o_next;         // +0x04
    t_outconnect* o_connections;  // +0x08
    t_symbol      o_symfrom;      // +0x0c
    t_symbol      o_symto;        // +0x14
};

// ---------------------------------------------------------------- globals
extern int gOutletCount;                    // 0x167545c
extern t_symbol gEmptySymbol;               // 0x167589c
extern t_symbol gFloatSymbol;               // 0x16758c4
extern t_symbol gSymbolSymbol;              // 0x1675894
extern t_symbol gListSymbol;                // 0x16758ac
extern t_symbol gListSender;                // 0x16758b0
extern t_class* spTriggerClass;             // 0x1675638
extern t_class* spSpigotClass;              // 0x1675670
extern t_class* spGateClass;                // 0x167567c
extern t_class* spSwitchClass;              // 0x1675658
extern t_class* spMosesClass;               // 0x167564c
extern t_class* spUntilClass;               // 0x1675644
extern t_class* spMakefilenameClass;        // 0x1675628
extern t_class* spSwapClass;                // 0x1675674
extern t_class* spChangeClass;              // 0x1675650

// --------------------------------------------------------------- callees
t_symbol* gensym(t_symbol* out, const char* s);                          // 0xa675f0
t_class*  class_new_t1(t_symbol name, void* newmethod, void* freemethod,
                       int size, int flags, int a1);                     // 0xa48e50
t_class*  class_new_t2(t_symbol name, void* newmethod, void* freemethod,
                       int size, int flags, int a1, int a2);             // 0xa48ea0
t_class*  class_new_t3(t_symbol name, void* newmethod, void* freemethod,
                       int size, int flags, int a1, int a2, int a3);     // 0xa48f00
bool class_addcreator(void* newmethod, t_symbol name, int a1, int a2);   // 0xa48e00
bool class_doaddfloat(t_class* c, void* fn);                             // 0xa47f30
bool class_addbang(t_class* c, void* fn);                                // 0xa47f10
bool class_addsymbol(t_class* c, void* fn);                              // 0xa47f50
bool class_addlist(t_class* c, void* fn);                                // 0xa47f70
bool class_addanything(t_class* c, void* fn);                            // 0xa47f90
bool class_addmethod1(t_class* c, void* fn, t_symbol name, int a1);      // 0xa48a30
bool class_addmethod2(t_class* c, void* fn, t_symbol name, int a1, int a2);  // 0xa48a80
void* pd_new(t_class* c);                                                // 0xa49390
void  pd_free(void* x);                                                  // 0xa493d0
void  outlet_float(char* to, float f);                                   // 0xa49570
void  outlet_bang(char* to);                                             // 0xa49da0
void  outlet_symbol(char* to, t_symbol s);                               // 0xa49df0
void  trigger_list(char* x, unsigned int s, unsigned int a, int argc, void* argv); // 0xa5b330int   espd_sprintf(char*, const char*, ...);                             // msvcr90!sprintf
void  outlet_list(char* to, t_symbol s, int argc, void* argv);           // 0xa49e40
void  outlet_anything(char* to, t_symbol s, int argc, void* argv);       // 0xa49eb0
void* floatinlet_new(void* owner, void* dest);                           // 0xa49a00
void* outlet_new(void* owner, t_symbol a, t_symbol b);                   // 0xa49d30
void* inlet_new(void* owner, void* dest, t_symbol a, t_symbol b,
                t_symbol c, t_symbol d);                                 // 0xa49740
void* getbytes(int n, const char* tag);                                  // 0xa49610
void  freebytes(void* p, int n);                                         // 0xa49650
int   espd_sprintf(char*, const char*, ...);                             // msvcr90!sprintf

// ------------------------------------------------------- object accessors
// x points at the t_object header (0x2c bytes) followed by the object fields.
inline float  objF(char* x, int off)  { return *(float*)(x + off); }
inline void   setObjF(char* x, int off, float v) { *(float*)(x + off) = v; }
inline int    objI(char* x, int off)  { return *(int*)(x + off); }
inline void   setObjI(char* x, int off, int v) { *(int*)(x + off) = v; }
inline void*  objP(char* x, int off)  { return *(void**)(x + off); }
inline void   setObjP(char* x, int off, void* v) { *(void**)(x + off) = v; }

// Sends `v` out of the outlet list `lst`, guarded by the outlet-nesting counter
// (PD's outlet_float wrapper: bail out past 1000 nested sends).
inline void outlet_cnt(t_outlet* lst, float v)
{
    if (++gOutletCount < 1000) {
        t_outconnect* oc;
        for (oc = lst->o_connections; oc; oc = oc->oc_next)
            outlet_float((char*)oc->oc_to, v);
    }
    gOutletCount--;
}

} } }  // namespace EA::Audio::Eapd
