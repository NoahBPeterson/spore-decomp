// 0x00ff8100: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00ff7530/s00ff7530.cpp.

struct il2c_vc0 {
    virtual void s0();
};

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f09b4[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00ff8100
extern "C" int __fastcall FUN_00ff8100(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1012;
    int t1013;
    int t1021;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 8));
    if (t1001 != (int)0) {
        t1004 = (int)(t1001);
        t1005 = (int)(*(int*)((char*)(t1001)));
        *(int*)((char*)((int)(self)) + 8) = (int)(t1005);
    } else {
        t1006 = (int)(*(int*)((char*)((int)(self)) + 24));
        t1009 = (int)FUN_00f473a0((unsigned int)(t1006), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
        t1004 = (int)(t1009);
    }
    t1010 = (int)(t1004 + (int)8);
    if (t1010 != (int)0) {
        t1012 = (int)((int)(a4));
        t1013 = (int)(*(int*)((char*)(t1012)));
        *(int*)((char*)(t1010)) = (int)(t1013);
        if (t1013 != (int)0) {
            ((il2c_vc0*)(t1013))->s0();
        }
        *(float*)((char*)(t1010) + 4) = (float)(*(float*)((char*)(t1012) + 4));
        *(float*)((char*)(t1010) + 8) = (float)(*(float*)((char*)(t1012) + 8));
        *(float*)((char*)(t1010) + 12) = (float)(*(float*)((char*)(t1012) + 12));
    }
    t1021 = (int)(t1004);
    return (int)(t1021);
}
