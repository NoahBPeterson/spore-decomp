// 0x00ba7220: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00ba0000.cpp, match/slices/s00ba6750/s00ba6750.cpp.

struct C_00bba2a0 { int FUN_00bba2a0(); };

// @ 0x00ba7220
extern "C" void __fastcall FUN_00ba7220(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1006;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    t1002 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1002) + 200));
    if (t1004 != (int)*(int*)((char*)(t1002) + 204)) {
        t1006 = (int)((int)(a4));
        do {
            t1008 = (int)(*(int*)((char*)(t1004)));
            if (t1008 != (int)*(int*)((char*)(t1004) + 4)) {
                do {
                    t1009 = (int)(*(int*)((char*)(t1008)));
                    t1010 = (int)(*(int*)((char*)(t1009) + 116));
                    if (t1010 == (int)*(int*)((char*)(t1006))) {
                        t1011 = (int)(*(int*)((char*)(t1009) + 120));
                        if (t1011 == (int)*(int*)((char*)(t1006) + 4)) {
                            t1010 = (int)(*(int*)((char*)(t1009) + 124));
                            if (t1010 == (int)*(int*)((char*)(t1006) + 8)) {
                                t1010 = (int)((C_00bba2a0*)(t1009))->FUN_00bba2a0();
                            }
                        }
                    }
                    t1008 = (int)(t1008 + (int)4);
                } while (t1008 != (int)*(int*)((char*)(t1004) + 4));
            }
            t1004 = (int)(t1004 + (int)20);
        } while (t1004 != (int)*(int*)((char*)(t1002) + 204));
    }
    return;
}
