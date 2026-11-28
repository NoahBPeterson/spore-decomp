// 0x00c17d60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c17350/s00c17350.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};

struct C_009cab60 { int FUN_009cab60(unsigned int); };
struct C_00c14f70 { int FUN_00c14f70(unsigned int, unsigned int, unsigned int); };
struct C_00c15150 { void FUN_00c15150(unsigned int, unsigned int); };

// @ 0x00c17d60
extern "C" int __fastcall FUN_00c17d60(char* self, int edx_unused, int a4, int a8, int a12, int a16, int a20)
{
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1013;
    int t1015;
    int t1018;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1030;
    int t1031;
    int t1032;
    int t1037;
    t1003 = (int)((int)(self));
    if ((unsigned char)(a4) != (unsigned char)0) {
        t1004 = (int)(*(int*)((char*)(t1003) + 2900));
        t1005 = (int)((int)(a16));
        if (t1004 != (int)0) {
            t1006 = (int)(*(int*)((char*)(t1004) + 380));
            t1007 = (int)(t1006);
            t1008 = (int)((C_009cab60*)(t1007))->FUN_009cab60((unsigned int)(t1005));
            if (t1008 != (int)0) {
                t1011 = (int)(*(int*)((char*)(t1008) + 140));
                if (t1011 != (int)0) {
                    t1013 = (int)(t1011);
                    t1015 = (int)((il2c_vc0*)(t1013))->s4();
                    if ((unsigned char)(t1015) != (unsigned char)0) goto Lc17dd4;
                }
            }
        }
        t1018 = (int)(t1003);
        ((C_00c15150*)(t1018))->FUN_00c15150((unsigned int)(t1005), (unsigned int)((int)1));
        t1022 = (int)((int)(a12));
        t1023 = (int)((int)(a8));
        t1024 = (int)(t1003);
        t1025 = (int)((C_00c14f70*)(t1024))->FUN_00c14f70((unsigned int)(t1023), (unsigned int)(t1022), (unsigned int)(t1005));
        return (int)(t1025);
    }
    t1030 = (int)((int)(a20));
    t1031 = (int)((int)(a16));
    t1032 = (int)(t1003);
    ((C_00c15150*)(t1032))->FUN_00c15150((unsigned int)(t1031), (unsigned int)(t1030));
    Lc17dd4:;
    t1037 = (int)((int)0);
    return (int)(t1037);
}
