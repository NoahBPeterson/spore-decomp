// 0x00808ce0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s008087f0/s008087f0.cpp.

extern "C" unsigned char g_013eb938[];
extern "C" unsigned char g_01417b14[];
struct C_00811ad0 { void FUN_00811ad0(unsigned int); };
struct C_00811fe0 { void FUN_00811fe0(); };
extern "C" void __cdecl FUN_00f47380(...);

// @ 0x00808ce0
extern "C" int __fastcall FUN_00808ce0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1005;
    int t1009;
    unsigned char t4;
    int t1017;
    t1002 = (int)((int)(self));
    t1004 = (int)(t1002 + (int)8);
    t1005 = (int)(t1004);
    *(int*)((char*)(t1002)) = (int)((int)g_01417b14);
    ((C_00811ad0*)(t1005))->FUN_00811ad0((unsigned int)((int)1));
    t1009 = (int)(t1004);
    ((C_00811fe0*)(t1009))->FUN_00811fe0();
    t4 = (unsigned char)((unsigned char)(a4) & (unsigned char)1);
    *(int*)((char*)(t1002)) = (int)((int)g_013eb938);
    if (t4 != (unsigned char)0) {
        FUN_00f47380((unsigned int)(t1002));
    }
    t1017 = (int)(t1002);
    return (int)(t1017);
}
