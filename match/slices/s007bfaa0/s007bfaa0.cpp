// Slice s007bfaa0 — SP::cTestScript::HandleMessage renderer, an empty EH-framed
// stub, and a large capture routine.  /O2 /arch:SSE2 /EHsc.  See partial.txt.
#include "types.h"

// @ 0x007bfaa0  SP::cTestScript::HandleMessage (this + 4 stack args)
void FUN_007bfaa0(void* pThis, void* a, void* b, void* c, void* d)
{ (void)pThis; (void)a; (void)b; (void)c; (void)d; }

// @ 0x007bfeb0  empty EH-framed stub (5 stack args)
void __stdcall FUN_007bfeb0(int a, int b, int c, int d, int e)
{ (void)a; (void)b; (void)c; (void)d; (void)e; }

// @ 0x007bfee0  large capture routine
void FUN_007bfee0(void* a) { (void)a; }
