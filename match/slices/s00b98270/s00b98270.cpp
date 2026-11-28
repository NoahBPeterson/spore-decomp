// 0x00b98270: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00b981a0/s00b981a0.cpp, src/game/SPGonzago/_at_00b90000.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f09b4[];
extern "C" int __cdecl FUN_00f473a0(...);
struct C_01011cc0 { void FUN_01011cc0(unsigned int); };

// @ 0x00b98270
extern "C" int __fastcall FUN_00b98270(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1018;
    t1002 = (int)(*(int*)((char*)((int)(self)) + 28));
    if (t1002 != (int)0) {
        t1003 = (int)(*(int*)((char*)(t1002)));
        *(int*)((char*)((int)(self)) + 28) = (int)(t1003);
    } else {
        t1004 = (int)(*(int*)((char*)((int)(self)) + 44));
        t1005 = (int)FUN_00f473a0((unsigned int)(t1004), (unsigned int)((int)g_013f09b4), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
        t1002 = (int)(t1005);
    }
    if (t1002 != (int)0) {
        t1008 = (int)((int)(a4));
        t1009 = (int)(*(int*)((char*)(t1008)));
        *(int*)((char*)(t1002)) = (int)(t1009);
        t1010 = (int)(*(int*)((char*)(t1008) + 4));
        *(int*)((char*)(t1002) + 4) = (int)(t1010);
        t1011 = (int)(t1002 + (int)8);
        t1012 = (int)(t1011 + (int)24);
        *(int*)((char*)(t1011)) = (int)(t1012);
        *(int*)((char*)(t1011) + 4) = (int)(t1012);
        t1013 = (int)(t1008 + (int)8);
        t1014 = (int)(t1012 + (int)32);
        *(int*)((char*)(t1011) + 20) = (int)((int)0);
        *(int*)((char*)(t1011) + 8) = (int)(t1014);
        ((C_01011cc0*)(t1011))->FUN_01011cc0((unsigned int)(t1013));
    }
    t1018 = (int)(t1002);
    *(int*)((char*)(t1002) + 64) = (int)((int)0);
    return (int)(t1018);
}
