// Slice s00a4f1e0: EA::Audio::Eapd::gatom_bang (0x00a4fdb0, 221 bytes). __cdecl, one t_gatom* arg, plain ret.
// Callees (all cdecl, caller pops): outlet_float(to, f) 0x00a49570, outlet_symbol(outlet, sym) 0x00a49df0,
// pd_send_float(a, b, f) 0x00a67230, pd_send_symbol(a, b, sym) 0x00a67250.
// Offsets are from the disassembly: +0x0c outlet, +0x28 a_type (1 float, 2 symbol), +0x2c value (float or
// t_symbol), +0x4c / +0x54 symbol pointers, +0x88 / +0x8c send target words.
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_symbol {               // by-value pair: hash at +0, name pointer at +4
    uint32_t    mHash;
    const char* mpName;
};

struct t_connection {
    t_connection* oc_next;      // +0
    void*         oc_to;        // +4: inlet the connection feeds
};

struct t_outlet {
    uint32_t       pad00[2];
    t_connection*  o_connections;   // +0x08
};

struct t_gatom {
    uint32_t  pad00[3];         // te_g, te_binbuf
    t_outlet* a_outlet;         // +0x0c (te_outlet)
    uint32_t  pad10[6];         // +0x10 .. +0x27
    int       a_type;           // +0x28: 1 = float atom, 2 = symbol atom
    union {                     // +0x2c
        float    a_float;
        t_symbol a_symbol;      // +0x2c hash, +0x30 name
    };
    uint8_t   pad34[0x4c - 0x34];
    t_symbol* a_symfrom;        // +0x4c
    uint32_t  pad50;            // +0x50
    t_symbol* a_symto;          // +0x54
    uint8_t   pad58[0x88 - 0x58];
    uint32_t  a_sendA;          // +0x88
    uint32_t  a_sendB;          // +0x8c
};

// Reentrancy depth of gatom_bang's outlet loop (global at 0x0167545c).
extern int gBangDepth;
// The empty symbol (global at 0x0167589c, compared by value).
extern t_symbol* gEmptySymbol;

void outlet_float(void* to, float f);                              // 0x00a49570
void outlet_symbol(t_outlet* o, t_symbol s);                       // 0x00a49df0
void pd_send_float(uint32_t a, uint32_t b, float f);               // 0x00a67230
void pd_send_symbol(uint32_t a, uint32_t b, t_symbol s);           // 0x00a67250

// @ 0x00a4fdb0
void gatom_bang(t_gatom* x)
{
    if (x->a_type == 1) {
        t_outlet* o = x->a_outlet;
        if (o) {
            float f = x->a_float;
            if (++gBangDepth < 1000) {
                for (t_connection* c = o->o_connections; c; c = c->oc_next)
                    outlet_float(c->oc_to, f);
            }
            --gBangDepth;
        }
        if (gEmptySymbol != x->a_symto && x->a_symto != x->a_symfrom)
            pd_send_float(x->a_sendA, x->a_sendB, x->a_float);
    } else if (x->a_type == 2) {
        if (x->a_outlet)
            outlet_symbol(x->a_outlet, x->a_symbol);
        if (gEmptySymbol != x->a_symto && x->a_symto != x->a_symfrom)
            pd_send_symbol(x->a_sendA, x->a_sendB, x->a_symbol);
    }
}

}}}
