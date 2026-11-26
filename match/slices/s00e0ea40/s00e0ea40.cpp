// 0x00e0ea40: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e0df70/s00e0df70.cpp, src/game/SPGonzago/SPUIMinimapWin.cpp.

// lifted by il2c_lift + l2c_search (ref@t1006); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
};


// @ 0x00e0ea40
extern "C" int __fastcall FUN_00e0ea40(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1006;
    unsigned char t1007;
    int t1008;
    int t1010;
    int t1013;
    int t1019;
    int t1023;
    int t1024;
    int t1027;
    int t1033;
    int t1038;
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1001)));
    t1006 = (int)((int)(self));
    int& t1006_r = t1006;
    *(int*)((char*)(t1006_r)) = (int)(t1002);
    t1007 = (unsigned char)(*(unsigned char*)((char*)(t1001) + 4));
    *(unsigned char*)((char*)(t1006_r) + 4) = (unsigned char)(t1007);
    t1008 = (int)(*(int*)((char*)(t1006_r) + 8));
    t1010 = (int)(*(int*)((char*)(t1001) + 8));
    if (t1010 != t1008) {
        if (t1010 != (int)0) {
            t1013 = (int)(t1010);
            ((il2c_vc0*)(t1013))->s0();
        }
        *(int*)((char*)(t1006_r) + 8) = (int)(t1010);
        if (t1008 != (int)0) {
            t1019 = (int)(t1008);
            ((il2c_vc1*)(t1019))->s1();
        }
    }
    t1023 = (int)(*(int*)((char*)(t1001) + 12));
    t1024 = (int)(*(int*)((char*)(t1006_r) + 12));
    if (t1023 != t1024) {
        if (t1023 != (int)0) {
            t1027 = (int)(t1023);
            ((il2c_vc2*)(t1027))->s0();
        }
        *(int*)((char*)(t1006_r) + 12) = (int)(t1023);
        if (t1024 != (int)0) {
            t1033 = (int)(t1024);
            ((il2c_vc3*)(t1033))->s1();
        }
    }
    t1038 = (int)(t1006_r);
    return (int)(t1038);
}
