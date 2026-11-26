// 0x00dbf390: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};

struct C_00c38b00 { int FUN_00c38b00(); };

// @ 0x00dbf390
extern "C" float __cdecl FUN_00dbf390(int a4)
{
    int t1000;
    int t1003;
    int t1005;
    t1000 = (int)((int)(a4));
    t1003 = (int)((C_00c38b00*)(t1000))->FUN_00c38b00();
    if (t1003 != (int)0) {
        t1005 = (int)(t1003);
        t1003 = (int)((il2c_vc0*)(t1005))->s3((int)((int)(-291823054)));
        if (t1003 != (int)0) {
            return (float)((float)1);
        }
    }
    return (float)((float)0);
}
