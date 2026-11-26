// 0x005dbc70: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005dae60/s005dae60.cpp.

// lifted by il2c_lift + l2c_search (ref@t1003); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_013eb8a0[];
extern "C" unsigned char g_013ec480[];
extern "C" unsigned char g_013fb19c[];
extern "C" unsigned char g_01485720[];

// @ 0x005dbc70
extern "C" int __fastcall FUN_005dbc70(char* self, int edx_unused)
{
    float t1000;
    float t1001;
    int t1003;
    float t1004;
    int t1005;
    t1000 = (float)((float)(*(float*)g_01485720));
    t1001 = (float)((float)(*(float*)g_013eb8a0));
    t1003 = (int)((int)(self));
    int& t1003_r = t1003;
    *(float*)((char*)(t1003_r) + 16) = (float)(t1000);
    *(float*)((char*)(t1003_r) + 20) = (float)(t1000);
    *(float*)((char*)(t1003_r) + 28) = (float)(t1000);
    t1004 = (float)((float)(*(float*)g_013ec480));
    t1005 = (int)((int)0);
    *(int*)((char*)(t1003_r)) = (int)((int)g_013fb19c);
    *(float*)((char*)(t1003_r) + 24) = (float)(t1001);
    *(int*)((char*)(t1003_r) + 96) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 100) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 104) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 108) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 112) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 116) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 120) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 124) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 128) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 132) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 136) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 140) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 144) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 148) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 152) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 156) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 160) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 164) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 168) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 172) = (int)(t1005);
    *(int*)((char*)(t1003_r) + 176) = (int)(t1005);
    *(float*)((char*)(t1003_r) + 180) = (float)(t1004);
    return (int)(t1003_r);
}
