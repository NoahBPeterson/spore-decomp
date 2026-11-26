// 0x00eb0d60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00eaffc0/s00eaffc0.cpp, src/game/SPGonzago/SPAudioPlayerCityMusic.cpp.

struct C_00ead6a0 { int FUN_00ead6a0(); };
struct C_00eb0810 { int FUN_00eb0810(unsigned int, unsigned int); };
struct C_00eb0870 { void FUN_00eb0870(unsigned int, unsigned int, unsigned int); };
struct C_00eb1d70 { int FUN_00eb1d70(); };

// @ 0x00eb0d60
extern "C" void __fastcall FUN_00eb0d60(char* self, int edx_unused, int a4)
{
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1017;
    int t1016;
    int t1018;
    int v_l108[27];
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1031;
    int t1032;
    int t1033;
    int t1037;
    int t1045;
    int t1046;
    int t1047;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 4));
    t1006 = (int)(*(int*)((char*)(t1004)));
    t1007 = (int)(t1005);
    t1008 = (int)(t1007 - t1006);
    t1017 = (int)(t1008 / (int)108);
    t1016 = (int)((int)(a4));
    if ((unsigned int)(t1016) > (unsigned int)(t1017)) {
        t1018 = (int)((int)&v_l108);
        t1021 = (int)((C_00eb1d70*)(t1018))->FUN_00eb1d70();
        t1022 = (int)(*(int*)((char*)(t1004) + 4));
        t1023 = (int)(t1022);
        t1024 = (int)(t1023 - (int)*(int*)((char*)(t1004)));
        t1031 = (int)(t1024 / (int)108);
        t1032 = (int)(t1016 - t1031);
        t1033 = (int)(t1004);
        ((C_00eb0870*)(t1033))->FUN_00eb0870((unsigned int)(t1022), (unsigned int)(t1032), (unsigned int)(t1021));
        t1037 = (int)((int)&v_l108);
        ((C_00ead6a0*)(t1037))->FUN_00ead6a0();
        return;
    }
    t1045 = (int)(t1016 * (int)108);
    t1046 = (int)(t1045 + t1006);
    t1047 = (int)(t1004);
    ((C_00eb0810*)(t1047))->FUN_00eb0810((unsigned int)(t1046), (unsigned int)(t1005));
    return;
}
