// 0x005f5970: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s005f5080/s005f5080.cpp, src/game/SPEditors/SPSwatchStrategies.cpp.

struct C_005f3680 { int FUN_005f3680(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_005f4e10(...);

// @ 0x005f5970
extern "C" void __fastcall FUN_005f5970(char* self, int edx_unused)
{
    int t1004;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1004)));
    t1006 = (int)(*(int*)((char*)(t1004) + 4));
    t1009 = (int)FUN_005f4e10((unsigned int)(t1006), (unsigned int)(t1006), (unsigned int)(t1005));
    t1010 = (int)(*(int*)((char*)(t1004) + 4));
    t1011 = (int)(t1004);
    ((C_005f3680*)(t1011))->FUN_005f3680((unsigned int)(t1009), (unsigned int)(t1010));
    t1015 = (int)(t1006 - t1005);
    t1016 = (int)(t1015 >> (int)2);
    t1017 = (int)(-t1016);
    t1018 = (int)(t1017 + t1017);
    t1019 = (int)(t1018 + t1018);
    *(int*)((char*)(t1004) + 4) += t1019;
    return;
}
