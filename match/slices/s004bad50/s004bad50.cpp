// 0x004bad50: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004ba150/s004ba150.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};

struct C_00404f90 { void FUN_00404f90(); };
struct C_0040f360 { void FUN_0040f360(); };
struct C_0041e640 { void FUN_0041e640(); };
struct C_0041eb80 { void FUN_0041eb80(); };
#pragma pack(push, 1)
struct Fr0_004bad50 {
    int dead0[2];
    int v_l60;
    int dead1[13];
};
struct Fr1_004bad50 {
    int v_l72;
};
#pragma pack(pop)


struct D_004bad50 { void FUN_004bad50(); };
// @ 0x004bad50
void D_004bad50::FUN_004bad50()
{
    Fr0_004bad50 fb;
    Fr1_004bad50 fa;
    ((C_0041eb80*)((int)this + 32))->FUN_0041eb80();
    ((C_0041e640*)((int)this + 12))->FUN_0041e640();
    fb.v_l60 = (int)this + 8;
    if ((int)*(int*)(char*)fb.v_l60 != 0) {
        ((C_00404f90*)(int)*(int*)(char*)fb.v_l60)->FUN_00404f90();
    }
    fa.v_l72 = (int)this + 4;
    if ((int)*(int*)(char*)fa.v_l72 != 0) {
        ((C_0040f360*)(int)*(int*)(char*)fa.v_l72)->FUN_0040f360();
    }
    if ((int)*(int*)(char*)(int)this != 0) {
        ((il2c_vc0*)(int)*(int*)(char*)(int)this)->s1();
    }
    return;
}
