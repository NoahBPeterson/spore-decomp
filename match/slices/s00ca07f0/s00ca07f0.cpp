// 0x00ca07f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPVehicle.cpp, match/slices/s00c9ffd0/s00c9ffd0.cpp.

extern "C" unsigned char g_01466c38[];
extern "C" unsigned char g_01570858[];
struct C_00695b40 { int FUN_00695b40(unsigned int, unsigned int, unsigned int); };

// @ 0x00ca07f0
extern "C" bool __cdecl FUN_00ca07f0(int a4, int a8)
{
    int t1000;
    int t1002;
    int t1004;
    int t1006;
    int t1007;
    bool t1012;
    t1000 = (int)((int)(a8));
    t1002 = (int)(*(int*)((char*)(t1000)));
    t1004 = (int)(*(int*)((char*)(t1000) + 4));
    if (t1002 != t1004) {
        t1006 = (int)((int)(a4));
        do {
            t1000 = (int)(*(int*)((char*)(t1002)));
            if (t1000 != (int)0) {
                t1007 = (int)(t1006);
                t1000 = (int)((C_00695b40*)(t1007))->FUN_00695b40((unsigned int)(t1000), (unsigned int)((int)g_01570858), (unsigned int)((int)g_01466c38));
            }
            t1002 = (int)(t1002 + (int)4);
        } while (t1002 != t1004);
    }
    t1012 = true;
    return (bool)(t1012);
}
