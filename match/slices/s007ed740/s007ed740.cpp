// 0x007ed740: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007ed1b0/s007ed1b0.cpp.

struct C_00423650 { void FUN_00423650(unsigned int, unsigned int); };
struct C_0050d4e0 { void FUN_0050d4e0(unsigned int); };
struct C_006f5cd0 { void FUN_006f5cd0(unsigned int); };

// @ 0x007ed740
extern "C" int __fastcall FUN_007ed740(char* self, int edx_unused, int a4)
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
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1024;
    int t1025;
    int t1029;
    int t1030;
    int t1035;
    t1002 = (int)((int)(a4));
    t1003 = (int)(*(int*)((char*)(t1002) + 8));
    t1005 = (int)((int)(self));
    *(int*)((char*)(t1005) + 8) = (int)(t1003);
    t1006 = (int)(t1002 + (int)12);
    t1007 = (int)(t1005 + (int)12);
    if (t1006 != t1007) {
        t1008 = (int)(*(int*)((char*)(t1006) + 4));
        t1009 = (int)(*(int*)((char*)(t1006)));
        ((C_00423650*)(t1007))->FUN_00423650((unsigned int)(t1009), (unsigned int)(t1008));
    }
    t1013 = (int)(*(int*)((char*)(t1002) + 32));
    *(int*)((char*)(t1005) + 32) = (int)(t1013);
    t1014 = (int)(*(int*)((char*)(t1002) + 36));
    *(int*)((char*)(t1005) + 36) = (int)(t1014);
    *(float*)((char*)(t1005) + 40) = (float)(*(float*)((char*)(t1002) + 40));
    t1015 = (int)(*(int*)((char*)(t1002) + 48));
    *(int*)((char*)(t1005) + 48) = (int)(t1015);
    t1016 = (int)(*(int*)((char*)(t1002) + 52));
    *(int*)((char*)(t1005) + 52) = (int)(t1016);
    t1017 = (int)(*(int*)((char*)(t1002) + 56));
    *(int*)((char*)(t1005) + 56) = (int)(t1017);
    t1018 = (int)(*(int*)((char*)(t1002) + 60));
    t1019 = (int)(t1002 + (int)68);
    *(int*)((char*)(t1005) + 60) = (int)(t1018);
    *(float*)((char*)(t1005) + 64) = (float)(*(float*)((char*)(t1002) + 64));
    t1020 = (int)(t1005 + (int)68);
    ((C_006f5cd0*)(t1020))->FUN_006f5cd0((unsigned int)(t1019));
    t1024 = (int)(t1002 + (int)88);
    t1025 = (int)(t1005 + (int)88);
    ((C_0050d4e0*)(t1025))->FUN_0050d4e0((unsigned int)(t1024));
    t1029 = (int)(t1002 + (int)108);
    t1030 = (int)(t1005 + (int)108);
    ((C_0050d4e0*)(t1030))->FUN_0050d4e0((unsigned int)(t1029));
    t1035 = (int)(t1005);
    return (int)(t1035);
}
