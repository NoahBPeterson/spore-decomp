// 0x00af09a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00af0000.cpp, match/slices/s00af08e0/s00af08e0.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f09b4[];
struct C_00af08e0 { int FUN_00af08e0(unsigned int, unsigned int); };
struct C_00af09a0 { int FUN_00af09a0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00af09a0
extern "C" int __fastcall FUN_00af09a0(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1004;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    unsigned char t1027;
    int t1028;
    int t1029;
    int t1030;
    int t1033;
    int t1041;
    t1000 = (int)((int)(a8));
    t1004 = (int)((int)(a4));
    t1007 = (int)((int)(self));
    t1008 = (int)((C_00af08e0*)((int)(self)))->FUN_00af08e0((unsigned int)(t1004), (unsigned int)(t1000));
    t1011 = (int)(t1008);
    t1012 = (int)(*(int*)((char*)(t1004)));
    *(int*)&(a8) = (int)(t1011);
    if (t1012 != (int)0) {
        t1013 = (int)(t1007);
        t1014 = (int)((C_00af09a0*)(t1013))->FUN_00af09a0((unsigned int)(t1012), (unsigned int)(t1011));
        *(int*)((char*)(t1011)) = (int)(t1014);
    }
    t1017 = (int)(*(int*)((char*)(t1004) + 4));
    if (t1017 != (int)0) {
        do {
            t1018 = (int)FUN_00f473a0((unsigned int)((int)32), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
            t1021 = (int)(t1018);
            t1022 = (int)(t1021 + (int)16);
            if (t1022 != (int)0) {
                t1023 = (int)(*(int*)((char*)(t1017) + 16));
                *(int*)((char*)(t1022)) = (int)(t1023);
                t1024 = (int)(*(int*)((char*)(t1017) + 20));
                *(int*)((char*)(t1022) + 4) = (int)(t1024);
                t1025 = (int)(*(int*)((char*)(t1017) + 24));
                *(int*)((char*)(t1022) + 8) = (int)(t1025);
                t1026 = (int)(*(int*)((char*)(t1017) + 28));
                *(int*)((char*)(t1022) + 12) = (int)(t1026);
            }
            *(int*)((char*)(t1021)) = (int)((int)0);
            *(int*)((char*)(t1021) + 4) = (int)((int)0);
            *(int*)((char*)(t1021) + 8) = (int)(t1011);
            t1027 = (unsigned char)(*(unsigned char*)((char*)(t1017) + 12));
            *(unsigned char*)((char*)(t1021) + 12) = (unsigned char)(t1027);
            *(int*)((char*)(t1011) + 4) = (int)(t1021);
            t1028 = (int)(*(int*)((char*)(t1017)));
            if (t1028 != (int)0) {
                t1029 = (int)(t1007);
                t1030 = (int)((C_00af09a0*)(t1029))->FUN_00af09a0((unsigned int)(t1028), (unsigned int)(t1021));
                *(int*)((char*)(t1021)) = (int)(t1030);
            }
            t1017 = (int)(*(int*)((char*)(t1017) + 4));
            t1011 = (int)(t1021);
        } while (t1017 != (int)0);
        t1033 = (int)((int)(a8));
        return (int)(t1033);
    }
    t1041 = (int)(t1011);
    return (int)(t1041);
}
