// 0x0113aa50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/plugins/_at_01130000.cpp, match/slices/s0113a8b0/s0113a8b0.cpp.

extern "C" void __cdecl FUN_0113a770(...);
extern "C" void __cdecl FUN_0113a8b0(...);
// @ 0x0113aa50
extern "C" int __fastcall FUN_0113aa50(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1010;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 4));
    t1002 = (int)(*(int*)((char*)(t1001) + 32));
    t1004 = (int)(*(int*)((char*)(t1001) + 180));
    t1005 = (int)(t1002 + t1004);
    if ((int)(a4) == (int)0) {
        t1006 = (int)(t1004 + (int)12);
        *(int*)((char*)(t1001) + 180) = (int)(t1006);
        t1007 = (int)((int)(a8));
        *(int*)((char*)(t1005)) = (int)((int)&FUN_0113a8b0);
        *(int*)((char*)(t1005) + 4) = (int)((int)(self));
        t1008 = (int)(*(int*)((char*)(t1007)));
        *(int*)((char*)(t1005) + 8) = (int)(t1008);
        return (int)(t1007);
    }
    t1010 = (int)(t1004 + (int)8);
    *(int*)((char*)(t1001) + 180) = (int)(t1010);
    *(int*)((char*)(t1005)) = (int)((int)&FUN_0113a770);
    *(int*)((char*)(t1005) + 4) = (int)((int)(self));
    return (int)(t1001);
}
