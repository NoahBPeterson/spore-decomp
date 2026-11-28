// 0x006758a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPAStar.cpp, match/slices/s006755c0/s006755c0.cpp.

extern "C" unsigned char g_013eb430[];
extern "C" unsigned char g_013ebb38[];
struct C_00675650 { void FUN_00675650(unsigned int); };
struct C_00921440 { void FUN_00921440(unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x006758a0
extern "C" int __fastcall FUN_006758a0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1000;
    int t1002;
    int t1006;
    int t1009;
    int t1010;
    unsigned int t1012;
    int t1013;
    int t1014;
    int t1;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int v_l8[2];
    int t1019;
    int t1023;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1031;
    unsigned int t1033;
    int t1034;
    int t1038;
    int t20;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    int t1043;
    int t1044;
    int t1049;
    t1000 = (int)((int)(a8));
    t1002 = (int)(*(int*)((char*)(t1000)));
    t1006 = (int)((int)(self));
    t1009 = (int)(*(int*)((char*)(t1006) + 8));
    t1010 = (int)(t1002);
    t1012 = (unsigned int)((unsigned int)(t1010) % (unsigned int)(t1009));
    t1013 = (int)(*(int*)((char*)(t1006) + 4));
    t1014 = (int)((int)(t1012));
    t1 = (int)(t1014 << (int)2);
    t1015 = (int)(t1013 + t1);
    t1016 = (int)(*(int*)((char*)(t1015)));
    if (t1016 != (int)0) {
        do {
            if (t1002 == (int)*(int*)((char*)(t1016))) goto L67596b;
            t1016 = (int)(*(int*)((char*)(t1016) + 4));
        } while (t1016 != (int)0);
    }
    t1017 = (int)(*(int*)((char*)(t1006) + 12));
    t1018 = (int)((int)&v_l8);
    t1019 = (int)(t1006 + (int)16);
    ((C_00921440*)(t1019))->FUN_00921440((unsigned int)(t1018), (unsigned int)(t1009), (unsigned int)(t1017), (unsigned int)((int)1));
    t1023 = (int)FUN_00f473a0((unsigned int)((int)8), (unsigned int)((int)g_013eb430), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    t1026 = (int)(t1023);
    if (t1026 != (int)0) {
        t1027 = (int)((int)(a8));
        t1028 = (int)(*(int*)((char*)(t1027)));
        *(int*)((char*)(t1026)) = (int)(t1028);
    }
    *(int*)((char*)(t1026) + 4) = (int)((int)0);
    if ((unsigned char)((*(int*)&v_l8[0])) != (unsigned char)0) {
        t1029 = (int)((*(int*)&v_l8[1]));
        t1031 = (int)(t1002);
        t1033 = (unsigned int)((unsigned int)(t1031) % (unsigned int)(t1029));
        t1034 = (int)(t1006);
        t1014 = (int)((int)(t1033));
        ((C_00675650*)(t1034))->FUN_00675650((unsigned int)(t1029));
    }
    t1038 = (int)(*(int*)((char*)(t1006) + 4));
    t20 = (int)(t1014 << (int)2);
    t1039 = (int)(t20);
    t1040 = (int)(*(int*)((char*)(t1039) + t1038));
    *(int*)((char*)(t1026) + 4) = (int)(t1040);
    t1041 = (int)(*(int*)((char*)(t1006) + 4));
    *(int*)((char*)(t1039) + t1041) = (int)(t1026);
    *(int*)((char*)(t1006) + 12) += (int)1;
    t1042 = (int)(*(int*)((char*)(t1006) + 4));
    t1043 = (int)(t1042 + t1039);
    t1044 = (int)((int)(a4));
    *(int*)((char*)(t1044)) = (int)(t1026);
    *(int*)((char*)(t1044) + 4) = (int)(t1043);
    *(unsigned char*)((char*)(t1044) + 8) = (unsigned char)((int)1);
    return (int)(t1044);
    L67596b:;
    t1049 = (int)((int)(a4));
    *(int*)((char*)(t1049)) = (int)(t1016);
    *(int*)((char*)(t1049) + 4) = (int)(t1015);
    *(unsigned char*)((char*)(t1049) + 8) = (unsigned char)((int)0);
    return (int)(t1049);
}
