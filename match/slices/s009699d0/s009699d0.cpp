// 0x009699d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00968da0/s00968da0.cpp, src/game/UTFSpore_Win32/ComboBox.cpp.

struct C_00579a90 { void FUN_00579a90(unsigned int); };
struct C_0092b750 { void FUN_0092b750(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x009699d0
// @ 0x009699d0
extern "C" bool __fastcall FUN_009699d0(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1002;
    int t1004;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int v_l16[4];
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    bool t1027;
    bool t1030;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 64));
    t1002 = (int)(t1001 - (int)*(int*)((char*)((int)(self)) + 60));
    t1004 = (int)((int)(a4));
    t1006 = (int)((int)(self) + (int)60);
    t1007 = (int)(t1002 >> (int)4);
    if ((unsigned int)(t1004) <= (unsigned int)(t1007)) {
        t1008 = (int)((int)(a8));
        t1009 = (int)((int)&v_l16);
        (*(int*)&v_l16[0]) = (int)((int)0);
        (*(int*)&v_l16[1]) = (int)((int)0);
        (*(int*)&v_l16[2]) = (int)((int)0);
        ((C_00579a90*)(t1009))->FUN_00579a90((unsigned int)(t1008));
        t1013 = (int)((int)&v_l16);
        t1014 = (int)(t1004 << (int)4);
        t1015 = (int)(t1014 + (int)*(int*)((char*)(t1006)));
        t1016 = (int)(t1006);
        ((C_0092b750*)(t1016))->FUN_0092b750((unsigned int)(t1015), (unsigned int)(t1013));
        t1020 = (int)((*(int*)&v_l16[2]));
        t1021 = (int)((*(int*)&v_l16[0]));
        t1022 = (int)(t1020 - t1021);
        t1023 = (int)(t1022 & (int)(-2));
        if (t1023 > (int)2) {
            if (t1021 != (int)0) {
                t1021 = (int)FUN_00f47380((unsigned int)(t1021));
            }
        }
        t1027 = true;
        return (bool)(t1027);
    }
    t1030 = false;
    return (bool)(t1030);
}
