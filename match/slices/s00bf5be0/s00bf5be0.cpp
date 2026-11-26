// 0x00bf5be0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00bf51d0/s00bf51d0.cpp, src/game/SPGonzago/_at_00bf0000.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1();
};

extern "C" unsigned char g_0168c514[];
struct C_00ae9390 { int FUN_00ae9390(); };
struct C_00b3d4a0 { int FUN_00b3d4a0(); };
struct C_00bd9bf0 { int FUN_00bd9bf0(); };
struct C_00be5be0 { int FUN_00be5be0(unsigned int, unsigned int); };
struct C_00bf0f90 { int FUN_00bf0f90(); };
struct C_00bf49e0 { int FUN_00bf49e0(unsigned int); };

// @ 0x00bf5be0
extern "C" bool __fastcall FUN_00bf5be0(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1003;
    int t1004;
    int t1007;
    int t1008;
    int t1011;
    bool t1016;
    int t1020;
    int t1021;
    int t1024;
    bool t1028;
    int t1030;
    int t1031;
    bool t1034;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    if (t1000 != (int)27271582) {
        if (t1000 != (int)34343068) {
            if (t1000 != (int)106057615) goto Lbf5c9f;
            t1004 = (int)(*(int*)((char*)(t1003) + 1132));
            if (t1004 != (int)0) {
                t1000 = (int)((C_00bd9bf0*)(t1004))->FUN_00bd9bf0();
                t1007 = (int)(t1003 + (int)(-56));
                if (t1000 == t1007) {
                    if ((unsigned char)*(unsigned char*)((char*)(t1003) + 81) != (unsigned char)0) {
                        t1000 = (int)(*(int*)((char*)(t1003) + 1136));
                        if (t1000 != (int)(-1)) {
                            t1008 = (int)(*(int*)((char*)(t1003) + 1132));
                            t1000 = (int)((C_00be5be0*)(t1008))->FUN_00be5be0((unsigned int)(t1000), (unsigned int)((int)g_0168c514));
                        }
                    }
                }
            }
            t1011 = (int)(*(int*)((char*)(t1003) + 1132));
            *(int*)((char*)(t1003) + 1132) = (int)((int)0);
            if (t1011 != (int)0) {
                t1000 = (int)((il2c_vc0*)(t1011))->s1();
            }
            *(int*)((char*)(t1003) + 1136) = (int)((int)(-1));
            t1016 = true;
            return (bool)(t1016);
        }
        t1020 = (int)((C_00b3d4a0*)((int)(self)))->FUN_00b3d4a0();
        t1021 = (int)(t1020);
        t1000 = (int)((C_00ae9390*)(t1021))->FUN_00ae9390();
        if ((unsigned char)(t1000) != (unsigned char)0) goto Lbf5c9f;
        t1024 = (int)(t1003 + (int)(-56));
        ((C_00bf0f90*)(t1024))->FUN_00bf0f90();
        t1028 = true;
        return (bool)(t1028);
    }
    t1030 = (int)((int)(a8));
    t1000 = (int)(*(int*)((char*)(t1030) + 16));
    if (t1000 != (int)0) {
        if ((int)*(int*)((char*)(t1030) + 8) == (int)4) {
            t1031 = (int)(t1003 + (int)(-56));
            t1000 = (int)((C_00bf49e0*)(t1031))->FUN_00bf49e0((unsigned int)(t1000));
        }
    }
    Lbf5c9f:;
    t1034 = true;
    return (bool)(t1034);
}
