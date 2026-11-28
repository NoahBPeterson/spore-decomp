// 0x00ec1670: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ec0a40/s00ec0a40.cpp.

#include <string.h>
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
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual int s46(int);
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
    virtual void s9();
    virtual void s10();
    virtual int s11();
};

extern "C" unsigned char g_01486110[];
extern "C" unsigned char g_017f243b[];
struct C_00bc97f0 { int FUN_00bc97f0(unsigned int, unsigned int, float, unsigned int); };
struct C_00c7d070 { int FUN_00c7d070(); };
extern "C" int __cdecl FUN_00c7d090(...);
extern "C" int __cdecl FUN_00ec0c90(...);
extern "C" int __cdecl FUN_00ec0d00(...);

// @ 0x00ec1670
extern "C" float __cdecl FUN_00ec1670(int a4, int a8, int a12, int a16, int a20, int a24, int a28)
{
    int t1000;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1008;
    int t1013;
    int t1015;
    int t1016;
    int t1025;
    int t1026;
    int t1029;
    int t1030;
    int t1031;
    int v_l8[2];
    int t1032;
    int t1033;
    int t1036;
    int t1039;
    int t1042;
    int t1043;
    int t1046;
    int t1047;
    int t1050;
    int t1056;
    int t1057;
    int t1058;
    int t1063;
    t1000 = (int)((int)(a28));
    t1002 = (int)(*(unsigned short*)((char*)(t1000) + 18));
    t1004 = (int)((int)(a4));
    t1005 = (int)(t1002 << (int)5);
    t1006 = (int)(t1005 + (int)*(int*)((char*)(t1004) + 1652));
    t1008 = (int)FUN_00ec0d00((unsigned int)(t1004), (unsigned int)(t1006));
    if ((unsigned char)(t1008) == (unsigned char)0) {
        return (float)((float)0);
    }
    t1013 = (int)(*(int*)((char*)(t1006) + 4));
    t1015 = (int)(t1006 + (int)4);
    if (t1013 != (int)0) {
        if (t1013 != (int)1) {
            if (t1013 != (int)2) {
                if (t1013 != (int)8) {
                    t1016 = (int)(t1004 + (int)1672);
                    memcpy((void*)(t1016), (const void*)(t1006), (unsigned int)((int)32));
                    return (float)((float)1);
                }
            }
        }
    }
    t1025 = (int)(t1004 + (int)1648);
    t1026 = (int)((C_00c7d070*)(t1025))->FUN_00c7d070();
    t1029 = (int)(*(int*)((char*)(t1026)));
    t1030 = (int)(*(int*)((char*)(t1026) + 4));
    t1031 = (int)(*(int*)((char*)(t1015)));
    (*(int*)&v_l8[0]) = (int)(t1031);
    t1032 = (int)(*(int*)((char*)(t1015) + 4));
    *(int*)&(a28) = (int)(t1030);
    (*(int*)&v_l8[1]) = (int)(t1032);
    if (t1029 != t1030) {
        do {
            t1033 = (int)(*(int*)((char*)(t1029)));
            if (t1033 != (int)0) {
                t1036 = (int)((il2c_vc0*)(t1033))->s46((int)((int)g_017f243b));
                t1039 = (int)(t1036);
                if (t1039 != (int)0) {
                    t1042 = (int)(t1039);
                    t1043 = (int)((il2c_vc1*)(t1042))->s11();
                    if ((unsigned char)(t1043) == (unsigned char)0) {
                        t1046 = (int)((int)&v_l8);
                        t1047 = (int)FUN_00c7d090((unsigned int)(t1039), (unsigned int)(t1046));
                        if ((unsigned char)(t1047) != (unsigned char)0) {
                            if ((int)*(int*)((char*)(t1006)) != (int)4) goto Lec1759;
                            t1050 = (int)FUN_00ec0c90((unsigned int)(t1039), (unsigned int)(t1015));
                            if ((unsigned char)(t1050) != (unsigned char)0) goto Lec1759;
                        }
                    }
                }
                t1030 = (int)((int)(a28));
            }
            t1029 = (int)(t1029 + (int)4);
        } while (t1029 != t1030);
    }
    return (float)((float)0);
    Lec1759:;
    t1056 = (int)((int)(a4));
    t1057 = (int)(*(int*)((char*)(t1056) + 2892));
    t1058 = (int)(t1057 + (int)8);
    ((C_00bc97f0*)(t1058))->FUN_00bc97f0((unsigned int)((int)0), (unsigned int)((int)268435456), (float)((float)(*(float*)g_01486110)), (unsigned int)(t1039));
    t1063 = (int)(t1056 + (int)1672);
    memcpy((void*)(t1063), (const void*)(t1006), (unsigned int)((int)32));
    return (float)((float)1);
}
