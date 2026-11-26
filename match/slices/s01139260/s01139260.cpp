// 0x01139260: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/plugins/_at_01130000.cpp, match/slices/s011388f0/s011388f0.cpp.

// lifted by il2c_lift + l2c_search (ref@t1000); CI scorer MATCH; corpus status nonmatching/residual
extern "C" unsigned char g_01485720[];
extern "C" unsigned char g_014b0e5c[];

// @ 0x01139260
extern "C" bool __cdecl FUN_01139260(int a4)
{
    int t1000;
    int t1001;
    float t1002;
    float t1003;
    int t1004;
    bool t1005;
    t1000 = (int)((int)(a4));
    int& t1000_r = t1000;
    t1001 = (int)((int)0);
    if (t1000_r != t1001) {
        *(int*)((char*)(t1000_r)) = (int)((int)g_014b0e5c);
        *(int*)((char*)(t1000_r) + 56) = (int)(t1001);
        *(int*)((char*)(t1000_r) + 60) = (int)(t1001);
        *(unsigned char*)((char*)(t1000_r) + 64) = (unsigned char)((unsigned char)(t1001));
    }
    t1002 = (float)((float)(*(float*)g_01485720));
    *(float*)((char*)(t1000_r) + 92) = (float)(t1002);
    *(float*)((char*)(t1000_r) + 40) = (float)(t1002);
    t1003 = (float)((float)0);
    *(unsigned char*)((char*)(t1000_r) + 96) = (unsigned char)((unsigned char)(t1001));
    t1004 = (int)(t1000_r + (int)40);
    *(int*)((char*)(t1000_r) + 12) = (int)(t1004);
    *(float*)((char*)(t1000_r) + 68) = (float)(t1003);
    *(float*)((char*)(t1000_r) + 72) = (float)(t1003);
    *(float*)((char*)(t1000_r) + 76) = (float)(t1003);
    *(float*)((char*)(t1000_r) + 80) = (float)(t1003);
    *(float*)((char*)(t1000_r) + 84) = (float)(t1003);
    *(float*)((char*)(t1000_r) + 88) = (float)(t1003);
    t1005 = true;
    return (bool)(t1005);
}
