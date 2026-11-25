extern "C" int __cdecl FUN_011835c0(...);

extern "C" int __cdecl FUN_011c8860(unsigned int a_4)
{
    int t_0;

    if (((*(unsigned char*)(a_4 + 28) & 1)) == 0) goto L_011c889a;
    FUN_011835c0(*(unsigned int*)(a_4 + 4));
    if (((int)(*(unsigned int*)(a_4)) != (int)(3))) goto L_011c889a;
    FUN_011835c0(*(unsigned int*)(a_4 + 16));
    FUN_011835c0(*(unsigned int*)(a_4 + 20));
    FUN_011835c0(*(unsigned int*)(a_4 + 24));
L_011c889a:;
    t_0 = FUN_011835c0(a_4);
    return t_0;
}
