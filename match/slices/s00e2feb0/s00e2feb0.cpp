// 0x00e2feb0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00e20000.cpp, match/slices/s00e2f6e0/s00e2f6e0.cpp.

extern "C" void __cdecl FUN_00f62def(...);
struct C_00594410 { void FUN_00594410(unsigned int); };
struct C_00e2fcb0 { int FUN_00e2fcb0(unsigned int); };

// @ 0x00e2feb0
extern "C" bool __fastcall FUN_00e2feb0(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1004;
    int t1007;
    int v_l8[2];
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    bool t1029;
    bool t1033;
    bool t1035;
    t1002 = (int)((int)(self));
    if ((int)(a4) == (int)&FUN_00f62def) {
        t1003 = (int)((int)(a8));
        if ((int)*(int*)((char*)(t1003) + 16) == (int)109705754) {
            t1004 = (int)(*(int*)((char*)(t1003) + 24));
            t1007 = (int)((int)&v_l8);
            t1008 = (int)(t1002 + (int)28);
            t1009 = (int)(t1008);
            *(int*)&(a4) = (int)(t1004);
            ((C_00594410*)(t1009))->FUN_00594410((unsigned int)(t1007));
            t1013 = (int)(*(int*)((char*)(t1008) + 8));
            t1014 = (int)(*(int*)((char*)(t1008) + 4));
            t1015 = (int)(*(int*)((char*)(t1014) + (t1013)*4));
            t1016 = (int)((*(int*)&v_l8[0]));
            if (t1016 != t1015) {
                t1018 = (int)((*(int*)&v_l8[1]));
                do {
                    t1019 = (int)((int)(a4));
                    if ((int)*(int*)((char*)(t1016)) == t1019) {
                        t1020 = (int)(t1016 + (int)4);
                        t1021 = (int)(t1002 + (int)(-8));
                        t1014 = (int)((C_00e2fcb0*)(t1021))->FUN_00e2fcb0((unsigned int)(t1020));
                    }
                    t1016 = (int)(*(int*)((char*)(t1016) + 20));
                    if (t1016 == (int)0) {
                        goto Le2ff20;
                        Le2ff20:;
                        t1016 = (int)(*(int*)((char*)(t1018) + 4));
                        t1018 = (int)(t1018 + (int)4);
                        if (t1016 == (int)0) goto Le2ff20;
                    }
                } while (t1016 != t1015);
                t1029 = true;
                return (bool)(t1029);
            }
            t1033 = true;
            return (bool)(t1033);
        }
    }
    t1035 = true;
    return (bool)(t1035);
}
