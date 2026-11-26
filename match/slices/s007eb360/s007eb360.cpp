// 0x007eb360: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s007ea440/s007ea440.cpp, src/game/SPEngine/SPAppTelemetry.cpp.

struct C_007eb000 { void FUN_007eb000(unsigned int, unsigned int); };

// @ 0x007eb360
extern "C" int __fastcall FUN_007eb360(char* self, int edx_unused, int a4)
{
    int t1001;
    int t1004;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    t1001 = (int)((int)(a4));
    t1004 = (int)((int)(self));
    t1005 = (int)(*(int*)((char*)(t1001) + 4));
    t1006 = (int)(t1005 - (int)*(int*)((char*)(t1001)));
    t1007 = (int)(t1001 + (int)12);
    t1008 = (int)(t1006 >> (int)2);
    t1009 = (int)(t1004);
    ((C_007eb000*)(t1009))->FUN_007eb000((unsigned int)(t1008), (unsigned int)(t1007));
    t1013 = (int)(*(int*)((char*)(t1001) + 4));
    t1014 = (int)(*(int*)((char*)(t1001)));
    t1015 = (int)(*(int*)((char*)(t1004)));
    if (t1014 != t1013) {
        do {
            if (t1015 != (int)0) {
                t1016 = (int)(*(int*)((char*)(t1014)));
                *(int*)((char*)(t1015)) = (int)(t1016);
            }
            t1014 = (int)(t1014 + (int)4);
            t1015 = (int)(t1015 + (int)4);
        } while (t1014 != t1013);
    }
    t1017 = (int)(t1004);
    *(int*)((char*)(t1004) + 4) = (int)(t1015);
    return (int)(t1017);
}
