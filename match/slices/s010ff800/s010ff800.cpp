// Same shape as the 2-arg forward thunks; Havok module row (/vc71).
// Flags: /vc71 /O2 /MD /Gy /TP

// @ 0x010ff800
void __cdecl Fun_0110fdd0(int a, int b);             // 0x110fdd0 (__cdecl, 2 args)

void __cdecl FUN_010ff800(int a, int b, int c)
{
    Fun_0110fdd0(b + 0xc, c);
}
