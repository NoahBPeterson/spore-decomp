// Slice s01357980: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_0169a0f8;
extern unsigned int g_0169a0fc;

// @ 0x01357980
void FUN_01357980() { g_0169a0f8 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x013579a0
void FUN_013579a0() { g_0169a0fc = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
