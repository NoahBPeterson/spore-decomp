// 0x0083f680: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0083f140/s0083f140.cpp, src/game/UTFSpore_Win32/FileParser.cpp.

// lifted by il2c_lift + l2c_search (bind@t1007); CI scorer MATCH; corpus status nonmatching/residual
struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11(int, int, int);
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual int s6();
};

struct C_00883860 { int FUN_00883860(); };

template<class HsT> __forceinline HsT& hs_bind(HsT& x) { HsT& r = x; return r; }
// @ 0x0083f680
extern "C" bool __fastcall FUN_0083f680(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1007;
    int t1008;
    int t1013;
    int t1019;
    int t1027;
    bool t1031;
    bool t1034;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 12) != (unsigned char)0) {
        *(unsigned char*)((char*)(t1002) + 12) = (unsigned char)((int)0);
        t1003 = (int)((C_00883860*)((int)(self)))->FUN_00883860();
        if (t1003 != (int)0) {
            t1007 = (int)(t1002 + (int)4);
            t1008 = (int)(t1003);
            ((il2c_vc0*)(t1008))->s11((int)(hs_bind(t1007)), (int)((int)1866592882), (int)((int)(-9999)));
        }
        t1013 = (int)(*(int*)((char*)(t1002) + 16));
        if (t1013 != (int)0) {
            ((il2c_vc1*)(t1013))->s3();
            t1019 = (int)(*(int*)((char*)(t1002) + 16));
            if (t1019 != (int)0) {
                *(int*)((char*)(t1002) + 16) = (int)((int)0);
                ((il2c_vc2*)(t1019))->s1();
            }
        }
        t1027 = (int)(t1002);
        ((il2c_vc3*)(t1027))->s6();
        t1031 = true;
        return (bool)(t1031);
    }
    t1034 = false;
    return (bool)(t1034);
}
