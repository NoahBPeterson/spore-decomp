// 0x007646c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

struct C_00763770 { int FUN_00763770(unsigned int, unsigned int, unsigned int); };

// @ 0x007646c0
extern "C" void __fastcall FUN_007646c0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1009;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 20));
    t1004 = (int)(*(int*)((char*)(t1002) + 40));
    t1005 = (int)(*(int*)((char*)(t1002) + 12));
    t1006 = (int)(t1002 + (int)44);
    t1009 = (int)((C_00763770*)(t1005))->FUN_00763770((unsigned int)(t1006), (unsigned int)(t1004), (unsigned int)(t1003));
    if ((unsigned char)(t1009) != (unsigned char)0) {
        *(unsigned char*)((char*)(t1002) + 820) = (unsigned char)((int)1);
    }
    return;
}
