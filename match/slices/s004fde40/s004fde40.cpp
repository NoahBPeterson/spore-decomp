// 0x004fde40: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004fd9a0/s004fd9a0.cpp.

struct C_00926650 { int FUN_00926650(unsigned int, unsigned int); };


struct D_004fde40 { int FUN_004fde40(); };
// @ 0x004fde40
int D_004fde40::FUN_004fde40()
{
    int v_l8;
    L4fde49:;
    if ((int)*(int*)((char*)(int)this + 16) != 0) {
        v_l8 = (int)(int)*(int*)((char*)(int)this + 16);
        *(int*)((char*)(int)this + 16) = (int)(int)*(int*)(char*)v_l8;
        return v_l8;
    }
        if ((int)(unsigned char)((C_00926650*)(int)this)->FUN_00926650((unsigned int)0, (unsigned int)0) != 0) {
            goto L4fde49;
        }
        return 0;
}
