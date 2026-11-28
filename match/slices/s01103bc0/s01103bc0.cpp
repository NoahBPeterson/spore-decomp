// 0x01103bc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01102fc0/s01102fc0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6(int, int);
};

extern "C" unsigned char g_013cc2bc[];
extern "C" unsigned char g_016e4174[];
extern "C" unsigned char g_016e4178[];
extern "C" void __cdecl FUN_0107f530(...);

// @ 0x01103bc0
extern "C" int __cdecl FUN_01103bc0(int a4)
{
    int t1001;
    int t1;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1017;
    t1001 = (int)((int)(a4));
    t1 = (int)((int)*(int*)((char*)(t1001) + 8) & (int)1073741823);
    *(int*)((char*)(t1001) + 4) = (int)((int)0);
    if (t1 == (int)0) {
        FUN_0107f530((unsigned int)(t1001), (unsigned int)((int)4));
    }
    *(int*)((char*)(t1001) + 4) += (int)1;
    t1006 = (int)((int)(*(int*)g_016e4174));
    t1007 = (int)((int (__stdcall*)(unsigned int))(*(int*)g_013cc2bc))((unsigned int)(t1006));
    t1010 = (int)(*(int*)((char*)(t1007) + 104));
    if (t1010 != (int)0) {
        *(int*)((char*)(t1007) + 172) -= (int)1;
        t1011 = (int)(*(int*)((char*)(t1010)));
        *(int*)((char*)(t1007) + 104) = (int)(t1011);
        t1012 = (int)(t1010);
    } else {
        t1013 = (int)((int)(*(int*)g_016e4178));
        t1012 = (int)((il2c_vc0*)(t1013))->s6((int)((int)12), (int)((int)28));
    }
    if (t1012 != (int)0) {
        *(int*)((char*)(t1012)) = (int)((int)0);
    } else {
        t1012 = (int)((int)0);
    }
    t1017 = (int)(*(int*)((char*)(t1001)));
    *(int*)((char*)(t1017)) = (int)(t1012);
    *(unsigned char*)((char*)(t1012) + 19) = (unsigned char)((int)16);
    *(unsigned char*)((char*)(t1012) + 16) = (unsigned char)((int)1);
    *(int*)((char*)(t1012) + 24) = (int)((int)(-1));
    *(int*)((char*)(t1012)) = (int)((int)16);
    return (int)(t1012);
}
