// 0x00b0f950: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPTerrain/SPTerrainCameraController.cpp, match/slices/s00b0f270/s00b0f270.cpp.

struct C_0067cab0 { int FUN_0067cab0(unsigned int); };
extern "C" int __stdcall FUN_0067cab0(unsigned int);
struct C_00801950 { void FUN_00801950(); };
struct C_00801980 { int FUN_00801980(); };

// @ 0x00b0f950
extern "C" void __fastcall FUN_00b0f950(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1007;
    int t1008;
    int t1014;
    int t1015;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    if ((unsigned char)*(unsigned char*)((char*)(t1004) + 17) != (unsigned char)(t1001)) {
        if ((unsigned char)(t1001) != (unsigned char)0) {
            *(float*)((char*)(t1004) + 904) = (float)(*(float*)((char*)(t1004) + 840));
            *(float*)((char*)(t1004) + 908) = (float)(*(float*)((char*)(t1004) + 844));
            t1007 = (int)((C_0067cab0*)((int)(self)))->FUN_0067cab0((unsigned int)((int)109075747));
            t1008 = (int)(t1007);
            ((C_00801950*)(t1008))->FUN_00801950();
        }
        t1014 = (int)FUN_0067cab0((unsigned int)(t1001));
        t1015 = (int)(t1014);
        ((C_00801980*)(t1015))->FUN_00801980();
    }
    *(unsigned char*)((char*)(t1004) + 17) = (unsigned char)((unsigned char)(t1001));
    return;
}
