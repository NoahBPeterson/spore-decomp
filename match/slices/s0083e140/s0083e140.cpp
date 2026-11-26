// 0x0083e140: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/Expression.cpp, match/slices/s0083d3d0/s0083d3d0.cpp.

struct C_0083dd00 { int FUN_0083dd00(unsigned int, unsigned int); };

// @ 0x0083e140
extern "C" void __fastcall FUN_0083e140(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 8));
    t1004 = (int)(*(int*)((char*)(t1002) + 4));
    t1005 = (int)(t1002);
    ((C_0083dd00*)(t1005))->FUN_0083dd00((unsigned int)(t1004), (unsigned int)(t1003));
    *(int*)((char*)(t1002) + 12) = (int)((int)0);
    return;
}
