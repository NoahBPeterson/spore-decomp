// 0x00922900: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00922500/s00922500.cpp.

extern "C" unsigned char g_013ec47c[];

// @ 0x00922900
extern "C" int __fastcall FUN_00922900(char* self, int edx_unused)
{
    int t1001;
    int t1002;
    t1001 = (int)((int)(self));
    t1002 = (int)((int)0);
    *(int*)((char*)(t1001)) = (int)(t1002);
    *(int*)((char*)(t1001) + 4) = (int)(t1002);
    *(int*)((char*)(t1001) + 8) = (int)(t1002);
    *(int*)((char*)(t1001) + 12) = (int)((int)(-1));
    *(unsigned char*)((char*)(t1001) + 16) = (unsigned char)((unsigned char)(t1002));
    *(int*)((char*)(t1001) + 20) = (int)((int)g_013ec47c);
    return (int)(t1001);
}
