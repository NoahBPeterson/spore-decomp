// 0x00440ff0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00440110/s00440110.cpp, src/game/SPBake/SPEditorBlock.cpp.

#pragma pack(push, 1)
struct Fr0_00440ff0 {
    int v_l20;
    int v_l16;
    int v_l12;
    int v_l8;
};
#pragma pack(pop)


struct D_00440ff0 { int FUN_00440ff0(int a4); };
// @ 0x00440ff0
int D_00440ff0::FUN_00440ff0(int a4)
{
    Fr0_00440ff0 fb;
    *(int*)(char*)(int)this = (int)(int)*(int*)(char*)a4;
    fb.v_l12 = a4 + 4;
    fb.v_l8 = (int)this + 4;
    *(float*)(char*)fb.v_l8 = *(float*)(char*)fb.v_l12;
    *(float*)((char*)fb.v_l8 + 4) = *(float*)((char*)fb.v_l12 + 4);
    *(float*)((char*)fb.v_l8 + 8) = *(float*)((char*)fb.v_l12 + 8);
    fb.v_l20 = a4 + 16;
    fb.v_l16 = (int)this + 16;
    *(float*)(char*)fb.v_l16 = *(float*)(char*)fb.v_l20;
    *(float*)((char*)fb.v_l16 + 4) = *(float*)((char*)fb.v_l20 + 4);
    *(float*)((char*)fb.v_l16 + 8) = *(float*)((char*)fb.v_l20 + 8);
    return (int)this;
}
