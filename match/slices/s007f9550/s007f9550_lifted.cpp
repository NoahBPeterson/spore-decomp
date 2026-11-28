// 0x007f9550: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIBehavior.cpp, match/slices/s007f9550/s007f9550_od.cpp.

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
};

extern "C" unsigned char g_014154a4[];
extern "C" unsigned char g_01485378[];
extern "C" unsigned char g_01485720[];


struct D_007f9550 { bool FUN_007f9550(); };
// @ 0x007f9550
bool D_007f9550::FUN_007f9550()
{
    *(unsigned char*)((char*)(int)this + 58) = (unsigned char)0;
    ((il2c_vc0*)(int)this)->s9();
    if ((float)*(float*)g_01485378 > (float)*(float*)((char*)(int)this + 32)) {
        *(float*)((char*)(int)this + 32) = (float)*(float*)g_01485378;
    }
    if ((float)*(float*)g_01485378 > (float)*(float*)((char*)(int)this + 36)) {
        *(float*)((char*)(int)this + 36) = (float)*(float*)g_01485378;
    }
    if (!!(*(float*)((char*)(int)this + 32) >= (float)*(float*)g_01485378) || !!(*(float*)((char*)(int)this + 36) >= (float)*(float*)g_01485378)) {
        if (*(float*)((char*)(int)this + 32) > (float)*(float*)g_01485720) {
            *(float*)((char*)(int)this + 32) = (float)*(float*)g_01485720;
        }
        if ((float)(*(float*)((char*)(int)this + 32) + (float)*(float*)((char*)(int)this + 32)) > (float)*(float*)g_01485720) {
            *(float*)((char*)(int)this + 36) = (float)((float)*(float*)g_01485720 - (float)*(float*)((char*)(int)this + 32));
        }
    } else {
        *(float*)((char*)(int)this + 36) = (float)*(float*)g_01485378;
        *(float*)((char*)(int)this + 32) = (float)*(float*)g_01485378;
    }
    if ((float)*(float*)g_01485378 > (float)*(float*)((char*)(int)this + 24)) {
        *(float*)((char*)(int)this + 24) = (float)*(float*)g_01485378;
    }
    if ((float)*(float*)g_01485378 > (float)*(float*)((char*)(int)this + 28)) {
        *(float*)((char*)(int)this + 28) = (float)*(float*)g_01485378;
    }
    if (!!(*(float*)((char*)(int)this + 24) >= (float)*(float*)g_01485378) || !!(*(float*)((char*)(int)this + 28) >= (float)*(float*)g_01485378)) {
        if (*(float*)((char*)(int)this + 24) > (float)*(float*)g_01485720) {
            *(float*)((char*)(int)this + 24) = (float)*(float*)g_01485720;
        }
        if ((float)(*(float*)((char*)(int)this + 24) + (float)*(float*)((char*)(int)this + 24)) > (float)*(float*)g_01485720) {
            *(float*)((char*)(int)this + 28) = (float)((float)*(float*)g_01485720 - (float)*(float*)((char*)(int)this + 24));
        }
    } else {
        *(float*)((char*)(int)this + 28) = (float)*(float*)g_01485378;
        *(float*)((char*)(int)this + 24) = (float)*(float*)g_01485378;
    }
    if ((float)*(float*)g_01485378 > (float)*(float*)((char*)(int)this + 12)) {
        *(float*)((char*)(int)this + 12) = (float)*(float*)g_014154a4;
    }
    *(float*)((char*)(int)this + 64) = (float)(*(float*)((char*)(int)this + 12) * (float)*(float*)((char*)(int)this + 32));
    *(float*)((char*)(int)this + 68) = (float)((float)((float)*(float*)g_01485720 - (float)*(float*)((char*)(int)this + 36)) * (float)*(float*)((char*)(int)this + 12));
    if ((float)*(float*)g_01485378 > (float)*(float*)((char*)(int)this + 16)) {
        *(float*)((char*)(int)this + 16) = (float)*(float*)g_01485378;
    }
    return (bool)(unsigned char)1;
}
