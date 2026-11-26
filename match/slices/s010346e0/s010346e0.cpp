// 0x010346e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01033de0/s01033de0.cpp, src/game/SPGonzago/SPSpaceGfx.cpp.

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
    virtual int s9(int, int);
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
    virtual int s10(int);
};

extern "C" unsigned char g_016df330[];
extern "C" unsigned char g_016df3d8[];
struct C_00542b80 { int FUN_00542b80(unsigned int); };

// @ 0x010346e0
extern "C" void __fastcall FUN_010346e0(char* self, int edx_unused)
{
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1011;
    int v_l4;
    int t1015;
    int t1016;
    unsigned char t7;
    int t1017;
    int t1022;
    int t11;
    int t1023;
    int t12;
    int t1024;
    t1005 = (int)((int)(self));
    t1006 = (int)((int)0);
    do {
        t1007 = (int)((int)0);
        t1008 = (int)((int)0);
        switch ((unsigned int)(t1006)) { case 0: goto L1034700; case 1: goto L103470a; case 2: goto L1034714; case 3: goto L103471e; default: goto L1034726; }
        goto L1034700;
        goto L103470a;
        goto L1034714;
        goto L103471e;
        goto L1034726;
        L1034700:;
        t1007 = (int)((int)26603522);
        t1008 = (int)(t1007 + (int)(-1));
        goto L1034726;
        L103470a:;
        t1007 = (int)((int)26603524);
        t1008 = (int)(t1007 + (int)(-1));
        goto L1034726;
        L1034714:;
        t1007 = (int)((int)26603528);
        t1008 = (int)(t1007 + (int)(-1));
        goto L1034726;
        L103471e:;
        t1007 = (int)((int)26603526);
        t1008 = (int)(t1007 + (int)(-1));
        L1034726:;
        t1009 = (int)(*(int*)((char*)(t1005) + 316));
        if (t1009 != (int)0) {
            t1011 = (int)((int)&v_l4);
            t1015 = (int)((il2c_vc0*)(t1009))->s9((int)(t1007), (int)(t1011));
            if ((unsigned char)(t1015) != (unsigned char)0) {
                t1016 = (int)(v_l4);
                if ((unsigned short)*(unsigned short*)((char*)(t1016) + 18) == (unsigned short)13) {
                    t7 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1016) + 16) & (unsigned char)48);
                    if (t7 != (unsigned char)0) {
                        t1016 = (int)(*(int*)((char*)(t1016)));
                    }
                    *(float*)((char*)((t1006)*4) + (int)g_016df330) = (float)(*(float*)((char*)(t1016)));
                }
            }
        }
        t1017 = (int)(*(int*)((char*)(t1005) + 316));
        t1022 = (int)((il2c_vc1*)(t1017))->s10((int)(t1008));
        t11 = (int)(t1006 << (int)2);
        t1023 = (int)(t1006 + t11);
        t12 = (int)(t1023 << (int)2);
        t1024 = (int)(t12 + (int)g_016df3d8);
        ((C_00542b80*)(t1024))->FUN_00542b80((unsigned int)(t1022));
        t1006 = (int)(t1006 + (int)1);
    } while (t1006 < (int)4);
    return;
}
