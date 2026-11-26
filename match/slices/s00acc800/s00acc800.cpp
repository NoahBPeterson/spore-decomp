// 0x00acc800: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00acc140/s00acc140.cpp, src/game/SPGonzago/_at_00ac0000.cpp.

extern "C" unsigned char g_01654c04[];
struct C_0041e4d0 { int FUN_0041e4d0(unsigned int); };
struct C_004e3e10 { int FUN_004e3e10(unsigned int, unsigned int); };
struct C_00b5b800 { int FUN_00b5b800(); };
extern "C" int __cdecl FUN_01021260(...);

// @ 0x00acc800
extern "C" int __stdcall FUN_00acc800(int a4)
{
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1015;
    int t1018;
    int t1020;
    int t1021;
    int t1022;
    int t1029;
    int t1030;
    int t1031;
    int t1035;
    int t1037;
    int t1038;
    int t1039;
    int t1040;
    int t1041;
    int t1042;
    int t1043;
    t1003 = (int)FUN_01021260();
    if (t1003 != (int)0) {
        t1005 = (int)(*(int*)((char*)(t1003) + 316));
        t1006 = (int)(*(int*)((char*)(t1005) + 212));
        t1007 = (int)(t1006 - (int)*(int*)((char*)(t1005) + 208));
        t1015 = (int)(t1007 / (int)12);
        t1018 = (int)((C_00b5b800*)(t1007))->FUN_00b5b800();
        if (t1018 == (int)g_01654c04) {
            t1015 = (int)((int)5);
        }
        t1020 = (int)((int)(a4));
        t1021 = (int)(*(int*)((char*)(t1020) + 4));
        t1022 = (int)(t1021 - (int)*(int*)((char*)(t1020)));
        t1029 = (int)(t1022 / (int)12);
        t1030 = (int)(t1029 + t1015);
        t1031 = (int)(t1020);
        t1003 = (int)((C_0041e4d0*)(t1031))->FUN_0041e4d0((unsigned int)(t1030));
        if (t1015 > (int)0) {
            t1035 = (int)((int)0);
            do {
                t1037 = (int)(*(int*)((char*)(t1005) + 208));
                t1003 = (int)(*(int*)((char*)(t1020) + 4));
                t1038 = (int)(t1037 + t1035);
                if ((unsigned int)(t1003) < (unsigned int)*(int*)((char*)(t1020) + 8)) {
                    t1039 = (int)(t1003 + (int)12);
                    *(int*)((char*)(t1020) + 4) = (int)(t1039);
                    if (t1003 == (int)0) goto Lacc8a5;
                    t1040 = (int)(*(int*)((char*)(t1038)));
                    *(int*)((char*)(t1003)) = (int)(t1040);
                    t1041 = (int)(*(int*)((char*)(t1038) + 4));
                    *(int*)((char*)(t1003) + 4) = (int)(t1041);
                    t1042 = (int)(*(int*)((char*)(t1038) + 8));
                    *(int*)((char*)(t1003) + 8) = (int)(t1042);
                    goto Lacc8a5;
                }
                t1043 = (int)(t1020);
                t1003 = (int)((C_004e3e10*)(t1043))->FUN_004e3e10((unsigned int)(t1003), (unsigned int)(t1038));
                Lacc8a5:;
                t1035 = (int)(t1035 + (int)12);
                t1015 = (int)(t1015 - (int)1);
            } while (t1015 != (int)0);
        }
    }
    return (int)(t1003);
}
