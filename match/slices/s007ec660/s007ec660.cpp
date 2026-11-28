// 0x007ec660: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGonzagoDebug.cpp, match/slices/s007ec220/s007ec220.cpp.

extern "C" unsigned char g_013ef094[];
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x007ec660
// @ 0x007ec660
extern "C" int __fastcall FUN_007ec660(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1007;
    int t1011;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 108));
    if (t1003 != (int)0) {
        if ((int)*(int*)((char*)(t1003) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1003));
        }
    }
    t1007 = (int)(*(int*)((char*)(t1002) + 88));
    if (t1007 != (int)0) {
        if ((int)*(int*)((char*)(t1007) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1007));
        }
    }
    t1011 = (int)(*(int*)((char*)(t1002) + 68));
    if (t1011 != (int)0) {
        if ((int)*(int*)((char*)(t1011) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1011));
        }
    }
    t1015 = (int)(*(int*)((char*)(t1002) + 12));
    t1016 = (int)(*(int*)((char*)(t1002) + 20));
    t1017 = (int)(t1016 - t1015);
    t1018 = (int)(t1017 & (int)(-2));
    if (t1018 > (int)2) {
        if (t1015 != (int)0) {
            t1015 = (int)FUN_00f47380((unsigned int)(t1015));
        }
    }
    *(int*)((char*)(t1002)) = (int)((int)g_013ef094);
    return (int)(t1015);
}
