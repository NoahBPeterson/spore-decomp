// 0x01052880: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPToolStrategies.cpp, match/slices/s010527f0/s010527f0.cpp.

extern "C" int __stdcall FUN_00b3d390(unsigned int);
struct C_0104c4f0 { int FUN_0104c4f0(); };

// @ 0x01052880
extern "C" void __cdecl FUN_01052880(int a4, int a8)
{
    int t1001;
    int t1002;
    int t1006;
    int t1007;
    int t1010;
    t1001 = (int)((int)(a8));
    if (t1001 != (int)0) {
        t1002 = (int)((int)(a4));
        t1006 = (int)FUN_00b3d390((unsigned int)(t1002));
        t1007 = (int)(t1006);
        t1010 = (int)((C_0104c4f0*)(t1007))->FUN_0104c4f0();
        *(int*)((char*)(t1001)) = (int)(t1010);
    }
    return;
}
