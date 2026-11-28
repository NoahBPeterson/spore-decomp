// 0x007a8790: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007a7d50/s007a7d50.cpp.

struct C_00890560 { void FUN_00890560(); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x007a8790
extern "C" void __fastcall FUN_007a8790(char* self, int edx_unused)
{
    int t1002;
    int t1004;
    int t1005;
    int t1009;
    int t1013;
    int t1014;
    int t1021;
    int t1022;
    int t1029;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 12) != (unsigned char)0) {
        t1004 = (int)(*(int*)((char*)(t1002) + 16));
        *(int*)((char*)(t1004) + 41856) = (int)((int)0);
        *(int*)((char*)(t1004) + 41852) = (int)((int)0);
    }
    t1005 = (int)(*(int*)((char*)(t1002)));
    FUN_00f47380((unsigned int)(t1005));
    t1009 = (int)(*(int*)((char*)(t1002) + 4));
    FUN_00f47380((unsigned int)(t1009));
    t1013 = (int)(*(int*)((char*)(t1002) + 16));
    if (t1013 != (int)0) {
        t1014 = (int)(t1013 + (int)40960);
        ((C_00890560*)(t1014))->FUN_00890560();
        FUN_00f47380((unsigned int)(t1013));
    }
    t1021 = (int)(*(int*)((char*)(t1002) + 20));
    if (t1021 != (int)0) {
        t1022 = (int)(t1021);
        ((C_00890560*)(t1022))->FUN_00890560();
        FUN_00f47380((unsigned int)(t1021));
    }
    t1029 = (int)(*(int*)((char*)(t1002) + 24));
    FUN_00f47380((unsigned int)(t1029));
    return;
}
