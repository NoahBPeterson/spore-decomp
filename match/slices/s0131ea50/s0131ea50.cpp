// Slice s0131ea50: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_016870c4;
extern unsigned int g_016870c8;

// @ 0x0131ea50
void FUN_0131ea50() { g_016870c4 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0131ea70
void FUN_0131ea70() { g_016870c8 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
