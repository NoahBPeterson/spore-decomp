extern "C" unsigned char g_016e61a8[];
extern "C" int __cdecl FUN_01133f80(...);

extern "C" int __fastcall FUN_0112dc80(char* self)
{
    int t_0;

    if (((int)(*(unsigned int*)(((unsigned int)self) + 44)) != (int)(0))) goto L_0112dc9a;
    t_0 = FUN_01133f80(*(unsigned int*)g_016e61a8);
    *(unsigned int*)(((unsigned int)self) + 44) = t_0;
L_0112dc9a:;
    return *(unsigned int*)(((unsigned int)self) + 44);
}
