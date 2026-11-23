// Slice s012e3f70: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_01633c90;

// @ 0x012e3f70
void FUN_012e3f70() { g_01633c90 = FUN_00932e80("ExpBasisTable", 0x811c9dc5, 1); }
