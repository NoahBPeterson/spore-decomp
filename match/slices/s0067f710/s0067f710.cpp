// 0x0067f710: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPEngine/SPCheatManager.cpp, match/slices/s0067eae0/s0067eae0.cpp.

struct C_00690b80 { void FUN_00690b80(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00921580(...);
extern "C" int __cdecl FUN_0093d5d0(...);

// @ 0x0067f710
extern "C" int __fastcall FUN_0067f710(char* self, int edx_unused, int a4, int a8)
{
    int t1003;
    int t1004;
    int t1005;
    int v_l4;
    int t1007;
    int t1009;
    int t1011;
    int t1012;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1023;
    t1003 = (int)(*(int*)((char*)((int)(self)) + 20));
    t1004 = (int)((int)0);
    t1005 = (int)((int)(self) + (int)16);
    v_l4 = (int)(t1004);
    if (t1003 != t1005) {
        t1007 = (int)((int)(a4));
        t1009 = (int)((int)(a8));
        do {
            t1011 = (int)(*(int*)((char*)(t1003) + 16));
            t1012 = (int)FUN_0093d5d0((unsigned int)(t1011), (unsigned int)(t1007), (unsigned int)((int)0));
            if ((unsigned char)(t1012) != (unsigned char)0) {
                t1015 = (int)(*(int*)((char*)(t1009) + 4));
                t1016 = (int)(*(int*)((char*)(t1003) + 16));
                *(int*)&(a8) = (int)(t1016);
                if ((unsigned int)(t1015) < (unsigned int)*(int*)((char*)(t1009) + 8)) {
                    t1017 = (int)(t1015 + (int)4);
                    *(int*)((char*)(t1009) + 4) = (int)(t1017);
                    if (t1015 == (int)0) goto L67f76d;
                    *(int*)((char*)(t1015)) = (int)(t1016);
                    goto L67f76d;
                }
                t1018 = (int)((int)&a8);
                t1019 = (int)(t1009);
                ((C_00690b80*)(t1019))->FUN_00690b80((unsigned int)(t1015), (unsigned int)(t1018));
                L67f76d:;
                v_l4 = (int)(v_l4 + (int)1);
            }
            t1023 = (int)FUN_00921580((unsigned int)(t1003));
            t1003 = (int)(t1023);
        } while (t1003 != t1005);
        t1004 = (int)(v_l4);
    }
    return (int)(t1004);
}
