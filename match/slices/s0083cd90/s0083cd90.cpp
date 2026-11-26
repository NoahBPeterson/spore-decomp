// 0x0083cd90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0083c900/s0083c900.cpp, src/game/UTFSpore_Win32/Commands.cpp.

extern "C" unsigned char g_0141b5e4[];
struct C_0083cad0 { int FUN_0083cad0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x0083cd90
extern "C" void __fastcall FUN_0083cd90(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    t1002 = (int)((int)(self) + (int)16);
    *(int*)((char*)((int)(self))) = (int)((int)g_0141b5e4);
    t1003 = (int)(*(int*)((char*)(t1002) + 8));
    t1004 = (int)(*(int*)((char*)(t1002) + 4));
    t1005 = (int)(t1002);
    ((C_0083cad0*)(t1005))->FUN_0083cad0((unsigned int)(t1004), (unsigned int)(t1003));
    *(int*)((char*)(t1002) + 12) = (int)((int)0);
    if ((unsigned int)*(int*)((char*)(t1002) + 8) > (unsigned int)1) {
        t1009 = (int)(*(int*)((char*)(t1002) + 4));
        FUN_00f47380((unsigned int)(t1009));
    }
    return;
}
