// 0x00ccbb60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPTribeDisplayStrategy.cpp, match/slices/s00ccaff0/s00ccaff0.cpp.

struct il2c_vc0 {
    virtual void s0();
};
struct il2c_vc1 {
    virtual void s0();
    virtual int s1();
};
struct il2c_vc2 {
    virtual void s0();
};
struct il2c_vc3 {
    virtual void s0();
    virtual int s1();
};

struct C_005f05e0 { int FUN_005f05e0(unsigned int); };
struct C_00cc9040 { void FUN_00cc9040(unsigned int); };
struct C_00e0f9c0 { void FUN_00e0f9c0(unsigned int, unsigned int, unsigned int); };
struct C_00e5c780 { int FUN_00e5c780(unsigned int, unsigned int); };

// @ 0x00ccbb60
extern "C" void __fastcall FUN_00ccbb60(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1005;
    int t1006;
    int t1012;
    int t1016;
    int t1017;
    int v_l4;
    int t1018;
    int t1019;
    int t1025;
    int t1028;
    int t1029;
    int t1035;
    int t1039;
    int t1040;
    int t1045;
    t1003 = (int)((int)(a4));
    t1005 = (int)((int)(self));
    t1006 = (int)(*(int*)((char*)(t1005) + 112));
    if (t1006 != (int)0) {
        ((C_00e0f9c0*)(t1006))->FUN_00e0f9c0((unsigned int)(t1003), (unsigned int)((int)1), (unsigned int)((int)0));
    }
    *(int*)&(a4) = (int)(t1003);
    if (t1003 != (int)0) {
        t1012 = (int)(t1003);
        ((il2c_vc0*)(t1012))->s0();
    }
    t1016 = (int)((int)&a4);
    t1017 = (int)((int)&v_l4);
    t1018 = (int)(t1005 + (int)148);
    t1019 = (int)(t1018);
    ((C_00e5c780*)(t1019))->FUN_00e5c780((unsigned int)(t1017), (unsigned int)(t1016));
    if (t1003 != (int)0) {
        t1025 = (int)(t1003);
        ((il2c_vc1*)(t1025))->s1();
    }
    t1028 = (int)(t1005 + (int)152);
    if (v_l4 != t1028) {
        t1029 = (int)(*(int*)((char*)(t1005) + 120));
        if (t1029 != (int)0) {
            ((C_00cc9040*)(t1029))->FUN_00cc9040((unsigned int)(t1003));
        }
        *(int*)&(a4) = (int)(t1003);
        if (t1003 != (int)0) {
            t1035 = (int)(t1003);
            ((il2c_vc2*)(t1035))->s0();
        }
        t1039 = (int)((int)&a4);
        t1040 = (int)(t1018);
        ((C_005f05e0*)(t1040))->FUN_005f05e0((unsigned int)(t1039));
        if (t1003 != (int)0) {
            t1045 = (int)(t1003);
            ((il2c_vc3*)(t1045))->s1();
        }
    }
    return;
}
