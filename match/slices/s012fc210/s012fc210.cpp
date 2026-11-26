// 0x012fc210: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013c07b0[];
extern "C" unsigned char g_014194ac[];
extern "C" unsigned char g_01419848[];
extern "C" unsigned char g_01546030[];
extern "C" unsigned char g_0164dd80[];
extern "C" unsigned char g_0164dd84[];
extern "C" unsigned char g_0164dd88[];
extern "C" unsigned char g_0164dd8c[];
extern "C" int __cdecl FUN_00932e80(...);
extern "C" int __cdecl FUN_011e07ef(...);

// @ 0x012fc210
extern "C" void __cdecl FUN_012fc210(void)
{
    int t1003;
    int t1004;
    t1003 = (int)FUN_00932e80((unsigned int)((int)g_01419848), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    *(int*)g_0164dd84 = (int)(t1003);
    t1004 = (int)((int)(*(int*)g_01546030));
    *(int*)g_0164dd88 = (int)(t1004);
    *(int*)g_01546030 = (int)((int)g_0164dd80);
    *(int*)g_0164dd80 = (int)((int)g_014194ac);
    *(int*)g_0164dd8c = (int)((int)250);
    FUN_011e07ef((unsigned int)((int)g_013c07b0));
    return;
}
