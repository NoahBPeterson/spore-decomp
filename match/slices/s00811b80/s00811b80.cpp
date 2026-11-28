// 0x00811b80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008117f0/s008117f0.cpp, src/game/Spui/SPUILayout.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4(int, int);
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4(int, int);
};

struct C_00811b30 { void FUN_00811b30(); };
extern "C" int __cdecl FUN_00962be0(...);

// @ 0x00811b80
extern "C" void __fastcall FUN_00811b80(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    unsigned char t6;
    int t1018;
    int t1023;
    int t1024;
    int v_l24[3];
    int v_l12[3];
    int t1025;
    int t1028;
    int t1029;
    int t1033;
    int t1036;
    t1003 = (int)((int)(self));
    t1004 = (int)(t1003 + (int)(-8));
    t1005 = (int)(t1004);
    ((C_00811b30*)(t1005))->FUN_00811b30();
    t1009 = (int)(*(int*)((char*)(t1003) + 140));
    if (t1009 != (int)0) {
        t1010 = (int)(*(int*)((char*)(t1003) + 136));
        t1011 = (int)(*(int*)((char*)(t1003) + 144));
        ((void (__cdecl*)(int, int, int))(t1009))((int)(t1011), (int)(t1010), (int)((int)1));
    }
    t1015 = (int)FUN_00962be0();
    t6 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1004) + 32) & (unsigned char)1);
    if (t6 != (unsigned char)0) {
        t1018 = (int)(*(int*)((char*)(t1004) + 12));
        t1015 = (int)((il2c_vc0*)(t1018))->s4((int)((int)801054808));
        *(int*)((char*)(t1004) + 16) = (int)(t1015);
        if (t1015 != (int)0) {
            t1023 = (int)(*(int*)((char*)(t1004) + 20));
            t1024 = (int)(*(int*)((char*)(t1004) + 28));
            (*(int*)&v_l24[0]) = (int)(t1023);
            (*(int*)&v_l12[0]) = (int)(t1023);
            (*(int*)&v_l24[2]) = (int)(t1024);
            (*(int*)&v_l12[2]) = (int)(t1024);
            t1025 = (int)(t1004 + (int)8);
            (*(int*)&v_l24[1]) = (int)((int)(-272784385));
            (*(int*)&v_l12[1]) = (int)((int)84887345);
            t1028 = (int)((int)&v_l24);
            t1029 = (int)(t1015);
            ((il2c_vc1*)(t1029))->s4((int)(t1028), (int)(t1025));
            t1033 = (int)(*(int*)((char*)(t1004) + 16));
            t1036 = (int)((int)&v_l12);
            t1015 = (int)((il2c_vc2*)(t1033))->s4((int)(t1036), (int)(t1025));
        }
    }
    return;
}
