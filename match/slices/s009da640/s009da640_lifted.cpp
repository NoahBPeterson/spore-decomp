// 0x009da640: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPCreatureAnim/_at_009d0000.cpp, match/slices/s009da640/s009da640.cpp.

struct C_009d1090 { void FUN_009d1090(unsigned int); };
struct C_009d30b0 { int FUN_009d30b0(); };
struct C_009d84f0 { void FUN_009d84f0(); };
struct C_009da000 { void FUN_009da000(unsigned int); };
struct C_009da5b0 { void FUN_009da5b0(unsigned int); };

// @ 0x009da640
extern "C" void __fastcall FUN_009da640(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1011;
    int t1013;
    int t1016;
    int v_l4;
    int t1017;
    int t1018;
    int t1019;
    int t1023;
    int t1027;
    int t1031;
    int t1032;
    int t1039;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 20));
    t1004 = (int)(t1003 - (int)*(int*)((char*)(t1002) + 16));
    t1011 = (int)(t1004 / (int)260);
    if (t1011 != (int)0) {
        t1013 = (int)((int)(a4));
        t1016 = (int)((int)0);
        v_l4 = (int)(t1011);
        do {
            t1017 = (int)(*(int*)((char*)(t1002) + 16));
            t1018 = (int)(t1017 + t1016);
            t1019 = (int)(t1018);
            ((C_009da000*)(t1019))->FUN_009da000((unsigned int)(t1013));
            t1023 = (int)(t1018);
            ((C_009da5b0*)(t1023))->FUN_009da5b0((unsigned int)(t1013));
            t1027 = (int)(t1018);
            ((C_009d84f0*)(t1027))->FUN_009d84f0();
            t1031 = (int)(t1002 + (int)36);
            t1032 = (int)(t1018);
            ((C_009d1090*)(t1032))->FUN_009d1090((unsigned int)(t1031));
            t1016 = (int)(t1016 + (int)260);
            v_l4 = (int)(v_l4 - (int)1);
        } while (v_l4 != (int)0);
    }
    t1039 = (int)(t1002);
    ((C_009d30b0*)(t1039))->FUN_009d30b0();
    return;
}
