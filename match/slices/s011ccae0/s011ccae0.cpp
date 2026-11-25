extern "C" void __cdecl FUN_0117a910(...);
extern "C" void __cdecl FUN_011abd90(...);
extern "C" int __cdecl FUN_011db4a0(...);

extern "C" int __cdecl FUN_011ccae0(unsigned int a_4)
{
    int t_0;

    if (((*(unsigned int*)(a_4 + 156) & *(unsigned int*)(a_4 + 156))) == 0) goto L_011ccb02;
    FUN_011abd90(*(unsigned int*)(a_4 + 156));
    *(unsigned int*)(a_4 + 156) = 0;
L_011ccb02:;
    if (((*(unsigned int*)(a_4 + 160) & *(unsigned int*)(a_4 + 160))) == 0) goto L_011ccb1f;
    FUN_0117a910(*(unsigned int*)(a_4 + 160));
    *(unsigned int*)(a_4 + 160) = 0;
L_011ccb1f:;
    t_0 = FUN_011db4a0(a_4);
    return t_0;
}
