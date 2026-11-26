// 0x00ec9ae0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ec8d20/s00ec8d20.cpp.

// lifted by il2c_lift + l2c_search (swap@26); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_016c757c[];
struct C_00ec9820 { int FUN_00ec9820(unsigned int); };

// @ 0x00ec9ae0
extern "C" int __cdecl FUN_00ec9ae0(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1005;
    int t1006;
    int t1008;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    t1000 = (int)((int)(*(int*)g_016c757c));
    t1001 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)(t1000) + 4));
    t1003 = (int)(*(int*)((char*)(t1002) + (t1001)*4));
    t1005 = (int)((int)&a4);
    *(int*)&(a4) = (int)(t1003);
    t1006 = (int)(t1000 + (int)80);
    t1008 = (int)((C_00ec9820*)(t1006))->FUN_00ec9820((unsigned int)(t1005));
    t1010 = (int)(t1008);
    t1011 = (int)(*(int*)((char*)(t1010)));
    t1012 = (int)(*(int*)((char*)(t1010) + 4));
    t1013 = (int)(t1012 - t1011);
    t1015 = (int)((int)0);
    t1014 = (int)(t1013 >> (int)2);
    if (t1014 > (int)0) {
        t1016 = (int)((int)(a8));
        do {
            if ((int)*(int*)((char*)(t1011)) == t1016) goto Lec9b25;
            t1015 = (int)(t1015 + (int)1);
            t1011 = (int)(t1011 + (int)4);
        } while (t1015 < t1014);
    }
    t1015 = (int)((int)0);
    Lec9b25:;
    return (int)(t1015);
}
