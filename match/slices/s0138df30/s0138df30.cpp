// Slice s0138df30: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_016c882c;
extern unsigned int g_016c8830;

// @ 0x0138df30
void FUN_0138df30() { g_016c882c = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0138df50
void FUN_0138df50() { g_016c8830 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
