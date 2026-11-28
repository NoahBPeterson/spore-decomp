// 0x009c7ff0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPCreatureAnim/creature_mesh_spore.cpp, match/slices/s009c7ff0/s009c7ff0.cpp.

struct C_009c67e0 { void FUN_009c67e0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_009c6860(...);
struct C_009c6c30 { void FUN_009c6c30(); };

// @ 0x009c7ff0
extern "C" int __fastcall FUN_009c7ff0(char* self, int edx_unused)
{
    int t1003;
    int t1005;
    int t1011;
    int t1009;
    int t1010;
    int t1012;
    int t1015;
    int t1016;
    int t1020;
    int t1027;
    int t8;
    int t1028;
    int t1029;
    int t1030;
    t1003 = (int)((int)(self));
    t1005 = (int)(t1003 + (int)8);
    *(unsigned char*)((char*)(t1003) + 36) = (unsigned char)((int)0);
    *(int*)((char*)(t1003)) = (int)((int)0);
    ((C_009c6c30*)(t1005))->FUN_009c6c30();
    t1011 = (int)(t1003 + (int)40);
    t1009 = (int)(*(int*)((char*)(t1011)));
    t1010 = (int)(*(int*)((char*)(t1011) + 4));
    t1012 = (int)FUN_009c6860((unsigned int)(t1010), (unsigned int)(t1010), (unsigned int)(t1009));
    t1015 = (int)(*(int*)((char*)(t1011) + 4));
    t1016 = (int)(t1011);
    ((C_009c67e0*)(t1016))->FUN_009c67e0((unsigned int)(t1012), (unsigned int)(t1015));
    t1020 = (int)(t1010 - t1009);
    t1027 = (int)(t1020 / (int)(-20));
    t8 = (int)(t1027 << (int)2);
    t1028 = (int)(t1027 + t8);
    t1029 = (int)(t1028 + t1028);
    t1030 = (int)(t1029 + t1029);
    *(int*)((char*)(t1011) + 4) += t1030;
    return (int)(t1027);
}
