// 0x00f964b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainSphere.cpp, match/slices/s00f955f0/s00f955f0.cpp.

extern "C" long __cdecl _InterlockedDecrement(long volatile*);
#pragma intrinsic(_InterlockedDecrement)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x00f964b0
extern "C" int __fastcall FUN_00f964b0(char* self, int edx_unused)
{
    int t1001;
    int t1003;
    int t1006;
    int t1007;
    int t1012;
    t1001 = (int)((int)(self) + (int)4);
    t1003 = (int)(t1001);
    t1006 = (int)_InterlockedDecrement((long volatile*)(t1003));
    if (t1006 == (int)0) {
        t1007 = (int)((int)1);
        _InterlockedExchange((long volatile*)(t1001), (long)(t1007));
        FUN_00f47380((unsigned int)((int)(self)));
    }
    t1012 = (int)(t1006);
    return (int)(t1012);
}
