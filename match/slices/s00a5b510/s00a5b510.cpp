// Slice s00a5b510: EA::Audio::Eapd (EA's embedded Pure Data) - the trigger, spigot,
// gate, switch, moses, until, makefilename, swap and change x_*.c object families.
// (0xa5b510-0xa5c458)
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00a5b510.h"

namespace EA { namespace Audio { namespace Eapd {

// ============================================================ trigger
// trigger_list is 0xa5b330 (out of slice); trigger_symbol forwards one symbol atom
// to it as a 3-element list.
// @ 0x00a5b510
void trigger_symbol(char* x, t_symbol s)
{
    struct { int type; t_symbol sym; } atom;
    atom.type = 2;                    // A_SYMBOL
    atom.sym  = s;
    trigger_list(x, gListSymbol.mHash, gListSender.mHash, 1, &atom);
}

// @ 0x00a5b550
bool trigger_setup(void)
{
    t_symbol s;
    t_symbol* sym;
    bool ok = true;

    sym = gensym(&s, "trigger");
    spTriggerClass = class_new_t2(*sym, (void*)0xa5b190, (void*)0xa5b100, 0x30, 0, 9, 0);
    ok = ok && (spTriggerClass != 0);

    sym = gensym(&s, "t");           // 0x14335f8
    ok = class_addcreator((void*)0xa5b190, *sym, 9, 0) && ok;

    ok = class_addlist(spTriggerClass, (void*)0xa5b330) && ok;
    ok = class_addbang(spTriggerClass, (void*)0xa5b4b0) && ok;
    ok = class_doaddfloat(spTriggerClass, (void*)0xa5b4d0) && ok;
    ok = class_addsymbol(spTriggerClass, (void*)trigger_symbol) && ok;
    ok = class_addanything(spTriggerClass, (void*)0xa5b450) && ok;
    return ok;
}

// ============================================================ spigot
// @ 0x00a5b620
char* spigot_new(float f)
{
    char* x = (char*)pd_new(spSpigotClass);
    if (x != 0) {
        floatinlet_new(x, x + 0x28);
        char* o = (char*)outlet_new(x, gEmptySymbol, *(t_symbol*)&gEmptySymbol /*DAT_016758a0*/);
        setObjP(x, 0x2c, o);
        setObjF(x, 0x28, f);
    }
    return x;
}

// @ 0x00a5b670
void spigot_bang(char* x)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_bang((char*)objP(x, 0x2c));
}

// @ 0x00a5b6a0
void spigot_float(char* x, float f)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_cnt((t_outlet*)objP(x, 0x2c), f);
}

// @ 0x00a5b700
void spigot_symbol(char* x, t_symbol s)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_symbol((char*)objP(x, 0x2c), s);
}

// @ 0x00a5b730
void spigot_list(char* x, t_symbol s, int argc, void* argv)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_list((char*)objP(x, 0x2c), s, argc, argv);
}

// @ 0x00a5b770
void spigot_anything(char* x, t_symbol s, int argc, void* argv)
{
    if (objF(x, 0x28) != 0.0f)
        outlet_anything((char*)objP(x, 0x2c), s, argc, argv);
}

// @ 0x00a5b7b0
bool spigot_setup(void)
{
    t_symbol s;
    t_symbol* sym;
    bool ok = true;

    sym = gensym(&s, "spigot");
    spSpigotClass = class_new_t2(*sym, (void*)spigot_new, 0, 0x30, 0, 5, 0);
    ok = ok && (spSpigotClass != 0);

    ok = class_addbang(spSpigotClass, (void*)spigot_bang) && ok;
    ok = class_doaddfloat(spSpigotClass, (void*)spigot_float) && ok;
    ok = class_addsymbol(spSpigotClass, (void*)spigot_symbol) && ok;
    ok = class_addlist(spSpigotClass, (void*)spigot_list) && ok;
    ok = class_addanything(spSpigotClass, (void*)spigot_anything) && ok;
    return ok;
}

// ============================================================ gate
// @ 0x00a5b850
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
            void* o = outlet_new(x, gEmptySymbol, *(t_symbol*)&gEmptySymbol /*DAT_016758a0*/);
            ((void**)objP(x, 0x28))[i] = o;
        }
    }
    return x;
}

// @ 0x00a5b920
void gate_free(char* x)
{
    if (objP(x, 0x28) != 0)
        freebytes(objP(x, 0x28), objI(x, 0x2c) * 4);
}

// @ 0x00a5b940
void gate_bang(char* x)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_bang((char*)((void**)objP(x, 0x28))[i - 1]);
}

