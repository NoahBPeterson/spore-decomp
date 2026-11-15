// src/game/SPAudio/eapdinputobject.cpp -- migrated from slice(s) s00a62ec0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdinputobject.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a62ec0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct PgSymbol {              // t_symbol: by-value pair (hash, name pointer)
    uint32_t    mHash;         // +0x00
    const char* mpName;        // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct XInput {
    uint32_t    mGobj[10];     // +0x00  t_gobj/t_text header
    void*       mpOutlet;      // +0x28  outlet_new result
    void*       mpP1;          // +0x2c
    void*       mpP2;          // +0x30
    void*       mpP3;          // +0x34
    uint8_t     mbPaused;      // +0x38
    void*       mpIface;       // +0x3c  instance interface (vtbl +0x1c = Notify)
};

// The instance interfaces the creators get back are plain objects: GObj_Attach
// is the first virtual (vtable +0x18), GObj_Notify the second (vtable +0x1c).
struct XInputIface {
    virtual void           v00();
    virtual void           v04();
    virtual void           v08();
    virtual void           v0c();
    virtual void           v10();
    virtual void           v14();
    virtual bool __thiscall attach(XInput* x);       // vtable +0x18
    virtual void __thiscall bang(XInput* x);         // vtable +0x1c
};

typedef void* __stdcall XInputNewReg(void* iface, void* a, void* b);
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class* gpInputClass;        // 0x0167585c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gSymbolSymbol;       // 0x01675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gBangSymbol;         // 0x016758b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gFloatSymbol;        // 0x016758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gBangSym2;           // 0x016758b8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gFloatSym2;          // 0x016758c8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern PgSymbol gSymbolSym2;         // 0x01675898
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol* gensym(PgSymbol* out, const char* s);                       // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  class_new7(PgSymbol name, int size, void* freemethod, void* newmethod,
                     int a1, int a2, int a3);                         // 0x00a48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool      class_addcreator(void* fn, PgSymbol name, int mkArg, int a); // 0x00a48e00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
bool      class_addmethod1(t_class* c, void* fn, PgSymbol name, int a1, int a2); // 0x00a48a80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     pd_new(t_class* c);                                        // 0x00a49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      pd_free(void* x);                                          // 0x00a493d0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     outlet_new(void* owner, PgSymbol s, PgSymbol s2);          // 0x00a49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     outlet_new0(void* owner);                                  // 0x00a49d30, both symbols zero
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     canvas_getcurrentinstance();                               // 0x00a4a450
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     InputCreate(int kind, PgSymbol sym, PgSymbol sym2,
                      void* a, void* b);                             // 0x00a67cf0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     InstanceCreate(void* inst, PgSymbol sym, PgSymbol sym2, int kind,
                         void* a);                                  // 0x00ff5b80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
// The helper is reached through the XInputNewReg shape (a in edx, b on the
// stack) that class_addcreator keeps for these creators.
void* __fastcall x_input_new_reg(void* iface, void* a, void* b);      // 0x00a62ec0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  input_bang(XInput* x);                                         // 0x00a62f30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* input_new_float_local(void* a, void* b);                       // 0x00a62f40
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* input_new_symbol(void* a, void* b);                            // 0x00a62f80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* input_new_bang_local(void* a, void* b);                        // 0x00a62fc0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* input_new_globalfloat(void* a, void* b);                       // 0x00a63000
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* input_new_globalsymbol(void* a, void* b);                      // 0x00a63030
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* input_new_globalevent(void* a, void* b);                       // 0x00a63060
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  pause_float(XInput* x, float f);                               // 0x00a63090
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_class*  gpInputClass;         // 0x0167585c
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gSymbolSymbol;        // 0x01675894
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gBangSymbol;          // 0x016758b4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gFloatSymbol;         // 0x016758c4
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gBangSym2;            // 0x016758b8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gFloatSym2;           // 0x016758c8
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
PgSymbol  gSymbolSym2;          // 0x01675898
}
}
}
// ---- items of slice s00a62ec0 end

