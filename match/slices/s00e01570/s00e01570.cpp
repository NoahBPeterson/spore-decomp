// 0x00e01570: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUIGlobalUI.cpp, match/slices/s00e00760/s00e00760.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};


// @ 0x00e01570
extern "C" int __fastcall FUN_00e01570(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1030;
    int t1037;
    t1002 = (int)((int)(self));
    t1004 = (int)((int)(a4));
    t1005 = (int)(*(int*)((char*)(t1004)));
    *(int*)((char*)(t1002)) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1004) + 4));
    *(int*)((char*)(t1002) + 4) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1004) + 8));
    *(int*)((char*)(t1002) + 8) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1004) + 12));
    *(int*)((char*)(t1002) + 12) = (int)(t1008);
    t1009 = (int)(*(unsigned char*)((char*)(t1004) + 16));
    *(unsigned char*)((char*)(t1002) + 16) = (unsigned char)((unsigned char)(t1009));
    t1010 = (int)(*(unsigned char*)((char*)(t1004) + 17));
    *(unsigned char*)((char*)(t1002) + 17) = (unsigned char)((unsigned char)(t1010));
    t1011 = (int)(*(unsigned char*)((char*)(t1004) + 18));
    *(unsigned char*)((char*)(t1002) + 18) = (unsigned char)((unsigned char)(t1011));
    t1012 = (int)(*(unsigned char*)((char*)(t1004) + 19));
    *(unsigned char*)((char*)(t1002) + 19) = (unsigned char)((unsigned char)(t1012));
    t1013 = (int)(*(unsigned char*)((char*)(t1004) + 20));
    *(unsigned char*)((char*)(t1002) + 20) = (unsigned char)((unsigned char)(t1013));
    t1014 = (int)(*(int*)((char*)(t1004) + 24));
    *(int*)((char*)(t1002) + 24) = (int)(t1014);
    t1015 = (int)(*(int*)((char*)(t1004) + 28));
    *(int*)((char*)(t1002) + 28) = (int)(t1015);
    t1016 = (int)(*(int*)((char*)(t1004) + 32));
    *(int*)((char*)(t1002) + 32) = (int)(t1016);
    t1017 = (int)(*(unsigned char*)((char*)(t1004) + 36));
    *(unsigned char*)((char*)(t1002) + 36) = (unsigned char)((unsigned char)(t1017));
    t1018 = (int)(*(int*)((char*)(t1004) + 40));
    *(int*)((char*)(t1002) + 40) = (int)(t1018);
    t1019 = (int)(*(unsigned char*)((char*)(t1004) + 44));
    *(unsigned char*)((char*)(t1002) + 44) = (unsigned char)((unsigned char)(t1019));
    t1020 = (int)(*(int*)((char*)(t1004) + 48));
    *(int*)((char*)(t1002) + 48) = (int)(t1020);
    t1021 = (int)(*(int*)((char*)(t1004) + 52));
    *(int*)((char*)(t1002) + 52) = (int)(t1021);
    t1022 = (int)(*(int*)((char*)(t1004) + 56));
    *(int*)((char*)(t1002) + 56) = (int)(t1022);
    t1023 = (int)(*(int*)((char*)(t1004) + 60));
    *(int*)((char*)(t1002) + 60) = (int)(t1023);
    t1024 = (int)(*(int*)((char*)(t1004) + 64));
    *(int*)((char*)(t1002) + 64) = (int)(t1024);
    if (t1024 != (int)0) {
        ((il2c_vc0*)(t1024))->s1();
    }
    t1030 = (int)(*(int*)((char*)(t1004) + 68));
    *(int*)((char*)(t1002) + 68) = (int)(t1030);
    if (t1030 != (int)0) {
        ((il2c_vc1*)(t1030))->s1();
    }
    t1037 = (int)(t1002);
    return (int)(t1037);
}
