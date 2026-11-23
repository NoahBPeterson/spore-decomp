// Slice s01335f10: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_0168dc00;
extern unsigned int g_0168dc04;

// @ 0x01335f10
void FUN_01335f10() { g_0168dc00 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01335f30
void FUN_01335f30() { g_0168dc04 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
