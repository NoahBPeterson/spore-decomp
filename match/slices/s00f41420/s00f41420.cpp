// 0x00f41420: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f40d00/s00f40d00.cpp.

extern "C" int __cdecl FUN_00eeca30(...);
struct C_00f3b9e0 { int FUN_00f3b9e0(unsigned int, unsigned int, unsigned int); };
struct C_00f3ff70 { int FUN_00f3ff70(unsigned int); };
struct C_00f40ed0 { int FUN_00f40ed0(unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x00f41420
extern "C" bool __fastcall FUN_00f41420(char* self, int edx_unused, int a4, int a8, int a12, int a16)
{
    int t1001;
    int t1004;
    int t1007;
    int t1008;
    int t1011;
    int t1014;
    int t1017;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1026;
    bool t1030;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1007 = (int)FUN_00eeca30((unsigned int)(t1001));
    if (t1007 != (int)0) {
        t1008 = (int)(t1004);
        t1011 = (int)((C_00f3b9e0*)(t1008))->FUN_00f3b9e0((unsigned int)(t1001), (unsigned int)(t1007), (unsigned int)((int)0));
        if ((unsigned char)(t1011) == (unsigned char)0) {
            *(int*)((char*)(t1001) + 548) |= (int)16;
            return 0;
        }
        *(int*)((char*)(t1001) + 548) &= (int)(-17);
    }
    t1014 = (int)(t1004);
    t1017 = (int)((C_00f3ff70*)(t1014))->FUN_00f3ff70((unsigned int)(t1001));
    if ((unsigned char)(t1017) == (unsigned char)0) {
        *(int*)((char*)(t1001) + 548) |= (int)2;
        return 0;
    }
    t1020 = (int)((int)(a16));
    t1021 = (int)((int)(a12));
    t1022 = (int)((int)(a8));
    *(int*)((char*)(t1001) + 548) &= (int)(-3);
    t1023 = (int)(t1004);
    t1026 = (int)((C_00f40ed0*)(t1023))->FUN_00f40ed0((unsigned int)(t1001), (unsigned int)(t1022), (unsigned int)(t1021), (unsigned int)(t1020));
    if ((unsigned char)(t1026) == (unsigned char)0) {
        *(int*)((char*)(t1001) + 548) |= (int)4;
        return 0;
    }
    *(int*)((char*)(t1001) + 548) &= (int)(-5);
    t1030 = true;
    return (bool)(t1030);
}
