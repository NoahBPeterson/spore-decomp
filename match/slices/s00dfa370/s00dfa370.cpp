// 0x00dfa370: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00df9650/s00df9650.cpp, src/game/SPGonzago/SPGalaxyGameEntry.cpp.

extern "C" unsigned char g_01601760[];
extern "C" unsigned char g_016a0fb8[];
extern "C" unsigned char g_016a0fc8[];
struct C_00a68fb0 { int FUN_00a68fb0(unsigned int); };
extern "C" int __cdecl FUN_00dd9190(...);
struct C_00ddb760 { void FUN_00ddb760(); };
struct C_00ddbe40 { int FUN_00ddbe40(); };

// @ 0x00dfa370
extern "C" int __cdecl FUN_00dfa370(void)
{
    int t1003;
    int t1004;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1014;
    int t1015;
    int t1017;
    int t1021;
    int t1022;
    t1003 = (int)FUN_00dd9190();
    t1004 = (int)(t1003);
    ((C_00ddb760*)(t1004))->FUN_00ddb760();
    t1008 = (int)((int)(*(int*)g_016a0fc8));
    t1009 = (int)((int)(*(int*)g_016a0fb8));
    if ((unsigned int)(t1008) > (unsigned int)(t1009)) {
        t1010 = (int)(t1008 - t1009);
        t1011 = (int)((int)g_01601760);
        t1014 = (int)((C_00a68fb0*)(t1011))->FUN_00a68fb0((unsigned int)(t1010));
        t1015 = (int)((int)(*(int*)g_016a0fb8));
        t1008 = (int)(t1014 + t1015);
        if (t1008 != (int)0) {
            t1017 = (int)(t1008);
            do {
                t1021 = (int)FUN_00dd9190();
                t1022 = (int)(t1021);
                t1008 = (int)((C_00ddbe40*)(t1022))->FUN_00ddbe40();
                t1017 = (int)(t1017 - (int)1);
            } while (t1017 != (int)0);
        }
    }
    return (int)(t1008);
}