// @ 0x00a5b970
void gate_float(char* x, float f)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_cnt((t_outlet*)((void**)objP(x, 0x28))[i - 1], f);
}

// @ 0x00a5b9e0
void gate_symbol(char* x, t_symbol s)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_symbol((char*)((void**)objP(x, 0x28))[i - 1], s);
}

// @ 0x00a5ba20
void gate_list(char* x, t_symbol s, int argc, void* argv)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_list((char*)((void**)objP(x, 0x28))[i - 1], s, argc, argv);
}

// @ 0x00a5ba60
void gate_anything(char* x, t_symbol s, int argc, void* argv)
{
    int i = (int)objF(x, 0x30);
    if (objI(x, 0x2c) <= i)
        i = objI(x, 0x2c);
    if (i > 0)
        outlet_anything((char*)((void**)objP(x, 0x28))[i - 1], s, argc, argv);
}

// @ 0x00a5baa0
bool gate_setup(void)
{
    t_symbol s;
    t_symbol* sym;
    bool ok = true;

    sym = gensym(&s, "gate");
    spGateClass = class_new_t3(*sym, (void*)gate_new, (void*)gate_free, 0x34, 0, 5, 5, 0);
    ok = ok && (spGateClass != 0);

    ok = class_addbang(spGateClass, (void*)gate_bang) && ok;
    ok = class_doaddfloat(spGateClass, (void*)gate_float) && ok;
    ok = class_addsymbol(spGateClass, (void*)gate_symbol) && ok;
    ok = class_addlist(spGateClass, (void*)gate_list) && ok;
    ok = class_addanything(spGateClass, (void*)gate_anything) && ok;
    return ok;
}

// ============================================================ switch
// The switch object owns an array of embedded spigot structs (0x30 bytes each);
// each shares this object's outlet and the spigot class pointer.
// @ 0x00a5bb50
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
        void* o = outlet_new(x, gEmptySymbol, *(t_symbol*)&gEmptySymbol /*DAT_016758a0*/);
        for (int i = 0; i < objI(x, 0x2c); ++i) {
            char* sp = (char*)objP(x, 0x28) + i * 0x30;
            setObjP(sp, 0x00, spSpigotClass);
            setObjP(sp, 0x2c, o);
            setObjF(sp, 0x28, (float)(i == objI(x, 0x30) - 1));
            inlet_new(x, sp, gEmptySymbol, *(t_symbol*)&gEmptySymbol /*DAT_016758a0*/,
                      gEmptySymbol, *(t_symbol*)&gEmptySymbol /*DAT_016758a0*/);
        }
        inlet_new(x, x, gEmptySymbol, *(t_symbol*)&gEmptySymbol /*DAT_016758a0*/,
                  gEmptySymbol, *(t_symbol*)&gEmptySymbol /*DAT_016758a0*/);
    }
    return x;
}

// @ 0x00a5bc70
void switch_free(char* x)
{
    if (objP(x, 0x28) != 0)
        freebytes(objP(x, 0x28), objI(x, 0x2c) * 0x30);
}

// @ 0x00a5bc90
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

// @ 0x00a5bcf0
bool switch_setup(void)
{
    t_symbol s;
    t_symbol* sym;
    bool ok = true;

    sym = gensym(&s, "switch");
    spSwitchClass = class_new_t3(*sym, (void*)switch_new, (void*)switch_free, 0x34, 8, 5, 5, 0);
    ok = ok && (spSwitchClass != 0);

    ok = class_doaddfloat(spSwitchClass, (void*)switch_float) && ok;
    return ok;
}

// ============================================================ moses
// @ 0x00a5bd50
char* moses_new(float f)
{
    char* x = (char*)pd_new(spMosesClass);
    if (x != 0) {
        floatinlet_new(x, x + 0x2c);
        outlet_new(x, gFloatSymbol, *(t_symbol*)&gFloatSymbol /*DAT_016758c8*/);
        char* o = (char*)outlet_new(x, gFloatSymbol, *(t_symbol*)&gFloatSymbol /*DAT_016758c8*/);
        setObjP(x, 0x28, o);
        setObjF(x, 0x2c, f);
    }
    return x;
}

// @ 0x00a5bdb0
void moses_float(char* x, float f)
{
    if (objF(x, 0x2c) <= f)
        outlet_cnt((t_outlet*)objP(x, 0x28), f);
    else
        outlet_cnt((t_outlet*)objP(x, 0xc), f);
}

