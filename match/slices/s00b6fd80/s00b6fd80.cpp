// 0x00b6fd80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b6f4f0/s00b6f4f0.cpp, src/game/SPGonzago/SPMissionManagerBase.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7(int);
};


// @ 0x00b6fd80
extern "C" bool __cdecl FUN_00b6fd80(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1004;
    int t1006;
    int t1008;
    int t1009;
    int t1011;
    int t1012;
    bool t1020;
    t1000 = (int)((int)(a8));
    t1001 = (int)(*(int*)((char*)(t1000) + 4));
    t1004 = (int)(*(int*)((char*)(t1001)));
    t1006 = (int)(t1001);
    if (t1004 == (int)0) {
        t1006 = (int)(t1001 + (int)4);
        if ((int)*(int*)((char*)(t1001) + 4) == t1004) {
            do {
                t1006 = (int)(t1006 + (int)4);
            } while ((int)*(int*)((char*)(t1006)) == (int)0);
        }
        t1004 = (int)(*(int*)((char*)(t1006)));
    }
    t1008 = (int)(*(int*)((char*)(t1000) + 8));
    t1009 = (int)(*(int*)((char*)(t1001) + (t1008)*4));
    if (t1004 != t1009) {
        t1011 = (int)((int)(a4));
        do {
            t1012 = (int)(*(int*)((char*)(t1004) + 12));
            if (t1012 != (int)0) {
                t1001 = (int)((il2c_vc0*)(t1012))->s7((int)(t1011));
            }
            t1004 = (int)(*(int*)((char*)(t1004) + 16));
            if (t1004 == (int)0) {
                do {
                    t1004 = (int)(*(int*)((char*)(t1006) + 4));
                    t1006 = (int)(t1006 + (int)4);
                } while (t1004 == (int)0);
            }
        } while (t1004 != t1009);
    }
    t1020 = true;
    return (bool)(t1020);
}
