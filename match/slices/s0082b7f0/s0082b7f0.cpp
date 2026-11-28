// 0x0082b7f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/Spui/SPUISerialization.cpp, match/slices/s0082acb0/s0082acb0.cpp.

struct C_00928ba0 { int FUN_00928ba0(unsigned int); };
struct C_00928d40 { int FUN_00928d40(unsigned int, unsigned int, unsigned int, unsigned int); };

// @ 0x0082b7f0
extern "C" int __fastcall FUN_0082b7f0(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1001;
    int t1003;
    int t1004;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1021;
    int t1023;
    int t1024;
    t1000 = (int)((int)(a8));
    if ((unsigned int)(t1000) > (unsigned int)8) {
        t1001 = (int)((int)(a4));
        t1003 = (int)((int)(self) + (int)4);
        t1004 = (int)((C_00928d40*)(t1003))->FUN_00928d40((unsigned int)(t1001), (unsigned int)(t1000), (unsigned int)((int)0), (unsigned int)((int)1));
        return (int)(t1004);
    }
    t1009 = (int)((int)(a4));
    t1010 = (int)((int)(self) + (int)4);
    t1011 = (int)(*(int*)((char*)(t1010) + 8));
    t1012 = (int)(t1009 + (int)7);
    t1013 = (int)(t1012 & (int)(-8));
    t1014 = (int)(t1011 - t1013);
    t1015 = (int)(t1014 - (int)*(int*)((char*)(t1010) + 12));
    if (t1015 < (int)0) {
        t1016 = (int)(t1010);
        t1017 = (int)((C_00928ba0*)(t1016))->FUN_00928ba0((unsigned int)(t1013));
        if ((unsigned char)(t1017) == (unsigned char)0) {
            t1021 = (int)((int)0);
            return (int)(t1021);
        }
    }
    t1023 = (int)(*(int*)((char*)(t1010) + 12));
    t1024 = (int)(t1023 + t1013);
    *(int*)((char*)(t1010) + 12) = (int)(t1024);
    *(int*)((char*)(t1010) + 16) = (int)(t1024);
    return (int)(t1023);
}
