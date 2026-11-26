// 0x00d7b290: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00d7a5c0/s00d7a5c0.cpp, src/game/SPGonzago/SPAnimalBehaviorTrees.cpp.

struct C_00bc9b10 { int FUN_00bc9b10(); };
struct C_00bc9b50 { int FUN_00bc9b50(); };
struct C_00c04590 { int FUN_00c04590(); };

// @ 0x00d7b290
extern "C" bool __cdecl FUN_00d7b290(int a4, int a8)
{
    int t1002;
    int t1003;
    int t1006;
    int t1008;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t1019;
    int t1022;
    bool t1025;
    bool t1028;
    t1002 = (int)((int)(a4));
    t1003 = (int)(t1002);
    t1006 = (int)((C_00bc9b50*)(t1003))->FUN_00bc9b50();
    if ((unsigned char)(t1006) == (unsigned char)0) {
        t1008 = (int)(t1002);
        t1011 = (int)((C_00bc9b10*)(t1008))->FUN_00bc9b10();
        t1012 = (int)((int)(a8));
        t1013 = (int)(t1012);
        t1014 = (int)(t1011);
        t1017 = (int)((C_00c04590*)(t1013))->FUN_00c04590();
        t1018 = (int)(t1014);
        t1019 = (int)(t1017);
        t1006 = (int)((C_00c04590*)(t1018))->FUN_00c04590();
        t1022 = (int)(*(int*)((char*)(t1014) + 2848));
        if (t1022 == (int)*(int*)((char*)(t1012) + 2848)) {
            if (t1006 == t1019) {
                t1025 = true;
                return (bool)(t1025);
            }
        }
    }
    t1028 = false;
    return (bool)(t1028);
}
