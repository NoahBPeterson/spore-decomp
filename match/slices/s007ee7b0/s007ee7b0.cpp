// 0x007ee7b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPAppVolumeDescription.cpp, match/slices/s007ee060/s007ee060.cpp.

struct C_00838320 { int FUN_00838320(unsigned int); };
extern "C" int __cdecl FUN_00932e80(...);

// @ 0x007ee7b0
extern "C" void __fastcall FUN_007ee7b0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    t1002 = (int)((int)(self));
    t1003 = (int)((int)(a4));
    t1006 = (int)((C_00838320*)(t1003))->FUN_00838320((unsigned int)((int)1));
    t1007 = (int)(*(int*)((char*)(t1006)));
    t1010 = (int)FUN_00932e80((unsigned int)(t1007), (unsigned int)((int)(-2128831035)), (unsigned int)((int)1));
    t1011 = (int)(*(int*)((char*)(t1002) + 12));
    *(int*)((char*)(t1011) + 48) = (int)(t1010);
    *(int*)((char*)(t1011) + 52) = (int)((int)0);
    return;
}
