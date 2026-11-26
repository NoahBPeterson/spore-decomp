// 0x00877ac0: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

extern "C" int __cdecl FUN_00876ee0(...);
extern "C" int __cdecl FUN_00876f70(...);
extern "C" int __cdecl FUN_00876fb0(...);
extern "C" int __cdecl FUN_00877000(...);
extern "C" int __cdecl FUN_00877250(...);
extern "C" int __cdecl FUN_00877440(...);
extern "C" int __cdecl FUN_00877570(...);
extern "C" int __cdecl FUN_00877810(...);
extern "C" int __cdecl FUN_00877930(...);

// @ 0x00877ac0
extern "C" void __cdecl FUN_00877ac0(int a4)
{
    int t1001;
    int t2;
    int t1002;
    int t1003;
    int t1004;
    int t1005;
    int t8;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t13;
    int t1014;
    int t1015;
    int t1016;
    unsigned char t17;
    int t1019;
    int t1020;
    int t1021;
    int t1022;
    unsigned char t22;
    int t1025;
    int t1026;
    int t1027;
    unsigned char t26;
    int t1031;
    int t1032;
    int t1033;
    int t1034;
    int t31;
    int t1037;
    int t1038;
    int t1039;
    int t35;
    int t1042;
    int t1043;
    int t1044;
    unsigned char t39;
    int t1047;
    int t1048;
    int t1049;
    unsigned char t43;
    int t1052;
    int t1053;
    int t1054;
    t1001 = (int)((int)(a4));
    if (t1001 != (int)0) {
        t2 = (int)((int)*(int*)((char*)(t1001) + 112) & (int)1048576);
        if (t2 != (int)0) {
            t1002 = (int)(*(int*)((char*)(t1001) + 92));
            if (t1002 != (int)0) {
                t1003 = (int)(*(int*)((char*)(t1001) + 236));
                t1004 = (int)(t1003 + (int)1);
                t1005 = (int)(t1001 + (int)256);
                t1002 = (int)((int (__cdecl*)(int, int, int))(t1002))((int)(t1001), (int)(t1005), (int)(t1004));
            }
        }
        t8 = (int)((int)*(int*)((char*)(t1001) + 112) & (int)32768);
        if (t8 != (int)0) {
            t1008 = (int)(*(int*)((char*)(t1001) + 108));
            t1009 = (int)(*(int*)((char*)(t1001) + 236));
            t1010 = (int)(t1009 + (int)1);
            t1011 = (int)(t1001 + (int)256);
            t1002 = (int)FUN_00877000((unsigned int)(t1011), (unsigned int)(t1010), (unsigned int)(t1008));
        }
        t13 = (int)((int)*(int*)((char*)(t1001) + 112) & (int)65536);
        if (t13 != (int)0) {
            t1014 = (int)(*(int*)((char*)(t1001) + 236));
            t1015 = (int)(t1014 + (int)1);
            t1016 = (int)(t1001 + (int)256);
            t1002 = (int)FUN_00876fb0((unsigned int)(t1016), (unsigned int)(t1015));
        }
        t17 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1001) + 112) & (unsigned char)4);
        if (t17 != (unsigned char)0) {
            t1019 = (int)(*(unsigned char*)((char*)(t1001) + 295));
            t1020 = (int)(*(int*)((char*)(t1001) + 236));
            t1021 = (int)(t1020 + (int)1);
            t1022 = (int)(t1001 + (int)256);
            t1002 = (int)FUN_00877440((unsigned int)(t1022), (unsigned int)(t1021), (unsigned int)(t1019));
        }
        t22 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1001) + 112) & (unsigned char)16);
        if (t22 != (unsigned char)0) {
            t1025 = (int)(*(int*)((char*)(t1001) + 236));
            t1026 = (int)(t1025 + (int)1);
            t1027 = (int)(t1001 + (int)256);
            t1002 = (int)FUN_00876f70((unsigned int)(t1027), (unsigned int)(t1026));
        }
        t26 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1001) + 112) & (unsigned char)8);
        if (t26 != (unsigned char)0) {
            t1031 = (int)(*(int*)((char*)(t1001) + 236));
            t1032 = (int)(t1001 + (int)385);
            t1033 = (int)(t1031 + (int)1);
            t1034 = (int)(t1001 + (int)256);
            t1002 = (int)FUN_00877570((unsigned int)(t1034), (unsigned int)(t1033), (unsigned int)(t1032));
        }
        t31 = (int)((int)*(int*)((char*)(t1001) + 112) & (int)131072);
        if (t31 != (int)0) {
            t1037 = (int)(*(int*)((char*)(t1001) + 236));
            t1038 = (int)(t1037 + (int)1);
            t1039 = (int)(t1001 + (int)256);
            t1002 = (int)FUN_00877810((unsigned int)(t1039), (unsigned int)(t1038));
        }
        t35 = (int)((int)*(int*)((char*)(t1001) + 112) & (int)524288);
        if (t35 != (int)0) {
            t1042 = (int)(*(int*)((char*)(t1001) + 236));
            t1043 = (int)(t1042 + (int)1);
            t1044 = (int)(t1001 + (int)256);
            t1002 = (int)FUN_00877930((unsigned int)(t1044), (unsigned int)(t1043));
        }
        t39 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1001) + 112) & (unsigned char)1);
        if (t39 != (unsigned char)0) {
            t1047 = (int)(*(int*)((char*)(t1001) + 236));
            t1048 = (int)(t1047 + (int)1);
            t1049 = (int)(t1001 + (int)256);
            t1002 = (int)FUN_00877250((unsigned int)(t1049), (unsigned int)(t1048));
        }
        t43 = (unsigned char)((unsigned char)*(unsigned char*)((char*)(t1001) + 112) & (unsigned char)32);
        if (t43 != (unsigned char)0) {
            t1052 = (int)(*(int*)((char*)(t1001) + 236));
            t1053 = (int)(t1052 + (int)1);
            t1054 = (int)(t1001 + (int)256);
            t1002 = (int)FUN_00876ee0((unsigned int)(t1054), (unsigned int)(t1053));
        }
    }
    return;
}
