// 0x00bc77e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bc0000.cpp, match/slices/s00bc74d0/s00bc74d0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};

struct C_00bc7680 { int FUN_00bc7680(unsigned int); };

// @ 0x00bc77e0
extern "C" int __fastcall FUN_00bc77e0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1;
    int t1010;
    int t1011;
    int t1017;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    t1001 = (int)((int)(a4));
    t1003 = (int)(t1001);
    t1005 = (int)((int)(self));
    t1006 = (int)(*(int*)((char*)(t1005)));
    t1007 = (int)(t1003 << (int)4);
    t1008 = (int)(t1007 - t1001);
    t1 = (int)(t1008 << (int)2);
    t1010 = (int)(t1006 + t1);
    t1011 = (int)(*(int*)((char*)(t1010) + 40));
    if (t1011 != (int)0) {
        ((il2c_vc0*)(t1011))->s1();
    }
    t1017 = (int)(*(int*)((char*)(t1010) + 36));
    if (t1017 != (int)0) {
        ((il2c_vc1*)(t1017))->s1();
    }
    t1023 = (int)(*(int*)((char*)(t1005) + 24));
    t1024 = (int)(*(int*)((char*)(t1010)));
    t1025 = (int)(t1024 & (int)(-1073741824));
    t1026 = (int)(t1023 & (int)1073741823);
    t1027 = (int)(t1025 | t1026);
    t1028 = (int)(t1027 | (int)(-2147483648));
    *(int*)((char*)(t1010)) = (int)(t1028);
    *(int*)((char*)(t1005) + 24) = (int)(t1001);
    if ((int)*(int*)((char*)(t1005) + 20) == t1001) {
        t1029 = (int)(t1005);
        t1026 = (int)((C_00bc7680*)(t1029))->FUN_00bc7680((unsigned int)(t1001));
        *(int*)((char*)(t1005) + 20) = (int)(t1026);
    }
    return (int)(t1026);
}
