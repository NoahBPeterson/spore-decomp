// 0x0113c710: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0113baf0/s0113baf0.cpp.

extern "C" unsigned char g_0145464c[];
extern "C" void __cdecl FUN_0113c290(...);

// @ 0x0113c710
extern "C" bool __cdecl FUN_0113c710(int a4)
{
    int t1001;
    float t1007;
    int t1008;
    float t1009;
    float t1010;
    float t1011;
    float t1012;
    bool t1013;
    t1001 = (int)((int)(a4));
    FUN_0113c290((unsigned int)(t1001), (unsigned int)((int)40));
    t1007 = (float)((float)0);
    t1008 = (int)(*(int*)((char*)(t1001) + 8));
    *(float*)((char*)(t1001) + 40) = (float)(t1007);
    *(float*)((char*)(t1001) + 164) = (float)(t1007);
    t1009 = (float)((float)(*(float*)g_0145464c));
    t1010 = (float)(t1009);
    t1011 = (float)(t1010 - (float)*(float*)((char*)(t1001) + 24));
    t1012 = (float)(t1011 + (float)*(float*)((char*)(t1008) + 40));
    *(float*)((char*)(t1008) + 40) = (float)(t1012);
    *(float*)((char*)(t1001) + 24) = (float)(t1009);
    t1013 = true;
    return (bool)(t1013);
}
