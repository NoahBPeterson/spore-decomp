// 0x00a870b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a86b30/s00a86b30.cpp, src/game/Swarm/_at_00a80000.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual int s5(int);
};

struct C_00537dc0 { void FUN_00537dc0(unsigned int); };
extern "C" int __cdecl FUN_007d5590(...);

// @ 0x00a870b0
extern "C" void __fastcall FUN_00a870b0(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1004;
    int t1006;
    int v_l56[14];
    int t1007;
    int t1010;
    int t1011;
    int t1015;
    int t1016;
    int t1017;
    unsigned char t7;
    int t1018;
    int t1022;
    int t1023;
    float t1024;
    int t1025;
    float t1026;
    float t1027;
    int t1028;
    int t1029;
    float t1030;
    int t1031;
    float t1032;
    int t1033;
    int t1035;
    t1002 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1002) + 124) == (unsigned char)0) {
        t1003 = (int)((int)(a8));
        t1004 = (int)((int)(a4));
        t1006 = (int)((int)&v_l56);
        t1007 = (int)(t1002 + (int)20);
        t1010 = (int)FUN_007d5590((unsigned int)(t1006), (unsigned int)(t1004), (unsigned int)(t1003));
        t1011 = (int)(t1007);
        ((C_00537dc0*)(t1011))->FUN_00537dc0((unsigned int)(t1010));
        t1015 = (int)(*(int*)((char*)(t1002) + 12));
        t1016 = (int)(*(int*)((char*)(t1015) + 8));
        t1017 = (int)((unsigned int)(t1016) >> (int)2);
        t7 = (unsigned char)((unsigned char)(t1017) & (unsigned char)1);
        if (t7 != (unsigned char)0) {
            t1018 = (int)(*(int*)((char*)(t1002) + 144));
            if (t1018 != (int)0) {
                ((C_00537dc0*)(t1018))->FUN_00537dc0((unsigned int)(t1007));
                t1022 = (int)(*(int*)((char*)(t1002) + 12));
                t1023 = (int)(*(int*)((char*)(t1022) + 72));
                t1024 = (float)(*(float*)((char*)(t1023)));
                t1025 = (int)(*(int*)((char*)(t1002) + 144));
                t1026 = (float)(t1024 * (float)*(float*)((char*)(t1002) + 104));
                *(unsigned short*)((char*)(t1025)) |= (unsigned short)1;
                *(unsigned short*)((char*)(t1025) + 2) += (unsigned short)1;
                t1027 = (float)(t1026 * (float)*(float*)((char*)(t1025) + 16));
                *(float*)((char*)(t1025) + 16) = (float)(t1027);
                t1028 = (int)(*(int*)((char*)(t1002) + 12));
                t1029 = (int)(*(int*)((char*)(t1028) + 52));
                t1030 = (float)(*(float*)((char*)(t1029)));
                t1031 = (int)(*(int*)((char*)(t1002) + 144));
                t1032 = (float)(t1030 * (float)*(float*)((char*)(t1002) + 108));
                *(float*)((char*)(t1031) + 72) = (float)(t1032);
                t1033 = (int)(*(int*)((char*)(t1002) + 140));
                t1035 = (int)(*(int*)((char*)(t1002) + 144));
                t1015 = (int)((il2c_vc0*)(t1033))->s5((int)(t1035));
            }
        }
    }
    return;
}
