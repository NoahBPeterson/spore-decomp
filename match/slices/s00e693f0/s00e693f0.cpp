// 0x00e693f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00e686c0/s00e686c0.cpp.

extern "C" unsigned char g_016b3c04[];
struct C_00b72210 { int FUN_00b72210(unsigned int); };
extern "C" void __cdecl FUN_00e69000(unsigned int, unsigned int, float, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

// @ 0x00e693f0
extern "C" int __cdecl FUN_00e693f0(int a4, int a8, int a12, float a16, int a20)
{
    int t1001;
    int t1002;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    float t1015;
    int t1016;
    int t1017;
    int v_l4;
    int t1018;
    int t1019;
    int t1023;
    int t1025;
    t1001 = (int)((int)(a8));
    t1002 = (int)(*(int*)((char*)(t1001)));
    t1005 = (int)((int)(a20));
    *(int*)((char*)(t1005)) = (int)(t1002);
    t1006 = (int)((int)1);
    goto Le69410;
    Le69410:;
    t1009 = (int)(*(int*)((char*)(t1005) + (t1006)*4 - 4));
    t1010 = (int)((int)(*(int*)g_016b3c04));
    t1011 = (int)(t1010 + (int)28);
    t1012 = (int)((C_00b72210*)(t1011))->FUN_00b72210((unsigned int)(t1009));
    t1015 = (float)((float)(a16));
    t1016 = (int)((int)&a20);
    t1017 = (int)((int)&v_l4);
    t1018 = (int)((int)&a8);
    t1019 = (int)(t1012 + (int)76);
    *(int*)&(a8) = (int)((int)0);
    *(float*)&(a20) = (float)(t1015);
    FUN_00e69000((unsigned int)(t1012), (unsigned int)(t1019), (float)((float)(a16)), (unsigned int)(t1018), (unsigned int)(t1017), (unsigned int)(t1016), (unsigned int)(t1005), (unsigned int)(t1006));
    t1023 = (int)((int)(a8));
    if (t1023 != (int)0) {
        *(int*)((char*)(t1005) + (t1006)*4) = (int)(t1023);
        t1006 = (int)(t1006 + (int)1);
        if (t1006 < (int)32) goto Le69410;
    }
    t1025 = (int)(t1006);
    return (int)(t1025);
}
