// 0x00828450: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUIPropertyLayout.cpp, match/slices/s00827bf0/s00827bf0.cpp.

struct il2c_vc0 {
    virtual void s0();
};

struct C_00542b80 { void FUN_00542b80(unsigned int); };

// @ 0x00828450
extern "C" int __fastcall FUN_00828450(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1005;
    int t1006;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1019;
    int t1021;
    t1002 = (int)((int)(a4));
    t1003 = (int)(*(int*)((char*)(t1002)));
    t1005 = (int)((int)(self));
    *(int*)((char*)(t1005)) = (int)(t1003);
    t1006 = (int)(*(int*)((char*)(t1002) + 4));
    *(int*)((char*)(t1005) + 4) = (int)(t1006);
    if (t1006 != (int)0) {
        ((il2c_vc0*)(t1006))->s0();
    }
    t1012 = (int)(t1005 + (int)8);
    t1013 = (int)((int)0);
    *(unsigned short*)((char*)(t1012) + 16) = (unsigned short)((unsigned short)(t1013));
    t1014 = (int)(t1002 + (int)8);
    t1015 = (int)((int)0);
    *(unsigned short*)((char*)(t1012) + 18) = (unsigned short)((unsigned short)(t1015));
    ((C_00542b80*)(t1012))->FUN_00542b80((unsigned int)(t1014));
    t1019 = (int)(*(int*)((char*)(t1002) + 28));
    *(int*)((char*)(t1005) + 28) = (int)(t1019);
    t1021 = (int)(t1005);
    return (int)(t1021);
}
