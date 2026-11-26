// 0x009e18c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPCreatureAnim/gait_record.cpp, match/slices/s009e0d90/s009e0d90.cpp.

extern "C" int __cdecl FUN_00932e80(...);
struct C_009e1850 { int FUN_009e1850(unsigned int, unsigned int); };

// @ 0x009e18c0
extern "C" void __fastcall FUN_009e18c0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1002;
    int t1004;
    int t1007;
    int t1008;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1007 = (int)FUN_00932e80((unsigned int)(t1002), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    t1008 = (int)(t1004);
    ((C_009e1850*)(t1008))->FUN_009e1850((unsigned int)(t1002), (unsigned int)(t1007));
    return;
}
