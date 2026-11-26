// 0x0104f250: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0104e060/s0104e060.cpp, src/game/SPGonzago/SPToolManager.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3(int);
};

extern "C" int __cdecl FUN_00921580(...);
struct C_0104ef30 { void FUN_0104ef30(unsigned int); };

// @ 0x0104f250
extern "C" int __fastcall FUN_0104f250(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1006;
    int t1007;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1022;
    int t1023;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 96));
    t1006 = (int)(t1003 + (int)92);
    if (t1004 != t1006) {
        do {
            t1007 = (int)(*(int*)((char*)(t1004) + 16));
            ((il2c_vc0*)(t1007))->s3((int)((int)1));
            t1015 = (int)FUN_00921580((unsigned int)(t1004));
            t1004 = (int)(t1015);
        } while (t1004 != t1006);
    }
    t1016 = (int)(*(int*)((char*)(t1003) + 100));
    t1017 = (int)(t1003 + (int)88);
    t1018 = (int)(t1017);
    ((C_0104ef30*)(t1018))->FUN_0104ef30((unsigned int)(t1016));
    t1022 = (int)(t1017 + (int)4);
    *(int*)((char*)(t1017) + 8) = (int)(t1022);
    *(int*)((char*)(t1022)) = (int)(t1022);
    t1023 = (int)((int)0);
    *(int*)((char*)(t1017) + 12) = (int)(t1023);
    *(unsigned char*)((char*)(t1017) + 16) = (unsigned char)((unsigned char)(t1023));
    *(int*)((char*)(t1017) + 20) = (int)(t1023);
    return (int)(t1023);
}
