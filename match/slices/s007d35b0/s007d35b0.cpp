// 0x007d35b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPAppGameModelDescription.cpp, match/slices/s007d2a30/s007d2a30.cpp.

struct C_0050d4e0 { void FUN_0050d4e0(unsigned int); };
struct C_007d2f90 { void FUN_007d2f90(unsigned int); };
struct C_007d30d0 { void FUN_007d30d0(unsigned int); };
struct C_007f1ac0 { void FUN_007f1ac0(unsigned int); };

// @ 0x007d35b0
extern "C" int __fastcall FUN_007d35b0(char* self, int edx_unused, int a4)
{
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
    int t1014;
    int t1015;
    int t1019;
    int t1020;
    int t1024;
    int t1025;
    int t1029;
    int t1030;
    int t1034;
    unsigned char t1035;
    unsigned char t1036;
    int t1037;
    int t1039;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1002 != (int)0) {
        t1005 = (int)(t1002 + (int)8);
    } else {
        t1005 = (int)((int)0);
    }
    t1006 = (int)(*(int*)((char*)(t1005)));
    *(int*)((char*)(t1004) + 8) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1002) + 12));
    *(int*)((char*)(t1004) + 12) = (int)(t1007);
    *(float*)((char*)(t1004) + 16) = (float)(*(float*)((char*)(t1002) + 16));
    t1008 = (int)(*(int*)((char*)(t1002) + 20));
    *(int*)((char*)(t1004) + 20) = (int)(t1008);
    t1009 = (int)(*(int*)((char*)(t1002) + 24));
    *(int*)((char*)(t1004) + 24) = (int)(t1009);
    t1010 = (int)(*(int*)((char*)(t1002) + 28));
    *(int*)((char*)(t1004) + 28) = (int)(t1010);
    *(float*)((char*)(t1004) + 32) = (float)(*(float*)((char*)(t1002) + 32));
    t1011 = (int)(*(int*)((char*)(t1002) + 36));
    *(int*)((char*)(t1004) + 36) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1002) + 40));
    *(int*)((char*)(t1004) + 40) = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1002) + 44));
    t1014 = (int)(t1002 + (int)48);
    *(int*)((char*)(t1004) + 44) = (int)(t1013);
    t1015 = (int)(t1004 + (int)48);
    ((C_007d2f90*)(t1015))->FUN_007d2f90((unsigned int)(t1014));
    t1019 = (int)(t1002 + (int)68);
    t1020 = (int)(t1004 + (int)68);
    ((C_007f1ac0*)(t1020))->FUN_007f1ac0((unsigned int)(t1019));
    t1024 = (int)(t1002 + (int)88);
    t1025 = (int)(t1004 + (int)88);
    ((C_007d30d0*)(t1025))->FUN_007d30d0((unsigned int)(t1024));
    t1029 = (int)(t1002 + (int)108);
    t1030 = (int)(t1004 + (int)108);
    ((C_0050d4e0*)(t1030))->FUN_0050d4e0((unsigned int)(t1029));
    t1034 = (int)(*(int*)((char*)(t1002) + 128));
    *(int*)((char*)(t1004) + 128) = (int)(t1034);
    t1035 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 132));
    *(unsigned char*)((char*)(t1004) + 132) = (unsigned char)(t1035);
    t1036 = (unsigned char)(*(unsigned char*)((char*)(t1002) + 133));
    *(unsigned char*)((char*)(t1004) + 133) = (unsigned char)(t1036);
    t1037 = (int)(*(int*)((char*)(t1002) + 136));
    *(int*)((char*)(t1004) + 136) = (int)(t1037);
    t1039 = (int)(t1004);
    return (int)(t1039);
}
