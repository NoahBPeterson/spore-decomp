// 0x00f974d0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00f96840/s00f96840.cpp.

extern "C" unsigned char g_016c9e8c[];
extern "C" unsigned char g_016c9e90[];
extern "C" unsigned char g_016c9e94[];
extern "C" void __cdecl FUN_00f8e6c0(unsigned int, float, float, unsigned int, unsigned int, unsigned int);

// @ 0x00f974d0
extern "C" int __fastcall FUN_00f974d0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1001;
    float t1002;
    int t1003;
    int t1004;
    int t1006;
    float t1007;
    float t1008;
    int t1009;
    int t1013;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 44));
    t1002 = (float)((float)(*(float*)g_016c9e8c));
    t1003 = (int)((int)(a12));
    t1004 = (int)((int)(a8));
    t1006 = (int)((int)(a4));
    *(float*)((char*)(t1006)) = (float)(t1002);
    t1007 = (float)((float)(*(float*)g_016c9e90));
    *(float*)((char*)(t1006) + 4) = (float)(t1007);
    t1008 = (float)((float)(*(float*)g_016c9e94));
    *(float*)((char*)(t1006) + 8) = (float)(t1008);
    t1009 = (int)(*(int*)((char*)(t1001) + 8));
    FUN_00f8e6c0((unsigned int)(t1009), (float)(*(float*)((char*)(t1001) + 52)), (float)(*(float*)((char*)(t1001) + 56)), (unsigned int)(t1004), (unsigned int)(t1003), (unsigned int)(t1006));
    t1013 = (int)(t1006);
    return (int)(t1013);
}
