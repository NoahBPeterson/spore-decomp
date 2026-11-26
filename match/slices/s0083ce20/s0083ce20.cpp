// 0x0083ce20: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/Commands.cpp, match/slices/s0083c900/s0083c900.cpp.

extern "C" unsigned char g_0141b5e4[];
struct C_0083cad0 { void FUN_0083cad0(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x0083ce20
extern "C" int __fastcall FUN_0083ce20(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1011;
    unsigned char t6;
    int t1018;
    t1003 = (int)((int)(self));
    t1004 = (int)(t1003 + (int)16);
    *(int*)((char*)(t1003)) = (int)((int)g_0141b5e4);
    t1005 = (int)(*(int*)((char*)(t1004) + 8));
    t1006 = (int)(*(int*)((char*)(t1004) + 4));
    t1007 = (int)(t1004);
    ((C_0083cad0*)(t1007))->FUN_0083cad0((unsigned int)(t1006), (unsigned int)(t1005));
    *(int*)((char*)(t1004) + 12) = (int)((int)0);
    if ((unsigned int)*(int*)((char*)(t1004) + 8) > (unsigned int)1) {
        t1011 = (int)(*(int*)((char*)(t1004) + 4));
        FUN_00f47380((unsigned int)(t1011));
    }
    t6 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    if (t6 != (unsigned char)0) {
        FUN_00f47380((unsigned int)(t1003));
    }
    t1018 = (int)(t1003);
    return (int)(t1018);
}
