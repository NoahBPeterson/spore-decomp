// 0x0089b250: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0089b250/s0089b250.cpp.

// lifted by il2c_lift + l2c_search (swap@24); CI scorer MATCH; corpus status nonmatching/residual
struct C_0089a5d0 { void FUN_0089a5d0(); };

// @ 0x0089b250
extern "C" int __fastcall FUN_0089b250(char* self, int edx_unused, int a4, int a8, int a12, int a16)
{
    int t1004;
    int t1005;
    int t1009;
    unsigned char t1010;
    unsigned char t1011;
    int t1012;
    int t1013;
    unsigned char t1015;
    unsigned char t1017;
    int t2;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    t1004 = (int)((int)(self));
    t1005 = (int)(t1004 + (int)976);
    ((C_0089a5d0*)(t1005))->FUN_0089a5d0();
    t1009 = (int)(*(int*)((char*)(t1004) + 980));
    t1011 = (unsigned char)((unsigned char)(a16));
    t1010 = (unsigned char)((unsigned char)(a12));
    t1012 = (int)(t1009 - (int)44);
    *(int*)((char*)(t1012)) = (int)((int)1);
    t1013 = (int)(*(int*)((char*)(t1004) + 1036));
    *(int*)((char*)(t1012) + 4) = (int)(t1013);
    t1015 = (unsigned char)((int)(t1010) != (int)((int)0));
    t1017 = (unsigned char)((int)(t1011) != (int)((int)0));
    t2 = (int)((int)(t1015) + (int)(t1017));
    t1018 = (int)(t2 + (int)1);
    *(int*)((char*)(t1012) + 8) = (int)(t1018);
    t1019 = (int)(*(int*)((char*)(t1004) + 956));
    *(int*)((char*)(t1012) + 12) = (int)(t1019);
    t1020 = (int)((int)(a4));
    *(int*)((char*)(t1012) + 16) = (int)(t1020);
    t1021 = (int)((int)(a8));
    t1022 = (int)(*(int*)((char*)(t1021)));
    *(int*)((char*)(t1012) + 20) = (int)(t1022);
    t1023 = (int)(*(int*)((char*)(t1021) + 4));
    *(int*)((char*)(t1012) + 24) = (int)(t1023);
    t1024 = (int)(*(int*)((char*)(t1021) + 8));
    *(int*)((char*)(t1012) + 28) = (int)(t1024);
    t1025 = (int)(*(int*)((char*)(t1021) + 12));
    *(int*)((char*)(t1012) + 32) = (int)(t1025);
    t1026 = (int)(*(int*)((char*)(t1021) + 16));
    *(unsigned char*)((char*)(t1012) + 40) = (unsigned char)(t1010);
    *(int*)((char*)(t1012) + 36) = (int)(t1026);
    *(unsigned char*)((char*)(t1012) + 41) = (unsigned char)(t1011);
    *(int*)((char*)(t1004) + 1032) += (int)1;
    t1027 = (int)(*(int*)((char*)(t1012) + 8));
    *(int*)((char*)(t1004) + 1036) += t1027;
    if ((int)*(int*)((char*)(t1004) + 1044) == (int)2) {
        *(int*)((char*)(t1004) + 1044) = (int)((int)0);
    }
    return (int)(t1026);
}
