// 0x00a86050: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00a85c00/s00a85c00.cpp, src/game/Swarm/_at_00a80000.cpp.

// @ 0x00a86050
extern "C" bool __fastcall FUN_00a86050(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1000;
    bool t1001;
    int t1002;
    bool t1004;
    int t1005;
    float t1006;
    float t1007;
    float t1008;
    float t1009;
    float t1011;
    int t1012;
    float t1013;
    unsigned char t1014;
    unsigned char t4;
    int t1015;
    bool t1016;
    t1000 = (int)((int)(a4));
    if (t1000 != (int)4) {
        if (t1000 != (int)12) {
            if (t1000 != (int)257) {
                t1001 = false;
                return (bool)(t1001);
            }
            t1002 = (int)((int)(a8));
            *(float*)((char*)((int)(self)) + 84) = (float)(*(float*)((char*)(t1002) + 4));
            *(float*)((char*)((int)(self)) + 92) = (float)(*(float*)((char*)(t1002) + 8));
            *(float*)((char*)((int)(self)) + 88) = (float)(*(float*)((char*)(t1002) + 16));
            t1004 = true;
            *(float*)((char*)((int)(self)) + 96) = (float)(*(float*)((char*)(t1002) + 20));
            return (bool)(t1004);
        }
        t1005 = (int)((int)(a8));
        t1006 = (float)(*(float*)((char*)(t1005) + 12));
        t1007 = (float)(*(float*)((char*)(t1005) + 16));
        t1008 = (float)(t1006 - (float)*(float*)((char*)(t1005)));
        t1009 = (float)(t1007 - (float)*(float*)((char*)(t1005) + 4));
        t1011 = (float)((float)0);
        t1012 = (int)(*(int*)((char*)((int)(self)) + 12));
        t1013 = (float)(t1009 / t1008);
        t1014 = (unsigned char)((int)1);
        *(float*)((char*)((int)(self)) + 80) = (float)(t1011);
        *(float*)((char*)((int)(self)) + 116) = (float)(t1013);
        t4 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1012) + 8) & t1014);
        if (t4 != (unsigned char)0) {
            *(float*)((char*)((int)(self)) + 112) = (float)(t1008);
        }
        *(unsigned char*)((char*)((int)(self)) + 124) = (unsigned char)(t1014);
        return (bool)(t1014);
    }
    t1015 = (int)((int)(a8));
    t1016 = true;
    *(float*)((char*)((int)(self)) + 120) = (float)(*(float*)((char*)(t1015)));
    return (bool)(t1016);
}
