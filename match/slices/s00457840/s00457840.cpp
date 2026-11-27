// 0x00457840: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004575d0/s004575d0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};

extern "C" unsigned char g_013eb394[];
extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ec458[];
extern "C" unsigned char g_013ec564[];
extern "C" unsigned char g_013ec574[];
extern "C" unsigned char g_013ec584[];
struct C_00425990 { void FUN_00425990(); };
struct C_00453540 { void FUN_00453540(); };
struct C_004b5440 { void FUN_004b5440(); };
#pragma pack(push, 1)
struct Fr0_00457840 {
    int v_l60;
    int v_l56;
    int dead0[3];
    int v_l40;
    int v_l36;
    int dead1[2];
    int v_l24;
    int dead2[3];
    int v_l8;
};
#pragma pack(pop)


struct D_00457840 { void FUN_00457840(); };
// @ 0x00457840
void D_00457840::FUN_00457840()
{
    Fr0_00457840 fb;
    *(int*)(char*)(int)this = (int)g_013ec584;
    *(int*)((char*)(int)this + 4) = (int)g_013ec574;
    *(int*)((char*)(int)this + 8) = (int)g_013ec564;
    fb.v_l24 = (int)this + 88;
    fb.v_l8 = (int)(int)*(int*)(char*)fb.v_l24;
    for (; (unsigned int)fb.v_l8 < (unsigned int)*(int*)((char*)fb.v_l24 + 4); fb.v_l8 = fb.v_l8 + 4) {
    }
    ((C_00425990*)fb.v_l24)->FUN_00425990();
    ((C_004b5440*)((int)this + 68))->FUN_004b5440();
    fb.v_l36 = (int)this + 64;
    if ((int)*(int*)(char*)fb.v_l36 != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)fb.v_l36)->s1();
    }
    fb.v_l40 = (int)this + 60;
    if ((int)*(int*)(char*)fb.v_l40 != 0) {
        ((il2c_vc1*)(int)(int)*(int*)(char*)fb.v_l40)->s1();
    }
    fb.v_l56 = (int)this + 56;
    if ((int)*(int*)(char*)fb.v_l56 != 0) {
        ((C_00453540*)(int)*(int*)(char*)fb.v_l56)->FUN_00453540();
    }
    fb.v_l60 = (int)this + 52;
    if ((int)*(int*)(char*)fb.v_l60 != 0) {
        ((il2c_vc2*)(int)(int)*(int*)(char*)fb.v_l60)->s2();
    }
    *(int*)((char*)(int)this + 8) = (int)g_013ec458;
    *(int*)((char*)(int)this + 4) = (int)g_013eb938;
    *(int*)(char*)(int)this = (int)g_013eb394;
    return;
}
