// Slice s0132ff40: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_0168cac4;
extern unsigned int g_0168cac8;

// @ 0x0132ff40
void FUN_0132ff40() { g_0168cac4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0132ff60
void FUN_0132ff60() { g_0168cac8 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
