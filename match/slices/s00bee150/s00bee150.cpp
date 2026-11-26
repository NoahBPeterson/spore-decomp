// 0x00bee150: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00bed920/s00bed920.cpp, src/game/SPGonzago/_at_00be0000.cpp.

struct C_00473810 { void FUN_00473810(unsigned int); };
struct C_00bd94a0 { int FUN_00bd94a0(unsigned int); };
struct C_00becb10 { int FUN_00becb10(unsigned int, unsigned int); };

// @ 0x00bee150
extern "C" void __fastcall FUN_00bee150(char* self, int edx_unused)
{
    int t1003;
    int t1004;
    int t1005;
    int t1012;
    int t1013;
    int t1014;
    int t1018;
    int t1019;
    int t1026;
    int t1029;
    int v_l16;
    int t1030;
    int t1031;
    int t1032;
    int t1033;
    int v_l12[3];
    int t1034;
    int t1035;
    int t1038;
    int t1039;
    int t1040;
    int t1041;
    int t1044;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003) + 352));
    t1005 = (int)(t1004 - (int)*(int*)((char*)(t1003) + 348));
    t1012 = (int)(t1005 / (int)12);
    t1013 = (int)(t1003 + (int)368);
    t1014 = (int)(t1013);
    ((C_00473810*)(t1014))->FUN_00473810((unsigned int)(t1012));
    t1018 = (int)(*(int*)((char*)(t1003) + 352));
    t1019 = (int)(t1018 - (int)*(int*)((char*)(t1003) + 348));
    t1026 = (int)(t1019 / (int)12);
    if (t1026 > (int)0) {
        t1029 = (int)((int)0);
        v_l16 = (int)(t1026);
        do {
            t1030 = (int)(*(int*)((char*)(t1003) + 348));
            t1031 = (int)(*(int*)((char*)(t1013)));
            t1032 = (int)(t1030 + t1029);
            t1033 = (int)((int)&v_l12);
            t1034 = (int)(t1003);
            t1035 = (int)(t1031 + t1029);
            t1038 = (int)((C_00becb10*)(t1034))->FUN_00becb10((unsigned int)(t1033), (unsigned int)(t1032));
            t1039 = (int)(*(int*)((char*)(t1038)));
            *(int*)((char*)(t1035)) = (int)(t1039);
            t1040 = (int)(*(int*)((char*)(t1038) + 4));
            *(int*)((char*)(t1035) + 4) = (int)(t1040);
            t1041 = (int)(*(int*)((char*)(t1038) + 8));
            t1029 = (int)(t1029 + (int)12);
            v_l16 = (int)(v_l16 - (int)1);
            *(int*)((char*)(t1035) + 8) = (int)(t1041);
        } while (v_l16 != (int)0);
    }
    t1044 = (int)(*(int*)((char*)(t1003) + 612));
    ((C_00bd94a0*)(t1044))->FUN_00bd94a0((unsigned int)(t1013));
    return;
}
