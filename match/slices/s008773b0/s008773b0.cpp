// 0x008773b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" unsigned char g_013cc420[];

// @ 0x008773b0
extern "C" int __cdecl FUN_008773b0(int a4)
{
    int t1000;
    int t4;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        t1000 = (int)(*(int*)((char*)(t1000) + 84));
        if (t1000 != (int)0) {
            *(int*)&(a4) = (int)(t1000);
            t4 = (int)((int (__cdecl*)(...))(*(int*)g_013cc420))((int)(a4));
            return (int)(t4);
        }
    }
    return (int)(t1000);
}
