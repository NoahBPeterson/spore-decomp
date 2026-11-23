// Slice s0137ed20: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_016b3c84;

// @ 0x0137ed20
void FUN_0137ed20() { g_016b3c84 = FUN_00932e80("electric_recharge_vs_small_count", 0x811c9dc5, 1); }
