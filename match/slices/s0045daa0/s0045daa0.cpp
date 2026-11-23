// Same shape as s0041d490's Unchecked_idl0 (0x0041daf0); the callee here is 0x0045eac0.
// Flags: /Od /Ob1 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

// @ 0x0045daa0
void __cdecl ExtCopy_0045eac0(int a, int b, int c);   // 0x0045eac0

int __cdecl FUN_0045daa0(int a, int b, int c)
{
    ExtCopy_0045eac0(a, b, c);
    return a;
}
