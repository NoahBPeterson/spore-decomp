// 0x00702660: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsHierGrid.cpp, match/slices/s00701a00/s00701a00.cpp.

// lifted by il2c_lift + l2c_search (swap@19); CI scorer MATCH; corpus status nonmatching/residual
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x00702660
extern "C" int __stdcall FUN_00702660(int a4, int a8)
{
    int t1001;
    int v_l4;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1020;
    t1001 = (int)((int)0);
    v_l4 = (int)(t1001);
    if ((unsigned int)((int)(a8)) > (unsigned int)(t1001)) {
        do {
            t1006 = (int)((int)(a4));
            t1007 = (int)(*(int*)((char*)(t1006) + (t1001)*4));
            if (t1007 != (int)0) {
                goto L702680;
                L702680:;
                t1010 = (int)(t1007);
                t1007 = (int)(*(int*)((char*)(t1007) + 20));
                t1011 = (int)(*(int*)((char*)(t1010) + 4));
                t1012 = (int)(t1010 + (int)4);
                if (t1011 != t1012) {
                    do {
                        t1013 = (int)(t1011);
                        t1011 = (int)(*(int*)((char*)(t1011)));
                        FUN_00f47380((unsigned int)(t1013));
                    } while (t1011 != t1012);
                }
                FUN_00f47380((unsigned int)(t1010));
                if (t1007 != (int)0) goto L702680;
                t1001 = (int)(v_l4);
            }
            t1020 = (int)((int)(a4));
            *(int*)((char*)(t1020) + (t1001)*4) = (int)((int)0);
            t1001 = (int)(t1001 + (int)1);
            v_l4 = (int)(t1001);
        } while ((unsigned int)(t1001) < (unsigned int)((int)(a8)));
    }
    return (int)(t1001);
}
