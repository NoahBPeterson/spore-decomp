// 0x0055eae0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0055dce0/s0055dce0.cpp, src/game/SPEditors/SPObjectTemplateDB.cpp.

extern "C" unsigned char g_013eb394[];
extern "C" unsigned char g_013f4af0[];
extern "C" void __cdecl FUN_0050f0d0(...);
struct C_00568740 { void FUN_00568740(unsigned int, unsigned int, unsigned int); };
#pragma pack(push, 1)
struct Fr0_0055eae0 {
    int v_l24;
    int v_l20;
    int v_l16;
    char dead0;
    char dead1;
    char dead2;
    unsigned char v_l9;
    int dead3[1];
};
#pragma pack(pop)


struct D_0055eae0 { int FUN_0055eae0(int a4, int a8); };
// @ 0x0055eae0
int D_0055eae0::FUN_0055eae0(int a4, int a8)
{
    Fr0_0055eae0 fb;
    *(int*)(char*)(int)this = (int)g_013eb394;
    *(int*)(char*)(int)this = (int)g_013f4af0;
    fb.v_l16 = (int)this + 4;
    *(int*)(char*)fb.v_l16 = 0;
    *(int*)((char*)fb.v_l16 + 4) = 0;
    *(int*)((char*)fb.v_l16 + 8) = 0;
    ((C_00568740*)fb.v_l16)->FUN_00568740((unsigned int)a4, (unsigned int)(a4 + (a8 << 2)), (unsigned int)(int)fb.v_l9);
    fb.v_l20 = (int)(int)*(int*)((char*)(int)this + 8);
    fb.v_l24 = (int)(int)*(int*)((char*)(int)this + 4);
    FUN_0050f0d0((unsigned int)fb.v_l24, (unsigned int)fb.v_l20);
    return (int)this;
}
