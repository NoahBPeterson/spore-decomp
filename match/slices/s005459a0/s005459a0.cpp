// 0x005459a0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPFeedXml.cpp, match/slices/s00545220/s00545220.cpp.

struct C_00548a30 { void FUN_00548a30(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00903550(...);


struct D_005459a0 { void FUN_005459a0(); };
// @ 0x005459a0
// @ 0x005459a0
void D_005459a0::FUN_005459a0()
{
    int dead_0_15[10];
    int dead_2_66;
    int dead_1_12[15];
    int v_l48;
    int dead_3_16[15];
    int v_l116;
    int v_l224_64;
    int dead_4[11];
    if ((int)*(int*)((char*)(int)this + 32) != 0 && ((int)*(int*)((char*)(int)this + 36) != 0 && (int)*(int*)((char*)(int)this + 40) != 0)) {
        v_l48 = (int)(int)*(int*)((char*)(int)this + 32);
        ((C_00548a30*)v_l48)->FUN_00548a30((unsigned int)(int)*(int*)(char*)v_l48, (unsigned int)(int)*(int*)((char*)v_l48 + 4));
        v_l116 = (int)(int)*(int*)((char*)(int)this + 36);
        ((C_00548a30*)v_l116)->FUN_00548a30((unsigned int)(int)*(int*)(char*)v_l116, (unsigned int)(int)*(int*)((char*)v_l116 + 4));
        v_l224_64 = (int)(int)*(int*)((char*)(int)this + 40);
        ((C_00548a30*)v_l224_64)->FUN_00548a30((unsigned int)(int)*(int*)(char*)v_l224_64, (unsigned int)(int)*(int*)((char*)v_l224_64 + 4));
        *(int*)((char*)(int)this + 52) = 0;
        *(int*)((char*)(int)this + 56) = 0;
        *(int*)((char*)(int)this + 60) = 0;
        *(unsigned char*)((char*)(int)this + 48) = (unsigned char)1;
    } else {
        FUN_00903550((unsigned int)(int)*(int*)((char*)(int)this + 12), (unsigned int)0);
    }
    return;
}
