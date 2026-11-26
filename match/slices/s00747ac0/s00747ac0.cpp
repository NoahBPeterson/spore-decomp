// 0x00747ac0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPGraphicsModelManager.cpp, match/slices/s00747920/s00747920.cpp.

struct C_0041cb40 { void FUN_0041cb40(unsigned int); };

// @ 0x00747ac0
extern "C" int __fastcall FUN_00747ac0(char* self, int edx_unused, int a4)
{
    int t1000;
    int t1003;
    int t1004;
    unsigned short t1006;
    unsigned short t1007;
    int t1008;
    int t1009;
    int t1013;
    t1000 = (int)((int)(a4));
    t1003 = (int)((int)(self));
    t1004 = (int)(*(int*)((char*)(t1000)));
    *(int*)((char*)(t1003)) = (int)(t1004);
    t1006 = (unsigned short)(*(unsigned short*)((char*)(t1000) + 4));
    *(unsigned short*)((char*)(t1003) + 4) = (unsigned short)(t1006);
    t1007 = (unsigned short)(*(unsigned short*)((char*)(t1000) + 6));
    *(unsigned short*)((char*)(t1003) + 6) = (unsigned short)(t1007);
    *(float*)((char*)(t1003) + 8) = (float)(*(float*)((char*)(t1000) + 8));
    t1008 = (int)(t1000 + (int)24);
    *(float*)((char*)(t1003) + 12) = (float)(*(float*)((char*)(t1008) - 12));
    t1009 = (int)(t1003 + (int)24);
    *(float*)((char*)(t1003) + 16) = (float)(*(float*)((char*)(t1008) - 8));
    *(float*)((char*)(t1003) + 20) = (float)(*(float*)((char*)(t1008) - 4));
    ((C_0041cb40*)(t1009))->FUN_0041cb40((unsigned int)(t1008));
    t1013 = (int)(t1003);
    return (int)(t1013);
}
