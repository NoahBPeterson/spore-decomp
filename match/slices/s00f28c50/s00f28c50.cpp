// 0x00f28c50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPPlanetSim.cpp, match/slices/s00f28680/s00f28680.cpp.

extern "C" unsigned char g_013ec468[];
extern "C" unsigned char g_015aff90[];
struct C_005c3d90 { int FUN_005c3d90(unsigned int); };
struct C_00692f90 { void FUN_00692f90(unsigned int, unsigned int, unsigned int); };
struct C_00693e10 { int FUN_00693e10(unsigned int); };
struct C_006b5240 { void FUN_006b5240(); };
struct C_006b5430 { void FUN_006b5430(unsigned int); };
struct C_006b5770 { int FUN_006b5770(unsigned int, unsigned int, unsigned int); };

// @ 0x00f28c50
extern "C" bool __fastcall FUN_00f28c50(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int v_l2580[645];
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1013;
    int v_l2600[5];
    int t1016;
    int t1017;
    int t1021;
    int t1025;
    bool t1028;
    bool t1030;
    t1002 = (int)((int)(self));
    t1003 = (int)((int)&v_l2580);
    ((C_00692f90*)(t1003))->FUN_00692f90((unsigned int)(t1002), (unsigned int)((int)g_015aff90), (unsigned int)((int)27790630));
    t1007 = (int)((int)(a4));
    t1008 = (int)((int)&v_l2580);
    t1011 = (int)((C_00693e10*)(t1008))->FUN_00693e10((unsigned int)(t1007));
    if ((unsigned char)(t1011) != (unsigned char)0) {
        t1012 = (int)(*(int*)((char*)(t1002) + 40));
        if (t1012 != (int)0) {
            t1011 = (int)(*(int*)((char*)(t1002) + 36));
            if (t1011 != (int)0) {
                t1013 = (int)((int)&v_l2600);
                t1016 = (int)((C_006b5770*)(t1013))->FUN_006b5770((unsigned int)(t1011), (unsigned int)(t1012), (unsigned int)((int)0));
                t1017 = (int)(t1002);
                ((C_006b5430*)(t1017))->FUN_006b5430((unsigned int)(t1016));
                t1021 = (int)((int)&v_l2600);
                ((C_006b5240*)(t1021))->FUN_006b5240();
                t1025 = (int)(t1002 + (int)20);
                t1011 = (int)((C_005c3d90*)(t1025))->FUN_005c3d90((unsigned int)((int)g_013ec468));
            }
        }
        t1028 = true;
        return (bool)(t1028);
    }
    t1030 = false;
    return (bool)(t1030);
}
