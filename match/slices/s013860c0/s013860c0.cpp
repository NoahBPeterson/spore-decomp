// Slice s013860c0: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_016c6ab4;
extern unsigned int g_016c6ab8;

// @ 0x013860c0
void FUN_013860c0() { g_016c6ab4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x013860e0
void FUN_013860e0() { g_016c6ab8 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
