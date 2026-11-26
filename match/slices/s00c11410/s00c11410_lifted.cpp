// 0x00c11410: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c11410/s00c11410.cpp.

extern "C" unsigned char g_01485548[];
extern "C" unsigned char g_01485720[];
struct C_00c0d050 { int FUN_00c0d050(float); };

// @ 0x00c11410
extern "C" int __fastcall FUN_00c11410(char* self, int edx_unused, float a4, int a8)
{
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    unsigned char t3;
    unsigned char t5;
    float t1010;
    float t1011;
    float t1013;
    float t1014;
    t1002 = (int)((int)(self));
    t1003 = (int)(t1002 + (int)(-192));
    t1006 = (int)((C_00c0d050*)(t1003))->FUN_00c0d050((float)((float)(a4)));
    *(int*)((char*)(t1002) + 3800) = (int)(t1006);
    t1007 = (int)(*(int*)((char*)(t1002) + 2712));
    t1008 = (int)(t1007);
    t1009 = (int)((unsigned int)(t1008) >> (int)9);
    t3 = (unsigned char)((unsigned char)(t1009) & (unsigned char)1);
    if (t3 == (unsigned char)0) {
        t1007 = (int)((unsigned int)(t1007) >> (int)8);
        t5 = (unsigned char)((unsigned char)(t1007) & (unsigned char)1);
        if (t5 == (unsigned char)0) {
            t1010 = (float)((float)(*(float*)g_01485720));
            t1011 = (float)(t1010 * (float)(a4));
            *(float*)((char*)(t1002) + 480) = (float)(t1011);
            return (int)(t1007);
        }
    }
    t1013 = (float)((float)(*(float*)g_01485548));
    t1014 = (float)(t1013 * (float)(a4));
    *(float*)((char*)(t1002) + 480) = (float)(t1014);
    return (int)(t1007);
}
