// 0x007fd390: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007fc880/s007fc880.cpp, src/game/Spui/_at_007f0000.cpp.

struct il2c_vc0 {
    virtual int s0(int, int);
};

extern "C" unsigned char g_01415b14[];
struct C_007f53c0 { int FUN_007f53c0(unsigned int); };

// @ 0x007fd390
// @ 0x007fd390
extern "C" bool __cdecl FUN_007fd390(int a4, int a8, int a12, int a16)
{
    int v_l8;
    int v_l16;
    int v_l12;
    v_l12 = (int)((C_007f53c0*)a8)->FUN_007f53c0((unsigned int)a12);
    v_l8 = (int)((il2c_vc0*)a16)->s0((int)(int)((int)*(int*)((char*)a12 + 20) << 2), 4);
    if (v_l8 != 0) {
        *(int*)((char*)a4 + 4) = v_l8;
        *(int*)((char*)a4 + 8) = (int)(int)*(int*)((char*)a12 + 20);
        *(int*)(char*)a4 = (int)g_01415b14;
        v_l16 = 0;
        for (; (unsigned int)v_l16 < (unsigned int)*(int*)((char*)a12 + 20); v_l16 = v_l16 + 1, v_l12 = v_l12 + 4, v_l8 = v_l8 + 4) {
            *(int*)(char*)v_l8 = (int)(int)*(int*)(char*)v_l12;
        }
        return (unsigned char)1;
    }
        return (unsigned char)0;
}
