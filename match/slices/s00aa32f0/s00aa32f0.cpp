// 0x00aa32f0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00aa2f00/s00aa2f00.cpp, src/game/Swarm/ParticlesDescription.cpp.

extern "C" unsigned char g_013ef094[];
struct C_00a87300 { void FUN_00a87300(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00f47380(...);

// @ 0x00aa32f0
extern "C" int __fastcall FUN_00aa32f0(char* self, int edx_unused)
{
    int t1002;
    int t1003;
    int t1007;
    int t1011;
    int t1015;
    int t1016;
    int t1018;
    int t1019;
    int t1023;
    int t1027;
    int t1032;
    int t1036;
    int t1040;
    int t1044;
    int t1048;
    int t1052;
    int t1056;
    int t1060;
    t1002 = (int)((int)(self));
    t1003 = (int)(*(int*)((char*)(t1002) + 604));
    if (t1003 != (int)0) {
        if ((int)*(int*)((char*)(t1003) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1003));
        }
    }
    t1007 = (int)(*(int*)((char*)(t1002) + 576));
    if (t1007 != (int)0) {
        if ((int)*(int*)((char*)(t1007) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1007));
        }
    }
    t1011 = (int)(*(int*)((char*)(t1002) + 540));
    if (t1011 != (int)0) {
        if ((int)*(int*)((char*)(t1011) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1011));
        }
    }
    t1015 = (int)(*(int*)((char*)(t1002) + 432));
    t1016 = (int)(*(int*)((char*)(t1002) + 428));
    t1018 = (int)(t1002 + (int)428);
    t1019 = (int)(t1018);
    ((C_00a87300*)(t1019))->FUN_00a87300((unsigned int)(t1016), (unsigned int)(t1015));
    t1023 = (int)(*(int*)((char*)(t1018)));
    if (t1023 != (int)0) {
        if ((int)*(int*)((char*)(t1023) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1023));
        }
    }
    t1027 = (int)(*(int*)((char*)(t1002) + 408));
    if (t1027 != (int)0) {
        if ((int)*(int*)((char*)(t1027) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1027));
        }
    }
    t1032 = (int)(*(int*)((char*)(t1002) + 388));
    if (t1032 != (int)0) {
        if ((int)*(int*)((char*)(t1032) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1032));
        }
    }
    t1036 = (int)(*(int*)((char*)(t1002) + 364));
    if (t1036 != (int)0) {
        if ((int)*(int*)((char*)(t1036) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1036));
        }
    }
    t1040 = (int)(*(int*)((char*)(t1002) + 244));
    if (t1040 != (int)0) {
        if ((int)*(int*)((char*)(t1040) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1040));
        }
    }
    t1044 = (int)(*(int*)((char*)(t1002) + 212));
    if (t1044 != (int)0) {
        if ((int)*(int*)((char*)(t1044) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1044));
        }
    }
    t1048 = (int)(*(int*)((char*)(t1002) + 184));
    if (t1048 != (int)0) {
        if ((int)*(int*)((char*)(t1048) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1048));
        }
    }
    t1052 = (int)(*(int*)((char*)(t1002) + 160));
    if (t1052 != (int)0) {
        if ((int)*(int*)((char*)(t1052) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1052));
        }
    }
    t1056 = (int)(*(int*)((char*)(t1002) + 136));
    if (t1056 != (int)0) {
        if ((int)*(int*)((char*)(t1056) - 4) != (int)0) {
            FUN_00f47380((unsigned int)(t1056));
        }
    }
    t1060 = (int)(*(int*)((char*)(t1002) + 104));
    if (t1060 != (int)0) {
        if ((int)*(int*)((char*)(t1060) - 4) != (int)0) {
            t1060 = (int)FUN_00f47380((unsigned int)(t1060));
        }
    }
    *(int*)((char*)(t1002)) = (int)((int)g_013ef094);
    return (int)(t1060);
}
