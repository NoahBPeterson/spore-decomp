// 0x0112c640: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/cmn/system.cpp.cpp, match/slices/s0112be40/s0112be40.cpp.

extern "C" unsigned char g_014a7c44[];
struct C_00922130 { int FUN_00922130(); };
struct C_009221b0 { void FUN_009221b0(unsigned int); };
struct C_00922270 { void FUN_00922270(); };
struct C_009222a0 { void FUN_009222a0(unsigned int, unsigned int); };

// @ 0x0112c640
extern "C" bool __fastcall FUN_0112c640(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int v_l48[12];
    int t1008;
    int t1012;
    int t1013;
    bool t1014;
    int t1018;
    bool t1023;
    t1003 = (int)((int)(self));
    t1004 = (int)((int)&v_l48);
    ((C_009222a0*)(t1004))->FUN_009222a0((unsigned int)((int)0), (unsigned int)((int)1));
    t1008 = (int)((int)&v_l48);
    ((C_009221b0*)(t1008))->FUN_009221b0((unsigned int)((int)g_014a7c44));
    t1012 = (int)(*(int*)((char*)(t1003) + 224));
    t1013 = (int)((int)&v_l48);
    t1014 = ((unsigned int)(t1012) > (unsigned int)((int)(a4)));
    ((C_00922270*)(t1013))->FUN_00922270();
    t1018 = (int)((int)&v_l48);
    ((C_00922130*)(t1018))->FUN_00922130();
    t1023 = t1014;
    return t1023;
}
