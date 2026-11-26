// 0x0093c210: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/EAStreamMemory.cpp, match/slices/s0093b9e0/s0093b9e0.cpp.

struct il2c_vc0 {
    virtual void s0(int);
};

extern "C" long __cdecl _InterlockedDecrement(long volatile*);
#pragma intrinsic(_InterlockedDecrement)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
extern "C" unsigned char g_013f3a68[];
extern "C" unsigned char g_0143eb78[];
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x0093c210
extern "C" int __fastcall FUN_0093c210(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1007;
    int t1010;
    int t1012;
    unsigned char t9;
    int t1022;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 4));
    *(int*)((char*)(t1002)) = (int)((int)g_0143eb78);
    if (t1003 != (int)0) {
        t1004 = (int)(t1003 + (int)4);
        t1005 = (int)(t1004 + (int)4);
        t1007 = (int)(t1005);
        t1010 = (int)_InterlockedDecrement((long volatile*)(t1007));
        if (t1010 == (int)0) {
            t1012 = (int)((int)1);
            _InterlockedExchange((long volatile*)(t1005), (long)(t1012));
            if (t1004 != (int)0) {
                ((il2c_vc0*)(t1004))->s0((int)((int)1));
            }
        }
    }
    t9 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    *(int*)((char*)(t1002)) = (int)((int)g_013f3a68);
    if (t9 != (unsigned char)0) {
        FUN_00f47380((unsigned int)(t1002));
    }
    t1022 = (int)(t1002);
    return (int)(t1022);
}
