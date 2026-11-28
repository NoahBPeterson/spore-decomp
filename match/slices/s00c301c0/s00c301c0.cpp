// 0x00c301c0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/SPCreatureMissions.cpp, match/slices/s00c2f830/s00c2f830.cpp.

struct C_00c0c1a0 { int FUN_00c0c1a0(); };
struct C_00c2fa50 { int FUN_00c2fa50(); };

// @ 0x00c301c0
extern "C" void __fastcall FUN_00c301c0(char* self, int edx_unused, int a4)
{
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    unsigned char t1018;
    int t1019;
    t1002 = (int)((int)(self));
    t1003 = (int)((int)(a4));
    t1004 = (int)(*(int*)((char*)(t1003) + 2856));
    *(int*)((char*)(t1002) + 128) = (int)(t1004);
    t1005 = (int)(*(int*)((char*)(t1003) + 2860));
    *(int*)((char*)(t1002) + 132) = (int)(t1005);
    t1006 = (int)(*(int*)((char*)(t1003) + 2864));
    *(int*)((char*)(t1002) + 136) = (int)(t1006);
    t1007 = (int)((C_00c0c1a0*)(t1003))->FUN_00c0c1a0();
    if (t1007 != (int)0) {
        t1010 = (int)(*(int*)((char*)(t1007) + 1020));
        *(int*)((char*)(t1002) + 172) = (int)(t1010);
        t1011 = (int)(*(int*)((char*)(t1007) + 1024));
        *(int*)((char*)(t1002) + 176) = (int)(t1011);
        t1012 = (int)(*(int*)((char*)(t1007) + 1028));
        *(int*)((char*)(t1002) + 180) = (int)(t1012);
        t1013 = (int)(*(int*)((char*)(t1007) + 1032));
        *(int*)((char*)(t1002) + 184) = (int)(t1013);
        t1014 = (int)(*(int*)((char*)(t1007) + 1036));
        *(int*)((char*)(t1002) + 188) = (int)(t1014);
        t1015 = (int)(*(int*)((char*)(t1007) + 1048));
        *(int*)((char*)(t1002) + 148) = (int)(t1015);
        t1016 = (int)(*(int*)((char*)(t1007) + 1056));
        *(int*)((char*)(t1002) + 152) = (int)(t1016);
        t1017 = (int)(*(int*)((char*)(t1007) + 816));
        *(int*)((char*)(t1002) + 192) = (int)(t1017);
        t1018 = (unsigned char)(*(unsigned char*)((char*)(t1007) + 905));
        *(unsigned char*)((char*)(t1002) + 196) = (unsigned char)(t1018);
    }
    t1019 = (int)(t1002);
    ((C_00c2fa50*)(t1019))->FUN_00c2fa50();
    return;
}
