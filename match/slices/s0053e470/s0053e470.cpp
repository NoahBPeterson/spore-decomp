// 0x0053e470: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0053e120/s0053e120.cpp.

extern "C" unsigned char g_013ef094[];
extern "C" unsigned char g_013f3464[];
struct C_00453540 { void FUN_00453540(); };
struct C_0045daf0 { int FUN_0045daf0(); };
struct C_004fd940 { void FUN_004fd940(); };
struct C_00540520 { void FUN_00540520(); };
#pragma pack(push, 1)
struct Fr0_0053e470 {
    int dead0[3];
    int v_l88;
    int v_l84;
    int dead1[3];
    int v_l68;
    int v_l64;
    int dead2[3];
    int v_l48;
    int dead3[2];
    int v_l36;
    int dead4[3];
    int v_l20;
    int dead5[3];
};
struct Fr1_0053e470 {
    int v_l104;
};
#pragma pack(pop)


struct D_0053e470 { void FUN_0053e470(); };
// @ 0x0053e470
void D_0053e470::FUN_0053e470()
{
    Fr0_0053e470 fb;
    Fr1_0053e470 fa;
    *(int*)(char*)(int)this = (int)g_013f3464;
    fb.v_l20 = (int)this + 148;
    if ((int)*(int*)(char*)fb.v_l20 != 0) {
        ((C_00453540*)(int)*(int*)(char*)fb.v_l20)->FUN_00453540();
    }
    fb.v_l36 = (int)this + 144;
    if ((int)*(int*)(char*)fb.v_l36 != 0) {
        ((C_00453540*)(int)*(int*)(char*)fb.v_l36)->FUN_00453540();
    }
    ((C_00540520*)((int)this + 124))->FUN_00540520();
    ((C_00540520*)((int)this + 104))->FUN_00540520();
    fb.v_l64 = (int)this + 80;
    fb.v_l48 = (int)(int)*(int*)(char*)fb.v_l64;
    for (; (unsigned int)fb.v_l48 < (unsigned int)*(int*)((char*)fb.v_l64 + 4); fb.v_l48 = fb.v_l48 + 24) {
    }
    ((C_004fd940*)fb.v_l64)->FUN_004fd940();
    fb.v_l84 = (int)this + 60;
    fb.v_l68 = (int)(int)*(int*)(char*)fb.v_l84;
    for (; (unsigned int)fb.v_l68 < (unsigned int)*(int*)((char*)fb.v_l84 + 4); fb.v_l68 = fb.v_l68 + 8) {
    }
    ((C_0045daf0*)fb.v_l84)->FUN_0045daf0();
    fa.v_l104 = (int)this + 32;
    fb.v_l88 = (int)(int)*(int*)(char*)fa.v_l104;
    for (; (unsigned int)fb.v_l88 < (unsigned int)*(int*)((char*)fa.v_l104 + 4); fb.v_l88 = fb.v_l88 + 8) {
    }
    ((C_0045daf0*)fa.v_l104)->FUN_0045daf0();
    *(int*)(char*)(int)this = (int)g_013ef094;
    return;
}
