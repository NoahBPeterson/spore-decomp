// Slice s01277b20: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_15e4fbc;
extern unsigned int g_15e4f54;

// @ 0x01277b20
void FUN_01277b20() { g_15e4fbc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01277b40
void FUN_01277b40() { g_15e4f54 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
