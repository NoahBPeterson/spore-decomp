// 0x00ec08d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ebfad0/s00ebfad0.cpp.

extern "C" unsigned char g_0145f924[];
extern "C" unsigned char g_0168d824[];
struct C_00c047d0 { int FUN_00c047d0(); };
struct C_00d997e0 { void FUN_00d997e0(); };
struct C_00f30bc0 { int FUN_00f30bc0(); };
struct C_00f30cc0 { int FUN_00f30cc0(unsigned int, float, float); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00ec08d0
extern "C" float __cdecl FUN_00ec08d0(int a4, int a8, int a12, int a16, int a20, int a24)
{
    int t1001;
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1015;
    int t1018;
    int t1021;
    int t1023;
    int t1024;
    int t1028;
    t1001 = (int)((int)(a4));
    t1002 = (int)(t1001);
    t1003 = (int)((C_00c047d0*)(t1002))->FUN_00c047d0();
    if (t1003 != (int)5) {
        t1006 = (int)(t1001);
        t1007 = (int)((C_00c047d0*)(t1006))->FUN_00c047d0();
        if (t1007 != (int)4) goto Lec0964;
    }
    if (t1001 != (int)0) {
        t1010 = (int)(t1001 + (int)1448);
    } else {
        t1010 = (int)((int)0);
    }
    t1011 = (int)((int)(*(int*)g_0168d824));
    if (t1011 == (int)0) {
        t1012 = (int)FUN_00f473a0((unsigned int)((int)36), (unsigned int)((int)g_0145f924), (unsigned int)(t1011), (unsigned int)(t1011), (unsigned int)(t1011), (unsigned int)(t1011));
        if (t1012 != (int)0) {
            t1015 = (int)(t1012);
            t1011 = (int)((C_00f30bc0*)(t1015))->FUN_00f30bc0();
        } else {
            t1011 = (int)((int)0);
        }
        *(int*)g_0168d824 = (int)(t1011);
    }
    t1018 = (int)(t1011);
    t1007 = (int)((C_00f30cc0*)(t1018))->FUN_00f30cc0((unsigned int)(t1010), (float)((float)0), (float)((float)0));
    t1021 = (int)(t1007);
    if (t1021 != (int)0) {
        t1023 = (int)((int)(a20));
        if (t1023 != (int)0) {
            t1024 = (int)(t1023);
            ((C_00d997e0*)(t1024))->FUN_00d997e0();
        }
        t1028 = (int)((int)(a24));
        *(unsigned char*)((char*)(t1028)) = (unsigned char)((int)1);
        *(int*)((char*)(t1023) + 4) = (int)(t1021);
        return (float)((float)1);
    }
    Lec0964:;
    return (float)((float)0);
}
