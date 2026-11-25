extern "C" unsigned char g_006c1180[];
extern "C" int __cdecl FUN_011e22c0(...);

extern "C" int __fastcall FUN_006c12a0(char* self)
{
    int t_0;

    t_0 = FUN_011e22c0(131247);
    *(unsigned int*)(t_0 + 4) = 0;
    *(unsigned int*)(t_0 + 8) = 0;
    *(unsigned int*)(t_0 + 12) = ((unsigned int)g_006c1180);
    *(unsigned int*)(t_0 + 16) = 0;
    return t_0;
}
