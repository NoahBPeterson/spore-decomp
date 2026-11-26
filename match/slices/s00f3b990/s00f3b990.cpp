// 0x00f3b990: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f3b0c0/s00f3b0c0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_0175cdc9[];
struct C_00b225d0 { int FUN_00b225d0(); };
extern "C" int __stdcall FUN_00b3d300(unsigned int);

// @ 0x00f3b990
extern "C" void __fastcall FUN_00f3b990(char* self, int edx_unused)
{
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1014;
    if ((int)(self) != (int)0) {
        t1006 = (int)((il2c_vc0*)((int)(self)))->s3((int)((int)g_0175cdc9));
        t1007 = (int)(t1006);
        if (t1007 != (int)0) {
            t1006 = (int)(*(int*)((char*)(t1007) + 84));
            if (t1006 != (int)0) {
                t1010 = (int)FUN_00b3d300((unsigned int)(t1006));
                t1011 = (int)(t1010);
                t1006 = (int)((C_00b225d0*)(t1011))->FUN_00b225d0();
                t1014 = (int)(*(int*)((char*)(t1007) + 84));
                if (t1014 != (int)0) {
                    *(int*)((char*)(t1007) + 84) = (int)((int)0);
                    ((il2c_vc1*)(t1014))->s1();
                    return;
                }
            }
        }
    }
    return;
}
