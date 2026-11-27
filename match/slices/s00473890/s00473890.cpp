// 0x00473890: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00472b80/s00472b80.cpp, src/game/SPGonzago/SPPlanetModel.cpp.

extern "C" int __cdecl FUN_0042dee0(...);
extern "C" int __cdecl FUN_004b6bf0(...);
extern "C" void __cdecl FUN_00f47380(...);
#pragma pack(push, 1)
struct Fr0_00473890 {
    int v_l64;
    int v_l60;
    int v_l56;
    int v_l52;
    int v_l48;
    int v_l44;
    int v_l40;
    char dead0;
    char dead1;
    char dead2;
    unsigned char v_l33;
    int dead3[4];
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00473890 { void FUN_00473890(int a4); };
// @ 0x00473890
void D_00473890::FUN_00473890(int a4)
{
    Fr0_00473890 fb;
    if ((unsigned int)a4 > (unsigned int)(int)((int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 12)) {
        fb.v_l12 = (int)(int)(a4 != 0 ? (int)(int)FUN_0042dee0((unsigned int)((int)this + 12), (unsigned int)(a4 * 12), (unsigned int)4, (unsigned int)0) : 0);
        fb.v_l52 = (int)(int)*(int*)((char*)(int)this + 4);
        fb.v_l48 = (int)(int)*(int*)(char*)(int)this;
        fb.v_l16 = (int)(int)FUN_004b6bf0((unsigned int)fb.v_l48, (unsigned int)fb.v_l52, (unsigned int)fb.v_l12);
        fb.v_l33 = (unsigned char)0;
        fb.v_l44 = fb.v_l12;
        fb.v_l40 = fb.v_l48;
        for (; fb.v_l40 != fb.v_l52; fb.v_l40 = fb.v_l40 + 12, fb.v_l44 = fb.v_l44 + 12) {
        }
        fb.v_l64 = (int)(int)((int)(int)((int)*(int*)((char*)(int)this + 8) - (int)*(int*)(char*)(int)this) / 12);
        fb.v_l60 = (int)(int)*(int*)(char*)(int)this;
        if (fb.v_l60 != 0) {
            if ((int)*(int*)((char*)fb.v_l60 - 4) != 0) {
                fb.v_l56 = fb.v_l60;
                FUN_00f47380((unsigned int)fb.v_l56);
            }
        }
        fb.v_l8 = (int)(int)((int)((int)*(int*)((char*)(int)this + 4) - (int)*(int*)(char*)(int)this) / 12);
        *(int*)(char*)(int)this = fb.v_l12;
        *(int*)((char*)(int)this + 4) = fb.v_l8 * 12 + fb.v_l12;
        *(int*)((char*)(int)this + 8) = (int)(int)(a4 * 12 + (int)*(int*)(char*)(int)this);
    }
    return;
}
