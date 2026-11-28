// 0x0113af90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/plugins/_at_01130000.cpp, match/slices/s0113a8b0/s0113a8b0.cpp.

struct C_0112c850 { int FUN_0112c850(unsigned int, unsigned int); };

// @ 0x0113af90
extern "C" void __fastcall FUN_0113af90(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 144) != (int)0) {
        t1003 = (int)(*(int*)((char*)(t1002) + 140));
        t1004 = (int)(*(int*)((char*)(t1002) + 4));
        ((C_0112c850*)(t1004))->FUN_0112c850((unsigned int)(t1003), (unsigned int)((int)0));
        *(int*)((char*)(t1002) + 144) = (int)((int)0);
    }
    return;
}
