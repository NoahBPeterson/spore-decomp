// 0x007fd2d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007fc880/s007fc880.cpp, src/game/Spui/SPUIBehavior.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};
struct il2c_vc2 {
    virtual void s0();
};

struct C_007f53c0 { int FUN_007f53c0(unsigned int); };
#pragma pack(push, 1)
struct Fr0_007fd2d0 {
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)

// @ 0x007fd2d0
extern "C" bool __cdecl FUN_007fd2d0(int a4, int a8, int a12)
{
    Fr0_007fd2d0 fb;
    fb.v_l12 = (int)(int)*(int*)((char*)a8 + 4);
    fb.v_l8 = (int)((C_007f53c0*)a4)->FUN_007f53c0((unsigned int)a12);
    fb.v_l16 = 0;
    for (; (unsigned int)fb.v_l16 < (unsigned int)*(int*)((char*)a12 + 20); fb.v_l16 = fb.v_l16 + 1, fb.v_l8 = fb.v_l8 + 4, fb.v_l12 = fb.v_l12 + 4) {
        fb.v_l24 = 0;
        fb.v_l20 = (int)(int)*(int*)(char*)fb.v_l8;
        if (fb.v_l20 != 0) {
            ((il2c_vc0*)fb.v_l20)->s1();
        }
        fb.v_l28 = (int)(int)*(int*)(char*)fb.v_l12;
        if (fb.v_l28 != 0) {
            fb.v_l24 = ((il2c_vc1*)fb.v_l28)->s3(37985327);
            if (fb.v_l24 != 0) {
                ((il2c_vc2*)fb.v_l24)->s0();
            }
        }
        *(int*)(char*)fb.v_l8 = fb.v_l24;
    }
    return (bool)(unsigned char)1;
}
