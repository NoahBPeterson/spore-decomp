// 0x00e264b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUIPosse.cpp, match/slices/s00e25710/s00e25710.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};

extern "C" void __cdecl FUN_00e245c0(...);

// @ 0x00e264b0
extern "C" int __cdecl FUN_00e264b0(int a4, int a8, int a12, int a16, int a20)
{
    int t1001;
    int t1003;
    int t1005;
    int t1006;
    int t1010;
    int t1011;
    int t1014;
    int t1015;
    int t1018;
    int t1021;
    int t1027;
    int t1033;
    t1001 = (int)((int)(a20));
    t1003 = (int)((int)(a8));
    t1005 = (int)((int)(a4));
    Le264c0:;
    t1006 = (int)((int)&a12);
    t1010 = (int)((int (__cdecl*)(int, int))(t1001))((int)(t1005), (int)(t1006));
    if ((unsigned char)(t1010) != (unsigned char)0) {
        t1005 = (int)(t1005 + (int)8);
        goto Le264c0;
    }
    t1003 = (int)(t1003 - (int)8);
    t1011 = (int)((int)&a12);
    t1014 = (int)((int (__cdecl*)(int, int))(t1001))((int)(t1011), (int)(t1003));
    if ((unsigned char)(t1014) != (unsigned char)0) {
        do {
            t1003 = (int)(t1003 - (int)8);
            t1015 = (int)((int)&a12);
            t1018 = (int)((int (__cdecl*)(int, int))(t1001))((int)(t1015), (int)(t1003));
        } while ((unsigned char)(t1018) != (unsigned char)0);
    }
    if ((unsigned int)(t1005) < (unsigned int)(t1003)) {
        FUN_00e245c0((unsigned int)(t1005), (unsigned int)(t1003));
        t1005 = (int)(t1005 + (int)8);
        goto Le264c0;
    }
    t1021 = (int)((int)(a16));
    if (t1021 != (int)0) {
        ((il2c_vc0*)(t1021))->s1();
    }
    t1027 = (int)((int)(a12));
    if (t1027 != (int)0) {
        ((il2c_vc1*)(t1027))->s1();
    }
    t1033 = (int)(t1005);
    return (int)(t1033);
}
