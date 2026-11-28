// 0x00974c30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00973dd0/s00973dd0.cpp, src/game/UTFSpore_Win32/Grid.cpp.

struct C_00614950 { int FUN_00614950(unsigned int); };

// @ 0x00974c30
extern "C" int __cdecl FUN_00974c30(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1011;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)(a8));
    t1003 = (int)(*(int*)((char*)(t1000)));
    if (t1003 == (int)*(int*)((char*)(t1001))) {
        t1004 = (int)(*(int*)((char*)(t1000) + 12));
        if (t1004 != (int)0) {
            t1005 = (int)(*(int*)((char*)(t1001) + 12));
            if (t1005 != (int)0) {
                if (t1003 == (int)2) {
                    t1006 = (int)(*(int*)((char*)(t1005)));
                    t1007 = (int)((C_00614950*)(t1004))->FUN_00614950((unsigned int)(t1006));
                    return (int)(t1007);
                }
            }
        }
    }
    t1011 = (int)((int)0);
    return (int)(t1011);
}
