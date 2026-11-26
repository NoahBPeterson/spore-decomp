// 0x008137f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIMainWin.cpp, match/slices/s008133f0/s008133f0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17(int, int, int);
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11(int, int);
};

extern "C" unsigned char g_01418650[];
extern "C" unsigned char g_01418660[];
struct C_00572680 { void FUN_00572680(unsigned int); };
struct C_0067dcd0 { int FUN_0067dcd0(); };
extern "C" int __cdecl FUN_00926020(...);
extern "C" int __cdecl FUN_00999780(...);
struct C_00999820 { int FUN_00999820(unsigned int); };
struct C_00999930 { void FUN_00999930(); };
struct C_00999c20 { int FUN_00999c20(); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x008137f0
extern "C" bool __fastcall FUN_008137f0(char* self, int edx_unused)
{
    int t1003;
    int t1006;
    int t1007;
    int t1012;
    int t1013;
    int t1016;
    int t1017;
    int t1018;
    int t1021;
    int t1027;
    int t1035;
    int t1039;
    int t1042;
    int v_l32[8];
    int t1048;
    int t1049;
    int t1052;
    int t1053;
    int t1054;
    int t1058;
    int t1062;
    bool t1066;
    t1003 = (int)((int)(self));
    t1006 = (int)((C_0067dcd0*)((int)(self)))->FUN_0067dcd0();
    t1007 = (int)(t1006);
    if (t1007 != (int)0) {
        t1012 = (int)FUN_00926020((unsigned int)((int)16), (unsigned int)((int)g_01418660), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
        if (t1012 != (int)0) {
            t1013 = (int)(t1012);
            t1016 = (int)((C_00999c20*)(t1013))->FUN_00999c20();
            t1017 = (int)(t1016);
        } else {
            t1017 = (int)((int)0);
        }
        t1018 = (int)(*(int*)((char*)(t1003) + 656));
        if (t1017 != t1018) {
            if (t1017 != (int)0) {
                t1021 = (int)(t1017);
                ((il2c_vc0*)(t1021))->s1();
            }
            *(int*)((char*)(t1003) + 656) = (int)(t1017);
            if (t1018 != (int)0) {
                t1027 = (int)(t1018);
                ((il2c_vc1*)(t1027))->s2();
            }
        }
        t1006 = (int)(*(int*)((char*)(t1003) + 656));
        if (t1006 != (int)0) {
            t1035 = (int)(t1007);
            ((il2c_vc2*)(t1035))->s17((int)((int)1), (int)(t1006), (int)((int)0));
            t1039 = (int)(*(int*)((char*)(t1003) + 656));
            t1042 = (int)((int)&v_l32);
            ((il2c_vc3*)(t1039))->s11((int)(t1042), (int)((int)8));
            t1048 = (int)FUN_00f473a0((unsigned int)((int)20), (unsigned int)((int)g_01418650), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
            if (t1048 != (int)0) {
                t1049 = (int)(t1048);
                t1052 = (int)((C_00999820*)(t1049))->FUN_00999820((unsigned int)(t1007));
            } else {
                t1052 = (int)((int)0);
            }
            t1053 = (int)(t1003 + (int)668);
            t1054 = (int)(t1053);
            ((C_00572680*)(t1054))->FUN_00572680((unsigned int)(t1052));
            t1058 = (int)(*(int*)((char*)(t1053)));
            ((C_00999930*)(t1058))->FUN_00999930();
            t1062 = (int)(*(int*)((char*)(t1053)));
            t1006 = (int)FUN_00999780((unsigned int)(t1062));
        }
    }
    t1066 = true;
    return (bool)(t1066);
}
