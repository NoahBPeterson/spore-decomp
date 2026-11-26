// 0x00e4f6d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e4e8d0/s00e4e8d0.cpp, src/game/SPGonzago/SPCellGame.cpp.

// @ 0x00e4f6d0
extern "C" int __cdecl FUN_00e4f6d0(int a4, int a8, int a12, int a16, int a20)
{
    int t1001;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1012;
    int t1014;
    int t1016;
    int t1017;
    int v_l4;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1024;
    int t1025;
    t1001 = (int)((int)(a8));
    if (t1001 == (int)(a12)) {
        t1003 = (int)((int)(a16));
        t1004 = (int)(*(int*)((char*)(t1003)));
        t1005 = (int)((int)(a20));
        t1006 = (int)(*(int*)((char*)(t1005)));
        *(int*)((char*)(t1004)) = (int)(t1006);
        *(int*)((char*)(t1003)) += (int)4;
        *(int*)((char*)(t1005)) += (int)1;
        t1007 = (int)((int)1);
        return (int)(t1007);
    }
    t1010 = (int)((int)(a4));
    t1012 = (int)((int)(a20));
    t1014 = (int)((int)(a16));
    t1016 = (int)((int)0);
    t1017 = (int)(t1010 + (int)4);
    v_l4 = (int)((int)4);
    do {
        t1018 = (int)(*(int*)((char*)(t1017)));
        if (t1018 != (int)0) {
            t1019 = (int)((int)(a12));
            t1020 = (int)((int)(a8));
            t1021 = (int)(t1019 + (int)1);
            t1024 = (int)FUN_00e4f6d0((unsigned int)(t1018), (unsigned int)(t1020), (unsigned int)(t1021), (unsigned int)(t1014), (unsigned int)(t1012));
            t1016 = (int)(t1016 + t1024);
        }
        t1017 = (int)(t1017 + (int)4);
        v_l4 = (int)(v_l4 - (int)1);
    } while (v_l4 != (int)0);
    t1025 = (int)(t1016);
    return (int)(t1025);
}