// @ 0x00a5be50
bool moses_setup(void)
{
    t_symbol s;
    t_symbol* sym;
    bool ok = true;

    sym = gensym(&s, "moses");
    spMosesClass = class_new_t2(*sym, (void*)moses_new, 0, 0x30, 0, 5, 0);
    ok = ok && (spMosesClass != 0);

    ok = class_doaddfloat(spMosesClass, (void*)moses_float) && ok;
    return ok;
}

// ============================================================ until
// @ 0x00a5bf20
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

// @ 0x00a5bf60
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

// @ 0x00a5bfa0
void until_bang2(char* x)
{
    setObjI(x, 0x28, 0);
}

// @ 0x00a5bfb0
bool until_setup(void)
{
    t_symbol s;
    t_symbol* sym;
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

// ============================================================ makefilename
// @ 0x00a5c040
char* makefilename_new(t_symbol s, int hasFormat)
{
    char* x = (char*)pd_new(spMakefilenameClass);
    if (x != 0) {
        if (hasFormat == 0) {
            t_symbol tmp;
            t_symbol* p = gensym(&tmp, "file.%d");
            s = *p;
        }
        outlet_new(x, gSymbolSymbol, *(t_symbol*)&gSymbolSymbol /*DAT_01675898*/);
        *(t_symbol*)(x + 0x28) = s;
    }
    return x;
}

// @ 0x00a5c0b0
void makefilename_float(char* x, float f)
{
    char buf[1000];
    espd_sprintf(buf, (const char*)objP(x, 0x2c), (int)f);
    t_symbol tmp;
    t_symbol* p = gensym(&tmp, buf);
    outlet_symbol((char*)objP(x, 0xc), *p);
}

// @ 0x00a5c100
void makefilename_symbol(char* x, t_symbol s)
{
    char buf[1000];
    espd_sprintf(buf, (const char*)objP(x, 0x2c), s.mpName);
    t_symbol tmp;
    t_symbol* p = gensym(&tmp, buf);
    outlet_symbol((char*)objP(x, 0xc), *p);
}

// @ 0x00a5c150
bool makefilename_setup(void)
{
    t_symbol s;
    t_symbol* sym;
    bool ok = true;

    sym = gensym(&s, "makefilename");
    spMakefilenameClass = class_new_t2(*sym, (void*)makefilename_new, 0, 0x30, 0, 6, 0);
    ok = ok && (spMakefilenameClass != 0);

    ok = class_doaddfloat(spMakefilenameClass, (void*)makefilename_float) && ok;
    ok = class_addsymbol(spMakefilenameClass, (void*)makefilename_symbol) && ok;

    sym = gensym(&s, "set");           // 0x13f2ce4
    ok = class_addmethod2(spMakefilenameClass, (void*)0xa57730, *sym, 2, 0) && ok;
    return ok;
}

// ============================================================ swap
// @ 0x00a5c1f0
char* swap_new(float f)
{
    char* x = (char*)pd_new(spSwapClass);
    if (x != 0) {
        setObjF(x, 0x30, f);
        setObjF(x, 0x2c, 0.0f);
        outlet_new(x, gFloatSymbol, *(t_symbol*)&gFloatSymbol /*DAT_016758c8*/);
        char* o = (char*)outlet_new(x, gFloatSymbol, *(t_symbol*)&gFloatSymbol /*DAT_016758c8*/);
        setObjP(x, 0x28, o);
        floatinlet_new(x, x + 0x30);
    }
    return x;
}

// @ 0x00a5c260
void swap_bang(char* x)
{
    outlet_cnt((t_outlet*)objP(x, 0x28), objF(x, 0x2c));
    outlet_cnt((t_outlet*)objP(x, 0xc), objF(x, 0x30));
}

// @ 0x00a5c300
void swap_float(char* x, float f)
{
    setObjF(x, 0x2c, f);
    swap_bang(x);
}

// @ 0x00a5c320
bool swap_setup(void)
{
    t_symbol s;
    t_symbol* sym;
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

// ============================================================ change
// @ 0x00a5c3c0
char* change_new(float f)
{
    char* x = (char*)pd_new(spChangeClass);
    if (x != 0) {
        setObjF(x, 0x28, f);
        outlet_new(x, gFloatSymbol, *(t_symbol*)&gFloatSymbol /*DAT_016758c8*/);
    }
    return x;
}

// @ 0x00a5c400
void change_float(char* x, float f)
{
    if (999 < gOutletCount + 1)
        return;
    outlet_cnt((t_outlet*)objP(x, 0xc), objF(x, 0x28));
}

} } }  // namespace EA::Audio::Eapd
