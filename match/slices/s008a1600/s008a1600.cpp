// 0x008a1600: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_0089ed20[];
extern "C" unsigned char g_0089ed40[];
struct C_0089edb0 { int FUN_0089edb0(); };
struct C_0089eed0 { void FUN_0089eed0(); };
struct C_008a0ef0 { int FUN_008a0ef0(); };
struct C_008a1350 { void FUN_008a1350(); };
struct C_00928b00 { void FUN_00928b00(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x008a1600
extern "C" bool __fastcall FUN_008a1600(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1008;
    int t1014;
    int t1017;
    int t1018;
    int t1022;
    int t1026;
    bool t1030;
    bool t1032;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 304) == (unsigned char)0) {
        t1003 = (int)(*(int*)((char*)(t1002) + 348));
        t1004 = (int)(t1002 + (int)312);
        *(unsigned char*)((char*)(t1002) + 304) = (unsigned char)((int)1);
        ((C_00928b00*)(t1004))->FUN_00928b00((unsigned int)((int)0), (unsigned int)((int)512), (unsigned int)((int)g_0089ed20), (unsigned int)((int)g_0089ed40), (unsigned int)(t1003));
        t1008 = (int)((int)(a4));
        *(int*)((char*)(t1002) + 308) = (int)(t1008);
        ((il2c_vc0*)(t1008))->s1();
        t1014 = (int)(t1002);
        t1017 = (int)((C_0089edb0*)(t1014))->FUN_0089edb0();
        if ((unsigned char)(t1017) != (unsigned char)0) {
            t1018 = (int)(t1002);
            ((C_0089eed0*)(t1018))->FUN_0089eed0();
            t1022 = (int)(t1002);
            ((C_008a1350*)(t1022))->FUN_008a1350();
            t1026 = (int)(t1002);
            ((C_008a0ef0*)(t1026))->FUN_008a0ef0();
            t1030 = true;
            return (bool)(t1030);
        }
    }
    t1032 = false;
    return (bool)(t1032);
}
