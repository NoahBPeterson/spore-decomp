extern "C" unsigned char g_013eb394[];
extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ef094[];
extern "C" void __cdecl FUN_00f47380(...);

extern "C" int __fastcall FUN_007c6370(char* self, int a_edx_dummy, unsigned char a_4)
{
    *(unsigned int*)(((unsigned int)self) + 8) = ((unsigned int)g_013ef094);
    *(unsigned int*)(((unsigned int)self) + 4) = ((unsigned int)g_013eb394);
    *(unsigned int*)(((unsigned int)self)) = ((unsigned int)g_013eb938);
    if (((a_4 & 1)) == 0) goto L_007c6397;
    FUN_00f47380(((unsigned int)self));
L_007c6397:;
    return ((unsigned int)self);
}
