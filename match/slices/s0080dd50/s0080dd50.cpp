// 0x0080dd50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUILayers.cpp, match/slices/s0080d670/s0080d670.cpp.

extern "C" void __cdecl FUN_0080d6d0(...);
struct C_0067cad0 { void FUN_0067cad0(); };
extern "C" void __cdecl FUN_00807d30(...);

// @ 0x0080dd50
extern "C" int __fastcall FUN_0080dd50(char* self, int edx_unused)
{
    int t1002;
    int t1006;
    int v_l12[3];
    int t1010;
    int t1012;
    t1002 = (int)(*(int*)((char*)((int)(self)) + 12));
    if (t1002 != (int)0) {
        ((C_0067cad0*)((int)(self)))->FUN_0067cad0();
        t1006 = (int)((int)&v_l12);
        (*(int*)&v_l12[1]) = (int)((int)10000);
        (*(int*)&v_l12[2]) = (int)((int)(-10000));
        *(unsigned char*)&v_l12[0] = (unsigned char)((int)0);
        FUN_00807d30((unsigned int)(t1002), (unsigned int)((int)&FUN_0080d6d0), (unsigned int)(t1006));
        t1010 = (int)((*(int*)&v_l12[1]));
        return (int)(t1010);
    }
    t1012 = (int)((int)0);
    return (int)(t1012);
}
