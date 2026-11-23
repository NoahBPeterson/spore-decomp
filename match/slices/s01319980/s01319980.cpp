// Slice s01319980: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_0167c2e8;
extern unsigned int g_0167c2ec;

// @ 0x01319980
void FUN_01319980() { g_0167c2e8 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x013199a0
void FUN_013199a0() { g_0167c2ec = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
