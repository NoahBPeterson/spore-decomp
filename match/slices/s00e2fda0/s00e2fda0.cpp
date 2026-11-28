// 0x00e2fda0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00e20000.cpp, match/slices/s00e2f6e0/s00e2f6e0.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
};

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f09b4[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00e2fda0
extern "C" int __stdcall FUN_00e2fda0(int a4)
{
    int t1002;
    int t1005;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    unsigned char t1015;
    int t1016;
    t1002 = (int)FUN_00f473a0((unsigned int)((int)24), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    t1005 = (int)(t1002);
    if (t1005 != (int)0) {
        t1007 = (int)((int)(a4));
        t1008 = (int)(*(int*)((char*)(t1007)));
        *(int*)((char*)(t1005)) = (int)(t1008);
        t1009 = (int)(*(int*)((char*)(t1007) + 4));
        *(int*)((char*)(t1005) + 4) = (int)(t1009);
        t1010 = (int)(*(int*)((char*)(t1007) + 8));
        *(int*)((char*)(t1005) + 8) = (int)(t1010);
        if (t1010 != (int)0) {
            ((il2c_vc0*)(t1010))->s0();
        }
        t1015 = (unsigned char)(*(unsigned char*)((char*)(t1007) + 12));
        *(unsigned char*)((char*)(t1005) + 12) = (unsigned char)(t1015);
        t1016 = (int)(*(int*)((char*)(t1007) + 16));
        *(int*)((char*)(t1005) + 16) = (int)(t1016);
        if (t1016 != (int)0) {
            ((il2c_vc1*)(t1016))->s0();
        }
        t1002 = (int)(t1005);
    }
    *(int*)((char*)(t1005) + 20) = (int)((int)0);
    return (int)(t1002);
}
