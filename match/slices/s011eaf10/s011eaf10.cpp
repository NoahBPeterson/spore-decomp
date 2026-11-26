// 0x011eaf10: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s011ea070/s011ea070_g7.cpp.

struct C_011eae90 { void FUN_011eae90(unsigned int); };

// @ 0x011eaf10
extern "C" int __fastcall FUN_011eaf10(char* self, int edx_unused, int a4)
{
    int t1003;
    int t1004;
    int t1005;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1003)));
    t1005 = (int)((int)0);
    if ((unsigned short)*(unsigned short*)((char*)(t1004) + 16) > (unsigned short)(t1005)) {
        t1007 = (int)((int)(a4));
        do {
            t1008 = (int)(*(int*)((char*)(t1004) + 8));
            t1009 = (int)((unsigned short)(t1005));
            t1010 = (int)(*(int*)((char*)(t1008) + (t1009)*4));
            if (t1010 != (int)(-1)) {
                t1011 = (int)(*(int*)((char*)(t1004)));
                t1012 = (int)(t1011 + t1010);
                t1013 = (int)(t1007);
                ((C_011eae90*)(t1013))->FUN_011eae90((unsigned int)(t1012));
            }
            t1004 = (int)(*(int*)((char*)(t1003)));
            t1005 = (int)(t1005 + (int)1);
        } while ((unsigned short)(t1005) < (unsigned short)*(unsigned short*)((char*)(t1004) + 16));
    }
    return (int)(t1004);
}
