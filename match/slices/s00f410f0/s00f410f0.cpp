// 0x00f410f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f40d00/s00f40d00.cpp.

struct C_00dfb850 { void FUN_00dfb850(unsigned int, unsigned int); };
struct C_00f3c160 { int FUN_00f3c160(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x00f410f0
extern "C" int __fastcall FUN_00f410f0(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1003;
    int t1004;
    int t1007;
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    int t1016;
    int t1017;
    int t1021;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    int t1032;
    t1001 = (int)((int)(a4));
    t1003 = (int)(t1001);
    t1004 = (int)(t1003 * (int)568);
    t1007 = (int)((int)(self));
    t1008 = (int)(t1004 + (int)*(int*)((char*)(t1007)));
    t1009 = (int)(*(int*)((char*)(t1008) + 528));
    if (t1009 != (int)0) {
        if ((int)*(int*)((char*)(t1009) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1009));
        }
    }
    t1013 = (int)(*(int*)((char*)(t1008) + 48));
    t1014 = (int)(*(int*)((char*)(t1008) + 44));
    t1016 = (int)(t1008 + (int)44);
    t1017 = (int)(t1016);
    ((C_00dfb850*)(t1017))->FUN_00dfb850((unsigned int)(t1014), (unsigned int)(t1013));
    t1021 = (int)(*(int*)((char*)(t1016)));
    if (t1021 != (int)0) {
        if ((int)*(int*)((char*)(t1021) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1021));
        }
    }
    t1025 = (int)(*(int*)((char*)(t1007) + 24));
    t1026 = (int)(*(int*)((char*)(t1008)));
    t1027 = (int)(t1026 & (int)(-1073741824));
    t1028 = (int)(t1025 & (int)1073741823);
    t1029 = (int)(t1027 | t1028);
    t1030 = (int)(t1029 | (int)(-2147483648));
    *(int*)((char*)(t1008)) = (int)(t1030);
    *(int*)((char*)(t1007) + 24) = (int)(t1001);
    if ((int)*(int*)((char*)(t1007) + 20) == t1001) {
        t1032 = (int)(t1007);
        t1028 = (int)((C_00f3c160*)(t1032))->FUN_00f3c160((unsigned int)(t1001));
        *(int*)((char*)(t1007) + 20) = (int)(t1028);
    }
    return (int)(t1028);
}
