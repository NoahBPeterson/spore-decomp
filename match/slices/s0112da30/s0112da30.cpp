// 0x0112da30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/cmn/system.cpp.cpp, match/slices/s0112be40/s0112be40.cpp, match/slices/s0112ce20/s0112ce20.cpp, match/slices/s0112ce20/scratch_tm_variants.cpp.

struct C_01133c90 { int FUN_01133c90(); };

// @ 0x0112da30
extern "C" void __fastcall FUN_0112da30(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1005;
    t1003 = (int)((int)(self));
    t1004 = (int)((int)2);
    do {
        t1005 = (int)(t1003);
        ((C_01133c90*)(t1005))->FUN_01133c90();
        t1003 = (int)(t1003 + (int)28);
        t1004 = (int)(t1004 - (int)1);
    } while (t1004 != (int)0);
    return;
}
