// 0x008e2b90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/Document.cpp, match/slices/s008e1d50/s008e1d50.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2(int);
};

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_01436ddc[];
struct C_00620230 { void FUN_00620230(); };
struct C_008e2b20 { void FUN_008e2b20(); };
struct C_00928dc0 { int FUN_00928dc0(); };

// @ 0x008e2b90
extern "C" void __fastcall FUN_008e2b90(char* self, int edx_unused)
{
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1009;
    int t1014;
    int t1015;
    int t1019;
    int t1023;
    int t1027;
    int t1031;
    int t1035;
    t1003 = (int)((int)(self));
    t1005 = (int)(t1003 + (int)256);
    *(int*)((char*)(t1003)) = (int)((int)g_01436ddc);
    if ((int)*(int*)((char*)(t1005) + 4) != t1005) {
        goto L8e2bb0;
        L8e2bb0:;
        t1006 = (int)(*(int*)((char*)(t1003) + 52));
        t1007 = (int)(*(int*)((char*)(t1003) + 260));
        t1009 = (int)(*(int*)((char*)(t1007) + 20));
        ((il2c_vc0*)(t1006))->s2((int)(t1009));
        if ((int)*(int*)((char*)(t1005) + 4) != t1005) goto L8e2bb0;
    }
    t1014 = (int)(t1003 + (int)8);
    t1015 = (int)(t1014);
    ((C_00928dc0*)(t1015))->FUN_00928dc0();
    t1019 = (int)(t1003 + (int)264);
    ((C_008e2b20*)(t1019))->FUN_008e2b20();
    t1023 = (int)(t1005);
    ((C_00620230*)(t1023))->FUN_00620230();
    t1027 = (int)(t1003 + (int)168);
    ((C_008e2b20*)(t1027))->FUN_008e2b20();
    t1031 = (int)(t1003 + (int)80);
    ((C_008e2b20*)(t1031))->FUN_008e2b20();
    t1035 = (int)(t1014);
    ((C_00928dc0*)(t1035))->FUN_00928dc0();
    *(int*)((char*)(t1003)) = (int)((int)g_013eb938);
    return;
}
