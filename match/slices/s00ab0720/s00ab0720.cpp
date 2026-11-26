// 0x00ab0720: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ab0590/s00ab0590.cpp.

struct C_00aaf670 { void FUN_00aaf670(unsigned int); };

// @ 0x00ab0720
extern "C" int __fastcall FUN_00ab0720(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1006;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1016;
    int t1019;
    t1003 = (int)((int)(self));
    t1004 = (int)(t1003 + (int)24);
    t1006 = (int)(*(int*)((char*)(t1004)));
    if (t1006 != t1004) {
        do {
            t1008 = (int)(*(int*)((char*)(t1006) + 4));
            t1009 = (int)(*(int*)((char*)(t1006)));
            *(int*)((char*)(t1008)) = (int)(t1009);
            t1010 = (int)(t1006);
            *(int*)((char*)(t1009) + 4) = (int)(t1008);
            *(int*)((char*)(t1006)) = (int)((int)0);
            *(int*)((char*)(t1006) + 4) = (int)((int)0);
            *(int*)((char*)(t1003) + 32) -= (int)1;
            t1011 = (int)(t1003);
            t1006 = (int)(t1009);
            ((C_00aaf670*)(t1011))->FUN_00aaf670((unsigned int)(t1010));
        } while (t1009 != t1004);
    }
    t1016 = (int)(*(int*)((char*)(t1004)));
    if (t1016 != t1004) {
        goto Lab0770;
        goto Lab0770;
        Lab0770:;
        t1019 = (int)(*(int*)((char*)(t1016)));
        *(int*)((char*)(t1016) + 4) = (int)((int)0);
        *(int*)((char*)(t1016)) = (int)((int)0);
        t1016 = (int)(t1019);
        if (t1019 != t1004) goto Lab0770;
    }
    *(int*)((char*)(t1004)) = (int)(t1004);
    *(int*)((char*)(t1004) + 4) = (int)(t1004);
    return (int)(t1016);
}
