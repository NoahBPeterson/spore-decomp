// 0x00dff1a0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPGalaxyGameEntry.cpp, match/slices/s00dfe460/s00dfe460.cpp.

#include <string.h>
struct C_00dfb280 { void FUN_00dfb280(unsigned int); };
struct C_00dfec50 { void FUN_00dfec50(unsigned int); };

// @ 0x00dff1a0
extern "C" int __fastcall FUN_00dff1a0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1004;
    int t1008;
    int t1009;
    unsigned char t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1022;
    int t1023;
    int t1024;
    int t1029;
    int t1030;
    int t1031;
    int t1032;
    int t1036;
    int t1037;
    int t1041;
    int t1042;
    int t1043;
    int t1044;
    int t1045;
    int t1047;
    int t1050;
    t1002 = (int)((int)(self));
    t1004 = (int)((int)(a4));
    t1008 = (int)(t1004);
    t1009 = (int)(t1002);
    memcpy((void*)(t1009), (const void*)(t1008), (unsigned int)((int)32));
    t1014 = (unsigned char)(*(unsigned char*)((char*)(t1004) + 32));
    *(unsigned char*)((char*)(t1002) + 32) = (unsigned char)(t1014);
    t1015 = (int)(*(int*)((char*)(t1004) + 36));
    *(int*)((char*)(t1002) + 36) = (int)(t1015);
    t1016 = (int)(t1004 + (int)40);
    t1017 = (int)(t1002 + (int)40);
    memcpy((void*)(t1017), (const void*)(t1016), (unsigned int)((int)32));
    t1022 = (int)(*(int*)((char*)(t1004) + 72));
    *(int*)((char*)(t1002) + 72) = (int)(t1022);
    t1023 = (int)(t1004 + (int)80);
    t1024 = (int)(t1002 + (int)80);
    memcpy((void*)(t1024), (const void*)(t1023), (unsigned int)((int)32));
    t1029 = (int)(t1002 + (int)112);
    t1030 = (int)(t1029 + (int)24);
    *(int*)((char*)(t1029)) = (int)(t1030);
    *(int*)((char*)(t1029) + 4) = (int)(t1030);
    t1031 = (int)(t1030 + (int)9984);
    *(int*)((char*)(t1029) + 8) = (int)(t1031);
    t1032 = (int)(t1004 + (int)112);
    *(int*)((char*)(t1029) + 20) = (int)((int)0);
    ((C_00dfec50*)(t1029))->FUN_00dfec50((unsigned int)(t1032));
    t1036 = (int)(t1004 + (int)10120);
    t1037 = (int)(t1002 + (int)10120);
    ((C_00dfb280*)(t1037))->FUN_00dfb280((unsigned int)(t1036));
    t1041 = (int)(*(int*)((char*)(t1004) + 10180));
    *(int*)((char*)(t1002) + 10180) = (int)(t1041);
    t1042 = (int)(*(int*)((char*)(t1004) + 10184));
    *(int*)((char*)(t1002) + 10184) = (int)(t1042);
    t1043 = (int)(*(int*)((char*)(t1004) + 10188));
    *(int*)((char*)(t1002) + 10188) = (int)(t1043);
    t1044 = (int)(*(int*)((char*)(t1004) + 10192));
    *(int*)((char*)(t1002) + 10192) = (int)(t1044);
    t1045 = (int)(*(int*)((char*)(t1004) + 10200));
    *(int*)((char*)(t1002) + 10200) = (int)(t1045);
    t1047 = (int)(*(int*)((char*)(t1004) + 10204));
    *(int*)((char*)(t1002) + 10204) = (int)(t1047);
    t1050 = (int)(t1002);
    return (int)(t1050);
}
