// 0x00b60920: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b60110/s00b60110.cpp.

extern "C" unsigned char g_01654c10[];
extern "C" unsigned char g_016c7aa4[];
struct C_0083b9d0 { void FUN_0083b9d0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00b5b800(...);
struct C_00f33b50 { int FUN_00f33b50(unsigned int); };

// @ 0x00b60920
extern "C" int __fastcall FUN_00b60920(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int t1005;
    int t1007;
    int t1011;
    int t1012;
    int v_l12[3];
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    unsigned char t5;
    unsigned char t7;
    int t1019;
    int t1020;
    unsigned char t9;
    int t1021;
    int t1022;
    unsigned char t11;
    int t1023;
    int t1024;
    unsigned char t13;
    int t1025;
    int t1026;
    unsigned char t15;
    unsigned char t17;
    int t1027;
    int t1028;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 4));
    t1005 = (int)((int)(a4));
    t1007 = (int)(t1003 + (int)16);
    ((C_0083b9d0*)(t1007))->FUN_0083b9d0((unsigned int)(t1005), (unsigned int)(t1004));
    t1011 = (int)((int)(*(int*)g_016c7aa4));
    t1012 = (int)((int)0);
    (*(int*)&v_l12[1]) = (int)(t1012);
    (*(int*)&v_l12[2]) = (int)(t1012);
    (*(int*)&v_l12[0]) = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1011) + 24));
    t1014 = (int)FUN_00b5b800();
    if (t1014 == (int)g_01654c10) {
        t1014 = (int)(*(int*)((char*)(t1003) + 128));
        t1017 = (int)(t1014);
        t1018 = (int)((unsigned int)(t1017) >> (int)6);
        t5 = (unsigned char)((unsigned char)(t1018) & (unsigned char)1);
        if (t5 != (unsigned char)0) {
            (*(int*)&v_l12[0]) = (int)(t1012);
            goto Lb609e2;
        }
        t7 = (unsigned char)((unsigned char)(t1014) & (unsigned char)1);
        if (t7 != (unsigned char)0) {
            (*(int*)&v_l12[0]) = (int)((int)695925509);
            goto Lb609e2;
        }
        t1019 = (int)(t1014);
        t1020 = (int)((unsigned int)(t1019) >> (int)1);
        t9 = (unsigned char)((unsigned char)(t1020) & (unsigned char)1);
        if (t9 != (unsigned char)0) {
            (*(int*)&v_l12[0]) = (int)((int)932831954);
            goto Lb609e2;
        }
        t1021 = (int)(t1014);
        t1022 = (int)((unsigned int)(t1021) >> (int)2);
        t11 = (unsigned char)((unsigned char)(t1022) & (unsigned char)1);
        if (t11 != (unsigned char)0) {
            (*(int*)&v_l12[0]) = (int)((int)(-354780398));
            goto Lb609e2;
        }
        t1023 = (int)(t1014);
        t1024 = (int)((unsigned int)(t1023) >> (int)3);
        t13 = (unsigned char)((unsigned char)(t1024) & (unsigned char)1);
        if (t13 != (unsigned char)0) {
            (*(int*)&v_l12[0]) = (int)((int)(-707873697));
            goto Lb609e2;
        }
        t1025 = (int)(t1014);
        t1026 = (int)((unsigned int)(t1025) >> (int)4);
        t15 = (unsigned char)((unsigned char)(t1026) & (unsigned char)1);
        if (t15 != (unsigned char)0) {
            (*(int*)&v_l12[0]) = (int)((int)(-1205418159));
            goto Lb609e2;
        }
        t1014 = (int)((unsigned int)(t1014) >> (int)5);
        t17 = (unsigned char)((unsigned char)(t1014) & (unsigned char)1);
        if (t17 != (unsigned char)0) {
            (*(int*)&v_l12[0]) = (int)((int)533679239);
        }
        Lb609e2:;
        if (t1013 != t1012) {
            t1027 = (int)((int)&v_l12);
            t1028 = (int)(t1013);
            t1014 = (int)((C_00f33b50*)(t1028))->FUN_00f33b50((unsigned int)(t1027));
        }
    }
    return (int)(t1014);
}
