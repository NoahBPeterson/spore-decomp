// 0x00c70420: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPPlanet.cpp, match/slices/s00c6f6e0/s00c6f6e0.cpp.

struct C_005c65e0 { int FUN_005c65e0(); };

// @ 0x00c70420
extern "C" int __cdecl FUN_00c70420(int a4)
{
    int t1001;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1020;
    t1001 = (int)((int)(a4));
    t1005 = (int)(*(int*)((char*)(t1001) + 352));
    t1006 = (int)(t1005 - (int)*(int*)((char*)(t1001) + 348));
    t1007 = (int)((int)0);
    t1008 = (int)(t1006 >> (int)2);
    t1009 = (int)((int)0);
    if (t1008 > (int)0) {
        do {
            t1010 = (int)(*(int*)((char*)(t1001) + 348));
            t1011 = (int)(*(int*)((char*)(t1010) + (t1009)*4));
            t1014 = (int)((C_005c65e0*)(t1011))->FUN_005c65e0();
            t1015 = (int)(*(int*)((char*)(t1014) + 4));
            t1016 = (int)(t1015 - (int)*(int*)((char*)(t1014)));
            t1009 = (int)(t1009 + (int)1);
            t1017 = (int)(t1016 >> (int)2);
            t1007 = (int)(t1007 + t1017);
        } while (t1009 < t1008);
    }
    t1020 = (int)(t1007);
    return (int)(t1020);
}
