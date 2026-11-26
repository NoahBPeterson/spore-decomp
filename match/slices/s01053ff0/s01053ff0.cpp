// 0x01053ff0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPToolStrategies.cpp, match/slices/s010527f0/s010527f0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};

struct C_00a1ad60 { int FUN_00a1ad60(); };
extern "C" int __cdecl FUN_00b3d3c0(...);
struct C_00b78860 { int FUN_00b78860(); };
struct C_00cb3c70 { void FUN_00cb3c70(); };
struct C_00ff3f10 { int FUN_00ff3f10(); };
extern "C" int __cdecl FUN_01002bd0(...);
struct C_01003480 { void FUN_01003480(); };
struct C_0104cd50 { int FUN_0104cd50(); };

// @ 0x01053ff0
extern "C" bool __stdcall FUN_01053ff0(int a4)
{
    int t1003;
    int t1004;
    int t1007;
    int t1008;
    int t1011;
    int t1014;
    int t1015;
    int t1020;
    int t1021;
    int t1027;
    int t1031;
    int t1037;
    int t1040;
    int t1044;
    int t1045;
    bool t1048;
    t1003 = (int)FUN_01002bd0();
    t1004 = (int)(t1003);
    t1007 = (int)((C_00a1ad60*)(t1004))->FUN_00a1ad60();
    t1008 = (int)(t1007);
    t1011 = (int)((C_00ff3f10*)(t1008))->FUN_00ff3f10();
    if (t1011 == (int)0) {
        t1014 = (int)FUN_01002bd0();
        t1015 = (int)(t1014);
        ((C_01003480*)(t1015))->FUN_01003480();
    }
    t1020 = (int)((int)(a4));
    t1021 = (int)(*(int*)((char*)(t1020) + 300));
    *(int*)((char*)(t1020) + 300) = (int)((int)0);
    if (t1021 != (int)0) {
        ((il2c_vc0*)(t1021))->s1();
    }
    t1027 = (int)(*(int*)((char*)(t1020) + 292));
    if (t1027 != (int)0) {
        ((C_00cb3c70*)(t1027))->FUN_00cb3c70();
        t1031 = (int)(*(int*)((char*)(t1020) + 292));
        if (t1031 != (int)0) {
            *(int*)((char*)(t1020) + 292) = (int)((int)0);
            ((il2c_vc1*)(t1031))->s1();
        }
    }
    t1037 = (int)(t1020);
    t1040 = (int)((C_0104cd50*)(t1037))->FUN_0104cd50();
    if ((unsigned char)(t1040) != (unsigned char)0) {
        t1044 = (int)FUN_00b3d3c0();
        t1045 = (int)(t1044);
        t1040 = (int)((C_00b78860*)(t1045))->FUN_00b78860();
    }
    t1048 = true;
    return (bool)(t1048);
}
