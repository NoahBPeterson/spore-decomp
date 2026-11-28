// 0x0112da60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/cmn/system.cpp.cpp, match/slices/s0112be40/s0112be40.cpp, match/slices/s0112ce20/s0112ce20.cpp.

struct C_01133b70 { int FUN_01133b70(); };
struct C_01133e30 { void FUN_01133e30(); };

// @ 0x0112da60
extern "C" void __fastcall FUN_0112da60(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    t1003 = (int)((int)(self));
    t1004 = (int)((int)2);
    do {
        t1005 = (int)(t1003);
        ((C_01133e30*)(t1005))->FUN_01133e30();
        t1009 = (int)(t1003);
        ((C_01133b70*)(t1009))->FUN_01133b70();
        t1003 = (int)(t1003 + (int)28);
        t1004 = (int)(t1004 - (int)1);
    } while (t1004 != (int)0);
    return;
}
