// 0x00a291b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPAudio/AudioSystem.cpp, match/slices/s00a290b0/s00a290b0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
};

struct C_00a24480 { int FUN_00a24480(unsigned int, unsigned int); };

// @ 0x00a291b0
extern "C" void __fastcall FUN_00a291b0(char* self, int edx_unused)
{
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1017;
    int t1018;
    int t1019;
    t1005 = (int)(*(int*)((char*)((int)(self)) + 5112));
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
    t1007 = (int)(*(int*)((char*)((int)(self)) + 5116));
    t1008 = (int)((int)(self) + (int)5108);
    t1009 = (int)(*(int*)((char*)(t1008) + 4));
    t1010 = (int)(*(int*)((char*)(t1009) + (t1007)*4));
    if (t1006 != t1010) {
        do {
            t1011 = (int)(*(int*)((char*)(t1006) + 4));
            ((il2c_vc0*)(t1011))->s5();
            t1006 = (int)(*(int*)((char*)(t1006) + 8));
            if (t1006 == (int)0) {
                do {
                    t1006 = (int)(*(int*)((char*)(t1005) + 4));
                    t1005 = (int)(t1005 + (int)4);
                } while (t1006 == (int)0);
            }
        } while (t1006 != t1010);
    }
    t1017 = (int)(*(int*)((char*)(t1008) + 8));
    t1018 = (int)(*(int*)((char*)(t1008) + 4));
    t1019 = (int)(t1008);
    ((C_00a24480*)(t1019))->FUN_00a24480((unsigned int)(t1018), (unsigned int)(t1017));
    *(int*)((char*)(t1008) + 12) = (int)((int)0);
    return;
}
