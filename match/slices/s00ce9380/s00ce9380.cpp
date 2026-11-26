// 0x00ce9380: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00ce0000.cpp, match/slices/s00ce90c0/s00ce90c0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual int s39(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual int s39(int);
};


// @ 0x00ce9380
extern "C" void __fastcall FUN_00ce9380(char* self, int edx_unused, int a4)
{
    int t1003;
    unsigned char t1005;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int v_l32[4];
    int t1015;
    float t1016;
    float t1017;
    float t1018;
    float t1019;
    float t1020;
    float t1021;
    float t1022;
    float t1023;
    int t1026;
    int v_l16[4];
    t1003 = (int)((int)(a4));
    t1005 = (unsigned char)((int)0);
    t1007 = (int)((int)(self) + (int)108);
    t1008 = (int)((int)4);
    do {
        t1009 = (int)(*(int*)((char*)(t1007)));
        if (t1009 != (int)0) {
            if ((unsigned char)*(unsigned char*)((char*)(t1009) + 484) != (unsigned char)0) {
                if (t1005 != (unsigned char)0) {
                    t1012 = (int)((int)&v_l32);
                    t1015 = (int)((il2c_vc0*)(t1009))->s39((int)(t1012));
                    t1016 = (float)(*(float*)((char*)(t1003)));
                    t1017 = (float)(*(float*)((char*)(t1015)));
                    if (!(t1017 > t1016)) {
                        t1016 = (float)(t1017);
                    }
                    *(float*)((char*)(t1003)) = (float)(t1016);
                    t1018 = (float)(*(float*)((char*)(t1003) + 4));
                    t1019 = (float)(*(float*)((char*)(t1015) + 4));
                    if (!(t1019 > t1018)) {
                        t1018 = (float)(t1019);
                    }
                    *(float*)((char*)(t1003) + 4) = (float)(t1018);
                    t1020 = (float)(*(float*)((char*)(t1003) + 8));
                    t1021 = (float)(*(float*)((char*)(t1015) + 8));
                    if (!(t1020 > t1021)) {
                        t1020 = (float)(t1021);
                    }
                    *(float*)((char*)(t1003) + 8) = (float)(t1020);
                    t1022 = (float)(*(float*)((char*)(t1003) + 12));
                    t1023 = (float)(*(float*)((char*)(t1015) + 12));
                    if (!(t1022 > t1023)) {
                        t1022 = (float)(t1023);
                    }
                    *(float*)((char*)(t1003) + 12) = (float)(t1022);
                    goto Lce9441;
                }
                t1026 = (int)((int)&v_l16);
                t1015 = (int)((il2c_vc1*)(t1009))->s39((int)(t1026));
                *(float*)((char*)(t1003)) = (float)(*(float*)((char*)(t1015)));
                t1005 = (unsigned char)((int)1);
                *(float*)((char*)(t1003) + 4) = (float)(*(float*)((char*)(t1015) + 4));
                *(float*)((char*)(t1003) + 8) = (float)(*(float*)((char*)(t1015) + 8));
                *(float*)((char*)(t1003) + 12) = (float)(*(float*)((char*)(t1015) + 12));
            }
        }
        Lce9441:;
        t1007 = (int)(t1007 + (int)4);
        t1008 = (int)(t1008 - (int)1);
    } while (t1008 != (int)0);
    return;
}
