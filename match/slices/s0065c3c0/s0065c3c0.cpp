// 0x0065c3c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0065bf20/s0065bf20.cpp.

extern "C" unsigned char g_013ffec8[];
extern "C" unsigned char g_01526598[];
extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bae[];
extern "C" void __cdecl FUN_004e0850(...);
extern "C" void __cdecl FUN_006214c0(...);
struct C_00997730 { bool FUN_00997730(unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x0065c3c0
extern "C" bool __fastcall FUN_0065c3c0(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1003;
    int t1004;
    int t1007;
    int t1008;
    int t1012;
    int v_l16[4];
    int t1013;
    int t1017;
    int t1018;
    int t1019;
    int t1023;
    int t1024;
    int t1025;
    int t1026;
    int t1029;
    bool t1030;
    int t1031;
    int t1032;
    int t1033;
    bool t1037;
    bool t1040;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 156));
    if (t1003 != (int)0) {
        t1004 = (int)((int)(*(int*)g_01526598));
        t1007 = (int)(t1002 + (int)32);
        t1008 = (int)(t1007);
        ((C_00997730*)(t1008))->FUN_00997730((unsigned int)(t1003), (unsigned int)(t1004), (unsigned int)((int)0), (unsigned int)((int)0));
        t1012 = (int)((int)&v_l16);
        t1013 = (int)((int)g_01667bac);
        (*(int*)&v_l16[0]) = (int)(t1013);
        (*(int*)&v_l16[1]) = (int)(t1013);
        (*(int*)&v_l16[2]) = (int)((int)g_01667bae);
        FUN_006214c0((unsigned int)((int)103728234), (unsigned int)(t1012));
        t1017 = (int)((int)(a8));
        t1018 = (int)((int)(a4));
        t1019 = (int)((int)&v_l16);
        FUN_004e0850((unsigned int)(t1019), (unsigned int)((int)g_013ffec8), (unsigned int)(t1018), (unsigned int)(t1017));
        t1023 = (int)((*(int*)&v_l16[0]));
        t1024 = (int)(*(int*)((char*)(t1002) + 156));
        t1025 = (int)(t1007);
        t1030 = ((C_00997730*)(t1025))->FUN_00997730((unsigned int)(t1024), (unsigned int)(t1023), (unsigned int)((int)0), (unsigned int)((int)0));
        t1029 = (int)((*(int*)&v_l16[2]));
        t1031 = (int)((*(int*)&v_l16[0]));
        t1032 = (int)(t1029 - t1031);
        t1033 = (int)(t1032 & (int)(-2));
        if (t1033 > (int)2) {
            if (t1031 != (int)0) {
                t1031 = (int)FUN_00f47380((unsigned int)(t1031));
            }
        }
        t1037 = t1030;
        return t1037;
    }
    t1040 = false;
    return (bool)(t1040);
}
