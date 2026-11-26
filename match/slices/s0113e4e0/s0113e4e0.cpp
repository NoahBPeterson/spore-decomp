// 0x0113e4e0: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0113dc00/s0113dc00.cpp.

// lifted by il2c_lift + l2c_search (ref@t1001); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_013f1f04[];
extern "C" unsigned char g_01485720[];
extern "C" unsigned char g_014bc0fc[];
extern "C" unsigned char g_014c8a98[];
extern "C" unsigned char g_014c8a9c[];
struct C_01153b00 { void FUN_01153b00(); };

// @ 0x0113e4e0
extern "C" bool __cdecl FUN_0113e4e0(int a4)
{
    int t1001;
    int t1002;
    float t1006;
    float t1007;
    int t1008;
    float t1009;
    float t1010;
    float t1011;
    float t1012;
    float t1013;
    bool t1014;
    t1001 = (int)((int)(a4));
    int& t1001_r = t1001;
    if (t1001_r != (int)0) {
        t1002 = (int)(t1001_r + (int)80);
        *(int*)((char*)(t1001_r)) = (int)((int)g_014bc0fc);
        ((C_01153b00*)(t1002))->FUN_01153b00();
    }
    t1006 = (float)((float)(*(float*)g_01485720));
    t1007 = (float)((float)(*(float*)g_013f1f04));
    t1008 = (int)(t1001_r + (int)40);
    *(int*)((char*)(t1001_r) + 12) = (int)(t1008);
    *(float*)((char*)(t1001_r) + 48) = (float)(t1006);
    *(float*)((char*)(t1008)) = (float)(t1007);
    t1009 = (float)((float)(*(float*)g_014c8a98));
    *(float*)((char*)(t1001_r) + 56) = (float)(t1009);
    t1010 = (float)((float)(*(float*)g_014c8a9c));
    *(float*)((char*)(t1001_r) + 72) = (float)(t1006);
    *(float*)((char*)(t1001_r) + 164) = (float)(t1006);
    *(float*)((char*)(t1001_r) + 64) = (float)(t1010);
    *(float*)((char*)(t1001_r) + 160) = (float)(t1007);
    t1011 = (float)((float)(*(float*)g_014c8a98));
    *(float*)((char*)(t1001_r) + 168) = (float)(t1011);
    t1012 = (float)((float)(*(float*)g_014c8a9c));
    *(float*)((char*)(t1001_r) + 176) = (float)(t1006);
    t1013 = (float)((float)0);
    *(float*)((char*)(t1001_r) + 172) = (float)(t1012);
    *(float*)((char*)(t1001_r) + 180) = (float)(t1013);
    *(int*)((char*)(t1001_r) + 184) = (int)((int)0);
    t1014 = true;
    return (bool)(t1014);
}
