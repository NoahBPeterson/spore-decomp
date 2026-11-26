// 0x00bc51c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00bc0000.cpp, match/slices/s00bc4730/s00bc4730.cpp.

struct C_00926650 { int FUN_00926650(unsigned int, unsigned int); };
struct C_00bc4820 { int FUN_00bc4820(); };

// @ 0x00bc51c0
extern "C" int __fastcall FUN_00bc51c0(char* self, int edx_unused)
{
    int t1003;
    int t1005;
    int t1006;
    int t1009;
    int t1010;
    int t1011;
    int t1014;
    int t1015;
    t1003 = (int)((int)(self));
    t1005 = (int)(t1003 + (int)8);
    do {
        if ((int)*(int*)((char*)(t1005) + 16) != (int)0) goto Lbc51ff;
        t1006 = (int)(t1005);
        t1009 = (int)((C_00926650*)(t1006))->FUN_00926650((unsigned int)((int)0), (unsigned int)((int)0));
    } while ((unsigned char)(t1009) != (unsigned char)0);
    t1010 = (int)((int)0);
    Lbc51df:;
    t1011 = (int)(t1010 + (int)8);
    if (t1011 != (int)0) {
        t1009 = (int)((C_00bc4820*)(t1011))->FUN_00bc4820();
    }
    *(int*)((char*)(t1010)) = (int)(t1003);
    t1014 = (int)(*(int*)((char*)(t1003) + 4));
    *(int*)((char*)(t1010) + 4) = (int)(t1014);
    t1015 = (int)(*(int*)((char*)(t1003) + 4));
    *(int*)((char*)(t1015)) = (int)(t1010);
    *(int*)((char*)(t1003) + 4) = (int)(t1010);
    return (int)(t1009);
    Lbc51ff:;
    t1010 = (int)(*(int*)((char*)(t1005) + 16));
    t1009 = (int)(*(int*)((char*)(t1010)));
    *(int*)((char*)(t1005) + 16) = (int)(t1009);
    goto Lbc51df;
}
