// Slice s0136d9c0: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_016a13fc;
extern unsigned int g_016a1400;
extern unsigned int g_016a15ec;
extern unsigned int g_016a15f0;

// @ 0x0136d9c0
void FUN_0136d9c0() { g_016a13fc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0136d9e0
void FUN_0136d9e0() { g_016a1400 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x0136e530
void FUN_0136e530() { g_016a15ec = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x0136e550
void FUN_0136e550() { g_016a15f0 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
