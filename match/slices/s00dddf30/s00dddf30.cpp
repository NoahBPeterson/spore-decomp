// 0x00dddf30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00dddd20/s00dddd20.cpp, src/game/SPGonzago/SPGalaxyGameEntry.cpp.

extern "C" unsigned char g_01413fac[];
extern "C" unsigned char g_0147d3c0[];
extern "C" unsigned char g_0147d3d0[];
extern "C" unsigned char g_0147d3e8[];
extern "C" unsigned char g_0147d3fc[];
extern "C" unsigned char g_0147d41c[];
struct C_0083a9f0 { void FUN_0083a9f0(unsigned int); };
extern "C" void __cdecl FUN_0083bcd0(...);
struct C_0083c800 { void FUN_0083c800(); };

// @ 0x00dddf30
extern "C" int __fastcall FUN_00dddf30(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1007;
    int t1008;
    int t1009;
    int t1017;
    t1003 = (int)((int)(self));
    ((C_0083c800*)((int)(self)))->FUN_0083c800();
    t1007 = (int)((int)(a4));
    t1008 = (int)(t1003 + (int)20);
    t1009 = (int)(t1008);
    *(int*)((char*)(t1003)) = (int)((int)g_0147d41c);
    *(int*)((char*)(t1003) + 16) = (int)(t1007);
    ((C_0083a9f0*)(t1009))->FUN_0083a9f0((unsigned int)((int)1));
    FUN_0083bcd0((unsigned int)(t1008), (unsigned int)((int)g_0147d3c0), (unsigned int)((int)g_01413fac), (unsigned int)((int)0), (unsigned int)((int)g_0147d3d0), (unsigned int)((int)g_0147d3e8), (unsigned int)((int)1), (unsigned int)((int)g_0147d3fc), (unsigned int)((int)0));
    t1017 = (int)(t1003);
    return (int)(t1017);
}
