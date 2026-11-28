// 0x00ec8d80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ec8d20/s00ec8d20.cpp.

struct C_00b534c0 { int FUN_00b534c0(unsigned int, unsigned int); };

// @ 0x00ec8d80
// @ 0x00ec8d80
extern "C" int __cdecl FUN_00ec8d80(int a4)
{
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int v_l32[7];
    int v_l40[2];
    int t1008;
    int t1009;
    int t1;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1018;
    int t1019;
    int t8;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    t1003 = (int)((int)(a4));
    t1004 = (int)((int)25);
    t1005 = (int)((int)50);
    t1006 = (int)((int)75);
    (*(int*)&v_l32[0]) = (int)(t1004);
    (*(int*)&v_l32[1]) = (int)(t1005);
    (*(int*)&v_l32[2]) = (int)(t1006);
    (*(int*)&v_l32[3]) = (int)((int)100);
    (*(int*)&v_l32[4]) = (int)(t1006);
    (*(int*)&v_l32[5]) = (int)(t1005);
    (*(int*)&v_l32[6]) = (int)(t1004);
    (*(int*)&v_l40[0]) = (int)((int)5);
    t1008 = (int)((int)0);
    do {
        t1009 = (int)(*(int*)((char*)(t1003) + 4));
        t1 = (int)((int)&v_l32);
        t1010 = (int)(*(int*)((char*)(t1) + (t1008)*4));
        (*(int*)&v_l40[1]) = (int)(t1010);
        if ((unsigned int)(t1009) < (unsigned int)*(int*)((char*)(t1003) + 8)) {
            t1011 = (int)(t1009 + (int)8);
            *(int*)((char*)(t1003) + 4) = (int)(t1011);
            if (t1009 == (int)0) goto Lec8df9;
            t1012 = (int)((*(int*)&v_l40[0]));
            *(int*)((char*)(t1009)) = (int)(t1012);
            *(int*)((char*)(t1009) + 4) = (int)(t1010);
            goto Lec8df9;
        }
        t1013 = (int)((int)&v_l40);
        t1014 = (int)(t1003);
        ((C_00b534c0*)(t1014))->FUN_00b534c0((unsigned int)(t1009), (unsigned int)(t1013));
        Lec8df9:;
        t1008 = (int)(t1008 + (int)1);
    } while ((unsigned int)(t1008) < (unsigned int)3);
    (*(int*)&v_l40[0]) = (int)((int)6);
    t1018 = (int)((int)0);
    do {
        t1019 = (int)(*(int*)((char*)(t1003) + 4));
        t8 = (int)((int)&v_l32[3]);
        t1020 = (int)(*(int*)((char*)(t8) + (t1018)*4));
        (*(int*)&v_l40[1]) = (int)(t1020);
        if ((unsigned int)(t1019) < (unsigned int)*(int*)((char*)(t1003) + 8)) {
            t1021 = (int)(t1019 + (int)8);
            *(int*)((char*)(t1003) + 4) = (int)(t1021);
            if (t1019 == (int)0) goto Lec8e3b;
            t1022 = (int)((*(int*)&v_l40[0]));
            *(int*)((char*)(t1019)) = (int)(t1022);
            *(int*)((char*)(t1019) + 4) = (int)(t1020);
            goto Lec8e3b;
        }
        t1023 = (int)((int)&v_l40);
        t1024 = (int)(t1003);
        t1019 = (int)((C_00b534c0*)(t1024))->FUN_00b534c0((unsigned int)(t1019), (unsigned int)(t1023));
        Lec8e3b:;
        t1018 = (int)(t1018 + (int)1);
    } while ((unsigned int)(t1018) < (unsigned int)4);
    return (int)(t1019);
}
