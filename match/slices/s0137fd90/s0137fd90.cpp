// Slice s0137fd90: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_016b4548;
extern unsigned int g_016b454c;

// @ 0x0137fd90
void FUN_0137fd90() { g_016b4548 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0137fdb0
void FUN_0137fdb0() { g_016b454c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
