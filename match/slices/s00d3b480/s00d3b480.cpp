// 0x00d3b480: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureModeStrategy.cpp, match/slices/s00d3a830/s00d3a830.cpp.

extern "C" void __cdecl FUN_00d39d50(...);

// @ 0x00d3b480
extern "C" int __cdecl FUN_00d3b480(int a4, int a8, int a12)
{
    int t1001;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1008;
    int t1009;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1021;
    t1001 = (int)((int)(a8));
    t1003 = (int)((int)(a4));
    t1004 = (int)(t1001);
    t1005 = (int)(t1004 - t1003);
    t1006 = (int)(t1005 >> (int)3);
    if (t1006 > (int)1) {
        t1008 = (int)((int)8);
        t1009 = (int)(t1001 + (int)(-8));
        t1011 = (int)(t1008 - t1003);
        do {
            t1012 = (int)(*(int*)((char*)(t1003)));
            t1013 = (int)(*(int*)((char*)(t1009)));
            t1014 = (int)(*(int*)((char*)(t1009) + 4));
            *(int*)((char*)(t1009)) = (int)(t1012);
            t1015 = (int)(*(int*)((char*)(t1003) + 4));
            *(int*)((char*)(t1009) + 4) = (int)(t1015);
            t1016 = (int)((int)(a12));
            t1017 = (int)(t1006 - (int)1);
            FUN_00d39d50((unsigned int)(t1003), (unsigned int)((int)0), (unsigned int)(t1017), (unsigned int)((int)0), (unsigned int)(t1013), (unsigned int)(t1014), (unsigned int)(t1016));
            t1009 = (int)(t1009 - (int)8);
            t1021 = (int)(t1011 + t1009);
            t1006 = (int)(t1021 >> (int)3);
        } while (t1006 > (int)1);
    }
    return (int)(t1006);
}
