// 0x00aca1f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ac9f70/s00ac9f70.cpp, src/game/SPGonzago/_at_00ac0000.cpp.

// @ 0x00aca1f0
extern "C" int __cdecl FUN_00aca1f0(int a4, int a8, int a12)
{
    int t1000;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    t1000 = (int)((int)(a4));
    t1002 = (int)((int)(a8));
    t1003 = (int)(t1002 - t1000);
    t1004 = (int)(t1003 >> (int)5);
    if (t1004 > (int)0) {
        t1005 = (int)((int)(a12));
        t1007 = (int)(*(int*)((char*)(t1005)));
        do {
            t1008 = (int)(t1004);
            t1009 = (int)(t1008 >> (int)1);
            t1010 = (int)(t1009);
            t1011 = (int)(t1010 << (int)5);
            t1012 = (int)(t1011 + t1000);
            if ((int)*(int*)((char*)(t1012)) < t1007) {
                t1000 = (int)(t1012 + (int)32);
                t1013 = (int)(t1012 | (int)(-1));
                t1014 = (int)(t1013 - t1009);
                t1004 = (int)(t1004 + t1014);
            } else {
                t1004 = (int)(t1009);
            }
        } while (t1004 > (int)0);
    }
    return (int)(t1000);
}
