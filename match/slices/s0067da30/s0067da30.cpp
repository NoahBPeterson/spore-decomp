// 0x0067da30: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/EACompressionStreamZLib.cpp, match/slices/s0067d550/s0067d550.cpp.

struct il2c_vc0 {
    virtual void s0(int);
};

extern "C" long __cdecl _InterlockedDecrement(long volatile*);
#pragma intrinsic(_InterlockedDecrement)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

// @ 0x0067da30
extern "C" int __fastcall FUN_0067da30(char* self, int edx_unused)
{
    int t1001;
    int t1002;
    int t1004;
    int t1008;
    int t1010;
    t1001 = (int)((int)(self) + (int)4);
    t1002 = (int)(t1001 + (int)4);
    t1004 = (int)(t1002);
    t1008 = (int)_InterlockedDecrement((long volatile*)(t1004));
    if (t1008 == (int)0) {
        t1010 = (int)((int)1);
        _InterlockedExchange((long volatile*)(t1002), (long)(t1010));
        if (t1001 != (int)0) {
            ((il2c_vc0*)(t1001))->s0((int)((int)1));
        }
        t1008 = (int)((int)0);
    }
    return (int)(t1008);
}
