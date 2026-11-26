// 0x00cc2d30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPWeaponsView.cpp, match/slices/s00cc22c0/s00cc22c0.cpp.

struct C_00e92ca0 { void FUN_00e92ca0(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_01043860(...);
extern "C" int __cdecl FUN_01043a50(...);

// @ 0x00cc2d30
extern "C" void __fastcall FUN_00cc2d30(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    int t1010;
    int t1014;
    int t1015;
    t1000 = (int)((int)(a8));
    t1003 = (int)((int)(self));
    t1004 = (int)((int)(a4));
    t1005 = (int)(t1003);
    ((C_00e92ca0*)(t1005))->FUN_00e92ca0((unsigned int)(t1004), (unsigned int)(t1000));
    t1009 = (int)(*(int*)((char*)(t1003) + 12));
    t1010 = (int)(t1003 + (int)52);
    FUN_01043860((unsigned int)(t1009), (unsigned int)(t1010), (unsigned int)((int)0));
    t1014 = (int)(*(int*)((char*)(t1003) + 12));
    t1015 = (int)(t1003 + (int)56);
    FUN_01043a50((unsigned int)(t1014), (unsigned int)(t1015), (unsigned int)((int)0));
    return;
}
