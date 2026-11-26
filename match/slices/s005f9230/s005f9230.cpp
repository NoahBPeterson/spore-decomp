// 0x005f9230: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005f8fe0/s005f8fe0.cpp.

struct C_00423650 { int FUN_00423650(unsigned int, unsigned int); };
struct C_0057cb60 { int FUN_0057cb60(unsigned int); };

// @ 0x005f9230
extern "C" bool __fastcall FUN_005f9230(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1002;
    int t1003;
    bool t1007;
    int t1008;
    int t1009;
    bool t1013;
    int t1014;
    int t1015;
    bool t1019;
    int t1020;
    int t1021;
    bool t1025;
    int t1026;
    int t1027;
    bool t1031;
    int t1032;
    int t1033;
    int t1034;
    bool t1037;
    t1000 = (int)((int)(a4));
    if ((unsigned int)(t1000) <= (unsigned int)912954125) {
        if (t1000 != (int)912954125) {
            if ((unsigned int)(t1000) <= (unsigned int)610804372) {
                if (t1000 != (int)610804372) {
                    if (t1000 != (int)83264676) {
                        if (t1000 != (int)597278293) goto L5f930b;
                        t1002 = (int)((int)(self) + (int)292);
                        t1003 = (int)((int)(a8));
                        ((C_0057cb60*)(t1003))->FUN_0057cb60((unsigned int)(t1002));
                        t1007 = true;
                        return (bool)(t1007);
                    }
                    t1008 = (int)((int)(self) + (int)356);
                    t1009 = (int)((int)(a8));
                    ((C_0057cb60*)(t1009))->FUN_0057cb60((unsigned int)(t1008));
                    t1013 = true;
                    return (bool)(t1013);
                }
                t1014 = (int)((int)(self) + (int)324);
                t1015 = (int)((int)(a8));
                ((C_0057cb60*)(t1015))->FUN_0057cb60((unsigned int)(t1014));
                t1019 = true;
                return (bool)(t1019);
            }
            if (t1000 != (int)731352134) goto L5f930b;
            t1020 = (int)((int)(self) + (int)276);
            t1021 = (int)((int)(a8));
            ((C_0057cb60*)(t1021))->FUN_0057cb60((unsigned int)(t1020));
            t1025 = true;
            return (bool)(t1025);
        }
        t1000 = (int)((int)(self) + (int)372);
        goto L5f92f7;
    }
    if (t1000 != (int)1033349348) {
        if (t1000 != (int)1133470535) {
            if (t1000 != (int)1198168263) goto L5f930b;
            t1026 = (int)((int)(self) + (int)340);
            t1027 = (int)((int)(a8));
            ((C_0057cb60*)(t1027))->FUN_0057cb60((unsigned int)(t1026));
            t1031 = true;
            return (bool)(t1031);
        }
        t1000 = (int)((int)(self) + (int)308);
        goto L5f92f7;
    }
    t1000 = (int)((int)(self) + (int)260);
    L5f92f7:;
    t1032 = (int)((int)(a8));
    if (t1000 != t1032) {
        t1033 = (int)(*(int*)((char*)(t1000) + 4));
        t1034 = (int)(*(int*)((char*)(t1000)));
        t1000 = (int)((C_00423650*)(t1032))->FUN_00423650((unsigned int)(t1034), (unsigned int)(t1033));
    }
    L5f930b:;
    t1037 = true;
    return (bool)(t1037);
}
