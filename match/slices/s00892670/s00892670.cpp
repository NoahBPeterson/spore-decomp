// 0x00892670: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct C_00925cb0 { int FUN_00925cb0(); };
extern "C" int __cdecl FUN_00925cb0(...);

// @ 0x00892670
extern "C" int __fastcall FUN_00892670(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1004;
    int t1008;
    int t1009;
    int t1012;
    int t1014;
    t1002 = (int)((int)(self));
    t1003 = (int)((int)0);
    t1004 = (int)((int)0);
    *(unsigned short*)((char*)(t1002)) = (unsigned short)((unsigned short)(t1003));
    *(unsigned short*)((char*)(t1002) + 2) = (unsigned short)((unsigned short)(t1004));
    t1008 = (int)((C_00925cb0*)(t1004))->FUN_00925cb0();
    t1009 = (int)((int)0);
    *(int*)((char*)(t1002) + 4) = (int)(t1009);
    *(int*)((char*)(t1002) + 8) = (int)(t1009);
    *(int*)((char*)(t1002) + 12) = (int)(t1009);
    *(int*)((char*)(t1002) + 16) = (int)(t1008);
    *(int*)((char*)(t1002) + 20) = (int)(t1009);
    t1012 = (int)FUN_00925cb0();
    *(int*)((char*)(t1002) + 24) = (int)(t1009);
    *(int*)((char*)(t1002) + 28) = (int)(t1009);
    *(int*)((char*)(t1002) + 32) = (int)(t1009);
    *(int*)((char*)(t1002) + 40) = (int)(t1009);
    *(int*)((char*)(t1002) + 36) = (int)(t1012);
    t1014 = (int)(t1002);
    return (int)(t1014);
}
