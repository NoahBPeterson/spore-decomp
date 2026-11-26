// 0x010888c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s010878b0/s010878b0.cpp.

struct C_01088410 { void FUN_01088410(unsigned int); };
struct C_01088480 { void FUN_01088480(unsigned int); };

// @ 0x010888c0
extern "C" int __fastcall FUN_010888c0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    unsigned short t1020;
    unsigned short t1021;
    int t1023;
    t1002 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    ((C_01088410*)((int)(self)))->FUN_01088410((unsigned int)(t1002));
    t1008 = (int)(t1002 + (int)64);
    t1009 = (int)(t1004 + (int)64);
    ((C_01088480*)(t1009))->FUN_01088480((unsigned int)(t1008));
    t1013 = (int)(*(int*)((char*)(t1002) + 144));
    *(int*)((char*)(t1004) + 144) = (int)(t1013);
    t1014 = (int)(*(int*)((char*)(t1002) + 148));
    *(int*)((char*)(t1004) + 148) = (int)(t1014);
    t1015 = (int)(*(int*)((char*)(t1002) + 152));
    *(int*)((char*)(t1004) + 152) = (int)(t1015);
    t1016 = (int)(*(int*)((char*)(t1002) + 156));
    *(int*)((char*)(t1004) + 156) = (int)(t1016);
    t1017 = (int)(*(int*)((char*)(t1002) + 160));
    *(int*)((char*)(t1004) + 160) = (int)(t1017);
    t1018 = (int)(*(int*)((char*)(t1002) + 164));
    *(int*)((char*)(t1004) + 164) = (int)(t1018);
    t1019 = (int)(*(int*)((char*)(t1002) + 168));
    *(int*)((char*)(t1004) + 168) = (int)(t1019);
    t1020 = (unsigned short)(*(unsigned short*)((char*)(t1002) + 172));
    *(unsigned short*)((char*)(t1004) + 172) = (unsigned short)(t1020);
    t1021 = (unsigned short)(*(unsigned short*)((char*)(t1002) + 174));
    *(unsigned short*)((char*)(t1004) + 174) = (unsigned short)(t1021);
    t1023 = (int)(t1004);
    return (int)(t1023);
}
