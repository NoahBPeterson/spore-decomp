// 0x0068cd40: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPID.cpp, match/slices/s0068c330/s0068c330.cpp.

#include <string.h>
struct C_0068c9e0 { void FUN_0068c9e0(unsigned int, unsigned int, unsigned int); };

// @ 0x0068cd40
extern "C" int __fastcall FUN_0068cd40(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1002;
    int t1005;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1017;
    t1000 = (int)((int)(a8));
    t1002 = (int)(t1000);
    t1005 = (int)((int)(self));
    t1008 = (int)strlen((const char*)(t1002));
    t1009 = (int)(t1008 + t1000);
    t1010 = (int)(*(int*)((char*)(t1005)));
    t1011 = (int)(t1010 + (int)(a4));
    t1012 = (int)(t1005);
    ((C_0068c9e0*)(t1012))->FUN_0068c9e0((unsigned int)(t1011), (unsigned int)(t1000), (unsigned int)(t1009));
    t1017 = (int)(t1005);
    return (int)(t1017);
}
