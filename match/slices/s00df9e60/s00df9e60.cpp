// 0x00df9e60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00df9650/s00df9650.cpp.

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
    virtual int s21();
};

extern "C" unsigned char g_016a1344[];
extern "C" int __cdecl FUN_0067dd00(...);
struct C_00df97e0 { void FUN_00df97e0(); };
struct C_00df9ad0 { void FUN_00df9ad0(); };
struct C_00df9c80 { int FUN_00df9c80(unsigned int); };
struct C_00df9e60 { int FUN_00df9e60(); };

// @ 0x00df9e60
extern "C" void __fastcall FUN_00df9e60(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t2;
    int t1006;
    int t1007;
    int t1008;
    int t1012;
    int t1013;
    int t4;
    int t1014;
    int t1015;
    int t1016;
    int t1019;
    int t1020;
    int t1025;
    int t1027;
    int t1031;
    int t1032;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 44));
    if ((unsigned int)(t1003) > (unsigned int)0) {
        t1004 = (int)(*(int*)((char*)(t1002) + 12));
        t1005 = (int)(t1003 - (int)1);
        *(int*)((char*)(t1002) + 44) = (int)(t1005);
        t2 = (int)(t1005 << (int)3);
        t1006 = (int)(t1005 + t2);
        t1007 = (int)(*(int*)((char*)(t1004) + (t1006)*4 + 32));
        t1008 = (int)(t1002);
        *(int*)((char*)(t1002) + 32) = (int)(t1007);
        ((C_00df97e0*)(t1008))->FUN_00df97e0();
        t1012 = (int)(*(int*)((char*)(t1002) + 44));
        t1013 = (int)(*(int*)((char*)(t1002) + 12));
        t4 = (int)(t1012 << (int)3);
        t1014 = (int)(t1012 + t4);
        t1015 = (int)(*(int*)((char*)(t1013) + (t1014)*4));
        t1016 = (int)(t1002);
        t1019 = (int)((C_00df9c80*)(t1016))->FUN_00df9c80((unsigned int)(t1015));
        if ((int)*(int*)((char*)(t1002) + 32) == (int)2) {
            if ((unsigned char)*(unsigned char*)((char*)(t1002) + 124) == (unsigned char)0) {
                t1020 = (int)(t1002);
                t1019 = (int)((C_00df9e60*)(t1020))->FUN_00df9e60();
            }
        }
        if ((int)*(int*)((char*)(t1002) + 32) == (int)1) {
            t1025 = (int)FUN_0067dd00();
            t1027 = (int)(t1025);
            t1019 = (int)((il2c_vc0*)(t1027))->s21();
            if ((unsigned char)(t1019) == (unsigned char)0) {
                t1031 = (int)((int)(*(int*)g_016a1344));
                if ((int)*(int*)((char*)(t1031) + 504) == (int)0) {
                    t1032 = (int)(t1002);
                    t1019 = (int)((C_00df9e60*)(t1032))->FUN_00df9e60();
                }
            }
        }
        *(unsigned char*)((char*)(t1002) + 126) = (unsigned char)((int)1);
        return;
    }
    ((C_00df9ad0*)((int)(self)))->FUN_00df9ad0();
    return;
}
