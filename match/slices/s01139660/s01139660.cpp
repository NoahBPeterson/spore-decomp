// 0x01139660: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/plugins/_at_01130000.cpp, match/slices/s011388f0/s011388f0.cpp.

extern "C" void __cdecl FUN_01139390(...);
extern "C" void __cdecl FUN_01139500(...);
// @ 0x01139660
extern "C" int __fastcall FUN_01139660(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1002;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1015;
    int t1016;
    int t1017;
    t1000 = (int)((int)(a4));
    t1002 = (int)(*(int*)((char*)((int)(self)) + 4));
    if (t1000 == (int)0) {
        t1004 = (int)(*(int*)((char*)(t1002) + 180));
        t1005 = (int)(*(int*)((char*)(t1002) + 32));
        t1006 = (int)(t1005 + t1004);
        t1007 = (int)(t1004 + (int)32);
        *(int*)((char*)(t1002) + 180) = (int)(t1007);
        *(int*)((char*)(t1006) + 4) = (int)((int)(self));
        t1008 = (int)((int)(a8));
        *(int*)((char*)(t1006)) = (int)((int)&FUN_01139500);
        *(int*)((char*)(t1006) + 8) = (int)((int)32);
        t1009 = (int)(*(int*)((char*)(t1008)));
        *(int*)((char*)(t1006) + 12) = (int)(t1009);
        t1010 = (int)(*(int*)((char*)(t1008) + 4));
        *(int*)((char*)(t1006) + 16) = (int)(t1010);
        t1011 = (int)(*(int*)((char*)(t1008) + 8));
        *(int*)((char*)(t1006) + 20) = (int)(t1011);
        t1012 = (int)(*(int*)((char*)(t1008) + 12));
        *(int*)((char*)(t1006) + 24) = (int)(t1012);
        t1013 = (int)(*(int*)((char*)(t1008) + 16));
        *(int*)((char*)(t1006) + 28) = (int)(t1013);
        return (int)(t1006);
    }
    if (t1000 == (int)1) {
        t1015 = (int)(*(int*)((char*)(t1002) + 180));
        t1016 = (int)(*(int*)((char*)(t1002) + 32));
        t1000 = (int)(t1016 + t1015);
        t1017 = (int)(t1015 + (int)8);
        *(int*)((char*)(t1002) + 180) = (int)(t1017);
        *(int*)((char*)(t1000)) = (int)((int)&FUN_01139390);
        *(int*)((char*)(t1000) + 4) = (int)((int)(self));
    }
    return (int)(t1000);
}
