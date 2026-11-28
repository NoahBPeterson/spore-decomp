// 0x00c144e0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c14350/s00c14350.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f09b4[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00c144e0
extern "C" int __fastcall FUN_00c144e0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 28));
    if (t1001 != (int)0) {
        t1002 = (int)(*(int*)((char*)(t1001)));
        *(int*)((char*)((int)(self)) + 28) = (int)(t1002);
    } else {
        t1003 = (int)(*(int*)((char*)((int)(self)) + 44));
        t1001 = (int)FUN_00f473a0((unsigned int)(t1003), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    }
    if (t1001 != (int)0) {
        t1006 = (int)((int)(a4));
        t1007 = (int)(*(int*)((char*)(t1006)));
        *(int*)((char*)(t1001)) = (int)(t1007);
        t1008 = (int)(*(int*)((char*)(t1006) + 4));
        *(int*)((char*)(t1001) + 4) = (int)(t1008);
    }
    *(int*)((char*)(t1001) + 8) = (int)((int)0);
    return (int)(t1001);
}
