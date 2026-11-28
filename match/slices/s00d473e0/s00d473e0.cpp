// 0x00d473e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureModeStrategy.cpp, match/slices/s00d463a0/s00d463a0.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f09b4[];
struct C_00d47320 { void FUN_00d47320(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00d473e0
extern "C" int __fastcall FUN_00d473e0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1008;
    int t1009;
    int t1013;
    t1002 = (int)(*(int*)((char*)((int)(self)) + 28));
    if (t1002 != (int)0) {
        t1003 = (int)(*(int*)((char*)(t1002)));
        *(int*)((char*)((int)(self)) + 28) = (int)(t1003);
    } else {
        t1004 = (int)(*(int*)((char*)((int)(self)) + 44));
        t1005 = (int)FUN_00f473a0((unsigned int)(t1004), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
        t1002 = (int)(t1005);
    }
    if (t1002 != (int)0) {
        t1008 = (int)((int)(a4));
        t1009 = (int)(t1002);
        ((C_00d47320*)(t1009))->FUN_00d47320((unsigned int)(t1008));
    }
    t1013 = (int)(t1002);
    *(int*)((char*)(t1002) + 388) = (int)((int)0);
    return (int)(t1013);
}
