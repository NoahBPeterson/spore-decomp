// 0x00c55540: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c54f90/s00c54f90.cpp, src/game/SPGonzago/SPMissionFindAliens.cpp.

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
    virtual int s9(int, int);
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
    virtual int s9(int, int);
};

struct C_0041e920 { int FUN_0041e920(); };
struct C_0041e990 { int FUN_0041e990(); };
struct C_00c4a0c0 { int FUN_00c4a0c0(); };
struct C_00c4ad50 { int FUN_00c4ad50(); };

// @ 0x00c55540
extern "C" bool __fastcall FUN_00c55540(char* self, int edx_unused)
{
    int t1002;
    int t1005;
    int t1008;
    int t1011;
    int v_l4;
    int t1014;
    int t1015;
    int t1018;
    int t1019;
    int t1020;
    int t1023;
    int t1026;
    int t1027;
    int t1030;
    unsigned char t1031;
    int t1032;
    bool t1036;
    t1002 = (int)((int)(self));
    t1005 = (int)((C_00c4ad50*)((int)(self)))->FUN_00c4ad50();
    if ((unsigned char)(t1005) == (unsigned char)0) {
        return 0;
    }
    t1008 = (int)(*(int*)((char*)(t1002) + 384));
    if (t1008 != (int)0) {
        t1011 = (int)((int)&v_l4);
        t1014 = (int)((il2c_vc0*)(t1008))->s9((int)((int)(-115020801)), (int)(t1011));
        if ((unsigned char)(t1014) != (unsigned char)0) {
            t1015 = (int)(v_l4);
            if ((unsigned short)*(unsigned short*)((char*)(t1015) + 18) == (unsigned short)9) {
                t1018 = (int)((C_0041e990*)(t1015))->FUN_0041e990();
                t1019 = (int)(*(int*)((char*)(t1018)));
                *(int*)((char*)(t1002) + 500) = (int)(t1019);
            }
        }
    }
    t1020 = (int)(*(int*)((char*)(t1002) + 384));
    if (t1020 != (int)0) {
        t1023 = (int)((int)&v_l4);
        t1026 = (int)((il2c_vc1*)(t1020))->s9((int)((int)(-115020800)), (int)(t1023));
        if ((unsigned char)(t1026) != (unsigned char)0) {
            t1027 = (int)(v_l4);
            if ((unsigned short)*(unsigned short*)((char*)(t1027) + 18) == (unsigned short)1) {
                t1030 = (int)((C_0041e920*)(t1027))->FUN_0041e920();
                t1031 = (unsigned char)(*(unsigned char*)((char*)(t1030)));
                *(unsigned char*)((char*)(t1002) + 508) = (unsigned char)(t1031);
            }
        }
    }
    t1032 = (int)(t1002);
    ((C_00c4a0c0*)(t1032))->FUN_00c4a0c0();
    t1036 = true;
    return (bool)(t1036);
}
