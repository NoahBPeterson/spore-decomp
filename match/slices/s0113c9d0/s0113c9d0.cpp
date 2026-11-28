// 0x0113c9d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0113baf0/s0113baf0.cpp.

extern "C" unsigned char g_01485720[];
extern "C" unsigned char g_014c13b8[];

// @ 0x0113c9d0
extern "C" bool __cdecl FUN_0113c9d0(int a4)
{
    int t1000;
    int t1001;
    float t1002;
    int t1003;
    bool t1004;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)0);
    if (t1000 != t1001) {
        *(int*)((char*)(t1000)) = (int)((int)g_014c13b8);
    }
    t1002 = (float)((float)(*(float*)g_01485720));
    t1003 = (int)(t1000 + (int)40);
    *(int*)((char*)(t1000) + 12) = (int)(t1003);
    *(unsigned char*)((char*)(t1000) + 104) = (unsigned char)((unsigned char)(t1001));
    *(unsigned char*)((char*)(t1000) + 105) = (unsigned char)((unsigned char)(t1001));
    *(float*)((char*)(t1000) + 100) = (float)(t1002);
    *(float*)((char*)(t1003)) = (float)(t1002);
    t1004 = true;
    return (bool)(t1004);
}
