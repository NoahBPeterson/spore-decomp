// 0x01043c60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPSpaceUtilities.cpp, match/slices/s010433e0/s010433e0.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual int s3(int);
};

struct C_00b225d0 { void FUN_00b225d0(); };
extern "C" int __stdcall FUN_00b3d300(unsigned int);
struct C_00b8e540 { void FUN_00b8e540(unsigned int); };
struct C_00e0df30 { int FUN_00e0df30(unsigned int); };
struct C_00e0f9c0 { int FUN_00e0f9c0(unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_010666a0(...);
struct C_01067e60 { int FUN_01067e60(); };

// @ 0x01043c60
extern "C" void __cdecl FUN_01043c60(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1004;
    int t1006;
    int t1007;
    unsigned char t2;
    int t1009;
    int t1010;
    int t1011;
    int t1018;
    int t1019;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1028;
    int t1029;
    int t1031;
    int t1035;
    int t1038;
    int t1039;
    int t1043;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000) + 308));
    t1002 = (int)(t1000 + (int)308);
    t1004 = (int)(*(int*)((char*)(t1002) + 4));
    t1006 = (int)((int)(a8));
    if (t1001 != t1004) {
        t1007 = (int)(t1001 + (int)36);
        do {
            t2 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1007) + 4) & (unsigned char)64);
            if (t2 != (unsigned char)0) {
                t1009 = (int)(*(int*)((char*)(t1007) - 8));
                if (t1009 == (int)*(int*)((char*)(t1006))) {
                    t1010 = (int)(*(int*)((char*)(t1007) - 4));
                    if (t1010 == (int)*(int*)((char*)(t1006) + 4)) {
                        t1011 = (int)(*(int*)((char*)(t1007)));
                        if (t1011 == (int)*(int*)((char*)(t1006) + 8)) goto L1043ca9;
                    }
                }
            }
            t1001 = (int)(t1001 + (int)44);
            t1007 = (int)(t1007 + (int)44);
        } while (t1001 != t1004);
        goto L1043caf;
        L1043ca9:;
        ((C_00b8e540*)(t1002))->FUN_00b8e540((unsigned int)(t1001));
        L1043caf:;
    }
    t1018 = (int)FUN_010666a0();
    t1019 = (int)(t1018);
    t1022 = (int)((C_01067e60*)(t1019))->FUN_01067e60();
    t1023 = (int)(*(int*)((char*)(t1006)));
    t1024 = (int)(t1022);
    t1025 = (int)(t1024);
    t1028 = (int)((C_00e0df30*)(t1025))->FUN_00e0df30((unsigned int)(t1023));
    if (t1028 != (int)0) {
        t1029 = (int)(*(int*)((char*)(t1028) + 20));
        if (t1029 != (int)0) {
            t1031 = (int)(t1029);
            t1035 = (int)((il2c_vc0*)(t1031))->s3((int)((int)28912423));
            if (t1035 != (int)0) {
                t1038 = (int)FUN_00b3d300((unsigned int)(t1035));
                t1039 = (int)(t1038);
                ((C_00b225d0*)(t1039))->FUN_00b225d0();
            }
        }
    }
    t1043 = (int)(t1024);
    ((C_00e0f9c0*)(t1043))->FUN_00e0f9c0((unsigned int)(t1023), (unsigned int)((int)1), (unsigned int)((int)0));
    return;
}
