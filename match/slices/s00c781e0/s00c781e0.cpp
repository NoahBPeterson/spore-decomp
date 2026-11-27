// 0x00c781e0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00c77380/s00c77380.cpp, src/game/SPGonzago/SPPlayer.cpp.

extern "C" unsigned char g_01465d64[];
struct C_00b638b0 { void FUN_00b638b0(); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x00c781e0
extern "C" int __stdcall FUN_00c781e0(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    unsigned int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1018;
    int t1022;
    int t1026;
    int t1030;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(a8));
    if ((unsigned int)(t1000) < (unsigned int)(t1001)) {
        t1002 = (int)(t1001 - t1000);
        t1004 = (int)(t1000 + (int)112);
        t1005 = (int)(t1002 - (int)1);
        t1011 = (unsigned int)((unsigned int)(t1005) / (unsigned int)176);
        t1012 = (int)((int)(t1011) + (int)1);
        goto Lc78210;
        t1012 = (int)(t1013);
        Lc78210:;
        t1014 = (int)(t1004 + (int)24);
        *(int*)((char*)(t1004) - 104) = (int)((int)g_01465d64);
        ((C_00b638b0*)(t1014))->FUN_00b638b0();
        t1018 = (int)(*(int*)((char*)(t1004)));
        if (t1018 != (int)0) {
            FUN_00f47380((unsigned int)(t1018));
        }
        t1022 = (int)(*(int*)((char*)(t1004) - 24));
        if (t1022 != (int)0) {
            FUN_00f47380((unsigned int)(t1022));
        }
        t1026 = (int)(*(int*)((char*)(t1004) - 48));
        if (t1026 != (int)0) {
            FUN_00f47380((unsigned int)(t1026));
        }
        t1030 = (int)(*(int*)((char*)(t1004) - 72));
        if (t1030 != (int)0) {
            FUN_00f47380((unsigned int)(t1030));
        }
        t1000 = (int)(*(int*)((char*)(t1004) - 96));
        if (t1000 != (int)0) {
            t1000 = (int)FUN_00f47380((unsigned int)(t1000));
        }
        t1004 = (int)(t1004 + (int)176);
        t1012 = (int)(t1012 - (int)1);
        if (t1012 != (int)0) goto Lc78210;
    }
    return (int)(t1000);
}
