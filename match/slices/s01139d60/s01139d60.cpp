// 0x01139d60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011399e0/s011399e0.cpp, src/game/plugins/reverbmodel1.cpp.cpp.

extern "C" unsigned char g_01485720[];
extern "C" unsigned char g_014b3dd0[];

// @ 0x01139d60
extern "C" int __fastcall FUN_01139d60(char* self, int edx_unused, int a4)
{
    float t1000;
    float t1002;
    float t1003;
    int t1004;
    float t1005;
    float t1006;
    float t1007;
    float t1008;
    float t1009;
    float t1010;
    float t1011;
    float t1012;
    float t1013;
    float t1014;
    float t1015;
    float t1016;
    float t1017;
    float t1018;
    float t1019;
    float t1020;
    float t1021;
    float t1022;
    float t1023;
    int t1024;
    t1000 = (float)((float)(*(float*)g_014b3dd0));
    if (t1000 > (float)*(float*)((char*)((int)(self)) + 40)) {
        *(float*)((char*)((int)(self)) + 40) = (float)(t1000);
    }
    t1002 = (float)(t1000 / (float)*(float*)((char*)((int)(self)) + 40));
    t1003 = (float)((float)(*(float*)g_01485720));
    t1004 = (int)((int)(a4));
    t1005 = (float)(t1003);
    t1006 = (float)(t1005 - t1002);
    t1007 = (float)(t1003);
    t1008 = (float)(t1007 - (float)*(float*)((char*)((int)(self)) + 428));
    t1009 = (float)(t1008 * t1006);
    *(float*)((char*)(t1004)) = (float)(t1009);
    t1010 = (float)(t1003);
    t1011 = (float)(t1010 - (float)*(float*)((char*)((int)(self)) + 432));
    t1012 = (float)(t1011 * t1006);
    *(float*)((char*)(t1004) + 4) = (float)(t1012);
    t1013 = (float)(t1003);
    t1014 = (float)(t1013 - (float)*(float*)((char*)((int)(self)) + 436));
    t1015 = (float)(t1014 * t1006);
    *(float*)((char*)(t1004) + 8) = (float)(t1015);
    t1016 = (float)(t1003);
    t1017 = (float)(t1016 - (float)*(float*)((char*)((int)(self)) + 440));
    t1018 = (float)(t1017 * t1006);
    *(float*)((char*)(t1004) + 12) = (float)(t1018);
    t1019 = (float)(t1003);
    t1020 = (float)(t1019 - (float)*(float*)((char*)((int)(self)) + 444));
    t1021 = (float)(t1020 * t1006);
    *(float*)((char*)(t1004) + 16) = (float)(t1021);
    t1022 = (float)(t1003 - (float)*(float*)((char*)((int)(self)) + 448));
    t1023 = (float)(t1022 * t1006);
    *(float*)((char*)(t1004) + 20) = (float)(t1023);
    t1024 = (int)((int)1);
    return (int)(t1024);
}
