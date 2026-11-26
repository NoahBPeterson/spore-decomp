// 0x00862d60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013cc550[];

// @ 0x00862d60
extern "C" void __cdecl FUN_00862d60(int a4, int a8)
{
    int t1000;
    t1000 = (int)((int)(a8));
    ((int (__cdecl*)(...))(*(int*)g_013cc550))(t1000);
    return;
}
