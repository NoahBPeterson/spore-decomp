// Slice s00a569c0 - EA::Audio::Eapd (Pure Data port): x_arithmetic.c setup.
// binop1 (+ - * / pow max min), binop2 (== != > < >= <=), binop3 (& && | || << >> % mod div)
// and the math objects (sin cos tan atan atan2 sqrt log exp abs), then clip_setup().
#include "types.h"

namespace EA { namespace Audio { namespace Eapd {

struct t_class;

// t_symbol is a by-value pair: hash, name pointer.
struct t_symbol {
    uint32_t    mHash;    // +0
    const char* mpName;   // +4
};

// gensym returns its symbol by value through a hidden pointer (non-POD).
struct t_symret : t_symbol {
    t_symret() {}
    t_symret(const t_symret& o) { mHash = o.mHash; mpName = o.mpName; }
};

enum { A_NULL = 0, A_DEFFLOAT = 5 };

t_symret  gensym(const char* s);                                                        // 0xa675f0
t_class*  class_new(t_symbol name, void* newmethod, void* freemethod, int size,
                    int flags, int arg1);                                                // 0xa48e50
t_class*  class_new(t_symbol name, void* newmethod, void* freemethod, int size,
                    int flags, int arg1, int arg2);                                      // 0xa48ea0
bool      class_addbang(t_class* c, void* fn);                                           // 0xa47f10
bool      class_doaddfloat(t_class* c, void* fn);                                        // 0xa47f30
void      class_sethelpsymbol(t_class* c, t_symbol s);                                   // 0xa47fc0
bool      clip_setup();                                                                  // 0xa56950

// t_binop (0x30 bytes) methods
void* binop1_plus_new(float f);      void binop1_plus_bang(void* x);   void binop1_plus_float(void* x, float f);
void* binop1_minus_new(float f);     void binop1_minus_bang(void* x);  void binop1_minus_float(void* x, float f);
void* binop1_times_new(float f);     void binop1_times_bang(void* x);  void binop1_times_float(void* x, float f);
void* binop1_div_new(float f);       void binop1_div_bang(void* x);    void binop1_div_float(void* x, float f);
void* binop1_pow_new(float f);       void binop1_pow_bang(void* x);    void binop1_pow_float(void* x, float f);
void* binop1_max_new(float f);       void binop1_max_bang(void* x);    void binop1_max_float(void* x, float f);
void* binop1_min_new(float f);       void binop1_min_bang(void* x);    void binop1_min_float(void* x, float f);
void* binop2_ee_new(float f);        void binop2_ee_bang(void* x);     void binop2_ee_float(void* x, float f);
void* binop2_ne_new(float f);        void binop2_ne_bang(void* x);     void binop2_ne_float(void* x, float f);
void* binop2_gt_new(float f);        void binop2_gt_bang(void* x);     void binop2_gt_float(void* x, float f);
void* binop2_lt_new(float f);        void binop2_lt_bang(void* x);     void binop2_lt_float(void* x, float f);
void* binop2_ge_new(float f);        void binop2_ge_bang(void* x);     void binop2_ge_float(void* x, float f);
void* binop2_le_new(float f);        void binop2_le_bang(void* x);     void binop2_le_float(void* x, float f);
void* binop3_ba_new(float f);        void binop3_ba_bang(void* x);     void binop3_ba_float(void* x, float f);
void* binop3_la_new(float f);        void binop3_la_bang(void* x);     void binop3_la_float(void* x, float f);
void* binop3_bo_new(float f);        void binop3_bo_bang(void* x);     void binop3_bo_float(void* x, float f);
void* binop3_lo_new(float f);        void binop3_lo_bang(void* x);     void binop3_lo_float(void* x, float f);
void* binop3_ls_new(float f);        void binop3_ls_bang(void* x);     void binop3_ls_float(void* x, float f);
void* binop3_rs_new(float f);        void binop3_rs_bang(void* x);     void binop3_rs_float(void* x, float f);
void* binop3_pc_new(float f);        void binop3_pc_bang(void* x);     void binop3_pc_float(void* x, float f);
void* binop3_mod_new(float f);       void binop3_mod_bang(void* x);    void binop3_mod_float(void* x, float f);
void* binop3_div_new(float f);       void binop3_div_bang(void* x);    void binop3_div_float(void* x, float f);
// math objects (t_object 0x28 bytes; atan2 0x2c)
void* sin_new();    void sin_float(void* x, float f);
void* cos_new();    void cos_float(void* x, float f);
void* tan_new();    void tan_float(void* x, float f);
void* atan_new();   void atan_float(void* x, float f);
void* atan2_new();  void atan2_float(void* x, float f);
void* sqrt_new();   void sqrt_float(void* x, float f);
void* log_new();    void log_float(void* x, float f);
void* exp_new();    void exp_float(void* x, float f);
void* abs_new();    void abs_float(void* x, float f);

t_class* binop1_plus_class;    // 0x16755ec
t_class* binop1_minus_class;   // 0x16755f0
t_class* binop1_times_class;   // 0x1675574
t_class* binop1_div_class;     // 0x1675590
t_class* binop1_pow_class;     // 0x167558c
t_class* binop1_max_class;     // 0x16755b8
t_class* binop1_min_class;     // 0x16755a8
t_class* binop2_ee_class;      // 0x16755b0
t_class* binop2_ne_class;      // 0x1675584
t_class* binop2_gt_class;      // 0x16755c8
t_class* binop2_lt_class;      // 0x1675594
t_class* binop2_ge_class;      // 0x16755d0
t_class* binop2_le_class;      // 0x1675580
t_class* binop3_ba_class;      // 0x16755e8
t_class* binop3_la_class;      // 0x16755e4
t_class* binop3_bo_class;      // 0x16755c0
t_class* binop3_lo_class;      // 0x1675598
t_class* binop3_ls_class;      // 0x16755b4
t_class* binop3_rs_class;      // 0x16755d8
t_class* binop3_pc_class;      // 0x16755dc
t_class* binop3_mod_class;     // 0x16755bc
t_class* binop3_div_class;     // 0x16755a0
t_class* sin_class;            // 0x16755d4
t_class* cos_class;            // 0x16755a4
t_class* tan_class;            // 0x16755cc
t_class* atan_class;           // 0x167559c
t_class* atan2_class;          // 0x1675588
t_class* sqrt_class;           // 0x16755e0
t_class* log_class;            // 0x16755c4
t_class* exp_class;            // 0x16755ac
t_class* abs_class;            // 0x167557c

#define BINOP(cls, name, pfx, help)                                                          \
    cls = class_new(gensym(name), (void*)pfx##_new, 0, 0x30, 0, A_DEFFLOAT, A_NULL); \
    ok &= (cls != 0);                                                                        \
    ok &= class_addbang(cls, (void*)pfx##_bang);                                             \
    ok &= class_doaddfloat(cls, (void*)pfx##_float);                                         \
    class_sethelpsymbol(cls, help);

#define MATHOP(cls, name, pfx, size)                                                         \
    cls = class_new(gensym(name), (void*)pfx##_new, 0, size, 0, A_NULL);              \
    ok &= (cls != 0);                                                                        \
    ok &= class_doaddfloat(cls, (void*)pfx##_float);                                         \
    class_sethelpsymbol(cls, math_sym);

// @ 0xa569c0
bool x_arithmetic_setup()
{
    t_symret binop1_sym = gensym("operators");
    t_symret binop23_sym = gensym("otherbinops");
    t_symret math_sym = gensym("math");
    bool ok = true;

    BINOP(binop1_plus_class,  "+",   binop1_plus,  binop1_sym)
    BINOP(binop1_minus_class, "-",   binop1_minus, binop1_sym)
    BINOP(binop1_times_class, "*",   binop1_times, binop1_sym)
    BINOP(binop1_div_class,   "/",   binop1_div,   binop1_sym)
    BINOP(binop1_pow_class,   "pow", binop1_pow,   binop1_sym)
    BINOP(binop1_max_class,   "max", binop1_max,   binop1_sym)
    BINOP(binop1_min_class,   "min", binop1_min,   binop1_sym)

    BINOP(binop2_ee_class, "==", binop2_ee, binop23_sym)
    BINOP(binop2_ne_class, "!=", binop2_ne, binop23_sym)
    BINOP(binop2_gt_class, ">",  binop2_gt, binop23_sym)
    BINOP(binop2_lt_class, "<",  binop2_lt, binop23_sym)
    BINOP(binop2_ge_class, ">=", binop2_ge, binop23_sym)
    BINOP(binop2_le_class, "<=", binop2_le, binop23_sym)

    BINOP(binop3_ba_class,  "&",   binop3_ba,  binop23_sym)
    BINOP(binop3_la_class,  "&&",  binop3_la,  binop23_sym)
    BINOP(binop3_bo_class,  "|",   binop3_bo,  binop23_sym)
    BINOP(binop3_lo_class,  "||",  binop3_lo,  binop23_sym)
    BINOP(binop3_ls_class,  "<<",  binop3_ls,  binop23_sym)
    BINOP(binop3_rs_class,  ">>",  binop3_rs,  binop23_sym)
    BINOP(binop3_pc_class,  "%",   binop3_pc,  binop23_sym)
    BINOP(binop3_mod_class, "mod", binop3_mod, binop23_sym)
    BINOP(binop3_div_class, "div", binop3_div, binop23_sym)

    MATHOP(sin_class,   "sin",   sin,   0x28)
    MATHOP(cos_class,   "cos",   cos,   0x28)
    MATHOP(tan_class,   "tan",   tan,   0x28)
    MATHOP(atan_class,  "atan",  atan,  0x28)
    MATHOP(atan2_class, "atan2", atan2, 0x2c)
    MATHOP(sqrt_class,  "sqrt",  sqrt,  0x28)
    MATHOP(log_class,   "log",   log,   0x28)
    MATHOP(exp_class,   "exp",   exp,   0x28)
    MATHOP(abs_class,   "abs",   abs,   0x28)

    ok &= clip_setup();
    return ok;
}

}}}
