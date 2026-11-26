// 0x00d596a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCityVisualizer.cpp, match/slices/s00d58a80/s00d58a80.cpp.

struct C_00d59280 { void FUN_00d59280(unsigned int, unsigned int); };

// @ 0x00d596a0
extern "C" int __fastcall FUN_00d596a0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1000;
    int t1003;
    int t1005;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t7;
    int t1013;
    int t8;
    int t1014;
    int t1016;
    t1000 = (int)((int)(a12));
    t1003 = (int)((int)(a4));
    t1005 = (int)((int)(self));
    ((C_00d59280*)((int)(self)))->FUN_00d59280((unsigned int)(t1003), (unsigned int)(t1000));
    t1009 = (int)(*(int*)((char*)(t1005)));
    t1010 = (int)(t1003);
    if ((unsigned int)(t1003) > (unsigned int)0) {
        t1011 = (int)((int)(a8));
        do {
            if (t1009 != (int)0) {
                *(float*)((char*)(t1009)) = (float)(*(float*)((char*)(t1011)));
                *(float*)((char*)(t1009) + 4) = (float)(*(float*)((char*)(t1011) + 4));
                *(float*)((char*)(t1009) + 8) = (float)(*(float*)((char*)(t1011) + 8));
            }
            t1010 = (int)(t1010 - (int)1);
            t1009 = (int)(t1009 + (int)12);
        } while ((unsigned int)(t1010) > (unsigned int)0);
    }
    t1012 = (int)(*(int*)((char*)(t1005)));
    t7 = (int)(t1003 << (int)1);
    t1013 = (int)(t1003 + t7);
    t8 = (int)(t1013 << (int)2);
    t1014 = (int)(t1012 + t8);
    *(int*)((char*)(t1005) + 4) = (int)(t1014);
    t1016 = (int)(t1005);
    return (int)(t1016);
}
