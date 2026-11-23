// Slice s0131d170: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_0167e978;
extern unsigned int g_0167e97c;

// @ 0x0131d170
void FUN_0131d170() { g_0167e978 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0131d190
void FUN_0131d190() { g_0167e97c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
