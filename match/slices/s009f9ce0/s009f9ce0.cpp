// 0x009f9ce0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s009f9b40/s009f9b40.cpp, src/game/SPCreatureAnim/jiggles.cpp.

extern "C" unsigned char g_00657965[];
extern "C" unsigned char g_01550b0c[];
extern "C" unsigned char g_01550b10[];
extern "C" unsigned char g_01550b14[];
extern "C" unsigned char g_0166c01c[];
extern "C" unsigned char g_0166c020[];
struct C_009b30e0 { int FUN_009b30e0(unsigned int); };
struct C_009b3110 { int FUN_009b3110(); };

// @ 0x009f9ce0
extern "C" int __cdecl FUN_009f9ce0(int a4)
{
    int t1002;
    int t1003;
    int t1006;
    int t1007;
    int t1010;
    int t1011;
    int t1014;
    int t1015;
    int t1018;
    int t1019;
    int t1020;
    int t1023;
    int t1024;
    int t1027;
    int t1028;
    int t1031;
    int t1033;
    int t1036;
    t1002 = (int)((int)(a4));
    if ((int)(*(int*)g_0166c01c) != (int)0) {
        t1003 = (int)(t1002 + (int)336);
        t1006 = (int)((C_009b30e0*)(t1003))->FUN_009b30e0((unsigned int)((int)g_00657965));
        if ((unsigned char)(t1006) != (unsigned char)0) goto L9f9dac;
    }
    if ((int)(*(int*)g_01550b0c) != (int)0) {
        t1007 = (int)(t1002 + (int)336);
        t1010 = (int)((C_009b30e0*)(t1007))->FUN_009b30e0((unsigned int)((int)1953853293));
        if ((unsigned char)(t1010) != (unsigned char)0) goto L9f9dac;
    }
    if ((int)(*(int*)g_01550b10) != (int)0) {
        t1011 = (int)(t1002 + (int)336);
        t1014 = (int)((C_009b30e0*)(t1011))->FUN_009b30e0((unsigned int)((int)1701278307));
        if ((unsigned char)(t1014) != (unsigned char)0) goto L9f9dac;
    }
    if ((int)(*(int*)g_01550b14) != (int)0) {
        t1015 = (int)(t1002 + (int)336);
        t1018 = (int)((C_009b30e0*)(t1015))->FUN_009b30e0((unsigned int)((int)1735289207));
        if ((unsigned char)(t1018) != (unsigned char)0) goto L9f9dac;
    }
    t1019 = (int)(t1002 + (int)336);
    t1020 = (int)(t1019);
    t1023 = (int)((C_009b30e0*)(t1020))->FUN_009b30e0((unsigned int)((int)1818456183));
    if ((unsigned char)(t1023) == (unsigned char)0) {
        t1024 = (int)(t1019);
        t1027 = (int)((C_009b30e0*)(t1024))->FUN_009b30e0((unsigned int)((int)1818457197));
        if ((unsigned char)(t1027) == (unsigned char)0) {
            if ((int)(*(int*)g_0166c020) != (int)0) {
                t1028 = (int)(t1019);
                t1031 = (int)((C_009b3110*)(t1028))->FUN_009b3110();
                if (t1031 == (int)0) {
                    if ((int)*(int*)((char*)(t1002) + 520) == t1031) goto L9f9dac;
                }
            }
            t1033 = (int)((int)1);
            return (int)(t1033);
        }
    }
    L9f9dac:;
    t1036 = (int)((int)0);
    return (int)(t1036);
}
