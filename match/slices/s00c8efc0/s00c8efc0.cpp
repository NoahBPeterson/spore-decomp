// 0x00c8efc0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c8ec60/s00c8ec60.cpp, src/game/SPGonzago/SPTribe.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual int s1();
};

struct C_00b225d0 { int FUN_00b225d0(); };
struct C_00b3d300 { int FUN_00b3d300(unsigned int); };
extern "C" int __stdcall FUN_00b3d300(unsigned int);

// @ 0x00c8efc0
extern "C" int __fastcall FUN_00c8efc0(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1011;
    int t1017;
    int t1020;
    int t1021;
    int t1024;
    int t1029;
    int t1034;
    int t17;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 36));
    if (t1003 != (int)0) {
        t1006 = (int)((C_00b3d300*)((int)(self)))->FUN_00b3d300((unsigned int)(t1003));
        t1007 = (int)(t1006);
        ((C_00b225d0*)(t1007))->FUN_00b225d0();
        t1011 = (int)(*(int*)((char*)(t1002) + 36));
        if (t1011 != (int)0) {
            *(int*)((char*)(t1002) + 36) = (int)((int)0);
            ((il2c_vc0*)(t1011))->s1();
        }
    }
    t1017 = (int)(*(int*)((char*)(t1002) + 40));
    if (t1017 != (int)0) {
        t1020 = (int)FUN_00b3d300((unsigned int)(t1017));
        t1021 = (int)(t1020);
        t1017 = (int)((C_00b225d0*)(t1021))->FUN_00b225d0();
        t1024 = (int)(*(int*)((char*)(t1002) + 40));
        if (t1024 != (int)0) {
            *(int*)((char*)(t1002) + 40) = (int)((int)0);
            t1017 = (int)((il2c_vc1*)(t1024))->s1();
        }
    }
    t1029 = (int)(*(int*)((char*)(t1002) + 60));
    if (t1029 != (int)0) {
        t1017 = (int)((il2c_vc2*)(t1029))->s3((int)((int)1));
        t1034 = (int)(*(int*)((char*)(t1002) + 60));
        if (t1034 != (int)0) {
            *(int*)((char*)(t1002) + 60) = (int)((int)0);
            t17 = (int)((il2c_vc3*)(t1034))->s1();
            return (int)(t17);
        }
    }
    return (int)(t1017);
}
