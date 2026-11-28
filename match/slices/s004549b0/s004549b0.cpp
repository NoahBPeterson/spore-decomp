// 0x004549b0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode with local names and order from the /Od frame inverse (odframe.py); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00454330/s00454330.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};


// @ 0x004549b0
extern "C" int __cdecl FUN_004549b0(int a4, int a8, int a12)
{
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l28;
    int v_l36_i;
    int v_l32;
    v_l16_i = a4;
    L4549bc:;
    if (v_l16_i != a8) {
        v_l12_40 = (int)(int)*(int*)(char*)v_l16_i;
        if (v_l12_40 != (int)*(int*)(char*)a12) {
            v_l16_i = v_l16_i + 4;
            goto L4549bc;
        }
    }
    *(int*)&a4 = v_l16_i;
    if (a4 != a8) {
        v_l8 = a4;
        v_l8 = v_l8 + 4;
        v_l36_i = a4;
        v_l32 = v_l8;
        for (; v_l32 != a8; v_l32 = v_l32 + 4) {
            v_l20_q = (int)(int)*(int*)(char*)v_l32;
            if (v_l20_q != (int)*(int*)(char*)a12) {
                v_l28 = (int)(int)*(int*)(char*)v_l32;
                if (v_l28 != (int)*(int*)(char*)v_l36_i) {
                    v_l24 = (int)(int)*(int*)(char*)v_l36_i;
                    if (v_l28 != 0) {
                        ((il2c_vc0*)v_l28)->s1();
                    }
                    *(int*)(char*)v_l36_i = v_l28;
                    if (v_l24 != 0) {
                        ((il2c_vc1*)v_l24)->s2();
                    }
                }
                v_l36_i = v_l36_i + 4;
            }
        }
        return v_l36_i;
    }
        return a4;
}
