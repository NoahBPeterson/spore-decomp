// 0x005056d0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00505170/s00505170.cpp.

extern "C" unsigned char g_01485378[];

// @ 0x005056d0
// @ 0x005056d0
extern "C" float __cdecl FUN_005056d0(int a4, int a8, int a12)
{
    float v_l8;
    float v_l12;
    v_l8 = (float)*(float*)g_01485378;
    if (*(float*)(char*)a8 > (float)*(float*)(char*)a4) {
        v_l12 = (float)(*(float*)(char*)a4 - (float)*(float*)(char*)a8);
        v_l8 = (float)((float)((float)v_l12 * v_l12) + v_l8);
    } else {
        if (*(float*)(char*)a4 > (float)*(float*)(char*)a12) {
            v_l12 = (float)(*(float*)(char*)a4 - (float)*(float*)(char*)a12);
            v_l8 = (float)((float)((float)v_l12 * v_l12) + v_l8);
        }
    }
    if (*(float*)((char*)a8 + 4) > (float)*(float*)((char*)a4 + 4)) {
        v_l12 = (float)(*(float*)((char*)a4 + 4) - (float)*(float*)((char*)a8 + 4));
        v_l8 = (float)((float)((float)v_l12 * v_l12) + v_l8);
    } else {
        if (*(float*)((char*)a4 + 4) > (float)*(float*)((char*)a12 + 4)) {
            v_l12 = (float)(*(float*)((char*)a4 + 4) - (float)*(float*)((char*)a12 + 4));
            v_l8 = (float)((float)((float)v_l12 * v_l12) + v_l8);
        }
    }
    if (*(float*)((char*)a8 + 8) > (float)*(float*)((char*)a4 + 8)) {
        v_l12 = (float)(*(float*)((char*)a4 + 8) - (float)*(float*)((char*)a8 + 8));
        v_l8 = (float)((float)((float)v_l12 * v_l12) + v_l8);
    } else {
        if (*(float*)((char*)a4 + 8) > (float)*(float*)((char*)a12 + 8)) {
            v_l12 = (float)(*(float*)((char*)a4 + 8) - (float)*(float*)((char*)a12 + 8));
            v_l8 = (float)((float)((float)v_l12 * v_l12) + v_l8);
        }
    }
    return (float)v_l8;
}
