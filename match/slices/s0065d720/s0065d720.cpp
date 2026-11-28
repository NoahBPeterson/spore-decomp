// 0x0065d720: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPUIFeedEdit.cpp, match/slices/s0065d050/s0065d050.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};

extern "C" unsigned char g_013fa29c[];
extern "C" unsigned char g_01526cb0[];
extern "C" int __cdecl FUN_0065d110(...);
struct C_00810000 { int FUN_00810000(); };
struct C_00810090 { void FUN_00810090(unsigned int, unsigned int); };
struct C_008120d0 { int FUN_008120d0(unsigned int, unsigned int, unsigned int); };
struct C_008121b0 { void FUN_008121b0(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x0065d720
extern "C" bool __fastcall FUN_0065d720(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1003;
    int t1008;
    int t1011;
    int t1012;
    int t1015;
    int t1020;
    int t1023;
    int t1026;
    int t1027;
    int v_l12[3];
    int t1030;
    int t1031;
    int t1035;
    int t1039;
    int t1040;
    bool t1044;
    bool t1046;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    *(int*)((char*)(t1003) + 16) = (int)(t1000);
    if (t1000 != (int)0) {
        t1000 = (int)FUN_00f473a0((unsigned int)((int)24), (unsigned int)((int)g_013fa29c), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1000 != (int)0) {
            t1008 = (int)(t1000);
            t1000 = (int)((C_00810000*)(t1008))->FUN_00810000();
            t1011 = (int)(t1000);
        } else {
            t1011 = (int)((int)0);
        }
        t1012 = (int)(*(int*)((char*)(t1003) + 12));
        if (t1011 != t1012) {
            if (t1011 != (int)0) {
                t1015 = (int)(t1011);
                t1000 = (int)((il2c_vc0*)(t1015))->s1();
            }
            *(int*)((char*)(t1003) + 12) = (int)(t1011);
            if (t1012 != (int)0) {
                t1020 = (int)(t1012);
                t1000 = (int)((il2c_vc1*)(t1020))->s2();
            }
        }
        t1023 = (int)(*(int*)((char*)(t1003) + 12));
        if (t1023 != (int)0) {
            t1026 = (int)((int)(*(int*)g_01526cb0));
            t1027 = (int)((int)&v_l12);
            (*(int*)&v_l12[0]) = (int)((int)(-834284664));
            (*(int*)&v_l12[1]) = (int)((int)84978011);
            (*(int*)&v_l12[2]) = (int)(t1026);
            t1000 = (int)((C_008120d0*)(t1023))->FUN_008120d0((unsigned int)(t1027), (unsigned int)((int)1), (unsigned int)((int)95787258));
            if ((unsigned char)(t1000) != (unsigned char)0) {
                t1030 = (int)(*(int*)((char*)(t1003) + 16));
                t1031 = (int)(*(int*)((char*)(t1003) + 12));
                ((C_008121b0*)(t1031))->FUN_008121b0((unsigned int)(t1030), (unsigned int)((int)1), (unsigned int)((int)95787258));
                t1035 = (int)(*(int*)((char*)(t1003) + 12));
                ((C_00810090*)(t1035))->FUN_00810090((unsigned int)((int)&FUN_0065d110), (unsigned int)(t1003));
                t1039 = (int)(*(int*)((char*)(t1003) + 12));
                t1040 = (int)((int)(a8));
                *(int*)((char*)(t1003) + 64) = (int)(t1040);
                FUN_0065d110((unsigned int)(t1003), (unsigned int)(t1039), (unsigned int)((int)1));
                t1044 = true;
                return (bool)(t1044);
            }
        }
    }
    t1046 = false;
    return (bool)(t1046);
}
