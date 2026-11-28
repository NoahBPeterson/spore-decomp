// 0x00816b90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00815dd0/s00815dd0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual int s7();
};

extern "C" unsigned char g_01510d08[];
extern "C" unsigned char g_01511161[];
struct C_005ff1c0 { int FUN_005ff1c0(); };
struct C_008105b0 { int FUN_008105b0(unsigned int, unsigned int); };
struct C_00816990 { int FUN_00816990(); };

// @ 0x00816b90
// @ 0x00816b90
extern "C" bool __fastcall FUN_00816b90(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1006;
    int t1008;
    int t1011;
    int t1014;
    bool t1019;
    int t1021;
    int t1007;
    int t1024;
    int t1027;
    bool t1031;
    unsigned char t17;
    int t1004;
    int t1033;
    int t1036;
    bool t1041;
    int t1043;
    bool t1047;
    t1002 = (int)((int)(a8));
    t1003 = (int)(*(int*)((char*)(t1002) + 8));
    t1006 = (int)((int)(self));
    switch ((unsigned int)(t1003)) { case 1: goto L816c25; case 12: goto L816be9; case 678582774: goto L816bb0; default: goto L816c1e; }
    goto L816bb0;
    goto L816be9;
    goto L816c1e;
    goto L816c25;
    L816bb0:;
    t1008 = (int)(*(int*)((char*)(t1002)));
    t1011 = (int)((il2c_vc0*)(t1008))->s7();
    if ((unsigned int)(t1011) >= (unsigned int)84966167) {
        if ((unsigned int)(t1011) <= (unsigned int)84966170) goto L816c83;
        if (t1011 == (int)(-15)) goto L816c83;
    }
    t1014 = (int)(t1006);
    *(int*)((char*)(t1006) + 48) = (int)((int)g_01510d08);
    ((C_00816990*)(t1014))->FUN_00816990();
    t1019 = true;
    return (bool)(t1019);
    L816be9:;
    if ((int)*(int*)((char*)(t1006) + 52) != (int)0) {
        t1021 = (int)(t1006 + (int)56);
        t1007 = (int)((C_005ff1c0*)(t1021))->FUN_005ff1c0();
        if ((unsigned char)(t1007) != (unsigned char)0) {
            t1024 = (int)(t1006 + (int)12);
            t1007 = (int)((C_008105b0*)(t1024))->FUN_008105b0((unsigned int)((int)103911032), (unsigned int)((int)1));
            if ((int)(a4) == t1007) {
                t1027 = (int)(t1006);
                *(int*)((char*)(t1006) + 48) = (int)((int)g_01511161);
                t1007 = (int)((C_00816990*)(t1027))->FUN_00816990();
            }
        }
    }
    L816c1e:;
    t1031 = false;
    return (bool)(t1031);
    L816c25:;
    t17 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1002) + 20) & (unsigned char)71);
    if (t17 != (unsigned char)0) goto L816c8d;
    if ((int)*(int*)((char*)(t1002) + 16) == (int)13) {
        if ((unsigned char)*(unsigned char*)((char*)(t1006) + 44) != (unsigned char)0) {
            *(int*)((char*)(t1006) + 48) = (int)((int)(-15));
        } else {
            t1004 = (int)(*(int*)((char*)(t1006) + 36));
            if (t1004 == (int)(-1)) goto L816c55;
            t1033 = (int)(t1004 + (int)84966167);
            *(int*)((char*)(t1006) + 48) = (int)(t1033);
        }
        t1004 = (int)((C_00816990*)((int)(self)))->FUN_00816990();
    }
    L816c55:;
    if ((int)*(int*)((char*)(t1002) + 16) != (int)27) goto L816c8d;
    if ((unsigned char)*(unsigned char*)((char*)(t1006) + 44) != (unsigned char)0) {
        t1036 = (int)(t1006);
        *(int*)((char*)(t1006) + 48) = (int)((int)(-15));
        ((C_00816990*)(t1036))->FUN_00816990();
        t1041 = true;
        return (bool)(t1041);
    }
    t1004 = (int)(*(int*)((char*)(t1006) + 40));
    if (t1004 == (int)(-1)) goto L816c8d;
    t1011 = (int)(t1004 + (int)84966167);
    L816c83:;
    t1043 = (int)(t1006);
    *(int*)((char*)(t1006) + 48) = (int)(t1011);
    t1004 = (int)((C_00816990*)(t1043))->FUN_00816990();
    L816c8d:;
    t1047 = true;
    return (bool)(t1047);
}
