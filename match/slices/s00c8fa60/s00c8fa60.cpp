// 0x00c8fa60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPTribe.cpp, match/slices/s00c8ec60/s00c8ec60.cpp.

struct C_00401090 { int FUN_00401090(); };
struct C_004df550 { int FUN_004df550(unsigned int); };
struct C_004df7d0 { int FUN_004df7d0(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00ba5df0(...);

// @ 0x00c8fa60
extern "C" bool __fastcall FUN_00c8fa60(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1007;
    int t1008;
    int t1009;
    int v_l12[3];
    int t1010;
    int t1013;
    int t1014;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    int t1023;
    int t1024;
    int t1027;
    int t1028;
    int t1030;
    int t1031;
    int t1032;
    bool t1034;
    t1003 = (int)((int)(self));
    t1004 = (int)((C_00401090*)((int)(self)))->FUN_00401090();
    t1007 = (int)(t1004);
    if ((int)*(int*)((char*)(t1003) + 6348) == (int)0) {
        t1008 = (int)(*(int*)((char*)(t1003) + 6404));
        t1009 = (int)((int)&v_l12);
        t1010 = (int)(t1007);
        (*(int*)&v_l12[0]) = (int)((int)0);
        (*(int*)&v_l12[1]) = (int)((int)0);
        (*(int*)&v_l12[2]) = (int)((int)0);
        t1004 = (int)((C_004df7d0*)(t1010))->FUN_004df7d0((unsigned int)(t1008), (unsigned int)((int)(-1146426130)), (unsigned int)(t1009));
        if ((unsigned char)(t1004) != (unsigned char)0) {
            t1013 = (int)(*(int*)((char*)(t1003) + 6404));
            t1014 = (int)((int)&v_l12);
            FUN_00ba5df0((unsigned int)(t1013), (unsigned int)(t1014));
            t1018 = (int)((*(int*)&v_l12[0]));
            t1019 = (int)(*(int*)((char*)(t1003) + 6404));
            *(int*)((char*)(t1019)) = (int)(t1018);
            t1020 = (int)((*(int*)&v_l12[1]));
            *(int*)((char*)(t1019) + 4) = (int)(t1020);
            t1021 = (int)((*(int*)&v_l12[2]));
            t1022 = (int)((int)&v_l12);
            *(int*)((char*)(t1019) + 8) = (int)(t1021);
            t1023 = (int)(t1007);
            t1024 = (int)((C_004df550*)(t1023))->FUN_004df550((unsigned int)(t1022));
            *(int*)((char*)(t1003) + 6348) = (int)(t1024);
            t1027 = (int)((int)12);
            t1028 = (int)(t1003 + (int)6352);
            do {
                t1004 = (int)(*(int*)((char*)(t1003) + 6404));
                if ((int)*(int*)((char*)(t1027) + t1004) != (int)0) {
                    if ((int)*(int*)((char*)(t1028)) == (int)0) {
                        t1030 = (int)(*(int*)((char*)(t1004)));
                        *(int*)((char*)(t1027) + t1004) = (int)(t1030);
                        t1031 = (int)(*(int*)((char*)(t1004) + 4));
                        *(int*)((char*)(t1027) + t1004 + 4) = (int)(t1031);
                        t1032 = (int)(*(int*)((char*)(t1004) + 8));
                        *(int*)((char*)(t1027) + t1004 + 8) = (int)(t1032);
                        t1004 = (int)(*(int*)((char*)(t1003) + 6348));
                        *(int*)((char*)(t1028)) = (int)(t1004);
                    }
                }
                t1027 = (int)(t1027 + (int)12);
                t1028 = (int)(t1028 + (int)4);
            } while (t1027 < (int)168);
        }
    }
    t1034 = true;
    return (bool)(t1034);
}
