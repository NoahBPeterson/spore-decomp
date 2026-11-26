// 0x007fde00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIBehaviorWinAction.cpp, match/slices/s007fd840/s007fd840.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc2 {
    virtual int s0();
};


// @ 0x007fde00
extern "C" bool __cdecl FUN_007fde00(int a4, int a8, int a12)
{
    int t1000;
    int t1001;
    int t1004;
    int t1005;
    int t1007;
    int t1008;
    int t1009;
    int t1011;
    int t1012;
    int t1017;
    int t1024;
    int t1027;
    bool t1031;
    t1000 = (int)((int)(a8));
    t1001 = (int)((int)(a4));
    t1004 = (int)(*(int*)((char*)(t1000) + 4));
    t1005 = (int)((int)(a12));
    t1007 = (int)(*(int*)((char*)(t1001) + 4));
    t1008 = (int)(t1007 + (int)*(int*)((char*)(t1005) + 16));
    t1009 = (int)((int)0);
    if ((unsigned int)*(int*)((char*)(t1005) + 20) > (unsigned int)(t1009)) {
        do {
            t1011 = (int)(*(int*)((char*)(t1008)));
            t1012 = (int)((int)0);
            if (t1011 != (int)0) {
                t1005 = (int)((il2c_vc0*)(t1011))->s1();
            }
            t1017 = (int)(*(int*)((char*)(t1004)));
            if (t1017 != (int)0) {
                t1005 = (int)((il2c_vc1*)(t1017))->s3((int)((int)37988435));
                t1012 = (int)(t1005);
                if (t1012 != (int)0) {
                    t1024 = (int)(t1012);
                    t1005 = (int)((il2c_vc2*)(t1024))->s0();
                }
            }
            t1027 = (int)((int)(a12));
            *(int*)((char*)(t1008)) = (int)(t1012);
            t1009 = (int)(t1009 + (int)1);
            t1008 = (int)(t1008 + (int)4);
            t1004 = (int)(t1004 + (int)4);
        } while ((unsigned int)(t1009) < (unsigned int)*(int*)((char*)(t1027) + 20));
    }
    t1031 = true;
    return (bool)(t1031);
}
