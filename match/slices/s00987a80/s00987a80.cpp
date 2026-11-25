struct C_00830150 { int FUN_00830150(unsigned int); };
struct C_00830280 { void FUN_00830280(unsigned int); };
struct C_00c2e4e0 { void FUN_00c2e4e0(); };

extern "C" int __cdecl FUN_00987a80(unsigned int a_4)
{
    int t_0;

    ((C_00c2e4e0*)(a_4))->FUN_00c2e4e0();
    ((C_00830280*)((a_4 + 84)))->FUN_00830280(*(unsigned int*)(a_4 + 84));
    t_0 = ((C_00830150*)((a_4 + 84)))->FUN_00830150(*(unsigned int*)(a_4 + 88));
    return t_0;
}
