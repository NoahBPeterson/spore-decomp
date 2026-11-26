// 0x008de7f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008de020/s008de020.cpp, src/game/UTFSpore_Win32/Manager.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int, int);
};


// @ 0x008de7f0
extern "C" void __fastcall FUN_008de7f0(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1004;
    int t1006;
    int t1008;
    int t1009;
    int t1011;
    t1002 = (int)((int)0);
    t1004 = (int)((int)(self));
    if ((unsigned int)((int)(a8)) > (unsigned int)(t1002)) {
        t1006 = (int)((int)(a4));
        do {
            t1008 = (int)(*(int*)((char*)(t1006) + (t1002)*4));
            if (t1008 != (int)0) {
                do {
                    t1009 = (int)(*(int*)((char*)(t1004) + 28));
                    t1011 = (int)(t1008);
                    t1008 = (int)(*(int*)((char*)(t1008) + 8));
                    ((il2c_vc0*)(t1009))->s3((int)(t1011), (int)((int)12));
                } while (t1008 != (int)0);
            }
            *(int*)((char*)(t1006) + (t1002)*4) = (int)((int)0);
            t1002 = (int)(t1002 + (int)1);
        } while ((unsigned int)(t1002) < (unsigned int)((int)(a8)));
    }
    return;
}
