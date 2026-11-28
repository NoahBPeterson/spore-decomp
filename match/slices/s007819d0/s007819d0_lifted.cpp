// 0x007819d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsShadowWorld.cpp, match/slices/s007819d0/s007819d0.cpp.

extern "C" int __cdecl FUN_00777ae0(...);
struct C_0077f980 { int FUN_0077f980(); };
struct C_00780810 { int FUN_00780810(); };

// @ 0x007819d0
extern "C" void __fastcall FUN_007819d0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1010;
    int t1014;
    t1002 = (int)((int)(self));
    if ((int)*(int*)((char*)(t1002) + 8) == (int)0) {
        t1003 = (int)(*(int*)((char*)(t1002) + 16));
        if (t1003 != (int)0) {
            if ((int)(a4) == t1003) {
                if ((unsigned char)*(unsigned char*)((char*)(t1002) + 5) != (unsigned char)0) {
                    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 4) != (unsigned char)0) {
                        if ((unsigned char)*(unsigned char*)((char*)(t1002) + 6) != (unsigned char)0) {
                            FUN_00777ae0((unsigned int)((int)522), (unsigned int)((int)0), (unsigned int)((int)0));
                            FUN_00777ae0((unsigned int)((int)523), (unsigned int)((int)0), (unsigned int)((int)0));
                            t1010 = (int)(t1002 + (int)60);
                            FUN_00777ae0((unsigned int)((int)547), (unsigned int)(t1010), (unsigned int)((int)1));
                            t1014 = (int)(t1002 + (int)(-8));
                            if ((unsigned char)*(unsigned char*)((char*)(t1002) + 444) != (unsigned char)0) {
                                ((C_00780810*)(t1014))->FUN_00780810();
                                return;
                            }
                            ((C_0077f980*)(t1014))->FUN_0077f980();
                            return;
                        }
                    }
                }
            }
        }
        FUN_00777ae0((unsigned int)((int)547), (unsigned int)((int)0), (unsigned int)((int)0));
    }
    return;
}
