// 0x00e7e7a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e7dd90/s00e7dd90.cpp, src/game/SPGonzago/SPCellGame.cpp.

extern "C" unsigned char g_016b3c04[];
struct C_00b72230 { int FUN_00b72230(unsigned int); };
struct C_00e31100 { int FUN_00e31100(); };
extern "C" void __cdecl FUN_00e7e6c0(float);

// @ 0x00e7e7a0
extern "C" void __cdecl FUN_00e7e7a0(float a4)
{
    int t1001;
    int t1002;
    int t1003;
    int t1006;
    int v_l4;
    int t1007;
    int t1008;
    int t1009;
    int t1015;
    int t1016;
    int t1017;
    t1001 = (int)((int)(*(int*)g_016b3c04));
    t1002 = (int)(t1001 + (int)84);
    t1003 = (int)((C_00e31100*)(t1002))->FUN_00e31100();
    t1006 = (int)((int)(*(int*)g_016b3c04));
    v_l4 = (int)(t1003);
    t1007 = (int)((int)&v_l4);
    t1008 = (int)(t1006 + (int)84);
    t1009 = (int)((C_00b72230*)(t1008))->FUN_00b72230((unsigned int)(t1007));
    if (t1009 != (int)0) {
        do {
            FUN_00e7e6c0((float)((float)(a4)));
            t1015 = (int)((int)(*(int*)g_016b3c04));
            t1016 = (int)((int)&v_l4);
            t1017 = (int)(t1015 + (int)84);
            t1009 = (int)((C_00b72230*)(t1017))->FUN_00b72230((unsigned int)(t1016));
        } while (t1009 != (int)0);
    }
    return;
}
