// 0x00bcab80: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bc0000.cpp, match/slices/s00bca040/s00bca040.cpp.

// lifted by il2c_lift + l2c_search (bind@t1002); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
};

extern "C" unsigned char g_01464450[];
extern "C" unsigned char g_01465d54[];
struct C_00542b80 { void FUN_00542b80(unsigned int); };

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x00bcab80
extern "C" int __fastcall FUN_00bcab80(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    unsigned char t1010;
    int t1011;
    int t1012;
    int t1017;
    int t1018;
    unsigned char t1019;
    int t1020;
    int t1021;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1032;
    int t1033;
    int t1034;
    int t1035;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    int t1047;
    t1002 = (int)((int)(self));
    t1004 = (int)((int)(a4));
    t1005 = (int)(*(int*)((char*)(t1004)));
    *(int*)((char*)(hs_bind(t1002))) = (int)(t1005);
    *(int*)((char*)(t1002) + 8) = (int)((int)g_01465d54);
    *(int*)((char*)(t1002) + 12) = (int)((int)0);
    t1006 = (int)(*(int*)((char*)(t1004) + 16));
    *(int*)((char*)(t1002) + 16) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1004) + 20));
    *(int*)((char*)(t1002) + 20) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1004) + 24));
    *(int*)((char*)(t1002) + 24) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1004) + 28));
    *(int*)((char*)(t1002) + 28) = (int)(t1009);
    t1010 = (unsigned char)(*(unsigned char*)((char*)(t1004) + 32));
    *(unsigned char*)((char*)(t1002) + 32) = (unsigned char)(t1010);
    t1011 = (int)(*(int*)((char*)(t1004) + 36));
    *(int*)((char*)(t1002) + 36) = (int)(t1011);
    *(int*)((char*)(t1002) + 8) = (int)((int)g_01464450);
    t1012 = (int)(*(int*)((char*)(t1004) + 40));
    *(int*)((char*)(t1002) + 40) = (int)(t1012);
    if (t1012 != (int)0) {
        ((il2c_vc0*)(t1012))->s0();
    }
    t1017 = (int)((int)0);
    *(float*)((char*)(t1002) + 44) = (float)(*(float*)((char*)(t1004) + 44));
    t1018 = (int)((int)0);
    *(float*)((char*)(t1002) + 48) = (float)(*(float*)((char*)(t1004) + 48));
    *(float*)((char*)(t1002) + 52) = (float)(*(float*)((char*)(t1004) + 52));
    t1019 = (unsigned char)(*(unsigned char*)((char*)(t1004) + 56));
    *(unsigned char*)((char*)(t1002) + 56) = (unsigned char)(t1019);
    t1020 = (int)(t1002 + (int)57);
    *(unsigned short*)((char*)(t1020) + 16) = (unsigned short)((unsigned short)(t1017));
    t1021 = (int)(t1004 + (int)57);
    *(unsigned short*)((char*)(t1020) + 18) = (unsigned short)((unsigned short)(t1018));
    ((C_00542b80*)(t1020))->FUN_00542b80((unsigned int)(t1021));
    t1025 = (int)(t1002 + (int)77);
    t1026 = (int)((int)0);
    *(unsigned short*)((char*)(t1025) + 16) = (unsigned short)((unsigned short)(t1026));
    t1027 = (int)(t1004 + (int)77);
    t1028 = (int)((int)0);
    *(unsigned short*)((char*)(t1025) + 18) = (unsigned short)((unsigned short)(t1028));
    ((C_00542b80*)(t1025))->FUN_00542b80((unsigned int)(t1027));
    t1032 = (int)(t1002 + (int)97);
    t1033 = (int)((int)0);
    *(unsigned short*)((char*)(t1032) + 16) = (unsigned short)((unsigned short)(t1033));
    t1034 = (int)(t1004 + (int)97);
    t1035 = (int)((int)0);
    *(unsigned short*)((char*)(t1032) + 18) = (unsigned short)((unsigned short)(t1035));
    ((C_00542b80*)(t1032))->FUN_00542b80((unsigned int)(t1034));
    t1039 = (int)(t1002 + (int)117);
    t1040 = (int)((int)0);
    t1041 = (int)((int)0);
    t1042 = (int)(t1004 + (int)117);
    *(unsigned short*)((char*)(t1039) + 16) = (unsigned short)((unsigned short)(t1040));
    *(unsigned short*)((char*)(t1039) + 18) = (unsigned short)((unsigned short)(t1041));
    ((C_00542b80*)(t1039))->FUN_00542b80((unsigned int)(t1042));
    t1047 = (int)(t1002);
    return (int)(t1047);
}
