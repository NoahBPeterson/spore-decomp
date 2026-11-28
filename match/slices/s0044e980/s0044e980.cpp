// 0x0044e980: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPEditorManipulationUtilities.cpp, src/game/SPBake/_at_00480000.cpp, src/game/SPBake/SPEditorBlock.cpp, match/slices/s0044e460/s0044e460.cpp, match/slices/s005ab7a0/s005ab7a0.cpp, match/slices/s00488600/s00488600.cpp.

struct C_0044f220 { int FUN_0044f220(); };
struct C_0044f240 { int FUN_0044f240(); };


struct D_0044e980 { void FUN_0044e980(int a4); };
// @ 0x0044e980
// @ 0x0044e980
void D_0044e980::FUN_0044e980(int a4)
{
    int v_l24;
    int v_l20_q;
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l28;
    int v_l32;
    v_l8 = (int)(int)*(int*)((char*)(int)this + 448);
    if (a4 == -2) {
        *(int*)((char*)(int)this + 448) = ((C_0044f240*)(int)this)->FUN_0044f240();
        v_l16_i = (int)(int)*(int*)((char*)(int)this + 828);
        if (v_l16_i != 0) {
            v_l20_q = (int)(int)*(int*)((char*)(int)this + 828);
            v_l12_40 = ((C_0044f220*)v_l20_q)->FUN_0044f220();
            if (v_l12_40 != 0) {
                if (v_l12_40 != -2) {
                    if (v_l12_40 != (int)*(int*)((char*)(int)this + 448)) {
                        *(int*)((char*)(int)this + 452) = -1;
                        *(int*)((char*)(int)this + 448) = v_l12_40;
                    }
                }
            }
        }
    } else {
        *(int*)((char*)(int)this + 448) = a4;
    }
    v_l24 = (int)(int)*(int*)((char*)(int)this + 992);
    if (v_l24 != 0) {
        if ((int)*(int*)((char*)(int)this + 448) == 0) {
            v_l28 = (int)(int)*(int*)((char*)(int)this + 992);
            *(int*)((char*)v_l28 + 448) = 0;
        } else {
            v_l32 = (int)(int)*(int*)((char*)(int)this + 992);
            *(int*)((char*)v_l32 + 448) = (int)(int)-(int)*(int*)((char*)(int)this + 448);
        }
    }
    return;
}
