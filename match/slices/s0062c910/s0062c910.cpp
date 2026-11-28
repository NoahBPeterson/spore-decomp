// 0x0062c910: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEditors/SPPlayMode.cpp, match/slices/s0062bb40/s0062bb40.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
};
struct il2c_vc1 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
};
struct il2c_vc2 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};
struct il2c_vc3 {
    virtual void s0();
    virtual void s1();
    virtual int s2();
};
struct il2c_vc4 {
    virtual void s0();
    virtual void s1();
};

extern "C" unsigned char g_015f7cf4[];
struct C_0062c340 { void FUN_0062c340(); };

// @ 0x0062c910
// @ 0x0062c910
extern "C" void __fastcall FUN_0062c910(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1005;
    int t1011;
    int t1015;
    int t1027;
    int t1032;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 148));
    t1005 = (int)((int)0);
    if (t1003 != t1005) {
        *(int*)((char*)(t1002) + 148) = (int)(t1005);
        ((il2c_vc0*)(t1003))->s1();
    }
    if ((int)*(int*)((char*)(t1002) + 200) != t1005) {
        t1011 = (int)(t1002);
        ((C_0062c340*)(t1011))->FUN_0062c340();
    }
    t1015 = (int)(*(int*)((char*)(t1002) + 204));
    ((il2c_vc1*)(t1015))->s2();
    *(int*)((char*)(t1002) + 204) = (int)(t1005);
    ((il2c_vc2*)((t1002 + (int)(13704))))->s2();
    t1027 = (int)((int)(*(int*)g_015f7cf4));
    if (t1027 != t1005) {
        *(int*)g_015f7cf4 = (int)(t1005);
        ((il2c_vc3*)(t1027))->s2();
    }
    t1032 = (int)(*(int*)((char*)(t1002) + 12));
    if (t1032 != t1005) {
        *(int*)((char*)(t1002) + 12) = (int)(t1005);
        ((il2c_vc4*)(t1032))->s1();
        return;
    }
    return;
}
