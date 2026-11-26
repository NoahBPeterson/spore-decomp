// 0x00690930: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s006907e0/s006907e0.cpp, src/game/SPEngine/SPJobManager.cpp.

struct C_00690540 { int FUN_00690540(unsigned int); };
struct C_00690b50 { int FUN_00690b50(unsigned int, unsigned int); };

// @ 0x00690930
extern "C" int __fastcall FUN_00690930(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1004;
    int t1005;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    t1000 = (int)((int)(a8));
    t1004 = (int)((int)(a4));
    t1005 = (int)(*(int*)((char*)(t1004) + 72));
    t1008 = (int)((int)(self));
    *(int*)((char*)(t1004) + 72) = (int)(t1000);
    if ((int)*(int*)((char*)(t1004) + 28) == (int)3) {
        t1009 = (int)(*(int*)((char*)(t1004) + 4));
        t1010 = (int)(*(int*)((char*)(t1004)));
        *(int*)((char*)(t1009)) = (int)(t1010);
        *(int*)((char*)(t1010) + 4) = (int)(t1009);
        *(int*)((char*)(t1004) + 4) = (int)((int)0);
        *(int*)((char*)(t1004)) = (int)((int)0);
        t1011 = (int)(*(int*)((char*)(t1008) + 96));
        t1012 = (int)(t1008 + (int)92);
        *(int*)((char*)(t1004) + 4) = (int)(t1011);
        *(int*)((char*)(t1004)) = (int)(t1012);
        *(int*)((char*)(t1012) + 4) = (int)(t1004);
        t1013 = (int)(*(int*)((char*)(t1004) + 4));
        *(int*)((char*)(t1013)) = (int)(t1004);
        t1014 = (int)(t1008);
        *(int*)((char*)(t1004) + 28) = (int)((int)2);
        t1000 = (int)((C_00690540*)(t1014))->FUN_00690540((unsigned int)(t1004));
    }
    t1017 = (int)(t1004 + (int)56);
    t1018 = (int)(*(int*)((char*)(t1017)));
    if (t1018 != t1017) {
        do {
            t1019 = (int)(*(int*)((char*)(t1018) + 16));
            t1020 = (int)(t1008);
            t1000 = (int)((C_00690b50*)(t1020))->FUN_00690b50((unsigned int)(t1019), (unsigned int)(t1005));
            t1018 = (int)(*(int*)((char*)(t1018)));
        } while (t1018 != t1017);
    }
    return (int)(t1000);
}
