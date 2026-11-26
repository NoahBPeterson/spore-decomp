// 0x00addd90: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00addb50/s00addb50.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
};

struct C_00961d60 { int FUN_00961d60(unsigned int, unsigned int); };

// @ 0x00addd90
extern "C" void __fastcall FUN_00addd90(char* self, int edx_unused)
{
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1018;
    int t1019;
    int t1020;
    t1005 = (int)(*(int*)((char*)((int)(self)) + 96));
    t1006 = (int)(*(int*)((char*)(t1005)));
    if (t1006 == (int)0) {
        t1005 = (int)(t1005 + (int)4);
        if ((int)*(int*)((char*)(t1005)) == t1006) {
            do {
                t1005 = (int)(t1005 + (int)4);
            } while ((int)*(int*)((char*)(t1005)) == (int)0);
        }
        t1006 = (int)(*(int*)((char*)(t1005)));
    }
    t1007 = (int)(*(int*)((char*)((int)(self)) + 100));
    t1008 = (int)((int)(self) + (int)92);
    t1009 = (int)(*(int*)((char*)(t1008) + 4));
    t1010 = (int)(*(int*)((char*)(t1009) + (t1007)*4));
    if (t1006 != t1010) {
        t1011 = (int)(t1005);
        do {
            t1012 = (int)(*(int*)((char*)(t1006) + 4));
            ((il2c_vc0*)(t1012))->s4();
            t1006 = (int)(*(int*)((char*)(t1006) + 8));
            if (t1006 == (int)0) {
                do {
                    t1006 = (int)(*(int*)((char*)(t1011) + 4));
                    t1011 = (int)(t1011 + (int)4);
                } while (t1006 == (int)0);
            }
        } while (t1006 != t1010);
    }
    t1018 = (int)(*(int*)((char*)(t1008) + 8));
    t1019 = (int)(*(int*)((char*)(t1008) + 4));
    t1020 = (int)(t1008);
    ((C_00961d60*)(t1020))->FUN_00961d60((unsigned int)(t1019), (unsigned int)(t1018));
    *(int*)((char*)(t1008) + 12) = (int)((int)0);
    return;
}
