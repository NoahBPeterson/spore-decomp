// 0x009e3790: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s009e3580/s009e3580.cpp, src/game/SPCreatureAnim/gait_record.cpp.

extern "C" unsigned char g_015515dc[];
struct C_009dbc60 { void FUN_009dbc60(unsigned int); };
extern "C" void __stdcall FUN_009e1370(unsigned int);
struct C_009e22f0 { void FUN_009e22f0(unsigned int); };

// @ 0x009e3790
extern "C" int __fastcall FUN_009e3790(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1011;
    int t1016;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if (t1004 != t1002) {
        ((C_009dbc60*)((int)(self)))->FUN_009dbc60((unsigned int)(t1002));
        FUN_009e1370((unsigned int)(t1002));
        if ((int)(*(int*)g_015515dc) != (int)0) {
            t1011 = (int)(t1004);
            ((C_009e22f0*)(t1011))->FUN_009e22f0((unsigned int)(t1002));
        }
    }
    t1016 = (int)(t1004);
    return (int)(t1016);
}
