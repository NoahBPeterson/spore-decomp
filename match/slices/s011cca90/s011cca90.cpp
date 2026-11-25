extern "C" void __cdecl FUN_0117a970(...);
extern "C" void __cdecl FUN_011abd90(...);
extern "C" int __cdecl FUN_011b4060(...);

extern "C" int __cdecl FUN_011cca90(unsigned int a_4)
{
    int t_0;

    if (((*(unsigned int*)(a_4 + 156) & *(unsigned int*)(a_4 + 156))) == 0) goto L_011ccab2;
    FUN_011abd90(*(unsigned int*)(a_4 + 156));
    *(unsigned int*)(a_4 + 156) = 0;
L_011ccab2:;
    if (((*(unsigned int*)(a_4 + 160) & *(unsigned int*)(a_4 + 160))) == 0) goto L_011ccacf;
    FUN_0117a970(*(unsigned int*)(a_4 + 160));
    *(unsigned int*)(a_4 + 160) = 0;
L_011ccacf:;
    t_0 = FUN_011b4060(a_4);
    return t_0;
}
