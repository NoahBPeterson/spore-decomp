// 0x00e86880: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPGonzago/_at_00e80000.cpp, match/slices/s00e85dc0/s00e85dc0.cpp.

// @ 0x00e86880
extern "C" int __cdecl FUN_00e86880(int a4, int a8, float a12, int a16)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1005;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1013;
    int t1014;
    float t1015;
    int t1016;
    int t1017;
    int t1018;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(int*)((char*)(t1000) + 4));
    t1002 = (int)(*(int*)((char*)(t1001)));
    if (t1002 == (int)*(int*)((char*)(t1001) + 20)) {
        t1003 = (int)((int)0);
    } else {
        t1005 = (int)(*(int*)((char*)(t1001) + 4));
        if (t1002 == t1005) {
            t1006 = (int)(*(int*)((char*)(t1001) + 16));
            t1007 = (int)(t1006 * t1002);
            t1008 = (int)(t1007 + (int)*(int*)((char*)(t1001) + 12));
            t1009 = (int)(t1002 + (int)1);
            t1010 = (int)(t1005 + (int)1);
            *(int*)((char*)(t1001) + 4) = (int)(t1010);
        } else {
            t1008 = (int)(*(int*)((char*)(t1001) + 8));
            t1011 = (int)(*(int*)((char*)(t1008)));
            *(int*)((char*)(t1001) + 8) = (int)(t1011);
            t1009 = (int)(t1002 + (int)1);
        }
        *(int*)((char*)(t1001)) = (int)(t1009);
        t1003 = (int)(t1008);
    }
    t1013 = (int)((int)(a8));
    t1014 = (int)(*(int*)((char*)(t1013)));
    t1015 = (float)((float)(a12));
    *(int*)((char*)(t1003)) = (int)(t1014);
    t1016 = (int)(*(int*)((char*)(t1013) + 4));
    *(int*)((char*)(t1003) + 4) = (int)(t1016);
    t1017 = (int)(*(int*)((char*)(t1013) + 8));
    t1018 = (int)((int)(a16));
    *(int*)((char*)(t1003) + 8) = (int)(t1017);
    *(float*)((char*)(t1003) + 12) = (float)(t1015);
    *(int*)((char*)(t1003) + 20) = (int)((int)0);
    *(int*)((char*)(t1003) + 24) = (int)(t1018);
    return (int)(t1003);
}
