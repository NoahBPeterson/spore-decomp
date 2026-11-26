// 0x006a30c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s006a22a0/s006a22a0.cpp.

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
    virtual int s20(int);
};

extern "C" unsigned char g_015fd918[];
struct C_0041e920 { int FUN_0041e920(); };
struct C_0041e990 { int FUN_0041e990(); };
struct C_0041ea70 { int FUN_0041ea70(); };
struct C_0067de30 { int FUN_0067de30(); };
struct C_006a17e0 { int FUN_006a17e0(unsigned int, unsigned int); };
struct C_006a1880 { int FUN_006a1880(unsigned int, unsigned int); };
struct C_006a1910 { int FUN_006a1910(unsigned int, float); };
struct C_006a2e20 { int FUN_006a2e20(unsigned int, unsigned int); };

// @ 0x006a30c0
extern "C" void __fastcall FUN_006a30c0(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1005;
    int t1007;
    int t1011;
    int t1012;
    unsigned char t1013;
    unsigned char t6;
    int t1014;
    int t1017;
    int t1018;
    int t1019;
    unsigned char t13;
    int t1024;
    int t1027;
    int t1028;
    int t1029;
    unsigned char t20;
    int t1034;
    int t1037;
    int t1038;
    int t1043;
    t1001 = (int)((int)(a4));
    if ((unsigned int)(t1001) < (unsigned int)*(int*)((char*)((int)(self)) + 56)) {
        t1005 = (int)((C_0067de30*)((int)(self)))->FUN_0067de30();
        t1007 = (int)(t1005);
        t1011 = (int)((il2c_vc0*)(t1007))->s20((int)(t1001));
        t1012 = (int)(*(unsigned short*)((char*)(t1011) + 18));
        t1013 = (unsigned char)((int)16);
        if ((unsigned short)(t1012) == (unsigned short)1) {
            t6 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1011) + 16) & t1013);
            if (t6 == (unsigned char)0) {
                t1014 = (int)((int)(a8));
                t1017 = (int)((C_0041e920*)(t1014))->FUN_0041e920();
                t1018 = (int)(*(unsigned char*)((char*)(t1017)));
                t1019 = (int)((int)(*(int*)g_015fd918));
                ((C_006a17e0*)(t1019))->FUN_006a17e0((unsigned int)(t1001), (unsigned int)(t1018));
                return;
            }
        }
        if ((unsigned short)(t1012) == (unsigned short)9) {
            t13 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1011) + 16) & t1013);
            if (t13 == (unsigned char)0) {
                t1024 = (int)((int)(a8));
                t1027 = (int)((C_0041e990*)(t1024))->FUN_0041e990();
                t1028 = (int)(*(int*)((char*)(t1027)));
                t1029 = (int)((int)(*(int*)g_015fd918));
                ((C_006a1880*)(t1029))->FUN_006a1880((unsigned int)(t1001), (unsigned int)(t1028));
                return;
            }
        }
        if ((unsigned short)(t1012) != (unsigned short)13) goto L6a3167;
        t20 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1011) + 16) & t1013);
        if (t20 != (unsigned char)0) goto L6a3167;
        t1034 = (int)((int)(a8));
        t1037 = (int)((C_0041ea70*)(t1034))->FUN_0041ea70();
        t1038 = (int)((int)(*(int*)g_015fd918));
        ((C_006a1910*)(t1038))->FUN_006a1910((unsigned int)(t1001), (float)(*(float*)((char*)(t1037))));
        return;
    }
    t1043 = (int)((int)(a8));
    t1011 = (int)((C_006a2e20*)((int)(self)))->FUN_006a2e20((unsigned int)(t1001), (unsigned int)(t1043));
    L6a3167:;
    return;
}
