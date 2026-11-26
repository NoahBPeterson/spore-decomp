// 0x00c048c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00c00000.cpp, match/slices/s00c045a0/s00c045a0.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
};


// @ 0x00c048c0
extern "C" int __fastcall FUN_00c048c0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    unsigned char t1006;
    unsigned char t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1018;
    int t1025;
    t1002 = (int)((int)(self));
    t1004 = (int)((int)(a4));
    *(float*)((char*)(t1002)) = (float)(*(float*)((char*)(t1004)));
    t1006 = (unsigned char)(*(unsigned char*)((char*)(t1004) + 4));
    *(unsigned char*)((char*)(t1002) + 4) = (unsigned char)(t1006);
    t1007 = (unsigned char)(*(unsigned char*)((char*)(t1004) + 5));
    *(unsigned char*)((char*)(t1002) + 5) = (unsigned char)(t1007);
    t1008 = (int)(*(int*)((char*)(t1004) + 8));
    *(int*)((char*)(t1002) + 8) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1004) + 8));
    *(int*)((char*)(t1002) + 8) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1004) + 8));
    *(int*)((char*)(t1002) + 8) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1004) + 8));
    *(int*)((char*)(t1002) + 8) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1004) + 12));
    *(int*)((char*)(t1002) + 12) = (int)(t1012);
    if (t1012 != (int)0) {
        ((il2c_vc0*)(t1012))->s0();
    }
    t1018 = (int)(*(int*)((char*)(t1004) + 16));
    *(int*)((char*)(t1002) + 16) = (int)(t1018);
    if (t1018 != (int)0) {
        ((il2c_vc1*)(t1018))->s0();
    }
    t1025 = (int)(t1002);
    return (int)(t1025);
}
