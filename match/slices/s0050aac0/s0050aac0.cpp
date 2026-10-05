// w1g1 slice s0050aac0 -- single 4542-byte /Od function.
//
// 0x50aac0 is a very large per-face processing routine (a ~2.3 KB stack frame:
// locals down to [ebp-0x918], dozens of Vector3 temporaries and inner loops).
// Far beyond the per-function budget, so this is a PARTIAL signature skeleton.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

// @ 0x0050aac0  (PARTIAL skeleton)
void __thiscall ProcessFace(int self, float param)
{
    (void)self; (void)param;
}
