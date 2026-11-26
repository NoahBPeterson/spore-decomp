// 0x0108f3e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0108eb30/s0108eb30.cpp.

extern "C" unsigned char g_014a1838[];
struct C_01098140 { void FUN_01098140(unsigned int, unsigned int); };

// @ 0x0108f3e0
extern "C" int __fastcall FUN_0108f3e0(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    t1000 = (int)((int)(a8));
    t1003 = (int)((int)(self));
    t1004 = (int)((int)(a4));
    t1005 = (int)(t1003);
    ((C_01098140*)(t1005))->FUN_01098140((unsigned int)(t1004), (unsigned int)(t1000));
    *(int*)((char*)(t1003)) = (int)((int)g_014a1838);
    t1009 = (int)(t1003);
    return (int)(t1009);
}
