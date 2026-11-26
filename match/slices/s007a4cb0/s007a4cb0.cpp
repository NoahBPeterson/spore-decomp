// 0x007a4cb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsSystem.cpp, match/slices/s007a41c0/s007a41c0.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3();
};
struct il2c_vc3 {
    virtual void s0();
    virtual int s1();
};

extern "C" int __cdecl FUN_0067df60(...);
struct C_0075fb90 { int FUN_0075fb90(); };

// @ 0x007a4cb0
extern "C" bool __fastcall FUN_007a4cb0(char* self, int edx_unused)
{
    int t1004;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1018;
    int t1022;
    int t1027;
    int t1028;
    bool t1034;
    int t1036;
    bool t1043;
    t1004 = (int)((int)(self));
    t1007 = (int)((C_0075fb90*)((int)(self)))->FUN_0075fb90();
    t1008 = (int)(*(int*)((char*)(t1004) + 16));
    t1009 = (int)(t1007);
    if (t1009 != t1008) {
        if (t1009 != (int)0) {
            t1012 = (int)(t1009);
            ((il2c_vc0*)(t1012))->s0();
        }
        *(int*)((char*)(t1004) + 16) = (int)(t1009);
        if (t1008 != (int)0) {
            t1018 = (int)(t1008);
            ((il2c_vc1*)(t1018))->s1();
        }
    }
    t1022 = (int)(*(int*)((char*)(t1004) + 16));
    t1027 = (int)((il2c_vc2*)(t1022))->s3();
    if ((unsigned char)(t1027) != (unsigned char)0) {
        t1028 = (int)(*(int*)((char*)(t1004) + 16));
        FUN_0067df60((unsigned int)(t1028));
        t1034 = true;
        return (bool)(t1034);
    }
    t1036 = (int)(*(int*)((char*)(t1004) + 16));
    if (t1036 != (int)0) {
        *(int*)((char*)(t1004) + 16) = (int)((int)0);
        t1027 = (int)((il2c_vc3*)(t1036))->s1();
    }
    t1043 = false;
    return (bool)(t1043);
}
