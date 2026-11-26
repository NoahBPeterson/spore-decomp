// 0x00810310: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUILayout.cpp, match/slices/s0080f7c0/s0080f7c0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int s4();
};
struct il2c_vc2 {
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
    virtual void s31(int, int);
};

extern "C" int __cdecl FUN_00804f50(...);

// @ 0x00810310
extern "C" bool __fastcall FUN_00810310(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1006;
    int t1010;
    int t1015;
    int t1016;
    int t1019;
    int t1022;
    int t1025;
    bool t1035;
    unsigned char t1038;
    bool t1039;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 136) != (int)0) {
        t1004 = (int)((int)(a4));
        t1006 = (int)(*(int*)((char*)(t1002) + 100));
        if (t1006 != (int)*(int*)((char*)(t1002) + 104)) {
            goto L810330;
            L810330:;
            t1010 = (int)(*(int*)((char*)(t1006)));
            t1006 = (int)(t1006 + (int)4);
            t1015 = (int)((il2c_vc0*)(t1010))->s3((int)((int)(-286359016)));
            t1016 = (int)(t1015);
            if (t1016 != (int)0) {
                t1019 = (int)(t1016);
                t1022 = (int)((il2c_vc1*)(t1019))->s4();
                if (t1022 != (int)*(int*)((char*)(t1002) + 136)) {
                    if (t1022 != (int)0) goto L810368;
                }
                t1025 = (int)(t1016);
                ((il2c_vc2*)(t1025))->s31((int)((int)1), (int)(t1004));
            }
            L810368:;
            if (t1006 != (int)*(int*)((char*)(t1002) + 104)) goto L810330;
        }
        FUN_00804f50((unsigned int)((int)1));
        *(unsigned char*)((char*)(t1002) + 140) = (unsigned char)((unsigned char)(t1004));
        t1035 = true;
        return (bool)(t1035);
    }
    t1038 = (unsigned char)((unsigned char)(a4));
    *(unsigned char*)((char*)(t1002) + 140) = (unsigned char)(t1038);
    t1039 = true;
    return (bool)(t1039);
}
