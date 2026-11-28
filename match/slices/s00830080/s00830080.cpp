// 0x00830080: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0082f9a0/s0082f9a0.cpp, src/game/Spui/_at_00830000.cpp.

extern "C" void __cdecl FUN_00830020(...);
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};

extern "C" int __cdecl FUN_00807d30(...);

// @ 0x00830080
extern "C" void __cdecl FUN_00830080(int a4)
{
    int t1000;
    int t1004;
    int t1006;
    int t1007;
    unsigned char t1008;
    int t1009;
    int v_l8[2];
    int t1010;
    int t1014;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)0) {
        t1004 = (int)((il2c_vc0*)(t1000))->s3((int)((int)788569552));
        t1006 = (int)(t1004);
    } else {
        t1006 = (int)((int)0);
    }
    t1007 = (int)(*(int*)((char*)(t1006) + 16));
    (*(int*)&v_l8[1]) = (int)(t1007);
    t1008 = (unsigned char)(*(unsigned char*)((char*)(t1006) + 12));
    t1009 = (int)((int)&v_l8);
    *(unsigned char*)&v_l8[0] = (unsigned char)(t1008);
    t1010 = (int)(*(int*)((char*)(t1006) + 32));
    FUN_00807d30((unsigned int)(t1010), (unsigned int)((int)&FUN_00830020), (unsigned int)(t1009));
    t1014 = (int)(*(int*)((char*)(t1006) + 32));
    if (t1014 != (int)0) {
        *(int*)((char*)(t1006) + 32) = (int)((int)0);
        ((il2c_vc1*)(t1014))->s1();
    }
    return;
}
