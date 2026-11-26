// 0x006ff100: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsFragmentVS.cpp, match/slices/s006fe430/s006fe430.cpp.

struct C_00454cb0 { void FUN_00454cb0(unsigned int, unsigned int); };
struct C_006fb9e0 { void FUN_006fb9e0(unsigned int); };

// @ 0x006ff100
extern "C" int __fastcall FUN_006ff100(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1020;
    int t1021;
    int t1025;
    int t1026;
    unsigned char t1027;
    unsigned char t1028;
    unsigned char t1029;
    int t1031;
    t1002 = (int)((int)(a4));
    t1003 = (int)(*(int*)((char*)(t1002)));
    t1005 = (int)((int)(self));
    *(int*)((char*)(t1005)) = (int)(t1003);
    t1006 = (int)(t1002 + (int)4);
    t1007 = (int)(t1005 + (int)4);
    if (t1006 != t1007) {
        t1008 = (int)(*(int*)((char*)(t1006) + 4));
        t1009 = (int)(*(int*)((char*)(t1006)));
        ((C_00454cb0*)(t1007))->FUN_00454cb0((unsigned int)(t1009), (unsigned int)(t1008));
    }
    t1013 = (int)(t1002 + (int)20);
    t1014 = (int)(t1005 + (int)20);
    if (t1013 != t1014) {
        t1015 = (int)(*(int*)((char*)(t1013) + 4));
        t1016 = (int)(*(int*)((char*)(t1013)));
        ((C_00454cb0*)(t1014))->FUN_00454cb0((unsigned int)(t1016), (unsigned int)(t1015));
    }
    t1020 = (int)(t1002 + (int)36);
    t1021 = (int)(t1005 + (int)36);
    ((C_006fb9e0*)(t1021))->FUN_006fb9e0((unsigned int)(t1020));
    t1025 = (int)(*(int*)((char*)(t1002) + 56));
    *(int*)((char*)(t1005) + 56) = (int)(t1025);
    t1026 = (int)(*(int*)((char*)(t1002) + 60));
    *(int*)((char*)(t1005) + 60) = (int)(t1026);
    t1027 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 64));
    *(unsigned char*)((char*)(t1005) + 64) = (unsigned char)(t1027);
    t1028 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 65));
    *(unsigned char*)((char*)(t1005) + 65) = (unsigned char)(t1028);
    t1029 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 66));
    *(unsigned char*)((char*)(t1005) + 66) = (unsigned char)(t1029);
    t1031 = (int)(t1005);
    return (int)(t1031);
}
