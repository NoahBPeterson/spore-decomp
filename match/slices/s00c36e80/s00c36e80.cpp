// 0x00c36e80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGameDataUFO.cpp, match/slices/s00c368c0/s00c368c0.cpp.

struct C_00b18460 { int FUN_00b18460(unsigned int); };
struct C_00bfc380 { int FUN_00bfc380(unsigned int); };
struct C_00c41d00 { int FUN_00c41d00(unsigned int); };

// @ 0x00c36e80
extern "C" int __fastcall FUN_00c36e80(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1008;
    int t1011;
    int t1012;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1002 != (int)(-1338788861)) {
        t1005 = (int)((C_00b18460*)((int)(self)))->FUN_00b18460((unsigned int)(t1002));
        if (t1005 != (int)0) goto Lc36eba;
        t1008 = (int)(t1004 + (int)52);
        t1005 = (int)((C_00c41d00*)(t1008))->FUN_00c41d00((unsigned int)(t1002));
        if (t1005 != (int)0) goto Lc36eba;
        t1011 = (int)(t1004 + (int)1288);
        t1012 = (int)((C_00bfc380*)(t1011))->FUN_00bfc380((unsigned int)(t1002));
        return (int)(t1012);
    }
    t1005 = (int)(t1004);
    Lc36eba:;
    return (int)(t1005);
}
