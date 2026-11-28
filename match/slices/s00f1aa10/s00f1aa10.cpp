// 0x00f1aa10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00f10000.cpp, match/slices/s00f19e70/s00f19e70.cpp, match/slices/s00f19e70/s00f19e70.cpp.bak.

#include <math.h>
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual int s26();
};

#include "sse_helpers.h"  // MATCH_SSE_HELPERS_H

extern "C" unsigned char g_015ad924[];
extern "C" unsigned char g_015ad928[];
extern "C" unsigned char g_015ad92c[];
extern "C" unsigned char g_015ad930[];
extern "C" unsigned char g_015ad934[];
extern "C" unsigned char g_015ad938[];

// @ 0x00f1aa10
extern "C" float __stdcall FUN_00f1aa10(int a4, float a8)
{
    int t1000;
    float t1001;
    float t1002;
    float t1003;
    int t1006;
    float t4;
    float t5;
    float t6;
    double t12;
    float v_l16;
    float t1009;
    float t1011;
    t1000 = (int)((int)(*(int*)&a8));
    if (t1000 != (int)0) {
        if ((unsigned char)(a4) != (unsigned char)0) {
            t1001 = (float)((float)(*(float*)g_015ad92c));
            *(float*)&(a8) = (float)(t1001);
            t1002 = (float)((float)(*(float*)g_015ad930));
        } else {
            t1003 = (float)((float)(*(float*)g_015ad934));
            *(float*)&(a8) = (float)(t1003);
            t1002 = (float)((float)(*(float*)g_015ad938));
        }
        *(float*)&(a4) = (float)(t1002);
        t1006 = (int)((il2c_vc0*)(t1000))->s26();
        t4 = (float)((float)*(float*)((char*)(t1006) + 12) - (float)*(float*)((char*)(t1006)));
        t5 = (float)((float)*(float*)((char*)(t1006) + 16) - (float)*(float*)((char*)(t1006) + 4));
        t6 = (float)((float)*(float*)((char*)(t1006) + 20) - (float)*(float*)((char*)(t1006) + 8));
        t12 = (double)sqrt((double)((((t4 * t4) + (t5 * t5)) + (t6 * t6))));
        v_l16 = (float)(t12);
        t1009 = (float)(v_l16);
        t1011 = (float)SseClamp((float)(t1009), (float)((float)(*(float*)g_015ad924)), (float)((float)(*(float*)g_015ad928)));
        v_l16 = (float)(t1011);
        return (float)(((float)(a8) + (((*(float*)&a4) - (float)(a8)) * ((v_l16 - (float)(*(float*)g_015ad924)) / ((float)(*(float*)g_015ad928) - (float)(*(float*)g_015ad924))))));
    }
    return (float)((float)0);
}
