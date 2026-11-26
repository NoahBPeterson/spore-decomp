// 0x008ee720: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008edc30/s008edc30.cpp, src/game/UTFSpore_Win32/_at_008e0000.cpp.

struct C_0089b250 { int FUN_0089b250(unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x008ee720
extern "C" void __fastcall FUN_008ee720(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1001;
    int t1003;
    t1000 = (int)((int)(a8));
    t1001 = (int)((int)(a4));
    t1003 = (int)((int)(self) + (int)4);
    ((C_0089b250*)(t1003))->FUN_0089b250((unsigned int)(t1001), (unsigned int)(t1000), (unsigned int)((int)0), (unsigned int)((int)0));
    return;
}
