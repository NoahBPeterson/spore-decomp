// 0x006abe50: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s006ab3d0/s006ab3d0.cpp.

extern "C" unsigned char g_013ebb38[];
extern "C" unsigned char g_013ebc58[];
struct C_00926650 { int FUN_00926650(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f473a0(...);

// @ 0x006abe50
extern "C" int __fastcall FUN_006abe50(char* self, int edx_unused, int a4, int a8)
{
    int t1000;
    int t1003;
    int t1004;
    int t1005;
    int t1008;
    int t1010;
    int t1011;
    int t1013;
    int t1014;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    if ((unsigned int)(t1000) <= (unsigned int)20) {
        L6abe60:;
        if ((int)*(int*)((char*)(t1003) + 16) == (int)0) {
            t1004 = (int)(t1003);
            t1005 = (int)((C_00926650*)(t1004))->FUN_00926650((unsigned int)((int)0), (unsigned int)((int)0));
            if ((unsigned char)(t1005) != (unsigned char)0) goto L6abe60;
            t1008 = (int)((int)0);
            return (int)(t1008);
        }
        t1010 = (int)(*(int*)((char*)(t1003) + 16));
        t1011 = (int)(*(int*)((char*)(t1010)));
        *(int*)((char*)(t1003) + 16) = (int)(t1011);
        return (int)(t1010);
    }
    t1013 = (int)((int)(a8));
    t1014 = (int)FUN_00f473a0((unsigned int)(t1000), (unsigned int)((int)g_013ebc58), (unsigned int)(t1013), (unsigned int)((int)0), (unsigned int)((int)g_013ebb38), (unsigned int)((int)209));
    return (int)(t1014);
}
