// 0x009245b0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/UTFSpore_Win32/ealog_imp.cpp, match/slices/s009245b0/s009245b0.cpp.

extern "C" unsigned char g_0143de68[];
struct C_009244d0 { int FUN_009244d0(unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x009245b0
extern "C" int __fastcall FUN_009245b0(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    unsigned short t1010;
    int t1011;
    t1002 = (int)((int)(self));
    t1003 = (int)FUN_00f473a0((unsigned int)((int)2648), (unsigned int)((int)g_0143de68), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0), (unsigned int)((int)0));
    if (t1003 != (int)0) {
        t1006 = (int)(*(int*)((char*)(t1002) + 8));
        t1007 = (int)(t1003);
        t1008 = (int)((C_009244d0*)(t1007))->FUN_009244d0((unsigned int)(t1006));
    } else {
        t1008 = (int)((int)0);
    }
    t1010 = (unsigned short)(*(unsigned short*)((char*)(t1002) + 540));
    *(unsigned short*)((char*)(t1008) + 540) = (unsigned short)(t1010);
    t1011 = (int)(*(int*)((char*)(t1002) + 544));
    *(int*)((char*)(t1008) + 544) = (int)(t1011);
    return (int)(t1008);
}
