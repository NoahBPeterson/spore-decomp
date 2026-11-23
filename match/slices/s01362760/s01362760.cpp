// Slice s01362760: compiler-generated dynamic initializers for setting globals.
// Each one registers a named setting and stores the resulting id:
//     g_<addr> = FUN_00932e80("<name>", 0x811c9dc5, 1);
// 0x811c9dc5 is the FNV-1a offset basis, the last argument the register flag.
// Built /O2 /MD /Gy /EHsc /TP.

unsigned int FUN_00932e80(const char* s, unsigned int seed, int flag);

extern unsigned int g_0169d578;
extern unsigned int g_0169d57c;
extern unsigned int g_0169d5dc;
extern unsigned int g_0169d5e0;

// @ 0x01362760
void FUN_01362760() { g_0169d578 = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01362780
void FUN_01362780() { g_0169d57c = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
// @ 0x01362940
void FUN_01362940() { g_0169d5dc = FUN_00932e80("editor_sym_snap", 0x811c9dc5, 1); }
// @ 0x01362960
void FUN_01362960() { g_0169d5e0 = FUN_00932e80("editor_sym_unsnap", 0x811c9dc5, 1); }
