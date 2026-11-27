// 0x004b0340: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004af210/s004af210.cpp, src/game/SPBake/SPEditorResourceFactory.cpp.

#include <string.h>
#pragma pack(push, 1)
struct Fr0_004b0340 {
    int v_l28;
    int v_l24;
    int v_l20;
    int v_l16;
    char dead0;
    unsigned char v_l11;
    unsigned char v_l10;
    unsigned char v_l9;
    int v_l8;
};
#pragma pack(pop)
struct S118 { int m0; int m1; int m2; int m3; int m4; int m5; int m6; int m7; int m8; int m9; int m10; int m11; int m12; int m13; int m14; int m15; int m16; int m17; int m18; int m19; int m20; int m21; int m22; int m23; int m24; int m25; int m26; int m27; int m28; int m29; int m30; int m31; int m32; int m33; int m34; int m35; int m36; int m37; int m38; int m39; int m40; int m41; int m42; int m43; int m44; int m45; int m46; int m47; int m48; int m49; int m50; int m51; int m52; int m53; int m54; int m55; int m56; int m57; int m58; int m59; int m60; int m61; int m62; int m63; int m64; int m65; int m66; int m67; int m68; int m69; int m70; int m71; int m72; int m73; int m74; int m75; int m76; int m77; int m78; int m79; int m80; int m81; int m82; int m83; int m84; int m85; int m86; int m87; int m88; int m89; int m90; int m91; int m92; int m93; int m94; int m95; int m96; int m97; int m98; int m99; int m100; int m101; int m102; int m103; int m104; int m105; int m106; int m107; int m108; int m109; int m110; int m111; int m112; int m113; int m114; int m115; int m116; int m117; };


struct D_004b0340 { int FUN_004b0340(int a4, int a8); };
// @ 0x004b0340
int D_004b0340::FUN_004b0340(int a4, int a8)
{
    Fr0_004b0340 fb;
    fb.v_l24 = (int)(int)*(int*)((char*)(int)this + 4);
    fb.v_l10 = (unsigned char)0;
    fb.v_l9 = (unsigned char)0;
    fb.v_l11 = (unsigned char)0;
    fb.v_l20 = a4;
    fb.v_l16 = a8;
    for (; fb.v_l16 != fb.v_l24; fb.v_l20 = fb.v_l20 + 472, fb.v_l16 = fb.v_l16 + 472) {
        *(S118*)fb.v_l20 = *(S118*)fb.v_l16;
    }
    fb.v_l8 = fb.v_l20;
    fb.v_l28 = fb.v_l8;
    for (; (unsigned int)fb.v_l28 < (unsigned int)*(int*)((char*)(int)this + 4); fb.v_l28 = fb.v_l28 + 472) {
    }
    *(int*)((char*)(int)this + 4) = (int)(int)((int)*(int*)((char*)(int)this + 4) - (a8 - a4) / 472 * 472);
    return a4;
}
