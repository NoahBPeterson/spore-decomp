// 0x0103d090: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPSpaceTrading.cpp, match/slices/s0103c3a0/s0103c3a0.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_013ef094[];
struct C_005c7f10 { void FUN_005c7f10(); };
struct C_00b638b0 { int FUN_00b638b0(); };
struct C_00bf1b60 { void FUN_00bf1b60(); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x0103d090
extern "C" void __fastcall FUN_0103d090(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1007;
    int t1011;
    int t1015;
    int t1019;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 156));
    if (t1003 != (int)0) {
        if (t1003 != (int)*(int*)((char*)(t1002) + 172)) {
            FUN_00f47380((unsigned int)(t1003));
        }
    }
    t1007 = (int)(*(int*)((char*)(t1002) + 96));
    if (t1007 != (int)0) {
        if (t1007 != (int)*(int*)((char*)(t1002) + 112)) {
            FUN_00f47380((unsigned int)(t1007));
        }
    }
    t1011 = (int)(t1002 + (int)72);
    ((C_00bf1b60*)(t1011))->FUN_00bf1b60();
    t1015 = (int)(t1002 + (int)52);
    ((C_005c7f10*)(t1015))->FUN_005c7f10();
    t1019 = (int)(t1002 + (int)16);
    ((C_00b638b0*)(t1019))->FUN_00b638b0();
    *(int*)((char*)(t1002) + 8) = (int)((int)g_013eb938);
    *(int*)((char*)(t1002)) = (int)((int)g_013ef094);
    return;
}
