// Slice s00a59690 -- EA::Audio::Eapd (the EA "Pd"-style audio processing descriptor graph).
//
// This range is the Pd-derived class-registration and message-handler layer of EA's Eapd runtime:
// every "setup" function registers a Pd class (class_new/class_addcreator/class_addbang/...), and the
// small leaf functions are the Pd method handlers (bang/float/symbol/list/anything) that forward into
// the outlet_* / pd_send_* / vinlet_* primitives.
//
// Symbols below come from symbols/pdb_names.json (the EA::Audio::Eapd::* names survive in the PDB),
// keyed by retail VA. Globals are referred to by their retail addresses as shown in the function cards.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned int   uintptr_t;
typedef int            int32_t;

// ------------------------------------------------------------------------------------ EAPD primitives
// All of these are real Eapd exports whose names survive in the PDB; declared here with the
// signatures that the callers in this slice actually use.
namespace EA { namespace Audio { namespace Eapd {

// A Pd symbol is a 2-word value {s_name (char*), s_name2/namespace}. gensym fills a caller-provided
// 8-byte buffer and returns a pointer to it.
struct t_symbol { void* s_name; void* s_name2; };

t_symbol* gensym(t_symbol* buf, const char* name);                                  // 0x00a675f0

// class_new / class_addcreator take variable argument counts; the concrete Eapd entry point used
// depends on the arity, so they are declared with the exact number of stack slots the callers use.
void* class_new(void* s_name, void* s_name2, void* nnew,
                void* a, int size, int b, int nargs, int c);                        // 0x00a48ea0 / 0x00a48e50
void* class_addcreator(void* fn, void* s_name, void* s_name2, int nargs, int c);    // 0x00a48db0 / 0x00a48e00
int   class_addbang(void* c, void* fn);                                             // 0x00a47f10
int   class_doaddfloat(void* c, void* fn);                                          // 0x00a47f30
int   class_addsymbol(void* c, void* fn);                                           // 0x00a47f50
int   class_addlist(void* c, void* fn);                                             // 0x00a47f70
int   class_addanything(void* c, void* fn);                                         // 0x00a47f90
int   class_addmethod(void* c, void* fn, void* a, void* b);                         // 0x00a47e70

void* pd_new(void* cls);                                                            // 0x00a49390
void  pd_free(void* obj);                                                           // 0x00a493d0
void* getbytes(int n, const char* tag);                                             // 0x00a49610
bool  pd_bind(void* obj, void* a, void* b);                                         // 0x00a67620

void* outlet_new(void* obj, void* a, void* b);                                      // 0x00a49d30
void  outlet_bang(void* out);                                                       // 0x00a49da0
void  outlet_float(void* out, float f);                                             // 0x00a49570
void  outlet_symbol(void* out, void* a, void* b);                                   // 0x00a49df0
void* floatinlet_new(void* obj, void* p);                                           // 0x00a49a00
void* symbolinlet_new(void* obj, void* p);                                          // 0x00a49ab0

void  pd_send_bang(uint32_t a, uint32_t b);                                         // 0x00a67210
void  pd_send_symbol(uint32_t a, uint32_t b, uint32_t c, uint32_t d);               // 0x00a67250
void  pd_send_float(uint32_t a, uint32_t b, float f);                               // 0x00a67230
void  pd_typedmess_bindings(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t); // 0x00a672b0
void  pd_list_bindings(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t); // 0x00a67280

float atom_getfloat_at(int a, int b, void* atoms);                                  // 0x00a468f0
t_symbol* atom_getsymbol_at(t_symbol* out, int a, int b, void* atoms);              // 0x00a46950

}}} // namespace EA::Audio::Eapd

using EA::Audio::Eapd::t_symbol;

// ------------------------------------------------------------------------- Eapd globals (retail VAs)
// Learned-class handles (sp*Class) and the well-known symbol singletons, all addressed absolutely.
#define g_spCollClass     (*(void**)0x016755f4u)
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

// ------------------------------------------------------------------------------------ Eapd structures
// A Pd object header: 0x00 outlist (the t_outlet list head is at +0x08 of whatever +0x0c points at),
// +0x0c = the primary outlet chain pointer used by the handlers; the object-specific payload begins
// at +0x28.
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

