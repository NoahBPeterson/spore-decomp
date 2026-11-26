// 0x00895370: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00894440/s00894440.cpp.

// lifted by il2c_lift + l2c_search (ref@t1002); CI scorer MATCH; corpus status nonmatching/residual
#include <string.h>
struct C_00942e50 { void FUN_00942e50(unsigned int, unsigned int); };

// @ 0x00895370
extern "C" int __fastcall FUN_00895370(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1010;
    int t1011;
    int t1012;
    int t1017;
    t1002 = (int)((int)(self));
    int& t1002_r = t1002;
    t1003 = (int)(t1002_r + (int)20);
    *(int*)((char*)(t1002_r) + 16) = (int)(t1003);
    t1004 = (int)(t1003 + (int)12);
    *(int*)((char*)(t1002_r) + 8) = (int)(t1004);
    t1005 = (int)((int)(a4));
    *(int*)((char*)(t1002_r) + 4) = (int)(t1003);
    *(int*)((char*)(t1002_r)) = (int)(t1003);
    *(unsigned char*)((char*)(t1003)) = (unsigned char)((int)0);
    t1006 = (int)(t1005);
    t1010 = (int)strlen((const char*)(t1006));
    t1011 = (int)(t1010 + t1005);
    t1012 = (int)(t1002_r);
    ((C_00942e50*)(t1012))->FUN_00942e50((unsigned int)(t1005), (unsigned int)(t1011));
    t1017 = (int)(t1002_r);
    return (int)(t1017);
}
