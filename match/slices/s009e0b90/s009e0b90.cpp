// 0x009e0b90: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPCreatureAnim/gait_record.cpp, match/slices/s009dfc40/s009dfc40.cpp.

struct C_009de770 { void FUN_009de770(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x009e0b90
extern "C" int __stdcall FUN_009e0b90(int a4, int a8)
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
    int t1015;
    int t1019;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(a8));
    if ((unsigned int)(t1000) < (unsigned int)(t1001)) {
        t1002 = (int)(t1001 - t1000);
        t1004 = (int)(t1000 + (int)36);
        t1005 = (int)(t1002 - (int)1);
        t1011 = (unsigned int)((unsigned int)(t1005) / (unsigned int)164);
        t1012 = (int)((int)(t1011) + (int)1);
        do {
            t1013 = (int)(*(int*)((char*)(t1004) + 4));
            t1014 = (int)(*(int*)((char*)(t1004)));
            t1015 = (int)(t1004);
            ((C_009de770*)(t1015))->FUN_009de770((unsigned int)(t1014), (unsigned int)(t1013));
            t1019 = (int)(*(int*)((char*)(t1004)));
            if (t1019 != (int)0) {
                if ((int)*(int*)((char*)(t1019) - 4) != (int)0) {
                    FUN_00f47380((unsigned int)(t1019));
                }
            }
            t1000 = (int)(*(int*)((char*)(t1004) - 20));
            if (t1000 != (int)0) {
                if ((int)*(int*)((char*)(t1000) - 4) != (int)0) {
                    t1000 = (int)FUN_00f47380((unsigned int)(t1000));
                }
            }
            t1004 = (int)(t1004 + (int)164);
            t1012 = (int)(t1012 - (int)1);
        } while (t1012 != (int)0);
    }
    return (int)(t1000);
}
