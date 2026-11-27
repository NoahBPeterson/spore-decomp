// 0x004fd670: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s004fcae0/s004fcae0.cpp.



struct D_004fd670 { int FUN_004fd670(int a4); };
// @ 0x004fd670
int D_004fd670::FUN_004fd670(int a4)
{
    *(float*)(char*)(int)this = *(float*)(char*)a4;
    *(float*)((char*)(int)this + 4) = *(float*)((char*)a4 + 4);
    *(float*)((char*)(int)this + 8) = *(float*)((char*)a4 + 8);
    *(float*)((char*)(int)this + 12) = *(float*)((char*)a4 + 12);
    *(float*)((char*)(int)this + 16) = *(float*)((char*)a4 + 16);
    *(int*)((char*)(int)this + 20) = (int)(int)*(int*)((char*)a4 + 20);
    return (int)this;
}
