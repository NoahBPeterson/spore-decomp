// 0x01120710: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0111ffc0/s0111ffc0.cpp.

extern "C" unsigned char g_01486110[];
struct C_01120470 { double FUN_01120470(unsigned int); };
struct C_011204d0 { double FUN_011204d0(unsigned int); };
struct C_01120570 { double FUN_01120570(unsigned int); };

// @ 0x01120710
extern "C" int __fastcall FUN_01120710(char* self, int edx_unused, int a4, int a8)
{
    int t1002;
    int t1005;
    double t3;
    int t1009;
    int t1010;
    double t6;
    int t1014;
    double t9;
    int t1018;
    int t1019;
    t1002 = (int)((int)(a4));
    t1005 = (int)((int)(self));
    t3 = (double)((C_011204d0*)((int)(self)))->FUN_011204d0((unsigned int)(t1002));
    t1009 = (int)((int)(a8));
    *(float*)((char*)(t1009) + 4) = (float)(t3);
    t1010 = (int)(t1005);
    t6 = (double)((C_01120570*)(t1010))->FUN_01120570((unsigned int)(t1002));
    *(float*)((char*)(t1009) + 12) = (float)(t6);
    t1014 = (int)(t1005);
    t9 = (double)((C_01120470*)(t1014))->FUN_01120470((unsigned int)(t1002));
    *(float*)((char*)(t1009) + 16) = (float)(t9);
    *(float*)((char*)(t1009)) = (float)(((((*(int*)((char*)(t1002) + 48)) * (float)*(float*)((char*)(t1002) + 28)) * (float)*(float*)((char*)(t1005) + 8)) * (float)(*(float*)g_01486110)));
    *(float*)((char*)(t1009) + 20) = (float)(((((float)*(float*)((char*)(t1002) + 56) - (float)*(float*)((char*)(t1002) + 32)) * (float)*(float*)((char*)(t1002) + 16)) * (float)*(float*)((char*)(t1005) + 12)));
    t1018 = (int)(*(int*)((char*)(t1002) + 8));
    *(int*)((char*)(t1009) + 24) = (int)(t1018);
    t1019 = (int)(*(int*)((char*)(t1002) + 12));
    *(int*)((char*)(t1009) + 28) = (int)(t1019);
    return (int)(t1018);
}
