// 0x00fa0f10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainSphere.cpp, match/slices/s00f9fef0/s00f9fef0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2(int);
};

extern "C" long __cdecl _InterlockedDecrement(long volatile*);
#pragma intrinsic(_InterlockedDecrement)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

// @ 0x00fa0f10
extern "C" int __fastcall FUN_00fa0f10(char* self, int edx_unused)
{
    int t1001;
    int t1002;
    int t1004;
    int t1007;
    int t1008;
    int t1015;
    t1001 = (int)((int)(self) + (int)16);
    t1002 = (int)(t1001 + (int)4);
    t1004 = (int)(t1002);
    t1007 = (int)_InterlockedDecrement((long volatile*)(t1004));
    if (t1007 == (int)0) {
        t1008 = (int)((int)1);
        _InterlockedExchange((long volatile*)(t1002), (long)(t1008));
        if (t1001 != (int)0) {
            ((il2c_vc0*)(t1001))->s2((int)((int)1));
        }
    }
    t1015 = (int)(t1007);
    return (int)(t1015);
}
