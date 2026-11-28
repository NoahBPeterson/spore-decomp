// 0x0112b620: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0112adf0/s0112adf0.cpp.

struct C_0107de70 { int FUN_0107de70(unsigned int, unsigned int); };
struct C_0107e540 { int FUN_0107e540(unsigned int, unsigned int); };
extern "C" void __cdecl FUN_0107f530(...);

// @ 0x0112b620
extern "C" void __fastcall FUN_0112b620(char* self, int edx_unused, int a4, int a8)
{
    int t1001;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1019;
    int t1020;
    int t1021;
    int t7;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    t1001 = (int)((int)(a4));
    t1006 = (int)((int)(self));
    t1007 = (int)(t1006 + (int)12);
    t1008 = (int)(t1007);
    t1009 = (int)((C_0107e540*)(t1008))->FUN_0107e540((unsigned int)(t1001), (unsigned int)((int)(-1)));
    t1012 = (int)(*(int*)((char*)(t1006) + 4));
    t1013 = (int)(t1009);
    t1014 = (int)(*(int*)((char*)(t1006) + 8));
    t1015 = (int)(t1014 & (int)1073741823);
    if (t1012 == t1015) {
        FUN_0107f530((unsigned int)(t1006), (unsigned int)((int)8));
    }
    t1019 = (int)(*(int*)((char*)(t1006) + 4));
    t1020 = (int)(*(int*)((char*)(t1006)));
    t1021 = (int)((int)(a8));
    t7 = (int)(t1019 << (int)3);
    t1022 = (int)(t1020 + t7);
    t1023 = (int)(t1019 + (int)1);
    *(int*)((char*)(t1006) + 4) = (int)(t1023);
    t1024 = (int)(*(int*)((char*)(t1021)));
    *(int*)((char*)(t1022)) = (int)(t1024);
    *(int*)((char*)(t1022) + 4) = (int)(t1013);
    t1025 = (int)(*(int*)((char*)(t1006) + 4));
    t1026 = (int)(t1025 - (int)1);
    t1027 = (int)(t1007);
    ((C_0107de70*)(t1027))->FUN_0107de70((unsigned int)(t1001), (unsigned int)(t1026));
    return;
}
