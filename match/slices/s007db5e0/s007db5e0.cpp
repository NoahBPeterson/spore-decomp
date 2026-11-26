// 0x007db5e0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// lifted by il2c_lift + l2c_search (swap@13); CI scorer MATCH; corpus status nonmatching/residual
// @ 0x007db5e0
extern "C" int __fastcall FUN_007db5e0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1009;
    int t1010;
    int t1011;
    int t1014;
    int t1016;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 4));
    t1004 = (int)(*(int*)((char*)((int)(self))));
    t1005 = (int)(t1001 - t1004);
    t1007 = (int)((int)0);
    t1006 = (int)(t1005 >> (int)2);
    if (t1006 > (int)0) {
        t1009 = (int)((int)(a4));
        t1010 = (int)(t1004);
        do {
            t1011 = (int)(*(int*)((char*)(t1010)));
            if ((int)*(int*)((char*)(t1011)) == t1009) goto L7db616;
            t1007 = (int)(t1007 + (int)1);
            t1010 = (int)(t1010 + (int)4);
        } while (t1007 < t1006);
    }
    t1014 = (int)((int)0);
    return (int)(t1014);
    L7db616:;
    t1016 = (int)(*(int*)((char*)(t1004) + (t1007)*4));
    return (int)(t1016);
}
