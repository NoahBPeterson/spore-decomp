// Slice s0136bb60: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_016a0ca0;
extern unsigned int g_016a0ca4;

// @ 0x0136bb60
void FUN_0136bb60() { g_016a0ca0 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0136bb80
void FUN_0136bb80() { g_016a0ca4 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
