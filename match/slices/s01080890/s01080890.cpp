// 0x01080890: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01080450/s01080450.cpp.

struct il2c_vc0 {
    virtual void s0(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5(int, int, int);
};

extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_0149d274[];
extern "C" unsigned char g_016e4178[];

// @ 0x01080890
extern "C" int __fastcall FUN_01080890(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1008;
    int t1009;
    unsigned char t7;
    int t1014;
    int t1015;
    int t1020;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 8));
    *(int*)((char*)(t1002)) = (int)((int)g_0149d274);
    if ((unsigned short)*(unsigned short*)((char*)(t1003) + 4) != (unsigned short)0) {
        *(unsigned short*)((char*)(t1003) + 6) -= (unsigned short)1;
        if ((unsigned short)*(unsigned short*)((char*)(t1003) + 6) == (unsigned short)0) {
            ((il2c_vc0*)(t1003))->s0((int)((int)1));
        }
    }
    t1008 = (int)((int)(*(int*)g_016e4178));
    t1009 = (int)(*(int*)((char*)(t1002) + 12));
    ((il2c_vc1*)(t1008))->s3((int)(t1009));
    t7 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    *(int*)((char*)(t1002)) = (int)((int)g_013ef094);
    if (t7 != (unsigned char)0) {
        t1014 = (int)(*(unsigned short*)((char*)(t1002) + 4));
        t1015 = (int)((int)(*(int*)g_016e4178));
        ((il2c_vc2*)(t1015))->s5((int)(t1002), (int)(t1014), (int)((int)23));
    }
    t1020 = (int)(t1002);
    return (int)(t1020);
}
