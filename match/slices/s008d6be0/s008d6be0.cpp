// 0x008d6be0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/DatabaseDirectoryFiles.cpp, match/slices/s008d62f0/s008d62f0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int, int);
};

struct C_008d6be0 { void FUN_008d6be0(unsigned int); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x008d6be0
// @ 0x008d6be0
extern "C" void __fastcall FUN_008d6be0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1007;
    int t1008;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1020;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1002 != (int)0) {
        do {
            t1007 = (int)(*(int*)((char*)(t1002)));
            t1008 = (int)(t1004);
            ((C_008d6be0*)(t1008))->FUN_008d6be0((unsigned int)(t1007));
            t1012 = (int)(*(int*)((char*)(t1002) + 16));
            t1013 = (int)(*(int*)((char*)(t1002) + 24));
            t1014 = (int)(*(int*)((char*)(t1002) + 4));
            t1015 = (int)(t1013 - t1012);
            t1016 = (int)(t1015 & (int)(-2));
            if (t1016 > (int)2) {
                if (t1012 != (int)0) {
                    FUN_00f47380((unsigned int)(t1012));
                }
            }
            t1020 = (int)(*(int*)((char*)(t1004) + 24));
            ((il2c_vc0*)(t1020))->s3((int)(t1002), (int)((int)36));
            t1002 = (int)(t1014);
        } while (t1014 != (int)0);
    }
    return;
}
