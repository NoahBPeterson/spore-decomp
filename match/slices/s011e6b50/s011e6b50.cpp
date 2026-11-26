// 0x011e6b50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011e6870/s011e6870.cpp.

extern "C" unsigned char g_014f6558[];
struct C_011ec170 { void FUN_011ec170(unsigned int); };
struct C_011ec230 { void FUN_011ec230(); };

// @ 0x011e6b50
extern "C" int __fastcall FUN_011e6b50(char* self, int edx_unused)
{
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1011;
    int t1012;
    int t1018;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1027;
    int t1028;
    int t1029;
    int t1030;
    int t1034;
    int t1039;
    int t1043;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004) + 4));
    t1006 = (int)(t1005 + (int)4);
    t1007 = (int)(t1006);
    ((C_011ec170*)(t1007))->FUN_011ec170((unsigned int)((int)g_014f6558));
    t1011 = (int)(*(int*)((char*)(t1004) + 12));
    if (t1011 == (int)0) {
        t1012 = (int)(t1006);
        ((C_011ec230*)(t1012))->FUN_011ec230();
        t1018 = (int)((int)0);
        return (int)(t1018);
    }
    t1021 = (int)(*(int*)((char*)(t1004) + 16));
    t1022 = (int)(*(int*)((char*)(t1021) + 8));
    *(int*)((char*)(t1021) + 16) = (int)((int)1);
    t1023 = (int)(*(int*)((char*)(t1004) + 12));
    t1024 = (int)(t1023 - t1022);
    *(int*)((char*)(t1004) + 12) = (int)(t1024);
    t1025 = (int)(*(int*)((char*)(t1005) + 144));
    t1026 = (int)(*(int*)((char*)(t1025) + 304));
    t1027 = (int)(t1026 - t1022);
    *(int*)((char*)(t1025) + 304) = (int)(t1027);
    if (t1024 > (int)0) {
        t1028 = (int)(*(int*)((char*)(t1021)));
        t1029 = (int)(*(int*)((char*)(t1004) + 8));
        if ((int)*(int*)((char*)(t1028) + 20) != t1029) {
            do {
                t1028 = (int)(*(int*)((char*)(t1028)));
            } while ((int)*(int*)((char*)(t1028) + 20) != t1029);
        }
        t1030 = (int)(t1006);
        *(int*)((char*)(t1004) + 16) = (int)(t1028);
        ((C_011ec230*)(t1030))->FUN_011ec230();
        t1034 = (int)(t1021 + (int)4);
        return (int)(t1034);
    }
    t1039 = (int)(t1006);
    *(int*)((char*)(t1004) + 16) = (int)((int)0);
    ((C_011ec230*)(t1039))->FUN_011ec230();
    t1043 = (int)(t1021 + (int)4);
    return (int)(t1043);
}