// The two-word payload at +0x28 of a symbol/float/bang object.  Assigning its two members through a
// pointer typed as this struct reproduces the original's sunk second-argument load.
struct PdPayload
{
    uint32_t at28;          // +0x00 (object +0x28)
    uint32_t at2c;          // +0x04 (object +0x2c)
};

// Forward declarations (the setup functions reference handlers defined later in the file).
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

// ===================================================================================== x_coll_setup
// @ 0x00a59690
// The "coll" (collection) class registration of the Eapd runtime. Declared as a plain function
// because it drives ~30 class_* registration calls over the gensym'd symbols.
bool x_coll_setup();

bool x_coll_setup()
{
    t_symbol sym;
    bool ok = true;

    EA::Audio::Eapd::gensym(&sym, "coll");
    g_spCollClass = (void*)((uintptr_t(*)(t_symbol*, void*, void*, int, int, int,
                                          int, int, int, int, int))0x00a48f00)(
        &sym, sym.s_name2, (void*)0x00a58e00, 0, 0x1f0, 0, 0, 9, 0, 0x016755f4, 0);
    (void)ok;
    return ok;
}

// ===================================================================================== coll registration
// @ 0x00a598d0
uint8_t FUN_00a598d0();
uint8_t FUN_00a598d0()
{
    uint8_t a = (uint8_t)x_coll_setup();
    uint8_t b = (uint8_t)((uint8_t(*)(void))0x00a582f0)();
    uint8_t c = (uint8_t)((uint8_t(*)(void))0x00a58ec0)();
    return (uint8_t)(a & 1 & b & c);
}

// ===================================================================================== pdint
// @ 0x00a598f0
void* FUN_00a598f0(float f);
void* FUN_00a598f0(float f)
{
    void* o = EA::Audio::Eapd::pd_new(g_spPdintClass);
    if (o != 0)
    {
        *(float*)((char*)o + 0x28) = f;
        EA::Audio::Eapd::outlet_new(o, g_gFloatSymbol.s_name, g_gFloatSymbol2);
        EA::Audio::Eapd::floatinlet_new(o, (char*)o + 0x28);
    }
    return o;
}

// @ 0x00a59940
void FUN_00a59940(PdObject* o);
void FUN_00a59940(PdObject* o)
{
    float f = *(float*)&o->mAt28;
    int n = g_gOutletCount + 1;
    if (n >= 1000)
        return;
    g_gOutletCount = n;
    for (void* p = *(void**)((char*)o->pOb + 8); p != 0; p = *(void**)p)
        EA::Audio::Eapd::outlet_float(*(void**)((char*)p + 4), (float)(int)f);
    --g_gOutletCount;
}

// @ 0x00a599a0
void FUN_00a599a0(PdObject* o, float v);
void FUN_00a599a0(PdObject* o, float v)
{
    o->mAt28 = *(uint32_t*)&v;
    int n = g_gOutletCount + 1;
    if (n >= 1000)
        return;
    g_gOutletCount = n;
    for (void* p = *(void**)((char*)o->pOb + 8); p != 0; p = *(void**)p)
        EA::Audio::Eapd::outlet_float(*(void**)((char*)p + 4), (float)(int)v);
    --g_gOutletCount;
}

// @ 0x00a59a10
bool pdint_setup();
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

// ===================================================================================== pdfloat
// @ 0x00a59ab0
void* pdfloat_new(float f, ...);
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
void* pdfloat_new2(float f);
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
void FUN_00a59b50(PdObject* o, float v);
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
bool pdfloat_setup();
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

// ===================================================================================== pdsymbol
// @ 0x00a59c50
void* pdsymbol_new(uint32_t a, uint32_t b, uint32_t c);
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
void pdsymbol_symbol(PdObject* o);
void pdsymbol_symbol(PdObject* o)
{
    EA::Audio::Eapd::outlet_symbol(o->pOb, (void*)(uintptr_t)o->mAt28, (void*)(uintptr_t)o->mAt2c);
}

// @ 0x00a59cc0
void pdsymbol_anything(PdObject* o, void* a, void* b);
void pdsymbol_anything(PdObject* o, void* a, void* b)
{
    PdPayload* p = (PdPayload*)((char*)o + 0x28);
    p->at28 = (uint32_t)(uintptr_t)a;
    p->at2c = (uint32_t)(uintptr_t)b;
    EA::Audio::Eapd::outlet_symbol(o->pOb, a, b);
}

