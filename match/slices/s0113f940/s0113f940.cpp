// 0x0113f940: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/cmn/spktplay.cpp.cpp, match/slices/s0113ec90/s0113ec90.cpp.

extern "C" unsigned char g_016e7cc8[];
extern "C" unsigned char g_016e7cd0[];
extern "C" unsigned char g_016e7fcc[];

// @ 0x0113f940
extern "C" void __cdecl FUN_0113f940(void)
{
    int t1001;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1011;
    int t1012;
    int t1013;
    t1001 = (int)((int)0);
    if ((int)(*(int*)g_016e7cc8) > t1001) {
        t1003 = (int)((int)g_016e7cd0);
        do {
            t1004 = (int)(*(unsigned short*)((char*)(t1003) - 2));
            t1005 = (int)(*(int*)((char*)((t1004)*4) + (int)g_016e7fcc));
            if (t1005 != (int)0) {
                if ((unsigned short)*(unsigned short*)((char*)(t1003) - 4) == (unsigned short)0) {
                    t1006 = (int)(*(int*)((char*)(t1005) + 88));
                    t1007 = (int)(*(int*)((char*)(t1005) + 84));
                    t1008 = (int)(*(int*)((char*)(t1003)));
                    t1005 = (int)((int (__cdecl*)(int, int, int))(t1007))((int)(t1004), (int)(t1008), (int)(t1006));
                    goto L113f988;
                }
                t1011 = (int)(*(int*)((char*)(t1005) + 88));
                t1012 = (int)(*(int*)((char*)(t1003)));
                t1013 = (int)(*(int*)((char*)(t1005) + 80));
                t1005 = (int)((int (__cdecl*)(int, int))(t1013))((int)(t1012), (int)(t1011));
            }
            L113f988:;
            t1001 = (int)(t1001 + (int)1);
            t1003 = (int)(t1003 + (int)8);
        } while (t1001 < (int)(*(int*)g_016e7cc8));
        *(int*)g_016e7cc8 = (int)((int)0);
        return;
    }
    *(int*)g_016e7cc8 = (int)(t1001);
    return;
}
