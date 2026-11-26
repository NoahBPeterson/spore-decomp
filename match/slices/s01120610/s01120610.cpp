// 0x01120610: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0111ffc0/s0111ffc0.cpp.

extern "C" unsigned char g_014a6128[];
struct C_01103830 { void FUN_01103830(unsigned int); };

// @ 0x01120610
extern "C" int __fastcall FUN_01120610(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int t1005;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    t1003 = (int)((int)(self));
    t1004 = (int)(t1003 + (int)8);
    t1005 = (int)(t1004);
    *(unsigned short*)((char*)(t1003) + 6) = (unsigned short)((int)1);
    *(int*)((char*)(t1003)) = (int)((int)g_014a6128);
    ((C_01103830*)(t1005))->FUN_01103830((unsigned int)((int)0));
    t1009 = (int)((int)(a4));
    t1010 = (int)(*(int*)((char*)(t1009)));
    *(int*)((char*)(t1004)) = (int)(t1010);
    t1011 = (int)(*(int*)((char*)(t1009) + 4));
    *(int*)((char*)(t1004) + 4) = (int)(t1011);
    t1012 = (int)(*(int*)((char*)(t1009) + 8));
    *(int*)((char*)(t1004) + 8) = (int)(t1012);
    t1013 = (int)(*(int*)((char*)(t1009) + 12));
    *(int*)((char*)(t1004) + 12) = (int)(t1013);
    t1014 = (int)(*(int*)((char*)(t1009) + 16));
    *(int*)((char*)(t1004) + 16) = (int)(t1014);
    t1015 = (int)(*(int*)((char*)(t1009) + 20));
    t1016 = (int)(t1003);
    *(int*)((char*)(t1004) + 20) = (int)(t1015);
    return (int)(t1016);
}
