extern "C" unsigned char g_016f16f4[];

extern "C" int __fastcall FUN_011683e0(char* self)
{
    if (((int)(*(unsigned char*)(((unsigned int)self) + 71)) == (int)(((unsigned char)(0))))) goto L_011683fa;
    *(unsigned int*)(((unsigned int)self) + 76) = 0;
    *(unsigned char*)(((unsigned int)self) + 71) = ((unsigned char)(0));
    ((void (__cdecl *)(...))*(unsigned int*)g_016f16f4)(*(unsigned int*)(((unsigned int)self) + 80));
L_011683fa:;
    return 0;
}
