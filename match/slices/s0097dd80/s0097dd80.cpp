// 0x0097dd80: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/ImageCursorProvider.cpp, match/slices/s0097cea0/s0097cea0.cpp.

struct il2c_vc0 {
    virtual void s0();
};

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f2150[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x0097dd80
extern "C" int __fastcall FUN_0097dd80(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1018;
    t1002 = (int)(*(int*)((char*)((int)(self)) + 28));
    if (t1002 != (int)0) {
        t1003 = (int)(*(int*)((char*)(t1002)));
        *(int*)((char*)((int)(self)) + 28) = (int)(t1003);
    } else {
        t1004 = (int)(*(int*)((char*)((int)(self)) + 44));
        t1007 = (int)FUN_00f473a0((unsigned int)(t1004), (unsigned int)((int)g_013f2150), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
        t1002 = (int)(t1007);
    }
    if (t1002 != (int)0) {
        t1008 = (int)((int)(a4));
        t1009 = (int)(*(int*)((char*)(t1008)));
        *(int*)((char*)(t1002)) = (int)(t1009);
        t1010 = (int)(*(int*)((char*)(t1008) + 4));
        *(int*)((char*)(t1002) + 4) = (int)(t1010);
        t1011 = (int)(*(int*)((char*)(t1008) + 8));
        *(int*)((char*)(t1002) + 8) = (int)(t1011);
        t1012 = (int)(*(int*)((char*)(t1008) + 12));
        *(int*)((char*)(t1002) + 12) = (int)(t1012);
        if (t1012 != (int)0) {
            ((il2c_vc0*)(t1012))->s0();
        }
    }
    *(int*)((char*)(t1002) + 16) = (int)((int)0);
    t1018 = (int)(t1002);
    return (int)(t1018);
}
