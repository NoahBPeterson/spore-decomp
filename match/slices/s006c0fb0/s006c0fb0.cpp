// @ 0x006c0fb0
// forwards its incoming fastcall arg (ecx) as the first stack argument: the wrapper pushes
// the 1-byte `ret` stub at 0xc2e4e0 as a callback pointer, then 4, 8, and ecx, and calls the
// SEH-wrapped helper at 0x11e0b22 (stdcall: call, no add esp, ret).
extern void __stdcall Callee_11e0b22(void* a, int b, int c, void* d);   // 0x11e0b22
extern void Stub_00c2e4e0();                                           // 0xc2e4e0 (1-byte ret)

void __fastcall FUN_006c0fb0(void* a) { Callee_11e0b22(a, 8, 4, &Stub_00c2e4e0); }
