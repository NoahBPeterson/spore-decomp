// 0x0111d3c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s0111c7f0/s0111c7f0.cpp.

#include <string.h>
struct C_0111cdb0 { void FUN_0111cdb0(unsigned int); };
struct C_0111d2b0 { void FUN_0111d2b0(unsigned int, unsigned int); };
struct C_0111d340 { void FUN_0111d340(); };

// @ 0x0111d3c0
extern "C" int __fastcall FUN_0111d3c0(char* self, int edx_unused, int a4, int a8, int a12)
{
    int t1002;
    int t1005;
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    int t1018;
    int t1019;
    int t1023;
    int t1024;
    int t1025;
    int t1032;
    t1002 = (int)((int)(a4));
    t1005 = (int)((int)(self));
    t1008 = (int)(t1002);
    t1009 = (int)(t1005);
    memcpy((void*)(t1009), (const void*)(t1008), (unsigned int)((int)72));
    t1013 = (int)((int)(a8));
    t1014 = (int)(t1005);
    ((C_0111cdb0*)(t1014))->FUN_0111cdb0((unsigned int)(t1013));
    t1018 = (int)((int)(a12));
    t1019 = (int)(t1005);
    ((C_0111d2b0*)(t1019))->FUN_0111d2b0((unsigned int)(t1013), (unsigned int)(t1018));
    t1023 = (int)(*(int*)((char*)(t1002)));
    t1024 = (int)(t1023 + (int)1);
    *(int*)((char*)(t1005)) = (int)(t1024);
    t1025 = (int)(t1005);
    *(unsigned char*)((char*)(t1005) + 4) = (unsigned char)((int)0);
    ((C_0111d340*)(t1025))->FUN_0111d340();
    t1032 = (int)(t1005);
    return (int)(t1032);
}
