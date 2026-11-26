// 0x008ecc10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008ec360/s008ec360.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1(int, int);
};

struct C_00899480 { void FUN_00899480(unsigned int, unsigned int); };

// @ 0x008ecc10
extern "C" int __stdcall FUN_008ecc10(int a4, int a8, int a12)
{
    int t1001;
    int t1002;
    int t1003;
    int t1004;
    int t1006;
    int t1007;
    int t1010;
    int t2;
    int t1011;
    int t1012;
    int t1013;
    int t1015;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1029;
    int t1030;
    int t1031;
    t1001 = (int)((int)(a8));
    t1002 = (int)(*(int*)((char*)(t1001)));
    t1003 = (int)(*(int*)((char*)(t1001) + 4));
    t1004 = (int)(t1003 - t1002);
    t1006 = (int)(t1004 >> (int)2);
    t1007 = (int)((int)0);
    if ((unsigned int)(t1006) > (unsigned int)0) {
        t1010 = (int)((int)(a12));
        do {
            t2 = (int)(t1007 << (int)2);
            t1011 = (int)(t2);
            t1012 = (int)(*(int*)((char*)(t1011) + t1002));
            t1013 = (int)(*(int*)((char*)(t1012) + 4));
            if (t1013 != (int)0) {
                t1015 = (int)((int)(a4));
                t1019 = (int)((il2c_vc0*)(t1013))->s1((int)(t1015), (int)((int)0));
                if ((unsigned char)(t1019) == (unsigned char)0) goto L8ecc78;
            }
            t1020 = (int)(*(int*)((char*)(t1001)));
            t1021 = (int)(*(int*)((char*)(t1010) + 4));
            t1022 = (int)(t1020 + t1011);
            if ((unsigned int)(t1021) < (unsigned int)*(int*)((char*)(t1010) + 8)) {
                t1023 = (int)(t1021 + (int)4);
                *(int*)((char*)(t1010) + 4) = (int)(t1023);
                if (t1021 == (int)0) goto L8ecc78;
                t1024 = (int)(*(int*)((char*)(t1022)));
                *(int*)((char*)(t1021)) = (int)(t1024);
                goto L8ecc78;
            }
            t1025 = (int)(t1010);
            ((C_00899480*)(t1025))->FUN_00899480((unsigned int)(t1021), (unsigned int)(t1022));
            L8ecc78:;
            t1002 = (int)(*(int*)((char*)(t1001)));
            t1029 = (int)(*(int*)((char*)(t1001) + 4));
            t1030 = (int)(t1029 - t1002);
            t1007 = (int)(t1007 + (int)1);
            t1031 = (int)(t1030 >> (int)2);
        } while ((unsigned int)(t1007) < (unsigned int)(t1031));
    }
    return (int)(t1002);
}
