// 0x0113c550: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0113baf0/s0113baf0.cpp.

extern "C" unsigned char g_013f1f04[];
extern "C" unsigned char g_01485720[];
extern "C" unsigned char g_014bc0fc[];
extern "C" unsigned char g_014bedec[];
struct C_01153b00 { void FUN_01153b00(); };

// @ 0x0113c550
extern "C" bool __cdecl FUN_0113c550(int a4)
{
    int t1001;
    int t1002;
    float t1006;
    int t1007;
    float t1008;
    float t1009;
    float t1010;
    float t1011;
    bool t1012;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t1002 = (int)(t1001 + (int)64);
        *(int*)((char*)(t1001)) = (int)((int)g_014bc0fc);
        ((C_01153b00*)(t1002))->FUN_01153b00();
    }
    t1006 = (float)((float)(*(float*)g_013f1f04));
    t1007 = (int)(t1001 + (int)40);
    *(int*)((char*)(t1001) + 12) = (int)(t1007);
    *(float*)((char*)(t1007)) = (float)(t1006);
    t1008 = (float)((float)(*(float*)g_014bedec));
    *(float*)((char*)(t1001) + 48) = (float)(t1008);
    t1009 = (float)((float)(*(float*)g_01485720));
    *(float*)((char*)(t1001) + 144) = (float)(t1006);
    *(float*)((char*)(t1001) + 56) = (float)(t1009);
    t1010 = (float)((float)(*(float*)g_014bedec));
    *(float*)((char*)(t1001) + 148) = (float)(t1010);
    t1011 = (float)((float)0);
    *(float*)((char*)(t1001) + 152) = (float)(t1009);
    *(float*)((char*)(t1001) + 156) = (float)(t1011);
    *(int*)((char*)(t1001) + 160) = (int)((int)0);
    t1012 = true;
    return (bool)(t1012);
}
