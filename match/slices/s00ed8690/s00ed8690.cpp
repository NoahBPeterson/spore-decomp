// 0x00ed8690: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/_at_00ed0000.cpp, match/slices/s00ed8490/s00ed8490.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};

extern "C" unsigned char g_01186577[];
struct C_006c0200 { int FUN_006c0200(); };
struct C_00b1f9b0 { int FUN_00b1f9b0(); };
extern "C" int __cdecl FUN_00b3d300(...);
struct C_00c8ad30 { int FUN_00c8ad30(unsigned int, unsigned int); };

// @ 0x00ed8690
extern "C" void __cdecl FUN_00ed8690(void)
{
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1017;
    int t1020;
    int t1021;
    int t1022;
    int t1025;
    int t1029;
    int t1033;
    int t1037;
    int t1041;
    int t1045;
    int t1046;
    int t1047;
    int t1050;
    t1005 = (int)FUN_00b3d300();
    t1006 = (int)(t1005);
    t1009 = (int)((C_00b1f9b0*)(t1006))->FUN_00b1f9b0();
    t1010 = (int)(*(int*)((char*)(t1009)));
    if (t1010 != (int)0) {
        t1011 = (int)(t1010 + (int)(-12));
    } else {
        t1011 = (int)((int)0);
    }
    t1012 = (int)(t1009 + (int)(-12));
    if (t1011 != t1012) {
        do {
            if (t1011 != (int)0) {
                t1017 = (int)(t1011);
                t1020 = (int)((il2c_vc0*)(t1017))->s3((int)((int)g_01186577));
                t1021 = (int)(t1020);
            } else {
                t1021 = (int)((int)0);
            }
            t1022 = (int)(t1011);
            t1009 = (int)((C_006c0200*)(t1022))->FUN_006c0200();
            if (t1009 != (int)0) {
                t1025 = (int)(t1021);
                ((C_00c8ad30*)(t1025))->FUN_00c8ad30((unsigned int)((int)226046093), (unsigned int)((int)0));
                t1029 = (int)(t1021);
                ((C_00c8ad30*)(t1029))->FUN_00c8ad30((unsigned int)((int)39725928), (unsigned int)((int)0));
                t1033 = (int)(t1021);
                ((C_00c8ad30*)(t1033))->FUN_00c8ad30((unsigned int)((int)(-508006422)), (unsigned int)((int)0));
                t1037 = (int)(t1021);
                ((C_00c8ad30*)(t1037))->FUN_00c8ad30((unsigned int)((int)(-22231953)), (unsigned int)((int)0));
                t1041 = (int)(t1021);
                ((C_00c8ad30*)(t1041))->FUN_00c8ad30((unsigned int)((int)(-1383486083)), (unsigned int)((int)0));
                t1045 = (int)((int)0);
                do {
                    t1046 = (int)(t1045 + (int)(-890007309));
                    t1047 = (int)(t1021);
                    t1009 = (int)((C_00c8ad30*)(t1047))->FUN_00c8ad30((unsigned int)(t1046), (unsigned int)((int)0));
                    t1045 = (int)(t1045 + (int)1);
                } while ((unsigned int)(t1045) < (unsigned int)3);
            }
            t1050 = (int)(*(int*)((char*)(t1011) + 12));
            if (t1050 != (int)0) {
                t1011 = (int)(t1050 + (int)(-12));
            } else {
                t1011 = (int)((int)0);
            }
        } while (t1011 != t1012);
    }
    return;
}
