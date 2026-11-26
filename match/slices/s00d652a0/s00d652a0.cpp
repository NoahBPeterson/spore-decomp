// 0x00d652a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00d65250/s00d65250.cpp, src/game/SPGonzago/_at_00d60000.cpp.

struct il2c_vc0 {
    virtual void s0();
};

struct C_00926650 { int FUN_00926650(unsigned int, unsigned int); };

// @ 0x00d652a0
extern "C" int __fastcall FUN_00d652a0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1016;
    int t1018;
    int t1019;
    t1002 = (int)((int)(self) + (int)8);
    do {
        if ((int)*(int*)((char*)(t1002) + 16) != (int)0) goto Ld652da;
        t1003 = (int)(t1002);
        t1006 = (int)((C_00926650*)(t1003))->FUN_00926650((unsigned int)((int)0), (unsigned int)((int)0));
    } while ((unsigned char)(t1006) != (unsigned char)0);
    t1007 = (int)((int)0);
    Ld652bb:;
    t1008 = (int)(t1007 + (int)8);
    if (t1008 != (int)0) {
        t1009 = (int)((int)(a4));
        t1010 = (int)(*(int*)((char*)(t1009)));
        *(int*)((char*)(t1008)) = (int)(t1010);
        if (t1010 != (int)0) {
            ((il2c_vc0*)(t1010))->s0();
        }
    }
    t1016 = (int)(t1007);
    return (int)(t1016);
    Ld652da:;
    t1018 = (int)(*(int*)((char*)(t1002) + 16));
    t1019 = (int)(*(int*)((char*)(t1018)));
    *(int*)((char*)(t1002) + 16) = (int)(t1019);
    t1007 = (int)(t1018);
    goto Ld652bb;
}
