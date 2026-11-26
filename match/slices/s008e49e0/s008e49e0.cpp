// 0x008e49e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/_at_008e0000.cpp, match/slices/s008e4310/s008e4310.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2(int);
};

struct C_00429580 { void FUN_00429580(unsigned int, unsigned int); };
struct C_00fc7e50 { int FUN_00fc7e50(); };

// @ 0x008e49e0
extern "C" int __fastcall FUN_008e49e0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1021;
    int t1022;
    int t1023;
    int t10;
    int t1024;
    int t1025;
    int t1029;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 24));
    t1005 = (int)((int)(self) + (int)24);
    if (t1001 != (int)0) {
        t1006 = (int)(t1001 + (int)(-4));
    } else {
        t1006 = (int)((int)0);
    }
    t1007 = (int)((int)(a4));
    L8e49f8:;
    if (t1005 != (int)0) {
        t1008 = (int)(t1005 + (int)(-4));
    } else {
        t1008 = (int)((int)0);
    }
    if (t1006 != t1008) {
        t1009 = (int)(t1006);
        t1012 = (int)((C_00fc7e50*)(t1009))->FUN_00fc7e50();
        t1013 = (int)(t1006);
        if (t1012 == (int)1) {
            ((il2c_vc0*)(t1013))->s2((int)(t1007));
            goto L8e4a3b;
        }
        t1021 = (int)((C_00fc7e50*)(t1013))->FUN_00fc7e50();
        if (t1021 == (int)2) {
            t1022 = (int)(*(int*)((char*)(t1006) + 24));
            t1023 = (int)(*(int*)((char*)(t1006) + 28));
            t10 = (int)(t1023 << (int)1);
            t1024 = (int)(t1022 + t10);
            t1025 = (int)(t1007);
            ((C_00429580*)(t1025))->FUN_00429580((unsigned int)(t1022), (unsigned int)(t1024));
        }
        L8e4a3b:;
        t1029 = (int)(*(int*)((char*)(t1006) + 4));
        if (t1029 != (int)0) {
            t1006 = (int)(t1029 + (int)(-4));
            goto L8e49f8;
        }
        t1006 = (int)((int)0);
        goto L8e49f8;
    }
    return (int)(t1008);
}
