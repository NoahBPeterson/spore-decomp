// 0x00e320c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPUISocialRainbow.cpp, match/slices/s00e31670/s00e31670.cpp.

extern "C" unsigned char g_015d1168[];

// @ 0x00e320c0
extern "C" int __cdecl FUN_00e320c0(int a4, int a8, int a12, int a16, float a20)
{
    int t1000;
    unsigned char t1;
    int t1001;
    int t1002;
    int t1005;
    int t1006;
    int t1007;
    unsigned char t5;
    int t1008;
    int t1011;
    float t1012;
    int t1013;
    int t1014;
    unsigned char t9;
    int t1015;
    float t1018;
    float t1019;
    float t1020;
    float t1021;
    t1000 = (int)((int)(a8));
    t1 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1000) + 16) & (unsigned char)48);
    if (t1 != (unsigned char)0) {
        t1001 = (int)(*(int*)((char*)(t1000)));
    } else {
        t1002 = (int)(*(unsigned short*)((char*)(t1000) + 18));
        t1001 = (int)(((int)(t1002) != (int)((int)0)) ? (int)(t1000) : (int)((int)0));
    }
    t1005 = (int)((int)(a12));
    t1006 = (int)(*(unsigned short*)((char*)(t1005) + 18));
    if ((unsigned short)(t1006) != (unsigned short)13) {
        if ((unsigned short)(t1006) != (unsigned short)16) {
            t1007 = (int)((int)g_015d1168);
            goto Le32106;
        }
    }
    t5 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1005) + 16) & (unsigned char)48);
    if (t5 != (unsigned char)0) {
        t1007 = (int)(*(int*)((char*)(t1005)));
        goto Le32106;
    }
    t1008 = (int)((unsigned short)(t1006));
    t1007 = (int)(((int)(t1008) != (int)((int)0)) ? (int)(t1005) : (int)((int)0));
    Le32106:;
    t1011 = (int)((int)(a16));
    t1012 = (float)(*(float*)((char*)(t1007)));
    t1013 = (int)(*(unsigned short*)((char*)(t1011) + 18));
    if ((unsigned short)(t1013) != (unsigned short)13) {
        if ((unsigned short)(t1013) != (unsigned short)16) {
            t1014 = (int)((int)g_015d1168);
            goto Le32138;
        }
    }
    t9 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1011) + 16) & (unsigned char)48);
    if (t9 != (unsigned char)0) {
        t1014 = (int)(*(int*)((char*)(t1011)));
        goto Le32138;
    }
    t1015 = (int)((unsigned short)(t1013));
    t1014 = (int)(((int)(t1015) != (int)((int)0)) ? (int)(t1011) : (int)((int)0));
    Le32138:;
    t1018 = (float)(*(float*)((char*)(t1014)));
    t1019 = (float)(t1018 - t1012);
    t1020 = (float)(t1019 * (float)(a20));
    t1021 = (float)(t1020 + t1012);
    *(float*)((char*)(t1001) + 148) = (float)(t1021);
    return (int)(t1014);
}
