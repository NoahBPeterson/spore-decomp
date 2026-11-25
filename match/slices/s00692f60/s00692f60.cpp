extern "C" unsigned char g_01403934[];
extern "C" unsigned char g_01600c58[];

extern "C" int __fastcall FUN_00692f60(char* self, int a_edx, unsigned int a_4)
{
    *(unsigned int*)(((unsigned int)self)) = ((unsigned int)g_01403934);
    *(unsigned int*)(((unsigned int)self) + 4) = 0;
    *(unsigned int*)(((unsigned int)self) + 8) = a_4;
    *(unsigned char*)(((unsigned int)self) + 12) = ((unsigned char)(0));
    if (((int)(*(unsigned int*)g_01600c58) == (int)(0))) goto L_00692f84;
    *(unsigned int*)(((unsigned int)self) + 4) = *(unsigned int*)g_01600c58;
L_00692f84:;
    *(unsigned int*)g_01600c58 = ((unsigned int)self);
    return ((unsigned int)self);
}
