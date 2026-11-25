extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_0147b7ec[];
extern "C" unsigned char g_0147b810[];
extern "C" unsigned char g_0169e5b8[];
extern "C" void __cdecl FUN_00f47380(...);

extern "C" int __fastcall FUN_00d536d0(char* self, int a_edx_dummy, unsigned char a_4)
{
    *(unsigned int*)(((unsigned int)self)) = ((unsigned int)g_0147b810);
    *(unsigned int*)(((unsigned int)self) + 8) = ((unsigned int)g_0147b7ec);
    *(unsigned int*)g_0169e5b8 = 0;
    if (((*(unsigned int*)(((unsigned int)self) + 32) & *(unsigned int*)(((unsigned int)self) + 32))) == 0) goto L_00d53700;
    if (((int)(*(unsigned int*)(*(unsigned int*)(((unsigned int)self) + 32) - 4)) == (int)(0))) goto L_00d53700;
    FUN_00f47380(*(unsigned int*)(((unsigned int)self) + 32));
L_00d53700:;
    *(unsigned int*)(((unsigned int)self) + 8) = ((unsigned int)g_013eb938);
    *(unsigned int*)(((unsigned int)self)) = ((unsigned int)g_013ec458);
    if (((a_4 & 1)) == 0) goto L_00d5371d;
    FUN_00f47380(((unsigned int)self));
L_00d5371d:;
    return ((unsigned int)self);
}