// @ 0x00a59cf0
bool pdsymbol_setup();
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

// ===================================================================================== bang
// @ 0x00a59d70
void* bang_new2();
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
void FUN_00a59db0(void* o);
void FUN_00a59db0(void* o)
{
    EA::Audio::Eapd::outlet_bang(*(void**)((char*)o + 0x0c));
}

// @ 0x00a59dc0
bool bang_setup();
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

// ===================================================================================== send
// @ 0x00a59e90
void FUN_00a59e90(PdObject* o);
void FUN_00a59e90(PdObject* o)
{
    EA::Audio::Eapd::pd_send_bang((uint32_t)(uintptr_t)o->mAt28, (uint32_t)(uintptr_t)o->mAt2c);
}

// @ 0x00a59eb0
void send_symbol(PdObject* o, void* a, void* b);
void send_symbol(PdObject* o, void* a, void* b)
{
    EA::Audio::Eapd::pd_send_symbol((uint32_t)(uintptr_t)o->mAt28,
                                    (uint32_t)(uintptr_t)o->mAt2c,
                                    (uint32_t)(uintptr_t)a, (uint32_t)(uintptr_t)b);
}

// @ 0x00a59ed0
void FUN_00a59ed0(PdObject* o, void* a, void* b, void* c, void* d);
void FUN_00a59ed0(PdObject* o, void* a, void* b, void* c, void* d)
{
    EA::Audio::Eapd::pd_typedmess_bindings((uint32_t)(uintptr_t)o->mAt28,
                                           (uint32_t)(uintptr_t)o->mAt2c,
                                           (uint32_t)(uintptr_t)a, (uint32_t)(uintptr_t)b,
                                           (uint32_t)(uintptr_t)c, (uint32_t)(uintptr_t)d);
}

// @ 0x00a59f00
void* FUN_00a59f00(uint32_t a, uint32_t b);
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
bool send_setup();
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

// ===================================================================================== send helpers
// @ 0x00a5a000
void FUN_00a5a000(PdObject* o, float f);
void FUN_00a5a000(PdObject* o, float f)
{
    EA::Audio::Eapd::pd_send_float((uint32_t)(uintptr_t)o->mAt28,
                                   (uint32_t)(uintptr_t)o->mAt2c, f);
}

// @ 0x00a5a020
void FUN_00a5a020(PdObject* o, void* a, void* b, void* c, void* d);
void FUN_00a5a020(PdObject* o, void* a, void* b, void* c, void* d)
{
    EA::Audio::Eapd::pd_list_bindings((uint32_t)(uintptr_t)o->mAt28,
                                      (uint32_t)(uintptr_t)o->mAt2c,
                                      (uint32_t)(uintptr_t)a, (uint32_t)(uintptr_t)b,
                                      (uint32_t)(uintptr_t)c, (uint32_t)(uintptr_t)d);
}

// ===================================================================================== forward
// @ 0x00a5a050
void* forward_new(uint32_t a, uint32_t b);
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
bool forward_setup();
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

// ===================================================================================== receive
// @ 0x00a5a140
void FUN_00a5a140(PdObject* o, void* a, void* b);
void FUN_00a5a140(PdObject* o, void* a, void* b)
{
    EA::Audio::Eapd::outlet_symbol(o->pOb, a, b);
}

// @ 0x00a5a160
void* receive_new(uint32_t a, uint32_t b);
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
bool receive_setup();
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

// ===================================================================================== selector (1 arg)
// @ 0x00a5a280
void FUN_00a5a280(PdObject* o, float v);
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
void sel1_symbol(PdObject* o, int sym, void* b);
void sel1_symbol(PdObject* o, int sym, void* b)
{
    if (*(int*)((char*)o + 0x28) == 2 && sym == *(int*)((char*)o + 0x2c))
    {
        EA::Audio::Eapd::outlet_bang(*(void**)((char*)o + 0x34));
        return;
    }
    EA::Audio::Eapd::outlet_symbol(*(void**)((char*)o + 0x38), (void*)(uintptr_t)sym, b);
}

// ===================================================================================== selector (2 arg)
// @ 0x00a5a330
void sel2_float(PdObject* o, float v);
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
void sel2_symbol(PdObject* o, int sym, void* b);
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

// ===================================================================================== select_new
// @ 0x00a5a410
void* select_new(int argc, void* argv, int mode, int* atoms);
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
