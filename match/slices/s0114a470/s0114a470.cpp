// 0x0114a470: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s01149f70/s01149f70.cpp.

struct C_01149fd0 { void FUN_01149fd0(); };
struct C_0114a160 { void FUN_0114a160(unsigned int, unsigned int); };

// @ 0x0114a470
extern "C" int __cdecl FUN_0114a470(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1003;
    int t1004;
    int t1008;
    int t1012;
    t1000 = (int)((int)(a8));
    t1001 = (int)(*(int*)((char*)(t1000) + 196620));
    t1003 = (int)((int)(a4));
    t1004 = (int)(t1003);
    ((C_0114a160*)(t1004))->FUN_0114a160((unsigned int)(t1001), (unsigned int)((int)256));
    t1008 = (int)(t1003);
    ((C_01149fd0*)(t1008))->FUN_01149fd0();
    t1012 = (int)((int)1);
    *(unsigned char*)((char*)(t1003) + 332) = (unsigned char)((unsigned char)(t1012));
    return (int)(t1012);
}
