extern "C" unsigned char g_013bfff0[];
extern "C" unsigned char g_01636248[];
extern "C" unsigned char g_0163624c[];
extern "C" unsigned char g_01636250[];
extern "C" unsigned char g_01636258[];
extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bae[];
extern "C" void __cdecl FUN_011e07ef(...);

extern "C" int __cdecl FUN_007c65a0()
{
    if (((*(unsigned char*)g_01636258 & ((unsigned char)(1)))) != 0) goto L_007c65d9;
    *(unsigned int*)g_01636258 = (*(unsigned int*)g_01636258 | 1);
    *(unsigned int*)g_01636248 = ((unsigned int)g_01667bac);
    *(unsigned int*)g_0163624c = ((unsigned int)g_01667bac);
    *(unsigned int*)g_01636250 = ((unsigned int)g_01667bae);
    FUN_011e07ef(((unsigned int)g_013bfff0));
L_007c65d9:;
    return ((unsigned int)g_01636248);
}
