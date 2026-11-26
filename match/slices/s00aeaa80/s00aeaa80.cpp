// 0x00aeaa80: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00aea5d0/s00aea5d0.cpp.

// lifted by il2c_lift + l2c_search (swap@55); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" void __cdecl FUN_006782c0(...);
extern "C" int __stdcall FUN_00b3d300(unsigned int);
struct C_00b3d3e0 { int FUN_00b3d3e0(unsigned int, unsigned int); };
struct C_00c77bf0 { int FUN_00c77bf0(); };
struct C_00dd6d10 { void FUN_00dd6d10(); };
struct C_00f67d90 { int FUN_00f67d90(); };
struct C_01045a60 { void FUN_01045a60(); };
struct C_01046fc0 { int FUN_01046fc0(unsigned int, unsigned int); };

// @ 0x00aeaa80
extern "C" void __fastcall FUN_00aeaa80(char* self, int edx_unused, int a4, int a8, int a12, int a16)
{
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1008;
    int t1010;
    int t1011;
    int t1012;
    int t1017;
    int t1019;
    int t1021;
    int t1025;
    int t1026;
    int t1028;
    int t1030;
    int t1034;
    int t1035;
    int t1039;
    int t1040;
    int t1047;
    int t1049;
    int t1051;
    int t1053;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 36));
    t1005 = (int)(*(int*)((char*)(t1003) + 40));
    if (t1004 != t1005) {
        t1006 = (int)((int)(a16));
        t1008 = (int)((int)(a12));
        do {
            t1010 = (int)(*(int*)((char*)(t1004)));
            if ((unsigned char)*(unsigned char*)((char*)(t1010) + 48) != (unsigned char)0) {
                t1011 = (int)(*(int*)((char*)(t1010) + 24));
                if (t1011 == (int)(a4)) {
                    t1012 = (int)((int)(a8));
                    if ((int)*(int*)((char*)(t1010) + 52) == t1012) {
                        if ((int)*(int*)((char*)(t1010) + 56) == t1008) {
                            if ((int)*(int*)((char*)(t1010) + 60) == t1006) goto Laeaad2;
                        }
                    }
                }
            }
            t1004 = (int)(t1004 + (int)4);
        } while (t1004 != t1005);
        return;
        Laeaad2:;
        t1017 = (int)(*(int*)((char*)(t1010) + 20));
        t1019 = (int)((C_00b3d3e0*)(t1005))->FUN_00b3d3e0((unsigned int)(t1017), (unsigned int)((int)0));
        t1021 = (int)(t1019);
        ((C_00dd6d10*)(t1021))->FUN_00dd6d10();
        t1025 = (int)(*(int*)((char*)(t1004)));
        t1026 = (int)(*(int*)((char*)(t1025) + 16));
        t1028 = (int)((C_01046fc0*)(t1026))->FUN_01046fc0((unsigned int)(t1026), (unsigned int)((int)1));
        t1030 = (int)(t1028);
        ((C_01045a60*)(t1030))->FUN_01045a60();
        t1035 = (int)(t1004 + (int)4);
        t1034 = (int)(*(int*)((char*)(t1003) + 40));
        if ((unsigned int)(t1035) < (unsigned int)(t1034)) {
            FUN_006782c0((unsigned int)(t1035), (unsigned int)(t1034), (unsigned int)(t1004));
        }
        *(int*)((char*)(t1003) + 40) += (int)(-4);
        t1039 = (int)(*(int*)((char*)(t1003) + 40));
        t1040 = (int)(*(int*)((char*)(t1039)));
        if (t1040 != (int)0) {
            ((il2c_vc0*)(t1040))->s1();
        }
        t1047 = (int)FUN_00b3d300((unsigned int)((int)92236422));
        t1049 = (int)(t1047);
        t1051 = (int)((C_00f67d90*)(t1049))->FUN_00f67d90();
        t1053 = (int)(t1051);
        ((C_00c77bf0*)(t1053))->FUN_00c77bf0();
    }
    return;
}
