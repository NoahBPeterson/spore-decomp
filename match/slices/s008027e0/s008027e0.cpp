// 0x008027e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008019f0/s008019f0.cpp, src/game/Spui/SPUICursorManager.cpp.

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
    virtual void s31();
    virtual int s32(int);
};

extern "C" int __cdecl FUN_0067dcf0(...);
struct C_008026e0 { int FUN_008026e0(unsigned int); };

// @ 0x008027e0
extern "C" void __fastcall FUN_008027e0(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1017;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 64) != (unsigned char)0) {
        if ((int)*(int*)((char*)(t1002) + 88) > (int)0) {
            t1003 = (int)(*(int*)((char*)(t1002) + 60));
            goto L80280c;
        }
        t1003 = (int)(*(int*)((char*)(t1002) + 48));
        if (t1003 == (int)0) {
            if ((unsigned char)*(unsigned char*)((char*)(t1002) + 66) != (unsigned char)(t1003)) {
                t1003 = (int)(*(int*)((char*)(t1002) + 44));
            } else {
                t1003 = (int)(*(int*)((char*)(t1002) + 52));
            }
            if (t1003 == (int)0) goto L80280f;
        }
        L80280c:;
        *(int*)((char*)(t1002) + 56) = (int)(t1003);
        L80280f:;
        t1004 = (int)(*(int*)((char*)(t1002) + 56));
        t1006 = (int)((int)0);
        if (t1004 != (int)0) {
            if ((int)*(int*)((char*)(t1004) + 24) == t1006) {
                t1007 = (int)(*(int*)((char*)(t1004)));
                if (t1007 == (int)*(int*)((char*)(t1004) + 4)) goto L802837;
                t1008 = (int)(t1002);
                t1009 = (int)((C_008026e0*)(t1008))->FUN_008026e0((unsigned int)(t1004));
                if ((unsigned char)(t1009) == (unsigned char)0) goto L802837;
            }
            t1012 = (int)(*(int*)((char*)(t1002) + 56));
            t1006 = (int)(*(int*)((char*)(t1012) + 24));
        }
        L802837:;
        t1013 = (int)FUN_0067dcf0();
        t1017 = (int)(t1013);
        ((il2c_vc0*)(t1017))->s32((int)(t1006));
    }
    return;
}
