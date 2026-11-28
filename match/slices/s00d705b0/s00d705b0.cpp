// 0x00d705b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureSleep.cpp, match/slices/s00d70080/s00d70080.cpp.

struct C_00c04590 { int FUN_00c04590(); };

// @ 0x00d705b0
extern "C" float __cdecl FUN_00d705b0(int a4)
{
    int t1000;
    int t1001;
    int t1004;
    int t1005;
    int t1006;
    int t4;
    t1000 = (int)((int)(a4));
    t1001 = (int)((C_00c04590*)(t1000))->FUN_00c04590();
    t1004 = (int)(t1001 + (int)356);
    t1005 = (int)(*(int*)((char*)(t1004)));
    if (t1005 != (int)0) {
        t1006 = (int)(*(int*)((char*)(t1005) + 2892));
        if ((int)*(int*)((char*)(t1006) + 472) == (int)47731444) {
            t4 = (int)((int)*(int*)((char*)(t1005) + 2904) & (int)1024);
            if (t4 != (int)0) {
                return (float)((float)1);
            }
        }
    }
    return (float)((float)0);
}
