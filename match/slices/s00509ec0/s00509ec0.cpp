// 0x00509ec0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00508fd0/s00508fd0.cpp.

#pragma pack(push, 1)
struct Fr0_00509ec0 {
    float v_l24;
    int v_l20;
    int v_l16;
    int v_l12;
    float v_l8;
};
#pragma pack(pop)

// @ 0x00509ec0
extern "C" int __cdecl FUN_00509ec0(int a4, int a8, int a12)
{
    Fr0_00509ec0 fb;
    fb.v_l16 = (int)(int)((unsigned int)a12 >> 1);
    fb.v_l12 = (int)(unsigned int)((unsigned int)(fb.v_l16 + 1) % (unsigned int)3);
    fb.v_l20 = (int)(unsigned int)((unsigned int)(fb.v_l16 + 2) % (unsigned int)3);
    fb.v_l8 = *(float*)((char*)a8 + fb.v_l12 * 4);
    fb.v_l24 = *(float*)((char*)a8 + fb.v_l20 * 4);
    if ((a12 & 1) != 0) {
        fb.v_l8 = (float)-(float)fb.v_l8;
    }
    *(float*)(char*)a4 = (float)fb.v_l8;
    *(float*)((char*)a4 + 4) = (float)fb.v_l24;
    return a4;
}
