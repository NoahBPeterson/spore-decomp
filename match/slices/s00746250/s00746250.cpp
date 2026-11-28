// 0x00746250: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsModelManager.cpp, match/slices/s00745ac0/s00745ac0.cpp.

struct C_0041d8b0 { int FUN_0041d8b0(unsigned int); };
struct C_00743150 { int FUN_00743150(unsigned int, unsigned int); };

// @ 0x00746250
extern "C" int __stdcall FUN_00746250(int a4, int a8, int a12)
{
    int t1000;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1013;
    int t1015;
    int t1016;
    int t1017;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        t1003 = (int)(t1000 + (int)(-8));
    } else {
        t1003 = (int)((int)0);
    }
    t1004 = (int)((int)(a12));
    if (t1004 < (int)0) {
        t1005 = (int)((int)(a8));
        t1006 = (int)(t1003 + (int)216);
        t1007 = (int)((C_0041d8b0*)(t1006))->FUN_0041d8b0((unsigned int)(t1005));
        return (int)(t1007);
    }
    t1013 = (int)((int)(a8));
    t1015 = (int)((int)0);
    t1016 = (int)(t1003 + (int)156);
    L746290:;
    t1017 = (int)(*(int*)((char*)(t1016)));
    if (t1017 != (int)0) {
        t1000 = (int)((C_00743150*)(t1017))->FUN_00743150((unsigned int)(t1004), (unsigned int)(t1013));
        t1015 = (int)(t1015 + (int)1);
        t1016 = (int)(t1016 + (int)4);
        if (t1015 < (int)4) goto L746290;
    }
    return (int)(t1000);
}
