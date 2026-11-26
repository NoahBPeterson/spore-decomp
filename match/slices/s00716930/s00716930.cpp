// 0x00716930: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00716110/s00716110.cpp, src/game/SPEngine/_at_00710000.cpp.

struct C_00473890 { int FUN_00473890(unsigned int); };
struct C_004b5ad0 { int FUN_004b5ad0(unsigned int, unsigned int); };

// @ 0x00716930
extern "C" int __fastcall FUN_00716930(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1004;
    int t1013;
    int t1012;
    int t1014;
    int t1015;
    int t1018;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    t1002 = (int)((int)(self) + (int)28);
    t1003 = (int)(*(int*)((char*)(t1002) + 4));
    t1004 = (int)(t1003 - (int)*(int*)((char*)(t1002)));
    t1013 = (int)(t1004 / (int)12);
    t1012 = (int)((int)(a4));
    t1014 = (int)(t1013 + t1012);
    t1015 = (int)(t1002);
    t1018 = (int)((C_00473890*)(t1015))->FUN_00473890((unsigned int)(t1014));
    if (t1012 > (int)0) {
        t1020 = (int)(t1012);
        t1021 = (int)((int)(a8));
        do {
            t1018 = (int)(*(int*)((char*)(t1002) + 4));
            if ((unsigned int)(t1018) < (unsigned int)*(int*)((char*)(t1002) + 8)) {
                t1022 = (int)(t1018 + (int)12);
                *(int*)((char*)(t1002) + 4) = (int)(t1022);
                if (t1018 == (int)0) goto L716990;
                *(float*)((char*)(t1018)) = (float)(*(float*)((char*)(t1021)));
                *(float*)((char*)(t1018) + 4) = (float)(*(float*)((char*)(t1021) + 4));
                *(float*)((char*)(t1018) + 8) = (float)(*(float*)((char*)(t1021) + 8));
                goto L716990;
            }
            t1023 = (int)(t1002);
            t1018 = (int)((C_004b5ad0*)(t1023))->FUN_004b5ad0((unsigned int)(t1018), (unsigned int)(t1021));
            L716990:;
            t1021 = (int)(t1021 + (int)12);
            t1020 = (int)(t1020 - (int)1);
        } while (t1020 != (int)0);
    }
    return (int)(t1018);
}
