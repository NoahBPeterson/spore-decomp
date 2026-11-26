// 0x00fef5d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00fef140/s00fef140.cpp, src/game/SPGonzago/SPMissionManager.cpp.

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
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};

struct C_00b227c0 { int FUN_00b227c0(); };
extern "C" int __stdcall FUN_00b3d300(unsigned int);
struct C_00b3d330 { int FUN_00b3d330(); };
struct C_00c2e4e0 { void FUN_00c2e4e0(); };
struct C_00fef570 { void FUN_00fef570(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00fef670(...);
extern "C" void __cdecl FUN_00fef6b0(...);

// @ 0x00fef5d0
extern "C" void __fastcall FUN_00fef5d0(char* self, int edx_unused)
{
    int t1002;
    int t1005;
    int t1007;
    int t1014;
    int t1015;
    int t1022;
    int t1023;
    int t1024;
    int t1028;
    int t1029;
    int t1030;
    int t1034;
    int t1035;
    int t1036;
    int t1042;
    int t1043;
    int t1047;
    int t1052;
    t1002 = (int)((int)(self));
    t1005 = (int)((C_00b3d330*)((int)(self)))->FUN_00b3d330();
    t1007 = (int)(t1005);
    ((il2c_vc0*)(t1007))->s21((int)(t1002));
    t1014 = (int)FUN_00fef670();
    t1015 = (int)(t1014);
    ((C_00c2e4e0*)(t1015))->FUN_00c2e4e0();
    FUN_00fef6b0();
    t1022 = (int)(*(int*)((char*)(t1002) + 36));
    t1023 = (int)(*(int*)((char*)(t1002) + 32));
    t1024 = (int)(t1002 + (int)32);
    ((C_00fef570*)(t1024))->FUN_00fef570((unsigned int)(t1023), (unsigned int)(t1022));
    t1028 = (int)(*(int*)((char*)(t1002) + 56));
    t1029 = (int)(*(int*)((char*)(t1002) + 52));
    t1030 = (int)(t1002 + (int)52);
    ((C_00fef570*)(t1030))->FUN_00fef570((unsigned int)(t1029), (unsigned int)(t1028));
    t1034 = (int)(*(int*)((char*)(t1002) + 76));
    t1035 = (int)(*(int*)((char*)(t1002) + 72));
    t1036 = (int)(t1002 + (int)72);
    ((C_00fef570*)(t1036))->FUN_00fef570((unsigned int)(t1035), (unsigned int)(t1034));
    t1042 = (int)FUN_00b3d300((unsigned int)((int)44718810));
    t1043 = (int)(t1042);
    ((C_00b227c0*)(t1043))->FUN_00b227c0();
    t1047 = (int)(*(int*)((char*)(t1002) + 192));
    if (t1047 != (int)0) {
        *(int*)((char*)(t1002) + 192) = (int)((int)0);
        ((il2c_vc1*)(t1047))->s1();
    }
    t1052 = (int)(*(int*)((char*)(t1002) + 196));
    if (t1052 != (int)0) {
        *(int*)((char*)(t1002) + 196) = (int)((int)0);
        ((il2c_vc2*)(t1052))->s1();
        return;
    }
    return;
}
