// 0x009011e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/MemoryMan.cpp, match/slices/s00900410/s00900410.cpp.

extern "C" unsigned char g_0143a0b0[];
struct C_009009e0 { void FUN_009009e0(); };
extern "C" void __cdecl FUN_009055d0(...);
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x009011e0
extern "C" int __fastcall FUN_009011e0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1007;
    unsigned char t4;
    int t1014;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 108));
    *(int*)((char*)(t1002)) = (int)((int)g_0143a0b0);
    if (t1003 != (int)0) {
        FUN_009055d0((unsigned int)(t1003));
    }
    t1007 = (int)(t1002);
    ((C_009009e0*)(t1007))->FUN_009009e0();
    t4 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    if (t4 != (unsigned char)0) {
        FUN_00f47380((unsigned int)(t1002));
    }
    t1014 = (int)(t1002);
    return (int)(t1014);
}
