// 0x00b45b50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00b40000.cpp, match/slices/s00b45170/s00b45170.cpp.

struct C_00921440 { void FUN_00921440(unsigned int, unsigned int, unsigned int, unsigned int); };
struct C_00b41dc0 { int FUN_00b41dc0(unsigned int); };
struct C_00ef7c00 { void FUN_00ef7c00(unsigned int); };

// @ 0x00b45b50
// @ 0x00b45b50
extern "C" int __fastcall FUN_00b45b50(char* self, int edx_unused, int a4, int a8, int a12)
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
    int t1024;
    int t1025;
    int t1028;
    int t1029;
    int t1031;
    unsigned int t1033;
    int t1034;
    int t1038;
    int t15;
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
            if (t1002 == (int)*(int*)((char*)(t1016))) goto Lb45bf3;
            t1016 = (int)(*(int*)((char*)(t1016) + 4));
        } while (t1016 != (int)0);
    }
    t1017 = (int)(*(int*)((char*)(t1006) + 12));
    t1018 = (int)((int)&v_l8);
    t1019 = (int)(t1006 + (int)16);
    ((C_00921440*)(t1019))->FUN_00921440((unsigned int)(t1018), (unsigned int)(t1009), (unsigned int)(t1017), (unsigned int)((int)1));
    t1023 = (int)((int)(a8));
    t1024 = (int)(t1006);
    t1025 = (int)((C_00b41dc0*)(t1024))->FUN_00b41dc0((unsigned int)(t1023));
    t1028 = (int)(t1025);
    if ((unsigned char)((*(int*)&v_l8[0])) != (unsigned char)0) {
        t1029 = (int)((*(int*)&v_l8[1]));
        t1031 = (int)(t1002);
        t1033 = (unsigned int)((unsigned int)(t1031) % (unsigned int)(t1029));
        t1034 = (int)(t1006);
        t1014 = (int)((int)(t1033));
        ((C_00ef7c00*)(t1034))->FUN_00ef7c00((unsigned int)(t1029));
    }
    t1038 = (int)(*(int*)((char*)(t1006) + 4));
    t15 = (int)(t1014 << (int)2);
    t1039 = (int)(t15);
    t1040 = (int)(*(int*)((char*)(t1039) + t1038));
    *(int*)((char*)(t1028) + 4) = (int)(t1040);
    t1041 = (int)(*(int*)((char*)(t1006) + 4));
    *(int*)((char*)(t1039) + t1041) = (int)(t1028);
    *(int*)((char*)(t1006) + 12) += (int)1;
    t1042 = (int)(*(int*)((char*)(t1006) + 4));
    t1043 = (int)(t1042 + t1039);
    t1044 = (int)((int)(a4));
    *(int*)((char*)(t1044)) = (int)(t1028);
    *(int*)((char*)(t1044) + 4) = (int)(t1043);
    *(unsigned char*)((char*)(t1044) + 8) = (unsigned char)((int)1);
    return (int)(t1044);
    Lb45bf3:;
    t1049 = (int)((int)(a4));
    *(int*)((char*)(t1049)) = (int)(t1016);
    *(int*)((char*)(t1049) + 4) = (int)(t1015);
    *(unsigned char*)((char*)(t1049) + 8) = (unsigned char)((int)0);
    return (int)(t1049);
}
