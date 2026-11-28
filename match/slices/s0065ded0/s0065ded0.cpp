// 0x0065ded0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPUIFeedEdit.cpp, match/slices/s0065d050/s0065d050.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};

extern "C" int __cdecl FUN_00e99140(...);

// @ 0x0065ded0
extern "C" int __fastcall FUN_0065ded0(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1017;
    int t1018;
    int t1019;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1031;
    t1001 = (int)((int)(a8));
    t1003 = (int)((int)(a4));
    t1006 = (int)((int)(self));
    t1007 = (int)(*(int*)((char*)(t1006) + 4));
    t1008 = (int)FUN_00e99140((unsigned int)(t1001), (unsigned int)(t1007), (unsigned int)(t1003));
    t1011 = (int)(*(int*)((char*)(t1006) + 4));
    if ((unsigned int)(t1008) < (unsigned int)(t1011)) {
        t1012 = (int)(t1011 - t1008);
        t1013 = (int)(t1012 - (int)1);
        t1014 = (int)((unsigned int)(t1013) >> (int)4);
        t1015 = (int)(t1014 + (int)1);
        t1017 = (int)(t1008 + (int)12);
        t1018 = (int)(t1015);
        do {
            t1019 = (int)(*(int*)((char*)(t1017)));
            if (t1019 != (int)0) {
                ((il2c_vc0*)(t1019))->s1();
            }
            t1017 = (int)(t1017 + (int)16);
            t1018 = (int)(t1018 - (int)1);
        } while (t1018 != (int)0);
        t1003 = (int)((int)(a4));
    }
    t1026 = (int)(t1001 - t1003);
    t1027 = (int)(t1026 >> (int)4);
    t1028 = (int)(-t1027);
    t1029 = (int)(t1028 << (int)4);
    *(int*)((char*)(t1006) + 4) += t1029;
    t1031 = (int)(t1003);
    return (int)(t1031);
}
