// 0x00bdf880: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCity.cpp, match/slices/s00bdee20/s00bdee20.cpp.

extern "C" int __cdecl FUN_00921580(...);
struct C_00ac4280 { void FUN_00ac4280(unsigned int); };
struct C_00b534c0 { void FUN_00b534c0(unsigned int, unsigned int); };
struct C_00d018d0 { int FUN_00d018d0(unsigned int, unsigned int); };

// @ 0x00bdf880
extern "C" void __fastcall FUN_00bdf880(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int t1006;
    int t1007;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t1020;
    int t1021;
    int v_l8[2];
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 1516));
    t1006 = (int)((int)(a4));
    t1007 = (int)(t1006);
    ((C_00ac4280*)(t1007))->FUN_00ac4280((unsigned int)(t1004));
    t1011 = (int)(*(int*)((char*)(t1006) + 4));
    t1012 = (int)(*(int*)((char*)(t1006)));
    t1013 = (int)(t1006);
    t1014 = (int)((C_00d018d0*)(t1013))->FUN_00d018d0((unsigned int)(t1012), (unsigned int)(t1011));
    t1017 = (int)(*(int*)((char*)(t1003) + 1504));
    t1018 = (int)(t1003 + (int)1500);
    if (t1017 != t1018) {
        do {
            t1020 = (int)(*(int*)((char*)(t1017) + 20));
            t1021 = (int)(*(int*)((char*)(t1017) + 16));
            (*(int*)&v_l8[0]) = (int)(t1021);
            (*(int*)&v_l8[1]) = (int)(t1020);
            if (t1020 != (int)0) {
                t1022 = (int)(*(int*)((char*)(t1006) + 4));
                if ((unsigned int)(t1022) < (unsigned int)*(int*)((char*)(t1006) + 8)) {
                    t1023 = (int)(t1022 + (int)8);
                    *(int*)((char*)(t1006) + 4) = (int)(t1023);
                    if (t1022 == (int)0) goto Lbdf8f8;
                    *(int*)((char*)(t1022)) = (int)(t1021);
                    *(int*)((char*)(t1022) + 4) = (int)(t1020);
                    goto Lbdf8f8;
                }
                t1024 = (int)((int)&v_l8);
                t1025 = (int)(t1006);
                ((C_00b534c0*)(t1025))->FUN_00b534c0((unsigned int)(t1022), (unsigned int)(t1024));
            }
            Lbdf8f8:;
            t1014 = (int)FUN_00921580((unsigned int)(t1017));
            t1017 = (int)(t1014);
        } while (t1017 != t1018);
    }
    return;
}
