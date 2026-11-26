// 0x00ebbcd0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ebb4c0/s00ebb4c0.cpp.

// lifted by il2c_lift + l2c_search (ref@t1002); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
};

extern "C" unsigned char g_01464450[];
extern "C" unsigned char g_01465d54[];

// @ 0x00ebbcd0
extern "C" int __fastcall FUN_00ebbcd0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    unsigned char t1011;
    int t1012;
    int t1013;
    int t1019;
    int t1026;
    t1002 = (int)((int)(self));
    int& t1002_r = t1002;
    t1004 = (int)((int)(a4));
    t1005 = (int)(*(int*)((char*)(t1004)));
    *(int*)((char*)(t1002_r)) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1004) + 4));
    *(int*)((char*)(t1002_r) + 4) = (int)(t1006);
    *(float*)((char*)(t1002_r) + 8) = (float)(*(float*)((char*)(t1004) + 8));
    *(float*)((char*)(t1002_r) + 12) = (float)(*(float*)((char*)(t1004) + 12));
    *(float*)((char*)(t1002_r) + 16) = (float)(*(float*)((char*)(t1004) + 16));
    *(float*)((char*)(t1002_r) + 20) = (float)(*(float*)((char*)(t1004) + 20));
    *(float*)((char*)(t1002_r) + 24) = (float)(*(float*)((char*)(t1004) + 24));
    *(float*)((char*)(t1002_r) + 28) = (float)(*(float*)((char*)(t1004) + 28));
    *(float*)((char*)(t1002_r) + 32) = (float)(*(float*)((char*)(t1004) + 32));
    *(int*)((char*)(t1002_r) + 40) = (int)((int)g_01465d54);
    *(int*)((char*)(t1002_r) + 44) = (int)((int)0);
    t1007 = (int)(*(int*)((char*)(t1004) + 48));
    *(int*)((char*)(t1002_r) + 48) = (int)(t1007);
    t1008 = (int)(*(int*)((char*)(t1004) + 52));
    *(int*)((char*)(t1002_r) + 52) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1004) + 56));
    *(int*)((char*)(t1002_r) + 56) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1004) + 60));
    *(int*)((char*)(t1002_r) + 60) = (int)(t1010);
    t1011 = (unsigned char)(*(unsigned char*)((char*)(t1004) + 64));
    *(unsigned char*)((char*)(t1002_r) + 64) = (unsigned char)(t1011);
    t1012 = (int)(*(int*)((char*)(t1004) + 68));
    *(int*)((char*)(t1002_r) + 68) = (int)(t1012);
    *(int*)((char*)(t1002_r) + 40) = (int)((int)g_01464450);
    t1013 = (int)(*(int*)((char*)(t1004) + 72));
    *(int*)((char*)(t1002_r) + 72) = (int)(t1013);
    if (t1013 != (int)0) {
        ((il2c_vc0*)(t1013))->s0();
    }
    t1019 = (int)(*(int*)((char*)(t1004) + 76));
    *(int*)((char*)(t1002_r) + 76) = (int)(t1019);
    if (t1019 != (int)0) {
        ((il2c_vc1*)(t1019))->s0();
    }
    t1026 = (int)(t1002_r);
    return (int)(t1026);
}
