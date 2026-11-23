// Slice s01364a00: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_0169e2dc;
extern unsigned int g_0169e2e0;

// @ 0x01364a00
void FUN_01364a00() { g_0169e2dc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01364a20
void FUN_01364a20() { g_0169e2e0 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
