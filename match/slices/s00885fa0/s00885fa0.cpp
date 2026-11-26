// 0x00885fa0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00885ad0/s00885ad0.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013f2150[];
extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bad[];
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x00885fa0
extern "C" void __fastcall FUN_00885fa0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1007;
    int t1008;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if ((unsigned int)(t1002) > (unsigned int)1) {
        t1007 = (int)FUN_00f473a0((unsigned int)(t1002), (unsigned int)((int)g_013f2150), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
        *(int*)((char*)(t1004)) = (int)(t1007);
        *(int*)((char*)(t1004) + 4) = (int)(t1007);
        t1008 = (int)(t1007 + t1002);
        *(int*)((char*)(t1004) + 8) = (int)(t1008);
        return;
    }
    *(int*)((char*)(t1004)) = (int)((int)g_01667bac);
    *(int*)((char*)(t1004) + 4) = (int)((int)g_01667bac);
    *(int*)((char*)(t1004) + 8) = (int)((int)g_01667bad);
    return;
}
