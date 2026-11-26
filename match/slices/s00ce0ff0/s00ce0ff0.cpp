// 0x00ce0ff0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPTribePlanner.cpp, match/slices/s00cdfea0/s00cdfea0.cpp.

struct C_00427fd0 { void FUN_00427fd0(unsigned int); };
struct C_00bc3130 { void FUN_00bc3130(); };
struct C_00bcaf70 { int FUN_00bcaf70(unsigned int, unsigned int, unsigned int); };
struct C_00ce0e60 { int FUN_00ce0e60(unsigned int, unsigned int); };

// @ 0x00ce0ff0
extern "C" int __cdecl FUN_00ce0ff0(int a4, int a8, int a12, int a16, int a20)
{
    int t1000;
    int t1002;
    int t1004;
    int t1005;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    unsigned char t1019;
    int t1020;
    int t1024;
    int t1025;
    int t1029;
    int t1030;
    int t1035;
    t1000 = (int)((int)(a12));
    t1002 = (int)((int)(a8));
    t1004 = (int)((int)(a4));
    t1005 = (int)(*(int*)((char*)(t1004) + 4));
    t1009 = (int)((C_00ce0e60*)(t1005))->FUN_00ce0e60((unsigned int)(t1002), (unsigned int)(t1000));
    t1010 = (int)(*(int*)((char*)(t1009) + 8));
    if (t1010 != (int)(-1)) {
        if (t1010 != (int)0) {
            t1011 = (int)(t1010 - (int)1);
            *(int*)((char*)(t1009) + 8) = (int)(t1011);
        }
    }
    t1012 = (int)((int)(a20));
    t1013 = (int)(*(int*)((char*)(t1004) + 4));
    t1014 = (int)(*(int*)((char*)(t1013) + 16));
    t1017 = (int)((C_00bcaf70*)(t1014))->FUN_00bcaf70((unsigned int)(t1002), (unsigned int)(t1012), (unsigned int)((int)1));
    t1018 = (int)(t1017);
    t1019 = (unsigned char)((int)(t1012) != (int)((int)0));
    t1020 = (int)(t1018 + (int)8);
    *(unsigned char*)((char*)(t1018) + 56) = (unsigned char)(t1019);
    ((C_00bc3130*)(t1020))->FUN_00bc3130();
    t1024 = (int)((int)&a12);
    t1025 = (int)(t1018 + (int)57);
    ((C_00427fd0*)(t1025))->FUN_00427fd0((unsigned int)(t1024));
    t1029 = (int)((int)&a16);
    t1030 = (int)(t1018 + (int)77);
    ((C_00427fd0*)(t1030))->FUN_00427fd0((unsigned int)(t1029));
    t1035 = (int)(t1018);
    return (int)(t1035);
}
