// 0x007b4b10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsThumbnailManager.cpp, match/slices/s007b49f0/s007b49f0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int, int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int, int, int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int, int, int, int);
};


// @ 0x007b4b10
extern "C" void __fastcall FUN_007b4b10(char* self, int edx_unused, int a4, int a8, int a12, int a16)
{
    int t1002;
    int t1003;
    int t1005;
    int v_l16[4];
    int t1007;
    int t1008;
    int t1009;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1020;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    int t1031;
    int t1034;
    int t1038;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    int t1043;
    int t1044;
    int t1047;
    int t1048;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 4305) != (unsigned char)0) {
        t1003 = (int)(*(int*)((char*)(t1002) + 4320));
        t1005 = (int)((int)(a16));
        (*(int*)&v_l16[0]) = (int)(t1003);
        t1007 = (int)((int)(a8));
        t1008 = (int)((int)0);
        (*(int*)&v_l16[1]) = (int)(t1008);
        (*(int*)&v_l16[2]) = (int)(t1008);
        (*(int*)&v_l16[3]) = (int)(t1008);
        t1009 = (int)(*(int*)((char*)(t1002) + 4308));
        t1011 = (int)((int)(a4));
        t1012 = (int)(*(int*)((char*)(t1011)));
        *(int*)((char*)(t1009) + 16) = (int)(t1012);
        t1013 = (int)(*(int*)((char*)(t1011) + 4));
        *(int*)((char*)(t1009) + 20) = (int)(t1013);
        t1014 = (int)(*(int*)((char*)(t1002) + 4308));
        t1015 = (int)(*(int*)((char*)(t1007)));
        *(int*)((char*)(t1014) + 28) = (int)(t1015);
        t1016 = (int)(*(int*)((char*)(t1007) + 4));
        *(int*)((char*)(t1014) + 32) = (int)(t1016);
        t1017 = (int)(*(int*)((char*)(t1002) + 4308));
        t1020 = (int)((int)&v_l16);
        ((il2c_vc0*)(t1017))->s3((int)((int)0), (int)((int)0), (int)(t1020), (int)(t1005));
        t1024 = (int)(*(int*)((char*)(t1007)));
        t1025 = (int)(*(int*)((char*)(t1002) + 4312));
        *(int*)((char*)(t1025) + 16) = (int)(t1024);
        t1026 = (int)(*(int*)((char*)(t1007) + 4));
        t1027 = (int)((int)(a12));
        *(int*)((char*)(t1025) + 20) = (int)(t1026);
        t1028 = (int)(*(int*)((char*)(t1002) + 4312));
        t1029 = (int)(*(int*)((char*)(t1027)));
        *(int*)((char*)(t1028) + 28) = (int)(t1029);
        t1030 = (int)(*(int*)((char*)(t1027) + 4));
        *(int*)((char*)(t1028) + 32) = (int)(t1030);
        t1031 = (int)(*(int*)((char*)(t1002) + 4312));
        t1034 = (int)((int)&v_l16);
        ((il2c_vc1*)(t1031))->s3((int)((int)0), (int)((int)0), (int)(t1034), (int)(t1005));
        t1038 = (int)(*(int*)((char*)(t1002) + 4316));
        t1039 = (int)(*(int*)((char*)(t1027)));
        *(int*)((char*)(t1038) + 16) = (int)(t1039);
        t1040 = (int)(*(int*)((char*)(t1027) + 4));
        *(int*)((char*)(t1038) + 20) = (int)(t1040);
        t1041 = (int)(*(int*)((char*)(t1002) + 4316));
        t1042 = (int)(*(int*)((char*)(t1011)));
        *(int*)((char*)(t1041) + 28) = (int)(t1042);
        t1043 = (int)(*(int*)((char*)(t1011) + 4));
        *(int*)((char*)(t1041) + 32) = (int)(t1043);
        t1044 = (int)(*(int*)((char*)(t1002) + 4316));
        t1047 = (int)((int)&v_l16);
        t1048 = (int)(t1044);
        ((il2c_vc2*)(t1048))->s3((int)((int)0), (int)((int)0), (int)(t1047), (int)(t1005));
    }
    return;
}
