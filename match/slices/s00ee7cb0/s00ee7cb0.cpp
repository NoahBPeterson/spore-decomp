// 0x00ee7cb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ee7990/s00ee7990.cpp, src/game/SPEditors/_at_00ee0000.cpp.

extern "C" int __cdecl FUN_00b3d420(...);
struct C_00b8f860 { int FUN_00b8f860(); };
struct C_00b90410 { int FUN_00b90410(unsigned int); };
extern "C" int __cdecl FUN_010212a0(...);

// @ 0x00ee7cb0
extern "C" int __cdecl FUN_00ee7cb0(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int v_l12;
    int t1006;
    int t1009;
    int t1010;
    int t1013;
    int t1014;
    int v_l4;
    int t1021;
    int t1022;
    int v_l8;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1031;
    int t1032;
    int t1035;
    int t1036;
    int t1038;
    int t1042;
    int t1043;
    int t1044;
    int t1045;
    t1000 = (int)((int)(a4));
    if ((unsigned int)(t1000) >= (unsigned int)120334374) {
        *(int*)&(a4) = (int)((int)982246440);
        t1001 = (int)(t1000 + (int)(-120334374));
        goto Lee7cf0;
    }
    if ((unsigned int)(t1000) >= (unsigned int)120334371) {
        *(int*)&(a4) = (int)((int)43792522);
        t1001 = (int)(t1000 + (int)(-120334371));
        goto Lee7cf0;
    }
    *(int*)&(a4) = (int)((int)1835049420);
    t1001 = (int)(t1000 + (int)(-120334368));
    Lee7cf0:;
    v_l12 = (int)(t1001);
    t1006 = (int)FUN_010212a0();
    t1009 = (int)(t1006);
    t1010 = (int)FUN_00b3d420();
    t1013 = (int)(*(int*)((char*)(t1009) + 192));
    t1014 = (int)(t1013 - (int)*(int*)((char*)(t1009) + 188));
    v_l4 = (int)(t1010);
    t1021 = (int)(t1014 / (int)12);
    t1022 = (int)((int)0);
    v_l8 = (int)((int)(-1));
    if (t1021 > (int)0) {
        t1024 = (int)((int)0);
        do {
            t1025 = (int)(*(int*)((char*)(t1009) + 188));
            t1026 = (int)(v_l4);
            t1027 = (int)(t1025 + t1024);
            t1028 = (int)((C_00b90410*)(t1026))->FUN_00b90410((unsigned int)(t1027));
            t1031 = (int)(t1028);
            t1032 = (int)((C_00b8f860*)(t1031))->FUN_00b8f860();
            if (t1032 == (int)(a4)) {
                t1035 = (int)(*(int*)((char*)(t1009) + 248));
                t1036 = (int)(v_l12);
                if ((int)*(int*)((char*)(t1035) + (t1022)*4) == t1036) goto Lee7d6c;
            }
            t1022 = (int)(t1022 + (int)1);
            t1024 = (int)(t1024 + (int)12);
        } while (t1022 < t1021);
        goto Lee7d70;
        Lee7d6c:;
        v_l8 = (int)(t1022);
        Lee7d70:;
    }
    t1038 = (int)((int)(a8));
    if (t1038 != (int)0) {
        t1042 = (int)((int)(a4));
        *(int*)((char*)(t1038)) = (int)(t1042);
    }
    t1043 = (int)((int)(a12));
    if (t1043 != (int)0) {
        t1044 = (int)(v_l12);
        *(int*)((char*)(t1043)) = (int)(t1044);
    }
    t1045 = (int)(v_l8);
    return (int)(t1045);
}