// @ 0x00a62ec0
namespace EA { namespace Audio { namespace Eapd {
// Arguments come from the caller's stack slots in reverse: a is [esp+8],
// b is [esp+0xc].
void* __fastcall x_input_new_reg(void* iface, void* a, void* b)
{
    XInput* x = (XInput*)pd_new(gpInputClass);
    PgSymbol sym;

    if (x) {
        sym.mHash  = 0;
        sym.mpName = 0;
        x->mpOutlet = outlet_new(x, sym, sym);
        x->mpP1 = a;
        x->mpP2 = b;
        x->mpP3 = iface;
        x->mbPaused = 0;
        x->mpIface = iface;
        if (!((XInputIface*)iface)->attach(x)) {
            pd_free(x);
            return 0;
        }
    }
    return x;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a62f80
namespace EA { namespace Audio { namespace Eapd {
void input_bang(XInput* x)
{
    ((void (__thiscall*)(void*, XInput*))(*(void***)x->mpIface)[7])(x->mpIface, x);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a62f80
namespace EA { namespace Audio { namespace Eapd {
void* input_new_symbol(void* a, void* b)
{
    void* inst  = canvas_getcurrentinstance();
    void* iface = InstanceCreate(inst, gSymbolSymbol, gSymbolSym2, 1, a);
    return x_input_new_reg(iface, a, b);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a62fc0
namespace EA { namespace Audio { namespace Eapd {
void* input_new_bang_local(void* a, void* b)
{
    void* inst  = canvas_getcurrentinstance();
    void* iface = InstanceCreate(inst, gBangSymbol, gBangSym2, 2, a);
    return x_input_new_reg(iface, a, b);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63000
namespace EA { namespace Audio { namespace Eapd {
void* input_new_globalfloat(void* a, void* b)
{
    void* iface = InputCreate(0, gFloatSymbol, gFloatSym2, a, b);
    return x_input_new_reg(iface, a, b);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63030
namespace EA { namespace Audio { namespace Eapd {
void* input_new_globalsymbol(void* a, void* b)
{
    void* iface = InputCreate(1, gSymbolSymbol, gSymbolSym2, a, b);
    return x_input_new_reg(iface, a, b);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63060
namespace EA { namespace Audio { namespace Eapd {
void* input_new_globalevent(void* a, void* b)
{
    void* iface = InputCreate(2, gBangSymbol, gBangSym2, a, b);
    return x_input_new_reg(iface, a, b);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a63090
namespace EA { namespace Audio { namespace Eapd {
void pause_float(XInput* x, float f)
{
    int b = (f != 0.0f);
    x->mbPaused = (uint8_t)b;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a630c0
namespace EA {
namespace Audio {
namespace Eapd {
bool x_input_setup()
{
    PgSymbol s;
    bool ok;

    gpInputClass = class_new7(*gensym(&s, "input"), 0x44, 0, (void*)input_bang, 8, 9, 0);
    ok = gpInputClass != 0;
    ok &= class_addcreator((void*)input_new_bang_local,     *gensym(&s, "event"), 2, 0);
    ok &= class_addcreator((void*)input_new_float_local,    *gensym(&s, "floatparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_float_local,    *gensym(&s, "fparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_symbol,         *gensym(&s, "symbolparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_symbol,         *gensym(&s, "sparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalevent,    *gensym(&s, "globalevent"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalevent,    *gensym(&s, "gevent"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalfloat,    *gensym(&s, "globalfloatparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalfloat,    *gensym(&s, "gfparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalsymbol,   *gensym(&s, "globalsymbolparam"), 2, 0);
    ok &= class_addcreator((void*)input_new_globalsymbol,   *gensym(&s, "gsparam"), 2, 0);
    ok &= class_addmethod1(gpInputClass, (void*)pause_float, *gensym(&s, "pause"), 1, 0);
    return ok;
}
}
}
}  // namespace EA::Audio::Eapd
